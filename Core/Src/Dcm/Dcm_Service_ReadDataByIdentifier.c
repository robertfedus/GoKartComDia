/*
 * Dcm_Service_ReadDataByIdentifier.c
 *
 *  Created on: Oct 24, 2023
 *      Author: FER3CLJ
 */
#include <Dcm_Service_ReadDataByIdentifier.h>

extern Dcm_DID *allDIDs[100];
// HANDLE securityAccessDenied NRC!
// HANDLE requestOutOfRange NRC! (partea cu sesiunea si dynamicDefinedDataIdentifier)
// HANDLE conditionsNotCorrect NRC!
//Dcm_Service_ResponseCode Dcm_Service_ReadDadaByIdentifier_RequestNrcCheck(uint8_t *requestMessageData, uint8_t requestMessageDataLength)
//{
//	// 0x13 NRC
//	// incorrectMessageLengthOrInvalidFormat
//	// This NRC shall be sent if the length of the request message is invalid or the client exceeded
//	// the maximum number of dataIdentifiers allowed to be requested at a time.
//	if (requestMessageData[0] != DCM_SERVICE_ID_READ_DATA_BY_IDENTIFIER)
//	{
//		return DCM_SERVICE_NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;
//	}
//
//	if (requestMessageDataLength != 3)
//	{
//		// Only one DID can be read at a time, since the CAN Payload only accepts 8 bytes/message
//		return DCM_SERVICE_NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;
//	}
//
//	return DCM_SERVICE_NRC_NO_ERRORS;
//}
//
//Dcm_Service_ResponseCode Dcm_Service_ReadDadaByIdentifier_ResponseNrcCheck(uint8_t *responseMessageData, uint8_t *responseMessageDataLength)
//{
//	// 0x14 NRC
//	// responseTooLong
//	// This NRC shall be sent if the total length of the response message exceeds the limit of the
//	// underlying transport protocol (e.g., when multiple DIDs are requested in a single request).
//	if (*responseMessageDataLength > 8)
//	{
//		return DCM_SERVICE_NRC_RESPONSE_TOO_LONG;
//	}
//
//	return DCM_SERVICE_NRC_NO_ERRORS;
//}

Dcm_Service_ResponseCode Dcm_Service_ReadDataByIdentifier(uint8_t *requestMessageData, uint8_t requestMessageLength, uint8_t *responseData, uint8_t *responseDataLength)
{
	if (requestMessageData[0] != DCM_SERVICE_ID_READ_DATA_BY_IDENTIFIER)
			{
				return DCM_NRC_SERVICE_NOT_SUPPORTED;
			}

	    if(requestMessageLength != 3)
	    {
	    	return DCM_NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;
	    }

	    uint8_t responseDataIndex = 1;
	    uint8_t didHighByte = requestMessageData[responseDataIndex++];
	    uint8_t didLowByte = requestMessageData[responseDataIndex++];
	    uint16_t did = ((uint16_t)didHighByte << 8) | didLowByte;

	uint16_t didData = 0;

	uint16_t result = EE_ReadVariable(did, &didData);
		if (result != HAL_OK)
		{
		    return DCM_SERVICE_NRC_REQUEST_OUT_OF_RANGE;
		} else
		{
			responseData[0] = didHighByte;
			responseData[1] = didLowByte;
			responseData[2] = ((uint8_t)(didData >> 8));
			responseData[3] = (uint8_t)didData;
			*responseDataLength = 4;
		}


	// 0x31 NRC
	// requestOutOfRange
	// This NRC shall be sent if:
	// none of the requested dataIdentifier values are supported by the device;
	// none of the requested dataIdentifiers are supported in the current session;
	// the requested dynamicDefinedDataIdentifier has not been assigned yet;
//	if (!foundAtLeastOneDid)
//	{
//		return DCM_SERVICE_NRC_REQUEST_OUT_OF_RANGE;
//	}
//
//	uint8_t responseNRC = Dcm_Service_ReadDadaByIdentifier_ResponseNrcCheck(responseMessageData, responseMessageDataLength);
//
//	if (responseNRC != 0x00)
//	{
//		return responseNRC;
//	}

    return DCM_SERVICE_NRC_NO_ERRORS;
}
