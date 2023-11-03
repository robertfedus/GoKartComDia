/*
 * Dcm_Service_WriteDataByIdentifier.h
 *
 *  Created on: Oct 24, 2023
 *      Author: FER3CLJ
 */

#ifndef INC_DCM_SERVICE_WRITEDATABYIDENTIFIER_H_
#define INC_DCM_SERVICE_WRITEDATABYIDENTIFIER_H_

#include <stdint.h>
#include <Constants.h>
#include <Types.h>

#define DCM_SERVICE_ID_WRITE_DATA_BY_IDENTIFIER_RESPONSE_SID 0x6E
#define NEGATIVE_RESPONSE_SID 0x7F

uint8_t Dcm_Service_WriteDataByIdentifier(uint8_t *requestMessageData, uint8_t requestMessageLength, uint8_t *responseData, uint8_t *responseDataLength);

#endif /* INC_DCM_SERVICE_WRITEDATABYIDENTIFIER_H_ */
