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
#ifndef _HPPE_L3_API_H_
#define _HPPE_L3_API_H_

#define IPE_L3_BASE_ADDR    0x3a200000
#define METER_CMPST_LENGTH_REG_MAX_ENTRY	8
#define IN_ACL_METER_CFG_TBL_MAX_ENTRY	512
#define IN_ACL_METER_CRDT_TBL_MAX_ENTRY	512
#define IN_PORT_METER_CFG_TBL_MAX_ENTRY	8
#define IN_PORT_METER_CRDT_TBL_MAX_ENTRY	8
#define IN_PORT_METER_CNT_TBL_MAX_ENTRY	24
#define IN_ACL_METER_CNT_TBL_MAX_ENTRY	1536
#define IN_FLOW_CNT_TBL_MAX_ENTRY	4096
#define RT_INTERFACE_CNT_TBL_MAX_ENTRY	512
#define PC_GLOBAL_CNT_TBL_MAX_ENTRY	3
#define DROP_CPU_CNT_TBL_MAX_ENTRY	1280
#define IPO_CNT_TBL_MAX_ENTRY	512
#define VLAN_CNT_TBL_MAX_ENTRY	32
#define PRE_L2_CNT_TBL_MAX_ENTRY	32
#define PORT_TX_DROP_CNT_TBL_MAX_ENTRY	8
#define VP_TX_DROP_CNT_TBL_MAX_ENTRY	256
#define VLAN_DEV_CNT_TBL_MAX_ENTRY	64
#define XLT_RULE_TBL_MAX_ENTRY	64
#define XLT_ACTION_TBL_MAX_ENTRY	64
#define SERVICE_TBL_MAX_ENTRY	256
#define TRUNK_FILTER_MAX_ENTRY	2
#define TRUNK_MEMBER_MAX_ENTRY	2
#define ETHERTYPE_CTRL_MAX_ENTRY	4
#define CST_STATE_MAX_ENTRY	8
#define PORT_BRIDGE_CTRL_MAX_ENTRY	8
#define PORT_LRN_LIMIT_CTRL_MAX_ENTRY	8
#define PORT_LRN_LIMIT_COUNTER_MAX_ENTRY	8
#define PORT_TRUNK_ID_MAX_ENTRY	8
#define PORT_IN_FORWARD_MAX_ENTRY	8
#define PORT_MIRROR_MAX_ENTRY	8
#define PORT_QOS_CTRL_MAX_ENTRY	8
#define MC_MTU_CTRL_TBL_MAX_ENTRY	8
#define PCP_QOS_GROUP_0_MAX_ENTRY	16
#define PCP_QOS_GROUP_1_MAX_ENTRY	16
#define FLOW_QOS_GROUP_0_MAX_ENTRY	32
#define FLOW_QOS_GROUP_1_MAX_ENTRY	32
#define RFDB_TBL_MAX_ENTRY	32
#define APP_CTRL_MAX_ENTRY	32
#define VSI_TBL_MAX_ENTRY	32
#define DSCP_QOS_GROUP_0_MAX_ENTRY	64
#define DSCP_QOS_GROUP_1_MAX_ENTRY	64
#define MRU_MTU_CTRL_TBL_MAX_ENTRY	256
#define IN_L2_SERVICE_TBL_MAX_ENTRY	256
#define IPO_ACTION_MAX_ENTRY	512
#define FDB_TBL_MAX_ENTRY	2048
#define MY_MAC_TBL_MAX_ENTRY	8
#define L3_VSI_MAX_ENTRY	32
#define L3_VSI_EXT_MAX_ENTRY	32
#define NETWORK_ROUTE_IP_MAX_ENTRY	32
#define NETWORK_ROUTE_IP_EXT_MAX_ENTRY	32
#define NETWORK_ROUTE_ACTION_MAX_ENTRY	32
#define PPPOE_SESSION_MAX_ENTRY	4
#define PPPOE_SESSION_EXT_MAX_ENTRY	4
#define FLOW_CTRL1_MAX_ENTRY	3
#define IN_PUB_IP_ADDR_TBL_MAX_ENTRY	16
#define L3_EXCEPTION_CMD_MAX_ENTRY	72
#define L3_EXP_L3_ONLY_CTRL_MAX_ENTRY	72
#define L3_EXP_L2_ONLY_CTRL_MAX_ENTRY	72
#define L3_EXP_L2_FLOW_CTRL_MAX_ENTRY	72
#define L3_EXP_L3_FLOW_CTRL_MAX_ENTRY	72
#define L3_EXP_MULTICAST_CTRL_MAX_ENTRY	72
#define L3_VP_PORT_TBL_MAX_ENTRY	256
#define IN_L3_IF_TBL_MAX_ENTRY	256
#define HOST_IPV6_MCAST_TBL_MAX_ENTRY	1536
#define HOST_IPV4_MCAST_TBL_MAX_ENTRY	3072
#define HOST_TBL_MAX_ENTRY	6144
#define HOST_IPV6_TBL_MAX_ENTRY	3072
#define IN_FLOW_3TUPLE_TBL_MAX_ENTRY	4096
#define IN_FLOW_IPV6_3TUPLE_TBL_MAX_ENTRY	2048
#define IN_FLOW_IPV6_5TUPLE_TBL_MAX_ENTRY	2048
#define IN_FLOW_TBL_MAX_ENTRY	4096
#define IN_NEXTHOP_TBL_MAX_ENTRY	2560


sw_error_t
hppe_my_mac_tbl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union my_mac_tbl_u *value);

sw_error_t
hppe_my_mac_tbl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union my_mac_tbl_u *value);

sw_error_t
hppe_l3_vsi_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union l3_vsi_u *value);

sw_error_t
hppe_l3_vsi_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union l3_vsi_u *value);

sw_error_t
hppe_l3_vsi_ext_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union l3_vsi_ext_u *value);

sw_error_t
hppe_l3_vsi_ext_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union l3_vsi_ext_u *value);

sw_error_t
hppe_network_route_ip_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union network_route_ip_u *value);

sw_error_t
hppe_network_route_ip_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union network_route_ip_u *value);

sw_error_t
hppe_network_route_ip_ext_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union network_route_ip_ext_u *value);

sw_error_t
hppe_network_route_ip_ext_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union network_route_ip_ext_u *value);

sw_error_t
hppe_network_route_action_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union network_route_action_u *value);

sw_error_t
hppe_network_route_action_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union network_route_action_u *value);

sw_error_t
hppe_l3_route_ctrl_get(
		a_uint32_t dev_id,
		union l3_route_ctrl_u *value);

sw_error_t
hppe_l3_route_ctrl_set(
		a_uint32_t dev_id,
		union l3_route_ctrl_u *value);

sw_error_t
hppe_l3_route_ctrl_ext_get(
		a_uint32_t dev_id,
		union l3_route_ctrl_ext_u *value);

sw_error_t
hppe_l3_route_ctrl_ext_set(
		a_uint32_t dev_id,
		union l3_route_ctrl_ext_u *value);

sw_error_t
hppe_pppoe_session_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union pppoe_session_u *value);

sw_error_t
hppe_pppoe_session_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union pppoe_session_u *value);

