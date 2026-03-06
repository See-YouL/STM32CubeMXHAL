#include "main.h"

/**
 * @brief 定时器中断回调函数
 * @param htim 指向触发中断的定时器句柄的指针
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim == (&htim3))
  {
    HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin); // 红灯闪烁
  }
}
