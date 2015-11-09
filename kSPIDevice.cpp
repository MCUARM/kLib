#include "kSPIDevice.h"

const kSPI1 * kSPI::SPI_1 = (kSPI1 *)SRAM1_BASE;

static volatile unsigned short int k_SPIDevice_unused_var;

void kSPIDeviceHardware::setupMISOPin(void)
{

	//enable clock
	kPort misoPort(this->misoGPIO);
	misoPort = kPort::on;

	//get pin and function settings
	unsigned char pin;
	unsigned long long alternate_function;


	pin = this->misoPin & 0x0F;
	alternate_function = this->misoPin & 0xF0;
	alternate_function = alternate_function >> 4;

	// primary settings to avoid random states on bus
	misoPort[pin] = kPin::PullUp,kPin::in;
	misoPort[pin] = 1;

	// map alternate function
	unsigned long long reg = (unsigned long long)((unsigned long long)this->misoGPIO->AFR[1] << 32) + this->misoGPIO->AFR[0];
	unsigned long long mask = 0x0F;
	mask = mask << (pin << 2);
	mask = ~mask;
	reg &= mask;

	alternate_function = alternate_function << (pin << 2);
	reg |= alternate_function;
	this->misoGPIO->AFR[0] = (unsigned int)reg;
	this->misoGPIO->AFR[1] = (unsigned int)(reg >> 32);

	// use proper pin configuration
	misoPort[pin] = kPin::alternate,kPin::PushPull,kPin::VeryHighSpeed;
}
void kSPIDeviceHardware::setupMOSIPin(void)
{
	//enable clock
	kPort mosiPort(this->mosiGPIO);
	mosiPort = kPort::on;

	//get pin and function settings
	unsigned char pin;
	unsigned long long alternate_function;

	pin = this->mosiPin & 0x0F;
	alternate_function = this->mosiPin & 0xF0;
	alternate_function = alternate_function >> 4;

	// primary settings to avoid random states on bus
	mosiPort[pin] = kPin::PullUp,kPin::in;
	mosiPort[pin] = 1;

	// map alternate function
	unsigned long long reg = (unsigned long long)((unsigned long long)this->mosiGPIO->AFR[1] << 32) + this->mosiGPIO->AFR[0];
	unsigned long long mask = 0x0F;
	mask = mask << (pin << 2);
	mask = ~mask;
	reg &= mask;

	alternate_function = alternate_function << (pin << 2);
	reg |= alternate_function;
	this->mosiGPIO->AFR[0] = (unsigned int)reg;
	this->mosiGPIO->AFR[1] = (unsigned int)(reg >> 32);

	// use proper pin configuration
	mosiPort[pin] = kPin::alternate,kPin::PushPull,kPin::NoPull,kPin::VeryHighSpeed;
}
void kSPIDeviceHardware::setupNSSPin(void)
{
	//enable clock
	kPort nssPort(this->nssGPIO);
	nssPort = kPort::on;

	//get pin and function settings
	unsigned char pin;
	unsigned long long alternate_function;
	pin = this->nssPin & 0x0F;
	alternate_function = this->nssPin & 0xF0;
	alternate_function = alternate_function >> 4;

	// primary settings to avoid random states on bus
	nssPort[pin] = kPin::PullUp,kPin::in;
	nssPort[pin] = 1;

	// map alternate function
	unsigned long long reg = (unsigned long long)((unsigned long long)this->nssGPIO->AFR[1] << 32) + this->nssGPIO->AFR[0];
	unsigned long long mask = 0x0F;
	mask = mask << (pin << 2);
	mask = ~mask;
	reg &= mask;

	alternate_function = alternate_function << (pin << 2);
	reg |= alternate_function;
	this->nssGPIO->AFR[0] = (unsigned int)reg;
	this->nssGPIO->AFR[1] = (unsigned int)(reg >> 32);

	// use proper pin configuration
	nssPort[pin] = kPin::alternate,kPin::PushPull,kPin::NoPull,kPin::VeryHighSpeed;
}
void kSPIDeviceHardware::setupSCKPin(void)
{
	//enable clock
	kPort sckPort(this->sckGPIO);
	sckPort = kPort::on;

	//get pin and function settings
	unsigned char pin;
	unsigned long long alternate_function;
	pin = this->sckPin & 0x0F;
	alternate_function = this->sckPin & 0xF0;
	alternate_function = alternate_function >> 4;

	// primary settings to avoid random states on bus
	sckPort[pin] = kPin::PullUp,kPin::in;
	sckPort[pin] = 1;

	// map alternate function
	unsigned long long reg = (unsigned long long)((unsigned long long)this->sckGPIO->AFR[1] << 32) + this->sckGPIO->AFR[0];
	unsigned long long mask = 0x0F;
	mask = mask << (pin << 2);
	mask = ~mask;
	reg &= mask;

	alternate_function = alternate_function << (pin << 2);
	reg |= alternate_function;
	this->sckGPIO->AFR[0] = (unsigned int)reg;
	this->sckGPIO->AFR[1] = (unsigned int)(reg >> 32);

	// use proper pin configuration
	sckPort[pin] = kPin::alternate,kPin::PushPull,kPin::NoPull,kPin::VeryHighSpeed;
}
kSPIDeviceHardware& kSPIDeviceHardware::operator = (const kSPI1pin & spiHard)
{
	unsigned int reg_address = (unsigned int)&spiHard;
	this->spi = SPI1;
	unsigned int shift = reg_address - (unsigned int)kSPI::SPI_1;

	// enable SPI1 clock
	RCC->APB2ENR |= (1 << 12);

	switch(shift)
	{
		case 0: // MISO PORTA6

			this->misoGPIO = GPIOA;
			this->misoPin = 6 | (5 << 4);
			this->setupMISOPin();
		break;
		case 1: // MISO PORTB4
			this->misoGPIO = GPIOB;
			this->misoPin = 4 | (5 << 4);
			this->setupMISOPin();
		break;
		case 2:	// MOSI PORTA7
			this->mosiGPIO = GPIOA;
			this->mosiPin = 7 | (5 << 4);
			this->setupMOSIPin();
		break;
		case 3: // MOSI PORTB5
			this->mosiGPIO = GPIOB;
			this->mosiPin = 5 | (5 << 4);
			this->setupMOSIPin();
		break;
		case 4: // NSS PORTA4
			this->nssGPIO = GPIOA;
			this->nssPin = 4 | (5 << 4);
			this->setupNSSPin();
		break;
		case 5: // NSS PORTA15
			this->nssGPIO = GPIOA;
			this->nssPin = 15 | (5 << 4);
			this->setupNSSPin();
		break;
		case 6: // SCK PORTA5
			this->sckGPIO = GPIOA;
			this->sckPin = 5 | (5 << 4);
			this->setupSCKPin();
		break;
		case 7: // SCK PORTB3
			this->sckGPIO = GPIOB;
			this->sckPin = 3 | (5 << 4);
			this->setupSCKPin();
		break;
	}

	return *this;
}
kSPIDeviceHardware& operator , (kSPIDeviceHardware& spiDev,const kSPI1pin & spiHard)
{
	unsigned int reg_address = (unsigned int)&spiHard;
	spiDev.spi = SPI1;
	unsigned int shift = reg_address - (unsigned int)kSPI::SPI_1;

	// enable SPI1 clock
	RCC->APB2ENR |= (1 << 12);

	switch(shift)
	{
		case 0: // MISO PORTA6

			spiDev.misoGPIO = GPIOA;
			spiDev.misoPin = 6 | (5 << 4);
			spiDev.setupMISOPin();
		break;
		case 1: // MISO PORTB4
			spiDev.misoGPIO = GPIOB;
			spiDev.misoPin = 4 | (5 << 4);
			spiDev.setupMISOPin();
		break;
		case 2:	// MOSI PORTA7
			spiDev.mosiGPIO = GPIOA;
			spiDev.mosiPin = 7 | (5 << 4);
			spiDev.setupMOSIPin();
		break;
		case 3: // MOSI PORTB5
			spiDev.mosiGPIO = GPIOB;
			spiDev.mosiPin = 5 | (5 << 4);
			spiDev.setupMOSIPin();
		break;
		case 4: // NSS PORTA4
			spiDev.nssGPIO = GPIOA;
			spiDev.nssPin = 4 | (5 << 4);
			spiDev.setupNSSPin();
		break;
		case 5: // NSS PORTA15
			spiDev.nssGPIO = GPIOA;
			spiDev.nssPin = 15 | (5 << 4);
			spiDev.setupNSSPin();
		break;
		case 6: // SCK PORTA5
			spiDev.sckGPIO = GPIOA;
			spiDev.sckPin = 5 | (5 << 4);
			spiDev.setupSCKPin();
		break;
		case 7: // SCK PORTB3
			spiDev.sckGPIO = GPIOB;
			spiDev.sckPin = 3 | (5 << 4);
			spiDev.setupSCKPin();
		break;
	}

	return spiDev;
}


