#include "kPID.h"

kPID::kPID(void)
{
	this->Kp = 0;
	this->Kd = 0;
	this->Ki = 0;

	this->use_output_saturation=false;

}
void kPID::setSamplingTime(float time)
{
	this->Integral.setSamplingTime(time);
	this->Derivative.setSamplingTime(time);
}

float kPID::feed(float x)
{
	float res;

	float deriv = this->Derivative.feed(x);
	float integral = this->Integral.feed(this->Ki*x);


	// calculate response
	res = 	this->Kp*x;
	res += 	this->Kd*deriv;
	res += 	integral;

	// check saturation
	if(this->use_output_saturation) res = this->OutputSaturation.feed(res);


	return res;

}

void kPID::useOutputSaturation(bool state)
{
	this->use_output_saturation = state;
}
