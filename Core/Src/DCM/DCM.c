/*
 * DCM.c
 *
 *  Created on: Sep 28, 2023
 *      Author: MNN1CLJ
 */

#include <Dcm.h>
#include <Dcm_Service_RoutineControl.h>


void Dcm_Init()
{
		Dcm_RoutineControlTable_Init();

		// Aici testam serviciile

	//	uint8_t requestMessageLength = 5;
	//	uint8_t requestMessageData[5] = { 0x2E, 0x20, 0x10, 0X27, 0X65 };
	//	uint8_t responseData[8];
	//	uint8_t responseDataLength;
	//	Dcm_Service_WriteDataByIdentifier(requestMessageData, requestMessageLength, responseData, &responseDataLength);

		uint8_t requestMessageLength1 = 5, requestMessageLength2 = 6;
		uint8_t requestMessageData1[5] = { 0x31, 0x01, 0x00, 0x03, 0x65 }, requestMessageData2[5] = { 0x23, 0x12, 0x99, 0x99, 0x01 };
		uint8_t responseData1[8], responseData2[8];
		uint8_t responseDataLength1, responseDataLength2;
		uint8_t testResponseRC, testResponseRMBA;
		testResponseRC = Dcm_Service_RoutineControl(requestMessageData1, requestMessageLength1, responseData1, &responseDataLength1);
		HAL_FLASH_Unlock();
		if((EE_WriteVariable(0x9999,  0x1234)) != HAL_OK)
		{
			Error_Handler();
		}

		testResponseRMBA = Dcm_Service_ReadMemoryByAddress(requestMessageData2, requestMessageLength2, responseData2, &responseDataLength2);

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
