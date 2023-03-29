/*
 * dd_scheduler.c
 *
 *  Created on: Mar 25, 2023
 *      Author: williambowen
 */

#include <stdlib.h>
#include "dd_task_list.h"
#include "dd_scheduler.h"

dd_task_list active_list;
dd_task_list overdue_list;

		QueueHandle_t scheduler_message_queue;
		QueueHandle_t monitor_message_queue;


void init_dd_scheduler(){
	init_tasklist(&active_list); //make an active list
	init_tasklist(&overdue_list); //make an overdue list
}

// dd_scheduler

	//clear overdue tasks
	 //Figure out message type
	 //Task_Create
	 //  -> add new element to active list
	 // Task_Delete
	 //  -> remove the selected task from the active list (and maybe overdue list????)
	 //  Active_List & Overdue_List data requests
	 // -> provide data for the monitor task


		enum
		{
			Message_Create,
			Message_Delete,
			Message_ActiveList,
			Message_OverdueList

		}message_type;


		typedef struct
		{
			message_type 	message_type;
			TaskHandle_t      message_sender;
			void*             message_data;
		}message;


		void dd_scheduler(){

			dd_task* task_for_scheduling = NULL;
			message message_recieved;

			if( xQueueReceive(scheduler_message_queue, &message_received, 0)){ //if messaged received


				// Check input parameters are not NULL
					if( ( active_list == NULL ) || ( overdue_list == NULL ) )
					{
						printf("input parameters are NULL");
						return;
					}else{

						 dd_task* iter = active_list->head; // start from head, closest deadline
						 TickType_t current_time = xTaskGetTickCount();     // fetch the current time to check deadline.

						    while( iter != NULL ) //while not at end of list
						    {
						        if( iter->deadline < current_time ) // passed the deadline.
						        {
						        	// ACTIVE LIST

						        	// Remove item from active list

						        	  {

						        	            // This means that delete was called before the timer callback executed.
						        	            if( (iter->task_type == APERIODIC) && (iter->aperiodic_timer != NULL) )
						        	            {
						        	                xTimerStop( iterator->aperiodic_timer, 0 );      // Stop the timer
						        	                xTimerDelete( iterator->aperiodic_timer, 0 );    // Delete the timer
						        	                iter->aperiodic_timer = NULL;                // Clear the timer
						        	            }


						        	            if( active_list->length == 1 ) // removing the head and tail of the list.
						        	            {
						        	                active_list->head = NULL;   // No more items in the list
						        	                active_list->tail = NULL;
						        	            }
						        	            else if( iter->task_handle == active_list->head->task_handle ) //Removing the head of the list.
						        	            {
						        	               active_list->head = iter->next;      // Make the new head of the list the next item in line
						        	                iter->next->previous = NULL;         // Ensure the next item in the list points to NULL for anything before it.
						        	            }
						        	            else if( iter->task_handle == active_list->tail->task_handle ) //Removing the tail of the list
						        	            {
						        	                acitve_list->head = iter->previous;  // Make the new tail of the list the previous item in line
						        	                iter->previous->next = NULL;         // Ensure the previous item in the list points to NULL for anything after it.
						        	            }
						        	            else // remove from middle of list
						        	            {
						        	            	dd_task* temp = iter;
						        	                iter->previous->next = iter->next;
						        	                iter->nex->previous= iter->previous;

						        	            }

						        	            active->length = active->length - 1; // decrement the list size


						        	            iter->previous = NULL;
						        	            iter->next = NULL;


						        	    }





						        }


						        iter = iter->next_cell;
						    }

					}




		}

	}
