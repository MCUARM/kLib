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
#include "kRegister.h"

	unsigned char kRegister_zero_length=0;

kRegister::kRegister(void)
{
	this->pLength = &kRegister_zero_length;
	this->maxLength = 0;
}

unsigned char kRegister::count(void)
{
	return (*pLength);
}
kModule * kRegister::at(unsigned char i)
{
	if(i < (*pLength)) return ppModule[i];
	return 0;
}
bool kRegister::addModule(kModule * module,const char * module_name)
{
	if((*pLength) < maxLength)
	{
		ppModule[(*pLength)] = module;
		(*pLength)++;
		module->setName(module_name);

		return true;
	}

	return false;
}
char kRegister::findByName(const char * name)
{
	unsigned char i;

	for(i=0;i<(*pLength);i++)
	{
		if(kString::firstWordCompare(name,this->ppModule[i]->getName())) return (char)i;
	}

	return -1;
}

kRegister8::kRegister8(void)
{
	this->length = 0;
	this->maxLength = 8;
	this->pLength = &length;

	this->ppModule = &pModule[0];
}
kRegister16::kRegister16(void)
{
	this->length = 0;
	this->maxLength = 16;
	this->pLength = &length;

	this->ppModule = &pModule[0];
}
