/**
 * @file    : main.c
 * @author  : Eric
 * @brief   : 2-1 指针操作寄存器点灯
 */


int main(void)
{
    unsigned int *pAPB2ENR = (unsigned int *)0x40021018; // RCC_APB2ENR寄存器地址
    unsigned int *pGPIOB_CRL = (unsigned int *)0x40010C00; // GPIOB_CRL寄存器地址
    unsigned int *pGPIOB_ODR = (unsigned int *)0x40010C0C; // GPIOB_ODR寄存器地址
    *pAPB2ENR |= 0x00000008;
    *pGPIOB_CRL |= 0x00000022;
    *pGPIOB_ODR |= 0x00000002;
}
