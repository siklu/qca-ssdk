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

static a_bool_t _adpt_hppe_vsi_xlt_match(a_uint32_t dev_id, fal_port_t port_id,
				a_uint32_t stag_vid, a_uint32_t ctag_vid, union xlt_rule_tbl_u *xlt_rule)
{
	if(stag_vid != FAL_VLAN_INVALID)
	{
		if((xlt_rule->bf.skey_vid_incl) &&
			(xlt_rule->bf.skey_vid == stag_vid))
		{
			if(ctag_vid != FAL_VLAN_INVALID)
			{
				if((xlt_rule->bf.ckey_vid_incl) &&
					(xlt_rule->bf.ckey_vid == ctag_vid))
				{
					return A_TRUE;
				}
			}
			else
			{
				if(!(xlt_rule->bf.ckey_vid_incl))
				{
					return A_TRUE;
				}
			}
		}
	}
	else
	{
		if(!(xlt_rule->bf.skey_vid_incl))
		{
			if(ctag_vid != FAL_VLAN_INVALID)
			{
				if((xlt_rule->bf.ckey_vid_incl) &&
					(xlt_rule->bf.ckey_vid == ctag_vid))
				{
					return A_TRUE;
				}
			}
		}
	}
	return A_FALSE;
}

static sw_error_t _adpt_hppe_vsi_xlt_update(a_uint32_t dev_id,
				a_uint32_t vsi_id, a_uint32_t port_id,
				a_uint32_t stag_vid, a_uint32_t ctag_vid,
				a_uint32_t op)
{
	a_uint32_t index = 0;
	a_uint32_t new_entry = XLT_RULE_TBL_NUM;
	sw_error_t rv;
	union xlt_rule_tbl_u xlt_rule;
	union xlt_action_tbl_u xlt_action;

	/*printk("%s,%d: port_id 0x%x svlan %d cvlan %d vsi %d op %d\n",
			__FUNCTION__, __LINE__, port_id, stag_vid, ctag_vid, vsi_id, op);*/

	for(index = 0; index < XLT_RULE_TBL_NUM; index++)
	{
		rv = hppe_xlt_rule_tbl_get(dev_id, index, &xlt_rule);
		if( rv != SW_OK )
			return rv;
		rv = hppe_xlt_action_tbl_get(dev_id, index, &xlt_action);
		if( rv != SW_OK )
			return rv;
		if(xlt_rule.bf.valid == A_FALSE && index < new_entry)
		{
			new_entry = index;
		}
		if(xlt_rule.bf.valid == A_TRUE)
		{
			if(_adpt_hppe_vsi_xlt_match(dev_id, port_id,
				stag_vid, ctag_vid, &xlt_rule))
			{
				if((xlt_action.bf.vsi_cmd == A_TRUE) &&
					(xlt_action.bf.vsi == vsi_id))
					break;
			}
		}
	}

	if(index < XLT_RULE_TBL_NUM) /*found*/
	{
		if(op == ADPT_VSI_DEL)/*Delete*/
		{
			/*printk("%s,%d: port_id 0x%x svlan %d cvlan %d vsi %d op %d\n",
				__FUNCTION__, __LINE__, port_id, stag_vid, ctag_vid, vsi_id, op);*/
			if(!(xlt_rule.bf.port_bitmap & (1<<port_id)))
				return SW_OK;
			xlt_rule.bf.port_bitmap &= (~(1<<port_id));
			if(xlt_rule.bf.port_bitmap == 0)
			{
				rv= hppe_xlt_rule_tbl_valid_set(dev_id, index, A_FALSE);
				return rv;
			}
		}
		else/*add*/
		{
			/*printk("%s,%d: port_id 0x%x svlan %d cvlan %d vsi %d op %d\n",
				__FUNCTION__, __LINE__, port_id, stag_vid, ctag_vid, vsi_id, op);*/
			xlt_rule.bf.port_bitmap |= (1<<port_id);
		}
		/*printk("%s,%d: port_map 0x%x svlan %d cvlan %d vsi %d xlt table update index %d\n",
				__FUNCTION__, __LINE__, xlt_rule.bf.port_bitmap, stag_vid, ctag_vid, vsi_id, index);*/
		rv = hppe_xlt_rule_tbl_port_bitmap_set(dev_id, index, xlt_rule.bf.port_bitmap);
		return rv;
	}
	else/*not found*/
	{
		if(op == ADPT_VSI_DEL)
			return SW_OK;
		if(new_entry >= XLT_RULE_TBL_NUM)
		{
			printk("%s,%d: port_id 0x%x svlan %d cvlan %d vsi %d xlt table is full\n",
					__FUNCTION__, __LINE__, port_id, stag_vid, ctag_vid, vsi_id);
			return SW_NO_RESOURCE;
		}
		else/*new entry exist*/
		{
			aos_mem_zero(&xlt_rule, sizeof(union xlt_rule_tbl_u));
			/*printk("%s,%d: port_id 0x%x svlan %d cvlan %d vsi %d xlt table add index %d\n",
					__FUNCTION__, __LINE__, port_id, stag_vid, ctag_vid, vsi_id, new_entry);*/
			xlt_rule.bf.valid = A_TRUE;
			if(ctag_vid != FAL_VLAN_INVALID)
			{
				xlt_rule.bf.ckey_vid_incl = A_TRUE;
				xlt_rule.bf.ckey_vid = ctag_vid;
			}
			if(stag_vid != FAL_VLAN_INVALID)
			{
				xlt_rule.bf.skey_vid_incl = A_TRUE;
				xlt_rule.bf.skey_vid = stag_vid;
			}
			xlt_rule.bf.port_bitmap = (1<<port_id);
			xlt_rule.bf.skey_fmt = 0x7;
			xlt_rule.bf.ckey_fmt_0 = 0x1;
			xlt_rule.bf.ckey_fmt_1 = 0x3;
			rv = hppe_xlt_rule_tbl_set(dev_id, new_entry, &xlt_rule);
			if( rv != SW_OK )
				return rv;
			aos_mem_zero(&xlt_action, sizeof(union xlt_action_tbl_u));
			xlt_action.bf.vsi_cmd = A_TRUE;
			xlt_action.bf.vsi = vsi_id;
			rv = hppe_xlt_action_tbl_set(dev_id, new_entry, &xlt_action);
			return rv;
		}
	}
}

