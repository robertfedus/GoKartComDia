/*
 * Dcm_Service_DiagnosticSessionControl.c
 *
 *  Created on: Oct 26, 2023
 *      Author: MNN1CLJ
 */
#include <Dcm_Service_DiagnosticSessionControl.h>

volatile uint8_t currentDiagnosticSession;
extern volatile int OS_50ms_TaskCounter;

void Dcm_DiagnosticSession_Init()
{
	currentDiagnosticSession = DEFAULT_SESSION;
}

// Services
uint8_t Dcm_Service_DiagnosticSessionControl(uint8_t *requestMessageData, uint8_t requestMessageLength, uint8_t *responseData, uint8_t *responseDataLength)
{
	// Incorrect length
	if (requestMessageLength != 2)
	     return DCM_NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;

	    switch(requestMessageData[1])
	    {

	        case DEFAULT_SESSION:                                    // se doreste trecerea in DEFAULT_SESSION - se poate din orice alta sesiune
	            currentDiagnosticSession = DEFAULT_SESSION;

	            break;

	        case PROGRAMMING_SESSION:                                // se doreste trecerea in PROGRAMMING_SESSION
	            if (currentDiagnosticSession == EXTENDED_DIAGNOSTIC_SESSION)  // se poate doar din EXTENDED_DIAGNOSTIC_SESSION
	            {
	            	currentDiagnosticSession = PROGRAMMING_SESSION;
	                 break;
	            }
	            else
	            {
	                return DCM_NRC_SUBFUNCTION_NOT_SUPPORTED_IN_ACTIVE_DIAGNOSTIC_SESSION;
	            }

	        case EXTENDED_DIAGNOSTIC_SESSION:                       // se doreste trecerea in EXTENDED_DIAGNOSTIC_SESSION - se poate din orice sesiune

	        	currentDiagnosticSession = EXTENDED_DIAGNOSTIC_SESSION;

	                break;

	        case SAFETY_SYSTEM_DIAGNOSTIC_SESSION:                  // se doreste trecerea in SAFETY_SYSTEM_DIAGNOSTIC_SESSION
	            if (currentDiagnosticSession == EXTENDED_DIAGNOSTIC_SESSION) // se poate doar din EXTENDED_DIAGNOSTIC_SESSION
	            {
	            	currentDiagnosticSession = SAFETY_SYSTEM_DIAGNOSTIC_SESSION;
	                 break;
	            }
	            else
	            {
	                return DCM_NRC_SUBFUNCTION_NOT_SUPPORTED_IN_ACTIVE_DIAGNOSTIC_SESSION;
	            }

	        default:
	          {
	              return DCM_NRC_SUBFUNCTION_NOT_SUPPORTED;
	          }
	    }

	    responseData[0] = requestMessageData[1];
	    responseData[1] = P2_SERVER_MAX_HB;
	    responseData[2] = P2_SERVER_MAX_LB;
	    responseData[3] = P2_SERVER_MAX_STAR_HB;
	    responseData[4] = P2_SERVER_MAX_STAR_LB;
	    *responseDataLength = 0x05;

	    OS_50ms_TaskCounter = 0; // se reseteaza timer-ul sesiunii atunci cand intra intr-una noua

	    return DCM_POSITIVE_RESPONSE;
}