kSPIDeviceHardware& kSPIDeviceHardware::operator = (const kSPI::kSPIMode mode)
{
	if(mode == kSPI::Master)
	{
		// master mode
		this->spi->CR1 |= (1 << 2);
	}else
	{
		// slave mode
		this->spi->CR1 &= ~(unsigned short)(1 << 2);
	}
	return * this;
}
kSPIDeviceHardware& operator , (kSPIDeviceHardware& spiDev,const kSPI::kSPIMode mode)
{
	if(mode == kSPI::Master)
	{
		// master mode
		spiDev.spi->CR1 |= (1 << 2);
	}else
	{
		// slave mode
		spiDev.spi->CR1 &= ~(unsigned short)(1 << 2);
	}
	return spiDev;
}
kSPIDeviceHardware& kSPIDeviceHardware::operator = (const kSPI::kSPI_Baud baud)
{

	unsigned short reg = this->spi->CR1;
	//assert parameter
	unsigned short b = baud;
	b &= 0x0007;
	b = b << 3;

	// clear baud rate bits
	reg &= ~(0x0038);

	// insert new baud bits
	reg |= b;

	// write to register
	this->spi->CR1 = reg;

	return * this;
}
kSPIDeviceHardware& operator , (kSPIDeviceHardware& spiDev,const kSPI::kSPI_Baud baud)
{
	unsigned short reg = spiDev.spi->CR1;
	//assert parameter
	unsigned short b = baud;
	b &= 0x0007;
	b = b << 3;

	// clear baud rate bits
	reg &= ~(0x0038);

	// insert new baud bits
	reg |= b;

	// write to register
	spiDev.spi->CR1 = reg;

	return spiDev;
}
kSPIDeviceHardware& kSPIDeviceHardware::operator = (const kSPI::kSPI_CPHA cpha)
{
	unsigned short reg = this->spi->CR1;
	//assert parameter
	unsigned short c = cpha;
	c &= 0x0001;

	// claer CPHA bit
	reg &= ~(0x0001);
	// add new CPHA value
	reg |= c;

	//save register
	this->spi->CR1 = reg;

	return * this;
}
kSPIDeviceHardware& operator , (kSPIDeviceHardware& spiDev,const kSPI::kSPI_CPHA cpha)
{
	unsigned short reg = spiDev.spi->CR1;
	//assert parameter
	unsigned short c = cpha;
	c &= 0x0001;

	// clear CPHA bit
	reg &= ~(0x0001);
	// add new CPHA value
	reg |= c;

	//save register
	spiDev.spi->CR1 = reg;

	return spiDev;
}

