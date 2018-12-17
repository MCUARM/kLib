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

#ifndef __kPWMDEFS_H
#define __kPWMDEFS_H

#if (kLib_config_PLATFORM == kLib_STM32F427xx)

	typedef struct
	{
		typedef enum
		{
			PORTA0  = 0x00002100,
			PORTA5  = 0x00002105,
			PORTA15 = 0x0000210F
		}kPWM_Timer2_OC1_Pin;
	}kPWM_OC1_Timer2;

	typedef struct
	{
		typedef enum
		{
			PORTA1  = 0x48002101,
			PORTB3  = 0x48002113
		}kPWM_Timer2_OC2_Pin;
	}kPWM_OC2_Timer2;

	typedef struct
	{
		typedef enum
		{
			PORTA2  = 0x30002102,
			PORTB10 = 0x3000211A
		}kPWM_Timer2_OC3_Pin;
	}kPWM_OC3_Timer2;

	typedef struct
	{
		typedef enum
		{
			PORTA3  = 0x78002103,
			PORTB11 = 0x7800211B
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
			PORTA6  = 0x0100A206,
			PORTB4  = 0x0100A214,
			PORTC6  = 0x0100A226
		}kPWM_Timer3_OC1_Pin;
	}kPWM_OC1_Timer3;

	typedef struct
	{
		typedef enum
		{
			PORTA7  = 0x4900A207,
			PORTB5  = 0x4900A215,
			PORTC7  = 0x4900A227
		}kPWM_Timer3_OC2_Pin;
	}kPWM_OC2_Timer3;

	typedef struct
	{
		typedef enum
		{
			PORTB0  = 0x3100A210,
			PORTC8  = 0x3100A228
		}kPWM_Timer3_OC3_Pin;
	}kPWM_OC3_Timer3;

	typedef struct
	{
		typedef enum
		{
			PORTB1  = 0x7900A211,
			PORTC9  = 0x7900A229
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
			PORTB6  = 0x02012216,
			PORTD12 = 0x0201223C
		}kPWM_Timer4_OC1_Pin;
	}kPWM_OC1_Timer4;

	typedef struct
	{
		typedef enum
		{
			PORTB7  = 0x4A012217,
			PORTD13 = 0x4A01223D
		}kPWM_Timer4_OC2_Pin;
	}kPWM_OC2_Timer4;

	typedef struct
	{
		typedef enum
		{
			PORTB8  = 0x32012218,
			PORTD14 = 0x3201223E
		}kPWM_Timer4_OC3_Pin;
	}kPWM_OC3_Timer4;

	typedef struct
	{
		typedef enum
		{
			PORTB9  = 0x7A012219,
			PORTD15 = 0x7A01223F
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
			PORTA0  = 0x0301A200
		}kPWM_Timer5_OC1_Pin;
	}kPWM_OC1_Timer5;

	typedef struct
	{
		typedef enum
		{
			PORTA1  = 0x4B01A201
		}kPWM_Timer5_OC2_Pin;
	}kPWM_OC2_Timer5;

	typedef struct
	{
		typedef enum
		{
			PORTA2  = 0x3301A202
		}kPWM_Timer5_OC3_Pin;
	}kPWM_OC3_Timer5;

	typedef struct
	{
		typedef enum
		{
			PORTA3  = 0x7B01A203
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
			PORTB14 = 0x0603291E
		}kPWM_Timer12_OC1_Pin;
	}kPWM_OC1_Timer12;

	typedef struct
	{
		typedef enum
		{
			PORTB15 = 0x4E03291F,
			PORTH9  = 0x4E032979
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
			PORTA6  = 0x0703A906,
			PORTF8  = 0x0703A958
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
			PORTA7  = 0x00442907,
			PORTF9  = 0x00442959
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
			PORTA6  = 0x00202906,
			PORTA7  = 0x00202907,
			PORTA8  = 0x00202108,
			PORTB8  = 0x00202318,
			PORTB9  = 0x00202319,
			PORTB14 = 0x0020291E,
			PORTE9  = 0x00202149,
			PORTF6  = 0x00202356,
			PORTF7  = 0x00202357,
			PORTF8  = 0x00202958,
			PORTF9  = 0x00202959
		}kPWM_Timer1_OC1_Pin;
	}kPWM_OC1_Timer1;

	typedef struct
	{
		typedef enum
		{
			PORTA9  = 0x48202109,
			PORTB15 = 0x4820291F,
			PORTE11 = 0x4820214B,
			PORTH9  = 0x48202979
		}kPWM_Timer1_OC2_Pin;
	}kPWM_OC2_Timer1;

	typedef struct
	{
		typedef enum
		{
			PORTA10 = 0x3020210A,
			PORTE13 = 0x3020214D
		}kPWM_Timer1_OC3_Pin;
	}kPWM_OC3_Timer1;

	typedef struct
	{
		typedef enum
		{
			PORTA11 = 0x7820210B,
			PORTE14 = 0x7820214E
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
			PORTC6  = 0x0120A326
		}kPWM_Timer8_OC1_Pin;
	}kPWM_OC1_Timer8;

	typedef struct
	{
		typedef enum
		{
			PORTC7  = 0x4920A327
		}kPWM_Timer8_OC2_Pin;
	}kPWM_OC2_Timer8;

	typedef struct
	{
		typedef enum
		{
			PORTC8  = 0x3120A328
		}kPWM_Timer8_OC3_Pin;
	}kPWM_OC3_Timer8;

	typedef struct
	{
		typedef enum
		{
			PORTC9  = 0x7920A329
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
			PORTA2  = 0x00A82302,
			PORTE5  = 0x00A82345
		}kPWM_Timer9_OC1_Pin;
	}kPWM_OC1_Timer9;

	typedef struct
	{
		typedef enum
		{
			PORTA3  = 0x48A82303,
			PORTE6  = 0x48A82346
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
			PORTB8  = 0x01A8A318,
			PORTF6  = 0x01A8A356
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
			PORTB9  = 0x02A92319,
			PORTF7  = 0x02A92357
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
			Timer2_OC1  = 0x00002100,
			Timer5_OC1  = 0x0301A200
		}kPWM_OUT_PORTA0_PIN;
	}kPWM_out_PORTA0;

	typedef struct
	{
		typedef enum
		{
			Timer2_OC2  = 0x48002101,
			Timer5_OC2  = 0x4B01A201
		}kPWM_OUT_PORTA1_PIN;
	}kPWM_out_PORTA1;

	typedef struct
	{
		typedef enum
		{
			Timer2_OC3  = 0x30002102,
			Timer5_OC3  = 0x3301A202,
			Timer9_OC1  = 0x00A82302
		}kPWM_OUT_PORTA2_PIN;
	}kPWM_out_PORTA2;

	typedef struct
	{
		typedef enum
		{
			Timer2_OC4  = 0x78002103,
			Timer5_OC4  = 0x7B01A203,
			Timer9_OC2  = 0x48A82303
		}kPWM_OUT_PORTA3_PIN;
	}kPWM_out_PORTA3;

	typedef struct
	{
		typedef enum
		{
			Timer2_OC1  = 0x00002105
		}kPWM_OUT_PORTA5_PIN;
	}kPWM_out_PORTA5;

	typedef struct
	{
		typedef enum
		{
			Timer3_OC1  = 0x0100A206,
			Timer1_OC1  = 0x06032906
		}kPWM_OUT_PORTA6_PIN;
	}kPWM_out_PORTA6;

	typedef struct
	{
		typedef enum
		{
			Timer3_OC2  = 0x4900A207,
			Timer1_OC1  = 0x06032907
		}kPWM_OUT_PORTA7_PIN;
	}kPWM_out_PORTA7;

	typedef struct
	{
		typedef enum
		{
			Timer1_OC1  = 0x06032108
		}kPWM_OUT_PORTA8_PIN;
	}kPWM_out_PORTA8;

	typedef struct
	{
		typedef enum
		{
			Timer1_OC2  = 0x4E032109
		}kPWM_OUT_PORTA9_PIN;
	}kPWM_out_PORTA9;

	typedef struct
	{
		typedef enum
		{
			Timer1_OC3  = 0x3603210A
		}kPWM_OUT_PORTA10_PIN;
	}kPWM_out_PORTA10;

	typedef struct
	{
		typedef enum
		{
			Timer1_OC4  = 0x7E03210B
		}kPWM_OUT_PORTA11_PIN;
	}kPWM_out_PORTA11;

	typedef struct
	{
		typedef enum
		{
			Timer2_OC1  = 0x0000210F
		}kPWM_OUT_PORTA15_PIN;
	}kPWM_out_PORTA15;

	typedef struct
	{
		typedef enum
		{
			Timer3_OC3  = 0x3100A210
		}kPWM_OUT_PORTB0_PIN;
	}kPWM_out_PORTB0;

	typedef struct
	{
		typedef enum
		{
			Timer3_OC4  = 0x7900A211
		}kPWM_OUT_PORTB1_PIN;
	}kPWM_out_PORTB1;

	typedef struct
	{
		typedef enum
		{
			Timer2_OC2  = 0x48002113
		}kPWM_OUT_PORTB3_PIN;
	}kPWM_out_PORTB3;

	typedef struct
	{
		typedef enum
		{
			Timer3_OC1  = 0x0100A214
		}kPWM_OUT_PORTB4_PIN;
	}kPWM_out_PORTB4;

	typedef struct
	{
		typedef enum
		{
			Timer3_OC2  = 0x4900A215
		}kPWM_OUT_PORTB5_PIN;
	}kPWM_out_PORTB5;

	typedef struct
	{
		typedef enum
		{
			Timer4_OC1  = 0x02012216
		}kPWM_OUT_PORTB6_PIN;
	}kPWM_out_PORTB6;

	typedef struct
	{
		typedef enum
		{
			Timer4_OC2  = 0x4A012217
		}kPWM_OUT_PORTB7_PIN;
	}kPWM_out_PORTB7;

	typedef struct
	{
		typedef enum
		{
			Timer4_OC3  = 0x32012218,
			Timer1_OC1  = 0x06032318
		}kPWM_OUT_PORTB8_PIN;
	}kPWM_out_PORTB8;

	typedef struct
	{
		typedef enum
		{
			Timer4_OC4  = 0x7A012219,
			Timer1_OC1  = 0x06032319
		}kPWM_OUT_PORTB9_PIN;
	}kPWM_out_PORTB9;

	typedef struct
	{
		typedef enum
		{
			Timer2_OC3  = 0x3000211A
		}kPWM_OUT_PORTB10_PIN;
	}kPWM_out_PORTB10;

	typedef struct
	{
		typedef enum
		{
			Timer2_OC4  = 0x7800211B
		}kPWM_OUT_PORTB11_PIN;
	}kPWM_out_PORTB11;

	typedef struct
	{
		typedef enum
		{
			Timer1_OC1  = 0x0603291E
		}kPWM_OUT_PORTB14_PIN;
	}kPWM_out_PORTB14;

	typedef struct
	{
		typedef enum
		{
			Timer1_OC2  = 0x4E03291F
		}kPWM_OUT_PORTB15_PIN;
	}kPWM_out_PORTB15;

	typedef struct
	{
		typedef enum
		{
			Timer3_OC1  = 0x0100A226,
			Timer8_OC1  = 0x0120A326
		}kPWM_OUT_PORTC6_PIN;
	}kPWM_out_PORTC6;

	typedef struct
	{
		typedef enum
		{
			Timer3_OC2  = 0x4900A227,
			Timer8_OC2  = 0x4920A327
		}kPWM_OUT_PORTC7_PIN;
	}kPWM_out_PORTC7;

	typedef struct
	{
		typedef enum
		{
			Timer3_OC3  = 0x3100A228,
			Timer8_OC3  = 0x3120A328
		}kPWM_OUT_PORTC8_PIN;
	}kPWM_out_PORTC8;

	typedef struct
	{
		typedef enum
		{
			Timer3_OC4  = 0x7900A229,
			Timer8_OC4  = 0x7920A329
		}kPWM_OUT_PORTC9_PIN;
	}kPWM_out_PORTC9;

	typedef struct
	{
		typedef enum
		{
			Timer4_OC1  = 0x0201223C
		}kPWM_OUT_PORTD12_PIN;
	}kPWM_out_PORTD12;

	typedef struct
	{
		typedef enum
		{
			Timer4_OC2  = 0x4A01223D
		}kPWM_OUT_PORTD13_PIN;
	}kPWM_out_PORTD13;

	typedef struct
	{
		typedef enum
		{
			Timer4_OC3  = 0x3201223E
		}kPWM_OUT_PORTD14_PIN;
	}kPWM_out_PORTD14;

	typedef struct
	{
		typedef enum
		{
			Timer4_OC4  = 0x7A01223F
		}kPWM_OUT_PORTD15_PIN;
	}kPWM_out_PORTD15;

	typedef struct
	{
		typedef enum
		{
			Timer9_OC1  = 0x00A82345
		}kPWM_OUT_PORTE5_PIN;
	}kPWM_out_PORTE5;

	typedef struct
	{
		typedef enum
		{
			Timer9_OC2  = 0x48A82346
		}kPWM_OUT_PORTE6_PIN;
	}kPWM_out_PORTE6;

	typedef struct
	{
		typedef enum
		{
			Timer1_OC1  = 0x06032149
		}kPWM_OUT_PORTE9_PIN;
	}kPWM_out_PORTE9;

	typedef struct
	{
		typedef enum
		{
			Timer1_OC2  = 0x4E03214B
		}kPWM_OUT_PORTE11_PIN;
	}kPWM_out_PORTE11;

	typedef struct
	{
		typedef enum
		{
			Timer1_OC3  = 0x3603214D
		}kPWM_OUT_PORTE13_PIN;
	}kPWM_out_PORTE13;

	typedef struct
	{
		typedef enum
		{
			Timer1_OC4  = 0x7E03214E
		}kPWM_OUT_PORTE14_PIN;
	}kPWM_out_PORTE14;

	typedef struct
	{
		typedef enum
		{
			Timer1_OC1  = 0x06032356
		}kPWM_OUT_PORTF6_PIN;
	}kPWM_out_PORTF6;

	typedef struct
	{
		typedef enum
		{
			Timer1_OC1  = 0x06032357
		}kPWM_OUT_PORTF7_PIN;
	}kPWM_out_PORTF7;

	typedef struct
	{
		typedef enum
		{
			Timer1_OC1  = 0x06032958
		}kPWM_OUT_PORTF8_PIN;
	}kPWM_out_PORTF8;

	typedef struct
	{
		typedef enum
		{
			Timer1_OC1  = 0x06032959
		}kPWM_OUT_PORTF9_PIN;
	}kPWM_out_PORTF9;

	typedef struct
	{
		typedef enum
		{
			Timer1_OC2  = 0x4E032979
		}kPWM_OUT_PORTH9_PIN;
	}kPWM_out_PORTH9;

	typedef struct
	{
		kPWM_Timer2  Timer2;
		kPWM_Timer3  Timer3;
		kPWM_Timer4  Timer4;
		kPWM_Timer5  Timer5;
		kPWM_Timer12 Timer12;
		kPWM_Timer13 Timer13;
		kPWM_Timer14 Timer14;
		kPWM_Timer1  Timer1;
		kPWM_Timer8  Timer8;
		kPWM_Timer9  Timer9;
		kPWM_Timer10 Timer10;
		kPWM_Timer11 Timer11;

		kPWM_out_PORTA0  PORTA0;  //  TIM2_CH1  TIM5_CH1
		kPWM_out_PORTA1  PORTA1;  //  TIM2_CH2  TIM5_CH2
		kPWM_out_PORTA2  PORTA2;  //  TIM2_CH3  TIM5_CH3  TIM9_CH1
		kPWM_out_PORTA3  PORTA3;  //  TIM2_CH4  TIM5_CH4  TIM9_CH2
		kPWM_out_PORTA5  PORTA5;  //  TIM2_CH1
		kPWM_out_PORTA6  PORTA6;  //  TIM3_CH1  TIM13_CH1
		kPWM_out_PORTA7  PORTA7;  //  TIM3_CH2  TIM14_CH1
		kPWM_out_PORTA8  PORTA8;  //  TIM1_CH1
		kPWM_out_PORTA9  PORTA9;  //  TIM1_CH2
		kPWM_out_PORTA10 PORTA10; //  TIM1_CH3
		kPWM_out_PORTA11 PORTA11; //  TIM1_CH4
		kPWM_out_PORTA15 PORTA15; //  TIM2_CH1

		kPWM_out_PORTB0  PORTB0;  //  TIM3_CH3
		kPWM_out_PORTB1  PORTB1;  //  TIM3_CH4
		kPWM_out_PORTB3  PORTB3;  //  TIM2_CH2
		kPWM_out_PORTB4  PORTB4;  //  TIM3_CH1
		kPWM_out_PORTB5  PORTB5;  //  TIM3_CH2
		kPWM_out_PORTB6  PORTB6;  //  TIM4_CH1
		kPWM_out_PORTB7  PORTB7;  //  TIM4_CH2
		kPWM_out_PORTB8  PORTB8;  //  TIM4_CH3  TIM10_CH1
		kPWM_out_PORTB9  PORTB9;  //  TIM4_CH4  TIM11_CH1
		kPWM_out_PORTB10 PORTB10; //  TIM2_CH3
		kPWM_out_PORTB11 PORTB11; //  TIM2_CH4
		kPWM_out_PORTB14 PORTB14; //  TIM12_CH1
		kPWM_out_PORTB15 PORTB15; //  TIM12_CH2

		kPWM_out_PORTC6  PORTC6;  //  TIM3_CH1  TIM8_CH1
		kPWM_out_PORTC7  PORTC7;  //  TIM3_CH2  TIM8_CH2
		kPWM_out_PORTC8  PORTC8;  //  TIM3_CH3  TIM8_CH3
		kPWM_out_PORTC9  PORTC9;  //  TIM3_CH4  TIM8_CH4

		kPWM_out_PORTD12 PORTD12; //  TIM4_CH1
		kPWM_out_PORTD13 PORTD13; //  TIM4_CH2
		kPWM_out_PORTD14 PORTD14; //  TIM4_CH3
		kPWM_out_PORTD15 PORTD15; //  TIM4_CH4

		kPWM_out_PORTE5  PORTE5;  //  TIM9_CH1
		kPWM_out_PORTE6  PORTE6;  //  TIM9_CH2
		kPWM_out_PORTE9  PORTE9;  //  TIM1_CH1
		kPWM_out_PORTE11 PORTE11; //  TIM1_CH2
		kPWM_out_PORTE13 PORTE13; //  TIM1_CH3
		kPWM_out_PORTE14 PORTE14; //  TIM1_CH4

		kPWM_out_PORTF6  PORTF6;  //  TIM10_CH1
		kPWM_out_PORTF7  PORTF7;  //  TIM11_CH1
		kPWM_out_PORTF8  PORTF8;  //  TIM13_CH1
		kPWM_out_PORTF9  PORTF9;  //  TIM14_CH1

		kPWM_out_PORTH9  PORTH9;  //  TIM12_CH2
	}kPWM_out;


