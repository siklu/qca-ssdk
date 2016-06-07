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
 * @defgroup fal_stp FAL_VSI
 * @{
 */
#ifndef _FAL_VSI_H_
#define _FAL_VSI_H_

#ifdef __cplusplus
extern "C" {
#endif                          /* __cplusplus */

#include "common/sw.h"
#include "fal/fal_type.h"

#define FAL_VSI_INVALID 0xffff

typedef struct{
	a_uint32_t lrn_en;
	a_uint32_t action;
}fal_vsi_newaddr_lrn_t;

typedef struct{
	a_uint32_t stamove_en;
	a_uint32_t action;
}fal_vsi_stamove_t;

typedef struct{
	a_uint32_t member_ports;
	a_uint32_t uuc_ports;
	a_uint32_t umc_ports;
	a_uint32_t bc_ports;
}fal_vsi_member_t;

sw_error_t
fal_vsi_alloc(a_uint32_t dev_id, a_uint32_t *vsi);

sw_error_t
fal_vsi_free(a_uint32_t dev_id, a_uint32_t vsi);

sw_error_t
fal_port_vsi_set(a_uint32_t dev_id, fal_port_t port_id, a_uint32_t vsi_id);

sw_error_t
fal_port_vsi_get(a_uint32_t dev_id, fal_port_t port_id, a_uint32_t *vsi_id);

sw_error_t
fal_port_vlan_vsi_set(a_uint32_t dev_id, fal_port_t port_id, a_uint32_t vlan_id, a_uint32_t vsi_id);

sw_error_t
fal_port_vlan_vsi_get(a_uint32_t dev_id, fal_port_t port_id, a_uint32_t vlan_id, a_uint32_t *vsi_id);

sw_error_t
fal_vsi_tbl_dump(a_uint32_t dev_id);

sw_error_t
fal_vsi_newaddr_lrn_set(a_uint32_t dev_id, a_uint32_t vsi_id, fal_vsi_newaddr_lrn_t *newaddr_lrn);

sw_error_t
fal_vsi_newaddr_lrn_get(a_uint32_t dev_id, a_uint32_t vsi_id, fal_vsi_newaddr_lrn_t *newaddr_lrn);

sw_error_t
fal_vsi_stamove_set(a_uint32_t dev_id, a_uint32_t vsi_id, fal_vsi_stamove_t *stamove);

sw_error_t
fal_vsi_stamove_get(a_uint32_t dev_id, a_uint32_t vsi_id, fal_vsi_stamove_t *stamove);

sw_error_t
fal_vsi_member_set(a_uint32_t dev_id, a_uint32_t vsi_id, fal_vsi_member_t *vsi_member);

sw_error_t
fal_vsi_member_get(a_uint32_t dev_id, a_uint32_t vsi_id, fal_vsi_member_t *vsi_member);


#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* _FAL_VSI_H_ */

/**
 * @}
 */

