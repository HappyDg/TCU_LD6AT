
#include "Os_api.h"
#include "ComStack_Init.h"

#include "BSW.h"
#include "BswM.h"
#include "Can.h"
#include "CanIf.h"
#include "CanTp.h"
#include "Com.h"
#include "ComM.h"
#include "ComM_EcuMBswM.h"
#include "Dcm.h"
#include "Dcm_Cbk.h"
#include "Dem.h"
#include "PduR.h"
#include "fbl_def.h"
#include "fbl_cfg.h"

#include "TSTCAL.h"

extern boolean Main_bDCMCbkJumpBLCondOk(void);
extern void Main_vidDCMCbkComTxInh(void);
extern void Main_vidDCMCbkComTxUnInh(void);
extern void Main_vidDCMCbkComRxInh(void);
extern void Main_vidDCMCbkComRxUnInh(void);

void Can_Initi_Modes(void);

Com_IpduGroupVector  IpduVector;

CONST(uint16, COMM_CONST) ComM_BusSMMaxRetryCount[COMM_NUM_CHANNELS] =
{
  10U, /* ComMChannel_0 */
};


#define CANIF_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

static uint32 CANIF_u32BusOffCount;
static uint8  CANIF_u8ModeIndicationId;
static uint8  CANIF_u8ModeIndicationMode;

#define CANIF_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

/******************************************************************************/
void BSW_COMStack_Initi(void)
{
   Com_Init(&COM_CONFIG_NAME.Com_RootConfig);
   PduR_Init(&PduR_Configuration.PduR_RootConfig);
   CanIf_Init(&CanIf_InitCfg_0);
   Can_Initi_Modes();

   CanIf_SetPduMode(CanIf_CanController_0, CANIF_SET_ONLINE);
   CanIf_SetPduMode(CanIf_CanController_1, CANIF_SET_ONLINE);
   CanIf_SetPduMode(CanIf_CanController_2, CANIF_SET_ONLINE);

   ComM_CommunicationAllowed(ComMConf_ComMChannel_ComMChannel_0, TRUE);
   ComM_ASR40_RequestComMode(ComMUser_0, COMM_FULL_COMMUNICATION);

   Com_SetIpduGroup(IpduVector, 0, TRUE);
   Com_SetIpduGroup(IpduVector, 1, TRUE);
   Com_SetIpduGroup(IpduVector, 2, TRUE);
   Com_SetIpduGroup(IpduVector, 3, TRUE);
   Com_IpduGroupControl(IpduVector, FALSE);
   CanTp_Init(&CanTp_ConfigLayout.RootCfg);
   Dcm_Init(NULL_PTR);
   Dcm_ComM_FullComModeEntered(ComMConf_ComMChannel_ComMChannel_0);
}

/******************************************************************************/
/*FUNC(void, DEM_CODE) Dem_ReportErrorStatus(
   Dem_EventIdType     EventId,
   Dem_EventStatusType EventStatus)
{

}*/

/******************************************************************************/
 /* Dem Stubs */
FUNC(Std_ReturnType, DCM_CODE)Dcm_RoutineControlStartDummy(
   Dcm_OpStatusType OpStatus,
   P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA)pMsgContext,
   P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode)
{
    return E_OK;
}

// /******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SetProgConditions(
   P2VAR(Dcm_ProgConditionsType, AUTOMATIC, DCM_APPL_DATA) ProgConditions)
{
   Std_ReturnType retVal = E_NOT_OK;
   tFblHeader* fblHeaderPtr;
   tFblStrtFct fblStartFct;
   boolean ProgCondOk;

   ProgCondOk = Main_bDCMCbkJumpBLCondOk();

   if (0 != ProgCondOk)
   {
      fblHeaderPtr = (tFblHeader*) FBL_HEADER_ADDRESS;
      fblStartFct = fblHeaderPtr->FblStartFct;

      fblStartFct(V_NULL);

      retVal = E_OK;
   }
   else
   {
      retVal = E_NOT_OK;
   }

   return retVal;
}

/******************************************************************************/
FUNC(Dcm_EcuStartModeType, DCM_CODE) Dcm_GetProgConditions(
   P2VAR(Dcm_ProgConditionsType, AUTOMATIC, DCM_APPL_DATA) ProgConditions)
{
   return DCM_COLD_START;
}


