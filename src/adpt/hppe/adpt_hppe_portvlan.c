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
#include "hppe_portvlan_reg.h"
#include "hppe_portvlan.h"
#include "adpt.h"

sw_error_t
adpt_hppe_global_qinq_mode_set(a_uint32_t dev_id, fal_global_qinq_mode_t *mode)
{
	sw_error_t rtn = SW_OK;

	ADPT_DEV_ID_CHECK(dev_id);

	if (FAL_FLG_TST(mode->mask, FAL_GLOBAL_QINQ_MODE_INGRESS_EN)) {
		SW_RTN_ON_ERROR(hppe_bridge_config_bridge_type_set(dev_id,
						(a_uint32_t)mode->ingress_mode));
	}

	if (FAL_FLG_TST(mode->mask, FAL_GLOBAL_QINQ_MODE_EGRESS_EN)) {
		SW_RTN_ON_ERROR(hppe_eg_bridge_config_bridge_type_set(dev_id,
						(a_uint32_t)mode->egress_mode));
	}

	return rtn;
}

sw_error_t
adpt_hppe_global_qinq_mode_get(a_uint32_t dev_id, fal_global_qinq_mode_t *mode)
{
	sw_error_t rtn = SW_OK;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(mode);

	SW_RTN_ON_ERROR(hppe_bridge_config_bridge_type_get(dev_id,
					(a_uint32_t *)&mode->ingress_mode));

	SW_RTN_ON_ERROR(hppe_bridge_config_bridge_type_get(dev_id,
					(a_uint32_t *)&mode->egress_mode));

	return rtn;
}

sw_error_t
adpt_hppe_port_qinq_mode_set(a_uint32_t dev_id, fal_port_t port_id, fal_port_qinq_mode_t *mode)
{
	sw_error_t rtn = SW_OK;

	ADPT_DEV_ID_CHECK(dev_id);

	if (FAL_FLG_TST(mode->mask, FAL_PORT_QINQ_MODE_INGRESS_EN)) {
		SW_RTN_ON_ERROR(hppe_port_parsing_reg_port_role_set(dev_id, port_id,
									(a_uint32_t)mode->ingress_mode));
	}

	if (FAL_FLG_TST(mode->mask, FAL_PORT_QINQ_MODE_EGRESS_EN)) {
		SW_RTN_ON_ERROR(hppe_port_eg_vlan_port_vlan_type_set(dev_id, port_id,
									(a_uint32_t)mode->egress_mode));
	}

	return rtn;
}

sw_error_t
adpt_hppe_port_qinq_mode_get(a_uint32_t dev_id, fal_port_t port_id, fal_port_qinq_mode_t *mode)
{
	sw_error_t rtn = SW_OK;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(mode);

	SW_RTN_ON_ERROR(hppe_port_parsing_reg_port_role_get(dev_id, port_id,
								(a_uint32_t *)&mode->ingress_mode));

	SW_RTN_ON_ERROR(hppe_port_eg_vlan_port_vlan_type_get(dev_id, port_id,
								(a_uint32_t *)&mode->egress_mode));

	return rtn;
}

sw_error_t
adpt_hppe_tpid_set(a_uint32_t dev_id, fal_tpid_t *tpid)
{
	sw_error_t rtn = SW_OK;

	ADPT_DEV_ID_CHECK(dev_id);

	if (FAL_FLG_TST(tpid->mask, FAL_TPID_CTAG_EN)) {
		SW_RTN_ON_ERROR(hppe_vlan_tpid_reg_ctag_tpid_set(dev_id,
						(a_uint32_t)tpid->ctpid));
	}

	if (FAL_FLG_TST(tpid->mask, FAL_TPID_STAG_EN)) {
		SW_RTN_ON_ERROR(hppe_vlan_tpid_reg_stag_tpid_set(dev_id,
						(a_uint32_t)tpid->stpid));
	}

	return rtn;
}

sw_error_t
adpt_hppe_tpid_get(a_uint32_t dev_id, fal_tpid_t *tpid)
{
	sw_error_t rtn = SW_OK;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(tpid);

	SW_RTN_ON_ERROR(hppe_vlan_tpid_reg_ctag_tpid_get(dev_id,
					(a_uint32_t *)&tpid->ctpid));

	SW_RTN_ON_ERROR(hppe_vlan_tpid_reg_stag_tpid_get(dev_id,
					(a_uint32_t *)&tpid->stpid));

	return rtn;
}

sw_error_t
adpt_hppe_egress_tpid_set(a_uint32_t dev_id, fal_tpid_t *tpid)
{
	sw_error_t rtn = SW_OK;

	ADPT_DEV_ID_CHECK(dev_id);

	if (FAL_FLG_TST(tpid->mask, FAL_TPID_CTAG_EN)) {
		SW_RTN_ON_ERROR(hppe_eg_vlan_tpid_ctpid_set(dev_id,
						(a_uint32_t)tpid->ctpid));
	}

	if (FAL_FLG_TST(tpid->mask, FAL_TPID_STAG_EN)) {
		SW_RTN_ON_ERROR(hppe_eg_vlan_tpid_stpid_set(dev_id,
						(a_uint32_t)tpid->stpid));
	}

	return rtn;
}

sw_error_t
adpt_hppe_egress_tpid_get(a_uint32_t dev_id, fal_tpid_t *tpid)
{
	sw_error_t rtn = SW_OK;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(tpid);

	SW_RTN_ON_ERROR(hppe_eg_vlan_tpid_ctpid_get(dev_id,
					(a_uint32_t *)&tpid->ctpid));

	SW_RTN_ON_ERROR(hppe_eg_vlan_tpid_stpid_get(dev_id,
					(a_uint32_t *)&tpid->stpid));

	return rtn;
}

