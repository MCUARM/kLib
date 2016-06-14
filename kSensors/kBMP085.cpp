#include "kBMP085.h"

kBMP085::kBMP085(void)
{
	this->BMP085_BasePressure = 101325;
	this->I2C_Address = BMP085_Address;
	this->BMP085_OSS = 1;
}

void kBMP085::init(void)
{
	unsigned char BMP085_tp_buff[22];
	this->read(BMP085_REGISTER_EEPROM_DATA_BASE,BMP085_tp_buff,22);

	// przepisz dane z bufora odbiorczego do struktury BMP085_CALIB_VALUE
	// z jednoczesnym sk³adaniem dwóch bajtów w s³owo 16-bitowe
	BMP085_CALIB_VALUE.AC1 = (BMP085_tp_buff[0] << 8) | BMP085_tp_buff[1];
	BMP085_CALIB_VALUE.AC2 = (BMP085_tp_buff[2] << 8) | BMP085_tp_buff[3];
	BMP085_CALIB_VALUE.AC3 = (BMP085_tp_buff[4] << 8) | BMP085_tp_buff[5];
	BMP085_CALIB_VALUE.AC4 = (BMP085_tp_buff[6] << 8) | BMP085_tp_buff[7];
	BMP085_CALIB_VALUE.AC5 = (BMP085_tp_buff[8] << 8) | BMP085_tp_buff[9];
	BMP085_CALIB_VALUE.AC6 = (BMP085_tp_buff[10] << 8) | BMP085_tp_buff[11];
	BMP085_CALIB_VALUE.B1 = (BMP085_tp_buff[12] << 8) | BMP085_tp_buff[13];
	BMP085_CALIB_VALUE.B2 = (BMP085_tp_buff[14] << 8) | BMP085_tp_buff[15];
	BMP085_CALIB_VALUE.MB = (BMP085_tp_buff[16] << 8) | BMP085_tp_buff[17];
	BMP085_CALIB_VALUE.MC = (BMP085_tp_buff[18] << 8) | BMP085_tp_buff[19];
	BMP085_CALIB_VALUE.MD = (BMP085_tp_buff[20] << 8) | BMP085_tp_buff[21];
}
// funkcja wysy³a ¿¹danie pomiaru temperatury
// odczyt temperatury nale¿y dokonaæ po pewnym czasie
void kBMP085::requestUncompensatedTemperature(void)
{
	unsigned char BMP085_tp_buff[1];

	// wykonaj pomiar temperatury nieskompensowanej
	// wpisz wartosæ 0x2E do 0xF4 (zgodnie z datasheet)
	BMP085_tp_buff[0] = 0x2E;

	this->write(BMP085_REGISTER_CR,BMP085_tp_buff,1);
}
// funkcja odczytuje temperaturê nieskompensowan¹
long kBMP085::readUncompensatedTemperature(void)
{
	long ut;
	unsigned char BMP085_tp_buff[2];

	// odczytaj temperaturê nieskompensowan¹
	this->read(BMP085_REGISTER_DATA_MSB,BMP085_tp_buff,2);
	// przepisz bufor odbiorczy do zmiennej ut (uncompensated temperature)
	ut = (BMP085_tp_buff[0] << 8) | BMP085_tp_buff[1];

	return ut;
}
// funkcja wysy³a ¿¹danie pomiaru cisnienia
// odczyt cisniena nale¿y dokonaæ po pewnym czasie
void kBMP085::requestUncompensatedPressure(void)
{
	unsigned char BMP085_tp_buff[1];

	// wykonaj pomiar cisnienia nieskompensowanego
	BMP085_tp_buff[0] = (0x34+(BMP085_OSS<<6));
	this->write(BMP085_REGISTER_CR,BMP085_tp_buff,1);
}
// funkcja odczytuje cisnienie nieskompensowane
long kBMP085::readUncompensatedPressure(void)
{
	long up;
	unsigned char BMP085_tp_buff[3];

	// odczytaj cisnienie nieskompensowane
	this->read(BMP085_REGISTER_DATA_MSB,BMP085_tp_buff,3);
	// przepisz bufor odbiorczy do zmiennej up (uncompensated pressure) - 3 bajty
	up = (( BMP085_tp_buff[0] << 16) | ( BMP085_tp_buff[1] << 8) |  BMP085_tp_buff[2]) >> (8-BMP085_OSS);

	return up;
}
// funkcja oblicza skalibrowan¹ temperaturê
void kBMP085::getCalibratedData(long * temperature, long * pressure, long ut, long up)
{
	// pomocniczo w obliczeniach
	long x1,x2,x3;
	// obliczeniowe wspó³czynniki korekcyjne
	unsigned long b4;
	long b3,b5,b6,b7;

	long p; // cisnienie (pomocniczo)


    // Obliczanie temperatury
    // oblicz B5
    x1 = ((ut - this->BMP085_CALIB_VALUE.AC6) * this->BMP085_CALIB_VALUE.AC5) >> 15;
    x2 = (this->BMP085_CALIB_VALUE.MC << 11) / (x1 + this->BMP085_CALIB_VALUE.MD);
    b5 = x1 + x2;

    // temperatura skompensowana
    *temperature = ((b5 + 8) >> 4);

    // Obliczanie cisnienia
    // oblicz B6
    b6 = b5 - 4000;

    // oblicz B3
    x1 = (this->BMP085_CALIB_VALUE.B2 * ((b6 * b6) >> 12)) >> 11;
    x2 = (this->BMP085_CALIB_VALUE.AC2 * b6) >> 11;
    x3 = x1 + x2;
    b3 = ((((this->BMP085_CALIB_VALUE.AC1)*4 + x3)<<this->BMP085_OSS) + 2)>>2;

    // oblicz B4
    x1 = (this->BMP085_CALIB_VALUE.AC3 * b6)>>13;
    x2 = (this->BMP085_CALIB_VALUE.B1 * ((b6 * b6)>>12))>>16;
    x3 = ((x1 + x2) + 2)>>2;
    b4 = (this->BMP085_CALIB_VALUE.AC4 * (unsigned long)(x3 + 32768))>>15;

    // oblicz B7
    b7 = (((unsigned long)up - b3) * (50000>>this->BMP085_OSS));

    if (b7 < (long)0x80000000)
    {
          p = (b7<<1)/b4;
    }else
    {
          p = (b7/b4)<<1;
    }

    // oblicz cisnienie skompensowane
    x1 = (p>>8) * (p>>8);
    x1 = (x1 * 3038)>>16;
    x2 = (-7357 * p)>>16;
    p += (x1 + x2 + 3791)>>4;

    // cisnienie skompensowane
    *pressure = p;


	/*
	* Wiêcej szczegó³ów odnosnie obliczeñ znajdziesz w nocie katalogowej
	* BMP085
	*/
}
// funkcja przelicza cisnienie na wysokosæ zgodnie
// ze wzorem atmosfery standardowej
float kBMP085::getAltitude(long pressure)
{
	float dp,altitude,wyk;

	// Obliczanie wysokosci QNE (zgodnie ze wzorem atmosfery standardowej)
	// wzór dostêpny równie¿ w nocie katalogoej

	dp=((float)pressure)/((float)this->BMP085_BasePressure);        // podstawa potêgi
	wyk=1/5.25588;                     // wyk³adnik
	//przeliczenie na wysokosæ [m]
	altitude=1-(pow(dp,wyk));
	altitude=altitude*44330;

	return altitude;
}
