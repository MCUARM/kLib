#include "kHPF.h"

kHPF::kHPF(void)
{
	this->init(1,1);
}
kHPF::kHPF(float sampling_time, float time_constant)
{
	this->init(sampling_time,time_constant);
}
void kHPF::init(float sampling_time, float time_constant)
{
	this->T = time_constant;
	this->deriv.setSamplingTime(sampling_time);
	this->inertia.init(sampling_time,this->T);
}
void kHPF::setTimeConstant(float time_constant)
{
	this->T = time_constant;
	this->inertia.setTimeConstant(this->T);
}
bool kHPF::setSamplingTime(float sampling_time)
{
	this->inertia.setSamplingTime(sampling_time);
	return this->deriv.setSamplingTime(sampling_time);
}
float kHPF::feed(float x)
{
	float res = this->T*this->deriv.feed(x);
	res = this->inertia.feed(res);
	return res;
}
float kHPF::feedAngle(kAngle_0_to_2pi & x)
{
	float res = this->T*this->deriv.feedAngle(x);
	kAngle_0_to_2pi temp_res = res;
	return this->inertia.feedAngle(temp_res);
}
float kHPF::feedAngle(kAngle_minus_pi_to_pi & x)
{
	float res = this->T*this->deriv.feedAngle(x);
	kAngle_minus_pi_to_pi temp_res = res;
	return this->inertia.feedAngle(temp_res);
}