sw_error_t
hppe_pppoe_session_ext_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union pppoe_session_ext_u *value);

sw_error_t
hppe_pppoe_session_ext_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union pppoe_session_ext_u *value);

sw_error_t
hppe_flow_ctrl0_get(
		a_uint32_t dev_id,
		union flow_ctrl0_u *value);

sw_error_t
hppe_flow_ctrl0_set(
		a_uint32_t dev_id,
		union flow_ctrl0_u *value);

sw_error_t
hppe_flow_ctrl1_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union flow_ctrl1_u *value);

sw_error_t
hppe_flow_ctrl1_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union flow_ctrl1_u *value);

sw_error_t
hppe_in_pub_ip_addr_tbl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union in_pub_ip_addr_tbl_u *value);

sw_error_t
hppe_in_pub_ip_addr_tbl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union in_pub_ip_addr_tbl_u *value);

sw_error_t
hppe_in_flow_tbl_op_get(
		a_uint32_t dev_id,
		union in_flow_tbl_op_u *value);

sw_error_t
hppe_in_flow_tbl_op_set(
		a_uint32_t dev_id,
		union in_flow_tbl_op_u *value);

sw_error_t
hppe_in_flow_host_tbl_op_get(
		a_uint32_t dev_id,
		union in_flow_host_tbl_op_u *value);

sw_error_t
hppe_in_flow_host_tbl_op_set(
		a_uint32_t dev_id,
		union in_flow_host_tbl_op_u *value);

sw_error_t
hppe_in_flow_tbl_op_data0_get(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data0_u *value);

sw_error_t
hppe_in_flow_tbl_op_data0_set(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data0_u *value);

sw_error_t
hppe_in_flow_tbl_op_data1_get(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data1_u *value);

sw_error_t
hppe_in_flow_tbl_op_data1_set(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data1_u *value);

sw_error_t
hppe_in_flow_tbl_op_data2_get(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data2_u *value);

sw_error_t
hppe_in_flow_tbl_op_data2_set(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data2_u *value);

sw_error_t
hppe_in_flow_tbl_op_data3_get(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data3_u *value);

sw_error_t
hppe_in_flow_tbl_op_data3_set(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data3_u *value);

sw_error_t
hppe_in_flow_tbl_op_data4_get(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data4_u *value);

sw_error_t
hppe_in_flow_tbl_op_data4_set(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data4_u *value);

sw_error_t
hppe_in_flow_tbl_op_data5_get(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data5_u *value);

sw_error_t
hppe_in_flow_tbl_op_data5_set(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data5_u *value);

sw_error_t
hppe_in_flow_tbl_op_data6_get(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data6_u *value);

sw_error_t
hppe_in_flow_tbl_op_data6_set(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data6_u *value);

sw_error_t
hppe_in_flow_tbl_op_data7_get(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data7_u *value);

sw_error_t
hppe_in_flow_tbl_op_data7_set(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data7_u *value);

sw_error_t
hppe_in_flow_tbl_op_data8_get(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data8_u *value);

sw_error_t
hppe_in_flow_tbl_op_data8_set(
		a_uint32_t dev_id,
		union in_flow_tbl_op_data8_u *value);

sw_error_t
hppe_flow_host_tbl_op_data0_get(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data0_u *value);

sw_error_t
hppe_flow_host_tbl_op_data0_set(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data0_u *value);

sw_error_t
hppe_flow_host_tbl_op_data1_get(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data1_u *value);

sw_error_t
hppe_flow_host_tbl_op_data1_set(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data1_u *value);

sw_error_t
hppe_flow_host_tbl_op_data2_get(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data2_u *value);

sw_error_t
hppe_flow_host_tbl_op_data2_set(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data2_u *value);

sw_error_t
hppe_flow_host_tbl_op_data3_get(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data3_u *value);

sw_error_t
hppe_flow_host_tbl_op_data3_set(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data3_u *value);

sw_error_t
hppe_flow_host_tbl_op_data4_get(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data4_u *value);

sw_error_t
hppe_flow_host_tbl_op_data4_set(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data4_u *value);

sw_error_t
hppe_flow_host_tbl_op_data5_get(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data5_u *value);

sw_error_t
hppe_flow_host_tbl_op_data5_set(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data5_u *value);

sw_error_t
hppe_flow_host_tbl_op_data6_get(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data6_u *value);

sw_error_t
hppe_flow_host_tbl_op_data6_set(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data6_u *value);

sw_error_t
hppe_flow_host_tbl_op_data7_get(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data7_u *value);

sw_error_t
hppe_flow_host_tbl_op_data7_set(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data7_u *value);

sw_error_t
hppe_flow_host_tbl_op_data8_get(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data8_u *value);

sw_error_t
hppe_flow_host_tbl_op_data8_set(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data8_u *value);

sw_error_t
hppe_flow_host_tbl_op_data9_get(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data9_u *value);

sw_error_t
hppe_flow_host_tbl_op_data9_set(
		a_uint32_t dev_id,
		union flow_host_tbl_op_data9_u *value);

sw_error_t
hppe_in_flow_tbl_op_rslt_get(
		a_uint32_t dev_id,
		union in_flow_tbl_op_rslt_u *value);

sw_error_t
hppe_in_flow_tbl_op_rslt_set(
		a_uint32_t dev_id,
		union in_flow_tbl_op_rslt_u *value);

sw_error_t
hppe_flow_host_tbl_op_rslt_get(
		a_uint32_t dev_id,
		union flow_host_tbl_op_rslt_u *value);

sw_error_t
hppe_flow_host_tbl_op_rslt_set(
		a_uint32_t dev_id,
		union flow_host_tbl_op_rslt_u *value);

sw_error_t
hppe_in_flow_tbl_rd_op_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_u *value);

sw_error_t
hppe_in_flow_tbl_rd_op_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_u *value);

sw_error_t
hppe_in_flow_host_tbl_rd_op_get(
		a_uint32_t dev_id,
		union in_flow_host_tbl_rd_op_u *value);

sw_error_t
hppe_in_flow_host_tbl_rd_op_set(
		a_uint32_t dev_id,
		union in_flow_host_tbl_rd_op_u *value);

sw_error_t
hppe_in_flow_tbl_rd_op_data0_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data0_u *value);

sw_error_t
hppe_in_flow_tbl_rd_op_data0_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data0_u *value);

sw_error_t
hppe_in_flow_tbl_rd_op_data1_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data1_u *value);

sw_error_t
hppe_in_flow_tbl_rd_op_data1_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data1_u *value);

sw_error_t
hppe_in_flow_tbl_rd_op_data2_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data2_u *value);

sw_error_t
hppe_in_flow_tbl_rd_op_data2_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data2_u *value);

sw_error_t
hppe_in_flow_tbl_rd_op_data3_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data3_u *value);

sw_error_t
hppe_in_flow_tbl_rd_op_data3_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data3_u *value);

sw_error_t
hppe_in_flow_tbl_rd_op_data4_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data4_u *value);

sw_error_t
hppe_in_flow_tbl_rd_op_data4_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data4_u *value);

sw_error_t
hppe_in_flow_tbl_rd_op_data5_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data5_u *value);

sw_error_t
hppe_in_flow_tbl_rd_op_data5_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data5_u *value);

sw_error_t
hppe_in_flow_tbl_rd_op_data6_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data6_u *value);

sw_error_t
hppe_in_flow_tbl_rd_op_data6_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data6_u *value);

sw_error_t
hppe_in_flow_tbl_rd_op_data7_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data7_u *value);

sw_error_t
hppe_in_flow_tbl_rd_op_data7_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data7_u *value);

sw_error_t
hppe_in_flow_tbl_rd_op_data8_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data8_u *value);

sw_error_t
hppe_in_flow_tbl_rd_op_data8_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_data8_u *value);

sw_error_t
hppe_flow_host_tbl_rd_op_data0_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data0_u *value);

sw_error_t
hppe_flow_host_tbl_rd_op_data0_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data0_u *value);

sw_error_t
hppe_flow_host_tbl_rd_op_data1_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data1_u *value);

sw_error_t
hppe_flow_host_tbl_rd_op_data1_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data1_u *value);

sw_error_t
hppe_flow_host_tbl_rd_op_data2_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data2_u *value);

sw_error_t
hppe_flow_host_tbl_rd_op_data2_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data2_u *value);

sw_error_t
hppe_flow_host_tbl_rd_op_data3_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data3_u *value);

sw_error_t
hppe_flow_host_tbl_rd_op_data3_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data3_u *value);

sw_error_t
hppe_flow_host_tbl_rd_op_data4_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data4_u *value);

sw_error_t
hppe_flow_host_tbl_rd_op_data4_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data4_u *value);

sw_error_t
hppe_flow_host_tbl_rd_op_data5_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data5_u *value);

sw_error_t
hppe_flow_host_tbl_rd_op_data5_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data5_u *value);

sw_error_t
hppe_flow_host_tbl_rd_op_data6_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data6_u *value);

sw_error_t
hppe_flow_host_tbl_rd_op_data6_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data6_u *value);

sw_error_t
hppe_flow_host_tbl_rd_op_data7_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data7_u *value);

sw_error_t
hppe_flow_host_tbl_rd_op_data7_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data7_u *value);

sw_error_t
hppe_flow_host_tbl_rd_op_data8_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data8_u *value);

sw_error_t
hppe_flow_host_tbl_rd_op_data8_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data8_u *value);

sw_error_t
hppe_flow_host_tbl_rd_op_data9_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data9_u *value);

sw_error_t
hppe_flow_host_tbl_rd_op_data9_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_data9_u *value);

sw_error_t
hppe_in_flow_tbl_rd_op_rslt_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_rslt_u *value);

sw_error_t
hppe_in_flow_tbl_rd_op_rslt_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_op_rslt_u *value);

sw_error_t
hppe_flow_host_tbl_rd_op_rslt_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_rslt_u *value);

