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



#include "kSDCardDrive.h"
#include "ff_sys.h"


/* Used as a magic number to indicate that an FF_Disk_t structure is a RAM
disk. */
#define sdSIGNATURE				0x21404342

bool kSDCardDrive::init(const char *pcName, size_t xIOManagerCacheSize)
{
	uint32_t ulSectorCount;

	FF_Error_t xError;
	FF_CreationParameters_t xParameters;

	if(SD.init() != kSD::OK)
	{
		FF_PRINTF("kSDCardDrive::init: Error during SD card initialisation\n");
		return false;
	}
	if(SD.ioctl(kSD::GET_SECTOR_COUNT,&ulSectorCount) != kSD::OK)
	{
		FF_PRINTF("kSDCardDrive::init: Reading SD Card SECTOR_COUNT failed\n");
		return false;
	}
	if(SD.ioctl(kSD::GET_SECTOR_SIZE,&xParameters.ulSectorSize) != kSD::OK)
	{
		FF_PRINTF("kSDCardDrive::init: Reading SD Card SECTOR_SIZE failed\n");
		return false;
	}

	/* Check the validity of the xIOManagerCacheSize parameter. */
	configASSERT( ( xIOManagerCacheSize % xParameters.ulSectorSize ) == 0 );
	configASSERT( ( xIOManagerCacheSize >= ( 2 * (uint32_t)xParameters.ulSectorSize ) ) );

	/* Attempt to allocated the FF_Disk_t structure. */
	pxDisk = ( FF_Disk_t * ) pvPortMalloc( sizeof( FF_Disk_t ) );

	if( pxDisk != NULL )
	{
		/* Start with every member of the structure set to zero. */
		memset( pxDisk, '\0', sizeof( FF_Disk_t ) );

		/* The signature is used by the disk read and disk write functions to
		ensure the disk being accessed is a RAM disk. */
		pxDisk->ulSignature = sdSIGNATURE;


		/* The pvTag member of the FF_Disk_t structure allows the structure to be
		extended to also include media specific parameters.  The only media
		specific data that needs to be stored in the FF_Disk_t structure for a
		SD disk is the kSD object address */
		pxDisk->pvTag = ( void * )&SD;


		pxDisk->ulNumberOfSectors = ulSectorCount;

		/* Create the IO manager that will be used to control the RAM disk. */
		memset( &xParameters, '\0', sizeof( xParameters ) );
		xParameters.pucCacheMemory = NULL;
		xParameters.ulMemorySize = xIOManagerCacheSize;
		//xParameters.ulSectorSize = ulSectorSize; THIS is already written in ioctl(GET_SECTOR_COUNT,&ulSectorCount)
		xParameters.fnWriteBlocks = kSDCardDrive::write;
		xParameters.fnReadBlocks = kSDCardDrive::read;
		xParameters.pxDisk = pxDisk;

		/* Driver is reentrant so xBlockDeviceIsReentrant can be set to pdTRUE.
		In this case the semaphore is only used to protect FAT data
		structures. */
		xParameters.pvSemaphore = ( void * ) xSemaphoreCreateRecursiveMutex();
		xParameters.xBlockDeviceIsReentrant = pdTRUE;

		pxDisk->pxIOManager = FF_CreateIOManger( &xParameters, &xError );

		if( ( pxDisk->pxIOManager != NULL ) && ( FF_isERR( xError ) == pdFALSE ) )
		{
			/* Record that the RAM disk has been initialised. */
			pxDisk->xStatus.bIsInitialised = pdTRUE;

			/* Create a partition on the RAM disk.  NOTE!  The disk is only
			being partitioned here because it is a new RAM disk.  It is
			known that the disk has not been used before, and cannot already
			contain any partitions.  Most media drivers will not perform
			this step because the media will have already been partitioned. */
			//xError = prvPartitionAndFormatDisk( pxDisk );

			if( FF_isERR( xError ) == pdFALSE )
			{
				/* Record the partition number the FF_Disk_t structure is, then
				mount the partition. */
				pxDisk->xStatus.bPartitionNumber = kFAT::getNewPartitionId();

				/* Mount the partition. */
				xError = FF_Mount( pxDisk, pxDisk->xStatus.bPartitionNumber );
				FF_PRINTF( "kSDCardDrive::init: FF_Mount: FF_Mount: %s\n", ( const char * ) FF_GetErrMessage( xError ) );
			}

			if( FF_isERR( xError ) == pdFALSE )
			{
				/* The partition mounted successfully, add it to the virtual
				file system - where it will appear as a directory off the file
				system's root directory. */
				FF_FS_Add( pcName, pxDisk );
			}
		}
		else
		{
			FF_PRINTF( "kSDCardDrive::init: FF_CreateIOManger: %s\n", ( const char * ) FF_GetErrMessage( xError ) );

			/* The disk structure was allocated, but the disk's IO manager could
			not be allocated, so free the disk again. */
			extern BaseType_t FF_RAMDiskDelete( FF_Disk_t *pxDisk );
			FF_RAMDiskDelete( pxDisk );
			pxDisk = NULL;
		}
	}
	else
	{
		FF_PRINTF( "kSDCardDrive::init: Malloc failed\n" );
	}

	return ((bool)pxDisk);

}

