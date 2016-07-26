#include "adpt.h"
#include "adpt_hppe.h"
#include "ssdk_init.h"

adpt_api_t g_adpt_api[SW_MAX_NR_DEV] = {0};

adpt_api_t *adpt_api_ptr_get(a_uint32_t dev_id)
{
	if (dev_id >= SW_MAX_NR_DEV)
		return NULL;

	return &(g_adpt_api[dev_id]);
}

sw_error_t adpt_init(a_uint32_t dev_id, ssdk_init_cfg *cfg)
{
	sw_error_t rv= SW_FAIL;

	switch (cfg->chip_type)
	{
		case CHIP_HPPE:
			rv = adpt_hppe_vsi_init(dev_id);
			SW_RTN_ON_ERROR(rv);
			rv = adpt_hppe_fdb_init(dev_id);
			SW_RTN_ON_ERROR(rv);
			rv = adpt_hppe_mib_init(dev_id);
			SW_RTN_ON_ERROR(rv);
			rv = adpt_hppe_stp_init(dev_id);
			SW_RTN_ON_ERROR(rv);
			rv = adpt_hppe_port_ctrl_init(dev_id);
			SW_RTN_ON_ERROR(rv);
			rv =  adpt_hppe_mirror_init( dev_id);
			SW_RTN_ON_ERROR(rv);
			rv =  adpt_hppe_trunk_init( dev_id);
			SW_RTN_ON_ERROR(rv);
			rv = adpt_hppe_ip_init(dev_id);
			SW_RTN_ON_ERROR(rv);
			rv = adpt_hppe_flow_init(dev_id);
			SW_RTN_ON_ERROR(rv);
			rv = adpt_hppe_qm_init(dev_id);
			rv = adpt_hppe_portvlan_init(dev_id);
			SW_RTN_ON_ERROR(rv);
			rv = adpt_hppe_ctrlpkt_init( dev_id);
			SW_RTN_ON_ERROR(rv);
			rv = adpt_hppe_servcode_init( dev_id);
			SW_RTN_ON_ERROR(rv);
			rv = adpt_hppe_pppoe_init(dev_id);
			SW_RTN_ON_ERROR(rv);
			rv = adpt_hppe_sec_init(dev_id);
			SW_RTN_ON_ERROR(rv);
			rv = adpt_hppe_acl_init(dev_id);
			SW_RTN_ON_ERROR(rv);
			break;
		default:
			break;
	}
	return rv;
}

