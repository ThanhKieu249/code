#include "stm32f10x.h"

void UART_Config(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN;
    GPIOA->CRH = 0x000000B0; // Alternate function push-pull 50Mhz (1011)
    USART1->BRR = 72000000/9600;
		USART1->CR1 |= USART_CR1_TE | USART_CR1_UE; 
}

void UART_SendChar(char c) {
    while (!(USART1->SR & USART_SR_TXE)); //TXE=1 thoat vong lap, san sang nhan du lieu moi(tu c)
    USART1->DR = c;
}

void UART_SendString(char *str) {
    while (*str) {
        UART_SendChar(*str++);
    }
}
int main(void) {
    UART_Config();
    UART_SendString("Hello\n");
		while(1){
		
		}
}
