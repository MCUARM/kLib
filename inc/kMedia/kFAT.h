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



#ifndef __kFAT_H
#define __kFAT_H

	class kFATVolume;


	#include "kSystem.h"
	#include "kMacro.h"
	#include "ff_headers.h"
	#include "ff_stdio.h"


	class kFAT
	{
		public:

			static uint8_t getNewPartitionId(void);

	};





	class kFATVolume
	{
		protected:

			FF_Disk_t *pxDisk;



		public:

			//TODO add format function

	};

	class kDir
	{

		public:

			/*-----------------------------------------------------------
			 * Create directory, remove and rename files
			 * The most up to date API documentation is currently provided on the following URL:
			 * http://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_FAT/Standard_File_System_API.html
			 *-----------------------------------------------------------*/

		#if( ffconfigMKDIR_RECURSIVE == 0 )
			static __inline__ int mkdir( const char *pcPath) __attribute__((always_inline));


		#else
			/* If the parameter bRecursive is non-zero, the entire path will be checked
			and if necessary, created. */

			static __inline__ int mkdir( const char *pcPath, int bRecursive ) __attribute__((always_inline));

		#endif

			/*-----------------------------------------------------------
			 * Create path specified by the pcPath parameter.
			 * The most up to date API documentation is currently provided on the following URL:
			 * http://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_FAT/Standard_File_System_API.html
			 *-----------------------------------------------------------*/
			static __inline__ int mkpath( const char *pcPath ) __attribute__((always_inline));

			/*-----------------------------------------------------------
			 * Remove the directory specified by the pcDirectory parameter.
			 * The most up to date API documentation is currently provided on the following URL:
			 * http://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_FAT/Standard_File_System_API.html
			 *-----------------------------------------------------------*/
			static __inline__ int rmdir( const char *pcDirectory ) __attribute__((always_inline));

			/*-----------------------------------------------------------
			 * Delete a directory and, recursively, all of its contents.
			 * The most up to date API documentation is currently provided on the following URL:
			 * http://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_FAT/Standard_File_System_API.html
			 *-----------------------------------------------------------*/
			#if( ffconfigUSE_DELTREE != 0 )
				/* By default, this function will not be compiled.  The function will
				recursively call itself, which is against the FreeRTOS coding standards, so
				IT MUST BE USED WITH CARE.

				The cost of each recursion will be roughly:
					Stack : 48 (12 stack words)
					Heap  : 112 + ffconfigMAX_FILENAME
				These numbers may change depending on CPU and compiler. */
				static __inline__ int deltree( const char *pcPath ) __attribute__((always_inline));



			#endif

			/*-----------------------------------------------------------
			 * Remove/delete a file.
			 * The most up to date API documentation is currently provided on the following URL:
			 * http://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_FAT/Standard_File_System_API.html
			 *-----------------------------------------------------------*/
			static __inline__ int remove( const char *pcPath ) __attribute__((always_inline));

			/*-----------------------------------------------------------
			 * Move a file, also cross-directory but not across a file system.
			 * The most up to date API documentation is currently provided on the following URL:
			 * http://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_FAT/Standard_File_System_API.html
			 *-----------------------------------------------------------*/
			static __inline__ int rename( const char *pcOldName, const char *pcNewName, int bDeleteIfExists ) __attribute__((always_inline));

			/*-----------------------------------------------------------
			 * Get the status of a file.
			 * The most up to date API documentation is currently provided on the following URL:
			 * http://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_FAT/Standard_File_System_API.html
			 *-----------------------------------------------------------*/
			static __inline__ int stat( const char *pcFileName, FF_Stat_t *pxStatBuffer ) __attribute__((always_inline));
			/* _HT_ Keep this for a while, until the new ff_stat() is wel tested */
			static __inline__ int old_stat( const char *pcFileName, FF_Stat_t *pxStatBuffer ) __attribute__((always_inline));



			/*-----------------------------------------------------------
			 * Working directory and iterating through directories.
			 * The most up to date API documentation is currently provided on the following URL:
			 * http://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_FAT/Standard_File_System_API.html
			 *-----------------------------------------------------------*/
			#if ffconfigHAS_CWD

				static __inline__ int chdir( const char *pcDirectoryName )__attribute__((always_inline));
				static __inline__ char* getcwd( char *pcBuffer, size_t xBufferLength )__attribute__((always_inline));


			#endif

			static __inline__ int findfirst( const char *pcDirectory, FF_FindData_t *pxFindData )__attribute__((always_inline));
			static __inline__ int findnext( FF_FindData_t *pxFindData )__attribute__((always_inline));
			static __inline__ int isdirempty(const char *pcPath )__attribute__((always_inline));




	};

	class kFile
	{
		protected:



		public:



	};



	#if( ffconfigMKDIR_RECURSIVE == 0 )

		__attribute__((always_inline)) int kDir::mkdir( const char *pcPath)
		{
			return ff_mkdir( pcPath);
		}

	#else

		__attribute__((always_inline)) int kDir::mkdir( const char *pcPath, int bRecursive )
		{
			return ff_mkdir(pcPath,bRecursive );
		}

	#endif
	__attribute__((always_inline)) int kDir::mkpath( const char *pcPath )
	{
		return ff_mkpath(pcPath );
	}
	__attribute__((always_inline)) int kDir::rmdir( const char *pcDirectory )
	{
		return ff_rmdir(pcDirectory );
	}
	#if( ffconfigUSE_DELTREE != 0 )
		__attribute__((always_inline)) int kDir::deltree( const char *pcPath )
		{
			return ff_deltree(pcPath );
		}
	#endif
	__attribute__((always_inline)) int kDir::remove( const char *pcPath )
	{
		return ff_remove(pcPath );
	}
	__attribute__((always_inline)) int kDir::rename( const char *pcOldName, const char *pcNewName, int bDeleteIfExists )
	{
		return ff_rename(pcOldName,pcNewName,bDeleteIfExists );
	}
	__attribute__((always_inline)) int kDir::stat( const char *pcFileName, FF_Stat_t *pxStatBuffer )
	{
		return ff_stat(pcFileName,pxStatBuffer );
	}
	__attribute__((always_inline)) int kDir::old_stat( const char *pcName, FF_Stat_t *pxStatBuffer )
	{
		return ff_old_stat(pcName,pxStatBuffer );
	}

	#if ffconfigHAS_CWD
		__attribute__((always_inline)) int kDir::chdir( const char *pcDirectoryName )
		{
			return ff_chdir(pcDirectoryName );
		}
		__attribute__((always_inline)) char* kDir::getcwd( char *pcBuffer, size_t xBufferLength )
		{
			return ff_getcwd(pcBuffer,xBufferLength );
		}
	#endif

	__attribute__((always_inline)) int kDir::findfirst( const char *pcDirectory, FF_FindData_t *pxFindData )
	{
		return ff_findfirst(pcDirectory,pxFindData );
	}

	__attribute__((always_inline)) int kDir::findnext( FF_FindData_t *pxFindData )
	{
		return ff_findnext(pxFindData );
	}

	__attribute__((always_inline)) int kDir::isdirempty(const char *pcPath )
	{
		return ff_isdirempty(pcPath );
	}
#endif
