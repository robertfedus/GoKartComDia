/*
 * DCM.c
 *
 *  Created on: Sep 28, 2023
 *      Author: MNN1CLJ
 */

#include <Dcm.h>

volatile uint8_t Dcm_ActiveSecurityLevel = 0x00;

// The encryptedSeed is present here for testing purposes. It will be used as the key of the sendKey sub-function
extern uint16_t encryptedSeed;

void Dcm_Init()
{
	Dcm_DID_Init();

//	Dcm_Test_ReadDataByIdentifier();
	Dcm_Test_SecurityAccess();
}

//creating the response - serviceResponse -> 0x00 or NRC from the service; response -> the final response; serviceID -> id of the service;
//responseData -> the data returned by the service in case of positive response; response_length -> length of the response data (without the serviceID)
void Dcm_CreateResponse(uint8_t responseCode, CanTp_Frame *response, uint8_t serviceId, uint8_t *responseData, uint8_t responseLength)
{
    response->id = CAN_DCM_RESPONSE_STDID;

    if (responseCode == DCM_POSITIVE_RESPONSE)
    {
        response->data[0] = serviceId + 0x40;
            response->length = responseLength + 1;

            for (int i = 0; i < response->length - 1; i++) {
                response->data[i + 1] = responseData[i];
            }
    }
    else
    {
        response->length = 3;
        response->data[0] = 0x7F;
        response->data[1] = serviceId;
        response->data[2] = responseCode;
    }

}

void Dcm_PduR_GetRequest(Dcm_Message *requestMessage)
{
    uint8_t responseData[8]; //store data from the service
    CanTp_Frame response; //the final response from DCM
    uint8_t responseLength = 0; //length of the response
    uint8_t responseCode; //DCM response -> positive/NRC


    switch (requestMessage->data[0])
    {
        case DCM_SERVICE_ID_DIAGNOSTIC_SESSION_CONTROL:
		{
			responseCode = Dcm_Service_DiagnosticSessionControl(requestMessage->data, requestMessage->length, responseData, &responseLength);//diagnosticSessionControl(sessionType_subfunction-1 byte); //check if the request has a positive or negative
			Dcm_CreateResponse(responseCode, &response, DCM_SERVICE_ID_DIAGNOSTIC_SESSION_CONTROL, responseData, responseLength); // constructing the response - SingleFramePDU
			break;
		}

		case DCM_SERVICE_ID_CLEAR_DIAGNOSTIC_INFORMATION:
		{
			responseCode = Dcm_Service_ClearDiagnosticInformation(requestMessage->data, requestMessage->length, responseData, &responseLength);//clearDiagnosticInformation(group_of_DTC-3 bytes value);
			Dcm_CreateResponse(responseCode, &response, DCM_SERVICE_ID_CLEAR_DIAGNOSTIC_INFORMATION, responseData, responseLength);
			break;
		}

		case DCM_SERVICE_ID_READ_DTC_INFORMATION: //foarte multe subfunctii(21)
		{
			responseCode = Dcm_Service_ReadDTCInformation(requestMessage->data, requestMessage->length, responseData, &responseLength);//readDTCinformation(subfunction, DTCparametersArray-array of bytes);
			Dcm_CreateResponse(responseCode, &response, DCM_SERVICE_ID_READ_DTC_INFORMATION, responseData, responseLength);
			break;
		}

		case DCM_SERVICE_ID_READ_DATA_BY_IDENTIFIER:
		{
			responseCode = Dcm_Service_ReadDataByIdentifier(requestMessage->data, requestMessage->length, responseData, &responseLength);//readDTCinformation(subfunction, DTCparametersArray-array of bytes);
			Dcm_CreateResponse(responseCode, &response, DCM_SERVICE_ID_READ_DATA_BY_IDENTIFIER, responseData, responseLength);
			break;
		}

		case DCM_SERVICE_ID_READ_MEMORY_BY_ADDRESS:
		{
			responseCode = Dcm_Service_ReadMemoryByAddress(requestMessage->data, requestMessage->length, responseData, &responseLength);//readDTCinformation(subfunction, DTCparametersArray-array of bytes);
			Dcm_CreateResponse(responseCode, &response, DCM_SERVICE_ID_READ_MEMORY_BY_ADDRESS, responseData, responseLength);
			break;
		}

		case DCM_SERVICE_ID_SECURITY_ACCESS:
		{
			responseCode = Dcm_Service_SecurityAccess(requestMessage->data, requestMessage->length, responseData, &responseLength);//readDTCinformation(subfunction, DTCparametersArray-array of bytes);
			Dcm_CreateResponse(responseCode, &response, DCM_SERVICE_ID_SECURITY_ACCESS, responseData, responseLength);
			break;
		}

		case DCM_SERVICE_ID_WRITE_DATA_BY_IDENTIFIER:
		{
			responseCode = Dcm_Service_WriteDataByIdentifier(requestMessage->data, requestMessage->length, responseData, &responseLength);//readDTCinformation(subfunction, DTCparametersArray-array of bytes);
			Dcm_CreateResponse(responseCode, &response, DCM_SERVICE_ID_WRITE_DATA_BY_IDENTIFIER, responseData, responseLength);
			break;
		}

		case DCM_SERVICE_ID_ROUTINE_CONTROL:
		{
			responseCode = Dcm_Service_RoutineControl(requestMessage->data, requestMessage->length, responseData, &responseLength);//readDTCinformation(subfunction, DTCparametersArray-array of bytes);
			Dcm_CreateResponse(responseCode, &response, DCM_SERVICE_ID_ROUTINE_CONTROL, responseData, responseLength);
			break;
		}

		case DCM_SERVICE_ID_WRITE_MEMORY_BY_ADDRESS:
		{
			responseCode = Dcm_Service_WriteMemoryByAddress(requestMessage->data, requestMessage->length, responseData, &responseLength);//readDTCinformation(subfunction, DTCparametersArray-array of bytes);
			Dcm_CreateResponse(responseCode, &response, DCM_SERVICE_ID_WRITE_MEMORY_BY_ADDRESS, responseData, responseLength);
			break;
		}
		default:
		{
			response.id = CAN_DCM_RESPONSE_STDID;
			response.length = 3;
			response.data[0] = 0x7F;
			response.data[1] = requestMessage->data[0];
			response.data[2] = DCM_NRC_SERVICE_NOT_SUPPORTED;
		}
    }

    Dcm_PduR_SendResponse(&response);
}

