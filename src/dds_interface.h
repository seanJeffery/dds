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


void create_dd_task( TaskHandle_t t_handle,
					 task_type type,
					 uint32_t task_id,
					 uint32_t absolute_deadline
					);

#endif /* DDS_INTERFACE_H */
