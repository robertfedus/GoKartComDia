/*
 * Dcm_Service_SecurityAccess.c
 *
 *  Created on: Oct 24, 2023
 *      Author: FER3CLJ
 */
#include <Dcm_Service_SecurityAccess.h>

extern uint16_t Dcm_Service_SecurityAccess_SeedCounter;
extern uint8_t Dcm_ActiveSecurityLevel;
uint16_t requestedSeed = 0x00;
uint16_t encryptedSeed = 0x00;
uint8_t requestedSecurityLevel = 0x00;
uint8_t serviceState = IDLE;

uint8_t Dcm_Service_SecurityAccess(uint8_t *requestMessageData, uint8_t requestMessageDataLength, uint8_t *responseMessageData, uint8_t *responseMessageDataLength)
{
	uint8_t responseDataIndex = 0;
	responseMessageData[responseDataIndex++] = DCM_SERVICE_SECURITY_ACCESS_RESPONSE_SID;

	if (requestMessageData[0] != DCM_SERVICE_ID_SECURITY_ACCESS)
	{
		return DCM_SERVICE_NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;
	}

	if (serviceState == IDLE)
	{
		if (requestMessageData[1] % 2 != 1)
		{
			// HANDLE NRC
		}

		requestedSecurityLevel = requestMessageData[1];
		// The requestedSeed is sent back to the client
		requestedSeed = Dcm_Service_SecurityAccess_SeedCounter;
		// We encrypt the seed to check it against the received SecurityAccess key
		encryptedSeed = Dcm_Service_SecurityAccess_EncryptSeed(requestedSeed);

		responseMessageData[responseDataIndex++] = requestedSecurityLevel;
		responseMessageData[responseDataIndex++] = requestedSeed >> 8;
		responseMessageData[responseDataIndex++] = requestedSeed & 0x00FF;

		serviceState = WAITING_FOR_KEY;
	}
	else if (serviceState == WAITING_FOR_KEY)
	{
		if (requestMessageData[1] != requestedSecurityLevel + 1 || requestMessageData[1] % 2 != 0)
		{
			// HANDLE NRC
		}

		uint8_t keyHighByte = requestMessageData[2];
		uint8_t keyLowByte = requestMessageData[3];
		uint16_t key = ((uint16_t)keyHighByte << 8) | keyLowByte;

		if (key != encryptedSeed)
		{
			// HANDLE NRC
		}

		responseMessageData[responseDataIndex++] = 0x02; // sendKey sub-function
		Dcm_ActiveSecurityLevel = requestedSecurityLevel;
		serviceState = IDLE;
		requestedSeed = 0x00;
		encryptedSeed = 0x00;
		requestedSecurityLevel = 0x00;
	}

	*responseMessageDataLength = responseDataIndex;

    return 0x00;
}

uint16_t Dcm_Service_SecurityAccess_EncryptSeed(uint16_t seed)
{
    return seed ^ ENCRYPTION_KEY;
}

