/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"	//bibliotecas padr�o STM32F4
#include "Utility.h"	//biblioteca de fun��es utilit�rias
#include "stdio.h"

//fun��o principal
int main(void)
{
	Configure_Clock();			//configura o sistema de clock
	Delay_Start();				//inicializa fun��es de Delay

	RCC->AHB1ENR |= 1;	//habilita o clock do GPIOA
	GPIOA->MODER |= 0b11 << 8;				//inicializa��o do pino PA4 no modo anal�gico

	RCC->APB1ENR |= RCC_APB1ENR_DACEN;		//habilita o clock da interface digital do DAC
	DAC->CR |= DAC_CR_EN1;		//habilita o canal 1 do DAC

	int contador = 0;
	while(1)
	{
		for(; contador<4095; contador++)
		{
			DAC->DHR12R1 = contador;	//escreve no DAC1
			Delay_ms(1);						//aguarda para a pr�xima amostra
		}
		for(; contador>0; contador--)
		{
			DAC->DHR12R1 = contador;	//escreve no DAC1
			Delay_ms(1);						//aguarda para a pr�xima amostra
		}
	}
}
