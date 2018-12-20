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



#include "kDMA.h"


kDMAHardware::kDMAHardware()
{

}

void kDMAHardware::clearStatusFlags(void)
{
	// clear all status bits for this stream
	// this is done by writing 1 into LIFCR or LIFCR register
	uint32_t * reg = DMA2->LIFCR + (this->streamNumber & 0x04);
	*reg |= this->interruptClearVal;
}

kDMAHardware& kDMAHardware::operator = (unsigned int hard_code)
{
	// NOTE: Only the DMA2 controller is able to perform memory-to-memory transfers.

	// Decode DMA address
	uint32_t dmaBitPos = (hard_code >> 31);
	this->DMA = DMA1 | (dmaBitPos << 4);

	// Decode DMA Stream
	this->streamNumber = ((hard_code >> 28) & 0x00000007);
	this->DMA_Stream =  this->DMA | (0x10 + 0x18*this->streamNumber);

	// generate value to clear interrupt status register bits for stream
	this->interruptClearVal = 0x3D << ((this->streamNumber & 0x01)*6);
	this->interruptClearVal = this->interruptClearVal << (8*(this->streamNumber & 0x02));


	// make sure DMA2 clock is enabled
	RCC->AHB1ENR |= (1 << (21+dmaBitPos));

	// make sure there is no ongoing transactions on stream
	// clear EN bit
	this->DMA_Stream->CR &= ~(1 << 0);

	// wait until this bit is cleared
	// this may take a while if stream is operating
	while(this->DMA_Stream->CR & (1 << 0));

	// clear all status bits for this stream
	// this is done by writing 1 into LIFCR or LIFCR register
	this->clearStatusFlags();

	// clear unnecessary bits
	hard_code &= ~(0xF << 28);
	DMA_Stream->CR = hard_code;


	return (*this);
}

void kDMA::write(const void*source,const void*destination,uint16_t dataItems_to_transfer)
{
	// make sure there is no ongoing transactions on stream
	// clear EN bit
	this->hardware.DMA_Stream->CR &= ~(1 << 0);

	// wait until this bit is cleared
	// this may take a while if stream is operating
	while(this->hardware.DMA_Stream->CR & (1 << 0));

	// clear all status bits for this stream
	// this is done by writing 1 into LIFCR or LIFCR register
	this->hardware.clearStatusFlags();

	// set source address
	DMA2_Stream0->PAR = (uint32_t)source;

	// set destination address
	DMA2_Stream0->M0AR = (uint32_t)destination;

	// set number of data items to be transfered
	DMA2_Stream0->NDTR = dataItems_to_transfer;


	// start operation
	// set EN bit
	DMA2_Stream0->CR |= 1;

}

