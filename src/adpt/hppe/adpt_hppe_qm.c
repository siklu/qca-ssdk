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
#include "sw.h"
#include "fal_qm.h"
#include "hppe_qm_reg.h"
#include "hppe_qm.h"
#include "adpt.h"

#define SERVICE_CODE_QUEUE_OFFSET   2048
#define CPU_CODE_QUEUE_OFFSET         1024
#define VP_PORT_QUEUE_OFFSET            0

sw_error_t
adpt_hppe_mcast_queue_map_set(
		a_uint32_t dev_id,
		fal_mcast_queue_map_t *queue_map)
{
	union mcast_queue_map_tbl_u mcast_queue_map_tbl;

	memset(&mcast_queue_map_tbl, 0, sizeof(mcast_queue_map_tbl));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(queue_map);

	mcast_queue_map_tbl.bf.class = queue_map->class;
	return hppe_mcast_queue_map_tbl_set(dev_id, queue_map->cpu_code, &mcast_queue_map_tbl);
}

sw_error_t
adpt_hppe_mcast_queue_map_get(
		a_uint32_t dev_id,
		fal_mcast_queue_map_t *queue_map)
{
	sw_error_t rv = SW_OK;
	union mcast_queue_map_tbl_u mcast_queue_map_tbl;

	memset(&mcast_queue_map_tbl, 0, sizeof(mcast_queue_map_tbl));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(queue_map);

	rv = hppe_mcast_queue_map_tbl_get(dev_id, queue_map->cpu_code, &mcast_queue_map_tbl);
	if( rv != SW_OK )
		return rv;

	queue_map->class = mcast_queue_map_tbl.bf.class;
	return rv;
}

sw_error_t
adpt_hppe_ucast_priority_map_get(
		a_uint32_t dev_id,
		fal_ucast_priority_map_t *priority_map)
{
	sw_error_t rv = SW_OK;
	union ucast_priority_map_tbl_u ucast_priority_map_tbl;
	a_uint32_t index = 0;

	memset(&ucast_priority_map_tbl, 0, sizeof(ucast_priority_map_tbl));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(priority_map);

	index = priority_map->profile << 4 | priority_map->priority;
	rv = hppe_ucast_priority_map_tbl_get(dev_id, index, &ucast_priority_map_tbl);

	if( rv != SW_OK )
		return rv;

	priority_map->class = ucast_priority_map_tbl.bf.class;
	return rv;
}

sw_error_t
adpt_hppe_ucast_priority_map_set(
		a_uint32_t dev_id,
		fal_ucast_priority_map_t *priority_map)
{
	union ucast_priority_map_tbl_u ucast_priority_map_tbl;
	a_int32_t index = 0;

	memset(&ucast_priority_map_tbl, 0, sizeof(ucast_priority_map_tbl));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(priority_map);

	index = priority_map->profile << 4 | priority_map->priority;
	ucast_priority_map_tbl.bf.class = priority_map->class;
	
	return hppe_ucast_priority_map_tbl_set(dev_id, index, &ucast_priority_map_tbl);
}

sw_error_t
adpt_hppe_ucast_hash_map_set(
		a_uint32_t dev_id,
		fal_ucast_hash_map_t *hash_map)
{
	union ucast_hash_map_tbl_u ucast_hash_map_tbl;
	a_uint32_t index = 0;

	memset(&ucast_hash_map_tbl, 0, sizeof(ucast_hash_map_tbl));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(hash_map);

	index = hash_map->profile << 4 | hash_map->packet_hash;
	ucast_hash_map_tbl.bf.hash = hash_map->queue_hash;
	
	return hppe_ucast_hash_map_tbl_set(dev_id, index, &ucast_hash_map_tbl);
}

sw_error_t
adpt_hppe_ucast_hash_map_get(
		a_uint32_t dev_id,
		fal_ucast_hash_map_t *hash_map)
{
	sw_error_t rv = SW_OK;
	union ucast_hash_map_tbl_u ucast_hash_map_tbl;
	a_uint32_t index = 0;

	memset(&ucast_hash_map_tbl, 0, sizeof(ucast_hash_map_tbl));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(hash_map);

	index = hash_map->profile << 4 | hash_map->packet_hash;
	rv = hppe_ucast_hash_map_tbl_get(dev_id, index, &ucast_hash_map_tbl);
	if( rv != SW_OK )
		return rv;

	hash_map->queue_hash = ucast_hash_map_tbl.bf.hash;
	return rv;
}

sw_error_t
adpt_hppe_port_mcast_priority_class_get(
		a_uint32_t dev_id,
		fal_port_t port,
		fal_mcast_priority_map_t *pri_map)
{
	sw_error_t rv = SW_OK;
	union mcast_priority_map0_u mcast_priority_map0;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(pri_map);


	if (port == 0){
		rv = hppe_mcast_priority_map0_get(dev_id, pri_map->priority, &mcast_priority_map0);
	} else if (port == 1) {
		rv = hppe_mcast_priority_map1_get(dev_id, pri_map->priority,
					(union mcast_priority_map1_u *)&mcast_priority_map0);
	} else if (port == 2) {
		rv = hppe_mcast_priority_map2_get(dev_id, pri_map->priority,
					(union mcast_priority_map2_u *)&mcast_priority_map0);
	} else if (port == 3) {
		rv = hppe_mcast_priority_map3_get(dev_id, pri_map->priority,
					(union mcast_priority_map3_u *)&mcast_priority_map0);
	} else if (port == 4) {
		rv = hppe_mcast_priority_map4_get(dev_id, pri_map->priority,
					(union mcast_priority_map4_u *)&mcast_priority_map0);
	} else if (port == 5) {
		rv = hppe_mcast_priority_map5_get(dev_id, pri_map->priority,
					(union mcast_priority_map5_u *)&mcast_priority_map0);
	} else if (port == 6) {
		rv = hppe_mcast_priority_map6_get(dev_id, pri_map->priority,
					(union mcast_priority_map6_u *)&mcast_priority_map0);
	} else if (port == 7) {
		rv = hppe_mcast_priority_map7_get(dev_id, pri_map->priority,
					(union mcast_priority_map7_u *)&mcast_priority_map0);
	}

	if( rv != SW_OK )
		return rv;

	pri_map->class = mcast_priority_map0.bf.class;
	return SW_OK;
}

sw_error_t
adpt_hppe_port_mcast_priority_class_set(
		a_uint32_t dev_id,
		fal_port_t port,
		fal_mcast_priority_map_t *pri_map)
{
	sw_error_t rv = SW_OK;
	union mcast_priority_map0_u mcast_priority_map0;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(pri_map);

	mcast_priority_map0.bf.class = pri_map->class;
	
	if (port == 0){
		rv = hppe_mcast_priority_map0_set(dev_id, pri_map->priority, &mcast_priority_map0);
	} else if (port == 1) {
		rv = hppe_mcast_priority_map1_set(dev_id, pri_map->priority,
					(union mcast_priority_map1_u *)&mcast_priority_map0);
	} else if (port == 2) {
		rv = hppe_mcast_priority_map2_set(dev_id, pri_map->priority,
					(union mcast_priority_map2_u *)&mcast_priority_map0);
	} else if (port == 3) {
		rv = hppe_mcast_priority_map3_set(dev_id, pri_map->priority,
					(union mcast_priority_map3_u *)&mcast_priority_map0);
	} else if (port == 4) {
		rv = hppe_mcast_priority_map4_set(dev_id, pri_map->priority,
					(union mcast_priority_map4_u *)&mcast_priority_map0);
	} else if (port == 5) {
		rv = hppe_mcast_priority_map5_set(dev_id, pri_map->priority,
					(union mcast_priority_map5_u *)&mcast_priority_map0);
	} else if (port == 6) {
		rv = hppe_mcast_priority_map6_set(dev_id, pri_map->priority,
					(union mcast_priority_map6_u *)&mcast_priority_map0);
	} else if (port == 7) {
		rv = hppe_mcast_priority_map7_set(dev_id, pri_map->priority,
					(union mcast_priority_map7_u *)&mcast_priority_map0);
	}

	return rv;
}

sw_error_t
adpt_hppe_ucast_default_hash_get(
		a_uint32_t dev_id,
		a_uint8_t *hash_value)
{
	sw_error_t rv = SW_OK;
	union ucast_default_hash_u ucast_default_hash;

	memset(&ucast_default_hash, 0, sizeof(ucast_default_hash));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(hash_value);

	rv = hppe_ucast_default_hash_get(dev_id, &ucast_default_hash);
	if( rv != SW_OK )
		return rv;
	
	*hash_value = ucast_default_hash.bf.hash;
	return SW_OK;
}

sw_error_t
adpt_hppe_ucast_default_hash_set(
		a_uint32_t dev_id,
		a_uint8_t hash_value)
{
	sw_error_t rv = SW_OK;
	union ucast_default_hash_u ucast_default_hash;

	memset(&ucast_default_hash, 0, sizeof(ucast_default_hash));
	ADPT_DEV_ID_CHECK(dev_id);

	ucast_default_hash.bf.hash = hash_value;
	rv = hppe_ucast_default_hash_set(dev_id, &ucast_default_hash);
	
	return rv;
}

sw_error_t
adpt_hppe_ucast_queue_map_get(
		a_uint32_t dev_id,
		fal_ucast_queue_map_t *queue_map)
{
	sw_error_t rv = SW_OK;
	union ucast_queue_map_tbl_u ucast_queue_map_tbl;
	a_uint32_t index = 0;

	memset(&ucast_queue_map_tbl, 0, sizeof(ucast_queue_map_tbl));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(queue_map);

	if (queue_map ->service_code_en) {
		index = SERVICE_CODE_QUEUE_OFFSET + (queue_map->src_profile << 8) \
				+ queue_map->service_code;
	} else if (queue_map ->cpu_code_en) {
		index = CPU_CODE_QUEUE_OFFSET + (queue_map->src_profile << 8) \
				+ queue_map->cpu_code;
	} else {
		index = VP_PORT_QUEUE_OFFSET + (queue_map->src_profile << 8) \
				+ queue_map->dst_port;
	}

	rv = hppe_ucast_queue_map_tbl_set(dev_id, index, &ucast_queue_map_tbl);
	if (rv)
		return rv;
	queue_map->queue_base = ucast_queue_map_tbl.bf.queue_id;
	queue_map->profile = ucast_queue_map_tbl.bf.profile_id;
	
	return SW_OK;
}


sw_error_t
adpt_hppe_ucast_queue_map_set(
		a_uint32_t dev_id,
		fal_ucast_queue_map_t *queue_map)
{
	union ucast_queue_map_tbl_u ucast_queue_map_tbl;
	a_uint32_t index = 0;

	memset(&ucast_queue_map_tbl, 0, sizeof(ucast_queue_map_tbl));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(queue_map);

	if (queue_map ->service_code_en) {
		index = SERVICE_CODE_QUEUE_OFFSET + (queue_map->src_profile << 8) \
				+ queue_map->service_code;
	} else if (queue_map ->cpu_code_en) {
		index = CPU_CODE_QUEUE_OFFSET + (queue_map->src_profile << 8) \
				+ queue_map->cpu_code;
	} else {
		index = VP_PORT_QUEUE_OFFSET + (queue_map->src_profile << 8) \
				+ queue_map->dst_port;
	}

	ucast_queue_map_tbl.bf.queue_id = queue_map->queue_base;
	ucast_queue_map_tbl.bf.profile_id = queue_map->profile;
	
	return hppe_ucast_queue_map_tbl_set(dev_id, index, &ucast_queue_map_tbl);
}

