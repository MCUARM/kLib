
#ifndef __kVector_H
#define __kVector_H



	#include "math.h"

	class kVector2;
	class kVector3;

	class kQuaternion;

	class kVector
	{
		friend class kMatrix;
		friend class kLKF;

		protected:

			float * buff;
			unsigned char elements;

			static void add(kVector & result,kVector & vector_1, kVector & vector_2);
			static void subtract(kVector & result,kVector & vector_1, kVector & vector_2);
			static void multiply(kVector & result,kVector & vector,float value);

			void operator =  (kVector & v);
			void operator += (kVector & v);
			void operator -= (kVector & v);
	        bool operator == (kVector & v);

		public:

			void operator *= (float scalar);
			float length(void);
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
			kVector3(kVector3 & other);
			kVector3(float X, float Y, float Z);

			void operator += (kVector3 & v);
			void operator -= (kVector3 & v);
			void operator *= (float scalar);

			kVector3 operator +(kVector3 & v);
			kVector3 operator -(kVector3 & v);
			kVector3 operator *(float scalar);

            void operator = (const kVector3 & v);
            void operator = (const kQuaternion & q);

            bool operator == (kVector3 & v);
			
			float length(void);
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
	



#endif
