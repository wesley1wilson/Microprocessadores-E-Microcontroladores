/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "stm32f4xx.h"
#include <stdlib.h>
#include <time.h>

int main(void){
	Configure_Clock();			//configura o sistema de clock
	USART1_Init();				//inicializa a USART1
	Delay_Start();				//inicializa funções de Delay

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;	//habilita o clock do GPIOA
	GPIOA->MODER |= 0b11;					//pino PA0 como entrada analógica
	GPIOA->MODER |= 0b11 << 2;				//pino PA1 como entrada analogica
	GPIOA->MODER |= 0b01 << 4;					//pino PA0 como entrada analógica
	GPIOA->MODER |= 0b01 << 6;				//pino PA1 como entrada analogica

	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;		//liga o clock do ADC1

	ADC->CCR |= 0b01 << 16;		//prescaler /4
	ADC1->SQR1 &= ~(0xF << 20);	//conversão de apenas um canal
	ADC1->SQR3 &= ~(0x1F);		//seleção do canal a ser convertido (IN_0)
	ADC1->CR2 |= ADC_CR2_ADON;	//liga o conversor AD

	while(1)
	{
		ADC1->SQR3 &= ~(0x1F);		//seleção do canal a ser convertido (IN_0)
		ADC1->CR2 |= ADC_CR2_SWSTART;		//inicia a conversão
		while(!(ADC1->SR & ADC_SR_EOC));	//aguarda o fim da conversão
		uint16_t leitura = ADC1->DR;		//faz a leitura do valor convertido

		uint16_t grau = (0.43 * leitura) + 600;
		GPIOA->ODR |= (1 << 2);
		Delay_us(grau);
		GPIOA->ODR &= ~ (1 << 2);
		Delay_us(20000 - grau);

		ADC1->SQR3 |= 0x1;
		ADC1->CR2 |= ADC_CR2_SWSTART;		//inicia a conversão
		while(!(ADC1->SR & ADC_SR_EOC));	//aguarda o fim da conversão
		uint16_t leitura1 = ADC1->DR;		//faz a leitura do valor convertido

		uint16_t grau1 = (0.43 * leitura1) + 600;
		GPIOA->ODR |= (1 << 3);
		Delay_us(grau1);
		GPIOA->ODR &= ~ (1 << 3);
		Delay_us(20000 - grau1);

	}
}
