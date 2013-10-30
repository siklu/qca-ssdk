/*
 * Copyright (c) 2012 Qualcomm Atheros, Inc.
 * All rights reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 *
 */

#ifndef _REF_PORT_CTRL_H_
#define _REF_PORT_CTRL_H_

#ifdef __cplusplus
extern "C" {
#endif                          /* __cplusplus */

int
qca_ar8327_sw_get_port_link(struct switch_dev *dev, int port,
			                        struct switch_port_link *link);

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* _REF_PORT_CTRL_H_ */

