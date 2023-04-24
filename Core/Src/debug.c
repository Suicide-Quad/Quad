#include "debug.h"
#include <stdio.h> 
#include <string.h>
#include "utils.h"

UART_HandleTypeDef* huartDebug = NULL;
UART_HandleTypeDef* huartServer= NULL;

void initDebug(UART_HandleTypeDef* huartD, UART_HandleTypeDef* huartS)
{
    huartDebug = huartD;
    huartServer = huartS;
}

void sendIntDebug(char* msg, int value)
{
        uint8_t buffer[BUFF_SIZE];
        memset(buffer, '\0', sizeof(buffer));
        sprintf((char *)buffer, "%.6ld -- %s  %d \r\n",HAL_GetTick(), msg, value);
        if (huartDebug != NULL)
            HAL_UART_Transmit(huartDebug, buffer, sizeof(buffer), DEBUG_TIME_OUT);
}

void sendFloatDebug(char* msg, float value, int multiply)
{
    sendIntDebug(msg, (int)(value * multiply));
}

void sendFloat(char* msg, float value)
{
	uint8_t msg0 [256];
	sprintf((char*)msg0,"%s:%d",msg,(int)value);
	uint8_t sum = checksum((char*)msg0);
	uint8_t msg1 [1024];
	sprintf((char*)msg1,"%s;%d&",(char*)msg0,sum);
	int message_size = strlen((char*)msg1);
	HAL_UART_Transmit(huartServer,msg1, message_size, DEBUG_TIME_OUT);
    uint8_t recept[1];
    HAL_UART_Receive(huartServer, recept, 1, DEBUG_TIME_OUT);
}

void sendInt(char* msg, int value)
{
	uint8_t msg0 [256];
	sprintf((char*)msg0,"%s:%d",msg,value);
	uint8_t sum = checksum((char*)msg0);
	uint8_t msg1 [1024];
	sprintf((char*)msg1,"%s;%d&",(char*)msg0,sum);
	int message_size = strlen((char*)msg1);
	HAL_UART_Transmit(huartServer,msg1, message_size, DEBUG_TIME_OUT);
    uint8_t recept[1];
    HAL_UART_Receive(huartServer, recept, 1, DEBUG_TIME_OUT);
}
