/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KEY2_Pin GPIO_PIN_13
#define KEY2_GPIO_Port GPIOC
#define KEY1_Pin GPIO_PIN_0
#define KEY1_GPIO_Port GPIOA
#define LED_G_Pin GPIO_PIN_0
#define LED_G_GPIO_Port GPIOB
#define LED_B_Pin GPIO_PIN_1
#define LED_B_GPIO_Port GPIOB
#define LED_R_Pin GPIO_PIN_5
#define LED_R_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
// 按键定义
#define KEY1 HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin)
#define KEY2 HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin)

// LED操作定义
#define LED_R(x) HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, x) // LED打开关闭
#define LED_G(x) HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, x)
#define LED_B(x) HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, x)
#define LED_R_TOGGLE HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin) // LED取反
#define LED_G_TOGGLE HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin)
#define LED_B_TOGGLE HAL_GPIO_TogglePin(LED_B_GPIO_Port, LED_B_Pin)

// 按键状态机的状态定义
#define KEY_CHEKC 0 // 按键检测状态
#define KEY_COMFIRM 1 // 待确认状态
#define KEY_RELEASE 2 // 待释放状态

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
