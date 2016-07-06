#include "kAngleError.h"

kAngleError::kAngleError(void)
{
	this->min_value = 0;
	this->max_value = 0;

	this->ref_sig = &this->min_value;
	this->sig = &this->min_value;

	this->last_chosen_path_1 = true;
	this->hist = 0;
}
void kAngleError::attachData(float * reference_signal,float * signal)
{
	this->ref_sig = reference_signal;
	this->sig = signal;
}
void kAngleError::setHisteresis(float range)
{
	if(range >=0) this->hist = range;
}
float kAngleError::get(void)
{
	float out;
	float abs_path_1,abs_path_2;

	this->path_1 = (*this->ref_sig) - (*this->sig);

	if( (*this->ref_sig) > (*this->sig) )
	{
		this->path_2 = (*this->ref_sig)-this->max_value;
		this->path_2 += this->min_value-(*this->sig);
	}else
	{
		this->path_2 =  this->max_value - (*this->sig);
		this->path_2 += (*this->ref_sig)-this->min_value;
	}

	abs_path_1 = this->path_1;
	if(abs_path_1 < 0) abs_path_1 *= (-1);

	abs_path_2 = this->path_2;
	if(abs_path_2 < 0) abs_path_2 *= (-1);


	if(this->last_chosen_path_1)
	{
		abs_path_1 -= this->hist;
	}else
	{
		abs_path_1 += this->hist;
	}

	if(abs_path_1 < abs_path_2)
	{
		out = this->path_1;
		this->last_chosen_path_1 = true;
	}else
	{
		out = this->path_2;
		this->last_chosen_path_1 = false;
	}


	return out;
}
