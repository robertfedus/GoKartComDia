/*
 * Dcm_Service_SecurityAccess.c
 *
 *  Created on: Oct 24, 2023
 *      Author: FER3CLJ
 */
#include <Dcm_Service_SecurityAccess.h>

//extern uint16_t Dcm_Service_SecurityAccess_SeedCounter;
uint16_t Dcm_Service_SecurityAccess_SeedCounter;
//extern uint8_t Dcm_ActiveSecurityLevel;
uint8_t Dcm_ActiveSecurityLevel;

uint16_t requestedSeed = 0x00;
uint16_t requestedSeedCounter = 0x00;
uint16_t encryptedSeed = 0x00;
uint8_t requestedSecurityLevel = 0x00;
uint8_t serviceState = DCM_SERVICE_SECURITY_ACCESS_IDLE;

//// exceededNumberOfAttempts and requiredTimeDelayNotExpired to be implemented when a separate client is available
Dcm_Service_ResponseCode Dcm_Service_SecurityAccess_RequestNrcCheck(uint8_t *requestMessageData, uint8_t requestMessageDataLength)
{
	if (requestMessageData[0] != DCM_SERVICE_ID_SECURITY_ACCESS)
	{
		return DCM_SERVICE_NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;
	}

	// 0x13 NRC
	// incorrectMessageLengthOrInvalidFormat
	// This NRC shall be sent if the length of the message is wrong.
	if (requestMessageDataLength > 8)
	{
		return DCM_SERVICE_NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;
	}


	// 0x12 NRC
	// sub-functionNotSupported
	// This NRC shall be sent if the sub-function parameter is not supported.
	// The constant MAX_SECURITY_LEVEL describes the maximum security level this server accepts, therefore the max sub-function value is MAX_SECURITY_LEVEL + 1
	if (requestMessageData[1] < 0x01 || requestMessageData[1] >= DCM_MAX_SECURITY_LEVEL + 1)
	{
		return DCM_SERVICE_NRC_SUB_FUNCTION_NOT_SUPPORTED;
	}

	// 0x24 NRC
	// requestSequenceError
	// Send if the ‘sendKey’ sub-function is received without first receiving a ‘requestSeed’ request message.
	if ( (requestMessageData[1] % 2 == 0 && serviceState == DCM_SERVICE_SECURITY_ACCESS_IDLE)
			|| (requestMessageData[1] % 2 == 1 && serviceState == DCM_SERVICE_SECURITY_ACCESS_WAITING_FOR_KEY)
			|| (serviceState == DCM_SERVICE_SECURITY_ACCESS_WAITING_FOR_KEY && requestMessageData[1] != requestedSecurityLevel + 1))
	{
		return DCM_SERVICE_NRC_REQUEST_SEQUENCE_ERROR;
	}

	return DCM_SERVICE_NRC_NO_ERRORS;
	//return 0x00;
}


Dcm_Service_ResponseCode Dcm_Service_SecurityAccess(uint8_t *requestMessageData, uint8_t requestMessageDataLength, uint8_t *responseMessageData, uint8_t *responseMessageDataLength)
{
	uint8_t requestNRC = Dcm_Service_SecurityAccess_RequestNrcCheck(requestMessageData, requestMessageDataLength);

	if (requestNRC != DCM_SERVICE_NRC_NO_ERRORS)
	{
		return requestNRC;
	}

	uint8_t responseDataIndex = 0;
	responseMessageData[responseDataIndex++] = DCM_SERVICE_SECURITY_ACCESS_RESPONSE_SID;



	if (serviceState == DCM_SERVICE_SECURITY_ACCESS_IDLE)
	{
		requestedSecurityLevel = requestMessageData[1];

		// If the requested security level is already active, the server responds with seed 0x0000
		if (requestedSecurityLevel == Dcm_ActiveSecurityLevel)
		{
			responseMessageData[responseDataIndex++] = requestedSecurityLevel;
			responseMessageData[responseDataIndex++] = 0x00;
			responseMessageData[responseDataIndex++] = 0x00;
		}
		else
		{
			requestedSeedCounter = Dcm_Service_SecurityAccess_SeedCounter;
			// The requestedSeed is sent back to the client
			requestedSeed = requestedSeedCounter + requestedSecurityLevel;
			// We encrypt the seed to check it against the received SecurityAccess key
			encryptedSeed = Dcm_Service_SecurityAccess_EncryptSeed(requestedSeed);

			responseMessageData[responseDataIndex++] = requestedSecurityLevel;
			responseMessageData[responseDataIndex++] = requestedSeed >> 8;
			responseMessageData[responseDataIndex++] = requestedSeed & 0x00FF;

			serviceState = DCM_SERVICE_SECURITY_ACCESS_WAITING_FOR_KEY;
		}
	}
	else if (serviceState == DCM_SERVICE_SECURITY_ACCESS_WAITING_FOR_KEY)
	{

		uint8_t keyHighByte = requestMessageData[2];
		uint8_t keyLowByte = requestMessageData[3];
		uint16_t key = ((uint16_t)keyHighByte << 8) | keyLowByte;

		// In order to grant access to the requested security level, the key must:
		// match the encrypted seed calculated internally on this server,
		// be decrypted and checked against the initially requested security level
		uint16_t keySecurityLevel = Dcm_Service_SecurityAccess_DecryptKey(key) - requestedSeedCounter;
		if (key != encryptedSeed || keySecurityLevel != requestedSecurityLevel)
		{
			Dcm_Service_SecurityAccess_ResetServiceState();
			return DCM_SERVICE_NRC_INVALID_KEY;
		}

		responseMessageData[responseDataIndex++] = 0x02; // sendKey sub-function
		Dcm_ActiveSecurityLevel = requestedSecurityLevel;
		serviceState = DCM_SERVICE_SECURITY_ACCESS_IDLE;
		requestedSeed = 0x00;
		encryptedSeed = 0x00;
		requestedSeedCounter = 0x00;
		requestedSecurityLevel = 0x00;
	}

	*responseMessageDataLength = responseDataIndex;

    return DCM_SERVICE_NRC_NO_ERRORS;
	//return 0x00;
}

void Dcm_Service_SecurityAccess_ResetServiceState()
{
	serviceState = DCM_SERVICE_SECURITY_ACCESS_IDLE;
	requestedSeed = 0x00;
	encryptedSeed = 0x00;
	requestedSeedCounter = 0x00;
	requestedSecurityLevel = 0x00;
}


uint16_t Dcm_Service_SecurityAccess_EncryptSeed(uint16_t seed)
{
    return seed ^ ENCRYPTION_KEY;
	//return 0x00;
}

uint16_t Dcm_Service_SecurityAccess_DecryptKey(uint16_t key)
{
    return key ^ ENCRYPTION_KEY;
	//return 0x00;
}
