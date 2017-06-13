/******************************************************************************/
/*                                                                            */
/* !Layer           : BSW                                                     */
/*                                                                            */
/* !Module          : BSW                                                     */
/* !Description     : BSW initialization                                      */
/*                                                                            */
/* !File            : BSWSRV.C                                                */
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
/* 1.1  / BSW_vidInit                                                         */
/******************************************************************************/
/* PVCS Information                                                           */
/* $Archive::                                                                $*/
/* $Revision::             $$Author::   ogarot        $$Date::               $*/
/******************************************************************************/
/* Dimension Informations
 * %PCMS_HEADER_SUBSTITUTION_START:%
 * The PID has this format: <Product ID>:<Item ID>.<Variant>-<Item Type>;<Revision>
 * %PID:%
 * %PCMS_HEADER_SUBSTITUTION_END:%
 ******************************************************************************/

#include "Std_Types.h"
#include "TLF35584.h"
#include "BSW.h"
#include "BSW_L.h"

#include "bswsrv.h"

#include "CCP.h"
#include "CCPUSR.h"

#include "Evp.h"
#include "Scu.h"
#include "Dio.h"
#include "EcuM.h"
#include "PWD.h"
#include "Pwm_17_Gtm.h"
#include "IOHAL.h"
#include "Ovc.h"
#include "Vadc.h"
#include "Os_api.h"
#include "Gpt.h"

#include "CanIf.h"
#include "CanTp.h"
#include "Com.h"
#include "ComStack_Init.h"
#include "Dcm.h"
#include "MSG.h"

#include "fls_17_pmu.h"
#include "Fee.h"
#include "NvM.h"

#include "Dem.h"
#include "FiM.h"
#include "subrom.h"
#include "TLE8242.h"
#include "DIO_WrapAPI.h"
#include "RbBaseSw.h"
/******************************************************************************/
/* DEFINES                                                                    */
/******************************************************************************/

//>>
#define MSB_32BITS_REGISTER_MASK       0x80000000
#define MSB_REGISTER_MASK              MSB_32BITS_REGISTER_MASK

//>>
#define KRN_u16SCHEDULER_PERIOD_250US  4000u // (1s / 250us)
#define KRN_u16SCHEDULER_PERIOD_500US  2000 // (1s / 500us)
#define KRN_u16SCHEDULER_PERIOD_1000US  1000 // (1s / 500us)

/*----------------------------------------------------------------------------*/
/* COM                                                                        */
/*----------------------------------------------------------------------------*/
#define BSW_BUSOFF_COUNTER_MAX         200U


/******************************************************************************/
/* DATA DEFINITION                                                            */
/******************************************************************************/
#define BSW_START_SEC_VAR_UNSPECIFIED
#include "BSW_MemMap.h"
uint16 KRN_u16SdlOvernCnt[3];
uint16 KRN_u16Sdl50msCnt[3];
uint32 KRN_u32CompareValue;
#define BSW_STOP_SEC_VAR_UNSPECIFIED
#include "BSW_MemMap.h"

/******************************************************************************/
/* FUNCTIONS DECLARATION                                                      */
/******************************************************************************/

#define BSW_START_SEC_CODE
#include "BSW_MemMap.h"

extern void BSW_vidSchedulerInit(void);

#define BSW_STOP_SEC_CODE
#include "BSW_MemMap.h"

/******************************************************************************/
/* GLOBAL FUNCTION DEFINITION                                                 */
/******************************************************************************/

#define BSW_START_SEC_CODE
#include "BSW_MemMap.h"

/******************************************************************************/
/* !FuncName    : BSW_vidSchedulerInit                                        */
/* !Description : Initialize the scheduler                                    */
/*                                                                            */
/* !LastAuthor  : L. Baglin                                                   */
/******************************************************************************/
void BSW_vidSchedulerInit(void)
{
   IfxStm_CompareConfig stmCompareConfig;


   /* Initialize STM for the triggers */
   KRN_u16SdlOvernCnt[0] = 0u;
   KRN_u16Sdl50msCnt[0] = 0u;
   KRN_u32CompareValue = IfxStm_getFrequency(&MODULE_STM0) / KRN_u16SCHEDULER_PERIOD_1000US;

   /* ena suspend by debugger */
   IfxStm_enableOcdsSuspend(&MODULE_STM0);
   /* ena suspend by debugger */

   /* Call the constructor of configuration */
   IfxStm_initCompareConfig(&stmCompareConfig);

   /* Modify only the number of ticks and enable the trigger output */
   stmCompareConfig.ticks = KRN_u32CompareValue;   /*Interrupt after KRN_u32CompareValue ticks from now */

   /* Now Compare functionality is initialized */
   IfxStm_initCompare(&MODULE_STM0, &stmCompareConfig);
   

}

