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
 * @defgroup fal_ctrlpkt FAL_CTRLPKT
 * @{
 */
#include "sw.h"
#include "fal_ctrlpkt.h"
#include "hsl_api.h"
#include "adpt.h"

#include <linux/kernel.h>
#include <linux/module.h>


/**
 * @}
 */
sw_error_t
_fal_ethernet_type_profile_set(a_uint32_t dev_id, a_uint32_t profile_id, a_uint32_t ethernet_type, a_bool_t enable)
{
    sw_error_t rv;
    adpt_api_t *p_api;

    SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

    if (NULL == p_api->adpt_ethernet_type_profile_set)
        return SW_NOT_SUPPORTED;

    rv = p_api->adpt_ethernet_type_profile_set(dev_id, profile_id, ethernet_type, enable);
    return rv;
}

sw_error_t
_fal_ethernet_type_profile_get(a_uint32_t dev_id, a_uint32_t profile_id, a_uint32_t *ethernet_type, a_bool_t *enable)
{
    sw_error_t rv;
    adpt_api_t *p_api;

    SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

    if (NULL == p_api->adpt_ethernet_type_profile_get)
        return SW_NOT_SUPPORTED;

    rv = p_api->adpt_ethernet_type_profile_get(dev_id, profile_id, ethernet_type, enable);
    return rv;
}

sw_error_t
_fal_rfdb_profile_set(a_uint32_t dev_id, a_uint32_t profile_id, fal_mac_addr_t *addr, a_bool_t enable)
{
    sw_error_t rv;
    adpt_api_t *p_api;

    SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

    if (NULL == p_api->adpt_rfdb_profile_set)
        return SW_NOT_SUPPORTED;

    rv = p_api->adpt_rfdb_profile_set(dev_id, profile_id, addr, enable);
    return rv;
}

sw_error_t
_fal_rfdb_profile_get(a_uint32_t dev_id, a_uint32_t profile_id, fal_mac_addr_t *addr, a_bool_t *enable)
{
    sw_error_t rv;
    adpt_api_t *p_api;

    SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

    if (NULL == p_api->adpt_rfdb_profile_get)
        return SW_NOT_SUPPORTED;

    rv = p_api->adpt_rfdb_profile_get(dev_id, profile_id, addr, enable);
    return rv;
}

sw_error_t
_fal_ctrlpkt_profile_set(a_uint32_t dev_id, a_uint32_t profile_id, fal_ctrlpkt_profile_t *ctrlpkt)
{
    sw_error_t rv;
    adpt_api_t *p_api;

    SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

    if (NULL == p_api->adpt_ctrlpkt_profile_set)
        return SW_NOT_SUPPORTED;

    rv = p_api->adpt_ctrlpkt_profile_set(dev_id, profile_id, ctrlpkt);
    return rv;
}

sw_error_t
_fal_ctrlpkt_profile_get(a_uint32_t dev_id, a_uint32_t profile_id, fal_ctrlpkt_profile_t *ctrlpkt)
{
    sw_error_t rv;
    adpt_api_t *p_api;

    SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

    if (NULL == p_api->adpt_ctrlpkt_profile_get)
        return SW_NOT_SUPPORTED;

    rv = p_api->adpt_ctrlpkt_profile_get(dev_id, profile_id, ctrlpkt);
    return rv;
}

sw_error_t
fal_ethernet_type_profile_set(a_uint32_t dev_id, a_uint32_t profile_id, a_uint32_t ethernet_type, a_bool_t enable)
{
    sw_error_t rv = SW_OK;

    FAL_CTRLPKT_API_LOCK;
    rv = _fal_ethernet_type_profile_set(dev_id, profile_id, ethernet_type, enable);
    FAL_CTRLPKT_API_UNLOCK;
    return rv;
}

sw_error_t
fal_ethernet_type_profile_get(a_uint32_t dev_id, a_uint32_t profile_id, a_uint32_t *ethernet_type, a_bool_t *enable)
{
    sw_error_t rv = SW_OK;

    FAL_CTRLPKT_API_LOCK;
    rv = _fal_ethernet_type_profile_get(dev_id, profile_id, ethernet_type, enable);
    FAL_CTRLPKT_API_UNLOCK;
    return rv;
}

sw_error_t
fal_rfdb_profile_set(a_uint32_t dev_id, a_uint32_t profile_id, fal_mac_addr_t *addr, a_bool_t enable)
{
    sw_error_t rv = SW_OK;

    FAL_CTRLPKT_API_LOCK;
    rv = _fal_rfdb_profile_set(dev_id, profile_id, addr, enable);
    FAL_CTRLPKT_API_UNLOCK;
    return rv;
}

sw_error_t
fal_rfdb_profile_get(a_uint32_t dev_id, a_uint32_t profile_id, fal_mac_addr_t *addr, a_bool_t *enable)
{
    sw_error_t rv = SW_OK;

    FAL_CTRLPKT_API_LOCK;
    rv = _fal_rfdb_profile_get(dev_id, profile_id, addr, enable);
    FAL_CTRLPKT_API_UNLOCK;
    return rv;
}

sw_error_t
fal_ctrlpkt_profile_set(a_uint32_t dev_id, a_uint32_t profile_id, fal_ctrlpkt_profile_t *ctrlpkt)
{
    sw_error_t rv = SW_OK;

    FAL_CTRLPKT_API_LOCK;
    rv = _fal_ctrlpkt_profile_set(dev_id, profile_id, ctrlpkt);
    FAL_CTRLPKT_API_UNLOCK;
    return rv;
}

sw_error_t
fal_ctrlpkt_profile_get(a_uint32_t dev_id, a_uint32_t profile_id, fal_ctrlpkt_profile_t *ctrlpkt)
{
    sw_error_t rv = SW_OK;

    FAL_CTRLPKT_API_LOCK;
    rv = _fal_ctrlpkt_profile_get(dev_id, profile_id, ctrlpkt);
    FAL_CTRLPKT_API_UNLOCK;
    return rv;
}

