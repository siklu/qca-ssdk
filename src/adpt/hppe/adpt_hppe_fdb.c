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
#include "hppe_fdb.h"
#include "hppe_fdb_reg.h"
#include "adpt.h"

sw_error_t
adpt_hppe_fdb_first(a_uint32_t dev_id, fal_fdb_entry_t * entry)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(entry);

	return SW_OK;
}
sw_error_t
adpt_hppe_fdb_resv_add(a_uint32_t dev_id, fal_fdb_entry_t * entry)
{
	union rfdb_tbl_u rfdb_tbl = {0};

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(entry);

	return SW_OK;
}
sw_error_t
adpt_hppe_fdb_next(a_uint32_t dev_id, fal_fdb_entry_t * entry)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(entry);

	return SW_OK;
}
sw_error_t
adpt_hppe_fdb_add(a_uint32_t dev_id, const fal_fdb_entry_t * entry)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(entry);

	return SW_OK;
}
sw_error_t
adpt_hppe_fdb_age_time_set(a_uint32_t dev_id, a_uint32_t * time)
{
	union age_timer_u age_timer = {0};

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(time);

	age_timer.bf.age_val = *time;

	return hppe_age_timer_set(dev_id, &age_timer);
}
sw_error_t
adpt_hppe_fdb_resv_del(a_uint32_t dev_id, fal_fdb_entry_t * entry)
{
	union rfdb_tbl_u rfdb_tbl = {0};

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(entry);

	return SW_OK;
}
sw_error_t
adpt_hppe_fdb_extend_next(a_uint32_t dev_id, fal_fdb_op_t * option,
                        fal_fdb_entry_t * entry)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(option);
	ADPT_NULL_POINT_CHECK(entry);

	return SW_OK;
}
sw_error_t
adpt_hppe_fdb_age_mode_get(a_uint32_t dev_id, a_uint32_t * age_mode)
{
	sw_error_t rv = SW_OK;
	union l2_global_conf_u l2_global_conf = {0};

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(age_mode);


	rv = hppe_l2_global_conf_get(dev_id, &l2_global_conf);

	if( rv != SW_OK )
		return rv;

	*age_mode = l2_global_conf.bf.age_ctrl_mode;

	return SW_OK;
}

sw_error_t
adpt_hppe_fdb_resv_iterate(a_uint32_t dev_id, a_uint32_t * iterator, fal_fdb_entry_t * entry)
{
	union rfdb_tbl_u rfdb_tbl = {0};

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(iterator);
	ADPT_NULL_POINT_CHECK(entry);
	return SW_OK;
}
sw_error_t
adpt_hppe_fdb_learn_ctrl_get(a_uint32_t dev_id, a_bool_t * enable)
{
	sw_error_t rv = SW_OK;
	union l2_global_conf_u l2_global_conf = {0};

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(enable);


	rv = hppe_l2_global_conf_get(dev_id, &l2_global_conf);

	if( rv != SW_OK )
		return rv;

	*enable = l2_global_conf.bf.lrn_en;

	return SW_OK;
}

sw_error_t
adpt_hppe_fdb_age_time_get(a_uint32_t dev_id, a_uint32_t * time)
{
	sw_error_t rv = SW_OK;
	union age_timer_u age_timer = {0};

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(time);


	rv = hppe_age_timer_get(dev_id, &age_timer);

	if( rv != SW_OK )
		return rv;

	*time = age_timer.bf.age_val;
	return SW_OK;
}

sw_error_t
adpt_hppe_port_fdb_learn_limit_set(a_uint32_t dev_id, fal_port_t port_id,
                                 a_bool_t enable, a_uint32_t cnt)
{
	union port_lrn_limit_ctrl_u port_lrn_limit_ctrl = {0};

	ADPT_DEV_ID_CHECK(dev_id);

	return SW_OK;
}
sw_error_t
adpt_hppe_fdb_learn_mode_set(a_uint32_t dev_id, a_uint32_t learn_mode)
{
	union l2_global_conf_u l2_global_conf = {0};

	ADPT_DEV_ID_CHECK(dev_id);

	return SW_OK;
}
sw_error_t
adpt_hppe_fdb_port_add(a_uint32_t dev_id, a_uint32_t fid, fal_mac_addr_t * addr, fal_port_t port_id)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(addr);

	return SW_OK;
}
sw_error_t
adpt_hppe_fdb_port_learn_set(a_uint32_t dev_id, fal_port_t port_id, a_bool_t enable)
{
	union port_bridge_ctrl_u port_bridge_ctrl = {0};

	ADPT_DEV_ID_CHECK(dev_id);

	return SW_OK;
}
sw_error_t
adpt_hppe_fdb_resv_find(a_uint32_t dev_id, fal_fdb_entry_t * entry)
{
	union rfdb_tbl_u rfdb_tbl = {0};

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(entry);

	return SW_OK;
}
sw_error_t
adpt_hppe_fdb_port_learn_get(a_uint32_t dev_id, fal_port_t port_id, a_bool_t *enable)
{
	sw_error_t rv = SW_OK;
	union port_bridge_ctrl_u port_bridge_ctrl = {0};

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(enable);


	rv = hppe_port_bridge_ctrl_get(dev_id, port_id, &port_bridge_ctrl);

	if( rv != SW_OK )
		return rv;

	*enable = port_bridge_ctrl.bf.new_addr_lrn_en;

	return SW_OK;
}

sw_error_t
adpt_hppe_port_fdb_learn_counter_get(a_uint32_t dev_id, fal_port_t port_id,
                                  a_uint32_t * cnt)
{
	sw_error_t rv = SW_OK;
	union port_lrn_limit_counter_u port_lrn_limit_counter = {0};

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(cnt);


	rv = hppe_port_lrn_limit_counter_get(dev_id, port_id, &port_lrn_limit_counter);

	if( rv != SW_OK )
		return rv;

	cnt = port_lrn_limit_counter.bf.lrn_cnt;

	return SW_OK;
}

sw_error_t
adpt_hppe_fdb_extend_first(a_uint32_t dev_id, fal_fdb_op_t * option,
                         fal_fdb_entry_t * entry)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(option);
	ADPT_NULL_POINT_CHECK(entry);

	return SW_OK;
}
sw_error_t
adpt_hppe_fdb_transfer(a_uint32_t dev_id, fal_port_t old_port, fal_port_t new_port,
                     a_uint32_t fid, fal_fdb_op_t * option)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(option);

	return SW_OK;
}
sw_error_t
adpt_hppe_fdb_port_del(a_uint32_t dev_id, a_uint32_t fid, fal_mac_addr_t * addr, fal_port_t port_id)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(addr);

	return SW_OK;
}
sw_error_t
adpt_hppe_fdb_find(a_uint32_t dev_id, fal_fdb_entry_t * entry)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(entry);

	return SW_OK;
}
sw_error_t
adpt_hppe_fdb_learn_ctrl_set(a_uint32_t dev_id, a_bool_t enable)
{
	union l2_global_conf_u l2_global_conf = {0};

	ADPT_DEV_ID_CHECK(dev_id);
	return SW_OK;
}
sw_error_t
adpt_hppe_port_fdb_learn_exceed_cmd_get(a_uint32_t dev_id, fal_port_t port_id,
                                      fal_fwd_cmd_t * cmd)
{
	sw_error_t rv = SW_OK;
	union port_lrn_limit_ctrl_u port_lrn_limit_ctrl = {0};

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(cmd);


	rv = hppe_port_lrn_limit_ctrl_get(dev_id, port_id, &port_lrn_limit_ctrl);

	if( rv != SW_OK )
		return rv;

	*cmd = port_lrn_limit_ctrl.bf.lrn_lmt_exceed_fwd;

	return SW_OK;
}

sw_error_t
adpt_hppe_fdb_del_by_port(a_uint32_t dev_id, a_uint32_t port_id, a_uint32_t flag)
{

	ADPT_DEV_ID_CHECK(dev_id);

	return SW_OK;
}
sw_error_t
adpt_hppe_port_fdb_learn_limit_get(a_uint32_t dev_id, fal_port_t port_id,
                                 a_bool_t * enable, a_uint32_t * cnt)
{
	sw_error_t rv = SW_OK;
	union port_lrn_limit_ctrl_u port_lrn_limit_ctrl = {0};

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(enable);
	ADPT_NULL_POINT_CHECK(cnt);


	rv = hppe_port_lrn_limit_ctrl_get(dev_id, port_id, &port_lrn_limit_ctrl);

	if( rv != SW_OK )
		return rv;

	*enable = port_lrn_limit_ctrl.bf.lrn_lmt_en;
	*cnt = port_lrn_limit_ctrl.bf.lrn_lmt_cnt;

	return SW_OK;
}

sw_error_t
adpt_hppe_fdb_age_ctrl_set(a_uint32_t dev_id, a_bool_t enable)
{
	union l2_global_conf_u l2_global_conf = {0};

	ADPT_DEV_ID_CHECK(dev_id);

	return SW_OK;
}
sw_error_t
adpt_hppe_fdb_del_by_mac(a_uint32_t dev_id, const fal_fdb_entry_t *entry)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(entry);

	return SW_OK;
}
sw_error_t
adpt_hppe_fdb_iterate(a_uint32_t dev_id, a_uint32_t * iterator, fal_fdb_entry_t * entry)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(iterator);
	ADPT_NULL_POINT_CHECK(entry);

	return SW_OK;
}
sw_error_t
adpt_hppe_fdb_learn_mode_get(a_uint32_t dev_id, a_uint32_t * learn_mode)
{
	sw_error_t rv = SW_OK;
	union l2_global_conf_u l2_global_conf = {0};

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(learn_mode);


	rv = hppe_l2_global_conf_get(dev_id, &l2_global_conf);

	if( rv != SW_OK )
		return rv;



	return SW_OK;
}

sw_error_t
adpt_hppe_port_fdb_learn_exceed_cmd_set(a_uint32_t dev_id, fal_port_t port_id,
                                      fal_fwd_cmd_t cmd)
{
	union port_lrn_limit_ctrl_u port_lrn_limit_ctrl = {0};

	ADPT_DEV_ID_CHECK(dev_id);

	return SW_OK;
}
sw_error_t
adpt_hppe_fdb_age_mode_set(a_uint32_t dev_id, a_uint32_t age_mode)
{
	union l2_global_conf_u l2_global_conf = {0};

	ADPT_DEV_ID_CHECK(dev_id);

	return SW_OK;
}
sw_error_t
adpt_hppe_fdb_del_all(a_uint32_t dev_id, a_uint32_t flag)
{

	ADPT_DEV_ID_CHECK(dev_id);

	return SW_OK;
}
sw_error_t
adpt_hppe_fdb_age_ctrl_get(a_uint32_t dev_id, a_bool_t * enable)
{
	sw_error_t rv = SW_OK;
	union l2_global_conf_u l2_global_conf = {0};

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(enable);


	rv = hppe_l2_global_conf_get(dev_id, &l2_global_conf);

	if( rv != SW_OK )
		return rv;

	*enable = l2_global_conf.bf.age_en;

	return SW_OK;
}

sw_error_t adpt_hppe_fdb_init(a_uint32_t dev_id)
{
	adpt_api_t *p_adpt_api = NULL;

	p_adpt_api = adpt_api_ptr_get(dev_id);

	if(p_adpt_api == NULL)
		return SW_FAIL;

	p_adpt_api->adpt_fdb_first = adpt_hppe_fdb_first;
	p_adpt_api->adpt_fdb_next = adpt_hppe_fdb_next;
	p_adpt_api->adpt_fdb_add = adpt_hppe_fdb_add;
	p_adpt_api->adpt_fdb_age_time_set = adpt_hppe_fdb_age_time_set;
	p_adpt_api->adpt_fdb_extend_next = adpt_hppe_fdb_extend_next;
	p_adpt_api->adpt_fdb_age_mode_get = adpt_hppe_fdb_age_mode_get;
	p_adpt_api->adpt_fdb_learn_ctrl_get = adpt_hppe_fdb_learn_ctrl_get;
	p_adpt_api->adpt_fdb_age_time_get = adpt_hppe_fdb_age_time_get;
	p_adpt_api->adpt_port_fdb_learn_limit_set = adpt_hppe_port_fdb_learn_limit_set;
	p_adpt_api->adpt_fdb_learn_mode_set = adpt_hppe_fdb_learn_mode_set;
	p_adpt_api->adpt_fdb_port_add = adpt_hppe_fdb_port_add;
	p_adpt_api->adpt_fdb_port_learn_set = adpt_hppe_fdb_port_learn_set;
	p_adpt_api->adpt_fdb_port_learn_get = adpt_hppe_fdb_port_learn_get;
	p_adpt_api->adpt_port_fdb_learn_counter_get = adpt_hppe_port_fdb_learn_counter_get;
	p_adpt_api->adpt_fdb_extend_first = adpt_hppe_fdb_extend_first;
	p_adpt_api->adpt_fdb_transfer = adpt_hppe_fdb_transfer;
	p_adpt_api->adpt_fdb_port_del = adpt_hppe_fdb_port_del;
	p_adpt_api->adpt_fdb_find = adpt_hppe_fdb_find;
	p_adpt_api->adpt_fdb_learn_ctrl_set = adpt_hppe_fdb_learn_ctrl_set;
	p_adpt_api->adpt_port_fdb_learn_exceed_cmd_get = adpt_hppe_port_fdb_learn_exceed_cmd_get;
	p_adpt_api->adpt_fdb_del_by_port = adpt_hppe_fdb_del_by_port;
	p_adpt_api->adpt_port_fdb_learn_limit_get = adpt_hppe_port_fdb_learn_limit_get;
	p_adpt_api->adpt_fdb_age_ctrl_set = adpt_hppe_fdb_age_ctrl_set;
	p_adpt_api->adpt_fdb_del_by_mac = adpt_hppe_fdb_del_by_mac;
	p_adpt_api->adpt_fdb_iterate = adpt_hppe_fdb_iterate;
	p_adpt_api->adpt_fdb_learn_mode_get = adpt_hppe_fdb_learn_mode_get;
	p_adpt_api->adpt_port_fdb_learn_exceed_cmd_set = adpt_hppe_port_fdb_learn_exceed_cmd_set;
	p_adpt_api->adpt_fdb_age_mode_set = adpt_hppe_fdb_age_mode_set;
	p_adpt_api->adpt_fdb_del_all = adpt_hppe_fdb_del_all;
	p_adpt_api->adpt_fdb_age_ctrl_get = adpt_hppe_fdb_age_ctrl_get;


	return SW_OK;
}

/**
 * @}
 */
