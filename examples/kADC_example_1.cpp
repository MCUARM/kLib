#include "kSystem.h"
#include "kADC.h"



void main(void)
{

	kADC sens;

	// configure ADC channel ADC1 will be used mapped on PORTA0
	// Please note that for analog configuration internal Schmidt
	// trigger is disabled which disables the pin to be 5V tolerant
	sens.hardware = kADC::_ADC1->PORTA0;
	// Run ADC with APB2 clock divided by 2
	// Note that all ADC shares common clock source so that this
	// function can be called only once to start all ADCx
	sens.run(kADC::Clock->APB2_div_2);

	// storage for single measurement
	uint16_t result;

	while(1)
	{
		// perform conversion in synchronous mode
		result = sens.read();
		// delay 10 ms
		kSystem.waitms(10);
	}

}

