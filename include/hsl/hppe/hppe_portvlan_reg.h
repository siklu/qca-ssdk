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
#ifndef HPPE_PORTVLAN_REG_H
#define HPPE_PORTVLAN_REG_H

/*[register] PORT_PARSING_REG*/
#define PORT_PARSING_REG
#define PORT_PARSING_REG_ADDRESS 0x0
#define PORT_PARSING_REG_NUM     8
#define PORT_PARSING_REG_INC     0x4
#define PORT_PARSING_REG_TYPE    REG_TYPE_RW
#define PORT_PARSING_REG_DEFAULT 0x0
	/*[field] PORT_ROLE*/
	#define PORT_PARSING_REG_PORT_ROLE
	#define PORT_PARSING_REG_PORT_ROLE_OFFSET  0
	#define PORT_PARSING_REG_PORT_ROLE_LEN     1
	#define PORT_PARSING_REG_PORT_ROLE_DEFAULT 0x0

struct port_parsing_reg {
	a_uint32_t  port_role:1;
	a_uint32_t  _reserved0:31;
};

union port_parsing_reg_u {
	a_uint32_t val;
	struct port_parsing_reg bf;
};

/*[register] VLAN_TPID_REG*/
#define VLAN_TPID_REG
#define VLAN_TPID_REG_ADDRESS 0x20
#define VLAN_TPID_REG_NUM     1
#define VLAN_TPID_REG_INC     0x4
#define VLAN_TPID_REG_TYPE    REG_TYPE_RW
#define VLAN_TPID_REG_DEFAULT 0x88a88100
	/*[field] CTAG_TPID*/
	#define VLAN_TPID_REG_CTAG_TPID
	#define VLAN_TPID_REG_CTAG_TPID_OFFSET  0
	#define VLAN_TPID_REG_CTAG_TPID_LEN     16
	#define VLAN_TPID_REG_CTAG_TPID_DEFAULT 0x8100
	/*[field] STAG_TPID*/
	#define VLAN_TPID_REG_STAG_TPID
	#define VLAN_TPID_REG_STAG_TPID_OFFSET  16
	#define VLAN_TPID_REG_STAG_TPID_LEN     16
	#define VLAN_TPID_REG_STAG_TPID_DEFAULT 0x88a8

struct vlan_tpid_reg {
	a_uint32_t  ctag_tpid:16;
	a_uint32_t  stag_tpid:16;
};

union vlan_tpid_reg_u {
	a_uint32_t val;
	struct vlan_tpid_reg bf;
};

/*[register] BRIDGE_CONFIG*/
#define BRIDGE_CONFIG
#define BRIDGE_CONFIG_ADDRESS 0x0
#define BRIDGE_CONFIG_NUM     1
#define BRIDGE_CONFIG_INC     0x4
#define BRIDGE_CONFIG_TYPE    REG_TYPE_RW
#define BRIDGE_CONFIG_DEFAULT 0x0
	/*[field] BRIDGE_TYPE*/
	#define BRIDGE_CONFIG_BRIDGE_TYPE
	#define BRIDGE_CONFIG_BRIDGE_TYPE_OFFSET  0
	#define BRIDGE_CONFIG_BRIDGE_TYPE_LEN     1
	#define BRIDGE_CONFIG_BRIDGE_TYPE_DEFAULT 0x0

struct bridge_config {
	a_uint32_t  bridge_type:1;
	a_uint32_t  _reserved0:31;
};

union bridge_config_u {
	a_uint32_t val;
	struct bridge_config bf;
};

/*[register] PORT_DEF_VID_0*/
#define PORT_DEF_VID_0
#define PORT_DEF_VID_0_ADDRESS 0x10
#define PORT_DEF_VID_0_NUM     1
#define PORT_DEF_VID_0_INC     0x4
#define PORT_DEF_VID_0_TYPE    REG_TYPE_RW
#define PORT_DEF_VID_0_DEFAULT 0x0
	/*[field] PORT_DEF_SVID_0*/
	#define PORT_DEF_VID_0_PORT_DEF_SVID_0
	#define PORT_DEF_VID_0_PORT_DEF_SVID_0_OFFSET  0
	#define PORT_DEF_VID_0_PORT_DEF_SVID_0_LEN     12
	#define PORT_DEF_VID_0_PORT_DEF_SVID_0_DEFAULT 0x0
	/*[field] PORT_DEF_SVID_EN_0*/
	#define PORT_DEF_VID_0_PORT_DEF_SVID_EN_0
	#define PORT_DEF_VID_0_PORT_DEF_SVID_EN_0_OFFSET  12
	#define PORT_DEF_VID_0_PORT_DEF_SVID_EN_0_LEN     1
	#define PORT_DEF_VID_0_PORT_DEF_SVID_EN_0_DEFAULT 0x0
	/*[field] PORT_DEF_CVID_0*/
	#define PORT_DEF_VID_0_PORT_DEF_CVID_0
	#define PORT_DEF_VID_0_PORT_DEF_CVID_0_OFFSET  16
	#define PORT_DEF_VID_0_PORT_DEF_CVID_0_LEN     12
	#define PORT_DEF_VID_0_PORT_DEF_CVID_0_DEFAULT 0x0
	/*[field] PORT_DEF_CVID_EN_0*/
	#define PORT_DEF_VID_0_PORT_DEF_CVID_EN_0
	#define PORT_DEF_VID_0_PORT_DEF_CVID_EN_0_OFFSET  28
	#define PORT_DEF_VID_0_PORT_DEF_CVID_EN_0_LEN     1
	#define PORT_DEF_VID_0_PORT_DEF_CVID_EN_0_DEFAULT 0x0

struct port_def_vid_0 {
	a_uint32_t  port_def_svid_0:12;
	a_uint32_t  port_def_svid_en_0:1;
	a_uint32_t  _reserved0:3;
	a_uint32_t  port_def_cvid_0:12;
	a_uint32_t  port_def_cvid_en_0:1;
	a_uint32_t  _reserved1:3;
};

union port_def_vid_0_u {
	a_uint32_t val;
	struct port_def_vid_0 bf;
};

/*[register] PORT_DEF_VID_1*/
#define PORT_DEF_VID_1
#define PORT_DEF_VID_1_ADDRESS 0x14
#define PORT_DEF_VID_1_NUM     1
#define PORT_DEF_VID_1_INC     0x4
#define PORT_DEF_VID_1_TYPE    REG_TYPE_RW
#define PORT_DEF_VID_1_DEFAULT 0x0
	/*[field] PORT_DEF_SVID_1*/
	#define PORT_DEF_VID_1_PORT_DEF_SVID_1
	#define PORT_DEF_VID_1_PORT_DEF_SVID_1_OFFSET  0
	#define PORT_DEF_VID_1_PORT_DEF_SVID_1_LEN     12
	#define PORT_DEF_VID_1_PORT_DEF_SVID_1_DEFAULT 0x0
	/*[field] PORT_DEF_SVID_EN_1*/
	#define PORT_DEF_VID_1_PORT_DEF_SVID_EN_1
	#define PORT_DEF_VID_1_PORT_DEF_SVID_EN_1_OFFSET  12
	#define PORT_DEF_VID_1_PORT_DEF_SVID_EN_1_LEN     1
	#define PORT_DEF_VID_1_PORT_DEF_SVID_EN_1_DEFAULT 0x0
	/*[field] PORT_DEF_CVID_1*/
	#define PORT_DEF_VID_1_PORT_DEF_CVID_1
	#define PORT_DEF_VID_1_PORT_DEF_CVID_1_OFFSET  16
	#define PORT_DEF_VID_1_PORT_DEF_CVID_1_LEN     12
	#define PORT_DEF_VID_1_PORT_DEF_CVID_1_DEFAULT 0x0
	/*[field] PORT_DEF_CVID_EN_1*/
	#define PORT_DEF_VID_1_PORT_DEF_CVID_EN_1
	#define PORT_DEF_VID_1_PORT_DEF_CVID_EN_1_OFFSET  28
	#define PORT_DEF_VID_1_PORT_DEF_CVID_EN_1_LEN     1
	#define PORT_DEF_VID_1_PORT_DEF_CVID_EN_1_DEFAULT 0x0

struct port_def_vid_1 {
	a_uint32_t  port_def_svid_1:12;
	a_uint32_t  port_def_svid_en_1:1;
	a_uint32_t  _reserved0:3;
	a_uint32_t  port_def_cvid_1:12;
	a_uint32_t  port_def_cvid_en_1:1;
	a_uint32_t  _reserved1:3;
};

union port_def_vid_1_u {
	a_uint32_t val;
	struct port_def_vid_1 bf;
};

/*[register] PORT_DEF_VID_2*/
#define PORT_DEF_VID_2
#define PORT_DEF_VID_2_ADDRESS 0x18
#define PORT_DEF_VID_2_NUM     1
#define PORT_DEF_VID_2_INC     0x4
#define PORT_DEF_VID_2_TYPE    REG_TYPE_RW
#define PORT_DEF_VID_2_DEFAULT 0x0
	/*[field] PORT_DEF_SVID_2*/
	#define PORT_DEF_VID_2_PORT_DEF_SVID_2
	#define PORT_DEF_VID_2_PORT_DEF_SVID_2_OFFSET  0
	#define PORT_DEF_VID_2_PORT_DEF_SVID_2_LEN     12
	#define PORT_DEF_VID_2_PORT_DEF_SVID_2_DEFAULT 0x0
	/*[field] PORT_DEF_SVID_EN_2*/
	#define PORT_DEF_VID_2_PORT_DEF_SVID_EN_2
	#define PORT_DEF_VID_2_PORT_DEF_SVID_EN_2_OFFSET  12
	#define PORT_DEF_VID_2_PORT_DEF_SVID_EN_2_LEN     1
	#define PORT_DEF_VID_2_PORT_DEF_SVID_EN_2_DEFAULT 0x0
	/*[field] PORT_DEF_CVID_2*/
	#define PORT_DEF_VID_2_PORT_DEF_CVID_2
	#define PORT_DEF_VID_2_PORT_DEF_CVID_2_OFFSET  16
	#define PORT_DEF_VID_2_PORT_DEF_CVID_2_LEN     12
	#define PORT_DEF_VID_2_PORT_DEF_CVID_2_DEFAULT 0x0
	/*[field] PORT_DEF_CVID_EN_2*/
	#define PORT_DEF_VID_2_PORT_DEF_CVID_EN_2
	#define PORT_DEF_VID_2_PORT_DEF_CVID_EN_2_OFFSET  28
	#define PORT_DEF_VID_2_PORT_DEF_CVID_EN_2_LEN     1
	#define PORT_DEF_VID_2_PORT_DEF_CVID_EN_2_DEFAULT 0x0

struct port_def_vid_2 {
	a_uint32_t  port_def_svid_2:12;
	a_uint32_t  port_def_svid_en_2:1;
	a_uint32_t  _reserved0:3;
	a_uint32_t  port_def_cvid_2:12;
	a_uint32_t  port_def_cvid_en_2:1;
	a_uint32_t  _reserved1:3;
};

union port_def_vid_2_u {
	a_uint32_t val;
	struct port_def_vid_2 bf;
};

/*[register] PORT_DEF_VID_3*/
#define PORT_DEF_VID_3
#define PORT_DEF_VID_3_ADDRESS 0x1c
#define PORT_DEF_VID_3_NUM     1
#define PORT_DEF_VID_3_INC     0x4
#define PORT_DEF_VID_3_TYPE    REG_TYPE_RW
#define PORT_DEF_VID_3_DEFAULT 0x0
	/*[field] PORT_DEF_SVID_3*/
	#define PORT_DEF_VID_3_PORT_DEF_SVID_3
	#define PORT_DEF_VID_3_PORT_DEF_SVID_3_OFFSET  0
	#define PORT_DEF_VID_3_PORT_DEF_SVID_3_LEN     12
	#define PORT_DEF_VID_3_PORT_DEF_SVID_3_DEFAULT 0x0
	/*[field] PORT_DEF_SVID_EN_3*/
	#define PORT_DEF_VID_3_PORT_DEF_SVID_EN_3
	#define PORT_DEF_VID_3_PORT_DEF_SVID_EN_3_OFFSET  12
	#define PORT_DEF_VID_3_PORT_DEF_SVID_EN_3_LEN     1
	#define PORT_DEF_VID_3_PORT_DEF_SVID_EN_3_DEFAULT 0x0
	/*[field] PORT_DEF_CVID_3*/
	#define PORT_DEF_VID_3_PORT_DEF_CVID_3
	#define PORT_DEF_VID_3_PORT_DEF_CVID_3_OFFSET  16
	#define PORT_DEF_VID_3_PORT_DEF_CVID_3_LEN     12
	#define PORT_DEF_VID_3_PORT_DEF_CVID_3_DEFAULT 0x0
	/*[field] PORT_DEF_CVID_EN_3*/
	#define PORT_DEF_VID_3_PORT_DEF_CVID_EN_3
	#define PORT_DEF_VID_3_PORT_DEF_CVID_EN_3_OFFSET  28
	#define PORT_DEF_VID_3_PORT_DEF_CVID_EN_3_LEN     1
	#define PORT_DEF_VID_3_PORT_DEF_CVID_EN_3_DEFAULT 0x0

struct port_def_vid_3 {
	a_uint32_t  port_def_svid_3:12;
	a_uint32_t  port_def_svid_en_3:1;
	a_uint32_t  _reserved0:3;
	a_uint32_t  port_def_cvid_3:12;
	a_uint32_t  port_def_cvid_en_3:1;
	a_uint32_t  _reserved1:3;
};

union port_def_vid_3_u {
	a_uint32_t val;
	struct port_def_vid_3 bf;
};

/*[register] PORT_DEF_VID_4*/
#define PORT_DEF_VID_4
#define PORT_DEF_VID_4_ADDRESS 0x20
#define PORT_DEF_VID_4_NUM     1
#define PORT_DEF_VID_4_INC     0x4
#define PORT_DEF_VID_4_TYPE    REG_TYPE_RW
#define PORT_DEF_VID_4_DEFAULT 0x0
	/*[field] PORT_DEF_SVID_4*/
	#define PORT_DEF_VID_4_PORT_DEF_SVID_4
	#define PORT_DEF_VID_4_PORT_DEF_SVID_4_OFFSET  0
	#define PORT_DEF_VID_4_PORT_DEF_SVID_4_LEN     12
	#define PORT_DEF_VID_4_PORT_DEF_SVID_4_DEFAULT 0x0
	/*[field] PORT_DEF_SVID_EN_4*/
	#define PORT_DEF_VID_4_PORT_DEF_SVID_EN_4
	#define PORT_DEF_VID_4_PORT_DEF_SVID_EN_4_OFFSET  12
	#define PORT_DEF_VID_4_PORT_DEF_SVID_EN_4_LEN     1
	#define PORT_DEF_VID_4_PORT_DEF_SVID_EN_4_DEFAULT 0x0
	/*[field] PORT_DEF_CVID_4*/
	#define PORT_DEF_VID_4_PORT_DEF_CVID_4
	#define PORT_DEF_VID_4_PORT_DEF_CVID_4_OFFSET  16
	#define PORT_DEF_VID_4_PORT_DEF_CVID_4_LEN     12
	#define PORT_DEF_VID_4_PORT_DEF_CVID_4_DEFAULT 0x0
	/*[field] PORT_DEF_CVID_EN_4*/
	#define PORT_DEF_VID_4_PORT_DEF_CVID_EN_4
	#define PORT_DEF_VID_4_PORT_DEF_CVID_EN_4_OFFSET  28
	#define PORT_DEF_VID_4_PORT_DEF_CVID_EN_4_LEN     1
	#define PORT_DEF_VID_4_PORT_DEF_CVID_EN_4_DEFAULT 0x0

struct port_def_vid_4 {
	a_uint32_t  port_def_svid_4:12;
	a_uint32_t  port_def_svid_en_4:1;
	a_uint32_t  _reserved0:3;
	a_uint32_t  port_def_cvid_4:12;
	a_uint32_t  port_def_cvid_en_4:1;
	a_uint32_t  _reserved1:3;
};

union port_def_vid_4_u {
	a_uint32_t val;
	struct port_def_vid_4 bf;
};

