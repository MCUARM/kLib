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



#include "kADC.h"



void kADC::enableInterrupt(uint32_t interrupt_flags)
{
	hardware.adc->CR1 |= (interrupt_flags & (	kADC_Interrupt_struct::kADC_Interrupt_enum::EndOfConversion |
												kADC_Interrupt_struct::kADC_Interrupt_enum::Overrun));
}
void kADC::disableInterrupt(uint32_t interrupt_flags)
{
	interrupt_flags &= (kADC_Interrupt_struct::kADC_Interrupt_enum::EndOfConversion |
						kADC_Interrupt_struct::kADC_Interrupt_enum::Overrun);
	this->hardware.adc->CR1 &= ~(interrupt_flags);
}

void kADCHardware::operator =(uint32_t hard_code)
{
	adc = (ADC_TypeDef*)kPrivate::setupPeripheralOutput(hard_code);
	channel_number = kPrivate::getUserCode(hard_code);

	uint8_t shift;

	// set sampling time to 15 clock cycles
	if(channel_number < 10)
	{
		// channel number is less than 10: write to SMPR2 register

		/// clear appropriate bits
		shift = 3*channel_number;
		adc->SMPR2 &= ~(7 << shift);
		// set value of 15 clock cycles
		adc->SMPR2 |= (1<<shift);

	}else
	{
		// channel number is greater than 9: write to SMPR1 register

		// clear appropriate bits
		shift = 3*(channel_number-10);
		adc->SMPR1 &= ~(7 << shift);
		// set value of 15 clock cycles
		adc->SMPR1 |= (1<<shift);

	}

}
void kADC::run(kADC_Clock_struct::kADC_Clock_enum clock_divider)
{
	// set APB2 clock divider in CCR register
	// clear appropriate bits
	ADC->CCR &= ~(3<<16);
	ADC->CCR |= (clock_divider<<16);

	// run ADC
	hardware.adc->CR2 |= (1<<0);
}
uint16_t kADC::read()
{

	// select channel number to perform single conversion
	hardware.adc->SQR3 &= ~(0xF);
	hardware.adc->SQR3 |= hardware.channel_number;

	// set number of conversions in SQR1 register to 1 by writing 0 to L bits
	// this is done just by clearing bits
	// clear L bits
	hardware.adc->SQR1 &= ~(15 << 20);

	/* Start software conversion */
	hardware.adc->CR2 |= (uint32_t)(1<<30);

	/* Wait till End of conversion flag set (EOC) */
	while (!(hardware.adc->SR & (1<<1)));

	/* Return result - reading DR also clears EOC bit in SR register */
	return (uint16_t)hardware.adc->DR;
}

