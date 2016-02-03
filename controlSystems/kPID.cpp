#include "kPID.h"

kPID::kPID(void)
{
	this->use_integral_saturation = false;
	this->use_output_saturation = false;

	this->Kp = 0;
	this->Kd = 0;
	this->Ki = 0;
	this->T = 1;
	this->last_x = 0;
	this->last_integral = 0;
}

void kPID::setSamplingTime(float time)
{
	if(time > 0) this->T = time;
}

float kPID::feed(float x)
{
	float res;

	float deriv = (x - this->last_x)/this->T;

	// calculate response
	res = 	this->Kp*x;
	res += 	this->Kd*deriv;
	res += 	this->Ki*this->last_integral;

	// check saturation
	if(this->use_output_saturation)
	{
		if(this->output_upper_limit < res)
		{
			res = this->output_upper_limit;
		}
		else if(this->output_lower_limit > res)
		{
			res = this->output_lower_limit;
		}
	}


	// update integral value
	this->last_integral += x*this->T;

	if(this->use_integral_saturation)
	{
		if(this->integral_upper_limit < this->last_integral)
		{
			this->last_integral = this->integral_upper_limit;
			return res;
		}else if(this->integral_lower_limit > this->last_integral)
		{
			this->last_integral = this->integral_lower_limit;
			return res;
		}
	}

	return res;

}
void kPID::useIntegralSaturation(bool state)
{
	this->use_integral_saturation = state;
}
void kPID::setIntegralSaturation(float lower_limit,float upper_limit)
{
	this->integral_lower_limit = lower_limit;
	this->integral_upper_limit = upper_limit;

	this->use_integral_saturation = true;
}

void kPID::useOutputSaturation(bool state)
{
	this->use_integral_saturation = state;
}
void kPID::setOutputSaturation(float lower_limit,float upper_limit)
{
	this->output_lower_limit = lower_limit;
	this->output_upper_limit = upper_limit;

	this->use_output_saturation = true;
}

