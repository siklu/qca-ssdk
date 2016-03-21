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
#include "hppe_flow_reg.h"
#include "hppe_flow.h"

sw_error_t
hppe_flow_ctrl0_get(
		a_uint32_t dev_id,
		union flow_ctrl0_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_CTRL0_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_ctrl0_set(
		a_uint32_t dev_id,
		union flow_ctrl0_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_CTRL0_ADDRESS,
				value->val);
}

sw_error_t
hppe_flow_ctrl1_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union flow_ctrl1_u *value)
{
	if (index >= FLOW_CTRL1_MAX_ENTRY)
		return SW_OUT_OF_RANGE;
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_CTRL1_ADDRESS + \
				index * FLOW_CTRL1_INC,
				&value->val);
}

sw_error_t
hppe_flow_ctrl1_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union flow_ctrl1_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_CTRL1_ADDRESS + \
				index * FLOW_CTRL1_INC,
				value->val);
}

sw_error_t
hppe_in_pub_ip_addr_tbl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union in_pub_ip_addr_tbl_u *value)
{
	if (index >= IN_PUB_IP_ADDR_TBL_MAX_ENTRY)
		return SW_OUT_OF_RANGE;
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_PUB_IP_ADDR_TBL_ADDRESS + \
				index * IN_PUB_IP_ADDR_TBL_INC,
				&value->val);
}

sw_error_t
hppe_in_pub_ip_addr_tbl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union in_pub_ip_addr_tbl_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + IN_PUB_IP_ADDR_TBL_ADDRESS + \
				index * IN_PUB_IP_ADDR_TBL_INC,
				value->val);
}

sw_error_t
hppe_in_flow_tbl_op_get(
		a_uint32_t dev_id,
		union in_flow_tbl_op_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_OP_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_tbl_op_set(
		a_uint32_t dev_id,
		union in_flow_tbl_op_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_OP_ADDRESS,
				value->val);
}

sw_error_t
hppe_in_flow_host_tbl_op_get(
		a_uint32_t dev_id,
		union in_flow_host_tbl_op_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_HOST_TBL_OP_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_host_tbl_op_set(
		a_uint32_t dev_id,
		union in_flow_host_tbl_op_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_HOST_TBL_OP_ADDRESS,
				value->val);
}

sw_error_t
hppe_in_flow_tbl_op_data0_get(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data0_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_OP_DATA0_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_tbl_op_data0_set(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data0_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_OP_DATA0_ADDRESS,
				value->val);
}

sw_error_t
hppe_in_flow_tbl_op_data1_get(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data1_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_OP_DATA1_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_tbl_op_data1_set(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data1_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_OP_DATA1_ADDRESS,
				value->val);
}

sw_error_t
hppe_in_flow_tbl_op_data2_get(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data2_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_OP_DATA2_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_tbl_op_data2_set(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data2_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_OP_DATA2_ADDRESS,
				value->val);
}

sw_error_t
hppe_in_flow_tbl_op_data3_get(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data3_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_OP_DATA3_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_tbl_op_data3_set(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data3_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_OP_DATA3_ADDRESS,
				value->val);
}

sw_error_t
hppe_in_flow_tbl_op_data4_get(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data4_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_OP_DATA4_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_tbl_op_data4_set(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data4_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_OP_DATA4_ADDRESS,
				value->val);
}

sw_error_t
hppe_in_flow_tbl_op_data5_get(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data5_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_OP_DATA5_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_tbl_op_data5_set(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data5_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_OP_DATA5_ADDRESS,
				value->val);
}

sw_error_t
hppe_in_flow_tbl_op_data6_get(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data6_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_OP_DATA6_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_tbl_op_data6_set(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data6_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_OP_DATA6_ADDRESS,
				value->val);
}

sw_error_t
hppe_in_flow_tbl_op_data7_get(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data7_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_OP_DATA7_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_tbl_op_data7_set(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data7_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_OP_DATA7_ADDRESS,
				value->val);
}

sw_error_t
hppe_in_flow_tbl_op_data8_get(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data8_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_OP_DATA8_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_tbl_op_data8_set(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data8_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_OP_DATA8_ADDRESS,
				value->val);
}

sw_error_t
hppe_flow_host_tbl_op_data0_get(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data0_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_OP_DATA0_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_op_data0_set(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data0_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_OP_DATA0_ADDRESS,
				value->val);
}

sw_error_t
hppe_flow_host_tbl_op_data1_get(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data1_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_OP_DATA1_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_op_data1_set(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data1_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_OP_DATA1_ADDRESS,
				value->val);
}

sw_error_t
hppe_flow_host_tbl_op_data2_get(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data2_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_OP_DATA2_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_op_data2_set(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data2_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_OP_DATA2_ADDRESS,
				value->val);
}

sw_error_t
hppe_flow_host_tbl_op_data3_get(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data3_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_OP_DATA3_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_op_data3_set(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data3_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_OP_DATA3_ADDRESS,
				value->val);
}

sw_error_t
hppe_flow_host_tbl_op_data4_get(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data4_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_OP_DATA4_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_op_data4_set(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data4_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_OP_DATA4_ADDRESS,
				value->val);
}

