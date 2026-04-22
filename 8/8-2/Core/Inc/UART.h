#ifndef __UART_H__
#define __UART_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h> // 包含标准输入输出库，以使用 printf 函数
#include "main.h"

#define REC_LENGTH 1 // UART 接收缓冲区长度，设置为 1 表示每次接收一个字节
#define MAX_REC_LENGTH 1024 // UART 接收缓冲区最大长度，实际值需要根据应用需求进行调整

#define SET_RS485_SEND HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET) // 设置 RS485 发送模式
#define SET_RS485_RECEIVE HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET) // 设置 RS485 接收模式

#define BROADCAST 0 // Modbus RTU 广播地址，所有从设备都应该响应该地址的命令
#define PHOTO_RES 1 // Modbus RTU 功能码，表示读取光敏电阻数据的命令
#define TEMP_HUMI 2 // Modbus RTU 功能码，表示读取温湿度数据的命令

extern unsigned char Uart1ReceiveBuf[MAX_REC_LENGTH]; // UART1 接收缓冲区
extern unsigned char Uart1ReceiveFlag; // UART1 接收完成标志
extern unsigned int Uart1ReceiveCnt; // UART1 已接收字节数
extern unsigned char Uart1Temp[REC_LENGTH]; // UART1 临时接收缓冲区

void RS485_Send(uint8_t *pData, uint16_t Size); // 通过 RS485 发送数据的函数声明
unsigned short CRC_Compute(unsigned char * puchMsg, unsigned short usDataLen); // 计算 CRC 校验值的函数声明

#ifdef __cplusplus
}
#endif

#endif /* __UART_H__ */
