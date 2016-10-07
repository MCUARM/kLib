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

#include "kComplementaryFilter.h"

bool kComplementaryFilter::setSamplingTime(float sampling_time)
{
	this->HPF.setSamplingTime(sampling_time);
	return this->LPF.setSamplingTime(sampling_time);
}
void kComplementaryFilter::setTimeConstant(float time_constant)
{
	this->HPF.setTimeConstant(time_constant);
	this->LPF.setTimeConstant(time_constant);
}
float kComplementaryFilter::feed(float HPF_input,float LPF_input)
{
	float res = this->HPF.feed(HPF_input);
	res += this->LPF.feed(LPF_input);
	return res;
}
float kComplementaryFilter::feedAngle(kAngle_0_to_2pi & HPF_input,kAngle_0_to_2pi LPF_input)
{
	float res = this->HPF.feedAngle(HPF_input);
	res += this->LPF.feedAngle(LPF_input);
	return kAngle::setInBounds_0_to_2pi(res);
}
float kComplementaryFilter::feedAngle(kAngle_minus_pi_to_pi & HPF_input,kAngle_minus_pi_to_pi LPF_input)
{
	float res = this->HPF.feedAngle(HPF_input);
	res += this->LPF.feedAngle(LPF_input);
	return kAngle::setInBounds_minus_pi_to_pi(res);
}
