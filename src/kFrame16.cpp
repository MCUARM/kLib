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

#include "kFrame16.h"


kFrame16::kFrame16(void)
{
	unsigned char i;

	for(i=0;i<16;i++)
	{
		this->pData[i] = &default_data_storage;
		this->pDataHeaderString[i] = (const char *)&default_data_storage;
		this->dataHeaderStringLength[i] = 0;
	}

	this->ppDataHeaderString = pDataHeaderString;
	this->pDataHeaderStringLength = dataHeaderStringLength;
	this->ppData = this->pData;
}
void kFrame16::setDataTypes(const char * formatted_string)
{
	this->dataLength=0;
	this->pDataTypeDescriptor = (char *)formatted_string;
	while(formatted_string++) this->dataLength++;

	if(this->dataLength > 16) this->dataLength = 0;
}
void kFrame16::setData(unsigned char data_id,const char * headerString, void * data_pointer)
{
	if(data_id >= 16) return;

	this->dataHeaderStringLength[data_id]=0;
	this->pDataHeaderString[data_id] = headerString;
	while(headerString++) this->dataHeaderStringLength[data_id]++;

	this->pData[data_id] = data_pointer;
}
void kFrame16::setLength(unsigned char length)
{
	if(length > 16) return;
	this->dataLength = length;
}
