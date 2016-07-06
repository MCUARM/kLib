#include "kServo.h"

kServo::kServo(void)
{


}
void kServo::start(float initial_value)
{
	this->run(20000,1000000);
	*this = initial_value;
}
void kServo::operator = (float value)
{
	if(value > 100) value = 100;
	if(value < -100) value = -100;

	value *= 6.5;

	*(this->hardware.output) = ((int)1350) + ((int)value);
}
