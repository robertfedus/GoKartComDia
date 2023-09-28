/*
 * CanIf.c
 *
 *  Created on: Sep 20, 2023
 *      Author: FER3CLJ
 */

#include <CanIf.h>
#include <CanDrv.h>

void CanIf_MainFunction(void)
{
	// Loop to transmit messages at 1-second intervals
	for(;;)
	{
		// StdId for the transmitted message
		Can_StdId messageStdId = CAN_DCM_STDID;
		// Transmitted message length
		Can_MessageLength messageLength = 6;
		// Transmitted payload
		Can_Payload Can_TxData[6] = { 0x43, 0x48, 0x4F, 0x43, 0x48, 0x4F };
		// Call CanDrv to transmit data to the CAN bus
		if (CanIf_TxConfirmation(messageStdId, messageLength, Can_TxData) == COMDIA_NOT_OK)
		{
			// Call error handler in case the result is an error status
			CanIf_ErrorHandler();
		}
		// Add delay of 1 second between transmissions
		HAL_Delay (1000);
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
