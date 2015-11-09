#include "kSerial.h"


const char* kSerial::endl = "\r\n";
const kSerialUSART1 * kSerial::usart1 = (kSerialUSART1 *)SRAM1_BASE;
const kSerialUSART2 * kSerial::usart2 = (kSerialUSART2 *)SRAM1_BASE;
const kSerialUSART3 * kSerial::usart3 = (kSerialUSART3 *)SRAM1_BASE;


void kSerialHardware::setupRxPin(void)
{
	//enable clock
	kPort RxPort(this->rxGPIO);
	RxPort = kPort::on;
	unsigned char pin;
	unsigned long long alternate_function;
	pin = this->rxPin & 0x0F;
	alternate_function = this->rxPin & 0xF0;
	alternate_function = alternate_function >> 4;

	RxPort[pin] = kPin::alternate,kPin::PushPull,kPin::NoPull,kPin::VeryHighSpeed;

	// map alternate function
	unsigned long long reg = (unsigned long long)((unsigned long long)this->rxGPIO->AFR[1] << 32) + this->rxGPIO->AFR[0];
	unsigned long long mask = 0x0F;
	mask = mask << (pin << 2);
	mask = ~mask;
	reg &= mask;

	alternate_function = alternate_function << (pin << 2);
	reg |= alternate_function;
	this->rxGPIO->AFR[0] = (unsigned int)reg;
	this->rxGPIO->AFR[1] = (unsigned int)(reg >> 32);


}
void kSerialHardware::setupTxPin(void)
{
	//enable clock
	kPort TxPort(this->txGPIO);
	TxPort = kPort::on;
	unsigned char pin;
	unsigned long long alternate_function;
	pin = this->txPin & 0x0F;
	alternate_function = this->txPin & 0xF0;
	alternate_function = alternate_function >> 4;

	TxPort[pin] = kPin::alternate,kPin::PushPull,kPin::NoPull,kPin::VeryHighSpeed;

	// map alternate function
	unsigned long long reg = (unsigned long long)((unsigned long long)this->txGPIO->AFR[1] << 32) + this->txGPIO->AFR[0];
	unsigned long long mask = 0x0F;
	mask = mask << (pin << 2);
	mask = ~mask;
	reg &= mask;

	alternate_function = alternate_function << (pin << 2);
	reg |= alternate_function;
	this->txGPIO->AFR[0] = (unsigned int)reg;
	this->txGPIO->AFR[1] = (unsigned int)(reg >> 32);
}

kSerialHardware& kSerialHardware::operator = (const kSerialUSART1Pin & usartHard)
{
	unsigned int reg_address = (unsigned int)&usartHard;
	this->usart = USART1;
	unsigned int shift = reg_address - (unsigned int)kSerial::usart1;

	// enable USART1 clock
	RCC->APB2ENR |= 0x10;
	// force one stop bit
	USART1->CR2 &= 0xCFFF;



	switch(shift)
	{
		case 0: // RX PORTA10

			// enable receiver
			USART1->CR1 |= 0x04;


			this->rxGPIO = GPIOA;
			this->rxPin = 10 | (7 << 4);
			this->setupRxPin();
		break;
		case 1: // RX PORTB7

			// enable receiver
			USART1->CR1 |= 0x04;

			this->rxGPIO = GPIOB;
			this->rxPin = 7 | (7 << 4);
			this->setupRxPin();
		break;
		case 2:	// TX PORTA9

			// enable transmitter
			USART1->CR1 |= 0x08;

			this->txGPIO = GPIOA;
			this->txPin = 9 | (7 << 4);
			this->setupTxPin();
		break;
		case 3: // TX PORTB6

			// enable transmitter
			USART1->CR1 |= 0x08;

			this->txGPIO = GPIOB;
			this->txPin = 6 | (7 << 4);
			this->setupTxPin();
		break;
	}
	return *this;
}
kSerialHardware& kSerialHardware::operator = (const kSerialUSART2Pin & usartHard)
{
	unsigned int reg_address = (unsigned int)&usartHard;
	this->usart = USART2;
	unsigned int shift = reg_address - (unsigned int)kSerial::usart2;

	// enable USART2 clock
	RCC->APB1ENR |= (1 << 17);
	// force one stop bit
	USART2->CR2 &= 0xCFFF;



	switch(shift)
	{
		case 0: // RX PORTA3

			// enable receiver
			USART2->CR1 |= 0x04;


			this->rxGPIO = GPIOA;
			this->rxPin = 3 | (7 << 4);
			this->setupRxPin();
		break;
		case 1: // RX PORTD6

			// enable receiver
			USART2->CR1 |= 0x04;

			this->rxGPIO = GPIOD;
			this->rxPin = 6 | (7 << 4);
			this->setupRxPin();
		break;
		case 2:	// TX PORTA2

			// enable transmitter
			USART2->CR1 |= 0x08;

			this->txGPIO = GPIOA;
			this->txPin = 2 | (7 << 4);
			this->setupTxPin();
		break;
		case 3: // TX PORTD5

			// enable transmitter
			USART2->CR1 |= 0x08;

			this->txGPIO = GPIOD;
			this->txPin = 5 | (7 << 4);
			this->setupTxPin();
		break;
	}
	return *this;
}
kSerialHardware& kSerialHardware::operator = (const kSerialUSART3Pin & usartHard)
{
	unsigned int reg_address = (unsigned int)&usartHard;
	this->usart = USART3;
	unsigned int shift = reg_address - (unsigned int)kSerial::usart3;

	// enable USART3 clock
	RCC->APB1ENR |= (1<<18);
	// force one stop bit
	USART3->CR2 &= 0xCFFF;



	switch(shift)
	{
		case 0: // RX PORTB11

			// enable receiver
			USART3->CR1 |= 0x04;


			this->rxGPIO = GPIOB;
			this->rxPin = 11 | (7 << 4);
			this->setupRxPin();
		break;
		case 1: // RX PORTC11

			// enable receiver
			USART3->CR1 |= 0x04;

			this->rxGPIO = GPIOC;
			this->rxPin = 11 | (7 << 4);
			this->setupRxPin();
		break;
		case 2:	// RX PORTD9

			// enable receiver
			USART3->CR1 |= 0x04;

			this->txGPIO = GPIOD;
			this->txPin = 9 | (7 << 4);
			this->setupTxPin();
		break;
		case 3: // TX PORTB10

			// enable transmitter
			USART3->CR1 |= 0x08;

			this->txGPIO = GPIOB;
			this->txPin = 10 | (7 << 4);
			this->setupTxPin();
		break;
		case 4: // TX PORTC10

			// enable transmitter
			USART3->CR1 |= 0x08;

			this->txGPIO = GPIOC;
			this->txPin = 10 | (7 << 4);
			this->setupTxPin();
		break;
		case 5: // TX PORTD8

			// enable transmitter
			USART3->CR1 |= 0x08;

			this->txGPIO = GPIOD;
			this->txPin = 8 | (7 << 4);
			this->setupTxPin();
		break;
	}
	return *this;
}



