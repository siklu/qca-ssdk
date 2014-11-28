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
#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* _DESS_REG_H_ */

