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
#include "ref_vsi.h"

static ref_vsi_t ref_vsi_mapping[SW_MAX_NR_DEV][REF_VSI_MAX+1] ={{0, 0, NULL},
								{0, 0, NULL},
								{0, 0, NULL}};
static a_uint32_t default_port_vsi[REF_VSI_PPORT_NR+1] ={1, 2, 2, 2, 2, 3, 3};/*PPORT + CPU*/

static sw_error_t
_ref_vsi_member_init(a_uint32_t dev_id, a_uint32_t vsi_id)
{
	fal_vsi_member_t vsi_member;

	aos_mem_zero(&vsi_member, sizeof(vsi_member));

	vsi_member.member_ports = 0x1;
	vsi_member.umc_ports    = 0x1;
	vsi_member.uuc_ports    = 0x1;
	vsi_member.bc_ports     = 0x1;

	fal_vsi_member_set(dev_id, vsi_id, &vsi_member);

	return SW_OK;
}

static sw_error_t
_ref_vsi_member_update(a_uint32_t dev_id, a_uint32_t vsi_id,
				fal_port_t port_id, a_uint32_t op)
{
	sw_error_t rv;
	fal_vsi_member_t vsi_member;

	rv = fal_vsi_member_get( dev_id, vsi_id, &vsi_member);
	if( rv != SW_OK )
		return rv;
	if( REF_VSI_DEL == op )
	{
		vsi_member.member_ports &= (~(1<<port_id));
		vsi_member.bc_ports &= (~(1<<port_id));
		vsi_member.umc_ports &= (~(1<<port_id));
		vsi_member.uuc_ports &= (~(1<<port_id));
	}
	else if( REF_VSI_ADD == op )
	{
		vsi_member.member_ports |= (1<<port_id);
		vsi_member.bc_ports |= (1<<port_id);
		vsi_member.umc_ports |= (1<<port_id);
		vsi_member.uuc_ports |= (1<<port_id);
	}
	rv = fal_vsi_member_set(dev_id, vsi_id, &vsi_member);
	if( rv != SW_OK )
		return rv;

	return SW_OK;
}

static sw_error_t _ref_vlan_vsi_mapping_add(a_uint32_t dev_id, fal_port_t port_id,
					a_uint32_t vlan_id, a_uint32_t vsi_id)
{
	ref_vlan_info_t *p_vsi_info = NULL;
	sw_error_t rv;

	rv = fal_port_vlan_vsi_set(dev_id, port_id, vlan_id, vsi_id);
	if( rv != SW_OK )
	{
		printk("%s,%d: port %d vlan %d vsi %d fal_port_vlan_vsi_set fail\n",
				__FUNCTION__, __LINE__, port_id, vlan_id, vsi_id);
		return rv;
	}
	rv = _ref_vsi_member_update(dev_id, vsi_id, port_id, REF_VSI_ADD);
	if( rv != SW_OK )
	{
		return rv;
	}

	/*vlan based vsi update*/
	p_vsi_info = ref_vsi_mapping[dev_id][vsi_id].pHead;
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
		p_vsi_info = aos_mem_alloc(sizeof(ref_vlan_info_t));
		if(p_vsi_info == NULL)
		{
			printk("%s,%d: port %d vlan %d vsi %d aos_mem_alloc fail\n",
					__FUNCTION__, __LINE__, port_id, vlan_id, vsi_id);
			return SW_NO_RESOURCE;
		}
		p_vsi_info->vport_bitmap = 1 << port_id;
		p_vsi_info->vlan_id = vlan_id;
		p_vsi_info->pNext = (ref_vsi_mapping[dev_id][vsi_id].pHead);
		ref_vsi_mapping[dev_id][vsi_id].pHead = p_vsi_info;
	}

	return rv;
}

