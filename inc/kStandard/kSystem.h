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



#ifndef __kSystem_H
#define __kSystem_H

	#include "kConfig.h"
	#include "kMacro.h"




	#define kSystem_cmd_get_string "get"
	#define kSystem_cmd_info_string "info"

	#define kSystem_cmd_get 0
	#define kSystem_cmd_info 1

	#include "stm32f4xx.h"
	#include "core_cm4.h"

	#include "kPort.h"
	#include "kString.h"
	#include "kSerial.h"
	#include "kEXTI.h"



	#if(kLib_config_USE_MODULE == 1)

		#include "kRegister.h"
		#include "kModule.h"

	#endif

	#if(kLib_config_USE_RTOS == 1)

		#include "kRTOS.h"


	#endif

	class kPWM;
	class kPWM;

	class kPrivate
	{
		private:

			friend class kPort;
			friend class kPWM;
			friend class kSerial;
			friend class kI2CDeviceHardware;
			friend class kSPIDeviceHardware;
			friend class kEXTIHardware;

			union uintSplitter
			{
				unsigned int ui32;
				unsigned short int ui16[2];
				unsigned char ui8[4];
			};
			typedef struct
			{
				unsigned int bit[32];
			}intBitBand;



			/*
			 * this function prepare GPIO to be controlled by chosen peripheral,
			 * enable chosen peripheral clock and returns decoded peripheral
			 * base address. All settings are provided by passing hardware_code variable
			 * which codes all necessary options as described:
			 *
			 *   - bits [0:3]  -> GPIO pin number
			 *   - bits [4:7]  -> chosen GPIOx; 0=GPIA, 1=GPIOB, ...
			 *   - bits [8:11] -> alternate function number saved in AFR
			 *   - bits [12:13]-> GPIO mode saved in MODER
			 *   - bit  [14]   -> GPIO output type saved in OTYPER
			 *   - bits [15:21]-> Peripheral address,
			 *                    only bits specified by this mask: 0x0001FC00
			 *   - bits [22:23]-> RCC_APBx_ENR byte offset where exist bit responsible
			 *                    for chosen peripheral clock enable,
			 *                    only bits specified by this mask: 0x00000003
			 *   - bits [24:26]-> peripheral clock enable bit position in byte accessed
			 *                    RCC_APBx_ENR from 0 to 7
			 *   - bits [27:31]-> not used. Can be used for user purposes.
			 */
			static unsigned int* setupPeripheralOutput(unsigned int hardware_code);
			static unsigned int* getPeriheralAndEnableClock(unsigned int hardware_code);

			static unsigned int* getSRAMbitBand(unsigned int * reg, unsigned char bit);
			static unsigned int* getPeriphBitBand(unsigned int * reg, unsigned char bit);
			static intBitBand* getSRAMbitBand(unsigned int * reg);
			static intBitBand* getPeriphBitBand(unsigned int * reg);
	};



#if (kLib_config_USE_MODULE == 1)
	class k_System : public kModule
#else
	class k_System
#endif
	{

		private:

			unsigned int SecondInTimerTicks;
			unsigned int usInTimerTicks;


			#if (kLib_config_USE_MODULE == 1)
				kRegister * pSystemRegister;
			#endif


		public:

			k_System(void);

			void setIRQHandler(unsigned char channel,void (*IRQHandler_function_pointer)(void));
			void enableInterrupt(unsigned char channel,unsigned char preemptionPriority, unsigned char subPriority);


			#if(kLib_config_USE_RTOS == 1)

				__inline__ void addTask(void (*function_handler)(void*),const char * task_name,unsigned int stack_size,void * const params,unsigned long priority,kRTOS::task_t * const created_task) __attribute__((always_inline));

			#endif


			unsigned int coreCLK(void);
			unsigned int APB1_CLK(void);
			unsigned int APB2_CLK(void);
			unsigned int getPeripheralClock(unsigned int * peripheral_address);


			unsigned int APB1_Timer_CLK(void);
			unsigned int APB2_Timer_CLK(void);

			__inline__ unsigned int systemTimerCLK(void) __attribute__((always_inline));

			void waitus(unsigned short int microseconds);
			void waitms(unsigned short int miliseconds);
			void wait(unsigned short int seconds);
			unsigned int millis(void);
			unsigned int micros(void);
			bool isTimePassed(unsigned int * system_milliseconds_time);


			#if (kLib_config_USE_MODULE == 1)
				kRegister * getSystemRegister(void);
				void setSystemRegister(kRegister * reg);
				char * processCommand(const char * cmd, char * response);
			#endif

	};

	__attribute__((always_inline)) unsigned int k_System::systemTimerCLK()
	{
		return (this->coreCLK() >> 3);
	}

	#if(kLib_config_USE_RTOS == 1)

		__attribute__((always_inline)) void k_System::addTask(void (*function_handler)(void*),const char * task_name,unsigned int stack_size,void * const params,unsigned long priority,kRTOS::task_t * const created_task)
		{
			kRTOS::taskCreate(function_handler,task_name,stack_size,params,priority,created_task);
		}

	#endif



	#ifdef __cplusplus
		extern "C" { extern void (* kSystem_isr_vector[98])(void); }
	#else
		extern void (* kSystem_isr_vector[98])(void);
	#endif

	extern k_System kSystem;

#endif
