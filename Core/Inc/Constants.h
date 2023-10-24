/*
 * Types.h
 *
 *  Created on: Sep 20, 2023
 *      Author: FER3CLJ
 */
#ifndef INC_CONSTANTS_H_
#define INC_CONSTANTS_H_

/* GENERAL-PURPOSE CONSTANTS */

/* Application Development Stage */
#define COMDIA_PRODUCTION_STAGE 0
#define COMDIA_DEVELOPMENT_STAGE 1
#define COMDIA_TEST_STAGE 2
#define COMDIA_APP_STAGE COMDIA_DEVELOPMENT_STAGE

// General-purpose error/status flags, used primarily for ComDia_StatusFlag type
#define COMDIA_OK 1
#define COMDIA_NOT_OK 0

/* CANDRV-SPECIFIC CONSTANTS */

// Status flag for CAN initialization
#define CAN_READY COMDIA_OK
#define CAN_NOT_READY COMDIA_NOT_OK

/* In CanDrv messages not related to the modules below are discarded */
// StdId 0x000 messages are sent to CanIf by default
#define CAN_DEFAULT_STDID 0x000
#define CAN_MAX_MESSAGE_LENGTH 0x08
// StdId 0x720 messages are to be forwarded to DCM, through CanIf
#define CAN_DCM_STDID 0x720
#define CAN_DCM_RESPONSE_STDID 0x721

/* OS-SPECIFIC CONSTANTS */
// Periods of tasks
#define OS_5MS_TASK 5
#define OS_10MS_TASK 10
#define OS_1000MS_TASK 1000

/* TEST-SPECIFIC CONSTANTS */
#define COMDIA_TEST_OK COMDIA_OK
#define COMDIA_TEST_NOT_OK COMDIA_NOT_OK

#endif /* INC_CONSTANTS_H_ */
