/*
 * Dcm_DID.c
 *
 *  Created on: Oct 26, 2023
 *      Author: FER3CLJ
 */
#include <Dcm_DID.h>

Dcm_DID DID_0x100B_diagToolAndSessionStatus;
Dcm_DID DID_0x2010_programmingStatus;
Dcm_DID DID_0x201A_appSoftwareReprogrammingAttemptCounter;
Dcm_DID DID_0xF110_ecuDiagnosticIdentification;
Dcm_DID DID_0xF1A2_vectorDeliveryID;
Dcm_DID DID_0xF1BD_ecuSignatureType;

void Dcm_DID_Init()
{
	DID_0x100B_diagToolAndSessionStatus.id = 0x100B;
	DID_0x100B_diagToolAndSessionStatus.dataLength = 4;
	DID_0x100B_diagToolAndSessionStatus.data[0] = 0x3A;
	DID_0x100B_diagToolAndSessionStatus.data[1] = 0x28;
	DID_0x100B_diagToolAndSessionStatus.data[2] = 0xAF;
	DID_0x100B_diagToolAndSessionStatus.data[3] = 0x58;

	DID_0x2010_programmingStatus.id = 0x2010;
	DID_0x2010_programmingStatus.dataLength = 3;
	DID_0x2010_programmingStatus.data[0] = 0x1B;
	DID_0x2010_programmingStatus.data[1] = 0x3C;
	DID_0x2010_programmingStatus.data[2] = 0x70;

	DID_0x201A_appSoftwareReprogrammingAttemptCounter.id = 0x201A;
	DID_0x201A_appSoftwareReprogrammingAttemptCounter.dataLength = 2;
	DID_0x201A_appSoftwareReprogrammingAttemptCounter.data[0] = 0xAB;
	DID_0x201A_appSoftwareReprogrammingAttemptCounter.data[1] = 0xCD;

	DID_0xF110_ecuDiagnosticIdentification.id = 0xF110;
	DID_0xF110_ecuDiagnosticIdentification.dataLength = 1;
	DID_0xF110_ecuDiagnosticIdentification.data[0] = 0xFF;

	DID_0xF1A2_vectorDeliveryID.id = 0xF1A2;
	DID_0xF1A2_vectorDeliveryID.dataLength = 3;
	DID_0xF1A2_vectorDeliveryID.data[0] = 0x98;
	DID_0xF1A2_vectorDeliveryID.data[1] = 0xA3;
	DID_0xF1A2_vectorDeliveryID.data[2] = 0x7F;

	DID_0xF1BD_ecuSignatureType.id = 0xF1BD;
	DID_0xF1BD_ecuSignatureType.dataLength = 4;
	DID_0xF1BD_ecuSignatureType.data[0] = 0x6C;
	DID_0xF1BD_ecuSignatureType.data[1] = 0x9D;
	DID_0xF1BD_ecuSignatureType.data[2] = 0xDC;
	DID_0xF1BD_ecuSignatureType.data[3] = 0x81;
}

Dcm_DID Dcm_Get_DID_0x100B_diagToolAndSessionStatus()
{
	return DID_0x100B_diagToolAndSessionStatus;
}

Dcm_DID Dcm_Get_DID_0x2010_programmingStatus()
{
	return DID_0x2010_programmingStatus;
}

Dcm_DID Dcm_Get_DID_0x201A_appSoftwareReprogrammingAttemptCounter()
{
	return DID_0x201A_appSoftwareReprogrammingAttemptCounter;
}

Dcm_DID Dcm_Get_DID_0xF110_ecuDiagnosticIdentification()
{
	return DID_0xF110_ecuDiagnosticIdentification;
}

Dcm_DID Dcm_Get_DID_0xF1A2_vectorDeliveryID()
{
	return DID_0xF1A2_vectorDeliveryID;
}

Dcm_DID Dcm_Get_DID_0xF1BD_ecuSignatureType()
{
	return DID_0xF1BD_ecuSignatureType;
}
