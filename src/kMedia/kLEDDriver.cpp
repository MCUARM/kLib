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
	// do not allow program changes if its already started
	// you need to stop current program first
	if(state != stop) return;


	header = (kLEDDriver::ProgramHeader *)program;
	cmd_index = 0;
	loop_counter = 0;
	LED->set(0);


}

void kLEDDriver_task(void* args)
{
	kLEDDriver * driver = static_cast<kLEDDriver*>(args);



	kRTOS::tick_t current_time;
	kRTOS::tick_t zulu_time;
	kRTOS::tick_t end_time;
	bool isStarting;
	kLEDDriver::ProgramLine startingLine;

	kLEDDriver::ProgramLine * currentLine;
	kLEDDriver::ProgramLine * nextLine;




	// LED task main loop
	while(1)
	{
		// suspend task if state is not equal start until next state change is received
		if(driver->state != kLEDDriver::start) driver->stateRequestQueue.receive(&driver->state,portMAX_DELAY);

		// LED program main loop
		while(driver->state == kLEDDriver::start)
		{

			// prepare to execute program

			// get current RTOS time
			current_time = kRTOS::taskGetTickCount();
			// set beginning line as current LED brightness
			// this is the starting point in linear function model to interpolate brightness value
			// between current LED brightness and brightness encoded in first program line
			startingLine.time_ms = 0;
			startingLine.brightness = driver->LED->getBrightness();
			// set isStarting flag to indicate that program has just started
			isStarting = true;
			// set command intex to 0
			driver->cmd_index = 0;
			driver->loop_counter = 0;

			while(driver->loop_counter < driver->header->loops && driver->state != kLEDDriver::stop)
			{

				// set current executing line of code as starting point
				if(isStarting)
				{
					// if program is just started
					currentLine = &startingLine;
					isStarting = false;
				}else
				{
					// program is executing next line (not first)
					currentLine = &driver->line[driver->cmd_index++];
				}

				// assert cmd_index value
				if(driver->cmd_index >= driver->header->programLines)
				{
					// cmd_index exceeds number of lines in program
					// this is end of sequence

					// update loop counter
					driver->loop_counter++;

					// check if loop counter reached number of loops to be executed
					if(driver->loop_counter < driver->header->loops)
					{
						// no - loop counter didn't reach programmed loops

						// repeat program
						// set cmd_index to 0
						driver->cmd_index = 0;
					}else
					{
						// yes - loop counter have reached programmed loops

						// exit program by breaking while loop
						break;
					}

				}


				// set next executing line of code as end point
				nextLine = &driver->line[driver->cmd_index];

				// assert time in next line
				if(!nextLine->time_ms)
				{
					// time equals 0. It means value must be set immediately
					// set new brightness value
					driver->LED->set(nextLine->brightness);
					// go to the next stage of while loop (skip the code below)
					continue;
				}

				// set new parameters for linear function model
				// this model is used to interpolate current value of brightness between
				// two points (command lines) in program
				driver->lin.set(0,currentLine->brightness,nextLine->time_ms,nextLine->brightness);

				// zulu time is the RTOS time value (absolute time) captured at beginning of current line execution
				zulu_time = current_time;
				// end time is the RTOS time value which expires when time pass nextLine command in program code
				end_time = zulu_time + currentLine->time_ms;

				// interpolating while loop
				// in this loop LED brightness value is being interpolated between 2 lines of program - currentLine and nextLine
				while(current_time < end_time && driver->state != driver->stop)
				{
					driver->stateRequestQueue.receive(&driver->state,0);

					switch(driver->state)
					{
						case kLEDDriver::start:

							// set new LED brightness according to linear interpolation
							driver->LED->set(driver->lin.getValueAt(current_time-zulu_time));

							break;
						case kLEDDriver::pause:

							// pause signal has been send
							// do nothing except shifting zulu_time
							zulu_time += 20;

							break;
						case kLEDDriver::stop:

							break;
						default:

							// unknown state received
							// set state to stop
							driver->state = kLEDDriver::stop;

							break;
					}


					// sleep task for 20ms that is interpolation with frequency 50Hz
					// This frequency is fairly enough to make an impression LED brightness is changing fluently
					kRTOS::taskDelayUntil(&current_time,20);

				}
				// end of interpolation stage

				// go to next while loop iteration
			}
			// end of LED program
			// set state to stopped
			driver->state = kLEDDriver::stop;
		}
	}




}


void kLEDDriver::run(const char * task_name,unsigned long priority,const void * led_program)
{
	// prohibit calling this function more than one time
	if(taskHandle) return;


	if(!stateRequestQueue.create(1,sizeof(uint8_t))) return;

	// if led_program is not null set new led program and force start to easy startup
	if(led_program)
	{
		setProgram(led_program);
		state = start;
	}

	// create led driver task
	kRTOS::taskCreate(kLEDDriver_task,task_name,1024,this,priority,&this->taskHandle);

}
void kLEDDriver::setState(state_t state)
{
	stateRequestQueue.send(&state,0);
}
