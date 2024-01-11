/*
 * Dcm_Service_WriteMemoryByAddress.c
 *
 *  Created on: Oct 24, 2023
 *      Author: FER3CLJ
 */
#include <Dcm_Service_WriteMemoryByAddress.h>


//implementation service 0X3D
uint8_t Dcm_Service_WriteMemoryByAddress(uint8_t *requestMessageData, uint8_t requestMessageLength, uint8_t *responseData, uint8_t *responseDataLength)
{
	uint8_t dataRecord[3];

	if (requestMessageData[0] != DCM_SERVICE_ID_WRITE_MEMORY_BY_ADDRESS)
			{
				return 0x00;
			}

	//NRC 0x13
    //length of the message is wrong
	if((requestMessageLength < 6)||(requestMessageLength > 8))
	            {
	                responseData[0] = NEGATIVE_RESPONSE_SID;
	    	        responseData[1] = 0x13;

	    	            return 0x00;
	            }

	uint8_t responseDataIndex = 0;

	//create positive response
	responseData[responseDataIndex++] = DCM_SERVICE_ID_WRITE_MEMORY_BY_ADDRESS_RESPONSE_SID;

	uint8_t requestDataIndex = 1;

	uint8_t addressAndLengthFormatIdentifier = requestMessageData[requestDataIndex++];

	uint8_t addressHighByte = requestMessageData[requestDataIndex++];
	uint8_t addressLowByte = requestMessageData[requestDataIndex++];
	uint16_t memoryAddress = ((uint16_t)addressHighByte << 8) + addressLowByte;

	uint8_t memorySize = requestMessageData[requestDataIndex++];

	//NRC 0x31
	//the memorySize parameter value in the request message is not supported by the server
	//the specified addressAndLengthFormatIdentifier is not valid
	//the memorySize parameter value in the request message is zero
	if((memorySize > 2) || (memorySize == 0) || (addressAndLengthFormatIdentifier != 0x12))
		{
		    responseData[0] = NEGATIVE_RESPONSE_SID;
	    	responseData[1] = 0x31;

	    	    return 0x00;
		}

	//write data in a vector
    for(uint8_t DataIndex = 0; DataIndex < memorySize; DataIndex++){

		dataRecord[DataIndex] = requestMessageData[requestDataIndex+DataIndex];

	}

    //complete the positive response
	responseData[responseDataIndex++] = requestMessageData[1];
	responseData[responseDataIndex++] = requestMessageData[2];
    responseData[responseDataIndex++] = requestMessageData[3];
    responseData[responseDataIndex++] = requestMessageData[4];

	*responseDataLength = responseDataIndex;

    return 0x00;
}

