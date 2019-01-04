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



#include "kSerial.h"


const char* kSerial::endl = "\r\n";


void kSerial::enableInterrupt(uint16_t interrupt_flags)
{
	this->hardware.usart->CR1 |= (interrupt_flags & 0x01F0);
}
void kSerial::disableInterrupt(uint16_t interrupt_flags)
{
	interrupt_flags &= 0x01F0;
	this->hardware.usart->CR1 &= ~(interrupt_flags);
}

kSerialHardware& kSerialHardware::operator = (uint32_t hard_code)
{
	this->usart = (USART_TypeDef*)kPrivate::setupPeripheralOutput(hard_code);

	// force one stop bit
	this->usart->CR2 &= 0xCFFF;

	// enable receiver and/or transmitter
	hard_code = hard_code >> 25;
	this->usart->CR1 |= hard_code;

	return (*this);
}
kSerialHardware& kSerialHardware::operator , (uint32_t hard_code)
{
	return ((*this) = hard_code);
}

void kSerial::run(uint32_t BaudRate)
{
	  uint32_t tmpreg = 0x00, apbclock = 0x00;
	  uint32_t integerdivider = 0x00;
	  uint32_t fractionaldivider = 0x00;

	/*---------------------------- USART BRR Configuration -----------------------*/
	  /* Configure the USART Baud Rate */

	  //usart off
	  this->hardware.usart->CR1 &= 0xDFFF;
	  // get peripheral clock
	  apbclock = kSystem.getPeripheralClock((unsigned int*)this->hardware.usart);

	  /* Determine the integer part */
	  if ((this->hardware.usart->CR1 & 0x8000) != 0)
	  {
	    /* Integer part computing in case Oversampling mode is 8 Samples */
	    integerdivider = ((25 * apbclock) / (2 * (BaudRate)));
	  }
	  else /* if ((USARTx->CR1 & USART_CR1_OVER8) == 0) */
	  {
	    /* Integer part computing in case Oversampling mode is 16 Samples */
	    integerdivider = ((25 * apbclock) / (4 * (BaudRate)));
	  }
	  tmpreg = (integerdivider / 100) << 4;

	  /* Determine the fractional part */
	  fractionaldivider = integerdivider - (100 * (tmpreg >> 4));

	  /* Implement the fractional part in the register */
	  if ((this->hardware.usart->CR1 & 0x8000) != 0)
	  {
	    tmpreg |= ((((fractionaldivider * 8) + 50) / 100)) & ((uint8_t)0x07);
	  }
	  else /* if ((USARTx->CR1 & USART_CR1_OVER8) == 0) */
	  {
	    tmpreg |= ((((fractionaldivider * 16) + 50) / 100)) & ((uint8_t)0x0F);
	  }

	  /* Write to USART BRR register */
	  this->hardware.usart->BRR = (uint16_t)tmpreg;


	  // usart on
	  this->hardware.usart->CR1 |= 0x2000;
}

kSerial::kSerial(void)
{

}
bool kSerial::newByteAvailable(void)
{
	if(this->hardware.usart->SR & ~(1<<5)) return true;
	return false;
}
uint8_t kSerial::readByte(void)
{
	return ((uint8_t)this->hardware.usart->DR);
}
void kSerial::write(uint8_t byte)
{
	// wait while Tx buffer not empty
	while(!(this->hardware.usart->SR & ~(1<<7)));
	// write next byte
	this->hardware.usart->DR = byte;
}
void kSerial::write(const void * data)
{
	uint8_t * p = (uint8_t*)data;
	while(*p)
	{
		write(*p);
		p++;
	}

}
void kSerial::write(const void * data, uint32_t bytes)
{
	uint8_t * p = (uint8_t*)data;

	for(unsigned int i=0;i<bytes;i++)
	{
		// write one byte
		this->write(*p);
		// increment pointer
		p++;
	}
}


