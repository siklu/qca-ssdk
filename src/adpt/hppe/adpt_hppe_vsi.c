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
#include "fal_type.h"
#include "adpt.h"
#include "hppe_vsi_reg.h"
#include "hppe_vsi.h"
#include "hppe_portvlan_reg.h"
#include "hppe_portvlan.h"
#include "hppe_ip_reg.h"
#include "hppe_ip.h"

#define ADPT_VSI_MAX 31
#define ADPT_VSI_RESERVE_MAX 5

enum{
	ADPT_VSI_ADD,
	ADPT_VSI_DEL
};
typedef struct ADPT_VLAN_INFO_T {
	a_uint32_t vlan_id;
	a_uint32_t vport_bitmap; /*vlan based vsi*/
	struct ADPT_VLAN_INFO_T *pNext;
} adpt_vlan_info_t;

typedef struct{
	a_uint32_t valid;
	a_uint32_t pport_bitmap; /*port based vsi*/
	adpt_vlan_info_t *pHead;
} adpt_vsi_t;

#define ADPT_VSI_ALL_VLAN 0xffff
#define ADPT_VSI_PPORT_NR 6
#define ADPT_VSI_DELETE 0xffff

static adpt_vsi_t adpt_vsi_mapping[SW_MAX_NR_DEV][ADPT_VSI_MAX+1];
static a_uint32_t default_port_vsi[ADPT_VSI_PPORT_NR+1] ={0, 0, 1, 2, 3, 4, 5};/*PPORT + CPU*/

static sw_error_t
_adpt_hppe_vsi_member_update(a_uint32_t dev_id,	a_uint32_t vsi_id,
				fal_port_t port_id, a_uint32_t op)
{
	sw_error_t rv;
	union vsi_tbl_u vsi_tbl;

	rv = hppe_vsi_tbl_get( dev_id, vsi_id, &vsi_tbl);
	if( rv != SW_OK )
		return rv;
	if( ADPT_VSI_ADD == op )
	{
		vsi_tbl.bf.bc_bitmap &= (!(1<<port_id));
		vsi_tbl.bf.member_port_bitmap &= (!(1<<port_id));
		vsi_tbl.bf.umc_bitmap &= (!(1<<port_id));
		vsi_tbl.bf.uuc_bitmap &= (!(1<<port_id));
	}
	else if( ADPT_VSI_DEL == op )
	{
		vsi_tbl.bf.bc_bitmap |= (1<<port_id);
		vsi_tbl.bf.member_port_bitmap |= (1<<port_id);
		vsi_tbl.bf.umc_bitmap |= (1<<port_id);
		vsi_tbl.bf.uuc_bitmap |= (1<<port_id);
	}
	rv = hppe_vsi_tbl_set( dev_id, vsi_id, &vsi_tbl);
	if( rv != SW_OK )
		return rv;

	return SW_OK;
}


static sw_error_t _adpt_hppe_port_vsi_mapping_update(a_uint32_t dev_id,
					fal_port_t port_id, a_uint32_t vsi_id)
{
	adpt_vsi_t *p_vsi = NULL;
	sw_error_t rv;
	a_uint32_t i = 0;


	if(adpt_vsi_mapping[dev_id][vsi_id].valid == 0)
	{
		printk("%s,%d: port %d vsi %d entry not found\n",
				__FUNCTION__, __LINE__, port_id, vsi_id);
		return SW_NOT_FOUND;
	}

	/*check port previous vsi*/
	for( i = 0; i <= ADPT_VSI_MAX; i++ )
	{
		p_vsi = &(adpt_vsi_mapping[dev_id][i]);
		if(p_vsi->valid != 0 &&	(p_vsi->pport_bitmap & (1 << port_id)))
		{
			/*remmove from preious vsi*/
			rv = _adpt_hppe_vsi_member_update(dev_id, i,
							port_id, ADPT_VSI_DEL);
			if( rv != SW_OK )
				return rv;
			p_vsi->pport_bitmap &= (~(1<<port_id));
		}
	}

	/*port based vsi update*/
	rv = _adpt_hppe_vsi_member_update(dev_id, vsi_id, port_id, ADPT_VSI_ADD);
	if( rv != SW_OK )
		return rv;
	adpt_vsi_mapping[dev_id][vsi_id].pport_bitmap |= 1 << port_id;

	return SW_OK;
}

