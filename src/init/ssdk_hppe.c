/*
 * Copyright (c) 2012, 2014-2018, The Linux Foundation. All rights reserved.
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

#include "ssdk_init.h"
#include "adpt.h"
#include "adpt_hppe.h"
#include "fal.h"
#include "ref_vsi.h"
#include "ssdk_clk.h"

static sw_error_t qca_hppe_vsi_hw_init(a_uint32_t dev_id)
{
       return ppe_vsi_init(dev_id);
}

static sw_error_t qca_hppe_fdb_hw_init(a_uint32_t dev_id)
{
	a_uint32_t port = 0;
	adpt_api_t *p_api;

	SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));
	SW_RTN_ON_NULL(p_api->adpt_port_bridge_txmac_set);
	SW_RTN_ON_NULL(p_api->adpt_fdb_port_promisc_mode_set);

	for(port = SSDK_PHYSICAL_PORT0; port <= SSDK_PHYSICAL_PORT7; port++) {
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

	return SW_OK;
}

static sw_error_t
qca_hppe_portctrl_hw_init(a_uint32_t dev_id)
{
	a_uint32_t i = 0;

	for(i = SSDK_PHYSICAL_PORT1; i < SSDK_PHYSICAL_PORT7; i++) {
		qca_hppe_port_mac_type_set(dev_id, i, PORT_GMAC_TYPE);
#ifdef HAWKEYE_CHIP
		fal_port_txmac_status_set (dev_id, i, A_FALSE);
		fal_port_rxmac_status_set (dev_id, i, A_FALSE);
		fal_port_rxfc_status_set(dev_id, i, A_FALSE);
		fal_port_txfc_status_set(dev_id, i, A_FALSE);
#else
		fal_port_txmac_status_set (dev_id, i, A_TRUE);
		fal_port_rxmac_status_set (dev_id, i, A_TRUE);
		fal_port_rxfc_status_set(dev_id, i, A_TRUE);
		fal_port_txfc_status_set(dev_id, i, A_TRUE);
#endif
		fal_port_max_frame_size_set(dev_id, i, SSDK_MAX_FRAME_SIZE);
	}

	for(i = SSDK_PHYSICAL_PORT5; i < SSDK_PHYSICAL_PORT7; i++) {
		qca_hppe_port_mac_type_set(dev_id, i, PORT_XGMAC_TYPE);
#ifdef HAWKEYE_CHIP
		fal_port_txmac_status_set (dev_id, i, A_FALSE);
		fal_port_rxmac_status_set (dev_id, i, A_FALSE);
		fal_port_rxfc_status_set(dev_id, i, A_FALSE);
		fal_port_txfc_status_set(dev_id, i, A_FALSE);
#else
		fal_port_txmac_status_set (dev_id, i, A_TRUE);
		fal_port_rxmac_status_set (dev_id, i, A_TRUE);
		fal_port_rxfc_status_set(dev_id, i, A_TRUE);
		fal_port_txfc_status_set(dev_id, i, A_TRUE);
#endif
		fal_port_max_frame_size_set(dev_id, i, SSDK_MAX_FRAME_SIZE);
	}

	return SW_OK;
}

static sw_error_t
qca_hppe_policer_hw_init(a_uint32_t dev_id)
{
	a_uint32_t i = 0;

	fal_policer_timeslot_set(dev_id, HPPE_POLICER_TIMESLOT_DFT);

	for (i = SSDK_PHYSICAL_PORT0; i <= SSDK_PHYSICAL_PORT7; i++) {
		fal_port_policer_compensation_byte_set(dev_id, i, 4);
	}

	return SW_OK;
}

static sw_error_t
qca_hppe_shaper_hw_init(a_uint32_t dev_id)
{
	fal_shaper_token_number_t port_token_number, queue_token_number;
	fal_shaper_token_number_t flow_token_number;
	a_uint32_t i = 0;

	port_token_number.c_token_number_negative_en = A_FALSE;
	port_token_number.c_token_number = HPPE_MAX_C_TOKEN_NUM;
	queue_token_number.c_token_number_negative_en = A_FALSE;
	queue_token_number.c_token_number = HPPE_MAX_C_TOKEN_NUM;
	queue_token_number.e_token_number_negative_en = A_FALSE;
	queue_token_number.e_token_number = HPPE_MAX_E_TOKEN_NUM;
	flow_token_number.c_token_number_negative_en = A_FALSE;
	flow_token_number.c_token_number = HPPE_MAX_C_TOKEN_NUM;
	flow_token_number.e_token_number_negative_en = A_FALSE;
	flow_token_number.e_token_number = HPPE_MAX_E_TOKEN_NUM;

	for (i = SSDK_PHYSICAL_PORT0; i <= SSDK_PHYSICAL_PORT7; i++) {
		fal_port_shaper_token_number_set(dev_id, i, &port_token_number);
	}

	for(i = 0; i < SSDK_L0SCHEDULER_CFG_MAX; i ++) {
		fal_queue_shaper_token_number_set(dev_id, i, &queue_token_number);
	}

	for(i = 0; i < SSDK_L1SCHEDULER_CFG_MAX; i ++) {
		fal_flow_shaper_token_number_set(dev_id, i, &flow_token_number);
	}

	fal_port_shaper_timeslot_set(dev_id, HPPE_PORT_SHAPER_TIMESLOT_DFT);
	fal_flow_shaper_timeslot_set(dev_id, HPPE_FLOW_SHAPER_TIMESLOT_DFT);
	fal_queue_shaper_timeslot_set(dev_id, HPPE_QUEUE_SHAPER_TIMESLOT_DFT);
	fal_shaper_ipg_preamble_length_set(dev_id,
				HPPE_SHAPER_IPG_PREAMBLE_LEN_DFT);

	return SW_OK;
}

static sw_error_t
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
	for (port_id = SSDK_PHYSICAL_PORT1; port_id <= SSDK_PHYSICAL_PORT7;
			port_id++) {
		fal_port_qinq_mode_set(dev_id, port_id, &port_qinq_role);
	}

	/* configure ingress and egress stpid/ctpid as 0x88a8/0x8100 */
	in_eg_tpid.mask = 0x3;
	in_eg_tpid.ctpid = FAL_DEF_VLAN_CTPID;
	in_eg_tpid.stpid = FAL_DEF_VLAN_STPID;
	fal_ingress_tpid_set(dev_id, &in_eg_tpid);
	fal_egress_tpid_set(dev_id, &in_eg_tpid);

	/* configure the port0 - port7 of vsi0 - vsi31 to unmodified */
	for (vsi_idx = 0; vsi_idx <= FAL_VSI_MAX; vsi_idx++) {
		for (port_id = SSDK_PHYSICAL_PORT0;
			port_id <= SSDK_PHYSICAL_PORT7;	port_id++) {
			fal_port_vsi_egmode_set(dev_id, vsi_idx,
						port_id, FAL_EG_UNMODIFIED);
		}
	}

	vlantag_eg_mode.mask = 0x3;
	vlantag_eg_mode.stag_mode = FAL_EG_UNTOUCHED;
	vlantag_eg_mode.ctag_mode = FAL_EG_UNTOUCHED;
	/*stag/ctag egress mode as untouched/untouched*/
	fal_port_vlantag_egmode_set(dev_id, SSDK_PHYSICAL_PORT0,
				&vlantag_eg_mode);
	/*vsi tag mode control to disable*/
	fal_port_vlantag_vsi_egmode_enable(dev_id, SSDK_PHYSICAL_PORT0,
				A_FALSE);
	/*ingress vlan translation mismatched command as forward*/
	fal_port_vlan_xlt_miss_cmd_set(dev_id, SSDK_PHYSICAL_PORT0,
				FAL_MAC_FRWRD);

	vlantag_eg_mode.stag_mode = FAL_EG_UNMODIFIED;
	vlantag_eg_mode.ctag_mode = FAL_EG_UNMODIFIED;
	for (port_id = SSDK_PHYSICAL_PORT1; port_id <= SSDK_PHYSICAL_PORT7;
			port_id++) {
		/*ingress vlan translation mismatched command as forward*/
		fal_port_vlan_xlt_miss_cmd_set(dev_id, port_id, FAL_MAC_FRWRD);
		/*vsi tag mode control to enable*/
		fal_port_vlantag_vsi_egmode_enable(dev_id, port_id, A_TRUE);
		/*stag/ctag egress mode as unmodified/unmodified*/
		fal_port_vlantag_egmode_set(dev_id, port_id, &vlantag_eg_mode);
	}

	return SW_OK;
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

