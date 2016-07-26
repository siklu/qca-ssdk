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
#include "adpt.h"
#include "hppe_acl_reg.h"
#include "hppe_acl.h"


#define ADPT_ACL_HPPE_MAC_DA_RULE 0
#define ADPT_ACL_HPPE_MAC_SA_RULE 1
#define ADPT_ACL_HPPE_VLAN_RULE 2
#define ADPT_ACL_HPPE_L2_MISC_RULE 3
#define ADPT_ACL_HPPE_IPV4_DIP_RULE 4
#define ADPT_ACL_HPPE_IPV4_SIP_RULE 5
#define ADPT_ACL_HPPE_IPV6_DIP0_RULE 6
#define ADPT_ACL_HPPE_IPV6_DIP1_RULE 7
#define ADPT_ACL_HPPE_IPV6_DIP2_RULE 8
#define ADPT_ACL_HPPE_IPV6_SIP0_RULE 9
#define ADPT_ACL_HPPE_IPV6_SIP1_RULE 10
#define ADPT_ACL_HPPE_IPV6_SIP2_RULE 11
#define ADPT_ACL_HPPE_IPMISC_RULE 12
#define ADPT_ACL_HPPE_UDF0_RULE 13
#define ADPT_ACL_HPPE_UDF1_RULE 14
#define ADPT_ACL_HPPE_RULE_TYPE_NUM 15


#define ADPT_ACL_LIST_NUM 96
#define ADPT_ACL_RULE_NUM_PER_LIST 8
#define ADPT_ACL_ENTRY_NUM_PER_LIST 8


typedef struct{
	a_uint32_t list_pri;
	a_uint8_t free_hw_entry_bitmap;
	a_uint8_t free_hw_entry_count;
	a_uint8_t rule_hw_entry[ADPT_ACL_RULE_NUM_PER_LIST];
	a_uint8_t ext1_val[ADPT_ACL_RULE_NUM_PER_LIST];
	a_uint8_t ext2_val[ADPT_ACL_RULE_NUM_PER_LIST];
	a_uint8_t ext4_val[ADPT_ACL_RULE_NUM_PER_LIST];
}ADPT_HPPE_ACL_LIST;

typedef struct{
	a_uint8_t mac[6];
	a_uint32_t is_ip:1;
	a_uint32_t is_ipv6:1;
	a_uint32_t is_ethernet:1;
	a_uint32_t is_snap:1;
	a_uint32_t is_fake_mac_header:1;
}ADPT_HPPE_ACL_MAC_RULE;
typedef struct{
	a_uint8_t mac_mask[6];
	a_uint32_t is_ip_mask:1;
	a_uint32_t is_ipv6_mask:1;
	a_uint32_t is_ethernet_mask:1;
	a_uint32_t is_snap_mask:1;
	a_uint32_t is_fake_mac_header_mask:1;
}ADPT_HPPE_ACL_MAC_RULE_MASK;

typedef struct{
	a_uint32_t cvid:12;/*it is min cvid when range is enable*/
	a_uint32_t reserved:4;
	a_uint32_t cpcp:3;
	a_uint32_t cdei:1;
	a_uint32_t svid:12;
	a_uint32_t spcp:3;
	a_uint32_t sdei:1;
	a_uint32_t ctag_fmt:3;
	a_uint32_t stag_fmt:3;
	a_uint32_t vsi:5;
	a_uint32_t vsi_valid:1;
	a_uint32_t is_ip:1;
	a_uint32_t is_ipv6:1;
	a_uint32_t is_ethernet:1;
	a_uint32_t is_snap:1;
	a_uint32_t is_fake_mac_header:1;
}ADPT_HPPE_ACL_VLAN_RULE;

typedef struct{
	a_uint32_t cvid_mask:12;/*it is max cvid when range is enable*/
	a_uint32_t reserved:4;
	a_uint32_t cpcp_mask:3;
	a_uint32_t cdei_mask:1;
	a_uint32_t svid_mask:12;
	a_uint32_t spcp_mask:3;
	a_uint32_t sdei_mask:1;
	a_uint32_t ctag_fmt_mask:3;
	a_uint32_t stag_fmt_mask:3;
	a_uint32_t vsi_mask:5;
	a_uint32_t vsi_valid_mask:1;
	a_uint32_t is_ip_mask:1;
	a_uint32_t is_ipv6_mask:1;
	a_uint32_t is_ethernet_mask:1;
	a_uint32_t is_snap_mask:1;
	a_uint32_t is_fake_mac_header_mask:1;
}ADPT_HPPE_ACL_VLAN_RULE_MASK;

typedef struct{
	a_uint32_t svid:12;/*it is min svid when range is enable*/
	a_uint32_t reserved:4;
	a_uint32_t l2prot:16;
	a_uint32_t is_ip:1;
	a_uint32_t is_ipv6:1;
	a_uint32_t is_ethernet:1;
	a_uint32_t is_snap:1;
	a_uint32_t is_fake_mac_header:1;
}ADPT_HPPE_ACL_L2MISC_RULE;

typedef struct{
	a_uint32_t svid_mask:12;/*it is max svid when range is enable*/
	a_uint32_t reserved:4;
	a_uint32_t l2prot_mask:16;
	a_uint32_t is_ip_mask:1;
	a_uint32_t is_ipv6_mask:1;
	a_uint32_t is_ethernet_mask:1;
	a_uint32_t is_snap_mask:1;
	a_uint32_t is_fake_mac_header_mask:1;
}ADPT_HPPE_ACL_L2MISC_RULE_MASK;

typedef struct{
	a_uint32_t l4_port:16;/*it is min dport when range is enable*/
	a_uint32_t ip:32;
	a_uint32_t l3_fragment:1;
	a_uint32_t l3_packet_type:3;
	a_uint32_t is_ip:1;
}ADPT_HPPE_ACL_IPV4_RULE;

typedef struct{
	a_uint32_t l4_port_mask:16;/*it is min dport when range is enable*/
	a_uint32_t ip_mask:32;
	a_uint32_t l3_fragment_mask:1;
	a_uint32_t l3_packet_type_mask:3;
	a_uint32_t is_ip_mask:1;
}ADPT_HPPE_ACL_IPV4_RULE_MASK;

typedef struct{
	union{
		struct{
			a_uint32_t ip_32bit:32;
			a_uint32_t ip_16bits:16;
		};
		struct{
			a_uint32_t l4_port:16;
			a_uint32_t ip_32bits:32;
		};
	} ip_port;
	a_uint32_t l3_fragment:1;
	a_uint32_t l3_packet_type:3;
	a_uint32_t reserved:1;
}ADPT_HPPE_ACL_IPV6_RULE;

typedef struct{
	union{
		struct{
			a_uint32_t ip_32bit:32;
			a_uint32_t ip_16bits:16;
		};
		struct{
			a_uint32_t l4_port:16;
			a_uint32_t ip_32bits:32;
		};
	} ip_port_mask;
	a_uint32_t l3_fragment_mask:1;
	a_uint32_t l3_packet_type_mask:3;
	a_uint32_t reserved:1;
}ADPT_HPPE_ACL_IPV6_RULE_MASK;

typedef struct{
	a_uint32_t l3_length:16;/*it is min length when range is enable*/
	a_uint32_t l3_prot:8; /*ipv4 protocol or ipv6 next header*/
	a_uint32_t l3_dscp_tc:8;
	a_uint32_t first_fragment:1;
	a_uint32_t tcp_flags:6;
	a_uint32_t ipv4_option_state:1;
	a_uint32_t l3_ttl:2; /*ipv4 ttl, ipv6 hop limit*/
	a_uint32_t ah_header:1;
	a_uint32_t esp_header:1;
	a_uint32_t mobility_header:1;
	a_uint32_t fragment_header:1;
	a_uint32_t other_header:1;
	a_uint32_t reserved0:1;
	a_uint32_t l3_fragment:1;
	a_uint32_t is_ipv6:1;
	a_uint32_t reserved1:3;
}ADPT_HPPE_ACL_IPMISC_RULE;

typedef struct{
	a_uint32_t l3_length_mask:16;/*it is max length when range is enable*/
	a_uint32_t l3_prot_mask:8; /*ipv4 protocol or ipv6 next header*/
	a_uint32_t l3_dscp_tc_mask:8;
	a_uint32_t first_fragment_mask:1;
	a_uint32_t tcp_flags_mask:6;
	a_uint32_t ipv4_option_state_mask:1;
	a_uint32_t l3_ttl_mask:2; /*ipv4 ttl, ipv6 hop limit*/
	a_uint32_t ah_header_mask:1;
	a_uint32_t esp_header_mask:1;
	a_uint32_t mobility_header_mask:1;
	a_uint32_t fragment_header_mask:1;
	a_uint32_t other_header_mask:1;
	a_uint32_t reserved0:1;
	a_uint32_t l3_fragment_mask:1;
	a_uint32_t is_ipv6_mask:1;
	a_uint32_t reserved1:3;
}ADPT_HPPE_ACL_IPMISC_RULE_MASK;

static ADPT_HPPE_ACL_LIST g_acl_list[SW_MAX_NR_DEV][ADPT_ACL_LIST_NUM];

const a_uint8_t s_acl_ext2[7][2] = {
	{0,1},{2,3},{4,5},{6,7},{0,2},{4,6},{0,4}
};
typedef struct
{
	a_uint8_t num;
	a_uint8_t ext_1;
	a_uint8_t ext_2;
	a_uint8_t ext_4;
	a_uint8_t entries;
}ADPT_HPPE_ACL_ENTRY_EXTEND_INFO;
const ADPT_HPPE_ACL_ENTRY_EXTEND_INFO s_acl_entries[] = {
	/*num ext_1 ext_2 ext_4 entries*/
	{1, 0, 0, 0, 0x2},
	{1, 0, 0, 0, 0x8},
	{1, 0, 0, 0, 0x20},
	{1, 0, 0, 0, 0x80},
	{1, 0, 0, 0, 0x1},
	{1, 0, 0, 0, 0x4},
	{1, 0, 0, 0, 0x10},
	{1, 0, 0, 0, 0x40},
	{2, 0x1, 0, 0, 0x3},
	{2, 0x2, 0, 0, 0xc},
	{2, 0x4, 0, 0, 0x30},
	{2, 0x8, 0, 0, 0xc0},
	{2, 0, 0x1, 0, 0x5},
	{2, 0, 0x2, 0, 0x50},
	{2, 0, 0, 0x1, 0x11},
	{3, 0x1, 0x1, 0x0, 0x7},
	{3, 0x1, 0x0, 0x1, 0x13},
	{3, 0x2, 0x1, 0x0, 0xd},
	{3, 0x4, 0x2, 0x0, 0x70},
	{3, 0x4, 0x0, 0x1, 0x31},
	{3, 0x8, 0x2, 0x0, 0xd0},
	{3, 0x0, 0x1, 0x1, 0x15},
	{3, 0x0, 0x2, 0x1, 0x51},
	{4, 0x3, 0x1, 0x0, 0xf},
	{4, 0x5, 0x0, 0x1, 0x33},
	{4, 0x2, 0x1, 0x1, 0x1d},
	{4, 0xc, 0x2, 0x0, 0xf0},
	{4, 0x4, 0x1, 0x1, 0x35},
	{4, 0x8, 0x2, 0x1, 0xd1},
	{4, 0x0, 0x3, 0x1, 0x55},
	{5, 0x3, 0x1, 0x1, 0x1f},
	{5, 0x6, 0x1, 0x1, 0x3d},
	{5, 0xc, 0x2, 0x1, 0xf1},
	{5, 0x8, 0x3, 0x1, 0xd5},
	{6, 0x7, 0x1, 0x1, 0x3f},
	{6, 0x6, 0x3, 0x1, 0x7d},
	{6, 0xc, 0x3, 0x1, 0xf5},
	{7, 0x7, 0x3, 0x1, 0x7f},
	{7, 0xe, 0x3, 0x1, 0xfd},
	{8, 0xf, 0x3, 0x1, 0xff},
};

/*type = 0, count all; type = 1 count odd; type = 2 count even*/
static a_uint32_t _acl_bits_count(a_uint32_t bits, a_uint32_t max, a_uint32_t type)
{
	a_uint32_t i = 0, count = 0;
	while(i < max)
	{
		if((bits >> i) &0x1)
		{
			if(type == 1)
			{
				if(i%2!=0)
					count++;
			}
			else if(type == 2)
			{
				if(i%2==0)
					count++;
			}
			else
				count++;
		}
		i++;
	}
	return count;
}

/*type = 0, count all; type = 1 count odd; type = 2 count even*/
static a_uint32_t _acl_bit_index(a_uint32_t bits, a_uint32_t max, a_uint32_t type)
{
	a_uint32_t i = 0;
	while(i < max)
	{
		if((bits >> i) &0x1)
		{
			if(type == 1)/*odd*/
			{
				if(i%2!=0)
					break;
			}
			else if(type == 2)/*even*/
			{
				if(i%2==0)
					break;
			}
			else
				break;
		}
		i++;
	}
	if(i<max)
		return i;
	return 0xff;
}

static void _acl_print_extend_slices(a_uint8_t extend,a_uint8_t extend_slices, u_int8_t slice_count)
{
#if 0
	a_uint32_t i;
	for(i = 0; i < 8; i++)
	{
		if(extend & (1<<i))
		{
			if(i==6)
				printk("ext_2.bit0 ");
			else
				printk("ext_%d.bit%d ", i/4, (i%4));
		}
	}
	printk("\n");
	for(i = 0; i < 8; i++)
	{
		if(extend_slices & (1<<i))
		{
			printk("slice%d ", i);
		}
	}
	printk("\n");
#else
	a_uint32_t i;
	a_uint32_t ext_1=0, ext_2=0, ext_4=0;
	for(i = 0; i < 8; i++)
	{
		if(extend & (1<<i))
		{
			if(i==6)
				ext_4 = 0x1;
			else if(i<4)
				ext_1 |= (1<<i);
			else
				ext_2 |= (1<<(i%4));
		}
	}
	printk("\n{%d, 0x%x, 0x%x, 0x%x, 0x%x},\n", slice_count, ext_1, ext_2, ext_4, extend_slices);
#endif
}
static void _acl_slice_ext_bitmap_gen(a_uint32_t ext_n)
{
	a_uint32_t i, j;
	a_uint8_t extend = 0;
	a_uint8_t full_extend = 0;
	a_uint8_t extend_slices = 0;
	a_uint8_t extend_count = 0;

	printk("########ext_n = %d\n", ext_n);

	for(i = 0; i < 7; i++)
	{
		extend = (1 << i);
		extend_slices = (1<<s_acl_ext2[i][0])|(1<<s_acl_ext2[i][1]);
		extend_count = 2;
		full_extend = 0;
		for(j = i+1; j < 7; j++)
		{
			int k;
			if((extend & (1<<j))||(full_extend & (1<<j)))
			{
				//printk("extend = %x, full_extend = %x\n", extend, full_extend);
				continue;
			}
			for(k = 0; k < extend_count; k++)
			{
				if(extend_slices &(1<<s_acl_ext2[j][0]))
				{
					extend |= (1<<j);
					extend_slices |= (1<<s_acl_ext2[j][1]);
					extend_count++;
					break;
				}
				else if(extend_slices &(1<<s_acl_ext2[j][1]))
				{
					extend |= (1<<j);
					extend_slices |= (1<<s_acl_ext2[j][0]);
					extend_count++;
					break;
				}
			}
			if(extend_count == ext_n)
			{
				_acl_print_extend_slices(extend, extend_slices, extend_count);
				full_extend |= extend;
				extend_count = 2;
				extend = (1 << i);
				extend_slices = (1<<s_acl_ext2[i][0])|(1<<s_acl_ext2[i][1]);
				j=i;
			}
			if(k < extend_count)
			{
				j=i;
			}
		}
	}
}




sw_error_t
adpt_hppe_acl_list_bind(a_uint32_t dev_id, a_uint32_t list_id, fal_acl_direc_t direc, fal_acl_bind_obj_t obj_t, a_uint32_t obj_idx)
{

	ADPT_DEV_ID_CHECK(dev_id);

	return SW_OK;
}
sw_error_t
adpt_hppe_acl_port_udf_profile_get(a_uint32_t dev_id, fal_port_t port_id,
		fal_acl_udf_type_t udf_type, a_uint32_t * offset, a_uint32_t * length)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(offset);
	ADPT_NULL_POINT_CHECK(length);

	return SW_OK;
}

sw_error_t
adpt_hppe_acl_rule_src_filter_sts_get(a_uint32_t dev_id, a_uint32_t rule_id, a_bool_t* enable)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(enable);

	return SW_OK;
}

sw_error_t
adpt_hppe_acl_rule_deactive(a_uint32_t dev_id, a_uint32_t list_id, a_uint32_t rule_id, a_uint32_t rule_nr)
{

	ADPT_DEV_ID_CHECK(dev_id);

	return SW_OK;
}
sw_error_t
adpt_hppe_acl_list_dump(a_uint32_t dev_id)
{

	ADPT_DEV_ID_CHECK(dev_id);

	return SW_OK;
}
sw_error_t
adpt_hppe_acl_status_get(a_uint32_t dev_id, a_bool_t * enable)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(enable);

	return SW_OK;
}

