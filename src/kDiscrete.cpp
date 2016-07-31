#include "kDiscrete.h"

kDiscrete::kDiscrete(void)
{
	this->dt=1;
}
bool kDiscrete::setSamplingTime(float sampling_time)
{
	if(sampling_time <= 0) return false;
	this->dt = sampling_time;
	return true;
}
