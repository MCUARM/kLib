
#ifndef __kString_H
#define __kString_H

        //#include <kNew.h>

	class kString
	{

		private:

			unsigned char * buff[2];
			unsigned short int buff_leng;
			unsigned short int leng;

			unsigned char currentBuffer;
			unsigned char shadowBuffer(void) const;

			void reallocateMemory(unsigned short buff_len);


		public:

			kString(void);
			kString(const kString & other);
			kString(const char * str);
			~kString(void);

			unsigned short length(void) const;
			bool isEmpty(void);
			unsigned char * c_str(void) const;

			static kString number(int number);
			static const kString number(float number, unsigned char precision=2);

			kString getSubstring(char delimiter,unsigned char returned_part);

			void operator = (const char * str);
			void operator = (const kString & str);

			void operator += (const char * str);
			void operator += (const kString & str);

			const kString operator +(const kString &str);
			const kString operator +(const char * str);

			int toInt(void);
            float toFloat(void);


			friend const kString operator +(const char * str1,kString &str2);


	};

#endif
