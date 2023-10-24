/*
 * Dcm_Service_RoutineControl.h
 *
 *  Created on: Oct 24, 2023
 *      Author: FER3CLJ
 */

#ifndef INC_DCM_SERVICE_ROUTINECONTROL_H_
#define INC_DCM_SERVICE_ROUTINECONTROL_H_

#include <stdint.h>

uint8_t Dcm_Service_RoutineControl(uint8_t *requestMessageData, uint8_t requestMessageLength, uint8_t *responseData, uint8_t *responseDataLength);

#endif /* INC_DCM_SERVICE_ROUTINECONTROL_H_ */
