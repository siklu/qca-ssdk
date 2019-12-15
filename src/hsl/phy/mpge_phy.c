/*
 * Copyright (c) 2020, The Linux Foundation. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "sw.h"
#include "fal_port_ctrl.h"
#include "hsl_api.h"
#include "hsl.h"
#include "hsl_phy.h"
#include "ssdk_plat.h"
#include "qca808x_phy.h"
#include "mpge_phy.h"

#define PHY_INVALID_DATA 0xffff
#define PHY_RTN_ON_READ_ERROR(phy_data) \
    do { if (phy_data == PHY_INVALID_DATA) return(SW_READ_ERROR); } while(0);

#define PHY_RTN_ON_ERROR(rv) \
    do { if (rv != SW_OK) return(rv); } while(0);

#define MPGE_PHY_ONE_LED_MODE  1
#define MPGE_PHY_TWO_LEDS_MODE 2

/******************************************************************************
*
* mpge_phy_mii_read - mii register read
*
*/
static a_uint16_t
mpge_phy_reg_read (a_uint32_t dev_id, a_uint32_t phy_id, a_uint32_t reg_id)
{
	return qca808x_phy_reg_read (dev_id, phy_id, reg_id);
}

/******************************************************************************
*
* mpge_phy_mii_write - mii register write
*
*/
static sw_error_t
mpge_phy_reg_write (a_uint32_t dev_id, a_uint32_t phy_id, a_uint32_t reg_id,
	a_uint16_t reg_val)
{
	return qca808x_phy_reg_write (dev_id, phy_id, reg_id, reg_val);
}

/******************************************************************************
*
* mpge_phy_debug_read - debug port read
*
*/
static a_uint16_t
mpge_phy_debug_read(a_uint32_t dev_id, a_uint32_t phy_id, a_uint16_t reg_id)
{
	return qca808x_phy_debug_read(dev_id, phy_id, reg_id);
}

/******************************************************************************
*
* mpge_phy_debug_write - debug port write
*
*/
static sw_error_t
mpge_phy_debug_write(a_uint32_t dev_id, a_uint32_t phy_id, a_uint16_t reg_id,
	a_uint16_t reg_val)
{
	return qca808x_phy_debug_write (dev_id, phy_id, reg_id, reg_val);
}

/******************************************************************************
*
* mpge_phy_mmd_read -  PHY MMD register read
*
*/
static a_uint16_t
mpge_phy_mmd_read(a_uint32_t dev_id, a_uint32_t phy_id,
	a_uint16_t mmd_num, a_uint16_t reg_id)
{
	return qca808x_phy_mmd_read(dev_id, phy_id, mmd_num, reg_id);
}

/******************************************************************************
*
* mpge_phy_mmd_write - PHY MMD register write
*
*/
static sw_error_t
mpge_phy_mmd_write(a_uint32_t dev_id, a_uint32_t phy_id,
	a_uint16_t mmd_num, a_uint16_t reg_id, a_uint16_t reg_val)
{
	return qca808x_phy_mmd_write (dev_id, phy_id, mmd_num,
		reg_id, reg_val);
}

/******************************************************************************
*
* mpge_phy_reset - reset the phy
*
*/
static sw_error_t
mpge_phy_reset(a_uint32_t dev_id, a_uint32_t phy_id)
{
	return qca808x_phy_reset(dev_id, phy_id);
}


/******************************************************************************
*
* mpge_phy_get_phy_id - get the phy id
*
*/
static sw_error_t
mpge_phy_get_phy_id(a_uint32_t dev_id, a_uint32_t phy_id,
	a_uint32_t *phy_data)
{
	return qca808x_phy_get_phy_id (dev_id, phy_id, phy_data);
}

/******************************************************************************
*
* mpge_phy_off - power off the phy
*
*/
static sw_error_t
mpge_phy_poweroff(a_uint32_t dev_id, a_uint32_t phy_id)
{
	return qca808x_phy_poweroff (dev_id, phy_id);
}

