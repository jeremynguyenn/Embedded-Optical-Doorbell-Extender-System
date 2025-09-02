#include "ltr_329.h"

uint8_t getBit(uint8_t binary, uint8_t pos) {
	return ((binary >> pos) & 1) == 1 ? 1 : 0;
}

uint8_t LTR_329_readRegister(I2C_HandleTypeDef *hi2c, uint8_t addr) {
	uint8_t writeBuffer[] = {addr};
	uint8_t readBuffer[1];

	HAL_StatusTypeDef txResponse = HAL_I2C_Master_Transmit(hi2c, LTR_329_I2C_ADDR, writeBuffer, 1, 100);

	if (txResponse != HAL_OK) {
		return 255;
	}

	HAL_StatusTypeDef rxResponse = HAL_I2C_Master_Receive(hi2c, LTR_329_I2C_ADDR, readBuffer, 1, 100);

	if (rxResponse == HAL_OK) {
		return readBuffer[0];
	}

	return 255;
}

uint8_t LTR_329_writeRegister(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t value) {
	uint8_t writeBuffer[] = {addr, value};

	HAL_StatusTypeDef txResponse = HAL_I2C_Master_Transmit(hi2c, LTR_329_I2C_ADDR, writeBuffer, 2, 100);

	if (txResponse != HAL_OK) {
		return 255;
	}

	return 0;
}

uint8_t LTR_329_init(I2C_HandleTypeDef *hi2c) {
	uint8_t retryCount = 0;

	while (retryCount++ < 500) {
		uint8_t controlValue = LTR_329_readControl(hi2c);

		if (!getBit(controlValue, 1)) {
			break;
		}

		HAL_Delay(1);
	}

	LTR_329_writeControl(hi2c, 0b00011001);
//	LTR_329_writeControl(hi2c, 0b00000001);
}

uint8_t LTR_329_readControl(I2C_HandleTypeDef *hi2c) {
	return LTR_329_readRegister(hi2c, LTR_329_REG_CONTR_ADDR);
}

uint8_t LTR_329_writeControl(I2C_HandleTypeDef *hi2c, uint8_t value) {
	return LTR_329_writeRegister(hi2c, LTR_329_REG_CONTR_ADDR, value);
}

uint8_t LTR_329_readMeasurementRate(I2C_HandleTypeDef *hi2c) {
	return LTR_329_readRegister(hi2c, LTR_329_REG_MEAS_RATE_ADDR);
}

uint8_t LTR_329_writeMeasurementRate(I2C_HandleTypeDef *hi2c, uint8_t value) {
	return LTR_329_writeRegister(hi2c, LTR_329_REG_MEAS_RATE_ADDR, value);
}

uint8_t LTR_329_readPartID(I2C_HandleTypeDef *hi2c) {
	return LTR_329_readRegister(hi2c, LTR_329_REG_PART_ID_ADDR);
}

uint8_t LTR_329_readManufacturerID(I2C_HandleTypeDef *hi2c) {
	return LTR_329_readRegister(hi2c, LTR_329_REG_MANUFACTURER_ID_ADDR);
}

uint16_t LTR_329_readChannel0Data(I2C_HandleTypeDef *hi2c) {
	uint16_t ch00Data = LTR_329_readRegister(hi2c, LTR_329_REG_DATA_CH0_0_ADDR);
	uint16_t ch01Data = LTR_329_readRegister(hi2c, LTR_329_REG_DATA_CH0_1_ADDR);

	return ch00Data + (ch01Data << 8);
}

uint16_t LTR_329_readChannel1Data(I2C_HandleTypeDef *hi2c) {
	uint16_t ch10Data = LTR_329_readRegister(hi2c, LTR_329_REG_DATA_CH1_0_ADDR);
	uint16_t ch11Data = LTR_329_readRegister(hi2c, LTR_329_REG_DATA_CH1_1_ADDR);

	return ch10Data + (ch11Data << 8);
}

/**
 * The order of the read, matters! The sensor will lock the registers until it reads the last address.
 * When the code reads 0x8B (LTR_329_REG_DATA_CH0_1_ADDR), the lock will be removed from the sensor!
 */
void LTR_329_readMeasurement(I2C_HandleTypeDef *hi2c, LTR_329_measurement *measurement) {
	measurement->channel1 = LTR_329_readChannel1Data(hi2c);
	measurement->channel0 = LTR_329_readChannel0Data(hi2c);
}

uint8_t LTR_329_readStatus(I2C_HandleTypeDef *hi2c) {
	return LTR_329_readRegister(hi2c, LTR_329_REG_STATUS_ADDR);
}
