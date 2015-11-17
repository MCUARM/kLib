
#ifndef __kQuaternion_H
#define __kQuaternion_H

    #include "math.h"

	class kQuaternion
	{
		public:
		
			float r;
			float i;
			float j;
			float k;
			
			void operator += (kQuaternion & q);
			void operator -= (kQuaternion & q);
			void operator *= (kQuaternion & q);
			void operator *= (float & scalar);

            kQuaternion operator *(kQuaternion & q);
            kQuaternion operator +(kQuaternion & q);
            kQuaternion operator -(kQuaternion & q);

            void operator = (kQuaternion & q);
            bool operator == (kQuaternion & q);
			
			float norm(void);
			kQuaternion inv(void);
			kQuaternion versor(void);
			kQuaternion conjugate(void);
			kQuaternion reciprocal(void);
			
			
    };
	



#endif
