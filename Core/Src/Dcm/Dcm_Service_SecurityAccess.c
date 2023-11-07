/*
 * Dcm_Service_SecurityAccess.c
 *
 *  Created on: Oct 24, 2023
 *      Author: FER3CLJ
 */
#include <Dcm_Service_SecurityAccess.h>

extern uint8_t Dcm_ActiveSecurityLevel = 0x00;

uint8_t Dcm_Service_SecurityAccess(uint8_t *requestMessageData, uint8_t requestMessageDataLength, uint8_t *responseMessageData, uint8_t *responseMessageDataLength)
{
	uint8_t responseDataIndex = 0;
	responseMessageData[responseDataIndex++] = DCM_SERVICE_ID_READ_DATA_BY_IDENTIFIER_RESPONSE_SID;

	for (uint8_t currentRequestByteIndex = 1; currentRequestByteIndex < requestMessageDataLength; currentRequestByteIndex += 2)
	{

	}

    return 0x00;
}
