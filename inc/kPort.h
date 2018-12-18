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



#ifndef __kPort_H
#define __kPort_H

/* Includes ------------------------------------------------------------------*/
	#include "kSystem.h"


	/**
	  * @brief  kPin class is used as abstract layer to handle input/output pin
	  * functionality
	  */
	class kPin
	{
		// public access
		public:

			typedef enum
			{
				kMACRO_GET_ALL_PORTS_PINS_ENUM
			}kPIN_PIN;


			/**
			  * @brief  Contains available pin modes.
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

			GPIO_TypeDef * gpio;	/*!< specify hardware gpio to control*/
			unsigned char pin;		/*!< specify hardware pin number to control*/

		//constructors

			/**
			  * @brief  Default constructor
			  */
			kPin(void);

			/**
			  * @brief  Constructor with hardware attachment
			  * @param GPIO: pointer to GPIO hardware which will be controlled
			  * @param PIN: specifies pin number (0 to 15)
			  */
			kPin(GPIO_TypeDef * GPIO,unsigned char PIN);
			/**
			  * @brief  Copy constructor
			  * @param pin: reference to copied kPin object
			  */
			kPin(const kPin & pin);


		//public methods

			/**
			  * @brief  Get actual state on pin
			  * @retval 1 if high level occurred
 	 	 	  * @retval 0 when low level
			  */
			unsigned char get(void);

			/**
			  * @brief  set pin (writes 1), this function has an effect only in output mode
			  */
			void set(void);
			/**
			  * @brief  reset pin (writes 0), this function has an effect only in output mode
			  */
			void reset(void);
			/**
			  * @brief  toggle state on pin (when 1 set to 0; when 0 set to 1), this function has an effect only in output mode
			  */
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
			// change current GPIO pin pointing
			void operator = (kPIN_PIN new_pin);

		//friends functions - descriptions as above

			friend const kPin& operator , (const kPin& pin, kPinMode mode);
			friend const kPin& operator , (const kPin& pin, kPinOutType outType);
			friend const kPin& operator , (const kPin& pin, kPullResistor pullResistor);
			friend const kPin& operator , (const kPin& pin, kPinSpeed speed);

		//type conversion functions


			/**
			 * @brief specifies conversion from kPin to unsigned char. This function is equal to get() function
			 */
			operator unsigned char();



	};

	/**
	 *  @brief GPIO abstract layer
	 */
 	class kPort {

 		private:


			GPIO_TypeDef * gpio;

		public:

			/**
			  * @brief  Definition of type containing power states of port
			  */
			typedef enum
			{
				off,	/*!< port is disabled */
				on	/*!< port is enabled */
			}kPortPower;

			/**
			 *  @brief Constructor with hardware attachment
			 *  @param GPIO specifies controlled GPIOx where x can be from A to I
			 */
			kPort(GPIO_TypeDef * GPIO);

			/**
			 *  @brief Returns specified pin from port as kPin object
			 *  @param pin: pin number
			 */
			kPin operator [](const unsigned char pin);


			/**
			 *  @brief Writes binary value to output register
			 *  @param state: new output state on port
			 */
			void operator = (const unsigned int state);

			/**
			 *  @brief Power up/down port
			 *  @param power: new power state of port
			 */
			void operator = (kPortPower power);

			/**
			 *  @brief Get current state of port input register
			 */
			operator unsigned short int();


	};

// region PLATFORM_DEPENDED_STRUCTS

#if (kLib_config_PLATFORM == kLib_STM32F429xx)

	#define kPort_config_USE_PORTA_OBJECT
	#define kPort_config_USE_PORTB_OBJECT
	#define kPort_config_USE_PORTC_OBJECT
	#define kPort_config_USE_PORTD_OBJECT
	#define kPort_config_USE_PORTE_OBJECT
	#define kPort_config_USE_PORTF_OBJECT
	#define kPort_config_USE_PORTG_OBJECT
	#define kPort_config_USE_PORTH_OBJECT

#endif


// endregion PLATFORM_DEPENDED_STRUCTS

	#ifdef kPort_config_USE_PORTA_OBJECT
		extern kPort PORTA;
	#endif
	#ifdef kPort_config_USE_PORTB_OBJECT
		extern kPort PORTB;
	#endif
	#ifdef kPort_config_USE_PORTC_OBJECT
		extern kPort PORTC;
	#endif
	#ifdef kPort_config_USE_PORTD_OBJECT
		extern kPort PORTD;
	#endif
	#ifdef kPort_config_USE_PORTE_OBJECT
		extern kPort PORTE;
	#endif
	#ifdef kPort_config_USE_PORTF_OBJECT
		extern kPort PORTF;
	#endif
	#ifdef kPort_config_USE_PORTG_OBJECT
		extern kPort PORTG;
	#endif
	#ifdef kPort_config_USE_PORTH_OBJECT
		extern kPort PORTH;
	#endif
	#ifdef kPort_config_USE_PORTI_OBJECT
		extern kPort PORTI;
	#endif
	#ifdef kPort_config_USE_PORTJ_OBJECT
		extern kPort PORTJ;
	#endif
	#ifdef kPort_config_USE_PORTK_OBJECT
		extern kPort PORTK;
	#endif
	

#endif
