
#ifndef __kAHRS_H
#define __kAHRS_H

	#include "math.h"
	#include "kVector.h"

	class kAHRS
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

			float phi_c;
			float theta_c;
			float psi_c;

			kVector3 angularRates2EulerDot(void);
			kVector3 getCorrection(void);

		public:

			// attitude angles
			float phi;
			float theta;
			float psi;

			float dt;

			//default constructor
			kAHRS(void);

			void attachGyroData(float * p, float * q, float * r);
			void attachAccData(float * x, float * y, float * z);
			void attachMagData(float * x, float * y, float * z);
			void calculateAngles(void);
			void init(void);


	};

#endif
