
#ifndef __kAngle_H
#define __kAngle_H

	#include "kMath.h"

	class kAngle;
	class kAngle_minus_pi_to_pi;

	class kAngle_0_to_2pi
	{
		friend class kAngle;
		friend class kAngle_minus_pi_to_pi;

		protected:

			float value;

		public:


			kAngle_0_to_2pi(const kAngle_minus_pi_to_pi & other);
			kAngle_0_to_2pi(const float & f);

			operator float();

			void operator = (float & val);
			void operator += (float & val);
			void operator -= (float & val);
			void operator *= (float & val);
			void operator /= (float & val);

			void operator = (kAngle_0_to_2pi & ang);
			void operator += (kAngle_0_to_2pi & ang);
			void operator -= (kAngle_0_to_2pi & ang);
			void operator *= (kAngle_0_to_2pi & ang);
			void operator /= (kAngle_0_to_2pi & ang);

			float operator +(kAngle_0_to_2pi & ang);
			float operator -(kAngle_0_to_2pi & ang);
			float operator *(kAngle_0_to_2pi & ang);
			float operator /(kAngle_0_to_2pi & ang);

			bool operator == (kAngle_0_to_2pi & ang);
			bool operator > (kAngle_0_to_2pi & ang);
			bool operator < (kAngle_0_to_2pi & ang);

			void operator = (kAngle_minus_pi_to_pi & ang);
	};


	class kAngle_minus_pi_to_pi
	{
		friend class kAngle;
		friend class kAngle_0_to_2pi;

		protected:

			float value;

		public:


			kAngle_minus_pi_to_pi(const kAngle_0_to_2pi & other);
			kAngle_minus_pi_to_pi(const float & f);

			operator float();


			void operator = (float & val);
			void operator += (float & val);
			void operator -= (float & val);
			void operator *= (float & val);
			void operator /= (float & val);

			void operator = (kAngle_minus_pi_to_pi & ang);
			void operator += (kAngle_minus_pi_to_pi & ang);
			void operator -= (kAngle_minus_pi_to_pi & ang);
			void operator *= (kAngle_minus_pi_to_pi & ang);
			void operator /= (kAngle_minus_pi_to_pi & ang);

			float operator +(kAngle_minus_pi_to_pi & ang);
			float operator -(kAngle_minus_pi_to_pi & ang);
			float operator *(kAngle_minus_pi_to_pi & ang);
			float operator /(kAngle_minus_pi_to_pi & ang);

			bool operator == (kAngle_minus_pi_to_pi & ang);
			bool operator > (kAngle_minus_pi_to_pi & ang);
			bool operator < (kAngle_minus_pi_to_pi & ang);

			void operator = (kAngle_0_to_2pi & ang);
	};




	class kAngle
	{

		public:

		static float setInBounds_0_to_2pi(float angle_in_radians);
		static float setInBounds_minus_pi_to_pi(float angle_in_radians);

		static float getAngleError(kAngle_0_to_2pi & reference_signal,kAngle_0_to_2pi & signal);
		static float getAngleError(kAngle_minus_pi_to_pi & reference_signal,kAngle_minus_pi_to_pi & signal);
	};

#endif
