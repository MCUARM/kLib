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



#ifndef __kPWM_H
#define __kPWM_H



	/*
	 * Includes
	 */

	#include "kConfig.h"
	#include "kSystem.h"
	#include "misc.h"

	extern unsigned int kSystem_ms_downcounter;

	class kRCChannel;

	typedef struct
	{
		uint32_t last_kSystem_timer_value;
		uint32_t last_SysTick_value;
		uint32_t kSystem_timer_val;
		uint32_t SysTick_val;
		uint32_t temp_ms;
		uint32_t temp_us;
		uint32_t pwm_input_register;
		uint32_t last_update_kSystem_timer_value;
	}kPWM_EXTI_data_storage;


#if (kLib_config_PLATFORM == kLib_STM32F429xx)

	typedef struct
	{
		typedef enum
		{
			PORTA8 = 0x18202108,	// WORK
			PORTE9 = 0x18202149		// WORK
		}kPWM_Timer1_OC1_Pin;

	}kPWM_OC1_Timer1;

	typedef struct
	{
		typedef enum
		{
			PORTA9  = 0x50202109,	// WORK
			PORTE11 = 0x5020214B	// WORK
		}kPWM_Timer1_OC2_Pin;

	}kPWM_OC2_Timer1;

	typedef struct
	{
		typedef enum
		{
			PORTA10 = 0x2820210A,	// WORK
			PORTE13 = 0x2820214D	// WORK
		}kPWM_Timer1_OC3_Pin;

	}kPWM_OC3_Timer1;

	typedef struct
	{
		typedef enum
		{
			PORTA11 = 0x6020210B,	// WORK
			PORTE14 = 0x6020214E	// WORK
		}kPWM_Timer1_OC4_Pin;


	}kPWM_OC4_Timer1;

	typedef struct
	{
		kPWM_OC1_Timer1 OC1;
		kPWM_OC2_Timer1 OC2;
		kPWM_OC3_Timer1 OC3;
		kPWM_OC4_Timer1 OC4;

	}kPWM_Timer1;



	typedef struct
	{
		typedef enum
		{
			PORTA0 =  0x18002100,	// WORK
			PORTA5 =  0x18002105,	// WORK
			PORTA15 = 0x1800210F	// WORK
		}kPWM_Timer2_OC1_Pin;

	}kPWM_OC1_Timer2;

	typedef struct
	{
		typedef enum
		{
			PORTA1 =  0x50002101,	// DONT WORK (TESTED ON STM32F429-DISCOVERY)
			PORTB3 =  0x50002113	// WORK
		}kPWM_Timer2_OC2_Pin;

	}kPWM_OC2_Timer2;

	typedef struct
	{
		typedef enum
		{
			PORTA2 =  0x28002102,	// DONT WORK (TESTED ON STM32F429-DISCOVERY)
			PORTB10 = 0x2800211A	// WORK
		}kPWM_Timer2_OC3_Pin;

	}kPWM_OC3_Timer2;

	typedef struct
	{
		typedef enum
		{
			PORTA3  = 0x60002103,	// WORK
			PORTB11 = 0x6000211B	// WORK
		}kPWM_Timer2_OC4_Pin;

	}kPWM_OC4_Timer2;

	typedef struct
	{
		kPWM_OC1_Timer2 OC1;
		kPWM_OC2_Timer2 OC2;
		kPWM_OC3_Timer2 OC3;
		kPWM_OC4_Timer2 OC4;

	}kPWM_Timer2;


		typedef struct
		{
			typedef enum
			{
				PORTA6 = 0x1900A206,	// WORK
				PORTB4 = 0x1900A214,	// WORK
				PORTC6 = 0x1900A226		// WORK
			}kPWM_Timer3_OC1_Pin;

		}kPWM_OC1_Timer3;

		typedef struct
		{
			typedef enum
			{
				PORTA7 = 0x5100A207,	// WORK
				PORTB5 = 0x5100A215,	// WORK
				PORTC7 = 0x5100A227		// WORK
			}kPWM_Timer3_OC2_Pin;

		}kPWM_OC2_Timer3;

		typedef struct
		{
			typedef enum
			{
				PORTB0 = 0x2900A210,	// WORK
				PORTC8 = 0x2900A228		// WORK
			}kPWM_Timer3_OC3_Pin;

		}kPWM_OC3_Timer3;

		typedef struct
		{
			typedef enum
			{
				PORTB1 = 0x6100A211,	// WORK
				PORTC9 = 0x6100A229		// WORK
			}kPWM_Timer3_OC4_Pin;

		}kPWM_OC4_Timer3;

		typedef struct
		{
			kPWM_OC1_Timer3 OC1;
			kPWM_OC2_Timer3 OC2;
			kPWM_OC3_Timer3 OC3;
			kPWM_OC4_Timer3 OC4;

		}kPWM_Timer3;


		typedef struct
		{
			typedef enum
			{
				PORTB6 =  0x1A012216,	// WORK
				PORTD12 = 0x1A01223C	// WORK
			}kPWM_Timer4_OC1_Pin;

		}kPWM_OC1_Timer4;

		typedef struct
		{
			typedef enum
			{
				PORTB7 =  0x52012217,	// WORK
				PORTD13 = 0x5201223D	// WORK
			}kPWM_Timer4_OC2_Pin;

		}kPWM_OC2_Timer4;

		typedef struct
		{
			typedef enum
			{
				PORTB8 =  0x2A012218,	// WORK
				PORTD14 = 0x2A01223E	// WORK
			}kPWM_Timer4_OC3_Pin;

		}kPWM_OC3_Timer4;

		typedef struct
		{
			typedef enum
			{
				PORTB9  = 0x62012219,	// WORK
				PORTD15 = 0x6201223F	// WORK
			}kPWM_Timer4_OC4_Pin;

		}kPWM_OC4_Timer4;

		typedef struct
		{
			kPWM_OC1_Timer4 OC1;
			kPWM_OC2_Timer4 OC2;
			kPWM_OC3_Timer4 OC3;
			kPWM_OC4_Timer4 OC4;

		}kPWM_Timer4;



		typedef struct
		{
			typedef enum
			{
				PORTA0  = 0x1B01A200,	// WORK
				PORTH10 = 0x1B01A27A	// NOT TESTED
			}kPWM_Timer5_OC1_Pin;

		}kPWM_OC1_Timer5;

		typedef struct
		{
			typedef enum
			{
				PORTA1  = 0x5301A201,	// DONT WORK (TESTED ON STM32F429-DISCOVERY)
				PORTH11 = 0x5301A27B	// NOT TESTED
			}kPWM_Timer5_OC2_Pin;

		}kPWM_OC2_Timer5;

		typedef struct
		{
			typedef enum
			{
				PORTA2  = 0x2B01A202,	// DONT WORK (TESTED ON STM32F429-DISCOVERY)
				PORTH12 = 0x2B01A27C	// NOT TESTED
			}kPWM_Timer5_OC3_Pin;

		}kPWM_OC3_Timer5;

		typedef struct
		{
			typedef enum
			{
				PORTA3 = 0x6301A203,	// WORK
				PORTI0 = 0x6301A280		// NOT TESTED
			}kPWM_Timer5_OC4_Pin;

		}kPWM_OC4_Timer5;

		typedef struct
		{
			kPWM_OC1_Timer5 OC1;
			kPWM_OC2_Timer5 OC2;
			kPWM_OC3_Timer5 OC3;
			kPWM_OC4_Timer5 OC4;

		}kPWM_Timer5;



		typedef struct
		{
			typedef enum
			{
				PORTC6 = 0x1920A326,	// DONT WORK (TESTED ON STM32F429-DISCOVERY)
				PORTI5 = 0x1920A385		// NOT TESTED
			}kPWM_Timer8_OC1_Pin;

		}kPWM_OC1_Timer8;

		typedef struct
		{
			typedef enum
			{
				PORTC7 = 0x5120A327,	// DONT WORK (TESTED ON STM32F429-DISCOVERY)
				PORTI6 = 0x5120A386		// NOT TESTED
			}kPWM_Timer8_OC2_Pin;

		}kPWM_OC2_Timer8;

		typedef struct
		{
			typedef enum
			{
				PORTC8 = 0x2920A328,	// DONT WORK (TESTED ON STM32F429-DISCOVERY)
				PORTI7 = 0x2920A387		// NOT TESTED
			}kPWM_Timer8_OC3_Pin;

		}kPWM_OC3_Timer8;

		typedef struct
		{
			typedef enum
			{
				PORTC9 = 0x6120A329,	// DONT WORK (TESTED ON STM32F429-DISCOVERY)
				PORTI2 = 0x6120A382		// NOT TESTED
			}kPWM_Timer8_OC4_Pin;

		}kPWM_OC4_Timer8;

		typedef struct
		{
			kPWM_OC1_Timer8 OC1;
			kPWM_OC2_Timer8 OC2;
			kPWM_OC3_Timer8 OC3;
			kPWM_OC4_Timer8 OC4;

		}kPWM_Timer8;



		typedef struct
		{
			typedef enum
			{
				PORTA2 = 0x18A82302,	// DONT WORK (TESTED ON STM32F429-DISCOVERY)
				PORTE5 = 0x18A82345		// WORK
			}kPWM_Timer9_OC1_Pin;

		}kPWM_OC1_Timer9;

		typedef struct
		{
			typedef enum
			{
				PORTA3 = 0x50A82303,	// WORK
				PORTE6 = 0x50A82346		// WORK
			}kPWM_Timer9_OC2_Pin;

		}kPWM_OC2_Timer9;

		typedef struct
		{
			kPWM_OC1_Timer9 OC1;
			kPWM_OC2_Timer9 OC2;

		}kPWM_Timer9;

		typedef struct
		{
			typedef enum
			{
				PORTF6 = 0x19A8A356,	// WORK
				PORTB8 = 0x19A8A318		// WORK
			}kPWM_Timer10_OC1_Pin;

		}kPWM_OC1_Timer10;

		typedef struct
		{
			kPWM_OC1_Timer10 OC1;
		}kPWM_Timer10;



		typedef struct
		{
			typedef enum
			{
				PORTF7 = 0x1AA92357,	// WORK
				PORTB9 = 0x1AA92319		// WORK
			}kPWM_Timer11_OC1_Pin;

		}kPWM_OC1_Timer11;

		typedef struct
		{
			kPWM_OC1_Timer11 OC1;
		}kPWM_Timer11;



		typedef struct
		{
			typedef enum
			{
				PORTH6  = 0x1E032976,	// NOT TESTED
				PORTB14 = 0x1E03291E	// DONT WORK (TESTED ON STM32F429-DISCOVERY)
			}kPWM_Timer12_OC1_Pin;

		}kPWM_OC1_Timer12;

		typedef struct
		{
			typedef enum
			{
				PORTH9  = 0x56032979,	// NOT TESTED
				PORTB15 = 0x5603291F	// DONT WORK (TESTED ON STM32F429-DISCOVERY)
			}kPWM_Timer12_OC2_Pin;

		}kPWM_OC2_Timer12;

		typedef struct
		{
			kPWM_OC1_Timer12 OC1;
			kPWM_OC2_Timer12 OC2;

		}kPWM_Timer12;

		typedef struct
		{
			typedef enum
			{
				PORTF8 = 0x1F03A958,	// DONT WORK (TESTED ON STM32F429-DISCOVERY)
				PORTA6 = 0x1F03A906		// WORK
			}kPWM_Timer13_OC1_Pin;

		}kPWM_OC1_Timer13;

		typedef struct
		{
			kPWM_OC1_Timer13 OC1;
		}kPWM_Timer13;


		typedef struct
		{
			typedef enum
			{
				PORTF9 = 0x18442959,	// DONT WORK (TESTED ON STM32F429-DISCOVERY)
				PORTA7 = 0x18442907		// WORK
			}kPWM_Timer14_OC1_Pin;

		}kPWM_OC1_Timer14;

		typedef struct
		{
			kPWM_OC1_Timer14 OC1;
		}kPWM_Timer14;


		typedef struct
		{
			typedef enum
			{
				Timer2_OC1 = 0x18002100,
				Timer5_OC1 = 0x1B01A200
			}kPWM_OUT_PORTA0_Pin;
		}kPWM_out_PORTA0;


		typedef struct
		{
			typedef enum
			{
				Timer2_OC2 = 0x50002101,
				Timer5_OC2 = 0x5301A201
			}kPWM_OUT_PORTA1_Pin;
		}kPWM_out_PORTA1;


		typedef struct
		{
			typedef enum
			{
				Timer2_OC3 = 0x28002102,
				Timer5_OC3 = 0x2B01A202,
				Timer9_OC1 = 0x18A82302
			}kPWM_OUT_PORTA2_Pin;
		}kPWM_out_PORTA2;



		typedef struct
		{
			typedef enum
			{
				Timer5_OC4 = 0x6301A203,
				Timer9_OC2 = 0x50A82303
			}kPWM_OUT_PORTA3_Pin;
		}kPWM_out_PORTA3;



		typedef struct
		{
			typedef enum
			{
				Timer2_OC1 = 0x18002105
			}kPWM_OUT_PORTA5_Pin;
		}kPWM_out_PORTA5;


		typedef struct
		{
			typedef enum
			{
				Timer3_OC1 = 0x1900A206,
				Timer13_OC1 = 0x1F03A906
			}kPWM_OUT_PORTA6_Pin;
		}kPWM_out_PORTA6;

		typedef struct
		{
			typedef enum
			{
				Timer3_OC2 = 0x5100A207,
				Timer14_OC1 = 0x18442907
			}kPWM_OUT_PORTA7_Pin;
		}kPWM_out_PORTA7;


		typedef struct
		{
			typedef enum
			{
				Timer1_OC1 = 0x18202108
			}kPWM_OUT_PORTA8_Pin;
		}kPWM_out_PORTA8;

		typedef struct
		{
			typedef enum
			{
				Timer1_OC2 = 0x50202109
			}kPWM_OUT_PORTA9_Pin;
		}kPWM_out_PORTA9;


		typedef struct
		{
			typedef enum
			{
				Timer1_OC3 = 0x2820210A
			}kPWM_OUT_PORTA10_Pin;
		}kPWM_out_PORTA10;


		typedef struct
		{
			typedef enum
			{
				Timer1_OC4 = 0x6020210B
			}kPWM_OUT_PORTA11_Pin;
		}kPWM_out_PORTA11;

		typedef struct
		{
			typedef enum
			{
				Timer2_OC1 = 0x1800210F
			}kPWM_OUT_PORTA15_Pin;
		}kPWM_out_PORTA15;


		typedef struct
		{
			typedef enum
			{
				Timer3_OC3 = 0x2900A210
			}kPWM_OUT_PORTB0_Pin;
		}kPWM_out_PORTB0;


		typedef struct
		{
			typedef enum
			{
				Timer3_OC4 = 0x6100A211
			}kPWM_OUT_PORTB1_Pin;
		}kPWM_out_PORTB1;


		typedef struct
		{
			typedef enum
			{
				Timer2_OC2 = 0x50002113
			}kPWM_OUT_PORTB3_Pin;
		}kPWM_out_PORTB3;


		typedef struct
		{
			typedef enum
			{
				Timer3_OC1 = 0x1900A214
			}kPWM_OUT_PORTB4_Pin;
		}kPWM_out_PORTB4;


		typedef struct
		{
			typedef enum
			{
				Timer3_OC2 = 0x5100A207
			}kPWM_OUT_PORTB5_Pin;
		}kPWM_out_PORTB5;

		typedef struct
		{
			typedef enum
			{
				Timer4_OC1 = 0x1A012216
			}kPWM_OUT_PORTB6_Pin;
		}kPWM_out_PORTB6;

		typedef struct
		{
			typedef enum
			{
				Timer4_OC2 = 0x52012217
			}kPWM_OUT_PORTB7_Pin;
		}kPWM_out_PORTB7;


		typedef struct
		{
			typedef enum
			{
				Timer4_OC3 = 0x2A012218,
				Timer10_OC1 = 0x19A8A318
			}kPWM_OUT_PORTB8_Pin;
		}kPWM_out_PORTB8;


		typedef struct
		{
			typedef enum
			{
				Timer4_OC4 = 0x62012219,
				Timer11_OC1 = 0x1AA92319
			}kPWM_OUT_PORTB9_Pin;
		}kPWM_out_PORTB9;

		typedef struct
		{
			typedef enum
			{
				Timer2_OC3 = 0x2800211A
			}kPWM_OUT_PORTB10_Pin;
		}kPWM_out_PORTB10;

		typedef struct
		{
			typedef enum
			{
				Timer2_OC4 = 0x6000211B
			}kPWM_OUT_PORTB11_Pin;
		}kPWM_out_PORTB11;


		typedef struct
		{
			typedef enum
			{
				Timer12_OC1 = 0x1E03291E
			}kPWM_OUT_PORTB14_Pin;
		}kPWM_out_PORTB14;

		typedef struct
		{
			typedef enum
			{
				Timer12_OC2 = 0x5603291F
			}kPWM_OUT_PORTB15_Pin;
		}kPWM_out_PORTB15;






		typedef struct
		{
			kPWM_Timer1  Timer1;
			kPWM_Timer2  Timer2;
			kPWM_Timer3  Timer3;
			kPWM_Timer4  Timer4;
			kPWM_Timer5  Timer5;
			kPWM_Timer8  Timer8;
			kPWM_Timer9  Timer9;
			kPWM_Timer10 Timer10;
			kPWM_Timer11 Timer11;
			kPWM_Timer12 Timer12;
			kPWM_Timer13 Timer13;
			kPWM_Timer14 Timer14;

			kPWM_out_PORTA0 PORTA0;
			kPWM_out_PORTA1 PORTA1;
			kPWM_out_PORTA2 PORTA2;
			kPWM_out_PORTA3 PORTA3;
			kPWM_out_PORTA5 PORTA5;
			kPWM_out_PORTA6 PORTA6;
			kPWM_out_PORTA7 PORTA7;
			kPWM_out_PORTA8 PORTA8;
			kPWM_out_PORTA9 PORTA9;
			kPWM_out_PORTA10 PORTA10;
			kPWM_out_PORTA11 PORTA11;
			kPWM_out_PORTA15 PORTA15;

			kPWM_out_PORTB0 PORTB0;
			kPWM_out_PORTB1 PORTB1;
			kPWM_out_PORTB3 PORTB3;
			kPWM_out_PORTB4 PORTB4;
			kPWM_out_PORTB5 PORTB5;
			kPWM_out_PORTB6 PORTB6;
			kPWM_out_PORTB7 PORTB7;
			kPWM_out_PORTB8 PORTB8;
			kPWM_out_PORTB9 PORTB9;
			kPWM_out_PORTB10 PORTB10;
			kPWM_out_PORTB11 PORTB11;
			kPWM_out_PORTB14 PORTB14;
			kPWM_out_PORTB15 PORTB15;

		}kPWM_out;





