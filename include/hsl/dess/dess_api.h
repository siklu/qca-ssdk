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
    MIB_API  \
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
