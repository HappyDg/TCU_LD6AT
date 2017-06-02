/******************************************************************************/
/*                                                                            */
/* !Layer           : Application                                             */
/*                                                                            */
/* !Module          : MAIN                                                    */
/* !Description     : Gateway BSW - Application                               */
/*                                                                            */
/* !File            : MAIN_TSK.C                                              */
/*                                                                            */
/* !Target          : All                                                     */
/*                                                                            */
/* !Vendor          : Valeo                                                   */
/*                                                                            */
/* Coding language  : C                                                       */
/*                                                                            */
/* COPYRIGHT 2014 VALEO                                                       */
/* all rights reserved                                                        */
/*                                                                            */
/******************************************************************************/
/* 1.1  / MAIN_core0_main                                                     */
/* 1.2  / MAIN_Wait                                                           */
/******************************************************************************/
/* PVCS Information                                                           */
/* $Archive::                                                                $*/
/* $Revision::             $$Author::                 $$Date::               $*/
/******************************************************************************/
/* Dimension Informations
 * %PCMS_HEADER_SUBSTITUTION_START:%
 * The PID has this format: <Product ID>:<Item ID>.<Variant>-<Item Type>;<Revision>
 * %PID:%
 * %PCMS_HEADER_SUBSTITUTION_END:%
 ******************************************************************************/

#include "Std_Types.h"

#include "SWC_BSW_MAIN.h"
#include "SWC_BSW_MAIN_L.h"
#include "MAIN_Msg.h"
#include "bsw.h"
#include "MSG.h"
#include "bswsrv.h"
#include "Com_SymbolicNames_PBcfg.h"

#include "MAIN_WriteCan.h"
//#include "MAIN_WriteDcdcApi.h"
#include "MAIN_WriteIohal.h"

#include "Gpt.h"
//#include "INTBSL.h"
//#include "os_drv_isr.h"
#include "Os_api.h"
#include "IfxScuWdt.h"
#include "MATHSRV.h"

#include "VADC_Cfg.h"
#include "VADC_L.h"
#include "MAIN.h"
#include "Dem.h"
#include "FiM.h"
#include "Nvm.h"
#include "Icu_17_GtmCcu6.h"
#include "TLE8242_wrapper.h"
#include "DIO_WrapAPI.h"
#include "RbBaseSw.h"
#include "Trim_8242_App.h"
/*Inlcude HCU header file*/
//#include "Subsystem.h"
//#include "HCU_Cal.h"

extern FUNC(uint8, COM_CODE) Com_ReceiveSignal
(
   uint16 SignalId,
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
);

extern FUNC(uint8, COM_CODE) Com_SendSignal
(
   uint16 SignalId,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
);

/* include DCDC Model's header file */
//#include "SWC_MCU.h"

/******************************************************************************/
/* DEFINES                                                                    */
/******************************************************************************/
/* START_SECTION_CODE */
#define _user_write(Signal)            Write_ ## Signal(Signal)
#define _user_read(Signal)             Read_ ## Signal(Signal)

/******************************************************************************/

/******************************************************************************/

//#define NULL 0


/******************************************************************************/
/* DATA DECLARATION                                                           */
/******************************************************************************/
#pragma section ".inttab.osinterrupts" a
extern const uint32 const Os_InterruptVectorTable[];
#pragma section

//Delete the data definition if delivery

boolean ACCUMULATOR_SOLENOID_DRIVE;
boolean MCU_TORQUE_ENABLE_OUTPUT_DRIVE;
boolean PWR_LATCH;

uint8 CntrlCmdApmDirReq;
boolean CntrlCmdApmPrechReq;
uint8 CntrlCmdApmImaxReq;
float CntrlCmdApmUregReq;
float CntrlCmdApmUprechReq;
boolean CntrlCmdApmCanComStat;

/*TCU Tx global set*/
float   EngNIdleReq;
float   EngTqIndDecReqdByTrsm;
float   EngTqIndLmtdByTrsm;
uint8   TrsmCluStAct;
uint8   TrsmMsgCnt;
uint16  TrsmNInp;
float   EngTqIndIncReqdByTrsm;
uint8   TrsmFlgFlt;
boolean TrsmFlgShiftProgs;
uint8   TrsmGearAct;
uint8   TrsmGearTar;
boolean TrsmMILReq;
uint8   TrsmStGearLvr;
uint8   TrsmStGearMode;
float   TrsmTOil;
boolean TrsmTOilWrnLmpReq;


