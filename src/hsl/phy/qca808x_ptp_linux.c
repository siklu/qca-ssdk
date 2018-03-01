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

#include <linux/mdio.h>
#include <linux/ethtool.h>
#include <linux/if_vlan.h>
#include <linux/phy.h>
#include <linux/net_tstamp.h>
#include <linux/ptp_classify.h>
#include <linux/ptp_clock_kernel.h>
#include <linux/kthread.h>

#define PTP_DEV_ID	0
#define QCA8081_PHY 0x004DD011
#define PHY_QCA808X_FEATURES	(SUPPORTED_10000baseT_Full | \
				 SUPPORTED_1000baseT_Full | \
				 SUPPORTED_100baseT_Full | \
				 PHY_DEFAULT_FEATURES)

static struct task_struct *gps_seconds_sync_task;
struct sk_buff_head qca808x_tx_queue;
struct delayed_work qca808x_ts_work;
struct delayed_work qca808x_gm_seconds_work, qca808x_gm_nanoseconds_swpll_work;
unsigned int ptp_type;
struct phy_device *phy_dev;
u32 phy_addr, gps_seconds_sync_en;

/* used for recording skb PTP header messages */
typedef struct {
	u16 sequence_id;
	u64 clock_identify;
	u16 port_number;
	u8 msg_type;
} ptp_pkt_info;

typedef enum {
	RX_DIRECTION = 0,
	TX_DIRECTION
} ptp_direction;

typedef struct{
        s64 seconds;
        s32 nanoseconds;
        s32 fracnanoseconds;
} ptp_time;

static int qca808x_match_phy_device(struct phy_device *phydev)
{
	if(phydev->phy_id == QCA8081_PHY)
		return 1;
	return 0;
}

static int qca808x_soft_reset(struct phy_device *phydev)
{
	return 0;
}

static int qca808x_config_init(struct phy_device *phydev)
{
	u16 val;
	phy_addr = phydev->addr;
	phy_dev = kzalloc(sizeof (struct phy_device), GFP_KERNEL);
	phy_dev = phydev;
	if(phydev->phy_id != QCA8081_PHY)
		return genphy_config_init(phydev);

	/* enable 1588 */
	val = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8012);
	val &= (~(1<<3));
	val &= (~(1<<8));
	phy_write_mmd(phydev, MDIO_MMD_PCS, 0x8012, val);

	/* use OC/BC two-step clock */
	val = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8012);
	val &= (~(1<<1));
	val &= (~(1<<2));
	phy_write_mmd(phydev, MDIO_MMD_PCS, 0x8012, val);

	/* adjust frequency to 8ns(125MHz) */
	phy_write_mmd(phydev, MDIO_MMD_PCS, 0x8036, 0x2000);
	phy_write_mmd(phydev, MDIO_MMD_PCS, 0x8037, 0);

	/* use SyncE reference clock */
	val = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8012);
	val |= (1<<7);
	phy_write_mmd(phydev, MDIO_MMD_PCS, 0x8012, val);
	val = phy_read_mmd(phydev, MDIO_MMD_AN, 0x8017);
	val &= (~(1<<11));
	phy_write_mmd(phydev, MDIO_MMD_AN, 0x8017, val);

	/* use Embed mode to get RX timestamp */
	val = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8012);
	val &= (~(1<<4));
	phy_write_mmd(phydev, MDIO_MMD_PCS, 0x8012, val);
	val = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x80f0);
	val |= (1<<13);
	phy_write_mmd(phydev, MDIO_MMD_PCS, 0x80f0, val);

	phydev->speed = SPEED_UNKNOWN;
	phydev->link = PHY_NOLINK;
	phydev->duplex = DUPLEX_FULL;
	phydev->autoneg = AUTONEG_ENABLE;
	phydev->supported = PHY_QCA808X_FEATURES;
	phydev->advertising = ADVERTISED_10000baseT_Full |
				ADVERTISED_1000baseT_Full |
				ADVERTISED_100baseT_Full;
	return 0;
}

int qca808x_config_aneg(struct phy_device *phydev)
{
	int reg, err;
	if(phydev->phy_id != QCA8081_PHY)
		return genphy_config_aneg(phydev);

	reg = phy_read_mmd(phydev, MDIO_MMD_AN, MII_BMCR);

	err = phy_write_mmd(phydev, MDIO_MMD_AN, MII_BMCR,
			    reg | 0x1000);
	if (err < 0)
		return err;

	return 0;
}

int qca808x_aneg_done(struct phy_device *phydev)
{
	int reg;
	if(phydev->phy_id != QCA8081_PHY)
		return genphy_aneg_done(phydev);

	reg = phy_read_mmd(phydev, MDIO_MMD_AN, MDIO_STAT1);
	return (reg < 0) ? reg : (reg & BMSR_ANEGCOMPLETE);
}

static int qca808x_config_intr(struct phy_device *phydev)
{
	return 0;
}

static int qca808x_ack_interrupt(struct phy_device *phydev)
{
	return 0;
}

int qca808x_read_status(struct phy_device *phydev)
{
	int value;
	if(phydev->phy_id != QCA8081_PHY)
		return genphy_read_status(phydev);

	value = phy_read(phydev, 17);
	if (value & 0x0400) {
		phydev->link = 1;
	} else {
		phydev->link = 0;
	}
	phydev->speed = SPEED_1000;
	phydev->duplex = DUPLEX_FULL;

	return 0;
}

int qca808x_update_link(struct phy_device *phydev)
{
	int reg;
	reg = phy_read(phydev, 17);
	if (reg & 0x0400)
		phydev->link = 1;
	else
		phydev->link = 0;

	return 0;
}

#define SKB_TIMESTAMP_TIMEOUT	2 /* jiffies */

struct phy_device qca808x_phydev;
#define OFF_PTP_CLOCK_ID 20
#define OFF_PTP_PORT_ID 28
void qca808x_get_pkt_info(struct sk_buff *skb, unsigned int type, ptp_pkt_info *pkt_info)
{
	u16 *seqid, seqid_pkt;
	u64 *clockid, clockid_pkt;
	u16 *portid, portid_pkt;
	u8 *msgtype, msgtype_pkt;
	unsigned int offset = 0;
	u8 *data = skb_mac_header(skb);

	/* check sequenceID, messageType, 12 bit hash of offset 20-29 */

	if (type & PTP_CLASS_VLAN)
		offset += VLAN_HLEN;

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

	if (skb->len + ETH_HLEN < offset + OFF_PTP_SEQUENCE_ID + sizeof(*seqid))
		return;

	seqid = (u16 *)(data + offset + OFF_PTP_SEQUENCE_ID);
	seqid_pkt = ntohs(*seqid);
	clockid  = (u64 *)(data + offset + OFF_PTP_CLOCK_ID);
	clockid_pkt = ntohs(*clockid);
	portid = (u16 *)(data + offset + OFF_PTP_PORT_ID);
	portid_pkt = ntohs(*portid);
	msgtype = (u8 *)(data + offset);
	msgtype_pkt = ntohs(*clockid) & 0xf;

	pkt_info->sequence_id = seqid_pkt;
	pkt_info->clock_identify = clockid_pkt;
	pkt_info->port_number = portid_pkt;
	pkt_info->msg_type = msgtype_pkt;
	return ;
}

