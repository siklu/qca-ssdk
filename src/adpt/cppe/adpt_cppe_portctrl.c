/*
 * Copyright (c) 2018-2019, The Linux Foundation. All rights reserved.
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
 * @defgroup
 * @{
 */
#include "sw.h"
#include "hppe_global_reg.h"
#include "hppe_global.h"
#include "hppe_portctrl_reg.h"
#include "hppe_portctrl.h"
#include "cppe_portctrl_reg.h"
#include "cppe_portctrl.h"
#include "hsl.h"
#include "hsl_dev.h"
#include "hsl_phy.h"
#include "hsl_port_prop.h"
#include "adpt.h"
#include "adpt_hppe.h"
#include "adpt_cppe_portctrl.h"

sw_error_t
_adpt_cppe_port_mux_mac_set(a_uint32_t dev_id, fal_port_t port_id,
	a_uint32_t port_type)
{
	sw_error_t rv = SW_OK;
	a_uint32_t mode0, mode1;
	union cppe_port_mux_ctrl_u cppe_port_mux_ctrl;

	ADPT_DEV_ID_CHECK(dev_id);
	memset(&cppe_port_mux_ctrl, 0, sizeof(cppe_port_mux_ctrl));

	rv = cppe_port_mux_ctrl_get(dev_id, &cppe_port_mux_ctrl);
	SW_RTN_ON_ERROR (rv);

	mode0 = ssdk_dt_global_get_mac_mode(dev_id, SSDK_UNIPHY_INSTANCE0);
	mode1 = ssdk_dt_global_get_mac_mode(dev_id, SSDK_UNIPHY_INSTANCE1);

	switch (port_id) {
		case SSDK_PHYSICAL_PORT3:
		case SSDK_PHYSICAL_PORT4:
			if (mode0 == PORT_WRAPPER_PSGMII) {
				if (hsl_port_phyid_get(dev_id,
					SSDK_PHYSICAL_PORT3) == MALIBU2PORT_PHY) {
					cppe_port_mux_ctrl.bf.port3_pcs_sel =
						CPPE_PORT3_PCS_SEL_PCS0_CHANNEL4;
					cppe_port_mux_ctrl.bf.port4_pcs_sel =
						CPPE_PORT4_PCS_SEL_PCS0_CHANNEL3;
				} else {
					cppe_port_mux_ctrl.bf.port3_pcs_sel =
						CPPE_PORT3_PCS_SEL_PCS0_CHANNEL2;
					cppe_port_mux_ctrl.bf.port4_pcs_sel =
						CPPE_PORT4_PCS_SEL_PCS0_CHANNEL3;
				}
			} else if (mode0 == PORT_WRAPPER_QSGMII) {
				cppe_port_mux_ctrl.bf.port3_pcs_sel =
					CPPE_PORT3_PCS_SEL_PCS0_CHANNEL2;
				cppe_port_mux_ctrl.bf.port4_pcs_sel =
					CPPE_PORT4_PCS_SEL_PCS0_CHANNEL3;
			} else if (mode0 == PORT_WRAPPER_SGMII_PLUS) {
				cppe_port_mux_ctrl.bf.port3_pcs_sel =
					CPPE_PORT3_PCS_SEL_PCS0_CHANNEL2;
				cppe_port_mux_ctrl.bf.port4_pcs_sel =
					CPPE_PORT4_PCS_SEL_PCS0_SGMIIPLUS;
			} else if (mode0 ==PORT_WRAPPER_SGMII_CHANNEL0) {
				if (hsl_port_phyid_get(dev_id,
					SSDK_PHYSICAL_PORT4) == QCA8081_PHY_V1_1) {
					cppe_port_mux_ctrl.bf.port3_pcs_sel =
						CPPE_PORT3_PCS_SEL_PCS0_CHANNEL2;
					cppe_port_mux_ctrl.bf.port4_pcs_sel =
						CPPE_PORT4_PCS_SEL_PCS0_SGMIIPLUS;
				} else {
					cppe_port_mux_ctrl.bf.port3_pcs_sel =
						CPPE_PORT3_PCS_SEL_PCS0_CHANNEL2;
					cppe_port_mux_ctrl.bf.port4_pcs_sel =
						CPPE_PORT4_PCS_SEL_PCS0_CHANNEL3;
				}
			} else if ((mode0 == PORT_WRAPPER_SGMII_CHANNEL4) ||
				(mode0 == PORT_WRAPPER_SGMII0_RGMII4)) {
				cppe_port_mux_ctrl.bf.port3_pcs_sel =
					CPPE_PORT3_PCS_SEL_PCS0_CHANNEL2;
				cppe_port_mux_ctrl.bf.port4_pcs_sel =
					CPPE_PORT4_PCS_SEL_PCS0_CHANNEL3;
				cppe_port_mux_ctrl.bf.port5_pcs_sel =
					CPPE_PORT5_PCS_SEL_PCS0_CHANNEL4;
				cppe_port_mux_ctrl.bf.port5_gmac_sel =
					CPPE_PORT5_GMAC_SEL_GMAC;
			} else if ((mode0 == PORT_WRAPPER_SGMII_CHANNEL1) ||
				(mode0 == PORT_WRAPPER_SGMII1_RGMII4)) {
				cppe_port_mux_ctrl.bf.port3_pcs_sel =
					CPPE_PORT3_PCS_SEL_PCS0_CHANNEL2;
				cppe_port_mux_ctrl.bf.port4_pcs_sel =
					CPPE_PORT4_PCS_SEL_PCS0_CHANNEL3;
			}
			break;
		case SSDK_PHYSICAL_PORT5:
			if (mode0 == PORT_WRAPPER_PSGMII) {
				if (hsl_port_phyid_get(dev_id,
					SSDK_PHYSICAL_PORT3) != MALIBU2PORT_PHY) {
					cppe_port_mux_ctrl.bf.port5_pcs_sel =
						CPPE_PORT5_PCS_SEL_PCS0_CHANNEL4;
					cppe_port_mux_ctrl.bf.port5_gmac_sel =
						CPPE_PORT5_GMAC_SEL_GMAC;
				}
			}
			if ((mode1 == PORT_WRAPPER_SGMII_PLUS) ||
				(mode1 == PORT_WRAPPER_SGMII0_RGMII4) ||
				(mode1 == PORT_WRAPPER_SGMII_CHANNEL0)) {
				cppe_port_mux_ctrl.bf.port5_pcs_sel =
					CPPE_PORT5_PCS_SEL_PCS1_CHANNEL0;
				cppe_port_mux_ctrl.bf.port5_gmac_sel =
					CPPE_PORT5_GMAC_SEL_GMAC;
			} else if (mode1 == PORT_WRAPPER_USXGMII) {
				cppe_port_mux_ctrl.bf.port5_pcs_sel =
					CPPE_PORT5_PCS_SEL_PCS1_CHANNEL0;
				cppe_port_mux_ctrl.bf.port5_gmac_sel =
					CPPE_PORT5_GMAC_SEL_XGMAC;
			}
			break;
		default:
			break;
	}

	rv = cppe_port_mux_ctrl_set(dev_id, &cppe_port_mux_ctrl);

	return rv;
}

