/*
 * CanTp.c
 *
 *  Created on: Sep 26, 2023
 *      Author: REE2CLJ
 */
#include <CanTp.h>
#include <Dcm.h>

CanTp_Frame CanTp_CanTpFrame;//structura facuta pentru a testa functionalitatea codului
CanTp_Frame CanTp_PduRFrame;//structura din PduR
CanTp_Frame CanTp_DcmFrame;
CanTp_Frame CanTp_CanIfFrame;
CanTp_StdId ids[3] = {0x720,//DCM id
                     0x721};//CAN IF id
CanTp_Frame CanTp_DcmFrame_Prev;

void CanTp_Init(void)
{
	CanTp_DcmFrame_Prev.id = 0x85; // random value
	CanTp_PduRFrame.id = -1;
}

void (*operations[])(CanTp_Frame *frame) = {PduR_Dcm_SendRequest, PduR_to_CanTp};

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

void PduR_MainFunction()
{
    for(int i = 0; i < 2; i++)
    {

      if(CanTp_PduRFrame.id == ids[i])
      {
          operations[i](&CanTp_PduRFrame);
      }

    }
}



void PduR_Dcm_SendRequest(CanTp_Frame *request)
{
	uint8_t newMessage;
	uint8_t i;

	if (request->id != CanTp_DcmFrame_Prev.id
		|| request->length != CanTp_DcmFrame_Prev.length)
	{
		newMessage = 1;
	}
	else if (request->length == CanTp_DcmFrame_Prev.length)
	{

		for (i = 0; i < request->length; i++)
		{
				if (request->data[i] != CanTp_DcmFrame_Prev.data[i])
				{
					break;
				}
		}

		if (i == request->length)
		{
			newMessage = 0;
		}
		else
		{
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET);
			newMessage = 1;
		}
	}

	if (newMessage == 1)
	{
		Dcm_Message requestMessage;

		requestMessage.length = CanTp_PduRFrame.length;

		request->id = CanTp_PduRFrame.id;
		request->length = CanTp_PduRFrame.length;
		CanTp_DcmFrame_Prev.id = request->id;
		CanTp_DcmFrame_Prev.length = request->length;

		for(i = 0; i < CAN_MAX_MESSAGE_LENGTH; i++)
		{
			if (i < request->length)
			{
				requestMessage.data[i] = CanTp_PduRFrame.data[i];

				request->data[i] = CanTp_PduRFrame.data[i];
				CanTp_DcmFrame_Prev.data[i] = CanTp_PduRFrame.data[i];
			}
			else
			{
				// Restul mesajului se umple cu 0x00, pana la CAN_MAX_MESSAGE_LENGTH
				request->data[i] = 0x00;
				CanTp_DcmFrame_Prev.data[i] = 0x00;
			}
		}



		Dcm_PduR_GetRequest(&requestMessage);
	}

}

void PduR_Dcm_GetResponse(CanTp_Frame *response)
{
	CanTp_PduRFrame.id = response->id;
	CanTp_PduRFrame.length = response->length;

    for(uint8_t i = 0; i < CanTp_PduRFrame.length; i++)
    {
    	CanTp_PduRFrame.data[i] = response->data[i];
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

    for(uint8_t i = CanTp_PduRFrame.length; i < CAN_MAX_MESSAGE_LENGTH; i++)
        {
        	// Restul mesajului se umple cu 0x00, pana la CAN_MAX_MESSAGE_LENGTH
    	CanTp_CanTpFrame.data[i] = 0x00;
        }

    CanTp_TxConfirmation(&CanTp_CanTpFrame);
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
