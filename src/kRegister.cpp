#include "kRegister.h"

	unsigned char kRegister_zero_length=0;

kRegister::kRegister(void)
{
	this->pLength = &kRegister_zero_length;
	this->maxLength = 0;
}

unsigned char kRegister::count(void)
{
	return (*pLength);
}
kModule * kRegister::at(unsigned char i)
{
	if(i < (*pLength)) return ppModule[i];
	return 0;
}
bool kRegister::addModule(kModule * module,const char * module_name)
{
	if((*pLength) < maxLength)
	{
		ppModule[(*pLength)] = module;
		(*pLength)++;
		module->setName(module_name);

		return true;
	}

	return false;
}
char kRegister::findByName(const char * name)
{
	unsigned char i;

	for(i=0;i<(*pLength);i++)
	{
		if(kString::firstWordCompare(name,this->ppModule[i]->getName())) return (char)i;
	}

	return -1;
}

kRegister8::kRegister8(void)
{
	this->length = 0;
	this->maxLength = 8;
	this->pLength = &length;

	this->ppModule = &pModule[0];
}
kRegister16::kRegister16(void)
{
	this->length = 0;
	this->maxLength = 16;
	this->pLength = &length;

	this->ppModule = &pModule[0];
}
