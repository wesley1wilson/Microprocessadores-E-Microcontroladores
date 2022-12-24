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

    //configurando PA6 como saída (o pino PA6 tem um LED conectado)
    GPIOA->MODER |= (0b01 << 12);
    GPIOA->MODER |= (0b01 << 14);

    while(1)
    {
    	GPIOA->ODR &= ~(1<<6);
    	Delay_ms(250);
    	GPIOA->ODR |= (1<<6);

    	GPIOA->ODR &= ~(1<<7);
		Delay_ms(250);
		GPIOA->ODR |= (1<<7);
	}

}

