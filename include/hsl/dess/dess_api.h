/*
 * Copyright (c) 2012, The Linux Foundation. All rights reserved.
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



#ifndef _DESS_API_H_
#define _DESS_API_H_

#ifdef __cplusplus
extern "C" {
#endif                          /* __cplusplus */

#ifdef IN_VLAN
#define VLAN_API \
    SW_API_DEF(SW_API_VLAN_ADD, dess_vlan_create), \
    SW_API_DEF(SW_API_VLAN_DEL, dess_vlan_delete), \
    SW_API_DEF(SW_API_VLAN_FIND, dess_vlan_find), \
    SW_API_DEF(SW_API_VLAN_NEXT, dess_vlan_next), \
    SW_API_DEF(SW_API_VLAN_APPEND, dess_vlan_entry_append), \
    SW_API_DEF(SW_API_VLAN_FLUSH, dess_vlan_flush), \
    SW_API_DEF(SW_API_VLAN_FID_SET, dess_vlan_fid_set), \
    SW_API_DEF(SW_API_VLAN_FID_GET, dess_vlan_fid_get), \
    SW_API_DEF(SW_API_VLAN_MEMBER_ADD, dess_vlan_member_add), \
    SW_API_DEF(SW_API_VLAN_MEMBER_DEL, dess_vlan_member_del), \
    SW_API_DEF(SW_API_VLAN_LEARN_STATE_SET, dess_vlan_learning_state_set), \
    SW_API_DEF(SW_API_VLAN_LEARN_STATE_GET, dess_vlan_learning_state_get),

#define VLAN_API_PARAM \
    SW_API_DESC(SW_API_VLAN_ADD)     \
    SW_API_DESC(SW_API_VLAN_DEL)     \
    SW_API_DESC(SW_API_VLAN_FIND)    \
    SW_API_DESC(SW_API_VLAN_NEXT)    \
    SW_API_DESC(SW_API_VLAN_APPEND)  \
    SW_API_DESC(SW_API_VLAN_FLUSH)   \
    SW_API_DESC(SW_API_VLAN_FID_SET) \
    SW_API_DESC(SW_API_VLAN_FID_GET) \
    SW_API_DESC(SW_API_VLAN_MEMBER_ADD) \
    SW_API_DESC(SW_API_VLAN_MEMBER_DEL) \
    SW_API_DESC(SW_API_VLAN_LEARN_STATE_SET) \
    SW_API_DESC(SW_API_VLAN_LEARN_STATE_GET)
#else
#define VLAN_API
#define VLAN_API_PARAM
#endif

