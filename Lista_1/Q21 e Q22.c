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
#include "Utility.h"
#include <math.h>

int main(void)
{
RCC->AHB1ENR |= 1;         //habilita o clock do GPIOA
	RCC->AHB1ENR |= 1<<4;    //habilita o clock do GPIOE

	//configurando PA6 como saída (o pino PA6 tem um LED conectado)
	GPIOA->MODER |= (0b01 << 12);
	//configurando PA7 como saída (o pino PA6 tem um LED conectado)
	GPIOA->MODER |= (0b01 << 14);

	//Configurando o pino PE3 como entrada
	GPIOE->MODER &= ~(0b11 << 6);
	GPIOE->PUPDR |= (0b01 << 6);    //habilita o resistor de pull up para garantir nível lógico alto quando o botão estiver solto
	//Configurando o pino PE4 como entrada
	GPIOE->MODER &= ~(0b11 << 8);
	GPIOE->PUPDR |= (0b01 << 8);    //habilita o resistor de pull up para garantir nível lógico alto quando o botão estiver solto

	while(1)
	{
		uint32_t leitura = GPIOE->IDR;    //leia os níveis nos pinos da porta E
		if(leitura & (1<<3)) //testa se o pino PE3 é alto
		{
			//se for alto, executa isso
			GPIOA->ODR |= (1<<6);    //manda nível alto para o pino PA6
		}
		else
		{
			//se for baixo executa aquilo
			GPIOA->ODR &= ~(1<<6);    //manda nível baixo para o pino PA6
		}
		if(leitura & (1<<4)) //testa se o pino PE4 é alto
		{
			//se for alto, executa isso
			GPIOA->ODR |= (1<<7);    //manda nível alto para o pino PA7
		}
		else
		{
			//se for baixo executa aquilo
			GPIOA->ODR &= ~(1<<7);    //manda nível baixo para o pino PA7
		}
	}
}
