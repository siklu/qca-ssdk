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
 * @defgroup fal_flow
 * @{
 */
#ifndef _FAL_FLOW_H_
#define _FAL_FLOW_H_

#ifdef __cplusplus
extern "C" {
#endif                          /* __cplusplus */

#include "common/sw.h"
#include "fal/fal_type.h"
#include "fal/fal_ip.h"

typedef enum {
	FAL_FLOW_L3_UNICAST = 0,
	FAL_FLOW_L2_UNICAST,
	FAL_FLOW_MCAST,
} fal_flow_pkt_type_t;

typedef enum {
	FAL_FLOW_LAN_TO_LAN_DIR = 0,
	FAL_FLOW_LAN_TO_WAN_DIR,
	FAL_FLOW_WAN_TO_LAN_DIR,
	FAL_FLOW_WAN_TO_WAN_DIR,
	FAL_FLOW_UNKOWN_DIR_DIR,
} fal_flow_direction_t;

typedef enum {
	FAL_FLOW_FORWARD = 0,
	FAL_FLOW_SNAT,
	FAL_FLOW_DNAT,
	FAL_FLOW_ROUTE,
	FAL_FLOW_BRIDGE,
} fal_flow_fwd_type_t;

/* FLOW entry type field */
#define FAL_FLOW_IP4_5TUPLE_ADDR        0x1
#define FAL_FLOW_IP6_5TUPLE_ADDR        0x2
#define FAL_FLOW_IP4_3TUPLE_ADDR        0x4
#define FAL_FLOW_IP6_3TUPLE_ADDR        0x8

#define FAL_FLOW_OP_MODE_KEY         0x0
#define FAL_FLOW_OP_MODE_INDEX     0x1
#define FAL_FLOW_OP_MODE_FLUSH     0x2

#define FAL_FLOW_PROTOCOL_OTHER    0
#define FAL_FLOW_PROTOCOL_TCP	        1
#define FAL_FLOW_PROTOCOL_UDP	  2
#define FAL_FLOW_PROTOCOL_UDPLITE  3


typedef struct {
	fal_flow_type_t miss_action;
	a_bool_t frag_bypass;
	a_bool_t tcp_spec_bypass;
	a_bool_t all_bypass;
	a_uint8_t key_sel;
} fal_flow_ctrl_t;

typedef struct {
	a_bool_t valid;
	a_uint32_t entry_id;
	a_uint8_t entry_type;
	a_uint8_t host_addr_type;
	a_uint16_t host_addr_index;
	a_uint8_t protocol;
	a_uint8_t age;
	a_bool_t src_intf_valid;
	a_uint8_t src_intf_index;
	a_uint8_t fwd_type;
	a_uint16_t snat_nexthop;
	a_uint16_t snat_srcport;
	a_uint16_t dnat_nexthop;
	a_uint16_t dnat_dstport;
	a_uint16_t route_nexthop;
	a_bool_t port_valid;
	fal_port_t route_port;
	fal_port_t bridge_port;
	a_bool_t de_acce;
	a_bool_t copy_tocpu;
	a_uint8_t syn_toggle;
	a_uint8_t pri_profile;
	a_uint8_t sevice_code;
	a_uint8_t ip_type;
	union {
		fal_ip4_addr_t ipv4;
		fal_ip6_addr_t ipv6;
	} flow_ip;
	a_uint16_t src_port;
	a_uint16_t dst_port;
	a_uint32_t tree_id;
	a_uint32_t pkt_count;
	a_uint64_t byte_count;
} fal_flow_entry_t;

typedef struct {
	fal_fwd_cmd_t src_if_check;
	a_bool_t src_if_check_de_acce;
	a_bool_t service_loop_en;
	fal_fwd_cmd_t service_loop;
	a_bool_t service_loop_de_acce;
	fal_fwd_cmd_t flow_de_acce;
	fal_fwd_cmd_t sync_mismatch;
	a_bool_t sync_mismatch_de_acce;
	a_uint8_t hash_mode_0;
	a_uint8_t hash_mode_1;
} fal_flow_global_cfg_t;

typedef struct {
	fal_flow_entry_t flow_entry;
	fal_host_entry_t host_entry;
} fal_flow_host_entry_t;

typedef struct {
	a_uint16_t age_time;
	a_uint16_t unit;
} fal_flow_age_timer_t;

sw_error_t
fal_flow_status_set(a_uint32_t dev_id, a_bool_t enable);

sw_error_t
fal_flow_status_get(a_uint32_t dev_id, a_bool_t *enable);

sw_error_t
fal_flow_age_timer_set(a_uint32_t dev_id, fal_flow_age_timer_t *age_timer);

sw_error_t
fal_flow_age_timer_get(a_uint32_t dev_id, fal_flow_age_timer_t *age_timer);

sw_error_t
fal_flow_ctrl_set(
		a_uint32_t dev_id,
		fal_flow_pkt_type_t type,
		fal_flow_direction_t dir,
		fal_flow_ctrl_t *ctrl);

sw_error_t
fal_flow_ctrl_get(
		a_uint32_t dev_id,
		fal_flow_pkt_type_t type,
		fal_flow_direction_t dir,
		fal_flow_ctrl_t *ctrl);

sw_error_t
fal_flow_entry_add(
		a_uint32_t dev_id,
		a_uint32_t add_mode, /*index or hash*/
		fal_flow_entry_t *flow_entry);

sw_error_t
fal_flow_entry_del(
		a_uint32_t dev_id,
		a_uint32_t del_mode,
		fal_flow_entry_t *flow_entry);

sw_error_t
fal_flow_entry_get(
		a_uint32_t dev_id,
		a_uint32_t get_mode,
		fal_flow_entry_t *flow_entry);

sw_error_t
fal_flow_host_add(
		a_uint32_t dev_id,
		a_uint32_t add_mode,
		fal_flow_host_entry_t *flow_host_entry);

sw_error_t
fal_flow_host_del(
		a_uint32_t dev_id,
		a_uint32_t del_mode,
		fal_flow_host_entry_t *flow_host_entry);

sw_error_t
fal_flow_host_get(
		a_uint32_t dev_id,
		a_uint32_t get_mode,
		fal_flow_host_entry_t *flow_host_entry);

sw_error_t
fal_flow_global_cfg_get(
		a_uint32_t dev_id,
		fal_flow_global_cfg_t *cfg);

sw_error_t
fal_flow_global_cfg_set(
		a_uint32_t dev_id,
		fal_flow_global_cfg_t *cfg);

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* _FAL_FLOW_H_ */

/**
 * @}
 */

