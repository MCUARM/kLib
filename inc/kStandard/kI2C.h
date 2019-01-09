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



#ifndef __kI2CDevice_H
#define __kI2CDevice_H

#include "kPort.h"

// region PLATFORM_DEPENDED_STRUCTS

#if (kLib_config_PLATFORM == kLib_STM32F411xx)

	typedef struct
	{
		typedef enum
		{
			PORTB7  = 0x058AE417,
			PORTB9  = 0x058AE419
		}kI2C_I2C1_SDA_Pin;
	}kI2C_I2C1_SDA;

	typedef struct
	{
		typedef enum
		{
			PORTB6  = 0x058AE416,
			PORTB8  = 0x058AE418
		}kI2C_I2C1_SCL_Pin;
	}kI2C_I2C1_SCL;

	typedef struct
	{
		typedef enum
		{
			PORTB3  = 0x068B6913,
			PORTB9  = 0x068B6919,
			PORTB11 = 0x068B641B
		}kI2C_I2C2_SDA_Pin;
	}kI2C_I2C2_SDA;

	typedef struct
	{
		typedef enum
		{
			PORTB10 = 0x068B641A
		}kI2C_I2C2_SCL_Pin;
	}kI2C_I2C2_SCL;

	typedef struct
	{
		typedef enum
		{
			PORTB4  = 0x078BE914,
			PORTB8  = 0x078BE918,
			PORTC9  = 0x078BE429
		}kI2C_I2C3_SDA_Pin;
	}kI2C_I2C3_SDA;

	typedef struct
	{
		typedef enum
		{
			PORTA8  = 0x078BE408
		}kI2C_I2C3_SCL_Pin;
	}kI2C_I2C3_SCL;

	typedef struct
	{
		kI2C_I2C1_SDA SDA;
		kI2C_I2C1_SCL SCL;
	}kI2C_I2C1;

	typedef struct
	{
		kI2C_I2C2_SDA SDA;
		kI2C_I2C2_SCL SCL;
	}kI2C_I2C2;

	typedef struct
	{
		kI2C_I2C3_SDA SDA;
		kI2C_I2C3_SCL SCL;
	}kI2C_I2C3;


#endif
#if (kLib_config_PLATFORM == kLib_STM32F429xx)

	typedef struct
	{
		typedef enum
		{
			PORTB7  = 0x058AE417,
			PORTB9  = 0x058AE419
		}kI2C_I2C1_SDA_Pin;
	}kI2C_I2C1_SDA;

	typedef struct
	{
		typedef enum
		{
			PORTB6  = 0x058AE416,
			PORTB8  = 0x058AE418
		}kI2C_I2C1_SCL_Pin;
	}kI2C_I2C1_SCL;

	typedef struct
	{
		typedef enum
		{
			PORTB11 = 0x068B641B,
			PORTF0  = 0x068B6450,
			PORTH5  = 0x068B6475
		}kI2C_I2C2_SDA_Pin;
	}kI2C_I2C2_SDA;

	typedef struct
	{
		typedef enum
		{
			PORTB10 = 0x068B641A,
			PORTF1  = 0x068B6451,
			PORTH4  = 0x068B6474
		}kI2C_I2C2_SCL_Pin;
	}kI2C_I2C2_SCL;

	typedef struct
	{
		typedef enum
		{
			PORTC9  = 0x078BE429,
			PORTH8  = 0x078BE478
		}kI2C_I2C3_SDA_Pin;
	}kI2C_I2C3_SDA;

	typedef struct
	{
		typedef enum
		{
			PORTA8  = 0x078BE408,
			PORTH7  = 0x078BE477
		}kI2C_I2C3_SCL_Pin;
	}kI2C_I2C3_SCL;

	typedef struct
	{
		kI2C_I2C1_SDA SDA;
		kI2C_I2C1_SCL SCL;
	}kI2C_I2C1;

	typedef struct
	{
		kI2C_I2C2_SDA SDA;
		kI2C_I2C2_SCL SCL;
	}kI2C_I2C2;

	typedef struct
	{
		kI2C_I2C3_SDA SDA;
		kI2C_I2C3_SCL SCL;
	}kI2C_I2C3;


