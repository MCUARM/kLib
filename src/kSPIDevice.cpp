#include "kSPIDevice.h"


kSPIDeviceHardware::kSPIDeviceHardware(void)
{

}
kSPIDeviceHardware& kSPIDeviceHardware::operator = (unsigned int hard_code)
{
	if(hard_code & 0x08000000)
	{
		this->spi = (SPI_TypeDef*)kPrivate::getPeriheralAndEnableClock(hard_code);
		// make sure spi is stopped and clear first three bits and 7th
		this->spi->CR1 &= ~(0x00C7);
		// set new settings
		if(hard_code & 0x80000000) this->spi->CR1 |= (1<<7);
		this->spi->CR1 |= ((hard_code & 0x70000000) >> 28);



	}else
	{
		this->spi = (SPI_TypeDef*)kPrivate::setupPeripheralOutput(hard_code);
	}
	return (*this);
}
kSPIDeviceHardware& kSPIDeviceHardware::operator = (kSPI_SPI_NSS::kSPI_SPI_NSS_PIN nss_pin)
{
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
