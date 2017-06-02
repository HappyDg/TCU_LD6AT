/******************************************************************************/
/*                                                                            */
/* !Layer          : Layer                                                    */
/*                                                                            */
/* !Component      : Component                                                */
/* !Description    : Component description                                    */
/*                                                                            */
/* !Module         : MODULE                                                   */
/* !Description    : MODULE description                                       */
/*                                                                            */
/* !File           : MAIN_MSG.C                                               */
/*                                                                            */
/* !Scope          : Public                                                   */
/*                                                                            */
/* !Target         : Infineon_tc17                                            */
/*                                                                            */
/* !Vendor         : VALEO                                                    */
/*                                                                            */
/* !Author         : A. Abohassan                                             */
/*                                                                            */
/* Coding language : C                                                        */
/*                                                                            */
/* COPYRIGHT 2006 VALEO                                                       */
/* all rights reserved                                                        */
/*                                                                            */
/******************************************************************************/
/* PVCS Information                                                           */
/* $Archive::   $*/
/* $Revision::  $*/
/******************************************************************************/
/* !VnrOff :                                                                  */
/******************************************************************************/
/******************************************************************************/

#include "MAIN.H"
#include "MAIN_L.H"
#include "MAIN_Msg.h"

#include "MSG.h"

//<<#include "Com.h"
//>>
#include "Com_SymbolicNames_PBcfg.h"
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

/******************************************************************************/
/* GLOBAL FUNCTION DEFINITION                                                 */
/******************************************************************************/

#define MAIN_START_SEC_CODE
#include "MAIN_MemMap.h"

/******************************************************************************/
/*                                                                            */
/* !Description: MAIN MSG initialization                                      */
/* !Number     : MAIN.MSG.1                                                   */
/* !Reference  :                                                              */
/* !Trace_To   :                                                              */
/*                                                                            */
/* !LastAuthor : A. Abohassan                                                 */
/******************************************************************************/
void MAIN_MSGvidInit(void)
{
	/* ========================================================================== */
	/* CAN Rx MSG Functions Init													 */
	/* ========================================================================== */
	   /* 10 ms */
	   /* ABS1 */
	   MAIN_MSGu16WhlSpdFrntLeRaw = MAIN_MSG_WHLSPDFRNTLERAW_INIT;
	   MAIN_MSGf32WhlSpdFrntLeRawPhys = MAIN_MSG_WHLSPDFRNTLERAW_NEUTRAL;
	   MAIN_MSGu16WhlSpdFrntRiRaw = MAIN_MSG_WHLSPDFRNTRIRAW_INIT;
	   MAIN_MSGf32WhlSpdFrntRiRawPhys = MAIN_MSG_WHLSPDFRNTRIRAW_NEUTRAL;
	   MAIN_MSGu16WhlSpdReLeRaw = MAIN_MSG_WHLSPDRELERAW_INIT;
	   MAIN_MSGf32WhlSpdReLeRawPhys = MAIN_MSG_WHLSPDRELERAW_NEUTRAL;
	   MAIN_MSGu16WhlSpdReRiRaw = MAIN_MSG_WHLSPDRERIRAW_INIT;
	   MAIN_MSGf32WhlSpdReRiRawPhys = MAIN_MSG_WHLSPDRERIRAW_NEUTRAL;
	   /* 10 ms */
	   /* ABS2 */
	   MAIN_MSGbAbsCtrlActv = MAIN_MSG_ABSCTRLACTV_INIT;
	   MAIN_MSGbAbsFlgFlt = MAIN_MSG_ABSFLGFLT_INIT;
	   MAIN_MSGbEbdFlgFlt = MAIN_MSG_EBDFLGFLT_INIT;
	   /* 10 ms */
	   /* ECM1 */
	   MAIN_MSGu8AccrPedlRat = MAIN_MSG_ACCRPEDLRAT_INIT;
	   MAIN_MSGf32AccrPedlRatPhys = MAIN_MSG_ACCRPEDLRAT_NEUTRAL;
	   MAIN_MSGu8BrkPedlPsd = MAIN_MSG_BRKPEDLPSD_INIT;
	   MAIN_MSGu8ECM1AliveCounter = MAIN_MSG_ECM1ALIVECOUNTER_INIT;
	   MAIN_MSGf32ECM1AliveCounterPhys = MAIN_MSG_ECM1ALIVECOUNTER_NEUTRAL;
	   MAIN_MSGu8ECM1Checksum = MAIN_MSG_ECM1CHECKSUM_INIT;
	   MAIN_MSGf32ECM1ChecksumPhys = MAIN_MSG_ECM1CHECKSUM_NEUTRAL;
	   MAIN_MSGu8EngStAct = MAIN_MSG_ENGSTACT_INIT;
	   MAIN_MSGu16EngTqIndAct = MAIN_MSG_ENGTQINDACT_INIT;
	   MAIN_MSGf32EngTqIndActPhys = MAIN_MSG_ENGTQINDACT_NEUTRAL;
	   MAIN_MSGu16EngTqIndDrvDmd = MAIN_MSG_ENGTQINDDRVDMD_INIT;
	   MAIN_MSGf32EngTqIndDrvDmdPhys = MAIN_MSG_ENGTQINDDRVDMD_NEUTRAL;
	   MAIN_MSGu16EngTqLoss = MAIN_MSG_ENGTQLOSS_INIT;
	   MAIN_MSGf32EngTqLossPhys = MAIN_MSG_ENGTQLOSS_NEUTRAL;
	   MAIN_MSGbHvacCluSts = MAIN_MSG_HVACCLUSTS_INIT;
	   MAIN_MSGu8ThrottleCmdPos = MAIN_MSG_THROTTLECMDPOS_INIT;
	   MAIN_MSGf32ThrottleCmdPosPhys = MAIN_MSG_THROTTLECMDPOS_NEUTRAL;
	   /* 10 ms */
	   /* ECM2 */
	   MAIN_MSGbCrsCtrlCtrlActv = MAIN_MSG_CRSCTRLCTRLACTV_INIT;
	   MAIN_MSGu8ECM2AliveCounter = MAIN_MSG_ECM2ALIVECOUNTER_INIT;
	   MAIN_MSGf32ECM2AliveCounterPhys = MAIN_MSG_ECM2ALIVECOUNTER_NEUTRAL;
	   MAIN_MSGu8ECM2Checksum = MAIN_MSG_ECM2CHECKSUM_INIT;
	   MAIN_MSGf32ECM2ChecksumPhys = MAIN_MSG_ECM2CHECKSUM_NEUTRAL;
	   MAIN_MSGu16EngN = MAIN_MSG_ENGN_INIT;
	   MAIN_MSGf32EngNPhys = MAIN_MSG_ENGN_NEUTRAL;
	   MAIN_MSGu16EngNTgtIdle = MAIN_MSG_ENGNTGTIDLE_INIT;
	   MAIN_MSGf32EngNTgtIdlePhys = MAIN_MSG_ENGNTGTIDLE_NEUTRAL;
	   MAIN_MSGu8GearLmtForLightOff = MAIN_MSG_GEARLMTFORLIGHTOFF_INIT;
	   /* 10 ms */
	   /* ESC1 */
	   MAIN_MSGs16Algt = MAIN_MSG_ALGT_INIT;
	   MAIN_MSGf32AlgtPhys = MAIN_MSG_ALGT_NEUTRAL;
	   MAIN_MSGbEscFlgFlt = MAIN_MSG_ESCFLGFLT_INIT;
	   MAIN_MSGu8GearShiftPrevn = MAIN_MSG_GEARSHIFTPREVN_INIT;
	   MAIN_MSGbTcsCtrlActv = MAIN_MSG_TCSCTRLACTV_INIT;
	   MAIN_MSGbTcsFlgFlt = MAIN_MSG_TCSFLGFLT_INIT;
	   /* 20 ms */
	   /* ECM3 */
	   MAIN_MSGu16EngineSoakTime = MAIN_MSG_ENGINESOAKTIME_INIT;
	   MAIN_MSGf32EngineSoakTimePhys = MAIN_MSG_ENGINESOAKTIME_NEUTRAL;
	   MAIN_MSGu8EngPAmbAir = MAIN_MSG_ENGPAMBAIR_INIT;
	   MAIN_MSGf32EngPAmbAirPhys = MAIN_MSG_ENGPAMBAIR_NEUTRAL;
	   MAIN_MSGu8EngT = MAIN_MSG_ENGT_INIT;
	   MAIN_MSGf32EngTPhys = MAIN_MSG_ENGT_NEUTRAL;
	   MAIN_MSGbOBDDrivingCycleStatus = MAIN_MSG_OBDDRIVINGCYCLESTATUS_INIT;
	   MAIN_MSGbOBDWarmUpCycleStatus = MAIN_MSG_OBDWARMUPCYCLESTATUS_INIT;
	   /* 20 ms */
	   /* IP1 */
	   MAIN_MSGu8AmbAirTemp = MAIN_MSG_AMBAIRTEMP_INIT;
	   MAIN_MSGf32AmbAirTempPhys = MAIN_MSG_AMBAIRTEMP_NEUTRAL;
	/* ========================================================================== */
	/* CAN Tx MSG Functions Init													 */
	/* ========================================================================== */
	   /* 10 ms */
	   /* TCU1 */
	   MAIN_MSGu8EngNIdleReq = MAIN_MSG_ENGNIDLEREQ_INIT;
	   MAIN_MSGf32EngNIdleReqPhys = MAIN_MSG_ENGNIDLEREQ_NEUTRAL;
	   MAIN_MSGu8EngTqIndDecReqdByTrsm = MAIN_MSG_ENGTQINDDECREQDBYTRSM_INIT;
	   MAIN_MSGf32EngTqIndDecReqdByTrsmPhys = MAIN_MSG_ENGTQINDDECREQDBYTRSM_NEUTRAL;
	   MAIN_MSGu8EngTqIndLmtdByTrsm = MAIN_MSG_ENGTQINDLMTDBYTRSM_INIT;
	   MAIN_MSGf32EngTqIndLmtdByTrsmPhys = MAIN_MSG_ENGTQINDLMTDBYTRSM_NEUTRAL;
	   MAIN_MSGu8TrsmCluStAct = MAIN_MSG_TRSMCLUSTACT_INIT;
	   MAIN_MSGu8TrsmMsgCnt = MAIN_MSG_TRSMMSGCNT_INIT;
	   MAIN_MSGf32TrsmMsgCntPhys = MAIN_MSG_TRSMMSGCNT_NEUTRAL;
	   MAIN_MSGu16TrsmNInp = MAIN_MSG_TRSMNINP_INIT;
	   MAIN_MSGf32TrsmNInpPhys = MAIN_MSG_TRSMNINP_NEUTRAL;
	   /* 10 ms */
	   /* TCU2 */
	   MAIN_MSGu8EngTqIndIncReqdByTrsm = MAIN_MSG_ENGTQINDINCREQDBYTRSM_INIT;
	   MAIN_MSGf32EngTqIndIncReqdByTrsmPhys = MAIN_MSG_ENGTQINDINCREQDBYTRSM_NEUTRAL;
	   MAIN_MSGu8TrsmFlgFlt = MAIN_MSG_TRSMFLGFLT_INIT;
	   MAIN_MSGbTrsmFlgShiftProgs = MAIN_MSG_TRSMFLGSHIFTPROGS_INIT;
	   MAIN_MSGu8TrsmGearAct = MAIN_MSG_TRSMGEARACT_INIT;
	   MAIN_MSGu8TrsmGearTar = MAIN_MSG_TRSMGEARTAR_INIT;
	   MAIN_MSGbTrsmMILReq = MAIN_MSG_TRSMMILREQ_INIT;
	   MAIN_MSGu8TrsmStGearLvr = MAIN_MSG_TRSMSTGEARLVR_INIT;
	   MAIN_MSGu8TrsmStGearMode = MAIN_MSG_TRSMSTGEARMODE_INIT;
	   MAIN_MSGu8TrsmTOil = MAIN_MSG_TRSMTOIL_INIT;
	   MAIN_MSGf32TrsmTOilPhys = MAIN_MSG_TRSMTOIL_NEUTRAL;
	   MAIN_MSGbTrsmTOilWrnLmpReq = MAIN_MSG_TRSMTOILWRNLMPREQ_INIT;

}

