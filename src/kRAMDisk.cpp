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

#include "kRAMDisk.h"


kRAMDisk::kRAMDisk(void)
{
	this->prvSectors = 0;
	this->prvBuff = 0;
}

void kRAMDisk::setRAMbuffer(char * ram_buffer,unsigned long sectors)
{
	this->prvBuff = ram_buffer;
	this->prvSectors = sectors;
}

kFAT::DSTATUS kRAMDisk::init(void)
{
	if(this->prvBuff) return kFAT::RES_OK;
	return kFAT::RES_ERROR;
}
kFAT::DSTATUS kRAMDisk::getStatus(void)
{
	return kFAT::RES_OK;
}
kFAT::DRESULT kRAMDisk::readSector(unsigned char * buff, unsigned long sector, unsigned int count)
{
	unsigned int i;
	unsigned char * pBuff = (unsigned char *)&this->prvBuff[512*sector];

	count *= 512;
	for(i=0;i<count;i++)
	{
		*buff = *pBuff;
		buff++;
		pBuff++;
	}
	return kFAT::RES_OK;
}
kFAT::DRESULT kRAMDisk::writeSector(const unsigned char* buff, unsigned long sector, unsigned int count)
{
	unsigned int i;
	unsigned char * pBuff = (unsigned char *)&this->prvBuff[512*sector];

	count *= 512;
	for(i=0;i<count;i++)
	{
		*pBuff = *buff;
		buff++;
		pBuff++;
	}
	return kFAT::RES_OK;
}
kFAT::DRESULT kRAMDisk::ioctl(unsigned char cmd, void* buff)
{
	DWORD * pData = (DWORD*)buff;

	switch(cmd)
	{
		case CTRL_SYNC:
			return kFAT::RES_OK;
		break;
		case GET_SECTOR_COUNT:

			*pData = this->prvSectors;
			return kFAT::RES_OK;
		break;
		case GET_SECTOR_SIZE:

			*pData = 512;
			return kFAT::RES_OK;
		break;
		case GET_BLOCK_SIZE:

			*pData = 1;
			return kFAT::RES_OK;
		break;
		case CTRL_TRIM:

			return kFAT::RES_OK;
		break;

	}
	return kFAT::RES_OK;
}
