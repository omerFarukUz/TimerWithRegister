#include "main.h"
#include "string.h"

uint16_t count = 0;

void RCC_Config()
{
	RCC->CR |= 0x10000; 			  // HSEON enable
	while(!(RCC->CR & 0x20000));      // HSEON Ready Flag wait
	RCC->CR |= 0x80000;				  // CSS enable
	RCC->CR |= 0x1000000;			  // PLL Enable
	RCC->PLLCFGR |= 0x400000; 		  // PLL e HSE sectik
	RCC->PLLCFGR |= 0x000004; 		  // PLL M = 4
	RCC->PLLCFGR |= 0x005A00; 		  // PLL N=168
	RCC->PLLCFGR |= 0x000000; 		  // PLL P=2
	RCC->CFGR |= 0x000000; 		 	  // AHB Prescaler = 1
	RCC->CFGR |= 0x080000; 		  	  // APB2 Prescaler = 2
	RCC->CFGR |= 0x001400; 		  	  // APB1 Presclaer = 4
	RCC->CIR |= 0x00080000;			  // HSERDY Flag Clear
	RCC->CIR |= 0x00800000;			  // CSS Flag Clear

}

void Timer2_Config()
{
	RCC->APB1ENR |= 0x01 << 0U;		  // Timer 2 Clock Enable

	TIM2->CR1 &= ~(0x00 << 4U);		  // Counter mode's Upcounter mode
	TIM2->CR1 &= ~(0x00 << 5U);		  // Center Alignment mode's Edge Alignment mode
	TIM2->CR1 &= ~(0x00 << 8U);		  // Clock Division's 84Mhz
	//TIM2->SMCR &= ~(0x00 << 0U);	  // Clock Source Internal Clock Mode
	TIM2->EGR |= 0x01 << 0U;		  // Timer Update Generation
	TIM2->PSC = 41999;
	TIM2->ARR = 4000;

	TIM2->CR1 |= 0x01 << 0U;		  // Timer 2 Counter Enable
}

int main(void)
{
	RCC_Config();
	Timer2_Config();



	while(1)
	{
		count = TIM2->CNT;
	}

}
