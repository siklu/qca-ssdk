/*
 * Copyright (c) 2016-2017, The Linux Foundation. All rights reserved.
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

#include "adpt.h"
#include "ssdk_init.h"
#if defined(HPPE)
#include "adpt_hppe.h"
#endif

adpt_api_t *g_adpt_api[SW_MAX_NR_DEV] = {NULL};
ssdk_chip_type  g_chip_type = 0;

adpt_api_t *adpt_api_ptr_get(a_uint32_t dev_id)
{
	if (dev_id >= SW_MAX_NR_DEV)
		return NULL;

	return g_adpt_api[dev_id];
}

#if defined(HPPE)
static sw_error_t adpt_hppe_module_func_register(a_uint32_t dev_id, a_uint32_t module)
{
	sw_error_t rv= SW_OK;

	switch (module)
	{
		case FAL_MODULE_ACL:
			rv = adpt_hppe_acl_init(dev_id);
			break;
		case FAL_MODULE_VSI:
			rv = adpt_hppe_vsi_init(dev_id);
			break;
		case FAL_MODULE_IP:
			rv = adpt_hppe_ip_init(dev_id);
			break;
		case FAL_MODULE_FLOW:
			rv = adpt_hppe_flow_init(dev_id);
			break;
		case FAL_MODULE_QM:
			rv = adpt_hppe_qm_init(dev_id);
			break;
		case FAL_MODULE_QOS:
			rv = adpt_hppe_qos_init(dev_id);
			break;
		case FAL_MODULE_BM:
			rv = adpt_hppe_bm_init(dev_id);
			break;
		case FAL_MODULE_SERVCODE:
			rv = adpt_hppe_servcode_init( dev_id);
			break;
		case FAL_MODULE_RSS_HASH:
			rv = adpt_hppe_rss_hash_init( dev_id);
			break;
		case FAL_MODULE_PPPOE:
			rv = adpt_hppe_pppoe_init(dev_id);
			break;
		case FAL_MODULE_PORTCTRL:
			rv = adpt_hppe_port_ctrl_init(dev_id);
			break;
		case FAL_MODULE_SHAPER:
			rv = adpt_hppe_shaper_init( dev_id);
			break;
		case FAL_MODULE_MIB:
			rv = adpt_hppe_mib_init(dev_id);
			break;
		case FAL_MODULE_MIRROR:
			rv = adpt_hppe_mirror_init( dev_id);
			break;
		case FAL_MODULE_FDB:
			rv = adpt_hppe_fdb_init(dev_id);
			break;
		case FAL_MODULE_STP:
			rv = adpt_hppe_stp_init(dev_id);
			break;
		case FAL_MODULE_TRUNK:
			rv = adpt_hppe_trunk_init( dev_id);
			break;
		case FAL_MODULE_PORTVLAN:
			rv = adpt_hppe_portvlan_init(dev_id);
			break;
		case FAL_MODULE_CTRLPKT:
			rv = adpt_hppe_ctrlpkt_init( dev_id);
			break;
		case FAL_MODULE_SEC:
			rv = adpt_hppe_sec_init(dev_id);
			break;
		case FAL_MODULE_POLICER:
			rv = adpt_hppe_policer_init(dev_id);
			break;
		case FAL_MODULE_MISC:
			rv = adpt_hppe_misc_init(dev_id);
			break;
		default:
			break;
	}

	return rv;
}
#endif

sw_error_t adpt_module_func_ctrl_set(a_uint32_t dev_id,
		a_uint32_t module, fal_func_ctrl_t *func_ctrl)
{
	sw_error_t rv= SW_OK;

	adpt_api_t *p_adpt_api = NULL;

	p_adpt_api = adpt_api_ptr_get(dev_id);

	if(p_adpt_api == NULL)
		return SW_FAIL;

	if(module == FAL_MODULE_ACL){
		p_adpt_api->adpt_acl_func_bitmap = func_ctrl->bitmap[0];
	} else if (module == FAL_MODULE_VSI) {
		p_adpt_api->adpt_vsi_func_bitmap = func_ctrl->bitmap[0];
	}else if (module == FAL_MODULE_IP) {
		p_adpt_api->adpt_ip_func_bitmap[0] = func_ctrl->bitmap[0];
		p_adpt_api->adpt_ip_func_bitmap[1] = func_ctrl->bitmap[1];
	} else if (module == FAL_MODULE_FLOW) {
		p_adpt_api->adpt_flow_func_bitmap = func_ctrl->bitmap[0];
	} else if (module == FAL_MODULE_QM) {
		p_adpt_api->adpt_qm_func_bitmap[0] = func_ctrl->bitmap[0];
		p_adpt_api->adpt_qm_func_bitmap[1] = func_ctrl->bitmap[1];
	} else if (module == FAL_MODULE_QOS) {
		p_adpt_api->adpt_qos_func_bitmap = func_ctrl->bitmap[0];
	} else if (module == FAL_MODULE_BM) {
		p_adpt_api->adpt_bm_func_bitmap = func_ctrl->bitmap[0];
	} else if (module == FAL_MODULE_SERVCODE) {
		p_adpt_api->adpt_servcode_func_bitmap = func_ctrl->bitmap[0];
	} else if (module == FAL_MODULE_RSS_HASH) {
		p_adpt_api->adpt_rss_hash_func_bitmap = func_ctrl->bitmap[0];
	} else if (module == FAL_MODULE_PPPOE) {
		p_adpt_api->adpt_pppoe_func_bitmap = func_ctrl->bitmap[0];
	} else if (module == FAL_MODULE_PORTCTRL) {
		p_adpt_api->adpt_port_ctrl_func_bitmap[0] = func_ctrl->bitmap[0];
		p_adpt_api->adpt_port_ctrl_func_bitmap[1] = func_ctrl->bitmap[1];
		p_adpt_api->adpt_port_ctrl_func_bitmap[2] = func_ctrl->bitmap[2];
	} else if (module == FAL_MODULE_SHAPER) {
		p_adpt_api->adpt_shaper_func_bitmap = func_ctrl->bitmap[0];
	} else if(module == FAL_MODULE_MIB){
		p_adpt_api->adpt_mib_func_bitmap = func_ctrl->bitmap[0];
	} else if(module == FAL_MODULE_MIRROR){
		p_adpt_api->adpt_mirror_func_bitmap = func_ctrl->bitmap[0];
	} else if(module == FAL_MODULE_FDB){
		p_adpt_api->adpt_fdb_func_bitmap = func_ctrl->bitmap[0];
	} else if(module == FAL_MODULE_STP){
		p_adpt_api->adpt_stp_func_bitmap = func_ctrl->bitmap[0];
	} else if(module == FAL_MODULE_TRUNK){
		p_adpt_api->adpt_trunk_func_bitmap = func_ctrl->bitmap[0];
	} else if(module == FAL_MODULE_PORTVLAN){
		p_adpt_api->adpt_portvlan_func_bitmap[0] = func_ctrl->bitmap[0];
		p_adpt_api->adpt_portvlan_func_bitmap[1] = func_ctrl->bitmap[1];
	} else if(module == FAL_MODULE_CTRLPKT){
		p_adpt_api->adpt_ctrlpkt_func_bitmap = func_ctrl->bitmap[0];
	} else if(module == FAL_MODULE_SEC){
		p_adpt_api->adpt_sec_func_bitmap = func_ctrl->bitmap[0];
	} else if(module == FAL_MODULE_POLICER){
		p_adpt_api->adpt_policer_func_bitmap = func_ctrl->bitmap[0];
	}


	switch (g_chip_type)
	{
		#if defined(HPPE)
		case CHIP_HPPE:
			rv = adpt_hppe_module_func_register(dev_id, module);
			break;
		#endif
		default:
			break;
	}

	return rv;
}

sw_error_t adpt_module_func_ctrl_get(a_uint32_t dev_id,
		a_uint32_t module, fal_func_ctrl_t *func_ctrl)
{
	adpt_api_t *p_adpt_api = NULL;

	p_adpt_api = adpt_api_ptr_get(dev_id);

	if(p_adpt_api == NULL)
		return SW_FAIL;

	if(module == FAL_MODULE_ACL){
		func_ctrl->bitmap[0] = p_adpt_api->adpt_acl_func_bitmap;
	} else if (module == FAL_MODULE_VSI) {
		func_ctrl->bitmap[0] = p_adpt_api->adpt_vsi_func_bitmap;
	} else if (module == FAL_MODULE_IP) {
		func_ctrl->bitmap[0] = p_adpt_api->adpt_ip_func_bitmap[0];
		func_ctrl->bitmap[1] = p_adpt_api->adpt_ip_func_bitmap[1];
	} else if (module == FAL_MODULE_FLOW) {
		func_ctrl->bitmap[0] = p_adpt_api->adpt_flow_func_bitmap;
	} else if (module == FAL_MODULE_QM) {
		func_ctrl->bitmap[0] = p_adpt_api->adpt_qm_func_bitmap[0];
		func_ctrl->bitmap[1] = p_adpt_api->adpt_qm_func_bitmap[1];
	} else if (module == FAL_MODULE_QOS) {
		func_ctrl->bitmap[0] = p_adpt_api->adpt_qos_func_bitmap;
	} else if (module == FAL_MODULE_BM) {
		func_ctrl->bitmap[0] = p_adpt_api->adpt_bm_func_bitmap;
	} else if (module == FAL_MODULE_SERVCODE) {
		func_ctrl->bitmap[0] = p_adpt_api->adpt_servcode_func_bitmap;
	} else if (module == FAL_MODULE_RSS_HASH) {
		func_ctrl->bitmap[0] = p_adpt_api->adpt_rss_hash_func_bitmap;
	} else if (module == FAL_MODULE_PPPOE) {
		func_ctrl->bitmap[0] = p_adpt_api->adpt_pppoe_func_bitmap;
	} else if (module == FAL_MODULE_PORTCTRL) {
		func_ctrl->bitmap[0] = p_adpt_api->adpt_port_ctrl_func_bitmap[0];
		func_ctrl->bitmap[1] = p_adpt_api->adpt_port_ctrl_func_bitmap[1];
		func_ctrl->bitmap[2] = p_adpt_api->adpt_port_ctrl_func_bitmap[2];
	} else if (module == FAL_MODULE_SHAPER) {
		func_ctrl->bitmap[0] = p_adpt_api->adpt_shaper_func_bitmap;
	} else if(module == FAL_MODULE_MIB) {
		func_ctrl->bitmap[0] = p_adpt_api->adpt_mib_func_bitmap;
	} else if(module == FAL_MODULE_MIRROR) {
		func_ctrl->bitmap[0] = p_adpt_api->adpt_mirror_func_bitmap;
	} else if(module == FAL_MODULE_FDB) {
		func_ctrl->bitmap[0] = p_adpt_api->adpt_fdb_func_bitmap;
	} else if(module == FAL_MODULE_STP) {
		func_ctrl->bitmap[0] = p_adpt_api->adpt_stp_func_bitmap;
	} else if(module == FAL_MODULE_TRUNK) {
		func_ctrl->bitmap[0] = p_adpt_api->adpt_trunk_func_bitmap;
	} else if(module == FAL_MODULE_PORTVLAN) {
		func_ctrl->bitmap[0] = p_adpt_api->adpt_portvlan_func_bitmap[0];
		func_ctrl->bitmap[1] = p_adpt_api->adpt_portvlan_func_bitmap[1];
	} else if(module == FAL_MODULE_CTRLPKT) {
		func_ctrl->bitmap[0] = p_adpt_api->adpt_ctrlpkt_func_bitmap;
	} else if(module == FAL_MODULE_SEC) {
		func_ctrl->bitmap[0] = p_adpt_api->adpt_sec_func_bitmap;
	} else if(module == FAL_MODULE_POLICER) {
		func_ctrl->bitmap[0] = p_adpt_api->adpt_policer_func_bitmap;
	}

	return SW_OK;
}

sw_error_t adpt_init(a_uint32_t dev_id, ssdk_init_cfg *cfg)
{
	sw_error_t rv= SW_OK;

	g_chip_type = cfg->chip_type;

	switch (cfg->chip_type)
	{
		#if defined(HPPE)
		case CHIP_HPPE:
			g_adpt_api[dev_id] = aos_mem_alloc(sizeof(adpt_api_t));
			if(g_adpt_api[dev_id] == NULL)
			{
				printk("%s, %d:malloc fail for adpt api\n", __FUNCTION__, __LINE__);
				return SW_FAIL;
			}

			g_adpt_api[dev_id]->adpt_mirror_func_bitmap = 0xffffffff;
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_MIRROR);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_fdb_func_bitmap = 0xffffffff;
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_FDB);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_stp_func_bitmap = 0xffffffff;
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_STP);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_trunk_func_bitmap = 0xffffffff;
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_TRUNK);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_portvlan_func_bitmap[0] = 0xffffffff;
			g_adpt_api[dev_id]->adpt_portvlan_func_bitmap[1] = 0xffffffff;
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_PORTVLAN);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_ctrlpkt_func_bitmap = 0xffffffff;
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_CTRLPKT);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_sec_func_bitmap = 0xffffffff;
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_SEC);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_acl_func_bitmap = 0xffffffff;
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_ACL);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_vsi_func_bitmap = 0xffffffff;
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_VSI);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_ip_func_bitmap[0] = 0xffffffff;
			g_adpt_api[dev_id]->adpt_ip_func_bitmap[1] = 0xffffffff;
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_IP);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_flow_func_bitmap = 0xffffffff;
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_FLOW);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_qm_func_bitmap[0] = 0xffffffff;
			g_adpt_api[dev_id]->adpt_qm_func_bitmap[1] = 0xffffffff;
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_QM);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_qos_func_bitmap = 0xffffffff;
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_QOS);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_bm_func_bitmap = 0xffffffff;
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_BM);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_servcode_func_bitmap = 0xffffffff;
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_SERVCODE);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_rss_hash_func_bitmap = 0xffffffff;
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_RSS_HASH);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_pppoe_func_bitmap = 0xffffffff;
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_PPPOE);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_port_ctrl_func_bitmap[0] = 0xffffffff;
			g_adpt_api[dev_id]->adpt_port_ctrl_func_bitmap[1] = 0xffffffff;
			g_adpt_api[dev_id]->adpt_port_ctrl_func_bitmap[2] = 0xffffffff;
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_PORTCTRL);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_shaper_func_bitmap = 0xffffffff;
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_SHAPER);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_mib_func_bitmap = 0xffffffff;
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_MIB);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_policer_func_bitmap = 0xffffffff;
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_POLICER);
			SW_RTN_ON_ERROR(rv);

			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_MISC);
			SW_RTN_ON_ERROR(rv);

#ifdef HAWKEYE_CHIP
			/* uniphy */
			rv = adpt_hppe_uniphy_init(dev_id);
			SW_RTN_ON_ERROR(rv);
#endif
			break;
			#endif
		default:
			break;
	}
	return rv;
}

sw_error_t adpt_module_func_init(a_uint32_t dev_id, ssdk_init_cfg *cfg)
{
	sw_error_t rv= SW_OK;

	switch (cfg->chip_type)
	{
		#if defined(HPPE)
		case CHIP_HPPE:
			g_adpt_api[dev_id]->adpt_mirror_func_bitmap = 0;
			adpt_hppe_mirror_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_MIRROR);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_fdb_func_bitmap = 0;
			adpt_hppe_fdb_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_FDB);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_stp_func_bitmap = 0;
			adpt_hppe_stp_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_STP);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_trunk_func_bitmap = 0;
			adpt_hppe_trunk_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_TRUNK);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_portvlan_func_bitmap[0] = 0;
			g_adpt_api[dev_id]->adpt_portvlan_func_bitmap[1] = 0;
			adpt_hppe_portvlan_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_PORTVLAN);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_ctrlpkt_func_bitmap = 0;
			adpt_hppe_ctrlpkt_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_CTRLPKT);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_sec_func_bitmap = 0;
			adpt_hppe_sec_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_SEC);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_acl_func_bitmap = 0;
			adpt_hppe_acl_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_ACL);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_vsi_func_bitmap = 0;
			adpt_hppe_vsi_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_VSI);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_ip_func_bitmap[0] = 0;
			g_adpt_api[dev_id]->adpt_ip_func_bitmap[1] = 0;
			adpt_hppe_ip_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_IP);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_flow_func_bitmap = 0;
			adpt_hppe_flow_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_FLOW);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_qm_func_bitmap[0] = 0;
			g_adpt_api[dev_id]->adpt_qm_func_bitmap[1] = 0;
			adpt_hppe_qm_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_QM);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_qos_func_bitmap = 0;
			adpt_hppe_qos_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_QOS);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_bm_func_bitmap = 0;
			adpt_hppe_bm_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_BM);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_servcode_func_bitmap = 0;
			adpt_hppe_servcode_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_SERVCODE);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_rss_hash_func_bitmap = 0;
			adpt_hppe_rss_hash_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_RSS_HASH);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_pppoe_func_bitmap = 0;
			adpt_hppe_pppoe_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_PPPOE);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_port_ctrl_func_bitmap[0] = 0;
			g_adpt_api[dev_id]->adpt_port_ctrl_func_bitmap[1] = 0;
			g_adpt_api[dev_id]->adpt_port_ctrl_func_bitmap[2] = 0;
			adpt_hppe_port_ctrl_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_PORTCTRL);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_shaper_func_bitmap = 0;
			adpt_hppe_shaper_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_SHAPER);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_mib_func_bitmap = 0;
			adpt_hppe_mib_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_MIB);
			SW_RTN_ON_ERROR(rv);

			g_adpt_api[dev_id]->adpt_policer_func_bitmap = 0;
			adpt_hppe_policer_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_POLICER);
			SW_RTN_ON_ERROR(rv);

			break;
		#endif
		default:
			break;
	}
	return rv;
}

