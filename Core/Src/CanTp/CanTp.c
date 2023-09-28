/*
 * CanTp.c
 *
 *  Created on: Sep 26, 2023
 *      Author: REE2CLJ
 */
#include <CanTp.h>
#include <DCM.h>

CanTp_Frame CanTp_CanTpFrame;//structura facuta pentru a testa functionalitatea codului
CanTp_Frame CanTp_PduRFrame;//structura din PduR
CanTp_Frame CanTp_DcmFrame;
CanTp_Frame CanTp_CanIfFrame;
CanTp_StdId ids[2] = {0x720,//DCM id
                     0x721};//CAN IF id

void (*operations[])(CanTp_Frame *frame) = {PduR_to_DCM, PduR_to_CanTp};

ComDia_StatusFlag CanTp_RxIndication(CanTp_StdId id, CanTp_MessageLength length, CanTp_Payload *data)
{
	CanTp_CanTpFrame.id = id;
	CanTp_CanTpFrame.length = length;

	for(uint8_t i = 0; i < CanTp_CanTpFrame.length; i++)
	{
		CanTp_CanTpFrame.data[i] = data[i];
	}

	CanTp_to_PduR();

	return COMDIA_OK;
}

void CanTp_to_PduR()
{
	CanTp_PduRFrame.id = CanTp_CanTpFrame.id;
	CanTp_PduRFrame.length = CanTp_CanTpFrame.length;

    for(uint8_t i = 0; i < CanTp_PduRFrame.length; i++)
    {
    	CanTp_PduRFrame.data[i] = CanTp_CanTpFrame.data[i];
    }

}

void PduR_MainFunction(CanTp_Frame *PduRFrame)
{
    for(int i = 0; i < 2; i++)
    {

      if(PduRFrame->id == ids[i])
      {
          operations[i](PduRFrame);
      }

    }
}

void PduR_to_DCM(CanTp_Frame *CanTp_DcmFrame)
{
    CanTp_DcmFrame->id = CanTp_PduRFrame.id;
    CanTp_DcmFrame->length = CanTp_PduRFrame.length;

    for(uint8_t i = 0; i < CAN_MAX_MESSAGE_LENGTH; i++)
    {
    	if (i < CanTp_PduRFrame.length)
    	{
    		CanTp_DcmFrame->data[i] = CanTp_PduRFrame.data[i];
    	}
    	else
    	{
    		// Restul mesajului se umple cu 0x00, pana la CAN_MAX_MESSAGE_LENGTH
    		CanTp_DcmFrame->data[i] = 0x00;
    	}
    }
    GetResponse(CanTp_DcmFrame);
}

void DCM_to_PduR(CanTp_Frame *PduRFrame)
{
	PduRFrame->id = CanTp_DcmFrame.id;
	PduRFrame->length = CanTp_DcmFrame.length;

    for(uint8_t i = 0; i < CanTp_DcmFrame.length; i++)
    {
    	PduRFrame->data[i] = CanTp_DcmFrame.data[i];
    }
}

void PduR_to_CanTp()
{
    CanTp_CanTpFrame.id = CanTp_PduRFrame.id;
    CanTp_CanTpFrame.length = CanTp_PduRFrame.length;

    for(uint8_t i = 0; i < CanTp_PduRFrame.length; i++)
    {
        CanTp_CanTpFrame.data[i] = CanTp_PduRFrame.data[i];
    }

    CanTp_TxConfirmation(&CanTp_CanIfFrame);
}

void CanTp_TxConfirmation(CanTp_Frame* CanIfFrame)
{
	CanIfFrame->id = CanTp_CanTpFrame.id;
	CanIfFrame->length = CanTp_CanTpFrame.length;

	for(uint8_t i = 0; i < CanTp_CanTpFrame.length; i++)
	{
		CanIfFrame->data[i] = CanTp_CanTpFrame.data[i];
	}
	CanIf_TxConfirmation(CanIfFrame->id, CanIfFrame->length, CanIfFrame->data);
}

void CanTp_ErrorHandler(void)
{
	// All IRQ interrupts are disabled
		__disable_irq();
		// Sit in infinite loop
		for(;;);
}
