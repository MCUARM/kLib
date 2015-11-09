
#ifndef __kBMP085_H
#define __kBMP085_H

	/*
	 * Includes
	 */
	#include "stm32f4xx.h"
	#include "kI2CDevice.h"
	#include "math.h"

	// definicja struktury przechowuj¹cej indywidualne parametry kalibruj¹ce
	// BMP085
	typedef struct
	{
		  short AC1;
		  short AC2;
		  short AC3;
		  unsigned short AC4;
		  unsigned short AC5;
		  unsigned short AC6;
		  short B1;
		  short B2;
		  short MB;
		  short MC;
		  short MD;

	}BMP085_CalibValueType;

	#define BMP085_Address (uint8_t)0xEE
	#define BMP085_REGISTER_CR (uint8_t)0xF4
	#define BMP085_REGISTER_DATA_MSB (uint8_t)0xF6
	#define BMP085_REGISTER_DATA_LSB (uint8_t)0xF7
	#define BMP085_REGISTER_DATA_XLSB (uint8_t)0xF8
	#define BMP085_REGISTER_EEPROM_DATA_BASE (uint8_t)0xAA
	#define BMP085_OSS_1_SAMPLE (uint8_t)0x00
	#define BMP085_OSS_2_SAMPLES (uint8_t)0x01
	#define BMP085_OSS_4_SAMPLES (uint8_t)0x02
	#define BMP085_OSS_8_SAMPLES (uint8_t)0x03


	class kBMP085 : public kI2CDevice
	{
		public:

			BMP085_CalibValueType BMP085_CALIB_VALUE;
			uint8_t BMP085_OSS;
			long BMP085_BasePressure;

			kBMP085(void);

			void init(void);
			// funkcja wysy³a ¿¹danie pomiaru temperatury
			// odczyt temperatury nale¿y dokonaæ po pewnym czasie
			void requestUncompensatedTemperature(void);
			// funkcja odczytuje temperaturê nieskompensowan¹
			long readUncompensatedTemperature(void);
			// funkcja wysy³a ¿¹danie pomiaru cisnienia
			// odczyt cisniena nale¿y dokonaæ po pewnym czasie
			void requestUncompensatedPressure(void);
			// funkcja odczytuje cisnienie nieskompensowane
			long readUncompensatedPressure(void);
			// funkcja oblicza skalibrowan¹ temperaturê
			void getCalibratedData(long * temperature, long * pressure, long ut, long up);
			// funkcja przelicza cisnienie na wysokosæ zgodnie
			// ze wzorem atmosfery standardowej
			float getAltitude(long pressure);

	};

#endif