sw_error_t
adpt_hppe_port_ingress_filter_set(a_uint32_t dev_id, fal_port_t port_id,
										fal_ingress_filter_t *filter)
{
	sw_error_t rtn = SW_OK;

	ADPT_DEV_ID_CHECK(dev_id);

	SW_RTN_ON_ERROR(hppe_port_vlan_config_port_in_vlan_fltr_cmd_set(dev_id,
						port_id, (a_uint32_t)filter->mask));
	SW_RTN_ON_ERROR(hppe_port_vlan_config_port_untag_fltr_cmd_set(dev_id,
						port_id, (a_uint32_t)filter->untagged_filter));
	SW_RTN_ON_ERROR(hppe_port_vlan_config_port_tag_fltr_cmd_set(dev_id,
						port_id, (a_uint32_t)filter->tagged_filter));
	SW_RTN_ON_ERROR(hppe_port_vlan_config_port_pri_tag_fltr_cmd_set(dev_id,
						port_id, (a_uint32_t)filter->priority_filter));

	return rtn;
}

sw_error_t
adpt_hppe_port_ingress_filter_get(a_uint32_t dev_id, fal_port_t port_id,
										fal_ingress_filter_t *filter)
{
	sw_error_t rtn = SW_OK;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(filter);

	SW_RTN_ON_ERROR(hppe_port_vlan_config_port_in_vlan_fltr_cmd_get(dev_id,
						port_id, (a_uint32_t *)&filter->mask));
	SW_RTN_ON_ERROR(hppe_port_vlan_config_port_untag_fltr_cmd_get(dev_id,
						port_id, (a_uint32_t *)&filter->untagged_filter));
	SW_RTN_ON_ERROR(hppe_port_vlan_config_port_tag_fltr_cmd_get(dev_id,
						port_id, (a_uint32_t *)&filter->tagged_filter));
	SW_RTN_ON_ERROR(hppe_port_vlan_config_port_pri_tag_fltr_cmd_get(dev_id,
						port_id, (a_uint32_t *)&filter->priority_filter));

	return rtn;
}

sw_error_t
adpt_hppe_port_ingress_default_tag_set(a_uint32_t dev_id, fal_port_t port_id,
                                 fal_port_ingress_default_tag_t *default_tag)
{
	sw_error_t rtn = SW_OK;

	ADPT_DEV_ID_CHECK(dev_id);

	if (FAL_FLG_TST(default_tag->mask, FAL_PORT_INGRESS_DEFAULT_CVID_EN)) {
		SW_RTN_ON_ERROR(hppe_port_def_vid_port_def_cvid_set(dev_id, port_id,
					(a_uint32_t)default_tag->default_cvid));
	}

	if (FAL_FLG_TST(default_tag->mask, FAL_PORT_INGRESS_DEFAULT_SVID_EN)) {
		SW_RTN_ON_ERROR(hppe_port_def_vid_port_def_svid_set(dev_id, port_id,
					(a_uint32_t)default_tag->default_svid));
	}

	if (FAL_FLG_TST(default_tag->mask, FAL_PORT_INGRESS_DEFAULT_CPCP_EN)) {
		SW_RTN_ON_ERROR(hppe_port_def_pcp_port_def_cpcp_set(dev_id, port_id,
					(a_uint32_t)default_tag->default_cpri));
	}

	if (FAL_FLG_TST(default_tag->mask, FAL_PORT_INGRESS_DEFAULT_SPCP_EN)) {
		SW_RTN_ON_ERROR(hppe_port_def_pcp_port_def_spcp_set(dev_id, port_id,
					(a_uint32_t)default_tag->default_spri));
	}

	if (FAL_FLG_TST(default_tag->mask, FAL_PORT_INGRESS_DEFAULT_CDEI_EN)) {
		SW_RTN_ON_ERROR(hppe_port_def_pcp_port_def_cdei_set(dev_id, port_id,
					(a_uint32_t)default_tag->default_cdei));
	}

	if (FAL_FLG_TST(default_tag->mask, FAL_PORT_INGRESS_DEFAULT_SDEI_EN)) {
		SW_RTN_ON_ERROR(hppe_port_def_pcp_port_def_sdei_set(dev_id, port_id,
					(a_uint32_t)default_tag->default_sdei));
	}

	SW_RTN_ON_ERROR(hppe_port_def_vid_port_def_cvid_en_set(dev_id, port_id,
					(a_uint32_t)default_tag->apply_default_cvid));

	SW_RTN_ON_ERROR(hppe_port_def_vid_port_def_svid_en_set(dev_id, port_id,
					(a_uint32_t)default_tag->apply_default_svid));

	return rtn;
}

sw_error_t
adpt_hppe_port_ingress_default_tag_get(a_uint32_t dev_id, fal_port_t port_id,
                                 fal_port_ingress_default_tag_t *default_tag)
{
	sw_error_t rtn = SW_OK;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(default_tag);

	SW_RTN_ON_ERROR(hppe_port_def_vid_port_def_cvid_get(dev_id, port_id,
				(a_uint32_t *)&default_tag->default_cvid));

	SW_RTN_ON_ERROR(hppe_port_def_vid_port_def_svid_get(dev_id, port_id,
				(a_uint32_t *)&default_tag->default_svid));

	SW_RTN_ON_ERROR(hppe_port_def_pcp_port_def_cpcp_get(dev_id, port_id,
				(a_uint32_t *)&default_tag->default_cpri));

	SW_RTN_ON_ERROR(hppe_port_def_pcp_port_def_spcp_get(dev_id, port_id,
				(a_uint32_t *)&default_tag->default_spri));

	SW_RTN_ON_ERROR(hppe_port_def_pcp_port_def_cdei_get(dev_id, port_id,
				(a_uint32_t *)&default_tag->default_cdei));

	SW_RTN_ON_ERROR(hppe_port_def_pcp_port_def_sdei_get(dev_id, port_id,
				(a_uint32_t *)&default_tag->default_sdei));

	SW_RTN_ON_ERROR(hppe_port_def_vid_port_def_cvid_en_get(dev_id, port_id,
					(a_uint32_t *)&default_tag->apply_default_cvid));

	SW_RTN_ON_ERROR(hppe_port_def_vid_port_def_svid_en_get(dev_id, port_id,
					(a_uint32_t *)&default_tag->apply_default_svid));

	return rtn;
}

