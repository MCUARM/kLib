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



#include "kSOSystem.h"

kSOSystem::kSOSystem(void)
{
	this->first_last_value = 0;
	this->second_last_value = 0;
	this->a_coeff = 1;
	this->b_coeff = 1;
	this->c_coeff = 1;
}
kSOSystem::kSOSystem(float sampling_time, float damping_ratio, float resonance_freq_in_radians, float initial_output)
{
	this->first_last_value = 0;
	this->second_last_value = 0;
	this->a_coeff = 1;
	this->b_coeff = 1;
	this->c_coeff = 1;

	this->init(sampling_time,damping_ratio,resonance_freq_in_radians,initial_output);
}
void kSOSystem::init(float sampling_time, float damping_ratio, float resonance_freq_in_radians, float initial_output)
{
	this->first_last_value = initial_output;
	this->second_last_value = initial_output;

	if(sampling_time > 0) this->dt = sampling_time;

	this->a_coeff = this->dt*this->dt;
	this->b_coeff = 2*damping_ratio*resonance_freq_in_radians*this->dt;
	this->c_coeff = 1/(1+this->b_coeff + this->a_coeff*resonance_freq_in_radians*resonance_freq_in_radians);
	this->a_coeff = this->a_coeff*this->c_coeff;
	this->b_coeff = (2+this->b_coeff)*this->c_coeff;
	this->c_coeff *= (-1);
}
float kSOSystem::feed(float x)
{
	float res;
	res = x*this->a_coeff + this->first_last_value*this->b_coeff + this->second_last_value*this->c_coeff;

	this->second_last_value = this->first_last_value;
	this->first_last_value = res;

	return res;
}
