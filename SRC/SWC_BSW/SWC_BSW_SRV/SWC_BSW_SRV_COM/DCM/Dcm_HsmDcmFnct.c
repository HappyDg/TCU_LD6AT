/**
 * \file
 *
 * \brief AUTOSAR Dcm
 *
 * This file contains the implementation of the AUTOSAR
 * module Dcm.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/* Implementation of the state handler functions of the state machine
 * Dcm.
 *
 * This file contains the implementation of the state functions.  It
 * is generated but must be edited to implement the real actions.  If the
 * state machine model is updated and the code generator regenerates the
 * files the user must manually merge the changes with any existing hand
 * written code.
 */

/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 12.5 (required)
 *     The operands of a logical && or || shall be primary-expressions.
 *
 *     Reason:
 *     Misra has an exception that whenever an expression consists of either a
 *     sequence of only logical && or a sequence of only logical && or logical
 *     ||, extra parentheses are not required
 *
 * MISRA-2) Deviated Rule: 12.4 (required)
 *     The right-hand operand of a logical '&&' or '||' operator
 *     shall not contain side effects.
 *
 *     Reason:
 *     Logical operators '&&' and '||' are used here purposefully. The sub-expression shall not be
 *     evaluated if the first expression of a '&&' operation is FALSE. Similarly the
 *     sub-expression shall not be evaluated if the first expression of a '||' operation is TRUE.
 *     There is no side effects.
 */

/*==================[inclusions]============================================*/

#include <Dcm_Trace.h>
#include <Std_Types.h>                            /* AUTOSAR standard types */

#include <Dcm_Hsm.h>                      /* state machine driver interface */
#include <Dcm_HsmDcm.h>              /* public statechart model definitions */
#include <Dcm_HsmDcmInt.h>         /* internal statechart model definitions */

#include <Dem.h>
#include <Dcm_Int.h>                          /* Module intenal definitions */
#include <Dcm_DspExternal.h>      /* Callbacks provided by Central Diag SwC */
/* do not indirectly include PduR_SymbolicNames_PBcfg.h via PduR_Dcm.h */
#define PDUR_NO_PBCFG_REQUIRED
#include <PduR_Dcm.h>                             /* PduR interface for Dcm */
#include <ComM_Dcm.h>                             /* ComM interface for Dcm */
#include <SchM_Dcm.h>                             /* SchM interface for Dcm */
#if (DCM_BSWM_API_ENABLED == STD_ON)
#include <BswM_DCM.h>                             /* BswM interface for Dcm */
#endif
/*==================[macros]================================================*/

/* Macro for parameter DcmDslDiagRespMaxNumRespPend configured as 0xFF */
#define DCM_UNLIMITED_0X78_NRC                (0xFFU)
/* JumpFromBootloader positive response length with timing values */
#define DCM_JUMPFROMBL_RESPONSELENGTH_TIMING_VALUES     (5U)
/* JumpFromBootloader positive response length without timing values */
#define DCM_JUMPFROMBL_RESPONSELENGTH_NO_TIMING_VALUES  (1U)
/* Macro for CommunicationControl service ID */
#define DCM_DSP_SERVICE_0X28                  (0x28U)

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

#define DCM_START_SEC_CODE
#include <MemMap.h>

STATIC FUNC(boolean, DCM_CODE) Dcm_CheckBuf(
  const uint8               instIdx,
  const Dcm_BufferStateType bufferState);

/** \brief Set TX timer timeout value and start the timer
 **
 ** This function sets the TX timer timeout value implicitely starting the
 ** TX timer.
 ** Since TimerVal is calculated based on the S2 timer timeout value and
 ** DCM_TASK_TIME and can never be 0, this case is not handled.
 **
 ** \param[in] instIdx   Hsm instance
 ** \param[in] TimerVal  TX timeout 'ticks'
 **
 ** \Reentrancy{Non-reentrant}
 ** \Synchronicity{Synchronous}
 **
 */
STATIC FUNC(void, DCM_CODE)
  Dcm_StartTimerTx(DCM_PL_START_TIMER(const uint8 instIdx, uint32 TimerVal));

/** \brief Set Timer2 timer timeout value and start the timer
 **
 ** This function sets the Timer2 timer timeout value implicitely starting
 ** the Timer2 timer.
 **
 ** \param[in] instIdx   Hsm instance
 ** \param[in] TimerVal  Timer2 timeout 'ticks'
 **
 ** \Reentrancy{Non-reentrant}
 ** \Synchronicity{Synchronous}
 **
 */
STATIC FUNC(void, DCM_CODE)
  Dcm_StartTimer2(DCM_PL_START_TIMER(const uint8 instIdx, uint32 TimerVal));

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
/** \brief Set PgBuf timer timeout value and start the timer
 **
 ** This function sets the PgBuf timer timeout value implicitely starting the
 ** PgBuf timer.
 **
 ** \param[in] instIdx   Hsm instance
 ** \param[in] TimerVal  PgBuf timeout 'ticks'
 **
 ** \Reentrancy{Non-reentrant}
 ** \Synchronicity{Synchronous}
 **
 */
STATIC FUNC(void, DCM_CODE)
  Dcm_StartTimerPgBuf(DCM_PL_START_TIMER(const uint8 instIdx, uint32 TimerVal));
#endif /* DCM_PAGEDBUFFER_ENABLED */

/** \brief Set S3 timer timeout value and start the timer
 **
 ** This function sets the S3 timer timeout value implicitely starting the
 ** S3 timer.
 ** Since TimerVal is calculated based on the S3 timer timeout value and
 ** DCM_TASK_TIME and can never be 0, this case is not handled.
 **
 ** \param[in] instIdx   Hsm instance
 ** \param[in] TimerVal  S3 timeout 'ticks'
 **
 ** \Reentrancy{Non-reentrant}
 ** \Synchronicity{Synchronous}
 **
 ** \note This function must only be used from within critical section!
 */
STATIC FUNC(void, DCM_CODE)
  Dcm_StartTimer3(DCM_PL_START_TIMER(const uint8 instIdx, uint16 TimerVal));

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
/** \brief Stop the PgBuf timer
 **
 ** This function sets the PgBuf timer timeout value to zero implicitely
 ** stoping the PgBuf timer.
 **
 ** \param[in] instIdx   Hsm instance
 **
 ** \Reentrancy{Non-reentrant}
 ** \Synchronicity{Synchronous}
 **
 */
STATIC FUNC(void, DCM_CODE) Dcm_StopTimerPgBuf(DCM_PDL_SF(const uint8 instIdx));
#endif /* DCM_PAGEDBUFFER_ENABLED */

/** \brief Stop the Tx timer
 **
 ** This function sets the Tx timer timeout value to zero implicitely
 ** stoping the Tx timer.
 **
 ** \param[in] instIdx   Hsm instance
 **
 ** \Reentrancy{Non-reentrant}
 ** \Synchronicity{Synchronous}
 **
 */
STATIC FUNC(void, DCM_CODE) Dcm_StopTimerTx(DCM_PDL_SF(const uint8 instIdx));

/** \brief Stop the Timer2 timer
 **
 ** This function sets the Timer2 timer timeout value to zero implicitely
 ** stoping the Timer2 timer.
 **
 ** \param[in] instIdx   Hsm instance
 **
 ** \Reentrancy{Non-reentrant}
 ** \Synchronicity{Synchronous}
 **
 */
STATIC FUNC(void, DCM_CODE) Dcm_StopTimer2(DCM_PDL_SF(const uint8 instIdx));


STATIC FUNC(boolean, DCM_CODE) Dcm_SendRespPendInFirstCycle(DCM_PDL_SF(const uint8 instIdx));
STATIC FUNC(void, DCM_CODE) RespPendInFirstCycle(DCM_PDL_SF(const uint8 instIdx));
STATIC FUNC(boolean, DCM_CODE) Dcm_CheckTxEnbEmitEvt(const uint8 instIdx);
STATIC FUNC(boolean, DCM_CODE) Dcm_SuppressResponse(const uint8 instIdx);
STATIC FUNC(boolean, DCM_CODE) Dcm_PageBufferInProgress(const uint8 instIdx);
#if(DCM_ROE_ENABLED == STD_ON)
STATIC FUNC(void, DCM_CODE) Dcm_HsmDcmSetRoePduIdsAndProtocolData(DCM_PDL_SF(const uint8 instIdx));
#endif /* if(DCM_ROE_ENABLED == STD_ON) */
#define DCM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

#define DCM_START_SEC_CODE
#include <MemMap.h>

/* ************************ state functions ******************************* */

/* ************************************************************************
 * State: Top
 * Parent state: none
 * Init substate: OutOfService
 * Transitions originating from this state:
 */

FUNC(void, DCM_CODE) Dcm_HsmDcmSfTopEntry(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* entry action 'InitHsmVariables();' */

  /* Initialize status information for each configured protocol */
  DCM_TX_DATA_STATE(instIdx) = DCM_NO_TX_DATA;

  DBG_DCM_HSMDCMSFTOPENTRY_ENTRY(DCM_INST(instIdx));

  /* Set first byte of negative response buffer */
  DCM_NR_BUFFER(instIdx).ptrBuffer[0] = 0x7FU;

  /* Set Session type to default session */
  DCM_HSM_INFO(instIdx).sesTabIdx = Dcm_SesTabConfig[DCM_CUR_INST_ID(instIdx)].DefSessionIndex;

  /* Lock security */
  DCM_HSM_INFO(instIdx).secTabIdx = DCM_SEC_TAB_ENTRY_IDX_LOCKED;

  /* reset security access state handling */
  DCM_HSM_INFO(instIdx).requestedSecLevel = DCM_SEC_IDLE;

  /* Stop the timer Tx */
  DCM_HSM_INFO(instIdx).timerTx = 0U;

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  /* Stop the timer PgBuf */
  DCM_HSM_INFO(instIdx).timerPgBuf = 0U;
#endif

  /* Stop the timer 2 */
  DCM_HSM_INFO(instIdx).timer2 = 0U;

  /* Stop the timer 3 */
  DCM_HSM_INFO(instIdx).timer3 = 0U;

  /* Stop the retry timer */
  DCM_HSM_INFO(instIdx).retryTimer = (uint16)0U;
#if (DCM_MODEDECLARATION_SUPPORT == STD_OFF)
  /* Set confirmed diagnostics session to invalid */
  DCM_HSM_INFO(instIdx).confirmedDiagSession = DCM_INVALID_SESSION;

  /* Initialize the requested Reset Mode */
  DCM_HSM_INFO(instIdx).requestedResetMode = DCM_NO_RESET;

  /* Initialize the confirmed Reset Mode */
  DCM_HSM_INFO(instIdx).confirmedResetMode = DCM_NO_RESET;

  /* Initialize the confirmed Communication Mode */
  DCM_HSM_INFO(instIdx).confirmedCommunicationMode = DCM_0X28_COMM_MODE_INVALID;

  /* Initialize the requested Communication Mode */
  DCM_HSM_INFO(instIdx).requestedCommunicationMode = DCM_0X28_COMM_MODE_INVALID;
#endif
  /* Stop Security delay counter */
  DCM_SEC_DELAY_COUNTER(instIdx) = 0U;

  /* Clear security access attempts exceeded flag */
  DCM_EXCEED_NO_OF_ATTEMPTS(instIdx) = FALSE;

  /* Initialize the Jump to bootloader support status flag **/
  DCM_HSM_INFO(instIdx).jumpToBLSupport = FALSE;

  /* Initialize the Jump to bootloader mode execution pending status flag **/
  DCM_HSM_INFO(instIdx).jumpToBLExecution = DCM_PREPARE_JUMP;

  /* Initialize the message type flag **/
  DCM_HSM_INFO(instIdx).msgContext.msgAddInfo.messageType = DCM_NORMAL;

  /* Initialize 'Response Pending' transmission status */
  DCM_HSM_INFO(instIdx).responsePendingTxStatus = DCM_RP_NO_DATA;

  /* Initialize 'Status of ControlDTCSettings' status flag */
  DCM_HSM_INFO(instIdx).dtcDisableStatus = FALSE;

  /* Initialize 'Status of AsyncService opState */
  DCM_HSM_INFO(instIdx).asyncServiceOpState = DCM_ASYNC_PROCESSING_DONE;

  /* Initialize the initial request validation status */
  DCM_HSM_INFO(instIdx).requestValidationStatus = FALSE;

  DBG_DCM_HSMDCMSFTOPENTRY_EXIT(DCM_INST(instIdx));
}

/* ************************************************************************
 * State: WaitForFullCom
 * Parent state: Top
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) WaitForFullCom -> Finishing: BL_TX_RESPONSE[!ResponseRequired]/ReEnableRx
 * 2) WaitForFullCom -> Sending: BL_TX_RESPONSE[]/Fill response
 */

FUNC(boolean, DCM_CODE) Dcm_HsmDcmSfWaitForFullComGuard1(
  DCM_PDL_SF(const uint8 instIdx))
{
  boolean retVal;

  DBG_DCM_HSMDCMSFWAITFORFULLCOMGUARD1_ENTRY(DCM_INST(instIdx));
  TS_PARAM_UNUSED(DCM_INST(instIdx));

  /* guard condition '!ResponseRequired'
   * for BL_TX_RESPONSE[...]/ReEnableRx
   * external transition to state Finishing */

  retVal = (!ProgConditions.ResponseRequired);

  DBG_DCM_HSMDCMSFWAITFORFULLCOMGUARD1_EXIT(retVal, DCM_INST(instIdx));
  return retVal;
}

FUNC(void, DCM_CODE) Dcm_HsmDcmSfWaitForFullComAction1(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* action 'ReEnableRx'
   * for BL_TX_RESPONSE[!ResponseRequired]/...
   * external transition to state Finishing */

  DBG_DCM_HSMDCMSFWAITFORFULLCOMACTION1_ENTRY(DCM_INST(instIdx));

#if ((DCM_HSM_INST_MULTI_ENABLED == STD_ON) && (DCM_DBG_ENABLED == STD_OFF))
  TS_PARAM_UNUSED(instIdx);
#endif


  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* As processing is now finished, reset the flag for current processing in execution */
  DBG_DCM_REQPROCESSING((Dcm_ReqProcessing),(FALSE));
  Dcm_ReqProcessing = FALSE;

  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();


  DBG_DCM_HSMDCMSFWAITFORFULLCOMACTION1_EXIT(DCM_INST(instIdx));
}

FUNC(void, DCM_CODE) Dcm_HsmDcmSfWaitForFullComAction2(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* action 'Fill response'
   * for BL_TX_RESPONSE[]/...
   * external transition to state Sending */
#if (DCM_TIMING_VALUES_IN_POSITIVE_RESPONSE == STD_ON)
  uint16 P2StarTime;
  uint8_least i;
  uint8 sesTabIdxNew = 0U;
   /* Get SesTabConfig info */
  P2CONST(Dcm_SesTabConfigType, AUTOMATIC, DCM_CONST) sesTabConfig =
                                                        &Dcm_SesTabConfig[DCM_CUR_INST_ID(instIdx)];
  /* get the context information current instance */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo
    = &DCM_HSM_INFO(instIdx);

  /* Holds the RxPduId configuration */
  P2CONST(Dcm_RxPduIdConfigType, AUTOMATIC, DCM_CONST) curRxPduIdConfig = &Dcm_RxPduIdConfig[Dcm_RxPduIdBL];

  /* Holds the Tx, TxConf information for the current Main Connection */
  VAR(Dcm_TxPduIdConfigType, DCM_VAR) txConfig = Dcm_TxPduIds[curRxPduIdConfig->connectionId];

  /* allocate PduIDs*/
  curHsmInfo->rxPduId = Dcm_RxPduIdBL;
  curHsmInfo->txPduId = txConfig.txPduId;
  curHsmInfo->txConfirmationPduId = txConfig.txConfirmationPduId;

  DBG_DCM_HSMDCMSFWAITFORFULLCOMACTION2_ENTRY(DCM_INST(instIdx));

  /* getting new session table index for the new session control */
  for (i = 0U; i < sesTabConfig->NumEntries; ++i)
  {
    if ((sesTabConfig->SessionEntries[i]).SesCtrl == ProgConditions.SubFncId)
    {
      sesTabIdxNew = (uint8)i;
      break;
    }
  }
#else
  DBG_DCM_HSMDCMSFWAITFORFULLCOMACTION2_ENTRY(DCM_INST(instIdx));
#endif
  /* Assembling positive response */
  Dcm_BufferConfig[DCM_HSM_CONFIG(instIdx).txBufferId].ptrBuffer[0] =
                                                          ProgConditions.Sid | DCM_SID_RESPONSE_BIT;
  Dcm_BufferConfig[DCM_HSM_CONFIG(instIdx).txBufferId].ptrBuffer[1] = ProgConditions.SubFncId;
#if (DCM_TIMING_VALUES_IN_POSITIVE_RESPONSE == STD_ON)
  P2StarTime = (uint16)((sesTabConfig->SessionEntries[sesTabIdxNew].P2StarMaxTime *
                                                         DCM_TASK_TIME)/ DCM_P2STARTIME_RESOLUTION);

  Dcm_BufferConfig[DCM_HSM_CONFIG(instIdx).txBufferId].ptrBuffer[2] =
              (uint8)((sesTabConfig->SessionEntries[sesTabIdxNew].P2MaxTime *
                                                               DCM_TASK_TIME) >> DCM_BYTE_SWAPPING);
  Dcm_BufferConfig[DCM_HSM_CONFIG(instIdx).txBufferId].ptrBuffer[3] =
          (uint8)(sesTabConfig->SessionEntries[sesTabIdxNew].P2MaxTime * DCM_TASK_TIME);
  Dcm_BufferConfig[DCM_HSM_CONFIG(instIdx).txBufferId].ptrBuffer[4] =
                                          (uint8)(P2StarTime >> DCM_BYTE_SWAPPING);
  Dcm_BufferConfig[DCM_HSM_CONFIG(instIdx).txBufferId].ptrBuffer[5] = (uint8)(P2StarTime);
  DCM_HSM_INFO(instIdx).msgContext.resDataLen  = DCM_JUMPFROMBL_RESPONSELENGTH_TIMING_VALUES;
#else
  DCM_HSM_INFO(instIdx).msgContext.resDataLen  = DCM_JUMPFROMBL_RESPONSELENGTH_NO_TIMING_VALUES;
#endif
  /* Set the message Id context and data buffer length */
  DCM_HSM_INFO(instIdx).msgContext.idContext = ProgConditions.Sid;

  DBG_DCM_HSMDCMSFWAITFORFULLCOMACTION2_EXIT(DCM_INST(instIdx));
}

/* ************************************************************************
 * State: OutOfService
 * Parent state: Top
 * Init substate: OosInit
 * Transitions originating from this state:
 * 1) RST2DFLTSESS[]/Drop to default session
 * 2) OutOfService -> RoePrServiceCalled: ROE[TxEnabled && CheckRoeBuf()]/ConfigureRoePduIds
 * 3) OutOfService -> RoeFinalResponse: ROE_FINAL_RES[TxEnabled]/ConfigureRoePduIds
 * 4) OutOfService -> InService: RX_IND_OK[CheckRxBuf()]/
 * 5) OutOfService -> OosNotified: TIMEOUT3[]/drop to default session;
 */

FUNC(void, DCM_CODE) Dcm_HsmDcmSfOutOfServiceEntry(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* entry action 'StopTimer2();TxPduId.dataState=TX_DATA_NOT_OK;' */

  DBG_DCM_HSMDCMSFOUTOFSERVICEENTRY_ENTRY(DCM_INST(instIdx));

  /* ENTER critical section */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* status of transmission data is not ok */
  DCM_TX_DATA_STATE(instIdx) = DCM_TX_DATA_NOT_OK;

  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

#if (DCM_ROE_ENABLED == STD_ON)
  /* clear final roe response information */
  Dcm_RoeData.FinalRoeResponse[DCM_ROE_SUBFUNCTION_0x01_IDX] = DCM_ROE_INVALID_FINAL_RES;
  Dcm_RoeData.FinalRoeResponse[DCM_ROE_SUBFUNCTION_0x03_IDX] = DCM_ROE_INVALID_FINAL_RES;
#endif /* #if (DCM_ROE_ENABLED == STD_ON) */
#if (DCM_ASYNC_SERVICE_HANDLER == STD_ON)
  /* Terminate execution of any asynchronous service handler */

  /* ENTER critical section */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  DCM_HSM_INFO(instIdx).asyncServiceOpState = DCM_ASYNC_PROCESSING_DONE;

  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
#endif /* #if(DCM_ASYNC_SERVICE_HANDLER == STD_ON) */

  Dcm_StopTimer2(DCM_PL_SF(instIdx));

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  /* Initialize the flag for cancelling Paged Buffer processing */
  Dcm_CancelPagedProcessing = FALSE;
#endif /* #if (DCM_PAGEDBUFFER_ENABLED == STD_ON) */

  DBG_DCM_HSMDCMSFOUTOFSERVICEENTRY_EXIT(DCM_INST(instIdx));
}

FUNC(void, DCM_CODE) Dcm_HsmDcmSfOutOfServiceAction1(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* action 'Drop to default session'
   * for RST2DFLTSESS[]/...
   * internal transition */
    /* Holds the current HSM information */
  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo;
  P2CONST(Dcm_SesTabConfigType, AUTOMATIC, DCM_CONST) sesTabConfig;
  P2CONST(Dcm_RxPduIdConfigType, AUTOMATIC, DCM_CONST) curRxPduIdConfig;
  NetworkHandleType networkId;

  /* instIdx causes an 'unused parameter' compiler warning. */
  TS_PARAM_UNUSED(DCM_INST(instIdx));

  DBG_DCM_HSMDCMSFOUTOFSERVICEACTION1_ENTRY(DCM_INST(instIdx));

  /* ENTER critical section.
     Dcm_CurProtocolId and curHsmInfo->rxPduId must be accessed together.
     Protect the multiple reads of Dcm_CurProtocolId from preemption */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* get the context information current instance */
  curHsmInfo   = &DCM_HSM_INFO(Dcm_CurProtocolId);

  /* Get SesTabConfig info */
  sesTabConfig = &DCM_SES_TAB_CONFIG(Dcm_CurProtocolId);

  /* get configuration for current Rx Pdu Id */
  curRxPduIdConfig = &Dcm_RxPduIdConfig[curHsmInfo->rxPduId];

  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* Get the network id for the RxPduId */
  networkId = Dcm_ChannelId[curRxPduIdConfig->channelIdIndex].networkId;
  /* Change the session and security level only when current session is a Non-Default session
     [Dcm139] */
  if(sesTabConfig->SessionEntries[curHsmInfo->sesTabIdx].SesCtrl != DCM_DEFAULT_SESSION)
  {
    /* Set session table to Default session */
    curHsmInfo->sesTabIdx = sesTabConfig->DefSessionIndex;

    /* Reset security level */
    curHsmInfo->secTabIdx = DCM_SEC_TAB_ENTRY_IDX_LOCKED;

    /* Reset security access state handling */
    curHsmInfo->requestedSecLevel = DCM_SEC_IDLE;

    /* Inform ComM according to Dcm168 */
    ComM_DCM_InactiveDiagnostic(networkId);
#if (DCM_MODEDECLARATION_SUPPORT == STD_OFF)
#if (DCM_BSWM_API_ENABLED == STD_ON)
    /* Inform BswM about session change */
    BswM_Dcm_RequestSessionMode(DCM_DEFAULT_SESSION);
#endif
#else
    (void)SchM_Switch_Dcm_DcmDiagnosticSessionControl(
      DCM_RTE_DEFAULTSESSION_MODE);
#endif /* #if (DCM_MODEDECLARATION_SUPPORT == STD_OFF) */
  }

  /* The DCM module shall call Dem_EnableDTCSetting() while transitioning to
     default session via Dcm_ResetToDefaultsession */

  if(curHsmInfo->dtcDisableStatus == TRUE)
  {
    (void)Dem_EnableDTCSetting(DEM_DTC_GROUP_ALL_DTCS, DEM_DTC_KIND_ALL_DTCS);

#if (DCM_MODEDECLARATION_SUPPORT == STD_ON)
    /* Dcm751 */
    (void)SchM_Switch_Dcm_DcmControlDTCSetting(RTE_MODE_DcmControlDTCSetting_ENABLEDTCSETTING);
#endif
  }

#if (DCM_DSP_USE_SERVICE_0X2F == STD_ON)
  if(Dcm_ReturnControlToEcuContext.returnCtrlToECUStatus != DCM_RET_CTRL_PENDING)
  {
    /* Because the state of the DIDs is undefined until control has been returned to ECU for
       all. So it is not required to invoke returnControlToECU interface for signals */
    /* Will be done via Dcm_MainFunction */
    Dcm_DspInternal_ReturnControlToEcuforallSignals();
  }
#endif

#if(DCM_0X28_SVC_ENABLED == STD_ON)
  {
    uint8_least i = 0U;

    /* !LINKSTO Dcm.EB.CommunicationModeSwitch.DcmEnableRxTxNormNm,1
       !LINKSTO Dcm.EB.CommunicationModeSwitch.DcmEnableRxTxNormNm_2,1
        set communication mode to DCM_ENABLE_RX_TX_NORM_NM */
    for (i = 0U; i < DCM_NUM_CHANNELID; i++)
    {
      if (Dcm_ChannelId[i].communicationMode != DCM_ENABLE_RX_TX_NORM_NM)
      {
#if (DCM_MODEDECLARATION_SUPPORT == STD_ON)
        uint8_least j = 0U;
        /* Search for SchM switch index */
        /* Please note that a Dcm 'NetworkId' is exactly the same thing as a ComM 'ChannelId' */
        while ((j < DCM_COMCONTROL_LOOKUP_SIZE) &&
               (Dcm_ComControlLookUpTable[j].ComMChannelId != Dcm_ChannelId[i].networkId))
        {
          j++;
        }
        (void)Dcm_ComControlLookUpTable[j].SchMSwitchComControl(RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM_NM);

#if (DCM_BSWM_API_ENABLED == STD_ON)
        /* Invoke the BswM interface to notify the Communication Mode change */
        BswM_Dcm_CommunicationMode_CurrentState(Dcm_ChannelId[i].networkId, DCM_ENABLE_RX_TX_NORM_NM);
#endif /* #if (DCM_BSWM_API_ENABLED == STD_ON) */
#else /* #if (DCM_MODEDECLARATION_SUPPORT == STD_ON) */
#if (DCM_BSWM_API_ENABLED == STD_ON)
        /* Invoke the BswM interface to request the Communication Mode change */
        BswM_Dcm_RequestCommunicationMode(Dcm_ChannelId[i].networkId, DCM_ENABLE_RX_TX_NORM_NM);
#endif /* #if (DCM_BSWM_API_ENABLED == STD_ON) */
#endif /* #if (DCM_MODEDECLARATION_SUPPORT == STD_ON) */

        Dcm_ChannelId[i].communicationMode = DCM_ENABLE_RX_TX_NORM_NM;
      }
    }
  }
#endif /* #if (DCM_0X28_SVC_ENABLED == STD_ON) */

  DBG_DCM_HSMDCMSFOUTOFSERVICEACTION1_EXIT(DCM_INST(instIdx));
}

FUNC(boolean, DCM_CODE) Dcm_HsmDcmSfOutOfServiceGuard2(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* guard condition 'TxEnabled && CheckRoeBuf()'
   * for ROE[...]/ConfigureRoePduIds
   * external transition to state RoePrServiceCalled */
  boolean retVal = FALSE;
#if(DCM_ROE_ENABLED == STD_ON)
  boolean buffCheck = Dcm_CheckBuf(DCM_CUR_INST_ID(instIdx), DCM_BUF_ROE);
  uint8 channelIndex;
#endif /* if(DCM_ROE_ENABLED == STD_ON) */
  DBG_DCM_HSMDCMSFOUTOFSERVICEGUARD2_ENTRY(DCM_INST(instIdx));
#if(DCM_ROE_ENABLED == STD_ON)
  /* Get the network channel */
  channelIndex = Dcm_RxPduIdConfig[Dcm_RoeData.DcmRxPduId].channelIdIndex;

  retVal = ((Dcm_TxEnabled[channelIndex]) && (buffCheck));

  if(retVal == FALSE)
  {
    /* Release rx and tx buffers */
    Dcm_ReleaseRxTxBuffers(DCM_INST(instIdx));

    /* If currently stopping Request processing operation was ROE, unset ROE processing flag */
    DBG_DCM_ROEPROCESSING((Dcm_ROEProcessing),(DCM_ROE_NONE));
    Dcm_ROEProcessing = DCM_ROE_NONE;
  }
#else
  TS_PARAM_UNUSED(DCM_INST(instIdx));
#endif /* if(DCM_ROE_ENABLED == STD_ON) */

  DBG_DCM_HSMDCMSFOUTOFSERVICEGUARD2_EXIT(retVal, DCM_INST(instIdx));

  return retVal;
}

FUNC(void, DCM_CODE) Dcm_HsmDcmSfOutOfServiceAction2(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* action 'ConfigureRoePduIds'
   * for ROE[TxEnabled && CheckRoeBuf()]/...
   * external transition to state RoePrServiceCalled */
  DBG_DCM_HSMDCMSFOUTOFSERVICEACTION2_ENTRY(DCM_INST(instIdx));

#if(DCM_ROE_ENABLED == STD_ON)
  Dcm_HsmDcmSetRoePduIdsAndProtocolData(DCM_PL_SF(instIdx));
#else
  TS_PARAM_UNUSED(DCM_INST(instIdx));
#endif /* if(DCM_ROE_ENABLED == STD_ON) */

  DBG_DCM_HSMDCMSFOUTOFSERVICEACTION2_EXIT(DCM_INST(instIdx));
}

FUNC(boolean, DCM_CODE) Dcm_HsmDcmSfOutOfServiceGuard3(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* guard condition 'TxEnabled'
   * for ROE_FINAL_RES[...]/ConfigureRoePduIds
   * external transition to state RoeFinalResponse */

#if(DCM_ROE_ENABLED == STD_ON)
  uint8 channelIndex;
#endif /* if(DCM_ROE_ENABLED == STD_ON) */

  uint8 retVal = FALSE;

  DBG_DCM_HSMDCMSFOUTOFSERVICEGUARD3_ENTRY(DCM_INST(instIdx));
  TS_PARAM_UNUSED(DCM_INST(instIdx));

#if(DCM_ROE_ENABLED == STD_ON)
  /* Get the network channel */
  channelIndex = Dcm_RxPduIdConfig[Dcm_RoeData.DcmRxPduId].channelIdIndex;
  retVal = Dcm_TxEnabled[channelIndex];
#endif /* if(DCM_ROE_ENABLED == STD_ON) */

  DBG_DCM_HSMDCMSFOUTOFSERVICEGUARD3_EXIT((Dcm_TxEnabled[channelIndex]), DCM_INST(instIdx));

  return retVal;
}

