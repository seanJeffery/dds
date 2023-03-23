/*
 * DD_task_type.h
 *
 *  Created on: Mar 22, 2023
 *      Author: williambowen
 */

#ifndef DD_SCHEDULER_H_
#define DD_SCHEDULER_H_


	typedef enum {

		PERIODIC,
		APERIODIC

	} task_type;

	typedef struct {

		task_type type;
		uint32_t task_id;
		uint32_t release_time;
		uint32_t absolute_deadline;
		uint32_t completion_time;

	} DD_task;

	typedef struct {
		DD_task task;
	    struct DD_task_list *next_task;

	} DD_task_list;

#endif /* DD_SCHEDULER_H_ */
