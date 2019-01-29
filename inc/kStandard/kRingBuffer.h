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

			// holds physical buffer pointer
			obj_t * mBuffer;
			// holds buffer length (this is not sizeof(mBuffer[]) array)
			unsigned int mSize;
			// reading index
			unsigned int mReadIndex;
			// writing index
			unsigned int mWriteIndex;

			// increments chosen ring buffer pointer and assert it always within bounds
			void prvIncrementRingIndex(unsigned int * index){
				// increment pointer
				(*index)++;
				// assert index maximum value
				if(*index >= mSize) *index = 0;
			}
			void prvCheckBufferOverflow(void)
			{
				if(mReadIndex == mWriteIndex)
				{
					// buffer is overflowed
					// read index must be pushed forward item step after write index
					// one data item is lost (overwritten)
					prvIncrementRingIndex(&mReadIndex);
				}
			}

		public:

			kRingBuffer(obj_t * buffer, unsigned int buffer_size)
			{

				mBuffer = buffer;
				mSize = buffer_size;
				mReadIndex = 0;
				mWriteIndex = 0;

			}
			// writes data to buffer
			void write(obj_t * data, unsigned int size)
			{
				while(size--)
				{
					// copy new data item to buffer
					write(*data);
					// increment data pointer
					data++;
				}
			}
			// writes one data item to buffer
			void write(obj_t & data)
			{
					// copy new data item to buffer
					mBuffer[mWriteIndex] = data;
					// increment write index
					prvIncrementRingIndex(&mWriteIndex);
					// check for buffer overflow
					prvCheckBufferOverflow();
			}

			// reads data from buffer
			unsigned int read(obj_t * destination, unsigned int max_items_to_read)
			{
				// set read items counter to maximum items allowed to read
				unsigned int obj_read = max_items_to_read;

				// read all items one by one
				while(max_items_to_read)
				{
					// is there any data to read?
					if(mReadIndex != mWriteIndex)
					{
						// yes
						// copy data item from ring buffer to destination
						*destination = this->mBuffer[mReadIndex];
						// increment read index
						prvIncrementRingIndex(&mReadIndex);
						// increment destination pointer
						destination++;

					} else break; // there is no data left to read (break loop)

					// decrease max_items_to_read
					max_items_to_read--;
				}
				// actually obj_read = (max items to read) - (data items read)
				obj_read -= max_items_to_read;

				// return number of read items
				return obj_read;
			}

			unsigned int countAvailableData(void)
			{
				// standard for all buffers - writing index is greater than read index
				if(mWriteIndex > mReadIndex) return (mWriteIndex - this->mReadIndex);

				// else statement (mWriteIndex <= mReadIndex)
				// index inversion - write index is before read index
				return (mSize + this->mWriteIndex - mReadIndex);
			}

	};

#endif
