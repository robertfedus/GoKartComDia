/*
 * Dcm_Service_ReadDataByIdentifier.c
 *
 *  Created on: Oct 24, 2023
 *      Author: FER3CLJ
 */
#include <Dcm_Service_ReadDataByIdentifier.h>

extern Dcm_DID *allDIDs[100];

uint8_t Dcm_Service_ReadDataByIdentifier(uint8_t *requestMessageData, uint8_t requestMessageLength, uint8_t *responseData, uint8_t *responseDataLength)
{
	if (requestMessageData[0] != DCM_SERVICE_ID_READ_DATA_BY_IDENTIFIER)
	{
		return 0x00;
	}

	uint8_t responseDataIndex = 0;
	responseData[responseDataIndex++] = DCM_SERVICE_ID_READ_DATA_BY_IDENTIFIER_RESPONSE_SID;

	for (uint8_t currentRequestByteIndex = 1; currentRequestByteIndex < requestMessageLength; currentRequestByteIndex += 2)
	{
		uint8_t didHighByte = requestMessageData[currentRequestByteIndex];
		uint8_t didLowByte = requestMessageData[currentRequestByteIndex + 1];
		uint16_t did = ((uint16_t)didHighByte << 8) + didLowByte;

		for (uint8_t currentDidIndex = 0; currentDidIndex < DCM_DID_COUNT; currentDidIndex++)
		{
			Dcm_DID *currentDid = allDIDs[currentDidIndex];
			if (allDIDs[currentDidIndex]->id == did)
			{
				responseData[responseDataIndex++] = didHighByte;
				responseData[responseDataIndex++] = didLowByte;

				for (uint8_t currentDidDataIndex = 0; currentDidDataIndex < currentDid->dataLength; currentDidDataIndex++)
				{
					responseData[responseDataIndex++] = currentDid->data[currentDidDataIndex];
				}
			}
		}

		*responseDataLength = responseDataIndex;
	}

    return 0x00;
}
