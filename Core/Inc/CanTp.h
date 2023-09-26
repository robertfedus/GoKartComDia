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

ComDia_StatusFlag CanTp_RxIndication(CanIf_StdId id, CanIf_MessageLength length, CanIf_Payload *data);

// Setati parametrii si implementati functia asta
ComDia_StatusFlag CanTp_TxConfirmation(void);

void CanTp_ErrorHandler(void);

#endif /* INC_CANTP_H_ */