#elif (kLib_config_PLATFORM == kLib_STM32F411xx)

	typedef struct
	{
		typedef enum
		{
			PORTA8 = 0x10034018,
			PORTE9 = 0x10034419
		}kPWM_Timer1_OC1_Pin;

	}kPWM_OC1_Timer1;

	typedef struct
	{
		typedef enum
		{
			PORTA9  = 0x10038019,
			PORTE11 = 0x1003841B
		}kPWM_Timer1_OC2_Pin;

	}kPWM_OC2_Timer1;

	typedef struct
	{
		typedef enum
		{
			PORTA10 = 0x1003C01A,
			PORTE13 = 0x1003C41D
		}kPWM_Timer1_OC3_Pin;

	}kPWM_OC3_Timer1;

	typedef struct
	{
		typedef enum
		{
			PORTA11 = 0x1004001B,
			PORTE14 = 0x1004041E
		}kPWM_Timer1_OC4_Pin;


	}kPWM_OC4_Timer1;

	typedef struct
	{
		kPWM_OC1_Timer1 OC1;
		kPWM_OC2_Timer1 OC2;
		kPWM_OC3_Timer1 OC3;
		kPWM_OC4_Timer1 OC4;

	}kPWM_Timer1;



	typedef struct
	{
		typedef enum
		{
			PORTA0 =  0x00034010,
			PORTA5 =  0x00034015,
			PORTA15 = 0x0003401F
		}kPWM_Timer2_OC1_Pin;

	}kPWM_OC1_Timer2;

	typedef struct
	{
		typedef enum
		{
			PORTA1 =  0x00038011,
			PORTB3 =  0x00038113
		}kPWM_Timer2_OC2_Pin;

	}kPWM_OC2_Timer2;

	typedef struct
	{
		typedef enum
		{
			PORTA2 =  0x0003C012,
			PORTB10 = 0x0003C11A
		}kPWM_Timer2_OC3_Pin;

	}kPWM_OC3_Timer2;

	typedef struct
	{
		typedef enum
		{
			PORTA3  = 0x00040013,
			PORTB11 = 0x0004011B
		}kPWM_Timer2_OC4_Pin;

	}kPWM_OC4_Timer2;

	typedef struct
	{
		kPWM_OC1_Timer2 OC1;
		kPWM_OC2_Timer2 OC2;
		kPWM_OC3_Timer2 OC3;
		kPWM_OC4_Timer2 OC4;

	}kPWM_Timer2;


		typedef struct
		{
			typedef enum
			{
				PORTA6 = 0x00434026,
				PORTB4 = 0x00434124,
				PORTC6 = 0x00434226
			}kPWM_Timer3_OC1_Pin;

		}kPWM_OC1_Timer3;

		typedef struct
		{
			typedef enum
			{
				PORTA7 = 0x00438027,
				PORTB5 = 0x00438125,
				PORTC7 = 0x00438227
			}kPWM_Timer3_OC2_Pin;

		}kPWM_OC2_Timer3;

		typedef struct
		{
			typedef enum
			{
				PORTB0 = 0x0043C120,
				PORTC8 = 0x0043C228
			}kPWM_Timer3_OC3_Pin;

		}kPWM_OC3_Timer3;

		typedef struct
		{
			typedef enum
			{
				PORTB1 = 0x00440121,
				PORTC9 = 0x00440229
			}kPWM_Timer3_OC4_Pin;

		}kPWM_OC4_Timer3;

		typedef struct
		{
			kPWM_OC1_Timer3 OC1;
			kPWM_OC2_Timer3 OC2;
			kPWM_OC3_Timer3 OC3;
			kPWM_OC4_Timer3 OC4;

		}kPWM_Timer3;


		typedef struct
		{
			typedef enum
			{
				PORTB6 =  0x00834126,
				PORTD12 = 0x0083432C
			}kPWM_Timer4_OC1_Pin;

		}kPWM_OC1_Timer4;

		typedef struct
		{
			typedef enum
			{
				PORTB7 =  0x00838127,
				PORTD13 = 0x0083832D
			}kPWM_Timer4_OC2_Pin;

		}kPWM_OC2_Timer4;

		typedef struct
		{
			typedef enum
			{
				PORTB8 =  0x0083C128,
				PORTD14 = 0x0083C32E
			}kPWM_Timer4_OC3_Pin;

		}kPWM_OC3_Timer4;

		typedef struct
		{
			typedef enum
			{
				PORTB9  = 0x00840129,
				PORTD15 = 0x0084032F
			}kPWM_Timer4_OC4_Pin;

		}kPWM_OC4_Timer4;

		typedef struct
		{
			kPWM_OC1_Timer4 OC1;
			kPWM_OC2_Timer4 OC2;
			kPWM_OC3_Timer4 OC3;
			kPWM_OC4_Timer4 OC4;

		}kPWM_Timer4;



		typedef struct
		{
			typedef enum
			{
				PORTA0  = 0x00C34020
			}kPWM_Timer5_OC1_Pin;

		}kPWM_OC1_Timer5;

		typedef struct
		{
			typedef enum
			{
				PORTA1  = 0x00C38021
			}kPWM_Timer5_OC2_Pin;

		}kPWM_OC2_Timer5;

		typedef struct
		{
			typedef enum
			{
				PORTA2  = 0x00C3C022
			}kPWM_Timer5_OC3_Pin;

		}kPWM_OC3_Timer5;

		typedef struct
		{
			typedef enum
			{
				PORTA3 = 0x00C40023
			}kPWM_Timer5_OC4_Pin;

		}kPWM_OC4_Timer5;

		typedef struct
		{
			kPWM_OC1_Timer5 OC1;
			kPWM_OC2_Timer5 OC2;
			kPWM_OC3_Timer5 OC3;
			kPWM_OC4_Timer5 OC4;

		}kPWM_Timer5;



		typedef struct
		{
			typedef enum
			{
				PORTA2 = 0x14034032,
				PORTE5 = 0x14034435
			}kPWM_Timer9_OC1_Pin;

		}kPWM_OC1_Timer9;

		typedef struct
		{
			typedef enum
			{
				PORTA3 = 0x14038033,
				PORTE6 = 0x14038436
			}kPWM_Timer9_OC2_Pin;

		}kPWM_OC2_Timer9;

		typedef struct
		{
			kPWM_OC1_Timer9 OC1;
			kPWM_OC2_Timer9 OC2;

		}kPWM_Timer9;

		typedef struct
		{
			typedef enum
			{
				PORTB8 = 0x14434138
			}kPWM_Timer10_OC1_Pin;

		}kPWM_OC1_Timer10;

		typedef struct
		{
			kPWM_OC1_Timer10 OC1;
		}kPWM_Timer10;



		typedef struct
		{
			typedef enum
			{
				PORTB9 = 0x14834139
			}kPWM_Timer11_OC1_Pin;

		}kPWM_OC1_Timer11;

		typedef struct
		{
			kPWM_OC1_Timer11 OC1;
		}kPWM_Timer11;



		typedef struct
		{
			kPWM_Timer1  Timer1;
			kPWM_Timer2  Timer2;
			kPWM_Timer3  Timer3;
			kPWM_Timer4  Timer4;
			kPWM_Timer5  Timer5;
			kPWM_Timer9  Timer9;
			kPWM_Timer10 Timer10;
			kPWM_Timer11 Timer11;
		}kPWM_out;


#elif (kLib_config_PLATFORM == kLib_STM32F407xx)

	typedef struct
	{
		typedef enum
		{
			PORTA8 = 0x10034018,
			PORTE9 = 0x10034419
		}kPWM_Timer1_OC1_Pin;

	}kPWM_OC1_Timer1;

	typedef struct
	{
		typedef enum
		{
			PORTA9  = 0x10038019,
			PORTE11 = 0x1003841B
		}kPWM_Timer1_OC2_Pin;

	}kPWM_OC2_Timer1;

	typedef struct
	{
		typedef enum
		{
			PORTA10 = 0x1003C01A,
			PORTE13 = 0x1003C41D
		}kPWM_Timer1_OC3_Pin;

	}kPWM_OC3_Timer1;

	typedef struct
	{
		typedef enum
		{
			PORTA11 = 0x1004001B,
			PORTE14 = 0x1004041E
		}kPWM_Timer1_OC4_Pin;


	}kPWM_OC4_Timer1;

	typedef struct
	{
		kPWM_OC1_Timer1 OC1;
		kPWM_OC2_Timer1 OC2;
		kPWM_OC3_Timer1 OC3;
		kPWM_OC4_Timer1 OC4;

	}kPWM_Timer1;



	typedef struct
	{
		typedef enum
		{
			PORTA15 = 0x0003401F
		}kPWM_Timer2_OC1_Pin;

	}kPWM_OC1_Timer2;

	typedef struct
	{
		typedef enum
		{
			PORTA1 =  0x00038011,
			PORTB3 =  0x00038113
		}kPWM_Timer2_OC2_Pin;

	}kPWM_OC2_Timer2;

	typedef struct
	{
		typedef enum
		{
			PORTA2 =  0x0003C012,
			PORTB10 = 0x0003C11A
		}kPWM_Timer2_OC3_Pin;

	}kPWM_OC3_Timer2;

	typedef struct
	{
		typedef enum
		{
			PORTA3  = 0x00040013,
			PORTB11 = 0x0004011B
		}kPWM_Timer2_OC4_Pin;

	}kPWM_OC4_Timer2;

	typedef struct
	{
		kPWM_OC1_Timer2 OC1;
		kPWM_OC2_Timer2 OC2;
		kPWM_OC3_Timer2 OC3;
		kPWM_OC4_Timer2 OC4;

	}kPWM_Timer2;


		typedef struct
		{
			typedef enum
			{
				PORTA6 = 0x00434026,
				PORTB4 = 0x00434124,
				PORTC6 = 0x00434226
			}kPWM_Timer3_OC1_Pin;

		}kPWM_OC1_Timer3;

		typedef struct
		{
			typedef enum
			{
				PORTA7 = 0x00438027,
				PORTB5 = 0x00438125,
				PORTC7 = 0x00438227
			}kPWM_Timer3_OC2_Pin;

		}kPWM_OC2_Timer3;

		typedef struct
		{
			typedef enum
			{
				PORTB0 = 0x0043C120,
				PORTC8 = 0x0043C228
			}kPWM_Timer3_OC3_Pin;

		}kPWM_OC3_Timer3;

		typedef struct
		{
			typedef enum
			{
				PORTB1 = 0x00440121,
				PORTC9 = 0x00440229
			}kPWM_Timer3_OC4_Pin;

		}kPWM_OC4_Timer3;

		typedef struct
		{
			kPWM_OC1_Timer3 OC1;
			kPWM_OC2_Timer3 OC2;
			kPWM_OC3_Timer3 OC3;
			kPWM_OC4_Timer3 OC4;

		}kPWM_Timer3;


		typedef struct
		{
			typedef enum
			{
				PORTB6 =  0x00834126,
				PORTD12 = 0x0083432C
			}kPWM_Timer4_OC1_Pin;

		}kPWM_OC1_Timer4;

		typedef struct
		{
			typedef enum
			{
				PORTB7 =  0x00838127,
				PORTD13 = 0x0083832D
			}kPWM_Timer4_OC2_Pin;

		}kPWM_OC2_Timer4;

		typedef struct
		{
			typedef enum
			{
				PORTB8 =  0x0083C128,
				PORTD14 = 0x0083C32E
			}kPWM_Timer4_OC3_Pin;

		}kPWM_OC3_Timer4;

		typedef struct
		{
			typedef enum
			{
				PORTB9  = 0x00840129,
				PORTD15 = 0x0084032F
			}kPWM_Timer4_OC4_Pin;

		}kPWM_OC4_Timer4;

		typedef struct
		{
			kPWM_OC1_Timer4 OC1;
			kPWM_OC2_Timer4 OC2;
			kPWM_OC3_Timer4 OC3;
			kPWM_OC4_Timer4 OC4;

		}kPWM_Timer4;



		typedef struct
		{
			typedef enum
			{
				PORTA0  = 0x00C34020,
				PORTH10 = 0x00C3472A
			}kPWM_Timer5_OC1_Pin;

		}kPWM_OC1_Timer5;

		typedef struct
		{
			typedef enum
			{
				PORTA1  = 0x00C38021,
				PORTH11 = 0x00C3872B
			}kPWM_Timer5_OC2_Pin;

		}kPWM_OC2_Timer5;

		typedef struct
		{
			typedef enum
			{
				PORTA2  = 0x00C3C022,
				PORTH12 = 0x00C3C72C
			}kPWM_Timer5_OC3_Pin;

		}kPWM_OC3_Timer5;

		typedef struct
		{
			typedef enum
			{
				PORTA3 = 0x00C40023,
				PORTI0 = 0x00C40820
			}kPWM_Timer5_OC4_Pin;

		}kPWM_OC4_Timer5;

		typedef struct
		{
			kPWM_OC1_Timer5 OC1;
			kPWM_OC2_Timer5 OC2;
			kPWM_OC3_Timer5 OC3;
			kPWM_OC4_Timer5 OC4;

		}kPWM_Timer5;



		typedef struct
		{
			typedef enum
			{
				PORTC6 = 0x10434236,
				PORTI5 = 0x10434835
			}kPWM_Timer8_OC1_Pin;

		}kPWM_OC1_Timer8;

		typedef struct
		{
			typedef enum
			{
				PORTC7 = 0x10438237,
				PORTI6 = 0x10438836
			}kPWM_Timer8_OC2_Pin;

		}kPWM_OC2_Timer8;

		typedef struct
		{
			typedef enum
			{
				PORTC8 = 0x1043C238,
				PORTI7 = 0x1043C837
			}kPWM_Timer8_OC3_Pin;

		}kPWM_OC3_Timer8;

		typedef struct
		{
			typedef enum
			{
				PORTC9 = 0x10440239,
				PORTI2 = 0x10440832
			}kPWM_Timer8_OC4_Pin;

		}kPWM_OC4_Timer8;

		typedef struct
		{
			kPWM_OC1_Timer8 OC1;
			kPWM_OC2_Timer8 OC2;
			kPWM_OC3_Timer8 OC3;
			kPWM_OC4_Timer8 OC4;

		}kPWM_Timer8;



		typedef struct
		{
			typedef enum
			{
				PORTA2 = 0x14034032,
				PORTE5 = 0x14034435
			}kPWM_Timer9_OC1_Pin;

		}kPWM_OC1_Timer9;

		typedef struct
		{
			typedef enum
			{
				PORTA3 = 0x14038033,
				PORTE6 = 0x14038436
			}kPWM_Timer9_OC2_Pin;

		}kPWM_OC2_Timer9;

		typedef struct
		{
			kPWM_OC1_Timer9 OC1;
			kPWM_OC2_Timer9 OC2;

		}kPWM_Timer9;

		typedef struct
		{
			typedef enum
			{
				PORTF6 = 0x14434536,
				PORTB8 = 0x14434138
			}kPWM_Timer10_OC1_Pin;

		}kPWM_OC1_Timer10;

		typedef struct
		{
			kPWM_OC1_Timer10 OC1;
		}kPWM_Timer10;



		typedef struct
		{
			typedef enum
			{
				PORTF7 = 0x14834537,
				PORTB9 = 0x14834139
			}kPWM_Timer11_OC1_Pin;

		}kPWM_OC1_Timer11;

		typedef struct
		{
			kPWM_OC1_Timer11 OC1;
		}kPWM_Timer11;



		typedef struct
		{
			typedef enum
			{
				PORTH6 = 0x01834796,
				PORTB14 = 0x0183419E
			}kPWM_Timer12_OC1_Pin;

		}kPWM_OC1_Timer12;

		typedef struct
		{
			typedef enum
			{
				PORTH9 =  0x01838799,
				PORTB15 = 0x0183819F
			}kPWM_Timer12_OC2_Pin;

		}kPWM_OC2_Timer12;

		typedef struct
		{
			kPWM_OC1_Timer12 OC1;
			kPWM_OC2_Timer12 OC2;

		}kPWM_Timer12;

		typedef struct
		{
			typedef enum
			{
				PORTF8 = 0x01C34598,
				PORTA6 = 0x01C34096
			}kPWM_Timer13_OC1_Pin;

		}kPWM_OC1_Timer13;

		typedef struct
		{
			kPWM_OC1_Timer13 OC1;
		}kPWM_Timer13;


		typedef struct
		{
			typedef enum
			{
				PORTF9 = 0x02034599,
				PORTA7 = 0x02034097
			}kPWM_Timer14_OC1_Pin;

		}kPWM_OC1_Timer14;

		typedef struct
		{
			kPWM_OC1_Timer14 OC1;
		}kPWM_Timer14;

		typedef struct
		{
			kPWM_Timer1  Timer1;
			kPWM_Timer2  Timer2;
			kPWM_Timer3  Timer3;
			kPWM_Timer4  Timer4;
			kPWM_Timer5  Timer5;
			kPWM_Timer8  Timer8;
			kPWM_Timer9  Timer9;
			kPWM_Timer10 Timer10;
			kPWM_Timer11 Timer11;
			kPWM_Timer12 Timer12;
			kPWM_Timer13 Timer13;
			kPWM_Timer14 Timer14;
		}kPWM_out;

