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

//Negative or positive response
void Dcm_SendResponse(uint8_t DCM_response, CanTp_Frame *response, uint8_t serviceID, uint8_t *responseData, uint8_t response_length);

//DCM response
void Dcm_GetRequest(Dcm_Message *request);

// Services - not yet implemented
uint8_t Dcm_Service_DiagnosticSessionControl(Dcm_Message input, uint8_t *output, uint8_t *length_output);
uint8_t Dcm_Service_ClearDiagnosticInformation(Dcm_Message input, uint8_t *output, uint8_t *length_output);
uint8_t Dcm_Service_ReadDTCInformation(Dcm_Message input, uint8_t *output, uint8_t *length_output);
uint8_t Dcm_Service_ReadDataByIdentifier(Dcm_Message input, uint8_t *output, uint8_t *length_output);
uint8_t Dcm_Service_ReadMemoryByAddress(Dcm_Message input, uint8_t *output, uint8_t *length_output);
uint8_t Dcm_Service_SecurityAccess(Dcm_Message input, uint8_t *output, uint8_t *length_output);
uint8_t Dcm_Service_WriteDataByIdentifier(Dcm_Message input, uint8_t *output, uint8_t *length_output);
uint8_t Dcm_Service_RoutineControl(Dcm_Message input, uint8_t *output, uint8_t *length_output);
uint8_t Dcm_Service_WriteMemoryByAddress(Dcm_Message input, uint8_t *output, uint8_t *length_output);


#endif /* INC_DCM_H_ */
