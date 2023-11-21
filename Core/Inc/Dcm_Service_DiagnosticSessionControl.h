/*
 * Dcm_Service_DiagnosticSessionControl.h
 *
 *  Created on: Oct 24, 2023
 *      Author: FER3CLJ
 */

#ifndef INC_DCM_SERVICE_DIAGNOSTICSESSIONCONTROL_H_
#define INC_DCM_SERVICE_DIAGNOSTICSESSIONCONTROL_H_

#include <stdint.h>
#include <Constants.h>

void Dcm_DiagnosticSession_Init();

uint8_t Dcm_Service_DiagnosticSessionControl(uint8_t *requestMessageData, uint8_t requestMessageLength, uint8_t *responseData, uint8_t *responseDataLength);

#endif /* INC_DCM_SERVICE_DIAGNOSTICSESSIONCONTROL_H_ */