sw_error_t
adpt_cppe_port_mru_set(a_uint32_t dev_id, fal_port_t port_id,
		fal_mru_ctrl_t *ctrl)
{
	sw_error_t rv = SW_OK;
	union cppe_mru_mtu_ctrl_tbl_u mru_mtu_ctrl_tbl;

	memset(&mru_mtu_ctrl_tbl, 0, sizeof(mru_mtu_ctrl_tbl));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(ctrl);

	rv = cppe_mru_mtu_ctrl_tbl_get(dev_id, port_id, &mru_mtu_ctrl_tbl);
	SW_RTN_ON_ERROR (rv);

	mru_mtu_ctrl_tbl.bf.mru = ctrl->mru_size;
	mru_mtu_ctrl_tbl.bf.mru_cmd = (a_uint32_t)ctrl->action;
	rv = cppe_mru_mtu_ctrl_tbl_set(dev_id, port_id, &mru_mtu_ctrl_tbl);

	return rv;
}

sw_error_t
adpt_cppe_port_mru_get(a_uint32_t dev_id, fal_port_t port_id,
		fal_mru_ctrl_t *ctrl)
{
	sw_error_t rv = SW_OK;
	union cppe_mru_mtu_ctrl_tbl_u mru_mtu_ctrl_tbl;

	memset(&mru_mtu_ctrl_tbl, 0, sizeof(mru_mtu_ctrl_tbl));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(ctrl);

	rv = cppe_mru_mtu_ctrl_tbl_get(dev_id, port_id, &mru_mtu_ctrl_tbl);
	SW_RTN_ON_ERROR (rv);

	ctrl->mru_size = mru_mtu_ctrl_tbl.bf.mru;
	ctrl->action = (fal_fwd_cmd_t)mru_mtu_ctrl_tbl.bf.mru_cmd;

	return SW_OK;
}

