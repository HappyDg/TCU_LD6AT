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

/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 15.2 (required)
 *     An unconditional break statement shall terminate every non-empty switch clause.
 *
 *     Reason:
 *     The break is removed. Because the following actions has to be done in the same state.
 *     So in order to avoid repeating the same code again, the break statement is removed.
 *     This will reduce the code size.
 *
 *  MISRA-2) Deviated Rule: 12.5 (required)
 *     The operands of a logical && or || shall be primary-expressions.
 *
 *     Reason:
 *     Misra has an exception that whenever an expression consists of either a sequence of only
 *     logical && or a sequence of only logical && or logical ||, extra parentheses are not required
 *
 *  MISRA-3) Deviated Rule: 13.7 (required)
 *     Boolean operations whose results are invariant shall not be permitted.
 *
 *     Reason:
 *     This is not a programming error. This approach has been deliberately
 *     selected to apply a common method to access data in all configuration possibilities.
 */

/*==================[inclusions]=================================================================*/

#include <Dcm_Trace.h>
#include <Std_Types.h>                                                 /* AUTOSAR standard types */
#include <TSAutosar.h>                                             /* EB specific standard types */

#include <Dcm.h>                                                      /* Declaration of Dcm APIs */
#if (DCM_INCLUDE_RTE == STD_ON)
#include <Rte_Dcm.h>                                                /* Dcm Mainfunction prototype*/
#endif
#include <Dcm_HsmDcm.h>                                   /* public statechart model definitions */
#include <Dcm_Int.h>                                    /* Module internal header dependent part */

#include <Dcm_DspExternal.h>                           /* Callbacks provided by Central Diag SwC */
/* do not indirectly include PduR_SymbolicNames_PBcfg.h via PduR_Dcm.h */
#define PDUR_NO_PBCFG_REQUIRED
#include <PduR_Dcm.h>                                                  /* PduR interface for Dcm */
#include <ComM_Dcm.h>                                                  /* ComM interface for Dcm */
#if (DCM_BSWM_API_ENABLED == STD_ON)
#include <BswM_DCM.h>                                                  /* BswM interface for Dcm */
#endif
#include <SchM_Dcm.h>

#if (DCM_DEV_ERROR_DETECT == STD_ON)
/* Development Error Tracer (DCM_DET_REPORT_ERROR() macros) */
#include <Det.h>
#endif /* DCM_DEV_ERROR_DETECT == STD_ON */

/*==================[macros]=====================================================================*/
/* !LINKSTO Dcm.Version.Check,2 */
/*------------------[AUTOSAR vendor identification check]-------------------*/

#if (!defined DCM_VENDOR_ID) /* configuration check */
#error DCM_VENDOR_ID must be defined
#endif

#if (DCM_VENDOR_ID != 1U) /* vendor check */
#error DCM_VENDOR_ID has wrong vendor id
#endif

/*------------------[AUTOSAR release version identification check]----------*/

#if (!defined DCM_AR_RELEASE_MAJOR_VERSION) /* configuration check */
#error DCM_AR_RELEASE_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (DCM_AR_RELEASE_MAJOR_VERSION != 4U)
#error DCM_AR_RELEASE_MAJOR_VERSION wrong (!= 4U)
#endif

#if (!defined DCM_AR_RELEASE_MINOR_VERSION) /* configuration check */
#error DCM_AR_RELEASE_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (DCM_AR_RELEASE_MINOR_VERSION != 0U )
#error DCM_AR_RELEASE_MINOR_VERSION wrong (!= 0U)
#endif

#if (!defined DCM_AR_RELEASE_REVISION_VERSION) /* configuration check */
#error DCM_AR_RELEASE_REVISION_VERSION must be defined
#endif

/* revision version check */
#if (DCM_AR_RELEASE_REVISION_VERSION != 3U )
#error DCM_AR_RELEASE_REVISION_VERSION wrong (!= 3U)
#endif

/*------------------[AUTOSAR module version identification check]-----------*/

#if (!defined DCM_SW_MAJOR_VERSION) /* configuration check */
#error DCM_SW_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (DCM_SW_MAJOR_VERSION != 4U)
#error DCM_SW_MAJOR_VERSION wrong (!= 4U)
#endif

#if (!defined DCM_SW_MINOR_VERSION) /* configuration check */
#error DCM_SW_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (DCM_SW_MINOR_VERSION < 4U)
#error DCM_SW_MINOR_VERSION wrong (< 4U)
#endif

#if (!defined DCM_SW_PATCH_VERSION) /* configuration check */
#error DCM_SW_PATCH_VERSION must be defined
#endif

/* patch version check */
#if (DCM_SW_PATCH_VERSION < 81U)
#error DCM_SW_PATCH_VERSION wrong (< 81U)
#endif

/*==================[type definitions]===========================================================*/

/*==================[external function declarations]=============================================*/

/*==================[internal function declarations]=============================================*/

#define DCM_START_SEC_CODE
#include <MemMap.h>

STATIC FUNC(void, DCM_CODE) Dcm_Internal_NormalProcessing(void);
STATIC FUNC(void, DCM_CODE) Dcm_Internal_ProcessTimers(DCM_PDL_SF(const uint8 instIdx));

#if (DCM_ROE_ENABLED == STD_ON)
STATIC FUNC(void, DCM_CODE)Dcm_Internal_ROEInitVariables(void);
STATIC FUNC(void, DCM_CODE) Dcm_Internal_ProcessRoeEventWindowTime(void);
STATIC FUNC(void, DCM_CODE) Dcm_RoeSendFinalResponse(uint8 subFunctionId);

#if (DCM_ROE_PERSISTENCE == STD_ON)
STATIC FUNC(void, DCM_CODE)Dcm_Internal_ROEPersistenceInit(void);
#endif

/* if internally managed DIDs are configured */
#if (DCM_INT_MANAGED_DIDS == STD_ON)
STATIC FUNC(void, DCM_CODE)Dcm_Internal_ROEOnChangeOfDidPolling(void);
STATIC FUNC(void, DCM_CODE) Dcm_Internal_ROEOnChangeOfDidTrigEvent(
  P2VAR(Dcm_ChangeInDIDContextType, AUTOMATIC, DCM_APPL_DATA) pChangeInDIDContext );
#endif /* #if (DCM_INT_MANAGED_DIDS == STD_ON) */

/* if any externally managed DIDs are configured */
#if ((DCM_EXT_MANAGED_DIDS == STD_ON) && (DCM_ROE_PRECONF_SUPPORT == STD_ON))
STATIC FUNC(void, DCM_CODE)Dcm_Internal_ROEOnChangeOfDidExternalEventActivate(void);
#endif /* #if ((DCM_EXT_MANAGED_DIDS == STD_ON) && (DCM_ROE_PRECONF_SUPPORT == STD_ON)) */

#endif /* #if (DCM_ROE_ENABLED == STD_ON) */

#define DCM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]=========================================================*/

/*==================[internal constants]=========================================================*/

/*==================[external data]==============================================================*/

#define DCM_START_SEC_VAR_INIT_8
#include <MemMap.h>

/** \brief Status of DCM initialization 
 *         TRUE:  The Dcm is initialized
 *         FALSE: The Dcm is not initialized
 */
VAR(boolean, DCM_VAR) Dcm_Initialized = FALSE;

/** \brief Inhibits jumping to the BL to avoid ProgConditions corruption
           (TRUE - jump to the BL not allowed, FALSE - jump to the BL allowed) */
VAR(boolean, DCM_VAR) Dcm_InhibitJmpToBL = FALSE;


/** \brief Flag for postponed activation of externally handled ROE events of DCM initialization 
 *         TRUE:  The Dcm shall call xxx_ActivateEvent in the next Dcm_MainFunction() cycle
 *         FALSE: The Dcm shall not call xxx_ActivateEvent in the next Dcm_MainFunction() cycle
 */
VAR(boolean, DCM_VAR) Dcm_ROEActivateEvent = FALSE;

/** \brief Status of Request Process
           TRUE:  Request ongoing
           FALSE: Request completed

 * Set to True until the Dcm is fully initialized, to block any Rx.
 */
VAR(boolean, DCM_VAR) Dcm_ReqProcessing = TRUE;

#define DCM_STOP_SEC_VAR_INIT_8
#include <MemMap.h>

#define DCM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief Global variable holding the value of RxPduId on which the request was received **/
VAR(PduIdType, DCM_VAR) Dcm_RxPduIdBL;

#if(DCM_ROE_ENABLED == STD_ON)
VAR(Dcm_RoeDataType, DCM_VAR) Dcm_RoeData;
VAR(uint8, DCM_VAR) Dcm_RoePollAsyncState;
#endif /* #if(DCM_ROE_ENABLED == STD_ON) */

#define DCM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>


#if(DCM_ROE_ENABLED == STD_ON)

#define DCM_START_SEC_VAR_NO_INIT_16
#include <MemMap.h>

/** \brief Global variable holding the value of DcmDspRoeInterMessageTime **/
VAR(uint16, DCM_VAR) Dcm_RoeInterMsgTime;

#define DCM_STOP_SEC_VAR_NO_INIT_16
#include <MemMap.h>

#define DCM_START_SEC_VAR_NO_INIT_32
#include <MemMap.h>

/** \brief Global variable holding the value of eventWindowTime **/
VAR(uint32, DCM_VAR) Dcm_RoeEventWindowTime[2];

#define DCM_STOP_SEC_VAR_NO_INIT_32
#include <MemMap.h>

#endif /* #if(DCM_ROE_ENABLED == STD_ON) */

#define DCM_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>

/* Rationale for mapping Dcm_CurProtocolId to NOINIT section.
 *
 * This variable is initialized in Dcm_Init before being accessed from the same function.
 */
VAR(uint8, DCM_VAR) Dcm_CurProtocolId;

/* Rationale for mapping Dcm_TxEnabled to NOINIT section.
 *
 * This array is initialized in Dcm_Init before being accessed from functions
 * Dcm_DslInternal_ResponseOnOneEvent, Dcm_HsmSfOutOfServiceGuard3 or
 * Dcm_HsmSfOutOfServiceGuard5.
 */
VAR(boolean, DCM_VAR) Dcm_TxEnabled[DCM_NUM_CHANNELID];

/* Rationale for mapping Dcm_RxEnabled to NOINIT section.
 *
 * This array is initialized in Dcm_Init before being accessed from Dcm_StartOfReception.
 */
VAR(boolean, DCM_VAR) Dcm_RxEnabled[DCM_NUM_CHANNELID];

#if (DCM_ROE_ENABLED == STD_ON)
#if (DCM_INT_MANAGED_DIDS == STD_ON)
/** \brief Variable to holds status of ROE internal DID comparision for first time */
VAR(boolean, DCM_VAR) Dcm_ROEInternalDidsComparision;
#endif
#if (DCM_ROE_PERSISTENCE == STD_ON)
/** \brief Variable to holds status of ROE persistence Read memory */
VAR(boolean, DCM_VAR) Dcm_ROEPersistenceReadCall;
#endif
#endif

/** \brief Variable holding states of Dcm Init after Jump from BL  **/
VAR(Dcm_BLInitStatusType, DCM_VAR) Dcm_BLInitStatus;

#define DCM_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>


#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/* Status of ROE Processing (DCM_ROE_NONE -  No processing in progress
 * DCM_ROE_QUEUED - Processing enqueued, DCM_ROE_PROCESSING - Processing in progress)
 */
VAR(Dcm_ROEProcessingType, DCM_VAR) Dcm_ROEProcessing = DCM_ROE_NONE;

/** Flag to enqueue ROE event */
VAR(Dcm_ROEEnqueueEventType, DCM_VAR) Dcm_ROEEnqueueEvent = DCM_ROE_NO_EVENT;

#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>


#define DCM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/* Rationale for mapping Dcm_CurHsmConfig to NOINIT section.
 *
 * This variable is initialized in Dcm_Init before being accessed from functions
 * Dcm_GetActiveProtocol and Dcm_HsmSfOutOfServiceEntry.
 */
P2CONST(Dcm_HsmConfigType, DCM_VAR, DCM_CONST) Dcm_CurHsmConfig;

