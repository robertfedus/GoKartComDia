/*
 * Dcm_Service_SecurityAccess.h
 *
 *  Created on: Oct 24, 2023
 *      Author: FER3CLJ
 */

#ifndef INC_DCM_SERVICE_SECURITYACCESS_H_
#define INC_DCM_SERVICE_SECURITYACCESS_H_

#include <stdint.h>
#include <Constants.h>
#include <Types.h>

#define DCM_SERVICE_SECURITY_ACCESS_RESPONSE_SID 0x67
/* Constants that denote the current state of this service */
// IDLE means that no previous request was sent to the service. The service returns to IDLE if there has been a false access attempt (invalid access key request)
#define DCM_SERVICE_SECURITY_ACCESS_IDLE 0
// WAITING_FOR_KEY means that a seed was previously generated and send to the client and for the next request an access key is expected
#define DCM_SERVICE_SECURITY_ACCESS_WAITING_FOR_KEY 1

// This key does NOT refer to the SecurityAccess key. It is only used to decrypt the received key
#define ENCRYPTION_KEY 0x2202

Dcm_Service_ResponseCode Dcm_Service_SecurityAccess(uint8_t *requestMessageData, uint8_t requestMessageDataLength, uint8_t *responseMessageData, uint8_t *responseMessageDataLength);
void Dcm_Service_SecurityAccess_ResetServiceState();
uint16_t Dcm_Service_SecurityAccess_GenerateSeed(uint8_t securityLevel);
uint16_t Dcm_Service_SecurityAccess_EncryptSeed(uint16_t seed);
uint16_t Dcm_Service_SecurityAccess_DecryptKey(uint16_t key);
Dcm_Service_ResponseCode Dcm_Service_SecurityAccess_RequestNrcCheck(uint8_t *requestMessageData, uint8_t requestMessageDataLength);
#endif /* INC_DCM_SERVICE_SECURITYACCESS_H_ */
