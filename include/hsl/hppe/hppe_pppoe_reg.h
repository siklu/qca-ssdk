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
#ifndef HPPE_PPPOE_REG_H
#define HPPE_PPPOE_REG_H

/*[register] PPPOE_SESSION*/
#define PPPOE_SESSION
#define PPPOE_SESSION_ADDRESS 0x348
#define PPPOE_SESSION_NUM     4
#define PPPOE_SESSION_INC     0x4
#define PPPOE_SESSION_TYPE    REG_TYPE_RW
#define PPPOE_SESSION_DEFAULT 0x0
	/*[field] SESSION_ID*/
	#define PPPOE_SESSION_SESSION_ID
	#define PPPOE_SESSION_SESSION_ID_OFFSET  0
	#define PPPOE_SESSION_SESSION_ID_LEN     16
	#define PPPOE_SESSION_SESSION_ID_DEFAULT 0x0
	/*[field] PORT_BITMAP*/
	#define PPPOE_SESSION_PORT_BITMAP
	#define PPPOE_SESSION_PORT_BITMAP_OFFSET  16
	#define PPPOE_SESSION_PORT_BITMAP_LEN     8
	#define PPPOE_SESSION_PORT_BITMAP_DEFAULT 0x0
	/*[field] L3_IF_INDEX*/
	#define PPPOE_SESSION_L3_IF_INDEX
	#define PPPOE_SESSION_L3_IF_INDEX_OFFSET  24
	#define PPPOE_SESSION_L3_IF_INDEX_LEN     8
	#define PPPOE_SESSION_L3_IF_INDEX_DEFAULT 0x0

struct pppoe_session {
	a_uint32_t  session_id:16;
	a_uint32_t  port_bitmap:8;
	a_uint32_t  l3_if_index:8;
};

union pppoe_session_u {
	a_uint32_t val;
	struct pppoe_session bf;
};

/*[register] PPPOE_SESSION_EXT*/
#define PPPOE_SESSION_EXT
#define PPPOE_SESSION_EXT_ADDRESS 0x358
#define PPPOE_SESSION_EXT_NUM     4
#define PPPOE_SESSION_EXT_INC     0x4
#define PPPOE_SESSION_EXT_TYPE    REG_TYPE_RW
#define PPPOE_SESSION_EXT_DEFAULT 0x0
	/*[field] L3_IF_VALID*/
	#define PPPOE_SESSION_EXT_L3_IF_VALID
	#define PPPOE_SESSION_EXT_L3_IF_VALID_OFFSET  0
	#define PPPOE_SESSION_EXT_L3_IF_VALID_LEN     1
	#define PPPOE_SESSION_EXT_L3_IF_VALID_DEFAULT 0x0
	/*[field] MC_VALID*/
	#define PPPOE_SESSION_EXT_MC_VALID
	#define PPPOE_SESSION_EXT_MC_VALID_OFFSET  1
	#define PPPOE_SESSION_EXT_MC_VALID_LEN     1
	#define PPPOE_SESSION_EXT_MC_VALID_DEFAULT 0x0
	/*[field] UC_VALID*/
	#define PPPOE_SESSION_EXT_UC_VALID
	#define PPPOE_SESSION_EXT_UC_VALID_OFFSET  2
	#define PPPOE_SESSION_EXT_UC_VALID_LEN     1
	#define PPPOE_SESSION_EXT_UC_VALID_DEFAULT 0x0

struct pppoe_session_ext {
	a_uint32_t  l3_if_valid:1;
	a_uint32_t  mc_valid:1;
	a_uint32_t  uc_valid:1;
	a_uint32_t  _reserved0:29;
};

union pppoe_session_ext_u {
	a_uint32_t val;
	struct pppoe_session_ext bf;
};

#endif
