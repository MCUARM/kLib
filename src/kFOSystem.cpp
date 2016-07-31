#include "kFOSystem.h"

kFOSystem::kFOSystem(void)
{
	this->init(1,1,0);
}
kFOSystem::kFOSystem(float sampling_time, float time_constant, float initial_output)
{
	this->T=1;
	this->dt=1;
	this->last_value=0;
	this->init(sampling_time,time_constant,initial_output);
}
void kFOSystem::init(float sampling_time, float time_constant, float initial_output)
{
	if(sampling_time > 0) this->dt = sampling_time;
	if(time_constant >= 0) this->T = time_constant;
	this->last_value = initial_output;

	// use sampling_time as temporary storage
	sampling_time = 1/(this->T+this->dt);

	this->a_coeff = this->dt*sampling_time;
	this->b_coeff = this->T*sampling_time;

}
bool kFOSystem::setSamplingTime(float sampling_time)
{
	if(sampling_time <= 0) return false;
	this->init(sampling_time,this->T);
	return true;
}
void kFOSystem::setTimeConstant(float time_constant)
{
	if(time_constant < 0) return;

	this->T = time_constant;

	float sampling_time;
	// use sampling_time as temporary storage
	sampling_time = 1/(this->T+this->dt);

	this->a_coeff = this->dt*sampling_time;
	this->b_coeff = this->T*sampling_time;
}
float kFOSystem::feed(float x)
{
	float res;

	res = x*this->a_coeff + this->last_value*this->b_coeff;

	this->last_value = res;

	return res;
}