#ifdef IN_PORTVLAN
#define PORTVLAN_API \
    SW_API_DEF(SW_API_PT_ING_MODE_GET, dess_port_1qmode_get), \
    SW_API_DEF(SW_API_PT_ING_MODE_SET, dess_port_1qmode_set), \
    SW_API_DEF(SW_API_PT_EG_MODE_GET, dess_port_egvlanmode_get), \
    SW_API_DEF(SW_API_PT_EG_MODE_SET, dess_port_egvlanmode_set), \
    SW_API_DEF(SW_API_PT_VLAN_MEM_ADD, dess_portvlan_member_add), \
    SW_API_DEF(SW_API_PT_VLAN_MEM_DEL, dess_portvlan_member_del), \
    SW_API_DEF(SW_API_PT_VLAN_MEM_UPDATE, dess_portvlan_member_update), \
    SW_API_DEF(SW_API_PT_VLAN_MEM_GET, dess_portvlan_member_get), \
    SW_API_DEF(SW_API_PT_FORCE_DEF_VID_SET, dess_port_force_default_vid_set), \
    SW_API_DEF(SW_API_PT_FORCE_DEF_VID_GET, dess_port_force_default_vid_get), \
    SW_API_DEF(SW_API_PT_FORCE_PORTVLAN_SET, dess_port_force_portvlan_set), \
    SW_API_DEF(SW_API_PT_FORCE_PORTVLAN_GET, dess_port_force_portvlan_get), \
    SW_API_DEF(SW_API_NESTVLAN_TPID_SET, dess_nestvlan_tpid_set), \
    SW_API_DEF(SW_API_NESTVLAN_TPID_GET, dess_nestvlan_tpid_get), \
    SW_API_DEF(SW_API_PT_IN_VLAN_MODE_SET, dess_port_invlan_mode_set), \
    SW_API_DEF(SW_API_PT_IN_VLAN_MODE_GET, dess_port_invlan_mode_get), \
    SW_API_DEF(SW_API_PT_TLS_SET, dess_port_tls_set), \
    SW_API_DEF(SW_API_PT_TLS_GET, dess_port_tls_get), \
    SW_API_DEF(SW_API_PT_PRI_PROPAGATION_SET, dess_port_pri_propagation_set), \
    SW_API_DEF(SW_API_PT_PRI_PROPAGATION_GET, dess_port_pri_propagation_get), \
    SW_API_DEF(SW_API_PT_DEF_SVID_SET, dess_port_default_svid_set), \
    SW_API_DEF(SW_API_PT_DEF_SVID_GET, dess_port_default_svid_get), \
    SW_API_DEF(SW_API_PT_DEF_CVID_SET, dess_port_default_cvid_set), \
    SW_API_DEF(SW_API_PT_DEF_CVID_GET, dess_port_default_cvid_get), \
    SW_API_DEF(SW_API_PT_VLAN_PROPAGATION_SET, dess_port_vlan_propagation_set), \
    SW_API_DEF(SW_API_PT_VLAN_PROPAGATION_GET, dess_port_vlan_propagation_get), \
    SW_API_DEF(SW_API_PT_VLAN_TRANS_ADD, dess_port_vlan_trans_add), \
    SW_API_DEF(SW_API_PT_VLAN_TRANS_DEL, dess_port_vlan_trans_del), \
    SW_API_DEF(SW_API_PT_VLAN_TRANS_GET, dess_port_vlan_trans_get), \
    SW_API_DEF(SW_API_QINQ_MODE_SET, dess_qinq_mode_set), \
    SW_API_DEF(SW_API_QINQ_MODE_GET, dess_qinq_mode_get), \
    SW_API_DEF(SW_API_PT_QINQ_ROLE_SET, dess_port_qinq_role_set), \
    SW_API_DEF(SW_API_PT_QINQ_ROLE_GET, dess_port_qinq_role_get), \
    SW_API_DEF(SW_API_PT_VLAN_TRANS_ITERATE, dess_port_vlan_trans_iterate), \
    SW_API_DEF(SW_API_PT_MAC_VLAN_XLT_SET, dess_port_mac_vlan_xlt_set), \
    SW_API_DEF(SW_API_PT_MAC_VLAN_XLT_GET, dess_port_mac_vlan_xlt_get), \
    SW_API_DEF(SW_API_NETISOLATE_SET, dess_netisolate_set), \
    SW_API_DEF(SW_API_NETISOLATE_GET, dess_netisolate_get),\
    SW_API_DEF(SW_API_EG_FLTR_BYPASS_EN_SET, dess_eg_trans_filter_bypass_en_set), \
    SW_API_DEF(SW_API_EG_FLTR_BYPASS_EN_GET, dess_eg_trans_filter_bypass_en_get),


