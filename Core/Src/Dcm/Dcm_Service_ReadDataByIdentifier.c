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
uint8_t Dcm_Service_ReadDadaByIdentifier_RequestNrcCheck(uint8_t *requestMessageData, uint8_t requestMessageDataLength)
{
	// 0x13 NRC
	// incorrectMessageLengthOrInvalidFormat
	// This NRC shall be sent if the length of the request message is invalid or the client exceeded
	// the maximum number of dataIdentifiers allowed to be requested at a time.

	if (requestMessageData[0] != DCM_SERVICE_ID_READ_DATA_BY_IDENTIFIER)
	{
		return DCM_SERVICE_NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;
	}

	if (requestMessageDataLength != 3)
	{
		// Only one DID can be read at a time, since the CAN Payload only accepts 8 bytes/message
		return DCM_SERVICE_NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;
	}

	return 0x00;
}

uint8_t Dcm_Service_ReadDadaByIdentifier_ResponseNrcCheck(uint8_t *responseMessageData, uint8_t *responseMessageDataLength)
{
	// 0x14 NRC
	// responseTooLong
	// This NRC shall be sent if the total length of the response message exceeds the limit of the
	// underlying transport protocol (e.g., when multiple DIDs are requested in a single request).
	if (*responseMessageDataLength > 8)
	{
		return DCM_SERVICE_NRC_RESPONSE_TOO_LONG;
	}

	return 0x00;
}

uint8_t Dcm_Service_ReadDataByIdentifier(
		uint8_t *requestMessageData,
		uint8_t requestMessageDataLength,
		uint8_t *responseMessageData,
		uint8_t *responseMessageDataLength)
{
	uint8_t requestNRC = Dcm_Service_ReadDadaByIdentifier_RequestNrcCheck(requestMessageData, requestMessageDataLength);

	if (requestNRC != 0x00)
	{
		return requestNRC;
	}

	uint8_t responseDataIndex = 0;
	responseMessageData[responseDataIndex++] = DCM_SERVICE_ID_READ_DATA_BY_IDENTIFIER_RESPONSE_SID;
	uint8_t foundAtLeastOneDid = 0;

	for (uint8_t currentRequestByteIndex = 1; currentRequestByteIndex < requestMessageDataLength; currentRequestByteIndex += 2)
	{
		uint8_t didHighByte = requestMessageData[currentRequestByteIndex];
		uint8_t didLowByte = requestMessageData[currentRequestByteIndex + 1];
		uint16_t did = ((uint16_t)didHighByte << 8) | didLowByte;

		for (uint8_t currentDidIndex = 0; currentDidIndex < DCM_DID_COUNT; currentDidIndex++)
		{
			Dcm_DID *currentDid = allDIDs[currentDidIndex];
			if (allDIDs[currentDidIndex]->id == did)
			{
				foundAtLeastOneDid = 1;

				responseMessageData[responseDataIndex++] = didHighByte;
				responseMessageData[responseDataIndex++] = didLowByte;

				for (uint8_t currentDidDataIndex = 0; currentDidDataIndex < currentDid->dataLength; currentDidDataIndex++)
				{
					responseMessageData[responseDataIndex++] = currentDid->data[currentDidDataIndex];
				}
			}
		}

		*responseMessageDataLength = responseDataIndex;
	}

	// 0x31 NRC
	// requestOutOfRange
	// This NRC shall be sent if:
	// none of the requested dataIdentifier values are supported by the device;
	// none of the requested dataIdentifiers are supported in the current session;
	// the requested dynamicDefinedDataIdentifier has not been assigned yet;
	if (!foundAtLeastOneDid)
	{
		return DCM_SERVICE_NRC_REQUEST_OUT_OF_RANGE;
	}

	uint8_t responseNRC = Dcm_Service_ReadDadaByIdentifier_ResponseNrcCheck(responseMessageData, responseMessageDataLength);

	if (responseNRC != 0x00)
	{
		return responseNRC;
	}

    return 0x00;
}