/*[register] PORT_DEF_VID_5*/
#define PORT_DEF_VID_5
#define PORT_DEF_VID_5_ADDRESS 0x24
#define PORT_DEF_VID_5_NUM     1
#define PORT_DEF_VID_5_INC     0x4
#define PORT_DEF_VID_5_TYPE    REG_TYPE_RW
#define PORT_DEF_VID_5_DEFAULT 0x0
	/*[field] PORT_DEF_SVID_5*/
	#define PORT_DEF_VID_5_PORT_DEF_SVID_5
	#define PORT_DEF_VID_5_PORT_DEF_SVID_5_OFFSET  0
	#define PORT_DEF_VID_5_PORT_DEF_SVID_5_LEN     12
	#define PORT_DEF_VID_5_PORT_DEF_SVID_5_DEFAULT 0x0
	/*[field] PORT_DEF_SVID_EN_5*/
	#define PORT_DEF_VID_5_PORT_DEF_SVID_EN_5
	#define PORT_DEF_VID_5_PORT_DEF_SVID_EN_5_OFFSET  12
	#define PORT_DEF_VID_5_PORT_DEF_SVID_EN_5_LEN     1
	#define PORT_DEF_VID_5_PORT_DEF_SVID_EN_5_DEFAULT 0x0
	/*[field] PORT_DEF_CVID_5*/
	#define PORT_DEF_VID_5_PORT_DEF_CVID_5
	#define PORT_DEF_VID_5_PORT_DEF_CVID_5_OFFSET  16
	#define PORT_DEF_VID_5_PORT_DEF_CVID_5_LEN     12
	#define PORT_DEF_VID_5_PORT_DEF_CVID_5_DEFAULT 0x0
	/*[field] PORT_DEF_CVID_EN_5*/
	#define PORT_DEF_VID_5_PORT_DEF_CVID_EN_5
	#define PORT_DEF_VID_5_PORT_DEF_CVID_EN_5_OFFSET  28
	#define PORT_DEF_VID_5_PORT_DEF_CVID_EN_5_LEN     1
	#define PORT_DEF_VID_5_PORT_DEF_CVID_EN_5_DEFAULT 0x0

struct port_def_vid_5 {
	a_uint32_t  port_def_svid_5:12;
	a_uint32_t  port_def_svid_en_5:1;
	a_uint32_t  _reserved0:3;
	a_uint32_t  port_def_cvid_5:12;
	a_uint32_t  port_def_cvid_en_5:1;
	a_uint32_t  _reserved1:3;
};

union port_def_vid_5_u {
	a_uint32_t val;
	struct port_def_vid_5 bf;
};

/*[register] PORT_DEF_VID_6*/
#define PORT_DEF_VID_6
#define PORT_DEF_VID_6_ADDRESS 0x28
#define PORT_DEF_VID_6_NUM     1
#define PORT_DEF_VID_6_INC     0x4
#define PORT_DEF_VID_6_TYPE    REG_TYPE_RW
#define PORT_DEF_VID_6_DEFAULT 0x0
	/*[field] PORT_DEF_SVID_6*/
	#define PORT_DEF_VID_6_PORT_DEF_SVID_6
	#define PORT_DEF_VID_6_PORT_DEF_SVID_6_OFFSET  0
	#define PORT_DEF_VID_6_PORT_DEF_SVID_6_LEN     12
	#define PORT_DEF_VID_6_PORT_DEF_SVID_6_DEFAULT 0x0
	/*[field] PORT_DEF_SVID_EN_6*/
	#define PORT_DEF_VID_6_PORT_DEF_SVID_EN_6
	#define PORT_DEF_VID_6_PORT_DEF_SVID_EN_6_OFFSET  12
	#define PORT_DEF_VID_6_PORT_DEF_SVID_EN_6_LEN     1
	#define PORT_DEF_VID_6_PORT_DEF_SVID_EN_6_DEFAULT 0x0
	/*[field] PORT_DEF_CVID_6*/
	#define PORT_DEF_VID_6_PORT_DEF_CVID_6
	#define PORT_DEF_VID_6_PORT_DEF_CVID_6_OFFSET  16
	#define PORT_DEF_VID_6_PORT_DEF_CVID_6_LEN     12
	#define PORT_DEF_VID_6_PORT_DEF_CVID_6_DEFAULT 0x0
	/*[field] PORT_DEF_CVID_EN_6*/
	#define PORT_DEF_VID_6_PORT_DEF_CVID_EN_6
	#define PORT_DEF_VID_6_PORT_DEF_CVID_EN_6_OFFSET  28
	#define PORT_DEF_VID_6_PORT_DEF_CVID_EN_6_LEN     1
	#define PORT_DEF_VID_6_PORT_DEF_CVID_EN_6_DEFAULT 0x0

struct port_def_vid_6 {
	a_uint32_t  port_def_svid_6:12;
	a_uint32_t  port_def_svid_en_6:1;
	a_uint32_t  _reserved0:3;
	a_uint32_t  port_def_cvid_6:12;
	a_uint32_t  port_def_cvid_en_6:1;
	a_uint32_t  _reserved1:3;
};

union port_def_vid_6_u {
	a_uint32_t val;
	struct port_def_vid_6 bf;
};

/*[register] PORT_DEF_VID_7*/
#define PORT_DEF_VID_7
#define PORT_DEF_VID_7_ADDRESS 0x2c
#define PORT_DEF_VID_7_NUM     1
#define PORT_DEF_VID_7_INC     0x4
#define PORT_DEF_VID_7_TYPE    REG_TYPE_RW
#define PORT_DEF_VID_7_DEFAULT 0x0
	/*[field] PORT_DEF_SVID_7*/
	#define PORT_DEF_VID_7_PORT_DEF_SVID_7
	#define PORT_DEF_VID_7_PORT_DEF_SVID_7_OFFSET  0
	#define PORT_DEF_VID_7_PORT_DEF_SVID_7_LEN     12
	#define PORT_DEF_VID_7_PORT_DEF_SVID_7_DEFAULT 0x0
	/*[field] PORT_DEF_SVID_EN_7*/
	#define PORT_DEF_VID_7_PORT_DEF_SVID_EN_7
	#define PORT_DEF_VID_7_PORT_DEF_SVID_EN_7_OFFSET  12
	#define PORT_DEF_VID_7_PORT_DEF_SVID_EN_7_LEN     1
	#define PORT_DEF_VID_7_PORT_DEF_SVID_EN_7_DEFAULT 0x0
	/*[field] PORT_DEF_CVID_7*/
	#define PORT_DEF_VID_7_PORT_DEF_CVID_7
	#define PORT_DEF_VID_7_PORT_DEF_CVID_7_OFFSET  16
	#define PORT_DEF_VID_7_PORT_DEF_CVID_7_LEN     12
	#define PORT_DEF_VID_7_PORT_DEF_CVID_7_DEFAULT 0x0
	/*[field] PORT_DEF_CVID_EN_7*/
	#define PORT_DEF_VID_7_PORT_DEF_CVID_EN_7
	#define PORT_DEF_VID_7_PORT_DEF_CVID_EN_7_OFFSET  28
	#define PORT_DEF_VID_7_PORT_DEF_CVID_EN_7_LEN     1
	#define PORT_DEF_VID_7_PORT_DEF_CVID_EN_7_DEFAULT 0x0

struct port_def_vid_7 {
	a_uint32_t  port_def_svid_7:12;
	a_uint32_t  port_def_svid_en_7:1;
	a_uint32_t  _reserved0:3;
	a_uint32_t  port_def_cvid_7:12;
	a_uint32_t  port_def_cvid_en_7:1;
	a_uint32_t  _reserved1:3;
};

union port_def_vid_7_u {
	a_uint32_t val;
	struct port_def_vid_7 bf;
};

/*[register] PORT_DEF_PCP_0*/
#define PORT_DEF_PCP_0
#define PORT_DEF_PCP_0_ADDRESS 0x30
#define PORT_DEF_PCP_0_NUM     1
#define PORT_DEF_PCP_0_INC     0x4
#define PORT_DEF_PCP_0_TYPE    REG_TYPE_RW
#define PORT_DEF_PCP_0_DEFAULT 0x0
	/*[field] PORT_DEF_SPCP_0*/
	#define PORT_DEF_PCP_0_PORT_DEF_SPCP_0
	#define PORT_DEF_PCP_0_PORT_DEF_SPCP_0_OFFSET  0
	#define PORT_DEF_PCP_0_PORT_DEF_SPCP_0_LEN     3
	#define PORT_DEF_PCP_0_PORT_DEF_SPCP_0_DEFAULT 0x0
	/*[field] PORT_DEF_SDEI_0*/
	#define PORT_DEF_PCP_0_PORT_DEF_SDEI_0
	#define PORT_DEF_PCP_0_PORT_DEF_SDEI_0_OFFSET  3
	#define PORT_DEF_PCP_0_PORT_DEF_SDEI_0_LEN     1
	#define PORT_DEF_PCP_0_PORT_DEF_SDEI_0_DEFAULT 0x0
	/*[field] PORT_DEF_CPCP_0*/
	#define PORT_DEF_PCP_0_PORT_DEF_CPCP_0
	#define PORT_DEF_PCP_0_PORT_DEF_CPCP_0_OFFSET  4
	#define PORT_DEF_PCP_0_PORT_DEF_CPCP_0_LEN     3
	#define PORT_DEF_PCP_0_PORT_DEF_CPCP_0_DEFAULT 0x0
	/*[field] PORT_DEF_CDEI_0*/
	#define PORT_DEF_PCP_0_PORT_DEF_CDEI_0
	#define PORT_DEF_PCP_0_PORT_DEF_CDEI_0_OFFSET  7
	#define PORT_DEF_PCP_0_PORT_DEF_CDEI_0_LEN     1
	#define PORT_DEF_PCP_0_PORT_DEF_CDEI_0_DEFAULT 0x0

struct port_def_pcp_0 {
	a_uint32_t  port_def_spcp_0:3;
	a_uint32_t  port_def_sdei_0:1;
	a_uint32_t  port_def_cpcp_0:3;
	a_uint32_t  port_def_cdei_0:1;
	a_uint32_t  _reserved0:24;
};

union port_def_pcp_0_u {
	a_uint32_t val;
	struct port_def_pcp_0 bf;
};

/*[register] PORT_DEF_PCP_1*/
#define PORT_DEF_PCP_1
#define PORT_DEF_PCP_1_ADDRESS 0x34
#define PORT_DEF_PCP_1_NUM     1
#define PORT_DEF_PCP_1_INC     0x4
#define PORT_DEF_PCP_1_TYPE    REG_TYPE_RW
#define PORT_DEF_PCP_1_DEFAULT 0x0
	/*[field] PORT_DEF_SPCP_1*/
	#define PORT_DEF_PCP_1_PORT_DEF_SPCP_1
	#define PORT_DEF_PCP_1_PORT_DEF_SPCP_1_OFFSET  0
	#define PORT_DEF_PCP_1_PORT_DEF_SPCP_1_LEN     3
	#define PORT_DEF_PCP_1_PORT_DEF_SPCP_1_DEFAULT 0x0
	/*[field] PORT_DEF_SDEI_1*/
	#define PORT_DEF_PCP_1_PORT_DEF_SDEI_1
	#define PORT_DEF_PCP_1_PORT_DEF_SDEI_1_OFFSET  3
	#define PORT_DEF_PCP_1_PORT_DEF_SDEI_1_LEN     1
	#define PORT_DEF_PCP_1_PORT_DEF_SDEI_1_DEFAULT 0x0
	/*[field] PORT_DEF_CPCP_1*/
	#define PORT_DEF_PCP_1_PORT_DEF_CPCP_1
	#define PORT_DEF_PCP_1_PORT_DEF_CPCP_1_OFFSET  4
	#define PORT_DEF_PCP_1_PORT_DEF_CPCP_1_LEN     3
	#define PORT_DEF_PCP_1_PORT_DEF_CPCP_1_DEFAULT 0x0
	/*[field] PORT_DEF_CDEI_1*/
	#define PORT_DEF_PCP_1_PORT_DEF_CDEI_1
	#define PORT_DEF_PCP_1_PORT_DEF_CDEI_1_OFFSET  7
	#define PORT_DEF_PCP_1_PORT_DEF_CDEI_1_LEN     1
	#define PORT_DEF_PCP_1_PORT_DEF_CDEI_1_DEFAULT 0x0

struct port_def_pcp_1 {
	a_uint32_t  port_def_spcp_1:3;
	a_uint32_t  port_def_sdei_1:1;
	a_uint32_t  port_def_cpcp_1:3;
	a_uint32_t  port_def_cdei_1:1;
	a_uint32_t  _reserved0:24;
};

union port_def_pcp_1_u {
	a_uint32_t val;
	struct port_def_pcp_1 bf;
};

/*[register] PORT_DEF_PCP_2*/
#define PORT_DEF_PCP_2
#define PORT_DEF_PCP_2_ADDRESS 0x38
#define PORT_DEF_PCP_2_NUM     1
#define PORT_DEF_PCP_2_INC     0x4
#define PORT_DEF_PCP_2_TYPE    REG_TYPE_RW
#define PORT_DEF_PCP_2_DEFAULT 0x0
	/*[field] PORT_DEF_SPCP_2*/
	#define PORT_DEF_PCP_2_PORT_DEF_SPCP_2
	#define PORT_DEF_PCP_2_PORT_DEF_SPCP_2_OFFSET  0
	#define PORT_DEF_PCP_2_PORT_DEF_SPCP_2_LEN     3
	#define PORT_DEF_PCP_2_PORT_DEF_SPCP_2_DEFAULT 0x0
	/*[field] PORT_DEF_SDEI_2*/
	#define PORT_DEF_PCP_2_PORT_DEF_SDEI_2
	#define PORT_DEF_PCP_2_PORT_DEF_SDEI_2_OFFSET  3
	#define PORT_DEF_PCP_2_PORT_DEF_SDEI_2_LEN     1
	#define PORT_DEF_PCP_2_PORT_DEF_SDEI_2_DEFAULT 0x0
	/*[field] PORT_DEF_CPCP_2*/
	#define PORT_DEF_PCP_2_PORT_DEF_CPCP_2
	#define PORT_DEF_PCP_2_PORT_DEF_CPCP_2_OFFSET  4
	#define PORT_DEF_PCP_2_PORT_DEF_CPCP_2_LEN     3
	#define PORT_DEF_PCP_2_PORT_DEF_CPCP_2_DEFAULT 0x0
	/*[field] PORT_DEF_CDEI_2*/
	#define PORT_DEF_PCP_2_PORT_DEF_CDEI_2
	#define PORT_DEF_PCP_2_PORT_DEF_CDEI_2_OFFSET  7
	#define PORT_DEF_PCP_2_PORT_DEF_CDEI_2_LEN     1
	#define PORT_DEF_PCP_2_PORT_DEF_CDEI_2_DEFAULT 0x0

struct port_def_pcp_2 {
	a_uint32_t  port_def_spcp_2:3;
	a_uint32_t  port_def_sdei_2:1;
	a_uint32_t  port_def_cpcp_2:3;
	a_uint32_t  port_def_cdei_2:1;
	a_uint32_t  _reserved0:24;
};

union port_def_pcp_2_u {
	a_uint32_t val;
	struct port_def_pcp_2 bf;
};

/*[register] PORT_DEF_PCP_3*/
#define PORT_DEF_PCP_3
#define PORT_DEF_PCP_3_ADDRESS 0x3c
#define PORT_DEF_PCP_3_NUM     1
#define PORT_DEF_PCP_3_INC     0x4
#define PORT_DEF_PCP_3_TYPE    REG_TYPE_RW
#define PORT_DEF_PCP_3_DEFAULT 0x0
	/*[field] PORT_DEF_SPCP_3*/
	#define PORT_DEF_PCP_3_PORT_DEF_SPCP_3
	#define PORT_DEF_PCP_3_PORT_DEF_SPCP_3_OFFSET  0
	#define PORT_DEF_PCP_3_PORT_DEF_SPCP_3_LEN     3
	#define PORT_DEF_PCP_3_PORT_DEF_SPCP_3_DEFAULT 0x0
	/*[field] PORT_DEF_SDEI_3*/
	#define PORT_DEF_PCP_3_PORT_DEF_SDEI_3
	#define PORT_DEF_PCP_3_PORT_DEF_SDEI_3_OFFSET  3
	#define PORT_DEF_PCP_3_PORT_DEF_SDEI_3_LEN     1
	#define PORT_DEF_PCP_3_PORT_DEF_SDEI_3_DEFAULT 0x0
	/*[field] PORT_DEF_CPCP_3*/
	#define PORT_DEF_PCP_3_PORT_DEF_CPCP_3
	#define PORT_DEF_PCP_3_PORT_DEF_CPCP_3_OFFSET  4
	#define PORT_DEF_PCP_3_PORT_DEF_CPCP_3_LEN     3
	#define PORT_DEF_PCP_3_PORT_DEF_CPCP_3_DEFAULT 0x0
	/*[field] PORT_DEF_CDEI_3*/
	#define PORT_DEF_PCP_3_PORT_DEF_CDEI_3
	#define PORT_DEF_PCP_3_PORT_DEF_CDEI_3_OFFSET  7
	#define PORT_DEF_PCP_3_PORT_DEF_CDEI_3_LEN     1
	#define PORT_DEF_PCP_3_PORT_DEF_CDEI_3_DEFAULT 0x0

