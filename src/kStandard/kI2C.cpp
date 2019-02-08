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



#include "kI2C.h"



void kI2C_DefaultHandler_addressMatchedEvent()
{

}
void kI2C_DefaultHandler_byteReceivedEvent(uint8_t byte)
{
	K_UNUSED(byte);
}
void kI2C_DefaultHandler_stopBitEvent()
{

}
uint8_t kI2C_DefaultHandler_writeRequestEvent()
{
	return 0x00;
}


kI2C_IQR_data_t I2C1_irq_data = {	kI2C_DefaultHandler_addressMatchedEvent,
									kI2C_DefaultHandler_byteReceivedEvent,
									kI2C_DefaultHandler_writeRequestEvent,
									kI2C_DefaultHandler_stopBitEvent,
									0};
void I2C1_irq()
{
	I2C1_irq_data.i2c->hardware.SR1 = I2C1->SR1;
	I2C1_irq_data.i2c->hardware.SR2 = I2C1->SR2;

	if(I2C1_irq_data.i2c->hardware.SR1 & (1<<4))
	{
		// Stop bit detected
		I2C1_irq_data.i2c->hardware.i2c->CR1 |= (1<<0);
		I2C1_irq_data.stopBitEventHandler();
	}
	if(I2C1_irq_data.i2c->hardware.SR1 & (1<<1))
	{
		// Address matched event
		I2C1_irq_data.addressMatchedEventHandler();
	}
	if(I2C1_irq_data.i2c->hardware.SR1 & (1<<6))
	{
		// RxNE event
		I2C1_irq_data.byteReceivedEventHandler(I2C1->DR);
	}
	if(I2C1_irq_data.i2c->hardware.SR1 & (1<<7))
	{
		// TxE event
		I2C1->DR = I2C1_irq_data.writeRequestEventHandler();
	}

}




kI2C::kI2C(void)
{

}
kI2CHardware& kI2CHardware::operator = (uint32_t hard_code)
{
	// setup output pin
	this->i2c = (I2C_TypeDef*)kPrivate::setupPeripheralOutput(hard_code);
	return (*this);
}

kI2CHardware& kI2CHardware::operator , (uint32_t hard_code)
{
	return ((*this) = hard_code);
}

void kI2C::reset(void)
{
	uint16_t CR1 = this->hardware.i2c->CR1;
	uint16_t CR2 = this->hardware.i2c->CR2;
	// disable PE bit
	CR1 &= ~(1<<0);

	// reset
	this->hardware.i2c->CR1 |= (1<<15);
	// release reset
	this->hardware.i2c->CR2 &= ~(1<<15);

	// restore CR1 and CR2 settings. Please note that I2C will be stopped after calling reset function
	// Also I2C clock configuration must be calculated again and all other registers than CR1 and CR2
	this->hardware.i2c->CR1 = CR1;
	this->hardware.i2c->CR2 = CR2;
}


