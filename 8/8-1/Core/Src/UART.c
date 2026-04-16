#include "UART.h"


extern UART_HandleTypeDef huart1; // 声明 UART1 句柄
extern TIM_HandleTypeDef htim2; // 声明定时器2 句柄

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

// /**
//  * @brief 串口中断回调函数(基于换行符)
//  * @param huart UART 句柄
//  * @note 当 UART 接收完成时，该函数会被调用。它将接收到的字节存入缓冲区，并根据接收到的内容更新接收完成标志和计数器。
//  *     如果接收到的字节是换行符（'\n'），则认为一条命令接收完成，设置接收完成标志并重置计数器以准备接收下一条命令。
//  *    无论接收到的字节是什么，函数都会继续调用 HAL_UART_Receive_IT 来准备接收下一个字节。
//  * @return 无返回值
//  */
// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
//   if (huart == &huart1) // 判断是否是 UART1 的接收完成回调
//   {
//     Uart1ReceiveBuf[Uart1ReceiveCnt++] = Uart1Temp[0]; // 将接收到的字节存入缓冲区并更新计数
//     if (Uart1ReceiveCnt >= MAX_REC_LENGTH) // 如果接收字节数超过缓冲区大小，重置计数以避免溢出
//     { 
//       Uart1ReceiveCnt = 0; // 重置计数
//     }
//     if (Uart1Temp[0] == '\n') // 如果接收到换行符，认为一条命令接收完成
//     {
//       Uart1ReceiveFlag = 1; // 设置接收完成标志
//       Uart1ReceiveCnt = 0; // 重置计数以准备接收下一条命令
//     }
//     else
//     {
//       Uart1ReceiveFlag = 0; // 未接收到完整命令，继续接收
//     }
//     HAL_UART_Receive_IT(&huart1, Uart1Temp, REC_LENGTH); // 继续接收下一个字节
//   }
// }

/**
 * @brief 串口中断回调函数(基于定时器截断)
 * @param huart UART 句柄
 * @note 当 UART 接收完成时，该函数会被调用。它首先重置定时器2 的计数器，如果这是接收的第一个字节，则启动定时器2 的中断。
 * 然后将接收到的字节存入 UART1 接收缓冲区，并更新接收计数器。
 * 最后，重新打开 UART 接收中断以准备接收下一个字节。
 * @return 无返回值
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
  if (huart->Instance == USART1)
  {
    __HAL_TIM_SET_COUNTER(&htim2, 0); // 重置定时器计数器
    if (0 == Uart1ReceiveCnt) // 如果是接收的第一个字节，启动定时器中断
    {
      __HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_UPDATE); // 清除定时器更新中断标志
      HAL_TIM_Base_Start_IT(&htim2); // 启动定时器中断
    }
    Uart1ReceiveBuf[Uart1ReceiveCnt] = Uart1Temp[0]; // 将接收到的字节存入缓冲区并更新计数
    Uart1ReceiveCnt++; // 下标递增
    HAL_UART_Receive_IT(&huart1, (uint8_t *)Uart1Temp, REC_LENGTH); // 重新打开 UART 接收中断以接收下一个字节
  }
}

/**
 * @brief 通过 RS485 发送数据
 * @param pData 要发送的数据指针
 * @param Size 要发送的数据长度
 * @note 该函数首先设置 RS485 发送模式，然后通过 UART1 发送数据，最后设置 RS485 接收模式以准备接收数据。
 * @return 无返回值
 */
void RS485_Send(uint8_t *pData, uint16_t Size) {
  SET_RS485_SEND; // 设置 RS485 发送模式
  HAL_UART_Transmit(&huart1, pData, Size, HAL_MAX_DELAY); // 通过 UART1 发送数据
  SET_RS485_RECEIVE; // 设置 RS485 接收模式
}
