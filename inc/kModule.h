#ifndef __kModule_H
#define __kModule_H

	#include "kCommand.h"

	class kModule
	{
		protected:

			const char * pName;
			kCommand * pCommand;

		public:

			kModule(void);
			void setName(const char * name);
			const char * getName(void);
			kCommand * commands();
			void setCommands(kCommand * commands);
			char * processCommand(const char * cmd, char * response);

	};

#endif
