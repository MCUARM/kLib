#include "kMPU6050.h"

// Tablice wsp�czynnik�w przeliczaj�cych pomiary
// jednostki wyjsciowe to standardowe jednostki uk�adu SI!!!
// komentarze po prawej stronie dodane tylko w celach informacyjnych!
// wyniki pomiaru nale�y podzieli� przez nast�puj�ce odpowiednie wsp�czynniki
// aby uzyska� pomiary w jednostkach uk�adu SI

// LSB  / (m/s^2)
const float MPU6050_Acc_LSB_Sensitivity[] = {			1669.163,	// 2g
														834.5813,	// 4g
														417,2907,	// 8g
														208.6453	// 16g
};

// LSB  / (rad/s)
const float MPU6050_Gyro_LSB_Sensitivity[] = {			7505.747,	// 250 deg/s
														3752.874,	// 500 deg/s
														1879.302,	// 1000 deg/s
														939.6508	// 2000 deg/s
};

void kMPU6050::sensorsInit(MPU6050_SensorsInitStruct_TypeDef * MPU6050_SensorsInitStruct)
{
	uint8_t temp_reg;
	unsigned char MPU6050_temp_buff[4];


	this->read(MPU6050_REGISTER_CONFIG,&(MPU6050_temp_buff[1]),3);

	MPU6050_temp_buff[0] = MPU6050_SensorsInitStruct->SampleRateDivider;


	MPU6050_temp_buff[1] &= (~MPU6050_DLPF_CFG_Mask);
	MPU6050_temp_buff[1] |= (uint8_t)MPU6050_SensorsInitStruct->MPU6050_DigitalLowPassFilterBandwidth;

	MPU6050_temp_buff[2] &= (~MPU6050_FS_SEL_Mask);
	temp_reg = ((uint8_t)MPU6050_SensorsInitStruct->MPU6050_GyroFullScaleRange) << MPU6050_FS_SEL_Bit0Position;
	MPU6050_temp_buff[2] |= temp_reg;

	MPU6050_temp_buff[3] &= (~MPU6050_AFS_SEL_Mask);
	temp_reg = ((uint8_t)MPU6050_SensorsInitStruct->MPU6050_AccFullScaleRange) << MPU6050_AFS_SEL_Bit0Position;
	MPU6050_temp_buff[3] |= temp_reg;

	this->write(MPU6050_REGISTER_SMPLRT_DIV,MPU6050_temp_buff,4);

	if(MPU6050_SensorsInitStruct->MPU6050_PowerOnSensor)
	{
		this->read(MPU6050_REGISTER_PWR_MGMT_1,MPU6050_temp_buff,2);


		temp_reg = (MPU6050_SensorsInitStruct->MPU6050_PowerOnSensor & MPU6050_PowerOnSensor_TEMPERATURE) >> MPU6050_TEMP_DIS_Bit0Position;
		temp_reg |= MPU6050_SLEEP_Mask;
		temp_reg ^= (MPU6050_SLEEP_Mask | MPU6050_TEMP_DIS_Mask);

		MPU6050_temp_buff[0] &= ~(MPU6050_SLEEP_Mask | MPU6050_TEMP_DIS_Mask);
		MPU6050_temp_buff[0] |= temp_reg;


		temp_reg = (MPU6050_SensorsInitStruct->MPU6050_PowerOnSensor & MPU6050_STBY_Mask);
		temp_reg ^= MPU6050_STBY_Mask;

		MPU6050_temp_buff[1] &= ~MPU6050_STBY_Mask;
		MPU6050_temp_buff[1] |= temp_reg;

		this->write(MPU6050_REGISTER_PWR_MGMT_1,MPU6050_temp_buff,2);
	}

	// uaktualnij zmienne pomocnicze pami�taj�ce ostatnie ustawienia FullScaleRange
	this->MPU6050_currentAccFullScaleRangeOption = (uint8_t)MPU6050_SensorsInitStruct->MPU6050_AccFullScaleRange;
	this->MPU6050_currentGyroFullScaleRangeOption = (uint8_t)MPU6050_SensorsInitStruct->MPU6050_GyroFullScaleRange;

}
void kMPU6050::dataRead(void)
{
	uint8_t i;
	int16_t * p;
	uint8_t MPU6050_temp_buff[14];

	this->read(MPU6050_REGISTER_ACCEL_XOUT_H,MPU6050_temp_buff,14);

	p = (int16_t*)&this->rawData;
	// konwersja danych (sk�adanie dw�ch bajt�w w s�owo 16-bitowe
	for(i=0;i<13;i+=2)
	{
		*p = (int16_t)((MPU6050_temp_buff[i] << 8) | MPU6050_temp_buff[i+1]);
		p++;
	}

	// konwersja na jednostki fizyczne
	this->MeasurementsToPhysicalUnits();

}
void kMPU6050::powerOnSensor(uint8_t MPU6050_PowerOnSensor_xx,FunctionalState NewState)
{
	uint8_t MPU6050_temp_buff[4];

	//chro� przed b�ednymi parametrami
	MPU6050_PowerOnSensor_xx &= MPU6050_PowerOnSensor_Assert_Mask;

	//odczytaj rejestry PWR_MGMT_1 oraz PWR_MGMT_2
	this->read(MPU6050_REGISTER_PWR_MGMT_1,MPU6050_temp_buff,2);

	MPU6050_temp_buff[2] = (MPU6050_PowerOnSensor_xx & MPU6050_PowerOnSensor_TEMPERATURE) >> MPU6050_TEMP_DIS_Bit0Position;
	MPU6050_temp_buff[2] = ~MPU6050_temp_buff[2];

	MPU6050_temp_buff[0] &= MPU6050_temp_buff[2];


	MPU6050_temp_buff[3] = (MPU6050_PowerOnSensor_xx & (~MPU6050_PowerOnSensor_TEMPERATURE));
	MPU6050_temp_buff[3] = ~MPU6050_temp_buff[3];

	MPU6050_temp_buff[1] &= MPU6050_temp_buff[3];

	if(NewState == DISABLE)
	{
		MPU6050_temp_buff[2] = ~MPU6050_temp_buff[2];
		MPU6050_temp_buff[3] = ~MPU6050_temp_buff[3];

		MPU6050_temp_buff[0] |= MPU6050_temp_buff[2];
		MPU6050_temp_buff[1] |= MPU6050_temp_buff[3];
	}

	this->write(MPU6050_REGISTER_PWR_MGMT_1,MPU6050_temp_buff,2);
}
void kMPU6050::setPowerMode(uint8_t MPU6050_PowerMode_xx)
{
	uint8_t MPU6050_temp_buff[1];

	//chro� przed b�ednymi parametrami
	MPU6050_PowerMode_xx &= MPU6050_PowerMode_Assert_Mask;

	if(MPU6050_PowerMode_xx)
	{
		// odczytaj rejestr PWR_MGMT_1
		this->read(MPU6050_REGISTER_PWR_MGMT_1,MPU6050_temp_buff,1);

		// nanies bity resetuj�ce
		MPU6050_temp_buff[0] |= MPU6050_PowerMode_xx;

		// zapisz now� wartosc rejestru PWR_MGMT_1
		this->write(MPU6050_REGISTER_PWR_MGMT_1,MPU6050_temp_buff,1);

	}
}
void kMPU6050::reset(uint8_t MPU6050_RESET_xx)
{
	uint8_t MPU6050_temp_buff[1];

	//chro� przed b�ednymi parametrami
	MPU6050_RESET_xx &= MPU6050_Reset_Assert_Mask;

	// czy resetowa� ca�y uk�ad?
	if(MPU6050_RESET_xx & MPU6050_RESET_All_Device)
	{
		// ca�y uk�ad zostanie zresetowany, rejestry powr�c� do wartosci domyslnych
		MPU6050_temp_buff[0] = MPU6050_DEVICE_RESET_Mask | MPU6050_SLEEP_Mask;
		this->write(MPU6050_REGISTER_PWR_MGMT_1,MPU6050_temp_buff,1);

	}else
	{
		// odczytaj rejestr USER_CTRL
		this->read(MPU6050_REGISTER_USER_CTRL,MPU6050_temp_buff,1);

		// nanies bity resetuj�ce
		MPU6050_temp_buff[0] |= MPU6050_RESET_xx;

		// zapisz now� wartosc rejestru USER_CTRL
		this->write(MPU6050_REGISTER_USER_CTRL,MPU6050_temp_buff,1);

	}
}
void kMPU6050::setClockSource(MPU6050_ClockSource_TypeDef MPU6050_ClockSource_xx)
{
	uint8_t MPU6050_temp_buff[2];
	//chro� przed b�ednymi parametrami
	MPU6050_temp_buff[1] = MPU6050_ClockSource_xx;
	MPU6050_temp_buff[1] &= MPU6050_ClockSource_Assert_Mask;

	// odczytaj rejestr PWR_MGMT_1
	this->read(MPU6050_REGISTER_PWR_MGMT_1,MPU6050_temp_buff,1);

	// zeruj bity odpowiedzialne za CLKSEL
	MPU6050_temp_buff[0] &= (~MPU6050_CLKSEL_Mask);

	// dodaj nowe ustawienia
	MPU6050_temp_buff[0] |= MPU6050_temp_buff[1];

	// zapisz now� wartosc rejestru PWR_MGMT_1
	this->write(MPU6050_REGISTER_PWR_MGMT_1,MPU6050_temp_buff,1);
}
// funkcja ustawia op�nienie w��czenia uk�adu akcelerometru po wybudzeniu
void kMPU6050::AccPowerOnDelay(uint8_t MPU6050_AccPowerOnDelay_xx)
{
	uint8_t MPU6050_temp_buff[1];

	// chro� przed b�ednymi parametrami
	MPU6050_AccPowerOnDelay_xx &= MPU6050_AccPowerOnDelay_Assert_Mask;

	// zapisz now� wartos� rejestru do bufora
	MPU6050_temp_buff[0] = MPU6050_AccPowerOnDelay_xx;

	// wyslij now� wartos� rejestru MOT_DETECT_CTRL
	this->write(MPU6050_REGISTER_MOT_DETECT_CTRL,MPU6050_temp_buff,1);
}
// funkcja inicjalizuje rejestry odpowiedzialne za sterowanie przerwaniami MPU6050
void kMPU6050::InterruptsInit(MPU6050_InterruptsInitStruct_TypeDef * MPU6050_InterruptsInitStruct)
{
	uint8_t MPU6050_temp_buff[3];

	// odczytaj rejestr CONFIG
	this->read(MPU6050_REGISTER_CONFIG,MPU6050_temp_buff,1);

	//wyzeruj bity odpowiedzialne EXT_SYNC_SET
	MPU6050_temp_buff[0] &= (~MPU6050_EXT_SYNC_SET_Mask);

	// u�yj jako zmiennej pomocniczej
	MPU6050_temp_buff[1] = (uint8_t)(MPU6050_InterruptsInitStruct->MPU6050_ExternalFrameSynchro << MPU6050_EXT_SYNC_SET_Bit0Position);

	//wpisz now� wartosc EXT_SYNC_SET do bufora
	MPU6050_temp_buff[0] |= MPU6050_temp_buff[1];

	// wyslij now� wartos� rejestru CONFIG
	this->write(MPU6050_REGISTER_CONFIG,MPU6050_temp_buff,1);

	//wpisz now� wartosc MOT_THR do bufora
	MPU6050_temp_buff[0] = MPU6050_InterruptsInitStruct->MPU6050_MotionDetectionThreshold;

	// wyslij now� wartos� rejestru MOT_THR
	this->write(MPU6050_REGISTER_MOT_THR,MPU6050_temp_buff,1);

	//REJESTR INT_PIN_CFG

	MPU6050_temp_buff[0]= 0x00;

	// u�yj jako zmiennej pomocniczej
	//INT_LEVEL
	MPU6050_temp_buff[2] = (uint8_t)(MPU6050_InterruptsInitStruct->MPU6050_InterruptLogicLevel << MPU6050_INT_LEVEL_Bit0Position);
	MPU6050_temp_buff[0] |= MPU6050_temp_buff[2];

	//INT_OPEN
	MPU6050_temp_buff[2] = (uint8_t)(MPU6050_InterruptsInitStruct->MPU6050_InterruptOutputType << MPU6050_INT_OPEN_Bit0Position);
	MPU6050_temp_buff[0] |= MPU6050_temp_buff[2];

	//LATCH_INT_EN
	MPU6050_temp_buff[2] = (uint8_t)(MPU6050_InterruptsInitStruct->MPU6050_InterruptSignalLatch << MPU6050_LATCH_INT_EN_Bit0Position);
	MPU6050_temp_buff[0] |= MPU6050_temp_buff[2];

	//INT_RD_CLEAR
	MPU6050_temp_buff[2] = (uint8_t)(MPU6050_InterruptsInitStruct->MPU6050_InterruptClearFlagCondition << MPU6050_INT_RD_CLEAR_Bit0Position);
	MPU6050_temp_buff[0] |= MPU6050_temp_buff[2];

	//FSYNC_INT_LEVEL
	MPU6050_temp_buff[2] = (uint8_t)(MPU6050_InterruptsInitStruct->MPU6050_ExternalFrameSynchroLogicLevel << MPU6050_FSYNC_INT_LEVEL_Bit0Position);
	MPU6050_temp_buff[0] |= MPU6050_temp_buff[2];

	//FSYNC_INT_EN
	MPU6050_temp_buff[2] = (MPU6050_InterruptsInitStruct->MPU6050_EnableInterrupt & MPU6050_FSYNC_INT_EN_Mask);
	MPU6050_temp_buff[0] |= MPU6050_temp_buff[2];

	//I2C_BYPASS_EN - pozostaw bez zmian
	// odczytaj rejestr INT_PIN_CFG
	this->read(MPU6050_REGISTER_PWR_MGMT_1,&(MPU6050_temp_buff[2]),1);
	// pozostaw tylko bit I2C_BYPASS_EN
	MPU6050_temp_buff[2] &= MPU6050_I2CBYPASS_EN_Mask;
	MPU6050_temp_buff[0] |= MPU6050_temp_buff[2];

	//REJESTR INT_ENABLE

	// chro� przed b�ednymi parametrami
	MPU6050_temp_buff[1] &= (MPU6050_InterruptsInitStruct->MPU6050_EnableInterrupt & MPU6050_EnableInterrupt_Assert_Mask);

	// wpisz nowe wartosci do rejestr�w INT_PIN_CFG oraz INT_ENABLE
	this->write(MPU6050_REGISTER_INT_PIN_CFG,MPU6050_temp_buff,2);

	//REJESTR I2C_MST_CTRL
	// odczytaj rejestr I2C_MST_CTRL
	this->read(MPU6050_REGISTER_I2C_MST_CTRL,MPU6050_temp_buff,1);


	// I2C_MST_CTRL -> WAIT_FOR_ES
	// wyzeruj bit WAIT_FOR_ES
	MPU6050_temp_buff[0] &= (~MPU6050_WAIT_FOR_ES_Mask);
	// nowa wartos� bitu WAIT_FOR_ES
	MPU6050_temp_buff[0] |= (uint8_t)(MPU6050_InterruptsInitStruct->MPU6050_DataReadyWaitForExternalSesnor << MPU6050_WAIT_FOR_ES_Bit0Position);

	// wpisz now� wartos� rejestru I2C_MST_CTRL
	this->write(MPU6050_REGISTER_I2C_MST_CTRL,MPU6050_temp_buff,1);
}
// funkcja inicjalizuje rejestry odpowiedzialne za prac� Auxiliary I2C
void kMPU6050::AuxiliaryI2CInit(MPU6050_AuxiliaryI2C_InitStruct_TypeDef * MPU6050_AuxiliaryI2C_InitStruct)
{
	uint8_t MPU6050_temp_buff[2];

	// I2C_MST_CTRL

	// Odczytaj rejestr I2C_MST_CTRL
	this->read(MPU6050_REGISTER_I2C_MST_CTRL,MPU6050_temp_buff,1);

	// wyczys� ustawiane bity
	MPU6050_temp_buff[0] &= (~MPU6050_AuxiliaryI2CInit_Assert_Mask);

	// u�yj jako zmiennej pomocniczej
	// MULT_MST_EN
	MPU6050_temp_buff[1] = (uint8_t)(MPU6050_AuxiliaryI2C_InitStruct->MPU6050_AuxiliaryI2C_MultiMaster << MPU6050_MULT_MST_EN_Bit0Position);

	// I2C_MST_P_NSR
	MPU6050_temp_buff[1] |= (uint8_t)(MPU6050_AuxiliaryI2C_InitStruct->MPU6050_AuxiliaryI2C_StoppingTransmission << MPU6050_I2CMST_P_NSR_Bit0Position);

	// I2C_MST_CLK
	MPU6050_temp_buff[1] |= (uint8_t)(MPU6050_AuxiliaryI2C_InitStruct->MPU6050_AuxiliaryI2C_ClockSpeed);

	// wpisz ustawiane bity
	MPU6050_temp_buff[0] |= MPU6050_temp_buff[1];

	// zapisz now� wartos� rejestru I2C_MST_CTRL
	this->write(MPU6050_REGISTER_I2C_MST_CTRL,MPU6050_temp_buff,1);

	// REJESTR I2C_MST_DELAY_CTRL
	// Odczytaj rejestr I2C_MST_DELAY_CTRL
	this->read(MPU6050_REGISTER_I2CMSTDELAYCTRL,MPU6050_temp_buff,1);

	// DELAY_ES_SHADOW
	// wyzeruj bit DELAY_ES_SHADOW
	MPU6050_temp_buff[0] &= (~MPU6050_DELAYES_SHADOW_Mask);
	// wstaw now� wartos� bitu DELAY_ES_SHADOW
	MPU6050_temp_buff[0] |= (uint8_t)(MPU6050_AuxiliaryI2C_InitStruct->MPU6050_ExternalSensorDataShadowingDelay << MPU6050_DELAYES_SHADOW_Bit0Position);

	// zapisz now� wartos� rejestru I2C_MST_DELAY_CTRL
	this->write(MPU6050_REGISTER_I2CMSTDELAYCTRL,MPU6050_temp_buff,1);
}
// funkcja inicjalizuje prac� MPU6050 do obs�ugi dadatkowego uk�adu pod��czonego do Auxiliary I2C
void kMPU6050::SlaveInit(MPU6050_SlaveInitStruct_TypeDef * MPU6050_SlaveInitStruct)
{
	uint8_t MPU6050_temp_buff[4];

	// I2C_MST_DELAY_CTRL

	// Odczytaj rejestr I2C_MST_DELAY_CTRL
	this->read(MPU6050_REGISTER_I2CMSTDELAYCTRL,MPU6050_temp_buff,1);


	// u�yj jako zmiennej pomocniczej
	// utw�rz mask�
	MPU6050_temp_buff[1] = (uint8_t)(1 << MPU6050_SlaveInitStruct->MPU6050_Slave);
	//wyzeruj bit I2C_SLVx_DLY_EN
	MPU6050_temp_buff[0] &= (~MPU6050_temp_buff[1]);
	// u�yj jako zmiennej pomocniczej
	MPU6050_temp_buff[1] = (uint8_t)(MPU6050_SlaveInitStruct->MPU6050_SlaveDecreasedAccessingRate << MPU6050_SlaveInitStruct->MPU6050_Slave);
	// wpisz now� wartos� bitu I2C_SLVx_DLY_EN
	MPU6050_temp_buff[0] |= MPU6050_temp_buff[1];

	// zapisz now� wartos� rejestru I2C_MST_DELAY_CTRL
	this->write(MPU6050_REGISTER_I2CMSTDELAYCTRL,MPU6050_temp_buff,1);


	if(MPU6050_SlaveInitStruct->MPU6050_Slave < 4)
	{

		// I2C_SLVx_ADDR


		MPU6050_temp_buff[0] = MPU6050_SlaveInitStruct->MPU6050_Slave7bitAddress | (uint8_t)(MPU6050_SlaveInitStruct->MPU6050_SlaveTransferDirection << MPU6050_I2CSLV0_RW_Bit0Position);
		// I2C_SLVx_REG
		MPU6050_temp_buff[1] = MPU6050_SlaveInitStruct->MPU6050_SlaveStartingRegisterAddress;


		// I2C_SLVx_CTRL

		// I2C_SLV0_BYTE_SW
		MPU6050_temp_buff[2] = (uint8_t)(MPU6050_SlaveInitStruct->MPU6050_SlaveByteSwapping << MPU6050_I2CSLV0_BYTE_SW_Bit0Position);
		// I2C_SLV0_REG_DIS
		MPU6050_temp_buff[2] |= (uint8_t)(MPU6050_SlaveInitStruct->MPU6050_SlaveSendRegisterAddress << MPU6050_I2CSLV0_REG_DIS_Bit0Position);
		// I2C_SLV0_GRP
		MPU6050_temp_buff[2] |= (uint8_t)(MPU6050_SlaveInitStruct->MPU6050_SlaveRecievedBytesGroupingOrder << MPU6050_I2CSLV0_GRP_Bit0Position);

		// I2C_SLV0_LEN
		// u�yj jako zmiennej pomocniczej
		// chro� przed b�ednymi parametrami
		MPU6050_temp_buff[3] = (uint8_t)(MPU6050_SlaveInitStruct->MPU6050_SlaveBytesToTransfer & MPU6050_I2C_SLV0_LEN_Mask);

		MPU6050_temp_buff[2] |= MPU6050_temp_buff[3];

		// oblicz adres pocz�tkowego rejestru do wpisania (kt�ry Slave?)
		// u�yj jako zmiennej pomocniczej
		MPU6050_temp_buff[3] = MPU6050_REGISTER_I2C_SLV0_ADDR + MPU6050_SlaveInitStruct->MPU6050_Slave*0x03;

		// zapisz nowe wartosci rejestr�w I2C_SLVx_ADDR, I2C_SLVx_REG, I2C_SLVx_CTRL
		this->write(MPU6050_temp_buff[3],MPU6050_temp_buff,3);

	}else if(MPU6050_SlaveInitStruct->MPU6050_Slave == MPU6050_Slave_4)
	{
		// uk�ad obs�ugi slave 4 ma pewne ograniczenia, pozosta�e parametry nie b�d� brane pod uwag�

		// I2C_SLV4_ADDR
		MPU6050_temp_buff[0] = MPU6050_SlaveInitStruct->MPU6050_Slave7bitAddress | (uint8_t)(MPU6050_SlaveInitStruct->MPU6050_SlaveTransferDirection << MPU6050_I2CSLV4_RW_Bit0Position);
		// I2C_SLV4_REG
		MPU6050_temp_buff[1] = MPU6050_SlaveInitStruct->MPU6050_SlaveStartingRegisterAddress;

		// zapisz nowe wartosci rejestr�w I2C_SLV4_ADDR, I2C_SLV4_REG
		this->write(MPU6050_REGISTER_I2C_SLV4_ADDR,MPU6050_temp_buff,2);

		// odczytaj zawartos� rejestru I2C_SLV4_CTRL
		this->read(MPU6050_REGISTER_I2C_SLV4_CTRL,MPU6050_temp_buff,1);

		// I2C_SLV4_REG_DIS
		// wykasuj bit I2C_SLV4_REG_DIS
		MPU6050_temp_buff[0] &= (~MPU6050_I2CSLV4_REG_DIS_Mask);
		// nanies now� wartos�
		MPU6050_temp_buff[0] |= (uint8_t)(MPU6050_SlaveInitStruct->MPU6050_SlaveSendRegisterAddress << MPU6050_I2CSLV4_REG_DIS_Bit0Position);

		// zapisz now� wartos� rejestru I2C_SLV4_CTRL
		this->write(MPU6050_REGISTER_I2C_SLV4_CTRL,MPU6050_temp_buff,1);

	}
}
// funkcja w��cza/wy��cza buforowanie FIFO dla okreslonych danych z czujnik�w
void kMPU6050::FIFOsetBufferedData(uint16_t MPU6050_FIFOBufferData,FunctionalState NewState)
{
	uint8_t MPU6050_temp_buff[2];

	// pomocniczo
	uint8_t reg1 = (uint8_t)MPU6050_FIFOBufferData;
	uint8_t reg2 = (uint8_t)(MPU6050_FIFOBufferData >> 8);



	// Odczytaj rejestry FIFO_EN, I2C_MST_CTRL
	this->read(MPU6050_REGISTER_FIFO_EN,MPU6050_temp_buff,2);

	// w��czy� czy wy��czy�?
	if(NewState == ENABLE)
	{
		//ustaw okreslone bity
		// FIFO_EN
		MPU6050_temp_buff[0] |= reg1;
		// I2C_MST_CTRL -> SLV_3_FIFO_EN
		MPU6050_temp_buff[1] |= reg2;

	}else
	{
		// wykasuj okreslone bity
		// FIFO_EN
		MPU6050_temp_buff[0] &= (~reg1);
		// I2C_MST_CTRL -> SLV_3_FIFO_EN
		MPU6050_temp_buff[0] &= (~reg2);
	}

	// zapisz nowe wartosci rejestr�w FIFO_EN, I2C_MST_CTRL
	this->write(MPU6050_REGISTER_FIFO_EN,MPU6050_temp_buff,2);
}
// funkcja w��cza/wy��cza kontrol� nad Auxiliary I2C przez host (aplikacj� u�ytkownika)
void kMPU6050::I2CBypass(FunctionalState NewState)
{
	uint8_t MPU6050_temp_buff[1];

	// Odczytaj rejestr INT_PIN_CFG
	this->read(MPU6050_REGISTER_INT_PIN_CFG,MPU6050_temp_buff,1);

	// w��czy� czy wy��czy�?
	if(NewState == ENABLE)
	{
		// ustaw bit I2C_BYPASS_EN
		MPU6050_temp_buff[0] |= MPU6050_I2CBYPASS_EN_Mask;
	}else
	{
		// wykasuj bit I2C_BYPASS_EN
		MPU6050_temp_buff[0] &= (~MPU6050_I2CBYPASS_EN_Mask);
	}

	// zapisz now� wartos� rejestru INT_PIN_CFG
	this->write(MPU6050_REGISTER_INT_PIN_CFG,MPU6050_temp_buff,1);

}
// funkcja konwertuje pomiary do jednostek uk�adu SI (opr�cz temperatury kt�ra podawana jest w stopniach Celsjusza)
void kMPU6050::MeasurementsToPhysicalUnits(void)
{
	// ACC
	// x
	this->acc.x = (float)this->rawData.ACC_X;
	this->acc.x /= MPU6050_Acc_LSB_Sensitivity[this->MPU6050_currentAccFullScaleRangeOption];

	// y
	this->acc.y = (float)this->rawData.ACC_Y;
	this->acc.y /= MPU6050_Acc_LSB_Sensitivity[this->MPU6050_currentAccFullScaleRangeOption];
	// z
	this->acc.z = (float)this->rawData.ACC_Z;
	this->acc.z /= MPU6050_Acc_LSB_Sensitivity[this->MPU6050_currentAccFullScaleRangeOption];

	// GYRO
	// x
	this->gyro.x = (float)this->rawData.GYRO_X;
	this->gyro.x /= MPU6050_Gyro_LSB_Sensitivity[this->MPU6050_currentGyroFullScaleRangeOption];
	// y
	this->gyro.y = (float)this->rawData.GYRO_Y;
	this->gyro.y /= MPU6050_Gyro_LSB_Sensitivity[this->MPU6050_currentGyroFullScaleRangeOption];
	// z
	this->gyro.z = (float)this->rawData.GYRO_Z;
	this->gyro.z /= MPU6050_Gyro_LSB_Sensitivity[this->MPU6050_currentGyroFullScaleRangeOption];

	// TEMP
	this->temperature = (float)(this->rawData.TEMP);
	this->temperature /= 340;
	this->temperature += 36.53;
}