static sw_error_t _ref_vlan_vsi_mapping_del(a_uint32_t dev_id, fal_port_t port_id,
					a_uint32_t vlan_id, a_uint32_t vsi_id)
{
	ref_vlan_info_t *p_vsi_info = NULL;
	ref_vlan_info_t *p_prev = NULL;
	sw_error_t rv;
	a_bool_t in_vsi = 0;

	rv = fal_port_vlan_vsi_set(dev_id, port_id, vlan_id, REF_VSI_DEL);
	if( rv != SW_OK )
	{
		printk("%s,%d: port %d vlan %d vsi %d fal_port_vlan_vsi_set fail\n",
				__FUNCTION__, __LINE__, port_id, vlan_id, vsi_id);
		return rv;
	}

	/*vlan based vsi update*/
	p_vsi_info = ref_vsi_mapping[dev_id][vsi_id].pHead;
	while(p_vsi_info != NULL)
	{
		if(p_vsi_info->vport_bitmap & (1 << port_id))
		{
			if(vlan_id == p_vsi_info->vlan_id)
			{
				/*update software data*/
				p_vsi_info->vport_bitmap &= (~(1 << port_id));
				if(p_vsi_info->vport_bitmap == 0)/*free node if bitmap is 0*/
				{
					if(p_vsi_info == ref_vsi_mapping[dev_id][vsi_id].pHead)
					{
						ref_vsi_mapping[dev_id][vsi_id].pHead = p_vsi_info->pNext;
					}
					else
					{
						p_prev->pNext = p_vsi_info->pNext;
					}
					//printk("%s,%d: port %d vlan %d vsi %d free vsi info\n",
					//		__FUNCTION__, __LINE__, port_id, vlan_id, vsi_id);
					aos_mem_free(p_vsi_info);
				}
			}
			else
			{
				in_vsi = 1;/*port + another vlan --> vsi*/
			}
		}
		p_prev = p_vsi_info;
		p_vsi_info = p_vsi_info->pNext;
	}

	if(in_vsi == 0 &&
		(!(1 << port_id & ref_vsi_mapping[dev_id][vsi_id].pport_bitmap)))
	{
		rv = _ref_vsi_member_update(dev_id, vsi_id, port_id, REF_VSI_DEL);
		if( rv != SW_OK )
		{
			printk("%s,%d: port %d vlan %d vsi %d _ref_vsi_member_update fail\n",
					__FUNCTION__, __LINE__, port_id, vlan_id, vsi_id);
			return rv;
		}
	}

	return SW_OK;
}

static sw_error_t _ref_port_vsi_mapping_update(a_uint32_t dev_id,
					fal_port_t port_id, a_uint32_t vsi_id)
{
	ref_vsi_t *p_vsi = NULL;
	sw_error_t rv;
	a_uint32_t i = 0;


	if(ref_vsi_mapping[dev_id][vsi_id].valid == 0)
	{
		printk("%s,%d: port %d vsi %d entry not found\n",
				__FUNCTION__, __LINE__, port_id, vsi_id);
		return SW_NOT_FOUND;
	}
	//printk("%s, %d: port %d, vsi %d\n", __FUNCTION__, __LINE__, port_id, vsi_id);

	/*check port previous vsi*/
	for( i = 0; i <= REF_VSI_MAX; i++ )
	{
		p_vsi = &(ref_vsi_mapping[dev_id][i]);
		if(p_vsi->valid != 0 &&	(p_vsi->pport_bitmap & (1 << port_id)))
		{
			/*remmove from preious vsi*/
			rv = _ref_vsi_member_update(dev_id, i, port_id, REF_VSI_DEL);
			if( rv != SW_OK )
				return rv;
			p_vsi->pport_bitmap &= (~(1<<port_id));
		}
	}
	//printk("%s, %d: port %d, vsi %d\n", __FUNCTION__, __LINE__, port_id, vsi_id);

	/*port based vsi update*/
	rv = _ref_vsi_member_update(dev_id, vsi_id, port_id, REF_VSI_ADD);
	if( rv != SW_OK )
		return rv;
	ref_vsi_mapping[dev_id][vsi_id].pport_bitmap |= 1 << port_id;

	return SW_OK;
}


