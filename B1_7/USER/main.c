#include "stm32f10x.h"

void PWM_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    GPIOA->CRL =0x0000000B;
    TIM2->PSC = 72-1;  
    TIM2->ARR = 1000-1; 
    TIM2->CR1 |= 0x01;  
		TIM2->CCR1 = 300; 	// Thiet lap gia tri so sanh tuong ung 300/1000= 30% PWM
		TIM2->CCMR1 |= 0x0060;// PWM1 cho kenh 1
		TIM2->CCER |= 0x01; // bat tin hieu cho kenh 1(PA0)
		TIM2->EGR |=0x01;
}

int main(void) {
    PWM_Init();
    while (1){
			
		}
}
