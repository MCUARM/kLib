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
kVector3 kAHRS::angularRates2EulerDot(void)
{
	float sin_phi,cos_phi,sin_theta,cos_theta,tan_theta;

	sin_phi = sinf(this->phi);
	cos_phi = cosf(this->phi);

	sin_theta = sinf(this->theta);
	cos_theta = cosf(this->theta);
	tan_theta = sin_theta/cos_theta;


	kVector3 res;

	res.x =   (*this->sens_p)
			+ sin_phi*tan_theta*(*this->sens_q)
			+ cos_phi*tan_theta*(*this->sens_r);

	res.y =   cos_phi*(*this->sens_q)
			- sin_phi*(*this->sens_r);

	res.z =   sin_phi/cos_theta*(*this->sens_q)
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

	// psi angle from magnetometer
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

	// theta angle (using accelerometer)
	res.y = asinf(-(*this->sens_x_acc)/acc_magnitude);
	// phi angle (using accelerometer)
	res.x = atan2f((*this->sens_y_acc),(*this->sens_z_acc));

	// psi angle from magnetometer
	kVector3 mag(*this->sens_x_mag,*this->sens_y_mag,*this->sens_z_mag);
	mag.rotateX(this->phi);
	mag.rotateY(this->theta);

	res.z = atan2f(-mag.y,mag.x);

	return res;
}
void kAHRS::calculateAngles(void)
{
	kVector3 EulerC;
	kVector3 EulerDot;

	EulerC = this->getCorrection();
	EulerDot = this->angularRates2EulerDot();

	this->phi += EulerDot.x*this->dt;
	this->theta += EulerDot.y*this->dt;
	this->psi += EulerDot.z*this->dt;

	//correction
	if(this->phi > 1.5708 && EulerC.x < -1.5708)
	{
		this-> phi += (2*3.141593 + EulerC.x - this->phi)*0.005;

	}else if(this->phi < -1.5708 && EulerC.x > 1.5708)
	{
		this-> phi -= (2*3.141593 - EulerC.x + this->phi)*0.005;
	}else
	{
		this-> phi += (EulerC.x - this->phi)*0.01;
	}
	if(this->phi >  3.41593) this->phi -= 2*3.141593;
	if(this->phi < -3.41593) this->phi += 2*3.141593;


	if(this->psi > 1.5708 && EulerC.z < -1.5708)
	{
		this-> psi += (2*3.141593 + EulerC.z - this->psi)*0.005;
	}else if(this->psi < -1.5708 && EulerC.z > 1.5708)
	{
		this-> psi -= (2*3.141593 - EulerC.z + this->psi)*0.005;
	}else
	{
		this-> psi += (EulerC.z - this->psi)*0.005;
	}
	if(this->psi >  3.41593) this->psi -= 2*3.141593;
	if(this->psi < -3.41593) this->psi += 2*3.141593;


	this-> theta += (EulerC.y - this->theta)*0.005;


}
