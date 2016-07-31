#include "kServo.h"

kServo::kServo(void)
{

}
bool kServo::setRange(float min_normalized,float max_normalized,uint16_t min_pwm_width_us,uint16_t max_pwm_width_us)
{
	// pwm output parameters

	// assert relations between max and min
	if(max_pwm_width_us <= min_pwm_width_us) return false;
	// assert maximum allowed pwm width in us
	if(max_pwm_width_us > 3000) return false;

	// set max and min
	this->iMin = min_pwm_width_us;
	this->iMax = max_pwm_width_us;

	// calculate mid value
	this->iMid = (this->iMax +this->iMin) >> 1;


	// normalized parameters

	// assert relations between max and min
	if(max_normalized <= min_normalized) return false;

	// set max and min
	this->fMax = max_normalized;
	this->fMin = min_normalized;

	// calculate mid value
	this->fMid = (this->fMax + this->fMin)*0.5;

	// calculate scale factor
	this->scale = ( ((float)this->iMax)-((float)this->iMin) )/(this->fMax-this->fMin);

	return true;
}


void kServo::operator = (float value)
{
	value -= this->fMid;
	value *= this->scale;

	uint16_t res = (uint16_t)(((int16_t)value)+this->iMid);
	kPWM::operator = (res);
}
