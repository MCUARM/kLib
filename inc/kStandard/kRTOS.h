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
	#include "semphr.h"
	#include "portable.h"



		class kRTOS
		{
			public:

			typedef void * task_t;
			typedef uint32_t tick_t;

			class Notifier
			{
				private:

					uint8_t receivers_length = 0;
					task_t receiver[8];

				protected:

					void notifyAllReceivers(void);

				public:

					void addNotificationReceiver(task_t rx_task);


			};

			class Semaphore
			{
				private:
					SemaphoreHandle_t semaphore_handler;

				public:

					__inline__ bool createBinary(void)__attribute__((always_inline));
					__inline__ BaseType_t take(TickType_t xBlockTime)__attribute__((always_inline));
					__inline__ BaseType_t peek(void)__attribute__((always_inline));
					__inline__ BaseType_t give(void)__attribute__((always_inline));

			};

			class Queue
			{
				private:
					QueueHandle_t queue_handler;

				public:

					__inline__ bool create( const UBaseType_t uxQueueLength, const UBaseType_t uxItemSize)__attribute__((always_inline));
					__inline__ BaseType_t send(const void * const pvItemToQueue, TickType_t xTicksToWait)__attribute__((always_inline));
					__inline__ BaseType_t receive(void * const pvBuffer, TickType_t xTicksToWait)__attribute__((always_inline));


			};


			static __inline__ void taskCreate(void (*function_handler)(void*),const char * task_name,unsigned int stack_size,void * const params,unsigned long priority,task_t * const created_task) __attribute__((always_inline));
			static void taskCreateScheduled(void (*function_handler)(void*),const char * task_name,unsigned int stack_size,void * const params,unsigned long priority,task_t * const created_task,tick_t scheduleInterval);
			static __inline__ void run(void) __attribute__((always_inline));
			static __inline__ void taskDelayUntil(tick_t * previous_wake_time_ms, const tick_t time_increment_ms)__attribute__((always_inline));
			static __inline__ void taskDelay(const tick_t time_increment_ms)__attribute__((always_inline));
			static __inline__ tick_t taskGetTickCount(void) __attribute__((always_inline));
			static __inline__ void taskYield(void)__attribute__((always_inline));

			static __inline__ BaseType_t taskNotifyWait( uint32_t ulBitsToClearOnEntry, uint32_t ulBitsToClearOnExit, uint32_t *pulNotificationValue, TickType_t xTicksToWait )__attribute__((always_inline));
			static __inline__ BaseType_t taskNotifyGive( TaskHandle_t xTaskToNotify)__attribute__((always_inline));
			static __inline__ uint32_t taskNotifyTake( BaseType_t xClearCountOnExit, TickType_t xTicksToWait)__attribute__((always_inline));
			static __inline__ BaseType_t taskNotifyStateClear( TaskHandle_t xTask )__attribute__((always_inline));



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
		__attribute__((always_inline)) bool kRTOS::Queue::create( const UBaseType_t uxQueueLength, const UBaseType_t uxItemSize)
		{
			queue_handler = xQueueCreate(uxQueueLength,uxItemSize);
			return (bool)queue_handler;
		}
		__attribute__((always_inline)) BaseType_t kRTOS::Queue::send(const void * const pvItemToQueue, TickType_t xTicksToWait)
		{
			return xQueueGenericSend(queue_handler,pvItemToQueue,xTicksToWait,queueSEND_TO_BACK);
		}
		__attribute__((always_inline)) BaseType_t kRTOS::Queue::receive(void * const pvBuffer, TickType_t xTicksToWait)
		{
			return xQueueGenericReceive(queue_handler,pvBuffer,xTicksToWait,pdFALSE);
		}

		__attribute__((always_inline)) bool kRTOS::Semaphore::createBinary(void)
		{
			semaphore_handler = xSemaphoreCreateBinary();
			return (bool)semaphore_handler;
		}
		__attribute__((always_inline)) BaseType_t kRTOS::Semaphore::take(TickType_t xBlockTime)
		{
			return xSemaphoreTake(semaphore_handler,xBlockTime);
		}
		__attribute__((always_inline)) BaseType_t kRTOS::Semaphore::give(void)
		{
			return xSemaphoreGive(semaphore_handler);
		}
		__attribute__((always_inline)) BaseType_t kRTOS::Semaphore::peek(void)
		{
			return xQueueGenericReceive((QueueHandle_t)semaphore_handler, NULL, 0, pdTRUE );
		}



		__attribute__((always_inline)) BaseType_t kRTOS::taskNotifyWait( uint32_t ulBitsToClearOnEntry, uint32_t ulBitsToClearOnExit, uint32_t *pulNotificationValue, TickType_t xTicksToWait )
		{
			return xTaskNotifyWait(ulBitsToClearOnEntry,ulBitsToClearOnExit,pulNotificationValue,xTicksToWait);
		}
		__attribute__((always_inline)) BaseType_t kRTOS::taskNotifyGive( TaskHandle_t xTaskToNotify)
		{
			return xTaskNotifyGive(xTaskToNotify);
		}
		__attribute__((always_inline)) uint32_t kRTOS::taskNotifyTake( BaseType_t xClearCountOnExit, TickType_t xTicksToWait)
		{
			return ulTaskNotifyTake(xClearCountOnExit,xTicksToWait);
		}
		__attribute__((always_inline)) BaseType_t kRTOS::taskNotifyStateClear( TaskHandle_t xTask )
		{
			return xTaskNotifyStateClear(xTask);
		}



	#endif

#endif
