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

#define ARL_FIRST_ENTRY		0x0
#define ARL_NEXT_ENTRY		0x1
#define ARL_EXTENDFIRST_ENTRY	0x2
#define ARL_EXTENDNEXT_ENTRY	0x3

/*
 * set values to register FDB_TBL_OP
 */
sw_error_t
_adpt_hppe_fdb_tbl_op_reg_set(a_uint32_t dev_id, a_uint32_t cmd_id, a_uint32_t op_type)
{
	sw_error_t rv = SW_OK;
	union fdb_tbl_op_u reg_val_op;
	a_uint32_t op_mode = OP_MODE_HASH;
	a_uint32_t entry_index = 0x0;

	reg_val_op.bf.cmd_id = cmd_id;
	reg_val_op.bf.byp_rslt_en = 0x0;
	reg_val_op.bf.op_type = op_type;
	reg_val_op.bf.hash_block_bitmap = 0x3;
	reg_val_op.bf.op_mode = op_mode;
	reg_val_op.bf.entry_index = entry_index;
	rv = hppe_fdb_tbl_op_set(dev_id, &reg_val_op);

	return rv;
}

/*
 * get results from register FDB_TBL_OP_RSLT
 */
sw_error_t
_adpt_hppe_fdb_tbl_op_rslt_reg_get(a_uint32_t dev_id, a_uint32_t cmd_id)
{
	sw_error_t rv = SW_OK;
	union fdb_tbl_op_rslt_u reg_val_op_rslt;

	rv = hppe_fdb_tbl_op_rslt_get(dev_id, &reg_val_op_rslt);

	if (rv != SW_OK || reg_val_op_rslt.bf.op_rslt != SW_OK || reg_val_op_rslt.bf.cmd_id != cmd_id ||
			reg_val_op_rslt.bf.valid_cnt >= OP_FIFO_CNT_SIZE)
	{
		return SW_FAIL;
	}

	return SW_OK;
}

/*
 * set values to register FDB_TBL_RD_OP
 */
sw_error_t
_adpt_hppe_fdb_tbl_rd_op_reg_set(a_uint32_t dev_id, a_uint32_t cmd_id, a_uint32_t op_mode, a_uint32_t entry_index)
{
	sw_error_t rv = SW_OK;
	union fdb_tbl_rd_op_u reg_val_rd_op;
	a_uint32_t op_type = OP_TYPE_GET;

	reg_val_rd_op.bf.cmd_id = cmd_id;
	reg_val_rd_op.bf.byp_rslt_en = 0x0;
	reg_val_rd_op.bf.op_type = op_type;
	reg_val_rd_op.bf.hash_block_bitmap = 0x3;
	reg_val_rd_op.bf.op_mode = op_mode;
	reg_val_rd_op.bf.entry_index = entry_index;
	rv = hppe_fdb_tbl_rd_op_set(dev_id, &reg_val_rd_op);

	return rv;
}

/*
 * get results from register FDB_TBL_RD_OP_RSLT
 */
sw_error_t
_adpt_hppe_fdb_tbl_rd_op_rslt_reg_get(a_uint32_t dev_id, a_uint32_t cmd_id, a_uint32_t *entry_index)
{
	sw_error_t rv = SW_OK;
	union fdb_tbl_rd_op_rslt_u reg_val_rd_op_rslt;

	rv = hppe_fdb_tbl_rd_op_rslt_get(dev_id, &reg_val_rd_op_rslt);

	if (rv != SW_OK || (*entry_index !=0 && reg_val_rd_op_rslt.bf.op_rslt != SW_OK) ||
			reg_val_rd_op_rslt.bf.cmd_id != cmd_id || reg_val_rd_op_rslt.bf.valid_cnt >= OP_FIFO_CNT_SIZE)
	{
		return SW_FAIL;
	}

	*entry_index = reg_val_rd_op_rslt.bf.entry_index;

	return SW_OK;
}

/*
 * set values to register FDB_TBL_OP_DATA0/FDB_TBL_OP_DATA1/FDB_TBL_OP_DATA2
 */