/******************************************************************************
*
* mpge_phy_on - power on the phy
*
*/
static sw_error_t
mpge_phy_poweron(a_uint32_t dev_id, a_uint32_t phy_id)
{
	return qca808x_phy_poweron (dev_id, phy_id);
}

#ifndef IN_PORTCONTROL_MINI
/******************************************************************************
*
* mpge_phy_set_hibernate - set hibernate status
*
*/
static sw_error_t
mpge_phy_set_hibernate(a_uint32_t dev_id, a_uint32_t phy_id, a_bool_t enable)
{
	return qca808x_phy_set_hibernate (dev_id, phy_id, enable);
}

/******************************************************************************
*
* mpge_phy_get_hibernate - get hibernate status
*
*/
static sw_error_t
mpge_phy_get_hibernate(a_uint32_t dev_id, a_uint32_t phy_id,
	a_bool_t * enable)
{
	return qca808x_phy_get_hibernate (dev_id, phy_id, enable);
}

/******************************************************************************
*
* mpge_phy_cdt - cable diagnostic test
*
*/
static sw_error_t
mpge_phy_cdt(a_uint32_t dev_id, a_uint32_t phy_id, a_uint32_t mdi_pair,
	fal_cable_status_t * cable_status, a_uint32_t * cable_len)
{
	return qca808x_phy_cdt (dev_id, phy_id, mdi_pair,
		cable_status, cable_len);
}

/******************************************************************************
*
* mpge_phy_set_local_loopback
*
*/
static sw_error_t
mpge_phy_set_local_loopback(a_uint32_t dev_id, a_uint32_t phy_id,
	a_bool_t enable)
{
	a_uint16_t phy_data;
	fal_port_speed_t old_speed;
	sw_error_t rv = SW_OK;

	if (enable == A_TRUE)
	{
		mpge_phy_get_speed(dev_id, phy_id, &old_speed);
		if (old_speed == FAL_SPEED_1000)
		{
			phy_data = MPGE_1000M_LOOPBACK;
		}
		else if (old_speed == FAL_SPEED_100)
		{
			phy_data = MPGE_100M_LOOPBACK;
		}
		else if (old_speed == FAL_SPEED_10)
		{
			phy_data = MPGE_10M_LOOPBACK;
		}
		else
		{
			return SW_FAIL;
		}
	}
	else
	{
		phy_data = MPGE_COMMON_CTRL;
	}

	rv = mpge_phy_reg_write(dev_id, phy_id, MPGE_PHY_CONTROL, phy_data);

	return rv;
}

/******************************************************************************
*
* mpge_phy_get_local_loopback
*
*/
static sw_error_t
mpge_phy_get_local_loopback(a_uint32_t dev_id, a_uint32_t phy_id,
	a_bool_t * enable)
{
	return qca808x_phy_get_local_loopback (dev_id, phy_id, enable);
}

/******************************************************************************
*
* mpge_phy_set_remote_loopback
*
*/
static sw_error_t
mpge_phy_set_remote_loopback(a_uint32_t dev_id, a_uint32_t phy_id,
	a_bool_t enable)
{
	return qca808x_phy_set_remote_loopback (dev_id, phy_id, enable);
}

/******************************************************************************
*
* mpge_phy_get_remote_loopback
*
*/
static sw_error_t
mpge_phy_get_remote_loopback(a_uint32_t dev_id, a_uint32_t phy_id,
	a_bool_t * enable)
{
	return qca808x_phy_get_remote_loopback (dev_id, phy_id, enable);

}

/******************************************************************************
*
* mpge_phy_set_802.3az
*
*/
static sw_error_t
mpge_phy_set_8023az(a_uint32_t dev_id, a_uint32_t phy_id, a_bool_t enable)
{
	return qca808x_phy_set_8023az (dev_id, phy_id, enable);
}

