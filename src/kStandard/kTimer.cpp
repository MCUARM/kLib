/***********************************************************************************
 *                                                                                 *
 *   kLib - C++ development tools for ARM Cortex-M devices                         *
 *                                                                                 *
 *     Copyright (c) 2018, project author Pawel Zalewski                           *
 *     All rights reserved.                                                        *
 *                                                                                 *
 ***********************************************************************************
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions  in  binary  form  must  reproduce the above copyright
 *      notice,  this  list  of conditions and the following disclaimer in the
 *      documentation  and/or  other materials provided with the distribution.
 *   3. Neither  the  name  of  the  copyright  holder  nor  the  names of its
 *      contributors  may  be used to endorse or promote products derived from
 *      this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,  BUT NOT LIMITED  TO, THE
 *   IMPLIED WARRANTIES OF MERCHANTABILITY  AND FITNESS FOR A PARTICULAR PURPOSE
 *   ARE DISCLAIMED.  IN NO EVENT SHALL  THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *   LIABLE  FOR  ANY  DIRECT,  INDIRECT,  INCIDENTAL,  SPECIAL,  EXEMPLARY,  OR
 *   CONSEQUENTIAL  DAMAGES  (INCLUDING,  BUT  NOT  LIMITED  TO,  PROCUREMENT OF
 *   SUBSTITUTE  GOODS  OR SERVICES;  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *   INTERRUPTION) HOWEVER  CAUSED  AND  ON  ANY THEORY OF LIABILITY, WHETHER IN
 *   CONTRACT,  STRICT  LIABILITY,  OR  TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *   ARISING  IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 *
 */



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