sw_error_t
hppe_flow_host_tbl_rd_op_rslt_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_op_rslt_u *value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data0_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data0_u *value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data0_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data0_u *value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data1_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data1_u *value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data1_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data1_u *value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data2_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data2_u *value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data2_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data2_u *value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data3_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data3_u *value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data3_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data3_u *value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data4_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data4_u *value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data4_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data4_u *value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data5_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data5_u *value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data5_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data5_u *value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data6_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data6_u *value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data6_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data6_u *value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data7_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data7_u *value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data7_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data7_u *value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data8_get(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data8_u *value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data8_set(
		a_uint32_t dev_id,
		union in_flow_tbl_rd_rslt_data8_u *value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data0_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data0_u *value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data0_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data0_u *value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data1_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data1_u *value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data1_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data1_u *value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data2_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data2_u *value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data2_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data2_u *value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data3_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data3_u *value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data3_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data3_u *value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data4_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data4_u *value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data4_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data4_u *value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data5_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data5_u *value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data5_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data5_u *value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data6_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data6_u *value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data6_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data6_u *value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data7_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data7_u *value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data7_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data7_u *value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data8_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data8_u *value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data8_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data8_u *value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data9_get(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data9_u *value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data9_set(
		a_uint32_t dev_id,
		union flow_host_tbl_rd_rslt_data9_u *value);

sw_error_t
hppe_host_tbl_op_get(
		a_uint32_t dev_id,
		union host_tbl_op_u *value);

sw_error_t
hppe_host_tbl_op_set(
		a_uint32_t dev_id,
		union host_tbl_op_u *value);

sw_error_t
hppe_host_tbl_op_data0_get(
		a_uint32_t dev_id,
		union host_tbl_op_data0_u *value);

sw_error_t
hppe_host_tbl_op_data0_set(
		a_uint32_t dev_id,
		union host_tbl_op_data0_u *value);

sw_error_t
hppe_host_tbl_op_data1_get(
		a_uint32_t dev_id,
		union host_tbl_op_data1_u *value);

sw_error_t
hppe_host_tbl_op_data1_set(
		a_uint32_t dev_id,
		union host_tbl_op_data1_u *value);

sw_error_t
hppe_host_tbl_op_data2_get(
		a_uint32_t dev_id,
		union host_tbl_op_data2_u *value);

sw_error_t
hppe_host_tbl_op_data2_set(
		a_uint32_t dev_id,
		union host_tbl_op_data2_u *value);

sw_error_t
hppe_host_tbl_op_data3_get(
		a_uint32_t dev_id,
		union host_tbl_op_data3_u *value);

sw_error_t
hppe_host_tbl_op_data3_set(
		a_uint32_t dev_id,
		union host_tbl_op_data3_u *value);

sw_error_t
hppe_host_tbl_op_data4_get(
		a_uint32_t dev_id,
		union host_tbl_op_data4_u *value);

sw_error_t
hppe_host_tbl_op_data4_set(
		a_uint32_t dev_id,
		union host_tbl_op_data4_u *value);

sw_error_t
hppe_host_tbl_op_data5_get(
		a_uint32_t dev_id,
		union host_tbl_op_data5_u *value);

sw_error_t
hppe_host_tbl_op_data5_set(
		a_uint32_t dev_id,
		union host_tbl_op_data5_u *value);

sw_error_t
hppe_host_tbl_op_data6_get(
		a_uint32_t dev_id,
		union host_tbl_op_data6_u *value);

sw_error_t
hppe_host_tbl_op_data6_set(
		a_uint32_t dev_id,
		union host_tbl_op_data6_u *value);

sw_error_t
hppe_host_tbl_op_data7_get(
		a_uint32_t dev_id,
		union host_tbl_op_data7_u *value);

sw_error_t
hppe_host_tbl_op_data7_set(
		a_uint32_t dev_id,
		union host_tbl_op_data7_u *value);

sw_error_t
hppe_host_tbl_op_data8_get(
		a_uint32_t dev_id,
		union host_tbl_op_data8_u *value);

sw_error_t
hppe_host_tbl_op_data8_set(
		a_uint32_t dev_id,
		union host_tbl_op_data8_u *value);

sw_error_t
hppe_host_tbl_op_data9_get(
		a_uint32_t dev_id,
		union host_tbl_op_data9_u *value);

sw_error_t
hppe_host_tbl_op_data9_set(
		a_uint32_t dev_id,
		union host_tbl_op_data9_u *value);

sw_error_t
hppe_host_tbl_op_rslt_get(
		a_uint32_t dev_id,
		union host_tbl_op_rslt_u *value);

sw_error_t
hppe_host_tbl_op_rslt_set(
		a_uint32_t dev_id,
		union host_tbl_op_rslt_u *value);

sw_error_t
hppe_host_tbl_rd_op_get(
		a_uint32_t dev_id,
		union host_tbl_rd_op_u *value);

sw_error_t
hppe_host_tbl_rd_op_set(
		a_uint32_t dev_id,
		union host_tbl_rd_op_u *value);

sw_error_t
hppe_host_tbl_rd_op_data0_get(
		a_uint32_t dev_id,
		union host_tbl_rd_op_data0_u *value);

sw_error_t
hppe_host_tbl_rd_op_data0_set(
		a_uint32_t dev_id,
		union host_tbl_rd_op_data0_u *value);

sw_error_t
hppe_host_tbl_rd_op_data1_get(
		a_uint32_t dev_id,
		union host_tbl_rd_op_data1_u *value);

sw_error_t
hppe_host_tbl_rd_op_data1_set(
		a_uint32_t dev_id,
		union host_tbl_rd_op_data1_u *value);

sw_error_t
hppe_host_tbl_rd_op_data2_get(
		a_uint32_t dev_id,
		union host_tbl_rd_op_data2_u *value);

sw_error_t
hppe_host_tbl_rd_op_data2_set(
		a_uint32_t dev_id,
		union host_tbl_rd_op_data2_u *value);

sw_error_t
hppe_host_tbl_rd_op_data3_get(
		a_uint32_t dev_id,
		union host_tbl_rd_op_data3_u *value);

sw_error_t
hppe_host_tbl_rd_op_data3_set(
		a_uint32_t dev_id,
		union host_tbl_rd_op_data3_u *value);

sw_error_t
hppe_host_tbl_rd_op_data4_get(
		a_uint32_t dev_id,
		union host_tbl_rd_op_data4_u *value);

sw_error_t
hppe_host_tbl_rd_op_data4_set(
		a_uint32_t dev_id,
		union host_tbl_rd_op_data4_u *value);

sw_error_t
hppe_host_tbl_rd_op_data5_get(
		a_uint32_t dev_id,
		union host_tbl_rd_op_data5_u *value);

sw_error_t
hppe_host_tbl_rd_op_data5_set(
		a_uint32_t dev_id,
		union host_tbl_rd_op_data5_u *value);

sw_error_t
hppe_host_tbl_rd_op_data6_get(
		a_uint32_t dev_id,
		union host_tbl_rd_op_data6_u *value);

sw_error_t
hppe_host_tbl_rd_op_data6_set(
		a_uint32_t dev_id,
		union host_tbl_rd_op_data6_u *value);

sw_error_t
hppe_host_tbl_rd_op_data7_get(
		a_uint32_t dev_id,
		union host_tbl_rd_op_data7_u *value);

sw_error_t
hppe_host_tbl_rd_op_data7_set(
		a_uint32_t dev_id,
		union host_tbl_rd_op_data7_u *value);

sw_error_t
hppe_host_tbl_rd_op_data8_get(
		a_uint32_t dev_id,
		union host_tbl_rd_op_data8_u *value);

sw_error_t
hppe_host_tbl_rd_op_data8_set(
		a_uint32_t dev_id,
		union host_tbl_rd_op_data8_u *value);

sw_error_t
hppe_host_tbl_rd_op_data9_get(
		a_uint32_t dev_id,
		union host_tbl_rd_op_data9_u *value);

sw_error_t
hppe_host_tbl_rd_op_data9_set(
		a_uint32_t dev_id,
		union host_tbl_rd_op_data9_u *value);

sw_error_t
hppe_host_tbl_rd_op_rslt_get(
		a_uint32_t dev_id,
		union host_tbl_rd_op_rslt_u *value);

sw_error_t
hppe_host_tbl_rd_op_rslt_set(
		a_uint32_t dev_id,
		union host_tbl_rd_op_rslt_u *value);

sw_error_t
hppe_host_tbl_rd_rslt_data0_get(
		a_uint32_t dev_id,
		union host_tbl_rd_rslt_data0_u *value);

sw_error_t
hppe_host_tbl_rd_rslt_data0_set(
		a_uint32_t dev_id,
		union host_tbl_rd_rslt_data0_u *value);

sw_error_t
hppe_host_tbl_rd_rslt_data1_get(
		a_uint32_t dev_id,
		union host_tbl_rd_rslt_data1_u *value);

sw_error_t
hppe_host_tbl_rd_rslt_data1_set(
		a_uint32_t dev_id,
		union host_tbl_rd_rslt_data1_u *value);

sw_error_t
hppe_host_tbl_rd_rslt_data2_get(
		a_uint32_t dev_id,
		union host_tbl_rd_rslt_data2_u *value);

sw_error_t
hppe_host_tbl_rd_rslt_data2_set(
		a_uint32_t dev_id,
		union host_tbl_rd_rslt_data2_u *value);

sw_error_t
hppe_host_tbl_rd_rslt_data3_get(
		a_uint32_t dev_id,
		union host_tbl_rd_rslt_data3_u *value);

sw_error_t
hppe_host_tbl_rd_rslt_data3_set(
		a_uint32_t dev_id,
		union host_tbl_rd_rslt_data3_u *value);

sw_error_t
hppe_host_tbl_rd_rslt_data4_get(
		a_uint32_t dev_id,
		union host_tbl_rd_rslt_data4_u *value);

sw_error_t
hppe_host_tbl_rd_rslt_data4_set(
		a_uint32_t dev_id,
		union host_tbl_rd_rslt_data4_u *value);

sw_error_t
hppe_host_tbl_rd_rslt_data5_get(
		a_uint32_t dev_id,
		union host_tbl_rd_rslt_data5_u *value);

sw_error_t
hppe_host_tbl_rd_rslt_data5_set(
		a_uint32_t dev_id,
		union host_tbl_rd_rslt_data5_u *value);

sw_error_t
hppe_host_tbl_rd_rslt_data6_get(
		a_uint32_t dev_id,
		union host_tbl_rd_rslt_data6_u *value);

sw_error_t
hppe_host_tbl_rd_rslt_data6_set(
		a_uint32_t dev_id,
		union host_tbl_rd_rslt_data6_u *value);

sw_error_t
hppe_host_tbl_rd_rslt_data7_get(
		a_uint32_t dev_id,
		union host_tbl_rd_rslt_data7_u *value);

sw_error_t
hppe_host_tbl_rd_rslt_data7_set(
		a_uint32_t dev_id,
		union host_tbl_rd_rslt_data7_u *value);

sw_error_t
hppe_host_tbl_rd_rslt_data8_get(
		a_uint32_t dev_id,
		union host_tbl_rd_rslt_data8_u *value);

sw_error_t
hppe_host_tbl_rd_rslt_data8_set(
		a_uint32_t dev_id,
		union host_tbl_rd_rslt_data8_u *value);

sw_error_t
hppe_host_tbl_rd_rslt_data9_get(
		a_uint32_t dev_id,
		union host_tbl_rd_rslt_data9_u *value);

sw_error_t
hppe_host_tbl_rd_rslt_data9_set(
		a_uint32_t dev_id,
		union host_tbl_rd_rslt_data9_u *value);

sw_error_t
hppe_l3_exception_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union l3_exception_cmd_u *value);

sw_error_t
hppe_l3_exception_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union l3_exception_cmd_u *value);

sw_error_t
hppe_l3_exp_l3_only_ctrl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union l3_exp_l3_only_ctrl_u *value);