/******************************************************************************
*
* mpge_phy_get_8023az status
*
*/
static sw_error_t
mpge_phy_get_8023az(a_uint32_t dev_id, a_uint32_t phy_id, a_bool_t * enable)
{
	return qca808x_phy_get_8023az (dev_id, phy_id, enable);
}

/******************************************************************************
*
* mpge_phy_set wol-frame mac address
*
*/
static sw_error_t
mpge_phy_set_magic_frame_mac(a_uint32_t dev_id, a_uint32_t phy_id,
	fal_mac_addr_t * mac)
{
	return qca808x_phy_set_magic_frame_mac (dev_id, phy_id, mac);
}

/******************************************************************************
*
* mpge_phy_get wol - frame mac address
*
*/
static sw_error_t
mpge_phy_get_magic_frame_mac(a_uint32_t dev_id, a_uint32_t phy_id,
	fal_mac_addr_t * mac)
{
	return qca808x_phy_get_magic_frame_mac (dev_id, phy_id, mac);
}

/******************************************************************************
*
* mpge_phy_set wol - enable or disable
*
*/
static sw_error_t
mpge_phy_set_wol_status(a_uint32_t dev_id, a_uint32_t phy_id, a_bool_t enable)
{
	return qca808x_phy_set_wol_status (dev_id, phy_id, enable);
}

/******************************************************************************
*
* mpge_phy_get_wol status - get wol status
*
*/
static sw_error_t
mpge_phy_get_wol_status(a_uint32_t dev_id, a_uint32_t phy_id, a_bool_t * enable)
{
	return qca808x_phy_get_wol_status (dev_id, phy_id, enable);
}

/******************************************************************************
*
* mpge_phy_set_counter - set counter status
*
*/
static sw_error_t
mpge_phy_set_counter(a_uint32_t dev_id, a_uint32_t phy_id, a_bool_t enable)
{
	return qca808x_phy_set_counter (dev_id, phy_id, enable);
}

/******************************************************************************
*
* mpge_phy_get_counter_status - get counter status
*
*/
static sw_error_t
mpge_phy_get_counter(a_uint32_t dev_id, a_uint32_t phy_id,
	a_bool_t * enable)
{
	return qca808x_phy_get_counter (dev_id, phy_id, enable);
}

/******************************************************************************
*
* mpge_phy_show show - counter statistics
*
*/
static sw_error_t
mpge_phy_show_counter(a_uint32_t dev_id, a_uint32_t phy_id,
	fal_port_counter_info_t * counter_infor)
{
	return qca808x_phy_show_counter (dev_id, phy_id, counter_infor);
}

/******************************************************************************
*
* mpge_phy_set_intr_mask - Set interrupt mask with the
* specified device.
*/
sw_error_t
mpge_phy_set_intr_mask(a_uint32_t dev_id, a_uint32_t phy_id,
	a_uint32_t intr_mask_flag)
{
	a_uint16_t phy_data = 0;
	sw_error_t rv = SW_OK;

	phy_data = mpge_phy_reg_read(dev_id, phy_id, MPGE_PHY_INTR_MASK);
	PHY_RTN_ON_READ_ERROR(phy_data);

	if (intr_mask_flag & FAL_PHY_INTR_STATUS_UP_CHANGE) {
		phy_data |= MPGE_INTR_STATUS_LINK_UP;
	} else {
		phy_data &= (~MPGE_INTR_STATUS_LINK_UP);
	}

	if (intr_mask_flag & FAL_PHY_INTR_STATUS_DOWN_CHANGE) {
		phy_data |= MPGE_INTR_STATUS_LINK_DOWN;
	} else {
		phy_data &= (~MPGE_INTR_STATUS_LINK_DOWN);
	}

	if (intr_mask_flag & FAL_PHY_INTR_SPEED_CHANGE) {
		phy_data |= MPGE_INTR_SPEED_CHANGE;
	} else {
		phy_data &= (~MPGE_INTR_SPEED_CHANGE);
	}

	if (intr_mask_flag & FAL_PHY_INTR_DUPLEX_CHANGE) {
		phy_data |= MPGE_INTR_DUPLEX_CHANGE;
	} else {
		phy_data &= (~MPGE_INTR_DUPLEX_CHANGE);
	}

	if (intr_mask_flag & FAL_PHY_INTR_WOL_STATUS) {
		phy_data |= MPGE_INTR_WOL;
	} else {
		phy_data &= (~MPGE_INTR_WOL);
	}

	rv = mpge_phy_reg_write(dev_id, phy_id, MPGE_PHY_INTR_MASK, phy_data);

	return rv;
}

