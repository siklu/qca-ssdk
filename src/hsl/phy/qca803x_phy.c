/*
 * Copyright (c) 2017, The Linux Foundation. All rights reserved.
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
#include "sw.h"
#include "fal_port_ctrl.h"
#include "hsl_api.h"
#include "hsl.h"
#include "qca803x_phy.h"
#include "hsl_phy.h"
#include <linux/kconfig.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/phy.h>
#if defined(CONFIG_OF) && (LINUX_VERSION_CODE >= KERNEL_VERSION(3,14,0))
#include <linux/switch.h>
#else
#include <net/switch.h>
#endif
#include "ssdk_plat.h"

/******************************************************************************
*
* qca803x_phy_mii_read - mii register read
*
* mii register read
*/
a_uint16_t
qca803x_phy_reg_read(a_uint32_t dev_id, a_uint32_t phy_id, a_uint32_t reg_id)
{
	sw_error_t rv = SW_OK;
	a_uint16_t phy_data = 0;

	HSL_PHY_GET(rv, dev_id, phy_id, reg_id, &phy_data);
	if (SW_OK != rv) {
		return rv;
	}

	return phy_data;
}

/******************************************************************************
*
* qca803x_phy_mii_write - mii register write
*
* mii register write
*/
sw_error_t
qca803x_phy_reg_write(a_uint32_t dev_id, a_uint32_t phy_id, a_uint32_t reg_id,
		       a_uint16_t reg_val)
{
	sw_error_t rv;

	HSL_PHY_SET(rv, dev_id, phy_id, reg_id, reg_val);

	return rv;

}
/******************************************************************************
*
* qca803x_phy_get_speed - Determines the speed of phy ports associated with the
* specified device.
*/

sw_error_t
qca803x_phy_get_speed(a_uint32_t dev_id, a_uint32_t phy_id,
		     fal_port_speed_t * speed)
{
	a_uint16_t phy_data;
	sw_error_t rv = SW_OK;

	phy_data = qca803x_phy_reg_read(dev_id, phy_id, QCA803X_PHY_SPEC_STATUS);

	switch (phy_data & QCA803X_STATUS_SPEED_MASK)
	{
		case QCA803X_STATUS_SPEED_1000MBS:
			*speed = FAL_SPEED_1000;
			break;
		case QCA803X_STATUS_SPEED_100MBS:
			*speed = FAL_SPEED_100;
			break;
		case QCA803X_STATUS_SPEED_10MBS:
			*speed = FAL_SPEED_10;
			break;
		default:
			return SW_READ_ERROR;
	}

	return rv;
}

/******************************************************************************
*
* qca803x_phy_get_duplex - Determines the speed of phy ports associated with the
* specified device.
*/
sw_error_t
qca803x_phy_get_duplex(a_uint32_t dev_id, a_uint32_t phy_id,
		      fal_port_duplex_t * duplex)
{
	a_uint16_t phy_data;
	sw_error_t rv = SW_OK;

	phy_data = qca803x_phy_reg_read(dev_id, phy_id, QCA803X_PHY_SPEC_STATUS);

	//read duplex
	if (phy_data & QCA803X_STATUS_FULL_DUPLEX)
		*duplex = FAL_FULL_DUPLEX;
	else
		*duplex = FAL_HALF_DUPLEX;

	return rv;
}

