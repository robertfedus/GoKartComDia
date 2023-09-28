/*
 * CanDrv.h
 *
 *  Created on: Sep 20, 2023
 *      Author: FER3CLJ
 */
#ifndef CANDRV_CANDRV_H_
#define CANDRV_CANDRV_H_

#include <Constants.h>
#include <CanIf.h>
#include <Types.h>
#include "main.h"
#include "usb_host.h"

/**
  * @brief  CAN Driver entry-point
  */
void Can_MainFunction(void);
/**
  * @brief  Transmits messages from the CAN Interface to the lower-level CAN Driver function "Can_Write"
  * @param  messageStdId standard ID of the transmitted message
  * @param messageLength length of the transmitted payload
  * @param message payload
  * @retval ComDia_StatusFlag COMDIA_OK if transmission was successful, COMDIA_NOT_OK otherwise
  */
ComDia_StatusFlag Can_MainFunctionWrite(CanIf_StdId messageStdId, CanIf_MessageLength messageLength, CanIf_Payload *Can_TxData);
/**
  * @brief  Receives messages from the lower-level CAN Driver function "Can_Rea" and forwards them to the CAN Interface
  * @retval ComDia_StatusFlag COMDIA_OK if message was received successfully, COMDIA_NOT_OK otherwise
  */
ComDia_StatusFlag Can_MainFunctionRead();

/**
  * @brief  Transmits messages to the CAN bus. The transmitted message flow is interrupted when a message is received
  * @param  messageStdId standard ID of the transmitted message
  * @param messageLength length of the transmitted payload
  * @param message payload
  * @retval ComDia_StatusFlag COMDIA_OK if transmission was successful, COMDIA_NOT_OK otherwise
  */
ComDia_StatusFlag Can_Write(
		Can_ControllerInstance *hcan,
		Can_TxHeader *TxHeader,
		Can_StdId messageStdId,
		Can_MessageLength messageLength,
		Can_Payload *Can_TxData);
/**
  * @brief  Receives messages from the CAN bus
  * @retval ComDia_StatusFlag COMDIA_OK if message was received successfully, COMDIA_NOT_OK otherwise
  */
ComDia_StatusFlag Can_Read(Can_ControllerInstance *hcan, Can_RxHeader *RxHeader, Can_Payload *RxData);
/**
  * @brief  Initialization and configuration of CAN1 STM32 CAN Controller
  * @retval ComDia_StatusFlag COMDIA_OK if configuration was successful, COMDIA_NOT_OK otherwise
  */
ComDia_StatusFlag Can_Init(Can_ControllerInstance *hcan, Can_Filter *filter, ComDia_StatusFlag *readyFlag);
/**
  * @brief  CAN1 Controller filter configuration
  * @retval ComDia_StatusFlag COMDIA_OK if configuration was successful, COMDIA_NOT_OK otherwise
  */
ComDia_StatusFlag Can_FilterConfig(Can_ControllerInstance *hcan, Can_Filter *filter);
/**
  * @brief  De-initializes CAN1 Controller and stops CAN communication
  * @retval ComDia_StatusFlag CAN_NOT_READY if de-initialization was successful, CAN_READY otherwise
  */
ComDia_StatusFlag Can_DeInit(Can_ControllerInstance *hcan, ComDia_StatusFlag *readyFlag);

// Not yet implemented
void Can_DisableControllerInterrupts(void);
// Not yet implemented
void Can_EnableControllerInterrupts(void);
/**
  * @brief  CAN Driver Error Handler; disables IRQ interrupts and sits in infinite loop
  */
void Can_ErrorHandler(void);

#endif /* CANDRV_CANDRV_H_ */