/******************************************************************************
*
* mpge_phy_get_intr_mask - Get interrupt mask with the
* specified device.
*/
sw_error_t
mpge_phy_get_intr_mask(a_uint32_t dev_id, a_uint32_t phy_id,
	a_uint32_t * intr_mask_flag)
{
	a_uint16_t phy_data = 0;

	phy_data = mpge_phy_reg_read(dev_id, phy_id, MPGE_PHY_INTR_MASK);
	PHY_RTN_ON_READ_ERROR(phy_data);

	*intr_mask_flag = 0;
	if (phy_data & MPGE_INTR_STATUS_LINK_UP) {
		*intr_mask_flag |= FAL_PHY_INTR_STATUS_UP_CHANGE;
	}

	if (phy_data & MPGE_INTR_STATUS_LINK_DOWN) {
		*intr_mask_flag |= FAL_PHY_INTR_STATUS_DOWN_CHANGE;
	}

	if (phy_data & MPGE_INTR_SPEED_CHANGE) {
		*intr_mask_flag |= FAL_PHY_INTR_SPEED_CHANGE;
	}

	if (phy_data & MPGE_INTR_DUPLEX_CHANGE) {
		*intr_mask_flag |= FAL_PHY_INTR_DUPLEX_CHANGE;
	}

	if (phy_data & MPGE_INTR_WOL) {
		*intr_mask_flag |= FAL_PHY_INTR_WOL_STATUS;
	}

	return SW_OK;
}

/******************************************************************************
*
* mpge_phy_get_intr_status - Get interrupt status with the
* specified device.
*/
sw_error_t
mpge_phy_get_intr_status(a_uint32_t dev_id, a_uint32_t phy_id,
	a_uint32_t * intr_status_flag)
{
	a_uint16_t phy_data = 0;

	phy_data = mpge_phy_reg_read(dev_id, phy_id, MPGE_PHY_INTR_STATUS);
	PHY_RTN_ON_READ_ERROR(phy_data);

	*intr_status_flag = 0;
	if (phy_data & MPGE_INTR_STATUS_LINK_UP) {
		*intr_status_flag |= FAL_PHY_INTR_STATUS_UP_CHANGE;
	}

	if (phy_data & MPGE_INTR_STATUS_LINK_DOWN) {
		*intr_status_flag |= FAL_PHY_INTR_STATUS_DOWN_CHANGE;
	}

	if (phy_data & MPGE_INTR_SPEED_CHANGE) {
		*intr_status_flag |= FAL_PHY_INTR_SPEED_CHANGE;
	}

	if (phy_data & MPGE_INTR_DUPLEX_CHANGE) {
		*intr_status_flag |= FAL_PHY_INTR_DUPLEX_CHANGE;
	}

	if (phy_data & MPGE_INTR_WOL) {
		*intr_status_flag |= FAL_PHY_INTR_WOL_STATUS;
	}

	return SW_OK;
}
#endif

/******************************************************************************
*
* mpge_phy_set_eee_advertisement
*
*/
static sw_error_t
mpge_phy_set_eee_adv(a_uint32_t dev_id, a_uint32_t phy_id,
	a_uint32_t adv)
{
	return qca808x_phy_set_eee_adv (dev_id, phy_id, adv);
}

/******************************************************************************
*
* mpge_phy_get_eee_advertisement
*
*/
static sw_error_t
mpge_phy_get_eee_adv(a_uint32_t dev_id, a_uint32_t phy_id,
	a_uint32_t *adv)
{
	return qca808x_phy_get_eee_adv (dev_id, phy_id, adv);
}

