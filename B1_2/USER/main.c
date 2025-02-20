#include "stm32f10x.h" 

void GPIO_Config(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;
    GPIOA->CRL =0x00000003;
    GPIOB->CRL =0x00000003;                         
    GPIOB->ODR |= 0x00;                      
}

void EXTI_Config(void) {
    AFIO->EXTICR[0] &= ~AFIO_EXTICR1_EXTI0;        // reset EXTI0
    AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PB;      // EXTI0 voi PB0
    EXTI->IMR |= 0x01;                             // Bat ngat cho EXTI0
    EXTI->FTSR |= 0x01;                            // Kich hoat ngat suon xuong

    NVIC_EnableIRQ(EXTI0_IRQn);                   	// bat ngat EXTI0 trong NVIC
    NVIC_SetPriority(EXTI0_IRQn, 1);                          
}

void EXTI0_IRQHandler(void) {
    if (EXTI->PR & EXTI_PR_PR0){                         
        EXTI->PR |= EXTI_PR_PR0;                              
        GPIOA->ODR ^= 0x01;
    }
}

int main(void) {
    GPIO_Config();
    EXTI_Config();
    while (1) {

    }
}