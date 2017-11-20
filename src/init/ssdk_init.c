/*
 * Copyright (c) 2012, 2014-2017, The Linux Foundation. All rights reserved.
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


#include "sw.h"
#include "ssdk_init.h"
#include "fal_init.h"
#include "fal.h"
#include "hsl.h"
#include "hsl_dev.h"
#include "hsl_phy.h"
#include "ssdk_init.h"
#include "ssdk_interrupt.h"
#include <linux/kconfig.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/phy.h>
#include <linux/platform_device.h>
#include <linux/types.h>
//#include <asm/mach-types.h>
#include <generated/autoconf.h>
#include <linux/if_arp.h>
#include <linux/inetdevice.h>
#include <linux/netdevice.h>
#include <linux/phy.h>
#include <linux/mdio.h>
#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/string.h>
#include <linux/gpio.h>

#if defined(IN_SWCONFIG)
#if defined(CONFIG_OF) && (LINUX_VERSION_CODE >= KERNEL_VERSION(3,14,0))
#include <linux/switch.h>
#else
#include <net/switch.h>
#endif
#endif

#if defined(ISIS) ||defined(ISISC) ||defined(GARUDA)
#include <f1_phy.h>
#endif
#if defined(ATHENA) ||defined(SHIVA) ||defined(HORUS)
#include <f2_phy.h>
#endif
#ifdef IN_MALIBU_PHY
#include <malibu_phy.h>
#endif
#if defined(CONFIG_OF) && (LINUX_VERSION_CODE >= KERNEL_VERSION(4,1,0))
#include <linux/of.h>
#include <linux/reset.h>
#ifdef BOARD_AR71XX
#ifdef CONFIG_AR8216_PHY
#include "drivers/net/phy/ar8327.h"
#endif
#include "drivers/net/ethernet/atheros/ag71xx/ag71xx.h"
#endif
#elif defined(CONFIG_OF) && (LINUX_VERSION_CODE >= KERNEL_VERSION(3,14,0))
#include <linux/of.h>
#include <drivers/leds/leds-ipq40xx.h>
#include <linux/of_platform.h>
#include <linux/reset.h>
#else
#include <linux/ar8216_platform.h>
#include <drivers/net/phy/ar8216.h>
#include <drivers/net/ethernet/atheros/ag71xx/ag71xx.h>
#endif
#include "ssdk_plat.h"
#include "ssdk_clk.h"
#include "ref_vlan.h"
#include "ref_fdb.h"
#include "ref_mib.h"
#include "ref_port_ctrl.h"
#include "ref_misc.h"
#include "ref_uci.h"
#include "ref_vsi.h"
#include "shell.h"
#ifdef BOARD_AR71XX
#include "ssdk_uci.h"
#endif

#ifdef IN_IP
#if defined (CONFIG_NF_FLOW_COOKIE)
#include "fal_flowcookie.h"
#ifdef IN_SFE
#include <shortcut-fe/sfe.h>
#endif
#endif
#endif

#ifdef IN_RFS
#if defined(CONFIG_VLAN_8021Q) || defined(CONFIG_VLAN_8021Q_MODULE)
#include <linux/if_vlan.h>
#endif
#include <qca-rfs/rfs_dev.h>
#ifdef IN_IP
#include "fal_rfs.h"
#endif
#endif
#include "adpt.h"

#ifdef IN_RFS
struct rfs_device rfs_dev;
struct notifier_block ssdk_inet_notifier;
#endif

//#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,14,0))
struct notifier_block ssdk_dev_notifier;
//#endif


extern ssdk_chip_type SSDK_CURRENT_CHIP_TYPE;
extern a_uint32_t hsl_dev_wan_port_get(a_uint32_t dev_id);
extern void dess_rgmii_sw_mac_polling_task(struct qca_phy_priv *priv);
extern void qca_ar8327_sw_mac_polling_task(struct qca_phy_priv *priv);
extern void qca_ar8327_sw_mib_task(struct qca_phy_priv *priv);

//#define PSGMII_DEBUG

#define QCA_QM_WORK_DELAY	100
#define QCA_QM_ITEM_NUMBER 41
#define QCA_RGMII_WORK_DELAY	1000
#define QCA_MAC_SW_SYNC_WORK_DELAY	1000

static bool qca_dess_rfs_registered = false;
ssdk_dt_global_t ssdk_dt_global = {0};

struct qca_phy_priv **qca_phy_priv_global;

struct qca_phy_priv* ssdk_phy_priv_data_get(a_uint32_t dev_id)
{
	if (dev_id >= SW_MAX_NR_DEV || !qca_phy_priv_global)
		return NULL;

	return qca_phy_priv_global[dev_id];
}

a_uint32_t ssdk_dt_global_get_mac_mode(a_uint32_t dev_id, a_uint32_t index)
{
	if (index == 0)
		return ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->mac_mode;
	if (index == 1)
		return ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->mac_mode1;
	if (index == 2)
		return ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->mac_mode2;

	return 0;
}

a_uint32_t ssdk_dt_global_set_mac_mode(a_uint32_t dev_id, a_uint32_t index, a_uint32_t mode)
{
	if (index == 0)
	{
		 ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->mac_mode= mode;
	}
	if (index == 1)
	{
		 ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->mac_mode1 = mode;
	}
	if (index == 2)
	{
		 ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->mac_mode2 = mode;
	}

	return 0;
}

a_uint32_t hppe_port_type[6] = {0,0,0,0,0,0}; // this variable should be init by ssdk_init

a_uint32_t
qca_hppe_port_mac_type_get(a_uint32_t dev_id, a_uint32_t port_id)
{
	if ((port_id < 1) || (port_id > 6))
		return 0;
	return hppe_port_type[port_id - 1];
}

a_uint32_t
qca_hppe_port_mac_type_set(a_uint32_t dev_id, a_uint32_t port_id, a_uint32_t port_type)
{
	 if ((port_id < 1) || (port_id > 6))
		 return 0;
	hppe_port_type[port_id - 1] = port_type;

	return 0;
}

#ifndef BOARD_AR71XX
#if defined(CONFIG_OF) && (LINUX_VERSION_CODE >= KERNEL_VERSION(3,14,0))
static void
ssdk_phy_rgmii_set(struct qca_phy_priv *priv)
{
	struct device_node *np = NULL;
	u32 rgmii_en = 0, tx_delay = 0, rx_delay = 0;

	if (priv->ess_switch_flag == A_TRUE)
		np = priv->of_node;
	else
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4,9,0))
		np = priv->phy->mdio.dev.of_node;
#else
		np = priv->phy->dev.of_node;
#endif

	if (!np)
		return;

	if (!of_property_read_u32(np, "phy_rgmii_en", &rgmii_en)) {
		a_uint16_t val = 0;
		/*enable RGMII  mode */
		qca_ar8327_phy_dbg_read(0, AR8327_PORT5_PHY_ADDR,
				AR8327_PHY_REG_MODE_SEL, &val);
		val |= AR8327_PHY_RGMII_MODE;
		qca_ar8327_phy_dbg_write(0, AR8327_PORT5_PHY_ADDR,
				AR8327_PHY_REG_MODE_SEL, val);
		if (!of_property_read_u32(np, "txclk_delay_en", &tx_delay)
				&& tx_delay == 1) {
			qca_ar8327_phy_dbg_read(0, AR8327_PORT5_PHY_ADDR,
					AR8327_PHY_REG_SYS_CTRL, &val);
			val |= AR8327_PHY_RGMII_TX_DELAY;
			qca_ar8327_phy_dbg_write(0, AR8327_PORT5_PHY_ADDR,
					AR8327_PHY_REG_SYS_CTRL, val);
		}
		if (!of_property_read_u32(np, "rxclk_delay_en", &rx_delay)
				&& rx_delay == 1) {
			qca_ar8327_phy_dbg_read(0, AR8327_PORT5_PHY_ADDR,
					AR8327_PHY_REG_TEST_CTRL, &val);
			val |= AR8327_PHY_RGMII_RX_DELAY;
			qca_ar8327_phy_dbg_write(0, AR8327_PORT5_PHY_ADDR,
					AR8327_PHY_REG_TEST_CTRL, val);
		}
	}
}
#else
static void
ssdk_phy_rgmii_set(struct qca_phy_priv *priv)
{
	struct ar8327_platform_data *plat_data;

	plat_data = priv->phy->dev.platform_data;
	if (plat_data == NULL) {
		return;
	}

	if(plat_data->pad5_cfg) {
		if(plat_data->pad5_cfg->mode == AR8327_PAD_PHY_RGMII) {
			a_uint16_t val = 0;
			/*enable RGMII  mode */
			priv->phy_dbg_read(0, AR8327_PORT5_PHY_ADDR,
					AR8327_PHY_REG_MODE_SEL, &val);
			val |= AR8327_PHY_RGMII_MODE;
			priv->phy_dbg_write(0, AR8327_PORT5_PHY_ADDR,
					AR8327_PHY_REG_MODE_SEL, val);
			if(plat_data->pad5_cfg->txclk_delay_en) {
				priv->phy_dbg_read(0, AR8327_PORT5_PHY_ADDR,
						AR8327_PHY_REG_SYS_CTRL, &val);
				val |= AR8327_PHY_RGMII_TX_DELAY;
				priv->phy_dbg_write(0, AR8327_PORT5_PHY_ADDR,
						AR8327_PHY_REG_SYS_CTRL, val);
			}
			if(plat_data->pad5_cfg->rxclk_delay_en) {
				priv->phy_dbg_read(0, AR8327_PORT5_PHY_ADDR,
						AR8327_PHY_REG_TEST_CTRL, &val);
				val |= AR8327_PHY_RGMII_RX_DELAY;
				priv->phy_dbg_write(0, AR8327_PORT5_PHY_ADDR,
						AR8327_PHY_REG_TEST_CTRL, val);
			}
		}
	}
}
#endif
#endif


static void
qca_ar8327_phy_fixup(struct qca_phy_priv *priv, int phy)
{
	switch (priv->revision) {
	case 1:
		/* 100m waveform */
		priv->phy_dbg_write(priv->device_id, phy, 0, 0x02ea);
		/* turn on giga clock */
		priv->phy_dbg_write(priv->device_id, phy, 0x3d, 0x68a0);
		break;

	case 2:
		priv->phy_mmd_write(priv->device_id, phy, 0x7, 0x3c);
		priv->phy_mmd_write(priv->device_id, phy, 0x4007, 0x0);
		/* fallthrough */
	case 4:
		priv->phy_mmd_write(priv->device_id, phy, 0x3, 0x800d);
		priv->phy_mmd_write(priv->device_id, phy, 0x4003, 0x803f);

		priv->phy_dbg_write(priv->device_id, phy, 0x3d, 0x6860);
		priv->phy_dbg_write(priv->device_id, phy, 0x5, 0x2c46);
		priv->phy_dbg_write(priv->device_id, phy, 0x3c, 0x6000);
		break;
	}
}

#ifdef IN_PORTVLAN
static void qca_port_isolate(a_uint32_t dev_id)
{
	a_uint32_t port_id, mem_port_id, mem_port_map[AR8327_NUM_PORTS]={0};

	for(port_id = 0; port_id < AR8327_NUM_PORTS; port_id++)
	{
		if(port_id == 6)
			for(mem_port_id = 1; mem_port_id<= 4; mem_port_id++)
				mem_port_map[port_id]  |= (1 << mem_port_id);
		else if (port_id == 0)
			mem_port_map[port_id]  |= (1 << 5);
		else if (port_id >= 1 && port_id <= 4)
			mem_port_map[port_id]  |= (1 << 6);
		else
			mem_port_map[port_id]  |= 1;
	}

	for(port_id = 0; port_id < AR8327_NUM_PORTS; port_id++)

		 fal_portvlan_member_update(dev_id, port_id, mem_port_map[port_id]);

}

static void ssdk_portvlan_init(a_uint32_t dev_id)
{
	ssdk_dt_cfg *dt_cfg;
	a_uint32_t port = 0;
	a_uint32_t cpu_bmp, lan_bmp, wan_bmp;

	dt_cfg = ssdk_dt_global.ssdk_dt_switch_nodes[dev_id];
	cpu_bmp = dt_cfg->port_cfg.cpu_bmp;
	lan_bmp = dt_cfg->port_cfg.lan_bmp;
	wan_bmp = dt_cfg->port_cfg.wan_bmp;

	if (!(cpu_bmp | lan_bmp | wan_bmp)) {
		qca_port_isolate(dev_id);
		return;
	}

	for(port = 0; port < SSDK_MAX_PORT_NUM; port++)
	{
		if(cpu_bmp & (1 << port))
		{
			fal_portvlan_member_update(dev_id, port, lan_bmp|wan_bmp);
		}
		if(lan_bmp & (1 << port))
		{
			fal_portvlan_member_update(dev_id, port, (lan_bmp|cpu_bmp)&(~(1<<port)));
		}
		if(wan_bmp & (1 << port))
		{
			fal_portvlan_member_update(dev_id, port, (wan_bmp|cpu_bmp)&(~(1<<port)));
		}
	}
}
#endif

sw_error_t
qca_switch_init(a_uint32_t dev_id)
{
	a_uint32_t nr = 0;
	int i = 0;

	/*fal_reset(dev_id);*/
	/*enable cpu and disable mirror*/
	#ifdef IN_MISC
	fal_cpu_port_status_set(dev_id, A_TRUE);
	/* setup MTU */
	fal_frame_max_size_set(dev_id, 1518);
	#endif
	#ifdef IN_MIB
	/* Enable MIB counters */
	fal_mib_status_set(dev_id, A_TRUE);
	fal_mib_cpukeep_set(dev_id, A_FALSE);
	#endif
	#ifdef IN_IGMP
	fal_igmp_mld_rp_set(dev_id, 0);
	#endif

	/*enable pppoe for dakota to support RSS*/
	if (SSDK_CURRENT_CHIP_TYPE == CHIP_DESS) {
		#ifdef DESS
		#ifdef IN_MISC
		fal_pppoe_status_set(dev_id, A_TRUE);
		#endif
		#endif
	}

	for (i = 0; i < AR8327_NUM_PORTS; i++) {
		/* forward multicast and broadcast frames to CPU */
		#ifdef IN_MISC
		fal_port_unk_uc_filter_set(dev_id, i, A_FALSE);
		fal_port_unk_mc_filter_set(dev_id, i, A_FALSE);
		fal_port_bc_filter_set(dev_id, i, A_FALSE);
		#endif
		#ifdef IN_PORTVLAN
		fal_port_default_svid_set(dev_id, i, 0);
		fal_port_default_cvid_set(dev_id, i, 0);
		fal_port_1qmode_set(dev_id, i, FAL_1Q_DISABLE);
		fal_port_egvlanmode_set(dev_id, i, FAL_EG_UNMODIFIED);
		#endif

		#ifdef IN_FDB
		fal_fdb_port_learn_set(dev_id, i, A_TRUE);
		#endif
		#ifdef IN_STP
		fal_stp_port_state_set(dev_id, 0, i, FAL_STP_FARWARDING);
		#endif
		#ifdef IN_PORTVLAN
		fal_port_vlan_propagation_set(dev_id, i, FAL_VLAN_PROPAGATION_REPLACE);
		#endif
		#ifdef IN_IGMP
		fal_port_igmps_status_set(dev_id, i, A_FALSE);
		fal_port_igmp_mld_join_set(dev_id, i, A_FALSE);
		fal_port_igmp_mld_leave_set(dev_id, i, A_FALSE);
		fal_igmp_mld_entry_creat_set(dev_id, A_FALSE);
		fal_igmp_mld_entry_v3_set(dev_id, A_FALSE);
		#endif
		if (SSDK_CURRENT_CHIP_TYPE == CHIP_SHIVA) {
			return SW_OK;
		} else if (SSDK_CURRENT_CHIP_TYPE == CHIP_DESS) {
			#ifdef DESS
			#ifdef IN_PORTCONTROL
			fal_port_flowctrl_forcemode_set(dev_id, i, A_FALSE);
			fal_port_link_forcemode_set(dev_id, i, A_TRUE);
			#endif
			#ifdef IN_QOS
			nr = 240; /*30*8*/
			fal_qos_port_tx_buf_nr_set(dev_id, i, &nr);
			nr = 48; /*6*8*/
			fal_qos_port_rx_buf_nr_set(dev_id, i, &nr);
			fal_qos_port_red_en_set(dev_id, i, A_TRUE);
			nr = 32;
			fal_qos_queue_tx_buf_nr_set(dev_id, i, 5, &nr);
			fal_qos_queue_tx_buf_nr_set(dev_id, i, 4, &nr);
			fal_qos_queue_tx_buf_nr_set(dev_id, i, 3, &nr);
			fal_qos_queue_tx_buf_nr_set(dev_id, i, 2, &nr);
			fal_qos_queue_tx_buf_nr_set(dev_id, i, 1, &nr);
			fal_qos_queue_tx_buf_nr_set(dev_id, i, 0, &nr);
			#endif
			#endif
		} else if (SSDK_CURRENT_CHIP_TYPE == CHIP_ISISC ||
			SSDK_CURRENT_CHIP_TYPE == CHIP_ISIS) {
			#if defined(ISISC) || defined(ISIS)
			#ifdef IN_INTERFACECONTROL
			fal_port_3az_status_set(dev_id, i, A_FALSE);
			#endif
			#ifdef IN_PORTCONTROL
			fal_port_flowctrl_forcemode_set(dev_id, i, A_TRUE);
			fal_port_flowctrl_set(dev_id, i, A_FALSE);

			if (i != 0 && i != 6) {
				fal_port_flowctrl_set(dev_id, i, A_TRUE);
				fal_port_flowctrl_forcemode_set(dev_id, i, A_FALSE);
			}
			#endif
			if (i == 0 || i == 5 || i == 6) {
				#ifdef IN_QOS
				nr = 240; /*30*8*/
				fal_qos_port_tx_buf_nr_set(dev_id, i, &nr);
				nr = 48; /*6*8*/
				fal_qos_port_rx_buf_nr_set(dev_id, i, &nr);
				fal_qos_port_red_en_set(dev_id, i, A_TRUE);
				if (SSDK_CURRENT_CHIP_TYPE == CHIP_ISISC) {
					nr = 64; /*8*8*/
				} else if (SSDK_CURRENT_CHIP_TYPE == CHIP_ISIS) {
					nr = 60;
				}
				fal_qos_queue_tx_buf_nr_set(dev_id, i, 5, &nr);
				nr = 48; /*6*8*/
				fal_qos_queue_tx_buf_nr_set(dev_id, i, 4, &nr);
				nr = 32; /*4*8*/
				fal_qos_queue_tx_buf_nr_set(dev_id, i, 3, &nr);
				nr = 32; /*4*8*/
				fal_qos_queue_tx_buf_nr_set(dev_id, i, 2, &nr);
				nr = 32; /*4*8*/
				fal_qos_queue_tx_buf_nr_set(dev_id, i, 1, &nr);
				nr = 24; /*3*8*/
				fal_qos_queue_tx_buf_nr_set(dev_id, i, 0, &nr);
				#endif
			} else {
				#ifdef IN_QOS
				nr = 200; /*25*8*/
				fal_qos_port_tx_buf_nr_set(dev_id, i, &nr);
				nr = 48; /*6*8*/
				fal_qos_port_rx_buf_nr_set(dev_id, i, &nr);
				fal_qos_port_red_en_set(dev_id, i, A_TRUE);
				if (SSDK_CURRENT_CHIP_TYPE == CHIP_ISISC) {
					nr = 64; /*8*8*/
				} else if (SSDK_CURRENT_CHIP_TYPE == CHIP_ISIS) {
					nr = 60;
				}
				fal_qos_queue_tx_buf_nr_set(dev_id, i, 3, &nr);
				nr = 48; /*6*8*/
				fal_qos_queue_tx_buf_nr_set(dev_id, i, 2, &nr);
				nr = 32; /*4*8*/
				fal_qos_queue_tx_buf_nr_set(dev_id, i, 1, &nr);
				nr = 24; /*3*8*/
				fal_qos_queue_tx_buf_nr_set(dev_id, i, 0, &nr);
				#endif
			}
			#endif
		}
	}

	return SW_OK;
}

void qca_ar8327_phy_linkdown(a_uint32_t dev_id)
{
	int i;
	a_uint16_t phy_val;

	for (i = 0; i < AR8327_NUM_PHYS; i++) {
		qca_ar8327_phy_write(dev_id, i, 0x0, 0x0800);	// phy powerdown

		qca_ar8327_phy_dbg_read(dev_id, i, 0x3d, &phy_val);
		phy_val &= ~0x0040;
		qca_ar8327_phy_dbg_write(dev_id, i, 0x3d, phy_val);

		/*PHY will stop the tx clock for a while when link is down
			1. en_anychange  debug port 0xb bit13 = 0  //speed up link down tx_clk
			2. sel_rst_80us  debug port 0xb bit10 = 0  //speed up speed mode change to 2'b10 tx_clk
		*/
		qca_ar8327_phy_dbg_read(dev_id, i, 0xb, &phy_val);
		phy_val &= ~0x2400;
		qca_ar8327_phy_dbg_write(dev_id, i, 0xb, phy_val);
	}
}

void
qca_mac_disable(a_uint32_t device_id)
{
	hsl_api_t *p_api;

	p_api = hsl_api_ptr_get (device_id);
	if(p_api
		&& p_api->interface_mac_pad_set
		&& p_api->interface_mac_sgmii_set)
	{
		p_api->interface_mac_pad_set(device_id,0,0);
		p_api->interface_mac_pad_set(device_id,5,0);
		p_api->interface_mac_pad_set(device_id,6,0);
		p_api->interface_mac_sgmii_set(device_id,AR8327_REG_PAD_SGMII_CTRL_HW_INIT);
	}
	else
	{
		SSDK_ERROR("API not support \n");
	}
}

static void qca_switch_set_mac_force(struct qca_phy_priv *priv)
{
	a_uint32_t value, value0, i;
	if (priv == NULL || (priv->mii_read == NULL) || (priv->mii_write == NULL)) {
		SSDK_ERROR("In qca_switch_set_mac_force, private data is NULL!\r\n");
		return;
	}

	for (i=0; i < AR8327_NUM_PORTS; ++i) {
		/* b3:2=0,Tx/Rx Mac disable,
		 b9=0,LINK_EN disable */
		value0 = priv->mii_read(priv->device_id, AR8327_REG_PORT_STATUS(i));
		value = value0 & ~(AR8327_PORT_STATUS_LINK_AUTO |
						AR8327_PORT_STATUS_TXMAC |
						AR8327_PORT_STATUS_RXMAC);
		priv->mii_write(priv->device_id, AR8327_REG_PORT_STATUS(i), value);

		/* Force speed to 1000M Full */
		value = priv->mii_read(priv->device_id, AR8327_REG_PORT_STATUS(i));
		value &= ~(AR8327_PORT_STATUS_DUPLEX | AR8327_PORT_STATUS_SPEED);
		value |= AR8327_PORT_SPEED_1000M | AR8327_PORT_STATUS_DUPLEX;
		priv->mii_write(priv->device_id, AR8327_REG_PORT_STATUS(i), value);
	}
	return;
}

