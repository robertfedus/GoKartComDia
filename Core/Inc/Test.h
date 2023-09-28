/*
 * Test.h
 *
 *  Created on: Sep 26, 2023
 *      Author: FER3CLJ
 */

#ifndef INC_TEST_H_
#define INC_TEST_H_

#include <Constants.h>
#include <CanIf.h>
#include <Types.h>
#include "main.h"
#include "usb_host.h"
#include <Test_CanDrv.h>

void ComDia_Test_TestAll(void);

void ComDia_Test_FailHandler(void);

#endif /* INC_TEST_H_ */
