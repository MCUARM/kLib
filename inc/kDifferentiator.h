#ifndef __kDifferentiator_H
#define __kDifferentiator_H

	#include "kLPF.h"
	#include "kDiscrete.h"
	#include "kAngle.h"

	class kDifferentiator : public kDiscrete
	{
		private:

			float last_value;
			bool first_launch;
			bool useLPF;

		public:

			kLPF	LPF;

			kDifferentiator(void);
			void useLowPassFilter(bool enable);
			float feed(float x);
			float feedAngle(kAngle_0_to_2pi & x);
			float feedAngle(kAngle_minus_pi_to_pi & x);

	};


#endif