static sw_error_t
qca_hppe_tdm_hw_init(a_uint32_t dev_id)
{
	adpt_api_t *p_api;
	a_uint32_t i = 0;
	a_uint32_t num;
	fal_port_tdm_ctrl_t tdm_ctrl;
	fal_port_scheduler_cfg_t *scheduler_cfg;
	fal_port_tdm_tick_cfg_t *bm_cfg;

	SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));
	SW_RTN_ON_NULL(p_api->adpt_port_scheduler_cfg_set);
	SW_RTN_ON_NULL(p_api->adpt_tdm_tick_num_set);

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

	SW_RTN_ON_NULL(p_api->adpt_port_tdm_tick_cfg_set);
	SW_RTN_ON_NULL(p_api->adpt_port_tdm_ctrl_set);

	if (ssdk_dt_global.ssdk_dt_switch_nodes[dev_id]->bm_tick_mode == 0) {
		num = sizeof(port_tdm0_tbl) / sizeof(fal_port_tdm_tick_cfg_t);
		bm_cfg = port_tdm0_tbl;
	} else {
		return SW_BAD_VALUE;
	}
	for (i = 0; i < num; i++) {
		p_api->adpt_port_tdm_tick_cfg_set(0, i, &bm_cfg[i]);
	}
	tdm_ctrl.enable = A_TRUE;
	tdm_ctrl.offset = A_FALSE;
	tdm_ctrl.depth = num;
	p_api->adpt_port_tdm_ctrl_set(0, &tdm_ctrl);
	SSDK_INFO("tdm setup num=%d\n", num);
	return SW_OK;
}

