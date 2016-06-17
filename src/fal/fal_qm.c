/*
 * Copyright (c) 2012, The Linux Foundation. All rights reserved.
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
 * @defgroup fal_qm FAL_QM
 * @{
 */
#include "sw.h"
#include "fal_qm.h"
#include "hsl_api.h"
#include "adpt.h"

sw_error_t
_fal_mcast_queue_map_set(
		a_uint32_t dev_id,
		fal_mcast_queue_map_t *queue_map)
{
    adpt_api_t *p_api;
	sw_error_t rv = SW_OK;

    SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

    if (NULL == p_api->adpt_mcast_queue_map_set)
        return SW_NOT_SUPPORTED;

    rv = p_api->adpt_mcast_queue_map_set(dev_id, queue_map);
    return rv;
}
sw_error_t
_fal_ucast_priority_map_get(
		a_uint32_t dev_id,
		fal_ucast_priority_map_t *priority_map)
{
    adpt_api_t *p_api;
	sw_error_t rv = SW_OK;

    SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

    if (NULL == p_api->adpt_ucast_priority_map_get)
        return SW_NOT_SUPPORTED;

    rv = p_api->adpt_ucast_priority_map_get(dev_id, priority_map);
    return rv;
}
sw_error_t
_fal_ucast_hash_map_set(
		a_uint32_t dev_id,
		fal_ucast_hash_map_t *hash_map)
{
    adpt_api_t *p_api;
	sw_error_t rv = SW_OK;

    SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

    if (NULL == p_api->adpt_ucast_hash_map_set)
        return SW_NOT_SUPPORTED;

    rv = p_api->adpt_ucast_hash_map_set(dev_id, hash_map);
    return rv;
}
sw_error_t
_fal_port_mcast_priority_class_get(
		a_uint32_t dev_id,
		fal_port_t port,
		fal_mcast_priority_map_t *pri_map)
{
    adpt_api_t *p_api;
	sw_error_t rv = SW_OK;

    SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

    if (NULL == p_api->adpt_port_mcast_priority_class_get)
        return SW_NOT_SUPPORTED;

    rv = p_api->adpt_port_mcast_priority_class_get(dev_id, port, pri_map);
    return rv;
}
sw_error_t
_fal_ucast_default_hash_get(
		a_uint32_t dev_id,
		a_uint8_t *hash_value)
{
    adpt_api_t *p_api;
	sw_error_t rv = SW_OK;

    SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

    if (NULL == p_api->adpt_ucast_default_hash_get)
        return SW_NOT_SUPPORTED;

    rv = p_api->adpt_ucast_default_hash_get(dev_id, hash_value);
    return rv;
}
sw_error_t
_fal_ucast_queue_map_get(
		a_uint32_t dev_id,
		fal_ucast_queue_map_t *queue_map)
{
    adpt_api_t *p_api;
	sw_error_t rv = SW_OK;

    SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

    if (NULL == p_api->adpt_ucast_queue_map_get)
        return SW_NOT_SUPPORTED;

    rv = p_api->adpt_ucast_queue_map_get(dev_id, queue_map);
    return rv;
}
sw_error_t
_fal_ucast_default_hash_set(
		a_uint32_t dev_id,
		a_uint8_t hash_value)
{
    adpt_api_t *p_api;
	sw_error_t rv = SW_OK;

    SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

    if (NULL == p_api->adpt_ucast_default_hash_set)
        return SW_NOT_SUPPORTED;

    rv = p_api->adpt_ucast_default_hash_set(dev_id, hash_value);
    return rv;
}
sw_error_t
_fal_mcast_queue_map_get(
		a_uint32_t dev_id,
		fal_mcast_queue_map_t *queue_map)
{
    adpt_api_t *p_api;
	sw_error_t rv = SW_OK;

    SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

    if (NULL == p_api->adpt_mcast_queue_map_get)
        return SW_NOT_SUPPORTED;

    rv = p_api->adpt_mcast_queue_map_get(dev_id, queue_map);
    return rv;
}
sw_error_t
_fal_ucast_priority_map_set(
		a_uint32_t dev_id,
		fal_ucast_priority_map_t *priority_map)
{
    adpt_api_t *p_api;
	sw_error_t rv = SW_OK;

    SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

    if (NULL == p_api->adpt_ucast_priority_map_set)
        return SW_NOT_SUPPORTED;

    rv = p_api->adpt_ucast_priority_map_set(dev_id, priority_map);
    return rv;
}
sw_error_t
_fal_port_mcast_priority_class_set(
		a_uint32_t dev_id,
		fal_port_t port,
		fal_mcast_priority_map_t *pri_map)
{
    adpt_api_t *p_api;
	sw_error_t rv = SW_OK;

    SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

    if (NULL == p_api->adpt_port_mcast_priority_class_set)
        return SW_NOT_SUPPORTED;

    rv = p_api->adpt_port_mcast_priority_class_set(dev_id, port, pri_map);
    return rv;
}
sw_error_t
_fal_ucast_queue_map_set(
		a_uint32_t dev_id,
		fal_ucast_queue_map_t *queue_map)
{
    adpt_api_t *p_api;
	sw_error_t rv = SW_OK;

    SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

    if (NULL == p_api->adpt_ucast_queue_map_set)
        return SW_NOT_SUPPORTED;

    rv = p_api->adpt_ucast_queue_map_set(dev_id, queue_map);
    return rv;
}
sw_error_t
_fal_ucast_hash_map_get(
		a_uint32_t dev_id,
		fal_ucast_hash_map_t *hash_map)
{
    adpt_api_t *p_api;
	sw_error_t rv = SW_OK;

    SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

    if (NULL == p_api->adpt_ucast_hash_map_get)
        return SW_NOT_SUPPORTED;

    rv = p_api->adpt_ucast_hash_map_get(dev_id, hash_map);
    return rv;
}