sw_error_t
hppe_flow_host_tbl_op_data5_get(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data5_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_OP_DATA5_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_op_data5_set(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data5_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_OP_DATA5_ADDRESS,
				value->val);
}

sw_error_t
hppe_flow_host_tbl_op_data6_get(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data6_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_OP_DATA6_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_op_data6_set(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data6_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_OP_DATA6_ADDRESS,
				value->val);
}

sw_error_t
hppe_flow_host_tbl_op_data7_get(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data7_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_OP_DATA7_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_op_data7_set(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data7_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_OP_DATA7_ADDRESS,
				value->val);
}

sw_error_t
hppe_flow_host_tbl_op_data8_get(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data8_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_OP_DATA8_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_op_data8_set(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data8_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_OP_DATA8_ADDRESS,
				value->val);
}

sw_error_t
hppe_flow_host_tbl_op_data9_get(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data9_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_OP_DATA9_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_op_data9_set(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data9_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_OP_DATA9_ADDRESS,
				value->val);
}

sw_error_t
hppe_in_flow_tbl_op_rslt_get(
		a_uint32_t dev_id,
		union in_flow_tbl_op_rslt_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_OP_RSLT_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_tbl_op_rslt_set(
		a_uint32_t dev_id,
		union in_flow_tbl_op_rslt_u *value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_flow_host_tbl_op_rslt_get(
		a_uint32_t dev_id,
		union flow_host_tbl_op_rslt_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_OP_RSLT_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_op_rslt_set(
		a_uint32_t dev_id,
		union flow_host_tbl_op_rslt_u *value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_in_flow_tbl_rd_op_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_RD_OP_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_tbl_rd_op_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_RD_OP_ADDRESS,
				value->val);
}

sw_error_t
hppe_in_flow_host_tbl_rd_op_get(
		a_uint32_t dev_id,
		union in_flow_host_tbl_rd_op_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_HOST_TBL_RD_OP_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_host_tbl_rd_op_set(
		a_uint32_t dev_id,
		union in_flow_host_tbl_rd_op_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_HOST_TBL_RD_OP_ADDRESS,
				value->val);
}

sw_error_t
hppe_in_flow_tbl_rd_op_data0_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data0_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_RD_OP_DATA0_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_tbl_rd_op_data0_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data0_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_RD_OP_DATA0_ADDRESS,
				value->val);
}

sw_error_t
hppe_in_flow_tbl_rd_op_data1_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data1_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_RD_OP_DATA1_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_tbl_rd_op_data1_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data1_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_RD_OP_DATA1_ADDRESS,
				value->val);
}

sw_error_t
hppe_in_flow_tbl_rd_op_data2_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data2_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_RD_OP_DATA2_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_tbl_rd_op_data2_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data2_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_RD_OP_DATA2_ADDRESS,
				value->val);
}

sw_error_t
hppe_in_flow_tbl_rd_op_data3_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data3_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_RD_OP_DATA3_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_tbl_rd_op_data3_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data3_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_RD_OP_DATA3_ADDRESS,
				value->val);
}

sw_error_t
hppe_in_flow_tbl_rd_op_data4_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data4_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_RD_OP_DATA4_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_tbl_rd_op_data4_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data4_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_RD_OP_DATA4_ADDRESS,
				value->val);
}

sw_error_t
hppe_in_flow_tbl_rd_op_data5_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data5_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_RD_OP_DATA5_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_tbl_rd_op_data5_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data5_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_RD_OP_DATA5_ADDRESS,
				value->val);
}

sw_error_t
hppe_in_flow_tbl_rd_op_data6_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data6_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_RD_OP_DATA6_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_tbl_rd_op_data6_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data6_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_RD_OP_DATA6_ADDRESS,
				value->val);
}

sw_error_t
hppe_in_flow_tbl_rd_op_data7_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data7_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_RD_OP_DATA7_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_tbl_rd_op_data7_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data7_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_RD_OP_DATA7_ADDRESS,
				value->val);
}

sw_error_t
hppe_in_flow_tbl_rd_op_data8_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data8_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_RD_OP_DATA8_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_tbl_rd_op_data8_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data8_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_RD_OP_DATA8_ADDRESS,
				value->val);
}

sw_error_t
hppe_flow_host_tbl_rd_op_data0_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data0_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_RD_OP_DATA0_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_rd_op_data0_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data0_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_RD_OP_DATA0_ADDRESS,
				value->val);
}

sw_error_t
hppe_flow_host_tbl_rd_op_data1_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data1_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_RD_OP_DATA1_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_rd_op_data1_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data1_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_RD_OP_DATA1_ADDRESS,
				value->val);
}

sw_error_t
hppe_flow_host_tbl_rd_op_data2_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data2_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_RD_OP_DATA2_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_rd_op_data2_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data2_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_RD_OP_DATA2_ADDRESS,
				value->val);
}

sw_error_t
hppe_flow_host_tbl_rd_op_data3_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data3_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_RD_OP_DATA3_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_rd_op_data3_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data3_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_RD_OP_DATA3_ADDRESS,
				value->val);
}

sw_error_t
hppe_flow_host_tbl_rd_op_data4_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data4_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_RD_OP_DATA4_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_rd_op_data4_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data4_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_RD_OP_DATA4_ADDRESS,
				value->val);
}