sw_error_t
_adpt_hppe_fdb_tbl_op_data_reg_set(a_uint32_t dev_id, fal_fdb_entry_t * entry)
{
	sw_error_t rv = SW_OK;
	a_uint32_t i, port_value, dst_type = 0x0;
	a_uint32_t reg_value[3] = {0};

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(entry);

	for (i = 2; i < 6; i++)
	{
		reg_value[0] = (reg_value[0] << 8) + entry->addr.uc[i];
	}
	rv = hppe_fdb_tbl_op_data0_data_set(dev_id, reg_value[0]);
	if (rv != SW_OK)
		return rv;

	for (i = 0; i < 2; i++)
	{
		reg_value[1] = (reg_value[1] << 8) + entry->addr.uc[i];
	}
	reg_value[1] += (0x1 << (FDB_TBL_ENTRY_VALID_OFFSET - 32)) + (0x1 << (FDB_TBL_LOOKUP_VALID_OFFSET -32)) +
			(entry->fid << (FDB_TBL_VSI_OFFSET - 32));
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
	reg_value[1] += ((port_value & 0x1ff) << (FDB_TBL_DST_INFO_OFFSET - 32));
	rv = hppe_fdb_tbl_op_data1_data_set(dev_id, reg_value[1]);
	if (rv != SW_OK)
		return rv;

	reg_value[2] = ((port_value >> 0x9) & 0x7) + ((dst_type & 0x3) << 3) +
			((entry->sacmd & 0x3) << (FDB_TBL_SA_CMD_OFFSET - 64)) +
			((entry->dacmd & 0x3) << (FDB_TBL_DA_CMD_OFFSET - 64));
	if (entry->static_en == A_TRUE)
		reg_value[2] += (0x3 << (FDB_TBL_HIT_AGE_OFFSET - 64));
	else
		reg_value[2] += (0x2 << (FDB_TBL_HIT_AGE_OFFSET - 64));
	rv = hppe_fdb_tbl_op_data2_data_set(dev_id, reg_value[2]);
	if (rv != SW_OK)
		return rv;

	return SW_OK;
}

/*
 * set values to register FDB_TBL_RD_OP_DATA0/FDB_TBL_RD_OP_DATA1/FDB_TBL_RD_OP_DATA2
 */
sw_error_t
_adpt_hppe_fdb_tbl_rd_op_data_reg_set(a_uint32_t dev_id, fal_fdb_entry_t * entry)
{
	sw_error_t rv = SW_OK;
	a_uint32_t i, reg_value[3] = {0};

	for (i = 2; i < 6; i++)
	{
		reg_value[0] = (reg_value[0] << 8) + entry->addr.uc[i];
	}
	rv = hppe_fdb_tbl_rd_op_data0_data_set(dev_id, reg_value[0]);
	if (rv != SW_OK)
		return rv;

	for (i = 0; i < 2; i++)
	{
		reg_value[1] = (reg_value[1] << 8) + entry->addr.uc[i];
	}
	reg_value[1] += (entry->fid << (FDB_TBL_VSI_OFFSET - 32));
	rv = hppe_fdb_tbl_rd_op_data1_data_set(dev_id, reg_value[1]);
	if (rv != SW_OK)
		return rv;

	rv = hppe_fdb_tbl_rd_op_data2_data_set(dev_id, reg_value[2]);
	if (rv != SW_OK)
		return rv;

	return SW_OK;
}

/*
 * get values from register FDB_TBL_RD_OP_RSLT_DATA0/FDB_TBL_RD_OP_RSLT_DATA1/FDB_TBL_RD_OP_RSLT_DATA2
 */
