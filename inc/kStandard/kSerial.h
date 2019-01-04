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


	typedef struct
	{
		typedef enum
		{
			_9600 = 9600,
			_115200 = 115200
		}kSerial_BaudRate_enum;
	}kSerial_BaudRate_struct;

	typedef struct
	{
		typedef enum
		{
			RX_NotEmpty = 32,
			TX_Empty = 128
		}kSerial_Interrupt_enum;
	}kSerial_Interrupt_struct;

	typedef struct
	{
		typedef enum
		{
			Reception = 64,
			Transmission = 128
		}kSerial_DMA_enum;
	}kSerial_DMA_struct;

	class kSerialHardware
	{
		private:

			friend class kSerial;
			USART_TypeDef * usart;

		public:

			kSerialHardware& operator = (uint32_t hard_code);
			kSerialHardware& operator , (uint32_t hard_code);

	};

 	class kSerial {


		public:

 			kSerialHardware hardware;
 			static const char* endl;
 			static kSerial_BaudRate_struct * BaudRate;
 			static kSerial_Interrupt_struct * USART_Interrupt;
 			static kSerial_DMA_struct * DMA_mode;

// region USARTS_DECLARATIONS

		#if (kLib_config_PLATFORM == kLib_STM32F411xx)

			static const kSerial_USART1  * _USART1;
			static const kSerial_USART2  * _USART2;
			static const kSerial_USART6  * _USART6;

		#endif

		#if (kLib_config_PLATFORM == kLib_STM32F429xx)

			static const kSerial_UART4  * _UART4;
			static const kSerial_UART5  * _UART5;
			static const kSerial_UART7  * _UART7;
			static const kSerial_UART8  * _UART8;
			static const kSerial_USART1  * _USART1;
			static const kSerial_USART2  * _USART2;
			static const kSerial_USART3  * _USART3;
			static const kSerial_USART6  * _USART6;

		#endif

		#if (kLib_config_PLATFORM == kLib_STM32L053xx)

			static const kSerial_LPUART1  * _LPUART1;
			static const kSerial_USART1  * _USART1;
			static const kSerial_USART5  * _USART5;
			static const kSerial_USART4  * _USART4;
			static const kSerial_USART2  * _USART2;

		#endif



// endregion USARTS_DECLARATIONS


 			//constructors
 			kSerial(void);

 			void enableInterrupt(uint16_t interrupt_flags);
 			void disableInterrupt(uint16_t interrupt_flags);

 			void useDMA(uint16_t dma_flags);



			void run(uint32_t BaudRate);
			void write(uint8_t byte);
			void write(const void * data);
			void write(const void * data, uint32_t bytes);

			uint8_t readByte(void);
			bool newByteAvailable(void);

 };




#endif
