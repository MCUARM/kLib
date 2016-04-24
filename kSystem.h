
#ifndef __kSystem_H
#define __kSystem_H

	#define K_UNUSED(param) (void)param


	#include "stm32f4xx.h"
	#include "core_cm4.h"

	#include "kPort.h"
	#include "kSerial.h"

	class k_System
	{
		private:

			unsigned char timerReady;
			unsigned int SecondInTimerTicks;

		public:

			k_System(void);
			void init(void);

			void setIRQHandler(unsigned char channel,void (*IRQHandler_function_pointer)(void));
			void enableInterrupt(unsigned char channel,unsigned char preemptionPriority, unsigned char subPriority);

			unsigned int coreCLK(void);
			unsigned int APB1_CLK(void);
			unsigned int APB2_CLK(void);

			unsigned int APB1_Timer_CLK(void);
			unsigned int APB2_Timer_CLK(void);

			unsigned int systemTimerCLK(void);

			void waitTicks(unsigned short ticks);
			void waitus(unsigned short microseconds);
			void waitms(unsigned short miliseconds);
			void wait(unsigned short seconds);

	};



	extern k_System kSystem;

#endif
