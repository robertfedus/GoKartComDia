/*
 * DCM.c
 *
 *  Created on: Sep 28, 2023
 *      Author: MNN1CLJ
 */

#include <Dcm.h>

//creating the response - serviceResponse -> 0x00 or NRC from the service; response -> the final response; serviceID -> id of the service;
//responseData -> the data returned by the service in case of positive response; response_length -> length of the response data (without the serviceID)
void Dcm_SendResponse(uint8_t DCM_response, CanTp_Frame *response, uint8_t serviceID, uint8_t *responseData, uint8_t response_length)
{
    response->id = CAN_DCM_RESPONSE_STDID;

    if (DCM_response == DCM_POSITIVE_RESPONSE)
    {
        response->data[0] = serviceID + 0x40;
            response->length = response_length + 1;

            for (int i = 0; i < response->length - 1; i++) {
                response->data[i + 1] = responseData[i];
            }
    }
    else
    {
        response->length = 3;
        response->data[0] = 0x7F;
        response->data[1] = serviceID;
        response->data[2] = DCM_response;
    }

}

void Dcm_SendRequest(Dcm_Message *Dcm_Request)
{
    uint8_t DCM_responseData[8]; //store data from the service
    CanTp_Frame DCM_PDUR_response; //the final response from DCM
    uint8_t length_output = 0; //length of the response
    uint8_t DCM_response; //DCM response -> positive/NRC


    switch (Dcm_Request->data[0])
    {
        case DIAGNOSTIC_SESSION_CONTROL:
	{
		DCM_response = Dcm_Service_DiagnosticSessionControl(*Dcm_Request, DCM_responseData, &length_output);//diagnosticSessionControl(sessionType_subfunction-1 byte); //check if the request has a positive or negative
		Dcm_SendResponse(DCM_response, &DCM_PDUR_response, DIAGNOSTIC_SESSION_CONTROL, DCM_responseData, length_output); // constructing the response - SingleFramePDU
		break;
	}

	case CLEAR_DIAGNOSTIC_INFORMATION:
	{
		DCM_response = Dcm_Service_ClearDiagnosticInformation(*Dcm_Request, DCM_responseData, &length_output);//clearDiagnosticInformation(group_of_DTC-3 bytes value);
        Dcm_SendResponse(DCM_response, &DCM_PDUR_response, CLEAR_DIAGNOSTIC_INFORMATION, DCM_responseData, length_output);
		break;
	}

	case READ_DTC_INFORMATION: //foarte multe subfunctii(21)
	{
		DCM_response = Dcm_Service_ReadDTCInformation(*Dcm_Request, DCM_responseData, &length_output);//readDTCinformation(subfunction, DTCparametersArray-array of bytes);
		Dcm_SendResponse(DCM_response, &DCM_PDUR_response, READ_DTC_INFORMATION, DCM_responseData, length_output);
		break;
	}

	case READ_DATA_BY_IDENTIFIER:
	{
        DCM_response = Dcm_Service_ReadDataByIdentifier(*Dcm_Request, DCM_responseData, &length_output);//readDTCinformation(subfunction, DTCparametersArray-array of bytes);
		Dcm_SendResponse(DCM_response, &DCM_PDUR_response, READ_DATA_BY_IDENTIFIER, DCM_responseData, length_output);
		break;
	}

	case READ_MEMORY_BY_ADDRESS:
	{
		DCM_response = Dcm_Service_ReadMemoryByAddress(*Dcm_Request, DCM_responseData, &length_output);//readDTCinformation(subfunction, DTCparametersArray-array of bytes);
		Dcm_SendResponse(DCM_response, &DCM_PDUR_response, READ_MEMORY_BY_ADDRESS, DCM_responseData, length_output);
		break;
	}

	case SECURITY_ACCESS:
	{
		DCM_response = Dcm_Service_SecurityAccess(*Dcm_Request, DCM_responseData, &length_output);//readDTCinformation(subfunction, DTCparametersArray-array of bytes);
		Dcm_SendResponse(DCM_response, &DCM_PDUR_response, SECURITY_ACCESS, DCM_responseData, length_output);
		break;
	}

	case WRITE_DATA_BY_IDENTIFIER:
	{
		DCM_response = Dcm_Service_WriteDataByIdentifier(*Dcm_Request, DCM_responseData, &length_output);//readDTCinformation(subfunction, DTCparametersArray-array of bytes);
		Dcm_SendResponse(DCM_response, &DCM_PDUR_response, WRITE_DATA_BY_IDENTIFIER, DCM_responseData, length_output);
		break;
	}

	case ROUTINE_CONTROL:
	{
		DCM_response = Dcm_Service_RoutineControl(*Dcm_Request, DCM_responseData, &length_output);//readDTCinformation(subfunction, DTCparametersArray-array of bytes);
		Dcm_SendResponse(DCM_response, &DCM_PDUR_response, ROUTINE_CONTROL, DCM_responseData, length_output);
		break;
	}

	case WRITE_MEMORY_BY_ADDRESS:
	{
		DCM_response = Dcm_Service_WriteMemoryByAddress(*Dcm_Request, DCM_responseData, &length_output);//readDTCinformation(subfunction, DTCparametersArray-array of bytes);
		Dcm_SendResponse(DCM_response, &DCM_PDUR_response, WRITE_MEMORY_BY_ADDRESS, DCM_responseData, length_output);
		break;
	}
	default:
	{
		DCM_PDUR_response.id = CAN_DCM_RESPONSE_STDID;
		DCM_PDUR_response.length = 3;
		DCM_PDUR_response.data[0] = 0x7F;
		DCM_PDUR_response.data[1] = Dcm_Request->data[0];
		DCM_PDUR_response.data[2] = DCM_NRC_SERVICE_NOT_SUPPORTED;
	}
    }

    DCM_to_PduR(&DCM_PDUR_response); //sent the response to the PDUR
}

// Services
uint8_t Dcm_Service_DiagnosticSessionControl(Dcm_Message input, uint8_t *output, uint8_t *length_output)
{
    //implementation
    return 0x00;
}

uint8_t Dcm_Service_ClearDiagnosticInformation(Dcm_Message input, uint8_t *output, uint8_t *length_output)
{
    //implementation
    return 0x00;
}

uint8_t Dcm_Service_ReadDTCInformation(Dcm_Message input, uint8_t *output, uint8_t *length_output)
{
    //implementation
    return 0x00;
}

uint8_t Dcm_Service_ReadDataByIdentifier(Dcm_Message input, uint8_t *output, uint8_t *length_output)
{
    // Example implementation - test
    for (int i = 0; i < input.length - 1; i++) {
        output[i] = input.data[i+1];
        (*length_output)++;
    }

    output[input.length - 1] = 0x34;
    (*length_output)++;

    //implementation
    return 0x00;
}

uint8_t Dcm_Service_ReadMemoryByAddress(Dcm_Message input, uint8_t *output, uint8_t *length_output)
{
    //implementation
    return 0x13;
}

uint8_t Dcm_Service_SecurityAccess(Dcm_Message input, uint8_t *output, uint8_t *length_output)
{
    //implementation
    return 0x00;
}

uint8_t Dcm_Service_WriteDataByIdentifier(Dcm_Message input, uint8_t *output, uint8_t *length_output)
{
    //implementation
    return 0x00;
}

uint8_t Dcm_Service_RoutineControl(Dcm_Message input, uint8_t *output, uint8_t *length_output)
{
    //implementation
    return 0x00;
}

uint8_t Dcm_Service_WriteMemoryByAddress(Dcm_Message input, uint8_t *output, uint8_t *length_output)
{
    //implementation
    return 0x00;
}