static sw_error_t
qca_hppe_bm_hw_init(a_uint32_t dev_id)
{
	a_uint32_t i = 0;
	fal_bm_dynamic_cfg_t cfg;

	for (i = 0; i <  HPPE_BM_PORT_NUM; i++) {
		/* enable fc */
		fal_port_bm_ctrl_set(0, i, A_TRUE);
		/* map to group 0 */
		fal_port_bufgroup_map_set(0, i, 0);
	}

	fal_bm_bufgroup_buffer_set(dev_id, 0, 1400);

	/* set reserved buffer */
	for (i = 0; i < HPPE_BM_PHY_PORT_OFFSET; i++) {
		fal_bm_port_reserved_buffer_set(dev_id, i, 0, 100);
	}
	for (i = HPPE_BM_PHY_PORT_OFFSET; i < HPPE_BM_PORT_NUM-1; i++) {
		fal_bm_port_reserved_buffer_set(dev_id, i, 0, 128);
	}
	fal_bm_port_reserved_buffer_set(dev_id, HPPE_BM_PORT_NUM-1, 0, 40);

	memset(&cfg, 0, sizeof(cfg));
	cfg.resume_min_thresh = 0;
	cfg.resume_off = 36;
	cfg.weight= 4;
	cfg.shared_ceiling = 250;
	for (i = 0; i < HPPE_BM_PORT_NUM; i++) {
		fal_bm_port_dynamic_thresh_set(dev_id, i, &cfg);
	}
	return SW_OK;
}

