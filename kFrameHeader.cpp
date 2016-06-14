#include "kFrameHeader.h"

const char * default_pFrameString = "null";
const char * default_pDataHeaderString[1] = {default_pFrameString};

kFrameHeader::kFrameHeader(void)
{
	this->pFrameHeaderString = default_pFrameString;
	this->frameHeaderStringLength = 4;

	this->dataLength = 0;
	this->pDataTypeDescriptor = (char *)default_pFrameString;
	this->ppDataHeaderString = default_pDataHeaderString;
}
unsigned char kFrameHeader::getDataLength(void)
{
	return this->dataLength;
}
void kFrameHeader::setFrameHeader(unsigned short int header_code,const char * header_string)
{
	this->headerCode=header_code;
	this->pFrameHeaderString = header_string;
	this->frameHeaderStringLength=0;
	while(header_string++) this->frameHeaderStringLength++;

}
