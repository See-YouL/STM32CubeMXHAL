/**
 * @file    : main.c
 * @author  : Eric
 * @brief  : 2-2 优化寄存器流水灯
 */

#include "stm32f103xb.h"

void delay(unsigned int a)
{
    while(a--);
}

int main(void)
{
    RCC->APB2ENR |= 0x00000008;
    GPIOB->CRL &= ~(0xf<<(1*4) | 0xf<<(0*4)); // CRL对应位清零
    GPIOB->CRL |= 0x2<<(1*4) | 0x2<<(0*4);    // 设置为慢速推挽输出

    while(1)
    {
        GPIOB->ODR |= 1 << 0; // PB1置1
        GPIOB->ODR &= ~(1 << 1); // PB2置0
        delay(0xffff);
        GPIOB->ODR |= 1 << 1; // PB1置1
        GPIOB->ODR &= ~(1 << 0); // PB0置0
        delay(0xfffff);
    }
}