sw_error_t
_adpt_hppe_fdb_tbl_rd_op_rslt_data_reg_get(a_uint32_t dev_id, fal_fdb_entry_t * entry)
{
	a_uint32_t rslt_data[3];
	a_uint32_t entry_valid, lookup_valid;
	a_uint32_t i, dst_info_encode;

	hppe_fdb_tbl_rd_op_rslt_data0_data_get(dev_id, &rslt_data[0]);
	hppe_fdb_tbl_rd_op_rslt_data1_data_get(dev_id, &rslt_data[1]);
	hppe_fdb_tbl_rd_op_rslt_data2_data_get(dev_id, &rslt_data[2]);

	entry_valid = (rslt_data[1] >> (FDB_TBL_ENTRY_VALID_OFFSET - 32)) & 0x1;
	lookup_valid = (rslt_data[1] >> (FDB_TBL_LOOKUP_VALID_OFFSET - 32)) & 0x1;
	dst_info_encode = (rslt_data[2] >> (FDB_TBL_DST_INFO_OFFSET + 12 -64)) & 0x3;

	if (entry_valid == 0x0 || lookup_valid == 0x0 || dst_info_encode == 0x0)
	{
		return SW_NOT_FOUND;
	}
	else
	{
		entry->entry_valid = A_TRUE;
		entry->lookup_valid = A_TRUE;
		entry->fid = (rslt_data[1] >> (FDB_TBL_VSI_OFFSET - 32)) & 0x1f;
		entry->sacmd = (rslt_data[2] >> (FDB_TBL_SA_CMD_OFFSET - 64)) & 0x3;
		entry->dacmd = (rslt_data[2] >> (FDB_TBL_DA_CMD_OFFSET - 64)) & 0x3;
		if (((rslt_data[2] >> (FDB_TBL_HIT_AGE_OFFSET - 64)) & 0x3) == 0x3)
			entry->static_en = A_TRUE;
		else
			entry->static_en = A_FALSE;
		if (dst_info_encode == 0x1)
		{
			entry->nexthop_en = A_TRUE;
			entry->portmap_en = A_FALSE;
			entry->port.nexthop = ((rslt_data[2] & 0x7) << 9) + ((rslt_data[1] >> (FDB_TBL_DST_INFO_OFFSET - 32)) & 0x1ff);
		}
		else if (dst_info_encode == 0x2)
		{
			entry->nexthop_en = A_FALSE;
			entry->portmap_en = A_FALSE;
			entry->port.id = ((rslt_data[2] & 0x7) << 9) + ((rslt_data[1] >> (FDB_TBL_DST_INFO_OFFSET - 32)) & 0x1ff);
		}
		else
		{
			entry->portmap_en = A_TRUE;
			entry->nexthop_en = A_FALSE;
			entry->port.map = ((rslt_data[2] & 0x7) << 9) + ((rslt_data[1] >> (FDB_TBL_DST_INFO_OFFSET - 32)) & 0x1ff);
		}
		for (i = 2; i < 6; i++)
			entry->addr.uc[i] = (rslt_data[0] >> ((5 - i) << 3)) & 0xff;
		for (i = 0; i < 2; i++)
			entry->addr.uc[i] = (rslt_data[1] >> ((1 - i) << 3)) & 0xff;
	}

	return SW_OK;
}

sw_error_t
_get_fdb_table_entryindex_by_entry(a_uint32_t dev_id, fal_fdb_entry_t * entry,
		a_uint32_t *entry_index, a_uint32_t cmd_id)
{
	sw_error_t rv = SW_OK;
	a_uint32_t init_entry_index = 0;

	rv = _adpt_hppe_fdb_tbl_rd_op_data_reg_set(dev_id, entry);
	if (rv != SW_OK)
		return rv;

	rv = _adpt_hppe_fdb_tbl_rd_op_reg_set(dev_id, cmd_id, OP_MODE_HASH, init_entry_index);
	if (rv != SW_OK)
		return rv;

	rv = _adpt_hppe_fdb_tbl_rd_op_rslt_reg_get(dev_id, cmd_id, entry_index);
	if (rv != SW_OK)
		return rv;

	return SW_OK;
}

