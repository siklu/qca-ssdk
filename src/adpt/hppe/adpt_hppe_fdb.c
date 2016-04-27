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

#define OP_TYPE_ADD	0x0
#define OP_TYPE_DEL	0x1
#define OP_TYPE_GET	0x2
#define OP_TYPE_FLUSH	0x4
#define OP_TYPE_AGE	0x5

#define OP_MODE_HASH	0x0
#define OP_MODE_INDEX	0x1

#define OP_CMD_ID_SIZE	0xf

#define OP_FIFO_CNT_SIZE	0x8

a_uint32_t
_adpt_hppe_fdb_get_entry_index(a_uint32_t dev_id, fal_fdb_entry_t * entry)
{
	a_uint32_t i;
	a_uint32_t tmp_reg0_value, tmp_reg1_value;
	union fdb_tbl_rd_op_u reg_val_rd_op;
	union fdb_tbl_rd_op_rslt_u reg_val_rd_op_rslt;

	tmp_reg0_value = 0;
	tmp_reg1_value = 0;
	for (i = 2; i < 6; i++)
		tmp_reg0_value = (tmp_reg0_value << 8) + entry->addr.uc[i];
	hppe_fdb_tbl_rd_op_data0_data_set(dev_id, tmp_reg0_value);

	for (i = 0; i < 2; i++)
		tmp_reg1_value = (tmp_reg1_value << 8) + entry->addr.uc[i];
	tmp_reg1_value = (entry->fid << (FDB_TBL_VSI_OFFSET - 32)) + tmp_reg1_value;
	hppe_fdb_tbl_rd_op_data1_data_set(dev_id, tmp_reg1_value);

	hppe_fdb_tbl_rd_op_data2_data_set(dev_id, 0x0);

	reg_val_rd_op.bf.cmd_id = 0x0;
	reg_val_rd_op.bf.byp_rslt_en = 0x0;
	reg_val_rd_op.bf.op_type = OP_TYPE_GET;
	reg_val_rd_op.bf.hash_block_bitmap = 0x3;
	reg_val_rd_op.bf.op_mode = OP_MODE_HASH;
	reg_val_rd_op.bf.entry_index = 0x0;
	hppe_fdb_tbl_rd_op_set(dev_id, &reg_val_rd_op);

	hppe_fdb_tbl_rd_op_rslt_get(dev_id, &reg_val_rd_op_rslt);

	if (tmp_reg0_value == 0x0 && tmp_reg1_value == 0x0)
	{
		if (reg_val_rd_op_rslt.bf.cmd_id != 0x0 || reg_val_rd_op_rslt.bf.valid_cnt >= OP_FIFO_CNT_SIZE)
			return SW_FAIL;
		return reg_val_rd_op_rslt.bf.entry_index;
	}
	else
	{
		if (reg_val_rd_op_rslt.bf.op_rslt != SW_OK || reg_val_rd_op_rslt.bf.cmd_id != 0x0 ||
			reg_val_rd_op_rslt.bf.valid_cnt >= OP_FIFO_CNT_SIZE)
			return SW_FAIL;
		return reg_val_rd_op_rslt.bf.entry_index;
	}
}

