#ifndef __kRCChannel_H
#define __kRCChannel_H

	#include "kPWM.h"


	class kRCChannel : public kPWM
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

			kRCChannel(void);
			bool isGood(void);
			bool setRange(float min,float max,uint16_t min_pwm_width_us,uint16_t max_pwm_width_us);
			operator float();

	};

#endif