struct port_def_pcp_3 {
	a_uint32_t  port_def_spcp_3:3;
	a_uint32_t  port_def_sdei_3:1;
	a_uint32_t  port_def_cpcp_3:3;
	a_uint32_t  port_def_cdei_3:1;
	a_uint32_t  _reserved0:24;
};

union port_def_pcp_3_u {
	a_uint32_t val;
	struct port_def_pcp_3 bf;
};

/*[register] PORT_DEF_PCP_4*/
#define PORT_DEF_PCP_4
#define PORT_DEF_PCP_4_ADDRESS 0x40
#define PORT_DEF_PCP_4_NUM     1
#define PORT_DEF_PCP_4_INC     0x4
#define PORT_DEF_PCP_4_TYPE    REG_TYPE_RW
#define PORT_DEF_PCP_4_DEFAULT 0x0
	/*[field] PORT_DEF_SPCP_4*/
	#define PORT_DEF_PCP_4_PORT_DEF_SPCP_4
	#define PORT_DEF_PCP_4_PORT_DEF_SPCP_4_OFFSET  0
	#define PORT_DEF_PCP_4_PORT_DEF_SPCP_4_LEN     3
	#define PORT_DEF_PCP_4_PORT_DEF_SPCP_4_DEFAULT 0x0
	/*[field] PORT_DEF_SDEI_4*/
	#define PORT_DEF_PCP_4_PORT_DEF_SDEI_4
	#define PORT_DEF_PCP_4_PORT_DEF_SDEI_4_OFFSET  3
	#define PORT_DEF_PCP_4_PORT_DEF_SDEI_4_LEN     1
	#define PORT_DEF_PCP_4_PORT_DEF_SDEI_4_DEFAULT 0x0
	/*[field] PORT_DEF_CPCP_4*/
	#define PORT_DEF_PCP_4_PORT_DEF_CPCP_4
	#define PORT_DEF_PCP_4_PORT_DEF_CPCP_4_OFFSET  4
	#define PORT_DEF_PCP_4_PORT_DEF_CPCP_4_LEN     3
	#define PORT_DEF_PCP_4_PORT_DEF_CPCP_4_DEFAULT 0x0
	/*[field] PORT_DEF_CDEI_4*/
	#define PORT_DEF_PCP_4_PORT_DEF_CDEI_4
	#define PORT_DEF_PCP_4_PORT_DEF_CDEI_4_OFFSET  7
	#define PORT_DEF_PCP_4_PORT_DEF_CDEI_4_LEN     1
	#define PORT_DEF_PCP_4_PORT_DEF_CDEI_4_DEFAULT 0x0

struct port_def_pcp_4 {
	a_uint32_t  port_def_spcp_4:3;
	a_uint32_t  port_def_sdei_4:1;
	a_uint32_t  port_def_cpcp_4:3;
	a_uint32_t  port_def_cdei_4:1;
	a_uint32_t  _reserved0:24;
};

union port_def_pcp_4_u {
	a_uint32_t val;
	struct port_def_pcp_4 bf;
};

/*[register] PORT_DEF_PCP_5*/
#define PORT_DEF_PCP_5
#define PORT_DEF_PCP_5_ADDRESS 0x44
#define PORT_DEF_PCP_5_NUM     1
#define PORT_DEF_PCP_5_INC     0x4
#define PORT_DEF_PCP_5_TYPE    REG_TYPE_RW
#define PORT_DEF_PCP_5_DEFAULT 0x0
	/*[field] PORT_DEF_SPCP_5*/
	#define PORT_DEF_PCP_5_PORT_DEF_SPCP_5
	#define PORT_DEF_PCP_5_PORT_DEF_SPCP_5_OFFSET  0
	#define PORT_DEF_PCP_5_PORT_DEF_SPCP_5_LEN     3
	#define PORT_DEF_PCP_5_PORT_DEF_SPCP_5_DEFAULT 0x0
	/*[field] PORT_DEF_SDEI_5*/
	#define PORT_DEF_PCP_5_PORT_DEF_SDEI_5
	#define PORT_DEF_PCP_5_PORT_DEF_SDEI_5_OFFSET  3
	#define PORT_DEF_PCP_5_PORT_DEF_SDEI_5_LEN     1
	#define PORT_DEF_PCP_5_PORT_DEF_SDEI_5_DEFAULT 0x0
	/*[field] PORT_DEF_CPCP_5*/
	#define PORT_DEF_PCP_5_PORT_DEF_CPCP_5
	#define PORT_DEF_PCP_5_PORT_DEF_CPCP_5_OFFSET  4
	#define PORT_DEF_PCP_5_PORT_DEF_CPCP_5_LEN     3
	#define PORT_DEF_PCP_5_PORT_DEF_CPCP_5_DEFAULT 0x0
	/*[field] PORT_DEF_CDEI_5*/
	#define PORT_DEF_PCP_5_PORT_DEF_CDEI_5
	#define PORT_DEF_PCP_5_PORT_DEF_CDEI_5_OFFSET  7
	#define PORT_DEF_PCP_5_PORT_DEF_CDEI_5_LEN     1
	#define PORT_DEF_PCP_5_PORT_DEF_CDEI_5_DEFAULT 0x0

struct port_def_pcp_5 {
	a_uint32_t  port_def_spcp_5:3;
	a_uint32_t  port_def_sdei_5:1;
	a_uint32_t  port_def_cpcp_5:3;
	a_uint32_t  port_def_cdei_5:1;
	a_uint32_t  _reserved0:24;
};

union port_def_pcp_5_u {
	a_uint32_t val;
	struct port_def_pcp_5 bf;
};

/*[register] PORT_DEF_PCP_6*/
#define PORT_DEF_PCP_6
#define PORT_DEF_PCP_6_ADDRESS 0x48
#define PORT_DEF_PCP_6_NUM     1
#define PORT_DEF_PCP_6_INC     0x4
#define PORT_DEF_PCP_6_TYPE    REG_TYPE_RW
#define PORT_DEF_PCP_6_DEFAULT 0x0
	/*[field] PORT_DEF_SPCP_6*/
	#define PORT_DEF_PCP_6_PORT_DEF_SPCP_6
	#define PORT_DEF_PCP_6_PORT_DEF_SPCP_6_OFFSET  0
	#define PORT_DEF_PCP_6_PORT_DEF_SPCP_6_LEN     3
	#define PORT_DEF_PCP_6_PORT_DEF_SPCP_6_DEFAULT 0x0
	/*[field] PORT_DEF_SDEI_6*/
	#define PORT_DEF_PCP_6_PORT_DEF_SDEI_6
	#define PORT_DEF_PCP_6_PORT_DEF_SDEI_6_OFFSET  3
	#define PORT_DEF_PCP_6_PORT_DEF_SDEI_6_LEN     1
	#define PORT_DEF_PCP_6_PORT_DEF_SDEI_6_DEFAULT 0x0
	/*[field] PORT_DEF_CPCP_6*/
	#define PORT_DEF_PCP_6_PORT_DEF_CPCP_6
	#define PORT_DEF_PCP_6_PORT_DEF_CPCP_6_OFFSET  4
	#define PORT_DEF_PCP_6_PORT_DEF_CPCP_6_LEN     3
	#define PORT_DEF_PCP_6_PORT_DEF_CPCP_6_DEFAULT 0x0
	/*[field] PORT_DEF_CDEI_6*/
	#define PORT_DEF_PCP_6_PORT_DEF_CDEI_6
	#define PORT_DEF_PCP_6_PORT_DEF_CDEI_6_OFFSET  7
	#define PORT_DEF_PCP_6_PORT_DEF_CDEI_6_LEN     1
	#define PORT_DEF_PCP_6_PORT_DEF_CDEI_6_DEFAULT 0x0

struct port_def_pcp_6 {
	a_uint32_t  port_def_spcp_6:3;
	a_uint32_t  port_def_sdei_6:1;
	a_uint32_t  port_def_cpcp_6:3;
	a_uint32_t  port_def_cdei_6:1;
	a_uint32_t  _reserved0:24;
};

union port_def_pcp_6_u {
	a_uint32_t val;
	struct port_def_pcp_6 bf;
};

/*[register] PORT_DEF_PCP_7*/
#define PORT_DEF_PCP_7
#define PORT_DEF_PCP_7_ADDRESS 0x4c
#define PORT_DEF_PCP_7_NUM     1
#define PORT_DEF_PCP_7_INC     0x4
#define PORT_DEF_PCP_7_TYPE    REG_TYPE_RW
#define PORT_DEF_PCP_7_DEFAULT 0x0
	/*[field] PORT_DEF_SPCP_7*/
	#define PORT_DEF_PCP_7_PORT_DEF_SPCP_7
	#define PORT_DEF_PCP_7_PORT_DEF_SPCP_7_OFFSET  0
	#define PORT_DEF_PCP_7_PORT_DEF_SPCP_7_LEN     3
	#define PORT_DEF_PCP_7_PORT_DEF_SPCP_7_DEFAULT 0x0
	/*[field] PORT_DEF_SDEI_7*/
	#define PORT_DEF_PCP_7_PORT_DEF_SDEI_7
	#define PORT_DEF_PCP_7_PORT_DEF_SDEI_7_OFFSET  3
	#define PORT_DEF_PCP_7_PORT_DEF_SDEI_7_LEN     1
	#define PORT_DEF_PCP_7_PORT_DEF_SDEI_7_DEFAULT 0x0
	/*[field] PORT_DEF_CPCP_7*/
	#define PORT_DEF_PCP_7_PORT_DEF_CPCP_7
	#define PORT_DEF_PCP_7_PORT_DEF_CPCP_7_OFFSET  4
	#define PORT_DEF_PCP_7_PORT_DEF_CPCP_7_LEN     3
	#define PORT_DEF_PCP_7_PORT_DEF_CPCP_7_DEFAULT 0x0
	/*[field] PORT_DEF_CDEI_7*/
	#define PORT_DEF_PCP_7_PORT_DEF_CDEI_7
	#define PORT_DEF_PCP_7_PORT_DEF_CDEI_7_OFFSET  7
	#define PORT_DEF_PCP_7_PORT_DEF_CDEI_7_LEN     1
	#define PORT_DEF_PCP_7_PORT_DEF_CDEI_7_DEFAULT 0x0

struct port_def_pcp_7 {
	a_uint32_t  port_def_spcp_7:3;
	a_uint32_t  port_def_sdei_7:1;
	a_uint32_t  port_def_cpcp_7:3;
	a_uint32_t  port_def_cdei_7:1;
	a_uint32_t  _reserved0:24;
};

union port_def_pcp_7_u {
	a_uint32_t val;
	struct port_def_pcp_7 bf;
};

/*[register] PORT_VLAN_CONFIG_0*/
#define PORT_VLAN_CONFIG_0
#define PORT_VLAN_CONFIG_0_ADDRESS 0x50
#define PORT_VLAN_CONFIG_0_NUM     1
#define PORT_VLAN_CONFIG_0_INC     0x4
#define PORT_VLAN_CONFIG_0_TYPE    REG_TYPE_RW
#define PORT_VLAN_CONFIG_0_DEFAULT 0x0
	/*[field] PORT_IN_PCP_PROP_CMD_0*/
	#define PORT_VLAN_CONFIG_0_PORT_IN_PCP_PROP_CMD_0
	#define PORT_VLAN_CONFIG_0_PORT_IN_PCP_PROP_CMD_0_OFFSET  0
	#define PORT_VLAN_CONFIG_0_PORT_IN_PCP_PROP_CMD_0_LEN     1
	#define PORT_VLAN_CONFIG_0_PORT_IN_PCP_PROP_CMD_0_DEFAULT 0x0
	/*[field] PORT_IN_DEI_PROP_CMD_0*/
	#define PORT_VLAN_CONFIG_0_PORT_IN_DEI_PROP_CMD_0
	#define PORT_VLAN_CONFIG_0_PORT_IN_DEI_PROP_CMD_0_OFFSET  1
	#define PORT_VLAN_CONFIG_0_PORT_IN_DEI_PROP_CMD_0_LEN     1
	#define PORT_VLAN_CONFIG_0_PORT_IN_DEI_PROP_CMD_0_DEFAULT 0x0
	/*[field] PORT_UNTAG_FLTR_CMD_0*/
	#define PORT_VLAN_CONFIG_0_PORT_UNTAG_FLTR_CMD_0
	#define PORT_VLAN_CONFIG_0_PORT_UNTAG_FLTR_CMD_0_OFFSET  2
	#define PORT_VLAN_CONFIG_0_PORT_UNTAG_FLTR_CMD_0_LEN     1
	#define PORT_VLAN_CONFIG_0_PORT_UNTAG_FLTR_CMD_0_DEFAULT 0x0
	/*[field] PORT_PRI_TAG_FLTR_CMD_0*/
	#define PORT_VLAN_CONFIG_0_PORT_PRI_TAG_FLTR_CMD_0
	#define PORT_VLAN_CONFIG_0_PORT_PRI_TAG_FLTR_CMD_0_OFFSET  3
	#define PORT_VLAN_CONFIG_0_PORT_PRI_TAG_FLTR_CMD_0_LEN     1
	#define PORT_VLAN_CONFIG_0_PORT_PRI_TAG_FLTR_CMD_0_DEFAULT 0x0
	/*[field] PORT_TAG_FLTR_CMD_0*/
	#define PORT_VLAN_CONFIG_0_PORT_TAG_FLTR_CMD_0
	#define PORT_VLAN_CONFIG_0_PORT_TAG_FLTR_CMD_0_OFFSET  4
	#define PORT_VLAN_CONFIG_0_PORT_TAG_FLTR_CMD_0_LEN     1
	#define PORT_VLAN_CONFIG_0_PORT_TAG_FLTR_CMD_0_DEFAULT 0x0
	/*[field] PORT_VLAN_XLT_MISS_FWD_CMD_0*/
	#define PORT_VLAN_CONFIG_0_PORT_VLAN_XLT_MISS_FWD_CMD_0
	#define PORT_VLAN_CONFIG_0_PORT_VLAN_XLT_MISS_FWD_CMD_0_OFFSET  5
	#define PORT_VLAN_CONFIG_0_PORT_VLAN_XLT_MISS_FWD_CMD_0_LEN     2
	#define PORT_VLAN_CONFIG_0_PORT_VLAN_XLT_MISS_FWD_CMD_0_DEFAULT 0x0
	/*[field] PORT_IN_VLAN_FLTR_CMD_0*/
	#define PORT_VLAN_CONFIG_0_PORT_IN_VLAN_FLTR_CMD_0
	#define PORT_VLAN_CONFIG_0_PORT_IN_VLAN_FLTR_CMD_0_OFFSET  7
	#define PORT_VLAN_CONFIG_0_PORT_IN_VLAN_FLTR_CMD_0_LEN     1
	#define PORT_VLAN_CONFIG_0_PORT_IN_VLAN_FLTR_CMD_0_DEFAULT 0x0

struct port_vlan_config_0 {
	a_uint32_t  port_in_pcp_prop_cmd_0:1;
	a_uint32_t  port_in_dei_prop_cmd_0:1;
	a_uint32_t  port_untag_fltr_cmd_0:1;
	a_uint32_t  port_pri_tag_fltr_cmd_0:1;
	a_uint32_t  port_tag_fltr_cmd_0:1;
	a_uint32_t  port_vlan_xlt_miss_fwd_cmd_0:2;
	a_uint32_t  port_in_vlan_fltr_cmd_0:1;
	a_uint32_t  _reserved0:24;
};

