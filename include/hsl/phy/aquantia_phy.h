/*
 * Copyright (c) 2017, The Linux Foundation. All rights reserved.
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

#ifndef _AQUANTIA_PHY_H_
#define _AQUANTIA_PHY_H_

#ifdef __cplusplus
extern "C"
{
#endif				/* __cplusplus */
#define PHY_ID_AQ1202	0x03a1b445
#define PHY_ID_AQ2104	0x03a1b460
#define PHY_ID_AQR105	0x03a1b4a2
#define PHY_ID_AQR405	0x03a1b4b0
#define PHY_ID_AQR107	0x03a1b4e1

#define AQUANTIA_MII_ADDR_C45  (1<<30)
#define AQUANTIA_REG_ADDRESS(dev_ad, reg_num) (AQUANTIA_MII_ADDR_C45 |\
			((dev_ad & 0x1f) << 16) | (reg_num & 0xFFFF))
#define AQUANTIA_MMD_AUTONEG 0x7
#define AQUANTIA_MMD_PHY_XS_REGISTERS 4
#define AQUANTIA_MMD_GLOBAL_REGISTERS 0x1E
#define AQUANTIA_MMD_GBE_STANDARD_REGISTERS 0x1D

  /* PHY Registers */
#define AQUANTIA_GLOBAL_STANDARD_CONTROL1        0
#define AQUANTIA_REG_AUTONEG_VENDOR_STATUS  0xC800
#define AQUANTIA_AUTONEG_STANDARD_STATUS1  0x1
#define AQUANTIA_AUTONEG_STANDARD_CONTROL1  0
#define AQUANTIA_AUTONEG_TRANSMIT_VENDOR_INTR_MASK 0xD401
#define AQUANTIA_GLOBAL_INTR_STANDARD_MASK 0xff00
#define AQUANTIA_GLOBAL_INTR_VENDOR_MASK 0xff01
#define AQUANTIA_PHY_XS_USX_TRANSMIT 0xc441
#define AQUANTIA_PHY_INTR_STATUS                  19
#define AQUANTIA_RESERVED_VENDOR_PROVISIONING1  0xC410
#define AQUANTIA_RESERVED_VENDOR_STATUS1  0xC810
#define AQUANTIA_GLOBAL_RESERVED_PROVISIONING 0xC47a
#define AQUANTIA_GLOBAL_RESERVED_PROVISIONING6 0xC475
#define AQUANTIA_PHY_XS_TRANAMIT_RESERVED_VENDOR_PROVISION5 0xC444
#define AQUANTIA_CHIP_WIDE_VENDORT_INTERRUPT_FLAGS 0xFC01
#define AQUANTIA_AUTONEG_ADVERTISEMENT_REGISTER 0x10
#define AQUANTIA_AUTONEG_VENDOR_PROVISION1 0xC400
#define AQUANTIA_AUTONEG_10GBASE_T_CONTROL_REGISTER 0x20
#define AQUANTIA_AUTONEG_LINK_PARTNER_ABILITY 0x13
#define AQUANTIA_AUTONEG_LINK_PARTNER_5G_ABILITY 0xE820
#define AQUANTIA_AUTONEG_LINK_PARTNER_10G_ABILITY 0x21

#define AQUANTIA_GLOBAL_CDT_CONTROL  0xC470
#define AQUANTIA_NORMAL_CABLE_DIAGNOSTICS 0x10

#define AQUANTIA_CABLE_DIAGNOSTIC_STATUS1 0xC800
#define AQUANTIA_CABLE_DIAGNOSTIC_STATUS_PAIRA 0x7000/*0XC800, BITC:E*/
#define AQUANTIA_CABLE_DIAGNOSTIC_STATUS_PAIRB 0x0700/*0XC800, BITA:8*/
#define AQUANTIA_CABLE_DIAGNOSTIC_STATUS_PAIRC 0x0070/*0XC800, BIT6:4*/
#define AQUANTIA_CABLE_DIAGNOSTIC_STATUS_PAIRD 0x0007/*0XC800, BIT2:0*/


#define AQUANTIA_CABLE_DIAGNOSTIC_STATUS2 0xC801
#define AQUANTIA_CABLE_DIAGNOSTIC_STATUS4 0xC803
#define AQUANTIA_CABLE_DIAGNOSTIC_STATUS6 0xC805
#define AQUANTIA_CABLE_DIAGNOSTIC_STATUS8 0xC807
#define AQUANTIA_ACT_LED_STATUS 0xc430
#define AQUANTIA_LINK_LED_STATUS 0xc431
#define AQUANTIA_ACT_LED_VALUE 0xc0ef
#define AQUANTIA_LINK_LED_VALUE 0xc0e0


