/*
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all copies.
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <linux/version.h>
#include <linux/phy.h>

#if defined(IN_LINUX_STD_PTP)
#include <linux/if_vlan.h>
#include <linux/net_tstamp.h>
#include <linux/ptp_classify.h>
#include <linux/ptp_clock_kernel.h>
#include <linux/kthread.h>

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4,4,0))
#include <linux/time64.h>
#else
#include <linux/time.h>
#define ns_to_timespec64 ns_to_timespec
#define timespec64_to_ns timespec_to_ns
#define timespec64 timespec
#endif

#endif

#include "hsl.h"
#include "hsl_phy.h"
#include "ssdk_plat.h"
#include "qca808x_phy.h"
#include "sfp_phy.h"

#include "fal_ptp.h"
#include "qca808x_ptp.h"

#define QCA808X_PTP_EMBEDDED_MODE   0xa
#define QCA808X_PTP_MSG_SNYC        0X0
#define QCA808X_PTP_MSG_DREQ        0X1
#define QCA808X_PTP_MSG_PREQ        0X2
#define QCA808X_PTP_MSG_PRESP       0X3

#define SKB_TIMESTAMP_TIMEOUT	2 /* jiffies */

#define PHY_INVALID_DATA            0xffff
#define QCA808X_INTR_INIT           0xec00

#define QCA808X_PTP_TICK_RATE_125M  8
#define QCA808X_PTP_TICK_RATE_200M  5

#define QCA808X_PHY_LINK_UP         1
#define QCA808X_PHY_LINK_DOWN       0

#if defined(IN_LINUX_STD_PTP)
struct qca808x_ptp_clock;
#endif
struct qca808x_phy_info;
typedef struct {
	struct phy_device *phydev;
	struct qca808x_phy_info *phy_info;
#if defined(IN_LINUX_STD_PTP)
	struct qca808x_ptp_clock *clock;
	struct delayed_work tx_ts_work;
	struct delayed_work rx_ts_work;
	/* work for gps sencond sync and ingress trigger time record*/
	struct delayed_work ts_schedule_work;
	struct sk_buff_head tx_queue;
	struct sk_buff_head rx_queue;
	/* ingress trigger time stamp */
	a_int32_t ptp_in_trig_nsec;
	a_bool_t ptp_in_trig_flag;
#endif
} qca808x_priv;

#if defined(IN_LINUX_STD_PTP)
struct qca808x_ptp_clock{
	struct ptp_clock_info caps;
	struct ptp_clock *ptp_clock;
	struct mutex tsreg_lock;
	qca808x_priv *priv;
};

typedef struct {
	/* ptp filter class */
	a_int32_t ptp_type;
	/* ptp frame type */
	a_int32_t pkt_type;
} qca808x_ptp_cb;
#endif

struct qca808x_phy_info {
	struct list_head list;
	a_uint32_t dev_id;
	/* phy real address,it is the mdio addr or the i2c slave addr */
	a_uint32_t phy_addr;
	/* the address of phy device, it is a fake addr for the i2c accessed phy */
	a_uint32_t phydev_addr;
	a_uint16_t clock_mode;
	a_uint16_t step_mode;
	a_int32_t speed;
	a_bool_t gps_seconds_sync_en;
};

static LIST_HEAD(g_qca808x_phy_list);

static struct qca808x_phy_info* qca808x_phy_info_get(a_uint32_t phy_addr)
{
	struct qca808x_phy_info *pdata = NULL;
	list_for_each_entry(pdata, &g_qca808x_phy_list, list) {
		if (pdata->phydev_addr == phy_addr) {
			return pdata;
		}
	}

	SSDK_ERROR("%s can't get the data for phy addr: %d\n", __func__, phy_addr);
	return NULL;
}

void qca808x_ptp_gm_gps_seconds_sync_enable(a_uint32_t dev_id,
		a_uint32_t phy_addr, a_bool_t en)
{
	struct qca808x_phy_info *pdata;
#if defined(IN_PHY_I2C_MODE)
	a_uint32_t port_id;
	port_id = qca_ssdk_phy_addr_to_port(dev_id, phy_addr);
	if (hsl_port_phy_access_type_get(dev_id, port_id) == PHY_I2C_ACCESS) {
		phy_addr = qca_ssdk_port_to_phy_mdio_fake_addr(dev_id, port_id);
	}
#endif

	pdata = qca808x_phy_info_get(phy_addr);
	if (pdata) {
		pdata->gps_seconds_sync_en = en;
	}

	return;
}

a_bool_t qca808x_ptp_gm_gps_seconds_sync_status_get(a_uint32_t dev_id,
		a_uint32_t phy_addr)
{
	struct qca808x_phy_info *pdata;
#if defined(IN_PHY_I2C_MODE)
	a_uint32_t port_id;
	port_id = qca_ssdk_phy_addr_to_port(dev_id, phy_addr);
	if (hsl_port_phy_access_type_get(dev_id, port_id) == PHY_I2C_ACCESS) {
		phy_addr = qca_ssdk_port_to_phy_mdio_fake_addr(dev_id, port_id);
	}
#endif

	pdata = qca808x_phy_info_get(phy_addr);
	if (pdata) {
		return pdata->gps_seconds_sync_en;
	}

	return A_FALSE;
}

void qca808x_ptp_clock_mode_config(a_uint32_t dev_id,
		a_uint32_t phy_addr, a_uint16_t clock_mode, a_uint16_t step_mode)
{
	struct qca808x_phy_info *pdata;
#if defined(IN_PHY_I2C_MODE)
	a_uint32_t port_id;
	port_id = qca_ssdk_phy_addr_to_port(dev_id, phy_addr);
	if (hsl_port_phy_access_type_get(dev_id, port_id) == PHY_I2C_ACCESS) {
		phy_addr = qca_ssdk_port_to_phy_mdio_fake_addr(dev_id, port_id);
	}
#endif

	pdata = qca808x_phy_info_get(phy_addr);

	if (pdata) {
		pdata->clock_mode = clock_mode;
		pdata->step_mode = step_mode;
	}

	return;
}

