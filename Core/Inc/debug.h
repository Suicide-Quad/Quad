#ifndef _DEBUG_H
#define _DEBUG_H
#include "main.h"
#include <string.h>
#include <stdio.h>
#define BUFF_SIZE 258
#define DEBUG_TIME_OUT 100

void initDebug(TIM_HandleTypeDef* huartD)

void sendFloatDebug(char* msg, float value, int multiply)

void sendIntDebug(char* msg, int value)
#endif 
