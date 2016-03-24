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
#ifndef _ADPT_H_
#define _ADPT_H_

#ifdef __cplusplus
extern "C" {
#endif                          /* __cplusplus */

#include "sw.h"
#include "fal_fdb.h"
#include "ssdk_init.h"

#define ADPT_DEV_ID_CHECK(dev_id) \
do { \
    if (dev_id >= SW_MAX_NR_DEV) \
        return SW_OUT_OF_RANGE; \
} while (0)

#define ADPT_PORT_ID_CHECK(port_id) \
do { \
    if (port_id >= SW_MAX_NR_PORT) \
        return SW_OUT_OF_RANGE; \
} while (0)

#define ADPT_NULL_POINT_CHECK(point) \
do { \
    if (point == NULL) \
        return SW_BAD_PTR; \
} while (0)

typedef sw_error_t (*adpt_fdb_first_func)(a_uint32_t dev_id, fal_fdb_entry_t * entry);
typedef sw_error_t (*adpt_fdb_next_func)(a_uint32_t dev_id, fal_fdb_entry_t * entry);
typedef sw_error_t (*adpt_fdb_add_func)(a_uint32_t dev_id, const fal_fdb_entry_t * entry);
typedef sw_error_t (*adpt_fdb_age_time_set_func)(a_uint32_t dev_id, a_uint32_t * time);
typedef sw_error_t (*adpt_fdb_extend_next_func)(a_uint32_t dev_id, fal_fdb_op_t * option,
                        fal_fdb_entry_t * entry);
typedef sw_error_t (*adpt_fdb_age_mode_get_func)(a_uint32_t dev_id, a_uint32_t * age_mode);
typedef sw_error_t (*adpt_fdb_learn_ctrl_get_func)(a_uint32_t dev_id, a_bool_t * enable);
typedef sw_error_t (*adpt_fdb_age_time_get_func)(a_uint32_t dev_id, a_uint32_t * time);
typedef sw_error_t (*adpt_port_fdb_learn_limit_set_func)(a_uint32_t dev_id, fal_port_t port_id,
                                 a_bool_t enable, a_uint32_t cnt);
typedef sw_error_t (*adpt_fdb_learn_mode_set_func)(a_uint32_t dev_id, a_uint32_t learn_mode);
typedef sw_error_t (*adpt_fdb_port_add_func)(a_uint32_t dev_id, a_uint32_t fid, fal_mac_addr_t * addr, fal_port_t port_id);
typedef sw_error_t (*adpt_fdb_port_learn_set_func)(a_uint32_t dev_id, fal_port_t port_id, a_bool_t enable);
typedef sw_error_t (*adpt_fdb_port_learn_get_func)(a_uint32_t dev_id, fal_port_t port_id, a_bool_t *enable);
typedef sw_error_t (*adpt_port_fdb_learn_counter_get_func)(a_uint32_t dev_id, fal_port_t port_id,
                                  a_uint32_t * cnt);
typedef sw_error_t (*adpt_fdb_extend_first_func)(a_uint32_t dev_id, fal_fdb_op_t * option,
                         fal_fdb_entry_t * entry);
typedef sw_error_t (*adpt_fdb_transfer_func)(a_uint32_t dev_id, fal_port_t old_port, fal_port_t new_port,
                     a_uint32_t fid, fal_fdb_op_t * option);
typedef sw_error_t (*adpt_fdb_port_del_func)(a_uint32_t dev_id, a_uint32_t fid, fal_mac_addr_t * addr, fal_port_t port_id);
typedef sw_error_t (*adpt_fdb_find_func)(a_uint32_t dev_id, fal_fdb_entry_t * entry);
typedef sw_error_t (*adpt_fdb_learn_ctrl_set_func)(a_uint32_t dev_id, a_bool_t enable);
typedef sw_error_t (*adpt_port_fdb_learn_exceed_cmd_get_func)(a_uint32_t dev_id, fal_port_t port_id,
                                      fal_fwd_cmd_t * cmd);
typedef sw_error_t (*adpt_fdb_del_by_port_func)(a_uint32_t dev_id, a_uint32_t port_id, a_uint32_t flag);
typedef sw_error_t (*adpt_port_fdb_learn_limit_get_func)(a_uint32_t dev_id, fal_port_t port_id,
                                 a_bool_t * enable, a_uint32_t * cnt);
typedef sw_error_t (*adpt_fdb_age_ctrl_set_func)(a_uint32_t dev_id, a_bool_t enable);
typedef sw_error_t (*adpt_fdb_del_by_mac_func)(a_uint32_t dev_id, const fal_fdb_entry_t *entry);
typedef sw_error_t (*adpt_fdb_iterate_func)(a_uint32_t dev_id, a_uint32_t * iterator, fal_fdb_entry_t * entry);
typedef sw_error_t (*adpt_fdb_learn_mode_get_func)(a_uint32_t dev_id, a_uint32_t * learn_mode);
typedef sw_error_t (*adpt_port_fdb_learn_exceed_cmd_set_func)(a_uint32_t dev_id, fal_port_t port_id,
                                      fal_fwd_cmd_t cmd);
typedef sw_error_t (*adpt_fdb_age_mode_set_func)(a_uint32_t dev_id, a_uint32_t age_mode);
typedef sw_error_t (*adpt_fdb_del_all_func)(a_uint32_t dev_id, a_uint32_t flag);
typedef sw_error_t (*adpt_fdb_age_ctrl_get_func)(a_uint32_t dev_id, a_bool_t * enable);
typedef struct
{
	adpt_fdb_first_func adpt_fdb_first;
	adpt_fdb_next_func adpt_fdb_next;
	adpt_fdb_add_func adpt_fdb_add;
	adpt_fdb_age_time_set_func adpt_fdb_age_time_set;
	adpt_fdb_extend_next_func adpt_fdb_extend_next;
	adpt_fdb_age_mode_get_func adpt_fdb_age_mode_get;
	adpt_fdb_learn_ctrl_get_func adpt_fdb_learn_ctrl_get;
	adpt_fdb_age_time_get_func adpt_fdb_age_time_get;
	adpt_port_fdb_learn_limit_set_func adpt_port_fdb_learn_limit_set;
	adpt_fdb_learn_mode_set_func adpt_fdb_learn_mode_set;
	adpt_fdb_port_add_func adpt_fdb_port_add;
	adpt_fdb_port_learn_set_func adpt_fdb_port_learn_set;
	adpt_fdb_port_learn_get_func adpt_fdb_port_learn_get;
	adpt_port_fdb_learn_counter_get_func adpt_port_fdb_learn_counter_get;
	adpt_fdb_extend_first_func adpt_fdb_extend_first;
	adpt_fdb_transfer_func adpt_fdb_transfer;
	adpt_fdb_port_del_func adpt_fdb_port_del;
	adpt_fdb_find_func adpt_fdb_find;
	adpt_fdb_learn_ctrl_set_func adpt_fdb_learn_ctrl_set;
	adpt_port_fdb_learn_exceed_cmd_get_func adpt_port_fdb_learn_exceed_cmd_get;
	adpt_fdb_del_by_port_func adpt_fdb_del_by_port;
	adpt_port_fdb_learn_limit_get_func adpt_port_fdb_learn_limit_get;
	adpt_fdb_age_ctrl_set_func adpt_fdb_age_ctrl_set;
	adpt_fdb_del_by_mac_func adpt_fdb_del_by_mac;
	adpt_fdb_iterate_func adpt_fdb_iterate;
	adpt_fdb_learn_mode_get_func adpt_fdb_learn_mode_get;
	adpt_port_fdb_learn_exceed_cmd_set_func adpt_port_fdb_learn_exceed_cmd_set;
	adpt_fdb_age_mode_set_func adpt_fdb_age_mode_set;
	adpt_fdb_del_all_func adpt_fdb_del_all;
	adpt_fdb_age_ctrl_get_func adpt_fdb_age_ctrl_get;
}adpt_api_t;


adpt_api_t *adpt_api_ptr_get(a_uint32_t dev_id);
sw_error_t adpt_init(a_uint32_t dev_id, ssdk_init_cfg *cfg);

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif