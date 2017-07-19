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

#ifndef _QCA803X_PHY_H_
#define _QCA803X_PHY_H_

#ifdef __cplusplus
extern "C"
{
#endif				/* __cplusplus */

#define QCA803X_COMMON_CTRL  0x1040
#define QCA803X_10M_LOOPBACK  0x4100
#define QCA803X_100M_LOOPBACK  0x6100
#define QCA803X_1000M_LOOPBACK  0x4140

  /* PHY Registers */
#define QCA803X_PHY_CONTROL                      0
#define QCA803X_PHY_STATUS                       1
#define QCA803X_PHY_SPEC_STATUS                  17

#define QCA803X_PHY_ID1                          2
#define QCA803X_PHY_ID2                          3
#define QCA803X_AUTONEG_ADVERT                   4
#define QCA803X_1000BASET_CONTROL                9
#define QCA803X_1000BASET_STATUS                 10
#define QCA803X_MMD_CTRL_REG                     13
#define QCA803X_MMD_DATA_REG                     14
#define QCA803X_PHY_INTR_MASK                    18
#define QCA803X_PHY_INTR_STATUS                  19
#define QCA803X_PHY_CDT_CONTROL                  22
#define QCA803X_PHY_CDT_STATUS                   28
#define QCA803X_DEBUG_PORT_ADDRESS               29
#define QCA803X_DEBUG_PORT_DATA                  30

#define QCA803X_DEBUG_PHY_HIBERNATION_CTRL  0xb
#define QCA803X_DEBUG_PHY_POWER_SAVING_CTRL  0x29
#define QCA803X_PHY_MMD7_ADDR_8023AZ_EEE_CTRL       0x3c
#define QCA803X_PHY_MMD3_ADDR_REMOTE_LOOPBACK_CTRL       0x805a
#define QCA803X_PHY_MMD3_WOL_MAGIC_MAC_CTRL1   0x804a
#define QCA803X_PHY_MMD3_WOL_MAGIC_MAC_CTRL2   0x804b
#define QCA803X_PHY_MMD3_WOL_MAGIC_MAC_CTRL3   0x804c
#define QCA803X_PHY_MMD3_WOL_CTRL  0x8012
#define QCA803X_PHY_MMD3_ADDR_8023AZ_TIMER_CTRL       0x804e
#define QCA803X_PHY_MMD3_ADDR_8023AZ_CLD_CTRL       0x8007

  /* PHY Registers Field */
#define QCA803X_STATUS_LINK_PASS                 0x0400

  /* Control Register fields  offset:0 */
  /* bits 6,13: 10=1000, 01=100, 00=10 */
#define QCA803X_CTRL_SPEED_MSB                   0x0040

  /* Collision test enable */
#define QCA803X_CTRL_COLL_TEST_ENABLE            0x0080

  /* FDX =1, half duplex =0 */
#define QCA803X_CTRL_FULL_DUPLEX                 0x0100

  /* Restart auto negotiation */
#define QCA803X_CTRL_RESTART_AUTONEGOTIATION     0x0200

  /* Power down */
#define QCA803X_CTRL_POWER_DOWN                  0x0800

  /* Auto Neg Enable */
#define QCA803X_CTRL_AUTONEGOTIATION_ENABLE      0x1000

  /* Local Loopback Enable */
#define QCA803X_LOCAL_LOOPBACK_ENABLE      0x4000

  /* bits 6,13: 10=1000, 01=100, 00=10 */
#define QCA803X_CTRL_SPEED_LSB                   0x2000

  /* 0 = normal, 1 = loopback */
#define QCA803X_CTRL_LOOPBACK                    0x4000
#define QCA803X_CTRL_SOFTWARE_RESET              0x8000

#define QCA803X_CTRL_SPEED_MASK                  0x2040
#define QCA803X_CTRL_SPEED_1000                  0x0040
#define QCA803X_CTRL_SPEED_100                   0x2000
#define QCA803X_CTRL_SPEED_10                    0x0000

#define QCA803X_RESET_DONE(phy_control)                   \
    (((phy_control) & (QCA803X_CTRL_SOFTWARE_RESET)) == 0)

  /* Auto-Negotiation Advertisement register. offset:4 */
#define QCA803X_ADVERTISE_SELECTOR_FIELD         0x0001

  /* 10T   Half Duplex Capable */
#define QCA803X_ADVERTISE_10HALF                 0x0020

  /* 10T   Full Duplex Capable */
#define QCA803X_ADVERTISE_10FULL                 0x0040

  /* 100TX Half Duplex Capable */
#define QCA803X_ADVERTISE_100HALF                0x0080

  /* 100TX Full Duplex Capable */
#define QCA803X_ADVERTISE_100FULL                0x0100

  /* 100T4 Capable */
#define QCA803X_ADVERTISE_100T4                  0x0200

  /* Pause operation desired */
#define QCA803X_ADVERTISE_PAUSE                  0x0400

  /* Asymmetric Pause Direction bit */
#define QCA803X_ADVERTISE_ASYM_PAUSE             0x0800

  /* Remote Fault detected */
#define QCA803X_ADVERTISE_REMOTE_FAULT           0x2000

  /* 100TX Half Duplex Capable */
#define QCA803X_ADVERTISE_1000HALF                0x0100

  /* 100TX Full Duplex Capable */
#define QCA803X_ADVERTISE_1000FULL                0x0200

#define QCA803X_ADVERTISE_ALL \
    (QCA803X_ADVERTISE_10HALF | QCA803X_ADVERTISE_10FULL | \
     QCA803X_ADVERTISE_100HALF | QCA803X_ADVERTISE_100FULL | \
     QCA803X_ADVERTISE_1000FULL)

#define QCA803X_ADVERTISE_MEGA_ALL \
    (QCA803X_ADVERTISE_10HALF | QCA803X_ADVERTISE_10FULL | \
     QCA803X_ADVERTISE_100HALF | QCA803X_ADVERTISE_100FULL)

#define QCA803X_BX_ADVERTISE_1000FULL                0x0020
#define QCA803X_BX_ADVERTISE_1000HALF                0x0040
#define QCA803X_BX_ADVERTISE_PAUSE                      0x0080
#define QCA803X_BX_ADVERTISE_ASYM_PAUSE           0x0100

#define QCA803X_BX_ADVERTISE_ALL \
    (QCA803X_BX_ADVERTISE_ASYM_PAUSE | QCA803X_BX_ADVERTISE_PAUSE | \
     QCA803X_BX_ADVERTISE_1000HALF | QCA803X_BX_ADVERTISE_1000FULL)

  /* 1=Duplex 0=Half Duplex */
#define QCA803X_STATUS_FULL_DUPLEX               0x2000

  /* Speed, bits 14:15 */
#define QCA803X_STATUS_SPEED                    0xC000
#define QCA803X_STATUS_SPEED_MASK               0xC000

  /* 00=10Mbs */
#define QCA803X_STATUS_SPEED_10MBS              0x0000

  /* 01=100Mbs */
#define QCA803X_STATUS_SPEED_100MBS             0x4000

  /* 10=1000Mbs */
#define QCA803X_STATUS_SPEED_1000MBS            0x8000

  /*QCA803X interrupt flag */
#define QCA803X_INTR_SPEED_CHANGE              0x4000
#define QCA803X_INTR_DUPLEX_CHANGE             0x2000
#define QCA803X_INTR_STATUS_UP_CHANGE          0x0400
#define QCA803X_INTR_STATUS_DOWN_CHANGE        0x0800
#define QCA803X_INTR_BX_FX_STATUS_DOWN_CHANGE        0x0100
#define QCA803X_INTR_BX_FX_STATUS_UP_CHANGE        0x0080
#define QCA803X_INTR_MEDIA_STATUS_CHANGE             0x1000

sw_error_t
qca803x_phy_set_duplex (a_uint32_t dev_id, a_uint32_t phy_id,
		   fal_port_duplex_t duplex);

sw_error_t
qca803x_phy_get_duplex (a_uint32_t dev_id, a_uint32_t phy_id,
		   fal_port_duplex_t * duplex);

sw_error_t
qca803x_phy_set_speed (a_uint32_t dev_id, a_uint32_t phy_id,
		  fal_port_speed_t speed);

sw_error_t
qca803x_phy_get_speed (a_uint32_t dev_id, a_uint32_t phy_id,
		  fal_port_speed_t * speed);

sw_error_t
qca803x_phy_restart_autoneg (a_uint32_t dev_id, a_uint32_t phy_id);

sw_error_t
qca803x_phy_enable_autoneg (a_uint32_t dev_id, a_uint32_t phy_id);

a_bool_t
qca803x_phy_get_link_status (a_uint32_t dev_id, a_uint32_t phy_id);

sw_error_t
qca803x_phy_set_autoneg_adv (a_uint32_t dev_id, a_uint32_t phy_id,
			a_uint32_t autoneg);

sw_error_t
qca803x_phy_get_autoneg_adv (a_uint32_t dev_id, a_uint32_t phy_id,
			a_uint32_t * autoneg);

a_bool_t qca803x_phy_autoneg_status (a_uint32_t dev_id, a_uint32_t phy_id);

sw_error_t
qca803x_phy_intr_mask_set (a_uint32_t dev_id, a_uint32_t phy_id,
		      a_uint32_t intr_mask_flag);

sw_error_t
qca803x_phy_intr_mask_get (a_uint32_t dev_id, a_uint32_t phy_id,
		      a_uint32_t * intr_mask_flag);

sw_error_t
qca803x_phy_intr_status_get (a_uint32_t dev_id, a_uint32_t phy_id,
			a_uint32_t * intr_status_flag);

sw_error_t
qca803x_phy_get_phy_id(a_uint32_t dev_id, a_uint32_t phy_id,
		a_uint16_t * org_id, a_uint16_t * rev_id);

int qca803x_phy_init(a_uint32_t dev_id, a_uint32_t port_bmp);

#ifdef __cplusplus
}
#endif				/* __cplusplus */
#endif				/* _qca803x_PHY_H_ */