sw_error_t
hppe_flow_host_tbl_rd_op_data5_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data5_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_RD_OP_DATA5_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_rd_op_data5_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data5_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_RD_OP_DATA5_ADDRESS,
				value->val);
}

sw_error_t
hppe_flow_host_tbl_rd_op_data6_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data6_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_RD_OP_DATA6_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_rd_op_data6_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data6_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_RD_OP_DATA6_ADDRESS,
				value->val);
}

sw_error_t
hppe_flow_host_tbl_rd_op_data7_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data7_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_RD_OP_DATA7_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_rd_op_data7_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data7_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_RD_OP_DATA7_ADDRESS,
				value->val);
}

sw_error_t
hppe_flow_host_tbl_rd_op_data8_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data8_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_RD_OP_DATA8_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_rd_op_data8_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data8_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_RD_OP_DATA8_ADDRESS,
				value->val);
}

sw_error_t
hppe_flow_host_tbl_rd_op_data9_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data9_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_RD_OP_DATA9_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_rd_op_data9_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data9_u *value)
{
	return hppe_reg_set(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_RD_OP_DATA9_ADDRESS,
				value->val);
}

sw_error_t
hppe_in_flow_tbl_rd_op_rslt_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_rslt_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_RD_OP_RSLT_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_tbl_rd_op_rslt_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_rslt_u *value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_flow_host_tbl_rd_op_rslt_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_rslt_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_RD_OP_RSLT_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_rd_op_rslt_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_rslt_u *value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data0_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data0_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_RD_RSLT_DATA0_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data0_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data0_u *value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data1_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data1_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_RD_RSLT_DATA1_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data1_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data1_u *value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data2_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data2_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_RD_RSLT_DATA2_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data2_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data2_u *value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data3_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data3_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_RD_RSLT_DATA3_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data3_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data3_u *value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data4_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data4_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_RD_RSLT_DATA4_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data4_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data4_u *value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data5_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data5_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_RD_RSLT_DATA5_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data5_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data5_u *value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data6_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data6_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_RD_RSLT_DATA6_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data6_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data6_u *value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data7_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data7_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_RD_RSLT_DATA7_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data7_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data7_u *value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data8_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data8_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_RD_RSLT_DATA8_ADDRESS,
				&value->val);
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data8_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data8_u *value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data0_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data0_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_RD_RSLT_DATA0_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data0_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data0_u *value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data1_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data1_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_RD_RSLT_DATA1_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data1_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data1_u *value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data2_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data2_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_RD_RSLT_DATA2_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data2_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data2_u *value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data3_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data3_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_RD_RSLT_DATA3_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data3_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data3_u *value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data4_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data4_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_RD_RSLT_DATA4_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data4_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data4_u *value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data5_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data5_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_RD_RSLT_DATA5_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data5_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data5_u *value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data6_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data6_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_RD_RSLT_DATA6_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data6_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data6_u *value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data7_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data7_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_RD_RSLT_DATA7_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data7_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data7_u *value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data8_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data8_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_RD_RSLT_DATA8_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data8_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data8_u *value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data9_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data9_u *value)
{
	return hppe_reg_get(
				dev_id,
				IPE_L3_BASE_ADDR + FLOW_HOST_TBL_RD_RSLT_DATA9_ADDRESS,
				&value->val);
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data9_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data9_u *value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_in_flow_3tuple_tbl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union in_flow_3tuple_tbl_u *value)
{
	return hppe_reg_tbl_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_3TUPLE_TBL_ADDRESS + \
				index * IN_FLOW_3TUPLE_TBL_INC,
				value->val,
				4);
}

sw_error_t
hppe_in_flow_3tuple_tbl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union in_flow_3tuple_tbl_u *value)
{
	return hppe_reg_tbl_set(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_3TUPLE_TBL_ADDRESS + \
				index * IN_FLOW_3TUPLE_TBL_INC,
				value->val,
				4);
}

sw_error_t
hppe_in_flow_ipv6_3tuple_tbl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union in_flow_ipv6_3tuple_tbl_u *value)
{
	return hppe_reg_tbl_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_IPV6_3TUPLE_TBL_ADDRESS + \
				index * IN_FLOW_IPV6_3TUPLE_TBL_INC,
				value->val,
				9);
}

sw_error_t
hppe_in_flow_ipv6_3tuple_tbl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union in_flow_ipv6_3tuple_tbl_u *value)
{
	return hppe_reg_tbl_set(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_IPV6_3TUPLE_TBL_ADDRESS + \
				index * IN_FLOW_IPV6_3TUPLE_TBL_INC,
				value->val,
				9);
}

sw_error_t
hppe_in_flow_ipv6_5tuple_tbl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union in_flow_ipv6_5tuple_tbl_u *value)
{
	return hppe_reg_tbl_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_IPV6_5TUPLE_TBL_ADDRESS + \
				index * IN_FLOW_IPV6_5TUPLE_TBL_INC,
				value->val,
				9);
}

sw_error_t
hppe_in_flow_ipv6_5tuple_tbl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union in_flow_ipv6_5tuple_tbl_u *value)
{
	return hppe_reg_tbl_set(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_IPV6_5TUPLE_TBL_ADDRESS + \
				index * IN_FLOW_IPV6_5TUPLE_TBL_INC,
				value->val,
				9);
}