static sw_error_t
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
	ac_ctrl.ac_en = A_TRUE;
	ac_ctrl.ac_fc_en = A_FALSE;
	for (i = 0; i < SSDK_L0SCHEDULER_CFG_MAX; i++) {
		obj.type = FAL_AC_QUEUE;
		obj.obj_id = i;
		fal_ac_ctrl_set(dev_id, &obj, &ac_ctrl);
		fal_ac_queue_group_set(dev_id, i, 0);
		fal_ac_prealloc_buffer_set(dev_id, &obj, 0);
	}

	group_buff.prealloc_buffer = 0;
	group_buff.total_buffer = 2000;
	fal_ac_group_buffer_set(dev_id, 0, &group_buff);

	memset(&dthresh_cfg, 0, sizeof(dthresh_cfg));
	dthresh_cfg.shared_weight = 4;
	dthresh_cfg.ceiling = 400;
	dthresh_cfg.green_resume_off = 36;
	for (i = 0; i < SSDK_L0SCHEDULER_UCASTQ_CFG_MAX; i++) {
		fal_ac_dynamic_threshold_set(dev_id, i, &dthresh_cfg);
	}

	memset(&sthresh_cfg, 0, sizeof(sthresh_cfg));
	sthresh_cfg.green_max = 250;
	sthresh_cfg.green_resume_off = 36;
	for (i = SSDK_L0SCHEDULER_UCASTQ_CFG_MAX; i < SSDK_L0SCHEDULER_CFG_MAX;
			i++) {
		obj.type = FAL_AC_QUEUE;
		obj.obj_id = i;
		fal_ac_static_threshold_set(dev_id, &obj, &sthresh_cfg);
	}

	return SW_OK;
}

static sw_error_t
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
	for (i = SSDK_PHYSICAL_PORT0; i <= SSDK_PHYSICAL_PORT7; i++) {
		fal_qos_port_group_get(dev_id, i, &group_sel);
	}
	/* qos precedence */
	pri_pre.flow_pri = 4;
	pri_pre.acl_pri = 2;
	pri_pre.dscp_pri = 1;
	pri_pre.pcp_pri = 0;
	pri_pre.preheader_pri = 3;
	for (i = SSDK_PHYSICAL_PORT0; i <= SSDK_PHYSICAL_PORT7; i++) {
		fal_qos_port_pri_precedence_set(dev_id, i, &pri_pre);
	}

	return SW_OK;
}

#define LIST_ID_BYP_FDB_LRN 63/*reserved for bypass fdb learning*/
#define LIST_PRI_BYP_FDB_LRN 32

sw_error_t qca_hppe_acl_byp_intf_mac_learn(a_uint32_t dev_id)
{
	a_uint32_t index = 0;
	fal_acl_rule_t rule = { 0 };

	if(0 == ssdk_dt_global.num_intf_mac){
		return SW_OK;/*No found interface MAC*/
	}

	/*Bypass fdb learn*/
	rule.rule_type = FAL_ACL_RULE_MAC;
	rule.bypass_bitmap |= (1<<FAL_ACL_BYPASS_FDB_LEARNING);
	rule.bypass_bitmap |= (1<<FAL_ACL_BYPASS_FDB_REFRESH);

	FAL_FIELD_FLG_SET(rule.field_flg, FAL_ACL_FIELD_MAC_SA);

	fal_acl_list_creat(dev_id, LIST_ID_BYP_FDB_LRN, LIST_PRI_BYP_FDB_LRN);

	for (index = 0; index < SSDK_MAX_NR_ETH; index++) {
		if(index >= ssdk_dt_global.num_intf_mac)
			break;
		memcpy(rule.src_mac_val.uc, ssdk_dt_global.intf_mac[index].uc, 6);
		memset(rule.src_mac_mask.uc, 0xff, 6);
		SSDK_DEBUG("%02x:%02x:%02x:%02x:%02x:%02x\n", rule.src_mac_val.uc[0],
			rule.src_mac_val.uc[1], rule.src_mac_val.uc[2], rule.src_mac_val.uc[3],
			rule.src_mac_val.uc[4], rule.src_mac_val.uc[5]);
		fal_acl_rule_add(dev_id, LIST_ID_BYP_FDB_LRN, index, 1, &rule);
	}
	fal_acl_list_bind(dev_id, LIST_ID_BYP_FDB_LRN, FAL_ACL_DIREC_IN,
				FAL_ACL_BIND_PORTBITMAP, 0x7c);

	return SW_OK;
}

