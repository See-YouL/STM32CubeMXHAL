#include "UART.h"
#include "main.h"

unsigned char Uart1ReceiveBuf[MAX_REC_LENGTH] = {0}; // UART1 存储接收数据
unsigned char Uart1ReceiveFlag = 0; // UART1 接收完成标志
unsigned int Uart1ReceiveCnt = 0; // UART1 接收数据计数器
unsigned char Uart1Temp[REC_LENGTH] = {0}; // UART1 接收数据缓存

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
    if(huart->Instance == USART1) // 如果是USART1
    {
        Uart1ReceiveBuf[Uart1ReceiveCnt] = Uart1Temp[0]; // 将接收到的数据存入接收缓存
        Uart1ReceiveCnt++; // 接收计数器加1
        if(0x0A == Uart1Temp[0]) // 如果接收到换行符
        {
            Uart1ReceiveFlag = 1; // 设置接收完成标志
        }
        HAL_UART_Receive_IT(&huart1, (uint8_t*)Uart1Temp, REC_LENGTH); // 继续开启下一个接收中断
    }
}

// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
// {
//     if (huart->Instance == USART1)
//     {
//         uint8_t star='*';
//         HAL_UART_Transmit(&huart1, &star, 1, 0xFFFF);

//         HAL_UART_Receive_IT(&huart1, (uint8_t*)Uart1Temp, REC_LENGTH);
//     }
// }
