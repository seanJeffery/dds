/*
 * dds_interface.c
 *
 *  Created on: Mar 22, 2023
 *      Author: seanj
 */

#include "dds_interface.h"
#include "DD_Scheduler.h"

void create_dd_task( TaskHandle_t t_handle,
					 task_type type,
					 uint32_t task_id,
					 uint32_t absolute_deadline
					)
{


}

void delete_dd_task(uint32_t task_id) {

}

DD_task_list * get_active_dd_task_list(void) {

}

DD_task_list * get_completed_dd_task_list(void) {

}

DD_task_list * get_overdue_dd_task_list(void) {

}
