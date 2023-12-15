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
uint16_t requestedSeedCounter = 0x00;
uint16_t encryptedSeed = 0x00;
uint8_t requestedSecurityLevel = 0x00;
uint8_t serviceState = DCM_SERVICE_SECURITY_ACCESS_IDLE;

//// exceededNumberOfAttempts and requiredTimeDelayNotExpired to be implemented when a separate client is available
Dcm_Service_ResponseCode Dcm_Service_SecurityAccess_RequestNrcCheck(uint8_t *requestMessageData, uint8_t requestMessageDataLength)
{

	return 0x00;
}


Dcm_Service_ResponseCode Dcm_Service_SecurityAccess(uint8_t *requestMessageData, uint8_t requestMessageDataLength, uint8_t *responseMessageData, uint8_t *responseMessageDataLength)
{

	return 0x00;
}

void Dcm_Service_SecurityAccess_ResetServiceState()
{

}


uint16_t Dcm_Service_SecurityAccess_EncryptSeed(uint16_t seed)
{

	return 0x00;
}

uint16_t Dcm_Service_SecurityAccess_DecryptKey(uint16_t key)
{

	return 0x00;
}
