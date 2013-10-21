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



#ifndef _ATHENA_FDB_H
#define _ATHENA_FDB_H

#ifdef __cplusplus
extern "C" {
#endif                          /* __cplusplus */

#include "fal/fal_fdb.h"

    sw_error_t athena_fdb_init(a_uint32_t dev_id);

#ifdef IN_FDB
#define ATHENA_FDB_INIT(rv, dev_id) \
    { \
        rv = athena_fdb_init(dev_id); \
        SW_RTN_ON_ERROR(rv); \
    }
#else
#define ATHENA_FDB_INIT(rv, dev_id)
#endif

#ifdef HSL_STANDALONG


    HSL_LOCAL sw_error_t
    athena_fdb_add(a_uint32_t dev_id, const fal_fdb_entry_t * entry);



    HSL_LOCAL sw_error_t
    athena_fdb_del_all(a_uint32_t dev_id, a_uint32_t flag);



    HSL_LOCAL sw_error_t
    athena_fdb_del_by_port(a_uint32_t dev_id, a_uint32_t port_id,
                           a_uint32_t flag);



    HSL_LOCAL sw_error_t
    athena_fdb_del_by_mac(a_uint32_t dev_id, const fal_fdb_entry_t * addr);



    HSL_LOCAL sw_error_t
    athena_fdb_first(a_uint32_t dev_id, fal_fdb_entry_t * entry);



    HSL_LOCAL sw_error_t
    athena_fdb_next(a_uint32_t dev_id, fal_fdb_entry_t * entry);

#endif

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* _ATHENA_FDB_H */

