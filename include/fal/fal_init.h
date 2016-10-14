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
 * @defgroup fal_init FAL_INIT
 * @{
 */
#ifndef _FAL_INIT_H_
#define _FAL_INIT_H_

#ifdef __cplusplus
extern "C" {
#endif                          /* __cplusplus */

#include "init/ssdk_init.h"

enum{
	FAL_MODULE_ACL,
	FAL_MODULE_VSI,
	FAL_MODULE_IP,
	FAL_MODULE_FLOW,
	FAL_MODULE_QM,
	FAL_MODULE_QOS,
	FAL_MODULE_BM,
	FAL_MODULE_MAX,
};

typedef struct
{
	a_uint32_t bitmap[3];
}fal_func_ctrl_t;

sw_error_t fal_init(a_uint32_t dev_id, ssdk_init_cfg * cfg);
sw_error_t fal_reset(a_uint32_t dev_id);
sw_error_t fal_ssdk_cfg(a_uint32_t dev_id, ssdk_cfg_t *ssdk_cfg);
sw_error_t fal_cleanup(void);
sw_error_t fal_module_func_ctrl_set(a_uint32_t dev_id,
		a_uint32_t module, fal_func_ctrl_t *func_ctrl);
sw_error_t fal_module_func_ctrl_get(a_uint32_t dev_id,
		a_uint32_t module, fal_func_ctrl_t *func_ctrl);

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* _FAL_INIT_H_ */
/**
 * @}
 */
