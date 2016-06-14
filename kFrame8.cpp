#include "kFrame8.h"

float default_data_storage=0;

kFrame8::kFrame8(void)
{
	unsigned char i;

	for(i=0;i<8;i++)
	{
		this->pData[i] = &default_data_storage;
		this->pDataHeaderString[i] = (const char *)&default_data_storage;
		this->dataHeaderStringLength[i] = 0;
	}

	this->ppDataHeaderString = pDataHeaderString;
	this->pDataHeaderStringLength = dataHeaderStringLength;
}
void kFrame8::setDataTypes(const char * formatted_string)
{
	this->dataLength=0;
	this->pDataTypeDescriptor = (char *)formatted_string;
	while(formatted_string++) this->dataLength++;

	if(this->dataLength > 8) this->dataLength = 0;
}
void kFrame8::setData(unsigned char data_id,const char * headerString, void * data_pointer)
{
	if(data_id >= 8) return;

	this->dataHeaderStringLength[data_id]=0;
	this->pDataHeaderString[data_id] = headerString;
	while(headerString++) this->dataHeaderStringLength[data_id]++;

	this->pData[data_id] = data_pointer;
}
void kFrame8::setLength(unsigned char length)
{
	if(length > 8) return;
	this->dataLength = length;
}