sw_error_t
adpt_hppe_acl_status_set(a_uint32_t dev_id, a_bool_t enable)
{

	ADPT_DEV_ID_CHECK(dev_id);

	return SW_OK;
}
sw_error_t
adpt_hppe_acl_rule_query(a_uint32_t dev_id, a_uint32_t list_id, a_uint32_t rule_id, fal_acl_rule_t * rule)
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(rule);

	return SW_OK;
}
sw_error_t
adpt_hppe_acl_list_unbind(a_uint32_t dev_id, a_uint32_t list_id, fal_acl_direc_t direc, fal_acl_bind_obj_t obj_t, a_uint32_t obj_idx)
{

	ADPT_DEV_ID_CHECK(dev_id);

	return SW_OK;
}
sw_error_t
adpt_hppe_acl_rule_active(a_uint32_t dev_id, a_uint32_t list_id, a_uint32_t rule_id, a_uint32_t rule_nr)
{

	ADPT_DEV_ID_CHECK(dev_id);

	return SW_OK;
}

static sw_error_t _adpt_hppe_acl_rule_range_match(a_uint32_t dev_id, a_uint32_t list_id,
			a_uint32_t rule_id, a_uint32_t rule_nr, fal_acl_rule_t * rule, a_uint8_t entries)
{
	a_uint8_t rangecount = 0, even_entry_count = 0;
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_MAC_STAG_VID))
	{
		if (FAL_ACL_FIELD_MASK != rule->stag_vid_op)
		{
			rangecount++;
		}
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_MAC_CTAG_VID))
	{
		if (FAL_ACL_FIELD_MASK != rule->ctag_vid_op)
		{
			rangecount++;
		}
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_L4_DPORT))
	{
		if (FAL_ACL_FIELD_MASK != rule->dest_l4port_op)
		{
			rangecount++;
		}
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_L4_SPORT))
	{
		if (FAL_ACL_FIELD_MASK != rule->src_l4port_op)
		{
			rangecount++;
		}
	}

	even_entry_count = _acl_bits_count(entries, 8, 2);

	if(rangecount <= even_entry_count)
		return SW_OK;
	return SW_NO_RESOURCE;
}
sw_error_t _adpt_hppe_acl_alloc_entries(a_uint32_t dev_id, a_uint32_t list_id,
			a_uint32_t rule_id, a_uint32_t rule_nr, fal_acl_rule_t * rule,
			a_uint32_t rule_type_map, a_uint32_t rule_type_count, a_uint32_t *index)
{
	a_uint8_t free_hw_entry_bitmap =
			g_acl_list[dev_id][list_id].free_hw_entry_bitmap;
	a_uint8_t free_hw_entry_count =
			g_acl_list[dev_id][list_id].free_hw_entry_count;

	a_uint8_t i = 0;
	a_uint8_t map_info_count = sizeof(s_acl_entries)/sizeof(ADPT_HPPE_ACL_ENTRY_EXTEND_INFO);

	if(free_hw_entry_count < rule_type_count)
		return SW_NO_RESOURCE;

	while(i < map_info_count)
	{
		if((rule_type_count == s_acl_entries[i].num) &&
			((free_hw_entry_bitmap & s_acl_entries[i].entries) == s_acl_entries[i].entries))
		{
			if(SW_OK == _adpt_hppe_acl_rule_range_match(dev_id, list_id,
					rule_id, rule_nr, rule, s_acl_entries[i].entries))
			{
				printk("\n{%d, 0x%x, 0x%x, 0x%x, 0x%x},\n",
					s_acl_entries[i].num, s_acl_entries[i].ext_1, s_acl_entries[i].ext_2,
					s_acl_entries[i].ext_4, s_acl_entries[i].entries);
				*index = i;
				return SW_OK;
			}
		}
		i++;
	}
	return SW_NO_RESOURCE;
}

static sw_error_t
_adpt_hppe_acl_l2_fields_check(a_uint32_t dev_id, a_uint32_t list_id, a_uint32_t rule_id, a_uint32_t rule_nr,
				fal_acl_rule_t * rule, a_uint32_t *rule_type_map)
{
	printk("%s, %d: fields[0] = 0x%x, fields[1] = 0x%x\n", __FUNCTION__, __LINE__, rule->field_flg[0], rule->field_flg[1]);

	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_MAC_DA))
	{
		printk("%s, %d: select MAC DA rule\n", __FUNCTION__, __LINE__);
		*rule_type_map |= (1<<ADPT_ACL_HPPE_MAC_DA_RULE);
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_MAC_SA))
	{
		printk("%s, %d: select MAC SA rule\n", __FUNCTION__, __LINE__);
		*rule_type_map |= (1<<ADPT_ACL_HPPE_MAC_SA_RULE);
	}
	if((FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_MAC_STAG_PRI)) ||
		(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_MAC_STAG_DEI)) ||
		(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_MAC_STAGGED)) ||
		(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_MAC_CTAG_VID)) ||
		(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_MAC_CTAG_PRI)) ||
		(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_MAC_CTAG_CFI)) ||
		(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_MAC_CTAGGED)) ||
		(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_VSI)))
	{
		printk("%s, %d: select VLAN rule\n", __FUNCTION__, __LINE__);
		*rule_type_map |= (1<<ADPT_ACL_HPPE_VLAN_RULE);
	}

	if((FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_MAC_ETHTYPE)) ||
		(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_PPPOE_SESSIONID)))
	{
		printk("%s, %d: select L2 MISC rule\n", __FUNCTION__, __LINE__);
		*rule_type_map |= (1<<ADPT_ACL_HPPE_L2_MISC_RULE);
	}

	if(!((*rule_type_map & (1<<ADPT_ACL_HPPE_VLAN_RULE))||
		(*rule_type_map & (1<<ADPT_ACL_HPPE_L2_MISC_RULE))))
	{
		if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_MAC_STAG_VID))
		{
			printk("%s, %d: select VLAN rule\n", __FUNCTION__, __LINE__);
			*rule_type_map |= (1<<ADPT_ACL_HPPE_VLAN_RULE);
		}
	}

	if(*rule_type_map == 0)
	{
		if((FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_SNAP)) ||
			(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_ETHERNET)) ||
			(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_FAKE_MAC_HEADER)))
		{
			printk("%s, %d: select MAC DA rule\n", __FUNCTION__, __LINE__);
			*rule_type_map |= (1<<ADPT_ACL_HPPE_MAC_DA_RULE);
		}
	}
	printk("%s, %d: rule_type_map = 0x%x\n", __FUNCTION__, __LINE__, *rule_type_map);

	return SW_OK;
}
static sw_error_t
_adpt_hppe_acl_ipv4_fields_check(a_uint32_t dev_id, a_uint32_t list_id, a_uint32_t rule_id, a_uint32_t rule_nr,
				fal_acl_rule_t * rule, a_uint32_t *rule_type_map)
{
	printk("%s, %d: fields[0] = 0x%x, fields[1] = 0x%x\n", __FUNCTION__, __LINE__, rule->field_flg[0], rule->field_flg[1]);

	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_L4_SPORT) ||
		FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_IP4_SIP) ||
		FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_ICMP_TYPE) ||
		FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_ICMP_CODE))
	{
		*rule_type_map |= (1<<ADPT_ACL_HPPE_IPV4_SIP_RULE);
	}

	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_L4_DPORT) ||
		FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_IP4_DIP))
	{
		*rule_type_map |= (1<<ADPT_ACL_HPPE_IPV4_DIP_RULE);
	}

	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_L3_LENGTH) ||
		FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_IP_DSCP) ||
		FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_FIRST_FRAGMENT) ||
		FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_TCP_FLAG) ||
		FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_IPV4_OPTION) ||
		FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_L3_TTL) ||
		FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_L3_FRAGMENT) ||
		FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_IP_PROTO))
	{
		*rule_type_map |= (1<<ADPT_ACL_HPPE_IPMISC_RULE);
	}
	if((!(*rule_type_map & (1<<ADPT_ACL_HPPE_IPV4_DIP_RULE))) &&
		(!(*rule_type_map & (1<<ADPT_ACL_HPPE_IPV4_SIP_RULE))))
	{/*both dip and sip rule are not selected, but ip_pkt_type field selected*/
		if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_IP_PKT_TYPE))
		{
			*rule_type_map |= (1<<ADPT_ACL_HPPE_IPV4_DIP_RULE);
		}
	}
	if(*rule_type_map == 0)
	{
		if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_L3_FRAGMENT))
		{
			*rule_type_map |= (1<<ADPT_ACL_HPPE_IPV4_DIP_RULE);
		}
	}

	printk("%s, %d: rule_type_map = 0x%x\n", __FUNCTION__, __LINE__, *rule_type_map);
	return SW_OK;
}

static sw_error_t
_adpt_hppe_acl_ipv6_fields_check(a_uint32_t dev_id, a_uint32_t list_id, a_uint32_t rule_id, a_uint32_t rule_nr,
				fal_acl_rule_t * rule, a_uint32_t *rule_type_map)
{
	printk("%s, %d: fields[0] = 0x%x, fields[1] = 0x%x\n", __FUNCTION__, __LINE__, rule->field_flg[0], rule->field_flg[1]);

	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_L4_SPORT) ||
		FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_ICMP_TYPE) ||
		FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_ICMP_CODE))
	{
		*rule_type_map |= (1<<ADPT_ACL_HPPE_IPV6_SIP2_RULE);
	}

	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_IP6_SIP))
	{
		if(rule->src_ip6_mask.ul[0] != 0 || rule->src_ip6_mask.ul[1]&0xffff0000)
			*rule_type_map |= (1<<ADPT_ACL_HPPE_IPV6_SIP0_RULE);
		if(rule->src_ip6_mask.ul[2] != 0 || rule->src_ip6_mask.ul[1]&0x0000ffff)
			*rule_type_map |= (1<<ADPT_ACL_HPPE_IPV6_SIP1_RULE);
		if(rule->src_ip6_mask.ul[3] != 0 )
			*rule_type_map |= (1<<ADPT_ACL_HPPE_IPV6_SIP2_RULE);
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_L4_DPORT))
	{
		*rule_type_map |= (1<<ADPT_ACL_HPPE_IPV6_DIP2_RULE);
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_IP6_DIP))
	{
		if(rule->dest_ip6_mask.ul[0] != 0 || rule->dest_ip6_mask.ul[1]&0xffff0000)
			*rule_type_map |= (1<<ADPT_ACL_HPPE_IPV6_DIP0_RULE);
		if(rule->dest_ip6_mask.ul[2] != 0 || rule->dest_ip6_mask.ul[1]&0x0000ffff)
			*rule_type_map |= (1<<ADPT_ACL_HPPE_IPV6_DIP1_RULE);
		if(rule->dest_ip6_mask.ul[3] != 0 )
			*rule_type_map |= (1<<ADPT_ACL_HPPE_IPV6_DIP2_RULE);
	}

	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_L3_LENGTH) ||
		FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_IP_DSCP) ||
		FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_FIRST_FRAGMENT) ||
		FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_TCP_FLAG) ||
		FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_L3_TTL) ||
		FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_L3_FRAGMENT)||
		FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_ESP_HEADER) ||
		FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_MOBILITY_HEADER) ||
		FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_FRAGMENT_HEADER)||
		FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_OTHER_EXT_HEADER)||
		FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_AH_HEADER) ||
		FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_IP_PROTO))
	{
		*rule_type_map |= (1<<ADPT_ACL_HPPE_IPMISC_RULE);
	}

	if((!(*rule_type_map & (1<<ADPT_ACL_HPPE_IPV6_DIP0_RULE))) &&
		(!(*rule_type_map & (1<<ADPT_ACL_HPPE_IPV6_DIP1_RULE))) &&
		(!(*rule_type_map & (1<<ADPT_ACL_HPPE_IPV6_DIP2_RULE))) &&
		(!(*rule_type_map & (1<<ADPT_ACL_HPPE_IPV6_SIP0_RULE))) &&
		(!(*rule_type_map & (1<<ADPT_ACL_HPPE_IPV6_SIP1_RULE))) &&
		(!(*rule_type_map & (1<<ADPT_ACL_HPPE_IPV6_SIP2_RULE))))
	{/*both dip and sip rule are not selected, but ip_pkt_type field selected*/
		if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_IP_PKT_TYPE))
		{
			*rule_type_map |= (1<<ADPT_ACL_HPPE_IPV6_DIP0_RULE);
		}
	}

	if(*rule_type_map == 0)
	{
		if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_L3_FRAGMENT))
		{
			*rule_type_map |= (1<<ADPT_ACL_HPPE_IPV6_DIP0_RULE);
		}
	}

	printk("%s, %d: rule_type_map = 0x%x\n", __FUNCTION__, __LINE__, *rule_type_map);

	return SW_OK;
}

static sw_error_t _adpt_hppe_acl_mac_rule_sw_2_hw(fal_acl_rule_t *rule, a_uint32_t is_mac_da,
		union ipo_rule_reg_u *hw_reg, union ipo_mask_reg_u *hw_mask)
{
	ADPT_HPPE_ACL_MAC_RULE * macrule = (ADPT_HPPE_ACL_MAC_RULE *)hw_reg;
	ADPT_HPPE_ACL_MAC_RULE_MASK *macrule_mask = (ADPT_HPPE_ACL_MAC_RULE_MASK *)hw_mask;

	if(is_mac_da)
	{
		if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_MAC_DA))
		{
			memcpy(macrule->mac, rule->dest_mac_val.uc, 6);
			memcpy(macrule_mask->mac_mask, rule->dest_mac_mask.uc, 6);
		}
	}
	else
	{
		if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_MAC_SA))
		{
			memcpy(macrule->mac, rule->src_mac_val.uc, 6);
			memcpy(macrule_mask->mac_mask, rule->src_mac_mask.uc, 6);
		}
	}

	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_IP))
	{
		macrule->is_ip = rule->is_ip_val;
		macrule_mask->is_ip_mask = 1;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_IPV6))
	{
		macrule->is_ip = rule->is_ipv6_val;
		macrule_mask->is_ipv6_mask = 1;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_ETHERNET))
	{
		macrule->is_ethernet = rule->is_ipv6_val;
		macrule_mask->is_ethernet_mask = 1;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_SNAP))
	{
		macrule->is_snap = rule->is_snap_val;
		macrule_mask->is_snap_mask = 1;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_FAKE_MAC_HEADER))
	{
		macrule->is_fake_mac_header = rule->is_fake_mac_header_val;
		macrule_mask->is_fake_mac_header_mask = 1;
	}

	return SW_OK;
}

static sw_error_t _adpt_hppe_acl_vlan_rule_sw_2_hw(fal_acl_rule_t *rule,
		union ipo_rule_reg_u *hw_reg, union ipo_mask_reg_u *hw_mask)
{
	ADPT_HPPE_ACL_VLAN_RULE * vlanrule = (ADPT_HPPE_ACL_VLAN_RULE *)hw_reg;
	ADPT_HPPE_ACL_VLAN_RULE_MASK *vlanrule_mask = (ADPT_HPPE_ACL_VLAN_RULE_MASK *)hw_mask;

	/*ctag*/
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_MAC_CTAG_VID))
	{
		if(FAL_ACL_FIELD_MASK == rule->ctag_vid_op)
		{
			vlanrule->cvid = rule->ctag_vid_val;
			vlanrule_mask->cvid_mask = rule->ctag_vid_mask;
		}
		else
		{
			a_uint16_t min, max;
			if(FAL_ACL_FIELD_LE == rule->ctag_vid_op)
			{
				min = 0;
				max = rule->ctag_vid_val;
			}
			if(FAL_ACL_FIELD_GE == rule->ctag_vid_op)
			{
				min = rule->ctag_vid_val;
				max = 0xfff;
			}
			if(FAL_ACL_FIELD_RANGE == rule->ctag_vid_op)
			{
				min = rule->ctag_vid_val;
				max = rule->ctag_vid_mask;
			}
			else
				return SW_NOT_SUPPORTED;
			vlanrule->cvid = min;
			vlanrule_mask->cvid_mask = max;
			hw_reg->bf.range_en = 1;
		}
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_MAC_CTAG_PRI))
	{
		vlanrule->cpcp = rule->ctag_pri_val;
		vlanrule_mask->cpcp_mask = rule->ctag_pri_mask;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_MAC_CTAG_CFI))
	{
		vlanrule->cdei = rule->ctag_cfi_val;
		vlanrule_mask->cdei_mask = rule->ctag_cfi_mask;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_MAC_CTAGGED))
	{
		vlanrule->ctag_fmt = rule->ctagged_val;
		vlanrule_mask->ctag_fmt_mask = rule->ctagged_mask;
	}
	/*stag*/
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_MAC_STAG_VID))
	{
		vlanrule->svid = rule->stag_vid_val;
		vlanrule_mask->svid_mask = rule->stag_vid_mask;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_MAC_STAG_PRI))
	{
		vlanrule->spcp = rule->stag_pri_val;
		vlanrule_mask->spcp_mask = rule->stag_pri_mask;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_MAC_CTAG_CFI))
	{
		vlanrule->sdei = rule->stag_dei_val;
		vlanrule_mask->sdei_mask = rule->stag_dei_mask;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_MAC_STAGGED))
	{
		vlanrule->stag_fmt = rule->stagged_val;
		vlanrule_mask->stag_fmt_mask = rule->stagged_mask;
	}
	/*vsi*/
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_VSI_VALID))
	{
		vlanrule->vsi_valid= rule->vsi_valid;
		vlanrule_mask->vsi_valid_mask = rule->vsi_valid_mask;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_VSI))
	{
		vlanrule->vsi= rule->vsi;
		vlanrule_mask->vsi_mask = rule->vsi_mask;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_IP))
	{
		vlanrule->is_ip = rule->is_ip_val;
		vlanrule_mask->is_ip_mask = 1;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_IPV6))
	{
		vlanrule->is_ip = rule->is_ipv6_val;
		vlanrule_mask->is_ipv6_mask = 1;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_ETHERNET))
	{
		vlanrule->is_ethernet = rule->is_ipv6_val;
		vlanrule_mask->is_ethernet_mask = 1;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_SNAP))
	{
		vlanrule->is_snap = rule->is_snap_val;
		vlanrule_mask->is_snap_mask = 1;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_FAKE_MAC_HEADER))
	{
		vlanrule->is_fake_mac_header = rule->is_fake_mac_header_val;
		vlanrule_mask->is_fake_mac_header_mask = 1;
	}

	return SW_OK;
}


static sw_error_t _adpt_hppe_acl_l2_misc_rule_sw_2_hw(fal_acl_rule_t *rule,
		union ipo_rule_reg_u *hw_reg, union ipo_mask_reg_u *hw_mask)
{
	ADPT_HPPE_ACL_L2MISC_RULE * l2misc_rule = (ADPT_HPPE_ACL_L2MISC_RULE *)hw_reg;
	ADPT_HPPE_ACL_L2MISC_RULE_MASK *l2misc_mask = (ADPT_HPPE_ACL_L2MISC_RULE_MASK *)hw_mask;

	/*stag*/
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_MAC_STAG_VID))
	{
		if(FAL_ACL_FIELD_MASK == rule->stag_vid_op)
		{
			l2misc_rule->svid = rule->stag_vid_val;
			l2misc_mask->svid_mask = rule->stag_vid_mask;
		}
		else
		{
			a_uint16_t min, max;
			if(FAL_ACL_FIELD_LE == rule->stag_vid_op)
			{
				min = 0;
				max = rule->stag_vid_val;
			}
			if(FAL_ACL_FIELD_GE == rule->stag_vid_op)
			{
				min = rule->stag_vid_val;
				max = 0xfff;
			}
			if(FAL_ACL_FIELD_RANGE == rule->stag_vid_op)
			{
				min = rule->stag_vid_val;
				max = rule->stag_vid_mask;
			}
			else
				return SW_NOT_SUPPORTED;
			l2misc_rule->svid = min;
			l2misc_mask->svid_mask = max;
			hw_reg->bf.range_en = 1;
		}
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_MAC_ETHTYPE))
	{
		l2misc_rule->l2prot = rule->ethtype_val;
		l2misc_mask->l2prot_mask = rule->ethtype_mask;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_IP))
	{
		l2misc_rule->is_ip = rule->is_ip_val;
		l2misc_mask->is_ip_mask = 1;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_IPV6))
	{
		l2misc_rule->is_ip = rule->is_ipv6_val;
		l2misc_mask->is_ipv6_mask = 1;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_ETHERNET))
	{
		l2misc_rule->is_ethernet = rule->is_ipv6_val;
		l2misc_mask->is_ethernet_mask = 1;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_SNAP))
	{
		l2misc_rule->is_snap = rule->is_snap_val;
		l2misc_mask->is_snap_mask = 1;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_FAKE_MAC_HEADER))
	{
		l2misc_rule->is_fake_mac_header = rule->is_fake_mac_header_val;
		l2misc_mask->is_fake_mac_header_mask = 1;
	}

	return SW_OK;
}

static sw_error_t _adpt_hppe_acl_ipv4_rule_sw_2_hw(fal_acl_rule_t *rule, a_uint32_t is_ip_da,
		union ipo_rule_reg_u *hw_reg, union ipo_mask_reg_u *hw_mask)
{
	ADPT_HPPE_ACL_IPV4_RULE * ipv4rule = (ADPT_HPPE_ACL_IPV4_RULE *)hw_reg;
	ADPT_HPPE_ACL_IPV4_RULE_MASK *ipv4rule_mask = (ADPT_HPPE_ACL_IPV4_RULE_MASK *)hw_mask;

	if(is_ip_da)
	{
		if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_IP4_DIP))
		{
			ipv4rule->ip = rule->dest_ip4_val;
			ipv4rule_mask->ip_mask = rule->dest_ip4_mask;
		}
		if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_L4_DPORT))
		{
			if(FAL_ACL_FIELD_MASK == rule->dest_l4port_op)
			{
				ipv4rule->l4_port = rule->dest_l4port_val;
				ipv4rule_mask->l4_port_mask = rule->dest_l4port_mask;
			}
			else
			{
				a_uint16_t min, max;
				if(FAL_ACL_FIELD_LE == rule->dest_l4port_op)
				{
					min = 0;
					max = rule->dest_l4port_val;
				}
				if(FAL_ACL_FIELD_GE == rule->dest_l4port_op)
				{
					min = rule->dest_l4port_val;
					max = 0xffff;
				}
				if(FAL_ACL_FIELD_RANGE == rule->dest_l4port_op)
				{
					min = rule->dest_l4port_val;
					max = rule->dest_l4port_mask;
				}
				else
					return SW_NOT_SUPPORTED;
				ipv4rule->l4_port = min;
				ipv4rule_mask->l4_port_mask = max;
				hw_reg->bf.range_en = 1;
			}
		}
	}
	else
	{
		if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_IP4_SIP))
		{
			ipv4rule->ip = rule->src_ip4_val;
			ipv4rule_mask->ip_mask = rule->src_ip4_mask;
		}
		if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_L4_SPORT))
		{
			if(FAL_ACL_FIELD_MASK == rule->src_l4port_op)
			{
				ipv4rule->l4_port = rule->src_l4port_val;
				ipv4rule_mask->l4_port_mask = rule->src_l4port_mask;
			}
			else
			{
				a_uint16_t min, max;
				if(FAL_ACL_FIELD_LE == rule->src_l4port_op)
				{
					min = 0;
					max = rule->src_l4port_val;
				}
				if(FAL_ACL_FIELD_GE == rule->src_l4port_op)
				{
					min = rule->src_l4port_val;
					max = 0xffff;
				}
				if(FAL_ACL_FIELD_RANGE == rule->src_l4port_op)
				{
					min = rule->src_l4port_val;
					max = rule->src_l4port_mask;
				}
				else
					return SW_NOT_SUPPORTED;
				hw_reg->bf.range_en = 1;
			}
		}
	}

	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_IP))
	{
		ipv4rule->is_ip = rule->is_ip_val;
		ipv4rule_mask->is_ip_mask = 1;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_L3_FRAGMENT))
	{
		ipv4rule->l3_fragment = rule->is_fragement_val;
		ipv4rule_mask->l3_fragment_mask = rule->is_fragement_mask;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_IP_PKT_TYPE))
	{
		ipv4rule->l3_packet_type = rule->l3_pkt_type;
		ipv4rule_mask->l3_packet_type_mask = rule->l3_pkt_type_mask;
	}

	return SW_OK;
}

/*ip_bit_range: 0 mean DIP0 or SIP0, 1 mean DIP1 or SIP1, 2 mean DIP2 or SIP2,*/
static sw_error_t _adpt_hppe_acl_ipv6_rule_sw_2_hw(fal_acl_rule_t *rule, a_uint32_t is_ip_da, a_uint32_t ip_bit_range,
		union ipo_rule_reg_u *hw_reg, union ipo_mask_reg_u *hw_mask)
{
	ADPT_HPPE_ACL_IPV6_RULE * ipv6rule = (ADPT_HPPE_ACL_IPV6_RULE *)hw_reg;
	ADPT_HPPE_ACL_IPV6_RULE_MASK *ipv6rule_mask = (ADPT_HPPE_ACL_IPV6_RULE_MASK *)hw_mask;

