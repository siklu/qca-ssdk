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
#ifndef _HPPE_SEC_REG_H_
#define _HPPE_SEC_REG_H_


/*[register] L3_EXCEPTION_CMD*/
#define L3_EXCEPTION_CMD
#define L3_EXCEPTION_CMD_ADDRESS 0x544
#define L3_EXCEPTION_CMD_NUM     72
#define L3_EXCEPTION_CMD_INC     0x4
#define L3_EXCEPTION_CMD_TYPE    REG_TYPE_RW
#define L3_EXCEPTION_CMD_DEFAULT 0x0
	/*[field] L3_EXCEP_CMD*/
	#define L3_EXCEPTION_CMD_L3_EXCEP_CMD
	#define L3_EXCEPTION_CMD_L3_EXCEP_CMD_OFFSET  0
	#define L3_EXCEPTION_CMD_L3_EXCEP_CMD_LEN     2
	#define L3_EXCEPTION_CMD_L3_EXCEP_CMD_DEFAULT 0x0
	/*[field] DE_ACCE*/
	#define L3_EXCEPTION_CMD_DE_ACCE
	#define L3_EXCEPTION_CMD_DE_ACCE_OFFSET  2
	#define L3_EXCEPTION_CMD_DE_ACCE_LEN     1
	#define L3_EXCEPTION_CMD_DE_ACCE_DEFAULT 0x0

struct l3_exception_cmd {
	a_uint32_t  l3_excep_cmd:2;
	a_uint32_t  de_acce:1;
	a_uint32_t  _reserved0:29;
};

union l3_exception_cmd_u {
	a_uint32_t val;
	struct l3_exception_cmd bf;
};

/*[register] L3_EXP_L3_ONLY_CTRL*/
#define L3_EXP_L3_ONLY_CTRL
#define L3_EXP_L3_ONLY_CTRL_ADDRESS 0x664
#define L3_EXP_L3_ONLY_CTRL_NUM     72
#define L3_EXP_L3_ONLY_CTRL_INC     0x4
#define L3_EXP_L3_ONLY_CTRL_TYPE    REG_TYPE_RW
#define L3_EXP_L3_ONLY_CTRL_DEFAULT 0x0
	/*[field] EXCEP_EN*/
	#define L3_EXP_L3_ONLY_CTRL_EXCEP_EN
	#define L3_EXP_L3_ONLY_CTRL_EXCEP_EN_OFFSET  0
	#define L3_EXP_L3_ONLY_CTRL_EXCEP_EN_LEN     1
	#define L3_EXP_L3_ONLY_CTRL_EXCEP_EN_DEFAULT 0x0

struct l3_exp_l3_only_ctrl {
	a_uint32_t  excep_en:1;
	a_uint32_t  _reserved0:31;
};

union l3_exp_l3_only_ctrl_u {
	a_uint32_t val;
	struct l3_exp_l3_only_ctrl bf;
};

/*[register] L3_EXP_L2_ONLY_CTRL*/
#define L3_EXP_L2_ONLY_CTRL
#define L3_EXP_L2_ONLY_CTRL_ADDRESS 0x784
#define L3_EXP_L2_ONLY_CTRL_NUM     72
#define L3_EXP_L2_ONLY_CTRL_INC     0x4
#define L3_EXP_L2_ONLY_CTRL_TYPE    REG_TYPE_RW
#define L3_EXP_L2_ONLY_CTRL_DEFAULT 0x0
	/*[field] EXCEP_EN*/
	#define L3_EXP_L2_ONLY_CTRL_EXCEP_EN
	#define L3_EXP_L2_ONLY_CTRL_EXCEP_EN_OFFSET  0
	#define L3_EXP_L2_ONLY_CTRL_EXCEP_EN_LEN     1
	#define L3_EXP_L2_ONLY_CTRL_EXCEP_EN_DEFAULT 0x0

