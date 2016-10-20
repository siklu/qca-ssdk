/*
 * Copyright (c) 2016, The Linux Foundation. All rights reserved.
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all copies.
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */


/**
 * @defgroup
 * @{
 */
#include "sw.h"
#include "hppe_mib.h"
#include "hppe_mib_reg.h"
#include "adpt.h"


sw_error_t
adpt_hppe_mib_cpukeep_get(a_uint32_t dev_id, a_bool_t *enable)
{
	sw_error_t rv = SW_OK;
	a_uint32_t port_id = 0, status = 0;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(enable);

	rv = hppe_mac_mib_ctrl_mib_rd_clr_get(dev_id, port_id, &status);

	if (status == A_TRUE)
		*enable = A_FALSE;
	else
		*enable = A_TRUE;

	if( rv != SW_OK )
		return rv;

	return SW_OK;
}

sw_error_t
adpt_hppe_mib_cpukeep_set(a_uint32_t dev_id, a_bool_t  enable)
{
	a_uint32_t port_id = 0;

	ADPT_DEV_ID_CHECK(dev_id);

	for (port_id = 0; port_id < 6; port_id++) {

		hppe_mac_mib_ctrl_mib_rd_clr_set(dev_id, port_id, (a_uint32_t)(!enable));
	}

	return SW_OK;
}
sw_error_t
adpt_hppe_get_mib_info(a_uint32_t dev_id, fal_port_t port_id,
                     fal_mib_info_t * mib_info )
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(mib_info);
	memset(mib_info, 0, sizeof(fal_mib_info_t));

	port_id = port_id -1;
	hppe_rxbroad_get(dev_id, (a_uint32_t)port_id, (union rxbroad_u *)&mib_info->RxBroad);
	hppe_rxpause_get(dev_id, (a_uint32_t)port_id, (union rxpause_u *)&mib_info->RxPause);
	hppe_rxmulti_get(dev_id, (a_uint32_t)port_id, (union rxmulti_u *)&mib_info->RxMulti);
	hppe_rxfcserr_get(dev_id, (a_uint32_t)port_id, (union rxfcserr_u *)&mib_info->RxFcsErr);
	hppe_rxalignerr_get(dev_id, (a_uint32_t)port_id, (union rxalignerr_u *)&mib_info->RxAllignErr);
	hppe_rxrunt_get(dev_id, (a_uint32_t)port_id, (union rxrunt_u *)&mib_info->RxRunt);
	hppe_rxfrag_get(dev_id, (a_uint32_t)port_id, (union rxfrag_u *)&mib_info->RxFragment);
	hppe_rxjumbofcserr_get(dev_id, (a_uint32_t)port_id, (union rxjumbofcserr_u *)&mib_info->RxJumboFcsErr);
	hppe_rxjumboalignerr_get(dev_id, (a_uint32_t)port_id, (union rxjumboalignerr_u *)&mib_info->RxJumboAligenErr);
	hppe_rxpkt64_get(dev_id, (a_uint32_t)port_id, (union rxpkt64_u *)&mib_info->Rx64Byte);
	hppe_rxpkt65to127_get(dev_id, (a_uint32_t)port_id, (union rxpkt65to127_u *)&mib_info->Rx128Byte);
	hppe_rxpkt128to255_get(dev_id, (a_uint32_t)port_id, (union rxpkt128to255_u *)&mib_info->Rx256Byte);
	hppe_rxpkt256to511_get(dev_id, (a_uint32_t)port_id, (union rxpkt256to511_u *)&mib_info->Rx512Byte);
	hppe_rxpkt512to1023_get(dev_id, (a_uint32_t)port_id, (union rxpkt512to1023_u *)&mib_info->Rx1024Byte);
	hppe_rxpkt1024to1518_get(dev_id, (a_uint32_t)port_id, (union rxpkt1024to1518_u *)&mib_info->Rx1518Byte);
	hppe_rxpkt1519tox_get(dev_id, (a_uint32_t)port_id, (union rxpkt1519tox_u *)&mib_info->RxMaxByte);
	hppe_rxtoolong_get(dev_id, (a_uint32_t)port_id, (union rxtoolong_u *)&mib_info->RxTooLong);
	hppe_rxgoodbyte_l_get(dev_id, (a_uint32_t)port_id, (union rxgoodbyte_l_u *)&mib_info->RxGoodByte_lo);
	hppe_rxgoodbyte_h_get(dev_id, (a_uint32_t)port_id, (union rxgoodbyte_h_u *)&mib_info->RxGoodByte_hi);
	hppe_rxbadbyte_l_get(dev_id, (a_uint32_t)port_id, (union rxbadbyte_l_u *)&mib_info->RxBadByte_lo);
	hppe_rxbadbyte_h_get(dev_id, (a_uint32_t)port_id, (union rxbadbyte_h_u *)&mib_info->RxBadByte_hi);
	hppe_rxuni_get(dev_id, (a_uint32_t)port_id, (union rxuni_u *)&mib_info->RxUniCast);
	hppe_txbroad_get(dev_id, (a_uint32_t)port_id, (union txbroad_u *)&mib_info->TxBroad);
	hppe_txpause_get(dev_id, (a_uint32_t)port_id, (union txpause_u *)&mib_info->TxPause);
	hppe_txmulti_get(dev_id, (a_uint32_t)port_id, (union txmulti_u *)&mib_info->TxMulti);
	hppe_txunderrun_get(dev_id, (a_uint32_t)port_id, (union txunderrun_u *)&mib_info->TxUnderRun);
	hppe_txpkt64_get(dev_id, (a_uint32_t)port_id, (union txpkt64_u *)&mib_info->Tx64Byte);
	hppe_txpkt65to127_get(dev_id, (a_uint32_t)port_id, (union txpkt65to127_u *)&mib_info->Tx128Byte);
	hppe_txpkt128to255_get(dev_id, (a_uint32_t)port_id, (union txpkt128to255_u *)&mib_info->Tx256Byte);
	hppe_txpkt256to511_get(dev_id, (a_uint32_t)port_id, (union txpkt256to511_u *)&mib_info->Tx512Byte);
	hppe_txpkt512to1023_get(dev_id, (a_uint32_t)port_id, (union txpkt512to1023_u *)&mib_info->Tx1024Byte);
	hppe_txpkt1024to1518_get(dev_id, (a_uint32_t)port_id, (union txpkt1024to1518_u *)&mib_info->Tx1518Byte);
	hppe_txpkt1519tox_get(dev_id, (a_uint32_t)port_id, (union txpkt1519tox_u *)&mib_info->TxMaxByte);
	hppe_txbyte_l_get(dev_id, (a_uint32_t)port_id, (union txbyte_l_u *)&mib_info->TxByte_lo);
	hppe_txbyte_h_get(dev_id, (a_uint32_t)port_id, (union txbyte_h_u *)&mib_info->TxByte_hi);
	hppe_txcollisions_get(dev_id, (a_uint32_t)port_id, (union txcollisions_u *)&mib_info->TxCollision);
	hppe_txabortcol_get(dev_id, (a_uint32_t)port_id, (union txabortcol_u *)&mib_info->TxAbortCol);
	hppe_txmulticol_get(dev_id, (a_uint32_t)port_id, (union txmulticol_u *)&mib_info->TxMultiCol);
	hppe_txsinglecol_get(dev_id, (a_uint32_t)port_id, (union txsinglecol_u *)&mib_info->TxSingalCol);
	hppe_txexcessivedefer_get(dev_id, (a_uint32_t)port_id, (union txexcessivedefer_u *)&mib_info->TxExcDefer);
	hppe_txdefer_get(dev_id, (a_uint32_t)port_id, (union txdefer_u *)&mib_info->TxDefer);
	hppe_txlatecol_get(dev_id, (a_uint32_t)port_id, (union txlatecol_u *)&mib_info->TxLateCol);
	hppe_txuni_get(dev_id, (a_uint32_t)port_id, (union txuni_u *)&mib_info->TxUniCast);

}

