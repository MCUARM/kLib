#include "kSystem.h"
#include "kSerial.h"
#include "kRingBuffer.h"

// receive buffer size definition
#define RX_BUFFER_SIZE ((uint8_t)255)

// memory storage for receive buffer
uint8_t rxBuffer[RX_BUFFER_SIZE];
// receive buffer (ring buffer)
kRingBuffer<uint8_t> rxRing(rxBuffer,RX_BUFFER_SIZE);
// serial port
kSerial com;

// interrupt handler function for UART RxNE event
void comIRQHandler(void)
{
	// read byte from serial port
	uint8_t byte = com.readByte();
	// push data to ring buffer
	rxRing.write(byte);
}


void main(void)
{

	// set IRQ handler function for USART1 interrupt
	kSystem.setIRQHandler(kSystem.IRQ->_USART1,comIRQHandler);
	// set preemption priority, subpriority and enable this interrupt
	kSystem.enableInterrupt(kSystem.IRQ->_USART1,0,0);

	// hardware initialisation of serial port
	// USART1 will be used, RX only mapped on PORTA10
	com.hardware = kSerial::_USART1->RX.PORTA10;
	// allow to trigger interrupt for RX buffer not empty event
	com.enableInterrupt(kSerial::USART_Interrupt->RX_NotEmpty);
	// run serial port with 9600 baud rate
	com.run(kSerial::BaudRate->_9600);

	// go infinite loop
	while(1);

}

