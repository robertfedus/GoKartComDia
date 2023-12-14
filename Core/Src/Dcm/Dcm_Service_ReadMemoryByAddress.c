/*
 * Dcm_Service_ReadMemoryByAddress.c
 *
 *  Created on: Oct 24, 2023
 *      Author: FER3CLJ
 */
#include <Dcm_Service_ReadMemoryByAddress.h>
#include <stdint.h>
#include <Eeprom.h>

#define DCM_SERVICE_ID_RMBA 0x23

#define REQUEST_OUT_OF_RANGE 0x31
#define CONDITIONS_NOT_CORRECT 0x22
#define INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT 0x13
#define SECURITY_ACCESS_DENIED 0x33


uint8_t Dcm_Service_ReadMemoryByAddress(uint8_t *requestMessageData, uint8_t requestMessageLength, uint8_t *responseData, uint8_t *responseDataLength)
{
	if (requestMessageLength < 3 || requestMessageLength > 8)
		return INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;

    //implementation
	uint8_t addressAndLengthFormatIdentifier, memorySizeLength, memoryAddressLength;
	/*
	    bits 0-3 of addressAndLengthFormatIdentifier=length in bytes of memoryAddress
	    bits 4-7 of addressAndLengthFormatIdentifier=length in bytes of memorySize
	*/
	addressAndLengthFormatIdentifier = requestMessageData[1];
	memoryAddressLength = addressAndLengthFormatIdentifier & 0x0f; //get low nibble of addressAndLengthFormatIdentifier
	memorySizeLength = addressAndLengthFormatIdentifier >> 4; //get high nibble of addressAndLengthFormatIdentifier

	if((memoryAddressLength > 6) || (memoryAddressLength < 1) || (memorySizeLength == 0) || (memorySizeLength > 7))
		return REQUEST_OUT_OF_RANGE;

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
	responseData[0] = DCM_SERVICE_ID_RMBA + 0x40;


	uint8_t dataRecord[7], varRead;
	for(int i=0 ; i<memorySizeLength ; i++)
	{
		HAL_FLASH_Unlock();
		if(EE_ReadVariable(memoryAddress, (uint16_t)&varRead))
		{
			Error_Handler();
		}
		HAL_FLASH_Lock();
		dataRecord[i] = (uint8_t)varRead;
		memoryAddress++;
	}

	for(int i=0 ; i<memorySizeLength ; i++)
		responseData[i+1] = dataRecord[i];

    return 0x00;
}
