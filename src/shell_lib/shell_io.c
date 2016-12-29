/*
 * Copyright (c) 2013, 2015, The Linux Foundation. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

//#include <stdio.h>
#include "shell_io.h"
#include "shell.h"

#define SW_RTN_ON_NULL_PARAM(rtn) \
    do { if ((rtn) == NULL) return SW_BAD_PARAM; } while(0);

#define DEFAULT_FLAG "default"
static char **full_cmdstrp;
static int talk_mode = 1;

int
get_talk_mode(void)
{
    return talk_mode ;
}

void
set_talk_mode(int mode)
{
    talk_mode = mode;
}

void
set_full_cmdstrp(char **cmdstrp)
{
    full_cmdstrp = cmdstrp;
}

static char *
get_cmd_buf(char *tag, char *defval)
{
    if(!full_cmdstrp || !(*full_cmdstrp))
    {
        dprintf("parameter (%s) or default (%s) absent\n", tag, defval);

        return NULL;
    }

    if (!strcasecmp(*(full_cmdstrp), DEFAULT_FLAG))
    {
        full_cmdstrp++;
        return defval;
    }
    else
    {
        return *(full_cmdstrp++);
    }
}

static char *
get_sub_cmd(char *tag, char *defval)
{
    return get_cmd_buf(tag, defval);
}


static inline  a_bool_t
is_hex(char c)
{
    if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f')
            || (c >= 'A' && c <= 'F'))
        return A_TRUE;

    return A_FALSE;
}

static inline a_bool_t
is_dec(char c)
{
    if ((c >= '0') && (c <= '9'))
        return A_TRUE;

    return A_FALSE;
}

static sw_data_type_t sw_data_type[] =
{
    SW_TYPE_DEF(SW_UINT8, cmd_data_check_uint8, NULL),
    SW_TYPE_DEF(SW_INT8, NULL, NULL),
    SW_TYPE_DEF(SW_UINT16, cmd_data_check_uint16, NULL),
    SW_TYPE_DEF(SW_INT16, NULL, NULL),
    SW_TYPE_DEF(SW_UINT32, cmd_data_check_uint32, NULL),
    SW_TYPE_DEF(SW_INT32, NULL, NULL),
    SW_TYPE_DEF(SW_UINT64, NULL, NULL),
    SW_TYPE_DEF(SW_INT64, NULL, NULL),
	#ifdef IN_PORTCONTROL
	SW_TYPE_DEF(SW_DUPLEX, cmd_data_check_duplex, NULL),
    SW_TYPE_DEF(SW_SPEED, cmd_data_check_speed, NULL),
    SW_TYPE_DEF(SW_CAP, cmd_data_check_capable, NULL),
	#endif
	#ifdef IN_PORTVLAN
    SW_TYPE_DEF(SW_1QMODE, cmd_data_check_1qmode, NULL),
    SW_TYPE_DEF(SW_EGMODE, cmd_data_check_egmode, NULL),
	#endif
	#ifdef IN_MIB
    SW_TYPE_DEF(SW_MIB, NULL, NULL),
    SW_TYPE_DEF(SW_XGMIB, NULL, NULL),
	#endif
	#ifdef IN_VLAN
    SW_TYPE_DEF(SW_VLAN, cmd_data_check_vlan, NULL),
	#endif
    SW_TYPE_DEF(SW_PBMP, cmd_data_check_pbmp, NULL),
    SW_TYPE_DEF(SW_ENABLE, cmd_data_check_enable, NULL),
    SW_TYPE_DEF(SW_MACADDR, cmd_data_check_macaddr, NULL),
	#ifdef IN_FDB
    SW_TYPE_DEF(SW_FDBENTRY, cmd_data_check_fdbentry, NULL),
	#endif
	#ifdef IN_QOS
	#ifndef IN_QOS_MINI
    SW_TYPE_DEF(SW_SCH, cmd_data_check_qos_sch, NULL),
    SW_TYPE_DEF(SW_QOS, cmd_data_check_qos_pt, NULL),
	#endif
    SW_TYPE_DEF(SW_PORTGROUP, cmd_data_check_port_group, NULL),
    SW_TYPE_DEF(SW_PORTPRI, cmd_data_check_port_pri, NULL),
    SW_TYPE_DEF(SW_PORTREMARK, cmd_data_check_port_remark, NULL),
    SW_TYPE_DEF(SW_COSMAP, cmd_data_check_cosmap, NULL),
    SW_TYPE_DEF(SW_SCHEDULER, cmd_data_check_queue_scheduler, NULL),
    SW_TYPE_DEF(SW_QUEUEBMP, cmd_data_check_ring_queue, NULL),
	#endif
	#ifdef IN_RATE
	SW_TYPE_DEF(SW_STORM, cmd_data_check_storm, NULL),
	#endif
	#ifdef IN_STP
    SW_TYPE_DEF(SW_STP, cmd_data_check_stp_state, NULL),
	#endif
	#ifdef IN_LEAKY
    SW_TYPE_DEF(SW_LEAKY, cmd_data_check_leaky, NULL),
	#endif
    SW_TYPE_DEF(SW_MACCMD, cmd_data_check_maccmd, NULL),
	#ifdef IN_IP
    SW_TYPE_DEF(SW_FLOWCMD, cmd_data_check_flowcmd, NULL),
    SW_TYPE_DEF(SW_FLOWTYPE, cmd_data_check_flowtype, NULL),
	#endif
    SW_TYPE_DEF(SW_UINT_A, cmd_data_check_uinta, NULL),
	#ifdef IN_ACL
    SW_TYPE_DEF(SW_ACLRULE, NULL, NULL),
	#endif
	#ifdef IN_LED
    SW_TYPE_DEF(SW_LEDPATTERN, cmd_data_check_ledpattern, NULL),
	#endif
	#ifdef IN_PORTVLAN
    SW_TYPE_DEF(SW_INVLAN, cmd_data_check_invlan_mode, NULL),
	#ifndef IN_PORTVLAN_MINI
    SW_TYPE_DEF(SW_VLANPROPAGATION, cmd_data_check_vlan_propagation, NULL),
    SW_TYPE_DEF(SW_VLANTRANSLATION, cmd_data_check_vlan_translation, NULL),
    SW_TYPE_DEF(SW_QINQMODE, cmd_data_check_qinq_mode, NULL),
    SW_TYPE_DEF(SW_QINQROLE, cmd_data_check_qinq_role, NULL),
	#endif
	#endif
    SW_TYPE_DEF(SW_CABLESTATUS, NULL, NULL),
    SW_TYPE_DEF(SW_CABLELEN, NULL, NULL),
    SW_TYPE_DEF(SW_SSDK_CFG, NULL, NULL),
    SW_TYPE_DEF(SW_MODULE, NULL, NULL),
    SW_TYPE_DEF(SW_FUNC_CTRL, NULL, NULL),
	#ifdef IN_PORTCONTROL
    SW_TYPE_DEF(SW_HDRMODE, cmd_data_check_hdrmode, NULL),
	#endif
	#ifdef IN_FDB
    SW_TYPE_DEF(SW_FDBOPRATION, cmd_data_check_fdboperation, NULL),
	#endif
	#ifdef IN_PPPOE
    SW_TYPE_DEF(SW_PPPOE, cmd_data_check_pppoe, NULL),
    SW_TYPE_DEF(SW_PPPOE_LESS, cmd_data_check_pppoe_less, NULL),
	#endif
    SW_TYPE_DEF(SW_ACL_UDF_TYPE, NULL, NULL),
	#if defined(IN_IP) || defined(IN_NAT)
    SW_TYPE_DEF(SW_IP_HOSTENTRY, cmd_data_check_host_entry, NULL),
    SW_TYPE_DEF(SW_ARP_LEARNMODE, cmd_data_check_arp_learn_mode, NULL),
    SW_TYPE_DEF(SW_IP_GUARDMODE, cmd_data_check_ip_guard_mode, NULL),
    SW_TYPE_DEF(SW_NATENTRY, cmd_data_check_nat_entry, NULL),
    SW_TYPE_DEF(SW_NAPTENTRY, cmd_data_check_napt_entry, NULL),
    SW_TYPE_DEF(SW_FLOWENTRY, cmd_data_check_flow_entry, NULL),
    SW_TYPE_DEF(SW_FLOWCOOKIE, cmd_data_check_flow_cookie, NULL),
    SW_TYPE_DEF(SW_FLOWRFS, cmd_data_check_flow_rfs, NULL),
    SW_TYPE_DEF(SW_NAPTMODE, cmd_data_check_napt_mode, NULL),
    SW_TYPE_DEF(SW_IP4ADDR, cmd_data_check_ip4addr, NULL),
    SW_TYPE_DEF(SW_IP6ADDR, cmd_data_check_ip6addr, NULL),
    SW_TYPE_DEF(SW_INTFMACENTRY, cmd_data_check_intf_mac_entry, NULL),
    SW_TYPE_DEF(SW_PUBADDRENTRY, cmd_data_check_pub_addr_entry, NULL),
	#endif
	#ifdef IN_RATE
    SW_TYPE_DEF(SW_INGPOLICER, cmd_data_check_port_policer, NULL),
    SW_TYPE_DEF(SW_EGSHAPER, cmd_data_check_egress_shaper, NULL),
    SW_TYPE_DEF(SW_ACLPOLICER, cmd_data_check_acl_policer, NULL),
	#endif
    SW_TYPE_DEF(SW_MACCONFIG, NULL, NULL),
    SW_TYPE_DEF(SW_PHYCONFIG, NULL, NULL),
	#ifdef IN_FDB
    SW_TYPE_DEF(SW_FDBSMODE, cmd_data_check_fdb_smode, NULL),
	#endif
    SW_TYPE_DEF(SW_FX100CONFIG, NULL, NULL),
	#ifdef IN_IGMP
    SW_TYPE_DEF(SW_SGENTRY, cmd_data_check_multi, NULL),
	#endif
	#ifdef IN_SEC
    SW_TYPE_DEF(SW_SEC_MAC, cmd_data_check_sec_mac, NULL),
    SW_TYPE_DEF(SW_SEC_IP, cmd_data_check_sec_ip, NULL),
    SW_TYPE_DEF(SW_SEC_IP4, cmd_data_check_sec_ip4, NULL),
    SW_TYPE_DEF(SW_SEC_IP6, cmd_data_check_sec_ip6, NULL),
    SW_TYPE_DEF(SW_SEC_TCP, cmd_data_check_sec_tcp, NULL),
    SW_TYPE_DEF(SW_SEC_UDP, cmd_data_check_sec_udp, NULL),
    SW_TYPE_DEF(SW_SEC_ICMP4, cmd_data_check_sec_icmp4, NULL),
    SW_TYPE_DEF(SW_SEC_ICMP6, cmd_data_check_sec_icmp6, NULL),
    SW_TYPE_DEF(SW_L3_PARSER, cmd_data_check_l3_parser, NULL),
    SW_TYPE_DEF(SW_L4_PARSER, cmd_data_check_l4_parser, NULL),
    SW_TYPE_DEF(SW_EXP_CTRL, cmd_data_check_exp_ctrl, NULL),
	#endif
	#ifdef IN_COSMAP
    SW_TYPE_DEF(SW_REMARKENTRY, cmd_data_check_remark_entry, NULL),
	#endif
	#ifdef IN_IP
    SW_TYPE_DEF(SW_DEFAULT_ROUTE_ENTRY, cmd_data_check_default_route_entry, NULL),
    SW_TYPE_DEF(SW_HOST_ROUTE_ENTRY, cmd_data_check_host_route_entry, NULL),
    SW_TYPE_DEF(SW_IP_RFS_IP4, cmd_data_check_ip4_rfs_entry, NULL),
	SW_TYPE_DEF(SW_IP_RFS_IP6, cmd_data_check_ip6_rfs_entry, NULL),
	SW_TYPE_DEF(SW_ARP_SG_CFG, cmd_data_check_arp_sg, NULL),
	SW_TYPE_DEF(SW_IP_NETWORK_ROUTE, cmd_data_check_network_route, NULL),
	SW_TYPE_DEF(SW_IP_INTF, cmd_data_check_intf, NULL),
	SW_TYPE_DEF(SW_IP_VSI_INTF, cmd_data_check_vsi_intf, NULL),
	SW_TYPE_DEF(SW_IP_NEXTHOP, cmd_data_check_nexthop, NULL),
	SW_TYPE_DEF(SW_IP_SG, cmd_data_check_ip_sg, NULL),
	SW_TYPE_DEF(SW_IP_PUB, cmd_data_check_ip_pub, NULL),
	SW_TYPE_DEF(SW_IP_PORTMAC, cmd_data_check_ip_portmac, NULL),
	SW_TYPE_DEF(SW_IP_MCMODE, cmd_data_check_ip_mcmode, NULL),
	SW_TYPE_DEF(SW_IP_GLOBAL, cmd_data_check_ip_global, NULL),
	#endif
	#ifdef IN_PORTCONTROL
	#ifndef IN_PORTCONTROL_MINI
    SW_TYPE_DEF(SW_CROSSOVER_MODE, cmd_data_check_crossover_mode, NULL),
    SW_TYPE_DEF(SW_CROSSOVER_STATUS, cmd_data_check_crossover_status, NULL),
    SW_TYPE_DEF(SW_PREFER_MEDIUM, cmd_data_check_prefer_medium, NULL),
    SW_TYPE_DEF(SW_FIBER_MODE, cmd_data_check_fiber_mode, NULL),
	#endif
	#endif
	#ifdef IN_INTERFACECONTROL
    SW_TYPE_DEF(SW_INTERFACE_MODE, cmd_data_check_interface_mode, NULL),
	#endif
    SW_TYPE_DEF(SW_COUNTER_INFO, NULL, NULL),
    #ifdef IN_VSI
    SW_TYPE_DEF(SW_VSI_NEWADDR_LRN, cmd_data_check_newadr_lrn, NULL),
    SW_TYPE_DEF(SW_VSI_STAMOVE, cmd_data_check_stamove, NULL),
    SW_TYPE_DEF(SW_VSI_MEMBER, cmd_data_check_vsi_member, NULL),
    SW_TYPE_DEF(SW_VSI_COUNTER, NULL, NULL),
    #endif
    #ifdef IN_QM
    SW_TYPE_DEF(SW_STATIC_THRESH, cmd_data_check_ac_static_thresh, NULL),
    SW_TYPE_DEF(SW_DYNAMIC_THRESH, cmd_data_check_ac_dynamic_thresh, NULL),
    SW_TYPE_DEF(SW_GROUP_BUFFER, cmd_data_check_ac_group_buff, NULL),
    SW_TYPE_DEF(SW_AC_CTRL, cmd_data_check_ac_ctrl, NULL),
    SW_TYPE_DEF(SW_AC_OBJ, cmd_data_check_ac_obj, NULL),
    SW_TYPE_DEF(SW_UCAST_QUEUE_MAP, cmd_data_check_u_qmap, NULL),
    #endif
    #ifdef IN_BM
    SW_TYPE_DEF(SW_BMSTHRESH, cmd_data_check_bm_static_thresh, NULL),
    SW_TYPE_DEF(SW_BMDTHRESH, cmd_data_check_bm_dynamic_thresh, NULL),
    #endif
    #ifdef IN_FLOW
    SW_TYPE_DEF(SW_FLOW_AGE, cmd_data_check_flow_age, NULL),
    SW_TYPE_DEF(SW_FLOW_CTRL, cmd_data_check_flow_ctrl, NULL),
    SW_TYPE_DEF(SW_FLOW_ENTRY, cmd_data_check_flow, NULL),
    SW_TYPE_DEF(SW_FLOW_GLOBAL, cmd_data_check_flow_global, NULL),
    #endif
    SW_TYPE_DEF(SW_MTU_INFO, NULL, NULL),
    SW_TYPE_DEF(SW_MRU_INFO, NULL, NULL),
    SW_TYPE_DEF(SW_MTU_ENTRY, cmd_data_check_mtu_entry, NULL),
    SW_TYPE_DEF(SW_MRU_ENTRY, cmd_data_check_mru_entry, NULL),
    SW_TYPE_DEF(SW_ACL_UDF_PKT_TYPE, NULL, NULL),
    #ifdef IN_SHAPER
    SW_TYPE_DEF(SW_PORT_SHAPER_TOKEN_CONFIG, cmd_data_check_port_shaper_token_config, NULL),
    SW_TYPE_DEF(SW_SHAPER_TOKEN_CONFIG, cmd_data_check_shaper_token_config, NULL),
    SW_TYPE_DEF(SW_PORT_SHAPER_CONFIG, cmd_data_check_port_shaper_config, NULL),
    SW_TYPE_DEF(SW_SHAPER_CONFIG, cmd_data_check_shaper_config, NULL),
  #endif

  #ifdef IN_POLICER
    SW_TYPE_DEF(SW_POLICER_ACL_CONFIG, cmd_data_check_acl_policer_config, NULL),
    SW_TYPE_DEF(SW_POLICER_PORT_CONFIG, cmd_data_check_port_policer_config, NULL),
    SW_TYPE_DEF(SW_POLICER_CMD_CONFIG, cmd_data_check_policer_cmd_config, NULL),
  #endif
};

sw_data_type_t *
cmd_data_type_find(sw_data_type_e type)
{
    a_uint16_t i = 0;

    do
    {
        if (type == sw_data_type[i].data_type)
            return &sw_data_type[i];
    }
    while ( ++i < sizeof(sw_data_type)/sizeof(sw_data_type[0]));

    return NULL;
}

sw_error_t __cmd_data_check_quit_help(char *cmd, char *usage)
{
    sw_error_t ret = SW_OK;

    if (!strncasecmp(cmd, "quit", 4)) {
        return SW_ABORTED;
    } else if (!strncasecmp(cmd, "help", 4)) {
        dprintf("%s", usage);
        ret = SW_BAD_VALUE;
    }

    return ret;
}

sw_error_t __cmd_data_check_complex(char *info, char *defval, char *usage,
				sw_error_t(*chk_func)(), void *arg_val,
				a_uint32_t size)
{
    sw_error_t ret;
    char *cmd;

    do {
        cmd = get_sub_cmd(info, defval);
        SW_RTN_ON_NULL_PARAM(cmd);

        ret = __cmd_data_check_quit_help(cmd, usage);
        if (ret == SW_ABORTED)
            return ret;
        else if (ret == SW_OK) {
            ret = chk_func(cmd, arg_val, size);
            if (ret)
                dprintf("%s", usage);
        }
    } while (talk_mode && (SW_OK != ret));

    return SW_OK;
}

sw_error_t __cmd_data_check_range(char *info, char *defval, char *usage,
				sw_error_t(*chk_func)(), void *arg_val,
				a_uint32_t max_val, a_uint32_t min_val)
{
    sw_error_t ret;
    char *cmd;

    do {
        cmd = get_sub_cmd(info, defval);
        SW_RTN_ON_NULL_PARAM(cmd);

        ret = __cmd_data_check_quit_help(cmd, usage);
        if (ret == SW_ABORTED)
            return ret;
        else if (ret == SW_OK) {
            ret = chk_func(cmd, arg_val, max_val, min_val);
            if (ret)
                dprintf("%s", usage);
        }
    } while (talk_mode && (SW_OK != ret));

    return SW_OK;
}

sw_error_t __cmd_data_check_boolean(char *info, char *defval, char *usage,
				sw_error_t(*chk_func)(), a_bool_t def, a_bool_t *val,
				a_uint32_t size)
{
    sw_error_t ret;
    char *cmd;

    do {
        cmd = get_sub_cmd(info, defval);
        SW_RTN_ON_NULL_PARAM(cmd);

        ret = __cmd_data_check_quit_help(cmd, usage);
        if (ret == SW_ABORTED)
            return ret;
        else if (ret == SW_OK) {
            ret = chk_func(cmd, def, val, size);
            if (ret)
                dprintf("%s", usage);
        }
    } while (talk_mode && (SW_OK != ret));

    return SW_OK;
}

sw_error_t
cmd_data_check_uint8(char *cmd_str, a_uint32_t *arg_val, a_uint32_t size)
{
    if (cmd_str == NULL)
        return SW_BAD_PARAM;

    if (0 == cmd_str[0])
    {
        return SW_BAD_VALUE;
    }

    if (cmd_str[0] == '0' && (cmd_str[1] == 'x' || cmd_str[1] == 'X'))
        sscanf(cmd_str, "%x", arg_val);
    else
        sscanf(cmd_str, "%d", arg_val);

    if (255 < *arg_val)
    {
        return SW_BAD_PARAM;
    }

    return SW_OK;
}

sw_error_t
cmd_data_check_uint32(char *cmd_str, a_uint32_t * arg_val, a_uint32_t size)
{
    if (cmd_str == NULL)
        return SW_BAD_PARAM;

    if (0 == cmd_str[0])
    {
        return SW_BAD_VALUE;
    }

    if (strspn(cmd_str, "1234567890abcdefABCDEFXx") != strlen(cmd_str)){
        return SW_BAD_VALUE;
    }

    if (cmd_str[0] == '0' && (cmd_str[1] == 'x' || cmd_str[1] == 'X'))
        sscanf(cmd_str, "%x", arg_val);
    else
        sscanf(cmd_str, "%d", arg_val);

    return SW_OK;
}

sw_error_t
cmd_data_check_uint16(char *cmd_str, a_uint32_t *arg_val, a_uint32_t size)
{
    if (cmd_str == NULL)
        return SW_BAD_PARAM;

    if (0 == cmd_str[0])
    {
        return SW_BAD_VALUE;
    }

    if (cmd_str[0] == '0' && (cmd_str[1] == 'x' || cmd_str[1] == 'X'))
        sscanf(cmd_str, "%x", arg_val);
    else
        sscanf(cmd_str, "%d", arg_val);

    if (65535 < *arg_val)
    {
        return SW_BAD_PARAM;
    }

    return SW_OK;
}

sw_error_t
cmd_data_check_pbmp(char *cmd_str, a_uint32_t * arg_val, a_uint32_t size)
{
    if (cmd_str == NULL)
        return SW_BAD_PARAM;

    if (cmd_str[0] == '0' && (cmd_str[1] == 'x' || cmd_str[1] == 'X'))
        sscanf(cmd_str, "%x", arg_val);
    else
        sscanf(cmd_str, "%d", arg_val);

    return SW_OK;

}

sw_error_t
cmd_data_check_enable(char *cmd_str, a_uint32_t * arg_val, a_uint32_t size)
{
    if (cmd_str == NULL)
        return SW_BAD_PARAM;

    if (!strcasecmp(cmd_str, "disable"))
        *arg_val = FAL_DISABLE;
    else if (!strcasecmp(cmd_str, "enable"))
        *arg_val = FAL_ENABLE;
    else
    {
        //dprintf("input error");
        return SW_BAD_VALUE;
    }

    return SW_OK;
}
#ifdef IN_PORTCONTROL
/*port ctrl*/
sw_error_t
cmd_data_check_duplex(char *cmd_str, a_uint32_t * arg_val, a_uint32_t size)
{
    if (cmd_str == NULL)
        return SW_BAD_PARAM;

    if (!strcasecmp(cmd_str, "half"))
        *arg_val = FAL_HALF_DUPLEX;
    else if (!strcasecmp(cmd_str, "full"))
        *arg_val = FAL_FULL_DUPLEX;
    else
    {
        //dprintf("input error \n");
        return SW_BAD_VALUE;
    }

    return SW_OK;
}

