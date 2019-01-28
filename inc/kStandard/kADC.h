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



#ifndef __kADC_H
#define __kADC_H

	#include "kSystem.h"

	// This library provides analog signal conversions API in synchronious mode


// region PLATFORM_DEPENDED_STRUCTS

#if (kLib_config_PLATFORM == kLib_STM32F411xx)

	typedef struct
	{
		typedef enum
		{
			PORTA0  = 0x00643000,
			PORTA1  = 0x08643001,
			PORTA2  = 0x10643002,
			PORTA3  = 0x18643003,
			PORTA4  = 0x20643004,
			PORTA5  = 0x28643005,
			PORTA6  = 0x30643006,
			PORTA7  = 0x38643007,
			PORTB0  = 0x40643010,
			PORTB1  = 0x48643011,
			PORTC0  = 0x50643020,
			PORTC1  = 0x58643021,
			PORTC2  = 0x60643022,
			PORTC3  = 0x68643023,
			PORTC4  = 0x70643024,
			PORTC5  = 0x78643025
		}kADC_ADC1_CHANNEL_ENUM;
	}kADC_ADC1_CHANNEL_STRUCT;


#endif
#if (kLib_config_PLATFORM == kLib_STM32F429xx)


#endif
#if (kLib_config_PLATFORM == kLib_STM32L053xx)


#endif


// endregion PLATFORM_DEPENDED_STRUCTS



	// Interrupt flags for enabling or disabling specific interrupt
	typedef struct
	{
		typedef enum
		{
			EndOfConversion = 0x20,
			Overrun = 0x04000000
		}kADC_Interrupt_enum;
	}kADC_Interrupt_struct;



	// Clock setttings struct ADC clock is APB2 bus clock divieded by prescaler
	typedef struct
	{
		typedef enum
		{
			APB2_div_2 = 0,
			APB2_div_4 = 1,
			APB2_div_6 = 2,
			APB2_div_8 = 3
		}kADC_Clock_enum;
	}kADC_Clock_struct;


	// ADC hardware class definition for hardware setup
	class kADCHardware
	{
		private:

			friend class kADC;

			ADC_TypeDef * adc;
			uint8_t channel_number;

		public:

			void operator = (uint32_t hard_code);

	};


	class kADC
	{
		public:

// region ADC_DECLARATIONS

		#if (kLib_config_PLATFORM == kLib_STM32F411xx)

			static const kADC_ADC1_CHANNEL_STRUCT * _ADC1;

		#endif

		#if (kLib_config_PLATFORM == kLib_STM32F429xx)


		#endif

		#if (kLib_config_PLATFORM == kLib_STM32L053xx)


		#endif



// endregion ADC_DECLARATIONS

			// hardware object implementation for
			// setting up hardware. Settings must be called before
			// run() method is invoked
			kADCHardware hardware;

			// struct pointer to access Interrput flags
			static const kADC_Interrupt_struct * Interrupt;
			// struct pointer to access clock enumerateted values
			static const kADC_Clock_struct * Clock;

			// this function set up clocks and runs ADC chosen earlier
			// in hardware settings
			void run(kADC_Clock_struct::kADC_Clock_enum clock_divider);
			// this function provides ADC conversion in synchroniuos mode
			// it setup ADC channel, perform conversion, wait till end and
			// return back result of the conversion
			uint16_t read();

			// this function is used to enable chosen interrupt
			void enableInterrupt(uint32_t interrupt_flags);
			// this function is used to disable chosen interrupt
			void disableInterrupt(uint32_t interrupt_flags);
	};


#endif
