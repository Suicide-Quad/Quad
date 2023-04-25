#ifndef _DMA_H
#define _DMA_H
#include "main.h"
#define BUFF_SIZE 128

void initDMA(UART_HandleTypeDef uart);

void getFromDMA(char buffer[], uint8_t size);

#endif
