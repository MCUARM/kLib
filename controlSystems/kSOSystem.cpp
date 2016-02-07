#include "kSOSystem.h"

kSOSystem::kSOSystem(void)
{
	this->Ti=1;
	this->first_last_value = 0;
	this->second_last_value = 0;
	this->a_coeff = 1;
	this->b_coeff = 1;
	this->c_coeff = 1;
}
kSOSystem::kSOSystem(float sampling_time, float damping_ratio, float resonance_freq_in_radians, float initial_output)
{
	this->Ti=1;
	this->first_last_value = 0;
	this->second_last_value = 0;
	this->a_coeff = 1;
	this->b_coeff = 1;
	this->c_coeff = 1;

	this->init(sampling_time,damping_ratio,resonance_freq_in_radians,initial_output);
}
void kSOSystem::init(float sampling_time, float damping_ratio, float resonance_freq_in_radians, float initial_output)
{
	this->first_last_value = initial_output;
	this->second_last_value = initial_output;

	if(sampling_time > 0) this->Ti = sampling_time;

	this->a_coeff = this->Ti*this->Ti;
	this->b_coeff = 2*damping_ratio*resonance_freq_in_radians*this->Ti;
	this->c_coeff = 1/(1+this->b_coeff + this->a_coeff*resonance_freq_in_radians*resonance_freq_in_radians);
	this->a_coeff = this->a_coeff*this->c_coeff;
	this->b_coeff = (2+this->b_coeff)*this->c_coeff;
	this->c_coeff *= (-1);
}
float kSOSystem::feed(float x)
{
	float res;
	res = x*this->a_coeff + this->first_last_value*this->b_coeff + this->second_last_value*this->c_coeff;

	this->second_last_value = this->first_last_value;
	this->first_last_value = res;

	return res;
}