/*TCU Tx global set*/
extern float   EngNIdleReq;
extern float   EngTqIndDecReqdByTrsm;
extern float   EngTqIndLmtdByTrsm;
extern uint8   TrsmCluStAct;
extern uint8   TrsmMsgCnt;
extern uint16  TrsmNInp;
extern float   EngTqIndIncReqdByTrsm;
extern uint8   TrsmFlgFlt;
extern boolean TrsmFlgShiftProgs;
extern uint8   TrsmGearAct;
extern uint8   TrsmGearTar;
extern boolean TrsmMILReq;
extern uint8   TrsmStGearLvr;
extern uint8   TrsmStGearMode;
extern float   TrsmTOil;
extern boolean TrsmTOilWrnLmpReq;

//IOHAL API global variables
extern boolean ACCUMULATOR_SOLENOID_DRIVE;
extern boolean MCU_TORQUE_ENABLE_OUTPUT_DRIVE;
extern boolean PWR_LATCH;
//DCDC API global variables
extern uint8 CntrlCmdApmDirReq;
extern boolean CntrlCmdApmPrechReq;
extern uint8 CntrlCmdApmImaxReq;
extern float CntrlCmdApmUregReq;
extern float CntrlCmdApmUprechReq;
extern boolean CntrlCmdApmCanComStat;

/******************************************************************************/
/* DATA DEFINITION                                                            */
/******************************************************************************/
#define  MAIN_START_SEC_VAR_UNSPECIFIED
#include "MAIN_MemMap.h"

Os_StackValueType  Os_StackValue;
#define  MAIN_STOP_SEC_VAR_UNSPECIFIED
#include "MAIN_MemMap.h"

#pragma section

/******************************************************************************/
/* FUNCTIONS DECLARATION                                                      */
/******************************************************************************/

#define  MAIN_START_SEC_CODE
#include "MAIN_MemMap.h"

void MAIN_core0_main (void);
void MAIN_Wait(uint32 time);

#define  MAIN_STOP_SEC_CODE
#include "MAIN_MemMap.h"

/******************************************************************************/
/* GLOBAL FUNCTION DEFINITION                                                 */
/******************************************************************************/

#define MAIN_START_SEC_CODE
#include "MAIN_MemMap.h"


/*********************************************** <AUTO_FUNCTION_HEADER> ***********************************************/
/*                                                                                                                    */
/* !FuncName    : ISR_GRP_0_END_OF_CONV                                                                               */
/*                                                                                                                    */
/* !Description : Interrupt trigged by the last element of queue of group 0                                           */
/* !Number      : 2                                                                                                   */
/* !Reference   : NONE                                                                                                */
/*                                                                                                                    */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/********************************************** </AUTO_FUNCTION_HEADER> ***********************************************/
/* !Trigger  : isr                                                                                                    */
/*                                                                                                                    */
/* !LastAuthor  :  E. Moas                                                                                            */
/********************************************* <AUTO_FUNCTION_PROTOTYPE> **********************************************/
CAT1_ISR(ISR_GRP_0_END_OF_CONV)
{
   uint32       u32LocTimeStamp;


   u32LocTimeStamp          = VADC_u32GET_TIMEOUT_START();
   VADC_au32IsrPeriod[0]    = u32LocTimeStamp - VADC_au32IsrTimeStamp[0];
   VADC_au32IsrTimeStamp[0] = u32LocTimeStamp;

   //VADC_au16ConvRes[VADC_u8ANA_P14_RES_IDX] = VADC_u16GET_VALUE(ANA_P14);
   //VADC_au16ConvRes[VADC_u8ANA_P48_RES_IDX]  = VADC_u16GET_VALUE(ANA_P48);

   //VADC_au16ConvRes[VADC_u8ANA_P14_2_RES_IDX] = VADC_u16GET_VALUE(ANA_P14_2);
   //VADC_au16ConvRes[VADC_u8ANA_P48_2_RES_IDX]  = VADC_u16GET_VALUE(ANA_P48_2);

   //MAIN_vidAdcCallBackGroup1();

   //For test DCDC function and IO

   //Test end

   //MCU_400usCall();
   //MCU_200usCall();

   //IOHAL_vidWriteUdt_PWM_FRQ_DCDC_ISETD(100);
   //IOHAL_vidWriteUdt_PWM_DUTY_DCDC_ISETD(CSDCS_CurRefDutyCycToTi);
   //IOHAL_vidWriteUdt_PWM_DUTY_DCDC_ISETD(5000);
   //IOHAL_vidWriteUdt_PWM_ENA_DCDC_ISETD(1);

   EVP_au16Dur[EVP_u8GRP_0_IDX] = (uint16)(VADC_u32GET_TIMEOUT_START() - u32LocTimeStamp);
}


