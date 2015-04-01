/*
 * Copyright (c) 2014, The Linux Foundation. All rights reserved.
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
#ifndef _DESS_INIT_H_
#define _DESS_INIT_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "init/ssdk_init.h"

enum dess_port_cfg {
	PORT_WRAPPER_PSGMII = 0,
	PORT_WRAPPER_PSGMII_RGMII5,
	PORT_WRAPPER_PSGMII_RMII0,
	PORT_WRAPPER_PSGMII_RMII1,
	PORT_WRAPPER_PSGMII_RMII0_RMII1,
	PORT_WRAPPER_PSGMII_RGMII4,
	PORT_WRAPPER_MAX
};



    sw_error_t
    dess_init(a_uint32_t dev_id, ssdk_init_cfg *cfg);


    sw_error_t
    dess_cleanup(a_uint32_t dev_id);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _DESS_INIT_H_ */
/**
 * @}
 */