/******************************************************************************/
FUNC(void, BSWM_CODE) BswM_Dcm_RequestSessionMode
(
   Dcm_SesCtrlType RequestedMode
)
{
   Dcm_SesCtrlType               ActiveSession;

   Dcm_GetSesCtrlType(&ActiveSession);

   switch (RequestedMode)
   {
      case 1:
      {
         Dcm_DefaultSessionModeEntry();
         break;
      }

      case 2:
      {
         switch (ActiveSession)
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
         switch (ActiveSession)
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

/******************************************************************************/
FUNC(void, BSWM_CODE) BswM_Dcm_RequestResetMode
(
   Dcm_ResetModeType RequestedMode
)
{
   switch (RequestedMode)
   {
      case DCM_HARD_RESET:
      {
         Dcm_HardResetModeEntry();
         break;
      }
      case DCM_BOOTLOADER_RESET:
      {
         Dcm_BootloaderResetModeEntry();
         break;
      }
      case DCM_RESET_EXECUTION:
      {
         /* Do something */
         break;
      }
      default:
         break;
   }
}


/******************************************************************************/
FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_DummyCommunicationControl
(
   Dcm_OpStatusType opStatus,
   P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
)
{
   switch (opStatus)
   {
      /* first call of service function */
      case DCM_INITIAL:
         /* check request length */
         if (pMsgContext->reqDataLen != 2U)
         {
            Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
         }
         /* check subfunctions */
         switch (pMsgContext->reqData[0])
         {
            case 0x01:
            case 0x02:
            case 0x03:
               /* assemble response */
             pMsgContext->resData[0] = pMsgContext->reqData[0];
             pMsgContext->resDataLen = 1U;
             break;

            case 0x00:
               Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
               break;

            default:
               Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_SUBFUNCTIONNOTSUPPORTED);
               break;
         }
         break;

      /* actions performed on sucessful sending of the response */
      case DCM_CONFIRMED_OK:
         /* do nothing */
         break;

      /* actions performed on failure in sending of the response */
      case DCM_CONFIRMED_NOK:
         /* do nothing */
         break;

      default:
         /* do nothing */
         break;
   }

  return DCM_E_DONE;
}

/******************************************************************************/
FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_DummyControlDtcSettings
(
   Dcm_OpStatusType opStatus,
   P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
)
{

   switch (opStatus)
   {
      /* first call of service function */
      case DCM_INITIAL:
         /* check request length */
         if (pMsgContext->reqDataLen != 1U)
         {
            Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
         }
         /* check subfunctions */
         /* check subfunctions */
         switch (pMsgContext->reqData[0])
         {
            case 0x02:
               /* assemble response */
               pMsgContext->resData[0] = pMsgContext->reqData[0];
               pMsgContext->resDataLen = 1U;
               break;

            case 0x01:
               Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_SUBFUNCTIONNOTSUPPORTED);
               break;

            default:
               Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_SUBFUNCTIONNOTSUPPORTED);
               break;
         }
         break;

         /* actions performed on sucessful sending of the response */
         case DCM_CONFIRMED_OK:
         /* do nothing */
            break;

         /* actions performed on failure in sending of the response */
         case DCM_CONFIRMED_NOK:
         /* do nothing */
            break;

         default:
         /* do nothing */
            break;
   }

  return DCM_E_DONE;
}

