#include "UART.h"


extern UART_HandleTypeDef huart1; // 声明 UART1 句柄

unsigned char Uart1ReceiveBuf[MAX_REC_LENGTH] = {0}; // UART1 接收缓冲区
unsigned char Uart1ReceiveFlag = 0; // UART1 接收完成标志
unsigned char Uart1ReceiveCnt = 0; // UART1 已接收字节数
unsigned char Uart1Temp[REC_LENGTH] = {0}; // UART1 临时接收缓冲区

/**
 * @brief 重定向 printf 函数到 UART1
 * @param ch 要发送的字符
 * @param f 文件指针（未使用）
 * @return 发送的字符
 */
int fputc(int ch, FILE *f) {
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY); // 将字符通过 UART1 发送
  return ch; // 返回发送的字符
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
  if (huart == &huart1) // 判断是否是 UART1 的接收完成回调
  {
    Uart1ReceiveBuf[Uart1ReceiveCnt++] = Uart1Temp[0]; // 将接收到的字节存入缓冲区并更新计数
    if (Uart1ReceiveCnt >= MAX_REC_LENGTH) // 如果接收字节数超过缓冲区大小，重置计数以避免溢出
    { 
      Uart1ReceiveCnt = 0; // 重置计数
    }
    if (Uart1Temp[0] == '\n') // 如果接收到换行符，认为一条命令接收完成
    {
      Uart1ReceiveFlag = 1; // 设置接收完成标志
      Uart1ReceiveCnt = 0; // 重置计数以准备接收下一条命令
    }
    else
    {
      Uart1ReceiveFlag = 0; // 未接收到完整命令，继续接收
    }
    HAL_UART_Receive_IT(&huart1, Uart1Temp, REC_LENGTH); // 继续接收下一个字节
  }
}
