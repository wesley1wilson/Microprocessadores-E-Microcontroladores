#include "stm32f4xx.h"
#include "Utility.h"
#define LED_OFF (GPIOA->ODR |= (1 << 6))
#define LED_ON (GPIOA->ODR &= ~(1 << 6))
#define LED2_OFF (GPIOA->ODR |= (1 << 7))
#define LED2_ON (GPIOA->ODR &= ~(1 << 7))
#define K0 !(GPIOE->IDR & (1<<4))
#define K1 !(GPIOE->IDR & (1<<3))

void questao_25(){
		RCC->AHB1ENR |= 1;         //habilita o clock do GPIOA
	    RCC->AHB1ENR |= 1<<4;    //habilita o clock do GPIOE

	    //configurando PA6 como saída (o pino PA6 tem um LED conectado)
	    GPIOA->MODER |= (0b01 << 12);
	    //configurando PA7 como saída (o pino PA6 tem um LED conectado)
	    GPIOA->MODER |= (0b01 << 14);

	    //Configurando o pino PE3 como entrada
	    GPIOE->MODER &= ~(0b11 << 6);
	    GPIOE->PUPDR |= (0b01 << 6);    //habilita o resistor de pull up para garantir nível lógico alto quando o botão estiver solto
	    //Configurando o pino PE4 como entrada
	    GPIOE->MODER &= ~(0b11 << 8);
	    GPIOE->PUPDR |= (0b01 << 8);    //habilita o resistor de pull up para garantir nível lógico alto quando o botão estiver solto

	    while(1){
	    	LED_OFF;
			LED2_OFF;

			if(K0 && !K1){
				uint32_t a = 0;
				while(K0){
					Delay_ms(100);
					if(K1){
						if(a<=1000){
							LED_ON;
							LED2_ON;
						}
					}else{
						LED_OFF;
					}
					a += 100;
				}
			}
	    }
}

int main(void)
{
	Configure_Clock();
	Delay_Start();
	questao_25();
}
