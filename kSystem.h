
#ifndef __kSystem_H
#define __kSystem_H

	#include "stm32f4xx.h"
	#include "core_cm4.h"

	class k_System
	{
		private:

			unsigned char timerReady;
			unsigned int SecondInTimerTicks;

		public:

			k_System(void);
			void init(void);
			unsigned int coreCLK(void);
			unsigned int systemTimerCLK(void);

			void waitTicks(unsigned short ticks);
			void waitus(unsigned short microseconds);
			void waitms(unsigned short miliseconds);
			void wait(unsigned short seconds);

	};

	extern k_System kSystem;

#endif