void kI2C::run(unsigned int clock_speed)
{

	uint16_t tmpreg = 0, freqrange = 0;
	uint16_t result = 0x04;
	uint32_t pclk1 = 8000000;

	  // reset
	this->reset();


	/*---------------------------- I2Cx CR2 Configuration ------------------------*/
	  /* Get the I2Cx CR2 value */
	  tmpreg = this->hardware.i2c->CR2;
	  /* Clear frequency FREQ[5:0] bits */
	  tmpreg &= (uint16_t)~((uint16_t)0x003F);
	  /* Get pclk1 frequency value */
	  pclk1 = kSystem.APB1_CLK();
	  /* Set frequency bits depending on pclk1 value */
	  freqrange = (uint16_t)(pclk1 / 1000000);
	  tmpreg |= freqrange;
	  /* Write to I2Cx CR2 */
	  this->hardware.i2c->CR2 = tmpreg;

	/*---------------------------- I2Cx CCR Configuration ------------------------*/
	  /* Disable the selected I2C peripheral to configure TRISE */
	  this->hardware.i2c->CR1 &= (uint16_t)~((uint16_t)0x0001);
	  /* Reset tmpreg value */
	  /* Clear F/S, DUTY and CCR[11:0] bits */
	  tmpreg = 0;

	  /* Configure speed in standard mode */
	  if (clock_speed <= 100000)
	  {
	    /* Standard mode speed calculate */
	    result = (uint16_t)(pclk1 / (clock_speed << 1));
	    /* Test if CCR value is under 0x4*/
	    if (result < 0x04)
	    {
	      /* Set minimum allowed value */
	      result = 0x04;
	    }
	    /* Set speed value for standard mode */
	    tmpreg |= result;
	    /* Set Maximum Rise Time for standard mode */
	    this->hardware.i2c->TRISE = freqrange + 1;
	  }
	  /* Configure speed in fast mode */
	  /* To use the I2C at 400 KHz (in fast mode), the PCLK1 frequency (I2C peripheral
	     input clock) must be a multiple of 10 MHz */
	  else /*(clock_speed <= 400000)*/
	  {
	      /* Fast mode speed calculate: Tlow/Thigh = 2 */
	      result = (uint16_t)(pclk1 / (clock_speed * 3));


	    /* Test if CCR value is under 0x1*/
	    if ((result & 0x0FFF) == 0)
	    {
	      /* Set minimum allowed value */
	      result |= (uint16_t)0x0001;
	    }
	    /* Set speed value and set F/S bit for fast mode */
	    tmpreg |= (uint16_t)(result | 0x8000);
	    /* Set Maximum Rise Time for fast mode */
	    this->hardware.i2c->TRISE = (uint16_t)(((freqrange * (uint16_t)300) / (uint16_t)1000) + (uint16_t)1);
	  }

	  /* Write to I2Cx CCR */
	  this->hardware.i2c->CCR = tmpreg;


	/*---------------------------- I2Cx OAR1 Configuration -----------------------*/
	  /* Set I2Cx Own Address1 and acknowledged address */
	  this->hardware.i2c->OAR1 = this->address;


	/*---------------------------- I2Cx CR1 Configuration ------------------------*/

	  /* Enable the selected I2C peripheral */
	  // I2C mode, disable ACK
	  this->hardware.i2c->CR1 = (1<<0);


}
void kI2C::sendStart(void)
{
	this->enableAcknowledge(true);


	// send start condition
	this->hardware.i2c->CR1 |= (1<<8);
	// wait while start condition not send (check SB bit in SR1 - start bit sent)
	while(!(this->hardware.i2c->SR1 &= (1<<0)));


}
void kI2C::sendAddress(transfer_direction dir)
{
	if(dir == kI2C::Transmitting)
	{
		// send device write address
		this->hardware.i2c->DR = (this->address & 0xFE);
	}else
	{
		// send device read address
		this->hardware.i2c->DR = (this->address | 0x01);
	}
	// wait for addressing match (read sequence of SR1 and SR2 register and check if ADDR bit in SR1 is set)


	// wait until address match
	do
	{
		// read SR1 register followed by SR2
		this->hardware.SR1 = this->hardware.i2c->SR1;
		this->hardware.SR2 = this->hardware.i2c->SR2;
	}while(!(this->hardware.SR1 & (1<<1)));

	// check if peripheral is in Master mode
	while(!(this->hardware.SR2 & (1<<0)));

}
void kI2C::sendData(uint8_t data)
{
	// send data
	this->hardware.i2c->DR = data;
	// wait while data not send
	while(!(this->hardware.i2c->SR1 & (1<<7)));
}
void kI2C::sendStop(void)
{
	// send stop condition
	this->hardware.i2c->CR1 |= (1<<9);
}
void kI2C::write(uint8_t StartingRegisterAddress,void * transmit_buffer,uint8_t BytesToWrite)
{
	uint8_t i;
	uint8_t * tx_buffer = (uint8_t*)transmit_buffer;

	// send start condition
	sendStart();
	// send device write address
	sendAddress(kI2C::Transmitting);
	// send internal device register address
	sendData(StartingRegisterAddress);
	// send data
	for(i=0;i<BytesToWrite;i++)
	{
		sendData(*tx_buffer);
		tx_buffer++;
	}

	// send stop condition
	sendStop();
}

void kI2C::write(const void * data)
{
	uint8_t * tx_buffer = (uint8_t *)data;
	// send start condition
	sendStart();
	// send device write address
	sendAddress(kI2C::Transmitting);

	while(*tx_buffer)
	{
		sendData(*tx_buffer);
		tx_buffer++;
	}

	// send stop condition
	sendStop();
}
void kI2C::write(const void * data, uint32_t bytes)
{
	uint8_t * tx_buffer = (uint8_t *)data;
	// send start condition
	sendStart();
	// send device write address
	sendAddress(kI2C::Transmitting);

	for(uint32_t i=0;i<bytes;i++)
	{
		sendData(*tx_buffer);
		tx_buffer++;
	}

	// send stop condition
	sendStop();
}

