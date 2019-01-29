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



#include "kMP3.h"



void kMP3::prvTrySynchronizeFrame(uint8_t byte)
{
	// Synchronisation sequence is 11 bits set to 1

	switch(SynchronizationState)
	{
		case NotSynchronized:
			// Try to match first synchronisation byte
			// it should be 0xFF
			if(byte == 0xFF) SynchronizationState = FirstByteMatched;

			break;
		case FirstByteMatched:
			// Try to match second synchronisation byte
			// it should have 3 most significant bits set
			if(byte & 0xE0)
			{
				// yes byte contains synchronisation bits

				// get MPEG version saved also in this byte
				MPEG_version = ((byte & 0x18) >> 3);
				// extract Layer description
				MPEG_layer = ((byte & 0x06) >> 1);
				// get CRC protection bit
				MPEG_protection = (byte & 0x01);

				SynchronizationState = SecondByteMatched;
			}

			break;
		case SecondByteMatched:
			// Try to match third synchronisation byte
			// it should be 0xFF

			break;
		case FrameSynchronized:

			break;
		default:

	}

}

uint32_t kMP3::feed(uint8_t byte)
{
	if(SynchronizationState != FrameSynchronized)
	{

	}




	return 0;
}
