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

void OS_TaskHandler(void);

void OS_1000ms_Task(void);

void OS_10ms_Task(void);

void OS_5ms_Task(void);

#endif /* INC_OS_H_ */
