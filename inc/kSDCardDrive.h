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