sw_error_t
cmd_data_check_speed(char *cmd_str, a_uint32_t * arg_val, a_uint32_t size)
{
    if (cmd_str == NULL)
        return SW_BAD_PARAM;

    if (!strncasecmp(cmd_str, "10", 3))
        *arg_val = FAL_SPEED_10;
    else if (!strncasecmp(cmd_str, "100", 4))
        *arg_val = FAL_SPEED_100;
    else if (!strncasecmp(cmd_str, "1000", 5))
        *arg_val = FAL_SPEED_1000;
    else
    {
        //dprintf("input error \n");
        return SW_BAD_VALUE;
    }

    return SW_OK;
}

sw_error_t
cmd_data_check_capable(char *cmd_str, a_uint32_t * arg_val, a_uint32_t size)
{
    if (cmd_str == NULL)
        return SW_BAD_PARAM;

    cmd_strtol(cmd_str, arg_val);
    if (*arg_val & (~FAL_PHY_COMBO_ADV_ALL))
    {
        //dprintf("input error should be within 0x3f\n");
        return SW_BAD_VALUE;
    }

    return SW_OK;
}

#ifndef IN_PORTCONTROL_MINI

sw_error_t
cmd_data_check_crossover_mode(char *cmd_str, a_uint32_t * arg_val, a_uint32_t size)
{
    if (cmd_str == NULL)
        return SW_BAD_PARAM;

    if (!strncasecmp(cmd_str, "auto", 5))
        *arg_val = PHY_MDIX_AUTO;
    else if (!strncasecmp(cmd_str, "mdi", 4))
        *arg_val = PHY_MDIX_MDI;
    else if (!strncasecmp(cmd_str, "mdix", 5))
        *arg_val = PHY_MDIX_MDIX;
    else
    {
        //dprintf("input error \n");
        return SW_BAD_VALUE;
    }

    return SW_OK;
}

sw_error_t
cmd_data_check_crossover_status(char *cmd_str, a_uint32_t * arg_val, a_uint32_t size)
{
    if (cmd_str == NULL)
        return SW_BAD_PARAM;
    if (!strncasecmp(cmd_str, "mdi", 4))
        *arg_val = PHY_MDIX_STATUS_MDI;
    else if (!strncasecmp(cmd_str, "mdix", 5))
        *arg_val = PHY_MDIX_STATUS_MDIX;
    else
    {
        //dprintf("input error \n");
        return SW_BAD_VALUE;
    }

    return SW_OK;
}

sw_error_t
cmd_data_check_prefer_medium(char *cmd_str, a_uint32_t * arg_val, a_uint32_t size)
{
    if (cmd_str == NULL)
        return SW_BAD_PARAM;
    if (!strncasecmp(cmd_str, "copper", 7))
        *arg_val = PHY_MEDIUM_COPPER;
    else if (!strncasecmp(cmd_str, "fiber", 6))
        *arg_val = PHY_MEDIUM_FIBER;
    else
    {
        //dprintf("input error \n");
        return SW_BAD_VALUE;
    }

    return SW_OK;
}

sw_error_t
cmd_data_check_fiber_mode(char *cmd_str, a_uint32_t * arg_val, a_uint32_t size)
{
    if (cmd_str == NULL)
        return SW_BAD_PARAM;
    if (!strncasecmp(cmd_str, "100fx", 6))
        *arg_val = PHY_FIBER_100FX;
    else if (!strncasecmp(cmd_str, "1000bx", 7))
        *arg_val = PHY_FIBER_1000BX;
    else
    {
        //dprintf("input error \n");
        return SW_BAD_VALUE;
    }

    return SW_OK;
}

