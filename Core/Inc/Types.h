/*
 * Types.h
 *
 *  Created on: Sep 20, 2023
 *      Author: FER3CLJ
 */

#ifndef INC_TYPES_H_
#define INC_TYPES_H_

#include "main.h"
#include "cmsis_os.h"
#include "usb_host.h"
#include <Constants.h>

/* GENERAL-PURPOSE TYPES */

// General-purpose error/status flag, value should be 0 or 1
typedef uint8_t ComDia_StatusFlag;

/* CANDRV-SPECIFIC Types */

typedef uint8_t Can_Payload;
// Standard ID for CAN frame
// Standard ID is 11 bits long, but STM32 specifies its use by 32-bit unsigned integers
typedef uint32_t Can_StdId;
// CAN Mailbox
typedef uint32_t Can_Mailbox;
// CAN Message length
typedef uint32_t Can_MessageLength;

/* CANIF-SPECIFIC TYPES */

// Mapping the CAN Driver payload to a CAN Interface payload
typedef Can_Payload CanIf_Payload;
// 16-bit unsigned integer since the CAN Standard ID is 11-bits long
typedef uint16_t CanIf_StdId;
// 8-bit unsigned integer since the CAN message length doesn't go above 8 for non-extended frames
typedef uint8_t CanIf_MessageLength;

/* CANTP-SPECIFIC TYPES */

/* STM32 ABSTRACT TYPES */

// CAN Controller Instance
typedef CAN_HandleTypeDef Can_ControllerInstance;
// CAN filter
typedef CAN_FilterTypeDef Can_Filter;
// CAN TxHeader
typedef CAN_TxHeaderTypeDef Can_TxHeader;
// CAN RxHeader
typedef CAN_RxHeaderTypeDef Can_RxHeader;

#endif /* INC_TYPES_H_ */
