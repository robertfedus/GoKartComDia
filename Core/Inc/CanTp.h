/*
 * CanTp.h
 *
 *  Created on: Sep 26, 2023
 *      Author: REE2CLJ
 */

#ifndef INC_CANTP_H_
#define INC_CANTP_H_

#include <Constants.h>
#include <Types.h>
#include <CanIf.h>
#include "main.h"
#include "usb_host.h"

void CanTp_Init(void);
void CanTp_PduR_SendRequest();

void PduR_MainFunction();
void PduR_Dcm_SendRequest(CanTp_Frame *request);
void PduR_Dcm_GetResponse(CanTp_Frame *response);
void PduR_CanTp_SendResponse();

ComDia_StatusFlag CanTp_RxIndication(CanTp_StdId id, CanTp_MessageLength length, CanTp_Payload *data);

// Setati parametrii si implementati functia asta
void CanTp_TxConfirmation(CanTp_Frame* frameCanIf);

void CanTp_ErrorHandler(void);

#endif /* INC_CANTP_H_ */