sw_error_t
adpt_hppe_port_tag_propagation_set(a_uint32_t dev_id, fal_port_t port_id,
                                 fal_tag_propagation_t *prop)
{
	sw_error_t rtn = SW_OK;

	ADPT_DEV_ID_CHECK(dev_id);

	if (FAL_FLG_TST(prop->mask, FAL_PORT_PROPOGATION_VID_EN)) {
		return SW_NOT_SUPPORTED;
	}

	if (FAL_FLG_TST(prop->mask, FAL_PORT_PROPOGATION_PCP_EN)) {
		SW_RTN_ON_ERROR(hppe_port_vlan_config_port_in_pcp_prop_cmd_set(dev_id,
					port_id, (a_uint32_t)prop->pri_prop));
	}

	if (FAL_FLG_TST(prop->mask, FAL_PORT_PROPOGATION_DEI_EN)) {
		SW_RTN_ON_ERROR(hppe_port_vlan_config_port_in_dei_prop_cmd_set(dev_id,
					port_id, (a_uint32_t)prop->dei_prop));
	}

	return rtn;
}

sw_error_t
adpt_hppe_port_tag_propagation_get(a_uint32_t dev_id, fal_port_t port_id,
                                 fal_tag_propagation_t *prop)
{
	sw_error_t rtn = SW_OK;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(prop);

	SW_RTN_ON_ERROR(hppe_port_vlan_config_port_in_pcp_prop_cmd_get(dev_id,
				port_id, (a_uint32_t *)&prop->pri_prop));

	SW_RTN_ON_ERROR(hppe_port_vlan_config_port_in_dei_prop_cmd_get(dev_id,
				port_id, (a_uint32_t *)&prop->dei_prop));

	return rtn;
}

sw_error_t
adpt_hppe_port_tag_egvlanmode_set(a_uint32_t dev_id, fal_port_t port_id,
                            fal_egressmode_t *port_egvlanmode)
{
	sw_error_t rtn = SW_OK;
	a_uint32_t value = 0;

	ADPT_DEV_ID_CHECK(dev_id);

	if (FAL_FLG_TST(port_egvlanmode->mask, FAL_EGRESSMODE_CTAG_EN)) {
		if (port_egvlanmode->ctag_mode == FAL_EG_UNMODIFIED) {
			value = 2;
		} else if (port_egvlanmode->ctag_mode == FAL_EG_UNTOUCHED) {
			value = 3;
		} else if (port_egvlanmode->ctag_mode == FAL_EG_UNTAGGED) {
			value = 0;
		} else if (port_egvlanmode->ctag_mode == FAL_EG_TAGGED) {
			value = 1;
		} else {
			return SW_FAIL;
		}

		SW_RTN_ON_ERROR(hppe_port_eg_vlan_port_eg_vlan_ctag_mode_set(dev_id,
					port_id, value));
	}

	if (FAL_FLG_TST(port_egvlanmode->mask, FAL_EGRESSMODE_STAG_EN)) {
		if (port_egvlanmode->stag_mode == FAL_EG_UNMODIFIED) {
			value = 2;
		} else if (port_egvlanmode->stag_mode == FAL_EG_UNTOUCHED) {
			value = 3;
		} else if (port_egvlanmode->stag_mode == FAL_EG_UNTAGGED) {
			value = 0;
		} else if (port_egvlanmode->stag_mode == FAL_EG_TAGGED) {
			value = 1;
		} else {
			return SW_FAIL;
		}

		SW_RTN_ON_ERROR(hppe_port_eg_vlan_port_eg_vlan_stag_mode_set(dev_id,
					port_id, value));
	}

	return rtn;
}

sw_error_t
adpt_hppe_port_tag_egvlanmode_get(a_uint32_t dev_id, fal_port_t port_id,
                            fal_egressmode_t *port_egvlanmode)
{
	sw_error_t rtn = SW_OK;
	a_uint32_t value = 0;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(port_egvlanmode);


	SW_RTN_ON_ERROR(hppe_port_eg_vlan_port_eg_vlan_ctag_mode_get(dev_id,
				port_id, &value));

	if (value == 2) {
		port_egvlanmode->ctag_mode = FAL_EG_UNMODIFIED;
	} else if (value == 3) {
		port_egvlanmode->ctag_mode = FAL_EG_UNTOUCHED;
	} else if (value == 0) {
		port_egvlanmode->ctag_mode = FAL_EG_UNTAGGED;
	} else if (value == 1) {
		port_egvlanmode->ctag_mode = FAL_EG_TAGGED;
	} else {
		return SW_FAIL;
	}

	SW_RTN_ON_ERROR(hppe_port_eg_vlan_port_eg_vlan_stag_mode_get(dev_id,
				port_id, &value));

	if (value == 2) {
		port_egvlanmode->stag_mode = FAL_EG_UNMODIFIED;
	} else if (value == 3) {
		port_egvlanmode->stag_mode = FAL_EG_UNTOUCHED;
	} else if (value == 0) {
		port_egvlanmode->stag_mode = FAL_EG_UNTAGGED;
	} else if (value == 1) {
		port_egvlanmode->stag_mode = FAL_EG_TAGGED;
	} else {
		return SW_FAIL;
	}

	return rtn;
}