struct l3_exp_l2_only_ctrl {
	a_uint32_t  excep_en:1;
	a_uint32_t  _reserved0:31;
};

union l3_exp_l2_only_ctrl_u {
	a_uint32_t val;
	struct l3_exp_l2_only_ctrl bf;
};

/*[register] L3_EXP_L2_FLOW_CTRL*/
#define L3_EXP_L2_FLOW_CTRL
#define L3_EXP_L2_FLOW_CTRL_ADDRESS 0x8a4
#define L3_EXP_L2_FLOW_CTRL_NUM     72
#define L3_EXP_L2_FLOW_CTRL_INC     0x4
#define L3_EXP_L2_FLOW_CTRL_TYPE    REG_TYPE_RW
#define L3_EXP_L2_FLOW_CTRL_DEFAULT 0x0
	/*[field] EXCEP_EN*/
	#define L3_EXP_L2_FLOW_CTRL_EXCEP_EN
	#define L3_EXP_L2_FLOW_CTRL_EXCEP_EN_OFFSET  0
	#define L3_EXP_L2_FLOW_CTRL_EXCEP_EN_LEN     1
	#define L3_EXP_L2_FLOW_CTRL_EXCEP_EN_DEFAULT 0x0

struct l3_exp_l2_flow_ctrl {
	a_uint32_t  excep_en:1;
	a_uint32_t  _reserved0:31;
};

union l3_exp_l2_flow_ctrl_u {
	a_uint32_t val;
	struct l3_exp_l2_flow_ctrl bf;
};

/*[register] L3_EXP_L3_FLOW_CTRL*/
#define L3_EXP_L3_FLOW_CTRL
#define L3_EXP_L3_FLOW_CTRL_ADDRESS 0x9c4
#define L3_EXP_L3_FLOW_CTRL_NUM     72
#define L3_EXP_L3_FLOW_CTRL_INC     0x4
#define L3_EXP_L3_FLOW_CTRL_TYPE    REG_TYPE_RW
#define L3_EXP_L3_FLOW_CTRL_DEFAULT 0x0
	/*[field] EXCEP_EN*/
	#define L3_EXP_L3_FLOW_CTRL_EXCEP_EN
	#define L3_EXP_L3_FLOW_CTRL_EXCEP_EN_OFFSET  0
	#define L3_EXP_L3_FLOW_CTRL_EXCEP_EN_LEN     1
	#define L3_EXP_L3_FLOW_CTRL_EXCEP_EN_DEFAULT 0x0

struct l3_exp_l3_flow_ctrl {
	a_uint32_t  excep_en:1;
	a_uint32_t  _reserved0:31;
};

union l3_exp_l3_flow_ctrl_u {
	a_uint32_t val;
	struct l3_exp_l3_flow_ctrl bf;
};

/*[register] L3_EXP_MULTICAST_CTRL*/
#define L3_EXP_MULTICAST_CTRL
#define L3_EXP_MULTICAST_CTRL_ADDRESS 0xae4
#define L3_EXP_MULTICAST_CTRL_NUM     72
#define L3_EXP_MULTICAST_CTRL_INC     0x4
#define L3_EXP_MULTICAST_CTRL_TYPE    REG_TYPE_RW
#define L3_EXP_MULTICAST_CTRL_DEFAULT 0x0
	/*[field] EXCEP_EN*/
	#define L3_EXP_MULTICAST_CTRL_EXCEP_EN
	#define L3_EXP_MULTICAST_CTRL_EXCEP_EN_OFFSET  0
	#define L3_EXP_MULTICAST_CTRL_EXCEP_EN_LEN     1
	#define L3_EXP_MULTICAST_CTRL_EXCEP_EN_DEFAULT 0x0

struct l3_exp_multicast_ctrl {
	a_uint32_t  excep_en:1;
	a_uint32_t  _reserved0:31;
};

union l3_exp_multicast_ctrl_u {
	a_uint32_t val;
	struct l3_exp_multicast_ctrl bf;
};


#endif
