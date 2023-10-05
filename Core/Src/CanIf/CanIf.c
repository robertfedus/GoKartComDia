/*
 * CanIf.c
 *
 *  Created on: Sep 20, 2023
 *      Author: FER3CLJ
 */

#include <CanIf.h>
#include <CanDrv.h>

int step = 0;

// Messages are being transmitted below at 1-second intervals and received by HAL_CAN_RxFifo0MsgPendingCallback in CanDrv
void CanIf_MainFunction(void)
{
	Can_MainFunction();

}

void CanIf_Client(void)
{
	Can_StdId messageStdId;
	Can_MessageLength messageLength;
	Can_Payload Can_TxData[6];

	if (step % 2 == 0)
	{
	// StdId for the transmitted message
	messageStdId = CAN_DCM_STDID;
	// Transmitted message length
	messageLength = 6;
	// Transmitted payload
	 Can_TxData[0] = 0x43;
	 Can_TxData[1] = 0x48;
	 Can_TxData[2] = 0x4F;
	 Can_TxData[3] = 0x43;
	 Can_TxData[4] = 0x48;
	 Can_TxData[5] = 0x4F;
	 step++;
	}
	else {
		// StdId for the transmitted message
		messageStdId = CAN_DCM_STDID;
		// Transmitted message length
		messageLength = 6;
		// Transmitted payload
		 Can_TxData[0] = 0x44;
		 Can_TxData[1] = 0x48;
		 Can_TxData[2] = 0x4F;
		 Can_TxData[3] = 0x44;
		 Can_TxData[4] = 0x48;
		 Can_TxData[5] = 0x4F;
	}
	// Call CanDrv to transmit data to the CAN bus
	if (CanIf_TxConfirmation(messageStdId, messageLength, Can_TxData) == COMDIA_NOT_OK)
	{
		// Call error handler in case the result is an error status
		CanIf_ErrorHandler();
	}

}

/**
  * @brief  Receives messages from the CAN Driver and forwards them to CanTP
  * @param  messageStdId standard ID of the received message
  * @param messageLength length of the received payload
  * @param message payload
  * @retval ComDia_StatusFlag COMDIA_OK if reception was successful, COMDIA_NOT_OK otherwise
  */
ComDia_StatusFlag CanIf_RxIndication(CanIf_StdId messageStdId, CanIf_MessageLength messageLength, CanIf_Payload *payload)
{
	// StdId extraction from received message
	Can_StdId stdId = messageStdId;

	// Non-relevant messages received through the CAN bus are discarded
	 if (stdId == CAN_DEFAULT_STDID || stdId == CAN_DCM_STDID)
	 {

		 // Process correct messages

		 /* COD PENTRU ELISABETA SI RARES */

		 if (CanTp_RxIndication(messageStdId, messageLength, payload) == COMDIA_NOT_OK)
		 {
			 // Call error handler in case CanTP_Request fails
			 CanIf_ErrorHandler();
		 }
	 }
	 else
	 {
		 // Discard messages with other StdId's
	 }

	return COMDIA_OK;
}

/**
  * @brief  Forwards messages to the CanDrv, which transmits them to the CAN bus
  * @param  messageStdId standard ID of the transmitted message
  * @param messageLength length of the transmitted payload
  * @param message payload
  * @retval ComDia_StatusFlag COMDIA_OK if transmission was successful, COMDIA_NOT_OK otherwise
  */
ComDia_StatusFlag CanIf_TxConfirmation(CanIf_StdId messageStdId, CanIf_MessageLength messageLength, CanIf_Payload *payload)
{
	if (Can_MainFunctionWrite(messageStdId, messageLength, payload) == COMDIA_NOT_OK)
	{
		// // Returns error status in case Can_MainFunction_Write fails
		return COMDIA_NOT_OK;
	}

	return COMDIA_OK;
}

/**
  * @brief  CAN Interface Error Handler; disables IRQ interrupts and sits in infinite loop
  */
void CanIf_ErrorHandler(void)
{
	// All IRQ interrupts are disabled
	__disable_irq();
	// Sit in infinite loop
	for(;;);
}
