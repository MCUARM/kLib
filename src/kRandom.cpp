#include "kRandom.h"

k_Random::k_Random(void)
{

}
void k_Random::init(void)
{
	RNG->CR |= (1<<2);
}
unsigned int k_Random::get(void)
{
	while( (RNG->SR & 1) == 0);
	return (unsigned int)RNG->DR;
}
