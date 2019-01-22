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



#include "kSystem.h"

struct scheduledTaskArgs
{
	void (*function_handler)(void*);
	kRTOS::tick_t scheduleInterval;
	void * params;
};

void kRTOS_scheduledTask(void * args)
{
	scheduledTaskArgs *scheduledTaskData = (scheduledTaskArgs*)args;
	kRTOS::tick_t time = kRTOS::taskGetTickCount();

	while(1)
	{
		scheduledTaskData->function_handler(scheduledTaskData->params);
		kRTOS::taskDelayUntil(&time,scheduledTaskData->scheduleInterval);
	}
}


void kRTOS::taskCreateScheduled(void (*function_handler)(void*),const char * task_name,unsigned int stack_size,void * const params,unsigned long priority,task_t * const created_task,tick_t scheduleInterval)
{
	scheduledTaskArgs * scheduledTaskData;

	scheduledTaskData = (scheduledTaskArgs*)pvPortMalloc(sizeof(scheduledTaskArgs));

	scheduledTaskData->function_handler = function_handler;
	scheduledTaskData->params = params;
	scheduledTaskData->scheduleInterval = scheduleInterval;

	kRTOS::taskCreate(kRTOS_scheduledTask,task_name,stack_size,scheduledTaskData,priority,created_task);

}
void kRTOS::Notifier::addNotificationReceiver(task_t rx_task)
{
	if(receivers_length >= 8) return;
	receiver[receivers_length++] = rx_task;
}
void kRTOS::Notifier::notifyAllReceivers(void)
{
	for(uint8_t i=0;i<receivers_length;i++)
	{
		// notify
		kRTOS::taskNotifyGive(receiver[i]);

	}
}
