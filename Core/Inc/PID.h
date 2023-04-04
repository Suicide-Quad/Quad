#ifndef ASSERV_H
#define ASSERV_H

#include "main.h"
//const Math
const float PI = 3.14;

//Value for choose direction to rotate
int LEFT = (-1);
int RIGHT = 1;

float posX;
float posY;
float rotation;
float move(float distance, TIM_HandleTypeDef* htim1, TIM_HandleTypeDef* htim8, TIM_HandleTypeDef* htim2, TIM_HandleTypeDef* htim5); //move robot to the distance(m) and return the distance left in m
float rotate(float angle, int dir, TIM_HandleTypeDef* htim1, TIM_HandleTypeDef* htim8, TIM_HandleTypeDef* htim2, TIM_HandleTypeDef* htim5); //rotate robot in angle(rad) and return the angle left in rad

#endif
