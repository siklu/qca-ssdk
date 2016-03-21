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
#include "hsl.h"
#include "hppe_reg_access.h"
#include "hppe_portvlan_reg.h"
#include "hppe_portvlan.h"

sw_error_t
hppe_port_parsing_reg_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union port_parsing_reg_u *value)
{
	if (index >= PORT_PARSING_REG_MAX_ENTRY)
		return SW_OUT_OF_RANGE;
	return hppe_reg_get(
				dev_id,
				IPR_CSR_BASE_ADDR + PORT_PARSING_REG_ADDRESS + \
				index * PORT_PARSING_REG_INC,
				&value->val);
}

sw_error_t
hppe_port_parsing_reg_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union port_parsing_reg_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPR_CSR_BASE_ADDR + PORT_PARSING_REG_ADDRESS + \
				index * PORT_PARSING_REG_INC,
				value->val);
}

sw_error_t
hppe_vlan_tpid_reg_get(
		a_uint32_t dev_id,
		union vlan_tpid_reg_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPR_CSR_BASE_ADDR + VLAN_TPID_REG_ADDRESS,
				&value->val);
}

sw_error_t
hppe_vlan_tpid_reg_set(
		a_uint32_t dev_id,
		union vlan_tpid_reg_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPR_CSR_BASE_ADDR + VLAN_TPID_REG_ADDRESS,
				value->val);
}

sw_error_t
hppe_port_parsing_reg_port_role_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union port_parsing_reg_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_parsing_reg_get(dev_id, index, &reg_val);
	*value = reg_val.bf.port_role;
	return ret;
}

sw_error_t
hppe_port_parsing_reg_port_role_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union port_parsing_reg_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_parsing_reg_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_role = value;
	ret = hppe_port_parsing_reg_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_vlan_tpid_reg_stag_tpid_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union vlan_tpid_reg_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_vlan_tpid_reg_get(dev_id, &reg_val);
	*value = reg_val.bf.stag_tpid;
	return ret;
}

sw_error_t
hppe_vlan_tpid_reg_stag_tpid_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union vlan_tpid_reg_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_vlan_tpid_reg_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.stag_tpid = value;
	ret = hppe_vlan_tpid_reg_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_vlan_tpid_reg_ctag_tpid_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union vlan_tpid_reg_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_vlan_tpid_reg_get(dev_id, &reg_val);
	*value = reg_val.bf.ctag_tpid;
	return ret;
}

sw_error_t
hppe_vlan_tpid_reg_ctag_tpid_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union vlan_tpid_reg_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_vlan_tpid_reg_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.ctag_tpid = value;
	ret = hppe_vlan_tpid_reg_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_bridge_config_get(
		a_uint32_t dev_id,
		union bridge_config_u *value)
{
	return hppe_reg_get(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + BRIDGE_CONFIG_ADDRESS,
				&value->val);
}

sw_error_t
hppe_bridge_config_set(
		a_uint32_t dev_id,
		union bridge_config_u *value)
{
	return hppe_reg_set(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + BRIDGE_CONFIG_ADDRESS,
				value->val);
}

sw_error_t
hppe_port_def_vid_0_get(
		a_uint32_t dev_id,
		union port_def_vid_0_u *value)
{
	return hppe_reg_get(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_VID_0_ADDRESS,
				&value->val);
}

sw_error_t
hppe_port_def_vid_0_set(
		a_uint32_t dev_id,
		union port_def_vid_0_u *value)
{
	return hppe_reg_set(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_VID_0_ADDRESS,
				value->val);
}

sw_error_t
hppe_port_def_vid_1_get(
		a_uint32_t dev_id,
		union port_def_vid_1_u *value)
{
	return hppe_reg_get(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_VID_1_ADDRESS,
				&value->val);
}

sw_error_t
hppe_port_def_vid_1_set(
		a_uint32_t dev_id,
		union port_def_vid_1_u *value)
{
	return hppe_reg_set(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_VID_1_ADDRESS,
				value->val);
}

sw_error_t
hppe_port_def_vid_2_get(
		a_uint32_t dev_id,
		union port_def_vid_2_u *value)
{
	return hppe_reg_get(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_VID_2_ADDRESS,
				&value->val);
}

sw_error_t
hppe_port_def_vid_2_set(
		a_uint32_t dev_id,
		union port_def_vid_2_u *value)
{
	return hppe_reg_set(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_VID_2_ADDRESS,
				value->val);
}

sw_error_t
hppe_port_def_vid_3_get(
		a_uint32_t dev_id,
		union port_def_vid_3_u *value)
{
	return hppe_reg_get(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_VID_3_ADDRESS,
				&value->val);
}

sw_error_t
hppe_port_def_vid_3_set(
		a_uint32_t dev_id,
		union port_def_vid_3_u *value)
{
	return hppe_reg_set(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_VID_3_ADDRESS,
				value->val);
}

sw_error_t
hppe_port_def_vid_4_get(
		a_uint32_t dev_id,
		union port_def_vid_4_u *value)
{
	return hppe_reg_get(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_VID_4_ADDRESS,
				&value->val);
}

sw_error_t
hppe_port_def_vid_4_set(
		a_uint32_t dev_id,
		union port_def_vid_4_u *value)
{
	return hppe_reg_set(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_VID_4_ADDRESS,
				value->val);
}

sw_error_t
hppe_port_def_vid_5_get(
		a_uint32_t dev_id,
		union port_def_vid_5_u *value)
{
	return hppe_reg_get(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_VID_5_ADDRESS,
				&value->val);
}

sw_error_t
hppe_port_def_vid_5_set(
		a_uint32_t dev_id,
		union port_def_vid_5_u *value)
{
	return hppe_reg_set(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_VID_5_ADDRESS,
				value->val);
}

sw_error_t
hppe_port_def_vid_6_get(
		a_uint32_t dev_id,
		union port_def_vid_6_u *value)
{
	return hppe_reg_get(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_VID_6_ADDRESS,
				&value->val);
}

sw_error_t
hppe_port_def_vid_6_set(
		a_uint32_t dev_id,
		union port_def_vid_6_u *value)
{
	return hppe_reg_set(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_VID_6_ADDRESS,
				value->val);
}

sw_error_t
hppe_port_def_vid_7_get(
		a_uint32_t dev_id,
		union port_def_vid_7_u *value)
{
	return hppe_reg_get(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_VID_7_ADDRESS,
				&value->val);
}

sw_error_t
hppe_port_def_vid_7_set(
		a_uint32_t dev_id,
		union port_def_vid_7_u *value)
{
	return hppe_reg_set(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_VID_7_ADDRESS,
				value->val);
}

sw_error_t
hppe_port_def_pcp_0_get(
		a_uint32_t dev_id,
		union port_def_pcp_0_u *value)
{
	return hppe_reg_get(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_PCP_0_ADDRESS,
				&value->val);
}

sw_error_t
hppe_port_def_pcp_0_set(
		a_uint32_t dev_id,
		union port_def_pcp_0_u *value)
{
	return hppe_reg_set(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_PCP_0_ADDRESS,
				value->val);
}

sw_error_t
hppe_port_def_pcp_1_get(
		a_uint32_t dev_id,
		union port_def_pcp_1_u *value)
{
	return hppe_reg_get(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_PCP_1_ADDRESS,
				&value->val);
}

sw_error_t
hppe_port_def_pcp_1_set(
		a_uint32_t dev_id,
		union port_def_pcp_1_u *value)
{
	return hppe_reg_set(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_PCP_1_ADDRESS,
				value->val);
}

sw_error_t
hppe_port_def_pcp_2_get(
		a_uint32_t dev_id,
		union port_def_pcp_2_u *value)
{
	return hppe_reg_get(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_PCP_2_ADDRESS,
				&value->val);
}

