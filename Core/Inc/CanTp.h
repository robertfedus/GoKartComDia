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
#include "cmsis_os.h"
#include "usb_host.h"


void CanTp_to_PduR();
void PduR_MainFunction(CanTp_Frame *framePduR);
void PduR_to_DCM(CanTp_Frame *CanTp_DcmFrame);
void DCM_to_PduR(CanTp_Frame *framePduR);
void PduR_to_CanTp();



ComDia_StatusFlag CanTp_RxIndication(CanIf_StdId id, CanIf_MessageLength length, CanIf_Payload *data);

// Setati parametrii si implementati functia asta
void CanTp_TxConfirmation(CanTp_Frame* frameCanIf);

void CanTp_ErrorHandler(void);

#endif /* INC_CANTP_H_ */
