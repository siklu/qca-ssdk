/*
 * Copyright (c) 2014-2015, The Linux Foundation. All rights reserved.
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
 * @defgroup dess_init DESS_INIT
 * @{
 */
#include "sw.h"
#include "hsl.h"
#include "hsl_dev.h"
#include "hsl_port_prop.h"
#include "sd.h"


static ssdk_init_cfg * hppe_cfg[SW_MAX_NR_DEV] = { 0 };


static sw_error_t
hppe_dev_init(a_uint32_t dev_id, ssdk_init_cfg *cfg)
{
	sw_error_t rv;
	hsl_dev_t *pdev = NULL;
	a_uint32_t i = 0, port_nr = 0, tmp = 0;

	pdev = hsl_dev_ptr_get(dev_id);
	if (pdev == NULL)
		return SW_NOT_INITIALIZED;

	tmp = cfg->port_cfg.lan_bmp | cfg->port_cfg.wan_bmp;
	for(i = 0; i < SW_MAX_NR_PORT; i++) {
		if(tmp & (1 << i)) {
			port_nr++;
		}
	}
	pdev->nr_phy = port_nr;
	for(i = 0; i < SW_MAX_NR_PORT; i++) {
		if(cfg->port_cfg.cpu_bmp & (1 << i)) {
			port_nr++;
			pdev->cpu_port_nr = i;
			break;
		}
	}
	if(i >= SW_MAX_NR_PORT)
		return SW_BAD_VALUE;
	pdev->nr_ports = port_nr;
	pdev->nr_vlans = 4096;
	pdev->hw_vlan_query = A_TRUE;
	pdev->nr_queue = port_nr;
	pdev->cpu_mode = cfg->cpu_mode;
	pdev->wan_bmp = cfg->port_cfg.wan_bmp;

	return SW_OK;
}

sw_error_t
hppe_cleanup(a_uint32_t dev_id)
{
    sw_error_t rv;

    if (hppe_cfg[dev_id])
    {
        SW_RTN_ON_ERROR(hsl_port_prop_cleanup_by_dev(dev_id));

        aos_mem_free(hppe_cfg[dev_id]);
        hppe_cfg[dev_id] = NULL;
    }

    return SW_OK;
}

/**
 * @brief Init hsl layer.
 * @details Comments:
 *   This operation will init hsl layer and hsl layer
 * @param[in] dev_id device id
 * @param[in] cfg configuration for initialization
 * @return SW_OK or error code
 */
sw_error_t hppe_init(a_uint32_t dev_id, ssdk_init_cfg *cfg)
{
    HSL_DEV_ID_CHECK(dev_id);

    printk("HPPE initializing...\n");
    if (NULL == hppe_cfg[dev_id])
    {
        hppe_cfg[dev_id] = aos_mem_alloc(sizeof (ssdk_init_cfg));
    }

    if (NULL == hppe_cfg[dev_id])
    {
        return SW_OUT_OF_MEM;
    }

    aos_mem_copy(hppe_cfg[dev_id], cfg, sizeof (ssdk_init_cfg));

    SW_RTN_ON_ERROR(hppe_dev_init(dev_id, cfg));

#if !(defined(KERNEL_MODULE) && defined(USER_MODE))
    {
        sw_error_t rv;
	hsl_api_t *p_api;

        SW_RTN_ON_ERROR(hsl_port_prop_init());
        SW_RTN_ON_ERROR(hsl_port_prop_init_by_dev(dev_id));

	SW_RTN_ON_NULL(p_api = hsl_api_ptr_get(dev_id));
	p_api->dev_clean   = hppe_cleanup;
	p_api->reg_get = sd_reg_hdr_get;
	p_api->reg_set = sd_reg_hdr_set;

    }
#endif

    return SW_OK;
}

/**
 * @}
 */

