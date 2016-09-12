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
#include "fal_bm.h"
#include "hppe_bm_reg.h"
#include "hppe_bm.h"
#include "adpt.h"

sw_error_t
adpt_hppe_port_bufgroup_map_get(a_uint32_t dev_id, fal_port_t port,
			a_uint8_t *group)
{
	sw_error_t rv = SW_OK;
	union port_group_id_u port_group_id;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(group);
	memset(&port_group_id, 0, sizeof(port_group_id));

	rv = hppe_port_group_id_get(dev_id, port, &port_group_id);
	if( rv != SW_OK )
		return rv;

	*group = port_group_id.bf.port_shared_group_id;

	return SW_OK;
}

sw_error_t
adpt_hppe_bm_port_reserved_buffer_get(a_uint32_t dev_id, fal_port_t port,
			a_uint16_t *prealloc_buff, a_uint16_t *react_buff)
{
	sw_error_t rv = SW_OK;
	union port_fc_cfg_u port_fc_cfg;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(prealloc_buff);
	ADPT_NULL_POINT_CHECK(react_buff);
	memset(&port_fc_cfg, 0, sizeof(port_fc_cfg));

	rv = hppe_port_fc_cfg_get(dev_id, port, &port_fc_cfg);
	if (rv)
		return rv;

	*prealloc_buff = port_fc_cfg.bf.port_pre_alloc;
	*react_buff = port_fc_cfg.bf.port_react_limit;

	return SW_OK;
}

sw_error_t
adpt_hppe_bm_bufgroup_buffer_get(a_uint32_t dev_id, a_uint8_t group,
			a_uint16_t *buff_num)
{
	sw_error_t rv = SW_OK;
	union shared_group_cfg_u shared_group_cfg;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(buff_num);
	memset(&shared_group_cfg, 0, sizeof(shared_group_cfg));

	rv = hppe_shared_group_cfg_get(dev_id, group, &shared_group_cfg);
	if( rv != SW_OK )
		return rv;

	*buff_num = shared_group_cfg.bf.shared_group_limit;

	return SW_OK;
}

sw_error_t
adpt_hppe_bm_port_dynamic_thresh_get(a_uint32_t dev_id, fal_port_t port,
			fal_bm_dynamic_cfg_t *cfg)
{
	sw_error_t rv = SW_OK;
	union port_fc_cfg_u port_fc_cfg;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(cfg);
	memset(&port_fc_cfg, 0, sizeof(port_fc_cfg));

	rv = hppe_port_fc_cfg_get(dev_id, port, &port_fc_cfg);
	if( rv != SW_OK )
		return rv;

	if (!port_fc_cfg.bf.port_shared_dynamic)
		return SW_FAIL;

	cfg->weight = port_fc_cfg.bf.port_shared_weight;
	cfg->shared_ceiling = port_fc_cfg.bf.port_shared_ceiling_0 |
				port_fc_cfg.bf.port_shared_ceiling_1 << 3;
	cfg->resume_off = port_fc_cfg.bf.port_resume_offset;
	cfg->resume_min_thresh = port_fc_cfg.bf.port_resume_floor_th;

	return SW_OK;
}

sw_error_t
adpt_hppe_port_bm_ctrl_get(a_uint32_t dev_id, fal_port_t port, a_bool_t *enable)
{
	sw_error_t rv = SW_OK;
	union port_fc_mode_u port_fc_mode;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(enable);
	memset(&port_fc_mode, 0, sizeof(port_fc_mode));

	rv = hppe_port_fc_mode_get(dev_id, port, &port_fc_mode);
	if( rv != SW_OK )
		return rv;

	*enable =  port_fc_mode.bf.fc_en;

	return SW_OK;
}

sw_error_t
adpt_hppe_bm_bufgroup_buffer_set(a_uint32_t dev_id, a_uint8_t group,
			a_uint16_t buff_num)
{
	sw_error_t rv = SW_OK;
	union shared_group_cfg_u shared_group_cfg;

	ADPT_DEV_ID_CHECK(dev_id);
	memset(&shared_group_cfg, 0, sizeof(shared_group_cfg));

	shared_group_cfg.bf.shared_group_limit = buff_num;
	rv = hppe_shared_group_cfg_set(dev_id, group, &shared_group_cfg);
	if( rv != SW_OK )
		return rv;

	return SW_OK;
}

sw_error_t
adpt_hppe_port_bufgroup_map_set(a_uint32_t dev_id, fal_port_t port,
			a_uint8_t group)
{
	sw_error_t rv = SW_OK;
	union port_group_id_u port_group_id;

	ADPT_DEV_ID_CHECK(dev_id);
	memset(&port_group_id, 0, sizeof(port_group_id));

	port_group_id.bf.port_shared_group_id = group;
	rv = hppe_port_group_id_set(dev_id, port, &port_group_id);
	if( rv != SW_OK )
		return rv;

	return SW_OK;
}

sw_error_t
adpt_hppe_bm_port_static_thresh_get(a_uint32_t dev_id, fal_port_t port,
			fal_bm_static_cfg_t *cfg)
{
	sw_error_t rv = SW_OK;
	union port_fc_cfg_u port_fc_cfg;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(cfg);
	memset(&port_fc_cfg, 0, sizeof(port_fc_cfg));

	rv = hppe_port_fc_cfg_get(dev_id, port, &port_fc_cfg);
	if( rv != SW_OK )
		return rv;

	if (port_fc_cfg.bf.port_shared_dynamic)
		return SW_FAIL;

	cfg->resume_off = port_fc_cfg.bf.port_resume_offset;
	cfg->max_thresh = port_fc_cfg.bf.port_shared_ceiling_0 |
			port_fc_cfg.bf.port_shared_ceiling_1 << 3;

	return SW_OK;
}

