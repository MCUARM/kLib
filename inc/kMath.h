#ifndef __kMath_H
#define __kMath_H


	#include "kUnits.h"
	#include "kQuaternion.h"
	#include "kVector.h"
	#include "kAxisAngle.h"
	#include "kMatrix.h"


	#define DEG_2_RAD_SCALE_FACTOR 0.017453292
	#define RAD_2_DEG_SCALE_FACTOR 57.29577951



	class kMath
	{
		public:

			static const float _pi;
			static const float _2pi;

			static float rad2deg(float input);
			static float deg2rad(float input);

			static float abs(float input);
	};

#endif
