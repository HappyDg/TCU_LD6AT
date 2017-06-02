#include "Compiler.h"


extern uint8 Native_HCU_DTC_Block_RAMAddress[1024];
extern uint8 Native_DCDC_DTC_Block_RAMAddress[1024];
extern uint8 Native_Calib_Block_RamAddress[2048];
extern uint8 Native_AppReserved_Block1_RamAddress[64];
extern uint8 Native_AppReserved_Block2_RamAddress[64];
extern uint8 Native_AppReserved_Block3_RamAddress[128];
extern uint8 Native_AppReserved_Block4_RamAddress[128];
extern uint8 Native_AppReserved_Block5_RamAddress[512];
extern uint8 Native_AppReserved_Block6_RamAddress[1024];
extern uint8 Native_AppReserved_Block7_RamAddress[2048];
extern uint8 Dcm_NvData[128];

extern void EcuM_CB_NfyNvMJobEnd(uint8 ServiceId, NvM_RequestResultType CurrentJobMode);
