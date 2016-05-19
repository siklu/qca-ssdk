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
#include "hppe_mirror.h"
#include "hppe_mirror_reg.h"
#include "adpt.h"

sw_error_t
adpt_hppe_mirr_eg_analysis_port_get(a_uint32_t dev_id, fal_port_t *port_id)
{
	sw_error_t rv = SW_OK;
	union mirror_analyzer_u mirror_analyzer;

	memset(&mirror_analyzer, 0, sizeof(mirror_analyzer));
	ADPT_DEV_ID_CHECK(dev_id);


	rv = hppe_mirror_analyzer_get(dev_id, &mirror_analyzer);

	if( rv != SW_OK )
		return rv;

	*port_id = mirror_analyzer.bf.eg_analyzer_port;

	return SW_OK;
}

sw_error_t
adpt_hppe_mirr_port_in_get(a_uint32_t dev_id, fal_port_t port_id,
                         a_bool_t * enable)
{
	sw_error_t rv = SW_OK;
	union port_mirror_u port_mirror;

	memset(&port_mirror, 0, sizeof(port_mirror));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(enable);

	rv = hppe_port_mirror_get(dev_id, port_id, &port_mirror);

	if( rv != SW_OK )
		return rv;

	*enable = port_mirror.bf.in_mirr_en;

	return SW_OK;
}

sw_error_t
adpt_hppe_mirr_port_eg_get(a_uint32_t dev_id, fal_port_t port_id,
                         a_bool_t * enable)
{
	sw_error_t rv = SW_OK;
	union port_mirror_u port_mirror;

	memset(&port_mirror, 0, sizeof(port_mirror));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(enable);


	rv = hppe_port_mirror_get(dev_id, port_id, &port_mirror);

	if( rv != SW_OK )
		return rv;

	*enable = port_mirror.bf.eg_mirr_en;

	return SW_OK;
}

sw_error_t
adpt_hppe_mirr_analysis_port_get(a_uint32_t dev_id, fal_port_t * port_id)
{
	sw_error_t rv = SW_OK;
	union mirror_analyzer_u mirror_analyzer;

	memset(&mirror_analyzer, 0, sizeof(mirror_analyzer));
	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(port_id);


	rv = hppe_mirror_analyzer_get(dev_id, &mirror_analyzer);

	if( rv != SW_OK )
		return rv;

	*port_id = mirror_analyzer.bf.eg_analyzer_port;

	return SW_OK;
}

sw_error_t
adpt_hppe_mirr_port_in_set(a_uint32_t dev_id, fal_port_t port_id,
                         a_bool_t enable)
{
	union port_mirror_u port_mirror;

	memset(&port_mirror, 0, sizeof(port_mirror));
	ADPT_DEV_ID_CHECK(dev_id);

	hppe_port_mirror_get(dev_id, port_id, &port_mirror);
	port_mirror.bf.in_mirr_en = enable;

	hppe_port_mirror_set(dev_id, port_id, &port_mirror);

	return SW_OK;
}
sw_error_t
adpt_hppe_mirr_port_eg_set(a_uint32_t dev_id, fal_port_t port_id,
                         a_bool_t enable)
{
	union port_mirror_u port_mirror;

	memset(&port_mirror, 0, sizeof(port_mirror));
	ADPT_DEV_ID_CHECK(dev_id);

	hppe_port_mirror_get(dev_id, port_id, &port_mirror);
	port_mirror.bf.eg_mirr_en = enable;

	hppe_port_mirror_set(dev_id, port_id, &port_mirror);

	return SW_OK;
}
sw_error_t
adpt_hppe_mirr_eg_analysis_port_set(a_uint32_t dev_id, fal_port_t port_id)
{
	union mirror_analyzer_u mirror_analyzer;

	memset(&mirror_analyzer, 0, sizeof(mirror_analyzer));
	ADPT_DEV_ID_CHECK(dev_id);


	hppe_mirror_analyzer_get(dev_id, &mirror_analyzer);
	mirror_analyzer.bf.eg_analyzer_port = port_id;

	hppe_mirror_analyzer_set(dev_id, &mirror_analyzer);

	return SW_OK;
}
sw_error_t
adpt_hppe_mirr_analysis_port_set(a_uint32_t dev_id, fal_port_t port_id)
{
	union mirror_analyzer_u mirror_analyzer;

	memset(&mirror_analyzer, 0, sizeof(mirror_analyzer));
	ADPT_DEV_ID_CHECK(dev_id);

	hppe_mirror_analyzer_get(dev_id, &mirror_analyzer);

	mirror_analyzer.bf.in_analyzer_port = port_id;
	mirror_analyzer.bf.eg_analyzer_port = port_id;

	hppe_mirror_analyzer_set(dev_id, &mirror_analyzer);

	return SW_OK;
}
sw_error_t
adpt_hppe_mirr_in_analysis_port_set(a_uint32_t dev_id, fal_port_t port_id)
{
	union mirror_analyzer_u mirror_analyzer;

	memset(&mirror_analyzer, 0, sizeof(mirror_analyzer));
	ADPT_DEV_ID_CHECK(dev_id);

	hppe_mirror_analyzer_get(dev_id, &mirror_analyzer);
	mirror_analyzer.bf.in_analyzer_port = port_id;

	hppe_mirror_analyzer_set(dev_id, &mirror_analyzer);

	return SW_OK;
}
sw_error_t
adpt_hppe_mirr_in_analysis_port_get(a_uint32_t dev_id, fal_port_t *port_id)
{
	sw_error_t rv = SW_OK;
	union mirror_analyzer_u mirror_analyzer;

	memset(&mirror_analyzer, 0, sizeof(mirror_analyzer));
	ADPT_DEV_ID_CHECK(dev_id);


	rv = hppe_mirror_analyzer_get(dev_id, &mirror_analyzer);

	if( rv != SW_OK )
		return rv;

	*port_id = mirror_analyzer.bf.in_analyzer_port;

	return SW_OK;
}

sw_error_t adpt_hppe_mirror_init(a_uint32_t dev_id)
{
	adpt_api_t *p_adpt_api = NULL;

	p_adpt_api = adpt_api_ptr_get(dev_id);

	if(p_adpt_api == NULL)
		return SW_FAIL;

	p_adpt_api->adpt_mirr_eg_analysis_port_get = adpt_hppe_mirr_eg_analysis_port_get;
	p_adpt_api->adpt_mirr_port_in_get = adpt_hppe_mirr_port_in_get;
	p_adpt_api->adpt_mirr_port_eg_get = adpt_hppe_mirr_port_eg_get;
	p_adpt_api->adpt_mirr_analysis_port_get = adpt_hppe_mirr_analysis_port_get;
	p_adpt_api->adpt_mirr_port_in_set = adpt_hppe_mirr_port_in_set;
	p_adpt_api->adpt_mirr_port_eg_set = adpt_hppe_mirr_port_eg_set;
	p_adpt_api->adpt_mirr_eg_analysis_port_set = adpt_hppe_mirr_eg_analysis_port_set;
	p_adpt_api->adpt_mirr_analysis_port_set = adpt_hppe_mirr_analysis_port_set;
	p_adpt_api->adpt_mirr_in_analysis_port_set = adpt_hppe_mirr_in_analysis_port_set;
	p_adpt_api->adpt_mirr_in_analysis_port_get = adpt_hppe_mirr_in_analysis_port_get;


	return SW_OK;
}

/**
 * @}
 */