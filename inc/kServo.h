#ifndef __kServo_H
#define __kServo_H

	#include "kPWM.h"

	class kServo : public kPWM
	{
		private:

			float fMax;
			float fMid;
			float fMin;

			float scale;

			uint16_t iMax;
			int16_t iMid;
			uint16_t iMin;


		public:

			kServo(void);

			bool setRange(float min,float max,uint16_t min_pwm_width_us,uint16_t max_pwm_width_us);
			__inline__ void run(void) __attribute__((always_inline));
			void operator = (float value);


	};

	__attribute__((always_inline)) void kServo::run(void)
	{
		kPWM::run(20000,1000000);
	}
#endif
