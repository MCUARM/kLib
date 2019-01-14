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
	// this is done by writing 1 into LIFCR or HIFCR register
	uint32_t * reg = (uint32_t*)(((uint32_t)&this->DMA->LIFCR) + ((uint32_t)(this->streamNumber & 0x04)));
	*reg |= this->interruptClearVal;
}

kDMAHardware& kDMAHardware::operator = (unsigned int hard_code)
{
	// NOTE: Only the DMA2 controller is able to perform memory-to-memory transfers.

	// Decode DMA address
	uint32_t dmaBitPos = (hard_code >> 31);
	this->DMA = (DMA_TypeDef*)(((uint32_t)DMA1) | (dmaBitPos << 10));

	// Decode DMA Stream
	this->streamNumber = ((hard_code >> 28) & 0x00000007);
	this->DMA_Stream =  (DMA_Stream_TypeDef*)(((uint32_t)this->DMA) | (0x10 + 0x18*this->streamNumber));

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

	// check if source address is memory address
	if(hard_code & 0x000000C0) this->sourceIsMemory = true; // yes
	else this->sourceIsMemory = false; // no

	return (*this);
}
void kDMA::waitForNewTransactionReady(void)
{
	// wait until EN bit is cleared
	// this may take a while if stream is operating
	while(this->isOperating());

	// clear all status bits for this stream
	// this is done by writing 1 into LIFCR or LIFCR register
	this->hardware.clearStatusFlags();
}
void kDMA::startTransaction(void)
{
	// start operation
	// set EN bit
	this->hardware.DMA_Stream->CR |= 1;
}
void kDMA::setTransferSource(const void *source)
{
	if(hardware.sourceIsMemory)
	{
		// set source address
		this->hardware.DMA_Stream->M0AR = (uint32_t)source;
	}else
	{
		// set source address
		this->hardware.DMA_Stream->PAR = (uint32_t)source;
	}
}
void kDMA::setTransferDestination(const void*destination)
{
	if(hardware.sourceIsMemory)
	{
		// set destination address
		this->hardware.DMA_Stream->PAR = (uint32_t)destination;
	}else
	{
		// set destination address
		this->hardware.DMA_Stream->M0AR = (uint32_t)destination;
	}
}
void kDMA::setPeripheralAddress(Endpoint & periph)
{
	// set peipheral address
	this->hardware.DMA_Stream->PAR = (uint32_t)periph.getAddress();
}

void kDMA::write(const void*source,const void*destination,uint16_t dataItems_to_transfer)
{
	// make sure there is no ongoing transactions on stream
	waitForNewTransactionReady();
	// set transfer source
	setTransferSource(source);
	// set transfer destination
	setTransferDestination(destination);
	// set number of data items to be transfered
	this->hardware.DMA_Stream->NDTR = dataItems_to_transfer;

	// start operation
	startTransaction();
}
void kDMA::write(const void*source,uint16_t dataItems_to_transfer)
{
	// make sure there is no ongoing transactions on stream
	waitForNewTransactionReady();
	// set transfer source
	setTransferSource(source);

	// set number of data items to be transfered
	this->hardware.DMA_Stream->NDTR = dataItems_to_transfer;

	// start operation
	startTransaction();
}
void kDMA::write(uint16_t dataItems_to_transfer)
{
	// make sure there is no ongoing transactions on stream
	waitForNewTransactionReady();
	// set number of data items to be transfered
	this->hardware.DMA_Stream->NDTR = dataItems_to_transfer;
	// start operation
	startTransaction();
}

bool kDMA::isOperating(void)
{
	return (this->hardware.DMA_Stream->CR & (1 << 0));
}
