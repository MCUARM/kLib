
#ifndef __kSDCard_H
#define __kSDCard_H

	/*
	 * Includes
	 */
	#include "kSystem.h"
	#include "kSPIDevice.h"
	#include "kFAT.h"


	/* Definitions for MMC/SDC command */

	class kSD
	{
		public:

			typedef enum : unsigned char
			{
				CMD0     = (0x40+0),     /* GO_IDLE_STATE */
				CMD1     = (0x40+1),     /* SEND_OP_COND */
				CMD8     = (0x40+8),     /* SEND_IF_COND */
				CMD9     = (0x40+9),     /* SEND_CSD */
				CMD10    = (0x40+10),    /* SEND_CID */
				CMD12    = (0x40+12),    /* STOP_TRANSMISSION */
				CMD16    = (0x40+16),    /* SET_BLOCKLEN */
				CMD17    = (0x40+17),    /* READ_SINGLE_BLOCK */
				CMD18    = (0x40+18),    /* READ_MULTIPLE_BLOCK */
				CMD23    = (0x40+23),    /* SET_BLOCK_COUNT */
				CMD24    = (0x40+24),    /* WRITE_BLOCK */
				CMD25    = (0x40+25),    /* WRITE_MULTIPLE_BLOCK */
				CMD41    = (0x40+41),    /* SEND_OP_COND = (ACMD) */
				CMD55    = (0x40+55),    /* APP_CMD */
				CMD58    = (0x40+58)     /* READ_OCR */
			}CMD_t;

			typedef enum : unsigned char
			{
				NoInit		 = 0x01,	/* Drive not initialized */
				NoDisk		 = 0x02,	/* No medium in the drive */
				WriteProtect = 0x04	/* Write protected */
			}status_t;

			typedef enum : unsigned char
			{
				OK	   = 0x00,		/* 0: Successful */
				ERROR  = 0x01,		/* 1: R/W Error */
				WRPRT  = 0x02,		/* 2: Write Protected */
				NOTRDY = 0x03,		/* 3: Not Ready */
				PARERR = 0x04		/* 4: Invalid Parameter */
			}result_t;

	};


	class kSDCard : public kSPIDevice
	{
		friend class kSDCardDrive;

		protected:

			unsigned char sd_card_mounted;
			unsigned char prvVersion;
			unsigned char prvStatus;

			bool xmit_datablock (unsigned char * buff, unsigned char token);
			bool rcvr_datablock (unsigned char * buff, unsigned int btr);

		public:

			kSDCard(void);
			unsigned char waitReady(void);

			void run(unsigned int sck_freq);

			unsigned char init(void);
			unsigned char getStatus(void);
			unsigned char writeCMD(unsigned char cmd,unsigned int arg);
			unsigned char readSector(unsigned char * buff, unsigned long sector, unsigned int count);
			unsigned char writeSector(const unsigned char* buff, unsigned long sector, unsigned int count);
	};

#endif