void MAIN_MSGvidRx_Tsk10ms( void )
{
   if (MAIN_MSGRxBenchOnC == 0)
	{
		  /* ABS1 Period:10ms. Direction:Rx */
      MAIN_MSGvidRxABS1(
         &MAIN_MSGf32WhlSpdFrntLeRawPhys,
         &MAIN_MSGu16WhlSpdFrntLeRaw,
         &MAIN_MSGf32WhlSpdFrntRiRawPhys,
         &MAIN_MSGu16WhlSpdFrntRiRaw,
         &MAIN_MSGf32WhlSpdReLeRawPhys,
         &MAIN_MSGu16WhlSpdReLeRaw,
         &MAIN_MSGf32WhlSpdReRiRawPhys,
         &MAIN_MSGu16WhlSpdReRiRaw);
/* ABS1 */
//<<      xxx = MAIN_MSGf32WhlSpdFrntLeRawPhys;
//<<      xxx = MAIN_MSGf32WhlSpdFrntRiRawPhys;
//<<      xxx = MAIN_MSGf32WhlSpdReLeRawPhys;
//<<      xxx = MAIN_MSGf32WhlSpdReRiRawPhys;


      /* ABS2 Period:10ms. Direction:Rx */
      MAIN_MSGvidRxABS2(
         &MAIN_MSGbAbsCtrlActv,
         &MAIN_MSGbAbsFlgFlt,
         &MAIN_MSGbEbdFlgFlt);
/* ABS2 */
//<<      xxx = MAIN_MSGbAbsCtrlActv;
//<<      xxx = MAIN_MSGbAbsFlgFlt;
//<<      xxx = MAIN_MSGbEbdFlgFlt;


      /* ECM1 Period:10ms. Direction:Rx */
      MAIN_MSGvidRxECM1(
         &MAIN_MSGf32AccrPedlRatPhys,
         &MAIN_MSGu8AccrPedlRat,
         &MAIN_MSGu8BrkPedlPsd,
         &MAIN_MSGf32ECM1AliveCounterPhys,
         &MAIN_MSGu8ECM1AliveCounter,
         &MAIN_MSGf32ECM1ChecksumPhys,
         &MAIN_MSGu8ECM1Checksum,
         &MAIN_MSGu8EngStAct,
         &MAIN_MSGf32EngTqIndActPhys,
         &MAIN_MSGu16EngTqIndAct,
         &MAIN_MSGf32EngTqIndDrvDmdPhys,
         &MAIN_MSGu16EngTqIndDrvDmd,
         &MAIN_MSGf32EngTqLossPhys,
         &MAIN_MSGu16EngTqLoss,
         &MAIN_MSGbHvacCluSts,
         &MAIN_MSGf32ThrottleCmdPosPhys,
         &MAIN_MSGu8ThrottleCmdPos);
/* ECM1 */
//<<      xxx = MAIN_MSGf32AccrPedlRatPhys;
//<<      xxx = MAIN_MSGu8BrkPedlPsd;
//<<      xxx = MAIN_MSGf32ECM1AliveCounterPhys;
//<<      xxx = MAIN_MSGf32ECM1ChecksumPhys;
//<<      xxx = MAIN_MSGu8EngStAct;
//<<      xxx = MAIN_MSGf32EngTqIndActPhys;
//<<      xxx = MAIN_MSGf32EngTqIndDrvDmdPhys;
//<<      xxx = MAIN_MSGf32EngTqLossPhys;
//<<      xxx = MAIN_MSGbHvacCluSts;
//<<      xxx = MAIN_MSGf32ThrottleCmdPosPhys;


      /* ECM2 Period:10ms. Direction:Rx */
      MAIN_MSGvidRxECM2(
         &MAIN_MSGbCrsCtrlCtrlActv,
         &MAIN_MSGf32ECM2AliveCounterPhys,
         &MAIN_MSGu8ECM2AliveCounter,
         &MAIN_MSGf32ECM2ChecksumPhys,
         &MAIN_MSGu8ECM2Checksum,
         &MAIN_MSGf32EngNPhys,
         &MAIN_MSGu16EngN,
         &MAIN_MSGf32EngNTgtIdlePhys,
         &MAIN_MSGu16EngNTgtIdle,
         &MAIN_MSGu8GearLmtForLightOff);
/* ECM2 */
//<<      xxx = MAIN_MSGbCrsCtrlCtrlActv;
//<<      xxx = MAIN_MSGf32ECM2AliveCounterPhys;
//<<      xxx = MAIN_MSGf32ECM2ChecksumPhys;
//<<      xxx = MAIN_MSGf32EngNPhys;
//<<      xxx = MAIN_MSGf32EngNTgtIdlePhys;
//<<      xxx = MAIN_MSGu8GearLmtForLightOff;


      /* ESC1 Period:10ms. Direction:Rx */
      MAIN_MSGvidRxESC1(
         &MAIN_MSGf32AlgtPhys,
         &MAIN_MSGs16Algt,
         &MAIN_MSGbEscFlgFlt,
         &MAIN_MSGu8GearShiftPrevn,
         &MAIN_MSGbTcsCtrlActv,
         &MAIN_MSGbTcsFlgFlt);
/* ESC1 */
	}
}
void MAIN_MSGvidRx_Tsk20ms( void )
{
   if (MAIN_MSGRxBenchOnC == 0)
   	{
   	//<<      xxx = MAIN_MSGf32AlgtPhys;
	//<<      xxx = MAIN_MSGbEscFlgFlt;
	//<<      xxx = MAIN_MSGu8GearShiftPrevn;
	//<<      xxx = MAIN_MSGbTcsCtrlActv;
	//<<      xxx = MAIN_MSGbTcsFlgFlt;


      /* ECM3 Period:20ms. Direction:Rx */
      MAIN_MSGvidRxECM3(
         &MAIN_MSGf32EngineSoakTimePhys,
         &MAIN_MSGu16EngineSoakTime,
         &MAIN_MSGf32EngPAmbAirPhys,
         &MAIN_MSGu8EngPAmbAir,
         &MAIN_MSGf32EngTPhys,
         &MAIN_MSGu8EngT,
         &MAIN_MSGbOBDDrivingCycleStatus,
         &MAIN_MSGbOBDWarmUpCycleStatus);
/* ECM3 */
//<<      xxx = MAIN_MSGf32EngineSoakTimePhys;
//<<      xxx = MAIN_MSGf32EngPAmbAirPhys;
//<<      xxx = MAIN_MSGf32EngTPhys;
//<<      xxx = MAIN_MSGbOBDDrivingCycleStatus;
//<<      xxx = MAIN_MSGbOBDWarmUpCycleStatus;


      /* IP1 Period:20ms. Direction:Rx */
      MAIN_MSGvidRxIP1(
         &MAIN_MSGf32AmbAirTempPhys,
         &MAIN_MSGu8AmbAirTemp);
/* IP1 */
   	}
}

