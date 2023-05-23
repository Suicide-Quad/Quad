#include "Message/send.h"
#include <string.h>
#include "main.h" 

UART_HandleTypeDef* huartESP = NULL;
UART_HandleTypeDef* huartUSB = NULL;

void initCommunication(UART_HandleTypeDef* uartESP, UART_HandleTypeDef* uartUSB)
{
    huartESP = uartESP;
    huartUSB = uartUSB;
}

uint8_t getTimeout(TypeRequest actualType)
{
    switch (actualType)
    {
        case DEBUG_INT:
            return 10;
        default: 
            return 20;
    }
}

void sendData(TypeRequest actualType, uint8_t* payload)
{
    uint8_t actualSize = getSizeType(actualType);
    uint8_t request[3 + actualSize];
    memset(&request, 0, 3 + actualSize);
    request[0] = START_REQUEST;
    request[1] = actualType;
    for(uint32_t i = 0; i < actualSize; i++)
    {
        request[2 + i] = payload[i];
    }
    uint8_t sum = computeCheckSum(payload, actualSize);
    request[sizeof(request) -1] = sum;
    if (huartESP != NULL)
        HAL_UART_Transmit(huartESP, request, 3 + actualSize, getTimeout(actualType));
    if (huartUSB != NULL)
        HAL_UART_Transmit(huartUSB, request, 3 + actualSize, getTimeout(actualType));
}
