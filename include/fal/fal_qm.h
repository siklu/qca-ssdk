/*
 * Copyright (c) 2012, 2016, The Linux Foundation. All rights reserved.
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
 * @defgroup fal_qos FAL_QM
 * @{
 */
#ifndef _FAL_QM_H_
#define _FAL_QM_H_

#ifdef __cplusplus
extern "C" {
#endif                          /* __cplusplus */

#include "common/sw.h"
#include "fal/fal_type.h"

typedef struct {
	a_uint8_t src_profile;
	a_bool_t service_code_en;
	a_uint16_t service_code;
	a_bool_t cpu_code_en;
	a_uint16_t cpu_code;
	fal_port_t dst_port;
	a_uint16_t queue_base;
	a_uint8_t profile;
} fal_ucast_queue_map_t;

typedef struct {
	a_uint8_t profile;
	a_uint8_t priority;
	a_uint8_t class;
} fal_ucast_priority_map_t;

typedef struct {
	a_uint8_t profile;
	a_uint8_t packet_hash;
	a_uint8_t queue_hash;
} fal_ucast_hash_map_t;

typedef struct {
	a_uint16_t cpu_code;
	a_uint8_t class;
} fal_mcast_queue_map_t;

typedef struct {
	a_uint16_t priority;
	a_uint8_t class;
} fal_mcast_priority_map_t;

typedef struct {
	a_uint8_t flush_mode;
	a_uint8_t status;
	a_uint16_t queue_id;
} fal_queue_flush_dst_t;

typedef struct {
	a_bool_t ac_en;
	a_bool_t wred_en;
	a_bool_t ac_fc_en;
	a_bool_t color_aware;
	a_bool_t dynamic_en;
	a_uint8_t group_id;
	a_uint16_t green_resume_off;
	a_uint16_t yel_resume_off;
	a_uint16_t red_resume_off;
	a_uint16_t green_red_min_gap;
	a_uint16_t green_red_max_gap;
	a_uint16_t green_yel_min_gap;
	a_uint16_t green_yel_max_gap;
	a_uint16_t green_green_min_gap;
	a_uint8_t share_weight;
	a_uint16_t share_ceiling;
	a_uint8_t prealloc;
} fal_uni_queue_ac_cfg_t;

typedef struct {
	a_bool_t ac_en;
	a_bool_t ac_fc_en;
	a_bool_t color_aware;
	a_uint8_t group_id;
	a_uint16_t green_resume_off;
	a_uint16_t yel_resume_off;
	a_uint16_t red_resume_off;
	a_uint16_t green_red_gap;
	a_uint16_t green_yel_gap;
	a_uint16_t share_ceiling;
	a_uint8_t prealloc;
} fal_multi_queue_ac_cfg_t;

typedef struct {
	a_bool_t ac_en;
	a_bool_t ac_fc_en;
	a_bool_t color_aware;
	a_uint16_t green_red_gap;
	a_uint16_t green_yel_gap;
	a_uint16_t dp_thresh;
	a_uint8_t grp_limit;
	a_uint16_t green_resume_off;
	a_uint16_t yel_resume_off;
	a_uint16_t red_resume_off;
	a_uint16_t pre_alloc;
} fal_group_ac_cfg_t;


sw_error_t
fal_port_mcast_priority_class_set(
		a_uint32_t dev_id,
		fal_port_t port,
		fal_mcast_priority_map_t *pri_map);

sw_error_t
fal_port_mcast_priority_class_get(
		a_uint32_t dev_id,
		fal_port_t port,
		fal_mcast_priority_map_t *pri_map);

sw_error_t
fal_ucast_default_hash_set(
		a_uint32_t dev_id,
		a_uint8_t hash_value);

sw_error_t
fal_ucast_default_hash_get(
		a_uint32_t dev_id,
		a_uint8_t *hash_value);

sw_error_t
fal_ucast_queue_map_set(
		a_uint32_t dev_id,
		fal_ucast_queue_map_t *queue_map);

sw_error_t
fal_ucast_queue_map_get(
		a_uint32_t dev_id,
		fal_ucast_queue_map_t *queue_map);

sw_error_t
fal_ucast_hash_map_set(
		a_uint32_t dev_id,
		fal_ucast_hash_map_t *hash_map);

sw_error_t
fal_ucast_hash_map_get(
		a_uint32_t dev_id,
		fal_ucast_hash_map_t *hash_map);

sw_error_t
fal_ucast_priority_map_set(
		a_uint32_t dev_id,
		fal_ucast_priority_map_t *priority_map);

sw_error_t
fal_ucast_priority_map_get(
		a_uint32_t dev_id,
		fal_ucast_priority_map_t *priority_map);

sw_error_t
fal_mcast_queue_map_set(
		a_uint32_t dev_id,
		fal_mcast_queue_map_t *queue_map);

sw_error_t
fal_mcast_queue_map_get(
		a_uint32_t dev_id,
		fal_mcast_queue_map_t *queue_map);

sw_error_t
fal_queue_flush(
		a_uint32_t dev_id,
		fal_port_t port,
		fal_queue_flush_dst_t *flush_dst);

sw_error_t
fal_unicast_queue_ac_cfg_set(
		a_uint32_t dev_id,
		a_uint32_t queue_id,
		fal_uni_queue_ac_cfg_t *cfg);

sw_error_t
fal_unicast_queue_ac_cfg_get(
		a_uint32_t dev_id,
		a_uint32_t queue_id,
		fal_uni_queue_ac_cfg_t *cfg);

sw_error_t
fal_multicast_queue_ac_cfg_set(
		a_uint32_t dev_id,
		a_uint32_t queue_id,
		fal_multi_queue_ac_cfg_t *cfg);

sw_error_t
fal_multicast_queue_ac_cfg_get(
		a_uint32_t dev_id,
		a_uint32_t queue_id,
		fal_multi_queue_ac_cfg_t *cfg);

sw_error_t
fal_group_ac_cfg_set(
		a_uint32_t dev_id,
		a_uint8_t group_id,
		fal_group_ac_cfg_t *cfg);

sw_error_t
fal_group_ac_cfg_get(
		a_uint32_t dev_id,
		a_uint8_t group_id,
		fal_group_ac_cfg_t *cfg);




#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* _PORT_QM_H_ */
/**
 * @}
 */