#define PORTVLAN_API_PARAM \
    SW_API_DESC(SW_API_PT_ING_MODE_GET)  \
    SW_API_DESC(SW_API_PT_ING_MODE_SET)  \
    SW_API_DESC(SW_API_PT_EG_MODE_GET)  \
    SW_API_DESC(SW_API_PT_EG_MODE_SET)  \
    SW_API_DESC(SW_API_PT_VLAN_MEM_ADD) \
    SW_API_DESC(SW_API_PT_VLAN_MEM_DEL) \
    SW_API_DESC(SW_API_PT_VLAN_MEM_UPDATE)  \
    SW_API_DESC(SW_API_PT_VLAN_MEM_GET)     \
    SW_API_DESC(SW_API_PT_FORCE_DEF_VID_SET)    \
    SW_API_DESC(SW_API_PT_FORCE_DEF_VID_GET)    \
    SW_API_DESC(SW_API_PT_FORCE_PORTVLAN_SET)   \
    SW_API_DESC(SW_API_PT_FORCE_PORTVLAN_GET)   \
    SW_API_DESC(SW_API_NESTVLAN_TPID_SET)    \
    SW_API_DESC(SW_API_NESTVLAN_TPID_GET)    \
    SW_API_DESC(SW_API_PT_IN_VLAN_MODE_SET)    \
    SW_API_DESC(SW_API_PT_IN_VLAN_MODE_GET)    \
    SW_API_DESC(SW_API_PT_TLS_SET)    \
    SW_API_DESC(SW_API_PT_TLS_GET)    \
    SW_API_DESC(SW_API_PT_PRI_PROPAGATION_SET)    \
    SW_API_DESC(SW_API_PT_PRI_PROPAGATION_GET)    \
    SW_API_DESC(SW_API_PT_DEF_SVID_SET)    \
    SW_API_DESC(SW_API_PT_DEF_SVID_GET)    \
    SW_API_DESC(SW_API_PT_DEF_CVID_SET)    \
    SW_API_DESC(SW_API_PT_DEF_CVID_GET)    \
    SW_API_DESC(SW_API_PT_VLAN_PROPAGATION_SET)    \
    SW_API_DESC(SW_API_PT_VLAN_PROPAGATION_GET)    \
    SW_API_DESC(SW_API_PT_VLAN_TRANS_ADD)  \
    SW_API_DESC(SW_API_PT_VLAN_TRANS_DEL)  \
    SW_API_DESC(SW_API_PT_VLAN_TRANS_GET)  \
    SW_API_DESC(SW_API_QINQ_MODE_SET)      \
    SW_API_DESC(SW_API_QINQ_MODE_GET)      \
    SW_API_DESC(SW_API_PT_QINQ_ROLE_SET)   \
    SW_API_DESC(SW_API_PT_QINQ_ROLE_GET)   \
    SW_API_DESC(SW_API_PT_VLAN_TRANS_ITERATE) \
    SW_API_DESC(SW_API_PT_MAC_VLAN_XLT_SET)   \
    SW_API_DESC(SW_API_PT_MAC_VLAN_XLT_GET)  \
    SW_API_DESC(SW_API_NETISOLATE_SET)   \
    SW_API_DESC(SW_API_NETISOLATE_GET)   \
    SW_API_DESC(SW_API_EG_FLTR_BYPASS_EN_SET) \
    SW_API_DESC(SW_API_EG_FLTR_BYPASS_EN_GET)

#else
#define PORTVLAN_API
#define PORTVLAN_API_PARAM
#endif


#ifdef IN_ACL
#define ACL_API \
    SW_API_DEF(SW_API_ACL_LIST_CREAT, dess_acl_list_creat), \
    SW_API_DEF(SW_API_ACL_LIST_DESTROY, dess_acl_list_destroy), \
    SW_API_DEF(SW_API_ACL_RULE_ADD, dess_acl_rule_add), \
    SW_API_DEF(SW_API_ACL_RULE_DELETE, dess_acl_rule_delete), \
    SW_API_DEF(SW_API_ACL_RULE_QUERY, dess_acl_rule_query), \
    SW_API_DEF(SW_API_ACL_LIST_BIND, dess_acl_list_bind), \
    SW_API_DEF(SW_API_ACL_LIST_UNBIND, dess_acl_list_unbind), \
    SW_API_DEF(SW_API_ACL_STATUS_SET, dess_acl_status_set), \
    SW_API_DEF(SW_API_ACL_STATUS_GET, dess_acl_status_get), \
    SW_API_DEF(SW_API_ACL_LIST_DUMP, dess_acl_list_dump), \
    SW_API_DEF(SW_API_ACL_RULE_DUMP, dess_acl_rule_dump), \
    SW_API_DEF(SW_API_ACL_PT_UDF_PROFILE_SET, dessort_udf_profile_set), \
    SW_API_DEF(SW_API_ACL_PT_UDF_PROFILE_GET, dess_acl_port_udf_profile_get), \
    SW_API_DEF(SW_API_ACL_RULE_ACTIVE, dess_acl_rule_active), \
    SW_API_DEF(SW_API_ACL_RULE_DEACTIVE, dess_acl_rule_deactive),\
    SW_API_DEF(SW_API_ACL_RULE_SRC_FILTER_STS_SET, dess_acl_rule_src_filter_sts_set),\
    SW_API_DEF(SW_API_ACL_RULE_SRC_FILTER_STS_GET, dess_acl_rule_src_filter_sts_get), \
    SW_API_DEF(SW_API_ACL_RULE_GET_OFFSET, dess_acl_rule_get_offset),

#define ACL_API_PARAM \
    SW_API_DESC(SW_API_ACL_LIST_CREAT)   \
    SW_API_DESC(SW_API_ACL_LIST_DESTROY) \
    SW_API_DESC(SW_API_ACL_RULE_ADD)     \
    SW_API_DESC(SW_API_ACL_RULE_DELETE)  \
    SW_API_DESC(SW_API_ACL_RULE_QUERY)   \
    SW_API_DESC(SW_API_ACL_LIST_BIND)    \
    SW_API_DESC(SW_API_ACL_LIST_UNBIND)  \
    SW_API_DESC(SW_API_ACL_STATUS_SET)   \
    SW_API_DESC(SW_API_ACL_STATUS_GET)   \
    SW_API_DESC(SW_API_ACL_LIST_DUMP)    \
    SW_API_DESC(SW_API_ACL_RULE_DUMP)    \
    SW_API_DESC(SW_API_ACL_PT_UDF_PROFILE_SET)    \
    SW_API_DESC(SW_API_ACL_PT_UDF_PROFILE_GET)    \
    SW_API_DESC(SW_API_ACL_RULE_ACTIVE)    \
    SW_API_DESC(SW_API_ACL_RULE_DEACTIVE) \
    SW_API_DESC(SW_API_ACL_RULE_SRC_FILTER_STS_SET) \
    SW_API_DESC(SW_API_ACL_RULE_SRC_FILTER_STS_GET)
#else
#define ACL_API
#define ACL_API_PARAM
#endif


