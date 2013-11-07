/*
 * Copyright (c) 2012 Qualcomm Atheros, Inc.
 * All rights reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 *
 */

#ifndef _REF_MISC_H_
#define _REF_MISC_H_

#ifdef __cplusplus
extern "C" {
#endif                          /* __cplusplus */

int
qca_ar8327_sw_set_max_frame_size(struct switch_dev *dev,
										const struct switch_attr *attr,
		   								struct switch_val *val);

int
qca_ar8327_sw_get_max_frame_size(struct switch_dev *dev,
										const struct switch_attr *attr,
		   								struct switch_val *val);

int
qca_ar8327_sw_reset_switch(struct switch_dev *dev);

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* _REF_MISC_H_ */

