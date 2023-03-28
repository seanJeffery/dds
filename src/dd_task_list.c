/*
 * dd_task_list.c
 *
 *  Created on: Mar 25, 2023
 *      Author: williambowen
 */

#include "dd_task_list.h"

//initialize list values
void init_tasklist( dd_task* list )
{

	if( list != NULL ){ //check input is not empty


    list->length = 0;
    list->head = NULL;
    list->tail = NULL;

	}else{

		printf("error: list is empty");
		return;

	}
