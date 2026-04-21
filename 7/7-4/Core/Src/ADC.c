#include "ADC.h"

extern ADC_HandleTypeDef hadc1; // 声明 ADC 句柄

uint32_t AD_Buf[ADC_DMA_BUF_LEN]; // ADC 转换结果缓冲区
uint32_t ADC1_AVG_Buf[ADC_CHANNEL_CNT]; // ADC1 各通道的平均值缓冲区
uint32_t DMA_CNT = 0; // DMA 传输完成计数器
uint8_t DMA_Flag = 0; // DMA 传输完成标志

// /**
//  * @brief ADC 转换完成回调函数
//  * @note 计算光敏电阻的阻值并根据 ADC 值判断光线强弱并且输出结果
//  * @param hadc: ADC 句柄
//  * @return None
//  */
// void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
//   if (hadc == &hadc1) // 判断是否是 ADC1 的转换完成回调
//   {
//     uint32_t AD_Value = HAL_ADC_GetValue(hadc); // 获取 ADC 转换结果

//     // 根据电压分压公式计算光敏电阻的阻值
//     uint32_t PhotoResistorValue = (uint32_t)(10240000 / (1.1 * AD_Value) - 2500);

//     // 打印 ADC 值和光敏电阻值
//     printf("The AD value is %d, the photoresistor value is %d\r\n", AD_Value, PhotoResistorValue);

//     if (AD_Value > DARK_VAL) // 光线较暗
//     {
//       printf("The light is dark.\r\n");
//     }
//     else if (AD_Value < DAZZLING_VAL) // 光线较强
//     {
//       printf("The light is dazzling.\r\n");
//     }
//     else // 光线适中
//     {
//       printf("The light is moderate.\r\n");
//     }
//   }
// }

/**
 * @brief 计算 ADC1 各通道的平均值
 * @note 通过累加 DMA 缓冲区中的 ADC 值并计算平均值来实现滤波功能
 * @param None
 * @return None
 */
void Get_ADC_Avg(void){
  uint32_t ADC1_SUM_Buf[ADC_CHANNEL_CNT] = {0}; // ADC1 各通道的累加和缓冲区
  for (int i = 0; i < ADC_DMA_BUF_LEN; i++)
  {
    ADC1_SUM_Buf[i % ADC_CHANNEL_CNT] += AD_Buf[i]; // 将 DMA 缓冲区中的 ADC 值累加到对应通道的累加和中
  }
  for (int i = 0; i < ADC_CHANNEL_CNT; i++)
  {
    ADC1_AVG_Buf[i] = ADC1_SUM_Buf[i] / (ADC_DMA_BUF_LEN / ADC_CHANNEL_CNT); // 计算每个通道的平均值并存储到 ADC1_AVG_Buf 中
  }
}

/**
 * @brief ADC 转换完成回调函数
 * @note 仅统计 DMA 传输完成的次数
 * @param hadc: ADC 句柄
 * @return None
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
  if (hadc == &hadc1) // 判断是否是 ADC1 的转换完成回调
  {
    Get_ADC_Avg(); // 计算 ADC1 各通道的平均值
    HAL_ADC_Stop_DMA(&hadc1); // 停止 ADC1 的 DMA 传输
    DMA_CNT++; // DMA 传输完成计数器加 1
    DMA_Flag = 1; // 设置 DMA 传输完成标志
  }
}
