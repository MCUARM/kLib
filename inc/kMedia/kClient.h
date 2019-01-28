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



#ifndef __kClient_H
#define __kClient_H

	#define kClient_RX_BUFFER_SIZE 256
	#define kClinet_TX_BUFFER_SIZE 256

	#include "kSystem.h"
	#include "FreeRTOS_CLI.h"


		class kClient
		{
			public:

				static __inline__ BaseType_t registerCommand( const CLI_Command_Definition_t * const pxCommandToRegister ) __attribute__((always_inline));

				static __inline__ char *getOutputBuffer( void ) __attribute__((always_inline));

				/*
				 * Return a pointer to the xParameterNumber'th word in pcCommandString.
				 */
				static __inline__ const char *getParameter( const char *pcCommandString, UBaseType_t uxWantedParameter, BaseType_t *pxParameterStringLength )__attribute__((always_inline));


		};


		__attribute__((always_inline)) BaseType_t kClient::registerCommand( const CLI_Command_Definition_t * const pxCommandToRegister )
		{
			return FreeRTOS_CLIRegisterCommand(pxCommandToRegister);
		}

		__attribute__((always_inline)) char* kClient::getOutputBuffer(void)
		{
			return FreeRTOS_CLIGetOutputBuffer();
		}
		__attribute__((always_inline)) const char *kClient::getParameter( const char *pcCommandString, UBaseType_t uxWantedParameter, BaseType_t *pxParameterStringLength )
		{
			return FreeRTOS_CLIGetParameter(pcCommandString,uxWantedParameter,pxParameterStringLength);
		}

#endif
