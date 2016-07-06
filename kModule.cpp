#include "kModule.h"
#include "kSystem.h"

const char * kModule_default_name = "";

kModule::kModule(void)
{
	this->pName = kModule_default_name;
	this->pCommand = (kCommand*)kCommand::empty;
}
void kModule::setName(const char * name)
{
	this->pName = name;
}
const char * kModule::getName(void)
{
	return this->pName;
}
kCommand * kModule::commands()
{
	return this->pCommand;
}
char * kModule::processCommand(const char * cmd, char * response)
{
	K_UNUSED(cmd);
	(*response) = 0;
	return response;
}
void kModule::setCommands(kCommand * commands)
{
	this->pCommand = commands;
}