int
qca808x_ptp_timestamp_get(ptp_direction direction,
		ptp_pkt_info *pkt_info, ptp_time *time)
{
	u16 seqid0, seqid1, seqid2, seqid3;
	u16 portid0, portid1, portid2, portid3, portid4;
	u16 ts0, ts1, ts2, ts3, ts4, ts5, ts6;
	u64 clock_id;
	u16 port_num;
	u8 msgtype;
	struct phy_device *phydev = phy_dev;
	portid0 = portid1 = portid2 = portid3 = portid4 = 0;
	ts0 = ts1 = ts2 = ts3 = ts4 = ts5 = ts6 = 0;

	if (direction == RX_DIRECTION)
	{
		seqid0 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8013);
		seqid1 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8500);
		seqid2 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x851a);
		seqid3 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8534);

		if (pkt_info->sequence_id == seqid0)
		{
			portid0 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8014);
			portid1 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8015);
			portid2 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8016);
			portid3 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8017);
			portid4 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8018);
			ts0 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8019);
			ts1 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x801a);
			ts2 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x801b);
			ts3 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x801c);
			ts4 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x801d);
			ts5 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x801e);
			ts6 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x801f);
		}
		else if (pkt_info->sequence_id == seqid1)
		{
			portid0 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8501);
			portid1 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8502);
			portid2 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8503);
			portid3 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8504);
			portid4 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8505);
			ts0 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8506);
			ts1 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8507);
			ts2 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8508);
			ts3 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8509);
			ts4 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x850a);
			ts5 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x850b);
			ts6 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x850c);
		}
		else if (pkt_info->sequence_id == seqid2)
		{
			portid0 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x851b);
			portid1 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x851c);
			portid2 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x851d);
			portid3 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x851e);
			portid4 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x851f);
			ts0 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8520);
			ts1 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8521);
			ts2 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8522);
			ts3 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8523);
			ts4 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8524);
			ts5 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8525);
			ts6 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8526);
		}
		else if (pkt_info->sequence_id == seqid3)
		{
			portid0 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8535);
			portid1 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8536);
			portid2 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8537);
			portid3 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8538);
			portid4 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8539);
			ts0 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x853a);
			ts1 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x853b);
			ts2 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x853c);
			ts3 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x853d);
			ts4 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x853e);
			ts5 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x853f);
			ts6 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8540);
		}
	}
	else
	{
		seqid0 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8020);

		if (pkt_info->sequence_id == seqid0)
		{
			portid0 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8021);
			portid1 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8022);
			portid2 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8023);
			portid3 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8024);
			portid4 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8025);
			ts0 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8026);
			ts1 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8027);
			ts2 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8028);
			ts3 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8029);
			ts4 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x802a);
			ts5 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x802b);
			ts6 = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x802c);
		}
	}

	clock_id = ((u64)portid0 << 48) | ((u64)portid1 << 32) |
		((u64)portid2 << 16) | portid3;
	port_num = portid4;
	msgtype = ts5 >> 12;
	if (pkt_info->clock_identify == clock_id && pkt_info->port_number == port_num &&
		pkt_info->msg_type == msgtype)
	{
		time->seconds = ((s64)ts0 << 32) | ((s64)ts1 << 16) | ts2;
		time->nanoseconds = ((s32)ts3 << 16) | ts4;
		time->fracnanoseconds = ((s32)((ts5 & 0xfff) << 8)) | ts6;

		return 0;
	}

	return -1;
}

static void tx_timestamp_work(struct work_struct *work)
{
	struct sk_buff *skb;
	ptp_pkt_info pkt_info;
	ptp_time tx_time;
	struct skb_shared_hwtstamps shhwtstamps;
	struct timespec64 ts;
	u64 ns;
	memset(&shhwtstamps, 0, sizeof(shhwtstamps));

	while ((skb = skb_dequeue(&qca808x_tx_queue))) {
		qca808x_get_pkt_info(skb, ptp_type, &pkt_info);

		qca808x_ptp_timestamp_get(TX_DIRECTION, &pkt_info, &tx_time);
		ts.tv_sec = tx_time.seconds;
		ts.tv_nsec = tx_time.nanoseconds;

		ns = timespec64_to_ns(&ts);

		shhwtstamps.hwtstamp = ns_to_ktime(ns);
		skb_complete_tx_timestamp(skb, &shhwtstamps);
		return;
	}
	schedule_delayed_work(&qca808x_ts_work, SKB_TIMESTAMP_TIMEOUT);
}

static void qca808x_gps_second_sync(int *buf)
{
	ptp_time time;
	int val;

	/* 0-3: time of week; 4-5: week number; 6-7: UTC offset */
	time.seconds = ((s64)buf[0] << 24 | buf[1] << 16 | buf[2] << 8 | buf[3]) *
		(buf[4] << 8 | buf[5]) + (buf[6] << 8 | buf[7]);
	time.nanoseconds = 0;
	time.fracnanoseconds = 0;

	phy_write_mmd(&qca808x_phydev,
			3, 0x803c, time.seconds & 0xffff);
	phy_write_mmd(&qca808x_phydev,
			3, 0x803b, (time.seconds>>16) & 0xffff);
	phy_write_mmd(&qca808x_phydev,
			3, 0x803a, (time.seconds>>32) & 0xffff);

	phy_write_mmd(&qca808x_phydev, 3, 0x8039, 0);
	phy_write_mmd(&qca808x_phydev, 3, 0x8038, 0);

	val = phy_read_mmd(&qca808x_phydev, 3, 0x8044);
	val |= 0x1;
	phy_write_mmd(&qca808x_phydev, 3, 0x8044, val);

	return;
}

