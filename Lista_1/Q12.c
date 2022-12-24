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

	GPIOA->MODER |= (1 << 0);
	GPIOA->MODER |= (1 << 2);
	GPIOA->MODER |= (1 << 4);
	GPIOA->MODER |= (1 << 6);
	GPIOA->MODER |= (1 << 8);
	GPIOA->MODER |= (1 << 10);
	GPIOA->MODER |= (1 << 12);
	GPIOA->MODER |= (1 << 14);

	int8_t pot;
	while(1)
	{
		for(int i = 0; i < 8; i++){
			pot = pow(2,i);
			GPIOA->ODR = pot;
			Delay_ms(500);

		}
		for(int i = 7; i > 0; i--){
			pot = pow(2,i);
			GPIOA->ODR = pot;
			Delay_ms(500);
		}
	}
}

