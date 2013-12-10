/*
 * Copyright (c) 2012 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */



#include "sw.h"

#ifdef KVER32
aos_lock_t sw_hsl_api_lock;
#else
aos_lock_t sw_hsl_api_lock = aos_default_unlock;
#endif

sw_error_t
hsl_api_lock_init(void)
{
    aos_lock_init(&sw_hsl_api_lock);
    return SW_OK;
}
