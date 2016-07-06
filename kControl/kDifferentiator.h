#ifndef __kDifferentiator_H
#define __kDifferentiator_H

	#include "kLPF.h"

	class kDifferentiator
	{
		private:

			float last_value;
			bool first_launch;
			float T;
			bool useLPF;

		public:

			kLPF	LPF;

			kDifferentiator(void);
			void setSamplingTime(float time);
			float feed(float x);
			void useLowPassFilter(bool enable);

	};


#endif
