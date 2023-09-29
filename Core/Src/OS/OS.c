/*
 * OS.c
 *
 *  Created on: Sep 28, 2023
 *      Author: MNN1CLJ
 */

#include <OS.h>

// Counters for tasks
extern int Counter_Task_5ms;
extern int Counter_Task_10ms;
extern int Counter_Task_1s;

void Task_Handler(void)
{

	if (Counter_Task_5ms == TASK_5ms)
	{

		Counter_Task_5ms = 0;
	}

	if (Counter_Task_10ms == TASK_10ms)
	{
		PduR_MainFunction();
		Counter_Task_10ms = 0;
	}

	if (Counter_Task_1s == TASK_1s)
	{
		CanIf_Client();
		Counter_Task_1s = 0;
	}
}
