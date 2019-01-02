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




#include "kEXTI.h"


void kEXTI_EmptyIRQ_Handler(void)
{

}

void (*user_irq_handler[16])(void) =
{
	kEXTI_EmptyIRQ_Handler, //0
	kEXTI_EmptyIRQ_Handler,	//1
	kEXTI_EmptyIRQ_Handler, //2
	kEXTI_EmptyIRQ_Handler, //3
	kEXTI_EmptyIRQ_Handler, //4
	kEXTI_EmptyIRQ_Handler, //5
	kEXTI_EmptyIRQ_Handler, //6
	kEXTI_EmptyIRQ_Handler, //7
	kEXTI_EmptyIRQ_Handler, //8
	kEXTI_EmptyIRQ_Handler, //9
	kEXTI_EmptyIRQ_Handler, //10
	kEXTI_EmptyIRQ_Handler, //11
	kEXTI_EmptyIRQ_Handler, //12
	kEXTI_EmptyIRQ_Handler, //13
	kEXTI_EmptyIRQ_Handler, //14
	kEXTI_EmptyIRQ_Handler, //15
};



void kEXTI_EXTI0_IRQ_Handler(void)
{
	// call user interrupt handler function
	user_irq_handler[0]();

	// clear pending flag (in fact write one)
	EXTI->PR |= (1<<0);
}

void kEXTI_EXTI1_IRQ_Handler(void)
{
	// call user interrupt handler function
	user_irq_handler[1]();

	// clear pending flag (in fact write one)
	EXTI->PR |= (1<<1);
}

void kEXTI_EXTI2_IRQ_Handler(void)
{
	// call user interrupt handler function
	user_irq_handler[2]();

	// clear pending flag (in fact write one)
	EXTI->PR |= (1<<2);
}

void kEXTI_EXTI3_IRQ_Handler(void)
{
	// call user interrupt handler function
	user_irq_handler[3]();

	// clear pending flag (in fact write one)
	EXTI->PR |= (1<<3);
}

void kEXTI_EXTI4_IRQ_Handler(void)
{
	// call user interrupt handler function
	user_irq_handler[4]();

	// clear pending flag (in fact write one)
	EXTI->PR |= (1<<4);
}

void kEXTI_EXTI5_9_IRQ_Handler(void)
{
	if(EXTI->PR & (1<<5))
	{
		// call user interrupt handler function
		user_irq_handler[5]();

		// clear pending flag (in fact write one)
		EXTI->PR |= (1<<5);
	}
	if(EXTI->PR & (1<<6))
	{
		// call user interrupt handler function
		user_irq_handler[6]();

		// clear pending flag (in fact write one)
		EXTI->PR |= (1<<6);
	}
	if(EXTI->PR & (1<<7))
	{
		// call user interrupt handler function
		user_irq_handler[7]();

		// clear pending flag (in fact write one)
		EXTI->PR |= (1<<7);
	}
	if(EXTI->PR & (1<<8))
	{
		// call user interrupt handler function
		user_irq_handler[8]();

		// clear pending flag (in fact write one)
		EXTI->PR |= (1<<8);
	}
	if(EXTI->PR & (1<<9))
	{
		// call user interrupt handler function
		user_irq_handler[9]();

		// clear pending flag (in fact write one)
		EXTI->PR |= (1<<9);
	}

}

void kEXTI_EXTI10_15_IRQ_Handler(void)
{
	if(EXTI->PR & (1<<10))
	{
		// call user interrupt handler function
		user_irq_handler[10]();

		// clear pending flag (in fact write one)
		EXTI->PR |= (1<<10);
	}
	if(EXTI->PR & (1<<11))
	{
		// call user interrupt handler function
		user_irq_handler[11]();

		// clear pending flag (in fact write one)
		EXTI->PR |= (1<<11);
	}
	if(EXTI->PR & (1<<12))
	{
		// call user interrupt handler function
		user_irq_handler[12]();

		// clear pending flag (in fact write one)
		EXTI->PR |= (1<<12);
	}
	if(EXTI->PR & (1<<13))
	{
		// call user interrupt handler function
		user_irq_handler[13]();

		// clear pending flag (in fact write one)
		EXTI->PR |= (1<<13);
	}
	if(EXTI->PR & (1<<14))
	{
		// call user interrupt handler function
		user_irq_handler[14]();

		// clear pending flag (in fact write one)
		EXTI->PR |= (1<<14);
	}
	if(EXTI->PR & (1<<15))
	{
		// call user interrupt handler function
		user_irq_handler[15]();

		// clear pending flag (in fact write one)
		EXTI->PR |= (1<<15);
	}
}

void (*kEXTI_irq_handler[7])(void) =
{
	kEXTI_EXTI0_IRQ_Handler, //0
	kEXTI_EXTI1_IRQ_Handler, //1
	kEXTI_EXTI2_IRQ_Handler, //2
	kEXTI_EXTI3_IRQ_Handler, //3
	kEXTI_EXTI4_IRQ_Handler, //4
	kEXTI_EXTI5_9_IRQ_Handler, //5
	kEXTI_EXTI10_15_IRQ_Handler //6
};


uint8_t kEXTI_irq_channel_num[7] =
{
	6, //0
	7, //1
	8, //2
	9, //3
	10, //4
	23, //5
	40 //6
};



kEXTIHardware& kEXTIHardware::operator = (unsigned int hard_code)
{
	kPrivate::setupPeripheralOutput(hard_code);
	exti_channel = hard_code & 0x0F;

	// get proper EXTI_CRx register
	uint32_t* reg = (uint32_t*)&SYSCFG->EXTICR[exti_channel >> 2];

	uint8_t shift = (exti_channel & 0x03)*4;

	// setup SYSCFG->EXTICR (setup which port to use)
	// clear proper bits
	*reg &= ~(((uint32_t)0x0F) << shift);
	// save new value
	*reg |=  ((hard_code >> 4) & 0x0F) << shift;


	// enable EXTI interrupt handling
	EXTI->IMR |= (1<<exti_channel);

	// enable EXTI falling edge detection if used
	EXTI->FTSR |= (((hard_code >> 27) & 0x01) << exti_channel);
	// enable EXTI rising edge detection if used
	EXTI->RTSR |= (((hard_code >> 28) & 0x01) << exti_channel);

	return (*this);
}
kEXTIHardware& kEXTIHardware::operator , (unsigned int hard_code)
{
	return ((*this) = hard_code);
}

void kEXTI::setIRQHandler(void (*IRQ_Handler)(void),uint8_t preemptionPriority, uint8_t subPriority)
{
	user_irq_handler[hardware.exti_channel] = IRQ_Handler;

	uint8_t index = hardware.exti_channel;
	if(index > 9) index = 6;
	else if(index > 4) index = 5;

	kSystem.setIRQHandler(kEXTI_irq_channel_num[index],kEXTI_irq_handler[index]);
	kSystem.enableInterrupt(kEXTI_irq_channel_num[index],preemptionPriority,subPriority);

}