void
qca_ar8327_phy_enable(struct qca_phy_priv *priv)
{
	int i = 0;
	#ifndef BOARD_AR71XX
        ssdk_phy_rgmii_set(priv);
        #endif
	for (i = 0; i < AR8327_NUM_PHYS; i++) {
		a_uint16_t value = 0;

		if (priv->version == QCA_VER_AR8327)
			qca_ar8327_phy_fixup(priv, i);

		/* start autoneg*/
		priv->phy_write(priv->device_id, i, MII_ADVERTISE, ADVERTISE_ALL |
						     ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM);
		//phy reg 0x9, b10,1 = Prefer multi-port device (master)
		priv->phy_write(priv->device_id, i, MII_CTRL1000, (0x0400|ADVERTISE_1000FULL));

		priv->phy_write(priv->device_id, i, MII_BMCR, BMCR_RESET | BMCR_ANENABLE);

		priv->phy_dbg_read(priv->device_id, i, 0, &value);
		value &= (~(1<<12));
		priv->phy_dbg_write(priv->device_id, i, 0, value);

		msleep(100);
	}
}
void qca_ar8327_sw_soft_reset(struct qca_phy_priv *priv)
{
	a_uint32_t value = 0;

	value = priv->mii_read(priv->device_id, AR8327_REG_CTRL);
	value |= 0x80000000;
	priv->mii_write(priv->device_id, AR8327_REG_CTRL, value);
	/*Need wait reset done*/
	do {
		udelay(10);
		value = priv->mii_read(priv->device_id, AR8327_REG_CTRL);
	} while(value & AR8327_CTRL_RESET);
	do {
		udelay(10);
		value = priv->mii_read(priv->device_id, 0x20);
	} while ((value & SSDK_GLOBAL_INITIALIZED_STATUS) !=
			SSDK_GLOBAL_INITIALIZED_STATUS);

	return;
}

#if defined(CONFIG_OF) && (LINUX_VERSION_CODE >= KERNEL_VERSION(3,14,0))
int qca_ar8327_hw_init(struct qca_phy_priv *priv)
{
	struct device_node *np = NULL;
	const __be32 *paddr;
	a_uint32_t reg, value, i;
	a_int32_t len;

	if (priv->ess_switch_flag == A_TRUE)
		np = priv->of_node;
	else
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4,9,0))
		np = priv->phy->mdio.dev.of_node;
#else
		np = priv->phy->dev.of_node;
#endif

	if(!np)
		return -EINVAL;

	/*Before switch software reset, disable PHY and clear  MAC PAD*/
	qca_ar8327_phy_linkdown(priv->device_id);
	qca_mac_disable(priv->device_id);
	msleep(1000);

	/*First software reset S17 chip*/
	qca_ar8327_sw_soft_reset(priv);

	/*After switch software reset, need disable all ports' MAC with 1000M FULL*/
	qca_switch_set_mac_force(priv);

	/* Configure switch register from DT information */
	paddr = of_get_property(np, "qca,ar8327-initvals", &len);
	if (paddr) {
		if (len < (2 * sizeof(*paddr))) {
			SSDK_ERROR("len:%d < 2 * sizeof(*paddr):%d\n", len, 2 * sizeof(*paddr));
			return -EINVAL;
		}

		len /= sizeof(*paddr);

		for (i = 0; i < len - 1; i += 2) {
			reg = be32_to_cpup(paddr + i);
			value = be32_to_cpup(paddr + i + 1);
			priv->mii_write(priv->device_id, reg, value);
		}
	}

	value = priv->mii_read(priv->device_id, AR8327_REG_MODULE_EN);
	value &= ~AR8327_REG_MODULE_EN_QM_ERR;
	value &= ~AR8327_REG_MODULE_EN_LOOKUP_ERR;
	priv->mii_write(priv->device_id, AR8327_REG_MODULE_EN, value);

	qca_switch_init(priv->device_id);
#ifdef IN_PORTVLAN
	ssdk_portvlan_init(priv->device_id);
#endif
	qca_mac_enable_intr(priv);
	qca_ar8327_phy_enable(priv);

	return 0;
}
#else
static a_uint32_t
qca_ar8327_get_pad_cfg(struct ar8327_pad_cfg *pad_cfg)
{
	a_uint32_t value = 0;

	if (pad_cfg == 0) {
		return 0;
    }

    if(pad_cfg->mode == AR8327_PAD_MAC2MAC_MII) {
		value = AR8327_PAD_CTRL_MAC_MII_EN;
		if (pad_cfg->rxclk_sel)
			value |= AR8327_PAD_CTRL_MAC_MII_RXCLK_SEL;
		if (pad_cfg->txclk_sel)
			value |= AR8327_PAD_CTRL_MAC_MII_TXCLK_SEL;

    } else if (pad_cfg->mode == AR8327_PAD_MAC2MAC_GMII) {
		value = AR8327_PAD_CTRL_MAC_GMII_EN;
		if (pad_cfg->rxclk_sel)
			value |= AR8327_PAD_CTRL_MAC_GMII_RXCLK_SEL;
		if (pad_cfg->txclk_sel)
			value |= AR8327_PAD_CTRL_MAC_GMII_TXCLK_SEL;

    } else if (pad_cfg->mode == AR8327_PAD_MAC_SGMII) {
		value = AR8327_PAD_CTRL_SGMII_EN;

		/* WAR for AP136 board. */
		value |= pad_cfg->txclk_delay_sel <<
		        AR8327_PAD_CTRL_RGMII_TXCLK_DELAY_SEL_S;
		value |= pad_cfg->rxclk_delay_sel <<
                AR8327_PAD_CTRL_RGMII_RXCLK_DELAY_SEL_S;
		if (pad_cfg->rxclk_delay_en)
			value |= AR8327_PAD_CTRL_RGMII_RXCLK_DELAY_EN;
		if (pad_cfg->txclk_delay_en)
			value |= AR8327_PAD_CTRL_RGMII_TXCLK_DELAY_EN;

    } else if (pad_cfg->mode == AR8327_PAD_MAC2PHY_MII) {
		value = AR8327_PAD_CTRL_PHY_MII_EN;
		if (pad_cfg->rxclk_sel)
			value |= AR8327_PAD_CTRL_PHY_MII_RXCLK_SEL;
		if (pad_cfg->txclk_sel)
			value |= AR8327_PAD_CTRL_PHY_MII_TXCLK_SEL;

    } else if (pad_cfg->mode == AR8327_PAD_MAC2PHY_GMII) {
		value = AR8327_PAD_CTRL_PHY_GMII_EN;
		if (pad_cfg->pipe_rxclk_sel)
			value |= AR8327_PAD_CTRL_PHY_GMII_PIPE_RXCLK_SEL;
		if (pad_cfg->rxclk_sel)
			value |= AR8327_PAD_CTRL_PHY_GMII_RXCLK_SEL;
		if (pad_cfg->txclk_sel)
			value |= AR8327_PAD_CTRL_PHY_GMII_TXCLK_SEL;

    } else if (pad_cfg->mode == AR8327_PAD_MAC_RGMII) {
		value = AR8327_PAD_CTRL_RGMII_EN;
		value |= pad_cfg->txclk_delay_sel <<
                 AR8327_PAD_CTRL_RGMII_TXCLK_DELAY_SEL_S;
		value |= pad_cfg->rxclk_delay_sel <<
                 AR8327_PAD_CTRL_RGMII_RXCLK_DELAY_SEL_S;
		if (pad_cfg->rxclk_delay_en)
			value |= AR8327_PAD_CTRL_RGMII_RXCLK_DELAY_EN;
		if (pad_cfg->txclk_delay_en)
			value |= AR8327_PAD_CTRL_RGMII_TXCLK_DELAY_EN;

    } else if (pad_cfg->mode == AR8327_PAD_PHY_GMII) {
		value = AR8327_PAD_CTRL_PHYX_GMII_EN;

    } else if (pad_cfg->mode == AR8327_PAD_PHY_RGMII) {
		value = AR8327_PAD_CTRL_PHYX_RGMII_EN;

    } else if (pad_cfg->mode == AR8327_PAD_PHY_MII) {
		value = AR8327_PAD_CTRL_PHYX_MII_EN;

	} else {
        value = 0;
    }

	return value;
}

#ifndef BOARD_AR71XX
static a_uint32_t
qca_ar8327_get_pwr_sel(struct qca_phy_priv *priv,
                                struct ar8327_platform_data *plat_data)
{
	struct ar8327_pad_cfg *cfg = NULL;
	a_uint32_t value;

	if (!plat_data) {
		return 0;
	}

	value = priv->mii_read(priv->device_id, AR8327_REG_PAD_MAC_PWR_SEL);

	cfg = plat_data->pad0_cfg;

	if (cfg && (cfg->mode == AR8327_PAD_MAC_RGMII) &&
                cfg->rgmii_1_8v) {
		value |= AR8327_PAD_MAC_PWR_RGMII0_1_8V;
	}

	cfg = plat_data->pad5_cfg;
	if (cfg && (cfg->mode == AR8327_PAD_MAC_RGMII) &&
                cfg->rgmii_1_8v) {
		value |= AR8327_PAD_MAC_PWR_RGMII1_1_8V;
	}

	cfg = plat_data->pad6_cfg;
	if (cfg && (cfg->mode == AR8327_PAD_MAC_RGMII) &&
               cfg->rgmii_1_8v) {
		value |= AR8327_PAD_MAC_PWR_RGMII1_1_8V;
	}

	return value;
}
#endif

static a_uint32_t
qca_ar8327_set_led_cfg(struct qca_phy_priv *priv,
                              struct ar8327_platform_data *plat_data,
                              a_uint32_t pos)
{
	struct ar8327_led_cfg *led_cfg;
	a_uint32_t new_pos = pos;

	led_cfg = plat_data->led_cfg;
	if (led_cfg) {
		if (led_cfg->open_drain)
			new_pos |= AR8327_POS_LED_OPEN_EN;
		else
			new_pos &= ~AR8327_POS_LED_OPEN_EN;

		priv->mii_write(priv->device_id, AR8327_REG_LED_CTRL_0, led_cfg->led_ctrl0);
		priv->mii_write(priv->device_id, AR8327_REG_LED_CTRL_1, led_cfg->led_ctrl1);
		priv->mii_write(priv->device_id, AR8327_REG_LED_CTRL_2, led_cfg->led_ctrl2);
		priv->mii_write(priv->device_id, AR8327_REG_LED_CTRL_3, led_cfg->led_ctrl3);

		if (new_pos != pos) {
			new_pos |= AR8327_POS_POWER_ON_SEL;
		}
	}
	return new_pos;
}
#ifndef BOARD_AR71XX
static int
qca_ar8327_set_sgmii_cfg(struct qca_phy_priv *priv,
                              struct ar8327_platform_data *plat_data,
                              a_uint32_t* new_pos)
{
	a_uint32_t value = 0;

	/*configure the SGMII*/
	value = priv->mii_read(priv->device_id, AR8327_REG_PAD_SGMII_CTRL);
	value &= ~(AR8327_PAD_SGMII_CTRL_MODE_CTRL);
	value |= ((plat_data->sgmii_cfg->sgmii_mode) <<
          AR8327_PAD_SGMII_CTRL_MODE_CTRL_S);

	if (priv->version == QCA_VER_AR8337) {
		value |= (AR8327_PAD_SGMII_CTRL_EN_PLL |
		     AR8327_PAD_SGMII_CTRL_EN_RX |
		     AR8327_PAD_SGMII_CTRL_EN_TX);
	} else {
		value &= ~(AR8327_PAD_SGMII_CTRL_EN_PLL |
		       AR8327_PAD_SGMII_CTRL_EN_RX |
		       AR8327_PAD_SGMII_CTRL_EN_TX);
	}
	value |= AR8327_PAD_SGMII_CTRL_EN_SD;

	priv->mii_write(priv->device_id, AR8327_REG_PAD_SGMII_CTRL, value);

	if (plat_data->sgmii_cfg->serdes_aen) {
		*new_pos &= ~AR8327_POS_SERDES_AEN;
	} else {
		*new_pos |= AR8327_POS_SERDES_AEN;
	}
	return 0;
}
#endif

static int
qca_ar8327_set_plat_data_cfg(struct qca_phy_priv *priv,
                              struct ar8327_platform_data *plat_data)
{
	a_uint32_t pos, new_pos;

	pos = priv->mii_read(priv->device_id, AR8327_REG_POS);

	new_pos = qca_ar8327_set_led_cfg(priv, plat_data, pos);

#ifndef BOARD_AR71XX
	/*configure the SGMII*/
	if (plat_data->sgmii_cfg) {
		qca_ar8327_set_sgmii_cfg(priv, plat_data, &new_pos);
	}
#endif

	priv->mii_write(priv->device_id, AR8327_REG_POS, new_pos);

	return 0;
}

static int
qca_ar8327_set_pad_cfg(struct qca_phy_priv *priv,
                              struct ar8327_platform_data *plat_data)
{
	a_uint32_t pad0 = 0, pad5 = 0, pad6 = 0;

	pad0 = qca_ar8327_get_pad_cfg(plat_data->pad0_cfg);
	priv->mii_write(priv->device_id, AR8327_REG_PAD0_CTRL, pad0);

	pad5 = qca_ar8327_get_pad_cfg(plat_data->pad5_cfg);
	if(priv->version == QCA_VER_AR8337) {
	        pad5 |= AR8327_PAD_CTRL_RGMII_RXCLK_DELAY_EN;
	}
	priv->mii_write(priv->device_id, AR8327_REG_PAD5_CTRL, pad5);

	pad6 = qca_ar8327_get_pad_cfg(plat_data->pad6_cfg);
	if(plat_data->pad5_cfg &&
		(plat_data->pad5_cfg->mode == AR8327_PAD_PHY_RGMII))
		pad6 |= AR8327_PAD_CTRL_PHYX_RGMII_EN;
	priv->mii_write(priv->device_id, AR8327_REG_PAD6_CTRL, pad6);

	return 0;
}

void
qca_ar8327_port_init(struct qca_phy_priv *priv, a_uint32_t port)
{
	struct ar8327_platform_data *plat_data;
	struct ar8327_port_cfg *port_cfg;
	a_uint32_t value;

	plat_data = priv->phy->dev.platform_data;
	if (plat_data == NULL) {
		return;
	}

	if (((port == 0) && plat_data->pad0_cfg) ||
	    ((port == 5) && plat_data->pad5_cfg) ||
	    ((port == 6) && plat_data->pad6_cfg)) {
	        switch (port) {
		        case 0:
		            port_cfg = &plat_data->cpuport_cfg;
		            break;
		        case 5:
		            port_cfg = &plat_data->port5_cfg;
		            break;
		        case 6:
		            port_cfg = &plat_data->port6_cfg;
		            break;
	        }
	} else {
	        return;
	}

	/*disable mac at first*/
	fal_port_rxmac_status_set(priv->device_id, port, A_FALSE);
	fal_port_txmac_status_set(priv->device_id, port, A_FALSE);
	value = port_cfg->duplex ? FAL_FULL_DUPLEX : FAL_HALF_DUPLEX;
	fal_port_duplex_set(priv->device_id, port, value);
	value = port_cfg->txpause ? A_TRUE : A_FALSE;
	fal_port_txfc_status_set(priv->device_id, port, value);
	value = port_cfg->rxpause ? A_TRUE : A_FALSE;
	fal_port_rxfc_status_set(priv->device_id, port, value);
	if(port_cfg->speed == AR8327_PORT_SPEED_10) {
		value = FAL_SPEED_10;
	} else if(port_cfg->speed == AR8327_PORT_SPEED_100) {
		value = FAL_SPEED_100;
	} else if(port_cfg->speed == AR8327_PORT_SPEED_1000) {
		value = FAL_SPEED_1000;
	} else {
		value = FAL_SPEED_1000;
	}
	fal_port_speed_set(priv->device_id, port, value);
	/*enable mac at last*/
	udelay(800);
	fal_port_rxmac_status_set(priv->device_id, port, A_TRUE);
	fal_port_txmac_status_set(priv->device_id, port, A_TRUE);
}

int
qca_ar8327_hw_init(struct qca_phy_priv *priv)
{
	struct ar8327_platform_data *plat_data;
	a_uint32_t i = 0;
	a_uint32_t value = 0;

	plat_data = priv->phy->dev.platform_data;
	if (plat_data == NULL) {
		return -EINVAL;
	}

	/*Before switch software reset, disable PHY and clear MAC PAD*/
	qca_ar8327_phy_linkdown(priv->device_id);
	qca_mac_disable(priv->device_id);
	udelay(10);

	qca_ar8327_set_plat_data_cfg(priv, plat_data);

	/*mac reset*/
	priv->mii_write(priv->device_id, AR8327_REG_MAC_SFT_RST, 0x3fff);

	msleep(100);

	/*First software reset S17 chip*/
	qca_ar8327_sw_soft_reset(priv);
	udelay(1000);

	/*After switch software reset, need disable all ports' MAC with 1000M FULL*/
	qca_switch_set_mac_force(priv);

	qca_ar8327_set_pad_cfg(priv, plat_data);

	value = priv->mii_read(priv->device_id, AR8327_REG_MODULE_EN);
	value &= ~AR8327_REG_MODULE_EN_QM_ERR;
	value &= ~AR8327_REG_MODULE_EN_LOOKUP_ERR;
	priv->mii_write(priv->device_id, AR8327_REG_MODULE_EN, value);

	qca_switch_init(priv->device_id);

#ifndef BOARD_AR71XX
	value = qca_ar8327_get_pwr_sel(priv, plat_data);
	priv->mii_write(priv->device_id, AR8327_REG_PAD_MAC_PWR_SEL, value);
#endif

	msleep(1000);

	for (i = 0; i < AR8327_NUM_PORTS; i++) {
		qca_ar8327_port_init(priv, i);
	}

	qca_ar8327_phy_enable(priv);

	return 0;
}
#endif

#if defined(IN_SWCONFIG)
#ifndef BOARD_AR71XX
static int
qca_ar8327_sw_get_reg_val(struct switch_dev *dev,
                                    int reg, int *val)
{
	return 0;
}

static int
qca_ar8327_sw_set_reg_val(struct switch_dev *dev,
                                    int reg, int val)
{
	return 0;
}
#endif
static struct switch_attr qca_ar8327_globals[] = {
	{
		.name = "enable_vlan",
		.description = "Enable 8021q VLAN",
		.type = SWITCH_TYPE_INT,
		.set = qca_ar8327_sw_set_vlan,
		.get = qca_ar8327_sw_get_vlan,
		.max = 1
	},{
		.name = "max_frame_size",
		.description = "Set Max frame Size Of Mac",
		.type = SWITCH_TYPE_INT,
		.set = qca_ar8327_sw_set_max_frame_size,
		.get = qca_ar8327_sw_get_max_frame_size,
		.max = 9018
	},
	{
		.name = "reset_mibs",
		.description = "Reset All MIB Counters",
		.type = SWITCH_TYPE_NOVAL,
		.set = qca_ar8327_sw_set_reset_mibs,
	},
	{
		.name = "flush_arl",
		.description = "Flush All ARL table",
		.type = SWITCH_TYPE_NOVAL,
		.set = qca_ar8327_sw_atu_flush,
	},
	{
		.name = "dump_arl",
		.description = "Dump All ARL table",
		.type = SWITCH_TYPE_STRING,
		.get = qca_ar8327_sw_atu_dump,
	},
	{
		.name = "switch_ext",
		.description = "Switch extended configuration",
		.type = SWITCH_TYPE_EXT,
		.set = qca_ar8327_sw_switch_ext,
	},
};

static struct switch_attr qca_ar8327_port[] = {
	{
		.name = "reset_mib",
		.description = "Reset Mib Counters",
		.type = SWITCH_TYPE_NOVAL,
		.set = qca_ar8327_sw_set_port_reset_mib,
	},
	{
		.name = "mib",
		.description = "Get Mib Counters",
		.type = SWITCH_TYPE_STRING,
		.set = NULL,
		.get = qca_ar8327_sw_get_port_mib,
	},
};

static struct switch_attr qca_ar8327_vlan[] = {
	{
		.name = "vid",
		.description = "Configure Vlan Id",
		.type = SWITCH_TYPE_INT,
		.set = qca_ar8327_sw_set_vid,
		.get = qca_ar8327_sw_get_vid,
		.max = 4094,
	},
};

const struct switch_dev_ops qca_ar8327_sw_ops = {
	.attr_global = {
		.attr = qca_ar8327_globals,
		.n_attr = ARRAY_SIZE(qca_ar8327_globals),
	},
	.attr_port = {
		.attr = qca_ar8327_port,
		.n_attr = ARRAY_SIZE(qca_ar8327_port),
	},
	.attr_vlan = {
		.attr = qca_ar8327_vlan,
		.n_attr = ARRAY_SIZE(qca_ar8327_vlan),
	},
	.get_port_pvid = qca_ar8327_sw_get_pvid,
	.set_port_pvid = qca_ar8327_sw_set_pvid,
	.get_vlan_ports = qca_ar8327_sw_get_ports,
	.set_vlan_ports = qca_ar8327_sw_set_ports,
	.apply_config = qca_ar8327_sw_hw_apply,
	.reset_switch = qca_ar8327_sw_reset_switch,
	.get_port_link = qca_ar8327_sw_get_port_link,
#ifndef BOARD_AR71XX
	.get_reg_val = qca_ar8327_sw_get_reg_val,
	.set_reg_val = qca_ar8327_sw_set_reg_val,
#endif
};
#endif

#define SSDK_MIB_CHANGE_WQ

static int
qca_phy_mib_task(struct qca_phy_priv *priv)
{
	qca_ar8327_sw_mib_task(priv);
	return 0;
}

static void
qca_phy_mib_work_task(struct work_struct *work)
{
	struct qca_phy_priv *priv = container_of(work, struct qca_phy_priv,
                                            mib_dwork.work);

	mutex_lock(&priv->mib_lock);

    qca_phy_mib_task(priv);

	mutex_unlock(&priv->mib_lock);
#ifndef SSDK_MIB_CHANGE_WQ
	schedule_delayed_work(&priv->mib_dwork,
			      msecs_to_jiffies(QCA_PHY_MIB_WORK_DELAY));
#else
	queue_delayed_work_on(0, system_long_wq, &priv->mib_dwork,
					msecs_to_jiffies(QCA_PHY_MIB_WORK_DELAY));
#endif
}

