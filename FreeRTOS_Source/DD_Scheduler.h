/*
 * DD_task_type.h
 *
 *  Created on: Mar 22, 2023
 *      Author: williambowen
 */

#ifndef DD_SCHEDULER_H_
#define DD_SCHEDULER_H_


	enum task_type{

		PERIODIC,
		APERIODIC

		};

	struct DD_task{

		task_type type;
		uint32_t task_id;
		uint32_t release_time;
		uint32_t absolute_deadline;
		uint32_t completion_time;
		};

	struct DD_task_list{

		DD_task task;
	    struct DD_task_list *next_task;


	};

#endif /* DD_SCHEDULER_H_ */