void MAIN_MSGvidRx_Tsk50ms( void )
{
   if (MAIN_MSGRxBenchOnC == 0)
   	{

   	}
}
void MAIN_MSGvidRx_Tsk100ms( void )
{
   if (MAIN_MSGRxBenchOnC == 0)
   	{

   	}
}
void MAIN_MSGvidRx_Tsk200ms( void )
{
   if (MAIN_MSGRxBenchOnC == 0)
   	{

   	}
}


void MAIN_MSGvidRx_Tsk1000ms( void )
{
   if (MAIN_MSGRxBenchOnC == 0)
   	{

   	}
}

void MAIN_MSGvidTx_Tsk10ms( void )
{
   if (MAIN_MSGTxBenchOnC == 0)
   	{
		/* TCU1 */
//<<      MAIN_MSGf32EngNIdleReqPhys = xxx;
//<<      MAIN_MSGf32EngTqIndDecReqdByTrsmPhys = xxx;
//<<      MAIN_MSGf32EngTqIndLmtdByTrsmPhys = xxx;
//<<      MAIN_MSGu8TrsmCluStAct = xxx;
//<<      MAIN_MSGf32TrsmMsgCntPhys = xxx;
//<<      MAIN_MSGf32TrsmNInpPhys = xxx;
      /* TCU1 Period:10ms. Direction:Tx */
      MAIN_MSGvidTxTCU1(
         MAIN_MSGf32EngNIdleReqPhys,
         &MAIN_MSGu8EngNIdleReq,
         MAIN_MSGf32EngTqIndDecReqdByTrsmPhys,
         &MAIN_MSGu8EngTqIndDecReqdByTrsm,
         MAIN_MSGf32EngTqIndLmtdByTrsmPhys,
         &MAIN_MSGu8EngTqIndLmtdByTrsm,
         MAIN_MSGu8TrsmCluStAct,
         MAIN_MSGf32TrsmMsgCntPhys,
         &MAIN_MSGu8TrsmMsgCnt,
         MAIN_MSGf32TrsmNInpPhys,
         &MAIN_MSGu16TrsmNInp);


/* TCU2 */
//<<      MAIN_MSGf32EngTqIndIncReqdByTrsmPhys = xxx;
//<<      MAIN_MSGu8TrsmFlgFlt = xxx;
//<<      MAIN_MSGbTrsmFlgShiftProgs = xxx;
//<<      MAIN_MSGu8TrsmGearAct = xxx;
//<<      MAIN_MSGu8TrsmGearTar = xxx;
//<<      MAIN_MSGbTrsmMILReq = xxx;
//<<      MAIN_MSGu8TrsmStGearLvr = xxx;
//<<      MAIN_MSGu8TrsmStGearMode = xxx;
//<<      MAIN_MSGf32TrsmTOilPhys = xxx;
//<<      MAIN_MSGbTrsmTOilWrnLmpReq = xxx;
      /* TCU2 Period:10ms. Direction:Tx */
      MAIN_MSGvidTxTCU2(
         MAIN_MSGf32EngTqIndIncReqdByTrsmPhys,
         &MAIN_MSGu8EngTqIndIncReqdByTrsm,
         MAIN_MSGu8TrsmFlgFlt,
         MAIN_MSGbTrsmFlgShiftProgs,
         MAIN_MSGu8TrsmGearAct,
         MAIN_MSGu8TrsmGearTar,
         MAIN_MSGbTrsmMILReq,
         MAIN_MSGu8TrsmStGearLvr,
         MAIN_MSGu8TrsmStGearMode,
         MAIN_MSGf32TrsmTOilPhys,
         &MAIN_MSGu8TrsmTOil,
         MAIN_MSGbTrsmTOilWrnLmpReq);
   	}
}

void MAIN_MSGvidTx_Tsk20ms( void )
{
   if (MAIN_MSGTxBenchOnC == 0)
   	{

   	}
}

void MAIN_MSGvidTx_Tsk50ms( void )
{

}
void MAIN_MSGvidTx_Tsk100ms( void )
{
   if (MAIN_MSGTxBenchOnC == 0)
   	{
   	}
}
void MAIN_MSGvidTx_Tsk200ms( void )
{
   if (MAIN_MSGTxBenchOnC == 0)
   {
   }
}

void MAIN_MSGvidTx_Tsk1000ms( void )
{

}

/* ========================================================================== */
/* CAN HCU_HS/ Functions Rx                                                   */
/* ========================================================================== */

