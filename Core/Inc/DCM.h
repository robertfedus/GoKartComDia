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
#include <Dcm_DID.h>

#include <Dcm_Service_ReadDataByIdentifier.h>
#include <Dcm_Service_DiagnosticSessionControl.h>
#include <Dcm_Service_ClearDiagnosticInformation.h>
#include <Dcm_Service_ReadDTCInformation.h>
#include <Dcm_Service_ReadMemoryByAddress.h>
#include <Dcm_Service_SecurityAccess.h>
#include <Dcm_Service_WriteDataByIdentifier.h>
#include <Dcm_Service_RoutineControl.h>
#include <Dcm_Service_WriteMemoryByAddress.h>

void Dcm_Init();
//Negative or positive response
void Dcm_CreateResponse(uint8_t DCM_response, CanTp_Frame *response, uint8_t serviceID, uint8_t *responseData, uint8_t response_length);

//DCM response
void Dcm_PduR_GetRequest(Dcm_Message *request);

void Dcm_PduR_SendResponse(CanTp_Frame *response);

/* Local tests for services */
void Dcm_Test_ReadDataByIdentifier();
void Dcm_Test_SecurityAccess();

#endif /* INC_DCM_H_ */
