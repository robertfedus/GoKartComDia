/*
 * DCM.h
 *
 *  Created on: Sep 28, 2023
 *      Author: MNN1CLJ
 */

#ifndef INC_DCM_H_
#define INC_DCM_H_

#include <Types.h>
#include <Responses.h>
#include <Services.h>
#include <Constants.h>
#include <CanTp.h>
#include <main.h>

//Negative or positive response
void ResponseHandler(uint8_t DCM_response, CanTp_Frame *response, uint8_t serviceID, uint8_t *responseData, uint8_t response_length);

//DCM response
void GetResponse(CanTp_Frame *request);

// Services
uint8_t diagnosticSessionControl(CanTp_Frame input, uint8_t *output, uint8_t *length_output);
uint8_t clearDiagnosticInformation(CanTp_Frame input, uint8_t *output, uint8_t *length_output);
uint8_t readDTCInformation(CanTp_Frame input, uint8_t *output, uint8_t *length_output);
uint8_t readDataByIdentifier(CanTp_Frame input, uint8_t *output, uint8_t *length_output);
uint8_t readMemoryByAddress(CanTp_Frame input, uint8_t *output, uint8_t *length_output);
uint8_t securityAccess(CanTp_Frame input, uint8_t *output, uint8_t *length_output);
uint8_t writeDataByIdentifier(CanTp_Frame input, uint8_t *output, uint8_t *length_output);
uint8_t routineControl(CanTp_Frame input, uint8_t *output, uint8_t *length_output);
uint8_t writeMemoryByAddress(CanTp_Frame input, uint8_t *output, uint8_t *length_output);


#endif /* INC_DCM_H_ */
