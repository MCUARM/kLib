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
#ifndef __kSPIDevice_H
#define __kSPIDevice_H

	#include "stm32f4xx_spi.h"
	#include "kSystem.h"

	class kSPIDevice;
	class kSPIDeviceHardware;

	typedef struct
	{
		typedef enum
		{
			PORTA6 = 0x04662506,
			PORTB4 = 0x04662514
		}kSPI_SPI1_MISO_Pin;
	}kSPI_SPI1_MISO;

	typedef struct
	{
		typedef enum
		{
			PORTA7 = 0x04662507,
			PORTB5 = 0x04662515
		}kSPI_SPI1_MOSI_Pin;
	}kSPI_SPI1_MOSI;

	typedef struct
	{
		typedef enum
		{
			PORTA5 = 0x04662505,
			PORTB3 = 0x04662513
		}kSPI_SPI1_SCK_Pin;
	}kSPI_SPI1_SCK;

	typedef struct
	{
		typedef enum
		{
			kMACRO_GET_ALL_PORTS_PINS_ENUM
		}kSPI_SPI_NSS_PIN;
	}kSPI_SPI_NSS;


	typedef struct
	{
		kSPI_SPI1_MISO MISO;
		kSPI_SPI1_MOSI MOSI;
		kSPI_SPI1_SCK SCK;

	}kSPI_SPI1;


	//spi.hardware = kSPI::Master.NSS_Soft.MSB_First.SCK_Idle_High.DataCapture_1Edge;


	typedef struct
	{
		typedef enum
		{
			DataCapture_1Edge = 0x6C660000,
			DataCapture_2Edge = 0x7C660000
		}kSPI_MASTER_SOFT_MSB_HIGH_SELECT;
	}kSPI_MASTER_SOFT_MSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{
			DataCapture_1Edge = 0x4C660000,
			DataCapture_2Edge = 0x5C660000
		}kSPI_MASTER_SOFT_MSB_LOW_SELECT;
	}kSPI_MASTER_SOFT_MSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{
			DataCapture_1Edge = 0xEC660000,
			DataCapture_2Edge = 0xFC660000
		}kSPI_MASTER_SOFT_LSB_HIGH_SELECT;
	}kSPI_MASTER_SOFT_LSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{
			DataCapture_1Edge = 0xCC660000,
			DataCapture_2Edge = 0xDC660000
		}kSPI_MASTER_SOFT_LSB_LOW_SELECT;
	}kSPI_MASTER_SOFT_LSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{
			DataCapture_1Edge = 0x2C660000,
			DataCapture_2Edge = 0x3C660000
		}kSPI_SLAVE_SOFT_MSB_HIGH_SELECT;
	}kSPI_SLAVE_SOFT_MSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{
			DataCapture_1Edge = 0x0C660000,
			DataCapture_2Edge = 0x1C660000
		}kSPI_SLAVE_SOFT_MSB_LOW_SELECT;
	}kSPI_SLAVE_SOFT_MSB_LOW_EDGE;

	typedef struct
	{
		typedef enum
		{
			DataCapture_1Edge = 0xAC660000,
			DataCapture_2Edge = 0xBC660000
		}kSPI_SLAVE_SOFT_LSB_HIGH_SELECT;
	}kSPI_SLAVE_SOFT_LSB_HIGH_EDGE;

	typedef struct
	{
		typedef enum
		{
			DataCapture_1Edge = 0x8C660000,
			DataCapture_2Edge = 0x9C660000
		}kSPI_SLAVE_SOFT_LSB_LOW_SELECT;
	}kSPI_SLAVE_SOFT_LSB_LOW_EDGE;

	typedef struct
	{
		kSPI_MASTER_SOFT_MSB_HIGH_EDGE SCK_IdleHigh;
		kSPI_MASTER_SOFT_MSB_LOW_EDGE SCK_IdleLow;
	}kSPI_MASTER_SOFT_MSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_MASTER_SOFT_LSB_HIGH_EDGE SCK_IdleHigh;
		kSPI_MASTER_SOFT_LSB_LOW_EDGE SCK_IdleLow;
	}kSPI_MASTER_SOFT_LSB_SELECT_SELECT;


	typedef struct
	{
		kSPI_SLAVE_SOFT_MSB_HIGH_EDGE SCK_IdleHigh;
		kSPI_SLAVE_SOFT_MSB_LOW_EDGE SCK_IdleLow;
	}kSPI_SLAVE_SOFT_MSB_SELECT_SELECT;

	typedef struct
	{
		kSPI_SLAVE_SOFT_LSB_HIGH_EDGE SCK_IdleHigh;
		kSPI_SLAVE_SOFT_LSB_LOW_EDGE SCK_IdleLow;
	}kSPI_SLAVE_SOFT_LSB_SELECT_SELECT;



	typedef struct
	{
		kSPI_MASTER_SOFT_MSB_SELECT_SELECT MSB_First;
		kSPI_MASTER_SOFT_LSB_SELECT_SELECT LSB_First;
	}kSPI_MASTER_SOFT_SELECT_SELECT_SELECT;


	typedef struct
	{
		kSPI_SLAVE_SOFT_MSB_SELECT_SELECT MSB_First;
		kSPI_SLAVE_SOFT_LSB_SELECT_SELECT LSB_First;
	}kSPI_SLAVE_SOFT_SELECT_SELECT_SELECT;


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
