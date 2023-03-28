/*
 * dd_scheduler.c
 *
 *  Created on: Mar 25, 2023
 *      Author: williambowen
 */
		dd_task_list active_list;
		dd_task_list overdue_list;


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

	void dd_scheduler(){

		dd_task* task_for_scheduling = NULL;

		//if xqueuerecieve.... wait for something on queue

	}