sw_error_t
adpt_hppe_unicast_queue_ac_cfg_get(
		a_uint32_t dev_id,
		a_uint32_t queue_id,
		fal_uni_queue_ac_cfg_t *cfg)
{
	sw_error_t rv = SW_OK;
	union ac_uni_queue_cfg_tbl_u ac_uni_queue_cfg_tbl;

	memset(&ac_uni_queue_cfg_tbl, 0, sizeof(ac_uni_queue_cfg_tbl));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(cfg);

	rv = hppe_ac_uni_queue_cfg_tbl_get(dev_id, queue_id, &ac_uni_queue_cfg_tbl);
	if( rv != SW_OK )
		return rv;

	cfg->ac_en = ac_uni_queue_cfg_tbl.bf.ac_cfg_ac_en;
	cfg->wred_en = ac_uni_queue_cfg_tbl.bf.ac_cfg_wred_en;
	cfg->ac_fc_en = ac_uni_queue_cfg_tbl.bf.ac_cfg_force_ac_en;
	cfg->color_aware = ac_uni_queue_cfg_tbl.bf.ac_cfg_color_aware;
	cfg->dynamic_en = ac_uni_queue_cfg_tbl.bf.ac_cfg_shared_dynamic;
	cfg->group_id = ac_uni_queue_cfg_tbl.bf.ac_cfg_grp_id;
	cfg->green_resume_off = ac_uni_queue_cfg_tbl.bf.ac_cfg_grn_resume_offset;
	cfg->yel_resume_off = ac_uni_queue_cfg_tbl.bf.ac_cfg_yel_resume_offset;
	cfg->red_resume_off = ac_uni_queue_cfg_tbl.bf.ac_cfg_red_resume_offset_0 | \
						ac_uni_queue_cfg_tbl.bf.ac_cfg_red_resume_offset_1 << 9;
	cfg->green_red_min_gap = ac_uni_queue_cfg_tbl.bf.ac_cfg_gap_grn_red_min;
	cfg->green_red_max_gap = ac_uni_queue_cfg_tbl.bf.ac_cfg_gap_grn_red_max;
	cfg->green_yel_min_gap = ac_uni_queue_cfg_tbl.bf.ac_cfg_gap_grn_yel_min_0 | \
							ac_uni_queue_cfg_tbl.bf.ac_cfg_gap_grn_yel_min_1 << 10;
	cfg->green_yel_max_gap = ac_uni_queue_cfg_tbl.bf.ac_cfg_gap_grn_yel_max;
	cfg->green_green_min_gap = ac_uni_queue_cfg_tbl.bf.ac_cfg_gap_grn_grn_min;
	cfg->share_weight = ac_uni_queue_cfg_tbl.bf.ac_cfg_shared_weight;
	cfg->share_ceiling = ac_uni_queue_cfg_tbl.bf.ac_cfg_shared_ceiling;
	cfg->prealloc = ac_uni_queue_cfg_tbl.bf.ac_cfg_pre_alloc_limit;

	return SW_OK;
}

