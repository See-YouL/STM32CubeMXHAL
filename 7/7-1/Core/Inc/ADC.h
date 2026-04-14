#ifndef __ADC_H__
#define __ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define DARK_VAL 8000 // 暗光的阈值，实际值需要根据环境光线情况进行调整
#define DAZZLING_VAL 2000 // 强光的阈值，实际值需要根据环境光线情况进行调整

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */
