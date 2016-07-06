#include "kSaturate.h"

kSaturate::kSaturate(void)
{
	this->up_limit = 0;
	this->down_limit = 0;

}
kSaturate::kSaturate(float lower_limit,float upper_limit)
{
	if(lower_limit >= upper_limit)
	{
		this->up_limit = upper_limit;
		this->down_limit = lower_limit;
	}else
	{
		this->up_limit = 0;
		this->down_limit = 0;
	}
}
void kSaturate::set(float lower_limit,float upper_limit)
{
	if(lower_limit >= upper_limit)
	{
		this->up_limit = upper_limit;
		this->down_limit = lower_limit;
	}
}
float kSaturate::feed(float x)
{
	if(x > this->up_limit) x = this->up_limit;
	if(x < this->down_limit) x = this->down_limit;

	return x;
}
