/*
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
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
#include "sw.h"
#include "ssdk_phy_i2c.h"
#include <linux/i2c.h>
#include "ssdk_init.h"
#include "ssdk_plat.h"

/******************************************************************************
*
* _qca_phy_i2c_mii_read - mii register i2c read
*
* mii register i2c read
*/
sw_error_t
qca_phy_i2c_mii_read(a_uint32_t dev_id, a_uint32_t phy_addr,
                          a_uint32_t reg_addr, a_uint16_t *reg_data)
{
	a_uint8_t ret;
	struct i2c_adapter *adapt;
	/*
		TX buffer to send:
		1st byte is reg addr
	*/
	a_uint8_t tx[1] = { reg_addr & 0xff };
	/*
		RX buffer to receive:
		1st byte is high 8bits of reg data
		2nd byte is low 8bits of reg data
	*/
	a_uint8_t rx[2] = { 0 };
	struct i2c_msg msg[] = {
		{ .addr = phy_addr, .flags = 0,
		  .buf = tx, .len = sizeof(tx) },
		{ .addr = phy_addr, .flags = I2C_M_RD,
		  .buf = rx, .len = sizeof(rx) } };

	adapt = i2c_get_adapter(0);
	if (!adapt) {
		return SW_FAIL;
	}

	ret = i2c_transfer(adapt, msg, ARRAY_SIZE(msg));
	*reg_data = (rx[0] << 8) | rx[1];

	i2c_put_adapter(adapt);

	if (ret != ARRAY_SIZE(msg)) {
		return SW_FAIL;
	}

	return SW_OK;
}

/******************************************************************************
*
* _qca_phy_i2c_mii_write - mii register i2c write
*
* mii register i2c write
*/
sw_error_t
qca_phy_i2c_mii_write(a_uint32_t dev_id, a_uint32_t phy_addr,
                           a_uint32_t reg_addr, a_uint16_t reg_data)
{
	a_uint8_t ret;
	struct i2c_adapter *adapt;
	/*
		TX buffer to send:
		1st byte is reg addr
		2nd byte is high 8bits of reg data
		3rd byte is low 8bits of reg data
	*/
	a_uint8_t tx[3] = { reg_addr & 0xff, (reg_data >> 8) & 0xff, reg_data & 0xff};
	struct i2c_msg msg[] = {
		{ .addr = phy_addr, .flags = 0,
			.buf = tx, .len = sizeof(tx) } };

	adapt = i2c_get_adapter(0);
	if (!adapt) {
		return SW_FAIL;
	}

	ret = i2c_transfer(adapt, msg, ARRAY_SIZE(msg));

	i2c_put_adapter(adapt);

	if (ret != ARRAY_SIZE(msg)) {
		return SW_FAIL;
	}

	return SW_OK;
}

/******************************************************************************
*
* _qca_phy_i2c_mmd_read - mmd register i2c read
*
* mmd register i2c read
*/
sw_error_t
qca_phy_i2c_mmd_read(a_uint32_t dev_id, a_uint32_t phy_addr, a_uint16_t mmd_num,
                            a_uint32_t reg_addr, a_uint16_t *reg_data)
{
	a_uint8_t ret;
	struct i2c_adapter *adapt;
	/*
		TX buffer to send:
		1st byte: Bit[6](1:MMD 0:MII) Bit[5](1:MMD address 0:MMD data) Bit[4:0](MMD num)
		2nd byte is high 8bits of reg addr
		3rd byte is low 8bits of reg addr
	*/
	a_uint8_t tx[3] = { ((QCA_PHY_I2C_IS_MMD << QCA_PHY_I2C_MMD_OR_MII_SHIFT) |
		(QCA_PHY_I2C_MMD_IS_ADDR << QCA_PHY_I2C_MMD_ADDR_OR_DATA_SHIFT) | mmd_num),
		(reg_addr >> 8) & 0xff, reg_addr & 0xff };
	/*
		RX buffer to receive:
		1st byte is high 8bits of reg data
		2nd byte is low 8bits of reg data
	*/
	a_uint8_t rx[2] = { 0 };
	struct i2c_msg msg[] = {
		{ .addr = phy_addr, .flags = 0,
		  .buf = tx, .len = sizeof(tx) },
		{ .addr = phy_addr, .flags = I2C_M_RD,
		  .buf = rx, .len = sizeof(rx) } };

	if((mmd_num != QCA_PHY_MMD1_NUM) && (mmd_num != QCA_PHY_MMD3_NUM) &&
		(mmd_num != QCA_PHY_MMD7_NUM)) {
		SSDK_ERROR("wrong MMD number:[%d]\n", mmd_num);
		return SW_FAIL;
	}

	adapt = i2c_get_adapter(0);
	if (!adapt) {
		return SW_FAIL;
	}

	ret = i2c_transfer(adapt, msg, ARRAY_SIZE(msg));
	*reg_data = (rx[0] << 8) | rx[1];

	i2c_put_adapter(adapt);

	if (ret != ARRAY_SIZE(msg)) {
		return SW_FAIL;
	}

	return SW_OK;
}