sw_error_t
adpt_hppe_bm_port_reserved_buffer_set(a_uint32_t dev_id, fal_port_t port,
			a_uint16_t prealloc_buff, a_uint16_t react_buff)
{
	sw_error_t rv = SW_OK;
	union port_fc_cfg_u port_fc_cfg;

	ADPT_DEV_ID_CHECK(dev_id);
	memset(&port_fc_cfg, 0, sizeof(port_fc_cfg));

	rv = hppe_port_fc_cfg_get(dev_id, port, &port_fc_cfg);
	if (rv)
		return rv;

	port_fc_cfg.bf.port_pre_alloc = prealloc_buff;
	port_fc_cfg.bf.port_react_limit = react_buff;

	return hppe_port_fc_cfg_set(dev_id, port, &port_fc_cfg);
}

sw_error_t
adpt_hppe_bm_port_static_thresh_set(a_uint32_t dev_id, fal_port_t port,
			fal_bm_static_cfg_t *cfg)
{
	sw_error_t rv = SW_OK;
	union port_fc_cfg_u port_fc_cfg;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(cfg);
	memset(&port_fc_cfg, 0, sizeof(port_fc_cfg));

	rv = hppe_port_fc_cfg_get(dev_id, port, &port_fc_cfg);
	if( rv != SW_OK )
		return rv;

	port_fc_cfg.bf.port_resume_offset = cfg->resume_off;
	port_fc_cfg.bf.port_shared_ceiling_0 = cfg->max_thresh;
	port_fc_cfg.bf.port_shared_ceiling_1 = cfg->max_thresh >> 3;
	port_fc_cfg.bf.port_shared_dynamic = 0;

	return hppe_port_fc_cfg_set(dev_id, port, &port_fc_cfg);;
}

sw_error_t
adpt_hppe_bm_port_dynamic_thresh_set(a_uint32_t dev_id, fal_port_t port,
			fal_bm_dynamic_cfg_t *cfg)
{
	sw_error_t rv = SW_OK;
	union port_fc_cfg_u port_fc_cfg;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(cfg);
	memset(&port_fc_cfg, 0, sizeof(port_fc_cfg));

	rv = hppe_port_fc_cfg_get(dev_id, port, &port_fc_cfg);
	if( rv != SW_OK )
		return rv;

	port_fc_cfg.bf.port_shared_weight = cfg->weight;
	port_fc_cfg.bf.port_shared_ceiling_0 = cfg->shared_ceiling;
	port_fc_cfg.bf.port_shared_ceiling_1 = cfg->shared_ceiling >> 3;
	port_fc_cfg.bf.port_resume_offset = cfg->resume_off;
	port_fc_cfg.bf.port_resume_floor_th = cfg->resume_min_thresh;
	port_fc_cfg.bf.port_shared_dynamic = 1;

	return hppe_port_fc_cfg_set(dev_id, port, &port_fc_cfg);;
}

sw_error_t
adpt_hppe_port_bm_ctrl_set(a_uint32_t dev_id, fal_port_t port, a_bool_t enable)
{
	union port_fc_mode_u port_fc_mode;

	ADPT_DEV_ID_CHECK(dev_id);
	memset(&port_fc_mode, 0, sizeof(port_fc_mode));

	port_fc_mode.bf.fc_en = enable;
	return hppe_port_fc_mode_set(dev_id, port, &port_fc_mode);
}

sw_error_t adpt_hppe_bm_init(a_uint32_t dev_id)
{
	adpt_api_t *p_adpt_api = NULL;

	p_adpt_api = adpt_api_ptr_get(dev_id);

	if(p_adpt_api == NULL)
		return SW_FAIL;

	p_adpt_api->adpt_port_bufgroup_map_get = adpt_hppe_port_bufgroup_map_get;
	p_adpt_api->adpt_bm_port_reserved_buffer_get = adpt_hppe_bm_port_reserved_buffer_get;
	p_adpt_api->adpt_bm_bufgroup_buffer_get = adpt_hppe_bm_bufgroup_buffer_get;
	p_adpt_api->adpt_bm_port_dynamic_thresh_get = adpt_hppe_bm_port_dynamic_thresh_get;
	p_adpt_api->adpt_port_bm_ctrl_get = adpt_hppe_port_bm_ctrl_get;
	p_adpt_api->adpt_bm_bufgroup_buffer_set = adpt_hppe_bm_bufgroup_buffer_set;
	p_adpt_api->adpt_port_bufgroup_map_set = adpt_hppe_port_bufgroup_map_set;
	p_adpt_api->adpt_bm_port_static_thresh_get = adpt_hppe_bm_port_static_thresh_get;
	p_adpt_api->adpt_bm_port_reserved_buffer_set = adpt_hppe_bm_port_reserved_buffer_set;
	p_adpt_api->adpt_bm_port_static_thresh_set = adpt_hppe_bm_port_static_thresh_set;
	p_adpt_api->adpt_bm_port_dynamic_thresh_set = adpt_hppe_bm_port_dynamic_thresh_set;
	p_adpt_api->adpt_port_bm_ctrl_set = adpt_hppe_port_bm_ctrl_set;


	return SW_OK;
}

/**
 * @}
 */