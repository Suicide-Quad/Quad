#include "Message/send.h"
#include "main.h" 

UART_HandleTypeDef* huartESP = NULL;
UART_HandleTypeDef* huartUSB = NULL;

void initCommunication(UART_HandleTypeDef* uartESP, UART_HandleTypeDef* uartUSB)
{
    huartESP = uartESP;
    huartUSB = uartUSB;
}

void sendData(TypeRequest actualType, uint8_t* payload)
{
    uint8_t actualSize = getSizeType(actualType);
    uint8_t request[3 + actualSize];
    request[0] = START_REQUEST;
    request[1] = actualType;
    for(uint32_t i = 0; i < actualSize; i++)
    {
        request[2 + i] = payload[i];
    }
    uint8_t sum = computeCheckSum(&payload[2], actualSize);
    request[sizeof(request) -1] = sum;
    if (huartESP != NULL)
        HAL_UART_Transmit_IT(huartESP, request, 3 + actualSize);
    if (huartUSB != NULL)
        HAL_UART_Transmit_IT(huartUSB, request, 3 + actualSize);
}
