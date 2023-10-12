/*
 * CanDrv_Tests.c
 *
 *  Created on: Sep 26, 2023
 *      Author: FER3CLJ
 */

#include <Test_CanDrv.h>

Can_ControllerInstance Test_Can_Hcan1;

Can_Filter Test_Can_Can1Filter;

Can_TxHeader Test_Can_Can1TxHeader;

Can_RxHeader Test_Can_Can1RxHeader;

Can_Mailbox Test_Can_TxMailbox[4];

ComDia_StatusFlag Test_Can_IsReadyFlag = CAN_NOT_READY;

ComDia_StatusFlag Test_CanDrv(void)
{
	if (Test_Can_Init() != COMDIA_TEST_OK)
	{
		return COMDIA_TEST_NOT_OK;
	}

	if (Test_Can_Write() != COMDIA_TEST_OK)
	{
		return COMDIA_TEST_NOT_OK;
	}

	if (Test_Can_DeInit() != COMDIA_TEST_OK)
	{
		return COMDIA_TEST_NOT_OK;
	}

	return COMDIA_TEST_OK;
}

ComDia_StatusFlag Test_Can_Init(void)
{
	if (Can_Init(&Test_Can_Hcan1, &Test_Can_Can1Filter, &Test_Can_IsReadyFlag) == CAN_NOT_READY)
	{
		return COMDIA_TEST_NOT_OK;
	}

	if (Test_Can_IsReadyFlag == CAN_NOT_READY)
	{
		return COMDIA_TEST_NOT_OK;
	}

	return COMDIA_TEST_OK;
}

ComDia_StatusFlag Test_Can_Write(void)
{
	Can_StdId messageStdId = CAN_DCM_STDID;
	// Transmitted message length
	Can_MessageLength messageLength = 8;
	// Transmitted payload
	Can_Payload Can_TxData[8] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };

	if (Can_Write(&Test_Can_Hcan1, &Test_Can_Can1TxHeader, messageStdId, messageLength, Can_TxData) == COMDIA_NOT_OK)
	{
		// Returns error status in case Can_Write fails
		return COMDIA_TEST_NOT_OK;
	}

	if (Test_Can_Hcan1.State != HAL_CAN_STATE_LISTENING)
	{
		return COMDIA_TEST_NOT_OK;
	}

	return COMDIA_TEST_OK;
}

ComDia_StatusFlag Test_Can_DeInit(void)
{
//	if (Can_DeInit(&Test_Can_Hcan1, &Test_Can_IsReadyFlag) == CAN_READY)
//	{
//		return COMDIA_TEST_NOT_OK;
//	}
//
//	if (Test_Can_IsReadyFlag == CAN_READY)
//	{
//		return COMDIA_TEST_NOT_OK;
//	}

	return COMDIA_TEST_OK;
}
