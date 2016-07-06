#include "kSDCard.h"


unsigned char kSDCard::init(void)
{
	unsigned char i;

	//wait 1ms for power up
	kSystem.waitms(1);

	// init SDCard SPI mode
	this->deselect();
	for(i=0;i<10;i++) this->write(0xFF);


	this->select();
	if(this->sendCMD(SD_CMD0,0) == 0x01)
	{
		// card detected

		// software card reset
		while(this->sendCMD(SD_CMD1,0) != 0x00);

		// card mounted
		this->sd_card_mounted = 1;

	}else
	{
		// card not available
		this->sd_card_mounted = 0;
	}
	this->deselect();

	return this->sd_card_mounted;
}
unsigned char kSDCard::mounted(void)
{
	return this->sd_card_mounted;
}
void kSDCard::waitReady(void)
{
	this->read();
	while(this->read() != 0xFF);
}
unsigned char kSDCard::sendCMD(unsigned char cmd,unsigned int arg)
{
    unsigned char n, res;

    this->waitReady();

    // Send command packet
    this->write(cmd);     		                   /* Command */
    this->write((unsigned char)(arg >> 24));        /* Argument[31..24] */
    this->write((unsigned char)(arg >> 16));        /* Argument[23..16] */
    this->write((unsigned char)(arg >> 8));            /* Argument[15..8] */
    this->write((unsigned char)arg);                /* Argument[7..0] */

    // send CRC
    n = 0;
    if (cmd == SD_CMD0) n = 0x95;            /* CRC for CMD0(0) */
    if (cmd == SD_CMD8) n = 0x87;            /* CRC for CMD8(0x1AA) */
    this->write(n);

    /* Receive command response */
    if (cmd == SD_CMD12) this->read();        /* Skip a stuff byte when stop reading */
    n = 10;                                /* Wait for a valid response in timeout of 10 attempts */
    do
        res = this->read();
    while ((res & 0x80) && --n);

    return res;            /* Return with the response value */
}
