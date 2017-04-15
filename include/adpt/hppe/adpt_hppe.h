/*
 * Copyright (c) 2016-2017, The Linux Foundation. All rights reserved.
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
#ifndef _ADPT_HPPE_H_
#define _ADPT_HPPE_H_

#ifdef __cplusplus
extern "C" {
#endif                          /* __cplusplus */

void adpt_hppe_fdb_func_bitmap_init(a_uint32_t dev_id);
sw_error_t adpt_hppe_fdb_init(a_uint32_t dev_id);
void adpt_hppe_portvlan_func_bitmap_init(a_uint32_t dev_id);
sw_error_t adpt_hppe_portvlan_init(a_uint32_t dev_id);
void adpt_hppe_ctrlpkt_func_bitmap_init(a_uint32_t dev_id);
sw_error_t adpt_hppe_ctrlpkt_init(a_uint32_t dev_id);
void adpt_hppe_servcode_func_bitmap_init(a_uint32_t dev_id);
sw_error_t adpt_hppe_servcode_init(a_uint32_t dev_id);
void adpt_hppe_rss_hash_func_bitmap_init(a_uint32_t dev_id);
sw_error_t adpt_hppe_rss_hash_init(a_uint32_t dev_id);
void adpt_hppe_mib_func_bitmap_init(a_uint32_t dev_id);
sw_error_t adpt_hppe_mib_init(a_uint32_t dev_id);
void adpt_hppe_stp_func_bitmap_init(a_uint32_t dev_id);
sw_error_t adpt_hppe_stp_init(a_uint32_t dev_id);
void adpt_hppe_vsi_func_bitmap_init(a_uint32_t dev_id);
sw_error_t adpt_hppe_vsi_init(a_uint32_t dev_id);
sw_error_t adpt_hppe_port_ctrl_init(a_uint32_t dev_id);
sw_error_t adpt_hppe_misc_init(a_uint32_t dev_id);

void adpt_hppe_mirror_func_bitmap_init(a_uint32_t dev_id);
sw_error_t adpt_hppe_mirror_init(a_uint32_t dev_id);
void adpt_hppe_trunk_func_bitmap_init(a_uint32_t dev_id);
sw_error_t adpt_hppe_trunk_init(a_uint32_t dev_id);
void adpt_hppe_ip_func_bitmap_init(a_uint32_t dev_id);
sw_error_t adpt_hppe_ip_init(a_uint32_t dev_id);
void adpt_hppe_qm_func_bitmap_init(a_uint32_t dev_id);
sw_error_t adpt_hppe_qm_init(a_uint32_t dev_id);
void adpt_hppe_flow_func_bitmap_init(a_uint32_t dev_id);
sw_error_t adpt_hppe_flow_init(a_uint32_t dev_id);

void adpt_hppe_pppoe_func_bitmap_init(a_uint32_t dev_id);
sw_error_t adpt_hppe_pppoe_init(a_uint32_t dev_id);
void adpt_hppe_sec_func_bitmap_init(a_uint32_t dev_id);
sw_error_t adpt_hppe_sec_init(a_uint32_t dev_id);

void adpt_hppe_acl_func_bitmap_init(a_uint32_t dev_id);
sw_error_t adpt_hppe_acl_init(a_uint32_t dev_id);
void adpt_hppe_qos_func_bitmap_init(a_uint32_t dev_id);
sw_error_t adpt_hppe_qos_init(a_uint32_t dev_id);
void adpt_hppe_bm_func_bitmap_init(a_uint32_t dev_id);
sw_error_t adpt_hppe_bm_init(a_uint32_t dev_id);

sw_error_t adpt_hppe_shaper_init(a_uint32_t dev_id);

void adpt_hppe_port_ctrl_func_bitmap_init(a_uint32_t dev_id);

void adpt_hppe_shaper_func_bitmap_init(a_uint32_t dev_id);

sw_error_t adpt_hppe_policer_init(a_uint32_t dev_id);

void adpt_hppe_policer_func_bitmap_init(a_uint32_t dev_id);

sw_error_t adpt_hppe_uniphy_init(a_uint32_t dev_id);

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif
