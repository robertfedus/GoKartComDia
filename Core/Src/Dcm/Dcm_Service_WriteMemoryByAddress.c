/*
 * Dcm_Service_WriteMemoryByAddress.c
 *
 *  Created on: Oct 24, 2023
 *      Author: FER3CLJ
 */
#include <Dcm_Service_WriteMemoryByAddress.h>

uint8_t Dcm_Service_WriteMemoryByAddress(uint8_t *requestMessageData, uint8_t requestMessageLength, uint8_t *responseData, uint8_t *responseDataLength)
{
	if (requestMessageData[0] != DCM_SERVICE_ID_WRITE_MEMORY_BY_ADDRESS)
			{
				return 0x00;
			}

	uint8_t responseDataIndex = 0;
	responseData[responseDataIndex++] = DCM_SERVICE_ID_WRITE_MEMORY_BY_ADDRESS_RESPONSE_SID;

	uint8_t requestDataIndex = 2;
	uint8_t addressHighByte = requestMessageData[requestDataIndex++];
	uint8_t addressLowByte = requestMessageData[requestDataIndex++];
	uint16_t memoryAddress = ((uint16_t)addressHighByte << 8) + addressLowByte;

	uint8_t memorySize = requestMessageData[requestDataIndex++];

    for(uint8_t DataIndex = 0; DataIndex < memorySize; DataIndex++){

		uint8_t Data = requestMessageData[requestDataIndex+DataIndex];

		//SCRIEREA IN MEMORIE

        memoryAddress = memoryAddress + 1;

	}

	responseData[responseDataIndex++] = requestMessageData[1];
	responseData[responseDataIndex++] = requestMessageData[2];
    responseData[responseDataIndex++] = requestMessageData[3];
    responseData[responseDataIndex++] = requestMessageData[4];

	*responseDataLength = responseDataIndex;

    return 0x00;
}

