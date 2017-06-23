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

#ifndef __kFrame_H
#define __kFrame_H

	#include "kSerial.h"

	template <class T> class kFrame
	{
		protected:

			T * mFrame;
			unsigned int mFrameSizeInBytes;

			void * mStart;
			unsigned char mStartSizeInBytes;

			void * mEnd;
			unsigned char mEndSizeInBytes;


		public:


			kFrame(T * data, unsigned int data_size_in_bytes)
			{
				this->mFrame = data;
				this->mFrameSizeInBytes = data_size_in_bytes;

				this->mStartSizeInBytes = 0;
				this->mEndSizeInBytes = 0;

				this->mStart = 0;
				this->mEnd = 0;

			}
			T * data(void){
				return mFrame;
			}
			void setStartSequence(void * start_sequence, unsigned char start_size_in_bytes)
			{
				this->mStart = start_sequence;
				this->mStartSizeInBytes = start_size_in_bytes;
			}
			void setEndSequence(void * end_sequence, unsigned char end_size_in_bytes)
			{
				this->mEnd = end_sequence;
				this->mEndSizeInBytes = end_size_in_bytes;
			}

			template <class T_obj>
			friend const kSerial& operator <<(const kSerial &serial,kFrame<T_obj> & frame){

				serial.write(frame.mStart,frame.mStartSizeInBytes);
				serial.write(frame.data(),frame.mFrameSizeInBytes);
				serial.write(frame.mEnd,frame.mEndSizeInBytes);

				return serial;
			}
	};

#endif