/* Rationale for mapping Dcm_HsmInfo to NOINIT section.
 *
 * Members of Dcm_HsmInfo are are initialized and accessed as described below:
 * msgContext                   : Elements of structure msgContext.
 *                        reqData    : Initialized in Dcm_DsdInternal_DispatchSvcReq before
 *                                     being accessed from Dcm_DsdInternal_DispatchSvcReq().
 *                        reqDataLen : Initialized in Dcm_DsdInternal_DispatchSvcReq before
 *                                     being accessed from different service handlers.
 *                        resData    : Initialized in Dcm_DsdInternal_DispatchSvcReq before
 *                                     being accessed from different service handlers.
 *                        resDataLen : Initialized in Dcm_DsdInternal_DispatchSvcReq before
 *                                     being accessed from different service handlers.
 *                        msgAddInfo : Initialized in Dcm_DsdInternal_DispatchSvcReq() before
 *                                     being accessed from Dcm_HsmSfServiceCalledGuard4() and
 *                                     Dcm_HsmSfServiceCalledGuard1()
 *                        resMaxDataLen : Initialized in Dcm_DsdInternal_DispatchSvcReq before
 *                                        being accessed from different service handlers.
 *                        idContext  : Initialized in Dcm_DsdInternal_DispatchSvcReq() before
 *                                     being accessed from Dcm_Confirmation()
 *                        dcmRxPduId : Initialized in Dcm_DsdInternal_DispatchSvcReq() before
 *                                     being accessed from different service handlers
 * sentLength                   : Initialized in Dcm_DsdInternal_StartPagedProcessing() in
 *                                case it is used in a simulated paged-buffer transmission.
 *                                Initialized in Dcm_HsmDcmSfNormalProcessingEntry(),
 *                                Dcm_HsmDcmSfSendingGrEntry(),
 *                                Dcm_HsmDcmSfRealPgBufProcessingEntry() or
 *                                Dcm_HsmDcmSfSendRpEntry()  in case it is used in any other
 *                                transmission mode before being accessed from
 *                                Dcm_CopyTxData()
 * curTxBuffer                  : Initialized in Dcm_HsmDcmSfTopEntry before being
 *                                accessed from Dcm_CopyTxData().
 * timerTx                      : Initialized in Dcm_HsmDcmSfTopEntry before being
 *                                accessed from Dcm_Internal_ProcessTimers()
 * timerPgBuf                   : Initialized in Dcm_HsmDcmSfTopEntry before being
 *                                accessed from Dcm_Internal_ProcessTimers()
 * timer2                       : Initialized in Dcm_HsmDcmSfTopEntry before being
 *                                accessed from Dcm_Internal_ProcessTimers()
 * timer3                       : Initialized in Dcm_HsmDcmSfTopEntry before being
 *                                accessed from Dcm_Internal_ProcessTimers()
 * retryTimer                   : Initialized in Dcm_HsmDcmSfTopEntry before being
 *                                accessed from Dcm_Internal_ProcessTimers().
 * retryTimerTxEn               : Initialized in Dcm_HsmDcmSfWaitForFullComProcessEntry before
                                  being accessed from Dcm_Internal_ProcessTimers().
 * securityDelayCounter         : Initialized in Dcm_HsmDcmSfTopEntry before being
 *                                accessed from Dcm_Internal_ProcessTimers()
 * rxPduId                      : Initialized in Dcm_StartOfReception() or
 *                                Dcm_Internal_ProcessTimers() before being accessed
 *                                from Dcm_StartOfReception().
 * txPduId                      : Initialized in Dcm_StartOfReception() before being
 *                                accessed from Dcm_HsmDcmSfNormalProcessingEntry() or
 *                                Dcm_HsmDcmSfRealPgBufProcessingEntry() or
 *                                Dcm_HsmDcmSfSendRpEntry() or
 *                                Dcm_HsmDcmSfSendingGrEntry()
 * txConfirmationPduId          : Initialized in Dcm_StartOfReception before being
 *                                accessed from Dcm_CopyTxData()
 * sesTabIdx                    : Initialized in Dcm_HsmDcmSfTopEntry() before being accessed
 *                                from Dcm_HsmSfOutOfServiceEntry().
 * sesTabIdxNew                 : Initialized in Dcm_DspInternal_DiagnosticSessionControl_SvcH
 *                                before being accessed from Dcm_DspInternal_DcmConfirmation().
 * secTabIdx                    : Initialized in Dcm_HsmDcmSfTopEntry() before being accessed
 *                                from Dcm_DsdInternal_ValidateSvcReq().
 * reqSecTabIdx                 : Initialized in Dcm_DspInternal_SecurityAccessControl_SvcStart
 *                                before being accessed from
 *                                Dcm_DspInternal_SecurityAccessControl_SvcCont().
 * sidTabEntryInd               : Initialized in Dcm_DsdInternal_ValidateSvcReq before being
 *                                accessed from Dcm_DspInternal_SvcFunc().
 * s3Restart                    : Initialized in Dcm_StartOfReception before being
 *                                accessed from Dcm_TpRxIndication().
 * newSesCtrl                   : Initialized in Dcm_DsdInternal_DispatchSvcReq before being
 *                                accessed from Dcm_DspInternal_SetSessionState().
 * confirmedDiagSession         : Initialized in Dcm_HsmDcmSfTopEntry before being
 *                                accessed from Dcm_DspInternal_DiagnosticSessionControl_SvcH().
 * requestedSecLevel            : Initialized in Dcm_HsmDcmSfTopEntry() before being accessed
 *                                from Dcm_DspInternal_SecurityAccessControl_SvcH().
 * requestedResetMode           : Initialized in Dcm_HsmDcmSfTopEntry before being
 *                                accessed from Dcm_DspInternal_JumpToBL().
 * confirmedResetMode           : Initialized in Dcm_HsmDcmSfTopEntry before being
 *                                accessed from Dcm_DspInternal_JumpToBL().
 * requestedCommunicationMode   : Initialized in Dcm_HsmDcmSfTopEntry before being
 *                                accessed from Dcm_DspInternal_CommunicationControl_SvcH().
 * confirmedCommunicationMode   : Initialized in Dcm_HsmDcmSfTopEntry before being
 *                                accessed from Dcm_DspInternal_CommunicationControl_SvcH().
 * serviceId                    : Initialized in Dcm_HsmDcmSfInServiceEntry before being
 *                                accessed from Dcm_DsdInternal_DispatchSvcReq().
 * subServiceId                 : Initialized in Dcm_HsmDcmSfInServiceEntry before being
 *                                accessed from Dcm_DsdInternal_ValidateSubSvcReq().
 * subServiceIdIdx              : Initialized in Dcm_DspInternal_ReadDTCInformation_SvcStart or
 *                                Dcm_DspInternal_ResponseOnEvent_SvcStart before being used in
 *                                Dcm_DspInternal_ReadDTCInformation_SvcCont or
 *                                Dcm_DspInternal_ResponseOnEvent_SvcCont.
 * negativeResponseCode         : Initialized in Dcm_HsmSfInServiceEntry()before being accessed
 *                                from Dcm_DsdInternal_DispatchSvcReq().
 * processPageFuncId            : Initialized in Dcm_HsmSfInServiceEntry before being accessed
 *                                from Dcm_DspInternal_ReadDTCInformation_SvcH
 * rpCntr                       : Initialized in Dcm_HsmDcmSfServiceCalledEntry before being
 *                                accessed from Dcm_HsmDcmSfWaitForApplGuard2().
 * txDataState                  : Initialized in Dcm_HsmDcmSfInServiceEntry() before being
 *                                accessed from Dcm_CopyTxData().
 * responsePendingTxStatus      : Initialized in Dcm_HsmDcmSfTopEntry before being
 *                                accessed from Dcm_TpTxConfirmation().
 * exceededNumberOfAttempts     : Initialized in Dcm_HsmDcmSfTopEntry before being
 *                                accessed from Dcm_DspInternal_SecurityAccessControl_SvcH().
 * jumpToBLSupport              : Initialized in Dcm_HsmDcmSfTopEntry before being
 *                                accessed from Dcm_DspInternal_DiagnosticSessionControl_SvcH().
 * jumpToBLExecution            : Initialized in Dcm_HsmDcmSfTopEntry before being
 *                                accessed from Dcm_DspInternal_JumpToBL, 
                                  Dcm_DspInternal_ProcessSetProgConditions() and the 
                                  Dcm_TpTxConfirmation() API.
 * dspService                   : Initialized in Dcm_HsmDcmSfInServiceEntry before being
 *                                accessed from Dcm_DspInternal_SetSessionState().
 * dtcDisableStatus             : Initialized in Dcm_HsmDcmSfTopEntry before being
 *                                accessed from Dcm_DspInternal_SetSessionState().
 */
VAR(Dcm_HsmInfoType, DCM_VAR) Dcm_HsmInfo[DCM_NUM_PROTOCOL];

/* Rationale for mapping Dcm_RxPduIdState to NOINIT section.
 *
 * This variable is initialized in Dcm_Init() before being accessed
 * from Dcm_StartOfReception().
 */
VAR(Dcm_RxPduIdStateType, DCM_VAR) Dcm_RxPduIdState[DCM_NUM_RX_PDU_ID];

/* Rationale for mapping Dcm_BufferInfo to NOINIT section.
 *
 * Members of Dcm_BufferInfo are initialized and accessed as described below:
 * state                : Initialized in Dcm_Init()before being accessed
 *                        in Dcm_StartOfReception()
 * filledLen            : Initialized in Dcm_StartOfReception()or
 *                        Dcm_DslInternal_ResponseOnOneEvent or
 *                        Dcm_DsdInternal_DispatchSvcReq() depending upon the
 *                        buffer type(Rx/Tx).
 * originatingRxPduId   : Initialized in Dcm_StartOfReception or
 *                        Dcm_DslInternal_ResponseOnOneEvent.
 */
VAR(Dcm_BufferInfoType, DCM_VAR) Dcm_BufferInfo[DCM_NUM_BUFFER];
VAR(Dcm_BufferInfoType, DCM_VAR) Dcm_NRCBufferInfo[DCM_NUM_PROTOCOL];

/** \brief Allows the integrator to store relevant information prior to jumping to bootloader  */
VAR(Dcm_ProgConditionsType, DCM_VAR) ProgConditions;

#define DCM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[internal data]==========================================*/

/* if internally managed DIDs are configured and ROE is enabled */
#if ((DCM_INT_MANAGED_DIDS == STD_ON) && (DCM_ROE_ENABLED == STD_ON))

#define DCM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief Array to hold the context information for checking change in DID value. */
STATIC VAR(Dcm_ChangeInDIDContextType, DCM_VAR) Dcm_ChangeInDIDContext[DCM_NUM_PROTOCOL];

#define DCM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

#define DCM_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>

/** \brief Global array for holding the data read for a signal **/
VAR(uint8, DCM_VAR) Roe_DidSignalBuffer[DCM_DATA_MAX_SIZE];

#define DCM_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>
#endif /* #if ((DCM_INT_MANAGED_DIDS == STD_ON) && (DCM_ROE_ENABLED == STD_ON)) */

/*==================[external function definitions]==========================*/

#define DCM_START_SEC_CODE
#include <MemMap.h>