static int
gps_seconds_sync_thread(void *param)
{
	struct file *filp;
	int nread;
	char buff[128];
	char *dev ="/dev/ttyMSM0";
	int arr[32], akk[32];
	int ii = 0, sign = 0, kk = 0, nn = 0;
	mm_segment_t fs;
	int return_tag = 32;

	filp = filp_open(dev, O_RDONLY, 0);
	if (IS_ERR(filp))
	{
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
				if (sign == 0 && !(buff[ii] == 0x10 ||
							buff[ii] == 0x8f || buff[ii] == 0xab))
					nn = 0;
				else if (sign == 0)
					arr[nn++] = buff[ii];

				if (sign == 1)
					akk[kk++] = buff[ii];
				if (sign == 1 && kk >= 2 && akk[kk-2] == 0x10 && akk[kk-1] == 0x3)
				{
					qca808x_gps_second_sync(akk);
					goto end;
				}
				if (sign == 0 && nn >= 3 && arr[nn-3] == 0x10 &&
						arr[nn-2] == 0x8f && arr[nn-1] == 0xab)
				{
					sign = 1;
				}
			}
		}
		else
		{
			set_fs(fs);
			if (--return_tag <= 0)
				break;
		}
	}
end:
	filp_close(filp,NULL);
	return 0;
}

void qca808x_ptp_gm_gps_seconds_sync_enable(int en)
{
	gps_seconds_sync_en = en;
}

int qca808x_ptp_gm_gps_seconds_sync_status_get(void)
{
	return gps_seconds_sync_en;
}

static void grandmaster_seconds_work_process(struct work_struct *work)
{
	const char gm_seconds_thread_name[] = "gps_seconds_sync";

	if (gps_seconds_sync_en == 1)
	{
		gps_seconds_sync_task = kthread_create(gps_seconds_sync_thread,
				NULL, gm_seconds_thread_name);

		if (IS_ERR(gps_seconds_sync_task))
		{
			return;
		}

		wake_up_process(gps_seconds_sync_task);

	}
	else
	{
		schedule_delayed_work(&qca808x_gm_seconds_work, SKB_TIMESTAMP_TIMEOUT);
	}
}

static void grandmaster_nanoseconds_swpll_work_process(struct work_struct *work)
{
	return ;
}

static int qca808x_ptp_settime(struct ptp_clock_info *ptp,
			       const struct timespec64 *ts)
{
	int val;

	phy_write_mmd(&qca808x_phydev, 3, 0x8103, ts->tv_sec&0xffff);
	phy_write_mmd(&qca808x_phydev, 3, 0x8102, (ts->tv_sec>>16)&0xffff);
	phy_write_mmd(&qca808x_phydev, 3, 0x8101, (ts->tv_sec>>32)&0xffff);
	phy_write_mmd(&qca808x_phydev, 3, 0x8105, (ts->tv_nsec)&0xffff);
	phy_write_mmd(&qca808x_phydev, 3, 0x8104, (ts->tv_nsec>>16)&0xffff);

	val = phy_read_mmd(&qca808x_phydev, 3, 0x8100);
	val |= 0x1;
	phy_write_mmd(&qca808x_phydev, 3, 0x8100, val);
	return 0;
}

static int qca808x_ptp_gettime(struct ptp_clock_info *ptp,
			       struct timespec64 *ts)
{
	ts->tv_sec = phy_read_mmd(&qca808x_phydev, 3, 0x803d);
	ts->tv_sec = (ts->tv_sec)<<16;
	ts->tv_sec |= phy_read_mmd(&qca808x_phydev, 3, 0x803e);
	ts->tv_sec = (ts->tv_sec)<<16;
	ts->tv_sec |= phy_read_mmd(&qca808x_phydev, 3, 0x803f);

	ts->tv_nsec = phy_read_mmd(&qca808x_phydev, 3, 0x8040);
	ts->tv_nsec = (ts->tv_nsec)<<16;
	ts->tv_nsec |= phy_read_mmd(&qca808x_phydev, 3, 0x8041);

