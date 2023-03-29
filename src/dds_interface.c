/*
 * dds_interface.c
 *
 *  Created on: Mar 22, 2023
 *      Author: seanj
 */

/* FreeRTOS includes*/
#include <dd_task_list.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Other includes */
#include "dds_interface.h"
#include "my_queues.h"

extern TaskHandle_t xTaskHandle_DDSTask;

void create_dd_task( TaskHandle_t handle,
					 task_type type,
					 uint32_t task_id,
					 uint32_t absolute_deadline
					)
{

	// Build struct to be placed on the create dd task queue
	create_dd_task_struct dd_task = {
		handle,
		type,
		task_id,
		absolute_deadline
	};

	// Send the dd task creation data to the dds
	xQueueSend(xQueueHandle_CreateDDTaskQueue, &dd_task, 1000);
	vTaskResume(xTaskHandle_DDSTask);
}

void delete_dd_task(uint32_t task_id) {
	xQueueSend(xQueueHandle_DeleteDDTaskQueue, &task_id, 1000);
	vTaskResume(xTaskHandle_DDSTask);
}

dd_task * get_active_dd_task_list(void) {
	uint8_t list_type = active_task_list;
	dd_task * list;
	xQueueSend(xQueueHandle_GetTaskListQueue, &list_type, 1000);
	vTaskResume(xTaskHandle_DDSTask);
	if(xQueueReceive(xQueueHandle_TaskListQueue, &list, 1000)) {
		return list;
	}
	else {
		return 0;
	}
}

dd_task * get_completed_dd_task_list(void) {
	uint8_t list_type = completed_task_list;
	dd_task * list;
	xQueueSend(xQueueHandle_GetTaskListQueue, &list_type, 1000);
	vTaskResume(xTaskHandle_DDSTask);
	if(xQueueReceive(xQueueHandle_TaskListQueue, &list, 1000)) {
		return list;
	}
	else {
		return 0;
	}
}

dd_task * get_overdue_dd_task_list(void) {
	uint8_t list_type = overdue_task_list;
	dd_task * list;
	xQueueSend(xQueueHandle_GetTaskListQueue, &list_type, 1000);
	vTaskResume(xTaskHandle_DDSTask);
	if(xQueueReceive(xQueueHandle_TaskListQueue, &list, 1000)) {
		return list;
	}
	else {
		return 0;
	}
}
