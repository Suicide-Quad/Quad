#include "pwm.h"
#include "utils.h"

// The pwm
TIM_HandleTypeDef* pwmMotorLeft;
TIM_HandleTypeDef* pwmMotorRight;

void initPWM(TIM_HandleTypeDef* htimLeft, TIM_HandleTypeDef* htim2)
{
    pwmMotorLeft = htimLeft;
    pwmMotorRight = htim2;

    HAL_TIM_PWM_Start(htimLeft, TIM_CHANNEL_1);
    HAL_TIMEx_PWMN_Start(htimLeft, TIM_CHANNEL_1);

    HAL_TIM_PWM_Start(htimRight, TIM_CHANNEL_1);
    HAL_TIMEx_PWMN_Start(htimRight, TIM_CHANNEL_1);
    // Set the disable pin to HIGH
    HAL_GPIO_WritePin(MOTOR1_DISABLE_GPIO_Port, MOTOR1_DISABLE_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR4_DISABLE_GPIO_Port, MOTOR4_DISABLE_Pin, GPIO_PIN_SET);
} 


void setPWM(enum Motor motor, double correction)
{
    TIM_HandleTypeDef* htim;
    if (motor ==  LEFT)
    {
        htim = pwmMotorLeft;
    }
    else if (motor == RIGHT)
    {
        htim = pwmMotorRight;
    }
    // TODO : Period = 2048
    float value = (CLAMP(-100.0F, DC, 100.0F) / 2 + 50.0F) / 100.0F * htim->Init.Period;
    __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, value); 
}

