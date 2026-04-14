#include "Beep.h"

extern TIM_HandleTypeDef htim1; // 定时器句柄，需在main.c中定义并初始化
extern TIM_HandleTypeDef htim4; // 定时器句柄，需在main.c中定义并初始化

unsigned short BGM_Length; // 乐谱长度变量，存储当前乐谱的长度
Note_TypeDef * BGM_Current; // 当前乐谱指针，指向正在播放的乐谱数组
unsigned char BGM_Volume; // 乐谱音量变量，存储当前乐谱的音量等级
unsigned char BGM_ChangeFlag; // 乐谱切换标志, 当需要切换乐谱时设置为1，在定时器中断处理函数中检测并切换乐谱

const Note_TypeDef TwoTigersNote[] = { // 《两只老虎》乐谱，包含音符频率和时值
	{0,37}, // 第一个元素的时间值为数组长度 音符数量比数组长度小1
	{CM1,S7/4},{CM2,S7/4},{CM3,S7/4},{CM1,S7/4},
	{CM1,S7/4},{CM2,S7/4},{CM3,S7/4},{CM1,S7/4},
	{CM3,S7/4},{CM4,S7/4},{CM5,S7/4},{0,S7/4},
	{CM3,S7/4},{CM4,S7/4},{CM5,S7/4},{0,S7/4},
	{CM5,S7/8},{CM6,S7/8},{CM5,S7/8},{CM4,S7/8},{CM3,S7/4},{CM1,S7/4},
	{CM5,S7/8},{CM6,S7/8},{CM5,S7/8},{CM4,S7/8},{CM3,S7/4},{CM1,S7/4},
	{CM1,S7/4},{CL5,S7/4},{CM1,S7/4},{0,S7/4},
	{CM1,S7/4},{CL5,S7/4},{CM1,S7/4},{0,S7/4},
};

const Note_TypeDef PeppaPigNote[] = { // 《小猪佩奇》乐谱，包含音符频率和时值
  {0,13},// 第一个元素的时间值为数组长度 音符数量比数组长度小1
	{CH5,S5/4},{CH3,S5/8},{CH1,S5/8},{CH2,S5/4},{CM5,S5/4},
	{CM5,S5/8},{CM7,S5/8},{CH2,S5/8},{CH4,S5/8},{CH3,S5/4},{CH1,S5/4},{0,S5/4},
};

const Note_TypeDef DouDiZhuNote[] = { // 《斗地主》乐谱，包含音符频率和时值
  {0,82},// 第一个元素的时间值为数组长度 音符数量比数组长度小1
  {CM3,S3},{CM3,S3/2},{CM2,S3/2},{CM1,S3},{CM1,S3/2},{CL6,S3/2},  //6
  {CM2,S3/2},{CM3,S3/2},{CM2,S3/2},{CM3,S3/2},{CL5,S3},{CL5,S3},   //6
  {CL6,S3}, {CL6,S3/2}, {CL5,S3/2}, {CL6,S3}, {CM1,S3},            //5
  {CM5,S3/2},{CM6,S3/2},{CM3,S3/2},{CM5,S3/2},{CM2,S3},{CM2,S3},   //6
  
  {CM3,S3},{CM3,S3/2},{CM2,S3/2},{CM3,S3},{CM5,S3},     //5
  {CM6,S3/2},{CM6,S3/2},{CM6,S3/2},{CH1,S3/2},{CM6,S3},{CM5,S3/2},{CM3,S3/2},   //7
  {CM2,S3},{CM2,S3/2},{CM3,S3/2},{CM5,S3},{CL5,S3},     //5
  {CM2,S3/2},{CM3,S3/2},{CM2,S3/2},{CM3,S3/2},{CM1,S3},{CM1,S3},   //6
  
  {CM3,S3},{CM3,S3/2},{CM2,S3/2},{CM3,S3},{CM5,S3},     //5
  {CM6,S3/2},{CH1,S3/2},{CM6,S3/2},{CM5,S3/2},{CM6,S3},{CM5,S3/2},{CM3,S3/2},   //7
  {CM2,S3},{CM2,S3/2},{CM3,S3/2},{CM5,S3},{CL5,S3},     //5
  {CM2,S3/2},{CM3,S3/2},{CM2,S3/2},{CM3,S3/2},{CM1,S3},{CM1,S3},   //6
  
  {CM2,S3/2},{CM2,S3/2},{CM2,S3/2},{CM3,S3/2},{CM5,S3},{CM5,S3/2},{CM6,S3/2},   //7
  {CH1,S3},{CM6,S3},  {CH1,S3},  {CH1,S3},              //4
  {0,S3},
};

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

/**
 * @brief 播放乐谱函数，循环播放乐谱中的每个音符
 * @param volume_level 音量等级，1-10，1 为最大音量
 * @param Music 乐谱数组，包含音符频率和时值，第一个元素的时间值为乐谱长度，音符数量比乐谱长度小1
 * @retval None
 */
void MusicPlay(unsigned char volume_level, Note_TypeDef * Music)
{
  int i = 1; // 从索引1开始，因为索引0存储了乐谱长度
  int length = Music[0].time; // 获取乐谱长度
  while (i <= length) // 循环播放乐谱中的每个音符
  {
    BeepPlay(Music[i].tone, volume_level); // 播放当前音符
    HAL_Delay(Music[i].time); // 等待当前音符的持续时间
    i++; // 继续下一个音符
  }
}

/**
 * @brief 播放背景音乐函数，使用定时器中断循环播放乐谱
 * @param volume_level 音量等级，1-10，1 为最大音量
 * @param BGM 乐谱数组，包含音符频率和时值，第一个元素的时间值为乐谱长度，音符数量比乐谱长度小1
 * @retval None
 */
void BGM_Play(unsigned char volume_level, Note_TypeDef * BGM)
{
  BGM_ChangeFlag = 1; 
  BGM_Length = BGM[0].time; // 获取乐谱长度
  BGM_Current = BGM; // 设置当前乐谱指针
  BGM_Volume = volume_level; // 设置乐谱音量
  HAL_TIM_Base_Start_IT(&htim4); // 启动定时器中断，开始播放乐谱
}

/**
 * @brief 定时器中断回调函数，用于循环播放背景音乐乐谱中的每个音符
 * @param htim 定时器句柄
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim == &htim4) // 判断是否是TIM4中断
  {
    static unsigned short i = 0; // 静态变量，记录当前播放的音符索引

    if (BGM_ChangeFlag) // 如果需要切换乐谱
    {
      i = 0; // 重置音符索引
      BGM_ChangeFlag = 0; // 清除切换标志
    }

    if (i < BGM_Length) // 如果当前音符索引小于乐谱长度，继续播放
    {
      BeepPlay(BGM_Current[i].tone, BGM_Volume); // 播放当前音符
      __HAL_TIM_SET_AUTORELOAD(&htim4, BGM_Current[i].time*10 - 1); // 设置定时器自动重装载值为当前音符的持续时间
      __HAL_TIM_SET_COUNTER(&htim4, 0); // 重置定时器计数器
      i++; // 继续下一个音符
    }
    else // 如果当前音符索引不小于乐谱长度，停止播放并重置索引
    {
      HAL_TIM_Base_Stop_IT(&htim4); // 停止定时器中断，结束播放
    }
  }
}
