#ifndef __kSaturate_H
#define __kSaturate_H

	class kSaturate
	{
		private:

			float up_limit;
			float down_limit;

		public:

			kSaturate(void);
			kSaturate(float lower_limit,float upper_limit);
			void set(float lower_limit,float upper_limit);
			float feed(float x);
	};


#endif