sw_error_t
adpt_hppe_port_egress_tag_propagation_set(a_uint32_t dev_id, fal_port_t port_id,
                                 fal_tag_propagation_t *eg_prop)
{
	sw_error_t rtn = SW_OK;

	ADPT_DEV_ID_CHECK(dev_id);

	if (FAL_FLG_TST(eg_prop->mask, FAL_PORT_PROPOGATION_VID_EN)) {
		return SW_NOT_SUPPORTED;
	}

	if (FAL_FLG_TST(eg_prop->mask, FAL_PORT_PROPOGATION_PCP_EN)) {
		SW_RTN_ON_ERROR(hppe_port_eg_vlan_port_eg_pcp_prop_cmd_set(dev_id,
					port_id, (a_uint32_t)eg_prop->pri_prop));
	}

	if (FAL_FLG_TST(eg_prop->mask, FAL_PORT_PROPOGATION_DEI_EN)) {
		SW_RTN_ON_ERROR(hppe_port_eg_vlan_port_eg_dei_prop_cmd_set(dev_id,
					port_id, (a_uint32_t)eg_prop->dei_prop));
	}

	return rtn;
}

sw_error_t
adpt_hppe_port_egress_tag_propagation_get(a_uint32_t dev_id, fal_port_t port_id,
                                 fal_tag_propagation_t *eg_prop)
{
	sw_error_t rtn = SW_OK;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(eg_prop);

	SW_RTN_ON_ERROR(hppe_port_eg_vlan_port_eg_pcp_prop_cmd_get(dev_id,
				port_id, (a_uint32_t *)&eg_prop->pri_prop));

	SW_RTN_ON_ERROR(hppe_port_eg_vlan_port_eg_dei_prop_cmd_get(dev_id,
				port_id, (a_uint32_t *)&eg_prop->dei_prop));

	return rtn;
}

sw_error_t
adpt_hppe_port_vlan_xlt_miss_cmd_set(a_uint32_t dev_id, fal_port_t port_id,
                                 fal_fwd_cmd_t cmd)
{
	sw_error_t rtn = SW_OK;
	a_uint32_t value = 0;

	ADPT_DEV_ID_CHECK(dev_id);

	if (cmd == FAL_MAC_FRWRD) {
		value = 0;
	} else if (cmd == FAL_MAC_DROP) {
		value = 1;
	} else if (cmd == FAL_MAC_CPY_TO_CPU) {
		value = 2;
	} else if (cmd == FAL_MAC_RDT_TO_CPU) {
		value = 3;
	} else {
		return SW_FAIL;
	}

	SW_RTN_ON_ERROR(hppe_port_vlan_config_port_vlan_xlt_miss_fwd_cmd_set(dev_id,
					port_id, value));

	return rtn;
}

sw_error_t
adpt_hppe_port_vlan_xlt_miss_cmd_get(a_uint32_t dev_id, fal_port_t port_id,
                                 fal_fwd_cmd_t *cmd)
{
	sw_error_t rtn = SW_OK;
	a_uint32_t value = 0;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(cmd);

	SW_RTN_ON_ERROR(hppe_port_vlan_config_port_vlan_xlt_miss_fwd_cmd_get(dev_id,
					port_id, &value));

	if (value == 0) {
		*cmd = FAL_MAC_FRWRD;
	} else if (value == 1) {
		*cmd = FAL_MAC_DROP;
	} else if (value == 2) {
		*cmd = FAL_MAC_CPY_TO_CPU;
	} else if (value == 3) {
		*cmd = FAL_MAC_RDT_TO_CPU;
	} else {
		return SW_FAIL;
	}

	return rtn;
}

sw_error_t
adpt_hppe_port_egress_default_vid_set(a_uint32_t dev_id, fal_port_t port_id,
                                 fal_port_egress_default_vid_t *default_vid)
{
	sw_error_t rtn = SW_OK;

	ADPT_DEV_ID_CHECK(dev_id);

	if (FAL_FLG_TST(default_vid->mask, FAL_PORT_EGRESS_DEFAULT_CVID_EN)) {
		SW_RTN_ON_ERROR(hppe_port_eg_def_vid_port_def_cvid_set(dev_id,
					port_id, (a_uint32_t)default_vid->default_cvid));

		SW_RTN_ON_ERROR(hppe_port_eg_def_vid_port_def_cvid_en_set(dev_id,
					port_id, (a_uint32_t)default_vid->trip_cvid));
	}

	if (FAL_FLG_TST(default_vid->mask, FAL_PORT_EGRESS_DEFAULT_SVID_EN)) {
		SW_RTN_ON_ERROR(hppe_port_eg_def_vid_port_def_svid_set(dev_id,
					port_id, (a_uint32_t)default_vid->default_svid));

		SW_RTN_ON_ERROR(hppe_port_eg_def_vid_port_def_svid_en_set(dev_id,
					port_id, (a_uint32_t)default_vid->trip_svid));
	}

	return rtn;
}
sw_error_t
adpt_hppe_port_egress_default_vid_get(a_uint32_t dev_id, fal_port_t port_id,
                                 fal_port_egress_default_vid_t *default_vid)
{
	sw_error_t rtn = SW_OK;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(default_vid);

	SW_RTN_ON_ERROR(hppe_port_eg_def_vid_port_def_cvid_get(dev_id,
				port_id, (a_uint32_t *)&default_vid->default_cvid));

	SW_RTN_ON_ERROR(hppe_port_eg_def_vid_port_def_cvid_en_get(dev_id,
				port_id, (a_uint32_t *)&default_vid->trip_cvid));

	SW_RTN_ON_ERROR(hppe_port_eg_def_vid_port_def_svid_get(dev_id,
				port_id, (a_uint32_t *)&default_vid->default_svid));

	SW_RTN_ON_ERROR(hppe_port_eg_def_vid_port_def_svid_en_get(dev_id,
				port_id, (a_uint32_t *)&default_vid->trip_svid));

	return rtn;
}

sw_error_t
adpt_hppe_port_vlan_trans_iterate(a_uint32_t dev_id, fal_port_t port_id,
                                a_uint32_t * iterator, fal_vlan_trans_entry_t *entry)
{
	sw_error_t rtn = SW_OK;

	return rtn;
}

