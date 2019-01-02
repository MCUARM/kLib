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



#ifndef __kRTOS_H
#define __kRTOS_H

	#if (kLib_config_USE_RTOS == 1)

	#include "FreeRTOS.h"
	#include "FreeRTOSConfig.h"
	#include "task.h"
	#include "portable.h"



		class kRTOS
		{
			public:

			typedef void * task_t;
			typedef uint32_t tick_t;


			static __inline__ void taskCreate(void (*function_handler)(void*),const char * task_name,unsigned int stack_size,void * const params,unsigned long priority,task_t * const created_task) __attribute__((always_inline));
			static void taskCreateScheduled(void (*function_handler)(void*),const char * task_name,unsigned int stack_size,void * const params,unsigned long priority,task_t * const created_task,tick_t scheduleInterval);
			static __inline__ void run(void) __attribute__((always_inline));
			static __inline__ void taskDelayUntil(tick_t * previous_wake_time_ms, const tick_t time_increment_ms)__attribute__((always_inline));
			static __inline__ void taskDelay(const tick_t time_increment_ms)__attribute__((always_inline));
			static __inline__ tick_t taskGetTickCount(void) __attribute__((always_inline));
			static __inline__ void taskYield(void);

		};

		__attribute__((always_inline)) void kRTOS::taskCreate(void (*function_handler)(void*),const char * task_name,unsigned int stack_size,void * const params,unsigned long priority,kRTOS::task_t * const created_task)
		{
			xTaskCreate(function_handler,task_name,stack_size,params,priority,created_task);
		}
		
		__attribute__((always_inline)) void kRTOS::run(void)
		{
			vTaskStartScheduler();
		}
		__attribute__((always_inline)) void kRTOS::taskDelayUntil(tick_t * previous_wake_time_ms, const tick_t time_increment_ms)
		{
			vTaskDelayUntil(previous_wake_time_ms,time_increment_ms);
		}
		__attribute__((always_inline)) void kRTOS::taskDelay(const tick_t time_increment_ms)
		{
			vTaskDelay(time_increment_ms);
		}
		__attribute__((always_inline)) kRTOS::tick_t kRTOS::taskGetTickCount(void)
		{
			return xTaskGetTickCount();
		}
		__attribute__((always_inline)) void kRTOS::taskYield(void)
		{
			taskYIELD();
		}

	#endif

#endif