FUNC(void, DCM_CODE) Dcm_HsmDcmSfOutOfServiceAction3(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* action 'ConfigureRoePduIds'
   * for ROE_FINAL_RES[TxEnabled]/...
   * external transition to state RoeFinalResponse */
  DBG_DCM_HSMDCMSFOUTOFSERVICEACTION3_ENTRY(DCM_INST(instIdx));

#if(DCM_ROE_ENABLED == STD_ON)
  Dcm_HsmDcmSetRoePduIdsAndProtocolData(DCM_PL_SF(instIdx));
#else
  TS_PARAM_UNUSED(DCM_INST(instIdx));
#endif /* if(DCM_ROE_ENABLED == STD_ON) */

  DBG_DCM_HSMDCMSFOUTOFSERVICEACTION3_EXIT(DCM_INST(instIdx));
}

FUNC(boolean, DCM_CODE) Dcm_HsmDcmSfOutOfServiceGuard4(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* guard condition 'CheckRxBuf()'
   * for RX_IND_OK[...]/
   * external transition to state InService */
  boolean retVal = FALSE;

  DBG_DCM_HSMDCMSFOUTOFSERVICEGUARD4_ENTRY(DCM_INST(instIdx));

  retVal = Dcm_CheckBuf(DCM_CUR_INST_ID(instIdx), DCM_BUF_RX);

  DBG_DCM_HSMDCMSFOUTOFSERVICEGUARD4_EXIT(retVal, DCM_INST(instIdx));
  return retVal;
}

FUNC(void, DCM_CODE) Dcm_HsmDcmSfOutOfServiceAction5(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* action 'drop to default session;'
   * for TIMEOUT3[]/...
   * external transition to state OosNotified */

  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo
    = &DCM_HSM_INFO(instIdx);

#if ((DCM_ROE_ENABLED == STD_ON) && (DCM_ROE_INIT_ON_DSC == STD_ON))
  P2CONST(Dcm_DidServicesType, TYPEDEF, DCM_CONST) didCfg =
                     &Dcm_DidTable[Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_REQUESTEDDID_0x03_IDX]];
#endif

  DBG_DCM_HSMDCMSFOUTOFSERVICEACTION5_ENTRY(DCM_INST(instIdx));

  /* set session to default session */
  curHsmInfo->sesTabIdx = Dcm_SesTabConfig[DCM_CUR_INST_ID(instIdx)].DefSessionIndex;

  /* reset security level */
  curHsmInfo->secTabIdx = DCM_SEC_TAB_ENTRY_IDX_LOCKED;

  /* reset security access state handling */
  curHsmInfo->requestedSecLevel = DCM_SEC_IDLE;

#if (DCM_MODEDECLARATION_SUPPORT == STD_OFF)
#if (DCM_BSWM_API_ENABLED == STD_ON)
  /* Dcm142: Whenever a non-default session is active and when the session timeout
    (S3Server) is reached without receiving any diagnostic request, the DSL submodule
    shall reset to the default session state (DefaultSession, 0x01) and invoke the
    function BswM_Dcm_RequestSessionMode() with the requested session as parameter */
  BswM_Dcm_RequestSessionMode(DCM_DEFAULT_SESSION);
#endif
#else
  /* Dcm140 */
  (void)SchM_Switch_Dcm_DcmDiagnosticSessionControl(
    DCM_RTE_DEFAULTSESSION_MODE);
#endif  /* #if (DCM_MODEDECLARATION_SUPPORT == STD_OFF) */

  /* The DCM module shall call Dem_EnableDTCSetting() while transitioning to
     default session on S3Server timeout */
  /* Enables the DTC setting for the DTC group */
  if(curHsmInfo->dtcDisableStatus == TRUE)
  {
    (void)Dem_EnableDTCSetting(DEM_DTC_GROUP_ALL_DTCS, DEM_DTC_KIND_ALL_DTCS);

#if (DCM_MODEDECLARATION_SUPPORT == STD_ON)
    /* Dcm751 */
    (void)SchM_Switch_Dcm_DcmControlDTCSetting(RTE_MODE_DcmControlDTCSetting_ENABLEDTCSETTING);
#endif
  }

#if(DCM_0X28_SVC_ENABLED == STD_ON)
  {
    uint8_least i = 0U;

    /* !LINKSTO Dcm.EB.CommunicationModeSwitch.DcmEnableRxTxNormNm,1
       !LINKSTO Dcm.EB.CommunicationModeSwitch.DcmEnableRxTxNormNm_2,1
        set communication mode to DCM_ENABLE_RX_TX_NORM_NM */
    for (i = 0U; i < DCM_NUM_CHANNELID; i++)
    {
      if (Dcm_ChannelId[i].communicationMode != DCM_ENABLE_RX_TX_NORM_NM)
      {
#if (DCM_MODEDECLARATION_SUPPORT == STD_ON)
        uint8_least j = 0U;
        /* Search for SchM switch index */
        /* Please note that a Dcm 'NetworkId' is exactly the same thing as a ComM 'ChannelId' */
        while ((j < DCM_COMCONTROL_LOOKUP_SIZE) &&
               (Dcm_ComControlLookUpTable[j].ComMChannelId != Dcm_ChannelId[i].networkId))
        {
          j++;
        }
        (void)Dcm_ComControlLookUpTable[j].SchMSwitchComControl(RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM_NM);

#if (DCM_BSWM_API_ENABLED == STD_ON)
        /* Invoke the BswM interface to notify the Communication Mode change */
        BswM_Dcm_CommunicationMode_CurrentState(Dcm_ChannelId[i].networkId, DCM_ENABLE_RX_TX_NORM_NM);
#endif /* #if (DCM_BSWM_API_ENABLED == STD_ON) */
#else /* #if (DCM_MODEDECLARATION_SUPPORT == STD_ON) */
#if (DCM_BSWM_API_ENABLED == STD_ON)
        /* Invoke the BswM interface to request the Communication Mode change */
        BswM_Dcm_RequestCommunicationMode(Dcm_ChannelId[i].networkId, DCM_ENABLE_RX_TX_NORM_NM);
#endif /* #if (DCM_BSWM_API_ENABLED == STD_ON) */
#endif /* #if (DCM_MODEDECLARATION_SUPPORT == STD_ON) */

        Dcm_ChannelId[i].communicationMode = DCM_ENABLE_RX_TX_NORM_NM;
      }
    }
  }
#endif /* #if (DCM_0X28_SVC_ENABLED == STD_ON) */

  /* Dcm618: If the configuration parameter DcmDspRoeInitOnDSC is set to TRUE:
     on S3Server timeout, if ROE is active (reception of startResponseOnEvent)
     the DCM module shall unactivate all ROE active event */
#if ((DCM_ROE_ENABLED == STD_ON) && (DCM_ROE_INIT_ON_DSC == STD_ON))
  /* Check if ROE is active */
  if( (Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] == DCM_ROE_EVENT_STARTED) ||
      (Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x01_IDX] == DCM_ROE_EVENT_STARTED) )
  {
    /* Verify presence of DcmDspDidExtRoe for requested DID */
    if(didCfg->ExtRoeSupport == TRUE)
    {
      /* Invoke xxx_ActivateEvent with DCM_ROE_UNACTIVE. Return value is not considered as
         currently there is no Diagnostic request */
      (void)didCfg->RoeActivateFnc(didCfg->RoeEventId, DCM_ROE_UNACTIVE);
    }
    Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x01_IDX] = DCM_ROE_EVENT_SETUP;
    Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] = DCM_ROE_EVENT_SETUP;
  }
#endif

#if (DCM_DSP_USE_SERVICE_0X2F == STD_ON)
  /* Dcm626: On S3Server timeout, the DCM shall stop all the control in progress */
  if(Dcm_ReturnControlToEcuContext.returnCtrlToECUStatus == DCM_RET_CTRL_INACTIVE)
  {
    Dcm_DspInternal_ReturnControlToEcuforallSignals();
  }
#endif

  DBG_DCM_HSMDCMSFOUTOFSERVICEACTION5_EXIT(DCM_INST(instIdx));
}

/* ************************************************************************
 * State: OosInit
 * Parent state: OutOfService
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) OosInit -> WaitForFullCom: RETURN_FROM_BL[]/ComM_DCM_ActiveDiagnostic()
 */

FUNC(void, DCM_CODE) Dcm_HsmDcmSfOosInitAction1(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* action 'ComM_DCM_ActiveDiagnostic()'
   * for RETURN_FROM_BL[]/...
   * external transition to state WaitForFullCom */
  uint8_least i;
  uint8_least j;
   /* Get SesTabConfig info */
  P2CONST(Dcm_SesTabConfigType, AUTOMATIC, DCM_CONST) sesTabConfig =
                                                        &Dcm_SesTabConfig[DCM_CUR_INST_ID(instIdx)];
  uint8 channelIdx;

  DBG_DCM_HSMDCMSFOOSINITACTION1_ENTRY(DCM_INST(instIdx));

  /* Get the 'RxPduId' corresponding to the 'TesterSourceAddr' */
  for (i =0U; i<DCM_NUM_RX_PDU_ID; i++)
  {
    if (Dcm_RxPduIdConfig[i].TesterSourceAddr == ProgConditions.TesterSourceAddr)
    {
      DCM_HSM_INFO(instIdx).rxPduId = (PduIdType)i;
      break;
    }
  }
  /* Check if the requested session is supported */
  for (j = 0U; j < sesTabConfig->NumEntries; ++j)
  {
    if ((sesTabConfig->SessionEntries[j]).SesCtrl == ProgConditions.SubFncId)
    {
      break;
    }
  }
  /* If the 'TesterSourceAddr' is not configured, report error */
  if (j >= sesTabConfig->NumEntries)
  {
    ProgConditions.ResponseRequired = FALSE;

#if (DCM_DEV_ERROR_DETECT == STD_ON)
    DCM_DET_REPORT_ERROR(DCM_SVCID_GETPROGCONDITIONS, DCM_E_PARAM);
#endif
  }
  else
  {
    /* Get the channel Identifier */
    channelIdx = Dcm_RxPduIdConfig[DCM_HSM_INFO(instIdx).rxPduId].channelIdIndex;

    /* Request the ComManager for the full communication */
    ComM_DCM_ActiveDiagnostic(Dcm_ChannelId[channelIdx].networkId);
  }

  DBG_DCM_HSMDCMSFOOSINITACTION1_EXIT(DCM_INST(instIdx));
}

/* ************************************************************************
 * State: OosNotified
 * Parent state: OutOfService
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 */

FUNC(void, DCM_CODE) Dcm_HsmDcmSfOosNotifiedEntry(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* entry action 'if (default session) ComM_DCM_InactiveDiagnostic();' */

  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

  /* Get SesTabConfig info */
  P2CONST(Dcm_SesTabConfigType, AUTOMATIC, DCM_CONST) sesTabConfig =
                                        &Dcm_SesTabConfig[DCM_CUR_INST_ID(instIdx)];

  NetworkHandleType networkId =
                Dcm_ChannelId[Dcm_RxPduIdConfig[curHsmInfo->rxPduId].channelIdIndex].networkId;

  DBG_DCM_HSMDCMSFOOSNOTIFIEDENTRY_ENTRY(DCM_INST(instIdx));

  /* if (default session), notify ComM about the session change */
  if (DCM_DEFAULT_SESSION == sesTabConfig->SessionEntries[curHsmInfo->sesTabIdx].SesCtrl)
  {
    ComM_DCM_InactiveDiagnostic(networkId);
  }

  /* Initialize 'Status of failures before dispatching a service request */
  DCM_HSM_INFO(instIdx).requestValidationStatus = FALSE;

  DBG_DCM_HSMDCMSFOOSNOTIFIEDENTRY_EXIT(DCM_INST(instIdx));
}

/* ************************************************************************
 * State: InService
 * Parent state: Top
 * Init substate: ServiceCalled
 * Transitions originating from this state:
 * 1) RETRY[]/if (RetryTimer==0) CallService(PENDING)
 */

FUNC(void, DCM_CODE) Dcm_HsmDcmSfInServiceEntry(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* entry action 'setup hsm context; TxPduId.dataState=NO_TX_DATA;' */

  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo
    = &DCM_HSM_INFO(instIdx);

  DBG_DCM_HSMDCMSFINSERVICEENTRY_ENTRY(DCM_INST(instIdx));

  /* setup context information for current Hsm */
  curHsmInfo->serviceId =
    Dcm_BufferConfig[Dcm_RxPduIdConfig[curHsmInfo->rxPduId].rxBufferId].ptrBuffer[0];

  curHsmInfo->negativeResponseCode = DCM_E_OK;

  /* Reset the page processing function id */
  curHsmInfo->processPageFuncId = DCM_PROCESS_PAGE_ID_INVALID;

  /* Set the service type to DSP implementation */
  curHsmInfo->dspService = TRUE;

  /* ENTER critical section */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* status of transmission data is not ok */
  curHsmInfo->txDataState = DCM_NO_TX_DATA;

  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();


  DBG_DCM_HSMDCMSFINSERVICEENTRY_EXIT(DCM_INST(instIdx));
}
FUNC(void, DCM_CODE) Dcm_HsmDcmSfInServiceAction1(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* action 'if (RetryTimer==0) CallService(PENDING)'
   * for RETRY[]/...
   * internal transition */
#if (DCM_ASYNC_SERVICE_HANDLER == STD_ON)
  CONSTP2CONST(Dcm_SidTabConfigType, AUTOMATIC, DCM_CONST) curSidTabConfig
      = &Dcm_SidTabConfig[DCM_HSM_CONFIG(instIdx).sidTabId];
#endif /* #if(DCM_ASYNC_SERVICE_HANDLER == STD_ON) */
#if ((DCM_ASYNC_SERVICE_HANDLER == STD_ON) || (DCM_DSP_USE_SERVICE_0X2F == STD_ON))
  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);
#endif /* #if(DCM_ASYNC_SERVICE_HANDLER == STD_ON) */

  DBG_DCM_HSMDCMSFINSERVICEACTION1_ENTRY(DCM_INST(instIdx));

  /* Call service handler, when retry timer expires */

  if (0U == DCM_HSM_INFO(instIdx).retryTimer)
  {
#if (DCM_ASYNC_SERVICE_HANDLER == STD_ON)
    if((curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).AsyncServiceExecution != TRUE)
    {
#if(DCM_DSP_USE_SERVICE_0X2F == STD_ON)
      if ( (curHsmInfo->serviceId == 0x22) || (curHsmInfo->serviceId == 0x2E) ||
           (curHsmInfo->serviceId == 0x2F)
          )
      {
        if (Dcm_ReturnControlToEcuContext.returnCtrlToECUStatus == DCM_RET_CTRL_PENDING)
        {
          /* try again after timeout */
          DCM_HSM_INFO(instIdx).retryTimer = 1U;
        }
        else if (Dcm_ReturnControlToEcuContext.returnCtrlToECUStatus == DCM_RET_CTRL_FINISHED)
        {
          /* DIDs are now in a known state, start normal service processing and
             reset the flag*/
          Dcm_DspInternal_SvcFunc(DCM_CUR_INST_ID(instIdx), DCM_INITIAL);
          Dcm_ReturnControlToEcuContext.returnCtrlToECUStatus = DCM_RET_CTRL_INACTIVE;
        }
        else
        {
          /* Flag has been reset DIDs are in a known state, just normal procesing
             from here on */
          Dcm_DspInternal_SvcFunc(DCM_CUR_INST_ID(instIdx), DCM_PENDING);
        }
      }
      else
#endif
      {
        Dcm_DspInternal_SvcFunc(DCM_CUR_INST_ID(instIdx), DCM_PENDING);
      }
    }
#else
#if(DCM_DSP_USE_SERVICE_0X2F == STD_ON)
    if ( (curHsmInfo->serviceId == 0x22) || (curHsmInfo->serviceId == 0x2E) ||
         (curHsmInfo->serviceId == 0x2F)
        )
    {
      if (Dcm_ReturnControlToEcuContext.returnCtrlToECUStatus == DCM_RET_CTRL_PENDING)
      {
        /* try again after timeout */
        DCM_HSM_INFO(instIdx).retryTimer = 1U;
      }
      else if (Dcm_ReturnControlToEcuContext.returnCtrlToECUStatus == DCM_RET_CTRL_FINISHED)
      {
        /* DIDs are now in a known state, start normal service processing and
           reset the flag*/
        Dcm_DspInternal_SvcFunc(DCM_CUR_INST_ID(instIdx), DCM_INITIAL);
        Dcm_ReturnControlToEcuContext.returnCtrlToECUStatus = DCM_RET_CTRL_INACTIVE;
      }
      else
      {
        /* Flag has been reset. DIDs are in a known state, just normal procesing
           from here on*/
        Dcm_DspInternal_SvcFunc(DCM_CUR_INST_ID(instIdx), DCM_PENDING);
      }
    }
    else
#endif
    {
      Dcm_DspInternal_SvcFunc(DCM_CUR_INST_ID(instIdx), DCM_PENDING);
    }
#endif /* #if(DCM_ASYNC_SERVICE_HANDLER == STD_ON) */
  }

  DBG_DCM_HSMDCMSFINSERVICEACTION1_EXIT(DCM_INST(instIdx));
}

