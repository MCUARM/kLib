#ifndef __kAxisAngle_H
#define __kAxisAngle_H


	#include "kVector.h"

	class kAxisAngle
	{
		public:

			kAxisAngle(void);
			kAxisAngle(kVector3 & axis, float angle);
			kAxisAngle(float x, float y, float z, float angle);


			float angle;
			kVector3 axis;

			static kAxisAngle create(kVector3 & axis, float angle);
			static kAxisAngle create(float x, float y, float z, float angle);

	};

#endif
