#ifndef __ADC_H__
#define __ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define DARK_VAL 8000 // 暗光的阈值，实际值需要根据环境光线情况进行调整
#define DAZZLING_VAL 2000 // 强光的阈值，实际值需要根据环境光线情况进行调整
#define ADC_CHANNEL_CNT 6 // ADC1 通道数量

extern uint32_t AD_Buf[ADC_CHANNEL_CNT]; // ADC 转换结果缓冲区
extern uint32_t DMA_CNT; // DMA 传输完成计数器

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */
