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
#ifndef __kVector_H
#define __kVector_H



	#include "math.h"

	class kVector2;
	class kVector3;
	class kVector4;

	class kQuaternion;

	class kVector
	{
		friend class kMatrix;
		friend class kLKF;

		protected:

			float * buff;
			unsigned char elements;

			static void add(kVector & result,const kVector & vector_1,const kVector & vector_2);
			static void subtract(kVector & result,const kVector & vector_1,const kVector & vector_2);
			static void multiply(kVector & result,const kVector & vector,float value);

			void operator =  (const kVector & v);
			void operator += (const kVector & v);
			void operator -= (const kVector & v);
	        bool operator == (const kVector & v);

		public:

			void operator *= (float scalar);
			float length(void) const;
			void makeUnit(void);


			static void add(kVector2 & result,kVector2 & vector_1, kVector2 & vector_2);
			static void subtract(kVector2 & result,kVector2 & vector_1, kVector2 & vector_2);
			static void multiply(kVector2 & result,kVector2 & vector,float value);


	};

	class kVector2 : public kVector
	{
		public:

			float x;
			float y;

			kVector2(void);
			kVector2(kVector2 & other);
			kVector2(float X, float Y);

			void operator += (kVector2 & v);
			void operator -= (kVector2 & v);
            void operator = (kVector2 & v);
            bool operator == (kVector2 & v);

			void rotate(float angle);
	};

	class kVector3 : public kVector
	{
		public:
		
			float x;
			float y;
			float z;
			
			kVector3(void);
			kVector3(const kVector3 & other);
			kVector3(float X, float Y, float Z);

			static kVector3 create(float X, float Y, float Z);

			void operator += (const kVector3 & v);
			void operator -= (const kVector3 & v);
			void operator *= (float scalar);
			void operator /= (float scalar);



			kVector3 operator +(const kVector3 & v);
			kVector3 operator -(const kVector3 & v);
			kVector3 operator *(float scalar) const;
			kVector3 operator /(float scalar) const;

            void operator = (const kVector3 & v);
            void operator = (const kQuaternion & q);

            bool operator == (kVector3 & v);
			
			float length(void) const;
			void makeUnit(void);
			void crossProduct(kVector3 & vector_1, kVector3 & vector_2);
			void dotProduct(kVector3 & vector_1, kVector3 & vector_2);
			
			void rotateX(float angle);
			void rotateY(float angle);
			void rotateZ(float angle);

			void rotateXY(kVector2 & angles);
			void rotateXZ(kVector2 & angles);
			void rotateYX(kVector2 & angles);
			void rotateYZ(kVector2 & angles);
			void rotateZX(kVector2 & angles);
			void rotateZY(kVector2 & angles);

    };
	
	class kVector4 : kVector
	{
		public:

			float x;
			float y;
			float z;
			float w;


			kVector4(void);
			kVector4(const kVector4 & other);
			kVector4(float X, float Y, float Z, float W);

			static kVector4 create(float X, float Y, float Z, float W);

			void operator += (kVector4 & v);
			void operator -= (kVector4 & v);
			void operator *= (float scalar);
			void operator /= (float scalar);

			kVector4 operator +(kVector4 & v);
			kVector4 operator -(kVector4 & v);
			kVector4 operator *(float scalar) const;
			kVector4 operator /(float scalar);

            void operator = (const kVector4 & v);
            void operator = (const kQuaternion & q);

            bool operator == (kVector4 & v);

			float length(void);
			void makeUnit(void);
			float dotProduct(kVector4 & vector_1, kVector4 & vector_2);
	};


#endif
