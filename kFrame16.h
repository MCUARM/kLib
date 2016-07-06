#ifndef __kFrame16_H
#define __kFrame16_H

	#include "kFrameHeader.h"

	class kFrame16 : public kFrameHeader
	{
		private:

			void * pData[16];
			const char * pDataHeaderString[16];
			unsigned char dataHeaderStringLength[16];

		public:

			kFrame16(void);
			void setDataTypes(const char * formatted_string);
			void setData(unsigned char data_id,const char * headerString, void * data_pointer);
			void setLength(unsigned char length);

	};


#endif
