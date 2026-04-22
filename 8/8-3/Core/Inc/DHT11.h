#ifndef __DHT11_H__
#define __DHT11_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define DHT11_IN HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin) // 读取 DHT11 数据引脚的输入状态
#define DHT11_OUT_1 HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin, GPIO_PIN_SET) // 将 DHT11 数据引脚设置为高电平
#define DHT11_OUT_0 HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin, GPIO_PIN_RESET) // 将 DHT11 数据引脚设置为低电平

#define DHT11_OK 1 // DHT11 读取成功的状态码
#define DHT11_ERR 0 // DHT11 读取失败的状态码
#define DHT11_BUSY 3 // DHT11 正在读取数据的状态码

typedef struct
{
  uint8_t humi_int; // 湿度整数部分
  uint8_t humi_deci; // 湿度小数部分
  uint8_t temp_int; // 温度整数部分
  uint8_t temp_deci; // 温度小数部分
  uint8_t check_sum; // 校验和，用于验证数据的正确性
}DHT11_Data_TypeDef; // 定义一个结构体来存储 DHT11 传感器读取到的数据，包括湿度和温度的整数部分、小数部分以及校验和



#ifdef __cplusplus
}
#endif

#endif /* __DHT11_H__ */
