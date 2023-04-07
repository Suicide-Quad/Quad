#include "main.h"
#include <string.h>
#include <stdio.h>
#pragma once
#define BUFF_SIZE 258
void sendInt(UART_HandleTypeDef* huart2, char* msg, int value);
void sendFloat(UART_HandleTypeDef* huart2, char* msg,float value);

