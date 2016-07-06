
#ifndef __kSystem_H
#define __kSystem_H

	#include "kConfig.h"



	#define K_UNUSED(param) (void)param

	#define kSystem_cmd_get_string "get"
	#define kSystem_cmd_info_string "info"

	#define kSystem_cmd_get 0
	#define kSystem_cmd_info 1

	#include "stm32f4xx.h"
	#include "core_cm4.h"

	#include "kPort.h"
	#include "kString.h"
	#include "kSerial.h"


	#if(kLib_config_USE_MODULE == 1)

		#include "kRegister.h"
		#include "kModule.h"

	#endif

	#if(kLib_config_USE_RTOS == 1)

		#include "kRTOS.h"


	#endif


	class k_System : public kModule
	{
		private:

			unsigned int SecondInTimerTicks;
			unsigned int usInTimerTicks;
			kRegister * pSystemRegister;

		public:

			k_System(void);

			void setIRQHandler(unsigned char channel,void (*IRQHandler_function_pointer)(void));
			void enableInterrupt(unsigned char channel,unsigned char preemptionPriority, unsigned char subPriority);

			unsigned int coreCLK(void);
			unsigned int APB1_CLK(void);
			unsigned int APB2_CLK(void);

			unsigned int APB1_Timer_CLK(void);
			unsigned int APB2_Timer_CLK(void);

			unsigned int systemTimerCLK(void);

			void waitus(unsigned short int microseconds);
			void waitms(unsigned short int miliseconds);
			void wait(unsigned short int seconds);



			kRegister * getSystemRegister(void);
			void setSystemRegister(kRegister * reg);

			char * processCommand(const char * cmd, char * response);

	};

	#ifdef __cplusplus
		extern "C" { extern void (* kSystem_isr_vector[98])(void); }
	#else
		extern void (* kSystem_isr_vector[98])(void);
	#endif

	extern k_System kSystem;

#endif