	return 0;
}
static int qca808x_ptp_adjtime(struct ptp_clock_info *ptp, s64 delta)
{
	struct timespec64 ts;
	int val;


	ts = ns_to_timespec64(delta);

	phy_write_mmd(&qca808x_phydev, 3, 0x803c, ts.tv_sec&0xffff);
	phy_write_mmd(&qca808x_phydev, 3, 0x803b, (ts.tv_sec>>16)&0xffff);
	phy_write_mmd(&qca808x_phydev, 3, 0x803a, (ts.tv_sec>>32)&0xffff);

	phy_write_mmd(&qca808x_phydev, 3, 0x8039, (ts.tv_nsec)&0xffff);
	phy_write_mmd(&qca808x_phydev, 3, 0x8038, (ts.tv_nsec>>16)&0xffff);

	val = phy_read_mmd(&qca808x_phydev, 3, 0x8044);
	val |= 0x1;
	phy_write_mmd(&qca808x_phydev, 3, 0x8044, val);
	return 0;
}
#include <linux/math64.h>
static int qca808x_ptp_adjfreq(struct ptp_clock_info *ptp, s32 ppb)
{
	u64 rate;
	int neg_adj = 0;
	u16 hi, lo, ns, val;

	if (ppb < 0) {
		neg_adj = 1;
		ppb = -ppb;
	}
	rate = ppb;
#if 1
	rate <<= 20;
	rate = div_u64(rate, 1953125);
#else
	rate <<= 20;
	rate = div_u64(rate, (125000000-ppb/8)/64);
#endif

	if(neg_adj)
	{
		ns = 7;
		rate = (2<<26)-rate;
	}
	else
	{
		ns = 8;
	}

	hi = (rate >> 16) & 0x3ff;
	lo = rate & 0xffff;
	phy_write_mmd(&qca808x_phydev, MDIO_MMD_PCS, 0x8037, lo);
	val = (ns<<10)|hi;
	phy_write_mmd(&qca808x_phydev, MDIO_MMD_PCS, 0x8036, val);

	return 0;
}

static int qca808x_ptp_enable(struct ptp_clock_info *ptp,
			      struct ptp_clock_request *rq, int on)
{
	return -EOPNOTSUPP;
}

static int qca808x_ptp_verify(struct ptp_clock_info *ptp, unsigned int pin,
			      enum ptp_pin_function func, unsigned int chan)
{
	return 1;
}


struct ptp_clock *qca808x_ptp_clock;
static int qca808x_ptp_register(struct phy_device *phydev)
{
	int err;
	static struct ptp_clock_info caps;

	caps.max_adj	= 1953124;
	caps.n_alarm	= 0;
	caps.n_ext_ts	= 6;
	caps.n_per_out	= 7;
	caps.n_pins	= 0;
	caps.pps		= 0;
	caps.adjfreq	= qca808x_ptp_adjfreq;
	caps.adjtime	= qca808x_ptp_adjtime;
	caps.gettime64	= qca808x_ptp_gettime;
	caps.settime64	= qca808x_ptp_settime;
	caps.enable	= qca808x_ptp_enable;
	caps.verify	= qca808x_ptp_verify;

	qca808x_ptp_clock = ptp_clock_register(&caps, &phydev->dev);
	if (IS_ERR(qca808x_ptp_clock)) {
		err = PTR_ERR(qca808x_ptp_clock);
		return err;
	}
	return 0;
}
/* PHY driver probe function */

static int qca808x_phy_probe(struct phy_device *phydev)
{
	if(phydev->phy_id != QCA8081_PHY)
		return 0;
	memcpy(&qca808x_phydev, phydev, sizeof(*phydev));
	qca808x_ptp_register(phydev);
	skb_queue_head_init(&qca808x_tx_queue);
	INIT_DELAYED_WORK(&qca808x_ts_work, tx_timestamp_work);
	INIT_DELAYED_WORK(&qca808x_gm_seconds_work, grandmaster_seconds_work_process);
	INIT_DELAYED_WORK(&qca808x_gm_nanoseconds_swpll_work,
			grandmaster_nanoseconds_swpll_work_process);

	schedule_delayed_work(&qca808x_gm_seconds_work, SKB_TIMESTAMP_TIMEOUT);
	schedule_delayed_work(&qca808x_gm_nanoseconds_swpll_work, SKB_TIMESTAMP_TIMEOUT);
	return 0;
}

static void qca808x_phy_remove(struct phy_device *phydev)
{
	if(phydev->phy_id != QCA8081_PHY)
		return;
	skb_queue_purge(&qca808x_tx_queue);
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
	struct timespec64 ts;
	unsigned int offset = 0;
	u64 ns;
	u32 *reserved2;
	u8 *reserved0, *reserved1;
	u32 *cf1, *cf2;
	u16 *seqid;
	u8 *data;
	ptp_pkt_info pkt_info;
	ptp_time tx_time;

	shhwtstamps = skb_hwtstamps(skb);
	memset(shhwtstamps, 0, sizeof(*shhwtstamps));

	data = skb_mac_header(skb);
	if (type & PTP_CLASS_VLAN)
		offset += VLAN_HLEN;

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
	reserved1 = data + offset + PTP_HDR_RESERVED1_OFFSET;
	cf1 = (u32 *)(data + offset + PTP_HDR_CORRECTIONFIELD_OFFSET);
	cf2 = (u32 *)(data + offset + PTP_HDR_CORRECTIONFIELD_OFFSET + 4);
	reserved2 = (u32 *)(data + offset + PTP_HDR_RESERVED2_OFFSET);
	seqid = (u16 *)(data + offset + OFF_PTP_SEQUENCE_ID);

	/* check FAL_RX_TS_EMBED or FAL_RX_TS_MDIO */
	if ((*reserved0 >> 4) == 0xa)
	{
		/* RX timestamp embed mode, FAL_RX_TS_EMBED */
		ts.tv_sec = ntohl(*reserved2);
		ts.tv_nsec = ((u32)*reserved1 << 24) | (ntohl(*cf1) >> 8);

		/* restore the original correctionfield value */
		if (((ntohl(*cf1) >> 7) & 0x1) == 1)
		{
			/* correctionnfield is negative */
			*cf1 = ((u32)0xff << 24) | ((ntohl(*cf1) & 0xff) << 16) |
				(ntohl(*cf2) >> 16);
			*cf1 = htonl(*cf1);
			*cf2 = (ntohl(*cf2) & 0xffff) << 16;
			*cf2 = htonl(*cf2);
		}
		else
		{
			/* correctionfield is positive */
			*cf1 = ((ntohl(*cf1) & 0xff) << 16) | (ntohl(*cf2) >> 16);
			*cf1 = htonl(*cf1);
			*cf2 = (ntohl(*cf2) & 0xffff) << 16;
			*cf2 = htonl(*cf2);
		}
	}
	else
	{
		/* RX timestamp mdio mode, FAL_RX_TS_MDIO */
		qca808x_get_pkt_info(skb, ptp_type, &pkt_info);

		qca808x_ptp_timestamp_get(RX_DIRECTION, &pkt_info, &tx_time);
		ts.tv_sec = tx_time.seconds;
		ts.tv_nsec = tx_time.nanoseconds;
	}
	ns = timespec64_to_ns(&ts);

	shhwtstamps->hwtstamp = ns_to_ktime(ns);
	netif_rx_ni(skb);
	return true;
}


static void qca808x_txtstamp(struct phy_device *phydev,
			     struct sk_buff *skb, int type)
{
	skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;

	skb_queue_tail(&qca808x_tx_queue, skb);
	ptp_type = type;
	schedule_delayed_work(&qca808x_ts_work, SKB_TIMESTAMP_TIMEOUT);
}

static int qca808x_ts_info(struct phy_device *dev, struct ethtool_ts_info *info)
{
	info->so_timestamping =
		SOF_TIMESTAMPING_TX_HARDWARE |
		SOF_TIMESTAMPING_RX_HARDWARE |
		SOF_TIMESTAMPING_RAW_HARDWARE;
	info->tx_types =
		(1 << HWTSTAMP_TX_OFF) |
		(1 << HWTSTAMP_TX_ON) |
		(1 << HWTSTAMP_TX_ONESTEP_SYNC);
	info->rx_filters =
		(1 << HWTSTAMP_FILTER_NONE) |
		(1 << HWTSTAMP_FILTER_PTP_V1_L4_EVENT) |
		(1 << HWTSTAMP_FILTER_PTP_V2_L4_EVENT) |
		(1 << HWTSTAMP_FILTER_PTP_V2_L2_EVENT) |
		(1 << HWTSTAMP_FILTER_PTP_V2_EVENT);
	return 0;
}

struct phy_driver qca808x_phy_driver = {
	.phy_id		= QCA8081_PHY,
	.phy_id_mask	= 0xfffffff0,
	.name		= "QCA808X PHY",
	.features	= PHY_QCA808X_FEATURES,
	.flags		= PHY_HAS_INTERRUPT,
	.probe		= qca808x_phy_probe,
	.remove		= qca808x_phy_remove,
	.soft_reset	= qca808x_soft_reset,
	.config_init	= qca808x_config_init,
	.aneg_done	= genphy_aneg_done,
	.config_aneg	= genphy_config_aneg,
	.config_intr	= qca808x_config_intr,
	.ack_interrupt	= qca808x_ack_interrupt,
	.read_status	= qca808x_read_status,
	.match_phy_device	= qca808x_match_phy_device,
	.ts_info	= qca808x_ts_info,
	.hwtstamp	= qca808x_hwtstamp,
	.rxtstamp	= qca808x_rxtstamp,
	.txtstamp	= qca808x_txtstamp,
	.driver		= { .owner = THIS_MODULE,},
};

void qca808x_phy_ptp_init(void)
{
	phy_driver_register(&qca808x_phy_driver);
}
