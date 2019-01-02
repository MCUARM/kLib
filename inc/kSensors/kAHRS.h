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

	class kAHRS : public kDiscrete
	{
		private:

			float * sens_p;
			float * sens_q;
			float * sens_r;

			float * sens_x_acc;
			float * sens_y_acc;
			float * sens_z_acc;

			float * sens_x_mag;
			float * sens_y_mag;
			float * sens_z_mag;

			float sin_phi_c;
			float cos_phi_c;
			float sin_theta_c;
			float cos_theta_c;
			float sin_psi_c;
			float cos_psi_c;

			kVector3 EulerC;
			kVector3 EulerG;

			kQuaternion q;
			kQuaternion qc;
			kQuaternion qg;

			kAxisAngle temp_AxisAngle;
		public:

			kVector3 angularRates2EulerDot(void);
			kVector3 getCorrection(void);

			// attitude angles
			float phi;
			float theta;
			float psi;

			//default constructor
			kAHRS(void);

			void attachGyroData(float * p, float * q, float * r);
			void attachGyroData(kVector3 * angular_rates);
			void attachGyroData(kGyroscope * gyro);

			void attachAccData(float * x, float * y, float * z);
			void attachAccData(kVector3 * acceleration);
			void attachAccData(kAccelerometer * acc);

			void attachMagData(float * x, float * y, float * z);
			void attachMagData(kVector3 * magnetic_induction);

			void calculateAngles(void);
			void init(void);


	};

#endif
