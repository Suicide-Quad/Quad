#ifndef _ENCODER_H
#define _ENCODER_H
#define HIGH_VALUE 2048 

#include "main.h"
enum Encoder
{
    ENCODER_LEFT,
    ENCODER_RIGHT
};

void initEncoder(TIM_HandleTypeDef* htimLeft, TIM_HandleTypeDef* htimRight);

int getEncoder(enum Encoder encoder);

double getEncoderRad(enum Encoder encoder);

#endif


