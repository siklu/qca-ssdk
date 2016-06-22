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
 * @defgroup fal_gen FAL_CTRLPKT
 * @{
 */
#ifndef _FAL_CTRLPKT_H_
#define _FAL_CTRLPKT_H_

#ifdef __cplusplus
extern "C" {
#endif
/* __cplusplus */

#include "common/sw.h"
#include "fal/fal_type.h"


#if defined(SW_API_LOCK) && (!defined(HSL_STANDALONG))
#define FAL_CTRLPKT_API_LOCK
#define FAL_CTRLPKT_API_UNLOCK
#else
#define FAL_CTRLPKT_API_LOCK
#define FAL_CTRLPKT_API_UNLOCK
#endif


typedef struct {
	fal_fwd_cmd_t cmd;
	a_bool_t sg_byp;
	a_bool_t l2_filter_byp;
	a_bool_t in_stg_byp;
	a_bool_t in_vlan_fltr_byp;
} fal_ctrlpkt_cmd_t;

typedef struct
{
	a_bool_t	     mgt_eapol;
	a_bool_t       mgt_pppoe;
	a_bool_t       mgt_igmp;
	a_bool_t       mgt_arp_req;
	a_bool_t       mgt_arp_rep;
	a_bool_t       mgt_dhcp4;
	a_bool_t       mgt_mld;
	a_bool_t       mgt_ns;
	a_bool_t       mgt_na;
	a_bool_t       mgt_dhcp6;
} fal_ctrlpkt_protocol_type_t;

typedef struct {
	fal_ctrlpkt_cmd_t cmd;
	fal_pbmp_t port_map;
	a_uint32_t ethtype_profile_bitmap;
	a_uint32_t rfdb_profile_bitmap;
	fal_ctrlpkt_protocol_type_t protocol_type;
	a_bool_t valid;
} fal_ctrlpkt_profile_t;

sw_error_t fal_ethernet_type_profile_set(a_uint32_t dev_id, a_uint32_t profile_id, a_uint32_t ethernet_type, a_bool_t enable);
sw_error_t fal_ethernet_type_profile_get(a_uint32_t dev_id, a_uint32_t profile_id, a_uint32_t *ethernet_type, a_bool_t *enable);

sw_error_t fal_rfdb_profile_set(a_uint32_t dev_id, a_uint32_t profile_id, fal_mac_addr_t *addr, a_bool_t enable);
sw_error_t fal_rfdb_profile_get(a_uint32_t dev_id, a_uint32_t profile_id, fal_mac_addr_t *addr, a_bool_t *enable);

sw_error_t fal_ctrlpkt_profile_set(a_uint32_t dev_id, a_uint32_t profile_id, fal_ctrlpkt_profile_t *ctrlpkt);
sw_error_t fal_ctrlpkt_profile_get(a_uint32_t dev_id, a_uint32_t profile_id, fal_ctrlpkt_profile_t *ctrlpkt);

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* _FAL_CTRLPKT_H_ */
/**
 * @}
 */

