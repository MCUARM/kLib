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



#include "kSerial.h"


const char* kSerial::endl = "\r\n";


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

kSerial::kSerialHardware& kSerial::kSerialHardware::operator = (unsigned int hard_code)
{
	this->usart = (USART_TypeDef*)kPrivate::setupPeripheralOutput(hard_code);

	// force one stop bit
	this->usart->CR2 &= 0xCFFF;


	// enable receiver and/or transmitter
	hard_code = hard_code >> 25;
	this->usart->CR1 |= hard_code;

	return (*this);
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

	  if((unsigned int)this->hardware.usart & 0x00010000)
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
const kSerial& operator <<(const kSerial &serial,const kVector3 & v)
{
	serial 	<< v.x << "i  "
			<< v.y << "j  "
			<< v.z << "k";

	return serial;
}
const kSerial& operator <<(const kSerial &serial,const kQuaternion & q)
{
	serial 	<< q.r << "  "
			<< q.i << "i  "
			<< q.j << "j  "
			<< q.k << "k";

	return serial;
}
const kSerial& operator <<(const kSerial &serial,const kAxisAngle & axis_angle)
{
	serial << axis_angle.angle << "rad  " << axis_angle.axis;
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
void kSerial::write(void * data, unsigned int bytes) const
{
	unsigned char * p = (unsigned char*)data;

	for(unsigned int i=0;i<bytes;i++)
	{
		//czekaj dop�ki bufor nadawczy nie jest pusty (nadajnik wysy�a dane)
		while(USART_GetFlagStatus(this->hardware.usart,USART_FLAG_TXE) == RESET);

		//wpisz kolejny znak do bufora nadawczego
		this->hardware.usart->DR = (*p & (uint16_t)0x01FF);
		p++;
	}
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
