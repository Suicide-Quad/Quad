#ifndef _DEBUG_H
#define _DEBUG_H
#include "main.h"
#define BUFF_SIZE 64
#define DEBUG_TIME_OUT 30

void initDebug(UART_HandleTypeDef* huartD, UART_HandleTypeDef* huartS);
void sendFloat(char* msg, float value);
void sendInt(char* msg, int value);

void sendFloatDebug(char* msg, float value, int multiply);

void sendIntDebug(char* msg, int value);

#endif 
