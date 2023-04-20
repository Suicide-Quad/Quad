#ifndef _ENCODER_H
#define _ENCODER_H

enum Encoder
{
    Left,
    Right
}

void initEncoder(TIM_HandleTypeDef* htimLeft, TIM_HandleTypeDef* htimRight);

int getEncoder(enum Encoder encoder);


#endif