/******************************************************************************/
/*                                                                            */
/* !Function    : MAIN_MSGvidRxETEI_Engine_Torque_Status                      */
/* !Description : Rx 10 ms                                                    */
/* !Number      : MAIN.MSG.2                                                  */
/* !Reference   : NONE                                                        */
/* !LastAuthor  : A. Abohassan                                                */
/*                                                                            */
/******************************************************************************/
void MAIN_MSGvidRxABS1(
   float   *Arg_f32WhlSpdFrntLeRawPhys,
   uint16  *Arg_u16WhlSpdFrntLeRawRaw,
   float   *Arg_f32WhlSpdFrntRiRawPhys,
   uint16  *Arg_u16WhlSpdFrntRiRawRaw,
   float   *Arg_f32WhlSpdReLeRawPhys,
   uint16  *Arg_u16WhlSpdReLeRawRaw,
   float   *Arg_f32WhlSpdReRiRawPhys,
   uint16  *Arg_u16WhlSpdReRiRawRaw)
{
   uint16  local_u16WhlSpdFrntLeRawRaw;
   float   local_f32WhlSpdFrntLeRawPhys;
   uint16  local_u16WhlSpdFrntRiRawRaw;
   float   local_f32WhlSpdFrntRiRawPhys;
   uint16  local_u16WhlSpdReLeRawRaw;
   float   local_f32WhlSpdReLeRawPhys;
   uint16  local_u16WhlSpdReRiRawRaw;
   float   local_f32WhlSpdReRiRawPhys;


   if (  (BSW_bCbkRxTOutFlag_SGABS1 == FALSE)
      || (MAIN_bMSGRxToutBenchOnC != FALSE)
      )
   {
      Com_ReceiveSignal(ComConf_ComSignal_SGWhlSpdFrntLeRaw_529R, &local_u16WhlSpdFrntLeRawRaw);
      Com_ReceiveSignal(ComConf_ComSignal_SGWhlSpdFrntRiRaw_529R, &local_u16WhlSpdFrntRiRawRaw);
      Com_ReceiveSignal(ComConf_ComSignal_SGWhlSpdReLeRaw_529R, &local_u16WhlSpdReLeRawRaw);
      Com_ReceiveSignal(ComConf_ComSignal_SGWhlSpdReRiRaw_529R, &local_u16WhlSpdReRiRawRaw);
   }
   else
   {
      local_u16WhlSpdFrntLeRawRaw = MAIN_MSG_WHLSPDFRNTLERAW_INIT;
      local_u16WhlSpdFrntRiRawRaw = MAIN_MSG_WHLSPDFRNTRIRAW_INIT;
      local_u16WhlSpdReLeRawRaw = MAIN_MSG_WHLSPDRELERAW_INIT;
      local_u16WhlSpdReRiRawRaw = MAIN_MSG_WHLSPDRERIRAW_INIT;
   }


   /*WhlSpdFrntLeRawPhys*/
   *Arg_u16WhlSpdFrntLeRawRaw = local_u16WhlSpdFrntLeRawRaw;
   if(local_u16WhlSpdFrntLeRawRaw == MAIN_MSG_WHLSPDFRNTLERAW_INIT)
   {
      *Arg_f32WhlSpdFrntLeRawPhys = MAIN_MSG_WHLSPDFRNTLERAW_NEUTRAL;
   }
   else
   {
      local_f32WhlSpdFrntLeRawPhys = MAIN_MSG_SCALE_SIGNAL_RAW2PHYS(WHLSPDFRNTLERAW, local_u16WhlSpdFrntLeRawRaw);
      *Arg_f32WhlSpdFrntLeRawPhys = MAIN_MSG_CLAMP_SIGNAL_PHYS(WHLSPDFRNTLERAW, local_f32WhlSpdFrntLeRawPhys);
   }


   /*WhlSpdFrntRiRawPhys*/
   *Arg_u16WhlSpdFrntRiRawRaw = local_u16WhlSpdFrntRiRawRaw;
   if(local_u16WhlSpdFrntRiRawRaw == MAIN_MSG_WHLSPDFRNTRIRAW_INIT)
   {
      *Arg_f32WhlSpdFrntRiRawPhys = MAIN_MSG_WHLSPDFRNTRIRAW_NEUTRAL;
   }
   else
   {
      local_f32WhlSpdFrntRiRawPhys = MAIN_MSG_SCALE_SIGNAL_RAW2PHYS(WHLSPDFRNTRIRAW, local_u16WhlSpdFrntRiRawRaw);
      *Arg_f32WhlSpdFrntRiRawPhys = MAIN_MSG_CLAMP_SIGNAL_PHYS(WHLSPDFRNTRIRAW, local_f32WhlSpdFrntRiRawPhys);
   }


   /*WhlSpdReLeRawPhys*/
   *Arg_u16WhlSpdReLeRawRaw = local_u16WhlSpdReLeRawRaw;
   if(local_u16WhlSpdReLeRawRaw == MAIN_MSG_WHLSPDRELERAW_INIT)
   {
      *Arg_f32WhlSpdReLeRawPhys = MAIN_MSG_WHLSPDRELERAW_NEUTRAL;
   }
   else
   {
      local_f32WhlSpdReLeRawPhys = MAIN_MSG_SCALE_SIGNAL_RAW2PHYS(WHLSPDRELERAW, local_u16WhlSpdReLeRawRaw);
      *Arg_f32WhlSpdReLeRawPhys = MAIN_MSG_CLAMP_SIGNAL_PHYS(WHLSPDRELERAW, local_f32WhlSpdReLeRawPhys);
   }


   /*WhlSpdReRiRawPhys*/
   *Arg_u16WhlSpdReRiRawRaw = local_u16WhlSpdReRiRawRaw;
   if(local_u16WhlSpdReRiRawRaw == MAIN_MSG_WHLSPDRERIRAW_INIT)
   {
      *Arg_f32WhlSpdReRiRawPhys = MAIN_MSG_WHLSPDRERIRAW_NEUTRAL;
   }
   else
   {
      local_f32WhlSpdReRiRawPhys = MAIN_MSG_SCALE_SIGNAL_RAW2PHYS(WHLSPDRERIRAW, local_u16WhlSpdReRiRawRaw);
      *Arg_f32WhlSpdReRiRawPhys = MAIN_MSG_CLAMP_SIGNAL_PHYS(WHLSPDRERIRAW, local_f32WhlSpdReRiRawPhys);
   }
}


void MAIN_MSGvidRxABS2(
   boolean *Arg_bAbsCtrlActvRaw,
   boolean *Arg_bAbsFlgFltRaw,
   boolean *Arg_bEbdFlgFltRaw)
{
   if (  (BSW_bCbkRxTOutFlag_SGABS2 == FALSE)
      || (MAIN_bMSGRxToutBenchOnC != FALSE)
      )
   {
      Com_ReceiveSignal(ComConf_ComSignal_SGAbsCtrlActv_545R, Arg_bAbsCtrlActvRaw);
      Com_ReceiveSignal(ComConf_ComSignal_SGAbsFlgFlt_545R, Arg_bAbsFlgFltRaw);
      Com_ReceiveSignal(ComConf_ComSignal_SGEbdFlgFlt_545R, Arg_bEbdFlgFltRaw);
   }
   else
   {
      *Arg_bAbsCtrlActvRaw = MAIN_MSG_ABSCTRLACTV_INIT;
      *Arg_bAbsFlgFltRaw = MAIN_MSG_ABSFLGFLT_INIT;
      *Arg_bEbdFlgFltRaw = MAIN_MSG_EBDFLGFLT_INIT;
   }
}

