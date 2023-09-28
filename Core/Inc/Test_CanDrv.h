/*
 * CanDrv_Tests.h
 *
 *  Created on: Sep 26, 2023
 *      Author: FER3CLJ
 */

#ifndef INC_TEST_CANDRV_H_
#define INC_TEST_CANDRV_H_

#include <Constants.h>
#include <CanIf.h>
#include <CanDrv.h>
#include <Types.h>
#include "main.h"
#include "usb_host.h"

ComDia_StatusFlag Test_CanDrv(void);

ComDia_StatusFlag Test_Can_Write(void);

ComDia_StatusFlag Test_Can_Init(void);

ComDia_StatusFlag Test_Can_DeInit(void);


#endif /* INC_TEST_CANDRV_H_ */
