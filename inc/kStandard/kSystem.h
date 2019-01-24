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


	#if(kLib_config_USE_MODULE == 1)

		#include "kRegister.h"
		#include "kModule.h"

	#endif

	#if(kLib_config_USE_RTOS == 1)

		#include "kRTOS.h"


	#endif

	class kPWM;

// region PLATFORM_DEPENDED_STRUCTS

#if (kLib_config_PLATFORM == kLib_STM32F411xx)

	typedef struct
	{
		typedef enum
		{
			_PVD = 1, // PVD through EXTI line detection interrupt
			_TAMP_STAMP = 2, // Tamper and TimeStamp interrupts through the EXTI line
			_RTC_WKUP = 3, // RTC Wakeup interrupt through the EXTI line
			_FLASH = 4, // Flash global interrupt
			_RCC = 5, // RCC global interrupt
			_EXTI0 = 6, // EXTI Line0 interrupt
			_EXTI1 = 7, // EXTI Line1 interrupt
			_EXTI2 = 8, // EXTI Line2 interrupt
			_EXTI3 = 9, // EXTI Line3 interrupt
			_EXTI4 = 10, // EXTI Line4 interrupt
			_DMA1_Stream0 = 11, // DMA1 Stream0 global interrupt
			_DMA1_Stream1 = 12, // DMA1 Stream1 global interrupt
			_DMA1_Stream2 = 13, // DMA1 Stream2 global interrupt
			_DMA1_Stream3 = 14, // DMA1 Stream3 global interrupt
			_DMA1_Stream4 = 15, // DMA1 Stream4 global interrupt
			_DMA1_Stream5 = 16, // DMA1 Stream5 global interrupt
			_DMA1_Stream6 = 17, // DMA1 Stream6 global interrupt
			_ADC = 18, // ADC1, ADC2 and ADC3 global interrupts
			_CAN1_TX = 19, // CAN1 TX interrupts
			_CAN1_RX0 = 20, // CAN1 RX0 interrupts
			_CAN1_RX1 = 21, // CAN1 RX1 interrupt
			_CAN1_SCE = 22, // CAN1 SCE interrupt
			_EXTI9_5 = 23, // EXTI Line[9:5] interrupts
			_TIM1_BRK_TIM9 = 24, // TIM1 Break interrupt and TIM9 global interrupt
			_TIM1_UP_TIM10 = 25, // TIM1 Update interrupt and TIM10 global interrupt
			_TIM1_TRG_COM_TIM11 = 26, // TIM1 Trigger and Commutation interrupts and TIM11 global interrupt
			_TIM1_CC = 27, // TIM1 Capture Compare interrupt
			_TIM2 = 28, // TIM2 global interrupt
			_TIM3 = 29, // TIM3 global interrupt
			_TIM4 = 30, // TIM4 global interrupt
			_I2C1_EV = 31, // I2C1 event interrupt
			_I2C1_ER = 32, // I2C1 error interrupt
			_I2C2_EV = 33, // I2C2 event interrupt
			_I2C2_ER = 34, // I2C2 error interrupt
			_SPI1 = 35, // SPI1 global interrupt
			_SPI2 = 36, // SPI2 global interrupt
			_USART1 = 37, // USART1 global interrupt
			_USART2 = 38, // USART2 global interrupt
			_USART3 = 39, // USART3 global interrupt
			_EXTI15_10 = 40, // EXTI Line[15:10] interrupts
			_RTC_Alarm = 41, // RTC Alarms (A and B) through EXTI line interrupt
			_OTG_FS_WKUP = 42, // USB On-The-Go FS Wakeup through EXTI line interrupt
			_TIM8_BRK_TIM12 = 43, // TIM8 Break interrupt and TIM12 global interrupt
			_TIM8_UP_TIM13 = 44, // TIM8 Update interrupt and TIM13 global interrupt
			_TIM8_TRG_COM_TIM14 = 45, // TIM8 Trigger and Commutation interrupts and TIM14 global interrupt
			_TIM8_CC = 46, // TIM8 Capture Compare interrupt
			_DMA1_Stream7 = 47, // DMA1 Stream7 global interrupt
			_FSMC = 48, // FSMC global interrupt
			_SDIO = 49, // SDIO global interrupt
			_TIM5 = 50, // TIM5 global interrupt
			_SPI3 = 51, // SPI3 global interrupt
			_UART4 = 52, // UART4 global interrupt
			_UART5 = 53, // UART5 global interrupt
			_TIM6_DAC = 54, // TIM6 global interrupt, DAC1 and DAC2 underrun error interrupts
			_TIM7 = 55, // TIM7 global interrupt
			_DMA2_Stream0 = 56, // DMA2 Stream0 global interrupt
			_DMA2_Stream1 = 57, // DMA2 Stream1 global interrupt
			_DMA2_Stream2 = 58, // DMA2 Stream2 global interrupt
			_DMA2_Stream3 = 59, // DMA2 Stream3 global interrupt
			_DMA2_Stream4 = 60, // DMA2 Stream4 global interrupt
			_ETH = 61, // Ethernet global interrupt
			_ETH_WKUP = 62, // Ethernet Wakeup through EXTI line interrupt
			_CAN2_TX = 63, // CAN2 TX interrupts
			_CAN2_RX0 = 64, // CAN2 RX0 interrupts
			_CAN2_RX1 = 65, // CAN2 RX1 interrupt
			_CAN2_SCE = 66, // CAN2 SCE interrupt
			_OTG_FS = 67, // USB On The Go FS global interrupt
			_DMA2_Stream5 = 68, // DMA2 Stream5 global interrupt
			_DMA2_Stream6 = 69, // DMA2 Stream6 global interrupt
			_DMA2_Stream7 = 70, // DMA2 Stream7 global interrupt
			_USART6 = 71, // USART6 global interrupt
			_I2C3_EV = 72, // I2C3 event interrupt
			_I2C3_ER = 73, // I2C3 error interrupt
			_OTG_HS_EP1_OUT = 74, // USB On The Go HS End Point 1 Out global interrupt
			_OTG_HS_EP1_IN = 75, // USB On The Go HS End Point 1 In global interrupt
			_OTG_HS_WKUP = 76, // USB On The Go HS Wakeup through EXTI interrupt
			_OTG_HS = 77, // USB On The Go HS global interrupt
			_DCMI = 78, // DCMI global interrupt
			_CRYP = 79, // CRYP crypto global interrupt
			_HASH_RNG = 80, // Hash and Rng global interrupt
			_FPU = 81 // FPU global interrupt
		}kSystem_IRQ_channel_enum;
	}kSystem_IRQ_channel;