#if defined(IN_LINUX_STD_PTP)
static sw_error_t qca808x_ptp_clock_synce_clock_enable(a_uint32_t dev_id,
		a_uint32_t phy_id, a_bool_t enable)
{
	a_uint16_t phy_data, phy_data1;
	sw_error_t ret = SW_OK;

	phy_data = qca808x_phy_debug_read(dev_id, phy_id,
			QCA808X_DEBUG_ANA_CLOCK_CTRL_REG);

	phy_data1 = qca808x_phy_mmd_read(dev_id, phy_id, QCA808X_PHY_MMD7_NUM,
			QCA808X_MMD7_CLOCK_CTRL_REG);

	if (enable == A_TRUE) {
		/* enable analog synce clock output */
		phy_data |= QCA808X_ANALOG_PHY_SYNCE_CLOCK_EN;
		/* enable digital synce clock output */
		phy_data1 |= QCA808X_DIGITAL_PHY_SYNCE_CLOCK_EN;
	} else {
		phy_data &= ~QCA808X_ANALOG_PHY_SYNCE_CLOCK_EN;
		phy_data1 &= ~QCA808X_DIGITAL_PHY_SYNCE_CLOCK_EN;
	}

	ret = qca808x_phy_debug_write(dev_id, phy_id,
			QCA808X_DEBUG_ANA_CLOCK_CTRL_REG, phy_data);

	ret |= qca808x_phy_mmd_write(dev_id, phy_id, QCA808X_PHY_MMD7_NUM,
			QCA808X_MMD7_CLOCK_CTRL_REG, phy_data1);
	return ret;
}

static sw_error_t qca808x_ptp_config_init(a_uint32_t dev_id, a_uint32_t phy_id)
{
	fal_ptp_config_t ptp_config;
	fal_ptp_reference_clock_t ptp_ref_clock;
	fal_ptp_rx_timestamp_mode_t rx_ts_mode;
	fal_ptp_time_t ptp_time = {0};
	sw_error_t ret = SW_OK;

	/* enable ptp OC two-step mode */
	ptp_config.ptp_en = A_TRUE;
	ptp_config.clock_mode = FAL_OC_CLOCK_MODE;
	ptp_config.step_mode = FAL_TWO_STEP_MODE;
	ret = qca808x_phy_ptp_config_set(dev_id, phy_id, &ptp_config);

	qca808x_ptp_clock_mode_config(dev_id, phy_id, ptp_config.clock_mode,
			ptp_config.step_mode);

	/* adjust frequency to 8ns(125MHz) */
	ptp_time.nanoseconds = QCA808X_PTP_TICK_RATE_125M;
	ret |= qca808x_phy_ptp_rtc_adjfreq_set(dev_id, phy_id, &ptp_time);

	/* use SyncE reference clock */
	ptp_ref_clock = FAL_REF_CLOCK_SYNCE;
	ret |= qca808x_phy_ptp_reference_clock_set(dev_id, phy_id, ptp_ref_clock);

	/* use Embed mode to get RX timestamp */
	rx_ts_mode = FAL_RX_TS_EMBED;
	ret |= qca808x_phy_ptp_rx_timestamp_mode_set(dev_id, phy_id, rx_ts_mode);

	/* enable SYNCE clock output */
	ret |= qca808x_ptp_clock_synce_clock_enable(dev_id, phy_id, A_TRUE);

	if (ret != SW_OK) {
		SSDK_ERROR("%s failed\n", __func__);
	}

	return ret;
}
#endif

static int qca808x_match_phy_device(struct phy_device *phydev)
{
	return phydev->phy_id == QCA8081_PHY;
}

static sw_error_t qca808x_phy_config_init(struct phy_device *phydev)
{
	a_uint16_t phy_data;
	a_uint32_t features;
	a_uint32_t dev_id = 0, phy_id = 0;
	qca808x_priv *priv = phydev->priv;
	struct qca808x_phy_info *pdata = priv->phy_info;

	if (!pdata) {
		return SW_NOT_FOUND;
	}

	dev_id = pdata->dev_id;
	phy_id = pdata->phy_addr;

	features = SUPPORTED_TP | SUPPORTED_MII |
		SUPPORTED_AUI | SUPPORTED_BNC;

	phy_data = qca808x_phy_reg_read(dev_id,
			phy_id, QCA808X_PHY_STATUS);

	if (phy_data == PHY_INVALID_DATA) {
		return SW_READ_ERROR;
	}

	if (phy_data & QCA808X_STATUS_AUTONEG_CAPS) {
		features |= SUPPORTED_Autoneg;
	}
	if (phy_data & QCA808X_STATUS_100X_FD_CAPS) {
		features |= SUPPORTED_100baseT_Full;
	}
	if (phy_data & QCA808X_STATUS_100X_HD_CAPS) {
		features |= SUPPORTED_100baseT_Half;
	}
	if (phy_data & QCA808X_STATUS_10T_FD_CAPS) {
		features |= SUPPORTED_10baseT_Full;
	}
	if (phy_data & QCA808X_STATUS_10T_HD_CAPS) {
		features |= SUPPORTED_10baseT_Half;
	}

	if (phy_data & QCA808X_STATUS_EXTENDED_STATUS) {
		phy_data = qca808x_phy_reg_read(dev_id,
				phy_id, QCA808X_EXTENDED_STATUS);

		if (phy_data == PHY_INVALID_DATA) {
			return SW_READ_ERROR;
		}
		if (phy_data & QCA808X_STATUS_1000T_FD_CAPS) {
			features |= SUPPORTED_1000baseT_Full;
		}
		if (phy_data & QCA808X_STATUS_1000T_HD_CAPS) {
			features |= SUPPORTED_1000baseT_Half;
		}
	}

	phy_data = qca808x_phy_mmd_read(dev_id, phy_id, QCA808X_PHY_MMD1_NUM,
			QCA808X_MMD1_PMA_CAP_REG);

	if (phy_data & QCA808X_STATUS_2500T_FD_CAPS) {
		features |= SUPPORTED_2500baseX_Full;
	}

	phydev->supported = features;
	phydev->advertising = features;

	return SW_OK;
}

static int qca808x_config_init(struct phy_device *phydev)
{
	int ret = 0;
	a_uint32_t dev_id = 0, phy_id = 0;
	qca808x_priv *priv = phydev->priv;
	const struct qca808x_phy_info *pdata = priv->phy_info;

	if (!pdata) {
		return SW_FAIL;
	}

	dev_id = pdata->dev_id;
	phy_id = pdata->phy_addr;

#if defined(IN_LINUX_STD_PTP)
	/* ptp function initialization */
	ret |= qca808x_ptp_config_init(dev_id, phy_id);
#endif

	ret |= qca808x_phy_config_init(phydev);

	return ret;
}

static int qca808x_config_intr(struct phy_device *phydev)
{
	int err;
	a_uint16_t phy_data;
	a_uint32_t dev_id = 0, phy_id = 0;
	qca808x_priv *priv = phydev->priv;
	const struct qca808x_phy_info *pdata = priv->phy_info;

	if (!pdata) {
		return SW_FAIL;
	}

	dev_id = pdata->dev_id;
	phy_id = pdata->phy_addr;

	phy_data = qca808x_phy_reg_read(dev_id, phy_id,
			QCA808X_PHY_INTR_MASK);

	if (phydev->interrupts == PHY_INTERRUPT_ENABLED) {
		err = qca808x_phy_reg_write(dev_id, phy_id,
				QCA808X_PHY_INTR_MASK,
				phy_data | QCA808X_INTR_INIT);
	} else {
		err = qca808x_phy_reg_write(dev_id, phy_id,
				QCA808X_PHY_INTR_MASK, 0);
	}

	return err;
}

static int qca808x_ack_interrupt(struct phy_device *phydev)
{
	int err;
	a_uint32_t dev_id = 0, phy_id = 0;
	qca808x_priv *priv = phydev->priv;
	const struct qca808x_phy_info *pdata = priv->phy_info;

	if (!pdata) {
		return SW_FAIL;
	}

	dev_id = pdata->dev_id;
	phy_id = pdata->phy_addr;

	err = qca808x_phy_reg_read(dev_id, phy_id,
			QCA808X_PHY_INTR_STATUS);

	return (err < 0) ? err : 0;
}

/* switch linux negtiation capability to fal avariable */
static a_uint32_t qca808x_negtiation_cap_get(a_uint32_t advertise)
{
	a_uint32_t autoneg = 0;

	if (advertise & ADVERTISED_Pause) {
		autoneg |= FAL_PHY_ADV_PAUSE;
	}
	if (advertise & ADVERTISED_Asym_Pause) {
		autoneg |= FAL_PHY_ADV_ASY_PAUSE;
	}
	if (advertise & ADVERTISED_10baseT_Half) {
		autoneg |= FAL_PHY_ADV_10T_HD;
	}
	if (advertise & ADVERTISED_10baseT_Full) {
		autoneg |= FAL_PHY_ADV_10T_FD;
	}
	if (advertise & ADVERTISED_100baseT_Half) {
		autoneg |= FAL_PHY_ADV_100TX_HD;
	}
	if (advertise & ADVERTISE_100FULL) {
		autoneg |= FAL_PHY_ADV_100TX_FD;
	}
	if (advertise & ADVERTISED_1000baseT_Full) {
		autoneg |= FAL_PHY_ADV_1000T_FD;
	}
	if (advertise & ADVERTISED_2500baseX_Full) {
		autoneg |= FAL_PHY_ADV_2500T_FD;
	}

	return autoneg;
}

static int qca808x_config_aneg(struct phy_device *phydev)
{
	a_uint32_t advertise = 0;
	a_uint16_t phy_data = 0;
	int err = 0;
	a_uint32_t dev_id = 0, phy_id = 0;
	qca808x_priv *priv = phydev->priv;
	const struct qca808x_phy_info *pdata = priv->phy_info;

	if (!pdata) {
		return SW_FAIL;
	}

	dev_id = pdata->dev_id;
	phy_id = pdata->phy_addr;
	if (phydev->autoneg != AUTONEG_ENABLE)
	{
		/* force speed */
		phydev->pause = 0;
		phydev->asym_pause = 0;

		phy_data = qca808x_phy_reg_read(dev_id, phy_id, QCA808X_PHY_CONTROL);
		if (phydev->duplex == FAL_FULL_DUPLEX) {
			phy_data |= QCA808X_CTRL_FULL_DUPLEX;
		} else {
			phy_data &= ~QCA808X_CTRL_FULL_DUPLEX;
		}
		qca808x_phy_reg_write(dev_id, phy_id, QCA808X_PHY_CONTROL, phy_data);
		err = qca808x_phy_set_force_speed(dev_id, phy_id, phydev->speed);
	} else {
		/* autoneg enabled */
		advertise = phydev->advertising & phydev->supported;
		advertise = qca808x_negtiation_cap_get(advertise);
		err |= qca808x_phy_set_autoneg_adv(dev_id, phy_id, advertise);
		err |= qca808x_phy_restart_autoneg(dev_id, phy_id);
	}

	return err;
}

static int qca808x_aneg_done(struct phy_device *phydev)
{

	a_uint16_t phy_data;
	a_uint32_t dev_id = 0, phy_id = 0;
	qca808x_priv *priv = phydev->priv;
	const struct qca808x_phy_info *pdata = priv->phy_info;

	if (!pdata) {
		return SW_FAIL;
	}

	dev_id = pdata->dev_id;
	phy_id = pdata->phy_addr;

	phy_data = qca808x_phy_reg_read(dev_id, phy_id,
			QCA808X_PHY_STATUS);

	return (phy_data < 0) ? phy_data : (phy_data & QCA808X_STATUS_AUTO_NEG_DONE);
}

static int qca808x_soft_reset(struct phy_device *phydev)
{
	a_uint32_t dev_id = 0, phy_id = 0;
	qca808x_priv *priv = phydev->priv;
	const struct qca808x_phy_info *pdata = priv->phy_info;

	if (!pdata) {
		return SW_FAIL;
	}

	dev_id = pdata->dev_id;
	phy_id = pdata->phy_addr;

	return qca808x_phy_reset(dev_id, phy_id);
}

static int qca808x_read_status(struct phy_device *phydev)
{
	struct port_phy_status phy_status;
	a_uint32_t dev_id = 0, phy_id = 0;
	qca808x_priv *priv = phydev->priv;
	const struct qca808x_phy_info *pdata = priv->phy_info;

	if (!pdata) {
		return SW_FAIL;
	}

	dev_id = pdata->dev_id;
	phy_id = pdata->phy_addr;

	qca808x_phy_get_status(dev_id, phy_id, &phy_status);

	if (phy_status.link_status) {
		phydev->link = QCA808X_PHY_LINK_UP;
	} else {
		phydev->link = QCA808X_PHY_LINK_DOWN;
	}

	switch (phy_status.speed) {
		case FAL_SPEED_2500:
			phydev->speed = SPEED_2500;
			break;
		case FAL_SPEED_1000:
			phydev->speed = SPEED_1000;
			break;
		case FAL_SPEED_100:
			phydev->speed = SPEED_100;
			break;
		default:
			phydev->speed = SPEED_10;
			break;
	}

	if (phy_status.duplex == FAL_FULL_DUPLEX) {
		phydev->duplex = DUPLEX_FULL;
	} else {
		phydev->duplex = DUPLEX_HALF;
	}

	return 0;
}