sw_error_t
hppe_port_def_pcp_2_set(
		a_uint32_t dev_id,
		union port_def_pcp_2_u *value)
{
	return hppe_reg_set(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_PCP_2_ADDRESS,
				value->val);
}

sw_error_t
hppe_port_def_pcp_3_get(
		a_uint32_t dev_id,
		union port_def_pcp_3_u *value)
{
	return hppe_reg_get(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_PCP_3_ADDRESS,
				&value->val);
}

sw_error_t
hppe_port_def_pcp_3_set(
		a_uint32_t dev_id,
		union port_def_pcp_3_u *value)
{
	return hppe_reg_set(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_PCP_3_ADDRESS,
				value->val);
}

sw_error_t
hppe_port_def_pcp_4_get(
		a_uint32_t dev_id,
		union port_def_pcp_4_u *value)
{
	return hppe_reg_get(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_PCP_4_ADDRESS,
				&value->val);
}

sw_error_t
hppe_port_def_pcp_4_set(
		a_uint32_t dev_id,
		union port_def_pcp_4_u *value)
{
	return hppe_reg_set(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_PCP_4_ADDRESS,
				value->val);
}

sw_error_t
hppe_port_def_pcp_5_get(
		a_uint32_t dev_id,
		union port_def_pcp_5_u *value)
{
	return hppe_reg_get(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_PCP_5_ADDRESS,
				&value->val);
}

sw_error_t
hppe_port_def_pcp_5_set(
		a_uint32_t dev_id,
		union port_def_pcp_5_u *value)
{
	return hppe_reg_set(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_PCP_5_ADDRESS,
				value->val);
}

sw_error_t
hppe_port_def_pcp_6_get(
		a_uint32_t dev_id,
		union port_def_pcp_6_u *value)
{
	return hppe_reg_get(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_PCP_6_ADDRESS,
				&value->val);
}

sw_error_t
hppe_port_def_pcp_6_set(
		a_uint32_t dev_id,
		union port_def_pcp_6_u *value)
{
	return hppe_reg_set(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_PCP_6_ADDRESS,
				value->val);
}

sw_error_t
hppe_port_def_pcp_7_get(
		a_uint32_t dev_id,
		union port_def_pcp_7_u *value)
{
	return hppe_reg_get(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_PCP_7_ADDRESS,
				&value->val);
}

sw_error_t
hppe_port_def_pcp_7_set(
		a_uint32_t dev_id,
		union port_def_pcp_7_u *value)
{
	return hppe_reg_set(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_DEF_PCP_7_ADDRESS,
				value->val);
}

sw_error_t
hppe_port_vlan_config_0_get(
		a_uint32_t dev_id,
		union port_vlan_config_0_u *value)
{
	return hppe_reg_get(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_VLAN_CONFIG_0_ADDRESS,
				&value->val);
}

sw_error_t
hppe_port_vlan_config_0_set(
		a_uint32_t dev_id,
		union port_vlan_config_0_u *value)
{
	return hppe_reg_set(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_VLAN_CONFIG_0_ADDRESS,
				value->val);
}

sw_error_t
hppe_port_vlan_config_1_get(
		a_uint32_t dev_id,
		union port_vlan_config_1_u *value)
{
	return hppe_reg_get(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_VLAN_CONFIG_1_ADDRESS,
				&value->val);
}

sw_error_t
hppe_port_vlan_config_1_set(
		a_uint32_t dev_id,
		union port_vlan_config_1_u *value)
{
	return hppe_reg_set(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_VLAN_CONFIG_1_ADDRESS,
				value->val);
}

sw_error_t
hppe_port_vlan_config_2_get(
		a_uint32_t dev_id,
		union port_vlan_config_2_u *value)
{
	return hppe_reg_get(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_VLAN_CONFIG_2_ADDRESS,
				&value->val);
}

sw_error_t
hppe_port_vlan_config_2_set(
		a_uint32_t dev_id,
		union port_vlan_config_2_u *value)
{
	return hppe_reg_set(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_VLAN_CONFIG_2_ADDRESS,
				value->val);
}

sw_error_t
hppe_port_vlan_config_3_get(
		a_uint32_t dev_id,
		union port_vlan_config_3_u *value)
{
	return hppe_reg_get(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_VLAN_CONFIG_3_ADDRESS,
				&value->val);
}

sw_error_t
hppe_port_vlan_config_3_set(
		a_uint32_t dev_id,
		union port_vlan_config_3_u *value)
{
	return hppe_reg_set(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_VLAN_CONFIG_3_ADDRESS,
				value->val);
}

sw_error_t
hppe_port_vlan_config_4_get(
		a_uint32_t dev_id,
		union port_vlan_config_4_u *value)
{
	return hppe_reg_get(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_VLAN_CONFIG_4_ADDRESS,
				&value->val);
}

sw_error_t
hppe_port_vlan_config_4_set(
		a_uint32_t dev_id,
		union port_vlan_config_4_u *value)
{
	return hppe_reg_set(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_VLAN_CONFIG_4_ADDRESS,
				value->val);
}

sw_error_t
hppe_port_vlan_config_5_get(
		a_uint32_t dev_id,
		union port_vlan_config_5_u *value)
{
	return hppe_reg_get(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_VLAN_CONFIG_5_ADDRESS,
				&value->val);
}

sw_error_t
hppe_port_vlan_config_5_set(
		a_uint32_t dev_id,
		union port_vlan_config_5_u *value)
{
	return hppe_reg_set(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_VLAN_CONFIG_5_ADDRESS,
				value->val);
}

sw_error_t
hppe_port_vlan_config_6_get(
		a_uint32_t dev_id,
		union port_vlan_config_6_u *value)
{
	return hppe_reg_get(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_VLAN_CONFIG_6_ADDRESS,
				&value->val);
}

sw_error_t
hppe_port_vlan_config_6_set(
		a_uint32_t dev_id,
		union port_vlan_config_6_u *value)
{
	return hppe_reg_set(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_VLAN_CONFIG_6_ADDRESS,
				value->val);
}

sw_error_t
hppe_port_vlan_config_7_get(
		a_uint32_t dev_id,
		union port_vlan_config_7_u *value)
{
	return hppe_reg_get(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_VLAN_CONFIG_7_ADDRESS,
				&value->val);
}

sw_error_t
hppe_port_vlan_config_7_set(
		a_uint32_t dev_id,
		union port_vlan_config_7_u *value)
{
	return hppe_reg_set(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + PORT_VLAN_CONFIG_7_ADDRESS,
				value->val);
}

sw_error_t
hppe_iv_dbg_addr_get(
		a_uint32_t dev_id,
		union iv_dbg_addr_u *value)
{
	return hppe_reg_get(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + IV_DBG_ADDR_ADDRESS,
				&value->val);
}

sw_error_t
hppe_iv_dbg_addr_set(
		a_uint32_t dev_id,
		union iv_dbg_addr_u *value)
{
	return hppe_reg_set(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + IV_DBG_ADDR_ADDRESS,
				value->val);
}

sw_error_t
hppe_iv_dbg_data_get(
		a_uint32_t dev_id,
		union iv_dbg_data_u *value)
{
	return hppe_reg_get(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + IV_DBG_DATA_ADDRESS,
				&value->val);
}

sw_error_t
hppe_iv_dbg_data_set(
		a_uint32_t dev_id,
		union iv_dbg_data_u *value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_eco_reserve_get(
		a_uint32_t dev_id,
		union eco_reserve_u *value)
{
	return hppe_reg_get(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + ECO_RESERVE_ADDRESS,
				&value->val);
}

sw_error_t
hppe_eco_reserve_set(
		a_uint32_t dev_id,
		union eco_reserve_u *value)
{
	return hppe_reg_set(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + ECO_RESERVE_ADDRESS,
				value->val);
}

sw_error_t
hppe_xlt_rule_tbl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union xlt_rule_tbl_u *value)
{
	return hppe_reg_tbl_get(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + XLT_RULE_TBL_ADDRESS + \
				index * XLT_RULE_TBL_INC,
				value->val,
				3);
}

sw_error_t
hppe_xlt_rule_tbl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union xlt_rule_tbl_u *value)
{
	return hppe_reg_tbl_set(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + XLT_RULE_TBL_ADDRESS + \
				index * XLT_RULE_TBL_INC,
				value->val,
				3);
}

sw_error_t
hppe_xlt_action_tbl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union xlt_action_tbl_u *value)
{
	return hppe_reg_tbl_get(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + XLT_ACTION_TBL_ADDRESS + \
				index * XLT_ACTION_TBL_INC,
				value->val,
				2);
}

sw_error_t
hppe_xlt_action_tbl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union xlt_action_tbl_u *value)
{
	return hppe_reg_tbl_set(
				dev_id,
				INGRESS_VLAN_BASE_ADDR + XLT_ACTION_TBL_ADDRESS + \
				index * XLT_ACTION_TBL_INC,
				value->val,
				2);
}

sw_error_t
hppe_bridge_config_bridge_type_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union bridge_config_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_bridge_config_get(dev_id, &reg_val);
	*value = reg_val.bf.bridge_type;
	return ret;
}

sw_error_t
hppe_bridge_config_bridge_type_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union bridge_config_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_bridge_config_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.bridge_type = value;
	ret = hppe_bridge_config_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_0_port_def_cvid_en_0_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_0_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cvid_en_0;
	return ret;
}

sw_error_t
hppe_port_def_vid_0_port_def_cvid_en_0_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_0_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cvid_en_0 = value;
	ret = hppe_port_def_vid_0_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_0_port_def_svid_en_0_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_0_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_svid_en_0;
	return ret;
}

sw_error_t
hppe_port_def_vid_0_port_def_svid_en_0_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_0_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_svid_en_0 = value;
	ret = hppe_port_def_vid_0_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_0_port_def_cvid_0_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_0_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cvid_0;
	return ret;
}

sw_error_t
hppe_port_def_vid_0_port_def_cvid_0_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_0_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cvid_0 = value;
	ret = hppe_port_def_vid_0_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_0_port_def_svid_0_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_0_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_svid_0;
	return ret;
}

sw_error_t
hppe_port_def_vid_0_port_def_svid_0_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_0_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_svid_0 = value;
	ret = hppe_port_def_vid_0_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_1_port_def_svid_1_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_1_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_svid_1;
	return ret;
}

sw_error_t
hppe_port_def_vid_1_port_def_svid_1_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_1_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_svid_1 = value;
	ret = hppe_port_def_vid_1_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_1_port_def_svid_en_1_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_1_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_svid_en_1;
	return ret;
}

sw_error_t
hppe_port_def_vid_1_port_def_svid_en_1_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_1_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_svid_en_1 = value;
	ret = hppe_port_def_vid_1_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_1_port_def_cvid_en_1_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_1_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cvid_en_1;
	return ret;
}

sw_error_t
hppe_port_def_vid_1_port_def_cvid_en_1_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_1_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cvid_en_1 = value;
	ret = hppe_port_def_vid_1_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_1_port_def_cvid_1_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_1_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cvid_1;
	return ret;
}

sw_error_t
hppe_port_def_vid_1_port_def_cvid_1_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_1_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cvid_1 = value;
	ret = hppe_port_def_vid_1_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_2_port_def_cvid_2_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_2_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cvid_2;
	return ret;
}

sw_error_t
hppe_port_def_vid_2_port_def_cvid_2_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_2_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cvid_2 = value;
	ret = hppe_port_def_vid_2_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_2_port_def_svid_2_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_2_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_svid_2;
	return ret;
}

sw_error_t
hppe_port_def_vid_2_port_def_svid_2_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_2_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_svid_2 = value;
	ret = hppe_port_def_vid_2_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_2_port_def_cvid_en_2_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_2_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cvid_en_2;
	return ret;
}

sw_error_t
hppe_port_def_vid_2_port_def_cvid_en_2_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_2_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cvid_en_2 = value;
	ret = hppe_port_def_vid_2_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_2_port_def_svid_en_2_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_2_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_svid_en_2;
	return ret;
}

sw_error_t
hppe_port_def_vid_2_port_def_svid_en_2_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_2_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_svid_en_2 = value;
	ret = hppe_port_def_vid_2_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_3_port_def_svid_3_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_3_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_svid_3;
	return ret;
}

sw_error_t
hppe_port_def_vid_3_port_def_svid_3_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_3_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_svid_3 = value;
	ret = hppe_port_def_vid_3_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_3_port_def_cvid_3_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_3_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cvid_3;
	return ret;
}

sw_error_t
hppe_port_def_vid_3_port_def_cvid_3_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_3_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cvid_3 = value;
	ret = hppe_port_def_vid_3_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_3_port_def_svid_en_3_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_3_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_svid_en_3;
	return ret;
}

sw_error_t
hppe_port_def_vid_3_port_def_svid_en_3_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_3_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_svid_en_3 = value;
	ret = hppe_port_def_vid_3_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_3_port_def_cvid_en_3_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_3_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cvid_en_3;
	return ret;
}

sw_error_t
hppe_port_def_vid_3_port_def_cvid_en_3_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_3_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cvid_en_3 = value;
	ret = hppe_port_def_vid_3_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_4_port_def_cvid_en_4_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_4_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cvid_en_4;
	return ret;
}

sw_error_t
hppe_port_def_vid_4_port_def_cvid_en_4_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_4_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cvid_en_4 = value;
	ret = hppe_port_def_vid_4_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_4_port_def_svid_en_4_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_4_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_svid_en_4;
	return ret;
}

sw_error_t
hppe_port_def_vid_4_port_def_svid_en_4_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_4_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_svid_en_4 = value;
	ret = hppe_port_def_vid_4_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_4_port_def_svid_4_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_4_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_svid_4;
	return ret;
}

sw_error_t
hppe_port_def_vid_4_port_def_svid_4_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_4_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_svid_4 = value;
	ret = hppe_port_def_vid_4_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_4_port_def_cvid_4_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_4_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cvid_4;
	return ret;
}

sw_error_t
hppe_port_def_vid_4_port_def_cvid_4_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_4_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cvid_4 = value;
	ret = hppe_port_def_vid_4_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_5_port_def_svid_en_5_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_5_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_svid_en_5;
	return ret;
}

sw_error_t
hppe_port_def_vid_5_port_def_svid_en_5_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_5_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_svid_en_5 = value;
	ret = hppe_port_def_vid_5_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_5_port_def_svid_5_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_5_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_svid_5;
	return ret;
}

sw_error_t
hppe_port_def_vid_5_port_def_svid_5_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_5_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_svid_5 = value;
	ret = hppe_port_def_vid_5_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_5_port_def_cvid_en_5_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_5_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cvid_en_5;
	return ret;
}

sw_error_t
hppe_port_def_vid_5_port_def_cvid_en_5_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_5_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cvid_en_5 = value;
	ret = hppe_port_def_vid_5_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_5_port_def_cvid_5_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_5_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cvid_5;
	return ret;
}

sw_error_t
hppe_port_def_vid_5_port_def_cvid_5_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_5_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cvid_5 = value;
	ret = hppe_port_def_vid_5_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_6_port_def_cvid_6_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_6_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cvid_6;
	return ret;
}

sw_error_t
hppe_port_def_vid_6_port_def_cvid_6_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_6_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cvid_6 = value;
	ret = hppe_port_def_vid_6_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_6_port_def_cvid_en_6_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_6_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cvid_en_6;
	return ret;
}

sw_error_t
hppe_port_def_vid_6_port_def_cvid_en_6_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_6_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cvid_en_6 = value;
	ret = hppe_port_def_vid_6_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_6_port_def_svid_6_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_6_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_svid_6;
	return ret;
}

