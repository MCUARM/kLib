#ifndef __kRandom_H
#define __kRandom_H

	#include "stm32f4xx.h"

	class k_Random
	{
		private:


		public:

			k_Random(void);
			void init(void);
			unsigned int get(void);

	};

#endif
