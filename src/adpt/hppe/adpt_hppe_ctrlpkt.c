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
#include "hppe_ctrlpkt_reg.h"
#include "hppe_ctrlpkt.h"
#include "hppe_fdb.h"
#include "adpt.h"

sw_error_t
adpt_ethernet_type_profile_set(a_uint32_t dev_id, a_uint32_t profile_id,
								a_uint32_t ethernet_type, a_bool_t enable)
{
	sw_error_t rtn = SW_OK;

	ADPT_DEV_ID_CHECK(dev_id);

	SW_RTN_ON_ERROR(hppe_ethertype_ctrl_ethertype_set(dev_id,
								profile_id, ethernet_type));
	SW_RTN_ON_ERROR(hppe_ethertype_ctrl_ethertype_en_set(dev_id,
								profile_id, (a_uint32_t)enable));

	return rtn;
}

sw_error_t
adpt_ethernet_type_profile_get(a_uint32_t dev_id, a_uint32_t profile_id,
								a_uint32_t *ethernet_type, a_bool_t *enable)
{
	sw_error_t rtn = SW_OK;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(ethernet_type);
	ADPT_NULL_POINT_CHECK(enable);

	SW_RTN_ON_ERROR(hppe_ethertype_ctrl_ethertype_get(dev_id,
								profile_id, ethernet_type));
	SW_RTN_ON_ERROR(hppe_ethertype_ctrl_ethertype_en_get(dev_id,
								profile_id, (a_uint32_t *)enable));

	return rtn;
}

sw_error_t
adpt_rfdb_profile_set(a_uint32_t dev_id, a_uint32_t profile_id,
						fal_mac_addr_t *addr, a_bool_t enable)
{
	sw_error_t rtn = SW_OK;
	a_uint64_t value = 0;

	ADPT_DEV_ID_CHECK(dev_id);

	value = ((((a_uint64_t)(addr->uc[5])) << 0) |
			(((a_uint64_t)(addr->uc[4])) << 8) |
			(((a_uint64_t)(addr->uc[3])) << 16) |
			(((a_uint64_t)(addr->uc[2])) << 24) |
			(((a_uint64_t)(addr->uc[1])) << 32) |
			(((a_uint64_t)(addr->uc[0])) << 40));

	SW_RTN_ON_ERROR(hppe_rfdb_tbl_mac_addr_set(dev_id, profile_id, value));
	SW_RTN_ON_ERROR(hppe_rfdb_tbl_valid_set(dev_id, profile_id, (a_uint32_t)enable));

	return rtn;
}

sw_error_t
adpt_rfdb_profile_get(a_uint32_t dev_id, a_uint32_t profile_id,
						fal_mac_addr_t *addr, a_bool_t *enable)
{
	sw_error_t rtn = SW_OK;
	a_uint64_t value = 0;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(addr);
	ADPT_NULL_POINT_CHECK(enable);

	SW_RTN_ON_ERROR(hppe_rfdb_tbl_mac_addr_get(dev_id, profile_id, &value));
	addr->uc[0] = (a_uint8_t)((value >> 40)& 0xff);
	addr->uc[1] = (a_uint8_t)((value >> 32) & 0xff);
	addr->uc[2] = (a_uint8_t)((value >> 24) & 0xff);
	addr->uc[3] = (a_uint8_t)((value >> 16) & 0xff);
	addr->uc[4] = (a_uint8_t)((value >> 8) & 0xff);
	addr->uc[5] = (a_uint8_t)((value >> 0) & 0xff);

	SW_RTN_ON_ERROR(hppe_rfdb_tbl_valid_get(dev_id, profile_id, (a_uint32_t *)enable));

	return rtn;
}