#endif
#if (kLib_config_PLATFORM == kLib_STM32F429xx)

	typedef struct
	{
		typedef enum
		{
			PORTA0  = 0x00002100,
			PORTA5  = 0x00002105,
			PORTA15 = 0x0000210F
		}kPWM_Timer2_OC1_Pin;
	}kPWM_OC1_Timer2;

	typedef struct
	{
		typedef enum
		{
			PORTA1  = 0x48002101,
			PORTB3  = 0x48002113
		}kPWM_Timer2_OC2_Pin;
	}kPWM_OC2_Timer2;

	typedef struct
	{
		typedef enum
		{
			PORTA2  = 0x30002102,
			PORTB10 = 0x3000211A
		}kPWM_Timer2_OC3_Pin;
	}kPWM_OC3_Timer2;

	typedef struct
	{
		typedef enum
		{
			PORTA3  = 0x78002103,
			PORTB11 = 0x7800211B
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
			PORTA6  = 0x0100A206,
			PORTB4  = 0x0100A214,
			PORTC6  = 0x0100A226
		}kPWM_Timer3_OC1_Pin;
	}kPWM_OC1_Timer3;

	typedef struct
	{
		typedef enum
		{
			PORTA7  = 0x4900A207,
			PORTB5  = 0x4900A215,
			PORTC7  = 0x4900A227
		}kPWM_Timer3_OC2_Pin;
	}kPWM_OC2_Timer3;

	typedef struct
	{
		typedef enum
		{
			PORTB0  = 0x3100A210,
			PORTC8  = 0x3100A228
		}kPWM_Timer3_OC3_Pin;
	}kPWM_OC3_Timer3;

	typedef struct
	{
		typedef enum
		{
			PORTB1  = 0x7900A211,
			PORTC9  = 0x7900A229
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
			PORTB6  = 0x02012216,
			PORTD12 = 0x0201223C
		}kPWM_Timer4_OC1_Pin;
	}kPWM_OC1_Timer4;

	typedef struct
	{
		typedef enum
		{
			PORTB7  = 0x4A012217,
			PORTD13 = 0x4A01223D
		}kPWM_Timer4_OC2_Pin;
	}kPWM_OC2_Timer4;

	typedef struct
	{
		typedef enum
		{
			PORTB8  = 0x32012218,
			PORTD14 = 0x3201223E
		}kPWM_Timer4_OC3_Pin;
	}kPWM_OC3_Timer4;

	typedef struct
	{
		typedef enum
		{
			PORTB9  = 0x7A012219,
			PORTD15 = 0x7A01223F
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
			PORTA0  = 0x0301A200
		}kPWM_Timer5_OC1_Pin;
	}kPWM_OC1_Timer5;

	typedef struct
	{
		typedef enum
		{
			PORTA1  = 0x4B01A201
		}kPWM_Timer5_OC2_Pin;
	}kPWM_OC2_Timer5;

	typedef struct
	{
		typedef enum
		{
			PORTA2  = 0x3301A202
		}kPWM_Timer5_OC3_Pin;
	}kPWM_OC3_Timer5;

	typedef struct
	{
		typedef enum
		{
			PORTA3  = 0x7B01A203
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
			PORTB14 = 0x0603291E
		}kPWM_Timer12_OC1_Pin;
	}kPWM_OC1_Timer12;

	typedef struct
	{
		typedef enum
		{
			PORTB15 = 0x4E03291F,
			PORTH9  = 0x4E032979
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
			PORTA6  = 0x0703A906,
			PORTF8  = 0x0703A958
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
			PORTA7  = 0x00442907,
			PORTF9  = 0x00442959
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
			PORTA6  = 0x00202906,
			PORTA7  = 0x00202907,
			PORTA8  = 0x00202108,
			PORTB8  = 0x00202318,
			PORTB9  = 0x00202319,
			PORTB14 = 0x0020291E,
			PORTE9  = 0x00202149,
			PORTF6  = 0x00202356,
			PORTF7  = 0x00202357,
			PORTF8  = 0x00202958,
			PORTF9  = 0x00202959
		}kPWM_Timer1_OC1_Pin;
	}kPWM_OC1_Timer1;

	typedef struct
	{
		typedef enum
		{
			PORTA9  = 0x48202109,
			PORTB15 = 0x4820291F,
			PORTE11 = 0x4820214B,
			PORTH9  = 0x48202979
		}kPWM_Timer1_OC2_Pin;
	}kPWM_OC2_Timer1;

	typedef struct
	{
		typedef enum
		{
			PORTA10 = 0x3020210A,
			PORTE13 = 0x3020214D
		}kPWM_Timer1_OC3_Pin;
	}kPWM_OC3_Timer1;

	typedef struct
	{
		typedef enum
		{
			PORTA11 = 0x7820210B,
			PORTE14 = 0x7820214E
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
			PORTC6  = 0x0120A326
		}kPWM_Timer8_OC1_Pin;
	}kPWM_OC1_Timer8;

	typedef struct
	{
		typedef enum
		{
			PORTC7  = 0x4920A327
		}kPWM_Timer8_OC2_Pin;
	}kPWM_OC2_Timer8;

	typedef struct
	{
		typedef enum
		{
			PORTC8  = 0x3120A328
		}kPWM_Timer8_OC3_Pin;
	}kPWM_OC3_Timer8;

	typedef struct
	{
		typedef enum
		{
			PORTC9  = 0x7920A329
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
			PORTA2  = 0x00A82302,
			PORTE5  = 0x00A82345
		}kPWM_Timer9_OC1_Pin;
	}kPWM_OC1_Timer9;

	typedef struct
	{
		typedef enum
		{
			PORTA3  = 0x48A82303,
			PORTE6  = 0x48A82346
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
			PORTB8  = 0x01A8A318,
			PORTF6  = 0x01A8A356
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
			PORTB9  = 0x02A92319,
			PORTF7  = 0x02A92357
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
			Timer2_OC1  = 0x00002100,
			Timer5_OC1  = 0x0301A200
		}kPWM_OUT_PORTA0_PIN;
	}kPWM_out_PORTA0;

	typedef struct
	{
		typedef enum
		{
			Timer2_OC2  = 0x48002101,
			Timer5_OC2  = 0x4B01A201
		}kPWM_OUT_PORTA1_PIN;
	}kPWM_out_PORTA1;

	typedef struct
	{
		typedef enum
		{
			Timer2_OC3  = 0x30002102,
			Timer5_OC3  = 0x3301A202,
			Timer9_OC1  = 0x00A82302
		}kPWM_OUT_PORTA2_PIN;
	}kPWM_out_PORTA2;

	typedef struct
	{
		typedef enum
		{
			Timer2_OC4  = 0x78002103,
			Timer5_OC4  = 0x7B01A203,
			Timer9_OC2  = 0x48A82303
		}kPWM_OUT_PORTA3_PIN;
	}kPWM_out_PORTA3;

	typedef struct
	{
		typedef enum
		{
			Timer2_OC1  = 0x00002105
		}kPWM_OUT_PORTA5_PIN;
	}kPWM_out_PORTA5;

	typedef struct
	{
		typedef enum
		{
			Timer3_OC1  = 0x0100A206,
			Timer1_OC1  = 0x06032906
		}kPWM_OUT_PORTA6_PIN;
	}kPWM_out_PORTA6;

	typedef struct
	{
		typedef enum
		{
			Timer3_OC2  = 0x4900A207,
			Timer1_OC1  = 0x06032907
		}kPWM_OUT_PORTA7_PIN;
	}kPWM_out_PORTA7;

	typedef struct
	{
		typedef enum
		{
			Timer1_OC1  = 0x06032108
		}kPWM_OUT_PORTA8_PIN;
	}kPWM_out_PORTA8;

	typedef struct
	{
		typedef enum
		{
			Timer1_OC2  = 0x4E032109
		}kPWM_OUT_PORTA9_PIN;
	}kPWM_out_PORTA9;

	typedef struct
	{
		typedef enum
		{
			Timer1_OC3  = 0x3603210A
		}kPWM_OUT_PORTA10_PIN;
	}kPWM_out_PORTA10;

	typedef struct
	{
		typedef enum
		{
			Timer1_OC4  = 0x7E03210B
		}kPWM_OUT_PORTA11_PIN;
	}kPWM_out_PORTA11;

	typedef struct
	{
		typedef enum
		{
			Timer2_OC1  = 0x0000210F
		}kPWM_OUT_PORTA15_PIN;
	}kPWM_out_PORTA15;

	typedef struct
	{
		typedef enum
		{
			Timer3_OC3  = 0x3100A210
		}kPWM_OUT_PORTB0_PIN;
	}kPWM_out_PORTB0;

	typedef struct
	{
		typedef enum
		{
			Timer3_OC4  = 0x7900A211
		}kPWM_OUT_PORTB1_PIN;
	}kPWM_out_PORTB1;

	typedef struct
	{
		typedef enum
		{
			Timer2_OC2  = 0x48002113
		}kPWM_OUT_PORTB3_PIN;
	}kPWM_out_PORTB3;

	typedef struct
	{
		typedef enum
		{
			Timer3_OC1  = 0x0100A214
		}kPWM_OUT_PORTB4_PIN;
	}kPWM_out_PORTB4;

	typedef struct
	{
		typedef enum
		{
			Timer3_OC2  = 0x4900A215
		}kPWM_OUT_PORTB5_PIN;
	}kPWM_out_PORTB5;

	typedef struct
	{
		typedef enum
		{
			Timer4_OC1  = 0x02012216
		}kPWM_OUT_PORTB6_PIN;
	}kPWM_out_PORTB6;

	typedef struct
	{
		typedef enum
		{
			Timer4_OC2  = 0x4A012217
		}kPWM_OUT_PORTB7_PIN;
	}kPWM_out_PORTB7;

	typedef struct
	{
		typedef enum
		{
			Timer4_OC3  = 0x32012218,
			Timer1_OC1  = 0x06032318
		}kPWM_OUT_PORTB8_PIN;
	}kPWM_out_PORTB8;

	typedef struct
	{
		typedef enum
		{
			Timer4_OC4  = 0x7A012219,
			Timer1_OC1  = 0x06032319
		}kPWM_OUT_PORTB9_PIN;
	}kPWM_out_PORTB9;

	typedef struct
	{
		typedef enum
		{
			Timer2_OC3  = 0x3000211A
		}kPWM_OUT_PORTB10_PIN;
	}kPWM_out_PORTB10;

	typedef struct
	{
		typedef enum
		{
			Timer2_OC4  = 0x7800211B
		}kPWM_OUT_PORTB11_PIN;
	}kPWM_out_PORTB11;

	typedef struct
	{
		typedef enum
		{
			Timer1_OC1  = 0x0603291E
		}kPWM_OUT_PORTB14_PIN;
	}kPWM_out_PORTB14;

	typedef struct
	{
		typedef enum
		{
			Timer1_OC2  = 0x4E03291F
		}kPWM_OUT_PORTB15_PIN;
	}kPWM_out_PORTB15;

	typedef struct
	{
		typedef enum
		{
			Timer3_OC1  = 0x0100A226,
			Timer8_OC1  = 0x0120A326
		}kPWM_OUT_PORTC6_PIN;
	}kPWM_out_PORTC6;

	typedef struct
	{
		typedef enum
		{
			Timer3_OC2  = 0x4900A227,
			Timer8_OC2  = 0x4920A327
		}kPWM_OUT_PORTC7_PIN;
	}kPWM_out_PORTC7;

	typedef struct
	{
		typedef enum
		{
			Timer3_OC3  = 0x3100A228,
			Timer8_OC3  = 0x3120A328
		}kPWM_OUT_PORTC8_PIN;
	}kPWM_out_PORTC8;

	typedef struct
	{
		typedef enum
		{
			Timer3_OC4  = 0x7900A229,
			Timer8_OC4  = 0x7920A329
		}kPWM_OUT_PORTC9_PIN;
	}kPWM_out_PORTC9;

	typedef struct
	{
		typedef enum
		{
			Timer4_OC1  = 0x0201223C
		}kPWM_OUT_PORTD12_PIN;
	}kPWM_out_PORTD12;

	typedef struct
	{
		typedef enum
		{
			Timer4_OC2  = 0x4A01223D
		}kPWM_OUT_PORTD13_PIN;
	}kPWM_out_PORTD13;

	typedef struct
	{
		typedef enum
		{
			Timer4_OC3  = 0x3201223E
		}kPWM_OUT_PORTD14_PIN;
	}kPWM_out_PORTD14;

	typedef struct
	{
		typedef enum
		{
			Timer4_OC4  = 0x7A01223F
		}kPWM_OUT_PORTD15_PIN;
	}kPWM_out_PORTD15;

	typedef struct
	{
		typedef enum
		{
			Timer9_OC1  = 0x00A82345
		}kPWM_OUT_PORTE5_PIN;
	}kPWM_out_PORTE5;

	typedef struct
	{
		typedef enum
		{
			Timer9_OC2  = 0x48A82346
		}kPWM_OUT_PORTE6_PIN;
	}kPWM_out_PORTE6;

	typedef struct
	{
		typedef enum
		{
			Timer1_OC1  = 0x06032149
		}kPWM_OUT_PORTE9_PIN;
	}kPWM_out_PORTE9;

	typedef struct
	{
		typedef enum
		{
			Timer1_OC2  = 0x4E03214B
		}kPWM_OUT_PORTE11_PIN;
	}kPWM_out_PORTE11;

	typedef struct
	{
		typedef enum
		{
			Timer1_OC3  = 0x3603214D
		}kPWM_OUT_PORTE13_PIN;
	}kPWM_out_PORTE13;

	typedef struct
	{
		typedef enum
		{
			Timer1_OC4  = 0x7E03214E
		}kPWM_OUT_PORTE14_PIN;
	}kPWM_out_PORTE14;

	typedef struct
	{
		typedef enum
		{
			Timer1_OC1  = 0x06032356
		}kPWM_OUT_PORTF6_PIN;
	}kPWM_out_PORTF6;

	typedef struct
	{
		typedef enum
		{
			Timer1_OC1  = 0x06032357
		}kPWM_OUT_PORTF7_PIN;
	}kPWM_out_PORTF7;

	typedef struct
	{
		typedef enum
		{
			Timer1_OC1  = 0x06032958
		}kPWM_OUT_PORTF8_PIN;
	}kPWM_out_PORTF8;

	typedef struct
	{
		typedef enum
		{
			Timer1_OC1  = 0x06032959
		}kPWM_OUT_PORTF9_PIN;
	}kPWM_out_PORTF9;

	typedef struct
	{
		typedef enum
		{
			Timer1_OC2  = 0x4E032979
		}kPWM_OUT_PORTH9_PIN;
	}kPWM_out_PORTH9;

	typedef struct
	{
		kPWM_Timer2  Timer2;
		kPWM_Timer3  Timer3;
		kPWM_Timer4  Timer4;
		kPWM_Timer5  Timer5;
		kPWM_Timer12 Timer12;
		kPWM_Timer13 Timer13;
		kPWM_Timer14 Timer14;
		kPWM_Timer1  Timer1;
		kPWM_Timer8  Timer8;
		kPWM_Timer9  Timer9;
		kPWM_Timer10 Timer10;
		kPWM_Timer11 Timer11;

		kPWM_out_PORTA0  PORTA0;  //  TIM2_CH1  TIM5_CH1
		kPWM_out_PORTA1  PORTA1;  //  TIM2_CH2  TIM5_CH2
		kPWM_out_PORTA2  PORTA2;  //  TIM2_CH3  TIM5_CH3  TIM9_CH1
		kPWM_out_PORTA3  PORTA3;  //  TIM2_CH4  TIM5_CH4  TIM9_CH2
		kPWM_out_PORTA5  PORTA5;  //  TIM2_CH1
		kPWM_out_PORTA6  PORTA6;  //  TIM3_CH1  TIM13_CH1
		kPWM_out_PORTA7  PORTA7;  //  TIM3_CH2  TIM14_CH1
		kPWM_out_PORTA8  PORTA8;  //  TIM1_CH1
		kPWM_out_PORTA9  PORTA9;  //  TIM1_CH2
		kPWM_out_PORTA10 PORTA10; //  TIM1_CH3
		kPWM_out_PORTA11 PORTA11; //  TIM1_CH4
		kPWM_out_PORTA15 PORTA15; //  TIM2_CH1

		kPWM_out_PORTB0  PORTB0;  //  TIM3_CH3
		kPWM_out_PORTB1  PORTB1;  //  TIM3_CH4
		kPWM_out_PORTB3  PORTB3;  //  TIM2_CH2
		kPWM_out_PORTB4  PORTB4;  //  TIM3_CH1
		kPWM_out_PORTB5  PORTB5;  //  TIM3_CH2
		kPWM_out_PORTB6  PORTB6;  //  TIM4_CH1
		kPWM_out_PORTB7  PORTB7;  //  TIM4_CH2
		kPWM_out_PORTB8  PORTB8;  //  TIM4_CH3  TIM10_CH1
		kPWM_out_PORTB9  PORTB9;  //  TIM4_CH4  TIM11_CH1
		kPWM_out_PORTB10 PORTB10; //  TIM2_CH3
		kPWM_out_PORTB11 PORTB11; //  TIM2_CH4
		kPWM_out_PORTB14 PORTB14; //  TIM12_CH1
		kPWM_out_PORTB15 PORTB15; //  TIM12_CH2

		kPWM_out_PORTC6  PORTC6;  //  TIM3_CH1  TIM8_CH1
		kPWM_out_PORTC7  PORTC7;  //  TIM3_CH2  TIM8_CH2
		kPWM_out_PORTC8  PORTC8;  //  TIM3_CH3  TIM8_CH3
		kPWM_out_PORTC9  PORTC9;  //  TIM3_CH4  TIM8_CH4

		kPWM_out_PORTD12 PORTD12; //  TIM4_CH1
		kPWM_out_PORTD13 PORTD13; //  TIM4_CH2
		kPWM_out_PORTD14 PORTD14; //  TIM4_CH3
		kPWM_out_PORTD15 PORTD15; //  TIM4_CH4

		kPWM_out_PORTE5  PORTE5;  //  TIM9_CH1
		kPWM_out_PORTE6  PORTE6;  //  TIM9_CH2
		kPWM_out_PORTE9  PORTE9;  //  TIM1_CH1
		kPWM_out_PORTE11 PORTE11; //  TIM1_CH2
		kPWM_out_PORTE13 PORTE13; //  TIM1_CH3
		kPWM_out_PORTE14 PORTE14; //  TIM1_CH4

		kPWM_out_PORTF6  PORTF6;  //  TIM10_CH1
		kPWM_out_PORTF7  PORTF7;  //  TIM11_CH1
		kPWM_out_PORTF8  PORTF8;  //  TIM13_CH1
		kPWM_out_PORTF9  PORTF9;  //  TIM14_CH1

		kPWM_out_PORTH9  PORTH9;  //  TIM12_CH2
	}kPWM_out;


#endif


#endif  //End of __kPWMDEFS_H
