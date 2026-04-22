#ifndef __ADC_H__
#define __ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define DARK_VAL 8000 // 暗光的阈值，实际值需要根据环境光线情况进行调整
#define DAZZLING_VAL 2000 // 强光的阈值，实际值需要根据环境光线情况进行调整
#define ADC_CHANNEL_CNT 6 // ADC1 通道数量
#define ADC_DMA_BUF_LEN 600 // ADC DMA 缓冲区长度，实际值需要根据采样频率和处理能力进行调整

typedef struct
{
  unsigned short ohm; // 光敏电阻值，单位为欧姆
  unsigned short lux; // 光照强度值，单位为勒克斯
}PhotoRes_TypeDef;

extern uint32_t AD_Buf[ADC_DMA_BUF_LEN]; // ADC 转换结果缓冲区，长度为 ADC_DMA_BUF_LEN，每个元素存储一个 ADC 转换结果
extern uint32_t ADC1_AVG_Buf[ADC_CHANNEL_CNT]; // ADC1 各通道的平均值缓冲区，长度为 ADC_CHANNEL_CNT，每个元素存储一个通道的平均值
extern uint8_t DMA_Flag; // DMA 传输完成标志，0 表示未完成，1 表示完成
extern uint32_t DMA_CNT; // DMA 传输完成计数器
extern const PhotoRes_TypeDef GL5528[281]; // GL5528 光敏电阻的阻值与光照强度的对应关系表，长度为 281，每个元素存储一个数据点

unsigned short GetLux(uint32_t PhotoResistor); // 根据光敏电阻值计算光照强度的函数声明

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */
