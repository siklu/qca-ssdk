/*
 * Copyright (c) 2012 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

#include "sw.h"
#include "ssdk_init.h"
#include "fal_init.h"
#include "fal_misc.h"
#include "fal_mib.h"
#include "fal_port_ctrl.h"
#include "fal_portvlan.h"
#include "fal_fdb.h"
#include "fal_stp.h"
#include "fal_igmp.h"
#include "fal_qos.h"
#include "hsl.h"
#include "hsl_dev.h"
#include "ssdk_init.h"
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/phy.h>
#include <linux/platform_device.h>
#include <linux/types.h>
#include <asm/mach-types.h>
#include <linux/kconfig.h>
#include <generated/autoconf.h>
#include <net/switch.h>
#include <linux/delay.h>
#include <linux/phy.h>
#include <linux/netdevice.h>
#include <linux/ar8216_platform.h>
#include "ssdk_plat.h"
#include "ref_vlan.h"

int
qca_ar8327_sw_set_vlan(struct switch_dev *dev,
                       const struct switch_attr *attr,
                       struct switch_val *val)
{
    struct qca_phy_priv *priv = qca_phy_priv_get(dev);

    priv->vlan = !!val->value.i;

    return 0;
}

int
qca_ar8327_sw_get_vlan(struct switch_dev *dev,
                       const struct switch_attr *attr,
                       struct switch_val *val)
{
    struct qca_phy_priv *priv = qca_phy_priv_get(dev);

    val->value.i = priv->vlan;

    return 0;
}

int
qca_ar8327_sw_set_vid(struct switch_dev *dev,
                      const struct switch_attr *attr,
                      struct switch_val *val)
{
    struct qca_phy_priv *priv = qca_phy_priv_get(dev);

    priv->vlan_id[val->port_vlan] = val->value.i;

    return 0;
}

int
qca_ar8327_sw_get_vid(struct switch_dev *dev,
                      const struct switch_attr *attr,
                      struct switch_val *val)
{
    struct qca_phy_priv *priv = qca_phy_priv_get(dev);

    val->value.i = priv->vlan_id[val->port_vlan];

    return 0;
}

int
qca_ar8327_sw_get_pvid(struct switch_dev *dev, int port, int *vlan)
{
    struct qca_phy_priv *priv = qca_phy_priv_get(dev);

    *vlan = priv->pvid[port];

    return 0;
}

int
qca_ar8327_sw_set_pvid(struct switch_dev *dev, int port, int vlan)
{
    struct qca_phy_priv *priv = qca_phy_priv_get(dev);

    /* make sure no invalid PVIDs get set */
    if (vlan >= dev->vlans)
        return -1;

    priv->pvid[port] = vlan;

    return 0;
}

int
qca_ar8327_sw_get_ports(struct switch_dev *dev, struct switch_val *val)
{
    struct qca_phy_priv *priv = qca_phy_priv_get(dev);
    a_uint8_t ports = priv->vlan_table[val->port_vlan];
    int i;

    val->len = 0;
    for (i = 0; i < dev->ports; i++) {
        struct switch_port *p;

        if (!(ports & (1 << i)))
            continue;

        p = &val->value.ports[val->len++];
        p->id = i;
        if (priv->vlan_tagged & (1 << i))
            p->flags = (1 << SWITCH_PORT_FLAG_TAGGED);
        else
            p->flags = 0;
    }

    return 0;
}

int
qca_ar8327_sw_set_ports(struct switch_dev *dev, struct switch_val *val)
{
    struct qca_phy_priv *priv = qca_phy_priv_get(dev);
    a_uint8_t *vt = &priv->vlan_table[val->port_vlan];
    int i, j;

    *vt = 0;
    for (i = 0; i < val->len; i++) {
        struct switch_port *p = &val->value.ports[i];

        if (p->flags & (1 << SWITCH_PORT_FLAG_TAGGED)) {
            priv->vlan_tagged |= (1 << p->id);
        } else {
            priv->vlan_tagged &= ~(1 << p->id);
            priv->pvid[p->id] = val->port_vlan;

            /* make sure that an untagged port does not
             * appear in other vlans */
            for (j = 0; j < AR8327_MAX_VLANS; j++) {
                if (j == val->port_vlan)
                    continue;
                priv->vlan_table[j] &= ~(1 << p->id);
            }
        }

        *vt |= 1 << p->id;
    }

    return 0;
}

int
qca_ar8327_sw_hw_apply(struct switch_dev *dev)
{
    struct qca_phy_priv *priv = qca_phy_priv_get(dev);
    fal_pbmp_t portmask[AR8327_NUM_PORTS];
    int i, j;

    mutex_lock(&priv->reg_mutex);

    /* flush all vlan translation unit entries */
    fal_vlan_flush(0);

    memset(portmask, 0, sizeof(portmask));
    if (!priv->init) {
        /* calculate the port destination masks and load vlans
         * into the vlan translation unit */
        for (j = 0; j < AR8327_MAX_VLANS; j++) {
            u8 vp = priv->vlan_table[j];

            if (!vp)
            continue;

            fal_vlan_create(0, priv->vlan_id[j]);

            for (i = 0; i < dev->ports; i++) {
                u8 mask = (1 << i);
                if (vp & mask) {
                    fal_vlan_member_add(0, priv->vlan_id[j], i,
                           (mask & priv->vlan_tagged)? FAL_EG_TAGGED : FAL_EG_UNTAGGED);
                    portmask[i] |= vp & ~mask;
                }
            }

        }
    } else {
        /* vlan disabled:
         * isolate all ports, but connect them to the cpu port */
        for (i = 0; i < dev->ports; i++) {
            if (i == AR8327_PORT_CPU)
                continue;

            portmask[i] = 1 << AR8327_PORT_CPU;
            portmask[AR8327_PORT_CPU] |= (1 << i);
        }
    }

    /* update the port destination mask registers and tag settings */
    for (i = 0; i < dev->ports; i++) {
        int pvid;
        fal_pt_1qmode_t ingressMode;
        fal_pt_1q_egmode_t egressMode;

        if (priv->vlan) {
            pvid = priv->vlan_id[priv->pvid[i]];
            if (priv->vlan_tagged & (1 << i)) {
                egressMode = FAL_EG_TAGGED;
            } else {
                egressMode = FAL_EG_UNTAGGED;
            }

            ingressMode = FAL_1Q_SECURE;
        } else {
            pvid = i;
            egressMode = FAL_EG_UNTOUCHED;
            ingressMode = FAL_1Q_DISABLE;
        }

        fal_port_1qmode_set(0, i, ingressMode);
        fal_port_egvlanmode_set(0, i, egressMode);
        fal_port_default_cvid_set(0, i, pvid);
        fal_portvlan_member_update(0, i, portmask[i]);
    }

    mutex_unlock(&priv->reg_mutex);

    return 0;
}