/******************************************************************************/
/*                                                                            */
/* !Runnable    : MAIN_core0_main                                             */
/* !Trigger     : Reset                                                       */
/* !Description : Main function of Core 0                                     */
/* !Number      : 1                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void MAIN_core0_main(void)
{
   __disable();

   StartOS(OSDEFAULTAPPMODE);

   while (1)
   {
   }
}

/******************************************************************************/
/*                                                                            */
/* !Runnable    : MAIN_core1_main                                             */
/* !Trigger     :                                                             */
/* !Description : Main function of Core 1                                     */
/* !Number      : 1                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : A. Elkhazragy                                               */
/******************************************************************************/
void MAIN_core2_main(void)
{
   while (1)
   {
   }
}

/******************************************************************************/
/*                                                                            */
/* !Runnable    : StartupHook_MAIN_OSAPP                                      */
/* !Trigger     : Reset                                                       */
/* !Description : Main function of Core 1                                     */
/* !Number      : 1                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void StartupHook_MAIN_OSAPP(void)
{
  // TST_WDG_vidInit();
  // TST_GPT_vidInit();
  // TST_DET_vidInit();
  // TST_PWD_vidInit();
 //  TST_PWM_vidInit();
  // TST_ADC_vidInit();
   //SWTST_vidTle6220Init();
   //TST_SPI_vidInit();
 //  SWTST_vidEVPInit();
 //  SWTST_vidDioInit();
 //  TST_CANAPI_vidInit();
   //TST_DCDCAPI_vidInit();
   //chyg just for test; should deleted for release;
 //  Fls_17_Pmu_Test_Init();
 //  TST_DEM_vidInit();

   MAIN_s8TestVar1 = 0;
   MAIN_s8TestVar2 = 0;
   MAIN_s8TestVar3 = 0;
   MAIN_s8TestVar4 = 0;
   MAIN_u8TestVar1 = 4;
   MAIN_u8TestVar2 = 0;
   MAIN_u8TestVar3 = 0;
   MAIN_u8TestVar4 = 0;
   MAIN_s16TestVar1 = 0;
   MAIN_s16TestVar2 = 0;
   MAIN_s16TestVar3 = 0;
   MAIN_s16TestVar4 = 0;
   MAIN_u16TestVar1 = 0;
   MAIN_u16TestVar2 = 0;
   MAIN_u16TestVar3 = 0;
   MAIN_u16TestVar4 = 0;
   MAIN_s32TestVar1 = 0;
   MAIN_s32TestVar2 = 0;
   MAIN_s32TestVar3 = 0;
   MAIN_s32TestVar4 = 0;
   MAIN_u32TestVar1 = 0;
   MAIN_u32TestVar2 = 0;
   MAIN_u32TestVar3 = 0;
   MAIN_u32TestVar4 = 0;
   MAIN_u32TskCtr1000ms = 0;
   MAIN_u32TskCtr100ms = 0;
   MAIN_u32TskCtr10ms = 0;
   MAIN_u32TskCtr1ms = 0;
   MAIN_u32TskCtr200ms = 0;
   MAIN_u32TskCtr20ms = 0;
   MAIN_u32TskCtr2ms = 0;
   MAIN_u32TskCtr50ms = 0;
   MAIN_u32TskCtr5ms = 0;
   

   ShrExp_Clear_SbrmStatus();

   /* SWC_XX - Initialize model */
   //SWC_MCU_initialize();

}

void StartupHook(void)
{
}

void PostTaskHook(void)
{
}
void PreTaskHook(void)
{
}
void ShutdownHook_MAIN_OSAPP(StatusType Error)
{
}
void ShutdownHook(StatusType Error)
{
}

Os_StopwatchTickType Os_Cbk_GetStopwatch(void)
{
   return(0);
}

