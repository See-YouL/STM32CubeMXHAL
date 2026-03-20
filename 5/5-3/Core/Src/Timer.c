#include "Timer.h"

extern TIM_HandleTypeDef htim1;

SW_TypeDef Clock = {0}; // 秒表变量
unsigned char SW_Flag = 0; // 打印标志位

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim)
{
  if (htim == &(htim1))
  {
    Clock.ms100++; // 毫秒自增
    SW_Flag = 1; // 打印时间
    if (10 == Clock.ms100) // 到达100ms
    {
      Clock.second++; // 1s
      SW_Flag = 1; // 打印时间
      Clock.ms100 = 0; // 毫秒计数清零
      if (60 == Clock.second) // 到达60s
      {
        Clock.minute++; // 1min
        Clock.second = 0; // 秒计数清零
        if (60 == Clock.minute) // 到达60min
        {
          Clock.minute = 0; // 分计数清零
        }
      }
    }
  }
}