sw_error_t
hppe_port_def_vid_6_port_def_svid_6_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_6_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_svid_6 = value;
	ret = hppe_port_def_vid_6_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_6_port_def_svid_en_6_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_6_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_svid_en_6;
	return ret;
}

sw_error_t
hppe_port_def_vid_6_port_def_svid_en_6_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_6_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_svid_en_6 = value;
	ret = hppe_port_def_vid_6_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_7_port_def_cvid_en_7_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_7_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cvid_en_7;
	return ret;
}

sw_error_t
hppe_port_def_vid_7_port_def_cvid_en_7_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_7_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cvid_en_7 = value;
	ret = hppe_port_def_vid_7_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_7_port_def_svid_en_7_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_7_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_svid_en_7;
	return ret;
}

sw_error_t
hppe_port_def_vid_7_port_def_svid_en_7_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_7_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_svid_en_7 = value;
	ret = hppe_port_def_vid_7_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_7_port_def_svid_7_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_7_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_svid_7;
	return ret;
}

sw_error_t
hppe_port_def_vid_7_port_def_svid_7_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_7_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_svid_7 = value;
	ret = hppe_port_def_vid_7_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_vid_7_port_def_cvid_7_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_vid_7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_7_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cvid_7;
	return ret;
}

sw_error_t
hppe_port_def_vid_7_port_def_cvid_7_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_vid_7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_vid_7_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cvid_7 = value;
	ret = hppe_port_def_vid_7_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_0_port_def_sdei_0_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_0_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_sdei_0;
	return ret;
}

sw_error_t
hppe_port_def_pcp_0_port_def_sdei_0_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_0_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_sdei_0 = value;
	ret = hppe_port_def_pcp_0_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_0_port_def_spcp_0_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_0_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_spcp_0;
	return ret;
}

sw_error_t
hppe_port_def_pcp_0_port_def_spcp_0_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_0_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_spcp_0 = value;
	ret = hppe_port_def_pcp_0_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_0_port_def_cdei_0_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_0_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cdei_0;
	return ret;
}

sw_error_t
hppe_port_def_pcp_0_port_def_cdei_0_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_0_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cdei_0 = value;
	ret = hppe_port_def_pcp_0_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_0_port_def_cpcp_0_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_0_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cpcp_0;
	return ret;
}

sw_error_t
hppe_port_def_pcp_0_port_def_cpcp_0_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_0_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cpcp_0 = value;
	ret = hppe_port_def_pcp_0_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_1_port_def_cpcp_1_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_1_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cpcp_1;
	return ret;
}

sw_error_t
hppe_port_def_pcp_1_port_def_cpcp_1_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_1_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cpcp_1 = value;
	ret = hppe_port_def_pcp_1_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_1_port_def_spcp_1_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_1_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_spcp_1;
	return ret;
}

sw_error_t
hppe_port_def_pcp_1_port_def_spcp_1_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_1_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_spcp_1 = value;
	ret = hppe_port_def_pcp_1_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_1_port_def_cdei_1_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_1_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cdei_1;
	return ret;
}

sw_error_t
hppe_port_def_pcp_1_port_def_cdei_1_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_1_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cdei_1 = value;
	ret = hppe_port_def_pcp_1_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_1_port_def_sdei_1_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_1_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_sdei_1;
	return ret;
}

sw_error_t
hppe_port_def_pcp_1_port_def_sdei_1_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_1_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_sdei_1 = value;
	ret = hppe_port_def_pcp_1_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_2_port_def_cpcp_2_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_2_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cpcp_2;
	return ret;
}

sw_error_t
hppe_port_def_pcp_2_port_def_cpcp_2_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_2_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cpcp_2 = value;
	ret = hppe_port_def_pcp_2_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_2_port_def_spcp_2_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_2_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_spcp_2;
	return ret;
}

sw_error_t
hppe_port_def_pcp_2_port_def_spcp_2_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_2_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_spcp_2 = value;
	ret = hppe_port_def_pcp_2_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_2_port_def_sdei_2_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_2_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_sdei_2;
	return ret;
}

sw_error_t
hppe_port_def_pcp_2_port_def_sdei_2_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_2_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_sdei_2 = value;
	ret = hppe_port_def_pcp_2_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_2_port_def_cdei_2_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_2_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cdei_2;
	return ret;
}

sw_error_t
hppe_port_def_pcp_2_port_def_cdei_2_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_2_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cdei_2 = value;
	ret = hppe_port_def_pcp_2_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_3_port_def_cdei_3_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_3_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cdei_3;
	return ret;
}

sw_error_t
hppe_port_def_pcp_3_port_def_cdei_3_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_3_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cdei_3 = value;
	ret = hppe_port_def_pcp_3_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_3_port_def_sdei_3_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_3_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_sdei_3;
	return ret;
}

sw_error_t
hppe_port_def_pcp_3_port_def_sdei_3_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_3_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_sdei_3 = value;
	ret = hppe_port_def_pcp_3_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_3_port_def_spcp_3_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_3_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_spcp_3;
	return ret;
}

sw_error_t
hppe_port_def_pcp_3_port_def_spcp_3_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_3_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_spcp_3 = value;
	ret = hppe_port_def_pcp_3_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_3_port_def_cpcp_3_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_3_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cpcp_3;
	return ret;
}

sw_error_t
hppe_port_def_pcp_3_port_def_cpcp_3_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_3_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cpcp_3 = value;
	ret = hppe_port_def_pcp_3_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_4_port_def_spcp_4_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_4_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_spcp_4;
	return ret;
}

sw_error_t
hppe_port_def_pcp_4_port_def_spcp_4_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_4_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_spcp_4 = value;
	ret = hppe_port_def_pcp_4_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_4_port_def_sdei_4_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_4_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_sdei_4;
	return ret;
}

sw_error_t
hppe_port_def_pcp_4_port_def_sdei_4_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_4_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_sdei_4 = value;
	ret = hppe_port_def_pcp_4_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_4_port_def_cdei_4_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_4_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cdei_4;
	return ret;
}

sw_error_t
hppe_port_def_pcp_4_port_def_cdei_4_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_4_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cdei_4 = value;
	ret = hppe_port_def_pcp_4_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_4_port_def_cpcp_4_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_4_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cpcp_4;
	return ret;
}

sw_error_t
hppe_port_def_pcp_4_port_def_cpcp_4_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_4_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cpcp_4 = value;
	ret = hppe_port_def_pcp_4_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_5_port_def_cdei_5_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_5_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cdei_5;
	return ret;
}

sw_error_t
hppe_port_def_pcp_5_port_def_cdei_5_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_5_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cdei_5 = value;
	ret = hppe_port_def_pcp_5_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_5_port_def_sdei_5_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_5_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_sdei_5;
	return ret;
}

sw_error_t
hppe_port_def_pcp_5_port_def_sdei_5_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_5_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_sdei_5 = value;
	ret = hppe_port_def_pcp_5_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_5_port_def_cpcp_5_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_5_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cpcp_5;
	return ret;
}

sw_error_t
hppe_port_def_pcp_5_port_def_cpcp_5_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_5_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cpcp_5 = value;
	ret = hppe_port_def_pcp_5_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_5_port_def_spcp_5_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_5_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_spcp_5;
	return ret;
}

sw_error_t
hppe_port_def_pcp_5_port_def_spcp_5_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_5_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_spcp_5 = value;
	ret = hppe_port_def_pcp_5_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_6_port_def_cdei_6_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_6_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cdei_6;
	return ret;
}

sw_error_t
hppe_port_def_pcp_6_port_def_cdei_6_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_6_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cdei_6 = value;
	ret = hppe_port_def_pcp_6_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_6_port_def_spcp_6_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_6_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_spcp_6;
	return ret;
}