union port_vlan_config_0_u {
	a_uint32_t val;
	struct port_vlan_config_0 bf;
};

/*[register] PORT_VLAN_CONFIG_1*/
#define PORT_VLAN_CONFIG_1
#define PORT_VLAN_CONFIG_1_ADDRESS 0x54
#define PORT_VLAN_CONFIG_1_NUM     1
#define PORT_VLAN_CONFIG_1_INC     0x4
#define PORT_VLAN_CONFIG_1_TYPE    REG_TYPE_RW
#define PORT_VLAN_CONFIG_1_DEFAULT 0x0
	/*[field] PORT_IN_PCP_PROP_CMD_1*/
	#define PORT_VLAN_CONFIG_1_PORT_IN_PCP_PROP_CMD_1
	#define PORT_VLAN_CONFIG_1_PORT_IN_PCP_PROP_CMD_1_OFFSET  0
	#define PORT_VLAN_CONFIG_1_PORT_IN_PCP_PROP_CMD_1_LEN     1
	#define PORT_VLAN_CONFIG_1_PORT_IN_PCP_PROP_CMD_1_DEFAULT 0x0
	/*[field] PORT_IN_DEI_PROP_CMD_1*/
	#define PORT_VLAN_CONFIG_1_PORT_IN_DEI_PROP_CMD_1
	#define PORT_VLAN_CONFIG_1_PORT_IN_DEI_PROP_CMD_1_OFFSET  1
	#define PORT_VLAN_CONFIG_1_PORT_IN_DEI_PROP_CMD_1_LEN     1
	#define PORT_VLAN_CONFIG_1_PORT_IN_DEI_PROP_CMD_1_DEFAULT 0x0
	/*[field] PORT_UNTAG_FLTR_CMD_1*/
	#define PORT_VLAN_CONFIG_1_PORT_UNTAG_FLTR_CMD_1
	#define PORT_VLAN_CONFIG_1_PORT_UNTAG_FLTR_CMD_1_OFFSET  2
	#define PORT_VLAN_CONFIG_1_PORT_UNTAG_FLTR_CMD_1_LEN     1
	#define PORT_VLAN_CONFIG_1_PORT_UNTAG_FLTR_CMD_1_DEFAULT 0x0
	/*[field] PORT_PRI_TAG_FLTR_CMD_1*/
	#define PORT_VLAN_CONFIG_1_PORT_PRI_TAG_FLTR_CMD_1
	#define PORT_VLAN_CONFIG_1_PORT_PRI_TAG_FLTR_CMD_1_OFFSET  3
	#define PORT_VLAN_CONFIG_1_PORT_PRI_TAG_FLTR_CMD_1_LEN     1
	#define PORT_VLAN_CONFIG_1_PORT_PRI_TAG_FLTR_CMD_1_DEFAULT 0x0
	/*[field] PORT_TAG_FLTR_CMD_1*/
	#define PORT_VLAN_CONFIG_1_PORT_TAG_FLTR_CMD_1
	#define PORT_VLAN_CONFIG_1_PORT_TAG_FLTR_CMD_1_OFFSET  4
	#define PORT_VLAN_CONFIG_1_PORT_TAG_FLTR_CMD_1_LEN     1
	#define PORT_VLAN_CONFIG_1_PORT_TAG_FLTR_CMD_1_DEFAULT 0x0
	/*[field] PORT_VLAN_XLT_MISS_FWD_CMD_1*/
	#define PORT_VLAN_CONFIG_1_PORT_VLAN_XLT_MISS_FWD_CMD_1
	#define PORT_VLAN_CONFIG_1_PORT_VLAN_XLT_MISS_FWD_CMD_1_OFFSET  5
	#define PORT_VLAN_CONFIG_1_PORT_VLAN_XLT_MISS_FWD_CMD_1_LEN     2
	#define PORT_VLAN_CONFIG_1_PORT_VLAN_XLT_MISS_FWD_CMD_1_DEFAULT 0x0
	/*[field] PORT_IN_VLAN_FLTR_CMD_1*/
	#define PORT_VLAN_CONFIG_1_PORT_IN_VLAN_FLTR_CMD_1
	#define PORT_VLAN_CONFIG_1_PORT_IN_VLAN_FLTR_CMD_1_OFFSET  7
	#define PORT_VLAN_CONFIG_1_PORT_IN_VLAN_FLTR_CMD_1_LEN     1
	#define PORT_VLAN_CONFIG_1_PORT_IN_VLAN_FLTR_CMD_1_DEFAULT 0x0

struct port_vlan_config_1 {
	a_uint32_t  port_in_pcp_prop_cmd_1:1;
	a_uint32_t  port_in_dei_prop_cmd_1:1;
	a_uint32_t  port_untag_fltr_cmd_1:1;
	a_uint32_t  port_pri_tag_fltr_cmd_1:1;
	a_uint32_t  port_tag_fltr_cmd_1:1;
	a_uint32_t  port_vlan_xlt_miss_fwd_cmd_1:2;
	a_uint32_t  port_in_vlan_fltr_cmd_1:1;
	a_uint32_t  _reserved0:24;
};

union port_vlan_config_1_u {
	a_uint32_t val;
	struct port_vlan_config_1 bf;
};

/*[register] PORT_VLAN_CONFIG_2*/
#define PORT_VLAN_CONFIG_2
#define PORT_VLAN_CONFIG_2_ADDRESS 0x58
#define PORT_VLAN_CONFIG_2_NUM     1
#define PORT_VLAN_CONFIG_2_INC     0x4
#define PORT_VLAN_CONFIG_2_TYPE    REG_TYPE_RW
#define PORT_VLAN_CONFIG_2_DEFAULT 0x0
	/*[field] PORT_IN_PCP_PROP_CMD_2*/
	#define PORT_VLAN_CONFIG_2_PORT_IN_PCP_PROP_CMD_2
	#define PORT_VLAN_CONFIG_2_PORT_IN_PCP_PROP_CMD_2_OFFSET  0
	#define PORT_VLAN_CONFIG_2_PORT_IN_PCP_PROP_CMD_2_LEN     1
	#define PORT_VLAN_CONFIG_2_PORT_IN_PCP_PROP_CMD_2_DEFAULT 0x0
	/*[field] PORT_IN_DEI_PROP_CMD_2*/
	#define PORT_VLAN_CONFIG_2_PORT_IN_DEI_PROP_CMD_2
	#define PORT_VLAN_CONFIG_2_PORT_IN_DEI_PROP_CMD_2_OFFSET  1
	#define PORT_VLAN_CONFIG_2_PORT_IN_DEI_PROP_CMD_2_LEN     1
	#define PORT_VLAN_CONFIG_2_PORT_IN_DEI_PROP_CMD_2_DEFAULT 0x0
	/*[field] PORT_UNTAG_FLTR_CMD_2*/
	#define PORT_VLAN_CONFIG_2_PORT_UNTAG_FLTR_CMD_2
	#define PORT_VLAN_CONFIG_2_PORT_UNTAG_FLTR_CMD_2_OFFSET  2
	#define PORT_VLAN_CONFIG_2_PORT_UNTAG_FLTR_CMD_2_LEN     1
	#define PORT_VLAN_CONFIG_2_PORT_UNTAG_FLTR_CMD_2_DEFAULT 0x0
	/*[field] PORT_PRI_TAG_FLTR_CMD_2*/
	#define PORT_VLAN_CONFIG_2_PORT_PRI_TAG_FLTR_CMD_2
	#define PORT_VLAN_CONFIG_2_PORT_PRI_TAG_FLTR_CMD_2_OFFSET  3
	#define PORT_VLAN_CONFIG_2_PORT_PRI_TAG_FLTR_CMD_2_LEN     1
	#define PORT_VLAN_CONFIG_2_PORT_PRI_TAG_FLTR_CMD_2_DEFAULT 0x0
	/*[field] PORT_TAG_FLTR_CMD_2*/
	#define PORT_VLAN_CONFIG_2_PORT_TAG_FLTR_CMD_2
	#define PORT_VLAN_CONFIG_2_PORT_TAG_FLTR_CMD_2_OFFSET  4
	#define PORT_VLAN_CONFIG_2_PORT_TAG_FLTR_CMD_2_LEN     1
	#define PORT_VLAN_CONFIG_2_PORT_TAG_FLTR_CMD_2_DEFAULT 0x0
	/*[field] PORT_VLAN_XLT_MISS_FWD_CMD_2*/
	#define PORT_VLAN_CONFIG_2_PORT_VLAN_XLT_MISS_FWD_CMD_2
	#define PORT_VLAN_CONFIG_2_PORT_VLAN_XLT_MISS_FWD_CMD_2_OFFSET  5
	#define PORT_VLAN_CONFIG_2_PORT_VLAN_XLT_MISS_FWD_CMD_2_LEN     2
	#define PORT_VLAN_CONFIG_2_PORT_VLAN_XLT_MISS_FWD_CMD_2_DEFAULT 0x0
	/*[field] PORT_IN_VLAN_FLTR_CMD_2*/
	#define PORT_VLAN_CONFIG_2_PORT_IN_VLAN_FLTR_CMD_2
	#define PORT_VLAN_CONFIG_2_PORT_IN_VLAN_FLTR_CMD_2_OFFSET  7
	#define PORT_VLAN_CONFIG_2_PORT_IN_VLAN_FLTR_CMD_2_LEN     1
	#define PORT_VLAN_CONFIG_2_PORT_IN_VLAN_FLTR_CMD_2_DEFAULT 0x0

struct port_vlan_config_2 {
	a_uint32_t  port_in_pcp_prop_cmd_2:1;
	a_uint32_t  port_in_dei_prop_cmd_2:1;
	a_uint32_t  port_untag_fltr_cmd_2:1;
	a_uint32_t  port_pri_tag_fltr_cmd_2:1;
	a_uint32_t  port_tag_fltr_cmd_2:1;
	a_uint32_t  port_vlan_xlt_miss_fwd_cmd_2:2;
	a_uint32_t  port_in_vlan_fltr_cmd_2:1;
	a_uint32_t  _reserved0:24;
};

union port_vlan_config_2_u {
	a_uint32_t val;
	struct port_vlan_config_2 bf;
};

/*[register] PORT_VLAN_CONFIG_3*/
#define PORT_VLAN_CONFIG_3
#define PORT_VLAN_CONFIG_3_ADDRESS 0x5c
#define PORT_VLAN_CONFIG_3_NUM     1
#define PORT_VLAN_CONFIG_3_INC     0x4
#define PORT_VLAN_CONFIG_3_TYPE    REG_TYPE_RW
#define PORT_VLAN_CONFIG_3_DEFAULT 0x0
	/*[field] PORT_IN_PCP_PROP_CMD_3*/
	#define PORT_VLAN_CONFIG_3_PORT_IN_PCP_PROP_CMD_3
	#define PORT_VLAN_CONFIG_3_PORT_IN_PCP_PROP_CMD_3_OFFSET  0
	#define PORT_VLAN_CONFIG_3_PORT_IN_PCP_PROP_CMD_3_LEN     1
	#define PORT_VLAN_CONFIG_3_PORT_IN_PCP_PROP_CMD_3_DEFAULT 0x0
	/*[field] PORT_IN_DEI_PROP_CMD_3*/
	#define PORT_VLAN_CONFIG_3_PORT_IN_DEI_PROP_CMD_3
	#define PORT_VLAN_CONFIG_3_PORT_IN_DEI_PROP_CMD_3_OFFSET  1
	#define PORT_VLAN_CONFIG_3_PORT_IN_DEI_PROP_CMD_3_LEN     1
	#define PORT_VLAN_CONFIG_3_PORT_IN_DEI_PROP_CMD_3_DEFAULT 0x0
	/*[field] PORT_UNTAG_FLTR_CMD_3*/
	#define PORT_VLAN_CONFIG_3_PORT_UNTAG_FLTR_CMD_3
	#define PORT_VLAN_CONFIG_3_PORT_UNTAG_FLTR_CMD_3_OFFSET  2
	#define PORT_VLAN_CONFIG_3_PORT_UNTAG_FLTR_CMD_3_LEN     1
	#define PORT_VLAN_CONFIG_3_PORT_UNTAG_FLTR_CMD_3_DEFAULT 0x0
	/*[field] PORT_PRI_TAG_FLTR_CMD_3*/
	#define PORT_VLAN_CONFIG_3_PORT_PRI_TAG_FLTR_CMD_3
	#define PORT_VLAN_CONFIG_3_PORT_PRI_TAG_FLTR_CMD_3_OFFSET  3
	#define PORT_VLAN_CONFIG_3_PORT_PRI_TAG_FLTR_CMD_3_LEN     1
	#define PORT_VLAN_CONFIG_3_PORT_PRI_TAG_FLTR_CMD_3_DEFAULT 0x0
	/*[field] PORT_TAG_FLTR_CMD_3*/
	#define PORT_VLAN_CONFIG_3_PORT_TAG_FLTR_CMD_3
	#define PORT_VLAN_CONFIG_3_PORT_TAG_FLTR_CMD_3_OFFSET  4
	#define PORT_VLAN_CONFIG_3_PORT_TAG_FLTR_CMD_3_LEN     1
	#define PORT_VLAN_CONFIG_3_PORT_TAG_FLTR_CMD_3_DEFAULT 0x0
	/*[field] PORT_VLAN_XLT_MISS_FWD_CMD_3*/
	#define PORT_VLAN_CONFIG_3_PORT_VLAN_XLT_MISS_FWD_CMD_3
	#define PORT_VLAN_CONFIG_3_PORT_VLAN_XLT_MISS_FWD_CMD_3_OFFSET  5
	#define PORT_VLAN_CONFIG_3_PORT_VLAN_XLT_MISS_FWD_CMD_3_LEN     2
	#define PORT_VLAN_CONFIG_3_PORT_VLAN_XLT_MISS_FWD_CMD_3_DEFAULT 0x0
	/*[field] PORT_IN_VLAN_FLTR_CMD_3*/
	#define PORT_VLAN_CONFIG_3_PORT_IN_VLAN_FLTR_CMD_3
	#define PORT_VLAN_CONFIG_3_PORT_IN_VLAN_FLTR_CMD_3_OFFSET  7
	#define PORT_VLAN_CONFIG_3_PORT_IN_VLAN_FLTR_CMD_3_LEN     1
	#define PORT_VLAN_CONFIG_3_PORT_IN_VLAN_FLTR_CMD_3_DEFAULT 0x0

struct port_vlan_config_3 {
	a_uint32_t  port_in_pcp_prop_cmd_3:1;
	a_uint32_t  port_in_dei_prop_cmd_3:1;
	a_uint32_t  port_untag_fltr_cmd_3:1;
	a_uint32_t  port_pri_tag_fltr_cmd_3:1;
	a_uint32_t  port_tag_fltr_cmd_3:1;
	a_uint32_t  port_vlan_xlt_miss_fwd_cmd_3:2;
	a_uint32_t  port_in_vlan_fltr_cmd_3:1;
	a_uint32_t  _reserved0:24;
};

union port_vlan_config_3_u {
	a_uint32_t val;
	struct port_vlan_config_3 bf;
};

