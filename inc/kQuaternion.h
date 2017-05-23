/***********************************************************************************
 *                                                                                 *
 *   kLib - C++ development tools for ARM Cortex-M devices                         *
 *                                                                                 *
 *     Copyright (c) 2016, project author Paweł Zalewski                                          *
 *     All rights reserved.                                                        *
 *                                                                                 *
 ***********************************************************************************
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions  in  binary  form  must  reproduce the above copyright
 *      notice,  this  list  of conditions and the following disclaimer in the
 *      documentation  and/or  other materials provided with the distribution.
 *   3. Neither  the  name  of  the  copyright  holder  nor  the  names of its
 *      contributors  may  be used to endorse or promote products derived from
 *      this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,  BUT NOT LIMITED  TO, THE
 *   IMPLIED WARRANTIES OF MERCHANTABILITY  AND FITNESS FOR A PARTICULAR PURPOSE
 *   ARE DISCLAIMED.  IN NO EVENT SHALL  THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *   LIABLE  FOR  ANY  DIRECT,  INDIRECT,  INCIDENTAL,  SPECIAL,  EXEMPLARY,  OR
 *   CONSEQUENTIAL  DAMAGES  (INCLUDING,  BUT  NOT  LIMITED  TO,  PROCUREMENT OF
 *   SUBSTITUTE  GOODS  OR SERVICES;  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *   INTERRUPTION) HOWEVER  CAUSED  AND  ON  ANY THEORY OF LIABILITY, WHETHER IN
 *   CONTRACT,  STRICT  LIABILITY,  OR  TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *   ARISING  IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 *
 */
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
			kQuaternion(const kVector3 & v);

			void operator += (const kQuaternion & q);
            kQuaternion operator +(const kQuaternion & q);

			void operator -= (const kQuaternion & q);
            kQuaternion operator -(const kQuaternion & q);

			void operator *= (const kQuaternion & q);
			void operator *= (const float &scalar);
			void operator *= (const kVector3 & v);
			kQuaternion operator *(const kQuaternion & q);
			kQuaternion operator *(const kVector3 & v);
			kQuaternion operator *(float & scalar);

			void operator /= (float scalar);
            kQuaternion operator /(float scalar);

            void operator = (const kQuaternion & q);
            bool operator == (const kQuaternion & q);
			
			float norm(void);
			kQuaternion inv(void);
			kQuaternion versor(void);
			kQuaternion conjugate(void);
			kQuaternion reciprocal(void);
			
			static float dotProduct(const kQuaternion & q1,const kQuaternion & q2);

			kVector3 toEulerAngles(void);
			kAxisAngle toAxisAngle(void);

			static kQuaternion fromAxisAngle(const kAxisAngle & axis_angle);
			static kQuaternion fromEulerAngles(kVector3 Euler_angles);

			static kQuaternion create(float r,float i, float j, float k);
			static kQuaternion create(const kVector3 & v);

			static kQuaternion slerp(const kQuaternion & begin, const kQuaternion & end, float normalized_time);

    };
	



#endif
