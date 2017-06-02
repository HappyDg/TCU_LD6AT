/******************************************************************************/
/* !Layer           : APPLI                                                   */
/* !Component       : TST_CAN                                                 */
/* !Description     : Test of CAN component                                   */
/*                                                                            */
/* !File            : TST_CAN.c                                               */
/* !Description     : Test of CAN component APIs                              */
/*                                                                            */
/* !Reference       :                                                         */
/*                                                                            */
/* Coding language  : C                                                       */
/*                                                                            */
/* COPYRIGHT VALEO all rights reserved                                        */
/******************************************************************************/
/* Dimension Informations
 * %PCMS_HEADER_SUBSTITUTION_START:%
 * The PID has this format: <Product ID>:<Item ID>.<Variant>-<Item Type>;<Revision>
 * %PID:%
 * %PCMS_HEADER_SUBSTITUTION_END:%
 ******************************************************************************/

#include "Std_Types.h"

#include "TST_CANAPI.h"
#include "MAIN_Msg.h"
#include "MAIN_L.h"
#include "SWTST_L.h"

#define TST_START_SEC_TST_CODE
#include "TST_MemMap.h"

void TST_CANAPI_vidInit(void)
{
   TST_bEnableTestPhys = 0;
	
	/* ========================================================================== */
	 /* TCU CAN API Test Init												  */
	 /* ========================================================================== */
	 /* 0x211: ABS1 */
	 TST_0x211_f32WhlSpdFrntLeRawPhys = MAIN_MSG_WHLSPDFRNTLERAW_NEUTRAL;
	 TST_0x211_f32WhlSpdFrntRiRawPhys = MAIN_MSG_WHLSPDFRNTRIRAW_NEUTRAL;
	 TST_0x211_f32WhlSpdReLeRawPhys = MAIN_MSG_WHLSPDRELERAW_NEUTRAL;
	 TST_0x211_f32WhlSpdReRiRawPhys = MAIN_MSG_WHLSPDRERIRAW_NEUTRAL;
	 /* 0x221: ABS2 */
	 TST_0x221_bAbsCtrlActv = MAIN_MSG_ABSCTRLACTV_INIT;
	 TST_0x221_bAbsFlgFlt = MAIN_MSG_ABSFLGFLT_INIT;
	 TST_0x221_bEbdFlgFlt = MAIN_MSG_EBDFLGFLT_INIT;
	 /* 0x111: ECM1 */
	 TST_0x111_f32AccrPedlRatPhys = MAIN_MSG_ACCRPEDLRAT_NEUTRAL;
	 TST_0x111_u8BrkPedlPsd = MAIN_MSG_BRKPEDLPSD_INIT;
	 TST_0x111_u8ECM1AliveCounter = MAIN_MSG_ECM1ALIVECOUNTER_INIT;
	 TST_0x111_u8ECM1Checksum = MAIN_MSG_ECM1CHECKSUM_INIT;
	 TST_0x111_u8EngStAct = MAIN_MSG_ENGSTACT_INIT;
	 TST_0x111_f32EngTqIndActPhys = MAIN_MSG_ENGTQINDACT_NEUTRAL;
	 TST_0x111_f32EngTqIndDrvDmdPhys = MAIN_MSG_ENGTQINDDRVDMD_NEUTRAL;
	 TST_0x111_f32EngTqLossPhys = MAIN_MSG_ENGTQLOSS_NEUTRAL;
	 TST_0x111_bHvacCluSts = MAIN_MSG_HVACCLUSTS_INIT;
	 TST_0x111_f32ThrottleCmdPosPhys = MAIN_MSG_THROTTLECMDPOS_NEUTRAL;
	 /* 0x121: ECM2 */
	 TST_0x121_bCrsCtrlCtrlActv = MAIN_MSG_CRSCTRLCTRLACTV_INIT;
	 TST_0x121_u8ECM2AliveCounter = MAIN_MSG_ECM2ALIVECOUNTER_INIT;
	 TST_0x121_u8ECM2Checksum = MAIN_MSG_ECM2CHECKSUM_INIT;
	 TST_0x121_f32EngNPhys = MAIN_MSG_ENGN_NEUTRAL;
	 TST_0x121_f32EngNTgtIdlePhys = MAIN_MSG_ENGNTGTIDLE_NEUTRAL;
	 TST_0x121_u8GearLmtForLightOff = MAIN_MSG_GEARLMTFORLIGHTOFF_INIT;
	 /* 0x231: ESC1 */
	 TST_0x231_f32AlgtPhys = MAIN_MSG_ALGT_NEUTRAL;
	 TST_0x231_bEscFlgFlt = MAIN_MSG_ESCFLGFLT_INIT;
	 TST_0x231_u8GearShiftPrevn = MAIN_MSG_GEARSHIFTPREVN_INIT;
	 TST_0x231_bTcsCtrlActv = MAIN_MSG_TCSCTRLACTV_INIT;
	 TST_0x231_bTcsFlgFlt = MAIN_MSG_TCSFLGFLT_INIT;
	 /* 0x261: ECM3 */
	 TST_0x261_u16EngineSoakTime = MAIN_MSG_ENGINESOAKTIME_INIT;
	 TST_0x261_u8EngPAmbAir = MAIN_MSG_ENGPAMBAIR_INIT;
	 TST_0x261_f32EngTPhys = MAIN_MSG_ENGT_NEUTRAL;
	 TST_0x261_bOBDDrivingCycleStatus = MAIN_MSG_OBDDRIVINGCYCLESTATUS_INIT;
	 TST_0x261_bOBDWarmUpCycleStatus = MAIN_MSG_OBDWARMUPCYCLESTATUS_INIT;
	 /* 0x281: IP1 */
	 TST_0x281_f32AmbAirTempPhys = MAIN_MSG_AMBAIRTEMP_NEUTRAL;
	 /* 0x141: TCU1 */
	 TST_0x141_f32EngNIdleReqPhys = MAIN_MSG_ENGNIDLEREQ_NEUTRAL;
	 TST_0x141_f32EngTqIndDecReqdByTrsmPhys = MAIN_MSG_ENGTQINDDECREQDBYTRSM_NEUTRAL;
	 TST_0x141_f32EngTqIndLmtdByTrsmPhys = MAIN_MSG_ENGTQINDLMTDBYTRSM_NEUTRAL;
	 TST_0x141_u8TrsmCluStAct = MAIN_MSG_TRSMCLUSTACT_INIT;
	 TST_0x141_u8TrsmMsgCnt = MAIN_MSG_TRSMMSGCNT_INIT;
	 TST_0x141_u16TrsmNInp = MAIN_MSG_TRSMNINP_INIT;
	 /* 0x151: TCU2 */
	 TST_0x151_f32EngTqIndIncReqdByTrsmPhys = MAIN_MSG_ENGTQINDINCREQDBYTRSM_NEUTRAL;
	 TST_0x151_u8TrsmFlgFlt = MAIN_MSG_TRSMFLGFLT_INIT;
	 TST_0x151_bTrsmFlgShiftProgs = MAIN_MSG_TRSMFLGSHIFTPROGS_INIT;
	 TST_0x151_u8TrsmGearAct = MAIN_MSG_TRSMGEARACT_INIT;
	 TST_0x151_u8TrsmGearTar = MAIN_MSG_TRSMGEARTAR_INIT;
	 TST_0x151_bTrsmMILReq = MAIN_MSG_TRSMMILREQ_INIT;
	 TST_0x151_u8TrsmStGearLvr = MAIN_MSG_TRSMSTGEARLVR_INIT;
	 TST_0x151_u8TrsmStGearMode = MAIN_MSG_TRSMSTGEARMODE_INIT;
	 TST_0x151_f32TrsmTOilPhys = MAIN_MSG_TRSMTOIL_NEUTRAL;
	 TST_0x151_bTrsmTOilWrnLmpReq = MAIN_MSG_TRSMTOILWRNLMPREQ_INIT;
}

void TST_vidTestCanApi( void )
{
   if (TST_bEnableTestPhys == 1)
   {
	
	       /* ========================================================================== */
		/* TCU CAN API Test 												*/
		/* ========================================================================== */
		//Message 0x211: ABS1 , Direction Rx , signal Read
		TST_0x211_f32WhlSpdFrntLeRawPhys = CANAPI_udtRead_WhlSpdFrntLeRaw();
		TST_0x211_f32WhlSpdFrntRiRawPhys = CANAPI_udtRead_WhlSpdFrntRiRaw();
		TST_0x211_f32WhlSpdReLeRawPhys = CANAPI_udtRead_WhlSpdReLeRaw();
		TST_0x211_f32WhlSpdReRiRawPhys = CANAPI_udtRead_WhlSpdReRiRaw();
	
		//Message 0x221: ABS2 , Direction Rx , signal Read
		TST_0x221_bAbsCtrlActv = CANAPI_udtRead_AbsCtrlActv();
		TST_0x221_bAbsFlgFlt = CANAPI_udtRead_AbsFlgFlt();
		TST_0x221_bEbdFlgFlt = CANAPI_udtRead_EbdFlgFlt();
	
		//Message 0x111: ECM1 , Direction Rx , signal Read
		TST_0x111_f32AccrPedlRatPhys = CANAPI_udtRead_AccrPedlRat();
		TST_0x111_u8BrkPedlPsd = CANAPI_udtRead_BrkPedlPsd();
		TST_0x111_u8ECM1AliveCounter = CANAPI_udtRead_ECM1AliveCounter();
		TST_0x111_u8ECM1Checksum = CANAPI_udtRead_ECM1Checksum();
		TST_0x111_u8EngStAct = CANAPI_udtRead_EngStAct();
		TST_0x111_f32EngTqIndActPhys = CANAPI_udtRead_EngTqIndAct();
		TST_0x111_f32EngTqIndDrvDmdPhys = CANAPI_udtRead_EngTqIndDrvDmd();
		TST_0x111_f32EngTqLossPhys = CANAPI_udtRead_EngTqLoss();
		TST_0x111_bHvacCluSts = CANAPI_udtRead_HvacCluSts();
		TST_0x111_f32ThrottleCmdPosPhys = CANAPI_udtRead_ThrottleCmdPos();
	
		//Message 0x121: ECM2 , Direction Rx , signal Read
		TST_0x121_bCrsCtrlCtrlActv = CANAPI_udtRead_CrsCtrlCtrlActv();
		TST_0x121_u8ECM2AliveCounter = CANAPI_udtRead_ECM2AliveCounter();
		TST_0x121_u8ECM2Checksum = CANAPI_udtRead_ECM2Checksum();
		TST_0x121_f32EngNPhys = CANAPI_udtRead_EngN();
		TST_0x121_f32EngNTgtIdlePhys = CANAPI_udtRead_EngNTgtIdle();
		TST_0x121_u8GearLmtForLightOff = CANAPI_udtRead_GearLmtForLightOff();
	
		//Message 0x231: ESC1 , Direction Rx , signal Read
		TST_0x231_f32AlgtPhys = CANAPI_udtRead_Algt();
		TST_0x231_bEscFlgFlt = CANAPI_udtRead_EscFlgFlt();
		TST_0x231_u8GearShiftPrevn = CANAPI_udtRead_GearShiftPrevn();
		TST_0x231_bTcsCtrlActv = CANAPI_udtRead_TcsCtrlActv();
		TST_0x231_bTcsFlgFlt = CANAPI_udtRead_TcsFlgFlt();
	
		//Message 0x261: ECM3 , Direction Rx , signal Read
		TST_0x261_u16EngineSoakTime = CANAPI_udtRead_EngineSoakTime();
		TST_0x261_u8EngPAmbAir = CANAPI_udtRead_EngPAmbAir();
		TST_0x261_f32EngTPhys = CANAPI_udtRead_EngT();
		TST_0x261_bOBDDrivingCycleStatus = CANAPI_udtRead_OBDDrivingCycleStatus();
		TST_0x261_bOBDWarmUpCycleStatus = CANAPI_udtRead_OBDWarmUpCycleStatus();
	
		//Message 0x281: IP1 , Direction Rx , signal Read
		TST_0x281_f32AmbAirTempPhys = CANAPI_udtRead_AmbAirTemp();
	
		//Message 0x141: TCU1 , Direction Tx , signal Write
		CANAPI_udtWrite_EngNIdleReq(TST_0x141_f32EngNIdleReqPhys);
		CANAPI_udtWrite_EngTqIndDecReqdByTrsm(TST_0x141_f32EngTqIndDecReqdByTrsmPhys);
		CANAPI_udtWrite_EngTqIndLmtdByTrsm(TST_0x141_f32EngTqIndLmtdByTrsmPhys);
		CANAPI_udtWrite_TrsmCluStAct(TST_0x141_u8TrsmCluStAct);
		CANAPI_udtWrite_TrsmMsgCnt(TST_0x141_u8TrsmMsgCnt);
		CANAPI_udtWrite_TrsmNInp(TST_0x141_u16TrsmNInp);
	
		//Message 0x151: TCU2 , Direction Tx , signal Write
		CANAPI_udtWrite_EngTqIndIncReqdByTrsm(TST_0x151_f32EngTqIndIncReqdByTrsmPhys);
		CANAPI_udtWrite_TrsmFlgFlt(TST_0x151_u8TrsmFlgFlt);
		CANAPI_udtWrite_TrsmFlgShiftProgs(TST_0x151_bTrsmFlgShiftProgs);
		CANAPI_udtWrite_TrsmGearAct(TST_0x151_u8TrsmGearAct);
		CANAPI_udtWrite_TrsmGearTar(TST_0x151_u8TrsmGearTar);
		CANAPI_udtWrite_TrsmMILReq(TST_0x151_bTrsmMILReq);
		CANAPI_udtWrite_TrsmStGearLvr(TST_0x151_u8TrsmStGearLvr);
		CANAPI_udtWrite_TrsmStGearMode(TST_0x151_u8TrsmStGearMode);
		CANAPI_udtWrite_TrsmTOil(TST_0x151_f32TrsmTOilPhys);
		CANAPI_udtWrite_TrsmTOilWrnLmpReq(TST_0x151_bTrsmTOilWrnLmpReq);
   
   }
   else
   {
   }
}

#define TST_STOP_SEC_TST_CODE
#include "TST_MemMap.h"

/*------------------------------- end of file --------------------------------*/