sw_error_t
adpt_hppe_port_vlan_vsi_get(a_uint32_t dev_id, fal_port_t port_id,
				a_uint32_t stag_vid, a_uint32_t ctag_vid, a_uint32_t *vsi_id)
{
	a_uint32_t index = 0;
	sw_error_t rv;
	union xlt_rule_tbl_u xlt_rule;
	union xlt_action_tbl_u xlt_action;
	for(index = 0; index < XLT_RULE_TBL_NUM; index++)
	{
		rv = hppe_xlt_rule_tbl_get(dev_id, index, &xlt_rule);
		if( rv != SW_OK )
			return rv;
		rv = hppe_xlt_action_tbl_get(dev_id, index, &xlt_action);
		if( rv != SW_OK )
			return rv;
		if(xlt_rule.bf.valid == A_TRUE)
		{
			if(_adpt_hppe_vsi_xlt_match(dev_id, port_id,
					stag_vid, ctag_vid, &xlt_rule))
			{
				if((xlt_rule.bf.port_bitmap&(1<<port_id))&&
					(xlt_action.bf.vsi_cmd == A_TRUE))
				{
					*vsi_id = xlt_action.bf.vsi;
					return SW_OK;
				}
			}
		}
	}

	/*not found*/
	*vsi_id = FAL_VSI_INVALID;
	return SW_NOT_FOUND;
}

sw_error_t
adpt_hppe_port_vlan_vsi_set(a_uint32_t dev_id, fal_port_t port_id,
				a_uint32_t stag_vid, a_uint32_t ctag_vid, a_uint32_t vsi_id)
{
	sw_error_t rv;
	a_uint32_t org_vsi;

	ADPT_DEV_ID_CHECK(dev_id);

	adpt_hppe_port_vlan_vsi_get(dev_id, port_id, stag_vid, ctag_vid, &org_vsi);

	if(org_vsi == vsi_id)
	{
		return SW_OK;
	}

	if(FAL_VSI_INVALID == vsi_id || org_vsi != FAL_VSI_INVALID)
	{
		rv = _adpt_hppe_vsi_xlt_update(dev_id, org_vsi, port_id, stag_vid, ctag_vid, ADPT_VSI_DEL);
		if(rv != SW_OK)
			return rv;
	}
	if(vsi_id != FAL_VSI_INVALID)
	{
		rv = _adpt_hppe_vsi_xlt_update(dev_id, vsi_id, port_id, stag_vid, ctag_vid, ADPT_VSI_ADD);
	}

	return rv;
}


sw_error_t
adpt_hppe_port_vsi_get(a_uint32_t dev_id, fal_port_t port_id, a_uint32_t *vsi_id)
{
	union l3_vp_port_tbl_u l3_vp_port_tbl;
	sw_error_t rv;

	ADPT_DEV_ID_CHECK(dev_id);
	//printk("%s, %d: port %d, vsi %d\n", __FUNCTION__, __LINE__, port_id, vsi_id);
	if(!(FAL_IS_PPORT(port_id)) && !(FAL_IS_VPORT(port_id)))
		return SW_BAD_VALUE;

	rv = hppe_l3_vp_port_tbl_get(dev_id, FAL_PORT_ID_VALUE(port_id), &l3_vp_port_tbl);
	if (SW_OK != rv)
		return rv;
	if(l3_vp_port_tbl.bf.vsi_valid)
		*vsi_id = l3_vp_port_tbl.bf.vsi;
	else
		*vsi_id = FAL_VSI_INVALID;

	return rv;
}


