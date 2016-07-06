#include "kLPF.h"

kLPF::kLPF(void)
{
	kFOSystem::init(1,1,0);
}
kLPF::kLPF(float sampling_time, float time_constant, float initial_output) : kFOSystem(sampling_time,time_constant,initial_output)
{

}
