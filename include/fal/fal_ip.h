/*
 * Copyright (c) 2012, 2015, The Linux Foundation. All rights reserved.
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
 * @defgroup fal_ip FAL_IP
 * @{
 */
#ifndef _FAL_IP_H_
#define _FAL_IP_H_

#ifdef __cplusplus
extern "C" {
#endif                          /* __cplusplus */

#include "common/sw.h"
#include "fal/fal_type.h"
#include "fal_multi.h"

#define FAL_MIN_VRF_ID 0
#define FAL_MAX_VRF_ID 7
    /* IP WCMP hash key flags */
#define FAL_WCMP_HASH_KEY_SIP             0x1
#define FAL_WCMP_HASH_KEY_DIP             0x2
#define FAL_WCMP_HASH_KEY_SPORT           0x4
#define FAL_WCMP_HASH_KEY_DPORT           0x8

    /* IP entry operation flags */
#define FAL_IP_ENTRY_ID_EN               0x1
#define FAL_IP_ENTRY_INTF_EN             0x2
#define FAL_IP_ENTRY_PORT_EN             0x4
#define FAL_IP_ENTRY_STATUS_EN           0x8
#define FAL_IP_ENTRY_IPADDR_EN           0x10
#define FAL_IP_ENTRY_ALL_EN           0x20

    /* IP host entry structure flags field */
#define FAL_IP_IP4_ADDR                         0x1
#define FAL_IP_IP6_ADDR                         0x2
#define FAL_IP_CPU_ADDR                         0x4
#define FAL_IP_IP4_ADDR_MCAST              0x8
#define FAL_IP_IP6_ADDR_MCAST              0x10

	typedef struct {
		a_uint8_t vsi;
	        fal_ip4_addr_t sip4_addr;
	        fal_ip6_addr_t sip6_addr;
	} fal_host_mcast_t;

    typedef struct
    {
        a_uint32_t rx_pkt;
        a_uint64_t rx_byte;
        a_uint32_t rx_drop_pkt;
        a_uint64_t rx_drop_byte;
        a_uint32_t tx_pkt;
        a_uint64_t tx_byte;
        a_uint32_t tx_drop_pkt;
        a_uint64_t tx_drop_byte;
    } fal_ip_cnt_t;

    typedef struct
    {
        a_uint32_t entry_id;
        a_uint32_t flags;
        a_uint32_t status;
        fal_ip4_addr_t ip4_addr;
        fal_ip6_addr_t ip6_addr;
        fal_mac_addr_t mac_addr;
        a_uint32_t intf_id;
        a_uint32_t lb_num;/*total 3 bits for load balance and highest bit for load balance enable or not*/
        a_uint32_t vrf_id;
        a_uint32_t expect_vid;
        fal_port_t port_id;
        a_bool_t mirror_en;
        a_bool_t counter_en;
        a_uint32_t counter_id;
        a_uint32_t packet;
        a_uint32_t byte;
        a_bool_t pppoe_en;
        a_uint32_t pppoe_id;
        fal_fwd_cmd_t action;
        a_uint8_t syn_toggle;
        a_uint8_t lan_wan;
        fal_host_mcast_t mcast_info;
    } fal_host_entry_t;

    typedef enum
    {
        FAL_MAC_IP_GUARD = 0,
        FAL_MAC_IP_PORT_GUARD,
        FAL_MAC_IP_VLAN_GUARD,
        FAL_MAC_IP_PORT_VLAN_GUARD,
        FAL_NO_SOURCE_GUARD,
    } fal_source_guard_mode_t;

    typedef enum
    {
        FAL_DEFAULT_FLOW_FORWARD = 0,
        FAL_DEFAULT_FLOW_DROP,
        FAL_DEFAULT_FLOW_RDT_TO_CPU,
        FAL_DEFAULT_FLOW_ADMIT_ALL,
    } fal_default_flow_cmd_t;

    typedef enum
    {
        FAL_FLOW_LAN_TO_LAN = 0,
        FAL_FLOW_WAN_TO_LAN,
        FAL_FLOW_LAN_TO_WAN,
        FAL_FLOW_WAN_TO_WAN,
    } fal_flow_type_t;

typedef enum
{
	FAL_GLB_LOCK_TIME_DISABLE = 0,
	FAL_GLB_LOCK_TIME_100US,
	FAL_GLB_LOCK_TIME_1MS,
	FAL_GLB_LOCK_TIME_10MS,
} fal_glb_lock_time_t;
		

    typedef enum
    {
        FAL_ARP_LEARN_LOCAL = 0,
        FAL_ARP_LEARN_ALL,
    } fal_arp_learn_mode_t;

    /* IP host entry auto learn arp packets type */
#define FAL_ARP_LEARN_REQ                0x1
#define FAL_ARP_LEARN_ACK                0x2

    typedef struct
    {
        a_uint32_t entry_id;
        a_uint32_t vrf_id;
        a_uint16_t vid_low;
        a_uint16_t vid_high;
        fal_mac_addr_t mac_addr;
        a_bool_t ip4_route;
        a_bool_t ip6_route;
    } fal_intf_mac_entry_t;

    typedef struct
    {
        a_uint32_t nh_nr;
        a_uint32_t nh_id[16];
    } fal_ip_wcmp_t;

	typedef struct
    {
        fal_mac_addr_t mac_addr;
        fal_ip4_addr_t ip4_addr;
		a_uint32_t     vid;
		a_uint8_t      load_balance;
    } fal_ip4_rfs_t;

	typedef struct
    {
        fal_mac_addr_t mac_addr;
        fal_ip6_addr_t ip6_addr;
		a_uint32_t     vid;
		a_uint8_t      load_balance;
    } fal_ip6_rfs_t;

    typedef struct
    {
        a_bool_t valid;
        a_uint32_t vrf_id;
        fal_addr_type_t ip_version; /*0 for IPv4 and 1 for IPv6*/
        a_uint32_t droute_type; /*0 for ARP and 1 for WCMP*/
        a_uint32_t index;/*when droute_type equals 0, means ARP entry index or means WCMP indexs*/
    } fal_default_route_t;

    typedef struct
    {
        a_bool_t valid;
        a_uint32_t vrf_id;
        a_uint32_t ip_version; /*0 for IPv4 and 1 for IPv6*/
        union {
        fal_ip4_addr_t ip4_addr;
        fal_ip6_addr_t ip6_addr;
	}route_addr;
        a_uint32_t prefix_length;/*For IPv4, up to 32 and for IPv6, up to 128*/
    } fal_host_route_t;

    typedef struct
    {
        a_bool_t l3_if_valid;
        a_uint32_t l3_if_index;        	  
    } fal_intf_id_t;

	typedef enum
	{
		FAL_MC_MODE_GV = 0,
		FAL_MC_MODE_SGV
	} fal_mc_mode_t;

	typedef struct
	{
		a_bool_t l2_ipv4_mc_en;
		fal_mc_mode_t l2_ipv4_mc_mode;
		a_bool_t l2_ipv6_mc_en;
		fal_mc_mode_t l2_ipv6_mc_mode;
	} fal_mc_mode_cfg_t;

	typedef struct
	{
		a_bool_t ipv4_sg_en;
		fal_fwd_cmd_t ipv4_sg_vio_cmd;
		a_bool_t ipv4_sg_port_en;
		a_bool_t ipv4_sg_svlan_en;
		a_bool_t ipv4_sg_cvlan_en;
		fal_fwd_cmd_t ipv4_src_unk_cmd;
		a_bool_t ipv6_sg_en;
		fal_fwd_cmd_t ipv6_sg_vio_cmd;
		a_bool_t ipv6_sg_port_en;
		a_bool_t ipv6_sg_svlan_en;
		a_bool_t ipv6_sg_cvlan_en;
		fal_fwd_cmd_t ipv6_src_unk_cmd;
	} fal_sg_cfg_t;

	typedef struct
	{
		a_bool_t ipv4_arp_sg_en;
		fal_fwd_cmd_t ipv4_arp_sg_vio_cmd;
		a_bool_t ipv4_arp_sg_port_en;
		a_bool_t ipv4_arp_sg_svlan_en;
		a_bool_t ipv4_arp_sg_cvlan_en;
		fal_fwd_cmd_t ipv4_arp_src_unk_cmd;
		a_bool_t ip_nd_sg_en;
		fal_fwd_cmd_t ip_nd_sg_vio_cmd;
		a_bool_t ip_nd_sg_port_en;
		a_bool_t ip_nd_sg_svlan_en;
		a_bool_t ip_nd_sg_cvlan_en;
		fal_fwd_cmd_t ip_nd_src_unk_cmd;
	} fal_arp_sg_cfg_t;

	typedef struct
	{
		a_bool_t valid;
		a_uint8_t type;
		fal_fwd_cmd_t fwd_cmd;
		fal_port_t port;
		a_uint8_t lan_wan;
		union {
			fal_ip4_addr_t ip4_addr;
			fal_ip6_addr_t ip6_addr;
		} route_addr;
		union {
			fal_ip4_addr_t ip4_addr_mask;
			fal_ip6_addr_t ip6_addr_mask;
		} route_addr_mask;
	} fal_network_route_entry_t;

	typedef struct {
		a_bool_t valid;
		fal_mac_addr_t mac_addr;
	} fal_macaddr_entry_t;

	typedef struct {
		a_uint16_t mru;
		a_uint16_t mtu;
		a_bool_t ttl_dec_bypass;
		a_bool_t ipv4_uc_route_en;
		a_bool_t ipv6_uc_route_en;
		a_bool_t icmp_trigger_en;
		fal_fwd_cmd_t ttl_exceed_cmd;
		a_bool_t ttl_exceed_de_acce;
		a_uint8_t mac_bitmap;
		fal_mac_addr_t mac_addr;
		a_bool_t pppoe_en;
		a_uint32_t session_id;
		fal_ip_cnt_t counter;
	} fal_intf_entry_t;

	typedef struct
	{
		a_uint32_t     entry_id;
		fal_ip4_addr_t pub_addr;
	} fal_ip_pub_addr_t;

	typedef enum
	{
		FAL_NEXTHOP_L3 = 0,
		FAL_NEXTHOP_VP,
	} fal_nexthop_type_t;

	typedef struct
	{
		fal_nexthop_type_t type;
		a_uint8_t vsi;
		fal_port_t port;
		a_uint32_t if_index;
		a_bool_t ip_to_me;
		a_uint8_t pub_index;
		a_uint8_t stag_fmt;
		a_uint16_t svid;
		a_int8_t ctag_fmt;
		a_uint16_t cvid;
		fal_mac_addr_t macaddr;
		fal_ip4_addr_t dnat_ip;
	} fal_ip_nexthop_t;

	typedef struct
	{
		fal_fwd_cmd_t mru_fail;
		a_bool_t mru_de_acce;
		fal_fwd_cmd_t mtu_fail;
		a_bool_t mtu_de_acce;
		fal_fwd_cmd_t mtu_df_fail;
		a_bool_t mtu_df_de_acce;
		fal_fwd_cmd_t prefix_bc;
		a_bool_t prefix_de_acce;
		fal_fwd_cmd_t icmp_rdt;
		a_bool_t icmp_rdt_de_acce;
		a_uint8_t hash_mode_0;
		a_uint8_t hash_mode_1;
	} fal_ip_global_cfg_t;

    sw_error_t
    fal_ip_host_add(a_uint32_t dev_id, fal_host_entry_t * host_entry);

    sw_error_t
    fal_ip_host_del(a_uint32_t dev_id, a_uint32_t del_mode,
                    fal_host_entry_t * host_entry);

    sw_error_t
    fal_ip_host_get(a_uint32_t dev_id, a_uint32_t get_mode,
                    fal_host_entry_t * host_entry);

    sw_error_t
    fal_ip_host_next(a_uint32_t dev_id, a_uint32_t next_mode,
                     fal_host_entry_t * host_entry);

    sw_error_t
    fal_ip_host_counter_bind(a_uint32_t dev_id, a_uint32_t entry_id,
                             a_uint32_t cnt_id, a_bool_t enable);

    sw_error_t
    fal_ip_host_pppoe_bind(a_uint32_t dev_id, a_uint32_t entry_id,
                           a_uint32_t pppoe_id, a_bool_t enable);

    sw_error_t
    fal_ip_pt_arp_learn_set(a_uint32_t dev_id, fal_port_t port_id,
                            a_uint32_t flags);

    sw_error_t
    fal_ip_pt_arp_learn_get(a_uint32_t dev_id, fal_port_t port_id,
                            a_uint32_t * flags);

    sw_error_t
    fal_ip_arp_learn_set(a_uint32_t dev_id, fal_arp_learn_mode_t mode);

    sw_error_t
    fal_ip_arp_learn_get(a_uint32_t dev_id, fal_arp_learn_mode_t * mode);

    sw_error_t
    fal_ip_source_guard_set(a_uint32_t dev_id, fal_port_t port_id,
                            fal_source_guard_mode_t mode);

    sw_error_t
    fal_ip_source_guard_get(a_uint32_t dev_id, fal_port_t port_id,
                            fal_source_guard_mode_t * mode);

    sw_error_t
    fal_ip_arp_guard_set(a_uint32_t dev_id, fal_port_t port_id,
                         fal_source_guard_mode_t mode);

    sw_error_t
    fal_ip_arp_guard_get(a_uint32_t dev_id, fal_port_t port_id,
                         fal_source_guard_mode_t * mode);

    sw_error_t
    fal_ip_route_status_set(a_uint32_t dev_id, a_bool_t enable);

    sw_error_t
    fal_ip_route_status_get(a_uint32_t dev_id, a_bool_t * enable);

    sw_error_t
    fal_ip_intf_entry_add(a_uint32_t dev_id, fal_intf_mac_entry_t * entry);

    sw_error_t
    fal_ip_intf_entry_del(a_uint32_t dev_id, a_uint32_t del_mode,
                          fal_intf_mac_entry_t * entry);

    sw_error_t
    fal_ip_intf_entry_next(a_uint32_t dev_id, a_uint32_t next_mode,
                           fal_intf_mac_entry_t * entry);

    sw_error_t
    fal_ip_unk_source_cmd_set(a_uint32_t dev_id, fal_fwd_cmd_t cmd);

    sw_error_t
    fal_ip_unk_source_cmd_get(a_uint32_t dev_id, fal_fwd_cmd_t * cmd);

    sw_error_t
    fal_arp_unk_source_cmd_set(a_uint32_t dev_id, fal_fwd_cmd_t cmd);

    sw_error_t
    fal_arp_unk_source_cmd_get(a_uint32_t dev_id, fal_fwd_cmd_t * cmd);

    sw_error_t
    fal_ip_age_time_set(a_uint32_t dev_id, a_uint32_t * time);

    sw_error_t
    fal_ip_age_time_get(a_uint32_t dev_id, a_uint32_t * time);


    sw_error_t
    fal_ip_wcmp_hash_mode_set(a_uint32_t dev_id, a_uint32_t hash_mode);

    sw_error_t
    fal_ip_wcmp_hash_mode_get(a_uint32_t dev_id, a_uint32_t * hash_mode);

    sw_error_t
    fal_ip_vrf_base_addr_set(a_uint32_t dev_id, a_uint32_t vrf_id, fal_ip4_addr_t addr);

    sw_error_t
    fal_ip_vrf_base_addr_get(a_uint32_t dev_id, a_uint32_t vrf_id, fal_ip4_addr_t * addr);

    sw_error_t
    fal_ip_vrf_base_mask_set(a_uint32_t dev_id, a_uint32_t vrf_id, fal_ip4_addr_t addr);

    sw_error_t
    fal_ip_vrf_base_mask_get(a_uint32_t dev_id, a_uint32_t vrf_id, fal_ip4_addr_t * addr);

    sw_error_t
    fal_ip_default_route_set(a_uint32_t dev_id, a_uint32_t droute_id,
			fal_default_route_t * entry);

    sw_error_t
    fal_ip_default_route_get(a_uint32_t dev_id, a_uint32_t droute_id,
			fal_default_route_t * entry);

    sw_error_t
    fal_ip_host_route_set(a_uint32_t dev_id, a_uint32_t hroute_id,
			fal_host_route_t * entry);

    sw_error_t
    fal_ip_host_route_get(a_uint32_t dev_id, a_uint32_t hroute_id,
			fal_host_route_t * entry);

	sw_error_t
    fal_ip_wcmp_entry_set(a_uint32_t dev_id, a_uint32_t wcmp_id,
			fal_ip_wcmp_t * wcmp);

    sw_error_t
    fal_ip_wcmp_entry_get(a_uint32_t dev_id, a_uint32_t wcmp_id,
			fal_ip_wcmp_t * wcmp);

	sw_error_t
	fal_ip_rfs_ip4_rule_set(a_uint32_t dev_id, fal_ip4_rfs_t * rfs);

	sw_error_t
	fal_ip_rfs_ip6_rule_set(a_uint32_t dev_id, fal_ip6_rfs_t * rfs);

	sw_error_t
	fal_ip_rfs_ip4_rule_del(a_uint32_t dev_id, fal_ip4_rfs_t * rfs);

	sw_error_t
	fal_ip_rfs_ip6_rule_del(a_uint32_t dev_id, fal_ip6_rfs_t * rfs);

    sw_error_t
    fal_default_flow_cmd_set(a_uint32_t dev_id, a_uint32_t vrf_id,
			fal_flow_type_t type, fal_default_flow_cmd_t cmd);

    sw_error_t
    fal_default_flow_cmd_get(a_uint32_t dev_id, a_uint32_t vrf_id,
			fal_flow_type_t type, fal_default_flow_cmd_t * cmd);

    sw_error_t
    fal_default_rt_flow_cmd_set(a_uint32_t dev_id, a_uint32_t vrf_id,
			fal_flow_type_t type, fal_default_flow_cmd_t cmd);

    sw_error_t
    fal_default_rt_flow_cmd_get(a_uint32_t dev_id, a_uint32_t vrf_id,
			fal_flow_type_t type, fal_default_flow_cmd_t * cmd);

    sw_error_t
    fal_ip_vsi_intf_set(a_uint32_t dev_id, a_uint32_t vsi, fal_intf_id_t *id);

    sw_error_t
    fal_ip_vsi_intf_get(a_uint32_t dev_id, a_uint32_t vsi, fal_intf_id_t *id);

    sw_error_t
    fal_ip_vsi_mc_mode_set(a_uint32_t dev_id, a_uint32_t vsi,
    			fal_mc_mode_cfg_t *cfg);

    sw_error_t
    fal_ip_vsi_mc_mode_get(a_uint32_t dev_id, a_uint32_t vsi,
    			fal_mc_mode_cfg_t *cfg);

    sw_error_t
    fal_ip_vsi_sg_cfg_set(a_uint32_t dev_id, a_uint32_t vsi,
    			fal_sg_cfg_t *sg_cfg);

    sw_error_t
    fal_ip_vsi_sg_cfg_get(a_uint32_t dev_id, a_uint32_t vsi,
    			fal_sg_cfg_t *sg_cfg);

    sw_error_t
    fal_ip_vsi_arp_sg_cfg_set(a_uint32_t dev_id, a_uint32_t vsi,
    			fal_arp_sg_cfg_t *arp_sg_cfg);

    sw_error_t
    fal_ip_vsi_arp_sg_cfg_get(a_uint32_t dev_id, a_uint32_t vsi,
    			fal_arp_sg_cfg_t *arp_sg_cfg);

    sw_error_t
    fal_ip_port_intf_set(a_uint32_t dev_id, fal_port_t port_id, fal_intf_id_t *id);

    sw_error_t
    fal_ip_port_intf_get(a_uint32_t dev_id, fal_port_t port_id, fal_intf_id_t *id);


    sw_error_t
    fal_ip_port_macaddr_set(a_uint32_t dev_id, fal_port_t port_id,
    			fal_macaddr_entry_t *macaddr);

    sw_error_t
    fal_ip_port_macaddr_get(a_uint32_t dev_id, fal_port_t port_id,
    			fal_macaddr_entry_t *macaddr);

    sw_error_t
    fal_ip_port_sg_cfg_set(a_uint32_t dev_id, fal_port_t port_id,
    			fal_sg_cfg_t *sg_cfg);

    sw_error_t
    fal_ip_port_sg_cfg_get(a_uint32_t dev_id, fal_port_t port_id,
    			fal_sg_cfg_t *sg_cfg);

    sw_error_t
    fal_ip_port_arp_sg_cfg_set(a_uint32_t dev_id, fal_port_t port_id,
    			fal_arp_sg_cfg_t *arp_sg_cfg);

    sw_error_t
    fal_ip_port_arp_sg_cfg_get(a_uint32_t dev_id, fal_port_t port_id,
    			fal_arp_sg_cfg_t *arp_sg_cfg);

    sw_error_t
    fal_ip_network_route_set(a_uint32_t dev_id,
    			a_uint32_t index,
			fal_network_route_entry_t *entry);

    sw_error_t
    fal_ip_network_route_get(a_uint32_t dev_id,
    			a_uint32_t index, a_uint8_t type,
			fal_network_route_entry_t *entry);


    sw_error_t
    fal_ip_intf_set(
    			a_uint32_t dev_id,
    			a_uint32_t index,
    			fal_intf_entry_t *entry);

    sw_error_t
    fal_ip_intf_get(
    			a_uint32_t dev_id,
    			a_uint32_t index,
    			fal_intf_entry_t *entry);

    sw_error_t
    fal_ip_route_mismatch_set(a_uint32_t dev_id, fal_fwd_cmd_t cmd);

    sw_error_t
    fal_ip_route_mismatch_get(a_uint32_t dev_id, fal_fwd_cmd_t *cmd);

    sw_error_t
    fal_ip_pub_addr_add(a_uint32_t dev_id, fal_ip_pub_addr_t *entry);

    sw_error_t
    fal_ip_pub_addr_del(a_uint32_t dev_id, a_uint32_t entry_id);

    sw_error_t
    fal_ip_pub_addr_get(a_uint32_t dev_id, fal_ip_pub_addr_t *entry);

    sw_error_t
    fal_ip_nexthop_set(a_uint32_t dev_id, a_uint32_t index,
    			fal_ip_nexthop_t *entry);


    sw_error_t
    fal_ip_nexthop_get(a_uint32_t dev_id, a_uint32_t index,
    			fal_ip_nexthop_t *entry);

    sw_error_t
    fal_ip_global_ctrl_get(a_uint32_t dev_id, fal_ip_global_cfg_t *cfg);

    sw_error_t
    fal_ip_global_ctrl_set(a_uint32_t dev_id, fal_ip_global_cfg_t *cfg);

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* _FAL_IP_H_ */
/**
 * @}
 */
