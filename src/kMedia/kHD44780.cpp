/***********************************************************************************
 *                                                                                 *
 *   kLib - C++ development tools for ARM Cortex-M devices                         *
 *                                                                                 *
 *     Copyright (c) 2018, project author Pawel Zalewski                           *
 *     All rights reserved.                                                        *
 *                                                                                 *
 ***********************************************************************************
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions  in  binary  form  must  reproduce the above copyright
 *      notice,  this  list  of conditions and the following disclaimer in the
 *      documentation  and/or  other materials provided with the distribution.
 *   3. Neither  the  name  of  the  copyright  holder  nor  the  names of its
 *      contributors  may  be used to endorse or promote products derived from
 *      this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,  BUT NOT LIMITED  TO, THE
 *   IMPLIED WARRANTIES OF MERCHANTABILITY  AND FITNESS FOR A PARTICULAR PURPOSE
 *   ARE DISCLAIMED.  IN NO EVENT SHALL  THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *   LIABLE  FOR  ANY  DIRECT,  INDIRECT,  INCIDENTAL,  SPECIAL,  EXEMPLARY,  OR
 *   CONSEQUENTIAL  DAMAGES  (INCLUDING,  BUT  NOT  LIMITED  TO,  PROCUREMENT OF
 *   SUBSTITUTE  GOODS  OR SERVICES;  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *   INTERRUPTION) HOWEVER  CAUSED  AND  ON  ANY THEORY OF LIABILITY, WHETHER IN
 *   CONTRACT,  STRICT  LIABILITY,  OR  TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *   ARISING  IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 *
 */



#include "kHD44780.h"


void kHD44780::init(mode_t running_mode)
{
	// wait about 30ms to make sure power is on and LCD is ready to operate
	kRTOS::taskDelay(30);

	mode = running_mode;

	if(mode == kHD44780::Mode4Bit)
	{
		// 4 bit mode initialisation


	}else
	{

		// 8 bit mode initialisation
		sendCMD(0x30);
		kRTOS::taskDelay(4);
		// send double again
		sendCMD(0x30);
		sendCMD(0x30);

		// set interface length to 8 bit, 2 displayed lines, character font 5x7 (typical)
		sendCMD(0x38);
		// turn off display
		sendCMD(kHD44780::CMD->turnOff);
		// clear display
		sendCMD(0x01);
		// set cursor move direction
		sendCMD(0x06);
		// turn on display
		sendCMD(kHD44780::CMD->turnOn);

	}
}
void kHD44780::sendCMD(uint8_t cmd)
{
	uint8_t delay = 1;
	// if it's clear display command or return cursor to home command wait at least 4.1ms for instruction complete
	if(cmd < 4) delay +=4;


	// send command
	RS = 0;
	RW = 0;
	E = 1;
	for(uint8_t i=0;i<8;i++) DB[i] = cmd & (1<<i);
	E = 0;


	kRTOS::taskDelay(delay);
}
void kHD44780::write(uint8_t chr)
{
	// send data
	RS = 1;
	RW = 0;
	E = 1;
	for(uint8_t i=0;i<8;i++) DB[i] = chr & (1<<i);
	E = 0;

	kRTOS::taskDelay(1);
}
void kHD44780::write(char * str)
{
	while(*str) write(*str++);
}
void kHD44780::setCursor(uint8_t row, uint8_t col)
{
	uint8_t address = lineLength*row + col;
	address |= 0x80;
	sendCMD(address);
}
void kHD44780::turnOff(void)
{
	// turn off display
	sendCMD(kHD44780::CMD->turnOff);
}
void kHD44780::turnOn(void)
{
	// turn on display
	sendCMD(kHD44780::CMD->turnOn);
}