kSPIDeviceHardware& kSPIDeviceHardware::operator = (const kSPI::kSPI_CPOL cpol)
{
	unsigned short reg = this->spi->CR1;
	//assert parameter
	unsigned short c = cpol;
	c &= 0x0001;

	this->NSS_idleState = (unsigned char)c;

	c = c<<1;

	// claer CPOL bit
	reg &= ~(0x0002);
	// add new CPOL value
	reg |= c;

	//save register
	this->spi->CR1 = reg;

	return * this;
}
kSPIDeviceHardware& operator , (kSPIDeviceHardware& spiDev,const kSPI::kSPI_CPOL cpol)
{
	unsigned short reg = spiDev.spi->CR1;
	//assert parameter
	unsigned short c = cpol;
	c &= 0x0001;
	c = c<<1;

	// clear CPOL bit
	reg &= ~(0x0002);
	// add new CPOL value
	reg |= c;

	//save register
	spiDev.spi->CR1 = reg;

	return spiDev;
}
kSPIDeviceHardware& kSPIDeviceHardware::operator = (const kSPI::kSPI_NSS_Control nss_control)
{
	//assert parameter
	unsigned char n = nss_control;
	n &= 0x01;

	if(n)
	{
		this->spi->CR1 |= 0x00000300;
	}else
	{
		this->spi->CR1 &= ~0x00000300;
	}

	return * this;
}
kSPIDeviceHardware& operator , (kSPIDeviceHardware& spiDev,const kSPI::kSPI_NSS_Control nss_control)
{
	//assert parameter
	unsigned char n = nss_control;
	n &= 0x01;

	if(n)
	{
		spiDev.spi->CR1 |= 0x00000300;
	}else
	{
		spiDev.spi->CR1 &= ~0x00000300;
	}

	return spiDev;
}
kSPIDeviceHardware& kSPIDeviceHardware::operator = (const kSPI::kSPI_TransferBitFirst endian)
{
	unsigned short reg = this->spi->CR1;
	//assert parameter
	unsigned short e = endian;
	e &= 0x0001;
	e = e<<7;

	// claer SSM bit
	reg &= ~(1<<7);
	// add new SSM value
	reg |= e;

	//save register
	this->spi->CR1 = reg;

	return * this;
}
kSPIDeviceHardware& operator , (kSPIDeviceHardware& spiDev,const kSPI::kSPI_TransferBitFirst endian)
{
	unsigned short reg = spiDev.spi->CR1;
	//assert parameter
	unsigned short e = endian;
	e &= 0x0001;
	e = e<<7;

	// claer SSM bit
	reg &= ~(1<<7);
	// add new SSM value
	reg |= e;

	//save register
	spiDev.spi->CR1 = reg;

	return spiDev;
}
kSPIDeviceHardware& kSPIDeviceHardware::operator = (const kSPI::kSPI_power pow)
{
	unsigned short reg = this->spi->CR1;
	//assert parameter
	unsigned short p = pow;
	p &= 0x0001;
	p = p<<6;

	// clear SPE bit
	reg &= ~(1<<6);
	// add new SPE value
	reg |= p;

	//save register
	this->spi->CR1 = reg;

	return * this;
}
kSPIDeviceHardware& operator , (kSPIDeviceHardware& spiDev,const kSPI::kSPI_power pow)
{
	unsigned short reg = spiDev.spi->CR1;
	//assert parameter
	unsigned short p = pow;
	p &= 0x0001;
	p = p<<6;


	// set SSOE
	spiDev.spi->CR2 &= ~(1<<2);

	// clear SPE bit
	reg &= ~(1<<6);
	// add new SPE value
	reg |= p;

	//save register
	spiDev.spi->CR1 = reg;


	return spiDev;
}
void kSPIDevice::write(unsigned short int BytesToWrite,unsigned char * DataBuffer)
{
	unsigned short int i;

	for(i=0;i<BytesToWrite;i++)
	{
	  while (SPI_I2S_GetFlagStatus(this->hardware.spi, SPI_I2S_FLAG_TXE) == RESET);
	  SPI_I2S_SendData(this->hardware.spi, *DataBuffer);
	  DataBuffer++;
	}
	while(SPI_I2S_GetFlagStatus(this->hardware.spi, SPI_I2S_FLAG_BSY) != RESET);
}
void kSPIDevice::write(unsigned char Byte)
{
	  k_SPIDevice_unused_var = this->hardware.spi->DR;
	  while (SPI_I2S_GetFlagStatus(this->hardware.spi, SPI_I2S_FLAG_TXE) == RESET);
	  SPI_I2S_SendData(this->hardware.spi, Byte);
	  while(SPI_I2S_GetFlagStatus(this->hardware.spi, SPI_I2S_FLAG_BSY) != RESET);
}
void kSPIDevice::read(unsigned short int BytesToRead,unsigned char * ReadDataBuffer)
{
	unsigned short int i;

	for(i=0;i<BytesToRead;i++)
	{
		// Wyslanie 0xFF
		while (SPI_I2S_GetFlagStatus(this->hardware.spi, SPI_I2S_FLAG_TXE) == RESET);
		SPI_I2S_SendData(this->hardware.spi, 0xFF);

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
	SPI_I2S_SendData(this->hardware.spi, 0xFF);

	// Odebranie bajtu
	while (SPI_I2S_GetFlagStatus(this->hardware.spi, SPI_I2S_FLAG_RXNE) == RESET);
	while(SPI_I2S_GetFlagStatus(this->hardware.spi, SPI_I2S_FLAG_BSY) != RESET);
	return SPI_I2S_ReceiveData(this->hardware.spi);
}
void kSPIDevice::select(void)
{
	// check if soft mode enabled
	if (this->hardware.spi->CR1 & (1<<9))
	{
		this->hardware.nssGPIO->ODR &= ~(unsigned int)(1 << this->hardware.nssPin);
	}
}
void kSPIDevice::deselect(void)
{
	// check if soft mode enabled
	if (this->hardware.spi->CR1 & (1<<9))
	{
		this->hardware.nssGPIO->ODR |= (unsigned int)(1 << this->hardware.nssPin);
	}
}
