#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h"

void UART_Config(void){
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN;
    GPIOA->CRH = 0x000000B0;
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
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN | RCC_APB2ENR_ADC2EN | RCC_APB2ENR_IOPAEN;	
    GPIOA->CRL =0x00;
		ADC1->CR2 |=ADC_CR2_ADON;
		ADC1->SQR3 =0x01; //(PA1)
		ADC2->CR2 |=ADC_CR2_ADON; 	
		ADC2->SQR3 =0x02; //(PA2)
}

uint32_t ADC1_Read(void) {
    ADC1->CR2 |=ADC_CR2_ADON;	
    ADC1->CR2 |=ADC_CR2_SWSTART;
    while (!(ADC1->SR & ADC_SR_EOC)); //End Of Conversion(EOC)
    return ADC1->DR;
}

uint32_t ADC2_Read(void) {
    ADC2->CR2 |=ADC_CR2_ADON;
		ADC2->CR2 |=ADC_CR2_SWSTART;
    while (!(ADC2->SR & ADC_SR_EOC));
    return ADC2->DR;
}

void PWM_Init(uint32_t arr, uint32_t ccr1) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    GPIOA->CRL |= 0x0000000B;
    TIM2->PSC = 72 - 1; 
    TIM2->ARR = arr-1;	
    TIM2->CCR1 = ccr1;
    TIM2->CCMR1 |= 0x0060;//PWM1 cho kenh 1
    TIM2->CCER |= 0x01; //bat tin hieu kenh 1
    TIM2->CR1 |= 0x01;
		TIM2->EGR |= 0x01;
}

#define Fmin 1000
#define Fmax 10000
#define Wmin 10
#define Wmax 90
uint32_t f;
uint32_t w;
uint32_t ADCValue1, ADCValue2;

void task_ADC1(void *pvParameters) {
    while (1) {
        ADCValue1 = ADC1_Read();
        f = Fmin+((ADCValue1*(Fmax-Fmin))/4095);
        vTaskDelay(200);
    }
}

void task_ADC2(void *pvParameters) {
    while (1) {
        ADCValue2 = ADC2_Read();
        w = Wmin+((ADCValue2*(Wmax-Wmin))/4095);
        vTaskDelay(200);
    }
}

void task_PWM(void *pvParameters) {
    while (1) {
        PWM_Init( 1000000/f,(1000000/f)*w/100 );
        vTaskDelay(200);
    }
}

void task_UART(void *pvParameters) {
    char data[50];
    while (1) {
        sprintf(data, "ADC1: %u, ADC2: %u, Tan so PWM: %u Hz, Do rong xung PWM: %u %%\n", ADCValue1, ADCValue2, f, w);
        UART_SendString(data);
        vTaskDelay(500);
    }
}

int main(void) {
    UART_Config();
    ADC_Config();

    xTaskCreate(task_ADC1, "Read ADC1", 128, NULL, 1, NULL);
    xTaskCreate(task_ADC2, "Read ADC2", 128, NULL, 1, NULL);
    xTaskCreate(task_PWM, "PWM Update", 128, NULL, 2, NULL);
    xTaskCreate(task_UART, "UART Send", 128, NULL, 3, NULL);
    vTaskStartScheduler();

}
