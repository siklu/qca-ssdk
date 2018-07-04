/*
 * Copyright (c) 2015, 2017-2018, The Linux Foundation. All rights reserved.
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
#include "hsl_phy.h"
#include "hsl.h"
#if defined(ISIS) ||defined(ISISC) ||defined(GARUDA)
#include <f1_phy.h>
#endif
#if defined(ATHENA) ||defined(SHIVA) ||defined(HORUS)
#include <f2_phy.h>
#endif
#ifdef IN_MALIBU_PHY
#include <malibu_phy.h>
#endif
#ifdef IN_AQUANTIA_PHY
#include <aquantia_phy.h>
#endif
#ifdef IN_QCA803X_PHY
#include <qca803x_phy.h>
#endif
#ifdef IN_SFP_PHY
#include <sfp_phy.h>
#endif
#ifdef IN_QCA808X_PHY
#include <qca808x_phy.h>
#endif
#include "sw.h"
#include "ssdk_plat.h"

phy_info_t *phy_info[SW_MAX_NR_DEV] = {0};
a_uint32_t port_bmp[SW_MAX_NR_DEV] = {0};


phy_driver_instance_t ssdk_phy_driver[] =
{
	#if defined(ISIS) ||defined(ISISC) ||defined(GARUDA)
	{F1_PHY_CHIP, {0}, NULL, f1_phy_init, NULL},
	#else
	{F1_PHY_CHIP, {0}, NULL, NULL, NULL},
	#endif
	#if defined(ATHENA) ||defined(SHIVA) ||defined(HORUS)
	{F2_PHY_CHIP, {0}, NULL, f2_phy_init, NULL},
	#else
	{F2_PHY_CHIP, {0}, NULL, NULL, NULL},
	#endif
	#ifdef IN_MALIBU_PHY
	{MALIBU_PHY_CHIP, {0}, NULL, malibu_phy_init, NULL},
	#else
	{MALIBU_PHY_CHIP, {0}, NULL, NULL, NULL},
	#endif
	#ifdef IN_AQUANTIA_PHY
	{AQUANTIA_PHY_CHIP, {0}, NULL, aquantia_phy_init, NULL},
	#else
	{AQUANTIA_PHY_CHIP, {0}, NULL, NULL, NULL},
	#endif
	#ifdef IN_QCA803X_PHY
	{QCA803X_PHY_CHIP, {0}, NULL, qca803x_phy_init, NULL},
	#else
	{QCA803X_PHY_CHIP, {0}, NULL, NULL, NULL},
	#endif
	#ifdef IN_SFP_PHY
	{SFP_PHY_CHIP, {0}, NULL, sfp_phy_init, sfp_phy_exit},
	#else
	{SFP_PHY_CHIP, {0}, NULL, NULL, NULL},
	#endif
	#ifdef IN_QCA808X_PHY
	{QCA808X_PHY_CHIP, {0}, NULL, qca808x_phy_init, NULL},
	#else
	{QCA808X_PHY_CHIP, {0}, NULL, NULL, NULL},
	#endif
	{MAX_PHY_CHIP, {0}, NULL, NULL, NULL}
};
sw_error_t hsl_phy_api_ops_register(phy_type_t phy_type, hsl_phy_ops_t * phy_api_ops)
{

	ssdk_phy_driver[phy_type].phy_ops = phy_api_ops;

	return SW_OK;

}

sw_error_t hsl_phy_api_ops_unregister(phy_type_t phy_type, hsl_phy_ops_t * phy_api_ops)
{

	ssdk_phy_driver[phy_type].phy_ops = NULL;

	return SW_OK;

}

hsl_phy_ops_t *hsl_phy_api_ops_get(a_uint32_t dev_id, a_uint32_t port_id)
{
	phy_type_t phytype = 0;

	if (dev_id >= SW_MAX_NR_DEV)
		return NULL;

	phytype = phy_info[dev_id]->phy_type[port_id];

	return ssdk_phy_driver[phytype].phy_ops;

}

sw_error_t phy_api_ops_init(phy_type_t phy_type)
{

	if (MAX_PHY_CHIP <= phy_type)
		return SW_BAD_PARAM;

	if(ssdk_phy_driver[phy_type].phy_ops != NULL)
	{
		kfree(ssdk_phy_driver[phy_type].phy_ops);
		ssdk_phy_driver[phy_type].phy_ops = NULL;
	}
	return SW_OK;
}

a_bool_t hsl_port_is_sfp(a_uint32_t dev_id, a_uint32_t port_id, ssdk_init_cfg *cfg)
{
	if ((cfg->chip_type == CHIP_HPPE) &&
	    (((SSDK_PHYSICAL_PORT5 == port_id) &&
	    	(cfg->mac_mode1 == PORT_WRAPPER_10GBASE_R)) ||
	    ((SSDK_PHYSICAL_PORT6 == port_id) &&
	    	(cfg->mac_mode2 == PORT_WRAPPER_10GBASE_R))))
		return A_TRUE;
	else
		return A_FALSE;
}

a_uint32_t hsl_phyid_get(a_uint32_t dev_id,
		a_uint32_t port_id, ssdk_init_cfg *cfg)
{
	a_uint16_t org_id = 0, rev_id = 0;
	a_uint32_t reg_pad = 0, phy_id = 0;

	if (hsl_port_is_sfp(dev_id, port_id, cfg))
		return SFP_PHY;

	if (phy_info[dev_id]->phy_c45[port_id] == A_TRUE)
		reg_pad = BIT(30) | BIT(16);

#if defined(IN_PHY_I2C_MODE)
	if (hsl_port_phy_access_type_get(dev_id, port_id) == PHY_I2C_ACCESS) {
		cfg->reg_func.i2c_get(dev_id,
				phy_info[dev_id]->phy_address[port_id], reg_pad | 2, &org_id);
		cfg->reg_func.i2c_get(dev_id,
				phy_info[dev_id]->phy_address[port_id], reg_pad | 3, &rev_id);
	}
	else
#endif
	{
		cfg->reg_func.mdio_get(dev_id,
				phy_info[dev_id]->phy_address[port_id], reg_pad | 2, &org_id);
		cfg->reg_func.mdio_get(dev_id,
				phy_info[dev_id]->phy_address[port_id], reg_pad | 3, &rev_id);
	}

	phy_id = (org_id<<16) | rev_id;

	return phy_id;
}

phy_type_t hsl_phytype_get_by_phyid(a_uint32_t dev_id, a_uint32_t phy_id)
{
	phy_type_t phytype = MAX_PHY_CHIP;

	switch (phy_id)
	{
		case F1V1_PHY:
		case F1V2_PHY:
		case F1V3_PHY:
		case F1V4_PHY:
			phytype = F1_PHY_CHIP;
			break;
		case F2V1_PHY:
			phytype = F2_PHY_CHIP;
			break;
		case MALIBU2PORT_PHY:
		case MALIBU5PORT_PHY:
			phytype = MALIBU_PHY_CHIP;
			break;
		case AQUANTIA_PHY_107:
		case AQUANTIA_PHY_108:
		case AQUANTIA_PHY_109:
		case AQUANTIA_PHY_111:
		case AQUANTIA_PHY_111B0:
		case AQUANTIA_PHY_112:
			phytype = AQUANTIA_PHY_CHIP;
			break;
		case QCA8030_PHY:
		case QCA8033_PHY:
		case QCA8035_PHY:
			phytype = QCA803X_PHY_CHIP;
			break;
		case SFP_PHY:
			phytype = SFP_PHY_CHIP;
			break;
		case QCA8081_PHY:
			phytype = QCA808X_PHY_CHIP;
			break;
		default:
			phytype = MAX_PHY_CHIP;
	}

	return phytype;
}

sw_error_t hsl_phydriver_update(a_uint32_t dev_id, a_uint32_t port_id,
	a_uint32_t mode)
{
	a_uint32_t phy_id;
	phy_type_t phytype;
	ssdk_init_cfg cfg;

	cfg.chip_type = CHIP_HPPE;
	if(port_id == SSDK_PHYSICAL_PORT5)
	{
		cfg.mac_mode1 = mode;
	}
	else if(port_id == SSDK_PHYSICAL_PORT6)
	{
		cfg.mac_mode2 = mode;
	}
	else
	{
		return SW_NOT_SUPPORTED;
	}
	cfg.reg_func.mdio_get = reduce_hsl_phy_get;

	phy_id = hsl_phyid_get(dev_id, port_id, &cfg);
	phytype = hsl_phytype_get_by_phyid(dev_id, phy_id);
	SSDK_DEBUG("port_id is %x, phy_id is %x, phy_type is:%x\n",
		port_id, phy_id, phytype);
	if (MAX_PHY_CHIP != phytype)
	{
		phy_info[dev_id]->phy_type[port_id] = phytype;
		ssdk_phy_driver[phytype].port_bmp[dev_id] |= (0x1 << port_id);
	}

	return SW_OK;
}

int ssdk_phy_driver_init(a_uint32_t dev_id, ssdk_init_cfg *cfg)
{

	int i = 0;
	a_uint32_t phy_id = 0;
	phy_type_t phytype = MAX_PHY_CHIP;

	for (i = 0; i < SW_MAX_NR_PORT; i++)
	{
		if (port_bmp[dev_id] & (0x1 << i))
		{
			phy_id = hsl_phyid_get(dev_id, i, cfg);
			phytype = hsl_phytype_get_by_phyid(dev_id, phy_id);
			if (MAX_PHY_CHIP != phytype) {
				phy_info[dev_id]->phy_type[i] = phytype;
				ssdk_phy_driver[phytype].port_bmp[dev_id] |= (0x1 << i);
			} else {
				SSDK_INFO("dev_id = %d, phy_adress = %d, phy_id = 0x%x phy\
				type doesn't match\n",dev_id, phy_info[dev_id]->phy_address[i],
				phy_id);
			}
		}
	}

	for(i = 0; i < MAX_PHY_CHIP;i++) {
		if(ssdk_phy_driver[i].port_bmp[dev_id] != 0 &&
			ssdk_phy_driver[i].init != NULL) {
			ssdk_phy_driver[i].init(dev_id, ssdk_phy_driver[i].port_bmp[dev_id]);
		}
	}
	return 0;
}
int qca_ssdk_phy_info_init(a_uint32_t dev_id)
{
	a_uint32_t j = 0;
	phy_info_t *phy_information;

	phy_information = kzalloc(sizeof(phy_info_t), GFP_KERNEL);
	if (phy_information == NULL) {
		SSDK_ERROR("phy_information kzalloc failed!\n");
		return -ENOMEM;
	}
	memset(phy_information, 0, sizeof(*phy_information));
	phy_info[dev_id] = phy_information;

	for (j = SSDK_PHYSICAL_PORT0; j < SW_MAX_NR_PORT; j ++)
	{
		if(j == SSDK_PHYSICAL_PORT0)
		{
			phy_info[dev_id]->phy_address[j] = INVALID_PHY_ADDR;
		}
		else
		{
			phy_info[dev_id]->phy_address[j] = j - 1;
		}
	}

	return 0;
}
void qca_ssdk_port_bmp_init(a_uint32_t dev_id)
{
	port_bmp[dev_id] = 0x3e;

	return;
}

void hsl_phy_address_init(a_uint32_t dev_id, a_uint32_t i,
			a_uint32_t value)
{
	phy_info[dev_id]->phy_address[i] = value;

	return;
}

void qca_ssdk_port_bmp_set(a_uint32_t dev_id, a_uint32_t value)
{
	port_bmp[dev_id] = value;

	return;
}

a_uint32_t qca_ssdk_port_bmp_get(a_uint32_t dev_id)
{

	return port_bmp[dev_id];
}

a_uint32_t qca_ssdk_phy_type_port_bmp_get(a_uint32_t dev_id,
				phy_type_t phy_type)
{

	return ssdk_phy_driver[phy_type].port_bmp[dev_id];
}

void
qca_ssdk_phy_address_set(a_uint32_t dev_id, a_uint32_t port_id,
	a_uint32_t phy_addr)
{
	 phy_info[dev_id]->phy_address[port_id] = phy_addr;

	 return;
}

a_uint32_t
qca_ssdk_port_to_phy_mdio_fake_addr(a_uint32_t dev_id, a_uint32_t port_id)
{
	return phy_info[dev_id]->phy_mdio_fake_address[port_id];
}

void qca_ssdk_phy_mdio_fake_address_set(a_uint32_t dev_id, a_uint32_t i,
			a_uint32_t value)
{
	phy_info[dev_id]->phy_mdio_fake_address[i] = value;

	return;
}

a_uint32_t
qca_ssdk_phy_mdio_fake_addr_to_port(a_uint32_t dev_id, a_uint32_t phy_mdio_fake_addr)
{
	a_uint32_t i = 0;

	for (i = 0; i < SW_MAX_NR_PORT; i ++)
	{
		if (phy_info[dev_id]->phy_mdio_fake_address[i] == phy_mdio_fake_addr)
			return i;
	}
	SSDK_ERROR("doesn't match port_id to specified phy_mdio_fake_addr !\n");
	return 0;
}

a_uint32_t
qca_ssdk_port_to_phy_addr(a_uint32_t dev_id, a_uint32_t port_id)
{
	return phy_info[dev_id]->phy_address[port_id];
}

a_uint32_t
qca_ssdk_phy_addr_to_port(a_uint32_t dev_id, a_uint32_t phy_addr)
{
	a_uint32_t i = 0;

	for (i = 0; i < SW_MAX_NR_PORT; i ++)
	{
		if (phy_info[dev_id]->phy_address[i] == phy_addr)
			return i;
	}
	SSDK_ERROR("doesn't match port_id to specified phy_addr !\n");
	return 0;
}

a_bool_t
hsl_port_phy_combo_capability_get(a_uint32_t dev_id, a_uint32_t port_id)
{
	if (dev_id >= SW_MAX_NR_DEV)
		return A_FALSE;

	return phy_info[dev_id]->phy_combo[port_id];
}

void
hsl_port_phy_combo_capability_set(a_uint32_t dev_id, a_uint32_t port_id,
		a_bool_t enable)
{
	if (dev_id >= SW_MAX_NR_DEV)
		return;

	phy_info[dev_id]->phy_combo[port_id] = enable;

	return;
}

a_uint8_t
hsl_port_phy_access_type_get(a_uint32_t dev_id, a_uint32_t port_id)
{
	if (dev_id >= SW_MAX_NR_DEV)
		return 0;

	return phy_info[dev_id]->phy_access_type[port_id];
}

void
hsl_port_phy_access_type_set(a_uint32_t dev_id, a_uint32_t port_id,
		a_uint8_t access_type)
{
	if (dev_id >= SW_MAX_NR_DEV)
		return;

	phy_info[dev_id]->phy_access_type[port_id] = access_type;

	return;
}

void
hsl_port_phy_c45_capability_set(a_uint32_t dev_id, a_uint32_t port_id,
		a_bool_t enable)
{
	phy_info[dev_id]->phy_c45[port_id] = enable;

	return;
}
sw_error_t
hsl_ssdk_phy_serdes_reset(a_uint32_t dev_id)
{
	sw_error_t rv;
	int i = 0;
	hsl_phy_ops_t *phy_drv;

	for (i = 0; i < SW_MAX_NR_PORT; i++)
	{
		if (phy_info[dev_id]->phy_type[i] == MALIBU_PHY_CHIP)
		{
			SW_RTN_ON_NULL(phy_drv = hsl_phy_api_ops_get (dev_id, i));
			if (NULL == phy_drv->phy_serdes_reset)
				return SW_NOT_SUPPORTED;
			rv = phy_drv->phy_serdes_reset(dev_id);
			return rv;
		}
	}

	return SW_OK;
}
sw_error_t
hsl_ssdk_phy_mode_set(a_uint32_t dev_id, fal_port_interface_mode_t mode)
{
	sw_error_t rv;
	a_uint32_t i = 0, phy_addr = 0;
	hsl_phy_ops_t *phy_drv;

	for (i = 0; i < SW_MAX_NR_PORT; i++)
	{
		if (phy_info[dev_id]->phy_type[i] == MALIBU_PHY_CHIP)
		{
			SW_RTN_ON_NULL(phy_drv = hsl_phy_api_ops_get (dev_id, i));
			if (NULL == phy_drv->phy_interface_mode_set)
				return SW_NOT_SUPPORTED;

			phy_addr = qca_ssdk_port_to_phy_addr(dev_id, i);
			rv = phy_drv->phy_interface_mode_set(dev_id, phy_addr, mode);
			return rv;
		}
	}

	return SW_OK;
}
sw_error_t ssdk_phy_driver_cleanup(void)
{
	a_uint32_t i = 0, j = 0;

	for (i = 0; i < MAX_PHY_CHIP;i++) {
		for (j = 0; j < SW_MAX_NR_DEV; j++) {
			if (ssdk_phy_driver[i].port_bmp[j] != 0 &&
			    ssdk_phy_driver[i].exit != NULL) {
				ssdk_phy_driver[i].exit(j, ssdk_phy_driver[i].port_bmp[j]);
			}
		}
		if(ssdk_phy_driver[i].phy_ops != NULL)
		{
			kfree(ssdk_phy_driver[i].phy_ops);
			ssdk_phy_driver[i].phy_ops = NULL;
		}
	}

	for(i = 0; i < SW_MAX_NR_DEV;i++) {

		if(phy_info[i] != NULL)
		{
			kfree(phy_info[i]);
			phy_info[i] = NULL;
		}
	}
	return SW_OK;
}