sw_error_t
adpt_hppe_port_vlan_trans_add(a_uint32_t dev_id, fal_port_t port_id, fal_vlan_trans_entry_t *entry)
{
	sw_error_t rtn = SW_OK;
	union xlt_rule_tbl_u in_vlan_xlt_rule;
	union eg_vlan_xlt_rule_u eg_vlan_xlt_rule;
	union xlt_action_tbl_u in_vlan_xlt_action;
	union eg_vlan_xlt_action_u eg_vlan_xlt_action;

	memset(&in_vlan_xlt_rule, 0, sizeof(struct xlt_rule_tbl));
	memset(&eg_vlan_xlt_rule, 0, sizeof(struct eg_vlan_xlt_rule));
	memset(&in_vlan_xlt_action, 0, sizeof(struct xlt_action_tbl));
	memset(&eg_vlan_xlt_action, 0, sizeof(struct eg_vlan_xlt_action));

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(entry);

	if (entry->forward_dir) {
		/*rule part*/
		in_vlan_xlt_rule.bf.valid = A_TRUE;
		in_vlan_xlt_rule.bf.port_bitmap = entry->port_bitmap;

		in_vlan_xlt_rule.bf.prot_incl = entry->protocol_enable;
		in_vlan_xlt_rule.bf.prot_value_0 = (entry->protocol  & 0x7f);
		in_vlan_xlt_rule.bf.prot_value_1 = (entry->protocol >> 7);
		in_vlan_xlt_rule.bf.frm_type_incl = entry->frmtype_enable;
		in_vlan_xlt_rule.bf.frm_type = entry->frmtype;

		in_vlan_xlt_rule.bf.ckey_fmt_0 = (entry->c_tagged & 0x1);
		in_vlan_xlt_rule.bf.ckey_fmt_1 = (entry->c_tagged >> 1);
		in_vlan_xlt_rule.bf.skey_fmt = entry->s_tagged;

		in_vlan_xlt_rule.bf.ckey_vid_incl = entry->c_vid_enable;
		in_vlan_xlt_rule.bf.ckey_vid = entry->c_vid;
		in_vlan_xlt_rule.bf.ckey_pcp_incl = entry->c_pcp_enable;
		in_vlan_xlt_rule.bf.ckey_pcp = entry->c_pcp;
		in_vlan_xlt_rule.bf.ckey_dei_incl = entry->c_dei_enable;
		in_vlan_xlt_rule.bf.ckey_dei = entry->c_dei;

		in_vlan_xlt_rule.bf.skey_vid_incl = entry->s_vid_enable;
		in_vlan_xlt_rule.bf.skey_vid = entry->s_vid;
		in_vlan_xlt_rule.bf.skey_pcp_incl = entry->s_pcp_enable;
		in_vlan_xlt_rule.bf.skey_pcp = entry->s_pcp;
		in_vlan_xlt_rule.bf.skey_dei_incl = entry->s_dei_enable;
		in_vlan_xlt_rule.bf.skey_dei = entry->s_dei;

		SW_RTN_ON_ERROR(hppe_xlt_rule_tbl_set(dev_id, port_id, &in_vlan_xlt_rule));

		/*action part*/
		in_vlan_xlt_action.bf.counter_en = entry->counter_enable;
		in_vlan_xlt_action.bf.counter_id = entry->counter_id;
		in_vlan_xlt_action.bf.vsi_cmd = entry->vsi_action_enable;
		in_vlan_xlt_action.bf.vsi = entry->vsi_action;

		in_vlan_xlt_action.bf.xlt_cdei_cmd = entry->cdei_xlt_enable;
		in_vlan_xlt_action.bf.xlt_cdei = entry->cdei_xlt;
		in_vlan_xlt_action.bf.xlt_sdei_cmd = entry->sdei_xlt_enable;
		in_vlan_xlt_action.bf.xlt_sdei = entry->sdei_xlt;
		in_vlan_xlt_action.bf.dei_swap_cmd = entry->swap_sdei_cdei;

		in_vlan_xlt_action.bf.xlt_cpcp_cmd = entry->cpcp_xlt_enable;
		in_vlan_xlt_action.bf.xlt_cpcp = entry->cpcp_xlt;
		in_vlan_xlt_action.bf.xlt_spcp_cmd = entry->spcp_xlt_enable;
		in_vlan_xlt_action.bf.xlt_spcp_0 = (entry->spcp_xlt & 0x1);
		in_vlan_xlt_action.bf.xlt_spcp_1 = (entry->spcp_xlt >> 1);
		in_vlan_xlt_action.bf.pcp_swap_cmd = entry->swap_spcp_cpcp;

		in_vlan_xlt_action.bf.xlt_cvid_cmd = entry->cvid_xlt_cmd;
		in_vlan_xlt_action.bf.xlt_cvid = entry->cvid_xlt;
		in_vlan_xlt_action.bf.xlt_svid_cmd = entry->svid_xlt_cmd;
		in_vlan_xlt_action.bf.xlt_svid = entry->svid_xlt;
		in_vlan_xlt_action.bf.vid_swap_cmd = entry->swap_svid_cvid;

		SW_RTN_ON_ERROR(hppe_xlt_action_tbl_set(dev_id, port_id, &in_vlan_xlt_action));
	}

	if (entry->reverse_dir) {
		/*rule part*/
		eg_vlan_xlt_rule.bf.valid = A_TRUE;
		eg_vlan_xlt_rule.bf.port_bitmap = entry->port_bitmap;

		eg_vlan_xlt_rule.bf.vsi_incl = entry->vsi_enable;
		eg_vlan_xlt_rule.bf.vsi = entry->vsi;
		eg_vlan_xlt_rule.bf.vsi_valid = entry->vsi_valid;

		eg_vlan_xlt_rule.bf.ckey_fmt = entry->c_tagged;
		eg_vlan_xlt_rule.bf.skey_fmt = entry->s_tagged;

		eg_vlan_xlt_rule.bf.ckey_vid_incl = entry->c_vid_enable;
		eg_vlan_xlt_rule.bf.ckey_vid = entry->c_vid;
		eg_vlan_xlt_rule.bf.ckey_pcp_incl = entry->c_pcp_enable;
		eg_vlan_xlt_rule.bf.ckey_pcp = entry->c_pcp;
		eg_vlan_xlt_rule.bf.ckey_dei_incl = entry->c_dei_enable;
		eg_vlan_xlt_rule.bf.ckey_dei = entry->c_dei;

		eg_vlan_xlt_rule.bf.skey_vid_incl = entry->s_vid_enable;
		eg_vlan_xlt_rule.bf.skey_vid = entry->s_vid;
		eg_vlan_xlt_rule.bf.skey_pcp_incl = entry->s_pcp_enable;
		eg_vlan_xlt_rule.bf.skey_pcp = entry->s_pcp;
		eg_vlan_xlt_rule.bf.skey_dei_incl = entry->s_dei_enable;
		eg_vlan_xlt_rule.bf.skey_dei = entry->s_dei;

		SW_RTN_ON_ERROR(hppe_eg_vlan_xlt_rule_set(dev_id, port_id, &eg_vlan_xlt_rule));

		/*action part*/
		eg_vlan_xlt_action.bf.xlt_cdei_cmd = entry->cdei_xlt_enable;
		eg_vlan_xlt_action.bf.xlt_cdei = entry->cdei_xlt;
		eg_vlan_xlt_action.bf.xlt_sdei_cmd = entry->sdei_xlt_enable;
		eg_vlan_xlt_action.bf.xlt_sdei = entry->sdei_xlt;
		eg_vlan_xlt_action.bf.dei_swap_cmd = entry->swap_sdei_cdei;

		eg_vlan_xlt_action.bf.xlt_cpcp_cmd = entry->cpcp_xlt_enable;
		eg_vlan_xlt_action.bf.xlt_cpcp = entry->cpcp_xlt;
		eg_vlan_xlt_action.bf.xlt_spcp_cmd = entry->spcp_xlt_enable;
		eg_vlan_xlt_action.bf.xlt_spcp_0 = (entry->spcp_xlt & 0x1);
		eg_vlan_xlt_action.bf.xlt_spcp_1 = (entry->spcp_xlt >> 1);
		eg_vlan_xlt_action.bf.pcp_swap_cmd = entry->swap_spcp_cpcp;

		eg_vlan_xlt_action.bf.xlt_cvid_cmd = entry->cvid_xlt_cmd;
		eg_vlan_xlt_action.bf.xlt_cvid = entry->cvid_xlt;
		eg_vlan_xlt_action.bf.xlt_svid_cmd = entry->svid_xlt_cmd;
		eg_vlan_xlt_action.bf.xlt_svid = entry->svid_xlt;
		eg_vlan_xlt_action.bf.vid_swap_cmd = entry->swap_svid_cvid;

		SW_RTN_ON_ERROR(hppe_eg_vlan_xlt_action_set(dev_id, port_id, &eg_vlan_xlt_action));
	}

	return rtn;
}