sw_error_t
_adpt_hppe_fdb_extend_first_next(a_uint32_t dev_id, fal_fdb_entry_t * entry)
{
	a_uint32_t rslt_data0, rslt_data1, rslt_data2;
	a_uint32_t entry_valid, lookup_valid;
	a_uint32_t entry_index, i, dst_info_encode;
	union fdb_tbl_rd_op_u reg_val_rd_op;
	union fdb_tbl_rd_op_rslt_u reg_val_rd_op_rslt;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(entry);

	entry_index = _adpt_hppe_fdb_get_entry_index(dev_id, entry);
	if (entry_index == SW_FAIL)
		return SW_FAIL;

	if (entry_index != 0)
		entry_index += 1;

	hppe_fdb_tbl_rd_op_data0_data_set(dev_id, 0x0);
	hppe_fdb_tbl_rd_op_data1_data_set(dev_id, 0x0);
	hppe_fdb_tbl_rd_op_data2_data_set(dev_id, 0x0);

	for (; entry_index < FDB_TBL_NUM; entry_index++)
	{
		reg_val_rd_op.bf.cmd_id = entry_index % OP_CMD_ID_SIZE;
		reg_val_rd_op.bf.byp_rslt_en = 0x0;
		reg_val_rd_op.bf.op_type = OP_TYPE_GET;
		reg_val_rd_op.bf.hash_block_bitmap = 0x3;
		reg_val_rd_op.bf.op_mode = OP_MODE_INDEX;
		reg_val_rd_op.bf.entry_index = entry_index;
		hppe_fdb_tbl_rd_op_set(dev_id, &reg_val_rd_op);

		hppe_fdb_tbl_rd_op_rslt_get(dev_id, &reg_val_rd_op_rslt);
		if (reg_val_rd_op_rslt.bf.op_rslt != SW_OK || reg_val_rd_op_rslt.bf.cmd_id != reg_val_rd_op.bf.cmd_id ||
			reg_val_rd_op_rslt.bf.valid_cnt >= OP_FIFO_CNT_SIZE)
			return SW_FAIL;

		hppe_fdb_tbl_rd_op_rslt_data0_data_get(dev_id, &rslt_data0);
		hppe_fdb_tbl_rd_op_rslt_data1_data_get(dev_id, &rslt_data1);
		hppe_fdb_tbl_rd_op_rslt_data2_data_get(dev_id, &rslt_data2);

		entry_valid = (rslt_data1 >> (FDB_TBL_ENTRY_VALID_OFFSET - 32)) & 0x1;
		lookup_valid = (rslt_data1 >> (FDB_TBL_LOOKUP_VALID_OFFSET - 32)) & 0x1;
		dst_info_encode = (rslt_data2 >> (FDB_TBL_DST_INFO_OFFSET + 12 -64)) & 0x3;

		if (entry_valid == 0x0 || lookup_valid == 0x0 || dst_info_encode == 0x0)
		{
			continue;
		}
		else
		{
			entry->entry_valid = entry_valid;
			entry->lookup_valid = lookup_valid;
			entry->fid = (rslt_data1 >> (FDB_TBL_VSI_OFFSET - 32)) & 0x1f;
			entry->sacmd = (rslt_data2 >> (FDB_TBL_SA_CMD_OFFSET - 64)) & 0x3;
			entry->dacmd = (rslt_data2 >> (FDB_TBL_DA_CMD_OFFSET - 64)) & 0x3;
			if (((rslt_data2 >> (FDB_TBL_HIT_AGE_OFFSET - 64)) & 0x3) == 0x3)
				entry->static_en = A_TRUE;
			else
				entry->static_en = A_FALSE;
			if (dst_info_encode == 0x1)
			{
				entry->nexthop_en = A_TRUE;
				entry->portmap_en = A_FALSE;
				entry->port.nexthop = ((rslt_data2 & 0x7) << 9) + ((rslt_data1 >> (FDB_TBL_DST_INFO_OFFSET - 32)) & 0x1ff);
			}
			else if (dst_info_encode == 0x2)
			{
				entry->nexthop_en = A_FALSE;
				entry->portmap_en = A_FALSE;
				entry->port.id = ((rslt_data2 & 0x7) << 9) + ((rslt_data1 >> (FDB_TBL_DST_INFO_OFFSET - 32)) & 0x1ff);
			}
			else
			{
				entry->portmap_en = A_TRUE;
				entry->nexthop_en = A_FALSE;
				entry->port.map = ((rslt_data2 & 0x7) << 9) + ((rslt_data1 >> (FDB_TBL_DST_INFO_OFFSET - 32)) & 0x1ff);
			}
			for (i = 2; i < 6; i++)
				entry->addr.uc[i] = (rslt_data0 >> ((5 - i) << 3)) & 0xff;
			for (i = 0; i < 2; i++)
				entry->addr.uc[i] = (rslt_data1 >> ((1 - i) << 3)) & 0xff;
			break;
		}
	}

	if (entry_index == FDB_TBL_NUM)
		return SW_NO_MORE;

	return SW_OK;
}

