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
	if(this->use_saturation) this->last_value = this->Saturation.feed(this->last_value);

	return this->last_value;
}
void kIntegrator::useSaturation(bool state)
{
	this->use_saturation = state;
}
