/* *****************************************************************************/
/*                                                                             */
/* !Layer          : Layer                                                    */
/*                                                                            */
/* !Component      : Component                                                */
/* !Description    : Component description                                    */
/*                                                                            */
/* !Module         : MODULE                                                   */
/* !Description    : MODULE description                                       */
/*                                                                            */
/* !File           : MAIN_WriteCan.h                                          */
/*                                                                            */
/* !Scope          : Public                                                   */
/*                                                                            */
/* !Target         : Infineon_tc27x                                           */
/*                                                                            */
/* !Vendor         : VALEO                                                    */
/*                                                                            */
/* !Author         : J. ZHANG                                                 */
/*                                                                            */
/* Coding language : C                                                        */
/*                                                                            */
/* COPYRIGHT 2016 VALEO                                                       */
/* all rights reserved                                                        */
/*                                                                            */
/* ****************************************************************************/
/* PVCS Information                                                           */
/* $Archive::   $                                                             */
/* $Revision::  $                                                             */
/* ****************************************************************************/
/* !VnrOff :                                                                  */
/* ****************************************************************************/
#ifndef MAIN_WRITE_CAN_H
#define MAIN_WRITE_CAN_H

#include "CAN_API.h"

#define MAIN_START_SEC_CODE
#include "MAIN_MemMap.h"

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

/* ****************************************************************************/
/*                                                                            */
/* !$item_header $item_name                                                   */
/* !Trigger     :                                                             */
/* !Description :                                                             */
/* !Number      :                                                             */
/* !Reference   : NONE                                                        */
/*                                                                            */
/* ****************************************************************************/
inline void Main_vidCAN_SngSetVle(void)
{

	/*TCU Tx global set*/
	CANAPI_udtWrite_EngNIdleReq(EngNIdleReq);
	CANAPI_udtWrite_EngTqIndDecReqdByTrsm(EngTqIndDecReqdByTrsm);
	CANAPI_udtWrite_EngTqIndLmtdByTrsm(EngTqIndLmtdByTrsm);
	CANAPI_udtWrite_TrsmCluStAct(TrsmCluStAct);
	CANAPI_udtWrite_TrsmMsgCnt(TrsmMsgCnt);
	CANAPI_udtWrite_TrsmNInp(TrsmNInp);
	CANAPI_udtWrite_EngTqIndIncReqdByTrsm(EngTqIndIncReqdByTrsm);
	CANAPI_udtWrite_TrsmFlgFlt(TrsmFlgFlt);
	CANAPI_udtWrite_TrsmFlgShiftProgs(TrsmFlgShiftProgs);
	CANAPI_udtWrite_TrsmGearAct(TrsmGearAct);
	CANAPI_udtWrite_TrsmGearTar(TrsmGearTar);
	CANAPI_udtWrite_TrsmMILReq(TrsmMILReq);
	CANAPI_udtWrite_TrsmStGearLvr(TrsmStGearLvr);
	CANAPI_udtWrite_TrsmStGearMode(TrsmStGearMode);
	CANAPI_udtWrite_TrsmTOil(TrsmTOil);
	CANAPI_udtWrite_TrsmTOilWrnLmpReq(TrsmTOilWrnLmpReq);
}

#define MAIN_STOP_SEC_CODE
#include "MAIN_MemMap.h"

#endif /* MAIN_WRITE_CAN_H */
/*-------------------------------- end of file -------------------------------*/
