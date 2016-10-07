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

	// macros
	#define K_UNUSED(param) (void)param
	#define K_PERFORMANCE(operating_function,result) \
	result = kSystem.micros();\
	operating_function;\
	result -= kSystem.micros()



	#define kMACRO_GET_PIN_ATTRIBUTE(c,d) 0x000000##c##d
	#define kMACRO_GET_PORT_STRING(name,pin) PORT##name##pin
	#define kMACRO_GET_PORT_PIN_ENUM(name,pin,pV,piV) kMACRO_GET_PORT_STRING(name,pin)\
		=kMACRO_GET_PIN_ATTRIBUTE(pV,piV) \


	#define kMACRO_GET_PORT_16PINS_ENUM(PORT_INDEX,PORT_VALUE) \
		kMACRO_GET_PORT_PIN_ENUM(PORT_INDEX,0,PORT_VALUE,0),\
		kMACRO_GET_PORT_PIN_ENUM(PORT_INDEX,1,PORT_VALUE,1),\
		kMACRO_GET_PORT_PIN_ENUM(PORT_INDEX,2,PORT_VALUE,2),\
		kMACRO_GET_PORT_PIN_ENUM(PORT_INDEX,3,PORT_VALUE,3),\
		kMACRO_GET_PORT_PIN_ENUM(PORT_INDEX,4,PORT_VALUE,4),\
		kMACRO_GET_PORT_PIN_ENUM(PORT_INDEX,5,PORT_VALUE,5),\
		kMACRO_GET_PORT_PIN_ENUM(PORT_INDEX,6,PORT_VALUE,6),\
		kMACRO_GET_PORT_PIN_ENUM(PORT_INDEX,7,PORT_VALUE,7),\
		kMACRO_GET_PORT_PIN_ENUM(PORT_INDEX,8,PORT_VALUE,8),\
		kMACRO_GET_PORT_PIN_ENUM(PORT_INDEX,9,PORT_VALUE,9),\
		kMACRO_GET_PORT_PIN_ENUM(PORT_INDEX,10,PORT_VALUE,A),\
		kMACRO_GET_PORT_PIN_ENUM(PORT_INDEX,11,PORT_VALUE,B),\
		kMACRO_GET_PORT_PIN_ENUM(PORT_INDEX,12,PORT_VALUE,C),\
		kMACRO_GET_PORT_PIN_ENUM(PORT_INDEX,13,PORT_VALUE,D),\
		kMACRO_GET_PORT_PIN_ENUM(PORT_INDEX,14,PORT_VALUE,E),\
		kMACRO_GET_PORT_PIN_ENUM(PORT_INDEX,15,PORT_VALUE,F)\

	#define kMACRO_GET_ALL_PORTS_PINS_ENUM \
		kMACRO_GET_PORT_16PINS_ENUM(A,0),\
		kMACRO_GET_PORT_16PINS_ENUM(B,1),\
		kMACRO_GET_PORT_16PINS_ENUM(C,2),\
		kMACRO_GET_PORT_16PINS_ENUM(D,3),\
		kMACRO_GET_PORT_16PINS_ENUM(E,4),\
		kMACRO_GET_PORT_16PINS_ENUM(F,5),\
		kMACRO_GET_PORT_16PINS_ENUM(G,6),\
		kMACRO_GET_PORT_16PINS_ENUM(H,7),\
		kMACRO_GET_PORT_16PINS_ENUM(I,8)\


#define kMACRO_GET_DRIVE_RESULT_ENUM \



