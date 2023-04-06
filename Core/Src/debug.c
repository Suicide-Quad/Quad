#include "debug.h"
void debug(UART_HandleTypeDef* huart2, char* msg, int value)
{
	uint8_t msgt [BUFF_SIZE];
	sprintf((char*)msgt,"%s=%d;",msg,value);
	int sizet = strlen((char*)msgt);
	HAL_UART_Transmit(huart2,msgt, sizet, 1000);
    uint8_t recept[1];
    HAL_UART_Receive(huart2, recept, 1, 1000);
}
