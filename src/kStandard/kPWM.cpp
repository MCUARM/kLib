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



#include "kPWM.h"

const kPWM_out * kPWM::out = (kPWM_out*)SRAM1_BASE;
const kPWM_in  * kPWM::in  = (kPWM_in *)SRAM1_BASE;


void kPWM_calculatePWM(kPWM_EXTI_data_storage & EXTIx_data,unsigned char channel)
{
	// get timer value
	EXTIx_data.SysTick_val = SysTick->VAL;
	EXTIx_data.kSystem_timer_val = kSystem_ms_downcounter;

	// check if rising or falling edge occurred
	if( (EXTI->RTSR & (1<<channel))) // rising edge
	{
		// disable rising edge trigger
		EXTI->RTSR &= ~(1<<channel);

		// update incoming pwm time
		EXTIx_data.last_update_kSystem_timer_value = EXTIx_data.last_kSystem_timer_value - EXTIx_data.kSystem_timer_val;

		// save current timers values
		EXTIx_data.last_kSystem_timer_value = EXTIx_data.kSystem_timer_val;
		EXTIx_data.last_SysTick_value = EXTIx_data.SysTick_val;

		// enable falling edge trigger
		EXTI->FTSR |= (1<<channel);
	}else 	// falling edge occurred
	{
		// disable falling edge trigger
		EXTI->FTSR &= ~(1<<channel);

		// calculate pwm width
		// get miliseconds
		EXTIx_data.temp_ms = EXTIx_data.last_kSystem_timer_value - EXTIx_data.kSystem_timer_val;


		// get microseconds
		if(EXTIx_data.temp_ms)
		{
			EXTIx_data.temp_ms--;
			// SysTick overflows
			EXTIx_data.temp_us = EXTIx_data.last_SysTick_value + (SysTick->LOAD+1);
		}
		// change units to microseconds
		EXTIx_data.temp_ms *= 1000;

		EXTIx_data.temp_us -= EXTIx_data.SysTick_val;
		EXTIx_data.temp_us *= 1000;
		EXTIx_data.temp_us /= (SysTick->LOAD+1);

		// collect data
		EXTIx_data.temp_ms += EXTIx_data.temp_us;

		// update signal value
		EXTIx_data.pwm_input_register = EXTIx_data.temp_ms;

		// enable rising edge trigger
		EXTI->RTSR |= (1<<channel);
	}

	// clear pending flag (in fact write one)
	EXTI->PR |= (1<<channel);

}

kPWM_EXTI_data_storage EXTIx_data[15];
void kPWM_EXTI0_IRQ_Handler(void)
{
	kPWM_calculatePWM(EXTIx_data[0],0);
}

void kPWM_EXTI1_IRQ_Handler(void)
{
	kPWM_calculatePWM(EXTIx_data[1],1);
}
void kPWM_EXTI2_IRQ_Handler(void)
{
	kPWM_calculatePWM(EXTIx_data[2],2);
}

void kPWM_EXTI3_IRQ_Handler(void)
{
	kPWM_calculatePWM(EXTIx_data[3],3);
}

void kPWM_EXTI4_IRQ_Handler(void)
{
	kPWM_calculatePWM(EXTIx_data[4],4);
}
void kPWM_EXTI9_5_IRQ_Handler(void)
{
	if(EXTI->PR & (1<<5))
	{
		kPWM_calculatePWM(EXTIx_data[5],5);
	}
	if(EXTI->PR & (1<<6))
	{
		kPWM_calculatePWM(EXTIx_data[6],6);
	}
	if(EXTI->PR & (1<<7))
	{
		kPWM_calculatePWM(EXTIx_data[7],7);
	}
	if(EXTI->PR & (1<<8))
	{
		kPWM_calculatePWM(EXTIx_data[8],8);
	}
	if(EXTI->PR & (1<<9))
	{
		kPWM_calculatePWM(EXTIx_data[9],9);
	}
}
void kPWM_EXTI15_10_IRQ_Handler(void)
{
	if(EXTI->PR & (1<<10))
	{
		kPWM_calculatePWM(EXTIx_data[10],10);
	}
	if(EXTI->PR & (1<<11))
	{
		kPWM_calculatePWM(EXTIx_data[11],11);
	}
	if(EXTI->PR & (1<<12))
	{
		kPWM_calculatePWM(EXTIx_data[12],12);
	}
	if(EXTI->PR & (1<<13))
	{
		kPWM_calculatePWM(EXTIx_data[13],13);
	}
	if(EXTI->PR & (1<<14))
	{
		kPWM_calculatePWM(EXTIx_data[14],14);
	}
	if(EXTI->PR & (1<<15))
	{
		kPWM_calculatePWM(EXTIx_data[15],15);
	}
}

