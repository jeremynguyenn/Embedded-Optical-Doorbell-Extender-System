#ifndef INC_HC12_H_
#define INC_HC12_H_

#include "main.h"

#define AT_SLEEP_CMD	"AT+SLEEP\r\n"

void HC12_sleep(UART_HandleTypeDef *uart);
void HC12_wakeUp(UART_HandleTypeDef *uart);

#endif /* INC_HC12_H_ */
