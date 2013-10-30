/*
 * Copyright (c) 2012 Qualcomm Atheros, Inc.
 * All rights reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 *
 */

#ifndef _REF_FDB_H_
#define _REF_FDB_H_

#ifdef __cplusplus
extern "C" {
#endif                          /* __cplusplus */


int
qca_ar8327_sw_atu_flush(struct qca_phy_priv *priv);

int
qca_ar8327_sw_atu_dump(struct switch_dev *dev,
		       		const struct switch_attr *attr,
		       		struct switch_val *val);


#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* _REF_FDB_H_ */

