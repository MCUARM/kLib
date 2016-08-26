#include "kSDCardDrive.h"

kFAT::DRESULT kSDCardDrive::ioctl(unsigned char cmd, void* buff)
{
    kFAT::DRESULT res;
    unsigned char n, csd[16];
    unsigned short csize;

    if (this->prvStatus & kSD::NoInit) return kFAT::RES_NOTRDY;

	res = kFAT::RES_ERROR;

	this->select();        /* CS = L */

	switch (cmd) {
        case GET_SECTOR_COUNT :    /* Get number of sectors on the disk (DWORD) */
            if ((this->writeCMD(kSD::CMD9, 0) == 0) && this->rcvr_datablock(csd, 16)) {
                if ((csd[0] >> 6) == 1) {    /* SDC ver 2.00 */
                    csize = csd[9] + ((WORD)csd[8] << 8) + 1;
                    *(DWORD*)buff = (DWORD)csize << 10;
                } else {                    /* MMC or SDC ver 1.XX */
                    n = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
                    csize = (csd[8] >> 6) + ((WORD)csd[7] << 2) + ((WORD)(csd[6] & 3) << 10) + 1;
                    *(DWORD*)buff = (DWORD)csize << (n - 9);
                }
                res = kFAT::RES_OK;
            }
            break;

        case GET_SECTOR_SIZE :    /* Get sectors on the disk (WORD) */
            *(WORD*)buff = 512;
            res = kFAT::RES_OK;
            break;

        case CTRL_SYNC :    /* Make sure that data has been written */
            if (this->waitReady() == 0xFF)
                res = kFAT::RES_OK;
            break;
        case GET_BLOCK_SIZE:
        	*(WORD*)buff = 1;
			return kFAT::RES_OK;
		case CTRL_TRIM:
			return kFAT::RES_OK;
		break;
        default:
            res = kFAT::RES_PARERR;
	}

	this->deselect();            /* CS = H */
	this->kSPIDevice::read();    /* Idle (Release DO) */

    return res;
}



