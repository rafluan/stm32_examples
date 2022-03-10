#include "stm32f429xx.h"

int main()
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Enable peripheral clock to GPIOA
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN; // Enable peripheral clock to GPIOG

    GPIOG->MODER |= GPIO_MODER_MODER13_0; // Configure gpio with - General purpose output mode
    GPIOA->PUPDR |= GPIO_PUPDR_PUPDR0_1;

    /********************* Interrupt settings *********************/
    SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0 ;
    EXTI->IMR |= (1 << 0);
    EXTI->RTSR |= EXTI_RTSR_TR0;

    NVIC_EnableIRQ(EXTI0_IRQn);
    NVIC_SetPriority(EXTI0_IRQn, 0);

    while (1)
    {
    }

    return 0;
}

void EXTI0_IRQHandler(void)
{
    if(EXTI->PR & EXTI_PR_PR0)
         EXTI->PR |= EXTI_PR_PR0;

    GPIOG->ODR  ^= GPIO_ODR_OD13_Msk;
}
