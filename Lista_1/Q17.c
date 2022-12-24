#include "stm32f4xx.h"
#include "Utility.h"
#define LED1_OFF (GPIOA->ODR |= (1 << 6))
#define LED1_ON (GPIOA->ODR &= ~(1 << 6))
#define LED2_OFF (GPIOA->ODR |= (1 << 7))
#define LED2_ON (GPIOA->ODR &= ~(1 << 7))
#define K0 !(GPIOE->IDR & (1<<3))
#define K1 !(GPIOE->IDR & (1<<4))

int main(void)
{
	Configure_Clock();
	Delay_Start();

	RCC->AHB1ENR |= 1;         //habilita o clock do GPIOA

	//configurando PA0 como entrada
	GPIOA->MODER |= (0b01 << 0);

	while(1)
	{
		for(int x = 600; x <= 2400; x+=10){
			GPIOA->ODR |= (1 << 0);
			Delay_us(x);
			GPIOA->ODR &= ~(1 << 0);
			Delay_us(20000-x);
		}
		for(int x = 2400; x >= 600; x-=10){
			GPIOA->ODR |= (1 << 0);
			Delay_us(x);
			GPIOA->ODR &= ~(1 << 0);
			Delay_us(20000-x);
		}
	}

}