sw_error_t
adpt_hppe_get_tx_mib_info(a_uint32_t dev_id, fal_port_t port_id,
                     fal_mib_info_t * mib_info )
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(mib_info);
	memset(mib_info, 0, sizeof(fal_mib_info_t));

	port_id = port_id -1;
	hppe_txbroad_get(dev_id, (a_uint32_t)port_id, (union txbroad_u *)&mib_info->TxBroad);
	hppe_txpause_get(dev_id, (a_uint32_t)port_id, (union txpause_u *)&mib_info->TxPause);
	hppe_txmulti_get(dev_id, (a_uint32_t)port_id, (union txmulti_u *)&mib_info->TxMulti);
	hppe_txunderrun_get(dev_id, (a_uint32_t)port_id, (union txunderrun_u *)&mib_info->TxUnderRun);
	hppe_txpkt64_get(dev_id, (a_uint32_t)port_id, (union txpkt64_u *)&mib_info->Tx64Byte);
	hppe_txpkt65to127_get(dev_id, (a_uint32_t)port_id, (union txpkt65to127_u *)&mib_info->Tx128Byte);
	hppe_txpkt128to255_get(dev_id, (a_uint32_t)port_id, (union txpkt128to255_u *)&mib_info->Tx256Byte);
	hppe_txpkt256to511_get(dev_id, (a_uint32_t)port_id, (union txpkt256to511_u *)&mib_info->Tx512Byte);
	hppe_txpkt512to1023_get(dev_id, (a_uint32_t)port_id, (union txpkt512to1023_u *)&mib_info->Tx1024Byte);
	hppe_txpkt1024to1518_get(dev_id, (a_uint32_t)port_id, (union txpkt1024to1518_u *)&mib_info->Tx1518Byte);
	hppe_txpkt1519tox_get(dev_id, (a_uint32_t)port_id, (union txpkt1519tox_u *)&mib_info->TxMaxByte);
	hppe_txbyte_l_get(dev_id, (a_uint32_t)port_id, (union txbyte_l_u *)&mib_info->TxByte_lo);
	hppe_txbyte_h_get(dev_id, (a_uint32_t)port_id, (union txbyte_h_u *)&mib_info->TxByte_hi);
	hppe_txcollisions_get(dev_id, (a_uint32_t)port_id, (union txcollisions_u *)&mib_info->TxCollision);
	hppe_txabortcol_get(dev_id, (a_uint32_t)port_id, (union txabortcol_u *)&mib_info->TxAbortCol);
	hppe_txmulticol_get(dev_id, (a_uint32_t)port_id, (union txmulticol_u *)&mib_info->TxMultiCol);
	hppe_txsinglecol_get(dev_id, (a_uint32_t)port_id, (union txsinglecol_u *)&mib_info->TxSingalCol);
	hppe_txexcessivedefer_get(dev_id, (a_uint32_t)port_id, (union txexcessivedefer_u *)&mib_info->TxExcDefer);
	hppe_txdefer_get(dev_id, (a_uint32_t)port_id, (union txdefer_u *)&mib_info->TxDefer);
	hppe_txlatecol_get(dev_id, (a_uint32_t)port_id, (union txlatecol_u *)&mib_info->TxLateCol);
	hppe_txuni_get(dev_id, (a_uint32_t)port_id, (union txuni_u *)&mib_info->TxUniCast);

}

