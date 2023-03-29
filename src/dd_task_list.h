/*
 * dd_task_list.h
 *
 *  Created on: Mar 22, 2023
 *      Author: williambowen
 */

#ifndef DD_TASK_LIST_H_
#define DD_TASK_LIST_H_

#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"

typedef enum {

	PERIODIC,
	APERIODIC

} task_type;

typedef struct dd_task {

	TaskHandle_t handle;
	task_type type;
	uint32_t task_id;
	uint32_t release_time;
	uint32_t absolute_deadline;
	uint32_t completion_time;
	struct dd_task * next;

} dd_task;



#endif /* DD_TASK_LIST_H_ */