sw_error_t
adpt_ctrlpkt_profile_set(a_uint32_t dev_id, a_uint32_t profile_id,
							fal_ctrlpkt_profile_t *ctrlpkt)
{
	sw_error_t rtn = SW_OK;
	union app_ctrl_u entry;

	memset(&entry, 0, sizeof(union app_ctrl_u));

	ADPT_DEV_ID_CHECK(dev_id);

	entry.bf.valid = ctrlpkt->valid;
	entry.bf.rfdb_include = ctrlpkt->rfdb_profile_bitmap?1:0;
	entry.bf.rfdb_index_bitmap_0 = (ctrlpkt->rfdb_profile_bitmap & 0x3fffffff);
	entry.bf.rfdb_index_bitmap_1 = (ctrlpkt->rfdb_profile_bitmap >> 30);

	if (ctrlpkt->protocol_type.mgt_eapol)
		entry.bf.protocol_bitmap |= (0x1 << 0);
	if (ctrlpkt->protocol_type.mgt_pppoe)
		entry.bf.protocol_bitmap |= (0x1 << 1);
	if (ctrlpkt->protocol_type.mgt_igmp)
		entry.bf.protocol_bitmap |= (0x1 << 2);
	if (ctrlpkt->protocol_type.mgt_arp_req)
		entry.bf.protocol_bitmap |= (0x1 << 3);
	if (ctrlpkt->protocol_type.mgt_arp_rep)
		entry.bf.protocol_bitmap |= (0x1 << 4);
	if (ctrlpkt->protocol_type.mgt_dhcp4)
		entry.bf.protocol_bitmap |= (0x1 << 5);
	if (ctrlpkt->protocol_type.mgt_mld)
		entry.bf.protocol_bitmap |= (0x1 << 6);
	if (ctrlpkt->protocol_type.mgt_ns)
		entry.bf.protocol_bitmap |= (0x1 << 7);
	if (ctrlpkt->protocol_type.mgt_na)
		entry.bf.protocol_bitmap |= (0x1 << 8);
	if (ctrlpkt->protocol_type.mgt_dhcp6)
		entry.bf.protocol_bitmap |= (0x1 << 9);

	entry.bf.protocol_include = entry.bf.protocol_bitmap?1:0;

	entry.bf.ethertype_include = ctrlpkt->ethtype_profile_bitmap?1:0;
	entry.bf.ethertype_index_bitmap_0 = (ctrlpkt->ethtype_profile_bitmap & 0x3);
	entry.bf.ethertype_index_bitmap_1 = (ctrlpkt->ethtype_profile_bitmap >> 2);

	entry.bf.portbitmap_include = ctrlpkt->port_map?1:0;
	entry.bf.portbitmap = ctrlpkt->port_map;

	entry.bf.in_vlan_fltr_byp = ctrlpkt->cmd.in_vlan_fltr_byp?1:0;
	entry.bf.in_stg_byp = ctrlpkt->cmd.in_stg_byp?1:0;
	entry.bf.l2_sec_byp = ctrlpkt->cmd.l2_filter_byp?1:0;
	entry.bf.sg_byp = ctrlpkt->cmd.sg_byp?1:0;
	entry.bf.cmd = (a_uint32_t)ctrlpkt->cmd.cmd;

	if (entry.bf.valid == A_FALSE)
		memset(&entry, 0, sizeof(union app_ctrl_u));

	SW_RTN_ON_ERROR(hppe_app_ctrl_set(dev_id, profile_id,
						&entry));

	return rtn;
}