sw_error_t
adpt_hppe_port_vsi_set(a_uint32_t dev_id, fal_port_t port_id, a_uint32_t vsi_id)
{
	union l3_vp_port_tbl_u l3_vp_port_tbl;
	sw_error_t rv;

	ADPT_DEV_ID_CHECK(dev_id);
	//printk("%s, %d: port %d, vsi %d\n", __FUNCTION__, __LINE__, port_id, vsi_id);
	if(!(FAL_IS_PPORT(port_id)) && !(FAL_IS_VPORT(port_id)))
		return SW_BAD_VALUE;

	rv = hppe_l3_vp_port_tbl_get(dev_id, FAL_PORT_ID_VALUE(port_id), &l3_vp_port_tbl);
	if (SW_OK != rv)
		return rv;
	if(FAL_VSI_INVALID == vsi_id)
	{
		l3_vp_port_tbl.bf.vsi_valid = A_FALSE;
		l3_vp_port_tbl.bf.vsi = 0;
	}
	else
	{
		l3_vp_port_tbl.bf.vsi_valid = A_TRUE;
		l3_vp_port_tbl.bf.vsi = vsi_id;
	}
	rv = hppe_l3_vp_port_tbl_set(dev_id, FAL_PORT_ID_VALUE(port_id), &l3_vp_port_tbl);
	if( rv != SW_OK )
		return rv;
	//printk("%s, %d: port %d, vsi %d\n", __FUNCTION__, __LINE__, port_id, vsi_id);

	return rv;
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

sw_error_t
adpt_hppe_vsi_member_set(a_uint32_t dev_id, a_uint32_t vsi_id, fal_vsi_member_t *vsi_member)
{
	sw_error_t rv;
	union vsi_tbl_u vsi_tbl;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(vsi_member);

	rv = hppe_vsi_tbl_get( dev_id, vsi_id, &vsi_tbl);
	if( rv != SW_OK )
		return rv;

	vsi_tbl.bf.bc_bitmap = vsi_member->bc_ports & 0xff;
	vsi_tbl.bf.member_port_bitmap = vsi_member->member_ports & 0xff;
	vsi_tbl.bf.umc_bitmap = vsi_member->umc_ports & 0xff;
	vsi_tbl.bf.uuc_bitmap = vsi_member->uuc_ports & 0xff;

	rv = hppe_vsi_tbl_set(dev_id, vsi_id, &vsi_tbl);
	if( rv != SW_OK )
		return rv;

	return SW_OK;

}

sw_error_t
adpt_hppe_vsi_member_get(a_uint32_t dev_id, a_uint32_t vsi_id, fal_vsi_member_t *vsi_member)
{
	sw_error_t rv;
	union vsi_tbl_u vsi_tbl;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(vsi_member);

	rv = hppe_vsi_tbl_get( dev_id, vsi_id, &vsi_tbl);
	if( rv != SW_OK )
		return rv;

	vsi_member->bc_ports = vsi_tbl.bf.bc_bitmap;
	vsi_member->member_ports = vsi_tbl.bf.member_port_bitmap;
	vsi_member->umc_ports = vsi_tbl.bf.umc_bitmap;
	vsi_member->uuc_ports = vsi_tbl.bf.uuc_bitmap;

	rv = hppe_vsi_tbl_set(dev_id, vsi_id, &vsi_tbl);
	if( rv != SW_OK )
		return rv;

	return SW_OK;

}

void adpt_hppe_vsi_func_bitmap_init(a_uint32_t dev_id)
{
	adpt_api_t *p_adpt_api = NULL;

	p_adpt_api = adpt_api_ptr_get(dev_id);

	if(p_adpt_api == NULL)
		return;

	return;
}



sw_error_t adpt_hppe_vsi_init(a_uint32_t dev_id)
{
	adpt_api_t *p_adpt_api = NULL;

	p_adpt_api = adpt_api_ptr_get(dev_id);

	if(p_adpt_api == NULL)
		return SW_FAIL;

	p_adpt_api->adpt_port_vlan_vsi_set = adpt_hppe_port_vlan_vsi_set;
	p_adpt_api->adpt_port_vlan_vsi_get = adpt_hppe_port_vlan_vsi_get;
	p_adpt_api->adpt_port_vsi_set = adpt_hppe_port_vsi_set;
	p_adpt_api->adpt_port_vsi_get = adpt_hppe_port_vsi_get;
	p_adpt_api->adpt_vsi_stamove_set = adpt_hppe_vsi_stamove_set;
	p_adpt_api->adpt_vsi_stamove_get = adpt_hppe_vsi_stamove_get;
	p_adpt_api->adpt_vsi_newaddr_lrn_get = adpt_hppe_vsi_newaddr_lrn_get;
	p_adpt_api->adpt_vsi_newaddr_lrn_set = adpt_hppe_vsi_newaddr_lrn_set;
	p_adpt_api->adpt_vsi_member_set = adpt_hppe_vsi_member_set;
	p_adpt_api->adpt_vsi_member_get = adpt_hppe_vsi_member_get;


	return SW_OK;
}

/**
 * @}
 */
