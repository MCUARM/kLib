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



#include "kFAT.h"			/* Declarations of kVOLUME API */
#include "diskio.h"		/* Declarations of disk I/O functions */



static uint8_t partition_counter = 0;
uint8_t kFAT::getNewPartitionId(void)
{
	return partition_counter++;
}

kFile kFile::truncate( const char * pcFileName, long lTruncateSize )
{
	kFile fil;
	fil.pxStream = ff_truncate(pcFileName,lTruncateSize );
	return fil;
}

#if( ffconfigFPRINTF_SUPPORT == 1 )

	int kFile::printf(const char *pcFormat, ... )
	{
		int iCount;
		size_t xResult;
		char *pcBuffer;
		va_list xArgs;

		pcBuffer = ( char * ) ffconfigMALLOC( ffconfigFPRINTF_BUFFER_LENGTH );
		if( pcBuffer == NULL )
		{
			/* Store the errno to thread local storage. */
			stdioSET_ERRNO( pdFREERTOS_ERRNO_ENOMEM );
			iCount = -1;
		}
		else
		{
			va_start( xArgs, pcFormat );
			iCount = vsnprintf( pcBuffer, ffconfigFPRINTF_BUFFER_LENGTH, pcFormat, xArgs );
			va_end( xArgs );

			/* ff_fwrite() will set ff_errno. */
			if( iCount > 0 )
			{
				xResult = ff_fwrite( pcBuffer, ( size_t ) 1, ( size_t ) iCount, pxStream );
				if( xResult < ( size_t ) iCount )
				{
					iCount = -1;
				}
			}

			ffconfigFREE( pcBuffer );
		}

		return iCount;
	}

#endif



