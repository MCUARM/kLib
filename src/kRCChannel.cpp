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



#include "kRCChannel.h"


kRCChannel::kRCChannel(void)
{
	this->scale = 0;
}
bool kRCChannel::isGood(void)
{
	// get last time PWM was updated - it cannot be longer than 20 ms + margin 2 ms
	uint32_t temp_time = this->hardware.EXTI_data->last_update_kSystem_timer_value;
	if(temp_time > 22) return false;
	if(temp_time < 18) return false;

	// PWM window checking - down margin 500us, up margin 2500us
	if( (this->hardware.EXTI_data->pwm_input_register <  500) ||
		(this->hardware.EXTI_data->pwm_input_register > 2500)) return false;

	// signal is in good condition
	return true;
}
bool kRCChannel::setRange(float min_normalized,float max_normalized,uint16_t min_pwm_width_us,uint16_t max_pwm_width_us)
{
	// pwm input parameters

	// assert relations between max and min
	if(max_pwm_width_us <= min_pwm_width_us) return false;

	// set max and min
	this->iMin = min_pwm_width_us;
	this->iMax = max_pwm_width_us;

	// calculate mid value
	this->iMid = (this->iMax +this->iMin) >> 1;


	// normalized parameters

	// assert relations between max and min
	if(max_normalized <= min_normalized) return false;

	// set max and min
	this->fMax = max_normalized;
	this->fMin = min_normalized;

	// calculate mid value
	this->fMid = (this->fMax + this->fMin)*0.5;

	// calculate scale factor
	this->scale =  (this->fMax-this->fMin)/( ((float)this->iMax)-((float)this->iMin) );

	return true;
}
kRCChannel::operator float()
{
	float res = (float)((int16_t)this->hardware.EXTI_data->pwm_input_register-this->iMid);
	res *= this->scale;
	res += this->fMid;
	return res;
}
