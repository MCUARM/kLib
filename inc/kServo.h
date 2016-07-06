#ifndef __kServo_H
#define __kServo_H

	#include "kPWM.h"

	class kServo : public kPWM
	{
		private:


		public:

			kServo(void);
			void start(float initial_value=0.0);
			void operator = (float value);


	};


#endif
