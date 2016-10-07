/***********************************************************************************
 *                                                                                 *
 *   kLib - C++ development tools for ARM Cortex-M devices                         *
 *                                                                                 *
 *     Copyright (c) 2016, project author Paweł Zalewski                                          *
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
#ifndef __kI2CDevice_H
#define __kI2CDevice_H

#include "stm32f4xx_i2c.h"
#include "kPort.h"


	typedef struct
	{
		unsigned char kI2C1pin;
	}kI2C1Pin;

	typedef struct
	{
		kI2C1Pin PORTB7;
		kI2C1Pin PORTB9;

	}kI2C1_SDA_Pin;

	typedef struct
	{
		kI2C1Pin PORTB6;
		kI2C1Pin PORTB8;
	}kI2C1_SCL_Pin;

	typedef struct
	{
		kI2C1_SCL_Pin SCL;
		kI2C1_SDA_Pin SDA;
	}kI2C1;

	typedef struct
	{
		unsigned char kI2C1pin;
	}kI2C2Pin;

	typedef struct
	{
		kI2C2Pin PORTB11;
		kI2C2Pin PORTF0;
		kI2C2Pin PORTH5;

	}kI2C2_SDA_Pin;

	typedef struct
	{
		kI2C2Pin PORTB10;
		kI2C2Pin PORTF1;
		kI2C2Pin PORTH4;
	}kI2C2_SCL_Pin;

	typedef struct
	{
		kI2C2_SCL_Pin SCL;
		kI2C2_SDA_Pin SDA;
	}kI2C2;

	typedef struct
	{
		unsigned char kI2C3pin;
	}kI2C3Pin;

	typedef struct
	{
		kI2C3Pin PORTC9;
		kI2C3Pin PORTH8;

	}kI2C3_SDA_Pin;

	typedef struct
	{
		kI2C3Pin PORTA8;
		kI2C3Pin PORTH7;
	}kI2C3_SCL_Pin;

	typedef struct
	{
		kI2C3_SCL_Pin SCL;
		kI2C3_SDA_Pin SDA;
	}kI2C3;

	class kI2CDeviceHardware
	{
		public:

			I2C_TypeDef * i2c;
			GPIO_TypeDef * sdaGPIO;
			GPIO_TypeDef * sclGPIO;
			unsigned char sdaPin;
			unsigned char sclPin;

			void operator = (const kI2C1Pin & i2cHard);
			void operator = (const kI2C2Pin & i2cHard);
			void operator = (const kI2C3Pin & i2cHard);

			void setupSCLPin(void);
			void setupSDAPin(void);
			void clockSpeed(unsigned int value);



	};

	class kI2CDevice
	{
		public:

			kI2CDeviceHardware hardware;
			unsigned char I2C_Address;

			kI2CDevice(void);
			kI2CDevice(const kI2C1Pin & SCL,const kI2C1Pin & SDA,unsigned int clockSpeed);
			kI2CDevice(const kI2C2Pin & SCL,const kI2C2Pin & SDA,unsigned int clockSpeed);
			kI2CDevice(const kI2C3Pin & SCL,const kI2C3Pin & SDA,unsigned int clockSpeed);

			static const kI2C1 * I2C_1;
			static const kI2C2 * I2C_2;
			static const kI2C3 * I2C_3;

			void write(uint8_t StartingRegisterAddress,uint8_t * transmit_buffer,uint8_t BytesToWrite);
			void write(uint8_t RegisterAddress,uint8_t value);

			void read(uint8_t StartingRegisterAddress, uint8_t * recieve_buffer,uint8_t BytesToRead);
			unsigned char read(uint8_t RegisterAddress);

	};




#endif
