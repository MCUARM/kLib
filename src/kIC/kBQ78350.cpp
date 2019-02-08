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



#include "kBQ78350.h"



void kBQ78350::run()
{
	// bq78350 default address
	address = 0x16;
	// set to maximum SMB speed
	kI2C::run(kI2C::I2C_Speed->_100kHz);
}
void kBQ78350::sendCommandSBS(uint8_t command_SBS, void * read_buffer, uint8_t bytesToRead)
{
	// send SBS command (SMB Byte Protocol)
	writeByte(command_SBS);
	// read command response (bytes to read are variable and depend on specific command)
	read(read_buffer,bytesToRead);
}
void kBQ78350::sendCommandMA(uint16_t command_MA, void * read_buffer, uint8_t bytesToRead)
{
	/*
	 * Each data entity read/write through ManufacturerBlockAccess() is in Little Endian. For example, a 2-byte
	 * data 0x1234 should be read/write as 0x34 + 0x12; a 4-byte 0x12345678 data should be read/write as
	 * 0x78+ 0x56+ 0x34 + 0x12.
	 */
	uint8_t data[3];
	// Special SBS command -> ManufacturerAccess() extends commands to manufacturer commands (SBS command 0x00)
	data[0] = 0x00;
	data[1] = (uint8_t)(command_MA & 0x00FF);
	data[2] = (uint8_t)(command_MA >> 8);

	// send ManufacturerAccess command
	write(data,3);
	// read response
	read(read_buffer,bytesToRead);
}
uint16_t kBQ78350::getCellVoltage(uint8_t cell_number)
{
	//assert cell_number
	if(cell_number < 1) cell_number = 1;
	if(cell_number > 15) cell_number = 15;

	uint16_t res;
	// get proper SBS command
	uint8_t SBS_CellVoltageX = 0x40 - cell_number;
	// send command and read result
	sendCommandSBS(SBS_CellVoltageX,&res,2);

	return res;
}
uint16_t kBQ78350::getPackVoltage(void)
{
	uint16_t res;
	sendCommandSBS(kBQ78350::SBS_Command->Voltage,&res,2);
	return res;
}
uint16_t kBQ78350::getCurrent(void)
{
	uint16_t res;
	sendCommandSBS(kBQ78350::SBS_Command->Current,&res,2);
	return res;
}
uint16_t kBQ78350::getRemainingCapacity(void)
{
	uint16_t res;
	sendCommandSBS(kBQ78350::SBS_Command->RemainingCapacity,&res,2);
	return res;
}
uint8_t kBQ78350::getStateOfHealth(void)
{
	uint8_t res;
	sendCommandSBS(kBQ78350::SBS_Command->StateOfHealth,&res,1);
	return res;
}
