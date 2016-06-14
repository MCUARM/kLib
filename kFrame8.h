#ifndef __kFrame8_H
#define __kFrame8_H

	#include "kFrameHeader.h"

	class kFrame8 : public kFrameHeader
	{
		private:

			void * pData[8];
			const char * pDataHeaderString[8];
			unsigned char dataHeaderStringLength[8];

		public:

			kFrame8(void);
			void setDataTypes(const char * formatted_string);
			void setData(unsigned char data_id,const char * headerString, void * data_pointer);
			void setLength(unsigned char length);

	};


#endif