/******************************************************************************/
/*                                                                            */
/* !Runnable    : MAIN_Wait function                                          */
/* !Trigger     : Main Function                                               */
/* !Description : Wait function                                               */
/* !Number      : 2                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void MAIN_Wait(uint32 time)
{
   volatile uint32 localu32Counter;

   localu32Counter = time;
   while(localu32Counter > 0)
   {
      localu32Counter--;
   }  
}

/******************************************************************************/
/*                                                                            */
/* !Task        : TASK_INIT                                                   */
/* !Trigger     : Init                                                        */
/* !Description : This task is launched at the init of the OS                 */
/* !Number      : 3                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
TASK(TASK_INIT)
{

   MAIN_MSGvidInit();
   BSW_vidEnable();
   //IOHAL_vidWriteUdt_PWM_FRQ_DCDC_ISETD(100);
   //IOHAL_vidWriteUdt_PWM_DUTY_DCDC_ISETD(0);
   //IOHAL_vidWriteUdt_PWM_ENA_DCDC_ISETD(1);

   MAIN_u32StackPreValue = 0x60019A00;	
   (void)TerminateTask();
}

/******************************************************************************/
/*                                                                            */
/* !Task        : TASK_TIME_1MS                                               */
/* !Trigger     : Time (1ms)                                                  */
/* !Description : This task has a 1ms period                                  */
/* !Number      : 4                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
TASK(TASK_TIME_1MS)
{
   BSW_1msPreCall();
   MAIN_u32TskCtr1ms=MAIN_u32TskCtr1ms+1;

   Os_StackValue = Os_GetStackValue();
   MAIN_u32StackCurValue = Os_StackValue.sp;
   if(MAIN_u32StackCurValue < MAIN_u32StackPreValue)
   {
	   MAIN_u32StackPreValue = MAIN_u32StackCurValue;
   }

   /*
    * SWC_XX - Set function inputs here:
    */


   /*
    * SWC_XX - Call to function
    */

  /* !Comment: DCDC */
   //MCU_1msCall();
   //IOHAL_vidWriteUdt_CUT_SAFETY(CSACS_SftyMOSCmd);
   //IOHAL_vidWriteUdt_CMD_PRE(CSACS_PrecCmd);

   /*
    * SWC_XX - Read function outputs here
    */

   BSW_1msPostCall();
   (void)TerminateTask();
}

/******************************************************************************/
/*                                                                            */
/* !Task        : TASK_TIME_2MS                                               */
/* !Trigger     : Time (2ms)                                                  */
/* !Description : This task has a 2ms period                                  */
/* !Number      : 5                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
TASK(TASK_TIME_2MS)
{
   BSW_2msPreCall();
   MAIN_u32TskCtr2ms=MAIN_u32TskCtr2ms+1;

   Os_StackValue = Os_GetStackValue();
   MAIN_u32StackCurValue = Os_StackValue.sp;
   if(MAIN_u32StackCurValue < MAIN_u32StackPreValue)
   {
	   MAIN_u32StackPreValue = MAIN_u32StackCurValue;
   }

   //MCU_2msCall();
   //IOHAL_vidWriteUdt_DCDC_UVLO(CSLCS_TiUVLO);
   //IOHAL_vidWriteUdt_NFAULT_O(CSLCS_TinFaultOut);
   //IOHAL_vidWriteUdt_DCDC_EN(CSLCS_TiEn);
   //IOHAL_vidWriteUdt_DCDC_DIR(CSLCS_TiDir);

   BSW_2msPostCall();
   (void)TerminateTask();
}

/******************************************************************************/
/*                                                                            */
/* !Task        : TASK_TIME_5MS                                               */
/* !Trigger     : Time (5ms)                                                  */
/* !Description : This task has a 5ms period                                  */
/* !Number      : 7                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : A. Elkhazragy                                               */
/******************************************************************************/
TASK(TASK_TIME_5MS)
{
   BSW_5msPreCall();
   MAIN_u32TskCtr5ms=MAIN_u32TskCtr5ms+1;

   Os_StackValue = Os_GetStackValue();
   MAIN_u32StackCurValue = Os_StackValue.sp;
   if(MAIN_u32StackCurValue < MAIN_u32StackPreValue)
   {
	   MAIN_u32StackPreValue = MAIN_u32StackCurValue;
   }
   #if 0
    if(MAIN_s8TestVar2 == 5)
	{
		ShrExp_Set_Solenoid(TST_u8TLE8242CHIndex, TST_u8TLE8242_OpenLoopC, (uint16)TST_f32TLE8242_Target, (uint16)TST_f32TLE8242_DitherAmpl, (uint16)TST_f32TLE8242_DitherFreq);
	}
	else
	{
		TST_TLE8242_vidMainFunction();
	}
	#endif
   //MCU_5msCall();
   //CANAPI_u8Write_DCDC_FAULT_STATUS(DDDSM_FaultStatus);
   //CANAPI_u8Write_DCDC_CURRENT_STATUS(DDDSM_CurrentStatus);
   //CANAPI_u8Write_DCDC_VOLTAGE_STATUS(DDDSM_VoltageStatus);
   //CANAPI_u16Write_DCDC_FAULT(DDDSM_Fault);

   BSW_5msPostCall();
   (void)TerminateTask();
}