#else
	#error "kPWM library do not support current chosen platform"
#endif

		typedef struct
		{
			typedef enum
			{
				PORTA0 = 0x00080000,
				PORTB0 = 0x00080010,
				PORTC0 = 0x00080020,
				PORTD0 = 0x00080030,
				PORTE0 = 0x00080040,
				PORTF0 = 0x00080050,
				PORTG0 = 0x00080060,
				PORTH0 = 0x00080070
			}kPWM_EXTI0_Pin;
		}kPWM_EXTI0;

		typedef struct
		{
			typedef enum
			{
				PORTA1 = 0x00080401,
				PORTB1 = 0x00080411,
				PORTC1 = 0x00080421,
				PORTD1 = 0x00080431,
				PORTE1 = 0x00080441,
				PORTF1 = 0x00080451,
				PORTG1 = 0x00080461,
				PORTH1 = 0x00080471
			}kPWM_EXTI1_Pin;
		}kPWM_EXTI1;

		typedef struct
		{
			typedef enum
			{
				PORTA2 = 0x00080802,
				PORTB2 = 0x00080812,
				PORTC2 = 0x00080822,
				PORTD2 = 0x00080832,
				PORTE2 = 0x00080842,
				PORTF2 = 0x00080852,
				PORTG2 = 0x00080862,
				PORTH2 = 0x00080872
			}kPWM_EXTI2_Pin;
		}kPWM_EXTI2;

		typedef struct
		{
			typedef enum
			{
				PORTA3 = 0x00080C03,
				PORTB3 = 0x00080C13,
				PORTC3 = 0x00080C23,
				PORTD3 = 0x00080C33,
				PORTE3 = 0x00080C43,
				PORTF3 = 0x00080C53,
				PORTG3 = 0x00080C63,
				PORTH3 = 0x00080C73
			}kPWM_EXTI3_Pin;
		}kPWM_EXTI3;

		typedef struct
		{
			typedef enum
			{
				PORTA4 = 0x000C0004,
				PORTB4 = 0x000C0014,
				PORTC4 = 0x000C0024,
				PORTD4 = 0x000C0034,
				PORTE4 = 0x000C0044,
				PORTF4 = 0x000C0054,
				PORTG4 = 0x000C0064,
				PORTH4 = 0x000C0074
			}kPWM_EXTI4_Pin;
		}kPWM_EXTI4;

		typedef struct
		{
			typedef enum
			{
				PORTA5 = 0x000C0405,
				PORTB5 = 0x000C0415,
				PORTC5 = 0x000C0425,
				PORTD5 = 0x000C0435,
				PORTE5 = 0x000C0445,
				PORTF5 = 0x000C0455,
				PORTG5 = 0x000C0465,
				PORTH5 = 0x000C0475
			}kPWM_EXTI5_Pin;
		}kPWM_EXTI5;

		typedef struct
		{
			typedef enum
			{
				PORTA6 = 0x000C0806,
				PORTB6 = 0x000C0816,
				PORTC6 = 0x000C0826,
				PORTD6 = 0x000C0836,
				PORTE6 = 0x000C0846,
				PORTF6 = 0x000C0856,
				PORTG6 = 0x000C0866,
				PORTH6 = 0x000C0876
			}kPWM_EXTI6_Pin;
		}kPWM_EXTI6;

		typedef struct
		{
			typedef enum
			{
				PORTA7 = 0x000C0C07,
				PORTB7 = 0x000C0C17,
				PORTC7 = 0x000C0C27,
				PORTD7 = 0x000C0C37,
				PORTE7 = 0x000C0C47,
				PORTF7 = 0x000C0C57,
				PORTG7 = 0x000C0C67,
				PORTH7 = 0x000C0C77
			}kPWM_EXTI7_Pin;
		}kPWM_EXTI7;

		typedef struct
		{
			typedef enum
			{
				PORTA8 = 0x00100008,
				PORTB8 = 0x00100018,
				PORTC8 = 0x00100028,
				PORTD8 = 0x00100038,
				PORTE8 = 0x00100048,
				PORTF8 = 0x00100058,
				PORTG8 = 0x00100068,
				PORTH8 = 0x00100078
			}kPWM_EXTI8_Pin;
		}kPWM_EXTI8;

		typedef struct
		{
			typedef enum
			{
				PORTA9 = 0x00100409,
				PORTB9 = 0x00100419,
				PORTC9 = 0x00100429,
				PORTD9 = 0x00100439,
				PORTE9 = 0x00100449,
				PORTF9 = 0x00100459,
				PORTG9 = 0x00100469,
				PORTH9 = 0x00100479
			}kPWM_EXTI9_Pin;
		}kPWM_EXTI9;

		typedef struct
		{
			typedef enum
			{
				PORTA10 = 0x0010080A,
				PORTB10 = 0x0010081A,
				PORTC10 = 0x0010082A,
				PORTD10 = 0x0010083A,
				PORTE10 = 0x0010084A,
				PORTF10 = 0x0010085A,
				PORTG10 = 0x0010086A,
				PORTH10 = 0x0010087A
			}kPWM_EXTI10_Pin;
		}kPWM_EXTI10;

		typedef struct
		{
			typedef enum
			{
				PORTA11 = 0x00100C0B,
				PORTB11 = 0x00100C1B,
				PORTC11 = 0x00100C2B,
				PORTD11 = 0x00100C3B,
				PORTE11 = 0x00100C4B,
				PORTF11 = 0x00100C5B,
				PORTG11 = 0x00100C6B,
				PORTH11 = 0x00100C7B
			}kPWM_EXTI11_Pin;
		}kPWM_EXTI11;

		typedef struct
		{
			typedef enum
			{
				PORTA12 = 0x0014000C,
				PORTB12 = 0x0014001C,
				PORTC12 = 0x0014002C,
				PORTD12 = 0x0014003C,
				PORTE12 = 0x0014004C,
				PORTF12 = 0x0014005C,
				PORTG12 = 0x0014006C,
				PORTH12 = 0x0014007C
			}kPWM_EXTI12_Pin;
		}kPWM_EXTI12;

		typedef struct
		{
			typedef enum
			{
				PORTA13 = 0x0014040D,
				PORTB13 = 0x0014041D,
				PORTC13 = 0x0014042D,
				PORTD13 = 0x0014043D,
				PORTE13 = 0x0014044D,
				PORTF13 = 0x0014045D,
				PORTG13 = 0x0014046D,
				PORTH13 = 0x0014047D
			}kPWM_EXTI13_Pin;
		}kPWM_EXTI13;

		typedef struct
		{
			typedef enum
			{
				PORTA14 = 0x0014080E,
				PORTB14 = 0x0014081E,
				PORTC14 = 0x0014082E,
				PORTD14 = 0x0014083E,
				PORTE14 = 0x0014084E,
				PORTF14 = 0x0014085E,
				PORTG14 = 0x0014086E,
				PORTH14 = 0x0014087E
			}kPWM_EXTI14_Pin;
		}kPWM_EXTI14;

		typedef struct
		{
			typedef enum
			{
				PORTA15 = 0x00140C0F,
				PORTB15 = 0x00140C1F,
				PORTC15 = 0x00140C2F,
				PORTD15 = 0x00140C3F,
				PORTE15 = 0x00140C4F,
				PORTF15 = 0x00140C5F,
				PORTG15 = 0x00140C6F,
				PORTH15 = 0x00140C7F
			}kPWM_EXTI15_Pin;
		}kPWM_EXTI15;

		typedef struct
		{
			kPWM_EXTI0   EXTI0;
			kPWM_EXTI1   EXTI1;
			kPWM_EXTI2   EXTI2;
			kPWM_EXTI3   EXTI3;
			kPWM_EXTI4   EXTI4;
			kPWM_EXTI5   EXTI5;
			kPWM_EXTI6   EXTI6;
			kPWM_EXTI7   EXTI7;
			kPWM_EXTI8   EXTI8;
			kPWM_EXTI9   EXTI9;
			kPWM_EXTI10  EXTI10;
			kPWM_EXTI11  EXTI11;
			kPWM_EXTI12  EXTI12;
			kPWM_EXTI13  EXTI13;
			kPWM_EXTI14  EXTI14;
			kPWM_EXTI15  EXTI15;
		}kPWM_in;

	class kPWM;

	class kPWM
	{
		public:

		typedef enum
		{
			activeHigh,
			activeLow
		}kPWM_ActiveState;




		class kPWMHardware
		{
			friend class kPWM;
			friend class kRCChannel;

			private:

				kPWM_EXTI_data_storage * EXTI_data;

				void setupInputModeHardware(unsigned int hard_code);

			public:

				TIM_TypeDef * tim;
				uint32_t * output;
				uint32_t input;

				kPWMHardware(void);


				kPWMHardware& operator = (unsigned int pwmHard);
				kPWMHardware& operator = (const kPWM::kPWM_ActiveState state);
				kPWMHardware& operator = (const kPWM_EXTI0::kPWM_EXTI0_Pin & pwmHard);
				kPWMHardware& operator = (const kPWM_EXTI1::kPWM_EXTI1_Pin & pwmHard);
				kPWMHardware& operator = (const kPWM_EXTI2::kPWM_EXTI2_Pin & pwmHard);
				kPWMHardware& operator = (const kPWM_EXTI3::kPWM_EXTI3_Pin & pwmHard);
				kPWMHardware& operator = (const kPWM_EXTI4::kPWM_EXTI4_Pin & pwmHard);
				kPWMHardware& operator = (const kPWM_EXTI5::kPWM_EXTI5_Pin & pwmHard);
				kPWMHardware& operator = (const kPWM_EXTI6::kPWM_EXTI6_Pin & pwmHard);
				kPWMHardware& operator = (const kPWM_EXTI7::kPWM_EXTI7_Pin & pwmHard);
				kPWMHardware& operator = (const kPWM_EXTI8::kPWM_EXTI8_Pin & pwmHard);
				kPWMHardware& operator = (const kPWM_EXTI9::kPWM_EXTI9_Pin & pwmHard);
				kPWMHardware& operator = (const kPWM_EXTI10::kPWM_EXTI10_Pin & pwmHard);
				kPWMHardware& operator = (const kPWM_EXTI11::kPWM_EXTI11_Pin & pwmHard);
				kPWMHardware& operator = (const kPWM_EXTI12::kPWM_EXTI12_Pin & pwmHard);
				kPWMHardware& operator = (const kPWM_EXTI13::kPWM_EXTI13_Pin & pwmHard);
				kPWMHardware& operator = (const kPWM_EXTI14::kPWM_EXTI14_Pin & pwmHard);
				kPWMHardware& operator = (const kPWM_EXTI15::kPWM_EXTI15_Pin & pwmHard);
		};


			kPWM(void);
			void run(unsigned short int resolution, unsigned int tick_freq);
			__inline__ void operator = (unsigned short int value) __attribute__((always_inline));

			//extract input pwm duty
			operator unsigned int();


			kPWMHardware hardware;



			static const kPWM_out * out;
			static const kPWM_in  * in ;

	};

	__attribute__((always_inline)) void kPWM::operator = (unsigned short int value)
	{
		*(this->hardware.output) = (uint32_t)value;
	}

#endif
