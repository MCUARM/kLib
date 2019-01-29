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



#ifndef __kMath_H
#define __kMath_H


	#include "kConfig.h"
	#include "kUnits.h"
	#include "kQuaternion.h"
	#include "kVector.h"
	#include "kAxisAngle.h"
	#include "kMatrix.h"


	#define DEG_2_RAD_SCALE_FACTOR (0.017453292)
	#define RAD_2_DEG_SCALE_FACTOR (57.29577951)

	#ifndef M_PI
		#define M_PI ((float)3.14159265359)
	#endif


	class kMath
	{
		public:

			static const float _pi;
			static const float _2pi;

			static float rad2deg(float input);
			static __inline__ kVector3 rad2deg(const kVector3 & v)__attribute__((always_inline));
			static float deg2rad(float input);

			static float abs(float input);
			static float sign(float input);

			static float max(float in_1, float in_2);
			static float min(float in_1, float in_2);

			static __inline__ float sin(float x)__attribute__((always_inline));
			static __inline__ float cos(float x)__attribute__((always_inline));

			static __inline__ float asin(float x)__attribute__((always_inline));
			static __inline__ float acos(float x)__attribute__((always_inline));
			static __inline__ float atan2(float y,float x)__attribute__((always_inline));
	};

	__attribute__((always_inline)) kVector3 kMath::rad2deg(const kVector3 & v)
	{
		return v*RAD_2_DEG_SCALE_FACTOR;
	}

	__attribute__((always_inline)) float kMath::sin(float x)
	{
		#ifdef kLib_config_FAST_TRIGONOMETRIC
			// TODO implementation for fast sin utilising pre-calculated values stored in Flash
			return sinf(x);
		#else

			return sinf(x);
		#endif
	}
	__attribute__((always_inline)) float kMath::cos(float x)
	{
		#ifdef kLib_config_FAST_TRIGONOMETRIC
			// TODO implementation for fast cos utilising pre-calculated values stored in Flash
			return cosf(x);
		#else

			return cosf(x);
		#endif
	}
	__attribute__((always_inline)) float kMath::asin(float x)
	{
		#ifdef kLib_config_FAST_TRIGONOMETRIC
			// TODO implementation for fast asin utilising pre-calculated values stored in Flash
			return asinf(x);
		#else

			return asinf(x);
		#endif
	}
	__attribute__((always_inline)) float kMath::acos(float x)
	{
		#ifdef kLib_config_FAST_TRIGONOMETRIC
			// TODO implementation for fast acos utilising pre-calculated values stored in Flash
			return acosf(x);
		#else

			return acosf(x);
		#endif
	}
	__attribute__((always_inline)) float kMath::atan2(float y,float x)
	{
		#ifdef kLib_config_FAST_TRIGONOMETRIC
			// TODO implementation for fast atan2 utilising pre-calculated values stored in Flash
			return atan2f(y,x);
		#else

			return atan2f(y,x);
		#endif
	}

#endif
