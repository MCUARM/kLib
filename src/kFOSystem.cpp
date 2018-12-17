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



#include "kFOSystem.h"

kFOSystem::kFOSystem(void)
{
	this->init(1,1,0);
}
kFOSystem::kFOSystem(float sampling_time, float time_constant, float initial_output)
{
	this->T=1;
	this->dt=1;
	this->last_value=0;
	this->init(sampling_time,time_constant,initial_output);
}
void kFOSystem::init(float sampling_time, float time_constant, float initial_output)
{
	if(sampling_time > 0) this->dt = sampling_time;
	if(time_constant >= 0) this->T = time_constant;
	this->last_value = initial_output;

	// use sampling_time as temporary storage
	sampling_time = 1/(this->T+this->dt);

	this->a_coeff = this->dt*sampling_time;
	this->b_coeff = this->T*sampling_time;

}
bool kFOSystem::setSamplingTime(float sampling_time)
{
	if(sampling_time <= 0) return false;
	this->init(sampling_time,this->T);
	return true;
}
void kFOSystem::setTimeConstant(float time_constant)
{
	if(time_constant < 0) return;

	this->T = time_constant;

	float sampling_time;
	// use sampling_time as temporary storage
	sampling_time = 1/(this->T+this->dt);

	this->a_coeff = this->dt*sampling_time;
	this->b_coeff = this->T*sampling_time;
}
float kFOSystem::feed(float x)
{
	float res;

	res = x*this->a_coeff + this->last_value*this->b_coeff;

	this->last_value = res;

	return res;
}
