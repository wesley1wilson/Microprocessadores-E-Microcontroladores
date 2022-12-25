#include "stm32f4xx.h"
#include "Utility.h"

#define LED1_ON GPIOB->ODR |= (1)
#define LED1_OFF GPIOB->ODR &= ~(1)

int main(void)
{
	Configure_Clock(); //configura o sistema de clock
	USART1_Init(); //inicializa a USART1
	Delay_Start(); //inicializa funções de Delay
	RCC->APB2ENR |= 1 << 8; //liga o clock da interface digital do ADC1
	ADC->CCR |= 0b01 << 16; //prescaler /4
	ADC1->SQR1 &= ~(0xF << 20); //conversão de apenas um canal
	ADC1->SQR3 |= 16; //seleção do canal a ser convertido (IN_16)
	ADC1->SMPR1 |= (7 << 18); //tempo de amostragem igual a 480 ciclos de ADCCLK
	ADC->CCR |= (1 << 23); //liga o sensor de temperatura
	ADC1->CR2 |= 1; //liga o conversor AD
	uint32_t *p = (uint32_t *) 0x1FFF7A2C; //cria ponteiro para uma posição de memória
	uint32_t Word = p[0]; //lê o conteúdo da memória
	uint16_t TS_CAL1 = (Word & 0x0000FFFF); //lê o valor de TS_CAL1
	uint16_t TS_CAL2 = (Word & 0xFFFF0000) >> 16; //lê o valor de TS_CAL2

	RCC->AHB1ENR |= 1; // Habilita o clock do GPIOA
	GPIOA->MODER |= 1;    //configura o pino PA0 como saída digital

	int y;
	while(1)
	{

		ADC1->CR2 |= 1 << 30; //inicia a conversão
		while(!(ADC1->SR & 0x02)); //aguarda o fim da conversão
		//calcula a temperatura
		uint8_t temperatura = ((80*(int)(ADC1->DR - TS_CAL1))/(TS_CAL2-TS_CAL1))+30;
		//printf("Temperatura = %d °C\n", temperatura); //imprime a temperatura
		//Delay_ms(500); //aguarda 500ms para fazer a nova leitura

		if (temperatura <= 35){
			GPIOA->ODR |= 1;
			Delay_us(600);
			GPIOA->ODR &= ~1;
			Delay_us(19400);
		} else if(temperatura > 35 && temperatura < 60){
			y = 72*temperatura - 1920;
			GPIOA->ODR |= 1;
			Delay_us(y);
			GPIOA->ODR &= ~1;
			Delay_us(20000 - y);

		}else if (temperatura >= 60){
			GPIOA->ODR |= 1;
			Delay_us(2400);
			GPIOA->ODR &= ~1;
			Delay_us(17600);
		}
	}
}
