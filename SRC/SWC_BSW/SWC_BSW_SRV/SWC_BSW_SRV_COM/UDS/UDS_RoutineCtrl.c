/******************************************************************************/
/*                                                                            */
/* !Layer           : SRV                                                     */
/*                                                                            */
/* !Component       : UDS                                                     */
/* !Description     : 								                                 */
/*                                                                            */
/* !File            : UDS.RoutineCtrl.c                                       */
/*                                                                            */
/* !Scope           : Public                                                  */
/*                                                                            */
/* !Target          : All                                                     */
/*                                                                            */
/* !Vendor          : Valeo                                                   */
/*                                                                            */
/* Coding language  : C                                                       */
/*                                                                            */
/* COPYRIGHT 2011 VALEO                                                       */
/* all rights reserved                                                        */
/*                                                                            */
/******************************************************************************/
/* PVCS Information                                                           */
/* $Archive:                                                                 $*/
/* $Revision::            $$Author::                  $$Date::               $*/
/******************************************************************************/
/* !VnrOff :                                                                  */
/******************************************************************************/
/******************************************************************************/

#include "Std_Types.h"
#include "Dcm_Types.h" 
#include "UDS.h"


#define UDS_START_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bRcStartProgCond                                        */
/* !Description : RID 0203                                                    */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE)UDS_bRcStartProgCond(
   Dcm_OpStatusType OpStatus,
   P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA)pMsgContext,
   P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode)
{
    /* No preconditions requested */
    return E_OK;
}

#define UDS_STOP_SEC_CODE
#include "MemMap.h"