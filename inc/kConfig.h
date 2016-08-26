#ifndef __kConfig_H
#define __kConfig_H

	// kLib configuration file

	#define kLib_STM32F407xx 1
	#define kLib_STM32F411xx 2
	#define kLib_STM32F429xx 3

	// PLATFORM SELECTION
	// Uncomment one line below

		//#define kLib_config_PLATFORM kLib_STM32F411xx
		//#define kLib_config_PLATFORM kLib_STM32F407xx
		#define kLib_config_PLATFORM kLib_STM32F429xx


	#ifndef kLib_config_PLATFORM
		#error "Please select platform first in kConfig.h header file"
	#endif


	// GENERAL SETTINGS
	#define kLib_config_USE_RTOS 0
	#define kLib_config_USE_MODULE 0


	// kPort settings
	// Uncomment line(s) below if you want to declare kPort PORTx object
	#define kPort_config_USE_PORTA_OBJECT
	#define kPort_config_USE_PORTB_OBJECT
	#define kPort_config_USE_PORTC_OBJECT
	#define kPort_config_USE_PORTD_OBJECT
	//#define kPort_config_USE_PORTE_OBJECT
	//#define kPort_config_USE_PORTF_OBJECT
	//#define kPort_config_USE_PORTG_OBJECT
	//#define kPort_config_USE_PORTH_OBJECT
	//#define kPort_config_USE_PORTI_OBJECT
	//#define kPort_config_USE_PORTJ_OBJECT
	//#define kPort_config_USE_PORTK_OBJECT


#endif





#if (kLib_config_PLATFORM == kLib_STM32F411xx) || \
	(kLib_config_PLATFORM == kLib_STM32F407xx) || \
	(kLib_config_PLATFORM == kLib_STM32F429xx)

	#include "stm32f4xx.h"

#endif
