#include "kSerial.h"

const char* kSerial::endl = "\r\n";
const kSerialUSART1 * kSerial::usart1 = (kSerialUSART1 *)SRAM1_BASE;
const kSerialUSART2 * kSerial::usart2 = (kSerialUSART2 *)SRAM1_BASE;
const kSerialUSART3 * kSerial::usart3 = (kSerialUSART3 *)SRAM1_BASE;

char default_rx_buffer[2];
unsigned short int default_rx_buffer_length = 2;
unsigned short int default_rx_buffer_pointer = 0;
bool default_use_terminator = false;
char default_terminator = 0;

char * usart1_rx_buffer = default_rx_buffer;
unsigned short int * p_usart1_rx_buffer_length = &default_rx_buffer_length;
unsigned short int * p_usart1_rx_buffer_pointer = &default_rx_buffer_pointer;
bool * p_usart1_use_terminator = &default_use_terminator;
char * p_usart1_terminator = &default_terminator;
unsigned char * p_usart1_terminator_counter = (unsigned char*) &default_rx_buffer[0];

static void kSerial_USART1_IRQ_Handler(void)
{
	// check if the USART1 receive interrupt flag was set
	if( USART_GetITStatus(USART1, USART_IT_RXNE) )
	{
		usart1_rx_buffer[*p_usart1_rx_buffer_pointer] = (char)USART1->DR;

		if(*p_usart1_use_terminator)
		{
			if(usart1_rx_buffer[*p_usart1_rx_buffer_pointer] == (*p_usart1_terminator))
			{
				(*p_usart1_terminator_counter)++;
			}
		}

		(*p_usart1_rx_buffer_pointer)++;
		if((*p_usart1_rx_buffer_pointer) == (*p_usart1_rx_buffer_length)) (*p_usart1_rx_buffer_pointer)=0;

	}
}


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
			// enable RXNE interrupt
			USART1->CR1 |= (1<<5);


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

void kSerial::run(unsigned int BaudRate)
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


	  //setup interrupt
	  this->attachUSART();

	  // usart on
	  this->hardware.usart->CR1 |= 0x2000;
}
const kSerial& operator <<(const kSerial &serial,const char * String)
{
	//Dop�ki nie zero (koniec �a�cucha znak�w) wykonuj p�tl�
	while(*String)
	{
		//czekaj dop�ki bufor nadawczy nie jest pusty (nadajnik wysy�a dane)
		while(USART_GetFlagStatus(serial.hardware.usart,USART_FLAG_TXE) == RESET);

		//wpisz kolejny znak do bufora nadawczego
		serial.hardware.usart->DR = (*String & (uint16_t)0x01FF);

		//przesu� wska�nik na nast�pny znak w �a�cuchu znak�w
		String++;
	}

	return serial;
}


kSerial::kSerial(void)
{
	this->useTerminator = false;
}