int
qca_phy_mib_work_start(struct qca_phy_priv *priv)
{
	mutex_init(&priv->mib_lock);
	if(SW_OK != fal_mib_counter_alloc(priv->device_id, &priv->mib_counters)){
		SSDK_ERROR("Memory allocation fail\n");
		return -ENOMEM;
	}

	INIT_DELAYED_WORK(&priv->mib_dwork, qca_phy_mib_work_task);
#ifndef SSDK_MIB_CHANGE_WQ
	schedule_delayed_work(&priv->mib_dwork,
			               msecs_to_jiffies(QCA_PHY_MIB_WORK_DELAY));
#else
	queue_delayed_work_on(0, system_long_wq, &priv->mib_dwork,
					msecs_to_jiffies(QCA_PHY_MIB_WORK_DELAY));
#endif

	return 0;
}

void
qca_phy_mib_work_stop(struct qca_phy_priv *priv)
{
	if(!priv)
		return;
	if(priv->mib_counters)
		kfree(priv->mib_counters);
	cancel_delayed_work_sync(&priv->mib_dwork);
}

#define SSDK_QM_CHANGE_WQ

static void
qm_err_check_work_task_polling(struct work_struct *work)
{
	struct qca_phy_priv *priv = container_of(work, struct qca_phy_priv,
                                            qm_dwork_polling.work);

	mutex_lock(&priv->qm_lock);

	qca_ar8327_sw_mac_polling_task(priv);

	mutex_unlock(&priv->qm_lock);

	#ifndef SSDK_QM_CHANGE_WQ
	schedule_delayed_work(&priv->qm_dwork,
							msecs_to_jiffies(QCA_QM_WORK_DELAY));
	#else
	queue_delayed_work_on(0, system_long_wq, &priv->qm_dwork_polling,
							msecs_to_jiffies(QCA_QM_WORK_DELAY));
	#endif
}

static int config_gpio(a_uint32_t  gpio_num)
{
	int  error;

	if (gpio_is_valid(gpio_num))
	{
		error = gpio_request_one(gpio_num, GPIOF_IN, "linkchange");
		if (error < 0) {
			SSDK_ERROR("gpio request faild \n");
			return -1;
		}
		gpio_set_debounce(gpio_num, 60000);
	}
	else
	{
		SSDK_ERROR("gpio is invalid\n");
		return -1;
	}

	return 0;
}
static int qca_link_polling_select(struct qca_phy_priv *priv)
{
	struct device_node *np = NULL;
	const __be32 *link_polling_required, *link_intr_gpio;
	a_int32_t len;

	if (priv->ess_switch_flag == A_TRUE)
		np = priv->of_node;
	else if(priv->version == QCA_VER_AR8337 || priv->version == QCA_VER_AR8327)
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4,9,0))
		np = priv->phy->mdio.dev.of_node;
#else
		np = priv->phy->dev.of_node;
#endif
	else
		SSDK_ERROR("cannot find np node!\n");

	if(!np)
	{
		SSDK_ERROR("np is null !\n");
		return -1;
	}

	link_polling_required = of_get_property(np, "link-polling-required", &len);
	if (!link_polling_required )
	{
		SSDK_INFO("link-polling-required node does not exist\n");
		return -1;
	}
	priv->link_polling_required  = be32_to_cpup(link_polling_required);
	if(!priv->link_polling_required)
	{
		link_intr_gpio = of_get_property(np, "link-intr-gpio", &len);
		if (!link_intr_gpio )
		{
			SSDK_ERROR("cannot find link-intr-gpio node\n");
			return -1;
		}
		if(config_gpio(be32_to_cpup(link_intr_gpio)))
			return -1;
		priv->link_interrupt_no = gpio_to_irq (be32_to_cpup(link_intr_gpio));
		SSDK_INFO("the interrupt number is:%x\n",priv->link_interrupt_no);
	}

	return 0;
}

int
qm_err_check_work_start(struct qca_phy_priv *priv)
{
	if (priv->version == QCA_VER_HPPE)
		return 0;

	/*Only valid for S17c chip*/
	if (priv->version != QCA_VER_AR8337 &&
		priv->version != QCA_VER_AR8327 &&
		priv->version != QCA_VER_DESS)
		return -1;

	mutex_init(&priv->qm_lock);
	INIT_DELAYED_WORK(&priv->qm_dwork_polling, qm_err_check_work_task_polling);
	#ifndef SSDK_MIB_CHANGE_WQ
	schedule_delayed_work(&priv->qm_dwork_polling,
							msecs_to_jiffies(QCA_QM_WORK_DELAY));
	#else
	queue_delayed_work_on(0, system_long_wq, &priv->qm_dwork_polling,
							msecs_to_jiffies(QCA_QM_WORK_DELAY));
	#endif

	return 0;
}

void
qm_err_check_work_stop(struct qca_phy_priv *priv)
{
	/*Only valid for S17c chip*/
	if (priv->version != QCA_VER_AR8337 &&
		priv->version != QCA_VER_AR8327 &&
		priv->version != QCA_VER_DESS) return;

		cancel_delayed_work_sync(&priv->qm_dwork_polling);

}
#ifdef DESS
static void
dess_rgmii_mac_work_task(struct work_struct *work)
{
	struct qca_phy_priv *priv = container_of(work, struct qca_phy_priv,
                                            rgmii_dwork.work);

	mutex_lock(&priv->rgmii_lock);

	dess_rgmii_sw_mac_polling_task(priv);

	mutex_unlock(&priv->rgmii_lock);

	schedule_delayed_work(&priv->rgmii_dwork, msecs_to_jiffies(QCA_RGMII_WORK_DELAY));
}

int
dess_rgmii_mac_work_start(struct qca_phy_priv *priv)
{
	mutex_init(&priv->rgmii_lock);

	INIT_DELAYED_WORK(&priv->rgmii_dwork, dess_rgmii_mac_work_task);

	schedule_delayed_work(&priv->rgmii_dwork, msecs_to_jiffies(QCA_RGMII_WORK_DELAY));

	return 0;
}

void
dess_rgmii_mac_work_stop(struct qca_phy_priv *priv)
{
	cancel_delayed_work_sync(&priv->rgmii_dwork);
}
#endif

void
qca_mac_sw_sync_port_status_init(a_uint32_t dev_id)
{
	a_uint32_t port_id;

	for (port_id = 1; port_id < SW_MAX_NR_PORT; port_id ++) {

		qca_phy_priv_global[dev_id]->port_old_link[port_id - 1] = 0;
		qca_phy_priv_global[dev_id]->port_old_speed[port_id - 1] = FAL_SPEED_BUTT;
		qca_phy_priv_global[dev_id]->port_old_duplex[port_id - 1] = FAL_DUPLEX_BUTT;
		qca_phy_priv_global[dev_id]->port_old_tx_flowctrl[port_id - 1] = A_TRUE;
		qca_phy_priv_global[dev_id]->port_old_rx_flowctrl[port_id - 1] = A_TRUE;
		qca_phy_priv_global[dev_id]->port_tx_flowctrl_forcemode[port_id - 1] = A_FALSE;
		qca_phy_priv_global[dev_id]->port_rx_flowctrl_forcemode[port_id - 1] = A_FALSE;
	}
}
void
qca_mac_sw_sync_work_task(struct work_struct *work)
{
	adpt_api_t *p_adpt_api;

	struct qca_phy_priv *priv = container_of(work, struct qca_phy_priv,
					mac_sw_sync_dwork.work);

	mutex_lock(&priv->mac_sw_sync_lock);

	 if((p_adpt_api = adpt_api_ptr_get(priv->device_id)) != NULL) {
		if (NULL == p_adpt_api->adpt_port_polling_sw_sync_set)
			return;
		p_adpt_api->adpt_port_polling_sw_sync_set(priv);
	}

	mutex_unlock(&priv->mac_sw_sync_lock);

	schedule_delayed_work(&priv->mac_sw_sync_dwork,
					msecs_to_jiffies(QCA_MAC_SW_SYNC_WORK_DELAY));
}

int
qca_mac_sw_sync_work_start(struct qca_phy_priv *priv)
{
	if (priv->version != QCA_VER_HPPE)
		return 0;

	qca_mac_sw_sync_port_status_init(priv->device_id);

	mutex_init(&priv->mac_sw_sync_lock);

	INIT_DELAYED_WORK(&priv->mac_sw_sync_dwork,
					qca_mac_sw_sync_work_task);
	schedule_delayed_work(&priv->mac_sw_sync_dwork,
					msecs_to_jiffies(QCA_MAC_SW_SYNC_WORK_DELAY));

	return 0;
}

void
qca_mac_sw_sync_work_stop(struct qca_phy_priv *priv)
{
	if (priv->version != QCA_VER_HPPE)
		return;

	cancel_delayed_work_sync(&priv->mac_sw_sync_dwork);
}

int
qca_phy_id_chip(struct qca_phy_priv *priv)
{
	a_uint32_t value, version;

	value = qca_ar8216_mii_read(priv->device_id, AR8327_REG_CTRL);
	version = value & (AR8327_CTRL_REVISION |
                AR8327_CTRL_VERSION);
	priv->version = (version & AR8327_CTRL_VERSION) >>
                           AR8327_CTRL_VERSION_S;
	priv->revision = (version & AR8327_CTRL_REVISION);

    if((priv->version == QCA_VER_AR8327) ||
       (priv->version == QCA_VER_AR8337) ||
       (priv->version == QCA_VER_AR8227)) {
		return 0;

    } else {
		SSDK_ERROR("unsupported QCA device\n");
		return -ENODEV;
	}
}

#if defined(IN_SWCONFIG)
static int qca_switchdev_register(struct qca_phy_priv *priv)
{
	struct switch_dev *sw_dev;
	int ret = SW_OK;
	sw_dev = &priv->sw_dev;

	sw_dev->ops = &qca_ar8327_sw_ops;
	sw_dev->name = "QCA AR8327 AR8337";
	sw_dev->alias = "QCA AR8327 AR8337";
	sw_dev->vlans = AR8327_MAX_VLANS;
	sw_dev->ports = AR8327_NUM_PORTS;

	ret = register_switch(sw_dev, NULL);
	if (ret != SW_OK) {
		SSDK_ERROR("register_switch failed for %s\n", sw_dev->name);
		return ret;
	}

	return ret;
}
#endif

static int
qca_phy_config_init(struct phy_device *pdev)
{
	struct qca_phy_priv *priv = pdev->priv;
	int ret = 0;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4,9,0))
	if (pdev->mdio.addr != 0) {
#else
	if (pdev->addr != 0) {
#endif
        pdev->supported |= SUPPORTED_1000baseT_Full;
        pdev->advertising |= ADVERTISED_1000baseT_Full;
		#ifndef BOARD_AR71XX
		#if defined(CONFIG_OF) && (LINUX_VERSION_CODE >= KERNEL_VERSION(3,14,0))
		ssdk_phy_rgmii_set(priv);
		#endif
		#endif
		return 0;
	}

	if (priv == NULL)
		return -ENOMEM;

	priv->phy = pdev;
	ret = qca_phy_id_chip(priv);
	if (ret != 0) {
		return ret;
	}

	priv->mii_read = qca_ar8216_mii_read;
	priv->mii_write = qca_ar8216_mii_write;
	priv->phy_write = qca_ar8327_phy_write;
	priv->phy_read = qca_ar8327_phy_read;
	priv->phy_dbg_write = qca_ar8327_phy_dbg_write;
	priv->phy_dbg_read = qca_ar8327_phy_dbg_read;
	priv->phy_mmd_write = qca_ar8327_mmd_write;
	priv->ports = AR8327_NUM_PORTS;

	ret = qca_link_polling_select(priv);
	if(ret)
		priv->link_polling_required = 1;
	pdev->priv = priv;
	pdev->supported |= SUPPORTED_1000baseT_Full;
	pdev->advertising |= ADVERTISED_1000baseT_Full;

#if defined(IN_SWCONFIG)
	ret = qca_switchdev_register(priv);
	if (ret != SW_OK) {
		return ret;
	}
#endif
	priv->qca_ssdk_sw_dev_registered = A_TRUE;

	ret = qca_ar8327_hw_init(priv);
	if (ret != 0) {
		return ret;
	}

	qca_phy_mib_work_start(priv);

	if(priv->link_polling_required)
	{
		SSDK_INFO("polling is selected\n");
		ret = qm_err_check_work_start(priv);
		if (ret != 0)
		{
			SSDK_ERROR("qm_err_check_work_start failed for chip 0x%02x%02x\n", priv->version, priv->revision);
			return ret;
		}
	}
	else
	{
		SSDK_INFO("interrupt is selected\n");
		priv->interrupt_flag = IRQF_TRIGGER_LOW;
		ret = qca_intr_init(priv);
		if(ret)
			SSDK_ERROR("the interrupt init faild !\n");
	}

	return ret;
}

#if defined(DESS) || defined(HPPE) || defined (ISISC) || defined (ISIS)
static int ssdk_switch_register(a_uint32_t dev_id)
{
	struct qca_phy_priv *priv;
	int ret = 0;
	a_uint32_t chip_id = 0;
	priv = qca_phy_priv_global[dev_id];

	priv->mii_read = qca_ar8216_mii_read;
	priv->mii_write = qca_ar8216_mii_write;
	priv->phy_write = qca_ar8327_phy_write;
	priv->phy_read = qca_ar8327_phy_read;
	priv->phy_dbg_write = qca_ar8327_phy_dbg_write;
	priv->phy_dbg_read = qca_ar8327_phy_dbg_read;
	priv->phy_mmd_write = qca_ar8327_mmd_write;
	priv->ports = AR8327_NUM_PORTS;

	if (fal_reg_get(dev_id, 0, (a_uint8_t *)&chip_id, 4) == SW_OK) {
		priv->version = ((chip_id >> 8) & 0xff);
		priv->revision = (chip_id & 0xff);
		SSDK_INFO("Chip version 0x%02x%02x\n", priv->version, priv->revision);
	}

	mutex_init(&priv->reg_mutex);

#if defined(IN_SWCONFIG)
	ret = qca_switchdev_register(priv);
	if (ret != SW_OK) {
		return ret;
	}
#endif

	priv->qca_ssdk_sw_dev_registered = A_TRUE;
	ret = qca_phy_mib_work_start(qca_phy_priv_global[dev_id]);
	if (ret != 0) {
			SSDK_ERROR("qca_phy_mib_work_start failed for chip 0x%02x%02x\n", priv->version, priv->revision);
			return ret;
	}
	ret = qca_link_polling_select(priv);
	if(ret)
		priv->link_polling_required = 1;
	if(priv->link_polling_required)
	{
		SSDK_INFO("polling is selected\n");
		ret = qm_err_check_work_start(priv);
		if (ret != 0)
		{
			SSDK_ERROR("qm_err_check_work_start failed for chip 0x%02x%02x\n", priv->version, priv->revision);
			return ret;
		}
	}
	else
	{
		SSDK_INFO("interrupt is selected\n");
		priv->interrupt_flag = IRQF_TRIGGER_MASK;
		ret = qca_intr_init(priv);
		if(ret)
		{
			SSDK_ERROR("the interrupt init faild !\n");
			return ret;
		}
	}

	#if 0
	#ifdef DESS
	if ((ssdk_dt_global.mac_mode == PORT_WRAPPER_SGMII0_RGMII5)
		||(ssdk_dt_global.mac_mode == PORT_WRAPPER_SGMII1_RGMII5)
		||(ssdk_dt_global.mac_mode == PORT_WRAPPER_SGMII0_RGMII4)
		||(ssdk_dt_global.mac_mode == PORT_WRAPPER_SGMII1_RGMII4)
		||(ssdk_dt_global.mac_mode == PORT_WRAPPER_SGMII4_RGMII4)) {
		ret = dess_rgmii_mac_work_start(priv);
		if (ret != 0) {
			SSDK_ERROR("dess_rgmii_mac_work_start failed for chip 0x%02x%02x\n", priv->version, priv->revision);
			return ret;
		}
	}
	#endif
	#endif
	#ifdef HPPE
	ret = qca_mac_sw_sync_work_start(priv);
	if (ret != 0) {
			SSDK_ERROR("qca_mac_sw_sync_work_start failed for chip 0x%02x%02x\n", priv->version, priv->revision);
			return ret;
	}
	#endif

	return 0;

}

static int ssdk_switch_unregister(a_uint32_t dev_id)
{
	qca_phy_mib_work_stop(qca_phy_priv_global[dev_id]);
	qm_err_check_work_stop(qca_phy_priv_global[dev_id]);
	#ifdef HPPE
	qca_mac_sw_sync_work_stop(qca_phy_priv_global[dev_id]);
	#endif

	#if defined(IN_SWCONFIG)
	unregister_switch(&qca_phy_priv_global[dev_id]->sw_dev);
	#endif
	return 0;
}
#endif

static int
qca_phy_read_status(struct phy_device *pdev)
{
	struct qca_phy_priv *priv = pdev->priv;
	a_uint32_t port_status;
	a_uint32_t port_speed;
	int ret = 0, addr = 0;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4,9,0))
	addr = pdev->mdio.addr;
#else
	addr = pdev->addr;
#endif
	if (addr != 0) {
		mutex_lock(&priv->reg_mutex);
		ret = genphy_read_status(pdev);
		mutex_unlock(&priv->reg_mutex);
		return ret;
	}

	mutex_lock(&priv->reg_mutex);
	port_status = priv->mii_read(priv->device_id, AR8327_REG_PORT_STATUS(addr));
	mutex_unlock(&priv->reg_mutex);

	pdev->link = 1;
	if (port_status & AR8327_PORT_STATUS_LINK_AUTO) {
		pdev->link = !!(port_status & AR8327_PORT_STATUS_LINK_UP);
		if (pdev->link == 0) {
			return ret;
		}
	}

	port_speed = (port_status & AR8327_PORT_STATUS_SPEED) >>
		            AR8327_PORT_STATUS_SPEED_S;

	switch (port_speed) {
		case AR8327_PORT_SPEED_10M:
			pdev->speed = SPEED_10;
			break;
		case AR8327_PORT_SPEED_100M:
			pdev->speed = SPEED_100;
			break;
		case AR8327_PORT_SPEED_1000M:
			pdev->speed = SPEED_1000;
			break;
		default:
			pdev->speed = 0;
			break;
	}

	if(port_status & AR8327_PORT_STATUS_DUPLEX) {
		pdev->duplex = DUPLEX_FULL;
	} else {
		pdev->duplex = DUPLEX_HALF;
	}

	pdev->state = PHY_RUNNING;
	netif_carrier_on(pdev->attached_dev);
	pdev->adjust_link(pdev->attached_dev);

	return ret;
}

static int
qca_phy_config_aneg(struct phy_device *pdev)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4,9,0))
	if (pdev->mdio.addr != 0) {
#else
	if (pdev->addr != 0) {
#endif
		return genphy_config_aneg(pdev);
	}

	return 0;
}

static int
qca_phy_probe(struct phy_device *pdev)
{
	struct qca_phy_priv *priv;
	int ret;

	priv = kzalloc(sizeof(struct qca_phy_priv), GFP_KERNEL);
	if (priv == NULL) {
		return -ENOMEM;
	}

	pdev->priv = priv;
	priv->phy = pdev;
	mutex_init(&priv->reg_mutex);

	ret = qca_phy_id_chip(priv);
	return ret;
}

static void
qca_phy_remove(struct phy_device *pdev)
{
	struct qca_phy_priv *priv = pdev->priv;
	int addr;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4,9,0))
	addr = pdev->mdio.addr;
#else
	addr = pdev->addr;
#endif

	if ((addr == 0) && priv && (priv->ports != 0)) {
		qca_phy_mib_work_stop(priv);
		qm_err_check_work_stop(priv);
#if defined(IN_SWCONFIG)
		if (priv->sw_dev.name != NULL)
			unregister_switch(&priv->sw_dev);
#endif
	}

	if (priv) {
		kfree(priv);
    }
}

static struct phy_driver qca_phy_driver = {
    .name		= "QCA AR8216 AR8236 AR8316 AR8327 AR8337",
	.phy_id		= 0x004d0000,
	.phy_id_mask= 0xffff0000,
	.probe		= qca_phy_probe,
	.remove		= qca_phy_remove,
	.config_init= &qca_phy_config_init,
	.config_aneg= &qca_phy_config_aneg,
	.read_status= &qca_phy_read_status,
	.features	= PHY_BASIC_FEATURES,
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4,9,0))
	.mdiodrv.driver		= { .owner = THIS_MODULE },
#else
	.driver		= { .owner = THIS_MODULE },
#endif
};

#ifndef BOARD_AR71XX
#if defined(CONFIG_OF) && (LINUX_VERSION_CODE >= KERNEL_VERSION(3,14,0))
struct reset_control *ess_rst = NULL;
struct reset_control *ess_mac_clock_disable[5] = {NULL,NULL,NULL,NULL,NULL};

void ssdk_ess_reset(void)
{
	if (!ess_rst)
		return;
	reset_control_assert(ess_rst);
	mdelay(10);
	reset_control_deassert(ess_rst);
	mdelay(100);
}

char ssdk_driver_name[] = "ess_ssdk";

static int ssdk_probe(struct platform_device *pdev)
{
	ess_rst = devm_reset_control_get(&pdev->dev, "ess_rst");
	ess_mac_clock_disable[0] = devm_reset_control_get(&pdev->dev, "ess_mac1_clk_dis");
	ess_mac_clock_disable[1] = devm_reset_control_get(&pdev->dev, "ess_mac2_clk_dis");
	ess_mac_clock_disable[2] = devm_reset_control_get(&pdev->dev, "ess_mac3_clk_dis");
	ess_mac_clock_disable[3] = devm_reset_control_get(&pdev->dev, "ess_mac4_clk_dis");
	ess_mac_clock_disable[4] = devm_reset_control_get(&pdev->dev, "ess_mac5_clk_dis");

	if (IS_ERR(ess_rst)) {
		SSDK_INFO("ess_rst doesn't exist!\n");
		return 0;
	}
	if (!ess_mac_clock_disable[0]) {
		SSDK_ERROR("ess_mac1_clock_disable fail!\n");
		return -1;
	}
	if (!ess_mac_clock_disable[1]) {
		SSDK_ERROR("ess_mac2_clock_disable fail!\n");
		return -1;
	}
	if (!ess_mac_clock_disable[2]) {
		SSDK_ERROR("ess_mac3_clock_disable fail!\n");
		return -1;
	}
	if (!ess_mac_clock_disable[3]) {
		SSDK_ERROR("ess_mac4_clock_disable fail!\n");
		return -1;
	}
	if (!ess_mac_clock_disable[4]) {
		SSDK_ERROR("ess_mac5_clock_disable fail!\n");
		return -1;
	}

	reset_control_assert(ess_rst);
	mdelay(10);
	reset_control_deassert(ess_rst);
	mdelay(100);
	SSDK_INFO("reset ok in probe!\n");
	return 0;
}

static const struct of_device_id ssdk_of_mtable[] = {
        {.compatible = "qcom,ess-switch" },
        {}
};

static struct platform_driver ssdk_driver = {
        .driver = {
                .name    = ssdk_driver_name,
                .owner   = THIS_MODULE,
                .of_match_table = ssdk_of_mtable,
        },
        .probe    = ssdk_probe,
};
#endif
#endif
#ifdef DESS
static u32 phy_t_status = 0;
void ssdk_malibu_psgmii_and_dakota_dess_reset(a_uint32_t dev_id, a_uint32_t first_phy_addr)
{
#ifndef BOARD_AR71XX
#if defined(CONFIG_OF) && (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 14, 0))
	int m = 0, n = 0;
	a_uint32_t psgmii_phy_addr;

	psgmii_phy_addr = first_phy_addr + 5;

	/*reset Malibu PSGMII and Dakota ESS start*/
	qca_ar8327_phy_write(dev_id, psgmii_phy_addr, 0x0, 0x005b);/*fix phy psgmii RX 20bit*/
	qca_ar8327_phy_write(dev_id, psgmii_phy_addr, 0x0, 0x001b);/*reset phy psgmii*/
	qca_ar8327_phy_write(dev_id, psgmii_phy_addr, 0x0, 0x005b);/*release reset phy psgmii*/
	/* mdelay(100); this 100ms be replaced with below malibu psgmii calibration process*/
	/*check malibu psgmii calibration done start*/
	n = 0;
	while (n < 100) {
		u16 status;
		status = qca_phy_mmd_read(dev_id, psgmii_phy_addr, 1, 0x28);
		if (status & BIT(0))
			break;
		mdelay(10);
		n++;
	}
#ifdef PSGMII_DEBUG
	if (n >= 100)
		SSDK_INFO("MALIBU PSGMII PLL_VCO_CALIB NOT READY\n");
#endif
	mdelay(50);
	/*check malibu psgmii calibration done end..*/
	qca_ar8327_phy_write(dev_id, psgmii_phy_addr, 0x1a, 0x2230);/*freeze phy psgmii RX CDR*/

	ssdk_ess_reset();
	/*check dakota psgmii calibration done start*/
	m = 0;
	while (m < 100) {
		u32 status = 0;
		qca_psgmii_reg_read(dev_id, 0xa0, (a_uint8_t *)&status, 4);
		if (status & BIT(0))
			break;
		mdelay(10);
		m++;
	}
#ifdef PSGMII_DEBUG
	if (m >= 100)
		SSDK_INFO("DAKOTA PSGMII PLL_VCO_CALIB NOT READY\n");
#endif
	mdelay(50);
	/*check dakota psgmii calibration done end..*/
	qca_ar8327_phy_write(dev_id, psgmii_phy_addr, 0x1a, 0x3230);/*relesae phy psgmii RX CDR*/
	qca_ar8327_phy_write(dev_id, psgmii_phy_addr, 0x0, 0x005f);/*release phy psgmii RX 20bit*/
	mdelay(200);
#endif
#endif
	/*reset Malibu PSGMII and Dakota ESS end*/
	return;
}

static void ssdk_psgmii_phy_testing_printf(a_uint32_t phy, u32 tx_ok, u32 rx_ok,
				u32 tx_counter_error, u32 rx_counter_error)
{
	SSDK_INFO("tx_ok = 0x%x, rx_ok = 0x%x, tx_counter_error = 0x%x, rx_counter_error = 0x%x\n",
			tx_ok, rx_ok, tx_counter_error, rx_counter_error);
	if (tx_ok== 0x3000 && tx_counter_error == 0)
		SSDK_INFO("PHY %d single PSGMII test pass\n", phy);
	else
		SSDK_ERROR("PHY %d single PSGMII test fail\n", phy);
	return;

}
static void ssdk_psgmii_all_phy_testing_printf(a_uint32_t phy, u32 tx_ok, u32 rx_ok,
				u32 tx_counter_error, u32 rx_counter_error)
{
	SSDK_INFO("tx_ok = 0x%x, rx_ok = 0x%x, tx_counter_error = 0x%x, rx_counter_error = 0x%x\n",
			tx_ok, rx_ok, tx_counter_error, rx_counter_error);
	if (tx_ok== 0x3000 && tx_counter_error == 0)
		SSDK_INFO("PHY %d all PSGMII test pass\n", phy);
	else
		SSDK_ERROR("PHY %d all PSGMII test fail\n", phy);
	return;

}
void ssdk_psgmii_single_phy_testing(a_uint32_t dev_id, a_uint32_t phy, a_bool_t enable)
{
	int j = 0;

	u32 tx_counter_ok, tx_counter_error;
	u32 rx_counter_ok, rx_counter_error;
	u32 tx_counter_ok_high16;
	u32 rx_counter_ok_high16;
	u32 tx_ok, rx_ok;
	qca_ar8327_phy_write(dev_id, phy, 0x0, 0x9000);
	qca_ar8327_phy_write(dev_id, phy, 0x0, 0x4140);
	j = 0;
	while (j < 100) {
		u16 status = 0;
		qca_ar8327_phy_read(dev_id, phy, 0x11, &status);
		if (status & (1 << 10))
			break;
		mdelay(10);
		j++;
	}
	/*add a 300ms delay as qm polling task existing*/
	if (enable == A_TRUE)
		mdelay(300);

	/*enable check*/
	qca_phy_mmd_write(dev_id, phy, 7, 0x8029, 0x0000);
	qca_phy_mmd_write(dev_id, phy, 7, 0x8029, 0x0003);

	/*start traffic*/
	qca_phy_mmd_write(dev_id, phy, 7, 0x8020, 0xa000);
	mdelay(200);

	/*check counter*/
	tx_counter_ok = qca_phy_mmd_read(dev_id, phy, 7, 0x802e);
	tx_counter_ok_high16 = qca_phy_mmd_read(dev_id, phy, 7, 0x802d);
	tx_counter_error = qca_phy_mmd_read(dev_id, phy, 7, 0x802f);
	rx_counter_ok = qca_phy_mmd_read(dev_id, phy, 7, 0x802b);
	rx_counter_ok_high16 = qca_phy_mmd_read(dev_id, phy, 7, 0x802a);
	rx_counter_error = qca_phy_mmd_read(dev_id, phy, 7, 0x802c);
	tx_ok = tx_counter_ok + (tx_counter_ok_high16<<16);
	rx_ok = rx_counter_ok + (rx_counter_ok_high16<<16);
	if (tx_ok== 0x3000 && tx_counter_error == 0) {
		/*success*/
		phy_t_status &= (~(1<<phy));
	} else {
		phy_t_status |= (1<<phy);
	}

	if (enable == A_TRUE)
		ssdk_psgmii_phy_testing_printf(phy, tx_ok, rx_ok,
				tx_counter_error, rx_counter_error);

	qca_ar8327_phy_write(dev_id, phy, 0x0, 0x1840);
}

void ssdk_psgmii_all_phy_testing(a_uint32_t dev_id, a_uint32_t first_phy_addr, a_bool_t enable)
{
	int j = 0;
	a_uint32_t phy = 0;
	qca_ar8327_phy_write(dev_id, 0x1f, 0x0, 0x9000);
	qca_ar8327_phy_write(dev_id, 0x1f, 0x0, 0x4140);
	j = 0;
	while (j < 100) {
		for (phy = first_phy_addr; phy < first_phy_addr + 5; phy++) {
			u16 status = 0;
			qca_ar8327_phy_read(dev_id, phy, 0x11, &status);
			if (!(status & (1 << 10)))
				break;
		}

		if (phy >= 5)
			break;
		mdelay(10);
		j++;
	}
	/*add a 300ms delay as qm polling task existing*/
	if (enable == A_TRUE)
		mdelay(300);

	/*enable check*/
	qca_phy_mmd_write(dev_id, 0x1f, 7, 0x8029, 0x0000);
	qca_phy_mmd_write(dev_id, 0x1f, 7, 0x8029, 0x0003);

	/*start traffic*/
	qca_phy_mmd_write(dev_id, 0x1f, 7, 0x8020, 0xa000);
	mdelay(200);
	for (phy = first_phy_addr; phy < first_phy_addr + 5; phy++) {
		u32 tx_counter_ok, tx_counter_error;
		u32 rx_counter_ok, rx_counter_error;
		u32 tx_counter_ok_high16;
		u32 rx_counter_ok_high16;
		u32 tx_ok, rx_ok;
		/*check counter*/
		tx_counter_ok = qca_phy_mmd_read(dev_id, phy, 7, 0x802e);
		tx_counter_ok_high16 = qca_phy_mmd_read(dev_id, phy, 7, 0x802d);
		tx_counter_error = qca_phy_mmd_read(dev_id, phy, 7, 0x802f);
		rx_counter_ok = qca_phy_mmd_read(dev_id, phy, 7, 0x802b);
		rx_counter_ok_high16 = qca_phy_mmd_read(dev_id, phy, 7, 0x802a);
		rx_counter_error = qca_phy_mmd_read(dev_id, phy, 7, 0x802c);
		tx_ok = tx_counter_ok + (tx_counter_ok_high16<<16);
		rx_ok = rx_counter_ok + (rx_counter_ok_high16<<16);
		if (tx_ok== 0x3000 && tx_counter_error == 0) {
			/*success*/
			phy_t_status &= (~(1<<(phy+8)));
		} else {
			phy_t_status |= (1<<(phy+8));
		}

		if (enable == A_TRUE)
			ssdk_psgmii_all_phy_testing_printf(phy, tx_ok,
					rx_ok,
					tx_counter_error, rx_counter_error);
		}
	if (enable == A_TRUE)
		SSDK_INFO("PHY final test result: 0x%x \r\n",phy_t_status);

}
void ssdk_psgmii_self_test(a_uint32_t dev_id, a_bool_t enable, a_uint32_t times,
				a_uint32_t *result)
{
	int i = 0;
	u32 value = 0;
	a_uint32_t port_bmp[SW_MAX_NR_DEV] = {0};
	a_uint32_t port_id = 0, first_phy_addr = 0, phy = 0;

	port_bmp[dev_id] = qca_ssdk_phy_type_port_bmp_get(dev_id, MALIBU_PHY_CHIP);

	for (port_id = 0; port_id < SW_MAX_NR_PORT; port_id ++)
	{
		if (port_bmp[dev_id] & (0x1 << port_id))
		{
			first_phy_addr = qca_ssdk_port_to_phy_addr(dev_id, port_id);
				break;
		}
	}

	if (enable == A_FALSE) {
		ssdk_malibu_psgmii_and_dakota_dess_reset(dev_id, first_phy_addr);
	}

	qca_ar8327_phy_write(dev_id, first_phy_addr + 4, 0x1f, 0x8500);/*switch to access MII reg for copper*/
	for(phy = first_phy_addr; phy < first_phy_addr + 5; phy++) {
		/*enable phy mdio broadcast write*/
		qca_phy_mmd_write(dev_id, phy, 7, 0x8028, 0x801f);
	}

	/* force no link by power down */
	qca_ar8327_phy_write(dev_id, 0x1f, 0x0, 0x1840);

	/*packet number*/
	qca_phy_mmd_write(dev_id, 0x1f, 7, 0x8021, 0x3000);
	qca_phy_mmd_write(dev_id, 0x1f, 7, 0x8062, 0x05e0);

	/*fix mdi status */
	qca_ar8327_phy_write(dev_id, 0x1f, 0x10, 0x6800);

	for(i = 0; i < times; i++) {
		phy_t_status = 0;

		for(phy = 0; phy < 5; phy++) {
			value = readl(qca_phy_priv_global[dev_id]->hw_addr + 0x66c + phy * 0xc);
			writel((value|(1<<21)), (qca_phy_priv_global[dev_id]->hw_addr + 0x66c + phy * 0xc));
		}

		for (phy = first_phy_addr; phy < first_phy_addr + 5; phy++) {
			ssdk_psgmii_single_phy_testing(dev_id, phy, enable);
		}
		ssdk_psgmii_all_phy_testing(dev_id, first_phy_addr, enable);
		if (enable == A_FALSE) {
			if (phy_t_status) {
				ssdk_malibu_psgmii_and_dakota_dess_reset(dev_id, first_phy_addr);
			}
			else
			{
		                break;
			}
		}
	}

	*result = phy_t_status;
#ifdef PSGMII_DEBUG
	if (i>=100)
		SSDK_ERROR("PSGMII cannot recover\n");
	else
		SSDK_INFO("PSGMII recovered after %d times reset\n",i);
#endif
	/*configuration recover*/
	/*packet number*/
	qca_phy_mmd_write(dev_id, 0x1f, 7, 0x8021, 0x0);
	/*disable check*/
	qca_phy_mmd_write(dev_id, 0x1f, 7, 0x8029, 0x0);
	/*disable traffic*/
	qca_phy_mmd_write(dev_id, 0x1f, 7, 0x8020, 0x0);
}


void clear_self_test_config(a_uint32_t dev_id)
{
	u32 value = 0;
	a_uint32_t port_bmp[SW_MAX_NR_DEV] = {0};
	a_uint32_t port_id = 0, first_phy_addr = 0, phy = 0;


	port_bmp[dev_id] = qca_ssdk_phy_type_port_bmp_get(dev_id, MALIBU_PHY_CHIP);

	for (port_id = 0; port_id < SW_MAX_NR_PORT; port_id ++)
	{
		if (port_bmp[dev_id] & (0x1 << port_id))
		{
			first_phy_addr = qca_ssdk_port_to_phy_addr(dev_id, port_id);
				break;
		}
	}

	/* disable EEE */
	/* qca_phy_mmd_write(0, 0x1f, 0x7,  0x3c, 0x0); */

	/*disable phy internal loopback*/
	qca_ar8327_phy_write(dev_id, 0x1f, 0x10, 0x6860);
	qca_ar8327_phy_write(dev_id, 0x1f, 0x0, 0x9040);

	for(phy = 0; phy < 5; phy++)
	{
		/*disable mac loop back*/
		value = readl(qca_phy_priv_global[dev_id]->hw_addr+0x66c+phy*0xc);
		writel((value&(~(1<<21))), (qca_phy_priv_global[dev_id]->hw_addr+0x66c+phy*0xc));
	}

	for(phy = first_phy_addr; phy < first_phy_addr + 5; phy++)
	{
		/*diable phy mdio broadcast write*/
		qca_phy_mmd_write(dev_id, phy, 7, 0x8028, 0x001f);

	}

	/* clear fdb entry */
	fal_fdb_entry_flush(dev_id,1);
}
#endif

sw_error_t
ssdk_init(a_uint32_t dev_id, ssdk_init_cfg * cfg)
{
	sw_error_t rv;

	rv = fal_init(dev_id, cfg);
	if (rv != SW_OK)
		SSDK_ERROR("ssdk fal init failed: %d. \r\n", rv);

	rv = ssdk_phy_driver_init(dev_id, cfg);
	if (rv != SW_OK)
		SSDK_ERROR("ssdk phy init failed: %d. \r\n", rv);

	return rv;
}

sw_error_t
ssdk_cleanup(void)
{
	sw_error_t rv;

	rv = fal_cleanup();
	rv = ssdk_phy_driver_cleanup();

	return rv;
}

sw_error_t
ssdk_hsl_access_mode_set(a_uint32_t dev_id, hsl_access_mode reg_mode)
{
    sw_error_t rv;

    rv = hsl_access_mode_set(dev_id, reg_mode);
    return rv;
}

void switch_cpuport_setup(a_uint32_t dev_id)
{
	#ifdef IN_PORTCONTROL
	//According to HW suggestion, enable CPU port flow control for Dakota
	fal_port_flowctrl_forcemode_set(dev_id, 0, A_TRUE);
	fal_port_flowctrl_set(dev_id, 0, A_TRUE);
	fal_port_duplex_set(dev_id, 0, FAL_FULL_DUPLEX);
	fal_port_speed_set(dev_id, 0, FAL_SPEED_1000);
	udelay(10);
	fal_port_txmac_status_set(dev_id, 0, A_TRUE);
	fal_port_rxmac_status_set(dev_id, 0, A_TRUE);
	#endif
}

ssdk_dt_scheduler_cfg *ssdk_bootup_shceduler_cfg_get(a_uint32_t dev_id)
{
	return &(ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->scheduler_cfg);
}

#ifndef BOARD_AR71XX
#if defined(CONFIG_OF) && (LINUX_VERSION_CODE >= KERNEL_VERSION(3,14,0))
static void ssdk_dt_parse_mac_mode(ssdk_init_cfg *cfg, struct device_node *switch_node, a_uint32_t dev_id)
{
	const __be32 *mac_mode;
	a_uint32_t len = 0;

	mac_mode = of_get_property(switch_node, "switch_mac_mode", &len);
	if (!mac_mode)
		SSDK_INFO("mac mode doesn't exit!\n");
	else {
		cfg->mac_mode = be32_to_cpup(mac_mode);
		SSDK_INFO("mac mode = 0x%x\n", be32_to_cpup(mac_mode));
		ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->mac_mode = cfg->mac_mode;
	}

	mac_mode = of_get_property(switch_node, "switch_mac_mode1", &len);
	if(!mac_mode)
		SSDK_INFO("mac mode1 doesn't exit!\n");
	else {
		cfg->mac_mode1 = be32_to_cpup(mac_mode);
		SSDK_INFO("mac mode1 = 0x%x\n", be32_to_cpup(mac_mode));
		ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->mac_mode1 = cfg->mac_mode1;
	}

	mac_mode = of_get_property(switch_node, "switch_mac_mode2", &len);
	if(!mac_mode)
		SSDK_INFO("mac mode2 doesn't exit!\n");
	else {
		cfg->mac_mode2 = be32_to_cpup(mac_mode);
		SSDK_INFO("mac mode2 = 0x%x\n", be32_to_cpup(mac_mode));
		ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->mac_mode2 = cfg->mac_mode2;
	}

	return;
}

static void ssdk_dt_parse_uniphy(a_uint32_t dev_id)
{
	struct device_node *uniphy_node = NULL;
	a_uint32_t len = 0;
	const __be32 *reg_cfg;

	/* read uniphy register base and address space */
	uniphy_node = of_find_node_by_name(NULL, "ess-uniphy");
	if (!uniphy_node)
		SSDK_INFO("ess-uniphy DT doesn't exist!\n");
	else {
		SSDK_INFO("ess-uniphy DT exist!\n");
		reg_cfg = of_get_property(uniphy_node, "reg", &len);
		if(!reg_cfg)
			SSDK_INFO("uniphy reg address doesn't exist!\n");
		else {
			ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->uniphyreg_base_addr = be32_to_cpup(reg_cfg);
			ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->uniphyreg_size = be32_to_cpup(reg_cfg + 1);
		}
		if (of_property_read_string(uniphy_node, "uniphy_access_mode", (const char **)&ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->uniphy_access_mode))
			SSDK_INFO("uniphy access mode doesn't exist!\n");
		else {
			if(!strcmp(ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->uniphy_access_mode, "local bus"))
				ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->uniphy_reg_access_mode = HSL_REG_LOCAL_BUS;
		}
	}

	return;
}

static void ssdk_dt_parse_l1_scheduler_cfg(
	struct device_node *port_node,
	a_uint32_t port_id, a_uint32_t dev_id)
{
	struct device_node *scheduler_node;
	struct device_node *child;
	ssdk_dt_scheduler_cfg *cfg = &(ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->scheduler_cfg);
	a_uint32_t tmp_cfg[4];
	const __be32 *paddr;
	a_uint32_t len, i, sp_id;

	scheduler_node = of_find_node_by_name(port_node, "l1scheduler");
	if (!scheduler_node) {
		SSDK_ERROR("cannot find l1scheduler node for port\n");
		return;
	}
	for_each_available_child_of_node(scheduler_node, child) {
		paddr = of_get_property(child, "sp", &len);
		len /= sizeof(a_uint32_t);
		if (!paddr) {
			SSDK_ERROR("error reading sp property\n");
			return;
		}
		if (of_property_read_u32_array(child,
				"cfg", tmp_cfg, 4)) {
			SSDK_ERROR("error reading cfg property!\n");
			return;
		}
		for (i = 0; i < len; i++) {
			sp_id = be32_to_cpup(paddr+i);
			if (sp_id >= SSDK_L1SCHEDULER_CFG_MAX) {
				SSDK_ERROR("Invalid parameter for sp(%d)\n",
					sp_id);
				return;
			}
			cfg->l1cfg[sp_id].valid = 1;
			cfg->l1cfg[sp_id].port_id = port_id;
			cfg->l1cfg[sp_id].cpri = tmp_cfg[0];
			cfg->l1cfg[sp_id].cdrr_id = tmp_cfg[1];
			cfg->l1cfg[sp_id].epri = tmp_cfg[2];
			cfg->l1cfg[sp_id].edrr_id = tmp_cfg[3];
		}
	}
}

static void ssdk_dt_parse_l0_queue_cfg(
	a_uint32_t dev_id,
	a_uint32_t port_id,
	struct device_node *node,
	a_uint8_t *queue_name,
	a_uint8_t *loop_name)
{
	ssdk_dt_scheduler_cfg *cfg = &(ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->scheduler_cfg);
	a_uint32_t tmp_cfg[5];
	const __be32 *paddr;
	a_uint32_t len, i, queue_id, pri_loop;

	paddr = of_get_property(node, queue_name, &len);
	len /= sizeof(a_uint32_t);
	if (!paddr) {
		SSDK_ERROR("error reading %s property\n", queue_name);
		return;
	}
	if (of_property_read_u32_array(node, "cfg", tmp_cfg, 5)) {
		SSDK_ERROR("error reading cfg property!\n");
		return;
	}
	if (of_property_read_u32(node, loop_name, &pri_loop)) {
		for (i = 0; i < len; i++) {
			queue_id = be32_to_cpup(paddr+i);
			if (queue_id >= SSDK_L0SCHEDULER_CFG_MAX) {
				SSDK_ERROR("Invalid parameter for queue(%d)\n",
					queue_id);
				return;
			}
			cfg->l0cfg[queue_id].valid = 1;
			cfg->l0cfg[queue_id].port_id = port_id;
			cfg->l0cfg[queue_id].sp_id = tmp_cfg[0];
			cfg->l0cfg[queue_id].cpri = tmp_cfg[1];
			cfg->l0cfg[queue_id].cdrr_id = tmp_cfg[2];
			cfg->l0cfg[queue_id].epri = tmp_cfg[3];
			cfg->l0cfg[queue_id].edrr_id = tmp_cfg[4];
		}
	} else {
		/* should one queue for loop */
		if (len != 1) {
			SSDK_ERROR("should one queue for loop!\n");
			return;
		}
		queue_id = be32_to_cpup(paddr);
		if (queue_id >= SSDK_L0SCHEDULER_CFG_MAX) {
			SSDK_ERROR("Invalid parameter for queue(%d)\n",
				queue_id);
			return;
		}
		for (i = 0; i < pri_loop; i++) {
			cfg->l0cfg[queue_id + i].valid = 1;
			cfg->l0cfg[queue_id + i].port_id = port_id;
			cfg->l0cfg[queue_id + i].sp_id = tmp_cfg[0] + i/SSDK_SP_MAX_PRIORITY;
			cfg->l0cfg[queue_id + i].cpri = tmp_cfg[1] + i%SSDK_SP_MAX_PRIORITY;
			cfg->l0cfg[queue_id + i].cdrr_id = tmp_cfg[2] + i;
			cfg->l0cfg[queue_id + i].epri = tmp_cfg[3] + i%SSDK_SP_MAX_PRIORITY;
			cfg->l0cfg[queue_id + i].edrr_id = tmp_cfg[4] + i;
		}
	}
}

