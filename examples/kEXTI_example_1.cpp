#include "kSystem.h"
#include "kEXTI.h"



//interrupt counter
uint8_t eventCounter=0;


// EXTI handler function
void extiHandler(void)
{
	// increment event counter
	eventCounter++;
}


void main(void)
{
	kEXTI exti;

	// setup hardware -> EXTI0 will be used
	// triggered on rising edge on PORTB0
	exti.hardware = kEXTI::_EXTI0->RisingEdge.PORTB0;
	// set IRQ handler function and interrupt preemption priority and subpriority
	exti.setIRQHandler(extiHandler,0,0);


	while(1)
	{
		// wait one second
		kSystem.wait(1);
		// force interrupt (simulating external interrupt)
		exti.forceInterrupt();
	}

}

