#include "kMath.h"

const float kMath::_pi=3.14159265358f;
const float kMath::_2pi=2*3.14159265358f;



float kMath::rad2deg(float input)
{
	return (input*RAD_2_DEG_SCALE_FACTOR);
}
float kMath::deg2rad(float input)
{
	return (input*DEG_2_RAD_SCALE_FACTOR);
}
float kMath::abs(float input)
{
	if(input<0) input *= (-1);
	return input;
}