static void qca808x_link_change_notify(struct phy_device *phydev)
{
#if defined(IN_LINUX_STD_PTP)
	fal_ptp_time_t ptp_cycle_time = {0};
#endif
	a_uint32_t nanoseconds = 0;
	qca808x_priv *priv = phydev->priv;
	struct qca808x_phy_info *pdata = priv->phy_info;

	if (!pdata) {
		return;
	}

	if (pdata->speed != phydev->speed) {
		if (phydev->speed == SPEED_2500 &&
				pdata->speed < SPEED_2500) {
			/* adjust frequency to 5ns(200MHz) */
			nanoseconds = QCA808X_PTP_TICK_RATE_200M;
		} else if (pdata->speed == SPEED_2500 &&
				phydev->speed < SPEED_2500) {
			/* adjust frequency to 8ns(125MHz) */
			nanoseconds = QCA808X_PTP_TICK_RATE_125M;
		}
		pdata->speed = phydev->speed;
#if defined(IN_LINUX_STD_PTP)
		if (nanoseconds != 0) {
			ptp_cycle_time.nanoseconds = nanoseconds;
			qca808x_phy_ptp_rtc_adjfreq_set(pdata->dev_id,
					pdata->phy_addr, &ptp_cycle_time);
		}
#endif
	}
}

#if defined(IN_LINUX_STD_PTP)
void qca808x_pkt_info_get(struct sk_buff *skb,
		unsigned int type, fal_ptp_pkt_info_t *pkt_info)
{
	a_uint16_t *seqid, seqid_pkt;
	a_uint32_t *clockid;
	a_uint32_t clockid_lo;
	a_uint64_t clockid_pkt;
	a_uint16_t *portid, portid_pkt;
	a_uint8_t *msgtype, msgtype_pkt;
	a_uint32_t offset = 0;
	a_uint8_t *data = skb_mac_header(skb);

#define OFF_PTP_CLOCK_ID 20
#define OFF_PTP_PORT_ID 28
	if (type & PTP_CLASS_VLAN) {
		offset += VLAN_HLEN;
	}

	switch (type & PTP_CLASS_PMASK) {
	case PTP_CLASS_IPV4:
		offset += ETH_HLEN + IPV4_HLEN(data + offset) + UDP_HLEN;
		break;
	case PTP_CLASS_IPV6:
		offset += ETH_HLEN + IP6_HLEN + UDP_HLEN;
		break;
	case PTP_CLASS_L2:
		offset += ETH_HLEN;
		break;
	default:
		return;
	}

	if (skb->len + ETH_HLEN < offset +
			OFF_PTP_SEQUENCE_ID + sizeof(*seqid)) {
		return;
	}

	seqid = (a_uint16_t *)(data + offset + OFF_PTP_SEQUENCE_ID);
	seqid_pkt = ntohs(*seqid);
	clockid  = (a_uint32_t *)(data + offset + OFF_PTP_CLOCK_ID);
	clockid_pkt = ntohl(*clockid);

	clockid  = (a_uint32_t *)(data + offset + OFF_PTP_CLOCK_ID + 4);
	clockid_lo = ntohl(*clockid);
	clockid_pkt =  (clockid_pkt << 32) | clockid_lo;
	portid = (a_uint16_t *)(data + offset + OFF_PTP_PORT_ID);
	portid_pkt = ntohs(*portid);
	msgtype = (a_uint8_t *)(data + offset);
	msgtype_pkt = (*msgtype) & 0xf;

	pkt_info->sequence_id = seqid_pkt;
	pkt_info->clock_identify = clockid_pkt;
	pkt_info->port_number = portid_pkt;
	pkt_info->msg_type = msgtype_pkt;
	return ;
}

static void tx_timestamp_work(struct work_struct *work)
{
	struct sk_buff *skb;
	struct skb_shared_hwtstamps shhwtstamps;
	struct timespec64 ts;
	a_uint64_t ns;
	a_uint32_t dev_id, phy_id;
	qca808x_ptp_cb *ptp_cb;
	const struct qca808x_phy_info *pdata;
	fal_ptp_pkt_info_t pkt_info;
	fal_ptp_time_t tx_time = {0};
	sw_error_t ret = SW_OK;
	qca808x_priv *priv =
		container_of(work, qca808x_priv, tx_ts_work.work);

	pdata = priv->phy_info;

	if (!pdata) {
		return;
	}

	dev_id = pdata->dev_id;
	phy_id = pdata->phy_addr;

	memset(&shhwtstamps, 0, sizeof(shhwtstamps));

	while ((skb = skb_dequeue(&priv->tx_queue))) {
		ptp_cb = (qca808x_ptp_cb *)skb->cb;
		qca808x_pkt_info_get(skb, ptp_cb->ptp_type, &pkt_info);

		ret = qca808x_phy_ptp_timestamp_get(dev_id, phy_id,
				FAL_TX_DIRECTION, &pkt_info, &tx_time);
		if (ret == SW_NOT_FOUND) {
			SSDK_DEBUG("Fail to get tx_ts: sequence_id:%x, clock_identify:%llx,"
					" port_number:%x, msg_type:%x\n",
					pkt_info.sequence_id, pkt_info.clock_identify,
					pkt_info.port_number, pkt_info.msg_type);
		}

		ts.tv_sec = tx_time.seconds;
		ts.tv_nsec = tx_time.nanoseconds;

		ns = timespec64_to_ns(&ts);

		shhwtstamps.hwtstamp = ns_to_ktime(ns);
		skb_complete_tx_timestamp(skb, &shhwtstamps);
	}

	if (!skb_queue_empty(&priv->tx_queue))
		schedule_delayed_work(&priv->tx_ts_work, SKB_TIMESTAMP_TIMEOUT);
}

