/*
 * Copyright (c) 2016-2017, The Linux Foundation. All rights reserved.
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


/**
 * @defgroup hppe_init _HPPE_INIT_H_
 * @{
 */
#ifndef _HPPE_INIT_H_
#define _HPPE_INIT_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "init/ssdk_init.h"

#define MII_PHYADDR_C45 (1<<30)
#define HPPE_GCC_UNIPHY_REG_INC 0x100
#define HPPE_TO_XGMAC_PORT_ID(port_id)  (port_id - 5)
#define HPPE_TO_GMAC_PORT_ID(port_id) (port_id -1)
#define HPPE_MAX_FRAME_SIZE 0x3FFF
#define HPPE_FCS_LEN  4

#define HPPE_MUX_PORT1  5
#define HPPE_MUX_PORT2  6
#define HPPE_PORT_GMAC_TYPE	1
#define HPPE_PORT_XGMAC_TYPE	2

#define HPPE_GCC_UNIPHY_PSGMII_SOFT_RESET 0x3ff2
#define HPPE_GCC_UNIPHY_USXGMII_SOFT_RESET 0x32
#define PORT_LINK_UP 1
#define PORT_LINK_DOWN 0
#define HPPE_MAX_PORT_NUM 6

#define HPPE_UNIPHY_INSTANCE0	0
#define HPPE_UNIPHY_INSTANCE1	1
#define HPPE_UNIPHY_INSTANCE2	2
#define HPPE_UNIPHY_BASE1	0x10000
#define HPPE_UNIPHY_BASE2	0x20000
#define HPPE_UNIPHY_MAX_DIRECT_ACCESS_REG	0x7fff
#define HPPE_UNIPHY_INDIRECT_REG_ADDR  0x83fc
#define HPPE_UNIPHY_INDIRECT_HIGH_ADDR  0x1fff00
#define HPPE_UNIPHY_INDIRECT_LOW_ADDR  0xff
#define HPPE_UNIPHY_INDIRECT_DATA  0x20
#define UNIPHY_CALIBRATION_DONE 0x80
#define UNIPHY_10GR_LINKUP 0x1000

#define AQ_PHY_AUTO_STATUS_REG 0x70001
#define AQ_PHY_LINK_STATUS_REG 0x7c800
#define AQ_PHY_LINK_PARTNER_REG 0x70013

sw_error_t hppe_init(a_uint32_t dev_id, ssdk_init_cfg *cfg);
a_bool_t hppe_mac_port_valid_check(fal_port_t port_id);
a_bool_t hppe_xgmac_port_check(fal_port_t port_id);
sw_error_t hppe_cleanup(a_uint32_t dev_id);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _HPPE_INIT_H_ */
/**
 * @}
 */
