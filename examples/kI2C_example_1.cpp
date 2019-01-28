#include "kSystem.h"
#include "kI2C.h"



void main(void)
{
	kI2C i2c;

	i2c.hardware = kI2C::_I2C1->SCL.PORTB6;	// setup SCL pin -> I2C1 on PORTB6
	i2c.hardware = kI2C::_I2C1->SDA.PORTB7; // setup SDA pin -> I2C1 on PORTB7
	i2c.address = 0xD8;	// set receiver I2C address
	i2c.run(kI2C::I2C_Speed->_100kHz);	// set I2C speed

	// If you want to use internal pull-ups
	// you must to do this explicitly by calling kPort API
	PORTB[6] = kPin::PullUp;
	PORTB[7] = kPin::PullUp;


	while(1)
	{
		// wait 1 second
		kSystem.wait(1);
		// transmit message through I2C
		// this function works in synchronous mode
		i2c.write("Hello from I2C!");
	}

}