sw_error_t
_fal_unicast_queue_ac_cfg_get(
		a_uint32_t dev_id,
		a_uint32_t queue_id,
		fal_uni_queue_ac_cfg_t *cfg)
{
	adpt_api_t *p_api;
	sw_error_t rv = SW_OK;

	SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

	if (NULL == p_api->adpt_unicast_queue_ac_cfg_get)
		return SW_NOT_SUPPORTED;

	rv = p_api->adpt_unicast_queue_ac_cfg_get(dev_id, queue_id, cfg);
	return rv;
}
sw_error_t
_fal_queue_flush(
		a_uint32_t dev_id,
		fal_port_t port,
		fal_queue_flush_dst_t *flush_dst)
{
	adpt_api_t *p_api;
	sw_error_t rv = SW_OK;

	SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

	if (NULL == p_api->adpt_queue_flush)
		return SW_NOT_SUPPORTED;

	rv = p_api->adpt_queue_flush(dev_id, port, flush_dst);
	return rv;
}
sw_error_t
_fal_unicast_queue_ac_cfg_set(
		a_uint32_t dev_id,
		a_uint32_t queue_id,
		fal_uni_queue_ac_cfg_t *cfg)
{
	adpt_api_t *p_api;
	sw_error_t rv = SW_OK;

	SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

	if (NULL == p_api->adpt_unicast_queue_ac_cfg_set)
		return SW_NOT_SUPPORTED;

	rv = p_api->adpt_unicast_queue_ac_cfg_set(dev_id, queue_id, cfg);
	return rv;
}
sw_error_t
_fal_group_ac_cfg_set(
		a_uint32_t dev_id,
		a_uint8_t group_id,
		fal_group_ac_cfg_t *cfg)
{
	adpt_api_t *p_api;
	sw_error_t rv = SW_OK;

	SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

	if (NULL == p_api->adpt_group_ac_cfg_set)
		return SW_NOT_SUPPORTED;

	rv = p_api->adpt_group_ac_cfg_set(dev_id, group_id, cfg);
	return rv;
}
sw_error_t
_fal_group_ac_cfg_get(
		a_uint32_t dev_id,
		a_uint8_t group_id,
		fal_group_ac_cfg_t *cfg)
{
	adpt_api_t *p_api;
	sw_error_t rv = SW_OK;

	SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

	if (NULL == p_api->adpt_group_ac_cfg_get)
		return SW_NOT_SUPPORTED;

	rv = p_api->adpt_group_ac_cfg_get(dev_id, group_id, cfg);
	return rv;
}
sw_error_t
_fal_multicast_queue_ac_cfg_get(
		a_uint32_t dev_id,
		a_uint32_t queue_id,
		fal_multi_queue_ac_cfg_t *cfg)
{
	adpt_api_t *p_api;
	sw_error_t rv = SW_OK;

	SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

	if (NULL == p_api->adpt_multicast_queue_ac_cfg_get)
		return SW_NOT_SUPPORTED;

	rv = p_api->adpt_multicast_queue_ac_cfg_get(dev_id, queue_id, cfg);
	return rv;
}
sw_error_t
_fal_multicast_queue_ac_cfg_set(
		a_uint32_t dev_id,
		a_uint32_t queue_id,
		fal_multi_queue_ac_cfg_t *cfg)
{
	adpt_api_t *p_api;
	sw_error_t rv = SW_OK;

	SW_RTN_ON_NULL(p_api = adpt_api_ptr_get(dev_id));

	if (NULL == p_api->adpt_multicast_queue_ac_cfg_set)
		return SW_NOT_SUPPORTED;

	rv = p_api->adpt_multicast_queue_ac_cfg_set(dev_id, queue_id, cfg);
	return rv;
}
/*insert flag for inner fal, don't remove it*/

sw_error_t
fal_mcast_queue_map_set(
		a_uint32_t dev_id,
		fal_mcast_queue_map_t *queue_map)
{
    sw_error_t rv = SW_OK;

    FAL_API_LOCK;
    rv = _fal_mcast_queue_map_set(dev_id, queue_map);
    FAL_API_UNLOCK;
    return rv;
}
sw_error_t
fal_ucast_priority_map_get(
		a_uint32_t dev_id,
		fal_ucast_priority_map_t *priority_map)
{
    sw_error_t rv = SW_OK;

    FAL_API_LOCK;
    rv = _fal_ucast_priority_map_get(dev_id, priority_map);
    FAL_API_UNLOCK;
    return rv;
}
sw_error_t
fal_ucast_hash_map_set(
		a_uint32_t dev_id,
		fal_ucast_hash_map_t *hash_map)
{
    sw_error_t rv = SW_OK;

    FAL_API_LOCK;
    rv = _fal_ucast_hash_map_set(dev_id, hash_map);
    FAL_API_UNLOCK;
    return rv;
}
sw_error_t
fal_port_mcast_priority_class_get(
		a_uint32_t dev_id,
		fal_port_t port,
		fal_mcast_priority_map_t *pri_map)
{
    sw_error_t rv = SW_OK;

    FAL_API_LOCK;
    rv = _fal_port_mcast_priority_class_get(dev_id, port, pri_map);
    FAL_API_UNLOCK;
    return rv;
}
sw_error_t
fal_ucast_default_hash_get(
		a_uint32_t dev_id,
		a_uint8_t *hash_value)
{
    sw_error_t rv = SW_OK;

    FAL_API_LOCK;
    rv = _fal_ucast_default_hash_get(dev_id, hash_value);
    FAL_API_UNLOCK;
    return rv;
}
sw_error_t
fal_ucast_queue_map_get(
		a_uint32_t dev_id,
		fal_ucast_queue_map_t *queue_map)
{
    sw_error_t rv = SW_OK;

    FAL_API_LOCK;
    rv = _fal_ucast_queue_map_get(dev_id, queue_map);
    FAL_API_UNLOCK;
    return rv;
}
sw_error_t
fal_ucast_default_hash_set(
		a_uint32_t dev_id,
		a_uint8_t hash_value)
{
    sw_error_t rv = SW_OK;

    FAL_API_LOCK;
    rv = _fal_ucast_default_hash_set(dev_id, hash_value);
    FAL_API_UNLOCK;
    return rv;
}
sw_error_t
fal_mcast_queue_map_get(
		a_uint32_t dev_id,
		fal_mcast_queue_map_t *queue_map)
{
    sw_error_t rv = SW_OK;

    FAL_API_LOCK;
    rv = _fal_mcast_queue_map_get(dev_id, queue_map);
    FAL_API_UNLOCK;
    return rv;
}
sw_error_t
fal_ucast_priority_map_set(
		a_uint32_t dev_id,
		fal_ucast_priority_map_t *priority_map)
{
    sw_error_t rv = SW_OK;

    FAL_API_LOCK;
    rv = _fal_ucast_priority_map_set(dev_id, priority_map);
    FAL_API_UNLOCK;
    return rv;
}
sw_error_t
fal_port_mcast_priority_class_set(
		a_uint32_t dev_id,
		fal_port_t port,
		fal_mcast_priority_map_t *pri_map)
{
    sw_error_t rv = SW_OK;

    FAL_API_LOCK;
    rv = _fal_port_mcast_priority_class_set(dev_id, port, pri_map);
    FAL_API_UNLOCK;
    return rv;
}
sw_error_t
fal_ucast_queue_map_set(
		a_uint32_t dev_id,
		fal_ucast_queue_map_t *queue_map)
{
    sw_error_t rv = SW_OK;

    FAL_API_LOCK;
    rv = _fal_ucast_queue_map_set(dev_id, queue_map);
    FAL_API_UNLOCK;
    return rv;
}
sw_error_t
fal_ucast_hash_map_get(
		a_uint32_t dev_id,
		fal_ucast_hash_map_t *hash_map)
{
    sw_error_t rv = SW_OK;

    FAL_API_LOCK;
    rv = _fal_ucast_hash_map_get(dev_id, hash_map);
    FAL_API_UNLOCK;
    return rv;
}

