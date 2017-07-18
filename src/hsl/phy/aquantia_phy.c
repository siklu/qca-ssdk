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
#include "aquantia_phy.h"
#include "aos_timer.h"
#include "hsl_phy.h"
#include <linux/kconfig.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/phy.h>
#include "ssdk_plat.h"

/* #define aquantia_phy_reg_read _phy_reg_read  */
/* #define aquantia_phy_reg_write _phy_reg_write */

/******************************************************************************
*
* aquantia_phy_mii_read - mii register read
*
* mii register read
*/
static sw_error_t
aquantia_phy_reg_read(a_uint32_t dev_id, a_uint32_t phy_id, a_uint32_t reg_mmd,
	a_uint32_t reg_id)
{
	sw_error_t rv;
	a_uint16_t phy_data;

	reg_id = AQUANTIA_REG_ADDRESS(reg_mmd, reg_id);
	HSL_PHY_GET(rv, dev_id, phy_id, reg_id, &phy_data);
	if (rv)
		return rv;

	return phy_data;
}

/******************************************************************************
*
* aquantia_phy_mii_write - mii register write
*
* mii register write
*/
static sw_error_t
aquantia_phy_reg_write(a_uint32_t dev_id, a_uint32_t phy_id, a_uint32_t reg_mmd,
	a_uint32_t reg_id, a_uint16_t reg_val)
{
	sw_error_t rv;

	reg_id = AQUANTIA_REG_ADDRESS(reg_mmd, reg_id);
	HSL_PHY_SET(rv, dev_id,  phy_id, reg_id, reg_val);

	return rv;
}

sw_error_t
aquantia_phy_get_speed(a_uint32_t dev_id, a_uint32_t phy_id,
		     fal_port_speed_t * speed)
{
	a_uint16_t phy_data;

	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
				AQUANTIA_REG_AUTONEG_VENDOR_STATUS);
	switch ((phy_data & AQUANTIA_STATUS_SPEED_MASK) >>1) {
	case AQUANTIA_STATUS_SPEED_100MBS:
		*speed = FAL_SPEED_100;
		break;
	case AQUANTIA_STATUS_SPEED_1000MBS:
		*speed = FAL_SPEED_1000;
		break;
	case AQUANTIA_STATUS_SPEED_10000MBS:
		*speed = FAL_SPEED_10000;
		break;
	case AQUANTIA_STATUS_SPEED_2500MBS:
		*speed = FAL_SPEED_2500;
		break;
	case AQUANTIA_STATUS_SPEED_5000MBS:
		*speed = FAL_SPEED_5000;
		break;
	default:
		return SW_READ_ERROR;
	}

	return SW_OK;
}

/******************************************************************************
*
* aquantia_phy_get_duplex - Determines the speed of phy ports associated with the
* specified device.
*/
sw_error_t
aquantia_phy_get_duplex(a_uint32_t dev_id, a_uint32_t phy_id,
		      fal_port_duplex_t * duplex)
{
	a_uint16_t phy_data;

	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_REG_AUTONEG_VENDOR_STATUS);
	//read duplex
	if (phy_data & AQUANTIA_STATUS_FULL_DUPLEX)
		*duplex = FAL_FULL_DUPLEX;
	else
		*duplex = FAL_HALF_DUPLEX;

	return SW_OK;
}

/******************************************************************************
*
* aquantia_phy_reset - reset the phy
*
* reset the phy
*/
sw_error_t aquantia_phy_reset(a_uint32_t dev_id, a_uint32_t phy_id)
{
	a_uint16_t phy_data;

	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_GLOABLE_REGISTERS,
		AQUANTIA_GLOABLE_STANDARD_CONTROL1);
	aquantia_phy_reg_write(dev_id, phy_id, AQUANTIA_MMD_GLOABLE_REGISTERS,
	AQUANTIA_GLOABLE_STANDARD_CONTROL1, phy_data | AQUANTIA_CTRL_SOFTWARE_RESET);

	return SW_OK;
}

/******************************************************************************
*
* aquantia_phy_set_powersave - set power saving status
*
* set power saving status
*/
sw_error_t
aquantia_phy_set_powersave(a_uint32_t dev_id, a_uint32_t phy_id, a_bool_t enable)
{
	a_uint16_t phy_data;

	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_GLOABLE_REGISTERS,
		AQUANTIA_GLOABLE_STANDARD_CONTROL1);
	if (enable == A_TRUE)
			phy_data |= AQUANTIA_POWER_SAVE;
	else
			phy_data &= ~AQUANTIA_POWER_SAVE;
	phy_data = aquantia_phy_reg_write(dev_id, phy_id, AQUANTIA_MMD_GLOABLE_REGISTERS,
		AQUANTIA_GLOABLE_STANDARD_CONTROL1,phy_data);

	return SW_OK;
}

/******************************************************************************
*
* aquantia_phy_get_powersave - get power saving status
*
* set power saving status
*/
sw_error_t
aquantia_phy_get_powersave(a_uint32_t dev_id, a_uint32_t phy_id,
			 a_bool_t * enable)
{
	a_uint16_t phy_data;

	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_GLOABLE_REGISTERS,
		AQUANTIA_GLOABLE_STANDARD_CONTROL1);
	if (phy_data& AQUANTIA_POWER_SAVE)
		*enable = A_TRUE;
	else
		*enable = A_FALSE;

	return SW_OK;
}

