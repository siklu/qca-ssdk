/*
 * Copyright (c) 2012 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

#ifndef _REF_MIB_H_
#define _REF_MIB_H_

#ifdef __cplusplus
extern "C" {
#endif                          /* __cplusplus */

int
qca_ar8327_sw_set_reset_mibs(struct switch_dev *dev,
			 						const struct switch_attr *attr,
			 						struct switch_val *val);

int
qca_ar8327_sw_set_port_reset_mib(struct switch_dev *dev,
			     					const struct switch_attr *attr,
			     					struct switch_val *val);


int
qca_ar8327_sw_get_port_mib(struct switch_dev *dev,
		       						const struct switch_attr *attr,
		       						struct switch_val *val);

void
qca_ar8327_sw_mib_task(struct switch_dev *dev);

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* _REF_MIB_H_ */