/*[register] PORT_VLAN_CONFIG_4*/
#define PORT_VLAN_CONFIG_4
#define PORT_VLAN_CONFIG_4_ADDRESS 0x60
#define PORT_VLAN_CONFIG_4_NUM     1
#define PORT_VLAN_CONFIG_4_INC     0x4
#define PORT_VLAN_CONFIG_4_TYPE    REG_TYPE_RW
#define PORT_VLAN_CONFIG_4_DEFAULT 0x0
	/*[field] PORT_IN_PCP_PROP_CMD_4*/
	#define PORT_VLAN_CONFIG_4_PORT_IN_PCP_PROP_CMD_4
	#define PORT_VLAN_CONFIG_4_PORT_IN_PCP_PROP_CMD_4_OFFSET  0
	#define PORT_VLAN_CONFIG_4_PORT_IN_PCP_PROP_CMD_4_LEN     1
	#define PORT_VLAN_CONFIG_4_PORT_IN_PCP_PROP_CMD_4_DEFAULT 0x0
	/*[field] PORT_IN_DEI_PROP_CMD_4*/
	#define PORT_VLAN_CONFIG_4_PORT_IN_DEI_PROP_CMD_4
	#define PORT_VLAN_CONFIG_4_PORT_IN_DEI_PROP_CMD_4_OFFSET  1
	#define PORT_VLAN_CONFIG_4_PORT_IN_DEI_PROP_CMD_4_LEN     1
	#define PORT_VLAN_CONFIG_4_PORT_IN_DEI_PROP_CMD_4_DEFAULT 0x0
	/*[field] PORT_UNTAG_FLTR_CMD_4*/
	#define PORT_VLAN_CONFIG_4_PORT_UNTAG_FLTR_CMD_4
	#define PORT_VLAN_CONFIG_4_PORT_UNTAG_FLTR_CMD_4_OFFSET  2
	#define PORT_VLAN_CONFIG_4_PORT_UNTAG_FLTR_CMD_4_LEN     1
	#define PORT_VLAN_CONFIG_4_PORT_UNTAG_FLTR_CMD_4_DEFAULT 0x0
	/*[field] PORT_PRI_TAG_FLTR_CMD_4*/
	#define PORT_VLAN_CONFIG_4_PORT_PRI_TAG_FLTR_CMD_4
	#define PORT_VLAN_CONFIG_4_PORT_PRI_TAG_FLTR_CMD_4_OFFSET  3
	#define PORT_VLAN_CONFIG_4_PORT_PRI_TAG_FLTR_CMD_4_LEN     1
	#define PORT_VLAN_CONFIG_4_PORT_PRI_TAG_FLTR_CMD_4_DEFAULT 0x0
	/*[field] PORT_TAG_FLTR_CMD_4*/
	#define PORT_VLAN_CONFIG_4_PORT_TAG_FLTR_CMD_4
	#define PORT_VLAN_CONFIG_4_PORT_TAG_FLTR_CMD_4_OFFSET  4
	#define PORT_VLAN_CONFIG_4_PORT_TAG_FLTR_CMD_4_LEN     1
	#define PORT_VLAN_CONFIG_4_PORT_TAG_FLTR_CMD_4_DEFAULT 0x0
	/*[field] PORT_VLAN_XLT_MISS_FWD_CMD_4*/
	#define PORT_VLAN_CONFIG_4_PORT_VLAN_XLT_MISS_FWD_CMD_4
	#define PORT_VLAN_CONFIG_4_PORT_VLAN_XLT_MISS_FWD_CMD_4_OFFSET  5
	#define PORT_VLAN_CONFIG_4_PORT_VLAN_XLT_MISS_FWD_CMD_4_LEN     2
	#define PORT_VLAN_CONFIG_4_PORT_VLAN_XLT_MISS_FWD_CMD_4_DEFAULT 0x0
	/*[field] PORT_IN_VLAN_FLTR_CMD_4*/
	#define PORT_VLAN_CONFIG_4_PORT_IN_VLAN_FLTR_CMD_4
	#define PORT_VLAN_CONFIG_4_PORT_IN_VLAN_FLTR_CMD_4_OFFSET  7
	#define PORT_VLAN_CONFIG_4_PORT_IN_VLAN_FLTR_CMD_4_LEN     1
	#define PORT_VLAN_CONFIG_4_PORT_IN_VLAN_FLTR_CMD_4_DEFAULT 0x0

struct port_vlan_config_4 {
	a_uint32_t  port_in_pcp_prop_cmd_4:1;
	a_uint32_t  port_in_dei_prop_cmd_4:1;
	a_uint32_t  port_untag_fltr_cmd_4:1;
	a_uint32_t  port_pri_tag_fltr_cmd_4:1;
	a_uint32_t  port_tag_fltr_cmd_4:1;
	a_uint32_t  port_vlan_xlt_miss_fwd_cmd_4:2;
	a_uint32_t  port_in_vlan_fltr_cmd_4:1;
	a_uint32_t  _reserved0:24;
};

union port_vlan_config_4_u {
	a_uint32_t val;
	struct port_vlan_config_4 bf;
};

/*[register] PORT_VLAN_CONFIG_5*/
#define PORT_VLAN_CONFIG_5
#define PORT_VLAN_CONFIG_5_ADDRESS 0x64
#define PORT_VLAN_CONFIG_5_NUM     1
#define PORT_VLAN_CONFIG_5_INC     0x4
#define PORT_VLAN_CONFIG_5_TYPE    REG_TYPE_RW
#define PORT_VLAN_CONFIG_5_DEFAULT 0x0
	/*[field] PORT_IN_PCP_PROP_CMD_5*/
	#define PORT_VLAN_CONFIG_5_PORT_IN_PCP_PROP_CMD_5
	#define PORT_VLAN_CONFIG_5_PORT_IN_PCP_PROP_CMD_5_OFFSET  0
	#define PORT_VLAN_CONFIG_5_PORT_IN_PCP_PROP_CMD_5_LEN     1
	#define PORT_VLAN_CONFIG_5_PORT_IN_PCP_PROP_CMD_5_DEFAULT 0x0
	/*[field] PORT_IN_DEI_PROP_CMD_5*/
	#define PORT_VLAN_CONFIG_5_PORT_IN_DEI_PROP_CMD_5
	#define PORT_VLAN_CONFIG_5_PORT_IN_DEI_PROP_CMD_5_OFFSET  1
	#define PORT_VLAN_CONFIG_5_PORT_IN_DEI_PROP_CMD_5_LEN     1
	#define PORT_VLAN_CONFIG_5_PORT_IN_DEI_PROP_CMD_5_DEFAULT 0x0
	/*[field] PORT_UNTAG_FLTR_CMD_5*/
	#define PORT_VLAN_CONFIG_5_PORT_UNTAG_FLTR_CMD_5
	#define PORT_VLAN_CONFIG_5_PORT_UNTAG_FLTR_CMD_5_OFFSET  2
	#define PORT_VLAN_CONFIG_5_PORT_UNTAG_FLTR_CMD_5_LEN     1
	#define PORT_VLAN_CONFIG_5_PORT_UNTAG_FLTR_CMD_5_DEFAULT 0x0
	/*[field] PORT_PRI_TAG_FLTR_CMD_5*/
	#define PORT_VLAN_CONFIG_5_PORT_PRI_TAG_FLTR_CMD_5
	#define PORT_VLAN_CONFIG_5_PORT_PRI_TAG_FLTR_CMD_5_OFFSET  3
	#define PORT_VLAN_CONFIG_5_PORT_PRI_TAG_FLTR_CMD_5_LEN     1
	#define PORT_VLAN_CONFIG_5_PORT_PRI_TAG_FLTR_CMD_5_DEFAULT 0x0
	/*[field] PORT_TAG_FLTR_CMD_5*/
	#define PORT_VLAN_CONFIG_5_PORT_TAG_FLTR_CMD_5
	#define PORT_VLAN_CONFIG_5_PORT_TAG_FLTR_CMD_5_OFFSET  4
	#define PORT_VLAN_CONFIG_5_PORT_TAG_FLTR_CMD_5_LEN     1
	#define PORT_VLAN_CONFIG_5_PORT_TAG_FLTR_CMD_5_DEFAULT 0x0
	/*[field] PORT_VLAN_XLT_MISS_FWD_CMD_5*/
	#define PORT_VLAN_CONFIG_5_PORT_VLAN_XLT_MISS_FWD_CMD_5
	#define PORT_VLAN_CONFIG_5_PORT_VLAN_XLT_MISS_FWD_CMD_5_OFFSET  5
	#define PORT_VLAN_CONFIG_5_PORT_VLAN_XLT_MISS_FWD_CMD_5_LEN     2
	#define PORT_VLAN_CONFIG_5_PORT_VLAN_XLT_MISS_FWD_CMD_5_DEFAULT 0x0
	/*[field] PORT_IN_VLAN_FLTR_CMD_5*/
	#define PORT_VLAN_CONFIG_5_PORT_IN_VLAN_FLTR_CMD_5
	#define PORT_VLAN_CONFIG_5_PORT_IN_VLAN_FLTR_CMD_5_OFFSET  7
	#define PORT_VLAN_CONFIG_5_PORT_IN_VLAN_FLTR_CMD_5_LEN     1
	#define PORT_VLAN_CONFIG_5_PORT_IN_VLAN_FLTR_CMD_5_DEFAULT 0x0

struct port_vlan_config_5 {
	a_uint32_t  port_in_pcp_prop_cmd_5:1;
	a_uint32_t  port_in_dei_prop_cmd_5:1;
	a_uint32_t  port_untag_fltr_cmd_5:1;
	a_uint32_t  port_pri_tag_fltr_cmd_5:1;
	a_uint32_t  port_tag_fltr_cmd_5:1;
	a_uint32_t  port_vlan_xlt_miss_fwd_cmd_5:2;
	a_uint32_t  port_in_vlan_fltr_cmd_5:1;
	a_uint32_t  _reserved0:24;
};

union port_vlan_config_5_u {
	a_uint32_t val;
	struct port_vlan_config_5 bf;
};

/*[register] PORT_VLAN_CONFIG_6*/
#define PORT_VLAN_CONFIG_6
#define PORT_VLAN_CONFIG_6_ADDRESS 0x68
#define PORT_VLAN_CONFIG_6_NUM     1
#define PORT_VLAN_CONFIG_6_INC     0x4
#define PORT_VLAN_CONFIG_6_TYPE    REG_TYPE_RW
#define PORT_VLAN_CONFIG_6_DEFAULT 0x0
	/*[field] PORT_IN_PCP_PROP_CMD_6*/
	#define PORT_VLAN_CONFIG_6_PORT_IN_PCP_PROP_CMD_6
	#define PORT_VLAN_CONFIG_6_PORT_IN_PCP_PROP_CMD_6_OFFSET  0
	#define PORT_VLAN_CONFIG_6_PORT_IN_PCP_PROP_CMD_6_LEN     1
	#define PORT_VLAN_CONFIG_6_PORT_IN_PCP_PROP_CMD_6_DEFAULT 0x0
	/*[field] PORT_IN_DEI_PROP_CMD_6*/
	#define PORT_VLAN_CONFIG_6_PORT_IN_DEI_PROP_CMD_6
	#define PORT_VLAN_CONFIG_6_PORT_IN_DEI_PROP_CMD_6_OFFSET  1
	#define PORT_VLAN_CONFIG_6_PORT_IN_DEI_PROP_CMD_6_LEN     1
	#define PORT_VLAN_CONFIG_6_PORT_IN_DEI_PROP_CMD_6_DEFAULT 0x0
	/*[field] PORT_UNTAG_FLTR_CMD_6*/
	#define PORT_VLAN_CONFIG_6_PORT_UNTAG_FLTR_CMD_6
	#define PORT_VLAN_CONFIG_6_PORT_UNTAG_FLTR_CMD_6_OFFSET  2
	#define PORT_VLAN_CONFIG_6_PORT_UNTAG_FLTR_CMD_6_LEN     1
	#define PORT_VLAN_CONFIG_6_PORT_UNTAG_FLTR_CMD_6_DEFAULT 0x0
	/*[field] PORT_PRI_TAG_FLTR_CMD_6*/
	#define PORT_VLAN_CONFIG_6_PORT_PRI_TAG_FLTR_CMD_6
	#define PORT_VLAN_CONFIG_6_PORT_PRI_TAG_FLTR_CMD_6_OFFSET  3
	#define PORT_VLAN_CONFIG_6_PORT_PRI_TAG_FLTR_CMD_6_LEN     1
	#define PORT_VLAN_CONFIG_6_PORT_PRI_TAG_FLTR_CMD_6_DEFAULT 0x0
	/*[field] PORT_TAG_FLTR_CMD_6*/
	#define PORT_VLAN_CONFIG_6_PORT_TAG_FLTR_CMD_6
	#define PORT_VLAN_CONFIG_6_PORT_TAG_FLTR_CMD_6_OFFSET  4
	#define PORT_VLAN_CONFIG_6_PORT_TAG_FLTR_CMD_6_LEN     1
	#define PORT_VLAN_CONFIG_6_PORT_TAG_FLTR_CMD_6_DEFAULT 0x0
	/*[field] PORT_VLAN_XLT_MISS_FWD_CMD_6*/
	#define PORT_VLAN_CONFIG_6_PORT_VLAN_XLT_MISS_FWD_CMD_6
	#define PORT_VLAN_CONFIG_6_PORT_VLAN_XLT_MISS_FWD_CMD_6_OFFSET  5
	#define PORT_VLAN_CONFIG_6_PORT_VLAN_XLT_MISS_FWD_CMD_6_LEN     2
	#define PORT_VLAN_CONFIG_6_PORT_VLAN_XLT_MISS_FWD_CMD_6_DEFAULT 0x0
	/*[field] PORT_IN_VLAN_FLTR_CMD_6*/
	#define PORT_VLAN_CONFIG_6_PORT_IN_VLAN_FLTR_CMD_6
	#define PORT_VLAN_CONFIG_6_PORT_IN_VLAN_FLTR_CMD_6_OFFSET  7
	#define PORT_VLAN_CONFIG_6_PORT_IN_VLAN_FLTR_CMD_6_LEN     1
	#define PORT_VLAN_CONFIG_6_PORT_IN_VLAN_FLTR_CMD_6_DEFAULT 0x0

struct port_vlan_config_6 {
	a_uint32_t  port_in_pcp_prop_cmd_6:1;
	a_uint32_t  port_in_dei_prop_cmd_6:1;
	a_uint32_t  port_untag_fltr_cmd_6:1;
	a_uint32_t  port_pri_tag_fltr_cmd_6:1;
	a_uint32_t  port_tag_fltr_cmd_6:1;
	a_uint32_t  port_vlan_xlt_miss_fwd_cmd_6:2;
	a_uint32_t  port_in_vlan_fltr_cmd_6:1;
	a_uint32_t  _reserved0:24;
};

union port_vlan_config_6_u {
	a_uint32_t val;
	struct port_vlan_config_6 bf;
};

/*[register] PORT_VLAN_CONFIG_7*/
#define PORT_VLAN_CONFIG_7
#define PORT_VLAN_CONFIG_7_ADDRESS 0x6c
#define PORT_VLAN_CONFIG_7_NUM     1
#define PORT_VLAN_CONFIG_7_INC     0x4
#define PORT_VLAN_CONFIG_7_TYPE    REG_TYPE_RW
#define PORT_VLAN_CONFIG_7_DEFAULT 0x0
	/*[field] PORT_IN_PCP_PROP_CMD_7*/
	#define PORT_VLAN_CONFIG_7_PORT_IN_PCP_PROP_CMD_7
	#define PORT_VLAN_CONFIG_7_PORT_IN_PCP_PROP_CMD_7_OFFSET  0
	#define PORT_VLAN_CONFIG_7_PORT_IN_PCP_PROP_CMD_7_LEN     1
	#define PORT_VLAN_CONFIG_7_PORT_IN_PCP_PROP_CMD_7_DEFAULT 0x0
	/*[field] PORT_IN_DEI_PROP_CMD_7*/
	#define PORT_VLAN_CONFIG_7_PORT_IN_DEI_PROP_CMD_7
	#define PORT_VLAN_CONFIG_7_PORT_IN_DEI_PROP_CMD_7_OFFSET  1
	#define PORT_VLAN_CONFIG_7_PORT_IN_DEI_PROP_CMD_7_LEN     1
	#define PORT_VLAN_CONFIG_7_PORT_IN_DEI_PROP_CMD_7_DEFAULT 0x0
	/*[field] PORT_UNTAG_FLTR_CMD_7*/
	#define PORT_VLAN_CONFIG_7_PORT_UNTAG_FLTR_CMD_7
	#define PORT_VLAN_CONFIG_7_PORT_UNTAG_FLTR_CMD_7_OFFSET  2
	#define PORT_VLAN_CONFIG_7_PORT_UNTAG_FLTR_CMD_7_LEN     1
	#define PORT_VLAN_CONFIG_7_PORT_UNTAG_FLTR_CMD_7_DEFAULT 0x0
	/*[field] PORT_PRI_TAG_FLTR_CMD_7*/
	#define PORT_VLAN_CONFIG_7_PORT_PRI_TAG_FLTR_CMD_7
	#define PORT_VLAN_CONFIG_7_PORT_PRI_TAG_FLTR_CMD_7_OFFSET  3
	#define PORT_VLAN_CONFIG_7_PORT_PRI_TAG_FLTR_CMD_7_LEN     1
	#define PORT_VLAN_CONFIG_7_PORT_PRI_TAG_FLTR_CMD_7_DEFAULT 0x0
	/*[field] PORT_TAG_FLTR_CMD_7*/
	#define PORT_VLAN_CONFIG_7_PORT_TAG_FLTR_CMD_7
	#define PORT_VLAN_CONFIG_7_PORT_TAG_FLTR_CMD_7_OFFSET  4
	#define PORT_VLAN_CONFIG_7_PORT_TAG_FLTR_CMD_7_LEN     1
	#define PORT_VLAN_CONFIG_7_PORT_TAG_FLTR_CMD_7_DEFAULT 0x0
	/*[field] PORT_VLAN_XLT_MISS_FWD_CMD_7*/
	#define PORT_VLAN_CONFIG_7_PORT_VLAN_XLT_MISS_FWD_CMD_7
	#define PORT_VLAN_CONFIG_7_PORT_VLAN_XLT_MISS_FWD_CMD_7_OFFSET  5
	#define PORT_VLAN_CONFIG_7_PORT_VLAN_XLT_MISS_FWD_CMD_7_LEN     2
	#define PORT_VLAN_CONFIG_7_PORT_VLAN_XLT_MISS_FWD_CMD_7_DEFAULT 0x0
	/*[field] PORT_IN_VLAN_FLTR_CMD_7*/
	#define PORT_VLAN_CONFIG_7_PORT_IN_VLAN_FLTR_CMD_7
	#define PORT_VLAN_CONFIG_7_PORT_IN_VLAN_FLTR_CMD_7_OFFSET  7
	#define PORT_VLAN_CONFIG_7_PORT_IN_VLAN_FLTR_CMD_7_LEN     1
	#define PORT_VLAN_CONFIG_7_PORT_IN_VLAN_FLTR_CMD_7_DEFAULT 0x0

