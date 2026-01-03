# STM32CubeMXHAL

## 介绍

- 参考书籍: 《嵌入式系统开发项目教程——基于STM32CubeMX+HAL库》 曾文权 王辉 王亚涛 编著
- 开发板使用野火霸道V2,下载器为野火高速版DAP下载器

## 目录

1. STM32开发初体验
2. 编写自己的库函数
    - 2-1 指针操作寄存器点灯
    - 2-2 优化寄存器流水灯
    - 2-4 引入HAL库函数
3. 按键控制的开关灯设计
    - 3-1 轮询式获取按键输入
    - 3-2 外部中断获取按键输入
4. 串口控制的开关灯设计
    - 4-1 开关灯的数据发送
    - 4-2 开关灯的数据接收
    - 4-3 自定义串口命令控制开关灯
5. 电子秒表的设计
    - 5-1 使用定时器定时1s
    - 5-2 使用定时器实现状态机
    - 5-3 实现电子秒表

## 引脚配置

### LED引脚

![LED引脚配置](https://raw.githubusercontent.com/See-YouL/PicGoFhotos/master/20251122224753.png)

- LED_R PB5
- LED_G PB0
- LED_B PB1

### 按键引脚

![按键引脚配置](https://raw.githubusercontent.com/See-YouL/PicGoFhotos/master/20251216171317.png)

- KEY1 PA0
- KEY2 PC13