static void ssdk_dt_parse_l0_scheduler_cfg(
	struct device_node *port_node,
	a_uint32_t port_id, a_uint32_t dev_id)
{
	struct device_node *scheduler_node;
	struct device_node *child;

	scheduler_node = of_find_node_by_name(port_node, "l0scheduler");
	if (!scheduler_node) {
		SSDK_ERROR("Can't find l0scheduler node for port\n");
		return;
	}
	for_each_available_child_of_node(scheduler_node, child) {
		ssdk_dt_parse_l0_queue_cfg(dev_id, port_id, child,
				"ucast_queue", "ucast_loop_pri");
		ssdk_dt_parse_l0_queue_cfg(dev_id, port_id, child,
				"mcast_queue", "mcast_loop_pri");
	}
}

static void ssdk_dt_parse_scheduler_resource(
	struct device_node *port_node,
	a_uint32_t dev_id, a_uint32_t port_id)
{
	a_uint32_t uq[2], mq[2], l0sp[2], l0cdrr[2];
	a_uint32_t l0edrr[2], l1cdrr[2], l1edrr[2];
	ssdk_dt_scheduler_cfg *cfg = &(ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->scheduler_cfg);

	if (of_property_read_u32_array(port_node, "ucast_queue", uq, 2)
		|| of_property_read_u32_array(port_node, "mcast_queue", mq, 2)
		|| of_property_read_u32_array(port_node, "l0sp", l0sp, 2)
		|| of_property_read_u32_array(port_node, "l0cdrr", l0cdrr, 2)
		|| of_property_read_u32_array(port_node, "l0edrr", l0edrr, 2)
		|| of_property_read_u32_array(port_node, "l1cdrr", l1cdrr, 2)
		|| of_property_read_u32_array(port_node, "l1edrr", l1edrr, 2)){
		SSDK_ERROR("error reading port resource scheduler properties\n");
		return;
	}
	cfg->pool[port_id].ucastq_start = uq[0];
	cfg->pool[port_id].ucastq_end = uq[1];
	cfg->pool[port_id].mcastq_start = mq[0];
	cfg->pool[port_id].mcastq_end = mq[1];
	cfg->pool[port_id].l0sp_start = l0sp[0];
	cfg->pool[port_id].l0sp_end = l0sp[1];
	cfg->pool[port_id].l0cdrr_start = l0cdrr[0];
	cfg->pool[port_id].l0cdrr_end = l0cdrr[1];
	cfg->pool[port_id].l0edrr_start = l0edrr[0];
	cfg->pool[port_id].l0edrr_end = l0edrr[1];
	cfg->pool[port_id].l1cdrr_start = l1cdrr[0];
	cfg->pool[port_id].l1cdrr_end = l1cdrr[1];
	cfg->pool[port_id].l1edrr_start = l1edrr[0];
	cfg->pool[port_id].l1edrr_end = l1edrr[1];
}

static void ssdk_dt_parse_scheduler_cfg(struct device_node *switch_node, a_uint32_t dev_id)
{
	struct device_node *scheduler_node;
	struct device_node *child;
	a_uint32_t port_id;

	scheduler_node = of_find_node_by_name(switch_node, "port_scheduler_resource");
	if (!scheduler_node) {
		SSDK_ERROR("cannot find port_scheduler_resource node\n");
		return;
	}
	for_each_available_child_of_node(scheduler_node, child) {
		if (of_property_read_u32(child, "port_id", &port_id)) {
			SSDK_ERROR("error reading for port_id property!\n");
			return;
		}
		if (port_id >= SSDK_MAX_PORT_NUM) {
			SSDK_ERROR("invalid parameter for port_id(%d)!\n", port_id);
			return;
		}
		ssdk_dt_parse_scheduler_resource(child, dev_id, port_id);
	}

	scheduler_node = of_find_node_by_name(switch_node, "port_scheduler_config");
	if (!scheduler_node) {
		SSDK_ERROR("cannot find port_scheduler_config node\n");
		return ;
	}
	for_each_available_child_of_node(scheduler_node, child) {
		if (of_property_read_u32(child, "port_id", &port_id)) {
			SSDK_ERROR("error reading for port_id property!\n");
			return;
		}
		if (port_id >= SSDK_MAX_PORT_NUM) {
			SSDK_ERROR("invalid parameter for port_id(%d)!\n", port_id);
			return;
		}
		ssdk_dt_parse_l1_scheduler_cfg(child, port_id, dev_id);
		ssdk_dt_parse_l0_scheduler_cfg(child, port_id, dev_id);
	}
}

static sw_error_t ssdk_dt_parse_phy_info(struct device_node *switch_node, a_uint32_t dev_id)
{
	struct device_node *phy_info_node, *port_node;
	a_uint32_t port_id, phy_addr;
	a_bool_t phy_c45;
	sw_error_t rv = SW_OK;

	phy_info_node = of_get_child_by_name(switch_node, "qcom,port_phyinfo");
	if (!phy_info_node) {
		SSDK_INFO("qcom,port_phyinfo DT doesn't exist!\n");
		return SW_NOT_FOUND;
	}

	for_each_available_child_of_node(phy_info_node, port_node) {
		if (of_property_read_u32(port_node, "port_id", &port_id) ||
				of_property_read_u32(port_node, "phy_address", &phy_addr))
			return SW_BAD_VALUE;

		phy_c45 = of_property_read_bool(port_node,
				"ethernet-phy-ieee802.3-c45");

		hsl_port_phy_c45_capability_set(dev_id, port_id, phy_c45);
		qca_ssdk_phy_address_set(dev_id, port_id, phy_addr);
	}

	return rv;
}

static void ssdk_dt_parse_mdio(struct device_node *switch_node, a_uint32_t dev_id)
{
	struct device_node *mdio_node = NULL;
	struct device_node *child = NULL;
	a_uint32_t len = 0, i = 1;
	const __be32 *phy_addr;
	const __be32 * c45_phy;

	/* prefer to get phy info from ess-switch node */
	if (SW_OK == ssdk_dt_parse_phy_info(switch_node, dev_id))
		return;

	mdio_node = of_find_node_by_name(NULL, "mdio");

	if (!mdio_node) {
		SSDK_INFO("mdio DT doesn't exist!\n");
	}
	else {
		SSDK_INFO("mdio DT exist!\n");
		for_each_available_child_of_node(mdio_node, child) {
			phy_addr = of_get_property(child, "reg", &len);
			if (phy_addr)
				qca_ssdk_phy_address_set(dev_id, i, be32_to_cpup(phy_addr));

			c45_phy = of_get_property(child, "compatible", &len);
			if (c45_phy)
				hsl_port_phy_c45_capability_set(dev_id, i, A_TRUE);
			i++;
			if (i >= SW_MAX_NR_PORT)
				break;
		}
	}
	return;
}

static void ssdk_dt_parse_port_bmp(a_uint32_t dev_id,ssdk_init_cfg *cfg,
				struct device_node *switch_node)
{
	a_uint32_t portbmp = 0;

	if (of_property_read_u32(switch_node, "switch_cpu_bmp", &cfg->port_cfg.cpu_bmp)
		|| of_property_read_u32(switch_node, "switch_lan_bmp", &cfg->port_cfg.lan_bmp)
		|| of_property_read_u32(switch_node, "switch_wan_bmp", &cfg->port_cfg.wan_bmp)) {
		SSDK_ERROR("port_bmp doesn't exist!\n");
		return;
	}

	ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->port_cfg.cpu_bmp = cfg->port_cfg.cpu_bmp;
	ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->port_cfg.lan_bmp = cfg->port_cfg.lan_bmp;
	ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->port_cfg.wan_bmp = cfg->port_cfg.wan_bmp;

	portbmp = cfg->port_cfg.lan_bmp | cfg->port_cfg.wan_bmp;
	qca_ssdk_port_bmp_set(dev_id, portbmp);

	return;
}

static int ssdk_dt_parse(ssdk_init_cfg *cfg, a_uint32_t num, a_uint32_t *dev_id)
{
	struct device_node *switch_node = NULL;
	struct device_node *switch_instance = NULL;
	struct device_node *psgmii_node = NULL;
	struct device_node *child = NULL;
	ssdk_dt_cfg *ssdk_dt_priv = NULL;
	a_uint32_t len = 0, i = 0, mode = 0;
	const __be32 *reg_cfg, *led_source, *device_id;
	const __be32 *led_number;
	a_uint8_t *led_str;
	a_uint8_t *status_value;
	char ess_switch_name[64] = {0};

	if (num == 0)
		snprintf(ess_switch_name, sizeof(ess_switch_name), "ess-switch");
	else
		snprintf(ess_switch_name, sizeof(ess_switch_name), "ess-switch%d", num);

	/*
	 * Get reference to ESS SWITCH device node from ess-instance node firstly.
	 */
	switch_instance = of_find_node_by_name(NULL, "ess-instance");
	switch_node = of_find_node_by_name(switch_instance, ess_switch_name);
	if (!switch_node) {
		SSDK_ERROR("cannot find ess-switch node\n");
		return SW_BAD_PARAM;
	}

	SSDK_INFO("ess-switch DT exist!\n");

	if (!of_property_read_string(switch_node, "status", (const char **)&status_value))
	{
		if (!strcmp(status_value, "disabled"))
			return SW_DISABLE;
	}

	device_id = of_get_property(switch_node, "device_id", &len);
	if(!device_id)
		*dev_id = 0;
	else
		*dev_id = be32_to_cpup(device_id);

	ssdk_dt_priv = ssdk_dt_global.ssdk_dt_switch_nodes[*dev_id];
	ssdk_dt_priv->device_id = *dev_id;
	ssdk_dt_priv->ess_switch_flag = A_TRUE;
	ssdk_dt_priv->of_node = switch_node;

	if (of_property_read_string(switch_node, "switch_access_mode", (const char **)&ssdk_dt_priv->reg_access_mode)) {
		SSDK_ERROR("%s: error reading device node properties for switch_access_mode\n", switch_node->name);
		return SW_BAD_PARAM;
	}

	ssdk_dt_priv->ess_clk = of_clk_get_by_name(switch_node, "ess_clk");
	if (IS_ERR(ssdk_dt_priv->ess_clk))
		SSDK_INFO("ess_clk doesn't exist!\n");
	ssdk_dt_priv->cmnblk_clk = of_clk_get_by_name(switch_node, "cmn_ahb_clk");

	SSDK_INFO("switch_access_mode: %s\n", ssdk_dt_priv->reg_access_mode);
	if(!strcmp(ssdk_dt_priv->reg_access_mode, "local bus"))
		ssdk_dt_priv->switch_reg_access_mode = HSL_REG_LOCAL_BUS;
	else if(!strcmp(ssdk_dt_priv->reg_access_mode, "mdio"))
		ssdk_dt_priv->switch_reg_access_mode = HSL_REG_MDIO;
	else
		ssdk_dt_priv->switch_reg_access_mode = HSL_REG_MDIO;

	ssdk_dt_parse_mac_mode(cfg, switch_node, *dev_id);

	ssdk_dt_parse_uniphy(*dev_id);

	ssdk_dt_parse_scheduler_cfg(switch_node, *dev_id);

	ssdk_dt_parse_mdio(switch_node, *dev_id);

	ssdk_dt_parse_port_bmp(*dev_id, cfg, switch_node);

	reg_cfg = of_get_property(switch_node, "reg", &len);
	if(!reg_cfg) {
		SSDK_ERROR("%s: error reading device node properties for reg\n", switch_node->name);
		return SW_BAD_PARAM;
	}
	ssdk_dt_priv->switchreg_base_addr = be32_to_cpup(reg_cfg);
	ssdk_dt_priv->switchreg_size = be32_to_cpup(reg_cfg + 1);

	SSDK_INFO("switchreg_base_addr: 0x%x\n", ssdk_dt_priv->switchreg_base_addr);
	SSDK_INFO("switchreg_size: 0x%x\n", ssdk_dt_priv->switchreg_size);

	if (!of_property_read_u32(switch_node, "tm_tick_mode", &mode))
		ssdk_dt_priv->tm_tick_mode = mode;

	psgmii_node = of_find_node_by_name(NULL, "ess-psgmii");
	if (!psgmii_node) {
		return SW_BAD_PARAM;
	}
	SSDK_INFO("ess-psgmii DT exist!\n");
	reg_cfg = of_get_property(psgmii_node, "reg", &len);
	if(!reg_cfg) {
		SSDK_ERROR("%s: error reading device node properties for reg\n", psgmii_node->name);
		return SW_BAD_PARAM;
	}

	ssdk_dt_priv->psgmiireg_base_addr = be32_to_cpup(reg_cfg);
	ssdk_dt_priv->psgmiireg_size = be32_to_cpup(reg_cfg + 1);
	if (of_property_read_string(psgmii_node, "psgmii_access_mode", (const char **)&ssdk_dt_priv->psgmii_reg_access_str)) {
		SSDK_INFO("%s: error reading device node properties for psmgii_access_mode\n", psgmii_node->name);
		return SW_BAD_PARAM;
	}
	if(!strcmp(ssdk_dt_priv->psgmii_reg_access_str, "local bus"))
		ssdk_dt_priv->psgmii_reg_access_mode = HSL_REG_LOCAL_BUS;

	for_each_available_child_of_node(switch_node, child) {

		led_source = of_get_property(child, "source", &len);
		if (led_source)
			cfg->led_source_cfg[i].led_source_id = be32_to_cpup(led_source);
		led_number = of_get_property(child, "led", &len);
		if (led_number)
			cfg->led_source_cfg[i].led_num = be32_to_cpup(led_number);
		if (!of_property_read_string(child, "mode", (const char **)&led_str)) {
			if (!strcmp(led_str, "normal"))
			cfg->led_source_cfg[i].led_pattern.mode = LED_PATTERN_MAP_EN;
			if (!strcmp(led_str, "on"))
			cfg->led_source_cfg[i].led_pattern.mode = LED_ALWAYS_ON;
			if (!strcmp(led_str, "blink"))
			cfg->led_source_cfg[i].led_pattern.mode = LED_ALWAYS_BLINK;
			if (!strcmp(led_str, "off"))
			cfg->led_source_cfg[i].led_pattern.mode = LED_ALWAYS_OFF;
		}
		if (!of_property_read_string(child, "speed", (const char **)&led_str)) {
			if (!strcmp(led_str, "10M"))
			cfg->led_source_cfg[i].led_pattern.map = LED_MAP_10M_SPEED;
			if (!strcmp(led_str, "100M"))
			cfg->led_source_cfg[i].led_pattern.map = LED_MAP_100M_SPEED;
			if (!strcmp(led_str, "100M"))
			cfg->led_source_cfg[i].led_pattern.map = LED_MAP_1000M_SPEED;
			if (!strcmp(led_str, "all"))
			cfg->led_source_cfg[i].led_pattern.map = LED_MAP_ALL_SPEED;
		}
		if (!of_property_read_string(child, "freq", (const char **)&led_str)) {
			if (!strcmp(led_str, "2Hz"))
			cfg->led_source_cfg[i].led_pattern.freq = LED_BLINK_2HZ;
			if (!strcmp(led_str, "4Hz"))
			cfg->led_source_cfg[i].led_pattern.freq = LED_BLINK_4HZ;
			if (!strcmp(led_str, "8Hz"))
			cfg->led_source_cfg[i].led_pattern.freq = LED_BLINK_8HZ;
			if (!strcmp(led_str, "auto"))
			cfg->led_source_cfg[i].led_pattern.freq = LED_BLINK_TXRX;
		}
		i++;
	}
	cfg->led_source_num = i;
	SSDK_INFO("current dts led_source_num is %d\n",cfg->led_source_num);

	return SW_OK;
}

#endif
#endif

#ifdef CONFIG_MDIO
static struct mdio_if_info ssdk_mdio_ctl;
#endif
static struct net_device *ssdk_miireg_netdev = NULL;

static int ssdk_miireg_open(struct net_device *netdev)
{
	return 0;
}
static int ssdk_miireg_close(struct net_device *netdev)
{
	return 0;
}

static int ssdk_miireg_do_ioctl(struct net_device *netdev,
			struct ifreq *ifr, int32_t cmd)
{
	int ret = -EINVAL;
#ifdef CONFIG_MDIO
	struct mii_ioctl_data *mii_data = if_mii(ifr);
	ret = mdio_mii_ioctl(&ssdk_mdio_ctl, mii_data, cmd);
#endif
	return ret;
}

static const struct net_device_ops ssdk_netdev_ops = {
	.ndo_open = &ssdk_miireg_open,
	.ndo_stop = &ssdk_miireg_close,
	.ndo_do_ioctl = &ssdk_miireg_do_ioctl,
};

#ifdef CONFIG_MDIO
static int ssdk_miireg_ioctl_read(struct net_device *netdev, int phy_addr, int mmd, uint16_t addr)
{
	a_uint32_t reg = 0;
	a_uint16_t val = 0;

	if (MDIO_DEVAD_NONE == mmd) {
		qca_ar8327_phy_read(0, phy_addr, addr, &val);
		return (int)val;
	}

	reg = MII_ADDR_C45 | mmd << 16 | addr;
	qca_ar8327_phy_read(0, phy_addr, reg, &val);

	return (int)val;
}

static int ssdk_miireg_ioctl_write(struct net_device *netdev, int phy_addr, int mmd,
				uint16_t addr, uint16_t value)
{
	a_uint32_t reg = 0;

	if (MDIO_DEVAD_NONE == mmd) {
		qca_ar8327_phy_write(0, phy_addr, addr, value);
		return 0;
	}

	reg = MII_ADDR_C45 | mmd << 16 | addr;
	qca_ar8327_phy_write(0, phy_addr, reg, value);

	return 0;
}
#endif

static void ssdk_netdev_setup(struct net_device *dev)
{
	dev->netdev_ops = &ssdk_netdev_ops;
}
static void ssdk_miireg_ioctrl_register(void)
{
	if (ssdk_miireg_netdev)
		return;
#ifdef CONFIG_MDIO
	ssdk_mdio_ctl.mdio_read = ssdk_miireg_ioctl_read;
	ssdk_mdio_ctl.mdio_write = ssdk_miireg_ioctl_write;
	ssdk_mdio_ctl.mode_support = MDIO_SUPPORTS_C45;
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,18,0))
	ssdk_miireg_netdev = alloc_netdev(100, "miireg", 0, ssdk_netdev_setup);
#else
	ssdk_miireg_netdev = alloc_netdev(100, "miireg", ssdk_netdev_setup);
#endif
	if (ssdk_miireg_netdev)
		register_netdev(ssdk_miireg_netdev);
}

static void ssdk_miireg_ioctrl_unregister(void)
{
	if (ssdk_miireg_netdev) {
		unregister_netdev(ssdk_miireg_netdev);
		kfree(ssdk_miireg_netdev);
		ssdk_miireg_netdev = NULL;
	}
}

static void ssdk_driver_register(a_uint32_t dev_id)
{
#ifdef DESS
	if(ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->switch_reg_access_mode == HSL_REG_LOCAL_BUS) {
#ifndef BOARD_AR71XX
#if defined(CONFIG_OF) && (LINUX_VERSION_CODE >= KERNEL_VERSION(3,14,0))
		platform_driver_register(&ssdk_driver);
#endif
#endif
	}
#endif

	if(ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->switch_reg_access_mode == HSL_REG_MDIO && ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->ess_switch_flag == A_FALSE) {
		if(driver_find(qca_phy_driver.name, &mdio_bus_type)){
			SSDK_ERROR("QCA PHY driver had been Registered\n");
			return;
		}

		SSDK_INFO("Register QCA PHY driver\n");
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4,9,0))
		phy_driver_register(&qca_phy_driver, THIS_MODULE);
#else
		phy_driver_register(&qca_phy_driver);
#endif

#ifdef BOARD_AR71XX
#if defined(IN_SWCONFIG)
		ssdk_uci_takeover_init();
#endif

#ifdef CONFIG_AR8216_PHY
		ar8327_port_link_notify_register(ssdk_port_link_notify);
#endif
		ar7240_port_link_notify_register(ssdk_port_link_notify);
#endif
	}
}

static void ssdk_driver_unregister(a_uint32_t dev_id)
{
	if(ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->switch_reg_access_mode == HSL_REG_MDIO && ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->ess_switch_flag == A_FALSE) {
		phy_driver_unregister(&qca_phy_driver);

	#if defined(BOARD_AR71XX) && defined(IN_SWCONFIG)
		ssdk_uci_takeover_exit();
	#endif
	}

	if (ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->switch_reg_access_mode == HSL_REG_LOCAL_BUS) {
#ifndef BOARD_AR71XX
#if defined(CONFIG_OF) && (LINUX_VERSION_CODE >= KERNEL_VERSION(3,14,0))
		platform_driver_unregister(&ssdk_driver);
#endif
#endif
	}
}

static int chip_ver_get(a_uint32_t dev_id, ssdk_init_cfg* cfg)
{
	int rv = 0;
	a_uint8_t chip_ver = 0;
	if(ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->switch_reg_access_mode == HSL_REG_MDIO)
	{
		chip_ver = (qca_ar8216_mii_read(dev_id, 0)&0xff00)>>8;
	}
	else {
		a_uint32_t reg_val = 0;
		qca_switch_reg_read(dev_id,0,(a_uint8_t *)&reg_val, 4);
		chip_ver = (reg_val&0xff00)>>8;
	}

	if(chip_ver == QCA_VER_AR8227)
		cfg->chip_type = CHIP_SHIVA;
	else if(chip_ver == QCA_VER_AR8337)
		cfg->chip_type = CHIP_ISISC;
	else if(chip_ver == QCA_VER_AR8327)
		cfg->chip_type = CHIP_ISIS;
	else if(chip_ver == QCA_VER_DESS)
		cfg->chip_type = CHIP_DESS;
	else if(chip_ver == QCA_VER_HPPE)
		cfg->chip_type = CHIP_HPPE;
	else
		rv = -ENODEV;

	return rv;
}