sw_error_t
_get_fdb_table_entry_by_entryindex(a_uint32_t dev_id, fal_fdb_entry_t * entry,
		a_uint32_t entry_index, a_uint32_t cmd_id)
{
	sw_error_t rv = SW_OK;
	fal_fdb_entry_t init_entry;
	a_uint32_t rslt_entry_index = 0;

	aos_mem_zero(&init_entry, sizeof (fal_fdb_entry_t));
	rv = _adpt_hppe_fdb_tbl_rd_op_data_reg_set(dev_id, &init_entry);
	if (rv != SW_OK)
		return rv;

	rv = _adpt_hppe_fdb_tbl_rd_op_reg_set(dev_id, cmd_id, OP_MODE_INDEX, entry_index);
	if (rv != SW_OK)
		return rv;

	rv = _adpt_hppe_fdb_tbl_rd_op_rslt_reg_get(dev_id, cmd_id, &rslt_entry_index);
	if (rv != SW_OK)
		return rv;

	rv = _adpt_hppe_fdb_tbl_rd_op_rslt_data_reg_get(dev_id, entry);
	if (rv != SW_OK)
		return rv;

	return SW_OK;
}

sw_error_t
_modify_fdb_table_entry(a_uint32_t dev_id, fal_fdb_entry_t * entry, a_uint32_t op_type,
	a_uint32_t cmd_id)
{
	sw_error_t rv = SW_OK;

	rv = _adpt_hppe_fdb_tbl_op_data_reg_set(dev_id, entry);
	if (rv != SW_OK)
		return rv;

	rv = _adpt_hppe_fdb_tbl_op_reg_set(dev_id, cmd_id, op_type);
	if (rv != SW_OK)
		return rv;

	rv = _adpt_hppe_fdb_tbl_op_rslt_reg_get(dev_id, cmd_id);
	if (rv != SW_OK)
		return rv;

	return SW_OK;
}

sw_error_t
_adpt_hppe_fdb_extend_first_next(a_uint32_t dev_id, fal_fdb_entry_t * entry, fal_fdb_op_t * option, a_uint32_t hwop)
{
	sw_error_t rv;
	a_uint32_t cmd_id = 0x0;
	a_uint32_t entry_index = 0x0;
	fal_fdb_entry_t ori_entry;

	if (hwop == ARL_EXTENDFIRST_ENTRY || hwop == ARL_EXTENDNEXT_ENTRY)
	{
		ori_entry.portmap_en = entry->portmap_en;
		ori_entry.nexthop_en = entry->nexthop_en;
		ori_entry.port.id = entry->port.id;
		ori_entry.fid = entry->fid;
	}

	if (hwop == ARL_FIRST_ENTRY || hwop == ARL_EXTENDFIRST_ENTRY)
		aos_mem_zero(entry, sizeof (fal_fdb_entry_t));

	rv = _get_fdb_table_entryindex_by_entry(dev_id, entry, &entry_index, cmd_id);
	if (rv != SW_OK)
		return rv;

	if (entry->entry_valid == A_TRUE || entry_index > 0)
		entry_index += 1;

	for (; entry_index < FDB_TBL_NUM; entry_index++)
	{
		cmd_id = entry_index % OP_CMD_ID_SIZE;
		rv = _get_fdb_table_entry_by_entryindex(dev_id, entry, entry_index, cmd_id);
		if (rv == SW_NOT_FOUND)
			continue;
		else if (rv == SW_OK)
		{
			if (hwop == ARL_EXTENDFIRST_ENTRY || hwop == ARL_EXTENDNEXT_ENTRY)
			{
				if (option->fid_en == A_TRUE && ori_entry.fid != entry->fid)
					continue;
				if (option->port_en == A_TRUE && !(ori_entry.portmap_en == entry->portmap_en &&
					ori_entry.nexthop_en == entry->nexthop_en && ori_entry.port.id == entry->port.id))
					continue;
			}
			break;
		}
		else
			return rv;
	}

	if (entry_index == FDB_TBL_NUM)
		return SW_NO_MORE;
	return SW_OK;
}

sw_error_t
adpt_hppe_fdb_first(a_uint32_t dev_id, fal_fdb_entry_t * entry)
{
	fal_fdb_op_t option;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(entry);

	aos_mem_zero(&option, sizeof (fal_fdb_op_t));

	return _adpt_hppe_fdb_extend_first_next(dev_id, entry, &option, ARL_FIRST_ENTRY);
}

