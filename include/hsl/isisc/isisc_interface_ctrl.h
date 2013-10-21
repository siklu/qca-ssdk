/*
 * Copyright (c) 2012 Qualcomm Atheros, Inc.
 * All rights reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 *
 */
#ifndef _ISISC_INTERFACE_CTRL_H_
#define _ISISC_INTERFACE_CTRL_H_

#ifdef __cplusplus
extern "C" {
#endif                          /* __cplusplus */

#include "fal/fal_interface_ctrl.h"

    sw_error_t isisc_interface_ctrl_init(a_uint32_t dev_id);

#ifdef IN_INTERFACECONTROL
#define ISISC_INTERFACE_CTRL_INIT(rv, dev_id) \
    { \
        rv = isisc_interface_ctrl_init(dev_id); \
        SW_RTN_ON_ERROR(rv); \
    }
#else
#define ISISC_INTERFACE_CTRL_INIT(rv, dev_id)
#endif

#ifdef HSL_STANDALONG

    HSL_LOCAL sw_error_t
    isisc_port_3az_status_set(a_uint32_t dev_id, fal_port_t port_id, a_bool_t enable);

    HSL_LOCAL sw_error_t
    isisc_port_3az_status_get(a_uint32_t dev_id, fal_port_t port_id, a_bool_t * enable);

    HSL_LOCAL sw_error_t
    isisc_interface_mac_mode_set(a_uint32_t dev_id, fal_port_t port_id, fal_mac_config_t * config);


    HSL_LOCAL sw_error_t
    isisc_interface_mac_mode_get(a_uint32_t dev_id, fal_port_t port_id, fal_mac_config_t * config);

    HSL_LOCAL sw_error_t
    isisc_interface_phy_mode_set(a_uint32_t dev_id, a_uint32_t phy_id, fal_phy_config_t * config);

    HSL_LOCAL sw_error_t
    isisc_interface_phy_mode_get(a_uint32_t dev_id, a_uint32_t phy_id, fal_phy_config_t * config);

    HSL_LOCAL sw_error_t
    isisc_interface_fx100_ctrl_set(a_uint32_t dev_id, fal_fx100_ctrl_config_t* config);

    HSL_LOCAL sw_error_t
    isisc_interface_fx100_ctrl_get(a_uint32_t dev_id, fal_fx100_ctrl_config_t* config);

    HSL_LOCAL sw_error_t
    isisc_interface_fx100_status_get(a_uint32_t dev_id, a_uint32_t* status);

    HSL_LOCAL sw_error_t
    isisc_interface_mac06_exch_set(a_uint32_t dev_id, a_bool_t enable);

    HSL_LOCAL sw_error_t
    isisc_interface_mac06_exch_get(a_uint32_t dev_id, a_bool_t* enable);
#endif

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* _ISISC_INTERFACE_CTRL_H_ */