sw_error_t
adpt_ctrlpkt_profile_get(a_uint32_t dev_id, a_uint32_t profile_id,
							fal_ctrlpkt_profile_t *ctrlpkt)
{
	sw_error_t rtn = SW_OK;
	union app_ctrl_u entry;

	memset(&entry, 0, sizeof(union app_ctrl_u));

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(ctrlpkt);

	SW_RTN_ON_ERROR(hppe_app_ctrl_get(dev_id, profile_id,
						&entry));

	ctrlpkt->valid = entry.bf.valid;
	ctrlpkt->cmd.cmd = entry.bf.cmd;
	ctrlpkt->cmd.sg_byp = entry.bf.sg_byp;
	ctrlpkt->cmd.l2_filter_byp = entry.bf.l2_sec_byp;
	ctrlpkt->cmd.in_stg_byp = entry.bf.in_stg_byp;
	ctrlpkt->cmd.in_vlan_fltr_byp = entry.bf.in_vlan_fltr_byp;

	if (entry.bf.portbitmap_include)
		ctrlpkt->port_map = entry.bf.portbitmap;

	if (entry.bf.ethertype_include)
		ctrlpkt->ethtype_profile_bitmap = entry.bf.ethertype_index_bitmap_0 |
								(entry.bf.ethertype_index_bitmap_1 << 2);
	if (ctrlpkt->protocol_type.mgt_eapol)
		entry.bf.protocol_bitmap |= (0x1 << 0);
	if (ctrlpkt->protocol_type.mgt_pppoe)
		entry.bf.protocol_bitmap |= (0x1 << 1);
	if (ctrlpkt->protocol_type.mgt_igmp)
		entry.bf.protocol_bitmap |= (0x1 << 2);
	if (ctrlpkt->protocol_type.mgt_arp_req)
		entry.bf.protocol_bitmap |= (0x1 << 3);
	if (ctrlpkt->protocol_type.mgt_arp_rep)
		entry.bf.protocol_bitmap |= (0x1 << 4);
	if (ctrlpkt->protocol_type.mgt_dhcp4)
		entry.bf.protocol_bitmap |= (0x1 << 5);
	if (ctrlpkt->protocol_type.mgt_mld)
		entry.bf.protocol_bitmap |= (0x1 << 6);
	if (ctrlpkt->protocol_type.mgt_ns)
		entry.bf.protocol_bitmap |= (0x1 << 7);
	if (ctrlpkt->protocol_type.mgt_na)
		entry.bf.protocol_bitmap |= (0x1 << 8);
	if (ctrlpkt->protocol_type.mgt_dhcp6)
		entry.bf.protocol_bitmap |= (0x1 << 9);

	if (entry.bf.protocol_include) {
		ctrlpkt->protocol_type.mgt_eapol = (entry.bf.protocol_bitmap & (0x1 << 0))?1:0;
		ctrlpkt->protocol_type.mgt_pppoe = (entry.bf.protocol_bitmap & (0x1 << 1))?1:0;
		ctrlpkt->protocol_type.mgt_igmp = (entry.bf.protocol_bitmap & (0x1 << 2))?1:0;
		ctrlpkt->protocol_type.mgt_arp_req = (entry.bf.protocol_bitmap & (0x1 << 3))?1:0;
		ctrlpkt->protocol_type.mgt_arp_rep = (entry.bf.protocol_bitmap & (0x1 << 4))?1:0;
		ctrlpkt->protocol_type.mgt_dhcp4 = (entry.bf.protocol_bitmap & (0x1 << 5))?1:0;
		ctrlpkt->protocol_type.mgt_mld = (entry.bf.protocol_bitmap & (0x1 << 6))?1:0;
		ctrlpkt->protocol_type.mgt_ns = (entry.bf.protocol_bitmap & (0x1 << 7))?1:0;
		ctrlpkt->protocol_type.mgt_na = (entry.bf.protocol_bitmap & (0x1 << 8))?1:0;
		ctrlpkt->protocol_type.mgt_dhcp6 = (entry.bf.protocol_bitmap & (0x1 << 9))?1:0;
	}

	if (entry.bf.rfdb_include)
		ctrlpkt->rfdb_profile_bitmap = entry.bf.rfdb_index_bitmap_0|
								(entry.bf.rfdb_index_bitmap_1 << 30);

	return rtn;
}

sw_error_t adpt_hppe_ctrlpkt_init(a_uint32_t dev_id)
{
	adpt_api_t *p_adpt_api = NULL;

	p_adpt_api = adpt_api_ptr_get(dev_id);

	if(p_adpt_api == NULL)
		return SW_FAIL;

	p_adpt_api->adpt_ethernet_type_profile_set = adpt_ethernet_type_profile_set;
	p_adpt_api->adpt_ethernet_type_profile_get = adpt_ethernet_type_profile_get;
	p_adpt_api->adpt_rfdb_profile_set = adpt_rfdb_profile_set;
	p_adpt_api->adpt_rfdb_profile_get = adpt_rfdb_profile_get;
	p_adpt_api->adpt_ctrlpkt_profile_set = adpt_ctrlpkt_profile_set;
	p_adpt_api->adpt_ctrlpkt_profile_get = adpt_ctrlpkt_profile_get;

	return SW_OK;
}

/**
 * @}
 */

