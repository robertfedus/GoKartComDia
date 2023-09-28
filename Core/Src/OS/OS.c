/*
 * OS.c
 *
 *  Created on: Sep 28, 2023
 *      Author: MNN1CLJ
 */

// Counters for tasks
extern int Counter_Task_5ms;
extern int Counter_Task_10ms;
extern int Counter_Task_1s;

void Task_Handler(void)
{
	if (Counter_Task_5ms == Task_5ms)
	{

		Counter_Task_5ms = 0;
	}

	if (Counter_Task_10ms == Task_10ms)
	{

		Counter_Task_10ms = 0;
	}

	if (Counter_Task_1s == Task_1s)
	{

		Counter_Task_1s = 0;
	}
}
