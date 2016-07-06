#ifndef __kError_H
#define __kError_H

	#include "kSystem.h"

	class k_Error
	{
		public:
		
			k_Error(void);
			void report(unsigned int error_code);
	};

#endif
