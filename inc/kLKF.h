#ifndef __kLKF_H
#define __kLKF_H

	class LkF;


	#include "kMatrix.h"
	#include "kSystem.h"

	class kLKF
	{
		public:


			void init(void);
			void process(void);

	};


	class kLKF_2x_2u : public kLKF
	{
		protected:



			kMatrix_2x2 Ft;
			kMatrix_2x2 Ht;
			kMatrix_2x2 K;
			kMatrix_2x2 I;
			kMatrix_2x2 P_a_priori;
			kMatrix_2x2 P_a_posteriori;

			kMatrix_2x2 T1;
			kMatrix_2x2 T2;

			kVector2 x_a_priori;
			kVector2 y;

			kVector2 t1;
			kVector2 t2;


		public:

			kLKF_2x_2u(void);

			void init(void);
			void process(void);

			kMatrix_2x2 F;
			kMatrix_2x2 B;
			kMatrix_2x2 H;
			kMatrix_2x2 Q;
			kMatrix_2x2 R;

			kVector2 x;
			kVector2 u;
			kVector2 z;
	};

#endif
