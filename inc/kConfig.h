/***********************************************************************************
 *                                                                                 *
 *   kLib - C++ development tools for ARM Cortex-M devices                         *
 *                                                                                 *
 *     Copyright (c) 2016, project author Paweł Zalewski                                          *
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
