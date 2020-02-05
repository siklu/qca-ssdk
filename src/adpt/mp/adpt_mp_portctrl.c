/*
 * Copyright (c) 2020, The Linux Foundation. All rights reserved.
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

#include "sw.h"
#include "mp_portctrl_reg.h"
#include "mp_portctrl.h"
#include "adpt.h"
#include "adpt_mp.h"
#include "adpt_mp_portctrl.h"
#include "hsl_port_prop.h"
#include "hsl_phy.h"

static sw_error_t
adpt_mp_port_txmac_status_set(a_uint32_t dev_id, fal_port_t port_id,
		a_bool_t enable)
{
	sw_error_t rv = SW_OK;
	a_uint32_t gmac_id = 0;
	union mac_configuration_u configuration;

	ADPT_DEV_ID_CHECK(dev_id);
	MP_PORT_ID_CHECK(port_id);

	memset(&configuration, 0, sizeof(configuration));
	gmac_id = MP_PORT_TO_GMAC_ID(port_id);

	rv = mp_mac_configuration_get(dev_id, gmac_id, &configuration);
	SW_RTN_ON_ERROR(rv);

	configuration.bf.tx_enable = enable;
	rv = mp_mac_configuration_set(dev_id, gmac_id, &configuration);

	return rv;
}

static sw_error_t
adpt_mp_port_txmac_status_get(a_uint32_t dev_id, fal_port_t port_id,
		a_bool_t *enable)
{
	sw_error_t rv = SW_OK;
	a_uint32_t gmac_id = 0;
	union mac_configuration_u configuration;

	ADPT_DEV_ID_CHECK(dev_id);
	MP_PORT_ID_CHECK(port_id);
	ADPT_NULL_POINT_CHECK(enable);

	memset(&configuration, 0, sizeof(configuration));
	gmac_id = MP_PORT_TO_GMAC_ID(port_id);

	rv = mp_mac_configuration_get(dev_id, gmac_id, &configuration);
	SW_RTN_ON_ERROR(rv);

	*enable = configuration.bf.tx_enable;

	return rv;
}

static sw_error_t
adpt_mp_port_rxmac_status_set(a_uint32_t dev_id, fal_port_t port_id,
		a_bool_t enable)
{
	sw_error_t rv = SW_OK;
	a_uint32_t gmac_id = 0;
	union mac_configuration_u configuration;

	ADPT_DEV_ID_CHECK(dev_id);
	MP_PORT_ID_CHECK(port_id);

	memset(&configuration, 0, sizeof(configuration));
	gmac_id = MP_PORT_TO_GMAC_ID(port_id);

	rv = mp_mac_configuration_get(dev_id, gmac_id, &configuration);
	SW_RTN_ON_ERROR(rv);

	configuration.bf.rx_enable = enable;
	rv = mp_mac_configuration_set(dev_id, gmac_id, &configuration);

	return rv;
}

static sw_error_t
adpt_mp_port_rxmac_status_get(a_uint32_t dev_id, fal_port_t port_id,
		a_bool_t *enable)
{
	sw_error_t rv = SW_OK;
	a_uint32_t gmac_id = 0;
	union mac_configuration_u configuration;

	ADPT_DEV_ID_CHECK(dev_id);
	MP_PORT_ID_CHECK(port_id);
	ADPT_NULL_POINT_CHECK(enable);

	memset(&configuration, 0, sizeof(configuration));
	gmac_id = MP_PORT_TO_GMAC_ID(port_id);

	rv = mp_mac_configuration_get(dev_id, gmac_id, &configuration);
	SW_RTN_ON_ERROR(rv);

	*enable = configuration.bf.rx_enable;

	return rv;
}

static sw_error_t
adpt_mp_port_txfc_status_set(a_uint32_t dev_id, fal_port_t port_id,
	a_bool_t enable)
{
	sw_error_t rv = SW_OK;
	a_uint32_t gmac_id = 0;
	union mac_flow_ctrl_u mac_flow_ctrl;
	struct qca_phy_priv *priv = ssdk_phy_priv_data_get(dev_id);

	ADPT_DEV_ID_CHECK(dev_id);
	MP_PORT_ID_CHECK(port_id);
	ADPT_NULL_POINT_CHECK(priv);

	memset(&mac_flow_ctrl, 0, sizeof(mac_flow_ctrl));
	gmac_id = MP_PORT_TO_GMAC_ID(port_id);

	rv = mp_mac_flowctrl_get(dev_id, gmac_id, &mac_flow_ctrl);
	SW_RTN_ON_ERROR(rv);

	if (A_TRUE == enable) {
		mac_flow_ctrl.bf.flowctrl_tx_enable = 1;
		mac_flow_ctrl.bf.pause_time = GMAC_PAUSE_TIME;
	} else {
		mac_flow_ctrl.bf.flowctrl_tx_enable = 0;
	}

	rv = mp_mac_flowctrl_set(dev_id, gmac_id, &mac_flow_ctrl);

	priv->port_old_tx_flowctrl[port_id - 1] = enable;

	return rv;
}

static sw_error_t
adpt_mp_port_txfc_status_get(a_uint32_t dev_id, fal_port_t port_id,
	a_bool_t * enable)
{
	sw_error_t rv = SW_OK;
	a_uint32_t gmac_id = 0;
	union mac_flow_ctrl_u mac_flow_ctrl;

	ADPT_DEV_ID_CHECK(dev_id);
	MP_PORT_ID_CHECK(port_id);
	ADPT_NULL_POINT_CHECK(enable);

	memset(&mac_flow_ctrl, 0, sizeof(mac_flow_ctrl));
	gmac_id = MP_PORT_TO_GMAC_ID(port_id);

	rv = mp_mac_flowctrl_get(dev_id, gmac_id, &mac_flow_ctrl);
	SW_RTN_ON_ERROR(rv);

	if (mac_flow_ctrl.bf.flowctrl_tx_enable) {
		*enable = A_TRUE;
	} else {
		*enable = A_FALSE;
	}

	return rv;
}

static sw_error_t
adpt_mp_port_rxfc_status_set(a_uint32_t dev_id, fal_port_t port_id,
	a_bool_t enable)
{
	sw_error_t rv = SW_OK;
	a_uint32_t gmac_id = 0;
	union mac_flow_ctrl_u mac_flow_ctrl;
	struct qca_phy_priv *priv = ssdk_phy_priv_data_get(dev_id);

	ADPT_DEV_ID_CHECK(dev_id);
	MP_PORT_ID_CHECK(port_id);
	ADPT_NULL_POINT_CHECK(priv);

	memset(&mac_flow_ctrl, 0, sizeof(mac_flow_ctrl));
	gmac_id = MP_PORT_TO_GMAC_ID(port_id);

	rv = mp_mac_flowctrl_get(dev_id, gmac_id, &mac_flow_ctrl);
	SW_RTN_ON_ERROR(rv);

	if (A_TRUE == enable) {
		mac_flow_ctrl.bf.flowctrl_rx_enable = 1;
	} else {
		mac_flow_ctrl.bf.flowctrl_rx_enable = 0;
	}

	rv = mp_mac_flowctrl_set(dev_id, gmac_id, &mac_flow_ctrl);

	priv->port_old_rx_flowctrl[port_id - 1] = enable;

	return rv;
}

static sw_error_t
adpt_mp_port_rxfc_status_get(a_uint32_t dev_id, fal_port_t port_id,
	a_bool_t * enable)
{
	sw_error_t rv = SW_OK;
	a_uint32_t gmac_id = 0;
	union mac_flow_ctrl_u mac_flow_ctrl;

	ADPT_DEV_ID_CHECK(dev_id);
	MP_PORT_ID_CHECK(port_id);
	ADPT_NULL_POINT_CHECK(enable);

	memset(&mac_flow_ctrl, 0, sizeof(mac_flow_ctrl));
	gmac_id = MP_PORT_TO_GMAC_ID(port_id);

	rv = mp_mac_flowctrl_get(dev_id, gmac_id, &mac_flow_ctrl);
	SW_RTN_ON_ERROR(rv);

	if (mac_flow_ctrl.bf.flowctrl_rx_enable) {
		*enable = A_TRUE;
	} else {
		*enable = A_FALSE;
	}

	return rv;
}

static sw_error_t
adpt_mp_port_flowctrl_set(a_uint32_t dev_id, fal_port_t port_id,
	a_bool_t enable)
{
	sw_error_t rv = SW_OK;
	struct qca_phy_priv *priv = ssdk_phy_priv_data_get(dev_id);

	ADPT_DEV_ID_CHECK(dev_id);
	MP_PORT_ID_CHECK(port_id);
	ADPT_NULL_POINT_CHECK(priv);

	rv = adpt_mp_port_txfc_status_set(dev_id, port_id, enable);
	SW_RTN_ON_ERROR(rv);

	rv = adpt_mp_port_rxfc_status_set(dev_id, port_id, enable);
	SW_RTN_ON_ERROR(rv);

	priv->port_old_tx_flowctrl[port_id - 1] = enable;
	priv->port_old_rx_flowctrl[port_id - 1] = enable;

	return rv;
}

static sw_error_t
adpt_mp_port_flowctrl_get(a_uint32_t dev_id, fal_port_t port_id,
	a_bool_t * enable)
{
	sw_error_t rv = SW_OK;
	a_bool_t txfc_enable, rxfc_enable;

	ADPT_DEV_ID_CHECK(dev_id);
	MP_PORT_ID_CHECK(port_id);
	ADPT_NULL_POINT_CHECK(enable);

	rv = adpt_mp_port_txfc_status_get(dev_id, port_id,  &txfc_enable);
	SW_RTN_ON_ERROR(rv);
	rv = adpt_mp_port_rxfc_status_get(dev_id, port_id,  &rxfc_enable);
	SW_RTN_ON_ERROR(rv);

	*enable = txfc_enable & rxfc_enable;

	return rv;
}

static sw_error_t
adpt_mp_port_flowctrl_forcemode_set(a_uint32_t dev_id,
	fal_port_t port_id, a_bool_t enable)
{
	sw_error_t rv = SW_OK;
	struct qca_phy_priv *priv = ssdk_phy_priv_data_get(dev_id);

	ADPT_DEV_ID_CHECK(dev_id);
	MP_PORT_ID_CHECK(port_id);
	ADPT_NULL_POINT_CHECK(priv);

	priv->port_tx_flowctrl_forcemode[port_id - 1] = enable;
	priv->port_rx_flowctrl_forcemode[port_id - 1] = enable;

	return rv;
}

static sw_error_t
adpt_mp_port_flowctrl_forcemode_get(a_uint32_t dev_id,
	fal_port_t port_id, a_bool_t *enable)
{
	sw_error_t rv = SW_OK;
	struct qca_phy_priv *priv = ssdk_phy_priv_data_get(dev_id);


	ADPT_DEV_ID_CHECK(dev_id);
	MP_PORT_ID_CHECK(port_id);
	ADPT_NULL_POINT_CHECK(enable);
	ADPT_NULL_POINT_CHECK(priv);

	*enable = (priv->port_tx_flowctrl_forcemode[port_id - 1] &
		priv->port_rx_flowctrl_forcemode[port_id - 1]);

	return rv;
}

static sw_error_t
adpt_mp_port_mac_speed_set(a_uint32_t dev_id, a_uint32_t port_id,
	fal_port_speed_t speed)
{
	sw_error_t rv = SW_OK;
	a_uint32_t gmac_id = 0;
	union mac_configuration_u configuration;

	ADPT_DEV_ID_CHECK(dev_id);
	MP_PORT_ID_CHECK(port_id);

	memset(&configuration, 0, sizeof(configuration));
	gmac_id = MP_PORT_TO_GMAC_ID(port_id);

	rv = mp_mac_configuration_get(dev_id, gmac_id, &configuration);
	SW_RTN_ON_ERROR(rv);


	if (FAL_SPEED_1000 == speed) {
		 configuration.bf.port_select = GMAC_SPEED_1000M;
	} else if (FAL_SPEED_100 == speed) {
		configuration.bf.port_select = (~GMAC_SPEED_1000M) & 0x1;
		configuration.bf.mii_speed = GMAC_SPEED_100M;
	} else if (FAL_SPEED_10== speed) {
		configuration.bf.port_select = (~GMAC_SPEED_1000M) & 0x1;
		configuration.bf.mii_speed = GMAC_SPEED_10M;
	}

	rv = mp_mac_configuration_set(dev_id, gmac_id, &configuration);

	return rv;

}

static sw_error_t
adpt_mp_port_mac_duplex_set(a_uint32_t dev_id, a_uint32_t port_id,
	fal_port_duplex_t duplex)
{
	sw_error_t rv = SW_OK;
	a_uint32_t gmac_id = 0;
	union mac_configuration_u configuration;

	ADPT_DEV_ID_CHECK(dev_id);
	MP_PORT_ID_CHECK(port_id);

	memset(&configuration, 0, sizeof(configuration));
	gmac_id = MP_PORT_TO_GMAC_ID(port_id);

	rv = mp_mac_configuration_get(dev_id, gmac_id, &configuration);
	SW_RTN_ON_ERROR(rv);

	if (FAL_FULL_DUPLEX == duplex) {
		configuration.bf.duplex = GMAC_FULL_DUPLEX;
	} else {
		configuration.bf.duplex = GMAC_HALF_DUPLEX;
	}

	rv = mp_mac_configuration_set(dev_id, gmac_id, &configuration);

	return rv;
}

static sw_error_t
adpt_mp_port_promisc_mode_set(a_uint32_t dev_id, fal_port_t port_id,
	a_bool_t enable)
{
	sw_error_t rv = SW_OK;
	a_uint32_t gmac_id = 0;
	union mac_frame_filter_u mac_frame_filter;

	ADPT_DEV_ID_CHECK(dev_id);
	MP_PORT_ID_CHECK(port_id);

	memset(&mac_frame_filter, 0, sizeof(mac_frame_filter));
	gmac_id = MP_PORT_TO_GMAC_ID(port_id);

	rv = mp_mac_frame_filter_get(dev_id, gmac_id, &mac_frame_filter);
	SW_RTN_ON_ERROR(rv);

	mac_frame_filter.bf.promiscuous_mode = enable;

	rv = mp_mac_frame_filter_set(dev_id, gmac_id, &mac_frame_filter);

	return rv;
}

static sw_error_t
adpt_mp_port_promisc_mode_get(a_uint32_t dev_id, fal_port_t port_id,
	a_bool_t *enable)
{
	sw_error_t rv = SW_OK;
	a_uint32_t gmac_id = 0;
	union mac_frame_filter_u mac_frame_filter;

	ADPT_DEV_ID_CHECK(dev_id);
	MP_PORT_ID_CHECK(port_id);
	ADPT_NULL_POINT_CHECK(enable);

	memset(&mac_frame_filter, 0, sizeof(mac_frame_filter));
	gmac_id = MP_PORT_TO_GMAC_ID(port_id);

	rv = mp_mac_frame_filter_get(dev_id, gmac_id, &mac_frame_filter);
	SW_RTN_ON_ERROR(rv);

	*enable = mac_frame_filter.bf.promiscuous_mode;

	return rv;
}

static sw_error_t
adpt_mp_port_max_frame_size_set(a_uint32_t dev_id, fal_port_t port_id,
	a_uint32_t max_frame)
{
	sw_error_t rv = SW_OK;
	a_uint32_t gmac_id = 0;
	union mac_max_frame_ctrl_u mac_max_frame_ctrl;
	union mac_configuration_u configuration;

	ADPT_DEV_ID_CHECK(dev_id);
	MP_PORT_ID_CHECK(port_id);

	memset(&configuration, 0, sizeof(configuration));
	memset(&mac_max_frame_ctrl, 0, sizeof(mac_max_frame_ctrl));
	gmac_id = MP_PORT_TO_GMAC_ID(port_id);

	rv = mp_mac_max_frame_ctrl_get(dev_id, gmac_id, &mac_max_frame_ctrl);
	SW_RTN_ON_ERROR(rv);
	rv = mp_mac_configuration_get(dev_id, gmac_id, &configuration);
	SW_RTN_ON_ERROR(rv);

	configuration.bf.jabber_disable = GMAC_JD_ENABLE;
	configuration.bf.watchdog_disable = GMAC_WD_DISABLE;
	configuration.bf.jumbo_frame_enable = GMAC_JUMBO_FRAME_ENABLE;
	configuration.bf.frame_burst_enable = GMAC_FRAME_BURST_ENABLE;
	rv = mp_mac_configuration_set(dev_id, gmac_id, &configuration);
	SW_RTN_ON_ERROR(rv);

	mac_max_frame_ctrl.bf.max_frame_ctrl_enable = GMAC_MAX_FRAME_CTRL_ENABLE;
	mac_max_frame_ctrl.bf.max_frame_ctrl = max_frame;
	rv = mp_mac_max_frame_ctrl_set(dev_id, gmac_id, &mac_max_frame_ctrl);

	return rv;
}

static sw_error_t
adpt_mp_port_max_frame_size_get(a_uint32_t dev_id, fal_port_t port_id,
	a_uint32_t *max_frame)
{
	sw_error_t rv = SW_OK;
	a_uint32_t gmac_id = 0;
	union mac_max_frame_ctrl_u mac_max_frame_ctrl;

	ADPT_DEV_ID_CHECK(dev_id);
	MP_PORT_ID_CHECK(port_id);
	ADPT_NULL_POINT_CHECK(max_frame);

	memset(&mac_max_frame_ctrl, 0, sizeof(mac_max_frame_ctrl));
	gmac_id = MP_PORT_TO_GMAC_ID(port_id);

	rv = mp_mac_max_frame_ctrl_get(dev_id, gmac_id, &mac_max_frame_ctrl);
	SW_RTN_ON_ERROR(rv);

	*max_frame = mac_max_frame_ctrl.bf.max_frame_ctrl;

	return rv;
}

static sw_error_t
adpt_mp_port_mac_eee_enable_set(a_uint32_t dev_id, fal_port_t port_id,
	a_bool_t enable)
{
	sw_error_t rv = 0;
	a_uint32_t gmac_id = 0;
	union mac_lpi_ctrl_status_u mac_lpi_ctrl_status;

	ADPT_DEV_ID_CHECK(dev_id);
	MP_PORT_ID_CHECK(port_id);

	memset(&mac_lpi_ctrl_status, 0, sizeof(mac_lpi_ctrl_status));
	gmac_id = MP_PORT_TO_GMAC_ID(port_id);

	rv = mp_mac_lpi_ctrl_status_get(dev_id, gmac_id, &mac_lpi_ctrl_status);
	SW_RTN_ON_ERROR(rv);
	mac_lpi_ctrl_status.bf.lpi_enable = enable;

	rv = mp_mac_lpi_ctrl_status_set(dev_id, gmac_id, &mac_lpi_ctrl_status);

	return rv;
}
static sw_error_t
adpt_mp_port_mac_eee_enable_get(a_uint32_t dev_id, fal_port_t port_id,
	a_bool_t *enable)
{
	sw_error_t rv = 0;
	a_uint32_t gmac_id = 0;
	union mac_lpi_ctrl_status_u mac_lpi_ctrl_status;

	ADPT_DEV_ID_CHECK(dev_id);
	MP_PORT_ID_CHECK(port_id);
	ADPT_NULL_POINT_CHECK(enable);

	memset(&mac_lpi_ctrl_status, 0, sizeof(mac_lpi_ctrl_status));
	gmac_id = MP_PORT_TO_GMAC_ID(port_id);

	rv = mp_mac_lpi_ctrl_status_get(dev_id, gmac_id, &mac_lpi_ctrl_status);
	SW_RTN_ON_ERROR(rv);

	*enable = mac_lpi_ctrl_status.bf.lpi_enable;

	return rv;

}

static sw_error_t
adpt_mp_port_interface_eee_cfg_set(a_uint32_t dev_id, fal_port_t port_id,
	fal_port_eee_cfg_t *port_eee_cfg)
{
	sw_error_t rv = 0;
	union mac_lpi_timer_ctrl_u mac_lpi_timer_ctrl;
	union mac_lpi_ctrl_status_u mac_lpi_ctrl_status;

	a_uint32_t phy_id = 0, gmac_id = 0;
	a_uint32_t adv;
	hsl_phy_ops_t *phy_drv;

	ADPT_DEV_ID_CHECK(dev_id);
	MP_PORT_ID_CHECK(port_id);

	memset(&mac_lpi_timer_ctrl, 0, sizeof(mac_lpi_timer_ctrl));
	memset(&mac_lpi_ctrl_status, 0, sizeof(mac_lpi_ctrl_status));
	gmac_id = MP_PORT_TO_GMAC_ID(port_id);

	if (port_eee_cfg->enable) {
		adv = port_eee_cfg->advertisement;
	} else {
		adv = 0;
	}

	SW_RTN_ON_NULL(phy_drv = hsl_phy_api_ops_get(dev_id, port_id));
	if (NULL == phy_drv->phy_eee_adv_set) {
		return SW_NOT_SUPPORTED;
	}

	rv = hsl_port_prop_get_phyid(dev_id, port_id, &phy_id);
	SW_RTN_ON_ERROR (rv);

	rv = phy_drv->phy_eee_adv_set(dev_id, phy_id, adv);
	SW_RTN_ON_ERROR (rv);

	rv = mp_mac_lpi_timer_ctrl_get(dev_id, gmac_id, &mac_lpi_timer_ctrl);
	SW_RTN_ON_ERROR (rv);
	mac_lpi_timer_ctrl.bf.lpi_tw_timer = port_eee_cfg->lpi_wakeup_timer;
	rv = mp_mac_lpi_timer_ctrl_set(dev_id, gmac_id, &mac_lpi_timer_ctrl);
	SW_RTN_ON_ERROR (rv);

	rv = mp_mac_lpi_ctrl_status_get(dev_id, gmac_id, &mac_lpi_ctrl_status);
	SW_RTN_ON_ERROR (rv);
	mac_lpi_ctrl_status.bf.lpi_tx_auto_enable = GMAC_LPI_AUTO_MODE;
	mac_lpi_ctrl_status.bf.link_status = GMAC_LPI_LINK_UP;
	mac_lpi_ctrl_status.bf.lpi_enable = port_eee_cfg->lpi_tx_enable;
	rv = mp_mac_lpi_ctrl_status_set(dev_id, gmac_id, &mac_lpi_ctrl_status);

	return rv;
}
static sw_error_t
adpt_mp_port_interface_eee_cfg_get(a_uint32_t dev_id, fal_port_t port_id,
	fal_port_eee_cfg_t *port_eee_cfg)
{
	sw_error_t rv = 0;
	union mac_lpi_timer_ctrl_u mac_lpi_timer_ctrl;
	union mac_lpi_ctrl_status_u mac_lpi_ctrl_status;
	a_uint32_t phy_id = 0, gmac_id = 0;
	a_uint32_t adv, lp_adv, cap, status;
	hsl_phy_ops_t *phy_drv;

	ADPT_DEV_ID_CHECK(dev_id);
	MP_PORT_ID_CHECK(port_id);
	ADPT_NULL_POINT_CHECK(port_eee_cfg);

	memset(&mac_lpi_timer_ctrl, 0, sizeof(mac_lpi_timer_ctrl));
	memset(&mac_lpi_ctrl_status, 0, sizeof(mac_lpi_ctrl_status));
	memset(port_eee_cfg, 0, sizeof(*port_eee_cfg));
	gmac_id = MP_PORT_TO_GMAC_ID(port_id);

	SW_RTN_ON_NULL (phy_drv =hsl_phy_api_ops_get (dev_id, port_id));
	if ((NULL == phy_drv->phy_eee_adv_get) || (NULL == phy_drv->phy_eee_partner_adv_get) ||
		(NULL == phy_drv->phy_eee_cap_get) || (NULL == phy_drv->phy_eee_status_get)) {
		return SW_NOT_SUPPORTED;
	}

	rv = hsl_port_prop_get_phyid(dev_id, port_id, &phy_id);
	SW_RTN_ON_ERROR (rv);

	rv = phy_drv->phy_eee_adv_get(dev_id, phy_id, &adv);
	SW_RTN_ON_ERROR (rv);
	port_eee_cfg->advertisement = adv;
	rv = phy_drv->phy_eee_partner_adv_get(dev_id, phy_id, &lp_adv);
	SW_RTN_ON_ERROR (rv);
	port_eee_cfg->link_partner_advertisement = lp_adv;
	rv = phy_drv->phy_eee_cap_get(dev_id, phy_id, &cap);
	SW_RTN_ON_ERROR (rv);
	port_eee_cfg->capability = cap;
	rv = phy_drv->phy_eee_status_get(dev_id, phy_id, &status);
	SW_RTN_ON_ERROR (rv);
	port_eee_cfg->eee_status = status;

	if (port_eee_cfg->advertisement) {
		port_eee_cfg->enable = A_TRUE;
	} else {
		port_eee_cfg->enable = A_FALSE;
	}
	rv = mp_mac_lpi_ctrl_status_get(dev_id, gmac_id, &mac_lpi_ctrl_status);
	SW_RTN_ON_ERROR (rv);
	port_eee_cfg->lpi_tx_enable = mac_lpi_ctrl_status.bf.lpi_enable;

	rv = mp_mac_lpi_timer_ctrl_get(dev_id, gmac_id, &mac_lpi_timer_ctrl);
	SW_RTN_ON_ERROR (rv);
	port_eee_cfg->lpi_wakeup_timer = mac_lpi_timer_ctrl.bf.lpi_tw_timer;

	return rv;
}

sw_error_t adpt_mp_portctrl_init(a_uint32_t dev_id)
{
	adpt_api_t *p_adpt_api = NULL;

	p_adpt_api = adpt_api_ptr_get(dev_id);

	if(p_adpt_api == NULL)
	{
		return SW_FAIL;
	}
	p_adpt_api->adpt_port_txmac_status_get = adpt_mp_port_txmac_status_get;
	p_adpt_api->adpt_port_txmac_status_set = adpt_mp_port_txmac_status_set;
	p_adpt_api->adpt_port_rxmac_status_get = adpt_mp_port_rxmac_status_get;
	p_adpt_api->adpt_port_rxmac_status_set = adpt_mp_port_rxmac_status_set;
	p_adpt_api->adpt_port_rxfc_status_get = adpt_mp_port_rxfc_status_get;
	p_adpt_api->adpt_port_rxfc_status_set = adpt_mp_port_rxfc_status_set;
	p_adpt_api->adpt_port_txfc_status_get = adpt_mp_port_txfc_status_get;
	p_adpt_api->adpt_port_txfc_status_set = adpt_mp_port_txfc_status_set;
	p_adpt_api->adpt_port_flowctrl_set = adpt_mp_port_flowctrl_set;
	p_adpt_api->adpt_port_flowctrl_get = adpt_mp_port_flowctrl_get;
	p_adpt_api->adpt_port_flowctrl_forcemode_set =
		adpt_mp_port_flowctrl_forcemode_set;
	p_adpt_api->adpt_port_flowctrl_forcemode_get =
		adpt_mp_port_flowctrl_forcemode_get;
	p_adpt_api->adpt_port_max_frame_size_set = adpt_mp_port_max_frame_size_set;
	p_adpt_api->adpt_port_max_frame_size_get = adpt_mp_port_max_frame_size_get;
	p_adpt_api->adpt_port_promisc_mode_set = adpt_mp_port_promisc_mode_set;
	p_adpt_api->adpt_port_promisc_mode_get = adpt_mp_port_promisc_mode_get;
	p_adpt_api->adpt_port_mac_speed_set = adpt_mp_port_mac_speed_set;
	p_adpt_api->adpt_port_mac_duplex_set = adpt_mp_port_mac_duplex_set;
	p_adpt_api->adpt_port_interface_3az_status_set = adpt_mp_port_mac_eee_enable_set;
	p_adpt_api->adpt_port_interface_3az_status_get = adpt_mp_port_mac_eee_enable_get;
	p_adpt_api->adpt_port_interface_eee_cfg_set = adpt_mp_port_interface_eee_cfg_set;
	p_adpt_api->adpt_port_interface_eee_cfg_get = adpt_mp_port_interface_eee_cfg_get;

	return SW_OK;
}
/**
 * @}
 */
