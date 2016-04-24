#include "kTimer.h"

bool default_trigg = false;
bool * trigg_p = &default_trigg;

void kTimer_TIM1_UP_TIM10_IRQHandler(void)
{
	*trigg_p = true;
	// clear update flag
	TIM1->SR &= (~1);
}





bool kTimer::checkTrigger(void)
{
	if(*trigg_p)
	{
		*trigg_p = false;
		return true;
	}
	return false;
}
kTimer::kTimerHardware& kTimer::kTimerHardware::operator = (const kTimer::kTimer_timer & timerHard)
{
	switch(timerHard)
	{
		case kTimer_timer::Timer1:

			//enable TIM1 clock
			RCC->APB2ENR |= 1;
			this->tim = TIM1;


		break;

		default:
			// unexpected timerHard value
		break;
	}

	return (*this);
}
void kTimer::run(unsigned short int resolution, unsigned int tick_freq)
{

	unsigned int timer_clock;
	unsigned int prescaler;

	if(this->hardware.tim == TIM1 ||
	   this->hardware.tim == TIM9 ||
	   this->hardware.tim == TIM10 ||
	   this->hardware.tim == TIM11)
	{
		timer_clock = kSystem.APB2_Timer_CLK();

	}else if(this->hardware.tim == TIM2 ||
			 this->hardware.tim == TIM3 ||
			 this->hardware.tim == TIM4 ||
			 this->hardware.tim == TIM5)
	{
		timer_clock = kSystem.APB1_Timer_CLK();
	}

	this->hardware.tim->CR1 &= ~((15<<3)+1);
	this->hardware.tim->ARR = (uint32_t)resolution-1;

	if(tick_freq)
	{
		prescaler = timer_clock/tick_freq;

		if(prescaler)
		{
			prescaler -=1;
			this->hardware.tim->PSC = (uint16_t)prescaler;

			// enable update interrupt
			this->hardware.tim->DIER |= 1;
			// setup nvic
			kSystem.setIRQHandler(TIM1_UP_TIM10_IRQn,kTimer_TIM1_UP_TIM10_IRQHandler);
			kSystem.enableInterrupt(TIM1_UP_TIM10_IRQn,0,1);

			this->hardware.tim->CR1 |=1;
		}

	}

}
