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



#ifndef __kAHRS_H
#define __kAHRS_H

	#include "math.h"
	#include "kMath.h"
	#include "kDiscrete.h"
	#include "kQuaternion.h"
	#include "kAxisAngle.h"

	#include "kGyroscope.h"
	#include "kAccelerometer.h"
	#include "kRTOS.h"
	#include "kLPF.h"

	class kAHRS : public kDiscrete, public kRTOS::Notifier
	{
		private:

			friend void kAHRS_task(void*args);

			kRTOS::task_t taskHandle=0;
			kRTOS::Semaphore inputDataSemaphore;

			uint8_t isStartingUp;


			kVector3 * gyro;
			kVector3 * acc;
			kVector3 * mag;

			// attitude angles
			kVector3 EulerC;
			kVector3 EulerEst;

			kLPF correctionWeight;

			kQuaternion q;
			kQuaternion qc;

			kVector3 calculateCorrectionAngles(void);
			void calculateAngles(void);
			void init(void);

		public:

			void run(const char * task_name,unsigned long priority);

			float phi();
			float theta();
			float psi();


			void setGyroData(kVector3 * angular_rates);
			void setAccData(kVector3 * acceleration);
			void setMagData(kVector3 * magnetic_induction);

			void notifyNewInputData(void);




	};

#endif
