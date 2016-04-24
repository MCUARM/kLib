
#ifndef __kTimer_H
#define __kTimer_H

	#include "stm32f4xx.h"
	#include "kSystem.h"

	class kTimer
	{
		public:

			typedef enum
			{
				Timer1
			}kTimer_timer;

			typedef enum
			{
				trigger
			}kTimer_mode;


			class kTimerHardware
			{
				public:

					TIM_TypeDef * tim;

					kTimerHardware& operator = (const kTimer_timer & timerHard);
			};

			kTimerHardware hardware;

			void run(unsigned short int resolution, unsigned int tick_freq);
			bool checkTrigger(void);
	};

#endif