#define AQUANTIA_PHY_ID1  0x2
#define AQUANTIA_PHY_ID2  0x3
#define AQUANTIA_MAGIC_FRAME_MAC0  0xC339
#define AQUANTIA_MAGIC_FRAME_MAC1  0xC33a
#define AQUANTIA_MAGIC_FRAME_MAC2  0xC33b
#define AQUANTIA_MAGIC_ENGINE_REGISTER1 0xC355
#define AQUANTIA_MAGIC_ENGINE_REGISTER2 0xC356

#define AQUANTIA_GLOBAL_SYS_CONFIG_FOR_100M 0x31B
#define AQUANTIA_GLOBAL_SYS_CONFIG_FOR_1000M 0x31C
#define AQUANTIA_GLOBAL_SYS_CONFIG_FOR_2500M 0x31D
#define AQUANTIA_GLOBAL_SYS_CONFIG_FOR_5000M 0x31E
#define AQUANTIA_GLOBAL_SYS_CONFIG_FOR_10000M 0x31F


  /* PHY Registers Field */
#define AQUANTIA_SERDES_MODE_XFI  0
#define AQUANTIA_SERDES_MODE_SGMII  0x3
#define AQUANTIA_SERDES_MODE_OCSGMII 0X4

#define AQUANTIA_MAGIC_PACKETS_ENABLE 0x0001
#define AQUANTIA_PHY_MDIX_CONTRO_BIT  3
#define AQUANTIA_PHY_MDIX_AUTO  0
#define AQUANTIA_PHY_MDI  1
#define AQUANTIA_PHY_MDIX  2
#define  AQUANTIA_PHY_MDIX_STATUS     0x0100
#define AQUANTIA_PHY_WOL_ENABLE 0x0040
#define AQUANTIA_PHY_REMOTE_LOOPBACK 0x1800
#define AQUANTIA_COMMON_CTRL  0x1040
#define AQUANTIA_INTERNAL_LOOPBACK 0x4800
#define AQUANTIA_100M_LOOPBACK  0x0001
#define AQUANTIA_1000M_LOOPBACK  0x0002
#define AQUANTIA_10000M_LOOPBACK  0x0003
#define AQUANTIA_2500M_LOOPBACK  0x0004
#define AQUANTIA_5000M_LOOPBACK  0x0005
#define AQUANTIA_POWER_DOWN  0x0800
#define AQUANTIA_ALL_SPEED_LOOPBACK  (AQUANTIA_100M_LOOPBACK |\
	AQUANTIA_1000M_LOOPBACK | AQUANTIA_1000M_LOOPBACK |AQUANTIA_2500M_LOOPBACK |\
	AQUANTIA_5000M_LOOPBACK | AQUANTIA_10000M_LOOPBACK)

#define AQUANTIA_POWER_SAVE  0x0004
#define AQUANTIA_STATUS_LINK 0x0004
#define AQUANTIA_PHY_USX_AUTONEG_ENABLE	0x8
  /* FDX =1, half duplex =0 */
#define AQUANTIA_CTRL_FULL_DUPLEX                 0x0100

  /* Restart auto negotiation */
#define AQUANTIA_CTRL_RESTART_AUTONEGOTIATION     0x0200

  /* Power down */
#define AQUANTIA_CTRL_POWER_DOWN                  0x0800

  /* Auto Neg Enable */
#define AQUANTIA_CTRL_AUTONEGOTIATION_ENABLE      0x1000

  /* Local Loopback Enable */
#define AQUANTIA_LOCAL_LOOPBACK_ENABLE      0x4000

  /* 0 = normal, 1 = loopback */
#define AQUANTIA_CTRL_SOFTWARE_RESET              0x8000

#define AQUANTIA_RESET_DONE(phy_control)                   \
    (((phy_control) & (AQUANTIA_CTRL_SOFTWARE_RESET)) == 0)

  /* Auto Neg Complete */
#define AQUANTIA_STATUS_AUTO_NEG_DONE             0x0020

#define AQUANTIA_AUTONEG_DONE(ip_phy_status) \
    (((ip_phy_status) & (AQUANTIA_STATUS_AUTO_NEG_DONE)) ==  \
        (AQUANTIA_STATUS_AUTO_NEG_DONE))

