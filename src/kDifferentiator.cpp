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



#include "kDifferentiator.h"

kDifferentiator::kDifferentiator(void)
{
	this->first_launch = true;
	this->useLPF=false;
}
float kDifferentiator::feed(float x)
{
	float res=last_value;

	if(first_launch)
	{
		res = 0;
		first_launch = false;
		kDiscrete::init();
	}else
	{
		float t = dt();
		if(t != 0) res = (x - last_value)/t;
	}

	last_value = x;

	if(useLPF) res = LPF.feed(res);

	return res;
}
float kDifferentiator::feedAngle(kAngle_0_to_2pi & x)
{
	float res;
	kAngle_0_to_2pi current_value = this->last_value;
	res = kAngle::getAngleError(x,current_value);
	this->last_value = x;
	return res;
}
float kDifferentiator::feedAngle(kAngle_minus_pi_to_pi & x)
{
	float res;
	kAngle_minus_pi_to_pi current_value = this->last_value;
	res = kAngle::getAngleError(x,current_value);
	this->last_value = x;
	return res;
}
void kDifferentiator::useLowPassFilter(bool enable)
{
	useLPF = enable;
}
