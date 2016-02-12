#include "kPWM.h"

const kPWM_Timer1 * kPWM::Timer1 = (kPWM_Timer1 *)SRAM1_BASE;
const kPWM_Timer2 * kPWM::Timer2 = (kPWM_Timer2 *)SRAM1_BASE;

kPWM::kPWM(void)
{

}

kPWM::kPWMHardware::kPWMHardware(void)
{
	this->output = &this->default_CCR;
}

kPWM::kPWMHardware& kPWM::kPWMHardware::operator = (const kPWM_Timer2Pin & pwmHard)
{
	uint32_t reg_add = (uint32_t)&pwmHard;
	reg_add -= (uint32_t)kPWM::Timer2;

	//register hardware
	this->tim = TIM2;

	//enable TIM2 clock
	RCC->APB1ENR |= 1;
	//stop TIM2
	TIM2->CR1 &= ~(1);


	//enable GPIOA clock
	RCC->AHB1ENR |= 1;
	//PA5 alternate function mode
	GPIOA->MODER |= (2<<10);
	//PA5 output type push-pull
	GPIOA->OTYPER &= ~(1<<5);
	//PA5 output speed medium
	GPIOA->OSPEEDR &= ~(3<<10);
	GPIOA->OSPEEDR |= (1<<10);
	//PA5 no pull resistors
	GPIOA->PUPDR &= ~(3<<10);
	//PA5 alternate function AF01 (TIM2_CH1)
	GPIOA->AFR[0] &= ~(15<<20);
	GPIOA->AFR[0] |= (1<<20);



	//PWM mode 1
	TIM2->CCMR1 &= ~(7<<4);
	TIM2->CCMR1 |= (6<<4);

	//Enable preload
	TIM2->CCMR1 |= (1<<3);

	//PWM active high and enable channel
	TIM2->CCER &= ~3;
	TIM2->CCER |= 1;

	//Enable auto-reload
	//TIM2->CR1 |= (1<<7);


	this->output = (uint32_t *)&TIM1->CCR1;



	return *this;
}

void kPWM::start(unsigned short int resolution, unsigned int tick_freq)
{

	unsigned int timer_clock = kSystem.APB2_Timer_CLK();
	unsigned int prescaler;

	TIM2->CR1 &= ~((15<<3)+1);
	TIM2->ARR = (uint32_t)resolution-1;

	if(tick_freq)
	{
		prescaler = timer_clock/tick_freq;

		if(prescaler)
		{
			prescaler -=1;
			TIM2->PSC = (uint16_t)prescaler;

			TIM2->CR1 |=1;
		}

	}


}


