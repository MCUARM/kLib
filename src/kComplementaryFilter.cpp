#include "kComplementaryFilter.h"

bool kComplementaryFilter::setSamplingTime(float sampling_time)
{
	this->HPF.setSamplingTime(sampling_time);
	return this->LPF.setSamplingTime(sampling_time);
}
void kComplementaryFilter::setTimeConstant(float time_constant)
{
	this->HPF.setTimeConstant(time_constant);
	this->LPF.setTimeConstant(time_constant);
}
float kComplementaryFilter::feed(float HPF_input,float LPF_input)
{
	float res = this->HPF.feed(HPF_input);
	res += this->LPF.feed(LPF_input);
	return res;
}
float kComplementaryFilter::feedAngle(kAngle_0_to_2pi & HPF_input,kAngle_0_to_2pi LPF_input)
{
	float res = this->HPF.feedAngle(HPF_input);
	res += this->LPF.feedAngle(LPF_input);
	return kAngle::setInBounds_0_to_2pi(res);
}
float kComplementaryFilter::feedAngle(kAngle_minus_pi_to_pi & HPF_input,kAngle_minus_pi_to_pi LPF_input)
{
	float res = this->HPF.feedAngle(HPF_input);
	res += this->LPF.feedAngle(LPF_input);
	return kAngle::setInBounds_minus_pi_to_pi(res);
}
