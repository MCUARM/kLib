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



#ifndef __kBMP085_H
#define __kBMP085_H

	/*
	 * Includes
	 */
	#include "stm32f4xx.h"
	#include "kI2C.h"
	#include "math.h"

	// definicja struktury przechowuj�cej indywidualne parametry kalibruj�ce
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


	class kBMP085 : public kI2C
	{
		public:

			BMP085_CalibValueType BMP085_CALIB_VALUE;
			uint8_t BMP085_OSS;
			long BMP085_BasePressure;

			kBMP085(void);

			void init(void);
			// funkcja wysy�a ��danie pomiaru temperatury
			// odczyt temperatury nale�y dokona� po pewnym czasie
			void requestUncompensatedTemperature(void);
			// funkcja odczytuje temperatur� nieskompensowan�
			long readUncompensatedTemperature(void);
			// funkcja wysy�a ��danie pomiaru cisnienia
			// odczyt cisniena nale�y dokona� po pewnym czasie
			void requestUncompensatedPressure(void);
			// funkcja odczytuje cisnienie nieskompensowane
			long readUncompensatedPressure(void);
			// funkcja oblicza skalibrowan� temperatur�
			void getCalibratedData(long * temperature, long * pressure, long ut, long up);
			// funkcja przelicza cisnienie na wysokos� zgodnie
			// ze wzorem atmosfery standardowej
			float getAltitude(long pressure);

	};

#endif
