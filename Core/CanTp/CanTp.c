/*
 * CanTp.c
 *
 *  Created on: Sep 26, 2023
 *      Author: REE2CLJ
 */
#include <CanTp.h>

ComDia_StatusFlag CanTp_RxIndication(CanIf_StdId id, CanIf_MessageLength length, CanIf_Payload *data)
{
	return COMDIA_OK;
}

// Setati parametrii si implementati functia asta
ComDia_StatusFlag CanTp_TxConfirmation(void)
{
	return COMDIA_OK;
}

void CanTp_ErrorHandler(void)
{

}
