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

#define K0 !(GPIOC -> IDR & (1 << 3))
#define K1 !(GPIOC -> IDR & (1 << 4))
#define K2 !(GPIOC -> IDR & (1 << 5))

#define k0 !(GPIOE->IDR & (1<<2))
#define k1 !(GPIOE->IDR & (1<<3))
#define k2 !(GPIOE->IDR & (1<<4))


#define LEDX_OFF   (GPIOC -> ODR &= ~(1 << 0))
#define LEDX_ON    (GPIOC -> ODR |= (1 << 0))
#define LEDY_OFF   (GPIOC -> ODR &= ~(1 << 1))
#define LEDY_ON    (GPIOC -> ODR |= (1 << 1))
#define LEDZ_OFF   (GPIOC -> ODR &= ~(1 << 2))
#define LEDZ_ON    (GPIOC -> ODR |= (1 << 2))

void atraso(int atraso){
    while(atraso) --atraso;
}

int main(void){
	uint8_t mask[16]={ 0b00111111, //0
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

		RCC->AHB1ENR |= (1 << 3);
		RCC->AHB1ENR |= (1 << 4);

		GPIOD->MODER |= (1<<12);
		GPIOD->MODER |= (1<<10);
		GPIOD->MODER |= (1<<0);
		GPIOD->MODER |= (1<<2);
		GPIOD->MODER |= (1<<4);
		GPIOD->MODER |= (1<<6);
		GPIOD->MODER |= (1<<8);

		GPIOE->MODER |= (1<<0);
		GPIOE->MODER |= (1<<2);

		while(1){
			for(int i = 0, j = 0; i < 10; i++, j++){

				for(int j = 0; j < 10; j++){
					GPIOD->ODR = mask[j];
					GPIOE->ODR |= (1 << 1);
					delay(150000);
					GPIOE->ODR &= ~(1 << 1);

					GPIOD->ODR = mask[i];
					GPIOE->ODR |= (1 << 0);
					delay(200000);
					GPIOE->ODR &= ~(1 << 0);
				}


			}

			for(int i = 9; i >=0; i--){

						for(int j = 9; j >= 0; j--){
							GPIOD->ODR = mask[j];
							GPIOE->ODR |= (1 << 1);
							delay(150000);
							GPIOE->ODR &= ~(1 << 1);

							GPIOD->ODR = mask[i];
							GPIOE->ODR |= (1 << 0);
							delay(200000);
							GPIOE->ODR &= ~(1 << 0);
						}


					}

			//delay(100000);
			//GPIOE->ODR &= ~(1 << 1);

		}
}
