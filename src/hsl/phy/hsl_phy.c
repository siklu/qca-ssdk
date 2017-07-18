/*
 * Copyright (c) 2015, 2017, The Linux Foundation. All rights reserved.
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

#include "ssdk_plat.h"

a_uint32_t phy_address[SW_MAX_NR_DEV][SW_MAX_NR_PORT] = {0};
a_uint32_t phy_type[SW_MAX_NR_DEV][SW_MAX_NR_PORT] = {0};
a_uint32_t port_bmp[SW_MAX_NR_DEV] = {0};

phy_driver_instance_t ssdk_phy_driver[] =
{
	#if defined(ISIS) ||defined(ISISC) ||defined(GARUDA)
	{F1_PHY_CHIP, {0}, NULL, f1_phy_init},
	#else
	{F1_PHY_CHIP, {0}, NULL, NULL},
	#endif
	#if defined(ATHENA) ||defined(SHIVA) ||defined(HORUS)
	{F2_PHY_CHIP, {0}, NULL, f2_phy_init},
	#else
	{F2_PHY_CHIP, {0}, NULL, NULL},
	#endif
	#ifdef IN_MALIBU_PHY
	{MALIBU_PHY_CHIP, {0}, NULL, malibu_phy_init},
	#else
	{MALIBU_PHY_CHIP, {0}, NULL, NULL},
	#endif
	#ifdef IN_AQUANTIA_PHY
	{AQUANTIA_PHY_CHIP, {0}, NULL, aquantia_phy_init},
	#else
	{AQUANTIA_PHY_CHIP, {0}, NULL, NULL},
	#endif
	{MAX_PHY_CHIP, {0}, NULL, NULL}
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

	phytype = phy_type[dev_id][port_id];

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

int ssdk_phy_driver_init(a_uint32_t dev_id, ssdk_init_cfg *cfg)
{

	int i = 0;
	a_uint16_t org_id = 0, rev_id = 0;
	a_uint32_t phy_id = 0, xgphy_id = 0;
	phy_type_t phytype = MAX_PHY_CHIP;

	for (i = 0; i < SW_MAX_NR_PORT; i++)
	{
		if (port_bmp[dev_id] & (0x1 << i))
		{
			cfg->reg_func.mdio_get(dev_id, phy_address[dev_id][i], 2, &org_id);
			cfg->reg_func.mdio_get(dev_id, phy_address[dev_id][i], 3, &rev_id);
			phy_id = (org_id<<16) | rev_id;
			cfg->reg_func.mdio_get(dev_id, phy_address[dev_id][i], ((1<<30) |(1<<16) |2), &org_id);
			cfg->reg_func.mdio_get(dev_id, phy_address[dev_id][i], ((1<<30) |(1<<16) |3), &rev_id);
			xgphy_id = (org_id<<16) | rev_id;

			if ((phy_id == F1V1_PHY) || (phy_id == F1V2_PHY) ||
				(phy_id == F1V3_PHY) || (phy_id == F1V4_PHY))
				phytype = F1_PHY_CHIP;
			else if (phy_id == F2V1_PHY)
				phytype = F2_PHY_CHIP;
			else if ((phy_id == MALIBU2PORT_PHY) || (phy_id == MALIBU5PORT_PHY))
				phytype = MALIBU_PHY_CHIP;
			else if ((phy_id == AQUANTIA_PHY_107) || (xgphy_id == AQUANTIA_PHY_107)
				|| (phy_id == AQUANTIA_PHY_109) || (xgphy_id == AQUANTIA_PHY_109))
				phytype = AQUANTIA_PHY_CHIP;
			else
			{
				SSDK_INFO("phy type doesn't match!\n");
				continue;
			}
			phy_type[dev_id][i] = phytype;
			ssdk_phy_driver[phytype].port_bmp[dev_id] |= (0x1 << i);
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
void qca_ssdk_phy_address_init(a_uint32_t dev_id)
{
	a_uint32_t j = 0;

	for (j = 1; j < SW_MAX_NR_PORT; j ++)
	{
		phy_address[dev_id][j] = j - 1;
	}
	return;
}
void qca_ssdk_port_bmp_init(a_uint32_t dev_id)
{
	port_bmp[dev_id] = 0x3e;

	return;
}

void qca_ssdk_phy_address_set(a_uint32_t dev_id, a_uint32_t i,
			a_uint32_t value)
{
	phy_address[dev_id][i] = value;

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

a_uint32_t
qca_ssdk_port_to_phy_addr(a_uint32_t dev_id, a_uint32_t port_id)
{
	return phy_address[dev_id][port_id];
}

a_uint32_t
qca_ssdk_phy_addr_to_port(a_uint32_t dev_id, a_uint32_t phy_addr)
{
	a_uint32_t i = 0;

	for (i = 0; i < SW_MAX_NR_PORT; i ++)
	{
		if (phy_address[dev_id][i] == phy_addr)
			return i;
	}
	SSDK_ERROR("doesn't match port_id to specified phy_addr !\n");
	return 0;
}

sw_error_t ssdk_phy_driver_cleanup(void)
{
	a_uint32_t i = 0;

	for(i = 0; i < MAX_PHY_CHIP;i++) {

		if(ssdk_phy_driver[i].phy_ops != NULL)
		{
			kfree(ssdk_phy_driver[i].phy_ops);
			ssdk_phy_driver[i].phy_ops = NULL;
		}
	}
	return SW_OK;
}

