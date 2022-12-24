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
	int sequencia[1000] = {0};
	int num, topo = 0;

	RCC->AHB1ENR |= 1<<2;

	GPIOC -> MODER |= (1 << 0);
	GPIOC -> MODER |= (1 << 2);
	GPIOC -> MODER |= (1 << 4);


	GPIOC->MODER &= ~(1 << 6);
	GPIOC->PUPDR |= (1 << 6);
	GPIOC->MODER &= ~(1 << 8);
	GPIOC->PUPDR |= (1 << 8);
	GPIOC->MODER &= ~(1 << 10);
	GPIOC->PUPDR |= (1 << 10);

	while(1){
		num = rand() % 3;
		sequencia[topo] = num;
		atraso(1000000);
		for(int i = 0; i < topo + 1; i++){
			if(sequencia[i] == 0){
				LEDX_ON;
				atraso(500000);
				LEDX_OFF;
				atraso(500000);
			}else if(sequencia[i] == 1){
				LEDY_ON;
				atraso(500000);
				LEDY_OFF;
				atraso(500000);
			}else if(sequencia[i] == 2){
				LEDZ_ON;
				atraso(500000);
				LEDZ_OFF;
				atraso(500000);
			}
		}

		int indice = 0;
		while(1){
			if(indice > topo){
				break;
			}

			if(K0 && sequencia[indice] == 0){
				while(1){
					if(!K0){
						indice++;
						break;
					}
				}
			}else if(K0 && sequencia[indice] != 0){
				for(int i = 0; i < 3; i++){
					LEDX_ON;
					LEDY_ON;
					LEDZ_ON;
					atraso(1000000);
					LEDX_OFF;
					LEDY_OFF;
					LEDZ_OFF;
					atraso(1000000);
				}
				exit(0);
			}

			if(K1 && sequencia[indice] == 1){
				while(1){
					if(!K1){
						indice++;
						break;
					}
				}
			}else if(K1 && sequencia[indice] != 1){
				for(int i = 0; i < 3; i++){
					LEDX_ON;
					LEDY_ON;
					LEDZ_ON;
					atraso(1000000);
					LEDX_OFF;
					LEDY_OFF;
					LEDZ_OFF;
					atraso(1000000);
				}
				exit(0);
			}

			if(K2 && sequencia[indice] == 2){
				while(1){
					if(!K2){
						indice++;
						break;
					}
				}
			}else if(K2 && sequencia[indice] != 2){
				for(int i = 0; i < 3; i++){
					LEDX_ON;
					LEDY_ON;
					LEDZ_ON;
					atraso(1000000);
					LEDX_OFF;
					LEDY_OFF;
					LEDZ_OFF;
					atraso(1000000);
				}
				exit(0);
			}
		}
	topo++;
	}
}
