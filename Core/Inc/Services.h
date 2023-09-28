/*
 * Services.h
 *
 *  Created on: Sep 28, 2023
 *      Author: MNN1CLJ
 */

#ifndef INC_SERVICES_H_
#define INC_SERVICES_H_


//service define directives
#define DIAGNOSTIC_SESSION_CONTROL 0x10
#define CLEAR_DIAGNOSTIC_INFORMATION 0x14
#define READ_DTC_INFORMATION 0x19
#define READ_DATA_BY_IDENTIFIER 0x22
#define READ_MEMORY_BY_ADDRESS 0x23
#define SECURITY_ACCESS 0x27
#define WRITE_DATA_BY_IDENTIFIER 0x2E
#define ROUTINE_CONTROL 0x31
#define WRITE_MEMORY_BY_ADDRESS 0x3D

//SESSIONS
#define DEFAULT_SESSION 0X01
#define PROGRAMMING_SESSION 0x02
#define EXTENDED_SESSION 0x03



#endif /* INC_SERVICES_H_ */
