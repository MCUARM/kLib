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

#ifndef __kSI2CDEFS_H
#define __kSI2CDEFS_H

#if (kLib_config_PLATFORM == kLib_STM32F427xx)

	typedef struct
	{
		typedef enum
		{
			PORTB7  = 0x058AE417,
			PORTB9  = 0x058AE419
		}kI2C_I2C1_SDA_Pin;
	}kSPI_I2C1_SDA;

	typedef struct
	{
		typedef enum
		{
			PORTB6  = 0x058AE416,
			PORTB8  = 0x058AE418
		}kI2C_I2C1_SCL_Pin;
	}kSPI_I2C1_SCL;

	typedef struct
	{
		typedef enum
		{
			PORTB11 = 0x068B641B,
			PORTF0  = 0x068B6450,
			PORTH5  = 0x068B6475
		}kI2C_I2C2_SDA_Pin;
	}kSPI_I2C2_SDA;

	typedef struct
	{
		typedef enum
		{
			PORTB10 = 0x068B641A,
			PORTF1  = 0x068B6451,
			PORTH4  = 0x068B6474
		}kI2C_I2C2_SCL_Pin;
	}kSPI_I2C2_SCL;

	typedef struct
	{
		typedef enum
		{
			PORTC9  = 0x078BE429,
			PORTH8  = 0x078BE478
		}kI2C_I2C3_SDA_Pin;
	}kSPI_I2C3_SDA;

	typedef struct
	{
		typedef enum
		{
			PORTA8  = 0x078BE408,
			PORTH7  = 0x078BE477
		}kI2C_I2C3_SCL_Pin;
	}kSPI_I2C3_SCL;


#endif
#if (kLib_config_PLATFORM == kLib_STM32F429xx)

	typedef struct
	{
		typedef enum
		{
			PORTB7  = 0x058AE417,
			PORTB9  = 0x058AE419
		}kI2C_I2C1_SDA_Pin;
	}kSPI_I2C1_SDA;

	typedef struct
	{
		typedef enum
		{
			PORTB6  = 0x058AE416,
			PORTB8  = 0x058AE418
		}kI2C_I2C1_SCL_Pin;
	}kSPI_I2C1_SCL;

	typedef struct
	{
		typedef enum
		{
			PORTB11 = 0x068B641B,
			PORTF0  = 0x068B6450,
			PORTH5  = 0x068B6475
		}kI2C_I2C2_SDA_Pin;
	}kSPI_I2C2_SDA;

	typedef struct
	{
		typedef enum
		{
			PORTB10 = 0x068B641A,
			PORTF1  = 0x068B6451,
			PORTH4  = 0x068B6474
		}kI2C_I2C2_SCL_Pin;
	}kSPI_I2C2_SCL;

	typedef struct
	{
		typedef enum
		{
			PORTC9  = 0x078BE429,
			PORTH8  = 0x078BE478
		}kI2C_I2C3_SDA_Pin;
	}kSPI_I2C3_SDA;

	typedef struct
	{
		typedef enum
		{
			PORTA8  = 0x078BE408,
			PORTH7  = 0x078BE477
		}kI2C_I2C3_SCL_Pin;
	}kSPI_I2C3_SCL;


#endif


#endif  //End of __kSI2CDEFS_H