/*AQUANTIA interrupt flag */
#define AQUANTIA_INTR_DUPLEX_CHANGE             0x2000
#define AQUANTIA_INTR_LINK_STATUS_CHANGE          0x0001
#define AQUANTIA_ALL_VENDOR_ALARMS_INTR_MASK  0x0001
#define AQUANTIA_AUTO_AND_ALARMS_INTR_MASK 0x1001

  /* 10T   Half Duplex Capable */
#define AQUANTIA_ADVERTISE_10HALF                 0x0020

  /* 10T   Full Duplex Capable */
#define AQUANTIA_ADVERTISE_10FULL                 0x0040

  /* 100TX Half Duplex Capable */
#define AQUANTIA_ADVERTISE_100HALF                0x0080

  /* 100TX Full Duplex Capable */
#define AQUANTIA_ADVERTISE_100FULL                0x0100

  /* Pause operation desired */
#define AQUANTIA_ADVERTISE_PAUSE                  0x0400

  /* Asymmetric Pause Direction bit */
#define AQUANTIA_ADVERTISE_ASYM_PAUSE             0x0800

  /* Remote Fault detected */
#define AQUANTIA_ADVERTISE_REMOTE_FAULT           0x2000

  /* Next Page ability supported */
#define AQUANTIA_ADVERTISE_NEXT_PAGE              0x8000

  /* 1000TX Half Duplex Capable */
#define AQUANTIA_ADVERTISE_1000HALF                0x4000

  /* 1000TX Full Duplex Capable */
#define AQUANTIA_ADVERTISE_1000FULL                0x8000

  /* 2500TX Full Duplex Capable */
#define AQUANTIA_ADVERTISE_2500FULL                0x0400
#define AQUANTIA_ADVERTISE_8023BZ_2500FULL                0x80

  /* 10000TX Full Duplex Capable */
#define AQUANTIA_ADVERTISE_10000FULL                0x1000

  /* 5000TX Full Duplex Capable */
#define AQUANTIA_ADVERTISE_5000FULL                0x0800
#define AQUANTIA_ADVERTISE_8023BZ_5000FULL                0x100

#define AQUANTIA_ADVERTISE_ALL \
    (AQUANTIA_ADVERTISE_10HALF | AQUANTIA_ADVERTISE_10FULL | \
     AQUANTIA_ADVERTISE_100HALF | AQUANTIA_ADVERTISE_100FULL | \
     AQUANTIA_ADVERTISE_1000HALF |AQUANTIA_ADVERTISE_1000FULL |\
     AQUANTIA_ADVERTISE_10000FULL | AQUANTIA_ADVERTISE_2500FULL |\
     AQUANTIA_ADVERTISE_5000FULL)

#define AQUANTIA_ADVERTISE_MEGA_ALL \
    (AQUANTIA_ADVERTISE_10HALF | AQUANTIA_ADVERTISE_10FULL | \
     AQUANTIA_ADVERTISE_100HALF | AQUANTIA_ADVERTISE_100FULL)

#define AQUANTIA_ADVERTISE_GIGA_ALL \
  (AQUANTIA_ADVERTISE_1000HALF |AQUANTIA_ADVERTISE_1000FULL |\
 AQUANTIA_ADVERTISE_2500FULL |  AQUANTIA_ADVERTISE_5000FULL)
 
  #define AQUANTIA_ADVERTISE_GIGA_PLUS_ALL \
	(AQUANTIA_ADVERTISE_10000FULL | AQUANTIA_ADVERTISE_8023BZ_2500FULL|\
	AQUANTIA_ADVERTISE_8023BZ_5000FULL)


#define AQUANTIA_BX_ADVERTISE_1000FULL                0x0020
#define AQUANTIA_BX_ADVERTISE_1000HALF                0x0040
#define AQUANTIA_BX_ADVERTISE_PAUSE                      0x0080
#define AQUANTIA_BX_ADVERTISE_ASYM_PAUSE           0x0100

#define AQUANTIA_BX_ADVERTISE_ALL \
    (AQUANTIA_BX_ADVERTISE_ASYM_PAUSE | AQUANTIA_BX_ADVERTISE_PAUSE | \
     AQUANTIA_BX_ADVERTISE_1000HALF | AQUANTIA_BX_ADVERTISE_1000FULL)

  /* Link Partner ability offset:5 */
  /* Same as advertise selector  */
#define AQUANTIA_LINK_SLCT                        0x001f

  /* Can do 10mbps half-duplex   */
#define AQUANTIA_LINK_10BASETX_HALF_DUPLEX        0x0020

  /* Can do 10mbps full-duplex   */
#define AQUANTIA_LINK_10BASETX_FULL_DUPLEX        0x0040

  /* Can do 100mbps half-duplex  */