static sw_error_t _adpt_hppe_vsi_xlt_update(a_uint32_t dev_id, a_uint32_t vsi_id,
					a_uint32_t vlan_id, a_uint32_t port_id, a_uint32_t op)
{
	a_uint32_t index = 0;
	a_uint32_t new_entry = XLT_RULE_TBL_NUM;
	sw_error_t rv;
	union xlt_rule_tbl_u value;

	for(index = 0; index < XLT_RULE_TBL_NUM; index++)
	{
		rv = hppe_xlt_rule_tbl_get(dev_id, index, &value);
		if( rv != SW_OK )
			return rv;
		if(value.bf.valid == A_FALSE && index < new_entry)
		{
			new_entry = index;
		}
		if((value.bf.valid == A_TRUE) && (value.bf.port_bitmap & (1<<port_id)) &&
			(value.bf.ckey_vid_incl) && (value.bf.ckey_vid == vlan_id))
		{
			break;
		}
	}

	if(index < XLT_RULE_TBL_NUM) /*found*/
	{
		if(op == ADPT_VSI_DEL)/*Delete*/
		{
			value.bf.port_bitmap &= (~(1<<port_id));
			if(value.bf.port_bitmap == 0)
			{
				rv= hppe_xlt_rule_tbl_valid_set(dev_id, index, A_FALSE);
				return rv;
			}
		}
		else/*add*/
		{
			value.bf.port_bitmap |= (1<<port_id);
		}
		rv = hppe_xlt_rule_tbl_port_bitmap_set(dev_id, index, value.bf.port_bitmap);
		return rv;
	}
	else/*not found*/
	{
		if(new_entry >= XLT_RULE_TBL_NUM)
		{
			printk("%s,%d: port_id 0x%x vlan %d vsi %d xlt table is full\n",
					__FUNCTION__, __LINE__, port_id, vlan_id, vsi_id);
			return SW_NO_RESOURCE;
		}
		else/*new entry exist*/
		{
			aos_mem_zero(&value, sizeof(union xlt_rule_tbl_u));
			value.bf.ckey_vid_incl = A_TRUE;
			value.bf.ckey_vid = vlan_id;
			value.bf.port_bitmap = (1<<port_id);
			value.bf.ckey_fmt_0 = 0x1;
			value.bf.ckey_fmt_1 = 0x3;
			rv = hppe_xlt_rule_tbl_set(dev_id, new_entry, &value);
			if( rv != SW_OK )
				return rv;
			rv = hppe_xlt_action_tbl_vsi_cmd_set(dev_id, new_entry, A_TRUE);
			if( rv != SW_OK )
				return rv;
			rv = hppe_xlt_action_tbl_vsi_set(dev_id, new_entry, vsi_id);
			return rv;
		}
	}
}

static sw_error_t _adpt_hppe_vlan_vsi_mapping_add(a_uint32_t dev_id, fal_port_t port_id,
					a_uint32_t vlan_id, a_uint32_t vsi_id)
{
	adpt_vlan_info_t *p_vsi_info = NULL;
	sw_error_t rv;


	/*vlan based vsi update*/
	p_vsi_info = adpt_vsi_mapping[dev_id][vsi_id].pHead;
	while(p_vsi_info != NULL)
	{
		if(vlan_id == p_vsi_info->vlan_id)
		{
			p_vsi_info->vport_bitmap |= 1 << port_id;
			break;
		}
		p_vsi_info = p_vsi_info->pNext;
	}

	if(p_vsi_info == NULL)/*create a new entry if no match*/
	{
		p_vsi_info = aos_mem_alloc(sizeof(adpt_vlan_info_t));
		if(p_vsi_info == NULL)
		{
			printk("%s,%d: port %d vlan %d vsi %d aos_mem_alloc fail\n",
					__FUNCTION__, __LINE__, port_id, vlan_id, vsi_id);
			return SW_NO_RESOURCE;
		}
		p_vsi_info->vport_bitmap = 1 << port_id;
		p_vsi_info->vlan_id = vlan_id;
		p_vsi_info->pNext = (adpt_vsi_mapping[dev_id][vsi_id].pHead);
		adpt_vsi_mapping[dev_id][vsi_id].pHead = p_vsi_info;
	}

	rv = _adpt_hppe_vsi_xlt_update(dev_id, vsi_id, vlan_id, port_id, ADPT_VSI_ADD);
	if( rv != SW_OK )
	{
		printk("%s,%d: port %d vlan %d vsi %d _adpt_hppe_vsi_xlt_update fail\n",
				__FUNCTION__, __LINE__, port_id, vlan_id, vsi_id);
		return rv;
	}
	rv = _adpt_hppe_vsi_member_update(dev_id, vsi_id, port_id, ADPT_VSI_ADD);
	return rv;
}