sw_error_t
adpt_hppe_port_vlan_trans_get(a_uint32_t dev_id, fal_port_t port_id, fal_vlan_trans_entry_t *entry)
{
	sw_error_t rtn = SW_OK;

	union xlt_rule_tbl_u in_vlan_xlt_rule;
	union eg_vlan_xlt_rule_u eg_vlan_xlt_rule;
	union xlt_action_tbl_u in_vlan_xlt_action;
	union eg_vlan_xlt_action_u eg_vlan_xlt_action;

	memset(&in_vlan_xlt_rule, 0, sizeof(struct xlt_rule_tbl));
	memset(&eg_vlan_xlt_rule, 0, sizeof(struct eg_vlan_xlt_rule));
	memset(&in_vlan_xlt_action, 0, sizeof(struct xlt_action_tbl));
	memset(&eg_vlan_xlt_action, 0, sizeof(struct eg_vlan_xlt_action));

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(entry);

	if (entry->forward_dir) {
		/*rule part*/
		SW_RTN_ON_ERROR(hppe_xlt_rule_tbl_get(dev_id, port_id, &in_vlan_xlt_rule));
		if (!in_vlan_xlt_rule.bf.valid) {
			memset(&in_vlan_xlt_rule, 0, sizeof(struct xlt_rule_tbl));
		}

		entry->frmtype_enable = in_vlan_xlt_rule.bf.frm_type_incl;
		entry->frmtype = in_vlan_xlt_rule.bf.frm_type;
		entry->protocol_enable = in_vlan_xlt_rule.bf.prot_incl;
		entry->protocol = ((in_vlan_xlt_rule.bf.prot_value_1 << 7) |
							(in_vlan_xlt_rule.bf.prot_value_0));

		entry->port_bitmap = in_vlan_xlt_rule.bf.port_bitmap;
		entry->c_tagged = in_vlan_xlt_rule.bf.ckey_fmt_0 | (in_vlan_xlt_rule.bf.ckey_fmt_1 << 1);
		entry->s_tagged = in_vlan_xlt_rule.bf.skey_fmt;

		entry->c_vid_enable = in_vlan_xlt_rule.bf.ckey_vid_incl;
		entry->c_vid = in_vlan_xlt_rule.bf.ckey_vid;
		entry->c_pcp_enable = in_vlan_xlt_rule.bf.ckey_pcp_incl;
		entry->c_pcp = in_vlan_xlt_rule.bf.ckey_pcp;
		entry->c_dei_enable = in_vlan_xlt_rule.bf.ckey_dei_incl;
		entry->c_dei = in_vlan_xlt_rule.bf.ckey_dei;

		entry->s_vid_enable = in_vlan_xlt_rule.bf.skey_vid_incl;
		entry->s_vid = in_vlan_xlt_rule.bf.skey_vid;
		entry->s_pcp_enable = in_vlan_xlt_rule.bf.skey_pcp_incl;
		entry->s_pcp = in_vlan_xlt_rule.bf.skey_pcp;
		entry->s_dei_enable = in_vlan_xlt_rule.bf.skey_dei_incl;
		entry->s_dei = in_vlan_xlt_rule.bf.skey_dei;

		/*action part*/
		SW_RTN_ON_ERROR(hppe_xlt_action_tbl_get(dev_id, port_id, &in_vlan_xlt_action));
		if (!in_vlan_xlt_rule.bf.valid) {
			memset(&in_vlan_xlt_action, 0, sizeof(struct xlt_action_tbl));
		}

		entry->counter_enable = in_vlan_xlt_action.bf.counter_en;
		entry->counter_id = in_vlan_xlt_action.bf.counter_id;
		entry->vsi_action_enable = in_vlan_xlt_action.bf.vsi_cmd;
		entry->vsi_action = in_vlan_xlt_action.bf.vsi;

		entry->cdei_xlt_enable = in_vlan_xlt_action.bf.xlt_cdei_cmd;
		entry->cdei_xlt = in_vlan_xlt_action.bf.xlt_cdei;
		entry->sdei_xlt_enable = in_vlan_xlt_action.bf.xlt_sdei_cmd;
		entry->sdei_xlt = in_vlan_xlt_action.bf.xlt_sdei;
		entry->swap_sdei_cdei = in_vlan_xlt_action.bf.dei_swap_cmd;

		entry->cpcp_xlt_enable = in_vlan_xlt_action.bf.xlt_cpcp_cmd;
		entry->cpcp_xlt = in_vlan_xlt_action.bf.xlt_cpcp;
		entry->spcp_xlt_enable = in_vlan_xlt_action.bf.xlt_spcp_cmd;
		entry->spcp_xlt = (in_vlan_xlt_action.bf.xlt_spcp_0 | (in_vlan_xlt_action.bf.xlt_spcp_1 << 1));
		entry->swap_spcp_cpcp = in_vlan_xlt_action.bf.pcp_swap_cmd;

		entry->cvid_xlt_cmd = in_vlan_xlt_action.bf.xlt_cvid_cmd;
		entry->cvid_xlt = in_vlan_xlt_action.bf.xlt_cvid;
		entry->svid_xlt_cmd = in_vlan_xlt_action.bf.xlt_svid_cmd;
		entry->svid_xlt = in_vlan_xlt_action.bf.xlt_svid;
		entry->swap_svid_cvid = in_vlan_xlt_action.bf.vid_swap_cmd;
	}

	if (entry->reverse_dir) {
		/*rule part*/
		SW_RTN_ON_ERROR(hppe_eg_vlan_xlt_rule_get(dev_id, port_id, &eg_vlan_xlt_rule));
		if (!eg_vlan_xlt_rule.bf.valid) {
			memset(&eg_vlan_xlt_rule, 0, sizeof(struct eg_vlan_xlt_rule));
		}

		entry->port_bitmap = eg_vlan_xlt_rule.bf.port_bitmap;

		entry->vsi_enable = eg_vlan_xlt_rule.bf.vsi_incl;
		entry->vsi = eg_vlan_xlt_rule.bf.vsi;
		entry->vsi_valid = eg_vlan_xlt_rule.bf.vsi_valid;

		entry->c_tagged = eg_vlan_xlt_rule.bf.ckey_fmt;
		entry->s_tagged = eg_vlan_xlt_rule.bf.skey_fmt;

		entry->c_vid_enable = eg_vlan_xlt_rule.bf.ckey_vid_incl;
		entry->c_vid = eg_vlan_xlt_rule.bf.ckey_vid;
		entry->c_pcp_enable = eg_vlan_xlt_rule.bf.ckey_pcp_incl;
		entry->c_pcp = eg_vlan_xlt_rule.bf.ckey_pcp;
		entry->c_dei_enable = eg_vlan_xlt_rule.bf.ckey_dei_incl;
		entry->c_dei = eg_vlan_xlt_rule.bf.ckey_dei;

		entry->s_vid_enable = eg_vlan_xlt_rule.bf.skey_vid_incl;
		entry->s_vid = eg_vlan_xlt_rule.bf.skey_vid;
		entry->s_pcp_enable = eg_vlan_xlt_rule.bf.skey_pcp_incl;
		entry->s_pcp = eg_vlan_xlt_rule.bf.skey_pcp;
		entry->s_dei_enable = eg_vlan_xlt_rule.bf.skey_dei_incl;
		entry->s_dei = eg_vlan_xlt_rule.bf.skey_dei;

		/*action part*/
		SW_RTN_ON_ERROR(hppe_eg_vlan_xlt_action_get(dev_id, port_id, &eg_vlan_xlt_action));
		if (!eg_vlan_xlt_rule.bf.valid) {
			memset(&eg_vlan_xlt_action, 0, sizeof(struct eg_vlan_xlt_action));
		}

		entry->cdei_xlt_enable = eg_vlan_xlt_action.bf.xlt_cdei_cmd;
		entry->cdei_xlt = eg_vlan_xlt_action.bf.xlt_cdei;
		entry->sdei_xlt_enable = eg_vlan_xlt_action.bf.xlt_sdei_cmd;
		entry->sdei_xlt = eg_vlan_xlt_action.bf.xlt_sdei;
		entry->swap_sdei_cdei = eg_vlan_xlt_action.bf.dei_swap_cmd;

		entry->cpcp_xlt_enable = eg_vlan_xlt_action.bf.xlt_cpcp_cmd;
		entry->cpcp_xlt = eg_vlan_xlt_action.bf.xlt_cpcp;
		entry->spcp_xlt_enable = eg_vlan_xlt_action.bf.xlt_spcp_cmd;
		entry->spcp_xlt = (in_vlan_xlt_action.bf.xlt_spcp_0 | (in_vlan_xlt_action.bf.xlt_spcp_1 << 1));
		entry->swap_spcp_cpcp = eg_vlan_xlt_action.bf.pcp_swap_cmd;

		entry->cvid_xlt_cmd = eg_vlan_xlt_action.bf.xlt_cvid_cmd;
		entry->cvid_xlt = eg_vlan_xlt_action.bf.xlt_cvid;
		entry->svid_xlt_cmd = eg_vlan_xlt_action.bf.xlt_svid_cmd;
		entry->svid_xlt = eg_vlan_xlt_action.bf.xlt_svid;
		entry->swap_svid_cvid = eg_vlan_xlt_action.bf.vid_swap_cmd;
	}

	return rtn;
}