/******************************************************************************/
/* !FuncName    : INT(BSW_SCHEDULER_MANAGE_IT)                                */
/* !Description : Scheduler Interrupt                                         */
/*                                                                            */
/* !LastAuthor  : L. Baglin                                                   */
/******************************************************************************/
ISR(MAIN_OSISR_P_PIM1ms)
{
   uint32 u32LocalNextDate;
   uint32 u32LocalDuration;


   u32LocalNextDate = (uint32)(IfxStm_getCompare(&MODULE_STM0, 0u) + KRN_u32CompareValue);

   IfxStm_updateCompare(&MODULE_STM0, 0u, u32LocalNextDate);

   (void)IncrementCounter(MAIN_OSCNT_PIM1ms);

   u32LocalDuration = (uint32)(IfxStm_getCompare(&MODULE_STM0, 0u) ) - IfxStm_getLower(&MODULE_STM0);

   if ( (u32LocalDuration & MSB_REGISTER_MASK) != 0u)
   {
      KRN_u16SdlOvernCnt[0]++;
      MODULE_SRC.STM.STM[0].SR0.B.SETR = 1;
   }

   if (KRN_u16Sdl50msCnt[0]++ >=  49)
   {
       KRN_u16Sdl50msCnt[0] = 0;
      (void)IncrementCounter(MAIN_OSCNT_PIM50ms);
   }
}


/******************************************************************************/
/*                                                                            */
/* !Runnable    : BSW_vidInit                                                 */
/* !Trigger     : Init                                                        */
/* !Description :                                                             */
/* !Number      : 1                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void BSW_vidInit(void)
{
   SWFAIL_vidInit();
   DEVHAL_vidInit();
   OVC_vidInit();
   TLF35584_vidInit(TLF35584_u8CHIP_STEP_B);
   TLE8242_vidInit();
   Dio_WrapAPI_Init();
   ShrExp_SubRom_Init();

   IOHAL_vidInit();
   PWD_vidInit();
   
   
   
   RTMTSK_vidTaskTimeMeasureInit();

   Fls_17_Pmu_Init(&Fls_17_Pmu_ConfigRoot[0]);
   
   //Dem_PreInit(DemConfigSet_0);
   
   Fee_Init();
   while(Fee_GetStatus() == MEMIF_BUSY_INTERNAL)
   {
	Fee_MainFunction();
	Fls_17_Pmu_MainFunction();
   }

   NvM_Init();
   BSW_vidSchedulerInit(); 
   //BSW_vidSchedulerInitCpu1();

/*----------------------------------------------------------------------------*/
/* Busoff Init                                                                */
/*----------------------------------------------------------------------------*/
   BSW_u8CAN0BusOffCounter = 0;
   BSW_u8CAN1BusOffCounter = 0;
   BSW_u8CAN2BusOffCounter = 0;
   BSW_bCAN0BusOff = 0;
   BSW_bCAN1BusOff = 0;
   BSW_bCAN2BusOff = 0;


/*----------------------------------------------------------------------------*/
   CCP_vidIni(NULL_PTR);
   SPY_vidInit();
   SCU_vidInit();
   VADC_vidInit();
   EVP_vidInit();

   BSW_COMStack_Initi();

   SubRom_Init();

   //DCDCAPI_vidInit();
   
   BSW_u16Var1 = 0;

/*----------------------------------------------------------------------------*/
/* System layer Init                                                          */
/*----------------------------------------------------------------------------*/  
   Dem_Init();
   Dem_SetOperationCycleState( DEM_OPCYC_POWER, DEM_CYCLE_STATE_START);
   
   FiM_Init(FiM_Config_0);

   //chyg just for test; should deleted for release;
   //Fls_17_Pmu_Test_Init();
}

