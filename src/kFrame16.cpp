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
