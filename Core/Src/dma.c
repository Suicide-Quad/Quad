#include "dma.h"

uint16_t indexDMASend = 0;
uint8_t DMASendBuff[BUFF_SIZE];

UART_HandleTypeDef uartDMA;
void initDMA(UART_HandleTypeDef uart)
{
    uartDMA = uart;
    HAL_UARTEx_ReceiveToIdle_DMA(&uart, DMASendBuff , BUFF_SIZE);
}

void getFromDMA(char buffer[], uint8_t size)
{
    uint8_t index;
    for(index = 0; index < size; index++)
    {
        buffer[index] = DMASendBuff[(indexDMASend + index) % BUFF_SIZE];
    } 
    indexDMASend = (indexDMASend + index) % BUFF_SIZE;
}