/******************************************************************************
*
* mpge_phy_get_eee_partner_advertisement
*
*/
static sw_error_t
mpge_phy_get_eee_partner_adv(a_uint32_t dev_id, a_uint32_t phy_id,
	a_uint32_t *adv)
{
	return qca808x_phy_get_eee_partner_adv (dev_id, phy_id, adv);
}

/******************************************************************************
*
* mpge_phy_get_eee_capability
*
*/
static sw_error_t
mpge_phy_get_eee_cap(a_uint32_t dev_id, a_uint32_t phy_id,
	a_uint32_t *cap)
{
	return qca808x_phy_get_eee_cap (dev_id, phy_id, cap);
}

/******************************************************************************
*
* mpge_phy_get_eee_status - get eee status
*
*/
static sw_error_t
mpge_phy_get_eee_status(a_uint32_t dev_id, a_uint32_t phy_id,
	a_uint32_t *status)
{
	return qca808x_phy_get_eee_status (dev_id, phy_id, status);
}

/******************************************************************************
*
* mpge_phy_led_set - set led behavior
*
* set led behavior
*/
static sw_error_t
mpge_phy_led_set(a_uint32_t dev_id, a_uint32_t phy_id,
	a_uint32_t led_mode)
{
	sw_error_t rv = SW_OK;
	a_uint32_t mpge_phy_pin0_ctrl =0, mpge_phy_pin1_ctrl = 0,
		mpge_phy_pin2_ctrl = 0;
	/*MPGE_PHY_ONE_LED_MODE use only one pin for one LED
		MPGE_PHY_TWO_LEDS_MODE use three pins for two LEDs*/
	if(led_mode == MPGE_PHY_ONE_LED_MODE)
	{
		mpge_phy_pin0_ctrl = MPGE_PHY_MMD7_MODE1_PIN0_CTRL;
		mpge_phy_pin1_ctrl = MPGE_PHY_MMD7_MODE1_PIN1_CTRL;
		mpge_phy_pin2_ctrl = MPGE_PHY_MMD7_MODE1_PIN2_CTRL;
	}
	else
	{
		mpge_phy_pin0_ctrl = MPGE_PHY_MMD7_MODE2_PIN0_CTRL;
		mpge_phy_pin1_ctrl = MPGE_PHY_MMD7_MODE2_PIN1_CTRL;
		mpge_phy_pin2_ctrl = MPGE_PHY_MMD7_MODE2_PIN2_CTRL;
	}
	rv = mpge_phy_mmd_write(dev_id, phy_id, MPGE_PHY_MMD7_NUM,
		MPGE_PHY_MMD7_LED0_CTRL,
		mpge_phy_pin0_ctrl);
	SW_RTN_ON_ERROR(rv);

	rv = mpge_phy_mmd_write(dev_id, phy_id, MPGE_PHY_MMD7_NUM,
		MPGE_PHY_MMD7_LED1_CTRL,
		mpge_phy_pin1_ctrl);
	SW_RTN_ON_ERROR(rv);

	rv = mpge_phy_mmd_write(dev_id, phy_id, MPGE_PHY_MMD7_NUM,
		MPGE_PHY_MMD7_LED2_CTRL,
		mpge_phy_pin2_ctrl);

	return rv;
}

/******************************************************************************
*
* mpge_phy_led_init - init led mode
*
* set led mode
*/
static sw_error_t
mpge_phy_led_init(a_uint32_t dev_id, a_uint32_t phy_id)
{
	sw_error_t rv = SW_OK;

	rv = mpge_phy_led_set(dev_id, phy_id, MPGE_PHY_ONE_LED_MODE);

	return rv;
}