sw_error_t
adpt_hppe_queue_flush(
		a_uint32_t dev_id,
		fal_port_t port,
		fal_queue_flush_dst_t *flush_dst)
{
	union flush_cfg_u flush_cfg;
	a_uint32_t i = 0x100;
	sw_error_t rv;

	memset(&flush_cfg, 0, sizeof(flush_cfg));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(flush_dst);

	hppe_flush_cfg_get(dev_id, &flush_cfg);

	flush_cfg.bf.flush_all_queues = flush_dst->flush_mode;
	flush_cfg.bf.flush_qid = flush_dst->queue_id;
	flush_cfg.bf.flush_dst_port = port;
	flush_cfg.bf.flush_busy = 1;
	
	hppe_flush_cfg_set(dev_id, &flush_cfg);
	rv = hppe_flush_cfg_get(dev_id, &flush_cfg);
	if (SW_OK != rv)
		return rv;
	while (flush_cfg.bf.flush_busy && --i) {
		hppe_flush_cfg_get(dev_id, &flush_cfg);
	}
	if (i == 0)
		return SW_BUSY;
	flush_dst->status = flush_cfg.bf.flush_status;
	return SW_OK;
}
sw_error_t
adpt_hppe_unicast_queue_ac_cfg_set(
		a_uint32_t dev_id,
		a_uint32_t queue_id,
		fal_uni_queue_ac_cfg_t *cfg)
{
	sw_error_t rv = SW_OK;
	union ac_uni_queue_cfg_tbl_u ac_uni_queue_cfg_tbl;

	memset(&ac_uni_queue_cfg_tbl, 0, sizeof(ac_uni_queue_cfg_tbl));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(cfg);

	rv = hppe_ac_uni_queue_cfg_tbl_get(dev_id, queue_id, &ac_uni_queue_cfg_tbl);
	if( rv != SW_OK )
		return rv;

	ac_uni_queue_cfg_tbl.bf.ac_cfg_ac_en = cfg->ac_en;
	ac_uni_queue_cfg_tbl.bf.ac_cfg_wred_en = cfg->wred_en;
	ac_uni_queue_cfg_tbl.bf.ac_cfg_force_ac_en = cfg->ac_fc_en;
	ac_uni_queue_cfg_tbl.bf.ac_cfg_color_aware = cfg->color_aware;
	ac_uni_queue_cfg_tbl.bf.ac_cfg_shared_dynamic = cfg->dynamic_en;
	ac_uni_queue_cfg_tbl.bf.ac_cfg_grp_id = cfg->group_id;
	ac_uni_queue_cfg_tbl.bf.ac_cfg_grn_resume_offset = cfg->green_resume_off;
	ac_uni_queue_cfg_tbl.bf.ac_cfg_yel_resume_offset = cfg->yel_resume_off;
	ac_uni_queue_cfg_tbl.bf.ac_cfg_red_resume_offset_0 = cfg->red_resume_off;
	ac_uni_queue_cfg_tbl.bf.ac_cfg_red_resume_offset_1 = cfg->red_resume_off >> 9;
	ac_uni_queue_cfg_tbl.bf.ac_cfg_gap_grn_red_min = cfg->green_red_min_gap;
	ac_uni_queue_cfg_tbl.bf.ac_cfg_gap_grn_red_max = cfg->green_red_max_gap;
	ac_uni_queue_cfg_tbl.bf.ac_cfg_gap_grn_yel_min_0 = cfg->green_yel_min_gap;
	ac_uni_queue_cfg_tbl.bf.ac_cfg_gap_grn_yel_min_1 = cfg->green_yel_min_gap >> 20;
	ac_uni_queue_cfg_tbl.bf.ac_cfg_gap_grn_yel_max = cfg->green_yel_max_gap;
	ac_uni_queue_cfg_tbl.bf.ac_cfg_gap_grn_grn_min = cfg->green_green_min_gap;
	ac_uni_queue_cfg_tbl.bf.ac_cfg_shared_weight = cfg->share_weight;
	ac_uni_queue_cfg_tbl.bf.ac_cfg_shared_ceiling = cfg->share_ceiling;
	ac_uni_queue_cfg_tbl.bf.ac_cfg_pre_alloc_limit = cfg->prealloc;

	return hppe_ac_uni_queue_cfg_tbl_set(dev_id, queue_id, &ac_uni_queue_cfg_tbl);;
}
sw_error_t
adpt_hppe_group_ac_cfg_set(
		a_uint32_t dev_id,
		a_uint8_t group_id,
		fal_group_ac_cfg_t *cfg)
{
	union ac_grp_cfg_tbl_u ac_grp_cfg_tbl;

	memset(&ac_grp_cfg_tbl, 0, sizeof(ac_grp_cfg_tbl));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(cfg);

	ac_grp_cfg_tbl.bf.ac_cfg_ac_en = cfg->ac_en;
	ac_grp_cfg_tbl.bf.ac_cfg_force_ac_en = cfg->ac_fc_en;
	ac_grp_cfg_tbl.bf.ac_cfg_color_aware = cfg->color_aware;
	ac_grp_cfg_tbl.bf.ac_grp_gap_grn_red = cfg->green_red_gap;
	ac_grp_cfg_tbl.bf.ac_grp_gap_grn_yel = cfg->green_yel_gap;
	ac_grp_cfg_tbl.bf.ac_grp_dp_thrd_0 = cfg->dp_thresh;
	ac_grp_cfg_tbl.bf.ac_grp_dp_thrd_1 = cfg->dp_thresh >> 7;
	ac_grp_cfg_tbl.bf.ac_grp_limit = cfg->grp_limit;
	ac_grp_cfg_tbl.bf.ac_grp_grn_resume_offset = cfg->green_resume_off;
	ac_grp_cfg_tbl.bf.ac_grp_yel_resume_offset_0 = cfg->yel_resume_off;
	ac_grp_cfg_tbl.bf.ac_grp_yel_resume_offset_1 = cfg->yel_resume_off >> 6;
	ac_grp_cfg_tbl.bf.ac_grp_red_resume_offset = cfg->red_resume_off;
	ac_grp_cfg_tbl.bf.ac_grp_palloc_limit = cfg->pre_alloc;

	return hppe_ac_grp_cfg_tbl_set(dev_id, group_id, &ac_grp_cfg_tbl);
}