void kI2C::write(uint8_t RegisterAddress,uint8_t value)
{
	write(RegisterAddress,&value,1);
}
void kI2C::enableAcknowledge(bool state)
{
	if(state) this->hardware.i2c->CR1 |= (1<<10);
	else this->hardware.i2c->CR1 &= ~(1<<10);
}
uint8_t kI2C::readData(void)
{
	// wait for byte reception
	while(!(this->hardware.i2c->SR1 & (1<<6)));
	// return byte
	return ((uint8_t)this->hardware.i2c->DR);
}


void kI2C::read(void * receive_buffer, uint32_t BytesToRead)
{
	uint8_t * rx_buffer = (uint8_t*)receive_buffer;

	if(BytesToRead > 1)
	{
		// there are more than 1 byte to receive

		// ACK is already set in sendStart() function
		//enableAcknowledge(true);

		// send repeated start
		sendStart();
		// send device read address
		sendAddress(kI2C::Receiving);

		// read bytes one by one
		for(uint32_t i=0,loop_end = BytesToRead-2;i<loop_end;i++)
		{
			*rx_buffer = readData();
			rx_buffer++;
		}

		// wait for byte reception
		while(!(this->hardware.i2c->SR1 & (1<<6)));
		// disable acknowledge
		enableAcknowledge(false);
		// send stop condition
		sendStop();

		// receive last two bytes
		// read second last byte
		*rx_buffer = readData();
		rx_buffer++;

		// read last byte
		*rx_buffer = readData();

	}else
	{
		// one byte reception
		// acknowledge bit must be cleared before address send

		// send repeated start
		sendStart();

		// set acknowledge false
		enableAcknowledge(false);

		// send device read address
		sendAddress(kI2C::Receiving);

		// read one byte
		*rx_buffer = readData();

		// send stop condition
		sendStop();
	}
}

void kI2C::read(uint8_t StartingRegisterAddress, void * recieve_buffer,uint8_t BytesToRead)
{

	// send start condition
	sendStart();
	// send device write address
	sendAddress(kI2C::Transmitting);
	// send internal device register address
	sendData(StartingRegisterAddress);
	// read bytes and close communication
	read(recieve_buffer,BytesToRead);

}
unsigned char kI2C::read(uint8_t RegisterAddress)
{
	uint8_t data;
	read(RegisterAddress,&data,1);
	return data;
}
void kI2C::writeWord(uint16_t word)
{
	write(&word,2);
}
void kI2C::writeByte(uint8_t byte)
{
	write(&byte,1);
}
uint16_t kI2C::readWord(void)
{
	uint16_t res;
	read(&res,2);
	return res;
}


void kI2C::enableInterrupt(unsigned char preemptionPriority, unsigned char subPriority)
{
	// enable event and buffer interrupt
	this->hardware.i2c->CR2 |= ((1024 | 512) & 0x0700);


	I2C1_irq_data.i2c = this;

	// enable interrupt handling in NVIC
	kSystem.setIRQHandler(kSystem.IRQ->_I2C1_EV,I2C1_irq);
	kSystem.enableInterrupt(kSystem.IRQ->_I2C1_EV,preemptionPriority,subPriority);
}
void kI2C::setAddressMatchedEventHandler(void (*addressMatchedEventHandler)(void))
{
	I2C1_irq_data.addressMatchedEventHandler = addressMatchedEventHandler;
}
void kI2C::setByteReceivedEventHandler(void (*byteReceivedEventHandler)(uint8_t))
{
	I2C1_irq_data.byteReceivedEventHandler = byteReceivedEventHandler;
}
void kI2C::setStopBitEventHandler(void (*stopBitEventHandler)(void))
{
	I2C1_irq_data.stopBitEventHandler = stopBitEventHandler;
}
void kI2C::setWriteRequestEventHandler(uint8_t (*writeRequestEventHandler)(void))
{
	I2C1_irq_data.writeRequestEventHandler = writeRequestEventHandler;
}

bool kI2C::isReceiver(void)
{
	// Check if TRA bit (Transmitter) is set or cleared in SR2 register
	return (this->hardware.i2c->SR2 & (1<<2)) ? false : true;
}
bool kI2C::isTransmitter(void)
{
	// Check if TRA bit (Transmitter) is set or cleared in SR2 register
	return (this->hardware.i2c->SR2 & (1<<2)) ? true : false;
}