/* ************************************************************************
 * State: Finishing
 * Parent state: InService
 * Init substate: ConfirmingOk
 * Transitions originating from this state:
 * 1) Finishing -> OosNotified: PROC_DONE[]/
 */

 FUNC(void, DCM_CODE) Dcm_HsmDcmSfFinishingEntry(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* entry action 'StopTimer2();' */
  DBG_DCM_HSMDCMSFFINISHINGENTRY_ENTRY(DCM_INST(instIdx));

  Dcm_StopTimer2(DCM_PL_SF(instIdx));

  DBG_DCM_HSMDCMSFFINISHINGENTRY_EXIT(DCM_INST(instIdx));
}

FUNC(void, DCM_CODE) Dcm_HsmDcmSfFinishingExit(
   DCM_PDL_SF(const uint8 instIdx))
{
  /* exit action 'if (non-default session) StartTimer3(S3Timer)' */

  /* Get SesTabConfig info */
  CONSTP2CONST(Dcm_SesTabConfigType, AUTOMATIC, DCM_CONST) sesTabConfig =
    &Dcm_SesTabConfig[DCM_CUR_INST_ID(instIdx)];

  DBG_DCM_HSMDCMSFFINISHINGEXIT_ENTRY(DCM_INST(instIdx));

  /* ENTER critical section */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* Start S3 timer, if processed request is a normal diagnostic request
   * (ie, Neither ROE nor PR), a non-default session is active and no new
   * request is in reception. */
  if ((DCM_HSM_INFO(instIdx).msgContext.msgAddInfo.messageType == DCM_NORMAL) &&
      (sesTabConfig->SessionEntries[DCM_HSM_INFO(instIdx).sesTabIdx].SesCtrl != DCM_DEFAULT_SESSION) &&
      (Dcm_ReqProcessing == FALSE)
     )
  {
    Dcm_StartTimer3(DCM_PL_START_TIMER(instIdx, DCM_S3SERVER_TICK_DEFAULT));
  }

  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  DBG_DCM_HSMDCMSFFINISHINGEXIT_EXIT(DCM_INST(instIdx));
}

/* ************************************************************************
 * State: CancelProcessing
 * Parent state: Finishing
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) CancelProcessing -> OosNotified: FORCE_RCRRP[]/
 * 2) CancelProcessing -> OosNotified: PROCESS_PAGE[]/
 * 3) CancelProcessing -> OosNotified: PROC_ABORT[]/
 * 4) CancelProcessing -> OosNotified: TX_CONF_NOT_OK[]/
 * 5) CancelProcessing -> OosNotified: TX_CONF_OK[]/
 */

FUNC(void, DCM_CODE) Dcm_HsmDcmSfCancelProcessingEntry(
  DCM_PDL_SF(const uint8 instIdx))
{

  DBG_DCM_HSMDCMSFCANCELPROCESSINGENTRY_ENTRY(DCM_INST(instIdx));

  /* entry action depending if is a Paged Buffering Processing or Normal Processing*/
  if (Dcm_PageBufferInProgress(DCM_CUR_INST_ID(instIdx)) == FALSE) 
  {
    /* Non-PageBuffered cancellation */ 
    Dcm_DspInternal_CancelProcessing(); 
  } 
  else 
  { 
    /* PageBuffered cancellation */ 
#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
    Dcm_DspInternal_CancelPagedBufferProcessing();
#endif /* #if (DCM_PAGEDBUFFER_ENABLED == STD_ON) */
  }

  DBG_DCM_HSMDCMSFCANCELPROCESSINGENTRY_EXIT(DCM_INST(instIdx));
}

/* ************************************************************************
 * State: ConfirmingNOk
 * Parent state: Finishing
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 */

FUNC(void, DCM_CODE) Dcm_HsmDcmSfConfirmingNOkEntry(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* entry action 'DspInternal_DcmConfirmation(NOT_OK);' */

  /* get the context information current instance */
  P2CONST(Dcm_HsmInfoType, AUTOMATIC, DCM_CONST) curHsmInfo
    = &(DCM_HSM_INFO(instIdx));
  /* holds the confirmation status */
  Dcm_ConfirmationStatusType status;

  DBG_DCM_HSMDCMSFCONFIRMINGNOKENTRY_ENTRY(DCM_INST(instIdx));

  if(curHsmInfo->negativeResponseCode == DCM_E_OK)
  {
    status = DCM_RES_POS_NOT_OK;
  }
  else
  {
    status = DCM_RES_NEG_NOT_OK;
  }

  /* confirm the transmission */
  Dcm_DspInternal_DcmConfirmation(curHsmInfo->msgContext.idContext,
                                  curHsmInfo->rxPduId,
                                  status);

  DBG_DCM_HSMDCMSFCONFIRMINGNOKENTRY_EXIT(DCM_INST(instIdx));
}

/* ************************************************************************
 * State: ConfirmingOk
 * Parent state: Finishing
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 */

FUNC(void, DCM_CODE) Dcm_HsmDcmSfConfirmingOkEntry(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* entry action 'DspInternal_DcmConfirmation(OK);' */

  /* get the context information current instance */
  P2CONST(Dcm_HsmInfoType, AUTOMATIC, DCM_CONST) curHsmInfo
    = &(DCM_HSM_INFO(instIdx));
  /* holds the confirmation status */
  Dcm_ConfirmationStatusType status;

  DBG_DCM_HSMDCMSFCONFIRMINGOKENTRY_ENTRY(DCM_INST(instIdx));

  if(curHsmInfo->negativeResponseCode == DCM_E_OK)
  {
    status = DCM_RES_POS_OK;
  }
  else
  {
    status = DCM_RES_NEG_OK;
  }

  /* confirm the transmission */
  Dcm_DspInternal_DcmConfirmation(curHsmInfo->msgContext.idContext,
                                  curHsmInfo->rxPduId,
                                  status);

  DBG_DCM_HSMDCMSFCONFIRMINGOKENTRY_EXIT(DCM_INST(instIdx));
}

/* ************************************************************************
 * State: RoePrServiceCalled
 * Parent state: InService
 * Init substate: RoePrResponse
 * Transitions originating from this state:
 * 1) RoePrServiceCalled -> PgBufProcessing: PROCESS_PAGE[]/
 * 2) RoePrServiceCalled -> OosNotified: PROC_ABORT[]/Free Rx Buffer; Free Tx Buffer
 * 3) RoePrServiceCalled -> Sending: PROC_DONE[]/
 */

FUNC(void, DCM_CODE) Dcm_HsmDcmSfRoePrServiceCalledAction2(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* action 'Free Rx Buffer; Free Tx Buffer'
   * for PROC_ABORT[]/...
   * external transition to state OosNotified */

  DBG_DCM_HSMDCMSFROEPRSERVICECALLEDACTION2_ENTRY(DCM_INST(instIdx));

  /* Release rx and tx buffers */
  Dcm_ReleaseRxTxBuffers(DCM_INST(instIdx));

  DBG_DCM_HSMDCMSFROEPRSERVICECALLEDACTION2_EXIT(DCM_INST(instIdx));
}

#if (DCM_ROE_ENABLED == STD_ON)
/*!
 * \brief Set the correct transmission Pdu IDs for ROE response messages
 *
 * \param[in] instIdx - Current state machine instance index
 *
 */

STATIC FUNC(void, DCM_CODE) Dcm_HsmDcmSetRoePduIdsAndProtocolData(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* Holds the RxPduId configuration */
  CONSTP2CONST(Dcm_RxPduIdConfigType, AUTOMATIC, DCM_VAR) curRxPduIdConfig
    = &Dcm_RxPduIdConfig[Dcm_RoeData.DcmRxPduId];

  /* Get the current state machine info */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo
    = &DCM_HSM_INFO(instIdx);


  /* ENTER critical section. 
     Dcm_CurProtocolId and curHsmInfo->rxPduId must be set together. */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* Set rx PduID*/
  curHsmInfo->rxPduId = Dcm_RoeData.DcmRxPduId;

  /* Set current Protocol Id */
  Dcm_CurProtocolId = curRxPduIdConfig->protocolId;

  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();


  /* Set tx PduID*/
  curHsmInfo->txPduId = Dcm_TxPduIds[curRxPduIdConfig->connectionId].txPduId;

  /* Set txConfirmation PduID*/
  curHsmInfo->txConfirmationPduId = Dcm_TxPduIds[curRxPduIdConfig->connectionId].txConfirmationPduId;
}
#endif

/* ************************************************************************
 * State: RoeFinalResponse
 * Parent state: RoePrServiceCalled
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 */

FUNC(void, DCM_CODE) Dcm_HsmDcmSfRoeFinalResponseEntry(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* entry action 'UpdateFinalResponse()' */

  DBG_DCM_HSMDCMSFROEFINALRESPONSEENTRY_ENTRY(DCM_INST(instIdx));

#if(DCM_ROE_ENABLED == STD_ON)
  Dcm_DspInternal_FinalRoeResponse(DCM_INST(instIdx));
#else
  TS_PARAM_UNUSED(DCM_INST(instIdx));
#endif /* if(DCM_ROE_ENABLED == STD_ON) */

  DBG_DCM_HSMDCMSFROEFINALRESPONSEENTRY_EXIT(DCM_INST(instIdx));
}

/* ************************************************************************
 * State: RoePrResponse
 * Parent state: RoePrServiceCalled
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 */

FUNC(void, DCM_CODE) Dcm_HsmDcmSfRoePrResponseEntry(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* entry action 'DispatchServiceReq();' */

  DBG_DCM_HSMDCMSFROEPRRESPONSEENTRY_ENTRY(DCM_INST(instIdx));

#if(DCM_ROE_ENABLED == STD_ON)

  /* ENTER critical section */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* change ROE processing status flag from QUEUED to PROCESSING */
  DBG_DCM_ROEPROCESSING((Dcm_ROEProcessing),(DCM_ROE_PROCESSING));
  Dcm_ROEProcessing = DCM_ROE_PROCESSING;

  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  Dcm_DsdInternal_DispatchSvcReq(DCM_PL_SF(instIdx));
#else
  TS_PARAM_UNUSED(DCM_INST(instIdx));
#endif /* if(DCM_ROE_ENABLED == STD_ON) */

  DBG_DCM_HSMDCMSFROEPRRESPONSEENTRY_EXIT(DCM_INST(instIdx));
}

/* ************************************************************************
 * State: Sending
 * Parent state: InService
 * Init substate: NormalProcessing
 * Transitions originating from this state:
 * 1) Sending -> ConfirmingNOk: TX_CONF_NOT_OK[]/
 * 2) Sending -> Finishing: TX_CONF_OK[]/
 */

 FUNC(void, DCM_CODE) Dcm_HsmDcmSfSendingEntry(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* entry action 'StopTimer2();StopTimerTx();' */
  DBG_DCM_HSMDCMSFSENDINGENTRY_ENTRY(DCM_INST(instIdx));

  Dcm_StopTimer2(DCM_PL_SF(instIdx));
  Dcm_StopTimerTx(DCM_PL_SF(instIdx));

  DBG_DCM_HSMDCMSFSENDINGENTRY_EXIT(DCM_INST(instIdx));
}

/* ************************************************************************
 * State: NormalProcessing
 * Parent state: Sending
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 */

FUNC(void, DCM_CODE) Dcm_HsmDcmSfNormalProcessingEntry(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* entry action 'TxPduId.dataState=TX_DATA_READY;PduR_DcmTransmit();' */

  Std_ReturnType retVal;

  /* get the context information current instance */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo
    = &DCM_HSM_INFO(instIdx);

  VAR(PduInfoType, DCM_VAR) Dcm_TxInformation;

  DBG_DCM_HSMDCMSFNORMALPROCESSINGENTRY_ENTRY(DCM_INST(instIdx));

  /* ENTER critical section */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* data is ready to send */
  DCM_TX_DATA_STATE(instIdx) = DCM_TX_DATA_READY;

  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  if (curHsmInfo->negativeResponseCode != DCM_E_OK)
  {
    /* get negative response buffer */
    CONSTP2VAR(uint8, AUTOMATIC, DCM_VAR) nrBuffer = DCM_NR_BUFFER(instIdx).ptrBuffer;

    /* assemble negative response including:
     *     - currently processed service Id
     *     - currently occurred negative response code */
    nrBuffer[1] = curHsmInfo->serviceId;
    nrBuffer[2] = curHsmInfo->negativeResponseCode;

    /* set the data buffer and length */
    curHsmInfo->msgContext.resDataLen  = 2U;

    /* Update filledLen with NRC response length as this is used in CopyTxData to update remaining
     * response length
     */
    /* set the data buffer and length */
    curHsmInfo->msgContext.resDataLen  = 2U;
    curHsmInfo->curTxBuffer = &DCM_NR_BUFFER(instIdx);
  }
  else
  {
    /* set the data buffer */
    curHsmInfo->curTxBuffer
      = &Dcm_BufferConfig[DCM_HSM_CONFIG(instIdx).txBufferId];
  }

  /* Update filledLen with response length */
  curHsmInfo->curTxBuffer->bufferInfo->filledLen = curHsmInfo->msgContext.resDataLen + 1U;

  /* The length has to be incremented as response ID was already added */
  Dcm_TxInformation.SduLength = curHsmInfo->msgContext.resDataLen + 1U;

  /* The length to be transmitted is memorized here as this is not a paged-buffer context */
  DCM_HSM_INFO(instIdx).sentLength = Dcm_TxInformation.SduLength;

  /* Trigger transmission of diagnostic response from PduR */
  retVal = PduR_DcmTransmit(curHsmInfo->txPduId, &Dcm_TxInformation);

  /* if transmission failed, send signal DCM_TX_CONF_NOT_OK to current HSM
   * instance so that transmission is cancelled, release rx and tx buffers */
  if (retVal != E_OK)
  {
    /* get pointer to current message context */
    CONSTP2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext = &(DCM_HSM_INFO(instIdx).msgContext);

    (void)DCM_HSMEMITTOSELFINST_WRAPPER(&Dcm_HsmScDcm, DCM_CUR_INST_ID(instIdx),
                                                DCM_HSM_DCM_EV_TX_CONF_NOT_OK);

    /* Release rx and tx buffers */
    Dcm_ReleaseRxTxBuffers(DCM_INST(instIdx));


    SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

    if (pMsgContext->msgAddInfo.messageType == DCM_NORMAL)
    {
      /* Current Request processing is finished */
      DBG_DCM_REQPROCESSING((Dcm_ReqProcessing),(FALSE));
      Dcm_ReqProcessing = FALSE;
    }
    else if ((pMsgContext->msgAddInfo.messageType == DCM_ROE) || (pMsgContext->msgAddInfo.messageType == DCM_ROE_FINAL))
    {
      /* If currently stopping Request processing operation was ROE, unset ROE processing flag */
      DBG_DCM_ROEPROCESSING((Dcm_ROEProcessing),(DCM_ROE_NONE));
      Dcm_ROEProcessing = DCM_ROE_NONE;
    }
    /* CHECK: NOPARSE */
    else
    {
     /* Do nothing */
    }
    /* CHECK: PARSE */

    SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
  }

  DBG_DCM_HSMDCMSFNORMALPROCESSINGENTRY_EXIT(DCM_INST(instIdx));
}

