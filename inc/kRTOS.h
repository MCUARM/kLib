#ifndef __kRTOS_H
#define __kRTOS_H

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
		static __inline__ void startScheduler(void) __attribute__((always_inline));
		static __inline__ void taskDelayUntil(tick_t * previous_wake_time_ms, const tick_t time_increment_ms)__attribute__((always_inline));
		static __inline__ void taskDelay(const tick_t time_increment_ms)__attribute__((always_inline));
		static __inline__ tick_t taskGetTickCount(void) __attribute__((always_inline));
	};

	__attribute__((always_inline)) void kRTOS::taskCreate(void (*function_handler)(void*),const char * task_name,unsigned int stack_size,void * const params,unsigned long priority,kRTOS::task_t * const created_task)
	{
		xTaskCreate(function_handler,task_name,stack_size,params,priority,created_task);
	}
	__attribute__((always_inline)) void kRTOS::startScheduler(void)
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

#endif