sw_error_t
adpt_hppe_port_vlan_trans_del(a_uint32_t dev_id, fal_port_t port_id, fal_vlan_trans_entry_t *entry)
{
	sw_error_t rtn = SW_OK;

	union xlt_rule_tbl_u in_vlan_xlt_rule;
	union eg_vlan_xlt_rule_u eg_vlan_xlt_rule;
	union xlt_action_tbl_u in_vlan_xlt_action;
	union eg_vlan_xlt_action_u eg_vlan_xlt_action;

	memset(&in_vlan_xlt_rule, 0, sizeof(struct xlt_rule_tbl));
	memset(&eg_vlan_xlt_rule, 0, sizeof(struct eg_vlan_xlt_rule));
	memset(&in_vlan_xlt_action, 0, sizeof(struct xlt_action_tbl));
	memset(&eg_vlan_xlt_action, 0, sizeof(struct eg_vlan_xlt_action));

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(entry);

	if (entry->forward_dir) {
		SW_RTN_ON_ERROR(hppe_xlt_rule_tbl_set(dev_id, port_id, &in_vlan_xlt_rule));
		SW_RTN_ON_ERROR(hppe_xlt_action_tbl_set(dev_id, port_id, &in_vlan_xlt_action));
	}

	if (entry->reverse_dir) {
		SW_RTN_ON_ERROR(hppe_eg_vlan_xlt_rule_set(dev_id, port_id, &in_vlan_xlt_rule));
		SW_RTN_ON_ERROR(hppe_eg_vlan_xlt_action_set(dev_id, port_id, &in_vlan_xlt_action));
	}

	return rtn;
}