/* ************************************************************************
 * State: PgBufProcessing
 * Parent state: Sending
 * Init substate: RealPgBufProcessing
 * Transitions originating from this state:
 */


/* ************************************************************************
 * State: EmulatePgBufProcessing
 * Parent state: PgBufProcessing
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) EmulatePgBufProcessing -> Finishing: PROCESS_PAGE[resTotLen>=MsgContext->resDataLen+1]/Free Rx Buffer; Free Tx Buffer;
 * 2) EmulatePgBufProcessing -> EmulatePgBufProcessing: PROCESS_PAGE[]/
 * 3) EmulatePgBufProcessing -> ConfirmingNOk: TIMEOUTPGBUF[]/Free Rx Buffer; Free Tx Buffer; DspInternal_CancelPagedBufferProcessing()
 */

FUNC(void, DCM_CODE) Dcm_HsmDcmSfEmulatePgBufProcessingEntry(
  DCM_PDL_SF(const uint8 instIdx))
{
/* entry action 'StartTimerPgBuf(PagedBufferTimeout);TxBuf.filledLen=0; DspInternal_UpdatePage();' */

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  /* get configuration of current transmission(Tx) buffer */
  CONSTP2CONST(Dcm_BufferConfigType, AUTOMATIC, DCM_CONST) curTxBufferConfig
    = &Dcm_BufferConfig[DCM_HSM_CONFIG(instIdx).txBufferId];

  /* Start timeout for Paged Buffer transmission */
  Dcm_StartTimerPgBuf(DCM_PL_START_TIMER(instIdx, DCM_PAGED_BUFFER_TIMEOUT));

  DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGENTRY_ENTRY(DCM_INST(instIdx));

  /* ENTER critical section */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  curTxBufferConfig->bufferInfo->filledLen = 0U;

  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* get first page of response, see sec 9.3.2 in SWS R3.1 */
  /* get first page of response, always provide the full buffer as we discard
   * the already received data all the time. */
  if (DCM_HSM_INFO(instIdx).dspService)
  {
    Dcm_DspInternal_UpdatePage(&curTxBufferConfig->ptrBuffer[0],
      curTxBufferConfig->size);
  }
  /* CHECK: NOPARSE */
  else
  {
    /* Defensive branch, paged-buffer handling is not available
     * for the Application (DCM-internal use only)*/
  }
  /* CHECK: PARSE */

#else
  DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGENTRY_ENTRY(DCM_INST(instIdx));
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  TS_PARAM_UNUSED(instIdx);
#endif /* #if (DCM_HSM_INST_MULTI_ENABLED == STD_ON) */
#endif /* #if (DCM_PAGEDBUFFER_ENABLED == STD_ON) */

  DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGENTRY_EXIT(DCM_INST(instIdx));
}

FUNC(void, DCM_CODE) Dcm_HsmDcmSfEmulatePgBufProcessingExit(
   DCM_PDL_SF(const uint8 instIdx))
{
  /* exit action 'StopTimerPgBuf();' */

  DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGEXIT_ENTRY(DCM_INST(instIdx));

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  Dcm_StopTimerPgBuf(DCM_PL_SF(instIdx));
#else
  TS_PARAM_UNUSED(DCM_INST(instIdx));
#endif

  DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGEXIT_EXIT(DCM_INST(instIdx));
}

FUNC(boolean, DCM_CODE) Dcm_HsmDcmSfEmulatePgBufProcessingGuard1(
  DCM_PDL_SF(const uint8 instIdx))
{
  boolean retVal;

  /* guard condition 'resTotLen>=MsgContext->resDataLen+1'
   * for PROCESS_PAGE[...]/Free Rx Buffer; Free Tx Buffer;
   * external transition to state Finishing */
#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  /* get the context information current instance */
  P2CONST(Dcm_HsmInfoType, AUTOMATIC, DCM_CONST) curHsmInfo
    = &(DCM_HSM_INFO(instIdx));

  DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGGUARD1_ENTRY(DCM_INST(instIdx));

  /* check if service function already has sent all response data incl. SID */
  retVal = (curHsmInfo->sentLength >= ((curHsmInfo->msgContext.resDataLen) + 1U));
#else
  DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGGUARD1_ENTRY(DCM_INST(instIdx));

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  TS_PARAM_UNUSED(instIdx);
#endif /* #if (DCM_HSM_INST_MULTI_ENABLED == STD_ON) */

  retVal = TRUE;
#endif /* #if (DCM_PAGEDBUFFER_ENABLED == STD_ON) */

  DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGGUARD1_EXIT(retVal, DCM_INST(instIdx));
  return retVal;
}
FUNC(void, DCM_CODE) Dcm_HsmDcmSfEmulatePgBufProcessingAction1(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* action 'Free Rx Buffer; Free Tx Buffer;'
   * for PROCESS_PAGE[resTotLen>=MsgContext->resDataLen+1]/...
   * external transition to state Finishing */

  /* get pointer to current message context */
  CONSTP2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext = &(DCM_HSM_INFO(instIdx).msgContext);

  DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGACTION1_ENTRY(DCM_INST(instIdx));

  /* Release rx and tx buffers */
  Dcm_ReleaseRxTxBuffers(DCM_INST(instIdx));


  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  if (pMsgContext->msgAddInfo.messageType == DCM_NORMAL)
  {
    /* Current Request processing is finished */
    DBG_DCM_REQPROCESSING((Dcm_ReqProcessing),(FALSE));
    Dcm_ReqProcessing = FALSE;
  }
  else if ((pMsgContext->msgAddInfo.messageType == DCM_ROE) || (pMsgContext->msgAddInfo.messageType == DCM_ROE_FINAL))
  {
    /* If currently stopping Request processing operation was ROE, unset ROE processing flag */
    DBG_DCM_ROEPROCESSING((Dcm_ROEProcessing),(DCM_ROE_NONE));
    Dcm_ROEProcessing = DCM_ROE_NONE;
  }
  /* CHECK: NOPARSE */
  else
  {
   /* Do nothing */
  }
  /* CHECK: PARSE */

  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();


  DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGACTION1_EXIT(DCM_INST(instIdx));
}

FUNC(void, DCM_CODE) Dcm_HsmDcmSfEmulatePgBufProcessingAction3(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* action 'Free Rx Buffer; Free Tx Buffer; DspInternal_CancelPagedBufferProcessing()'
   * for TIMEOUTPGBUF[]/...
   * external transition to state ConfirmingNOk */

  DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGACTION3_ENTRY(DCM_INST(instIdx));

  DCM_TX_DATA_STATE(instIdx) = DCM_TX_DATA_NOT_OK; 
     
  /* Release rx and tx buffers */
  Dcm_ReleaseRxTxBuffers(DCM_INST(instIdx));
  
#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  /* if Paged buffer handling enabled */
  Dcm_DspInternal_CancelPagedBufferProcessing();
#endif /* #if (DCM_PAGEDBUFFER_ENABLED == STD_ON) */

  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* As processing is now finished, reset the flag for current processing in execution */
  DBG_DCM_REQPROCESSING((Dcm_ReqProcessing),(FALSE));
  Dcm_ReqProcessing = FALSE;

  /* If currently stopping Request processing operation was ROE, unset ROE processing flag */
  DBG_DCM_ROEPROCESSING((Dcm_ROEProcessing),(DCM_ROE_NONE));
  Dcm_ROEProcessing = DCM_ROE_NONE;

  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGACTION3_EXIT(DCM_INST(instIdx));
}


/* ************************************************************************
 * State: RealPgBufProcessing
 * Parent state: PgBufProcessing
 * Init substate: PgBufDataAvailable
 * Transitions originating from this state:
 * 1) TIMEOUTPGBUF[]/DspInternal_CancelPagedBufferProcessing
 */

FUNC(void, DCM_CODE) Dcm_HsmDcmSfRealPgBufProcessingEntry(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* entry action 'PduR_DcmTransmit();' */
#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  Std_ReturnType retVal;

  /* use a local copy of PduInfo here instead of Dcm_TxInformation[] as the
   * Dcm_TxInformation entrie is already prepared for sending the first
   * page */
  PduInfoType PduInfo;

  DBG_DCM_HSMDCMSFREALPGBUFPROCESSINGENTRY_ENTRY(DCM_INST(instIdx));

  /* The length has to be incremented as response ID was already  added */
  /* The length to be transmitted in this page has been added to the DCM_HSM_INFO(instIdx).sentLength
     in the Dcm_DsdInternal_StartPagedProcessing() function */
  PduInfo.SduLength  = DCM_HSM_INFO(instIdx).msgContext.resDataLen + 1U;
  PduInfo.SduDataPtr = &(Dcm_BufferConfig[DCM_HSM_CONFIG(instIdx).txBufferId].ptrBuffer[0]);

  /* Start transmission of diagnostic response to the PduR */
  retVal = PduR_DcmTransmit(DCM_HSM_INFO(instIdx).txPduId, &PduInfo);

  /* if transmission failed, send signal DCM_TX_CONF_NOT_OK to current HSM
   * instance so that transmission is canceled, release rx and tx buffers */
  if (retVal != E_OK)
  {
    /* get pointer to current message context */
    CONSTP2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext = &(DCM_HSM_INFO(instIdx).msgContext);

    (void)DCM_HSMEMITTOSELFINST_WRAPPER(&Dcm_HsmScDcm, DCM_CUR_INST_ID(instIdx),
                                                    DCM_HSM_DCM_EV_TX_CONF_NOT_OK);

    /* Release rx and tx buffers */
    Dcm_ReleaseRxTxBuffers(DCM_INST(instIdx));


    SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

    if (pMsgContext->msgAddInfo.messageType == DCM_NORMAL)
    {
      /* Current Request processing is finished */
      DBG_DCM_REQPROCESSING((Dcm_ReqProcessing),(FALSE));
      Dcm_ReqProcessing = FALSE;
    }
    else if ((pMsgContext->msgAddInfo.messageType == DCM_ROE) || (pMsgContext->msgAddInfo.messageType == DCM_ROE_FINAL))
    {
      /* If currently stopping Request processing operation was ROE, unset ROE processing flag */
      DBG_DCM_ROEPROCESSING((Dcm_ROEProcessing),(DCM_ROE_NONE));
      Dcm_ROEProcessing = DCM_ROE_NONE;
    }
    /* CHECK: NOPARSE */
    else
    {
     /* Do nothing */
    }
    /* CHECK: PARSE */

    SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  }
#else
  DBG_DCM_HSMDCMSFREALPGBUFPROCESSINGENTRY_ENTRY(DCM_INST(instIdx));
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  TS_PARAM_UNUSED(instIdx);
#endif /* #if (DCM_HSM_INST_MULTI_ENABLED == STD_ON) */
#endif /* #if (DCM_PAGEDBUFFER_ENABLED == STD_ON) */

  DBG_DCM_HSMDCMSFREALPGBUFPROCESSINGENTRY_EXIT(DCM_INST(instIdx));
}

FUNC(void, DCM_CODE) Dcm_HsmDcmSfRealPgBufProcessingAction1(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* action 'DspInternal_CancelPagedBufferProcessing'
   * for TIMEOUTPGBUF[]/...
   * internal transition */

  DBG_DCM_HSMDCMSREALPGBUFPROCESSINGACTION1_ENTRY(DCM_INST(instIdx));

  DCM_TX_DATA_STATE(instIdx) = DCM_TX_DATA_NOT_OK; 
     
  /* Release rx and tx buffers */
  Dcm_ReleaseRxTxBuffers(DCM_INST(instIdx));
  
#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  /* if Paged buffer handling enabled */
  Dcm_DspInternal_CancelPagedBufferProcessing();
#endif /* #if (DCM_PAGEDBUFFER_ENABLED == STD_ON) */

  DBG_DCM_HSMDCMSREALPGBUFPROCESSINGACTION1_EXIT(DCM_INST(instIdx));

}

/* ************************************************************************
 * State: PgBufDataAvailable
 * Parent state: RealPgBufProcessing
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) PgBufDataAvailable -> PgBufDataRequested: PROVIDE_TX_BUF[]/
 */

FUNC(void, DCM_CODE) Dcm_HsmDcmSfPgBufDataAvailableEntry(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* entry action 'SduLength=TxBuf.filledLength;TxPduId.dataState=TX_DATA_READY;' */

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)

  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

  DBG_DCM_HSMDCMSFPGBUFDATAAVAILABLEENTRY_ENTRY(DCM_INST(instIdx));

  /* ENTER critical section */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* update length information in Pdu Info type passed to PDU Router via Dcm
   * callback functions */

  /* Data is ready to be transmitted */
  DCM_TX_DATA_STATE(instIdx) = DCM_TX_DATA_READY;

  /* Update the buffer passed to PduR Router via Dcm callback functions */
  curHsmInfo->curTxBuffer = &Dcm_BufferConfig[DCM_HSM_CONFIG(instIdx).txBufferId];

  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
#else
  DBG_DCM_HSMDCMSFPGBUFDATAAVAILABLEENTRY_ENTRY(DCM_INST(instIdx));
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  TS_PARAM_UNUSED(instIdx);
#endif /* #if (DCM_HSM_INST_MULTI_ENABLED == STD_ON) */
#endif /* #if (DCM_PAGEDBUFFER_ENABLED == STD_ON) */

  DBG_DCM_HSMDCMSFPGBUFDATAAVAILABLEENTRY_EXIT(DCM_INST(instIdx));
}

/* ************************************************************************
 * State: PgBufDataRequested
 * Parent state: RealPgBufProcessing
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) PgBufDataRequested -> PgBufDataAvailable: PROCESS_PAGE[]/
 */

FUNC(void, DCM_CODE) Dcm_HsmDcmSfPgBufDataRequestedEntry(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* entry action 'DspInternal_UpdatePage();StartTimerPgBuf(PagedBufferTimeout);' */

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  /* get the context information current instance */
  P2CONST(Dcm_BufferConfigType, AUTOMATIC, DCM_CONST) txBufferConfig =
    &Dcm_BufferConfig[DCM_HSM_CONFIG(instIdx).txBufferId];
  /* for holding the filled length */
  PduLengthType FilledLength;

  DBG_DCM_HSMDCMSFPGBUFDATAREQUESTEDENTRY_ENTRY(DCM_INST(instIdx));

  /* ENTER critical section */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* Get the length of data filled in Tx Buffer */
  FilledLength = txBufferConfig->bufferInfo->filledLen;

  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* Get new data from service */
  if (DCM_HSM_INFO(instIdx).dspService)
  {
    Dcm_DspInternal_UpdatePage(
      &txBufferConfig->ptrBuffer[FilledLength],
      /* buffer size minus length of data already stored in buffer */
      txBufferConfig->size - FilledLength);
  }
  /* CHECK: NOPARSE */
  else
  {
    /* Defensive branch. Paged-buffer handling is not available for user-implementated services  */
  }
  /* CHECK: PARSE */

  /* Start timeout for Paged Buffer transmission */
  Dcm_StartTimerPgBuf(DCM_PL_START_TIMER(instIdx, DCM_PAGED_BUFFER_TIMEOUT));
#else
  DBG_DCM_HSMDCMSFPGBUFDATAREQUESTEDENTRY_ENTRY(DCM_INST(instIdx));
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  TS_PARAM_UNUSED(instIdx);
#endif /* #if (DCM_HSM_INST_MULTI_ENABLED == STD_ON) */
#endif /* #if (DCM_PAGEDBUFFER_ENABLED == STD_ON) */


  DBG_DCM_HSMDCMSFPGBUFDATAREQUESTEDENTRY_EXIT(DCM_INST(instIdx));
}
FUNC(void, DCM_CODE) Dcm_HsmDcmSfPgBufDataRequestedExit(
   DCM_PDL_SF(const uint8 instIdx))
{
 /* exit action 'StopTimerPgBuf();' */

  DBG_DCM_HSMDCMSFPGBUFDATAREQUESTEDEXIT_ENTRY(DCM_INST(instIdx));

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  /* Stop timers P2ServerMax, P2StarServerMax and PgBufTimeout */

  Dcm_StopTimerPgBuf(DCM_PL_SF(instIdx));

#endif /* #if (DCM_PAGEDBUFFER_ENABLED == STD_ON) */
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  TS_PARAM_UNUSED(instIdx);
#endif /* #if (DCM_HSM_INST_MULTI_ENABLED == STD_ON) */

  DBG_DCM_HSMDCMSFPGBUFDATAREQUESTEDEXIT_EXIT(DCM_INST(instIdx));
}