sw_error_t
hppe_port_def_pcp_6_port_def_spcp_6_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_6_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_spcp_6 = value;
	ret = hppe_port_def_pcp_6_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_6_port_def_sdei_6_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_6_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_sdei_6;
	return ret;
}

sw_error_t
hppe_port_def_pcp_6_port_def_sdei_6_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_6_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_sdei_6 = value;
	ret = hppe_port_def_pcp_6_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_6_port_def_cpcp_6_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_6_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cpcp_6;
	return ret;
}

sw_error_t
hppe_port_def_pcp_6_port_def_cpcp_6_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_6_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cpcp_6 = value;
	ret = hppe_port_def_pcp_6_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_7_port_def_sdei_7_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_7_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_sdei_7;
	return ret;
}

sw_error_t
hppe_port_def_pcp_7_port_def_sdei_7_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_7_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_sdei_7 = value;
	ret = hppe_port_def_pcp_7_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_7_port_def_spcp_7_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_7_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_spcp_7;
	return ret;
}

sw_error_t
hppe_port_def_pcp_7_port_def_spcp_7_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_7_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_spcp_7 = value;
	ret = hppe_port_def_pcp_7_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_7_port_def_cdei_7_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_7_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cdei_7;
	return ret;
}

sw_error_t
hppe_port_def_pcp_7_port_def_cdei_7_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_7_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cdei_7 = value;
	ret = hppe_port_def_pcp_7_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_def_pcp_7_port_def_cpcp_7_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_def_pcp_7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_7_get(dev_id, &reg_val);
	*value = reg_val.bf.port_def_cpcp_7;
	return ret;
}

sw_error_t
hppe_port_def_pcp_7_port_def_cpcp_7_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_def_pcp_7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_def_pcp_7_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_def_cpcp_7 = value;
	ret = hppe_port_def_pcp_7_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_0_port_in_dei_prop_cmd_0_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_0_get(dev_id, &reg_val);
	*value = reg_val.bf.port_in_dei_prop_cmd_0;
	return ret;
}

sw_error_t
hppe_port_vlan_config_0_port_in_dei_prop_cmd_0_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_0_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_in_dei_prop_cmd_0 = value;
	ret = hppe_port_vlan_config_0_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_0_port_in_pcp_prop_cmd_0_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_0_get(dev_id, &reg_val);
	*value = reg_val.bf.port_in_pcp_prop_cmd_0;
	return ret;
}

sw_error_t
hppe_port_vlan_config_0_port_in_pcp_prop_cmd_0_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_0_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_in_pcp_prop_cmd_0 = value;
	ret = hppe_port_vlan_config_0_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_0_port_untag_fltr_cmd_0_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_0_get(dev_id, &reg_val);
	*value = reg_val.bf.port_untag_fltr_cmd_0;
	return ret;
}

sw_error_t
hppe_port_vlan_config_0_port_untag_fltr_cmd_0_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_0_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_untag_fltr_cmd_0 = value;
	ret = hppe_port_vlan_config_0_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_0_port_in_vlan_fltr_cmd_0_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_0_get(dev_id, &reg_val);
	*value = reg_val.bf.port_in_vlan_fltr_cmd_0;
	return ret;
}

sw_error_t
hppe_port_vlan_config_0_port_in_vlan_fltr_cmd_0_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_0_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_in_vlan_fltr_cmd_0 = value;
	ret = hppe_port_vlan_config_0_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_0_port_pri_tag_fltr_cmd_0_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_0_get(dev_id, &reg_val);
	*value = reg_val.bf.port_pri_tag_fltr_cmd_0;
	return ret;
}

sw_error_t
hppe_port_vlan_config_0_port_pri_tag_fltr_cmd_0_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_0_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_pri_tag_fltr_cmd_0 = value;
	ret = hppe_port_vlan_config_0_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_0_port_vlan_xlt_miss_fwd_cmd_0_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_0_get(dev_id, &reg_val);
	*value = reg_val.bf.port_vlan_xlt_miss_fwd_cmd_0;
	return ret;
}

sw_error_t
hppe_port_vlan_config_0_port_vlan_xlt_miss_fwd_cmd_0_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_0_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_vlan_xlt_miss_fwd_cmd_0 = value;
	ret = hppe_port_vlan_config_0_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_0_port_tag_fltr_cmd_0_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_0_get(dev_id, &reg_val);
	*value = reg_val.bf.port_tag_fltr_cmd_0;
	return ret;
}

sw_error_t
hppe_port_vlan_config_0_port_tag_fltr_cmd_0_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_0_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_tag_fltr_cmd_0 = value;
	ret = hppe_port_vlan_config_0_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_1_port_tag_fltr_cmd_1_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_1_get(dev_id, &reg_val);
	*value = reg_val.bf.port_tag_fltr_cmd_1;
	return ret;
}

sw_error_t
hppe_port_vlan_config_1_port_tag_fltr_cmd_1_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_1_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_tag_fltr_cmd_1 = value;
	ret = hppe_port_vlan_config_1_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_1_port_in_pcp_prop_cmd_1_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_1_get(dev_id, &reg_val);
	*value = reg_val.bf.port_in_pcp_prop_cmd_1;
	return ret;
}

sw_error_t
hppe_port_vlan_config_1_port_in_pcp_prop_cmd_1_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_1_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_in_pcp_prop_cmd_1 = value;
	ret = hppe_port_vlan_config_1_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_1_port_in_vlan_fltr_cmd_1_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_1_get(dev_id, &reg_val);
	*value = reg_val.bf.port_in_vlan_fltr_cmd_1;
	return ret;
}

sw_error_t
hppe_port_vlan_config_1_port_in_vlan_fltr_cmd_1_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_1_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_in_vlan_fltr_cmd_1 = value;
	ret = hppe_port_vlan_config_1_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_1_port_untag_fltr_cmd_1_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_1_get(dev_id, &reg_val);
	*value = reg_val.bf.port_untag_fltr_cmd_1;
	return ret;
}

sw_error_t
hppe_port_vlan_config_1_port_untag_fltr_cmd_1_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_1_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_untag_fltr_cmd_1 = value;
	ret = hppe_port_vlan_config_1_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_1_port_in_dei_prop_cmd_1_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_1_get(dev_id, &reg_val);
	*value = reg_val.bf.port_in_dei_prop_cmd_1;
	return ret;
}

sw_error_t
hppe_port_vlan_config_1_port_in_dei_prop_cmd_1_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_1_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_in_dei_prop_cmd_1 = value;
	ret = hppe_port_vlan_config_1_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_1_port_vlan_xlt_miss_fwd_cmd_1_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_1_get(dev_id, &reg_val);
	*value = reg_val.bf.port_vlan_xlt_miss_fwd_cmd_1;
	return ret;
}

sw_error_t
hppe_port_vlan_config_1_port_vlan_xlt_miss_fwd_cmd_1_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_1_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_vlan_xlt_miss_fwd_cmd_1 = value;
	ret = hppe_port_vlan_config_1_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_1_port_pri_tag_fltr_cmd_1_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_1_get(dev_id, &reg_val);
	*value = reg_val.bf.port_pri_tag_fltr_cmd_1;
	return ret;
}

sw_error_t
hppe_port_vlan_config_1_port_pri_tag_fltr_cmd_1_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_1_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_pri_tag_fltr_cmd_1 = value;
	ret = hppe_port_vlan_config_1_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_2_port_vlan_xlt_miss_fwd_cmd_2_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_2_get(dev_id, &reg_val);
	*value = reg_val.bf.port_vlan_xlt_miss_fwd_cmd_2;
	return ret;
}

sw_error_t
hppe_port_vlan_config_2_port_vlan_xlt_miss_fwd_cmd_2_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_2_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_vlan_xlt_miss_fwd_cmd_2 = value;
	ret = hppe_port_vlan_config_2_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_2_port_in_vlan_fltr_cmd_2_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_2_get(dev_id, &reg_val);
	*value = reg_val.bf.port_in_vlan_fltr_cmd_2;
	return ret;
}