void MAIN_MSGvidRxECM1(
   float   *Arg_f32AccrPedlRatPhys,
   uint8   *Arg_u8AccrPedlRatRaw,
   uint8   *Arg_u8BrkPedlPsdRaw,
   float   *Arg_f32ECM1AliveCounterPhys,
   uint8   *Arg_u8ECM1AliveCounterRaw,
   float   *Arg_f32ECM1ChecksumPhys,
   uint8   *Arg_u8ECM1ChecksumRaw,
   uint8   *Arg_u8EngStActRaw,
   float   *Arg_f32EngTqIndActPhys,
   uint16  *Arg_u16EngTqIndActRaw,
   float   *Arg_f32EngTqIndDrvDmdPhys,
   uint16  *Arg_u16EngTqIndDrvDmdRaw,
   float   *Arg_f32EngTqLossPhys,
   uint16  *Arg_u16EngTqLossRaw,
   boolean *Arg_bHvacCluStsRaw,
   float   *Arg_f32ThrottleCmdPosPhys,
   uint8   *Arg_u8ThrottleCmdPosRaw)
{
   uint8   local_u8AccrPedlRatRaw;
   float   local_f32AccrPedlRatPhys;
   uint8   local_u8ECM1AliveCounterRaw;
   float   local_f32ECM1AliveCounterPhys;
   uint8   local_u8ECM1ChecksumRaw;
   float   local_f32ECM1ChecksumPhys;
   uint16  local_u16EngTqIndActRaw;
   float   local_f32EngTqIndActPhys;
   uint16  local_u16EngTqIndDrvDmdRaw;
   float   local_f32EngTqIndDrvDmdPhys;
   uint16  local_u16EngTqLossRaw;
   float   local_f32EngTqLossPhys;
   uint8   local_u8ThrottleCmdPosRaw;
   float   local_f32ThrottleCmdPosPhys;


   if (  (BSW_bCbkRxTOutFlag_SGECM1 == FALSE)
      || (MAIN_bMSGRxToutBenchOnC != FALSE)
      )
   {
      Com_ReceiveSignal(ComConf_ComSignal_SGAccrPedlRat_273R, &local_u8AccrPedlRatRaw);
      Com_ReceiveSignal(ComConf_ComSignal_SGBrkPedlPsd_273R, Arg_u8BrkPedlPsdRaw);
      Com_ReceiveSignal(ComConf_ComSignal_SGECM1AliveCounter_273R, &local_u8ECM1AliveCounterRaw);
      Com_ReceiveSignal(ComConf_ComSignal_SGECM1Checksum_273R, &local_u8ECM1ChecksumRaw);
      Com_ReceiveSignal(ComConf_ComSignal_SGEngStAct_273R, Arg_u8EngStActRaw);
      Com_ReceiveSignal(ComConf_ComSignal_SGEngTqIndAct_273R, &local_u16EngTqIndActRaw);
      Com_ReceiveSignal(ComConf_ComSignal_SGEngTqIndDrvDmd_273R, &local_u16EngTqIndDrvDmdRaw);
      Com_ReceiveSignal(ComConf_ComSignal_SGEngTqLoss_273R, &local_u16EngTqLossRaw);
      Com_ReceiveSignal(ComConf_ComSignal_SGHvacCluSts_273R, Arg_bHvacCluStsRaw);
      Com_ReceiveSignal(ComConf_ComSignal_SGThrottleCmdPos_273R, &local_u8ThrottleCmdPosRaw);
   }
   else
   {
      local_u8AccrPedlRatRaw = MAIN_MSG_ACCRPEDLRAT_INIT;
      *Arg_u8BrkPedlPsdRaw = MAIN_MSG_BRKPEDLPSD_INIT;
      local_u8ECM1AliveCounterRaw = MAIN_MSG_ECM1ALIVECOUNTER_INIT;
      local_u8ECM1ChecksumRaw = MAIN_MSG_ECM1CHECKSUM_INIT;
      *Arg_u8EngStActRaw = MAIN_MSG_ENGSTACT_INIT;
      local_u16EngTqIndActRaw = MAIN_MSG_ENGTQINDACT_INIT;
      local_u16EngTqIndDrvDmdRaw = MAIN_MSG_ENGTQINDDRVDMD_INIT;
      local_u16EngTqLossRaw = MAIN_MSG_ENGTQLOSS_INIT;
      *Arg_bHvacCluStsRaw = MAIN_MSG_HVACCLUSTS_INIT;
      local_u8ThrottleCmdPosRaw = MAIN_MSG_THROTTLECMDPOS_INIT;
   }


   /*AccrPedlRatPhys*/
   *Arg_u8AccrPedlRatRaw = local_u8AccrPedlRatRaw;
   if(local_u8AccrPedlRatRaw == MAIN_MSG_ACCRPEDLRAT_INIT)
   {
      *Arg_f32AccrPedlRatPhys = MAIN_MSG_ACCRPEDLRAT_NEUTRAL;
   }
   else
   {
      local_f32AccrPedlRatPhys = MAIN_MSG_SCALE_SIGNAL_RAW2PHYS(ACCRPEDLRAT, local_u8AccrPedlRatRaw);
      *Arg_f32AccrPedlRatPhys = MAIN_MSG_CLAMP_SIGNAL_PHYS(ACCRPEDLRAT, local_f32AccrPedlRatPhys);
   }


   /*ECM1AliveCounterPhys*/
   *Arg_u8ECM1AliveCounterRaw = local_u8ECM1AliveCounterRaw;
   if(local_u8ECM1AliveCounterRaw == MAIN_MSG_ECM1ALIVECOUNTER_INIT)
   {
      *Arg_f32ECM1AliveCounterPhys = MAIN_MSG_ECM1ALIVECOUNTER_NEUTRAL;
   }
   else
   {
      local_f32ECM1AliveCounterPhys = MAIN_MSG_SCALE_SIGNAL_RAW2PHYS(ECM1ALIVECOUNTER, local_u8ECM1AliveCounterRaw);
      *Arg_f32ECM1AliveCounterPhys = MAIN_MSG_CLAMP_SIGNAL_PHYS(ECM1ALIVECOUNTER, local_f32ECM1AliveCounterPhys);
   }


   /*ECM1ChecksumPhys*/
   *Arg_u8ECM1ChecksumRaw = local_u8ECM1ChecksumRaw;
   if(local_u8ECM1ChecksumRaw == MAIN_MSG_ECM1CHECKSUM_INIT)
   {
      *Arg_f32ECM1ChecksumPhys = MAIN_MSG_ECM1CHECKSUM_NEUTRAL;
   }
   else
   {
      local_f32ECM1ChecksumPhys = MAIN_MSG_SCALE_SIGNAL_RAW2PHYS(ECM1CHECKSUM, local_u8ECM1ChecksumRaw);
      *Arg_f32ECM1ChecksumPhys = MAIN_MSG_CLAMP_SIGNAL_PHYS(ECM1CHECKSUM, local_f32ECM1ChecksumPhys);
   }


   /*EngTqIndActPhys*/
   *Arg_u16EngTqIndActRaw = local_u16EngTqIndActRaw;
   if(local_u16EngTqIndActRaw == MAIN_MSG_ENGTQINDACT_INIT)
   {
      *Arg_f32EngTqIndActPhys = MAIN_MSG_ENGTQINDACT_NEUTRAL;
   }
   else
   {
      local_f32EngTqIndActPhys = MAIN_MSG_SCALE_SIGNAL_RAW2PHYS(ENGTQINDACT, local_u16EngTqIndActRaw);
      *Arg_f32EngTqIndActPhys = MAIN_MSG_CLAMP_SIGNAL_PHYS(ENGTQINDACT, local_f32EngTqIndActPhys);
   }


   /*EngTqIndDrvDmdPhys*/
   *Arg_u16EngTqIndDrvDmdRaw = local_u16EngTqIndDrvDmdRaw;
   if(local_u16EngTqIndDrvDmdRaw == MAIN_MSG_ENGTQINDDRVDMD_INIT)
   {
      *Arg_f32EngTqIndDrvDmdPhys = MAIN_MSG_ENGTQINDDRVDMD_NEUTRAL;
   }
   else
   {
      local_f32EngTqIndDrvDmdPhys = MAIN_MSG_SCALE_SIGNAL_RAW2PHYS(ENGTQINDDRVDMD, local_u16EngTqIndDrvDmdRaw);
      *Arg_f32EngTqIndDrvDmdPhys = MAIN_MSG_CLAMP_SIGNAL_PHYS(ENGTQINDDRVDMD, local_f32EngTqIndDrvDmdPhys);
   }


   /*EngTqLossPhys*/
   *Arg_u16EngTqLossRaw = local_u16EngTqLossRaw;
   if(local_u16EngTqLossRaw == MAIN_MSG_ENGTQLOSS_INIT)
   {
      *Arg_f32EngTqLossPhys = MAIN_MSG_ENGTQLOSS_NEUTRAL;
   }
   else
   {
      local_f32EngTqLossPhys = MAIN_MSG_SCALE_SIGNAL_RAW2PHYS(ENGTQLOSS, local_u16EngTqLossRaw);
      *Arg_f32EngTqLossPhys = MAIN_MSG_CLAMP_SIGNAL_PHYS(ENGTQLOSS, local_f32EngTqLossPhys);
   }


   /*ThrottleCmdPosPhys*/
   *Arg_u8ThrottleCmdPosRaw = local_u8ThrottleCmdPosRaw;
   if(local_u8ThrottleCmdPosRaw == MAIN_MSG_THROTTLECMDPOS_INIT)
   {
      *Arg_f32ThrottleCmdPosPhys = MAIN_MSG_THROTTLECMDPOS_NEUTRAL;
   }
   else
   {
      local_f32ThrottleCmdPosPhys = MAIN_MSG_SCALE_SIGNAL_RAW2PHYS(THROTTLECMDPOS, local_u8ThrottleCmdPosRaw);
      *Arg_f32ThrottleCmdPosPhys = MAIN_MSG_CLAMP_SIGNAL_PHYS(THROTTLECMDPOS, local_f32ThrottleCmdPosPhys);
   }
}


