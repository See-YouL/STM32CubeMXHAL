#ifndef __LED_H
#define __LED_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define LED_RED_ON HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET) // 红灯亮
#define LED_RED_OFF HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_SET)   // 红灯灭
#define LED_RED_TOGGLE HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin) // 红灯翻转
#define LED_GREEN_ON HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_RESET) // 绿灯亮
#define LED_GREEN_OFF HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET)   // 绿灯灭
#define LED_GREEN_TOGGLE HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin) // 绿灯翻转
#define LED_BLUE_ON HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_RESET) // 蓝灯亮
#define LED_BLUE_OFF HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_SET)   // 蓝灯灭
#define LED_BLUE_TOGGLE HAL_GPIO_TogglePin(LED_B_GPIO_Port, LED_B_Pin) // 蓝灯翻转

#define LED_RED PBout(5) // 红灯控制宏定义，直接操作 GPIOB 的第 5 个引脚
#define LED_GREEN PBout(0) // 绿灯控制宏定义，直接操作 GPIOB 的第 0 个引脚
#define LED_BLUE PBout(1) // 蓝灯控制宏定义，直接操作 GPIOB 的第 1 个引脚

#ifdef __cplusplus
}
#endif

#endif /* __LED_H */
