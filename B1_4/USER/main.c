#include "stm32f10x.h"

void GPIO_Config(void) {
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
  GPIOA->CRL = 0x00000003;
}

void UART_Config(void){
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN |RCC_APB2ENR_USART1EN;
  GPIOA->CRH =	0x00000400; // Floating input 0100;
	USART1->BRR = 72000000/9600; 
	USART1->CR1 |= USART_CR1_RE | USART_CR1_UE;
}

char Receive(void){
	while (!(USART1->SR & USART_SR_RXNE)); // Receive Not Empty (RXNE)
  return USART1->DR; 
}

int main(void) {
    UART_Config();
    GPIO_Config();
    while (1) {
				char c=Receive();
        if (c=='A') GPIOA->ODR = 0x01;
				if (c=='B') GPIOA->ODR = 0x00;
    }
}