	if(is_ip_da)
	{
		if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_IP6_DIP))
		{
			if(ip_bit_range == 0)
			{
				memcpy(&ipv6rule->ip_port, (a_uint8_t *)&rule->dest_ip6_val.ul[0], 6);
				memcpy(&ipv6rule_mask->ip_port_mask, (a_uint8_t *)&rule->dest_ip6_mask.ul[0], 6);
			}
			else if(ip_bit_range == 1)
			{
				memcpy(&ipv6rule->ip_port, ((a_uint8_t *)&rule->dest_ip6_val.ul[0])+6, 6);
				memcpy(&ipv6rule_mask->ip_port_mask, ((a_uint8_t *)&rule->dest_ip6_mask.ul[0])+6, 6);
			}
			else if(ip_bit_range == 2)
			{
				ipv6rule->ip_port.ip_32bits = rule->dest_ip6_val.ul[3];
				ipv6rule_mask->ip_port_mask.ip_32bits = rule->dest_ip6_mask.ul[3];
			}
		}
		if((ip_bit_range == 2) && (FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_L4_DPORT)))
		{
			if(FAL_ACL_FIELD_MASK == rule->dest_l4port_op)
			{
				ipv6rule->ip_port.l4_port = rule->dest_l4port_val;
				ipv6rule_mask->ip_port_mask.l4_port = rule->dest_l4port_mask;
			}
			else
			{
				a_uint16_t min, max;
				if(FAL_ACL_FIELD_LE == rule->dest_l4port_op)
				{
					min = 0;
					max = rule->dest_l4port_val;
				}
				if(FAL_ACL_FIELD_GE == rule->dest_l4port_op)
				{
					min = rule->dest_l4port_val;
					max = 0xffff;
				}
				if(FAL_ACL_FIELD_RANGE == rule->dest_l4port_op)
				{
					min = rule->dest_l4port_val;
					max = rule->dest_l4port_mask;
				}
				else
					return SW_NOT_SUPPORTED;
				ipv6rule->ip_port.l4_port = min;
				ipv6rule_mask->ip_port_mask.l4_port = max;
				hw_reg->bf.range_en = 1;
			}
		}
	}
	else
	{
		if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_IP6_SIP))
		{
			if(ip_bit_range == 0)
			{
				memcpy(&ipv6rule->ip_port, (a_uint8_t *)&rule->src_ip6_val.ul[0], 6);
				memcpy(&ipv6rule_mask->ip_port_mask, (a_uint8_t *)&rule->src_ip6_mask.ul[0], 6);
			}
			else if(ip_bit_range == 1)
			{
				memcpy(&ipv6rule->ip_port, ((a_uint8_t *)&rule->src_ip6_val.ul[0])+6, 6);
				memcpy(&ipv6rule_mask->ip_port_mask, ((a_uint8_t *)&rule->src_ip6_mask.ul[0])+6, 6);
			}
			else if(ip_bit_range == 2)
			{
				ipv6rule->ip_port.ip_32bits = rule->src_ip6_val.ul[3];
				ipv6rule_mask->ip_port_mask.ip_32bits = rule->src_ip6_mask.ul[3];
			}
		}
		if((ip_bit_range == 2) && (FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_L4_SPORT)))
		{
			if(FAL_ACL_FIELD_MASK == rule->src_l4port_op)
			{
				ipv6rule->ip_port.l4_port = rule->src_l4port_val;
				ipv6rule_mask->ip_port_mask.l4_port = rule->src_l4port_mask;
			}
			else
			{
				a_uint16_t min, max;
				if(FAL_ACL_FIELD_LE == rule->src_l4port_op)
				{
					min = 0;
					max = rule->src_l4port_val;
				}
				if(FAL_ACL_FIELD_GE == rule->src_l4port_op)
				{
					min = rule->src_l4port_val;
					max = 0xffff;
				}
				if(FAL_ACL_FIELD_RANGE == rule->src_l4port_op)
				{
					min = rule->src_l4port_val;
					max = rule->src_l4port_mask;
				}
				else
					return SW_NOT_SUPPORTED;
				ipv6rule->ip_port.l4_port = min;
				ipv6rule_mask->ip_port_mask.l4_port = max;
				hw_reg->bf.range_en = 1;
			}
		}
	}

	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_L3_FRAGMENT))
	{
		ipv6rule->l3_fragment = rule->is_fragement_val;
		ipv6rule_mask->l3_fragment_mask = rule->is_fragement_mask;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_IP_PKT_TYPE))
	{
		ipv6rule->l3_packet_type = rule->l3_pkt_type;
		ipv6rule_mask->l3_packet_type_mask = rule->l3_pkt_type_mask;
	}
	return SW_OK;
}

static sw_error_t _adpt_hppe_acl_ipmisc_rule_sw_2_hw(fal_acl_rule_t *rule,
		union ipo_rule_reg_u *hw_reg, union ipo_mask_reg_u *hw_mask)
{
	ADPT_HPPE_ACL_IPMISC_RULE * ipmisc_rule = (ADPT_HPPE_ACL_IPMISC_RULE *)hw_reg;
	ADPT_HPPE_ACL_IPMISC_RULE_MASK *ipmisc_mask = (ADPT_HPPE_ACL_IPMISC_RULE_MASK *)hw_mask;

	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_L3_LENGTH))
	{
		if(FAL_ACL_FIELD_MASK == rule->l3_length_op)
		{
			ipmisc_rule->l3_length = rule->l3_length;
			ipmisc_mask->l3_length_mask = rule->l3_length_mask;
		}
		else
		{
			a_uint16_t min, max;
			if(FAL_ACL_FIELD_LE == rule->l3_length_op)
			{
				min = 0;
				max = rule->l3_length;
			}
			if(FAL_ACL_FIELD_GE == rule->l3_length_op)
			{
				min = rule->l3_length;
				max = 0xffff;
			}
			if(FAL_ACL_FIELD_RANGE == rule->l3_length_op)
			{
				min = rule->l3_length;
				max = rule->l3_length_mask;
			}
			else
				return SW_NOT_SUPPORTED;
			ipmisc_rule->l3_length = min;
			ipmisc_mask->l3_length_mask = max;
			hw_reg->bf.range_en = 1;
		}
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_IP_PROTO))
	{
		ipmisc_rule->l3_prot = rule->ip_proto_val;
		ipmisc_mask->l3_prot_mask = rule->ip_proto_mask;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_IP_DSCP))
	{
		ipmisc_rule->l3_dscp_tc = rule->ip_dscp_val;
		ipmisc_mask->l3_dscp_tc_mask = rule->ip_dscp_mask;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_FIRST_FRAGMENT))
	{
		ipmisc_rule->first_fragment = rule->is_first_frag_val;
		ipmisc_mask->first_fragment_mask = 1;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_TCP_FLAG))
	{
		ipmisc_rule->tcp_flags = rule->tcp_flag_val;
		ipmisc_mask->tcp_flags_mask = rule->tcp_flag_mask;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_IPV4_OPTION))
	{
		ipmisc_rule->ipv4_option_state = rule->is_ipv4_option_val;
		ipmisc_mask->tcp_flags_mask = 1;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_L3_TTL))
	{
		ipmisc_rule->l3_ttl = rule->l3_ttl;
		ipmisc_mask->l3_ttl_mask = rule->l3_ttl_mask;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_AH_HEADER))
	{
		ipmisc_rule->ah_header = rule->is_ah_header_val;
		ipmisc_mask->ah_header_mask = 1;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_ESP_HEADER))
	{
		ipmisc_rule->esp_header = rule->is_esp_header_val;
		ipmisc_mask->esp_header_mask = 1;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_MOBILITY_HEADER))
	{
		ipmisc_rule->mobility_header = rule->is_mobility_header_val;
		ipmisc_mask->mobility_header_mask = 1;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_FRAGMENT_HEADER))
	{
		ipmisc_rule->fragment_header = rule->is_fragment_header_val;
		ipmisc_mask->fragment_header_mask= 1;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_OTHER_EXT_HEADER))
	{
		ipmisc_rule->other_header = rule->is_other_header_val;
		ipmisc_mask->other_header_mask = 1;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_IPV6))
	{
		ipmisc_rule->is_ipv6 = rule->is_ipv6_val;
		ipmisc_mask->is_ipv6_mask = 1;
	}
	if(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_L3_FRAGMENT))
	{
		ipmisc_rule->l3_fragment = rule->is_fragement_val;
		ipmisc_mask->l3_fragment_mask = 1;
	}
	return SW_OK;
}
sw_error_t
_adpt_hppe_acl_rule_hw_add(a_uint32_t dev_id, a_uint32_t list_id,
		a_uint32_t rule_id, a_uint32_t rule_nr, fal_acl_rule_t * rule,
		a_uint32_t rule_type_map, a_uint32_t allocated_entries)
{
	union ipo_rule_reg_u hw_reg = {0};
	union ipo_mask_reg_u hw_mask = {0};
	sw_error_t rv = 0;
	a_uint32_t hw_entry = 0;
	a_uint32_t i = 0;

	for( i = 0; i < ADPT_ACL_HPPE_RULE_TYPE_NUM; i++)
	{
		if(!((1<<i)&rule_type_map))
			continue;
		memset(&hw_reg, 0, sizeof(hw_reg));
		memset(&hw_mask, 0, sizeof(hw_mask));

		if(i == ADPT_ACL_HPPE_VLAN_RULE)
		{
			_adpt_hppe_acl_vlan_rule_sw_2_hw(rule, &hw_reg, &hw_mask);
		}
		else if(i == ADPT_ACL_HPPE_MAC_DA_RULE)
		{
			_adpt_hppe_acl_mac_rule_sw_2_hw(rule, 1, &hw_reg, &hw_mask);
		}
		else if(i == ADPT_ACL_HPPE_MAC_SA_RULE)
		{
			_adpt_hppe_acl_mac_rule_sw_2_hw(rule, 0, &hw_reg, &hw_mask);
		}
		else if(i == ADPT_ACL_HPPE_L2_MISC_RULE)
		{
			_adpt_hppe_acl_l2_misc_rule_sw_2_hw(rule, &hw_reg, &hw_mask);
		}
		else if(i == ADPT_ACL_HPPE_IPV4_DIP_RULE)
		{
			_adpt_hppe_acl_ipv4_rule_sw_2_hw(rule, 1, &hw_reg, &hw_mask);
		}
		else if(i == ADPT_ACL_HPPE_IPV4_SIP_RULE)
		{
			_adpt_hppe_acl_ipv4_rule_sw_2_hw(rule, 0, &hw_reg, &hw_mask);
		}
		else if(i == ADPT_ACL_HPPE_IPV6_DIP0_RULE)
		{
			_adpt_hppe_acl_ipv6_rule_sw_2_hw(rule, 1, 0, &hw_reg, &hw_mask);
		}
		else if(i == ADPT_ACL_HPPE_IPV6_DIP1_RULE)
		{
			_adpt_hppe_acl_ipv6_rule_sw_2_hw(rule, 1, 1, &hw_reg, &hw_mask);
		}
		else if(i == ADPT_ACL_HPPE_IPV6_DIP2_RULE)
		{
			_adpt_hppe_acl_ipv6_rule_sw_2_hw(rule, 1, 2, &hw_reg, &hw_mask);
		}
		else if(i == ADPT_ACL_HPPE_IPV6_SIP0_RULE)
		{
			_adpt_hppe_acl_ipv6_rule_sw_2_hw(rule, 0, 0, &hw_reg, &hw_mask);
		}
		else if(i == ADPT_ACL_HPPE_IPV6_SIP1_RULE)
		{
			_adpt_hppe_acl_ipv6_rule_sw_2_hw(rule, 0, 1, &hw_reg, &hw_mask);
		}
		else if(i == ADPT_ACL_HPPE_IPV6_SIP2_RULE)
		{
			_adpt_hppe_acl_ipv6_rule_sw_2_hw(rule, 0, 2, &hw_reg, &hw_mask);
		}
		else if(i == ADPT_ACL_HPPE_IPMISC_RULE)
		{
			_adpt_hppe_acl_ipmisc_rule_sw_2_hw(rule, &hw_reg, &hw_mask);
		}

		if(!hw_reg.bf.range_en)
		{
			hw_entry = _acl_bit_index(allocated_entries, 8, 1);
		}
		if(hw_entry == 0xff || hw_reg.bf.range_en)
		{
			hw_entry = _acl_bit_index(allocated_entries, 8, 2);
		}
		if(hw_entry == 0xff)
			return SW_NO_RESOURCE;
		allocated_entries &= (~(1<<hw_entry));

		printk("%s, %d: rule and mask set hw_entry = %d\n", __FUNCTION__, __LINE__,
				list_id*ADPT_ACL_ENTRY_NUM_PER_LIST+hw_entry);
		rv |= hppe_ipo_rule_reg_set(dev_id, list_id*ADPT_ACL_ENTRY_NUM_PER_LIST+hw_entry, &hw_reg);
		rv |= hppe_ipo_mask_reg_set(dev_id, list_id*ADPT_ACL_ENTRY_NUM_PER_LIST+hw_entry, &hw_mask);
		if(rv != SW_OK)
			return rv;
	}

	return SW_OK;
}

