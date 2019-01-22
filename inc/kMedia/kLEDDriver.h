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



#ifndef __kLEDDRIVER_H
#define __kLEDDRIVER_H

	#include "kSystem.h"
	#include "kLED.h"
	#include "kLinear.h"
	#include "kRTOS.h"

	class kLEDDriver
	{


		public:

			 typedef struct __attribute__ ((packed))
			{
				uint16_t programLines;
				uint16_t loops;
			}ProgramHeader;

			typedef struct __attribute__ ((packed))
			{
				uint16_t time_ms;
				uint16_t brightness;
			}ProgramLine;

			typedef struct
			{
				ProgramHeader header;
				ProgramLine line1;
				ProgramLine line2;
			}HeartBeatProgram_struct;


		public:

			typedef enum
			{
				stop = 0,
				start = 1,
				pause = 2
			}state_t;


			void setProgram(const void * program);
			void setState(state_t state);

			void run(const char * task_name,unsigned long priority,const void * led_program);

			static const HeartBeatProgram_struct HeartBeat;

		protected:

			friend void kLEDDriver_task(void* args);

			kRTOS::task_t taskHandle=0;

			kRTOS::Queue stateRequestQueue;

			kLED * LED;
			kLinear lin;

			bool taskCreated=false;

			ProgramHeader * header;
			ProgramLine * line;
			uint16_t cmd_index;
			uint16_t loop_counter;
			uint8_t state=stop;



	};


#endif
