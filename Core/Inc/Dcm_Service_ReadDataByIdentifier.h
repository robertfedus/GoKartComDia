/*
 * Dcm_Service_ReadDataByIdentifier.h
 *
 *  Created on: Oct 24, 2023
 *      Author: FER3CLJ
 */

#ifndef INC_DCM_SERVICE_READDATABYIDENTIFIER_H_
#define INC_DCM_SERVICE_READDATABYIDENTIFIER_H_

#include <stdint.h>
#include <Constants.h>
#include <Types.h>

#define DCM_SERVICE_ID_READ_DATA_BY_IDENTIFIER_RESPONSE_SID 0x62

uint8_t Dcm_Service_ReadDataByIdentifier(uint8_t *requestMessageData, uint8_t requestMessageLength, uint8_t *responseData, uint8_t *responseDataLength);

#endif /* INC_DCM_SERVICE_READDATABYIDENTIFIER_H_ */
