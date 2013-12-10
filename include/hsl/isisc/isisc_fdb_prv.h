/*
 * Copyright (c) 2012 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */


#ifndef _ISISC_FDB_PRV_H_
#define _ISISC_FDB_PRV_H_

#ifdef __cplusplus
extern "C" {
#endif                          /* __cplusplus */


#define ARL_FLUSH_ALL             1
#define ARL_LOAD_ENTRY            2
#define ARL_PURGE_ENTRY           3
#define ARL_FLUSH_ALL_UNLOCK      4
#define ARL_FLUSH_PORT_UNICAST    5
#define ARL_NEXT_ENTRY            6
#define ARL_FIND_ENTRY            7
#define ARL_TRANSFER_ENTRY        8

#define ARL_FIRST_ENTRY           1001
#define ARL_FLUSH_PORT_NO_STATIC  1002
#define ARL_FLUSH_PORT_AND_STATIC 1003

#define ISISC_MAX_FID                   4095
#define ISISC_MAX_LEARN_LIMIT_CNT       2048
#define ISISC_MAX_PORT_LEARN_LIMIT_CNT  1024

    sw_error_t
    inter_isisc_fdb_flush(a_uint32_t dev_id, a_uint32_t flag);


#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* _ISISC_FDB_PRV_H_ */