/******************************************************************************/
/*                                                                            */
/* !Task        : BSW_vidEnable                                               */
/* !Trigger     : Init                                                        */
/* !Description : This function is launched at the init of the OS             */
/* !Number      : 2                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void BSW_vidEnable(void)
{
   VADC_vidEna();
   Os_Enable_SRC_GTM_GTM0_TOM0_7_ISR();               //start the micro level INT
   Gpt_StartTimer(GptConf_GptChannel_GPT_0,5000);     //start counter with 50us peroid 
   Gpt_EnableNotification(GptConf_GptChannel_GPT_0); //start the GPT level INT
}

/******************************************************************************/
/*                                                                            */
/* !Task        : BSW_1msPreCall                                              */
/* !Trigger     : TASK_TIME_1MS                                               */
/* !Description :                                                             */
/* !Number      : 10                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void BSW_1msPreCall(void)
{
   BSW_u32FrtTM1msGlbCnt=BSW_u32FrtTM1msGlbCnt+1;
   
}

/******************************************************************************/
/*                                                                            */
/* !Task        : BSW_1msPostCall                                             */
/* !Trigger     : TASK_TIME_1MS                                               */
/* !Description :                                                             */
/* !Number      : 11                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void BSW_1msPostCall(void)
{
   CCP_vidDaqListSetEvent(CCP_u8DAQ_EVT_EVENT_FAST);
   if (BSW_bSPYBenchOnC != 0)
   {
      SPY_vidWrBuf();
      if (BSW_u8TestVar1 != 0)
      {
         SPY_vidStopDataAcq();
         BSW_u8TestVar1 = 0;
      }
   }

   

}

/******************************************************************************/
/*                                                                            */
/* !Task        : BSW_2msPreCall                                              */
/* !Trigger     : TASK_TIME_2MS                                               */
/* !Description :                                                             */
/* !Number      : 12                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void BSW_2msPreCall(void)
{
   PWD_vidActivationManager();
}

/******************************************************************************/
/*                                                                            */
/* !Task        : BSW_2msPostCall                                             */
/* !Trigger     : TASK_TIME_2MS                                               */
/* !Description :                                                             */
/* !Number      : 13                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void BSW_2msPostCall(void)
{
}

/******************************************************************************/
/*                                                                            */
/* !Task        : BSW_5msPreCall                                              */
/* !Trigger     : TASK_TIME_5MS                                               */
/* !Description :                                                             */
/* !Number      : 14                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void BSW_4msPreCall(void)
{
}

/******************************************************************************/
/*                                                                            */
/* !Task        : BSW_5msPostCall                                             */
/* !Trigger     : TASK_TIME_5MS                                               */
/* !Description :                                                             */
/* !Number      : 15                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void BSW_4msPostCall(void)
{
}

/******************************************************************************/
/*                                                                            */
/* !Task        : BSW_5msPreCall                                              */
/* !Trigger     : TASK_TIME_5MS                                               */
/* !Description :                                                             */
/* !Number      : 16                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void BSW_5msPreCall(void)
{
   BSW_u32FrtTM5msGlbCnt=BSW_u32FrtTM5msGlbCnt+1;

   Com_MainFunctionRx();

   Com_MainFunctionTx();

   Com_MainFunctionRouteSignals();

   CanTp_MainFunction();

   Dcm_MainFunction();

   Dem_MainFunction();


   TLF35584_vidManagement();
   
   TLE8242_vidParseResponse();
}

/******************************************************************************/
/*                                                                            */
/* !Task        : BSW_5msPostCall                                             */
/* !Trigger     : TASK_TIME_5MS                                               */
/* !Description :                                                             */
/* !Number      : 17                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void BSW_5msPostCall(void)
{
	TLE8242_vidCtrlManagement();
	TLE8242_vidDiagManagement();
	TLE8242_vidFaultDet();
}

/******************************************************************************/
/*                                                                            */
/* !Task        : BSW_10msPreCall                                             */
/* !Trigger     : TASK_TIME_10MS                                              */
/* !Description :                                                             */
/* !Number      : 18                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void BSW_10msPreCall(void)
{
   BSW_u32FrtTM10msGlbCnt=BSW_u32FrtTM10msGlbCnt+1;
   
   BSW_u32FrtTemp3Cnt=BSW_u32FrtTemp3Cnt+1;
   if(BSW_u32FrtTemp3Cnt >= 3)
   {
      BSW_u32FrtTM30msGlbCnt=BSW_u32FrtTM30msGlbCnt+1;
      BSW_u32FrtTemp3Cnt = 0;
   }

   VADC_vidUpdate10ms();
   //PWD_vidTimeoutManager();

   if (BSW_bCAN0BusOff != 0)
   {
      BSW_u8CAN0BusOffCounter++;
   }
   if (BSW_bCAN1BusOff != 0)
   {
      BSW_u8CAN1BusOffCounter++;
   }
   if (BSW_bCAN2BusOff != 0)
   {
      BSW_u8CAN2BusOffCounter++;
   }

   if (BSW_u8CAN0BusOffCounter > BSW_BUSOFF_COUNTER_MAX)
   {
      BSW_u8CAN0BusOffCounter = 0;

      CanIf_SetControllerMode(CanIf_CanController_0, CANIF_CS_STARTED);
      CanIf_SetPduMode(CanIf_CanController_0, CANIF_SET_ONLINE);

      BSW_bCAN0BusOff = 0;
   }
   if (BSW_u8CAN1BusOffCounter > BSW_BUSOFF_COUNTER_MAX)
   {
      BSW_u8CAN1BusOffCounter = 0;

      CanIf_SetControllerMode(CanIf_CanController_1, CANIF_CS_STARTED);
      CanIf_SetPduMode(CanIf_CanController_1, CANIF_SET_ONLINE);

      BSW_bCAN1BusOff = 0;
   }
   if (BSW_u8CAN2BusOffCounter > BSW_BUSOFF_COUNTER_MAX)
   {
      BSW_u8CAN2BusOffCounter = 0;

      CanIf_SetControllerMode(CanIf_CanController_2, CANIF_CS_STARTED);
      CanIf_SetPduMode(CanIf_CanController_2, CANIF_SET_ONLINE);

      BSW_bCAN2BusOff = 0;
   }
   
   NvM_MainFunction();
   Fee_MainFunction();
   Fls_17_Pmu_MainFunction();
}

/******************************************************************************/
/*                                                                            */
/* !Task        : BSW_10msPostCall                                            */
/* !Trigger     : TASK_TIME_10MS                                              */
/* !Description :                                                             */
/* !Number      : 19                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void BSW_10msPostCall(void)
{
    CCP_vidDaqListSetEvent(CCP_u8DAQ_EVT_EVENT_MEDIUM);
}

/******************************************************************************/
/*                                                                            */
/* !Task        : BSW_20msPreCall                                             */
/* !Trigger     : TASK_TIME_20MS                                              */
/* !Description :                                                             */
/* !Number      : 20                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void BSW_20msPreCall(void)
{
   EcuM_MainFunction();

   FiM_MainFunction();
}

/******************************************************************************/
/*                                                                            */
/* !Task        : BSW_20msPostCall                                            */
/* !Trigger     : TASK_TIME_20MS                                              */
/* !Description :                                                             */
/* !Number      : 21                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void BSW_20msPostCall(void)
{
}

/******************************************************************************/
/*                                                                            */
/* !Task        : BSW_30msPreCall                                             */
/* !Trigger     : TASK_TIME_30MS                                              */
/* !Description :                                                             */
/* !Number      : 22                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void BSW_30msPreCall(void)
{
}

/******************************************************************************/
/*                                                                            */
/* !Task        : BSW_30msPostCall                                            */
/* !Trigger     : TASK_TIME_30MS                                              */
/* !Description :                                                             */
/* !Number      : 23                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void BSW_30msPostCall(void)
{
}

/******************************************************************************/
/*                                                                            */
/* !Task        : BSW_50msPreCall                                             */
/* !Trigger     : TASK_TIME_50MS                                              */
/* !Description :                                                             */
/* !Number      : 24                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void BSW_50msPreCall(void)
{
   SCU_vidUpdate50ms();
}

/******************************************************************************/
/*                                                                            */
/* !Task        : BSW_50msPostCall                                            */
/* !Trigger     : TASK_TIME_50MS                                              */
/* !Description :                                                             */
/* !Number      : 25                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void BSW_50msPostCall(void)
{
}

/******************************************************************************/
/*                                                                            */
/* !Task        : BSW_100msPreCall                                            */
/* !Trigger     : TASK_TIME_100MS                                             */
/* !Description :                                                             */
/* !Number      : 26                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void BSW_100msPreCall(void)
{
   BSW_u32FrtTM100msGlbCnt=BSW_u32FrtTM100msGlbCnt+1;
   
   BSW_u32FrtTemp5Cnt=BSW_u32FrtTemp5Cnt+1; 
   if(BSW_u32FrtTemp5Cnt >= 5)
   {
      BSW_u32FrtTM500msGlbCnt=BSW_u32FrtTM500msGlbCnt+1;
      BSW_u32FrtTemp5Cnt = 0;
   }


   RSTSRV_vidMainFunction();
   PWD_vidEntry_100ms();
}

/******************************************************************************/
/*                                                                            */
/* !Task        : BSW_100msPostCall                                           */
/* !Trigger     : TASK_TIME_100MS                                             */
/* !Description :                                                             */
/* !Number      : 27                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void BSW_100msPostCall(void)
{
   CCP_vidDaqListSetEvent(CCP_u8DAQ_EVT_EVENT_SLOW);
   CCP_vidMainFunction();
}

/******************************************************************************/
/*                                                                            */
/* !Task        : BSW_200msPreCall                                            */
/* !Trigger     : TASK_TIME_200MS                                             */
/* !Description :                                                             */
/* !Number      : 28                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void BSW_200msPreCall(void)
{
}

/******************************************************************************/
/*                                                                            */
/* !Task        : BSW_200msPostCal                                            */
/* !Trigger     : TASK_TIME_200MS                                             */
/* !Description :                                                             */
/* !Number      : 29                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void BSW_200msPostCall(void)
{
}

/******************************************************************************/
/*                                                                            */
/* !Task        : BSW_500msPreCall                                            */
/* !Trigger     : TASK_TIME_500MS                                             */
/* !Description :                                                             */
/* !Number      : 30                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void BSW_500msPreCall(void)
{
}

/******************************************************************************/
/*                                                                            */
/* !Task        : BSW_500msPostCall                                           */
/* !Trigger     : TASK_TIME_500MS                                             */
/* !Description :                                                             */
/* !Number      : 31                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void BSW_500msPostCall(void)
{
}

/******************************************************************************/
/*                                                                            */
/* !Task        : BSW_1000msPreCall                                           */
/* !Trigger     : TASK_TIME_1000MS                                            */
/* !Description :                                                             */
/* !Number      : 32                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void BSW_1000msPreCall(void)
{
   BSW_u32FrtTM1sGlbCnt=BSW_u32FrtTM1sGlbCnt+1;

   RTMCLD_vidMainFunction();

   if(BSW_u32FrtTM1sGlbCnt > 10)
   {
   	RTMCLD_vidCpuLoadMeasure_4SR();
   }
	
}

/******************************************************************************/
/*                                                                            */
/* !Task        : BSW_1000msPostCall                                          */
/* !Trigger     : TASK_TIME_1000MS                                            */
/* !Description :                                                             */
/* !Number      : 33                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void BSW_1000msPostCall(void)
{
}

/******************************************************************************/
/*                                                                            */
/* !Task        : BSW_1000msPreCall                                           */
/* !Trigger     : TASK_TIME_1000MS                                            */
/* !Description :                                                             */
/* !Number      : 34                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void BSW_2000msPreCall(void)
{
}

/******************************************************************************/
/*                                                                            */
/* !Task        : BSW_1000msPostCall                                          */
/* !Trigger     : TASK_TIME_1000MS                                            */
/* !Description :                                                             */
/* !Number      : 35                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void BSW_2000msPostCall(void)
{
}

/******************************************************************************/
/*                                                                            */
/* !Task        : BSW_PowerDown                                               */
/* !Trigger     : TASK_POWER_DOWN                                             */
/* !Description :                                                             */
/* !Number      : 40                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void BSW_PowerDown(void)
{
   //DMA_vidStartDeInit();
   //INTBSL_vidDeInit();
   if (DMA_vidChckDeInit() == TRUE)
   {
   }
   else
   {
   }
   //Dio_WriteChannel(DioConf_DioChannel_PWR_LATCH, STD_OFF);
}

/******************************************************************************/
/*                                                                            */
/* !Task        : BSW_PowerUp                                                 */
/* !Trigger     : TASK_POWER_UP                                               */
/* !Description :                                                             */
/* !Number      : 41                                                          */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : O. Garot                                                    */
/******************************************************************************/
void BSW_PowerUp(void)
{
   //Dio_WriteChannel(DioConf_DioChannel_PWR_LATCH, STD_ON);
}


#define BSW_STOP_SEC_CODE
#include "BSW_MemMap.h"

/*-------------------------------- end of file -------------------------------*/