/* ************************************************************************
 * State: SendingGr
 * Parent state: InService
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) SendingGr -> CancelProcessing: TX_CONF_NOT_OK[]/
 * 2) SendingGr -> CancelProcessing: TX_CONF_OK[]/
 */

FUNC(void, DCM_CODE) Dcm_HsmDcmSfSendingGrEntry(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* entry action 'nrc = GeneralReject;PduR_DcmTransmit();StopTimer2();TxPduId.dataState=TX_DATA_READY;' */

  VAR(PduInfoType, DCM_VAR) Dcm_TxInformation;

  /* Get the network channel */
  uint8 channelIndex;
  Std_ReturnType retVal = E_NOT_OK;
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);
  /* get negative response buffer */
  CONSTP2VAR(uint8, AUTOMATIC, DCM_VAR) nrBuffer = DCM_NR_BUFFER(instIdx).ptrBuffer;

  channelIndex = Dcm_RxPduIdConfig[curHsmInfo->rxPduId].channelIdIndex;

  DBG_DCM_HSMDCMSFSENDINGGRENTRY_ENTRY(DCM_INST(instIdx));

#if (DCM_ASYNC_SERVICE_HANDLER == STD_ON)
  /* The async service processor can access negativeResponseCode in parallel
   * from within a different task context than the HSM */

  /* ENTER critical section */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
#endif

  /* set NRC GeneralReject */
  curHsmInfo->negativeResponseCode = DCM_E_GENERALREJECT;

#if (DCM_ASYNC_SERVICE_HANDLER == STD_ON)
  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
#endif

  /* assemble negative response including:
   *     - currently processed service Id
   *     - currently occured negative response code */
  nrBuffer[1] = curHsmInfo->serviceId;
  nrBuffer[2] = DCM_E_GENERALREJECT;

  /* set the Tx data buffer and length */
  curHsmInfo->msgContext.resDataLen  = 2U;
  curHsmInfo->curTxBuffer = &DCM_NR_BUFFER(instIdx);

  /* Set the data state to ready */
  DCM_TX_DATA_STATE(instIdx) = DCM_TX_DATA_READY;

  /* The length has to be incremented as response ID was already added */
  Dcm_TxInformation.SduLength = curHsmInfo->msgContext.resDataLen + 1U;

  /* Update filledLen with NRC response length as this is used in CopyTxData to update remaining
   * response length
   */

  /* Update filledLen with response length */
  curHsmInfo->curTxBuffer->bufferInfo->filledLen = curHsmInfo->msgContext.resDataLen + 1U;

  /* The length to be transmitted is memorized here as this is not a paged-buffer context */
  DCM_HSM_INFO(instIdx).sentLength = Dcm_TxInformation.SduLength;


  if (TRUE == Dcm_TxEnabled[channelIndex])
  {
    /* Trigger transmission of diagnostic response from PduR */
    retVal = PduR_DcmTransmit(DCM_HSM_INFO(instIdx).txPduId, &Dcm_TxInformation);
  }

  if ((FALSE == Dcm_TxEnabled[channelIndex]) || (retVal != E_OK))
  {

  /* if transmission failed, send signal DCM_TX_CONF_NOT_OK to current HSM
   * instance so that transmission is canceled, release rx and tx buffers */

    (void)DCM_HSMEMITTOSELFINST_WRAPPER(&Dcm_HsmScDcm, DCM_CUR_INST_ID(instIdx),
                                  DCM_HSM_DCM_EV_TX_CONF_NOT_OK);
    /* Release rx and tx buffers */
    Dcm_ReleaseRxTxBuffers(DCM_INST(instIdx));


    SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

    /* Current Request processing is finished */
    DBG_DCM_REQPROCESSING((Dcm_ReqProcessing),(FALSE));
    Dcm_ReqProcessing = FALSE;

    SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
  }

  Dcm_StopTimer2(DCM_PL_SF(instIdx));

  DBG_DCM_HSMDCMSFSENDINGGRENTRY_EXIT(DCM_INST(instIdx));
}

/* ************************************************************************
 * State: ServiceCalled
 * Parent state: InService
 * Init substate: WaitForAppl
 * Transitions originating from this state:
 * 1) ServiceCalled -> EmulatePgBufProcessing: PROCESS_PAGE[spr]/
 * 2) ServiceCalled -> PgBufProcessing: PROCESS_PAGE[!Dcm_SupressResponse() && Tx En]/
 * 3) ServiceCalled -> WaitForFullComProcess: PROCESS_PAGE[!Dcm_SupressResponse() && Tx Dis]/
 * 4) ServiceCalled -> OosNotified: PROC_ABORT[]/Free Rx Buffer; Free Tx Buffer; if (non-default session) StartTimer3(S3Timer);
 * 5) ServiceCalled -> Finishing: PROC_DONE[Dcm_SupressResponse()]/Free Rx Buffer; Free Tx Buffer;
 * 6) ServiceCalled -> Sending: PROC_DONE[!Dcm_SupressResponse() && Tx En]/
 * 7) ServiceCalled -> WaitForFullComProcess: PROC_DONE[!Dcm_SupressResponse() && Tx Dis]/
 * 8) ServiceCalled -> SendingGr: TX_CONF_NOT_OK[]/
 */

FUNC(void, DCM_CODE) Dcm_HsmDcmSfServiceCalledEntry(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* entry action 'DispatchServiceReq();RespPendInFirstCycle();RpCntr=0;' */

  DBG_DCM_HSMDCMSFSERVICECALLEDENTRY_ENTRY(DCM_INST(instIdx));
  /* reset the response counter */
  DCM_HSM_INFO(instIdx).rpCntr = 0;

  /* process the service request */
  Dcm_DsdInternal_DispatchSvcReq(DCM_PL_SF(instIdx));

  /* If necessary send a RCRRP in the first cycle */
  RespPendInFirstCycle(DCM_PL_SF(instIdx));

  DBG_DCM_HSMDCMSFSERVICECALLEDENTRY_EXIT(DCM_INST(instIdx));
}

FUNC(boolean, DCM_CODE) Dcm_HsmDcmSfServiceCalledGuard1(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* guard condition 'spr'
   * for PROCESS_PAGE[...]/
   * external transition to state EmulatePgBufProcessing */
  boolean retVal;

  DBG_DCM_HSMDCMSFSERVICECALLEDGUARD1_ENTRY(DCM_INST(instIdx));

  retVal = (boolean)DCM_HSM_INFO(instIdx).msgContext.msgAddInfo.suppressPosResponse;

  DBG_DCM_HSMDCMSFSERVICECALLEDGUARD1_EXIT(retVal, DCM_INST(instIdx));
  return retVal;
}
FUNC(boolean, DCM_CODE) Dcm_HsmDcmSfServiceCalledGuard2(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* guard condition '!Dcm_SupressResponse() && Tx En'
   * for PROCESS_PAGE[...]/
   * external transition to state PgBufProcessing */

  boolean retVal = FALSE;
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

  /* Get the network channel */
  uint8 channelIndex;

  DBG_DCM_HSMDCMSFSERVICECALLEDGUARD2_ENTRY(DCM_INST(instIdx));

  channelIndex = Dcm_RxPduIdConfig[curHsmInfo->rxPduId].channelIdIndex;

  /* if transmission is enabled and positive/Nrc response is not suppressed */
  if ((TRUE == Dcm_TxEnabled[channelIndex]) &&
      /* Deviation MISRA-2 */
      (!Dcm_SuppressResponse(DCM_CUR_INST_ID(instIdx))))
  {
    retVal = TRUE;
  }

  DBG_DCM_HSMDCMSFSERVICECALLEDGUARD2_EXIT(retVal, DCM_INST(instIdx));

  return retVal;
}
FUNC(boolean, DCM_CODE) Dcm_HsmDcmSfServiceCalledGuard3(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* guard condition '!Dcm_SupressResponse() && Tx Dis'
   * for PROCESS_PAGE[...]/
   * external transition to state WaitForFullComProcess */

  boolean retVal = FALSE;
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

  /* Get the network channel */
  uint8 channelIndex;

  DBG_DCM_HSMDCMSFSERVICECALLEDGUARD3_ENTRY(DCM_INST(instIdx));

  channelIndex = Dcm_RxPduIdConfig[curHsmInfo->rxPduId].channelIdIndex;

  /* if transmission is disabled and positive/Nrc response is not suppressed */
  if ((FALSE == Dcm_TxEnabled[channelIndex]) &&
      /* Deviation MISRA-2 */
      (!Dcm_SuppressResponse(DCM_CUR_INST_ID(instIdx))))
  {
    retVal = TRUE;
  }

  DBG_DCM_HSMDCMSFSERVICECALLEDGUARD3_EXIT(retVal, DCM_INST(instIdx));

  return retVal;
}
FUNC(void, DCM_CODE) Dcm_HsmDcmSfServiceCalledAction4(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* action 'Free Rx Buffer; Free Tx Buffer; if (non-default session) StartTimer3(S3Timer);'
   * for PROC_ABORT[]/...
   * external transition to state OosNotified */

  /* Get SesTabConfig info */
  P2CONST(Dcm_SesTabConfigType, AUTOMATIC, DCM_CONST) sesTabConfig =
    &Dcm_SesTabConfig[DCM_CUR_INST_ID(instIdx)];

  /* get pointer to current message context */
  CONSTP2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext = &(DCM_HSM_INFO(instIdx).msgContext);

  DBG_DCM_HSMDCMSFSERVICECALLEDACTION4_ENTRY(DCM_INST(instIdx));

  /* Release rx and tx buffers */
  Dcm_ReleaseRxTxBuffers(DCM_INST(instIdx));

  /* ENTER critical section */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  if (pMsgContext->msgAddInfo.messageType == DCM_NORMAL)
  {
    /* Current Request processing is finished */
    DBG_DCM_REQPROCESSING((Dcm_ReqProcessing),(FALSE));
    Dcm_ReqProcessing = FALSE;
  }
  else if ((pMsgContext->msgAddInfo.messageType == DCM_ROE) || (pMsgContext->msgAddInfo.messageType == DCM_ROE_FINAL))
  {
    /* If currently stopping Request processing operation was ROE, unset ROE processing flag */
    DBG_DCM_ROEPROCESSING((Dcm_ROEProcessing),(DCM_ROE_NONE));
    Dcm_ROEProcessing = DCM_ROE_NONE;
  }
  /* CHECK: NOPARSE */
  else
  {
   /* Do nothing */
  }
  /* CHECK: PARSE */

  /* start S3 timer if a non-default session is active */
  if (sesTabConfig->SessionEntries[DCM_HSM_INFO(instIdx).sesTabIdx].SesCtrl != DCM_DEFAULT_SESSION)
  {
    Dcm_StartTimer3(DCM_PL_START_TIMER(instIdx, DCM_S3SERVER_TICK_DEFAULT));
  }

  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  DBG_DCM_HSMDCMSFSERVICECALLEDACTION4_EXIT(DCM_INST(instIdx));
}

FUNC(boolean, DCM_CODE) Dcm_HsmDcmSfServiceCalledGuard5(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* guard condition 'Dcm_SupressResponse()'
   * for PROC_DONE[...]/Free Rx Buffer; Free Tx Buffer;
   * external transition to state Finishing */
  boolean retVal = FALSE;

  DBG_DCM_HSMDCMSFSERVICECALLEDGUARD5_ENTRY(DCM_INST(instIdx));

  retVal = Dcm_SuppressResponse(DCM_CUR_INST_ID(instIdx));

  DBG_DCM_HSMDCMSFSERVICECALLEDGUARD5_EXIT(retVal, DCM_INST(instIdx));
  return retVal;
}
FUNC(void, DCM_CODE) Dcm_HsmDcmSfServiceCalledAction5(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* action 'Free Rx Buffer; Free Tx Buffer;'
   * for PROC_DONE[Dcm_SupressResponse()]/...
   * external transition to state Finishing */
  /* Release rx and tx buffers */

  DBG_DCM_HSMDCMSFSERVICECALLEDACTION5_ENTRY(DCM_INST(instIdx));

  Dcm_ReleaseRxTxBuffers(DCM_INST(instIdx));

  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* As processing is now finished, reset the flag for current processing in execution */
  DBG_DCM_REQPROCESSING((Dcm_ReqProcessing),(FALSE));
  Dcm_ReqProcessing = FALSE;

  /* If currently stopping Request processing operation was ROE, unset ROE processing flag */
  DBG_DCM_ROEPROCESSING((Dcm_ROEProcessing),(DCM_ROE_NONE));
  Dcm_ROEProcessing = DCM_ROE_NONE;

  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  DBG_DCM_HSMDCMSFSERVICECALLEDACTION5_EXIT(DCM_INST(instIdx));
}
FUNC(boolean, DCM_CODE) Dcm_HsmDcmSfServiceCalledGuard6(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* guard condition '!Dcm_SupressResponse() && Tx En'
   * for PROC_DONE[...]/
   * external transition to state Sending */
  boolean retVal = FALSE;
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

  /* Get the network channel */
  uint8 channelIndex;

  DBG_DCM_HSMDCMSFSERVICECALLEDGUARD6_ENTRY(DCM_INST(instIdx));

  channelIndex = Dcm_RxPduIdConfig[curHsmInfo->rxPduId].channelIdIndex;

  /* if transmission is enabled and positive/nrc response is not suppressed */
  if ((TRUE == Dcm_TxEnabled[channelIndex]) &&
      /* Deviation MISRA-2 */
      (!Dcm_SuppressResponse(DCM_CUR_INST_ID(instIdx))))
  {
    retVal = TRUE;
  }

  DBG_DCM_HSMDCMSFSERVICECALLEDGUARD6_EXIT(retVal, DCM_INST(instIdx));

  return retVal;
}
FUNC(boolean, DCM_CODE) Dcm_HsmDcmSfServiceCalledGuard7(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* guard condition '!Dcm_SupressResponse() && Tx Dis'
   * for PROC_DONE[...]/
   * external transition to state WaitForFullComProcess */
  boolean retVal = FALSE;
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);
  /* Get the network channel */
  uint8 channelIndex;

  DBG_DCM_HSMDCMSFSERVICECALLEDGUARD7_ENTRY(DCM_INST(instIdx));

  channelIndex = Dcm_RxPduIdConfig[curHsmInfo->rxPduId].channelIdIndex;

  /* if transmission is enabled and positive/nrc response is not suppressed */
  if ((FALSE == Dcm_TxEnabled[channelIndex]) &&
      /* Deviation MISRA-2 */
      (!Dcm_SuppressResponse(DCM_CUR_INST_ID(instIdx))))
  {
    retVal = TRUE;
  }

  DBG_DCM_HSMDCMSFSERVICECALLEDGUARD7_EXIT(retVal, DCM_INST(instIdx));

  return retVal;
}