sw_error_t adpt_hppe_portvlan_init(a_uint32_t dev_id)
{
	adpt_api_t *p_adpt_api = NULL;

	p_adpt_api = adpt_api_ptr_get(dev_id);

	if(p_adpt_api == NULL)
		return SW_FAIL;

	p_adpt_api->adpt_global_qinq_mode_set = adpt_hppe_global_qinq_mode_set;
	p_adpt_api->adpt_global_qinq_mode_get = adpt_hppe_global_qinq_mode_get;
	p_adpt_api->adpt_port_qinq_mode_set = adpt_hppe_port_qinq_mode_set;
	p_adpt_api->adpt_port_qinq_mode_get = adpt_hppe_port_qinq_mode_get;
	p_adpt_api->adpt_tpid_set = adpt_hppe_tpid_set;
	p_adpt_api->adpt_tpid_get = adpt_hppe_tpid_get;
	p_adpt_api->adpt_egress_tpid_set = adpt_hppe_egress_tpid_set;
	p_adpt_api->adpt_egress_tpid_get = adpt_hppe_egress_tpid_get;
	p_adpt_api->adpt_port_ingress_filter_set = adpt_hppe_port_ingress_filter_set;
	p_adpt_api->adpt_port_ingress_filter_get = adpt_hppe_port_ingress_filter_get;
	p_adpt_api->adpt_port_ingress_default_tag_set = adpt_hppe_port_ingress_default_tag_set;
	p_adpt_api->adpt_port_ingress_default_tag_get = adpt_hppe_port_ingress_default_tag_get;
	p_adpt_api->adpt_port_tag_propagation_set = adpt_hppe_port_tag_propagation_set;
	p_adpt_api->adpt_port_tag_propagation_get = adpt_hppe_port_tag_propagation_get;
	p_adpt_api->adpt_port_egress_tag_propagation_set = adpt_hppe_port_egress_tag_propagation_set;
	p_adpt_api->adpt_port_egress_tag_propagation_get = adpt_hppe_port_egress_tag_propagation_get;
	p_adpt_api->adpt_port_tag_egvlanmode_set = adpt_hppe_port_tag_egvlanmode_set;
	p_adpt_api->adpt_port_tag_egvlanmode_get = adpt_hppe_port_tag_egvlanmode_get;
	p_adpt_api->adpt_port_vlan_xlt_miss_cmd_set = adpt_hppe_port_vlan_xlt_miss_cmd_set;
	p_adpt_api->adpt_port_vlan_xlt_miss_cmd_get = adpt_hppe_port_vlan_xlt_miss_cmd_get;
	p_adpt_api->adpt_port_egress_default_vid_set = adpt_hppe_port_egress_default_vid_set;
	p_adpt_api->adpt_port_egress_default_vid_get = adpt_hppe_port_egress_default_vid_get;

	p_adpt_api->adpt_port_vlan_trans_iterate = adpt_hppe_port_vlan_trans_iterate;
	p_adpt_api->adpt_port_vlan_trans_add = adpt_hppe_port_vlan_trans_add;
	p_adpt_api->adpt_port_vlan_trans_get = adpt_hppe_port_vlan_trans_get;
	p_adpt_api->adpt_port_vlan_trans_del = adpt_hppe_port_vlan_trans_del;

	return SW_OK;
}

/**
 * @}
 */
