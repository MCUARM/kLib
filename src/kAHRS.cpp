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



#include "kAHRS.h"

float default_sens_input;

kAHRS::kAHRS(void)
{
	this->attachAccData(&default_sens_input,&default_sens_input,&default_sens_input);
	this->attachGyroData(&default_sens_input,&default_sens_input,&default_sens_input);
	this->attachMagData(&default_sens_input,&default_sens_input,&default_sens_input);

	this->phi = 0;
	this->theta = 0;
	this->psi = 0;
}


void kAHRS::attachGyroData(float * p, float * q, float * r)
{
	this->sens_p = p;
	this->sens_q = q;
	this->sens_r = r;
}
void kAHRS::attachAccData(float * x, float * y, float * z)
{
	this->sens_x_acc = x;
	this->sens_y_acc = y;
	this->sens_z_acc = z;
}
void kAHRS::attachMagData(float * x, float * y, float * z)
{
	this->sens_x_mag = x;
	this->sens_y_mag = y;
	this->sens_z_mag = z;
}
void kAHRS::attachGyroData(kVector3 * angular_rates)
{
	this->attachGyroData(&angular_rates->x,&angular_rates->y,&angular_rates->z);
}

void kAHRS::attachAccData(kVector3 * acceleration)
{
	this->attachAccData(&acceleration->x,&acceleration->y,&acceleration->z);
}

void kAHRS::attachMagData(kVector3 * magnetic_induction)
{
	this->attachMagData(&magnetic_induction->x,&magnetic_induction->y,&magnetic_induction->z);
}
void kAHRS::attachGyroData(kGyroscope * gyro)
{
	this->attachGyroData(&gyro->gyro.x,&gyro->gyro.y,&gyro->gyro.z);
}
void kAHRS::attachAccData(kAccelerometer * acc)
{
	this->attachAccData(&acc->acc.x,&acc->acc.y,&acc->acc.z);
}

kVector3 kAHRS::angularRates2EulerDot(void)
{
	float sin_phi,cos_phi,sin_theta,cos_theta,tan_theta;

	sin_phi = sinf(this->phi);
	cos_phi = cosf(this->phi);

	sin_theta = sinf(this->theta);
	cos_theta = cosf(this->theta);
	tan_theta = sin_theta/cos_theta;


	kVector3 res;

	res.x = + (*this->sens_p)
			+ sin_phi*tan_theta*(*this->sens_q)
			+ cos_phi*tan_theta*(*this->sens_r);

	res.y = + cos_phi*(*this->sens_q)
			- sin_phi*(*this->sens_r);

	res.z = + sin_phi/cos_theta*(*this->sens_q)
			+ cos_phi/cos_theta*(*this->sens_r);

	return res;
}
void kAHRS::init(void)
{
	// calculate magnitude of acceleration
	float acc_magnitude = sqrtf( (*this->sens_x_acc)*(*this->sens_x_acc)+
								(*this->sens_y_acc)*(*this->sens_y_acc)+
								(*this->sens_z_acc)*(*this->sens_z_acc));

	// initial theta angle (using accelerometer)
	this->theta = asinf(-(*this->sens_x_acc)/acc_magnitude);
	// initial phi angle (using accelerometer)
	this->phi = atan2f((*this->sens_y_acc),(*this->sens_z_acc));

	// initial psi angle from magnetometer
	kVector3 mag(*this->sens_x_mag,*this->sens_y_mag,*this->sens_z_mag);
	mag.rotateX(this->phi);
	mag.rotateY(this->theta);

	this->psi = atan2f(-mag.y,mag.x);
}
kVector3 kAHRS::getCorrection(void)
{
	kVector3 res;
	// calculate magnitude of acceleration
	float acc_magnitude = sqrtf( (*this->sens_x_acc)*(*this->sens_x_acc)+
								(*this->sens_y_acc)*(*this->sens_y_acc)+
								(*this->sens_z_acc)*(*this->sens_z_acc));

	// phi angle (using accelerometer)
	res.x = atan2f((*this->sens_y_acc),(*this->sens_z_acc));

	// theta angle (using accelerometer)
	res.y = asinf(-(*this->sens_x_acc)/acc_magnitude);

	// psi angle from magnetometer
	kVector3 mag(*this->sens_x_mag,*this->sens_y_mag,*this->sens_z_mag);
	mag.rotateX(this->phi);
	mag.rotateY(this->theta);
	res.z = atan2f(-mag.y,mag.x);

	return res;
}
void kAHRS::calculateAngles(void)
{
	kVector3 gyro(*this->sens_p,*this->sens_q,*this->sens_r);

	this->temp_AxisAngle = kAxisAngle::create(gyro,gyro.length()*dt());
	this->qg = kQuaternion::fromAxisAngle(this->temp_AxisAngle);

	this->q *= this->qg;


	this->EulerC = this->getCorrection();
	qc = kQuaternion::fromEulerAngles(this->EulerC);

	this->q = kQuaternion::slerp(this->q,this->qc,0.01);

	//quaternion *= quaternion_error;
	this->q = this->q.versor();

	this->EulerG = this->q.toEulerAngles();

	this->phi   = this->EulerG.x;
	this->theta = this->EulerG.y;
	this->psi   = this->EulerG.z;

}
