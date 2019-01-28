#include "kSystem.h"
#include "kDMA.h"


// rx buffer for receiving DMA message
uint8_t rx_buffer[255];


void main(void)
{
	kDMA dma;

	// hardware setup: use DMA2 stream 2. Memory to memory mode,
	// One data item equals 8 bits, medium priority of the transfer
	dma.hardware = kDMA::_DMA2->Stream0.M2M.Data8bit.PriorityMedium;

	// write Message to rx buffer (third argument is number of data items
	// to transfer (this function works in asynchronious mode)
	dma.write("Hello from DMA!",rx_buffer,14);


	while(1);

}

