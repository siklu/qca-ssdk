/*
 * Copyright (c) 2012, The Linux Foundation. All rights reserved.
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
 * @defgroup fal_port_vlan FAL_PORT_VLAN
 * @{
 */
#ifndef _FAL_PORT_VLAN_H_
#define _FAL_PORT_VLAN_H_

#ifdef __cplusplus
extern "C" {
#endif                          /* __cplusplus */

#include "common/sw.h"
#include "fal/fal_type.h"

#if defined(SW_API_LOCK) && (!defined(HSL_STANDALONG))
#define FAL_PORTVLAN_API_LOCK
#define FAL_PORTVLAN_API_UNLOCK
#else
#define FAL_PORTVLAN_API_LOCK
#define FAL_PORTVLAN_API_UNLOCK
#endif

    /**
    @brief This enum defines 802.1q mode type.
    */
    typedef enum {
        FAL_1Q_DISABLE = 0, /**<  802.1q mode disbale, port based vlan */
        FAL_1Q_SECURE,      /**<   secure mode, packets which vid isn't in vlan table or source port isn't in vlan port member will be discarded.*/
        FAL_1Q_CHECK,       /**<   check mode, packets which vid isn't in vlan table will be discarded, packets which source port isn't in vlan port member will forward base on vlan port member*/
        FAL_1Q_FALLBACK,    /**<   fallback mode, packets which vid isn't in vlan table will forwarded base on port vlan, packet's which source port isn't in vlan port member will forward base on vlan port member.*/
        FAL_1Q_MODE_BUTT
    }
    fal_pt_1qmode_t;

    /**
    @brief This enum defines receive packets tagged mode.
    */
    typedef enum
    {
        FAL_INVLAN_ADMIT_ALL = 0,  /**<  receive all packets include tagged and untagged */
        FAL_INVLAN_ADMIT_TAGGED,   /**<  only receive tagged packets*/
        FAL_INVLAN_ADMIT_UNTAGGED, /**<  only receive untagged packets include priority tagged */
        FAL_INVLAN_MODE_BUTT
    } fal_pt_invlan_mode_t;

    /**
    @brief This enum defines vlan propagation mode.
    */
    typedef enum
    {
        FAL_VLAN_PROPAGATION_DISABLE = 0, /**<  vlan propagation disable */
        FAL_VLAN_PROPAGATION_CLONE,       /**<  vlan paopagation mode is clone */
        FAL_VLAN_PROPAGATION_REPLACE,     /**<  vlan paopagation mode is repalce */
        FAL_VLAN_PROPAGATION_MODE_BUTT
    } fal_vlan_propagation_mode_t;

    typedef enum
    {
        FAL_FRAMETYPE_ETHERNET = 0,
        FAL_FRAMETYPE_RFC_1024 = 1,
        FAL_FRAMETYPE_LLC_OTHER = 2,
        FAL_FRAMETYPE_ETHORRFC1024 = 3,
    } fal_frametype_t;

    typedef enum
    {
        FAL_VID_XLT_CMD_UNCHANGED = 0,
        FAL_VID_XLT_CMD_ADDORREPLACE = 1,
        FAL_VID_XLT_CMD_DELETE = 2,
    } fal_vid_xlt_cmd_t;


    /**
      @details  Fields description:

     o_vid - original vlan id
     s_vid - service vid id
     c_vid - custom vid id
     bi_dir - entry search direction
     forward_dir - entry search direction only be forward
     reverse_dir - entry search direction only be reverse
     o_vid_is_cvid - o_vid in entry means c_vid not s_vid
     s_vid_enable  - s_vid in entry is valid
     c_vid_enable  - c_vid in entry is valid
     one_2_one_vlan- the entry used for 1:1 vlan
    @brief This structure defines the vlan translation entry.

    */
    typedef struct
    {
        a_uint32_t o_vid;
        a_uint32_t s_vid;
        a_uint32_t c_vid;
        a_bool_t   bi_dir;       /**< lookup can be forward and reverse*/
        a_bool_t   forward_dir;  /**< lookup direction only can be from o_vid to s_vid and/or c_vid*/
        a_bool_t   reverse_dir;  /**< lookup direction only can be from s_vid and/or c_vid to o_vid*/
        a_bool_t   o_vid_is_cvid;
        a_bool_t   s_vid_enable;
        a_bool_t   c_vid_enable;
        a_bool_t   one_2_one_vlan;

        /*vsi check*/
        a_bool_t   vsi_valid;
        a_bool_t   vsi_enable;
        a_uint32_t   vsi;

        /*protocol and ethernet type*/
        a_bool_t   protocol_enable;
        a_uint16_t   protocol;
        a_bool_t   frmtype_enable;
        fal_frametype_t   frmtype;

        /*tagged mode, bit 0 for untagged, bit 1 for priority tagged and bit 2 for tagged*/
        a_uint8_t   s_tagged;
        a_uint8_t   c_tagged;

        /*cpcp and cdei*/
        a_bool_t   c_pcp_enable;
        a_uint8_t   c_pcp;
        a_bool_t   c_dei_enable;
        a_uint8_t   c_dei;
        /*spcp and sdei*/
        a_bool_t   s_pcp_enable;
        a_uint8_t   s_pcp;
        a_bool_t   s_dei_enable;
        a_uint8_t   s_dei;

        /*translation action*/
        /*counter action*/
        a_bool_t   counter_enable;
        a_uint8_t   counter_id;
        /*vsi action*/
        a_bool_t   vsi_action_enable;
        a_uint8_t   vsi_action;
        /*svid action*/
        fal_vid_xlt_cmd_t   svid_xlt_cmd;
        a_uint16_t   svid_xlt;
        /*cvid action*/
        fal_vid_xlt_cmd_t   cvid_xlt_cmd;
        a_uint16_t   cvid_xlt;
        /*swap svid and cvid action*/
        a_bool_t   swap_svid_cvid;
        /*spcp action*/
        a_bool_t   spcp_xlt_enable;
        a_uint8_t   spcp_xlt;
        /*cpcp action*/
        a_bool_t   cpcp_xlt_enable;
        a_uint8_t   cpcp_xlt;
        /*swap spcp and cpcp action*/
        a_bool_t   swap_spcp_cpcp;
        /*sdei action*/
        a_bool_t   sdei_xlt_enable;
        a_uint8_t   sdei_xlt;
        /*cdei action*/
        a_bool_t   cdei_xlt_enable;
        a_uint8_t   cdei_xlt;
        /*swap sdei and cdei action*/
        a_bool_t   swap_sdei_cdei;

	 /*port bitmap for this entry*/
	 a_uint32_t port_bitmap;
    } fal_vlan_trans_entry_t;

    /**
    @brief This enum defines qinq working mode.
    */
    typedef enum
    {
        FAL_QINQ_CTAG_MODE = 0,
        FAL_QINQ_STAG_MODE,
        FAL_QINQ_MODE_BUTT
    } fal_qinq_mode_t;

    /**
    @brief This enum defines port role in qinq mode.
    */
    typedef enum
    {
        FAL_QINQ_EDGE_PORT = 0,
        FAL_QINQ_CORE_PORT,
        FAL_QINQ_PORT_ROLE_BUTT
    } fal_qinq_port_role_t;


    sw_error_t
    fal_port_1qmode_set(a_uint32_t dev_id, fal_port_t port_id,
                        fal_pt_1qmode_t port_1qmode);


#ifndef IN_PORTVLAN_MINI
    sw_error_t
    fal_port_1qmode_get(a_uint32_t dev_id, fal_port_t port_id,
                        fal_pt_1qmode_t * pport_1qmode);

#endif

    sw_error_t
    fal_port_egvlanmode_set(a_uint32_t dev_id, fal_port_t port_id,
                            fal_pt_1q_egmode_t port_egvlanmode);


#ifndef IN_PORTVLAN_MINI
    sw_error_t
    fal_port_egvlanmode_get(a_uint32_t dev_id, fal_port_t port_id,
                            fal_pt_1q_egmode_t * pport_egvlanmode);

#endif

    sw_error_t
    fal_portvlan_member_add(a_uint32_t dev_id, fal_port_t port_id,
                            fal_port_t mem_port_id);



    sw_error_t
    fal_portvlan_member_del(a_uint32_t dev_id, fal_port_t port_id,
                            fal_port_t mem_port_id);



    sw_error_t
    fal_portvlan_member_update(a_uint32_t dev_id, fal_port_t port_id,
                               fal_pbmp_t mem_port_map);


#ifndef IN_PORTVLAN_MINI
    sw_error_t
    fal_portvlan_member_get(a_uint32_t dev_id, fal_port_t port_id,
                            fal_pbmp_t * mem_port_map);
#endif


    sw_error_t
    fal_port_default_vid_set(a_uint32_t dev_id, fal_port_t port_id,
                             a_uint32_t vid);


#ifndef IN_PORTVLAN_MINI
    sw_error_t
    fal_port_default_vid_get(a_uint32_t dev_id, fal_port_t port_id,
                             a_uint32_t * vid);

#endif

    sw_error_t
    fal_port_force_default_vid_set(a_uint32_t dev_id, fal_port_t port_id,
                                   a_bool_t enable);


#ifndef IN_PORTVLAN_MINI
    sw_error_t
    fal_port_force_default_vid_get(a_uint32_t dev_id, fal_port_t port_id,
                                   a_bool_t * enable);
#endif


    sw_error_t
    fal_port_force_portvlan_set(a_uint32_t dev_id, fal_port_t port_id,
                                a_bool_t enable);


#ifndef IN_PORTVLAN_MINI
    sw_error_t
    fal_port_force_portvlan_get(a_uint32_t dev_id, fal_port_t port_id,
                                a_bool_t * enable);

#endif

    sw_error_t
    fal_port_nestvlan_set(a_uint32_t dev_id, fal_port_t port_id,
                          a_bool_t enable);


#ifndef IN_PORTVLAN_MINI
    sw_error_t
    fal_port_nestvlan_get(a_uint32_t dev_id, fal_port_t port_id,
                          a_bool_t * enable);
#endif


    sw_error_t
    fal_nestvlan_tpid_set(a_uint32_t dev_id, a_uint32_t tpid);


#ifndef IN_PORTVLAN_MINI
    sw_error_t
    fal_nestvlan_tpid_get(a_uint32_t dev_id, a_uint32_t * tpid);
#endif

    sw_error_t
    fal_port_invlan_mode_set(a_uint32_t dev_id, fal_port_t port_id,
                             fal_pt_invlan_mode_t mode);

#ifndef IN_PORTVLAN_MINI
    sw_error_t
    fal_port_invlan_mode_get(a_uint32_t dev_id, fal_port_t port_id,
                             fal_pt_invlan_mode_t * mode);
#endif
 sw_error_t
    fal_port_tls_set(a_uint32_t dev_id, fal_port_t port_id,
                     a_bool_t enable);
#ifndef IN_PORTVLAN_MINI
   


    sw_error_t
    fal_port_tls_get(a_uint32_t dev_id, fal_port_t port_id,
                     a_bool_t * enable);


    sw_error_t
    fal_port_pri_propagation_set(a_uint32_t dev_id, fal_port_t port_id,
                                 a_bool_t enable);


    sw_error_t
    fal_port_pri_propagation_get(a_uint32_t dev_id, fal_port_t port_id,
                                 a_bool_t * enable);
#endif

    sw_error_t
    fal_port_default_svid_set(a_uint32_t dev_id, fal_port_t port_id,
                              a_uint32_t vid);

#ifndef IN_PORTVLAN_MINI
    sw_error_t
    fal_port_default_svid_get(a_uint32_t dev_id, fal_port_t port_id,
                              a_uint32_t * vid);
#endif

    sw_error_t
    fal_port_default_cvid_set(a_uint32_t dev_id, fal_port_t port_id,
                              a_uint32_t vid);

#ifndef IN_PORTVLAN_MINI
    sw_error_t
    fal_port_default_cvid_get(a_uint32_t dev_id, fal_port_t port_id,
                              a_uint32_t * vid);
#endif
	sw_error_t
    fal_port_vlan_propagation_set(a_uint32_t dev_id, fal_port_t port_id,
                                  fal_vlan_propagation_mode_t mode);

#ifndef IN_PORTVLAN_MINI
    


    sw_error_t
    fal_port_vlan_propagation_get(a_uint32_t dev_id, fal_port_t port_id,
                                  fal_vlan_propagation_mode_t * mode);


    sw_error_t
    fal_port_vlan_trans_add(a_uint32_t dev_id, fal_port_t port_id, fal_vlan_trans_entry_t *entry);


    sw_error_t
    fal_port_vlan_trans_del(a_uint32_t dev_id, fal_port_t port_id, fal_vlan_trans_entry_t *entry);


    sw_error_t
    fal_port_vlan_trans_get(a_uint32_t dev_id, fal_port_t port_id, fal_vlan_trans_entry_t *entry);


    sw_error_t
    fal_qinq_mode_set(a_uint32_t dev_id, fal_qinq_mode_t mode);


    sw_error_t
    fal_qinq_mode_get(a_uint32_t dev_id, fal_qinq_mode_t * mode);


    sw_error_t
    fal_port_qinq_role_set(a_uint32_t dev_id, fal_port_t port_id, fal_qinq_port_role_t role);


    sw_error_t
    fal_port_qinq_role_get(a_uint32_t dev_id, fal_port_t port_id, fal_qinq_port_role_t * role);


    sw_error_t
    fal_port_vlan_trans_iterate(a_uint32_t dev_id, fal_port_t port_id,
                                a_uint32_t * iterator, fal_vlan_trans_entry_t * entry);


    sw_error_t
    fal_port_mac_vlan_xlt_set(a_uint32_t dev_id, fal_port_t port_id,
                              a_bool_t enable);


    sw_error_t
    fal_port_mac_vlan_xlt_get(a_uint32_t dev_id, fal_port_t port_id,
                              a_bool_t * enable);

    sw_error_t
    fal_netisolate_set(a_uint32_t dev_id, a_uint32_t enable);

    sw_error_t
    fal_netisolate_get(a_uint32_t dev_id, a_uint32_t * enable);

    sw_error_t
    fal_eg_trans_filter_bypass_en_set(a_uint32_t dev_id, a_uint32_t enable);

    sw_error_t
    fal_eg_trans_filter_bypass_en_get(a_uint32_t dev_id, a_uint32_t * enable);

    sw_error_t
    fal_port_vrf_id_set(a_uint32_t dev_id, fal_port_t port_id,
                              a_uint32_t vrf_id);

    sw_error_t
    fal_port_vrf_id_get(a_uint32_t dev_id, fal_port_t port_id,
                              a_uint32_t * vrf_id);
#endif


#define FAL_FLG_TST(flag, field) \
    (((flag) & (field)) ? 1 : 0)

#define FAL_GLOBAL_QINQ_MODE_INGRESS_EN (0x1UL << 0)
#define FAL_GLOBAL_QINQ_MODE_EGRESS_EN (0x1UL << 1)
	typedef struct {
	    a_uint32_t mask;/*bit 0 for ingress and bit 1 for egress*/
	    fal_qinq_mode_t ingress_mode;
	    fal_qinq_mode_t egress_mode;
	} fal_global_qinq_mode_t;

#define FAL_PORT_QINQ_MODE_INGRESS_EN (0x1UL << 0)
#define FAL_PORT_QINQ_MODE_EGRESS_EN (0x1UL << 1)
	typedef struct {
	    a_uint32_t mask;/*bit 0 for ingress and bit 1 for egress*/
	    fal_qinq_port_role_t ingress_mode;
	    fal_qinq_port_role_t egress_mode;
	} fal_port_qinq_mode_t;

#define FAL_TPID_CTAG_EN (0x1UL << 0)
#define FAL_TPID_STAG_EN (0x1UL << 1)
    typedef struct
	{
		a_uint32_t mask; /*bit 0 for ctpid and bit 1 for stpid*/
		a_uint16_t ctpid;
		a_uint16_t stpid;
	} fal_tpid_t;

	typedef struct {
		a_bool_t mask;/*when mask is false, no filter should be performed*/
		a_bool_t tagged_filter;
		a_bool_t untagged_filter;
		a_bool_t priority_filter;
	} fal_ingress_filter_t;

#define FAL_PORT_INGRESS_DEFAULT_CVID_EN (0x1UL << 0)
#define FAL_PORT_INGRESS_DEFAULT_SVID_EN (0x1UL << 1)
#define FAL_PORT_INGRESS_DEFAULT_CPCP_EN (0x1UL << 2)
#define FAL_PORT_INGRESS_DEFAULT_SPCP_EN (0x1UL << 3)
#define FAL_PORT_INGRESS_DEFAULT_CDEI_EN (0x1UL << 4)
#define FAL_PORT_INGRESS_DEFAULT_SDEI_EN (0x1UL << 5)
    typedef struct
	{
    	a_uint32_t mask; /*bit 0 for ctag vid and bit 1 for stag vid;
							*bit 2 for ctag priority and bit 3 for stag priority;
							*bit 4 for ctag dei and bit 5 for stag dei*/
		a_bool_t apply_default_cvid;
		a_uint16_t default_cvid;
		a_bool_t apply_default_svid;
		a_uint16_t default_svid;
		a_uint16_t default_cpri;
		a_uint16_t default_spri;
		a_uint16_t default_cdei;
		a_uint16_t default_sdei;
	} fal_port_ingress_default_tag_t;

#define FAL_PORT_PROPOGATION_VID_EN (0x1UL << 0)
#define FAL_PORT_PROPOGATION_PCP_EN (0x1UL << 1)
#define FAL_PORT_PROPOGATION_DEI_EN (0x1UL << 2)
    typedef struct
	{
    	a_uint32_t mask; /*bit 0 for vid;
							*bit 1 for priority;
							*bit 2 for dei*/
		a_bool_t vid_prop;
		a_bool_t pri_prop;
		a_bool_t dei_prop;
	} fal_tag_propagation_t;

#define FAL_PORT_EGRESS_DEFAULT_CVID_EN (0x1UL << 0)
#define FAL_PORT_EGRESS_DEFAULT_SVID_EN (0x1UL << 1)
    typedef struct
	{
		a_uint32_t mask; /*bit 0 for ctag vid and bit 1 for stag vidi*/
		a_bool_t trip_cvid;
		a_uint16_t default_cvid;
		a_bool_t trip_svid;
		a_uint16_t default_svid;
	} fal_port_egress_default_vid_t;

#define FAL_EGRESSMODE_CTAG_EN (0x1UL << 0)
#define FAL_EGRESSMODE_STAG_EN (0x1UL << 1)
	typedef struct
	{
    	a_uint32_t mask; /*bit 0 for ctag and bit 1 for stag*/
		fal_pt_1q_egmode_t     stag_mode;
		fal_pt_1q_egmode_t     ctag_mode;
	} fal_egressmode_t;

    sw_error_t
    fal_global_qinq_mode_set(a_uint32_t dev_id, fal_global_qinq_mode_t *mode);
    sw_error_t
    fal_global_qinq_mode_get(a_uint32_t dev_id, fal_global_qinq_mode_t *mode);

    sw_error_t
    fal_port_qinq_mode_set(a_uint32_t dev_id, fal_port_t port_id, fal_port_qinq_mode_t *mode);
    sw_error_t
    fal_port_qinq_mode_get(a_uint32_t dev_id, fal_port_t port_id, fal_port_qinq_mode_t *mode);

    sw_error_t
    fal_tpid_set(a_uint32_t dev_id, fal_tpid_t *tpid);
    sw_error_t
    fal_tpid_get(a_uint32_t dev_id, fal_tpid_t *tpid);

    sw_error_t
    fal_egress_tpid_set(a_uint32_t dev_id, fal_tpid_t *tpid);
    sw_error_t
    fal_egress_tpid_get(a_uint32_t dev_id, fal_tpid_t *tpid);

    sw_error_t
    fal_port_ingress_filter_set(a_uint32_t dev_id, fal_port_t port_id, fal_ingress_filter_t *filter);
    sw_error_t
    fal_port_ingress_filter_get(a_uint32_t dev_id, fal_port_t port_id, fal_ingress_filter_t *filter);

    sw_error_t
    fal_port_ingress_default_tag_set(a_uint32_t dev_id, fal_port_t port_id,
                                 fal_port_ingress_default_tag_t *default_tag);
    sw_error_t
    fal_port_ingress_default_tag_get(a_uint32_t dev_id, fal_port_t port_id,
                                 fal_port_ingress_default_tag_t *default_tag);

    sw_error_t
    fal_port_tag_propagation_set(a_uint32_t dev_id, fal_port_t port_id,
                                 fal_tag_propagation_t *prop);
    sw_error_t
    fal_port_tag_propagation_get(a_uint32_t dev_id, fal_port_t port_id,
                                 fal_tag_propagation_t *prop);

    sw_error_t
    fal_port_egress_tag_propagation_set(a_uint32_t dev_id, fal_port_t port_id,
                                 fal_tag_propagation_t *eg_prop);
    sw_error_t
    fal_port_egress_tag_propagation_get(a_uint32_t dev_id, fal_port_t port_id,
                                 fal_tag_propagation_t *eg_prop);

    sw_error_t
    fal_port_egress_default_vid_set(a_uint32_t dev_id, fal_port_t port_id,
                                 fal_port_egress_default_vid_t *default_vid);
    sw_error_t
    fal_port_egress_default_vid_get(a_uint32_t dev_id, fal_port_t port_id,
                                 fal_port_egress_default_vid_t *default_vid);

    sw_error_t
    fal_port_vlan_xlt_miss_cmd_set(a_uint32_t dev_id, fal_port_t port_id,
                                 fal_fwd_cmd_t cmd);
    sw_error_t
    fal_port_vlan_xlt_miss_cmd_get(a_uint32_t dev_id, fal_port_t port_id,
                                 fal_fwd_cmd_t *cmd);

    sw_error_t
    fal_port_tag_egvlanmode_set(a_uint32_t dev_id, fal_port_t port_id,
                            fal_egressmode_t *port_egvlanmode);
    sw_error_t
    fal_port_tag_egvlanmode_get(a_uint32_t dev_id, fal_port_t port_id,
                            fal_egressmode_t *port_egvlanmode);

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* _PORT_VLAN_H_ */
/**
 * @}
 */
