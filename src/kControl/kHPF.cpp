/***********************************************************************************
 *                                                                                 *
 *   kLib - C++ development tools for ARM Cortex-M devices                         *
 *                                                                                 *
 *     Copyright (c) 2018, project author Pawel Zalewski                           *
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



#include "kHPF.h"

kHPF::kHPF(void)
{
	this->init(1);
}
kHPF::kHPF(float time_constant)
{
	this->init(time_constant);
}
void kHPF::init(float time_constant)
{
	this->T = time_constant;
	this->inertia.init(this->T);
}
void kHPF::setTimeConstant(float time_constant)
{
	this->T = time_constant;
	this->inertia.setTimeConstant(this->T);
}

float kHPF::feed(float x)
{
	float res = this->T*this->deriv.feed(x);
	res = this->inertia.feed(res);
	return res;
}
float kHPF::feedAngle(kAngle_0_to_2pi & x)
{
	float res = this->T*this->deriv.feedAngle(x);
	kAngle_0_to_2pi temp_res = res;
	return this->inertia.feedAngle(temp_res);
}
float kHPF::feedAngle(kAngle_minus_pi_to_pi & x)
{
	float res = this->T*this->deriv.feedAngle(x);
	kAngle_minus_pi_to_pi temp_res = res;
	return this->inertia.feedAngle(temp_res);
}