static void rx_timestamp_work(struct work_struct *work)
{
	struct sk_buff *skb;
	struct skb_shared_hwtstamps *shhwtstamps = NULL;
	struct timespec64 ts;
	a_uint64_t ns;
	a_uint32_t dev_id, phy_id;
	qca808x_ptp_cb *ptp_cb;
	const struct qca808x_phy_info *pdata;
	fal_ptp_pkt_info_t pkt_info;
	fal_ptp_time_t rx_time = {0};
	sw_error_t ret = SW_OK;

	qca808x_priv *priv =
		container_of(work, qca808x_priv, rx_ts_work.work);

	pdata = priv->phy_info;

	if (!pdata) {
		return;
	}
	dev_id = pdata->dev_id;
	phy_id = pdata->phy_addr;

	/* Deliver packets */
	while ((skb = skb_dequeue(&priv->rx_queue))) {
		ptp_cb = (qca808x_ptp_cb *)skb->cb;
		qca808x_pkt_info_get(skb, ptp_cb->ptp_type, &pkt_info);

		ret = qca808x_phy_ptp_timestamp_get(dev_id, phy_id,
				FAL_RX_DIRECTION, &pkt_info, &rx_time);
		if (ret == SW_NOT_FOUND) {
			SSDK_DEBUG("Fail to get rx_ts: sequence_id:%x, clock_identify:%llx, "
					"port_number:%x, msg_type:%x\n",
					pkt_info.sequence_id, pkt_info.clock_identify,
					pkt_info.port_number, pkt_info.msg_type);
		}

		ts.tv_sec = rx_time.seconds;
		ts.tv_nsec = rx_time.nanoseconds;
		ns = timespec64_to_ns(&ts);
		shhwtstamps = skb_hwtstamps(skb);
		memset(shhwtstamps, 0, sizeof(*shhwtstamps));
		shhwtstamps->hwtstamp = ns_to_ktime(ns);

		/* for OC/BC needs record ingress time stamp on receiving
		 * peer delay request message under one-step mode.
		 * for TC needs record ingress time stamp on receiving
		 * the event message */
		if ((pdata->clock_mode == FAL_P2PTC_CLOCK_MODE) ||
				(pdata->clock_mode == FAL_OC_CLOCK_MODE &&
				 pdata->step_mode == FAL_ONE_STEP_MODE &&
				 ptp_cb->pkt_type == QCA808X_PTP_MSG_PREQ)) {
			priv->ptp_in_trig_nsec = ts.tv_nsec;
			priv->ptp_in_trig_flag = A_TRUE;
		}
		netif_rx_ni(skb);
	}

	if (!skb_queue_empty(&priv->rx_queue))
		schedule_delayed_work(&priv->rx_ts_work, SKB_TIMESTAMP_TIMEOUT);
}

static void pdelay_ingress_time_sync(struct phy_device *phydev)
{
	a_uint32_t dev_id, phy_id;
	fal_ptp_time_t ingress_trig_time = {0};
	qca808x_priv *priv = phydev->priv;
	const struct qca808x_phy_info *pdata = priv->phy_info;

	if (!pdata) {
		return;
	}
	dev_id = pdata->dev_id;
	phy_id = pdata->phy_addr;

	if (priv->ptp_in_trig_flag) {
		ingress_trig_time.nanoseconds = priv->ptp_in_trig_nsec;
		qca808x_phy_ptp_pkt_timestamp_set(dev_id, phy_id, &ingress_trig_time);
		priv->ptp_in_trig_flag = A_FALSE;
	}
}

static void qca808x_gps_second_sync(struct phy_device *phydev, a_int32_t *buf)
{
	fal_ptp_time_t time, old_time;
	a_uint32_t dev_id, phy_id;
	qca808x_priv *priv = phydev->priv;
	const struct qca808x_phy_info *pdata = priv->phy_info;

	if (!pdata) {
		return;
	}
	dev_id = pdata->dev_id;
	phy_id = pdata->phy_addr;
	/* 0-3: time of week; 4-5: week number; 6-7: UTC offset */
	time.seconds = ((a_int64_t)buf[0] << 24 | buf[1] << 16 |
			buf[2] << 8 | buf[3]) +
		((buf[4] << 8 | buf[5]) * 7 * 24 * 3600) +
		(buf[6] << 8 | buf[7]);

	time.nanoseconds = 0;
	time.fracnanoseconds = 0;

	qca808x_phy_ptp_rtc_time_get(dev_id, phy_id, &old_time);
	time.seconds -= old_time.seconds;
	qca808x_phy_ptp_rtc_adjtime_set(dev_id, phy_id, &time);

	qca808x_ptp_gm_gps_seconds_sync_enable(dev_id, phy_id, A_FALSE);
	return;
}

static int
gps_seconds_sync_thread(void *param)
{
	struct file *filp;
	a_uint32_t nread;
	char buff[128];
	char *dev ="/dev/ttyMSM0";
	a_int32_t arr[32], akk[32];
	a_uint32_t ii = 0, sign = 0, kk = 0, nn = 0;
	mm_segment_t fs;
	a_int32_t return_tag = 32;

	filp = filp_open(dev, O_RDONLY, 0);
	if (IS_ERR(filp))
	{
		SSDK_ERROR("Open %s error\n", dev);
		return 0;
	}

	memset(arr, 0, sizeof(arr));
	memset(akk, 0, sizeof(akk));
	while(1)
	{
		memset(buff, 0, sizeof(buff));
		fs=get_fs();
		set_fs(KERNEL_DS);
		if ((nread = filp->f_op->read(filp, buff, sizeof(buff), &filp->f_pos)))
		{
			set_fs(fs);
			buff[nread+1]='\0';
			for(ii = 0; ii < sizeof(buff); ii++)
			{
				if (sign == 0 && !(buff[ii] == 0x10 || buff[ii] == 0x8f ||
							buff[ii] == 0xab)) {
					nn = 0;
				} else if (sign == 0) {
					arr[nn++] = buff[ii];
				}

				if (sign == 1) {
					akk[kk++] = buff[ii];
				}

				if (sign == 1 && kk >= 2 && akk[kk-2] == 0x10 && akk[kk-1] == 0x3)
				{
					qca808x_gps_second_sync((struct phy_device *)param, akk);
					goto gps_time_sync_exit;
				}
				if (sign == 0 && nn >= 3 && arr[nn-3] == 0x10 &&
						arr[nn-2] == 0x8f && arr[nn-1] == 0xab) {
					sign = 1;
				}
			}
		}
		else
		{
			set_fs(fs);
			if (--return_tag <= 0) {
				break;
			}
		}
	}

gps_time_sync_exit:
	filp_close(filp,NULL);
	return 0;
}

static void qca808x_ptp_schedule_work(struct work_struct *work)
{
	const char gm_seconds_thread_name[] = "gps_seconds_sync";
	struct task_struct *gps_seconds_sync_task;
	struct phy_device *phydev;

	const struct qca808x_phy_info *pdata;
	qca808x_priv *priv = NULL;
	priv = container_of(work, qca808x_priv, ts_schedule_work.work);

	phydev = priv->phydev;
	pdata = priv->phy_info;

	if (pdata && pdata->gps_seconds_sync_en == A_TRUE) {
		gps_seconds_sync_task = kthread_create(gps_seconds_sync_thread,
				(void *)phydev, gm_seconds_thread_name);
		if (IS_ERR(gps_seconds_sync_task)) {
			SSDK_ERROR("thread: %s create failed\n", gm_seconds_thread_name);
			return;
		}
		wake_up_process(gps_seconds_sync_task);
	}

	pdelay_ingress_time_sync(phydev);
	schedule_delayed_work(&priv->ts_schedule_work, SKB_TIMESTAMP_TIMEOUT);
}

