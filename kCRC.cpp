#include "kCRC.h"

kCRC::kCRC(void)
{

}

unsigned char kCRC::getChecksumGPS(const char * buffer, unsigned short int bytes)
{
	unsigned char res=0;
	unsigned short int i;

	for(i=0;i<bytes;i++)
	{
		res = char(res ^ (*buffer));
		buffer++;
	}

	return res;
}
