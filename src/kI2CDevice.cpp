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



#include "kI2CDevice.h"


kI2CDevice::kI2CDevice(void)
{

}
kI2CDeviceHardware& kI2CDeviceHardware::operator = (unsigned int hard_code)
{
	// setup output pin
	this->i2c = (I2C_TypeDef*)kPrivate::setupPeripheralOutput(hard_code);
	return (*this);
}
void kI2CDevice::run(unsigned int clock_speed)
{
	I2C_InitTypeDef I2C_InitStruct;

	I2C_InitStruct.I2C_ClockSpeed = clock_speed;
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStruct.I2C_OwnAddress1 = 0x00;
	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(this->hardware.i2c,&I2C_InitStruct);

	I2C_Cmd(this->hardware.i2c,ENABLE);

}

void kI2CDevice::write(uint8_t StartingRegisterAddress,void * transmit_buffer,uint8_t BytesToWrite)
{
	uint8_t i;
	uint8_t * tx_buffer = (uint8_t*)transmit_buffer;

	//poczekaj dop�ki I2C1 jest zaj�ty
	while(I2C_GetFlagStatus(this->hardware.i2c, I2C_FLAG_BUSY) != RESET);
	//wygeneruj sygna� startu
	I2C_GenerateSTART(this->hardware.i2c,ENABLE);
	//poczekaj dop�ki transciever I2Cx przejdzie do trybu master
	while(!I2C_CheckEvent(this->hardware.i2c, I2C_EVENT_MASTER_MODE_SELECT));
	//wyslij adres uk�adu docelowego do zapisu
	I2C_Send7bitAddress(this->hardware.i2c,this->I2C_Address,I2C_Direction_Transmitter);

	//czekaj na potwierdzenie od ukladu podrz�dnego
	//master przejdzie w tryb nadawania
	while(!I2C_CheckEvent(this->hardware.i2c, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));


	//wyslij bajt danych
	I2C_SendData(this->hardware.i2c,StartingRegisterAddress);
	//czekaj dop�ki nie wys�ano bajtu danych
	while(!I2C_CheckEvent(this->hardware.i2c, I2C_EVENT_MASTER_BYTE_TRANSMITTED));


	for(i=0;i<BytesToWrite;i++)
	{
		//wyslij bajt danych
		I2C_SendData(this->hardware.i2c,*tx_buffer);
		//czekaj dop�ki nie wys�ano bajtu danych
		while(!I2C_CheckEvent(this->hardware.i2c, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

		tx_buffer++;
	}

	//wyslij znak stop
	I2C_GenerateSTOP(this->hardware.i2c,ENABLE);
}
void kI2CDevice::write(uint8_t RegisterAddress,uint8_t value)
{

	//poczekaj dop�ki I2Cx jest zaj�ty
	while(I2C_GetFlagStatus(this->hardware.i2c, I2C_FLAG_BUSY) != RESET);
	//wygeneruj sygna� startu
	I2C_GenerateSTART(this->hardware.i2c,ENABLE);
	//poczekaj dop�ki transciever I2Cx przejdzie do trybu master
	while(!I2C_CheckEvent(this->hardware.i2c, I2C_EVENT_MASTER_MODE_SELECT));
	//wyslij adres uk�adu docelowego do zapisu
	I2C_Send7bitAddress(this->hardware.i2c,this->I2C_Address,I2C_Direction_Transmitter);

	//czekaj na potwierdzenie od ukladu podrz�dnego
	//master przejdzie w tryb nadawania
	while(!I2C_CheckEvent(this->hardware.i2c, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));


	//wyslij adres rejestru
	I2C_SendData(this->hardware.i2c,RegisterAddress);
	//czekaj dop�ki nie wys�ano bajtu danych
	while(!I2C_CheckEvent(this->hardware.i2c, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	//wyslij wartosc rejestru
	I2C_SendData(this->hardware.i2c,value);
	//czekaj dop�ki nie wys�ano bajtu danych
	while(!I2C_CheckEvent(this->hardware.i2c, I2C_EVENT_MASTER_BYTE_TRANSMITTED));


	//wyslij znak stop
	I2C_GenerateSTOP(this->hardware.i2c,ENABLE);
}
void kI2CDevice::read(uint8_t StartingRegisterAddress, void * recieve_buffer,uint8_t BytesToRead)
{
	uint8_t i,loop_end;
	uint8_t * rx_buffer = (uint8_t*)recieve_buffer;

	if(BytesToRead > 1)
	{

		//poczekaj dop�ki I2Cx jest zaj�ty
		while(I2C_GetFlagStatus(this->hardware.i2c, I2C_FLAG_BUSY) != RESET);
		//wygeneruj sygna� startu
		I2C_GenerateSTART(this->hardware.i2c,ENABLE);
		//poczekaj dop�ki transciever I2C1 przejdzie do trybu master
		while(!I2C_CheckEvent(this->hardware.i2c, I2C_EVENT_MASTER_MODE_SELECT));
		//wyslij adres uk�adu docelowego do zapisu
		I2C_Send7bitAddress(this->hardware.i2c,this->I2C_Address,I2C_Direction_Transmitter);

		//czekaj na potwierdzenie od ukladu podrz�dnego
		//master przejdzie w tryb nadawania
		while(!I2C_CheckEvent(this->hardware.i2c, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

		//wyslij bajt danych
		I2C_SendData(this->hardware.i2c,StartingRegisterAddress);
		//czekaj dop�ki nie wys�ano bajtu danych
		while(!I2C_CheckEvent(this->hardware.i2c, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

		//w��cz potwierdzenia otrzymywania danych (ACK on)
		I2C_AcknowledgeConfig(this->hardware.i2c,ENABLE);

		//wygeneruj sygna� startu
		I2C_GenerateSTART(this->hardware.i2c,ENABLE);
		//poczekaj dop�ki transciever I2Cx przejdzie do trybu master
		while(!I2C_CheckEvent(this->hardware.i2c, I2C_EVENT_MASTER_MODE_SELECT));
		//wyslij adres uk�adu docelowego do odczytu
		I2C_Send7bitAddress(this->hardware.i2c,this->I2C_Address,I2C_Direction_Receiver);

		//czekaj na potwierdzenie od ukladu podrz�dnego
		//master przejdzie w tryb odbioru
		while(!I2C_CheckEvent(this->hardware.i2c, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));



		loop_end = BytesToRead - 2;
		//czekaj a� I2Cx odbierze dane z kolejnych rejestr�w
		for(i=0;i<loop_end;i++)
		{
			//czekaj a� I2Cx odbierze bajt danych
			while(!I2C_CheckEvent(this->hardware.i2c, I2C_EVENT_MASTER_BYTE_RECEIVED));
			//odbierz dane
			*rx_buffer = I2C_ReceiveData(this->hardware.i2c);

			rx_buffer++;
		}
		//czekaj a� I2Cx odbierze bajt danych
		while(!I2C_CheckEvent(this->hardware.i2c, I2C_EVENT_MASTER_BYTE_RECEIVED));

		/*
		 * Wy��cz potwierdzenia ACK oraz za��daj wygenerowanie sygna�u STOP
		 * Uk�ad I2C posiada opr�cz rejestru danych, wewn�trzny rejestr przesuwny
		 * Na tym etapie oba rejestry s� wype�nione danymi
		 * Aby poprawnie zako�czy� transmisj� danych sygna�y NACK i STOP
		 * musz� by� zaprogramowane w�asnie w tym momencie
		 * (pozosta�o do odebrania 2 bajty danych)
		 * Po wi�cej informacji prosz� odnies� si� do stm32f4xx reference manual
		 */

		I2C_AcknowledgeConfig(this->hardware.i2c,DISABLE);
		I2C_GenerateSTOP(this->hardware.i2c,ENABLE);

		// odbierz ostantie dwa bajty
		*rx_buffer = I2C_ReceiveData(this->hardware.i2c);
		rx_buffer++;

		//czekaj a� I2Cx odbierze bajt danych
		while(!I2C_CheckEvent(this->hardware.i2c, I2C_EVENT_MASTER_BYTE_RECEIVED));
		//odbierz dane
		*rx_buffer = I2C_ReceiveData(this->hardware.i2c);

	}else
	{
		//poczekaj dop�ki I2Cx jest zaj�ty
		while(I2C_GetFlagStatus(this->hardware.i2c, I2C_FLAG_BUSY) != RESET);
		//wygeneruj sygna� startu
		I2C_GenerateSTART(this->hardware.i2c,ENABLE);
		//poczekaj dop�ki transciever I2C1 przejdzie do trybu master
		while(!I2C_CheckEvent(this->hardware.i2c, I2C_EVENT_MASTER_MODE_SELECT));
		//wyslij adres uk�adu docelowego do zapisu
		I2C_Send7bitAddress(this->hardware.i2c,this->I2C_Address,I2C_Direction_Transmitter);

		//czekaj na potwierdzenie od ukladu podrz�dnego
		//master przejdzie w tryb nadawania
		while(!I2C_CheckEvent(this->hardware.i2c, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
		//wyslij bajt danych
		I2C_SendData(this->hardware.i2c,StartingRegisterAddress);
		//czekaj dop�ki nie wys�ano bajtu danych
		while(!I2C_CheckEvent(this->hardware.i2c, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
		//wy��cz potwierdzenia otrzymywania danych (ACK off)
		I2C_AcknowledgeConfig(this->hardware.i2c,DISABLE);



		//wygeneruj sygna� startu
		I2C_GenerateSTART(this->hardware.i2c,ENABLE);
		//poczekaj dop�ki transciever I2C1 przejdzie do trybu master
		while(!I2C_CheckEvent(this->hardware.i2c, I2C_EVENT_MASTER_MODE_SELECT));
		//wyslij adres uk�adu docelowego do zapisu
		I2C_Send7bitAddress(this->hardware.i2c,this->I2C_Address,I2C_Direction_Receiver);

		//czekaj na potwierdzenie od ukladu podrz�dnego
		//master przejdzie w tryb odbioru
		while(!I2C_CheckEvent(this->hardware.i2c, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

		I2C_GenerateSTOP(this->hardware.i2c,ENABLE);

		// odbierz bajt
		*rx_buffer = I2C_ReceiveData(this->hardware.i2c);
	}

}
unsigned char kI2CDevice::read(uint8_t RegisterAddress)
{
	// there is some problem with internal shift buffer
	// that do not allow receiving single byte
	unsigned char buff[3];
	this->read(RegisterAddress,buff,3);
	return buff[0];
}
