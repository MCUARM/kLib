
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
