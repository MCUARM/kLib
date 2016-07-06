#ifndef __kSOSystem_H
#define __kSOSystem_H

	class kSOSystem
	{
		private:

			float first_last_value;
			float second_last_value;

			float Ti;


			float a_coeff;
			float b_coeff;
			float c_coeff;

		public:

			kSOSystem(void);

			kSOSystem(float sampling_time, float damping_ratio, float resonance_freq_in_radians, float initial_output=0);
			void init(float sampling_time, float damping_ratio, float resonance_freq_in_radians, float initial_output=0);
			float feed(float x);



	};


#endif
