#include "kDifferentiator.h"

kDifferentiator::kDifferentiator(void)
{
	this->first_launch = true;
	this->useLPF=false;
}
float kDifferentiator::feed(float x)
{
	float res;

	if(this->first_launch)
	{
		res = 0;
		this->first_launch = false;
	}else
	{
		res = (x - this->last_value)/this->dt;
	}
	this->last_value = x;

	if(this->useLPF) res = LPF.feed(res);

	return res;
}
float kDifferentiator::feedAngle(kAngle_0_to_2pi & x)
{
	float res;
	kAngle_0_to_2pi current_value = this->last_value;
	res = kAngle::getAngleError(x,current_value);
	this->last_value = x;
	return res;
}
float kDifferentiator::feedAngle(kAngle_minus_pi_to_pi & x)
{
	float res;
	kAngle_minus_pi_to_pi current_value = this->last_value;
	res = kAngle::getAngleError(x,current_value);
	this->last_value = x;
	return res;
}
void kDifferentiator::useLowPassFilter(bool enable)
{
	this->useLPF = enable;
}
