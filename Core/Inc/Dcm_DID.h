/*
 * Dcm_DID.h
 *
 *  Created on: Oct 26, 2023
 *      Author: FER3CLJ
 */

#ifndef INC_DCM_DID_H_
#define INC_DCM_DID_H_

#include <Types.h>
#include <Constants.h>

void Dcm_DID_Init();

Dcm_DID Dcm_Get_DID_0x100B_diagToolAndSessionStatus();
Dcm_DID Dcm_Get_DID_0x2010_programmingStatus();
Dcm_DID Dcm_Get_DID_0x201A_appSoftwareReprogrammingAttemptCounter();
Dcm_DID Dcm_Get_DID_0xF110_ecuDiagnosticIdentification();
Dcm_DID Dcm_Get_DID_0xF1A2_vectorDeliveryID();
Dcm_DID Dcm_Get_DID_0xF1BD_ecuSignatureType();

#endif /* INC_DCM_DID_H_ */
