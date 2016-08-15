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
kFAT::DSTATUS kRAMDisk::status(void)
{
	return kFAT::RES_OK;
}
kFAT::DRESULT kRAMDisk::read(unsigned char * buff, unsigned long sector, unsigned int count)
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
kFAT::DRESULT kRAMDisk::write(const unsigned char* buff, unsigned long sector, unsigned int count)
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
