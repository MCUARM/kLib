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

#ifndef __kSDCardDrive_H
#define __kSDCardDrive_H

	#include "kSDCard.h"
	#include "kFAT.h"

	class kSDCardDrive : public kSDCard, public kFATVolume
	{

		public:

			kFAT::DSTATUS __inline__ init(void) __attribute__((always_inline));
			kFAT::DSTATUS __inline__ getStatus(void) __attribute__((always_inline));
			kFAT::DRESULT __inline__ readSector(unsigned char * buff, unsigned long sector, unsigned int count)__attribute__((always_inline));
			kFAT::DRESULT __inline__ writeSector(const unsigned char* buff, unsigned long sector, unsigned int count)__attribute__((always_inline));
			kFAT::DRESULT ioctl(unsigned char cmd, void* buff);


	};

	__attribute__((always_inline)) kFAT::DSTATUS kSDCardDrive::init(void)
	{
		return (kFAT::DSTATUS)this->kSDCard::init();
	}
	__attribute__((always_inline)) kFAT::DSTATUS kSDCardDrive::getStatus(void)
	{
		return (kFAT::DSTATUS)this->kSDCard::getStatus();
	}
	__attribute__((always_inline)) kFAT::DRESULT kSDCardDrive::readSector(unsigned char * buff, unsigned long sector, unsigned int count)
	{
		return (kFAT::DRESULT)this->kSDCard::readSector(buff,sector,count);
	}
	__attribute__((always_inline)) kFAT::DRESULT kSDCardDrive::writeSector(const unsigned char* buff, unsigned long sector, unsigned int count)
	{
		return (kFAT::DRESULT)this->kSDCard::writeSector(buff,sector,count);
	}
#endif
