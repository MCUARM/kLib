#include "kWatchdog.h"

k_Watchdog kWatchdog;


k_Watchdog::k_Watchdog(void)
{

}
bool k_Watchdog::init(float counting_period)
{
	float f_presc;
	int prescaler;

	if(counting_period > 32.768) return false;
	if(counting_period < 0.000125) return false;

	f_presc = counting_period / 4096;
	f_presc *= 32000;

	prescaler = (int)f_presc;

	// function not completed
	return false;
}
void k_Watchdog::start(void)
{
	IWDG->KR = 0xCCCC;
}

void k_Watchdog::feed(void)
{
	IWDG->KR = 0xAAAA;
}
