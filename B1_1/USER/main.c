#include "stm32f10x.h"

void GPIO_Config(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		GPIOA->CRL=0x00000003;
}

void Timer_Config(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    TIM2->PSC = 7200 - 1;
    TIM2->ARR = 10000 - 1; 
    TIM2->DIER |= TIM_DIER_UIE; // Kich hoat co ngat
    TIM2->CR1 |= 0x01;

    NVIC_EnableIRQ(TIM2_IRQn);
}

void TIM2_IRQHandler(void) {
    if (TIM2->SR & TIM_SR_UIF) { 
        TIM2->SR &= ~TIM_SR_UIF; 
        GPIOA->ODR ^= 0x01;
    }
}

int main(void) {
    GPIO_Config();
    Timer_Config();
    while (1) {
        
    }
}