sw_error_t
adpt_hppe_acl_rule_add(a_uint32_t dev_id, a_uint32_t list_id,
		a_uint32_t rule_id, a_uint32_t rule_nr, fal_acl_rule_t * rule)
{
	a_uint32_t rule_type_map = 0;
	a_uint32_t rule_type_count = 0;
	a_uint32_t index = 0;
	sw_error_t rv = 0;
	union rule_ext_1_reg_u ext_1 = {0};
	union rule_ext_2_reg_u ext_2 = {0};
	union rule_ext_4_reg_u ext_4 = {0};

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(rule);

	printk("%s, %d: fields[0] = 0x%x, fields[1] = 0x%x\n", __FUNCTION__, __LINE__, rule->field_flg[0], rule->field_flg[1]);
	if(rule->rule_type == FAL_ACL_RULE_IP4)/*input ipv4 type*/
		_adpt_hppe_acl_ipv4_fields_check(dev_id, list_id, rule_id, rule_nr, rule, &rule_type_map);
	else if(rule->rule_type == FAL_ACL_RULE_IP6)/*input ipv6 type*/
		_adpt_hppe_acl_ipv6_fields_check(dev_id, list_id, rule_id, rule_nr, rule, &rule_type_map);
	_adpt_hppe_acl_l2_fields_check(dev_id, list_id, rule_id, rule_nr, rule, &rule_type_map);

	if(rule_type_map == 0)
	{
		if((FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_IPV6)) ||
			(FAL_FIELD_FLG_TST(rule->field_flg, FAL_ACL_FIELD_IP)))
		rule_type_map |= (1<<ADPT_ACL_HPPE_MAC_DA_RULE);
	}

	printk("%s, %d: rule_type_map = 0x%x\n", __FUNCTION__, __LINE__, rule_type_map);

	rule_type_count = _acl_bits_count(rule_type_map, ADPT_ACL_HPPE_RULE_TYPE_NUM, 0);
	printk("%s, %d: rule_type_count = %d\n", __FUNCTION__, __LINE__, rule_type_count);

	if(rule_type_count > ADPT_ACL_RULE_NUM_PER_LIST)
	{
		printk("%s, %d: rule_type_count = %d > 8\n", __FUNCTION__, __LINE__, rule_type_count);
		return SW_NOT_SUPPORTED;
	}

	rv = _adpt_hppe_acl_alloc_entries(dev_id, list_id, rule_id, rule_nr, rule, rule_type_map, rule_type_count, &index);
	if(rv != SW_OK)
		return rv;

	rv = _adpt_hppe_acl_rule_hw_add(dev_id, list_id, rule_id, rule_nr, rule, rule_type_map, s_acl_entries[index].entries);
	if(rv != SW_OK)
		return rv;

	if(s_acl_entries[index].ext_1 != 0)
	{
		rv |= hppe_rule_ext_1_reg_get(dev_id, list_id, &ext_1);
		ext_1.val |= s_acl_entries[index].ext_1;
		printk("%s, %d: ext_1.val = 0x%x\n", __FUNCTION__, __LINE__, ext_1.val);
		rv |= hppe_rule_ext_1_reg_set(dev_id, list_id, &ext_1);
	}
	if(s_acl_entries[index].ext_2 != 0)
	{
		rv |= hppe_rule_ext_2_reg_get(dev_id, list_id, &ext_2);
		ext_2.val |= s_acl_entries[index].ext_2;
		printk("%s, %d: ext_2.val = 0x%x\n", __FUNCTION__, __LINE__, ext_2.val);
		rv |= hppe_rule_ext_2_reg_set(dev_id, list_id, &ext_2);
	}
	if(s_acl_entries[index].ext_4 != 0)
	{
		rv |= hppe_rule_ext_4_reg_get(dev_id, list_id, &ext_4);
		ext_4.val |= s_acl_entries[index].ext_4;
		printk("%s, %d: ext_4.val = 0x%x\n", __FUNCTION__, __LINE__, ext_4.val);
		rv |= hppe_rule_ext_4_reg_set(dev_id, list_id, &ext_4);
	}

	g_acl_list[dev_id][list_id].rule_hw_entry[rule_id] = s_acl_entries[index].entries;
	g_acl_list[dev_id][list_id].ext1_val[rule_id] = s_acl_entries[index].ext_1;
	g_acl_list[dev_id][list_id].ext2_val[rule_id] = s_acl_entries[index].ext_2;
	g_acl_list[dev_id][list_id].ext4_val[rule_id] = s_acl_entries[index].ext_4;
	g_acl_list[dev_id][list_id].free_hw_entry_bitmap &= (~(s_acl_entries[index].entries));
	g_acl_list[dev_id][list_id].free_hw_entry_count -= s_acl_entries[index].num;

	return SW_OK;
}