struct port_vlan_config_7 {
	a_uint32_t  port_in_pcp_prop_cmd_7:1;
	a_uint32_t  port_in_dei_prop_cmd_7:1;
	a_uint32_t  port_untag_fltr_cmd_7:1;
	a_uint32_t  port_pri_tag_fltr_cmd_7:1;
	a_uint32_t  port_tag_fltr_cmd_7:1;
	a_uint32_t  port_vlan_xlt_miss_fwd_cmd_7:2;
	a_uint32_t  port_in_vlan_fltr_cmd_7:1;
	a_uint32_t  _reserved0:24;
};

union port_vlan_config_7_u {
	a_uint32_t val;
	struct port_vlan_config_7 bf;
};

/*[register] IV_DBG_ADDR*/
#define IV_DBG_ADDR
#define IV_DBG_ADDR_ADDRESS 0x70
#define IV_DBG_ADDR_NUM     1
#define IV_DBG_ADDR_INC     0x4
#define IV_DBG_ADDR_TYPE    REG_TYPE_RW
#define IV_DBG_ADDR_DEFAULT 0x0
	/*[field] DBG_ADDR*/
	#define IV_DBG_ADDR_DBG_ADDR
	#define IV_DBG_ADDR_DBG_ADDR_OFFSET  0
	#define IV_DBG_ADDR_DBG_ADDR_LEN     8
	#define IV_DBG_ADDR_DBG_ADDR_DEFAULT 0x0

struct iv_dbg_addr {
	a_uint32_t  dbg_addr:8;
	a_uint32_t  _reserved0:24;
};

union iv_dbg_addr_u {
	a_uint32_t val;
	struct iv_dbg_addr bf;
};

/*[register] IV_DBG_DATA*/
#define IV_DBG_DATA
#define IV_DBG_DATA_ADDRESS 0x74
#define IV_DBG_DATA_NUM     1
#define IV_DBG_DATA_INC     0x4
#define IV_DBG_DATA_TYPE    REG_TYPE_RO
#define IV_DBG_DATA_DEFAULT 0x0
	/*[field] DBG_DATA*/
	#define IV_DBG_DATA_DBG_DATA
	#define IV_DBG_DATA_DBG_DATA_OFFSET  0
	#define IV_DBG_DATA_DBG_DATA_LEN     32
	#define IV_DBG_DATA_DBG_DATA_DEFAULT 0x0

struct iv_dbg_data {
	a_uint32_t  dbg_data:32;
};

union iv_dbg_data_u {
	a_uint32_t val;
	struct iv_dbg_data bf;
};

/*[register] ECO_RESERVE*/
#define ECO_RESERVE
#define ECO_RESERVE_ADDRESS 0x78
#define ECO_RESERVE_NUM     1
#define ECO_RESERVE_INC     0x4
#define ECO_RESERVE_TYPE    REG_TYPE_RW
#define ECO_RESERVE_DEFAULT 0x0
	/*[field] ECO_RES*/
	#define ECO_RESERVE_ECO_RES
	#define ECO_RESERVE_ECO_RES_OFFSET  0
	#define ECO_RESERVE_ECO_RES_LEN     32
	#define ECO_RESERVE_ECO_RES_DEFAULT 0x0

struct eco_reserve {
	a_uint32_t  eco_res:32;
};

union eco_reserve_u {
	a_uint32_t val;
	struct eco_reserve bf;
};

/*[table] XLT_RULE_TBL*/
#define XLT_RULE_TBL
#define XLT_RULE_TBL_ADDRESS 0x2000
#define XLT_RULE_TBL_NUM     64
#define XLT_RULE_TBL_INC     0x10
#define XLT_RULE_TBL_TYPE    REG_TYPE_RW
#define XLT_RULE_TBL_DEFAULT 0x0
	/*[field] VALID*/
	#define XLT_RULE_TBL_VALID
	#define XLT_RULE_TBL_VALID_OFFSET  0
	#define XLT_RULE_TBL_VALID_LEN     1
	#define XLT_RULE_TBL_VALID_DEFAULT 0x0
	/*[field] PORT_BITMAP*/
	#define XLT_RULE_TBL_PORT_BITMAP
	#define XLT_RULE_TBL_PORT_BITMAP_OFFSET  1
	#define XLT_RULE_TBL_PORT_BITMAP_LEN     8
	#define XLT_RULE_TBL_PORT_BITMAP_DEFAULT 0x0
	/*[field] SKEY_FMT*/
	#define XLT_RULE_TBL_SKEY_FMT
	#define XLT_RULE_TBL_SKEY_FMT_OFFSET  9
	#define XLT_RULE_TBL_SKEY_FMT_LEN     3
	#define XLT_RULE_TBL_SKEY_FMT_DEFAULT 0x0
	/*[field] SKEY_VID_INCL*/
	#define XLT_RULE_TBL_SKEY_VID_INCL
	#define XLT_RULE_TBL_SKEY_VID_INCL_OFFSET  12
	#define XLT_RULE_TBL_SKEY_VID_INCL_LEN     1
	#define XLT_RULE_TBL_SKEY_VID_INCL_DEFAULT 0x0
	/*[field] SKEY_VID*/
	#define XLT_RULE_TBL_SKEY_VID
	#define XLT_RULE_TBL_SKEY_VID_OFFSET  13
	#define XLT_RULE_TBL_SKEY_VID_LEN     12
	#define XLT_RULE_TBL_SKEY_VID_DEFAULT 0x0
	/*[field] SKEY_PCP_INCL*/
	#define XLT_RULE_TBL_SKEY_PCP_INCL
	#define XLT_RULE_TBL_SKEY_PCP_INCL_OFFSET  25
	#define XLT_RULE_TBL_SKEY_PCP_INCL_LEN     1
	#define XLT_RULE_TBL_SKEY_PCP_INCL_DEFAULT 0x0
	/*[field] SKEY_PCP*/
	#define XLT_RULE_TBL_SKEY_PCP
	#define XLT_RULE_TBL_SKEY_PCP_OFFSET  26
	#define XLT_RULE_TBL_SKEY_PCP_LEN     3
	#define XLT_RULE_TBL_SKEY_PCP_DEFAULT 0x0
	/*[field] SKEY_DEI_INCL*/
	#define XLT_RULE_TBL_SKEY_DEI_INCL
	#define XLT_RULE_TBL_SKEY_DEI_INCL_OFFSET  29
	#define XLT_RULE_TBL_SKEY_DEI_INCL_LEN     1
	#define XLT_RULE_TBL_SKEY_DEI_INCL_DEFAULT 0x0
	/*[field] SKEY_DEI*/
	#define XLT_RULE_TBL_SKEY_DEI
	#define XLT_RULE_TBL_SKEY_DEI_OFFSET  30
	#define XLT_RULE_TBL_SKEY_DEI_LEN     1
	#define XLT_RULE_TBL_SKEY_DEI_DEFAULT 0x0
	/*[field] CKEY_FMT*/
	#define XLT_RULE_TBL_CKEY_FMT
	#define XLT_RULE_TBL_CKEY_FMT_OFFSET  31
	#define XLT_RULE_TBL_CKEY_FMT_LEN     3
	#define XLT_RULE_TBL_CKEY_FMT_DEFAULT 0x0
	/*[field] CKEY_VID_INCL*/
	#define XLT_RULE_TBL_CKEY_VID_INCL
	#define XLT_RULE_TBL_CKEY_VID_INCL_OFFSET  34
	#define XLT_RULE_TBL_CKEY_VID_INCL_LEN     1
	#define XLT_RULE_TBL_CKEY_VID_INCL_DEFAULT 0x0
	/*[field] CKEY_VID*/
	#define XLT_RULE_TBL_CKEY_VID
	#define XLT_RULE_TBL_CKEY_VID_OFFSET  35
	#define XLT_RULE_TBL_CKEY_VID_LEN     12
	#define XLT_RULE_TBL_CKEY_VID_DEFAULT 0x0
	/*[field] CKEY_PCP_INCL*/
	#define XLT_RULE_TBL_CKEY_PCP_INCL
	#define XLT_RULE_TBL_CKEY_PCP_INCL_OFFSET  47
	#define XLT_RULE_TBL_CKEY_PCP_INCL_LEN     1
	#define XLT_RULE_TBL_CKEY_PCP_INCL_DEFAULT 0x0
	/*[field] CKEY_PCP*/
	#define XLT_RULE_TBL_CKEY_PCP
	#define XLT_RULE_TBL_CKEY_PCP_OFFSET  48
	#define XLT_RULE_TBL_CKEY_PCP_LEN     3
	#define XLT_RULE_TBL_CKEY_PCP_DEFAULT 0x0
	/*[field] CKEY_DEI_INCL*/
	#define XLT_RULE_TBL_CKEY_DEI_INCL
	#define XLT_RULE_TBL_CKEY_DEI_INCL_OFFSET  51
	#define XLT_RULE_TBL_CKEY_DEI_INCL_LEN     1
	#define XLT_RULE_TBL_CKEY_DEI_INCL_DEFAULT 0x0
	/*[field] CKEY_DEI*/
	#define XLT_RULE_TBL_CKEY_DEI
	#define XLT_RULE_TBL_CKEY_DEI_OFFSET  52
	#define XLT_RULE_TBL_CKEY_DEI_LEN     1
	#define XLT_RULE_TBL_CKEY_DEI_DEFAULT 0x0
	/*[field] FRM_TYPE_INCL*/
	#define XLT_RULE_TBL_FRM_TYPE_INCL
	#define XLT_RULE_TBL_FRM_TYPE_INCL_OFFSET  53
	#define XLT_RULE_TBL_FRM_TYPE_INCL_LEN     1
	#define XLT_RULE_TBL_FRM_TYPE_INCL_DEFAULT 0x0
	/*[field] FRM_TYPE*/
	#define XLT_RULE_TBL_FRM_TYPE
	#define XLT_RULE_TBL_FRM_TYPE_OFFSET  54
	#define XLT_RULE_TBL_FRM_TYPE_LEN     2
	#define XLT_RULE_TBL_FRM_TYPE_DEFAULT 0x0
	/*[field] PROT_INCL*/
	#define XLT_RULE_TBL_PROT_INCL
	#define XLT_RULE_TBL_PROT_INCL_OFFSET  56
	#define XLT_RULE_TBL_PROT_INCL_LEN     1
	#define XLT_RULE_TBL_PROT_INCL_DEFAULT 0x0
	/*[field] PROT_VALUE*/
	#define XLT_RULE_TBL_PROT_VALUE
	#define XLT_RULE_TBL_PROT_VALUE_OFFSET  57
	#define XLT_RULE_TBL_PROT_VALUE_LEN     16
	#define XLT_RULE_TBL_PROT_VALUE_DEFAULT 0x0

struct xlt_rule_tbl {
	a_uint32_t  valid:1;
	a_uint32_t  port_bitmap:8;
	a_uint32_t  skey_fmt:3;
	a_uint32_t  skey_vid_incl:1;
	a_uint32_t  skey_vid:12;
	a_uint32_t  skey_pcp_incl:1;
	a_uint32_t  skey_pcp:3;
	a_uint32_t  skey_dei_incl:1;
	a_uint32_t  skey_dei:1;
	a_uint32_t  ckey_fmt_0:1;
	a_uint32_t  ckey_fmt_1:2;
	a_uint32_t  ckey_vid_incl:1;
	a_uint32_t  ckey_vid:12;
	a_uint32_t  ckey_pcp_incl:1;
	a_uint32_t  ckey_pcp:3;
	a_uint32_t  ckey_dei_incl:1;
	a_uint32_t  ckey_dei:1;
	a_uint32_t  frm_type_incl:1;
	a_uint32_t  frm_type:2;
	a_uint32_t  prot_incl:1;
	a_uint32_t  prot_value_0:7;
	a_uint32_t  prot_value_1:9;
	a_uint32_t  _reserved0:23;
};

union xlt_rule_tbl_u {
	a_uint32_t val[3];
	struct xlt_rule_tbl bf;
};

