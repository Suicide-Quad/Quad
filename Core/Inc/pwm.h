
#ifndef _PWM_H
#define _PWM_H
#include "main.h"

enum Motor
{
    LEFT,
    RIGHT
};

void initPWM(TIM_HandleTypeDef* htimLeft, TIM_HandleTypeDef* htimRight);

void setPWM(enum Motor motor, double correction);

#endif
