#ifndef __kLPF_H
#define __kLPF_H

	#include "kFOSystem.h"

	class kLPF : public kFOSystem
	{

		public:

			kLPF(void);
			kLPF(float sampling_time, float time_constant, float initial_output=0);

	};


#endif
