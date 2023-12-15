/*
 * Dcm_Service_RoutineControl.h
 *
 *  Created on: Oct 24, 2023
 *      Author: FER3CLJ
 */

#ifndef INC_DCM_SERVICE_ROUTINECONTROL_H_
#define INC_DCM_SERVICE_ROUTINECONTROL_H_

#include <stdint.h>

#define DCM_SERVICE_ID_ROUTINE_CONTROL 0x31


//SUBFUNCTIONS
#define START_ROUTINE 0x01
#define STOP_ROUTINE 0x02
#define REQUEST_ROUTINE_RESULTS 0x03

//NRCs (fara securityAccessDenied si conditionsNotCorrect)
#define SUBFUNCTION_NOT_SUPPORTED 0x12
#define INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT 0x13
#define REQUEST_SEQUENCE_ERROR 0x24
#define REQUEST_OUT_OF_RANGE 0x31

//for checking the current status of a routine
#define ROUTINE_ACTIVE 0x01
#define ROUTINE_NOT_ACTIVE 0x02
#define ROUTINE_NEVER_ACTIVE 0x03

#define NUMBER_OF_ROUTINE_IDENTIFIERS 3

void routine1(uint8_t* output, uint8_t changeStatus, uint8_t* routineControlRecord);
void routine2(uint8_t* output, uint8_t changeStatus, uint8_t* routineControlRecord);
void routine3(uint8_t* output, uint8_t changeStatus, uint8_t* routineControlRecord);


typedef struct
{
	uint16_t routineId;
	void (*StartRoutine[3])(uint8_t* output, uint8_t changeStatus, uint8_t* routineControlRecord);
	void (*StopRoutine[3])(uint8_t* output, uint8_t changeStatus, uint8_t* routineControlRecord);
	void (*RequestRoutineResults[3])(uint8_t* output, uint8_t changeStatus, uint8_t* routineControlRecord);
}RoutineControlTable;

RoutineControlTable routineControlTable;
uint16_t routineIds[3]={0x01,0x02,0x03}; //routine IDs
uint16_t routineStatus[3]={ROUTINE_NEVER_ACTIVE,ROUTINE_NEVER_ACTIVE,ROUTINE_NEVER_ACTIVE}; //routineStatus[0] - prima rutina

void Dcm_RoutineControlTable_Init();

uint8_t Dcm_Service_RoutineControl(uint8_t *requestMessageData, uint8_t requestMessageLength, uint8_t *responseData, uint8_t *responseDataLength);

#endif /* INC_DCM_SERVICE_ROUTINECONTROL_H_ */