/******************************************************************************
*
* aquantia_phy_set_mdix -
*
* set phy mdix configuraiton
*/
sw_error_t
aquantia_phy_set_mdix(a_uint32_t dev_id, a_uint32_t phy_id,
		    fal_port_mdix_mode_t mode)
{
	a_uint16_t phy_data;

	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_RESERVED_VENDOR_PROVISIONING1);
	if (mode == PHY_MDIX_AUTO) {
		phy_data |= AQUANTIA_PHY_MDIX_AUTO;
	} else if (mode == PHY_MDIX_MDIX) {
		phy_data &= ~AQUANTIA_PHY_MDIX_AUTO;
		phy_data |= AQUANTIA_PHY_MDIX;
	} else if (mode == PHY_MDIX_MDI) {
		phy_data &= ~AQUANTIA_PHY_MDIX_AUTO;
	} else {
		return SW_BAD_PARAM;
	}
	aquantia_phy_reg_write(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_RESERVED_VENDOR_PROVISIONING1,phy_data);
	aquantia_phy_reset(dev_id, phy_id);

	return SW_OK;
}

/******************************************************************************
*
* aquantia_phy_get_mdix
*
* get phy mdix configuration
*/
sw_error_t
aquantia_phy_get_mdix(a_uint32_t dev_id, a_uint32_t phy_id,
		    fal_port_mdix_mode_t * mode)
{
	a_uint16_t phy_data;

	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_RESERVED_VENDOR_PROVISIONING1);
	if ((phy_data & AQUANTIA_PHY_MDIX_AUTO) == AQUANTIA_PHY_MDIX_AUTO) {
		*mode = PHY_MDIX_AUTO;
	} else if ((phy_data & AQUANTIA_PHY_MDIX) == AQUANTIA_PHY_MDIX) {
		*mode = PHY_MDIX_MDIX;
	} else {
		*mode = PHY_MDIX_MDI;
	}

	return SW_OK;
}

/******************************************************************************
*
* aquantia_phy_get_mdix status
*
* get phy mdix status
*/
sw_error_t
aquantia_phy_get_mdix_status(a_uint32_t dev_id, a_uint32_t phy_id,
			   fal_port_mdix_status_t * mode)
{
	a_uint16_t phy_data;

	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_RESERVED_VENDOR_STATUS1);
	*mode = (phy_data &  AQUANTIA_PHY_MDIX_STATUS) ? PHY_MDIX_STATUS_MDIX :
	    PHY_MDIX_STATUS_MDI;

	return SW_OK;
}

/******************************************************************************
*
* aquantia_phy_set_local_loopback
*
* set phy local loopback
*/
sw_error_t
aquantia_phy_set_local_loopback(a_uint32_t dev_id, a_uint32_t phy_id,
			      a_bool_t enable)
{
	a_uint16_t phy_data;
	fal_port_speed_t old_speed;

	 phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_PHY_XS_REGISTERS,
		AQUANTIA_PHY_XS_TRANAMIT_RESERVED_VENDOR_PROVISION5);
       if (enable == A_TRUE) {
	   		  phy_data |= AQUANTIA_INTERNAL_LOOPBACK;
			  aquantia_phy_get_speed(dev_id, phy_id, &old_speed);
			  if (old_speed == FAL_SPEED_100) {
			  	   phy_data |= AQUANTIA_100M_LOOPBACK;
			  	} else if (old_speed == FAL_SPEED_1000) {
			  	   phy_data |= AQUANTIA_1000M_LOOPBACK;
			  	} else if (old_speed == FAL_SPEED_10000) {
			  	   phy_data |= AQUANTIA_10000M_LOOPBACK;
			  	}else if (old_speed == FAL_SPEED_2500) {
			  	   phy_data |= AQUANTIA_2500M_LOOPBACK;
			  	}else if (old_speed == FAL_SPEED_5000) {
			  	   phy_data |= AQUANTIA_5000M_LOOPBACK;
			  	}else {
                                return SW_FAIL;
			  	}
         } else {
			  phy_data &= AQUANTIA_INTERNAL_LOOPBACK;
		 }
	 phy_data = aquantia_phy_reg_write(dev_id, phy_id, AQUANTIA_MMD_PHY_XS_REGISTERS,
		AQUANTIA_PHY_XS_TRANAMIT_RESERVED_VENDOR_PROVISION5,phy_data);

	return SW_OK;
}

/******************************************************************************
*
* aquantia_phy_get_local_loopback
*
* get phy local loopback
*/
sw_error_t
aquantia_phy_get_local_loopback(a_uint32_t dev_id, a_uint32_t phy_id,
			      a_bool_t * enable)
{
	a_uint16_t phy_data;

	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_PHY_XS_REGISTERS,
		AQUANTIA_PHY_XS_TRANAMIT_RESERVED_VENDOR_PROVISION5);
	if (phy_data & AQUANTIA_INTERNAL_LOOPBACK) {
		*enable = A_TRUE;
	} else {
		*enable = A_FALSE;
	}

	return SW_OK;
}

sw_error_t
aquantia_phy_set_remote_loopback(a_uint32_t dev_id, a_uint32_t phy_id,
				   a_bool_t enable)
{
	a_uint16_t phy_data;

	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_PHY_XS_REGISTERS,
		AQUANTIA_PHY_XS_STANDARD_CONTROL1);
	if (enable == A_TRUE) {
		phy_data |= AQUANTIA_PHY_REMOTE_LOOPBACK;
	} else {
		phy_data &= ~AQUANTIA_PHY_REMOTE_LOOPBACK;
	}
	phy_data = aquantia_phy_reg_write(dev_id, phy_id, AQUANTIA_MMD_PHY_XS_REGISTERS,
		AQUANTIA_PHY_XS_STANDARD_CONTROL1, phy_data);

	return SW_OK;
}

/******************************************************************************
*
* aquantia_phy_get_remote_loopback
*
* get phy remote loopback
*/
sw_error_t
aquantia_phy_get_remote_loopback(a_uint32_t dev_id, a_uint32_t phy_id,
				   a_bool_t * enable)
{
	a_uint16_t phy_data;

	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_PHY_XS_REGISTERS,
		AQUANTIA_PHY_XS_STANDARD_CONTROL1);
	if (phy_data & AQUANTIA_PHY_REMOTE_LOOPBACK) {
		*enable = A_TRUE;
	} else {
		*enable = A_FALSE;
	}

	return SW_OK;
}

/******************************************************************************
*
* aquantia_phy_cdt - cable diagnostic test
*
* cable diagnostic test
*/
static inline fal_cable_status_t _phy_cdt_status_mapping(a_uint16_t status)
{
	fal_cable_status_t status_mapping = FAL_CABLE_STATUS_INVALID;

	if (0 == status)
		status_mapping = FAL_CABLE_STATUS_INVALID;
	else if (1 == status)
		status_mapping = FAL_CABLE_STATUS_NORMAL;
	else if (2 == status)
		status_mapping = FAL_CABLE_STATUS_OPENED;
	else if (3 == status)
		status_mapping = FAL_CABLE_STATUS_SHORT;

	return status_mapping;
}

sw_error_t
aquantia_phy_cdt_get(a_uint32_t dev_id, a_uint32_t phy_id,
		   fal_port_cdt_t * port_cdt)
{
	a_uint16_t status = 0;

	if ((!port_cdt) || (phy_id > 6)) {
		return SW_FAIL;
	}
	/* Get cable status */
	status = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_GLOABLE_REGISTERS,
		AQUANTIA_CABLE_DIAGNOSTIC_STATUS1);
	port_cdt->pair_a_status =  (status >> 12) & 0x7;
	port_cdt->pair_b_status = (status >> 8) & 0x7;
	port_cdt->pair_c_status = (status >> 4) & 0x7;
	port_cdt->pair_d_status = status & 0x3;
	/* Get Cable Length value */
	port_cdt->pair_a_len = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_GLOABLE_REGISTERS,
		AQUANTIA_CABLE_DIAGNOSTIC_STATUS2);
	port_cdt->pair_b_len = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_GLOABLE_REGISTERS,
		AQUANTIA_CABLE_DIAGNOSTIC_STATUS4);
	port_cdt->pair_c_len = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_GLOABLE_REGISTERS,
		AQUANTIA_CABLE_DIAGNOSTIC_STATUS6);
	port_cdt->pair_d_len = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_GLOABLE_REGISTERS,
		AQUANTIA_CABLE_DIAGNOSTIC_STATUS8);

	return SW_OK;
}

sw_error_t
aquantia_phy_cdt(a_uint32_t dev_id, a_uint32_t phy_id, a_uint32_t mdi_pair,
	       fal_cable_status_t * cable_status, a_uint32_t * cable_len)
{
	fal_port_cdt_t aquantia_port_cdt;

	if ((mdi_pair >= 4) || (phy_id > 6)) {
		//There are only 4 mdi pairs in 1000BASE-T
		return SW_BAD_PARAM;
	}

	aquantia_phy_cdt_get(dev_id, phy_id, &aquantia_port_cdt);

	switch (mdi_pair) {
	case 0:
		*cable_status =
		    _phy_cdt_status_mapping(aquantia_port_cdt.pair_a_status);
		/* Get Cable Length value */
		*cable_len = aquantia_port_cdt.pair_a_len;
		break;
	case 1:
		*cable_status =
		    _phy_cdt_status_mapping(aquantia_port_cdt.pair_b_status);
		/* Get Cable Length value */
		*cable_len = aquantia_port_cdt.pair_b_len;
		break;
	case 2:
		*cable_status =
		    _phy_cdt_status_mapping(aquantia_port_cdt.pair_c_status);
		/* Get Cable Length value */
		*cable_len = aquantia_port_cdt.pair_c_len;
		break;
	case 3:
		*cable_status =
		    _phy_cdt_status_mapping(aquantia_port_cdt.pair_d_status);
		/* Get Cable Length value */
		*cable_len = aquantia_port_cdt.pair_d_len;
		break;
	default:
		break;
	}

	return SW_OK;
}

/******************************************************************************
*
* AQUANTIA_autoneg_done
*
* AQUANTIA_autoneg_done
*/
a_bool_t aquantia_autoneg_done(a_uint32_t dev_id, a_uint32_t phy_id)
{
	a_uint16_t phy_data;
	a_uint16_t ii = 200;

	do {
		phy_data =  aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
			AQUANTIA_AUTONEG_STANDARD_STATUS1);
		aos_mdelay(10);
	}
	while ((!AQUANTIA_AUTONEG_DONE(phy_data)) && --ii);

	if (ii == 0)
		return A_FALSE;

	return A_TRUE;
}

/******************************************************************************
*
* aquantia_phy_get_ability - get the phy ability
*
*
*/
sw_error_t
aquantia_phy_get_partner_ability(a_uint32_t dev_id, a_uint32_t phy_id,
			       a_uint32_t * ability)
{
	a_uint16_t phy_data;

	*ability = 0;
	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_LINK_PARTNER_ABILITY);

	if (phy_data & AQUANTIA_LINK_10BASETX_HALF_DUPLEX)
		*ability |= FAL_PHY_PART_10T_HD;

	if (phy_data & AQUANTIA_LINK_10BASETX_FULL_DUPLEX)
		*ability |= FAL_PHY_PART_10T_FD;

	if (phy_data & AQUANTIA_LINK_100BASETX_HALF_DUPLEX)
		*ability |= FAL_PHY_PART_100TX_HD;

	if (phy_data & AQUANTIA_LINK_100BASETX_FULL_DUPLEX)
		*ability |= FAL_PHY_PART_100TX_FD;

	return SW_OK;
}

/******************************************************************************
*
* aquantia_phy_status - test to see if the specified phy link is alive
*
* RETURNS:
*    A_TRUE  --> link is alive
*    A_FALSE --> link is down
*/
a_bool_t aquantia_phy_get_link_status(a_uint32_t dev_id, a_uint32_t phy_id)
{
	a_uint16_t phy_data;

	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_STANDARD_STATUS1);
	if (phy_data & AQUANTIA_STATUS_LINK)
		return A_TRUE;

	return A_FALSE;
}

/******************************************************************************
*
* AQUANTIA_set_autoneg_adv - set the phy autoneg Advertisement
*
*/
sw_error_t
aquantia_phy_set_autoneg_adv(a_uint32_t dev_id, a_uint32_t phy_id,
			   a_uint32_t autoneg)
{
	a_uint16_t phy_data = 0;

	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_ADVERTISEMENT_REGISTER);
	phy_data &= ~AQUANTIA_ADVERTISE_MEGA_ALL;
	phy_data &=
	    ~(AQUANTIA_ADVERTISE_PAUSE | AQUANTIA_ADVERTISE_ASYM_PAUSE);
	if (autoneg & FAL_PHY_ADV_100TX_FD)
		phy_data |= AQUANTIA_ADVERTISE_100FULL;
	if (autoneg & FAL_PHY_ADV_100TX_HD)
		phy_data |= AQUANTIA_ADVERTISE_100HALF;
	if (autoneg & FAL_PHY_ADV_10T_FD)
		phy_data |= AQUANTIA_ADVERTISE_10FULL;
	if (autoneg & FAL_PHY_ADV_10T_HD)
		phy_data |= AQUANTIA_ADVERTISE_10HALF;
	if (autoneg & FAL_PHY_ADV_PAUSE)
		phy_data |= AQUANTIA_ADVERTISE_PAUSE;
	if (autoneg & FAL_PHY_ADV_ASY_PAUSE)
		phy_data |= AQUANTIA_ADVERTISE_ASYM_PAUSE;
	aquantia_phy_reg_write(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_ADVERTISEMENT_REGISTER, phy_data);

	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_VENDOR_PROVISION1);
	phy_data &= ~AQUANTIA_ADVERTISE_GIGA_ALL;
	if (autoneg & FAL_PHY_ADV_1000T_FD)
		phy_data |= AQUANTIA_ADVERTISE_1000FULL;
	if (autoneg & FAL_PHY_ADV_1000T_FD)
		phy_data |= AQUANTIA_ADVERTISE_1000FULL;
	if (autoneg & FAL_PHY_ADV_2500T_FD)
		phy_data |= AQUANTIA_ADVERTISE_2500FULL;
	if (autoneg & FAL_PHY_ADV_5000T_FD)
		phy_data |= AQUANTIA_ADVERTISE_5000FULL;
	aquantia_phy_reg_write(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_VENDOR_PROVISION1, phy_data);

	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_10GBASS_T_CONTROL_REGISTER);
	phy_data &= ~AQUANTIA_ADVERTISE_GIGA_PLUS_ALL;
	if (autoneg & FAL_PHY_ADV_10000T_FD)
		phy_data |= AQUANTIA_ADVERTISE_10000FULL;
	phy_data = aquantia_phy_reg_write(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_10GBASS_T_CONTROL_REGISTER,phy_data);

	return SW_OK;
}

/******************************************************************************
*
* AQUANTIA_get_autoneg_adv - get the phy autoneg Advertisement
*
*/
sw_error_t
aquantia_phy_get_autoneg_adv(a_uint32_t dev_id, a_uint32_t phy_id,
			   a_uint32_t * autoneg)
{
	a_uint16_t phy_data = 0;

	*autoneg = 0;
	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_ADVERTISEMENT_REGISTER);

	if (phy_data & AQUANTIA_ADVERTISE_100FULL)
		*autoneg |= FAL_PHY_ADV_100TX_FD;
	if (phy_data & AQUANTIA_ADVERTISE_100HALF)
		*autoneg |= FAL_PHY_ADV_100TX_HD;
	if (phy_data & AQUANTIA_ADVERTISE_10FULL)
		*autoneg |= FAL_PHY_ADV_10T_FD;
	if (phy_data & AQUANTIA_ADVERTISE_10HALF)
		*autoneg |= FAL_PHY_ADV_10T_HD;
	if (phy_data & AQUANTIA_ADVERTISE_PAUSE)
		*autoneg |= FAL_PHY_ADV_PAUSE;
	if (phy_data & AQUANTIA_ADVERTISE_ASYM_PAUSE)
		*autoneg |= FAL_PHY_ADV_ASY_PAUSE;

	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_VENDOR_PROVISION1);
	if (phy_data & AQUANTIA_ADVERTISE_1000FULL)
		*autoneg |= FAL_PHY_ADV_1000T_FD;
	if (phy_data & AQUANTIA_ADVERTISE_2500FULL)
		*autoneg |= FAL_PHY_ADV_2500T_FD;
	if (phy_data & AQUANTIA_ADVERTISE_5000FULL)
		*autoneg |= FAL_PHY_ADV_5000T_FD;

	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_10GBASS_T_CONTROL_REGISTER);
	if (phy_data & AQUANTIA_ADVERTISE_10000FULL)
		*autoneg |= FAL_PHY_ADV_10000T_FD;

	return SW_OK;
}

/******************************************************************************
*
* aquantia_phy_enable_autonego
*
*/
a_bool_t aquantia_phy_autoneg_status(a_uint32_t dev_id, a_uint32_t phy_id)
{
	a_uint16_t phy_data;

	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_STANDARD_CONTROL1);
	if (phy_data & AQUANTIA_CTRL_AUTONEGOTIATION_ENABLE)
		return A_TRUE;

	return A_FALSE;
}
/******************************************************************************
*
* AQUANTIA_restart_autoneg - restart the phy autoneg
*
*/
sw_error_t aquantia_phy_restart_autoneg(a_uint32_t dev_id, a_uint32_t phy_id)
{
	a_uint16_t phy_data = 0;

	phy_data = aquantia_phy_reg_read(dev_id, phy_id,
		AQUANTIA_MMD_PHY_XS_REGISTERS,
		AQUANTIA_PHY_XS_USX_TRANSMIT);
	if (!(phy_data & AQUANTIA_PHY_USX_AUTONEG_ENABLE))
		aquantia_phy_reg_write(dev_id, phy_id,
		AQUANTIA_MMD_PHY_XS_REGISTERS,
		AQUANTIA_PHY_XS_USX_TRANSMIT,
		phy_data | AQUANTIA_PHY_USX_AUTONEG_ENABLE);

	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_STANDARD_CONTROL1);
	phy_data |= AQUANTIA_CTRL_AUTONEGOTIATION_ENABLE;
	aquantia_phy_reg_write(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_STANDARD_CONTROL1,
		phy_data | AQUANTIA_CTRL_RESTART_AUTONEGOTIATION);

	return SW_OK;
}

/******************************************************************************
*
* aquantia_phy_enable_autonego
*
*/
sw_error_t aquantia_phy_enable_autoneg(a_uint32_t dev_id, a_uint32_t phy_id)
{
	a_uint16_t phy_data = 0;

	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_STANDARD_CONTROL1);
	aquantia_phy_reg_write(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_STANDARD_CONTROL1,
		phy_data | AQUANTIA_CTRL_AUTONEGOTIATION_ENABLE);

	return SW_OK;
}

/******************************************************************************
*
* aquantia_phy_set_speed - Determines the speed of phy ports associated with the
* specified device.
*/
static sw_error_t _aquantia_phy_set_100speed(a_uint32_t dev_id, a_uint32_t phy_id, fal_port_duplex_t duplex)
{
	a_uint16_t phy_data = 0;

	/*set 100M */
	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_ADVERTISEMENT_REGISTER);
	phy_data &= ~(AQUANTIA_ADVERTISE_MEGA_ALL);
	if(duplex == FAL_FULL_DUPLEX)
		phy_data |= AQUANTIA_ADVERTISE_100FULL;
	else
		phy_data |= AQUANTIA_ADVERTISE_100HALF;
	aquantia_phy_reg_write(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_ADVERTISEMENT_REGISTER, phy_data);

	/*disable 1000M, 2500M, 5000M speed*/
	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_VENDOR_PROVISION1);
	phy_data &= ~(AQUANTIA_ADVERTISE_GIGA_ALL);
	aquantia_phy_reg_write(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_VENDOR_PROVISION1, phy_data);

	/*disable 10000M speed*/
	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_10GBASS_T_CONTROL_REGISTER);
	phy_data &= ~(AQUANTIA_ADVERTISE_GIGA_PLUS_ALL);
	aquantia_phy_reg_write(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_10GBASS_T_CONTROL_REGISTER, phy_data);

	return SW_OK;
}