sw_error_t
adpt_hppe_fdb_next(a_uint32_t dev_id, fal_fdb_entry_t * entry)
{
	fal_fdb_op_t option;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(entry);

	aos_mem_zero(&option, sizeof (fal_fdb_op_t));

	return _adpt_hppe_fdb_extend_first_next(dev_id, entry, &option, ARL_NEXT_ENTRY);
}

sw_error_t
adpt_hppe_fdb_add(a_uint32_t dev_id, const fal_fdb_entry_t * entry)
{
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(entry);

	return _modify_fdb_table_entry(dev_id, entry, OP_TYPE_ADD, 0x0);
}

sw_error_t
adpt_hppe_fdb_del_by_port(a_uint32_t dev_id, a_uint32_t port_id, a_uint32_t flag)
{
	a_uint32_t entry_index, id, cmd_id = 0;
	sw_error_t rv = SW_OK;
	fal_fdb_entry_t entry;

	ADPT_DEV_ID_CHECK(dev_id);

	for (entry_index = 0; entry_index < FDB_TBL_NUM; entry_index++)
	{
		cmd_id = entry_index % OP_CMD_ID_SIZE;
		aos_mem_zero(&entry, sizeof (fal_fdb_entry_t));
		rv = _get_fdb_table_entry_by_entryindex(dev_id, &entry, entry_index, cmd_id);

		if (rv == SW_NOT_FOUND)
			continue;
		else if (rv == SW_OK)
		{
			if (entry.nexthop_en == A_TRUE)
			{
				continue;
			}
			else if (entry.portmap_en == A_TRUE)
			{
				if (((entry.port.map >> port_id) & 0x1) == 1)
				{
					if ((flag == 0 && entry.static_en == A_FALSE) || flag == 1)
					{
						id = entry.port.map & (~(0x1 << port_id));
						if (id == 0)
						{
							rv = adpt_hppe_fdb_del_by_mac(dev_id, &entry);
							if (rv != SW_OK)
								return rv;
						}
						else
						{
							entry.port.map &= (~(0x1 << port_id));
							rv = adpt_hppe_fdb_add(dev_id, &entry);
							if (rv != SW_OK)
								return rv;
						}
					}
				}
			}
			else
			{
				if (entry.port.id == port_id &&
					((flag == 0 && entry.static_en == A_FALSE) || flag == 1))
				{
					rv = adpt_hppe_fdb_del_by_mac(dev_id, &entry);
					if (rv != SW_OK)
						return rv;
				}
			}
		}
		else
			return rv;
	}

	return SW_OK;
}

sw_error_t
adpt_hppe_fdb_del_by_mac(a_uint32_t dev_id, const fal_fdb_entry_t *entry)
{
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(entry);

	return _modify_fdb_table_entry(dev_id, entry, OP_TYPE_DEL, 0x0);
}

sw_error_t
adpt_hppe_fdb_del_all(a_uint32_t dev_id, a_uint32_t flag)
{
	sw_error_t rv;
	fal_fdb_entry_t entry;
	a_uint32_t entry_index = 0, cmd_id;

	ADPT_DEV_ID_CHECK(dev_id);

	if (flag == 1)
	{
		aos_mem_zero(&entry, sizeof (fal_fdb_entry_t));
		return _modify_fdb_table_entry(dev_id, &entry, OP_TYPE_FLUSH, 0x0);
	}
	else
	{
		for (entry_index = 0; entry_index < FDB_TBL_NUM; entry_index++)
		{
			cmd_id = entry_index % OP_CMD_ID_SIZE;
			aos_mem_zero(&entry, sizeof (fal_fdb_entry_t));
			rv = _get_fdb_table_entry_by_entryindex(dev_id, &entry, entry_index, cmd_id);
			if (rv != SW_OK)
				return rv;

			if (entry.static_en == A_FALSE)
			{
				rv = adpt_hppe_fdb_del_by_mac(dev_id, &entry);
				if (rv != SW_OK)
					return rv;
			}
		}
	}

	return SW_OK;
}

