#include "kI2CDevice.h"

const kI2C1 * kI2CDevice::I2C_1 = (kI2C1 *)SRAM1_BASE;
const kI2C2 * kI2CDevice::I2C_2 = (kI2C2 *)SRAM1_BASE;
const kI2C3 * kI2CDevice::I2C_3 = (kI2C3 *)SRAM1_BASE;

kI2CDevice::kI2CDevice(void)
{

}
void kI2CDeviceHardware::setupSCLPin(void)
{

	//enable clock
	kPort sclPort(this->sclGPIO);
	sclPort = kPort::on;
	unsigned char pin;
	unsigned long long alternate_function;
	pin = this->sclPin & 0x0F;
	alternate_function = this->sclPin & 0xF0;
	alternate_function = alternate_function >> 4;

	sclPort[pin] = kPin::alternate,kPin::OpenDrain,kPin::NoPull,kPin::VeryHighSpeed;

	// map alternate function
	unsigned long long reg = (unsigned long long)((unsigned long long)this->sclGPIO->AFR[1] << 32) + this->sclGPIO->AFR[0];
	unsigned long long mask = 0x0F;
	mask = mask << (pin << 2);
	mask = ~mask;
	reg &= mask;

	alternate_function = alternate_function << (pin << 2);
	reg |= alternate_function;
	this->sclGPIO->AFR[0] = (unsigned int)reg;
	this->sclGPIO->AFR[1] = (unsigned int)(reg >> 32);
}
void kI2CDeviceHardware::setupSDAPin(void)
{
	//enable clock
	kPort sdaPort(this->sdaGPIO);
	sdaPort = kPort::on;
	unsigned char pin;
	unsigned long long alternate_function;
	pin = this->sdaPin & 0x0F;
	alternate_function = this->sdaPin & 0xF0;
	alternate_function = alternate_function >> 4;

	sdaPort[pin] = kPin::alternate,kPin::OpenDrain,kPin::NoPull,kPin::VeryHighSpeed;

	// map alternate function
	unsigned long long reg = (unsigned long long)((unsigned long long)this->sdaGPIO->AFR[1] << 32) + this->sdaGPIO->AFR[0];
	unsigned long long mask = 0x0F;
	mask = mask << (pin << 2);
	mask = ~mask;
	reg &= mask;

	alternate_function = alternate_function << (pin << 2);
	reg |= alternate_function;
	this->sdaGPIO->AFR[0] = (unsigned int)reg;
	this->sdaGPIO->AFR[1] = (unsigned int)(reg >> 32);
}
void kI2CDeviceHardware::operator = (const kI2C1Pin & i2cHard)
{
	unsigned int reg_address = (unsigned int)&i2cHard;
	this->i2c = I2C1;
	unsigned int shift = reg_address - (unsigned int)kI2CDevice::I2C_1;

	// enable I2C1 clock
	RCC->APB1ENR |= (1 << 21);

	switch(shift)
	{
		case 0: // SCL PORTB6

			this->sclGPIO = GPIOB;
			this->sclPin = 6 | (4 << 4);
			this->setupSCLPin();
		break;
		case 1: // SCL PORTB8
			this->sclGPIO = GPIOB;
			this->sclPin = 8 | (4 << 4);
			this->setupSCLPin();
		break;
		case 2:	// SDA PORTB7
			this->sdaGPIO = GPIOB;
			this->sdaPin = 7 | (4 << 4);
			this->setupSDAPin();
		break;
		case 3: // SDA PORTB9
			this->sdaGPIO = GPIOB;
			this->sdaPin = 9 | (4 << 4);
			this->setupSDAPin();
		break;
	}
}
void kI2CDeviceHardware::operator = (const kI2C2Pin & i2cHard)
{
	unsigned int reg_address = (unsigned int)&i2cHard;
	this->i2c = I2C2;
	unsigned int shift = reg_address - (unsigned int)kI2CDevice::I2C_2;

	// enable I2C2 clock
	RCC->APB1ENR |= (1 << 22);

	switch(shift)
	{
		case 0: // SCL PORTB10
			this->sclGPIO = GPIOB;
			this->sclPin = 10 | (4 << 4);
			this->setupSCLPin();
		break;
		case 1: // SCL PORTF1
			this->sclGPIO = GPIOF;
			this->sclPin = 1 | (4 << 4);
			this->setupSCLPin();
		break;
		case 2:	// SCL PORTH4
			this->sdaGPIO = GPIOH;
			this->sdaPin = 4 | (4 << 4);
			this->setupSCLPin();
		break;
		case 3: // SDA PORTB11
			this->sdaGPIO = GPIOB;
			this->sdaPin = 11 | (4 << 4);
			this->setupSDAPin();
		break;
		case 4: // SDA PORTF0
			this->sclGPIO = GPIOF;
			this->sclPin = 0 | (4 << 4);
			this->setupSDAPin();
		break;
		case 5: // SDA PORTH5
			this->sclGPIO = GPIOH;
			this->sclPin = 5 | (4 << 4);
			this->setupSDAPin();
		break;
	}
}
void kI2CDeviceHardware::operator = (const kI2C3Pin & i2cHard)
{
	unsigned int reg_address = (unsigned int)&i2cHard;
	this->i2c = I2C3;
	unsigned int shift = reg_address - (unsigned int)kI2CDevice::I2C_3;

	// enable I2C3 clock
	RCC->APB1ENR |= (1 << 23);

	switch(shift)
	{
		case 0: // SCL PORTA8

			this->sclGPIO = GPIOA;
			this->sclPin = 8 | (4 << 4);
			this->setupSCLPin();
		break;
		case 1: // SCL PORTH7
			this->sclGPIO = GPIOH;
			this->sclPin = 7 | (4 << 4);
			this->setupSCLPin();
		break;
		case 2:	// SDA PORTC9
			this->sdaGPIO = GPIOC;
			this->sdaPin = 9 | (4 << 4);
			this->setupSDAPin();
		break;
		case 3: // SDA PORTH8
			this->sdaGPIO = GPIOH;
			this->sdaPin = 8 | (4 << 4);
			this->setupSDAPin();
		break;
	}
}
void kI2CDeviceHardware::clockSpeed(unsigned int value)
{
	I2C_InitTypeDef I2C_InitStruct;

	//konfiguracja pracy uk�adu I2C1
	//pr�dkos� sygna�u zegarowego linii SCL - 100kHz (standardowo)
	I2C_InitStruct.I2C_ClockSpeed = value;
	//tryb dzia�ania uk�adu - dost�pne r�wnie� rozszerzenie protoko�u: SMBus
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	// ustawienia Timing'�w sygna�u - istotne w fast mode - tutaj standardowo 50%
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	//adres uk�adu - w trybie Master nieistotny (nieu�ywany)
	I2C_InitStruct.I2C_OwnAddress1 = 0x00;
	//wysy�aj potwierdzenie (ACK) po ka�dym otrzymanym bajcie
	//r�wnoznaczne z ��daniem nast�pnego bajtu danych od Slave
	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
	//korzystamy z adres�w 7-bitowych + 1bit kierunku
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;

	//Przekazanie wype�nionej struktury do funkcji inicjalizuj�cej uk�ad I2C1
	I2C_Init(this->i2c,&I2C_InitStruct);

	//zezwolenie na prac� uk�adu
	I2C_Cmd(this->i2c,ENABLE);

}
kI2CDevice::kI2CDevice(const kI2C1Pin & SCL,const kI2C1Pin & SDA,unsigned int clockSpeed)
{
	this->hardware = SCL;
	this->hardware = SDA;
	this->hardware.clockSpeed(clockSpeed);
}
kI2CDevice::kI2CDevice(const kI2C2Pin & SCL,const kI2C2Pin & SDA,unsigned int clockSpeed)
{
	this->hardware = SCL;
	this->hardware = SDA;
	this->hardware.clockSpeed(clockSpeed);
}
kI2CDevice::kI2CDevice(const kI2C3Pin & SCL,const kI2C3Pin & SDA,unsigned int clockSpeed)
{
	this->hardware = SCL;
	this->hardware = SDA;
	this->hardware.clockSpeed(clockSpeed);
}
void kI2CDevice::write(uint8_t StartingRegisterAddress,uint8_t * transmit_buffer,uint8_t BytesToWrite)
{
	uint8_t i;

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
		I2C_SendData(this->hardware.i2c,*transmit_buffer);
		//czekaj dop�ki nie wys�ano bajtu danych
		while(!I2C_CheckEvent(this->hardware.i2c, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

		transmit_buffer++;
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
void kI2CDevice::read(uint8_t StartingRegisterAddress, uint8_t * recieve_buffer,uint8_t BytesToRead)
{
	uint8_t i,loop_end;


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
			*recieve_buffer = I2C_ReceiveData(this->hardware.i2c);

			recieve_buffer++;
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
		*recieve_buffer = I2C_ReceiveData(this->hardware.i2c);
		recieve_buffer++;

		//czekaj a� I2Cx odbierze bajt danych
		while(!I2C_CheckEvent(this->hardware.i2c, I2C_EVENT_MASTER_BYTE_RECEIVED));
		//odbierz dane
		*recieve_buffer = I2C_ReceiveData(this->hardware.i2c);

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
		*recieve_buffer = I2C_ReceiveData(this->hardware.i2c);
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
