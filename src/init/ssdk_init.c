/*
 * Copyright (c) 2012 Qualcomm Atheros, Inc.
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
#include "ssdk_init.h"
#include "fal_init.h"
#include "hsl.h"
#include "hsl_dev.h"
#include "ssdk_init.h"
#include <linux/kernel.h> 
#include <linux/module.h> 
#include <linux/phy.h>
#include <linux/platform_device.h>
#include <linux/types.h>

#define IPQ806X_MDIO_BUS_NAME			"mdio-gpio"
#define IPQ806X_MDIO_BUS_NUM			0
#define IPQ806X_MDIO_BUS_MAX			1

static struct mii_bus *miibus = NULL;

sw_error_t
ssdk_init(a_uint32_t dev_id, ssdk_init_cfg * cfg)
{
    sw_error_t rv;

#if (defined(KERNEL_MODULE) && defined(USER_MODE))
    rv = hsl_dev_init(dev_id, cfg);
#else
#ifdef HSL_STANDALONG
    rv = hsl_dev_init(dev_id, cfg);
#else
    rv = fal_init(dev_id, cfg);
#endif
#endif

    return rv;
}

sw_error_t
ssdk_reduced_init(a_uint32_t dev_id, hsl_init_mode cpu_mode,
                  hsl_access_mode reg_mode)
{
    sw_error_t rv;

#if (defined(KERNEL_MODULE) && defined(USER_MODE))
    rv = hsl_dev_reduced_init(dev_id, cpu_mode, reg_mode);
#else
#ifdef HSL_STANDALONG
    rv = hsl_dev_reduced_init(dev_id, cpu_mode, reg_mode);
#else
    rv = fal_reduced_init(dev_id, cpu_mode, reg_mode);
#endif
#endif

    return rv;
}

sw_error_t
ssdk_cleanup(void)
{
    sw_error_t rv;

#if (defined(KERNEL_MODULE) && defined(USER_MODE))
    rv = hsl_dev_cleanup();
#else
#ifdef HSL_STANDALONG
    rv = hsl_dev_cleanup();
#else
    rv = fal_cleanup();
#endif
#endif

    return rv;
}

sw_error_t
ssdk_hsl_access_mode_set(a_uint32_t dev_id, hsl_access_mode reg_mode)
{
    sw_error_t rv;

    rv = hsl_access_mode_set(dev_id, reg_mode);
    return rv;
}

static inline void
split_addr(uint32_t regaddr, uint16_t *r1, uint16_t *r2, uint16_t *page)
{
	regaddr >>= 1;
	*r1 = regaddr & 0x1e;

	regaddr >>= 5;
	*r2 = regaddr & 0x7;

	regaddr >>= 3;
	*page = regaddr & 0x3ff;
}

uint32_t
qca_ar8216_mii_read(int reg)
{
	struct mii_bus *bus = miibus;
	uint16_t r1, r2, page;
	uint16_t lo, hi;

	split_addr((uint32_t) reg, &r1, &r2, &page);

	mutex_lock(&bus->mdio_lock);

	bus->write(bus, 0x18, 0, page);
	usleep_range(1000, 2000); /* wait for the page switch to propagate */
	lo = bus->read(bus, 0x10 | r2, r1);
	hi = bus->read(bus, 0x10 | r2, r1 + 1);

	mutex_unlock(&bus->mdio_lock);

	return (hi << 16) | lo;
}

void
qca_ar8216_mii_write(int reg, uint32_t val)
{
	struct mii_bus *bus = miibus;
	uint16_t r1, r2, r3;
	uint16_t lo, hi;

	split_addr((u32) reg, &r1, &r2, &r3);
	lo = val & 0xffff;
	hi = (u16) (val >> 16);

	mutex_lock(&bus->mdio_lock);

	bus->write(bus, 0x18, 0, r3);
	usleep_range(1000, 2000); /* wait for the page switch to propagate */
	bus->write(bus, 0x10 | r2, r1, lo);
	bus->write(bus, 0x10 | r2, r1 + 1, hi);

	mutex_unlock(&bus->mdio_lock);
}

static sw_error_t qca_ar8216_phy_read(a_uint32_t dev_id, a_uint32_t phy_addr, 
                                    a_uint32_t reg, a_uint16_t* data)

{
    struct mii_bus *bus = miibus;
    
    mutex_lock(&bus->mdio_lock);
    *data = bus->read(bus, phy_addr, reg);
    mutex_unlock(&bus->mdio_lock);
    
    return 0;
}

static sw_error_t qca_ar8216_phy_write(a_uint32_t dev_id, a_uint32_t phy_addr, 
                                    a_uint32_t reg, a_uint16_t data)
{
    struct mii_bus *bus = miibus;
    
    mutex_lock(&bus->mdio_lock);
    bus->write(bus, phy_addr, reg, data);
    mutex_unlock(&bus->mdio_lock);

    return 0;
}

static int miibus_get()
{
    struct device *miidev;
    uint8_t busid[MII_BUS_ID_SIZE];
	snprintf(busid, MII_BUS_ID_SIZE, "%s.%d", IPQ806X_MDIO_BUS_NAME, IPQ806X_MDIO_BUS_NUM);

	miidev = bus_find_device_by_name(&platform_bus_type, NULL, busid);
	if (!miidev) {
		printk("cannot get mii bus\n");
		return 1;
	}

	miibus = dev_get_drvdata(miidev);
	if(!miidev){
	    printk("mdio bus '%s' get FAIL\n", busid);
	    return 1;
	}

	return 0;

}

static int __init
regi_init(void)
{
    int phy_addr; 
    ssdk_init_cfg cfg;
    int rv = 0;
    
	miibus_get();
    garuda_init_spec_cfg chip_spec_cfg;

    memset(&cfg, 0, sizeof(ssdk_init_cfg));
    memset(&chip_spec_cfg, 0, sizeof(garuda_init_spec_cfg));

    cfg.cpu_mode = HSL_CPU_1;
    cfg.reg_mode = HSL_MDIO;
    cfg.nl_prot = 30;

    #ifdef QCA_SWITCH_S17
    cfg.chip_type = CHIP_ISIS;
    #else
    cfg.chip_type = CHIP_ISISC;
    #endif

    cfg.chip_spec_cfg = &chip_spec_cfg;
    cfg.reg_func.mdio_set = qca_ar8216_phy_write;      //   parameters 
    cfg.reg_func.mdio_get = qca_ar8216_phy_read;

	
    rv = ssdk_init(0, &cfg);
    if (rv == 0)
        printk("qca-ssdk module init succeeded!\n");
    else
        printk("qca-ssdk module init failed! (code: %d)\n", rv);

	return rv;

}

static void __exit
regi_exit(void)
{
    sw_error_t rv=ssdk_cleanup();

    if (rv == 0)
    	printk("qca-ssdk module exit  done!\n");
    else
        printk("qca-ssdk module exit failed! (code: %d)\n", rv);
}

module_init(regi_init);
module_exit(regi_exit);

MODULE_DESCRIPTION("QCA SSDK Driver");
MODULE_AUTHOR("Qualcomm Atheros Inc");
MODULE_LICENSE("Dual BSD/GPL");

