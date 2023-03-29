/*
 * DD_task_type.h
 *
 *  Created on: Mar 22, 2023
 *      Author: williambowen
 */

#ifndef DD_TASK_LIST_H_
#define DD_TASK_LIST_H_

#include <stdint.h>

typedef enum {

	PERIODIC,
	APERIODIC

} task_type;

typedef struct {

	xTimerHandle aperiodic_timer;
	task_type task_type;
	TaskHandle_t task_handle;
	uint32_t task_id;
	uint32_t release_time;
	uint32_t absolute_deadline;
	uint32_t completion_time;
	struct dd_task* next;
	struct dd_task* previous;
	TickType_t creation_time;
	TickType_t deadline;

} dd_task;

typedef struct {

	uint32_t length;
	dd_task* head;
	dd_task* tail;

} dd_task_list;


#endif /* DD_TASK_LIST_H_ */
