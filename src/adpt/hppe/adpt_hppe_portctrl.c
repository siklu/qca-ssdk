/*
 * Copyright (c) 2016, The Linux Foundation. All rights reserved.
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
#include "hppe_portctrl.h"
#include "hppe_portctrl_reg.h"
#include "adpt.h"

sw_error_t
adpt_hppe_port_local_loopback_get(a_uint32_t dev_id, fal_port_t port_id,
					a_bool_t * enable)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(enable);


}

sw_error_t
adpt_hppe_port_autoneg_restart(a_uint32_t dev_id, fal_port_t port_id)
{

	ADPT_DEV_ID_CHECK(dev_id);


}
sw_error_t
adpt_hppe_port_duplex_set(a_uint32_t dev_id, fal_port_t port_id,
				fal_port_duplex_t duplex)
{
	union mac_enable_u mac_enable;

	memset(&mac_enable, 0, sizeof(mac_enable));
	ADPT_DEV_ID_CHECK(dev_id);

	port_id = port_id - 1;
	hppe_mac_enable_get(dev_id, port_id, &mac_enable);

	if (FAL_HALF_DUPLEX == duplex)
		mac_enable.bf.duplex = 0;
	if (FAL_FULL_DUPLEX == duplex)
		mac_enable.bf.duplex = 1;

	hppe_mac_enable_set(dev_id, port_id, &mac_enable);

	return SW_OK;
}
sw_error_t
adpt_hppe_port_rxmac_status_get(a_uint32_t dev_id, fal_port_t port_id,
				      a_bool_t * enable)
{
	sw_error_t rv = SW_OK;
	union mac_enable_u mac_enable;

	memset(&mac_enable, 0, sizeof(mac_enable));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(enable);

	port_id = port_id - 1;
	rv = hppe_mac_enable_get(dev_id, port_id, &mac_enable);

	if( rv != SW_OK )
		return rv;

	if (mac_enable.bf.rxmac_en)
		*enable = A_TRUE;
	else
		*enable = A_FALSE;

	return SW_OK;
}

sw_error_t
adpt_hppe_port_cdt(a_uint32_t dev_id, fal_port_t port_id,
		a_uint32_t mdi_pair, fal_cable_status_t * cable_status,
		a_uint32_t * cable_len)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(cable_status);
	ADPT_NULL_POINT_CHECK(cable_len);


}
sw_error_t
adpt_hppe_port_txmac_status_set(a_uint32_t dev_id, fal_port_t port_id,
				      a_bool_t enable)
{
	union mac_enable_u mac_enable;

	memset(&mac_enable, 0, sizeof(mac_enable));
	ADPT_DEV_ID_CHECK(dev_id);

	port_id = port_id - 1;
	hppe_mac_enable_get(dev_id, port_id, &mac_enable);

	if (A_TRUE == enable)
		mac_enable.bf.txmac_en = 1;
	if (A_FALSE == enable)
		mac_enable.bf.txmac_en = 0;

	hppe_mac_enable_set(dev_id, port_id, &mac_enable);

	return SW_OK;
}
sw_error_t
adpt_hppe_port_combo_fiber_mode_set(a_uint32_t dev_id,
						  a_uint32_t port_id,
						  fal_port_fiber_mode_t mode)
{

	ADPT_DEV_ID_CHECK(dev_id);


}
sw_error_t
adpt_hppe_port_combo_medium_status_get(a_uint32_t dev_id,
						     a_uint32_t port_id,
						     fal_port_medium_t *
						     medium)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(medium);


}

sw_error_t
adpt_hppe_port_magic_frame_mac_set(a_uint32_t dev_id, fal_port_t port_id,
				   fal_mac_addr_t * mac)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(mac);


}
sw_error_t
adpt_hppe_port_powersave_set(a_uint32_t dev_id, fal_port_t port_id,
			  a_bool_t enable)
{

	ADPT_DEV_ID_CHECK(dev_id);


}
sw_error_t
adpt_hppe_port_hibernate_set(a_uint32_t dev_id, fal_port_t port_id,
			  a_bool_t enable)
{

	ADPT_DEV_ID_CHECK(dev_id);


}
sw_error_t
adpt_hppe_port_max_frame_size_set(a_uint32_t dev_id, fal_port_t port_id,
		a_uint32_t max_frame)
{
	union mac_ctrl2_u mac_ctrl2;

	memset(&mac_ctrl2, 0, sizeof(mac_ctrl2));
	ADPT_DEV_ID_CHECK(dev_id);

	port_id = port_id -1;
	hppe_mac_ctrl2_get(dev_id, port_id, &mac_ctrl2);
	mac_ctrl2.bf.maxfr = max_frame;
	hppe_mac_ctrl2_set(dev_id, port_id, &mac_ctrl2);
	return SW_OK;
}

sw_error_t
adpt_hppe_port_8023az_get(a_uint32_t dev_id, fal_port_t port_id,
				a_bool_t * enable)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(enable);


}

sw_error_t
adpt_hppe_port_rxfc_status_get(a_uint32_t dev_id, fal_port_t port_id,
				     a_bool_t * enable)
{
	sw_error_t rv = SW_OK;
	union mac_enable_u mac_enable;

	memset(&mac_enable, 0, sizeof(mac_enable));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(enable);

	port_id = port_id - 1;
	rv = hppe_mac_enable_get(dev_id, port_id, &mac_enable);

	if( rv != SW_OK )
		return rv;

	if (mac_enable.bf.rx_flow_en)
		*enable = A_TRUE;
	else
		*enable = A_FALSE;

	return SW_OK;
}

sw_error_t
adpt_hppe_port_txfc_status_get(a_uint32_t dev_id, fal_port_t port_id,
				     a_bool_t * enable)
{
	sw_error_t rv = SW_OK;
	union mac_enable_u mac_enable;

	memset(&mac_enable, 0, sizeof(mac_enable));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(enable);

	port_id = port_id - 1;
	rv = hppe_mac_enable_get(dev_id, port_id, &mac_enable);

	if( rv != SW_OK )
		return rv;

	if (mac_enable.bf.tx_flow_en)
		*enable = A_TRUE;
	else
		*enable = A_FALSE;

	return SW_OK;
}

sw_error_t
adpt_hppe_port_remote_loopback_set(a_uint32_t dev_id, fal_port_t port_id,
					 a_bool_t enable)
{

	ADPT_DEV_ID_CHECK(dev_id);


}
sw_error_t
adpt_hppe_port_flowctrl_set(a_uint32_t dev_id, fal_port_t port_id,
				  a_bool_t enable)
{
	union mac_enable_u mac_enable;

	memset(&mac_enable, 0, sizeof(mac_enable));
	ADPT_DEV_ID_CHECK(dev_id);

	return SW_OK;
}
sw_error_t
adpt_hppe_port_mru_set(a_uint32_t dev_id, fal_port_t port_id,
		fal_mru_ctrl_t *ctrl)
{
	union mru_mtu_ctrl_tbl_u mru_mtu_ctrl_tbl;

	memset(&mru_mtu_ctrl_tbl, 0, sizeof(mru_mtu_ctrl_tbl));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(ctrl);

	hppe_mru_mtu_ctrl_tbl_get(dev_id, port_id, &mru_mtu_ctrl_tbl);
	mru_mtu_ctrl_tbl.bf.mru = ctrl->mru_size;
	mru_mtu_ctrl_tbl.bf.mru_cmd = (a_uint32_t)ctrl->action;

	return hppe_mru_mtu_ctrl_tbl_set(dev_id, port_id, &mru_mtu_ctrl_tbl);
}
sw_error_t
adpt_hppe_port_autoneg_status_get(a_uint32_t dev_id, fal_port_t port_id,
					a_bool_t * status)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(status);


}

sw_error_t
adpt_hppe_port_txmac_status_get(a_uint32_t dev_id, fal_port_t port_id,
				      a_bool_t * enable)
{
	sw_error_t rv = SW_OK;
	union mac_enable_u mac_enable;

	memset(&mac_enable, 0, sizeof(mac_enable));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(enable);

	port_id = port_id - 1;
	rv = hppe_mac_enable_get(dev_id, port_id, &mac_enable);

	if( rv != SW_OK )
		return rv;

	if (mac_enable.bf.txmac_en)
		*enable = A_TRUE;
	else
		*enable = A_FALSE;

	return SW_OK;
}

sw_error_t
adpt_hppe_port_mdix_get(a_uint32_t dev_id, fal_port_t port_id,
			      fal_port_mdix_mode_t * mode)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(mode);


}

sw_error_t
adpt_hppe_ports_link_status_get(a_uint32_t dev_id, a_uint32_t * status)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(status);


}

sw_error_t
adpt_hppe_port_mac_loopback_set(a_uint32_t dev_id, fal_port_t port_id,
				 a_bool_t enable)
{
	union mac_ctrl2_u mac_ctrl2;

	memset(&mac_ctrl2, 0, sizeof(mac_ctrl2));
	ADPT_DEV_ID_CHECK(dev_id);

	port_id = port_id - 1;
	hppe_mac_ctrl2_get(dev_id, port_id, &mac_ctrl2);

	if (A_TRUE == enable)
		mac_ctrl2.bf.mac_loop_back = 1;
	if (A_FALSE== enable)
		mac_ctrl2.bf.mac_loop_back = 0;

	hppe_mac_ctrl2_set(dev_id, port_id, &mac_ctrl2);

	return SW_OK;
}
sw_error_t
adpt_hppe_port_phy_id_get(a_uint32_t dev_id, fal_port_t port_id,
		      a_uint16_t * org_id, a_uint16_t * rev_id)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(org_id);
	ADPT_NULL_POINT_CHECK(rev_id);


}

sw_error_t
adpt_hppe_port_mru_get(a_uint32_t dev_id, fal_port_t port_id,
		fal_mru_ctrl_t *ctrl)
{
	sw_error_t rv = SW_OK;
	union mru_mtu_ctrl_tbl_u mru_mtu_ctrl_tbl;

	memset(&mru_mtu_ctrl_tbl, 0, sizeof(mru_mtu_ctrl_tbl));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(ctrl);


	rv = hppe_mru_mtu_ctrl_tbl_get(dev_id, port_id, &mru_mtu_ctrl_tbl);

	if( rv != SW_OK )
		return rv;

	ctrl->mru_size = mru_mtu_ctrl_tbl.bf.mru;
	ctrl->action = (fal_mtu_action_t)mru_mtu_ctrl_tbl.bf.mru_cmd;

	return SW_OK;
}

sw_error_t
adpt_hppe_port_power_on(a_uint32_t dev_id, fal_port_t port_id)
{

	ADPT_DEV_ID_CHECK(dev_id);


}
sw_error_t
adpt_hppe_port_speed_set(a_uint32_t dev_id, fal_port_t port_id,
			       fal_port_speed_t speed)
{
	union mac_speed_u mac_speed;

	memset(&mac_speed, 0, sizeof(mac_speed));
	ADPT_DEV_ID_CHECK(dev_id);

	port_id = port_id - 1;
	hppe_mac_speed_get(dev_id, port_id, &mac_speed);

	if(FAL_SPEED_1000 == speed)
		mac_speed.bf.mac_speed = 2;
	if(FAL_SPEED_100 == speed)
		mac_speed.bf.mac_speed = 1;
	if(FAL_SPEED_10 == speed)
		mac_speed.bf.mac_speed = 0;

	hppe_mac_speed_set(dev_id, port_id, &mac_speed);

	return SW_OK;
}
sw_error_t
adpt_hppe_port_interface_mode_get(a_uint32_t dev_id, fal_port_t port_id,
			      fal_port_interface_mode_t * mode)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(mode);


}

sw_error_t
adpt_hppe_port_duplex_get(a_uint32_t dev_id, fal_port_t port_id,
				fal_port_duplex_t * pduplex)
{
	sw_error_t rv = SW_OK;
	union mac_enable_u mac_enable;

	memset(&mac_enable, 0, sizeof(mac_enable));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(pduplex);

	port_id = port_id - 1;
	rv = hppe_mac_enable_get(dev_id, port_id, &mac_enable);

	if( rv != SW_OK )
		return rv;

	if (mac_enable.bf.duplex == 0)
		*pduplex = FAL_HALF_DUPLEX;
	if (mac_enable.bf.duplex == 1)
		*pduplex = FAL_FULL_DUPLEX;

	return SW_OK;
}

sw_error_t
adpt_hppe_port_autoneg_adv_get(a_uint32_t dev_id, fal_port_t port_id,
				     a_uint32_t * autoadv)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(autoadv);


}

sw_error_t
adpt_hppe_port_mdix_status_get(a_uint32_t dev_id, fal_port_t port_id,
				     fal_port_mdix_status_t * mode)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(mode);


}

sw_error_t
adpt_hppe_port_mtu_set(a_uint32_t dev_id, fal_port_t port_id,
		fal_mtu_ctrl_t *ctrl)
{
	union mru_mtu_ctrl_tbl_u mru_mtu_ctrl_tbl;
	union mac_jumbo_size_u mac_jumbo_ctrl;
	union mc_mtu_ctrl_tbl_u mc_mtu_ctrl_tb;

	memset(&mru_mtu_ctrl_tbl, 0, sizeof(mru_mtu_ctrl_tbl));
	memset(&mac_jumbo_ctrl, 0, sizeof(mac_jumbo_ctrl));
	memset(&mc_mtu_ctrl_tb, 0, sizeof(mc_mtu_ctrl_tb));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(ctrl);

	if ((port_id > 0) && (port_id < 7))
	{
		hppe_mac_jumbo_size_get(dev_id, port_id - 1, &mac_jumbo_ctrl);
		mac_jumbo_ctrl.bf.mac_jumbo_size = ctrl->mtu_size;
		hppe_mac_jumbo_size_set(dev_id, port_id - 1, &mac_jumbo_ctrl);
	}

	hppe_mru_mtu_ctrl_tbl_get(dev_id, port_id, &mru_mtu_ctrl_tbl);
	mru_mtu_ctrl_tbl.bf.mtu = ctrl->mtu_size;
	mru_mtu_ctrl_tbl.bf.mtu_cmd = (a_uint32_t)ctrl->action;
	hppe_mru_mtu_ctrl_tbl_set(dev_id, port_id, &mru_mtu_ctrl_tbl);

	if ((port_id >= 0) && (port_id <= 7))
	{
		hppe_mc_mtu_ctrl_tbl_get(dev_id, port_id, &mc_mtu_ctrl_tb);
		mc_mtu_ctrl_tb.bf.mtu = ctrl->mtu_size;
		mc_mtu_ctrl_tb.bf.mtu_cmd = (a_uint32_t)ctrl->action;
		hppe_mc_mtu_ctrl_tbl_set(dev_id, port_id, &mc_mtu_ctrl_tb);
	}

	return SW_OK;
}
sw_error_t
adpt_hppe_port_link_status_get(a_uint32_t dev_id, fal_port_t port_id,
				     a_bool_t * status)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(status);


}

sw_error_t
adpt_hppe_port_8023az_set(a_uint32_t dev_id, fal_port_t port_id,
				a_bool_t enable)
{

	ADPT_DEV_ID_CHECK(dev_id);


}
sw_error_t
adpt_hppe_port_powersave_get(a_uint32_t dev_id, fal_port_t port_id,
			  a_bool_t * enable)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(enable);


}

sw_error_t
adpt_hppe_port_combo_prefer_medium_get(a_uint32_t dev_id,
						     a_uint32_t port_id,
						     fal_port_medium_t *
						     medium)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(medium);


}
sw_error_t
adpt_hppe_port_max_frame_size_get(a_uint32_t dev_id, fal_port_t port_id,
		a_uint32_t *max_frame)
{
	sw_error_t rv = SW_OK;
	union mac_ctrl2_u mac_ctrl2;

	memset(&mac_ctrl2, 0, sizeof(mac_ctrl2));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(max_frame);


	rv = hppe_mac_ctrl2_get(dev_id, port_id, &mac_ctrl2);

	if( rv != SW_OK )
		return rv;

	*max_frame = mac_ctrl2.bf.maxfr;

	return SW_OK;
}

sw_error_t
adpt_hppe_port_combo_prefer_medium_set(a_uint32_t dev_id,
					     a_uint32_t port_id,
					     fal_port_medium_t medium)
{

	ADPT_DEV_ID_CHECK(dev_id);


}
sw_error_t
adpt_hppe_port_power_off(a_uint32_t dev_id, fal_port_t port_id)
{

	ADPT_DEV_ID_CHECK(dev_id);


}
sw_error_t
adpt_hppe_port_txfc_status_set(a_uint32_t dev_id, fal_port_t port_id,
				     a_bool_t enable)
{
	union mac_enable_u mac_enable;

	memset(&mac_enable, 0, sizeof(mac_enable));
	ADPT_DEV_ID_CHECK(dev_id);

	port_id = port_id - 1;
	hppe_mac_enable_get(dev_id, port_id, &mac_enable);

	if (A_TRUE == enable)
		mac_enable.bf.tx_flow_en = 1;
	if (A_FALSE == enable)
		mac_enable.bf.tx_flow_en = 0;

	hppe_mac_enable_set(dev_id, port_id, &mac_enable);

	return SW_OK;
}
sw_error_t
adpt_hppe_port_counter_set(a_uint32_t dev_id, fal_port_t port_id,
		   a_bool_t enable)
{

	ADPT_DEV_ID_CHECK(dev_id);


}
sw_error_t
adpt_hppe_port_combo_fiber_mode_get(a_uint32_t dev_id,
						  a_uint32_t port_id,
						  fal_port_fiber_mode_t * mode)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(mode);


}

sw_error_t
adpt_hppe_port_local_loopback_set(a_uint32_t dev_id,
						fal_port_t port_id,
						a_bool_t enable)
{

	ADPT_DEV_ID_CHECK(dev_id);


}
sw_error_t
adpt_hppe_port_wol_status_set(a_uint32_t dev_id, fal_port_t port_id,
			      a_bool_t enable)
{

	ADPT_DEV_ID_CHECK(dev_id);


}
sw_error_t
adpt_hppe_port_magic_frame_mac_get(a_uint32_t dev_id, fal_port_t port_id,
				   fal_mac_addr_t * mac)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(mac);


}

sw_error_t
adpt_hppe_port_flowctrl_get(a_uint32_t dev_id, fal_port_t port_id,
				  a_bool_t * enable)
{
	sw_error_t rv = SW_OK;
	union mac_enable_u mac_enable;

	memset(&mac_enable, 0, sizeof(mac_enable));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(enable);


	rv = hppe_mac_enable_get(dev_id, port_id, &mac_enable);

	if( rv != SW_OK )
		return rv;



	return SW_OK;
}

sw_error_t
adpt_hppe_port_rxmac_status_set(a_uint32_t dev_id, fal_port_t port_id,
				      a_bool_t enable)
{
	union mac_enable_u mac_enable;

	memset(&mac_enable, 0, sizeof(mac_enable));
	ADPT_DEV_ID_CHECK(dev_id);

	port_id = port_id - 1;
	hppe_mac_enable_get(dev_id, port_id, &mac_enable);

	if (A_TRUE == enable)
		mac_enable.bf.rxmac_en = 1;
	if (A_FALSE == enable)
		mac_enable.bf.rxmac_en = 0;

	hppe_mac_enable_set(dev_id, port_id, &mac_enable);

	return SW_OK;
}
sw_error_t
adpt_hppe_port_counter_get(a_uint32_t dev_id, fal_port_t port_id,
		   a_bool_t * enable)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(enable);


}

sw_error_t
adpt_hppe_port_interface_mode_set(a_uint32_t dev_id, fal_port_t port_id,
			      fal_port_interface_mode_t mode)
{

	ADPT_DEV_ID_CHECK(dev_id);


}
sw_error_t
adpt_hppe_port_mac_loopback_get(a_uint32_t dev_id, fal_port_t port_id,
				 a_bool_t * enable)
{
	sw_error_t rv = SW_OK;
	union mac_ctrl2_u mac_ctrl2;

	memset(&mac_ctrl2, 0, sizeof(mac_ctrl2));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(enable);

	port_id = port_id - 1;
	rv = hppe_mac_ctrl2_get(dev_id, port_id, &mac_ctrl2);

	if( rv != SW_OK )
		return rv;

	*enable = mac_ctrl2.bf.mac_loop_back;

	return SW_OK;
}

sw_error_t
adpt_hppe_port_hibernate_get(a_uint32_t dev_id, fal_port_t port_id,
			  a_bool_t * enable)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(enable);


}

sw_error_t
adpt_hppe_port_autoneg_adv_set(a_uint32_t dev_id, fal_port_t port_id,
				     a_uint32_t autoadv)
{

	ADPT_DEV_ID_CHECK(dev_id);


}
sw_error_t
adpt_hppe_port_remote_loopback_get(a_uint32_t dev_id, fal_port_t port_id,
					 a_bool_t * enable)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(enable);


}

sw_error_t
adpt_hppe_port_counter_show(a_uint32_t dev_id, fal_port_t port_id,
				 fal_port_counter_info_t * counter_info)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(counter_info);


}
sw_error_t
adpt_hppe_port_autoneg_enable(a_uint32_t dev_id, fal_port_t port_id)
{

	ADPT_DEV_ID_CHECK(dev_id);


}
sw_error_t
adpt_hppe_port_mtu_get(a_uint32_t dev_id, fal_port_t port_id,
		fal_mtu_ctrl_t *ctrl)
{
	sw_error_t rv = SW_OK;
	union mru_mtu_ctrl_tbl_u mru_mtu_ctrl_tbl;

	memset(&mru_mtu_ctrl_tbl, 0, sizeof(mru_mtu_ctrl_tbl));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(ctrl);


	rv = hppe_mru_mtu_ctrl_tbl_get(dev_id, port_id, &mru_mtu_ctrl_tbl);

	if( rv != SW_OK )
		return rv;

	ctrl->mtu_size = mru_mtu_ctrl_tbl.bf.mtu;
	ctrl->action = (fal_mtu_action_t)mru_mtu_ctrl_tbl.bf.mtu_cmd;

	return SW_OK;
}

sw_error_t
adpt_hppe_port_interface_mode_status_get(a_uint32_t dev_id, fal_port_t port_id,
			      fal_port_interface_mode_t * mode)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(mode);


}

sw_error_t
adpt_hppe_port_reset(a_uint32_t dev_id, fal_port_t port_id)
{

	ADPT_DEV_ID_CHECK(dev_id);


}
sw_error_t
adpt_hppe_port_rxfc_status_set(a_uint32_t dev_id, fal_port_t port_id,
				     a_bool_t enable)
{
	union mac_enable_u mac_enable;

	memset(&mac_enable, 0, sizeof(mac_enable));
	ADPT_DEV_ID_CHECK(dev_id);

	port_id = port_id - 1;
	hppe_mac_enable_get(dev_id, port_id, &mac_enable);

	if (A_TRUE == enable)
		mac_enable.bf.rx_flow_en = 1;
	if (A_FALSE == enable)
		mac_enable.bf.rx_flow_en = 0;

	hppe_mac_enable_set(dev_id, port_id, &mac_enable);

	return SW_OK;
}
sw_error_t
adpt_hppe_port_speed_get(a_uint32_t dev_id, fal_port_t port_id,
			       fal_port_speed_t * pspeed)
{
	sw_error_t rv = SW_OK;
	union mac_speed_u mac_speed;

	memset(&mac_speed, 0, sizeof(mac_speed));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(pspeed);

	port_id = port_id - 1;
	rv = hppe_mac_speed_get(dev_id, port_id, &mac_speed);

	if( rv != SW_OK )
		return rv;

	if (mac_speed.bf.mac_speed == 0)
		*pspeed = FAL_SPEED_10;
	if (mac_speed.bf.mac_speed == 1)
		*pspeed = FAL_SPEED_100;
	if (mac_speed.bf.mac_speed == 2)
		*pspeed = FAL_SPEED_1000;

	return SW_OK;
}

sw_error_t
adpt_hppe_port_mdix_set(a_uint32_t dev_id, fal_port_t port_id,
			      fal_port_mdix_mode_t mode)
{

	ADPT_DEV_ID_CHECK(dev_id);


}
sw_error_t
adpt_hppe_port_wol_status_get(a_uint32_t dev_id, fal_port_t port_id,
			      a_bool_t * enable)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(enable);


}

sw_error_t
adpt_hppe_port_source_filter_get(a_uint32_t dev_id,
				fal_port_t port_id, a_bool_t * enable)
{
	sw_error_t rv = SW_OK;
	union port_in_forward_u port_in_forward = {0};

	ADPT_DEV_ID_CHECK(dev_id);

	rv = hppe_port_in_forward_get(dev_id, port_id, &port_in_forward);

	if (rv != SW_OK)
		return rv;

	if (port_in_forward.bf.source_filtering_bypass == A_TRUE)
		*enable = A_FALSE;
	else
		*enable = A_TRUE;

	return SW_OK;
}

sw_error_t
adpt_hppe_port_source_filter_set(a_uint32_t dev_id,
				fal_port_t port_id, a_bool_t enable)
{
	union port_in_forward_u port_in_forward = {0};

	ADPT_DEV_ID_CHECK(dev_id);

	if (enable == A_TRUE)
		port_in_forward.bf.source_filtering_bypass = A_FALSE;
	else
		port_in_forward.bf.source_filtering_bypass = A_TRUE;

	return hppe_port_in_forward_set(dev_id, port_id, &port_in_forward);
}

sw_error_t adpt_hppe_port_ctrl_init(a_uint32_t dev_id)
{
	adpt_api_t *p_adpt_api = NULL;

	p_adpt_api = adpt_api_ptr_get(dev_id);

	if(p_adpt_api == NULL)
		return SW_FAIL;

	p_adpt_api->adpt_port_local_loopback_get = adpt_hppe_port_local_loopback_get;
	p_adpt_api->adpt_port_autoneg_restart = adpt_hppe_port_autoneg_restart;
	p_adpt_api->adpt_port_duplex_set = adpt_hppe_port_duplex_set;
	p_adpt_api->adpt_port_rxmac_status_get = adpt_hppe_port_rxmac_status_get;
	p_adpt_api->adpt_port_cdt = adpt_hppe_port_cdt;
	p_adpt_api->adpt_port_txmac_status_set = adpt_hppe_port_txmac_status_set;
	p_adpt_api->adpt_port_combo_fiber_mode_set = adpt_hppe_port_combo_fiber_mode_set;
	p_adpt_api->adpt_port_combo_medium_status_get = adpt_hppe_port_combo_medium_status_get;
	p_adpt_api->adpt_port_magic_frame_mac_set = adpt_hppe_port_magic_frame_mac_set;
	p_adpt_api->adpt_port_powersave_set = adpt_hppe_port_powersave_set;
	p_adpt_api->adpt_port_hibernate_set = adpt_hppe_port_hibernate_set;
	p_adpt_api->adpt_port_8023az_get = adpt_hppe_port_8023az_get;
	p_adpt_api->adpt_port_rxfc_status_get = adpt_hppe_port_rxfc_status_get;
	p_adpt_api->adpt_port_txfc_status_get = adpt_hppe_port_txfc_status_get;
	p_adpt_api->adpt_port_remote_loopback_set = adpt_hppe_port_remote_loopback_set;
	p_adpt_api->adpt_port_flowctrl_set = adpt_hppe_port_flowctrl_set;
	p_adpt_api->adpt_port_mru_set = adpt_hppe_port_mru_set;
	p_adpt_api->adpt_port_autoneg_status_get = adpt_hppe_port_autoneg_status_get;
	p_adpt_api->adpt_port_txmac_status_get = adpt_hppe_port_txmac_status_get;
	p_adpt_api->adpt_port_mdix_get = adpt_hppe_port_mdix_get;
	p_adpt_api->adpt_ports_link_status_get = adpt_hppe_ports_link_status_get;
	p_adpt_api->adpt_port_mac_loopback_set = adpt_hppe_port_mac_loopback_set;
	p_adpt_api->adpt_port_phy_id_get = adpt_hppe_port_phy_id_get;
	p_adpt_api->adpt_port_mru_get = adpt_hppe_port_mru_get;
	p_adpt_api->adpt_port_power_on = adpt_hppe_port_power_on;
	p_adpt_api->adpt_port_speed_set = adpt_hppe_port_speed_set;
	p_adpt_api->adpt_port_interface_mode_get = adpt_hppe_port_interface_mode_get;
	p_adpt_api->adpt_port_duplex_get = adpt_hppe_port_duplex_get;
	p_adpt_api->adpt_port_autoneg_adv_get = adpt_hppe_port_autoneg_adv_get;
	p_adpt_api->adpt_port_mdix_status_get = adpt_hppe_port_mdix_status_get;
	p_adpt_api->adpt_port_mtu_set = adpt_hppe_port_mtu_set;
	p_adpt_api->adpt_port_link_status_get = adpt_hppe_port_link_status_get;
	p_adpt_api->adpt_port_8023az_set = adpt_hppe_port_8023az_set;
	p_adpt_api->adpt_port_powersave_get = adpt_hppe_port_powersave_get;
	p_adpt_api->adpt_port_combo_prefer_medium_get = adpt_hppe_port_combo_prefer_medium_get;
	p_adpt_api->adpt_port_combo_prefer_medium_set = adpt_hppe_port_combo_prefer_medium_set;
	p_adpt_api->adpt_port_power_off = adpt_hppe_port_power_off;
	p_adpt_api->adpt_port_txfc_status_set = adpt_hppe_port_txfc_status_set;
	p_adpt_api->adpt_port_counter_set = adpt_hppe_port_counter_set;
	p_adpt_api->adpt_port_combo_fiber_mode_get = adpt_hppe_port_combo_fiber_mode_get;
	p_adpt_api->adpt_port_local_loopback_set = adpt_hppe_port_local_loopback_set;
	p_adpt_api->adpt_port_wol_status_set = adpt_hppe_port_wol_status_set;
	p_adpt_api->adpt_port_magic_frame_mac_get = adpt_hppe_port_magic_frame_mac_get;
	p_adpt_api->adpt_port_flowctrl_get = adpt_hppe_port_flowctrl_get;
	p_adpt_api->adpt_port_rxmac_status_set = adpt_hppe_port_rxmac_status_set;
	p_adpt_api->adpt_port_counter_get = adpt_hppe_port_counter_get;
	p_adpt_api->adpt_port_interface_mode_set = adpt_hppe_port_interface_mode_set;
	p_adpt_api->adpt_port_mac_loopback_get = adpt_hppe_port_mac_loopback_get;
	p_adpt_api->adpt_port_hibernate_get = adpt_hppe_port_hibernate_get;
	p_adpt_api->adpt_port_autoneg_adv_set = adpt_hppe_port_autoneg_adv_set;
	p_adpt_api->adpt_port_remote_loopback_get = adpt_hppe_port_remote_loopback_get;
	p_adpt_api->adpt_port_counter_show = adpt_hppe_port_counter_show;
	p_adpt_api->adpt_port_autoneg_enable = adpt_hppe_port_autoneg_enable;
	p_adpt_api->adpt_port_mtu_get = adpt_hppe_port_mtu_get;
	p_adpt_api->adpt_port_interface_mode_status_get = adpt_hppe_port_interface_mode_status_get;
	p_adpt_api->adpt_port_reset = adpt_hppe_port_reset;
	p_adpt_api->adpt_port_rxfc_status_set = adpt_hppe_port_rxfc_status_set;
	p_adpt_api->adpt_port_speed_get = adpt_hppe_port_speed_get;
	p_adpt_api->adpt_port_mdix_set = adpt_hppe_port_mdix_set;
	p_adpt_api->adpt_port_wol_status_get = adpt_hppe_port_wol_status_get;
	p_adpt_api->adpt_port_max_frame_size_set = adpt_hppe_port_max_frame_size_set;
	p_adpt_api->adpt_port_max_frame_size_get = adpt_hppe_port_max_frame_size_get;
	p_adpt_api->adpt_port_source_filter_get = adpt_hppe_port_source_filter_get;
	p_adpt_api->adpt_port_source_filter_set = adpt_hppe_port_source_filter_set;


	return SW_OK;
}

/**
 * @}
 */
