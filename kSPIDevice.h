
#ifndef __kSPIDevice_H
#define __kSPIDevice_H

	#include "stm32f4xx_spi.h"
	#include "kPort.h"

	class kSPIDevice;
	class kSPIDeviceHardware;


	typedef struct
	{
		unsigned char kSPIpin;
	}kSPI1pin;

	typedef struct
	{
		kSPI1pin PORTA4;
		kSPI1pin PORTA15;

	}kSPI1_NSS_Pin;

	typedef struct
	{
		kSPI1pin PORTA5;
		kSPI1pin PORTB3;
	}kSPI1_SCK_Pin;

	typedef struct
	{
		kSPI1pin PORTA6;
		kSPI1pin PORTB4;
	}kSPI1_MISO_Pin;

	typedef struct
	{
		kSPI1pin PORTA7;
		kSPI1pin PORTB5;
	}kSPI1_MOSI_Pin;

	typedef struct
	{
		kSPI1_MISO_Pin MISO;
		kSPI1_MOSI_Pin MOSI;
		kSPI1_NSS_Pin NSS;
		kSPI1_SCK_Pin SCK;

	}kSPI1;


	class kSPI
	{
		public:

			static const kSPI1 * SPI_1;

			typedef enum
			{
				Master,
				Slave
			}kSPIMode;

			typedef enum
			{
				NSS_Hard_Control,
				NSS_Soft_Control
			}kSPI_NSS_Control;

			typedef enum
			{
				MSB_First,
				LSB_First
			}kSPI_TransferBitFirst;
			typedef enum
			{
				BaudDiv_2,
				BaudDiv_4,
				BaudDiv_8,
				BaudDiv_16,
				BaudDiv_32,
				BaudDiv_64,
				BaudDiv_128,
				BaudDiv_256
			}kSPI_Baud;

			typedef enum
			{
				SCK_IdleLow,
				SCK_IdleHigh
			}kSPI_CPOL;

			typedef enum
			{
				DataCapture_1Edge,
				DataCapture_2Edge
			}kSPI_CPHA;

			typedef enum
			{
				off,
				on
			}kSPI_power;

	};

	class kSPIDeviceHardware
	{
		private:

			void powerOn(void);

		public:


			unsigned char NSS_idleState;
			bool nss_hard;


			SPI_TypeDef * spi;
			GPIO_TypeDef * misoGPIO;
			GPIO_TypeDef * mosiGPIO;
			GPIO_TypeDef * nssGPIO;
			GPIO_TypeDef * sckGPIO;

			unsigned char misoPin;
			unsigned char mosiPin;
			unsigned char nssPin;
			unsigned char sckPin;

			kSPIDeviceHardware(void);

			kSPIDeviceHardware& operator = (const kSPI1pin & spiHard);
			kSPIDeviceHardware& operator = (const kSPI::kSPIMode mode);
			kSPIDeviceHardware& operator = (const kSPI::kSPI_Baud baud);
			kSPIDeviceHardware& operator = (const kSPI::kSPI_CPHA cpha);
			kSPIDeviceHardware& operator = (const kSPI::kSPI_CPOL cpol);
			kSPIDeviceHardware& operator = (const kSPI::kSPI_NSS_Control nss_control);
			kSPIDeviceHardware& operator = (const kSPI::kSPI_TransferBitFirst endian);
			kSPIDeviceHardware& operator = (const kSPI::kSPI_power pow);

			friend kSPIDeviceHardware& operator , (kSPIDeviceHardware& spiDev,const kSPI1pin & spiHard);
			friend kSPIDeviceHardware& operator , (kSPIDeviceHardware& spiDev,const kSPI::kSPIMode mode);
			friend kSPIDeviceHardware& operator , (kSPIDeviceHardware& spiDev,const kSPI::kSPI_Baud baud);
			friend kSPIDeviceHardware& operator , (kSPIDeviceHardware& spiDev,const kSPI::kSPI_CPHA cpha);
			friend kSPIDeviceHardware& operator , (kSPIDeviceHardware& spiDev,const kSPI::kSPI_CPOL cpol);
			friend kSPIDeviceHardware& operator , (kSPIDeviceHardware& spiDev,const kSPI::kSPI_NSS_Control nss_control);
			friend kSPIDeviceHardware& operator , (kSPIDeviceHardware& spiDev,const kSPI::kSPI_TransferBitFirst endian);
			friend kSPIDeviceHardware& operator , (kSPIDeviceHardware& spiDev,const kSPI::kSPI_power pow);

			void setupMISOPin(void);
			void setupMOSIPin(void);
			void setupNSSPin(void);
			void setupSCKPin(void);

	};

	class kSPIDevice
	{

		public:

			kSPIDeviceHardware hardware;

			void write(unsigned short int BytesToWrite,unsigned char * DataBuffer);
			void write(unsigned char Byte);
			void read(unsigned short int BytesToRead,unsigned char * ReadDataBuffer);
			unsigned char read(void);
			void select(void);
			void deselect(void);
	};



#endif
