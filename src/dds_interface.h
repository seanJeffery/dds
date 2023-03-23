/*
 * dds_interface.h
 *
 *  Created on: Mar 22, 2023
 *      Author: seanj
 *
 *  Interface functions declarations for the DDS.
 *
 */

#ifndef DDS_INTERFACE_H
#define DDS_INTERFACE_H

#include <stdint.h>

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"

/* Other includes. */
#include "DD_Scheduler.h"

/*
 * Assigns a release time to a new DD-task, adds it to the active list,
 * sort the list by the deadline, and set the priorities of the user defined tasks.
 */
void create_dd_task( TaskHandle_t t_handle,
					 task_type type,
					 uint32_t task_id,
					 uint32_t absolute_deadline
					);

/*
 * Assign a completion time to finished DD-task, remove it from active task list,
 * add to the completed task list. Also sorts active task list and sets user defined task priority.
 */
void delete_dd_task(uint32_t task_id);

/*
 * Send the active task list to a queue.
 */
DD_task_list * get_active_dd_task_list(void);

/*
 * Send the completed task list to a queue.
 */
DD_task_list * get_completed_dd_task_list(void);

/*
 * Send the overdue task list to a queue.
 */
DD_task_list * get_overdue_dd_task_list(void);

#endif /* DDS_INTERFACE_H */
