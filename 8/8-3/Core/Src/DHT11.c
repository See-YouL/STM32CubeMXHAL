#include "DHT11.h"

/**
 * @brief 以微秒为单位的延时函数，使用 SysTick 计数器实现精确的延时
 * @note 该函数通过计算 SysTick 计数器的值来实现延时，适用于需要精确控制时间的场景，如与 DHT11 传感器通信时的时序要求
 * @param us: 需要延时的微秒数
 * @return None
 */
void DelayUS(uint32_t us){
  __IO uint32_t currentTicks = SysTick->VAL; // 获取当前 SysTick 计数器的值，SysTick 是一个 24 位的递减计数器，用于实现延时功能
  const uint32_t tickPerMs = SysTick->LOAD + 1; // 计算每毫秒的计数器滴答数，SysTick->LOAD 是 SysTick 计数器的重装载值，+1 是因为计数器从 LOAD 开始递减到 0，所以实际周期是 LOAD + 1 个时钟周期
  const uint32_t nbTicks = ((us - ((us > 0) ? 1 : 0)) * tickPerMs) / 1000; // 计算需要等待的计数周期数，考虑到函数调用的时间开销
  uint32_t elapsedTicks = 0; // 初始化已等待的计数周期数为 0
  __IO uint32_t oldTicks = currentTicks; // 保存初始的 SysTick 计数器值，用于后续计算经过的时间
  do {
  currentTicks = SysTick->VAL; // 获取当前 SysTick 计数器的值
  elapsedTicks += (oldTicks < currentTicks) ? tickPerMs + oldTicks - currentTicks :
              oldTicks - currentTicks; // 计算从上次获取计数器值到现在经过的计数周期数，考虑到计数器可能已经从 0 重新加载到 LOAD 的情况
  oldTicks = currentTicks; // 更新 oldTicks 为当前的计数器值，以便下一次循环计算经过的时间
  } while (nbTicks > elapsedTicks); // 循环直到等待的计数周期数达到或超过所需的 nbTicks，确保至少等待了指定的微秒数
}

/**
 * @brief 将 DHT11 数据引脚配置为推挽输出模式，以便发送信号给 DHT11 传感器
 * @param None
 * @return None
 */
static void DHT11_Mode_OUT_PP(void){
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = DHT11_Pin; // 配置 DHT11 数据引脚
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // 设置为推挽输出模式
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; // 设置输出速度为低速

  HAL_GPIO_Init(DHT11_GPIO_Port, &GPIO_InitStruct); // 初始化 GPIO 引脚
}

/**
 * @brief 将 DHT11 数据引脚配置为输入模式，以便接收来自 DHT11 传感器的数据
 * @param None
 * @return None
 */
static void DHT11_Mode_IN_NP(void){
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = DHT11_Pin; // 配置 DHT11 数据引脚
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT; // 设置为输入模式
  GPIO_InitStruct.Pull = GPIO_NOPULL; // 不使用上拉或下拉电阻

  HAL_GPIO_Init(DHT11_GPIO_Port, &GPIO_InitStruct); // 初始化 GPIO 引脚
}

/**
 * @brief 从 DHT11 传感器读取一个字节的数据，按照 DHT11 的通信协议进行时序控制
 * @note DHT11 在发送数据时会先拉低数据线 50 微秒，然后根据数据位的值保持高电平的时间不同，
 * 1 的高电平时间大约为 70 微秒，0 的高电平时间大约为 26-28 微秒，
 * 因此通过延时和读取数据线的状态可以判断每一位数据的值
 * @param None
 * @return 读取到的一个字节数据，包含 DHT11 传感器发送的湿度或温度数据的一部分
 */
uint8_t DHT11_ReadByte(void){
  uint8_t i, temp = 0;

  for (i = 0; i < 8; i++)
  {
    while (DHT11_IN == 0)
    {
      ; // 等待 DHT11 数据引脚变为高电平，表示开始发送数据位
    }
    DelayUS(50); // 等待 50 微秒，DHT11 在发送数据位时会保持高电平至少 26-28 微秒，50 微秒的延时可以确保在数据位的中间读取到正确的值
    if (DHT11_IN == 1) // 如果 DHT11 数据引脚仍然是高电平，表示发送的数据位是 1，否则是 0
    {
      while (DHT11_IN == 1)
      {
        ; // 等待 DHT11 数据引脚变为低电平，表示数据位发送完成，为下一位数据做准备
      }
      temp |= (uint8_t)(0x01 << (7 - i)); // 将读取到的数据位设置到 temp 的对应位置，0x01 << (7 - i) 表示将 1 左移到第 (7 - i) 位，i 从 0 到 7 依次读取每一位数据
    }
    else // 如果 DHT11 数据引脚是低电平，表示发送的数据位是 0
    {
      temp &= (uint8_t)~(0x01 << (7 - i)); // 将读取到的数据位设置为 0，使用按位与操作将对应位置清零
    }
  }

  return temp;
}

/**
 * @brief 从 DHT11 传感器读取湿度和温度数据，并进行校验
 * @note 该函数按照 DHT11 的通信协议进行时序控制，首先发送开始信号，然后等待 DHT11 的响应，
 * 接着依次读取湿度整数部分、湿度小数部分、温度整数部分、温度小数部分和校验和，最后通过校验和验证数据的正确性
 * @param DHT11_Data: 指向 DHT11_Data_TypeDef 结构体的指针，用于存储读取到的湿度和温度数据
 * @return DHT11_OK 表示读取成功，DHT11_ERR 表示读取失败，DHT11_BUSY 表示 DHT11 没有响应开始信号，可能正在忙碌中
 */
uint8_t DHT11_ReadData(DHT11_Data_TypeDef * DHT11_Data){
  DHT11_Mode_OUT_PP(); // 将 DHT11 数据引脚配置为推挽输出模式，准备发送开始信号
  DHT11_OUT_0; // 将 DHT11 数据引脚拉低，表示开始信号，DHT11 在接收到开始信号后会准备发送数据
  HAL_Delay(18); // 等待 18 毫秒，DHT11 在接收到开始信号后会保持数据线低电平至少 18 毫秒，确保 DHT11 已经准备好发送数据
  DHT11_OUT_1; // 将 DHT11 数据引脚拉高，结束开始信号，DHT11 在接收到结束信号后会拉高数据线并保持至少 20-40 微秒的时间，然后开始发送数据
  DelayUS(50); // 等待 50 微秒，确保 DHT11 已经准备好发送数据

  DHT11_Mode_IN_NP(); // 将 DHT11 数据引脚配置为输入模式，准备接收数据
  if (DHT11_IN == 0) // 如果 DHT11 数据引脚是低电平，表示 DHT11 已经响应开始信号并准备发送数据
  {
    while (DHT11_IN == 0)
    {
      ; // 等待 DHT11 数据引脚变为高电平，表示 DHT11 已经开始发送数据
    }

    while (DHT11_IN == 1)
    {
      ; // 等待 DHT11 数据引脚变为低电平，表示 DHT11 发送数据位的准备阶段结束，为正式发送数据做准备
    }

    DHT11_Data->humi_int = DHT11_ReadByte(); // 读取湿度整数部分
    DHT11_Data->humi_deci = DHT11_ReadByte(); // 读取湿度小数部分
    DHT11_Data->temp_int = DHT11_ReadByte(); // 读取温度整数部分
    DHT11_Data->temp_deci = DHT11_ReadByte(); // 读取温度小数部分
    DHT11_Data->check_sum = DHT11_ReadByte(); // 读取校验和

    DHT11_Mode_OUT_PP(); // 将 DHT11 数据引脚配置为推挽输出模式，准备发送结束信号
    DHT11_OUT_1; // 将 DHT11 数据引脚拉高, 表示结束信号，DHT11 在发送完数据后会保持数据线高电平至少 20-40 微秒，确保 DHT11 已经完成数据发送

    if (DHT11_Data->check_sum == DHT11_Data->humi_int + DHT11_Data->humi_deci + DHT11_Data->temp_int + DHT11_Data->temp_deci) // 校验数据的正确性，校验和应该等于湿度整数部分、湿度小数部分、温度整数部分和温度小数部分的总和
    {
      return DHT11_OK; // 如果校验成功，返回 DHT11_OK 表示读取成功
    }
    else
    {
      return DHT11_ERR; // 如果校验失败，返回 DHT11_ERR 表示读取失败
    }
  }
  else
  {
    return DHT11_BUSY; // 如果 DHT11 数据引脚不是低电平，表示 DHT11 没有响应开始信号，可能正在忙碌中，返回 DHT11_BUSY 表示读取失败
  }
}
