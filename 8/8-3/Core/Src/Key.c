#include "Key.h"

unsigned char Key1Flag = 0; // 按键1按下标志位，初始为0

void Key_Scan(void)
{
    if(KEY1 == 1) // 按键按下为高电平
    {
        HAL_Delay(20); // 消抖延时20ms
        if(KEY1 == 1) // 再次检测按键状态
        {
            Key1Flag = 1; // 确认按下
            while(KEY1 == 1); // 等待按键释放
        }
    }
}