#endif
#if (kLib_config_PLATFORM == kLib_STM32L053xx)

	typedef struct
	{
		typedef enum
		{
			PORTB11 = 0x068B661B,
			PORTB14 = 0x068B651E
		}kI2C_I2C2_SDA_Pin;
	}kI2C_I2C2_SDA;

	typedef struct
	{
		typedef enum
		{
			PORTB10 = 0x068B661A,
			PORTB13 = 0x068B651D
		}kI2C_I2C2_SCL_Pin;
	}kI2C_I2C2_SCL;

	typedef struct
	{
		typedef enum
		{
			PORTB9  = 0x058AE419
		}kI2C_I2C1_SDA_Pin;
	}kI2C_I2C1_SDA;

	typedef struct
	{
		typedef enum
		{
			PORTB8  = 0x058AE418
		}kI2C_I2C1_SCL_Pin;
	}kI2C_I2C1_SCL;

	typedef struct
	{
		kI2C_I2C3_SDA SDA;
		kI2C_I2C3_SCL SCL;
	}kI2C_I2C3;

	typedef struct
	{
		kI2C_I2C2_SDA SDA;
		kI2C_I2C2_SCL SCL;
	}kI2C_I2C2;

	typedef struct
	{
		kI2C_I2C1_SDA SDA;
		kI2C_I2C1_SCL SCL;
	}kI2C_I2C1;


#endif


// endregion PLATFORM_DEPENDED_STRUCTS


	typedef struct
	{
		typedef enum
		{
			_100kHz = 100000,
			_400kHz = 400000
		}kI2C_Speed_enum;
	}kI2C_Speed_struct;


	typedef struct
	{
		typedef enum
		{
			BufferInterrupt = 1024,
			EventInterrupt = 512,
			ErrorInterrupt = 256
		}kI2C_Interrupt_enum;
	}kI2C_Interrupt_struct;

	class kI2CHardware
	{
		private:

			friend class kI2C;

			I2C_TypeDef * i2c;

		public:

			kI2CHardware & operator = (uint32_t hard_code);
			kI2CHardware & operator , (uint32_t hard_code);

	};

	class kI2C
	{
			typedef enum
			{
				Receiving,
				Transmitting
			}transfer_direction;


			void sendStart(void);
			void sendAddress(transfer_direction dir);
			void sendData(uint8_t data);
			void sendStop(void);
			uint8_t readData(void);

		public:

			static kI2C_Speed_struct * I2C_Speed;
			static kI2C_Interrupt_struct * I2C_Interrupt;


			kI2CHardware hardware;
			uint8_t address;

			kI2C(void);
			void run(unsigned int clock_speed);

			void reset(void);

			void enableAcknowledge(bool state);

 			void enableInterrupt(uint16_t interrupt_flags);
 			void disableInterrupt(uint16_t interrupt_flags);


			void write(uint8_t StartingRegisterAddress, void * transmit_buffer,uint8_t BytesToWrite);
			void write(uint8_t RegisterAddress,uint8_t value);

			void read(uint8_t StartingRegisterAddress, void * recieve_buffer,uint8_t BytesToRead);
			unsigned char read(uint8_t RegisterAddress);


// region I2C_DECLARATIONS

		#if (kLib_config_PLATFORM == kLib_STM32F411xx)

			static const kI2C_I2C1  * _I2C1;
			static const kI2C_I2C2  * _I2C2;
			static const kI2C_I2C3  * _I2C3;

		#endif

		#if (kLib_config_PLATFORM == kLib_STM32F429xx)

			static const kI2C_I2C1  * _I2C1;
			static const kI2C_I2C2  * _I2C2;
			static const kI2C_I2C3  * _I2C3;

		#endif

		#if (kLib_config_PLATFORM == kLib_STM32L053xx)

			static const kI2C_I2C3  * _I2C3;
			static const kI2C_I2C2  * _I2C2;
			static const kI2C_I2C1  * _I2C1;

		#endif



// endregion I2C_DECLARATIONS

	};



#endif
