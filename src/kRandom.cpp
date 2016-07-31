#include "kRandom.h"


void kRandom::init(void)
{
	RNG->CR |= (1<<2);
}
unsigned int kRandom::get(void)
{
	while( (RNG->SR & 1) == 0);
	return (unsigned int)RNG->DR;
}
