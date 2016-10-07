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

#include "kCommand.h"

kCommand kCommand_empty;
const kCommand * kCommand::empty = &kCommand_empty;


kCommand::kCommand(void)
{
	this->length = 0;
}
kCommand::kCommand(const char ** cmd_list, unsigned char n)
{
	this->ppCommand = cmd_list;
	this->length = n;
}
unsigned char kCommand::count(void)
{
	return this->length;
}
void kCommand::setCommandList(const char ** cmd_list, unsigned char n)
{
	this->ppCommand = cmd_list;
	this->length = n;
}
bool kCommand::containCommand(const char * cmd, const char * string)
{
	bool res=false;
	const char * pCmd=cmd;

	while(1)
	{
		if((*pCmd) == (*string))
		{
			pCmd++;
		}else
		{
			pCmd=cmd;
		}
		string++;

		if((*pCmd) == 0) return true;
		if((*string) == ' ' || (*string) == 0) return false;
	}

	return res;
}


char kCommand::decode(const char * cmd)
{
	unsigned char i;

	for(i=0;i<this->length;i++)
	{
		if(this->containCommand(this->ppCommand[i],cmd)) return (char)i;
	}

	return (char)-1;
}

