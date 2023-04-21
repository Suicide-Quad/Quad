#include "debug.h"

TIM_HandleTypeDef* huartDebug;

void initDebug(TIM_HandleTypeDef* huartD)
{
    huartDebug = huartD;
}

void sendIntDebug(char* msg, int value)
{
    uint8_t buffer[64];
    memset(buffer, '\0', sizeof(buffer));
    sprintf((char *)buffer, "%s  %d \r\n", msg, value);
    HAL_UART_Transmit(huartDebug, buffer, sizeof(buffer), DEBUG_TIME_OUT);
}

void sendFloatDebug(char* msg, float value, int multiply)
{
    sendIntDebug(msg, (int)(value * multiply));
}