sw_error_t
fal_unicast_queue_ac_cfg_get(
		a_uint32_t dev_id,
		a_uint32_t queue_id,
		fal_uni_queue_ac_cfg_t *cfg)
{
	sw_error_t rv = SW_OK;

	FAL_API_LOCK;
	rv = _fal_unicast_queue_ac_cfg_get(dev_id, queue_id, cfg);
	FAL_API_UNLOCK;
	return rv;
}
sw_error_t
fal_queue_flush(
		a_uint32_t dev_id,
		fal_port_t port,
		fal_queue_flush_dst_t *flush_dst)
{
	sw_error_t rv = SW_OK;

	FAL_API_LOCK;
	rv = _fal_queue_flush(dev_id, port, flush_dst);
	FAL_API_UNLOCK;
	return rv;
}
sw_error_t
fal_unicast_queue_ac_cfg_set(
		a_uint32_t dev_id,
		a_uint32_t queue_id,
		fal_uni_queue_ac_cfg_t *cfg)
{
	sw_error_t rv = SW_OK;

	FAL_API_LOCK;
	rv = _fal_unicast_queue_ac_cfg_set(dev_id, queue_id, cfg);
	FAL_API_UNLOCK;
	return rv;
}
sw_error_t
fal_group_ac_cfg_set(
		a_uint32_t dev_id,
		a_uint8_t group_id,
		fal_group_ac_cfg_t *cfg)
{
	sw_error_t rv = SW_OK;

	FAL_API_LOCK;
	rv = _fal_group_ac_cfg_set(dev_id, group_id, cfg);
	FAL_API_UNLOCK;
	return rv;
}
sw_error_t
fal_group_ac_cfg_get(
		a_uint32_t dev_id,
		a_uint8_t group_id,
		fal_group_ac_cfg_t *cfg)
{
	sw_error_t rv = SW_OK;

	FAL_API_LOCK;
	rv = _fal_group_ac_cfg_get(dev_id, group_id, cfg);
	FAL_API_UNLOCK;
	return rv;
}
sw_error_t
fal_multicast_queue_ac_cfg_get(
		a_uint32_t dev_id,
		a_uint32_t queue_id,
		fal_multi_queue_ac_cfg_t *cfg)
{
	sw_error_t rv = SW_OK;

	FAL_API_LOCK;
	rv = _fal_multicast_queue_ac_cfg_get(dev_id, queue_id, cfg);
	FAL_API_UNLOCK;
	return rv;
}
sw_error_t
fal_multicast_queue_ac_cfg_set(
		a_uint32_t dev_id,
		a_uint32_t queue_id,
		fal_multi_queue_ac_cfg_t *cfg)
{
	sw_error_t rv = SW_OK;

	FAL_API_LOCK;
	rv = _fal_multicast_queue_ac_cfg_set(dev_id, queue_id, cfg);
	FAL_API_UNLOCK;
	return rv;
}
/*insert flag for outter fal, don't remove it*/
