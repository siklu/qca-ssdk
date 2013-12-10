/*
 * Copyright (c) 2012 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

#ifndef _REF_VLAN_H_
#define _REF_VLAN_H_

#ifdef __cplusplus
extern "C" {
#endif                          /* __cplusplus */

int
qca_ar8327_sw_set_vlan(struct switch_dev *dev,
                       const struct switch_attr *attr,
                       struct switch_val *val);

int
qca_ar8327_sw_get_vlan(struct switch_dev *dev,
                       const struct switch_attr *attr,
                       struct switch_val *val);

int
qca_ar8327_sw_set_vid(struct switch_dev *dev,
                      const struct switch_attr *attr,
                      struct switch_val *val);

int
qca_ar8327_sw_get_vid(struct switch_dev *dev,
                      const struct switch_attr *attr,
                      struct switch_val *val);

int
qca_ar8327_sw_get_pvid(struct switch_dev *dev, int port, int *vlan);

int
qca_ar8327_sw_set_pvid(struct switch_dev *dev, int port, int vlan);

int
qca_ar8327_sw_get_ports(struct switch_dev *dev, struct switch_val *val);

int
qca_ar8327_sw_set_ports(struct switch_dev *dev, struct switch_val *val);

int
qca_ar8327_sw_hw_apply(struct switch_dev *dev);

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* _REF_VLAN_H_ */

