#include "kIntegrator.h"

kIntegrator::kIntegrator(void)
{
	this->last_value = 0;
	this->use_saturation = false;
}
float kIntegrator::feed(float x)
{
	this->last_value += this->dt*x;
	if(this->use_saturation) this->last_value = this->Saturation.feed(this->last_value);

	return this->last_value;
}
void kIntegrator::useSaturation(bool state)
{
	this->use_saturation = state;
}
float kIntegrator::feedAngle(kAngle_0_to_2pi & x)
{
	this->feed(x);
	this->last_value = kAngle::setInBounds_0_to_2pi(this->last_value);
	return this->last_value;
}
float kIntegrator::feedAngle(kAngle_minus_pi_to_pi & x)
{
	this->feed(x);
	this->last_value = kAngle::setInBounds_minus_pi_to_pi(this->last_value);
	return this->last_value;
}
