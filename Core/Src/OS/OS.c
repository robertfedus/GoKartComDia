/*
 * OS.c
 *
 *  Created on: Sep 28, 2023
 *      Author: MNN1CLJ
 */


#include <OS.h>

 extern volatile int Counter_Task_5ms;
 extern volatile int Counter_Task_10ms;
 extern volatile int Counter_Task_1s;

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

		HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_13);
		CanIf_Client();

		Counter_Task_1s = 0;
	}
}
