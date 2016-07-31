#ifndef __kRandom_H
#define __kRandom_H

	#include "stm32f4xx.h"

	class kRandom
	{
		public:


			static void init(void);
			static unsigned int get(void);

	};

#endif
