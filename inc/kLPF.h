#ifndef __kLPF_H
#define __kLPF_H

	#include "kFOSystem.h"
	#include "kAngle.h"
	#include "kMath.h"

	class kLPF : public kFOSystem
	{

		public:

			kLPF(void);
			float feedAngle(kAngle_0_to_2pi & x);
			float feedAngle(kAngle_minus_pi_to_pi & x);
	};


#endif
