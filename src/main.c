/*
    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>>> AND MODIFIED BY <<<< the FreeRTOS exceptio

    ***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
    ***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
    the FAQ page "My application does not run, what could be wwrong?".  Have you
    defined configASSERT()?

    http://www.FreeRTOS.org/support - In return for receiving this top quality
    embedded software for free we request you assist our global community by
    participating in the support forum.

    http://www.FreeRTOS.org/training - Investing in training allows your team to
    be as productive as possible as early as possible.  Now you can receive
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
    Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/

/*
FreeRTOS is a market leading RTOS from Real Time Engineers Ltd. that supports
31 architectures and receives 77500 downloads a year. It is professionally
developed, strictly quality controlled, robust, supported, and free to use in
commercial products without any requirement to expose your proprietary source
code.

This simple FreeRTOS demo does not make use of any IO ports, so will execute on
any Cortex-M3 of Cortex-M4 hardware.  Look for TODO markers in the code for
locations that may require tailoring to, for example, include a manufacturer
specific header file.

This is a starter project, so only a subset of the RTOS features are
demonstrated.  Ample source comments are provided, along with web links to
relevant pages on the http://www.FreeRTOS.org site.

Here is a description of the project's functionality:

The main() Function:
main() creates the tasks and software timers described in this section, before
starting the scheduler.

The Queue Send Task:
The queue send task is implemented by the prvQueueSendTask() function.
The task uses the FreeRTOS vTaskDelayUntil() and xQueueSend() API functions to
periodically send the number 100 on a queue.  The period is set to 200ms.  See
the comments in the function for more details.
http://www.freertos.org/vtaskdelayuntil.html
http://www.freertos.org/a00117.html

The Queue Receive Task:
The queue receive task is implemented by the prvQueueReceiveTask() function.
The task uses the FreeRTOS xQueueReceive() API function to receive values from
a queue.  The values received are those sent by the queue send task.  The queue
receive task increments the ulCountOfItemsReceivedOnQueue variable each time it
receives the value 100.  Therefore, as values are sent to the queue every 200ms,
the value of ulCountOfItemsReceivedOnQueue will increase by 5 every second.
http://www.freertos.org/a00118.html

An example software timer:
A software timer is created with an auto reloading period of 1000ms.  The
timer's callback function increments the ulCountOfTimerCallbackExecutions
variable each time it is called.  Therefore the value of
ulCountOfTimerCallbackExecutions will count seconds.
http://www.freertos.org/RTOS-software-timer.html

The FreeRTOS RTOS tick hook (or callback) function:
The tick hook function executes in the context of the FreeRTOS tick interrupt.
The function 'gives' a semaphore every 500th time it executes.  The semaphore
is used to synchronise with the event semaphore task, which is described next.

The event semaphore task:
The event semaphore task uses the FreeRTOS xSemaphoreTake() API function to
wait for the semaphore that is given by the RTOS tick hook function.  The task
increments the ulCountOfReceivedSemaphores variable each time the semaphore is
received.  As the semaphore is given every 500ms (assuming a tick frequency of
1KHz), the value of ulCountOfReceivedSemaphores will increase by 2 each second.

The idle hook (or callback) function:
The idle hook function queries the amount of free FreeRTOS heap space available.
See vApplicationIdleHook().

The malloc failed and stack overflow hook (or callback) functions:
These two hook functions are provided as examples, but do not contain any
functionality.
*/

/* Standard includes. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "stm32f4_discovery.h"
/* Kernel includes. */
#include "stm32f4xx.h"
#include "../FreeRTOS_Source/include/FreeRTOS.h"
#include "../FreeRTOS_Source/include/queue.h"
#include "../FreeRTOS_Source/include/semphr.h"
#include "../FreeRTOS_Source/include/task.h"
#include "../FreeRTOS_Source/include/timers.h"
/* Other includes */
#include "dds_interface.h"

/*-----------------------------------------------------------*/

/*
 * TODO: Implement this function for any hardware specific clock configuration
 * that was not already performed before main() was called.
 */
static void prvSetupHardware( void );

/* Extracts information from the DDS and reports scheduling information. */
static void MonitorTask( void *pvParameters );

/* Implements the EDF algorithm and controls the priorities of user-defined F-tasks from DD-task list. */
static void DDSTask( void *pvParameters );

/* User defined deadline-sensitive application code 0. */
static void UserTask0( void *pvParameters );

/* User defined deadline-sensitive application code 1. */
static void UserTask1( void *pvParameters );

/* User defined deadline-sensitive application code 2. */
static void UserTask2( void *pvParameters );

/* Periodically creates DD-tasks that are scheduled by the DDS */
static void DDSGenTask( void *pvParameters );

#define DDS_TASK_PRIO	 	5
#define MONITOR_TASK_PRIO   3
#define USER0_TASK_PRIO	 	0	// Subject to change by the DDS
#define USER1_TASK_PRIO	 	1	// Subject to change by the DDS
#define USER2_TASK_PRIO	 	2	// Subject to change by the DDS
#define DDSGEN_TASK_PRIO  	4

