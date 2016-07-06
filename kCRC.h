#ifndef __kCRC_H
#define __kCRC_H


	class kCRC
	{
		public:

			kCRC(void);
			unsigned char getChecksumGPS(const char * buffer, unsigned short int bytes);

	};

#endif
