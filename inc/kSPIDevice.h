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



#ifndef __kSPIDevice_H
#define __kSPIDevice_H

	#include "stm32f4xx_spi.h"
	#include "kSystem.h"

	class kSPIDevice;
	class kSPIDeviceHardware;

#pragma region PLATFORM_DEPENDED_STRUCTS

#if (kLib_config_PLATFORM == kLib_STM32F427xx)

	typedef struct
	{
		typedef enum
		{
			PORTA6  = 0x04662506,
			PORTB4  = 0x04662514
		}kSPI_SPI1_MISO_Pin;
	}kSPI_SPI1_MISO;

	typedef struct
	{
		typedef enum
		{
			PORTA7  = 0x04662507,
			PORTB5  = 0x04662515
		}kSPI_SPI1_MOSI_Pin;
	}kSPI_SPI1_MOSI;

	typedef struct
	{
		typedef enum
		{
			PORTA5  = 0x04662505,
			PORTB3  = 0x04662513
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
			PORTA4  = 0x04662504,
			PORTB0  = 0x04662510
		}kSPI_SPI1_NSS_HARD_Pin;
	}kSPI_SPI1_NSS_HARD;

	typedef struct
	{
		typedef enum
		{
			PORTD2  = 0x06472532
		}kSPI_SPI2_SCK_Pin;
	}kSPI_SPI2_SCK;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E470000,
			DataCapture_2Edge = 0x0E470001
		}kSPI_SPI2_SLAVE_MSB_LOW_SELECT;
	}kSPI_SPI2_SLAVE_MSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E470002,
			DataCapture_2Edge = 0x0E470003
		}kSPI_SPI2_SLAVE_MSB_HIGH_SELECT;
	}kSPI_SPI2_SLAVE_MSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E470008,
			DataCapture_2Edge = 0x0E470009
		}kSPI_SPI2_SLAVE_LSB_LOW_SELECT;
	}kSPI_SPI2_SLAVE_LSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E47000A,
			DataCapture_2Edge = 0x0E47000B
		}kSPI_SPI2_SLAVE_LSB_HIGH_SELECT;
	}kSPI_SPI2_SLAVE_LSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E470004,
			DataCapture_2Edge = 0x0E470005
		}kSPI_SPI2_MASTER_MSB_LOW_SELECT;
	}kSPI_SPI2_MASTER_MSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E470006,
			DataCapture_2Edge = 0x0E470007
		}kSPI_SPI2_MASTER_MSB_HIGH_SELECT;
	}kSPI_SPI2_MASTER_MSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E47000C,
			DataCapture_2Edge = 0x0E47000D
		}kSPI_SPI2_MASTER_LSB_LOW_SELECT;
	}kSPI_SPI2_MASTER_LSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E47000E,
			DataCapture_2Edge = 0x0E47000F
		}kSPI_SPI2_MASTER_LSB_HIGH_SELECT;
	}kSPI_SPI2_MASTER_LSB_HIGH_EDGE;

	typedef struct
	{
		kSPI_SPI2_SLAVE_MSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI2_SLAVE_MSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI2_SLAVE_MSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI2_SLAVE_LSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI2_SLAVE_LSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI2_SLAVE_LSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI2_MASTER_MSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI2_MASTER_MSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI2_MASTER_MSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI2_MASTER_LSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI2_MASTER_LSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI2_MASTER_LSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI2_SLAVE_MSB_SELECT_SELECT MSB_First;
		kSPI_SPI2_SLAVE_LSB_SELECT_SELECT LSB_First;
	}kSPI_SPI2_SLAVE_SELECT_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI2_MASTER_MSB_SELECT_SELECT MSB_First;
		kSPI_SPI2_MASTER_LSB_SELECT_SELECT LSB_First;
	}kSPI_SPI2_MASTER_SELECT_SELECT_SELECT;

	typedef struct
	{
		typedef enum
		{
			PORTB4  = 0x0747A614,
			PORTC11 = 0x0747A62B
		}kSPI_SPI3_MISO_Pin;
	}kSPI_SPI3_MISO;

	typedef struct
	{
		typedef enum
		{
			PORTB5  = 0x0747A615,
			PORTC12 = 0x0747A62C,
			PORTD6  = 0x0747A536
		}kSPI_SPI3_MOSI_Pin;
	}kSPI_SPI3_MOSI;

	typedef struct
	{
		typedef enum
		{
			PORTB3  = 0x0747A613,
			PORTC10 = 0x0747A62A
		}kSPI_SPI3_SCK_Pin;
	}kSPI_SPI3_SCK;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0F478000,
			DataCapture_2Edge = 0x0F478001
		}kSPI_SPI3_SLAVE_MSB_LOW_SELECT;
	}kSPI_SPI3_SLAVE_MSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0F478002,
			DataCapture_2Edge = 0x0F478003
		}kSPI_SPI3_SLAVE_MSB_HIGH_SELECT;
	}kSPI_SPI3_SLAVE_MSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0F478008,
			DataCapture_2Edge = 0x0F478009
		}kSPI_SPI3_SLAVE_LSB_LOW_SELECT;
	}kSPI_SPI3_SLAVE_LSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0F47800A,
			DataCapture_2Edge = 0x0F47800B
		}kSPI_SPI3_SLAVE_LSB_HIGH_SELECT;
	}kSPI_SPI3_SLAVE_LSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0F478004,
			DataCapture_2Edge = 0x0F478005
		}kSPI_SPI3_MASTER_MSB_LOW_SELECT;
	}kSPI_SPI3_MASTER_MSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0F478006,
			DataCapture_2Edge = 0x0F478007
		}kSPI_SPI3_MASTER_MSB_HIGH_SELECT;
	}kSPI_SPI3_MASTER_MSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0F47800C,
			DataCapture_2Edge = 0x0F47800D
		}kSPI_SPI3_MASTER_LSB_LOW_SELECT;
	}kSPI_SPI3_MASTER_LSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0F47800E,
			DataCapture_2Edge = 0x0F47800F
		}kSPI_SPI3_MASTER_LSB_HIGH_SELECT;
	}kSPI_SPI3_MASTER_LSB_HIGH_EDGE;

	typedef struct
	{
		kSPI_SPI3_SLAVE_MSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI3_SLAVE_MSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI3_SLAVE_MSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI3_SLAVE_LSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI3_SLAVE_LSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI3_SLAVE_LSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI3_MASTER_MSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI3_MASTER_MSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI3_MASTER_MSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI3_MASTER_LSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI3_MASTER_LSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI3_MASTER_LSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI3_SLAVE_MSB_SELECT_SELECT MSB_First;
		kSPI_SPI3_SLAVE_LSB_SELECT_SELECT LSB_First;
	}kSPI_SPI3_SLAVE_SELECT_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI3_MASTER_MSB_SELECT_SELECT MSB_First;
		kSPI_SPI3_MASTER_LSB_SELECT_SELECT LSB_First;
	}kSPI_SPI3_MASTER_SELECT_SELECT_SELECT;

	typedef struct
	{
		typedef enum
		{
			PORTA4  = 0x0747A604,
			PORTB0  = 0x0747A610
		}kSPI_SPI3_NSS_HARD_Pin;
	}kSPI_SPI3_NSS_HARD;

	typedef struct
	{
		typedef enum
		{
			PORTE5  = 0x0666A545,
			PORTE13 = 0x0666A54D
		}kSPI_SPI4_MISO_Pin;
	}kSPI_SPI4_MISO;

	typedef struct
	{
		typedef enum
		{
			PORTE6  = 0x0666A546,
			PORTE14 = 0x0666A54E
		}kSPI_SPI4_MOSI_Pin;
	}kSPI_SPI4_MOSI;

	typedef struct
	{
		typedef enum
		{
			PORTE2  = 0x0666A542,
			PORTE12 = 0x0666A54C
		}kSPI_SPI4_SCK_Pin;
	}kSPI_SPI4_SCK;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E668000,
			DataCapture_2Edge = 0x0E668001
		}kSPI_SPI4_SLAVE_MSB_LOW_SELECT;
	}kSPI_SPI4_SLAVE_MSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E668002,
			DataCapture_2Edge = 0x0E668003
		}kSPI_SPI4_SLAVE_MSB_HIGH_SELECT;
	}kSPI_SPI4_SLAVE_MSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E668008,
			DataCapture_2Edge = 0x0E668009
		}kSPI_SPI4_SLAVE_LSB_LOW_SELECT;
	}kSPI_SPI4_SLAVE_LSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E66800A,
			DataCapture_2Edge = 0x0E66800B
		}kSPI_SPI4_SLAVE_LSB_HIGH_SELECT;
	}kSPI_SPI4_SLAVE_LSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E668004,
			DataCapture_2Edge = 0x0E668005
		}kSPI_SPI4_MASTER_MSB_LOW_SELECT;
	}kSPI_SPI4_MASTER_MSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E668006,
			DataCapture_2Edge = 0x0E668007
		}kSPI_SPI4_MASTER_MSB_HIGH_SELECT;
	}kSPI_SPI4_MASTER_MSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E66800C,
			DataCapture_2Edge = 0x0E66800D
		}kSPI_SPI4_MASTER_LSB_LOW_SELECT;
	}kSPI_SPI4_MASTER_LSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E66800E,
			DataCapture_2Edge = 0x0E66800F
		}kSPI_SPI4_MASTER_LSB_HIGH_SELECT;
	}kSPI_SPI4_MASTER_LSB_HIGH_EDGE;

	typedef struct
	{
		kSPI_SPI4_SLAVE_MSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI4_SLAVE_MSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI4_SLAVE_MSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI4_SLAVE_LSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI4_SLAVE_LSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI4_SLAVE_LSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI4_MASTER_MSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI4_MASTER_MSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI4_MASTER_MSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI4_MASTER_LSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI4_MASTER_LSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI4_MASTER_LSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI4_SLAVE_MSB_SELECT_SELECT MSB_First;
		kSPI_SPI4_SLAVE_LSB_SELECT_SELECT LSB_First;
	}kSPI_SPI4_SLAVE_SELECT_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI4_MASTER_MSB_SELECT_SELECT MSB_First;
		kSPI_SPI4_MASTER_LSB_SELECT_SELECT LSB_First;
	}kSPI_SPI4_MASTER_SELECT_SELECT_SELECT;

	typedef struct
	{
		typedef enum
		{
			PORTE4  = 0x0666A544,
			PORTE11 = 0x0666A54B
		}kSPI_SPI4_NSS_HARD_Pin;
	}kSPI_SPI4_NSS_HARD;

	typedef struct
	{
		typedef enum
		{
			PORTF8  = 0x04AA2558,
			PORTH7  = 0x04AA2577
		}kSPI_SPI5_MISO_Pin;
	}kSPI_SPI5_MISO;

	typedef struct
	{
		typedef enum
		{
			PORTF9  = 0x04AA2559,
			PORTF11 = 0x04AA255B
		}kSPI_SPI5_MOSI_Pin;
	}kSPI_SPI5_MOSI;

	typedef struct
	{
		typedef enum
		{
			PORTF7  = 0x04AA2557,
			PORTH6  = 0x04AA2576
		}kSPI_SPI5_SCK_Pin;
	}kSPI_SPI5_SCK;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0CAA0000,
			DataCapture_2Edge = 0x0CAA0001
		}kSPI_SPI5_SLAVE_MSB_LOW_SELECT;
	}kSPI_SPI5_SLAVE_MSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0CAA0002,
			DataCapture_2Edge = 0x0CAA0003
		}kSPI_SPI5_SLAVE_MSB_HIGH_SELECT;
	}kSPI_SPI5_SLAVE_MSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0CAA0008,
			DataCapture_2Edge = 0x0CAA0009
		}kSPI_SPI5_SLAVE_LSB_LOW_SELECT;
	}kSPI_SPI5_SLAVE_LSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0CAA000A,
			DataCapture_2Edge = 0x0CAA000B
		}kSPI_SPI5_SLAVE_LSB_HIGH_SELECT;
	}kSPI_SPI5_SLAVE_LSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0CAA0004,
			DataCapture_2Edge = 0x0CAA0005
		}kSPI_SPI5_MASTER_MSB_LOW_SELECT;
	}kSPI_SPI5_MASTER_MSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0CAA0006,
			DataCapture_2Edge = 0x0CAA0007
		}kSPI_SPI5_MASTER_MSB_HIGH_SELECT;
	}kSPI_SPI5_MASTER_MSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0CAA000C,
			DataCapture_2Edge = 0x0CAA000D
		}kSPI_SPI5_MASTER_LSB_LOW_SELECT;
	}kSPI_SPI5_MASTER_LSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0CAA000E,
			DataCapture_2Edge = 0x0CAA000F
		}kSPI_SPI5_MASTER_LSB_HIGH_SELECT;
	}kSPI_SPI5_MASTER_LSB_HIGH_EDGE;

	typedef struct
	{
		kSPI_SPI5_SLAVE_MSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI5_SLAVE_MSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI5_SLAVE_MSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI5_SLAVE_LSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI5_SLAVE_LSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI5_SLAVE_LSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI5_MASTER_MSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI5_MASTER_MSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI5_MASTER_MSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI5_MASTER_LSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI5_MASTER_LSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI5_MASTER_LSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI5_SLAVE_MSB_SELECT_SELECT MSB_First;
		kSPI_SPI5_SLAVE_LSB_SELECT_SELECT LSB_First;
	}kSPI_SPI5_SLAVE_SELECT_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI5_MASTER_MSB_SELECT_SELECT MSB_First;
		kSPI_SPI5_MASTER_LSB_SELECT_SELECT LSB_First;
	}kSPI_SPI5_MASTER_SELECT_SELECT_SELECT;

	typedef struct
	{
		typedef enum
		{
			PORTF6  = 0x04AA2556,
			PORTH5  = 0x04AA2575
		}kSPI_SPI5_NSS_HARD_Pin;
	}kSPI_SPI5_NSS_HARD;

	typedef struct
	{
		typedef enum
		{
			PORTG12 = 0x05AAA56C
		}kSPI_SPI6_MISO_Pin;
	}kSPI_SPI6_MISO;

	typedef struct
	{
		typedef enum
		{
			PORTG14 = 0x05AAA56E
		}kSPI_SPI6_MOSI_Pin;
	}kSPI_SPI6_MOSI;

	typedef struct
	{
		typedef enum
		{
			PORTG13 = 0x05AAA56D
		}kSPI_SPI6_SCK_Pin;
	}kSPI_SPI6_SCK;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0DAA8000,
			DataCapture_2Edge = 0x0DAA8001
		}kSPI_SPI6_SLAVE_MSB_LOW_SELECT;
	}kSPI_SPI6_SLAVE_MSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0DAA8002,
			DataCapture_2Edge = 0x0DAA8003
		}kSPI_SPI6_SLAVE_MSB_HIGH_SELECT;
	}kSPI_SPI6_SLAVE_MSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0DAA8008,
			DataCapture_2Edge = 0x0DAA8009
		}kSPI_SPI6_SLAVE_LSB_LOW_SELECT;
	}kSPI_SPI6_SLAVE_LSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0DAA800A,
			DataCapture_2Edge = 0x0DAA800B
		}kSPI_SPI6_SLAVE_LSB_HIGH_SELECT;
	}kSPI_SPI6_SLAVE_LSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0DAA8004,
			DataCapture_2Edge = 0x0DAA8005
		}kSPI_SPI6_MASTER_MSB_LOW_SELECT;
	}kSPI_SPI6_MASTER_MSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0DAA8006,
			DataCapture_2Edge = 0x0DAA8007
		}kSPI_SPI6_MASTER_MSB_HIGH_SELECT;
	}kSPI_SPI6_MASTER_MSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0DAA800C,
			DataCapture_2Edge = 0x0DAA800D
		}kSPI_SPI6_MASTER_LSB_LOW_SELECT;
	}kSPI_SPI6_MASTER_LSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0DAA800E,
			DataCapture_2Edge = 0x0DAA800F
		}kSPI_SPI6_MASTER_LSB_HIGH_SELECT;
	}kSPI_SPI6_MASTER_LSB_HIGH_EDGE;

	typedef struct
	{
		kSPI_SPI6_SLAVE_MSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI6_SLAVE_MSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI6_SLAVE_MSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI6_SLAVE_LSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI6_SLAVE_LSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI6_SLAVE_LSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI6_MASTER_MSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI6_MASTER_MSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI6_MASTER_MSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI6_MASTER_LSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI6_MASTER_LSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI6_MASTER_LSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI6_SLAVE_MSB_SELECT_SELECT MSB_First;
		kSPI_SPI6_SLAVE_LSB_SELECT_SELECT LSB_First;
	}kSPI_SPI6_SLAVE_SELECT_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI6_MASTER_MSB_SELECT_SELECT MSB_First;
		kSPI_SPI6_MASTER_LSB_SELECT_SELECT LSB_First;
	}kSPI_SPI6_MASTER_SELECT_SELECT_SELECT;

	typedef struct
	{
		typedef enum
		{
			PORTG8  = 0x05AAA568
		}kSPI_SPI6_NSS_HARD_Pin;
	}kSPI_SPI6_NSS_HARD;

	typedef struct
	{
		typedef enum
		{
			PORTA0  = 0x05AAA000,
			PORTA1  = 0x05AAA001,
			PORTA2  = 0x05AAA002,
			PORTA3  = 0x05AAA003,
			PORTA4  = 0x05AAA004,
			PORTA5  = 0x05AAA005,
			PORTA6  = 0x05AAA006,
			PORTA7  = 0x05AAA007,
			PORTA8  = 0x05AAA008,
			PORTA9  = 0x05AAA009,
			PORTA10 = 0x05AAA00A,
			PORTA11 = 0x05AAA00B,
			PORTA12 = 0x05AAA00C,
			PORTA13 = 0x05AAA00D,
			PORTA14 = 0x05AAA00E,
			PORTA15 = 0x05AAA00F,
			PORTB0  = 0x05AAA010,
			PORTB1  = 0x05AAA011,
			PORTB2  = 0x05AAA012,
			PORTB3  = 0x05AAA013,
			PORTB4  = 0x05AAA014,
			PORTB5  = 0x05AAA015,
			PORTB6  = 0x05AAA016,
			PORTB7  = 0x05AAA017,
			PORTB8  = 0x05AAA018,
			PORTB9  = 0x05AAA019,
			PORTB10 = 0x05AAA01A,
			PORTB11 = 0x05AAA01B,
			PORTB12 = 0x05AAA01C,
			PORTB13 = 0x05AAA01D,
			PORTB14 = 0x05AAA01E,
			PORTB15 = 0x05AAA01F,
			PORTC0  = 0x05AAA020,
			PORTC1  = 0x05AAA021,
			PORTC2  = 0x05AAA022,
			PORTC3  = 0x05AAA023,
			PORTC4  = 0x05AAA024,
			PORTC5  = 0x05AAA025,
			PORTC6  = 0x05AAA026,
			PORTC7  = 0x05AAA027,
			PORTC8  = 0x05AAA028,
			PORTC9  = 0x05AAA029,
			PORTC10 = 0x05AAA02A,
			PORTC11 = 0x05AAA02B,
			PORTC12 = 0x05AAA02C,
			PORTC13 = 0x05AAA02D,
			PORTC14 = 0x05AAA02E,
			PORTC15 = 0x05AAA02F,
			PORTD0  = 0x05AAA030,
			PORTD1  = 0x05AAA031,
			PORTD2  = 0x05AAA032,
			PORTD3  = 0x05AAA033,
			PORTD4  = 0x05AAA034,
			PORTD5  = 0x05AAA035,
			PORTD6  = 0x05AAA036,
			PORTD7  = 0x05AAA037,
			PORTD8  = 0x05AAA038,
			PORTD9  = 0x05AAA039,
			PORTD10 = 0x05AAA03A,
			PORTD11 = 0x05AAA03B,
			PORTD12 = 0x05AAA03C,
			PORTD13 = 0x05AAA03D,
			PORTD14 = 0x05AAA03E,
			PORTD15 = 0x05AAA03F,
			PORTE0  = 0x05AAA040,
			PORTE1  = 0x05AAA041,
			PORTE2  = 0x05AAA042,
			PORTE3  = 0x05AAA043,
			PORTE4  = 0x05AAA044,
			PORTE5  = 0x05AAA045,
			PORTE6  = 0x05AAA046,
			PORTE7  = 0x05AAA047,
			PORTE8  = 0x05AAA048,
			PORTE9  = 0x05AAA049,
			PORTE10 = 0x05AAA04A,
			PORTE11 = 0x05AAA04B,
			PORTE12 = 0x05AAA04C,
			PORTE13 = 0x05AAA04D,
			PORTE14 = 0x05AAA04E,
			PORTE15 = 0x05AAA04F,
			PORTF0  = 0x05AAA050,
			PORTF1  = 0x05AAA051,
			PORTF2  = 0x05AAA052,
			PORTF3  = 0x05AAA053,
			PORTF4  = 0x05AAA054,
			PORTF5  = 0x05AAA055,
			PORTF6  = 0x05AAA056,
			PORTF7  = 0x05AAA057,
			PORTF8  = 0x05AAA058,
			PORTF9  = 0x05AAA059,
			PORTF10 = 0x05AAA05A,
			PORTF11 = 0x05AAA05B,
			PORTF12 = 0x05AAA05C,
			PORTF13 = 0x05AAA05D,
			PORTF14 = 0x05AAA05E,
			PORTF15 = 0x05AAA05F,
			PORTG0  = 0x05AAA060,
			PORTG1  = 0x05AAA061,
			PORTG2  = 0x05AAA062,
			PORTG3  = 0x05AAA063,
			PORTG4  = 0x05AAA064,
			PORTG5  = 0x05AAA065,
			PORTG6  = 0x05AAA066,
			PORTG7  = 0x05AAA067,
			PORTG8  = 0x05AAA068,
			PORTG9  = 0x05AAA069,
			PORTG10 = 0x05AAA06A,
			PORTG11 = 0x05AAA06B,
			PORTG12 = 0x05AAA06C,
			PORTG13 = 0x05AAA06D,
			PORTG14 = 0x05AAA06E,
			PORTG15 = 0x05AAA06F,
			PORTH0  = 0x05AAA070,
			PORTH1  = 0x05AAA071,
			PORTH2  = 0x05AAA072,
			PORTH3  = 0x05AAA073,
			PORTH4  = 0x05AAA074,
			PORTH5  = 0x05AAA075,
			PORTH6  = 0x05AAA076,
			PORTH7  = 0x05AAA077,
			PORTH8  = 0x05AAA078,
			PORTH9  = 0x05AAA079,
			PORTH10 = 0x05AAA07A,
			PORTH11 = 0x05AAA07B,
			PORTH12 = 0x05AAA07C,
			PORTH13 = 0x05AAA07D,
			PORTH14 = 0x05AAA07E,
			PORTH15 = 0x05AAA07F
		}kSPI_NSS_SOFT_Pin;
	}kSPI_NSS_SOFT;

	typedef struct
	{
		kSPI_SPI1_NSS Hard;
		kSPI_NSS_SOFT Soft;
	}kSPI_SPI1_NSS_SELECT;

	typedef struct
	{
		kSPI_SPI2_NSS Hard;
		kSPI_NSS_SOFT Soft;
	}kSPI_SPI2_NSS_SELECT;

	typedef struct
	{
		kSPI_SPI3_NSS Hard;
		kSPI_NSS_SOFT Soft;
	}kSPI_SPI3_NSS_SELECT;

	typedef struct
	{
		kSPI_SPI4_NSS Hard;
		kSPI_NSS_SOFT Soft;
	}kSPI_SPI4_NSS_SELECT;

	typedef struct
	{
		kSPI_SPI5_NSS Hard;
		kSPI_NSS_SOFT Soft;
	}kSPI_SPI5_NSS_SELECT;

	typedef struct
	{
		kSPI_SPI6_NSS Hard;
		kSPI_NSS_SOFT Soft;
	}kSPI_SPI6_NSS_SELECT;

	typedef struct
	{
		kSPI_SPI6_SLAVE_SELECT_SELECT_SELECT Master;
		kSPI_SPI6_MASTER_SELECT_SELECT_SELECT Slave;
		kSPI_SPI6_MISO MISO;
		kSPI_SPI6_MOSI MOSI;
		kSPI_SPI6_SCK  SCK;
		kSPI_SPI6_NSS_SELECT NSS;
	}kSPI_SPI6;