/******************************************************************************/
FUNC(void, BSWM_CODE) BswM_Dcm_RequestCommunicationMode
(
   NetworkHandleType Network,
   Dcm_CommunicationModeType RequestedMode
)
{
   /* EB_IMPL_START BSCTEMPLATE-1438 - Unused Parameter */
   TS_PARAM_UNUSED(Network);
   TS_PARAM_UNUSED(RequestedMode);
   /* EB_IMPL_END */

   if (RequestedMode == DCM_ENABLE_RX_TX_NORM)
   {
      (void)Dcm_EnableRxTxNormModeEntry();
      Main_vidDCMCbkComTxUnInh();
      Main_vidDCMCbkComRxUnInh();
   }
   else
   {
      if (RequestedMode == DCM_ENABLE_RX_DISABLE_TX_NORM)
      {
         (void)Dcm_EnableRxDisableTxNormModeEntry();
         Main_vidDCMCbkComTxInh();
         Main_vidDCMCbkComRxUnInh();
      }
      else
      {
         if (RequestedMode == DCM_DISABLE_RX_ENABLE_TX_NORM)
         {
            (void)Dcm_DisableRxEnableTxNormModeEntry();
            Main_vidDCMCbkComRxInh();
            Main_vidDCMCbkComTxUnInh();
         }
         else
         {
            if (RequestedMode == DCM_DISABLE_RX_TX_NORM)
            {
               (void)Dcm_DisableRxTxNormModeEntry();
               Main_vidDCMCbkComTxInh();
               Main_vidDCMCbkComRxInh();
            }
            else
            {
               (void)Dcm_EnableRxTxNormModeEntry();
               Main_vidDCMCbkComTxUnInh();
               Main_vidDCMCbkComRxUnInh();
            }
         }
      }
   }
}


/******************************************************************************/
void Can_Initi_Modes(void)
{
   uint16 u16LocalBaudrate;
   Std_ReturnType udtLocalStatus;

   /* Initialize CAN 0 Baudrate */
   u16LocalBaudrate = 500;

   /* Put the CAN controller 0 into stopped state */
   CanIf_SetControllerMode(CanIf_CanController_0, CANIF_CS_STOPPED);

   /* check Baudrate 500Kbps for CanController 0 */
   udtLocalStatus = Can_CheckBaudrate(CanIf_CanController_0, u16LocalBaudrate);

   if (E_OK == udtLocalStatus)
   {
      /* If baudrate is configured then change baudrate */
      udtLocalStatus = Can_ChangeBaudrate(CanIf_CanController_0, u16LocalBaudrate);
   }

   /* Put the CAN controllers into started state */
   CanIf_SetControllerMode(CanIf_CanController_0, CANIF_CS_STARTED);


   /* Initialize CAN 1 Baudrate */
   u16LocalBaudrate = 500;

   /* Put the CAN controller 1 into stopped state */
   CanIf_SetControllerMode(CanIf_CanController_1, CANIF_CS_STOPPED);

   /* check Baudrate 500Kbps for CanController_1 */
   udtLocalStatus = Can_CheckBaudrate(CanIf_CanController_1, u16LocalBaudrate);

   if (E_OK == udtLocalStatus)
   {
      /* If baudrate is configured then change baudrate */
      udtLocalStatus = Can_ChangeBaudrate(CanIf_CanController_1, u16LocalBaudrate);
   }

   /* Put the CAN controllers into started state */
   CanIf_SetControllerMode(CanIf_CanController_1, CANIF_CS_STARTED);


   /* Initialize CAN 2 Baudrate */
   u16LocalBaudrate = 1000;

   /* Put the CAN controller 2 into stopped state */
   CanIf_SetControllerMode(CanIf_CanController_2, CANIF_CS_STOPPED);

   /* check Baudrate 1Mbps for CanController_2 */
   udtLocalStatus = Can_CheckBaudrate(CanIf_CanController_2, u16LocalBaudrate);

   if (E_OK == udtLocalStatus)
   {
      /* If baudrate is configured then change baudrate */
      udtLocalStatus = Can_ChangeBaudrate(CanIf_CanController_2, u16LocalBaudrate);
   }

   /* Put the CAN controllers into started state */
   CanIf_SetControllerMode(CanIf_CanController_2, CANIF_CS_STARTED);
}

/******************************************************************************/
void CanSM_ControllerBusOff( uint8 ControllerId )
{
   CANIF_u32BusOffCount++;
   if (ControllerId == CanIf_CanController_0)
   {
      BSW_bCAN0BusOff = 1;
   }
   if (ControllerId == CanIf_CanController_1)
   {
      BSW_bCAN1BusOff = 1;
   }
   if (ControllerId == CanIf_CanController_2)
   {
      BSW_bCAN2BusOff = 1;
   }
}

/******************************************************************************/
void CanSM_ControllerModeIndication( uint8 ControllerId, CanIf_ControllerModeType ControllerMode )
{
   CANIF_u8ModeIndicationId   = ControllerId;
   CANIF_u8ModeIndicationMode = ControllerMode;
}

/*-------------------------------- end of file -------------------------------*/