sw_error_t
hppe_l3_exp_l3_only_ctrl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union l3_exp_l3_only_ctrl_u *value);

sw_error_t
hppe_l3_exp_l2_only_ctrl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union l3_exp_l2_only_ctrl_u *value);

sw_error_t
hppe_l3_exp_l2_only_ctrl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union l3_exp_l2_only_ctrl_u *value);

sw_error_t
hppe_l3_exp_l2_flow_ctrl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union l3_exp_l2_flow_ctrl_u *value);

sw_error_t
hppe_l3_exp_l2_flow_ctrl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union l3_exp_l2_flow_ctrl_u *value);

sw_error_t
hppe_l3_exp_l3_flow_ctrl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union l3_exp_l3_flow_ctrl_u *value);

sw_error_t
hppe_l3_exp_l3_flow_ctrl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union l3_exp_l3_flow_ctrl_u *value);

sw_error_t
hppe_l3_exp_multicast_ctrl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union l3_exp_multicast_ctrl_u *value);

sw_error_t
hppe_l3_exp_multicast_ctrl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union l3_exp_multicast_ctrl_u *value);

sw_error_t
hppe_l3_dbg_cmd_get(
		a_uint32_t dev_id,
		union l3_dbg_cmd_u *value);

sw_error_t
hppe_l3_dbg_cmd_set(
		a_uint32_t dev_id,
		union l3_dbg_cmd_u *value);

sw_error_t
hppe_l3_dbg_wr_data_get(
		a_uint32_t dev_id,
		union l3_dbg_wr_data_u *value);

sw_error_t
hppe_l3_dbg_wr_data_set(
		a_uint32_t dev_id,
		union l3_dbg_wr_data_u *value);

sw_error_t
hppe_l3_dbg_rd_data_get(
		a_uint32_t dev_id,
		union l3_dbg_rd_data_u *value);

sw_error_t
hppe_l3_dbg_rd_data_set(
		a_uint32_t dev_id,
		union l3_dbg_rd_data_u *value);

sw_error_t
hppe_l3_vp_port_tbl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union l3_vp_port_tbl_u *value);

sw_error_t
hppe_l3_vp_port_tbl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union l3_vp_port_tbl_u *value);

sw_error_t
hppe_in_l3_if_tbl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union in_l3_if_tbl_u *value);

sw_error_t
hppe_in_l3_if_tbl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union in_l3_if_tbl_u *value);

sw_error_t
hppe_host_ipv6_mcast_tbl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union host_ipv6_mcast_tbl_u *value);

sw_error_t
hppe_host_ipv6_mcast_tbl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union host_ipv6_mcast_tbl_u *value);

sw_error_t
hppe_host_ipv4_mcast_tbl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union host_ipv4_mcast_tbl_u *value);

sw_error_t
hppe_host_ipv4_mcast_tbl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union host_ipv4_mcast_tbl_u *value);

sw_error_t
hppe_host_tbl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union host_tbl_u *value);

sw_error_t
hppe_host_tbl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union host_tbl_u *value);

sw_error_t
hppe_host_ipv6_tbl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union host_ipv6_tbl_u *value);

sw_error_t
hppe_host_ipv6_tbl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union host_ipv6_tbl_u *value);

sw_error_t
hppe_in_flow_3tuple_tbl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union in_flow_3tuple_tbl_u *value);

sw_error_t
hppe_in_flow_3tuple_tbl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union in_flow_3tuple_tbl_u *value);

sw_error_t
hppe_in_flow_ipv6_3tuple_tbl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union in_flow_ipv6_3tuple_tbl_u *value);

sw_error_t
hppe_in_flow_ipv6_3tuple_tbl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union in_flow_ipv6_3tuple_tbl_u *value);

sw_error_t
hppe_in_flow_ipv6_5tuple_tbl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union in_flow_ipv6_5tuple_tbl_u *value);

sw_error_t
hppe_in_flow_ipv6_5tuple_tbl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union in_flow_ipv6_5tuple_tbl_u *value);

sw_error_t
hppe_in_flow_tbl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union in_flow_tbl_u *value);

sw_error_t
hppe_in_flow_tbl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union in_flow_tbl_u *value);

sw_error_t
hppe_in_nexthop_tbl_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		union in_nexthop_tbl_u *value);

sw_error_t
hppe_in_nexthop_tbl_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		union in_nexthop_tbl_u *value);

sw_error_t
hppe_my_mac_tbl_mac_da_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint64_t *value);

sw_error_t
hppe_my_mac_tbl_mac_da_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint64_t value);

sw_error_t
hppe_my_mac_tbl_valid_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_my_mac_tbl_valid_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vsi_l3_if_index_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vsi_l3_if_index_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vsi_l2_ipv6_mc_mode_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vsi_l2_ipv6_mc_mode_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vsi_l3_if_valid_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vsi_l3_if_valid_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vsi_l2_ipv6_mc_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vsi_l2_ipv6_mc_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vsi_l2_ipv4_mc_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vsi_l2_ipv4_mc_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vsi_l2_ipv4_mc_mode_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vsi_l2_ipv4_mc_mode_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vsi_ext_ip_arp_sg_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vsi_ext_ip_arp_sg_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vsi_ext_ipv6_sg_svlan_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vsi_ext_ipv6_sg_svlan_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vsi_ext_ip_nd_sg_cvlan_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vsi_ext_ip_nd_sg_cvlan_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vsi_ext_ip_nd_sg_vio_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vsi_ext_ip_nd_sg_vio_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vsi_ext_ipv4_sg_port_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vsi_ext_ipv4_sg_port_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vsi_ext_ip_nd_sg_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vsi_ext_ip_nd_sg_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vsi_ext_ipv4_sg_svlan_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vsi_ext_ipv4_sg_svlan_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vsi_ext_ipv4_sg_cvlan_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vsi_ext_ipv4_sg_cvlan_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vsi_ext_ip_arp_sg_svlan_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vsi_ext_ip_arp_sg_svlan_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vsi_ext_ip_nd_sg_svlan_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vsi_ext_ip_nd_sg_svlan_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vsi_ext_ipv6_sg_vio_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vsi_ext_ipv6_sg_vio_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vsi_ext_ip_nd_sg_port_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vsi_ext_ip_nd_sg_port_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vsi_ext_ip_arp_src_unk_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vsi_ext_ip_arp_src_unk_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vsi_ext_ipv6_sg_port_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vsi_ext_ipv6_sg_port_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vsi_ext_ipv4_src_unk_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vsi_ext_ipv4_src_unk_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vsi_ext_ip_arp_sg_vio_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vsi_ext_ip_arp_sg_vio_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vsi_ext_ip_arp_sg_port_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vsi_ext_ip_arp_sg_port_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vsi_ext_ipv4_sg_vio_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vsi_ext_ipv4_sg_vio_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vsi_ext_ipv6_src_unk_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vsi_ext_ipv6_src_unk_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vsi_ext_ipv6_sg_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vsi_ext_ipv6_sg_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vsi_ext_ip_arp_sg_cvlan_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vsi_ext_ip_arp_sg_cvlan_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vsi_ext_ip_nd_src_unk_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vsi_ext_ip_nd_src_unk_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vsi_ext_ipv4_sg_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vsi_ext_ipv4_sg_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vsi_ext_ipv6_sg_cvlan_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vsi_ext_ipv6_sg_cvlan_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_network_route_ip_ip_addr_mask_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_network_route_ip_ip_addr_mask_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_network_route_ip_ip_addr_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_network_route_ip_ip_addr_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_network_route_ip_ext_entry_type_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_network_route_ip_ext_entry_type_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_network_route_ip_ext_valid_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_network_route_ip_ext_valid_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_network_route_action_lan_wan_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_network_route_action_lan_wan_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_network_route_action_fwd_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_network_route_action_fwd_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_network_route_action_dst_info_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_network_route_action_dst_info_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_route_ctrl_flow_src_if_check_de_acce_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_l3_route_ctrl_flow_src_if_check_de_acce_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_l3_route_ctrl_pppoe_multicast_cmd_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_l3_route_ctrl_pppoe_multicast_cmd_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_l3_route_ctrl_ip_mtu_fail_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_l3_route_ctrl_ip_mtu_fail_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_l3_route_ctrl_flow_src_if_check_cmd_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_l3_route_ctrl_flow_src_if_check_cmd_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_l3_route_ctrl_icmp_rdt_de_acce_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_l3_route_ctrl_icmp_rdt_de_acce_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_l3_route_ctrl_flow_de_acce_cmd_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_l3_route_ctrl_flow_de_acce_cmd_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_l3_route_ctrl_ip_mtu_fail_de_acce_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_l3_route_ctrl_ip_mtu_fail_de_acce_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_l3_route_ctrl_flow_sync_mismatch_cmd_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_l3_route_ctrl_flow_sync_mismatch_cmd_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_l3_route_ctrl_flow_service_code_loop_de_acce_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_l3_route_ctrl_flow_service_code_loop_de_acce_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_l3_route_ctrl_flow_sync_mismatch_de_acce_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_l3_route_ctrl_flow_sync_mismatch_de_acce_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_l3_route_ctrl_ip_mtu_df_fail_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_l3_route_ctrl_ip_mtu_df_fail_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_l3_route_ctrl_flow_service_code_loop_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_l3_route_ctrl_flow_service_code_loop_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_l3_route_ctrl_ip_mru_check_fail_de_acce_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_l3_route_ctrl_ip_mru_check_fail_de_acce_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_l3_route_ctrl_ip_prefix_bc_cmd_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_l3_route_ctrl_ip_prefix_bc_cmd_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_l3_route_ctrl_ip_mtu_df_fail_de_acce_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_l3_route_ctrl_ip_mtu_df_fail_de_acce_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_l3_route_ctrl_pppoe_multicast_de_acce_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_l3_route_ctrl_pppoe_multicast_de_acce_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_l3_route_ctrl_ip_mru_check_fail_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_l3_route_ctrl_ip_mru_check_fail_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_l3_route_ctrl_icmp_rdt_cmd_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_l3_route_ctrl_icmp_rdt_cmd_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_l3_route_ctrl_ip_prefix_bc_de_acce_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_l3_route_ctrl_ip_prefix_bc_de_acce_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_l3_route_ctrl_ext_flow_service_code_loop_en_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_l3_route_ctrl_ext_flow_service_code_loop_en_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_l3_route_ctrl_ext_host_hash_mode_0_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_l3_route_ctrl_ext_host_hash_mode_0_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_l3_route_ctrl_ext_host_hash_mode_1_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_l3_route_ctrl_ext_host_hash_mode_1_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_l3_route_ctrl_ext_ip_route_mismatch_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_l3_route_ctrl_ext_ip_route_mismatch_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_pppoe_session_session_id_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_pppoe_session_session_id_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_pppoe_session_l3_if_index_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_pppoe_session_l3_if_index_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_pppoe_session_port_bitmap_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_pppoe_session_port_bitmap_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_pppoe_session_ext_uc_valid_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_pppoe_session_ext_uc_valid_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_pppoe_session_ext_mc_valid_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_pppoe_session_ext_mc_valid_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_pppoe_session_ext_l3_if_valid_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_pppoe_session_ext_l3_if_valid_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_flow_ctrl0_flow_hash_mode_0_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_ctrl0_flow_hash_mode_0_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_ctrl0_flow_age_timer_unit_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_ctrl0_flow_age_timer_unit_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_ctrl0_flow_hash_mode_1_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_ctrl0_flow_hash_mode_1_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_ctrl0_flow_age_timer_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_ctrl0_flow_age_timer_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_ctrl0_flow_en_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_ctrl0_flow_en_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_ctrl1_flow_ctl1_frag_bypass_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_flow_ctrl1_flow_ctl1_frag_bypass_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_flow_ctrl1_flow_ctl4_key_sel_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_flow_ctrl1_flow_ctl4_key_sel_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_flow_ctrl1_flow_ctl1_key_sel_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_flow_ctrl1_flow_ctl1_key_sel_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_flow_ctrl1_flow_ctl0_frag_bypass_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_flow_ctrl1_flow_ctl0_frag_bypass_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_flow_ctrl1_flow_ctl0_miss_action_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_flow_ctrl1_flow_ctl0_miss_action_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_flow_ctrl1_flow_ctl0_key_sel_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_flow_ctrl1_flow_ctl0_key_sel_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_flow_ctrl1_flow_ctl1_bypass_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_flow_ctrl1_flow_ctl1_bypass_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_flow_ctrl1_flow_ctl0_bypass_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_flow_ctrl1_flow_ctl0_bypass_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_flow_ctrl1_flow_ctl2_tcp_special_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_flow_ctrl1_flow_ctl2_tcp_special_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_flow_ctrl1_flow_ctl4_tcp_special_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_flow_ctrl1_flow_ctl4_tcp_special_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_flow_ctrl1_flow_ctl3_frag_bypass_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_flow_ctrl1_flow_ctl3_frag_bypass_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_flow_ctrl1_flow_ctl3_bypass_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_flow_ctrl1_flow_ctl3_bypass_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_flow_ctrl1_flow_ctl3_tcp_special_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_flow_ctrl1_flow_ctl3_tcp_special_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_flow_ctrl1_flow_ctl1_miss_action_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_flow_ctrl1_flow_ctl1_miss_action_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_flow_ctrl1_flow_ctl4_frag_bypass_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_flow_ctrl1_flow_ctl4_frag_bypass_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_flow_ctrl1_flow_ctl1_tcp_special_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_flow_ctrl1_flow_ctl1_tcp_special_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_flow_ctrl1_flow_ctl2_key_sel_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_flow_ctrl1_flow_ctl2_key_sel_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_flow_ctrl1_flow_ctl2_miss_action_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_flow_ctrl1_flow_ctl2_miss_action_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_flow_ctrl1_flow_ctl2_bypass_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_flow_ctrl1_flow_ctl2_bypass_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_flow_ctrl1_flow_ctl4_bypass_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_flow_ctrl1_flow_ctl4_bypass_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_flow_ctrl1_flow_ctl3_key_sel_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_flow_ctrl1_flow_ctl3_key_sel_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_flow_ctrl1_flow_ctl0_tcp_special_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_flow_ctrl1_flow_ctl0_tcp_special_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_flow_ctrl1_flow_ctl2_frag_bypass_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_flow_ctrl1_flow_ctl2_frag_bypass_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_flow_ctrl1_flow_ctl3_miss_action_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_flow_ctrl1_flow_ctl3_miss_action_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_flow_ctrl1_flow_ctl4_miss_action_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_flow_ctrl1_flow_ctl4_miss_action_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_in_pub_ip_addr_tbl_ip_addr_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_in_pub_ip_addr_tbl_ip_addr_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_in_flow_tbl_op_entry_index_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_op_entry_index_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_op_cmd_id_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_op_cmd_id_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_op_byp_rslt_en_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_op_byp_rslt_en_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_op_op_mode_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_op_op_mode_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_op_op_type_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_op_op_type_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_op_op_host_en_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_op_op_host_en_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_op_op_result_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_op_op_result_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_op_busy_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_op_busy_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_op_hash_block_bitmap_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_op_hash_block_bitmap_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_host_tbl_op_host_entry_index_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_host_tbl_op_host_entry_index_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_host_tbl_op_hash_block_bitmap_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_host_tbl_op_hash_block_bitmap_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_op_data0_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_op_data0_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_op_data1_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_op_data1_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_op_data2_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_op_data2_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_op_data3_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_op_data3_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_op_data4_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_op_data4_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_op_data5_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_op_data5_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_op_data6_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_op_data6_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_op_data7_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_op_data7_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_op_data8_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_op_data8_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_op_data0_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_op_data0_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_op_data1_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_op_data1_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_op_data2_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_op_data2_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_op_data3_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_op_data3_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_op_data4_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_op_data4_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_op_data5_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_op_data5_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_op_data6_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_op_data6_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_op_data7_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_op_data7_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_op_data8_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_op_data8_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_op_data9_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_op_data9_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_op_rslt_op_rslt_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_op_rslt_op_rslt_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_op_rslt_valid_cnt_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_op_rslt_valid_cnt_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_op_rslt_flow_entry_index_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_op_rslt_flow_entry_index_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_op_rslt_cmd_id_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_op_rslt_cmd_id_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_op_rslt_host_entry_index_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_op_rslt_host_entry_index_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_rd_op_entry_index_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_rd_op_entry_index_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_rd_op_cmd_id_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_rd_op_cmd_id_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_rd_op_byp_rslt_en_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_rd_op_byp_rslt_en_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_rd_op_op_mode_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_rd_op_op_mode_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_rd_op_op_type_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_rd_op_op_type_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_rd_op_op_host_en_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_rd_op_op_host_en_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_rd_op_op_result_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_rd_op_op_result_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_rd_op_busy_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_rd_op_busy_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_rd_op_hash_block_bitmap_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_rd_op_hash_block_bitmap_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_host_tbl_rd_op_host_entry_index_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_host_tbl_rd_op_host_entry_index_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_host_tbl_rd_op_hash_block_bitmap_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_host_tbl_rd_op_hash_block_bitmap_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_rd_op_data0_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_rd_op_data0_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_rd_op_data1_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_rd_op_data1_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_rd_op_data2_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_rd_op_data2_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_rd_op_data3_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_rd_op_data3_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_rd_op_data4_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_rd_op_data4_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_rd_op_data5_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_rd_op_data5_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_rd_op_data6_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_rd_op_data6_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_rd_op_data7_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_rd_op_data7_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_rd_op_data8_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_rd_op_data8_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_rd_op_data0_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_rd_op_data0_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_rd_op_data1_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_rd_op_data1_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_rd_op_data2_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_rd_op_data2_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_rd_op_data3_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_rd_op_data3_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_rd_op_data4_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_rd_op_data4_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_rd_op_data5_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_rd_op_data5_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_rd_op_data6_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_rd_op_data6_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_rd_op_data7_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_rd_op_data7_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_rd_op_data8_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_rd_op_data8_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_rd_op_data9_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_rd_op_data9_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_rd_op_rslt_op_rslt_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_rd_op_rslt_op_rslt_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_rd_op_rslt_valid_cnt_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_rd_op_rslt_valid_cnt_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_rd_op_rslt_flow_entry_index_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_rd_op_rslt_flow_entry_index_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_rd_op_rslt_cmd_id_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_rd_op_rslt_cmd_id_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_rd_op_rslt_host_entry_index_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_rd_op_rslt_host_entry_index_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data0_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data0_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data1_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data1_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data2_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data2_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data3_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data3_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data4_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data4_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data5_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data5_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data6_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data6_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data7_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data7_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data8_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_in_flow_tbl_rd_rslt_data8_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data0_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data0_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data1_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data1_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data2_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data2_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data3_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data3_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data4_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data4_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data5_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data5_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data6_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data6_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data7_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data7_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data8_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data8_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data9_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_flow_host_tbl_rd_rslt_data9_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_op_entry_index_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_op_entry_index_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_op_cmd_id_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_op_cmd_id_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_op_byp_rslt_en_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_op_byp_rslt_en_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_op_op_mode_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_op_op_mode_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_op_op_type_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_op_op_type_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_op_op_result_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_op_op_result_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_op_busy_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_op_busy_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_op_hash_block_bitmap_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_op_hash_block_bitmap_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_op_data0_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_op_data0_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_op_data1_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_op_data1_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_op_data2_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_op_data2_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_op_data3_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_op_data3_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_op_data4_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_op_data4_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_op_data5_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_op_data5_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_op_data6_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_op_data6_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_op_data7_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_op_data7_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_op_data8_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_op_data8_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_op_data9_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_op_data9_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_op_rslt_op_rslt_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_op_rslt_op_rslt_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_op_rslt_valid_cnt_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_op_rslt_valid_cnt_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_op_rslt_entry_index_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_op_rslt_entry_index_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_op_rslt_cmd_id_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_op_rslt_cmd_id_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_op_entry_index_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_op_entry_index_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_op_cmd_id_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_op_cmd_id_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_op_byp_rslt_en_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_op_byp_rslt_en_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_op_op_mode_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_op_op_mode_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_op_op_type_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_op_op_type_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_op_op_result_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_op_op_result_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_op_busy_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_op_busy_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_op_hash_block_bitmap_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_op_hash_block_bitmap_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_op_data0_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_op_data0_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_op_data1_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_op_data1_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_op_data2_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_op_data2_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_op_data3_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_op_data3_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_op_data4_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_op_data4_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_op_data5_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_op_data5_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_op_data6_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_op_data6_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_op_data7_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_op_data7_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_op_data8_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_op_data8_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_op_data9_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_op_data9_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_op_rslt_op_rslt_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_op_rslt_op_rslt_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_op_rslt_valid_cnt_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_op_rslt_valid_cnt_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_op_rslt_entry_index_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_op_rslt_entry_index_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_op_rslt_cmd_id_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_op_rslt_cmd_id_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_rslt_data0_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_rslt_data0_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_rslt_data1_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_rslt_data1_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_rslt_data2_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_rslt_data2_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_rslt_data3_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_rslt_data3_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_rslt_data4_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_rslt_data4_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_rslt_data5_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_rslt_data5_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_rslt_data6_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_rslt_data6_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_rslt_data7_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_rslt_data7_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_rslt_data8_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_rslt_data8_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_host_tbl_rd_rslt_data9_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_host_tbl_rd_rslt_data9_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_l3_exception_cmd_l3_excep_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_exception_cmd_l3_excep_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_exception_cmd_de_acce_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_exception_cmd_de_acce_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_exp_l3_only_ctrl_excep_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_exp_l3_only_ctrl_excep_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_exp_l2_only_ctrl_excep_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_exp_l2_only_ctrl_excep_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_exp_l2_flow_ctrl_excep_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_exp_l2_flow_ctrl_excep_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_exp_l3_flow_ctrl_excep_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_exp_l3_flow_ctrl_excep_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_exp_multicast_ctrl_excep_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_exp_multicast_ctrl_excep_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_dbg_cmd_type_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_l3_dbg_cmd_type_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_l3_dbg_cmd_addr_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_l3_dbg_cmd_addr_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_l3_dbg_wr_data_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_l3_dbg_wr_data_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_l3_dbg_rd_data_data_get(
		a_uint32_t dev_id,
		unsigned int *value);

