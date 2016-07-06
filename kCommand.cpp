#include "kCommand.h"

kCommand kCommand_empty;
const kCommand * kCommand::empty = &kCommand_empty;


kCommand::kCommand(void)
{
	this->length = 0;
}
kCommand::kCommand(const char ** cmd_list, unsigned char n)
{
	this->ppCommand = cmd_list;
	this->length = n;
}
unsigned char kCommand::count(void)
{
	return this->length;
}
void kCommand::setCommandList(const char ** cmd_list, unsigned char n)
{
	this->ppCommand = cmd_list;
	this->length = n;
}
bool kCommand::containCommand(const char * cmd, const char * string)
{
	bool res=false;
	const char * pCmd=cmd;

	while(1)
	{
		if((*pCmd) == (*string))
		{
			pCmd++;
		}else
		{
			pCmd=cmd;
		}
		string++;

		if((*pCmd) == 0) return true;
		if((*string) == ' ' || (*string) == 0) return false;
	}

	return res;
}


char kCommand::decode(const char * cmd)
{
	unsigned char i;

	for(i=0;i<this->length;i++)
	{
		if(this->containCommand(this->ppCommand[i],cmd)) return (char)i;
	}

	return (char)-1;
}

