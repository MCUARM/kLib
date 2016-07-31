#ifndef __kIntegrator_H
#define __kIntegrator_H

	#include "kSaturate.h"
	#include "kDiscrete.h"
	#include "kAngle.h"

	class kIntegrator : public kDiscrete
	{
		private:

			float last_value;
			bool use_saturation;

		public:

			kSaturate	Saturation;

			kIntegrator(void);
			float feed(float x);
			float feedAngle(kAngle_0_to_2pi & x);
			float feedAngle(kAngle_minus_pi_to_pi & x);

			void useSaturation(bool state);


	};


#endif
