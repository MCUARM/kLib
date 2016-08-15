#ifndef __kFAT_H
#define __kFAT_H

	class kFATVolume;

	#include "kSystem.h"
	#include "ff.h"

	/* Generic command (Used by FatFs) */
	#define CTRL_SYNC			0	/* Complete pending write process (needed at _FS_READONLY == 0) */
	#define GET_SECTOR_COUNT	1	/* Get media size (needed at _USE_MKFS == 1) */
	#define GET_SECTOR_SIZE		2	/* Get sector size (needed at _MAX_SS != _MIN_SS) */
	#define GET_BLOCK_SIZE		3	/* Get erase block size (needed at _USE_MKFS == 1) */
	#define CTRL_TRIM			4	/* Inform device that the data on the block of sectors is no longer used (needed at _USE_TRIM == 1) */




	class kFAT
	{
		public:

			typedef struct {
				FSIZE_t	fsize;			/* File size */
				WORD	fdate;			/* Modified date */
				WORD	ftime;			/* Modified time */
				BYTE	fattrib;		/* File attribute */
			#if _USE_LFN != 0
				TCHAR	altname[13];			/* Altenative file name */
				TCHAR	fname[_MAX_LFN + 1];	/* Primary file name */
			#else
				TCHAR	fname[13];		/* File name */
			#endif
			} FILINFO;

			typedef enum {
				FR_OK = 0,				/* (0) Succeeded */
				FR_DISK_ERR,			/* (1) A hard error occurred in the low level disk I/O layer */
				FR_INT_ERR,				/* (2) Assertion failed */
				FR_NOT_READY,			/* (3) The physical drive cannot work */
				FR_NO_FILE,				/* (4) Could not find the file */
				FR_NO_PATH,				/* (5) Could not find the path */
				FR_INVALID_NAME,		/* (6) The path name format is invalid */
				FR_DENIED,				/* (7) Access denied due to prohibited access or directory full */
				FR_EXIST,				/* (8) Access denied due to prohibited access */
				FR_INVALID_OBJECT,		/* (9) The file/directory object is invalid */
				FR_WRITE_PROTECTED,		/* (10) The physical drive is write protected */
				FR_INVALID_DRIVE,		/* (11) The logical drive number is invalid */
				FR_NOT_ENABLED,			/* (12) The volume has no work area */
				FR_NO_FILESYSTEM,		/* (13) There is no valid FAT volume */
				FR_MKFS_ABORTED,		/* (14) The f_mkfs() aborted due to any parameter error */
				FR_TIMEOUT,				/* (15) Could not get a grant to access the volume within defined period */
				FR_LOCKED,				/* (16) The operation is rejected according to the file sharing policy */
				FR_NOT_ENOUGH_CORE,		/* (17) LFN working buffer could not be allocated */
				FR_TOO_MANY_OPEN_FILES,	/* (18) Number of open files > _FS_LOCK */
				FR_INVALID_PARAMETER	/* (19) Given parameter is invalid */
			} FRESULT;


			/* Status of Disk Functions */
			typedef BYTE	DSTATUS;

			/* Results of Disk Functions */
			typedef enum {
				RES_OK = 0,		/* 0: Successful */
				RES_ERROR,		/* 1: R/W Error */
				RES_WRPRT,		/* 2: Write Protected */
				RES_NOTRDY,		/* 3: Not Ready */
				RES_PARERR		/* 4: Invalid Parameter */
			} DRESULT;



	};

	class kFATVolume
	{
		friend class kDir;
		friend class kFile;

		protected:

			FATFS prvFAT;

			friend FRESULT find_volume (	/* FR_OK(0): successful, !=0: any error occurred */
				const TCHAR** path,	/* Pointer to pointer to the path name (drive number) */
				kFATVolume** rk_vol,		/* Pointer to pointer to the found file system object */
				BYTE mode			/* !=0: Check write protection for write access */
			);
			friend FRESULT sync_window (	/* Returns FR_OK or FR_DISK_ERROR */
				kFATVolume* k_vol			/* File system object */
			);
			friend FRESULT move_window (	/* Returns FR_OK or FR_DISK_ERROR */
				kFATVolume* k_vol,			/* File system object */
				DWORD sector		/* Sector number to make appearance in the fs->win[] */
			);
			friend FRESULT sync_fs (	/* FR_OK:succeeded, !=0:error */
				kFATVolume* k_vol		/* File system object */
			);
			friend DWORD get_fat (	/* 0xFFFFFFFF:Disk error, 1:Internal error, 2..0x7FFFFFFF:Cluster status */
				_FDID* obj,	/* Corresponding object */
				DWORD clst	/* Cluster number to get the value */
			);
			friend FRESULT put_fat (	/* FR_OK(0):succeeded, !=0:error */
				kFATVolume* k_vol,		/* Corresponding object */
				DWORD clst,		/* FAT index number (cluster number) to be changed */
				DWORD val		/* New value to be set to the entry */
			);
			friend FRESULT remove_chain (	/* FR_OK(0):succeeded, !=0:error */
				_FDID* obj,			/* Corresponding object */
				DWORD clst,			/* Cluster to remove a chain from */
				DWORD pclst			/* Previous cluster of clst (0:an entire chain) */
			);
			friend DWORD clust2sect (	/* !=0:Sector number, 0:Failed (invalid cluster#) */
				kFATVolume*k_vol,		/* File system object */
				DWORD clst		/* Cluster# to be converted */
			);
			friend DWORD create_chain (	/* 0:No free cluster, 1:Internal error, 0xFFFFFFFF:Disk error, >=2:New cluster# */
				_FDID* obj,			/* Corresponding object */
				DWORD clst			/* Cluster# to stretch, 0:Create a new chain */
			);
			DWORD clmt_clust (	/* <2:Error, >=2:Cluster number */
				FIL* fp,		/* Pointer to the file object */
				DWORD ofs		/* File offset to be converted to cluster# */
			);
			friend FRESULT dir_sdi (	/* FR_OK(0):succeeded, !=0:error */
				DIR* dp,		/* Pointer to directory object */
				DWORD ofs		/* Offset of directory table */
			);
			friend FRESULT dir_next (	/* FR_OK(0):succeeded, FR_NO_FILE:End of table, FR_DENIED:Could not stretch */
				DIR* dp,		/* Pointer to the directory object */
				int stretch		/* 0: Do not stretch table, 1: Stretch table if needed */
			);
			friend FRESULT dir_alloc (	/* FR_OK(0):succeeded, !=0:error */
				DIR* dp,		/* Pointer to the directory object */
				UINT nent		/* Number of contiguous entries to allocate */
			);
			friend DWORD ld_clust (	/* Returns the top cluster value of the SFN entry */
				kFATVolume*k_vol,		/* Pointer to the fs object */
				const BYTE* dir	/* Pointer to the key entry */
			);
			void st_clust (
				kFATVolume*k_vol,	/* Pointer to the fs object */
				BYTE* dir,	/* Pointer to the key entry */
				DWORD cl	/* Value to be set */
			);
			friend FRESULT dir_read (
				DIR* dp,		/* Pointer to the directory object */
				int vol			/* Filtered by 0:file/directory or 1:volume label */
			);
			friend FRESULT dir_find (	/* FR_OK(0):succeeded, !=0:error */
				DIR* dp			/* Pointer to the directory object with the file name */
			);
			friend FRESULT dir_register (	/* FR_OK:succeeded, FR_DENIED:no free entry or too many SFN collision, FR_DISK_ERR:disk error */
				DIR* dp				/* Target directory with object name to be created */
			);
			friend FRESULT dir_remove (	/* FR_OK:Succeeded, FR_DISK_ERR:A disk error */
				DIR* dp				/* Directory object pointing the entry to be removed */
			);
			friend FRESULT follow_path (	/* FR_OK(0): successful, !=0: error code */
				DIR* dp,			/* Directory object to return last directory and found object */
				const TCHAR* path	/* Full-path string to find a file or directory */
			);
			friend BYTE check_fs (	/* 0:FAT, 1:exFAT, 2:Valid BS but not FAT, 3:Not a BS, 4:Disk error */
				kFATVolume*k_vol,	/* File system object */
				DWORD sect	/* Sector# (lba) to check if it is an FAT boot record or not */
			);
			friend FRESULT validate (	/* Returns FR_OK or FR_INVALID_OBJECT */
				void* dfp,		/* Pointer to the FIL/DIR object to check validity */
				kFATVolume** rk_vol		/* Pointer to pointer to the owner file system object to return */
			);
			friend void st_clust (
				kFATVolume*k_vol,	/* Pointer to the fs object */
				BYTE* dir,	/* Pointer to the key entry */
				DWORD cl	/* Value to be set */
			);
		public:

			kFAT::FRESULT mount(const char * path);
			kFAT::FRESULT format(
					BYTE sfd,			/* Partitioning rule 0:FDISK, 1:SFD */
					UINT au				/* Size of allocation unit in unit of byte or sector */
				);

			virtual kFAT::DSTATUS init(void);
			virtual kFAT::DSTATUS status(void);
			virtual kFAT::DRESULT read(unsigned char * buff, unsigned long sector, unsigned int count);
			virtual kFAT::DRESULT write(const unsigned char* buff, unsigned long sector, unsigned int count);
			virtual kFAT::DRESULT ioctl(unsigned char cmd, void* buff);

	};

	class kDir
	{
		protected:

			DIR prvDir;

		public:

			kFAT::FRESULT open(const char * path);
			kFAT::FRESULT close(void);
			kFAT::FRESULT read(kFAT::FILINFO * fno);
			kFAT::FRESULT findFirst(kFAT::FILINFO * fno, const char * path, const char * pattern);
			kFAT::FRESULT findNext(kFAT::FILINFO * fno);

	};

	class kFile
	{
		protected:

			FIL prvFile;

		public:

			kFAT::FRESULT open(const char * path, BYTE mode);
			kFAT::FRESULT close(void);
			kFAT::FRESULT read(void* buff,UINT btr, UINT * br);
			kFAT::FRESULT write(const void* buff, UINT btw, UINT * bw);
			kFAT::FRESULT lseek(FSIZE_t ofs);
			kFAT::FRESULT sync(void);

	};

#endif
