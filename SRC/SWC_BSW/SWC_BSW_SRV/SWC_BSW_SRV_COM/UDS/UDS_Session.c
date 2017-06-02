/******************************************************************************/
/*                                                                            */
/* !Layer           : COM                                                     */
/*                                                                            */
/* !Component       : UDS                                                     */
/* !Description     :                                                         */
/*                                                                            */
/* !File            : UDS_Session.c                                           */
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

#define UDS_START_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_vidSession                                              */
/* !Description : Management of session changes                               */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
void UDS_vidSession(uint8 RequestedMode)
{
   Dcm_SesCtrlType bLocalActiveSession;

   Dcm_GetSesCtrlType(&bLocalActiveSession);

   switch (RequestedMode)
   {
      case 1:
      {
         Dcm_DefaultSessionModeEntry();
         break;
      }

      case 2:
      {
         switch (bLocalActiveSession)
         {
            case DCM_EXTENDED_DIAGNOSTIC_SESSION:
            case DCM_PROGRAMMING_SESSION:
               Dcm_ProgrammingSessionModeEntry();
               break;

            default:
               Dcm_ExtendedDiagnosticSessionModeEntry();
               break;
         }
         break;
      }

      case 3:
      {
         switch (bLocalActiveSession)
         {
            case DCM_EXTENDED_DIAGNOSTIC_SESSION:
            case DCM_DEFAULT_SESSION:
               Dcm_ExtendedDiagnosticSessionModeEntry();
               break;

            default:
               Dcm_DefaultSessionModeEntry();
               break;
         }
         break;
      }
      default:
         break;
   }
}

#define UDS_STOP_SEC_CODE
#include "memmap.h"

/*-------------------------------- end of file -------------------------------*/