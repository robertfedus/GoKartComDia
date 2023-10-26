/*
 * OS.h
 *
 *  Created on: Sep 28, 2023
 *      Author: MNN1CLJ
 */

#ifndef INC_OS_H_
#define INC_OS_H_

#include <Constants.h>
#include <main.h>
#include <CanIf.h>
#include <Counters.h>
#include "stm32f4xx_hal.h"

/* OS-SPECIFIC CONSTANTS */
// Periods of tasks
#define OS_5MS_TASK 5
#define OS_10MS_TASK 10
#define OS_1000MS_TASK 1000

void OS_TaskHandler(void);

void OS_1000ms_Task(void);

void OS_10ms_Task(void);

void OS_5ms_Task(void);

#endif /* INC_OS_H_ */
