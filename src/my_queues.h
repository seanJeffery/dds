/*
 * my_queues.h
 *
 *  Created on: Mar 22, 2023
 *      Author: seanj
 *
 *  Extern definitions of queue handles for other files.
 *  Queues are created in main.c
 *
 */

#ifndef MY_QUEUES_H_
#define MY_QUEUES_H_

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "queue.h"

extern xQueueHandle xQueueHandle_CreateDDTaskQueue;

#endif /* MY_QUEUES_H_ */
