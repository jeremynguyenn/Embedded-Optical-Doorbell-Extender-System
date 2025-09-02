#include "hc12.h"

void HC12_sleep(UART_HandleTypeDef *uart) {
	HAL_GPIO_WritePin(AT_SET_GPIO_Port, AT_SET_Pin, 0);

	uint8_t uart_buffer_tx[] = AT_SLEEP_CMD;
	uint8_t uart_buffer_rx[16] = {0};

	HAL_Delay(200);

	HAL_UART_Transmit(uart, uart_buffer_tx, sizeof(uart_buffer_tx), 100);
	HAL_UART_Receive(uart, uart_buffer_rx, sizeof(uart_buffer_rx), 100);
	HAL_GPIO_WritePin(AT_SET_GPIO_Port, AT_SET_Pin, 1);
}

void HC12_wakeUp(UART_HandleTypeDef *uart) {
	HAL_GPIO_WritePin(AT_SET_GPIO_Port, AT_SET_Pin, 0);
	HAL_GPIO_WritePin(AT_SET_GPIO_Port, AT_SET_Pin, 1);
}