/* ************************************************************************
 * State: SendRp
 * Parent state: ServiceCalled
 * Init substate: SendRpNormal
 * Transitions originating from this state:
 */

FUNC(void, DCM_CODE) Dcm_HsmDcmSfSendRpEntry(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* entry action '++RpCntr;SendNegResp(ResponsePending);spr=false;' */

  /* Get the network channel */
  uint8 channelIndex;
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);
  Std_ReturnType retVal = E_NOT_OK;
  /* pointer to buffer used for negative responses */
  P2VAR(uint8, AUTOMATIC, DCM_VAR) curNrBuffer = DCM_NR_BUFFER(instIdx).ptrBuffer;

  VAR(PduInfoType, DCM_VAR) Dcm_TxInformation;

  channelIndex = Dcm_RxPduIdConfig[curHsmInfo->rxPduId].channelIdIndex;

  DBG_DCM_HSMDCMSFSENDRPENTRY_ENTRY(DCM_INST(instIdx));

  /* ENTER critical section */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* Data is ready to send */
  DCM_TX_DATA_STATE(instIdx) = DCM_TX_DATA_READY;

  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* Reset supress positive response bit */
  curHsmInfo->msgContext.msgAddInfo.suppressPosResponse = FALSE;

  /* increment Response Pending timeout counter  */
  ++curHsmInfo->rpCntr;

  /* Set flag to indicate 'response pending' message transmission */
  curHsmInfo->responsePendingTxStatus = DCM_RP_PENDING_CONF;

  /* Fill buffer with error code 'response pending' and service Id */
  curNrBuffer[1] = curHsmInfo->serviceId;
  curNrBuffer[2] = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;

  /* get and setup PduIdInfo for transmission */
  curHsmInfo->curTxBuffer = &DCM_NR_BUFFER(instIdx);

  /* Update filledLen with response length */
  curHsmInfo->curTxBuffer->bufferInfo->filledLen = 3U;
  Dcm_TxInformation.SduLength = 3U;

  /* The length to be transmitted is memorized here as this is not a paged-buffer context */
  DCM_HSM_INFO(instIdx).sentLength = Dcm_TxInformation.SduLength;

  if (TRUE == Dcm_TxEnabled[channelIndex])
  {
    /* Trigger the transmission of diagnostic response by the PduR */
    retVal = PduR_DcmTransmit(DCM_HSM_INFO(instIdx).txPduId, &Dcm_TxInformation);
  }

  if ((FALSE == Dcm_TxEnabled[channelIndex]) || (retVal != E_OK))
  {
  /* if transmission failed, send signal DCM_TX_CONF_NOT_OK to current HSM
   * instance so that transmission is canceled, release rx and tx buffers */
    (void)DCM_HSMEMITTOSELFINST_WRAPPER(&Dcm_HsmScDcm, DCM_CUR_INST_ID(instIdx),
                                  DCM_HSM_DCM_EV_TX_CONF_NOT_OK);
    /* Release rx and tx buffers */
    Dcm_ReleaseRxTxBuffers(DCM_INST(instIdx));
  }


  DBG_DCM_HSMDCMSFSENDRPENTRY_EXIT(DCM_INST(instIdx));
}
FUNC(void, DCM_CODE) Dcm_HsmDcmSfSendRpExit(
   DCM_PDL_SF(const uint8 instIdx))
{
  /* exit action 'StartTimer2(P2StarTime);TxPduId.dataState=NO_TX_DATA;' */

  /* Get SesTabConfig info */
  P2CONST(Dcm_SesTabConfigType, AUTOMATIC, DCM_CONST) sesTabConfig =
                                          &Dcm_SesTabConfig[DCM_CUR_INST_ID(instIdx)];

  P2CONST(Dcm_SesTabEntryConfigType, AUTOMATIC, DCM_CONST) SessionTiming
    = &(sesTabConfig->SessionEntries[DCM_HSM_INFO(instIdx).sesTabIdx]);

  DBG_DCM_HSMDCMSFSENDRPEXIT_ENTRY(DCM_INST(instIdx));

  /* ENTER critical section */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* No Data to send */
  DCM_TX_DATA_STATE(instIdx) = DCM_NO_TX_DATA;

  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* Start timer P2StarServerMax */
  /* P2StarTime = P2StarMax of current session - Star Adjust time of current protocol*/
  if (SessionTiming->P2StarMaxTime > DCM_HSM_CONFIG(instIdx).P2StarServerAdjustTime)
  {
    Dcm_StartTimer2(DCM_PL_START_TIMER(instIdx,
    (SessionTiming->P2StarMaxTime - DCM_HSM_CONFIG(instIdx).P2StarServerAdjustTime)));
  }
  else
  {
  /* If the P2StarMaxTime is less than or equal to 'P2StarServerAdjustTime' then start
   * the timer with zero and this will emit the event TIMEOUT2 immediately. */
    Dcm_StartTimer2(DCM_PL_START_TIMER(instIdx, 0U));
  }


  DBG_DCM_HSMDCMSFSENDRPEXIT_EXIT(DCM_INST(instIdx));
}

/* ************************************************************************
 * State: SendRpForced
 * Parent state: SendRp
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) SendRpForced -> WaitForAppl: TX_CONF_OK[]/CallService(FORCE_RCRRP_OK);
 */

FUNC(void, DCM_CODE) Dcm_HsmDcmSfSendRpForcedAction1(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* action 'CallService(FORCE_RCRRP_OK);'
   * for TX_CONF_OK[]/...
   * external transition to state WaitForAppl */

  /* Call service handler, after application triggered response pending transmission */
#if (DCM_ASYNC_SERVICE_HANDLER == STD_ON)
  CONSTP2CONST(Dcm_SidTabConfigType, AUTOMATIC, DCM_CONST) curSidTabConfig
      = &Dcm_SidTabConfig[DCM_HSM_CONFIG(instIdx).sidTabId];

  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

  DBG_DCM_HSMDCMSFSENDRPFORCEDACTION1_ENTRY(DCM_INST(instIdx));

  if((curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).AsyncServiceExecution == TRUE)
  {
    /* if handling is asynchronous, signal the asynchronous service dispatcher that the next
     * invocation of the service handler function should be done with an OpStatus of
     *  DCM_FORCE_RCRRP_OK
     */

    /* ENTER critical section */
    SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
    curHsmInfo->asyncServiceOpState = DCM_FORCE_RCRRP_OK;

    /* LEAVE critical section */
    SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  }
  else
#else
  DBG_DCM_HSMDCMSFSENDRPFORCEDACTION1_ENTRY(DCM_INST(instIdx));
#endif /* #if(DCM_ASYNC_SERVICE_HANDLER == STD_ON) */
  {
    Dcm_DspInternal_SvcFunc(DCM_CUR_INST_ID(instIdx), DCM_FORCE_RCRRP_OK);
  }

  DBG_DCM_HSMDCMSFSENDRPFORCEDACTION1_EXIT(DCM_INST(instIdx));
}

/* ************************************************************************
 * State: SendRpNormal
 * Parent state: SendRp
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) SendRpNormal -> WaitForAppl: TX_CONF_OK[]/
 */


/* ************************************************************************
 * State: WaitForAppl
 * Parent state: ServiceCalled
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) WaitForAppl -> SendRpForced: FORCE_RCRRP[]/
 * 2) WaitForAppl -> SendingGr: TIMEOUT2[RpCntr >= Limit]/
 * 3) WaitForAppl -> SendRpNormal: TIMEOUT2[]/
 */

FUNC(boolean, DCM_CODE) Dcm_HsmDcmSfWaitForApplGuard2(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* guard condition 'RpCntr >= Limit'
   * for TIMEOUT2[...]/
   * external transition to state SendingGr */
  boolean retVal;

  DBG_DCM_HSMDCMSFWAITFORAPPLGUARD2_ENTRY(DCM_INST(instIdx));

  /* Depending on the configuration this function may always allow the
   * transition to SendingResponse if DCM_DIAG_RESP_MAX_NUM_RESP_PEND is
   * configured to be equal to 0.  This prevents the sending of any "response
   * pending" negative response and will lead to an "general reject" if the
   * diagnostic application does not respond within the P2 timeout. */
#if ((DCM_DIAG_RESP_MAX_NUM_RESP_PEND > 0U) && (DCM_DIAG_RESP_MAX_NUM_RESP_PEND <= 0xFEU))
    retVal = (DCM_HSM_INFO(instIdx).rpCntr >= DCM_DIAG_RESP_MAX_NUM_RESP_PEND);
  /* if DCM_DIAG_RESP_MAX_NUM_RESP_PEND = 0xFF, then NRC 0x10 response shall not be sent */
#elif (DCM_DIAG_RESP_MAX_NUM_RESP_PEND == DCM_UNLIMITED_0X78_NRC)
  retVal = FALSE; 
#else 
  retVal = TRUE; 
#endif /* #if (DCM_DIAG_RESP_MAX_NUM_RESP_PEND > 0U) */

/* Deviation MISRA-1 */
#if (!((DCM_DIAG_RESP_MAX_NUM_RESP_PEND > 0U) && (DCM_DIAG_RESP_MAX_NUM_RESP_PEND <= 0xFEU)) \
     && (DCM_HSM_INST_MULTI_ENABLED == STD_ON))
  TS_PARAM_UNUSED(instIdx); 
#endif /*#if(!((DCM_DIAG_RESP_MAX_NUM_RESP_PEND > 0U) && (DCM_DIAG_RESP_MAX_NUM_RESP_PEND <= 0xFEU)))*/

  DBG_DCM_HSMDCMSFWAITFORAPPLGUARD2_EXIT(retVal, DCM_INST(instIdx));

return retVal;
}

/* ************************************************************************
 * State: WaitForFullComProcess
 * Parent state: InService
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) RETRY_TX[]/if(TxDis)
 * 2) WaitForFullComProcess -> PgBufProcessing: PROCESS_PAGE[]/
 * 3) WaitForFullComProcess -> Sending: PROC_DONE[]/
 * 4) WaitForFullComProcess -> CancelProcessing: TIMEOUTTX[PageBufferInProgress()]/Free Rx Buffer; Free Tx Buffer;
 * 5) WaitForFullComProcess -> ConfirmingNOk: TIMEOUTTX[!PageBufferInProgress()]/Free Rx Buffer; Free Tx Buffer;
 */

FUNC(void, DCM_CODE) Dcm_HsmDcmSfWaitForFullComProcessEntry(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* entry action 'Start RetryTimerTxEn()StartTimerTx(timer2)StopTimer2()' */
  DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSENTRY_ENTRY(DCM_INST(instIdx));

  /* start retry timer for Tx Enabled state */
  DCM_HSM_INFO(instIdx).retryTimerTxEn = 1U;

  (void)Dcm_CheckTxEnbEmitEvt(DCM_CUR_INST_ID(instIdx));

  Dcm_StartTimerTx(DCM_PL_START_TIMER(instIdx, DCM_HSM_INFO(instIdx).timer2));

  Dcm_StopTimer2(DCM_PL_SF(instIdx));

  DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSENTRY_EXIT(DCM_INST(instIdx));
}
FUNC(void, DCM_CODE) Dcm_HsmDcmSfWaitForFullComProcessExit(
   DCM_PDL_SF(const uint8 instIdx))
{
  /* exit action 'Stop RetryTimerTxEn()' */
  DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSEXIT_ENTRY(DCM_INST(instIdx));

  /* stop retry timer for Tx Enabled state */
  DCM_HSM_INFO(instIdx).retryTimerTxEn = 0U;

  DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSEXIT_EXIT(DCM_INST(instIdx));
}
FUNC(void, DCM_CODE) Dcm_HsmDcmSfWaitForFullComProcessAction1(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* action 'if(TxDis)'
   * for RETRY_TX[]/...
   * internal transition */
  DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSACTION1_ENTRY(DCM_INST(instIdx));

  /* if Tx is disabled restart the retry timer so as to
     wait for Tx to be enabled */
  if (!Dcm_CheckTxEnbEmitEvt(DCM_CUR_INST_ID(instIdx)))
  {
    /* restart retry timer */
    DCM_HSM_INFO(instIdx).retryTimerTxEn = 1U;
  }

  DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSACTION1_EXIT(DCM_INST(instIdx));
}
FUNC(boolean, DCM_CODE) Dcm_HsmDcmSfWaitForFullComProcessGuard4(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* guard condition 'PageBufferInProgress()'
   * for TIMEOUTTX[...]/Free Rx Buffer; Free Tx Buffer;
   * external transition to state CancelProcessing */

  boolean retVal;
  
  DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSGUARD4_ENTRY(DCM_INST(instIdx));
  
  retVal = Dcm_PageBufferInProgress(DCM_CUR_INST_ID(instIdx));

  DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSGUARD4_EXIT(retVal, DCM_INST(instIdx));

  return retVal;
}
FUNC(void, DCM_CODE) Dcm_HsmDcmSfWaitForFullComProcessAction4(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* action 'Free Rx Buffer; Free Tx Buffer;'
   * for TIMEOUTTX[PageBufferInProgress()]/...
   * external transition to state CancelProcessing */

  DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSACTION4_ENTRY(DCM_INST(instIdx));

  Dcm_ReleaseRxTxBuffers(DCM_INST(instIdx));

  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* As processing is now finished, reset the flag for current processing in execution */
  DBG_DCM_REQPROCESSING((Dcm_ReqProcessing),(FALSE));
  Dcm_ReqProcessing = FALSE;

  /* If currently stopping Request processing operation was ROE, unset ROE processing flag */
  DBG_DCM_ROEPROCESSING((Dcm_ROEProcessing),(DCM_ROE_NONE));
  Dcm_ROEProcessing = DCM_ROE_NONE;

  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSACTION4_EXIT(DCM_INST(instIdx));
}
FUNC(boolean, DCM_CODE) Dcm_HsmDcmSfWaitForFullComProcessGuard5(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* guard condition '!PageBufferInProgress()'
   * for TIMEOUTTX[...]/Free Rx Buffer; Free Tx Buffer;
   * external transition to state ConfirmingNOk */

   boolean retVal;
  
  DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSGUARD5_ENTRY(DCM_INST(instIdx));
  
  retVal = !(Dcm_PageBufferInProgress(DCM_CUR_INST_ID(instIdx)));

  DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSGUARD5_EXIT(retVal, DCM_INST(instIdx));

  return retVal;
}
FUNC(void, DCM_CODE) Dcm_HsmDcmSfWaitForFullComProcessAction5(
  DCM_PDL_SF(const uint8 instIdx))
{
  /* action 'Free Rx Buffer; Free Tx Buffer;'
   * for TIMEOUTTX[!PageBufferInProgress()]/...
   * external transition to state ConfirmingNOk */

  DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSACTION5_ENTRY(DCM_INST(instIdx));

  Dcm_ReleaseRxTxBuffers(DCM_INST(instIdx));

  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* As processing is now finished, reset the flag for current processing in execution */
  DBG_DCM_REQPROCESSING((Dcm_ReqProcessing),(FALSE));
  Dcm_ReqProcessing = FALSE;

  /* If currently stopping Request processing operation was ROE, unset ROE processing flag */
  DBG_DCM_ROEPROCESSING((Dcm_ROEProcessing),(DCM_ROE_NONE));
  Dcm_ROEProcessing = DCM_ROE_NONE;

  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSACTION5_EXIT(DCM_INST(instIdx));
}

/*==================[internal function definitions]=========================*/

STATIC FUNC(boolean, DCM_CODE) Dcm_CheckBuf(
  const uint8               instIdx,
  const Dcm_BufferStateType bufferState)
{
  uint16_least DcmRxPduId; /* loop variable */
  Dcm_BufferStateType bufState = DCM_BUF_IDLE;
  boolean rxPduIdFound = FALSE;

  DBG_DCM_CHECKBUF_ENTRY(DCM_INST(instIdx),bufferState);

#if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF)
    TS_PARAM_UNUSED(instIdx);
#endif /* #if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF) */

  /* ENTER critical section */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* check for which of our RxPduIds there is a request available */
  for (DcmRxPduId = 0; DcmRxPduId < DCM_NUM_RX_PDU_ID; ++DcmRxPduId)
  {
    /* get configuration of current Rx Pdu Id */
    P2CONST(Dcm_RxPduIdConfigType, AUTOMATIC, DCM_CONST) curRxPduIdConfig  = &Dcm_RxPduIdConfig[DcmRxPduId];

    /* get configuration of current Rx buffer */
    P2CONST(Dcm_BufferConfigType, AUTOMATIC, DCM_CONST)  curRxBufferConfig = &Dcm_BufferConfig[curRxPduIdConfig->rxBufferId];

    bufState = curRxBufferConfig->bufferInfo->state;

    /* conditions to check:
     * - RxPduId is associated to this protocol instance
     * - RxPduId state must be idle to indicate that a reception was _finished_
     *   and is not going on
     * - buffer is actually filled with data of selected rxPduId
     * - buffer must be marked to hold received data or ROE data */
    if ((DCM_INST(instIdx) == curRxPduIdConfig->protocolId)
      && (DCM_RX_PDU_ID_IDLE == Dcm_RxPduIdState[DcmRxPduId])
      /* Deviation MISRA-1 */
      && (DcmRxPduId == curRxBufferConfig->bufferInfo->originatingRxPduId)
      /* Deviation MISRA-1 */
      && (bufState == bufferState))
    {
      /* found a buffer with RX or ROE data */
      rxPduIdFound = TRUE;
      break;
    }
  }

  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* outside of critical section */

  DBG_DCM_CHECKBUF_EXIT(rxPduIdFound, DCM_INST(instIdx), bufferState);
  return rxPduIdFound;
}

STATIC FUNC(void, DCM_CODE) Dcm_StartTimer2(DCM_PL_START_TIMER(const uint8 instIdx
                                            ,uint32 TimerVal))
{
  DBG_DCM_STARTTIMER2_ENTRY(DCM_INST(instIdx),TimerVal);

  /* if timer value is 0 */
  if (TimerVal == 0)
  {
    /* Emit the event TIMEOUT2 */
    (void)DCM_HSMEMITTOSELFINST_WRAPPER(&Dcm_HsmScDcm, DCM_CUR_INST_ID(instIdx)
                                        ,DCM_HSM_DCM_EV_TIMEOUT2);
  }
  else
  {
    /* ENTER critical section 
       Protect the setting of timer2 from preemption */
    SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

    /* load timer value */
    DCM_HSM_INFO(instIdx).timer2 = (uint32)TimerVal;

    /* LEAVE critical section */
    SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
  }

  DBG_DCM_STARTTIMER2_EXIT(DCM_INST(instIdx),TimerVal);
}

STATIC FUNC(void, DCM_CODE) Dcm_StartTimer3(
  DCM_PL_START_TIMER(const uint8 instIdx, uint16 TimerVal))
{
  DBG_DCM_STARTTIMER3_ENTRY(DCM_INST(instIdx),TimerVal);

  /* no protection required at this point; this function may only be called
   * from within critical section */

  /* load timer value */
  DCM_HSM_INFO(instIdx).timer3 = TimerVal;

  DBG_DCM_STARTTIMER3_EXIT(DCM_INST(instIdx),TimerVal);
}

STATIC FUNC(void, DCM_CODE) Dcm_StartTimerTx (DCM_PL_START_TIMER(const uint8 instIdx
                                                                 ,uint32 TimerVal))
{
  DBG_DCM_STARTTIMERTX_ENTRY(DCM_INST(instIdx),TimerVal);

  /* ENTER critical section 
     Protect the setting of timerTx from preemption */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* load timer value */
  DCM_HSM_INFO(instIdx).timerTx = (uint32)TimerVal;

  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  DBG_DCM_STARTTIMERTX_EXIT(DCM_INST(instIdx),TimerVal);
}

STATIC FUNC(void, DCM_CODE) Dcm_StopTimerTx(DCM_PDL_SF(const uint8 instIdx))
{
  DBG_DCM_STOPTIMERTX_ENTRY();

  /* ENTER critical section 
     Protect the setting of timerTx from preemption */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* Stop the timer Tx */
  DCM_HSM_INFO(instIdx).timerTx = 0U;

  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  DBG_DCM_STOPTIMERTX_EXIT();
}

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
STATIC FUNC(void, DCM_CODE) Dcm_StartTimerPgBuf (DCM_PL_START_TIMER(const uint8 instIdx
                                                                 ,uint32 TimerVal))
{
  DBG_DCM_STARTTIMERPGBUF_ENTRY(DCM_INST(instIdx),TimerVal);

  /* ENTER critical section 
     Protect the setting of timerPgBuf from preemption */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* load timer value */
  DCM_HSM_INFO(instIdx).timerPgBuf = (uint32)TimerVal;

  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  DBG_DCM_STARTTIMERPGBUF_EXIT(DCM_INST(instIdx),TimerVal);
}

STATIC FUNC(void, DCM_CODE) Dcm_StopTimerPgBuf(DCM_PDL_SF(const uint8 instIdx))
{
  DBG_DCM_STOPTIMERPGBUF_ENTRY();

  /* ENTER critical section 
     Protect the setting of timerPgBuf from preemption */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* Stop the timer Tx */
  DCM_HSM_INFO(instIdx).timerPgBuf = 0U;

  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  DBG_DCM_STOPTIMERPGBUF_EXIT();
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

STATIC FUNC(void, DCM_CODE) Dcm_StopTimer2(DCM_PDL_SF(const uint8 instIdx))
{
  DBG_DCM_STOPTIMER2_ENTRY();


  /* ENTER critical section 
     Protect the setting of timer2 from preemption */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* Stop the timer 2 */
  DCM_HSM_INFO(instIdx).timer2 = 0U;

  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();


  DBG_DCM_STOPTIMER2_EXIT();
}

/* Function to release Rx and Tx buffers */
FUNC(void, DCM_CODE) Dcm_ReleaseRxTxBuffers(const uint8 instIdx)
{
  P2VAR(Dcm_BufferInfoType, AUTOMATIC, DCM_VAR) curBufferInfo;

  DBG_DCM_RELEASERXTXBUFFERS_ENTRY(DCM_INST(instIdx));

#if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(instIdx);
#endif

  /* ENTER critical section */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* Release Tx Buffer */
  curBufferInfo = Dcm_BufferConfig[DCM_HSM_CONFIG(instIdx).txBufferId].bufferInfo;

  curBufferInfo->state = DCM_BUF_IDLE;
  /* reset filled buffer length */
  curBufferInfo->filledLen = 0;
  /* reset buffer data marking variables */
  curBufferInfo->confirmedDataMark = 0U;
  curBufferInfo->dataMark = 0U;

  /* Release NRC Tx Buffer */
  curBufferInfo = DCM_NR_BUFFER(instIdx).bufferInfo;
  curBufferInfo->state = DCM_BUF_IDLE;

  curBufferInfo->state = DCM_BUF_IDLE;
  /* reset filled buffer length */
  curBufferInfo->filledLen = 0;
  /* reset buffer data marking variables */
  curBufferInfo->confirmedDataMark = 0U;
  curBufferInfo->dataMark = 0U;

  /* Release Rx Buffer */
  curBufferInfo =
  Dcm_BufferConfig[Dcm_RxPduIdConfig[DCM_HSM_INFO(instIdx).rxPduId].rxBufferId].bufferInfo;

  curBufferInfo->state = DCM_BUF_IDLE;
  /* reset filled buffer length */
  curBufferInfo->filledLen = 0;
  /* reset buffer data marking variables */
  curBufferInfo->confirmedDataMark = 0U;
  curBufferInfo->dataMark = 0U;

  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  DBG_DCM_RELEASERXTXBUFFERS_EXIT(DCM_INST(instIdx));
}

STATIC FUNC(boolean, DCM_CODE) Dcm_SendRespPendInFirstCycle(DCM_PDL_SF(const uint8 instIdx))
{
  boolean retVal = FALSE;

  /* If DcmDspSessionP2ServerMax - DcmTimStrP2ServerAdjust configured is anywhere smaller
   * than the DcmTaskTime, then the RCRRP needs to be sent in the first execution cycle. */

  /* Get SesTabConfig info */
  P2CONST(Dcm_SesTabConfigType, AUTOMATIC, DCM_CONST) sesTabConfig =
                                      &Dcm_SesTabConfig[DCM_CUR_INST_ID(instIdx)];

  P2CONST(Dcm_SesTabEntryConfigType, AUTOMATIC, DCM_CONST) SessionTiming
    = &(sesTabConfig->SessionEntries[DCM_HSM_INFO(instIdx).sesTabIdx]);

  DBG_DCM_SENDRESPPENDINFIRSTCYCLE_ENTRY(DCM_INST(instIdx));

#if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(DCM_INST(instIdx));
#endif

  if ((SessionTiming->P2MaxTime <= DCM_HSM_CONFIG(instIdx).P2ServerAdjustTime) ||
      ((uint16)(SessionTiming->P2MaxTime - DCM_HSM_CONFIG(instIdx).P2ServerAdjustTime) <= 1U))
  {
    retVal = TRUE;
  }

  DBG_DCM_SENDRESPPENDINFIRSTCYCLE_EXIT(retVal, DCM_INST(instIdx));
  return retVal;
}

STATIC FUNC(void, DCM_CODE) RespPendInFirstCycle(DCM_PDL_SF(const uint8 instIdx))
{
  /* Get SesTabConfig info */
  P2CONST(Dcm_SesTabConfigType, AUTOMATIC, DCM_CONST) sesTabConfig =
                                          &Dcm_SesTabConfig[DCM_CUR_INST_ID(instIdx)];

  P2CONST(Dcm_SesTabEntryConfigType, AUTOMATIC, DCM_CONST) SessionTiming
    = &(sesTabConfig->SessionEntries[DCM_HSM_INFO(instIdx).sesTabIdx]);

  DBG_DCM_RESPPENDINFIRSTCYCLE_ENTRY(DCM_INST(instIdx));

  if (Dcm_SendRespPendInFirstCycle(DCM_PL_SF(instIdx)) == FALSE)
  {
    /* We do not need to send a RCRRP NRC in the first cycle, proceed as normal */
    /* Start timer P2ServerMax */
    /* P2Time = P2Max of current session - Adjust time of current protocol*/
    if (SessionTiming->P2MaxTime > DCM_HSM_CONFIG(instIdx).P2ServerAdjustTime)
    {
      Dcm_StartTimer2(DCM_PL_START_TIMER(instIdx,
            ((uint32)SessionTiming->P2MaxTime - DCM_HSM_CONFIG(instIdx).P2ServerAdjustTime)));
    }
  }
  else
  {
    /* Check if by any chance the indication interface does not allow the process to proceed */
    if (DCM_HSM_INFO(instIdx).requestValidationStatus == TRUE)
    {
      /* Emit the event TIMEOUT2 */
      (void)DCM_HSMEMITINST_WRAPPER(&Dcm_HsmScDcm, DCM_CUR_INST_ID(instIdx)
                                          ,DCM_HSM_DCM_EV_TIMEOUT2);
    }
  }

  DBG_DCM_RESPPENDINFIRSTCYCLE_EXIT(DCM_INST(instIdx));
}

STATIC FUNC(boolean, DCM_CODE) Dcm_CheckTxEnbEmitEvt(const uint8 instIdx)
{
  boolean retVal = FALSE;

  /* Get the network channel */
  uint8 channelIndex;
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);
  channelIndex = Dcm_RxPduIdConfig[curHsmInfo->rxPduId].channelIdIndex;

  DBG_DCM_CHECKTXENBEMITEVT_ENTRY(DCM_INST(instIdx));

#if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(instIdx);
#endif

  /* incase Tx is enabled, based on normal or paged processing, transition should be
     made to either PgBufProcessing or Sending(NormalProcessing) state */
  if (TRUE == Dcm_TxEnabled[channelIndex])
  {
    /* check whether paged or normal processing */
    if (curHsmInfo->processPageFuncId == DCM_PROCESS_PAGE_ID_INVALID)
    {
      (void)DCM_HSMEMITINST_WRAPPER(&Dcm_HsmScDcm, DCM_CUR_INST_ID(instIdx), DCM_HSM_DCM_EV_PROC_DONE);
    }
    else
    {
      (void)DCM_HSMEMITINST_WRAPPER(&Dcm_HsmScDcm, instIdx, DCM_HSM_DCM_EV_PROCESS_PAGE);
    }

    retVal = TRUE;
  }

  DBG_DCM_CHECKTXENBEMITEVT_EXIT(DCM_INST(instIdx));

  return retVal;
}

STATIC FUNC(boolean, DCM_CODE) Dcm_SuppressResponse(const uint8 instIdx)
{
  boolean retVal = FALSE;

  const Dcm_NegativeResponseCodeType nrc
    = DCM_HSM_INFO(instIdx).negativeResponseCode;

  DBG_DCM_SUPPRESSRESPONSE_ENTRY(DCM_INST(instIdx));

#if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(instIdx);
#endif
  /* if negative response needs to be sent */
  if (DCM_E_OK != nrc)
  {
    /* check for exception according to Dcm001 */
    if ((DCM_FUNCTIONAL_TYPE == DCM_HSM_INFO(instIdx).msgContext.msgAddInfo.reqType)
      && ((DCM_E_SERVICENOTSUPPORTED == nrc)
        || (DCM_E_SUBFUNCTIONNOTSUPPORTED == nrc)
    /* Deviation MISRA-1 */
        || (DCM_E_REQUESTOUTOFRANGE == nrc)))
    {
      /* reqType == functional and nrc either 0x11, 0x12, or 0x31, so that this nrc
         shall not be sent i.e suppressed */
      retVal = TRUE;
    }
    else
    {
     /* reqType == functional and nrc is other than 0x11, 0x12, or 0x31
        or reqType == physical, so that this nrc shall be sent and not suppressed */
     retVal = FALSE;
    }
  } /* as no nrc, check if positive response shall be suppressed */
  else if (TRUE == DCM_HSM_INFO(instIdx).msgContext.msgAddInfo.suppressPosResponse)
  {
    retVal = TRUE;
  }
  else
  {
    /* positive response shall not be suppressed */
    retVal = FALSE;
  }

  DBG_DCM_SUPPRESSRESPONSE_EXIT(DCM_INST(instIdx));

  return retVal;
}

STATIC FUNC(boolean, DCM_CODE) Dcm_PageBufferInProgress(const uint8 instIdx)
{
  boolean retVal = FALSE;
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);
  
  DBG_DCM_PAGEBUFFERINPROGRESS_ENTRY(DCM_INST(instIdx));

#if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(instIdx);
#endif
  /* check whether paged or normal processing */
    retVal = (!(curHsmInfo->processPageFuncId == DCM_PROCESS_PAGE_ID_INVALID));
   
  DBG_DCM_PAGEBUFFERINPROGRESS_EXIT(retVal, DCM_INST(instIdx));

  return retVal;
}

#define DCM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[end of file]===========================================*/
