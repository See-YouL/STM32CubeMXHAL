#ifndef __UART_H__
#define __UART_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h> // 包含标准输入输出库，以使用 printf 函数
#include "main.h"

#define REC_LENGTH 1
#define MAX_REC_LENGTH 1024

extern unsigned char Uart1ReceiveBuf[MAX_REC_LENGTH]; // UART1 接收缓冲区
extern unsigned char Uart1ReceiveFlag; // UART1 接收完成标志
extern unsigned char Uart1ReceiveCnt; // UART1 已接收字节数
extern unsigned char Uart1Temp[REC_LENGTH]; // UART1 临时接收缓冲区


#ifdef __cplusplus
}
#endif

#endif /* __UART_H__ */