#ifdef IN_QOS
#define QOS_API \
    SW_API_DEF(SW_API_QOS_QU_TX_BUF_ST_SET, dess_qos_queue_tx_buf_status_set), \
    SW_API_DEF(SW_API_QOS_QU_TX_BUF_ST_GET, dess_qos_queue_tx_buf_status_get), \
    SW_API_DEF(SW_API_QOS_QU_TX_BUF_NR_SET, dess_qos_queue_tx_buf_nr_set), \
    SW_API_DEF(SW_API_QOS_QU_TX_BUF_NR_GET, dess_qos_queue_tx_buf_nr_get), \
    SW_API_DEF(SW_API_QOS_PT_TX_BUF_ST_SET, dess_qos_port_tx_buf_status_set), \
    SW_API_DEF(SW_API_QOS_PT_TX_BUF_ST_GET, dess_qos_port_tx_buf_status_get), \
    SW_API_DEF(SW_API_QOS_PT_RED_EN_SET, dess_qos_port_red_en_set),\
    SW_API_DEF(SW_API_QOS_PT_RED_EN_GET, dess_qos_port_red_en_get),\
    SW_API_DEF(SW_API_QOS_PT_TX_BUF_NR_SET, dess_qos_port_tx_buf_nr_set), \
    SW_API_DEF(SW_API_QOS_PT_TX_BUF_NR_GET, dess_qos_port_tx_buf_nr_get), \
    SW_API_DEF(SW_API_QOS_PT_RX_BUF_NR_SET, dess_qos_port_rx_buf_nr_set), \
    SW_API_DEF(SW_API_QOS_PT_RX_BUF_NR_GET, dess_qos_port_rx_buf_nr_get), \
    SW_API_DEF(SW_API_QOS_PT_MODE_SET, dess_qos_port_mode_set), \
    SW_API_DEF(SW_API_QOS_PT_MODE_GET, dess_qos_port_mode_get), \
    SW_API_DEF(SW_API_QOS_PT_MODE_PRI_SET, dess_qos_port_mode_pri_set), \
    SW_API_DEF(SW_API_QOS_PT_MODE_PRI_GET, dess_qos_port_mode_pri_get), \
    SW_API_DEF(SW_API_QOS_PORT_SCH_MODE_SET, dess_qos_port_sch_mode_set), \
    SW_API_DEF(SW_API_QOS_PORT_SCH_MODE_GET, dess_qos_port_sch_mode_get), \
    SW_API_DEF(SW_API_QOS_PT_DEF_SPRI_SET, dess_qos_port_default_spri_set), \
    SW_API_DEF(SW_API_QOS_PT_DEF_SPRI_GET, dess_qos_port_default_spri_get), \
    SW_API_DEF(SW_API_QOS_PT_DEF_CPRI_SET, dess_qos_port_default_cpri_set), \
    SW_API_DEF(SW_API_QOS_PT_DEF_CPRI_GET, dess_qos_port_default_cpri_get), \
    SW_API_DEF(SW_API_QOS_PT_FORCE_SPRI_ST_SET, dess_qos_port_force_spri_status_set), \
    SW_API_DEF(SW_API_QOS_PT_FORCE_SPRI_ST_GET, dess_qos_port_force_spri_status_get), \
    SW_API_DEF(SW_API_QOS_PT_FORCE_CPRI_ST_SET, dess_qos_port_force_cpri_status_set), \
    SW_API_DEF(SW_API_QOS_PT_FORCE_CPRI_ST_GET, dess_qos_port_force_cpri_status_get), \
    SW_API_DEF(SW_API_QOS_QUEUE_REMARK_SET, dess_qos_queue_remark_table_set), \
    SW_API_DEF(SW_API_QOS_QUEUE_REMARK_GET, dess_qos_queue_remark_table_get),


#define QOS_API_PARAM \
    SW_API_DESC(SW_API_QOS_QU_TX_BUF_ST_SET) \
    SW_API_DESC(SW_API_QOS_QU_TX_BUF_ST_GET) \
    SW_API_DESC(SW_API_QOS_QU_TX_BUF_NR_SET) \
    SW_API_DESC(SW_API_QOS_QU_TX_BUF_NR_GET) \
    SW_API_DESC(SW_API_QOS_PT_TX_BUF_ST_SET) \
    SW_API_DESC(SW_API_QOS_PT_TX_BUF_ST_GET) \
    SW_API_DESC(SW_API_QOS_PT_RED_EN_SET) \
    SW_API_DESC(SW_API_QOS_PT_RED_EN_GET) \
    SW_API_DESC(SW_API_QOS_PT_TX_BUF_NR_SET) \
    SW_API_DESC(SW_API_QOS_PT_TX_BUF_NR_GET) \
    SW_API_DESC(SW_API_QOS_PT_RX_BUF_NR_SET) \
    SW_API_DESC(SW_API_QOS_PT_RX_BUF_NR_GET) \
    SW_API_DESC(SW_API_QOS_PT_MODE_SET) \
    SW_API_DESC(SW_API_QOS_PT_MODE_GET) \
    SW_API_DESC(SW_API_QOS_PT_MODE_PRI_SET) \
    SW_API_DESC(SW_API_QOS_PT_MODE_PRI_GET) \
    SW_API_DESC(SW_API_QOS_PORT_DEF_UP_SET) \
    SW_API_DESC(SW_API_QOS_PORT_DEF_UP_GET) \
    SW_API_DESC(SW_API_QOS_PORT_SCH_MODE_SET) \
    SW_API_DESC(SW_API_QOS_PORT_SCH_MODE_GET) \
    SW_API_DESC(SW_API_QOS_PT_DEF_SPRI_SET)  \
    SW_API_DESC(SW_API_QOS_PT_DEF_SPRI_GET)  \
    SW_API_DESC(SW_API_QOS_PT_DEF_CPRI_SET)  \
    SW_API_DESC(SW_API_QOS_PT_DEF_CPRI_GET)  \
    SW_API_DESC(SW_API_QOS_PT_FORCE_SPRI_ST_SET)  \
    SW_API_DESC(SW_API_QOS_PT_FORCE_SPRI_ST_GET)  \
    SW_API_DESC(SW_API_QOS_PT_FORCE_CPRI_ST_SET)  \
    SW_API_DESC(SW_API_QOS_PT_FORCE_CPRI_ST_GET)  \
    SW_API_DESC(SW_API_QOS_QUEUE_REMARK_SET) \
    SW_API_DESC(SW_API_QOS_QUEUE_REMARK_GET)
#else
#define QOS_API
#define QOS_API_PARAM
#endif


#ifdef IN_MIB
#define MIB_API \
    SW_API_DEF(SW_API_PT_MIB_GET, dess_get_mib_info), \
    SW_API_DEF(SW_API_MIB_STATUS_SET, dess_mib_status_set), \
    SW_API_DEF(SW_API_MIB_STATUS_GET, dess_mib_status_get), \
    SW_API_DEF(SW_API_PT_MIB_FLUSH_COUNTERS, dess_mib_port_flush_counters), \
    SW_API_DEF(SW_API_MIB_CPU_KEEP_SET, dess_mib_cpukeep_set), \
    SW_API_DEF(SW_API_MIB_CPU_KEEP_GET, dess_mib_cpukeep_get),


#define MIB_API_PARAM \
    SW_API_DESC(SW_API_PT_MIB_GET)  \
    SW_API_DESC(SW_API_MIB_STATUS_SET) \
    SW_API_DESC(SW_API_MIB_STATUS_GET)\
    SW_API_DESC(SW_API_PT_MIB_FLUSH_COUNTERS) \
    SW_API_DESC(SW_API_MIB_CPU_KEEP_SET) \
    SW_API_DESC(SW_API_MIB_CPU_KEEP_GET)
#else
#define MIB_API
#define MIB_API_PARAM
#endif


#ifdef IN_COSMAP
#define COSMAP_API \
    SW_API_DEF(SW_API_COSMAP_DSCP_TO_PRI_SET, dess_cosmap_dscp_to_pri_set), \
    SW_API_DEF(SW_API_COSMAP_DSCP_TO_PRI_GET, dess_cosmap_dscp_to_pri_get), \
    SW_API_DEF(SW_API_COSMAP_DSCP_TO_DP_SET, dess_cosmap_dscp_to_dp_set), \
    SW_API_DEF(SW_API_COSMAP_DSCP_TO_DP_GET, dess_cosmap_dscp_to_dp_get), \
    SW_API_DEF(SW_API_COSMAP_UP_TO_PRI_SET, dess_cosmap_up_to_pri_set), \
    SW_API_DEF(SW_API_COSMAP_UP_TO_PRI_GET, dess_cosmap_up_to_pri_get), \
    SW_API_DEF(SW_API_COSMAP_UP_TO_DP_SET, dess_cosmap_up_to_dp_set), \
    SW_API_DEF(SW_API_COSMAP_UP_TO_DP_GET, dess_cosmap_up_to_dp_get), \
    SW_API_DEF(SW_API_COSMAP_PRI_TO_QU_SET, dess_cosmap_pri_to_queue_set), \
    SW_API_DEF(SW_API_COSMAP_PRI_TO_QU_GET, dess_cosmap_pri_to_queue_get), \
    SW_API_DEF(SW_API_COSMAP_PRI_TO_EHQU_SET, dess_cosmap_pri_to_ehqueue_set), \
    SW_API_DEF(SW_API_COSMAP_PRI_TO_EHQU_GET, dess_cosmap_pri_to_ehqueue_get), \
    SW_API_DEF(SW_API_COSMAP_EG_REMARK_SET, dess_cosmap_egress_remark_set), \
    SW_API_DEF(SW_API_COSMAP_EG_REMARK_GET, dess_cosmap_egress_remark_get),

#define COSMAP_API_PARAM \
    SW_API_DESC(SW_API_COSMAP_DSCP_TO_PRI_SET)  \
    SW_API_DESC(SW_API_COSMAP_DSCP_TO_PRI_GET)  \
    SW_API_DESC(SW_API_COSMAP_DSCP_TO_DP_SET)  \
    SW_API_DESC(SW_API_COSMAP_DSCP_TO_DP_GET)  \
    SW_API_DESC(SW_API_COSMAP_UP_TO_PRI_SET)  \
    SW_API_DESC(SW_API_COSMAP_UP_TO_PRI_GET)  \
    SW_API_DESC(SW_API_COSMAP_UP_TO_DP_SET)  \
    SW_API_DESC(SW_API_COSMAP_UP_TO_DP_GET)  \
    SW_API_DESC(SW_API_COSMAP_PRI_TO_QU_SET)  \
    SW_API_DESC(SW_API_COSMAP_PRI_TO_QU_GET)  \
    SW_API_DESC(SW_API_COSMAP_PRI_TO_EHQU_SET) \
    SW_API_DESC(SW_API_COSMAP_PRI_TO_EHQU_GET) \
    SW_API_DESC(SW_API_COSMAP_EG_REMARK_SET) \
    SW_API_DESC(SW_API_COSMAP_EG_REMARK_GET)
#else
#define COSMAP_API
#define COSMAP_API_PARAM
#endif

#ifdef IN_SEC
#define SEC_API \
    SW_API_DEF(SW_API_SEC_NORM_SET, dess_sec_norm_item_set), \
    SW_API_DEF(SW_API_SEC_NORM_GET, dess_sec_norm_item_get), \
    SW_API_DEF(SW_API_SEC_MAC_SET, dess_sec_norm_item_set), \
    SW_API_DEF(SW_API_SEC_MAC_GET, dess_sec_norm_item_get), \
    SW_API_DEF(SW_API_SEC_IP_SET, dess_sec_norm_item_set), \
    SW_API_DEF(SW_API_SEC_IP_GET, dess_sec_norm_item_get), \
    SW_API_DEF(SW_API_SEC_IP4_SET, dess_sec_norm_item_set), \
    SW_API_DEF(SW_API_SEC_IP4_GET, dess_sec_norm_item_get), \
    SW_API_DEF(SW_API_SEC_IP6_SET, dess_sec_norm_item_set), \
    SW_API_DEF(SW_API_SEC_IP6_GET, dess_sec_norm_item_get), \
    SW_API_DEF(SW_API_SEC_TCP_SET, dess_sec_norm_item_set), \
    SW_API_DEF(SW_API_SEC_TCP_GET, dess_sec_norm_item_get), \
    SW_API_DEF(SW_API_SEC_UDP_SET, dess_sec_norm_item_set), \
    SW_API_DEF(SW_API_SEC_UDP_GET, dess_sec_norm_item_get), \
    SW_API_DEF(SW_API_SEC_ICMP4_SET, dess_sec_norm_item_set), \
    SW_API_DEF(SW_API_SEC_ICMP4_GET, dess_sec_norm_item_get), \
    SW_API_DEF(SW_API_SEC_ICMP6_SET, dess_sec_norm_item_set), \
    SW_API_DEF(SW_API_SEC_ICMP6_GET, dess_sec_norm_item_get),

