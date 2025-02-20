#include "stm32f10x.h"
#include "stdio.h"

void UART_Config(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN; 
		GPIOA->CRH = 0x000000B0; //ALternate function push-pull 50MHz (1011)
    USART1->BRR = 72000000/9600;
    USART1->CR1 |= USART_CR1_TE | USART_CR1_UE;
}

void UART_SendChar(char c) {
    while (!(USART1->SR & USART_SR_TXE));
    USART1->DR = c;
}

void UART_SendString(char *str) {
    while (*str) {
        UART_SendChar(*str++);
    }
}

void ADC_Config(void) {
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN |RCC_APB2ENR_IOPAEN;
    GPIOA->CRL = 0x00; 		
    ADC1->CR1 = 0x00;  
		ADC1->CR2 |=ADC_CR2_ADON;
		ADC1->SQR3 = 0x01; // Kenh 1 (Sequence Register)
}

uint32_t ADC_Read(void) {
		ADC1->CR2 |=ADC_CR2_ADON;	
    ADC1->CR2 |= ADC_CR2_SWSTART;
    while (!(ADC1->SR & ADC_SR_EOC)); //END OF CONVERSION = 1, thoat ra khoi while
    return ADC1->DR;
}

void timer_config(void){
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; 
    TIM2->PSC = 72 - 1;
    TIM2->ARR = 0xFFFF;
    TIM2->CR1 |= 0x01;
		TIM2->EGR |= 0x01;
}

void Delay_ms(uint32_t time){
    while(time--) {
        TIM2->CNT = 0;
        while (TIM2->CNT < 1000);
    }
}

int main(void) {
    UART_Config();
    ADC_Config();
    timer_config();
    while (1) {    
        uint32_t Value = ADC_Read();
        float vol = Value*3.3/4095;
				char data[40];
				snprintf(data, sizeof(data), "ADC: %u, Voltage: %.2f V \n", Value, vol);
				UART_SendString(data);
        Delay_ms(1000);
    }
}
