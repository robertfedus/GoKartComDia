/*
 * Dcm_Service_ReadMemoryByAddress.c
 *
 *  Created on: Oct 24, 2023
 *      Author: FER3CLJ
 */
#include <Eeprom.h>
#include <Dcm_Service_ReadMemoryByAddress.h>
#include <Constants.h>



uint8_t Dcm_Service_ReadMemoryByAddress(uint8_t *requestMessageData, uint8_t requestMessageLength, uint8_t *responseData, uint8_t *responseDataLength)
{
	if (requestMessageLength < 3 || requestMessageLength > 8)
		return DCM_NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;

	uint8_t addressAndLengthFormatIdentifier, memorySizeLength, memoryAddressLength;
	/*
	    bits 0-3 of addressAndLengthFormatIdentifier=length in bytes of memoryAddress
	    bits 4-7 of addressAndLengthFormatIdentifier=length in bytes of memorySize
	*/
	addressAndLengthFormatIdentifier = requestMessageData[1];
	memoryAddressLength = addressAndLengthFormatIdentifier & 0x0f;
	memorySizeLength = addressAndLengthFormatIdentifier >> 4;

	if((memoryAddressLength > 6) || (memoryAddressLength < 1) || (memorySizeLength == 0) || (memorySizeLength > 7))
		return DCM_NRC_REQUEST_OUT_OF_RANGE;

	uint8_t memoryAddressArray[memoryAddressLength];
	for(int i=0;i<memoryAddressLength;i++)
	{
		memoryAddressArray[i] = requestMessageData[i+2]; //because the first 2 bytes are already occupied
	}

	uint16_t memoryAddress=memoryAddressArray[0];
	for(int i=1;i<memoryAddressLength;i++) //concatenate bytes to form the address
	{
		memoryAddress=(memoryAddress<<8) | memoryAddressArray[i];
	}

	*responseDataLength = memorySizeLength + 1;
	responseData[0] = DCM_SERVICE_ID_READ_MEMORY_BY_ADDRESS;


	uint8_t dataRecord[7];
	uint16_t varRead;
	for(int i=0 ; i<memorySizeLength ; i++)
	{
		HAL_FLASH_Unlock();
		if(EE_ReadVariable(memoryAddress, &varRead))
		{
			Error_Handler();
		}
		HAL_FLASH_Lock();
		dataRecord[i] = (uint8_t)varRead;
		memoryAddress++;
	}

	for(int i=0 ; i<memorySizeLength ; i++)
		responseData[i+1] = dataRecord[i];

    return DCM_POSITIVE_RESPONSE;
}
