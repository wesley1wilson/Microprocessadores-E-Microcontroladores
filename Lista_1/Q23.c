#include "stm32f4xx.h"
#include "Utility.h"
#define LED_ON (GPIOA->ODR |= (0b01 << 6))
#define LED_OFF (GPIOA->ODR &= ~(0b01 << 6))
#define K0 (GPIOE->IDR & (1 << 3))

int main(void)
{
	Configure_Clock();
	Delay_Start();

	//Iniciando os clocks
	RCC->AHB1ENR |= 1;
	RCC->AHB1ENR |= (1 << 4);

	//Declarando o pino PA6 como saída
	GPIOA->MODER |= (0b01 << 12);

	//Declarando o pino PE3 como entrada
	GPIOE->MODER &= ~(0b11 << 6);
	GPIOE->PUPDR |= (0b01 << 6);

	int boleano = 1, bol = 0;
	while(1){
		if(K0 && boleano){
			LED_OFF;
			bol = 1;
		}
		if(K0 && !boleano){
			LED_ON;
			bol = 1;
		}
		if(!K0 && boleano && bol){
			boleano = 0;
			bol = 0;
		}
		if(!K0 && !boleano && bol){
			boleano = 1;
			bol = 0;
		}
	}
}
