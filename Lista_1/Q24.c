#include "stm32f4xx.h"
#include "Utility.h"
#define LED1_ON (GPIOA->ODR |= (1 << 6))
#define LED1_OFF (GPIOA->ODR &= ~(1 << 6))
#define LED2_ON (GPIOA->ODR |= (1 << 7))
#define LED2_OFF (GPIOA->ODR &= ~(1 << 7))
#define K0 !(GPIOE->IDR & (1<<3))
#define K1 !(GPIOE->IDR & (1<<4))

int main(void)
{
	Configure_Clock();
	Delay_Start();

	RCC->AHB1ENR |= 1;         //habilita o clock do GPIOA
	RCC->AHB1ENR |= 1<<4;    //habilita o clock do GPIOE

	//configurando PA6 como sa?da (o pino PA6 tem um LED conectado)
	GPIOA->MODER |= (0b01 << 12);
	//configurando PA7 como sa?da (o pino PA6 tem um LED conectado)
	GPIOA->MODER |= (0b01 << 14);

	//Configurando o pino PE3 como entrada
	GPIOE->MODER &= ~(0b11 << 6);
	GPIOE->PUPDR |= (0b01 << 6);    //habilita o resistor de pull up para garantir n?vel l?gico alto quando o bot?o estiver solto
	//Configurando o pino PE4 como entrada
	GPIOE->MODER &= ~(0b11 << 8);
	GPIOE->PUPDR |= (0b01 << 8);    //habilita o resistor de pull up para garantir n?vel l?gico alto quando o bot?o estiver solto
	int verificarPin = 0;
	while(1)
	{
		LED1_OFF;
		LED2_OFF;
		if (K0 && !K1){
			verificarPin = 1;
		}
		if (!K0 && K1){
			verificarPin = 0;
		}
		if ((K1 && K0) && verificarPin == 1){
			LED1_ON;
			LED2_ON;
		}
	}

}
