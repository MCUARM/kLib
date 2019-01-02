/***********************************************************************************
 *                                                                                 *
 *   kLib - C++ development tools for ARM Cortex-M devices                         *
 *                                                                                 *
 *     Copyright (c) 2018, project author Pawel Zalewski                           *
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



#ifndef __kRingBuffer_H
#define __kRingBuffer_H


	template <class obj_t> class kRingBuffer
	{
		private:

			obj_t * mBuffer;
			unsigned int mSize;
			unsigned int mReadIndex;
			unsigned int mWriteIndex;

			void prvIncrementRingIndex(unsigned int * index){
				*index++;
				if(*index >= this->mSize) *index = 0;
			}

		public:

			kRingBuffer(obj_t * buffer, unsigned int buffer_size){

				this->mBuffer = buffer;
				this->mSize = buffer_size;
				this->mReadIndex = 0;
				this->mWriteIndex = 0;

			}
			void write(obj_t * data, unsigned int size){

				while(size)
				{
					this->mBuffer[this->mWriteIndex] = *data;
					this->prvIncrementRingIndex(&this->mWriteIndex);

					if(this->mReadIndex == this->mWriteIndex)
					{
						this->prvIncrementRingIndex(&this->mReadIndex);
					}

					size--;
				}

			}
			unsigned int read(obj_t * destination, unsigned int max_items_to_read)
			{

				unsigned int obj_read = max_items_to_read;
				while(max_items_to_read)
				{
					if(this->mReadIndex != this->mWriteIndex)
					{
						*destination = this->mBuffer[this->mReadIndex];
						this->prvIncrementRingIndex(&this->mReadIndex);
						destination++;
					} else break;
					max_items_to_read--;
				}
				obj_read -= max_items_to_read;

				return obj_read;
			}
			unsigned int countAvailableData(void){
				if(this->mWriteIndex > this->mReadIndex) return (this->mWriteIndex - this->mReadIndex);
				else return (this->mSize + this->mWriteIndex - this->mReadIndex);
			}

	};

#endif
