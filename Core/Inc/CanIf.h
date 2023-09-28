/*
 * CanIf.h
 *
 *  Created on: Sep 20, 2023
 *      Author: FER3CLJ
 */

#ifndef INC_CANIF_H_
#define INC_CANIF_H_

#include <Constants.h>
#include <Types.h>
#include <CanTp.h>
#include "main.h"
#include "usb_host.h"

void CanIf_MainFunction(void);
/**
  * @brief  Receives messages from the CAN Driver and forwards them to CanTP
  * @param  messageStdId standard ID of the received message
  * @param messageLength length of the received payload
  * @param message payload
  * @retval ComDia_StatusFlag COMDIA_OK if reception was successful, COMDIA_NOT_OK otherwise
  */
ComDia_StatusFlag CanIf_RxIndication(CanIf_StdId messageStdId, CanIf_MessageLength messageLength, CanIf_Payload *payload);
/**
  * @brief  Forwards messages to the CanDrv, which transmits them to the CAN bus
  * @param  messageStdId standard ID of the transmitted message
  * @param messageLength length of the transmitted payload
  * @param message payload
  * @retval ComDia_StatusFlag COMDIA_OK if transmission was successful, COMDIA_NOT_OK otherwise
  */
ComDia_StatusFlag CanIf_TxConfirmation(CanIf_StdId messageStdId, CanIf_MessageLength messageLength, CanIf_Payload *payload);
/**
  * @brief  CAN Interface Error Handler; disables IRQ interrupts and sits in infinite loop
  */
void CanIf_ErrorHandler();

void CanIf_Client(void);

#endif /* INC_CANIF_H_ */