sw_error_t
hppe_in_flow_tbl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union in_flow_tbl_u *value)
{
	return hppe_reg_tbl_get(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_ADDRESS + \
				index * IN_FLOW_TBL_INC,
				value->val,
				5);
}

sw_error_t
hppe_in_flow_tbl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union in_flow_tbl_u *value)
{
	return hppe_reg_tbl_set(
				dev_id,
				IPE_L3_BASE_ADDR + IN_FLOW_TBL_ADDRESS + \
				index * IN_FLOW_TBL_INC,
				value->val,
				5);
}

sw_error_t
hppe_eg_flow_tree_map_tbl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union eg_flow_tree_map_tbl_u *value)
{
	if (index >= EG_FLOW_TREE_MAP_TBL_MAX_ENTRY)
		return SW_OUT_OF_RANGE;
	return hppe_reg_get(
				dev_id,
				NSS_PTX_CSR_BASE_ADDR + EG_FLOW_TREE_MAP_TBL_ADDRESS + \
				index * EG_FLOW_TREE_MAP_TBL_INC,
				&value->val);
}

sw_error_t
hppe_eg_flow_tree_map_tbl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union eg_flow_tree_map_tbl_u *value)
{
	return hppe_reg_set(
				dev_id,
				NSS_PTX_CSR_BASE_ADDR + EG_FLOW_TREE_MAP_TBL_ADDRESS + \
				index * EG_FLOW_TREE_MAP_TBL_INC,
				value->val);
}

sw_error_t
hppe_flow_ctrl0_flow_hash_mode_0_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_ctrl0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl0_get(dev_id, &reg_val);
	*value = reg_val.bf.flow_hash_mode_0;
	return ret;
}

sw_error_t
hppe_flow_ctrl0_flow_hash_mode_0_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union flow_ctrl0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl0_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.flow_hash_mode_0 = value;
	ret = hppe_flow_ctrl0_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_ctrl0_flow_age_timer_unit_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_ctrl0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl0_get(dev_id, &reg_val);
	*value = reg_val.bf.flow_age_timer_unit;
	return ret;
}

sw_error_t
hppe_flow_ctrl0_flow_age_timer_unit_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union flow_ctrl0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl0_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.flow_age_timer_unit = value;
	ret = hppe_flow_ctrl0_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_ctrl0_flow_hash_mode_1_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_ctrl0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl0_get(dev_id, &reg_val);
	*value = reg_val.bf.flow_hash_mode_1;
	return ret;
}

sw_error_t
hppe_flow_ctrl0_flow_hash_mode_1_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union flow_ctrl0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl0_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.flow_hash_mode_1 = value;
	ret = hppe_flow_ctrl0_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_ctrl0_flow_age_timer_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_ctrl0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl0_get(dev_id, &reg_val);
	*value = reg_val.bf.flow_age_timer;
	return ret;
}

sw_error_t
hppe_flow_ctrl0_flow_age_timer_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union flow_ctrl0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl0_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.flow_age_timer = value;
	ret = hppe_flow_ctrl0_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_ctrl0_flow_en_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_ctrl0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl0_get(dev_id, &reg_val);
	*value = reg_val.bf.flow_en;
	return ret;
}

