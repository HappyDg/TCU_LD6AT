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
/* !File           : MAIN_WriteDcdcApi.h                                   */
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
#ifndef MAIN_WRITE_DCDCAPI_H
#define MAIN_WRITE_DCDCAPI_H

//#include "DCDCAPI_Api.h"

#define  MAIN_START_SEC_CODE
#include "MAIN_MemMap.h"

extern uint8 CntrlCmdApmDirReq;
extern boolean CntrlCmdApmPrechReq;
extern uint8 CntrlCmdApmImaxReq;
extern float CntrlCmdApmUregReq;
extern float CntrlCmdApmUprechReq;
extern boolean CntrlCmdApmCanComStat;
/* ****************************************************************************/
/*                                                                            */
/* !$item_header $item_name                                                   */
/* !Trigger     :                                                             */
/* !Description :                                                             */
/* !Number      :                                                             */
/* !Reference   : NONE                                                        */
/*                                                                            */
/* ****************************************************************************/
inline void Main_vidDCDCAPI_SngSetVle(void)
{

   DCDCAPI_udtWrite_CntrlCmdApmDirReq(CntrlCmdApmDirReq);
   DCDCAPI_udtWrite_CntrlCmdApmPrechReq(CntrlCmdApmPrechReq);
   DCDCAPI_udtWrite_CntrlCmdApmImaxReq(CntrlCmdApmImaxReq);
   DCDCAPI_udtWrite_CntrlCmdApmUregReq(CntrlCmdApmUregReq);
   DCDCAPI_udtWrite_CntrlCmdApmUprechReq(CntrlCmdApmUprechReq);
   DCDCAPI_udtWrite_CntrlCmdApmCanComStat(CntrlCmdApmCanComStat);
}

#define MAIN_STOP_SEC_CODE
#include "MAIN_MemMap.h"

#endif /* MAIN_WRITE_DCDCAPI_H */
/*-------------------------------- end of file -------------------------------*/