#endif
#if (kLib_config_PLATFORM == kLib_STM32F429xx)

	typedef struct
	{
		typedef enum
		{
			PORTA6  = 0x04662506,
			PORTB4  = 0x04662514
		}kSPI_SPI1_MISO_Pin;
	}kSPI_SPI1_MISO;

	typedef struct
	{
		typedef enum
		{
			PORTA7  = 0x04662507,
			PORTB5  = 0x04662515
		}kSPI_SPI1_MOSI_Pin;
	}kSPI_SPI1_MOSI;

	typedef struct
	{
		typedef enum
		{
			PORTA5  = 0x04662505,
			PORTB3  = 0x04662513
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
			PORTA4  = 0x04662504,
			PORTB0  = 0x04662510
		}kSPI_SPI1_NSS_HARD_Pin;
	}kSPI_SPI1_NSS_HARD;

	typedef struct
	{
		typedef enum
		{
			PORTD2  = 0x06472532
		}kSPI_SPI2_SCK_Pin;
	}kSPI_SPI2_SCK;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E470000,
			DataCapture_2Edge = 0x0E470001
		}kSPI_SPI2_SLAVE_MSB_LOW_SELECT;
	}kSPI_SPI2_SLAVE_MSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E470002,
			DataCapture_2Edge = 0x0E470003
		}kSPI_SPI2_SLAVE_MSB_HIGH_SELECT;
	}kSPI_SPI2_SLAVE_MSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E470008,
			DataCapture_2Edge = 0x0E470009
		}kSPI_SPI2_SLAVE_LSB_LOW_SELECT;
	}kSPI_SPI2_SLAVE_LSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E47000A,
			DataCapture_2Edge = 0x0E47000B
		}kSPI_SPI2_SLAVE_LSB_HIGH_SELECT;
	}kSPI_SPI2_SLAVE_LSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E470004,
			DataCapture_2Edge = 0x0E470005
		}kSPI_SPI2_MASTER_MSB_LOW_SELECT;
	}kSPI_SPI2_MASTER_MSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E470006,
			DataCapture_2Edge = 0x0E470007
		}kSPI_SPI2_MASTER_MSB_HIGH_SELECT;
	}kSPI_SPI2_MASTER_MSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E47000C,
			DataCapture_2Edge = 0x0E47000D
		}kSPI_SPI2_MASTER_LSB_LOW_SELECT;
	}kSPI_SPI2_MASTER_LSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E47000E,
			DataCapture_2Edge = 0x0E47000F
		}kSPI_SPI2_MASTER_LSB_HIGH_SELECT;
	}kSPI_SPI2_MASTER_LSB_HIGH_EDGE;

	typedef struct
	{
		kSPI_SPI2_SLAVE_MSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI2_SLAVE_MSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI2_SLAVE_MSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI2_SLAVE_LSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI2_SLAVE_LSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI2_SLAVE_LSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI2_MASTER_MSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI2_MASTER_MSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI2_MASTER_MSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI2_MASTER_LSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI2_MASTER_LSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI2_MASTER_LSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI2_SLAVE_MSB_SELECT_SELECT MSB_First;
		kSPI_SPI2_SLAVE_LSB_SELECT_SELECT LSB_First;
	}kSPI_SPI2_SLAVE_SELECT_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI2_MASTER_MSB_SELECT_SELECT MSB_First;
		kSPI_SPI2_MASTER_LSB_SELECT_SELECT LSB_First;
	}kSPI_SPI2_MASTER_SELECT_SELECT_SELECT;

	typedef struct
	{
		typedef enum
		{
			PORTB4  = 0x0747A614,
			PORTC11 = 0x0747A62B
		}kSPI_SPI3_MISO_Pin;
	}kSPI_SPI3_MISO;

	typedef struct
	{
		typedef enum
		{
			PORTB5  = 0x0747A615,
			PORTC12 = 0x0747A62C,
			PORTD6  = 0x0747A536
		}kSPI_SPI3_MOSI_Pin;
	}kSPI_SPI3_MOSI;

	typedef struct
	{
		typedef enum
		{
			PORTB3  = 0x0747A613,
			PORTC10 = 0x0747A62A
		}kSPI_SPI3_SCK_Pin;
	}kSPI_SPI3_SCK;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0F478000,
			DataCapture_2Edge = 0x0F478001
		}kSPI_SPI3_SLAVE_MSB_LOW_SELECT;
	}kSPI_SPI3_SLAVE_MSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0F478002,
			DataCapture_2Edge = 0x0F478003
		}kSPI_SPI3_SLAVE_MSB_HIGH_SELECT;
	}kSPI_SPI3_SLAVE_MSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0F478008,
			DataCapture_2Edge = 0x0F478009
		}kSPI_SPI3_SLAVE_LSB_LOW_SELECT;
	}kSPI_SPI3_SLAVE_LSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0F47800A,
			DataCapture_2Edge = 0x0F47800B
		}kSPI_SPI3_SLAVE_LSB_HIGH_SELECT;
	}kSPI_SPI3_SLAVE_LSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0F478004,
			DataCapture_2Edge = 0x0F478005
		}kSPI_SPI3_MASTER_MSB_LOW_SELECT;
	}kSPI_SPI3_MASTER_MSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0F478006,
			DataCapture_2Edge = 0x0F478007
		}kSPI_SPI3_MASTER_MSB_HIGH_SELECT;
	}kSPI_SPI3_MASTER_MSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0F47800C,
			DataCapture_2Edge = 0x0F47800D
		}kSPI_SPI3_MASTER_LSB_LOW_SELECT;
	}kSPI_SPI3_MASTER_LSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0F47800E,
			DataCapture_2Edge = 0x0F47800F
		}kSPI_SPI3_MASTER_LSB_HIGH_SELECT;
	}kSPI_SPI3_MASTER_LSB_HIGH_EDGE;

	typedef struct
	{
		kSPI_SPI3_SLAVE_MSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI3_SLAVE_MSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI3_SLAVE_MSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI3_SLAVE_LSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI3_SLAVE_LSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI3_SLAVE_LSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI3_MASTER_MSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI3_MASTER_MSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI3_MASTER_MSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI3_MASTER_LSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI3_MASTER_LSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI3_MASTER_LSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI3_SLAVE_MSB_SELECT_SELECT MSB_First;
		kSPI_SPI3_SLAVE_LSB_SELECT_SELECT LSB_First;
	}kSPI_SPI3_SLAVE_SELECT_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI3_MASTER_MSB_SELECT_SELECT MSB_First;
		kSPI_SPI3_MASTER_LSB_SELECT_SELECT LSB_First;
	}kSPI_SPI3_MASTER_SELECT_SELECT_SELECT;

	typedef struct
	{
		typedef enum
		{
			PORTA4  = 0x0747A604,
			PORTB0  = 0x0747A610
		}kSPI_SPI3_NSS_HARD_Pin;
	}kSPI_SPI3_NSS_HARD;

	typedef struct
	{
		typedef enum
		{
			PORTE5  = 0x0666A545,
			PORTE13 = 0x0666A54D
		}kSPI_SPI4_MISO_Pin;
	}kSPI_SPI4_MISO;

	typedef struct
	{
		typedef enum
		{
			PORTE6  = 0x0666A546,
			PORTE14 = 0x0666A54E
		}kSPI_SPI4_MOSI_Pin;
	}kSPI_SPI4_MOSI;

	typedef struct
	{
		typedef enum
		{
			PORTE2  = 0x0666A542,
			PORTE12 = 0x0666A54C
		}kSPI_SPI4_SCK_Pin;
	}kSPI_SPI4_SCK;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E668000,
			DataCapture_2Edge = 0x0E668001
		}kSPI_SPI4_SLAVE_MSB_LOW_SELECT;
	}kSPI_SPI4_SLAVE_MSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E668002,
			DataCapture_2Edge = 0x0E668003
		}kSPI_SPI4_SLAVE_MSB_HIGH_SELECT;
	}kSPI_SPI4_SLAVE_MSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E668008,
			DataCapture_2Edge = 0x0E668009
		}kSPI_SPI4_SLAVE_LSB_LOW_SELECT;
	}kSPI_SPI4_SLAVE_LSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E66800A,
			DataCapture_2Edge = 0x0E66800B
		}kSPI_SPI4_SLAVE_LSB_HIGH_SELECT;
	}kSPI_SPI4_SLAVE_LSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E668004,
			DataCapture_2Edge = 0x0E668005
		}kSPI_SPI4_MASTER_MSB_LOW_SELECT;
	}kSPI_SPI4_MASTER_MSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E668006,
			DataCapture_2Edge = 0x0E668007
		}kSPI_SPI4_MASTER_MSB_HIGH_SELECT;
	}kSPI_SPI4_MASTER_MSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E66800C,
			DataCapture_2Edge = 0x0E66800D
		}kSPI_SPI4_MASTER_LSB_LOW_SELECT;
	}kSPI_SPI4_MASTER_LSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0E66800E,
			DataCapture_2Edge = 0x0E66800F
		}kSPI_SPI4_MASTER_LSB_HIGH_SELECT;
	}kSPI_SPI4_MASTER_LSB_HIGH_EDGE;

	typedef struct
	{
		kSPI_SPI4_SLAVE_MSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI4_SLAVE_MSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI4_SLAVE_MSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI4_SLAVE_LSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI4_SLAVE_LSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI4_SLAVE_LSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI4_MASTER_MSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI4_MASTER_MSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI4_MASTER_MSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI4_MASTER_LSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI4_MASTER_LSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI4_MASTER_LSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI4_SLAVE_MSB_SELECT_SELECT MSB_First;
		kSPI_SPI4_SLAVE_LSB_SELECT_SELECT LSB_First;
	}kSPI_SPI4_SLAVE_SELECT_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI4_MASTER_MSB_SELECT_SELECT MSB_First;
		kSPI_SPI4_MASTER_LSB_SELECT_SELECT LSB_First;
	}kSPI_SPI4_MASTER_SELECT_SELECT_SELECT;

	typedef struct
	{
		typedef enum
		{
			PORTE4  = 0x0666A544,
			PORTE11 = 0x0666A54B
		}kSPI_SPI4_NSS_HARD_Pin;
	}kSPI_SPI4_NSS_HARD;

	typedef struct
	{
		typedef enum
		{
			PORTF8  = 0x04AA2558,
			PORTH7  = 0x04AA2577
		}kSPI_SPI5_MISO_Pin;
	}kSPI_SPI5_MISO;

	typedef struct
	{
		typedef enum
		{
			PORTF9  = 0x04AA2559,
			PORTF11 = 0x04AA255B
		}kSPI_SPI5_MOSI_Pin;
	}kSPI_SPI5_MOSI;

	typedef struct
	{
		typedef enum
		{
			PORTF7  = 0x04AA2557,
			PORTH6  = 0x04AA2576
		}kSPI_SPI5_SCK_Pin;
	}kSPI_SPI5_SCK;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0CAA0000,
			DataCapture_2Edge = 0x0CAA0001
		}kSPI_SPI5_SLAVE_MSB_LOW_SELECT;
	}kSPI_SPI5_SLAVE_MSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0CAA0002,
			DataCapture_2Edge = 0x0CAA0003
		}kSPI_SPI5_SLAVE_MSB_HIGH_SELECT;
	}kSPI_SPI5_SLAVE_MSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0CAA0008,
			DataCapture_2Edge = 0x0CAA0009
		}kSPI_SPI5_SLAVE_LSB_LOW_SELECT;
	}kSPI_SPI5_SLAVE_LSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0CAA000A,
			DataCapture_2Edge = 0x0CAA000B
		}kSPI_SPI5_SLAVE_LSB_HIGH_SELECT;
	}kSPI_SPI5_SLAVE_LSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0CAA0004,
			DataCapture_2Edge = 0x0CAA0005
		}kSPI_SPI5_MASTER_MSB_LOW_SELECT;
	}kSPI_SPI5_MASTER_MSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0CAA0006,
			DataCapture_2Edge = 0x0CAA0007
		}kSPI_SPI5_MASTER_MSB_HIGH_SELECT;
	}kSPI_SPI5_MASTER_MSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0CAA000C,
			DataCapture_2Edge = 0x0CAA000D
		}kSPI_SPI5_MASTER_LSB_LOW_SELECT;
	}kSPI_SPI5_MASTER_LSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0CAA000E,
			DataCapture_2Edge = 0x0CAA000F
		}kSPI_SPI5_MASTER_LSB_HIGH_SELECT;
	}kSPI_SPI5_MASTER_LSB_HIGH_EDGE;

	typedef struct
	{
		kSPI_SPI5_SLAVE_MSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI5_SLAVE_MSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI5_SLAVE_MSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI5_SLAVE_LSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI5_SLAVE_LSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI5_SLAVE_LSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI5_MASTER_MSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI5_MASTER_MSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI5_MASTER_MSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI5_MASTER_LSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI5_MASTER_LSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI5_MASTER_LSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI5_SLAVE_MSB_SELECT_SELECT MSB_First;
		kSPI_SPI5_SLAVE_LSB_SELECT_SELECT LSB_First;
	}kSPI_SPI5_SLAVE_SELECT_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI5_MASTER_MSB_SELECT_SELECT MSB_First;
		kSPI_SPI5_MASTER_LSB_SELECT_SELECT LSB_First;
	}kSPI_SPI5_MASTER_SELECT_SELECT_SELECT;

	typedef struct
	{
		typedef enum
		{
			PORTF6  = 0x04AA2556,
			PORTH5  = 0x04AA2575
		}kSPI_SPI5_NSS_HARD_Pin;
	}kSPI_SPI5_NSS_HARD;

	typedef struct
	{
		typedef enum
		{
			PORTG12 = 0x05AAA56C
		}kSPI_SPI6_MISO_Pin;
	}kSPI_SPI6_MISO;

	typedef struct
	{
		typedef enum
		{
			PORTG14 = 0x05AAA56E
		}kSPI_SPI6_MOSI_Pin;
	}kSPI_SPI6_MOSI;

	typedef struct
	{
		typedef enum
		{
			PORTG13 = 0x05AAA56D
		}kSPI_SPI6_SCK_Pin;
	}kSPI_SPI6_SCK;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0DAA8000,
			DataCapture_2Edge = 0x0DAA8001
		}kSPI_SPI6_SLAVE_MSB_LOW_SELECT;
	}kSPI_SPI6_SLAVE_MSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0DAA8002,
			DataCapture_2Edge = 0x0DAA8003
		}kSPI_SPI6_SLAVE_MSB_HIGH_SELECT;
	}kSPI_SPI6_SLAVE_MSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0DAA8008,
			DataCapture_2Edge = 0x0DAA8009
		}kSPI_SPI6_SLAVE_LSB_LOW_SELECT;
	}kSPI_SPI6_SLAVE_LSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0DAA800A,
			DataCapture_2Edge = 0x0DAA800B
		}kSPI_SPI6_SLAVE_LSB_HIGH_SELECT;
	}kSPI_SPI6_SLAVE_LSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0DAA8004,
			DataCapture_2Edge = 0x0DAA8005
		}kSPI_SPI6_MASTER_MSB_LOW_SELECT;
	}kSPI_SPI6_MASTER_MSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0DAA8006,
			DataCapture_2Edge = 0x0DAA8007
		}kSPI_SPI6_MASTER_MSB_HIGH_SELECT;
	}kSPI_SPI6_MASTER_MSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0DAA800C,
			DataCapture_2Edge = 0x0DAA800D
		}kSPI_SPI6_MASTER_LSB_LOW_SELECT;
	}kSPI_SPI6_MASTER_LSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0x0DAA800E,
			DataCapture_2Edge = 0x0DAA800F
		}kSPI_SPI6_MASTER_LSB_HIGH_SELECT;
	}kSPI_SPI6_MASTER_LSB_HIGH_EDGE;

	typedef struct
	{
		kSPI_SPI6_SLAVE_MSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI6_SLAVE_MSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI6_SLAVE_MSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI6_SLAVE_LSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI6_SLAVE_LSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI6_SLAVE_LSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI6_MASTER_MSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI6_MASTER_MSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI6_MASTER_MSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI6_MASTER_LSB_LOW_EDGE SCK_IdleLow;
		kSPI_SPI6_MASTER_LSB_HIGH_EDGE SCK_IdleHigh;
	}kSPI_SPI6_MASTER_LSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI6_SLAVE_MSB_SELECT_SELECT MSB_First;
		kSPI_SPI6_SLAVE_LSB_SELECT_SELECT LSB_First;
	}kSPI_SPI6_SLAVE_SELECT_SELECT_SELECT;

	typedef struct
	{
		kSPI_SPI6_MASTER_MSB_SELECT_SELECT MSB_First;
		kSPI_SPI6_MASTER_LSB_SELECT_SELECT LSB_First;
	}kSPI_SPI6_MASTER_SELECT_SELECT_SELECT;

	typedef struct
	{
		typedef enum
		{
			PORTG8  = 0x05AAA568
		}kSPI_SPI6_NSS_HARD_Pin;
	}kSPI_SPI6_NSS_HARD;

	typedef struct
	{
		typedef enum
		{
			PORTA0  = 0x05AAA000,
			PORTA1  = 0x05AAA001,
			PORTA2  = 0x05AAA002,
			PORTA3  = 0x05AAA003,
			PORTA4  = 0x05AAA004,
			PORTA5  = 0x05AAA005,
			PORTA6  = 0x05AAA006,
			PORTA7  = 0x05AAA007,
			PORTA8  = 0x05AAA008,
			PORTA9  = 0x05AAA009,
			PORTA10 = 0x05AAA00A,
			PORTA11 = 0x05AAA00B,
			PORTA12 = 0x05AAA00C,
			PORTA13 = 0x05AAA00D,
			PORTA14 = 0x05AAA00E,
			PORTA15 = 0x05AAA00F,
			PORTB0  = 0x05AAA010,
			PORTB1  = 0x05AAA011,
			PORTB2  = 0x05AAA012,
			PORTB3  = 0x05AAA013,
			PORTB4  = 0x05AAA014,
			PORTB5  = 0x05AAA015,
			PORTB6  = 0x05AAA016,
			PORTB7  = 0x05AAA017,
			PORTB8  = 0x05AAA018,
			PORTB9  = 0x05AAA019,
			PORTB10 = 0x05AAA01A,
			PORTB11 = 0x05AAA01B,
			PORTB12 = 0x05AAA01C,
			PORTB13 = 0x05AAA01D,
			PORTB14 = 0x05AAA01E,
			PORTB15 = 0x05AAA01F,
			PORTC0  = 0x05AAA020,
			PORTC1  = 0x05AAA021,
			PORTC2  = 0x05AAA022,
			PORTC3  = 0x05AAA023,
			PORTC4  = 0x05AAA024,
			PORTC5  = 0x05AAA025,
			PORTC6  = 0x05AAA026,
			PORTC7  = 0x05AAA027,
			PORTC8  = 0x05AAA028,
			PORTC9  = 0x05AAA029,
			PORTC10 = 0x05AAA02A,
			PORTC11 = 0x05AAA02B,
			PORTC12 = 0x05AAA02C,
			PORTC13 = 0x05AAA02D,
			PORTC14 = 0x05AAA02E,
			PORTC15 = 0x05AAA02F,
			PORTD0  = 0x05AAA030,
			PORTD1  = 0x05AAA031,
			PORTD2  = 0x05AAA032,
			PORTD3  = 0x05AAA033,
			PORTD4  = 0x05AAA034,
			PORTD5  = 0x05AAA035,
			PORTD6  = 0x05AAA036,
			PORTD7  = 0x05AAA037,
			PORTD8  = 0x05AAA038,
			PORTD9  = 0x05AAA039,
			PORTD10 = 0x05AAA03A,
			PORTD11 = 0x05AAA03B,
			PORTD12 = 0x05AAA03C,
			PORTD13 = 0x05AAA03D,
			PORTD14 = 0x05AAA03E,
			PORTD15 = 0x05AAA03F,
			PORTE0  = 0x05AAA040,
			PORTE1  = 0x05AAA041,
			PORTE2  = 0x05AAA042,
			PORTE3  = 0x05AAA043,
			PORTE4  = 0x05AAA044,
			PORTE5  = 0x05AAA045,
			PORTE6  = 0x05AAA046,
			PORTE7  = 0x05AAA047,
			PORTE8  = 0x05AAA048,
			PORTE9  = 0x05AAA049,
			PORTE10 = 0x05AAA04A,
			PORTE11 = 0x05AAA04B,
			PORTE12 = 0x05AAA04C,
			PORTE13 = 0x05AAA04D,
			PORTE14 = 0x05AAA04E,
			PORTE15 = 0x05AAA04F,
			PORTF0  = 0x05AAA050,
			PORTF1  = 0x05AAA051,
			PORTF2  = 0x05AAA052,
			PORTF3  = 0x05AAA053,
			PORTF4  = 0x05AAA054,
			PORTF5  = 0x05AAA055,
			PORTF6  = 0x05AAA056,
			PORTF7  = 0x05AAA057,
			PORTF8  = 0x05AAA058,
			PORTF9  = 0x05AAA059,
			PORTF10 = 0x05AAA05A,
			PORTF11 = 0x05AAA05B,
			PORTF12 = 0x05AAA05C,
			PORTF13 = 0x05AAA05D,
			PORTF14 = 0x05AAA05E,
			PORTF15 = 0x05AAA05F,
			PORTG0  = 0x05AAA060,
			PORTG1  = 0x05AAA061,
			PORTG2  = 0x05AAA062,
			PORTG3  = 0x05AAA063,
			PORTG4  = 0x05AAA064,
			PORTG5  = 0x05AAA065,
			PORTG6  = 0x05AAA066,
			PORTG7  = 0x05AAA067,
			PORTG8  = 0x05AAA068,
			PORTG9  = 0x05AAA069,
			PORTG10 = 0x05AAA06A,
			PORTG11 = 0x05AAA06B,
			PORTG12 = 0x05AAA06C,
			PORTG13 = 0x05AAA06D,
			PORTG14 = 0x05AAA06E,
			PORTG15 = 0x05AAA06F,
			PORTH0  = 0x05AAA070,
			PORTH1  = 0x05AAA071,
			PORTH2  = 0x05AAA072,
			PORTH3  = 0x05AAA073,
			PORTH4  = 0x05AAA074,
			PORTH5  = 0x05AAA075,
			PORTH6  = 0x05AAA076,
			PORTH7  = 0x05AAA077,
			PORTH8  = 0x05AAA078,
			PORTH9  = 0x05AAA079,
			PORTH10 = 0x05AAA07A,
			PORTH11 = 0x05AAA07B,
			PORTH12 = 0x05AAA07C,
			PORTH13 = 0x05AAA07D,
			PORTH14 = 0x05AAA07E,
			PORTH15 = 0x05AAA07F
		}kSPI_NSS_SOFT_Pin;
	}kSPI_NSS_SOFT;

	typedef struct
	{
		kSPI_SPI1_NSS Hard;
		kSPI_NSS_SOFT Soft;
	}kSPI_SPI1_NSS_SELECT;

	typedef struct
	{
		kSPI_SPI2_NSS Hard;
		kSPI_NSS_SOFT Soft;
	}kSPI_SPI2_NSS_SELECT;

	typedef struct
	{
		kSPI_SPI3_NSS Hard;
		kSPI_NSS_SOFT Soft;
	}kSPI_SPI3_NSS_SELECT;

	typedef struct
	{
		kSPI_SPI4_NSS Hard;
		kSPI_NSS_SOFT Soft;
	}kSPI_SPI4_NSS_SELECT;

	typedef struct
	{
		kSPI_SPI5_NSS Hard;
		kSPI_NSS_SOFT Soft;
	}kSPI_SPI5_NSS_SELECT;

	typedef struct
	{
		kSPI_SPI6_NSS Hard;
		kSPI_NSS_SOFT Soft;
	}kSPI_SPI6_NSS_SELECT;

	typedef struct
	{
		kSPI_SPI6_SLAVE_SELECT_SELECT_SELECT Master;
		kSPI_SPI6_MASTER_SELECT_SELECT_SELECT Slave;
		kSPI_SPI6_MISO MISO;
		kSPI_SPI6_MOSI MOSI;
		kSPI_SPI6_SCK  SCK;
		kSPI_SPI6_NSS_SELECT NSS;
	}kSPI_SPI6;


#endif


#pragma endregion PLATFORM_DEPENDED_STRUCTS

	class kSPI
	{
		public:

			static const kSPI_SPI1 * spi1;
			static const kSPI_SPI_NSS *NSS;
			static const kSPI_MASTER_SOFT_SELECT_SELECT_SELECT * Master;
			static const kSPI_SLAVE_SOFT_SELECT_SELECT_SELECT * Slave;


	};

	class kSPIDeviceHardware
	{
		private:



		public:

			kPin NSS;
			SPI_TypeDef * spi;



			kSPIDeviceHardware(void);
			kSPIDeviceHardware& operator = (unsigned int pwmHard);
			kSPIDeviceHardware& operator = (kSPI_SPI_NSS::kSPI_SPI_NSS_PIN nss_pin);

	};

	class kSPIDevice
	{

		public:

			kSPIDeviceHardware hardware;
			void run(unsigned int sck_freq);

			void write(unsigned short int BytesToWrite,unsigned char * DataBuffer);
			void write(unsigned char Byte);
			void read(unsigned short int BytesToRead,unsigned char * ReadDataBuffer);
			unsigned char read(void);
			void select(void);
			void deselect(void);
	};



#endif