kSerial::kSerial(const kSerialUSART1Pin & Rx,const kSerialUSART1Pin & Tx,unsigned int BaudRate)
{
	this->hardware = Rx;
	this->hardware = Tx;
	this->run(BaudRate);
}
kSerial::kSerial(const kSerialUSART1Pin & Pin,unsigned int BaudRate)
{
	this->hardware = Pin;
	this->run(BaudRate);
}
kSerial::kSerial(const kSerialUSART2Pin & Rx,const kSerialUSART2Pin & Tx,unsigned int BaudRate)
{
	this->hardware = Rx;
	this->hardware = Tx;
	this->run(BaudRate);
}
kSerial::kSerial(const kSerialUSART2Pin & Pin,unsigned int BaudRate)
{
	this->hardware = Pin;
	this->run(BaudRate);
}
kSerial::kSerial(const kSerialUSART3Pin & Rx,const kSerialUSART3Pin & Tx,unsigned int BaudRate)
{
	this->hardware = Rx;
	this->hardware = Tx;
	this->run(BaudRate);
}
kSerial::kSerial(const kSerialUSART3Pin & Pin,unsigned int BaudRate)
{
	this->hardware = Pin;
	this->run(BaudRate);
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
	this->useTerminator = true;
}
const kSerial& operator <<(const kSerial &serial,int number)
{
	long long div=1;
	unsigned int digit;

	if(number < 0)
	{
		//czekaj dop�ki bufor nadawczy nie jest pusty (nadajnik wysy�a dane)
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

		//czekaj dop�ki bufor nadawczy nie jest pusty (nadajnik wysy�a dane)
		while(USART_GetFlagStatus(serial.hardware.usart,USART_FLAG_TXE) == RESET);

		//wpisz kolejny znak do bufora nadawczego
		serial.hardware.usart->DR = ((char)(digit + 48) & (uint16_t)0x01FF);

	}

	return serial;
}
const kSerial& operator <<(const kSerial &serial,unsigned int number)
{
	long long div=1;
	unsigned int digit;

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

		//czekaj dop�ki bufor nadawczy nie jest pusty (nadajnik wysy�a dane)
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
	//czekaj dop�ki bufor nadawczy nie jest pusty (nadajnik wysy�a dane)
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
unsigned short int kSerial::newBytesAvailable(void)
{
	if(this->rx_buffer_read_pointer < this->rx_buffer_write_pointer)
	{
		return (rx_buffer_write_pointer-rx_buffer_read_pointer);
	}
	if(this->rx_buffer_read_pointer > this->rx_buffer_write_pointer)
	{
		return (rx_buffer_write_pointer-rx_buffer_read_pointer+kSerial_rxBuffer_size);
	}
	return 0;
}
char kSerial::getChar(void)
{
	char res;
	unsigned int ticks= this->k_timeout;

	while(this->newBytesAvailable() == 0 && (ticks--));
	if(ticks)
	{
		res = this->rxBuffer[this->rx_buffer_read_pointer++];
		if(this->rx_buffer_read_pointer == kSerial_rxBuffer_size) this->rx_buffer_read_pointer=0;
	}else res = 0;

	return res;
}
char kSerial::readByte(void)
{
	char res;
	if(this->newBytesAvailable())
	{
		res = this->rxBuffer[this->rx_buffer_read_pointer++];
		if(this->rx_buffer_read_pointer == kSerial_rxBuffer_size) this->rx_buffer_read_pointer=0;
		return res;
	}
	return 0;
}
unsigned short int kSerial::readAll(char * buffer)
{
	unsigned short int bytes=0;
	while(rx_buffer_read_pointer != this->rx_buffer_write_pointer)
	{
		*buffer = this->rxBuffer[this->rx_buffer_read_pointer++];
		buffer++;
		if(this->rx_buffer_read_pointer == kSerial_rxBuffer_size) this->rx_buffer_read_pointer=0;
	}

	return bytes;
}
unsigned char kSerial::newDataAvailable(void)
{
	return this->dataCounter;
}
unsigned short int kSerial::readData(char * buffer)
{
	unsigned short int res = 0;
	if(this->newDataAvailable())
	{
		while(1)
		{
			*buffer = this->readByte();
			res++;
			if(*buffer == this->k_terminator)
			{
				this->dataCounter--;
				return res;
			}
			buffer++;
		}
	}
	return 0;
}
unsigned short int kSerial::readAllData(char * buffer)
{
	unsigned short int res=0;
	unsigned short int tmp_cnt;

	while(this->dataCounter--)
	{
		tmp_cnt = this->readData(buffer);
		buffer += tmp_cnt;
		res += tmp_cnt;
	}

	return res;
}



const kSerial& operator <<(const kSerial &serial,const kString & str)
{
	unsigned short i;
	unsigned char * cstr = str.c_str();
	unsigned short length = str.length();
	for(i=0;i<length;i++)
	{
		//czekaj dop�ki bufor nadawczy nie jest pusty (nadajnik wysy�a dane)
		while(USART_GetFlagStatus(serial.hardware.usart,USART_FLAG_TXE) == RESET);

		//wpisz kolejny znak do bufora nadawczego
		serial.hardware.usart->DR = (*cstr & (uint16_t)0x01FF);
		cstr++;
	}



	return serial;
}

void kSerial::attachUSART(void)
{
	this->rx_buffer_read_pointer = 0;
	this->rx_buffer_write_pointer = 0;
	this->dataCounter = 0;

	usart1_rx_buffer = this->rxBuffer;
	p_usart1_rx_buffer_length = &this->rx_buffer_size;
	p_usart1_rx_buffer_pointer = &this->rx_buffer_write_pointer;
	p_usart1_use_terminator = &this->useTerminator;
	p_usart1_terminator = &this->k_terminator;
	p_usart1_terminator_counter = &this->dataCounter;

	kSystem.setIRQHandler(37,kSerial_USART1_IRQ_Handler);
	kSystem.enableInterrupt(37,1,1);



}