sw_error_t
adpt_hppe_group_ac_cfg_get(
		a_uint32_t dev_id,
		a_uint8_t group_id,
		fal_group_ac_cfg_t *cfg)
{
	union ac_grp_cfg_tbl_u ac_grp_cfg_tbl;

	memset(&ac_grp_cfg_tbl, 0, sizeof(ac_grp_cfg_tbl));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(cfg);

	hppe_ac_grp_cfg_tbl_get(dev_id, group_id, &ac_grp_cfg_tbl);

	cfg->ac_en = ac_grp_cfg_tbl.bf.ac_cfg_ac_en;
	cfg->ac_fc_en = ac_grp_cfg_tbl.bf.ac_cfg_force_ac_en;
	cfg->color_aware = ac_grp_cfg_tbl.bf.ac_cfg_color_aware;
	cfg->green_red_gap = ac_grp_cfg_tbl.bf.ac_grp_gap_grn_red;
	cfg->green_yel_gap = ac_grp_cfg_tbl.bf.ac_grp_gap_grn_yel;
	cfg->dp_thresh = ac_grp_cfg_tbl.bf.ac_grp_dp_thrd_0 | \
					ac_grp_cfg_tbl.bf.ac_grp_dp_thrd_1 >> 7;
	cfg->grp_limit = ac_grp_cfg_tbl.bf.ac_grp_limit;
	cfg->green_resume_off = ac_grp_cfg_tbl.bf.ac_grp_grn_resume_offset;
	cfg->yel_resume_off = ac_grp_cfg_tbl.bf.ac_grp_yel_resume_offset_0 | \
						ac_grp_cfg_tbl.bf.ac_grp_yel_resume_offset_1 >> 6;
	cfg->red_resume_off = ac_grp_cfg_tbl.bf.ac_grp_red_resume_offset;
	cfg->pre_alloc = ac_grp_cfg_tbl.bf.ac_grp_palloc_limit;

	return SW_OK;
}

sw_error_t
adpt_hppe_multicast_queue_ac_cfg_get(
		a_uint32_t dev_id,
		a_uint32_t queue_id,
		fal_multi_queue_ac_cfg_t *cfg)
{
	sw_error_t rv = SW_OK;
	union ac_mul_queue_cfg_tbl_u ac_mul_queue_cfg_tbl;

	memset(&ac_mul_queue_cfg_tbl, 0, sizeof(ac_mul_queue_cfg_tbl));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(cfg);

	rv = hppe_ac_mul_queue_cfg_tbl_get(dev_id, queue_id, &ac_mul_queue_cfg_tbl);
	if( rv != SW_OK )
		return rv;

	cfg->ac_en = ac_mul_queue_cfg_tbl.bf.ac_cfg_ac_en;
	cfg->ac_fc_en = ac_mul_queue_cfg_tbl.bf.ac_cfg_force_ac_en;
	cfg->color_aware = ac_mul_queue_cfg_tbl.bf.ac_cfg_color_aware;
	cfg->group_id = ac_mul_queue_cfg_tbl.bf.ac_cfg_grp_id;
	cfg->green_resume_off = ac_mul_queue_cfg_tbl.bf.ac_cfg_grn_resume_offset;
	cfg->yel_resume_off = ac_mul_queue_cfg_tbl.bf.ac_cfg_yel_resume_offset_0 | \
						ac_mul_queue_cfg_tbl.bf.ac_cfg_yel_resume_offset_1 << 4;
	cfg->red_resume_off = ac_mul_queue_cfg_tbl.bf.ac_cfg_red_resume_offset;
	cfg->green_red_gap = ac_mul_queue_cfg_tbl.bf.ac_cfg_gap_grn_red;
	cfg->green_yel_gap = ac_mul_queue_cfg_tbl.bf.ac_cfg_gap_grn_yel_0 | \
						ac_mul_queue_cfg_tbl.bf.ac_cfg_gap_grn_yel_1 << 5;
	cfg->share_ceiling = ac_mul_queue_cfg_tbl.bf.ac_cfg_shared_ceiling;
	cfg->prealloc = ac_mul_queue_cfg_tbl.bf.ac_cfg_pre_alloc_limit;

	return SW_OK;
}