#endif
#if (kLib_config_PLATFORM == kLib_STM32F429xx)

	typedef struct
	{
		typedef enum
		{
		}kSystem_IRQ_channel_enum;
	}kSystem_IRQ_channel;


#endif
#if (kLib_config_PLATFORM == kLib_STM32L053xx)

	typedef struct
	{
		typedef enum
		{
		}kSystem_IRQ_channel_enum;
	}kSystem_IRQ_channel;


#endif


// endregion PLATFORM_DEPENDED_STRUCTS

	class kPrivate
	{
		private:

			friend class kPort;
			friend class kPWM;
			friend class kADCHardware;
			friend class kSerialHardware;
			friend class kI2CHardware;
			friend class kSPIHardware;
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

			// this function extract peripheral address from hardware_code and enables its clock in RCC registers
			static unsigned int* getPeriheralAndEnableClock(unsigned int hardware_code);
			// this function extract user code (5 most significant bits) from hardware_code
			static uint8_t getUserCode(uint32_t hardware_code);

			// bitband related functions
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


			static kSystem_IRQ_channel * IRQ;

			void setIRQHandler(unsigned char channel,void (*IRQHandler_function_pointer)(void));
			void enableInterrupt(unsigned char channel,unsigned char preemptionPriority, unsigned char subPriority);
			void disableInterrupt(unsigned char channel);

			#if(kLib_config_USE_RTOS == 1)

				__inline__ void addTask(void (*function_handler)(void*),const char * task_name,unsigned int stack_size,void * const params,unsigned long priority,kRTOS::task_t * const created_task) __attribute__((always_inline));

			#endif

			// this function terminates user application
			// and runs internal bootloader
			void boot(void);
			// this function reset system so that it starts
			// like in case of power on
			void reset(void);

			// clocks related functions
			void deInitClocks(void);
			unsigned int coreCLK(void);
			unsigned int APB1_CLK(void);
			unsigned int APB2_CLK(void);
			unsigned int getPeripheralClock(unsigned int * peripheral_address);
			unsigned int APB1_Timer_CLK(void);
			unsigned int APB2_Timer_CLK(void);
			__inline__ unsigned int systemTimerCLK(void) __attribute__((always_inline));

			// timing related functions
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
