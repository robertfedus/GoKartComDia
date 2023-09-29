/*
 * OS.c
 *
 *  Created on: Sep 28, 2023
 *      Author: MNN1CLJ
 */

#include <OS.h>

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

		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET);
		CanIf_Client();

		Counter_Task_1s = 0;
	}
}
