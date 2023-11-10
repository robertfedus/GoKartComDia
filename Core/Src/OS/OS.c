/*
 * OS.c
 *
 *  Created on: Sep 28, 2023
 *      Author: MNN1CLJ
 */


#include <OS.h>

 extern volatile int OS_5ms_TaskCounter;
 extern volatile int OS_10ms_TaskCounter;
 extern volatile int OS_1000ms_TaskCounter;
 extern volatile uint16_t Dcm_Service_SecurityAccess_SeedCounter;

void OS_TaskHandler(void)
{

	if (OS_5ms_TaskCounter == OS_5MS_TASK)
	{
		OS_5ms_Task();
		OS_5ms_TaskCounter = 0;
	}

	if (OS_10ms_TaskCounter == OS_10MS_TASK)
	{
		OS_10ms_Task();
		OS_10ms_TaskCounter = 0;
	}

	if (OS_1000ms_TaskCounter == OS_1000MS_TASK)
	{
		OS_1000ms_Task();

		OS_1000ms_TaskCounter = 0;
	}

	if (Dcm_Service_SecurityAccess_SeedCounter == OS_DCM_SERVICE_SECURITY_ACCESS_SEED_COUNTER_LIMIT)
	{
		Dcm_Service_SecurityAccess_SeedCounter = 0;
	}
}

void OS_1000ms_Task(void)
{
	CanIf_Client();
}

void OS_10ms_Task(void)
{
	PduR_MainFunction();
}

void OS_5ms_Task(void)
{

}
