#ifndef __kComplementaryFilter_H
#define __kComplementaryFilter_H

	#include "kLPF.h"
	#include "kHPF.h"
	#include "kAngle.h"

	class kComplementaryFilter
	{
		private:

			kLPF LPF;
			kHPF HPF;

		public:

			bool setSamplingTime(float sampling_time);
			void setTimeConstant(float time_constant);
			float feed(float HPF_input,float LPF_input);
			float feedAngle(kAngle_0_to_2pi & HPF_input,kAngle_0_to_2pi LPF_input);
			float feedAngle(kAngle_minus_pi_to_pi & HPF_input,kAngle_minus_pi_to_pi LPF_input);
	};

#endif