/******************************************************************************
*
* _qca_phy_i2c_mmd_write - mmd register i2c write
*
* mmd register i2c write
*/
sw_error_t
qca_phy_i2c_mmd_write(a_uint32_t dev_id, a_uint32_t phy_addr, a_uint16_t mmd_num,
                            a_uint32_t reg_addr, a_uint16_t reg_data)
{
	a_uint8_t ret;
	struct i2c_adapter *adapt;
	/*
		First TX buffer to send:
		1st byte: Bit[6](1:MMD 0:MII) Bit[5](1:MMD address 0:MMD data) Bit[4:0](MMD num)
		2nd byte is high 8bits of reg addr
		3rd byte is low 8bits of reg addr
	*/
	a_uint8_t tx[3] = { ((QCA_PHY_I2C_IS_MMD << QCA_PHY_I2C_MMD_OR_MII_SHIFT) |
		(QCA_PHY_I2C_MMD_IS_ADDR << QCA_PHY_I2C_MMD_ADDR_OR_DATA_SHIFT) | mmd_num),
		(reg_addr >> 8) & 0xff, reg_addr & 0xff };

	/*
		Second TX buffer to send:
		1st byte: Bit[6](1:MMD 0:MII) Bit[5](1:MMD address 0:MMD data) Bit[4:0](MMD num)
		2nd byte is high 8bits of reg data
		3rd byte is low 8bits of reg data
	*/
	a_uint8_t tx2[3] = { ((QCA_PHY_I2C_IS_MMD << QCA_PHY_I2C_MMD_OR_MII_SHIFT) |
		(QCA_PHY_I2C_MMD_IS_DATA << QCA_PHY_I2C_MMD_ADDR_OR_DATA_SHIFT) | mmd_num),
		(reg_data >> 8) & 0xff, reg_data & 0xff };

	struct i2c_msg msg[] = {
		{ .addr = phy_addr, .flags = 0,
		  .buf = tx, .len = sizeof(tx) },
		{ .addr = phy_addr, .flags = 0,
		  .buf = tx2, .len = sizeof(tx2) } };

	if((mmd_num != QCA_PHY_MMD1_NUM) && (mmd_num != QCA_PHY_MMD3_NUM) &&
		(mmd_num != QCA_PHY_MMD7_NUM)) {
		SSDK_ERROR("wrong MMD number:[%d]\n", mmd_num);
		return SW_FAIL;
	}

	adapt = i2c_get_adapter(0);
	if (!adapt) {
		return SW_FAIL;
	}

	ret = i2c_transfer(adapt, msg, ARRAY_SIZE(msg));

	i2c_put_adapter(adapt);

	if (ret != ARRAY_SIZE(msg)) {
		return SW_FAIL;
	}

	return SW_OK;
}

/******************************************************************************
*
* qca_phy_is_i2c_addr -  check if phy addr is i2c addr
*
* check if phy addr is i2c addr
*/
a_bool_t
qca_phy_is_i2c_addr(a_uint32_t phy_addr)
{
	if(((phy_addr & QCA_PHY_I2C_DEVADDR_MASK) ==
					QCA_PHY_I2C_PHYCORE_DEVADDR) ||
		((phy_addr & QCA_PHY_I2C_DEVADDR_MASK) ==
					QCA_PHY_I2C_SERDES_DEVADDR)) {
		return A_TRUE;
	} else {
		return A_FALSE;
	}
}

/******************************************************************************
*
* qca_phy_i2c_read -  PHY register i2c read
*
* PHY register i2c read
*/
sw_error_t
qca_phy_i2c_read(a_uint32_t dev_id, a_uint32_t phy_addr,
                           a_uint32_t reg_addr_c45, a_uint16_t *reg_data)
{
	a_uint32_t mmd_num = QCA_PHY_MII_ADDR_C45_MMD_NUM(reg_addr_c45);
	a_uint32_t reg_addr = QCA_PHY_MII_ADDR_C45_REG_ADDR(reg_addr_c45);

	if(qca_phy_is_i2c_addr(phy_addr) == A_FALSE) {
		return SW_BAD_PARAM;
	}

	if(QCA_PHY_MII_ADDR_C45_IS_MMD(reg_addr_c45)) {
		qca_phy_i2c_mmd_read(dev_id, phy_addr, mmd_num, reg_addr, reg_data);

	} else {
		qca_phy_i2c_mii_read(dev_id, phy_addr, reg_addr, reg_data);
	}

	return SW_OK;
}

/******************************************************************************
*
* qca_phy_i2c_write -  PHY register i2c write
*
* PHY register i2c write
*/
sw_error_t
qca_phy_i2c_write(a_uint32_t dev_id, a_uint32_t phy_addr,
                            a_uint32_t reg_addr_c45, a_uint16_t reg_data)
{
	a_uint32_t mmd_num = QCA_PHY_MII_ADDR_C45_MMD_NUM(reg_addr_c45);
	a_uint32_t reg_addr = QCA_PHY_MII_ADDR_C45_REG_ADDR(reg_addr_c45);

	if(qca_phy_is_i2c_addr(phy_addr) == A_FALSE) {
		return SW_BAD_PARAM;
	}

	if(QCA_PHY_MII_ADDR_C45_IS_MMD(reg_addr_c45)) {
		qca_phy_i2c_mmd_write(dev_id, phy_addr, mmd_num, reg_addr, reg_data);

	} else {
		qca_phy_i2c_mii_write(dev_id, phy_addr, reg_addr, reg_data);
	}

	return SW_OK;
}

