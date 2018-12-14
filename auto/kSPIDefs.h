/***********************************************************************************
 *                                                                                 *
 *   kLib - C++ development tools for ARM Cortex-M devices                         *
 *                                                                                 *
 *     Copyright (c) 2016, project author Pawel Zalewski                           *
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

#ifndef __kSPIDEFS_H
#define __kSPIDEFS_H

#if (kLib_config_PLATFORM == kLib_STM32F427xx)

	typedef struct
	{
		typedef enum
		{
			PORTA6 = 0x04662506
		}kSPI_SPI1_MISO_Pin;
	}kSPI_SPI1_MISO;

	typedef struct
	{
		typedef enum
		{
			PORTA7 = 0x04662507
		}kSPI_SPI1_MOSI_Pin;
	}kSPI_SPI1_MOSI;

	typedef struct
	{
		typedef enum
		{
			PORTA5 = 0x04662505
		}kSPI_SPI1_SCK_Pin;
	}kSPI_SPI1_SCK;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0C660000,
			DataCapture_2Edge = 0x0C660001
		}kSPI_SPI1_SLAVE_MSB_LOW_SELECT;
	}kSPI_SPI1_SLAVE_MSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0C660002,
			DataCapture_2Edge = 0x0C660003
		}kSPI_SPI1_SLAVE_MSB_HIGH_SELECT;
	}kSPI_SPI1_SLAVE_MSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0C660008,
			DataCapture_2Edge = 0x0C660009
		}kSPI_SPI1_SLAVE_LSB_LOW_SELECT;
	}kSPI_SPI1_SLAVE_LSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0C66000A,
			DataCapture_2Edge = 0x0C66000B
		}kSPI_SPI1_SLAVE_LSB_HIGH_SELECT;
	}kSPI_SPI1_SLAVE_LSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0C660004,
			DataCapture_2Edge = 0x0C660005
		}kSPI_SPI1_MASTER_MSB_LOW_SELECT;
	}kSPI_SPI1_MASTER_MSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0C660006,
			DataCapture_2Edge = 0x0C660007
		}kSPI_SPI1_MASTER_MSB_HIGH_SELECT;
	}kSPI_SPI1_MASTER_MSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0C66000C,
			DataCapture_2Edge = 0x0C66000D
		}kSPI_SPI1_MASTER_LSB_LOW_SELECT;
	}kSPI_SPI1_MASTER_LSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0C66000E,
			DataCapture_2Edge = 0x0C66000F
		}kSPI_SPI1_MASTER_LSB_HIGH_SELECT;
	}kSPI_SPI1_MASTER_LSB_HIGH_EDGE;

	typedef struct
	{
		kSPI_SPI1_SLAVE_MSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI1_SLAVE_MSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI1_SLAVE_MSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI1_SLAVE_LSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI1_SLAVE_LSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI1_SLAVE_LSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI1_MASTER_MSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI1_MASTER_MSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI1_MASTER_MSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI1_MASTER_LSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI1_MASTER_LSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI1_MASTER_LSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI1_SLAVE_MSB_SELECT_SELECT MSB_First;
		kSPI_SPI1_SLAVE_LSB_SELECT_SELECT LSB_First;
	}kSPI_SPI1_SLAVE_SELECT_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI1_MASTER_MSB_SELECT_SELECT MSB_First;
		kSPI_SPI1_MASTER_LSB_SELECT_SELECT LSB_First;
	}kSPI_SPI1_MASTER_SELECT_SELECT_SELECT;

	typedef struct
	{
		typedef enum
		{
			PORTA0  = 0x04662000,
			PORTA1  = 0x04662001,
			PORTA2  = 0x04662002,
			PORTA3  = 0x04662003,
			PORTA4  = 0x04662004,
			PORTA5  = 0x04662005,
			PORTA6  = 0x04662006,
			PORTA7  = 0x04662007,
			PORTA8  = 0x04662008,
			PORTA9  = 0x04662009,
			PORTA10 = 0x0466200A,
			PORTA11 = 0x0466200B,
			PORTA12 = 0x0466200C,
			PORTA13 = 0x0466200D,
			PORTA14 = 0x0466200E,
			PORTA15 = 0x0466200F,
			PORTB0  = 0x04662010,
			PORTB1  = 0x04662011,
			PORTB2  = 0x04662012,
			PORTB3  = 0x04662013,
			PORTB4  = 0x04662014,
			PORTB5  = 0x04662015,
			PORTB6  = 0x04662016,
			PORTB7  = 0x04662017,
			PORTB8  = 0x04662018,
			PORTB9  = 0x04662019,
			PORTB10 = 0x0466201A,
			PORTB11 = 0x0466201B,
			PORTB12 = 0x0466201C,
			PORTB13 = 0x0466201D,
			PORTB14 = 0x0466201E,
			PORTB15 = 0x0466201F,
			PORTC0  = 0x04662020,
			PORTC1  = 0x04662021,
			PORTC2  = 0x04662022,
			PORTC3  = 0x04662023,
			PORTC4  = 0x04662024,
			PORTC5  = 0x04662025,
			PORTC6  = 0x04662026,
			PORTC7  = 0x04662027,
			PORTC8  = 0x04662028,
			PORTC9  = 0x04662029,
			PORTC10 = 0x0466202A,
			PORTC11 = 0x0466202B,
			PORTC12 = 0x0466202C,
			PORTC13 = 0x0466202D,
			PORTC14 = 0x0466202E,
			PORTC15 = 0x0466202F,
			PORTD0  = 0x04662030,
			PORTD1  = 0x04662031,
			PORTD2  = 0x04662032,
			PORTD3  = 0x04662033,
			PORTD4  = 0x04662034,
			PORTD5  = 0x04662035,
			PORTD6  = 0x04662036,
			PORTD7  = 0x04662037,
			PORTD8  = 0x04662038,
			PORTD9  = 0x04662039,
			PORTD10 = 0x0466203A,
			PORTD11 = 0x0466203B,
			PORTD12 = 0x0466203C,
			PORTD13 = 0x0466203D,
			PORTD14 = 0x0466203E,
			PORTD15 = 0x0466203F,
			PORTE0  = 0x04662040,
			PORTE1  = 0x04662041,
			PORTE2  = 0x04662042,
			PORTE3  = 0x04662043,
			PORTE4  = 0x04662044,
			PORTE5  = 0x04662045,
			PORTE6  = 0x04662046,
			PORTE7  = 0x04662047,
			PORTE8  = 0x04662048,
			PORTE9  = 0x04662049,
			PORTE10 = 0x0466204A,
			PORTE11 = 0x0466204B,
			PORTE12 = 0x0466204C,
			PORTE13 = 0x0466204D,
			PORTE14 = 0x0466204E,
			PORTE15 = 0x0466204F
		}kSPI_NSS_SOFT_Pin;
	}kSPI_NSS_SOFT;

	typedef struct
	{
		kSPI_SPI1_NSS Hard;
		kSPI_NSS_SOFT Soft;
	}kSPI_SPI1_NSS_SELECT;

	typedef struct
	{
		kSPI_SPI1_SLAVE_SELECT_SELECT_SELECT Master;
		kSPI_SPI1_MASTER_SELECT_SELECT_SELECT Slave;
		kSPI_SPI1_MISO MISO;
		kSPI_SPI1_MOSI MOSI;
		kSPI_SPI1_SCK  SCK;
		kSPI_SPI1_NSS_SELECT NSS;
	}kSPI_SPI1;

	class
	{
		public:

			static const kSPI_SPI1 * spi1;

	}


#endif
#if (kLib_config_PLATFORM == kLib_STM32F427xx)

	typedef struct
	{
		typedef enum
		{
			PORTA0  = 0x04662000,
			PORTA1  = 0x04662001,
			PORTA2  = 0x04662002,
			PORTA3  = 0x04662003,
			PORTA4  = 0x04662004,
			PORTA5  = 0x04662005,
			PORTA6  = 0x04662006,
			PORTA7  = 0x04662007,
			PORTA8  = 0x04662008,
			PORTA9  = 0x04662009,
			PORTA10 = 0x0466200A,
			PORTA11 = 0x0466200B,
			PORTA12 = 0x0466200C,
			PORTA13 = 0x0466200D,
			PORTA14 = 0x0466200E,
			PORTA15 = 0x0466200F,
			PORTB0  = 0x04662010,
			PORTB1  = 0x04662011,
			PORTB2  = 0x04662012,
			PORTB3  = 0x04662013,
			PORTB4  = 0x04662014,
			PORTB5  = 0x04662015,
			PORTB6  = 0x04662016,
			PORTB7  = 0x04662017,
			PORTB8  = 0x04662018,
			PORTB9  = 0x04662019,
			PORTB10 = 0x0466201A,
			PORTB11 = 0x0466201B,
			PORTB12 = 0x0466201C,
			PORTB13 = 0x0466201D,
			PORTB14 = 0x0466201E,
			PORTB15 = 0x0466201F,
			PORTC0  = 0x04662020,
			PORTC1  = 0x04662021,
			PORTC2  = 0x04662022,
			PORTC3  = 0x04662023,
			PORTC4  = 0x04662024,
			PORTC5  = 0x04662025,
			PORTC6  = 0x04662026,
			PORTC7  = 0x04662027,
			PORTC8  = 0x04662028,
			PORTC9  = 0x04662029,
			PORTC10 = 0x0466202A,
			PORTC11 = 0x0466202B,
			PORTC12 = 0x0466202C,
			PORTC13 = 0x0466202D,
			PORTC14 = 0x0466202E,
			PORTC15 = 0x0466202F,
			PORTD0  = 0x04662030,
			PORTD1  = 0x04662031,
			PORTD2  = 0x04662032,
			PORTD3  = 0x04662033,
			PORTD4  = 0x04662034,
			PORTD5  = 0x04662035,
			PORTD6  = 0x04662036,
			PORTD7  = 0x04662037,
			PORTD8  = 0x04662038,
			PORTD9  = 0x04662039,
			PORTD10 = 0x0466203A,
			PORTD11 = 0x0466203B,
			PORTD12 = 0x0466203C,
			PORTD13 = 0x0466203D,
			PORTD14 = 0x0466203E,
			PORTD15 = 0x0466203F,
			PORTE0  = 0x04662040,
			PORTE1  = 0x04662041,
			PORTE2  = 0x04662042,
			PORTE3  = 0x04662043,
			PORTE4  = 0x04662044,
			PORTE5  = 0x04662045,
			PORTE6  = 0x04662046,
			PORTE7  = 0x04662047,
			PORTE8  = 0x04662048,
			PORTE9  = 0x04662049,
			PORTE10 = 0x0466204A,
			PORTE11 = 0x0466204B,
			PORTE12 = 0x0466204C,
			PORTE13 = 0x0466204D,
			PORTE14 = 0x0466204E,
			PORTE15 = 0x0466204F
		}kSPI_NSS_SOFT_Pin;
	}kSPI_NSS_SOFT;

	typedef struct
	{
		kSPI_SPI1_SLAVE_SELECT_SELECT_SELECT Master;
		kSPI_SPI1_MASTER_SELECT_SELECT_SELECT Slave;
		kSPI_SPI1_MISO MISO;
		kSPI_SPI1_MOSI MOSI;
		kSPI_SPI1_SCK  SCK;
		kSPI_SPI1_NSS_SELECT NSS;
	}kSPI_SPI1;

	class
	{
		public:


	}


#endif


#endif  //End of __kSPIDEFS_H