static sw_error_t _adpt_hppe_vlan_vsi_mapping_del(a_uint32_t dev_id, fal_port_t port_id,
					a_uint32_t vlan_id, a_uint32_t vsi_id)
{
	adpt_vlan_info_t *p_vsi_info = NULL;
	adpt_vlan_info_t *p_prev = NULL;
	sw_error_t rv;
	a_bool_t in_vsi = 0;
	/*vlan based vsi update*/
	p_vsi_info = adpt_vsi_mapping[dev_id][vsi_id].pHead;
	while(p_vsi_info != NULL)
	{
		if(p_vsi_info->vport_bitmap & (1 << port_id))
		{
			if(vlan_id == p_vsi_info->vlan_id)
			{
				rv = _adpt_hppe_vsi_xlt_update(dev_id, vsi_id, vlan_id, port_id, ADPT_VSI_DEL);
				if( rv != SW_OK )
				{
					printk("%s,%d: port %d vlan %d vsi %d _adpt_hppe_vsi_xlt_update fail\n",
							__FUNCTION__, __LINE__, port_id, vlan_id, vsi_id);
					return rv;
				}
			}
			else
			{
				in_vsi = 1;/*port + another vlan --> vsi*/
			}
			/*update software data*/
			p_vsi_info->vport_bitmap &= (~(1 << port_id));

			if(p_vsi_info->vport_bitmap == 0)/*free node if bitmap is 0*/
			{
				if(p_vsi_info == adpt_vsi_mapping[dev_id][vsi_id].pHead)
				{
					adpt_vsi_mapping[dev_id][vsi_id].pHead = p_vsi_info->pNext;
				}
				else
				{
					p_prev->pNext = p_vsi_info->pNext;
				}
				aos_mem_free(p_vsi_info);
			}
			return SW_OK;
		}
		p_prev = p_vsi_info;
		p_vsi_info = p_vsi_info->pNext;
	}

	if(in_vsi == 0)
	{
		rv = _adpt_hppe_vsi_member_update(dev_id, vsi_id, port_id, ADPT_VSI_DEL);
		if( rv != SW_OK )
		{
			printk("%s,%d: port %d vlan %d vsi %d _adpt_hppe_vsi_member_update fail\n",
					__FUNCTION__, __LINE__, port_id, vlan_id, vsi_id);
			return rv;
		}
	}

	printk("%s,%d: port %d vlan %d vsi %d entry not found\n",
			__FUNCTION__, __LINE__, port_id, vlan_id, vsi_id);
	return SW_NOT_FOUND;
}

sw_error_t
adpt_hppe_port_vsi_get(a_uint32_t dev_id, fal_port_t port_id, a_uint32_t *vsi_id)
{
	a_uint32_t i = 0;

	for( i = 0; i <= ADPT_VSI_MAX; i++ )
	{
		if((adpt_vsi_mapping[dev_id][i].valid != 0)&&
			(adpt_vsi_mapping[dev_id][i].pport_bitmap & (1 << port_id)))
		{
			*vsi_id = i;
			return SW_OK;
		}
	}

	return SW_NOT_FOUND;
}

sw_error_t
adpt_hppe_port_vlan_vsi_get(a_uint32_t dev_id, fal_port_t port_id,
				a_uint32_t vlan_id, a_uint32_t *vsi_id)
{
	adpt_vlan_info_t *p_vsi_info = NULL;
	a_uint32_t i = 0;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(vsi_id);

	/*vlan based vsi update*/
	for( i = ADPT_VSI_RESERVE_MAX; i <= ADPT_VSI_MAX; i++ )
	{
		p_vsi_info = adpt_vsi_mapping[dev_id][i].pHead;
		while(p_vsi_info != NULL)
		{
			if((p_vsi_info->vport_bitmap & (1 << port_id)) &&
				(vlan_id == p_vsi_info->vlan_id))
			{
				*vsi_id = i;
				return SW_OK;
			}
			p_vsi_info = p_vsi_info->pNext;
		}
	}
	return SW_NOT_FOUND;
}

sw_error_t
adpt_hppe_port_vlan_vsi_set(a_uint32_t dev_id, fal_port_t port_id,
				a_uint32_t vlan_id, a_uint32_t vsi_id)
{
	sw_error_t rv;

	ADPT_DEV_ID_CHECK(dev_id);

	if(adpt_vsi_mapping[dev_id][vsi_id].valid == 0)
	{
		printk("%s,%d: port %d vlan %d vsi %d entry not found\n",
				__FUNCTION__, __LINE__, port_id, vlan_id, vsi_id);
		return SW_NOT_FOUND;
	}


	if(ADPT_VSI_DELETE == vsi_id)
	{
		a_uint32_t cur_vsi = 0;
		rv = adpt_hppe_port_vlan_vsi_get(dev_id, port_id, vlan_id, &cur_vsi);
		if( rv != SW_OK )
			return rv;
		rv = _adpt_hppe_vlan_vsi_mapping_del(dev_id, port_id, vlan_id, cur_vsi);
	}
	else
	{
		rv = _adpt_hppe_vlan_vsi_mapping_add(dev_id, port_id, vlan_id, vsi_id);
	}

	return rv;
}

