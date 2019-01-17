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



#include "kLEDDriver.h"

const kLEDDriver::HeartBeatProgram_struct HeartBeat =
{
		{0xFFFF,4},
		{500,	0xFFFF},
		{1000,	0x0000}
};



void kLEDDriver::setProgram(const void * program)
{
	header = (kLEDDriver::ProgramHeader *)program;
	cmd_index = 0;
	loop_counter = 0;
	LED->set(0);


}

void kLEDDriver::run()
{
	kRTOS::tick_t current_time = kRTOS::taskGetTickCount();
	kRTOS::tick_t zulu_time;
	kRTOS::tick_t end_time;

	ProgramLine * currentLine;
	ProgramLine * nextLine;

	while(1)
	{
		currentLine = &line[cmd_index++];
		if(cmd_index >= header->programLines)
		{
			loop_counter++;
			if(loop_counter < header->loops)
			{
				// repeat program
				// set cmd_index to 0
				cmd_index = 0;
			}else
			{
				// exit program
				break;
			}

		}
		nextLine = &line[cmd_index];

		lin.set(0,currentLine->brightness,currentLine->time_ms,nextLine->brightness);


		zulu_time = current_time;
		end_time = zulu_time + currentLine->time_ms;
		while(current_time < end_time)
		{
			LED->set(lin.getValueAt(current_time-zulu_time));
			kRTOS::taskDelayUntil(&current_time,20);
		}

	}

}

