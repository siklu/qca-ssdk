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
 * @defgroup fal_ctrlpkt FAL_SERVCODE
 * @{
 */
#include "sw.h"
#include "fal_servcode.h"
#include "hsl_api.h"
#include "adpt.h"

#include <linux/kernel.h>
#include <linux/module.h>


/**
 * @}
 */
sw_error_t
_fal_parse_service_profile_set(a_uint32_t dev_id,
						a_uint32_t profile_id,
						fal_parse_service_entry_t *entry)
{
    sw_error_t rv;
    adpt_api_t *p_api;

    SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

    if (NULL == p_api->adpt_parse_service_profile_set)
        return SW_NOT_SUPPORTED;

    rv = p_api->adpt_parse_service_profile_set(dev_id, profile_id, entry);
    return rv;
}

sw_error_t
_fal_parse_service_profile_get(a_uint32_t dev_id,
						a_uint32_t profile_id,
						fal_parse_service_entry_t *entry)
{
    sw_error_t rv;
    adpt_api_t *p_api;

    SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

    if (NULL == p_api->adpt_parse_service_profile_get)
        return SW_NOT_SUPPORTED;

    rv = p_api->adpt_parse_service_profile_get(dev_id, profile_id, entry);
    return rv;
}

sw_error_t
_fal_ingress_service_profile_set(a_uint32_t dev_id,
						a_uint32_t profile_id,
						fal_ingress_service_entry_t *entry)
{
    sw_error_t rv;
    adpt_api_t *p_api;

    SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

    if (NULL == p_api->adpt_ingress_service_profile_set)
        return SW_NOT_SUPPORTED;

    rv = p_api->adpt_ingress_service_profile_set(dev_id, profile_id, entry);
    return rv;
}

sw_error_t
_fal_ingress_service_profile_get(a_uint32_t dev_id,
						a_uint32_t profile_id,
						fal_ingress_service_entry_t *entry)
{
    sw_error_t rv;
    adpt_api_t *p_api;

    SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

    if (NULL == p_api->adpt_ingress_service_profile_get)
        return SW_NOT_SUPPORTED;

    rv = p_api->adpt_ingress_service_profile_get(dev_id, profile_id, entry);
    return rv;
}

sw_error_t
_fal_egress_service_profile_set(a_uint32_t dev_id,
						a_uint32_t profile_id,
						fal_egress_service_entry_t *entry)
{
    sw_error_t rv;
    adpt_api_t *p_api;

    SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

    if (NULL == p_api->adpt_egress_service_profile_set)
        return SW_NOT_SUPPORTED;

    rv = p_api->adpt_egress_service_profile_set(dev_id, profile_id, entry);
    return rv;
}

sw_error_t
_fal_egress_service_profile_get(a_uint32_t dev_id,
						a_uint32_t profile_id,
						fal_egress_service_entry_t *entry)
{
    sw_error_t rv;
    adpt_api_t *p_api;

    SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

    if (NULL == p_api->adpt_egress_service_profile_get)
        return SW_NOT_SUPPORTED;

    rv = p_api->adpt_egress_service_profile_get(dev_id, profile_id, entry);
    return rv;
}

sw_error_t
fal_parse_service_profile_set(a_uint32_t dev_id,
						a_uint32_t profile_id,
						fal_parse_service_entry_t *entry)
{
    sw_error_t rv = SW_OK;

    FAL_SERVCODE_API_LOCK;
    rv = _fal_parse_service_profile_set(dev_id, profile_id, entry);
    FAL_SERVCODE_API_UNLOCK;
    return rv;
}

sw_error_t
fal_parse_service_profile_get(a_uint32_t dev_id,
						a_uint32_t profile_id,
						fal_parse_service_entry_t *entry)
{
    sw_error_t rv = SW_OK;

    FAL_SERVCODE_API_LOCK;
    rv = _fal_parse_service_profile_get(dev_id, profile_id, entry);
    FAL_SERVCODE_API_UNLOCK;
    return rv;
}

sw_error_t
fal_ingress_service_profile_set(a_uint32_t dev_id,
						a_uint32_t profile_id,
						fal_ingress_service_entry_t *entry)
{
    sw_error_t rv = SW_OK;

    FAL_SERVCODE_API_LOCK;
    rv = _fal_ingress_service_profile_set(dev_id, profile_id, entry);
    FAL_SERVCODE_API_UNLOCK;
    return rv;
}

sw_error_t
fal_ingress_service_profile_get(a_uint32_t dev_id,
						a_uint32_t profile_id,
						fal_ingress_service_entry_t *entry)
{
    sw_error_t rv = SW_OK;

    FAL_SERVCODE_API_LOCK;
    rv = _fal_ingress_service_profile_get(dev_id, profile_id, entry);
    FAL_SERVCODE_API_UNLOCK;
    return rv;
}

sw_error_t
fal_egress_service_profile_set(a_uint32_t dev_id,
						a_uint32_t profile_id,
						fal_egress_service_entry_t *entry)
{
    sw_error_t rv = SW_OK;

    FAL_SERVCODE_API_LOCK;
    rv = _fal_egress_service_profile_set(dev_id, profile_id, entry);
    FAL_SERVCODE_API_UNLOCK;
    return rv;
}

sw_error_t
fal_egress_service_profile_get(a_uint32_t dev_id,
						a_uint32_t profile_id,
						fal_egress_service_entry_t *entry)
{
    sw_error_t rv = SW_OK;

    FAL_SERVCODE_API_LOCK;
    rv = _fal_egress_service_profile_get(dev_id, profile_id, entry);
    FAL_SERVCODE_API_UNLOCK;
    return rv;
}

