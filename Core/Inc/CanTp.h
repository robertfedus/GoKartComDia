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

CanTp_StdId ids[2] = {0x720,//DCM id
                     0x721};//CAN IF id
void CanTp_to_PduR(CANTp_Frame *framePduR);
void PduR_MainFunction(CANTp_Frame *framePduR);
void PduR_to_DCM(CANTp_Frame *framePduR);
void DCM_to_PduR(CANTp_Frame *framePduR);
void PduR_to_CanTp(CANTp_Frame *framePduR);

void (*operations[])(CANTp_Frame *frame) = {PduR_to_DCM, PduR_to_CanTp};

ComDia_StatusFlag CanTp_RxIndication(CanIf_StdId id, CanIf_MessageLength length, CanIf_Payload *data);

// Setati parametrii si implementati functia asta
void CanTp_TxConfirmation(CANTp_Frame* frameCanIf);

void CanTp_ErrorHandler(void);

#endif /* INC_CANTP_H_ */