sw_error_t
ref_port_vlan_vsi_set(a_uint32_t dev_id, fal_port_t port_id, a_uint32_t vlan_id, a_uint32_t vsi_id)
{
	sw_error_t rv;
	a_uint32_t cur_vsi = REF_VSI_DELETE;

	REF_DEV_ID_CHECK(dev_id);

	if((vsi_id != REF_VSI_DELETE) &&
		(ref_vsi_mapping[dev_id][vsi_id].valid == 0))
	{
		printk("%s,%d: port %d vlan %d vsi %d entry not found\n",
				__FUNCTION__, __LINE__, port_id, vlan_id, vsi_id);
		return SW_NOT_FOUND;
	}

	ref_port_vlan_vsi_get(dev_id, port_id, vlan_id, &cur_vsi);
	if(cur_vsi == vsi_id)
		return SW_OK;

	if(REF_VSI_DELETE == vsi_id || cur_vsi != REF_VSI_DELETE)
	{
		rv = _ref_vlan_vsi_mapping_del(dev_id, port_id, vlan_id, cur_vsi);
		if( rv != SW_OK )
			return rv;
	}

	if(REF_VSI_DELETE != vsi_id)
		rv = _ref_vlan_vsi_mapping_add(dev_id, port_id, vlan_id, vsi_id);

	return rv;
}
sw_error_t
ref_port_vlan_vsi_get(a_uint32_t dev_id, fal_port_t port_id, a_uint32_t vlan_id, a_uint32_t *vsi_id)
{
	ref_vlan_info_t *p_vsi_info = NULL;
	a_uint32_t i = 0;

	REF_DEV_ID_CHECK(dev_id);
	REF_NULL_POINT_CHECK(vsi_id);

	for( i = REF_VSI_RESERVE_MAX; i <= REF_VSI_MAX; i++ )
	{
		p_vsi_info = ref_vsi_mapping[dev_id][i].pHead;
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


/*called when
	1. switchdev create physical interface for port
	2. add physical interface to a bridge*/
sw_error_t
ref_port_vsi_set(a_uint32_t dev_id, fal_port_t port_id, a_uint32_t vsi_id)
{
	sw_error_t rv;

	REF_DEV_ID_CHECK(dev_id);
	//printk("%s, %d: port %d, vsi %d\n", __FUNCTION__, __LINE__, port_id, vsi_id);
	if(!(FAL_IS_PPORT(port_id)) && !(FAL_IS_VPORT(port_id)))
		return SW_BAD_VALUE;

	rv = fal_port_vsi_set(dev_id, port_id, vsi_id);
	if (SW_OK != rv)
		return rv;

	//printk("%s, %d: port %d, vsi %d\n", __FUNCTION__, __LINE__, port_id, vsi_id);

	if(FAL_IS_PPORT(port_id))
	{
		rv = _ref_port_vsi_mapping_update(dev_id, FAL_PORT_ID_VALUE(port_id), vsi_id);
		if( rv != SW_OK )
			return rv;
	}
	return rv;
}
sw_error_t
ref_port_vsi_get(a_uint32_t dev_id, fal_port_t port_id, a_uint32_t *vsi_id)
{
	a_uint32_t i = 0;

	for( i = 0; i <= REF_VSI_MAX; i++ )
	{
		if((ref_vsi_mapping[dev_id][i].valid != 0)&&
			(ref_vsi_mapping[dev_id][i].pport_bitmap & (1 << port_id)))
		{
			*vsi_id = i;
			return SW_OK;
		}
	}

	return SW_NOT_FOUND;
}

sw_error_t ref_vsi_alloc(a_uint32_t dev_id, a_uint32_t *vsi)
{
	a_uint32_t vsi_id;

	REF_DEV_ID_CHECK(dev_id);
	REF_NULL_POINT_CHECK(vsi);

	for( vsi_id = REF_VSI_RESERVE_MAX+1; vsi_id < REF_VSI_MAX; vsi_id++ )
	{
		if(ref_vsi_mapping[dev_id][vsi_id].valid == 0)
		{
			ref_vsi_mapping[dev_id][vsi_id].valid = 1;
  			ref_vsi_mapping[dev_id][vsi_id].pport_bitmap = 0;
  			ref_vsi_mapping[dev_id][vsi_id].pHead = NULL;
			*vsi = vsi_id;
			_ref_vsi_member_init(dev_id, vsi_id);
			return SW_OK;
		}
	}

	return SW_NO_RESOURCE;
}

sw_error_t ref_vsi_free(a_uint32_t dev_id, a_uint32_t vsi_id)
{
	REF_DEV_ID_CHECK(dev_id);

	if( vsi_id <= REF_VSI_RESERVE_MAX || vsi_id > REF_VSI_MAX )
		return SW_OUT_OF_RANGE;

	ref_vsi_mapping[dev_id][vsi_id].valid = 0;

	/*TODO: free vlan and port bitmap*/

	return SW_OK;
}

sw_error_t ref_vsi_init(a_uint32_t dev_id)
{
	a_uint32_t vsi_id;
	/*init reserved vsi*/
	for( vsi_id = 0; vsi_id < REF_VSI_RESERVE_MAX + 1; vsi_id++ )
	{
		if(ref_vsi_mapping[dev_id][vsi_id].valid == 0)
		{
			ref_vsi_mapping[dev_id][vsi_id].valid = 1;
			ref_vsi_mapping[dev_id][vsi_id].pport_bitmap = 0;
			ref_vsi_mapping[dev_id][vsi_id].pHead = NULL;
			_ref_vsi_member_init(dev_id, vsi_id);
		}
	}

	return SW_OK;
}


sw_error_t ref_vsi_tbl_dump(a_uint32_t dev_id)
{
	a_uint32_t vsi_id;
	ref_vlan_info_t *p_vsi_info = NULL;

	REF_DEV_ID_CHECK(dev_id);
	printk("########Software VSI mapping table\n");
	for( vsi_id = 0; vsi_id < REF_VSI_MAX; vsi_id++ )
	{
		if(ref_vsi_mapping[dev_id][vsi_id].valid == 0)
			continue;
		p_vsi_info = ref_vsi_mapping[dev_id][vsi_id].pHead;
		printk("vsi %d, port bitmap 0x%x\n",vsi_id, ref_vsi_mapping[dev_id][vsi_id].pport_bitmap);
		while(p_vsi_info != NULL)
		{
			printk("%8s vlan %d, port bitmap 0x%x\n","",
				p_vsi_info->vlan_id, p_vsi_info->vport_bitmap);
			p_vsi_info = p_vsi_info->pNext;
		}
	}

	return SW_OK;
}

