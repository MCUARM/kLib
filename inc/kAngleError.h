#ifndef __kAngleError_H
#define __kAngleError_H

	class kAngleError
	{
		private:

			float min_value;
			float max_value;

			float * ref_sig;
			float * sig;

			bool last_chosen_path_1;
			float hist;

			float path_1,path_2;

		public:

			kAngleError(void);
			void attachData(float * reference_signal,float * signal);
			void setHisteresis(float range);
			float get(void);

	};


#endif
