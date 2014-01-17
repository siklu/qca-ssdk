/*
 * Copyright (c) 2012 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

#ifdef KVER32
#include <linux/kconfig.h> 
#include <generated/autoconf.h>
#else
#include <linux/autoconf.h>
#endif

#include "nat_helper.h"

sw_error_t
nat_helper_init(uint32_t dev_id)
{
    host_helper_init();
    napt_helper_init();
    nat_ipt_helper_init();

    aos_printk("Hello, nat helper module for 1.1!\n");

    return SW_OK;
}

sw_error_t
nat_helper_cleanup(uint32_t dev_id)
{
    host_helper_exit();
    napt_helper_exit();
    nat_ipt_helper_exit();

    aos_printk("Goodbye, nat helper module!\n");

    return SW_OK;
}

