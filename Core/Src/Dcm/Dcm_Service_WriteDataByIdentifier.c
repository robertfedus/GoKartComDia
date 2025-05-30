/*
 * Dcm_Service_WriteDataByIdentifier.c
 *
 *  Created on: May 29, 2025
 *      Author: MNN1CLJ
 */
#include <Dcm_Service_WriteDataByidentifier.h>

extern Dcm_DID *allDIDs[100];

uint8_t Dcm_Service_WriteDataByIdentifier(uint8_t *requestMessageData, uint8_t requestMessageLength, uint8_t *responseData, uint8_t *responseDataLength)
{
	if (requestMessageData[0] != DCM_SERVICE_ID_WRITE_DATA_BY_IDENTIFIER)
		{
			return DCM_NRC_SERVICE_NOT_SUPPORTED;
		}

    if(requestMessageLength < 4)
    {
    	return DCM_NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;
    }

    if(requestMessageLength > 5)
    {
        return DCM_NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;
    }

	uint8_t responseDataIndex = 1;
	uint8_t didHighByte = requestMessageData[responseDataIndex++];
	uint8_t didLowByte = requestMessageData[responseDataIndex++];
	uint16_t did = ((uint16_t)didHighByte << 8) | didLowByte;

	uint8_t didDataHighByte = requestMessageData[responseDataIndex++];
	uint8_t didDataLowByte = requestMessageData[responseDataIndex++];
	uint16_t didData = ((uint16_t)didDataHighByte << 8) | didDataLowByte;

	uint16_t result = EE_WriteVariable(did, didData);
	if (result != HAL_OK)
	{
	    return DCM_NRC_GENERAL_PROGRAMMING_FAILURE;
	} else
	{
		responseData[0] = didHighByte;
		responseData[1] = didLowByte;
		*responseDataLength = 2; // two bytes of DID in response
	}

    return 0x00;
}
