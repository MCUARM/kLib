#ifndef __kMediaDriver_H
#define __kMediaDriver_H

#include "fat.h"

	class kMediaDriver
	{
		protected:

			F_DRIVER * init( unsigned long driver_param );
			int readSector ( F_DRIVER * driver, void * data, unsigned long sector );
			int writeSector( F_DRIVER * driver, void * data, unsigned long sector );

		public:
	};


#endif