sw_error_t
adpt_hppe_mib_status_set(a_uint32_t dev_id, a_bool_t enable)
{
	a_uint32_t port_id = 0;

	ADPT_DEV_ID_CHECK(dev_id);

	for (port_id = 0; port_id < 6; port_id++) {

		hppe_mac_mib_ctrl_mib_en_set(dev_id, port_id, (a_uint32_t)enable);
	}

	return SW_OK;
}
sw_error_t
adpt_hppe_mib_port_flush_counters(a_uint32_t dev_id, fal_port_t port_id)
{

	ADPT_DEV_ID_CHECK(dev_id);

	port_id = port_id -1;
	hppe_mac_mib_ctrl_mib_reset_set(dev_id, port_id, A_TRUE);
	hppe_mac_mib_ctrl_mib_reset_set(dev_id, port_id, A_FALSE);

	return SW_OK;
}
sw_error_t
adpt_hppe_mib_status_get(a_uint32_t dev_id, a_bool_t * enable)
{
	sw_error_t rv = SW_OK;
	a_uint32_t port_id = 0, status = 0;

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(enable);

	rv = hppe_mac_mib_ctrl_mib_en_get(dev_id, port_id, &status);
	*enable = status;

	if( rv != SW_OK )
		return rv;

	return SW_OK;
}

