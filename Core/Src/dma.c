#include "dma.h"

uint16_t indexDMA = 0;
uint8_t DMABuff[BUFF_SIZE];
UART_HandleTypeDef uartDMA;

void initDMA(UART_HandleTypeDef uart)
{
    uartDMA = uart;
    HAL_UARTEx_ReceiveToIdle_DMA(&uart, DMABuff, BUFF_SIZE);
}

void getFromDMA(char buffer[], uint8_t size)
{
    uint8_t index;
    for(index = 0; index < size; index++)
    {
        buffer[index] = DMABuff[(indexDMA + index) % BUFF_SIZE];
    } 
    indexDMA = (indexDMA + index) % BUFF_SIZE;
}