sw_error_t
adpt_hppe_fdb_transfer(a_uint32_t dev_id, fal_port_t old_port, fal_port_t new_port,
                     a_uint32_t fid, fal_fdb_op_t * option)
{
	a_uint32_t entry_index, cmd_id = 0;
	sw_error_t rv = SW_OK;
	fal_fdb_entry_t entry;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(option);

	if (option->port_en == A_TRUE)
		return SW_NOT_SUPPORTED;

	for (entry_index = 0; entry_index < FDB_TBL_NUM; entry_index++)
	{
		cmd_id = entry_index % OP_CMD_ID_SIZE;
		aos_mem_zero(&entry, sizeof (fal_fdb_entry_t));
		rv = _get_fdb_table_entry_by_entryindex(dev_id, &entry, entry_index, cmd_id);

		if (rv == SW_NOT_FOUND)
			continue;
		else if (rv == SW_OK)
		{
			if (option->fid_en == A_TRUE && entry.fid != fid)
				continue;
			if (entry.nexthop_en == A_TRUE)
			{
				continue;
			}
			else if (entry.portmap_en == A_TRUE)
			{
				if (((entry.port.map >> old_port) & 0x1) == 1)
				{
					entry.port.map &= (~(0x1 << old_port));
					entry.port.map |= (0x1 << new_port);
					rv = adpt_hppe_fdb_add(dev_id, &entry);
					if (rv != SW_OK)
						return rv;
				}
			}
			else
			{
				if (entry.port.id == old_port)
				{
					entry.port.id = new_port;
					rv = adpt_hppe_fdb_add(dev_id, &entry);
					if (rv != SW_OK)
						return rv;
				}
			}
		}
		else
			return rv;
	}

	return SW_OK;
}

sw_error_t
adpt_hppe_fdb_find(a_uint32_t dev_id, fal_fdb_entry_t * entry)
{
	sw_error_t rv;
	a_uint32_t cmd_id = 0x0;
	a_uint32_t entry_index = 0x0;

	rv = _get_fdb_table_entryindex_by_entry(dev_id, entry, &entry_index, cmd_id);
	if (rv != SW_OK)
		return rv;

	cmd_id = entry_index % OP_CMD_ID_SIZE;

	return _get_fdb_table_entry_by_entryindex(dev_id, entry, entry_index, cmd_id);
}

sw_error_t
adpt_hppe_fdb_iterate(a_uint32_t dev_id, a_uint32_t * iterator, fal_fdb_entry_t * entry)
{
	sw_error_t rv;
	a_uint32_t cmd_id = 0x0;
	a_uint32_t entry_index = 0x0;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(iterator);
	ADPT_NULL_POINT_CHECK(entry);

	for (entry_index = *iterator; entry_index < FDB_TBL_NUM; entry_index++)
	{
		cmd_id = entry_index % OP_CMD_ID_SIZE;
		rv = _get_fdb_table_entry_by_entryindex(dev_id, entry, entry_index, cmd_id);
		if (rv == SW_NOT_FOUND)
			continue;
		else if (rv == SW_OK)
			break;
		else
			return rv;
	}

	if (entry_index == FDB_TBL_NUM)
		return SW_NO_MORE;

	*iterator = entry_index + 1;
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

	age_timer.bf.age_val = data;

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
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(option);
	ADPT_NULL_POINT_CHECK(entry);

	return _adpt_hppe_fdb_extend_first_next(dev_id, entry, option, ARL_EXTENDFIRST_ENTRY);
}

