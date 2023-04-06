#include "main.h"
#pragma once
//const Math

#include <debug.h>
float move(float distance, TIM_HandleTypeDef* htim1, TIM_HandleTypeDef* htim8, TIM_HandleTypeDef* htim2, TIM_HandleTypeDef* htim5); //move robot to the distance(m) and return the distance left in m
float rotate(float angle, TIM_HandleTypeDef* htim1, TIM_HandleTypeDef* htim8, TIM_HandleTypeDef* htim2, TIM_HandleTypeDef* htim5); //rotate robot in angle(rad) and return the angle left in rad

