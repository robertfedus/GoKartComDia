/*
 * DCM.c
 *
 *  Created on: Sep 28, 2023
 *      Author: MNN1CLJ
 */

#include <DCM.h>

//creating the response - serviceResponse -> 0x00 or NRC from the service; response -> the final response; serviceID -> id of the service;
//responseData -> the data returned by the service in case of positive response; response_length -> length of the response data (without the serviceID)
void ResponseHandler(uint8_t DCM_response, CanTp_Frame *response, uint8_t serviceID, uint8_t *responseData, uint8_t response_length)
{
    response->id = CAN_DCM_RESPONSE_STDID;

    if (DCM_response == POSITIVE_RESPONSE)
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

void GetResponse(CanTp_Frame *DCM_request)
{
    uint8_t DCM_responseData[8]; //store data from the service
    CanTp_Frame DCM_PDUR_response; //the final response from DCM
    uint8_t length_output = 0; //length of the response
    uint8_t DCM_response; //DCM response -> positive/NRC


    switch (DCM_request->data[0])
    {
        case DIAGNOSTIC_SESSION_CONTROL:
	{
		DCM_response = diagnosticSessionControl(*DCM_request, DCM_responseData, &length_output);//diagnosticSessionControl(sessionType_subfunction-1 byte); //check if the request has a positive or negative
		ResponseHandler(DCM_response, &DCM_PDUR_response, DIAGNOSTIC_SESSION_CONTROL, DCM_responseData, length_output); // constructing the response - SingleFramePDU
		break;
	}

	case CLEAR_DIAGNOSTIC_INFORMATION:
	{
		DCM_response = clearDiagnosticInformation(*DCM_request, DCM_responseData, &length_output);//clearDiagnosticInformation(group_of_DTC-3 bytes value);
        ResponseHandler(DCM_response, &DCM_PDUR_response, CLEAR_DIAGNOSTIC_INFORMATION, DCM_responseData, length_output);
		break;
	}

	case READ_DTC_INFORMATION: //foarte multe subfunctii(21)
	{
		DCM_response = readDTCInformation(*DCM_request, DCM_responseData, &length_output);//readDTCinformation(subfunction, DTCparametersArray-array of bytes);
		ResponseHandler(DCM_response, &DCM_PDUR_response, READ_DTC_INFORMATION, DCM_responseData, length_output);
		break;
	}

	case READ_DATA_BY_IDENTIFIER:
	{
        DCM_response = readDataByIdentifier(*DCM_request, DCM_responseData, &length_output);//readDTCinformation(subfunction, DTCparametersArray-array of bytes);
		ResponseHandler(DCM_response, &DCM_PDUR_response, READ_DATA_BY_IDENTIFIER, DCM_responseData, length_output);
		break;
	}

	case READ_MEMORY_BY_ADDRESS:
	{
		DCM_response = readMemoryByAddress(*DCM_request, DCM_responseData, &length_output);//readDTCinformation(subfunction, DTCparametersArray-array of bytes);
		ResponseHandler(DCM_response, &DCM_PDUR_response, READ_MEMORY_BY_ADDRESS, DCM_responseData, length_output);
		break;
	}

	case SECURITY_ACCESS:
	{
		DCM_response = securityAccess(*DCM_request, DCM_responseData, &length_output);//readDTCinformation(subfunction, DTCparametersArray-array of bytes);
		ResponseHandler(DCM_response, &DCM_PDUR_response, SECURITY_ACCESS, DCM_responseData, length_output);
		break;
	}

	case WRITE_DATA_BY_IDENTIFIER:
	{
		DCM_response = writeDataByIdentifier(*DCM_request, DCM_responseData, &length_output);//readDTCinformation(subfunction, DTCparametersArray-array of bytes);
		ResponseHandler(DCM_response, &DCM_PDUR_response, WRITE_DATA_BY_IDENTIFIER, DCM_responseData, length_output);
		break;
	}

	case ROUTINE_CONTROL:
	{
		DCM_response = routineControl(*DCM_request, DCM_responseData, &length_output);//readDTCinformation(subfunction, DTCparametersArray-array of bytes);
		ResponseHandler(DCM_response, &DCM_PDUR_response, ROUTINE_CONTROL, DCM_responseData, length_output);
		break;
	}

	case WRITE_MEMORY_BY_ADDRESS:
	{
		DCM_response = writeMemoryByAddress(*DCM_request, DCM_responseData, &length_output);//readDTCinformation(subfunction, DTCparametersArray-array of bytes);
		ResponseHandler(DCM_response, &DCM_PDUR_response, WRITE_MEMORY_BY_ADDRESS, DCM_responseData, length_output);
		break;
	}
    }

    DCM_to_PduR(&DCM_PDUR_response); //sent the response to the PDUR
}

// Services
uint8_t diagnosticSessionControl(CanTp_Frame input, uint8_t *output, uint8_t *length_output)
{
    //implementation
    return 0x00;
}

uint8_t clearDiagnosticInformation(CanTp_Frame input, uint8_t *output, uint8_t *length_output)
{
    //implementation
    return 0x00;
}

uint8_t readDTCInformation(CanTp_Frame input, uint8_t *output, uint8_t *length_output)
{
    //implementation
    return 0x00;
}

uint8_t readDataByIdentifier(CanTp_Frame input, uint8_t *output, uint8_t *length_output)
{
    // Example implementation - test
    for (int i = 0; i < input.length - 1; i++) {
        output[i] = input.data[i+1];
        (*length_output)++;
    }

    output[input.length - 1] = 0x34;
    (*length_output)++;

    //implementation
    return 0x13;
}

uint8_t readMemoryByAddress(CanTp_Frame input, uint8_t *output, uint8_t *length_output)
{
    //implementation
    return 0x00;
}

uint8_t securityAccess(CanTp_Frame input, uint8_t *output, uint8_t *length_output)
{
    //implementation
    return 0x00;
}

uint8_t writeDataByIdentifier(CanTp_Frame input, uint8_t *output, uint8_t *length_output)
{
    //implementation
    return 0x00;
}

uint8_t routineControl(CanTp_Frame input, uint8_t *output, uint8_t *length_output)
{
    //implementation
    return 0x00;
}

uint8_t writeMemoryByAddress(CanTp_Frame input, uint8_t *output, uint8_t *length_output)
{
    //implementation
    return 0x00;
}