/******************************************************************************
*
* mpge_phy_cdt_thresh_set - set CDT threshold
*
* set CDT threshold
*/
static sw_error_t
mpge_phy_cdt_thresh_init(a_uint32_t dev_id, a_uint32_t phy_id)
{
	sw_error_t rv = SW_OK;

	rv = mpge_phy_mmd_write(dev_id, phy_id, MPGE_PHY_MMD3_NUM,
		MPGE_PHY_MMD3_CDT_THRESH_CTRL3,
		MPGE_PHY_MMD3_CDT_THRESH_CTRL3_VAL);
	SW_RTN_ON_ERROR(rv);
	rv = mpge_phy_mmd_write(dev_id, phy_id, MPGE_PHY_MMD3_NUM,
		MPGE_PHY_MMD3_CDT_THRESH_CTRL4,
		MPGE_PHY_MMD3_CDT_THRESH_CTRL4_VAL);
	SW_RTN_ON_ERROR(rv);
	rv = mpge_phy_mmd_write(dev_id, phy_id, MPGE_PHY_MMD3_NUM,
		MPGE_PHY_MMD3_CDT_THRESH_CTRL5,
		MPGE_PHY_MMD3_CDT_THRESH_CTRL5_VAL);
	SW_RTN_ON_ERROR(rv);
	rv = mpge_phy_mmd_write(dev_id, phy_id, MPGE_PHY_MMD3_NUM,
		MPGE_PHY_MMD3_CDT_THRESH_CTRL6,
		MPGE_PHY_MMD3_CDT_THRESH_CTRL6_VAL);
	SW_RTN_ON_ERROR(rv);
	rv = mpge_phy_mmd_write(dev_id, phy_id, MPGE_PHY_MMD3_NUM,
		MPGE_PHY_MMD3_CDT_THRESH_CTRL7,
		MPGE_PHY_MMD3_CDT_THRESH_CTRL7_VAL);
	SW_RTN_ON_ERROR(rv);
	rv = mpge_phy_mmd_write(dev_id, phy_id, MPGE_PHY_MMD3_NUM,
		MPGE_PHY_MMD3_CDT_THRESH_CTRL9,
		MPGE_PHY_MMD3_CDT_THRESH_CTRL9_VAL);
	SW_RTN_ON_ERROR(rv);
	rv = mpge_phy_mmd_write(dev_id, phy_id, MPGE_PHY_MMD3_NUM,
		MPGE_PHY_MMD3_CDT_THRESH_CTRL13,
		MPGE_PHY_MMD3_CDT_THRESH_CTRL13_VAL);

	return rv;
}

/******************************************************************************
*
* mpge_phy_adc_set - set ADC metastability
*
* set ADC metastability
*/
static sw_error_t
mpge_phy_adc_init(a_uint32_t dev_id, a_uint32_t phy_id)
{
	sw_error_t rv = SW_OK;

	rv = mpge_phy_debug_write(dev_id, phy_id, AFE50_ADC_2_DP,
		AFE50_ADC_2_DP_VAL);
	SW_RTN_ON_ERROR(rv);
	rv = mpge_phy_debug_write(dev_id, phy_id, AFE50_ADC_4_DP,
		AFE50_ADC_4_DP_VAL);
	SW_RTN_ON_ERROR(rv);
	rv = mpge_phy_debug_write(dev_id, phy_id, AFE50_ADC_7_DP,
		AFE50_ADC_7_DP_VAL);
	SW_RTN_ON_ERROR(rv);
	rv = mpge_phy_debug_write(dev_id, phy_id, AFE50_ADC_14_DP,
		AFE50_ADC_14_DP_VAL);

	return rv;
}

