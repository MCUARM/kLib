#include "kSystem.h"
#include "kSerial.h"




void main(void)
{
	kSerial com;

	// setup hardware USART1 will be used
	// transmitter on PORTA9
	com.hardware = kSerial::_USART1->TX.PORTA9;
	// run USART with 9600 baud rate
	com.run(kSerial::BaudRate->_9600);

	while(1)
	{
		// wait 1 second
		kSystem.wait(1);
		// transmit message in synchronous mode
		com.write("Hello from UART!\r\n");
	}

}

