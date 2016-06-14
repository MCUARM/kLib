#ifndef __kFrameHeader_H
#define __kFrameHeader_H

	class kFrameHeader
	{
		protected:

			const char * pFrameHeaderString;
			unsigned char frameHeaderStringLength;
			unsigned char * pDataHeaderStringLength;

			unsigned char dataLength;
			char * pDataTypeDescriptor;
			const char ** ppDataHeaderString;

			unsigned short int headerCode;

		public:

			kFrameHeader(void);
			unsigned char getDataLength(void);
			void setFrameHeader(unsigned short int header_code,const char * header_string);

	};


#endif