// Uncomment one of these to try different testbenches
#define TB1
//#define TB2
//#define TB3

#ifdef TB1

	#define USER0_EXEC_TIME		95
	#define USER1_EXEC_TIME 	150
	#define USER2_EXEC_TIME 	250

	#define USER0_PERIOD 		500
	#define USER1_PERIOD 		500
	#define USER2_PERIOD		750

#elif defined(TB2)

	#define USER0_EXEC_TIME		95
	#define USER1_EXEC_TIME 	150
	#define USER2_EXEC_TIME 	250

	#define USER0_PERIOD 		250
	#define USER1_PERIOD 		500
	#define USER2_PERIOD		750

#elif defined(TB3)

	#define USER0_EXEC_TIME		100
	#define USER1_EXEC_TIME 	200
	#define USER2_EXEC_TIME 	200

	#define USER0_PERIOD 		500
	#define USER1_PERIOD 		500
	#define USER2_PERIOD		500

#endif

#define CreateDDTaskQueue_QUEUE_LENGTH  4
#define TimerExpiredQueue_QUEUE_LENGTH  4

xQueueHandle xQueueHandle_CreateDDTaskQueue = 0;
xQueueHandle xQueueHandle_TimerExpiredQueue = 0;

xTaskHandle xTaskHandle_DDSGenTask = 0; // Need handle so that timer callback can resume the task

xTimerHandle xTimerHandle_User0Timer = 0;
xTimerHandle xTimerHandle_User1Timer = 0;
xTimerHandle xTimerHandle_User2Timer = 0;

/*-----------------------------------------------------------*/

void vTimerCallback(TimerHandle_t xTimer) {

	int8_t expired_timer = -1;

	if(xTimer == xTimerHandle_User0Timer) {
		expired_timer = 0;
	}

	if(xTimer == xTimerHandle_User1Timer) {
		expired_timer = 1;
	}

	if(xTimer == xTimerHandle_User2Timer) {
		expired_timer = 2;
	}

	xQueueSend(xQueueHandle_TimerExpiredQueue, &expired_timer, 1000);

	vTaskResume(xTaskHandle_DDSGenTask);
};

/*-----------------------------------------------------------*/

int main(void)
{
	/* Configure the system ready to run the demo.  The clock configuration
	can be done here if it was not done before main() was called. */
	prvSetupHardware();
	init_dd_scheduler();

	/* Create the queue used by the queue send and queue receive tasks.
	http://www.freertos.org/a00116.html */
	xQueueHandle_CreateDDTaskQueue = xQueueCreate( CreateDDTaskQueue_QUEUE_LENGTH,	/* The number of items the queue can hold. */
											  	   sizeof(create_dd_task_struct) );	/* The size of each item the queue holds. */

	xQueueHandle_TimerExpiredQueue = xQueueCreate( TimerExpiredQueue_QUEUE_LENGTH,	/* The number of items the queue can hold. */
											  	   sizeof(uint8_t) );				/* The size of each item the queue holds. */
														
	/* Add to the registry, for the benefit of kernel aware debugging. */
	vQueueAddToRegistry(xQueueHandle_CreateDDTaskQueue, "CreateDDTaskQueue" );
	vQueueAddToRegistry(xQueueHandle_TimerExpiredQueue, "TimerExpiredQueue" );

	xTaskCreate(DDSTask	   , "DDSTask"	  , configMINIMAL_STACK_SIZE, NULL, DDS_TASK_PRIO	 , NULL);
	xTaskCreate(MonitorTask, "MonitorTask", configMINIMAL_STACK_SIZE, NULL, MONITOR_TASK_PRIO, NULL);
//	xTaskCreate(UserTask0  , "UserTask0"  , configMINIMAL_STACK_SIZE, NULL, USER0_TASK_PRIO	 , NULL);
//	xTaskCreate(UserTask1  , "UserTask1"  , configMINIMAL_STACK_SIZE, NULL, USER1_TASK_PRIO	 , NULL);
//	xTaskCreate(UserTask2  , "UserTask2"  , configMINIMAL_STACK_SIZE, NULL, USER2_TASK_PRIO	 , NULL);
	xTaskCreate(DDSGenTask , "DDSGenTask" , configMINIMAL_STACK_SIZE, NULL, DDSGEN_TASK_PRIO , xTaskHandle_DDSGenTask);

	xTimerHandle_User0Timer = xTimerCreate("User0Timer", USER0_PERIOD, pdFALSE, 0, vTimerCallback);
	xTimerHandle_User1Timer = xTimerCreate("User1Timer", USER1_PERIOD, pdFALSE, 0, vTimerCallback);
	xTimerHandle_User2Timer = xTimerCreate("User2Timer", USER2_PERIOD, pdFALSE, 0, vTimerCallback);

	xTimerStart(xTimerHandle_User0Timer, 1000);
	xTimerStart(xTimerHandle_User1Timer, 1000);
	xTimerStart(xTimerHandle_User2Timer, 1000);

	/* Start the tasks and timer running. */
	vTaskStartScheduler();

	return 0;
}


