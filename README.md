# STM32CubeMXHAL

## 工程环境

- 参考书籍: 《嵌入式系统开发项目教程——基于STM32CubeMX+HAL库》 曾文权 王辉 王亚涛 编著
- 开发板: 野火霸道V2(STM32F103ZET6)
- 下载器: 野火高速版DAP下载器
- IDE版本: Keil MDK5(V5.24.2.0)
- 编译器版本: V5.06update(build528)
- STM32CubeMX版本: V6.16.0
- HAL库版本: V1.8.6

## 目录

- STM32开发初体验
- 编写自己的库函数
  - 2-1 指针操作寄存器点灯
  - 2-2 优化寄存器流水灯
  - 2-4 引入HAL库函数
- 按键控制的开关灯设计
  - 3-1 轮询式获取按键输入
  - 3-2 外部中断获取按键输入
- 串口控制的开关灯设计
  - 4-1 开关灯的数据发送
  - 4-2 开关灯的数据接收
  - 4-3 自定义串口命令控制开关灯
- 电子秒表的设计
  - 5-1 使用定时器定时1s
  - 5-2 使用定时器实现状态机
  - 5-3 实现电子秒表
- 电子音乐播放器
  - 6-1 驱动无源蜂鸣器演奏音符


## 引脚配置

### LED引脚

![LED引脚配置](https://raw.githubusercontent.com/See-YouL/PicGoFhotos/master/20251122224753.png)

----

低电平点亮

- LED_R PB5
- LED_G PB0
- LED_B PB1

### 按键引脚

![按键引脚配置](https://raw.githubusercontent.com/See-YouL/PicGoFhotos/master/20251216171317.png)

----

按键按下为高电平

- KEY1 PA0
- KEY2 PC13

### 串口引脚

![串口引脚](https://raw.githubusercontent.com/See-YouL/PicGoFhotos/master/20260103162839.png)

----

- USART1_RXD PA9
- USART1_TXD PA10

### 蜂鸣器引脚

- 正极 PA11
- 负极 GND

## 勘误

书中存在很多不完整的地方以及配置上的省略**具体请参照本工程中的代码, 全部经过测试**

### P96 重定向fputc函数

使用书中重定向fputc函数的方法时需要将Keil MDK的编译选项中的"Use MicroLIB"选项勾选。

![勾选MicroLIB](https://raw.githubusercontent.com/See-YouL/PicGoFhotos/master/20260103163322.png)

### P107 串口应声虫程序

在main函数的while(1)循环之前需要添加如下代码以初始化串口接收中断

```c
HAL_UART_Receive_IT(&huart1, (uint8_t *)Uart1Temp, REC_LENGTH); // 启动UART1接收中断
```

```txt
建议添加到main.c文件的/* USER CODE BEGIN 2 */ 和 /* USER CODE END 2 */之间，如下所示：
```

```c
/* USER CODE BEGIN 2 */
HAL_UART_Receive_IT(&huart1, (uint8_t *)Uart1Temp, REC_LENGTH); // 启动UART1接收中断
/* USER CODE END 2 */
```

### P133 秒表程序

在 `Timer.h`中

```c
extern unsigned char SW_Statue; // 秒表状态
extern unsigned char SW_Flag; // 秒表标志位, 1 : 打印时间

```

在 `Timer.c` 中

```c
extern TIM_HandleTypeDef htim1;

SW_TypeDef Clock = {0}; // 秒表变量
unsigned char SW_Flag = 0; // 打印标志位
```

在 `main.c` 中

增加头文件引用

```c
/* USER CODE BEGIN Includes */
#include "Timer.h" // 秒表
#include <stdio.h> // printf重定向

/* USER CODE END Includes */
```

增加 print 重定向

```c
/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int fputc(int ch, FILE *f) // print 重定向
{
    HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
    return ch;
}
/* USER CODE END 0 */
```