sw_error_t
hppe_l3_dbg_rd_data_data_set(
		a_uint32_t dev_id,
		unsigned int value);

sw_error_t
hppe_l3_vp_port_tbl_ip_arp_sg_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vp_port_tbl_ip_arp_sg_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vp_port_tbl_ipv6_sg_svlan_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vp_port_tbl_ipv6_sg_svlan_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vp_port_tbl_ip_nd_sg_cvlan_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vp_port_tbl_ip_nd_sg_cvlan_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vp_port_tbl_l3_if_valid_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vp_port_tbl_l3_if_valid_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vp_port_tbl_ip_nd_sg_vio_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vp_port_tbl_ip_nd_sg_vio_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vp_port_tbl_ipv4_sg_port_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vp_port_tbl_ipv4_sg_port_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vp_port_tbl_ip_nd_sg_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vp_port_tbl_ip_nd_sg_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vp_port_tbl_l3_if_index_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vp_port_tbl_l3_if_index_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vp_port_tbl_ipv4_sg_svlan_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vp_port_tbl_ipv4_sg_svlan_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vp_port_tbl_ipv4_sg_cvlan_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vp_port_tbl_ipv4_sg_cvlan_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vp_port_tbl_ip_arp_sg_svlan_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vp_port_tbl_ip_arp_sg_svlan_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vp_port_tbl_mac_valid_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vp_port_tbl_mac_valid_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vp_port_tbl_ip_nd_sg_svlan_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vp_port_tbl_ip_nd_sg_svlan_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vp_port_tbl_vsi_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vp_port_tbl_vsi_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vp_port_tbl_mac_da_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint64_t *value);

sw_error_t
hppe_l3_vp_port_tbl_mac_da_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint64_t value);

sw_error_t
hppe_l3_vp_port_tbl_ipv6_sg_vio_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vp_port_tbl_ipv6_sg_vio_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vp_port_tbl_ip_nd_sg_port_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vp_port_tbl_ip_nd_sg_port_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vp_port_tbl_ip_arp_src_unk_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vp_port_tbl_ip_arp_src_unk_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vp_port_tbl_ipv6_sg_port_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vp_port_tbl_ipv6_sg_port_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vp_port_tbl_ipv4_src_unk_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vp_port_tbl_ipv4_src_unk_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vp_port_tbl_ip_arp_sg_port_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vp_port_tbl_ip_arp_sg_port_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vp_port_tbl_ip_arp_sg_vio_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vp_port_tbl_ip_arp_sg_vio_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vp_port_tbl_ipv4_sg_vio_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vp_port_tbl_ipv4_sg_vio_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vp_port_tbl_ipv6_src_unk_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vp_port_tbl_ipv6_src_unk_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vp_port_tbl_ip_arp_sg_cvlan_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vp_port_tbl_ip_arp_sg_cvlan_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vp_port_tbl_ipv6_sg_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vp_port_tbl_ipv6_sg_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vp_port_tbl_vsi_valid_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vp_port_tbl_vsi_valid_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vp_port_tbl_ip_nd_src_unk_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vp_port_tbl_ip_nd_src_unk_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vp_port_tbl_ipv4_sg_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vp_port_tbl_ipv4_sg_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_l3_vp_port_tbl_ipv6_sg_cvlan_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_l3_vp_port_tbl_ipv6_sg_cvlan_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_in_l3_if_tbl_ttl_dec_bypass_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_in_l3_if_tbl_ttl_dec_bypass_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_in_l3_if_tbl_ttl_exceed_cmd_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_in_l3_if_tbl_ttl_exceed_cmd_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_in_l3_if_tbl_mru_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_in_l3_if_tbl_mru_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_in_l3_if_tbl_ipv4_uc_route_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_in_l3_if_tbl_ipv4_uc_route_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_in_l3_if_tbl_ipv6_uc_route_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_in_l3_if_tbl_ipv6_uc_route_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_in_l3_if_tbl_ttl_exceed_de_acce_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_in_l3_if_tbl_ttl_exceed_de_acce_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_in_l3_if_tbl_icmp_trigger_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_in_l3_if_tbl_icmp_trigger_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_in_l3_if_tbl_mac_bitmap_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_in_l3_if_tbl_mac_bitmap_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_in_l3_if_tbl_pppoe_en_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_in_l3_if_tbl_pppoe_en_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_in_l3_if_tbl_mtu_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_in_l3_if_tbl_mtu_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_in_nexthop_tbl_ip_pub_addr_index_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_in_nexthop_tbl_ip_pub_addr_index_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_in_nexthop_tbl_cvid_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_in_nexthop_tbl_cvid_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_in_nexthop_tbl_post_l3_if_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_in_nexthop_tbl_post_l3_if_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_in_nexthop_tbl_mac_addr_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint64_t *value);

sw_error_t
hppe_in_nexthop_tbl_mac_addr_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint64_t value);

sw_error_t
hppe_in_nexthop_tbl_port_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_in_nexthop_tbl_port_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_in_nexthop_tbl_ip_to_me_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_in_nexthop_tbl_ip_to_me_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_in_nexthop_tbl_ip_addr_dnat_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_in_nexthop_tbl_ip_addr_dnat_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_in_nexthop_tbl_type_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_in_nexthop_tbl_type_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_in_nexthop_tbl_stag_fmt_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_in_nexthop_tbl_stag_fmt_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_in_nexthop_tbl_vsi_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_in_nexthop_tbl_vsi_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_in_nexthop_tbl_svid_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_in_nexthop_tbl_svid_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

sw_error_t
hppe_in_nexthop_tbl_ctag_fmt_get(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t *value);

sw_error_t
hppe_in_nexthop_tbl_ctag_fmt_set(
		a_uint32_t dev_id,
		a_uint32_t index,
		a_uint32_t value);

#endif

