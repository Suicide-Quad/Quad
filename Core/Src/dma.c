#include "dma.h"
#include "communication.h" 

uint16_t indexDMASend = 0;
uint8_t DMASendBuff[BUFF_SIZE];

UART_HandleTypeDef* uartDMA;

void initDMA(UART_HandleTypeDef* uart)
{
    uartDMA = uart;
}

void getFromDMA(char buffer[], uint8_t size)
{
    /*
    uint8_t index;

    for(index = 0; index < size; index++)
    {
        buffer[index] = DMASendBuff[(indexDMASend + index) % BUFF_SIZE];
    } 
    indexDMASend = (indexDMASend + index) % BUFF_SIZE;
    */
    for(int i = 0; i < size; i++)
    {
        buffer[i] = DMASendBuff[i];
    }
}

void updateDMA()
{
    HAL_UART_Receive_IT(uartDMA, DMASendBuff, BUFF_SIZE);
}

void printDMA()
{
    for(int i = 0; i < 6 ; i++)
    {
        sendDebugInt(DMASendBuff[i],'z');
    }
} 
