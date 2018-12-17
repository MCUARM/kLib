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



#ifndef __kHMC5883L_H
#define __kHMC5883L_H

	/*
	 * Includes
	 */
	#include "stm32f4xx.h"
	#include "kI2CDevice.h"


	typedef enum
	{
		HMC5883L_MeasurementAverage_1_Sample	= 0x00,
		HMC5883L_MeasurementAverage_2_Samples	= 0x01,
		HMC5883L_MeasurementAverage_4_Samples	= 0x02,
		HMC5883L_MeasurementAverage_8_Samples	= 0x03
	}HMC5883L_MeasurementAverage_TypeDef;

	typedef enum
	{
		HMC5883L_DataOutputRate_0_dot_75_Hz	= 0x00,
		HMC5883L_DataOutputRate_1_dot_5_Hz	= 0x01,
		HMC5883L_DataOutputRate_3_dot_0_Hz	= 0x02,
		HMC5883L_DataOutputRate_7_dot_5_Hz	= 0x03,
		HMC5883L_DataOutputRate_15_dot_0_Hz	= 0x04,
		HMC5883L_DataOutputRate_30_dot_0_Hz	= 0x05,
		HMC5883L_DataOutputRate_75_dot_0_Hz	= 0x06
	}HMC5883L_DataOutputRate_TypeDef;

	typedef enum
	{
		HMC5883L_MeasurementMode_Normal	= 0x00,
		HMC5883L_MeasurementMode_Positive_Bias	= 0x01,
		HMC5883L_MeasurementMode_Negative_Bias	= 0x02
	}HMC5883L_MeasurementMode_TypeDef;

	typedef enum
	{
		HMC5883L_Gain_0_dot_88_Ga	= 0x00,
		HMC5883L_Gain_1_dot_3_Ga	= 0x01,
		HMC5883L_Gain_1_dot_9_Ga	= 0x02,
		HMC5883L_Gain_2_dot_5_Ga	= 0x03,
		HMC5883L_Gain_4_dot_0_Ga	= 0x04,
		HMC5883L_Gain_4_dot_7_Ga	= 0x05,
		HMC5883L_Gain_5_dot_6_Ga	= 0x06,
		HMC5883L_Gain_8_dot_1_Ga	= 0x07
	}HMC5883L_Gain_TypeDef;

	typedef enum
	{
		HMC5883L_I2C_Speed_UpTo_400_kHz	= 0x00,
		HMC5883L_I2C_Speed_3400_kHz	= 0x01
	}HMC5883L_I2C_Speed_TypeDef;

	typedef enum
	{
		HMC5883L_OperatingMode_Continuous_Measurement	= 0x00,
		HMC5883L_OperatingMode_Single_Measurement	= 0x01,
		HMC5883L_OperatingMode_Idle	= 0x02
	}HMC5883L_OperatingMode_TypeDef;

	typedef struct
	{
		HMC5883L_MeasurementAverage_TypeDef HMC5883L_MeasurementAverage;
		HMC5883L_MeasurementMode_TypeDef HMC5883L_MeasurementMode;
		HMC5883L_DataOutputRate_TypeDef HMC5883L_DataOutputRate;
		HMC5883L_Gain_TypeDef HMC5883L_Gain;
		HMC5883L_I2C_Speed_TypeDef HMC5883L_I2C_Speed;
		HMC5883L_OperatingMode_TypeDef HMC5883L_OperatingMode;
	}HMC5883L_InitTypeDef;

	#define HMC5883L_Address (uint8_t)0x3D

	#define HMC5883L_REGISTER_CRA (uint8_t) 0x00
	#define HMC5883L_REGISTER_CRB (uint8_t) 0x01
	#define HMC5883L_REGISTER_MODE (uint8_t) 0x02
	#define HMC5883L_REGISTER_X_MSB (uint8_t) 0x03
	#define HMC5883L_REGISTER_X_LSB (uint8_t) 0x04
	#define HMC5883L_REGISTER_Z_MSB (uint8_t) 0x05
	#define HMC5883L_REGISTER_Z_LSB (uint8_t) 0x06
	#define HMC5883L_REGISTER_Y_MSB (uint8_t) 0x07
	#define HMC5883L_REGISTER_Y_LSB (uint8_t) 0x08
	#define HMC5883L_REGISTER_SR (uint8_t) 0x09
	#define HMC5883L_REGISTER_ID_A (uint8_t) 0x0A
	#define HMC5883L_REGISTER_ID_B (uint8_t) 0x0B
	#define HMC5883L_REGISTER_ID_C (uint8_t) 0x0C

	//CRA

	#define HMC5883L_CRA_MA0_BitPosition (uint8_t) 0x05
	#define HMC5883L_CRA_MA_Mask (uint8_t) 0x60

	#define HMC5883L_CRA_DO0_BitPosition (uint8_t) 0x02
	#define HMC5883L_CRA_DO_Mask (uint8_t) 0x1C

	#define HMC5883L_CRA_MS0_BitPosition (uint8_t) 0x00
	#define HMC5883L_CRA_MS_Mask (uint8_t) 0x03

	//CRB

	#define HMC5883L_CRB_GN0_BitPosition (uint8_t) 0x05
	#define HMC5883L_CRB_GN_Mask (uint8_t) 0xE0

	//MR

	#define HMC5883L_MR_HS0_BitPosition (uint8_t) 0x07
	#define HMC5883L_MR_HS_Mask (uint8_t) 0x80

	#define HMC5883L_MR_MD0_BitPosition (uint8_t) 0x00
	#define HMC5883L_MR_MD_Mask (uint8_t) 0x03

	//SR

	#define HMC5883L_SR_LOCK_BitPosition (uint8_t) 0x01
	#define HMC5883L_SR_LOCK_Mask (uint8_t) 0x02
	#define HMC5883L_DataLock (uint8_t) 0x02

	#define HMC5883L_SR_RDY_BitPosition (uint8_t) 0x00
	#define HMC5883L_SR_RDY_Mask (uint8_t) 0x01
	#define HMC5883L_DataReady (uint8_t) 0x01




	class kHMC5883L : public kI2CDevice
	{
		private:

			unsigned char HMC5883L_MR_HS_BitState;

		public:

			// funkcja inicjalizuje modu� do pracy
			void init(HMC5883L_InitTypeDef * HMC5883L_InitStruct);
			// funkcja odbiera dane z czujnika
			void readData(int16_t *X, int16_t *Y, int16_t *Z);
			// funkcja wysy�a ��danie pojedynczego pomiaru
			void requestSingleMeasure(void);
	};

#endif