sw_error_t
adpt_hppe_get_rx_mib_info(a_uint32_t dev_id, fal_port_t port_id,
                     fal_mib_info_t * mib_info )
{

	ADPT_DEV_ID_CHECK(dev_id);
	ADPT_NULL_POINT_CHECK(mib_info);
	memset(mib_info, 0, sizeof(fal_mib_info_t));

	port_id = port_id -1;
	hppe_rxbroad_get(dev_id, (a_uint32_t)port_id, (union rxbroad_u *)&mib_info->RxBroad);
	hppe_rxpause_get(dev_id, (a_uint32_t)port_id, (union rxpause_u *)&mib_info->RxPause);
	hppe_rxmulti_get(dev_id, (a_uint32_t)port_id, (union rxmulti_u *)&mib_info->RxMulti);
	hppe_rxfcserr_get(dev_id, (a_uint32_t)port_id, (union rxfcserr_u *)&mib_info->RxFcsErr);
	hppe_rxalignerr_get(dev_id, (a_uint32_t)port_id, (union rxalignerr_u *)&mib_info->RxAllignErr);
	hppe_rxrunt_get(dev_id, (a_uint32_t)port_id, (union rxrunt_u *)&mib_info->RxRunt);
	hppe_rxfrag_get(dev_id, (a_uint32_t)port_id, (union rxfrag_u *)&mib_info->RxFragment);
	hppe_rxjumbofcserr_get(dev_id, (a_uint32_t)port_id, (union rxjumbofcserr_u *)&mib_info->RxJumboFcsErr);
	hppe_rxjumboalignerr_get(dev_id, (a_uint32_t)port_id, (union rxjumboalignerr_u *)&mib_info->RxJumboAligenErr);
	hppe_rxpkt64_get(dev_id, (a_uint32_t)port_id, (union rxpkt64_u *)&mib_info->Rx64Byte);
	hppe_rxpkt65to127_get(dev_id, (a_uint32_t)port_id, (union rxpkt65to127_u *)&mib_info->Rx128Byte);
	hppe_rxpkt128to255_get(dev_id, (a_uint32_t)port_id, (union rxpkt128to255_u *)&mib_info->Rx256Byte);
	hppe_rxpkt256to511_get(dev_id, (a_uint32_t)port_id, (union rxpkt256to511_u *)&mib_info->Rx512Byte);
	hppe_rxpkt512to1023_get(dev_id, (a_uint32_t)port_id, (union rxpkt512to1023_u *)&mib_info->Rx1024Byte);
	hppe_rxpkt1024to1518_get(dev_id, (a_uint32_t)port_id, (union rxpkt1024to1518_u *)&mib_info->Rx1518Byte);
	hppe_rxpkt1519tox_get(dev_id, (a_uint32_t)port_id, (union rxpkt1519tox_u *)&mib_info->RxMaxByte);
	hppe_rxtoolong_get(dev_id, (a_uint32_t)port_id, (union rxtoolong_u *)&mib_info->RxTooLong);
	hppe_rxgoodbyte_l_get(dev_id, (a_uint32_t)port_id, (union rxgoodbyte_l_u *)&mib_info->RxGoodByte_lo);
	hppe_rxgoodbyte_h_get(dev_id, (a_uint32_t)port_id, (union rxgoodbyte_h_u *)&mib_info->RxGoodByte_hi);
	hppe_rxbadbyte_l_get(dev_id, (a_uint32_t)port_id, (union rxbadbyte_l_u *)&mib_info->RxBadByte_lo);
	hppe_rxbadbyte_h_get(dev_id, (a_uint32_t)port_id, (union rxbadbyte_h_u *)&mib_info->RxBadByte_hi);
	hppe_rxuni_get(dev_id, (a_uint32_t)port_id, (union rxuni_u *)&mib_info->RxUniCast);

}

