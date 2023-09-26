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

void (*operations[])(Frame *frame) = {PduR_to_DCM, PduR_to_CanTp};

ComDia_StatusFlag CanTp_RxIndication(CanIf_StdId id, CanIf_MessageLength length, CanIf_Payload *data);

// Setati parametrii si implementati functia asta
ComDia_StatusFlag CanTp_TxConfirmation(void);

void CanTp_ErrorHandler(void);

#endif /* INC_CANTP_H_ */
