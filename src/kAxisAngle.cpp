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

#include "kAxisAngle.h"

kAxisAngle::kAxisAngle(void)
{

}
kAxisAngle::kAxisAngle(const kVector3 & axis, float angle)
{
	this->axis.x = axis.x;
	this->axis.y = axis.y;
	this->axis.z = axis.z;
	this->angle = angle;
}
kAxisAngle::kAxisAngle(float x, float y, float z, float angle)
{
	this->axis.x = x;
	this->axis.y = y;
	this->axis.z = z;
	this->angle = angle;
}

kAxisAngle kAxisAngle::create(const kVector3 & axis, float angle)
{
	kAxisAngle res(axis,angle);
	return res;
}
kAxisAngle kAxisAngle::create(float x, float y, float z, float angle)
{
	kAxisAngle res(x,y,z,angle);
	return res;
}
kAxisAngle kAxisAngle::fromAngularRates(const kVector3 & angular_rates, float dt)
{
	float length = angular_rates.length();
	return kAxisAngle::create(angular_rates/length,length*dt);
}


kVector3 kAxisAngle::toEulerAngles(void)
{
	float sin_angle = sinf(this->angle);
	float one_minus_cos_angle = 1-cosf(this->angle);

	float temp1,temp2;


	kVector3 res;

	//phi

	temp1 = sin_angle*this->axis.x + one_minus_cos_angle*this->axis.y*this->axis.z;
	temp2 = 1 - one_minus_cos_angle*(this->axis.x*this->axis.x + this->axis.y*this->axis.y);
	res.x = atan2(temp1,temp2);

	//theta
	temp1 = sin_angle*this->axis.y - one_minus_cos_angle*this->axis.x*this->axis.z;
	res.y = asin(temp1);

	//psi
	temp1 = sin_angle*this->axis.z + one_minus_cos_angle*this->axis.x*this->axis.y;
	temp2 = 1 - one_minus_cos_angle*(this->axis.y*this->axis.y + this->axis.z*this->axis.z);
	res.z = atan2(temp1,temp2);


	return res;

}
