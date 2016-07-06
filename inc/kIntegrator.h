#ifndef __kIntegrator_H
#define __kIntegrator_H

	#include "kSaturate.h"

	class kIntegrator
	{
		private:

			float last_value;
			float T;
			bool use_saturation;

		public:

			kSaturate	Saturation;

			kIntegrator(void);
			void setSamplingTime(float time);
			float feed(float x);

			void useSaturation(bool state);


	};


#endif
