/*
 * Dcm_Service_RoutineControl.c
 *
 *  Created on: Oct 24, 2023
 *      Author: FER3CLJ
 */
#include <Dcm_Service_RoutineControl.h>


//for testing routineControl
void routine1(uint8_t* output, uint8_t changeStatus, uint8_t* routineControlRecord)
{
	//GeneralProgrammingFailure NRC 0x72
}
void routine2(uint8_t* output, uint8_t changeStatus, uint8_t* routineControlRecord)
{
	//GeneralProgrammingFailure NRC 0x72
}
void routine3(uint8_t* output, uint8_t changeStatus, uint8_t* routineControlRecord)
{
	//GeneralProgrammingFailure NRC 0x72
    output[6]=200;
}



void Dcm_RoutineControlTable_Init()
{
    routineControlTable.StartRoutine[0]=routine1;
    routineControlTable.StartRoutine[1]=routine2;
    routineControlTable.StartRoutine[2]=routine3;

    routineControlTable.StopRoutine[0]=routine1;
    routineControlTable.StopRoutine[1]=routine2;
    routineControlTable.StopRoutine[2]=routine3;

    routineControlTable.RequestRoutineResults[0]=routine1;
    routineControlTable.RequestRoutineResults[1]=routine2;
    routineControlTable.RequestRoutineResults[2]=routine3;
}

//END


uint8_t Dcm_Service_RoutineControl(uint8_t *requestMessageData, uint8_t requestMessageLength, uint8_t *responseData, uint8_t *responseDataLength)
{
    //implementation
	//BEGIN
	if(requestMessageData[0] != DCM_SERVICE_ID_ROUTINE_CONTROL  ||  requestMessageLength < 5  ||  requestMessageLength > 8)
		return INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;

	routineControlTable.routineId=(requestMessageData[2] << 8) | requestMessageData[3]; //form Routine ID
	if(routineControlTable.routineId > NUMBER_OF_ROUTINE_IDENTIFIERS)
		return REQUEST_OUT_OF_RANGE; //NRC-routine id incorrect

	//for routineStatusRecord
	uint8_t routineControlOptionRecord[4];
	for(int i=0;i<4;i++)
		routineControlOptionRecord[i]=requestMessageData[i+4];

	switch(requestMessageData[1])
	{
		case START_ROUTINE:
			for(uint8_t i=0;i<3;i++)
			{
				if(routineIds[i] == routineControlTable.routineId)
				{
					if(routineStatus[i] != ROUTINE_ACTIVE)
						routineControlTable.StartRoutine[i](responseData, START_ROUTINE, routineControlOptionRecord);
					else
						return REQUEST_SEQUENCE_ERROR; //NRC-daca rutina e deja activa
				}
			}
			break;

		case STOP_ROUTINE:
			for(int i=0;i<NUMBER_OF_ROUTINE_IDENTIFIERS;i++)
			{
				if(routineIds[i]==routineControlTable.routineId)
				{
					//check if routine is currently active, if not => NRC-REQUEST_SEQUENCE_ERROR
					if(routineStatus[i] == ROUTINE_ACTIVE)
					{
						routineControlTable.StopRoutine[i](responseData, STOP_ROUTINE, routineControlOptionRecord);
					}
					else
					{
						return REQUEST_SEQUENCE_ERROR; //NRC-daca rutina e deja oprita
					}
				}
			}
			break;

		case REQUEST_ROUTINE_RESULTS:
			for(int i=0;i<NUMBER_OF_ROUTINE_IDENTIFIERS;i++)
			{
				if(routineIds[i]==routineControlTable.routineId)
				{
					//check if routine was active, if not return NRC-REQUEST_SEQUENCE_ERROR
					if(routineStatus[i] != ROUTINE_NEVER_ACTIVE)
					{
						routineControlTable.RequestRoutineResults[i](responseData, REQUEST_ROUTINE_RESULTS, routineControlOptionRecord);
					}
					else
					{
						return REQUEST_SEQUENCE_ERROR; //rutina nu a fost niciodata activa
					}
				}
			}
			break;

		default:
			return SUBFUNCTION_NOT_SUPPORTED;

	}


	responseData[0] = DCM_SERVICE_ID_ROUTINE_CONTROL + 0x40;
	for(int i=1 ; i<4 ; i++)
	{
		responseData[i] = requestMessageData[i]; //to the positive response add sub function and routine id
	}

	//END
    return 0x00;
}
