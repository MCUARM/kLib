
#ifndef __kSerial_H
#define __kSerial_H

	/*
	 * Includes
	 */

	#include "stm32f4xx_usart.h"
	#include "kPort.h"
	#include "stm32f4xx_rcc.h"
	#include "kString.h"
	#include "kSystem.h"


	#define kSerial_rxBuffer_size 512


	typedef struct
	{
		unsigned char kUSART1pin;
	}kSerialUSART1Pin;

	typedef struct
	{
		kSerialUSART1Pin PORTA10;
		kSerialUSART1Pin PORTB7;
	}kSerialRxUSART1;

	typedef struct
	{
		kSerialUSART1Pin PORTA9;
		kSerialUSART1Pin PORTB6;
	}kSerialTxUSART1;

	typedef struct
	{
		kSerialRxUSART1 RX;
		kSerialTxUSART1 TX;
	}kSerialUSART1;

	typedef struct
	{
		unsigned char kUSART2pin;
	}kSerialUSART2Pin;

	typedef struct
	{
		kSerialUSART2Pin PORTA3;
		kSerialUSART2Pin PORTD6;
	}kSerialRxUSART2;

	typedef struct
	{
		kSerialUSART2Pin PORTA2;
		kSerialUSART2Pin PORTD5;
	}kSerialTxUSART2;

	typedef struct
	{
		kSerialRxUSART2 RX;
		kSerialTxUSART2 TX;
	}kSerialUSART2;

	typedef struct
	{
		unsigned char kUSART3pin;
	}kSerialUSART3Pin;

	typedef struct
	{
		kSerialUSART3Pin PORTB11;
		kSerialUSART3Pin PORTC11;
		kSerialUSART3Pin PORTD9;
	}kSerialRxUSART3;

	typedef struct
	{
		kSerialUSART3Pin PORTB10;
		kSerialUSART3Pin PORTC10;
		kSerialUSART3Pin PORTD8;
	}kSerialTxUSART3;

	typedef struct
	{
		kSerialRxUSART3 RX;
		kSerialTxUSART3 TX;
	}kSerialUSART3;


	class kSerialHardware
	{
		private:

			void setupRxPin(void);
			void setupTxPin(void);



		public:

			USART_TypeDef * usart;
			GPIO_TypeDef * rxGPIO;
			GPIO_TypeDef * txGPIO;
			unsigned char rxPin;
			unsigned char txPin;

			kSerialHardware& operator = (const kSerialUSART1Pin & usartHard);
			kSerialHardware& operator = (const kSerialUSART2Pin & usartHard);
			kSerialHardware& operator = (const kSerialUSART3Pin & usartHard);


			kSerialHardware& operator , (const kSerialUSART1Pin & usartHard);
			kSerialHardware& operator , (const kSerialUSART2Pin & usartHard);
			kSerialHardware& operator , (const kSerialUSART3Pin & usartHard);


	};



 	class kSerial {

 		protected:

			unsigned int k_timeout;
			char k_terminator;
			unsigned char dataCounter;
			bool useTerminator;


			unsigned long long k_precision;

			char rxBuffer[kSerial_rxBuffer_size];
			unsigned short int rx_buffer_size;
			unsigned short int rx_buffer_read_pointer;
			unsigned short int rx_buffer_write_pointer;


			void attachUSART(void);

		public:


			//constants
 			static const char * endl;
 			static const kSerialUSART1 * usart1;
 			static const kSerialUSART2 * usart2;
 			static const kSerialUSART3 * usart3;

 			kSerialHardware hardware;




 			//constructors
 			kSerial(void);
 			kSerial(const kSerial & other);
 			kSerial(const kSerialUSART1Pin & Rx,const kSerialUSART1Pin & Tx,unsigned int BaudRate);
 			kSerial(const kSerialUSART1Pin & Pin,unsigned int BaudRate);
 			kSerial(const kSerialUSART2Pin & Rx,const kSerialUSART2Pin & Tx,unsigned int BaudRate);
 			kSerial(const kSerialUSART2Pin & Pin,unsigned int BaudRate);
 			kSerial(const kSerialUSART3Pin & Rx,const kSerialUSART3Pin & Tx,unsigned int BaudRate);
 			kSerial(const kSerialUSART3Pin & Pin,unsigned int BaudRate);



			void run(unsigned int BaudRate);
			void timeout(unsigned int ticks);
			void precision(unsigned char precision_points);
			void terminator(unsigned char character);

 			unsigned short int newBytesAvailable(void);
			char getChar(void);
			char readByte(void);
			unsigned short int readAll(char * buffer);

			unsigned char newDataAvailable(void);
			unsigned short int readData(char * buffer);
			unsigned short int readAllData(char * buffer);

			friend const kSerial& operator <<(const kSerial &serial,const char * String);
			friend const kSerial& operator <<(const kSerial &serial,char chr);
			friend const kSerial& operator <<(const kSerial &serial,int number);
			friend const kSerial& operator <<(const kSerial &serial,unsigned int number);
			friend const kSerial& operator <<(const kSerial &serial,float number);
			friend const kSerial& operator <<(const kSerial &serial,const kString & str);

	};




#endif