/******************************************************************************
*
* qca808x_ptp_settime - reset the rtc timecounter
*
* ptp: the ptp clock info structure
* ts:  the new rtc timecounter
*
*/
static int qca808x_ptp_settime(struct ptp_clock_info *ptp,
			       const struct timespec64 *ts)
{
	const struct qca808x_phy_info *pdata;
	struct qca808x_ptp_clock *clock =
		container_of(ptp, struct qca808x_ptp_clock, caps);

	fal_ptp_time_t ptp_time = {0};

	qca808x_priv *priv = clock->priv;
	pdata = priv->phy_info;

	if (!pdata) {
		return SW_FAIL;
	}
	ptp_time.seconds = ts->tv_sec;
	ptp_time.nanoseconds = ts->tv_nsec;

	mutex_lock(&clock->tsreg_lock);
	qca808x_phy_ptp_rtc_time_set(pdata->dev_id, pdata->phy_addr, &ptp_time);
	mutex_unlock(&clock->tsreg_lock);
	return 0;
}

/******************************************************************************
*
* qca808x_ptp_gettime - read the rtc timecounter
*
* ptp: the ptp clock info structure
* ts:  the timespace to hold the current rtc time
*
*/
static int qca808x_ptp_gettime(struct ptp_clock_info *ptp,
			       struct timespec64 *ts)
{
	const struct qca808x_phy_info *pdata;
	struct qca808x_ptp_clock *clock =
		container_of(ptp, struct qca808x_ptp_clock, caps);

	fal_ptp_time_t ptp_time = {0};

	qca808x_priv *priv = clock->priv;
	pdata = priv->phy_info;

	if (!pdata) {
		return SW_FAIL;
	}
	mutex_lock(&clock->tsreg_lock);
	qca808x_phy_ptp_rtc_time_get(pdata->dev_id, pdata->phy_addr, &ptp_time);
	mutex_unlock(&clock->tsreg_lock);

	ts->tv_sec = ptp_time.seconds;
	ts->tv_nsec = ptp_time.nanoseconds;
	return 0;
}

/******************************************************************************
*
* qca808x_ptp_adjtime - adjust the rtc timecounter offset
*
* ptp: the ptp clock info structure
* delta:  offset to be adjusted per cycle counter
*
*/
static int qca808x_ptp_adjtime(struct ptp_clock_info *ptp, s64 delta)
{
	struct timespec64 ts;
	const struct qca808x_phy_info *pdata;
	struct qca808x_ptp_clock *clock =
		container_of(ptp, struct qca808x_ptp_clock, caps);

	fal_ptp_time_t ptp_time = {0};

	qca808x_priv *priv = clock->priv;
	pdata = priv->phy_info;

	if (!pdata) {
		return SW_FAIL;
	}
	ts = ns_to_timespec64(delta);
	ptp_time.seconds = ts.tv_sec;
	ptp_time.nanoseconds = ts.tv_nsec;

	mutex_lock(&clock->tsreg_lock);
	qca808x_phy_ptp_rtc_adjtime_set(pdata->dev_id, pdata->phy_addr, &ptp_time);
	mutex_unlock(&clock->tsreg_lock);
	return 0;
}

/******************************************************************************
*
* qca808x_ptp_adjfreq - adjust the frequency of cycle counter
*
* ptp: the ptp clock info structure
* ppb:  parts per billion adjustment from master
*
*/
static int qca808x_ptp_adjfreq(struct ptp_clock_info *ptp, s32 ppb)
{
	a_uint64_t rate;
	a_uint16_t ns, ns_tmp;
	a_int32_t neg_adj = 0, tmp = 0;
	const struct qca808x_phy_info *pdata;
	struct qca808x_ptp_clock *clock =
		container_of(ptp, struct qca808x_ptp_clock, caps);

	fal_ptp_time_t ptp_time = {0};

	qca808x_priv *priv = clock->priv;
	pdata = priv->phy_info;

	if (!pdata) {
		return SW_FAIL;
	}
	if (ppb < 0) {
		neg_adj = 1;
		ppb = -ppb;
	}

	rate = ppb;
	rate <<= 20;
	/* divided by (125000000-ppb/8)/64 */
	if (pdata->speed == FAL_SPEED_2500) {
		tmp = (ppb/5)/64;
		ns_tmp = QCA808X_PTP_TICK_RATE_200M;
		rate = div_u64(rate, 3125000 + tmp);
	} else {
		tmp = (ppb/8)/64;
		ns_tmp = QCA808X_PTP_TICK_RATE_125M;
		rate = div_u64(rate, 1953125 + tmp);
	}

	if(neg_adj) {
		ns = ns_tmp - 1;
		rate = (2<<26)-rate;
	} else {
		ns = ns_tmp;
	}

	ptp_time.nanoseconds = ns;
	ptp_time.fracnanoseconds = rate;

	mutex_lock(&clock->tsreg_lock);
	qca808x_phy_ptp_rtc_adjfreq_set(pdata->dev_id, pdata->phy_addr, &ptp_time);
	mutex_unlock(&clock->tsreg_lock);
	return 0;
}

static int qca808x_ptp_enable(struct ptp_clock_info *ptp,
			      struct ptp_clock_request *rq, int on)
{
	return -EOPNOTSUPP;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4,4,0))
static int qca808x_ptp_verify(struct ptp_clock_info *ptp, unsigned int pin,
			      enum ptp_pin_function func, unsigned int chan)
{
	return 1;
}
#endif

static int qca808x_ptp_register(struct phy_device *phydev)
{
	int err;
	struct qca808x_ptp_clock *clock;
	qca808x_priv *priv = phydev->priv;

	clock = kzalloc(sizeof(struct qca808x_ptp_clock), GFP_KERNEL);
	if (!clock) {
		return -ENOMEM;
	}

	mutex_init(&clock->tsreg_lock);
	clock->caps.owner = THIS_MODULE;
	sprintf(clock->caps.name, "qca808x timer");
	clock->caps.max_adj	= 3124999;
	clock->caps.n_alarm	= 0;
	clock->caps.n_ext_ts	= 6;
	clock->caps.n_per_out	= 7;
	clock->caps.pps		= 0;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4,4,0))
	clock->caps.n_pins	= 0;
	clock->caps.verify	= qca808x_ptp_verify;
	clock->caps.gettime64	= qca808x_ptp_gettime;
	clock->caps.settime64	= qca808x_ptp_settime;
