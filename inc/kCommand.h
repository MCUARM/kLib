#ifndef __kCommand_H
#define __kCommand_H



	class kCommand;

	class kCommand
	{
		protected:

			unsigned char length;
			const char ** ppCommand;

			bool containCommand(const char * cmd, const char * string);

		public:

			kCommand(void);
			kCommand(const char ** cmd_list, unsigned char n);
			unsigned char count(void);
			char decode(const char * cmd);
			void setCommandList(const char ** cmd_list, unsigned char n);

			static const kCommand * empty;
	};

#endif
