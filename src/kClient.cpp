/***********************************************************************************
 *                                                                                 *
 *   kLib - C++ development tools for ARM Cortex-M devices                         *
 *                                                                                 *
 *     Copyright (c) 2016, project author Paweł Zalewski                                          *
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

#include "kClient.h"

#if (kLib_config_USE_MODULE == 1)

	kClient::kClient(void)
	{

	}
	void kClient::run(unsigned int BaudRate)
	{
		this->terminator('\r');
		kSerial::run(BaudRate);
	}

	void kClient::check(void)
	{
		unsigned short int i;
		char * pBuffer;
		kRegister * systemReg;
		kModule * module;
		char module_id;

		if(!this->newDataAvailable()) return;

		i = this->readData(this->cli_rxBuffer);
		this->cli_rxBuffer[i]=0;

		pBuffer = kString::skipWhiteSpace(cli_rxBuffer);
		if(!(*pBuffer))
		{
			this->sendResponse(cli_txBuffer);
			return;
		}

		if(kString::firstWordCompare(pBuffer,"system"))
		{
			pBuffer = kString::skipOneWord(pBuffer);
			if(!(*pBuffer))
			{
				this->sendResponse(cli_txBuffer);
				return;
			}
			pBuffer = kSystem.processCommand(pBuffer,cli_txBuffer);
		}else
		{
			systemReg = kSystem.getSystemRegister();
			module_id = systemReg->findByName(cli_rxBuffer);

			if(module_id >= 0)
			{
				module = systemReg->at(module_id);
				pBuffer = module->processCommand(pBuffer,cli_txBuffer);
			}else
			{
				pBuffer = kString::copy("Unresolved module",cli_txBuffer);
			}

		}


		this->sendResponse(pBuffer);


	}
	void kClient::sendResponse(char * buffer)
	{
		buffer = kString::copy("\rkSystem > ",buffer);
		*buffer = 0;
		(*this) << cli_txBuffer;
	}

#endif