void MAIN_MSGvidRxECM2(
   boolean *Arg_bCrsCtrlCtrlActvRaw,
   float   *Arg_f32ECM2AliveCounterPhys,
   uint8   *Arg_u8ECM2AliveCounterRaw,
   float   *Arg_f32ECM2ChecksumPhys,
   uint8   *Arg_u8ECM2ChecksumRaw,
   float   *Arg_f32EngNPhys,
   uint16  *Arg_u16EngNRaw,
   float   *Arg_f32EngNTgtIdlePhys,
   uint16  *Arg_u16EngNTgtIdleRaw,
   uint8   *Arg_u8GearLmtForLightOffRaw)
{
   uint8   local_u8ECM2AliveCounterRaw;
   float   local_f32ECM2AliveCounterPhys;
   uint8   local_u8ECM2ChecksumRaw;
   float   local_f32ECM2ChecksumPhys;
   uint16  local_u16EngNRaw;
   float   local_f32EngNPhys;
   uint16  local_u16EngNTgtIdleRaw;
   float   local_f32EngNTgtIdlePhys;
   if (  (BSW_bCbkRxTOutFlag_SGECM2 == FALSE)
      || (MAIN_bMSGRxToutBenchOnC != FALSE)
      )
   {
      Com_ReceiveSignal(ComConf_ComSignal_SGCrsCtrlCtrlActv_289R, Arg_bCrsCtrlCtrlActvRaw);
      Com_ReceiveSignal(ComConf_ComSignal_SGECM2AliveCounter_289R, &local_u8ECM2AliveCounterRaw);
      Com_ReceiveSignal(ComConf_ComSignal_SGECM2Checksum_289R, &local_u8ECM2ChecksumRaw);
      Com_ReceiveSignal(ComConf_ComSignal_SGEngN_289R, &local_u16EngNRaw);
      Com_ReceiveSignal(ComConf_ComSignal_SGEngNTgtIdle_289R, &local_u16EngNTgtIdleRaw);
      Com_ReceiveSignal(ComConf_ComSignal_SGGearLmtForLightOff_289R, Arg_u8GearLmtForLightOffRaw);
   }
   else
   {
      *Arg_bCrsCtrlCtrlActvRaw = MAIN_MSG_CRSCTRLCTRLACTV_INIT;
      local_u8ECM2AliveCounterRaw = MAIN_MSG_ECM2ALIVECOUNTER_INIT;
      local_u8ECM2ChecksumRaw = MAIN_MSG_ECM2CHECKSUM_INIT;
      local_u16EngNRaw = MAIN_MSG_ENGN_INIT;
      local_u16EngNTgtIdleRaw = MAIN_MSG_ENGNTGTIDLE_INIT;
      *Arg_u8GearLmtForLightOffRaw = MAIN_MSG_GEARLMTFORLIGHTOFF_INIT;
   }


   /*ECM2AliveCounterPhys*/
   *Arg_u8ECM2AliveCounterRaw = local_u8ECM2AliveCounterRaw;
   if(local_u8ECM2AliveCounterRaw == MAIN_MSG_ECM2ALIVECOUNTER_INIT)
   {
      *Arg_f32ECM2AliveCounterPhys = MAIN_MSG_ECM2ALIVECOUNTER_NEUTRAL;
   }
   else
   {
      local_f32ECM2AliveCounterPhys = MAIN_MSG_SCALE_SIGNAL_RAW2PHYS(ECM2ALIVECOUNTER, local_u8ECM2AliveCounterRaw);
      *Arg_f32ECM2AliveCounterPhys = MAIN_MSG_CLAMP_SIGNAL_PHYS(ECM2ALIVECOUNTER, local_f32ECM2AliveCounterPhys);
   }


   /*ECM2ChecksumPhys*/
   *Arg_u8ECM2ChecksumRaw = local_u8ECM2ChecksumRaw;
   if(local_u8ECM2ChecksumRaw == MAIN_MSG_ECM2CHECKSUM_INIT)
   {
      *Arg_f32ECM2ChecksumPhys = MAIN_MSG_ECM2CHECKSUM_NEUTRAL;
   }
   else
   {
      local_f32ECM2ChecksumPhys = MAIN_MSG_SCALE_SIGNAL_RAW2PHYS(ECM2CHECKSUM, local_u8ECM2ChecksumRaw);
      *Arg_f32ECM2ChecksumPhys = MAIN_MSG_CLAMP_SIGNAL_PHYS(ECM2CHECKSUM, local_f32ECM2ChecksumPhys);
   }


   /*EngNPhys*/
   *Arg_u16EngNRaw = local_u16EngNRaw;
   if(local_u16EngNRaw == MAIN_MSG_ENGN_INIT)
   {
      *Arg_f32EngNPhys = MAIN_MSG_ENGN_NEUTRAL;
   }
   else
   {
      local_f32EngNPhys = MAIN_MSG_SCALE_SIGNAL_RAW2PHYS(ENGN, local_u16EngNRaw);
      *Arg_f32EngNPhys = MAIN_MSG_CLAMP_SIGNAL_PHYS(ENGN, local_f32EngNPhys);
   }


   /*EngNTgtIdlePhys*/
   *Arg_u16EngNTgtIdleRaw = local_u16EngNTgtIdleRaw;
   if(local_u16EngNTgtIdleRaw == MAIN_MSG_ENGNTGTIDLE_INIT)
   {
      *Arg_f32EngNTgtIdlePhys = MAIN_MSG_ENGNTGTIDLE_NEUTRAL;
   }
   else
   {
      local_f32EngNTgtIdlePhys = MAIN_MSG_SCALE_SIGNAL_RAW2PHYS(ENGNTGTIDLE, local_u16EngNTgtIdleRaw);
      *Arg_f32EngNTgtIdlePhys = MAIN_MSG_CLAMP_SIGNAL_PHYS(ENGNTGTIDLE, local_f32EngNTgtIdlePhys);
   }


}

void MAIN_MSGvidRxESC1(
   float   *Arg_f32AlgtPhys,
   sint16  *Arg_s16AlgtRaw,
   boolean *Arg_bEscFlgFltRaw,
   uint8   *Arg_u8GearShiftPrevnRaw,
   boolean *Arg_bTcsCtrlActvRaw,
   boolean *Arg_bTcsFlgFltRaw)
{
   sint16  local_s16AlgtRaw;
   float   local_f32AlgtPhys;
   if (  (BSW_bCbkRxTOutFlag_SGESC1 == FALSE)
      || (MAIN_bMSGRxToutBenchOnC != FALSE)
      )
   {
      Com_ReceiveSignal(ComConf_ComSignal_SGAlgt_561R, &local_s16AlgtRaw);
      Com_ReceiveSignal(ComConf_ComSignal_SGEscFlgFlt_561R, Arg_bEscFlgFltRaw);
      Com_ReceiveSignal(ComConf_ComSignal_SGGearShiftPrevn_561R, Arg_u8GearShiftPrevnRaw);
      Com_ReceiveSignal(ComConf_ComSignal_SGTcsCtrlActv_561R, Arg_bTcsCtrlActvRaw);
      Com_ReceiveSignal(ComConf_ComSignal_SGTcsFlgFlt_561R, Arg_bTcsFlgFltRaw);
   }
   else
   {
      local_s16AlgtRaw = MAIN_MSG_ALGT_INIT;
      *Arg_bEscFlgFltRaw = MAIN_MSG_ESCFLGFLT_INIT;
      *Arg_u8GearShiftPrevnRaw = MAIN_MSG_GEARSHIFTPREVN_INIT;
      *Arg_bTcsCtrlActvRaw = MAIN_MSG_TCSCTRLACTV_INIT;
      *Arg_bTcsFlgFltRaw = MAIN_MSG_TCSFLGFLT_INIT;
   }


   /*AlgtPhys*/
   *Arg_s16AlgtRaw = local_s16AlgtRaw;
   if(local_s16AlgtRaw == MAIN_MSG_ALGT_INIT)
   {
      *Arg_f32AlgtPhys = MAIN_MSG_ALGT_NEUTRAL;
   }
   else
   {
      local_f32AlgtPhys = MAIN_MSG_SCALE_SIGNAL_RAW2PHYS(ALGT, local_s16AlgtRaw);
      *Arg_f32AlgtPhys = MAIN_MSG_CLAMP_SIGNAL_PHYS(ALGT, local_f32AlgtPhys);
   }


}

void MAIN_MSGvidRxECM3(
   float   *Arg_f32EngineSoakTimePhys,
   uint16  *Arg_u16EngineSoakTimeRaw,
   float   *Arg_f32EngPAmbAirPhys,
   uint8   *Arg_u8EngPAmbAirRaw,
   float   *Arg_f32EngTPhys,
   uint8   *Arg_u8EngTRaw,
   boolean *Arg_bOBDDrivingCycleStatusRaw,
   boolean *Arg_bOBDWarmUpCycleStatusRaw)
{
   uint16  local_u16EngineSoakTimeRaw;
   float   local_f32EngineSoakTimePhys;
   uint8   local_u8EngPAmbAirRaw;
   float   local_f32EngPAmbAirPhys;
   uint8   local_u8EngTRaw;
   float   local_f32EngTPhys;
   if (  (BSW_bCbkRxTOutFlag_SGECM3 == FALSE)
      || (MAIN_bMSGRxToutBenchOnC != FALSE)
      )
   {
      Com_ReceiveSignal(ComConf_ComSignal_SGEngineSoakTime_609R, &local_u16EngineSoakTimeRaw);
      Com_ReceiveSignal(ComConf_ComSignal_SGEngPAmbAir_609R, &local_u8EngPAmbAirRaw);
      Com_ReceiveSignal(ComConf_ComSignal_SGEngT_609R, &local_u8EngTRaw);
      Com_ReceiveSignal(ComConf_ComSignal_SGOBDDrivingCycleStatus_609R, Arg_bOBDDrivingCycleStatusRaw);
      Com_ReceiveSignal(ComConf_ComSignal_SGOBDWarmUpCycleStatus_609R, Arg_bOBDWarmUpCycleStatusRaw);
   }
   else
   {
      local_u16EngineSoakTimeRaw = MAIN_MSG_ENGINESOAKTIME_INIT;
      local_u8EngPAmbAirRaw = MAIN_MSG_ENGPAMBAIR_INIT;
      local_u8EngTRaw = MAIN_MSG_ENGT_INIT;
      *Arg_bOBDDrivingCycleStatusRaw = MAIN_MSG_OBDDRIVINGCYCLESTATUS_INIT;
      *Arg_bOBDWarmUpCycleStatusRaw = MAIN_MSG_OBDWARMUPCYCLESTATUS_INIT;
   }


   /*EngineSoakTimePhys*/
   *Arg_u16EngineSoakTimeRaw = local_u16EngineSoakTimeRaw;
   if(local_u16EngineSoakTimeRaw == MAIN_MSG_ENGINESOAKTIME_INIT)
   {
      *Arg_f32EngineSoakTimePhys = MAIN_MSG_ENGINESOAKTIME_NEUTRAL;
   }
   else
   {
      local_f32EngineSoakTimePhys = MAIN_MSG_SCALE_SIGNAL_RAW2PHYS(ENGINESOAKTIME, local_u16EngineSoakTimeRaw);
      *Arg_f32EngineSoakTimePhys = MAIN_MSG_CLAMP_SIGNAL_PHYS(ENGINESOAKTIME, local_f32EngineSoakTimePhys);
   }


   /*EngPAmbAirPhys*/
   *Arg_u8EngPAmbAirRaw = local_u8EngPAmbAirRaw;
   if(local_u8EngPAmbAirRaw == MAIN_MSG_ENGPAMBAIR_INIT)
   {
      *Arg_f32EngPAmbAirPhys = MAIN_MSG_ENGPAMBAIR_NEUTRAL;
   }
   else
   {
      local_f32EngPAmbAirPhys = MAIN_MSG_SCALE_SIGNAL_RAW2PHYS(ENGPAMBAIR, local_u8EngPAmbAirRaw);
      *Arg_f32EngPAmbAirPhys = MAIN_MSG_CLAMP_SIGNAL_PHYS(ENGPAMBAIR, local_f32EngPAmbAirPhys);
   }


   /*EngTPhys*/
   *Arg_u8EngTRaw = local_u8EngTRaw;
   if(local_u8EngTRaw == MAIN_MSG_ENGT_INIT)
   {
      *Arg_f32EngTPhys = MAIN_MSG_ENGT_NEUTRAL;
   }
   else
   {
      local_f32EngTPhys = MAIN_MSG_SCALE_SIGNAL_RAW2PHYS(ENGT, local_u8EngTRaw);
      *Arg_f32EngTPhys = MAIN_MSG_CLAMP_SIGNAL_PHYS(ENGT, local_f32EngTPhys);
   }


}

void MAIN_MSGvidRxIP1(
   float   *Arg_f32AmbAirTempPhys,
   uint8   *Arg_u8AmbAirTempRaw)
{
   uint8   local_u8AmbAirTempRaw;
   float   local_f32AmbAirTempPhys;


   if (  (BSW_bCbkRxTOutFlag_SGIP1 == FALSE)
      || (MAIN_bMSGRxToutBenchOnC != FALSE)
      )
   {
      Com_ReceiveSignal(ComConf_ComSignal_SGAmbAirTemp_641R, &local_u8AmbAirTempRaw);
   }
   else
   {
      local_u8AmbAirTempRaw = MAIN_MSG_AMBAIRTEMP_INIT;
   }


   /*AmbAirTempPhys*/
   *Arg_u8AmbAirTempRaw = local_u8AmbAirTempRaw;
   if(local_u8AmbAirTempRaw == MAIN_MSG_AMBAIRTEMP_INIT)
   {
      *Arg_f32AmbAirTempPhys = MAIN_MSG_AMBAIRTEMP_NEUTRAL;
   }
   else
   {
      local_f32AmbAirTempPhys = MAIN_MSG_SCALE_SIGNAL_RAW2PHYS(AMBAIRTEMP, local_u8AmbAirTempRaw);
      *Arg_f32AmbAirTempPhys = MAIN_MSG_CLAMP_SIGNAL_PHYS(AMBAIRTEMP, local_f32AmbAirTempPhys);
   }
}