sw_error_t
adpt_hppe_fdb_extend_next(a_uint32_t dev_id, fal_fdb_op_t * option,
                        fal_fdb_entry_t * entry)
{
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(option);
	ADPT_NULL_POINT_CHECK(entry);

	return _adpt_hppe_fdb_extend_first_next(dev_id, entry, option, ARL_EXTENDNEXT_ENTRY);
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

	return hppe_l2_global_conf_set(dev_id, &l2_global_conf);
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

	return hppe_l2_global_conf_set(dev_id, &l2_global_conf);
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

	return hppe_port_lrn_limit_ctrl_set(dev_id, port_id, &port_lrn_limit_ctrl);
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

	return hppe_l2_global_conf_set(dev_id, &l2_global_conf);
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
	sw_error_t rv = SW_OK;
	fal_fdb_entry_t entry;
	int i, cmd_id = 0x0, entry_index = 0x0, id;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(addr);

	aos_mem_zero(&entry, sizeof (fal_fdb_entry_t));

	entry.fid = fid;
	for (i = 0; i < 6; i++)
		entry.addr.uc[i] = addr->uc[i];

	rv = _get_fdb_table_entryindex_by_entry(dev_id, &entry, &entry_index, cmd_id);
	if (rv != SW_OK)
		return rv;

	cmd_id = entry_index % OP_CMD_ID_SIZE;
	rv = _get_fdb_table_entry_by_entryindex(dev_id, &entry, entry_index, cmd_id);
	if (rv != SW_OK)
		return rv;

	if (entry.nexthop_en == A_TRUE)
	{
		return SW_FAIL;
	}
	else if (entry.portmap_en == A_TRUE)
	{
		if (port_id >= 12)
			return SW_FAIL;
		entry.port.map |= (0x1 << port_id);
	}
	else
	{
		if (port_id >= 12 || entry.port.id >= 12)
			return SW_FAIL;
		entry.portmap_en = A_TRUE;
		entry.nexthop_en = A_FALSE;
		id = entry.port.id;
		entry.port.map = 0;
		entry.port.map |= (0x1 << id);
		entry.port.map |= (0x1 << port_id);
	}

	return adpt_hppe_fdb_add(dev_id, &entry);
}

sw_error_t
adpt_hppe_fdb_port_del(a_uint32_t dev_id, a_uint32_t fid, fal_mac_addr_t * addr, fal_port_t port_id)
{
	sw_error_t rv = SW_OK;
	fal_fdb_entry_t entry;
	int i, cmd_id = 0x0, entry_index = 0x0, id;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(addr);

	aos_mem_zero(&entry, sizeof (fal_fdb_entry_t));

	entry.fid = fid;
	for (i = 0; i < 6; i++)
		entry.addr.uc[i] = addr->uc[i];

	rv = _get_fdb_table_entryindex_by_entry(dev_id, &entry, &entry_index, cmd_id);
	if (rv != SW_OK)
		return rv;

	cmd_id = entry_index % OP_CMD_ID_SIZE;
	rv = _get_fdb_table_entry_by_entryindex(dev_id, &entry, entry_index, cmd_id);
	if (rv != SW_OK)
		return rv;

	if (entry.nexthop_en == A_TRUE)
	{
		rv = SW_FAIL;
	}
	else if (entry.portmap_en == A_TRUE)
	{
		if (((entry.port.map >> port_id) & 0x1) == 1)
		{
			id = entry.port.map & (~(0x1 << port_id));
			if (id == 0)
			{
				rv = adpt_hppe_fdb_del_by_mac(dev_id, &entry);
			}
			else
			{
				entry.port.map &= (~(0x1 << port_id));
				rv = adpt_hppe_fdb_add(dev_id, &entry);
			}
		}
	}
	else
	{
		if (entry.port.id == port_id)
			rv = adpt_hppe_fdb_del_by_mac(dev_id, &entry);
	}

	return rv;
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

	return hppe_port_bridge_ctrl_set(dev_id, port_id, &port_bridge_ctrl);
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
	sw_error_t rv = SW_OK;
	union port_lrn_limit_ctrl_u port_lrn_limit_ctrl = {0};

	ADPT_DEV_ID_CHECK(dev_id);

	rv = hppe_port_lrn_limit_ctrl_get(dev_id, port_id, &port_lrn_limit_ctrl);

	if( rv != SW_OK )
		return rv;

	port_lrn_limit_ctrl.bf.lrn_lmt_exceed_fwd = cmd;

	return hppe_port_lrn_limit_ctrl_set(dev_id, port_id, &port_lrn_limit_ctrl);
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

	return hppe_l2_global_conf_set(dev_id, &l2_global_conf);
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