sw_error_t
adpt_hppe_vsi_free(a_uint32_t dev_id, a_uint32_t vsi_id)
{
	ADPT_DEV_ID_CHECK(dev_id);

	if( vsi_id <= ADPT_VSI_RESERVE_MAX || vsi_id > ADPT_VSI_MAX )
		return SW_OUT_OF_RANGE;

	adpt_vsi_mapping[dev_id][vsi_id].valid = 0;

	/*TODO: free vlan and port bitmap*/

	return SW_OK;
}

/*called when
	1. switchdev create physical interface for port
	2. add physical interface to a bridge*/
sw_error_t
adpt_hppe_port_vsi_set(a_uint32_t dev_id, fal_port_t port_id, a_uint32_t vsi_id)
{
	union l3_vp_port_tbl_u l3_vp_port_tbl;
	sw_error_t rv;

	ADPT_DEV_ID_CHECK(dev_id);

	l3_vp_port_tbl.bf.vsi_valid = A_TRUE;
	if(ADPT_VSI_DELETE == vsi_id && port_id > ADPT_VSI_PPORT_NR)
	{
		if(port_id <= ADPT_VSI_PPORT_NR)
			vsi_id = default_port_vsi[port_id];
		else
		{
			l3_vp_port_tbl.bf.vsi_valid = A_FALSE;
			vsi_id = 0;
		}
	}

	rv = hppe_l3_vp_port_tbl_get(dev_id, port_id, &l3_vp_port_tbl);
	if (SW_OK != rv)
		return rv;
	l3_vp_port_tbl.bf.vsi = vsi_id;
	rv = hppe_l3_vp_port_tbl_set(dev_id, port_id, &l3_vp_port_tbl);
	if( rv != SW_OK )
		return rv;

	rv = _adpt_hppe_port_vsi_mapping_update(dev_id, port_id, vsi_id);
	if( rv != SW_OK )
		return rv;

	return rv;
}

sw_error_t
adpt_hppe_vsi_alloc(a_uint32_t dev_id, a_uint32_t *vsi)
{
	a_uint32_t vsi_id;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(vsi);

	for( vsi_id = ADPT_VSI_RESERVE_MAX+1; vsi_id < ADPT_VSI_MAX; vsi_id++ )
	{
		if(adpt_vsi_mapping[dev_id][vsi_id].valid == 0)
		{
			adpt_vsi_mapping[dev_id][vsi_id].valid = 1;
  			adpt_vsi_mapping[dev_id][vsi_id].pport_bitmap = 0;
  			adpt_vsi_mapping[dev_id][vsi_id].pHead = NULL;
			*vsi = vsi_id;
			return SW_OK;
		}
	}

	return SW_NO_RESOURCE;
}

sw_error_t
adpt_hppe_vsi_stamove_set(a_uint32_t dev_id, a_uint32_t vsi_id, fal_vsi_stamove_t *stamove)
{
	sw_error_t rv;
	union vsi_tbl_u vsi_tbl;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(stamove);

	rv = hppe_vsi_tbl_get( dev_id, vsi_id, &vsi_tbl);
	if( rv != SW_OK )
		return rv;

	vsi_tbl.bf.station_move_lrn_en = stamove->stamove_en;
	vsi_tbl.bf.station_move_fwd_cmd = stamove->action;

	rv = hppe_vsi_tbl_set( dev_id, vsi_id, &vsi_tbl);
	if( rv != SW_OK )
		return rv;

	return SW_OK;
}
sw_error_t
adpt_hppe_vsi_stamove_get(a_uint32_t dev_id, a_uint32_t vsi_id, fal_vsi_stamove_t *stamove)
{
	sw_error_t rv;
	union vsi_tbl_u vsi_tbl;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(stamove);

	rv = hppe_vsi_tbl_get( dev_id, vsi_id, &vsi_tbl);
	if( rv != SW_OK )
		return rv;

	stamove->stamove_en = vsi_tbl.bf.station_move_lrn_en;
	stamove->action = vsi_tbl.bf.station_move_fwd_cmd;

	return SW_OK;
}