kSerialHardware& kSerialHardware::operator , (const kSerialUSART1Pin & usartHard)
{
	return (*this = usartHard);
}
kSerialHardware& kSerialHardware::operator , (const kSerialUSART2Pin & usartHard)
{
	return (*this = usartHard);
}
kSerialHardware& kSerialHardware::operator , (const kSerialUSART3Pin & usartHard)
{
	return (*this = usartHard);
}

void kSerial::baud(unsigned int BaudRate)
{
	  uint32_t tmpreg = 0x00, apbclock = 0x00;
	  uint32_t integerdivider = 0x00;
	  uint32_t fractionaldivider = 0x00;
	  RCC_ClocksTypeDef RCC_ClocksStatus;

	/*---------------------------- USART BRR Configuration -----------------------*/
	  /* Configure the USART Baud Rate */

	  //usart off
	  this->hardware.usart->CR1 &= 0xDFFF;

	  RCC_GetClocksFreq(&RCC_ClocksStatus);

	  if ((this->hardware.usart == USART1) || (this->hardware.usart == USART6))
	  {
	    apbclock = RCC_ClocksStatus.PCLK2_Frequency;
	  }
	  else
	  {
	    apbclock = RCC_ClocksStatus.PCLK1_Frequency;
	  }

	  /* Determine the integer part */
	  if ((this->hardware.usart->CR1 & USART_CR1_OVER8) != 0)
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
	  if ((this->hardware.usart->CR1 & USART_CR1_OVER8) != 0)
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
const kSerial& operator <<(const kSerial &serial,const char * String)
{
	//Dopóki nie zero (koniec ³añcucha znaków) wykonuj pêtlê
	while(*String)
	{
		//czekaj dopóki bufor nadawczy nie jest pusty (nadajnik wysy³a dane)
		while(USART_GetFlagStatus(serial.hardware.usart,USART_FLAG_TXE) == RESET);

		//wpisz kolejny znak do bufora nadawczego
		serial.hardware.usart->DR = (*String & (uint16_t)0x01FF);

		//przesuñ wskaŸnik na nastêpny znak w ³añcuchu znaków
		String++;
	}

	return serial;
}
const kSerial& operator >>(const kSerial &serial,unsigned char * RecieveBuffer)
{
	unsigned int count;

	while(1)
	{
		count = serial.k_timeout;
		while(!USART_GetFlagStatus(serial.hardware.usart,USART_FLAG_RXNE) && count)
		{
			count--;
		}
		if(!count)
		{
			// timeout
			*RecieveBuffer = 0;
			break;
		}

		*RecieveBuffer = USART_ReceiveData(serial.hardware.usart);
		if(*RecieveBuffer == serial.k_terminator)
		{
			RecieveBuffer++;
			*RecieveBuffer = 0;
			break;
		}
		RecieveBuffer++;
	}

	return serial;
}

kSerial::kSerial(void)
{

}

kSerial::kSerial(const kSerialUSART1Pin & Rx,const kSerialUSART1Pin & Tx,unsigned int BaudRate)
{
	this->hardware = Rx;
	this->hardware = Tx;
	this->baud(BaudRate);
}
kSerial::kSerial(const kSerialUSART1Pin & Pin,unsigned int BaudRate)
{
	this->hardware = Pin;
	this->baud(BaudRate);
}
kSerial::kSerial(const kSerialUSART2Pin & Rx,const kSerialUSART2Pin & Tx,unsigned int BaudRate)
{
	this->hardware = Rx;
	this->hardware = Tx;
	this->baud(BaudRate);
}
kSerial::kSerial(const kSerialUSART2Pin & Pin,unsigned int BaudRate)
{
	this->hardware = Pin;
	this->baud(BaudRate);
}
kSerial::kSerial(const kSerialUSART3Pin & Rx,const kSerialUSART3Pin & Tx,unsigned int BaudRate)
{
	this->hardware = Rx;
	this->hardware = Tx;
	this->baud(BaudRate);
}
kSerial::kSerial(const kSerialUSART3Pin & Pin,unsigned int BaudRate)
{
	this->hardware = Pin;
	this->baud(BaudRate);
}
kSerial::kSerial(const kSerial & other)
{
	this->k_timeout = other.k_timeout;
	this->k_terminator = other.k_terminator;
	this->k_precision = other.k_precision;

	this->hardware = other.hardware;
}
void kSerial::timeout(unsigned int ticks)
{
	this->k_timeout = ticks;
}
void kSerial::terminator(unsigned char character)
{
	this->k_terminator = character;
}
const kSerial& operator <<(const kSerial &serial,int number)
{
	long long div=1;
	unsigned int digit;

	if(number < 0)
	{
		//czekaj dopóki bufor nadawczy nie jest pusty (nadajnik wysy³a dane)
		while(USART_GetFlagStatus(serial.hardware.usart,USART_FLAG_TXE) == RESET);

		//wpisz kolejny znak do bufora nadawczego
		serial.hardware.usart->DR = ('-' & (uint16_t)0x01FF);

		number *= (-1);
	}

	while(div <= number)
	{
		div*=10;
	}
	if(number == 0) div*=10;
	div /= 10;

	while(div)
	{
		digit = number/div;
		number = number % div;
		div /=10;

		//czekaj dopóki bufor nadawczy nie jest pusty (nadajnik wysy³a dane)
		while(USART_GetFlagStatus(serial.hardware.usart,USART_FLAG_TXE) == RESET);

		//wpisz kolejny znak do bufora nadawczego
		serial.hardware.usart->DR = ((char)(digit + 48) & (uint16_t)0x01FF);

	}

	return serial;
}
void kSerial::precision(unsigned char precision_points)
{
	unsigned char i;
	this->k_precision = 1;
	for(i=0;i<precision_points;i++)
	{
		this->k_precision *=10;
	}

}
const kSerial& operator <<(const kSerial &serial,char chr)
{
	//czekaj dopóki bufor nadawczy nie jest pusty (nadajnik wysy³a dane)
	while(USART_GetFlagStatus(serial.hardware.usart,USART_FLAG_TXE) == RESET);

	//wpisz kolejny znak do bufora nadawczego
	serial.hardware.usart->DR = (chr & (uint16_t)0x01FF);

	return serial;
}
const kSerial& operator <<(const kSerial &serial,float number)
{
	long long temp;
	int num1,num2;

	if(number < 0)
	{
		serial << '-';
		number *= (-1);
	}
	num1 = number;
	serial << num1;

	if(serial.k_precision)
	{
		serial << '.';
		number *= serial.k_precision;
		temp = number;
		num2 = temp % serial.k_precision;
		temp = serial.k_precision/10;
		while(temp > num2)
		{
			serial << '0';
			temp /=10;
		}
		if(num2) serial << num2;
	}

	return serial;
}
char kSerial::getChar(void)
{
	while(USART_GetFlagStatus(this->hardware.usart,USART_FLAG_RXNE) == RESET);
	return (char)this->hardware.usart->DR;
}
const kSerial& operator <<(const kSerial &serial,const kString & str)
{
	unsigned short i;
	unsigned char * cstr = str.c_str();
	unsigned short length = str.length();
	for(i=0;i<length;i++)
	{
		//czekaj dopóki bufor nadawczy nie jest pusty (nadajnik wysy³a dane)
		while(USART_GetFlagStatus(serial.hardware.usart,USART_FLAG_TXE) == RESET);

		//wpisz kolejny znak do bufora nadawczego
		serial.hardware.usart->DR = (*cstr & (uint16_t)0x01FF);
		cstr++;
	}



	return serial;
}
