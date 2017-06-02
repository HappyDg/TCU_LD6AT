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

#ifndef DCM_HSMDCMINT_H
#define DCM_HSMDCMINT_H

/* Internal interface for the Dcm state
 * machine.
 *
 * This header must only be included by
 * Dcm_HsmDcmData.c and Dcm_HsmDcmFnct.c.
 */

/*==================[inclusions]============================================*/

#include <Std_Types.h>                            /* AUTOSAR standard types */

/* include state machine driver interface */
#include <Dcm_Hsm.h>

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/* *** State indices and IDs for states *** */

#define DCM_HSM_DCM_SIDX_TOP 0U
#define DCM_HSM_DCM_SIDX_WAITFORFULLCOM 1U
#define DCM_HSM_DCM_SIDX_OUTOFSERVICE 2U
#define DCM_HSM_DCM_SIDX_OOSINIT 3U
#define DCM_HSM_DCM_SIDX_OOSNOTIFIED 4U
#define DCM_HSM_DCM_SIDX_INSERVICE 5U
#define DCM_HSM_DCM_SIDX_FINISHING 6U
#define DCM_HSM_DCM_SIDX_CANCELPROCESSING 7U
#define DCM_HSM_DCM_SIDX_CONFIRMINGNOK 8U
#define DCM_HSM_DCM_SIDX_CONFIRMINGOK 9U
#define DCM_HSM_DCM_SIDX_ROEPRSERVICECALLED 10U
#define DCM_HSM_DCM_SIDX_ROEFINALRESPONSE 11U
#define DCM_HSM_DCM_SIDX_ROEPRRESPONSE 12U
#define DCM_HSM_DCM_SIDX_SENDING 13U
#define DCM_HSM_DCM_SIDX_NORMALPROCESSING 14U
#define DCM_HSM_DCM_SIDX_PGBUFPROCESSING 15U
#define DCM_HSM_DCM_SIDX_EMULATEPGBUFPROCESSING 16U
#define DCM_HSM_DCM_SIDX_REALPGBUFPROCESSING 17U
#define DCM_HSM_DCM_SIDX_PGBUFDATAAVAILABLE 18U
#define DCM_HSM_DCM_SIDX_PGBUFDATAREQUESTED 19U
#define DCM_HSM_DCM_SIDX_SENDINGGR 20U
#define DCM_HSM_DCM_SIDX_SERVICECALLED 21U
#define DCM_HSM_DCM_SIDX_SENDRP 22U
#define DCM_HSM_DCM_SIDX_SENDRPFORCED 23U
#define DCM_HSM_DCM_SIDX_SENDRPNORMAL 24U
#define DCM_HSM_DCM_SIDX_WAITFORAPPL 25U
#define DCM_HSM_DCM_SIDX_WAITFORFULLCOMPROCESS 26U
#define DCM_HSM_DCM_NO_OF_STATES 27U

  typedef uint8 Dcm_HsmDcmStateIdType;
/* typedefed type only used for debugging */

/* *** IDs for entry/axit and transition actions *** */


