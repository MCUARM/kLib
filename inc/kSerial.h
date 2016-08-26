
#ifndef __kSerial_H
#define __kSerial_H

	/*
	 * Includes
	 */

	#include "kConfig.h"
	#include "kString.h"
	#include "kSystem.h"
	#include "kMath.h"
	#include "kPort.h"

	#include "stm32f4xx_usart.h"
	#include "stm32f4xx_rcc.h"

	#define kSerial_rxBuffer_size 512


	typedef struct
	{
		typedef enum
		{
			PORTA10 = 0x0C22270A,
			PORTB7  = 0x0C222717
		}kSerial_USART1_RX_Pin;

	}kSerial_USART1_RX;

	typedef struct
	{
		typedef enum
		{
			PORTA9 = 0x14222709,
			PORTB6 = 0x14222716
		}kSerial_USART1_TX_Pin;

	}kSerial_USART1_TX;

	typedef struct
	{
		kSerial_USART1_RX RX;
		kSerial_USART1_TX TX;
	}kSerial_USART1;

	typedef struct
	{
		typedef enum
		{
			PORTA3 = 0x0988A703,
			PORTD6 = 0x0988A736
		}kSerial_USART2_RX_Pin;

	}kSerial_USART2_RX;

	typedef struct
	{
		typedef enum
		{
			PORTA2 = 0x1188A702,
			PORTD5 = 0x1188A735
		}kSerial_USART2_TX_Pin;

	}kSerial_USART2_TX;

	typedef struct
	{
		kSerial_USART2_RX RX;
		kSerial_USART2_TX TX;
	}kSerial_USART2;


	typedef struct
	{
		typedef enum
		{
			PORTB11 = 0x0A89271B,
			PORTC11 = 0x0A89272B,
			PORTD9  = 0x0A892739
		}kSerial_USART3_RX_Pin;

	}kSerial_USART3_RX;

	typedef struct
	{
		typedef enum
		{
			PORTB10 = 0x1289271A,
			PORTC10 = 0x1289272A,
			PORTD8  = 0x12892738
		}kSerial_USART3_TX_Pin;

	}kSerial_USART3_TX;

	typedef struct
	{
		kSerial_USART3_RX RX;
		kSerial_USART3_TX TX;
	}kSerial_USART3;


	typedef struct
	{
		typedef enum
		{
			PORTA1  = 0x104C2801,
			PORTC11 = 0x104C282B
		}kSerial_UART4_RX_Pin;

	}kSerial_UART4_RX;

	typedef struct
	{
		typedef enum
		{
			PORTA0  = 0x204C2800,
			PORTC10 = 0x204C282A
		}kSerial_UART4_TX_Pin;

	}kSerial_UART4_TX;

	typedef struct
	{
		kSerial_UART4_RX RX;
		kSerial_UART4_TX TX;
	}kSerial_UART4;

	typedef struct
	{
		typedef enum
		{
			PORTD2 = 0x10502832
		}kSerial_UART5_RX_Pin;

	}kSerial_UART5_RX;

	typedef struct
	{
		typedef enum
		{
			PORTC12 = 0x2050282C
		}kSerial_UART5_TX_Pin;

	}kSerial_UART5_TX;

	typedef struct
	{
		kSerial_UART5_RX RX;
		kSerial_UART5_TX TX;
	}kSerial_UART5;


	typedef struct
	{
		typedef enum
		{
			PORTC7 = 0x11142287,
			PORTG9 = 0x11142689
		}kSerial_USART6_RX_Pin;

	}kSerial_USART6_RX;

	typedef struct
	{
		typedef enum
		{
			PORTC6  = 0x21142286,
			PORTG14 = 0x2114268E
		}kSerial_USART6_TX_Pin;

	}kSerial_USART6_TX;

	typedef struct
	{
		kSerial_USART6_RX RX;
		kSerial_USART6_TX TX;
	}kSerial_USART6;

	typedef struct
	{
		typedef enum
		{
			PORTE7 = 0x10782487,
			PORTF6 = 0x10782586
		}kSerial_UART7_RX_Pin;

	}kSerial_UART7_RX;

	typedef struct
	{
		typedef enum
		{
			PORTE8 = 0x20782488,
			PORTF7 = 0x20782587
		}kSerial_UART7_TX_Pin;

	}kSerial_UART7_TX;

	typedef struct
	{
		kSerial_UART7_RX RX;
		kSerial_UART7_TX TX;
	}kSerial_UART7;

	typedef struct
	{
		typedef enum
		{
			PORTE0 = 0x107C2480
		}kSerial_UART8_RX_Pin;

	}kSerial_UART8_RX;

	typedef struct
	{
		typedef enum
		{
			PORTE1 = 0x207C2481
		}kSerial_UART8_TX_Pin;

	}kSerial_UART8_TX;

	typedef struct
	{
		kSerial_UART8_RX RX;
		kSerial_UART8_TX TX;
	}kSerial_UART8;




	class kSerial;

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


			class kSerialHardware
			{
				friend class kSerial;

				public:

					USART_TypeDef * usart;
					kSerialHardware& operator = (unsigned int pwmHard);

			};

 			kSerialHardware hardware;

			//constants
 			static const char * endl;
 			static const kSerial_USART1 * usart1;
 			static const kSerial_USART2 * usart2;
 			static const kSerial_USART3 * usart3;
 			static const kSerial_UART4  * uart4;
 			static const kSerial_UART5  * uart5;
 			static const kSerial_USART6 * usart6;
 			static const kSerial_UART7  * uart7;
 			static const kSerial_UART8  * uart8;


 			//constructors
 			kSerial(void);


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
			friend const kSerial& operator <<(const kSerial &serial,const kVector3 & v);
			friend const kSerial& operator <<(const kSerial &serial,const kQuaternion & q);
			friend const kSerial& operator <<(const kSerial &serial,const kAxisAngle & axis_angle);

	};




#endif
