/******************************************************************************/
/*                                                                            */
/* !Layer           : SRV                                                     */
/*                                                                            */
/* !Component       : UDS                                                     */
/* !Description     :                                                         */
/*                                                                            */
/* !File            : UDS_Reset.c                                             */
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
#include "Dcm.h"
#include "RSTSRV.h"
#include "ComStack_Init.h"

#define UDS_START_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_vidReset                                                */
/* !Description : Management of reset requests                                 */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
void UDS_vidReset(uint8 RequestedMode)
{
   switch (RequestedMode)
   {
      case (uint8)DCM_HARD_RESET:
      {
         Dcm_HardResetModeEntry();
         UDS_u8ResetRequestedMode = DCM_HARD_RESET;
         break;
      }
      case (uint8)DCM_KEY_ON_OFF_RESET:
      {
         Dcm_KeyOnOffResetModeEntry();
         UDS_u8ResetRequestedMode = DCM_KEY_ON_OFF_RESET;
         break;
      }      
      case (uint8)DCM_SOFT_RESET:
      {
         Dcm_SoftResetModeEntry();
         UDS_u8ResetRequestedMode = DCM_SOFT_RESET;
         break;
      }
      case (uint8)DCM_BOOTLOADER_RESET:
      {
         Dcm_BootloaderResetModeEntry();
         UDS_u8ResetRequestedMode = DCM_BOOTLOADER_RESET;
         break;
      }
      case (uint8)DCM_RESET_EXECUTION:
      {
         /* Do something */
         break;
      }
      default:
         UDS_u8ResetRequestedMode = DCM_NO_RESET;
         break;
   }
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_vidResetExecution                                       */
/* !Description : Execution of reset demands                                  */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
void UDS_vidResetExecution
(
  uint8 SID,
  uint8 ReqType,
  uint16 SourceAddress,
  Dcm_ConfirmationStatusType ConfirmationStatus
)
{
   if (UDS_u8ResetRequestedMode == DCM_HARD_RESET)
   { 
       RSTSRV_vidPerformReset(RSTSRV_udtHARDWARE_RESET);
   }
   else if (UDS_u8ResetRequestedMode == DCM_SOFT_RESET)
   { 
       RSTSRV_vidPerformReset(RSTSRV_udtSOFTWARE_RESET);
   }
   else if (UDS_u8ResetRequestedMode == DCM_KEY_ON_OFF_RESET)
   { 
       RSTSRV_vidPerformReset(RSTSRV_udtSOFTWARE_RESET);
   }   
   else
   {
      UDS_u8ResetRequestedMode = DCM_NO_RESET;
   }
}
#define UDS_STOP_SEC_CODE
#include "memmap.h"

/*-------------------------------- end of file -------------------------------*/