/******************************************************************************/
/*                                                                            */
/* !Task        : TASK_TIME_10MS                                              */
/* !Trigger     : Time (10ms)                                                 */
/* !Description : This task has a 10ms period                                 */
/* !Number      : 8                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : A. Elkhazragy                                               */
/******************************************************************************/
TASK(TASK_TIME_10MS)
{
   BSW_10msPreCall();
   MAIN_u32TskCtr10ms=MAIN_u32TskCtr10ms+1;

   Trim_InitGainAndOffset();
   Trim_Feedback_InitGainAndOffset();
    MAIN_MSGvidRx_Tsk10ms();

   /*
    * SWC_XX - Set function inputs here:
    */


   /*
    * SWC_XX - Call to function
    */
/*	Task_PMDRPowerModeRunnable();
	Task_CDPR12VltgStatus();
	Task_CDPR12VltgValFlt();
	Task_CDPREngSpdValFlt();
	Task_CDPROutdAirTemp();
	Task_CDPRVehSpdValFlt();
    Task_MCCRDtrmn48VCnnctn();
	Task_MEMRCntrlJumpStart();
	Task_MEMRDCPowerConversion();
	Task_MEMRPowerLimits();
	Task_MICRcontrolBSGSpeed();
	Task_MICRdetermineBSGCntrlMode();
	Task_MICRdetermineBSGTorqueRequest();
	Task_MICRmonitorBSGStatusData();
	Task_MKCRDetemnProplsnSystmActvRunnable();
	Task_MDPRTT();
	Task_MDPRINFO();
*/
	/*Ricardo defined task*/ //jiang yintian
//	Task_HWIO();
//  	Task_APMR();
//	Task_CANR();
//	Task_DGMR();
//	Task_OSTM();
//	Task_HCUAPP();


   //Write after HCU change the global variables. The HCU task should be before this line.

   //Main_vidCAN_SngSetVle();
   //Main_vidDCDCAPI_SngSetVle();
/* !Comment: DCDC */
   //MCU_10msCall();
   //CANAPI_u8Write_DCDC_U14(ASLVD_DCDCULVtoCAN);
   //CANAPI_u16Write_DCDC_UHV(ASLVD_DCDCUHVtoCAN);
   //CANAPI_u16Write_DCDC_IHV(ASDPM_DCDCIHVtoCAN);
   //CANAPI_u16Write_DCDC_I14(ASDPM_DCDCILVtoCAN);
   //CANAPI_u8Write_DCDC_PRECH_STATUS(SMFSM_DCDCPrecSts);
   //CANAPI_u8Write_DCDC_MODE(SMFSM_DCDCOperateMode);
/* !Comment: DCDC END */
   /*
    * SWC_XX - Read function outputs here
    */
   //Main_vidIOHAL_SngSetVle();
  
   MAIN_MSGvidTx_Tsk10ms();
   BSW_10msPostCall();
   (void)TerminateTask();
}

/******************************************************************************/
/*                                                                            */
/* !Task        : TASK_TIME_20MS                                              */
/* !Trigger     : Time (20ms)                                                 */
/* !Description : This task has a 20ms period                                 */
/* !Number      : 9                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
TASK(TASK_TIME_20MS)
{
   BSW_20msPreCall();
   MAIN_u32TskCtr20ms=MAIN_u32TskCtr20ms+1;

   MAIN_MSGvidRx_Tsk20ms();

   /*
    * SWC_XX - Set function inputs here:
    */


   /*
    * SWC_XX - Call to function
    */


   /*
    * SWC_XX - Read function outputs here
    */


   MAIN_MSGvidTx_Tsk20ms();
   BSW_20msPostCall();
   (void)TerminateTask();
}

