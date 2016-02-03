#include "kIntegrator.h"

kIntegrator::kIntegrator(void)
{
	this->T = 1;
	this->last_value = 0;
	this->use_saturation = false;
}

void kIntegrator::setSamplingTime(float time)
{
	if(time > 0 ) this->T = time;
}
float kIntegrator::feed(float x)
{
	this->last_value += this->T*x;

	if(this->use_saturation)
	{
		if(this->up_limit < this->last_value)
		{
			this->last_value = this->up_limit;
		}
		else if(this->dw_limit > this->last_value)
		{
			this->last_value = this->dw_limit;
		}
	}

	return this->last_value;
}
void kIntegrator::useSaturation(bool state)
{
	this->use_saturation = state;
}

void kIntegrator::setSaturation(float lower_limit,float upper_limit)
{
	this->up_limit = upper_limit;
	this->dw_limit = lower_limit;
	this->use_saturation = true;
}
