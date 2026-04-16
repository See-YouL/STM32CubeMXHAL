#ifndef KEY_H
#define KEY_H

#include "main.h"

#define KEY1 HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin)

extern unsigned char Key1Flag; // 按键1按下标志位

void Key_Scan(void); // 按键扫描函数

#endif