void Dcm_PduR_SendResponse(CanTp_Frame *response)
{
	PduR_Dcm_GetResponse(response); //sent the response to the PDUR
}

void Dcm_Test_ReadDataByIdentifier()
{
	// Testing ReadDataByIdentifier
	uint8_t requestMessageLength = 3;
	uint8_t requestMessageData[3] = { 0x22, 0x20, 0x10 };
	uint8_t responseData[8];
	uint8_t responseDataLength;
	Dcm_Service_ResponseCode responseCode = Dcm_Service_ReadDataByIdentifier(requestMessageData, requestMessageLength, responseData, &responseDataLength);
}

void Dcm_Test_SecurityAccess()
{
	// Testing SecurityAccess
	// Requesting seed for security level 1
	uint8_t requestSeedMessageLength = 2;
	uint8_t requestSeedMessageData[3] = { 0x27, 0x01 };
	uint8_t responseSeedData[4];
	uint8_t responseSeedDataLength;
	Dcm_Service_ResponseCode responseCode1 = Dcm_Service_SecurityAccess(requestSeedMessageData, requestSeedMessageLength, responseSeedData, &responseSeedDataLength);

	/* One of the two requests below must be commented out! */
	// Sending the wrong key and obtaining an NRC
//	uint8_t sendKeyMessageLength = 4;
//	uint8_t sendKeyMessageData[4] = { 0x27, 0x02, 0x12, 0x34 };
//	uint8_t sendKeyResponseData[2];
//	uint8_t sendKeyResponseDataLength;
//	Dcm_Service_ResponseCode responseCode2 = Dcm_Service_SecurityAccess(sendKeyMessageData, sendKeyMessageLength, sendKeyResponseData, &sendKeyResponseDataLength);

	// Sending the correct key and unlocking the server
	uint8_t sendKeyMessageLength = 4;
	uint8_t sendKeyMessageData[4] = { 0x27, 0x02, encryptedSeed >> 8, encryptedSeed & 0x00FF };
	uint8_t sendKeyResponseData[2];
	uint8_t sendKeyResponseDataLength;
	Dcm_Service_ResponseCode responseCode2 = Dcm_Service_SecurityAccess(sendKeyMessageData, sendKeyMessageLength, sendKeyResponseData, &sendKeyResponseDataLength);

	// Requesting seed once again for security level 1. The server should respond with seed 0x0000
	uint8_t requestSeedMessageLength2 = 2;
	uint8_t requestSeedMessageData2[3] = { 0x27, 0x01 };
	uint8_t responseSeedData2[8];
	uint8_t responseSeedDataLength2;
	Dcm_Service_ResponseCode responseCode3 = Dcm_Service_SecurityAccess(requestSeedMessageData2, requestSeedMessageLength2, responseSeedData2, &responseSeedDataLength2);

//	int breakpointHere;
}