sw_error_t
adpt_hppe_fdb_first(a_uint32_t dev_id, fal_fdb_entry_t * entry)
{

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

	a_uint32_t i;
	a_uint32_t tmp_reg0_value, tmp_reg1_value, tmp_reg2_value, port_value, dst_type;
	union fdb_tbl_op_u reg_val_op;
	union fdb_tbl_op_rslt_u reg_val_op_rslt;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(entry);

	tmp_reg0_value = tmp_reg1_value = tmp_reg2_value = 0;
	for (i = 2; i < 6; i++)
		tmp_reg0_value = (tmp_reg0_value << 8) + entry->addr.uc[i];
	hppe_fdb_tbl_op_data0_data_set(dev_id, tmp_reg0_value);

	for (i = 0; i < 2; i++)
		tmp_reg1_value = (tmp_reg1_value << 8) + entry->addr.uc[i];
	tmp_reg1_value = (0x1 << (FDB_TBL_ENTRY_VALID_OFFSET - 32)) + (0x1 << (FDB_TBL_LOOKUP_VALID_OFFSET -32)) +
		(entry->fid << (FDB_TBL_VSI_OFFSET - 32)) + tmp_reg1_value;
	dst_type = 0x0;
	if (entry->nexthop_en == A_TRUE)
	{
		port_value = entry->port.nexthop;
		dst_type = 0x1;
	}
	else if (entry->portmap_en == A_TRUE)
	{
		port_value = entry->port.map;
		dst_type = 0x3;
	}
	else
	{
		port_value = entry->port.id;
		dst_type = 0x2;
	}
	tmp_reg1_value = ((port_value & 0x1ff) << (FDB_TBL_DST_INFO_OFFSET - 32)) + tmp_reg1_value;
	hppe_fdb_tbl_op_data1_data_set(dev_id, tmp_reg1_value);

	tmp_reg2_value = ((port_value >> 0x9) & 0x7) + ((dst_type & 0x3) << 3) +
		((entry->sacmd & 0x3) << (FDB_TBL_SA_CMD_OFFSET - 64)) +
		((entry->dacmd & 0x3) << (FDB_TBL_DA_CMD_OFFSET - 64));
	if (entry->static_en == A_TRUE)
		tmp_reg2_value = (0x3 << (FDB_TBL_HIT_AGE_OFFSET - 64)) + tmp_reg2_value;
	else
		tmp_reg2_value = (0x2 << (FDB_TBL_HIT_AGE_OFFSET - 64)) + tmp_reg2_value;
	hppe_fdb_tbl_op_data2_data_set(dev_id, tmp_reg2_value);

	reg_val_op.bf.cmd_id = 0x0;
	reg_val_op.bf.byp_rslt_en = 0x0;
	reg_val_op.bf.op_type = OP_TYPE_ADD;
	reg_val_op.bf.hash_block_bitmap = 0x3;
	reg_val_op.bf.op_mode = OP_MODE_HASH;
	reg_val_op.bf.entry_index = 0x0;
	hppe_fdb_tbl_op_set(dev_id, &reg_val_op);

	hppe_fdb_tbl_op_rslt_get(dev_id, &reg_val_op_rslt);

	if (reg_val_op_rslt.bf.op_rslt != SW_OK || reg_val_op_rslt.bf.cmd_id != 0x0 ||
		reg_val_op_rslt.bf.valid_cnt >= OP_FIFO_CNT_SIZE)
		return SW_FAIL;

	return SW_OK;
}

