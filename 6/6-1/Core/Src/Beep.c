#include "Beep.h"

extern TIM_HandleTypeDef htim1; // 定时器句柄，需在main.c中定义并初始化

/**
 * @brief 通过定时器控制蜂鸣器发声
 * @param tone 音符频率，单位Hz，范围为CL1(262Hz)到20000Hz，超出范围将停止蜂鸣器
 * @param volumeLevel 音量等级，1-10，1 为最大音量，10 为最小音量，占空比分别为自动重装载值的1/2到1/1024
 * @retval None
 */
void BeepPlay(unsigned short tone, unsigned char volumeLevel)
{
  unsigned short autoReload; // 自动重装载值
  if ((tone < CL1) || (tone > 20000)) // 如果音符频率不合法，停止蜂鸣器
  {
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0); // 停止蜂鸣器
    __HAL_TIM_SET_COUNTER(&htim1, 0);                // 重置计数器
  }
  else // 如果音符频率合法，计算自动重装载值并设置占空比
  {
    autoReload = (BEEP_TIM_CLOCK / tone) - 1; // 计算自动重装载值
    __HAL_TIM_SET_AUTORELOAD(&htim1, autoReload); // 设置自动重装载值
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, autoReload >> volumeLevel); // 设置占空比，音量等级越大，占空比越小
    __HAL_TIM_SET_COUNTER(&htim1, 0); // 重置计数器
  }
}
