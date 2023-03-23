/*
 * dds_interface.c
 *
 *  Created on: Mar 22, 2023
 *      Author: seanj
 */

/* FreeRTOS includes*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Other includes */
#include "dds_interface.h"
#include "DD_Scheduler.h"
#include "my_queues.h"

void create_dd_task( TaskHandle_t t_handle,
					 task_type type,
					 uint32_t task_id,
					 uint32_t absolute_deadline
					)
{

	// Build struct to be placed on the create dd task queue
	create_dd_task_struct dd_task = {
			t_handle,
			type,
			task_id,
			absolute_deadline
	};

	// Send the dd task creation data to the dds
	xQueueSend(xQueueHandle_CreateDDTaskQueue, &dd_task, 1000);
}

void delete_dd_task(uint32_t task_id) {

}

DD_task_list * get_active_dd_task_list(void) {

}

DD_task_list * get_completed_dd_task_list(void) {

}

DD_task_list * get_overdue_dd_task_list(void) {

}
