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


void kAHRS_task(void*args)
{
	kAHRS * AHRS = static_cast<kAHRS*>(args);
	AHRS->isStartingUp = 2;


	while(1)
	{
		// wait for new data coming from IMU
		if(AHRS->inputDataSemaphore.take(portMAX_DELAY))
		{
			// new data from IMU is available

			// check if this is filter start up
			if(AHRS->isStartingUp)
			{
				// yes
				if(AHRS->isStartingUp == 2)
				{
					//this is first step data are passed from IMU
					//run correction weight LPF dt calculation
					AHRS->correctionWeight.run();
				}
				if(AHRS->isStartingUp == 1)
				{
					// AHRS should be initialised with these data
					AHRS->init();
					// run AHRS dt calculation
					AHRS->kDiscrete::run();
					// setup correctionWeight LPF with time constant and initial value
					// these settings must be set when proper dt value is maintained
					AHRS->correctionWeight.init(5,1.0);
				}
				// decrement starting up counter
				AHRS->isStartingUp--;
			}else
			{
				// filter stage

				// process new data
				AHRS->calculateAngles();

				// notify new data
				AHRS->notifyAllReceivers();
			}


		}

	}

}



void kAHRS::run(const char * task_name,unsigned long priority)
{
	// prohibit calling this function more than one time
	if(taskHandle) return;

	// create input data semaphore
	if(!inputDataSemaphore.createBinary()) return;
	inputDataSemaphore.take(portMAX_DELAY);


	// create AHRS task
	kRTOS::taskCreate(kAHRS_task,task_name,1024,this,priority,&taskHandle);
}

void kAHRS::notifyNewInputData(void)
{
	inputDataSemaphore.give();
}

void kAHRS::setGyroData(kVector3 * angular_rates)
{
	gyro = angular_rates;
}

void kAHRS::setAccData(kVector3 * acceleration)
{
	acc = acceleration;
}

void kAHRS::setMagData(kVector3 * magnetic_induction)
{
	mag = magnetic_induction;
}

void kAHRS::init(void)
{
	// calculate magnitude of acceleration
	float acc_magnitude = acc->length();

	// initial phi angle (using accelerometer)
	EulerEst.x = atan2f(acc->y,acc->z);

	// initial theta angle (using accelerometer)
	EulerEst.y = asinf(-acc->x/acc_magnitude);

	// initial psi angle from magnetometer
	kVector3 rotated_mag = *mag;
	rotated_mag.rotateX(EulerEst.x);
	rotated_mag.rotateY(EulerEst.y);

	EulerEst.z = atan2f(-rotated_mag.y,rotated_mag.x);

	// run dt calculation
	kDiscrete::run();
	correctionWeight.run();

}
kVector3 kAHRS::calculateCorrectionAngles(void)
{
	kVector3 res;


	// calculate magnitude of acceleration
	float acc_magnitude = acc->length();

	// initial phi angle (using accelerometer)
	res.x = atan2f(acc->y,acc->z);

	// initial theta angle (using accelerometer)
	res.y = asinf(-acc->x/acc_magnitude);

	// initial psi angle from magnetometer
	kVector3 rotated_mag = *mag;
	rotated_mag.rotateX(EulerEst.x);
	rotated_mag.rotateY(EulerEst.y);

	res.z = atan2f(-rotated_mag.y,rotated_mag.x);

	return res;
}
void kAHRS::calculateAngles(void)
{
	// process
	q *= kQuaternion::fromAngularRates(*gyro,dt());

	// correction
	EulerC = calculateCorrectionAngles();
	qc = kQuaternion::fromEulerAngles(EulerC);
	q = kQuaternion::slerp(q,qc,correctionWeight.feed(0.01));

	//quaternion normalisation
	q = q.versor();

	// outputting angles
	EulerEst = q.toEulerAngles();

}

float kAHRS::phi()
{
	return EulerEst.x;
}
float kAHRS::theta()
{
	return EulerEst.y;
}
float kAHRS::psi()
{
	return EulerEst.z;
}
