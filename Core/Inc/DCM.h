/*
 * DCM.h
 *
 *  Created on: Sep 28, 2023
 *      Author: MNN1CLJ
 */

#ifndef INC_DCM_H_
#define INC_DCM_H_

#include <Types.h>
#include <Constants.h>
#include <CanTp.h>
#include <main.h>

#include <Dcm_Service_ReadDataByIdentifier.h>
#include <Dcm_Service_DiagnosticSessionControl.h>
#include <Dcm_Service_ClearDiagnosticInformation.h>
#include <Dcm_Service_ReadDTCInformation.h>
#include <Dcm_Service_ReadMemoryByAddress.h>
#include <Dcm_Service_SecurityAccess.h>
#include <Dcm_Service_WriteDataByIdentifier.h>
#include <Dcm_Service_RoutineControl.h>
#include <Dcm_Service_WriteMemoryByAddress.h>

/* DCM-SPECIFIC CONSTANTS */
// positive response definitions
#define DCM_POSITIVE_RESPONSE 0x00

// NRC definitions
#define DCM_NRC_SERVICE_NOT_SUPPORTED 0X11
#define DCM_NRC_SUBFUNCTION_NOT_SUPPORTED 0x12
#define DCM_NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT 0x13
#define DCM_NRC_RESPONSE_TOO_LONG 0x14
#define DCM_NRC_CONDITIONS_NOT_CORRECT 0x22
#define DCM_NRC_REQUEST_SEQUENCE_ERROR 0x24
#define DCM_NRC_REQUEST_OUT_OF_RANGE 0x31
#define DCM_NRC_SECURITY_ACCESS_DENIED 0x33
#define DCM_NRC_INVALID_KEY 0x35
#define DCM_NRC_EXCEEDED_NUMBER_OF_ATTEMPTS 0x36
#define DCM_NRC_REQUIRED_TIME_DELAY_NOT_EXPIRED 0x37
#define DCM_NRC_GENERAL_PROGRAMMING_FAILURE 0x72

// Services
//service define directives
#define DCM_SERVICE_ID_DIAGNOSTIC_SESSION_CONTROL 0x10
#define DCM_SERVICE_ID_CLEAR_DIAGNOSTIC_INFORMATION 0x14
#define DCM_SERVICE_ID_READ_DTC_INFORMATION 0x19
#define DCM_SERVICE_ID_READ_DATA_BY_IDENTIFIER 0x22
#define DCM_SERVICE_ID_READ_MEMORY_BY_ADDRESS 0x23
#define DCM_SERVICE_ID_SECURITY_ACCESS 0x27
#define DCM_SERVICE_ID_WRITE_DATA_BY_IDENTIFIER 0x2E
#define DCM_SERVICE_ID_ROUTINE_CONTROL 0x31
#define DCM_SERVICE_ID_WRITE_MEMORY_BY_ADDRESS 0x3D

//SESSIONS
#define DCM_SESSION_DEFAULT 0X01
#define DCM_SESSION_PROGRAMMING 0x02
#define DCM_SESSION_EXTENDED 0x03

/* DCM-SPECIFIC TYPES */
typedef uint8_t Dcm_MessageLength;
typedef uint8_t Dcm_MessageData;
typedef struct
{
	Dcm_MessageLength length;
	Dcm_MessageData data[8];
} Dcm_Message;

//Negative or positive response
void Dcm_CreateResponse(uint8_t DCM_response, CanTp_Frame *response, uint8_t serviceID, uint8_t *responseData, uint8_t response_length);

//DCM response
void Dcm_PduR_GetRequest(Dcm_Message *request);

void Dcm_PduR_SendResponse(CanTp_Frame *response);

#endif /* INC_DCM_H_ */