sw_error_t
hppe_flow_ctrl0_flow_en_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union flow_ctrl0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl0_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.flow_en = value;
	ret = hppe_flow_ctrl0_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl1_frag_bypass_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	*value = reg_val.bf.flow_ctl1_frag_bypass;
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl1_frag_bypass_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.flow_ctl1_frag_bypass = value;
	ret = hppe_flow_ctrl1_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl4_key_sel_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	*value = reg_val.bf.flow_ctl4_key_sel;
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl4_key_sel_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.flow_ctl4_key_sel = value;
	ret = hppe_flow_ctrl1_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl1_key_sel_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	*value = reg_val.bf.flow_ctl1_key_sel;
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl1_key_sel_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.flow_ctl1_key_sel = value;
	ret = hppe_flow_ctrl1_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl0_frag_bypass_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	*value = reg_val.bf.flow_ctl0_frag_bypass;
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl0_frag_bypass_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.flow_ctl0_frag_bypass = value;
	ret = hppe_flow_ctrl1_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl0_miss_action_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	*value = reg_val.bf.flow_ctl0_miss_action;
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl0_miss_action_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.flow_ctl0_miss_action = value;
	ret = hppe_flow_ctrl1_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl0_key_sel_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	*value = reg_val.bf.flow_ctl0_key_sel;
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl0_key_sel_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.flow_ctl0_key_sel = value;
	ret = hppe_flow_ctrl1_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl1_bypass_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	*value = reg_val.bf.flow_ctl1_bypass;
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl1_bypass_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.flow_ctl1_bypass = value;
	ret = hppe_flow_ctrl1_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl0_bypass_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	*value = reg_val.bf.flow_ctl0_bypass;
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl0_bypass_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.flow_ctl0_bypass = value;
	ret = hppe_flow_ctrl1_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl2_tcp_special_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	*value = reg_val.bf.flow_ctl2_tcp_special;
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl2_tcp_special_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.flow_ctl2_tcp_special = value;
	ret = hppe_flow_ctrl1_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl4_tcp_special_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	*value = reg_val.bf.flow_ctl4_tcp_special;
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl4_tcp_special_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.flow_ctl4_tcp_special = value;
	ret = hppe_flow_ctrl1_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl3_frag_bypass_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	*value = reg_val.bf.flow_ctl3_frag_bypass;
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl3_frag_bypass_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.flow_ctl3_frag_bypass = value;
	ret = hppe_flow_ctrl1_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl3_bypass_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	*value = reg_val.bf.flow_ctl3_bypass;
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl3_bypass_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.flow_ctl3_bypass = value;
	ret = hppe_flow_ctrl1_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl3_tcp_special_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	*value = reg_val.bf.flow_ctl3_tcp_special;
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl3_tcp_special_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.flow_ctl3_tcp_special = value;
	ret = hppe_flow_ctrl1_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl1_miss_action_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	*value = reg_val.bf.flow_ctl1_miss_action;
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl1_miss_action_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.flow_ctl1_miss_action = value;
	ret = hppe_flow_ctrl1_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl4_frag_bypass_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	*value = reg_val.bf.flow_ctl4_frag_bypass;
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl4_frag_bypass_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.flow_ctl4_frag_bypass = value;
	ret = hppe_flow_ctrl1_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl1_tcp_special_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	*value = reg_val.bf.flow_ctl1_tcp_special;
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl1_tcp_special_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.flow_ctl1_tcp_special = value;
	ret = hppe_flow_ctrl1_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl2_key_sel_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	*value = reg_val.bf.flow_ctl2_key_sel;
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl2_key_sel_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.flow_ctl2_key_sel = value;
	ret = hppe_flow_ctrl1_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl2_miss_action_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	*value = reg_val.bf.flow_ctl2_miss_action;
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl2_miss_action_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.flow_ctl2_miss_action = value;
	ret = hppe_flow_ctrl1_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl2_bypass_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	*value = reg_val.bf.flow_ctl2_bypass;
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl2_bypass_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.flow_ctl2_bypass = value;
	ret = hppe_flow_ctrl1_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl4_bypass_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	*value = reg_val.bf.flow_ctl4_bypass;
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl4_bypass_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.flow_ctl4_bypass = value;
	ret = hppe_flow_ctrl1_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl3_key_sel_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	*value = reg_val.bf.flow_ctl3_key_sel;
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl3_key_sel_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.flow_ctl3_key_sel = value;
	ret = hppe_flow_ctrl1_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl0_tcp_special_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	*value = reg_val.bf.flow_ctl0_tcp_special;
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl0_tcp_special_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.flow_ctl0_tcp_special = value;
	ret = hppe_flow_ctrl1_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl2_frag_bypass_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	*value = reg_val.bf.flow_ctl2_frag_bypass;
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl2_frag_bypass_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.flow_ctl2_frag_bypass = value;
	ret = hppe_flow_ctrl1_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl3_miss_action_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	*value = reg_val.bf.flow_ctl3_miss_action;
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl3_miss_action_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.flow_ctl3_miss_action = value;
	ret = hppe_flow_ctrl1_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl4_miss_action_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	*value = reg_val.bf.flow_ctl4_miss_action;
	return ret;
}

sw_error_t
hppe_flow_ctrl1_flow_ctl4_miss_action_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union flow_ctrl1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_ctrl1_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.flow_ctl4_miss_action = value;
	ret = hppe_flow_ctrl1_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_in_pub_ip_addr_tbl_ip_addr_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union in_pub_ip_addr_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_pub_ip_addr_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.ip_addr;
	return ret;
}

sw_error_t
hppe_in_pub_ip_addr_tbl_ip_addr_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union in_pub_ip_addr_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_pub_ip_addr_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.ip_addr = value;
	ret = hppe_in_pub_ip_addr_tbl_set(dev_id, index, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_entry_index_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_get(dev_id, &reg_val);
	*value = reg_val.bf.entry_index;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_entry_index_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.entry_index = value;
	ret = hppe_in_flow_tbl_op_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_cmd_id_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_get(dev_id, &reg_val);
	*value = reg_val.bf.cmd_id;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_cmd_id_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.cmd_id = value;
	ret = hppe_in_flow_tbl_op_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_byp_rslt_en_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_get(dev_id, &reg_val);
	*value = reg_val.bf.byp_rslt_en;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_byp_rslt_en_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.byp_rslt_en = value;
	ret = hppe_in_flow_tbl_op_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_op_mode_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_get(dev_id, &reg_val);
	*value = reg_val.bf.op_mode;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_op_mode_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.op_mode = value;
	ret = hppe_in_flow_tbl_op_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_op_type_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_get(dev_id, &reg_val);
	*value = reg_val.bf.op_type;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_op_type_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.op_type = value;
	ret = hppe_in_flow_tbl_op_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_op_host_en_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_get(dev_id, &reg_val);
	*value = reg_val.bf.op_host_en;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_op_host_en_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.op_host_en = value;
	ret = hppe_in_flow_tbl_op_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_op_result_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_get(dev_id, &reg_val);
	*value = reg_val.bf.op_result;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_op_result_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.op_result = value;
	ret = hppe_in_flow_tbl_op_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_busy_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_get(dev_id, &reg_val);
	*value = reg_val.bf.busy;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_busy_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.busy = value;
	ret = hppe_in_flow_tbl_op_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_hash_block_bitmap_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_get(dev_id, &reg_val);
	*value = reg_val.bf.hash_block_bitmap;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_hash_block_bitmap_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.hash_block_bitmap = value;
	ret = hppe_in_flow_tbl_op_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_host_tbl_op_host_entry_index_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_host_tbl_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_host_tbl_op_get(dev_id, &reg_val);
	*value = reg_val.bf.host_entry_index;
	return ret;
}

sw_error_t
hppe_in_flow_host_tbl_op_host_entry_index_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_host_tbl_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_host_tbl_op_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.host_entry_index = value;
	ret = hppe_in_flow_host_tbl_op_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_host_tbl_op_hash_block_bitmap_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_host_tbl_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_host_tbl_op_get(dev_id, &reg_val);
	*value = reg_val.bf.hash_block_bitmap;
	return ret;
}

sw_error_t
hppe_in_flow_host_tbl_op_hash_block_bitmap_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_host_tbl_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_host_tbl_op_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.hash_block_bitmap = value;
	ret = hppe_in_flow_host_tbl_op_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_data0_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_op_data0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_data0_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_data0_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_op_data0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_data0_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_in_flow_tbl_op_data0_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_data1_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_op_data1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_data1_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_data1_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_op_data1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_data1_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_in_flow_tbl_op_data1_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_data2_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_op_data2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_data2_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_data2_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_op_data2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_data2_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_in_flow_tbl_op_data2_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_data3_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_op_data3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_data3_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_data3_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_op_data3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_data3_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_in_flow_tbl_op_data3_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_data4_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_op_data4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_data4_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_data4_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_op_data4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_data4_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_in_flow_tbl_op_data4_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_data5_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_op_data5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_data5_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_data5_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_op_data5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_data5_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_in_flow_tbl_op_data5_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_data6_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_op_data6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_data6_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_data6_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_op_data6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_data6_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_in_flow_tbl_op_data6_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_data7_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_op_data7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_data7_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_data7_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_op_data7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_data7_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_in_flow_tbl_op_data7_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_data8_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_op_data8_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_data8_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_data8_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_op_data8_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_data8_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_in_flow_tbl_op_data8_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_host_tbl_op_data0_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_op_data0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_op_data0_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_op_data0_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union flow_host_tbl_op_data0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_op_data0_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_flow_host_tbl_op_data0_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_host_tbl_op_data1_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_op_data1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_op_data1_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_op_data1_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union flow_host_tbl_op_data1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_op_data1_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_flow_host_tbl_op_data1_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_host_tbl_op_data2_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_op_data2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_op_data2_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_op_data2_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union flow_host_tbl_op_data2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_op_data2_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_flow_host_tbl_op_data2_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_host_tbl_op_data3_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_op_data3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_op_data3_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_op_data3_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union flow_host_tbl_op_data3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_op_data3_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_flow_host_tbl_op_data3_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_host_tbl_op_data4_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_op_data4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_op_data4_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_op_data4_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union flow_host_tbl_op_data4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_op_data4_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_flow_host_tbl_op_data4_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_host_tbl_op_data5_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_op_data5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_op_data5_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_op_data5_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union flow_host_tbl_op_data5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_op_data5_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_flow_host_tbl_op_data5_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_host_tbl_op_data6_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_op_data6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_op_data6_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_op_data6_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union flow_host_tbl_op_data6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_op_data6_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_flow_host_tbl_op_data6_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_host_tbl_op_data7_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_op_data7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_op_data7_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_op_data7_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union flow_host_tbl_op_data7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_op_data7_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_flow_host_tbl_op_data7_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_host_tbl_op_data8_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_op_data8_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_op_data8_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_op_data8_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union flow_host_tbl_op_data8_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_op_data8_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_flow_host_tbl_op_data8_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_host_tbl_op_data9_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_op_data9_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_op_data9_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_op_data9_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union flow_host_tbl_op_data9_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_op_data9_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_flow_host_tbl_op_data9_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_rslt_op_rslt_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_op_rslt_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_rslt_get(dev_id, &reg_val);
	*value = reg_val.bf.op_rslt;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_rslt_op_rslt_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_in_flow_tbl_op_rslt_valid_cnt_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_op_rslt_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_rslt_get(dev_id, &reg_val);
	*value = reg_val.bf.valid_cnt;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_rslt_valid_cnt_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_in_flow_tbl_op_rslt_flow_entry_index_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_op_rslt_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_rslt_get(dev_id, &reg_val);
	*value = reg_val.bf.flow_entry_index;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_rslt_flow_entry_index_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_in_flow_tbl_op_rslt_cmd_id_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_op_rslt_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_op_rslt_get(dev_id, &reg_val);
	*value = reg_val.bf.cmd_id;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_op_rslt_cmd_id_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_flow_host_tbl_op_rslt_host_entry_index_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_op_rslt_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_op_rslt_get(dev_id, &reg_val);
	*value = reg_val.bf.host_entry_index;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_op_rslt_host_entry_index_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_in_flow_tbl_rd_op_entry_index_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_rd_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_get(dev_id, &reg_val);
	*value = reg_val.bf.entry_index;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_entry_index_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_rd_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.entry_index = value;
	ret = hppe_in_flow_tbl_rd_op_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_cmd_id_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_rd_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_get(dev_id, &reg_val);
	*value = reg_val.bf.cmd_id;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_cmd_id_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_rd_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.cmd_id = value;
	ret = hppe_in_flow_tbl_rd_op_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_byp_rslt_en_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_rd_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_get(dev_id, &reg_val);
	*value = reg_val.bf.byp_rslt_en;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_byp_rslt_en_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_rd_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.byp_rslt_en = value;
	ret = hppe_in_flow_tbl_rd_op_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_op_mode_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_rd_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_get(dev_id, &reg_val);
	*value = reg_val.bf.op_mode;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_op_mode_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_rd_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.op_mode = value;
	ret = hppe_in_flow_tbl_rd_op_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_op_type_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_rd_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_get(dev_id, &reg_val);
	*value = reg_val.bf.op_type;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_op_type_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_rd_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.op_type = value;
	ret = hppe_in_flow_tbl_rd_op_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_op_host_en_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_rd_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_get(dev_id, &reg_val);
	*value = reg_val.bf.op_host_en;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_op_host_en_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_rd_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.op_host_en = value;
	ret = hppe_in_flow_tbl_rd_op_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_op_result_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_rd_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_get(dev_id, &reg_val);
	*value = reg_val.bf.op_result;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_op_result_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_rd_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.op_result = value;
	ret = hppe_in_flow_tbl_rd_op_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_busy_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_rd_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_get(dev_id, &reg_val);
	*value = reg_val.bf.busy;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_busy_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_rd_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.busy = value;
	ret = hppe_in_flow_tbl_rd_op_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_hash_block_bitmap_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_rd_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_get(dev_id, &reg_val);
	*value = reg_val.bf.hash_block_bitmap;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_hash_block_bitmap_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_rd_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.hash_block_bitmap = value;
	ret = hppe_in_flow_tbl_rd_op_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_host_tbl_rd_op_host_entry_index_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_host_tbl_rd_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_host_tbl_rd_op_get(dev_id, &reg_val);
	*value = reg_val.bf.host_entry_index;
	return ret;
}

