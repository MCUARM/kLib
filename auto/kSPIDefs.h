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
			PORTA6 = 0x4662506
		}kSPI_SPI1_MISO_Pin;
	}kSPI_SPI1_MISO;

	typedef struct
	{
		typedef enum
		{
			PORTA7 = 0x4662507
		}kSPI_SPI1_MOSI_Pin;
	}kSPI_SPI1_MOSI;

	typedef struct
	{
		typedef enum
		{
			PORTA5 = 0x4662505
		}kSPI_SPI1_SCK_Pin;
	}kSPI_SPI1_SCK;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0xc660000,
			DataCapture_2Edge = 0xc660001
		}kSPI_SPI1_SLAVE_MSB_LOW_SELECT;
	}kSPI_SPI1_SLAVE_MSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0xc660002,
			DataCapture_2Edge = 0xc660003
		}kSPI_SPI1_SLAVE_MSB_HIGH_SELECT;
	}kSPI_SPI1_SLAVE_MSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0xc660008,
			DataCapture_2Edge = 0xc660009
		}kSPI_SPI1_SLAVE_LSB_LOW_SELECT;
	}kSPI_SPI1_SLAVE_LSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0xc66000a,
			DataCapture_2Edge = 0xc66000b
		}kSPI_SPI1_SLAVE_LSB_HIGH_SELECT;
	}kSPI_SPI1_SLAVE_LSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0xc660004,
			DataCapture_2Edge = 0xc660005
		}kSPI_SPI1_MASTER_MSB_LOW_SELECT;
	}kSPI_SPI1_MASTER_MSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0xc660006,
			DataCapture_2Edge = 0xc660007
		}kSPI_SPI1_MASTER_MSB_HIGH_SELECT;
	}kSPI_SPI1_MASTER_MSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0xc66000c,
			DataCapture_2Edge = 0xc66000d
		}kSPI_SPI1_MASTER_LSB_LOW_SELECT;
	}kSPI_SPI1_MASTER_LSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{

			DataCapture_1Edge = 0xc66000e,
			DataCapture_2Edge = 0xc66000f
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
		kSPI_SPI1_SLAVE_SELECT_SELECT_SELECT Master;
		kSPI_SPI1_MASTER_SELECT_SELECT_SELECT Slave;
	}kSPI_SPI1;


#endif
#if (kLib_config_PLATFORM == kLib_STM32F427xx)


#endif


#endif  //End of __kSPIDEFS_H
