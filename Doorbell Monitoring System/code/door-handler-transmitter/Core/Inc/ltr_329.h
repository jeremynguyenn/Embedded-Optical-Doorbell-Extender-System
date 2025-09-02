#ifndef SRC_LTR_329_H_
#define SRC_LTR_329_H_

#include "stm32l0xx_hal.h"

#define LTR_329_I2C_ADDR						0x52

#define LTR_329_REG_CONTR_ADDR					0x80
#define LTR_329_REG_MEAS_RATE_ADDR				0x85
#define LTR_329_REG_PART_ID_ADDR				0x86
#define LTR_329_REG_MANUFACTURER_ID_ADDR		0x87
#define LTR_329_REG_DATA_CH1_0_ADDR				0x88
#define LTR_329_REG_DATA_CH1_1_ADDR				0x89
#define LTR_329_REG_DATA_CH0_0_ADDR				0x8A
#define LTR_329_REG_DATA_CH0_1_ADDR				0x8B
#define LTR_329_REG_STATUS_ADDR					0x8C

typedef struct LTR_329_measurement {
	uint16_t channel0;
	uint16_t channel1;
} LTR_329_measurement;

uint8_t LTR_329_readRegister(I2C_HandleTypeDef *hi2c, uint8_t addr);
uint8_t LTR_329_writeRegister(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t value);

uint8_t LTR_329_init(I2C_HandleTypeDef *hi2c);

uint8_t LTR_329_readControl(I2C_HandleTypeDef *hi2c);
uint8_t LTR_329_writeControl(I2C_HandleTypeDef *hi2c, uint8_t value);
uint8_t LTR_329_readMeasurementRate(I2C_HandleTypeDef *hi2c);
uint8_t LTR_329_writeMeasurementRate(I2C_HandleTypeDef *hi2c, uint8_t value);
uint8_t LTR_329_readPartID(I2C_HandleTypeDef *hi2c);
uint8_t LTR_329_readManufacturerID(I2C_HandleTypeDef *hi2c);
uint16_t LTR_329_readChannel0Data(I2C_HandleTypeDef *hi2c);
uint16_t LTR_329_readChannel1Data(I2C_HandleTypeDef *hi2c);
void LTR_329_readMeasurement(I2C_HandleTypeDef *hi2c, LTR_329_measurement *measurement);
uint8_t LTR_329_readStatus(I2C_HandleTypeDef *hi2c);

#endif /* SRC_LTR_329_H_ */
