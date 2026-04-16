#ifndef __UART_H__
#define __UART_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h> // 包含标准输入输出库，以使用 printf 函数
#include "main.h"

#define REC_LENGTH 1
#define MAX_REC_LENGTH 1024

#define SET_RS485_SEND HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET) // 设置 RS485 发送模式
#define SET_RS485_RECEIVE HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET) // 设置 RS485 接收模式

extern unsigned char Uart1ReceiveBuf[MAX_REC_LENGTH]; // UART1 接收缓冲区
extern unsigned char Uart1ReceiveFlag; // UART1 接收完成标志
extern unsigned char Uart1ReceiveCnt; // UART1 已接收字节数
extern unsigned char Uart1Temp[REC_LENGTH]; // UART1 临时接收缓冲区

void RS485_Send(uint8_t *pData, uint16_t Size); // 通过 RS485 发送数据的函数声明

#ifdef __cplusplus
}
#endif

#endif /* __UART_H__ */