sw_error_t
hppe_port_vlan_config_2_port_in_vlan_fltr_cmd_2_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_2_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_in_vlan_fltr_cmd_2 = value;
	ret = hppe_port_vlan_config_2_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_2_port_pri_tag_fltr_cmd_2_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_2_get(dev_id, &reg_val);
	*value = reg_val.bf.port_pri_tag_fltr_cmd_2;
	return ret;
}

sw_error_t
hppe_port_vlan_config_2_port_pri_tag_fltr_cmd_2_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_2_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_pri_tag_fltr_cmd_2 = value;
	ret = hppe_port_vlan_config_2_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_2_port_in_pcp_prop_cmd_2_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_2_get(dev_id, &reg_val);
	*value = reg_val.bf.port_in_pcp_prop_cmd_2;
	return ret;
}

sw_error_t
hppe_port_vlan_config_2_port_in_pcp_prop_cmd_2_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_2_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_in_pcp_prop_cmd_2 = value;
	ret = hppe_port_vlan_config_2_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_2_port_untag_fltr_cmd_2_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_2_get(dev_id, &reg_val);
	*value = reg_val.bf.port_untag_fltr_cmd_2;
	return ret;
}

sw_error_t
hppe_port_vlan_config_2_port_untag_fltr_cmd_2_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_2_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_untag_fltr_cmd_2 = value;
	ret = hppe_port_vlan_config_2_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_2_port_in_dei_prop_cmd_2_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_2_get(dev_id, &reg_val);
	*value = reg_val.bf.port_in_dei_prop_cmd_2;
	return ret;
}

sw_error_t
hppe_port_vlan_config_2_port_in_dei_prop_cmd_2_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_2_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_in_dei_prop_cmd_2 = value;
	ret = hppe_port_vlan_config_2_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_2_port_tag_fltr_cmd_2_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_2_get(dev_id, &reg_val);
	*value = reg_val.bf.port_tag_fltr_cmd_2;
	return ret;
}

sw_error_t
hppe_port_vlan_config_2_port_tag_fltr_cmd_2_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_2_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_tag_fltr_cmd_2 = value;
	ret = hppe_port_vlan_config_2_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_3_port_in_dei_prop_cmd_3_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_3_get(dev_id, &reg_val);
	*value = reg_val.bf.port_in_dei_prop_cmd_3;
	return ret;
}

sw_error_t
hppe_port_vlan_config_3_port_in_dei_prop_cmd_3_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_3_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_in_dei_prop_cmd_3 = value;
	ret = hppe_port_vlan_config_3_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_3_port_pri_tag_fltr_cmd_3_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_3_get(dev_id, &reg_val);
	*value = reg_val.bf.port_pri_tag_fltr_cmd_3;
	return ret;
}

sw_error_t
hppe_port_vlan_config_3_port_pri_tag_fltr_cmd_3_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_3_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_pri_tag_fltr_cmd_3 = value;
	ret = hppe_port_vlan_config_3_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_3_port_in_vlan_fltr_cmd_3_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_3_get(dev_id, &reg_val);
	*value = reg_val.bf.port_in_vlan_fltr_cmd_3;
	return ret;
}

sw_error_t
hppe_port_vlan_config_3_port_in_vlan_fltr_cmd_3_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_3_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_in_vlan_fltr_cmd_3 = value;
	ret = hppe_port_vlan_config_3_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_3_port_tag_fltr_cmd_3_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_3_get(dev_id, &reg_val);
	*value = reg_val.bf.port_tag_fltr_cmd_3;
	return ret;
}

sw_error_t
hppe_port_vlan_config_3_port_tag_fltr_cmd_3_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_3_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_tag_fltr_cmd_3 = value;
	ret = hppe_port_vlan_config_3_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_3_port_untag_fltr_cmd_3_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_3_get(dev_id, &reg_val);
	*value = reg_val.bf.port_untag_fltr_cmd_3;
	return ret;
}

sw_error_t
hppe_port_vlan_config_3_port_untag_fltr_cmd_3_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_3_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_untag_fltr_cmd_3 = value;
	ret = hppe_port_vlan_config_3_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_3_port_in_pcp_prop_cmd_3_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_3_get(dev_id, &reg_val);
	*value = reg_val.bf.port_in_pcp_prop_cmd_3;
	return ret;
}

sw_error_t
hppe_port_vlan_config_3_port_in_pcp_prop_cmd_3_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_3_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_in_pcp_prop_cmd_3 = value;
	ret = hppe_port_vlan_config_3_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_3_port_vlan_xlt_miss_fwd_cmd_3_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_3_get(dev_id, &reg_val);
	*value = reg_val.bf.port_vlan_xlt_miss_fwd_cmd_3;
	return ret;
}

sw_error_t
hppe_port_vlan_config_3_port_vlan_xlt_miss_fwd_cmd_3_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_3_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_vlan_xlt_miss_fwd_cmd_3 = value;
	ret = hppe_port_vlan_config_3_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_4_port_in_pcp_prop_cmd_4_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_4_get(dev_id, &reg_val);
	*value = reg_val.bf.port_in_pcp_prop_cmd_4;
	return ret;
}

sw_error_t
hppe_port_vlan_config_4_port_in_pcp_prop_cmd_4_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_4_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_in_pcp_prop_cmd_4 = value;
	ret = hppe_port_vlan_config_4_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_4_port_untag_fltr_cmd_4_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_4_get(dev_id, &reg_val);
	*value = reg_val.bf.port_untag_fltr_cmd_4;
	return ret;
}

sw_error_t
hppe_port_vlan_config_4_port_untag_fltr_cmd_4_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_4_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_untag_fltr_cmd_4 = value;
	ret = hppe_port_vlan_config_4_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_4_port_in_vlan_fltr_cmd_4_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_4_get(dev_id, &reg_val);
	*value = reg_val.bf.port_in_vlan_fltr_cmd_4;
	return ret;
}

sw_error_t
hppe_port_vlan_config_4_port_in_vlan_fltr_cmd_4_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_4_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_in_vlan_fltr_cmd_4 = value;
	ret = hppe_port_vlan_config_4_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_4_port_vlan_xlt_miss_fwd_cmd_4_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_4_get(dev_id, &reg_val);
	*value = reg_val.bf.port_vlan_xlt_miss_fwd_cmd_4;
	return ret;
}

sw_error_t
hppe_port_vlan_config_4_port_vlan_xlt_miss_fwd_cmd_4_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_4_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_vlan_xlt_miss_fwd_cmd_4 = value;
	ret = hppe_port_vlan_config_4_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_4_port_tag_fltr_cmd_4_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_4_get(dev_id, &reg_val);
	*value = reg_val.bf.port_tag_fltr_cmd_4;
	return ret;
}

sw_error_t
hppe_port_vlan_config_4_port_tag_fltr_cmd_4_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_4_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_tag_fltr_cmd_4 = value;
	ret = hppe_port_vlan_config_4_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_4_port_pri_tag_fltr_cmd_4_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_4_get(dev_id, &reg_val);
	*value = reg_val.bf.port_pri_tag_fltr_cmd_4;
	return ret;
}

sw_error_t
hppe_port_vlan_config_4_port_pri_tag_fltr_cmd_4_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_4_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_pri_tag_fltr_cmd_4 = value;
	ret = hppe_port_vlan_config_4_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_4_port_in_dei_prop_cmd_4_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_4_get(dev_id, &reg_val);
	*value = reg_val.bf.port_in_dei_prop_cmd_4;
	return ret;
}

sw_error_t
hppe_port_vlan_config_4_port_in_dei_prop_cmd_4_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_4_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_in_dei_prop_cmd_4 = value;
	ret = hppe_port_vlan_config_4_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_5_port_in_vlan_fltr_cmd_5_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_5_get(dev_id, &reg_val);
	*value = reg_val.bf.port_in_vlan_fltr_cmd_5;
	return ret;
}

