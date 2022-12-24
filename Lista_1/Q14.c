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

	GPIOA->MODER |=(1<<0);
	GPIOA->MODER |=(1<<2);
	GPIOA->MODER |=(1<<4);
	GPIOA->MODER |=(1<<6);
	GPIOA->MODER |=(1<<8);
	GPIOA->MODER |=(1<<10);
	GPIOA->MODER |=(1<<12);

	uint8_t mask[16]={	0b00111111, //0
						0b00000110, //1
						0b01011011, //2
						0b01001111, //3
						0b01100110, //4
						0b01101101, //5
						0b01111101, //6
						0b00000111, //7
						0b01111111, //8
						0b01101111, //9
						0b01110111, //A
						0b01111100, //B
						0b00111001, //C
						0b01011110, //D
						0b01111001, //E
						0b01110001}; //F
	while(1){
		for(int i = 0; i< 16; i++){
			GPIOA->ODR = mask[i];
			Delay_ms(500);
		}
		for(int i = 15; i>= 0; i--){
			GPIOA->ODR = mask[i];
			Delay_ms(500);
		}
	}
}
