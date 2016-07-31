#ifndef __kFOSystem_H
#define __kFOSystem_H

	#include "kDiscrete.h"

	class kFOSystem : public kDiscrete
	{
		protected:

			float last_value;
			float T;

			float a_coeff;
			float b_coeff;

		public:

			kFOSystem(void);
			kFOSystem(float sampling_time, float time_constant, float initial_output=0);
			void setTimeConstant(float time_constant);
			void init(float sampling_time, float time_constant, float initial_output=0);
			bool setSamplingTime(float sampling_time);
			float feed(float x);



	};


#endif
