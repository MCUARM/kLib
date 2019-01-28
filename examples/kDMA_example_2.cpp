#include "kSystem.h"
#include "kSerial.h"
#include "kDMA.h"



void main(void)
{
	kSerial com;
	kDMA dma;


	// setup hardware USART1 will be used
	// transmitter on PORTA9
	com.hardware = kSerial::_USART1->TX.PORTA9;
	// enable DMA usage for transmission
	com.useDMA(kSerial::DMA_mode->Transmission);
	// run USART with 9600 baud rate
	com.run(kSerial::BaudRate->_9600);

	// setup hardware for DMA - use DMA2 stream 7
	// Memory to peripheral mode, channel USART1_TX
	// Data item is 8bit long, auto-increment memory address
	// for each data item, circular buffer off, transfer priority medium
	dma.hardware = kDMA::_DMA2->Stream7.M2P._USART1_TX.Data8bit.MemAddrIncr.CircOff.PriorityMedium;
	// set peripheral address to USART data register
	dma.setPeripheralAddress(com);

	while(1)
	{
		// wait 1 second
		kSystem.wait(1);
		// transmit message in through dma to com port
		// this function works in asynchronous mode
		dma.write("Hello from DMA!\r\n",17);
	}

}

