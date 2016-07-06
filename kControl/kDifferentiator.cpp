#include "kDifferentiator.h"

kDifferentiator::kDifferentiator(void)
{
	this->first_launch = true;
	this->T = 1;
	this->useLPF=false;
}
void kDifferentiator::setSamplingTime(float time)
{
	if(time > 0) this->T = time;
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
		res = (x - this->last_value)/this->T;
	}
	this->last_value = x;

	if(useLPF) res = LPF.feed(res);

	return res;
}
void kDifferentiator::useLowPassFilter(bool enable)
{
	this->useLPF = enable;
}