#define DCM_HSM_DCM_AIDX_TOP_ENTRY 0U
#define DCM_HSM_DCM_AIDX_WAITFORFULLCOM_ACTION_1 1U
#define DCM_HSM_DCM_AIDX_WAITFORFULLCOM_ACTION_2 2U
#define DCM_HSM_DCM_AIDX_OUTOFSERVICE_ENTRY 3U
#define DCM_HSM_DCM_AIDX_OUTOFSERVICE_ACTION_1 4U
#define DCM_HSM_DCM_AIDX_OUTOFSERVICE_ACTION_2 5U
#define DCM_HSM_DCM_AIDX_OUTOFSERVICE_ACTION_3 6U
#define DCM_HSM_DCM_AIDX_OUTOFSERVICE_ACTION_5 7U
#define DCM_HSM_DCM_AIDX_OOSINIT_ACTION_1 8U
#define DCM_HSM_DCM_AIDX_OOSNOTIFIED_ENTRY 9U
#define DCM_HSM_DCM_AIDX_INSERVICE_ENTRY 10U
#define DCM_HSM_DCM_AIDX_INSERVICE_ACTION_1 11U
#define DCM_HSM_DCM_AIDX_FINISHING_ENTRY 12U
#define DCM_HSM_DCM_AIDX_FINISHING_EXIT 13U
#define DCM_HSM_DCM_AIDX_CANCELPROCESSING_ENTRY 14U
#define DCM_HSM_DCM_AIDX_CONFIRMINGNOK_ENTRY 15U
#define DCM_HSM_DCM_AIDX_CONFIRMINGOK_ENTRY 16U
#define DCM_HSM_DCM_AIDX_ROEPRSERVICECALLED_ACTION_2 17U
#define DCM_HSM_DCM_AIDX_ROEFINALRESPONSE_ENTRY 18U
#define DCM_HSM_DCM_AIDX_ROEPRRESPONSE_ENTRY 19U
#define DCM_HSM_DCM_AIDX_SENDING_ENTRY 20U
#define DCM_HSM_DCM_AIDX_NORMALPROCESSING_ENTRY 21U
#define DCM_HSM_DCM_AIDX_EMULATEPGBUFPROCESSING_ENTRY 22U
#define DCM_HSM_DCM_AIDX_EMULATEPGBUFPROCESSING_EXIT 23U
#define DCM_HSM_DCM_AIDX_EMULATEPGBUFPROCESSING_ACTION_1 24U
#define DCM_HSM_DCM_AIDX_EMULATEPGBUFPROCESSING_ACTION_3 25U
#define  DCM_HSM_DCM_AIDX_REALPGBUFPROCESSING_ENTRY 26U
#define DCM_HSM_DCM_AIDX_REALPGBUFPROCESSING_ACTION_1 27U 
#define DCM_HSM_DCM_AIDX_PGBUFDATAAVAILABLE_ENTRY 28U
#define DCM_HSM_DCM_AIDX_PGBUFDATAREQUESTED_ENTRY 29U
#define DCM_HSM_DCM_AIDX_PGBUFDATAREQUESTED_EXIT 30U
#define DCM_HSM_DCM_AIDX_SENDINGGR_ENTRY 31U
#define DCM_HSM_DCM_AIDX_SERVICECALLED_ENTRY 32U
#define DCM_HSM_DCM_AIDX_SERVICECALLED_ACTION_4 33U
#define DCM_HSM_DCM_AIDX_SERVICECALLED_ACTION_5 34U
#define DCM_HSM_DCM_AIDX_SENDRP_ENTRY 35U
#define DCM_HSM_DCM_AIDX_SENDRP_EXIT 36U
#define DCM_HSM_DCM_AIDX_SENDRPFORCED_ACTION_1 37U
#define DCM_HSM_DCM_AIDX_WAITFORFULLCOMPROCESS_ENTRY 38U
#define DCM_HSM_DCM_AIDX_WAITFORFULLCOMPROCESS_EXIT 39U
#define DCM_HSM_DCM_AIDX_WAITFORFULLCOMPROCESS_ACTION_1 40U
#define DCM_HSM_DCM_AIDX_WAITFORFULLCOMPROCESS_ACTION_4 41U
#define DCM_HSM_DCM_AIDX_WAITFORFULLCOMPROCESS_ACTION_5 42U
#define DCM_HSM_DCM_NO_OF_ACTIONS 43U

typedef uint8 Dcm_HsmDcmActionIdType;
/* typedefed type only used for debugging */

/* *** IDs for guards *** */
#define DCM_HSM_DCM_GIDX_WAITFORFULLCOM_GUARD_1 0U
#define DCM_HSM_DCM_GIDX_OUTOFSERVICE_GUARD_2 1U
#define DCM_HSM_DCM_GIDX_OUTOFSERVICE_GUARD_3 2U
#define DCM_HSM_DCM_GIDX_OUTOFSERVICE_GUARD_4 3U
#define DCM_HSM_DCM_GIDX_EMULATEPGBUFPROCESSING_GUARD_1 4U
#define DCM_HSM_DCM_GIDX_SERVICECALLED_GUARD_1 5U
#define DCM_HSM_DCM_GIDX_SERVICECALLED_GUARD_2 6U
#define DCM_HSM_DCM_GIDX_SERVICECALLED_GUARD_3 7U
#define DCM_HSM_DCM_GIDX_SERVICECALLED_GUARD_5 8U
#define DCM_HSM_DCM_GIDX_SERVICECALLED_GUARD_6 9U
#define DCM_HSM_DCM_GIDX_SERVICECALLED_GUARD_7 10U
#define DCM_HSM_DCM_GIDX_WAITFORAPPL_GUARD_2 11U
#define DCM_HSM_DCM_GIDX_WAITFORFULLCOMPROCESS_GUARD_4 12U
#define DCM_HSM_DCM_GIDX_WAITFORFULLCOMPROCESS_GUARD_5 13U
#define DCM_HSM_DCM_NO_OF_GUARDS 14U

typedef uint8 Dcm_HsmDcmGuardIdType;
/* typedefed type only used for debugging */

/*==================[external function declarations]========================*/

#define DCM_START_SEC_CODE
#include <MemMap.h>

/* function declarations of state entry, exit, guard, action functions
 * defined in Dcm_fnct.c */

extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfTopEntry(
  DCM_PDL_SF(const uint8 instIdx));

/* implements guard '!ResponseRequired' */
extern FUNC(boolean, DCM_CODE)
 Dcm_HsmDcmSfWaitForFullComGuard1(
  DCM_PDL_SF(const uint8 instIdx));
/* implements action 'ReEnableRx' */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfWaitForFullComAction1(
  DCM_PDL_SF(const uint8 instIdx));
/* implements action 'Fill response' */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfWaitForFullComAction2(
  DCM_PDL_SF(const uint8 instIdx));

extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfOutOfServiceEntry(
  DCM_PDL_SF(const uint8 instIdx));
/* implements action 'Drop to default session' */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfOutOfServiceAction1(
  DCM_PDL_SF(const uint8 instIdx));
/* implements guard 'TxEnabled && CheckRoeBuf()' */
extern FUNC(boolean, DCM_CODE)
 Dcm_HsmDcmSfOutOfServiceGuard2(
  DCM_PDL_SF(const uint8 instIdx));
/* implements action 'ConfigureRoePduIds' */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfOutOfServiceAction2(
  DCM_PDL_SF(const uint8 instIdx));
/* implements guard 'TxEnabled' */
extern FUNC(boolean, DCM_CODE)
 Dcm_HsmDcmSfOutOfServiceGuard3(
  DCM_PDL_SF(const uint8 instIdx));
/* implements action 'ConfigureRoePduIds' */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfOutOfServiceAction3(
  DCM_PDL_SF(const uint8 instIdx));
/* implements guard 'CheckRxBuf()' */
extern FUNC(boolean, DCM_CODE)
 Dcm_HsmDcmSfOutOfServiceGuard4(
  DCM_PDL_SF(const uint8 instIdx));
/* implements action 'drop to default session;' */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfOutOfServiceAction5(
  DCM_PDL_SF(const uint8 instIdx));

/* implements action 'ComM_DCM_ActiveDiagnostic()' */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfOosInitAction1(
  DCM_PDL_SF(const uint8 instIdx));

extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfOosNotifiedEntry(
  DCM_PDL_SF(const uint8 instIdx));

extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfInServiceEntry(
  DCM_PDL_SF(const uint8 instIdx));
/* implements action 'if (RetryTimer==0) CallService(PENDING)' */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfInServiceAction1(
  DCM_PDL_SF(const uint8 instIdx));

extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfFinishingEntry(
  DCM_PDL_SF(const uint8 instIdx));
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfFinishingExit(
  DCM_PDL_SF(const uint8 instIdx));

extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfCancelProcessingEntry(
  DCM_PDL_SF(const uint8 instIdx));

extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfConfirmingNOkEntry(
  DCM_PDL_SF(const uint8 instIdx));

extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfConfirmingOkEntry(
  DCM_PDL_SF(const uint8 instIdx));

/* implements action 'Free Rx Buffer; Free Tx Buffer' */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfRoePrServiceCalledAction2(
  DCM_PDL_SF(const uint8 instIdx));

extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfRoeFinalResponseEntry(
  DCM_PDL_SF(const uint8 instIdx));

extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfRoePrResponseEntry(
  DCM_PDL_SF(const uint8 instIdx));

extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfSendingEntry(
  DCM_PDL_SF(const uint8 instIdx));

extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfNormalProcessingEntry(
  DCM_PDL_SF(const uint8 instIdx));


extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfEmulatePgBufProcessingEntry(
  DCM_PDL_SF(const uint8 instIdx));
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfEmulatePgBufProcessingExit(
  DCM_PDL_SF(const uint8 instIdx));
/* implements guard 'resTotLen>=MsgContext->resDataLen+1' */
extern FUNC(boolean, DCM_CODE)
 Dcm_HsmDcmSfEmulatePgBufProcessingGuard1(
  DCM_PDL_SF(const uint8 instIdx));
/* implements action 'Free Rx Buffer; Free Tx Buffer;' */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfEmulatePgBufProcessingAction1(
  DCM_PDL_SF(const uint8 instIdx));
/* implements action 'Free Rx Buffer; Free Tx Buffer; DspInternal_CancelPagedBufferProcessing()' */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfEmulatePgBufProcessingAction3(
  DCM_PDL_SF(const uint8 instIdx));

extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfRealPgBufProcessingEntry(
  DCM_PDL_SF(const uint8 instIdx));
/* implements action 'DspInternal_CancelPagedBufferProcessing' */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfRealPgBufProcessingAction1(
  DCM_PDL_SF(const uint8 instIdx));

extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfPgBufDataAvailableEntry(
  DCM_PDL_SF(const uint8 instIdx));

extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfPgBufDataRequestedEntry(
  DCM_PDL_SF(const uint8 instIdx));
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfPgBufDataRequestedExit(
  DCM_PDL_SF(const uint8 instIdx));

extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfSendingGrEntry(
  DCM_PDL_SF(const uint8 instIdx));

extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfServiceCalledEntry(
  DCM_PDL_SF(const uint8 instIdx));
/* implements guard 'spr' */
extern FUNC(boolean, DCM_CODE)
 Dcm_HsmDcmSfServiceCalledGuard1(
  DCM_PDL_SF(const uint8 instIdx));
/* implements guard '!Dcm_SupressResponse() && Tx En' */
extern FUNC(boolean, DCM_CODE)
 Dcm_HsmDcmSfServiceCalledGuard2(
  DCM_PDL_SF(const uint8 instIdx));
/* implements guard '!Dcm_SupressResponse() && Tx Dis' */
extern FUNC(boolean, DCM_CODE)
 Dcm_HsmDcmSfServiceCalledGuard3(
  DCM_PDL_SF(const uint8 instIdx));
/* implements action 'Free Rx Buffer; Free Tx Buffer; if (non-default session) StartTimer3(S3Timer);' */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfServiceCalledAction4(
  DCM_PDL_SF(const uint8 instIdx));
/* implements guard 'Dcm_SupressResponse()' */
extern FUNC(boolean, DCM_CODE)
 Dcm_HsmDcmSfServiceCalledGuard5(
  DCM_PDL_SF(const uint8 instIdx));
/* implements action 'Free Rx Buffer; Free Tx Buffer;' */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfServiceCalledAction5(
  DCM_PDL_SF(const uint8 instIdx));
/* implements guard '!Dcm_SupressResponse() && Tx En' */
extern FUNC(boolean, DCM_CODE)
 Dcm_HsmDcmSfServiceCalledGuard6(
  DCM_PDL_SF(const uint8 instIdx));
/* implements guard '!Dcm_SupressResponse() && Tx Dis' */
extern FUNC(boolean, DCM_CODE)
 Dcm_HsmDcmSfServiceCalledGuard7(
  DCM_PDL_SF(const uint8 instIdx));

extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfSendRpEntry(
  DCM_PDL_SF(const uint8 instIdx));
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfSendRpExit(
  DCM_PDL_SF(const uint8 instIdx));

/* implements action 'CallService(FORCE_RCRRP_OK);' */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfSendRpForcedAction1(
  DCM_PDL_SF(const uint8 instIdx));


/* implements guard 'RpCntr >= Limit' */
extern FUNC(boolean, DCM_CODE)
 Dcm_HsmDcmSfWaitForApplGuard2(
  DCM_PDL_SF(const uint8 instIdx));

extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfWaitForFullComProcessEntry(
  DCM_PDL_SF(const uint8 instIdx));
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfWaitForFullComProcessExit(
  DCM_PDL_SF(const uint8 instIdx));
/* implements action 'if(TxDis)' */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfWaitForFullComProcessAction1(
  DCM_PDL_SF(const uint8 instIdx));
/* implements guard 'PageBufferInProgress()' */
extern FUNC(boolean, DCM_CODE)
 Dcm_HsmDcmSfWaitForFullComProcessGuard4(
  DCM_PDL_SF(const uint8 instIdx));
/* implements action 'Free Rx Buffer; Free Tx Buffer;' */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfWaitForFullComProcessAction4(
  DCM_PDL_SF(const uint8 instIdx));
/* implements guard '!PageBufferInProgress()' */
extern FUNC(boolean, DCM_CODE)
 Dcm_HsmDcmSfWaitForFullComProcessGuard5(
  DCM_PDL_SF(const uint8 instIdx));
/* implements action 'Free Rx Buffer; Free Tx Buffer;' */
extern FUNC(void, DCM_CODE)
 Dcm_HsmDcmSfWaitForFullComProcessAction5(
  DCM_PDL_SF(const uint8 instIdx));


#define DCM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* defined DCM_HSMDCMINT_H */
/*==================[end of file]===========================================*/
