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
#include "hppe_servcode_reg.h"
#include "hppe_servcode.h"
#include "adpt.h"

sw_error_t
adpt_parse_service_profile_set(a_uint32_t dev_id,
								a_uint32_t profile_id,
								fal_parse_service_entry_t *entry)
{
	sw_error_t rtn = SW_OK;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(entry);

	SW_RTN_ON_ERROR(hppe_service_tbl_rx_counting_en_set(dev_id,
								profile_id, entry->rx_counting_en));
	SW_RTN_ON_ERROR(hppe_service_tbl_bypass_bitmap_set(dev_id,
								profile_id, entry->bypass_bitmap));

	return rtn;
}

sw_error_t
adpt_parse_service_profile_get(a_uint32_t dev_id,
								a_uint32_t profile_id,
								fal_parse_service_entry_t *entry)
{
	sw_error_t rtn = SW_OK;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(entry);

	SW_RTN_ON_ERROR(hppe_service_tbl_rx_counting_en_get(dev_id,
								profile_id, &(entry->rx_counting_en)));
	SW_RTN_ON_ERROR(hppe_service_tbl_bypass_bitmap_get(dev_id,
								profile_id, &(entry->bypass_bitmap)));

	return rtn;
}

sw_error_t
adpt_ingress_service_profile_set(a_uint32_t dev_id,
								a_uint32_t profile_id,
								fal_ingress_service_entry_t *entry)
{
	sw_error_t rtn = SW_OK;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(entry);

	SW_RTN_ON_ERROR(hppe_in_l2_service_tbl_direction_set(dev_id,
								profile_id, entry->direction));
	SW_RTN_ON_ERROR(hppe_in_l2_service_tbl_rx_cnt_en_set(dev_id,
								profile_id, (a_uint32_t)entry->rx_cnt_en));
	SW_RTN_ON_ERROR(hppe_in_l2_service_tbl_tx_cnt_en_set(dev_id,
								profile_id, (a_uint32_t)entry->tx_cnt_en));
	SW_RTN_ON_ERROR(hppe_in_l2_service_tbl_bypass_bitmap_set(dev_id,
								profile_id, entry->bypass_bitmap));
	SW_RTN_ON_ERROR(hppe_in_l2_service_tbl_dst_port_id_valid_set(dev_id,
								profile_id, (a_uint32_t)entry->dst_port_id_valid));
	SW_RTN_ON_ERROR(hppe_in_l2_service_tbl_dst_port_id_set(dev_id,
								profile_id, entry->dst_port_id));

	return rtn;
}

sw_error_t
adpt_ingress_service_profile_get(a_uint32_t dev_id,
								a_uint32_t profile_id,
								fal_ingress_service_entry_t *entry)
{
	sw_error_t rtn = SW_OK;
	a_uint64_t value = 0;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(entry);

	SW_RTN_ON_ERROR(hppe_in_l2_service_tbl_direction_get(dev_id,
								profile_id, &(entry->direction)));
	SW_RTN_ON_ERROR(hppe_in_l2_service_tbl_rx_cnt_en_set(dev_id,
								profile_id, (a_uint32_t *)&(entry->rx_cnt_en)));
	SW_RTN_ON_ERROR(hppe_in_l2_service_tbl_tx_cnt_en_set(dev_id,
								profile_id, (a_uint32_t *)&(entry->tx_cnt_en)));
	SW_RTN_ON_ERROR(hppe_in_l2_service_tbl_bypass_bitmap_set(dev_id,
								profile_id, &(entry->bypass_bitmap)));
	SW_RTN_ON_ERROR(hppe_in_l2_service_tbl_dst_port_id_valid_set(dev_id,
								profile_id, (a_uint32_t *)&(entry->dst_port_id_valid)));
	SW_RTN_ON_ERROR(hppe_in_l2_service_tbl_dst_port_id_set(dev_id,
								profile_id, &(entry->dst_port_id)));

	return rtn;
}

sw_error_t
adpt_egress_service_profile_set(a_uint32_t dev_id,
								a_uint32_t profile_id,
								fal_egress_service_entry_t *entry)
{
	sw_error_t rtn = SW_OK;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(entry);

	SW_RTN_ON_ERROR(hppe_eg_service_tbl_next_service_code_set(dev_id,
								profile_id,
								entry->next_service_code));
	SW_RTN_ON_ERROR(hppe_eg_service_tbl_tx_counting_en_set(dev_id,
								profile_id,
								(a_uint32_t)entry->tx_counting_en));
	SW_RTN_ON_ERROR(hppe_eg_service_tbl_field_update_action_set(dev_id,
								profile_id,
								entry->field_update_action));
	SW_RTN_ON_ERROR(hppe_eg_service_tbl_offset_sel_set(dev_id,
								profile_id,
								entry->offset_sel));
	SW_RTN_ON_ERROR(hppe_eg_service_tbl_hw_services_set(dev_id,
								profile_id,
								entry->hw_services));

	return rtn;
}

sw_error_t
adpt_egress_service_profile_get(a_uint32_t dev_id,
								a_uint32_t profile_id,
								fal_egress_service_entry_t *entry)
{
	sw_error_t rtn = SW_OK;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(entry);

	SW_RTN_ON_ERROR(hppe_eg_service_tbl_next_service_code_get(dev_id,
								profile_id,
								(a_uint32_t *)&(entry->next_service_code)));
	SW_RTN_ON_ERROR(hppe_eg_service_tbl_tx_counting_en_get(dev_id,
								profile_id,
								(a_uint32_t *)&(entry->tx_counting_en)));
	SW_RTN_ON_ERROR(hppe_eg_service_tbl_field_update_action_get(dev_id,
								profile_id,
								(a_uint32_t *)&(entry->field_update_action)));
	SW_RTN_ON_ERROR(hppe_eg_service_tbl_offset_sel_get(dev_id,
								profile_id,
								(a_uint32_t *)&(entry->offset_sel)));
	SW_RTN_ON_ERROR(hppe_eg_service_tbl_hw_services_get(dev_id,
								profile_id,
								(a_uint32_t *)&(entry->hw_services)));

	return rtn;
}

sw_error_t adpt_hppe_servcode_init(a_uint32_t dev_id)
{
	adpt_api_t *p_adpt_api = NULL;

	p_adpt_api = adpt_api_ptr_get(dev_id);

	if(p_adpt_api == NULL)
		return SW_FAIL;

	p_adpt_api->adpt_parse_service_profile_set = adpt_parse_service_profile_set;
	p_adpt_api->adpt_parse_service_profile_get = adpt_parse_service_profile_get;
	p_adpt_api->adpt_ingress_service_profile_set = adpt_ingress_service_profile_set;
	p_adpt_api->adpt_ingress_service_profile_get = adpt_ingress_service_profile_get;
	p_adpt_api->adpt_egress_service_profile_set = adpt_egress_service_profile_set;
	p_adpt_api->adpt_egress_service_profile_get = adpt_egress_service_profile_get;

	return SW_OK;
}

/**
 * @}
 */


