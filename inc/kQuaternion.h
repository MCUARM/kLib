
#ifndef __kQuaternion_H
#define __kQuaternion_H

	class kQuaternion;

    #include "math.h"
	#include "kVector.h"
	#include "kAxisAngle.h"
	#include "kMath.h"

	class kQuaternion
	{
		public:
		
			float r;
			float i;
			float j;
			float k;
			

			kQuaternion(void);
			kQuaternion(float r,float i, float j, float k);
			kQuaternion(kVector3 & v);

			void operator += (kQuaternion & q);
			void operator -= (kQuaternion & q);

			void operator *= (kQuaternion & q);
			void operator *= (float & scalar);
			void operator *= (kVector3 v);

            kQuaternion operator *(kQuaternion & q);
            kQuaternion operator *(kVector3 v);

            kQuaternion operator +(kQuaternion & q);
            kQuaternion operator -(kQuaternion & q);

            void operator = (kQuaternion q);


            bool operator == (kQuaternion & q);
			
			float norm(void);
			kQuaternion inv(void);
			kQuaternion versor(void);
			kQuaternion conjugate(void);
			kQuaternion reciprocal(void);
			

			kVector3 toEulerAngles(void);
			kAxisAngle toAxisAngle(void);

			static kQuaternion fromAxisAngle(kAxisAngle & axis_angle);
			static kQuaternion fromEulerAngles(kVector3 Euler_angles);

			static kQuaternion create(float r,float i, float j, float k);
			static kQuaternion create(kVector3 & v);

			static kQuaternion SLERP(kQuaternion & begin, kQuaternion end, float normalized_time);

    };
	



#endif
