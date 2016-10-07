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

#include "kLKF.h"


void kLKF::init(void)
{
	kMatrix::transpose(*p_Ft,*p_F);
	kMatrix::transpose(*p_Ht,*p_H);
	kMatrix::makeEye(*p_I);
}
void kLKF::process(void)
{
	// Prediction
	kMatrix::multiply(*p_t1,*p_F,*p_x);
	kMatrix::multiply(*p_t2,*p_B,*p_u);
	kVector::add(*p_x_a_priori,*p_t1,*p_t2);

	// Error propagation
	kMatrix::multiply(*p_T1,*p_F,*p_P_a_posteriori);
	kMatrix::multiply(*p_T2,*p_T1,*p_Ft);
	kMatrix::add(*p_P_a_priori,*p_T2,*p_Q);


	// Correction
	kMatrix::multiply(*p_t1,*p_H,*p_x_a_priori);
	kVector::subtract(*p_y,*p_z,*p_t1);

	kMatrix::multiply(*p_T1,*p_H,*p_P_a_priori);
	kMatrix::multiply(*p_T2,*p_T1,*p_Ht);
	kMatrix::add(*p_T1,*p_T2,*p_R);

	this->invertMatrix(*p_T2,*p_T1);
	kMatrix::multiply(*p_T1,*p_P_a_priori,*p_Ht);
	kMatrix::multiply(*p_K,*p_T1,*p_T2);

	kMatrix::multiply(*p_t1,*p_K,*p_y);
	kVector::add(*p_x,*p_x_a_priori,*p_t1);

	kMatrix::multiply(*p_T1,*p_K,*p_H);
	kMatrix::subtract(*p_T2,*p_I,*p_T1);
	kMatrix::multiply(*p_P_a_posteriori,*p_T2,*p_P_a_priori);
}
void kLKF::invertMatrix(kMatrix &result,kMatrix & matrix)
{
	K_UNUSED(result);
	K_UNUSED(matrix);
}



kLKF_2x_2u::kLKF_2x_2u(void)
{
	this->p_Ft = &this->Ft;
	this->p_Ht = &this->Ht;
	this->p_K = &this->K;
	this->p_I = &this->I;
	this->p_P_a_priori = &this->P_a_priori;
	this->p_P_a_posteriori = &this->P_a_posteriori;

	this->p_T1 = &this->T1;
	this->p_T2 = &this->T2;

	this->p_x_a_priori = &this->x_a_priori;
	this->p_y = &this->y;

	this->p_t1 = &this->t1;
	this->p_t2 = &this->t2;


	this->p_F = &this->F;
	this->p_B = &this->B;
	this->p_H = &this->H;
	this->p_Q = &this->Q;
	this->p_R = &this->R;

	this->p_x = &this->x;
	this->p_u = &this->u;
	this->p_z = &this->z;
}
void kLKF_2x_2u::invertMatrix(kMatrix &result,kMatrix & matrix)
{
	kMatrix::invert((kMatrix2x2&)result,(kMatrix2x2&)matrix);
}
