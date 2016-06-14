#ifndef __kPID_H
#define __kPID_H

	class kPID
	{
		private:

			float last_x;
			float last_integral;

			bool use_integral_saturation;
			float integral_upper_limit;
			float integral_lower_limit;

			bool use_output_saturation;
			float output_upper_limit;
			float output_lower_limit;

			float T;

		public:

			float Kp;
			float Kd;
			float Ki;


			kPID(void);

			float feed(float x);
			void setSamplingTime(float time);
			void useIntegralSaturation(bool state);
			void setIntegralSaturation(float lower_limit,float upper_limit);

			void useOutputSaturation(bool state);
			void setOutputSaturation(float lower_limit,float upper_limit);
	};


#endif