static sw_error_t _aquantia_phy_set_giga_speed(a_uint32_t dev_id, a_uint32_t phy_id, fal_port_speed_t speed)
{
	a_uint16_t phy_data = 0;

	/*set 1000M and disable 2500M, 5000M */
	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_VENDOR_PROVISION1);
	phy_data &= ~(AQUANTIA_ADVERTISE_GIGA_ALL);
	switch(speed)
	{
		case FAL_SPEED_1000:
			phy_data |= AQUANTIA_ADVERTISE_1000FULL;
			break;
		case FAL_SPEED_2500:
			phy_data |= AQUANTIA_ADVERTISE_2500FULL;
			break;
		case FAL_SPEED_5000:
			phy_data |= AQUANTIA_ADVERTISE_5000FULL;
			break;
		default:
			return SW_FAIL;
	}
	aquantia_phy_reg_write(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_VENDOR_PROVISION1, phy_data);

	/*disable 100M speed*/
	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_ADVERTISEMENT_REGISTER);
	phy_data &= ~(AQUANTIA_ADVERTISE_MEGA_ALL);
	aquantia_phy_reg_write(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_ADVERTISEMENT_REGISTER, phy_data);

	/*disable 10000M speed*/
	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_10GBASS_T_CONTROL_REGISTER);
	phy_data &= ~(AQUANTIA_ADVERTISE_GIGA_PLUS_ALL);
	 aquantia_phy_reg_write(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_10GBASS_T_CONTROL_REGISTER, phy_data);

	return SW_OK;
}

static sw_error_t _aquantia_phy_set_10g_speed(a_uint32_t dev_id, a_uint32_t phy_id)
{
	a_uint16_t phy_data = 0;

	/*set giga speed */
	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_10GBASS_T_CONTROL_REGISTER);
	phy_data &= ~(AQUANTIA_ADVERTISE_GIGA_PLUS_ALL);
	phy_data |= AQUANTIA_ADVERTISE_10000FULL;
	aquantia_phy_reg_write(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_10GBASS_T_CONTROL_REGISTER, phy_data);

	/*disable 100M speed*/
	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_ADVERTISEMENT_REGISTER);
	phy_data &= ~(AQUANTIA_ADVERTISE_MEGA_ALL);
	aquantia_phy_reg_write(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_ADVERTISEMENT_REGISTER, phy_data);

	/*disable 1000M 2500M 5000M speed*/
	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_VENDOR_PROVISION1);
	phy_data &= ~(AQUANTIA_ADVERTISE_GIGA_ALL);
	aquantia_phy_reg_write(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_VENDOR_PROVISION1, phy_data);

	return SW_OK;
}

sw_error_t
aquantia_phy_set_speed(a_uint32_t dev_id, a_uint32_t phy_id,
		     fal_port_speed_t speed)
{
	fal_port_duplex_t old_duplex;

	aquantia_phy_get_duplex(dev_id, phy_id, &old_duplex);
	if (old_duplex == FAL_FULL_DUPLEX) {
		if (FAL_SPEED_100 == speed) {
			_aquantia_phy_set_100speed(dev_id, phy_id, FAL_FULL_DUPLEX);
		}
		else if(FAL_SPEED_2500 == speed ||FAL_SPEED_5000 == speed || FAL_SPEED_1000 == speed){
			_aquantia_phy_set_giga_speed(dev_id, phy_id, speed);
		}
		else if(FAL_SPEED_10000 == speed){
				_aquantia_phy_set_10g_speed(dev_id, phy_id);
		}
		else{
			return SW_BAD_PARAM;
		}
	}else if (old_duplex == FAL_HALF_DUPLEX) {
		if (FAL_SPEED_100 == speed) {
			_aquantia_phy_set_100speed(dev_id, phy_id, FAL_HALF_DUPLEX);
		}else {
			return SW_BAD_PARAM;
	       }
	} else {
		return SW_FAIL;
	}
	aquantia_phy_restart_autoneg(dev_id, phy_id);

	return SW_OK;
}

/******************************************************************************
*
* aquantia_phy_set_duplex - Determines the speed of phy ports associated with the
* specified device.
*/
sw_error_t
aquantia_phy_set_duplex(a_uint32_t dev_id, a_uint32_t phy_id,
		      fal_port_duplex_t duplex)
{
	a_uint16_t phy_data = 0;
	fal_port_speed_t old_speed;

	aquantia_phy_get_speed(dev_id, phy_id, &old_speed);
	if (old_speed == FAL_SPEED_100){
		phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
			AQUANTIA_AUTONEG_ADVERTISEMENT_REGISTER);
	 	if (duplex == FAL_FULL_DUPLEX) {
			phy_data &= ~(AQUANTIA_ADVERTISE_MEGA_ALL);
			phy_data |= AQUANTIA_ADVERTISE_100FULL;
			 aquantia_phy_reg_write(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
				AQUANTIA_AUTONEG_ADVERTISEMENT_REGISTER, phy_data);
		 } else {
		 	phy_data &= ~(AQUANTIA_ADVERTISE_MEGA_ALL);
			phy_data |= AQUANTIA_ADVERTISE_100HALF;
			aquantia_phy_reg_write(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
				AQUANTIA_AUTONEG_ADVERTISEMENT_REGISTER, phy_data);
		 }
	}
	else
	 	return SW_NOT_SUPPORTED;
	aquantia_phy_restart_autoneg(dev_id, phy_id);

	return SW_OK;
}

