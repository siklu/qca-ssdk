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



#ifndef _DESS_REG_H_
#define _DESS_REG_H_

#ifdef __cplusplus
extern "C" {
#endif                          /* __cplusplus */

#define DESS_DEVICE_ID   0x14 /* TBD */

#define MAX_ENTRY_LEN   128

#define HSL_RW 1
#define HSL_RO 0


    /* ISIS Mask Control Register */
#define MASK_CTL
#define MASK_CTL_ID               0
#define MASK_CTL_OFFSET           0x0000
#define MASK_CTL_E_LENGTH         4
#define MASK_CTL_E_OFFSET         0
#define MASK_CTL_NR_E             1

#define SOFT_RST
#define MASK_CTL_SOFT_RST_BOFFSET             31
#define MASK_CTL_SOFT_RST_BLEN                1
#define MASK_CTL_SOFT_RST_FLAG                HSL_RW

#define LOAD_EEPROM
#define MASK_CTL_LOAD_EEPROM_BOFFSET          16
#define MASK_CTL_LOAD_EEPROM_BLEN             1
#define MASK_CTL_LOAD_EEPROM_FLAG             HSL_RW

#define DEVICE_ID
#define MASK_CTL_DEVICE_ID_BOFFSET            8
#define MASK_CTL_DEVICE_ID_BLEN               8
#define MASK_CTL_DEVICE_ID_FLAG               HSL_RO

#define REV_ID
#define MASK_CTL_REV_ID_BOFFSET               0
#define MASK_CTL_REV_ID_BLEN                  8
#define MASK_CTL_REV_ID_FLAG                  HSL_RO
    /* Module Enable Register */
#define MOD_ENABLE
#define MOD_ENABLE_OFFSET           0x0030
#define MOD_ENABLE_E_LENGTH         4
#define MOD_ENABLE_E_OFFSET         0
#define MOD_ENABLE_NR_E             1

#define L3_EN
#define MOD_ENABLE_L3_EN_BOFFSET                  2
#define MOD_ENABLE_L3_EN_BLEN                     1
#define MOD_ENABLE_L3_EN_FLAG                     HSL_RW

#define ACL_EN
#define MOD_ENABLE_ACL_EN_BOFFSET                 1
#define MOD_ENABLE_ACL_EN_BLEN                    1
#define MOD_ENABLE_ACL_EN_FLAG                    HSL_RW

#define MIB_EN
#define MOD_ENABLE_MIB_EN_BOFFSET                 0
#define MOD_ENABLE_MIB_EN_BLEN                    1
#define MOD_ENABLE_MIB_EN_FLAG                    HSL_RW




    /* MIB Function Register */
#define MIB_FUNC
#define MIB_FUNC_OFFSET           0x0034
#define MIB_FUNC_E_LENGTH         4
#define MIB_FUNC_E_OFFSET         0
#define MIB_FUNC_NR_E             1

#define MIB_FUN
#define MIB_FUNC_MIB_FUN_BOFFSET               24
#define MIB_FUNC_MIB_FUN_BLEN                  3
#define MIB_FUNC_MIB_FUN_FLAG                  HSL_RW

#define MIB_FLUSH_PORT
#define MIB_FUNC_MIB_FLUSH_PORT_BOFFSET        21
#define MIB_FUNC_MIB_FLUSH_PORT_BLEN            3
#define MIB_FUNC_MIB_FLUSH_PORT_FLAG          HSL_RW

#define MIB_CPU_KEEP
#define MIB_FUNC_MIB_CPU_KEEP_BOFFSET     20
#define MIB_FUNC_MIB_CPU_KEEP_BLEN          1
#define MIB_FUNC_MIB_CPU_KEEP_FLAG         HSL_RW

#define MIB_BUSY
#define MIB_FUNC_MIB_BUSY_BOFFSET              17
#define MIB_FUNC_MIB_BUSY_BLEN                 1
#define MIB_FUNC_MIB_BUSY_FLAG                 HSL_RW

#define MIB_AT_HALF_EN
#define MIB_FUNC_MIB_AT_HALF_EN_BOFFSET        16
#define MIB_FUNC_MIB_AT_HALF_EN_BLEN           1
#define MIB_FUNC_MIB_AT_HALF_EN_FLAG           HSL_RW

#define MIB_TIMER
#define MIB_FUNC_MIB_TIMER_BOFFSET             0
#define MIB_FUNC_MIB_TIMER_BLEN                16
#define MIB_FUNC_MIB_TIMER_FLAG                HSL_RW



    /* Service tag Register */
#define SERVICE_TAG
#define SERVICE_TAG_OFFSET           0x0048
#define SERVICE_TAG_E_LENGTH         4
#define SERVICE_TAG_E_OFFSET         0
#define SERVICE_TAG_NR_E             1

#define STAG_MODE
#define SERVICE_TAG_STAG_MODE_BOFFSET    17
#define SERVICE_TAG_STAG_MODE_BLEN       1
#define SERVICE_TAG_STAG_MODE_FLAG       HSL_RW

#define TAG_VALUE
#define SERVICE_TAG_TAG_VALUE_BOFFSET    0
#define SERVICE_TAG_TAG_VALUE_BLEN       16
#define SERVICE_TAG_TAG_VALUE_FLAG       HSL_RW


    /* Window Rule Ctl0 Register */
#define WIN_RULE_CTL0
#define WIN_RULE_CTL0_OFFSET               0x0218
#define WIN_RULE_CTL0_E_LENGTH             4
#define WIN_RULE_CTL0_E_OFFSET             0x4
#define WIN_RULE_CTL0_NR_E                 7

#define L4_LENGTH
#define WIN_RULE_CTL0_L4_LENGTH_BOFFSET    24
#define WIN_RULE_CTL0_L4_LENGTH_BLEN       4
#define WIN_RULE_CTL0_L4_LENGTH_FLAG       HSL_RW

#define L3_LENGTH
#define WIN_RULE_CTL0_L3_LENGTH_BOFFSET    20
#define WIN_RULE_CTL0_L3_LENGTH_BLEN       4
#define WIN_RULE_CTL0_L3_LENGTH_FLAG       HSL_RW

#define L2_LENGTH
#define WIN_RULE_CTL0_L2_LENGTH_BOFFSET    16
#define WIN_RULE_CTL0_L2_LENGTH_BLEN       4
#define WIN_RULE_CTL0_L2_LENGTH_FLAG       HSL_RW

#define L4_OFFSET
#define WIN_RULE_CTL0_L4_OFFSET_BOFFSET    10
#define WIN_RULE_CTL0_L4_OFFSET_BLEN       5
#define WIN_RULE_CTL0_L4_OFFSET_FLAG       HSL_RW

#define L3_OFFSET
#define WIN_RULE_CTL0_L3_OFFSET_BOFFSET    5
#define WIN_RULE_CTL0_L3_OFFSET_BLEN       5
#define WIN_RULE_CTL0_L3_OFFSET_FLAG       HSL_RW

#define L2_OFFSET
#define WIN_RULE_CTL0_L2_OFFSET_BOFFSET    0
#define WIN_RULE_CTL0_L2_OFFSET_BLEN       5
#define WIN_RULE_CTL0_L2_OFFSET_FLAG       HSL_RW




    /* Window Rule Ctl1 Register */
#define WIN_RULE_CTL1
#define WIN_RULE_CTL1_OFFSET               0x0234
#define WIN_RULE_CTL1_E_LENGTH             4
#define WIN_RULE_CTL1_E_OFFSET             0x4
#define WIN_RULE_CTL1_NR_E                 7

#define L3P_LENGTH
#define WIN_RULE_CTL1_L3P_LENGTH_BOFFSET   20
#define WIN_RULE_CTL1_L3P_LENGTH_BLEN      4
#define WIN_RULE_CTL1_L3P_LENGTH_FLAG      HSL_RW

#define L2S_LENGTH
#define WIN_RULE_CTL1_L2S_LENGTH_BOFFSET   16
#define WIN_RULE_CTL1_L2S_LENGTH_BLEN      4
#define WIN_RULE_CTL1_L2S_LENGTH_FLAG      HSL_RW

#define L3P_OFFSET
#define WIN_RULE_CTL1_L3P_OFFSET_BOFFSET   5
#define WIN_RULE_CTL1_L3P_OFFSET_BLEN      5
#define WIN_RULE_CTL1_L3P_OFFSET_FLAG      HSL_RW

#define L2S_OFFSET
#define WIN_RULE_CTL1_L2S_OFFSET_BOFFSET   0
#define WIN_RULE_CTL1_L2S_OFFSET_BLEN      5
#define WIN_RULE_CTL1_L2S_OFFSET_FLAG      HSL_RW


    /* Vlan Table Function0 Register */
#define VLAN_TABLE_FUNC0
#define VLAN_TABLE_FUNC0_OFFSET    0x0610
#define VLAN_TABLE_FUNC0_E_LENGTH  4
#define VLAN_TABLE_FUNC0_E_OFFSET  0
#define VLAN_TABLE_FUNC0_NR_E      1

#define VT_VALID
#define VLAN_TABLE_FUNC0_VT_VALID_BOFFSET      20
#define VLAN_TABLE_FUNC0_VT_VALID_BLEN         1
#define VLAN_TABLE_FUNC0_VT_VALID_FLAG         HSL_RW

#define IVL_EN
#define VLAN_TABLE_FUNC0_IVL_EN_BOFFSET        19
#define VLAN_TABLE_FUNC0_IVL_EN_BLEN           1
#define VLAN_TABLE_FUNC0_IVL_EN_FLAG           HSL_RW

#define LEARN_DIS
#define VLAN_TABLE_FUNC0_LEARN_DIS_BOFFSET     18
#define VLAN_TABLE_FUNC0_LEARN_DIS_BLEN        1
#define VLAN_TABLE_FUNC0_LEARN_DIS_FLAG        HSL_RW

#define VID_MEM
#define VLAN_TABLE_FUNC0_VID_MEM_BOFFSET       4
#define VLAN_TABLE_FUNC0_VID_MEM_BLEN          14
#define VLAN_TABLE_FUNC0_VID_MEM_FLAG          HSL_RW

#define VT_PRI_EN
#define VLAN_TABLE_FUNC0_VT_PRI_EN_BOFFSET     3
#define VLAN_TABLE_FUNC0_VT_PRI_EN_BLEN        1
#define VLAN_TABLE_FUNC0_VT_PRI_EN_FLAG        HSL_RW

#define VT_PRI
#define VLAN_TABLE_FUNC0_VT_PRI_BOFFSET        0
#define VLAN_TABLE_FUNC0_VT_PRI_BLEN           3
#define VLAN_TABLE_FUNC0_VT_PRI_FLAG           HSL_RW

    /* Vlan Table Function1 Register */
#define VLAN_TABLE_FUNC1
#define VLAN_TABLE_FUNC1_OFFSET    0x0614
#define VLAN_TABLE_FUNC1_E_LENGTH  4
#define VLAN_TABLE_FUNC1_E_OFFSET  0
#define VLAN_TABLE_FUNC1_NR_E      1

#define VT_BUSY
#define VLAN_TABLE_FUNC1_VT_BUSY_BOFFSET       31
#define VLAN_TABLE_FUNC1_VT_BUSY_BLEN          1
#define VLAN_TABLE_FUNC1_VT_BUSY_FLAG          HSL_RW

#define VLAN_ID
#define VLAN_TABLE_FUNC1_VLAN_ID_BOFFSET       16
#define VLAN_TABLE_FUNC1_VLAN_ID_BLEN          12
#define VLAN_TABLE_FUNC1_VLAN_ID_FLAG          HSL_RW

#define VT_PORT_NUM
#define VLAN_TABLE_FUNC1_VT_PORT_NUM_BOFFSET   8
#define VLAN_TABLE_FUNC1_VT_PORT_NUM_BLEN      4
#define VLAN_TABLE_FUNC1_VT_PORT_NUM_FLAG      HSL_RW

#define VT_FULL_VIO
#define VLAN_TABLE_FUNC1_VT_FULL_VIO_BOFFSET   4
#define VLAN_TABLE_FUNC1_VT_FULL_VIO_BLEN      1
#define VLAN_TABLE_FUNC1_VT_FULL_VIO_FLAG      HSL_RW

#define VT_FUNC
#define VLAN_TABLE_FUNC1_VT_FUNC_BOFFSET       0
#define VLAN_TABLE_FUNC1_VT_FUNC_BLEN          3
#define VLAN_TABLE_FUNC1_VT_FUNC_FLAG          HSL_RW

    /* DSCP To Priority Register */
#define DSCP_TO_PRI
#define DSCP_TO_PRI_OFFSET     0x0630
#define DSCP_TO_PRI_E_LENGTH   4
#define DSCP_TO_PRI_E_OFFSET   0x0004
#define DSCP_TO_PRI_NR_E       8




    /* UP To Priority Register */
#define UP_TO_PRI
#define UP_TO_PRI_OFFSET     0x0650
#define UP_TO_PRI_E_LENGTH   4
#define UP_TO_PRI_E_OFFSET   0x0004
#define UP_TO_PRI_NR_E       1




    /* WAN DSCP To Priority Register */
#define DSCP_TO_EHPRI
#define DSCP_TO_EHPRI_OFFSET     0x0730
#define DSCP_TO_EHPRI_E_LENGTH   4
#define DSCP_TO_EHPRI_E_OFFSET   0x0004
#define DSCP_TO_EHPRI_NR_E       8




    /* WAN UP To Priority Register */
#define UP_TO_EHPRI
#define UP_TO_EHPRI_OFFSET     0x0750
#define UP_TO_EHPRI_E_LENGTH   4
#define UP_TO_EHPRI_E_OFFSET   0x0004
#define UP_TO_EHPRI_NR_E       1




    /* Port Lookup control Register */
#define PORT_LOOKUP_CTL
#define PORT_LOOKUP_CTL_OFFSET     0x0660
#define PORT_LOOKUP_CTL_E_LENGTH   4
#define PORT_LOOKUP_CTL_E_OFFSET   0x000c
#define PORT_LOOKUP_CTL_NR_E       7

#define MULTI_DROP_EN
#define PORT_LOOKUP_CTL_MULTI_DROP_EN_BOFFSET    31
#define PORT_LOOKUP_CTL_MULTI_DROP_EN_BLEN       1
#define PORT_LOOKUP_CTL_MULTI_DROP_EN_FLAG       HSL_RW

#define UNI_LEAKY_EN
#define PORT_LOOKUP_CTL_UNI_LEAKY_EN_BOFFSET     28
#define PORT_LOOKUP_CTL_UNI_LEAKY_EN_BLEN        1
#define PORT_LOOKUP_CTL_UNI_LEAKY_EN_FLAG        HSL_RW

#define MUL_LEAKY_EN
#define PORT_LOOKUP_CTL_MUL_LEAKY_EN_BOFFSET     27
#define PORT_LOOKUP_CTL_MUL_LEAKY_EN_BLEN        1
#define PORT_LOOKUP_CTL_MUL_LEAKY_EN_FLAG        HSL_RW

#define ARP_LEAKY_EN
#define PORT_LOOKUP_CTL_ARP_LEAKY_EN_BOFFSET     26
#define PORT_LOOKUP_CTL_ARP_LEAKY_EN_BLEN        1
#define PORT_LOOKUP_CTL_ARP_LEAKY_EN_FLAG        HSL_RW

#define ING_MIRROR_EN
#define PORT_LOOKUP_CTL_ING_MIRROR_EN_BOFFSET    25
#define PORT_LOOKUP_CTL_ING_MIRROR_EN_BLEN       1
#define PORT_LOOKUP_CTL_ING_MIRROR_EN_FLAG       HSL_RW

#define PORT_LOOP_BACK
#define PORT_LOOKUP_CTL_PORT_LOOP_BACK_BOFFSET   21
#define PORT_LOOKUP_CTL_PORT_LOOP_BACK_BLEN      1
#define PORT_LOOKUP_CTL_PORT_LOOP_BACK_FLAG      HSL_RW

#define LEARN_EN
#define PORT_LOOKUP_CTL_LEARN_EN_BOFFSET         20
#define PORT_LOOKUP_CTL_LEARN_EN_BLEN            1
#define PORT_LOOKUP_CTL_LEARN_EN_FLAG            HSL_RW

#define PORT_STATE
#define PORT_LOOKUP_CTL_PORT_STATE_BOFFSET       16
#define PORT_LOOKUP_CTL_PORT_STATE_BLEN          3
#define PORT_LOOKUP_CTL_PORT_STATE_FLAG          HSL_RW

#define FORCE_PVLAN
#define PORT_LOOKUP_CTL_FORCE_PVLAN_BOFFSET      10
#define PORT_LOOKUP_CTL_FORCE_PVLAN_BLEN         1
#define PORT_LOOKUP_CTL_FORCE_PVLAN_FLAG         HSL_RW

#define DOT1Q_MODE
#define PORT_LOOKUP_CTL_DOT1Q_MODE_BOFFSET       8
#define PORT_LOOKUP_CTL_DOT1Q_MODE_BLEN          2
#define PORT_LOOKUP_CTL_DOT1Q_MODE_FLAG          HSL_RW

#define PORT_VID_MEM
#define PORT_LOOKUP_CTL_PORT_VID_MEM_BOFFSET     0
#define PORT_LOOKUP_CTL_PORT_VID_MEM_BLEN        7
#define PORT_LOOKUP_CTL_PORT_VID_MEM_FLAG        HSL_RW




    /* Priority Control Register */
#define PRI_CTL
#define PRI_CTL_OFFSET            0x0664
#define PRI_CTL_E_LENGTH          4
#define PRI_CTL_E_OFFSET          0x000c
#define PRI_CTL_NR_E              7

#define EG_MAC_BASE_VLAN_EN
#define PRI_CTL_EG_MAC_BASE_VLAN_EN_BOFFSET     20
#define PRI_CTL_EG_MAC_BASE_VLAN_EN_BLEN        1
#define PRI_CTL_EG_MAC_BASE_VLAN_EN_FLAG        HSL_RW

#define FLOW_PRI_EN
#define PRI_CTL_FLOW_PRI_EN_BOFFSET               19
#define PRI_CTL_FLOW_PRI_EN_BLEN                  1
#define PRI_CTL_FLOW_PRI_EN_FLAG                  HSL_RW

#define DA_PRI_EN
#define PRI_CTL_DA_PRI_EN_BOFFSET               18
#define PRI_CTL_DA_PRI_EN_BLEN                  1
#define PRI_CTL_DA_PRI_EN_FLAG                  HSL_RW

#define VLAN_PRI_EN
#define PRI_CTL_VLAN_PRI_EN_BOFFSET             17
#define PRI_CTL_VLAN_PRI_EN_BLEN                1
#define PRI_CTL_VLAN_PRI_EN_FLAG                HSL_RW

#define IP_PRI_EN
#define PRI_CTL_IP_PRI_EN_BOFFSET               16
#define PRI_CTL_IP_PRI_EN_BLEN                  1
#define PRI_CTL_IP_PRI_EN_FLAG                  HSL_RW

#define FLOW_PRI_SEL
#define PRI_CTL_FLOW_PRI_SEL_BOFFSET              8
#define PRI_CTL_FLOW_PRI_SEL_BLEN                 2
#define PRI_CTL_FLOW_PRI_SEL_FLAG                 HSL_RW

#define DA_PRI_SEL
#define PRI_CTL_DA_PRI_SEL_BOFFSET              6
#define PRI_CTL_DA_PRI_SEL_BLEN                 2
#define PRI_CTL_DA_PRI_SEL_FLAG                 HSL_RW

#define VLAN_PRI_SEL
#define PRI_CTL_VLAN_PRI_SEL_BOFFSET            4
#define PRI_CTL_VLAN_PRI_SEL_BLEN               2
#define PRI_CTL_VLAN_PRI_SEL_FLAG               HSL_RW

#define IP_PRI_SEL
#define PRI_CTL_IP_PRI_SEL_BOFFSET              2
#define PRI_CTL_IP_PRI_SEL_BLEN                 2
#define PRI_CTL_IP_PRI_SEL_FLAG                 HSL_RW




    /* ACL Forward source filter Register */
#define ACL_FWD_SRC_FILTER_CTL0
#define ACL_FWD_SRC_FILTER_CTL0_OFFSET               0x0710
#define ACL_FWD_SRC_FILTER_CTL0_E_LENGTH             4
#define ACL_FWD_SRC_FILTER_CTL0_E_OFFSET             0x4
#define ACL_FWD_SRC_FILTER_CTL0_NR_E                 3


    /* VLAN translation register */
#define VLAN_TRANS
#define VLAN_TRANS_OFFSET     0x0418
#define VLAN_TRANS_E_LENGTH   4
#define VLAN_TRANS_E_OFFSET   0
#define VLAN_TRANS_NR_E       7

#define EG_FLTR_BYPASS_EN
#define VLAN_TRANS_EG_FLTR_BYPASS_EN_BOFFSET     1
#define VLAN_TRANS_EG_FLTR_BYPASS_EN_BLEN        1
#define VLAN_TRANS_EG_FLTR_BYPASS_EN_FLAG        HSL_RW

#define NET_ISO
#define VLAN_TRANS_NET_ISO_BOFFSET       0
#define VLAN_TRANS_NET_ISO_BLEN          1
#define VLAN_TRANS_NET_ISO_FLAG          HSL_RW


    /* Port vlan0 Register */
#define PORT_VLAN0
#define PORT_VLAN0_OFFSET     0x0420
#define PORT_VLAN0_E_LENGTH   4
#define PORT_VLAN0_E_OFFSET   0x0008
#define PORT_VLAN0_NR_E       7

#define ING_CPRI
#define PORT_VLAN0_ING_CPRI_BOFFSET       29
#define PORT_VLAN0_ING_CPRI_BLEN          3
#define PORT_VLAN0_ING_CPRI_FLAG          HSL_RW

#define ING_FORCE_CPRI
#define PORT_VLAN0_ING_FORCE_CPRI_BOFFSET       28
#define PORT_VLAN0_ING_FORCE_CPRI_BLEN          1
#define PORT_VLAN0_ING_FORCE_CPRI_FLAG          HSL_RW

#define DEF_CVID
#define PORT_VLAN0_DEF_CVID_BOFFSET       16
#define PORT_VLAN0_DEF_CVID_BLEN          12
#define PORT_VLAN0_DEF_CVID_FLAG          HSL_RW

#define ING_SPRI
#define PORT_VLAN0_ING_SPRI_BOFFSET       13
#define PORT_VLAN0_ING_SPRI_BLEN          3
#define PORT_VLAN0_ING_SPRI_FLAG          HSL_RW

#define ING_FORCE_SPRI
#define PORT_VLAN0_ING_FORCE_SPRI_BOFFSET       12
#define PORT_VLAN0_ING_FORCE_SPRI_BLEN          1
#define PORT_VLAN0_ING_FORCE_SPRI_FLAG          HSL_RW

#define DEF_SVID
#define PORT_VLAN0_DEF_SVID_BOFFSET       0
#define PORT_VLAN0_DEF_SVID_BLEN          12
#define PORT_VLAN0_DEF_SVID_FLAG          HSL_RW

    /* Port vlan1 Register */
#define PORT_VLAN1
#define PORT_VLAN1_OFFSET     0x0424
#define PORT_VLAN1_E_LENGTH   4
#define PORT_VLAN1_E_OFFSET   0x0008
#define PORT_VLAN1_NR_E       7

#define VRF_ID
#define PORT_VLAN1_VRF_ID_BOFFSET   15
#define PORT_VLAN1_VRF_ID_BLEN      3
#define PORT_VLAN1_VRF_ID_FLAG      HSL_RW

#define EG_VLAN_MODE
#define PORT_VLAN1_EG_VLAN_MODE_BOFFSET   12
#define PORT_VLAN1_EG_VLAN_MODE_BLEN      2
#define PORT_VLAN1_EG_VLAN_MODE_FLAG      HSL_RW

#define VLAN_DIS
#define PORT_VLAN1_VLAN_DIS_BOFFSET       11
#define PORT_VLAN1_VLAN_DIS_BLEN          1
#define PORT_VLAN1_VLAN_DIS_FLAG          HSL_RW

#define SP_CHECK_EN
#define PORT_VLAN1_SP_CHECK_EN_BOFFSET    10
#define PORT_VLAN1_SP_CHECK_EN_BLEN       1
#define PORT_VLAN1_SP_CHECK_EN_FLAG       HSL_RW

#define COREP_EN
#define PORT_VLAN1_COREP_EN_BOFFSET       9
#define PORT_VLAN1_COREP_EN_BLEN          1
#define PORT_VLAN1_COREP_EN_FLAG          HSL_RW

#define FORCE_DEF_VID
#define PORT_VLAN1_FORCE_DEF_VID_BOFFSET  8
#define PORT_VLAN1_FORCE_DEF_VID_BLEN     1
#define PORT_VLAN1_FORCE_DEF_VID_FLAG     HSL_RW

#define TLS_EN
#define PORT_VLAN1_TLS_EN_BOFFSET         7
#define PORT_VLAN1_TLS_EN_BLEN            1
#define PORT_VLAN1_TLS_EN_FLAG            HSL_RW

#define PROPAGATION_EN
#define PORT_VLAN1_PROPAGATION_EN_BOFFSET 6
#define PORT_VLAN1_PROPAGATION_EN_BLEN    1
#define PORT_VLAN1_PROPAGATION_EN_FLAG    HSL_RW

#define CLONE
#define PORT_VLAN1_CLONE_BOFFSET          5
#define PORT_VLAN1_CLONE_BLEN             1
#define PORT_VLAN1_CLONE_FLAG             HSL_RW

#define PRI_PROPAGATION
#define PORT_VLAN1_PRI_PROPAGATION_BOFFSET   4
#define PORT_VLAN1_PRI_PROPAGATION_BLEN      1
#define PORT_VLAN1_VLAN_PRI_PROPAGATION_FLAG HSL_RW

#define IN_VLAN_MODE
#define PORT_VLAN1_IN_VLAN_MODE_BOFFSET      2
#define PORT_VLAN1_IN_VLAN_MODE_BLEN         2
#define PORT_VLAN1_IN_VLAN_MODE_FLAG         HSL_RW


    /* Route Default VID Register */
#define ROUTER_DEFV
#define ROUTER_DEFV_OFFSET     0x0c70
#define ROUTER_DEFV_E_LENGTH   4
#define ROUTER_DEFV_E_OFFSET   0x0004
#define ROUTER_DEFV_NR_E       4


    /* Route Egress VLAN Mode Register */
#define ROUTER_EG
#define ROUTER_EG_OFFSET     0x0c80
#define ROUTER_EG_E_LENGTH   4
#define ROUTER_EG_E_OFFSET   0x0004
#define ROUTER_EG_NR_E       1






    /* Pri To Queue Register */
#define PRI_TO_QUEUE
#define PRI_TO_QUEUE_OFFSET         0x0814
#define PRI_TO_QUEUE_E_LENGTH       4
#define PRI_TO_QUEUE_E_OFFSET       0x0004
#define PRI_TO_QUEUE_NR_E           1




    /* Pri To EhQueue Register */
#define PRI_TO_EHQUEUE
#define PRI_TO_EHQUEUE_OFFSET         0x0810
#define PRI_TO_EHQUEUE_E_LENGTH       4
#define PRI_TO_EHQUEUE_E_OFFSET       0x0004
#define PRI_TO_EHQUEUE_NR_E           1




    /*Global Flow Control Register*/
#define QM_CTRL_REG
#define QM_CTRL_REG_OFFSET       0X0808
#define QM_CTRL_REG_E_LENGTH     4
#define QM_CTRL_REG_E_OFFSET     0x0004
#define QM_CTRL_REG_NR_E         1

#define GOL_FLOW_EN
#define QM_CTRL_REG_GOL_FLOW_EN_BOFFSET    16
#define QM_CTRL_REG_GOL_FLOW_EN_BLEN       7
#define QM_CTRL_REG_GOL_FLOW_EN_FLAG       HSL_RW

#define QM_FUNC_TEST
#define QM_CTRL_REG_QM_FUNC_TEST_BOFFSET   10
#define QM_CTRL_REG_QM_FUNC_TEST_BLEN      1
#define QM_CTRL_REG_QM_FUNC_TEST_FLAG      HSL_RW

#define RATE_DROP_EN
#define QM_CTRL_REG_RATE_DROP_EN_BOFFSET 7
#define QM_CTRL_REG_RATE_DROP_EN_BLEN    1
#define QM_CTRL_REG_RATE_DROP_EN_FLAG    HSL_RW

#define FLOW_DROP_EN
#define QM_CTRL_REG_FLOW_DROP_EN_BOFFSET 6
#define QM_CTRL_REG_FLOW_DROP_EN_BLEN    1
#define QM_CTRL_REG_FLOW_DROP_EN_FLAG    HSL_RW

#define FLOW_DROP_CNT
#define QM_CTRL_REG_FLOW_DROP_CNT_BOFFSET 0
#define QM_CTRL_REG_FLOW_DROP_CNT_BLEN    6
#define QM_CTRL_REG_FLOW_DROP_CNT_FLAG    HSL_RW




    /* Port HOL CTL0 Register */
#define PORT_HOL_CTL0
#define PORT_HOL_CTL0_OFFSET         0x0970
#define PORT_HOL_CTL0_E_LENGTH       4
#define PORT_HOL_CTL0_E_OFFSET       0x0008
#define PORT_HOL_CTL0_NR_E           7

#define PORT_DESC_NR
#define PORT_HOL_CTL0_PORT_DESC_NR_BOFFSET           24
#define PORT_HOL_CTL0_PORT_DESC_NR_BLEN              6
#define PORT_HOL_CTL0_PORT_DESC_NR_FLAG              HSL_RW

#define QUEUE5_DESC_NR
#define PORT_HOL_CTL0_QUEUE5_DESC_NR_BOFFSET         20
#define PORT_HOL_CTL0_QUEUE5_DESC_NR_BLEN            4
#define PORT_HOL_CTL0_QUEUE5_DESC_NR_FLAG            HSL_RW

#define QUEUE4_DESC_NR
#define PORT_HOL_CTL0_QUEUE4_DESC_NR_BOFFSET         16
#define PORT_HOL_CTL0_QUEUE4_DESC_NR_BLEN            4
#define PORT_HOL_CTL0_QUEUE4_DESC_NR_FLAG            HSL_RW

#define QUEUE3_DESC_NR
#define PORT_HOL_CTL0_QUEUE3_DESC_NR_BOFFSET         12
#define PORT_HOL_CTL0_QUEUE3_DESC_NR_BLEN            4
#define PORT_HOL_CTL0_QUEUE3_DESC_NR_FLAG            HSL_RW

#define QUEUE2_DESC_NR
#define PORT_HOL_CTL0_QUEUE2_DESC_NR_BOFFSET         8
#define PORT_HOL_CTL0_QUEUE2_DESC_NR_BLEN            4
#define PORT_HOL_CTL0_QUEUE2_DESC_NR_FLAG            HSL_RW

#define QUEUE1_DESC_NR
#define PORT_HOL_CTL0_QUEUE1_DESC_NR_BOFFSET         4
#define PORT_HOL_CTL0_QUEUE1_DESC_NR_BLEN            4
#define PORT_HOL_CTL0_QUEUE1_DESC_NR_FLAG            HSL_RW

#define QUEUE0_DESC_NR
#define PORT_HOL_CTL0_QUEUE0_DESC_NR_BOFFSET         0
#define PORT_HOL_CTL0_QUEUE0_DESC_NR_BLEN            4
#define PORT_HOL_CTL0_QUEUE0_DESC_NR_FLAG            HSL_RW

    /* Port HOL CTL1 Register */
#define PORT_HOL_CTL1
#define PORT_HOL_CTL1_OFFSET         0x0974
#define PORT_HOL_CTL1_E_LENGTH       4
#define PORT_HOL_CTL1_E_OFFSET       0x0008
#define PORT_HOL_CTL1_NR_E           7

#define EG_MIRROR_EN
#define PORT_HOL_CTL1_EG_MIRROR_EN_BOFFSET           16
#define PORT_HOL_CTL1_EG_MIRROR_EN_BLEN              1
#define PORT_HOL_CTL1_EG_MIRROR_EN_FLAG              HSL_RW

#define PORT_RED_EN
#define PORT_HOL_CTL1_PORT_RED_EN_BOFFSET            8
#define PORT_HOL_CTL1_PORT_RED_EN_BLEN               1
#define PORT_HOL_CTL1_PORT_RED_EN_FLAG               HSL_RW

#define PORT_DESC_EN
#define PORT_HOL_CTL1_PORT_DESC_EN_BOFFSET           7
#define PORT_HOL_CTL1_PORT_DESC_EN_BLEN              1
#define PORT_HOL_CTL1_PORT_DESC_EN_FLAG              HSL_RW

#define QUEUE_DESC_EN
#define PORT_HOL_CTL1_QUEUE_DESC_EN_BOFFSET          6
#define PORT_HOL_CTL1_QUEUE_DESC_EN_BLEN             1
#define PORT_HOL_CTL1_QUEUE_DESC_EN_FLAG             HSL_RW

#define PORT_IN_DESC_EN
#define PORT_HOL_CTL1_PORT_IN_DESC_EN_BOFFSET        0
#define PORT_HOL_CTL1_PORT_IN_DESC_EN_BLEN           4
#define PORT_HOL_CTL1_PORT_IN_DESC_EN_FLAG           HSL_RW




    /* mib memory info */
#define MIB_RXBROAD
#define MIB_RXBROAD_OFFSET                0x01000
#define MIB_RXBROAD_E_LENGTH              4
#define MIB_RXBROAD_E_OFFSET              0x100
#define MIB_RXBROAD_NR_E                  7

#define MIB_RXPAUSE
#define MIB_RXPAUSE_OFFSET                0x01004
#define MIB_RXPAUSE_E_LENGTH              4
#define MIB_RXPAUSE_E_OFFSET              0x100
#define MIB_RXPAUSE_NR_E                  7

#define MIB_RXMULTI
#define MIB_RXMULTI_OFFSET                0x01008
#define MIB_RXMULTI_E_LENGTH              4
#define MIB_RXMULTI_E_OFFSET              0x100
#define MIB_RXMULTI_NR_E                  7

#define MIB_RXFCSERR
#define MIB_RXFCSERR_OFFSET               0x0100c
#define MIB_RXFCSERR_E_LENGTH             4
#define MIB_RXFCSERR_E_OFFSET             0x100
#define MIB_RXFCSERR_NR_E                 7

#define MIB_RXALLIGNERR
#define MIB_RXALLIGNERR_OFFSET            0x01010
#define MIB_RXALLIGNERR_E_LENGTH          4
#define MIB_RXALLIGNERR_E_OFFSET          0x100
#define MIB_RXALLIGNERR_NR_E              7

#define MIB_RXRUNT
#define MIB_RXRUNT_OFFSET                 0x01014
#define MIB_RXRUNT_E_LENGTH               4
#define MIB_RXRUNT_E_OFFSET               0x100
#define MIB_RXRUNT_NR_E                   7

#define MIB_RXFRAGMENT
#define MIB_RXFRAGMENT_OFFSET             0x01018
#define MIB_RXFRAGMENT_E_LENGTH           4
#define MIB_RXFRAGMENT_E_OFFSET           0x100
#define MIB_RXFRAGMENT_NR_E               7

#define MIB_RX64BYTE
#define MIB_RX64BYTE_OFFSET               0x0101c
#define MIB_RX64BYTE_E_LENGTH             4
#define MIB_RX64BYTE_E_OFFSET             0x100
#define MIB_RX64BYTE_NR_E                 7

#define MIB_RX128BYTE
#define MIB_RX128BYTE_OFFSET              0x01020
#define MIB_RX128BYTE_E_LENGTH            4
#define MIB_RX128BYTE_E_OFFSET            0x100
#define MIB_RX128BYTE_NR_E                7

#define MIB_RX256BYTE
#define MIB_RX256BYTE_OFFSET              0x01024
#define MIB_RX256BYTE_E_LENGTH            4
#define MIB_RX256BYTE_E_OFFSET            0x100
#define MIB_RX256BYTE_NR_E                7

#define MIB_RX512BYTE
#define MIB_RX512BYTE_OFFSET              0x01028
#define MIB_RX512BYTE_E_LENGTH            4
#define MIB_RX512BYTE_E_OFFSET            0x100
#define MIB_RX512BYTE_NR_E                7

#define MIB_RX1024BYTE
#define MIB_RX1024BYTE_OFFSET             0x0102c
#define MIB_RX1024BYTE_E_LENGTH           4
#define MIB_RX1024BYTE_E_OFFSET           0x100
#define MIB_RX1024BYTE_NR_E               7

#define MIB_RX1518BYTE
#define MIB_RX1518BYTE_OFFSET             0x01030
#define MIB_RX1518BYTE_E_LENGTH           4
#define MIB_RX1518BYTE_E_OFFSET           0x100
#define MIB_RX1518BYTE_NR_E               7

#define MIB_RXMAXBYTE
#define MIB_RXMAXBYTE_OFFSET              0x01034
#define MIB_RXMAXBYTE_E_LENGTH            4
#define MIB_RXMAXBYTE_E_OFFSET            0x100
#define MIB_RXMAXBYTE_NR_E                7

#define MIB_RXTOOLONG
#define MIB_RXTOOLONG_OFFSET              0x01038
#define MIB_RXTOOLONG_E_LENGTH            4
#define MIB_RXTOOLONG_E_OFFSET            0x100
#define MIB_RXTOOLONG_NR_E                7

#define MIB_RXGOODBYTE_LO
#define MIB_RXGOODBYTE_LO_OFFSET          0x0103c
#define MIB_RXGOODBYTE_LO_E_LENGTH        4
#define MIB_RXGOODBYTE_LO_E_OFFSET        0x100
#define MIB_RXGOODBYTE_LO_NR_E            7

#define MIB_RXGOODBYTE_HI
#define MIB_RXGOODBYTE_HI_OFFSET          0x01040
#define MIB_RXGOODBYTE_HI_E_LENGTH        4
#define MIB_RXGOODBYTE_HI_E_OFFSET        0x100
#define MIB_RXGOODBYTE_HI_NR_E            7

#define MIB_RXBADBYTE_LO
#define MIB_RXBADBYTE_LO_OFFSET           0x01044
#define MIB_RXBADBYTE_LO_E_LENGTH         4
#define MIB_RXBADBYTE_LO_E_OFFSET         0x100
#define MIB_RXBADBYTE_LO_NR_E             7

#define MIB_RXBADBYTE_HI
#define MIB_RXBADBYTE_HI_OFFSET           0x01048
#define MIB_RXBADBYTE_HI_E_LENGTH         4
#define MIB_RXBADBYTE_HI_E_OFFSET         0x100
#define MIB_RXBADBYTE_HI_NR_E             7

#define MIB_RXOVERFLOW
#define MIB_RXOVERFLOW_OFFSET             0x0104c
#define MIB_RXOVERFLOW_E_LENGTH           4
#define MIB_RXOVERFLOW_E_OFFSET           0x100
#define MIB_RXOVERFLOW_NR_E               7

#define MIB_FILTERED
#define MIB_FILTERED_OFFSET               0x01050
#define MIB_FILTERED_E_LENGTH             4
#define MIB_FILTERED_E_OFFSET             0x100
#define MIB_FILTERED_NR_E                 7

#define MIB_TXBROAD
#define MIB_TXBROAD_OFFSET                0x01054
#define MIB_TXBROAD_E_LENGTH              4
#define MIB_TXBROAD_E_OFFSET              0x100
#define MIB_TXBROAD_NR_E                  7

#define MIB_TXPAUSE
#define MIB_TXPAUSE_OFFSET                0x01058
#define MIB_TXPAUSE_E_LENGTH              4
#define MIB_TXPAUSE_E_OFFSET              0x100
#define MIB_TXPAUSE_NR_E                  7

#define MIB_TXMULTI
#define MIB_TXMULTI_OFFSET                0x0105c
#define MIB_TXMULTI_E_LENGTH              4
#define MIB_TXMULTI_E_OFFSET              0x100
#define MIB_TXMULTI_NR_E                  7

#define MIB_TXUNDERRUN
#define MIB_TXUNDERRUN_OFFSET             0x01060
#define MIB_TXUNDERRUN_E_LENGTH           4
#define MIB_TXUNDERRUN_E_OFFSET           0x100
#define MIB_TXUNDERRUN_NR_E               7

#define MIB_TX64BYTE
#define MIB_TX64BYTE_OFFSET               0x01064
#define MIB_TX64BYTE_E_LENGTH             4
#define MIB_TX64BYTE_E_OFFSET             0x100
#define MIB_TX64BYTE_NR_E                 7

#define MIB_TX128BYTE
#define MIB_TX128BYTE_OFFSET              0x01068
#define MIB_TX128BYTE_E_LENGTH            4
#define MIB_TX128BYTE_E_OFFSET            0x100
#define MIB_TX128BYTE_NR_E                7

#define MIB_TX256BYTE
#define MIB_TX256BYTE_OFFSET              0x0106c
#define MIB_TX256BYTE_E_LENGTH            4
#define MIB_TX256BYTE_E_OFFSET            0x100
#define MIB_TX256BYTE_NR_E                7

#define MIB_TX512BYTE
#define MIB_TX512BYTE_OFFSET              0x01070
#define MIB_TX512BYTE_E_LENGTH            4
#define MIB_TX512BYTE_E_OFFSET            0x100
#define MIB_TX512BYTE_NR_E                7

#define MIB_TX1024BYTE
#define MIB_TX1024BYTE_OFFSET             0x01074
#define MIB_TX1024BYTE_E_LENGTH           4
#define MIB_TX1024BYTE_E_OFFSET           0x100
#define MIB_TX1024BYTE_NR_E               7

#define MIB_TX1518BYTE
#define MIB_TX1518BYTE_OFFSET             0x01078
#define MIB_TX1518BYTE_E_LENGTH           4
#define MIB_TX1518BYTE_E_OFFSET           0x100
#define MIB_TX1518BYTE_NR_E               7

#define MIB_TXMAXBYTE
#define MIB_TXMAXBYTE_OFFSET              0x0107c
#define MIB_TXMAXBYTE_E_LENGTH            4
#define MIB_TXMAXBYTE_E_OFFSET            0x100
#define MIB_TXMAXBYTE_NR_E                7

#define MIB_TXOVERSIZE
#define MIB_TXOVERSIZE_OFFSET             0x01080
#define MIB_TXOVERSIZE_E_LENGTH           4
#define MIB_TXOVERSIZE_E_OFFSET           0x100
#define MIB_TXOVERSIZE_NR_E               7

#define MIB_TXBYTE_LO
#define MIB_TXBYTE_LO_OFFSET              0x01084
#define MIB_TXBYTE_LO_E_LENGTH            4
#define MIB_TXBYTE_LO_E_OFFSET            0x100
#define MIB_TXBYTE_LO_NR_E                7

#define MIB_TXBYTE_HI
#define MIB_TXBYTE_HI_OFFSET              0x01088
#define MIB_TXBYTE_HI_E_LENGTH            4
#define MIB_TXBYTE_HI_E_OFFSET            0x100
#define MIB_TXBYTE_HI_NR_E                7

#define MIB_TXCOLLISION
#define MIB_TXCOLLISION_OFFSET            0x0108c
#define MIB_TXCOLLISION_E_LENGTH          4
#define MIB_TXCOLLISION_E_OFFSET          0x100
#define MIB_TXCOLLISION_NR_E              7

#define MIB_TXABORTCOL
#define MIB_TXABORTCOL_OFFSET             0x01090
#define MIB_TXABORTCOL_E_LENGTH           4
#define MIB_TXABORTCOL_E_OFFSET           0x100
#define MIB_TXABORTCOL_NR_E               7

#define MIB_TXMULTICOL
#define MIB_TXMULTICOL_OFFSET             0x01094
#define MIB_TXMULTICOL_E_LENGTH           4
#define MIB_TXMULTICOL_E_OFFSET           0x100
#define MIB_TXMULTICOL_NR_E               7

#define MIB_TXSINGALCOL
#define MIB_TXSINGALCOL_OFFSET            0x01098
#define MIB_TXSINGALCOL_E_LENGTH          4
#define MIB_TXSINGALCOL_E_OFFSET          0x100
#define MIB_TXSINGALCOL_NR_E              7

#define MIB_TXEXCDEFER
#define MIB_TXEXCDEFER_OFFSET             0x0109c
#define MIB_TXEXCDEFER_E_LENGTH           4
#define MIB_TXEXCDEFER_E_OFFSET           0x100
#define MIB_TXEXCDEFER_NR_E               7

#define MIB_TXDEFER
#define MIB_TXDEFER_OFFSET                0x010a0
#define MIB_TXDEFER_E_LENGTH              4
#define MIB_TXDEFER_E_OFFSET              0x100
#define MIB_TXDEFER_NR_E                  7

#define MIB_TXLATECOL
#define MIB_TXLATECOL_OFFSET              0x010a4
#define MIB_TXLATECOL_E_LENGTH            4
#define MIB_TXLATECOL_E_OFFSET            0x100
#define MIB_TXLATECOL_NR_E                7

#define MIB_RXUNICAST
#define MIB_RXUNICAST_OFFSET              0x010a8
#define MIB_RXUNICAST_E_LENGTH            4
#define MIB_RXUNICAST_E_OFFSET            0x100
#define MIB_RXUNICAST_NR_E                7

#define MIB_TXUNICAST
#define MIB_TXUNICAST_OFFSET              0x010ac
#define MIB_TXUNICAST_E_LENGTH            4
#define MIB_TXUNICAST_E_OFFSET            0x100
#define MIB_TXUNICAST_NR_E                7

	/* Flow Congestion Drop CTRL0 */
#define FLOW_CONGE_DROP_CTRL0
#define FLOW_CONGE_DROP_CTRL0_OFFSET         0x0b74
#define FLOW_CONGE_DROP_CTRL0_E_LENGTH       4
#define FLOW_CONGE_DROP_CTRL0_E_OFFSET       4
#define FLOW_CONGE_DROP_CTRL0_NR_E           1

#define EN5
#define FLOW_CONGE_DROP_CTRL0_EN5_BOFFSET        22
#define FLOW_CONGE_DROP_CTRL0_EN5_BLEN           6
#define FLOW_CONGE_DROP_CTRL0_EN5_FLAG           HSL_RW

#define EN4
#define FLOW_CONGE_DROP_CTRL0_EN4_BOFFSET        18
#define FLOW_CONGE_DROP_CTRL0_EN4_BLEN           4
#define FLOW_CONGE_DROP_CTRL0_EN4_FLAG           HSL_RW

#define EN3
#define FLOW_CONGE_DROP_CTRL0_EN3_BOFFSET        14
#define FLOW_CONGE_DROP_CTRL0_EN3_BLEN           4
#define FLOW_CONGE_DROP_CTRL0_EN3_FLAG           HSL_RW

#define EN2
#define FLOW_CONGE_DROP_CTRL0_EN2_BOFFSET        10
#define FLOW_CONGE_DROP_CTRL0_EN2_BLEN           4
#define FLOW_CONGE_DROP_CTRL0_EN2_FLAG           HSL_RW

#define EN1
#define FLOW_CONGE_DROP_CTRL0_EN1_BOFFSET        6
#define FLOW_CONGE_DROP_CTRL0_EN1_BLEN           4
#define FLOW_CONGE_DROP_CTRL0_EN1_FLAG           HSL_RW

#define EN0
#define FLOW_CONGE_DROP_CTRL0_EN0_BOFFSET        0
#define FLOW_CONGE_DROP_CTRL0_EN0_BLEN           6
#define FLOW_CONGE_DROP_CTRL0_EN0_FLAG           HSL_RW

		/* Ring Flow Control Threshold Register*/
#define RING_FLOW_CTRL_THRES
#define RING_FLOW_CTRL_THRES_OFFSET         0x0b80
#define RING_FLOW_CTRL_THRES_E_LENGTH       4
#define RING_FLOW_CTRL_THRES_E_OFFSET       4
#define RING_FLOW_CTRL_THRES_NR_E           8

#define XON
#define RING_FLOW_CTRL_THRES_XON_BOFFSET        16
#define RING_FLOW_CTRL_THRES_XON_BLEN           8
#define RING_FLOW_CTRL_THRES_XON_FLAG           HSL_RW

#define XOFF
#define RING_FLOW_CTRL_THRES_XOFF_BOFFSET        0
#define RING_FLOW_CTRL_THRES_XOFF_BLEN           8
#define RING_FLOW_CTRL_THRES_XOFF_FLAG           HSL_RW




    /* ACL Counter Register0 */
#define ACL_COUNTER0
#define ACL_COUNTER0_OFFSET         0x1c000
#define ACL_COUNTER0_E_LENGTH       4
#define ACL_COUNTER0_E_OFFSET       0x0008
#define ACL_COUNTER0_NR_E           32

    /* ACL Counter Register1 */
#define ACL_COUNTER1
#define ACL_COUNTER1_OFFSET         0x1c004
#define ACL_COUNTER1_E_LENGTH       4
#define ACL_COUNTER1_E_OFFSET       0x0008
#define ACL_COUNTER1_NR_E           32





    /* Port Rate Limit2 Register */
#define WRR_CTRL
#define WRR_CTRL_OFFSET                         0x0830
#define WRR_CTRL_E_LENGTH                       4
#define WRR_CTRL_E_OFFSET                       0x0004
#define WRR_CTRL_NR_E                           7

#define SCH_MODE
#define WRR_CTRL_SCH_MODE_BOFFSET               30
#define WRR_CTRL_SCH_MODE_BLEN                  2
#define WRR_CTRL_SCH_MODE_FLAG                  HSL_RW

#define Q5_W
#define WRR_CTRL_Q5_W_BOFFSET                   25
#define WRR_CTRL_Q5_W_BLEN                      5
#define WRR_CTRL_Q5_W_FLAG                      HSL_RW

#define Q4_W
#define WRR_CTRL_Q4_W_BOFFSET                   20
#define WRR_CTRL_Q4_W_BLEN                      5
#define WRR_CTRL_Q4_W_FLAG                      HSL_RW

#define Q3_W
#define WRR_CTRL_Q3_W_BOFFSET                   15
#define WRR_CTRL_Q3_W_BLEN                      5
#define WRR_CTRL_Q3_W_FLAG                      HSL_RW

#define Q2_W
#define WRR_CTRL_Q2_W_BOFFSET                   10
#define WRR_CTRL_Q2_W_BLEN                      5
#define WRR_CTRL_Q2_W_FLAG                      HSL_RW

#define Q1_W
#define WRR_CTRL_Q1_W_BOFFSET                   5
#define WRR_CTRL_Q1_W_BLEN                      5
#define WRR_CTRL_Q1_W_FLAG                      HSL_RW

#define Q0_W
#define WRR_CTRL_Q0_W_BOFFSET                   0
#define WRR_CTRL_Q0_W_BLEN                      5
#define WRR_CTRL_Q0_W_FLAG                      HSL_RW


    /* ACL Action Register */
#define ACL_RSLT0                         10
#define ACL_RSLT0_OFFSET                  0x5a000
#define ACL_RSLT0_E_LENGTH                4
#define ACL_RSLT0_E_OFFSET                0x10
#define ACL_RSLT0_NR_E                    96

#define CTAGPRI
#define ACL_RSLT0_CTAGPRI_BOFFSET         29
#define ACL_RSLT0_CTAGPRI_BLEN            3
#define ACL_RSLT0_CTAGPRI_FLAG            HSL_RW

#define CTAGCFI
#define ACL_RSLT0_CTAGCFI_BOFFSET         28
#define ACL_RSLT0_CTAGCFI_BLEN            1
#define ACL_RSLT0_CTAGCFI_FLAG            HSL_RW

#define CTAGVID
#define ACL_RSLT0_CTAGVID_BOFFSET         16
#define ACL_RSLT0_CTAGVID_BLEN            12
#define ACL_RSLT0_CTAGVID_FLAG            HSL_RW

#define STAGPRI
#define ACL_RSLT0_STAGPRI_BOFFSET         13
#define ACL_RSLT0_STAGPRI_BLEN            3
#define ACL_RSLT0_STAGPRI_FLAG            HSL_RW

#define STAGDEI
#define ACL_RSLT0_STAGDEI_BOFFSET         12
#define ACL_RSLT0_STAGDEI_BLEN            1
#define ACL_RSLT0_STAGDEI_FLAG            HSL_RW

#define STAGVID
#define ACL_RSLT0_STAGVID_BOFFSET         0
#define ACL_RSLT0_STAGVID_BLEN            12
#define ACL_RSLT0_STAGVID_FLAG            HSL_RW


#define ACL_RSLT1                         11
#define ACL_RSLT1_OFFSET                  0x5a004
#define ACL_RSLT1_E_LENGTH                4
#define ACL_RSLT1_E_OFFSET                0x10
#define ACL_RSLT1_NR_E                    96

#define DES_PORT0
#define ACL_RSLT1_DES_PORT0_BOFFSET       29
#define ACL_RSLT1_DES_PORT0_BLEN          3
#define ACL_RSLT1_DES_PORT0_FLAG          HSL_RW

#define PRI_QU_EN
#define ACL_RSLT1_PRI_QU_EN_BOFFSET       28
#define ACL_RSLT1_PRI_QU_EN_BLEN          1
#define ACL_RSLT1_PRI_QU_EN_FLAG          HSL_RW

#define PRI_QU
#define ACL_RSLT1_PRI_QU_BOFFSET          25
#define ACL_RSLT1_PRI_QU_BLEN             3
#define ACL_RSLT1_PRI_QU_FLAG             HSL_RW

#define WCMP_EN
#define ACL_RSLT1_WCMP_EN_BOFFSET         24
#define ACL_RSLT1_WCMP_EN_BLEN            1
#define ACL_RSLT1_WCMP_EN_FLAG            HSL_RW

#define ARP_PTR
#define ACL_RSLT1_ARP_PTR_BOFFSET         17
#define ACL_RSLT1_ARP_PTR_BLEN            7
#define ACL_RSLT1_ARP_PTR_FLAG            HSL_RW

#define ARP_PTR_EN
#define ACL_RSLT1_ARP_PTR_EN_BOFFSET      16
#define ACL_RSLT1_ARP_PTR_EN_BLEN         1
#define ACL_RSLT1_ARP_PTR_EN_FLAG         HSL_RW

#define FORCE_L3_MODE
#define ACL_RSLT1_FORCE_L3_MODE_BOFFSET   14
#define ACL_RSLT1_FORCE_L3_MODE_BLEN      2
#define ACL_RSLT1_FORCE_L3_MODE_FLAG      HSL_RW

#define LOOK_VID_CHG
#define ACL_RSLT1_LOOK_VID_CHG_BOFFSET    13
#define ACL_RSLT1_LOOK_VID_CHG_BLEN       1
#define ACL_RSLT1_LOOK_VID_CHG_FLAG       HSL_RW

#define TRANS_CVID_CHG
#define ACL_RSLT1_TRANS_CVID_CHG_BOFFSET  12
#define ACL_RSLT1_TRANS_CVID_CHG_BLEN     1
#define ACL_RSLT1_TRANS_CVID_CHG_FLAG     HSL_RW

#define TRANS_SVID_CHG
#define ACL_RSLT1_TRANS_SVID_CHG_BOFFSET  11
#define ACL_RSLT1_TRANS_SVID_CHG_BLEN     1
#define ACL_RSLT1_TRANS_SVID_CHG_FLAG     HSL_RW

#define CTAG_CFI_CHG
#define ACL_RSLT1_CTAG_CFI_CHG_BOFFSET    10
#define ACL_RSLT1_CTAG_CFI_CHG_BLEN       1
#define ACL_RSLT1_CTAG_CFI_CHG_FLAG       HSL_RW

#define CTAG_PRI_REMAP
#define ACL_RSLT1_CTAG_PRI_REMAP_BOFFSET  9
#define ACL_RSLT1_CTAG_PRI_REMAP_BLEN     1
#define ACL_RSLT1_CTAG_PRI_REMAP_FLAG     HSL_RW

#define STAG_DEI_CHG
#define ACL_RSLT1_STAG_DEI_CHG_BOFFSET    8
#define ACL_RSLT1_STAG_DEI_CHG_BLEN       1
#define ACL_RSLT1_STAG_DEI_CHG_FLAG       HSL_RW

#define STAG_PRI_REMAP
#define ACL_RSLT1_STAG_PRI_REMAP_BOFFSET  7
#define ACL_RSLT1_STAG_PRI_REMAP_BLEN     1
#define ACL_RSLT1_STAG_PRI_REMAP_FLAG     HSL_RW

#define DSCP_REMAP
#define ACL_RSLT1_DSCP_REMAP_BOFFSET      6
#define ACL_RSLT1_DSCP_REMAP_BLEN         1
#define ACL_RSLT1_DSCP_REMAP_FLAG         HSL_RW

#define DSCPV
#define ACL_RSLT1_DSCPV_BOFFSET           0
#define ACL_RSLT1_DSCPV_BLEN              6
#define ACL_RSLT1_DSCPV_FLAG              HSL_RW

#define ACL_RSLT2                         12
#define ACL_RSLT2_OFFSET                  0x5a008
#define ACL_RSLT2_E_LENGTH                4
#define ACL_RSLT2_E_OFFSET                0x10
#define ACL_RSLT2_NR_E                    96

#define TRIGGER_INTR
#define ACL_RSLT2_TRIGGER_INTR_BOFFSET    16
#define ACL_RSLT2_TRIGGER_INTR_BLEN       1
#define ACL_RSLT2_TRIGGER_INTR_FLAG       HSL_RW

#define EG_BYPASS
#define ACL_RSLT2_EG_BYPASS_BOFFSET       15
#define ACL_RSLT2_EG_BYPASS_BLEN          1
#define ACL_RSLT2_EG_BYPASS_FLAG          HSL_RW

#define POLICER_EN
#define ACL_RSLT2_POLICER_EN_BOFFSET      14
#define ACL_RSLT2_POLICER_EN_BLEN         1
#define ACL_RSLT2_POLICER_EN_FLAG         HSL_RW

#define POLICER_PTR
#define ACL_RSLT2_POLICER_PTR_BOFFSET     9
#define ACL_RSLT2_POLICER_PTR_BLEN        5
#define ACL_RSLT2_POLICER_PTR_FLAG        HSL_RW

#define FWD_CMD
#define ACL_RSLT2_FWD_CMD_BOFFSET         6
#define ACL_RSLT2_FWD_CMD_BLEN            3
#define ACL_RSLT2_FWD_CMD_FLAG            HSL_RW

#define MIRR_EN
#define ACL_RSLT2_MIRR_EN_BOFFSET         5
#define ACL_RSLT2_MIRR_EN_BLEN            1
#define ACL_RSLT2_MIRR_EN_FLAG            HSL_RW

#define DES_PORT_EN
#define ACL_RSLT2_DES_PORT_EN_BOFFSET     4
#define ACL_RSLT2_DES_PORT_EN_BLEN        1
#define ACL_RSLT2_DES_PORT_EN_FLAG        HSL_RW

#define DES_PORT1
#define ACL_RSLT2_DES_PORT1_BOFFSET       0
#define ACL_RSLT2_DES_PORT1_BLEN          4
#define ACL_RSLT2_DES_PORT1_FLAG          HSL_RW




    /* MAC Type Rule Field Define */
#define MAC_RUL_V0                         0
#define MAC_RUL_V0_OFFSET                  0x58000
#define MAC_RUL_V0_E_LENGTH                4
#define MAC_RUL_V0_E_OFFSET                0x20
#define MAC_RUL_V0_NR_E                    96

#define DAV_BYTE2
#define MAC_RUL_V0_DAV_BYTE2_BOFFSET       24
#define MAC_RUL_V0_DAV_BYTE2_BLEN          8
#define MAC_RUL_V0_DAV_BYTE2_FLAG          HSL_RW

#define DAV_BYTE3
#define MAC_RUL_V0_DAV_BYTE3_BOFFSET       16
#define MAC_RUL_V0_DAV_BYTE3_BLEN          8
#define MAC_RUL_V0_DAV_BYTE3_FLAG          HSL_RW

#define DAV_BYTE4
#define MAC_RUL_V0_DAV_BYTE4_BOFFSET       8
#define MAC_RUL_V0_DAV_BYTE4_BLEN          8
#define MAC_RUL_V0_DAV_BYTE4_FLAG          HSL_RW

#define DAV_BYTE5
#define MAC_RUL_V0_DAV_BYTE5_BOFFSET       0
#define MAC_RUL_V0_DAV_BYTE5_BLEN          8
#define MAC_RUL_V0_DAV_BYTE5_FLAG          HSL_RW


#define MAC_RUL_V1                         1
#define MAC_RUL_V1_OFFSET                  0x58004
#define MAC_RUL_V1_E_LENGTH                4
#define MAC_RUL_V1_E_OFFSET                0x20
#define MAC_RUL_V1_NR_E                    96

#define SAV_BYTE4
#define MAC_RUL_V1_SAV_BYTE4_BOFFSET       24
#define MAC_RUL_V1_SAV_BYTE4_BLEN          8
#define MAC_RUL_V1_SAV_BYTE4_FLAG          HSL_RW

#define SAV_BYTE5
#define MAC_RUL_V1_SAV_BYTE5_BOFFSET       16
#define MAC_RUL_V1_SAV_BYTE5_BLEN          8
#define MAC_RUL_V1_SAV_BYTE5_FLAG          HSL_RW

#define DAV_BYTE0
#define MAC_RUL_V1_DAV_BYTE0_BOFFSET       8
#define MAC_RUL_V1_DAV_BYTE0_BLEN          8
#define MAC_RUL_V1_DAV_BYTE0_FLAG          HSL_RW

#define DAV_BYTE1
#define MAC_RUL_V1_DAV_BYTE1_BOFFSET       0
#define MAC_RUL_V1_DAV_BYTE1_BLEN          8
#define MAC_RUL_V1_DAV_BYTE1_FLAG          HSL_RW


#define MAC_RUL_V2                         2
#define MAC_RUL_V2_OFFSET                  0x58008
#define MAC_RUL_V2_E_LENGTH                4
#define MAC_RUL_V2_E_OFFSET                0x20
#define MAC_RUL_V2_NR_E                    96

#define SAV_BYTE0
#define MAC_RUL_V2_SAV_BYTE0_BOFFSET       24
#define MAC_RUL_V2_SAV_BYTE0_BLEN          8
#define MAC_RUL_V2_SAV_BYTE0_FLAG          HSL_RW

#define SAV_BYTE1
#define MAC_RUL_V2_SAV_BYTE1_BOFFSET       16
#define MAC_RUL_V2_SAV_BYTE1_BLEN          8
#define MAC_RUL_V2_SAV_BYTE1_FLAG          HSL_RW

#define SAV_BYTE2
#define MAC_RUL_V2_SAV_BYTE2_BOFFSET       8
#define MAC_RUL_V2_SAV_BYTE2_BLEN          8
#define MAC_RUL_V2_SAV_BYTE2_FLAG          HSL_RW

#define SAV_BYTE3
#define MAC_RUL_V2_SAV_BYTE3_BOFFSET       0
#define MAC_RUL_V2_SAV_BYTE3_BLEN          8
#define MAC_RUL_V2_SAV_BYTE3_FLAG          HSL_RW


#define MAC_RUL_V3                         3
#define MAC_RUL_V3_ID                      13
#define MAC_RUL_V3_OFFSET                  0x5800c
#define MAC_RUL_V3_E_LENGTH                4
#define MAC_RUL_V3_E_OFFSET                0x20
#define MAC_RUL_V3_NR_E                    96

#define ETHTYPV
#define MAC_RUL_V3_ETHTYPV_BOFFSET         16
#define MAC_RUL_V3_ETHTYPV_BLEN            16
#define MAC_RUL_V3_ETHTYPV_FLAG            HSL_RW

#define VLANPRIV
#define MAC_RUL_V3_VLANPRIV_BOFFSET        13
#define MAC_RUL_V3_VLANPRIV_BLEN           3
#define MAC_RUL_V3_VLANPRIV_FLAG           HSL_RW

#define VLANCFIV
#define MAC_RUL_V3_VLANCFIV_BOFFSET        12
#define MAC_RUL_V3_VLANCFIV_BLEN           1
#define MAC_RUL_V3_VLANCFIV_FLAG           HSL_RW

#define VLANIDV
#define MAC_RUL_V3_VLANIDV_BOFFSET         0
#define MAC_RUL_V3_VLANIDV_BLEN            12
#define MAC_RUL_V3_VLANIDV_FLAG            HSL_RW


#define MAC_RUL_V4                         4
#define MAC_RUL_V4_OFFSET                  0x58010
#define MAC_RUL_V4_E_LENGTH                4
#define MAC_RUL_V4_E_OFFSET                0x20
#define MAC_RUL_V4_NR_E                    96

#define RULE_INV
#define MAC_RUL_V4_RULE_INV_BOFFSET        7
#define MAC_RUL_V4_RULE_INV_BLEN           1
#define MAC_RUL_V4_RULE_INV_FLAG           HSL_RW

#define SRC_PT
#define MAC_RUL_V4_SRC_PT_BOFFSET          0
#define MAC_RUL_V4_SRC_PT_BLEN             7
#define MAC_RUL_V4_SRC_PT_FLAG             HSL_RW


#define MAC_RUL_M0                         5
#define MAC_RUL_M0_OFFSET                  0x59000
#define MAC_RUL_M0_E_LENGTH                4
#define MAC_RUL_M0_E_OFFSET                0x20
#define MAC_RUL_M0_NR_E                    96

#define DAM_BYTE2
#define MAC_RUL_M0_DAM_BYTE2_BOFFSET       24
#define MAC_RUL_M0_DAM_BYTE2_BLEN          8
#define MAC_RUL_M0_DAM_BYTE2_FLAG          HSL_RW

#define DAM_BYTE3
#define MAC_RUL_M0_DAM_BYTE3_BOFFSET       16
#define MAC_RUL_M0_DAM_BYTE3_BLEN          8
#define MAC_RUL_M0_DAM_BYTE3_FLAG          HSL_RW

#define DAM_BYTE4
#define MAC_RUL_M0_DAM_BYTE4_BOFFSET       8
#define MAC_RUL_M0_DAM_BYTE4_BLEN          8
#define MAC_RUL_M0_DAM_BYTE4_FLAG          HSL_RW

#define DAM_BYTE5
#define MAC_RUL_M0_DAM_BYTE5_BOFFSET       0
#define MAC_RUL_M0_DAM_BYTE5_BLEN          8
#define MAC_RUL_M0_DAM_BYTE5_FLAG          HSL_RW


#define MAC_RUL_M1                         6
#define MAC_RUL_M1_OFFSET                  0x59004
#define MAC_RUL_M1_E_LENGTH                4
#define MAC_RUL_M1_E_OFFSET                0x20
#define MAC_RUL_M1_NR_E                    96

#define SAM_BYTE4
#define MAC_RUL_M1_SAM_BYTE4_BOFFSET       24
#define MAC_RUL_M1_SAM_BYTE4_BLEN          8
#define MAC_RUL_M1_SAM_BYTE4_FLAG          HSL_RW

#define SAM_BYTE5
#define MAC_RUL_M1_SAM_BYTE5_BOFFSET       16
#define MAC_RUL_M1_SAM_BYTE5_BLEN          8
#define MAC_RUL_M1_SAM_BYTE5_FLAG          HSL_RW

#define DAM_BYTE0
#define MAC_RUL_M1_DAM_BYTE0_BOFFSET       8
#define MAC_RUL_M1_DAM_BYTE0_BLEN          8
#define MAC_RUL_M1_DAM_BYTE0_FLAG          HSL_RW

#define DAM_BYTE1
#define MAC_RUL_M1_DAM_BYTE1_BOFFSET       0
#define MAC_RUL_M1_DAM_BYTE1_BLEN          8
#define MAC_RUL_M1_DAM_BYTE1_FLAG          HSL_RW


#define MAC_RUL_M2                         7
#define MAC_RUL_M2_OFFSET                  0x59008
#define MAC_RUL_M2_E_LENGTH                4
#define MAC_RUL_M2_E_OFFSET                0x20
#define MAC_RUL_M2_NR_E                    96

#define SAM_BYTE0
#define MAC_RUL_M2_SAM_BYTE0_BOFFSET       24
#define MAC_RUL_M2_SAM_BYTE0_BLEN          8
#define MAC_RUL_M2_SAM_BYTE0_FLAG          HSL_RW

#define SAM_BYTE1
#define MAC_RUL_M2_SAM_BYTE1_BOFFSET       16
#define MAC_RUL_M2_SAM_BYTE1_BLEN          8
#define MAC_RUL_M2_SAM_BYTE1_FLAG          HSL_RW

#define SAM_BYTE2
#define MAC_RUL_M2_SAM_BYTE2_BOFFSET       8
#define MAC_RUL_M2_SAM_BYTE2_BLEN          8
#define MAC_RUL_M2_SAM_BYTE2_FLAG          HSL_RW

#define SAM_BYTE3
#define MAC_RUL_M2_SAM_BYTE3_BOFFSET       0
#define MAC_RUL_M2_SAM_BYTE3_BLEN          8
#define MAC_RUL_M2_SAM_BYTE3_FLAG          HSL_RW


#define MAC_RUL_M3                         8
#define MAC_RUL_M3_OFFSET                  0x5900c
#define MAC_RUL_M3_E_LENGTH                4
#define MAC_RUL_M3_E_OFFSET                0x20
#define MAC_RUL_M3_NR_E                    96

#define ETHTYPM
#define MAC_RUL_M3_ETHTYPM_BOFFSET         16
#define MAC_RUL_M3_ETHTYPM_BLEN            16
#define MAC_RUL_M3_ETHTYPM_FLAG            HSL_RW

#define VLANPRIM
#define MAC_RUL_M3_VLANPRIM_BOFFSET        13
#define MAC_RUL_M3_VLANPRIM_BLEN           3
#define MAC_RUL_M3_VLANPRIM_FLAG           HSL_RW

#define VLANCFIM
#define MAC_RUL_M3_VLANCFIM_BOFFSET        12
#define MAC_RUL_M3_VLANCFIM_BLEN           1
#define MAC_RUL_M3_VLANCFIM_FLAG           HSL_RW

#define VLANIDM
#define MAC_RUL_M3_VLANIDM_BOFFSET         0
#define MAC_RUL_M3_VLANIDM_BLEN            12
#define MAC_RUL_M3_VLANIDM_FLAG            HSL_RW


#define MAC_RUL_M4                         9
#define MAC_RUL_M4_OFFSET                  0x59010
#define MAC_RUL_M4_E_LENGTH                4
#define MAC_RUL_M4_E_OFFSET                0x20
#define MAC_RUL_M4_NR_E                    96

#define RULE_VALID
#define MAC_RUL_M4_RULE_VALID_BOFFSET      6
#define MAC_RUL_M4_RULE_VALID_BLEN         2
#define MAC_RUL_M4_RULE_VALID_FLAG         HSL_RW

#define TAGGEDM
#define MAC_RUL_M4_TAGGEDM_BOFFSET         5
#define MAC_RUL_M4_TAGGEDM_BLEN            1
#define MAC_RUL_M4_TAGGEDM_FLAG            HSL_RW

#define TAGGEDV
#define MAC_RUL_M4_TAGGEDV_BOFFSET         4
#define MAC_RUL_M4_TAGGEDV_BLEN            1
#define MAC_RUL_M4_TAGGEDV_FLAG            HSL_RW

#define VIDMSK
#define MAC_RUL_M4_VIDMSK_BOFFSET          3
#define MAC_RUL_M4_VIDMSK_BLEN             1
#define MAC_RUL_M4_VIDMSK_FLAG             HSL_RW

#define RULE_TYP
#define MAC_RUL_M4_RULE_TYP_BOFFSET        0
#define MAC_RUL_M4_RULE_TYP_BLEN           3
#define MAC_RUL_M4_RULE_TYP_FLAG           HSL_RW




    /* IP4 Type Rule Field Define */
#define IP4_RUL_V0                         0
#define IP4_RUL_V0_OFFSET                  0x58000
#define IP4_RUL_V0_E_LENGTH                4
#define IP4_RUL_V0_E_OFFSET                0x20
#define IP4_RUL_V0_NR_E                    96

#define DIPV
#define IP4_RUL_V0_DIPV_BOFFSET            0
#define IP4_RUL_V0_DIPV_BLEN               32
#define IP4_RUL_V0_DIPV_FLAG               HSL_RW


#define IP4_RUL_V1                         1
#define IP4_RUL_V1_OFFSET                  0x58004
#define IP4_RUL_V1_E_LENGTH                4
#define IP4_RUL_V1_E_OFFSET                0x20
#define IP4_RUL_V1_NR_E                    96

#define SIPV
#define IP4_RUL_V1_SIPV_BOFFSET            0
#define IP4_RUL_V1_SIPV_BLEN               32
#define IP4_RUL_V1_SIPV_FLAG               HSL_RW


#define IP4_RUL_V2                         2
#define IP4_RUL_V2_OFFSET                  0x58008
#define IP4_RUL_V2_E_LENGTH                4
#define IP4_RUL_V2_E_OFFSET                0x20
#define IP4_RUL_V2_NR_E                    96

#define IP4PROTV
#define IP4_RUL_V2_IP4PROTV_BOFFSET        0
#define IP4_RUL_V2_IP4PROTV_BLEN           8
#define IP4_RUL_V2_IP4PROTV_FLAG           HSL_RW

#define IP4DSCPV
#define IP4_RUL_V2_IP4DSCPV_BOFFSET        8
#define IP4_RUL_V2_IP4DSCPV_BLEN           8
#define IP4_RUL_V2_IP4DSCPV_FLAG           HSL_RW

#define IP4DPORTV
#define IP4_RUL_V2_IP4DPORTV_BOFFSET       16
#define IP4_RUL_V2_IP4DPORTV_BLEN          16
#define IP4_RUL_V2_IP4DPORTV_FLAG          HSL_RW


#define IP4_RUL_V3                         3
#define IP4_RUL_V3_OFFSET                  0x5800c
#define IP4_RUL_V3_E_LENGTH                4
#define IP4_RUL_V3_E_OFFSET                0x20
#define IP4_RUL_V3_NR_E                    96

#define IP4TCPFLAGV
#define IP4_RUL_V3_IP4TCPFLAGV_BOFFSET     24
#define IP4_RUL_V3_IP4TCPFLAGV_BLEN        6
#define IP4_RUL_V3_IP4TCPFLAGV_FLAG        HSL_RW

#define IP4DHCPV
#define IP4_RUL_V3_IP4DHCPV_BOFFSET        22
#define IP4_RUL_V3_IP4DHCPV_BLEN           1
#define IP4_RUL_V3_IP4DHCPV_FLAG           HSL_RW

#define IP4RIPV
#define IP4_RUL_V3_IP4RIPV_BOFFSET         21
#define IP4_RUL_V3_IP4RIPV_BLEN            1
#define IP4_RUL_V3_IP4RIPV_FLAG            HSL_RW

#define ICMP_EN
#define IP4_RUL_V3_ICMP_EN_BOFFSET         20
#define IP4_RUL_V3_ICMP_EN_BLEN            1
#define IP4_RUL_V3_ICMP_EN_FLAG            HSL_RW

#define IP4SPORTV
#define IP4_RUL_V3_IP4SPORTV_BOFFSET       0
#define IP4_RUL_V3_IP4SPORTV_BLEN          16
#define IP4_RUL_V3_IP4SPORTV_FLAG          HSL_RW

#define IP4ICMPTYPV
#define IP4_RUL_V3_IP4ICMPTYPV_BOFFSET     8
#define IP4_RUL_V3_IP4ICMPTYPV_BLEN        8
#define IP4_RUL_V3_IP4ICMPTYPV_FLAG        HSL_RW

#define IP4ICMPCODEV
#define IP4_RUL_V3_IP4ICMPCODEV_BOFFSET    0
#define IP4_RUL_V3_IP4ICMPCODEV_BLEN       8
#define IP4_RUL_V3_IP4ICMPCODEV_FLAG       HSL_RW


#define IP4_RUL_V4                         4
#define IP4_RUL_V4_OFFSET                  0x58010
#define IP4_RUL_V4_E_LENGTH                4
#define IP4_RUL_V4_E_OFFSET                0x20
#define IP4_RUL_V4_NR_E                    96


#define IP4_RUL_M0                         5
#define IP4_RUL_M0_OFFSET                  0x59000
#define IP4_RUL_M0_E_LENGTH                4
#define IP4_RUL_M0_E_OFFSET                0x20
#define IP4_RUL_M0_NR_E                    96

#define DIPM
#define IP4_RUL_M0_DIPM_BOFFSET            0
#define IP4_RUL_M0_DIPM_BLEN               32
#define IP4_RUL_M0_DIPM_FLAG               HSL_RW


#define IP4_RUL_M1                         6
#define IP4_RUL_M1_OFFSET                  0x59004
#define IP4_RUL_M1_E_LENGTH                4
#define IP4_RUL_M1_E_OFFSET                0x20
#define IP4_RUL_M1_NR_E                    96

#define SIPM
#define IP4_RUL_M1_SIPM_BOFFSET            0
#define IP4_RUL_M1_SIPM_BLEN               32
#define IP4_RUL_M1_SIPM_FLAG               HSL_RW


#define IP4_RUL_M2                         7
#define IP4_RUL_M2_OFFSET                  0x59008
#define IP4_RUL_M2_E_LENGTH                4
#define IP4_RUL_M2_E_OFFSET                0x20
#define IP4_RUL_M2_NR_E                    96

#define IP4PROTM
#define IP4_RUL_M2_IP4PROTM_BOFFSET        0
#define IP4_RUL_M2_IP4PROTM_BLEN           8
#define IP4_RUL_M2_IP4PROTM_FLAG           HSL_RW

#define IP4DSCPM
#define IP4_RUL_M2_IP4DSCPM_BOFFSET        8
#define IP4_RUL_M2_IP4DSCPM_BLEN           8
#define IP4_RUL_M2_IP4DSCPM_FLAG           HSL_RW

#define IP4DPORTM
#define IP4_RUL_M2_IP4DPORTM_BOFFSET       16
#define IP4_RUL_M2_IP4DPORTM_BLEN          16
#define IP4_RUL_M2_IP4DPORTM_FLAG          HSL_RW


#define IP4_RUL_M3                         8
#define IP4_RUL_M3_OFFSET                  0x5900c
#define IP4_RUL_M3_E_LENGTH                4
#define IP4_RUL_M3_E_OFFSET                0x20
#define IP4_RUL_M3_NR_E                    96

#define IP4TCPFLAGM
#define IP4_RUL_M3_IP4TCPFLAGM_BOFFSET     24
#define IP4_RUL_M3_IP4TCPFLAGM_BLEN        6
#define IP4_RUL_M3_IP4TCPFLAGM_FLAG        HSL_RW

#define IP4DHCPM
#define IP4_RUL_M3_IP4DHCPM_BOFFSET        22
#define IP4_RUL_M3_IP4DHCPM_BLEN           1
#define IP4_RUL_M3_IP4DHCPM_FLAG           HSL_RW

#define IP4RIPM
#define IP4_RUL_M3_IP4RIPM_BOFFSET         21
#define IP4_RUL_M3_IP4RIPM_BLEN            1
#define IP4_RUL_M3_IP4RIPM_FLAG            HSL_RW

#define IP4DPORTM_EN
#define IP4_RUL_M3_IP4DPORTM_EN_BOFFSET    17
#define IP4_RUL_M3_IP4DPORTM_EN_BLEN       1
#define IP4_RUL_M3_IP4DPORTM_EN_FLAG       HSL_RW

#define IP4SPORTM_EN
#define IP4_RUL_M3_IP4SPORTM_EN_BOFFSET    16
#define IP4_RUL_M3_IP4SPORTM_EN_BLEN       1
#define IP4_RUL_M3_IP4SPORTM_EN_FLAG       HSL_RW

#define IP4SPORTM
#define IP4_RUL_M3_IP4SPORTM_BOFFSET       0
#define IP4_RUL_M3_IP4SPORTM_BLEN          16
#define IP4_RUL_M3_IP4SPORTM_FLAG          HSL_RW

#define IP4ICMPTYPM
#define IP4_RUL_M3_IP4ICMPTYPM_BOFFSET     8
#define IP4_RUL_M3_IP4ICMPTYPM_BLEN        8
#define IP4_RUL_M3_IP4ICMPTYPM_FLAG        HSL_RW

#define IP4ICMPCODEM
#define IP4_RUL_M3_IP4ICMPCODEM_BOFFSET    0
#define IP4_RUL_M3_IP4ICMPCODEM_BLEN       8
#define IP4_RUL_M3_IP4ICMPCODEM_FLAG       HSL_RW


#define IP4_RUL_M4                         9
#define IP4_RUL_M4_OFFSET                  0x59010
#define IP4_RUL_M4_E_LENGTH                4
#define IP4_RUL_M4_E_OFFSET                0x20
#define IP4_RUL_M4_NR_E                    32




    /* IP6 Type1 Rule Field Define */
#define IP6_RUL1_V0                        0
#define IP6_RUL1_V0_OFFSET                 0x58000
#define IP6_RUL1_V0_E_LENGTH               4
#define IP6_RUL1_V0_E_OFFSET               0x20
#define IP6_RUL1_V0_NR_E                   96

#define IP6_DIPV0
#define IP6_RUL1_V0_IP6_DIPV0_BOFFSET      0
#define IP6_RUL1_V0_IP6_DIPV0_BLEN         32
#define IP6_RUL1_V0_IP6_DIPV0_FLAG         HSL_RW


#define IP6_RUL1_V1                        1
#define IP6_RUL1_V1_OFFSET                 0x58004
#define IP6_RUL1_V1_E_LENGTH               4
#define IP6_RUL1_V1_E_OFFSET               0x20
#define IP6_RUL1_V1_NR_E                   96

#define IP6_DIPV1
#define IP6_RUL1_V1_IP6_DIPV1_BOFFSET      0
#define IP6_RUL1_V1_IP6_DIPv1_BLEN         32
#define IP6_RUL1_V1_IP6_DIPV1_FLAG         HSL_RW


#define IP6_RUL1_V2                        2
#define IP6_RUL1_V2_OFFSET                 0x58008
#define IP6_RUL1_V2_E_LENGTH               4
#define IP6_RUL1_V2_E_OFFSET               0x20
#define IP6_RUL1_V2_NR_E                   96

#define IP6_DIPV2
#define IP6_RUL1_V2_IP6_DIPV2_BOFFSET      0
#define IP6_RUL1_V2_IP6_DIPv2_BLEN         32
#define IP6_RUL1_V2_IP6_DIPV2_FLAG         HSL_RW


#define IP6_RUL1_V3                        3
#define IP6_RUL1_V3_OFFSET                 0x5800c
#define IP6_RUL1_V3_E_LENGTH               4
#define IP6_RUL1_V3_E_OFFSET               0x20
#define IP6_RUL1_V3_NR_E                   96

#define IP6_DIPV3
#define IP6_RUL1_V3_IP6_DIPV3_BOFFSET      0
#define IP6_RUL1_V3_IP6_DIPv3_BLEN         32
#define IP6_RUL1_V3_IP6_DIPV3_FLAG         HSL_RW


#define IP6_RUL1_V4                        4
#define IP6_RUL1_V4_OFFSET                 0x58010
#define IP6_RUL1_V4_E_LENGTH               4
#define IP6_RUL1_V4_E_OFFSET               0x20
#define IP6_RUL1_V4_NR_E                   96


#define IP6_RUL1_M0                        5
#define IP6_RUL1_M0_OFFSET                 0x59000
#define IP6_RUL1_M0_E_LENGTH               4
#define IP6_RUL1_M0_E_OFFSET               0x20
#define IP6_RUL1_M0_NR_E                   96

#define IP6_DIPM0
#define IP6_RUL1_M0_IP6_DIPM0_BOFFSET      0
#define IP6_RUL1_M0_IP6_DIPM0_BLEN         32
#define IP6_RUL1_M0_IP6_DIPM0_FLAG         HSL_RW


#define IP6_RUL1_M1                        6
#define IP6_RUL1_M1_OFFSET                 0x59004
#define IP6_RUL1_M1_E_LENGTH               4
#define IP6_RUL1_M1_E_OFFSET               0x20
#define IP6_RUL1_M1_NR_E                   96

#define IP6_DIPM1
#define IP6_RUL1_M1_IP6_DIPM1_BOFFSET      0
#define IP6_RUL1_M1_IP6_DIPM1_BLEN         32
#define IP6_RUL1_M1_IP6_DIPM1_FLAG         HSL_RW


#define IP6_RUL1_M2                        7
#define IP6_RUL1_M2_OFFSET                 0x59008
#define IP6_RUL1_M2_E_LENGTH               4
#define IP6_RUL1_M2_E_OFFSET               0x20
#define IP6_RUL1_M2_NR_E                   96

#define IP6_DIPM2
#define IP6_RUL1_M2_IP6_DIPM2_BOFFSET      0
#define IP6_RUL1_M2_IP6_DIPM2_BLEN         32
#define IP6_RUL1_M2_IP6_DIPM2_FLAG         HSL_RW


#define IP6_RUL1_M3                        8
#define IP6_RUL1_M3_OFFSET                 0x5900c
#define IP6_RUL1_M3_E_LENGTH               4
#define IP6_RUL1_M3_E_OFFSET               0x20
#define IP6_RUL1_M3_NR_E                   96

#define IP6_DIPM3
#define IP6_RUL1_M3_IP6_DIPM3_BOFFSET      0
#define IP6_RUL1_M3_IP6_DIPM3_BLEN         32
#define IP6_RUL1_M3_IP6_DIPM3_FLAG         HSL_RW


#define IP6_RUL1_M4                        9
#define IP6_RUL1_M4_OFFSET                 0x59010
#define IP6_RUL1_M4_E_LENGTH               4
#define IP6_RUL1_M4_E_OFFSET               0x20
#define IP6_RUL1_M4_NR_E                   96




    /* IP6 Type2 Rule Field Define */
#define IP6_RUL2_V0                        0
#define IP6_RUL2_V0_OFFSET                 0x58000
#define IP6_RUL2_V0_E_LENGTH               4
#define IP6_RUL2_V0_E_OFFSET               0x20
#define IP6_RUL2_V0_NR_E                   96

#define IP6_SIPV0
#define IP6_RUL2_V0_IP6_SIPV0_BOFFSET      0
#define IP6_RUL2_V0_IP6_SIPv0_BLEN         32
#define IP6_RUL2_V0_IP6_SIPV0_FLAG         HSL_RW


#define IP6_RUL2_V1                        1
#define IP6_RUL2_V1_OFFSET                 0x58004
#define IP6_RUL2_V1_E_LENGTH               4
#define IP6_RUL2_V1_E_OFFSET               0x20
#define IP6_RUL2_V1_NR_E                   96

#define IP6_SIPV1
#define IP6_RUL2_V1_IP6_SIPV1_BOFFSET      0
#define IP6_RUL2_V1_IP6_SIPv1_BLEN         32
#define IP6_RUL2_V1_IP6_SIPV1_FLAG         HSL_RW


#define IP6_RUL2_V2                        2
#define IP6_RUL2_V2_OFFSET                 0x58008
#define IP6_RUL2_V2_E_LENGTH               4
#define IP6_RUL2_V2_E_OFFSET               0x20
#define IP6_RUL2_V2_NR_E                   96

#define IP6_SIPV2
#define IP6_RUL2_V2_IP6_SIPV2_BOFFSET      0
#define IP6_RUL2_V2_IP6_SIPv2_BLEN         32
#define IP6_RUL2_V2_IP6_SIPV2_FLAG         HSL_RW


#define IP6_RUL2_V3                        3
#define IP6_RUL2_V3_OFFSET                 0x5800c
#define IP6_RUL2_V3_E_LENGTH               4
#define IP6_RUL2_V3_E_OFFSET               0x20
#define IP6_RUL2_V3_NR_E                   96

#define IP6_SIPV3
#define IP6_RUL2_V3_IP6_SIPV3_BOFFSET      0
#define IP6_RUL2_V3_IP6_SIPv3_BLEN         32
#define IP6_RUL2_V3_IP6_SIPV3_FLAG         HSL_RW


#define IP6_RUL2_V4                        4
#define IP6_RUL2_V4_OFFSET                 0x58010
#define IP6_RUL2_V4_E_LENGTH               4
#define IP6_RUL2_V4_E_OFFSET               0x20
#define IP6_RUL2_V4_NR_E                   96


#define IP6_RUL2_M0                        5
#define IP6_RUL2_M0_OFFSET                 0x59000
#define IP6_RUL2_M0_E_LENGTH               4
#define IP6_RUL2_M0_E_OFFSET               0x20
#define IP6_RUL2_M0_NR_E                   96

#define IP6_SIPM0
#define IP6_RUL2_M0_IP6_SIPM0_BOFFSET      0
#define IP6_RUL2_M0_IP6_SIPM0_BLEN         32
#define IP6_RUL2_M0_IP6_SIPM0_FLAG         HSL_RW


#define IP6_RUL2_M1                        6
#define IP6_RUL2_M1_OFFSET                 0x59004
#define IP6_RUL2_M1_E_LENGTH               4
#define IP6_RUL2_M1_E_OFFSET               0x20
#define IP6_RUL2_M1_NR_E                   96

#define IP6_SIPM1
#define IP6_RUL2_M1_IP6_DIPM1_BOFFSET      0
#define IP6_RUL2_M1_IP6_DIPM1_BLEN         32
#define IP6_RUL2_M1_IP6_DIPM1_FLAG         HSL_RW


#define IP6_RUL2_M2                        7
#define IP6_RUL2_M2_OFFSET                 0x59008
#define IP6_RUL2_M2_E_LENGTH               4
#define IP6_RUL2_M2_E_OFFSET               0x20
#define IP6_RUL2_M2_NR_E                   96

#define IP6_SIPM2
#define IP6_RUL2_M2_IP6_DIPM2_BOFFSET      0
#define IP6_RUL2_M2_IP6_DIPM2_BLEN         32
#define IP6_RUL2_M2_IP6_DIPM2_FLAG         HSL_RW


#define IP6_RUL2_M3                        8
#define IP6_RUL2_M3_OFFSET                 0x5900c
#define IP6_RUL2_M3_E_LENGTH               4
#define IP6_RUL2_M3_E_OFFSET               0x20
#define IP6_RUL2_M3_NR_E                   96

#define IP6_SIPM3
#define IP6_RUL2_M3_IP6_SIPM3_BOFFSET      0
#define IP6_RUL2_M3_IP6_SIPM3_BLEN         32
#define IP6_RUL2_M3_IP6_SIPM3_FLAG         HSL_RW


#define IP6_RUL2_M4                        9
#define IP6_RUL2_M4_OFFSET                 0x59010
#define IP6_RUL2_M4_E_LENGTH               4
#define IP6_RUL2_M4_E_OFFSET               0x20
#define IP6_RUL2_M4_NR_E                   96




    /* IP6 Type3 Rule Field Define */
#define IP6_RUL3_V0                        0
#define IP6_RUL3_V0_OFFSET                 0x58000
#define IP6_RUL3_V0_E_LENGTH               4
#define IP6_RUL3_V0_E_OFFSET               0x20
#define IP6_RUL3_V0_NR_E                   96

#define IP6PROTV
#define IP6_RUL3_V0_IP6PROTV_BOFFSET       0
#define IP6_RUL3_V0_IP6PROTV_BLEN          8
#define IP6_RUL3_V0_IP6PROTV_FLAG          HSL_RW

#define IP6DSCPV
#define IP6_RUL3_V0_IP6DSCPV_BOFFSET       8
#define IP6_RUL3_V0_IP6DSCPV_BLEN          8
#define IP6_RUL3_V0_IP6DSCPV_FLAG          HSL_RW


#define IP6_RUL3_V1                        1
#define IP6_RUL3_V1_OFFSET                 0x58004
#define IP6_RUL3_V1_E_LENGTH               4
#define IP6_RUL3_V1_E_OFFSET               0x20
#define IP6_RUL3_V1_NR_E                   96

#define IP6LABEL1V
#define IP6_RUL3_V1_IP6LABEL1V_BOFFSET     16
#define IP6_RUL3_V1_IP6LABEL1V_BLEN        16
#define IP6_RUL3_V1_IP6LABEL1V_FLAG        HSL_RW


#define IP6_RUL3_V2                        2
#define IP6_RUL3_V2_OFFSET                 0x58008
#define IP6_RUL3_V2_E_LENGTH               4
#define IP6_RUL3_V2_E_OFFSET               0x20
#define IP6_RUL3_V2_NR_E                   96

#define IP6LABEL2V
#define IP6_RUL3_V2_IP6LABEL2V_BOFFSET     0
#define IP6_RUL3_V2_IP6LABEL2V_BLEN        4
#define IP6_RUL3_V2_IP6LABEL2V_FLAG        HSL_RW

#define IP6DPORTV
#define IP6_RUL3_V2_IP6DPORTV_BOFFSET      16
#define IP6_RUL3_V2_IP6DPORTV_BLEN         16
#define IP6_RUL3_V2_IP6DPORTV_FLAG         HSL_RW


#define IP6_RUL3_V3                        3
#define IP6_RUL3_V3_OFFSET                 0x5800c
#define IP6_RUL3_V3_E_LENGTH               4
#define IP6_RUL3_V3_E_OFFSET               0x20
#define IP6_RUL3_V3_NR_E                   96

#define IP6TCPFLAGV
#define IP6_RUL3_V3_IP6TCPFLAGV_BOFFSET    24
#define IP6_RUL3_V3_IP6TCPFLAGV_BLEN       6
#define IP6_RUL3_V3_IP6TCPFLAGV_FLAG       HSL_RW

#define IP6FWDTYPV
#define IP6_RUL3_V3_IP6FWDTYPV_BOFFSET     23
#define IP6_RUL3_V3_IP6FWDTYPV_BLEN        1
#define IP6_RUL3_V3_IP6FWDTYPV_FLAG        HSL_RW

#define IP6DHCPV
#define IP6_RUL3_V3_IP6DHCPV_BOFFSET       22
#define IP6_RUL3_V3_IP6DHCPV_BLEN          1
#define IP6_RUL3_V3_IP6DHCPV_FLAG          HSL_RW

#define ICMP6_EN
#define IP6_RUL3_V3_ICMP6_EN_BOFFSET       20
#define IP6_RUL3_V3_ICMP6_EN_BLEN          1
#define IP6_RUL3_V3_ICMP6_EN_FLAG          HSL_RW

#define IP6SPORTV
#define IP6_RUL3_V3_IP6SPORTV_BOFFSET      0
#define IP6_RUL3_V3_IP6SPORTV_BLEN         16
#define IP6_RUL3_V3_IP6SPORTV_FLAG         HSL_RW

#define IP6ICMPTYPV
#define IP6_RUL3_V3_IP6ICMPTYPV_BOFFSET    8
#define IP6_RUL3_V3_IP6ICMPTYPV_BLEN       8
#define IP6_RUL3_V3_IP6ICMPTYPV_FLAG       HSL_RW

#define IP6ICMPCODEV
#define IP6_RUL3_V3_IP6ICMPCODEV_BOFFSET   0
#define IP6_RUL3_V3_IP6ICMPCODEV_BLEN      8
#define IP6_RUL3_V3_IP6ICMPCODEV_FLAG      HSL_RW


#define IP6_RUL3_V4                        4
#define IP6_RUL3_V4_OFFSET                 0x58010
#define IP6_RUL3_V4_E_LENGTH               4
#define IP6_RUL3_V4_E_OFFSET               0x20
#define IP6_RUL3_V4_NR_E                   96


#define IP6_RUL3_M0                        5
#define IP6_RUL3_M0_OFFSET                 0x59000
#define IP6_RUL3_M0_E_LENGTH               4
#define IP6_RUL3_M0_E_OFFSET               0x20
#define IP6_RUL3_M0_NR_E                   96

#define IP6PROTM
#define IP6_RUL3_M0_IP6PROTM_BOFFSET       0
#define IP6_RUL3_M0_IP6PROTM_BLEN          8
#define IP6_RUL3_M0_IP6PROTM_FLAG          HSL_RW

#define IP6DSCPM
#define IP6_RUL3_M0_IP6DSCPM_BOFFSET       8
#define IP6_RUL3_M0_IP6DSCPM_BLEN          8
#define IP6_RUL3_M0_IP6DSCPM_FLAG          HSL_RW


#define IP6_RUL3_M1                        6
#define IP6_RUL3_M1_OFFSET                 0x59004
#define IP6_RUL3_M1_E_LENGTH               4
#define IP6_RUL3_M1_E_OFFSET               0x20
#define IP6_RUL3_M1_NR_E                   96

#define IP6LABEL1M
#define IP6_RUL3_M1_IP6LABEL1M_BOFFSET     16
#define IP6_RUL3_M1_IP6LABEL1M_BLEN        16
#define IP6_RUL3_M1_IP6LABEL1M_FLAG        HSL_RW


#define IP6_RUL3_M2                        7
#define IP6_RUL3_M2_OFFSET                 0x59008
#define IP6_RUL3_M2_E_LENGTH               4
#define IP6_RUL3_M2_E_OFFSET               0x20
#define IP6_RUL3_M2_NR_E                   96

#define IP6LABEL2M
#define IP6_RUL3_M2_IP6LABEL2M_BOFFSET     0
#define IP6_RUL3_M2_IP6LABEL2M_BLEN        4
#define IP6_RUL3_M2_IP6LABEL21M_FLAG       HSL_RW

#define IP6DPORTM
#define IP6_RUL3_M2_IP6DPORTM_BOFFSET      16
#define IP6_RUL3_M2_IP6DPORTM_BLEN         16
#define IP6_RUL3_M2_IP6DPORTM_FLAG         HSL_RW


#define IP6_RUL3_M3                        8
#define IP6_RUL3_M3_OFFSET                 0x5900c
#define IP6_RUL3_M3_E_LENGTH               4
#define IP6_RUL3_M3_E_OFFSET               0x20
#define IP6_RUL3_M3_NR_E                   96

#define IP6TCPFLAGM
#define IP6_RUL3_M3_IP6TCPFLAGM_BOFFSET    24
#define IP6_RUL3_M3_IP6TCPFLAGM_BLEN       6
#define IP6_RUL3_M3_IP6TCPFLAGM_FLAG       HSL_RW

#define IP6RWDTYPM
#define IP6_RUL3_M3_IP6RWDTYPV_BOFFSET     23
#define IP6_RUL3_M3_IP6RWDTYPV_BLEN        1
#define IP6_RUL3_M3_IP6RWDTYPV_FLAG        HSL_RW

#define IP6DHCPM
#define IP6_RUL3_M3_IP6DHCPM_BOFFSET       22
#define IP6_RUL3_M3_IP6DHCPM_BLEN          1
#define IP6_RUL3_M3_IP6DHCPM_FLAG          HSL_RW

#define IP6DPORTM_EN
#define IP6_RUL3_M3_IP6DPORTM_EN_BOFFSET   17
#define IP6_RUL3_M3_IP6DPORTM_EN_BLEN      1
#define IP6_RUL3_M3_IP6DPORTM_EN_FLAG      HSL_RW

#define IP6SPORTM_EN
#define IP6_RUL3_M3_IP6SPORTM_EN_BOFFSET   16
#define IP6_RUL3_M3_IP6SPORTM_EN_BLEN      1
#define IP6_RUL3_M3_IP6SPORTM_EN_FLAG      HSL_RW

#define IP6SPORTM
#define IP6_RUL3_M3_IP6SPORTM_BOFFSET      0
#define IP6_RUL3_M3_IP6SPORTM_BLEN         16
#define IP6_RUL3_M3_IP6SPORTM_FLAG         HSL_RW

#define IP6ICMPTYPM
#define IP6_RUL3_M3_IP6ICMPTYPM_BOFFSET     8
#define IP6_RUL3_M3_IP6ICMPTYPM_BLEN        8
#define IP6_RUL3_M3_IP6ICMPTYPM_FLAG        HSL_RW

#define IP6ICMPCODEM
#define IP6_RUL3_M3_IP6ICMPCODEM_BOFFSET    0
#define IP6_RUL3_M3_IP6ICMPCODEM_BLEN       8
#define IP6_RUL3_M3_IP6ICMPCODEM_FLAG       HSL_RW


#define IP6_RUL3_M4                        9
#define IP6_RUL3_M4_OFFSET                 0x59010
#define IP6_RUL3_M4_E_LENGTH               4
#define IP6_RUL3_M4_E_OFFSET               0x20
#define IP6_RUL3_M4_NR_E                   96




    /* Enhanced MAC Type Rule Field Define */
#define EHMAC_RUL_V0                         0
#define EHMAC_RUL_V0_OFFSET                  0x58000
#define EHMAC_RUL_V0_E_LENGTH                4
#define EHMAC_RUL_V0_E_OFFSET                0x20
#define EHMAC_RUL_V0_NR_E                    96

#define DAV_BYTE2
#define EHMAC_RUL_V0_DAV_BYTE2_BOFFSET       24
#define EHMAC_RUL_V0_DAV_BYTE2_BLEN          8
#define EHMAC_RUL_V0_DAV_BYTE2_FLAG          HSL_RW

#define DAV_BYTE3
#define EHMAC_RUL_V0_DAV_BYTE3_BOFFSET       16
#define EHMAC_RUL_V0_DAV_BYTE3_BLEN          8
#define EHMAC_RUL_V0_DAV_BYTE3_FLAG          HSL_RW

#define DAV_BYTE4
#define EHMAC_RUL_V0_DAV_BYTE4_BOFFSET       8
#define EHMAC_RUL_V0_DAV_BYTE4_BLEN          8
#define EHMAC_RUL_V0_DAV_BYTE4_FLAG          HSL_RW

#define DAV_BYTE5
#define EHMAC_RUL_V0_DAV_BYTE5_BOFFSET       0
#define EHMAC_RUL_V0_DAV_BYTE5_BLEN          8
#define EHMAC_RUL_V0_DAV_BYTE5_FLAG          HSL_RW


#define EHMAC_RUL_V1                         1
#define EHMAC_RUL_V1_OFFSET                  0x58004
#define EHMAC_RUL_V1_E_LENGTH                4
#define EHMAC_RUL_V1_E_OFFSET                0x20
#define EHMAC_RUL_V1_NR_E                    96

#define SAV_BYTE4
#define EHMAC_RUL_V1_SAV_BYTE4_BOFFSET       24
#define EHMAC_RUL_V1_SAV_BYTE4_BLEN          8
#define EHMAC_RUL_V1_SAV_BYTE4_FLAG          HSL_RW

#define SAV_BYTE5
#define EHMAC_RUL_V1_SAV_BYTE5_BOFFSET       16
#define EHMAC_RUL_V1_SAV_BYTE5_BLEN          8
#define EHMAC_RUL_V1_SAV_BYTE5_FLAG          HSL_RW

#define DAV_BYTE0
#define EHMAC_RUL_V1_DAV_BYTE0_BOFFSET       8
#define EHMAC_RUL_V1_DAV_BYTE0_BLEN          8
#define EHMAC_RUL_V1_DAV_BYTE0_FLAG          HSL_RW

#define DAV_BYTE1
#define EHMAC_RUL_V1_DAV_BYTE1_BOFFSET       0
#define EHMAC_RUL_V1_DAV_BYTE1_BLEN          8
#define EHMAC_RUL_V1_DAV_BYTE1_FLAG          HSL_RW


#define EHMAC_RUL_V2                         2
#define EHMAC_RUL_V2_OFFSET                  0x58008
#define EHMAC_RUL_V2_E_LENGTH                4
#define EHMAC_RUL_V2_E_OFFSET                0x20
#define EHMAC_RUL_V2_NR_E                    96

#define CTAG_VIDLV
#define EHMAC_RUL_V2_CTAG_VIDLV_BOFFSET      24
#define EHMAC_RUL_V2_CTAG_VIDLV_BLEN         8
#define EHMAC_RUL_V2_CTAG_VIDLV_FLAG         HSL_RW

#define STAG_PRIV
#define EHMAC_RUL_V2_STAG_PRIV_BOFFSET       21
#define EHMAC_RUL_V2_STAG_PRIV_BLEN          3
#define EHMAC_RUL_V2_STAG_PRIV_FLAG          HSL_RW

#define STAG_DEIV
#define EHMAC_RUL_V2_STAG_DEIV_BOFFSET       20
#define EHMAC_RUL_V2_STAG_DEIV_BLEN          1
#define EHMAC_RUL_V2_STAG_DEIV_FLAG          HSL_RW

#define STAG_VIDV
#define EHMAC_RUL_V2_STAG_VIDV_BOFFSET       8
#define EHMAC_RUL_V2_STAG_VIDV_BLEN          12
#define EHMAC_RUL_V2_STAG_VIDV_FLAG          HSL_RW

#define SAV_BYTE3
#define EHMAC_RUL_V2_SAV_BYTE3_BOFFSET       0
#define EHMAC_RUL_V2_SAV_BYTE3_BLEN          8
#define EHMAC_RUL_V2_SAV_BYTE3_FLAG          HSL_RW


#define EHMAC_RUL_V3                         3
#define EHMAC_RUL_V3_ID                      13
#define EHMAC_RUL_V3_OFFSET                  0x5800c
#define EHMAC_RUL_V3_E_LENGTH                4
#define EHMAC_RUL_V3_E_OFFSET                0x20
#define EHMAC_RUL_V3_NR_E                    96

#define STAGGEDM
#define EHMAC_RUL_V3_STAGGEDM_BOFFSET         31
#define EHMAC_RUL_V3_STAGGEDM_BLEN            1
#define EHMAC_RUL_V3_STAGGEDM_FLAG            HSL_RW

#define STAGGEDV
#define EHMAC_RUL_V3_STAGGEDV_BOFFSET         30
#define EHMAC_RUL_V3_STAGGEDV_BLEN            1
#define EHMAC_RUL_V3_STAGGEDV_FLAG            HSL_RW

#define DA_EN
#define EHMAC_RUL_V3_DA_EN_BOFFSET          25
#define EHMAC_RUL_V3_DA_EN_BLEN             1
#define EHMAC_RUL_V3_DA_EN_FLAG             HSL_RW

#define SVIDMSK
#define EHMAC_RUL_V3_SVIDMSK_BOFFSET          24
#define EHMAC_RUL_V3_SVIDMSK_BLEN             1
#define EHMAC_RUL_V3_SVIDMSK_FLAG             HSL_RW

#define ETHTYPV
#define EHMAC_RUL_V3_ETHTYPV_BOFFSET         8
#define EHMAC_RUL_V3_ETHTYPV_BLEN            16
#define EHMAC_RUL_V3_ETHTYPV_FLAG            HSL_RW

#define CTAG_PRIV
#define EHMAC_RUL_V3_CTAG_PRIV_BOFFSET       5
#define EHMAC_RUL_V3_CTAG_PRIV_BLEN          3
#define EHMAC_RUL_V3_CTAG_PRIV_FLAG          HSL_RW

#define CTAG_CFIV
#define EHMAC_RUL_V3_CTAG_CFIV_BOFFSET       4
#define EHMAC_RUL_V3_CTAG_CFIV_BLEN          1
#define EHMAC_RUL_V3_CTAG_CFIV_FLAG          HSL_RW

#define CTAG_VIDHV
#define EHMAC_RUL_V3_CTAG_VIDHV_BOFFSET      0
#define EHMAC_RUL_V3_CTAG_VIDHV_BLEN         4
#define EHMAC_RUL_V3_CTAG_VIDHV_FLAG         HSL_RW


#define EHMAC_RUL_V4                         4
#define EHMAC_RUL_V4_OFFSET                  0x58010
#define EHMAC_RUL_V4_E_LENGTH                4
#define EHMAC_RUL_V4_E_OFFSET                0x20
#define EHMAC_RUL_V4_NR_E                    96


#define EHMAC_RUL_M0                         5
#define EHMAC_RUL_M0_OFFSET                  0x59000
#define EHMAC_RUL_M0_E_LENGTH                4
#define EHMAC_RUL_M0_E_OFFSET                0x20
#define EHMAC_RUL_M0_NR_E                    96

#define DAM_BYTE2
#define EHMAC_RUL_M0_DAM_BYTE2_BOFFSET       24
#define EHMAC_RUL_M0_DAM_BYTE2_BLEN          8
#define EHMAC_RUL_M0_DAM_BYTE2_FLAG          HSL_RW

#define DAM_BYTE3
#define EHMAC_RUL_M0_DAM_BYTE3_BOFFSET       16
#define EHMAC_RUL_M0_DAM_BYTE3_BLEN          8
#define EHMAC_RUL_M0_DAM_BYTE3_FLAG          HSL_RW

#define DAM_BYTE4
#define EHMAC_RUL_M0_DAM_BYTE4_BOFFSET       8
#define EHMAC_RUL_M0_DAM_BYTE4_BLEN          8
#define EHMAC_RUL_M0_DAM_BYTE4_FLAG          HSL_RW

#define DAM_BYTE5
#define EHMAC_RUL_M0_DAM_BYTE5_BOFFSET       0
#define EHMAC_RUL_M0_DAM_BYTE5_BLEN          8
#define EHMAC_RUL_M0_DAM_BYTE5_FLAG          HSL_RW


#define EHMAC_RUL_M1                         6
#define EHMAC_RUL_M1_OFFSET                  0x59004
#define EHMAC_RUL_M1_E_LENGTH                4
#define EHMAC_RUL_M1_E_OFFSET                0x20
#define EHMAC_RUL_M1_NR_E                    96

#define SAM_BYTE4
#define EHMAC_RUL_M1_SAM_BYTE4_BOFFSET       24
#define EHMAC_RUL_M1_SAM_BYTE4_BLEN          8
#define EHMAC_RUL_M1_SAM_BYTE4_FLAG          HSL_RW

#define SAM_BYTE5
#define EHMAC_RUL_M1_SAM_BYTE5_BOFFSET       16
#define EHMAC_RUL_M1_SAM_BYTE5_BLEN          8
#define EHMAC_RUL_M1_SAM_BYTE5_FLAG          HSL_RW

#define DAM_BYTE0
#define EHMAC_RUL_M1_DAM_BYTE0_BOFFSET       8
#define EHMAC_RUL_M1_DAM_BYTE0_BLEN          8
#define EHMAC_RUL_M1_DAM_BYTE0_FLAG          HSL_RW

#define DAM_BYTE1
#define EHMAC_RUL_M1_DAM_BYTE1_BOFFSET       0
#define EHMAC_RUL_M1_DAM_BYTE1_BLEN          8
#define EHMAC_RUL_M1_DAM_BYTE1_FLAG          HSL_RW


#define EHMAC_RUL_M2                         7
#define EHMAC_RUL_M2_OFFSET                  0x59008
#define EHMAC_RUL_M2_E_LENGTH                4
#define EHMAC_RUL_M2_E_OFFSET                0x20
#define EHMAC_RUL_M2_NR_E                    96

#define CTAG_VIDLM
#define EHMAC_RUL_M2_CTAG_VIDLM_BOFFSET      24
#define EHMAC_RUL_M2_CTAG_VIDLM_BLEN         8
#define EHMAC_RUL_M2_CTAG_VIDLM_FLAG         HSL_RW

#define STAG_PRIM
#define EHMAC_RUL_M2_STAG_PRIM_BOFFSET       21
#define EHMAC_RUL_M2_STAG_PRIM_BLEN          3
#define EHMAC_RUL_M2_STAG_PRIM_FLAG          HSL_RW

#define STAG_DEIM
#define EHMAC_RUL_M2_STAG_DEIM_BOFFSET       20
#define EHMAC_RUL_M2_STAG_DEIM_BLEN          1
#define EHMAC_RUL_M2_STAG_DEIM_FLAG          HSL_RW

#define STAG_VIDM
#define EHMAC_RUL_M2_STAG_VIDM_BOFFSET       8
#define EHMAC_RUL_M2_STAG_VIDM_BLEN          12
#define EHMAC_RUL_M2_STAG_VIDM_FLAG          HSL_RW

#define SAM_BYTE3
#define EHMAC_RUL_M2_SAM_BYTE3_BOFFSET       0
#define EHMAC_RUL_M2_SAM_BYTE3_BLEN          8
#define EHMAC_RUL_M2_SAM_BYTE3_FLAG          HSL_RW


#define EHMAC_RUL_M3                         8
#define EHMAC_RUL_M3_OFFSET                  0x5900c
#define EHMAC_RUL_M3_E_LENGTH                4
#define EHMAC_RUL_M3_E_OFFSET                0x20
#define EHMAC_RUL_M3_NR_E                    96

#define ETHTYPM
#define EHMAC_RUL_M3_ETHTYPM_BOFFSET         8
#define EHMAC_RUL_M3_ETHTYPM_BLEN            16
#define EHMAC_RUL_M3_ETHTYPM_FLAG            HSL_RW

#define CTAG_PRIM
#define EHMAC_RUL_M3_CTAG_PRIM_BOFFSET       5
#define EHMAC_RUL_M3_CTAG_PRIM_BLEN          3
#define EHMAC_RUL_M3_CTAG_PRIM_FLAG          HSL_RW

#define CTAG_CFIM
#define EHMAC_RUL_M3_CTAG_CFIM_BOFFSET       4
#define EHMAC_RUL_M3_CTAG_CFIM_BLEN          1
#define EHMAC_RUL_M3_CTAG_CFIM_FLAG          HSL_RW

#define CTAG_VIDHM
#define EHMAC_RUL_M3_CTAG_VIDHM_BOFFSET      0
#define EHMAC_RUL_M3_CTAG_VIDHM_BLEN         4
#define EHMAC_RUL_M3_CTAG_VIDHM_FLAG         HSL_RW


#define EHMAC_RUL_M4                         9
#define EHMAC_RUL_M4_OFFSET                  0x59010
#define EHMAC_RUL_M4_E_LENGTH                4
#define EHMAC_RUL_M4_E_OFFSET                0x20
#define EHMAC_RUL_M4_NR_E                    96

#define CTAGGEDM
#define EHMAC_RUL_M4_CTAGGEDM_BOFFSET        5
#define EHMAC_RUL_M4_CTAGGEDM_BLEN           1
#define EHMAC_RUL_M4_CTAGGEDM_FLAG           HSL_RW

#define CTAGGEDV
#define EHMAC_RUL_M4_CTAGGEDV_BOFFSET        4
#define EHMAC_RUL_M4_CTAGGEDV_BLEN           1
#define EHMAC_RUL_M4_CTAGGEDV_FLAG           HSL_RW

#define CVIDMSK
#define EHMAC_RUL_M4_CVIDMSK_BOFFSET         3
#define EHMAC_RUL_M4_CVIDMSK_BLEN            1
#define EHMAC_RUL_M4_CVIDMSK_FLAG            HSL_RW







#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* _DESS_REG_H_ */

