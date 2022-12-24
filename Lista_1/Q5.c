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

    RCC->AHB1ENR |= 1;         //habilita o clock do GPIOA

    //configurando PA6 como saída (o pino PA6 tem um LED conectado)
    GPIOA->MODER |= (0b01 << 12);

    while(1)
    {
    	for(int i=0;i<4;i++){
    		GPIOA->ODR |= (1<<6);
			Delay_ms(50);
			GPIOA->ODR &= ~(1<<6);
			Delay_ms(50);
    	}
    	Delay_ms(1500);
	}

}

