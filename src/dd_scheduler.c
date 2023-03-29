/*
 * dd_scheduler.c
 *
 *  Created on: Mar 25, 2023
 *      Author: williambowen
 */

#include <stdlib.h>
#include "dd_task_list.h"
#include "dd_scheduler.h"
#include "my_queues.h"

dd_task_list active_list;
dd_task_list overdue_list;
dd_task_list completed_list;



void init_dd_scheduler(){
	init_tasklist(&active_list); //make an active list
	init_tasklist(&overdue_list); //make an overdue list
}



		void dd_scheduler(){

			//dd_task* task_for_scheduling = NULL;
			uint8_t list_type;

			if( xQueueReceive(xQueueHandle_GetTaskListQueue, &list_type, 1000)){

				if(list_type == active_task_list){

				dd_task_list* list = active_list;

				if(xQueueSend(xQueueHandle_TaskListQueue, &list, 1000)){

				}


				}

				if(list_type == completed_task_list){

						dd_task_list* list = completed_list;

							if(xQueueSend(xQueueHandle_TaskListQueue, &list, 1000)){

								}


								}

				if(list_type == overdue_task_list){

								dd_task_list* list = overdue_list;

								if(xQueueSend(xQueueHandle_TaskListQueue, &list, 1000)){

								}


							}

			}

			create_dd_task_struct new_task;

			//if messaged received
			if( xQueueReceive(xQueueHandle_CreateDDTaskQueue, &new_task, 1000)){

				dd_task task;

				task.task_type = new_task.type;
				task.task_id = new_task.task_id;
				task.task_handle = new_task.t_handle;
				task.absolute_deadline = new_task.absolute_deadline;

				task.release_time = xTaskGetTickCount();

				if(active_list.head == NULL){

					active_list.head = &task;
					active_list.tail = &task;

				}else{


					   uint32_t deadline = task.absolute_deadline;
					   dd_task* current = active_list.head;
					   dd_task* next = active_list;



					    while (current != NULL) {
					      previous = current;


					      if (current == null) {
					        break;
					      }

					     current = curretn.next;
					      }

					      task.next = current;
					      previous.nextNode = node;
					}



				}



			}

				uint32_t task_id;

			if( xQueueReceive(xQueueHandle_DeleteDDTaskQueue, &task_id, 1000)){


			}



				// Check input parameters are not NULL
					if( ( active_list == NULL ) || ( overdue_list == NULL ) )
					{
						printf("input parameters are NULL");
						return;
					}else{

						 dd_task* iter = active_list.head; // start from head
						 TickType_t current_time = xTaskGetTickCount();     // fetch the current time to check deadline.

						    while( iter != NULL ) //while not at end of list
						    {



						        if( iter->deadline < current_time ) // passed the deadline.
						        {
						        	// ACTIVE LIST

						        	// Remove item from active list

						        	  {

						        	            // This means that delete was called before the timer callback executed.



						        	            if( active_list.length == 1 ) // removing the head and tail of the list.
						        	            {
						        	                active_list.head = NULL;   // No more items in the list
						        	                active_list.tail = NULL;
						        	            }
						        	            else if( iter.task_handle == active_list.head->task_handle ) //Removing the head of the list.
						        	            {
						        	               active_list.head = iter->next;      // Make the new head of the list the next item in line
						        	                iter.next.previous = NULL;         // Ensure the next item in the list points to NULL for anything before it.
						        	            }
						        	            else if( iter->task_handle == active_list.tail->task_handle ) //Removing the tail of the list
						        	            {
						        	                acitve_list.head = iter->previous;  // Make the new tail of the list the previous item in line
						        	                iter->previous = NULL;         // Ensure the previous item in the list points to NULL for anything after it.
						        	            }
						        	            else // remove from middle of list
						        	            {

						        	                iter->previous->next = iter->next;
						        	                iter->next->previous= iter->previous;

						        	            }

						        	            active.length = active.length - 1;


						        	            iter->previous = NULL;
						        	            iter->next = NULL;

						        	    }
						        }

						    // OVERDUE LIST

						       //add to overdue list

						        if( overdue_list->length == 0 ) //empty
						                  {
						                  	overdue_list.length = 1; //lsit length is now 1
						                  	overdue_list.head = iter;
						                  	overdue_list.tail = iter;
						                  }
						                  else //already things on list
						                  {
						                      dd_task* temp = overdue_list->tail;
						                      overdue_list.tail = iter;
						                      temp->next = iter;
						                      iter->previous = temp;

						                      overdue_list.length = overdue_list.length + 1;

						                  }

						     iter = iter->next;

						    }
					}

					//sort active list

					case(Message_Create)



		}

	}