#else
	clock->caps.gettime	= qca808x_ptp_gettime;
	clock->caps.settime	= qca808x_ptp_settime;
#endif
	clock->caps.adjfreq	= qca808x_ptp_adjfreq;
	clock->caps.adjtime	= qca808x_ptp_adjtime;
	clock->caps.enable	= qca808x_ptp_enable;

	clock->ptp_clock = ptp_clock_register(&clock->caps, &phydev->dev);
	if (IS_ERR(clock->ptp_clock)) {
		err = PTR_ERR(clock->ptp_clock);
		kfree(clock);
		return err;
	}
	priv->clock = clock;
	clock->priv = priv;

	SSDK_INFO("qca808x ptp clock registered\n");
	return 0;
}

static void qca808x_ptp_unregister(struct phy_device *phydev)
{
	qca808x_priv *priv = phydev->priv;
	struct qca808x_ptp_clock *clock = priv->clock;

	if (clock) {
		ptp_clock_unregister(clock->ptp_clock);
		mutex_destroy(&clock->tsreg_lock);
		kfree(clock);
	}
}

static int qca808x_hwtstamp(struct phy_device *phydev, struct ifreq *ifr)
{
	struct hwtstamp_config cfg;
	if (copy_from_user(&cfg, ifr->ifr_data, sizeof(cfg)))
		return -EFAULT;
	if (cfg.flags) /* reserved for future extensions */
		return -EINVAL;

	if (cfg.tx_type < 0 || cfg.tx_type > HWTSTAMP_TX_ONESTEP_SYNC)
		return -ERANGE;
	return copy_to_user(ifr->ifr_data, &cfg, sizeof(cfg)) ? -EFAULT : 0;
}

static bool qca808x_rxtstamp(struct phy_device *phydev,
			     struct sk_buff *skb, int type)
{
	struct skb_shared_hwtstamps *shhwtstamps = NULL;
	struct timespec64 ts = {0};
	unsigned int offset = 0;
	a_uint64_t ns;
	a_uint32_t *reserved2;
	a_uint8_t *reserved0, *reserved1;
	a_uint8_t *msg_type;
	a_uint32_t *cf1, *cf2;
	a_uint8_t *data;
	a_uint8_t embed_val, pkt_type;
	qca808x_ptp_cb *ptp_cb = (qca808x_ptp_cb *)skb->cb;
	qca808x_priv *priv = phydev->priv;
	const struct qca808x_phy_info *pdata = priv->phy_info;

	if (!pdata) {
		return false;
	}
	shhwtstamps = skb_hwtstamps(skb);
	memset(shhwtstamps, 0, sizeof(*shhwtstamps));

	data = skb_mac_header(skb);
	if (type & PTP_CLASS_VLAN) {
		offset += VLAN_HLEN;
	}

	switch (type & PTP_CLASS_PMASK) {
	case PTP_CLASS_IPV4:
		offset += ETH_HLEN + IPV4_HLEN(data + offset) + UDP_HLEN;
		break;
	case PTP_CLASS_IPV6:
		offset += ETH_HLEN + IP6_HLEN + UDP_HLEN;
		break;
	case PTP_CLASS_L2:
		offset += ETH_HLEN;
		break;
	default:
		return false;
	}

#define PTP_HDR_RESERVED0_OFFSET	1
#define PTP_HDR_RESERVED1_OFFSET	5
#define PTP_HDR_CORRECTIONFIELD_OFFSET	8
#define PTP_HDR_RESERVED2_OFFSET	16

	reserved0 = data + offset + PTP_HDR_RESERVED0_OFFSET;
	msg_type = (a_uint8_t *)(data + offset);
	reserved1 = data + offset + PTP_HDR_RESERVED1_OFFSET;
	cf1 = (a_uint32_t *)(data + offset + PTP_HDR_CORRECTIONFIELD_OFFSET);
	cf2 = (a_uint32_t *)(data + offset + PTP_HDR_CORRECTIONFIELD_OFFSET + 4);
	reserved2 = (a_uint32_t *)(data + offset + PTP_HDR_RESERVED2_OFFSET);

	embed_val = (*reserved0 & 0xf0) >> 4;
	pkt_type = *msg_type & 0xf;

	if (embed_val == QCA808X_PTP_EMBEDDED_MODE) {
		ts.tv_sec = ntohl(*reserved2);
		ts.tv_nsec = ((a_uint32_t)*reserved1 << 24) | (ntohl(*cf1) >> 8);

		/* restore the original correctionfield value except for
		 * the TC one-step mode */
		if (!(pdata->clock_mode == FAL_P2PTC_CLOCK_MODE &&
					pdata->step_mode == FAL_ONE_STEP_MODE))
		{
			if (((ntohl(*cf1) >> 7) & 0x1) == 1) {
				*cf1 = ((a_uint32_t)0xff << 24) |
					((ntohl(*cf1) & 0xff) << 16) | (ntohl(*cf2) >> 16);
			} else {
				*cf1 = ((ntohl(*cf1) & 0xff) << 16) | (ntohl(*cf2) >> 16);
			}

			*cf1 = htonl(*cf1);
			*cf2 = (ntohl(*cf2) & 0xffff) << 16;
			*cf2 = htonl(*cf2);
		}
	} else {
		ptp_cb->ptp_type = type;
		ptp_cb->pkt_type = pkt_type;
		skb_queue_tail(&priv->rx_queue, skb);
		schedule_delayed_work(&priv->rx_ts_work, 0);
		return true;
	}
	ns = timespec64_to_ns(&ts);

	/* for OC/BC needs record ingress time stamp on receiving
	 * peer delay request message under one-step mode.
	 * for TC needs record ingress time stamp on receiving
	 * the event message */
	if ((pdata->clock_mode == FAL_P2PTC_CLOCK_MODE) ||
			(pdata->clock_mode == FAL_OC_CLOCK_MODE &&
			 pdata->step_mode == FAL_ONE_STEP_MODE &&
			 pkt_type == QCA808X_PTP_MSG_PREQ)) {
		priv->ptp_in_trig_nsec = ts.tv_nsec;
		priv->ptp_in_trig_flag = A_TRUE;
	}

	shhwtstamps->hwtstamp = ns_to_ktime(ns);
	netif_rx_ni(skb);
	return true;
}


static void qca808x_txtstamp(struct phy_device *phydev,
			     struct sk_buff *skb, int type)
{
	qca808x_priv *priv = phydev->priv;
	qca808x_ptp_cb *ptp_cb = (qca808x_ptp_cb *)skb->cb;

	skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
	skb_queue_tail(&priv->tx_queue, skb);
	ptp_cb->ptp_type = type;
	schedule_delayed_work(&priv->tx_ts_work, SKB_TIMESTAMP_TIMEOUT);
}

static int qca808x_ts_info(struct phy_device *phydev,
		struct ethtool_ts_info *info)
{
	qca808x_priv *priv = phydev->priv;
	const struct qca808x_phy_info *pdata = priv->phy_info;

	if (!pdata) {
		return 0;
	}
	info->so_timestamping =
		SOF_TIMESTAMPING_TX_HARDWARE |
		SOF_TIMESTAMPING_RX_HARDWARE |
		SOF_TIMESTAMPING_RAW_HARDWARE;
	info->tx_types =
		(1 << HWTSTAMP_TX_OFF) |
		(1 << HWTSTAMP_TX_ON);

	if (pdata->step_mode == FAL_ONE_STEP_MODE) {
		info->tx_types |= (1 << HWTSTAMP_TX_ONESTEP_SYNC);
	}

	info->rx_filters =
		(1 << HWTSTAMP_FILTER_NONE) |
		(1 << HWTSTAMP_FILTER_PTP_V1_L4_EVENT) |
		(1 << HWTSTAMP_FILTER_PTP_V2_L4_EVENT) |
		(1 << HWTSTAMP_FILTER_PTP_V2_L2_EVENT) |
		(1 << HWTSTAMP_FILTER_PTP_V2_EVENT);

	return 0;
}
#endif

static int qca808x_phy_probe(struct phy_device *phydev)
{
	qca808x_priv *priv;
	int err = 0;

	priv = kzalloc(sizeof(qca808x_priv), GFP_KERNEL);
	if (!priv) {
		return -ENOMEM;
	}

	priv->phydev = phydev;
	priv->phy_info = qca808x_phy_info_get(phydev->addr);
	phydev->priv = priv;

#if defined(IN_LINUX_STD_PTP)
	INIT_DELAYED_WORK(&priv->tx_ts_work, tx_timestamp_work);
	INIT_DELAYED_WORK(&priv->rx_ts_work, rx_timestamp_work);
	skb_queue_head_init(&priv->tx_queue);
	skb_queue_head_init(&priv->rx_queue);

	err = qca808x_ptp_register(phydev);
	if (err <0) {
		SSDK_ERROR("qca808x ptp clock register failed\n");
		kfree(priv);
		return err;
	}

	INIT_DELAYED_WORK(&priv->ts_schedule_work, qca808x_ptp_schedule_work);
	schedule_delayed_work(&priv->ts_schedule_work, SKB_TIMESTAMP_TIMEOUT);
#endif

	return err;
}

static void qca808x_phy_remove(struct phy_device *phydev)
{
	qca808x_priv *priv = phydev->priv;

#if defined(IN_LINUX_STD_PTP)
	cancel_delayed_work_sync(&priv->tx_ts_work);
	cancel_delayed_work_sync(&priv->rx_ts_work);
	cancel_delayed_work_sync(&priv->ts_schedule_work);
	skb_queue_purge(&priv->tx_queue);
	skb_queue_purge(&priv->rx_queue);

	qca808x_ptp_unregister(phydev);
#endif
	kfree(priv);
}

struct phy_driver qca808x_phy_driver = {
	.phy_id		= QCA8081_PHY,
	.phy_id_mask    = 0xfffffff0,
	.name		= "QCA808X ethernet",
	.features	= PHY_GBIT_FEATURES,
	.flags		= PHY_HAS_INTERRUPT,
	.probe		= qca808x_phy_probe,
	.remove		= qca808x_phy_remove,
	.config_init	= qca808x_config_init,
	.config_intr	= qca808x_config_intr,
	.config_aneg	= qca808x_config_aneg,
	.aneg_done	= qca808x_aneg_done,
	.soft_reset	= qca808x_soft_reset,
	.ack_interrupt	= qca808x_ack_interrupt,
	.read_status	= qca808x_read_status,
	.match_phy_device       = qca808x_match_phy_device,
	.link_change_notify     = qca808x_link_change_notify,
#if defined(IN_LINUX_STD_PTP)
	.ts_info	= qca808x_ts_info,
	.hwtstamp	= qca808x_hwtstamp,
	.rxtstamp	= qca808x_rxtstamp,
	.txtstamp	= qca808x_txtstamp,
#endif
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4,9,0))
	.mdiodrv.driver		= { .owner = THIS_MODULE },
#else
	.driver		= { .owner = THIS_MODULE },
#endif
};

a_int32_t qca808x_phy_driver_register(void)
{
	a_int32_t ret;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4,9,0))
	ret = phy_driver_register(&qca808x_phy_driver, THIS_MODULE);
#else
	ret = phy_driver_register(&qca808x_phy_driver);
#endif
	return ret;
}

void qca808x_phy_driver_unregister(void)
{
	phy_driver_unregister(&qca808x_phy_driver);
}

void qca808x_phydev_init(a_uint32_t dev_id, a_uint32_t port_id)
{
	struct qca808x_phy_info *pdata;
	pdata = kzalloc(sizeof(struct qca808x_phy_info), GFP_KERNEL);

	if (!pdata) {
		return;
	}
	list_add_tail(&pdata->list, &g_qca808x_phy_list);
	pdata->dev_id = dev_id;
	/* the phy address may be the i2c slave addr or mdio addr */
	pdata->phy_addr = qca_ssdk_port_to_phy_addr(dev_id, port_id);
	pdata->phydev_addr = pdata->phy_addr;
#if defined(IN_PHY_I2C_MODE)
	/* in i2c mode, need to register a fake phy device
	 * before the phy driver register */
	if (hsl_port_phy_access_type_get(dev_id, port_id) == PHY_I2C_ACCESS)
	{
		pdata->phydev_addr = qca_ssdk_port_to_phy_mdio_fake_addr(dev_id, port_id);
		sfp_phy_device_setup(dev_id, port_id, QCA8081_PHY);
	}
#endif
}

void qca808x_phydev_deinit(a_uint32_t dev_id, a_uint32_t port_id)
{
	struct qca808x_phy_info *pdata;

#if defined(IN_PHY_I2C_MODE)
	/* in i2c mode, need to remove the fake phy device
	 * after the phy driver unregistered */
	if (hsl_port_phy_access_type_get(dev_id, port_id) == PHY_I2C_ACCESS) {
		sfp_phy_device_remove(dev_id, port_id);
	}
#endif
	list_for_each_entry(pdata, &g_qca808x_phy_list, list) {
		list_del(&pdata->list);
		kfree(pdata);
	}
}