/******************************************************************************
*
* mpge_phy_function_reset - do function reset
*
*/
static sw_error_t
mpge_phy_function_reset(a_uint32_t dev_id, a_uint32_t phy_id,
	hsl_phy_function_reset_t phy_reset_type)
{
	a_uint16_t phy_data = 0;
	sw_error_t rv = SW_OK;

	switch (phy_reset_type)
	{
		case PHY_FIFO_RESET:
			phy_data = mpge_phy_reg_read (dev_id, phy_id, MPGE_PHY_FIFO_CONTROL);
			PHY_RTN_ON_READ_ERROR(phy_data);

			rv = mpge_phy_reg_write(dev_id, phy_id, MPGE_PHY_FIFO_CONTROL,
				phy_data & (~MPGE_PHY_FIFO_RESET));
			SW_RTN_ON_ERROR(rv);

			aos_mdelay(50);

			rv = mpge_phy_reg_write(dev_id, phy_id, MPGE_PHY_FIFO_CONTROL,
			phy_data | MPGE_PHY_FIFO_RESET);
			SW_RTN_ON_ERROR(rv);
			break;
		default:
			return SW_NOT_SUPPORTED;
	}

	return rv;
}

static void
mpge_phy_lock_init(void)
{
	return qca808x_phy_lock_init();
}

static sw_error_t
mpge_phy_hw_init(a_uint32_t dev_id,  a_uint32_t port_bmp)
{
	a_uint32_t port_id = 0, phy_addr = 0;
	sw_error_t rv = SW_OK;

	for (port_id = SSDK_PHYSICAL_PORT0; port_id < SW_MAX_NR_PORT; port_id ++)
	{
		if (port_bmp & (0x1 << port_id))
		{
			phy_addr = qca_ssdk_port_to_phy_addr(dev_id, port_id);
			/*configure LED mode*/
			rv = mpge_phy_led_init(dev_id, phy_addr);
			SW_RTN_ON_ERROR(rv);
			/*configure the CDT threshold*/
			rv = mpge_phy_cdt_thresh_init (dev_id, phy_addr);
			SW_RTN_ON_ERROR(rv);
			/*ADC metastability*/
			rv = mpge_phy_adc_init (dev_id, phy_addr);
			SW_RTN_ON_ERROR(rv);
			/*special configuration for AZ*/
			rv = mpge_phy_mmd_write(dev_id, phy_addr, MPGE_PHY_MMD3_NUM,
				MPGE_PHY_MMD3_AZ_CTRL1, MPGE_PHY_MMD3_AZ_CTRL1_VAL);
			SW_RTN_ON_ERROR(rv);
			rv = mpge_phy_mmd_write(dev_id, phy_addr, MPGE_PHY_MMD3_NUM,
				MPGE_PHY_MMD3_AZ_CTRL2, MPGE_PHY_MMD3_AZ_CTRL2_VAL);
			SW_RTN_ON_ERROR(rv);
			/*configure MSE threshold and over threshold times*/
			rv = mpge_phy_mmd_write(dev_id, phy_addr, MPGE_PHY_MMD1_NUM,
				MPGE_PHY_MMD1_MSE_THRESH1, MPGE_PHY_MMD1_MSE_THRESH1_VAL);
			SW_RTN_ON_ERROR(rv);
			rv = mpge_phy_mmd_write(dev_id, phy_addr, MPGE_PHY_MMD1_NUM,
				MPGE_PHY_MMD1_MSE_THRESH2, MPGE_PHY_MMD1_MSE_THRESH2_VAL);
			SW_RTN_ON_ERROR(rv);
		}
	}

	return rv;
}

