#include "stm32f10x.h"
#include "stdio.h"

void I2C1_Config(void) {
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    GPIOB->CRL = 0xFF000000; // Alternate function open-drain
    I2C1->CR2 = 36; // AP1 la 36Mhz
    I2C1->CCR = 180; // CCR=36Mhz/(2*100khz) ( set xung nhip SCL o standard mode 100khz)
    I2C1->TRISE = 37; 
    I2C1->CR1 |= I2C_CR1_PE; // Kich hoat I2C
}

void I2C_start( uint8_t address, uint8_t direction) {
    I2C1->CR1 |= I2C_CR1_START;
    while (!(I2C1->SR1 & I2C_SR1_SB)); 
    I2C1->DR = address | direction; 
    while (!(I2C1->SR1 & I2C_SR1_ADDR)); 
    I2C1->SR1; // doc du lieu tu SR1
    I2C1->SR2; // xoa bit ADDR chuan bi cho lan doc tiep
}

void I2C_write(uint8_t data) {
    while (!(I2C1->SR1 & I2C_SR1_TXE)); //Transmit Data Register Empty
    I2C1->DR = data; 
}

uint8_t I2C_read_ack(void) {
    I2C1->CR1 |= I2C_CR1_ACK; // xac nhan voi slave la du lieu duoc gui da nhan thanh cong, master->ack
    while (!(I2C1->SR1 & I2C_SR1_RXNE)); //Receive Not Empty
    return I2C1->DR;
}

uint8_t I2C_read_nack(void) {
    I2C1->CR1 &= ~I2C_CR1_ACK; // bao cho slave khong co du lieu nao duoc yeu cau tiep theo, master->nack
    I2C1->CR1 |= I2C_CR1_STOP;
    while (!(I2C1->SR1 & I2C_SR1_RXNE)); 
    return I2C1->DR; 
}

void BH1750_Config() {
    I2C_start(0x23<<1, 0x00);
    I2C_write(0x10); 
    I2C1->CR1 |= I2C_CR1_STOP;
}

uint8_t data[1];
uint16_t BH1750_Read() {
    I2C_start(0x23 << 1, 0x01);
    data[0] = I2C_read_ack(); 
    data[1] = I2C_read_nack();
    I2C1->CR1 |= I2C_CR1_STOP;
    uint16_t val = ((data[0] << 8) | data[1])/1.2; // 8 bit cao la data[0], 8 bit thap data[1]
    return val;
}

void UART_Config(void) {
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN |RCC_APB2ENR_IOPAEN;
    GPIOA->CRH =0x000000B0;
    USART1->BRR = 72000000/9600;
    USART1->CR1 |=USART_CR1_TE | USART_CR1_UE;
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

void timer_Config(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    TIM2->PSC = 72 - 1;
    TIM2->ARR = 0xFFFF;
    TIM2->CR1 |= 0x01;
		TIM2->EGR |= 0x01;
}
void delay_ms(uint32_t time) {
    while (time--) {
        TIM2->CNT = 0;
        while (TIM2->CNT < 1000);
    }
}

int main(void) {
    I2C1_Config();
    UART_Config();
    timer_Config();
		BH1750_Config();
    while (1) {
				uint16_t Value = BH1750_Read();
				char c[40];
				snprintf(c, sizeof(c), "BH1750: %u lx\n", Value);
				UART_SendString(c);
        delay_ms(1000);
    }
}
