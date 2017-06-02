/******************************************************************************/
/*                                                                            */
/* !Layer           : SRV                                                     */
/*                                                                            */
/* !Component       : UDS                                                     */
/* !Description     :                                                         */
/*                                                                            */
/* !File            : UDS_DtcSetting.c                                        */
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
//#include "DSM_Drv.h"


#define UDS_START_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bDtcSettingOn                                           */
/* !Description : Activation of fault detections                              */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
void UDS_vidDtcSettingOn(void)
{
   //FaultEnableAllDTCs();
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bDtcSettingOff                                          */
/* !Description : Deactivation of fault detections                            */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
void UDS_vidDtcSettingOff(void)
{
   //FaultDisableAllDTCs();
}

#define UDS_STOP_SEC_CODE
#include "memmap.h"

/*-------------------------------- end of file -------------------------------*/