sw_error_t
adpt_hppe_multicast_queue_ac_cfg_set(
		a_uint32_t dev_id,
		a_uint32_t queue_id,
		fal_multi_queue_ac_cfg_t *cfg)
{
	union ac_mul_queue_cfg_tbl_u ac_mul_queue_cfg_tbl;

	memset(&ac_mul_queue_cfg_tbl, 0, sizeof(ac_mul_queue_cfg_tbl));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(cfg);


	ac_mul_queue_cfg_tbl.bf.ac_cfg_ac_en = cfg->ac_en;
	ac_mul_queue_cfg_tbl.bf.ac_cfg_force_ac_en = cfg->ac_fc_en;
	ac_mul_queue_cfg_tbl.bf.ac_cfg_color_aware = cfg->color_aware;
	ac_mul_queue_cfg_tbl.bf.ac_cfg_grp_id = cfg->group_id;
	ac_mul_queue_cfg_tbl.bf.ac_cfg_grn_resume_offset = cfg->green_resume_off;
	ac_mul_queue_cfg_tbl.bf.ac_cfg_yel_resume_offset_0 = cfg->yel_resume_off;
	ac_mul_queue_cfg_tbl.bf.ac_cfg_yel_resume_offset_1 = cfg->yel_resume_off >> 4;
	ac_mul_queue_cfg_tbl.bf.ac_cfg_red_resume_offset = cfg->red_resume_off;
	ac_mul_queue_cfg_tbl.bf.ac_cfg_gap_grn_red = cfg->green_red_gap;
	ac_mul_queue_cfg_tbl.bf.ac_cfg_gap_grn_yel_0 = cfg->green_yel_gap;
	ac_mul_queue_cfg_tbl.bf.ac_cfg_gap_grn_yel_1 = cfg->green_yel_gap >> 5;
	ac_mul_queue_cfg_tbl.bf.ac_cfg_shared_ceiling = cfg->share_ceiling;
	ac_mul_queue_cfg_tbl.bf.ac_cfg_pre_alloc_limit = cfg->prealloc;

	return hppe_ac_mul_queue_cfg_tbl_set(dev_id, queue_id, &ac_mul_queue_cfg_tbl);
}

sw_error_t adpt_hppe_qm_init(a_uint32_t dev_id)
{
	adpt_api_t *p_adpt_api = NULL;

	p_adpt_api = adpt_api_ptr_get(dev_id);

	if(p_adpt_api == NULL)
		return SW_FAIL;

	p_adpt_api->adpt_mcast_queue_map_set = adpt_hppe_mcast_queue_map_set;
	p_adpt_api->adpt_ucast_priority_map_get = adpt_hppe_ucast_priority_map_get;
	p_adpt_api->adpt_ucast_hash_map_set = adpt_hppe_ucast_hash_map_set;
	p_adpt_api->adpt_port_mcast_priority_class_get = adpt_hppe_port_mcast_priority_class_get;
	p_adpt_api->adpt_ucast_default_hash_get = adpt_hppe_ucast_default_hash_get;
	p_adpt_api->adpt_ucast_queue_map_get = adpt_hppe_ucast_queue_map_get;
	p_adpt_api->adpt_ucast_default_hash_set = adpt_hppe_ucast_default_hash_set;
	p_adpt_api->adpt_mcast_queue_map_get = adpt_hppe_mcast_queue_map_get;
	p_adpt_api->adpt_ucast_priority_map_set = adpt_hppe_ucast_priority_map_set;
	p_adpt_api->adpt_port_mcast_priority_class_set = adpt_hppe_port_mcast_priority_class_set;
	p_adpt_api->adpt_ucast_queue_map_set = adpt_hppe_ucast_queue_map_set;
	p_adpt_api->adpt_ucast_hash_map_get = adpt_hppe_ucast_hash_map_get;
	p_adpt_api->adpt_unicast_queue_ac_cfg_get = adpt_hppe_unicast_queue_ac_cfg_get;
	p_adpt_api->adpt_queue_flush = adpt_hppe_queue_flush;
	p_adpt_api->adpt_unicast_queue_ac_cfg_set = adpt_hppe_unicast_queue_ac_cfg_set;
	p_adpt_api->adpt_group_ac_cfg_set = adpt_hppe_group_ac_cfg_set;
	p_adpt_api->adpt_group_ac_cfg_get = adpt_hppe_group_ac_cfg_get;
	p_adpt_api->adpt_multicast_queue_ac_cfg_get = adpt_hppe_multicast_queue_ac_cfg_get;
	p_adpt_api->adpt_multicast_queue_ac_cfg_set = adpt_hppe_multicast_queue_ac_cfg_set;


	return SW_OK;
}

/**
 * @}
 */