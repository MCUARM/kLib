#ifndef __kFrameHeader_H
#define __kFrameHeader_H

	extern float default_data_storage;

	class kFrameHeader
	{

		public:

			const char * pFrameHeaderString;
			unsigned char frameHeaderStringLength;
			unsigned char * pDataHeaderStringLength;

			unsigned char dataLength;
			char * pDataTypeDescriptor;
			const char ** ppDataHeaderString;
			void ** ppData;

			unsigned short int headerCode;

		public:

			kFrameHeader(void);
			unsigned char getDataLength(void);
			void setFrameHeader(unsigned short int header_code,const char * header_string);

	};


#endif