void (*kPWM_irq_handler[7])(void) =
{
	kPWM_EXTI0_IRQ_Handler, //0
	kPWM_EXTI1_IRQ_Handler, //1
	kPWM_EXTI2_IRQ_Handler, //2
	kPWM_EXTI3_IRQ_Handler, //3
	kPWM_EXTI4_IRQ_Handler, //4
	kPWM_EXTI9_5_IRQ_Handler, //5
	kPWM_EXTI15_10_IRQ_Handler //6
};

kPWM::kPWM(void)
{

}

kPWM::kPWMHardware::kPWMHardware(void)
{

}


kPWM::kPWMHardware& kPWM::kPWMHardware::operator = (unsigned int pwmHard)
{

	if(pwmHard & 0x80000000)
	{
		// PWM input mode (based on EXTI and system timer)
		isInput = true;

		exti.hardware = pwmHard;

		uint8_t EXTI_channel = pwmHard & 0x0F;
		uint8_t IRQ_channel = EXTI_channel;
		uint8_t IRQ_vector_index = EXTI_channel;

		if(EXTI_channel > 9)
		{
			IRQ_channel = 40;
			IRQ_vector_index = 6;
		}else if(EXTI_channel > 4)
		{
			IRQ_channel = 23;
			IRQ_vector_index = 5;
		}else IRQ_channel += 6;

		this->EXTI_data = &EXTIx_data[EXTI_channel];

		kSystem.setIRQHandler(IRQ_channel,kPWM_irq_handler[IRQ_vector_index]);
		kSystem.enableInterrupt(IRQ_channel,0,0);



	}else
	{
		// PWM output mode (based on Timer OC channel)
		isInput = false;


		unsigned int temp;
		unsigned int * pReg;
		unsigned char * pData;

		this->tim = (TIM_TypeDef*)kPrivate::setupPeripheralOutput(pwmHard);

		// decode output register
		temp = (pwmHard & 0x18000000) >> 27;
		this->output = (uint32_t*)&this->tim->CCR4 - (uint32_t)temp;

		// make sure timer is stopped
		this->tim->CR1 &= ~(1);

		// if it is TIM1 or TIM8 set global output enable
		if((unsigned int)this->tim & 0x00010000) this->tim->BDTR |= (1<<15);


		// setup OCx
		// get CCMRx register
		pReg = (unsigned int*)( ((unsigned int)&this->tim->CCMR1) |	((unsigned int)((pwmHard & 0x20000000) >> 27))  );
		temp = *pReg;
		pData = (unsigned char*)&temp;
		pwmHard &= 0x40000000;
		pwmHard = pwmHard >> 30;
		pData+=pwmHard;
		// clear bits
		*pData &= ~(7<<4);
		// set bits
		*pData |= ((6<<4) | (1<<3));
		// save settings
		*pReg = temp;

		//enable channel
		this->tim->CCER |= (1<<( ((unsigned int)this->output) - ((unsigned int)&this->tim->CCR1)));

	}


	return (*this);
}



void kPWM::run(unsigned short int resolution, unsigned int tick_freq)
{

	unsigned int timer_clock;
	unsigned int prescaler;

	// check if timer is APB2 or APB1 peripheral
	if( ((uint32_t)this->hardware.tim) & 0x00010000)
	{
		// timer is connected to APB2 bus
		timer_clock = kSystem.APB2_Timer_CLK();

	}else
	{
		// timer is connected to APB1 bus
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

			this->hardware.tim->CR1 |=1;
		}

	}



}


kPWM::operator unsigned int()
{
	return (unsigned int)this->hardware.EXTI_data->pwm_input_register;
}
uint32_t kPWM::getValue()
{
	if(hardware.isInput) return this->operator unsigned int();
	return *hardware.output;
}