sw_error_t
adpt_hppe_vsi_newaddr_lrn_get(a_uint32_t dev_id, a_uint32_t vsi_id, fal_vsi_newaddr_lrn_t *newaddr_lrn)
{
	sw_error_t rv;
	union vsi_tbl_u vsi_tbl;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(newaddr_lrn);

	rv = hppe_vsi_tbl_get( dev_id, vsi_id, &vsi_tbl);
	if( rv != SW_OK )
		return rv;

	newaddr_lrn->lrn_en = vsi_tbl.bf.new_addr_lrn_en;
	newaddr_lrn->action = vsi_tbl.bf.new_addr_fwd_cmd;

	return SW_OK;
}

sw_error_t
adpt_hppe_vsi_tbl_dump(a_uint32_t dev_id)
{
	a_uint32_t vsi_id;
	adpt_vlan_info_t *p_vsi_info = NULL;

	ADPT_DEV_ID_CHECK(dev_id);
	printk("########Software VSI mapping table\n");
	for( vsi_id = 0; vsi_id < ADPT_VSI_MAX; vsi_id++ )
	{
		if(adpt_vsi_mapping[dev_id][vsi_id].valid == 0)
			continue;
		p_vsi_info = adpt_vsi_mapping[dev_id][vsi_id].pHead;
		printk("vsi , port bitmap 0x%x\n",vsi_id, adpt_vsi_mapping[dev_id][vsi_id].pport_bitmap);
		while(p_vsi_info != NULL)
		{
			printk("%8s vlan %d, port bitmap 0x%x\n","",
				p_vsi_info->vlan_id, p_vsi_info->vport_bitmap);
			p_vsi_info = p_vsi_info->pNext;
		}
	}

	return SW_OK;
}

sw_error_t
adpt_hppe_vsi_newaddr_lrn_set(a_uint32_t dev_id, a_uint32_t vsi_id, fal_vsi_newaddr_lrn_t *newaddr_lrn)
{
	sw_error_t rv;
	union vsi_tbl_u vsi_tbl;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(newaddr_lrn);

	rv = hppe_vsi_tbl_get( dev_id, vsi_id, &vsi_tbl);
	if( rv != SW_OK )
		return rv;

	vsi_tbl.bf.new_addr_lrn_en = newaddr_lrn->lrn_en;
	vsi_tbl.bf.new_addr_fwd_cmd = newaddr_lrn->action;

	rv = hppe_vsi_tbl_set( dev_id, vsi_id, &vsi_tbl);
	if( rv != SW_OK )
		return rv;

	return SW_OK;
}

sw_error_t adpt_hppe_vsi_init(a_uint32_t dev_id)
{
	adpt_api_t *p_adpt_api = NULL;
	a_uint32_t vsi_id;

	p_adpt_api = adpt_api_ptr_get(dev_id);

	if(p_adpt_api == NULL)
		return SW_FAIL;

	p_adpt_api->adpt_port_vlan_vsi_set = adpt_hppe_port_vlan_vsi_set;
	p_adpt_api->adpt_vsi_free = adpt_hppe_vsi_free;
	p_adpt_api->adpt_port_vsi_set = adpt_hppe_port_vsi_set;
	p_adpt_api->adpt_vsi_stamove_set = adpt_hppe_vsi_stamove_set;
	p_adpt_api->adpt_vsi_stamove_get = adpt_hppe_vsi_stamove_get;
	p_adpt_api->adpt_vsi_newaddr_lrn_get = adpt_hppe_vsi_newaddr_lrn_get;
	p_adpt_api->adpt_port_vsi_get = adpt_hppe_port_vsi_get;
	p_adpt_api->adpt_vsi_tbl_dump = adpt_hppe_vsi_tbl_dump;
	p_adpt_api->adpt_vsi_newaddr_lrn_set = adpt_hppe_vsi_newaddr_lrn_set;
	p_adpt_api->adpt_port_vlan_vsi_get = adpt_hppe_port_vlan_vsi_get;
	p_adpt_api->adpt_vsi_alloc = adpt_hppe_vsi_alloc;

	/*init reserved vsi*/
	for( vsi_id = 0; vsi_id < ADPT_VSI_RESERVE_MAX + 1; vsi_id++ )
	{
		if(adpt_vsi_mapping[dev_id][vsi_id].valid == 0)
		{
			adpt_vsi_mapping[dev_id][vsi_id].valid = 1;
  			adpt_vsi_mapping[dev_id][vsi_id].pport_bitmap = 0;
  			adpt_vsi_mapping[dev_id][vsi_id].pHead = NULL;
		}
	}

	return SW_OK;
}

/**
 * @}
 */
