/*
 * Copyright (c) 2012 Qualcomm Atheros, Inc.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */


#ifndef _ATHENA_VLAN_H
#define _ATHENA_VLAN_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "fal/fal_vlan.h"

    sw_error_t
    athena_vlan_reset(a_uint32_t dev_id);

    sw_error_t
    athena_vlan_init(a_uint32_t dev_id);

    sw_error_t
    athena_vlan_cleanup(a_uint32_t dev_id);

#ifdef IN_VLAN
#define ATHENA_VLAN_RESET(rv, dev_id) \
    { \
        rv = athena_vlan_reset(dev_id); \
        SW_RTN_ON_ERROR(rv); \
    }

#define ATHENA_VLAN_INIT(rv, dev_id) \
    { \
        rv = athena_vlan_init(dev_id); \
        SW_RTN_ON_ERROR(rv); \
    }

#define ATHENA_VLAN_CLEANUP(rv, dev_id) \
    { \
        rv = athena_vlan_cleanup(dev_id); \
        SW_RTN_ON_ERROR(rv); \
    }
#else
#define ATHENA_VLAN_RESET(rv, dev_id)
#define ATHENA_VLAN_INIT(rv, dev_id)
#define ATHENA_VLAN_CLEANUP(rv, dev_id)
#endif

#ifdef HSL_STANDALONG


    HSL_LOCAL sw_error_t
    athena_vlan_entry_append(a_uint32_t dev_id, const fal_vlan_t * vlan_entry);



    HSL_LOCAL sw_error_t
    athena_vlan_create(a_uint32_t dev_id, a_uint32_t vlan_id);



    HSL_LOCAL sw_error_t
    athena_vlan_next(a_uint32_t dev_id, a_uint32_t vlan_id, fal_vlan_t * p_vlan);



    HSL_LOCAL sw_error_t
    athena_vlan_find(a_uint32_t dev_id, a_uint32_t vlan_id, fal_vlan_t * p_vlan);



    HSL_LOCAL sw_error_t
    athena_vlan_member_update(a_uint32_t dev_id, a_uint32_t vlan_id,
                              fal_pbmp_t member, fal_pbmp_t u_member);


    HSL_LOCAL sw_error_t
    athena_vlan_delete(a_uint32_t dev_id, a_uint32_t vlan_id);
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _ATHENA_VLAN_H */
