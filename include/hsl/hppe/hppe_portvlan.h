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
#ifndef _HPPE_PORTVLAN_H_
#define _HPPE_PORTVLAN_H_

#define XLT_RULE_TBL_MAX_ENTRY	64
#define XLT_ACTION_TBL_MAX_ENTRY	64
#define PORT_PARSING_REG_MAX_ENTRY	8


sw_error_t
hppe_port_parsing_reg_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union port_parsing_reg_u *value);

sw_error_t
hppe_port_parsing_reg_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union port_parsing_reg_u *value);

sw_error_t
hppe_vlan_tpid_reg_get(
		a_uint32_t dev_id,
		union vlan_tpid_reg_u *value);

sw_error_t
hppe_vlan_tpid_reg_set(
		a_uint32_t dev_id,
		union vlan_tpid_reg_u *value);

sw_error_t
hppe_port_parsing_reg_port_role_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_port_parsing_reg_port_role_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_vlan_tpid_reg_stag_tpid_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_vlan_tpid_reg_stag_tpid_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_vlan_tpid_reg_ctag_tpid_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_vlan_tpid_reg_ctag_tpid_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_bridge_config_get(
		a_uint32_t dev_id,
		union bridge_config_u *value);

sw_error_t
hppe_bridge_config_set(
		a_uint32_t dev_id,
		union bridge_config_u *value);

sw_error_t
hppe_port_def_vid_0_get(
		a_uint32_t dev_id,
		union port_def_vid_0_u *value);

sw_error_t
hppe_port_def_vid_0_set(
		a_uint32_t dev_id,
		union port_def_vid_0_u *value);

sw_error_t
hppe_port_def_vid_1_get(
		a_uint32_t dev_id,
		union port_def_vid_1_u *value);

sw_error_t
hppe_port_def_vid_1_set(
		a_uint32_t dev_id,
		union port_def_vid_1_u *value);

sw_error_t
hppe_port_def_vid_2_get(
		a_uint32_t dev_id,
		union port_def_vid_2_u *value);

sw_error_t
hppe_port_def_vid_2_set(
		a_uint32_t dev_id,
		union port_def_vid_2_u *value);

sw_error_t
hppe_port_def_vid_3_get(
		a_uint32_t dev_id,
		union port_def_vid_3_u *value);

sw_error_t
hppe_port_def_vid_3_set(
		a_uint32_t dev_id,
		union port_def_vid_3_u *value);

sw_error_t
hppe_port_def_vid_4_get(
		a_uint32_t dev_id,
		union port_def_vid_4_u *value);

sw_error_t
hppe_port_def_vid_4_set(
		a_uint32_t dev_id,
		union port_def_vid_4_u *value);

sw_error_t
hppe_port_def_vid_5_get(
		a_uint32_t dev_id,
		union port_def_vid_5_u *value);

sw_error_t
hppe_port_def_vid_5_set(
		a_uint32_t dev_id,
		union port_def_vid_5_u *value);

sw_error_t
hppe_port_def_vid_6_get(
		a_uint32_t dev_id,
		union port_def_vid_6_u *value);

sw_error_t
hppe_port_def_vid_6_set(
		a_uint32_t dev_id,
		union port_def_vid_6_u *value);

sw_error_t
hppe_port_def_vid_7_get(
		a_uint32_t dev_id,
		union port_def_vid_7_u *value);

sw_error_t
hppe_port_def_vid_7_set(
		a_uint32_t dev_id,
		union port_def_vid_7_u *value);

sw_error_t
hppe_port_def_pcp_0_get(
		a_uint32_t dev_id,
		union port_def_pcp_0_u *value);

sw_error_t
hppe_port_def_pcp_0_set(
		a_uint32_t dev_id,
		union port_def_pcp_0_u *value);

sw_error_t
hppe_port_def_pcp_1_get(
		a_uint32_t dev_id,
		union port_def_pcp_1_u *value);

sw_error_t
hppe_port_def_pcp_1_set(
		a_uint32_t dev_id,
		union port_def_pcp_1_u *value);

sw_error_t
hppe_port_def_pcp_2_get(
		a_uint32_t dev_id,
		union port_def_pcp_2_u *value);

sw_error_t
hppe_port_def_pcp_2_set(
		a_uint32_t dev_id,
		union port_def_pcp_2_u *value);

sw_error_t
hppe_port_def_pcp_3_get(
		a_uint32_t dev_id,
		union port_def_pcp_3_u *value);

sw_error_t
hppe_port_def_pcp_3_set(
		a_uint32_t dev_id,
		union port_def_pcp_3_u *value);

sw_error_t
hppe_port_def_pcp_4_get(
		a_uint32_t dev_id,
		union port_def_pcp_4_u *value);

sw_error_t
hppe_port_def_pcp_4_set(
		a_uint32_t dev_id,
		union port_def_pcp_4_u *value);

sw_error_t
hppe_port_def_pcp_5_get(
		a_uint32_t dev_id,
		union port_def_pcp_5_u *value);

sw_error_t
hppe_port_def_pcp_5_set(
		a_uint32_t dev_id,
		union port_def_pcp_5_u *value);

sw_error_t
hppe_port_def_pcp_6_get(
		a_uint32_t dev_id,
		union port_def_pcp_6_u *value);

sw_error_t
hppe_port_def_pcp_6_set(
		a_uint32_t dev_id,
		union port_def_pcp_6_u *value);

sw_error_t
hppe_port_def_pcp_7_get(
		a_uint32_t dev_id,
		union port_def_pcp_7_u *value);

sw_error_t
hppe_port_def_pcp_7_set(
		a_uint32_t dev_id,
		union port_def_pcp_7_u *value);

sw_error_t
hppe_port_vlan_config_0_get(
		a_uint32_t dev_id,
		union port_vlan_config_0_u *value);

sw_error_t
hppe_port_vlan_config_0_set(
		a_uint32_t dev_id,
		union port_vlan_config_0_u *value);

sw_error_t
hppe_port_vlan_config_1_get(
		a_uint32_t dev_id,
		union port_vlan_config_1_u *value);

sw_error_t
hppe_port_vlan_config_1_set(
		a_uint32_t dev_id,
		union port_vlan_config_1_u *value);

sw_error_t
hppe_port_vlan_config_2_get(
		a_uint32_t dev_id,
		union port_vlan_config_2_u *value);

sw_error_t
hppe_port_vlan_config_2_set(
		a_uint32_t dev_id,
		union port_vlan_config_2_u *value);

sw_error_t
hppe_port_vlan_config_3_get(
		a_uint32_t dev_id,
		union port_vlan_config_3_u *value);

sw_error_t
hppe_port_vlan_config_3_set(
		a_uint32_t dev_id,
		union port_vlan_config_3_u *value);

sw_error_t
hppe_port_vlan_config_4_get(
		a_uint32_t dev_id,
		union port_vlan_config_4_u *value);

sw_error_t
hppe_port_vlan_config_4_set(
		a_uint32_t dev_id,
		union port_vlan_config_4_u *value);

sw_error_t
hppe_port_vlan_config_5_get(
		a_uint32_t dev_id,
		union port_vlan_config_5_u *value);

sw_error_t
hppe_port_vlan_config_5_set(
		a_uint32_t dev_id,
		union port_vlan_config_5_u *value);

sw_error_t
hppe_port_vlan_config_6_get(
		a_uint32_t dev_id,
		union port_vlan_config_6_u *value);

sw_error_t
hppe_port_vlan_config_6_set(
		a_uint32_t dev_id,
		union port_vlan_config_6_u *value);

sw_error_t
hppe_port_vlan_config_7_get(
		a_uint32_t dev_id,
		union port_vlan_config_7_u *value);

sw_error_t
hppe_port_vlan_config_7_set(
		a_uint32_t dev_id,
		union port_vlan_config_7_u *value);

sw_error_t
hppe_iv_dbg_addr_get(
		a_uint32_t dev_id,
		union iv_dbg_addr_u *value);

sw_error_t
hppe_iv_dbg_addr_set(
		a_uint32_t dev_id,
		union iv_dbg_addr_u *value);

sw_error_t
hppe_iv_dbg_data_get(
		a_uint32_t dev_id,
		union iv_dbg_data_u *value);

sw_error_t
hppe_iv_dbg_data_set(
		a_uint32_t dev_id,
		union iv_dbg_data_u *value);

sw_error_t
hppe_eco_reserve_get(
		a_uint32_t dev_id,
		union eco_reserve_u *value);

sw_error_t
hppe_eco_reserve_set(
		a_uint32_t dev_id,
		union eco_reserve_u *value);

sw_error_t
hppe_xlt_rule_tbl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union xlt_rule_tbl_u *value);

sw_error_t
hppe_xlt_rule_tbl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union xlt_rule_tbl_u *value);

sw_error_t
hppe_xlt_action_tbl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union xlt_action_tbl_u *value);

sw_error_t
hppe_xlt_action_tbl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union xlt_action_tbl_u *value);

