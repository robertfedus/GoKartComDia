/*
 * CanDrv.c
 *
 *  Created on: Sep 20, 2023
 *      Author: FER3CLJ
 */
#include "CanDrv.h"

/* Global Variables */

// CAN Handle for CAN1 Controller
Can_ControllerInstance Can_Hcan1;
// CAN filter for CAN1 Controller
Can_Filter Can_Can1Filter;
// CAN TxHeader for CAN1 Controller
Can_TxHeader Can_Can1TxHeader;
// CAN RxHeader for CAN1 Controller
Can_RxHeader Can_Can1RxHeader;
// CAN TxMailbox
Can_Mailbox Can_TxMailbox[4];
// CAN1 Controller ready flag
ComDia_StatusFlag Can_IsReadyFlag = CAN_NOT_READY;

/**
  * @brief  CAN Driver entry-point
  */
void Can_MainFunction(void)
{
	// Initialization of CAN Controller
	if (Can_Init(&Can_Hcan1, &Can_Can1Filter, &Can_IsReadyFlag) == CAN_NOT_READY)
	{
		// Call error handler in case the de-initialization result is not CAN_READY
		Can_ErrorHandler();
	}

//	// Deinitialization of CAN Controller
//	if (Can_DeInit(&Can_Hcan1, &Can_IsReadyFlag) != CAN_NOT_READY)
//	{
//		// Call error handler in case the de-initialization result is not CAN_NOT_READY
//		Can_ErrorHandler();
//	}
}

/**
  * @brief  Transmits messages to the CAN bus. It is interrupted when a message is received
  * @param  messageStdId standard ID of the transmitted message
  * @param messageLength length of the transmitted payload
  * @param message payload that is sent to the CAN bus
  * @retval ComDia_StatusFlag COMDIA_OK if transmission was successful, COMDIA_NOT_OK otherwise
  */
ComDia_StatusFlag Can_MainFunctionWrite(CanIf_StdId messageStdId, CanIf_MessageLength messageLength, CanIf_Payload *Can_TxData)
{
	if (Can_Write(&Can_Hcan1, &Can_Can1TxHeader, messageStdId, messageLength, Can_TxData) == COMDIA_NOT_OK)
	{
		// Returns error status in case Can_Write fails
		return COMDIA_NOT_OK;
	}

	return COMDIA_OK;
}

/**
  * @brief  Receives messages from the CAN bus
  * @retval ComDia_StatusFlag COMDIA_OK if message was received successfully, COMDIA_NOT_OK otherwise
  */
ComDia_StatusFlag Can_MainFunctionRead()
{
	// Array for received CAN payload
	Can_Payload Can_RxData[8];

	if (Can_Read(&Can_Hcan1, &Can_Can1RxHeader, Can_RxData) == COMDIA_NOT_OK)
	{
		// Returns error status in case Can_Read fails
		return COMDIA_NOT_OK;
	}

	CanIf_RxIndication(Can_Can1RxHeader.StdId, Can_Can1RxHeader.DLC, Can_RxData);

	return COMDIA_OK;
}

/**
  * @brief  Transmits messages to the CAN bus. The transmitted message flow is interrupted when a message is received
  * @param  messageStdId standard ID of the transmitted message
  * @param messageLength length of the transmitted payload
  * @param message payload
  * @retval ComDia_StatusFlag COMDIA_OK if transmission was successful, COMDIA_NOT_OK otherwise
  */
ComDia_StatusFlag Can_Write(
		Can_ControllerInstance *hcan,
		Can_TxHeader *TxHeader, Can_StdId messageStdId,
		Can_MessageLength messageLength,
		Can_Payload *Can_TxData)
{
	// Message length
	TxHeader->DLC = messageLength;
	// Extended ID; not used
	TxHeader->ExtId = 0;
	// CAN ID type
	TxHeader->IDE = CAN_ID_STD;
	// CAN frame type
	TxHeader->RTR = CAN_RTR_DATA;
	// CAN StdId
	TxHeader->StdId = CAN_DCM_STDID;
	// Enable to capture the initial time stamp of the transmission; not used
	TxHeader->TransmitGlobalTime = DISABLE;

	// Transmit messages in loop
	// STM32 API to transmit message
	if (HAL_CAN_AddTxMessage(hcan, TxHeader, Can_TxData, &Can_TxMailbox[0]) != HAL_OK)
	{
		// Returns error status in case API status is not HAL_OK
		return COMDIA_NOT_OK;
	}

	return COMDIA_OK;
}
/**
  * @brief  Receives messages from the CAN bus
  * @retval ComDia_StatusFlag COMDIA_OK if message was received successfully, COMDIA_NOT_OK otherwise
  */
ComDia_StatusFlag Can_Read(Can_ControllerInstance *hcan, Can_RxHeader *RxHeader, Can_Payload *RxData)
{
	// STM32 API to receive message
	if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, RxHeader, RxData) != HAL_OK)
	{
		// Returns error status in case API status is not HAL_OK
		return COMDIA_NOT_OK;
	}

	return COMDIA_OK;
}

/**
  * @brief  Called on interruption, when message is received
  * @param Can_ControllerInstance pointer to default Can_ControllerInstance; should not be used, use Can_Hcan1 global variable instead
  */
