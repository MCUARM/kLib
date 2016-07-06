#ifndef __kRegister_H
#define __kRegister_H

	#include "kModule.h"
	#include "kString.h"

	class kRegister
	{
		protected:

			unsigned char maxLength;
			unsigned char * pLength;
			kModule ** ppModule;

		public:

			kRegister(void);
			unsigned char count(void);
			kModule * at(unsigned char i);
			bool addModule(kModule * module,const char * module_name);
			char findByName(const char * name);
	};

	class kRegister8 : private kRegister
	{
		private:

			unsigned char length;
			kModule * pModule[8];

		public:

			kRegister8(void);

	};


	class kRegister16 : private kRegister
	{
		private:

			unsigned char length;
			kModule * pModule[16];

		public:

			kRegister16(void);

	};

#endif
