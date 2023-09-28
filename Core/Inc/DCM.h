/*
 * DCM.h
 *
 *  Created on: Sep 28, 2023
 *      Author: MNN1CLJ
 */

#ifndef INC_DCM_H_
#define INC_DCM_H_

#include <Types.h>
#include <Responses.h>
#include <Services.h>
#include <Constants.h>
#include <CanTp.h>
#include <main.h>

//Negative or positive response
void ResponseHandler(uint8_t DCM_response, CanTp_Frame *response, uint8_t serviceID, uint8_t *responseData, uint8_t response_length);

//DCM response
void GetResponse(CanTp_Frame *request);

#endif /* INC_DCM_H_ */
