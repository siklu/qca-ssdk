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
 * @defgroup fal_gen FAL_SERVCODE
 * @{
 */
#ifndef _FAL_SERVCODE_H_
#define _FAL_SERVCODE_H_

#ifdef __cplusplus
extern "C" {
#endif                          /* __cplusplus */

#include "common/sw.h"
#include "fal/fal_type.h"

#if defined(SW_API_LOCK) && (!defined(HSL_STANDALONG))
#define FAL_SERVCODE_API_LOCK
#define FAL_SERVCODE_API_UNLOCK
#else
#define FAL_SERVCODE_API_LOCK
#define FAL_SERVCODE_API_UNLOCK
#endif

typedef struct {
	a_uint32_t  bypass_bitmap;
	a_uint32_t  rx_counting_en;
} fal_parse_service_entry_t;

typedef struct {
	a_bool_t  dst_port_id_valid;
	a_uint32_t  dst_port_id;
	a_uint32_t  direction;
	a_uint32_t  bypass_bitmap;
	a_bool_t  rx_cnt_en;
	a_bool_t  tx_cnt_en;
} fal_ingress_service_entry_t;

typedef struct {
	a_uint32_t  field_update_action;
	a_uint32_t  next_service_code;
	a_uint32_t  hw_services;
	a_uint32_t  offset_sel; //Select the offset value to IP-197:0: l3_offset1:l4_offset
	a_bool_t  tx_counting_en;
} fal_egress_service_entry_t;

sw_error_t fal_parse_service_profile_set(a_uint32_t dev_id,
										a_uint32_t profile_id,
										fal_parse_service_entry_t *entry);
sw_error_t fal_parse_service_profile_get(a_uint32_t dev_id,
										a_uint32_t profile_id,
										fal_parse_service_entry_t *entry);

sw_error_t fal_ingress_service_profile_set(a_uint32_t dev_id,
										a_uint32_t profile_id,
										fal_ingress_service_entry_t *entry);
sw_error_t fal_ingress_service_profile_get(a_uint32_t dev_id,
										a_uint32_t profile_id,
										fal_ingress_service_entry_t *entry);

sw_error_t fal_egress_service_profile_set(a_uint32_t dev_id,
										a_uint32_t profile_id,
										fal_egress_service_entry_t *entry);
sw_error_t fal_egress_service_profile_get(a_uint32_t dev_id,
										a_uint32_t profile_id,
										fal_egress_service_entry_t *entry);

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* _FAL_SERVCODE_H_ */
/**
 * @}
 */

