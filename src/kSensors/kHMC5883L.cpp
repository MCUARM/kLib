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



#include "kHMC5883L.h"

// funkcja inicjalizuje modu� do pracy
void kHMC5883L::init(HMC5883L_InitTypeDef * HMC5883L_InitStruct)
{
	uint8_t temp_reg[3];

	//CRA

	temp_reg[0] = 0x00;

	temp_reg[0] |= (uint8_t)(HMC5883L_InitStruct->HMC5883L_MeasurementAverage << HMC5883L_CRA_MA0_BitPosition);
	temp_reg[0] |= (uint8_t)(HMC5883L_InitStruct->HMC5883L_DataOutputRate << HMC5883L_CRA_DO0_BitPosition);
	temp_reg[0] |= (uint8_t)(HMC5883L_InitStruct->HMC5883L_MeasurementMode << HMC5883L_CRA_MS0_BitPosition);

	//CRB

	temp_reg[1] = 0x00;
	temp_reg[1] |= (uint8_t)(HMC5883L_InitStruct->HMC5883L_Gain << HMC5883L_CRB_GN0_BitPosition);


	//MR

	temp_reg[2] = 0x00;
	temp_reg[2] |= (uint8_t)(HMC5883L_InitStruct->HMC5883L_I2C_Speed << HMC5883L_MR_HS0_BitPosition);
	temp_reg[2] |= (uint8_t)(HMC5883L_InitStruct->HMC5883L_OperatingMode << HMC5883L_MR_MD0_BitPosition);



	//zapisz dane do uk�adu
	this->write(HMC5883L_REGISTER_CRA,temp_reg,3);

	this->HMC5883L_MR_HS_BitState = (uint8_t)(HMC5883L_InitStruct->HMC5883L_I2C_Speed << HMC5883L_MR_HS0_BitPosition);
}
// funkcja odbiera dane z czujnika
void kHMC5883L::readData(int16_t *X, int16_t *Y, int16_t *Z)
{
	uint8_t temp_buff[6];

	this->read(HMC5883L_REGISTER_X_MSB,temp_buff,6);

	*X = (int16_t)((temp_buff[0] << 8) | temp_buff[1]);
	*Z = (int16_t)((temp_buff[2] << 8) | temp_buff[3]);
	*Y = (int16_t)((temp_buff[4] << 8) | temp_buff[5]);
}
// funkcja wysy�a ��danie pojedynczego pomiaru
void kHMC5883L::requestSingleMeasure(void)
{
	uint8_t temp_reg;

	temp_reg = 0x00;
	temp_reg |= HMC5883L_OperatingMode_Single_Measurement;
	temp_reg |= HMC5883L_MR_HS_BitState;

	this->write(HMC5883L_REGISTER_MODE,&temp_reg,1);
}
