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



#ifndef __kMP3_H
#define __kMP3_H

	#include "kSystem.h"




	class kMP3
	{
		typedef enum
		{
			NotSynchronized,
			FirstByteMatched,
			SecondByteMatched,
			FrameSynchronized
		}SYNCHRO_STATE_T;

		typedef enum
		{
			MPEG_Version_2_dot_5 = 0,
			MPEG_Version_RESERVED = 1,
			MPEG_Verison_2 = 2, // (ISO/IEC 13818-3)
			MPEG_Version_1 = 3 // (ISO/IEC 11172-3)

		}MPEG_Audio_version_ID_T;

		typedef enum
		{
			Layer_RESERVED = 0,
			Layer_III = 1,
			Layer_II = 2,
			Layer_I = 3
		}MPEG_LAYER_T;

		typedef enum
		{
			CRC_Protected = 0,
			NotProtected = 1
		}MPEG_PROTECTION_T;

			MPEG_Audio_version_ID_T MPEG_version;
			MPEG_LAYER_T MPEG_layer;
			MPEG_PROTECTION_T MPEG_protection;

			SYNCHRO_STATE_T SynchronizationState;

			void prvTrySynchronizeFrame(uint8_t byte);

		public:

			uint32_t feed(uint8_t byte);

	};


#endif