#ifdef DESS
static int ssdk_flow_default_act_init(a_uint32_t dev_id)
{
	a_uint32_t vrf_id = 0;
	fal_flow_type_t type = 0;
	for(vrf_id = FAL_MIN_VRF_ID; vrf_id <= FAL_MAX_VRF_ID; vrf_id++)
	{
		for(type = FAL_FLOW_LAN_TO_LAN; type <= FAL_FLOW_WAN_TO_WAN; type++)
		{
			#ifdef IN_IP
			fal_default_flow_cmd_set(dev_id, vrf_id, type, FAL_DEFAULT_FLOW_ADMIT_ALL);
			#endif
		}
	}

	return 0;
}

static int ssdk_dess_led_init(ssdk_init_cfg *cfg)
{
	a_uint32_t i,led_num, led_source_id,source_id;
	led_ctrl_pattern_t  pattern;

	if(cfg->led_source_num != 0) {
		for (i = 0; i < cfg->led_source_num; i++) {

			led_source_id = cfg->led_source_cfg[i].led_source_id;
			pattern.mode = cfg->led_source_cfg[i].led_pattern.mode;
			pattern.map = cfg->led_source_cfg[i].led_pattern.map;
			pattern.freq = cfg->led_source_cfg[i].led_pattern.freq;
			#ifdef IN_LED
			fal_led_source_pattern_set(0, led_source_id,&pattern);
			#endif
			led_num = ((led_source_id-1)/3) + 3;
			source_id = led_source_id%3;
		#ifndef BOARD_AR71XX
		#if defined(CONFIG_OF) && (LINUX_VERSION_CODE >= KERNEL_VERSION(3,14,0)) && (LINUX_VERSION_CODE <= KERNEL_VERSION(4,0,0))
			if (source_id == 1) {
				if (led_source_id == 1) {
					ipq40xx_led_source_select(led_num, LAN0_1000_LNK_ACTIVITY);
				}
				if (led_source_id == 4) {
					ipq40xx_led_source_select(led_num, LAN1_1000_LNK_ACTIVITY);
				}
				if (led_source_id == 7) {
					ipq40xx_led_source_select(led_num, LAN2_1000_LNK_ACTIVITY);
				}
				if (led_source_id == 10) {
					ipq40xx_led_source_select(led_num, LAN3_1000_LNK_ACTIVITY);
				}
				if (led_source_id == 13) {
					ipq40xx_led_source_select(led_num, WAN_1000_LNK_ACTIVITY);
				}
			}
			if (source_id == 2) {
				if (led_source_id == 2) {
					ipq40xx_led_source_select(led_num, LAN0_100_LNK_ACTIVITY);
				}
				if (led_source_id == 5) {
					ipq40xx_led_source_select(led_num, LAN1_100_LNK_ACTIVITY);
				}
				if (led_source_id == 8) {
					ipq40xx_led_source_select(led_num, LAN2_100_LNK_ACTIVITY);
				}
				if (led_source_id == 11) {
					ipq40xx_led_source_select(led_num, LAN3_100_LNK_ACTIVITY);
				}
				if (led_source_id == 14) {
					ipq40xx_led_source_select(led_num, WAN_100_LNK_ACTIVITY);
				}
			}
			if (source_id == 0) {
				if (led_source_id == 3) {
					ipq40xx_led_source_select(led_num, LAN0_10_LNK_ACTIVITY);
				}
				if (led_source_id == 6) {
					ipq40xx_led_source_select(led_num, LAN1_10_LNK_ACTIVITY);
				}
				if (led_source_id == 9) {
					ipq40xx_led_source_select(led_num, LAN2_10_LNK_ACTIVITY);
				}
				if (led_source_id == 12) {
					ipq40xx_led_source_select(led_num, LAN3_10_LNK_ACTIVITY);
				}
				if (led_source_id == 15) {
					ipq40xx_led_source_select(led_num, WAN_10_LNK_ACTIVITY);
				}
			}
		#endif
		#endif
		}
	}
	return 0;
}

static int ssdk_dess_mac_mode_init(a_uint32_t dev_id, a_uint32_t mac_mode)
{
	a_uint32_t reg_value;
	u8  __iomem      *gcc_addr = NULL;

	switch(mac_mode) {
		case PORT_WRAPPER_PSGMII:
			reg_value = 0x2200;
			qca_psgmii_reg_write(dev_id, DESS_PSGMII_MODE_CONTROL,
								(a_uint8_t *)&reg_value, 4);
			reg_value = 0x8380;
			qca_psgmii_reg_write(dev_id, DESS_PSGMIIPHY_TX_CONTROL,
								(a_uint8_t *)&reg_value, 4);
			break;
		case PORT_WRAPPER_SGMII0_RGMII5:
		case PORT_WRAPPER_SGMII1_RGMII5:
		case PORT_WRAPPER_SGMII0_RGMII4:
		case PORT_WRAPPER_SGMII1_RGMII4:
		case PORT_WRAPPER_SGMII4_RGMII4:

		/*config sgmii */
			if ((mac_mode == PORT_WRAPPER_SGMII0_RGMII5)
				||(mac_mode == PORT_WRAPPER_SGMII0_RGMII4)) {
				/*PSGMII channnel 0 as SGMII*/
				reg_value = 0x2001;
				fal_psgmii_reg_set(dev_id, 0x1b4,
								(a_uint8_t *)&reg_value, 4);
				udelay(1000);
			}
			if ((mac_mode == PORT_WRAPPER_SGMII1_RGMII5)
				||(mac_mode == PORT_WRAPPER_SGMII1_RGMII4)) {
				/*PSGMII channnel 1 as SGMII*/
				reg_value = 0x2003;
				fal_psgmii_reg_set(dev_id, 0x1b4,
								(a_uint8_t *)&reg_value, 4);
				udelay(1000);
			}
			if ((mac_mode == PORT_WRAPPER_SGMII4_RGMII4)) {
				/*PSGMII channnel 4 as SGMII*/
				reg_value = 0x2005;
				fal_psgmii_reg_set(dev_id, 0x1b4,
								(a_uint8_t *)&reg_value, 4);
				udelay(1000);
			}

			/*clock gen 1*/
			reg_value = 0xea6;
			fal_psgmii_reg_set(dev_id, 0x13c,
							(a_uint8_t *)&reg_value, 4);
			mdelay(10);
			/*softreset psgmii, fixme*/
			gcc_addr = ioremap_nocache(0x1812000, 0x200);
			if (!gcc_addr) {
				SSDK_ERROR("gcc map fail!\n");
				return 0;
			} else {
				SSDK_INFO("gcc map success!\n");
				writel(0x20, gcc_addr+0xc);
				mdelay(10);
				writel(0x0, gcc_addr+0xc);
				mdelay(10);
				iounmap(gcc_addr);
			}
			/*relock pll*/
			reg_value = 0x2803;
			fal_psgmii_reg_set(dev_id, DESS_PSGMII_PLL_VCO_RELATED_CONTROL_1,
							(a_uint8_t *)&reg_value, 4);
			udelay(1000);
			reg_value = 0x4ADA;
			fal_psgmii_reg_set(dev_id, DESS_PSGMII_VCO_CALIBRATION_CONTROL_1,
							(a_uint8_t *)&reg_value, 4);
			udelay(1000);
			reg_value = 0xADA;
			fal_psgmii_reg_set(dev_id, DESS_PSGMII_VCO_CALIBRATION_CONTROL_1,
							(a_uint8_t *)&reg_value, 4);
			udelay(1000);

			/* Reconfig channel 0 as SGMII and re autoneg*/
			if ((mac_mode == PORT_WRAPPER_SGMII0_RGMII5)
				||(mac_mode == PORT_WRAPPER_SGMII0_RGMII4)) {
			/*PSGMII channnel 0 as SGMII*/
			reg_value = 0x2001;
			fal_psgmii_reg_set(dev_id, 0x1b4,
								(a_uint8_t *)&reg_value, 4);
			udelay(1000);
			/* restart channel 0 autoneg*/
			reg_value = 0xc4;
			fal_psgmii_reg_set(dev_id, 0x1c8,
							(a_uint8_t *)&reg_value, 4);
			mdelay(10);
			reg_value = 0x44;
			fal_psgmii_reg_set(dev_id, 0x1c8,
							(a_uint8_t *)&reg_value, 4);
			mdelay(10);
			}
			/* Reconfig channel 1 as SGMII and re autoneg*/
			if ((mac_mode == PORT_WRAPPER_SGMII1_RGMII5)
				||(mac_mode == PORT_WRAPPER_SGMII1_RGMII4)) {

			/*PSGMII channnel 1 as SGMII*/
			reg_value = 0x2003;
			fal_psgmii_reg_set(dev_id, 0x1b4,
							(a_uint8_t *)&reg_value, 4);
			udelay(1000);
			/* restart channel 1 autoneg*/
			reg_value = 0xc4;
			fal_psgmii_reg_set(dev_id, 0x1e0,
							(a_uint8_t *)&reg_value, 4);
			mdelay(10);
			reg_value = 0x44;
			fal_psgmii_reg_set(dev_id, 0x1e0,
							(a_uint8_t *)&reg_value, 4);
			mdelay(10);

			}
			/* Reconfig channel 4 as SGMII and re autoneg*/
			if ((mac_mode == PORT_WRAPPER_SGMII4_RGMII4)) {
			/*PSGMII channnel 4 as SGMII*/
			reg_value = 0x2005;
			fal_psgmii_reg_set(dev_id, 0x1b4,
							(a_uint8_t *)&reg_value, 4);
			udelay(1000);
			/* restart channel 4 autoneg*/
			reg_value = 0xc4;
			fal_psgmii_reg_set(dev_id, 0x228,
							(a_uint8_t *)&reg_value, 4);
			mdelay(10);
			reg_value = 0x44;
			fal_psgmii_reg_set(dev_id, 0x228,
							(a_uint8_t *)&reg_value, 4);
			mdelay(10);
			}

		  	/* config RGMII*/
			reg_value = 0x400;
			fal_reg_set(dev_id, 0x4, (a_uint8_t *)&reg_value, 4);
			/* config mac5 RGMII*/
			if ((mac_mode == PORT_WRAPPER_SGMII0_RGMII5)
				||(mac_mode == PORT_WRAPPER_SGMII1_RGMII5)) {
				qca_ar8327_phy_dbg_write(0, 4, 0x5, 0x2d47);
				qca_ar8327_phy_dbg_write(0, 4, 0xb, 0xbc40);
				qca_ar8327_phy_dbg_write(0, 4, 0x0, 0x82ee);
				reg_value = 0x72;
				qca_switch_reg_write(dev_id, 0x90, (a_uint8_t *)&reg_value, 4);
			}
			/* config mac4 RGMII*/
			if ((mac_mode == PORT_WRAPPER_SGMII0_RGMII4)
				||(mac_mode == PORT_WRAPPER_SGMII1_RGMII4)
				||(mac_mode == PORT_WRAPPER_SGMII4_RGMII4)) {
				qca_ar8327_phy_dbg_write(dev_id, 4, 0x5, 0x2d47);
				qca_ar8327_phy_dbg_write(dev_id, 4, 0xb, 0xbc40);
				qca_ar8327_phy_dbg_write(dev_id, 4, 0x0, 0x82ee);
				reg_value = 0x72;
				qca_switch_reg_write(dev_id, 0x8c, (a_uint8_t *)&reg_value, 4);
			}
			break;
		case PORT_WRAPPER_PSGMII_RMII0_RMII1:
		case PORT_WRAPPER_PSGMII_RMII0:
		case PORT_WRAPPER_PSGMII_RMII1:
			reg_value = 0x2200;
			qca_psgmii_reg_write(dev_id, DESS_PSGMII_MODE_CONTROL,
				(a_uint8_t *)&reg_value, 4);
			reg_value = 0x8380;
			qca_psgmii_reg_write(dev_id, DESS_PSGMIIPHY_TX_CONTROL,
					(a_uint8_t *)&reg_value, 4);
			/*switch RMII clock source to gcc_ess_clk,ESS_RGMII_CTRL:0x0C000004,dakota rmii1/rmii0 master mode*/
			if(mac_mode== PORT_WRAPPER_PSGMII_RMII0_RMII1)
				reg_value = 0x3000000;
			if(mac_mode== PORT_WRAPPER_PSGMII_RMII0)
				reg_value = 0x1000000;
			if(mac_mode== PORT_WRAPPER_PSGMII_RMII1)
				reg_value = 0x2000000;
			qca_switch_reg_write(dev_id, 0x4, (a_uint8_t *)&reg_value, 4);
			/*enable RMII MAC5 100M/full*/
			if(mac_mode == PORT_WRAPPER_PSGMII_RMII0_RMII1 || mac_mode == PORT_WRAPPER_PSGMII_RMII0)
			{
				reg_value = 0x7d;
				qca_switch_reg_write(dev_id, 0x90, (a_uint8_t *)&reg_value, 4);
			}

			/*enable RMII MAC4 100M/full*/
			if(mac_mode == PORT_WRAPPER_PSGMII_RMII0_RMII1 || mac_mode == PORT_WRAPPER_PSGMII_RMII1)
			{
				reg_value = 0x7d;
				qca_switch_reg_write(dev_id, 0x8C, (a_uint8_t *)&reg_value, 4);
			}
			/*set QM CONTROL REGISTER FLOW_DROP_CNT as max*/
			reg_value = 0x7f007f;
			qca_switch_reg_write(dev_id, 0x808, (a_uint8_t *)&reg_value, 4);

			/*relock PSGMII PLL*/
			reg_value = 0x2803;
			fal_psgmii_reg_set(dev_id, DESS_PSGMII_PLL_VCO_RELATED_CONTROL_1,
							(a_uint8_t *)&reg_value, 4);
			udelay(1000);
			reg_value = 0x4ADA;
			fal_psgmii_reg_set(dev_id, DESS_PSGMII_VCO_CALIBRATION_CONTROL_1,
							(a_uint8_t *)&reg_value, 4);
			udelay(1000);
			reg_value = 0xADA;
			fal_psgmii_reg_set(dev_id, DESS_PSGMII_VCO_CALIBRATION_CONTROL_1,
							(a_uint8_t *)&reg_value, 4);
			udelay(1000);
			break;
	}

	return 0;
}

static int
qca_dess_hw_init(ssdk_init_cfg *cfg, a_uint32_t dev_id)
{
	a_uint32_t reg_value = 0;
	hsl_api_t *p_api;

	qca_switch_init(dev_id);
#ifdef IN_PORTVLAN
	ssdk_portvlan_init(dev_id);
#endif

	#ifdef IN_PORTVLAN
	fal_port_rxhdr_mode_set(dev_id, 0, FAL_ALL_TYPE_FRAME_EN);
	#endif
	#ifdef IN_IP
	fal_ip_route_status_set(dev_id, A_TRUE);
	#endif

	ssdk_flow_default_act_init(dev_id);

	/*set normal hash and disable nat/napt*/
	qca_switch_reg_read(dev_id, 0x0e38, (a_uint8_t *)&reg_value, 4);
	reg_value = (reg_value|0x1000000|0x8);
	reg_value &= ~2;
	qca_switch_reg_write(dev_id, 0x0e38, (a_uint8_t *)&reg_value, 4);
	#ifdef IN_IP
	fal_ip_vrf_base_addr_set(dev_id, 0, 0);
	#endif

	p_api = hsl_api_ptr_get (dev_id);
	if (p_api && p_api->port_flowctrl_thresh_set)
		p_api->port_flowctrl_thresh_set(dev_id, 0, SSDK_PORT0_FC_THRESH_ON_DFLT,
							SSDK_PORT0_FC_THRESH_OFF_DFLT);

	if (p_api && p_api->ip_glb_lock_time_set)
		p_api->ip_glb_lock_time_set(dev_id, FAL_GLB_LOCK_TIME_100US);


	/*config psgmii,sgmii or rgmii mode for Dakota*/
	ssdk_dess_mac_mode_init(dev_id, cfg->mac_mode);

	/*add BGA Board led contorl*/
	ssdk_dess_led_init(cfg);

	return 0;
}
#endif

#ifdef HPPE
static int qca_hppe_vsi_hw_init(a_uint32_t dev_id)
{
	return ppe_vsi_init(dev_id);
}

static int qca_hppe_fdb_hw_init(a_uint32_t dev_id)
{
	a_uint32_t port = 0;
	adpt_api_t *p_api;

	p_api = adpt_api_ptr_get(dev_id);
	if (!p_api)
		return SW_FAIL;

	if (!p_api->adpt_port_bridge_txmac_set ||
		!p_api->adpt_fdb_port_promisc_mode_set)
		return SW_FAIL;

	for(port = 0; port < SSDK_MAX_PORT_NUM; port++)
	{
		fal_fdb_port_learning_ctrl_set(dev_id, port, A_TRUE, FAL_MAC_FRWRD);
		fal_fdb_port_stamove_ctrl_set(dev_id, port, A_TRUE, FAL_MAC_FRWRD);
		fal_portvlan_member_update(dev_id, port, 0x7f);
		if (port == SSDK_PORT_CPU)
			p_api->adpt_port_bridge_txmac_set(dev_id, port, A_TRUE);
		else
			p_api->adpt_port_bridge_txmac_set(dev_id, port, A_FALSE);
		p_api->adpt_fdb_port_promisc_mode_set(dev_id, port, A_TRUE);
	}

	fal_fdb_aging_ctrl_set(dev_id, A_TRUE);
	fal_fdb_learning_ctrl_set(dev_id, A_TRUE);

	return 0;
}

static int
qca_hppe_portctrl_hw_init(a_uint32_t dev_id)
{
	a_uint32_t i = 0, val;

	for (i = 0; i < 2; i++)
	{
		val = 0x00000081;
		qca_switch_reg_write(dev_id, 0x00003008 + (0x4000*i), (a_uint8_t *)&val, 4);
	}

	for(i = 1; i < 7; i++) {
		hppe_port_type[i - 1] = PORT_GMAC_TYPE;
		fal_port_txmac_status_set (dev_id, i, A_FALSE);
		fal_port_rxmac_status_set (dev_id, i, A_FALSE);
		fal_port_rxfc_status_set(dev_id, i, A_TRUE);
		fal_port_txfc_status_set(dev_id, i, A_TRUE);
		fal_port_max_frame_size_set(dev_id, i, SSDK_MAX_FRAME_SIZE);
	}

	for(i = 5; i < 7; i++) {
		hppe_port_type[i - 1] = PORT_XGMAC_TYPE;
		fal_port_txmac_status_set (dev_id, i, A_FALSE);
		fal_port_rxmac_status_set (dev_id, i, A_FALSE);
		fal_port_rxfc_status_set(dev_id, i, A_TRUE);
		fal_port_txfc_status_set(dev_id, i, A_TRUE);
		fal_port_max_frame_size_set(dev_id, i, SSDK_MAX_FRAME_SIZE);
	}

	for(i = 1; i < 7; i++) {
		hppe_port_type[i -1] = 0;
	}
	return 0;
}

static int
qca_hppe_policer_hw_init(a_uint32_t dev_id)
{
	a_uint32_t i = 0;

	fal_policer_timeslot_set(dev_id, 600);

	for(i = 0; i < 8; i ++)
	{
		fal_port_policer_compensation_byte_set(dev_id, i, 4);
	}

	return 0;
}

static int
qca_hppe_shaper_hw_init(a_uint32_t dev_id)
{
	fal_shaper_token_number_t port_token_number, queue_token_number;
	fal_shaper_token_number_t flow_token_number;
	a_uint32_t i = 0;

	port_token_number.c_token_number_negative_en = 0;
	port_token_number.c_token_number = 0x3fffffff;
	queue_token_number.c_token_number_negative_en = 0;
	queue_token_number.c_token_number = 0x3fffffff;
	queue_token_number.e_token_number_negative_en = 0;
	queue_token_number.e_token_number = 0x3fffffff;
	flow_token_number.c_token_number_negative_en = 0;
	flow_token_number.c_token_number = 0x3fffffff;
	flow_token_number.e_token_number_negative_en = 0;
	flow_token_number.e_token_number = 0x3fffffff;

	for(i = 0; i < 8; i ++)
	{
		fal_port_shaper_token_number_set(dev_id, i, &port_token_number);
	}

	for(i = 0; i < 300; i ++)
	{
		fal_queue_shaper_token_number_set(dev_id, i, &queue_token_number);
	}

	for(i = 0; i < 64; i ++)
	{
		fal_flow_shaper_token_number_set(dev_id, i, &flow_token_number);
	}

	fal_port_shaper_timeslot_set(dev_id, 8);
	fal_flow_shaper_timeslot_set(dev_id, 64);
	fal_queue_shaper_timeslot_set(dev_id, 300);
	fal_shaper_ipg_preamble_length_set(dev_id, 20);

	return 0;
}

