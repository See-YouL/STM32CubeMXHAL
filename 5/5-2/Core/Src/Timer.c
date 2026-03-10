#include "main.h"

extern TIM_HandleTypeDef htim3;
extern unsigned char KeyState; // 按键状态变量，默认为检测状态
extern unsigned char KeyFlag; // 按键有效状态, 1有效, 0无效

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim == (&htim3))
    {
        switch(KeyState) // TIM3 每 10ms 触发中断，检测按键
        {
            case KEY_CHEKC:
                if(KEY1 == 1) // 读到高电平(按键按下)，进入待确认状态
                {
                    KeyState = KEY_COMFIRM;
                }
                break;
            case KEY_COMFIRM:
                if(KEY1 == 1) // 读到高电平(按键按下)，进入待释放状态
                {
                    KeyState = KEY_RELEASE;
                    KeyFlag = 1; // 有效标志为1，按下按键立即执行按键任务
                }
                else // 读到低电平(按键未按下)，说明是干扰信号，回到检测状态
                {
                    KeyState = KEY_CHEKC;
                }
                break;
            case KEY_RELEASE:
                if(KEY1 == 0) // 读到低电平(按键释放)，回到检测状态
                {
                    KeyState = KEY_CHEKC;
                }
        }
    }

}
