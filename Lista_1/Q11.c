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
			
int main(void)
{
	Configure_Clock();
	Delay_Start();

	//habilita o clock do GPIOA
	RCC->AHB1ENR |= 1;

	GPIOA->MODER |= (0b01 << 0);
	GPIOA->MODER |= (0b01 << 2);
	GPIOA->MODER |= (0b01 << 4);
	GPIOA->MODER |= (0b01 << 6);
	GPIOA->MODER |= (0b01 << 8);
	GPIOA->MODER |= (0b01 << 10);
	GPIOA->MODER |= (0b01 << 12);
	GPIOA->MODER |= (0b01 << 14);



	while(1)
	{
		for(int8_t contador =0; contador<=255; ++contador)
		{
			GPIOA->ODR = contador;
			Delay_ms(500);
		}

	}
}