static int
qca_hppe_portvlan_hw_init(a_uint32_t dev_id)
{
	a_uint32_t port_id = 0, vsi_idx = 0;
	fal_global_qinq_mode_t global_qinq_mode;
	fal_port_qinq_role_t port_qinq_role;
	fal_tpid_t in_eg_tpid;
	fal_vlantag_egress_mode_t vlantag_eg_mode;

	/* configure ingress/egress global QinQ mode as ctag/ctag */
	global_qinq_mode.mask = 0x3;
	global_qinq_mode.ingress_mode = FAL_QINQ_CTAG_MODE;
	global_qinq_mode.egress_mode = FAL_QINQ_CTAG_MODE;
	fal_global_qinq_mode_set(dev_id, &global_qinq_mode);

	/* configure port0 - port7 ingress/egress QinQ role as edge/edge */
	port_qinq_role.mask = 0x3;
	port_qinq_role.ingress_port_role = FAL_QINQ_CORE_PORT;
	port_qinq_role.egress_port_role = FAL_QINQ_CORE_PORT;
	fal_port_qinq_mode_set(dev_id, 0, &port_qinq_role);
	port_qinq_role.mask = 0x3;
	port_qinq_role.ingress_port_role = FAL_QINQ_EDGE_PORT;
	port_qinq_role.egress_port_role = FAL_QINQ_EDGE_PORT;
	for (port_id = 1; port_id < 8; port_id++)
		fal_port_qinq_mode_set(dev_id, port_id, &port_qinq_role);

	/* configure ingress and egress stpid/ctpid as 0x88a8/0x8100 */
	in_eg_tpid.mask = 0x3;
	in_eg_tpid.ctpid = FAL_DEF_VLAN_CTPID;
	in_eg_tpid.stpid = FAL_DEF_VLAN_STPID;
	fal_ingress_tpid_set(dev_id, &in_eg_tpid);
	fal_egress_tpid_set(dev_id, &in_eg_tpid);

	/* configure port0 - port7 ingress vlan translation mismatched command as forward*/
	for (port_id = 0; port_id < 8; port_id++)
		fal_port_vlan_xlt_miss_cmd_set(dev_id, port_id, FAL_MAC_FRWRD);

	/* configure port0 - port7 stag/ctag egress mode as unmodified/unmodified */
	vlantag_eg_mode.mask = 0x3;
	vlantag_eg_mode.stag_mode = FAL_EG_UNMODIFIED;
	vlantag_eg_mode.ctag_mode = FAL_EG_UNMODIFIED;
	for (port_id = 0; port_id < 8; port_id++)
		fal_port_vlantag_egmode_set(dev_id, port_id, &vlantag_eg_mode);

	/* configure the port0 - port7 of vsi0 - vsi31 to unmodified */
	for (vsi_idx = 0; vsi_idx < 32; vsi_idx++)
		for (port_id = 0; port_id < 8; port_id++)
			fal_port_vsi_egmode_set(dev_id, vsi_idx, port_id, FAL_EG_UNMODIFIED);

	/* configure port0 - port7 vsi tag mode control to enable */
	for (port_id = 0; port_id < 8; port_id++)
		fal_port_vlantag_vsi_egmode_enable(dev_id, port_id, A_TRUE);

	return 0;
}

fal_port_scheduler_cfg_t port_scheduler0_tbl[] = {
	{0xee, 6, 0},
	{0xde, 4, 5},
	{0x9f, 0, 6},
	{0xbe, 5, 0},
	{0x7e, 6, 7},
	{0x5f, 0, 5},
	{0x9f, 7, 6},
	{0xbe, 5, 0},
	{0xfc, 6, 1},
	{0xdd, 0, 5},
	{0xde, 1, 0},
	{0xbe, 5, 6},
	{0xbb, 0, 2},
	{0xdb, 6, 5},
	{0xde, 2, 0},
	{0xbe, 5, 6},
	{0x3f, 0, 7},
	{0x7e, 6, 0},
	{0xde, 7, 5},
	{0x9f, 0, 6},
	{0xb7, 5, 3},
	{0xf6, 6, 0},
	{0xde, 3, 5},
	{0x9f, 0, 6},
	{0xbe, 5, 0},
	{0xee, 6, 4},
	{0xcf, 0, 5},
	{0x9f, 4, 6},
	{0xbe, 5, 0},
	{0x7e, 6, 7},
	{0x5f, 0, 5},
	{0xde, 7, 0},
	{0xbe, 5, 6},
	{0xbd, 0, 1},
	{0xdd, 6, 5},
	{0xde, 1, 0},
	{0xbe, 5, 6},
	{0xbb, 0, 2},
	{0xfa, 6, 0},
	{0xde, 2, 5},
	{0x9f, 0, 6},
	{0x3f, 5, 7},
	{0x7e, 6, 0},
	{0xde, 7, 5},
	{0x9f, 0, 6},
	{0xb7, 5, 3},
	{0xf6, 6, 0},
	{0xde, 3, 5},
	{0x9f, 0, 6},
	{0xaf, 5, 4},
};

fal_port_scheduler_cfg_t port_scheduler1_tbl[] = {
	{0x30, 5, 6},
	{0x30, 4, 0},
	{0x30, 5, 6},
	{0x11, 0, 5},
	{0x50, 6, 0},
	{0x30, 5, 6},
	{0x21, 0, 4},
	{0x21, 5, 6},
	{0x30, 4, 0},
	{0x50, 6, 5},
	{0x11, 0, 6},
	{0x30, 5, 0},
	{0x30, 4, 6},
	{0x11, 0, 5},
	{0x50, 6, 0},
	{0x30, 5, 6},
	{0x11, 0, 5},
	{0x11, 4, 6},
	{0x30, 5, 0},
	{0x50, 6, 5},
	{0x11, 0, 6},
	{0x30, 5, 0},
	{0x30, 4, 6},
	{0x11, 0, 5},
	{0x50, 6, 0},
};

fal_port_tdm_tick_cfg_t port_tdm0_tbl[] = {
	{1, FAL_PORT_TDB_DIR_INGRESS, 0},
	{1, FAL_PORT_TDB_DIR_EGRESS, 5},
	{1, FAL_PORT_TDB_DIR_INGRESS, 5},
	{1, FAL_PORT_TDB_DIR_EGRESS, 7},
	{1, FAL_PORT_TDB_DIR_INGRESS, 1},
	{1, FAL_PORT_TDB_DIR_EGRESS, 6},
	{1, FAL_PORT_TDB_DIR_INGRESS, 6},
	{1, FAL_PORT_TDB_DIR_EGRESS, 0},
	{1, FAL_PORT_TDB_DIR_INGRESS, 0},
	{1, FAL_PORT_TDB_DIR_EGRESS, 7},
	{1, FAL_PORT_TDB_DIR_INGRESS, 7},
	{1, FAL_PORT_TDB_DIR_EGRESS, 5},
	{1, FAL_PORT_TDB_DIR_INGRESS, 5},
	{1, FAL_PORT_TDB_DIR_EGRESS, 0},
	{1, FAL_PORT_TDB_DIR_INGRESS, 6},
	{1, FAL_PORT_TDB_DIR_EGRESS, 6},
	{1, FAL_PORT_TDB_DIR_INGRESS, 0},
	{1, FAL_PORT_TDB_DIR_EGRESS, 3},
	{1, FAL_PORT_TDB_DIR_INGRESS, 2},
	{1, FAL_PORT_TDB_DIR_EGRESS, 7},
	{1, FAL_PORT_TDB_DIR_INGRESS, 7},
	{1, FAL_PORT_TDB_DIR_EGRESS, 5},
	{1, FAL_PORT_TDB_DIR_INGRESS, 5},
	{1, FAL_PORT_TDB_DIR_EGRESS, 0},
	{1, FAL_PORT_TDB_DIR_INGRESS, 0},
	{1, FAL_PORT_TDB_DIR_EGRESS, 6},
	{1, FAL_PORT_TDB_DIR_INGRESS, 6},
	{1, FAL_PORT_TDB_DIR_EGRESS, 0},
	{1, FAL_PORT_TDB_DIR_INGRESS, 7},
	{1, FAL_PORT_TDB_DIR_EGRESS, 7},
	{1, FAL_PORT_TDB_DIR_INGRESS, 5},
	{1, FAL_PORT_TDB_DIR_EGRESS, 5},
	{1, FAL_PORT_TDB_DIR_INGRESS, 0},
	{1, FAL_PORT_TDB_DIR_EGRESS, 0},
	{1, FAL_PORT_TDB_DIR_INGRESS, 6},
	{1, FAL_PORT_TDB_DIR_EGRESS, 6},
	{1, FAL_PORT_TDB_DIR_INGRESS, 0},
	{1, FAL_PORT_TDB_DIR_EGRESS, 0},
	{1, FAL_PORT_TDB_DIR_INGRESS, 7},
	{1, FAL_PORT_TDB_DIR_EGRESS, 7},
	{1, FAL_PORT_TDB_DIR_INGRESS, 0},
	{1, FAL_PORT_TDB_DIR_EGRESS, 5},
	{1, FAL_PORT_TDB_DIR_INGRESS, 5},
	{1, FAL_PORT_TDB_DIR_EGRESS, 4},
	{1, FAL_PORT_TDB_DIR_INGRESS, 6},
	{1, FAL_PORT_TDB_DIR_EGRESS, 6},
	{1, FAL_PORT_TDB_DIR_INGRESS, 7},
	{1, FAL_PORT_TDB_DIR_EGRESS, 0},
	{1, FAL_PORT_TDB_DIR_INGRESS, 0},
	{1, FAL_PORT_TDB_DIR_EGRESS, 7},
	{1, FAL_PORT_TDB_DIR_INGRESS, 4},
	{1, FAL_PORT_TDB_DIR_EGRESS, 5},
	{1, FAL_PORT_TDB_DIR_INGRESS, 5},
	{1, FAL_PORT_TDB_DIR_EGRESS, 0},
	{1, FAL_PORT_TDB_DIR_INGRESS, 6},
	{1, FAL_PORT_TDB_DIR_EGRESS, 6},
	{1, FAL_PORT_TDB_DIR_INGRESS, 0},
	{1, FAL_PORT_TDB_DIR_EGRESS, 1},
	{1, FAL_PORT_TDB_DIR_INGRESS, 7},
	{1, FAL_PORT_TDB_DIR_EGRESS, 7},
	{1, FAL_PORT_TDB_DIR_INGRESS, 0},
	{1, FAL_PORT_TDB_DIR_EGRESS, 5},
	{1, FAL_PORT_TDB_DIR_INGRESS, 5},
	{1, FAL_PORT_TDB_DIR_EGRESS, 0},
	{1, FAL_PORT_TDB_DIR_INGRESS, 0},
	{1, FAL_PORT_TDB_DIR_EGRESS, 6},
	{1, FAL_PORT_TDB_DIR_INGRESS, 6},
	{1, FAL_PORT_TDB_DIR_EGRESS, 0},
	{1, FAL_PORT_TDB_DIR_INGRESS, 7},
	{1, FAL_PORT_TDB_DIR_EGRESS, 7},
	{1, FAL_PORT_TDB_DIR_INGRESS, 5},
	{1, FAL_PORT_TDB_DIR_EGRESS, 5},
	{1, FAL_PORT_TDB_DIR_INGRESS, 0},
	{1, FAL_PORT_TDB_DIR_EGRESS, 0},
	{1, FAL_PORT_TDB_DIR_INGRESS, 6},
	{1, FAL_PORT_TDB_DIR_EGRESS, 6},
	{1, FAL_PORT_TDB_DIR_INGRESS, 3},
	{1, FAL_PORT_TDB_DIR_EGRESS, 0},
	{1, FAL_PORT_TDB_DIR_INGRESS, 7},
	{1, FAL_PORT_TDB_DIR_EGRESS, 7},
	{1, FAL_PORT_TDB_DIR_INGRESS, 0},
	{1, FAL_PORT_TDB_DIR_EGRESS, 5},
	{1, FAL_PORT_TDB_DIR_INGRESS, 5},
	{1, FAL_PORT_TDB_DIR_EGRESS, 0},
	{1, FAL_PORT_TDB_DIR_INGRESS, 6},
	{1, FAL_PORT_TDB_DIR_EGRESS, 6},
	{1, FAL_PORT_TDB_DIR_INGRESS, 7},
	{1, FAL_PORT_TDB_DIR_EGRESS, 2},
	{1, FAL_PORT_TDB_DIR_INGRESS, 0},
	{1, FAL_PORT_TDB_DIR_EGRESS, 7},
	{1, FAL_PORT_TDB_DIR_INGRESS, 5},
	{1, FAL_PORT_TDB_DIR_EGRESS, 5},
	{1, FAL_PORT_TDB_DIR_INGRESS, 6},
	{1, FAL_PORT_TDB_DIR_EGRESS, 0},
	{1, FAL_PORT_TDB_DIR_INGRESS, 7},
	{1, FAL_PORT_TDB_DIR_EGRESS, 6},
};

static int
qca_hppe_tdm_hw_init(a_uint32_t dev_id)
{
	adpt_api_t *p_api;
	a_uint32_t i = 0;
	a_uint32_t num;
	fal_port_tdm_ctrl_t tdm_ctrl;
	fal_port_scheduler_cfg_t *scheduler_cfg;
	fal_port_tdm_tick_cfg_t *bm_cfg;

	p_api = adpt_api_ptr_get(dev_id);
	if (!p_api)
		return SW_FAIL;

	if (!p_api->adpt_port_scheduler_cfg_set ||
		!p_api->adpt_tdm_tick_num_set)
		return SW_FAIL;

	if (ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->tm_tick_mode == 0) {
		num = sizeof(port_scheduler0_tbl) / sizeof(fal_port_scheduler_cfg_t);
		scheduler_cfg = port_scheduler0_tbl;
	} else if (ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->tm_tick_mode == 1) {
		num = sizeof(port_scheduler1_tbl) / sizeof(fal_port_scheduler_cfg_t);
		scheduler_cfg = port_scheduler1_tbl;
	} else {
		return SW_BAD_VALUE;
	}

	for (i = 0; i < num; i++) {
		p_api->adpt_port_scheduler_cfg_set(0, i, &scheduler_cfg[i]);
	}
	p_api->adpt_tdm_tick_num_set(0, num);

	if (!p_api->adpt_port_tdm_tick_cfg_set ||
		!p_api->adpt_port_tdm_ctrl_set)
		return SW_FAIL;
	if (ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->bm_tick_mode == 0) {
		num = sizeof(port_tdm0_tbl) / sizeof(fal_port_tdm_tick_cfg_t);
		bm_cfg = port_tdm0_tbl;
	} else {
		return SW_BAD_VALUE;
	}
	for (i = 0; i < num; i++) {
		p_api->adpt_port_tdm_tick_cfg_set(0, i, &bm_cfg[i]);
	}
	tdm_ctrl.enable = 1;
	tdm_ctrl.offset = 0;
	tdm_ctrl.depth = num;
	p_api->adpt_port_tdm_ctrl_set(0, &tdm_ctrl);
	SSDK_INFO("tdm setup num=%d\n", num);
	return 0;
}

static int
qca_hppe_bm_hw_init(a_uint32_t dev_id)
{
	a_uint32_t i = 0;
	fal_bm_dynamic_cfg_t cfg;

	for (i = 0; i <  15; i++) {
		/* enable fc */
		fal_port_bm_ctrl_set(0, i, 1);
		/* map to group 0 */
		fal_port_bufgroup_map_set(0, i, 0);
	}

	fal_bm_bufgroup_buffer_set(dev_id, 0, 1600);

	/* set reserved buffer */
	fal_bm_port_reserved_buffer_set(dev_id, 0, 0, 52);
	for (i = 1; i < 8; i++)
		fal_bm_port_reserved_buffer_set(dev_id, i, 0, 18);
	for (i = 8; i < 14; i++)
		fal_bm_port_reserved_buffer_set(dev_id, i, 0, 163);
	fal_bm_port_reserved_buffer_set(dev_id, 14, 0, 40);

	memset(&cfg, 0, sizeof(cfg));
	cfg.resume_min_thresh = 0;
	cfg.resume_off = 36;
	cfg.weight= 4;
	cfg.shared_ceiling = 250;
	for (i = 0; i < 15; i++)
		fal_bm_port_dynamic_thresh_set(dev_id, i, &cfg);
	return 0;
}

static int
qca_hppe_qm_hw_init(a_uint32_t dev_id)
{
	a_uint32_t i;
	fal_ucast_queue_dest_t queue_dst;
	fal_ac_obj_t obj;
	fal_ac_ctrl_t ac_ctrl;
	fal_ac_group_buffer_t group_buff;
	fal_ac_dynamic_threshold_t  dthresh_cfg;
	fal_ac_static_threshold_t sthresh_cfg;
	a_uint32_t qbase = 0;

	memset(&queue_dst, 0, sizeof(queue_dst));

	/*
	 * Redirect service code 2 to queue 1
	 * TODO: keep sync with  NSS
	 */
	queue_dst.service_code_en = A_TRUE;
	queue_dst.service_code = 2;
	fal_ucast_queue_base_profile_set(dev_id, &queue_dst, 8, 0);

	queue_dst.service_code = 3;
	fal_ucast_queue_base_profile_set(dev_id, &queue_dst, 128, 0);

	queue_dst.service_code = 4;
	fal_ucast_queue_base_profile_set(dev_id, &queue_dst, 128, 0);

	queue_dst.service_code = 5;
	fal_ucast_queue_base_profile_set(dev_id, &queue_dst, 0, 0);

	queue_dst.service_code = 6;
	fal_ucast_queue_base_profile_set(dev_id, &queue_dst, 8, 0);

	queue_dst.service_code_en = A_FALSE;
	queue_dst.service_code = 0;
	for(i = 0; i < SSDK_MAX_PORT_NUM; i++) {
		queue_dst.dst_port = i;
		qbase = ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->scheduler_cfg.pool[i].ucastq_start;
		fal_ucast_queue_base_profile_set(dev_id, &queue_dst, qbase, i);
	}

	/*
	 * Enable PPE source profile 1 and map it to PPE queue 4
	 */
	memset(&queue_dst, 0, sizeof(queue_dst));
	queue_dst.src_profile = 1;

	/*
	 * Enable service code mapping for profile 1
	 */
	queue_dst.service_code_en = A_TRUE;
	for (i = 0; i < SSDK_MAX_SERVICE_CODE_NUM; i++) {
		queue_dst.service_code = i;

		if (i == 2 || i == 6) {
			fal_ucast_queue_base_profile_set(dev_id, &queue_dst, 8, 0);
		} else if (i == 3 || i == 4) {
			fal_ucast_queue_base_profile_set(dev_id, &queue_dst, 128, 0);
		} else {
			fal_ucast_queue_base_profile_set(dev_id, &queue_dst, 4, 0);
		}
	}
	queue_dst.service_code_en = A_FALSE;
	queue_dst.service_code = 0;

	/*
	 * Enable cpu code mapping for profile 1
	 */
	queue_dst.cpu_code_en = A_TRUE;
	for (i = 0; i < SSDK_MAX_CPU_CODE_NUM; i++) {
		queue_dst.cpu_code = i;
		fal_ucast_queue_base_profile_set(dev_id, &queue_dst, 4, 0);
	}
	queue_dst.cpu_code_en = A_FALSE;
	queue_dst.cpu_code = 0;

	/*
	 * Enable destination port mappings for profile 1
	 */
	for (i = 0; i < SSDK_MAX_PORT_NUM; i++) {
		queue_dst.dst_port = i;
		qbase = ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->scheduler_cfg.pool[i].ucastq_start;
		fal_ucast_queue_base_profile_set(dev_id, &queue_dst, qbase, i);
	}

	for (i = SSDK_MAX_PORT_NUM; i < SSDK_MAX_VIRTUAL_PORT_NUM; i++) {
		queue_dst.dst_port = i;
		fal_ucast_queue_base_profile_set(dev_id, &queue_dst, 4, 0);
	}
	queue_dst.dst_port = 0;

	/* queue ac*/
	ac_ctrl.ac_en = 1;
	ac_ctrl.ac_fc_en = 0;
	for (i = 0; i < 300; i++) {
		obj.type = FAL_AC_QUEUE;
		obj.obj_id = i;
		fal_ac_ctrl_set(0, &obj, &ac_ctrl);
		fal_ac_queue_group_set(0, i, 0);
		fal_ac_prealloc_buffer_set(0, &obj, 0);
	}

	group_buff.prealloc_buffer = 0;
	group_buff.total_buffer = 2000;
	fal_ac_group_buffer_set(0, 0, &group_buff);

	memset(&dthresh_cfg, 0, sizeof(dthresh_cfg));
	dthresh_cfg.shared_weight = 4;
	dthresh_cfg.ceiling = 250;
	dthresh_cfg.green_resume_off = 36;
	for (i = 0; i < 256; i++)
		fal_ac_dynamic_threshold_set(0, i, &dthresh_cfg);

	memset(&sthresh_cfg, 0, sizeof(sthresh_cfg));
	sthresh_cfg.green_max = 250;
	sthresh_cfg.green_resume_off = 36;
	for (i = 256; i < 300; i++) {
		obj.type = FAL_AC_QUEUE;
		obj.obj_id = i;
		fal_ac_static_threshold_set(0, &obj, &sthresh_cfg);
	}

	return 0;
}

static int
qca_hppe_qos_scheduler_hw_init(a_uint32_t dev_id)
{
	a_uint32_t i = 0;
	fal_qos_scheduler_cfg_t cfg;
	fal_queue_bmp_t queue_bmp;
	fal_qos_group_t group_sel;
	fal_qos_pri_precedence_t pri_pre;
	ssdk_dt_scheduler_cfg *dt_cfg = &(ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->scheduler_cfg);

	memset(&cfg, 0, sizeof(cfg));

	/* L1 shceduler */
	for (i = 0; i < SSDK_L1SCHEDULER_CFG_MAX; i++) {
		if (dt_cfg->l1cfg[i].valid) {
			cfg.sp_id = dt_cfg->l1cfg[i].port_id;
			cfg.c_pri = dt_cfg->l1cfg[i].cpri;
			cfg.e_pri = dt_cfg->l1cfg[i].epri;
			cfg.c_drr_id = dt_cfg->l1cfg[i].cdrr_id;
			cfg.e_drr_id = dt_cfg->l1cfg[i].edrr_id;
			cfg.c_drr_wt = 1;
			cfg.e_drr_wt = 1;
			fal_queue_scheduler_set(dev_id, i, 1,
					dt_cfg->l1cfg[i].port_id, &cfg);
		}
	}

	/* L0 shceduler */
	for (i = 0; i < SSDK_L0SCHEDULER_CFG_MAX; i++) {
		if (dt_cfg->l0cfg[i].valid) {
			cfg.sp_id = dt_cfg->l0cfg[i].sp_id;
			cfg.c_pri = dt_cfg->l0cfg[i].cpri;
			cfg.e_pri = dt_cfg->l0cfg[i].epri;
			cfg.c_drr_id = dt_cfg->l0cfg[i].cdrr_id;
			cfg.e_drr_id = dt_cfg->l0cfg[i].edrr_id;
			cfg.c_drr_wt = 1;
			cfg.e_drr_wt = 1;
			fal_queue_scheduler_set(dev_id, i,
					0, dt_cfg->l0cfg[i].port_id, &cfg);
		}
	}

	/* queue--edma ring mapping*/
	memset(&queue_bmp, 0, sizeof(queue_bmp));
	queue_bmp.bmp[0] = 0xF;
	fal_edma_ring_queue_map_set(dev_id, 0, &queue_bmp);
	queue_bmp.bmp[0] = 0xF0;
	fal_edma_ring_queue_map_set(dev_id, 3, &queue_bmp);
	queue_bmp.bmp[0] = 0xF00;
	fal_edma_ring_queue_map_set(dev_id, 1, &queue_bmp);
	queue_bmp.bmp[0] = 0;
	queue_bmp.bmp[4] = 0xFFFF;
	fal_edma_ring_queue_map_set(dev_id, 2, &queue_bmp);

	/* chose qos group 0 */
	group_sel.dscp_group = 0;
	group_sel.flow_group = 0;
	group_sel.pcp_group = 0;
	for (i = 0; i < 8; i++)
		fal_qos_port_group_get(dev_id, i, &group_sel);
	/* qos precedence */
	pri_pre.flow_pri = 4;
	pri_pre.acl_pri = 2;
	pri_pre.dscp_pri = 1;
	pri_pre.pcp_pri = 0;
	pri_pre.preheader_pri = 3;
	for (i = 0; i < 8; i++)
		fal_qos_port_pri_precedence_set(dev_id, i, &pri_pre);

	return 0;
}

