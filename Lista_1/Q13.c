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
	Configure_Clock();
	Delay_Start();
	RCC->AHB1ENR |= 1;
	RCC->AHB1ENR |= (1 << 3);

	GPIOD->MODER |=(1<<0);
	GPIOD->MODER |=(1<<2);
	GPIOD->MODER |=(1<<4);

	GPIOA->MODER |= (1 << 0);
	GPIOA->MODER |= (1 << 2);
	GPIOA->MODER |= (1 << 4);
	while(1){
		for(int i = 0; i < 3; i++){
			GPIOA->ODR = 1;
			GPIOD->ODR = 4;
			Delay_ms(2000);
			GPIOD->ODR = 2;
			Delay_ms(1000);
			GPIOA->ODR = 4;
			GPIOD->ODR = 1;
			Delay_ms(2000);
			GPIOA->ODR = 2;
			Delay_ms(1000);

		}


	}
}
