#ifndef __kRAMDisk_H
#define __kRAMDisk_H

	#include "kFAT.h"

	class kRAMDisk : public kFATVolume
	{
		private:

			char * prvBuff;
			unsigned long prvSectors;

		public:
		
			kRAMDisk(void);

			void setRAMbuffer(char * ram_buffer,unsigned long sectors);

			kFAT::DSTATUS init(void);
			kFAT::DSTATUS status(void);
			kFAT::DRESULT read(unsigned char * buff, unsigned long sector, unsigned int count);
			kFAT::DRESULT write(const unsigned char* buff, unsigned long sector, unsigned int count);
			kFAT::DRESULT ioctl(unsigned char cmd, void* buff);


	};

#endif