static sw_error_t mpge_phy_api_ops_init(void)
{
	sw_error_t ret = SW_OK;
	hsl_phy_ops_t *mpge_phy_api_ops = NULL;

	mpge_phy_api_ops = kzalloc(sizeof(hsl_phy_ops_t), GFP_KERNEL);
	if (mpge_phy_api_ops == NULL)
	{
		SSDK_ERROR("mpge phy ops kzalloc failed!\n");
		return -ENOMEM;
	}

	phy_api_ops_init(MPGE_PHY_CHIP);

	mpge_phy_api_ops->phy_reg_write = mpge_phy_reg_write;
	mpge_phy_api_ops->phy_reg_read = mpge_phy_reg_read;
	mpge_phy_api_ops->phy_debug_write = mpge_phy_debug_write;
	mpge_phy_api_ops->phy_debug_read = mpge_phy_debug_read;
	mpge_phy_api_ops->phy_mmd_write = mpge_phy_mmd_write;
	mpge_phy_api_ops->phy_mmd_read = mpge_phy_mmd_read;
	mpge_phy_api_ops->phy_reset = mpge_phy_reset;
	mpge_phy_api_ops->phy_id_get = mpge_phy_get_phy_id;
	mpge_phy_api_ops->phy_power_off = mpge_phy_poweroff;
	mpge_phy_api_ops->phy_power_on = mpge_phy_poweron;
#ifndef IN_PORTCONTROL_MINI
	mpge_phy_api_ops->phy_cdt = mpge_phy_cdt;
	mpge_phy_api_ops->phy_local_loopback_set = mpge_phy_set_local_loopback;
	mpge_phy_api_ops->phy_local_loopback_get = mpge_phy_get_local_loopback;
	mpge_phy_api_ops->phy_remote_loopback_set = mpge_phy_set_remote_loopback;
	mpge_phy_api_ops->phy_remote_loopback_get = mpge_phy_get_remote_loopback;
	mpge_phy_api_ops->phy_8023az_set = mpge_phy_set_8023az;
	mpge_phy_api_ops->phy_8023az_get = mpge_phy_get_8023az;
	mpge_phy_api_ops->phy_hibernation_set = mpge_phy_set_hibernate;
	mpge_phy_api_ops->phy_hibernation_get = mpge_phy_get_hibernate;
	mpge_phy_api_ops->phy_magic_frame_mac_set = mpge_phy_set_magic_frame_mac;
	mpge_phy_api_ops->phy_magic_frame_mac_get = mpge_phy_get_magic_frame_mac;
	mpge_phy_api_ops->phy_counter_set = mpge_phy_set_counter;
	mpge_phy_api_ops->phy_counter_get = mpge_phy_get_counter;
	mpge_phy_api_ops->phy_counter_show = mpge_phy_show_counter;
	mpge_phy_api_ops->phy_wol_status_set = mpge_phy_set_wol_status;
	mpge_phy_api_ops->phy_wol_status_get = mpge_phy_get_wol_status;
	mpge_phy_api_ops->phy_intr_mask_set = mpge_phy_set_intr_mask;
	mpge_phy_api_ops->phy_intr_mask_get = mpge_phy_get_intr_mask;
	mpge_phy_api_ops->phy_intr_status_get = mpge_phy_get_intr_status;
#endif
	mpge_phy_api_ops->phy_eee_adv_set = mpge_phy_set_eee_adv;
	mpge_phy_api_ops->phy_eee_adv_get = mpge_phy_get_eee_adv;
	mpge_phy_api_ops->phy_eee_partner_adv_get = mpge_phy_get_eee_partner_adv;
	mpge_phy_api_ops->phy_eee_cap_get = mpge_phy_get_eee_cap;
	mpge_phy_api_ops->phy_eee_status_get = mpge_phy_get_eee_status;
	mpge_phy_api_ops->phy_function_reset = mpge_phy_function_reset;
	ret = hsl_phy_api_ops_register(MPGE_PHY_CHIP, mpge_phy_api_ops);

	if (ret == SW_OK)
	{
		SSDK_INFO("qca probe mpge phy driver succeeded!\n");
	}
	else
	{
		SSDK_ERROR("qca probe mpge phy driver failed! (code: %d)\n", ret);
	}

	return ret;
}

/******************************************************************************
*
* mpge_phy_init -
*
*/
int mpge_phy_init(a_uint32_t dev_id, a_uint32_t port_bmp)
{
	a_int32_t ret = 0;
	static a_bool_t phy_ops_flag = A_FALSE;

	if(phy_ops_flag == A_FALSE &&
			mpge_phy_api_ops_init() == SW_OK) {
		mpge_phy_lock_init();
		phy_ops_flag = A_TRUE;
	}
	mpge_phy_hw_init(dev_id, port_bmp);

	return ret;
}
