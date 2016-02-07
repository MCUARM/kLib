#ifndef __kFOSystem_H
#define __kFOSystem_H

	class kFOSystem
	{
		private:

			float last_value;
			float Ti;
			float T;

			float a_coeff;
			float b_coeff;

		public:

			kFOSystem(void);
			kFOSystem(float sampling_time, float time_constant, float initial_output=0);

			void init(float sampling_time, float time_constant, float initial_output=0);
			float feed(float x);



	};


#endif