/*-----------------------------------------------------------*/

static void MonitorTask( void *pvParameters )
{
	while(1)
	{
	}
}

/*-----------------------------------------------------------*/

static void DDSTask( void *pvParameters )
{
	while(1)
	{

	}
}

/*-----------------------------------------------------------*/

static void UserTask0( void *pvParameters )
{
	while(1)
	{
		/* Spin in an empty loop for the execution time */
		TickType_t start_ticks = xTaskGetTickCount();
		while( (TickType_t)(start_ticks - xTaskGetTickCount()) < USER0_EXEC_TIME );

		/* Dereference pvParameters to get the dd task id that was passed to this function */
		uint32_t dd_task_id = (uint32_t)pvParameters;
		delete_dd_task(dd_task_id);
	}
}

/*-----------------------------------------------------------*/

static void UserTask1( void *pvParameters )
{
	while(1)
	{
		/* Spin in an empty loop for the execution time */
		TickType_t start_ticks = xTaskGetTickCount();
		while( (TickType_t)(start_ticks - xTaskGetTickCount()) < USER1_EXEC_TIME );

		/* Dereference pvParameters to get the dd task id that was passed to this function */
		uint32_t dd_task_id = (uint32_t)pvParameters;
		delete_dd_task(dd_task_id);
	}
}

/*-----------------------------------------------------------*/

static void UserTask2( void *pvParameters )
{
	while(1)
	{
		/* Spin in an empty loop for the execution time */
		TickType_t start_ticks = xTaskGetTickCount();
		while( (TickType_t)(start_ticks - xTaskGetTickCount()) < USER2_EXEC_TIME );

		/* Dereference pvParameters to get the dd task id that was passed to this function */
		uint32_t dd_task_id = (uint32_t)pvParameters;
		delete_dd_task(dd_task_id);
	}
}

/*-----------------------------------------------------------*/

static void DDSGenTask( void *pvParameters )
{
	static uint32_t task_id_count = 0; // Iterated every time a dd task is created to make a new id
	while(1)
	{
		int8_t expired_timer;

		if(xQueueReceive(xQueueHandle_TimerExpiredQueue, &expired_timer, 1000)) {

			uint32_t release_time = xTaskGetTickCount();
			uint32_t absolute_deadline;

			uint32_t id = task_id_count++;

			xTaskHandle * handle = pvPortMalloc(sizeof(xTaskHandle));

			switch(expired_timer) {
			case 0: {
				xTaskCreate(UserTask0, "UserTask0", configMINIMAL_STACK_SIZE, (void *)(id), USER0_TASK_PRIO, handle);
				absolute_deadline = release_time + USER0_PERIOD;
				break;
			}
			case 1: {
				xTaskCreate(UserTask1, "UserTask1", configMINIMAL_STACK_SIZE, (void *)(id), USER1_TASK_PRIO, handle);
				absolute_deadline = release_time + USER1_PERIOD;
				break;
			}
			case 2: {
				xTaskCreate(UserTask2, "UserTask2", configMINIMAL_STACK_SIZE, (void *)(id), USER2_TASK_PRIO, handle);
				absolute_deadline = release_time + USER2_PERIOD;
				break;
			}
			default:
				break;
			}

			create_dd_task(*handle, PERIODIC, id, absolute_deadline);

		}
		vTaskSuspend(NULL); // Suspend the generator
	}
}

/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
	/* The malloc failed hook is enabled by setting
	configUSE_MALLOC_FAILED_HOOK to 1 in FreeRTOSConfig.h.

	Called if a call to pvPortMalloc() fails because there is insufficient
	free memory available in the FreeRTOS heap.  pvPortMalloc() is called
	internally by FreeRTOS API functions that create tasks, queues, software 
	timers, and semaphores.  The size of the FreeRTOS heap is set by the
	configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
	configconfigCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected.  pxCurrentTCB can be
	inspected in the debugger if the task name passed into this function is
	corrupt. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
volatile size_t xFreeStackSpace;

	/* The idle task hook is enabled by setting configUSE_IDLE_HOOK to 1 in
	FreeRTOSConfig.h.

	This function is called on each cycle of the idle task.  In this case it
	does nothing useful, other than report the amount of FreeRTOS heap that
	remains unallocated. */
	xFreeStackSpace = xPortGetFreeHeapSize();

	if( xFreeStackSpace > 100 )
	{
		/* By now, the kernel has allocated everything it is going to, so
		if there is a lot of heap remaining unallocated then
		the value of configTOTAL_HEAP_SIZE in FreeRTOSConfig.h can be
		reduced accordingly. */
	}
}
/*-----------------------------------------------------------*/

static void prvSetupHardware( void )
{
	/* Ensure all priority bits are assigned as preemption priority bits.
	http://www.freertos.org/RTOS-Cortex-M3-M4.html */
	NVIC_SetPriorityGrouping( 0 );

	/* TODO: Setup the clocks, etc. here, if they were not configured before
	main() was called. */
}

