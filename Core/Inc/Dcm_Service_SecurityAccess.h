/*
 * Dcm_Service_SecurityAccess.h
 *
 *  Created on: Oct 24, 2023
 *      Author: FER3CLJ
 */

#ifndef INC_DCM_SERVICE_SECURITYACCESS_H_
#define INC_DCM_SERVICE_SECURITYACCESS_H_

#include <stdint.h>

uint8_t Dcm_Service_SecurityAccess(uint8_t *requestMessageData, uint8_t requestMessageDataLength, uint8_t *responseMessageData, uint8_t *responseMessageDataLength);
uint16_t Dcm_Service_SecurityAccess_GenerateSeed(uint8_t securityLevel);
#endif /* INC_DCM_SERVICE_SECURITYACCESS_H_ */