sw_error_t
hppe_port_vlan_config_5_port_in_vlan_fltr_cmd_5_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_5_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_in_vlan_fltr_cmd_5 = value;
	ret = hppe_port_vlan_config_5_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_5_port_tag_fltr_cmd_5_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_5_get(dev_id, &reg_val);
	*value = reg_val.bf.port_tag_fltr_cmd_5;
	return ret;
}

sw_error_t
hppe_port_vlan_config_5_port_tag_fltr_cmd_5_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_5_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_tag_fltr_cmd_5 = value;
	ret = hppe_port_vlan_config_5_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_5_port_in_dei_prop_cmd_5_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_5_get(dev_id, &reg_val);
	*value = reg_val.bf.port_in_dei_prop_cmd_5;
	return ret;
}

sw_error_t
hppe_port_vlan_config_5_port_in_dei_prop_cmd_5_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_5_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_in_dei_prop_cmd_5 = value;
	ret = hppe_port_vlan_config_5_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_5_port_in_pcp_prop_cmd_5_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_5_get(dev_id, &reg_val);
	*value = reg_val.bf.port_in_pcp_prop_cmd_5;
	return ret;
}

sw_error_t
hppe_port_vlan_config_5_port_in_pcp_prop_cmd_5_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_5_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_in_pcp_prop_cmd_5 = value;
	ret = hppe_port_vlan_config_5_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_5_port_pri_tag_fltr_cmd_5_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_5_get(dev_id, &reg_val);
	*value = reg_val.bf.port_pri_tag_fltr_cmd_5;
	return ret;
}

sw_error_t
hppe_port_vlan_config_5_port_pri_tag_fltr_cmd_5_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_5_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_pri_tag_fltr_cmd_5 = value;
	ret = hppe_port_vlan_config_5_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_5_port_vlan_xlt_miss_fwd_cmd_5_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_5_get(dev_id, &reg_val);
	*value = reg_val.bf.port_vlan_xlt_miss_fwd_cmd_5;
	return ret;
}

sw_error_t
hppe_port_vlan_config_5_port_vlan_xlt_miss_fwd_cmd_5_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_5_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_vlan_xlt_miss_fwd_cmd_5 = value;
	ret = hppe_port_vlan_config_5_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_5_port_untag_fltr_cmd_5_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_5_get(dev_id, &reg_val);
	*value = reg_val.bf.port_untag_fltr_cmd_5;
	return ret;
}

sw_error_t
hppe_port_vlan_config_5_port_untag_fltr_cmd_5_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_5_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_untag_fltr_cmd_5 = value;
	ret = hppe_port_vlan_config_5_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_6_port_in_vlan_fltr_cmd_6_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_6_get(dev_id, &reg_val);
	*value = reg_val.bf.port_in_vlan_fltr_cmd_6;
	return ret;
}

sw_error_t
hppe_port_vlan_config_6_port_in_vlan_fltr_cmd_6_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_6_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_in_vlan_fltr_cmd_6 = value;
	ret = hppe_port_vlan_config_6_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_6_port_untag_fltr_cmd_6_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_6_get(dev_id, &reg_val);
	*value = reg_val.bf.port_untag_fltr_cmd_6;
	return ret;
}

sw_error_t
hppe_port_vlan_config_6_port_untag_fltr_cmd_6_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_6_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_untag_fltr_cmd_6 = value;
	ret = hppe_port_vlan_config_6_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_6_port_tag_fltr_cmd_6_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_6_get(dev_id, &reg_val);
	*value = reg_val.bf.port_tag_fltr_cmd_6;
	return ret;
}

sw_error_t
hppe_port_vlan_config_6_port_tag_fltr_cmd_6_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_6_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_tag_fltr_cmd_6 = value;
	ret = hppe_port_vlan_config_6_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_6_port_pri_tag_fltr_cmd_6_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_6_get(dev_id, &reg_val);
	*value = reg_val.bf.port_pri_tag_fltr_cmd_6;
	return ret;
}

sw_error_t
hppe_port_vlan_config_6_port_pri_tag_fltr_cmd_6_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_6_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_pri_tag_fltr_cmd_6 = value;
	ret = hppe_port_vlan_config_6_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_6_port_vlan_xlt_miss_fwd_cmd_6_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_6_get(dev_id, &reg_val);
	*value = reg_val.bf.port_vlan_xlt_miss_fwd_cmd_6;
	return ret;
}

sw_error_t
hppe_port_vlan_config_6_port_vlan_xlt_miss_fwd_cmd_6_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_6_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_vlan_xlt_miss_fwd_cmd_6 = value;
	ret = hppe_port_vlan_config_6_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_6_port_in_dei_prop_cmd_6_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_6_get(dev_id, &reg_val);
	*value = reg_val.bf.port_in_dei_prop_cmd_6;
	return ret;
}

sw_error_t
hppe_port_vlan_config_6_port_in_dei_prop_cmd_6_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_6_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_in_dei_prop_cmd_6 = value;
	ret = hppe_port_vlan_config_6_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_6_port_in_pcp_prop_cmd_6_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_6_get(dev_id, &reg_val);
	*value = reg_val.bf.port_in_pcp_prop_cmd_6;
	return ret;
}

sw_error_t
hppe_port_vlan_config_6_port_in_pcp_prop_cmd_6_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_6_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_in_pcp_prop_cmd_6 = value;
	ret = hppe_port_vlan_config_6_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_7_port_vlan_xlt_miss_fwd_cmd_7_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_7_get(dev_id, &reg_val);
	*value = reg_val.bf.port_vlan_xlt_miss_fwd_cmd_7;
	return ret;
}

sw_error_t
hppe_port_vlan_config_7_port_vlan_xlt_miss_fwd_cmd_7_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_7_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_vlan_xlt_miss_fwd_cmd_7 = value;
	ret = hppe_port_vlan_config_7_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_7_port_tag_fltr_cmd_7_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_7_get(dev_id, &reg_val);
	*value = reg_val.bf.port_tag_fltr_cmd_7;
	return ret;
}

sw_error_t
hppe_port_vlan_config_7_port_tag_fltr_cmd_7_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_7_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_tag_fltr_cmd_7 = value;
	ret = hppe_port_vlan_config_7_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_7_port_untag_fltr_cmd_7_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_7_get(dev_id, &reg_val);
	*value = reg_val.bf.port_untag_fltr_cmd_7;
	return ret;
}

sw_error_t
hppe_port_vlan_config_7_port_untag_fltr_cmd_7_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_7_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_untag_fltr_cmd_7 = value;
	ret = hppe_port_vlan_config_7_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_7_port_in_dei_prop_cmd_7_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_7_get(dev_id, &reg_val);
	*value = reg_val.bf.port_in_dei_prop_cmd_7;
	return ret;
}

sw_error_t
hppe_port_vlan_config_7_port_in_dei_prop_cmd_7_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_7_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_in_dei_prop_cmd_7 = value;
	ret = hppe_port_vlan_config_7_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_7_port_in_pcp_prop_cmd_7_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_7_get(dev_id, &reg_val);
	*value = reg_val.bf.port_in_pcp_prop_cmd_7;
	return ret;
}

sw_error_t
hppe_port_vlan_config_7_port_in_pcp_prop_cmd_7_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_7_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_in_pcp_prop_cmd_7 = value;
	ret = hppe_port_vlan_config_7_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_7_port_pri_tag_fltr_cmd_7_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_7_get(dev_id, &reg_val);
	*value = reg_val.bf.port_pri_tag_fltr_cmd_7;
	return ret;
}