/******************************************************************************
*
* qca803x_phy_reset - reset the phy
*
* reset the phy
*/
sw_error_t qca803x_phy_reset(a_uint32_t dev_id, a_uint32_t phy_id)
{
	a_uint16_t phy_data;
	sw_error_t rv = SW_OK;

	phy_data = qca803x_phy_reg_read(dev_id, phy_id, QCA803X_PHY_CONTROL);
	rv = qca803x_phy_reg_write(dev_id, phy_id, QCA803X_PHY_CONTROL,
			     phy_data | QCA803X_CTRL_SOFTWARE_RESET);

	return rv;
}
/******************************************************************************
*
* qca803x_phy_status - test to see if the specified phy link is alive
*
* RETURNS:
*    A_TRUE  --> link is alive
*    A_FALSE --> link is down
*/
a_bool_t qca803x_phy_get_link_status(a_uint32_t dev_id, a_uint32_t phy_id)
{
	a_uint16_t phy_data;
	a_bool_t rv = A_TRUE;
	phy_data = qca803x_phy_reg_read(dev_id, phy_id, QCA803X_PHY_SPEC_STATUS);

	if (phy_data & QCA803X_STATUS_LINK_PASS) {
		rv = A_TRUE;
	} else {
		rv = A_FALSE;
	}
	return rv;
}
/******************************************************************************
*
* qca803x_restart_autoneg - restart the phy autoneg
*
*/
sw_error_t qca803x_phy_restart_autoneg(a_uint32_t dev_id, a_uint32_t phy_id)
{
	a_uint16_t phy_data = 0;
	sw_error_t rv = SW_OK;

	phy_data = qca803x_phy_reg_read(dev_id, phy_id, QCA803X_PHY_CONTROL);
	phy_data |= QCA803X_CTRL_AUTONEGOTIATION_ENABLE;
	rv = qca803x_phy_reg_write(dev_id, phy_id, QCA803X_PHY_CONTROL,
			     phy_data | QCA803X_CTRL_RESTART_AUTONEGOTIATION);

	return rv;
}
/******************************************************************************
*
* qca803x_phy_enable_autonego
*
*/
sw_error_t qca803x_phy_enable_autoneg(a_uint32_t dev_id, a_uint32_t phy_id)
{
	a_uint16_t phy_data = 0;
	sw_error_t rv = SW_OK;

	phy_data = qca803x_phy_reg_read(dev_id, phy_id, QCA803X_PHY_CONTROL);
	rv = qca803x_phy_reg_write(dev_id, phy_id, QCA803X_PHY_CONTROL,
			     phy_data | QCA803X_CTRL_AUTONEGOTIATION_ENABLE);

	return rv;
}

/******************************************************************************
*
* qca803x_phy_set_speed - Determines the speed of phy ports associated with the
* specified device.
*/
sw_error_t
qca803x_phy_set_speed(a_uint32_t dev_id, a_uint32_t phy_id,
		     fal_port_speed_t speed)
{
	a_uint16_t phy_data = 0;
	fal_port_duplex_t old_duplex;
	sw_error_t rv = SW_OK;

	phy_data = qca803x_phy_reg_read(dev_id, phy_id, QCA803X_PHY_CONTROL);
	rv = qca803x_phy_get_duplex(dev_id, phy_id, &old_duplex);
	if(rv != SW_OK) {
		return rv;
	}

	if (old_duplex == FAL_FULL_DUPLEX) {
		phy_data |= QCA803X_CTRL_FULL_DUPLEX;
		switch(speed)
		{
			case FAL_SPEED_1000:
				phy_data |= QCA803X_CTRL_SPEED_1000;
				phy_data &= ~QCA803X_CTRL_SPEED_100;
				phy_data |= QCA803X_CTRL_AUTONEGOTIATION_ENABLE;
				break;
			case FAL_SPEED_100:
			case FAL_SPEED_10:
				phy_data &= ~QCA803X_CTRL_SPEED_1000;
				phy_data &= ~QCA803X_CTRL_AUTONEGOTIATION_ENABLE;
				if (FAL_SPEED_100 == speed) {
					phy_data |= QCA803X_CTRL_SPEED_100;
				} else {
					phy_data &= ~QCA803X_CTRL_SPEED_100;
				}
				break;
			default:
				return SW_BAD_PARAM;
		}
	} else if (old_duplex == FAL_HALF_DUPLEX) {
		phy_data &= ~QCA803X_CTRL_FULL_DUPLEX;
		switch(speed)
		{
			case FAL_SPEED_100:
			case FAL_SPEED_10:
				phy_data &= ~QCA803X_CTRL_SPEED_1000;
				phy_data &= ~QCA803X_CTRL_AUTONEGOTIATION_ENABLE;
				if (FAL_SPEED_100 == speed) {
					phy_data |= QCA803X_CTRL_SPEED_100;
				} else {
					phy_data &= ~QCA803X_CTRL_SPEED_100;
				}
				break;
			case FAL_SPEED_1000:
				phy_data |= QCA803X_CTRL_FULL_DUPLEX;
				phy_data |= QCA803X_CTRL_SPEED_1000;
				phy_data &= ~QCA803X_CTRL_SPEED_100;
				phy_data |= QCA803X_CTRL_AUTONEGOTIATION_ENABLE;
				break;
			default:
				return SW_BAD_PARAM;
		}
	} else {
		return SW_FAIL;
	}
	rv = qca803x_phy_reg_write(dev_id, phy_id, QCA803X_PHY_CONTROL, phy_data);

	return rv;
}

/******************************************************************************
*
* qca803x_phy_set_duplex - Determines the speed of phy ports associated with the
* specified device.
*/
sw_error_t
qca803x_phy_set_duplex(a_uint32_t dev_id, a_uint32_t phy_id,
		      fal_port_duplex_t duplex)
{
	a_uint16_t phy_data = 0;
	fal_port_speed_t old_speed;
	sw_error_t rv = SW_OK;

	phy_data = qca803x_phy_reg_read(dev_id, phy_id, QCA803X_PHY_CONTROL);
	qca803x_phy_get_speed(dev_id, phy_id, &old_speed);
	switch(old_speed)
	{
		case FAL_SPEED_1000:
			phy_data |= QCA803X_CTRL_SPEED_1000;
			phy_data &= ~QCA803X_CTRL_SPEED_100;
			phy_data |= QCA803X_CTRL_AUTONEGOTIATION_ENABLE;
			if (duplex == FAL_FULL_DUPLEX) {
				phy_data |= QCA803X_CTRL_FULL_DUPLEX;
			} else {
				return SW_NOT_SUPPORTED;
			}
			break;
		case FAL_SPEED_100:
		case FAL_SPEED_10:
			if(old_speed == FAL_SPEED_100) {
				phy_data |= QCA803X_CTRL_SPEED_100;
			} else {
				phy_data &= ~QCA803X_CTRL_SPEED_100;
			}
			phy_data &= ~QCA803X_CTRL_SPEED_1000;
			phy_data &= ~QCA803X_CTRL_AUTONEGOTIATION_ENABLE;
			if (duplex == FAL_FULL_DUPLEX) {
				phy_data |= QCA803X_CTRL_FULL_DUPLEX;
			} else {
				phy_data &= ~QCA803X_CTRL_FULL_DUPLEX;
			}
			break;
		default:
			return SW_FAIL;
	}
	rv = qca803x_phy_reg_write(dev_id, phy_id, QCA803X_PHY_CONTROL, phy_data);

	return rv;
}

/******************************************************************************
*
* qca803x_phy_get_phy_id - get the phy id
*
*/
sw_error_t
qca803x_phy_get_phy_id(a_uint32_t dev_id, a_uint32_t phy_id,
		      a_uint16_t * org_id, a_uint16_t * rev_id)
{
	*org_id = qca803x_phy_reg_read(dev_id, phy_id, QCA803X_PHY_ID1);
	*rev_id = qca803x_phy_reg_read(dev_id, phy_id, QCA803X_PHY_ID2);

	return SW_OK;
}

static sw_error_t qca803x_phy_api_ops_init(void)
{
	sw_error_t  ret = SW_OK;
	hsl_phy_ops_t *qca803x_phy_api_ops = NULL;

	qca803x_phy_api_ops = kzalloc(sizeof(hsl_phy_ops_t), GFP_KERNEL);
	if (qca803x_phy_api_ops == NULL) {
		SSDK_ERROR("qca803x phy ops kzalloc failed!\n");
		return -ENOMEM;
	}

	phy_api_ops_init(QCA803X_PHY_CHIP);

	qca803x_phy_api_ops->phy_speed_get = qca803x_phy_get_speed;
	qca803x_phy_api_ops->phy_speed_set = qca803x_phy_set_speed;
	qca803x_phy_api_ops->phy_duplex_get = qca803x_phy_get_duplex;
	qca803x_phy_api_ops->phy_duplex_set = qca803x_phy_set_duplex;
	qca803x_phy_api_ops->phy_autoneg_enable_set = qca803x_phy_enable_autoneg;
	qca803x_phy_api_ops->phy_restart_autoneg = qca803x_phy_restart_autoneg;
	qca803x_phy_api_ops->phy_link_status_get = qca803x_phy_get_link_status;
	qca803x_phy_api_ops->phy_reset = qca803x_phy_reset;
	qca803x_phy_api_ops->phy_reg_write = qca803x_phy_reg_write;
	qca803x_phy_api_ops->phy_reg_read = qca803x_phy_reg_read;

	ret = hsl_phy_api_ops_register(QCA803X_PHY_CHIP, qca803x_phy_api_ops);

	if (ret == SW_OK)
		SSDK_INFO("qca probe qca803x phy driver succeeded!\n");
	else
		SSDK_ERROR("qca probe qca803x phy driver failed! (code: %d)\n", ret);

	return ret;
}

/******************************************************************************
*
* qca803x_phy_init -
*
*/
int qca803x_phy_init(a_uint32_t dev_id, a_uint32_t port_bmp)
{
	static a_uint32_t phy_ops_flag = 0;

	SSDK_INFO("start to init qca803x phy!\n");
	if(phy_ops_flag == 0) {
		qca803x_phy_api_ops_init();
		phy_ops_flag = 1;
	}

	return 0;
}

