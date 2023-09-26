/*
 * Test.c
 *
 *  Created on: Sep 26, 2023
 *      Author: FER3CLJ
 */

#include "Test.h"

void ComDia_Test_TestAll(void)
{
	if (Test_CanDrv() != COMDIA_TEST_OK)
	{
		ComDia_Test_FailHandler();
	}
}

void ComDia_Test_FailHandler(void)
{
	// All IRQ interrupts are disabled
	__disable_irq();
	// Sit in infinite loop
	for(;;);
}