/******************************************************************************/
/*                                                                            */
/* !Task        : TASK_TIME_50MS                                              */
/* !Trigger     : Time (50ms)                                                 */
/* !Description : This task has a 50ms period                                 */
/* !Number      : 11                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : A. Elkhazragy                                               */
/******************************************************************************/
TASK(TASK_TIME_50MS)
{
   BSW_50msPreCall();
   MAIN_u32TskCtr50ms=MAIN_u32TskCtr50ms+1;

     MAIN_MSGvidRx_Tsk50ms();

   /*
    * SWC_XX - Set function inputs here:
    */


   /*
    * SWC_XX - Call to function
    */

   /*
    * SWC_XX - Read function outputs here
    */
    uint8 temp;
   
    ShrExp_Get_Switch(0,&temp);
   
   MAIN_MSGvidTx_Tsk50ms();
   Wdg_vidRefreshWatchdog();
   BSW_50msPostCall();
   (void)TerminateTask();
}

/******************************************************************************/
/*                                                                            */
/* !Task        : TASK_TIME_100MS                                             */
/* !Trigger     : Time (100ms)                                                */
/* !Description : This task has a 100ms period                                */
/* !Number      : 12                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
TASK(TASK_TIME_100MS)
{
   BSW_100msPreCall();
   MAIN_u32TskCtr100ms=MAIN_u32TskCtr100ms+1;

    MAIN_MSGvidRx_Tsk100ms();


   /*
    * SWC_XX - Set function inputs here:
    */


   /*
    * SWC_XX - Call to function
    */
/* !Comment:DCDC */
   //MCU_100msCall();
   //CANAPI_u8Write_DCDC_TEMP(ASBTD_DCDCTemptoCAN);
/* !Comment: DCDC END */

   /*
    * SWC_XX - Read function outputs here
    */


   MAIN_MSGvidTx_Tsk100ms();
   BSW_100msPostCall();
   (void)TerminateTask();
}

/******************************************************************************/
/*                                                                            */
/* !Task        : TASK_TIME_200MS                                             */
/* !Trigger     : Time (200ms)                                                */
/* !Description : This task has a 200ms period                                */
/* !Number      : 13                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : A. Elkhazragy                                               */
/******************************************************************************/
TASK(TASK_TIME_200MS)
{
   BSW_200msPreCall();
   MAIN_u32TskCtr200ms=MAIN_u32TskCtr200ms+1;

   MAIN_MSGvidRx_Tsk200ms();

   /*
    * SWC_XX - Set function inputs here:
    */


   /*
    * SWC_XX - Call to function
    */


   /*
    * SWC_XX - Read function outputs here
    */


   MAIN_MSGvidTx_Tsk200ms();
   BSW_200msPostCall();
   (void)TerminateTask();
}

/******************************************************************************/
/*                                                                            */
/* !Task        : TASK_TIME_1000MS                                            */
/* !Trigger     : Time (1000ms)                                               */
/* !Description : This task has a 1000ms period                               */
/* !Number      : 15                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
TASK(TASK_TIME_1000MS)
{
   BSW_1000msPreCall();
   MAIN_u32TskCtr1000ms=MAIN_u32TskCtr1000ms+1;
   MAIN_s32TestVar1++;

   MAIN_MSGvidRx_Tsk1000ms();
      

   /*
    * SWC_XX - Set function inputs here:
    */


   /*
    * SWC_XX - Call to function
    */


   /*
    * SWC_XX - Read function outputs here
    */


   MAIN_MSGvidTx_Tsk1000ms();
   BSW_1000msPostCall();
   (void)TerminateTask();
}

/******************************************************************************/
/*                                                                            */
/* !Task        : TASK_POWER_UP                                               */
/* !Trigger     :                                                             */
/* !Description :                                                             */
/* !Number      : 17                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
TASK(TASK_POWER_UP)
{

   BSW_PowerUp();
   (void)TerminateTask();
}

/******************************************************************************/
/*                                                                            */
/* !Task        : TASK_POWER_DOWN                                             */
/* !Trigger     :                                                             */
/* !Description :                                                             */
/* !Number      : 18                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
TASK(TASK_POWER_DOWN)
{
   /* Make WriteAll operation */
   Wdg_vidRefreshWatchdog();
   BSW_PowerDown();
   (void)TerminateTask();
}

