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

/*
 * Assigns a release time to a new DD-task, adds it to the active list,
 * sort the list by the deadline, and set the priorities of the user defined tasks.
 */
void create_dd_task( TaskHandle_t t_handle,
					 task_type type,
					 uint32_t task_id,
					 uint32_t absolute_deadline
					);

#endif /* DDS_INTERFACE_H */
