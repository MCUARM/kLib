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

#ifndef __kLKF_H
#define __kLKF_H

	class kLKF;


	#include "kMatrix.h"
	#include "kSystem.h"

	class kLKF
	{
		protected:

			kMatrix *p_Ft;
			kMatrix *p_Ht;
			kMatrix *p_K;
			kMatrix *p_I;
			kMatrix *p_P_a_priori;
			kMatrix *p_P_a_posteriori;

			kMatrix *p_T1;
			kMatrix *p_T2;

			kVector *p_x_a_priori;
			kVector *p_y;

			kVector *p_t1;
			kVector *p_t2;


			kMatrix *p_F;
			kMatrix *p_B;
			kMatrix *p_H;
			kMatrix *p_Q;
			kMatrix *p_R;

			kVector *p_x;
			kVector *p_u;
			kVector *p_z;



		public:


			virtual void invertMatrix(kMatrix &result,kMatrix & matrix);

			void init(void);
			void process(void);

	};


	class kLKF_2x_2u : public kLKF
	{
		protected:



			kMatrix2x2 Ft;
			kMatrix2x2 Ht;
			kMatrix2x2 K;
			kMatrix2x2 I;
			kMatrix2x2 P_a_priori;
			kMatrix2x2 P_a_posteriori;

			kMatrix2x2 T1;
			kMatrix2x2 T2;

			kVector2 x_a_priori;
			kVector2 y;

			kVector2 t1;
			kVector2 t2;


			void invertMatrix(kMatrix &result,kMatrix & matrix);

		public:

			kLKF_2x_2u(void);

			kMatrix2x2 F;
			kMatrix2x2 B;
			kMatrix2x2 H;
			kMatrix2x2 Q;
			kMatrix2x2 R;

			kVector2 x;
			kVector2 u;
			kVector2 z;


	};

#endif
