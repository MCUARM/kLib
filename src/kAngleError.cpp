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



#include "kAngleError.h"

kAngleError::kAngleError(void)
{
	this->min_value = 0;
	this->max_value = 0;

	this->ref_sig = &this->min_value;
	this->sig = &this->min_value;

	this->last_chosen_path_1 = true;
	this->hist = 0;
}
void kAngleError::attachData(float * reference_signal,float * signal)
{
	this->ref_sig = reference_signal;
	this->sig = signal;
}
void kAngleError::setHisteresis(float range)
{
	if(range >=0) this->hist = range;
}
float kAngleError::get(void)
{
	float out;
	float abs_path_1,abs_path_2;

	this->path_1 = (*this->ref_sig) - (*this->sig);

	if( (*this->ref_sig) > (*this->sig) )
	{
		this->path_2 = (*this->ref_sig)-this->max_value;
		this->path_2 += this->min_value-(*this->sig);
	}else
	{
		this->path_2 =  this->max_value - (*this->sig);
		this->path_2 += (*this->ref_sig)-this->min_value;
	}

	abs_path_1 = this->path_1;
	if(abs_path_1 < 0) abs_path_1 *= (-1);

	abs_path_2 = this->path_2;
	if(abs_path_2 < 0) abs_path_2 *= (-1);


	if(this->last_chosen_path_1)
	{
		abs_path_1 -= this->hist;
	}else
	{
		abs_path_1 += this->hist;
	}

	if(abs_path_1 < abs_path_2)
	{
		out = this->path_1;
		this->last_chosen_path_1 = true;
	}else
	{
		out = this->path_2;
		this->last_chosen_path_1 = false;
	}


	return out;
}
