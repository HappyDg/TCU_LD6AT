#include "Compiler.h"
#include "NvM_Types.h"
#include "NvM.h"

uint8 Native_HCU_DTC_Block_RAMAddress[1024];
uint8 Native_DCDC_DTC_Block_RAMAddress[1024];
uint8 Native_Calib_Block_RamAddress[2048];
uint8 Native_AppReserved_Block1_RamAddress[64];
uint8 Native_AppReserved_Block2_RamAddress[64];
uint8 Native_AppReserved_Block3_RamAddress[128];
uint8 Native_AppReserved_Block4_RamAddress[128];
uint8 Native_AppReserved_Block5_RamAddress[512];
uint8 Native_AppReserved_Block6_RamAddress[1024];
uint8 Native_AppReserved_Block7_RamAddress[2048];
uint8 Dcm_NvData[128];


uint8 MultiJob_ErrorStatus;
uint8 All_ErrorCount = 0;
void EcuM_CB_NfyNvMJobEnd(uint8 ServiceId, NvM_RequestResultType CurrentJobMode)
{
	NvM_GetErrorStatus(0, &MultiJob_ErrorStatus);
	if(MultiJob_ErrorStatus == NVM_REQ_OK)
	{
		MultiJob_ErrorStatus = NVM_REQ_NOT_OK;
	}
	else
	{
		All_ErrorCount++;
	}
}


