/*
 * Dcm_Service_WriteMemoryByAddress.c
 *
 *  Created on: Oct 24, 2023
 *      Author: FER3CLJ
 */
#include <Eeprom.h>
#include <Dcm_Service_WriteMemoryByAddress.h>
#include <Constants.h>

uint8_t Dcm_Service_WriteMemoryByAddress(uint8_t *requestMessageData, uint8_t requestMessageLength, uint8_t *responseData, uint8_t *responseDataLength)
{
    uint8_t responseDataIndex = 0, requestDataIndex = 2;
    responseData[responseDataIndex++] = DCM_SERVICE_ID_WRITE_MEMORY_BY_ADDRESS;

	uint8_t addressHighByte = requestMessageData[requestDataIndex++], addressLowByte = requestMessageData[requestDataIndex++];
	uint16_t memoryAddress = ((uint16_t) addressHighByte << 8) + addressLowByte;

	uint8_t memorySize = requestMessageData[requestDataIndex++];
	for(uint8_t dataIndex = 0; dataIndex < memorySize; dataIndex++)
	{
		uint16_t data = requestMessageData[requestDataIndex + dataIndex];

		if((EE_WriteVariable(memoryAddress,  data)) != HAL_OK)
			{
				Error_Handler();
			}

		memoryAddress++;
	}

	for(int i = 1; i < 5; i++)
		responseData[responseDataIndex++] = requestMessageData[i];
	*responseDataLength = responseDataIndex;
    return DCM_POSITIVE_RESPONSE;
}

