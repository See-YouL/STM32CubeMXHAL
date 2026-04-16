#include "Timer.h"

extern TIM_HandleTypeDef htim2;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim)
{
  if (htim == &(htim2)) // 判断是否是定时器2 的中断回调
  {
    LED_RED_TOGGLE; // 翻转红灯状态
    Uart1ReceiveFlag = 1; // 设置 UART 接收完成标志
    HAL_TIM_Base_Stop_IT(&htim2); // 停止定时器中断
  }
}
