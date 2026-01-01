#ifndef __UART_H__
#define __UART_H__

#define REC_LENGTH 1
#define MAX_REC_LENGTH 1024

extern unsigned char Uart1ReceiveBuf[MAX_REC_LENGTH]; // UART1 存储接收数据
extern unsigned char Uart1ReceiveFlag; // UART1 接收完成标志
extern unsigned int Uart1ReceiveCnt; // UART1 接收数据计数器
extern unsigned char Uart1Temp[REC_LENGTH]; // UART1 接收数据缓存

#endif
