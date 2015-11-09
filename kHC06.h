#ifndef __kHC06_H
#define __kHC06_H

	#include <kSerial.h>

	class kHC06 : public kSerial
	{
		private:

		public:

			void setName(char * new_name);
			void setPin(char * new_pin);

	};


#endif
