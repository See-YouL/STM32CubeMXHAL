#include "UART.h"
#include "main.h"
#include "stdio.h" // 包含stdio.h头文件以使用FILE结构体

unsigned char Uart1ReceiveBuf[MAX_REC_LENGTH] = {0}; // UART1 存储接收数据
unsigned char Uart1ReceiveFlag = 0; // UART1 接收完成标志
unsigned int Uart1ReceiveCnt = 0; // UART1 接收数据计数器
unsigned char Uart1Temp[REC_LENGTH] = {0}; // UART1 接收数据缓存

// 在Keil 魔术棒->Targets->C/C++选项卡中将"Use MicroLIB"选项勾选，否则printf无法使用
/**
 * @brief 重定向c库函数printf到USART1
 * @param ch 需要发送的字符
 * @param f 文件指针
 * @return 发送的字符
 */
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF); // 通过串口发送数据
  return ch;
}

/**
 * @brief 串口中断回调函数
 * @param huart UART句柄
 * @return None
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance != USART1)
    {
        return; // 不是USART1，直接返回
    }

    if(Uart1ReceiveFlag) // 如果上一帧数据还未处理完,丢弃本次接收数据,避免覆盖/越界
    {
        HAL_UART_Receive_IT(&huart1, (uint8_t*)Uart1Temp, REC_LENGTH); // 继续开启下一个接收中断
        return;
    }

    // 兼容CRLF结尾的命令
    if(0x0D == Uart1Temp[0]) // 如果接收到'\r',忽略该字符
    {
        HAL_UART_Receive_IT(&huart1, (uint8_t*)Uart1Temp, REC_LENGTH); // 继续开启下一个接收中断
        return;
    }

    // 越界保护： 预留1字节可放'\0'结束符
    if(Uart1ReceiveCnt < (MAX_REC_LENGTH - 1)) // 防止接收缓存溢出
    {
        Uart1ReceiveBuf[Uart1ReceiveCnt] = Uart1Temp[0]; // 将接收到的数据存入接收缓存
        Uart1ReceiveCnt++; // 接收计数器加1

        if(0x0A == Uart1Temp[0]) // 如果接收到'\n', 认为一帧数据接收完成
        {
            Uart1ReceiveFlag = 1; // 设置接收完成标志
        }
    }
    else // 缓冲满了，强制结束，防止爆内存导致程序异常
    {
        Uart1ReceiveBuf[MAX_REC_LENGTH - 1] = 0; // 防止溢出时，最后一个字节无法放置结束符
        Uart1ReceiveFlag = 1; // 设置接收完成标志
    }

    HAL_UART_Receive_IT(&huart1, (uint8_t*)Uart1Temp, REC_LENGTH); // 继续开启下一个接收中断

}