/* definition of Dcm_Init */
FUNC(void, DCM_CODE) Dcm_Init(
  P2CONST(Dcm_ConfigType, AUTOMATIC, DCM_APPL_CONST) ConfigPtr)
{
  Dcm_EcuStartModeType EcuStartModeType;
  uint16_least i;                           /* loop variable, which runs to 256 */
#if ((DCM_ROE_ENABLED == STD_ON) && (DCM_ROE_PERSISTENCE == STD_ON))
  Std_ReturnType RetVal = E_NOT_OK;
#endif /* ((DCM_ROE_ENABLED == STD_ON) && (DCM_ROE_PERSISTENCE == STD_ON)) */

  DBG_DCM_INIT_ENTRY(ConfigPtr);

  TS_PARAM_UNUSED(ConfigPtr);


  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* Set to True until the Dcm is fully initialized, to block any Rx. */
  DBG_DCM_REQPROCESSING((Dcm_ReqProcessing),(TRUE));
  Dcm_ReqProcessing = TRUE;

  /* No ROE currently executing */
  DBG_DCM_ROEPROCESSING((Dcm_ROEProcessing),(DCM_ROE_NONE));
  Dcm_ROEProcessing = DCM_ROE_NONE;

  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  /* Initialize the flag for cancelling Paged Buffer processing */
  Dcm_CancelPagedProcessing = FALSE;
#endif /* #if (DCM_PAGEDBUFFER_ENABLED == STD_ON) */
  /* Initialize array holding the status information for each buffer */
  for (i = 0U; i < DCM_NUM_BUFFER; ++i)
  {
    Dcm_BufferInfo[i].state = DCM_BUF_IDLE;
    Dcm_BufferInfo[i].dataMark = 0;
    Dcm_BufferInfo[i].confirmedDataMark = 0;
    Dcm_BufferInfo[i].filledLen = 0;
  }

  /* Initialize array holding the status information for each NRC buffer */
  for (i = 0U; i < DCM_NUM_PROTOCOL; ++i)
  {
    Dcm_NRCBufferInfo[i].state = DCM_BUF_IDLE;
    Dcm_NRCBufferInfo[i].dataMark = 0;
    Dcm_NRCBufferInfo[i].confirmedDataMark = 0;
    Dcm_NRCBufferInfo[i].filledLen = 0;
  }

  /* Initialize array holding the status information for each Rx Pdu Id **/
  for (i = 0U; i < DCM_NUM_RX_PDU_ID; ++i)
  {
    Dcm_RxPduIdState[i] = DCM_RX_PDU_ID_IDLE;
  }

  /* Disabling the diagnostic response transmission and reception. */
  for (i = 0U; i < DCM_NUM_CHANNELID; ++i)
  {
    Dcm_TxEnabled[i] = FALSE;

    Dcm_RxEnabled[i] = FALSE;
  }

/* If at least one routine is configured */
#if (DCM_NUM_ROUTINES > 0U)

  /* Initialize array holding the status information of each routines. */
  for (i = 0U; i < DCM_NUM_ROUTINES; ++i)
  {
    Dcm_DspRoutineStatus[i] = DCM_ROUTINE_INACTIVE;
  }
#endif /* #if (DCM_NUM_ROUTINES > 0U) */

#if(DCM_0X34_SVC_ENABLED == STD_ON) || \
   (DCM_0X35_SVC_ENABLED == STD_ON) || \
   (DCM_0X36_SVC_ENABLED == STD_ON) || \
   (DCM_0X37_SVC_ENABLED == STD_ON)
  for (i = 0U; i < DCM_NUM_PROTOCOL; ++i)
  {
    /* Initialize transfer state to IDLE for the transferservices. */
    Dcm_DataTransferContext[i].TransState = DCM_TRANSFER_IDLE;
  }
#endif

#if(DCM_0X87_SVC_ENABLED == STD_ON)
  /* Initialize LinkControl Request status. */
  Dcm_DspLinkControlRequestStatus = FALSE;
#endif

#if (DCM_ROE_ENABLED == STD_ON)
  /* Initialize ROE Global variables */
  Dcm_Internal_ROEInitVariables();

/* if internally managed DIDs are configured */
#if (DCM_INT_MANAGED_DIDS == STD_ON)
  for (i = 0U; i < DCM_NUM_PROTOCOL; ++i)
  {
    uint16_least j;
    P2VAR(Dcm_ChangeInDIDContextType, AUTOMATIC, DCM_VAR) pChangeInDIDContext =
      &Dcm_ChangeInDIDContext[i];

    /* Initialize the context information for checking change in DID data */
    pChangeInDIDContext->SignalInd = 0U;
    pChangeInDIDContext->DidReadSigConditionSt = DCM_DID_SIG_CONDITION_CALL;
    pChangeInDIDContext->DidNvmDataSt = DCM_DID_SIGNAL_CALL;

    for(j = 0U; j < DCM_ROE_DID_BUF_SIZE; j++)
    {
      pChangeInDIDContext->SavedDIDData[j] = 0U;
      pChangeInDIDContext->NewDIDData[j] = 0U;
      Dcm_ROEInternalDidsComparision = TRUE;
    }
  }
#endif /* #if (DCM_INT_MANAGED_DIDS == STD_ON)*/

#endif

/* initialize the signal buffer context for DIDs */
#if (DCM_DSP_USE_SERVICE_0X22 == STD_ON) || \
    (DCM_DSP_USE_SERVICE_0X2E == STD_ON) || \
    (DCM_DSP_USE_SERVICE_0X2F == STD_ON)

  Dcm_SignalBufferContext.BlockId = 0U;
  Dcm_SignalBufferContext.NvMService = DCM_DIDNVMOPERATION_NONE;

#endif /* #if (DCM_DSP_USE_SERVICE_0X22 == STD_ON) || \
              (DCM_DSP_USE_SERVICE_0X2E == STD_ON) || \
              (DCM_DSP_USE_SERVICE_0X2F == STD_ON) || */

  /* The default Protocol is the first configured protocol */
  DBG_DCM_CURPROTOCOLID((Dcm_CurProtocolId),(0U));
  Dcm_CurProtocolId = 0U;

  /* The default Protocol configuration */
  Dcm_CurHsmConfig = &(DCM_HSM_CONFIG(Dcm_CurProtocolId));

  /* Trigger initial transitions of all state machines */
  Dcm_HsmInit(&Dcm_HsmScDcm);


  DBG_DCM_BLINITSTATUS((Dcm_BLInitStatus),(DCM_NORMAL_PROC));
  Dcm_BLInitStatus = DCM_NORMAL_PROC;

#if (DCM_ROE_ENABLED == STD_ON)
#if (DCM_ROE_PERSISTENCE == STD_ON)
  RetVal = NvM_ReadBlock(DCM_ROE_NVM_BLOCK_ID, &Dcm_RoeData);

  if( RetVal == E_OK )
  {
    Dcm_ROEPersistenceReadCall = TRUE;
  }
  else
  {
    Dcm_Internal_ROEInitVariables();
#if ((DCM_EXT_MANAGED_DIDS == STD_ON) && (DCM_ROE_PRECONF_SUPPORT == STD_ON))
    Dcm_ROEActivateEvent = TRUE;
#endif /* ((DCM_EXT_MANAGED_DIDS == STD_ON) && (DCM_ROE_PRECONF_SUPPORT == STD_ON)) */ 

#if (DCM_DEV_ERROR_DETECT == STD_ON)
    if (RetVal == E_NOT_OK)
    {
    DCM_DET_REPORT_ERROR(DCM_SERVID_INIT, DCM_E_NVM_READ_FAIL);
    }
    else
    {
      DCM_DET_REPORT_ERROR(DCM_SVCID_NVMREADBLOCK, DCM_E_INTERFACE_RETURN_VALUE);
    }
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */

  }
#else /* #if (DCM_ROE_PERSISTENCE == STD_ON) */
#if ((DCM_EXT_MANAGED_DIDS == STD_ON) && (DCM_ROE_PRECONF_SUPPORT == STD_ON))
  Dcm_ROEActivateEvent = TRUE;
#endif /* #if ((DCM_EXT_MANAGED_DIDS == STD_ON) && (DCM_ROE_PRECONF_SUPPORT == STD_ON)) */ 
#endif /* #if (DCM_ROE_PERSISTENCE == STD_ON) */
#endif /* #if ((DCM_ROE_ENABLED == STD_ON) && (DCM_ROE_PERSISTENCE == STD_ON)) */

#if (DCM_DSP_USE_SERVICE_0X2F == STD_ON)
  Dcm_ReturnControlToEcuContext.returnCtrlToECUStatus = DCM_RET_CTRL_INACTIVE;
  Dcm_ReturnControlToEcuContext.returnToEcuSigInd = 0U;
  Dcm_ReturnControlToEcuContext.didIndex = 0U;
  Dcm_ReturnControlToEcuContext.timeoutCount = 0U;
#endif /* #if (DCM_DSP_USE_SERVICE_0X2F == STD_ON) */


  /* Call Dcm_GetProgConditions() to know if the initialization is the
     consequence of a jump from the bootloader */
  EcuStartModeType = Dcm_GetProgConditions(&ProgConditions);

  /* The ECU starts from a bootloader jump */
  if ( EcuStartModeType == DCM_WARM_START )
  {
    /* Get the 'RxPduId' corresponding to the 'TesterSourceAddr' */
    for (i = 0U; i < DCM_NUM_RX_PDU_ID; i++)
    {
      if (Dcm_RxPduIdConfig[i].TesterSourceAddr == ProgConditions.TesterSourceAddr)
      {
        break;
      }
    }
    /* If the 'TesterSourceAddr' is not configured, report error */
    if (i >= DCM_NUM_RX_PDU_ID)
    {
      ProgConditions.ResponseRequired = FALSE;

#if (DCM_DEV_ERROR_DETECT == STD_ON)
      DCM_DET_REPORT_ERROR(DCM_SVCID_GETPROGCONDITIONS, DCM_E_PARAM);
#endif

      SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

      /* Re-enable Rx, if the 'TesterSourceAddr' is not configured */
      DBG_DCM_REQPROCESSING((Dcm_ReqProcessing),(FALSE));
      Dcm_ReqProcessing = FALSE;

      SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
    }
    else
    {
      /* Set the RxPduId on which the request was received */
      Dcm_RxPduIdBL = (PduIdType)i;

      /* Emit event so that the Dcm shall call ComM_DCM_ActiveDiagnostic() to request the
                ComManager for full communication mode */
      (void) DCM_HSMEMITINST_WRAPPER( &Dcm_HsmScDcm, Dcm_RxPduIdConfig[Dcm_RxPduIdBL].protocolId,
        DCM_HSM_DCM_EV_RETURN_FROM_BL );

      /* Set the flag to indicate full communication mode confirmation is pending */

      DBG_DCM_BLINITSTATUS((Dcm_BLInitStatus),(DCM_COMM_MODE_CONF_PENDING));
      Dcm_BLInitStatus = DCM_COMM_MODE_CONF_PENDING;
    }
  }
  else
  {
#if (DCM_DEV_ERROR_DETECT == STD_ON)
    if (EcuStartModeType != DCM_COLD_START)
    {
      DCM_DET_REPORT_ERROR(DCM_SVCID_GETPROGCONDITIONS, DCM_E_INTERFACE_RETURN_VALUE);
    }
#endif

    SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

    /* Re-enable Rx, as the Dcm is now initialized and this is a "cold" start,
     * therefore no message needs to be sent */
    DBG_DCM_REQPROCESSING((Dcm_ReqProcessing),(FALSE));
    Dcm_ReqProcessing = FALSE;

    SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
  }

  Dcm_InhibitJmpToBL = FALSE;
  Dcm_Initialized = TRUE;

  DBG_DCM_INIT_EXIT(ConfigPtr);
}

#if (DCM_VERSION_INFO_API == STD_ON)
FUNC(void, DCM_CODE) Dcm_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, DCM_APPL_DATA) versioninfo)
{
  DBG_DCM_GETVERSIONINFO_ENTRY(versioninfo);

#if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (versioninfo == NULL_PTR)
  {
    DCM_DET_REPORT_ERROR(DCM_SERVID_GETVERSIONINFO, DCM_E_PARAM_POINTER);
  }
  else
#endif /* DCM_DEV_ERROR_DETECT == STD_ON */
  {
    /* get version info of this module */
    versioninfo->vendorID         = DCM_VENDOR_ID;
    versioninfo->moduleID         = DCM_MODULE_ID;
    versioninfo->sw_major_version = DCM_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = DCM_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = DCM_SW_PATCH_VERSION;
  }

  DBG_DCM_GETVERSIONINFO_EXIT(versioninfo);
}
#endif /* DCM_VERSION_INFO_API */

FUNC(Std_ReturnType, DCM_CODE) Dcm_GetSecurityLevel(
  P2VAR(Dcm_SecLevelType, AUTOMATIC, DCM_APPL_DATA) SecLevel)
{
  Std_ReturnType retVal = E_NOT_OK;

  DBG_DCM_GETSECURITYLEVEL_ENTRY(SecLevel);

#if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (Dcm_Initialized != TRUE)
  {
    DCM_DET_REPORT_ERROR(DCM_SERVID_GETSECURITYLEVEL, DCM_E_UNINIT);
  }
  else if (SecLevel == NULL_PTR)
  {
    DCM_DET_REPORT_ERROR(DCM_SERVID_GETSECURITYLEVEL, DCM_E_PARAM_POINTER);
  }
  else
#endif /* DCM_DEV_ERROR_DETECT */
  {
    /* Get current security table id */
    uint8 secTabIdx = DCM_HSM_INFO(Dcm_CurProtocolId).secTabIdx;
    /* Check if security table id is invalid */
    if (secTabIdx != DCM_SEC_TAB_ENTRY_IDX_LOCKED)
    {
      /* Get current security level */
      *SecLevel = Dcm_SecTabConfig.Entries[secTabIdx].SecLevel;
    }
    else
    {
      /* Locked state since current security table id is invalid */
      *SecLevel = DCM_SEC_LEV_LOCKED;
    }
    retVal = E_OK;
  }

  DBG_DCM_GETSECURITYLEVEL_EXIT(retVal,SecLevel);
  return retVal;
}

FUNC(Std_ReturnType, DCM_CODE) Dcm_GetSesCtrlType(
  P2VAR(Dcm_SesCtrlType, AUTOMATIC, DCM_APPL_DATA) SesCtrlType)
{
  Std_ReturnType retVal = E_NOT_OK;
  P2CONST(Dcm_SesTabConfigType, AUTOMATIC, DCM_CONST) sesTabConfig;

  DBG_DCM_GETSESCTRLTYPE_ENTRY(SesCtrlType);

#if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (Dcm_Initialized != TRUE)
  {
    DCM_DET_REPORT_ERROR(DCM_SERVID_GETSESCTRLTYPE, DCM_E_UNINIT);
  }
  else if (SesCtrlType == NULL_PTR)
  {
    DCM_DET_REPORT_ERROR(DCM_SERVID_GETSESCTRLTYPE, DCM_E_PARAM_POINTER);
  }
  else
#endif /* DCM_DEV_ERROR_DETECT */
  {
    /* ENTER critical section.
       Protect the multiple reads of Dcm_CurProtocolId from preemption */
    SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

    /* Get SesTabConfig info */
    sesTabConfig = &DCM_SES_TAB_CONFIG(Dcm_CurProtocolId);
    retVal = E_OK;
    *SesCtrlType = sesTabConfig->SessionEntries[DCM_HSM_INFO(Dcm_CurProtocolId).sesTabIdx].SesCtrl;

    /* LEAVE critical section */
    SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
  }

  DBG_DCM_GETSESCTRLTYPE_EXIT(retVal,SesCtrlType);
  return retVal;
}

FUNC(Std_ReturnType, DCM_CODE) Dcm_GetActiveProtocol(
  P2VAR(Dcm_ProtocolType, AUTOMATIC, DCM_APPL_DATA) ActiveProtocol)
{
  Std_ReturnType retVal = E_NOT_OK;

  DBG_DCM_GETACTIVEPROTOCOL_ENTRY(ActiveProtocol);

#if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (Dcm_Initialized != TRUE)
  {
    DCM_DET_REPORT_ERROR(DCM_SERVID_GETACTIVEPROTOCOL, DCM_E_UNINIT);
  }
  else if (ActiveProtocol == NULL_PTR)
  {
    DCM_DET_REPORT_ERROR(DCM_SERVID_GETACTIVEPROTOCOL, DCM_E_PARAM_POINTER);
  }
  else
#endif /* DCM_DEV_ERROR_DETECT == STD_ON */
  {
    /* ENTER critical section */
    SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

    *ActiveProtocol = Dcm_CurHsmConfig->protocolType;

    /* LEAVE critical section */
    SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

    retVal = E_OK;
  }

  DBG_DCM_GETACTIVEPROTOCOL_EXIT(retVal,ActiveProtocol);
  return retVal;
}

FUNC(Std_ReturnType, DCM_CODE) Dcm_ResetToDefaultSession(void)
{
  Std_ReturnType retVal = E_NOT_OK;

  DBG_DCM_RESETTODEFAULTSESSION_ENTRY();

#if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (Dcm_Initialized != TRUE)
  {
    DCM_DET_REPORT_ERROR(DCM_SERVID_RESETTODEFAULTSESSION, DCM_E_UNINIT);
  }
  else
#endif /* DCM_DEV_ERROR_DETECT == STD_ON */
  {
    /* Emit the event RST2DFLTSESS. It will be deferred from execution until
       the HSM reaches a state (OutOfService) where it is safe to execute */
    (void)DCM_HSMEMITINST_WRAPPER(&Dcm_HsmScDcm
                                  ,DCM_CUR_INST_ID(Dcm_CurProtocolId)
                                  ,DCM_HSM_DCM_EV_RST2DFLTSESS
                                  );
    retVal = E_OK;
  }

  DBG_DCM_RESETTODEFAULTSESSION_EXIT(retVal);
  return retVal;
}

FUNC(Std_ReturnType, DCM_CODE)  Dcm_TriggerOnEvent(
  uint8 RoeEventId)
{
  Std_ReturnType apiRetVal = E_NOT_OK;
#if (DCM_ROE_ENABLED == STD_ON)
  Dcm_StatusType retVal = DCM_E_ROE_NOT_ACCEPTED;
  uint8_least i;
#endif
  DBG_DCM_TRIGGERONEVENT_ENTRY(RoeEventId);
  /* Dcm521 */
#if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (Dcm_Initialized != TRUE)
  {
    DCM_DET_REPORT_ERROR(DCM_SERVID_TRIGGERONEVENT, DCM_E_UNINIT);
    apiRetVal = E_NOT_OK;
  }
  else if(RoeEventId == 0xFFU)
  {
    DCM_DET_REPORT_ERROR(DCM_SERVID_TRIGGERONEVENT, DCM_E_PARAM);
    apiRetVal = E_NOT_OK;
  }
  else
  {
#endif
#if (DCM_ROE_ENABLED == STD_ON)
    /* Check if RoeEventId is Configured*/
    for (i = 0U; i < DCM_NUM_DID ; ++i)
    {
      if (RoeEventId == Dcm_DidTable[i].RoeEventId)
      {
        break;
      }
    }
    if ((i < DCM_NUM_DID) && (Dcm_DidTable[i].ExtRoeSupport == TRUE))
    {
      apiRetVal = E_OK;
      if( Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] == DCM_ROE_EVENT_STARTED )
      {
        /* Trigger OnChangeOfDataIdentifier event transmission for external event */
        retVal = Dcm_DslInternal_ResponseOnOneEvent(
                            &Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_SERVICETORESPOND0_0x03_IDX],
                            3U,
                            Dcm_RoeData.DcmRxPduId);
        if(retVal == DCM_E_OK)
        {
          /* increment the number of identified events */
          Dcm_RoeData.NoOfIdentifiedEvents[DCM_ROE_SUBFUNCTION_0x03_IDX]++;
          apiRetVal = E_OK;
        }
        else
        {
          apiRetVal = E_NOT_OK;
        }
      }
    }
#else
  TS_PARAM_UNUSED(RoeEventId);
#endif /* (DCM_ROE_ENABLED == STD_ON) */
#if (DCM_DEV_ERROR_DETECT == STD_ON)
 }
#endif

  DBG_DCM_TRIGGERONEVENT_EXIT(apiRetVal,RoeEventId);
  return apiRetVal;
}

#if (DCM_ROE_ENABLED == STD_ON)
STATIC FUNC(void, DCM_CODE) Dcm_RoeSendFinalResponse(uint8 subFunctionId)
{
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  uint8 protocolId = Dcm_RxPduIdConfig[Dcm_RoeData.DcmRxPduId].protocolId;
#endif
  /* get configuration of current transmission(Tx) buffer */
  P2CONST(Dcm_BufferConfigType, AUTOMATIC, DCM_CONST) curTxBufferConfig =
    &Dcm_BufferConfig[DCM_HSM_CONFIG(protocolId).txBufferId];

  /* get the context information current instance */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo =
    &(DCM_HSM_INFO(protocolId));

  /* get pointer to current message context */
  CONSTP2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) curMsgContext = &curHsmInfo->msgContext;
    
  /* allocate buffer */
  curTxBufferConfig->bufferInfo->state = DCM_BUF_ROE;
  curMsgContext->msgAddInfo.messageType = DCM_ROE_FINAL;

  /* Set the final ROE response type */
  switch (subFunctionId)
  {
    case DCM_ROE_SUBFUNCTION_0x01_IDX:
      Dcm_RoeData.FinalRoeResponse[subFunctionId] = DCM_ROE_ONDTC_STATUS_CHANGE;
      break;
    case DCM_ROE_SUBFUNCTION_0x03_IDX:
      Dcm_RoeData.FinalRoeResponse[subFunctionId] = DCM_ROE_ONCHANGE_OF_DATA_IDENTIFIER;
      break;
    /* CHECK: NOPARSE */
    default:
        /* Defensive branch. Unexpected subFunctionId value  */
        DCM_UNREACHABLE_CODE_ASSERT(DCM_SERVID_MAINFUNCTION);
      break;
    /* CHECK: PARSE */
  }

  /* enqueue final ROE response event */
  (void)DCM_HSMEMITINST_WRAPPER(&Dcm_HsmScDcm, protocolId, DCM_HSM_DCM_EV_ROE_FINAL_RES);
  Dcm_RoeEventWindowTime[subFunctionId] = 0U;

  DBG_DCM_ROEPROCESSING((Dcm_ROEProcessing),(DCM_ROE_PROCESSING));
  Dcm_ROEProcessing = DCM_ROE_PROCESSING;
  
  DBG_DCM_ROEENQUEUEEVENT((Dcm_ROEEnqueueEvent), (DCM_ROE_NO_EVENT))
  Dcm_ROEEnqueueEvent = DCM_ROE_NO_EVENT;

}
#endif /* (DCM_ROE_ENABLED == STD_ON) */


FUNC(void, DCM_CODE) Dcm_MainFunction(void)
{
  Std_ReturnType SetProgConditionsReturn = E_OK;
  boolean FullCommEnabled = FALSE;
  
  DBG_DCM_MAINFUNCTION_ENTRY();

  if ( Dcm_Initialized == TRUE )
  {
    switch ( Dcm_BLInitStatus )
    {
      case DCM_COMM_MODE_CONF_PENDING:

        /* ENTER critical section 
           The paired reading of Dcm_TxEnabled and Dcm_RxEnabled must be protected from preemption */
        SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

        /* Check if Full-Communication is enabled on the corresponding 'channelIdIndex' */
        if ((Dcm_TxEnabled[Dcm_RxPduIdConfig[Dcm_RxPduIdBL].channelIdIndex] == TRUE) &&
            (Dcm_RxEnabled[Dcm_RxPduIdConfig[Dcm_RxPduIdBL].channelIdIndex] == TRUE))
        {
          FullCommEnabled = TRUE;
        }

        /* LEAVE critical section */
        SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();


        if (FullCommEnabled == TRUE)
        {
          (void)DCM_HSMEMITINST_WRAPPER(&Dcm_HsmScDcm, Dcm_RxPduIdConfig[Dcm_RxPduIdBL].protocolId,
            DCM_HSM_DCM_EV_BL_TX_RESPONSE);

          DBG_DCM_BLINITSTATUS((Dcm_BLInitStatus),(DCM_TX_CONF_PENDING));
          Dcm_BLInitStatus = DCM_TX_CONF_PENDING;
        }


        break;

      case DCM_TX_CONF_PENDING:
        break;

        /* Deviation MISRA-1 */
      case DCM_RES_TX_CONF_OK:

        /* Check if 'ApplUpdated' or 'ResponseRequired' flag is set, so as to reset them */
        if ((ProgConditions.ResponseRequired == TRUE) || (ProgConditions.ApplUpdated == TRUE))
        {
          ProgConditions.ResponseRequired = FALSE;
          ProgConditions.ApplUpdated = FALSE;

          /* Call Dcm_SetProgConditions() to clear the flags:
             Fall through to the next state so that further processing
             is carried out in the same cycle */

          DBG_DCM_BLINITSTATUS((Dcm_BLInitStatus),(DCM_SET_PROGCONDITIONS_PENDING));
          Dcm_BLInitStatus = DCM_SET_PROGCONDITIONS_PENDING;
        }
        else
        {
          /* Session status updated; Enable and execute normal processing */

          DBG_DCM_BLINITSTATUS((Dcm_BLInitStatus),(DCM_NORMAL_PROC));
          Dcm_BLInitStatus = DCM_NORMAL_PROC;
          Dcm_Internal_NormalProcessing();

          break;
        }

      /* Deviation MISRA-1 */
      case DCM_SET_PROGCONDITIONS_PENDING:

        /* Disallow new jump to bootloader until Dcm_SetProgConditions() finishes.
           This is to avoid corrupting the ProgConditions by a reentrant call to
           Dcm_SetProgConditions */
        Dcm_InhibitJmpToBL = TRUE;

        /* Call Dcm_SetProgConditions() to clear the flags */
        SetProgConditionsReturn = Dcm_SetProgConditions(&ProgConditions);

        if (SetProgConditionsReturn == DCM_E_OK)
        {
          /* Jump to the bootloader allowed again. */
          Dcm_InhibitJmpToBL = FALSE;

          /* Dcm_SetProgConditions() is successfull, Enable normal processing;
             Fall through to the next state so that Normal processing
             is started in the same cycle */

          DBG_DCM_BLINITSTATUS((Dcm_BLInitStatus),(DCM_NORMAL_PROC));
          Dcm_BLInitStatus = DCM_NORMAL_PROC;
        }
        else if (SetProgConditionsReturn == DCM_E_PENDING)
        {
          /* do nothing, just perform the call in the next cycle again */
        }
        else
        {
          /* Jump to the bootloader allowed again. */
          Dcm_InhibitJmpToBL = FALSE;

          /* error condition, the setting of the flags has most probably failed,
             the only thing which can be done at this point is to continue with
             normal functions and report a relevant error. */

          DBG_DCM_BLINITSTATUS((Dcm_BLInitStatus),(DCM_NORMAL_PROC));
          Dcm_BLInitStatus = DCM_NORMAL_PROC;
#if (DCM_DEV_ERROR_DETECT == STD_ON)
          if (SetProgConditionsReturn == DCM_E_NOT_OK)
          {
            DCM_DET_REPORT_ERROR(DCM_SVCID_SETPROGCONDITIONS, DCM_E_SET_PROG_CONDITIONS_FAIL);
          }
          else
          {
            DCM_DET_REPORT_ERROR(DCM_SVCID_SETPROGCONDITIONS, DCM_E_INTERFACE_RETURN_VALUE);
          }
#endif
        }

        /* Start normal message processing */
        Dcm_Internal_NormalProcessing();

        break;

      case DCM_NORMAL_PROC:
        /* Start normal message processing */
        Dcm_Internal_NormalProcessing();
        break;

      /* CHECK: NOPARSE */
      default:
        /* Defensive branch. Default case at the end of the switch statement */
        DCM_UNREACHABLE_CODE_ASSERT(DCM_SERVID_MAINFUNCTION);
        break;
      /* CHECK: PARSE */
    }
#if (DCM_ROE_ENABLED == STD_ON)
    if (Dcm_ReqProcessing == FALSE)
    {
      /* If a ROE event is waiting for execution enqueue it */
      if (Dcm_ROEEnqueueEvent == DCM_ROE_NORMAL_EVENT)
      {
        (void)DCM_HSMEMITINST_WRAPPER(
          &Dcm_HsmScDcm, Dcm_RxPduIdConfig[Dcm_RoeData.DcmRxPduId].protocolId, DCM_HSM_DCM_EV_ROE);
        DBG_DCM_ROEENQUEUEEVENT((Dcm_ROEEnqueueEvent), (DCM_ROE_NO_EVENT))
        Dcm_ROEEnqueueEvent = DCM_ROE_NO_EVENT;
      } 
      else if (Dcm_ROEEnqueueEvent == DCM_ROE_FINAL_RESPONSE_01)
      {
        Dcm_RoeSendFinalResponse(DCM_ROE_SUBFUNCTION_0x01_IDX);
      }
      else if (Dcm_ROEEnqueueEvent == DCM_ROE_FINAL_RESPONSE_03)
      {
        Dcm_RoeSendFinalResponse(DCM_ROE_SUBFUNCTION_0x03_IDX);
      }
      else
      {
        /* no event is enqueued here, nothing to actually do... */
      }
    }
#endif /* DCM_ROE_ENABLED == STD_ON) */
    /* Main processing function of HSM for multiple state charts */
    Dcm_HsmMain(&Dcm_HsmScDcm);
  }

  DBG_DCM_MAINFUNCTION_EXIT();
}

/* Dcm614 */
FUNC(Std_ReturnType, DCM_CODE)  Dcm_DemTriggerOnDTCStatus(
  uint32 DTC,
  uint8 DTCStatusOld,
  uint8 DTCStatusNew)
{
  Std_ReturnType retVal = E_NOT_OK;

  DBG_DCM_DEMTRIGGERONDTCSTATUS_ENTRY(DTC,DTCStatusOld,DTCStatusNew);
  TS_PARAM_UNUSED(DTC);

#if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (Dcm_Initialized != TRUE)
  {
    DCM_DET_REPORT_ERROR(DCM_SERVID_DEMTRIGGERONDTC, DCM_E_UNINIT);
  }
  else
#endif
  {
#if (DCM_ROE_ENABLED == STD_ON)
    uint8 maskDTCStatusOld;
    uint8 maskDTCStatusNew;
  /* Check if EventLogic for onDTCStatusChange is set */
  if( Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x01_IDX] == DCM_ROE_EVENT_STARTED )
  {
    /* Dcm603 partially */
    if( DTCStatusNew != 0U )
    {
      maskDTCStatusOld = (uint8)(DTCStatusOld &
                              Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_EVENTTYPERECORD0_0x01_IDX]);
      maskDTCStatusNew = (uint8)(DTCStatusNew &
                              Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_EVENTTYPERECORD0_0x01_IDX]);
      if( maskDTCStatusOld != maskDTCStatusNew )
      {
        /* Dcm128, Dcm602: Trigger event transmission */
        (void)Dcm_DslInternal_ResponseOnOneEvent(
                            &Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_SERVICETORESPOND0_0x01_IDX],
                            3U,
                            Dcm_RoeData.DcmRxPduId);
        /* increment the number of identified events */
        Dcm_RoeData.NoOfIdentifiedEvents[DCM_ROE_SUBFUNCTION_0x01_IDX]++;
      }
    }
  }
  retVal = E_OK;
#else
  TS_PARAM_UNUSED(DTCStatusOld);
  TS_PARAM_UNUSED(DTCStatusNew);
#endif /* (DCM_ROE_ENABLED == STD_ON) */
}

  DBG_DCM_DEMTRIGGERONDTCSTATUS_EXIT(retVal,DTC,DTCStatusOld,DTCStatusNew);
  return retVal;
}
#if ((DCM_MODEDECLARATION_SUPPORT == STD_OFF) && (DCM_BSWM_API_ENABLED == STD_ON))
FUNC(Std_ReturnType, DCM_CODE) Dcm_HardResetModeEntry(void)
{
  /* get Hsm information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(Dcm_CurProtocolId);

  DBG_DCM_HARDRESETMODEENTRY_ENTRY();

  /* Update the confirmed Reset Mode */
  curHsmInfo->confirmedResetMode = DCM_HARD_RESET;


  DBG_DCM_HARDRESETMODEENTRY_EXIT(E_OK);
  return E_OK;
}

FUNC(Std_ReturnType, DCM_CODE) Dcm_KeyOnOffResetModeEntry(void)
{
  /* get Hsm information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(Dcm_CurProtocolId);

  DBG_DCM_KEYONOFFRESETMODEENTRY_ENTRY();

  /* Update the confirmed Reset Mode */
  curHsmInfo->confirmedResetMode = DCM_KEY_ON_OFF_RESET;


  DBG_DCM_KEYONOFFRESETMODEENTRY_EXIT(E_OK);
  return E_OK;
}

FUNC(Std_ReturnType, DCM_CODE) Dcm_SoftResetModeEntry(void)
{
  /* get Hsm information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(Dcm_CurProtocolId);

  DBG_DCM_SOFTRESETMODEENTRY_ENTRY();

  /* Update the confirmed Reset Mode */
  curHsmInfo->confirmedResetMode = DCM_SOFT_RESET;


  DBG_DCM_SOFTRESETMODEENTRY_EXIT(E_OK);
  return E_OK;
}

FUNC(Std_ReturnType, DCM_CODE) Dcm_EnableRapidPowerShutdownResetModeEntry(void)
{
  /* get Hsm information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(Dcm_CurProtocolId);

  DBG_DCM_ENABLERAPIDPOWERSHUTDOWNRESETMODEENTRY_ENTRY();

  /* Update the confirmed Reset Mode */
  curHsmInfo->confirmedResetMode = DCM_ENABLE_RAPID_POWER_SHUTDOWN_RESET;


  DBG_DCM_ENABLERAPIDPOWERSHUTDOWNRESETMODEENTRY_EXIT(E_OK);
  return E_OK;
}

FUNC(Std_ReturnType, DCM_CODE) Dcm_DisableRapidPowerShutdownResetModeEntry(void)
{
  /* get Hsm information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(Dcm_CurProtocolId);

  DBG_DCM_DISABLERAPIDPOWERSHUTDOWNRESETMODEENTRY_ENTRY();

  /* Update the confirmed Reset Mode */
  curHsmInfo->confirmedResetMode = DCM_DISABLE_RAPID_POWER_SHUTDOWN_RESET;


  DBG_DCM_DISABLERAPIDPOWERSHUTDOWNRESETMODEENTRY_EXIT(E_OK);
  return E_OK;
}

FUNC(Std_ReturnType, DCM_CODE) Dcm_BootloaderResetModeEntry(void)
{
  /* get Hsm information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(Dcm_CurProtocolId);

  DBG_DCM_BOOTLOADERRESETMODEENTRY_ENTRY();

  /* Update the confirmed Reset Mode */
  curHsmInfo->confirmedResetMode = DCM_BOOTLOADER_RESET;


  DBG_DCM_BOOTLOADERRESETMODEENTRY_EXIT(E_OK);
  return E_OK;
}

FUNC(Std_ReturnType, DCM_CODE) Dcm_SsBootloaderResetModeEntry(void)
{
  /* get Hsm information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(Dcm_CurProtocolId);

  DBG_DCM_SSBOOTLOADERRESETMODEENTRY_ENTRY();

  /* Update the confirmed Reset Mode */
  curHsmInfo->confirmedResetMode = DCM_SS_BOOTLOADER_RESET;


  DBG_DCM_SSBOOTLOADERRESETMODEENTRY_EXIT(E_OK);
  return E_OK;
}

#if(DCM_0X28_SVC_ENABLED == STD_ON)

FUNC(Std_ReturnType, DCM_CODE) Dcm_EnableRxTxNormModeEntry(void)
{
  /* get Hsm information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(Dcm_CurProtocolId);

  DBG_DCM_ENABLERXTXNORMMODEENTRY_ENTRY();

  /* Update the confirmed Communication Mode */
  curHsmInfo->confirmedCommunicationMode = DCM_ENABLE_RX_TX_NORM;


  DBG_DCM_ENABLERXTXNORMMODEENTRY_EXIT(E_OK);
  return E_OK;
}

FUNC(Std_ReturnType, DCM_CODE) Dcm_EnableRxDisableTxNormModeEntry(void)
{
  /* get Hsm information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(Dcm_CurProtocolId);

  DBG_DCM_ENABLERXDISABLETXNORMMODEENTRY_ENTRY();

  /* Update the confirmed Communication Mode */
  curHsmInfo->confirmedCommunicationMode = DCM_ENABLE_RX_DISABLE_TX_NORM;


  DBG_DCM_ENABLERXDISABLETXNORMMODEENTRY_EXIT(E_OK);
  return E_OK;
}

FUNC(Std_ReturnType, DCM_CODE) Dcm_DisableRxEnableTxNormModeEntry(void)
{
  /* get Hsm information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(Dcm_CurProtocolId);

  DBG_DCM_DISABLERXENABLETXNORMMODEENTRY_ENTRY();

  /* Update the confirmed Communication Mode */
  curHsmInfo->confirmedCommunicationMode = DCM_DISABLE_RX_ENABLE_TX_NORM;


  DBG_DCM_DISABLERXENABLETXNORMMODEENTRY_EXIT(E_OK);
  return E_OK;
}

FUNC(Std_ReturnType, DCM_CODE) Dcm_DisableRxTxNormModeEntry(void)
{
  /* get Hsm information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(Dcm_CurProtocolId);

  DBG_DCM_DISABLERXTXNORMMODEENTRY_ENTRY();

  /* Update the confirmed Communication Mode */
  curHsmInfo->confirmedCommunicationMode = DCM_DISABLE_RX_TX_NORM;


  DBG_DCM_DISABLERXTXNORMMODEENTRY_EXIT(E_OK);
  return E_OK;
}

FUNC(Std_ReturnType, DCM_CODE) Dcm_EnableRxTxNmModeEntry(void)
{
  /* get Hsm information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(Dcm_CurProtocolId);

  DBG_DCM_ENABLERXTXNMMODEENTRY_ENTRY();

  /* Update the confirmed Communication Mode */
  curHsmInfo->confirmedCommunicationMode = DCM_ENABLE_RX_TX_NM;


  DBG_DCM_ENABLERXTXNMMODEENTRY_EXIT(E_OK);
  return E_OK;
}

FUNC(Std_ReturnType, DCM_CODE) Dcm_EnableRxDisableTxNmModeEntry(void)
{
  /* get Hsm information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(Dcm_CurProtocolId);

  DBG_DCM_ENABLERXDISABLETXNMMODEENTRY_ENTRY();

  /* Update the confirmed Communication Mode */
  curHsmInfo->confirmedCommunicationMode = DCM_ENABLE_RX_DISABLE_TX_NM;


  DBG_DCM_ENABLERXDISABLETXNMMODEENTRY_EXIT(E_OK);
  return E_OK;
}

FUNC(Std_ReturnType, DCM_CODE) Dcm_DisableRxEnableTxNmModeEntry(void)
{
  /* get Hsm information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(Dcm_CurProtocolId);

  DBG_DCM_DISABLERXENABLETXNMMODEENTRY_ENTRY();

  /* Update the confirmed Communication Mode */
  curHsmInfo->confirmedCommunicationMode = DCM_DISABLE_RX_ENABLE_TX_NM;


  DBG_DCM_DISABLERXENABLETXNMMODEENTRY_EXIT(E_OK);
  return E_OK;
}

FUNC(Std_ReturnType, DCM_CODE) Dcm_DisableRxTxNmModeEntry(void)
{
  /* get Hsm information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(Dcm_CurProtocolId);

  DBG_DCM_DISABLERXTXNMMODEENTRY_ENTRY();

  /* Update the confirmed Communication Mode */
  curHsmInfo->confirmedCommunicationMode = DCM_DISABLE_RX_TX_NM;


  DBG_DCM_DISABLERXTXNMMODEENTRY_EXIT(E_OK);
  return E_OK;
}

FUNC(Std_ReturnType, DCM_CODE) Dcm_EnableRxTxNormNmModeEntry(void)
{
  /* get Hsm information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(Dcm_CurProtocolId);

  DBG_DCM_ENABLERXTXNORMNMMODEENTRY_ENTRY();

  /* Update the confirmed Communication Mode */
  curHsmInfo->confirmedCommunicationMode = DCM_ENABLE_RX_TX_NORM_NM;


  DBG_DCM_ENABLERXTXNORMNMMODEENTRY_EXIT(E_OK);
  return E_OK;
}

FUNC(Std_ReturnType, DCM_CODE) Dcm_EnableRxDisableTxNormNmModeEntry(void)
{
  /* get Hsm information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(Dcm_CurProtocolId);

  DBG_DCM_ENABLERXDISABLETXNORMNMMODEENTRY_ENTRY();

  /* Update the confirmed Communication Mode */
  curHsmInfo->confirmedCommunicationMode = DCM_ENABLE_RX_DISABLE_TX_NORM_NM;


  DBG_DCM_ENABLERXDISABLETXNORMNMMODEENTRY_EXIT(E_OK);
  return E_OK;
}

FUNC(Std_ReturnType, DCM_CODE) Dcm_DisableRxEnableTxNormNmModeEntry(void)
{
  /* get Hsm information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(Dcm_CurProtocolId);

  DBG_DCM_DISABLERXENABLETXNORMNMMODEENTRY_ENTRY();

  /* Update the confirmed Communication Mode */
  curHsmInfo->confirmedCommunicationMode = DCM_DISABLE_RX_ENABLE_TX_NORM_NM;


  DBG_DCM_DISABLERXENABLETXNORMNMMODEENTRY_EXIT(E_OK);
  return E_OK;
}

FUNC(Std_ReturnType, DCM_CODE) Dcm_DisableRxTxNormNmModeEntry(void)
{
  /* get Hsm information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(Dcm_CurProtocolId);

  DBG_DCM_DISABLERXTXNORMNMMODEENTRY_ENTRY();

  /* Update the confirmed Communication Mode */
  curHsmInfo->confirmedCommunicationMode = DCM_DISABLE_RX_TX_NORM_NM;


  DBG_DCM_DISABLERXTXNORMNMMODEENTRY_EXIT(E_OK);
  return E_OK;
}

#endif /* #if(DCM_0X28_SVC_ENABLED == STD_ON) */
#endif /* ((DCM_MODEDECLARATION_SUPPORT == STD_OFF) && (DCM_BSWM_API_ENABLED == STD_ON)) */

/*==================[internal function definitions]==============================================*/

STATIC FUNC(void, DCM_CODE) Dcm_Internal_NormalProcessing(void)
{
#if (DCM_HSM_DCM_NUM_INST > 1U)
  uint8_least i;
#endif

#if (DCM_DSP_USE_SERVICE_0X22 == STD_ON) || \
    (DCM_DSP_USE_SERVICE_0X2E == STD_ON) || \
    (DCM_DSP_USE_SERVICE_0X2F == STD_ON) || \
    ((DCM_ROE_ENABLED == STD_ON) && (DCM_ROE_PERSISTENCE == STD_ON) )
  NvM_RequestResultType result = NVM_REQ_NOT_OK;
#endif /* #if (DCM_DSP_USE_SERVICE_0X22 == STD_ON) || \
              (DCM_DSP_USE_SERVICE_0X2E == STD_ON) || \
              (DCM_DSP_USE_SERVICE_0X2F == STD_ON) || \
              ((DCM_ROE_ENABLED == STD_ON) && (DCM_ROE_PERSISTENCE == STD_ON))*/

#if (DCM_DSP_USE_SERVICE_0X22 == STD_ON) || \
    (DCM_DSP_USE_SERVICE_0X2E == STD_ON) || \
    (DCM_DSP_USE_SERVICE_0X2F == STD_ON)
  Std_ReturnType retVal = E_NOT_OK;

  /* Local copies of BlockId and NvMService structure members of 
     global variable Dcm_SignalBufferContext. */
  NvM_BlockIdType LocalSigBufBlockId;
  Dcm_DidNvmOperationType LocalSigBufNvMService;

  /* Flag indicating whether the signal buffer has to be released */
  boolean FreeSignalBuffer = FALSE;
#endif /* #if (DCM_DSP_USE_SERVICE_0X22 == STD_ON) || \
              (DCM_DSP_USE_SERVICE_0X2E == STD_ON) || \
              (DCM_DSP_USE_SERVICE_0X2F == STD_ON) */

  DBG_DCM_INTERNAL_NORMALPROCESSING_ENTRY();

#if (DCM_HSM_DCM_NUM_INST > 1U)
  for (i = 0U; i<DCM_HSM_DCM_NUM_INST; ++i)
#endif
  {
    /* process Dcm timers and emit timeout events */
    Dcm_Internal_ProcessTimers(DCM_PL_SF((uint8)i));
  }
#if(DCM_DSP_USE_SERVICE_0X2F == STD_ON)
  /* Process returnControlToEcu if not completed */
  if(Dcm_ReturnControlToEcuContext.returnCtrlToECUStatus == DCM_RET_CTRL_PENDING)
  {
#if (DCM_DSP_RETURN_CONTROLTOECU_TIMEOUT_REPORT == STD_ON)
    /* Processing time for returncontroltoecu operation expired */
    if(Dcm_ReturnControlToEcuContext.timeoutCount == DCM_DSP_RETURN_CONTROLTOECU_TIMEOUT)
    {
      /* Reset all the structure variables as the timeout occur */
#if (DCM_DEV_ERROR_DETECT == STD_ON)
      DCM_DET_REPORT_ERROR(DCM_SVCID_RETURNCONTROLTOECU, DCM_E_RETURNCONTROLTOECU_TIMEOUT);
#endif
      Dcm_ReturnControlToEcuContext.returnCtrlToECUStatus = DCM_RET_CTRL_FINISHED;
      Dcm_ReturnControlToEcuContext.returnToEcuSigInd = 0U;
      Dcm_ReturnControlToEcuContext.didIndex = 0U;
      Dcm_ReturnControlToEcuContext.timeoutCount = 0U;
    }
    else
#endif
    {
      Dcm_DspInternal_ReturnControlToEcuforallSignals();
    }
  }
#endif

#if (DCM_ROE_ENABLED == STD_ON)

#if (DCM_ROE_PERSISTENCE == STD_ON)
  if( Dcm_ROEPersistenceReadCall == TRUE )
  {
    /* for NvM_GetErrorStatus*/
    retVal = NvM_GetErrorStatus(DCM_ROE_NVM_BLOCK_ID, &result);
    
    if( retVal == E_OK)
    {
      Dcm_ROEPersistenceReadCall = FALSE;
      /* result == NVM_REQ_OK or NVM_REQ_REDUNDANCY_FAILED and Data is written
         into NvM previously */
      if(( result == NVM_REQ_OK )
        || ( result == NVM_REQ_REDUNDANCY_FAILED ))
      {
        if( Dcm_RoeData.NvMWriteFlag == TRUE )
        {
          /* initialize variables to trigger ROE events */
          Dcm_Internal_ROEPersistenceInit();
        }
      }
      else if( result == NVM_REQ_PENDING )
      {
        Dcm_ROEPersistenceReadCall = TRUE;
      }
      else if ( result == NVM_REQ_NV_INVALIDATED )
      {
        /* Restore with Defaults */
        Dcm_Internal_ROEInitVariables();
#if ((DCM_EXT_MANAGED_DIDS == STD_ON) && (DCM_ROE_PRECONF_SUPPORT == STD_ON))
        Dcm_Internal_ROEOnChangeOfDidExternalEventActivate();
#endif /* ((DCM_EXT_MANAGED_DIDS == STD_ON) && (DCM_ROE_PRECONF_SUPPORT == STD_ON)) */
      }
      else
      {
        Dcm_Internal_ROEInitVariables();
#if ((DCM_EXT_MANAGED_DIDS == STD_ON) && (DCM_ROE_PRECONF_SUPPORT == STD_ON))
        Dcm_Internal_ROEOnChangeOfDidExternalEventActivate();
#endif /* ((DCM_EXT_MANAGED_DIDS == STD_ON) && (DCM_ROE_PRECONF_SUPPORT == STD_ON)) */
#if (DCM_DEV_ERROR_DETECT == STD_ON)
        DCM_DET_REPORT_ERROR(DCM_SERVID_MAINFUNCTION, DCM_E_NVM_READ_FAIL);
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
      }
      }
      else
      {
      Dcm_Internal_ROEInitVariables();
#if ((DCM_EXT_MANAGED_DIDS == STD_ON) && (DCM_ROE_PRECONF_SUPPORT == STD_ON))
      Dcm_Internal_ROEOnChangeOfDidExternalEventActivate();
#endif /* ((DCM_EXT_MANAGED_DIDS == STD_ON) && (DCM_ROE_PRECONF_SUPPORT == STD_ON)) */
#if (DCM_DEV_ERROR_DETECT == STD_ON)
      if (retVal == E_NOT_OK)
      {
        DCM_DET_REPORT_ERROR(DCM_SERVID_MAINFUNCTION, DCM_E_NVM_READ_FAIL);
      }
    else
    {
        DCM_DET_REPORT_ERROR(DCM_SVCID_NVMGETERRORSTATUS, DCM_E_INTERFACE_RETURN_VALUE);
    }
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
  }
  }
#endif /* #if (DCM_ROE_PERSISTENCE == STD_ON) */

/* if internally managed DIDs are configured */
#if (DCM_INT_MANAGED_DIDS == STD_ON)

  /* Deviation MISRA-2 */
  if( (Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] ==
                DCM_ROE_EVENT_STARTED) &&
      (Dcm_DidTable[Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_REQUESTEDDID_0x03_IDX]]
                .ExtRoeSupport == FALSE) &&
      (Dcm_RoeInterMsgTime == 0U) )
  {
    Dcm_Internal_ROEOnChangeOfDidPolling();
  }
#endif /* #if (DCM_INT_MANAGED_DIDS == STD_ON) */

#if ((DCM_EXT_MANAGED_DIDS == STD_ON) && (DCM_ROE_PRECONF_SUPPORT == STD_ON))
  if (Dcm_ROEActivateEvent == TRUE)
  {
    Dcm_Internal_ROEOnChangeOfDidExternalEventActivate();
    Dcm_ROEActivateEvent = FALSE;
  }
#endif /* ((DCM_EXT_MANAGED_DIDS == STD_ON) && (DCM_ROE_PRECONF_SUPPORT == STD_ON)) */

#endif /* #if (DCM_ROE_ENABLED == STD_ON) */


#if (DCM_DSP_USE_SERVICE_0X22 == STD_ON) || \
    (DCM_DSP_USE_SERVICE_0X2E == STD_ON) || \
    (DCM_DSP_USE_SERVICE_0X2F == STD_ON)

/*   Cache BlockId and NvMService values from global variable Dcm_SignalBufferContext 
     into local variables to minimize the time spent in critical sections.*/
     
#if (DCM_ASYNC_DID_SERVICES == STD_ON)

  /* ENTER critical section

     Only use critical sections if either of services 0x22 or 0x2E or 0x2F use an Async 
     service handler, for performance reasons. Only a preemption by that handler can 
     have an impact on the Dcm_SignalBufferContext. */

  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
#endif

  LocalSigBufBlockId = Dcm_SignalBufferContext.BlockId;
  LocalSigBufNvMService = Dcm_SignalBufferContext.NvMService;

#if (DCM_ASYNC_DID_SERVICES == STD_ON)
  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
#endif


  /* if the signal buffer is locked by an NvM operation */
  if (LocalSigBufNvMService != DCM_DIDNVMOPERATION_NONE)
  {
    /* check result of the last NvM operation */
    retVal = NvM_GetErrorStatus(LocalSigBufBlockId, &result);

    if (retVal == E_OK)
    {
      if (result != NVM_REQ_PENDING)
      {
        /* NvM operation completed, release SignalBuffer */
        FreeSignalBuffer = TRUE;
      }
    }
    else
    {
#if (DCM_DEV_ERROR_DETECT == STD_ON)
      if (retVal != E_NOT_OK)
      {
        DCM_DET_REPORT_ERROR(DCM_SVCID_NVMGETERRORSTATUS, DCM_E_INTERFACE_RETURN_VALUE);
      }

      if (LocalSigBufNvMService == DCM_DIDNVMOPERATION_READNVMDATA)
      {
        DCM_DET_REPORT_ERROR(DCM_SVCID_NVMREADDATA, DCM_E_NVM_READ_FAIL);
      }
      else if (LocalSigBufNvMService == DCM_DIDNVMOPERATION_WRITENVMDATA)
      {
        DCM_DET_REPORT_ERROR(DCM_SVCID_NVMWRITEDATA, DCM_E_NVM_WRITE_FAIL);
      }
      /* CHECK: NOPARSE */
      else
      {
        /* this branch cannot be reached: 'unreachable code' */
        DCM_UNREACHABLE_CODE_ASSERT(DCM_SERVID_MAINFUNCTION);
      }
      /* CHECK: PARSE */
#endif

      /* NvM_GetErrorStatus() failed, releasing SignalBuffer to prevent
         Dcm DID services from remaining locked  */
      FreeSignalBuffer = TRUE;
    }
  }


  if (FreeSignalBuffer == TRUE)
  {
    if (LocalSigBufNvMService == DCM_DIDNVMOPERATION_WRITENVMDATA)
    {
      /* Dcm.EB.WriteNvmData.CancelJobs.LockBlock */
      /* Lock back the NVRAM block */
      NvM_SetBlockLockStatus(Dcm_SignalBufferContext.BlockId, TRUE);
    }

#if (DCM_ASYNC_DID_SERVICES == STD_ON)
    /* ENTER critical section

     if the signal buffer needs to be freed, it must be done in
     a critical section, to prevent preemption*/

    SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
#endif

    /* Free the signal buffer */
    Dcm_SignalBufferContext.BlockId = 0U;
    Dcm_SignalBufferContext.NvMService = DCM_DIDNVMOPERATION_NONE;

#if (DCM_ASYNC_DID_SERVICES == STD_ON)
    /* LEAVE critical section */
    SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
#endif
  }

#endif /* #if (DCM_DSP_USE_SERVICE_0X22 == STD_ON) || \
              (DCM_DSP_USE_SERVICE_0X2E == STD_ON) || \
              (DCM_DSP_USE_SERVICE_0X2F == STD_ON) */

  DBG_DCM_INTERNAL_NORMALPROCESSING_EXIT();
}

STATIC FUNC(void, DCM_CODE) Dcm_Internal_ProcessTimers(DCM_PDL_SF(const uint8 instIdx))
{
  /* get the context information for the current instance */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo =
    &(DCM_HSM_INFO(instIdx));

  boolean InhibitRetry = FALSE;

  DBG_DCM_INTERNAL_PROCESSTIMERS_ENTRY();

  /* ENTER critical section 
     Protect timers from preemption */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  /* if timerPgBuf is running */
  if (curHsmInfo->timerPgBuf > 0U)
  {
    /* if timerPgBuf is expired */
    if (curHsmInfo->timerPgBuf == 1U)
    {
      /* Emit the event TIMEOUTPGBUF */
      (void)DCM_HSMEMITINST_WRAPPER(&Dcm_HsmScDcm, DCM_CUR_INST_ID(instIdx), DCM_HSM_DCM_EV_TIMEOUTPGBUF);

      /* Inhibit the generation of another RETRY event; if we've cancelled paged buffer processing there
         is no need to call the service handler yet again with a DCM_PENDING OpStatus. */
      InhibitRetry = TRUE;

    }
    --curHsmInfo->timerPgBuf;
  }
#endif /* DCM_PAGEDBUFFER_ENABLED */

  /* if timerTx is running */
  if (curHsmInfo->timerTx > 0U)
  {
    /* if timerTx is expired */
    if (curHsmInfo->timerTx == 1U)
    {
      /* Emit the event TIMEOUTTX */
      (void)DCM_HSMEMITINST_WRAPPER(&Dcm_HsmScDcm, DCM_CUR_INST_ID(instIdx), DCM_HSM_DCM_EV_TIMEOUTTX);
    }
    --curHsmInfo->timerTx;
  }

  /* if timer2 is running */
  if (curHsmInfo->timer2 > 0U)
  {
    /* if timer2 is expired */
    if (curHsmInfo->timer2 == 1U)
    {
      /* Emit the event TIMEOUT2 */
      (void)DCM_HSMEMITINST_WRAPPER(&Dcm_HsmScDcm, DCM_CUR_INST_ID(instIdx), DCM_HSM_DCM_EV_TIMEOUT2);
    }
    --curHsmInfo->timer2;
  }

  /* if timer3 is running */
  if (curHsmInfo->timer3 > 0U)
  {
    /* if timer3 is expired */
    if (curHsmInfo->timer3 == 1U)
    {
      /* Emit the event TIMEOUT3 */
      (void)DCM_HSMEMITINST_WRAPPER(&Dcm_HsmScDcm, DCM_CUR_INST_ID(instIdx), DCM_HSM_DCM_EV_TIMEOUT3);
    }
    --curHsmInfo->timer3;
  }

  /* if Dsp retry timer is running */
  if (curHsmInfo->retryTimer > 0U)
  {
    /* if retryTimer is expired */
    if ((curHsmInfo->retryTimer == 1U) && (FALSE == InhibitRetry))
    {
      /* Emit the event RETRY to Dsp */
      (void)DCM_HSMEMITINST_WRAPPER(&Dcm_HsmScDcm, DCM_CUR_INST_ID(instIdx), DCM_HSM_DCM_EV_RETRY);
    }
    --curHsmInfo->retryTimer;
  }

  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();


  /* if Tx Enabled retry timer is running */
  if (curHsmInfo->retryTimerTxEn > 0U)
  {
    /* if retryTimerTxEn is expired */
    if (curHsmInfo->retryTimerTxEn == 1U)
    {
      /* Emit the event RETRY_TX to Dsp */
      (void)DCM_HSMEMITINST_WRAPPER(&Dcm_HsmScDcm, DCM_CUR_INST_ID(instIdx), DCM_HSM_DCM_EV_RETRY_TX);
    }
    --curHsmInfo->retryTimerTxEn;
  }

  /* check if Delay Time counter is active */
  if (DCM_SEC_DELAY_COUNTER(instIdx) > 0U)
  {
    --DCM_SEC_DELAY_COUNTER(instIdx);
  }

#if(DCM_ROE_ENABLED == STD_ON)

  /* Decrementing inter-message time and event window time for all ROE events needs to be done
     only once(for the first instance), as it is common for all the instances. */
  /* Deviation MISRA-3 */
  if (DCM_CUR_INST_ID(instIdx) == 0U)
  {
    if ((Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x01_IDX] == DCM_ROE_EVENT_STARTED) ||
        (Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] == DCM_ROE_EVENT_STARTED))
    {
    /* Process ROE event window timers */
    Dcm_Internal_ProcessRoeEventWindowTime();
  }
  }
#endif

  DBG_DCM_INTERNAL_PROCESSTIMERS_EXIT();
}

/* if ROE enabled */
#if (DCM_ROE_ENABLED == STD_ON)
STATIC FUNC(void, DCM_CODE) Dcm_Internal_ProcessRoeEventWindowTime(void)
{
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* get configuration for current Rx Pdu Id */
  P2CONST(Dcm_RxPduIdConfigType, AUTOMATIC, DCM_CONST) curRxPduIdConfig
    = &Dcm_RxPduIdConfig[Dcm_RoeData.DcmRxPduId];
#endif

  DBG_DCM_INTERNAL_PROCESSROEEVENTWINDOWTIME_ENTRY();

  
  /* Dcm601: The DCM module shall respect a minimum time between two consecutive
     Roe transmissions. */
  if (Dcm_RoeInterMsgTime > 0U)
  {
    --Dcm_RoeInterMsgTime;
  }

  /* eventWindowTime for OnDTCStatusChange event for ROE service. If
    infiniteeventWindow is requested, Dcm_RoeEventWindowTime[0] will not be
    loaded with value from the request. Hence value of Dcm_RoeEventWindowTime[0]
    will be 0x0000 */
  if (Dcm_RoeEventWindowTime[DCM_ROE_SUBFUNCTION_0x01_IDX] > 0U)
  {
    if(Dcm_RoeEventWindowTime[DCM_ROE_SUBFUNCTION_0x01_IDX] == 1U)
    {
      /* get configuration of current transmission(Tx) buffer */
      P2CONST(Dcm_BufferConfigType, AUTOMATIC, DCM_CONST) curTxBufferConfig =
        &Dcm_BufferConfig[DCM_HSM_CONFIG(curRxPduIdConfig->protocolId).txBufferId];

      /* clear the ROE event */
      Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x01_IDX] = DCM_ROE_EVENT_CLEARED;

      /* ENTER critical section */
      SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

      /* Send the final ROE response if Tx buffer is free and no request is being processed.
         If response cannot be sent, enqueue it. */
      if ((curTxBufferConfig->bufferInfo->state == DCM_BUF_IDLE) && (Dcm_ReqProcessing == FALSE))
      {
        Dcm_RoeSendFinalResponse(DCM_ROE_SUBFUNCTION_0x01_IDX);
      }
      else
      {
        DBG_DCM_ROEPROCESSING((Dcm_ROEProcessing),(DCM_ROE_QUEUED));
        Dcm_ROEProcessing = DCM_ROE_QUEUED;
        DBG_DCM_ROEENQUEUEEVENT((Dcm_ROEEnqueueEvent), (DCM_ROE_FINAL_RESPONSE_01));
        Dcm_ROEEnqueueEvent = DCM_ROE_FINAL_RESPONSE_01;
      }

      /* LEAVE critical section */
      SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
    }
    else
    {
      --Dcm_RoeEventWindowTime[DCM_ROE_SUBFUNCTION_0x01_IDX];
    }
  }

  /* eventWindowTime for onChangeOfDataIdentifier event for ROE service. If
    infiniteeventWindow is requested, Dcm_RoeEventWindowTime[0] will not be
    loaded with value from the request. Hence value of Dcm_RoeEventWindowTime[1]
    will be 0x0000 */
  if (Dcm_RoeEventWindowTime[DCM_ROE_SUBFUNCTION_0x03_IDX] > 0U)
  {
    if(Dcm_RoeEventWindowTime[DCM_ROE_SUBFUNCTION_0x03_IDX] == 1U)
    {
      /* get configuration of current transmission(Tx) buffer */
      P2CONST(Dcm_BufferConfigType, AUTOMATIC, DCM_CONST) curTxBufferConfig =
        &Dcm_BufferConfig[DCM_HSM_CONFIG(curRxPduIdConfig->protocolId).txBufferId];

      /* get corresponding did configuration of the ROE event */
      P2CONST(Dcm_DidServicesType, TYPEDEF, DCM_CONST) didCfg =
        &Dcm_DidTable[Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_REQUESTEDDID_0x03_IDX]];

      /* clear the ROE event */
      Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] = DCM_ROE_EVENT_CLEARED;
      /* if event is externally managed */
      if(didCfg->ExtRoeSupport == TRUE)
      {
        /* Dcm526: Invoke xxx_ActivateEvent with DCM_ROE_UNACTIVE. Return value is not considered
            as currently there is no Diagnostic request*/
        (void) didCfg->RoeActivateFnc(didCfg->RoeEventId, DCM_ROE_UNACTIVE);
      }

      /* ENTER critical section */
      SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

      /* Send the final ROE response if Tx buffer is free.
         If response cannot be sent, enqueue it. */
      if ((curTxBufferConfig->bufferInfo->state == DCM_BUF_IDLE) && (Dcm_ReqProcessing == FALSE))
      {
        Dcm_RoeSendFinalResponse(DCM_ROE_SUBFUNCTION_0x03_IDX);
      }
      else
      {
        DBG_DCM_ROEPROCESSING((Dcm_ROEProcessing),(DCM_ROE_QUEUED));
        Dcm_ROEProcessing = DCM_ROE_QUEUED;
        DBG_DCM_ROEENQUEUEEVENT((Dcm_ROEEnqueueEvent), (DCM_ROE_FINAL_RESPONSE_03));
        Dcm_ROEEnqueueEvent = DCM_ROE_FINAL_RESPONSE_03;
      }

      /* LEAVE critical section */
      SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
    }
    else
    {
      --Dcm_RoeEventWindowTime[DCM_ROE_SUBFUNCTION_0x03_IDX];
    }
  }

  DBG_DCM_INTERNAL_PROCESSROEEVENTWINDOWTIME_EXIT();

}

/* if internally managed DIDs are configured */
#if (DCM_INT_MANAGED_DIDS == STD_ON)

#if ((DCM_EXT_MANAGED_DIDS == STD_ON) && (DCM_ROE_PRECONF_SUPPORT == STD_ON))
STATIC FUNC(void, DCM_CODE)Dcm_Internal_ROEOnChangeOfDidExternalEventActivate(void)
{
  /* To fetch DID configuraion of the requested DID */
  P2CONST(Dcm_DidServicesType, TYPEDEF, DCM_CONST) didCfg =
    &Dcm_DidTable[Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_REQUESTEDDID_0x03_IDX]];

DBG_DCM_INTERNAL_ROEONCHANGEOFDIDEXTERNALEVENTACTIVATE_ENTRY();

  if ((Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] == DCM_ROE_EVENT_STARTED) &&
      (didCfg->ExtRoeSupport == TRUE))
  {
    /* Invoke xxx_ActivateEvent with DCM_ROE_ACTIVE. Return value is not considered as currently
      there is no Diagnostic request */
    (void)didCfg->RoeActivateFnc(didCfg->RoeEventId, DCM_ROE_ACTIVE);
  }
DBG_DCM_INTERNAL_ROEONCHANGEOFDIDEXTERNALEVENTACTIVATE_EXIT();
}
#endif /* ((DCM_EXT_MANAGED_DIDS == STD_ON) && (DCM_ROE_PRECONF_SUPPORT == STD_ON)) */ 

STATIC FUNC(void, DCM_CODE)Dcm_Internal_ROEOnChangeOfDidPolling(void)
{
  /* Total number of signals configured for the DID*/
  P2CONST(Dcm_DidSignalType, TYPEDEF, DCM_CONST) SignalCfg;
  uint16 numSignals;

  /* For collecting instIdx */
  P2CONST(Dcm_RxPduIdConfigType, AUTOMATIC, DCM_CONST) curRxPduIdConfig =
    &Dcm_RxPduIdConfig[Dcm_RoeData.DcmRxPduId];
  P2VAR(Dcm_ChangeInDIDContextType, AUTOMATIC, DCM_VAR) pChangeInDIDContext =
    &Dcm_ChangeInDIDContext[curRxPduIdConfig->protocolId];
  Dcm_NegativeResponseCodeType nrc = E_OK;
  Std_ReturnType RetVal = E_OK;

  DBG_DCM_INTERNAL_ROEONCHANGEOFDIDPOLLING_ENTRY();

  numSignals =
    Dcm_DidTable[Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_REQUESTEDDID_0x03_IDX]].NumSignals;
  SignalCfg = Dcm_DidTable[Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_REQUESTEDDID_0x03_IDX]].Signals;

  /* Start of reading signals referenced by DID */
  /* no asynchronous reading of same DID allowed by other signal read functions */

  /* ENTER critical section */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  if (Dcm_RoePollAsyncState == ROE_POLLING_IDLE)
  {
     Dcm_RoePollAsyncState = ROE_POLLING_ACTIVE;
  }

  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  if (Dcm_RoePollAsyncState == ROE_POLLING_ACTIVE)
  {
    /* Loops over the signals in a DID while return value is ok */
    while((pChangeInDIDContext->SignalInd < numSignals)
           && (RetVal == E_OK))
    {
      /*Index of the signal Data in the table Dcm_DidDataTable[]*/
       uint16 dataIndex = SignalCfg[pChangeInDIDContext->SignalInd].DspDataIndex;
       P2CONST(Dcm_DidDataType, AUTOMATIC, DCM_CONST) dataCfg = &Dcm_DidDataTable[dataIndex];
       /*Starting bit position of signal after the DID in the response data */
       uint16 didDataPosn = SignalCfg[pChangeInDIDContext->SignalInd].DataPos;
       /* Maximum length of the signal in bits */
       uint16 signalLength = dataCfg->DataLength;
       switch(pChangeInDIDContext->DidReadSigConditionSt)
       {
         /* Deviation MISRA-1 */
         case DCM_DID_SIG_CONDITION_CALL:
           if((dataCfg->AccessInterface == DCM_USE_DATA_ASYNCH_FUNC) ||
              (dataCfg->AccessInterface == DCM_USE_DATA_ASYNCH_CLIENT_SERVER))
           {
             RetVal = dataCfg->ConditionCheckReadAsync(DCM_INITIAL, &nrc);
           }
           else
           {
             if((dataCfg->AccessInterface == DCM_USE_DATA_SYNCH_FUNC) ||
                (dataCfg->AccessInterface == DCM_USE_DATA_SYNCH_CLIENT_SERVER))
             {
               RetVal = dataCfg->ConditionCheckReadSync(&nrc);
             }
           }
           if(RetVal != E_OK)
           {
             if(RetVal == DCM_E_NO_DATA)
             {
               RetVal = DCM_E_PENDING;
             }
             break;
           }
           else
           {
             /* continue to read signal data length */
             pChangeInDIDContext->DidReadSigConditionSt = DCM_DID_SIG_READDATA_LEN_CALL;
           }
           /* Deviation MISRA-1 */
           /* fall through to readdata length state */
         case DCM_DID_SIG_READDATA_LEN_CALL:
           if(dataCfg->FixedLength == FALSE)
           {
             RetVal = dataCfg->ReadDataLength(&signalLength);
             if(RetVal != E_OK)
             {
               if(RetVal != DCM_E_PENDING)
               {
                 nrc = DCM_E_GENERALREJECT;
               }
               break;
             }
             else
             {
               /* singnal length is in bytes, convert value into bits */
               signalLength = DCM_GET_BITS(signalLength);
   
               pChangeInDIDContext->DidReadSigConditionSt = DCM_DID_SIG_READ;
             }
           }
           /* Deviation MISRA-1 */
           /* fall through to read signal data state */
         case DCM_DID_SIG_READ:
           if(RetVal == E_OK)
           {
             RetVal = Dcm_DspInternal_ReadDidSignalData(dataIndex, &pChangeInDIDContext->DidNvmDataSt,
                                                      Roe_DidSignalBuffer, &nrc, DCM_INITIAL);
             if(RetVal == E_OK)
             {
                 Dcm_DspInternal_CopySignalData(Roe_DidSignalBuffer, pChangeInDIDContext->NewDIDData, 0U,
                                             didDataPosn, signalLength);
                 pChangeInDIDContext->SignalInd++;
                 pChangeInDIDContext->DidReadSigConditionSt = DCM_DID_SIG_CONDITION_CALL;
                 pChangeInDIDContext->DidNvmDataSt = DCM_DID_SIGNAL_CALL;
             }
           }
           break;
         default:
           /* do nothing */
           break;
       }
     }

     Dcm_RoePollAsyncState = ROE_POLLING_IDLE;
  
     if (RetVal != DCM_E_PENDING)
     {
       if (RetVal == E_OK)
       {
         /* Trigger ROE event transmission */
         Dcm_Internal_ROEOnChangeOfDidTrigEvent(pChangeInDIDContext);
       }

       pChangeInDIDContext->SignalInd = 0U;
       pChangeInDIDContext->DidNvmDataSt = DCM_DID_SIGNAL_CALL;
       pChangeInDIDContext->DidReadSigConditionSt = DCM_DID_SIG_CONDITION_CALL;
    }
  }

  DBG_DCM_INTERNAL_ROEONCHANGEOFDIDPOLLING_EXIT();
}

STATIC FUNC(void, DCM_CODE) Dcm_Internal_ROEOnChangeOfDidTrigEvent(
  P2VAR(Dcm_ChangeInDIDContextType, AUTOMATIC, DCM_APPL_DATA) pChangeInDIDContext )
{
  uint8_least i;

  DBG_DCM_INTERNAL_ROEONCHANGEOFDIDTRIGEVENT_ENTRY();

  for(i = 0U; i < DCM_ROE_DID_BUF_SIZE; i++)
  {
    if(pChangeInDIDContext->SavedDIDData[i] != pChangeInDIDContext->NewDIDData[i])
    {
      uint8_least j;
      /* For first time invocation data should not be compared as init(0x00U) values are stored
      */
      if(Dcm_ROEInternalDidsComparision == FALSE)
      {
        (void)Dcm_DslInternal_ResponseOnOneEvent(
                          &Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_SERVICETORESPOND0_0x03_IDX],
                          3U,
                          Dcm_RoeData.DcmRxPduId);

        /* increment the number of identified events */
        Dcm_RoeData.NoOfIdentifiedEvents[DCM_ROE_SUBFUNCTION_0x03_IDX]++;
      }

      j = i;
      /* copy the rest of data to buffer */
      while (j < DCM_ROE_DID_BUF_SIZE)
      {
        pChangeInDIDContext->SavedDIDData[j] = pChangeInDIDContext->NewDIDData[j];
        ++j;
      }
      /* Can trigger events in Data change */
      Dcm_ROEInternalDidsComparision = FALSE;
      break;
    }
  }
  DBG_DCM_INTERNAL_ROEONCHANGEOFDIDTRIGEVENT_EXIT(pChangeInDIDContxt);
}
#endif /* #if (DCM_INT_MANAGED_DIDS == STD_ON) */

STATIC FUNC(void, DCM_CODE)Dcm_Internal_ROEInitVariables(void)
{
#if (DCM_ROE_PRECONF_SUPPORT == STD_ON)
  P2CONST(Dcm_RoeEventPreConfigType, TYPEDEF, DCM_CONST) eventCfg =
                            &Dcm_RoeEventPreConfiguration[DCM_ROE_PRECONF_ONCHANGEDID_EVENT_IDX];
  uint8_least i;
#endif

  DBG_DCM_INTERNAL_ROEINITVARIABLES_ENTRY();

  /* Initialize data for ROE service */
  Dcm_RoeData.DcmRxPduId = DCM_ROE_INVALID_DATA;
  Dcm_RoeData.RoeStoreBit[DCM_ROE_SUBFUNCTION_0x01_IDX] = FALSE;
  Dcm_RoeData.RoeStoreBit[DCM_ROE_SUBFUNCTION_0x03_IDX] = FALSE;
  Dcm_RoeData.NoOfIdentifiedEvents[DCM_ROE_SUBFUNCTION_0x01_IDX] = DCM_ROE_INIT_DATA;
  Dcm_RoeData.NoOfIdentifiedEvents[DCM_ROE_SUBFUNCTION_0x03_IDX] = DCM_ROE_INIT_DATA;
  Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_EVENTTYPE_IDX] = DCM_ROE_INIT_DATA;
  Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_EVENTWINDOWTIME_IDX] = DCM_ROE_INIT_DATA;
  Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_EVENTTYPERECORD0_0x01_IDX] = DCM_ROE_INIT_DATA;
  Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_SERVICETORESPOND0_0x01_IDX] = DCM_ROE_INIT_DATA;
  Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_SERVICETORESPOND1_0x01_IDX] = DCM_ROE_INIT_DATA;
  Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_SERVICETORESPOND2_0x01_IDX] = DCM_ROE_INIT_DATA;
  Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTTYPE_IDX] = DCM_ROE_INIT_DATA;
  Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTWINDOWTIME_IDX] = DCM_ROE_INIT_DATA;
  Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTTYPERECORD0_0x03_IDX] = DCM_ROE_INIT_DATA;
  Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTTYPERECORD1_0x03_IDX] = DCM_ROE_INIT_DATA;
  Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_SERVICETORESPOND0_0x03_IDX] = DCM_ROE_INIT_DATA;
  Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_SERVICETORESPOND1_0x03_IDX] = DCM_ROE_INIT_DATA;
  Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_SERVICETORESPOND2_0x03_IDX] = DCM_ROE_INIT_DATA;
  Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_REQUESTEDDID_0x03_IDX] = DCM_ROE_INIT_DATA;
  Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x01_IDX] = DCM_ROE_EVENT_CLEARED;
  Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] = DCM_ROE_EVENT_CLEARED;
  Dcm_RoeData.FinalRoeResponse[DCM_ROE_SUBFUNCTION_0x01_IDX] = DCM_ROE_INVALID_FINAL_RES;
  Dcm_RoeData.FinalRoeResponse[DCM_ROE_SUBFUNCTION_0x03_IDX] = DCM_ROE_INVALID_FINAL_RES;
  Dcm_RoeInterMsgTime = 0U;
#if (DCM_ROE_PERSISTENCE == STD_ON)
  Dcm_RoeData.NvMWriteFlag = FALSE;
  Dcm_ROEPersistenceReadCall = FALSE;
#endif

#if (DCM_ROE_PRECONF_SUPPORT == STD_ON)
  Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTTYPE_IDX] = DCM_ROE_ONCHANGE_OF_DATA_IDENTIFIER;
  Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTWINDOWTIME_IDX] = eventCfg->EventWindowTime;
  Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTTYPERECORD0_0x03_IDX] =
                                                                  (uint8)(eventCfg->DID >> 8U);
  Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTTYPERECORD1_0x03_IDX] = (uint8)eventCfg->DID;
  Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_SERVICETORESPOND0_0x03_IDX] = 0x22U;
  Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_SERVICETORESPOND1_0x03_IDX] =
                                                                  (uint8)(eventCfg->DID >> 8U);
  Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_SERVICETORESPOND2_0x03_IDX] = (uint8)eventCfg->DID;

  if(eventCfg->InitialStatus == DCM_ROE_UNACTIVE)
  {
    Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] = DCM_ROE_EVENT_SETUP;
  }
  else
  {
    Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] = DCM_ROE_EVENT_STARTED;
    Dcm_RoeData.DcmRxPduId = eventCfg->RxPduId;
  }
  /* Check if Did is Configured*/
  for (i = 0U; i < DCM_NUM_DID ; ++i)
  {
    if (eventCfg->DID == Dcm_DidTable[i].Did)
    {
      break;
    }
  }
  if(i < DCM_NUM_DID)
  {
    Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_REQUESTEDDID_0x03_IDX] = (uint8)i;
  }
#endif

  /* Initialize eventwindow timers */
  Dcm_RoeEventWindowTime[DCM_ROE_SUBFUNCTION_0x01_IDX] =
                                      Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_EVENTWINDOWTIME_IDX];
  if(Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTWINDOWTIME_IDX] != 2U)
  {
    Dcm_RoeEventWindowTime[DCM_ROE_SUBFUNCTION_0x03_IDX] =
                                      Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTWINDOWTIME_IDX];
  }
  else
  {
    Dcm_RoeEventWindowTime[DCM_ROE_SUBFUNCTION_0x03_IDX] = 0U;
  }

  Dcm_RoePollAsyncState = ROE_POLLING_IDLE;

  DBG_DCM_INTERNAL_ROEINITVARIABLES_EXIT();
}

#if (DCM_ROE_PERSISTENCE == STD_ON)
STATIC FUNC(void, DCM_CODE)Dcm_Internal_ROEPersistenceInit(void)
{
#if (DCM_EXT_MANAGED_DIDS == STD_ON)
  /* To fetch DID configuraion of the requested DID */
  P2CONST(Dcm_DidServicesType, TYPEDEF, DCM_CONST) didCfg =
    &Dcm_DidTable[Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_REQUESTEDDID_0x03_IDX]];
#endif /* (DCM_EXT_MANAGED_DIDS == STD_ON) */    

  DBG_DCM_INTERNAL_ROEPERSISTENCEINIT_ENTRY();

#if (DCM_EXT_MANAGED_DIDS == STD_ON)
    /* Deviation MISRA-3 <+2> */
  if ( (((Dcm_RoeData.RoeStoreBit[DCM_ROE_SUBFUNCTION_0x03_IDX] == TRUE) ||
       (DCM_ROE_PRECONF_SUPPORT == STD_ON)) &&
      (Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] == DCM_ROE_EVENT_STARTED)) &&
      (didCfg->ExtRoeSupport == TRUE))
  {
    /* Invoke xxx_ActivateEvent with DCM_ROE_ACTIVE. Return value is not considered as currently
      there is no Diagnostic request */
    (void)didCfg->RoeActivateFnc(didCfg->RoeEventId, DCM_ROE_ACTIVE);
  }
#endif /* (DCM_EXT_MANAGED_DIDS == STD_ON) */

  /* eventWindowTime is in seconds. Convert to ms in case of finite eventWindowTime */
  if ((Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_EVENTWINDOWTIME_IDX] != 2U) &&
      (Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x01_IDX] == DCM_ROE_EVENT_STARTED))
  {
    /* start EventWindowTime for event onDTCStatusChange */
    Dcm_RoeEventWindowTime[DCM_ROE_SUBFUNCTION_0x01_IDX] =
      ((uint32)(Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_EVENTWINDOWTIME_IDX]) * 1000U)
      / DCM_TASK_TIME;
  }

  if ((Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTWINDOWTIME_IDX] != 2U) &&
      (Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] == DCM_ROE_EVENT_STARTED))
  {
    /* start EventWindowTime for event onChangeOfDataIdentifier */
    Dcm_RoeEventWindowTime[DCM_ROE_SUBFUNCTION_0x03_IDX] =
        ((uint32)(Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTWINDOWTIME_IDX]) * 1000U)
        / DCM_TASK_TIME;
  
    /* Calculate DID mask for shared signals with ROE OnChangeOnDataIdentifer DID */
    Dcm_DspInternal_GetCommonDidSignalMask(Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_REQUESTEDDID_0x03_IDX]);
  }

  DBG_DCM_INTERNAL_ROEPERSISTENCEINIT_EXIT();
}
#endif /* #if (DCM_ROE_PERSISTENCE == STD_ON) */

#endif /* #if(DCM_ROE_ENABLED == STD_ON) */

#define DCM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[end of file]================================================================*/