sw_error_t
cmd_data_check_mtu_entry(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_mtu_ctrl_t entry;

    aos_mem_zero(&entry, sizeof (fal_mtu_ctrl_t));

    do
    {
        cmd = get_sub_cmd("mtu_size", "1514");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: 1514 - 32767 \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.mtu_size), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: usage: 1514 - 32767 \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("mtu_action", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: usage: 0:forward 1:drop 2:cpycpu 3:rdtcpu\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, (a_uint32_t *)&(entry.action), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: usage: 0:forward 1:drop 2:cpycpu 3:rdtcpu\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    *(fal_mtu_ctrl_t *)val = entry;
    return SW_OK;
}

sw_error_t
cmd_data_check_mru_entry(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_mru_ctrl_t entry;

    aos_mem_zero(&entry, sizeof (fal_mru_ctrl_t));

    do
    {
        cmd = get_sub_cmd("mru_size", "1514");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: 1514 - 32767 \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.mru_size), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: usage: 1514 - 32767 \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("mru_action", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: usage: 0:forward 1:drop 2:cpycpu 3:rdtcpu\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, (a_uint32_t *)&(entry.action), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: usage: 0:forward 1:drop 2:cpycpu 3:rdtcpu\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    *(fal_mru_ctrl_t *)val = entry;
    return SW_OK;
}

#endif
#endif
#ifdef IN_INTERFACECONTROL
sw_error_t
cmd_data_check_interface_mode(char *cmd_str, a_uint32_t * arg_val, a_uint32_t size)
{
    if (cmd_str == NULL)
        return SW_BAD_PARAM;

    if (!strncasecmp(cmd_str, "psgmii_baset", 13))
        *arg_val = PHY_PSGMII_BASET;
    else if (!strncasecmp(cmd_str, "psgmii_bx1000", 14))
        *arg_val = PHY_PSGMII_BX1000;
    else if (!strncasecmp(cmd_str, "psgmii_fx100", 13))
        *arg_val = PHY_PSGMII_FX100;
    else if (!strncasecmp(cmd_str, "psgmii_amdet", 13))
        *arg_val = PHY_PSGMII_AMDET;
    else if (!strncasecmp(cmd_str, "sgmii_baset", 13))
        *arg_val = PHY_SGMII_BASET;
    else
    {
        //dprintf("input error \n");
        return SW_BAD_VALUE;
    }

    return SW_OK;
}
#endif
/*portvlan*/
#ifdef IN_PORTVLAN
sw_error_t
cmd_data_check_1qmode(char *cmd_str, a_uint32_t * arg_val, a_uint32_t size)
{
    if (cmd_str == NULL)
        return SW_BAD_PARAM;

    if (!strcasecmp(cmd_str, "disable"))
    {
        *arg_val = FAL_1Q_DISABLE;
    }
    else if (!strcasecmp(cmd_str, "secure"))
    {
        *arg_val = FAL_1Q_SECURE;
    }
    else if (!strcasecmp(cmd_str, "check"))
    {
        *arg_val = FAL_1Q_CHECK;
    }
    else if (!strcasecmp(cmd_str, "fallback"))
    {
        *arg_val = FAL_1Q_FALLBACK;
    }
    else
    {
        //dprintf("input error \n");
        return SW_BAD_VALUE;
    }

    return SW_OK;
}



sw_error_t
cmd_data_check_egmode(char *cmd_str, a_uint32_t * arg_val, a_uint32_t size)
{
    if (cmd_str == NULL)
        return SW_BAD_PARAM;

    if (!strcasecmp(cmd_str, "unmodified"))
    {
        *arg_val = FAL_EG_UNMODIFIED;
    }
    else if (!strcasecmp(cmd_str, "untagged"))
    {
        *arg_val = FAL_EG_UNTAGGED;
    }
    else if (!strcasecmp(cmd_str, "tagged"))
    {
        *arg_val = FAL_EG_TAGGED;
    }
    else if (!strcasecmp(cmd_str, "hybrid"))
    {
        *arg_val = FAL_EG_HYBRID;
    }
    else if (!strcasecmp(cmd_str, "untouched"))
    {
        *arg_val = FAL_EG_UNTOUCHED;
    }
    else
    {
        //dprintf("input error \n");
        return SW_BAD_VALUE;
    }

    return SW_OK;
}
#endif
/*vlan*/
#ifdef IN_VLAN
sw_error_t
cmd_data_check_vlan(char *cmdstr, fal_vlan_t * val, a_uint32_t size)
{
    sw_error_t rv;
    fal_vlan_t entry;
    a_uint32_t tmp;

    memset(&entry, 0, sizeof (fal_vlan_t));

    rv = __cmd_data_check_complex("vlanid", NULL,
                        "usage: the range is 0 -- 4095\n",
                        cmd_data_check_uint16, &tmp, sizeof (a_uint32_t));
    if (rv)
        return rv;
    entry.vid = tmp & 0xffff;

    rv = __cmd_data_check_complex("fid", NULL,
                        "usage: the range is 0 -- 4095 or 65535\n",
                        cmd_data_check_uint16, &tmp, sizeof (a_uint32_t));
    if (rv)
        return rv;
    entry.fid = tmp & 0xffff;

    rv = __cmd_data_check_complex("port member", "null",
                        "usage: input port number such as 1,3\n",
                        cmd_data_check_portmap, &entry.mem_ports,
                        sizeof (fal_pbmp_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("tagged member", "null",
                        "usage: input port number such as 1,3\n",
                        cmd_data_check_portmap, &entry.tagged_ports,
                        sizeof (fal_pbmp_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("untagged member", "null",
                        "usage: input port number such as 1,3\n",
                        cmd_data_check_portmap, &entry.untagged_ports,
                        sizeof (fal_pbmp_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("unmodify member", "null",
                        "usage: input port number such as 1,3\n",
                        cmd_data_check_portmap, &entry.unmodify_ports,
                        sizeof (fal_pbmp_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("unmodify member", "null",
                        "usage: input port number such as 1,3\n",
                        cmd_data_check_portmap, &entry.unmodify_ports,
                        sizeof (fal_pbmp_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("learn disable", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &entry.learn_dis,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("queue override", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &entry.vid_pri_en,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    if (A_TRUE == entry.vid_pri_en)
    {
        rv = __cmd_data_check_complex("queue", NULL,
                        "usage: input number such as <0/1/2/3>\n",
                        cmd_data_check_uint32, &tmp, sizeof (a_uint32_t));
        if (rv)
            return rv;

        entry.vid_pri = tmp;
    }

    *val = entry;
    return SW_OK;
}
#endif
/*qos*/
#ifdef IN_QOS
sw_error_t
cmd_data_check_port_group(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_qos_group_t entry;

    aos_mem_zero(&entry, sizeof (fal_qos_group_t));

    do
    {
        cmd = get_sub_cmd("pcp group", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: group\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.pcp_group),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: group\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("dscp group", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: group\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.dscp_group),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: group\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("flow group", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: group\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.flow_group),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: group\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    *(fal_qos_group_t *)val = entry;
    return SW_OK;
}

sw_error_t
cmd_data_check_port_pri(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_qos_pri_precedence_t entry;

    aos_mem_zero(&entry, sizeof (fal_qos_pri_precedence_t));

    do
    {
        cmd = get_sub_cmd("pcp pri", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: priority\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.pcp_pri),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: priority\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("dscp pri", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: priority\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.dscp_pri),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: priority\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("preheader pri", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: priority\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.preheader_pri),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: priority\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("flow pri", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: priority\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.flow_pri),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: priority\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("acl pri", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: priority\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.acl_pri),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: priority\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    *(fal_qos_pri_precedence_t *)val = entry;
    return SW_OK;
}

sw_error_t
cmd_data_check_port_remark(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_qos_remark_enable_t entry;

    aos_mem_zero(&entry, sizeof (fal_qos_remark_enable_t));

    do
    {
        cmd = get_sub_cmd("pcp change en", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.pcp_change_en),
                                       sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("dei change en", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.dei_chage_en),
                                       sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("dscp change en", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.dscp_change_en),
                                       sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    *(fal_qos_remark_enable_t *)val = entry;
    return SW_OK;
}

sw_error_t
cmd_data_check_cosmap(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_qos_cosmap_t entry;

    aos_mem_zero(&entry, sizeof (fal_qos_cosmap_t));

    do
    {
        cmd = get_sub_cmd("internal pcp", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: internal pcp\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.internal_pcp),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: internal pcp\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("internal dei", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: internal dei\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.internal_dei),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: internal dei\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("internal pri", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: internal pri\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.internal_pri),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: internal pri\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("internal dscp", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: internal dscp\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.internal_dscp),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: internal dscp\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("internal dp", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: internal dp\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.internal_dp),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: internal dp\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    *(fal_qos_cosmap_t *)val = entry;
    return SW_OK;
}

sw_error_t
cmd_data_check_queue_scheduler(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_qos_scheduler_cfg_t entry;

    aos_mem_zero(&entry, sizeof (fal_qos_scheduler_cfg_t));

    do
    {
        cmd = get_sub_cmd("sp id", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: sp id\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.sp_id),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: spi id\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("e pri", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: e pri\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.e_pri),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: e pri\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("c pri", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: c pri\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.c_pri),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: c pri\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("e drr id", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: e drr id\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.e_drr_id),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: e drr id\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("c drr id", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: c drr id\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.c_drr_id),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: c drr id\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("e drr wt", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: e drr wt\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.e_drr_wt),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: e drr wt\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("c drr wt", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: c drr wt\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.c_drr_wt),
                                       sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: c drr wt\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("c drr ut", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: c drr unit\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.c_drr_unit),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: c drr unit\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("e drr ut", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: e drr unit\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.e_drr_unit),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: e drr unit\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("drr frame mode", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: drr frame mode\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.drr_frame_mode),
                                       sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: drr frame mode\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    *(fal_qos_scheduler_cfg_t *)val = entry;
    return SW_OK;
}

sw_error_t
cmd_data_check_ring_queue(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp, i = 0;
    sw_error_t rv;
    fal_queue_bmp_t entry;

    aos_mem_zero(&entry, sizeof (fal_queue_bmp_t));

    do
    {
        cmd = get_sub_cmd("bmp", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: bmp\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.bmp[i]),
                                       sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: bmp\n");
        }

    }
    while (talk_mode && (SW_OK != rv) || i++ < 10);

    *(fal_queue_bmp_t *)val = entry;
    return SW_OK;
}


#ifndef IN_QOS_MINI
sw_error_t
cmd_data_check_qos_sch(char *cmdstr, fal_sch_mode_t * val, a_uint32_t size)
{
    if (cmdstr == NULL)
        return SW_BAD_PARAM;

    if (!strcasecmp(cmdstr, "sp"))
    {
        *val = FAL_SCH_SP_MODE;
    }
    else if (!strcasecmp(cmdstr, "wrr"))
    {
        *val = FAL_SCH_WRR_MODE;
    }
    else if (!strcasecmp(cmdstr, "mixplus"))
    {
        *val = FAL_SCH_MIX_PLUS_MODE;
    }
    else if (!strcasecmp(cmdstr, "mix"))
    {
        *val = FAL_SCH_MIX_MODE;
    }
    else
    {
        return SW_BAD_VALUE;
    }

    return SW_OK;
}


sw_error_t
cmd_data_check_qos_pt(char *cmdstr, fal_qos_mode_t * val, a_uint32_t size)
{
    if (cmdstr == NULL)
        return SW_BAD_PARAM;

    if (!strcasecmp(cmdstr, "da"))
    {
        *val = FAL_QOS_DA_MODE;
    }
    else if (!strcasecmp(cmdstr, "up"))
    {
        *val = FAL_QOS_UP_MODE;
    }
    else if (!strcasecmp(cmdstr, "dscp"))
    {
        *val = FAL_QOS_DSCP_MODE;
    }
    else if (!strcasecmp(cmdstr, "port"))
    {
        *val = FAL_QOS_PORT_MODE;
    }
    else if (!strcasecmp(cmdstr, "flow"))
    {
        *val = FAL_QOS_FLOW_MODE;
    }
    else
    {
        return SW_BAD_VALUE;
    }

    return SW_OK;
}
#endif
#endif

/*rate*/
#ifdef IN_RATE
sw_error_t
cmd_data_check_storm(char *cmdstr, fal_storm_type_t * val, a_uint32_t size)
{
    if (cmdstr == NULL)
        return SW_BAD_PARAM;

    if (!strcasecmp(cmdstr, "unicast"))
    {
        *val = FAL_UNICAST_STORM;
    }
    else if (!strcasecmp(cmdstr, "multicast"))
    {
        *val = FAL_MULTICAST_STORM;
    }
    else if (!strcasecmp(cmdstr, "broadcast"))
    {
        *val = FAL_BROADCAST_STORM;
    }
    else
    {
        return SW_BAD_VALUE;
    }

    return SW_OK;
}
#endif

/*stp*/
#ifdef IN_STP
sw_error_t
cmd_data_check_stp_state(char *cmdstr, fal_stp_state_t * val, a_uint32_t size)
{
    if (cmdstr == NULL)
        return SW_BAD_PARAM;

    if (!strcasecmp(cmdstr, "disable"))
    {
        *val = FAL_STP_DISABLED;
    }
    else if (!strcasecmp(cmdstr, "block"))
    {
        *val = FAL_STP_BLOKING;
    }
    else if (!strcasecmp(cmdstr, "listen"))
    {
        *val = FAL_STP_LISTENING;
    }
    else if (!strcasecmp(cmdstr, "learn"))
    {
        *val = FAL_STP_LEARNING;
    }
    else if (!strcasecmp(cmdstr, "forward"))
    {
        *val = FAL_STP_FARWARDING;
    }
    else
    {
        return SW_BAD_VALUE;
    }

    return SW_OK;
}
#endif

#ifdef IN_LEAKY
/*general*/
sw_error_t
cmd_data_check_leaky(char *cmdstr, fal_leaky_ctrl_mode_t * val, a_uint32_t size)
{
    if (cmdstr == NULL)
        return SW_BAD_VALUE;

    if (!strcasecmp(cmdstr, "port"))
    {
        *val = FAL_LEAKY_PORT_CTRL;
    }
    else if (!strcasecmp(cmdstr, "fdb"))
    {
        *val = FAL_LEAKY_FDB_CTRL;
    }
    else
    {
        return SW_BAD_VALUE;
    }

    return SW_OK;
}
#endif

sw_error_t
cmd_data_check_uinta(char *cmdstr, a_uint32_t * val, a_uint32_t size)
{
    char *tmp_str = NULL;
    a_uint32_t *tmp_ptr = val;
    a_uint32_t i = 0;

    tmp_str = (void *) strsep(&cmdstr, ",");

    while (tmp_str)
    {
        if (i >= (size / 4))
        {
            return SW_BAD_VALUE;
        }

        sscanf(tmp_str, "%d", tmp_ptr);
        tmp_ptr++;

        i++;
        tmp_str = (void *) strsep(&cmdstr, ",");
    }

    if (i != (size / 4))
    {
        return SW_BAD_VALUE;
    }

    return SW_OK;
}


/*fdb*/
sw_error_t
cmd_data_check_maccmd(char *cmdstr, fal_fwd_cmd_t * val, a_uint32_t size)
{
    if (NULL == cmdstr)
    {
        return SW_BAD_VALUE;
    }

    if (0 == cmdstr[0])
    {
        *val = FAL_MAC_FRWRD;   //defualt
    }
    else if (!strcasecmp(cmdstr, "forward"))
    {
        *val = FAL_MAC_FRWRD;
    }
    else if (!strcasecmp(cmdstr, "drop"))
    {
        *val = FAL_MAC_DROP;
    }
    else if (!strcasecmp(cmdstr, "cpycpu"))
    {
        *val = FAL_MAC_CPY_TO_CPU;
    }
    else if (!strcasecmp(cmdstr, "rdtcpu"))
    {
        *val = FAL_MAC_RDT_TO_CPU;
    }
    else
    {
        return SW_BAD_VALUE;
    }

    return SW_OK;
}

/*flow*/
#ifdef IN_IP
sw_error_t
cmd_data_check_flowcmd(char *cmdstr, fal_default_flow_cmd_t * val, a_uint32_t size)
{
    if (NULL == cmdstr)
    {
        return SW_BAD_VALUE;
    }

    if (0 == cmdstr[0])
    {
        *val = FAL_DEFAULT_FLOW_FORWARD;   //default
    }
    else if (!strcasecmp(cmdstr, "forward"))
    {
        *val = FAL_DEFAULT_FLOW_FORWARD;
    }
    else if (!strcasecmp(cmdstr, "drop"))
    {
        *val = FAL_DEFAULT_FLOW_DROP;
    }
    else if (!strcasecmp(cmdstr, "rdtcpu"))
    {
        *val = FAL_DEFAULT_FLOW_RDT_TO_CPU;
    }
    else if (!strcasecmp(cmdstr, "admit_all"))
    {
        *val = FAL_DEFAULT_FLOW_ADMIT_ALL;
    }
    else
    {
        return SW_BAD_VALUE;
    }

    return SW_OK;
}

sw_error_t
cmd_data_check_flowtype(char *cmd_str, fal_flow_type_t * arg_val,
                        a_uint32_t size)
{
    if (NULL == cmd_str)
    {
        return SW_BAD_VALUE;
    }

    if (!strcasecmp(cmd_str, "lan2lan"))
    {
        *arg_val = FAL_FLOW_LAN_TO_LAN;
    }
    else if (!strcasecmp(cmd_str, "wan2lan"))
    {
        *arg_val = FAL_FLOW_WAN_TO_LAN;
    }
    else if (!strcasecmp(cmd_str, "lan2wan"))
    {
        *arg_val = FAL_FLOW_LAN_TO_WAN;
    }
    else if (!strcasecmp(cmd_str, "wan2wan"))
    {
        *arg_val = FAL_FLOW_WAN_TO_WAN;
    }
    else
    {
        return SW_BAD_VALUE;
    }

    return SW_OK;
}
#endif
sw_error_t
cmd_data_check_confirm(char *cmdstr, a_bool_t def, a_bool_t * val,
                       a_uint32_t size)
{
    if (0 == cmdstr[0])
    {
        *val = def;
    }
    else if ((!strcasecmp(cmdstr, "yes")) || (!strcasecmp(cmdstr, "y")))
    {
        *val = A_TRUE;
    }
    else if ((!strcasecmp(cmdstr, "no")) || (!strcasecmp(cmdstr, "n")))
    {
        *val = A_FALSE;
    }
    else
    {
        return SW_BAD_VALUE;
    }

    return SW_OK;
}

sw_error_t
cmd_data_check_portmap(char *cmdstr, fal_pbmp_t * val, a_uint32_t size)
{
    char *tmp = NULL;
    a_uint32_t i = 0;
    a_uint32_t port;

    *val = 0;
    //default input null
    if(!strcasecmp(cmdstr, "null"))
    {
        return SW_OK;
    }

    tmp = (void *) strsep(&cmdstr, ",");
    while (tmp)
    {
        if (SW_MAX_NR_PORT <= i)
        {
            return SW_BAD_VALUE;
        }

        sscanf(tmp, "%d", &port);
        if (SW_MAX_NR_PORT <= port)
        {
            return SW_BAD_VALUE;
        }

        *val |= (0x1 << port);
        tmp = (void *) strsep(&cmdstr, ",");
    }

    return SW_OK;
}

sw_error_t
cmd_data_check_macaddr(char *cmdstr, void *val, a_uint32_t size)
{
    char *tmp = NULL;
    a_uint32_t i = 0, j;
    a_uint32_t addr;
    fal_mac_addr_t mac;

    memset(&mac, 0, sizeof (fal_mac_addr_t));
    if (NULL == cmdstr)
    {
        *(fal_mac_addr_t *) val = mac;
        return SW_BAD_VALUE; /*was: SW_OK;*/
    }

    if (0 == cmdstr[0])
    {
        *(fal_mac_addr_t *) val = mac;
        return SW_OK;
    }

    tmp = (void *) strsep(&cmdstr, "-");
    while (tmp)
    {
        if (6 <= i)
        {
            return SW_BAD_VALUE;
        }

        if ((2 < strlen(tmp)) || (0 == strlen(tmp)))
        {
            return SW_BAD_VALUE;
        }

        for (j = 0; j < strlen(tmp); j++)
        {
            if (A_FALSE == is_hex(tmp[j]))
                return SW_BAD_VALUE;
        }

        sscanf(tmp, "%x", &addr);
        if (0xff < addr)
        {
            return SW_BAD_VALUE;
        }

        mac.uc[i++] = addr;
        tmp = (void *) strsep(&cmdstr, "-");
    }

    if (6 != i)
    {
        return SW_BAD_VALUE;
    }

    *(fal_mac_addr_t *) val = mac;
    return SW_OK;
}
#ifdef IN_FDB
sw_error_t
cmd_data_check_fdbentry(char *info, void *val, a_uint32_t size)
{
    sw_error_t rv;
    fal_fdb_entry_t entry;
    a_uint32_t tmp;

    memset(&entry, 0, sizeof (fal_fdb_entry_t));

    rv = __cmd_data_check_complex("addr", NULL,
                        "usage: the format is xx-xx-xx-xx-xx-xx \n",
                        cmd_data_check_macaddr, &entry.addr,
                        sizeof (fal_mac_addr_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("fid", "65535",
                        "usage: the range is 1 -- 4095 or 65535\n",
                        cmd_data_check_uint32, &tmp, sizeof (a_uint32_t));
    if (rv)
        return rv;
    entry.fid = tmp & 0xffff;

    rv = __cmd_data_check_complex("dacmd", "forward",
                        "usage: <forward/drop/cpycpu/rdtcpu>\n",
                        cmd_data_check_maccmd, &entry.dacmd,
                        sizeof (fal_fwd_cmd_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("sacmd", "forward",
                        "usage: <forward/drop/cpycpu/rdtcpu>\n",
                        cmd_data_check_maccmd, &entry.sacmd,
                        sizeof (fal_fwd_cmd_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("dest port", "null",
                        "usage: input port number such as 1,3\n",
                        cmd_data_check_portmap, &entry.port.map,
                        sizeof (fal_pbmp_t));
    if (rv)
        return rv;

    entry.portmap_en = A_TRUE;

    rv = __cmd_data_check_boolean("static", "yes",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_TRUE, &entry.static_en,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("leaky", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &entry.leaky_en,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("mirror", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &entry.mirror_en,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("clone", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &entry.clone_en,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("queue override", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &entry.da_pri_en,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    if (A_TRUE == entry.da_pri_en)
    {
        rv = __cmd_data_check_complex("queue", NULL,
                            "usage: input number such as <0/1/2/3>\n",
                            cmd_data_check_uint32, &tmp, sizeof (a_uint32_t));
        if (rv)
            return rv;
        entry.da_queue = tmp;
    }

    rv = __cmd_data_check_boolean("cross_pt_state", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &entry.cross_pt_state,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("white_list_en", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &entry.white_list_en,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("load_balance_en", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &entry.load_balance_en,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    if (A_TRUE == entry.load_balance_en)
    {
        rv = __cmd_data_check_complex("load_balance", NULL,
                            "usage: input number such as <0/1/2/3>\n",
                            cmd_data_check_uint32, &tmp, sizeof (a_uint32_t));
        if (rv)
            return rv;
        entry.load_balance = tmp;
    }

    *(fal_fdb_entry_t *) val = entry;

    return SW_OK;
}
#endif
sw_error_t
cmd_data_check_integer(char *cmd_str, a_uint32_t * arg_val, a_uint32_t max_val,
                       a_uint32_t min_val)
{
    a_uint32_t tmp;
    a_uint32_t i;

    if (NULL == cmd_str)
    {
        return SW_BAD_PARAM;
    }

    if (0 == cmd_str[0])
    {
        return SW_BAD_PARAM;
    }

    if ((cmd_str[0] == '0') && ((cmd_str[1] == 'x') || (cmd_str[1] == 'X')))
    {
        for (i = 2; i < strlen(cmd_str); i++)
        {
            if (A_FALSE == is_hex(cmd_str[i]))
            {
                return SW_BAD_VALUE;
            }
        }
        sscanf(cmd_str, "%x", &tmp);
    }
    else
    {
        for (i = 0; i < strlen(cmd_str); i++)
        {
            if (A_FALSE == is_dec(cmd_str[i]))
            {
                return SW_BAD_VALUE;
            }
        }
        sscanf(cmd_str, "%d", &tmp);
    }

    if ((tmp > max_val) || (tmp < min_val))
        return SW_BAD_PARAM;

    *arg_val = tmp;
    return SW_OK;
}
#ifdef IN_ACL
sw_error_t
cmd_data_check_ruletype(char *cmd_str, fal_acl_rule_type_t * arg_val,
                        a_uint32_t size)
{
    if (NULL == cmd_str)
    {
        return SW_BAD_VALUE;
    }

    if (!strcasecmp(cmd_str, "mac"))
    {
        *arg_val = FAL_ACL_RULE_MAC;
    }
    else if (!strcasecmp(cmd_str, "ip4"))
    {
        *arg_val = FAL_ACL_RULE_IP4;
    }
    else if (!strcasecmp(cmd_str, "ip6"))
    {
        *arg_val = FAL_ACL_RULE_IP6;
    }
    else if (!strcasecmp(cmd_str, "udf"))
    {
        *arg_val = FAL_ACL_RULE_UDF;
    }
    else
    {
        return SW_BAD_VALUE;
    }

    return SW_OK;
}
#endif
sw_error_t
cmd_data_check_ip4addr(char *cmdstr, void * val, a_uint32_t size)
{
    char *tmp = NULL;
    a_uint32_t i = 0, j;
    a_uint32_t addr;
    fal_ip4_addr_t ip4;
    char cmd[128] = { 0 };
	char *str;

    memset(&ip4, 0, sizeof (fal_ip4_addr_t));
    if (NULL == cmdstr)
    {
        return SW_BAD_VALUE;
    }

    if (0 == cmdstr[0])
    {
        return SW_BAD_VALUE;
    }

    for (i = 0; i < 128; i++)
    {
        if (0 == cmdstr[i])
        {
            break;
        }
    }

    i++;
    if (128 < i)
    {
        i = 128;
    }

    memcpy(cmd, cmdstr, i);
	str = cmd;
    tmp = (void *) strsep(&str, ".");
    i = 0;
    while (tmp)
    {
        if (4 <= i)
        {
            return SW_BAD_VALUE;
        }

        if ((3 < strlen(tmp)) || (0 == strlen(tmp)))
        {
            return SW_BAD_VALUE;
        }

        for (j = 0; j < strlen(tmp); j++)
        {
            if (A_FALSE == is_dec(tmp[j]))
            {
                return SW_BAD_VALUE;
            }
        }

        sscanf(tmp, "%d", &addr);
        if (255 < addr)
        {
            return SW_BAD_VALUE;
        }

        ip4 |= ((addr & 0xff) << (24 - i * 8));
        i++;
        tmp = (void *) strsep(&str, ".");
    }

    if (4 != i)
    {
        return SW_BAD_VALUE;
    }

    *(fal_ip4_addr_t*)val = ip4;
    return SW_OK;
}

#ifdef IN_IGMP
sw_error_t
cmd_data_check_multi(char *info, void *val, a_uint32_t size)
{
    sw_error_t rv;
    fal_igmp_sg_entry_t entry;

    memset(&entry, 0, sizeof (fal_igmp_sg_entry_t));

    rv = __cmd_data_check_complex("group type", "0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.group.type),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    if(entry.group.type == 0)
    {
        rv = __cmd_data_check_complex("group ip4 addr", "0.0.0.0",
                            "usage: the format is xx.xx.xx.xx \n",
                            cmd_data_check_ip4addr, &(entry.group.u.ip4_addr),
                            4);
        if (rv)
            return rv;
    }
    else
    {
        rv = __cmd_data_check_complex("group ip6 addr", NULL,
                            "usage: the format is xx.xx.xx.xx \n",
                            cmd_data_check_ip6addr, &(entry.group.u.ip6_addr),
                            16);
        if (rv)
            return rv;

    }

    rv = __cmd_data_check_complex("source type", "0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.source.type),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    if(entry.source.type == 0)
    {
        rv = __cmd_data_check_complex("source ip4 addr", "0.0.0.0",
                            "usage: the format is xx.xx.xx.xx \n",
                            cmd_data_check_ip4addr, &(entry.source.u.ip4_addr),
                            4);
        if (rv)
            return rv;
    }
    else
    {
        rv = __cmd_data_check_complex("source ip6 addr", NULL,
                            "usage: the format is xx.xx.xx.xx \n",
                            cmd_data_check_ip6addr, &(entry.source.u.ip6_addr),
                            16);
        if (rv)
            return rv;
    }

    rv = __cmd_data_check_complex("portmap", "0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.port_map),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("vlanid", "0xffff",
                        "usage: the range is 0 -- 4095 or 65535\n",
                        cmd_data_check_uint32, &(entry.vlan_id),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    *(fal_igmp_sg_entry_t *)val = entry;

    return SW_OK;
}
#endif

sw_error_t
cmd_data_check_ip6addr(char *cmdstr, void * val, a_uint32_t size)
{
    char *tmp = NULL;
    a_uint32_t j;
    a_uint32_t i = 0, cnt = 0, rep = 0, loc = 0;
    a_uint32_t data;
    a_uint32_t addr[8];
    fal_ip6_addr_t ip6;

    if (NULL == cmdstr)
    {
        return SW_BAD_VALUE;
    }

    if (0 == cmdstr[0])
    {
        return SW_BAD_VALUE;
    }

    for (i = 0; i < 8; i++)
    {
        addr[i] = 0;
    }

    for (i = 0; i < strlen(cmdstr); i++)
    {
        if (':' == cmdstr[i])
        {
            if ((i == (strlen(cmdstr) - 1))
                    || (0 == i))
            {
                return SW_BAD_VALUE;
            }
            cnt++;

            if (':' == cmdstr[i - 1])
            {
                rep++;
                loc = cnt - 1;
            }
        }
    }

    if (1 < rep)
    {
        return SW_BAD_VALUE;
    }

    tmp = (void *) strsep(&cmdstr, ":");
    i = 0;
    while (tmp)
    {
        if (8 <= i)
        {
            return SW_BAD_VALUE;
        }

        if ((4 < strlen(tmp)) || (0 == strlen(tmp)))
        {
            return SW_BAD_VALUE;
        }

        for (j = 0; j < strlen(tmp); j++)
        {
            if (A_FALSE == is_hex(tmp[j]))
            {
                return SW_BAD_VALUE;
            }
        }

        sscanf(tmp, "%x", &data);
        if (65535 < data)
        {
            return SW_BAD_VALUE;
        }

        addr[i++] = data;
        tmp = (void *) strsep(&cmdstr, ":");
    }

    if (0 == rep)
    {
        if (8 != i)
        {
            return SW_BAD_VALUE;
        }
    }
    else
    {
        if (8 <= i)
        {
            return SW_BAD_VALUE;
        }

        for (j = i - 1; j >= loc; j--)
        {
            addr[8 - i + j] = addr[j];
            addr[j] = 0;
        }
    }

    for (i = 0; i < 4; i++)
    {
        ip6.ul[i] = (addr[i * 2] << 16) | addr[i * 2 + 1];
    }

    dprintf("\n");
    for (i = 0; i < 4; i++)
    {
        dprintf("%08x  ", ip6.ul[i]);
    }
    dprintf("\n");

    *(fal_ip6_addr_t*)val = ip6;
    return SW_OK;
}


sw_error_t
cmd_data_check_udf_element(char *cmdstr, a_uint8_t * val, a_uint32_t * len)
{
    char *tmp = NULL;
    a_uint32_t i = 0, j;
    a_uint32_t data;

    memset(val, 0, 16);
    if (NULL == cmdstr)
    {
        return SW_BAD_VALUE;
    }

    if (0 == cmdstr[0])
    {
        return SW_BAD_VALUE;
    }

    tmp = (void *) strsep(&cmdstr, "-");
    while (tmp)
    {
        if (16 <= i)
        {
            return SW_BAD_VALUE;
        }

        if ((2 < strlen(tmp)) || (0 == strlen(tmp)))
        {
            return SW_BAD_VALUE;
        }

        for (j = 0; j < strlen(tmp); j++)
        {
            if (A_FALSE == is_hex(tmp[j]))
            {
                return SW_BAD_VALUE;
            }
        }

        sscanf(tmp, "%x", &data);

        val[i++] = data & 0xff;
        tmp = (void *) strsep(&cmdstr, "-");
    }

    if (0 == i)
    {
        return SW_BAD_VALUE;
    }

    *len = i;
    return SW_OK;
}

sw_error_t
cmd_data_check_patternmode(char *cmd_str, led_pattern_mode_t * arg_val,
                           a_uint32_t size)
{
    if (NULL == cmd_str)
    {
        return SW_BAD_VALUE;
    }

    if (!strcasecmp(cmd_str, "always_off"))
    {
        *arg_val = LED_ALWAYS_OFF;
    }
    else if (!strcasecmp(cmd_str, "always_blink"))
    {
        *arg_val = LED_ALWAYS_BLINK;
    }
    else if (!strcasecmp(cmd_str, "always_on"))
    {
        *arg_val = LED_ALWAYS_ON;
    }
    else  if (!strcasecmp(cmd_str, "map"))
    {
        *arg_val = LED_PATTERN_MAP_EN;
    }
    else
    {
        return SW_BAD_VALUE;
    }

    return SW_OK;
}
#ifdef IN_LED
sw_error_t
cmd_data_check_blinkfreq(char *cmd_str, led_blink_freq_t * arg_val,
                         a_uint32_t size)
{
    if (NULL == cmd_str)
    {
        return SW_BAD_VALUE;
    }

    if (!strcasecmp(cmd_str, "2HZ"))
    {
        *arg_val = LED_BLINK_2HZ;
    }
    else if (!strcasecmp(cmd_str, "4HZ"))
    {
        *arg_val = LED_BLINK_4HZ;
    }
    else if (!strcasecmp(cmd_str, "8HZ"))
    {
        *arg_val = LED_BLINK_8HZ;
    }
    else if (!strcasecmp(cmd_str, "TXRX"))
    {
        *arg_val = LED_BLINK_TXRX;
    }
    else
    {
        return SW_BAD_VALUE;
    }

    return SW_OK;
}

sw_error_t
cmd_data_check_ledpattern(char *info, void * val, a_uint32_t size)
{
    led_ctrl_pattern_t pattern;
    a_uint32_t tmpdata;
    sw_error_t rv;

    memset(&pattern, 0, sizeof (led_ctrl_pattern_t));

    dprintf("\n");

    /* get pattern mode configuration */
    rv = __cmd_data_check_complex("pattern_mode", NULL,
                        "usage: <always_off/always_blink/always_on/map>\n",
                        cmd_data_check_patternmode, &pattern.mode,
                        sizeof (led_pattern_mode_t));
    if (rv)
        return rv;

    if (LED_PATTERN_MAP_EN == pattern.mode)
    {
        rv = __cmd_data_check_boolean("full_duplex_light", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &tmpdata,
                        sizeof (a_bool_t));
        if (rv)
            return rv;

        if (1 == tmpdata)
        {
            pattern.map |= (1 << FULL_DUPLEX_LIGHT_EN);
        }

        rv = __cmd_data_check_boolean("half_duplex_light", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &tmpdata,
                        sizeof (a_bool_t));
        if (rv)
            return rv;

        if (1 == tmpdata)
        {
            pattern.map |= (1 << HALF_DUPLEX_LIGHT_EN);
        }

        rv = __cmd_data_check_boolean("power_on_light", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &tmpdata,
                        sizeof (a_bool_t));
        if (rv)
            return rv;

        if (1 == tmpdata)
        {
            pattern.map |= (1 << POWER_ON_LIGHT_EN);
        }

        rv = __cmd_data_check_boolean("link_1000m_light", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &tmpdata,
                        sizeof (a_bool_t));
        if (rv)
            return rv;

        if (1 == tmpdata)
        {
            pattern.map |= (1 << LINK_1000M_LIGHT_EN);
        }

        rv = __cmd_data_check_boolean("link_100m_light", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &tmpdata,
                        sizeof (a_bool_t));
        if (rv)
            return rv;

        if (1 == tmpdata)
        {
            pattern.map |= (1 << LINK_100M_LIGHT_EN);
        }

        rv = __cmd_data_check_boolean("link_10m_light", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &tmpdata,
                        sizeof (a_bool_t));
        if (rv)
            return rv;

        if (1 == tmpdata)
        {
            pattern.map |= (1 << LINK_10M_LIGHT_EN);
        }

        rv = __cmd_data_check_boolean("conllision_light", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &tmpdata,
                        sizeof (a_bool_t));
        if (rv)
            return rv;

        if (1 == tmpdata)
        {
            pattern.map |= (1 << COLLISION_BLINK_EN);
        }

        rv = __cmd_data_check_boolean("rx_traffic_blink", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &tmpdata,
                        sizeof (a_bool_t));
        if (rv)
            return rv;

        if (1 == tmpdata)
        {
            pattern.map |= (1 << RX_TRAFFIC_BLINK_EN);
        }

        rv = __cmd_data_check_boolean("tx_traffic_blink", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &tmpdata,
                        sizeof (a_bool_t));
        if (rv)
            return rv;

        if (1 == tmpdata)
        {
            pattern.map |= (1 << TX_TRAFFIC_BLINK_EN);
        }

        rv = __cmd_data_check_boolean("linkup_override_light", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &tmpdata,
                        sizeof (a_bool_t));
        if (rv)
            return rv;

        if (1 == tmpdata)
        {
            pattern.map |= (1 << LINKUP_OVERRIDE_EN);
        }

        rv = __cmd_data_check_complex("blink freq", NULL,
                        "usage: <2HZ/4HZ/8HZ/TXRX> \n",
                        cmd_data_check_blinkfreq, &pattern.freq,
                        sizeof (led_blink_freq_t));
        if (rv)
            return rv;
    }

    *(led_ctrl_pattern_t *)val = pattern;

    return SW_OK;
}
#endif

/*Shiva*/
#ifdef IN_PORTVLAN
sw_error_t
cmd_data_check_invlan_mode(char *cmd_str, a_uint32_t * arg_val, a_uint32_t size)
{
    if (cmd_str == NULL)
        return SW_BAD_PARAM;

    if (!strcasecmp(cmd_str, "admit_all"))
    {
        *arg_val = FAL_INVLAN_ADMIT_ALL;
    }
    else if (!strcasecmp(cmd_str, "admit_tagged"))
    {
        *arg_val = FAL_INVLAN_ADMIT_TAGGED;
    }
    else if (!strcasecmp(cmd_str, "admit_untagged"))
    {
        *arg_val = FAL_INVLAN_ADMIT_UNTAGGED;
    }
    else
    {
        //dprintf("input error \n");
        return SW_BAD_VALUE;
    }

    return SW_OK;
}
#ifndef IN_PORTVLAN_MINI
sw_error_t
cmd_data_check_vlan_propagation(char *cmd_str, a_uint32_t * arg_val, a_uint32_t size)
{
    if (cmd_str == NULL)
        return SW_BAD_PARAM;

    if (!strcasecmp(cmd_str, "disable"))
    {
        *arg_val = FAL_VLAN_PROPAGATION_DISABLE;
    }
    else if (!strcasecmp(cmd_str, "clone"))
    {
        *arg_val = FAL_VLAN_PROPAGATION_CLONE;
    }
    else if (!strcasecmp(cmd_str, "replace"))
    {
        *arg_val = FAL_VLAN_PROPAGATION_REPLACE;
    }
    else
    {
        //dprintf("input error \n");
        return SW_BAD_VALUE;
    }

    return SW_OK;
}


sw_error_t
cmd_data_check_vlan_translation(char *info, fal_vlan_trans_entry_t *val, a_uint32_t size)
{
    sw_error_t rv;
    fal_vlan_trans_entry_t entry;

    memset(&entry, 0, sizeof (fal_vlan_trans_entry_t));

    rv = __cmd_data_check_complex("ovid", "1",
                        "usage: the range is 0 -- 4095\n",
                        cmd_data_check_uint32, &entry.o_vid,
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("bi direction", "yes",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_TRUE, &entry.bi_dir,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("forward direction", "yes",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_TRUE, &entry.forward_dir,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("reverse direction", "yes",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_TRUE, &entry.reverse_dir,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("svid ", "1",
                        "usage: the range is 0 -- 4095\n",
                        cmd_data_check_uint32, &entry.s_vid,
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("cvid ", "1",
                        "usage: the range is 0 -- 4095\n",
                        cmd_data_check_uint32, &entry.c_vid,
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("ovid_is_cvid", "yes",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_TRUE, &entry.o_vid_is_cvid,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("svid_enable", "yes",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_TRUE, &entry.s_vid_enable,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("cvid_enable", "yes",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_TRUE, &entry.c_vid_enable,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("one_2_one_vlan", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &entry.one_2_one_vlan,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    *val = entry;
    return SW_OK;
}


sw_error_t
cmd_data_check_qinq_mode(char *cmd_str, a_uint32_t * arg_val, a_uint32_t size)
{
    if (cmd_str == NULL)
        return SW_BAD_PARAM;

    if (!strcasecmp(cmd_str, "ctag"))
    {
        *arg_val = FAL_QINQ_CTAG_MODE;
    }
    else if (!strcasecmp(cmd_str, "stag"))
    {
        *arg_val = FAL_QINQ_STAG_MODE;
    }
    else
    {
        //dprintf("input error \n");
        return SW_BAD_VALUE;
    }

    return SW_OK;
}


sw_error_t
cmd_data_check_qinq_role(char *cmd_str, a_uint32_t * arg_val, a_uint32_t size)
{
    if (cmd_str == NULL)
        return SW_BAD_PARAM;

    if (!strcasecmp(cmd_str, "edge"))
    {
        *arg_val = FAL_QINQ_EDGE_PORT;
    }
    else if (!strcasecmp(cmd_str, "core"))
    {
        *arg_val = FAL_QINQ_CORE_PORT;
    }
    else
    {
        //dprintf("input error \n");
        return SW_BAD_VALUE;
    }

    return SW_OK;
}
#endif
#endif

#ifdef IN_PORTCONTROL
sw_error_t
cmd_data_check_hdrmode(char *cmd_str, a_uint32_t * arg_val, a_uint32_t size)
{
    if (cmd_str == NULL)
        return SW_BAD_PARAM;

    if (!strcasecmp(cmd_str, "noheader"))
    {
        *arg_val = FAL_NO_HEADER_EN;
    }
    else if (!strcasecmp(cmd_str, "onlymanagement"))
    {
        *arg_val = FAL_ONLY_MANAGE_FRAME_EN;
    }
    else if (!strcasecmp(cmd_str, "allframe"))
    {
        *arg_val = FAL_ALL_TYPE_FRAME_EN;
    }
    else
    {
        //dprintf("input error \n");
        return SW_BAD_VALUE;
    }

    return SW_OK;
}
#endif
#ifdef IN_FDB
sw_error_t
cmd_data_check_fdboperation(char *cmd_str, void * val, a_uint32_t size)
{
    sw_error_t rv;
    fal_fdb_op_t entry;

    memset(&entry, 0, sizeof (fal_fdb_op_t));

    rv = __cmd_data_check_boolean("port_en", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &entry.port_en,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("fid_en", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &entry.fid_en,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("multi_en", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &entry.multicast_en,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    *(fal_fdb_op_t *) val = entry;
    return SW_OK;
}
#endif
#ifdef IN_PPPOE
sw_error_t
cmd_data_check_pppoe(char *cmd_str, void * val, a_uint32_t size)
{
    sw_error_t rv;
    fal_pppoe_session_t entry;

    aos_mem_zero(&entry, sizeof (fal_pppoe_session_t));

    rv = __cmd_data_check_complex("entryid", "0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.entry_id),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("sessionid", "0",
                        "usage: the range is 0 -- 65535\n",
                        cmd_data_check_uint32, &entry.session_id,
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("multi_session", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &entry.multi_session,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("uni_session", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &entry.uni_session,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("vrf_id", "0",
                        "usage: the range is 0 -- 7\n",
                        cmd_data_check_uint32, &entry.vrf_id,
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    *(fal_pppoe_session_t*)val = entry;
    return SW_OK;
}

sw_error_t
cmd_data_check_pppoe_less(char *cmd_str, void * val, a_uint32_t size)
{
    sw_error_t rv;
    fal_pppoe_session_t entry;

    aos_mem_zero(&entry, sizeof (fal_pppoe_session_t));

    rv = __cmd_data_check_complex("sessionid", "0",
                        "usage: the range is 0 -- 65535\n",
                        cmd_data_check_uint32, &entry.session_id,
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    *(fal_pppoe_session_t*)val = entry;
    return SW_OK;
}
#endif

#if defined(IN_IP) || defined(IN_NAT)
sw_error_t
cmd_data_check_host_entry(char *cmd_str, void * val, a_uint32_t size)
{
    sw_error_t rv;
    fal_host_entry_t entry;

    aos_mem_zero(&entry, sizeof (fal_host_entry_t));

    rv = __cmd_data_check_complex("entryid", "0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.entry_id),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("entryflags", "0x1",
                        "usage: bitmap for host entry\n",
                        cmd_data_check_uint32, &(entry.flags),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("entrystatus", "0",
                        "usage: bitmap for host entry\n",
                        cmd_data_check_uint32, &(entry.status),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    if (FAL_IP_IP4_ADDR & (entry.flags) ==  FAL_IP_IP4_ADDR|| 
		FAL_IP_IP4_ADDR_MCAST& (entry.flags) ==  FAL_IP_IP4_ADDR_MCAST)
    {
        rv = __cmd_data_check_complex("ip4 addr", NULL,
                            "usage: the format is xx.xx.xx.xx \n",
                            cmd_data_check_ip4addr, &(entry.ip4_addr),
                            4);
        if (rv)
            return rv;
    }
    else if ((FAL_IP_IP6_ADDR & (entry.flags)) == FAL_IP_IP6_ADDR || 
		(FAL_IP_IP6_ADDR_MCAST& (entry.flags)) == FAL_IP_IP6_ADDR_MCAST)
    {
        rv = __cmd_data_check_complex("ip6 addr", NULL,
                            "usage: the format is xxxx::xxxx \n",
                            cmd_data_check_ip6addr, &(entry.ip6_addr),
                            16);
        if (rv)
            return rv;
    }

    rv = __cmd_data_check_complex("mac addr", NULL,
                        "usage: the format is xx-xx-xx-xx-xx-xx \n",
                        cmd_data_check_macaddr, &(entry.mac_addr),
                        sizeof (fal_mac_addr_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("interface id", "0",
                        "usage: the format is xx-xx-xx-xx-xx-xx \n",
                        cmd_data_check_uint32, &(entry.intf_id),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("load_balance num", "0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.lb_num),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("vrf id", "0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.vrf_id),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("port id", "0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.port_id),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("action", "forward",
                        "usage: <forward/drop/cpycpu/rdtcpu>\n",
                        cmd_data_check_maccmd, &(entry.action),
                        sizeof (fal_fwd_cmd_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("mirror", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &entry.mirror_en,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("counter", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &entry.counter_en,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    if (A_TRUE == entry.counter_en)
    {
        rv = __cmd_data_check_complex("counter id", "0",
                            "usage: integer\n",
                            cmd_data_check_uint32, &(entry.counter_id),
                            sizeof (a_uint32_t));
        if (rv)
            return rv;
    }

    rv = __cmd_data_check_complex("dst info", "0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.dst_info),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("sync_toggle", "0",
                        "usage: integer\n",
                        cmd_data_check_uint8, &(entry.syn_toggle),
                        sizeof (a_uint8_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("lan_wan", "0",
                        "usage: integer\n",
                        cmd_data_check_uint8, &(entry.lan_wan),
                        sizeof (a_uint8_t));
    if (rv)
        return rv;

    if ((FAL_IP_IP4_ADDR_MCAST & (entry.flags)) == FAL_IP_IP4_ADDR_MCAST || 
		(FAL_IP_IP6_ADDR_MCAST& (entry.flags)) == FAL_IP_IP6_ADDR_MCAST) {
         rv = __cmd_data_check_complex("vsi", "0",
                        "usage: integer\n",
                        cmd_data_check_uint8, &(entry.mcast_info.vsi),
                        sizeof (a_uint8_t));
        if (rv)
            return rv;
        if ((FAL_IP_IP4_ADDR_MCAST & (entry.flags)) == FAL_IP_IP4_ADDR_MCAST) {
		rv = __cmd_data_check_complex("ip4 addr", NULL,
                            "usage: the format is xx.xx.xx.xx \n",
                            cmd_data_check_ip4addr, &(entry.mcast_info.sip4_addr),
                            4);
            if (rv)
                return rv;
        } else {
            rv = __cmd_data_check_complex("ip6 addr", NULL,
                            "usage: the format is xxxx::xxxx \n",
                            cmd_data_check_ip6addr, &(entry.mcast_info.sip6_addr),
                            16);
            if (rv)
                return rv;
        }
    }

    

    *(fal_host_entry_t *)val = entry;
    return SW_OK;
}


sw_error_t
cmd_data_check_arp_learn_mode(char *cmd_str, fal_arp_learn_mode_t * arg_val,
                              a_uint32_t size)
{
    if (NULL == cmd_str)
    {
        return SW_BAD_VALUE;
    }

    if (!strcasecmp(cmd_str, "learnlocal"))
    {
        *arg_val = FAL_ARP_LEARN_LOCAL;
    }
    else if (!strcasecmp(cmd_str, "learnall"))
    {
        *arg_val = FAL_ARP_LEARN_ALL;
    }
    else
    {
        return SW_BAD_VALUE;
    }

    return SW_OK;
}


sw_error_t
cmd_data_check_ip_guard_mode(char *cmd_str, fal_source_guard_mode_t * arg_val, a_uint32_t size)
{
    if (NULL == cmd_str)
    {
        return SW_BAD_VALUE;
    }

    if (!strcasecmp(cmd_str, "mac_ip"))
    {
        *arg_val = FAL_MAC_IP_GUARD;
    }
    else if (!strcasecmp(cmd_str, "mac_ip_port"))
    {
        *arg_val = FAL_MAC_IP_PORT_GUARD;
    }
    else if (!strcasecmp(cmd_str, "mac_ip_vlan"))
    {
        *arg_val = FAL_MAC_IP_VLAN_GUARD;
    }
    else if (!strcasecmp(cmd_str, "mac_ip_port_vlan"))
    {
        *arg_val = FAL_MAC_IP_PORT_VLAN_GUARD;
    }
    else if (!strcasecmp(cmd_str, "no_guard"))
    {
        *arg_val = FAL_NO_SOURCE_GUARD;
    }
    else
    {
        return SW_BAD_VALUE;
    }

    return SW_OK;
}



sw_error_t
cmd_data_check_nat_entry(char *cmd_str, void * val, a_uint32_t size)
{
    sw_error_t rv;
    a_uint32_t tmp;
    fal_nat_entry_t entry;

    aos_mem_zero(&entry, sizeof (fal_nat_entry_t));

    rv = __cmd_data_check_complex("entryid", "0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.entry_id),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("entryflags", "0",
                        "usage: bitmap for host entry\n",
                        cmd_data_check_uint32, &(entry.flags),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("entrystatus", "0xf",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.status),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("select_idx", "0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.slct_idx),
                        sizeof (a_uint32_t));

	if (rv)
        return rv;

	rv = __cmd_data_check_complex("vrf_id", "0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.vrf_id),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("src addr", "0.0.0.0",
                        "usage: the format is xx.xx.xx.xx \n",
                        cmd_data_check_ip4addr, &(entry.src_addr),
                        4);
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("trans addr", "0.0.0.0",
                        "usage: the format is xx.xx.xx.xx \n",
                        cmd_data_check_ip4addr, &(entry.trans_addr),
                        4);
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("port num", "0",
                        "usage: 0- 65535\n",
                        cmd_data_check_uint16, &tmp, sizeof (a_uint32_t));
    if (rv)
        return rv;
    entry.port_num = tmp & 0xffff;


    rv = __cmd_data_check_complex("port range", "0",
                        "usage: 0- 65535\n",
                        cmd_data_check_uint16, &tmp, sizeof (a_uint32_t));
    if (rv)
        return rv;
    entry.port_range = tmp & 0xffff;

    rv = __cmd_data_check_complex("action", "forward",
                        "usage: <forward/drop/cpycpu/rdtcpu>\n",
                        cmd_data_check_maccmd, &entry.action,
                        sizeof (fal_fwd_cmd_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("mirror", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &entry.mirror_en,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("counter", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &entry.counter_en,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    if (A_TRUE == entry.counter_en)
    {
        rv = __cmd_data_check_complex("counter id", "0",
                            "usage: integer\n",
                            cmd_data_check_uint32, &(entry.counter_id),
                            sizeof (a_uint32_t));
        if (rv)
            return rv;
    }

    *(fal_nat_entry_t *)val = entry;
    return SW_OK;
}



sw_error_t
cmd_data_check_napt_entry(char *cmd_str, void * val, a_uint32_t size)
{
    sw_error_t rv;
    a_uint32_t tmp;
    fal_napt_entry_t entry;

    aos_mem_zero(&entry, sizeof (fal_napt_entry_t));

    rv = __cmd_data_check_complex("entryid", "0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &entry.entry_id,
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("entryflags", "0",
                        "usage: bitmap for host entry\n",
                        cmd_data_check_uint32, &(entry.flags),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("entrystatus", "0xf",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.status),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

	rv = __cmd_data_check_complex("vrf_id", "0x0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.vrf_id),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

	rv = __cmd_data_check_complex("flow_cookie", "0x0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.flow_cookie),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

	rv = __cmd_data_check_complex("load_balance", "0x0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.load_balance),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("src addr", "0.0.0.0",
                        "usage: the format is xx.xx.xx.xx \n",
                        cmd_data_check_ip4addr, &(entry.src_addr),
                        4);
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("dst addr", "0.0.0.0",
                        "usage: the format is xx.xx.xx.xx \n",
                        cmd_data_check_ip4addr, &(entry.dst_addr),
                        4);
    if (rv)
        return rv;

    if (FAL_NAT_ENTRY_TRANS_IPADDR_INDEX & (entry.flags))
    {
        rv = __cmd_data_check_complex("trans addr index", "0",
                            "usage: integer\n",
                            cmd_data_check_uint32, &(entry.trans_addr),
                            sizeof (a_uint32_t));
        if (rv)
            return rv;
    }
    else
    {
        rv = __cmd_data_check_complex("trans addr", "0.0.0.0",
                            "usage: the format is xx.xx.xx.xx \n",
                            cmd_data_check_ip4addr, &(entry.trans_addr),
                            4);
        if (rv)
            return rv;
    }

    rv = __cmd_data_check_complex("src port", "0",
                        "usage: 0- 65535\n",
                        cmd_data_check_uint16, &tmp,
                        sizeof (a_uint32_t));
    if (rv)
        return rv;
    entry.src_port = tmp & 0xffff;

    rv = __cmd_data_check_complex("dst port", "0",
                        "usage: 0- 65535\n",
                        cmd_data_check_uint16, &tmp,
                        sizeof (a_uint32_t));
    if (rv)
        return rv;
    entry.dst_port = tmp & 0xffff;

    rv = __cmd_data_check_complex("trans port", "0",
                        "usage: 0- 65535\n",
                        cmd_data_check_uint16, &tmp,
                        sizeof (a_uint32_t));
    if (rv)
        return rv;
    entry.trans_port = tmp & 0xffff;

    rv = __cmd_data_check_complex("action", "forward",
                        "usage: <forward/drop/cpycpu/rdtcpu>\n",
                        cmd_data_check_maccmd, &(entry.action),
                        sizeof (fal_fwd_cmd_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("mirror", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &entry.mirror_en,
                        sizeof (a_bool_t));
    if (rv)
        return rv;


    rv = __cmd_data_check_boolean("counter", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &entry.counter_en,
                        sizeof (a_bool_t));
    if (rv)
        return rv;


    if (A_TRUE == entry.counter_en)
    {
        rv = __cmd_data_check_complex("counter id", "0",
                            "usage: integer\n",
                            cmd_data_check_uint32, &(entry.counter_id),
                            sizeof (a_uint32_t));
        if (rv)
            return rv;
    }

	rv = __cmd_data_check_boolean("priority", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &entry.priority_en,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

	if (A_TRUE == entry.priority_en)
    {
        rv = __cmd_data_check_complex("priority value", "0",
                            "usage: integer\n",
                            cmd_data_check_uint32, &(entry.priority_val),
                            sizeof (a_uint32_t));
        if (rv)
            return rv;
    }

    *(fal_napt_entry_t *)val = entry;
    return SW_OK;
}

sw_error_t
cmd_data_check_flow_entry(char *cmd_str, void * val, a_uint32_t size)
{
    sw_error_t rv;
    a_uint32_t tmp;
    fal_napt_entry_t entry;

    aos_mem_zero(&entry, sizeof (fal_napt_entry_t));

    rv = __cmd_data_check_complex("entryid", "0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &entry.entry_id,
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("entryflags", "0",
                        "usage: bitmap for host entry\n",
                        cmd_data_check_uint32, &(entry.flags),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("entrystatus", "0xf",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.status),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

	rv = __cmd_data_check_complex("vrf_id", "0x0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.vrf_id),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

	rv = __cmd_data_check_complex("flow_cookie", "0x0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.flow_cookie),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

	rv = __cmd_data_check_complex("load_balance", "0x0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.load_balance),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("src addr", "0.0.0.0",
                        "usage: the format is xx.xx.xx.xx \n",
                        cmd_data_check_ip4addr, &(entry.src_addr),
                        4);
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("dst addr", "0.0.0.0",
                        "usage: the format is xx.xx.xx.xx \n",
                        cmd_data_check_ip4addr, &(entry.dst_addr),
                        4);
    if (rv)
        return rv;


    rv = __cmd_data_check_complex("src port", "0",
                        "usage: 0- 65535\n",
                        cmd_data_check_uint16, &tmp,
                        sizeof (a_uint32_t));
    if (rv)
        return rv;
    entry.src_port = tmp & 0xffff;

    rv = __cmd_data_check_complex("dst port", "0",
                        "usage: 0- 65535\n",
                        cmd_data_check_uint16, &tmp,
                        sizeof (a_uint32_t));
    if (rv)
        return rv;
    entry.dst_port = tmp & 0xffff;


    rv = __cmd_data_check_complex("action", "forward",
                        "usage: <forward/drop/cpycpu/rdtcpu>\n",
                        cmd_data_check_maccmd, &(entry.action),
                        sizeof (fal_fwd_cmd_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("mirror", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &entry.mirror_en,
                        sizeof (a_bool_t));
    if (rv)
        return rv;


    rv = __cmd_data_check_boolean("counter", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &entry.counter_en,
                        sizeof (a_bool_t));
    if (rv)
        return rv;


    if (A_TRUE == entry.counter_en)
    {
        rv = __cmd_data_check_complex("counter id", "0",
                            "usage: integer\n",
                            cmd_data_check_uint32, &(entry.counter_id),
                            sizeof (a_uint32_t));
        if (rv)
            return rv;
    }

	rv = __cmd_data_check_boolean("priority", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &entry.priority_en,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

	if (A_TRUE == entry.priority_en)
    {
        rv = __cmd_data_check_complex("priority value", "0",
                            "usage: integer\n",
                            cmd_data_check_uint32, &(entry.priority_val),
                            sizeof (a_uint32_t));
        if (rv)
            return rv;
    }

    *(fal_napt_entry_t *)val = entry;
    return SW_OK;
}


sw_error_t
cmd_data_check_napt_mode(char *cmd_str, fal_napt_mode_t * arg_val,
                         a_uint32_t size)
{
    if (NULL == cmd_str)
    {
        return SW_BAD_VALUE;
    }

    if (!strcasecmp(cmd_str, "fullcone"))
    {
        *arg_val = FAL_NAPT_FULL_CONE;
    }
    else if (!strcasecmp(cmd_str, "strictcone"))
    {
        *arg_val = FAL_NAPT_STRICT_CONE;
    }
    else if (!strcasecmp(cmd_str, "portstrict"))
    {
        *arg_val = FAL_NAPT_PORT_STRICT;
    }
    else if (!strcasecmp(cmd_str, "synmatric"))
    {
        *arg_val = FAL_NAPT_SYNMETRIC;
    }
    else
    {
        return SW_BAD_VALUE;
    }

    return SW_OK;
}


sw_error_t
cmd_data_check_intf_mac_entry(char *cmd_str, void * val, a_uint32_t size)
{
    a_uint32_t tmp;
    sw_error_t rv;
    fal_intf_mac_entry_t entry;

    aos_mem_zero(&entry, sizeof (fal_intf_mac_entry_t));

    rv = __cmd_data_check_complex("entryid", "0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.entry_id),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("vrf id", "0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.vrf_id),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("vid low", NULL,
                        "usage: low vlan id\n",
                        cmd_data_check_uint16, &tmp, sizeof (a_uint32_t));
    if (rv)
        return rv;
    entry.vid_low = tmp & 0xffff;

    rv = __cmd_data_check_complex("vid high", NULL,
                        "usage: high vlan id\n",
                        cmd_data_check_uint16, &tmp, sizeof (a_uint32_t));
    if (rv)
        return rv;
    entry.vid_high = tmp & 0xffff;

    rv = __cmd_data_check_complex("mac addr", NULL,
                        "usage: the format is xx-xx-xx-xx-xx-xx \n",
                        cmd_data_check_macaddr, &(entry.mac_addr),
                        sizeof (fal_mac_addr_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("ip4_route", "yes",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_TRUE, &entry.ip4_route,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("ip6_route", "yes",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_TRUE, &entry.ip6_route,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    *(fal_intf_mac_entry_t *)val = entry;
    return SW_OK;
}


sw_error_t
cmd_data_check_pub_addr_entry(char *cmd_str, void * val, a_uint32_t size)
{
    sw_error_t rv;
    fal_nat_pub_addr_t entry;

    aos_mem_zero(&entry, sizeof (fal_nat_pub_addr_t));

    rv = __cmd_data_check_complex("entryid", "0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.entry_id),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("pub addr", NULL,
                        "usage: the format is xx.xx.xx.xx \n",
                        cmd_data_check_ip4addr, &(entry.pub_addr),
                        4);
    if (rv)
        return rv;

    *(fal_nat_pub_addr_t *)val = entry;
    return SW_OK;
}
#endif

#ifdef IN_RATE
sw_error_t
cmd_data_check_egress_shaper(char *cmd_str, void * val, a_uint32_t size)
{
    sw_error_t rv;
    a_bool_t bool;
    fal_egress_shaper_t entry;

    aos_mem_zero(&entry, sizeof (fal_egress_shaper_t));

    rv = __cmd_data_check_boolean("bytebased", "yes",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_TRUE, &bool,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    if (A_TRUE == bool)
    {
        entry.meter_unit = FAL_BYTE_BASED;
    }
    else
    {
        entry.meter_unit = FAL_FRAME_BASED;
    }

    rv = __cmd_data_check_complex("cir", "0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.cir),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("cbs", "0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.cbs),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("eir", "0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.eir),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("ebs", "0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.ebs),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    *(fal_egress_shaper_t *)val = entry;
    return SW_OK;
}


sw_error_t
cmd_data_check_acl_policer(char *cmd_str, void * val, a_uint32_t size)
{
    sw_error_t rv;
    a_bool_t bool;
    fal_acl_policer_t entry;

    aos_mem_zero(&entry, sizeof (fal_acl_policer_t));

    rv = __cmd_data_check_boolean("counter_mode", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &(entry.counter_mode),
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("bytebased", "yes",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_TRUE, &bool,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    if (A_TRUE == bool)
    {
        entry.meter_unit = FAL_BYTE_BASED;
    }
    else
    {
        entry.meter_unit = FAL_FRAME_BASED;
    }

    if (A_TRUE == entry.counter_mode)
    {
        *(fal_acl_policer_t *)val = entry;
        return SW_OK;
    }

    rv = __cmd_data_check_boolean("couple_flag", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &(entry.couple_flag),
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("color_aware", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &(entry.color_mode),
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("deficit_flag", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &(entry.deficit_en),
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("cir", "0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.cir),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("cbs", "0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.cbs),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("eir", "0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.eir),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("ebs", "0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.ebs),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("meter_interval", "1ms",
                        "usage: the format <100us/1ms/10ms/100ms>\n",
                        cmd_data_check_policer_timesslot, &(entry.meter_interval),
                        sizeof (fal_rate_mt_t));
    if (rv)
        return rv;

    *(fal_acl_policer_t *)val = entry;
    return SW_OK;
}


sw_error_t
cmd_data_check_policer_timesslot(char *cmd_str, a_uint32_t * arg_val, a_uint32_t size)
{
    if (cmd_str == NULL)
        return SW_BAD_PARAM;

    if (!strncasecmp(cmd_str, "100us", 5))
        *arg_val = FAL_RATE_MI_100US;
    else if (!strncasecmp(cmd_str, "1ms", 3))
        *arg_val = FAL_RATE_MI_1MS;
    else if (!strncasecmp(cmd_str, "10ms", 4))
        *arg_val = FAL_RATE_MI_10MS;
    else if (!strncasecmp(cmd_str, "100ms", 5))
        *arg_val = FAL_RATE_MI_100MS;
    else
    {
        //dprintf("input error \n");
        return SW_BAD_VALUE;
    }

    return SW_OK;
}


sw_error_t
cmd_data_check_port_policer(char *cmd_str, void * val, a_uint32_t size)
{
    sw_error_t rv;
    a_bool_t bool;
    fal_port_policer_t entry;

    aos_mem_zero(&entry, sizeof (fal_port_policer_t));

    rv = __cmd_data_check_boolean("combine_enable", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &(entry.combine_mode),
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("bytebased", "yes",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_TRUE, &bool,
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    if (A_TRUE == bool)
    {
        entry.meter_unit = FAL_BYTE_BASED;
    }
    else
    {
        entry.meter_unit = FAL_FRAME_BASED;
    }

    rv = __cmd_data_check_boolean("couple_flag", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &(entry.couple_flag),
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("color_aware", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &(entry.color_mode),
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("deficit_flag", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &(entry.deficit_en),
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("c_enable", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &(entry.c_enable),
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("cir", "0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.cir),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("cbs", "0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.cbs),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("c_rate_flag", "0xfe",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.c_rate_flag),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("c_meter_interval", "1ms",
                        "usage: the format <100us/1ms/10ms/100ms>\n",
                        cmd_data_check_policer_timesslot, &(entry.c_meter_interval),
                        sizeof (fal_rate_mt_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_boolean("e_enable", "no",
                        "usage: <yes/no/y/n>\n",
                        cmd_data_check_confirm, A_FALSE, &(entry.e_enable),
                        sizeof (a_bool_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("eir", "0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.eir),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("ebs", "0",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.ebs),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("e_rate_flag", "0xfe",
                        "usage: integer\n",
                        cmd_data_check_uint32, &(entry.e_rate_flag),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

    rv = __cmd_data_check_complex("e_meter_interval", "1ms",
                        "usage: the format <100us/1ms/10ms/100ms>\n",
                        cmd_data_check_policer_timesslot, &(entry.e_meter_interval),
                        sizeof (fal_rate_mt_t));
    if (rv)
        return rv;

    *(fal_port_policer_t *)val = entry;
    return SW_OK;
}
#endif
#if 0
sw_error_t
cmd_data_check_mac_mode(char *cmd_str, fal_interface_mac_mode_t * arg_val,
                        a_uint32_t size)
{
    if (NULL == cmd_str)
    {
        return SW_BAD_VALUE;
    }

    if (0 == cmd_str[0])
    {
        *arg_val = FAL_MAC_MODE_RGMII;
    }
    else if (!strcasecmp(cmd_str, "rgmii"))
    {
        *arg_val = FAL_MAC_MODE_RGMII;
    }
    else if (!strcasecmp(cmd_str, "rmii"))
    {
        *arg_val = FAL_MAC_MODE_RMII;
    }
    else if (!strcasecmp(cmd_str, "gmii"))
    {
        *arg_val = FAL_MAC_MODE_GMII;
    }
    else if (!strcasecmp(cmd_str, "mii"))
    {
        *arg_val = FAL_MAC_MODE_MII;
    }
    else if (!strcasecmp(cmd_str, "sgmii"))
    {
        *arg_val = FAL_MAC_MODE_SGMII;
    }
    else if (!strcasecmp(cmd_str, "fiber"))
    {
        *arg_val = FAL_MAC_MODE_FIBER;
    }
    else if (!strcasecmp(cmd_str, "default"))
    {
        *arg_val = FAL_MAC_MODE_DEFAULT;
    }
    else
    {
        return SW_BAD_VALUE;
    }

    return SW_OK;
}


sw_error_t
cmd_data_check_clock_mode(char *cmd_str, fal_interface_clock_mode_t * arg_val,
                          a_uint32_t size)
{
    if (NULL == cmd_str)
    {
        return SW_BAD_VALUE;
    }

    if (0 == cmd_str[0])
    {
        *arg_val = FAL_INTERFACE_CLOCK_MAC_MODE;
    }
    if (!strcasecmp(cmd_str, "mac"))
    {
        *arg_val = FAL_INTERFACE_CLOCK_MAC_MODE;
    }
    else if (!strcasecmp(cmd_str, "phy"))
    {
        *arg_val = FAL_INTERFACE_CLOCK_PHY_MODE;
    }
    else
    {
        return SW_BAD_VALUE;
    }

    return SW_OK;
}
#endif
#ifdef IN_FDB
sw_error_t
cmd_data_check_fdb_smode(char *cmd_str, a_uint32_t * arg_val, a_uint32_t size)
{
    if (cmd_str == NULL)
        return SW_BAD_PARAM;

    if (!strcasecmp(cmd_str, "ivl"))
        *arg_val = INVALID_VLAN_IVL;
    else if (!strcasecmp(cmd_str, "svl"))
        *arg_val = INVALID_VLAN_SVL;
    else
    {
        return SW_BAD_VALUE;
    }

    return SW_OK;
}
#endif
#ifdef IN_SEC
sw_error_t
cmd_data_check_sec_mac(char *cmd_str, a_uint32_t * arg_val, a_uint32_t size)
{
    if (cmd_str == NULL)
        return SW_BAD_PARAM;

    if (!strcasecmp(cmd_str, "resv_vid"))
        *arg_val = FAL_NORM_MAC_RESV_VID_CMD;
    else if (!strcasecmp(cmd_str, "invalid_src_addr"))
        *arg_val = FAL_NORM_MAC_INVALID_SRC_ADDR_CMD;
    else
    {
        dprintf("UNKNOWN VALUE");
        return SW_BAD_VALUE;
    }

    return SW_OK;
}

sw_error_t
cmd_data_check_sec_ip(char *cmd_str, a_uint32_t * arg_val, a_uint32_t size)
{
    if (cmd_str == NULL)
        return SW_BAD_PARAM;

    if (!strcasecmp(cmd_str, "invalid_ver"))
        *arg_val = FAL_NORM_IP_INVALID_VER_CMD;
    else if (!strcasecmp(cmd_str, "same_addr"))
        *arg_val = FAL_NROM_IP_SAME_ADDR_CMD;
    else if (!strcasecmp(cmd_str, "ttl_change_status"))
        *arg_val = FAL_NROM_IP_TTL_CHANGE_STATUS;
    else if (!strcasecmp(cmd_str, "ttl_val"))
        *arg_val = FAL_NROM_IP_TTL_VALUE;
    else
    {
        dprintf("UNKNOWN VALUE");
        return SW_BAD_VALUE;
    }

    return SW_OK;
}


sw_error_t
cmd_data_check_sec_ip4(char *cmd_str, a_uint32_t * arg_val, a_uint32_t size)
{
    if (cmd_str == NULL)
        return SW_BAD_PARAM;

    if (!strcasecmp(cmd_str, "invalid_hl"))
        *arg_val = FAL_NROM_IP4_INVALID_HL_CMD;
    else if (!strcasecmp(cmd_str, "hdr_opts"))
        *arg_val = FAL_NROM_IP4_HDR_OPTIONS_CMD;
    else if (!strcasecmp(cmd_str, "invalid_df"))
        *arg_val = FAL_NROM_IP4_INVALID_DF_CMD;
    else if (!strcasecmp(cmd_str, "frag_offset_min_len"))
        *arg_val = FAL_NROM_IP4_FRAG_OFFSET_MIN_LEN_CMD;
    else if (!strcasecmp(cmd_str, "frag_offset_min_size"))
        *arg_val = FAL_NROM_IP4_FRAG_OFFSET_MIN_SIZE;
    else if (!strcasecmp(cmd_str, "frag_offset_max_len"))
        *arg_val = FAL_NROM_IP4_FRAG_OFFSET_MAX_LEN_CMD;
    else if (!strcasecmp(cmd_str, "invalid_frag_offset"))
        *arg_val = FAL_NROM_IP4_INVALID_FRAG_OFFSET_CMD;
    else if (!strcasecmp(cmd_str, "invalid_sip"))
        *arg_val = FAL_NROM_IP4_INVALID_SIP_CMD;
    else if (!strcasecmp(cmd_str, "invalid_dip"))
        *arg_val = FAL_NROM_IP4_INVALID_DIP_CMD;
    else if (!strcasecmp(cmd_str, "invalid_chksum"))
        *arg_val = FAL_NROM_IP4_INVALID_CHKSUM_CMD;
    else if (!strcasecmp(cmd_str, "invalid_pl"))
        *arg_val = FAL_NROM_IP4_INVALID_PL_CMD;
    else if (!strcasecmp(cmd_str, "df_clear_status"))
        *arg_val = FAL_NROM_IP4_DF_CLEAR_STATUS;
    else if (!strcasecmp(cmd_str, "ipid_random_status"))
        *arg_val = FAL_NROM_IP4_IPID_RANDOM_STATUS;
    else
    {
        dprintf("UNKNOWN VALUE");
        return SW_BAD_VALUE;
    }

    return SW_OK;
}

sw_error_t
cmd_data_check_sec_ip6(char *cmd_str, a_uint32_t * arg_val, a_uint32_t size)
{
    if (cmd_str == NULL)
        return SW_BAD_PARAM;

    if (!strcasecmp(cmd_str, "invalid_dip"))
        *arg_val = FAL_NROM_IP6_INVALID_DIP_CMD;
    else if (!strcasecmp(cmd_str, "invalid_sip"))
        *arg_val = FAL_NROM_IP6_INVALID_SIP_CMD;
    else if (!strcasecmp(cmd_str, "invalid_pl"))
        *arg_val = FAL_NROM_IP6_INVALID_PL_CMD;
    else
    {
        dprintf("UNKNOWN VALUE");
        return SW_BAD_VALUE;
    }

    return SW_OK;
}


sw_error_t
cmd_data_check_sec_tcp(char *cmd_str, a_uint32_t * arg_val, a_uint32_t size)
{
    if (cmd_str == NULL)
        return SW_BAD_PARAM;

    if (!strcasecmp(cmd_str, "blat"))
        *arg_val = FAL_NROM_TCP_BLAT_CMD;
    else if (!strcasecmp(cmd_str, "invalid_hl"))
        *arg_val = FAL_NROM_TCP_INVALID_HL_CMD;
    else if (!strcasecmp(cmd_str, "min_hdr_size"))
        *arg_val = FAL_NROM_TCP_MIN_HDR_SIZE;
    else if (!strcasecmp(cmd_str, "invalid_syn"))
        *arg_val = FAL_NROM_TCP_INVALID_SYN_CMD;
    else if (!strcasecmp(cmd_str, "su_block"))
        *arg_val = FAL_NROM_TCP_SU_BLOCK_CMD;
    else if (!strcasecmp(cmd_str, "sp_block"))
        *arg_val = FAL_NROM_TCP_SP_BLOCK_CMD;
    else if (!strcasecmp(cmd_str, "sap_block"))
        *arg_val = FAL_NROM_TCP_SAP_BLOCK_CMD;
    else if (!strcasecmp(cmd_str, "xmas_scan"))
        *arg_val = FAL_NROM_TCP_XMAS_SCAN_CMD;
    else if (!strcasecmp(cmd_str, "null_scan"))
        *arg_val = FAL_NROM_TCP_NULL_SCAN_CMD;
    else if (!strcasecmp(cmd_str, "sr_block"))
        *arg_val = FAL_NROM_TCP_SR_BLOCK_CMD;
    else if (!strcasecmp(cmd_str, "sf_block"))
        *arg_val = FAL_NROM_TCP_SF_BLOCK_CMD;
    else if (!strcasecmp(cmd_str, "sar_block"))
        *arg_val = FAL_NROM_TCP_SAR_BLOCK_CMD;
    else if (!strcasecmp(cmd_str, "rst_scan"))
        *arg_val = FAL_NROM_TCP_RST_SCAN_CMD;
    else if (!strcasecmp(cmd_str, "rst_with_data"))
        *arg_val = FAL_NROM_TCP_RST_WITH_DATA_CMD;
    else if (!strcasecmp(cmd_str, "fa_block"))
        *arg_val = FAL_NROM_TCP_FA_BLOCK_CMD;
    else if (!strcasecmp(cmd_str, "pa_block"))
        *arg_val = FAL_NROM_TCP_PA_BLOCK_CMD;
    else if (!strcasecmp(cmd_str, "ua_block"))
        *arg_val = FAL_NROM_TCP_UA_BLOCK_CMD;
    else if (!strcasecmp(cmd_str, "invalid_chksum"))
        *arg_val = FAL_NROM_TCP_INVALID_CHKSUM_CMD;
    else if (!strcasecmp(cmd_str, "invalid_urgptr"))
        *arg_val = FAL_NROM_TCP_INVALID_URGPTR_CMD;
    else if (!strcasecmp(cmd_str, "invalid_opts"))
        *arg_val = FAL_NROM_TCP_INVALID_OPTIONS_CMD;
    else
    {
        dprintf("UNKNOWN VALUE");
        return SW_BAD_VALUE;
    }

    return SW_OK;
}


sw_error_t
cmd_data_check_sec_udp(char *cmd_str, a_uint32_t * arg_val, a_uint32_t size)
{
    if (cmd_str == NULL)
        return SW_BAD_PARAM;

    if (!strcasecmp(cmd_str, "blat"))
        *arg_val = FAL_NROM_UDP_BLAT_CMD;
    else if (!strcasecmp(cmd_str, "invalid_len"))
        *arg_val = FAL_NROM_UDP_INVALID_LEN_CMD;
    else if (!strcasecmp(cmd_str, "invalid_chksum"))
        *arg_val = FAL_NROM_UDP_INVALID_CHKSUM_CMD;
    else
    {
        dprintf("UNKNOWN VALUE");
        return SW_BAD_VALUE;
    }

    return SW_OK;
}

sw_error_t
cmd_data_check_sec_icmp4(char *cmd_str, a_uint32_t * arg_val, a_uint32_t size)
{
    if (cmd_str == NULL)
        return SW_BAD_PARAM;

    if (!strcasecmp(cmd_str, "ping_pl_exceed"))
        *arg_val = FAL_NROM_ICMP4_PING_PL_EXCEED_CMD;
    else if (!strcasecmp(cmd_str, "ping_frag"))
        *arg_val = FAL_NROM_ICMP4_PING_FRAG_CMD;
    else if (!strcasecmp(cmd_str, "ping_max_pl"))
        *arg_val = FAL_NROM_ICMP4_PING_MAX_PL_VALUE;
    else
    {
        //dprintf("input error");
        return SW_BAD_VALUE;
    }

    return SW_OK;
}

sw_error_t
cmd_data_check_sec_icmp6(char *cmd_str, a_uint32_t * arg_val, a_uint32_t size)
{
    if (cmd_str == NULL)
        return SW_BAD_PARAM;

    if (!strcasecmp(cmd_str, "ping_pl_exceed"))
        *arg_val = FAL_NROM_ICMP6_PING_PL_EXCEED_CMD;
    else if (!strcasecmp(cmd_str, "ping_frag"))
        *arg_val = FAL_NROM_ICMP6_PING_FRAG_CMD;
    else if (!strcasecmp(cmd_str, "ping_max_pl"))
        *arg_val = FAL_NROM_ICMP6_PING_MAX_PL_VALUE;
    else
    {
        //dprintf("input error");
        return SW_BAD_VALUE;
    }

    return SW_OK;
}

sw_error_t
cmd_data_check_l3_parser(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_l3_excep_parser_ctrl entry;

    aos_mem_zero(&entry, sizeof (fal_l3_excep_parser_ctrl));

    do
    {
        cmd = get_sub_cmd("small ttl", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: small ttl value\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.small_ttl),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: small ttl value\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("small hop limit", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: small hop limit value\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.small_hop_limit),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: small hop limit value\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    *(fal_l3_excep_parser_ctrl *)val = entry;
    return SW_OK;

}

sw_error_t
cmd_data_check_l4_parser(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_l4_excep_parser_ctrl entry;

    aos_mem_zero(&entry, sizeof (fal_l4_excep_parser_ctrl));

    do
    {
        cmd = get_sub_cmd("tcp flags0", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: tcp flags value\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.tcp_flags[0]),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: tcp flags value\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("tcp flags0 mask", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: tcp flags mask value\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.tcp_flags_mask[0]),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: tcp flags maskvalue\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("tcp flags1", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: tcp flags value\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.tcp_flags[1]),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: tcp flags value\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("tcp flags1 mask", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: tcp flags mask value\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.tcp_flags_mask[1]),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: tcp flags maskvalue\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("tcp flags2", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: tcp flags value\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.tcp_flags[2]),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: tcp flags value\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("tcp flags2 mask", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: tcp flags mask value\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.tcp_flags_mask[2]),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: tcp flags maskvalue\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("tcp flags3", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: tcp flags value\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.tcp_flags[3]),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: tcp flags value\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("tcp flags3 mask", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: tcp flags mask value\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.tcp_flags_mask[3]),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: tcp flags maskvalue\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("tcp flags4", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: tcp flags value\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.tcp_flags[4]),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: tcp flags value\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("tcp flags4 mask", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: tcp flags mask value\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.tcp_flags_mask[4]),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: tcp flags maskvalue\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("tcp flags5", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: tcp flags value\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.tcp_flags[5]),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: tcp flags value\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("tcp flags5 mask", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: tcp flags mask value\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.tcp_flags_mask[5]),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: tcp flags maskvalue\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("tcp flags6", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: tcp flags value\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.tcp_flags[6]),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: tcp flags value\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("tcp flags6 mask", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: tcp flags mask value\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.tcp_flags_mask[6]),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: tcp flags maskvalue\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("tcp flags7", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: tcp flags value\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.tcp_flags[7]),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: tcp flags value\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("tcp flags7 mask", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: tcp flags mask value\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.tcp_flags_mask[7]),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: tcp flags maskvalue\n");
        }

    }
    while (talk_mode && (SW_OK != rv));


    *(fal_l4_excep_parser_ctrl *)val = entry;
    return SW_OK;

}

sw_error_t
cmd_data_check_exp_ctrl(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_l3_excep_ctrl_t entry;

    aos_mem_zero(&entry, sizeof (fal_l3_excep_ctrl_t));

    do
    {
        cmd = get_sub_cmd("exp cmd", "forward");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_maccmd(cmd, &(entry.cmd),
                                       sizeof (fal_fwd_cmd_t));
            if (SW_OK != rv)
                dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("de acce en", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: 0 for disable and 1 for enable\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.de_acce_en),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: 0 for disable and 1 for enable\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("l3 only en", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: 0 for disable and 1 for enable\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.l3_only_en),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: 0 for disable and 1 for enable\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("l2 only en", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: 0 for disable and 1 for enable\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.l2_only_en),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: 0 for disable and 1 for enable\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("l2 flow en", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: 0 for disable and 1 for enable\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.l2_flow_en),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: 0 for disable and 1 for enable\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("l3 flow en", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: 0 for disable and 1 for enable\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.l3_flow_en),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: 0 for disable and 1 for enable\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("multicast en", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: 0 for disable and 1 for enable\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.multicast_en),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: 0 for disable and 1 for enable\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    *(fal_l3_excep_ctrl_t *)val = entry;
    return SW_OK;
}

#endif
#ifdef IN_COSMAP
sw_error_t
cmd_data_check_remark_entry(char *info, void *val, a_uint32_t size)
{
    sw_error_t rv;
    fal_egress_remark_table_t *pEntry = (fal_egress_remark_table_t *)val;
    a_uint32_t tmp;

    memset(pEntry, 0, sizeof(fal_egress_remark_table_t));

    /* get remark_dscp */
    rv = __cmd_data_check_complex("remark dscp", "enable",
                        "usage: <enable/disable>\n",
                        cmd_data_check_enable, &(pEntry->remark_dscp),
                        sizeof(a_bool_t));
    if (rv)
        return rv;

    /* get remark_up */
    rv = __cmd_data_check_complex("remark up", "enable",
                        "usage: <enable/disable>\n",
                        cmd_data_check_enable, &(pEntry->remark_up),
                        sizeof(a_bool_t));
    if (rv)
        return rv;

    /* get remark_dei */
    rv = __cmd_data_check_complex("remark dei", "enable",
                        "usage: <enable/disable>\n",
                        cmd_data_check_enable, &(pEntry->remark_dei),
                        sizeof(a_bool_t));
    if (rv)
        return rv;

    /* get g_dscp */
    rv = __cmd_data_check_range("green dscp", NULL,
                        "usage: the range is 0 -- 63\n",
                        cmd_data_check_integer, &tmp, 63, 0);
    if (rv)
        return rv;
    pEntry->g_dscp = tmp;

    /* get y_dscp */
    rv = __cmd_data_check_range("yellow dscp", NULL,
                        "usage: the range is 0 -- 63\n",
                        cmd_data_check_integer, &tmp, 63, 0);
    if (rv)
        return rv;
    pEntry->y_dscp = tmp;

    /* get g_up */
    rv = __cmd_data_check_range("green up", NULL,
                        "usage: the range is 0 -- 63\n",
                        cmd_data_check_integer, &tmp, 7, 0);
    if (rv)
        return rv;
    pEntry->g_up = tmp;

    /* get y_up */
    rv = __cmd_data_check_range("yellow up", NULL,
                        "usage: the range is 0 -- 63\n",
                        cmd_data_check_integer, &tmp, 7, 0);
    if (rv)
        return rv;
    pEntry->y_up = tmp;

    /* get g_dei */
    rv = __cmd_data_check_range("green dei", NULL,
                        "usage: the range is 0 -- 1\n",
                        cmd_data_check_integer, &tmp, 1, 0);
    if (rv)
        return rv;
    pEntry->g_dei = tmp;

    /* get y_dei */
    rv = __cmd_data_check_range("yellow dei", NULL,
                        "usage: the range is 0 -- 1\n",
                        cmd_data_check_integer, &tmp, 1, 0);
    if (rv)
        return rv;
    pEntry->y_dei = tmp;

/*
    dprintf("remark_dscp=%d, remark_up=%d, g_dscp=%d, y_dscp=%d\n",
            pEntry->remark_dscp,
            pEntry->remark_up,
            pEntry->g_dscp,
            pEntry->y_dscp);

    *(fal_egress_remark_table_t *) val = entry;
*/
    return SW_OK;
}
#endif
#ifdef IN_IP
sw_error_t
cmd_data_check_default_route_entry(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_default_route_t entry;

    aos_mem_zero(&entry, sizeof (fal_intf_mac_entry_t));

    do
    {
        cmd = get_sub_cmd("entry valid", "0");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: 0 for invalid and 1 for valid \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.valid), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: 0 for invalid and 1 for valid \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("vrf id", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: VRF id\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.vrf_id), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: VRF id\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("ip version", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: 0 for ipv4 and 1 for ipv6 \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.ip_version), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: 0 for ipv4 and 1 for ipv6 \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("route type", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {

            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: 0 for arp and 1 for wcmp \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.droute_type), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: 0 for arp and 1 for wcmp \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("index", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {

            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: index for arp entry or wcmp entry \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.index), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: index for arp entry or wcmp entry \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    *(fal_default_route_t *)val = entry;
    return SW_OK;
}

sw_error_t
cmd_data_check_host_route_entry(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_host_route_t entry;

    aos_mem_zero(&entry, sizeof (fal_intf_mac_entry_t));

    do
    {
        cmd = get_sub_cmd("entry valid", "0");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: 0 for invalid and 1 for valid \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.valid), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: 0 for invalid and 1 for valid \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("vrf id", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: VRF id\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.vrf_id), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: VRF id\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("ip version", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: 0 for ipv4 and 1 for ipv6 \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.ip_version), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: 0 for ipv4 and 1 for ipv6 \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    if (entry.ip_version == 0) /*IPv4*/
    {
        rv = __cmd_data_check_complex("ip4 addr", NULL,
                            "usage: the format is xx.xx.xx.xx \n",
                            cmd_data_check_ip4addr, &(entry.route_addr.ip4_addr),
                            4);
        if (rv)
            return rv;
    }
    else if (entry.ip_version == 1) /*IPv6*/
    {
        rv = __cmd_data_check_complex("ip6 addr", NULL,
                            "usage: the format is xxxx::xxxx \n",
                            cmd_data_check_ip6addr, &(entry.route_addr.ip6_addr),
                            16);
        if (rv)
            return rv;
    }
    else
    {
        return SW_BAD_VALUE;
    }

    do
    {
        cmd = get_sub_cmd("prefix_length", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: prefix length for this host route, 0~31 for ipv4 and 0~127 for ipv6 \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.prefix_length), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: prefix length for this host route, 0~31 for ipv4 and 0~127 for ipv6 \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    *(fal_host_route_t *)val = entry;
    return SW_OK;
}

sw_error_t
cmd_data_check_ip4_rfs_entry(char *cmd_str, void * val, a_uint32_t size)
{
	char *cmd;
	a_uint32_t tmp;
	sw_error_t rv;
	fal_ip4_rfs_t entry;

	aos_mem_zero(&entry, sizeof (fal_ip4_rfs_t));

	rv = __cmd_data_check_complex("mac addr", NULL,
                        "usage: the format is xx-xx-xx-xx-xx-xx \n",
                        cmd_data_check_macaddr, &(entry.mac_addr),
                        sizeof (fal_mac_addr_t));
    if (rv)
        return rv;

	rv = __cmd_data_check_complex("ip4 addr", NULL,
                            "usage: the format is xx.xx.xx.xx \n",
                            cmd_data_check_ip4addr, &(entry.ip4_addr),
                            4);
    if (rv)
        return rv;

	rv = __cmd_data_check_complex("vid", "0",
                        "usage: the format is xx \n",
                        cmd_data_check_uint32, &(entry.vid),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

	rv = __cmd_data_check_complex("loadbalance", "0",
                        "usage: the format is xx \n",
                        cmd_data_check_uint32, &tmp,
                        sizeof (a_uint32_t));
    if (rv)
        return rv;
	entry.load_balance = tmp;
	*(fal_ip4_rfs_t *)val = entry;
	return SW_OK;
}
#endif
#if 0
sw_error_t
cmd_data_check_fdb_rfs(char *cmd_str, void * val, a_uint32_t size)
{
	char *cmd;
	a_uint32_t tmp;
	sw_error_t rv;
	fal_fdb_rfs_t entry;

	aos_mem_zero(&entry, sizeof (fal_fdb_rfs_t));

	rv = __cmd_data_check_complex("mac addr", NULL,
                        "usage: the format is xx-xx-xx-xx-xx-xx \n",
                        cmd_data_check_macaddr, &(entry.addr),
                        sizeof (fal_mac_addr_t));
    if (rv)
        return rv;

	rv = __cmd_data_check_complex("fid", NULL,
                            "usage: the format is xx\n",
                            cmd_data_check_uint32, &tmp,
                            sizeof (a_uint32_t));
    if (rv)
        return rv;
	entry.fid = tmp;

	rv = __cmd_data_check_complex("loadbalance", "0",
                        "usage: the format is xx \n",
                        cmd_data_check_uint32, &tmp,
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

	entry.load_balance = tmp;

	*(fal_fdb_rfs_t *)val = entry;
	return SW_OK;
}
#endif
#ifdef IN_NAT
sw_error_t
cmd_data_check_flow_cookie(char *cmd_str, void * val, a_uint32_t size)
{
	char *cmd;
	a_uint32_t tmp;
	sw_error_t rv;
	fal_flow_cookie_t entry;

	aos_mem_zero(&entry, sizeof (fal_flow_cookie_t));

	rv = __cmd_data_check_complex("proto", "0",
                        "usage: the format is xx \n",
                        cmd_data_check_uint32, &(entry.proto),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

	rv = __cmd_data_check_complex("src addr", NULL,
                            "usage: the format is xx.xx.xx.xx \n",
                            cmd_data_check_ip4addr, &(entry.src_addr),
                            4);
    if (rv)
        return rv;

	rv = __cmd_data_check_complex("dst addr", NULL,
                            "usage: the format is xx.xx.xx.xx \n",
                            cmd_data_check_ip4addr, &(entry.dst_addr),
                            4);
    if (rv)
        return rv;

	rv = __cmd_data_check_complex("src port", "0",
                        "usage: the format is xx \n",
                        cmd_data_check_uint32, &(entry.src_port),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

	rv = __cmd_data_check_complex("dst port", "0",
                        "usage: the format is xx \n",
                        cmd_data_check_uint32, &(entry.dst_port),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

	rv = __cmd_data_check_complex("flow cookie", "0",
                        "usage: the format is xx \n",
                        cmd_data_check_uint32, &(entry.flow_cookie),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;


	*(fal_flow_cookie_t *)val = entry;
	return SW_OK;
}

sw_error_t
cmd_data_check_flow_rfs(char *cmd_str, void * val, a_uint32_t size)
{
	char *cmd;
	a_uint32_t tmp;
	sw_error_t rv;
	fal_flow_rfs_t entry;

	aos_mem_zero(&entry, sizeof (fal_flow_cookie_t));

	rv = __cmd_data_check_complex("proto", "0",
                        "usage: the format is xx \n",
                        cmd_data_check_uint32, &(entry.proto),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

	rv = __cmd_data_check_complex("src addr", NULL,
                            "usage: the format is xx.xx.xx.xx \n",
                            cmd_data_check_ip4addr, &(entry.src_addr),
                            4);
    if (rv)
        return rv;

	rv = __cmd_data_check_complex("dst addr", NULL,
                            "usage: the format is xx.xx.xx.xx \n",
                            cmd_data_check_ip4addr, &(entry.dst_addr),
                            4);
    if (rv)
        return rv;

	rv = __cmd_data_check_complex("src port", "0",
                        "usage: the format is xx \n",
                        cmd_data_check_uint32, &(entry.src_port),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

	rv = __cmd_data_check_complex("dst port", "0",
                        "usage: the format is xx \n",
                        cmd_data_check_uint32, &(entry.dst_port),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

	rv = __cmd_data_check_complex("flow rfs", "0",
                        "usage: the format is xx \n",
                        cmd_data_check_uint32, &tmp,
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

	entry.load_balance = tmp;


	*(fal_flow_rfs_t *)val = entry;
	return SW_OK;
}
#endif
#ifdef IN_IP
sw_error_t
cmd_data_check_ip_global(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_ip_global_cfg_t entry;

    aos_mem_zero(&entry, sizeof (fal_ip_global_cfg_t));

    do
    {
        cmd = get_sub_cmd("mru fail action", "forward");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_maccmd(cmd, &(entry.mru_fail_action),
                                       sizeof (fal_fwd_cmd_t));
            if (SW_OK != rv)
                dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("mru deaclr", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.mru_deacclr_en),
                                       sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("mtu fail action", "forward");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_maccmd(cmd, &(entry.mtu_fail_action),
                                       sizeof (fal_fwd_cmd_t));
            if (SW_OK != rv)
                dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("mtu deaclr", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.mtu_deacclr_en),
                                       sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("mtu nonfrag fail action", "forward");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_maccmd(cmd, &(entry.mtu_nonfrag_fail_action),
                                       sizeof (fal_fwd_cmd_t));
            if (SW_OK != rv)
                dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("mtu nanfrag deaclr", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.mtu_df_deacclr_en),
                                       sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("prefix bc action", "forward");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_maccmd(cmd, &(entry.prefix_bc_action),
                                       sizeof (fal_fwd_cmd_t));
            if (SW_OK != rv)
                dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("prefix bc deaclr", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.prefix_deacclr_en),
                                       sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("icmp rdt action", "forward");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_maccmd(cmd, &(entry.icmp_rdt_action),
                                       sizeof (fal_fwd_cmd_t));
            if (SW_OK != rv)
                dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("icmp rdt deaclr", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.icmp_rdt_deacclr_en),
                                       sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("hash mode 0", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: hash mode\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.hash_mode_0),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: 0 for disable and 1 for enable\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("hash mode 1", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: hash mode\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.hash_mode_1),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: 0 for disable and 1 for enable\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    *(fal_ip_global_cfg_t *)val = entry;
    return SW_OK;

}

sw_error_t
cmd_data_check_ip_mcmode(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_mc_mode_cfg_t entry;

    aos_mem_zero(&entry, sizeof (fal_mc_mode_cfg_t));

    do
    {
        cmd = get_sub_cmd("ipv4 mc en", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.l2_ipv4_mc_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("ipv4 mc mode", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: mc mode \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.l2_ipv4_mc_mode), sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: mc mode \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("ipv6 mc en", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.l2_ipv6_mc_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("ipv6 mc mode", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: mc mode \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.l2_ipv6_mc_mode), sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: mc mode \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    *(fal_mc_mode_cfg_t *)val = entry;
    return SW_OK;
}

sw_error_t
cmd_data_check_ip_portmac(char *cmd_str, void * val, a_uint32_t size)
{
	char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_macaddr_entry_t entry;

    aos_mem_zero(&entry, sizeof (fal_macaddr_entry_t));

    do
    {
        cmd = get_sub_cmd("entry valid", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: 1 for invalid and 1 for valid \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.valid), sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: 1 for invalid and 1 for valid \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    rv = __cmd_data_check_complex("mac addr", NULL,
                        "usage: the format is xx-xx-xx-xx-xx-xx \n",
                        cmd_data_check_macaddr, &(entry.mac_addr),
                        sizeof (fal_mac_addr_t));
    if (rv)
		return rv;

    *(fal_macaddr_entry_t *)val = entry;
    return SW_OK;
}

sw_error_t
cmd_data_check_ip_pub(char *cmd_str, void * val, a_uint32_t size)
{
	char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_ip_pub_addr_t entry;

    aos_mem_zero(&entry, sizeof (fal_ip_pub_addr_t));

    rv = __cmd_data_check_complex(" dnat_ip", NULL,
                            "usage: the format is xx.xx.xx.xx \n",
                            cmd_data_check_ip4addr, &(entry.pub_ip_addr),
                            4);
    if (rv)
        return rv; 

    *(fal_ip_pub_addr_t *)val = entry;
    return SW_OK;
}

sw_error_t
cmd_data_check_ip_sg(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_sg_cfg_t entry;

    aos_mem_zero(&entry, sizeof (fal_sg_cfg_t));

    do
    {
        cmd = get_sub_cmd("ipv4 sg en", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.ipv4_sg_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("ipv4 sg vio cmd", "forward");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_maccmd(cmd, &(entry.ipv4_sg_vio_action),
                                       sizeof (fal_fwd_cmd_t));
            if (SW_OK != rv)
                dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("ipv4 sg port en", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.ipv4_sg_port_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("ipv4 sg svlan en", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.ipv4_sg_svlan_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("ipv4 sg cvlan en", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.ipv4_sg_cvlan_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("ipv4 src unk cmd", "forward");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_maccmd(cmd, &(entry.ipv4_src_unk_action),
                                       sizeof (fal_fwd_cmd_t));
            if (SW_OK != rv)
                dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("ipv6 sg en", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.ipv6_sg_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("ipv6 sg vio cmd", "forward");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_maccmd(cmd, &(entry.ipv6_sg_vio_action),
                                       sizeof (fal_fwd_cmd_t));
            if (SW_OK != rv)
                dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("ipv6 sg port en", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.ipv6_sg_port_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("ipv6 sg svlan en", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.ipv6_sg_svlan_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("ipv6 sg cvlan en", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.ipv6_sg_cvlan_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("ipv6 src unk cmd", "forward");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_maccmd(cmd, &(entry.ipv6_src_unk_action),
                                       sizeof (fal_fwd_cmd_t));
            if (SW_OK != rv)
                dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    *(fal_sg_cfg_t *)val = entry;
    return SW_OK;
}

sw_error_t
cmd_data_check_nexthop(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_ip_nexthop_t entry;

    aos_mem_zero(&entry, sizeof (fal_ip_nexthop_t));

    do
    {
        cmd = get_sub_cmd("type", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: 0 l3 and 1 for vp \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.type), sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: 0 for invalid and 1 for valid\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    if (entry.type == 0) {
		do
    		{
		        cmd = get_sub_cmd("vsi", "0");
		        SW_RTN_ON_NULL_PARAM(cmd);

		        if (!strncasecmp(cmd, "quit", 4))
		        {
		            return SW_BAD_VALUE;
		        }
		        else if (!strncasecmp(cmd, "help", 4))
		        {
		            dprintf("usage: vsi \n");
		            rv = SW_BAD_VALUE;
		        }
		        else
		        {
		            rv = cmd_data_check_uint8(cmd, &(entry.vsi), sizeof (a_uint8_t));
		            if (SW_OK != rv)
		                dprintf("usage: vsi\n");
		        }
    		}
    		while (talk_mode && (SW_OK != rv));
    } else {
    		do
    		{
		        cmd = get_sub_cmd("port", "0");
		        SW_RTN_ON_NULL_PARAM(cmd);

		        if (!strncasecmp(cmd, "quit", 4))
		        {
		            return SW_BAD_VALUE;
		        }
		        else if (!strncasecmp(cmd, "help", 4))
		        {
		            dprintf("usage: port \n");
		            rv = SW_BAD_VALUE;
		        }
		        else
		        {
		            rv = cmd_data_check_uint8(cmd, &(entry.port), sizeof (a_uint8_t));
		            if (SW_OK != rv)
		                dprintf("usage: port\n");
		        }
    		}
    		while (talk_mode && (SW_OK != rv));
    }

    do
    {
        cmd = get_sub_cmd("post l3 if", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: post l3 if \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.if_index), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: post l3 if index\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("ip to me", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.ip_to_me_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("pubip index", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: pub index \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.pub_ip_index), sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: pub index\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("stag fmt", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: stag fmt \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.stag_fmt), sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: stag fmt\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("svid", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: svid \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.svid), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: svid\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("ctag fmt", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: ctag fmt \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.ctag_fmt), sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: ctag fmt\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("cvid", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: cvid \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.cvid), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: cvid\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    rv = __cmd_data_check_complex("mac addr", NULL,
    		"usage: the format is xx-xx-xx-xx-xx-xx \n",
    		cmd_data_check_macaddr, &(entry.mac_addr),
    		sizeof (fal_mac_addr_t));
    if (rv)
    	return rv;

    rv = __cmd_data_check_complex(" dnat_ip", NULL,
                            "usage: the format is xx.xx.xx.xx \n",
                            cmd_data_check_ip4addr, &(entry.dnat_ip),
                            4);
    if (rv)
        return rv;   
	

    *(fal_ip_nexthop_t *)val = entry;
    return SW_OK;
}

sw_error_t
cmd_data_check_vsi_intf(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_intf_id_t entry;

    aos_mem_zero(&entry, sizeof (fal_intf_id_t));

    do
    {
        cmd = get_sub_cmd("l3 if valid", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: 0 for invalid and 1 for valid \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.l3_if_valid), sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: 0 for invalid and 1 for valid\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("l3 if index", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: l3 if index \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.l3_if_index), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: l3 if index\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    *(fal_intf_id_t *)val = entry;
    return SW_OK;
}

sw_error_t
cmd_data_check_intf(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_intf_entry_t entry;

    aos_mem_zero(&entry, sizeof (fal_intf_entry_t));

    do
    {
        cmd = get_sub_cmd("mru", "0x5dc");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: mru \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.mru), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: mru \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("mtu", "0x5dc");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: mtu \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.mtu), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: mtu \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("ttl dec bypass", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.ttl_dec_bypass_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("ipv4 uc route en", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.ipv4_uc_route_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("ipv6 uc route en", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.ipv6_uc_route_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("icmp trigger en", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.icmp_trigger_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("ttl exceed cmd", "forward");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_maccmd(cmd, &(entry.ttl_exceed_action),
                                       sizeof (fal_fwd_cmd_t));
            if (SW_OK != rv)
                dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("ttl exceed deaclr", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.ttl_exceed_deacclr_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("macaddr bitmap", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: mac bitmap \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.mac_addr_bitmap), sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: mac bitmap \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    rv = __cmd_data_check_complex("macaddr", NULL,
    		"usage: the format is xx-xx-xx-xx-xx-xx \n",
    		cmd_data_check_macaddr, &(entry.mac_addr),
    		sizeof (fal_mac_addr_t));
    if (rv)
    	return rv;

    *(fal_intf_entry_t *)val = entry;
    return SW_OK;
}

sw_error_t
cmd_data_check_network_route(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_network_route_entry_t entry;

    aos_mem_zero(&entry, sizeof (fal_network_route_entry_t));

    do
    {
        cmd = get_sub_cmd("type", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: 0 for ipv4 and 1 for ipv6 \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.type), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: 0 for disable and 1 for enable \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    if (entry.type == 0) /*IPv4*/
    {
        rv = __cmd_data_check_complex("ip4 addr", NULL,
                        "usage: the format is xx.xx.xx.xx \n",
                        cmd_data_check_ip4addr, &(entry.route_addr.ip4_addr),
                        4);
	 if (rv)
	 	return rv;
    }
    else if (entry.type == 1) /*IPv6*/
    {
	  rv = __cmd_data_check_complex("ip6 addr", NULL,
                        "usage: the format is xxxx::xxxx \n",
                        cmd_data_check_ip6addr, &(entry.route_addr.ip6_addr),
                        16);
	 if (rv)
	 	return rv;

    }
    else
    {
        return SW_BAD_VALUE;
    }

     if (entry.type == 0) /*IPv4*/
    {
        rv = __cmd_data_check_complex("ip4 addr mask", NULL,
                            "usage: the format is xx.xx.xx.xx \n",
                            cmd_data_check_ip4addr, &(entry.route_addr_mask.ip4_addr_mask),
                            4);
        if (rv)
            return rv;
    }
    else if (entry.type == 1) /*IPv6*/
    {
        rv = __cmd_data_check_complex("ip6 addr mask", NULL,
                            "usage: the format is xxxx::xxxx \n",
                            cmd_data_check_ip6addr, &(entry.route_addr_mask.ip6_addr_mask),
                            16);
        if (rv)
            return rv;
    }
    else
    {
        return SW_BAD_VALUE;
    }

    do
    {
        cmd = get_sub_cmd("fwd cmd", "forward");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_maccmd(cmd, &(entry.action),
                                       sizeof (fal_fwd_cmd_t));
            if (SW_OK != rv)
                dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("dst info", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: Dst info \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.dst_info), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: dst info \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("lan wan", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: 0 for lan and 1 for wan \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.lan_wan), sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: 0 for lan and 1 for wan \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    *(fal_network_route_entry_t *)val = entry;
    return SW_OK;
}



sw_error_t
cmd_data_check_arp_sg(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_arp_sg_cfg_t entry;

    aos_mem_zero(&entry, sizeof (fal_arp_sg_cfg_t));

    do
    {
        cmd = get_sub_cmd("arp sg en", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.ipv4_arp_sg_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("arp sg vio cmd", "forward");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_maccmd(cmd, &(entry.ipv4_arp_sg_vio_action),
                                       sizeof (fal_fwd_cmd_t));
            if (SW_OK != rv)
                dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("arp sg port en", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.ipv4_arp_sg_port_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("arp sg svlan en", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.ipv4_arp_sg_svlan_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("arp sg cvlan en", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.ipv4_arp_sg_cvlan_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("arp sg unk cmd", "forward");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_maccmd(cmd, &(entry.ipv4_arp_src_unk_action),
                                       sizeof (fal_fwd_cmd_t));
            if (SW_OK != rv)
                dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("nd sg en", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.ip_nd_sg_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("nd sg vio cmd", "forward");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_maccmd(cmd, &(entry.ip_nd_sg_vio_action),
                                       sizeof (fal_fwd_cmd_t));
            if (SW_OK != rv)
                dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("nd sg port en", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.ip_nd_sg_port_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("nd sg svlan en", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.ip_nd_sg_svlan_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("nd sg cvlan en", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.ip_nd_sg_cvlan_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("nd sg unk cmd", "forward");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_maccmd(cmd, &(entry.ip_nd_src_unk_action),
                                       sizeof (fal_fwd_cmd_t));
            if (SW_OK != rv)
                dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    *(fal_arp_sg_cfg_t *)val = entry;
    return SW_OK;
}
sw_error_t
cmd_data_check_ip6_rfs_entry(char *cmd_str, void * val, a_uint32_t size)
{
	char *cmd;
	a_uint32_t tmp;
	sw_error_t rv;
	fal_ip6_rfs_t entry;

	aos_mem_zero(&entry, sizeof (fal_ip4_rfs_t));

	rv = __cmd_data_check_complex("mac addr", NULL,
                        "usage: the format is xx-xx-xx-xx-xx-xx \n",
                        cmd_data_check_macaddr, &(entry.mac_addr),
                        sizeof (fal_mac_addr_t));
    if (rv)
        return rv;

	rv = __cmd_data_check_complex("ip6 addr", NULL,
                            "usage: the format is xxxx::xxxx \n",
                            cmd_data_check_ip6addr, &(entry.ip6_addr),
                            16);
    if (rv)
        return rv;

	rv = __cmd_data_check_complex("vid", "0",
                        "usage: the format is xx \n",
                        cmd_data_check_uint32, &(entry.vid),
                        sizeof (a_uint32_t));
    if (rv)
        return rv;

	rv = __cmd_data_check_complex("loadbalance", "0",
                        "usage: the format is xx \n",
                        cmd_data_check_uint32, &tmp,
                        sizeof (a_uint32_t));
    if (rv)
        return rv;
	entry.load_balance = tmp;

	*(fal_ip6_rfs_t *)val = entry;
	return SW_OK;
}
#endif

#ifdef IN_VSI
sw_error_t
cmd_data_check_newadr_lrn(char *cmd_str, void * val, a_uint32_t size)
{
	char *cmd;
	a_uint32_t tmp;
	sw_error_t rv;
	fal_vsi_newaddr_lrn_t entry;

	aos_mem_zero(&entry, sizeof (fal_vsi_newaddr_lrn_t));

	rv = __cmd_data_check_complex("lrn_en", "1",
                        "usage: 0-disable 1-enable\n",
                        cmd_data_check_uint32, &(entry.lrn_en),
                        sizeof (a_uint32_t));
	if (rv)
		return rv;

	rv = __cmd_data_check_complex("action", 0,
                            "usage: 0-Forward 1-Drop 2-Copy to CPU 3-redirect to CPU\n",
                            cmd_data_check_uint32, &(entry.action),
                            4);
	if (rv)
		return rv;

	*(fal_vsi_newaddr_lrn_t *)val = entry;
	return SW_OK;
}

sw_error_t
cmd_data_check_stamove(char *cmd_str, void * val, a_uint32_t size)
{
	char *cmd;
	a_uint32_t tmp;
	sw_error_t rv;
	fal_vsi_stamove_t entry;

	aos_mem_zero(&entry, sizeof (fal_vsi_stamove_t));

	rv = __cmd_data_check_complex("stamove", "1",
                        "usage: 0-disable 1-enable\n",
                        cmd_data_check_uint32, &(entry.stamove_en),
                        sizeof (a_uint32_t));
	if (rv)
		return rv;

	rv = __cmd_data_check_complex("action", 0,
                            "usage: 0-Forward 1-Drop 2-Copy to CPU 3-redirect to CPU\n",
                            cmd_data_check_uint32, &(entry.action),
                            4);
	if (rv)
		return rv;

	*(fal_vsi_stamove_t *)val = entry;
	return SW_OK;
}
sw_error_t
cmd_data_check_vsi_member(char *cmd_str, void * val, a_uint32_t size)
{
	char *cmd;
	a_uint32_t tmp;
	sw_error_t rv;
	fal_vsi_member_t entry;

	aos_mem_zero(&entry, sizeof (fal_vsi_member_t));

	rv = __cmd_data_check_complex("member_ports", 0,
                        "usage: Bit0-port0 Bit1-port1 ....\n",
                        cmd_data_check_pbmp, &(entry.member_ports),
                        sizeof (a_uint32_t));
	if (rv)
		return rv;

	rv = __cmd_data_check_complex("uuc_ports", 0,
                        "usage: Bit0-port0 Bit1-port1 ....\n",
                        cmd_data_check_pbmp, &(entry.uuc_ports),
                        sizeof (a_uint32_t));
	if (rv)
		return rv;

	rv = __cmd_data_check_complex("umc_ports", 0,
                        "usage: Bit0-port0 Bit1-port1 ....\n",
                        cmd_data_check_pbmp, &(entry.umc_ports),
                        sizeof (a_uint32_t));
	if (rv)
		return rv;

	rv = __cmd_data_check_complex("bc_ports", 0,
                        "usage: Bit0-port0 Bit1-port1 ....\n",
                        cmd_data_check_pbmp, &(entry.bc_ports),
                        sizeof (a_uint32_t));
	if (rv)
		return rv;

	*(fal_vsi_member_t *)val = entry;
	return SW_OK;
}
#endif

#ifdef IN_FLOW
sw_error_t
cmd_data_check_flow_global(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_flow_global_cfg_t entry;

    aos_mem_zero(&entry, sizeof (fal_flow_global_cfg_t));

    do
    {
        cmd = get_sub_cmd("src if check", "forward");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_maccmd(cmd, &(entry.src_if_check_action),
                                       sizeof (fal_fwd_cmd_t));
            if (SW_OK != rv)
                dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("src if deacclr", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.src_if_check_deacclr_en),
                                       sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("loop en", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.service_loop_en),
                                       sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("loop action", "forward");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_maccmd(cmd, &(entry.service_loop_action),
                                       sizeof (fal_fwd_cmd_t));
            if (SW_OK != rv)
                dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("loop deacclr", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.service_loop_deacclr_en),
                                       sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("flow deacclr", "forward");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_maccmd(cmd, &(entry.flow_deacclr_action),
                                       sizeof (fal_fwd_cmd_t));
            if (SW_OK != rv)
                dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("sync mismatch action", "forward");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_maccmd(cmd, &(entry.sync_mismatch_action),
                                       sizeof (fal_fwd_cmd_t));
            if (SW_OK != rv)
                dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("sync mismatch deacclr", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.sync_mismatch_deacclr_en),
                                       sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("hash mode 0", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: hash mode\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.hash_mode_0),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: 0 for disable and 1 for enable\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("hash mode 1", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: hash mode\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.hash_mode_1),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: 0 for disable and 1 for enable\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    *(fal_flow_global_cfg_t *)val = entry;
    return SW_OK;

}

sw_error_t
cmd_data_check_flow(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_flow_entry_t entry;

    aos_mem_zero(&entry, sizeof (fal_flow_entry_t));

    do
    {
        cmd = get_sub_cmd("entry_id", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: entry id \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.entry_id), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: entry id \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("entry_type", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: entry type \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.entry_type), sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: entry type \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("host_addr_type", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: host addr type \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.host_addr_type), sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: host addr type \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("host_addr_index", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: host addr index \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.host_addr_index), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: host addr index \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("protocol", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: protocol \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.protocol), sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: protocol \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("age", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: age \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.age), sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: age \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("src_intf_valid", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: src intf valid \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.src_intf_valid), sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: src intf valid \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("src_intf_index", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: src intf index \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.src_intf_index), sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: src intf index \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("fwd_type", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: fwd type \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.fwd_type), sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: fwd type \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    
    do
    {
        cmd = get_sub_cmd("snat_nexthop", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: snat nexthop \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.snat_nexthop), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: snat nexthop \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("snat_srcport", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: snat srcport \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.snat_srcport), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: snat srcport \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("dnat_nexthop", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: dnat nexthop \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.dnat_nexthop), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: dnat nexthop \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("dnat_dstport", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: dnat dstport \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.dnat_dstport), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: dnat dstport \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("route_nexthop", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: route nexthop \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.route_nexthop), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: route nexthop \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("port_valid", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: port valid \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.port_valid), sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: port valid \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("route_port", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: route port \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.route_port), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: route port \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("bridge_port", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: bridge port \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.bridge_port), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: bridge port \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("de_acce", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.deacclr_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("copy_tocpu", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.copy_tocpu_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("syn_toggle", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: sync toggle \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.syn_toggle), sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: sync toggle \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("pri_profile", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: pri profile \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.pri_profile), sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: pri profile \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("sevice_code", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: service code \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.sevice_code), sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: service code \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("ip_type", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: ip type \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.ip_type), sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: ip type \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("src_port", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: src port \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.src_port), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: src port \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("dst_port", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: dst port \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.dst_port), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: dst port \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    if (entry.entry_type & FAL_FLOW_IP4_5TUPLE_ADDR || entry.entry_type & FAL_FLOW_IP4_3TUPLE_ADDR) {
        rv = __cmd_data_check_complex("ip4 addr", NULL,
		"usage: the format is xx.xx.xx.xx \n",
		cmd_data_check_ip4addr, &(entry.flow_ip.ipv4),
		4);
        if (rv)
		return rv;
		
    } else if (entry.entry_type & FAL_FLOW_IP6_5TUPLE_ADDR || entry.entry_type & FAL_FLOW_IP6_3TUPLE_ADDR) {
        rv = __cmd_data_check_complex("ip6 addr", NULL,
		"usage: the format is xxxx::xxxx \n",
		cmd_data_check_ip6addr, &(entry.flow_ip.ipv6),
		16);
        if (rv)
		return rv;
    }

    do
    {
        cmd = get_sub_cmd("tree id", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: tree id \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.tree_id), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: tree id \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    *(fal_flow_entry_t *)val = entry;
    return SW_OK;
}

sw_error_t
cmd_data_check_flow_ctrl(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_flow_mgmt_t entry;

    aos_mem_zero(&entry, sizeof (fal_flow_mgmt_t));

    do
    {
        cmd = get_sub_cmd("miss action", "forward");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_maccmd(cmd, &(entry.miss_action),
                                       sizeof (fal_fwd_cmd_t));
            if (SW_OK != rv)
                dprintf("usage: <forward/drop/cpycpu/rdtcpu>\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("frag bypass", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.frag_bypass_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("tcpspec bypass", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.tcp_spec_bypass_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("all bypass", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.all_bypass_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("key sel", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: key sel \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.key_sel), sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: key sel \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    *(fal_flow_mgmt_t *)val = entry;
    return SW_OK;
}

sw_error_t
cmd_data_check_flow_age(char *cmd_str, void * val, a_uint32_t size)
{
	char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_flow_age_timer_t entry;

    aos_mem_zero(&entry, sizeof (fal_flow_age_timer_t));

    do
    {
        cmd = get_sub_cmd("age time", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: age time \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.age_time), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: age time \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("age unit", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: age unit \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.unit), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: age unit \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    *(fal_flow_age_timer_t *)val = entry;
    return SW_OK;
}

#endif

#ifdef IN_BM
sw_error_t
cmd_data_check_bm_static_thresh(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_bm_static_cfg_t entry;

    aos_mem_zero(&entry, sizeof (fal_bm_static_cfg_t));

    do
    {
        cmd = get_sub_cmd("max thresh", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: max thresh\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.max_thresh),
                                       sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: max thresh\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("resume offset", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: resume offset\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.resume_off),
                                       sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: resume offset\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    *(fal_bm_static_cfg_t *)val = entry;
    return SW_OK;
}

sw_error_t
cmd_data_check_bm_dynamic_thresh(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_bm_dynamic_cfg_t entry;

    aos_mem_zero(&entry, sizeof (fal_bm_dynamic_cfg_t));

    do
    {
        cmd = get_sub_cmd("weight", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: weight\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.weight),
                                       sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: weight\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("shared ceiling", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: shared ceiling\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.shared_ceiling),
                                       sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: shared ceiling\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("resume offset", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: resume offset\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.resume_off),
                                       sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: resume offset\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("resume min thresh", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: resmue min thresh\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.resume_min_thresh),
                                       sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: resume min thresh\n");
        }

    }
    while (talk_mode && (SW_OK != rv));

    *(fal_bm_dynamic_cfg_t *)val = entry;
    return SW_OK;
}
#endif

#ifdef IN_QM
sw_error_t
cmd_data_check_u_qmap(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_ucast_queue_dest_t entry;

    aos_mem_zero(&entry, sizeof (fal_ucast_queue_dest_t));

    do
    {
        cmd = get_sub_cmd("src profile", "0");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: src profile \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.src_profile), sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: src profile \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("srv code en", "enable");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.service_code_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("srv code", "0");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: service code \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.service_code), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: service code \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("cpu code en", "enable");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.cpu_code_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("cpu code", "0");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: cpu code \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.cpu_code), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: cpu code \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("dst port", "0");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: dest port\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.dst_port), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: dst port \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    *(fal_ucast_queue_dest_t *)val = entry;
    return SW_OK;
}

sw_error_t
cmd_data_check_ac_static_thresh(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_ac_static_threshold_t entry;

    aos_mem_zero(&entry, sizeof (fal_ac_static_threshold_t));

    do
    {
        cmd = get_sub_cmd("color en", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.color_enable), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));


    do
    {
        cmd = get_sub_cmd("wred en", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.wred_enable), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("green max", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: green max \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.green_max), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: group id\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("green min off", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: green min offset \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.green_min_off), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: green min offset \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("yel max off", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: yel max offset \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.yel_max_off), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: green max offset \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("yel min off", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: yel min offset \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.yel_min_off), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: green min offset \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("red max off", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: red max offset \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.red_max_off), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: red max offset \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("red min off", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: red min offset \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.red_min_off), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: red min offset \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("green resume off", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: green resume offset \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.green_resume_off), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: green resume offset \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("yellow resume off", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: yellow resume offset \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.yel_resume_off), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: yellow resume offset \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("red resume off", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: red resume offset \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.red_resume_off), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: red resume offset \n");
        }
    }
    while (talk_mode && (SW_OK != rv));
	
    *(fal_ac_static_threshold_t *)val = entry;
    return SW_OK;
}

sw_error_t
cmd_data_check_ac_dynamic_thresh(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_ac_dynamic_threshold_t entry;

    aos_mem_zero(&entry, sizeof (fal_ac_dynamic_threshold_t));

    do
    {
        cmd = get_sub_cmd("color en", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.color_enable), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));


    do
    {
        cmd = get_sub_cmd("wred en", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.wred_enable), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("weight", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: weight \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint8(cmd, &(entry.shared_weight), sizeof (a_uint8_t));
            if (SW_OK != rv)
                dprintf("usage: weight\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("green min off", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: green min offset \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.green_min_off), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: green min offset \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("yel max off", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: yel max offset \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.yel_max_off), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: green max offset \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("yel min off", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: yel min offset \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.yel_min_off), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: green min offset \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("red max off", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: red max offset \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.red_max_off), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: red max offset \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("red min off", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: red min offset \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.red_min_off), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: red min offset \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("green resume off", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: green resume offset \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.green_resume_off), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: green resume offset \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("yellow resume off", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: yellow resume offset \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.yel_resume_off), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: yellow resume offset \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("red resume off", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: red resume offset \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.red_resume_off), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: red resume offset \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("ceiling", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: shared ceiling \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.ceiling), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: shared ceiling \n");
        }
    }
    while (talk_mode && (SW_OK != rv));
	
    *(fal_ac_dynamic_threshold_t *)val = entry;
    return SW_OK;
}

sw_error_t
cmd_data_check_ac_group_buff(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_ac_group_buffer_t entry;

    do
    {
        cmd = get_sub_cmd("prealloc buffer", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: prealloc buffer \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.prealloc_buffer), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: prealloc buffer \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("total buffer", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: total buffer \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint16(cmd, &(entry.total_buffer), sizeof (a_uint16_t));
            if (SW_OK != rv)
                dprintf("usage: total buffer \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    *(fal_ac_group_buffer_t *)val = entry;
    return SW_OK;
}

sw_error_t
cmd_data_check_ac_ctrl(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_ac_ctrl_t entry;

    do
    {
        cmd = get_sub_cmd("ac en", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.ac_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("ac fc en", "enable");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <enable/disable>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_enable(cmd, &(entry.ac_fc_en), sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <enable/disable>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    *(fal_ac_ctrl_t *)val = entry;
    return SW_OK;
}

sw_error_t
cmd_data_check_ac_obj(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    a_uint32_t tmp;
    sw_error_t rv;
    fal_ac_obj_t entry;

    do
    {
        cmd = get_sub_cmd("obj type", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: 0 for queue and 1 for group \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.type), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: 0 for queue and 1 for group \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("obj id", "0");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: obj id \n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.obj_id), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: obj id \n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    *(fal_ac_obj_t *)val = entry;
    return SW_OK;
}

#endif

#ifdef IN_SHAPER

sw_error_t
cmd_data_check_port_shaper_token_config(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    sw_error_t rv;
    a_bool_t bool = A_FALSE;
    fal_shaper_token_number_t entry;

    aos_mem_zero(&entry, sizeof (fal_shaper_token_number_t));

    do
    {
        cmd = get_sub_cmd("c_token_negative_en", "no");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {

            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <yes/no/y/n>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_confirm(cmd, A_FALSE, &(entry.c_token_number_negative_en),
                                        sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <yes/no/y/n>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("c_token_number", "0-0x3FFFFFFF");
	SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.c_token_number), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    *(fal_shaper_token_number_t *)val = entry;
    return SW_OK;
}


sw_error_t
cmd_data_check_shaper_token_config(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    sw_error_t rv;
    a_bool_t bool = A_FALSE;
    fal_shaper_token_number_t entry;

    aos_mem_zero(&entry, sizeof (fal_shaper_token_number_t));

    do
    {
        cmd = get_sub_cmd("c_token_negative_en", "no");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {

            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <yes/no/y/n>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_confirm(cmd, A_FALSE, &(entry.c_token_number_negative_en),
                                        sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <yes/no/y/n>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("c_token_number", "0-0x3FFFFFFF");
	SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.c_token_number), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("e_token_negative_en", "no");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {

            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <yes/no/y/n>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_confirm(cmd, A_FALSE, &(entry.e_token_number_negative_en),
                                        sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <yes/no/y/n>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));


    do
    {
        cmd = get_sub_cmd("e_token_number", "0-0x3FFFFFFF");
	SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.e_token_number), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    *(fal_shaper_token_number_t *)val = entry;
    return SW_OK;
}


sw_error_t
cmd_data_check_port_shaper_config(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    sw_error_t rv;
    a_bool_t bool = A_FALSE;
    fal_shaper_config_t entry;

    aos_mem_zero(&entry, sizeof (fal_shaper_config_t));

    do
    {
        cmd = get_sub_cmd("meter_unit", "0-1");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.meter_unit), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("c_shaper_enable", "no");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {

            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <yes/no/y/n>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_confirm(cmd, A_FALSE, &(entry.c_shaper_en),
                                        sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <yes/no/y/n>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("cir", "0");
	SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.cir), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("cbs", "0");
	SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.cbs), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

     do
    {
        cmd = get_sub_cmd("shaper_frame_mode", "0-2");
	SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.shaper_frame_mode), sizeof (fal_shaper_frame_mode_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    *(fal_shaper_config_t *)val = entry;
    return SW_OK;
}


sw_error_t
cmd_data_check_shaper_config(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    sw_error_t rv;
    a_bool_t bool = A_FALSE;
    fal_shaper_config_t entry;

    aos_mem_zero(&entry, sizeof (fal_shaper_config_t));

    do
    {
        cmd = get_sub_cmd("couple_enable", "no");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {

            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <yes/no/y/n>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_confirm(cmd, A_FALSE, &(entry.couple_en),
                                        sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <yes/no/y/n>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("meter_unit", "0-1");
	SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.meter_unit), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("c_shaper_enable", "no");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {

            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <yes/no/y/n>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_confirm(cmd, A_FALSE, &(entry.c_shaper_en),
                                        sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <yes/no/y/n>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("cir", "0");
	SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.cir), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("cbs", "0");
	SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.cbs), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("e_shaper_enable", "no");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {

            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <yes/no/y/n>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_confirm(cmd, A_FALSE, &(entry.e_shaper_en),
                                        sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <yes/no/y/n>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("eir", "0");
	SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.eir), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("ebs", "0");
	SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.ebs), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("shaper_frame_mode", "0-2");
	SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.shaper_frame_mode), sizeof (fal_shaper_frame_mode_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    *(fal_shaper_config_t *)val = entry;
    return SW_OK;
}

#endif

#ifdef IN_POLICER
sw_error_t
cmd_data_check_port_policer_config(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    sw_error_t rv;
    a_bool_t bool = A_FALSE;
    fal_policer_config_t entry;

    aos_mem_zero(&entry, sizeof (fal_policer_config_t));

    do
    {
        cmd = get_sub_cmd("meter_enable", "no");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {

            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <yes/no/y/n>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_confirm(cmd, A_FALSE, &(entry.meter_en),
                                        sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <yes/no/y/n>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("couple_enable", "no");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {

            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <yes/no/y/n>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_confirm(cmd, A_FALSE, &(entry.couple_en),
                                        sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <yes/no/y/n>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("color_mode", "0-1");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.color_mode), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("frame_type", "0-0x1f");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.frame_type), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("meter_mode", "0-1");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.meter_mode), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));


    do
    {
        cmd = get_sub_cmd("meter_unit", "0-1");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.meter_unit), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("cir", "0");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.cir), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("cbs", "0");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.cbs), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("eir", "0");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.eir), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("ebs", "0");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.ebs), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    *(fal_policer_config_t *)val = entry;
    return SW_OK;
}

sw_error_t
cmd_data_check_acl_policer_config(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    sw_error_t rv;
    a_bool_t bool = A_FALSE;
    fal_policer_config_t entry;

    aos_mem_zero(&entry, sizeof (fal_policer_config_t));

    do
    {
        cmd = get_sub_cmd("meter_enable", "no");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {

            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <yes/no/y/n>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_confirm(cmd, A_FALSE, &(entry.meter_en),
                                        sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <yes/no/y/n>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("couple_enable", "no");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {

            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <yes/no/y/n>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_confirm(cmd, A_FALSE, &(entry.couple_en),
                                        sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <yes/no/y/n>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("color_mode", "0-1");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.color_mode), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("meter_mode", "0-1");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.meter_mode), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));


    do
    {
        cmd = get_sub_cmd("meter_unit", "0-1");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.meter_unit), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("cir", "0");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.cir), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("cbs", "0");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.cbs), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("eir", "0");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.eir), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("ebs", "0");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.ebs), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    *(fal_policer_config_t *)val = entry;
    return SW_OK;
}

sw_error_t
cmd_data_check_policer_cmd_config(char *cmd_str, void * val, a_uint32_t size)
{
    char *cmd;
    sw_error_t rv;
    a_bool_t bool = A_FALSE;
    fal_policer_action_t entry;

    aos_mem_zero(&entry, sizeof (fal_policer_action_t));

    do
    {
        cmd = get_sub_cmd("yellow_priority_en", "no");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {

            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <yes/no/y/n>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_confirm(cmd, A_FALSE, &(entry.yellow_priority_en),
                                        sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <yes/no/y/n>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("yellow_drop_priority_en", "no");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {

            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <yes/no/y/n>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_confirm(cmd, A_FALSE, &(entry.yellow_drop_priority_en),
                                        sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <yes/no/y/n>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));


    do
    {
        cmd = get_sub_cmd("yellow_pcp_en", "no");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {

            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <yes/no/y/n>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_confirm(cmd, A_FALSE, &(entry.yellow_pcp_en),
                                        sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <yes/no/y/n>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("yellow_dei_en", "no");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {

            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <yes/no/y/n>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_confirm(cmd, A_FALSE, &(entry.yellow_dei_en),
                                        sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <yes/no/y/n>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("yellow_priority", "0-15");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.yellow_priority), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("yellow_drop_priority", "0-3");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.yellow_drop_priority), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("yellow_pcp", "0-7");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.yellow_pcp), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("yellow_dei", "0-1");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.yellow_dei), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

       do
    {
        cmd = get_sub_cmd("red_action", "0-1");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.red_action), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));


    do
    {
        cmd = get_sub_cmd("red_priority_en", "no");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {

            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <yes/no/y/n>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_confirm(cmd, A_FALSE, &(entry.red_priority_en),
                                        sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <yes/no/y/n>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("red_drop_priority_en", "no");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {

            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <yes/no/y/n>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_confirm(cmd, A_FALSE, &(entry.red_drop_priority_en),
                                        sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <yes/no/y/n>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("red_pcp_en", "no");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {

            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <yes/no/y/n>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_confirm(cmd, A_FALSE, &(entry.red_pcp_en),
                                        sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <yes/no/y/n>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("red_dei_en", "no");
        SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {

            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: <yes/no/y/n>\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_confirm(cmd, A_FALSE, &(entry.red_dei_en),
                                        sizeof (a_bool_t));
            if (SW_OK != rv)
                dprintf("usage: <yes/no/y/n>\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("red_priority", "0-15");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.red_priority), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("red_drop_priority", "0-3");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.red_drop_priority), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("red_pcp", "0-7");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.red_pcp), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    do
    {
        cmd = get_sub_cmd("red_dei", "0-1");
		SW_RTN_ON_NULL_PARAM(cmd);

        if (!strncasecmp(cmd, "quit", 4))
        {
            return SW_BAD_VALUE;
        }
        else if (!strncasecmp(cmd, "help", 4))
        {
            dprintf("usage: integer\n");
            rv = SW_BAD_VALUE;
        }
        else
        {
            rv = cmd_data_check_uint32(cmd, &(entry.red_dei), sizeof (a_uint32_t));
            if (SW_OK != rv)
                dprintf("usage: integer\n");
        }
    }
    while (talk_mode && (SW_OK != rv));

    *(fal_policer_action_t *)val = entry;
    return SW_OK;
}

#endif