/******************************************************************************
*
* aquantia_phy_set wol enable or disable
*
* set phy wol enable or disable
*/
sw_error_t
aquantia_phy_set_wol_status(a_uint32_t dev_id, a_uint32_t phy_id, a_bool_t enable)
{
	a_uint16_t phy_data;

	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_RESERVED_VENDOR_PROVISIONING1);
	if (enable == A_TRUE) {
		phy_data |= AQUANTIA_PHY_WOL_ENABLE;
	} else {
		phy_data &= ~AQUANTIA_PHY_WOL_ENABLE;
	}
	aquantia_phy_reg_write(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_RESERVED_VENDOR_PROVISIONING1, phy_data);

	return SW_OK;
}

/******************************************************************************
*
* aquantia_phy_get_wol status
*
* get wol status
*/
sw_error_t
aquantia_phy_get_wol_status(a_uint32_t dev_id, a_uint32_t phy_id, a_bool_t * enable)
{
	a_uint16_t phy_data;

	*enable = A_FALSE;
	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_RESERVED_VENDOR_PROVISIONING1);
	if (phy_data & AQUANTIA_PHY_WOL_ENABLE)
		*enable = A_TRUE;

	return SW_OK;
}

/******************************************************************************
*
* aquantia_phy_intr_mask_set - Set interrupt mask with the
* specified device.
*/
sw_error_t
aquantia_phy_intr_mask_set(a_uint32_t dev_id, a_uint32_t phy_id,
			 a_uint32_t intr_mask_flag)
{
	a_uint16_t phy_data = 0;

	if ((FAL_PHY_INTR_STATUS_DOWN_CHANGE |FAL_PHY_INTR_STATUS_UP_CHANGE)
		& intr_mask_flag)
	{
		phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
			AQUANTIA_AUTONEG_TRANSMIT_VENDOR_INTR_MASK);
		phy_data |= AQUANTIA_INTR_LINK_STATUS_CHANGE;
		aquantia_phy_reg_write(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
			AQUANTIA_AUTONEG_TRANSMIT_VENDOR_INTR_MASK, phy_data);
	}

	return SW_OK;
}

/******************************************************************************
*
* aquantia_phy_intr_mask_get - Get interrupt mask with the
* specified device.
*/
sw_error_t
aquantia_phy_intr_mask_get(a_uint32_t dev_id, a_uint32_t phy_id,
			 a_uint32_t * intr_mask_flag)
{
	a_uint16_t phy_data = 0;

	phy_data = aquantia_phy_reg_read(dev_id, phy_id, AQUANTIA_MMD_AUTONEG,
		AQUANTIA_AUTONEG_TRANSMIT_VENDOR_INTR_MASK);
	if (AQUANTIA_INTR_LINK_STATUS_CHANGE & phy_data)
		*intr_mask_flag = (FAL_PHY_INTR_STATUS_DOWN_CHANGE |
							  FAL_PHY_INTR_STATUS_UP_CHANGE);

	return SW_OK;
}


/******************************************************************************
*
* aquantia_phy_hw_register init to avoid packet loss
*
*/
sw_error_t
aquantia_phy_hw_init(a_uint32_t dev_id,  a_uint32_t port_bmp)
{
	a_uint16_t phy_data = 0;
	a_uint32_t port_id = 0, phy_addr = 0;

	for (port_id = 0; port_id < SW_MAX_NR_PORT; port_id ++)
	{
		if (port_bmp & (0x1 << port_id))
		{
			phy_addr = qca_ssdk_port_to_phy_addr(dev_id, port_id);
			/*set auto neg of aq*/
			phy_data = aquantia_phy_reg_read(dev_id, phy_addr, AQUANTIA_MMD_PHY_XS_REGISTERS,
				AQUANTIA_PHY_XS_USX_TRANSMIT);
			phy_data |= AQUANTIA_PHY_USX_AUTONEG_ENABLE;
			aquantia_phy_reg_write(dev_id, phy_addr, AQUANTIA_MMD_PHY_XS_REGISTERS,
				AQUANTIA_PHY_XS_USX_TRANSMIT,phy_data);

			/*config interrupt of aq*/
			phy_data = aquantia_phy_reg_read(dev_id, phy_addr, AQUANTIA_MMD_AUTONEG,
				AQUANTIA_AUTONEG_TRANSMIT_VENDOR_INTR_MASK);
			phy_data |= AQUANTIA_INTR_LINK_STATUS_CHANGE;
			aquantia_phy_reg_write(dev_id, phy_addr, AQUANTIA_MMD_AUTONEG,
				AQUANTIA_AUTONEG_TRANSMIT_VENDOR_INTR_MASK, phy_data);

			phy_data = aquantia_phy_reg_read(dev_id, phy_addr, AQUANTIA_MMD_GLOABLE_REGISTERS,
				AQUANTIA_GLOBAL_INTR_STANDARD_MASK);
			phy_data |= AQUANTIA_ALL_VENDOR_ALARMS_INTERRUPT_MASK;
			aquantia_phy_reg_write(dev_id, phy_addr, AQUANTIA_MMD_GLOABLE_REGISTERS,
				AQUANTIA_GLOBAL_INTR_STANDARD_MASK, phy_data);

			phy_data = aquantia_phy_reg_read(dev_id, phy_addr, AQUANTIA_MMD_GLOABLE_REGISTERS,
				AQUANTIA_GLOBAL_INTR_VENDOR_MASK);
			phy_data |= AQUANTIA_AUTO_AND_ALARMS_INTR_MASK;
			aquantia_phy_reg_write(dev_id, phy_addr, AQUANTIA_MMD_GLOABLE_REGISTERS,
				AQUANTIA_GLOBAL_INTR_VENDOR_MASK, phy_data);
		}
	}

	return SW_OK;
}

