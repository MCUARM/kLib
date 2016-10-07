/***********************************************************************************
 *                                                                                 *
 *   kLib - C++ development tools for ARM Cortex-M devices                         *
 *                                                                                 *
 *     Copyright (c) 2016, project author Paweł Zalewski                                          *
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


#ifndef __kMPU6050_H
#define __kMPU6050_H

	/*
	 * Includes
	 */
	#include "stm32f4xx.h"
	#include "kI2CDevice.h"
	#include "kGyroscope.h"
	#include "kAccelerometer.h"

	typedef enum
	{
		MPU6050_ExternalFrameSynchro_DISABLED 		=0x00,
		MPU6050_ExternalFrameSynchro_TEMP_OUT_L 	=0x01,
		MPU6050_ExternalFrameSynchro_GYRO_XOUT_L 	=0x02,
		MPU6050_ExternalFrameSynchro_GYRO_YOUT_L 	=0x03,
		MPU6050_ExternalFrameSynchro_GYRO_ZOUT_L 	=0x04,
		MPU6050_ExternalFrameSynchro_ACCEL_XOUT_L 	=0x05,
		MPU6050_ExternalFrameSynchro_ACCEL_YOUT_L 	=0x06,
		MPU6050_ExternalFrameSynchro_ACCEL_ZOUT_L 	=0x07
	}MPU6050_ExternalFrameSynchro_TypeDef;

	typedef enum
	{
		MPU6050_DigitalLowPassFilterBandwidth_ACC_260Hz_GYRO_256Hz	=0x00,
		MPU6050_DigitalLowPassFilterBandwidth_ACC_184Hz_GYRO_188Hz	=0x01,
		MPU6050_DigitalLowPassFilterBandwidth_ACC_94Hz_GYRO_98Hz	=0x02,
		MPU6050_DigitalLowPassFilterBandwidth_ACC_44Hz_GYRO_42Hz	=0x03,
		MPU6050_DigitalLowPassFilterBandwidth_ACC_21Hz_GYRO_20Hz	=0x04,
		MPU6050_DigitalLowPassFilterBandwidth_ACC_10Hz_GYRO_10Hz	=0x05,
		MPU6050_DigitalLowPassFilterBandwidth_ACC_5Hz_GYRO_5Hz		=0x06
	}MPU6050_DigitalLowPassFilterBandwidth_TypeDef;

	typedef enum
	{
		MPU6050_GyroFullScaleRange_250_deg_per_sec		=0x00,
		MPU6050_GyroFullScaleRange_500_deg_per_sec		=0x01,
		MPU6050_GyroFullScaleRange_1000_deg_per_sec		=0x02,
		MPU6050_GyroFullScaleRange_2000_deg_per_sec		=0x03
	}MPU6050_GyroFullScaleRange_TypeDef;

	typedef enum
	{
		MPU6050_AccFullScaleRange_2g		=0x00,
		MPU6050_AccFullScaleRange_4g		=0x01,
		MPU6050_AccFullScaleRange_8g		=0x02,
		MPU6050_AccFullScaleRange_16g		=0x03
	}MPU6050_AccFullScaleRange_TypeDef;

	typedef enum
	{
		MPU6050_AuxiliaryI2C_ClockSpeed_348kHz		=0x00,
		MPU6050_AuxiliaryI2C_ClockSpeed_333kHz		=0x01,
		MPU6050_AuxiliaryI2C_ClockSpeed_320kHz		=0x02,
		MPU6050_AuxiliaryI2C_ClockSpeed_308kHz		=0x03,
		MPU6050_AuxiliaryI2C_ClockSpeed_296kHz		=0x04,
		MPU6050_AuxiliaryI2C_ClockSpeed_286kHz		=0x05,
		MPU6050_AuxiliaryI2C_ClockSpeed_276kHz		=0x06,
		MPU6050_AuxiliaryI2C_ClockSpeed_267kHz		=0x07,
		MPU6050_AuxiliaryI2C_ClockSpeed_258kHz		=0x08,
		MPU6050_AuxiliaryI2C_ClockSpeed_500kHz		=0x09,
		MPU6050_AuxiliaryI2C_ClockSpeed_471kHz		=0x0A,
		MPU6050_AuxiliaryI2C_ClockSpeed_444kHz		=0x0B,
		MPU6050_AuxiliaryI2C_ClockSpeed_421kHz		=0x0C,
		MPU6050_AuxiliaryI2C_ClockSpeed_400kHz		=0x0D,
		MPU6050_AuxiliaryI2C_ClockSpeed_381kHz		=0x0E,
		MPU6050_AuxiliaryI2C_ClockSpeed_364kHz		=0x0F
	}MPU6050_AuxiliaryI2C_ClockSpeed_TypeDef;

	typedef enum
	{
		MPU6050_ClockSource_Internal_8MHz_OSC		=0x00,
		MPU6050_ClockSource_PLL_GYRO_X_REF			=0x01,
		MPU6050_ClockSource_PLL_GYRO_Y_REF			=0x02,
		MPU6050_ClockSource_PLL_GYRO_Z_REF			=0x03,
		MPU6050_ClockSource_External_32768Hz_REF	=0x04,
		MPU6050_ClockSource_External_19200000Hz_REF	=0x05,
		MPU6050_RESERVED_VALUE_ClockSource			=0x06,
		MPU6050_ClockSource_Stop_Clock				=0x07
	}MPU6050_ClockSource_TypeDef;


	typedef enum
	{
		MPU6050_AccLowPowerMode_WakeUpFreq_1_dot_25_Hz =0x00,
		MPU6050_AccLowPowerMode_WakeUpFreq_5_Hz =0x01,
		MPU6050_AccLowPowerMode_WakeUpFreq_20_Hz =0x02,
		MPU6050_AccLowPowerMode_WakeUpFreq_40_Hz =0x03
	}MPU6050_AccLowPowerMode_WakeUpFreq_TypeDef;

	typedef enum
	{
		MPU6050_InterruptLogicLevel_Active_High = 0x00,
		MPU6050_InterruptLogicLevel_Active_Low = 0x01,
	}MPU6050_InterruptLogicLevel_TypeDef;

	typedef enum
	{
		MPU6050_ExternalFrameSynchroLogicLevel_Active_High = 0x00,
		MPU6050_ExternalFrameSynchroLogicLevel_Active_Low = 0x01,
	}MPU6050_ExternalFrameSynchroLogicLevel_TypeDef;

	typedef enum
	{
		MPU6050_InterruptOutputType_Push_Pull = 0x00,
		MPU6050_InterruptOutputType_Open_Drain = 0x01,
	}MPU6050_InterruptOutputType_TypeDef;

	typedef enum
	{
		MPU6050_InterruptSignalLatch_DISABLE = 0x00,
		MPU6050_InterruptSignalLatch_ENABLE = 0x01,
	}MPU6050_InterruptSignalLatch_TypeDef;

	typedef enum
	{
		MPU6050_InterruptClearFlagCondition_READ_INT_STATUS = 0x00,
		MPU6050_InterruptClearFlagCondition_READ_ANY_REGISTER = 0x01,
	}MPU6050_InterruptClearFlagCondition_TypeDef;

	typedef enum
	{
		MPU6050_AuxiliaryI2C_MultiMaster_DISABLE = 0x00,
		MPU6050_AuxiliaryI2C_MultiMaster_ENABLE = 0x01,
	}MPU6050_AuxiliaryI2C_MultiMaster_TypeDef;


	typedef enum
	{
		MPU6050_AuxiliaryI2C_StoppingTransmission_ALLOW_RESTART = 0x00,
		MPU6050_AuxiliaryI2C_StoppingTransmission_STOP_AND_START = 0x01,
	}MPU6050_AuxiliaryI2C_StoppingTransmission_TypeDef;


	typedef enum
	{
		MPU6050_Slave_0 = 0x00,
		MPU6050_Slave_1 = 0x01,
		MPU6050_Slave_2 = 0x02,
		MPU6050_Slave_3 = 0x03,
		MPU6050_Slave_4 = 0x04
	}MPU6050_Slave_TypeDef;

	typedef enum
	{
		MPU6050_SlaveTransferDirection_WRTIE = 0x00,
		MPU6050_SlaveTransferDirection_READ = 0x01
	}MPU6050_SlaveTransferDirection_TypeDef;

	typedef enum
	{
		MPU6050_SlaveByteSwapping_DISABLE = 0x00,
		MPU6050_SlaveByteSwapping_ENABLE = 0x01
	}MPU6050_SlaveByteSwapping_TypeDef;

	typedef enum
	{
		MPU6050_SlaveSendRegisterAddress_ENABLE = 0x00,
		MPU6050_SlaveSendRegisterAddress_DISABLE = 0x01
	}MPU6050_SlaveSendRegisterAddress_TypeDef;

	typedef enum
	{
		MPU6050_SlaveRecievedBytesGroupingOrder_EVEN_then_ODD = 0x00,
		MPU6050_SlaveRecievedBytesGroupingOrder_ODD_then_EVEN = 0x01
	}MPU6050_SlaveRecievedBytesGroupingOrder_TypeDef;

	typedef enum
	{
		MPU6050_SlaveDecreasedAccessingRate_DISABLE = 0x00,
		MPU6050_SlaveDecreasedAccessingRate_ENABLE = 0x01
	}MPU6050_SlaveDecreasedAccessingRate_TypeDef;

	typedef enum
	{
		MPU6050_DataReadyWaitForExternalSesnor_DISABLE = 0x00,
		MPU6050_DataReadyWaitForExternalSesnor_ENABLE = 0x01
	}MPU6050_DataReadyWaitForExternalSesnor_TypeDef;

	typedef enum
	{
		MPU6050_ExternalSensorDataShadowingDelay_DISABLE = 0x00,
		MPU6050_ExternalSensorDataShadowingDelay_ENABLE = 0x01
	}MPU6050_ExternalSensorDataShadowingDelay_TypeDef;

	typedef struct
	{
		uint8_t SampleRateDivider;
		MPU6050_GyroFullScaleRange_TypeDef MPU6050_GyroFullScaleRange;
		MPU6050_AccFullScaleRange_TypeDef MPU6050_AccFullScaleRange;
		MPU6050_DigitalLowPassFilterBandwidth_TypeDef MPU6050_DigitalLowPassFilterBandwidth;
		uint8_t MPU6050_PowerOnSensor;
	}MPU6050_SensorsInitStruct_TypeDef;

	typedef struct
	{
		MPU6050_ExternalFrameSynchro_TypeDef MPU6050_ExternalFrameSynchro;
		MPU6050_ExternalFrameSynchroLogicLevel_TypeDef MPU6050_ExternalFrameSynchroLogicLevel;
		uint8_t MPU6050_MotionDetectionThreshold;
		MPU6050_InterruptLogicLevel_TypeDef MPU6050_InterruptLogicLevel;
		MPU6050_InterruptOutputType_TypeDef MPU6050_InterruptOutputType;
		MPU6050_InterruptSignalLatch_TypeDef MPU6050_InterruptSignalLatch;
		MPU6050_InterruptClearFlagCondition_TypeDef MPU6050_InterruptClearFlagCondition;
		uint8_t MPU6050_EnableInterrupt;
		MPU6050_DataReadyWaitForExternalSesnor_TypeDef MPU6050_DataReadyWaitForExternalSesnor;
	}MPU6050_InterruptsInitStruct_TypeDef;

	typedef struct
	{
		MPU6050_AuxiliaryI2C_ClockSpeed_TypeDef MPU6050_AuxiliaryI2C_ClockSpeed;
		MPU6050_AuxiliaryI2C_MultiMaster_TypeDef MPU6050_AuxiliaryI2C_MultiMaster;
		MPU6050_AuxiliaryI2C_StoppingTransmission_TypeDef MPU6050_AuxiliaryI2C_StoppingTransmission;
		MPU6050_ExternalSensorDataShadowingDelay_TypeDef MPU6050_ExternalSensorDataShadowingDelay;
	}MPU6050_AuxiliaryI2C_InitStruct_TypeDef;



	typedef struct
	{
		MPU6050_Slave_TypeDef MPU6050_Slave;
		MPU6050_SlaveTransferDirection_TypeDef MPU6050_SlaveTransferDirection;
		uint8_t MPU6050_Slave7bitAddress;
		uint8_t MPU6050_SlaveStartingRegisterAddress;
		uint8_t MPU6050_SlaveBytesToTransfer;
		MPU6050_SlaveByteSwapping_TypeDef MPU6050_SlaveByteSwapping;
		MPU6050_SlaveSendRegisterAddress_TypeDef MPU6050_SlaveSendRegisterAddress;
		MPU6050_SlaveRecievedBytesGroupingOrder_TypeDef MPU6050_SlaveRecievedBytesGroupingOrder;
		MPU6050_SlaveDecreasedAccessingRate_TypeDef MPU6050_SlaveDecreasedAccessingRate;
	}MPU6050_SlaveInitStruct_TypeDef;

	typedef struct
	{
	      int16_t ACC_X;
	      int16_t ACC_Y;
	      int16_t ACC_Z;
	      int16_t TEMP;
	      int16_t GYRO_X;
	      int16_t GYRO_Y;
	      int16_t GYRO_Z;
	}MPU6050_MeasurementsStorage_TypeDef;

	typedef struct
	{
	      float ACC_X;
	      float ACC_Y;
	      float ACC_Z;
	      float TEMP;
	      float GYRO_X;
	      float GYRO_Y;
	      float GYRO_Z;
	}MPU6050_MeasurementsPhysicalUnitsStorage_TypeDef;

	// DEFINICJE REJESTR�W


   #define MPU6050_REGISTER_SELF_TEST_X			 (uint8_t)0x0D     // R/W access
   #define MPU6050_REGISTER_SELF_TEST_Y			 (uint8_t)0x0E     // R/W access
   #define MPU6050_REGISTER_SELF_TEST_Z			 (uint8_t)0x0F     // R/W access
   #define MPU6050_REGISTER_SELF_TEST_A			 (uint8_t)0x10     // R/W access
   #define MPU6050_REGISTER_SMPLRT_DIV			 (uint8_t)0x19     // R/W access
   #define MPU6050_REGISTER_CONFIG			 (uint8_t)0x1A     // R/W access
   #define MPU6050_REGISTER_GYRO_CONFIG			 (uint8_t)0x1B     // R/W access
   #define MPU6050_REGISTER_ACCEL_CONFIG			 (uint8_t)0x1C     // R/W access
   #define MPU6050_REGISTER_MOT_THR			 (uint8_t)0x1F     // R/W access
   #define MPU6050_REGISTER_FIFO_EN			 (uint8_t)0x23     // R/W access
   #define MPU6050_REGISTER_I2C_MST_CTRL			 (uint8_t)0x24     // R/W access
   #define MPU6050_REGISTER_I2C_SLV0_ADDR			 (uint8_t)0x25     // R/W access
   #define MPU6050_REGISTER_I2C_SLV0_REG			 (uint8_t)0x26     // R/W access
   #define MPU6050_REGISTER_I2C_SLV0_CTRL			 (uint8_t)0x27     // R/W access
   #define MPU6050_REGISTER_I2C_SLV1_ADDR			 (uint8_t)0x28     // R/W access
   #define MPU6050_REGISTER_I2C_SLV1_REG			 (uint8_t)0x29     // R/W access
   #define MPU6050_REGISTER_I2C_SLV1_CTRL			 (uint8_t)0x2A     // R/W access
   #define MPU6050_REGISTER_I2C_SLV2_ADDR			 (uint8_t)0x2B     // R/W access
   #define MPU6050_REGISTER_I2C_SLV2_REG			 (uint8_t)0x2C     // R/W access
   #define MPU6050_REGISTER_I2C_SLV2_CTRL			 (uint8_t)0x2D     // R/W access
   #define MPU6050_REGISTER_I2C_SLV3_ADDR			 (uint8_t)0x2E     // R/W access
   #define MPU6050_REGISTER_I2C_SLV3_REG			 (uint8_t)0x2F     // R/W access
   #define MPU6050_REGISTER_I2C_SLV3_CTRL			 (uint8_t)0x30     // R/W access
   #define MPU6050_REGISTER_I2C_SLV4_ADDR			 (uint8_t)0x31     // R/W access
   #define MPU6050_REGISTER_I2C_SLV4_REG			 (uint8_t)0x32     // R/W access
   #define MPU6050_REGISTER_I2C_SLV4_DO			 (uint8_t)0x33     // R/W access
   #define MPU6050_REGISTER_I2C_SLV4_CTRL			 (uint8_t)0x34     // R/W access
   #define MPU6050_REGISTER_I2C_SLV4_DI			 (uint8_t)0x35     // R access
   #define MPU6050_REGISTER_I2C_MST_STATUS			 (uint8_t)0x36     // R access
   #define MPU6050_REGISTER_INT_PIN_CFG			 (uint8_t)0x37     // R/W access
   #define MPU6050_REGISTER_INT_ENABLE			 (uint8_t)0x38     // R/W access
   #define MPU6050_REGISTER_INT_STATUS			 (uint8_t)0x3A     // R access
   #define MPU6050_REGISTER_ACCEL_XOUT_H			 (uint8_t)0x3B     // R access
   #define MPU6050_REGISTER_ACCEL_XOUT_L			 (uint8_t)0x3C     // R access
   #define MPU6050_REGISTER_ACCEL_YOUT_H			 (uint8_t)0x3D     // R access
   #define MPU6050_REGISTER_ACCEL_YOUT_L			 (uint8_t)0x3E     // R access
   #define MPU6050_REGISTER_ACCEL_ZOUT_H			 (uint8_t)0x3F     // R access
   #define MPU6050_REGISTER_ACCEL_ZOUT_L			 (uint8_t)0x40     // R access
   #define MPU6050_REGISTER_TEMP_OUT_H			 (uint8_t)0x41     // R access
   #define MPU6050_REGISTER_TEMP_OUT_L			 (uint8_t)0x42     // R access
   #define MPU6050_REGISTER_GYRO_XOUT_H			 (uint8_t)0x43     // R access
   #define MPU6050_REGISTER_GYRO_XOUT_L			 (uint8_t)0x44     // R access
   #define MPU6050_REGISTER_GYRO_YOUT_H			 (uint8_t)0x45     // R access
   #define MPU6050_REGISTER_GYRO_YOUT_L			 (uint8_t)0x46     // R access
   #define MPU6050_REGISTER_GYRO_ZOUT_H			 (uint8_t)0x47     // R access
   #define MPU6050_REGISTER_GYRO_ZOUT_L			 (uint8_t)0x48     // R access
   #define MPU6050_REGISTER_EXT_SENS_DATA_00			 (uint8_t)0x49     // R access
   #define MPU6050_REGISTER_EXT_SENS_DATA_01			 (uint8_t)0x4A     // R access
   #define MPU6050_REGISTER_EXT_SENS_DATA_02			 (uint8_t)0x4B     // R access
   #define MPU6050_REGISTER_EXT_SENS_DATA_03			 (uint8_t)0x4C     // R access
   #define MPU6050_REGISTER_EXT_SENS_DATA_04			 (uint8_t)0x4D     // R access
   #define MPU6050_REGISTER_EXT_SENS_DATA_05			 (uint8_t)0x4E     // R access
   #define MPU6050_REGISTER_EXT_SENS_DATA_06			 (uint8_t)0x4F     // R access
   #define MPU6050_REGISTER_EXT_SENS_DATA_07			 (uint8_t)0x50     // R access
   #define MPU6050_REGISTER_EXT_SENS_DATA_08			 (uint8_t)0x51     // R access
   #define MPU6050_REGISTER_EXT_SENS_DATA_09			 (uint8_t)0x52     // R access
   #define MPU6050_REGISTER_EXT_SENS_DATA_10			 (uint8_t)0x53     // R access
   #define MPU6050_REGISTER_EXT_SENS_DATA_11			 (uint8_t)0x54     // R access
   #define MPU6050_REGISTER_EXT_SENS_DATA_12			 (uint8_t)0x55     // R access
   #define MPU6050_REGISTER_EXT_SENS_DATA_13			 (uint8_t)0x56     // R access
   #define MPU6050_REGISTER_EXT_SENS_DATA_14			 (uint8_t)0x57     // R access
   #define MPU6050_REGISTER_EXT_SENS_DATA_15			 (uint8_t)0x58     // R access
   #define MPU6050_REGISTER_EXT_SENS_DATA_16			 (uint8_t)0x59     // R access
   #define MPU6050_REGISTER_EXT_SENS_DATA_17			 (uint8_t)0x5A     // R access
   #define MPU6050_REGISTER_EXT_SENS_DATA_18			 (uint8_t)0x5B     // R access
   #define MPU6050_REGISTER_EXT_SENS_DATA_19			 (uint8_t)0x5C     // R access
   #define MPU6050_REGISTER_EXT_SENS_DATA_20			 (uint8_t)0x5D     // R access
   #define MPU6050_REGISTER_EXT_SENS_DATA_21			 (uint8_t)0x5E     // R access
   #define MPU6050_REGISTER_EXT_SENS_DATA_22			 (uint8_t)0x5F     // R access
   #define MPU6050_REGISTER_EXT_SENS_DATA_23			 (uint8_t)0x60     // R access
   #define MPU6050_REGISTER_I2C_SLV0_D0			 (uint8_t)0x63     // R/W access
   #define MPU6050_REGISTER_I2C_SLV1_D0			 (uint8_t)0x64     // R/W access
   #define MPU6050_REGISTER_I2C_SLV2_D0			 (uint8_t)0x65     // R/W access
   #define MPU6050_REGISTER_I2C_SLV3_D0			 (uint8_t)0x66     // R/W access
   #define MPU6050_REGISTER_I2CMSTDELAYCTRL			 (uint8_t)0x67     // R/W access
   #define MPU6050_REGISTER_SIGNALPATHRESET			 (uint8_t)0x68     // R/W access
   #define MPU6050_REGISTER_MOT_DETECT_CTRL			 (uint8_t)0x69     // R/W access
   #define MPU6050_REGISTER_USER_CTRL			 (uint8_t)0x6A     // R/W access
   #define MPU6050_REGISTER_PWR_MGMT_1			 (uint8_t)0x6B     // R/W access
   #define MPU6050_REGISTER_PWR_MGMT_2			 (uint8_t)0x6C     // R/W access
   #define MPU6050_REGISTER_FIFO_COUNTH			 (uint8_t)0x72     // R/W access
   #define MPU6050_REGISTER_FIFO_COUNTL			 (uint8_t)0x73     // R/W access
   #define MPU6050_REGISTER_FIFO_R_W			 (uint8_t)0x74     // R/W access
   #define MPU6050_REGISTER_WHO_AM_I			 (uint8_t)0x75     // R access



   // SELF_TEST_X



   #define MPU6050_XA_TEST_Bit0Position			 (uint8_t)5
   #define MPU6050_XA_TEST_Mask				 (uint8_t)0xE0
   #define MPU6050_XG_TEST_Bit0Position			 (uint8_t)0
   #define MPU6050_XG_TEST_Mask				 (uint8_t)0x1F



   // SELF_TEST_Y



   #define MPU6050_YA_TEST_Bit0Position			 (uint8_t)5
   #define MPU6050_YA_TEST_Mask				 (uint8_t)0xE0
   #define MPU6050_YG_TEST_Bit0Position			 (uint8_t)0
   #define MPU6050_YG_TEST_Mask				 (uint8_t)0x1F



   // SELF_TEST_Z



   #define MPU6050_ZA_TEST_Bit0Position			 (uint8_t)5
   #define MPU6050_ZA_TEST_Mask				 (uint8_t)0xE0
   #define MPU6050_ZG_TEST_Bit0Position			 (uint8_t)0
   #define MPU6050_ZG_TEST_Mask				 (uint8_t)0x1F



   // SELF_TEST_A



   #define MPU6050_XA_TEST_L_Bit0Position			 (uint8_t)4
   #define MPU6050_XA_TEST_L_Mask				 (uint8_t)0x30
   #define MPU6050_YA_TEST_L_Bit0Position			 (uint8_t)2
   #define MPU6050_YA_TEST_L_Mask				 (uint8_t)0x0C
   #define MPU6050_ZA_TEST_L_Bit0Position			 (uint8_t)0
   #define MPU6050_ZA_TEST_L_Mask				 (uint8_t)0x03



   // SMPLRT_DIV



   #define MPU6050_SMPLRT_DIV_Bit0Position			 (uint8_t)0
   #define MPU6050_SMPLRT_DIV_Mask				 (uint8_t)0xFF



   // CONFIG



   #define MPU6050_EXT_SYNC_SET_Bit0Position			 (uint8_t)3
   #define MPU6050_EXT_SYNC_SET_Mask				 (uint8_t)0x38
   #define MPU6050_DLPF_CFG_Bit0Position			 (uint8_t)0
   #define MPU6050_DLPF_CFG_Mask				 (uint8_t)0x07



   // GYRO_CONFIG



   #define MPU6050_FS_SEL_Bit0Position			 (uint8_t)3
   #define MPU6050_FS_SEL_Mask				 (uint8_t)0x18



   // ACCEL_CONFIG



   #define MPU6050_XA_ST_Bit0Position			 (uint8_t)7
   #define MPU6050_XA_ST_Mask				 (uint8_t)0x80
   #define MPU6050_YA_ST_Bit0Position			 (uint8_t)6
   #define MPU6050_YA_ST_Mask				 (uint8_t)0x40
   #define MPU6050_ZA_ST_Bit0Position			 (uint8_t)5
   #define MPU6050_ZA_ST_Mask				 (uint8_t)0x20
   #define MPU6050_AFS_SEL_Bit0Position			 (uint8_t)3
   #define MPU6050_AFS_SEL_Mask				 (uint8_t)0x18



   // MOT_THR



   #define MPU6050_MOT_THR_Bit0Position			 (uint8_t)0
   #define MPU6050_MOT_THR_Mask				 (uint8_t)0xFF



   // FIFO_EN



   #define MPU6050_TEMP_FIFO_EN_Bit0Position			 (uint8_t)7
   #define MPU6050_TEMP_FIFO_EN_Mask				 (uint8_t)0x80
   #define MPU6050_XG_FIFO_EN_Bit0Position			 (uint8_t)6
   #define MPU6050_XG_FIFO_EN_Mask				 (uint8_t)0x40
   #define MPU6050_YG_FIFO_EN_Bit0Position			 (uint8_t)5
   #define MPU6050_YG_FIFO_EN_Mask				 (uint8_t)0x20
   #define MPU6050_ZG_FIFO_EN_Bit0Position			 (uint8_t)4
   #define MPU6050_ZG_FIFO_EN_Mask				 (uint8_t)0x10
   #define MPU6050_ACCEL_FIFO_EN_Bit0Position			 (uint8_t)3
   #define MPU6050_ACCEL_FIFO_EN_Mask				 (uint8_t)0x08
   #define MPU6050_SLV2_FIFO_EN_Bit0Position			 (uint8_t)2
   #define MPU6050_SLV2_FIFO_EN_Mask				 (uint8_t)0x04
   #define MPU6050_SLV1_FIFO_EN_Bit0Position			 (uint8_t)1
   #define MPU6050_SLV1_FIFO_EN_Mask				 (uint8_t)0x02
   #define MPU6050_SLV0_FIFO_EN_Bit0Position			 (uint8_t)0
   #define MPU6050_SLV0_FIFO_EN_Mask				 (uint8_t)0x01



   // I2C_MST_CTRL



   #define MPU6050_MULT_MST_EN_Bit0Position			 (uint8_t)7
   #define MPU6050_MULT_MST_EN_Mask				 (uint8_t)0x80
   #define MPU6050_WAIT_FOR_ES_Bit0Position			 (uint8_t)6
   #define MPU6050_WAIT_FOR_ES_Mask				 (uint8_t)0x40
   #define MPU6050_SLV3_FIFO_EN_Bit0Position			 (uint8_t)5
   #define MPU6050_SLV3_FIFO_EN_Mask				 (uint8_t)0x20
   #define MPU6050_I2CMST_P_NSR_Bit0Position			 (uint8_t)4
   #define MPU6050_I2CMST_P_NSR_Mask				 (uint8_t)0x10
   #define MPU6050_I2C_MST_CLK_Bit0Position			 (uint8_t)0
   #define MPU6050_I2C_MST_CLK_Mask				 (uint8_t)0x0F



   // I2C_SLV0_ADDR



   #define MPU6050_I2CSLV0_RW_Bit0Position			 (uint8_t)7
   #define MPU6050_I2CSLV0_RW_Mask				 (uint8_t)0x80
   #define MPU6050_I2C_SLV0_ADDR_Bit0Position			 (uint8_t)0
   #define MPU6050_I2C_SLV0_ADDR_Mask				 (uint8_t)0x7F



   // I2C_SLV0_REG



   #define MPU6050_I2C_SLV0_REG_Bit0Position			 (uint8_t)0
   #define MPU6050_I2C_SLV0_REG_Mask				 (uint8_t)0xFF



   // I2C_SLV0_CTRL



   #define MPU6050_I2CSLV0_EN_Bit0Position			 (uint8_t)7
   #define MPU6050_I2CSLV0_EN_Mask				 (uint8_t)0x80
   #define MPU6050_I2CSLV0_BYTE_SW_Bit0Position			 (uint8_t)6
   #define MPU6050_I2CSLV0_BYTE_SW_Mask				 (uint8_t)0x40
   #define MPU6050_I2CSLV0_REG_DIS_Bit0Position			 (uint8_t)5
   #define MPU6050_I2CSLV0_REG_DIS_Mask				 (uint8_t)0x20
   #define MPU6050_I2CSLV0_GRP_Bit0Position			 (uint8_t)4
   #define MPU6050_I2CSLV0_GRP_Mask				 (uint8_t)0x10
   #define MPU6050_I2C_SLV0_LEN_Bit0Position			 (uint8_t)0
   #define MPU6050_I2C_SLV0_LEN_Mask				 (uint8_t)0x0F



   // I2C_SLV1_ADDR



   #define MPU6050_I2CSLV1_RW_Bit0Position			 (uint8_t)7
   #define MPU6050_I2CSLV1_RW_Mask				 (uint8_t)0x80
   #define MPU6050_I2C_SLV1_ADDR_Bit0Position			 (uint8_t)0
   #define MPU6050_I2C_SLV1_ADDR_Mask				 (uint8_t)0x7F



   // I2C_SLV1_REG



   #define MPU6050_I2C_SLV1_REG_Bit0Position			 (uint8_t)0
   #define MPU6050_I2C_SLV1_REG_Mask				 (uint8_t)0xFF



   // I2C_SLV1_CTRL



   #define MPU6050_I2CSLV1_EN_Bit0Position			 (uint8_t)7
   #define MPU6050_I2CSLV1_EN_Mask				 (uint8_t)0x80
   #define MPU6050_I2CSLV1_BYTE_SW_Bit0Position			 (uint8_t)6
   #define MPU6050_I2CSLV1_BYTE_SW_Mask				 (uint8_t)0x40
   #define MPU6050_I2CSLV1_REG_DIS_Bit0Position			 (uint8_t)5
   #define MPU6050_I2CSLV1_REG_DIS_Mask				 (uint8_t)0x20
   #define MPU6050_I2CSLV1_GRP_Bit0Position			 (uint8_t)4
   #define MPU6050_I2CSLV1_GRP_Mask				 (uint8_t)0x10
   #define MPU6050_I2C_SLV1_LEN_Bit0Position			 (uint8_t)0
   #define MPU6050_I2C_SLV1_LEN_Mask				 (uint8_t)0x0F



   // I2C_SLV2_ADDR



   #define MPU6050_I2CSLV2_RW_Bit0Position			 (uint8_t)7
   #define MPU6050_I2CSLV2_RW_Mask				 (uint8_t)0x80
   #define MPU6050_I2C_SLV2_ADDR_Bit0Position			 (uint8_t)0
   #define MPU6050_I2C_SLV2_ADDR_Mask				 (uint8_t)0x7F



   // I2C_SLV2_REG



   #define MPU6050_I2C_SLV2_REG_Bit0Position			 (uint8_t)0
   #define MPU6050_I2C_SLV2_REG_Mask				 (uint8_t)0xFF



   // I2C_SLV2_CTRL



   #define MPU6050_I2CSLV2_EN_Bit0Position			 (uint8_t)7
   #define MPU6050_I2CSLV2_EN_Mask				 (uint8_t)0x80
   #define MPU6050_I2CSLV2_BYTE_SW_Bit0Position			 (uint8_t)6
   #define MPU6050_I2CSLV2_BYTE_SW_Mask				 (uint8_t)0x40
   #define MPU6050_I2CSLV2_REG_DIS_Bit0Position			 (uint8_t)5
   #define MPU6050_I2CSLV2_REG_DIS_Mask				 (uint8_t)0x20
   #define MPU6050_I2CSLV2_GRP_Bit0Position			 (uint8_t)4
   #define MPU6050_I2CSLV2_GRP_Mask				 (uint8_t)0x10
   #define MPU6050_I2C_SLV2_LEN_Bit0Position			 (uint8_t)0
   #define MPU6050_I2C_SLV2_LEN_Mask				 (uint8_t)0x0F



   // I2C_SLV3_ADDR



   #define MPU6050_I2CSLV3_RW_Bit0Position			 (uint8_t)7
   #define MPU6050_I2CSLV3_RW_Mask				 (uint8_t)0x80
   #define MPU6050_I2C_SLV3_ADDR_Bit0Position			 (uint8_t)0
   #define MPU6050_I2C_SLV3_ADDR_Mask				 (uint8_t)0x7F



   // I2C_SLV3_REG



   #define MPU6050_I2C_SLV3_REG_Bit0Position			 (uint8_t)0
   #define MPU6050_I2C_SLV3_REG_Mask				 (uint8_t)0xFF



   // I2C_SLV3_CTRL



   #define MPU6050_I2CSLV3_EN_Bit0Position			 (uint8_t)7
   #define MPU6050_I2CSLV3_EN_Mask				 (uint8_t)0x80
   #define MPU6050_I2CSLV3_BYTE_SW_Bit0Position			 (uint8_t)6
   #define MPU6050_I2CSLV3_BYTE_SW_Mask				 (uint8_t)0x40
   #define MPU6050_I2CSLV3_REG_DIS_Bit0Position			 (uint8_t)5
   #define MPU6050_I2CSLV3_REG_DIS_Mask				 (uint8_t)0x20
   #define MPU6050_I2CSLV3_GRP_Bit0Position			 (uint8_t)4
   #define MPU6050_I2CSLV3_GRP_Mask				 (uint8_t)0x10
   #define MPU6050_I2C_SLV3_LEN_Bit0Position			 (uint8_t)0
   #define MPU6050_I2C_SLV3_LEN_Mask				 (uint8_t)0x0F



   // I2C_SLV4_ADDR



   #define MPU6050_I2CSLV4_RW_Bit0Position			 (uint8_t)7
   #define MPU6050_I2CSLV4_RW_Mask				 (uint8_t)0x80
   #define MPU6050_I2C_SLV4_ADDR_Bit0Position			 (uint8_t)0
   #define MPU6050_I2C_SLV4_ADDR_Mask				 (uint8_t)0x7F



   // I2C_SLV4_REG



   #define MPU6050_I2C_SLV4_REG_Bit0Position			 (uint8_t)0
   #define MPU6050_I2C_SLV4_REG_Mask				 (uint8_t)0xFF



   // I2C_SLV4_DO



   #define MPU6050_I2C_SLV4_DO_Bit0Position			 (uint8_t)0
   #define MPU6050_I2C_SLV4_DO_Mask				 (uint8_t)0xFF



   // I2C_SLV4_CTRL



   #define MPU6050_I2CSLV4_EN_Bit0Position			 (uint8_t)7
   #define MPU6050_I2CSLV4_EN_Mask				 (uint8_t)0x80
   #define MPU6050_I2CSLV4_INT_EN_Bit0Position			 (uint8_t)6
   #define MPU6050_I2CSLV4_INT_EN_Mask				 (uint8_t)0x40
   #define MPU6050_I2CSLV4_REG_DIS_Bit0Position			 (uint8_t)5
   #define MPU6050_I2CSLV4_REG_DIS_Mask				 (uint8_t)0x20
   #define MPU6050_I2C_MST_DLY_Bit0Position			 (uint8_t)0
   #define MPU6050_I2C_MST_DLY_Mask				 (uint8_t)0x1F



   // I2C_SLV4_DI



   #define MPU6050_I2C_SLV4_DI_Bit0Position			 (uint8_t)0
   #define MPU6050_I2C_SLV4_DI_Mask				 (uint8_t)0xFF



   // I2C_MST_STATUS



   #define MPU6050_PASSTHROUGH_Bit0Position			 (uint8_t)7
   #define MPU6050_PASSTHROUGH_Mask				 (uint8_t)0x80
   #define MPU6050_I2CSLV4_DONE_Bit0Position			 (uint8_t)6
   #define MPU6050_I2CSLV4_DONE_Mask				 (uint8_t)0x40
   #define MPU6050_I2CLOST_ARB_Bit0Position			 (uint8_t)5
   #define MPU6050_I2CLOST_ARB_Mask				 (uint8_t)0x20
   #define MPU6050_I2CSLV4_NACK_Bit0Position			 (uint8_t)4
   #define MPU6050_I2CSLV4_NACK_Mask				 (uint8_t)0x10
   #define MPU6050_I2CSLV3_NACK_Bit0Position			 (uint8_t)3
   #define MPU6050_I2CSLV3_NACK_Mask				 (uint8_t)0x08
   #define MPU6050_I2CSLV2_NACK_Bit0Position			 (uint8_t)2
   #define MPU6050_I2CSLV2_NACK_Mask				 (uint8_t)0x04
   #define MPU6050_I2CSLV1_NACK_Bit0Position			 (uint8_t)1
   #define MPU6050_I2CSLV1_NACK_Mask				 (uint8_t)0x02
   #define MPU6050_I2CSLV0_NACK_Bit0Position			 (uint8_t)0
   #define MPU6050_I2CSLV0_NACK_Mask				 (uint8_t)0x01



   // INT_PIN_CFG



   #define MPU6050_INT_LEVEL_Bit0Position			 (uint8_t)7
   #define MPU6050_INT_LEVEL_Mask				 (uint8_t)0x80
   #define MPU6050_INT_OPEN_Bit0Position			 (uint8_t)6
   #define MPU6050_INT_OPEN_Mask				 (uint8_t)0x40
   #define MPU6050_LATCH_INT_EN_Bit0Position			 (uint8_t)5
   #define MPU6050_LATCH_INT_EN_Mask				 (uint8_t)0x20
   #define MPU6050_INT_RD_CLEAR_Bit0Position			 (uint8_t)4
   #define MPU6050_INT_RD_CLEAR_Mask				 (uint8_t)0x10
   #define MPU6050_FSYNC_INT_LEVEL_Bit0Position			 (uint8_t)3
   #define MPU6050_FSYNC_INT_LEVEL_Mask				 (uint8_t)0x08
   #define MPU6050_FSYNC_INT_EN_Bit0Position			 (uint8_t)2
   #define MPU6050_FSYNC_INT_EN_Mask				 (uint8_t)0x04
   #define MPU6050_I2CBYPASS_EN_Bit0Position			 (uint8_t)1
   #define MPU6050_I2CBYPASS_EN_Mask				 (uint8_t)0x02



   // INT_ENABLE



   #define MPU6050_MOT_EN_Bit0Position			 (uint8_t)6
   #define MPU6050_MOT_EN_Mask				 (uint8_t)0x40
   #define MPU6050_FIFOOFLOW_EN_Bit0Position			 (uint8_t)4
   #define MPU6050_FIFOOFLOW_EN_Mask				 (uint8_t)0x10
   #define MPU6050_I2CMST_INT_EN_Bit0Position			 (uint8_t)3
   #define MPU6050_I2CMST_INT_EN_Mask				 (uint8_t)0x08
   #define MPU6050_DATA_RDY_EN_Bit0Position			 (uint8_t)0
   #define MPU6050_DATA_RDY_EN_Mask				 (uint8_t)0x01



   // INT_STATUS



   #define MPU6050_MOT_INT_Bit0Position			 (uint8_t)6
   #define MPU6050_MOT_INT_Mask				 (uint8_t)0x40
   #define MPU6050_FIFOOFLOWINT_Bit0Position			 (uint8_t)4
   #define MPU6050_FIFOOFLOWINT_Mask				 (uint8_t)0x10
   #define MPU6050_I2CMST_INT_Bit0Position			 (uint8_t)3
   #define MPU6050_I2CMST_INT_Mask				 (uint8_t)0x08
   #define MPU6050_DATA_RDY_INT_Bit0Position			 (uint8_t)0
   #define MPU6050_DATA_RDY_INT_Mask				 (uint8_t)0x01



   // ACCEL_XOUT_H



   #define MPU6050_ACCEL_X0UT_Bit0Position			 (uint8_t)0
   #define MPU6050_ACCEL_X0UT_Mask				 (uint8_t)0xFF



   // ACCEL_XOUT_L



   #define MPU6050_ACCEL_X0UT_Bit0Position			 (uint8_t)0
   #define MPU6050_ACCEL_X0UT_Mask				 (uint8_t)0xFF



   // ACCEL_YOUT_H



   #define MPU6050_ACCEL_Y0UT_Bit0Position			 (uint8_t)0
   #define MPU6050_ACCEL_Y0UT_Mask				 (uint8_t)0xFF



   // ACCEL_YOUT_L



   #define MPU6050_ACCEL_Y0UT_Bit0Position			 (uint8_t)0
   #define MPU6050_ACCEL_Y0UT_Mask				 (uint8_t)0xFF



   // ACCEL_ZOUT_H



   #define MPU6050_ACCEL_Z0UT_Bit0Position			 (uint8_t)0
   #define MPU6050_ACCEL_Z0UT_Mask				 (uint8_t)0xFF



   // ACCEL_ZOUT_L



   #define MPU6050_ACCEL_Z0UT_Bit0Position			 (uint8_t)0
   #define MPU6050_ACCEL_Z0UT_Mask				 (uint8_t)0xFF



   // TEMP_OUT_H



   #define MPU6050_TEMP_0UT_Bit0Position			 (uint8_t)0
   #define MPU6050_TEMP_0UT_Mask				 (uint8_t)0xFF



   // TEMP_OUT_L



   #define MPU6050_TEMP_0UT_Bit0Position			 (uint8_t)0
   #define MPU6050_TEMP_0UT_Mask				 (uint8_t)0xFF



   // GYRO_XOUT_H



   #define MPU6050_GYR0_X0UT_Bit0Position			 (uint8_t)0
   #define MPU6050_GYR0_X0UT_Mask				 (uint8_t)0xFF



   // GYRO_XOUT_L



   #define MPU6050_GYR0_X0UT_Bit0Position			 (uint8_t)0
   #define MPU6050_GYR0_X0UT_Mask				 (uint8_t)0xFF



   // GYRO_YOUT_H



   #define MPU6050_GYR0_Y0UT_Bit0Position			 (uint8_t)0
   #define MPU6050_GYR0_Y0UT_Mask				 (uint8_t)0xFF



   // GYRO_YOUT_L



   #define MPU6050_GYR0_Y0UT_Bit0Position			 (uint8_t)0
   #define MPU6050_GYR0_Y0UT_Mask				 (uint8_t)0xFF



   // GYRO_ZOUT_H



   #define MPU6050_GYR0_Z0UT_Bit0Position			 (uint8_t)0
   #define MPU6050_GYR0_Z0UT_Mask				 (uint8_t)0xFF



   // GYRO_ZOUT_L



   #define MPU6050_GYR0_Z0UT_Bit0Position			 (uint8_t)0
   #define MPU6050_GYR0_Z0UT_Mask				 (uint8_t)0xFF



   // EXT_SENS_DATA_00



   #define MPU6050_EXT_SENS_DATA_00_Bit0Position			 (uint8_t)0
   #define MPU6050_EXT_SENS_DATA_00_Mask				 (uint8_t)0xFF



   // EXT_SENS_DATA_01



   #define MPU6050_EXT_SENS_DATA_01_Bit0Position			 (uint8_t)0
   #define MPU6050_EXT_SENS_DATA_01_Mask				 (uint8_t)0xFF



   // EXT_SENS_DATA_02



   #define MPU6050_EXT_SENS_DATA_02_Bit0Position			 (uint8_t)0
   #define MPU6050_EXT_SENS_DATA_02_Mask				 (uint8_t)0xFF



   // EXT_SENS_DATA_03



   #define MPU6050_EXT_SENS_DATA_03_Bit0Position			 (uint8_t)0
   #define MPU6050_EXT_SENS_DATA_03_Mask				 (uint8_t)0xFF



   // EXT_SENS_DATA_04



   #define MPU6050_EXT_SENS_DATA_04_Bit0Position			 (uint8_t)0
   #define MPU6050_EXT_SENS_DATA_04_Mask				 (uint8_t)0xFF



   // EXT_SENS_DATA_05



   #define MPU6050_EXT_SENS_DATA_05_Bit0Position			 (uint8_t)0
   #define MPU6050_EXT_SENS_DATA_05_Mask				 (uint8_t)0xFF



   // EXT_SENS_DATA_06



   #define MPU6050_EXT_SENS_DATA_06_Bit0Position			 (uint8_t)0
   #define MPU6050_EXT_SENS_DATA_06_Mask				 (uint8_t)0xFF



   // EXT_SENS_DATA_07



   #define MPU6050_EXT_SENS_DATA_07_Bit0Position			 (uint8_t)0
   #define MPU6050_EXT_SENS_DATA_07_Mask				 (uint8_t)0xFF



   // EXT_SENS_DATA_08



   #define MPU6050_EXT_SENS_DATA_08_Bit0Position			 (uint8_t)0
   #define MPU6050_EXT_SENS_DATA_08_Mask				 (uint8_t)0xFF



   // EXT_SENS_DATA_09



   #define MPU6050_EXT_SENS_DATA_09_Bit0Position			 (uint8_t)0
   #define MPU6050_EXT_SENS_DATA_09_Mask				 (uint8_t)0xFF



   // EXT_SENS_DATA_10



   #define MPU6050_EXT_SENS_DATA_10_Bit0Position			 (uint8_t)0
   #define MPU6050_EXT_SENS_DATA_10_Mask				 (uint8_t)0xFF



   // EXT_SENS_DATA_11



   #define MPU6050_EXT_SENS_DATA_11_Bit0Position			 (uint8_t)0
   #define MPU6050_EXT_SENS_DATA_11_Mask				 (uint8_t)0xFF



   // EXT_SENS_DATA_12



   #define MPU6050_EXT_SENS_DATA_12_Bit0Position			 (uint8_t)0
   #define MPU6050_EXT_SENS_DATA_12_Mask				 (uint8_t)0xFF



   // EXT_SENS_DATA_13



   #define MPU6050_EXT_SENS_DATA_13_Bit0Position			 (uint8_t)0
   #define MPU6050_EXT_SENS_DATA_13_Mask				 (uint8_t)0xFF



   // EXT_SENS_DATA_14



   #define MPU6050_EXT_SENS_DATA_14_Bit0Position			 (uint8_t)0
   #define MPU6050_EXT_SENS_DATA_14_Mask				 (uint8_t)0xFF



   // EXT_SENS_DATA_15



   #define MPU6050_EXT_SENS_DATA_15_Bit0Position			 (uint8_t)0
   #define MPU6050_EXT_SENS_DATA_15_Mask				 (uint8_t)0xFF



   // EXT_SENS_DATA_16



   #define MPU6050_EXT_SENS_DATA_16_Bit0Position			 (uint8_t)0
   #define MPU6050_EXT_SENS_DATA_16_Mask				 (uint8_t)0xFF



   // EXT_SENS_DATA_17



   #define MPU6050_EXT_SENS_DATA_17_Bit0Position			 (uint8_t)0
   #define MPU6050_EXT_SENS_DATA_17_Mask				 (uint8_t)0xFF



   // EXT_SENS_DATA_18



   #define MPU6050_EXT_SENS_DATA_18_Bit0Position			 (uint8_t)0
   #define MPU6050_EXT_SENS_DATA_18_Mask				 (uint8_t)0xFF



   // EXT_SENS_DATA_19



   #define MPU6050_EXT_SENS_DATA_19_Bit0Position			 (uint8_t)0
   #define MPU6050_EXT_SENS_DATA_19_Mask				 (uint8_t)0xFF



   // EXT_SENS_DATA_20



   #define MPU6050_EXT_SENS_DATA_20_Bit0Position			 (uint8_t)0
   #define MPU6050_EXT_SENS_DATA_20_Mask				 (uint8_t)0xFF



   // EXT_SENS_DATA_21



   #define MPU6050_EXT_SENS_DATA_21_Bit0Position			 (uint8_t)0
   #define MPU6050_EXT_SENS_DATA_21_Mask				 (uint8_t)0xFF



   // EXT_SENS_DATA_22



   #define MPU6050_EXT_SENS_DATA_22_Bit0Position			 (uint8_t)0
   #define MPU6050_EXT_SENS_DATA_22_Mask				 (uint8_t)0xFF



   // EXT_SENS_DATA_23



   #define MPU6050_EXT_SENS_DATA_23_Bit0Position			 (uint8_t)0
   #define MPU6050_EXT_SENS_DATA_23_Mask				 (uint8_t)0xFF



   // I2C_SLV0_D0



   #define MPU6050_I2C_SLV0_D0_Bit0Position			 (uint8_t)0
   #define MPU6050_I2C_SLV0_D0_Mask				 (uint8_t)0xFF



   // I2C_SLV1_D0



   #define MPU6050_I2C_SLV1_D0_Bit0Position			 (uint8_t)0
   #define MPU6050_I2C_SLV1_D0_Mask				 (uint8_t)0xFF



   // I2C_SLV2_D0



   #define MPU6050_I2C_SLV2_D0_Bit0Position			 (uint8_t)0
   #define MPU6050_I2C_SLV2_D0_Mask				 (uint8_t)0xFF



   // I2C_SLV3_D0



   #define MPU6050_I2C_SLV3_D0_Bit0Position			 (uint8_t)0
   #define MPU6050_I2C_SLV3_D0_Mask				 (uint8_t)0xFF



   // I2CMSTDELAYCTRL



   #define MPU6050_DELAYES_SHADOW_Bit0Position			 (uint8_t)7
   #define MPU6050_DELAYES_SHADOW_Mask				 (uint8_t)0x80
   #define MPU6050_I2CSLV4DLYEN_Bit0Position			 (uint8_t)4
   #define MPU6050_I2CSLV4DLYEN_Mask				 (uint8_t)0x10
   #define MPU6050_I2CSLV3DLYEN_Bit0Position			 (uint8_t)3
   #define MPU6050_I2CSLV3DLYEN_Mask				 (uint8_t)0x08
   #define MPU6050_I2CSLV2DLYEN_Bit0Position			 (uint8_t)2
   #define MPU6050_I2CSLV2DLYEN_Mask				 (uint8_t)0x04
   #define MPU6050_I2CSLV1DLYEN_Bit0Position			 (uint8_t)1
   #define MPU6050_I2CSLV1DLYEN_Mask				 (uint8_t)0x02
   #define MPU6050_I2CSLV0DLYEN_Bit0Position			 (uint8_t)0
   #define MPU6050_I2CSLV0DLYEN_Mask				 (uint8_t)0x01



   // SIGNALPATHRESET



   #define MPU6050_GYRO_RESET_Bit0Position			 (uint8_t)2
   #define MPU6050_GYRO_RESET_Mask				 (uint8_t)0x04
   #define MPU6050_ACCEL_RESET_Bit0Position			 (uint8_t)1
   #define MPU6050_ACCEL_RESET_Mask				 (uint8_t)0x02
   #define MPU6050_TEMP_RESET_Bit0Position			 (uint8_t)0
   #define MPU6050_TEMP_RESET_Mask				 (uint8_t)0x01

   #define MPU6050_Reset_Assert_Mask 			(uint8_t)0x87


   // MOT_DETECT_CTRL



   #define MPU6050_ACCEL_0N_DELAY_Bit0Position			 (uint8_t)4
   #define MPU6050_ACCEL_0N_DELAY_Mask				 (uint8_t)0x30



   // USER_CTRL



   #define MPU6050_FIFO_EN_Bit0Position			 (uint8_t)6
   #define MPU6050_FIFO_EN_Mask				 (uint8_t)0x40
   #define MPU6050_I2C_MST_EN_Bit0Position			 (uint8_t)5
   #define MPU6050_I2C_MST_EN_Mask				 (uint8_t)0x20
   #define MPU6050_I2C_IF_DIS_Bit0Position			 (uint8_t)4
   #define MPU6050_I2C_IF_DIS_Mask				 (uint8_t)0x10
   #define MPU6050_FIFO_RESET_Bit0Position			 (uint8_t)2
   #define MPU6050_FIFO_RESET_Mask				 (uint8_t)0x04
   #define MPU6050_I2C_MST_RESET_Bit0Position			 (uint8_t)1
   #define MPU6050_I2C_MST_RESET_Mask				 (uint8_t)0x02
   #define MPU6050_SIG_COND_RESET_Bit0Position			 (uint8_t)0
   #define MPU6050_SIG_COND_RESET_Mask				 (uint8_t)0x01



   // PWR_MGMT_1



   #define MPU6050_DEVICE_RESET_Bit0Position			 (uint8_t)7
   #define MPU6050_DEVICE_RESET_Mask				 (uint8_t)0x80
   #define MPU6050_SLEEP_Bit0Position			 (uint8_t)6
   #define MPU6050_SLEEP_Mask				 (uint8_t)0x40
   #define MPU6050_CYCLE_Bit0Position			 (uint8_t)5
   #define MPU6050_CYCLE_Mask				 (uint8_t)0x20
   #define MPU6050_TEMP_DIS_Bit0Position			 (uint8_t)3
   #define MPU6050_TEMP_DIS_Mask				 (uint8_t)0x08
   #define MPU6050_CLKSEL_Bit0Position			 (uint8_t)0
   #define MPU6050_CLKSEL_Mask				 (uint8_t)0x07

   #define MPU6050_ClockSource_Assert_Mask MPU6050_CLKSEL_Mask


   // PWR_MGMT_2



   #define MPU6050_LP_WAKE_CTRL_Bit0Position			 (uint8_t)6
   #define MPU6050_LP_WAKE_CTRL_Mask				 (uint8_t)0xC0
   #define MPU6050_STBY_XA_Bit0Position			 (uint8_t)5
   #define MPU6050_STBY_XA_Mask				 (uint8_t)0x20
   #define MPU6050_STBY_YA_Bit0Position			 (uint8_t)4
   #define MPU6050_STBY_YA_Mask				 (uint8_t)0x10
   #define MPU6050_STBY_ZA_Bit0Position			 (uint8_t)3
   #define MPU6050_STBY_ZA_Mask				 (uint8_t)0x08
   #define MPU6050_STBY_XG_Bit0Position			 (uint8_t)2
   #define MPU6050_STBY_XG_Mask				 (uint8_t)0x04
   #define MPU6050_STBY_YG_Bit0Position			 (uint8_t)1
   #define MPU6050_STBY_YG_Mask				 (uint8_t)0x02
   #define MPU6050_STBY_ZG_Bit0Position			 (uint8_t)0
   #define MPU6050_STBY_ZG_Mask				 (uint8_t)0x01
   #define MPU6050_STBY_Mask				 (uint8_t)0x3F


   // FIFO_COUNTH



   #define MPU6050_FIF0_C0UNT_Bit0Position			 (uint8_t)0
   #define MPU6050_FIF0_C0UNT_Mask				 (uint8_t)0xFF



   // FIFO_COUNTL



   #define MPU6050_FIF0_C0UNT_Bit0Position			 (uint8_t)0
   #define MPU6050_FIF0_C0UNT_Mask				 (uint8_t)0xFF



   // FIFO_R_W



   #define MPU6050_FIF0_DATA_Bit0Position			 (uint8_t)0
   #define MPU6050_FIF0_DATA_Mask				 (uint8_t)0xFF



   // WHO_AM_I



   #define MPU6050_WH0_AM_I_Bit0Position			 (uint8_t)1
   #define MPU6050_WH0_AM_I_Mask				 (uint8_t)0x7E



	#define MPU6050_PowerOnSensor_ALL (uint8_t)0x7F
	#define MPU6050_PowerOnSensor_TEMPERATURE (uint8_t)0x40
	#define MPU6050_PowerOnSensor_ACC_X (uint8_t)0x20
	#define MPU6050_PowerOnSensor_ACC_Y (uint8_t)0x10
	#define MPU6050_PowerOnSensor_ACC_Z (uint8_t)0x08
	#define MPU6050_PowerOnSensor_GYRO_X (uint8_t)0x04
	#define MPU6050_PowerOnSensor_GYRO_Y (uint8_t)0x02
	#define MPU6050_PowerOnSensor_GYRO_Z (uint8_t)0x01

	#define MPU6050_PowerOnSensor_Assert_Mask MPU6050_PowerOnSensor_ALL

	#define MPU6050_RESET_All_Device MPU6050_DEVICE_RESET_Mask
	#define MPU6050_RESET_FIFO MPU6050_FIFO_RESET_Mask
	#define MPU6050_RESET_I2C_Master MPU6050_I2C_MST_RESET_Mask
	#define MPU6050_RESET_DigitalLowPassFilter MPU6050_SIG_COND_RESET_Mask

	#define MPU6050_PowerMode_NORMAL (uint8_t)0x00
	#define MPU6050_PowerMode_CYCLE MPU6050_CYCLE_Mask
	#define MPU6050_PowerMode_SLEEP MPU6050_SLEEP_Mask

	#define MPU6050_PowerMode_Assert_Mask (uint8_t)0x60

	#define MPU6050_AccPowerOnDelay_4ms		(uint8_t)0x00
	#define MPU6050_AccPowerOnDelay_5ms		(uint8_t)0x10
	#define MPU6050_AccPowerOnDelay_6ms		(uint8_t)0x20
	#define MPU6050_AccPowerOnDelay_7ms		(uint8_t)0x30

	#define MPU6050_AccPowerOnDelay_Assert_Mask	(uint8_t)0x30

	#define MPU6050_EnableInterrupt_MOTION_DETECTION MPU6050_MOT_EN_Mask
	#define MPU6050_EnableInterrupt_FIFO_OVERFLOW MPU6050_FIFOOFLOW_EN_Mask
	#define MPU6050_EnableInterrupt_I2C_MASTER_INT MPU6050_I2CMST_INT_EN_Mask
	#define MPU6050_EnableInterrupt_DATA_READY MPU6050_DATA_RDY_EN_Mask
	#define MPU6050_EnableInterrupt_EXTERNAL_FRAME_SYNCHRO MPU6050_FSYNC_INT_EN_Mask

	#define MPU6050_EnableInterrupt_Assert_Mask (uint8_t)0x59

	#define MPU6050_AuxiliaryI2CInit_Assert_Mask (uint8_t)0x9F

	#define MPU6050_BufferData_Slave0 (uint16_t)MPU6050_SLV0_FIFO_EN_Mask
	#define MPU6050_BufferData_Slave1 (uint16_t)MPU6050_SLV1_FIFO_EN_Mask
	#define MPU6050_BufferData_Slave2 (uint16_t)MPU6050_SLV2_FIFO_EN_Mask
	#define MPU6050_BufferData_ACC (uint16_t)MPU6050_ACCEL_FIFO_EN_Mask
	#define MPU6050_BufferData_GYRO_Z (uint16_t)MPU6050_ZG_FIFO_EN_Mask
	#define MPU6050_BufferData_GYRO_Y (uint16_t)MPU6050_YG_FIFO_EN_Mask
	#define MPU6050_BufferData_GYRO_X (uint16_t)MPU6050_XG_FIFO_EN_Mask
	#define MPU6050_BufferData_TEMP (uint16_t)MPU6050_TEMP_FIFO_EN_Mask
	#define MPU6050_BufferData_Slave3 (uint16_t)0x2000


	class kMPU6050 : public kI2CDevice, public kAccelerometer, public kGyroscope
	{
		protected:

			uint8_t MPU6050_currentAccFullScaleRangeOption;
			uint8_t MPU6050_currentGyroFullScaleRangeOption;

			// funkcja konwertuje pomiary do jednostek uk�adu SI (opr�cz temperatury kt�ra podawana jest w stopniach Celsjusza)
			void MeasurementsToPhysicalUnits(void);

		public:

			MPU6050_MeasurementsStorage_TypeDef rawData;


			void sensorsInit(MPU6050_SensorsInitStruct_TypeDef * MPU6050_SensorsInitStruct);
			void powerOnSensor(uint8_t MPU6050_PowerOnSensor_xx,FunctionalState NewState);
			void dataRead(void);
			void setPowerMode(uint8_t MPU6050_PowerMode_xx);
			void reset(uint8_t MPU6050_RESET_xx);
			void setClockSource(MPU6050_ClockSource_TypeDef MPU6050_ClockSource_xx);
			// funkcja ustawia op�nienie w��czenia uk�adu akcelerometru po wybudzeniu
			void AccPowerOnDelay(uint8_t MPU6050_AccPowerOnDelay_xx);
			// funkcja inicjalizuje rejestry odpowiedzialne za sterowanie przerwaniami MPU6050
			void InterruptsInit(MPU6050_InterruptsInitStruct_TypeDef * MPU6050_InterruptsInitStruct);
			// funkcja inicjalizuje rejestry odpowiedzialne za prac� Auxiliary I2C
			void AuxiliaryI2CInit(MPU6050_AuxiliaryI2C_InitStruct_TypeDef * MPU6050_AuxiliaryI2C_InitStruct);
			// funkcja inicjalizuje prac� MPU6050 do obs�ugi dadatkowego uk�adu pod��czonego do Auxiliary I2C
			void SlaveInit(MPU6050_SlaveInitStruct_TypeDef * MPU6050_SlaveInitStruct);
			// funkcja w��cza/wy��cza buforowanie FIFO dla okreslonych danych z czujnik�w
			void FIFOsetBufferedData(uint16_t MPU6050_FIFOBufferData,FunctionalState NewState);
			// funkcja w��cza/wy��cza kontrol� nad Auxiliary I2C przez host (aplikacj� u�ytkownika)
			void I2CBypass(FunctionalState NewState);

	};


#endif
