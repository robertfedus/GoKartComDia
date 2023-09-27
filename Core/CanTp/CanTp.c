/*
 * CanTp.c
 *
 *  Created on: Sep 26, 2023
 *      Author: REE2CLJ
 */
#include <CanTp.h>


CANTp_Frame frameCanTp;//structura facuta pentru a testa functionalitatea codului
CANTp_Frame framePduR;//structura din PduR
CANTp_Frame frameDCM;//structura din DCM
CANTp_Frame frameCanIf;//structura din DCM

CanTp_StdId ids[2] = {0x720,//DCM id
                     0x721};//CAN IF id

void (*operations[])(CANTp_Frame *frame) = {PduR_to_DCM, PduR_to_CanTp};

ComDia_StatusFlag CanTp_RxIndication(CanTp_StdId id, CanTp_MessageLength length, CanTp_Payload *data)
{
	frameCanTp.id = id;
	frameCanTp.length = length;
	for(uint8_t i=0; i<=frameCanTp.length; i++){
		frameCanTp.data[i] = data[i];
	}
	CanTp_to_PduR(&framePduR);
	return COMDIA_OK;

}

void CanTp_to_PduR(CANTp_Frame *framePduR){
    framePduR->id = frameCanTp.id;
    framePduR->length = frameCanTp.length;
    for(uint8_t i=0; i<=framePduR->length; i++){
        framePduR->data[i] = frameCanTp.data[i];
    }

}

void PduR_MainFunction(CANTp_Frame *framePduR){
    for(int i=0;i<2;i++){

      if(framePduR->id==ids[i]) {
          operations[i](&framePduR);
      }

    }
}

void PduR_to_DCM(CANTp_Frame *framePduR){
    frameDCM.id = framePduR->id;
    frameDCM.length = framePduR->length;
    for(uint8_t i=0; i<=framePduR->length; i++){
        frameDCM.data[i] = framePduR->data[i];
    }

}

void DCM_to_PduR(CANTp_Frame *framePduR){
    framePduR->id = frameDCM.id;
    framePduR->length = frameDCM.length;
    for(uint8_t i=0; i<=frameDCM.length; i++){
        framePduR->data[i] = frameDCM.data[i];
    }


}

void PduR_to_CanTp(CANTp_Frame *framePduR){
    frameCanTp.id = framePduR->id;
    frameCanTp.length = framePduR->length;
    for(uint8_t i=0; i<=framePduR->length; i++){
        frameCanTp.data[i] = framePduR->data[i];
    }

    CanTp_TxConfirmation(&frameCanIf);
}


void CanTp_TxConfirmation(CANTp_Frame* frameCanIf)
{
	frameCanIf->id = frameCanTp.id;
	frameCanIf->length = frameCanTp.length;
	for(uint8_t i=0; i<=frameCanTp.length;i++){
		frameCanIf->data[i] = frameCanTp.data[i];
	}
	CanIf_TxConfirmation(frameCanIf->id, frameCanIf->length, frameCanIf->data);
}

void CanTp_ErrorHandler(void)
{
	// All IRQ interrupts are disabled
		__disable_irq();
		// Sit in infinite loop
		for(;;);
}
