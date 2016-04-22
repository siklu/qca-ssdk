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
#include "fal_mib.h"
#include "ssdk_init.h"
#include "fal_type.h"
#include "fal_stp.h"
#include "fal_vsi.h"

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

/*fal_port_t definition,
	bit31-bit24: port_type, 0-physical port, 1-trunk port, 2-virtual port
	bit23-bit0: physical port id or trunk id or virtual port id*/

#define ADPT_PORT_ID_TYPE(port_id) (((port_id)>>24)&0xff)
#define ADPT_PORT_ID_VALUE(port_id) ((port_id)&0xffffff)
#define ADPT_PORT_ID(type, value) (((type)<<24)|(value))

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

typedef sw_error_t (*adpt_mib_cpukeep_get_func)(a_uint32_t dev_id, a_bool_t * enable);
typedef sw_error_t (*adpt_mib_cpukeep_set_func)(a_uint32_t dev_id, a_bool_t  enable);
typedef sw_error_t (*adpt_get_mib_info_func)(a_uint32_t dev_id, fal_port_t port_id,
                     fal_mib_info_t * mib_info );
typedef sw_error_t (*adpt_get_tx_mib_info_func)(a_uint32_t dev_id, fal_port_t port_id,
                     fal_mib_info_t * mib_info );
typedef sw_error_t (*adpt_mib_status_set_func)(a_uint32_t dev_id, a_bool_t enable);
typedef sw_error_t (*adpt_mib_port_flush_counters_func)(a_uint32_t dev_id, fal_port_t port_id);
typedef sw_error_t (*adpt_mib_status_get_func)(a_uint32_t dev_id, a_bool_t * enable);
typedef sw_error_t (*adpt_get_rx_mib_info_func)(a_uint32_t dev_id, fal_port_t port_id,
                     fal_mib_info_t * mib_info );

typedef sw_error_t (*adpt_stp_port_state_get_func)(a_uint32_t dev_id, a_uint32_t st_id,
                     fal_port_t port_id, fal_stp_state_t * state);
typedef sw_error_t (*adpt_stp_port_state_set_func)(a_uint32_t dev_id, a_uint32_t st_id,
                     fal_port_t port_id, fal_stp_state_t state);
typedef sw_error_t (*adpt_port_vlan_vsi_set_func)(a_uint32_t dev_id, fal_port_t port_id, a_uint32_t vlan_id, a_uint32_t vsi_id);
typedef sw_error_t (*adpt_vsi_free_func)(a_uint32_t dev_id, a_uint32_t vsi);
typedef sw_error_t (*adpt_port_vsi_set_func)(a_uint32_t dev_id, fal_port_t port_id, a_uint32_t vsi_id);
typedef sw_error_t (*adpt_vsi_stamove_set_func)(a_uint32_t dev_id, a_uint32_t vsi_id, fal_vsi_stamove_t *stamove);
typedef sw_error_t (*adpt_vsi_stamove_get_func)(a_uint32_t dev_id, a_uint32_t vsi_id, fal_vsi_stamove_t *stamove);
typedef sw_error_t (*adpt_vsi_newaddr_lrn_get_func)(a_uint32_t dev_id, a_uint32_t vsi_id, fal_vsi_newaddr_lrn_t *newaddr_lrn);
typedef sw_error_t (*adpt_port_vsi_get_func)(a_uint32_t dev_id, fal_port_t port_id, a_uint32_t *vsi_id);
typedef sw_error_t (*adpt_vsi_tbl_dump_func)(a_uint32_t dev_id);
typedef sw_error_t (*adpt_vsi_newaddr_lrn_set_func)(a_uint32_t dev_id, a_uint32_t vsi_id, fal_vsi_newaddr_lrn_t *newaddr_lrn);
typedef sw_error_t (*adpt_port_vlan_vsi_get_func)(a_uint32_t dev_id, fal_port_t port_id, a_uint32_t vlan_id, a_uint32_t *vsi_id);
typedef sw_error_t (*adpt_vsi_alloc_func)(a_uint32_t dev_id, a_uint32_t *vsi);
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

	adpt_mib_cpukeep_get_func adpt_mib_cpukeep_get;
	adpt_mib_cpukeep_set_func adpt_mib_cpukeep_set;
	adpt_get_mib_info_func adpt_get_mib_info;
	adpt_get_tx_mib_info_func adpt_get_tx_mib_info;
	adpt_mib_status_set_func adpt_mib_status_set;
	adpt_mib_port_flush_counters_func adpt_mib_port_flush_counters;
	adpt_mib_status_get_func adpt_mib_status_get;
	adpt_get_rx_mib_info_func adpt_get_rx_mib_info;

	adpt_stp_port_state_get_func adpt_stp_port_state_get;
	adpt_stp_port_state_set_func adpt_stp_port_state_set;
	adpt_port_vlan_vsi_set_func adpt_port_vlan_vsi_set;
	adpt_vsi_free_func adpt_vsi_free;
	adpt_port_vsi_set_func adpt_port_vsi_set;
	adpt_vsi_stamove_set_func adpt_vsi_stamove_set;
	adpt_vsi_stamove_get_func adpt_vsi_stamove_get;
	adpt_vsi_newaddr_lrn_get_func adpt_vsi_newaddr_lrn_get;
	adpt_port_vsi_get_func adpt_port_vsi_get;
	adpt_vsi_tbl_dump_func adpt_vsi_tbl_dump;
	adpt_vsi_newaddr_lrn_set_func adpt_vsi_newaddr_lrn_set;
	adpt_port_vlan_vsi_get_func adpt_port_vlan_vsi_get;
	adpt_vsi_alloc_func adpt_vsi_alloc;
}adpt_api_t;


adpt_api_t *adpt_api_ptr_get(a_uint32_t dev_id);
sw_error_t adpt_init(a_uint32_t dev_id, ssdk_init_cfg *cfg);

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif
