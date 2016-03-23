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
#ifndef HPPE_RSS_REG_H
#define HPPE_RSS_REG_H

/*[register] RSS_HASH_MASK_REG*/
#define RSS_HASH_MASK_REG
#define RSS_HASH_MASK_REG_ADDRESS 0x4318
#define RSS_HASH_MASK_REG_NUM     1
#define RSS_HASH_MASK_REG_INC     0x4
#define RSS_HASH_MASK_REG_TYPE    REG_TYPE_RW
#define RSS_HASH_MASK_REG_DEFAULT 0x0
	/*[field] MASK*/
	#define RSS_HASH_MASK_REG_MASK
	#define RSS_HASH_MASK_REG_MASK_OFFSET  0
	#define RSS_HASH_MASK_REG_MASK_LEN     21
	#define RSS_HASH_MASK_REG_MASK_DEFAULT 0x0

struct rss_hash_mask_reg {
	a_uint32_t  mask:21;
	a_uint32_t  _reserved0:11;
};

union rss_hash_mask_reg_u {
	a_uint32_t val;
	struct rss_hash_mask_reg bf;
};

/*[register] RSS_HASH_SEED_REG*/
#define RSS_HASH_SEED_REG
#define RSS_HASH_SEED_REG_ADDRESS 0x431c
#define RSS_HASH_SEED_REG_NUM     1
#define RSS_HASH_SEED_REG_INC     0x4
#define RSS_HASH_SEED_REG_TYPE    REG_TYPE_RW
#define RSS_HASH_SEED_REG_DEFAULT 0x0
	/*[field] SEED*/
	#define RSS_HASH_SEED_REG_SEED
	#define RSS_HASH_SEED_REG_SEED_OFFSET  0
	#define RSS_HASH_SEED_REG_SEED_LEN     32
	#define RSS_HASH_SEED_REG_SEED_DEFAULT 0x0

struct rss_hash_seed_reg {
	a_uint32_t  seed:32;
};

union rss_hash_seed_reg_u {
	a_uint32_t val;
	struct rss_hash_seed_reg bf;
};

/*[register] RSS_HASH_MIX_REG*/
#define RSS_HASH_MIX_REG
#define RSS_HASH_MIX_REG_ADDRESS 0x4320
#define RSS_HASH_MIX_REG_NUM     11
#define RSS_HASH_MIX_REG_INC     0x4
#define RSS_HASH_MIX_REG_TYPE    REG_TYPE_RW
#define RSS_HASH_MIX_REG_DEFAULT 0x0
	/*[field] HASH_MIX*/
	#define RSS_HASH_MIX_REG_HASH_MIX
	#define RSS_HASH_MIX_REG_HASH_MIX_OFFSET  0
	#define RSS_HASH_MIX_REG_HASH_MIX_LEN     5
	#define RSS_HASH_MIX_REG_HASH_MIX_DEFAULT 0x0

struct rss_hash_mix_reg {
	a_uint32_t  hash_mix:5;
	a_uint32_t  _reserved0:27;
};

union rss_hash_mix_reg_u {
	a_uint32_t val;
	struct rss_hash_mix_reg bf;
};

/*[register] RSS_HASH_FIN_REG*/
#define RSS_HASH_FIN_REG
#define RSS_HASH_FIN_REG_ADDRESS 0x4350
#define RSS_HASH_FIN_REG_NUM     5
#define RSS_HASH_FIN_REG_INC     0x4
#define RSS_HASH_FIN_REG_TYPE    REG_TYPE_RW
#define RSS_HASH_FIN_REG_DEFAULT 0x0
	/*[field] FIN_INNER*/
	#define RSS_HASH_FIN_REG_FIN_INNER
	#define RSS_HASH_FIN_REG_FIN_INNER_OFFSET  0
	#define RSS_HASH_FIN_REG_FIN_INNER_LEN     5
	#define RSS_HASH_FIN_REG_FIN_INNER_DEFAULT 0x0
	/*[field] FIN_OUTER*/
	#define RSS_HASH_FIN_REG_FIN_OUTER
	#define RSS_HASH_FIN_REG_FIN_OUTER_OFFSET  5
	#define RSS_HASH_FIN_REG_FIN_OUTER_LEN     5
	#define RSS_HASH_FIN_REG_FIN_OUTER_DEFAULT 0x0

struct rss_hash_fin_reg {
	a_uint32_t  fin_inner:5;
	a_uint32_t  fin_outer:5;
	a_uint32_t  _reserved0:22;
};

union rss_hash_fin_reg_u {
	a_uint32_t val;
	struct rss_hash_fin_reg bf;
};

#endif