/*[table] XLT_ACTION_TBL*/
#define XLT_ACTION_TBL
#define XLT_ACTION_TBL_ADDRESS 0x4000
#define XLT_ACTION_TBL_NUM     64
#define XLT_ACTION_TBL_INC     0x10
#define XLT_ACTION_TBL_TYPE    REG_TYPE_RW
#define XLT_ACTION_TBL_DEFAULT 0x0
	/*[field] VID_SWAP_CMD*/
	#define XLT_ACTION_TBL_VID_SWAP_CMD
	#define XLT_ACTION_TBL_VID_SWAP_CMD_OFFSET  0
	#define XLT_ACTION_TBL_VID_SWAP_CMD_LEN     1
	#define XLT_ACTION_TBL_VID_SWAP_CMD_DEFAULT 0x0
	/*[field] XLT_SVID_CMD*/
	#define XLT_ACTION_TBL_XLT_SVID_CMD
	#define XLT_ACTION_TBL_XLT_SVID_CMD_OFFSET  1
	#define XLT_ACTION_TBL_XLT_SVID_CMD_LEN     2
	#define XLT_ACTION_TBL_XLT_SVID_CMD_DEFAULT 0x0
	/*[field] XLT_SVID*/
	#define XLT_ACTION_TBL_XLT_SVID
	#define XLT_ACTION_TBL_XLT_SVID_OFFSET  3
	#define XLT_ACTION_TBL_XLT_SVID_LEN     12
	#define XLT_ACTION_TBL_XLT_SVID_DEFAULT 0x0
	/*[field] XLT_CVID_CMD*/
	#define XLT_ACTION_TBL_XLT_CVID_CMD
	#define XLT_ACTION_TBL_XLT_CVID_CMD_OFFSET  15
	#define XLT_ACTION_TBL_XLT_CVID_CMD_LEN     2
	#define XLT_ACTION_TBL_XLT_CVID_CMD_DEFAULT 0x0
	/*[field] XLT_CVID*/
	#define XLT_ACTION_TBL_XLT_CVID
	#define XLT_ACTION_TBL_XLT_CVID_OFFSET  17
	#define XLT_ACTION_TBL_XLT_CVID_LEN     12
	#define XLT_ACTION_TBL_XLT_CVID_DEFAULT 0x0
	/*[field] PCP_SWAP_CMD*/
	#define XLT_ACTION_TBL_PCP_SWAP_CMD
	#define XLT_ACTION_TBL_PCP_SWAP_CMD_OFFSET  29
	#define XLT_ACTION_TBL_PCP_SWAP_CMD_LEN     1
	#define XLT_ACTION_TBL_PCP_SWAP_CMD_DEFAULT 0x0
	/*[field] XLT_SPCP_CMD*/
	#define XLT_ACTION_TBL_XLT_SPCP_CMD
	#define XLT_ACTION_TBL_XLT_SPCP_CMD_OFFSET  30
	#define XLT_ACTION_TBL_XLT_SPCP_CMD_LEN     1
	#define XLT_ACTION_TBL_XLT_SPCP_CMD_DEFAULT 0x0
	/*[field] XLT_SPCP*/
	#define XLT_ACTION_TBL_XLT_SPCP
	#define XLT_ACTION_TBL_XLT_SPCP_OFFSET  31
	#define XLT_ACTION_TBL_XLT_SPCP_LEN     3
	#define XLT_ACTION_TBL_XLT_SPCP_DEFAULT 0x0
	/*[field] XLT_CPCP_CMD*/
	#define XLT_ACTION_TBL_XLT_CPCP_CMD
	#define XLT_ACTION_TBL_XLT_CPCP_CMD_OFFSET  34
	#define XLT_ACTION_TBL_XLT_CPCP_CMD_LEN     1
	#define XLT_ACTION_TBL_XLT_CPCP_CMD_DEFAULT 0x0
	/*[field] XLT_CPCP*/
	#define XLT_ACTION_TBL_XLT_CPCP
	#define XLT_ACTION_TBL_XLT_CPCP_OFFSET  35
	#define XLT_ACTION_TBL_XLT_CPCP_LEN     3
	#define XLT_ACTION_TBL_XLT_CPCP_DEFAULT 0x0
	/*[field] DEI_SWAP_CMD*/
	#define XLT_ACTION_TBL_DEI_SWAP_CMD
	#define XLT_ACTION_TBL_DEI_SWAP_CMD_OFFSET  38
	#define XLT_ACTION_TBL_DEI_SWAP_CMD_LEN     1
	#define XLT_ACTION_TBL_DEI_SWAP_CMD_DEFAULT 0x0
	/*[field] XLT_SDEI_CMD*/
	#define XLT_ACTION_TBL_XLT_SDEI_CMD
	#define XLT_ACTION_TBL_XLT_SDEI_CMD_OFFSET  39
	#define XLT_ACTION_TBL_XLT_SDEI_CMD_LEN     1
	#define XLT_ACTION_TBL_XLT_SDEI_CMD_DEFAULT 0x0
	/*[field] XLT_SDEI*/
	#define XLT_ACTION_TBL_XLT_SDEI
	#define XLT_ACTION_TBL_XLT_SDEI_OFFSET  40
	#define XLT_ACTION_TBL_XLT_SDEI_LEN     1
	#define XLT_ACTION_TBL_XLT_SDEI_DEFAULT 0x0
	/*[field] XLT_CDEI_CMD*/
	#define XLT_ACTION_TBL_XLT_CDEI_CMD
	#define XLT_ACTION_TBL_XLT_CDEI_CMD_OFFSET  41
	#define XLT_ACTION_TBL_XLT_CDEI_CMD_LEN     1
	#define XLT_ACTION_TBL_XLT_CDEI_CMD_DEFAULT 0x0
	/*[field] XLT_CDEI*/
	#define XLT_ACTION_TBL_XLT_CDEI
	#define XLT_ACTION_TBL_XLT_CDEI_OFFSET  42
	#define XLT_ACTION_TBL_XLT_CDEI_LEN     1
	#define XLT_ACTION_TBL_XLT_CDEI_DEFAULT 0x0
	/*[field] VSI_CMD*/
	#define XLT_ACTION_TBL_VSI_CMD
	#define XLT_ACTION_TBL_VSI_CMD_OFFSET  43
	#define XLT_ACTION_TBL_VSI_CMD_LEN     1
	#define XLT_ACTION_TBL_VSI_CMD_DEFAULT 0x0
	/*[field] VSI*/
	#define XLT_ACTION_TBL_VSI
	#define XLT_ACTION_TBL_VSI_OFFSET  44
	#define XLT_ACTION_TBL_VSI_LEN     5
	#define XLT_ACTION_TBL_VSI_DEFAULT 0x0
	/*[field] COUNTER_EN*/
	#define XLT_ACTION_TBL_COUNTER_EN
	#define XLT_ACTION_TBL_COUNTER_EN_OFFSET  49
	#define XLT_ACTION_TBL_COUNTER_EN_LEN     1
	#define XLT_ACTION_TBL_COUNTER_EN_DEFAULT 0x0
	/*[field] COUNTER_ID*/
	#define XLT_ACTION_TBL_COUNTER_ID
	#define XLT_ACTION_TBL_COUNTER_ID_OFFSET  50
	#define XLT_ACTION_TBL_COUNTER_ID_LEN     6
	#define XLT_ACTION_TBL_COUNTER_ID_DEFAULT 0x0

struct xlt_action_tbl {
	a_uint32_t  vid_swap_cmd:1;
	a_uint32_t  xlt_svid_cmd:2;
	a_uint32_t  xlt_svid:12;
	a_uint32_t  xlt_cvid_cmd:2;
	a_uint32_t  xlt_cvid:12;
	a_uint32_t  pcp_swap_cmd:1;
	a_uint32_t  xlt_spcp_cmd:1;
	a_uint32_t  xlt_spcp_0:1;
	a_uint32_t  xlt_spcp_1:2;
	a_uint32_t  xlt_cpcp_cmd:1;
	a_uint32_t  xlt_cpcp:3;
	a_uint32_t  dei_swap_cmd:1;
	a_uint32_t  xlt_sdei_cmd:1;
	a_uint32_t  xlt_sdei:1;
	a_uint32_t  xlt_cdei_cmd:1;
	a_uint32_t  xlt_cdei:1;
	a_uint32_t  vsi_cmd:1;
	a_uint32_t  vsi:5;
	a_uint32_t  counter_en:1;
	a_uint32_t  counter_id:6;
	a_uint32_t  _reserved0:8;
};

union xlt_action_tbl_u {
	a_uint32_t val[2];
	struct xlt_action_tbl bf;
};

/*[table] EG_VLAN_XLT_RULE*/
#define EG_VLAN_XLT_RULE
#define EG_VLAN_XLT_RULE_ADDRESS 0x200
#define EG_VLAN_XLT_RULE_NUM     64
#define EG_VLAN_XLT_RULE_INC     0x8
#define EG_VLAN_XLT_RULE_TYPE    REG_TYPE_RW
#define EG_VLAN_XLT_RULE_DEFAULT 0x0
	/*[field] VALID*/
	#define EG_VLAN_XLT_RULE_VALID
	#define EG_VLAN_XLT_RULE_VALID_OFFSET  0
	#define EG_VLAN_XLT_RULE_VALID_LEN     1
	#define EG_VLAN_XLT_RULE_VALID_DEFAULT 0x0
	/*[field] PORT_BITMAP*/
	#define EG_VLAN_XLT_RULE_PORT_BITMAP
	#define EG_VLAN_XLT_RULE_PORT_BITMAP_OFFSET  1
	#define EG_VLAN_XLT_RULE_PORT_BITMAP_LEN     8
	#define EG_VLAN_XLT_RULE_PORT_BITMAP_DEFAULT 0x0
	/*[field] VSI_INCL*/
	#define EG_VLAN_XLT_RULE_VSI_INCL
	#define EG_VLAN_XLT_RULE_VSI_INCL_OFFSET  9
	#define EG_VLAN_XLT_RULE_VSI_INCL_LEN     1
	#define EG_VLAN_XLT_RULE_VSI_INCL_DEFAULT 0x0
	/*[field] VSI*/
	#define EG_VLAN_XLT_RULE_VSI
	#define EG_VLAN_XLT_RULE_VSI_OFFSET  10
	#define EG_VLAN_XLT_RULE_VSI_LEN     5
	#define EG_VLAN_XLT_RULE_VSI_DEFAULT 0x0
	/*[field] VSI_VALID*/
	#define EG_VLAN_XLT_RULE_VSI_VALID
	#define EG_VLAN_XLT_RULE_VSI_VALID_OFFSET  15
	#define EG_VLAN_XLT_RULE_VSI_VALID_LEN     1
	#define EG_VLAN_XLT_RULE_VSI_VALID_DEFAULT 0x0
	/*[field] SKEY_FMT*/
	#define EG_VLAN_XLT_RULE_SKEY_FMT
	#define EG_VLAN_XLT_RULE_SKEY_FMT_OFFSET  16
	#define EG_VLAN_XLT_RULE_SKEY_FMT_LEN     3
	#define EG_VLAN_XLT_RULE_SKEY_FMT_DEFAULT 0x0
	/*[field] SKEY_VID_INCL*/
	#define EG_VLAN_XLT_RULE_SKEY_VID_INCL
	#define EG_VLAN_XLT_RULE_SKEY_VID_INCL_OFFSET  19
	#define EG_VLAN_XLT_RULE_SKEY_VID_INCL_LEN     1
	#define EG_VLAN_XLT_RULE_SKEY_VID_INCL_DEFAULT 0x0
	/*[field] SKEY_VID*/
	#define EG_VLAN_XLT_RULE_SKEY_VID
	#define EG_VLAN_XLT_RULE_SKEY_VID_OFFSET  20
	#define EG_VLAN_XLT_RULE_SKEY_VID_LEN     12
	#define EG_VLAN_XLT_RULE_SKEY_VID_DEFAULT 0x0
	/*[field] SKEY_PCP_INCL*/
	#define EG_VLAN_XLT_RULE_SKEY_PCP_INCL
	#define EG_VLAN_XLT_RULE_SKEY_PCP_INCL_OFFSET  32
	#define EG_VLAN_XLT_RULE_SKEY_PCP_INCL_LEN     1
	#define EG_VLAN_XLT_RULE_SKEY_PCP_INCL_DEFAULT 0x0
	/*[field] SKEY_PCP*/
	#define EG_VLAN_XLT_RULE_SKEY_PCP
	#define EG_VLAN_XLT_RULE_SKEY_PCP_OFFSET  33
	#define EG_VLAN_XLT_RULE_SKEY_PCP_LEN     3
	#define EG_VLAN_XLT_RULE_SKEY_PCP_DEFAULT 0x0
	/*[field] SKEY_DEI_INCL*/
	#define EG_VLAN_XLT_RULE_SKEY_DEI_INCL
	#define EG_VLAN_XLT_RULE_SKEY_DEI_INCL_OFFSET  36
	#define EG_VLAN_XLT_RULE_SKEY_DEI_INCL_LEN     1
	#define EG_VLAN_XLT_RULE_SKEY_DEI_INCL_DEFAULT 0x0
	/*[field] SKEY_DEI*/
	#define EG_VLAN_XLT_RULE_SKEY_DEI
	#define EG_VLAN_XLT_RULE_SKEY_DEI_OFFSET  37
	#define EG_VLAN_XLT_RULE_SKEY_DEI_LEN     1
	#define EG_VLAN_XLT_RULE_SKEY_DEI_DEFAULT 0x0
	/*[field] CKEY_FMT*/
	#define EG_VLAN_XLT_RULE_CKEY_FMT
	#define EG_VLAN_XLT_RULE_CKEY_FMT_OFFSET  38
	#define EG_VLAN_XLT_RULE_CKEY_FMT_LEN     3
	#define EG_VLAN_XLT_RULE_CKEY_FMT_DEFAULT 0x0
	/*[field] CKEY_VID_INCL*/
	#define EG_VLAN_XLT_RULE_CKEY_VID_INCL
	#define EG_VLAN_XLT_RULE_CKEY_VID_INCL_OFFSET  41
	#define EG_VLAN_XLT_RULE_CKEY_VID_INCL_LEN     1
	#define EG_VLAN_XLT_RULE_CKEY_VID_INCL_DEFAULT 0x0
	/*[field] CKEY_VID*/
	#define EG_VLAN_XLT_RULE_CKEY_VID
	#define EG_VLAN_XLT_RULE_CKEY_VID_OFFSET  42
	#define EG_VLAN_XLT_RULE_CKEY_VID_LEN     12
	#define EG_VLAN_XLT_RULE_CKEY_VID_DEFAULT 0x0
	/*[field] CKEY_PCP_INCL*/
	#define EG_VLAN_XLT_RULE_CKEY_PCP_INCL
	#define EG_VLAN_XLT_RULE_CKEY_PCP_INCL_OFFSET  54
	#define EG_VLAN_XLT_RULE_CKEY_PCP_INCL_LEN     1
	#define EG_VLAN_XLT_RULE_CKEY_PCP_INCL_DEFAULT 0x0
	/*[field] CKEY_PCP*/
	#define EG_VLAN_XLT_RULE_CKEY_PCP
	#define EG_VLAN_XLT_RULE_CKEY_PCP_OFFSET  55
	#define EG_VLAN_XLT_RULE_CKEY_PCP_LEN     3
	#define EG_VLAN_XLT_RULE_CKEY_PCP_DEFAULT 0x0
	/*[field] CKEY_DEI_INCL*/
	#define EG_VLAN_XLT_RULE_CKEY_DEI_INCL
	#define EG_VLAN_XLT_RULE_CKEY_DEI_INCL_OFFSET  58
	#define EG_VLAN_XLT_RULE_CKEY_DEI_INCL_LEN     1
	#define EG_VLAN_XLT_RULE_CKEY_DEI_INCL_DEFAULT 0x0
	/*[field] CKEY_DEI*/
	#define EG_VLAN_XLT_RULE_CKEY_DEI
	#define EG_VLAN_XLT_RULE_CKEY_DEI_OFFSET  59
	#define EG_VLAN_XLT_RULE_CKEY_DEI_LEN     1
	#define EG_VLAN_XLT_RULE_CKEY_DEI_DEFAULT 0x0

struct eg_vlan_xlt_rule {
	a_uint32_t  valid:1;
	a_uint32_t  port_bitmap:8;
	a_uint32_t  vsi_incl:1;
	a_uint32_t  vsi:5;
	a_uint32_t  vsi_valid:1;
	a_uint32_t  skey_fmt:3;
	a_uint32_t  skey_vid_incl:1;
	a_uint32_t  skey_vid:12;
	a_uint32_t  skey_pcp_incl:1;
	a_uint32_t  skey_pcp:3;
	a_uint32_t  skey_dei_incl:1;
	a_uint32_t  skey_dei:1;
	a_uint32_t  ckey_fmt:3;
	a_uint32_t  ckey_vid_incl:1;
	a_uint32_t  ckey_vid:12;
	a_uint32_t  ckey_pcp_incl:1;
	a_uint32_t  ckey_pcp:3;
	a_uint32_t  ckey_dei_incl:1;
	a_uint32_t  ckey_dei:1;
	a_uint32_t  _reserved0:4;
};

union eg_vlan_xlt_rule_u {
	a_uint32_t val[2];
	struct eg_vlan_xlt_rule bf;
};

/*[register] PORT_EG_DEF_VID*/
#define PORT_EG_DEF_VID
#define PORT_EG_DEF_VID_ADDRESS 0x400
#define PORT_EG_DEF_VID_NUM     8
#define PORT_EG_DEF_VID_INC     0x4
#define PORT_EG_DEF_VID_TYPE    REG_TYPE_RW
#define PORT_EG_DEF_VID_DEFAULT 0x0
	/*[field] PORT_DEF_SVID*/
	#define PORT_EG_DEF_VID_PORT_DEF_SVID
	#define PORT_EG_DEF_VID_PORT_DEF_SVID_OFFSET  0
	#define PORT_EG_DEF_VID_PORT_DEF_SVID_LEN     12
	#define PORT_EG_DEF_VID_PORT_DEF_SVID_DEFAULT 0x0
	/*[field] PORT_DEF_SVID_EN*/
	#define PORT_EG_DEF_VID_PORT_DEF_SVID_EN
	#define PORT_EG_DEF_VID_PORT_DEF_SVID_EN_OFFSET  12
	#define PORT_EG_DEF_VID_PORT_DEF_SVID_EN_LEN     1
	#define PORT_EG_DEF_VID_PORT_DEF_SVID_EN_DEFAULT 0x0
	/*[field] PORT_DEF_CVID*/
	#define PORT_EG_DEF_VID_PORT_DEF_CVID
	#define PORT_EG_DEF_VID_PORT_DEF_CVID_OFFSET  16
	#define PORT_EG_DEF_VID_PORT_DEF_CVID_LEN     12
	#define PORT_EG_DEF_VID_PORT_DEF_CVID_DEFAULT 0x0
	/*[field] PORT_DEF_CVID_EN*/
	#define PORT_EG_DEF_VID_PORT_DEF_CVID_EN
	#define PORT_EG_DEF_VID_PORT_DEF_CVID_EN_OFFSET  28
	#define PORT_EG_DEF_VID_PORT_DEF_CVID_EN_LEN     1
	#define PORT_EG_DEF_VID_PORT_DEF_CVID_EN_DEFAULT 0x0

