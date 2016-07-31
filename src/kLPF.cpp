#include "kLPF.h"

kLPF::kLPF(void)
{
	kFOSystem::init(1,1,0);
}
float kLPF::feedAngle(kAngle_0_to_2pi & x)
{
	kAngle_0_to_2pi current_angle = this->last_value;
	float desired_value = this->last_value + kAngle::getAngleError(x,current_angle);
	this->feed(desired_value);
	this->last_value = kAngle::setInBounds_0_to_2pi(this->last_value);
	return this->last_value;
}
float kLPF::feedAngle(kAngle_minus_pi_to_pi & x)
{
	kAngle_minus_pi_to_pi current_angle = this->last_value;
	float desired_value = this->last_value + kAngle::getAngleError(x,current_angle);
	this->feed(desired_value);
	this->last_value = kAngle::setInBounds_minus_pi_to_pi(this->last_value);
	return this->last_value;
}