void HAL_CAN_RxFifo0MsgPendingCallback(Can_ControllerInstance *hcan)
{
	if (Can_MainFunctionRead() == COMDIA_NOT_OK)
	{
		// Call error handler in case the result is an error status
		Can_ErrorHandler();
	}
}

/**
  * @brief  Initialization and configuration of CAN1 STM32 CAN Controller
  * @retval ComDia_StatusFlag COMDIA_OK if configuration was successful, COMDIA_NOT_OK otherwise
  */
ComDia_StatusFlag Can_Init(Can_ControllerInstance *hcan, Can_Filter *filter, ComDia_StatusFlag *readyFlag)
{
	/* STM32-specific initializations */
	// CAN Controller instance
	hcan->Instance = CAN1;
	// Length of a time quantum
	hcan->Init.Prescaler = 18;
	// CAN Controller mode
	hcan->Init.Mode = CAN_MODE_LOOPBACK;
	// Specifies the maximum number of time quanta the CAN hardware is allowed to lengthen or shorten a bit to perform resynchronization
	hcan->Init.SyncJumpWidth = CAN_SJW_1TQ;
	// Specifies the number of time quanta in Bit Segment 1
	hcan->Init.TimeSeg1 = CAN_BS1_15TQ;
	// Specifies the number of time quanta in Bit Segment 2
	hcan->Init.TimeSeg2 = CAN_BS2_1TQ;
	// Enable or disable the time triggered communication mode
	hcan->Init.TimeTriggeredMode = DISABLE;
	// Enable or disable the automatic bus-off management
	hcan->Init.AutoBusOff = DISABLE;
	// Enable or disable the automatic wake-up mode
	hcan->Init.AutoWakeUp = DISABLE;
	// Enable or disable the non-automatic retransmission mode
	hcan->Init.AutoRetransmission = DISABLE;
	// Enable or disable the Receive FIFO Locked mode
	hcan->Init.ReceiveFifoLocked = DISABLE;
	// Enable or disable the transmit FIFO priority
	hcan->Init.TransmitFifoPriority = DISABLE;

	/* STM32-specific Error Handler */
	if (HAL_CAN_Init(hcan) != HAL_OK)
	{
		*readyFlag = CAN_NOT_READY;
		// Returns not-ready status in case API status is not HAL_OK
		return *readyFlag;
	}

	if (Can_FilterConfig(hcan, filter) == COMDIA_NOT_OK)
	{
		*readyFlag = CAN_NOT_READY;
		// Returns not-ready status in case filter configuration fails
		return *readyFlag;
	}

	if(HAL_CAN_Start(hcan) != HAL_OK)
	{
		*readyFlag = CAN_NOT_READY;
		// Returns not-ready status in case CAN Controller start-up fails
		return *readyFlag;
	}

	if (HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
	{
		*readyFlag = CAN_NOT_READY;
		// Returns not-ready status in case CAN Controller notification activation fails on FIFO0
		return *readyFlag;
	}

	*readyFlag = CAN_READY;

	return *readyFlag;
}

/**
  * @brief  CAN1 Controller filter configuration
  * @retval ComDia_StatusFlag COMDIA_OK if configuration was successful, COMDIA_NOT_OK otherwise
  */
ComDia_StatusFlag Can_FilterConfig(Can_ControllerInstance *hcan, Can_Filter *filter)
{
	/* CAN1 filter configuration - all messages are accepted in the current configuration */
	filter->FilterActivation = ENABLE;
	filter->FilterBank  = 0;
	filter->FilterFIFOAssignment = CAN_RX_FIFO0;
	filter->FilterIdHigh = 0x0000;
	filter->FilterIdLow = 0x0000;
	filter->FilterMaskIdHigh = 0x0000;
	filter->FilterMaskIdLow = 0x0000;
	filter->FilterMode = CAN_FILTERMODE_IDMASK;
	filter->FilterScale = CAN_FILTERSCALE_32BIT;

	// STM32 API to configure filter
	if (HAL_CAN_ConfigFilter(hcan, filter) != HAL_OK)
	{
		// Returns error status in case API status is not HAL_OK
		return COMDIA_NOT_OK;
	}

	return COMDIA_OK;
}

/**
  * @brief  De-initializes CAN1 Controller and stops CAN communication
  * @retval ComDia_StatusFlag CAN_NOT_READY if de-initialization was successful, CAN_READY otherwise
  */
ComDia_StatusFlag Can_DeInit(Can_ControllerInstance *hcan, ComDia_StatusFlag *readyFlag)
{
	// Stops CAN communication for CAN1 Controller
	if (HAL_CAN_Stop(hcan) != HAL_OK)
	{
		// Can_IsReady remains CAN_READY is HAL_CAN_Stop fails
		*readyFlag = CAN_READY;
		return *readyFlag;
	}

	// De-initializes the CAN1 Controller
	if (HAL_CAN_DeInit(hcan) != HAL_OK)
	{
		// Can_IsReady remains CAN_READY is HAL_CAN_DeInit fails
		*readyFlag = CAN_READY;
		return *readyFlag;
	}

	*readyFlag = CAN_NOT_READY;
	return *readyFlag;
}

/**
  * @brief  CAN Driver Error Handler; disables IRQ interrupts and sits in infinite loop
  */
void Can_ErrorHandler(void)
{
	// All IRQ interrupts are disabled
	__disable_irq();
	// Sit in infinite loop
	for(;;);
}
