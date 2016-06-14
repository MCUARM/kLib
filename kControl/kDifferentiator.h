#ifndef __kDifferentiator_H
#define __kDifferentiator_H

	class kDifferentiator
	{
		private:

			float last_value;
			bool first_launch;
			float T;

		public:

			kDifferentiator(void);
			void setSamplingTime(float time);
			float feed(float x);

	};


#endif
