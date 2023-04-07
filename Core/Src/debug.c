#include "debug.h"
#define TIME_OUT 100
uint8_t checksum(char* msg)
{
	uint8_t sum = 0;
	for (int i = 0; *(msg+i) != 0; i ++)
	{
		sum += *(msg+i);
	}
	return sum % 256;
}

void sendFloat(UART_HandleTypeDef* huart2, char* msg, float value)
{
	uint8_t msg0 [256];
	sprintf((char*)msg0,"%s:%f",msg,value);
	uint8_t sum = checksum((char*)msg0);
	uint8_t msg1 [1024];
	sprintf((char*)msg1,"%s;%d&",(char*)msg0,sum);
	int message_size = strlen((char*)msg1);
	HAL_UART_Transmit(huart2,msg1, message_size, 1000);
    uint8_t recept[1];
    HAL_UART_Receive(huart2, recept, 1, 1000);
}

void sendInt(UART_HandleTypeDef* huart2, char* msg, int value)
{
	uint8_t msg0 [256];
	sprintf((char*)msg0,"%s:%d",msg,value);
	uint8_t sum = checksum((char*)msg0);
	uint8_t msg1 [1024];
	sprintf((char*)msg1,"%s;%d&",(char*)msg0,sum);
	int message_size = strlen((char*)msg1);
	HAL_UART_Transmit(huart2,msg1, message_size, TIME_OUT);
    uint8_t recept[1];
    HAL_UART_Receive(huart2, recept, 1, TIME_OUT);
}
