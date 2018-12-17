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

#ifndef __kSERIALDEFS_H
#define __kSERIALDEFS_H

#if (kLib_config_PLATFORM == kLib_STM32F427xx)

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


#endif


#endif  //End of __kSERIALDEFS_H
