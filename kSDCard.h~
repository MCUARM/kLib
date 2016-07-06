
#ifndef __kSDCard_H
#define __kSDCard_H

	/*
	 * Includes
	 */
	#include "stm32f4xx.h"
	#include "kSPIDevice.h"
	#include "kSystem.h"


	/* Definitions for MMC/SDC command */
	#define SD_CMD0    (0x40+0)    /* GO_IDLE_STATE */
	#define SD_CMD1    (0x40+1)    /* SEND_OP_COND */
	#define SD_CMD8    (0x40+8)    /* SEND_IF_COND */
	#define SD_CMD9    (0x40+9)    /* SEND_CSD */
	#define SD_CMD10    (0x40+10)    /* SEND_CID */
	#define SD_CMD12    (0x40+12)    /* STOP_TRANSMISSION */
	#define SD_CMD16    (0x40+16)    /* SET_BLOCKLEN */
	#define SD_CMD17    (0x40+17)    /* READ_SINGLE_BLOCK */
	#define SD_CMD18    (0x40+18)    /* READ_MULTIPLE_BLOCK */
	#define SD_CMD23    (0x40+23)    /* SET_BLOCK_COUNT */
	#define SD_CMD24    (0x40+24)    /* WRITE_BLOCK */
	#define SD_CMD25    (0x40+25)    /* WRITE_MULTIPLE_BLOCK */
	#define SD_CMD41    (0x40+41)    /* SEND_OP_COND (ACMD) */
	#define SD_CMD55    (0x40+55)    /* APP_CMD */
	#define SD_CMD58    (0x40+58)    /* READ_OCR */


	class kSDCard : public kSPIDevice
	{
		private:

			unsigned char sd_card_mounted;

			void waitReady(void);

		public:

			unsigned char init(void);
			unsigned char mounted(void);
			unsigned char sendCMD(unsigned char cmd,unsigned int arg);
	};

#endif
