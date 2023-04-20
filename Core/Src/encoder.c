#include "encoder.h"

TIM_HandleTypeDef* encoderLeft;
TIM_HandleTypeDef* encoderRight;

void initEncoder(TIM_HandleTypeDef* htimLeft, TIM_HandleTypeDef* htimRight)
{
    encoderLeft = htimLeft;
    encoderRight = htimRight;

    HAL_TIM_Encoder_Start(htimLeft, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(htimRight, TIM_CHANNEL_ALL);
}

int getEncoder(enum Encoder encoder)
{
    if (encoder == RIGHT)
        return encoderLeft->Instance->CNT;
    else if (encoder == LEFT)
        return encoderLeft->Instance->CNT;
}

