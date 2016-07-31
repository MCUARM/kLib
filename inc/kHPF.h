#ifndef __kHPF_H
#define __kHPF_H


	#include "kAngle.h"
	#include "kDifferentiator.h"
	#include "kLPF.h"

	class kHPF
	{
		private:

			kDifferentiator deriv;
			kLPF inertia;
			float T;

		public:

			kHPF(void);
			kHPF(float sampling_time, float time_constant);
			void init(float sampling_time, float time_constant);
			void setTimeConstant(float time_constant);
			bool setSamplingTime(float sampling_time);
			float feed(float x);
			float feedAngle(kAngle_0_to_2pi & x);
			float feedAngle(kAngle_minus_pi_to_pi & x);



	};

#endif