#define AQUANTIA_LINK_100BASETX_HALF_DUPLEX       0x0080
#define AQUANTIA_LINK_100BASETX_FULL_DUPLEX       0x0100
/*Can do 1G*/

#define AQUANTIA_LINK_1000BASETX_FULL_DUPLEX       0x8000
  /*Can do 5G*/
#define AQUANTIA_LINK_5000BASETX_FULL_DUPLEX       0x0800
/*Can do 2.5G*/
#define AQUANTIA_LINK_2500BASETX_FULL_DUPLEX       0x0400
/*Can do 10G*/
#define AQUANTIA_LINK_10000BASETX_FULL_DUPLEX       0x1



  /* 1=Duplex 0=Half Duplex */
#define AQUANTIA_STATUS_FULL_DUPLEX               0x0001

  /* Speed, bits 1 : 3*/
#define AQUANTIA_STATUS_SPEED                   	     0xC000
#define AQUANTIA_STATUS_SPEED_MASK               0x000E
  /* 000=10Mbs */
#define AQUANTIA_STATUS_SPEED_10MBS              0x0000
  /* 001=100Mbs */
#define AQUANTIA_STATUS_SPEED_100MBS           0x0001
  /* 010=1000Mbs */
#define AQUANTIA_STATUS_SPEED_1000MBS         0x0002
  /* 011=10000Mbs */
#define AQUANTIA_STATUS_SPEED_10000MBS      0x0003
  /* 100=2500Mbs */
#define AQUANTIA_STATUS_SPEED_2500MBS         0x0004
  /* 101=5000Mbs */
#define AQUANTIA_STATUS_SPEED_5000MBS         0x0005

#define RUN_CDT 0x8000
#define CABLE_LENGTH_UNIT 0x0400

/** Phy pages */
  typedef enum
  {
    AQUANTIA_PHY_SGBX_PAGES = 0,
				       /**< sgbx pages */
    AQUANTIA_PHY_COPPER_PAGES = 1
				       /**< copper pages */
  } AQUANTIA_PHY_reg_pages_t;

sw_error_t
   aquantia_phy_set_powersave (a_uint32_t dev_id, a_uint32_t phy_id,
			      a_bool_t enable);

sw_error_t
   aquantia_phy_get_powersave (a_uint32_t dev_id, a_uint32_t phy_id,
			      a_bool_t * enable);

sw_error_t
   aquantia_phy_cdt (a_uint32_t dev_id, a_uint32_t phy_id,
		    a_uint32_t mdi_pair,
		    fal_cable_status_t * cable_status,
		    a_uint32_t * cable_len);

sw_error_t
   aquantia_phy_set_duplex (a_uint32_t dev_id, a_uint32_t phy_id,
			   fal_port_duplex_t duplex);

sw_error_t
   aquantia_phy_get_duplex (a_uint32_t dev_id, a_uint32_t phy_id,
			   fal_port_duplex_t * duplex);

sw_error_t
   aquantia_phy_set_speed (a_uint32_t dev_id, a_uint32_t phy_id,
			  fal_port_speed_t speed);

sw_error_t
aquantia_phy_get_speed (a_uint32_t dev_id, a_uint32_t phy_id,
			  fal_port_speed_t * speed);

sw_error_t
   aquantia_phy_restart_autoneg (a_uint32_t dev_id, a_uint32_t phy_id);

sw_error_t
   aquantia_phy_enable_autoneg (a_uint32_t dev_id, a_uint32_t phy_id);

a_bool_t
   aquantia_phy_get_link_status (a_uint32_t dev_id, a_uint32_t phy_id);

sw_error_t
   aquantia_phy_set_autoneg_adv (a_uint32_t dev_id, a_uint32_t phy_id,
				a_uint32_t autoneg);

sw_error_t
   aquantia_phy_get_autoneg_adv (a_uint32_t dev_id, a_uint32_t phy_id,
				a_uint32_t * autoneg);

a_bool_t
   aquantia_phy_autoneg_status (a_uint32_t dev_id, a_uint32_t phy_id);

sw_error_t
   aquantia_phy_intr_mask_set (a_uint32_t dev_id, a_uint32_t phy_id,
			      a_uint32_t intr_mask_flag);

sw_error_t
   aquantia_phy_intr_mask_get (a_uint32_t dev_id, a_uint32_t phy_id,
			      a_uint32_t * intr_mask_flag);

int aquantia_phy_init(a_uint32_t dev_id, a_uint32_t port_bmp);

#ifdef __cplusplus
}
#endif				/* __cplusplus */
#endif				/* _AQUANTIA_PHY_H_ */
