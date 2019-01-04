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

void kI2C::run(unsigned int clock_speed)
{

	uint16_t tmpreg = 0, freqrange = 0;
	uint16_t result = 0x04;
	uint32_t pclk1 = 8000000;

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
	  this->hardware.i2c->CR1 = ((uint16_t)0x0001);



}
void kI2C::reset(void)
{
	this->hardware.i2c->CR1 |= (1<<15);
}
void kI2C::sendStart(void)
{
	// send start condition
	this->hardware.i2c->CR1 |= (1<<8);
	// wait while start condition not send (check SB bit in SR1 - start bit sent)
	while(this->hardware.i2c->SR1 &= (1<<0));
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
	while(!(this->hardware.i2c->SR1 & (1<<1)));
	// check if peripheral is in Master mode
	while(!(this->hardware.i2c->SR2 & (1<<0)));

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

	for(i=0;i<BytesToWrite;i++)
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
	return ((uint8_t)this->hardware.i2c->DR);
}
void kI2C::read(uint8_t StartingRegisterAddress, void * recieve_buffer,uint8_t BytesToRead)
{
	uint8_t i,loop_end;
	uint8_t * rx_buffer = (uint8_t*)recieve_buffer;

	// send start condition
	sendStart();
	// send device write address
	sendAddress(kI2C::Transmitting);
	// send internal device register address
	sendData(StartingRegisterAddress);

	if(BytesToRead > 1)
	{
		enableAcknowledge(true);

		// send repeated start
		sendStart();
		// send device read address
		sendAddress(kI2C::Receiving);

		for(i=0,loop_end = BytesToRead-2;i<loop_end;i++)
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
		*rx_buffer = readData();
		rx_buffer++;

		*rx_buffer = readData();
		rx_buffer++;

	}else
	{
		// send repeated start
		sendStart();

		enableAcknowledge(false);

		// send device read address
		sendAddress(kI2C::Receiving);

		for(i=0,loop_end = BytesToRead-2;i<loop_end;i++)
		{
			*rx_buffer = readData();
			rx_buffer++;
		}

		// send stop condition
		sendStop();

	}

}
unsigned char kI2C::read(uint8_t RegisterAddress)
{
	// there is some problem with internal shift buffer
	// that do not allow receiving single byte
	uint8_t data;
	this->read(RegisterAddress,&data,1);
	return data;
}