sw_error_t
adpt_hppe_fdb_del_by_port(a_uint32_t dev_id, a_uint32_t port_id, a_uint32_t flag)
{

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
adpt_hppe_fdb_del_all(a_uint32_t dev_id, a_uint32_t flag)
{

	ADPT_DEV_ID_CHECK(dev_id);

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
adpt_hppe_fdb_find(a_uint32_t dev_id, fal_fdb_entry_t * entry)
{
	a_uint32_t rslt_data0, rslt_data1, rslt_data2;
	a_uint32_t entry_valid, lookup_valid;
	a_uint32_t entry_index, i, dst_info_encode;
	union fdb_tbl_rd_op_u reg_val_rd_op;
	union fdb_tbl_rd_op_rslt_u reg_val_rd_op_rslt;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(entry);

	entry_index = _adpt_hppe_fdb_get_entry_index(dev_id, entry);
	if (entry_index == SW_FAIL || entry_index == 0)
		return SW_FAIL;

	hppe_fdb_tbl_rd_op_data0_data_set(dev_id, 0x0);
	hppe_fdb_tbl_rd_op_data1_data_set(dev_id, 0x0);
	hppe_fdb_tbl_rd_op_data2_data_set(dev_id, 0x0);

	reg_val_rd_op.bf.cmd_id = entry_index % OP_CMD_ID_SIZE;
	reg_val_rd_op.bf.byp_rslt_en = 0x0;
	reg_val_rd_op.bf.op_type = OP_TYPE_GET;
	reg_val_rd_op.bf.hash_block_bitmap = 0x3;
	reg_val_rd_op.bf.op_mode = OP_MODE_INDEX;
	reg_val_rd_op.bf.entry_index = entry_index;
	hppe_fdb_tbl_rd_op_set(dev_id, &reg_val_rd_op);

	hppe_fdb_tbl_rd_op_rslt_get(dev_id, &reg_val_rd_op_rslt);
	if (reg_val_rd_op_rslt.bf.op_rslt != SW_OK || reg_val_rd_op_rslt.bf.cmd_id != reg_val_rd_op.bf.cmd_id ||
		reg_val_rd_op_rslt.bf.valid_cnt >= OP_FIFO_CNT_SIZE)
		return SW_FAIL;

	hppe_fdb_tbl_rd_op_rslt_data0_data_get(dev_id, &rslt_data0);
	hppe_fdb_tbl_rd_op_rslt_data1_data_get(dev_id, &rslt_data1);
	hppe_fdb_tbl_rd_op_rslt_data2_data_get(dev_id, &rslt_data2);

	entry_valid = (rslt_data1 >> (FDB_TBL_ENTRY_VALID_OFFSET - 32)) & 0x1;
	lookup_valid = (rslt_data1 >> (FDB_TBL_LOOKUP_VALID_OFFSET - 32)) & 0x1;
	dst_info_encode = (rslt_data2 >> (FDB_TBL_DST_INFO_OFFSET + 12 -64)) & 0x3;

	if (entry_valid == 0x0 || lookup_valid == 0x0 || dst_info_encode == 0x0)
	{
		return SW_FAIL;
	}
	else
	{
		entry->entry_valid = entry_valid;
		entry->lookup_valid = lookup_valid;
		entry->fid = (rslt_data1 >> (FDB_TBL_VSI_OFFSET - 32)) & 0x1f;
		entry->sacmd = (rslt_data2 >> (FDB_TBL_SA_CMD_OFFSET - 64)) & 0x3;
		entry->dacmd = (rslt_data2 >> (FDB_TBL_DA_CMD_OFFSET - 64)) & 0x3;
		if (((rslt_data2 >> (FDB_TBL_HIT_AGE_OFFSET - 64)) & 0x3) == 0x3)
			entry->static_en = A_TRUE;
		else
			entry->static_en = A_FALSE;
		if (dst_info_encode == 0x1)
		{
			entry->portmap_en = A_FALSE;
			entry->nexthop_en = A_TRUE;
			entry->port.nexthop = ((rslt_data2 & 0x7) << 9) + ((rslt_data1 >> (FDB_TBL_DST_INFO_OFFSET - 32)) & 0x1ff);
		}
		else if (dst_info_encode = 0x2)
		{
			entry->nexthop_en = A_FALSE;
			entry->portmap_en = A_FALSE;
			entry->port.id = ((rslt_data2 & 0x7) << 9) + ((rslt_data1 >> (FDB_TBL_DST_INFO_OFFSET - 32)) & 0x1ff);
		}
		else
		{
			entry->portmap_en = A_TRUE;
			entry->nexthop_en = A_FALSE;
			entry->port.map = ((rslt_data2 & 0x7) << 9) + ((rslt_data1 >> (FDB_TBL_DST_INFO_OFFSET - 32)) & 0x1ff);
		}
		for (i = 2; i < 6; i++)
			entry->addr.uc[i] = (rslt_data0 >> ((5 - i) << 3)) & 0xff;
		for (i = 0; i < 2; i++)
			entry->addr.uc[i] = (rslt_data1 >> ((1 - i) << 3)) & 0xff;
	}

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
adpt_hppe_fdb_age_time_set(a_uint32_t dev_id, a_uint32_t * time)
{
	union age_timer_u age_timer = {0};
	a_uint32_t data;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(time);

	if ((65535 * 7 < *time) || (7 > *time))
		return SW_BAD_PARAM;

	data = *time / 7;
	*time = data * 7;

	age_timer.bf.age_val = *time;

	return hppe_age_timer_set(dev_id, &age_timer);
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

	*time = age_timer.bf.age_val * 7;

	return SW_OK;
}

sw_error_t
adpt_hppe_fdb_extend_first(a_uint32_t dev_id, fal_fdb_op_t * option,
                         fal_fdb_entry_t * entry)
{
	sw_error_t rv = SW_OK;
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(option);
	ADPT_NULL_POINT_CHECK(entry);

	rv = _adpt_hppe_fdb_extend_first_next(dev_id, entry);
	if (rv != SW_OK)
		return rv;

	return SW_OK;
}

sw_error_t
adpt_hppe_fdb_extend_next(a_uint32_t dev_id, fal_fdb_op_t * option,
                        fal_fdb_entry_t * entry)
{
	sw_error_t rv = SW_OK;
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(option);
	ADPT_NULL_POINT_CHECK(entry);

	rv = _adpt_hppe_fdb_extend_first_next(dev_id, entry);
	if (rv != SW_OK)
		return rv;

	return SW_OK;
}

sw_error_t
adpt_hppe_fdb_age_mode_set(a_uint32_t dev_id, a_uint32_t age_mode)
{
	sw_error_t rv = SW_OK;
	union l2_global_conf_u l2_global_conf = {0};

	ADPT_DEV_ID_CHECK(dev_id);

	rv = hppe_l2_global_conf_get(dev_id, &l2_global_conf);

	if( rv != SW_OK )
		return rv;

	l2_global_conf.bf.age_ctrl_mode = age_mode;

	rv = hppe_l2_global_conf_set(dev_id, &l2_global_conf);

	if( rv != SW_OK )
		return rv;

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
adpt_hppe_fdb_learn_ctrl_set(a_uint32_t dev_id, a_bool_t enable)
{
	sw_error_t rv = SW_OK;
	union l2_global_conf_u l2_global_conf = {0};

	ADPT_DEV_ID_CHECK(dev_id);

	rv = hppe_l2_global_conf_get(dev_id, &l2_global_conf);

	if( rv != SW_OK )
		return rv;

	l2_global_conf.bf.lrn_en = enable;

	rv = hppe_l2_global_conf_set(dev_id, &l2_global_conf);

	if( rv != SW_OK )
		return rv;

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
adpt_hppe_port_fdb_learn_limit_set(a_uint32_t dev_id, fal_port_t port_id,
                                 a_bool_t enable, a_uint32_t cnt)
{
	sw_error_t rv = SW_OK;
	union port_lrn_limit_ctrl_u port_lrn_limit_ctrl = {0};

	ADPT_DEV_ID_CHECK(dev_id);

	rv = hppe_port_lrn_limit_ctrl_get(dev_id, port_id, &port_lrn_limit_ctrl);

	if( rv != SW_OK )
		return rv;

	port_lrn_limit_ctrl.bf.lrn_lmt_en = enable;
	port_lrn_limit_ctrl.bf.lrn_lmt_cnt = cnt;

	rv = hppe_port_lrn_limit_ctrl_set(dev_id, port_id, &port_lrn_limit_ctrl);

	if( rv != SW_OK )
		return rv;

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
adpt_hppe_fdb_learn_mode_set(a_uint32_t dev_id, a_uint32_t learn_mode)
{
	sw_error_t rv = SW_OK;
	union l2_global_conf_u l2_global_conf = {0};


	ADPT_DEV_ID_CHECK(dev_id);

	rv = hppe_l2_global_conf_get(dev_id, &l2_global_conf);

	if( rv != SW_OK )
		return rv;

	l2_global_conf.bf.lrn_ctrl_mode = learn_mode;

	rv = hppe_l2_global_conf_set(dev_id, &l2_global_conf);

	if( rv != SW_OK )
		return rv;

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

	*learn_mode = l2_global_conf.bf.lrn_ctrl_mode;

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
adpt_hppe_fdb_port_del(a_uint32_t dev_id, a_uint32_t fid, fal_mac_addr_t * addr, fal_port_t port_id)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(addr);

	return SW_OK;
}

sw_error_t
adpt_hppe_fdb_port_learn_set(a_uint32_t dev_id, fal_port_t port_id, a_bool_t enable)
{
	sw_error_t rv = SW_OK;
	union port_bridge_ctrl_u port_bridge_ctrl = {0};

	ADPT_DEV_ID_CHECK(dev_id);

	rv = hppe_port_bridge_ctrl_get(dev_id, port_id, &port_bridge_ctrl);

	if( rv != SW_OK )
		return rv;

	port_bridge_ctrl.bf.new_addr_lrn_en = enable;

	rv = hppe_port_bridge_ctrl_set(dev_id, port_id, &port_bridge_ctrl);

	if( rv != SW_OK )
		return rv;

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
adpt_hppe_port_fdb_learn_exceed_cmd_set(a_uint32_t dev_id, fal_port_t port_id,
                                      fal_fwd_cmd_t cmd)
{
	union port_lrn_limit_ctrl_u port_lrn_limit_ctrl = {0};

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
adpt_hppe_fdb_age_ctrl_set(a_uint32_t dev_id, a_bool_t enable)
{
	sw_error_t rv = SW_OK;
	union l2_global_conf_u l2_global_conf = {0};

	ADPT_DEV_ID_CHECK(dev_id);

	rv = hppe_l2_global_conf_get(dev_id, &l2_global_conf);

	if( rv != SW_OK )
		return rv;

	l2_global_conf.bf.age_en = enable;

	rv = hppe_l2_global_conf_set(dev_id, &l2_global_conf);

	if( rv != SW_OK )
		return rv;

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
	p_adpt_api->adpt_fdb_del_by_port = adpt_hppe_fdb_del_by_port;
	p_adpt_api->adpt_fdb_del_by_mac = adpt_hppe_fdb_del_by_mac;
	p_adpt_api->adpt_fdb_del_all = adpt_hppe_fdb_del_all;
	p_adpt_api->adpt_fdb_transfer = adpt_hppe_fdb_transfer;
	p_adpt_api->adpt_fdb_find = adpt_hppe_fdb_find;
	p_adpt_api->adpt_fdb_iterate = adpt_hppe_fdb_iterate;
	p_adpt_api->adpt_fdb_age_time_set = adpt_hppe_fdb_age_time_set;
	p_adpt_api->adpt_fdb_age_time_get = adpt_hppe_fdb_age_time_get;
	p_adpt_api->adpt_fdb_extend_first = adpt_hppe_fdb_extend_first;
	p_adpt_api->adpt_fdb_extend_next = adpt_hppe_fdb_extend_next;
	p_adpt_api->adpt_fdb_age_mode_set = adpt_hppe_fdb_age_mode_set;
	p_adpt_api->adpt_fdb_age_mode_get = adpt_hppe_fdb_age_mode_get;
	p_adpt_api->adpt_fdb_learn_ctrl_set = adpt_hppe_fdb_learn_ctrl_set;
	p_adpt_api->adpt_fdb_learn_ctrl_get = adpt_hppe_fdb_learn_ctrl_get;
	p_adpt_api->adpt_port_fdb_learn_limit_set = adpt_hppe_port_fdb_learn_limit_set;
	p_adpt_api->adpt_port_fdb_learn_limit_get = adpt_hppe_port_fdb_learn_limit_get;
	p_adpt_api->adpt_fdb_learn_mode_set = adpt_hppe_fdb_learn_mode_set;
	p_adpt_api->adpt_fdb_learn_mode_get = adpt_hppe_fdb_learn_mode_get;
	p_adpt_api->adpt_fdb_port_add = adpt_hppe_fdb_port_add;
	p_adpt_api->adpt_fdb_port_del = adpt_hppe_fdb_port_del;
	p_adpt_api->adpt_fdb_port_learn_set = adpt_hppe_fdb_port_learn_set;
	p_adpt_api->adpt_fdb_port_learn_get = adpt_hppe_fdb_port_learn_get;
	p_adpt_api->adpt_port_fdb_learn_counter_get = adpt_hppe_port_fdb_learn_counter_get;
	p_adpt_api->adpt_port_fdb_learn_exceed_cmd_set = adpt_hppe_port_fdb_learn_exceed_cmd_set;
	p_adpt_api->adpt_port_fdb_learn_exceed_cmd_get = adpt_hppe_port_fdb_learn_exceed_cmd_get;
	p_adpt_api->adpt_fdb_age_ctrl_set = adpt_hppe_fdb_age_ctrl_set;
	p_adpt_api->adpt_fdb_age_ctrl_get = adpt_hppe_fdb_age_ctrl_get;

	return SW_OK;
}

/**
 * @}
 */