void adpt_hppe_mib_func_bitmap_init(a_uint32_t dev_id)
{
	adpt_api_t *p_adpt_api = NULL;

	p_adpt_api = adpt_api_ptr_get(dev_id);

	if(p_adpt_api == NULL)
		return;

	p_adpt_api->adpt_mib_func_bitmap = ((1<<FUNC_GET_MIB_INFO)|
						(1<<FUNC_GET_RX_MIB_INFO)|
						(1<<FUNC_GET_TX_MIB_INFO)|
						(1<<FUNC_MIB_STATUS_SET)|
						(1<<FUNC_MIB_STATUS_GET)|
						(1<<FUNC_MIB_PORT_FLUSH_COUNTERS)|
						(1<<FUNC_MIB_CPUKEEP_SET)|
						(1<<FUNC_MIB_CPUKEEP_GET)
						);
	return;
}

static void adpt_hppe_mib_func_unregister(a_uint32_t dev_id, adpt_api_t *p_adpt_api)
{
	if(p_adpt_api == NULL)
		return;

	p_adpt_api->adpt_get_mib_info = NULL;
	p_adpt_api->adpt_get_rx_mib_info = NULL;
	p_adpt_api->adpt_get_tx_mib_info = NULL;
	p_adpt_api->adpt_mib_status_set = NULL;
	p_adpt_api->adpt_mib_status_get = NULL;
	p_adpt_api->adpt_mib_port_flush_counters = NULL;
	p_adpt_api->adpt_mib_cpukeep_set = NULL;
	p_adpt_api->adpt_mib_cpukeep_get = NULL;

	return;
}

sw_error_t adpt_hppe_mib_init(a_uint32_t dev_id)
{
	adpt_api_t *p_adpt_api = NULL;

	p_adpt_api = adpt_api_ptr_get(dev_id);

	if(p_adpt_api == NULL)
		return SW_FAIL;

	adpt_hppe_mib_func_unregister(dev_id, p_adpt_api);

	if(p_adpt_api->adpt_mib_func_bitmap & (1<<FUNC_GET_MIB_INFO))
	{
		p_adpt_api->adpt_get_mib_info = adpt_hppe_get_mib_info;
	}
	if(p_adpt_api->adpt_mib_func_bitmap & (1<<FUNC_GET_RX_MIB_INFO))
	{
		p_adpt_api->adpt_get_rx_mib_info = adpt_hppe_get_rx_mib_info;
	}
	if(p_adpt_api->adpt_mib_func_bitmap & (1<<FUNC_GET_TX_MIB_INFO))
	{
		p_adpt_api->adpt_get_tx_mib_info = adpt_hppe_get_tx_mib_info;
	}
	if(p_adpt_api->adpt_mib_func_bitmap & (1<<FUNC_MIB_STATUS_SET))
	{
		p_adpt_api->adpt_mib_status_set = adpt_hppe_mib_status_set;
	}
	if(p_adpt_api->adpt_mib_func_bitmap & (1<<FUNC_MIB_STATUS_GET))
	{
		p_adpt_api->adpt_mib_status_get = adpt_hppe_mib_status_get;
	}
	if(p_adpt_api->adpt_mib_func_bitmap & (1<<FUNC_MIB_PORT_FLUSH_COUNTERS))
	{
		p_adpt_api->adpt_mib_port_flush_counters = adpt_hppe_mib_port_flush_counters;
	}
	if(p_adpt_api->adpt_mib_func_bitmap & (1<<FUNC_MIB_CPUKEEP_SET))
	{
		p_adpt_api->adpt_mib_cpukeep_set = adpt_hppe_mib_cpukeep_set;
	}
	if(p_adpt_api->adpt_mib_func_bitmap & (1<<FUNC_MIB_CPUKEEP_GET))
	{
		p_adpt_api->adpt_mib_cpukeep_get = adpt_hppe_mib_cpukeep_get;
	}

	return SW_OK;
}

/**
 * @}
 */
