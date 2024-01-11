/*
 * Dcm_Service_WriteDataByIdentifier.c
 *
 *  Created on: Oct 24, 2023
 *      Author: FER3CLJ
 */
#include <Dcm_Service_WriteDataByidentifier.h>

extern Dcm_DID *allDIDs[100];

//implementation service 0X2E
uint8_t Dcm_Service_WriteDataByIdentifier(uint8_t *requestMessageData, uint8_t requestMessageLength, uint8_t *responseData, uint8_t *responseDataLength)
{
	if (requestMessageData[0] != DCM_SERVICE_ID_WRITE_DATA_BY_IDENTIFIER)
		{
			return 0x00;
		}

	//NRC 0X13
	//the length of the message is wrong
	if((requestMessageLength < 4) || (requestMessageLength > 8)){
	    	responseData[0] = NEGATIVE_RESPONSE_SID;
	    	responseData[1] = 0x13;

	    	return 0x00;

	    }

	//create positive response
	uint8_t responseDataIndex = 0;
    responseData[responseDataIndex++] = DCM_SERVICE_ID_WRITE_DATA_BY_IDENTIFIER_RESPONSE_SID;

    uint8_t requestDataIndex = 1;

    //read dataIdentifier request parameter
    uint8_t didHighByte = requestMessageData[requestDataIndex++];
    uint8_t didLowByte = requestMessageData[requestDataIndex++];
    uint16_t did = ((uint16_t)didHighByte << 8) + didLowByte;

    for (uint8_t currentDidIndex = 0; currentDidIndex < DCM_DID_COUNT; currentDidIndex++){

    	Dcm_DID *currentDid = allDIDs[currentDidIndex];

    	if (allDIDs[currentDidIndex]->id == did){
    		responseData[responseDataIndex++] = didHighByte;
    		responseData[responseDataIndex++] = didLowByte;

    		for (uint8_t currentDidDataIndex = 0; currentDidDataIndex <= requestMessageLength-requestDataIndex; currentDidDataIndex++){

    				currentDid->data[currentDidDataIndex] = requestMessageData[requestDataIndex++];
    		}

    	}

    }

    			*responseDataLength = responseDataIndex;


    return 0x00;
}