sw_error_t
hppe_bridge_config_bridge_type_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_bridge_config_bridge_type_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_0_port_def_cvid_en_0_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_0_port_def_cvid_en_0_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_0_port_def_svid_en_0_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_0_port_def_svid_en_0_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_0_port_def_cvid_0_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_0_port_def_cvid_0_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_0_port_def_svid_0_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_0_port_def_svid_0_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_1_port_def_svid_1_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_1_port_def_svid_1_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_1_port_def_svid_en_1_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_1_port_def_svid_en_1_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_1_port_def_cvid_en_1_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_1_port_def_cvid_en_1_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_1_port_def_cvid_1_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_1_port_def_cvid_1_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_2_port_def_cvid_2_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_2_port_def_cvid_2_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_2_port_def_svid_2_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_2_port_def_svid_2_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_2_port_def_cvid_en_2_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_2_port_def_cvid_en_2_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_2_port_def_svid_en_2_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_2_port_def_svid_en_2_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_3_port_def_svid_3_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_3_port_def_svid_3_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_3_port_def_cvid_3_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_3_port_def_cvid_3_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_3_port_def_svid_en_3_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_3_port_def_svid_en_3_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_3_port_def_cvid_en_3_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_3_port_def_cvid_en_3_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_4_port_def_cvid_en_4_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_4_port_def_cvid_en_4_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_4_port_def_svid_en_4_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_4_port_def_svid_en_4_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_4_port_def_svid_4_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_4_port_def_svid_4_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_4_port_def_cvid_4_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_4_port_def_cvid_4_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_5_port_def_svid_en_5_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_5_port_def_svid_en_5_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_5_port_def_svid_5_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_5_port_def_svid_5_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_5_port_def_cvid_en_5_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_5_port_def_cvid_en_5_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_5_port_def_cvid_5_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_5_port_def_cvid_5_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_6_port_def_cvid_6_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_6_port_def_cvid_6_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_6_port_def_cvid_en_6_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_6_port_def_cvid_en_6_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_6_port_def_svid_6_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_6_port_def_svid_6_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_6_port_def_svid_en_6_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_6_port_def_svid_en_6_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_7_port_def_cvid_en_7_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_7_port_def_cvid_en_7_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_7_port_def_svid_en_7_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_7_port_def_svid_en_7_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_7_port_def_svid_7_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_7_port_def_svid_7_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_vid_7_port_def_cvid_7_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_vid_7_port_def_cvid_7_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_0_port_def_sdei_0_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_0_port_def_sdei_0_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_0_port_def_spcp_0_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_0_port_def_spcp_0_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_0_port_def_cdei_0_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_0_port_def_cdei_0_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_0_port_def_cpcp_0_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_0_port_def_cpcp_0_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_1_port_def_cpcp_1_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_1_port_def_cpcp_1_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_1_port_def_spcp_1_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_1_port_def_spcp_1_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_1_port_def_cdei_1_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_1_port_def_cdei_1_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_1_port_def_sdei_1_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_1_port_def_sdei_1_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_2_port_def_cpcp_2_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_2_port_def_cpcp_2_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_2_port_def_spcp_2_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_2_port_def_spcp_2_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_2_port_def_sdei_2_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_2_port_def_sdei_2_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_2_port_def_cdei_2_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_2_port_def_cdei_2_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_3_port_def_cdei_3_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_3_port_def_cdei_3_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_3_port_def_sdei_3_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_3_port_def_sdei_3_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_3_port_def_spcp_3_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_3_port_def_spcp_3_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_3_port_def_cpcp_3_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_3_port_def_cpcp_3_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_4_port_def_spcp_4_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_4_port_def_spcp_4_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_4_port_def_sdei_4_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_4_port_def_sdei_4_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_4_port_def_cdei_4_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_4_port_def_cdei_4_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_4_port_def_cpcp_4_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_4_port_def_cpcp_4_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_5_port_def_cdei_5_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_5_port_def_cdei_5_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_5_port_def_sdei_5_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_5_port_def_sdei_5_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_5_port_def_cpcp_5_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_5_port_def_cpcp_5_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_5_port_def_spcp_5_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_5_port_def_spcp_5_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_6_port_def_cdei_6_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_6_port_def_cdei_6_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_6_port_def_spcp_6_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_6_port_def_spcp_6_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_6_port_def_sdei_6_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_6_port_def_sdei_6_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_6_port_def_cpcp_6_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_6_port_def_cpcp_6_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_7_port_def_sdei_7_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_7_port_def_sdei_7_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_7_port_def_spcp_7_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_7_port_def_spcp_7_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_7_port_def_cdei_7_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_7_port_def_cdei_7_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_def_pcp_7_port_def_cpcp_7_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_def_pcp_7_port_def_cpcp_7_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_0_port_in_dei_prop_cmd_0_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_0_port_in_dei_prop_cmd_0_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_0_port_in_pcp_prop_cmd_0_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_0_port_in_pcp_prop_cmd_0_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_0_port_untag_fltr_cmd_0_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_0_port_untag_fltr_cmd_0_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_0_port_in_vlan_fltr_cmd_0_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_0_port_in_vlan_fltr_cmd_0_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_0_port_pri_tag_fltr_cmd_0_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_0_port_pri_tag_fltr_cmd_0_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_0_port_vlan_xlt_miss_fwd_cmd_0_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_0_port_vlan_xlt_miss_fwd_cmd_0_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_0_port_tag_fltr_cmd_0_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_0_port_tag_fltr_cmd_0_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_1_port_tag_fltr_cmd_1_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_1_port_tag_fltr_cmd_1_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_1_port_in_pcp_prop_cmd_1_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_1_port_in_pcp_prop_cmd_1_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_1_port_in_vlan_fltr_cmd_1_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_1_port_in_vlan_fltr_cmd_1_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_1_port_untag_fltr_cmd_1_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_1_port_untag_fltr_cmd_1_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_1_port_in_dei_prop_cmd_1_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_1_port_in_dei_prop_cmd_1_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_1_port_vlan_xlt_miss_fwd_cmd_1_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_1_port_vlan_xlt_miss_fwd_cmd_1_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_1_port_pri_tag_fltr_cmd_1_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_1_port_pri_tag_fltr_cmd_1_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_2_port_vlan_xlt_miss_fwd_cmd_2_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_2_port_vlan_xlt_miss_fwd_cmd_2_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_2_port_in_vlan_fltr_cmd_2_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_2_port_in_vlan_fltr_cmd_2_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_2_port_pri_tag_fltr_cmd_2_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_2_port_pri_tag_fltr_cmd_2_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_2_port_in_pcp_prop_cmd_2_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_2_port_in_pcp_prop_cmd_2_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_2_port_untag_fltr_cmd_2_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_2_port_untag_fltr_cmd_2_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_2_port_in_dei_prop_cmd_2_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_2_port_in_dei_prop_cmd_2_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_2_port_tag_fltr_cmd_2_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_2_port_tag_fltr_cmd_2_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_3_port_in_dei_prop_cmd_3_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_3_port_in_dei_prop_cmd_3_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_3_port_pri_tag_fltr_cmd_3_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_3_port_pri_tag_fltr_cmd_3_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_3_port_in_vlan_fltr_cmd_3_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_3_port_in_vlan_fltr_cmd_3_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_3_port_tag_fltr_cmd_3_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_3_port_tag_fltr_cmd_3_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_3_port_untag_fltr_cmd_3_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_3_port_untag_fltr_cmd_3_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_3_port_in_pcp_prop_cmd_3_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_3_port_in_pcp_prop_cmd_3_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_3_port_vlan_xlt_miss_fwd_cmd_3_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_3_port_vlan_xlt_miss_fwd_cmd_3_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_4_port_in_pcp_prop_cmd_4_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_4_port_in_pcp_prop_cmd_4_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_4_port_untag_fltr_cmd_4_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_4_port_untag_fltr_cmd_4_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_4_port_in_vlan_fltr_cmd_4_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_4_port_in_vlan_fltr_cmd_4_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_4_port_vlan_xlt_miss_fwd_cmd_4_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_4_port_vlan_xlt_miss_fwd_cmd_4_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_4_port_tag_fltr_cmd_4_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_4_port_tag_fltr_cmd_4_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_4_port_pri_tag_fltr_cmd_4_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_4_port_pri_tag_fltr_cmd_4_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_4_port_in_dei_prop_cmd_4_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_4_port_in_dei_prop_cmd_4_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_5_port_in_vlan_fltr_cmd_5_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_5_port_in_vlan_fltr_cmd_5_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_5_port_tag_fltr_cmd_5_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_5_port_tag_fltr_cmd_5_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_5_port_in_dei_prop_cmd_5_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_5_port_in_dei_prop_cmd_5_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_5_port_in_pcp_prop_cmd_5_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_5_port_in_pcp_prop_cmd_5_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_5_port_pri_tag_fltr_cmd_5_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_5_port_pri_tag_fltr_cmd_5_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_5_port_vlan_xlt_miss_fwd_cmd_5_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_5_port_vlan_xlt_miss_fwd_cmd_5_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_5_port_untag_fltr_cmd_5_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_5_port_untag_fltr_cmd_5_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_6_port_in_vlan_fltr_cmd_6_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_6_port_in_vlan_fltr_cmd_6_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_6_port_untag_fltr_cmd_6_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_6_port_untag_fltr_cmd_6_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_6_port_tag_fltr_cmd_6_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_6_port_tag_fltr_cmd_6_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_6_port_pri_tag_fltr_cmd_6_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_6_port_pri_tag_fltr_cmd_6_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_6_port_vlan_xlt_miss_fwd_cmd_6_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_6_port_vlan_xlt_miss_fwd_cmd_6_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_6_port_in_dei_prop_cmd_6_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_6_port_in_dei_prop_cmd_6_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_6_port_in_pcp_prop_cmd_6_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_6_port_in_pcp_prop_cmd_6_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_7_port_vlan_xlt_miss_fwd_cmd_7_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_7_port_vlan_xlt_miss_fwd_cmd_7_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_7_port_tag_fltr_cmd_7_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_7_port_tag_fltr_cmd_7_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_7_port_untag_fltr_cmd_7_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_7_port_untag_fltr_cmd_7_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_7_port_in_dei_prop_cmd_7_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_7_port_in_dei_prop_cmd_7_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_7_port_in_pcp_prop_cmd_7_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_7_port_in_pcp_prop_cmd_7_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_7_port_pri_tag_fltr_cmd_7_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_7_port_pri_tag_fltr_cmd_7_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_port_vlan_config_7_port_in_vlan_fltr_cmd_7_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_port_vlan_config_7_port_in_vlan_fltr_cmd_7_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_iv_dbg_addr_dbg_addr_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_iv_dbg_addr_dbg_addr_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_iv_dbg_data_dbg_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_iv_dbg_data_dbg_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_eco_reserve_eco_res_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_eco_reserve_eco_res_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_xlt_rule_tbl_ckey_vid_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_rule_tbl_ckey_vid_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_rule_tbl_frm_type_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_rule_tbl_frm_type_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_rule_tbl_prot_value_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_rule_tbl_prot_value_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_rule_tbl_valid_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_rule_tbl_valid_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_rule_tbl_frm_type_incl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_rule_tbl_frm_type_incl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_rule_tbl_ckey_dei_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_rule_tbl_ckey_dei_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_rule_tbl_skey_dei_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_rule_tbl_skey_dei_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_rule_tbl_skey_pcp_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_rule_tbl_skey_pcp_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_rule_tbl_ckey_pcp_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_rule_tbl_ckey_pcp_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_rule_tbl_ckey_vid_incl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_rule_tbl_ckey_vid_incl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_rule_tbl_ckey_dei_incl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_rule_tbl_ckey_dei_incl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_rule_tbl_port_bitmap_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_rule_tbl_port_bitmap_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_rule_tbl_prot_incl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_rule_tbl_prot_incl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_rule_tbl_skey_pcp_incl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_rule_tbl_skey_pcp_incl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_rule_tbl_ckey_fmt_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_rule_tbl_ckey_fmt_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_rule_tbl_skey_vid_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_rule_tbl_skey_vid_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_rule_tbl_skey_fmt_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_rule_tbl_skey_fmt_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_rule_tbl_ckey_pcp_incl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_rule_tbl_ckey_pcp_incl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_rule_tbl_skey_dei_incl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_rule_tbl_skey_dei_incl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_rule_tbl_skey_vid_incl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_rule_tbl_skey_vid_incl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_action_tbl_dei_swap_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_action_tbl_dei_swap_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_action_tbl_xlt_cvid_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_action_tbl_xlt_cvid_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_action_tbl_xlt_cpcp_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_action_tbl_xlt_cpcp_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_action_tbl_xlt_spcp_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_action_tbl_xlt_spcp_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_action_tbl_xlt_sdei_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_action_tbl_xlt_sdei_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_action_tbl_xlt_cvid_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_action_tbl_xlt_cvid_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_action_tbl_vsi_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_action_tbl_vsi_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_action_tbl_xlt_spcp_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_action_tbl_xlt_spcp_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_action_tbl_counter_id_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_action_tbl_counter_id_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_action_tbl_vid_swap_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_action_tbl_vid_swap_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_action_tbl_xlt_sdei_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_action_tbl_xlt_sdei_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_action_tbl_counter_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_action_tbl_counter_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_action_tbl_xlt_svid_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_action_tbl_xlt_svid_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_action_tbl_xlt_svid_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_action_tbl_xlt_svid_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_action_tbl_vsi_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_action_tbl_vsi_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_action_tbl_xlt_cpcp_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_action_tbl_xlt_cpcp_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_action_tbl_xlt_cdei_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_action_tbl_xlt_cdei_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_action_tbl_pcp_swap_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_action_tbl_pcp_swap_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_xlt_action_tbl_xlt_cdei_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_xlt_action_tbl_xlt_cdei_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

#endif

