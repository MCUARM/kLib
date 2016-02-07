/**
  ******************************************************************************
  * @file    kPort.h
  * @author  Ko�o Naukowe Kosmonautyki Politechnika Rzeszowska
  * @version V1.0.0
  * @date    29-October-2015
  * @brief   This file contains all the classes and functions prototypes for using
  *          General Purpose Input Output.
  ******************************************************************************
  * <h2><center>&copy; COPYRIGHT 2015 Ko�o Naukowe Kosmonautyki
  * Politechnika Rzeszowska</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __kPort_H
#define __kPort_H

/* Includes ------------------------------------------------------------------*/
	#include "stm32f4xx.h"
	#include "stm32f4xx_gpio.h"

	/**
	  * @brief  kPin class definition which is used to handle input/output pin
	  * functionality
	  */
	class kPin
	{
		// public access
		public:

			/**
			  * @brief  Definition of type containing pin modes
			  */
			typedef enum
			{
				in,			/*!< Input mode */
				out,		/*!< Output mode */
				alternate,	/*!< Alternate function mode - pin is controlled by other hardware, i.e. USART */
				analog		/*!< Analog mode - mode used with ADC */
			}kPinMode;

			/**
			  * @brief  Definition of type containing output mode types
			  */
			typedef enum
			{
				PushPull,	/*!< Push-Pull output */
				OpenDrain	/*!< Open-Drain output */
			}kPinOutType;

			/**
			  * @brief  Definition of type containing pull resistors settings
			  */
			typedef enum
			{
				NoPull,		/*!< No pull resistors */
				PullUp,		/*!< Use pull-up resistor */
				PullDown	/*!< Use pull-down resistor */
			}kPullResistor;

			/**
			  * @brief  Definition of type containing maximum state toggling frequencies of pin
			  */
			typedef enum
			{
				LowSpeed,		/*!< low speed - up to 2Mhz */
				MediumSpeed,	/*!< medium speed - up to 25Mhz */
				HighSpeed,		/*!< high speed - up to 50Mhz */
				VeryHighSpeed	/*!< very high speed - up to 100Mhz */
			}kPinSpeed;

		//public properties

			GPIO_TypeDef * gpio;
			unsigned char pin;

		//constructors

			//default constructor
			kPin(void);
			//constructor with hardware attachment
			kPin(GPIO_TypeDef * GPIO,unsigned char PIN);
			//copy constructor
			kPin(const kPin & pin);

		//destructor


		//public methods

			// get actual state on pin
			unsigned char get(void);
			// set pin (writes 1), this function has an effect only in output mode
			void set(void);
			// reset pin (writes 0), this function has an effect only in output mode
			void reset(void);
			// toggle state on pin (when 1 set to 0; when 0 set to 1), this function has an effect only in output mode
			void toggle(void);

		//operators overloading

			// writes new state on pin
			void operator = (unsigned char state);
			// setup pin mode
			const kPin& operator = (kPinMode mode);
			// setup pin output mode
			const kPin& operator = (kPinOutType outType);
			// setup pin Pull-Up,Pull-Down resistors
			const kPin& operator = (kPullResistor pullResistor);
			// setup maximum pin toggling frequency
			const kPin& operator = (kPinSpeed speed);

			// writes the same state on pin as in given pin in argument
			void operator = (kPin & pin);

		//friends functions - descriptions as above

			friend const kPin& operator , (const kPin& pin, kPinMode mode);
			friend const kPin& operator , (const kPin& pin, kPinOutType outType);
			friend const kPin& operator , (const kPin& pin, kPullResistor pullResistor);
			friend const kPin& operator , (const kPin& pin, kPinSpeed speed);

		//type conversion functions

			//specifies conversion from kPin to unsigned char. This function is equal to get() function
			operator unsigned char();



	};

 	class kPort {

 		private:

			GPIO_TypeDef * gpio;

		public:

			typedef enum
			{
				off,
				on
			}kPortPower;

			kPort(GPIO_TypeDef * GPIO);
			kPin operator [](const unsigned char pin);
			void operator = (const unsigned int state);

			void operator = (kPortPower power);
			operator unsigned short int();

	};

 	extern kPort PORTA;
 	extern kPort PORTB;
 	extern kPort PORTC;
 	extern kPort PORTD;
 	extern kPort PORTE;
 	extern kPort PORTF;
 	extern kPort PORTG;
 	extern kPort PORTH;
 	extern kPort PORTI;


#endif