static sw_error_t
qca_hppe_interface_mode_init(a_uint32_t dev_id, a_uint32_t mode0, a_uint32_t mode1, a_uint32_t mode2)
{

	adpt_api_t *p_api;
	sw_error_t rv = SW_OK;
	fal_port_t port_id;

	SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));
	SW_RTN_ON_NULL(p_api->adpt_port_mux_mac_type_set);
#ifdef HAWKEYE_CHIP
	SW_RTN_ON_NULL(p_api->adpt_uniphy_mode_set);


	rv = p_api->adpt_uniphy_mode_set(dev_id, SSDK_UNIPHY_INSTANCE0, mode0);
	SW_RTN_ON_ERROR(rv);

	rv = p_api->adpt_uniphy_mode_set(dev_id, SSDK_UNIPHY_INSTANCE1, mode1);
	SW_RTN_ON_ERROR(rv);

	rv = p_api->adpt_uniphy_mode_set(dev_id, SSDK_UNIPHY_INSTANCE2, mode2);
	SW_RTN_ON_ERROR(rv);
#endif
	for(port_id = SSDK_PHYSICAL_PORT1; port_id <=SSDK_PHYSICAL_PORT6; port_id++) {
		rv = p_api->adpt_port_mux_mac_type_set(dev_id, port_id, mode0, mode1, mode2);
		if(rv != SW_OK) {
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
		SW_RTN_ON_ERROR(rv);
		mgmt.miss_action = FAL_MAC_RDT_TO_CPU;
		rv = fal_flow_mgmt_set(dev_id, FAL_FLOW_MCAST, dir, &mgmt);
		SW_RTN_ON_ERROR(rv);
	}
	return SW_OK;
}

sw_error_t qca_hppe_hw_init(ssdk_init_cfg *cfg, a_uint32_t dev_id)
{
	sw_error_t rv = SW_OK;
#ifdef HAWKEYE_CHIP
	/* reset ppe */
	ssdk_ppe_reset_init();
#endif
	rv = qca_switch_init(dev_id);
	SW_RTN_ON_ERROR(rv);

	rv = qca_hppe_bm_hw_init(dev_id);
	SW_RTN_ON_ERROR(rv);
	rv = qca_hppe_qm_hw_init(dev_id);
	SW_RTN_ON_ERROR(rv);
	rv = qca_hppe_qos_scheduler_hw_init(dev_id);
	SW_RTN_ON_ERROR(rv);
	rv = qca_hppe_tdm_hw_init(dev_id);
	SW_RTN_ON_ERROR(rv);
	rv= qca_hppe_fdb_hw_init(dev_id);
	SW_RTN_ON_ERROR(rv);
	rv= qca_hppe_vsi_hw_init(dev_id);
	SW_RTN_ON_ERROR(rv);
	rv = qca_hppe_portvlan_hw_init(dev_id);
	SW_RTN_ON_ERROR(rv);
	rv = qca_hppe_portctrl_hw_init(dev_id);
	SW_RTN_ON_ERROR(rv);
	rv = qca_hppe_policer_hw_init(dev_id);
	SW_RTN_ON_ERROR(rv);
	rv = qca_hppe_shaper_hw_init(dev_id);
	SW_RTN_ON_ERROR(rv);
	rv = qca_hppe_flow_hw_init(dev_id);
	SW_RTN_ON_ERROR(rv);
	rv = qca_hppe_acl_byp_intf_mac_learn(dev_id);
	SW_RTN_ON_ERROR(rv);
	rv = qca_hppe_interface_mode_init(dev_id, cfg->mac_mode, cfg->mac_mode1,
				cfg->mac_mode2);
	return rv;
}

