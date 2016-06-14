#ifndef __kIntegrator_H
#define __kIntegrator_H

	class kIntegrator
	{
		private:

			float last_value;
			float T;

			bool use_saturation;

			float up_limit;
			float dw_limit;

		public:

			kIntegrator(void);

			void setSamplingTime(float time);
			float feed(float x);

			void useSaturation(bool state);
			void setSaturation(float lower_limit,float upper_limit);


	};


#endif