sw_error_t
hppe_port_vlan_config_7_port_pri_tag_fltr_cmd_7_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_7_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_pri_tag_fltr_cmd_7 = value;
	ret = hppe_port_vlan_config_7_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_port_vlan_config_7_port_in_vlan_fltr_cmd_7_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union port_vlan_config_7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_7_get(dev_id, &reg_val);
	*value = reg_val.bf.port_in_vlan_fltr_cmd_7;
	return ret;
}

sw_error_t
hppe_port_vlan_config_7_port_in_vlan_fltr_cmd_7_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union port_vlan_config_7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_port_vlan_config_7_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_in_vlan_fltr_cmd_7 = value;
	ret = hppe_port_vlan_config_7_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_iv_dbg_addr_dbg_addr_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union iv_dbg_addr_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_iv_dbg_addr_get(dev_id, &reg_val);
	*value = reg_val.bf.dbg_addr;
	return ret;
}

sw_error_t
hppe_iv_dbg_addr_dbg_addr_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union iv_dbg_addr_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_iv_dbg_addr_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.dbg_addr = value;
	ret = hppe_iv_dbg_addr_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_iv_dbg_data_dbg_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union iv_dbg_data_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_iv_dbg_data_get(dev_id, &reg_val);
	*value = reg_val.bf.dbg_data;
	return ret;
}

sw_error_t
hppe_iv_dbg_data_dbg_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_eco_reserve_eco_res_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union eco_reserve_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_eco_reserve_get(dev_id, &reg_val);
	*value = reg_val.bf.eco_res;
	return ret;
}

sw_error_t
hppe_eco_reserve_eco_res_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union eco_reserve_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_eco_reserve_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.eco_res = value;
	ret = hppe_eco_reserve_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_ckey_vid_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.ckey_vid;
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_ckey_vid_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.ckey_vid = value;
	ret = hppe_xlt_rule_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_frm_type_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.frm_type;
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_frm_type_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.frm_type = value;
	ret = hppe_xlt_rule_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_prot_value_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.prot_value_1 << 7 | \
		reg_val.bf.prot_value_0;
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_prot_value_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.prot_value_1 = value >> 7;
	reg_val.bf.prot_value_0 = value & (((a_uint64_t)1<<7)-1);
	ret = hppe_xlt_rule_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_valid_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.valid;
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_valid_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.valid = value;
	ret = hppe_xlt_rule_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_frm_type_incl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.frm_type_incl;
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_frm_type_incl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.frm_type_incl = value;
	ret = hppe_xlt_rule_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_ckey_dei_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.ckey_dei;
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_ckey_dei_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.ckey_dei = value;
	ret = hppe_xlt_rule_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_skey_dei_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.skey_dei;
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_skey_dei_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.skey_dei = value;
	ret = hppe_xlt_rule_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_skey_pcp_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.skey_pcp;
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_skey_pcp_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.skey_pcp = value;
	ret = hppe_xlt_rule_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_ckey_pcp_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.ckey_pcp;
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_ckey_pcp_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.ckey_pcp = value;
	ret = hppe_xlt_rule_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_ckey_vid_incl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.ckey_vid_incl;
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_ckey_vid_incl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.ckey_vid_incl = value;
	ret = hppe_xlt_rule_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_ckey_dei_incl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.ckey_dei_incl;
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_ckey_dei_incl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.ckey_dei_incl = value;
	ret = hppe_xlt_rule_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_port_bitmap_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.port_bitmap;
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_port_bitmap_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.port_bitmap = value;
	ret = hppe_xlt_rule_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_prot_incl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.prot_incl;
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_prot_incl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.prot_incl = value;
	ret = hppe_xlt_rule_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_skey_pcp_incl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.skey_pcp_incl;
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_skey_pcp_incl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.skey_pcp_incl = value;
	ret = hppe_xlt_rule_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_ckey_fmt_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.ckey_fmt_1 << 1 | \
		reg_val.bf.ckey_fmt_0;
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_ckey_fmt_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.ckey_fmt_1 = value >> 1;
	reg_val.bf.ckey_fmt_0 = value & (((a_uint64_t)1<<1)-1);
	ret = hppe_xlt_rule_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_skey_vid_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.skey_vid;
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_skey_vid_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.skey_vid = value;
	ret = hppe_xlt_rule_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_skey_fmt_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.skey_fmt;
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_skey_fmt_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.skey_fmt = value;
	ret = hppe_xlt_rule_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_ckey_pcp_incl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.ckey_pcp_incl;
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_ckey_pcp_incl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.ckey_pcp_incl = value;
	ret = hppe_xlt_rule_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_skey_dei_incl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.skey_dei_incl;
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_skey_dei_incl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.skey_dei_incl = value;
	ret = hppe_xlt_rule_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_skey_vid_incl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.skey_vid_incl;
	return ret;
}

sw_error_t
hppe_xlt_rule_tbl_skey_vid_incl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_rule_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_rule_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.skey_vid_incl = value;
	ret = hppe_xlt_rule_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_dei_swap_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.dei_swap_cmd;
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_dei_swap_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.dei_swap_cmd = value;
	ret = hppe_xlt_action_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_xlt_cvid_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.xlt_cvid;
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_xlt_cvid_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.xlt_cvid = value;
	ret = hppe_xlt_action_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_xlt_cpcp_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.xlt_cpcp;
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_xlt_cpcp_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.xlt_cpcp = value;
	ret = hppe_xlt_action_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_xlt_spcp_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.xlt_spcp_cmd;
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_xlt_spcp_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.xlt_spcp_cmd = value;
	ret = hppe_xlt_action_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_xlt_sdei_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.xlt_sdei_cmd;
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_xlt_sdei_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.xlt_sdei_cmd = value;
	ret = hppe_xlt_action_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_xlt_cvid_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.xlt_cvid_cmd;
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_xlt_cvid_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.xlt_cvid_cmd = value;
	ret = hppe_xlt_action_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_vsi_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.vsi;
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_vsi_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.vsi = value;
	ret = hppe_xlt_action_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_xlt_spcp_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.xlt_spcp_1 << 1 | \
		reg_val.bf.xlt_spcp_0;
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_xlt_spcp_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.xlt_spcp_1 = value >> 1;
	reg_val.bf.xlt_spcp_0 = value & (((a_uint64_t)1<<1)-1);
	ret = hppe_xlt_action_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_counter_id_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.counter_id;
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_counter_id_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.counter_id = value;
	ret = hppe_xlt_action_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_vid_swap_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.vid_swap_cmd;
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_vid_swap_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.vid_swap_cmd = value;
	ret = hppe_xlt_action_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_xlt_sdei_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.xlt_sdei;
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_xlt_sdei_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.xlt_sdei = value;
	ret = hppe_xlt_action_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_counter_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.counter_en;
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_counter_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.counter_en = value;
	ret = hppe_xlt_action_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_xlt_svid_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.xlt_svid_cmd;
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_xlt_svid_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.xlt_svid_cmd = value;
	ret = hppe_xlt_action_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_xlt_svid_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.xlt_svid;
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_xlt_svid_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.xlt_svid = value;
	ret = hppe_xlt_action_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_vsi_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.vsi_cmd;
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_vsi_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.vsi_cmd = value;
	ret = hppe_xlt_action_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_xlt_cpcp_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.xlt_cpcp_cmd;
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_xlt_cpcp_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.xlt_cpcp_cmd = value;
	ret = hppe_xlt_action_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_xlt_cdei_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.xlt_cdei_cmd;
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_xlt_cdei_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.xlt_cdei_cmd = value;
	ret = hppe_xlt_action_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_pcp_swap_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.pcp_swap_cmd;
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_pcp_swap_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.pcp_swap_cmd = value;
	ret = hppe_xlt_action_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_xlt_cdei_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.xlt_cdei;
	return ret;
}

sw_error_t
hppe_xlt_action_tbl_xlt_cdei_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union xlt_action_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_xlt_action_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.xlt_cdei = value;
	ret = hppe_xlt_action_tbl_set(dev_id, index, &reg_val);
	return ret;
}