struct port_eg_def_vid {
	a_uint32_t  port_def_svid:12;
	a_uint32_t  port_def_svid_en:1;
	a_uint32_t  _reserved0:3;
	a_uint32_t  port_def_cvid:12;
	a_uint32_t  port_def_cvid_en:1;
	a_uint32_t  _reserved1:3;
};

union port_eg_def_vid_u {
	a_uint32_t val;
	struct port_eg_def_vid bf;
};

/*[register] PORT_EG_VLAN*/
#define PORT_EG_VLAN
#define PORT_EG_VLAN_ADDRESS 0x420
#define PORT_EG_VLAN_NUM     8
#define PORT_EG_VLAN_INC     0x4
#define PORT_EG_VLAN_TYPE    REG_TYPE_RW
#define PORT_EG_VLAN_DEFAULT 0x14
	/*[field] PORT_VLAN_TYPE*/
	#define PORT_EG_VLAN_PORT_VLAN_TYPE
	#define PORT_EG_VLAN_PORT_VLAN_TYPE_OFFSET  0
	#define PORT_EG_VLAN_PORT_VLAN_TYPE_LEN     1
	#define PORT_EG_VLAN_PORT_VLAN_TYPE_DEFAULT 0x0
	/*[field] PORT_EG_VLAN_CTAG_MODE*/
	#define PORT_EG_VLAN_PORT_EG_VLAN_CTAG_MODE
	#define PORT_EG_VLAN_PORT_EG_VLAN_CTAG_MODE_OFFSET  1
	#define PORT_EG_VLAN_PORT_EG_VLAN_CTAG_MODE_LEN     2
	#define PORT_EG_VLAN_PORT_EG_VLAN_CTAG_MODE_DEFAULT 0x2
	/*[field] PORT_EG_VLAN_STAG_MODE*/
	#define PORT_EG_VLAN_PORT_EG_VLAN_STAG_MODE
	#define PORT_EG_VLAN_PORT_EG_VLAN_STAG_MODE_OFFSET  3
	#define PORT_EG_VLAN_PORT_EG_VLAN_STAG_MODE_LEN     2
	#define PORT_EG_VLAN_PORT_EG_VLAN_STAG_MODE_DEFAULT 0x2
	/*[field] VSI_TAG_MODE_EN*/
	#define PORT_EG_VLAN_VSI_TAG_MODE_EN
	#define PORT_EG_VLAN_VSI_TAG_MODE_EN_OFFSET  5
	#define PORT_EG_VLAN_VSI_TAG_MODE_EN_LEN     1
	#define PORT_EG_VLAN_VSI_TAG_MODE_EN_DEFAULT 0x0
	/*[field] PORT_EG_PCP_PROP_CMD*/
	#define PORT_EG_VLAN_PORT_EG_PCP_PROP_CMD
	#define PORT_EG_VLAN_PORT_EG_PCP_PROP_CMD_OFFSET  6
	#define PORT_EG_VLAN_PORT_EG_PCP_PROP_CMD_LEN     1
	#define PORT_EG_VLAN_PORT_EG_PCP_PROP_CMD_DEFAULT 0x0
	/*[field] PORT_EG_DEI_PROP_CMD*/
	#define PORT_EG_VLAN_PORT_EG_DEI_PROP_CMD
	#define PORT_EG_VLAN_PORT_EG_DEI_PROP_CMD_OFFSET  7
	#define PORT_EG_VLAN_PORT_EG_DEI_PROP_CMD_LEN     1
	#define PORT_EG_VLAN_PORT_EG_DEI_PROP_CMD_DEFAULT 0x0
	/*[field] TX_COUNTING_EN*/
	#define PORT_EG_VLAN_TX_COUNTING_EN
	#define PORT_EG_VLAN_TX_COUNTING_EN_OFFSET  8
	#define PORT_EG_VLAN_TX_COUNTING_EN_LEN     1
	#define PORT_EG_VLAN_TX_COUNTING_EN_DEFAULT 0x0

struct port_eg_vlan {
	a_uint32_t  port_vlan_type:1;
	a_uint32_t  port_eg_vlan_ctag_mode:2;
	a_uint32_t  port_eg_vlan_stag_mode:2;
	a_uint32_t  vsi_tag_mode_en:1;
	a_uint32_t  port_eg_pcp_prop_cmd:1;
	a_uint32_t  port_eg_dei_prop_cmd:1;
	a_uint32_t  tx_counting_en:1;
	a_uint32_t  _reserved0:23;
};

union port_eg_vlan_u {
	a_uint32_t val;
	struct port_eg_vlan bf;
};

/*[register] EG_VLAN_TPID*/
#define EG_VLAN_TPID
#define EG_VLAN_TPID_ADDRESS 0x440
#define EG_VLAN_TPID_NUM     1
#define EG_VLAN_TPID_INC     0x4
#define EG_VLAN_TPID_TYPE    REG_TYPE_RW
#define EG_VLAN_TPID_DEFAULT 0x810088a8
	/*[field] STPID*/
	#define EG_VLAN_TPID_STPID
	#define EG_VLAN_TPID_STPID_OFFSET  0
	#define EG_VLAN_TPID_STPID_LEN     16
	#define EG_VLAN_TPID_STPID_DEFAULT 0x88a8
	/*[field] CTPID*/
	#define EG_VLAN_TPID_CTPID
	#define EG_VLAN_TPID_CTPID_OFFSET  16
	#define EG_VLAN_TPID_CTPID_LEN     16
	#define EG_VLAN_TPID_CTPID_DEFAULT 0x8100

struct eg_vlan_tpid {
	a_uint32_t  stpid:16;
	a_uint32_t  ctpid:16;
};

union eg_vlan_tpid_u {
	a_uint32_t val;
	struct eg_vlan_tpid bf;
};

/*[register] EG_BRIDGE_CONFIG*/
#define EG_BRIDGE_CONFIG
#define EG_BRIDGE_CONFIG_ADDRESS 0x6000
#define EG_BRIDGE_CONFIG_NUM     1
#define EG_BRIDGE_CONFIG_INC     0x4
#define EG_BRIDGE_CONFIG_TYPE    REG_TYPE_RW
#define EG_BRIDGE_CONFIG_DEFAULT 0x0
	/*[field] BRIDGE_TYPE*/
	#define EG_BRIDGE_CONFIG_BRIDGE_TYPE
	#define EG_BRIDGE_CONFIG_BRIDGE_TYPE_OFFSET  0
	#define EG_BRIDGE_CONFIG_BRIDGE_TYPE_LEN     1
	#define EG_BRIDGE_CONFIG_BRIDGE_TYPE_DEFAULT 0x0

struct eg_bridge_config {
	a_uint32_t  bridge_type:1;
	a_uint32_t  _reserved0:31;
};

union eg_bridge_config_u {
	a_uint32_t val;
	struct eg_bridge_config bf;
};

/*[table] EG_VLAN_XLT_ACTION*/
#define EG_VLAN_XLT_ACTION
#define EG_VLAN_XLT_ACTION_ADDRESS 0xd000
#define EG_VLAN_XLT_ACTION_NUM     64
#define EG_VLAN_XLT_ACTION_INC     0x8
#define EG_VLAN_XLT_ACTION_TYPE    REG_TYPE_RW
#define EG_VLAN_XLT_ACTION_DEFAULT 0x0
	/*[field] VID_SWAP_CMD*/
	#define EG_VLAN_XLT_ACTION_VID_SWAP_CMD
	#define EG_VLAN_XLT_ACTION_VID_SWAP_CMD_OFFSET  0
	#define EG_VLAN_XLT_ACTION_VID_SWAP_CMD_LEN     1
	#define EG_VLAN_XLT_ACTION_VID_SWAP_CMD_DEFAULT 0x0
	/*[field] XLT_SVID_CMD*/
	#define EG_VLAN_XLT_ACTION_XLT_SVID_CMD
	#define EG_VLAN_XLT_ACTION_XLT_SVID_CMD_OFFSET  1
	#define EG_VLAN_XLT_ACTION_XLT_SVID_CMD_LEN     2
	#define EG_VLAN_XLT_ACTION_XLT_SVID_CMD_DEFAULT 0x0
	/*[field] XLT_SVID*/
	#define EG_VLAN_XLT_ACTION_XLT_SVID
	#define EG_VLAN_XLT_ACTION_XLT_SVID_OFFSET  3
	#define EG_VLAN_XLT_ACTION_XLT_SVID_LEN     12
	#define EG_VLAN_XLT_ACTION_XLT_SVID_DEFAULT 0x0
	/*[field] XLT_CVID_CMD*/
	#define EG_VLAN_XLT_ACTION_XLT_CVID_CMD
	#define EG_VLAN_XLT_ACTION_XLT_CVID_CMD_OFFSET  15
	#define EG_VLAN_XLT_ACTION_XLT_CVID_CMD_LEN     2
	#define EG_VLAN_XLT_ACTION_XLT_CVID_CMD_DEFAULT 0x0
	/*[field] XLT_CVID*/
	#define EG_VLAN_XLT_ACTION_XLT_CVID
	#define EG_VLAN_XLT_ACTION_XLT_CVID_OFFSET  17
	#define EG_VLAN_XLT_ACTION_XLT_CVID_LEN     12
	#define EG_VLAN_XLT_ACTION_XLT_CVID_DEFAULT 0x0
	/*[field] PCP_SWAP_CMD*/
	#define EG_VLAN_XLT_ACTION_PCP_SWAP_CMD
	#define EG_VLAN_XLT_ACTION_PCP_SWAP_CMD_OFFSET  29
	#define EG_VLAN_XLT_ACTION_PCP_SWAP_CMD_LEN     1
	#define EG_VLAN_XLT_ACTION_PCP_SWAP_CMD_DEFAULT 0x0
	/*[field] XLT_SPCP_CMD*/
	#define EG_VLAN_XLT_ACTION_XLT_SPCP_CMD
	#define EG_VLAN_XLT_ACTION_XLT_SPCP_CMD_OFFSET  30
	#define EG_VLAN_XLT_ACTION_XLT_SPCP_CMD_LEN     1
	#define EG_VLAN_XLT_ACTION_XLT_SPCP_CMD_DEFAULT 0x0
	/*[field] XLT_SPCP*/
	#define EG_VLAN_XLT_ACTION_XLT_SPCP
	#define EG_VLAN_XLT_ACTION_XLT_SPCP_OFFSET  31
	#define EG_VLAN_XLT_ACTION_XLT_SPCP_LEN     3
	#define EG_VLAN_XLT_ACTION_XLT_SPCP_DEFAULT 0x0
	/*[field] XLT_CPCP_CMD*/
	#define EG_VLAN_XLT_ACTION_XLT_CPCP_CMD
	#define EG_VLAN_XLT_ACTION_XLT_CPCP_CMD_OFFSET  34
	#define EG_VLAN_XLT_ACTION_XLT_CPCP_CMD_LEN     1
	#define EG_VLAN_XLT_ACTION_XLT_CPCP_CMD_DEFAULT 0x0
	/*[field] XLT_CPCP*/
	#define EG_VLAN_XLT_ACTION_XLT_CPCP
	#define EG_VLAN_XLT_ACTION_XLT_CPCP_OFFSET  35
	#define EG_VLAN_XLT_ACTION_XLT_CPCP_LEN     3
	#define EG_VLAN_XLT_ACTION_XLT_CPCP_DEFAULT 0x0
	/*[field] DEI_SWAP_CMD*/
	#define EG_VLAN_XLT_ACTION_DEI_SWAP_CMD
	#define EG_VLAN_XLT_ACTION_DEI_SWAP_CMD_OFFSET  38
	#define EG_VLAN_XLT_ACTION_DEI_SWAP_CMD_LEN     1
	#define EG_VLAN_XLT_ACTION_DEI_SWAP_CMD_DEFAULT 0x0
	/*[field] XLT_SDEI_CMD*/
	#define EG_VLAN_XLT_ACTION_XLT_SDEI_CMD
	#define EG_VLAN_XLT_ACTION_XLT_SDEI_CMD_OFFSET  39
	#define EG_VLAN_XLT_ACTION_XLT_SDEI_CMD_LEN     1
	#define EG_VLAN_XLT_ACTION_XLT_SDEI_CMD_DEFAULT 0x0
	/*[field] XLT_SDEI*/
	#define EG_VLAN_XLT_ACTION_XLT_SDEI
	#define EG_VLAN_XLT_ACTION_XLT_SDEI_OFFSET  40
	#define EG_VLAN_XLT_ACTION_XLT_SDEI_LEN     1
	#define EG_VLAN_XLT_ACTION_XLT_SDEI_DEFAULT 0x0
	/*[field] XLT_CDEI_CMD*/
	#define EG_VLAN_XLT_ACTION_XLT_CDEI_CMD
	#define EG_VLAN_XLT_ACTION_XLT_CDEI_CMD_OFFSET  41
	#define EG_VLAN_XLT_ACTION_XLT_CDEI_CMD_LEN     1
	#define EG_VLAN_XLT_ACTION_XLT_CDEI_CMD_DEFAULT 0x0
	/*[field] XLT_CDEI*/
	#define EG_VLAN_XLT_ACTION_XLT_CDEI
	#define EG_VLAN_XLT_ACTION_XLT_CDEI_OFFSET  42
	#define EG_VLAN_XLT_ACTION_XLT_CDEI_LEN     1
	#define EG_VLAN_XLT_ACTION_XLT_CDEI_DEFAULT 0x0
	/*[field] COUNTER_EN*/
	#define EG_VLAN_XLT_ACTION_COUNTER_EN
	#define EG_VLAN_XLT_ACTION_COUNTER_EN_OFFSET  43
	#define EG_VLAN_XLT_ACTION_COUNTER_EN_LEN     1
	#define EG_VLAN_XLT_ACTION_COUNTER_EN_DEFAULT 0x0
	/*[field] COUNTER_ID*/
	#define EG_VLAN_XLT_ACTION_COUNTER_ID
	#define EG_VLAN_XLT_ACTION_COUNTER_ID_OFFSET  44
	#define EG_VLAN_XLT_ACTION_COUNTER_ID_LEN     6
	#define EG_VLAN_XLT_ACTION_COUNTER_ID_DEFAULT 0x0

struct eg_vlan_xlt_action {
	a_uint32_t  vid_swap_cmd:1;
	a_uint32_t  xlt_svid_cmd:2;
	a_uint32_t  xlt_svid:12;
	a_uint32_t  xlt_cvid_cmd:2;
	a_uint32_t  xlt_cvid:12;
	a_uint32_t  pcp_swap_cmd:1;
	a_uint32_t  xlt_spcp_cmd:1;
	a_uint32_t  xlt_spcp_0:1;
	a_uint32_t  xlt_spcp_1:2;
	a_uint32_t  xlt_cpcp_cmd:1;
	a_uint32_t  xlt_cpcp:3;
	a_uint32_t  dei_swap_cmd:1;
	a_uint32_t  xlt_sdei_cmd:1;
	a_uint32_t  xlt_sdei:1;
	a_uint32_t  xlt_cdei_cmd:1;
	a_uint32_t  xlt_cdei:1;
	a_uint32_t  counter_en:1;
	a_uint32_t  counter_id:6;
	a_uint32_t  _reserved0:14;
};

union eg_vlan_xlt_action_u {
	a_uint32_t val[2];
	struct eg_vlan_xlt_action bf;
};


#endif
