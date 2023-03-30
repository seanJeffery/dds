/*
 * dd_scheduler.c
 *
 *  Created on: Mar 25, 2023
 *      Author: williambowen
 */

#include <stdlib.h>
#include "dd_scheduler.h"
#include "dds_interface.h"
#include "dd_task_list.h"
#include "my_queues.h"
#include "FreeRTOS.h"
#include "queue.h"

dd_task * active_list_head = 0;
dd_task * completed_list_head = 0;
dd_task * overdue_list_head = 0;


void dds() {

	dd_task * overdue_task = find_overdue_dd_task(&active_list_head);
	if(overdue_task) {
		vTaskDelete(overdue_task->handle);
		if(active_list_head != 0) {
			vTaskPrioritySet(active_list_head->handle, 1);
		}
//		vPortFree(task_to_delete);
		append_dd_task(&overdue_list_head, overdue_task);
	}

	/****** Create Task message ******/
	create_dd_task_struct new_task;

	if( xQueueReceive(xQueueHandle_CreateDDTaskQueue, &new_task, 0) ) {
		dd_task * task = (dd_task *) pvPortMalloc(sizeof(dd_task));
		task->handle = new_task.handle;
		task->type = new_task.type;
		task->task_id = new_task.task_id;
		task->absolute_deadline = new_task.absolute_deadline;
		task->release_time = xTaskGetTickCount();
		task->next = 0;
		add_dd_task_sorted(&active_list_head, &task);
		vTaskPrioritySet(active_list_head->handle, 1);
	}


	/****** Delete Task message ******/
	uint32_t task_id_to_delete;

	if( xQueueReceive(xQueueHandle_DeleteDDTaskQueue, &task_id_to_delete, 0) ) {
		dd_task * task_to_delete = remove_dd_task(&active_list_head, task_id_to_delete);
		vTaskDelete(task_to_delete->handle);

		if(active_list_head != 0) {
			vTaskPrioritySet(active_list_head->handle, 1);
		}
//		vPortFree(task_to_delete);
		append_dd_task(&completed_list_head, task_to_delete);
	}


	/****** Get Task List message ******/
	uint8_t list_request_type;

	if( xQueueReceive(xQueueHandle_GetTaskListQueue, &list_request_type, 0) ) {

		if(list_request_type == active_task_list ){
			dd_task * list = active_list_head;
			if(xQueueSend(xQueueHandle_TaskListQueue, &list, 1000)) {

			}
			else {

			}
		}
		else if(list_request_type == completed_task_list) {
			dd_task * list = completed_list_head;
			if(xQueueSend(xQueueHandle_TaskListQueue, &list, 1000)){

			}
			else {

			}
		}
		else if(list_request_type == overdue_task_list) {
			dd_task * list = overdue_list_head;
			if(xQueueSend(xQueueHandle_TaskListQueue, &list, 1000)){

			}
			else {

			}
		}
	}


	vTaskSuspend(NULL); // Put the DDS back to sleep
}


void append_dd_task(dd_task ** list_head, dd_task * new_task) {
	new_task->next = 0;
	if(*list_head == 0) {
		*list_head = new_task;
	}
	else {
		dd_task * temp = *list_head;
		while(temp->next != 0) {
			temp = temp->next;
		}
		temp->next = new_task;
	}

}

void add_dd_task_sorted(dd_task ** list_head, dd_task ** new_task) {

	if(*list_head == 0) {
		*list_head = *new_task;
		return;
	}
	dd_task * node = *list_head;
	dd_task * prev_node = *list_head;
	while(node != 0) {
		vTaskPrioritySet(node->handle, 0);

		if(node->absolute_deadline <= (*new_task)->absolute_deadline) {
			if(node->next == 0) { // End of list
				node->next = *new_task;
				return;
			}
			else {
				prev_node = node;
				node = node->next;
			}
		}
		else {
			if(prev_node != node) {
				prev_node->next = *new_task;
				(*new_task)->next = node;
				return;
			}
			else {
				(*new_task)->next = *list_head;
				*list_head = *new_task;
				return;
			}
		}
	}
}

dd_task * remove_dd_task(dd_task ** list_head, uint32_t task_id) {
	dd_task * current_node = *list_head;
	dd_task * prev_node = *list_head;
	if(current_node->task_id == task_id) {
		dd_task * temp = *list_head;
		*list_head = (*list_head)->next;
		return temp;
	}
	while(current_node != 0) {
		// If a node is found with a later absolute deadline
		if(current_node->task_id == task_id) {
			prev_node->next = current_node->next;
			return current_node;
		}
		else {
			prev_node = current_node;
			current_node = current_node->next;
		}
	}
	// No match found
	return 0;
}

dd_task * find_overdue_dd_task(dd_task ** list_head) {
	dd_task * current_node = *list_head;
	dd_task * prev_node = *list_head;
	if(current_node->absolute_deadline < xTaskGetTickCount()) {
		dd_task * temp = *list_head;
		*list_head = (*list_head)->next;
		return temp;
	}
	while(current_node != 0) {
		// If a node is found with a later absolute deadline
		if(current_node->absolute_deadline < xTaskGetTickCount()) {
			prev_node->next = current_node->next;
			return current_node;
		}
		else {
			prev_node = current_node;
			current_node = current_node->next;
		}
	}
	// No match found
	return 0;
}

uint32_t count_list_elements(dd_task ** list_head) {
	uint32_t i = 0;
	dd_task * temp = *list_head;
	while(temp != 0) {
		i++;
		temp = temp->next;
	}
	return i;
}

//void sort_dd_task_list(dd_task * list_head) {
//	dd_task * temp = list_head;
//		while()
//}
