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

<<<<<<< Updated upstream
void Task_Handler(void)
=======
#include <OS.h>

 extern volatile int OS_5ms_TaskCounter;
 extern volatile int OS_10ms_TaskCounter;
 extern volatile int OS_50ms_TaskCounter;
 extern volatile int OS_1000ms_TaskCounter;

void OS_TaskHandler(void)
>>>>>>> Stashed changes
{
	if (Counter_Task_5ms == Task_5ms)
	{

		Counter_Task_5ms = 0;
	}

	if (Counter_Task_10ms == Task_10ms)
	{

		Counter_Task_10ms = 0;
	}

<<<<<<< Updated upstream
	if (Counter_Task_1s == Task_1s)
=======
	if (OS_50ms_TaskCounter == OS_50MS_TASK)
		{
			OS_50ms_Task();
			OS_10ms_TaskCounter = 0;
		}

	if (OS_1000ms_TaskCounter == OS_1000MS_TASK)
>>>>>>> Stashed changes
	{

		Counter_Task_1s = 0;
	}
}
<<<<<<< Updated upstream
=======

void OS_1000ms_Task(void)
{
	CanIf_Client();
}

void OS_10ms_Task(void)
{
	PduR_MainFunction();
}

void OS_50ms_Task(void)
{
	Dcm_DiagnosticSession_Init(); // trece in DEFAULT_SESSION cand trece perioada P2_SERVER_MAX
}

void OS_5ms_Task(void)
{

}
>>>>>>> Stashed changes