static int aquantia_phy_api_ops_init(void)
{
	int ret;
	hsl_phy_ops_t *aquantia_phy_api_ops = NULL;

	aquantia_phy_api_ops = kzalloc(sizeof(hsl_phy_ops_t), GFP_KERNEL);
	if (aquantia_phy_api_ops == NULL) {
		SSDK_ERROR("aquantia phy ops kzalloc failed!\n");
		return -ENOMEM;
	}

	phy_api_ops_init(AQUANTIA_PHY_CHIP);

	aquantia_phy_api_ops->phy_speed_get = aquantia_phy_get_speed;
	aquantia_phy_api_ops->phy_speed_set = aquantia_phy_set_speed;
	aquantia_phy_api_ops->phy_duplex_get = aquantia_phy_get_duplex;
	aquantia_phy_api_ops->phy_duplex_set = aquantia_phy_set_duplex;
	aquantia_phy_api_ops->phy_autoneg_enable_set = aquantia_phy_enable_autoneg;
	aquantia_phy_api_ops->phy_restart_autoneg = aquantia_phy_restart_autoneg;
	aquantia_phy_api_ops->phy_autoneg_status_get = aquantia_phy_autoneg_status;
	aquantia_phy_api_ops->phy_autoneg_adv_set = aquantia_phy_set_autoneg_adv;
	aquantia_phy_api_ops->phy_autoneg_adv_get = aquantia_phy_get_autoneg_adv;
	aquantia_phy_api_ops->phy_powersave_set = aquantia_phy_set_powersave;
	aquantia_phy_api_ops->phy_powersave_get = aquantia_phy_get_powersave;
	aquantia_phy_api_ops->phy_cdt = aquantia_phy_cdt;
	aquantia_phy_api_ops->phy_link_status_get = aquantia_phy_get_link_status;
	aquantia_phy_api_ops->phy_mdix_set = aquantia_phy_set_mdix;
	aquantia_phy_api_ops->phy_mdix_get = aquantia_phy_get_mdix;
	aquantia_phy_api_ops->phy_mdix_status_get = aquantia_phy_get_mdix_status;
	aquantia_phy_api_ops->phy_local_loopback_set = aquantia_phy_set_local_loopback;
	aquantia_phy_api_ops->phy_local_loopback_get = aquantia_phy_get_local_loopback;
	aquantia_phy_api_ops->phy_remote_loopback_set = aquantia_phy_set_remote_loopback;
	aquantia_phy_api_ops->phy_remote_loopback_get = aquantia_phy_get_remote_loopback;
	aquantia_phy_api_ops->phy_reset = aquantia_phy_reset;
	aquantia_phy_api_ops->phy_wol_status_set = aquantia_phy_set_wol_status;
	aquantia_phy_api_ops->phy_wol_status_get = aquantia_phy_get_wol_status;
	aquantia_phy_api_ops->phy_intr_mask_set = aquantia_phy_intr_mask_set;
	aquantia_phy_api_ops->phy_intr_mask_get = aquantia_phy_intr_mask_get;

	ret = hsl_phy_api_ops_register(AQUANTIA_PHY_CHIP, aquantia_phy_api_ops);
	if (ret == 0)
		SSDK_INFO("qca probe aquantia phy driver succeeded!\n");
	else
		SSDK_ERROR("qca probe aquantia phy driver failed! (code: %d)\n", ret);

	return ret;
}

/******************************************************************************
*
* aquantia_phy_init -
*
*/
int aquantia_phy_init(a_uint32_t dev_id, a_uint32_t port_bmp)
{
	static a_uint32_t phy_ops_flag = 0;

	if(phy_ops_flag == 0) {
		aquantia_phy_api_ops_init();
		phy_ops_flag = 1;
	}
	aquantia_phy_hw_init(dev_id, port_bmp);

	return 0;

}