#define SEC_API_PARAM \
    SW_API_DESC(SW_API_SEC_NORM_SET) \
    SW_API_DESC(SW_API_SEC_NORM_GET) \
    SW_API_DESC(SW_API_SEC_MAC_SET) \
    SW_API_DESC(SW_API_SEC_MAC_GET) \
    SW_API_DESC(SW_API_SEC_IP_SET) \
    SW_API_DESC(SW_API_SEC_IP_GET) \
    SW_API_DESC(SW_API_SEC_IP4_SET) \
    SW_API_DESC(SW_API_SEC_IP4_GET) \
    SW_API_DESC(SW_API_SEC_IP6_SET) \
    SW_API_DESC(SW_API_SEC_IP6_GET) \
    SW_API_DESC(SW_API_SEC_TCP_SET) \
    SW_API_DESC(SW_API_SEC_TCP_GET) \
    SW_API_DESC(SW_API_SEC_UDP_SET) \
    SW_API_DESC(SW_API_SEC_UDP_GET) \
    SW_API_DESC(SW_API_SEC_ICMP4_SET) \
    SW_API_DESC(SW_API_SEC_ICMP4_GET) \
    SW_API_DESC(SW_API_SEC_ICMP6_SET) \
    SW_API_DESC(SW_API_SEC_ICMP6_GET)
#else
#define SEC_API
#define SEC_API_PARAM
#endif

#define REG_API \
    SW_API_DEF(SW_API_PHY_GET, dess_phy_get), \
    SW_API_DEF(SW_API_PHY_SET, dess_phy_set), \
    SW_API_DEF(SW_API_REG_GET, dess_reg_get), \
    SW_API_DEF(SW_API_REG_SET, dess_reg_set), \
    SW_API_DEF(SW_API_REG_FIELD_GET, dess_reg_field_get), \
    SW_API_DEF(SW_API_REG_FIELD_SET, dess_reg_field_set),

#define REG_API_PARAM \
    SW_API_DESC(SW_API_PHY_GET) \
    SW_API_DESC(SW_API_PHY_SET) \
    SW_API_DESC(SW_API_REG_GET) \
    SW_API_DESC(SW_API_REG_SET) \
    SW_API_DESC(SW_API_REG_FIELD_GET) \
    SW_API_DESC(SW_API_REG_FIELD_SET)

#define SSDK_API \
    SW_API_DEF(SW_API_SWITCH_RESET, dess_reset), \
    SW_API_DEF(SW_API_SSDK_CFG, hsl_ssdk_cfg), \
    VLAN_API \
    PORTVLAN_API \
    FDB_API    \
    ACL_API    \
    QOS_API    \
    MIB_API  \
    COSMAP_API \
    SEC_API  \
    REG_API  \
    SW_API_DEF(SW_API_MAX, NULL),
#define SSDK_PARAM  \
    SW_PARAM_DEF(SW_API_SWITCH_RESET, SW_UINT32, 4, SW_PARAM_IN, "Dev ID"), \
    SW_PARAM_DEF(SW_API_SSDK_CFG, SW_UINT32, 4, SW_PARAM_IN, "Dev ID"), \
    SW_PARAM_DEF(SW_API_SSDK_CFG, SW_SSDK_CFG, sizeof(ssdk_cfg_t), SW_PARAM_PTR|SW_PARAM_OUT, "ssdk configuration"), \
    MIB_API_PARAM    \
    PORTVLAN_API_PARAM    \
    VLAN_API_PARAM \
    FDB_API_PARAM  \
    QOS_API_PARAM  \
    ACL_API_PARAM  \
    COSMAP_API_PARAM \
    SEC_API_PARAM  \
    REG_API_PARAM  \
    SW_PARAM_DEF(SW_API_MAX, SW_UINT32, 4, SW_PARAM_IN, "Dev ID"),

#if (defined(USER_MODE) && defined(KERNEL_MODULE))
#undef SSDK_API
#undef SSDK_PARAM

#define SSDK_API \
    REG_API \
    SW_API_DEF(SW_API_MAX, NULL),

#define SSDK_PARAM  \
    REG_API_PARAM \
    SW_PARAM_DEF(SW_API_MAX, SW_UINT32, 4, SW_PARAM_IN, "Dev ID"),
#endif

#ifdef __cplusplus
}
#endif                          /* __cplusplus */

#endif                          /* _DESS_API_H_ */
_ */
