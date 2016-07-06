#ifndef __kRecorder_H
#define __kRecorder_H

	#include "kSPIDevice.h"







	class kRecorder : public kSPIDevice
	{
		private:


			/* These types MUST be 16-bit or 32-bit */
			typedef int				INT;
			typedef unsigned int	UINT;

			/* This type MUST be 8-bit */
			typedef unsigned char	BYTE;

			/* These types MUST be 16-bit */
			typedef short			SHORT;
			typedef unsigned short	WORD;
			typedef unsigned short	WCHAR;

			/* These types MUST be 32-bit */
			typedef long			LONG;
			typedef unsigned long	DWORD;

			/* This type MUST be 64-bit (Remove this for C89 compatibility) */
			typedef unsigned long long QWORD;



		//configuration

			#define _FFCONF 88100	/* Revision ID */

			/*---------------------------------------------------------------------------/
			/ Function Configurations
			/---------------------------------------------------------------------------*/

			#define _FS_READONLY	0
			/* This option switches read-only configuration. (0:Read/Write or 1:Read-only)
			/  Read-only configuration removes writing API functions, f_write(), f_sync(),
			/  f_unlink(), f_mkdir(), f_chmod(), f_rename(), f_truncate(), f_getfree()
			/  and optional writing functions as well. */


			#define _FS_MINIMIZE	0
			/* This option defines minimization level to remove some basic API functions.
			/
			/   0: All basic functions are enabled.
			/   1: f_stat(), f_getfree(), f_unlink(), f_mkdir(), f_truncate() and f_rename()
			/      are removed.
			/   2: f_opendir(), f_readdir() and f_closedir() are removed in addition to 1.
			/   3: f_lseek() function is removed in addition to 2. */


			#define	_USE_STRFUNC	0
			/* This option switches string functions, f_gets(), f_putc(), f_puts() and
			/  f_printf().
			/
			/  0: Disable string functions.
			/  1: Enable without LF-CRLF conversion.
			/  2: Enable with LF-CRLF conversion. */


			#define _USE_FIND		0
			/* This option switches filtered directory read functions, f_findfirst() and
			/  f_findnext(). (0:Disable, 1:Enable 2:Enable with matching altname[] too) */


			#define	_USE_MKFS		0
			/* This option switches f_mkfs() function. (0:Disable or 1:Enable) */


			#define	_USE_FASTSEEK	0
			/* This option switches fast seek function. (0:Disable or 1:Enable) */


			#define	_USE_EXPAND		0
			/* This option switches f_expand function. (0:Disable or 1:Enable) */


			#define _USE_CHMOD		0
			/* This option switches attribute manipulation functions, f_chmod() and f_utime().
			/  (0:Disable or 1:Enable) Also _FS_READONLY needs to be 0 to enable this option. */


			#define _USE_LABEL		0
			/* This option switches volume label functions, f_getlabel() and f_setlabel().
			/  (0:Disable or 1:Enable) */


			#define	_USE_FORWARD	0
			/* This option switches f_forward() function. (0:Disable or 1:Enable)
			/  To enable it, also _FS_TINY need to be 1. */


			/*---------------------------------------------------------------------------/
			/ Locale and Namespace Configurations
			/---------------------------------------------------------------------------*/

			#define _CODE_PAGE	932
			/* This option specifies the OEM code page to be used on the target system.
			/  Incorrect setting of the code page can cause a file open failure.
			/
			/   1   - ASCII (No extended character. Non-LFN cfg. only)
			/   437 - U.S.
			/   720 - Arabic
			/   737 - Greek
			/   771 - KBL
			/   775 - Baltic
			/   850 - Latin 1
			/   852 - Latin 2
			/   855 - Cyrillic
			/   857 - Turkish
			/   860 - Portuguese
			/   861 - Icelandic
			/   862 - Hebrew
			/   863 - Canadian French
			/   864 - Arabic
			/   865 - Nordic
			/   866 - Russian
			/   869 - Greek 2
			/   932 - Japanese (DBCS)
			/   936 - Simplified Chinese (DBCS)
			/   949 - Korean (DBCS)
			/   950 - Traditional Chinese (DBCS)
			*/


			#define	_USE_LFN	0
			#define	_MAX_LFN	255
			/* The _USE_LFN switches the support of long file name (LFN).
			/
			/   0: Disable support of LFN. _MAX_LFN has no effect.
			/   1: Enable LFN with static working buffer on the BSS. Always NOT thread-safe.
			/   2: Enable LFN with dynamic working buffer on the STACK.
			/   3: Enable LFN with dynamic working buffer on the HEAP.
			/
			/  To enable the LFN, Unicode handling functions (option/unicode.c) must be added
			/  to the project. The working buffer occupies (_MAX_LFN + 1) * 2 bytes and
			/  additional 608 bytes at exFAT enabled. _MAX_LFN can be in range from 12 to 255.
			/  It should be set 255 to support full featured LFN operations.
			/  When use stack for the working buffer, take care on stack overflow. When use heap
			/  memory for the working buffer, memory management functions, ff_memalloc() and
			/  ff_memfree(), must be added to the project. */


			#define	_LFN_UNICODE	0
			/* This option switches character encoding on the API. (0:ANSI/OEM or 1:Unicode)
			/  To use Unicode string for the path name, enable LFN and set _LFN_UNICODE = 1.
			/  This option also affects behavior of string I/O functions. */


			#define _STRF_ENCODE	3
			/* When _LFN_UNICODE == 1, this option selects the character encoding on the file to
			/  be read/written via string I/O functions, f_gets(), f_putc(), f_puts and f_printf().
			/
			/  0: ANSI/OEM
			/  1: UTF-16LE
			/  2: UTF-16BE
			/  3: UTF-8
			/
			/  This option has no effect when _LFN_UNICODE == 0. */


			#define _FS_RPATH	0
			/* This option configures support of relative path.
			/
			/   0: Disable relative path and remove related functions.
			/   1: Enable relative path. f_chdir() and f_chdrive() are available.
			/   2: f_getcwd() function is available in addition to 1.
			*/


			/*---------------------------------------------------------------------------/
			/ Drive/Volume Configurations
			/---------------------------------------------------------------------------*/

			#define _VOLUMES	1
			/* Number of volumes (logical drives) to be used. */


			#define _STR_VOLUME_ID	0
			#define _VOLUME_STRS	"RAM","NAND","CF","SD1","SD2","USB1","USB2","USB3"
			/* _STR_VOLUME_ID switches string support of volume ID.
			/  When _STR_VOLUME_ID is set to 1, also pre-defined strings can be used as drive
			/  number in the path name. _VOLUME_STRS defines the drive ID strings for each
			/  logical drives. Number of items must be equal to _VOLUMES. Valid characters for
			/  the drive ID strings are: A-Z and 0-9. */


			#define	_MULTI_PARTITION	0
			/* This option switches support of multi-partition on a physical drive.
			/  By default (0), each logical drive number is bound to the same physical drive
			/  number and only an FAT volume found on the physical drive will be mounted.
			/  When multi-partition is enabled (1), each logical drive number can be bound to
			/  arbitrary physical drive and partition listed in the VolToPart[]. Also f_fdisk()
			/  funciton will be available. */


			#define	_MIN_SS		512
			#define	_MAX_SS		512
			/* These options configure the range of sector size to be supported. (512, 1024,
			/  2048 or 4096) Always set both 512 for most systems, all type of memory cards and
			/  harddisk. But a larger value may be required for on-board flash memory and some
			/  type of optical media. When _MAX_SS is larger than _MIN_SS, FatFs is configured
			/  to variable sector size and GET_SECTOR_SIZE command must be implemented to the
			/  disk_ioctl() function. */


			#define	_USE_TRIM	0
			/* This option switches support of ATA-TRIM. (0:Disable or 1:Enable)
			/  To enable Trim function, also CTRL_TRIM command should be implemented to the
			/  disk_ioctl() function. */


			#define _FS_NOFSINFO	0
			/* If you need to know correct free space on the FAT32 volume, set bit 0 of this
			/  option, and f_getfree() function at first time after volume mount will force
			/  a full FAT scan. Bit 1 controls the use of last allocated cluster number.
			/
			/  bit0=0: Use free cluster count in the FSINFO if available.
			/  bit0=1: Do not trust free cluster count in the FSINFO.
			/  bit1=0: Use last allocated cluster number in the FSINFO if available.
			/  bit1=1: Do not trust last allocated cluster number in the FSINFO.
			*/



			/*---------------------------------------------------------------------------/
			/ System Configurations
			/---------------------------------------------------------------------------*/

			#define	_FS_TINY	0
			/* This option switches tiny buffer configuration. (0:Normal or 1:Tiny)
			/  At the tiny configuration, size of the file object (FIL) is reduced _MAX_SS bytes.
			/  Instead of private sector buffer eliminated from the file object, common sector
			/  buffer in the file system object (FATFS) is used for the file data transfer. */


			#define _FS_EXFAT	0
			/* This option switches support of exFAT file system in addition to the traditional
			/  FAT file system. (0:Disable or 1:Enable) To enable exFAT, also LFN must be enabled.
			/  Note that enabling exFAT discards C89 compatibility. */


			#define _FS_NORTC	0
			#define _NORTC_MON	3
			#define _NORTC_MDAY	1
			#define _NORTC_YEAR	2016
			/* The option _FS_NORTC switches timestamp functiton. If the system does not have
			/  any RTC function or valid timestamp is not needed, set _FS_NORTC = 1 to disable
			/  the timestamp function. All objects modified by FatFs will have a fixed timestamp
			/  defined by _NORTC_MON, _NORTC_MDAY and _NORTC_YEAR in local time.
			/  To enable timestamp function (_FS_NORTC = 0), get_fattime() function need to be
			/  added to the project to get current time form real-time clock. _NORTC_MON,
			/  _NORTC_MDAY and _NORTC_YEAR have no effect.
			/  These options have no effect at read-only configuration (_FS_READONLY = 1). */


			#define	_FS_LOCK	0
			/* The option _FS_LOCK switches file lock function to control duplicated file open
			/  and illegal operation to open objects. This option must be 0 when _FS_READONLY
			/  is 1.
			/
			/  0:  Disable file lock function. To avoid volume corruption, application program
			/      should avoid illegal open, remove and rename to the open objects.
			/  >0: Enable file lock function. The value defines how many files/sub-directories
			/      can be opened simultaneously under file lock control. Note that the file
			/      lock control is independent of re-entrancy. */


			#define _FS_REENTRANT	0
			#define _FS_TIMEOUT		1000
			#define	_SYNC_t			HANDLE
			/* The option _FS_REENTRANT switches the re-entrancy (thread safe) of the FatFs
			/  module itself. Note that regardless of this option, file access to different
			/  volume is always re-entrant and volume control functions, f_mount(), f_mkfs()
			/  and f_fdisk() function, are always not re-entrant. Only file/directory access
			/  to the same volume is under control of this function.
			/
			/   0: Disable re-entrancy. _FS_TIMEOUT and _SYNC_t have no effect.
			/   1: Enable re-entrancy. Also user provided synchronization handlers,
			/      ff_req_grant(), ff_rel_grant(), ff_del_syncobj() and ff_cre_syncobj()
			/      function, must be added to the project. Samples are available in
			/      option/syscall.c.
			/
			/  The _FS_TIMEOUT defines timeout period in unit of time tick.
			/  The _SYNC_t defines O/S dependent sync object type. e.g. HANDLE, ID, OS_EVENT*,
			/  SemaphoreHandle_t and etc.. A header file for O/S definitions needs to be
			/  included somewhere in the scope of ff.c. */


			/*--- End of configuration options ---*/







		#include "ffconf.h"		/* FatFs configuration options */


			#ifndef _FATFS
			#define _FATFS	88100	/* Revision ID */
			#endif


			#if _FATFS != _FFCONF
			#error Wrong configuration file (ffconf.h).
			#endif




			/* Definitions of volume management */

			#if _MULTI_PARTITION		/* Multiple partition configuration */
			typedef struct {
				BYTE pd;	/* Physical drive number */
				BYTE pt;	/* Partition: 0:Auto detect, 1-4:Forced partition) */
			} PARTITION;
			extern PARTITION VolToPart[];	/* Volume - Partition resolution table */
			#define LD2PD(vol) (VolToPart[vol].pd)	/* Get physical drive number */
			#define LD2PT(vol) (VolToPart[vol].pt)	/* Get partition index */

			#else							/* Single partition configuration */
			#define LD2PD(vol) (BYTE)(vol)	/* Each logical drive is bound to the same physical drive number */
			#define LD2PT(vol) 0			/* Find first valid partition or in SFD */

			#endif



			/* Type of path name strings on FatFs API */

			#if _LFN_UNICODE			/* Unicode string */
			#if _USE_LFN == 0
			#error _LFN_UNICODE must be 0 at non-LFN cfg.
			#endif
			#ifndef _INC_TCHAR
			typedef WCHAR TCHAR;
			#define _T(x) L ## x
			#define _TEXT(x) L ## x
			#endif

			#else						/* ANSI/OEM string */
			#ifndef _INC_TCHAR
			typedef char TCHAR;
			#define _T(x) x
			#define _TEXT(x) x
			#endif

			#endif



			/* File system object structure (FATFS) */

			typedef struct {
				BYTE	fs_type;		/* File system type (0:N/A) */
				BYTE	drv;			/* Physical drive number */
				BYTE	n_fats;			/* Number of FATs (1 or 2) */
				BYTE	wflag;			/* win[] flag (b0:dirty) */
				BYTE	fsi_flag;		/* FSINFO flags (b7:disabled, b0:dirty) */
				WORD	id;				/* File system mount ID */
				WORD	n_rootdir;		/* Number of root directory entries (FAT12/16) */
				WORD	csize;			/* Cluster size [sectors] */
			#if _MAX_SS != _MIN_SS
				WORD	ssize;			/* Sector size (512, 1024, 2048 or 4096) */
			#endif
			#if _FS_EXFAT
				BYTE*	dirbuf;			/* Directory entry block scratchpad buffer */
			#endif
			#if _FS_REENTRANT
				_SYNC_t	sobj;			/* Identifier of sync object */
			#endif
			#if !_FS_READONLY
				DWORD	last_clst;		/* Last allocated cluster */
				DWORD	free_clst;		/* Number of free clusters */
			#endif
			#if _FS_RPATH != 0
				DWORD	cdir;			/* Current directory start cluster (0:root) */
			#if _FS_EXFAT
				DWORD	cdc_scl;		/* Containing directory start cluster (invalid when cdir is 0) */
				DWORD	cdc_size;		/* b31-b8:Size of containing directory, b7-b0: Chain status */
				DWORD	cdc_ofs;		/* Offset in the containing directory (invalid when cdir is 0) */
			#endif
			#endif
				DWORD	n_fatent;		/* Number of FAT entries (number of clusters + 2) */
				DWORD	fsize;			/* Size of an FAT [sectors] */
				DWORD	volbase;		/* Volume base sector */
				DWORD	fatbase;		/* FAT base sector */
				DWORD	dirbase;		/* Root directory base sector/cluster */
				DWORD	database;		/* Data base sector */
				DWORD	winsect;		/* Current sector appearing in the win[] */
				BYTE	win[_MAX_SS];	/* Disk access window for Directory, FAT (and file data at tiny cfg) */
			} FATFS;



			/* Type of file size variables and object identifier */

			#if _FS_EXFAT
			#if _USE_LFN == 0
			#error LFN must be enabled when enable exFAT
			#endif
			typedef QWORD FSIZE_t;
			#else
			typedef DWORD FSIZE_t;
			#endif



			/* Object ID and allocation information (_FDID) */

			typedef struct {
				FATFS*	fs;			/* Pointer to the owner file system object */
				WORD	id;			/* Owner file system mount ID */
				BYTE	attr;		/* Object attribute */
				BYTE	stat;		/* Object chain status (b1-0: =0:not contiguous, =2:contiguous (no data on FAT), =3:got flagmented, b2:sub-directory stretched) */
				DWORD	sclust;		/* Object start cluster (0:no cluster or root directory) */
				FSIZE_t	objsize;	/* Object size (valid when sclust != 0) */
			#if _FS_EXFAT
				DWORD	n_cont;		/* Size of coutiguous part, clusters - 1 (valid when stat == 3) */
				DWORD	c_scl;		/* Containing directory start cluster (valid when sclust != 0) */
				DWORD	c_size;		/* b31-b8:Size of containing directory, b7-b0: Chain status (valid when c_scl != 0) */
				DWORD	c_ofs;		/* Offset in the containing directory (valid when sclust != 0) */
			#endif
			#if _FS_LOCK != 0
				UINT	lockid;		/* File lock ID origin from 1 (index of file semaphore table Files[]) */
			#endif
			} _FDID;



			/* File object structure (FIL) */

			typedef struct {
				_FDID	obj;			/* Object identifier */
				BYTE	flag;			/* File status flags */
				BYTE	err;			/* Abort flag (error code) */
				FSIZE_t	fptr;			/* File read/write pointer (Zeroed on file open) */
				DWORD	clust;			/* Current cluster of fpter (not valid when fprt is 0) */
				DWORD	sect;			/* Sector number appearing in buf[] (0:invalid) */
			#if !_FS_READONLY
				DWORD	dir_sect;		/* Sector number containing the directory entry */
				BYTE*	dir_ptr;		/* Pointer to the directory entry in the win[] */
			#endif
			#if _USE_FASTSEEK
				DWORD*	cltbl;			/* Pointer to the cluster link map table (Nulled on file open) */
			#endif
			#if !_FS_TINY
				BYTE	buf[_MAX_SS];	/* File private data read/write window */
			#endif
			} FIL;



			/* Directory object structure (DIR) */

			typedef struct {
				_FDID	obj;			/* Object identifier */
				DWORD	dptr;			/* Current read/write offset */
				DWORD	clust;			/* Current cluster */
				DWORD	sect;			/* Current sector */
				BYTE*	dir;			/* Pointer to the directory item in the win[] */
				BYTE*	fn;				/* Pointer to the SFN (in/out) {body[8],ext[3],status[1]} */
			#if _USE_LFN != 0
				DWORD	blk_ofs;		/* Offset of current entry block being processed (0xFFFFFFFF:Invalid) */
				WCHAR*	lfn;			/* Pointer to the LFN working buffer */
			#endif
			#if _USE_FIND
				const TCHAR* pat;		/* Pointer to the name matching pattern */
			#endif
			} DIR;



			/* File information structure (FILINFO) */

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



			/* File function return code (FRESULT) */

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




			/*--------------------------------------------------------------*/
			/* Flags and offset address                                     */


			/* File access control and file status flags (FIL.flag) */

			#define	FA_READ				0x01
			#define	FA_WRITE			0x02
			#define	FA_OPEN_EXISTING	0x00
			#define	FA_CREATE_NEW		0x04
			#define	FA_CREATE_ALWAYS	0x08
			#define	FA_OPEN_ALWAYS		0x10
			#define _FA_MODIFIED		0x20
			#define _FA_DIRTY			0x40


			/* FAT sub type (FATFS.fs_type) */

			#define FS_FAT12	1
			#define FS_FAT16	2
			#define FS_FAT32	3
			#define FS_EXFAT	4


			/* File attribute bits for directory entry */

			#define	AM_RDO	0x01	/* Read only */
			#define	AM_HID	0x02	/* Hidden */
			#define	AM_SYS	0x04	/* System */
			#define	AM_VOL	0x08	/* Volume label */
			#define AM_LFN	0x0F	/* LFN entry */
			#define AM_DIR	0x10	/* Directory */
			#define AM_ARC	0x20	/* Archive */
			#define AM_MASK	0x3F	/* Mask of defined bits */


			/* Fast seek controls */
			#define CREATE_LINKMAP	((FSIZE_t)0 - 1)


			/*--------------------------------------------------------------*/
			/* FatFs module application interface                           */

			FRESULT f_open (FIL* fp, const TCHAR* path, BYTE mode);				/* Open or create a file */
			FRESULT f_close (FIL* fp);											/* Close an open file object */
			FRESULT f_read (FIL* fp, void* buff, UINT btr, UINT* br);			/* Read data from a file */
			FRESULT f_write (FIL* fp, const void* buff, UINT btw, UINT* bw);	/* Write data to a file */
			FRESULT f_lseek (FIL* fp, FSIZE_t ofs);								/* Move file pointer of a file object */
			FRESULT f_truncate (FIL* fp);										/* Truncate file */
			FRESULT f_sync (FIL* fp);											/* Flush cached data of a writing file */
			FRESULT f_opendir (DIR* dp, const TCHAR* path);						/* Open a directory */
			FRESULT f_closedir (DIR* dp);										/* Close an open directory */
			FRESULT f_readdir (DIR* dp, FILINFO* fno);							/* Read a directory item */
			FRESULT f_findfirst (DIR* dp, FILINFO* fno, const TCHAR* path, const TCHAR* pattern);	/* Find first file */
			FRESULT f_findnext (DIR* dp, FILINFO* fno);							/* Find next file */
			FRESULT f_mkdir (const TCHAR* path);								/* Create a sub directory */
			FRESULT f_unlink (const TCHAR* path);								/* Delete an existing file or directory */
			FRESULT f_rename (const TCHAR* path_old, const TCHAR* path_new);	/* Rename/Move a file or directory */
			FRESULT f_stat (const TCHAR* path, FILINFO* fno);					/* Get file status */
			FRESULT f_chmod (const TCHAR* path, BYTE attr, BYTE mask);			/* Change attribute of the file/dir */
			FRESULT f_utime (const TCHAR* path, const FILINFO* fno);			/* Change timestamp of the file/dir */
			FRESULT f_chdir (const TCHAR* path);								/* Change current directory */
			FRESULT f_chdrive (const TCHAR* path);								/* Change current drive */
			FRESULT f_getcwd (TCHAR* buff, UINT len);							/* Get current directory */
			FRESULT f_getfree (const TCHAR* path, DWORD* nclst, FATFS** fatfs);	/* Get number of free clusters on the drive */
			FRESULT f_getlabel (const TCHAR* path, TCHAR* label, DWORD* vsn);	/* Get volume label */
			FRESULT f_setlabel (const TCHAR* label);							/* Set volume label */
			FRESULT f_forward (FIL* fp, UINT(*func)(const BYTE*,UINT), UINT btf, UINT* bf);	/* Forward data to the stream */
			FRESULT f_expand (FIL* fp, FSIZE_t szf, BYTE opt);					/* Allocate a contiguous block to the file */
			FRESULT f_mount (FATFS* fs, const TCHAR* path, BYTE opt);			/* Mount/Unmount a logical drive */
			FRESULT f_mkfs (const TCHAR* path, BYTE sfd, UINT au);				/* Create a file system on the volume */
			FRESULT f_fdisk (BYTE pdrv, const DWORD szt[], void* work);			/* Divide a physical drive into some partitions */
			int f_putc (TCHAR c, FIL* fp);										/* Put a character to the file */
			int f_puts (const TCHAR* str, FIL* cp);								/* Put a string to the file */
			int f_printf (FIL* fp, const TCHAR* str, ...);						/* Put a formatted string to the file */
			TCHAR* f_gets (TCHAR* buff, int len, FIL* fp);						/* Get a string from the file */

			#define f_eof(fp) ((int)((fp)->fptr == (fp)->obj.objsize))
			#define f_error(fp) ((fp)->err)
			#define f_tell(fp) ((fp)->fptr)
			#define f_size(fp) ((fp)->obj.objsize)
			#define f_rewind(fp) f_lseek((fp), 0)
			#define f_rewinddir(dp) f_readdir((dp), 0)

			#ifndef EOF
			#define EOF (-1)
			#endif


			/*--------------------------------------------------------------*/
			/* Additional user defined functions                            */

			/* RTC function */
			#if !_FS_READONLY && !_FS_NORTC
			DWORD get_fattime (void);
			#endif

			/* Unicode support functions */
			#if _USE_LFN != 0						/* Unicode - OEM code conversion */
			WCHAR ff_convert (WCHAR chr, UINT dir);	/* OEM-Unicode bidirectional conversion */
			WCHAR ff_wtoupper (WCHAR chr);			/* Unicode upper-case conversion */
			#if _USE_LFN == 3						/* Memory functions */
			void* ff_memalloc (UINT msize);			/* Allocate memory block */
			void ff_memfree (void* mblock);			/* Free memory block */
			#endif
			#endif

			/* Sync functions */
			#if _FS_REENTRANT
			int ff_cre_syncobj (BYTE vol, _SYNC_t* sobj);	/* Create a sync object */
			int ff_req_grant (_SYNC_t sobj);				/* Lock sync object */
			void ff_rel_grant (_SYNC_t sobj);				/* Unlock sync object */
			int ff_del_syncobj (_SYNC_t sobj);				/* Delete a sync object */
			#endif


		// low level functions

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


			/*---------------------------------------*/
			/* Prototypes for disk control functions */


			DSTATUS disk_initialize (BYTE pdrv);
			DSTATUS disk_status (BYTE pdrv);
			DRESULT disk_read (BYTE pdrv, BYTE* buff, DWORD sector, UINT count);
			DRESULT disk_write (BYTE pdrv, const BYTE* buff, DWORD sector, UINT count);
			DRESULT disk_ioctl (BYTE pdrv, BYTE cmd, void* buff);


			/* Disk Status Bits (DSTATUS) */

			#define STA_NOINIT		0x01	/* Drive not initialized */
			#define STA_NODISK		0x02	/* No medium in the drive */
			#define STA_PROTECT		0x04	/* Write protected */


			/* Command code for disk_ioctrl fucntion */

			/* Generic command (Used by FatFs) */
			#define CTRL_SYNC			0	/* Complete pending write process (needed at _FS_READONLY == 0) */
			#define GET_SECTOR_COUNT	1	/* Get media size (needed at _USE_MKFS == 1) */
			#define GET_SECTOR_SIZE		2	/* Get sector size (needed at _MAX_SS != _MIN_SS) */
			#define GET_BLOCK_SIZE		3	/* Get erase block size (needed at _USE_MKFS == 1) */
			#define CTRL_TRIM			4	/* Inform device that the data on the block of sectors is no longer used (needed at _USE_TRIM == 1) */

			/* Generic command (Not used by FatFs) */
			#define CTRL_POWER			5	/* Get/Set power status */
			#define CTRL_LOCK			6	/* Lock/Unlock media removal */
			#define CTRL_EJECT			7	/* Eject media */
			#define CTRL_FORMAT			8	/* Create physical format on the media */

			/* MMC/SDC specific ioctl command */
			#define MMC_GET_TYPE		10	/* Get card type */
			#define MMC_GET_CSD			11	/* Get CSD */
			#define MMC_GET_CID			12	/* Get CID */
			#define MMC_GET_OCR			13	/* Get OCR */
			#define MMC_GET_SDSTAT		14	/* Get SD status */
			#define ISDIO_READ			55	/* Read data form SD iSDIO register */
			#define ISDIO_WRITE			56	/* Write data to SD iSDIO register */
			#define ISDIO_MRITE			57	/* Masked write data to SD iSDIO register */

			/* ATA/CF specific ioctl command */
			#define ATA_GET_REV			20	/* Get F/W revision */
			#define ATA_GET_MODEL		21	/* Get model name */
			#define ATA_GET_SN			22	/* Get serial number */



			FATFS *FatFs[_VOLUMES];	/* Pointer to the file system objects (logical drives) */
			WORD Fsid;				/* File system mount ID */


			/* Reentrancy related */
			#if _FS_REENTRANT
			#if _USE_LFN == 1
			#error Static LFN work area cannot be used at thread-safe configuration
			#endif
			#define	ENTER_FF(fs)		{ if (!lock_fs(fs)) return FR_TIMEOUT; }
			#define	LEAVE_FF(fs, res)	{ unlock_fs(fs, res); return res; }
			#else
			#define	ENTER_FF(fs)
			#define LEAVE_FF(fs, res)	return res
			#endif

			#define	ABORT(fs, res)		{ fp->err = (BYTE)(res); LEAVE_FF(fs, res); }


			/* Definitions of sector size */
			#if (_MAX_SS < _MIN_SS) || (_MAX_SS != 512 && _MAX_SS != 1024 && _MAX_SS != 2048 && _MAX_SS != 4096) || (_MIN_SS != 512 && _MIN_SS != 1024 && _MIN_SS != 2048 && _MIN_SS != 4096)
			#error Wrong sector size configuration
			#endif
			#if _MAX_SS == _MIN_SS
			#define	SS(fs)	((UINT)_MAX_SS)	/* Fixed sector size */
			#else
			#define	SS(fs)	((fs)->ssize)	/* Variable sector size */
			#endif


			/* Timestamp */
			#if _FS_NORTC == 1
			#if _NORTC_YEAR < 1980 || _NORTC_YEAR > 2107 || _NORTC_MON < 1 || _NORTC_MON > 12 || _NORTC_MDAY < 1 || _NORTC_MDAY > 31
			#error Invalid _FS_NORTC settings
			#endif
			#define GET_FATTIME()	((DWORD)(_NORTC_YEAR - 1980) << 25 | (DWORD)_NORTC_MON << 21 | (DWORD)_NORTC_MDAY << 16)
			#else
			#define GET_FATTIME()	get_fattime()
			#endif


			/* File lock controls */
			#if _FS_LOCK != 0
			#if _FS_READONLY
			#error _FS_LOCK must be 0 at read-only configuration
			#endif
			typedef struct {
				FATFS *fs;		/* Object ID 1, volume (NULL:blank entry) */
				DWORD clu;		/* Object ID 2, directory (0:root) */
				DWORD ofs;		/* Object ID 3, directory offset */
				WORD ctr;		/* Object open counter, 0:none, 0x01..0xFF:read mode open count, 0x100:write mode */
			} FILESEM;
			#endif



			/* DBCS code ranges and SBCS upper conversion tables */

			#if _CODE_PAGE == 932	/* Japanese Shift-JIS */
			#define _DF1S	0x81	/* DBC 1st byte range 1 start */
			#define _DF1E	0x9F	/* DBC 1st byte range 1 end */
			#define _DF2S	0xE0	/* DBC 1st byte range 2 start */
			#define _DF2E	0xFC	/* DBC 1st byte range 2 end */
			#define _DS1S	0x40	/* DBC 2nd byte range 1 start */
			#define _DS1E	0x7E	/* DBC 2nd byte range 1 end */
			#define _DS2S	0x80	/* DBC 2nd byte range 2 start */
			#define _DS2E	0xFC	/* DBC 2nd byte range 2 end */

			#elif _CODE_PAGE == 936	/* Simplified Chinese GBK */
			#define _DF1S	0x81
			#define _DF1E	0xFE
			#define _DS1S	0x40
			#define _DS1E	0x7E
			#define _DS2S	0x80
			#define _DS2E	0xFE

			#elif _CODE_PAGE == 949	/* Korean */
			#define _DF1S	0x81
			#define _DF1E	0xFE
			#define _DS1S	0x41
			#define _DS1E	0x5A
			#define _DS2S	0x61
			#define _DS2E	0x7A
			#define _DS3S	0x81
			#define _DS3E	0xFE

			#elif _CODE_PAGE == 950	/* Traditional Chinese Big5 */
			#define _DF1S	0x81
			#define _DF1E	0xFE
			#define _DS1S	0x40
			#define _DS1E	0x7E
			#define _DS2S	0xA1
			#define _DS2E	0xFE

			#elif _CODE_PAGE == 437	/* U.S. */
			#define _DF1S	0
			#define _EXCVT {0x80,0x9A,0x45,0x41,0x8E,0x41,0x8F,0x80,0x45,0x45,0x45,0x49,0x49,0x49,0x8E,0x8F, \
							0x90,0x92,0x92,0x4F,0x99,0x4F,0x55,0x55,0x59,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, \
							0x41,0x49,0x4F,0x55,0xA5,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
							0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
							0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
							0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
							0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF, \
							0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}

			#elif _CODE_PAGE == 720	/* Arabic */
			#define _DF1S	0
			#define _EXCVT {0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F, \
							0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, \
							0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
							0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
							0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
							0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
							0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF, \
							0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}

			#elif _CODE_PAGE == 737	/* Greek */
			#define _DF1S	0
			#define _EXCVT {0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F, \
							0x90,0x92,0x92,0x93,0x94,0x95,0x96,0x97,0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87, \
							0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,0x90,0x91,0xAA,0x92,0x93,0x94,0x95,0x96, \
							0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
							0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
							0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
							0x97,0xEA,0xEB,0xEC,0xE4,0xED,0xEE,0xEF,0xF5,0xF0,0xEA,0xEB,0xEC,0xED,0xEE,0xEF, \
							0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}

			#elif _CODE_PAGE == 771	/* KBL */
			#define _DF1S	0
			#define _EXCVT {0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F, \
							0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, \
							0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F, \
							0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
							0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
							0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDC,0xDE,0xDE, \
							0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, \
							0xF0,0xF0,0xF2,0xF2,0xF4,0xF4,0xF6,0xF6,0xF8,0xF8,0xFA,0xFA,0xFC,0xFC,0xFE,0xFF}

			#elif _CODE_PAGE == 775	/* Baltic */
			#define _DF1S	0
			#define _EXCVT {0x80,0x9A,0x91,0xA0,0x8E,0x95,0x8F,0x80,0xAD,0xED,0x8A,0x8A,0xA1,0x8D,0x8E,0x8F, \
							0x90,0x92,0x92,0xE2,0x99,0x95,0x96,0x97,0x97,0x99,0x9A,0x9D,0x9C,0x9D,0x9E,0x9F, \
							0xA0,0xA1,0xE0,0xA3,0xA3,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
							0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
							0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
							0xB5,0xB6,0xB7,0xB8,0xBD,0xBE,0xC6,0xC7,0xA5,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
							0xE0,0xE1,0xE2,0xE3,0xE5,0xE5,0xE6,0xE3,0xE8,0xE8,0xEA,0xEA,0xEE,0xED,0xEE,0xEF, \
							0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}

			#elif _CODE_PAGE == 850	/* Latin 1 */
			#define _DF1S	0
			#define _EXCVT {0x43,0x55,0x45,0x41,0x41,0x41,0x41,0x43,0x45,0x45,0x45,0x49,0x49,0x49,0x41,0x41, \
							0x45,0x92,0x92,0x4F,0x4F,0x4F,0x55,0x55,0x59,0x4F,0x55,0x4F,0x9C,0x4F,0x9E,0x9F, \
							0x41,0x49,0x4F,0x55,0xA5,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
							0xB0,0xB1,0xB2,0xB3,0xB4,0x41,0x41,0x41,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
							0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0x41,0x41,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
							0xD1,0xD1,0x45,0x45,0x45,0x49,0x49,0x49,0x49,0xD9,0xDA,0xDB,0xDC,0xDD,0x49,0xDF, \
							0x4F,0xE1,0x4F,0x4F,0x4F,0x4F,0xE6,0xE8,0xE8,0x55,0x55,0x55,0x59,0x59,0xEE,0xEF, \
							0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}

			#elif _CODE_PAGE == 852	/* Latin 2 */
			#define _DF1S	0
			#define _EXCVT {0x80,0x9A,0x90,0xB6,0x8E,0xDE,0x8F,0x80,0x9D,0xD3,0x8A,0x8A,0xD7,0x8D,0x8E,0x8F, \
							0x90,0x91,0x91,0xE2,0x99,0x95,0x95,0x97,0x97,0x99,0x9A,0x9B,0x9B,0x9D,0x9E,0xAC, \
							0xB5,0xD6,0xE0,0xE9,0xA4,0xA4,0xA6,0xA6,0xA8,0xA8,0xAA,0x8D,0xAC,0xB8,0xAE,0xAF, \
							0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBD,0xBF, \
							0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC6,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
							0xD1,0xD1,0xD2,0xD3,0xD2,0xD5,0xD6,0xD7,0xB7,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
							0xE0,0xE1,0xE2,0xE3,0xE3,0xD5,0xE6,0xE6,0xE8,0xE9,0xE8,0xEB,0xED,0xED,0xDD,0xEF, \
							0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xEB,0xFC,0xFC,0xFE,0xFF}

			#elif _CODE_PAGE == 855	/* Cyrillic */
			#define _DF1S	0
			#define _EXCVT {0x81,0x81,0x83,0x83,0x85,0x85,0x87,0x87,0x89,0x89,0x8B,0x8B,0x8D,0x8D,0x8F,0x8F, \
							0x91,0x91,0x93,0x93,0x95,0x95,0x97,0x97,0x99,0x99,0x9B,0x9B,0x9D,0x9D,0x9F,0x9F, \
							0xA1,0xA1,0xA3,0xA3,0xA5,0xA5,0xA7,0xA7,0xA9,0xA9,0xAB,0xAB,0xAD,0xAD,0xAE,0xAF, \
							0xB0,0xB1,0xB2,0xB3,0xB4,0xB6,0xB6,0xB8,0xB8,0xB9,0xBA,0xBB,0xBC,0xBE,0xBE,0xBF, \
							0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC7,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
							0xD1,0xD1,0xD3,0xD3,0xD5,0xD5,0xD7,0xD7,0xDD,0xD9,0xDA,0xDB,0xDC,0xDD,0xE0,0xDF, \
							0xE0,0xE2,0xE2,0xE4,0xE4,0xE6,0xE6,0xE8,0xE8,0xEA,0xEA,0xEC,0xEC,0xEE,0xEE,0xEF, \
							0xF0,0xF2,0xF2,0xF4,0xF4,0xF6,0xF6,0xF8,0xF8,0xFA,0xFA,0xFC,0xFC,0xFD,0xFE,0xFF}

			#elif _CODE_PAGE == 857	/* Turkish */
			#define _DF1S	0
			#define _EXCVT {0x80,0x9A,0x90,0xB6,0x8E,0xB7,0x8F,0x80,0xD2,0xD3,0xD4,0xD8,0xD7,0x49,0x8E,0x8F, \
							0x90,0x92,0x92,0xE2,0x99,0xE3,0xEA,0xEB,0x98,0x99,0x9A,0x9D,0x9C,0x9D,0x9E,0x9E, \
							0xB5,0xD6,0xE0,0xE9,0xA5,0xA5,0xA6,0xA6,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
							0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
							0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC7,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
							0xD0,0xD1,0xD2,0xD3,0xD4,0x49,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
							0xE0,0xE1,0xE2,0xE3,0xE5,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xDE,0xED,0xEE,0xEF, \
							0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}

			#elif _CODE_PAGE == 860	/* Portuguese */
			#define _DF1S	0
			#define _EXCVT {0x80,0x9A,0x90,0x8F,0x8E,0x91,0x86,0x80,0x89,0x89,0x92,0x8B,0x8C,0x98,0x8E,0x8F, \
							0x90,0x91,0x92,0x8C,0x99,0xA9,0x96,0x9D,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, \
							0x86,0x8B,0x9F,0x96,0xA5,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
							0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
							0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
							0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
							0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF, \
							0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}

			#elif _CODE_PAGE == 861	/* Icelandic */
			#define _DF1S	0
			#define _EXCVT {0x80,0x9A,0x90,0x41,0x8E,0x41,0x8F,0x80,0x45,0x45,0x45,0x8B,0x8B,0x8D,0x8E,0x8F, \
							0x90,0x92,0x92,0x4F,0x99,0x8D,0x55,0x97,0x97,0x99,0x9A,0x9D,0x9C,0x9D,0x9E,0x9F, \
							0xA4,0xA5,0xA6,0xA7,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
							0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
							0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
							0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
							0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF, \
							0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}

			#elif _CODE_PAGE == 862	/* Hebrew */
			#define _DF1S	0
			#define _EXCVT {0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F, \
							0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, \
							0x41,0x49,0x4F,0x55,0xA5,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
							0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
							0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
							0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
							0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF, \
							0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}

			#elif _CODE_PAGE == 863	/* Canadian-French */
			#define _DF1S	0
			#define _EXCVT {0x43,0x55,0x45,0x41,0x41,0x41,0x86,0x43,0x45,0x45,0x45,0x49,0x49,0x8D,0x41,0x8F, \
							0x45,0x45,0x45,0x4F,0x45,0x49,0x55,0x55,0x98,0x4F,0x55,0x9B,0x9C,0x55,0x55,0x9F, \
							0xA0,0xA1,0x4F,0x55,0xA4,0xA5,0xA6,0xA7,0x49,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
							0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
							0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
							0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
							0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF, \
							0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}

			#elif _CODE_PAGE == 864	/* Arabic */
			#define _DF1S	0
			#define _EXCVT {0x80,0x9A,0x45,0x41,0x8E,0x41,0x8F,0x80,0x45,0x45,0x45,0x49,0x49,0x49,0x8E,0x8F, \
							0x90,0x92,0x92,0x4F,0x99,0x4F,0x55,0x55,0x59,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, \
							0x41,0x49,0x4F,0x55,0xA5,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
							0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
							0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
							0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
							0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF, \
							0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}

			#elif _CODE_PAGE == 865	/* Nordic */
			#define _DF1S	0
			#define _EXCVT {0x80,0x9A,0x90,0x41,0x8E,0x41,0x8F,0x80,0x45,0x45,0x45,0x49,0x49,0x49,0x8E,0x8F, \
							0x90,0x92,0x92,0x4F,0x99,0x4F,0x55,0x55,0x59,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, \
							0x41,0x49,0x4F,0x55,0xA5,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
							0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
							0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
							0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
							0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF, \
							0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}

			#elif _CODE_PAGE == 866	/* Russian */
			#define _DF1S	0
			#define _EXCVT {0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F, \
							0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, \
							0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F, \
							0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
							0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
							0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, \
							0x90,0x91,0x92,0x93,0x9d,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, \
							0xF0,0xF0,0xF2,0xF2,0xF4,0xF4,0xF6,0xF6,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF}

			#elif _CODE_PAGE == 869	/* Greek 2 */
			#define _DF1S	0
			#define _EXCVT {0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F, \
							0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x86,0x9C,0x8D,0x8F,0x90, \
							0x91,0x90,0x92,0x95,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, \
							0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, \
							0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, \
							0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xA4,0xA5,0xA6,0xD9,0xDA,0xDB,0xDC,0xA7,0xA8,0xDF, \
							0xA9,0xAA,0xAC,0xAD,0xB5,0xB6,0xB7,0xB8,0xBD,0xBE,0xC6,0xC7,0xCF,0xCF,0xD0,0xEF, \
							0xF0,0xF1,0xD1,0xD2,0xD3,0xF5,0xD4,0xF7,0xF8,0xF9,0xD5,0x96,0x95,0x98,0xFE,0xFF}

			#elif _CODE_PAGE == 1	/* ASCII (for only non-LFN cfg) */
			#if _USE_LFN != 0
			#error Cannot enable LFN without valid code page.
			#endif
			#define _DF1S	0

			#else
			#error Unknown code page

			#endif


			/* Character code support macros */
			#define IsUpper(c)	(((c)>='A')&&((c)<='Z'))
			#define IsLower(c)	(((c)>='a')&&((c)<='z'))
			#define IsDigit(c)	(((c)>='0')&&((c)<='9'))

			#if _DF1S != 0	/* Code page is DBCS */

			#ifdef _DF2S	/* Two 1st byte areas */
			#define IsDBCS1(c)	(((BYTE)(c) >= _DF1S && (BYTE)(c) <= _DF1E) || ((BYTE)(c) >= _DF2S && (BYTE)(c) <= _DF2E))
			#else			/* One 1st byte area */
			#define IsDBCS1(c)	((BYTE)(c) >= _DF1S && (BYTE)(c) <= _DF1E)
			#endif

			#ifdef _DS3S	/* Three 2nd byte areas */
			#define IsDBCS2(c)	(((BYTE)(c) >= _DS1S && (BYTE)(c) <= _DS1E) || ((BYTE)(c) >= _DS2S && (BYTE)(c) <= _DS2E) || ((BYTE)(c) >= _DS3S && (BYTE)(c) <= _DS3E))
			#else			/* Two 2nd byte areas */
			#define IsDBCS2(c)	(((BYTE)(c) >= _DS1S && (BYTE)(c) <= _DS1E) || ((BYTE)(c) >= _DS2S && (BYTE)(c) <= _DS2E))
			#endif

			#else			/* Code page is SBCS */

			#define IsDBCS1(c)	0
			#define IsDBCS2(c)	0

			#endif /* _DF1S */


			/* Name status flags */
			#define NSFLAG		11		/* Index of name status byte in fn[] */
			#define NS_LOSS		0x01	/* Out of 8.3 format */
			#define NS_LFN		0x02	/* Force to create LFN entry */
			#define NS_LAST		0x04	/* Last segment */
			#define NS_BODY		0x08	/* Lower case flag (body) */
			#define NS_EXT		0x10	/* Lower case flag (ext) */
			#define NS_DOT		0x20	/* Dot entry */
			#define NS_NONAME	0x80	/* Not followed */


			/* Limits and Boundaries (Differ from specs but correct for real DOS/Windows) */
			#define MIN_FAT16	4086U			/* Minimum number of clusters of FAT16 */
			#define	MIN_FAT32	65526U			/* Minimum number of clusters of FAT32 */
			#define MAX_DIR		0x200000		/* Maximum size of FAT directory */
			#define MAX_DIR_EX	0x10000000		/* Maximum size of exFAT directory */


			/* FatFs refers the members in the FAT structures as byte array instead of
			/ structure members because the structure is not binary compatible between
			/ different platforms */

			#define BS_jmpBoot			0		/* x86 jump instruction (3-byte) */
			#define BS_OEMName			3		/* OEM name (8-byte) */
			#define BPB_BytsPerSec		11		/* Sector size [byte] (WORD) */
			#define BPB_SecPerClus		13		/* Cluster size [sector] (BYTE) */
			#define BPB_RsvdSecCnt		14		/* Size of reserved area [sector] (WORD) */
			#define BPB_NumFATs			16		/* Number of FATs (BYTE) */
			#define BPB_RootEntCnt		17		/* Size of root directory area for FAT12/16 [entry] (WORD) */
			#define BPB_TotSec16		19		/* Volume size (16-bit) [sector] (WORD) */
			#define BPB_Media			21		/* Media descriptor (BYTE) */
			#define BPB_FATSz16			22		/* FAT size (16-bit) [sector] (WORD) */
			#define BPB_SecPerTrk		24		/* Track size for int13h [sector] (WORD) */
			#define BPB_NumHeads		26		/* Number of heads for int13h (WORD) */
			#define BPB_HiddSec			28		/* Volume offset from top of the drive (DWORD) */
			#define BPB_TotSec32		32		/* Volume size (32-bit) [sector] (DWORD) */
			#define BS_DrvNum			36		/* Physical drive number for int13h (BYTE) */
			#define BS_NTres			37		/* Error flag (BYTE) */
			#define BS_BootSig			38		/* Extended boot signature (BYTE) */
			#define BS_VolID			39		/* Volume serial number (DWORD) */
			#define BS_VolLab			43		/* Volume label string (8-byte) */
			#define BS_FilSysType		54		/* File system type string (8-byte) */
			#define BPB_FATSz32			36		/* FAT size (32-bit) [sector] (DWORD) */
			#define BPB_ExtFlags		40		/* Extended flags (WORD) */

			#define BPB_FSVer32			42		/* FAT32: File system version (WORD) */
			#define BPB_RootClus32		44		/* FAT32: Root directory cluster (DWORD) */
			#define BPB_FSInfo32		48		/* FAT32: Offset of FSINFO sector (WORD) */
			#define BPB_BkBootSec32		50		/* FAT32: Offset of backup boot sector (WORD) */
			#define BS_DrvNum32			64		/* FAT32: Physical drive number for int13h (BYTE) */
			#define BS_NTres32			65		/* FAT32: Error flag (BYTE) */
			#define BS_BootSig32		66		/* FAT32: Extended boot signature (BYTE) */
			#define BS_VolID32			67		/* FAT32: Volume serial number (DWORD) */
			#define BS_VolLab32			71		/* FAT32: Volume label string (8-byte) */
			#define BS_FilSysType32		82		/* FAT32: File system type string (8-byte) */

			#define BPB_ZeroedEx		11		/* exFAT: Must be zero (35-byte) */
			#define BPB_VolOfsEx		64		/* exFAT: Volume offset from top of the drive [sector] (QWORD) */
			#define BPB_TotSecEx		72		/* exFAT: Volume size [sector] (QWORD) */
			#define BPB_FatOfsEx		80		/* exFAT: FAT offset from top of the volume [sector] (DWORD) */
			#define BPB_FatSzEx			84		/* exFAT: FAT size [sector] (DWORD) */
			#define BPB_DataOfsEx		88		/* exFAT: Data offset from top of the volume [sector] (DWORD) */
			#define BPB_NumClusEx		92		/* exFAT: Number of clusters (DWORD) */
			#define BPB_RootClusEx		96		/* exFAT: Root directory cluster (DWORD) */
			#define BPB_VolIDEx			100		/* exFAT: Volume serial number (DWORD) */
			#define BPB_FSVerEx			104		/* exFAT: File system version (WORD) */
			#define BPB_VolFlagEx		106		/* exFAT: Volume flags (BYTE) */
			#define BPB_ActFatEx		107		/* exFAT: Active FAT flags (BYTE) */
			#define BPB_BytsPerSecEx	108		/* exFAT: Log2 of sector size in byte (BYTE) */
			#define BPB_SecPerClusEx	109		/* exFAT: Log2 of cluster size in sector (BYTE) */
			#define BPB_NumFATsEx		110		/* exFAT: Number of FATs (BYTE) */
			#define BPB_DrvNumEx		111		/* exFAT: Physical drive number for int13h (BYTE) */
			#define BPB_PercInUseEx		112		/* exFAT: Percent in use (BYTE) */

			#define	FSI_LeadSig			0		/* FAT32 FSI: Leading signature (DWORD) */
			#define	FSI_StrucSig		484		/* FAT32 FSI: Structure signature (DWORD) */
			#define	FSI_Free_Count		488		/* FAT32 FSI: Number of free clusters (DWORD) */
			#define	FSI_Nxt_Free		492		/* FAT32 FSI: Last allocated cluster (DWORD) */

			#define MBR_Table			446		/* MBR: Partition table offset */
			#define	SZ_PTE				16		/* MBR: Size of a partition table entry */

			#define BS_55AA				510		/* Signature word (WORD) */

			#define	DIR_Name			0		/* Short file name (11) */
			#define	DIR_Attr			11		/* Attribute (1) */
			#define	DIR_NTres			12		/* Lower case flag (1) */
			#define DIR_CrtTime10		13		/* Created time sub-second (1) */
			#define	DIR_CrtTime			14		/* Created time (2) */
			#define	DIR_CrtDate			16		/* Created date (2) */
			#define DIR_LstAccDate		18		/* Last accessed date (2) */
			#define	DIR_FstClusHI		20		/* Higher 16-bit of first cluster (WORD) */
			#define	DIR_WrtTime			22		/* Modified time (2) */
			#define	DIR_WrtDate			24		/* Modified date (2) */
			#define	DIR_FstClusLO		26		/* Lower 16-bit of first cluster (WORD) */
			#define	DIR_FileSize		28		/* File size (DWORD) */
			#define	LDIR_Ord			0		/* LFN entry order and LLE flag (1) */
			#define	LDIR_Attr			11		/* LFN attribute (1) */
			#define	LDIR_Type			12		/* LFN type (1) */
			#define	LDIR_Chksum			13		/* Checksum of the SFN entry */
			#define	LDIR_FstClusLO		26		/* Must be zero (WORD) */
			#define	XDIR_Type			0		/* Type of exFAT directory entry (BYTE) */
			#define	XDIR_NumLabel		1		/* Number of volume label characters (BYTE) */
			#define	XDIR_Label			2		/* Volume label (11-WORD) */
			#define	XDIR_CaseSum		4		/* Sum of case conversion table (DWORD) */
			#define	XDIR_NumSec			1		/* Number of secondary entries (BYTE) */
			#define	XDIR_SetSum			2		/* Sum of the set of directory entries (WORD) */
			#define	XDIR_Attr			4		/* File attribute (WORD) */
			#define	XDIR_CrtTime		8		/* Created time (4) */
			#define	XDIR_ModTime		12		/* Modified time (4) */
			#define	XDIR_AccTime		16		/* Last accessed time (4) */
			#define	XDIR_CrtTime10		20		/* Created time subsecond (1) */
			#define	XDIR_ModTime10		21		/* Modified time subsecond (1) */
			#define	XDIR_CrtTZ			22		/* Created timezone (1) */
			#define	XDIR_ModTZ			23		/* Modified timezone (1) */
			#define	XDIR_AccTZ			24		/* Last accessed timezone (1) */
			#define	XDIR_GenFlags		33		/* Gneral flags (1) */
			#define	XDIR_NumName		35		/* Number of file name characters (BYTE) */
			#define	XDIR_NameHash		36		/* Hash of file name (WORD) */
			#define XDIR_ValidFileSize	40		/* Valid file size (QWORD) */
			#define	XDIR_FstClus		52		/* First cluster of the File/Directory (DWORD) */
			#define	XDIR_FileSize		56		/* File/Directory size (QWORD) */

			#define	SZDIRE				32		/* Size of a directory entry */
			#define	LLEF				0x40	/* Last long entry flag in LDIR_Ord */
			#define	DDEM				0xE5	/* Deleted directory entry mark at DIR_Name[0] */
			#define	RDDEM				0x05	/* Replacement of the character collides with DDEM */





			/*--------------------------------------------------------------------------

			   Module Private Work Area

			---------------------------------------------------------------------------*/

			/* Remark: Variables here without initial value shall be guaranteed zero/null
			/  at start-up. If not, either the linker or start-up routine being used is
			/  not compliance with C standard. */

			#if _VOLUMES < 1 || _VOLUMES > 9
			#error Wrong _VOLUMES setting
			#endif


			#if _FS_RPATH != 0 && _VOLUMES >= 2
			static BYTE CurrVol;			/* Current drive */
			#endif

			#if _FS_LOCK != 0
			static FILESEM Files[_FS_LOCK];	/* Open object lock semaphores */
			#endif

			#if _USE_LFN == 0			/* Non-LFN configuration */
			#define	DEF_NAMBUF			BYTE sfn[12]
			#define INIT_NAMBUF(dobj)	(dobj).fn = sfn
			#define	FREE_NAMBUF()
			#define	DEF_DIRBUF
			#define INIT_DIRBUF(fs)
			#define	FREE_DIRBUF()
			#else
			#if _MAX_LFN < 12 || _MAX_LFN > 255
			#error Wrong _MAX_LFN setting
			#endif

			#if _USE_LFN == 1		/* LFN enabled with static working buffer */
			#if _FS_EXFAT
			static BYTE	DirBuf[SZDIRE*19];	/* Directory entry block scratchpad buffer (19 entries in size) */
			#endif
			static WCHAR LfnBuf[_MAX_LFN+1];	/* LFN enabled with static working buffer */
			#define	DEF_NAMBUF		BYTE sfn[12]
			#define INIT_NAMBUF(dj)	{ (dj).fn = sfn; (dj).lfn = LfnBuf; }
			#define	FREE_NAMBUF()
			#define	DEF_DIRBUF
			#define INIT_DIRBUF(fs)
			#define	FREE_DIRBUF()

			#elif _USE_LFN == 2 	/* LFN enabled with dynamic working buffer on the stack */
			#if _FS_EXFAT
			#define	DEF_NAMBUF		BYTE sfn[12]; WCHAR lbuf[_MAX_LFN+1]; BYTE dbuf[SZDIRE*19]
			#define INIT_NAMBUF(dj)	{ (dj).fn = sfn; (dj).lfn = lbuf; (dj).obj.fs->dirbuf = dbuf; }
			#define	FREE_NAMBUF()
			#define	DEF_DIRBUF		BYTE dbuf[SZDIRE*19]
			#define INIT_DIRBUF(fs)	fs->dirbuf = dbuf
			#define	FREE_DIRBUF()
			#else
			#define	DEF_NAMBUF		BYTE sfn[12]; WCHAR lbuf[_MAX_LFN+1]
			#define INIT_NAMBUF(dj)	{ (dj).fn = sfn; (dj).lfn = lbuf; }
			#define	FREE_NAMBUF()
			#define	DEF_DIRBUF
			#define INIT_DIRBUF(fs)
			#define	FREE_DIRBUF()
			#endif

			#elif _USE_LFN == 3 	/* LFN enabled with dynamic working buffer on the heap */
			#if _FS_EXFAT
			#define	DEF_NAMBUF		BYTE sfn[12]; WCHAR *lfn
			#define INIT_NAMBUF(dj)	{ lfn = ff_memalloc((_MAX_LFN+1)*2 + SZDIRE*19); if (!lfn) LEAVE_FF((dj).obj.fs, FR_NOT_ENOUGH_CORE); (dj).fn = sfn; (dj).lfn = lfn; (dj).obj.fs->dirbuf = (BYTE*)(lfn+_MAX_LFN+1); }
			#define	FREE_NAMBUF()	ff_memfree(lfn)
			#define	DEF_DIRBUF		BYTE *dirb
			#define INIT_DIRBUF(fs)	{ dirb = ff_memalloc(SZDIRE*19); if (!dirb) LEAVE_FF(fs, FR_NOT_ENOUGH_CORE); fs->dirbuf = dirb; }
			#define	FREE_DIRBUF()	ff_memfree(dirb)
			#else
			#define	DEF_NAMBUF		BYTE sfn[12]; WCHAR *lfn
			#define INIT_NAMBUF(dj)	{ lfn = ff_memalloc((_MAX_LFN+1)*2); if (!lfn) LEAVE_FF((dj).obj.fs, FR_NOT_ENOUGH_CORE); (dj).fn = sfn; (dj).lfn = lfn; }
			#define	FREE_NAMBUF()	ff_memfree(lfn)
			#define	DEF_DIRBUF
			#define INIT_DIRBUF(fs)
			#define	FREE_DIRBUF()
			#endif

			#else
			#error Wrong _USE_LFN setting
			#endif
			#endif

			#ifdef _EXCVT
			static const BYTE ExCvt[] = _EXCVT;	/* Upper conversion table for SBCS extended characters */
			#endif


			void st_word (BYTE* ptr, WORD val);
			void st_dword (BYTE* ptr, DWORD val);
			void mem_cpy (void* dst, const void* src, UINT cnt);
			void mem_set (void* dst, int val, UINT cnt);
			void st_clust (FATFS* fs,BYTE* dir,DWORD cl);

			BYTE check_fs (FATFS* fs,DWORD sect);

			WORD ld_word(const BYTE* ptr);

			DWORD ld_dword (const BYTE* ptr);
			DWORD clust2sect (FATFS* fs,	DWORD clst);
			DWORD get_fat (_FDID* obj,DWORD clst);
			DWORD create_chain (_FDID* obj,DWORD clst);
			DWORD ld_clust (FATFS* fs,const BYTE* dir);

			int chk_chr (const char* str, int chr);
			int mem_cmp (const void* dst, const void* src, UINT cnt);

			FRESULT sync_window (FATFS* fs);
			FRESULT move_window (FATFS* fs,DWORD sector);
			FRESULT sync_fs (FATFS* fs);
			FRESULT put_fat (FATFS* fs,DWORD clst,DWORD val);
			FRESULT remove_chain (_FDID* obj,DWORD clst,DWORD pclst	);

			FRESULT dir_sdi (DIR* dp,DWORD ofs);
			FRESULT dir_next (DIR* dp,int stretch);
			FRESULT dir_alloc (DIR* dp,UINT nent);




			FRESULT dir_read (DIR* dp,int vol	);
			FRESULT dir_find (DIR* dp	);
			FRESULT dir_register (DIR* dp);
			FRESULT dir_remove (DIR* dp);
			void get_fileinfo (DIR* dp,FILINFO* fno);
			FRESULT create_name (DIR* dp,const TCHAR** path);
			FRESULT follow_path (DIR* dp,const TCHAR* path);
			int get_ldnumber (const TCHAR** path);

			FRESULT find_volume (const TCHAR** path,FATFS** rfs,BYTE mode);
			FRESULT validate (void* dfp,FATFS** fs);


			FATFS mFatFs;
			FIL   mFile;
			FRESULT mRESULT;

			bool isFileOpen;







			// low level I/O functions

			/* Definitions for MMC/SDC command */
			#define CMD0    (0x40+0)    /* GO_IDLE_STATE */
			#define CMD1    (0x40+1)    /* SEND_OP_COND */
			#define CMD8    (0x40+8)    /* SEND_IF_COND */
			#define CMD9    (0x40+9)    /* SEND_CSD */
			#define CMD10    (0x40+10)    /* SEND_CID */
			#define CMD12    (0x40+12)    /* STOP_TRANSMISSION */
			#define CMD16    (0x40+16)    /* SET_BLOCKLEN */
			#define CMD17    (0x40+17)    /* READ_SINGLE_BLOCK */
			#define CMD18    (0x40+18)    /* READ_MULTIPLE_BLOCK */
			#define CMD23    (0x40+23)    /* SET_BLOCK_COUNT */
			#define CMD24    (0x40+24)    /* WRITE_BLOCK */
			#define CMD25    (0x40+25)    /* WRITE_MULTIPLE_BLOCK */
			#define CMD41    (0x40+41)    /* SEND_OP_COND (ACMD) */
			#define CMD55    (0x40+55)    /* APP_CMD */
			#define CMD58    (0x40+58)    /* READ_OCR */


			DSTATUS Stat = STA_NOINIT;    /* Disk status */
			BYTE Timer1, Timer2;    /* 100Hz decrement timer */
			BYTE CardType;            /* b0:MMC, b1:SDC, b2:Block addressing */
			BYTE PowerFlag = 0;     /* indicates if "power" is on */


			void SELECT(void);
			void DESELECT (void);
			void xmit_spi (BYTE Data);
			BYTE rcvr_spi (void);
			void rcvr_spi_m (BYTE *dst);
			BYTE wait_ready (void);
			void power_on (void);
			void power_off (void);
			int chk_power(void);
			unsigned char rcvr_datablock (BYTE *buff,UINT btr);
			unsigned char xmit_datablock (const BYTE *buff,BYTE token);
			BYTE send_cmd (BYTE cmd,DWORD arg);
			void disk_timerproc (void);


		public:

			kRecorder(void);
			bool init(void);
			bool openLog(const char * file_path);
			void closeLog(void);
			bool writeRecord(const char * data);
			bool writeRecord(char * buff,unsigned char bytes);
			bool isOpen(void);


	};

#endif