sw_error_t
adpt_cppe_port_mtu_set(a_uint32_t dev_id, fal_port_t port_id,
		fal_mtu_ctrl_t *ctrl)
{
	sw_error_t rv = SW_OK;
	union cppe_mru_mtu_ctrl_tbl_u mru_mtu_ctrl_tbl;

	memset(&mru_mtu_ctrl_tbl, 0, sizeof(mru_mtu_ctrl_tbl));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(ctrl);

	rv = cppe_mru_mtu_ctrl_tbl_get(dev_id, port_id, &mru_mtu_ctrl_tbl);
	SW_RTN_ON_ERROR (rv);

	mru_mtu_ctrl_tbl.bf.mtu = ctrl->mtu_size;
	mru_mtu_ctrl_tbl.bf.mtu_cmd = (a_uint32_t)ctrl->action;
	rv = cppe_mru_mtu_ctrl_tbl_set(dev_id, port_id, &mru_mtu_ctrl_tbl);
	SW_RTN_ON_ERROR (rv);

	if ((port_id >= SSDK_PHYSICAL_PORT0) && (port_id <= SSDK_PHYSICAL_PORT7))
	{
		rv = hppe_mc_mtu_ctrl_tbl_mtu_set(dev_id, port_id, ctrl->mtu_size);
		SW_RTN_ON_ERROR (rv);
		rv = hppe_mc_mtu_ctrl_tbl_mtu_cmd_set(dev_id, port_id, (a_uint32_t)ctrl->action);
		SW_RTN_ON_ERROR (rv);
	}

	return rv;
}

sw_error_t
adpt_cppe_port_mtu_get(a_uint32_t dev_id, fal_port_t port_id,
		fal_mtu_ctrl_t *ctrl)
{
	sw_error_t rv = SW_OK;
	union cppe_mru_mtu_ctrl_tbl_u mru_mtu_ctrl_tbl;

	memset(&mru_mtu_ctrl_tbl, 0, sizeof(mru_mtu_ctrl_tbl));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(ctrl);

	rv = cppe_mru_mtu_ctrl_tbl_get(dev_id, port_id, &mru_mtu_ctrl_tbl);
	SW_RTN_ON_ERROR (rv);

	ctrl->mtu_size = mru_mtu_ctrl_tbl.bf.mtu;
	ctrl->action = (fal_fwd_cmd_t)mru_mtu_ctrl_tbl.bf.mtu_cmd;

	return SW_OK;
}

sw_error_t
adpt_cppe_port_to_channel_convert(a_uint32_t dev_id, a_uint32_t port_id,
	a_uint32_t *channel_id)
{
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(channel_id);

	*channel_id = port_id;

	if (port_id == SSDK_PHYSICAL_PORT3) {
		if (hsl_port_phyid_get(dev_id,
				port_id) == MALIBU2PORT_PHY) {
			*channel_id = SSDK_PHYSICAL_PORT5;
		}
	}
	return SW_OK;
}

/**
 * @}
 */