/******************************************************************************/
/*                                                                            */
/* !Task        : TASK_WATCHDOG                                               */
/* !Trigger     :                                                             */
/* !Description :                                                             */
/* !Number      : 19                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
TASK(TASK_WATCHDOG)
{
   boolean Loc_bWdgSts;


   //Loc_bWdgSts = IOHAL_udtRead_M_SUPPLY_WDI();
   //IOHAL_vidWriteUdt_M_SUPPLY_WDI((!Loc_bWdgSts));
//<<   WdgHALTrigger();
  (void)TerminateTask();
}

/******************************************************************************/
/*                                                                            */
/* !Task        : TASK_WATCHDOG                                               */
/* !Trigger     :                                                             */
/* !Description :                                                             */
/* !Number      : 19                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
TASK(OSTSK_S_WTDG_REFRESH_WATCHDOG)
{
//<<   WdgHALTrigger();
  (void)TerminateTask();
}

/******************************************************************************/
/* !FuncName    : INT(TSKSRV_ACTIVATION_MANAGER_IT)                           */
/* !Description : TSKSRV Software ISR2 in which tasks are activated           */
/*                                                                            */
/* !Trace_To    : VEES_R_12_00698_009                                         */
/* !Trace_To    : VEES_R_12_00698_010                                         */
/*                                                                            */
/* !LastAuthor  :  L. Baglin                                                  */
/******************************************************************************/
ISR(TSKSRV_ACTIVATION_MANAGER_IT)
{
}

/******************************************************************************/
/* !FuncName    : INT(TSKSRV_ACTIVATION_MANAGER_IT)                           */
/* !Description : TSKSRV Software ISR2 in which tasks are activated           */
/*                                                                            */
/* !Trace_To    : VEES_R_12_00698_009                                         */
/* !Trace_To    : VEES_R_12_00698_010                                         */
/*                                                                            */
/* !LastAuthor  :  L. Baglin                                                  */
/******************************************************************************/
void MAIN_vidAdcCallBackGroup1(void)
{
   /*
    * Set function inputs here:
    */



   /*
    * Call to function
    */


   /*
    * Read function outputs here
    */

}

/******************************************************************************/
/* !FuncName    : INT(TSKSRV_ACTIVATION_MANAGER_IT)                           */
/* !Description : TSKSRV Software ISR2 in which tasks are activated           */
/*                                                                            */
/* !Trace_To    : VEES_R_12_00698_009                                         */
/* !Trace_To    : VEES_R_12_00698_010                                         */
/*                                                                            */
/* !LastAuthor  :  L. Baglin                                                  */
/******************************************************************************/
void MAIN_vidAdcCallBackGroup2(void)
{
   /*
    * Set function inputs here:
    */


   /*
    * Call to function
    */


   /*
    * Read function outputs here
    */

}
/******************************************************************************/
/* !FuncName    : INT(TSKSRV_ACTIVATION_MANAGER_IT)                           */
/* !Description : TSKSRV Software ISR2 in which tasks are activated           */
/*                                                                            */
/* !Trace_To    : VEES_R_12_00698_009                                         */
/* !Trace_To    : VEES_R_12_00698_010                                         */
/*                                                                            */
/* !LastAuthor  :  L. Baglin                                                  */
/******************************************************************************/
void MAIN_vidAdcCallBackGroup3(void)
{
   /*
    * Set function inputs here:
    */


   /*
    * Call to function
    */


   /*
    * Read function outputs here
    */

}

/******************************************************************************/
/* !FuncName    : INT(TSKSRV_ACTIVATION_MANAGER_IT)                           */
/* !Description : TSKSRV Software ISR2 in which tasks are activated           */
/*                                                                            */
/* !Trace_To    : VEES_R_12_00698_009                                         */
/* !Trace_To    : VEES_R_12_00698_010                                         */
/*                                                                            */
/* !LastAuthor  :  L. Baglin                                                  */
/******************************************************************************/
void MAIN_vidAdcCallBackGroup4(void)
{
   /*
    * Set function inputs here:
    */


   /*
    * Call to function
    */


   /*
    * Read function outputs here
    */

}
/******************************************************************************/
void MAIN_vidTestApiIOHAL(void)
{

   Os_Entry_SRC_CAN_CAN0_INT6_ISR();
   Os_Entry_SRC_CAN_CAN0_INT5_ISR();
   Os_Entry_SRC_CAN_CAN0_INT0_ISR();
   Os_Entry_SRC_CAN_CAN0_INT4_ISR();
   Os_Entry_SRC_CAN_CAN0_INT7_ISR();
   Os_Entry_SRC_CAN_CAN0_INT1_ISR();
   Os_Entry_SRC_CAN_CAN0_INT8_ISR();
   Os_Entry_SRC_CAN_CAN0_INT3_ISR();
   Os_Entry_SRC_CAN_CAN0_INT2_ISR();
   Os_Entry_DMA_ISR_QSPI3RX();
   Os_Entry_DMA_ISR_QSPI3TX();
   Os_Entry_SRC_QSPI_QSPI3_ERR_ISR();
   Os_Entry_SRC_QSPI_QSPI3_PT_ISR();
   Os_Entry_SRC_QSPI_QSPI3_U_ISR();
   Os_Entry_DMA_ISR_QSPI2RX();
   Os_Entry_DMA_ISR_QSPI2TX();
   Os_Entry_SRC_QSPI_QSPI2_ERR_ISR();
   Os_Entry_SRC_QSPI_QSPI2_PT_ISR();
   Os_Entry_SRC_QSPI_QSPI2_U_ISR();
   Os_Entry_TSKSRV_ACTIVATION_MANAGER_IT();
   DisableAllInterrupts();
   EnableAllInterrupts();
   //Os_Cbk_StartCore(0);
   SRC_GTM_GTM0_TIM0_3_ISR();
   SRC_GTM_GTM0_TOM0_7_ISR();
   ISR_GRP_0_END_OF_CONV();
}