int32_t kSDCardDrive::read( uint8_t *pucDestination, uint32_t ulSectorNumber, uint32_t ulSectorCount, FF_Disk_t *pxDisk )
{
	int32_t lReturn;

	if( pxDisk != NULL )
	{
		if( pxDisk->ulSignature != sdSIGNATURE )
		{
			/* The disk structure is not valid because it doesn't contain a
			magic number written to the disk when it was created. */
			lReturn = FF_ERR_IOMAN_DRIVER_FATAL_ERROR | FF_ERRFLAG;
		}
		else if( pxDisk->xStatus.bIsInitialised == pdFALSE )
		{
			/* The disk has not been initialised. */
			lReturn = FF_ERR_IOMAN_OUT_OF_BOUNDS_READ | FF_ERRFLAG;
		}
		else if( ulSectorNumber >= pxDisk->ulNumberOfSectors )
		{
			/* The start sector is not within the bounds of the disk. */
			lReturn = ( FF_ERR_IOMAN_OUT_OF_BOUNDS_READ | FF_ERRFLAG );
		}
		else if( ( pxDisk->ulNumberOfSectors - ulSectorNumber ) < ulSectorCount )
		{
			/* The end sector is not within the bounds of the disk. */
			lReturn = ( FF_ERR_IOMAN_OUT_OF_BOUNDS_READ | FF_ERRFLAG );
		}
		else
		{
			if(((kSDCard*)(pxDisk->pvTag))->readSector(pucDestination,ulSectorNumber,ulSectorCount) == kSD::OK) lReturn = FF_ERR_NONE;
			else lReturn = FF_ERR_IOMAN_DRIVER_FATAL_ERROR | FF_ERRFLAG;
		}
	}
	else
	{
		lReturn = FF_ERR_NULL_POINTER | FF_ERRFLAG;
	}

	return lReturn;
}
/*-----------------------------------------------------------*/

int32_t kSDCardDrive::write( uint8_t *pucSource, uint32_t ulSectorNumber, uint32_t ulSectorCount, FF_Disk_t *pxDisk )
{
	int32_t lReturn = FF_ERR_NONE;

	if( pxDisk != NULL )
	{
		if( pxDisk->ulSignature != sdSIGNATURE )
		{
			/* The disk structure is not valid because it doesn't contain a
			magic number written to the disk when it was created. */
			lReturn = FF_ERR_IOMAN_DRIVER_FATAL_ERROR | FF_ERRFLAG;
		}
		else if( pxDisk->xStatus.bIsInitialised == pdFALSE )
		{
			/* The disk has not been initialised. */
			lReturn = FF_ERR_IOMAN_OUT_OF_BOUNDS_WRITE | FF_ERRFLAG;
		}
		else if( ulSectorNumber >= pxDisk->ulNumberOfSectors )
		{
			/* The start sector is not within the bounds of the disk. */
			lReturn = ( FF_ERR_IOMAN_OUT_OF_BOUNDS_WRITE | FF_ERRFLAG );
		}
		else if( ( pxDisk->ulNumberOfSectors - ulSectorNumber ) < ulSectorCount )
		{
			/* The end sector is not within the bounds of the disk. */
			lReturn = ( FF_ERR_IOMAN_OUT_OF_BOUNDS_WRITE | FF_ERRFLAG );
		}
		else
		{
			if(((kSDCard*)(pxDisk->pvTag))->writeSector(pucSource,ulSectorNumber,ulSectorCount) == kSD::OK) lReturn = FF_ERR_NONE;
			else lReturn = FF_ERR_IOMAN_DRIVER_FATAL_ERROR | FF_ERRFLAG;
		}
	}
	else
	{
		lReturn = FF_ERR_NULL_POINTER | FF_ERRFLAG;
	}

	return lReturn;
}







