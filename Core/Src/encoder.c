#include "encoder.h"
#include "math.h"

TIM_HandleTypeDef* encoderLeft;
TIM_HandleTypeDef* encoderRight;

void initEncoder(TIM_HandleTypeDef* htimLeft, TIM_HandleTypeDef* htimRight)
{
    encoderLeft = htimLeft;
    encoderRight = htimRight;

    HAL_TIM_Encoder_Start_IT(htimLeft, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start_IT(htimRight, TIM_CHANNEL_ALL);
}

int getEncoder(enum Encoder encoder)
{
    if (encoder == ENCODER_RIGHT)
        return __HAL_TIM_GET_COUNTER(encoderRight);
    return __HAL_TIM_GET_COUNTER(encoderLeft);
}

double getEncoderRad(enum Encoder encoder)
{
    if (encoder == ENCODER_LEFT)
        return ((double)getEncoder(encoder)) / ((double)encoderLeft->Init.Period) * 2.0F * M_PI;
    return ((double)getEncoder(encoder)) / ((double)encoderRight->Init.Period) * 2.0F * M_PI;
}