/******************************************************************************/
/* UDS Callback functions (Boot loader)                                       */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/* !Runnable    : Main_bDCMCbkJumpBLCondOk function                           */
/* !Trigger     : Callback COM                                                */
/* !Description : Callback of UDS $10 service (diagnostic session control)    */
/*              : To check condition before jump to boot loader               */
/* !Number      : MAIN.DCM.1                                                  */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M. Bras-Rabiller                                            */
/******************************************************************************/
boolean Main_bDCMCbkJumpBLCondOk(void)
{
   boolean bLocalProgCondOk;

   /* ... */
   bLocalProgCondOk = 1;

   return(bLocalProgCondOk);
}

/******************************************************************************/
/*                                                                            */
/* !Runnable    : Main_vidDCMCbkComTxInh function                             */
/* !Trigger     : Callback COM                                                */
/* !Description : Callback of UDS $28 service (communication control)         */
/*              : To deactivate COM CAN vehicle transmission                  */
/* !Number      : MAIN.DCM.2                                                  */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M. Bras-Rabiller                                            */
/******************************************************************************/
void Main_vidDCMCbkComTxInh(void)
{
   /* ... */
}

/******************************************************************************/
/*                                                                            */
/* !Runnable    : Main_vidDCMCbkComTxUnInh function                           */
/* !Trigger     : Callback COM                                                */
/* !Description : Callback of UDS $28 service (communication control)         */
/*              : To Reactivate COM CAN vehicle transmission                  */
/* !Number      : MAIN.DCM.3                                                  */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M. Bras-Rabiller                                            */
/******************************************************************************/
void Main_vidDCMCbkComTxUnInh(void)
{
   /* ... */
}

/******************************************************************************/
/*                                                                            */
/* !Runnable    : Main_vidDCMCbkComRxInh function                             */
/* !Trigger     : Callback COM                                                */
/* !Description : Callback of UDS $28 service (communication control)         */
/*              : To deactivate COM CAN vehicle reception                     */
/* !Number      : MAIN.DCM.4                                                  */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M. Bras-Rabiller                                            */
/******************************************************************************/
void Main_vidDCMCbkComRxInh(void)
{
   /* ... */
}

/******************************************************************************/
/*                                                                            */
/* !Runnable    : Main_vidDCMCbkComRxUnInh function                           */
/* !Trigger     : Callback COM                                                */
/* !Description : Callback of UDS $28 service (communication control)         */
/*              : To Reactivate COM CAN vehicle reception                     */
/* !Number      : MAIN.DCM.5                                                  */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M. Bras-Rabiller                                            */
/******************************************************************************/
void Main_vidDCMCbkComRxUnInh(void)
{
   /* ... */
}

/******************************************************************************/
/*                                                                            */
/* !Runnable    : MAIN_vidGptNotification function                            */
/* !Trigger     :  GPT timer trigger by ATOM0_0                               */
/* !Description :  GPT timer with 50us period                                 */
/*                                                                            */
/* !Number      :                                                             */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : liping. Liu                                            */
/******************************************************************************/
void MAIN_vidGptNotification(void)
{
   uint32       u32LocTimeStamp;


   u32LocTimeStamp          = ((uint32)MODULE_STM0.TIM0.U);
   MAIN_au32GptIsrPeriod    = u32LocTimeStamp - MAIN_au32GptIsrTimeStamp;
   MAIN_au32GptIsrTimeStamp = u32LocTimeStamp;
}

#define MAIN_STOP_SEC_CODE
#include "MAIN_MemMap.h"

/*-------------------------------- end of file -------------------------------*/
