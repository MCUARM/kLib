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



#include "kSPIDevice.h"


kSPIDeviceHardware::kSPIDeviceHardware(void)
{

}
kSPIDeviceHardware& kSPIDeviceHardware::operator = (unsigned int hard_code)
{
	// check if it is spi configuration or pin configuration
	if(hard_code & 0x08000000)
	{
		// spi configuration
		
		// decode peripheral address
		this->spi = (SPI_TypeDef*)kPrivate::getPeriheralAndEnableClock(hard_code);
		// make sure spi is stopped and clear first three bits and 7th
		// these bits are responsible for:
		// [0]: CPHA - Data capture on first or second edge
		// [1]: CPOL - Clock polarity CK 0 or 1 when idle
		// [2]: MSTR - Master or slave configuration
		// [7]: LSBFIRST - Frame format is LSB first?
		// [9]: SSM - Software Slave Management enable/disable
		this->spi->CR1 &= ~(0x02C7);
		// set new settings
		
		// setup LSBFIRST
		this->spi->CR1 |= ((hard_code & 0x00000004) << 4)
		// setup [0:2] bits
		this->spi->CR1 |= (hard_code & 0x00000007)

	}else
	{
		// this is only gpio pin configuration
		this->spi = (SPI_TypeDef*)kPrivate::setupPeripheralOutput(hard_code);
	}
	return (*this);
}
kSPIDeviceHardware& kSPIDeviceHardware::operator = (kSPI_SPI_NSS::kSPI_SPI_NSS_PIN nss_pin)
{
	// software NSS pin configuration
	this->NSS = (kPin::kPIN_PIN)nss_pin;
	return (*this);
}
void kSPIDevice::run(unsigned int sck_freq)
{
	// assert
	if(!sck_freq) return;

	// setting up NSS output
	kPort tmpPort(this->hardware.NSS.gpio);
	tmpPort = kPort::on;
	this->hardware.NSS = 1;
	this->hardware.NSS = kPin::out;

	// get baud rate divider
	unsigned int spi_clock = kSystem.getPeripheralClock((unsigned int*)this->hardware.spi);
	spi_clock /= sck_freq;
	unsigned short int i;
	for(i=7;i>0;i--)
	{
		if(spi_clock & 0x00000100) break;
		spi_clock = spi_clock << 1;
	}
	// set SSI SSM high and enable bit
	i+=104;

	// setup baud divider and enable spi
	this->hardware.spi->CR1 &= ~(7<<3);
	this->hardware.spi->CR1 |= (i << 3);

}

void kSPIDevice::write(unsigned short int BytesToWrite,unsigned char * DataBuffer)
{
	unsigned short int i;

	for(i=0;i<BytesToWrite;i++)
	{
	  while (SPI_I2S_GetFlagStatus(this->hardware.spi, SPI_I2S_FLAG_TXE) == RESET);
	  this->hardware.spi->DR = *DataBuffer;
	  DataBuffer++;
	}
	while(SPI_I2S_GetFlagStatus(this->hardware.spi, SPI_I2S_FLAG_BSY) != RESET);
}
void kSPIDevice::write(unsigned char Byte)
{
	  while (SPI_I2S_GetFlagStatus(this->hardware.spi, SPI_I2S_FLAG_TXE) == RESET);
	  this->hardware.spi->DR = Byte;
	  while(SPI_I2S_GetFlagStatus(this->hardware.spi, SPI_I2S_FLAG_BSY) != RESET);
}
void kSPIDevice::read(unsigned short int BytesToRead,unsigned char * ReadDataBuffer)
{
	unsigned short int i;

	for(i=0;i<BytesToRead;i++)
	{
		// Wyslanie 0xFF
		while (SPI_I2S_GetFlagStatus(this->hardware.spi, SPI_I2S_FLAG_TXE) == RESET);
		this->hardware.spi->DR = 0xFF;

		// Odebranie bajtu
		while (SPI_I2S_GetFlagStatus(this->hardware.spi, SPI_I2S_FLAG_RXNE) == RESET);
		*ReadDataBuffer = SPI_I2S_ReceiveData(this->hardware.spi);

		ReadDataBuffer++;
	}
	while(SPI_I2S_GetFlagStatus(this->hardware.spi, SPI_I2S_FLAG_BSY) != RESET);
}
unsigned char kSPIDevice::read(void)
{
	// Wyslanie 0xFF
	while (SPI_I2S_GetFlagStatus(this->hardware.spi, SPI_I2S_FLAG_TXE) == RESET);
	this->hardware.spi->DR = 0xFF;

	// Odebranie bajtu
	while (SPI_I2S_GetFlagStatus(this->hardware.spi, SPI_I2S_FLAG_RXNE) == RESET);
	while(SPI_I2S_GetFlagStatus(this->hardware.spi, SPI_I2S_FLAG_BSY) != RESET);
	return SPI_I2S_ReceiveData(this->hardware.spi);
}
void kSPIDevice::select(void)
{
	this->hardware.NSS = 0;
}
void kSPIDevice::deselect(void)
{
	this->hardware.NSS = 1;
}
