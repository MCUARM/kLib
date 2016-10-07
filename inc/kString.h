/***********************************************************************************
 *                                                                                 *
 *   kLib - C++ development tools for ARM Cortex-M devices                         *
 *                                                                                 *
 *     Copyright (c) 2016, project author Paweł Zalewski                                          *
 *     All rights reserved.                                                        *
 *                                                                                 *
 ***********************************************************************************
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions  in  binary  form  must  reproduce the above copyright
 *      notice,  this  list  of conditions and the following disclaimer in the
 *      documentation  and/or  other materials provided with the distribution.
 *   3. Neither  the  name  of  the  copyright  holder  nor  the  names of its
 *      contributors  may  be used to endorse or promote products derived from
 *      this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,  BUT NOT LIMITED  TO, THE
 *   IMPLIED WARRANTIES OF MERCHANTABILITY  AND FITNESS FOR A PARTICULAR PURPOSE
 *   ARE DISCLAIMED.  IN NO EVENT SHALL  THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *   LIABLE  FOR  ANY  DIRECT,  INDIRECT,  INCIDENTAL,  SPECIAL,  EXEMPLARY,  OR
 *   CONSEQUENTIAL  DAMAGES  (INCLUDING,  BUT  NOT  LIMITED  TO,  PROCUREMENT OF
 *   SUBSTITUTE  GOODS  OR SERVICES;  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *   INTERRUPTION) HOWEVER  CAUSED  AND  ON  ANY THEORY OF LIABILITY, WHETHER IN
 *   CONTRACT,  STRICT  LIABILITY,  OR  TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *   ARISING  IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 *
 */
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

			static kString number(int number);
			static char * number(int number,char * buffer);
			static char * copy(const char * source,char * destination);
			static char * skipOneWord(const char * string);
			static char * skipWhiteSpace(const char * string);
			static char * find(const char * string,char chr);
			static char compare(const char * string_1,const char * string_2);
			static bool firstWordCompare(const char * string,const char * word);
			static char * copyOneWord(const char * source,char * destination);
			static int toInt(const char * string);
	};

#endif
