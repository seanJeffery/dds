/*
 * dd_scheduler.h
 *
 *  Created on: Mar 28, 2023
 *      Author: seanj
 */

#ifndef DD_SCHEDULER_H_
#define DD_SCHEDULER_H_

#include "dd_task_list.h"

/* Main DDS scheduling function */
void dds();

/* Iterate through a linked list and append the task to the end */
void append_dd_task(dd_task ** list_head, dd_task * new_task);

/* Remove a task from a linked list */
dd_task * remove_dd_task(dd_task ** list_head, uint32_t task_id);

/*  */
void add_dd_task_sorted(dd_task ** list_head, dd_task ** new_task);

uint32_t count_list_elements(dd_task ** list_head);

/* Sort a linked list of tasks by earliest deadline first */
//void sort_dd_task_list();

#endif /* DD_SCHEDULER_H_ */
