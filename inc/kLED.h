#ifndef __kLED_H
#define __kLED_H

	#include "kPWM.h"

	class kLED : public kPWM
	{
		public:

			kLED(void);
			__inline__ void run(void) __attribute__((always_inline));
			__inline__ void set(uint16_t bright) __attribute__((always_inline));
	};


	__attribute__((always_inline)) void kLED::run(void)
	{
		kPWM::run(0xFFFF,4000000);
	}

	__attribute__((always_inline)) void kLED::set(uint16_t bright)
	{
		kPWM::operator =(bright);
	}

#endif
