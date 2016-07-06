#ifndef __kPID_H
#define __kPID_H

	#include "kIntegrator.h"
	#include "kDifferentiator.h"
	#include "kSaturate.h"

	class kPID
	{
		private:

			bool use_output_saturation;

		public:

			float Kp;
			float Kd;
			float Ki;

			kSaturate OutputSaturation;
			kDifferentiator Derivative;
			kIntegrator Integral;

			kPID(void);

			float feed(float x);
			void setSamplingTime(float time);
			void useIntegralSaturation(bool state);
			void useOutputSaturation(bool state);


	};


#endif
