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



#ifndef __kSerial_H
#define __kSerial_H

	class kSerial;

	/*
	 * Includes
	 */

	#include "kConfig.h"
	#include "kString.h"
	#include "kSystem.h"
	#include "kMath.h"
	#include "kPort.h"

	#include "stm32f4xx_usart.h"
	#include "stm32f4xx_rcc.h"

	#define kSerial_rxBuffer_size 512

// region PLATFORM_DEPENDED_STRUCTS

#if (kLib_config_PLATFORM == kLib_STM32F411xx)

	typedef struct
	{
		typedef enum
		{
			PORTA10 = 0x0C22270A,
			PORTB3  = 0x0C222713,
			PORTB7  = 0x0C222717
		}kSerial_USART1_RX_Pin;
	}kSerial_USART1_RX;

	typedef struct
	{
		typedef enum
		{
			PORTA9  = 0x0C222709,
			PORTA15 = 0x0C22270F,
			PORTB6  = 0x0C222716
		}kSerial_USART1_TX_Pin;
	}kSerial_USART1_TX;

	typedef struct
	{
		typedef enum
		{
			PORTA3  = 0x0988A703,
			PORTD6  = 0x0988A736
		}kSerial_USART2_RX_Pin;
	}kSerial_USART2_RX;

	typedef struct
	{
		typedef enum
		{
			PORTA2  = 0x0988A702,
			PORTD5  = 0x0988A735
		}kSerial_USART2_TX_Pin;
	}kSerial_USART2_TX;

	typedef struct
	{
		typedef enum
		{
			PORTA12 = 0x0D22A80C,
			PORTC7  = 0x0D22A827
		}kSerial_USART6_RX_Pin;
	}kSerial_USART6_RX;

	typedef struct
	{
		typedef enum
		{
			PORTA11 = 0x0D22A80B,
			PORTC6  = 0x0D22A826
		}kSerial_USART6_TX_Pin;
	}kSerial_USART6_TX;

	typedef struct
	{
		kSerial_USART1_RX RX;
		kSerial_USART1_TX TX;
	}kSerial_USART1;

	typedef struct
	{
		kSerial_USART2_RX RX;
		kSerial_USART2_TX TX;
	}kSerial_USART2;

	typedef struct
	{
		kSerial_USART6_RX RX;
		kSerial_USART6_TX TX;
	}kSerial_USART6;


#endif
#if (kLib_config_PLATFORM == kLib_STM32F429xx)

	typedef struct
	{
		typedef enum
		{
			PORTA1  = 0x0B89A801,
			PORTC11 = 0x0B89A82B
		}kSerial_UART4_RX_Pin;
	}kSerial_UART4_RX;

	typedef struct
	{
		typedef enum
		{
			PORTA0  = 0x0B89A800,
			PORTC10 = 0x0B89A82A
		}kSerial_UART4_TX_Pin;
	}kSerial_UART4_TX;

	typedef struct
	{
		typedef enum
		{
			PORTD2  = 0x0C8A2832
		}kSerial_UART5_RX_Pin;
	}kSerial_UART5_RX;

	typedef struct
	{
		typedef enum
		{
			PORTC12 = 0x0C8A282C
		}kSerial_UART5_TX_Pin;
	}kSerial_UART5_TX;

	typedef struct
	{
		typedef enum
		{
			PORTE7  = 0x0ECF2847,
			PORTF6  = 0x0ECF2856
		}kSerial_UART7_RX_Pin;
	}kSerial_UART7_RX;

	typedef struct
	{
		typedef enum
		{
			PORTE8  = 0x0ECF2848,
			PORTF7  = 0x0ECF2857
		}kSerial_UART7_TX_Pin;
	}kSerial_UART7_TX;

	typedef struct
	{
		typedef enum
		{
			PORTE0  = 0x0FCFA840
		}kSerial_UART8_RX_Pin;
	}kSerial_UART8_RX;

	typedef struct
	{
		typedef enum
		{
			PORTE1  = 0x0FCFA841
		}kSerial_UART8_TX_Pin;
	}kSerial_UART8_TX;

	typedef struct
	{
		typedef enum
		{
			PORTA10 = 0x0C22270A,
			PORTB7  = 0x0C222717
		}kSerial_USART1_RX_Pin;
	}kSerial_USART1_RX;

	typedef struct
	{
		typedef enum
		{
			PORTA9  = 0x0C222709,
			PORTB6  = 0x0C222716
		}kSerial_USART1_TX_Pin;
	}kSerial_USART1_TX;

	typedef struct
	{
		typedef enum
		{
			PORTA3  = 0x0988A703,
			PORTD6  = 0x0988A736
		}kSerial_USART2_RX_Pin;
	}kSerial_USART2_RX;

	typedef struct
	{
		typedef enum
		{
			PORTA2  = 0x0988A702,
			PORTD5  = 0x0988A735
		}kSerial_USART2_TX_Pin;
	}kSerial_USART2_TX;

	typedef struct
	{
		typedef enum
		{
			PORTB11 = 0x0A89271B,
			PORTC11 = 0x0A89272B,
			PORTD9  = 0x0A892739
		}kSerial_USART3_RX_Pin;
	}kSerial_USART3_RX;

	typedef struct
	{
		typedef enum
		{
			PORTB10 = 0x0A89271A,
			PORTC10 = 0x0A89272A,
			PORTD8  = 0x0A892738
		}kSerial_USART3_TX_Pin;
	}kSerial_USART3_TX;

	typedef struct
	{
		typedef enum
		{
			PORTC7  = 0x0D22A827,
			PORTG9  = 0x0D22A869
		}kSerial_USART6_RX_Pin;
	}kSerial_USART6_RX;

	typedef struct
	{
		typedef enum
		{
			PORTC6  = 0x0D22A826,
			PORTG14 = 0x0D22A86E
		}kSerial_USART6_TX_Pin;
	}kSerial_USART6_TX;

	typedef struct
	{
		kSerial_UART4_RX RX;
		kSerial_UART4_TX TX;
	}kSerial_UART4;

	typedef struct
	{
		kSerial_UART5_RX RX;
		kSerial_UART5_TX TX;
	}kSerial_UART5;

	typedef struct
	{
		kSerial_UART7_RX RX;
		kSerial_UART7_TX TX;
	}kSerial_UART7;

	typedef struct
	{
		kSerial_UART8_RX RX;
		kSerial_UART8_TX TX;
	}kSerial_UART8;

	typedef struct
	{
		kSerial_USART1_RX RX;
		kSerial_USART1_TX TX;
	}kSerial_USART1;

	typedef struct
	{
		kSerial_USART2_RX RX;
		kSerial_USART2_TX TX;
	}kSerial_USART2;

	typedef struct
	{
		kSerial_USART3_RX RX;
		kSerial_USART3_TX TX;
	}kSerial_USART3;

	typedef struct
	{
		kSerial_USART6_RX RX;
		kSerial_USART6_TX TX;
	}kSerial_USART6;


#endif
#if (kLib_config_PLATFORM == kLib_STM32L053xx)

	typedef struct
	{
		typedef enum
		{
			PORTB11 = 0x0A89241B,
			PORTC5  = 0x0A892225,
			PORTC11 = 0x0A89202B
		}kSerial_LPUART1_RX_Pin;
	}kSerial_LPUART1_RX;

	typedef struct
	{
		typedef enum
		{
			PORTB10 = 0x0A89241A,
			PORTC4  = 0x0A892224,
			PORTC10 = 0x0A89202A
		}kSerial_LPUART1_TX_Pin;
	}kSerial_LPUART1_TX;

	typedef struct
	{
		typedef enum
		{
			PORTA10 = 0x0E67240A,
			PORTB7  = 0x0E672017
		}kSerial_USART1_RX_Pin;
	}kSerial_USART1_RX;

	typedef struct
	{
		typedef enum
		{
			PORTA9  = 0x0E672409,
			PORTB6  = 0x0E672016
		}kSerial_USART1_TX_Pin;
	}kSerial_USART1_TX;

	typedef struct
	{
		typedef enum
		{
			PORTA3  = 0x0988A403,
			PORTA15 = 0x0988A40F
		}kSerial_USART2_RX_Pin;
	}kSerial_USART2_RX;

	typedef struct
	{
		typedef enum
		{
			PORTA2  = 0x0988A402,
			PORTA14 = 0x0988A40E
		}kSerial_USART2_TX_Pin;
	}kSerial_USART2_TX;

	typedef struct
	{
		kSerial_LPUART1_RX RX;
		kSerial_LPUART1_TX TX;
	}kSerial_LPUART1;

	typedef struct
	{
		kSerial_USART1_RX RX;
		kSerial_USART1_TX TX;
	}kSerial_USART1;

	typedef struct
	{
		kSerial_USART5_RX RX;
		kSerial_USART5_TX TX;
	}kSerial_USART5;

	typedef struct
	{
		kSerial_USART4_RX RX;
		kSerial_USART4_TX TX;
	}kSerial_USART4;

	typedef struct
	{
		kSerial_USART2_RX RX;
		kSerial_USART2_TX TX;
	}kSerial_USART2;


#endif


// endregion PLATFORM_DEPENDED_STRUCTS

	class kSerial;

 	class kSerial {


 		protected:

			unsigned int k_timeout;
			char k_terminator;
			unsigned char dataCounter;
			bool useTerminator;


			unsigned long long k_precision;

			char rxBuffer[kSerial_rxBuffer_size];
			unsigned short int rx_buffer_size;
			unsigned short int rx_buffer_read_pointer;
			unsigned short int rx_buffer_write_pointer;

			void attachUSART(void);

		public:


			class kSerialHardware
			{
				friend class kSerial;

				public:

					USART_TypeDef * usart;
					kSerialHardware& operator = (unsigned int pwmHard);

			};

 			kSerialHardware hardware;

 			static const char* endl;

// region USARTS_DECLARATIONS

		#if (kLib_config_PLATFORM == kLib_STM32F411xx)

			static const kSerial_USART1  * usart1;
			static const kSerial_USART2  * usart2;
			static const kSerial_USART6  * usart6;

		#endif

		#if (kLib_config_PLATFORM == kLib_STM32F429xx)

			static const kSerial_UART4  * uart4;
			static const kSerial_UART5  * uart5;
			static const kSerial_UART7  * uart7;
			static const kSerial_UART8  * uart8;
			static const kSerial_USART1  * usart1;
			static const kSerial_USART2  * usart2;
			static const kSerial_USART3  * usart3;
			static const kSerial_USART6  * usart6;

		#endif

		#if (kLib_config_PLATFORM == kLib_STM32L053xx)

			static const kSerial_LPUART1  * lpuart1;
			static const kSerial_USART1  * usart1;
			static const kSerial_USART5  * usart5;
			static const kSerial_USART4  * usart4;
			static const kSerial_USART2  * usart2;

		#endif



// endregion USARTS_DECLARATIONS


 			//constructors
 			kSerial(void);


			void run(unsigned int BaudRate);
			void write(void * data, unsigned int bytes) const;


			void timeout(unsigned int ticks);
			void precision(unsigned char precision_points);
			void terminator(unsigned char character);

 			unsigned short int newBytesAvailable(void);
			char getChar(void);
			char readByte(void);
			unsigned short int readAll(char * buffer);

			unsigned char newDataAvailable(void);
			unsigned short int readData(char * buffer);
			unsigned short int readAllData(char * buffer);

			friend const kSerial& operator <<(const kSerial &serial,const char * String);
			friend const kSerial& operator <<(const kSerial &serial,char chr);
			friend const kSerial& operator <<(const kSerial &serial,int number);
			friend const kSerial& operator <<(const kSerial &serial,unsigned int number);
			friend const kSerial& operator <<(const kSerial &serial,float number);
			friend const kSerial& operator <<(const kSerial &serial,const kString & str);
			friend const kSerial& operator <<(const kSerial &serial,const kVector3 & v);
			friend const kSerial& operator <<(const kSerial &serial,const kQuaternion & q);
			friend const kSerial& operator <<(const kSerial &serial,const kAxisAngle & axis_angle);


	};




#endif
