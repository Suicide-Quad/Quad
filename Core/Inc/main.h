/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define JACK_Pin GPIO_PIN_2
#define JACK_GPIO_Port GPIOE
#define CONFIG_1_Pin GPIO_PIN_3
#define CONFIG_1_GPIO_Port GPIOE
#define CONFIG_2_Pin GPIO_PIN_4
#define CONFIG_2_GPIO_Port GPIOE
#define CONFIG_3_Pin GPIO_PIN_5
#define CONFIG_3_GPIO_Port GPIOE
#define CONFIG_4_Pin GPIO_PIN_6
#define CONFIG_4_GPIO_Port GPIOE
#define USER_Btn_Pin GPIO_PIN_13
#define USER_Btn_GPIO_Port GPIOC
#define LED_GREEN_2_Pin GPIO_PIN_0
#define LED_GREEN_2_GPIO_Port GPIOF
#define LED_RED_2_Pin GPIO_PIN_1
#define LED_RED_2_GPIO_Port GPIOF
#define LED_ORANGE_2_Pin GPIO_PIN_2
#define LED_ORANGE_2_GPIO_Port GPIOF
#define LED_BLUE_2_Pin GPIO_PIN_3
#define LED_BLUE_2_GPIO_Port GPIOF
#define LED_WHITE_2_Pin GPIO_PIN_4
#define LED_WHITE_2_GPIO_Port GPIOF
#define LED_WHITE_3_Pin GPIO_PIN_5
#define LED_WHITE_3_GPIO_Port GPIOF
#define LED_GREEN_1_Pin GPIO_PIN_6
#define LED_GREEN_1_GPIO_Port GPIOF
#define LED_RED_1_Pin GPIO_PIN_7
#define LED_RED_1_GPIO_Port GPIOF
#define LED_ORANGE_1_Pin GPIO_PIN_8
#define LED_ORANGE_1_GPIO_Port GPIOF
#define LED_BLUE_1_Pin GPIO_PIN_9
#define LED_BLUE_1_GPIO_Port GPIOF
#define LED_WHITE_1_Pin GPIO_PIN_10
#define LED_WHITE_1_GPIO_Port GPIOF
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOH
#define SPI_INT1_Pin GPIO_PIN_0
#define SPI_INT1_GPIO_Port GPIOC
#define SPI_INT2_Pin GPIO_PIN_1
#define SPI_INT2_GPIO_Port GPIOC
#define SPI_INT3_Pin GPIO_PIN_2
#define SPI_INT3_GPIO_Port GPIOC
#define SPI_INT4_Pin GPIO_PIN_3
#define SPI_INT4_GPIO_Port GPIOC
#define MOTOR4_PWM_L_Pin GPIO_PIN_7
#define MOTOR4_PWM_L_GPIO_Port GPIOA
#define ANALOG_3_Pin GPIO_PIN_4
#define ANALOG_3_GPIO_Port GPIOC
#define ANALOG_4_Pin GPIO_PIN_5
#define ANALOG_4_GPIO_Port GPIOC
#define LD1_Pin GPIO_PIN_0
#define LD1_GPIO_Port GPIOB
#define SWITH_1_Pin GPIO_PIN_2
#define SWITH_1_GPIO_Port GPIOB
#define SWITH_2_Pin GPIO_PIN_11
#define SWITH_2_GPIO_Port GPIOF
#define SWITH_3_Pin GPIO_PIN_12
#define SWITH_3_GPIO_Port GPIOF
#define MOTOR1_PWM_L_Pin GPIO_PIN_8
#define MOTOR1_PWM_L_GPIO_Port GPIOE
#define MOTOR1_PWM_H_Pin GPIO_PIN_9
#define MOTOR1_PWM_H_GPIO_Port GPIOE
#define SPI_SS1_Pin GPIO_PIN_14
#define SPI_SS1_GPIO_Port GPIOE
#define SPI_SS2_Pin GPIO_PIN_15
#define SPI_SS2_GPIO_Port GPIOE
#define SPI_SS3_Pin GPIO_PIN_10
#define SPI_SS3_GPIO_Port GPIOB
#define SPI_SS4_Pin GPIO_PIN_11
#define SPI_SS4_GPIO_Port GPIOB
#define IMU_INT1_Pin GPIO_PIN_12
#define IMU_INT1_GPIO_Port GPIOB
#define IMU_INT2_Pin GPIO_PIN_13
#define IMU_INT2_GPIO_Port GPIOB
#define LD3_Pin GPIO_PIN_14
#define LD3_GPIO_Port GPIOB
#define IMU_SS_Pin GPIO_PIN_15
#define IMU_SS_GPIO_Port GPIOB
#define STLK_RX_Pin GPIO_PIN_8
#define STLK_RX_GPIO_Port GPIOD
#define STLK_TX_Pin GPIO_PIN_9
#define STLK_TX_GPIO_Port GPIOD
#define USB_OverCurrent_Pin GPIO_PIN_7
#define USB_OverCurrent_GPIO_Port GPIOG
#define MOTOR4_PWM_H_Pin GPIO_PIN_6
#define MOTOR4_PWM_H_GPIO_Port GPIOC
#define USB_SOF_Pin GPIO_PIN_8
#define USB_SOF_GPIO_Port GPIOA
#define USB_VBUS_Pin GPIO_PIN_9
#define USB_VBUS_GPIO_Port GPIOA
#define USB_ID_Pin GPIO_PIN_10
#define USB_ID_GPIO_Port GPIOA
#define USB_DM_Pin GPIO_PIN_11
#define USB_DM_GPIO_Port GPIOA
#define USB_DP_Pin GPIO_PIN_12
#define USB_DP_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define MOTOR2_INDEX_Pin GPIO_PIN_10
#define MOTOR2_INDEX_GPIO_Port GPIOC
#define MOTOR2_FAIL_Pin GPIO_PIN_11
#define MOTOR2_FAIL_GPIO_Port GPIOC
#define MOTOR2_ISENSE_Pin GPIO_PIN_12
#define MOTOR2_ISENSE_GPIO_Port GPIOC
#define MOTOR2_DISABLE_Pin GPIO_PIN_0
#define MOTOR2_DISABLE_GPIO_Port GPIOD
#define MOTOR1_INDEX_Pin GPIO_PIN_1
#define MOTOR1_INDEX_GPIO_Port GPIOD
#define MOTOR1_FAIL_Pin GPIO_PIN_2
#define MOTOR1_FAIL_GPIO_Port GPIOD
#define MOTOR1_ISENSE_Pin GPIO_PIN_3
#define MOTOR1_ISENSE_GPIO_Port GPIOD
#define MOTOR1_DISABLE_Pin GPIO_PIN_4
#define MOTOR1_DISABLE_GPIO_Port GPIOD
#define MOTOR4_INDEX_Pin GPIO_PIN_6
#define MOTOR4_INDEX_GPIO_Port GPIOD
#define MOTOR4_FAIL_Pin GPIO_PIN_7
#define MOTOR4_FAIL_GPIO_Port GPIOD
#define MOTOR4_ISENSE_Pin GPIO_PIN_9
#define MOTOR4_ISENSE_GPIO_Port GPIOG
#define MOTOR4_DISABLE_Pin GPIO_PIN_10
#define MOTOR4_DISABLE_GPIO_Port GPIOG
#define MOTOR3_INDEX_Pin GPIO_PIN_11
#define MOTOR3_INDEX_GPIO_Port GPIOG
#define MOTOR3_FAIL_Pin GPIO_PIN_12
#define MOTOR3_FAIL_GPIO_Port GPIOG
#define MOTOR3_ISENSE_Pin GPIO_PIN_13
#define MOTOR3_ISENSE_GPIO_Port GPIOG
#define MOTOR3_DISABLE_Pin GPIO_PIN_14
#define MOTOR3_DISABLE_GPIO_Port GPIOG
#define LD2_Pin GPIO_PIN_7
#define LD2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

void SwitchId(uint8_t id);
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
