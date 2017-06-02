/******************************************************************************/
/*                                                                            */
/* !Layer           : COM                                                     */
/*                                                                            */
/* !Component       : UDS                                                     */
/* !Description     : 								                                 */
/*                                                                            */
/* !File            : UDS_ComControl.c                                        */
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
#include "Dcm_Int.h" 
#include "Com.h"

static Com_IpduGroupVector UDS_IpduVector1;

#define UDS_START_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bEnableRxAndTx                                          */
/* !Description : Enable CAN communication                                    */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
FUNC(Std_ReturnType, DCM_APPL_CODE) UDS_bEnableRxAndTx(
Dcm_OpStatusType OpStatus,
P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{

   if ((DCM_INITIAL == OpStatus) || (DCM_PENDING == OpStatus))
   {
      /* get Hsm information */
      CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(Dcm_CurProtocolId);
        
      /* Update the confirmed Communication Mode */
      curHsmInfo->confirmedCommunicationMode = DCM_ENABLE_RX_TX_NORM;
        
      pMsgContext->resData[0] = 0;
      pMsgContext->resDataLen = 1U;
           
      // ComM_CommunicationAllowed(ComMConf_ComMChannel_ComMChannel_0, TRUE);
      // ComM_ASR40_RequestComMode(ComMUser_0, COMM_FULL_COMMUNICATION);
      Com_SetIpduGroup(UDS_IpduVector1, 0, TRUE);
      Com_SetIpduGroup(UDS_IpduVector1, 1, TRUE);
      Com_SetIpduGroup(UDS_IpduVector1, 2, TRUE);
      Com_SetIpduGroup(UDS_IpduVector1, 3, TRUE);
      Com_IpduGroupControl(UDS_IpduVector1, FALSE);
   }
   
   return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bDisableRxAndTx                                         */
/* !Description : Disable CAN communication except UDS                        */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
FUNC(Std_ReturnType, DCM_APPL_CODE) UDS_bDisableRxAndTx(
Dcm_OpStatusType OpStatus,
P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
   if ((DCM_INITIAL == OpStatus) || (DCM_PENDING == OpStatus))
   {
      /* get Hsm information */
      CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(Dcm_CurProtocolId);
  
      pMsgContext->resData[0] = 3;
      pMsgContext->resDataLen = 1U;

      /* Update the confirmed Communication Mode */
      curHsmInfo->confirmedCommunicationMode = DCM_DISABLE_RX_TX_NORM;
  
      // ComM_CommunicationAllowed(ComMConf_ComMChannel_ComMChannel_0, FALSE);
      // ComM_ASR40_RequestComMode(ComMUser_0, COMM_NO_COMMUNICATION);
      Com_SetIpduGroup(UDS_IpduVector1, 0, FALSE);
      Com_SetIpduGroup(UDS_IpduVector1, 1, FALSE);
      Com_SetIpduGroup(UDS_IpduVector1, 2, FALSE);
      Com_SetIpduGroup(UDS_IpduVector1, 3, FALSE);
      Com_IpduGroupControl(UDS_IpduVector1, FALSE);
   }
   
   return E_OK;
}


#define UDS_STOP_SEC_CODE
#include "MemMap.h"