#include "main.h"
#pragma once
//const Math

float move(float distance, TIM_HandleTypeDef* htim1, TIM_HandleTypeDef* htim8, TIM_HandleTypeDef* htim2, TIM_HandleTypeDef* htim5, UART_HandleTypeDef* huart2); //move robot to the distance(m) and return the distance left in m
float rotate(float angle, TIM_HandleTypeDef* htim1, TIM_HandleTypeDef* htim8, TIM_HandleTypeDef* htim2, TIM_HandleTypeDef* htim5, UART_HandleTypeDef* huart2); //rotate robot in angle(rad) and return the angle left in rad

