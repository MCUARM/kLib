#include "kSystem.h"
#include "kPort.h"

void main(void)
{
	PORTA = kPort::on;		//Power on PORTA (by default is off)
	kPin LED = PORTA[2];	//kPin declaration named LED attached to PA2
	LED = kPin::out;		//set LED pin as output (by default input mode selected)

	while(1)
	{
		// program main loop
		
		kSystem.waitms(500);	// wait half a second
		LED.toggle();			// toggle LED state (blink LED)
	}


}
