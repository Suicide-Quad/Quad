#include "pwm.h"
#include "utils.h"
#define MAX_LIMIT 100.0F
// The pwm
TIM_HandleTypeDef* pwmMotorLeft;
TIM_HandleTypeDef* pwmMotorRight;

void initPWM(TIM_HandleTypeDef* htimLeft, TIM_HandleTypeDef* htimRight)
{
    pwmMotorLeft = htimLeft;
    pwmMotorRight = htimRight;

    HAL_TIM_PWM_Start(htimLeft, TIM_CHANNEL_1);
    HAL_TIMEx_PWMN_Start(htimLeft, TIM_CHANNEL_1);

    HAL_TIM_PWM_Start(htimRight, TIM_CHANNEL_1);
    HAL_TIMEx_PWMN_Start(htimRight, TIM_CHANNEL_1);
    // Set the disable pin to HIGH
    HAL_GPIO_WritePin(MOTOR1_DISABLE_GPIO_Port, MOTOR1_DISABLE_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR4_DISABLE_GPIO_Port, MOTOR4_DISABLE_Pin, GPIO_PIN_SET);
} 


void setPWM(enum Motor motor, double command)
{
    TIM_HandleTypeDef* htimPWM;
    if (motor ==  LEFT)
    {
        htimPWM = pwmMotorLeft;
    }
    else 
    {
        htimPWM = pwmMotorRight;
    }
    uint32_t value = (CLAMP(-MAX_LIMIT, command, MAX_LIMIT) / 2 + 50.0F) / 100.0F * htimPWM->Init.Period;
    __HAL_TIM_SET_COMPARE(htimPWM, TIM_CHANNEL_1, value); 
}

