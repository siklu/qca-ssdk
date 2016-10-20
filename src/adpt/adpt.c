#include "adpt.h"
#include "adpt_hppe.h"
#include "ssdk_init.h"

adpt_api_t *g_adpt_api[SW_MAX_NR_DEV] = {NULL};
ssdk_chip_type  g_chip_type = 0;

adpt_api_t *adpt_api_ptr_get(a_uint32_t dev_id)
{
	if (dev_id >= SW_MAX_NR_DEV)
		return NULL;

	return g_adpt_api[dev_id];
}

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
		default:
			rv = adpt_hppe_fdb_init(dev_id);
			rv = adpt_hppe_stp_init(dev_id);
			rv = adpt_hppe_mirror_init( dev_id);
			rv = adpt_hppe_trunk_init( dev_id);
			rv = adpt_hppe_portvlan_init(dev_id);
			rv = adpt_hppe_ctrlpkt_init( dev_id);
			rv = adpt_hppe_sec_init(dev_id);
			break;
	}

	return rv;
}


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
		p_adpt_api->adpt_qm_func_bitmap = func_ctrl->bitmap[0];
	} else if (module == FAL_MODULE_QOS) {
		p_adpt_api->adpt_qos_func_bitmap = func_ctrl->bitmap[0];
	} else if (module == FAL_MODULE_BM) {
		p_adpt_api->adpt_bm_func_bitmap = func_ctrl->bitmap[0];
	} else if (module == FAL_MODULE_SERVCODE) {
		p_adpt_api->adpt_servcode_func_bitmap = func_ctrl->bitmap[0];
	} else if (module == FAL_MODULE_PPPOE) {
		p_adpt_api->adpt_pppoe_func_bitmap = func_ctrl->bitmap[0];
	} else if (module == FAL_MODULE_PORTCTRL) {
		p_adpt_api->adpt_port_ctrl_func_bitmap[0] = func_ctrl->bitmap[0];
		p_adpt_api->adpt_port_ctrl_func_bitmap[1] = func_ctrl->bitmap[1];
	} else if (module == FAL_MODULE_SHAPER) {
		p_adpt_api->adpt_shaper_func_bitmap = func_ctrl->bitmap[0];
	} else if(module == FAL_MODULE_MIB){
		p_adpt_api->adpt_mib_func_bitmap = func_ctrl->bitmap[0];
	}

	switch (g_chip_type)
	{
		case CHIP_HPPE:
			rv = adpt_hppe_module_func_register(dev_id, module);
			break;
		default:
			break;
	}

	return SW_OK;
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
		func_ctrl->bitmap[0] = p_adpt_api->adpt_qm_func_bitmap;
	} else if (module == FAL_MODULE_QOS) {
		func_ctrl->bitmap[0] = p_adpt_api->adpt_qos_func_bitmap;
	} else if (module == FAL_MODULE_BM) {
		func_ctrl->bitmap[0] = p_adpt_api->adpt_bm_func_bitmap;
	} else if (module == FAL_MODULE_SERVCODE) {
		func_ctrl->bitmap[0] = p_adpt_api->adpt_servcode_func_bitmap;
	} else if (module == FAL_MODULE_PPPOE) {
		func_ctrl->bitmap[0] = p_adpt_api->adpt_pppoe_func_bitmap;
	} else if (module == FAL_MODULE_PORTCTRL) {
		func_ctrl->bitmap[0] = p_adpt_api->adpt_port_ctrl_func_bitmap[0];
		func_ctrl->bitmap[1] = p_adpt_api->adpt_port_ctrl_func_bitmap[1];
	} else if (module == FAL_MODULE_SHAPER) {
		func_ctrl->bitmap[0] = p_adpt_api->adpt_shaper_func_bitmap;
	} else if(module == FAL_MODULE_MIB) {
		func_ctrl->bitmap[0] = p_adpt_api->adpt_mib_func_bitmap;
	}

	return SW_OK;
}

sw_error_t adpt_init(a_uint32_t dev_id, ssdk_init_cfg *cfg)
{
	sw_error_t rv= SW_OK;

	g_chip_type = cfg->chip_type;

	switch (cfg->chip_type)
	{
		case CHIP_HPPE:
			g_adpt_api[dev_id] = aos_mem_alloc(sizeof(adpt_api_t));
			if(g_adpt_api[dev_id] == NULL)
			{
				printk("%s, %d:malloc fail for adpt api\n", __FUNCTION__, __LINE__);
				return SW_FAIL;
			}

			adpt_hppe_acl_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_ACL);
			SW_RTN_ON_ERROR(rv);

			adpt_hppe_vsi_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_VSI);
			SW_RTN_ON_ERROR(rv);

			adpt_hppe_ip_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_IP);
			SW_RTN_ON_ERROR(rv);

			adpt_hppe_flow_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_FLOW);
			SW_RTN_ON_ERROR(rv);

			adpt_hppe_qm_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_QM);
			SW_RTN_ON_ERROR(rv);

			adpt_hppe_qos_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_QOS);
			SW_RTN_ON_ERROR(rv);

			adpt_hppe_bm_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_BM);
			SW_RTN_ON_ERROR(rv);

			adpt_hppe_servcode_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_SERVCODE);
			SW_RTN_ON_ERROR(rv);

			adpt_hppe_pppoe_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_PPPOE);
			SW_RTN_ON_ERROR(rv);

			adpt_hppe_port_ctrl_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_PORTCTRL);
			SW_RTN_ON_ERROR(rv);

			adpt_hppe_shaper_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_SHAPER);
			SW_RTN_ON_ERROR(rv);

			adpt_hppe_mib_func_bitmap_init(dev_id);
			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_MIB);
			SW_RTN_ON_ERROR(rv);

			rv = adpt_hppe_module_func_register(dev_id, FAL_MODULE_MAX);
			SW_RTN_ON_ERROR(rv);
			break;
		default:
			break;
	}
	return rv;
}