void MAIN_MSGvidTxTCU1(
   float   Arg_f32EngNIdleReqPhys,
   uint8  *Arg_u8EngNIdleReqRaw,
   float   Arg_f32EngTqIndDecReqdByTrsmPhys,
   uint8  *Arg_u8EngTqIndDecReqdByTrsmRaw,
   float   Arg_f32EngTqIndLmtdByTrsmPhys,
   uint8  *Arg_u8EngTqIndLmtdByTrsmRaw,
   uint8   Arg_u8TrsmCluStActRaw,
   float   Arg_f32TrsmMsgCntPhys,
   uint8  *Arg_u8TrsmMsgCntRaw,
   float   Arg_f32TrsmNInpPhys,
   uint16 *Arg_u16TrsmNInpRaw)
{
   uint8   local_u8EngNIdleReqRaw;
   sint32  local_s32EngNIdleReq;
   float   local_f32EngNIdleReqPhys1;
   float   local_f32EngNIdleReqPhys2;
   uint8   local_u8EngTqIndDecReqdByTrsmRaw;
   sint32  local_s32EngTqIndDecReqdByTrsm;
   float   local_f32EngTqIndDecReqdByTrsmPhys1;
   float   local_f32EngTqIndDecReqdByTrsmPhys2;
   uint8   local_u8EngTqIndLmtdByTrsmRaw;
   sint32  local_s32EngTqIndLmtdByTrsm;
   float   local_f32EngTqIndLmtdByTrsmPhys1;
   float   local_f32EngTqIndLmtdByTrsmPhys2;
   uint8   local_u8TrsmMsgCntRaw;
   sint32  local_s32TrsmMsgCnt;
   float   local_f32TrsmMsgCntPhys1;
   float   local_f32TrsmMsgCntPhys2;
   uint16  local_u16TrsmNInpRaw;
   sint32  local_s32TrsmNInp;
   float   local_f32TrsmNInpPhys1;
   float   local_f32TrsmNInpPhys2;


   local_f32EngNIdleReqPhys1 = MAIN_MSG_CLAMP_SIGNAL_PHYS(ENGNIDLEREQ, Arg_f32EngNIdleReqPhys);
   local_f32EngNIdleReqPhys2 = MAIN_MSG_SCALE_SIGNAL_PHYS2RAW(ENGNIDLEREQ, local_f32EngNIdleReqPhys1);
   local_s32EngNIdleReq = F32SRV_s32F32ToSint32(local_f32EngNIdleReqPhys2, SINT32_MIN, SINT32_MAX, 0);
   local_u8EngNIdleReqRaw = (uint8)(local_s32EngNIdleReq);
   *Arg_u8EngNIdleReqRaw = local_u8EngNIdleReqRaw;


   local_f32EngTqIndDecReqdByTrsmPhys1 = MAIN_MSG_CLAMP_SIGNAL_PHYS(ENGTQINDDECREQDBYTRSM, Arg_f32EngTqIndDecReqdByTrsmPhys);
   local_f32EngTqIndDecReqdByTrsmPhys2 = MAIN_MSG_SCALE_SIGNAL_PHYS2RAW(ENGTQINDDECREQDBYTRSM, local_f32EngTqIndDecReqdByTrsmPhys1);
   local_s32EngTqIndDecReqdByTrsm = F32SRV_s32F32ToSint32(local_f32EngTqIndDecReqdByTrsmPhys2, SINT32_MIN, SINT32_MAX, 0);
   local_u8EngTqIndDecReqdByTrsmRaw = (uint8)(local_s32EngTqIndDecReqdByTrsm);
   *Arg_u8EngTqIndDecReqdByTrsmRaw = local_u8EngTqIndDecReqdByTrsmRaw;


   local_f32EngTqIndLmtdByTrsmPhys1 = MAIN_MSG_CLAMP_SIGNAL_PHYS(ENGTQINDLMTDBYTRSM, Arg_f32EngTqIndLmtdByTrsmPhys);
   local_f32EngTqIndLmtdByTrsmPhys2 = MAIN_MSG_SCALE_SIGNAL_PHYS2RAW(ENGTQINDLMTDBYTRSM, local_f32EngTqIndLmtdByTrsmPhys1);
   local_s32EngTqIndLmtdByTrsm = F32SRV_s32F32ToSint32(local_f32EngTqIndLmtdByTrsmPhys2, SINT32_MIN, SINT32_MAX, 0);
   local_u8EngTqIndLmtdByTrsmRaw = (uint8)(local_s32EngTqIndLmtdByTrsm);
   *Arg_u8EngTqIndLmtdByTrsmRaw = local_u8EngTqIndLmtdByTrsmRaw;


   local_f32TrsmMsgCntPhys1 = MAIN_MSG_CLAMP_SIGNAL_PHYS(TRSMMSGCNT, Arg_f32TrsmMsgCntPhys);
   local_f32TrsmMsgCntPhys2 = MAIN_MSG_SCALE_SIGNAL_PHYS2RAW(TRSMMSGCNT, local_f32TrsmMsgCntPhys1);
   local_s32TrsmMsgCnt = F32SRV_s32F32ToSint32(local_f32TrsmMsgCntPhys2, SINT32_MIN, SINT32_MAX, 0);
   local_u8TrsmMsgCntRaw = (uint8)(local_s32TrsmMsgCnt);
   *Arg_u8TrsmMsgCntRaw = local_u8TrsmMsgCntRaw;


   local_f32TrsmNInpPhys1 = MAIN_MSG_CLAMP_SIGNAL_PHYS(TRSMNINP, Arg_f32TrsmNInpPhys);
   local_f32TrsmNInpPhys2 = MAIN_MSG_SCALE_SIGNAL_PHYS2RAW(TRSMNINP, local_f32TrsmNInpPhys1);
   local_s32TrsmNInp = F32SRV_s32F32ToSint32(local_f32TrsmNInpPhys2, SINT32_MIN, SINT32_MAX, 0);
   local_u16TrsmNInpRaw = (uint16)(local_s32TrsmNInp);
   *Arg_u16TrsmNInpRaw = local_u16TrsmNInpRaw;


   Com_SendSignal(ComConf_ComSignal_SGEngNIdleReq_321T, &local_u8EngNIdleReqRaw);
   Com_SendSignal(ComConf_ComSignal_SGEngTqIndDecReqdByTrsm_321T, &local_u8EngTqIndDecReqdByTrsmRaw);
   Com_SendSignal(ComConf_ComSignal_SGEngTqIndLmtdByTrsm_321T, &local_u8EngTqIndLmtdByTrsmRaw);
   Com_SendSignal(ComConf_ComSignal_SGTrsmCluStAct_321T, &Arg_u8TrsmCluStActRaw);
   Com_SendSignal(ComConf_ComSignal_SGTrsmMsgCnt_321T, &local_u8TrsmMsgCntRaw);
   Com_SendSignal(ComConf_ComSignal_SGTrsmNInp_321T, &local_u16TrsmNInpRaw);
}

void MAIN_MSGvidTxTCU2(
   float   Arg_f32EngTqIndIncReqdByTrsmPhys,
   uint8  *Arg_u8EngTqIndIncReqdByTrsmRaw,
   uint8   Arg_u8TrsmFlgFltRaw,
   boolean Arg_bTrsmFlgShiftProgsRaw,
   uint8   Arg_u8TrsmGearActRaw,
   uint8   Arg_u8TrsmGearTarRaw,
   boolean Arg_bTrsmMILReqRaw,
   uint8   Arg_u8TrsmStGearLvrRaw,
   uint8   Arg_u8TrsmStGearModeRaw,
   float   Arg_f32TrsmTOilPhys,
   uint8  *Arg_u8TrsmTOilRaw,
   boolean Arg_bTrsmTOilWrnLmpReqRaw)
{
   uint8   local_u8EngTqIndIncReqdByTrsmRaw;
   sint32  local_s32EngTqIndIncReqdByTrsm;
   float   local_f32EngTqIndIncReqdByTrsmPhys1;
   float   local_f32EngTqIndIncReqdByTrsmPhys2;
   uint8   local_u8TrsmTOilRaw;
   sint32  local_s32TrsmTOil;
   float   local_f32TrsmTOilPhys1;
   float   local_f32TrsmTOilPhys2;
   local_f32EngTqIndIncReqdByTrsmPhys1 = MAIN_MSG_CLAMP_SIGNAL_PHYS(ENGTQINDINCREQDBYTRSM, Arg_f32EngTqIndIncReqdByTrsmPhys);
   local_f32EngTqIndIncReqdByTrsmPhys2 = MAIN_MSG_SCALE_SIGNAL_PHYS2RAW(ENGTQINDINCREQDBYTRSM, local_f32EngTqIndIncReqdByTrsmPhys1);
   local_s32EngTqIndIncReqdByTrsm = F32SRV_s32F32ToSint32(local_f32EngTqIndIncReqdByTrsmPhys2, SINT32_MIN, SINT32_MAX, 0);
   local_u8EngTqIndIncReqdByTrsmRaw = (uint8)(local_s32EngTqIndIncReqdByTrsm);
   *Arg_u8EngTqIndIncReqdByTrsmRaw = local_u8EngTqIndIncReqdByTrsmRaw;


   local_f32TrsmTOilPhys1 = MAIN_MSG_CLAMP_SIGNAL_PHYS(TRSMTOIL, Arg_f32TrsmTOilPhys);
   local_f32TrsmTOilPhys2 = MAIN_MSG_SCALE_SIGNAL_PHYS2RAW(TRSMTOIL, local_f32TrsmTOilPhys1);
   local_s32TrsmTOil = F32SRV_s32F32ToSint32(local_f32TrsmTOilPhys2, SINT32_MIN, SINT32_MAX, 0);
   local_u8TrsmTOilRaw = (uint8)(local_s32TrsmTOil);
   *Arg_u8TrsmTOilRaw = local_u8TrsmTOilRaw;


   Com_SendSignal(ComConf_ComSignal_SGEngTqIndIncReqdByTrsm_337T, &local_u8EngTqIndIncReqdByTrsmRaw);
   Com_SendSignal(ComConf_ComSignal_SGTrsmFlgFlt_337T, &Arg_u8TrsmFlgFltRaw);
   Com_SendSignal(ComConf_ComSignal_SGTrsmFlgShiftProgs_337T, &Arg_bTrsmFlgShiftProgsRaw);
   Com_SendSignal(ComConf_ComSignal_SGTrsmGearAct_337T, &Arg_u8TrsmGearActRaw);
   Com_SendSignal(ComConf_ComSignal_SGTrsmGearTar_337T, &Arg_u8TrsmGearTarRaw);
   Com_SendSignal(ComConf_ComSignal_SGTrsmMILReq_337T, &Arg_bTrsmMILReqRaw);
   Com_SendSignal(ComConf_ComSignal_SGTrsmStGearLvr_337T, &Arg_u8TrsmStGearLvrRaw);
   Com_SendSignal(ComConf_ComSignal_SGTrsmStGearMode_337T, &Arg_u8TrsmStGearModeRaw);
   Com_SendSignal(ComConf_ComSignal_SGTrsmTOil_337T, &local_u8TrsmTOilRaw);
   Com_SendSignal(ComConf_ComSignal_SGTrsmTOilWrnLmpReq_337T, &Arg_bTrsmTOilWrnLmpReqRaw);
}



#define MAIN_STOP_SEC_CODE
#include "MAIN_MemMap.h"


/*-------------------------------- end of file -------------------------------*/
