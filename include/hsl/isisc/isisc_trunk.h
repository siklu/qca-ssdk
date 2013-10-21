/*
 * Copyright (c) 2012 Qualcomm Atheros, Inc.
 * All rights reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 *
 */
#ifndef _ISISC_TRUNK_H_
#define _ISISC_TRUNK_H_

#ifdef __cplusplus
extern "C" {
#endif                          /* __cplusplus */

#include "fal/fal_trunk.h"

    sw_error_t isisc_trunk_init(a_uint32_t dev_id);

#ifdef IN_TRUNK
#define ISISC_TRUNK_INIT(rv, dev_id) \
    { \
        rv = isisc_trunk_init(dev_id); \
        SW_RTN_ON_ERROR(rv); \
    }
#else
#define ISISC_TRUNK_INIT(rv, dev_id)
#endif

#ifdef HSL_STANDALONG

    HSL_LOCAL sw_error_t
    isisc_trunk_group_set(a_uint32_t dev_id, a_uint32_t trunk_id,
                         a_bool_t enable, fal_pbmp_t member);

    HSL_LOCAL sw_error_t
    isisc_trunk_group_get(a_uint32_t dev_id, a_uint32_t trunk_id,
                         a_bool_t * enable, fal_pbmp_t * member);

    HSL_LOCAL sw_error_t
    isisc_trunk_hash_mode_set(a_uint32_t dev_id, a_uint32_t hash_mode);

    HSL_LOCAL sw_error_t
    isisc_trunk_hash_mode_get(a_uint32_t dev_id, a_uint32_t * hash_mode);

    HSL_LOCAL sw_error_t
    isisc_trunk_manipulate_sa_set(a_uint32_t dev_id, fal_mac_addr_t * addr);

    HSL_LOCAL sw_error_t
    isisc_trunk_manipulate_sa_get(a_uint32_t dev_id, fal_mac_addr_t * addr);

    HSL_LOCAL sw_error_t
    isisc_trunk_manipulate_dp(a_uint32_t dev_id, a_uint8_t * header,
                              a_uint32_t len, fal_pbmp_t dp_member);

#endif

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* _ISISC_TRUNK_H_ */