static sw_error_t
qca_hppe_interface_mode_init(a_uint32_t dev_id, a_uint32_t mode0, a_uint32_t mode1, a_uint32_t mode2)
{

	adpt_api_t *p_api;
	sw_error_t rv = SW_OK;
	fal_port_t port_id;

	SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

	if (NULL == p_api->adpt_uniphy_mode_set)
		return SW_NOT_SUPPORTED;

	rv = p_api->adpt_uniphy_mode_set(dev_id, SSDK_UNIPHY_INSTANCE0, mode0);

	rv = p_api->adpt_uniphy_mode_set(dev_id, SSDK_UNIPHY_INSTANCE1, mode1);

	rv = p_api->adpt_uniphy_mode_set(dev_id, SSDK_UNIPHY_INSTANCE2, mode2);

	for(port_id =1; port_id <=6; port_id++)
	{
		rv = p_api->adpt_port_mux_mac_type_set(dev_id, port_id, mode0, mode1, mode2);
		if(rv != SW_OK)
		{
			SSDK_ERROR("port_id:%d, mode0:%d, mode1:%d, mode2:%d\n", port_id, mode0, mode1, mode2);
			break;
		}
	}

	return rv;
}


static sw_error_t
qca_hppe_flow_hw_init(a_uint32_t dev_id)
{
	fal_flow_direction_t dir, dir_max;
	fal_flow_mgmt_t mgmt;
	sw_error_t rv;

	memset(&mgmt, 0, sizeof(fal_flow_mgmt_t));
	dir_max = FAL_FLOW_UNKOWN_DIR_DIR;

	/*set redirect to cpu for multicast flow*/
	for (dir = FAL_FLOW_LAN_TO_LAN_DIR; dir <= dir_max; dir++) {
		rv = fal_flow_mgmt_get(dev_id, FAL_FLOW_MCAST, dir, &mgmt);
		if (rv)
			return rv;
		mgmt.miss_action = FAL_MAC_RDT_TO_CPU;
		rv = fal_flow_mgmt_set(dev_id, FAL_FLOW_MCAST, dir, &mgmt);
		if (rv)
			return rv;
	}
	return SW_OK;
}

static int
qca_hppe_hw_init(ssdk_init_cfg *cfg, a_uint32_t dev_id)
{
	a_uint32_t val;

	/* reset ppe */
	ssdk_ppe_reset_init();

	qca_switch_init(dev_id);

	val = 0x3b;
	qca_switch_reg_write(dev_id, 0x000010, (a_uint8_t *)&val, 4);
	val = 0;
	qca_switch_reg_write(dev_id, 0x000008, (a_uint8_t *)&val, 4);

	qca_hppe_bm_hw_init(dev_id);
	qca_hppe_qm_hw_init(dev_id);
	qca_hppe_qos_scheduler_hw_init(dev_id);
	qca_hppe_tdm_hw_init(dev_id);

	qca_hppe_fdb_hw_init(dev_id);
	qca_hppe_vsi_hw_init(dev_id);
	qca_hppe_portvlan_hw_init(dev_id);

	qca_hppe_portctrl_hw_init(dev_id);

	qca_hppe_policer_hw_init(dev_id);

	qca_hppe_shaper_hw_init(dev_id);
	qca_hppe_flow_hw_init(dev_id);

	qca_hppe_interface_mode_init(dev_id, cfg->mac_mode, cfg->mac_mode1,
				cfg->mac_mode2);
	return 0;
}
#endif

static void ssdk_cfg_default_init(ssdk_init_cfg *cfg)
{
	memset(cfg, 0, sizeof(ssdk_init_cfg));
	cfg->cpu_mode = HSL_CPU_1;
	cfg->nl_prot = 30;
	cfg->reg_func.mdio_set = qca_ar8327_phy_write;
	cfg->reg_func.mdio_get = qca_ar8327_phy_read;
	cfg->reg_func.header_reg_set = qca_switch_reg_write;
	cfg->reg_func.header_reg_get = qca_switch_reg_read;
	cfg->reg_func.mii_reg_set = qca_ar8216_mii_write;
	cfg->reg_func.mii_reg_get = qca_ar8216_mii_read;
}

#ifdef IN_RFS
#if defined(CONFIG_RFS_ACCEL)
int ssdk_netdev_rfs_cb(
		struct net_device *dev,
		__be32 src, __be32 dst,
		__be16 sport, __be16 dport,
		u8 proto, u16 rxq_index, u32 action)
{
	return ssdk_rfs_ipct_rule_set(src, dst, sport, dport,
							proto, rxq_index, action);
}
#endif
int ssdk_intf_search(
	fal_intf_mac_entry_t *exist_entry, int num,
	fal_intf_mac_entry_t *new_entry, int *index)
{
	int i = 0;
	*index = 0xffffffff;
	for (i = 0; i < num; i++) {
		if (exist_entry[i].vid_high == 0 && exist_entry[i].vid_low == 0)
			*index = i;
		if (!memcmp(exist_entry[i].mac_addr.uc, new_entry->mac_addr.uc, 6) &&
			exist_entry[i].vid_low == new_entry->vid_low) {
			*index = i;
			return 1;
		}
	}
	return 0;
}

void ssdk_intf_set(struct net_device *dev, char op)
{
	a_uint8_t *devmac = NULL;
	fal_vlan_t entry;
	a_uint32_t tmp_vid = 0xffffffff;
	fal_intf_mac_entry_t intf_entry;
	a_uint32_t wan_port = 0;
	sw_error_t rv = 0;
	static fal_intf_mac_entry_t if_mac_entry[8] = {{0}};
	int index = 0xffffffff;
	/*get mac*/
	devmac = (a_uint8_t*)(dev->dev_addr);
	/*get wan port*/
	wan_port = hsl_dev_wan_port_get(0);
	/*get vid*/
	memset(&intf_entry, 0, sizeof(intf_entry));
	intf_entry.ip4_route = 1;
	intf_entry.ip6_route = 1;
	memcpy(&intf_entry.mac_addr, devmac, 6);

	#if defined(CONFIG_VLAN_8021Q) || defined(CONFIG_VLAN_8021Q_MODULE)
	tmp_vid = vlan_dev_vlan_id(dev);
	if (tmp_vid) {
		intf_entry.vid_low = tmp_vid;
		intf_entry.vid_high = intf_entry.vid_low;
		if (op) {
			if (!ssdk_intf_search(if_mac_entry, 8, &intf_entry, &index)) {
				if (index != 0xffffffff) {
					#ifdef IN_IP
					rv = fal_ip_intf_entry_add(0, &intf_entry);
					#endif
					if (SW_OK == rv) {
						if_mac_entry[index] = intf_entry;
					}
				}
			}
		}
		else {
			if (ssdk_intf_search(if_mac_entry, 8, &intf_entry, &index)) {
				intf_entry.entry_id = if_mac_entry[index].entry_id;
				#ifdef IN_IP
				fal_ip_intf_entry_del(0, 1, &intf_entry);
				#endif
				memset(&if_mac_entry[index], 0, sizeof(fal_intf_mac_entry_t));
			}
		}
		return;
	} else {
		tmp_vid = 0xffffffff;
	}
	#endif
	while(1) {
		#ifdef IN_VLAN
		if (SW_OK != fal_vlan_next(0, tmp_vid, &entry))
		#endif
			break;
		tmp_vid = entry.vid;
		if (tmp_vid != 0) {
			if(entry.mem_ports & wan_port) {
				if (!strcmp(dev->name, "eth0") ||
				    !strcmp(dev->name, "br-wan")) {
					intf_entry.vid_low = tmp_vid;
					intf_entry.vid_high = intf_entry.vid_low;
					if (op) {
						if (!ssdk_intf_search(if_mac_entry, 8, &intf_entry, &index)) {
							if (index != 0xffffffff) {
								#ifdef IN_IP
								rv = fal_ip_intf_entry_add(0, &intf_entry);
								#endif
								if (SW_OK == rv) {
									if_mac_entry[index] = intf_entry;
								}
							}
						}
					}
					else {
						if (ssdk_intf_search(if_mac_entry, 8, &intf_entry, &index)) {
							intf_entry.entry_id = if_mac_entry[index].entry_id;
							#ifdef IN_IP
							fal_ip_intf_entry_del(0, 1, &intf_entry);
							#endif
							memset(&if_mac_entry[index], 0, sizeof(fal_intf_mac_entry_t));
						}
					}
				}
			} else {
				if (strcmp(dev->name, "eth0") &&
				    strcmp(dev->name, "br-wan")) {
					intf_entry.vid_low = tmp_vid;
					intf_entry.vid_high = intf_entry.vid_low;
					if (op) {
						if (!ssdk_intf_search(if_mac_entry, 8, &intf_entry, &index)) {
							if (index != 0xffffffff) {
								#ifdef IN_IP
								rv = fal_ip_intf_entry_add(0, &intf_entry);
								#endif
								if (SW_OK == rv) {
									if_mac_entry[index] = intf_entry;
								}
							}
						}
					}
					else {
						if (ssdk_intf_search(if_mac_entry, 8, &intf_entry, &index)) {
							intf_entry.entry_id = if_mac_entry[index].entry_id;
							#ifdef IN_IP
							fal_ip_intf_entry_del(0, 1, &intf_entry);
							#endif
							memset(&if_mac_entry[index], 0, sizeof(fal_intf_mac_entry_t));
						}
					}
				}
			}
		}
	}

}

#ifdef DESS
static int ssdk_inet_event(struct notifier_block *this, unsigned long event, void *ptr)
{
	struct net_device *dev = ((struct in_ifaddr *)ptr)->ifa_dev->dev;

	if (!strstr(dev->name, "eth") && !strstr(dev->name, "br")) {
		return NOTIFY_DONE;
	}
	switch (event) {
		case NETDEV_DOWN:
			ssdk_intf_set(dev, 0);
			break;
		case NETDEV_UP:
			ssdk_intf_set(dev, 1);
			break;
	}
	return NOTIFY_DONE;
}
#endif
#endif

//#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,14,0))
static int ssdk_dev_event(struct notifier_block *this, unsigned long event, void *ptr)
{
	int rv = 0;
	ssdk_init_cfg cfg;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,14,0))
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);
#else
	struct net_device *dev = (struct net_device *)ptr;
#endif
	switch (event) {
#ifdef IN_RFS
#if defined(CONFIG_RFS_ACCEL)
		case NETDEV_UP:
			#if (LINUX_VERSION_CODE < KERNEL_VERSION(4,4,0))
			if (strstr(dev->name, "eth")) {
				if (dev->netdev_ops && dev->netdev_ops->ndo_register_rfs_filter) {
					dev->netdev_ops->ndo_register_rfs_filter(dev,
						ssdk_netdev_rfs_cb);
				}
			}
			#endif
			break;
#endif
#endif
		case NETDEV_CHANGEMTU:
			if(dev->type == ARPHRD_ETHER) {
				rv = chip_ver_get(0, &cfg);
				if (rv)
					return rv;
				if(cfg.chip_type == CHIP_DESS ||
				   cfg.chip_type == CHIP_ISIS ||
				   cfg.chip_type == CHIP_ISISC){
					fal_frame_max_size_set(0, dev->mtu + 18);
				}
			}
			break;
	}

	return NOTIFY_DONE;
}

#ifdef DESS
static void qca_dess_rfs_remove(void)
{
	/* ssdk_dt_global->switch_reg_access_mode == HSL_REG_LOCAL_BUS */
	if(qca_dess_rfs_registered){
		#if defined (CONFIG_NF_FLOW_COOKIE)
		#ifdef IN_NAT
		#ifdef IN_SFE
		sfe_unregister_flow_cookie_cb(ssdk_flow_cookie_set);
		#endif
		#endif
		#endif
		#ifdef IN_RFS
		rfs_ess_device_unregister(&rfs_dev);
		unregister_inetaddr_notifier(&ssdk_inet_notifier);
		#if defined(CONFIG_RFS_ACCEL)
		#endif
		#endif
		qca_dess_rfs_registered = false;
	}

}

static void qca_dess_rfs_init(void)
{
	if (!qca_dess_rfs_registered) {
		#if defined (CONFIG_NF_FLOW_COOKIE)
		#ifdef IN_NAT
		#ifdef IN_SFE
		sfe_register_flow_cookie_cb(ssdk_flow_cookie_set);
		#endif
		#endif
		#endif

		#ifdef IN_RFS
		memset(&rfs_dev, 0, sizeof(rfs_dev));
		rfs_dev.name = NULL;
		#ifdef IN_FDB
		rfs_dev.mac_rule_cb = ssdk_rfs_mac_rule_set;
		#endif
		#ifdef IN_IP
		rfs_dev.ip4_rule_cb = ssdk_rfs_ip4_rule_set;
		rfs_dev.ip6_rule_cb = ssdk_rfs_ip6_rule_set;
		#endif
		rfs_ess_device_register(&rfs_dev);
		#if defined(CONFIG_RFS_ACCEL)
		#endif
		ssdk_inet_notifier.notifier_call = ssdk_inet_event;
		ssdk_inet_notifier.priority = 1;
		register_inetaddr_notifier(&ssdk_inet_notifier);
		#endif
		qca_dess_rfs_registered = true;
	}
}
#endif

static a_uint32_t ssdk_get_switch_nums(void)
{
	struct device_node *switch_instance = NULL;
	a_uint32_t len = 0;
	const __be32 *num_devices;

	switch_instance = of_find_node_by_name(NULL, "ess-instance");
	if (!switch_instance) {
		return 1;
	}
	else {
		num_devices = of_get_property(switch_instance, "num_devices", &len);
		if (!num_devices)
			return 1;
		else
			return be32_to_cpup(num_devices);
	}
}

static void ssdk_free_priv(void)
{
	a_uint32_t dev_id;
	for (dev_id = 0; dev_id < ssdk_dt_global.num_devices; dev_id++) {
		if (qca_phy_priv_global[dev_id])
			kfree(qca_phy_priv_global[dev_id]);
		if (ssdk_dt_global.ssdk_dt_switch_nodes[dev_id])
			kfree(ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]);

		qca_phy_priv_global[dev_id] = NULL;
		ssdk_dt_global.ssdk_dt_switch_nodes[dev_id] = NULL;
	}

	if (ssdk_dt_global.ssdk_dt_switch_nodes)
		kfree(ssdk_dt_global.ssdk_dt_switch_nodes);
	if (qca_phy_priv_global)
		kfree(qca_phy_priv_global);

	ssdk_dt_global.ssdk_dt_switch_nodes = NULL;
	qca_phy_priv_global = NULL;

	ssdk_dt_global.num_devices = 0;
}

static int ssdk_alloc_priv(void)
{
	int rev = SW_OK;
	a_uint32_t dev_id;
	ssdk_dt_global.num_devices = ssdk_get_switch_nums();
	SSDK_INFO("ess-switch dts node number: %d\n", ssdk_dt_global.num_devices);

	ssdk_dt_global.ssdk_dt_switch_nodes = kzalloc(ssdk_dt_global.num_devices * sizeof(ssdk_dt_cfg *), GFP_KERNEL);
	if (ssdk_dt_global.ssdk_dt_switch_nodes == NULL) {
		return -ENOMEM;
	}

	qca_phy_priv_global = kzalloc(ssdk_dt_global.num_devices * sizeof(struct qca_phy_priv *), GFP_KERNEL);
	if (qca_phy_priv_global == NULL) {
		return -ENOMEM;
	}

	for (dev_id = 0; dev_id < ssdk_dt_global.num_devices; dev_id++) {
		ssdk_dt_global.ssdk_dt_switch_nodes[dev_id] = kzalloc(sizeof(ssdk_dt_cfg), GFP_KERNEL);
		if (ssdk_dt_global.ssdk_dt_switch_nodes[dev_id] == NULL) {
			return -ENOMEM;
		}
		ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->switch_reg_access_mode = HSL_REG_MDIO;
		ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->psgmii_reg_access_mode = HSL_REG_MDIO;
		ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->ess_switch_flag = A_FALSE;

		qca_phy_priv_global[dev_id] = kzalloc(sizeof(struct qca_phy_priv), GFP_KERNEL);
		if (qca_phy_priv_global[dev_id] == NULL) {
			return -ENOMEM;
		}
		qca_phy_priv_global[dev_id]->qca_ssdk_sw_dev_registered = A_FALSE;
		qca_phy_priv_global[dev_id]->ess_switch_flag = A_FALSE;
		qca_ssdk_phy_info_init(dev_id);
		qca_ssdk_port_bmp_init(dev_id);
	}

	return rev;
}

static int __init regi_init(void)
{
	a_uint32_t num = 0, dev_id = 0;
	ssdk_init_cfg cfg;
	garuda_init_spec_cfg chip_spec_cfg;
	#ifdef DESS
	a_uint32_t psgmii_result = 0;
	#endif
	int rv = 0;

	rv = ssdk_alloc_priv();
	if (rv)
		goto out;

	for (num = 0; num < ssdk_dt_global.num_devices; num++) {
		ssdk_cfg_default_init(&cfg);

		#ifndef BOARD_AR71XX
		#if defined(CONFIG_OF) && (LINUX_VERSION_CODE >= KERNEL_VERSION(3,14,0))
		if(SW_DISABLE == ssdk_dt_parse(&cfg, num, &dev_id)) {
			SSDK_INFO("ess-switch node is unavalilable\n");
			continue;
		}
		#endif
		#endif

		/* device id is the array index */
		qca_phy_priv_global[dev_id]->device_id = ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->device_id;
		qca_phy_priv_global[dev_id]->ess_switch_flag = ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->ess_switch_flag;
		qca_phy_priv_global[dev_id]->of_node = ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->of_node;

		rv = ssdk_plat_init(&cfg, dev_id);
		SW_CNTU_ON_ERROR_AND_COND1_OR_GOTO_OUT(rv, -ENODEV);

		ssdk_driver_register(dev_id);

		rv = chip_ver_get(dev_id, &cfg);
		SW_CNTU_ON_ERROR_AND_COND1_OR_GOTO_OUT(rv, -ENODEV);

		ssdk_miireg_ioctrl_register();

		memset(&chip_spec_cfg, 0, sizeof(garuda_init_spec_cfg));
		cfg.chip_spec_cfg = &chip_spec_cfg;

		rv = ssdk_init(dev_id, &cfg);
		SW_CNTU_ON_ERROR_AND_COND1_OR_GOTO_OUT(rv, -ENODEV);


		switch (cfg.chip_type)
		{
			case CHIP_ISIS:
			case CHIP_ISISC:
			#if defined (ISISC) || defined (ISIS)
				if (ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->ess_switch_flag == A_TRUE) {
					SSDK_INFO("Initializing ISISC!!\n");
					rv = ssdk_switch_register(dev_id);
					SW_CNTU_ON_ERROR_AND_COND1_OR_GOTO_OUT(rv, -ENODEV);
					rv = qca_ar8327_hw_init(qca_phy_priv_global[dev_id]);
					SSDK_INFO("Initializing ISISC Done!!\n");
				}
			#endif
				break;
			case CHIP_HPPE:
			#if defined(HPPE)
				SSDK_INFO("Initializing HPPE!!\n");
				qca_hppe_hw_init(&cfg, dev_id);
				rv = ssdk_switch_register(dev_id);
				SW_CNTU_ON_ERROR_AND_COND1_OR_GOTO_OUT(rv, -ENODEV);
				SSDK_INFO("Initializing HPPE Done!!\n");
			#endif
				break;

			case CHIP_DESS:
			#if defined(DESS)
				SSDK_INFO("Initializing DESS!!\n");
				/*Do Malibu self test to fix packet drop issue firstly*/
				if (ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->mac_mode == PORT_WRAPPER_PSGMII) {
					ssdk_psgmii_self_test(dev_id, A_FALSE, 100, &psgmii_result);
					clear_self_test_config(dev_id);
				}

				qca_dess_hw_init(&cfg, dev_id);
				qca_dess_rfs_init();

				/* Setup Cpu port for Dakota platform. */
				switch_cpuport_setup(dev_id);
				rv = ssdk_switch_register(dev_id);
				SW_CNTU_ON_ERROR_AND_COND1_OR_GOTO_OUT(rv, -ENODEV);
				SSDK_INFO("Initializing DESS Done!!\n");
			#endif
				break;

			case CHIP_SHIVA:
			case CHIP_ATHENA:
			case CHIP_GARUDA:
			case CHIP_HORUS:
			case CHIP_UNSPECIFIED:
				break;
		}

			fal_module_func_init(dev_id, &cfg);
	}

	ssdk_sysfs_init();

	/* register the notifier later should be ok */
	ssdk_dev_notifier.notifier_call = ssdk_dev_event;
	ssdk_dev_notifier.priority = 1;
	register_netdevice_notifier(&ssdk_dev_notifier);

out:
	if (rv == 0)
		SSDK_INFO("qca-ssdk module init succeeded!\n");
	else {
		if (rv == -ENODEV) {
			rv = 0;
			SSDK_INFO("qca-ssdk module init, no device found!\n");
		} else {
			SSDK_INFO("qca-ssdk module init failed! (code: %d)\n", rv);
			ssdk_free_priv();
		}
	}

	return rv;
}

static void __exit
regi_exit(void)
{
	a_uint32_t dev_id;
	sw_error_t rv=ssdk_cleanup();

	if (rv == 0)
		SSDK_INFO("qca-ssdk module exit  done!\n");
	else
		SSDK_ERROR("qca-ssdk module exit failed! (code: %d)\n", rv);

	#ifdef DESS
	qca_dess_rfs_remove();
	#endif

	ssdk_sysfs_exit();
	ssdk_miireg_ioctrl_unregister();
	for (dev_id = 0; dev_id < ssdk_dt_global.num_devices; dev_id++) {
		ssdk_plat_exit(dev_id);
		ssdk_driver_unregister(dev_id);
		if (qca_phy_priv_global[dev_id]->qca_ssdk_sw_dev_registered == A_TRUE)
			ssdk_switch_unregister(dev_id);
	}

	unregister_netdevice_notifier(&ssdk_dev_notifier);

	ssdk_free_priv();
}

module_init(regi_init);
module_exit(regi_exit);

MODULE_DESCRIPTION("QCA SSDK Driver");
MODULE_LICENSE("Dual BSD/GPL");