sw_error_t
adpt_hppe_acl_rule_delete(a_uint32_t dev_id, a_uint32_t list_id, a_uint32_t rule_id, a_uint32_t rule_nr)
{
	a_uint8_t hw_entries = g_acl_list[dev_id][list_id].rule_hw_entry[rule_id];
	a_uint8_t ext1_val = g_acl_list[dev_id][list_id].ext1_val[rule_id];
	a_uint8_t ext2_val = g_acl_list[dev_id][list_id].ext2_val[rule_id];
	a_uint8_t ext4_val = g_acl_list[dev_id][list_id].ext4_val[rule_id];
	a_uint8_t i;
	union ipo_rule_reg_u hw_reg = {0};
	union ipo_mask_reg_u hw_mask = {0};
	union rule_ext_1_reg_u ext_1 = {0};
	union rule_ext_2_reg_u ext_2 = {0};
	union rule_ext_4_reg_u ext_4 = {0};
	sw_error_t rv = 0;

	ADPT_DEV_ID_CHECK(dev_id);

	memset(&hw_reg, 0, sizeof(hw_reg));
	memset(&hw_mask, 0, sizeof(hw_mask));
	while( i < ADPT_ACL_ENTRY_NUM_PER_LIST )
	{
		if((1<<i) & hw_entries)
		{
			g_acl_list[dev_id][list_id].free_hw_entry_count++;
			g_acl_list[dev_id][list_id].free_hw_entry_bitmap |= (1<<i);
			rv |= hppe_ipo_rule_reg_set(dev_id,
				list_id*ADPT_ACL_ENTRY_NUM_PER_LIST+i, &hw_reg);
			rv |= hppe_ipo_mask_reg_set(dev_id,
				list_id*ADPT_ACL_ENTRY_NUM_PER_LIST+i, &hw_mask);
		}
	}
	g_acl_list[dev_id][list_id].rule_hw_entry[rule_id] = 0;

	rv |= hppe_rule_ext_1_reg_get(dev_id, list_id, &ext_1);
	ext_1.val &= (~g_acl_list[dev_id][list_id].ext1_val[rule_id]);
	printk("%s, %d: ext_1.val = 0x%x\n", __FUNCTION__, __LINE__, ext_1.val);
	rv |= hppe_rule_ext_1_reg_set(dev_id, list_id, &ext_1);

	rv |= hppe_rule_ext_2_reg_get(dev_id, list_id, &ext_2);
	ext_2.val &= (~g_acl_list[dev_id][list_id].ext2_val[rule_id]);
	printk("%s, %d: ext_2.val = 0x%x\n", __FUNCTION__, __LINE__, ext_2.val);
	rv |= hppe_rule_ext_2_reg_set(dev_id, list_id, &ext_2);

	rv |= hppe_rule_ext_4_reg_get(dev_id, list_id, &ext_4);
	ext_4.val &= (~g_acl_list[dev_id][list_id].ext4_val[rule_id]);
	printk("%s, %d: ext_4.val = 0x%x\n", __FUNCTION__, __LINE__, ext_4.val);
	rv |= hppe_rule_ext_4_reg_set(dev_id, list_id, &ext_4);

	if(rv != SW_OK)
	{
		return rv;
	}

	return SW_OK;
}

static void _adpt_acl_reg_dump(a_uint8_t *reg, a_uint32_t len)
{
	a_int32_t i = 0;

	for(i = 0; i < len; i++)
	{
		if(i%32 == 0)
			printk("\n");
		printk("%02x ", reg[i]);
	}
	return;
}

static sw_error_t
_adpt_hppe_acl_rule_dump(a_uint32_t dev_id, a_uint32_t list_id, a_uint32_t rule_id)
{
	a_uint8_t i = 0;
	a_uint8_t hw_entries = g_acl_list[dev_id][list_id].rule_hw_entry[rule_id];
	union ipo_rule_reg_u hw_reg = {0};
	union ipo_mask_reg_u hw_mask = {0};

	if(hw_entries != 0)
	{
		printk("######list_id %d, rule_id %d\n", list_id, rule_id);
		for(i = 0; i < ADPT_ACL_ENTRY_NUM_PER_LIST; i++)
		{
			if((1<<i) & hw_entries)
			{
				hppe_ipo_rule_reg_get(dev_id,
					list_id*ADPT_ACL_ENTRY_NUM_PER_LIST+i, &hw_reg);
				hppe_ipo_mask_reg_get(dev_id,
					list_id*ADPT_ACL_ENTRY_NUM_PER_LIST+i, &hw_mask);
				printk("hw_entry %d\n", i);
				_adpt_acl_reg_dump((u_int8_t *)&hw_reg, sizeof(hw_reg));
				printk("\n");
				printk("hw_entry_mask %d\n", i);
				_adpt_acl_reg_dump((u_int8_t *)&hw_mask, sizeof(hw_mask));
				printk("\n");
			}
		}
	}

	return SW_OK;
}

sw_error_t
adpt_hppe_acl_rule_dump(a_uint32_t dev_id)
{
	a_uint32_t list_id, rule_id;

	ADPT_DEV_ID_CHECK(dev_id);

	for(list_id = 0; list_id < ADPT_ACL_LIST_NUM; list_id++)
	{
		for(rule_id = 0; rule_id < ADPT_ACL_RULE_NUM_PER_LIST; rule_id++)
		{
			_adpt_hppe_acl_rule_dump(dev_id, list_id, rule_id);
		}
	}
	return SW_OK;
}

sw_error_t
adpt_hppe_acl_list_creat(a_uint32_t dev_id, a_uint32_t list_id, a_uint32_t list_pri)
{
	ADPT_DEV_ID_CHECK(dev_id);
	g_acl_list[dev_id][list_id].list_pri = list_pri;
	g_acl_list[dev_id][list_id].free_hw_entry_bitmap = 0xff;
	g_acl_list[dev_id][list_id].free_hw_entry_count = 8;
	return SW_OK;
}

sw_error_t
adpt_hppe_acl_rule_src_filter_sts_set(a_uint32_t dev_id, a_uint32_t rule_id, a_bool_t enable)
{

	ADPT_DEV_ID_CHECK(dev_id);

	return SW_OK;
}
sw_error_t
adpt_hppe_acl_list_destroy(a_uint32_t dev_id, a_uint32_t list_id)
{

	ADPT_DEV_ID_CHECK(dev_id);

	return SW_OK;
}
sw_error_t
adpt_hppe_acl_port_udf_profile_set(a_uint32_t dev_id, fal_port_t port_id, fal_acl_udf_type_t udf_type, a_uint32_t offset, a_uint32_t length)
{

	ADPT_DEV_ID_CHECK(dev_id);

	return SW_OK;
}
sw_error_t adpt_hppe_acl_init(a_uint32_t dev_id)
{
	adpt_api_t *p_adpt_api = NULL;

	p_adpt_api = adpt_api_ptr_get(dev_id);

	if(p_adpt_api == NULL)
		return SW_FAIL;

	p_adpt_api->adpt_acl_list_bind = adpt_hppe_acl_list_bind;
	p_adpt_api->adpt_acl_port_udf_profile_get = adpt_hppe_acl_port_udf_profile_get;
	p_adpt_api->adpt_acl_rule_src_filter_sts_get = adpt_hppe_acl_rule_src_filter_sts_get;
	p_adpt_api->adpt_acl_rule_deactive = adpt_hppe_acl_rule_deactive;
	p_adpt_api->adpt_acl_list_dump = adpt_hppe_acl_list_dump;
	p_adpt_api->adpt_acl_status_get = adpt_hppe_acl_status_get;
	p_adpt_api->adpt_acl_status_set = adpt_hppe_acl_status_set;
	p_adpt_api->adpt_acl_rule_query = adpt_hppe_acl_rule_query;
	p_adpt_api->adpt_acl_list_unbind = adpt_hppe_acl_list_unbind;
	p_adpt_api->adpt_acl_rule_active = adpt_hppe_acl_rule_active;
	p_adpt_api->adpt_acl_rule_add = adpt_hppe_acl_rule_add;
	p_adpt_api->adpt_acl_rule_delete = adpt_hppe_acl_rule_delete;
	p_adpt_api->adpt_acl_rule_dump = adpt_hppe_acl_rule_dump;
	p_adpt_api->adpt_acl_list_creat = adpt_hppe_acl_list_creat;
	p_adpt_api->adpt_acl_rule_src_filter_sts_set = adpt_hppe_acl_rule_src_filter_sts_set;
	p_adpt_api->adpt_acl_list_destroy = adpt_hppe_acl_list_destroy;
	p_adpt_api->adpt_acl_port_udf_profile_set = adpt_hppe_acl_port_udf_profile_set;

	_acl_slice_ext_bitmap_gen(3);
	_acl_slice_ext_bitmap_gen(4);
	_acl_slice_ext_bitmap_gen(5);
	_acl_slice_ext_bitmap_gen(6);
	_acl_slice_ext_bitmap_gen(7);
	_acl_slice_ext_bitmap_gen(8);
	return SW_OK;
}

/**
 * @}
 */
