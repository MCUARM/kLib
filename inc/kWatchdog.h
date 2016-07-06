#ifndef __kWatchdog_H
#define __kWatchdog_H

	#include "stm32f4xx.h"

	class k_Watchdog
	{
		public:
		

			k_Watchdog(void);
			bool init(float counting_period);
			void start(void);
			void feed(void);

	};

#endif