sw_error_t
hppe_in_flow_host_tbl_rd_op_host_entry_index_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_host_tbl_rd_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_host_tbl_rd_op_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.host_entry_index = value;
	ret = hppe_in_flow_host_tbl_rd_op_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_host_tbl_rd_op_hash_block_bitmap_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_host_tbl_rd_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_host_tbl_rd_op_get(dev_id, &reg_val);
	*value = reg_val.bf.hash_block_bitmap;
	return ret;
}

sw_error_t
hppe_in_flow_host_tbl_rd_op_hash_block_bitmap_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_host_tbl_rd_op_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_host_tbl_rd_op_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.hash_block_bitmap = value;
	ret = hppe_in_flow_host_tbl_rd_op_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_data0_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_rd_op_data0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_data0_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_data0_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_rd_op_data0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_data0_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_in_flow_tbl_rd_op_data0_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_data1_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_rd_op_data1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_data1_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_data1_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_rd_op_data1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_data1_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_in_flow_tbl_rd_op_data1_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_data2_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_rd_op_data2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_data2_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_data2_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_rd_op_data2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_data2_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_in_flow_tbl_rd_op_data2_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_data3_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_rd_op_data3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_data3_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_data3_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_rd_op_data3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_data3_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_in_flow_tbl_rd_op_data3_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_data4_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_rd_op_data4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_data4_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_data4_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_rd_op_data4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_data4_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_in_flow_tbl_rd_op_data4_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_data5_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_rd_op_data5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_data5_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_data5_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_rd_op_data5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_data5_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_in_flow_tbl_rd_op_data5_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_data6_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_rd_op_data6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_data6_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_data6_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_rd_op_data6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_data6_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_in_flow_tbl_rd_op_data6_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_data7_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_rd_op_data7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_data7_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_data7_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_rd_op_data7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_data7_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_in_flow_tbl_rd_op_data7_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_data8_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_rd_op_data8_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_data8_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_data8_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union in_flow_tbl_rd_op_data8_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_data8_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_in_flow_tbl_rd_op_data8_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_host_tbl_rd_op_data0_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_rd_op_data0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_rd_op_data0_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_rd_op_data0_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union flow_host_tbl_rd_op_data0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_rd_op_data0_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_flow_host_tbl_rd_op_data0_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_host_tbl_rd_op_data1_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_rd_op_data1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_rd_op_data1_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_rd_op_data1_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union flow_host_tbl_rd_op_data1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_rd_op_data1_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_flow_host_tbl_rd_op_data1_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_host_tbl_rd_op_data2_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_rd_op_data2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_rd_op_data2_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_rd_op_data2_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union flow_host_tbl_rd_op_data2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_rd_op_data2_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_flow_host_tbl_rd_op_data2_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_host_tbl_rd_op_data3_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_rd_op_data3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_rd_op_data3_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_rd_op_data3_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union flow_host_tbl_rd_op_data3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_rd_op_data3_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_flow_host_tbl_rd_op_data3_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_host_tbl_rd_op_data4_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_rd_op_data4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_rd_op_data4_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_rd_op_data4_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union flow_host_tbl_rd_op_data4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_rd_op_data4_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_flow_host_tbl_rd_op_data4_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_host_tbl_rd_op_data5_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_rd_op_data5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_rd_op_data5_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_rd_op_data5_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union flow_host_tbl_rd_op_data5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_rd_op_data5_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_flow_host_tbl_rd_op_data5_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_host_tbl_rd_op_data6_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_rd_op_data6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_rd_op_data6_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_rd_op_data6_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union flow_host_tbl_rd_op_data6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_rd_op_data6_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_flow_host_tbl_rd_op_data6_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_host_tbl_rd_op_data7_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_rd_op_data7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_rd_op_data7_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_rd_op_data7_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union flow_host_tbl_rd_op_data7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_rd_op_data7_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_flow_host_tbl_rd_op_data7_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_host_tbl_rd_op_data8_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_rd_op_data8_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_rd_op_data8_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_rd_op_data8_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union flow_host_tbl_rd_op_data8_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_rd_op_data8_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_flow_host_tbl_rd_op_data8_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_flow_host_tbl_rd_op_data9_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_rd_op_data9_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_rd_op_data9_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_rd_op_data9_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	union flow_host_tbl_rd_op_data9_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_rd_op_data9_get(dev_id, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.data = value;
	ret = hppe_flow_host_tbl_rd_op_data9_set(dev_id, &reg_val);
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_rslt_op_rslt_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_rd_op_rslt_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_rslt_get(dev_id, &reg_val);
	*value = reg_val.bf.op_rslt;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_rslt_op_rslt_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_in_flow_tbl_rd_op_rslt_valid_cnt_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_rd_op_rslt_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_rslt_get(dev_id, &reg_val);
	*value = reg_val.bf.valid_cnt;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_rslt_valid_cnt_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_in_flow_tbl_rd_op_rslt_flow_entry_index_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_rd_op_rslt_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_rslt_get(dev_id, &reg_val);
	*value = reg_val.bf.flow_entry_index;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_rslt_flow_entry_index_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_in_flow_tbl_rd_op_rslt_cmd_id_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_rd_op_rslt_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_op_rslt_get(dev_id, &reg_val);
	*value = reg_val.bf.cmd_id;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_op_rslt_cmd_id_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_flow_host_tbl_rd_op_rslt_host_entry_index_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_rd_op_rslt_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_rd_op_rslt_get(dev_id, &reg_val);
	*value = reg_val.bf.host_entry_index;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_rd_op_rslt_host_entry_index_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data0_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_rd_rslt_data0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_rslt_data0_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data0_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data1_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_rd_rslt_data1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_rslt_data1_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data1_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data2_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_rd_rslt_data2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_rslt_data2_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data2_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data3_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_rd_rslt_data3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_rslt_data3_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data3_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data4_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_rd_rslt_data4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_rslt_data4_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data4_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data5_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_rd_rslt_data5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_rslt_data5_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data5_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data6_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_rd_rslt_data6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_rslt_data6_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data6_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data7_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_rd_rslt_data7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_rslt_data7_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data7_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data8_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union in_flow_tbl_rd_rslt_data8_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_in_flow_tbl_rd_rslt_data8_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_in_flow_tbl_rd_rslt_data8_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data0_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_rd_rslt_data0_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_rd_rslt_data0_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data0_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data1_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_rd_rslt_data1_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_rd_rslt_data1_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data1_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data2_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_rd_rslt_data2_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_rd_rslt_data2_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data2_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data3_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_rd_rslt_data3_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_rd_rslt_data3_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data3_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data4_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_rd_rslt_data4_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_rd_rslt_data4_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data4_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data5_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_rd_rslt_data5_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_rd_rslt_data5_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data5_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data6_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_rd_rslt_data6_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_rd_rslt_data6_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data6_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data7_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_rd_rslt_data7_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_rd_rslt_data7_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data7_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data8_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_rd_rslt_data8_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_rd_rslt_data8_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data8_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data9_data_get(
		a_uint32_t dev_id,
		a_uint32_t *value)
{
	union flow_host_tbl_rd_rslt_data9_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_flow_host_tbl_rd_rslt_data9_get(dev_id, &reg_val);
	*value = reg_val.bf.data;
	return ret;
}

sw_error_t
hppe_flow_host_tbl_rd_rslt_data9_data_set(
		a_uint32_t dev_id,
		a_uint32_t value)
{
	return SW_NOT_SUPPORTED;
}

sw_error_t
hppe_eg_flow_tree_map_tbl_tree_id_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value)
{
	union eg_flow_tree_map_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_eg_flow_tree_map_tbl_get(dev_id, index, &reg_val);
	*value = reg_val.bf.tree_id;
	return ret;
}

sw_error_t
hppe_eg_flow_tree_map_tbl_tree_id_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value)
{
	union eg_flow_tree_map_tbl_u reg_val;
	sw_error_t ret = SW_OK;

	ret = hppe_eg_flow_tree_map_tbl_get(dev_id, index, &reg_val);
	if (SW_OK != ret)
		return ret;
	reg_val.bf.tree_id = value;
	ret = hppe_eg_flow_tree_map_tbl_set(dev_id, index, &reg_val);
	return ret;
}


