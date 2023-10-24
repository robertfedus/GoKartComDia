/*
 * Dcm_Service_ReadDataByIdentifier.c
 *
 *  Created on: Oct 24, 2023
 *      Author: FER3CLJ
 */
#include <Dcm_Service_ReadDataByIdentifier.h>

uint8_t Dcm_Service_ReadDataByIdentifier(uint8_t *requestMessageData, uint8_t requestMessageLength, uint8_t *responseData, uint8_t *responseDataLength)
{
    // Example implementation - test
    for (int i = 0; i < requestMessageLength - 1; i++) {
        responseData[i] = requestMessageData[i + 1];
        (*responseDataLength)++;
    }

    responseData[requestMessageLength - 1] = 0x34;
    (*responseDataLength)++;

    //implementation
    return 0x00;
}
