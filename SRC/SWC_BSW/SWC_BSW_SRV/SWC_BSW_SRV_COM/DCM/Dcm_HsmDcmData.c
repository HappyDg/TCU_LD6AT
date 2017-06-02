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

/* Definition of the configuration data of the state machine
 * Dcm.
 *
 * This file contains the definition of all used data structures of the state
 * machine model.  It is generated and must not be edited.
 */

/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 6.3 (advisory)
 *     'typedefs' that indicate size and signedness should be used in place
 *     of the basic types.
 *
 *     Reason:
 *     Platform depended 'char' type is only used to define debugging
 *     strings on Windows.
 */

/*==================[inclusions]============================================*/

#include <Std_Types.h>                            /* AUTOSAR standard types */

#include <Dcm_Hsm.h> /* state machine driver interface */
#include <Dcm_HsmDcm.h> /* public statechart model definitions, */
#include <Dcm_HsmDcmInt.h> /* internal statechart model definitions */

/*==================[macros]================================================*/

/** \brief Number of user events */
#define DCM_HSM_DCM_NUM_EVENTS 19U

/* Check if number of hsm instances is defined in the user's configuration */
#ifndef DCM_HSM_DCM_NUM_INST
# error DCM_HSM_DCM_NUM_INST must be defined in Dcm_HsmCfg.h
#endif

/* Check if event queue size of hsm instances is defined in the user's
 * configuration */
#ifndef DCM_HSM_DCM_EV_QUEUE_SIZE
# error DCM_HSM_DCM_EV_QUEUE_SIZE must be defined in Dcm_HsmCfg.h
#endif

/*==================[type definitions]======================================*/

/*==================[internal function declarations]========================*/

/*==================[external function declarations]========================*/

/*==================[internal data]=========================================*/

#define DCM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/* RAM data for instances */
STATIC VAR(Dcm_HsmInstType, DCM_VAR_NOINIT)
  Dcm_HsmInstDcm[DCM_HSM_DCM_NUM_INST];

/* RAM data for event queues */
STATIC VAR(Dcm_HsmEventType, DCM_VAR_NOINIT)
  Dcm_HsmEvQueuesDcm[
    DCM_HSM_DCM_NUM_INST * DCM_HSM_DCM_EV_QUEUE_SIZE];

#define DCM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[external data]=========================================*/

/*==================[internal constants]====================================*/

#define DCM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* *** array of entry/exit and transition actions ***  */
STATIC CONST(Dcm_HsmActionType, DCM_CONST)
  Dcm_HsmDcmActions[DCM_HSM_DCM_NO_OF_ACTIONS] =
{
  &Dcm_HsmDcmSfTopEntry,
  &Dcm_HsmDcmSfWaitForFullComAction1,
  &Dcm_HsmDcmSfWaitForFullComAction2,
  &Dcm_HsmDcmSfOutOfServiceEntry,
  &Dcm_HsmDcmSfOutOfServiceAction1,
  &Dcm_HsmDcmSfOutOfServiceAction2,
  &Dcm_HsmDcmSfOutOfServiceAction3,
  &Dcm_HsmDcmSfOutOfServiceAction5,
  &Dcm_HsmDcmSfOosInitAction1,
  &Dcm_HsmDcmSfOosNotifiedEntry,
  &Dcm_HsmDcmSfInServiceEntry,
  &Dcm_HsmDcmSfInServiceAction1,
  &Dcm_HsmDcmSfFinishingEntry,
  &Dcm_HsmDcmSfFinishingExit,
  &Dcm_HsmDcmSfCancelProcessingEntry,
  &Dcm_HsmDcmSfConfirmingNOkEntry,
  &Dcm_HsmDcmSfConfirmingOkEntry,
  &Dcm_HsmDcmSfRoePrServiceCalledAction2,
  &Dcm_HsmDcmSfRoeFinalResponseEntry,
  &Dcm_HsmDcmSfRoePrResponseEntry,
  &Dcm_HsmDcmSfSendingEntry,
  &Dcm_HsmDcmSfNormalProcessingEntry,
  &Dcm_HsmDcmSfEmulatePgBufProcessingEntry,
  &Dcm_HsmDcmSfEmulatePgBufProcessingExit,
  &Dcm_HsmDcmSfEmulatePgBufProcessingAction1,
  &Dcm_HsmDcmSfEmulatePgBufProcessingAction3,
  &Dcm_HsmDcmSfRealPgBufProcessingEntry,
  &Dcm_HsmDcmSfRealPgBufProcessingAction1,
  &Dcm_HsmDcmSfPgBufDataAvailableEntry,
  &Dcm_HsmDcmSfPgBufDataRequestedEntry,
  &Dcm_HsmDcmSfPgBufDataRequestedExit,
  &Dcm_HsmDcmSfSendingGrEntry,
  &Dcm_HsmDcmSfServiceCalledEntry,
  &Dcm_HsmDcmSfServiceCalledAction4,
  &Dcm_HsmDcmSfServiceCalledAction5,
  &Dcm_HsmDcmSfSendRpEntry,
  &Dcm_HsmDcmSfSendRpExit,
  &Dcm_HsmDcmSfSendRpForcedAction1,
  &Dcm_HsmDcmSfWaitForFullComProcessEntry,
  &Dcm_HsmDcmSfWaitForFullComProcessExit,
  &Dcm_HsmDcmSfWaitForFullComProcessAction1,
  &Dcm_HsmDcmSfWaitForFullComProcessAction4,
  &Dcm_HsmDcmSfWaitForFullComProcessAction5,
};

/* *** array of guards *** */
STATIC CONST(Dcm_HsmGuardType, DCM_CONST)
  Dcm_HsmDcmGuards[DCM_HSM_DCM_NO_OF_GUARDS] =
{
  &Dcm_HsmDcmSfWaitForFullComGuard1,
  &Dcm_HsmDcmSfOutOfServiceGuard2,
  &Dcm_HsmDcmSfOutOfServiceGuard3,
  &Dcm_HsmDcmSfOutOfServiceGuard4,
  &Dcm_HsmDcmSfEmulatePgBufProcessingGuard1,
  &Dcm_HsmDcmSfServiceCalledGuard1,
  &Dcm_HsmDcmSfServiceCalledGuard2,
  &Dcm_HsmDcmSfServiceCalledGuard3,
  &Dcm_HsmDcmSfServiceCalledGuard5,
  &Dcm_HsmDcmSfServiceCalledGuard6,
  &Dcm_HsmDcmSfServiceCalledGuard7,
  &Dcm_HsmDcmSfWaitForApplGuard2,
  &Dcm_HsmDcmSfWaitForFullComProcessGuard4,
  &Dcm_HsmDcmSfWaitForFullComProcessGuard5,
};

#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

#define DCM_START_SEC_CONST_8
#include <MemMap.h>

/* *** exit/action/entry sequences for transitions *** */
/* trans sequence for transition #1 from state WaitForFullCom */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrWaitForFullComSteps1[3] =
{
  DCM_HSM_DCM_AIDX_WAITFORFULLCOM_ACTION_1,
  DCM_HSM_DCM_AIDX_INSERVICE_ENTRY,
  DCM_HSM_DCM_AIDX_FINISHING_ENTRY,
};
/* trans sequence for transition #2 from state WaitForFullCom */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrWaitForFullComSteps2[3] =
{
  DCM_HSM_DCM_AIDX_WAITFORFULLCOM_ACTION_2,
  DCM_HSM_DCM_AIDX_INSERVICE_ENTRY,
  DCM_HSM_DCM_AIDX_SENDING_ENTRY,
};
/* trans sequence for transition #1 from state OutOfService */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrOutOfServiceSteps1[1] =
{
  DCM_HSM_DCM_AIDX_OUTOFSERVICE_ACTION_1,
};
/* trans sequence for transition #2 from state OutOfService */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrOutOfServiceSteps2[2] =
{
  DCM_HSM_DCM_AIDX_OUTOFSERVICE_ACTION_2,
  DCM_HSM_DCM_AIDX_INSERVICE_ENTRY,
};
/* trans sequence for transition #3 from state OutOfService */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrOutOfServiceSteps3[3] =
{
  DCM_HSM_DCM_AIDX_OUTOFSERVICE_ACTION_3,
  DCM_HSM_DCM_AIDX_INSERVICE_ENTRY,
  DCM_HSM_DCM_AIDX_ROEFINALRESPONSE_ENTRY,
};
/* trans sequence for transition #4 from state OutOfService */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrOutOfServiceSteps4[1] =
{
  DCM_HSM_DCM_AIDX_INSERVICE_ENTRY,
};
/* trans sequence for transition #5 from state OutOfService */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrOutOfServiceSteps5[2] =
{
  DCM_HSM_DCM_AIDX_OUTOFSERVICE_ACTION_5,
  DCM_HSM_DCM_AIDX_OOSNOTIFIED_ENTRY,
};
/* trans sequence for transition #1 from state OosInit */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrOosInitSteps1[1] =
{
  DCM_HSM_DCM_AIDX_OOSINIT_ACTION_1,
};
/* trans sequence for transition #1 from state InService */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrInServiceSteps1[1] =
{
  DCM_HSM_DCM_AIDX_INSERVICE_ACTION_1,
};
/* trans sequence for transition #1 from state Finishing */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrFinishingSteps1[3] =
{
  DCM_HSM_DCM_AIDX_FINISHING_EXIT,
  DCM_HSM_DCM_AIDX_OUTOFSERVICE_ENTRY,
  DCM_HSM_DCM_AIDX_OOSNOTIFIED_ENTRY,
};
/* trans sequence for transition #1 from state CancelProcessing */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrCancelProcessingSteps1[3] =
{
  DCM_HSM_DCM_AIDX_FINISHING_EXIT,
  DCM_HSM_DCM_AIDX_OUTOFSERVICE_ENTRY,
  DCM_HSM_DCM_AIDX_OOSNOTIFIED_ENTRY,
};
/* trans sequence for transition #2 from state CancelProcessing */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrCancelProcessingSteps2[3] =
{
  DCM_HSM_DCM_AIDX_FINISHING_EXIT,
  DCM_HSM_DCM_AIDX_OUTOFSERVICE_ENTRY,
  DCM_HSM_DCM_AIDX_OOSNOTIFIED_ENTRY,
};
/* trans sequence for transition #3 from state CancelProcessing */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrCancelProcessingSteps3[3] =
{
  DCM_HSM_DCM_AIDX_FINISHING_EXIT,
  DCM_HSM_DCM_AIDX_OUTOFSERVICE_ENTRY,
  DCM_HSM_DCM_AIDX_OOSNOTIFIED_ENTRY,
};
/* trans sequence for transition #4 from state CancelProcessing */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrCancelProcessingSteps4[3] =
{
  DCM_HSM_DCM_AIDX_FINISHING_EXIT,
  DCM_HSM_DCM_AIDX_OUTOFSERVICE_ENTRY,
  DCM_HSM_DCM_AIDX_OOSNOTIFIED_ENTRY,
};
/* trans sequence for transition #5 from state CancelProcessing */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrCancelProcessingSteps5[3] =
{
  DCM_HSM_DCM_AIDX_FINISHING_EXIT,
  DCM_HSM_DCM_AIDX_OUTOFSERVICE_ENTRY,
  DCM_HSM_DCM_AIDX_OOSNOTIFIED_ENTRY,
};
/* trans sequence for transition #1 from state RoePrServiceCalled */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrRoePrServiceCalledSteps1[1] =
{
  DCM_HSM_DCM_AIDX_SENDING_ENTRY,
};
/* trans sequence for transition #2 from state RoePrServiceCalled */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrRoePrServiceCalledSteps2[3] =
{
  DCM_HSM_DCM_AIDX_ROEPRSERVICECALLED_ACTION_2,
  DCM_HSM_DCM_AIDX_OUTOFSERVICE_ENTRY,
  DCM_HSM_DCM_AIDX_OOSNOTIFIED_ENTRY,
};
/* trans sequence for transition #3 from state RoePrServiceCalled */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrRoePrServiceCalledSteps3[1] =
{
  DCM_HSM_DCM_AIDX_SENDING_ENTRY,
};
/* trans sequence for transition #1 from state Sending */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrSendingSteps1[2] =
{
  DCM_HSM_DCM_AIDX_FINISHING_ENTRY,
  DCM_HSM_DCM_AIDX_CONFIRMINGNOK_ENTRY,
};
/* trans sequence for transition #2 from state Sending */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrSendingSteps2[1] =
{
  DCM_HSM_DCM_AIDX_FINISHING_ENTRY,
};
/* trans sequence for transition #1 from state EmulatePgBufProcessing */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrEmulatePgBufProcessingSteps1[3] =
{
  DCM_HSM_DCM_AIDX_EMULATEPGBUFPROCESSING_EXIT,
  DCM_HSM_DCM_AIDX_EMULATEPGBUFPROCESSING_ACTION_1,
  DCM_HSM_DCM_AIDX_FINISHING_ENTRY,
};
/* trans sequence for transition #2 from state EmulatePgBufProcessing */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrEmulatePgBufProcessingSteps2[2] =
{
  DCM_HSM_DCM_AIDX_EMULATEPGBUFPROCESSING_EXIT,
  DCM_HSM_DCM_AIDX_EMULATEPGBUFPROCESSING_ENTRY,
};
/* trans sequence for transition #3 from state EmulatePgBufProcessing */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrEmulatePgBufProcessingSteps3[4] =
{
  DCM_HSM_DCM_AIDX_EMULATEPGBUFPROCESSING_EXIT,
  DCM_HSM_DCM_AIDX_EMULATEPGBUFPROCESSING_ACTION_3,
  DCM_HSM_DCM_AIDX_FINISHING_ENTRY,
  DCM_HSM_DCM_AIDX_CONFIRMINGNOK_ENTRY,
};
/* trans sequence for transition #1 from state RealPgBufProcessing */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrRealPgBufProcessingSteps1[1] =
{
  DCM_HSM_DCM_AIDX_REALPGBUFPROCESSING_ACTION_1,
};
/* trans sequence for transition #1 from state PgBufDataAvailable */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrPgBufDataAvailableSteps1[1] =
{
  DCM_HSM_DCM_AIDX_PGBUFDATAREQUESTED_ENTRY,
};
/* trans sequence for transition #1 from state PgBufDataRequested */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrPgBufDataRequestedSteps1[2] =
{
  DCM_HSM_DCM_AIDX_PGBUFDATAREQUESTED_EXIT,
  DCM_HSM_DCM_AIDX_PGBUFDATAAVAILABLE_ENTRY,
};
/* trans sequence for transition #1 from state SendingGr */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrSendingGrSteps1[2] =
{
  DCM_HSM_DCM_AIDX_FINISHING_ENTRY,
  DCM_HSM_DCM_AIDX_CANCELPROCESSING_ENTRY,
};
/* trans sequence for transition #2 from state SendingGr */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrSendingGrSteps2[2] =
{
  DCM_HSM_DCM_AIDX_FINISHING_ENTRY,
  DCM_HSM_DCM_AIDX_CANCELPROCESSING_ENTRY,
};
/* trans sequence for transition #1 from state ServiceCalled */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrServiceCalledSteps1[2] =
{
  DCM_HSM_DCM_AIDX_SENDING_ENTRY,
  DCM_HSM_DCM_AIDX_EMULATEPGBUFPROCESSING_ENTRY,
};
/* trans sequence for transition #2 from state ServiceCalled */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrServiceCalledSteps2[1] =
{
  DCM_HSM_DCM_AIDX_SENDING_ENTRY,
};
/* trans sequence for transition #3 from state ServiceCalled */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrServiceCalledSteps3[1] =
{
  DCM_HSM_DCM_AIDX_WAITFORFULLCOMPROCESS_ENTRY,
};
/* trans sequence for transition #4 from state ServiceCalled */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrServiceCalledSteps4[3] =
{
  DCM_HSM_DCM_AIDX_SERVICECALLED_ACTION_4,
  DCM_HSM_DCM_AIDX_OUTOFSERVICE_ENTRY,
  DCM_HSM_DCM_AIDX_OOSNOTIFIED_ENTRY,
};
/* trans sequence for transition #5 from state ServiceCalled */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrServiceCalledSteps5[2] =
{
  DCM_HSM_DCM_AIDX_SERVICECALLED_ACTION_5,
  DCM_HSM_DCM_AIDX_FINISHING_ENTRY,
};
/* trans sequence for transition #6 from state ServiceCalled */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrServiceCalledSteps6[1] =
{
  DCM_HSM_DCM_AIDX_SENDING_ENTRY,
};
/* trans sequence for transition #7 from state ServiceCalled */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrServiceCalledSteps7[1] =
{
  DCM_HSM_DCM_AIDX_WAITFORFULLCOMPROCESS_ENTRY,
};
/* trans sequence for transition #8 from state ServiceCalled */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrServiceCalledSteps8[1] =
{
  DCM_HSM_DCM_AIDX_SENDINGGR_ENTRY,
};
/* trans sequence for transition #1 from state SendRpForced */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrSendRpForcedSteps1[2] =
{
  DCM_HSM_DCM_AIDX_SENDRP_EXIT,
  DCM_HSM_DCM_AIDX_SENDRPFORCED_ACTION_1,
};
/* trans sequence for transition #1 from state SendRpNormal */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrSendRpNormalSteps1[1] =
{
  DCM_HSM_DCM_AIDX_SENDRP_EXIT,
};
/* trans sequence for transition #1 from state WaitForAppl */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrWaitForApplSteps1[1] =
{
  DCM_HSM_DCM_AIDX_SENDRP_ENTRY,
};
/* trans sequence for transition #2 from state WaitForAppl */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrWaitForApplSteps2[1] =
{
  DCM_HSM_DCM_AIDX_SENDINGGR_ENTRY,
};
/* trans sequence for transition #3 from state WaitForAppl */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrWaitForApplSteps3[1] =
{
  DCM_HSM_DCM_AIDX_SENDRP_ENTRY,
};
/* trans sequence for transition #1 from state WaitForFullComProcess */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrWaitForFullComProcessSteps1[1] =
{
  DCM_HSM_DCM_AIDX_WAITFORFULLCOMPROCESS_ACTION_1,
};
/* trans sequence for transition #2 from state WaitForFullComProcess */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrWaitForFullComProcessSteps2[2] =
{
  DCM_HSM_DCM_AIDX_WAITFORFULLCOMPROCESS_EXIT,
  DCM_HSM_DCM_AIDX_SENDING_ENTRY,
};
/* trans sequence for transition #3 from state WaitForFullComProcess */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrWaitForFullComProcessSteps3[2] =
{
  DCM_HSM_DCM_AIDX_WAITFORFULLCOMPROCESS_EXIT,
  DCM_HSM_DCM_AIDX_SENDING_ENTRY,
};
/* trans sequence for transition #4 from state WaitForFullComProcess */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrWaitForFullComProcessSteps4[4] =
{
  DCM_HSM_DCM_AIDX_WAITFORFULLCOMPROCESS_EXIT,
  DCM_HSM_DCM_AIDX_WAITFORFULLCOMPROCESS_ACTION_4,
  DCM_HSM_DCM_AIDX_FINISHING_ENTRY,
  DCM_HSM_DCM_AIDX_CANCELPROCESSING_ENTRY,
};
/* trans sequence for transition #5 from state WaitForFullComProcess */
STATIC CONST(Dcm_HsmActionIdxType, DCM_CONST)
  Dcm_HsmTrWaitForFullComProcessSteps5[4] =
{
  DCM_HSM_DCM_AIDX_WAITFORFULLCOMPROCESS_EXIT,
  DCM_HSM_DCM_AIDX_WAITFORFULLCOMPROCESS_ACTION_5,
  DCM_HSM_DCM_AIDX_FINISHING_ENTRY,
  DCM_HSM_DCM_AIDX_CONFIRMINGNOK_ENTRY,
};

#define DCM_STOP_SEC_CONST_8
#include <MemMap.h>


#define DCM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* transitions from state WaitForFullCom */
STATIC CONST(Dcm_HsmTranType, DCM_CONST)
 Dcm_HsmTrWaitForFullCom[2] =
{
{
  Dcm_HsmTrWaitForFullComSteps1,
  sizeof(Dcm_HsmTrWaitForFullComSteps1)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_BL_TX_RESPONSE, /* triggering event */
  DCM_HSM_DCM_GIDX_WAITFORFULLCOM_GUARD_1, /* guard idx */
  DCM_HSM_DCM_SIDX_FINISHING /* target state */
},
{
  Dcm_HsmTrWaitForFullComSteps2,
  sizeof(Dcm_HsmTrWaitForFullComSteps2)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_BL_TX_RESPONSE, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_DCM_SIDX_SENDING /* target state */
},
};
/* transitions from state OutOfService */
STATIC CONST(Dcm_HsmTranType, DCM_CONST)
 Dcm_HsmTrOutOfService[5] =
{
{
  Dcm_HsmTrOutOfServiceSteps1,
  sizeof(Dcm_HsmTrOutOfServiceSteps1)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_RST2DFLTSESS, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_SIDX_INVALID /* no target state, internal transition */
},
{
  Dcm_HsmTrOutOfServiceSteps2,
  sizeof(Dcm_HsmTrOutOfServiceSteps2)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_ROE, /* triggering event */
  DCM_HSM_DCM_GIDX_OUTOFSERVICE_GUARD_2, /* guard idx */
  DCM_HSM_DCM_SIDX_ROEPRSERVICECALLED /* target state */
},
{
  Dcm_HsmTrOutOfServiceSteps3,
  sizeof(Dcm_HsmTrOutOfServiceSteps3)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_ROE_FINAL_RES, /* triggering event */
  DCM_HSM_DCM_GIDX_OUTOFSERVICE_GUARD_3, /* guard idx */
  DCM_HSM_DCM_SIDX_ROEFINALRESPONSE /* target state */
},
{
  Dcm_HsmTrOutOfServiceSteps4,
  sizeof(Dcm_HsmTrOutOfServiceSteps4)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_RX_IND_OK, /* triggering event */
  DCM_HSM_DCM_GIDX_OUTOFSERVICE_GUARD_4, /* guard idx */
  DCM_HSM_DCM_SIDX_INSERVICE /* target state */
},
{
  Dcm_HsmTrOutOfServiceSteps5,
  sizeof(Dcm_HsmTrOutOfServiceSteps5)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_TIMEOUT3, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_DCM_SIDX_OOSNOTIFIED /* target state */
},
};
/* transitions from state OosInit */
STATIC CONST(Dcm_HsmTranType, DCM_CONST)
 Dcm_HsmTrOosInit[1] =
{
{
  Dcm_HsmTrOosInitSteps1,
  sizeof(Dcm_HsmTrOosInitSteps1)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_RETURN_FROM_BL, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_DCM_SIDX_WAITFORFULLCOM /* target state */
},
};
/* transitions from state InService */
STATIC CONST(Dcm_HsmTranType, DCM_CONST)
 Dcm_HsmTrInService[1] =
{
{
  Dcm_HsmTrInServiceSteps1,
  sizeof(Dcm_HsmTrInServiceSteps1)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_RETRY, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_SIDX_INVALID /* no target state, internal transition */
},
};
/* transitions from state Finishing */
STATIC CONST(Dcm_HsmTranType, DCM_CONST)
 Dcm_HsmTrFinishing[1] =
{
{
  Dcm_HsmTrFinishingSteps1,
  sizeof(Dcm_HsmTrFinishingSteps1)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_PROC_DONE, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_DCM_SIDX_OOSNOTIFIED /* target state */
},
};
/* transitions from state CancelProcessing */
STATIC CONST(Dcm_HsmTranType, DCM_CONST)
 Dcm_HsmTrCancelProcessing[5] =
{
{
  Dcm_HsmTrCancelProcessingSteps1,
  sizeof(Dcm_HsmTrCancelProcessingSteps1)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_FORCE_RCRRP, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_DCM_SIDX_OOSNOTIFIED /* target state */
},
{
  Dcm_HsmTrCancelProcessingSteps2,
  sizeof(Dcm_HsmTrCancelProcessingSteps2)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_PROCESS_PAGE, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_DCM_SIDX_OOSNOTIFIED /* target state */
},
{
  Dcm_HsmTrCancelProcessingSteps3,
  sizeof(Dcm_HsmTrCancelProcessingSteps3)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_PROC_ABORT, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_DCM_SIDX_OOSNOTIFIED /* target state */
},
{
  Dcm_HsmTrCancelProcessingSteps4,
  sizeof(Dcm_HsmTrCancelProcessingSteps4)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_TX_CONF_NOT_OK, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_DCM_SIDX_OOSNOTIFIED /* target state */
},
{
  Dcm_HsmTrCancelProcessingSteps5,
  sizeof(Dcm_HsmTrCancelProcessingSteps5)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_TX_CONF_OK, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_DCM_SIDX_OOSNOTIFIED /* target state */
},
};
/* transitions from state RoePrServiceCalled */
STATIC CONST(Dcm_HsmTranType, DCM_CONST)
 Dcm_HsmTrRoePrServiceCalled[3] =
{
{
  Dcm_HsmTrRoePrServiceCalledSteps1,
  sizeof(Dcm_HsmTrRoePrServiceCalledSteps1)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_PROCESS_PAGE, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_DCM_SIDX_PGBUFPROCESSING /* target state */
},
{
  Dcm_HsmTrRoePrServiceCalledSteps2,
  sizeof(Dcm_HsmTrRoePrServiceCalledSteps2)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_PROC_ABORT, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_DCM_SIDX_OOSNOTIFIED /* target state */
},
{
  Dcm_HsmTrRoePrServiceCalledSteps3,
  sizeof(Dcm_HsmTrRoePrServiceCalledSteps3)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_PROC_DONE, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_DCM_SIDX_SENDING /* target state */
},
};
/* transitions from state Sending */
STATIC CONST(Dcm_HsmTranType, DCM_CONST)
 Dcm_HsmTrSending[2] =
{
{
  Dcm_HsmTrSendingSteps1,
  sizeof(Dcm_HsmTrSendingSteps1)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_TX_CONF_NOT_OK, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_DCM_SIDX_CONFIRMINGNOK /* target state */
},
{
  Dcm_HsmTrSendingSteps2,
  sizeof(Dcm_HsmTrSendingSteps2)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_TX_CONF_OK, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_DCM_SIDX_FINISHING /* target state */
},
};
/* transitions from state EmulatePgBufProcessing */
STATIC CONST(Dcm_HsmTranType, DCM_CONST)
 Dcm_HsmTrEmulatePgBufProcessing[3] =
{
{
  Dcm_HsmTrEmulatePgBufProcessingSteps1,
  sizeof(Dcm_HsmTrEmulatePgBufProcessingSteps1)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_PROCESS_PAGE, /* triggering event */
  DCM_HSM_DCM_GIDX_EMULATEPGBUFPROCESSING_GUARD_1, /* guard idx */
  DCM_HSM_DCM_SIDX_FINISHING /* target state */
},
{
  Dcm_HsmTrEmulatePgBufProcessingSteps2,
  sizeof(Dcm_HsmTrEmulatePgBufProcessingSteps2)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_PROCESS_PAGE, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_DCM_SIDX_EMULATEPGBUFPROCESSING /* target state */
},
{
  Dcm_HsmTrEmulatePgBufProcessingSteps3,
  sizeof(Dcm_HsmTrEmulatePgBufProcessingSteps3)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_TIMEOUTPGBUF, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_DCM_SIDX_CONFIRMINGNOK /* target state */
},
};
/* transitions from state RealPgBufProcessing */
STATIC CONST(Dcm_HsmTranType, DCM_CONST)
 Dcm_HsmTrRealPgBufProcessing[1] =
{
{
  Dcm_HsmTrRealPgBufProcessingSteps1,
  sizeof(Dcm_HsmTrRealPgBufProcessingSteps1)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_TIMEOUTPGBUF, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_SIDX_INVALID /* no target state, internal transition */
},
};
/* transitions from state PgBufDataAvailable */
STATIC CONST(Dcm_HsmTranType, DCM_CONST)
 Dcm_HsmTrPgBufDataAvailable[1] =
{
{
  Dcm_HsmTrPgBufDataAvailableSteps1,
  sizeof(Dcm_HsmTrPgBufDataAvailableSteps1)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_PROVIDE_TX_BUF, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_DCM_SIDX_PGBUFDATAREQUESTED /* target state */
},
};
/* transitions from state PgBufDataRequested */
STATIC CONST(Dcm_HsmTranType, DCM_CONST)
 Dcm_HsmTrPgBufDataRequested[1] =
{
{
  Dcm_HsmTrPgBufDataRequestedSteps1,
  sizeof(Dcm_HsmTrPgBufDataRequestedSteps1)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_PROCESS_PAGE, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_DCM_SIDX_PGBUFDATAAVAILABLE /* target state */
},
};
/* transitions from state SendingGr */
STATIC CONST(Dcm_HsmTranType, DCM_CONST)
 Dcm_HsmTrSendingGr[2] =
{
{
  Dcm_HsmTrSendingGrSteps1,
  sizeof(Dcm_HsmTrSendingGrSteps1)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_TX_CONF_NOT_OK, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_DCM_SIDX_CANCELPROCESSING /* target state */
},
{
  Dcm_HsmTrSendingGrSteps2,
  sizeof(Dcm_HsmTrSendingGrSteps2)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_TX_CONF_OK, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_DCM_SIDX_CANCELPROCESSING /* target state */
},
};
/* transitions from state ServiceCalled */
STATIC CONST(Dcm_HsmTranType, DCM_CONST)
 Dcm_HsmTrServiceCalled[8] =
{
{
  Dcm_HsmTrServiceCalledSteps1,
  sizeof(Dcm_HsmTrServiceCalledSteps1)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_PROCESS_PAGE, /* triggering event */
  DCM_HSM_DCM_GIDX_SERVICECALLED_GUARD_1, /* guard idx */
  DCM_HSM_DCM_SIDX_EMULATEPGBUFPROCESSING /* target state */
},
{
  Dcm_HsmTrServiceCalledSteps2,
  sizeof(Dcm_HsmTrServiceCalledSteps2)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_PROCESS_PAGE, /* triggering event */
  DCM_HSM_DCM_GIDX_SERVICECALLED_GUARD_2, /* guard idx */
  DCM_HSM_DCM_SIDX_PGBUFPROCESSING /* target state */
},
{
  Dcm_HsmTrServiceCalledSteps3,
  sizeof(Dcm_HsmTrServiceCalledSteps3)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_PROCESS_PAGE, /* triggering event */
  DCM_HSM_DCM_GIDX_SERVICECALLED_GUARD_3, /* guard idx */
  DCM_HSM_DCM_SIDX_WAITFORFULLCOMPROCESS /* target state */
},
{
  Dcm_HsmTrServiceCalledSteps4,
  sizeof(Dcm_HsmTrServiceCalledSteps4)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_PROC_ABORT, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_DCM_SIDX_OOSNOTIFIED /* target state */
},
{
  Dcm_HsmTrServiceCalledSteps5,
  sizeof(Dcm_HsmTrServiceCalledSteps5)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_PROC_DONE, /* triggering event */
  DCM_HSM_DCM_GIDX_SERVICECALLED_GUARD_5, /* guard idx */
  DCM_HSM_DCM_SIDX_FINISHING /* target state */
},
{
  Dcm_HsmTrServiceCalledSteps6,
  sizeof(Dcm_HsmTrServiceCalledSteps6)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_PROC_DONE, /* triggering event */
  DCM_HSM_DCM_GIDX_SERVICECALLED_GUARD_6, /* guard idx */
  DCM_HSM_DCM_SIDX_SENDING /* target state */
},
{
  Dcm_HsmTrServiceCalledSteps7,
  sizeof(Dcm_HsmTrServiceCalledSteps7)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_PROC_DONE, /* triggering event */
  DCM_HSM_DCM_GIDX_SERVICECALLED_GUARD_7, /* guard idx */
  DCM_HSM_DCM_SIDX_WAITFORFULLCOMPROCESS /* target state */
},
{
  Dcm_HsmTrServiceCalledSteps8,
  sizeof(Dcm_HsmTrServiceCalledSteps8)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_TX_CONF_NOT_OK, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_DCM_SIDX_SENDINGGR /* target state */
},
};
/* transitions from state SendRpForced */
STATIC CONST(Dcm_HsmTranType, DCM_CONST)
 Dcm_HsmTrSendRpForced[1] =
{
{
  Dcm_HsmTrSendRpForcedSteps1,
  sizeof(Dcm_HsmTrSendRpForcedSteps1)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_TX_CONF_OK, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_DCM_SIDX_WAITFORAPPL /* target state */
},
};
/* transitions from state SendRpNormal */
STATIC CONST(Dcm_HsmTranType, DCM_CONST)
 Dcm_HsmTrSendRpNormal[1] =
{
{
  Dcm_HsmTrSendRpNormalSteps1,
  sizeof(Dcm_HsmTrSendRpNormalSteps1)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_TX_CONF_OK, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_DCM_SIDX_WAITFORAPPL /* target state */
},
};
/* transitions from state WaitForAppl */
STATIC CONST(Dcm_HsmTranType, DCM_CONST)
 Dcm_HsmTrWaitForAppl[3] =
{
{
  Dcm_HsmTrWaitForApplSteps1,
  sizeof(Dcm_HsmTrWaitForApplSteps1)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_FORCE_RCRRP, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_DCM_SIDX_SENDRPFORCED /* target state */
},
{
  Dcm_HsmTrWaitForApplSteps2,
  sizeof(Dcm_HsmTrWaitForApplSteps2)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_TIMEOUT2, /* triggering event */
  DCM_HSM_DCM_GIDX_WAITFORAPPL_GUARD_2, /* guard idx */
  DCM_HSM_DCM_SIDX_SENDINGGR /* target state */
},
{
  Dcm_HsmTrWaitForApplSteps3,
  sizeof(Dcm_HsmTrWaitForApplSteps3)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_TIMEOUT2, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_DCM_SIDX_SENDRPNORMAL /* target state */
},
};
/* transitions from state WaitForFullComProcess */
STATIC CONST(Dcm_HsmTranType, DCM_CONST)
 Dcm_HsmTrWaitForFullComProcess[5] =
{
{
  Dcm_HsmTrWaitForFullComProcessSteps1,
  sizeof(Dcm_HsmTrWaitForFullComProcessSteps1)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_RETRY_TX, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_SIDX_INVALID /* no target state, internal transition */
},
{
  Dcm_HsmTrWaitForFullComProcessSteps2,
  sizeof(Dcm_HsmTrWaitForFullComProcessSteps2)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_PROCESS_PAGE, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_DCM_SIDX_PGBUFPROCESSING /* target state */
},
{
  Dcm_HsmTrWaitForFullComProcessSteps3,
  sizeof(Dcm_HsmTrWaitForFullComProcessSteps3)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_PROC_DONE, /* triggering event */
  DCM_HSM_GIDX_INVALID, /* no guard */
  DCM_HSM_DCM_SIDX_SENDING /* target state */
},
{
  Dcm_HsmTrWaitForFullComProcessSteps4,
  sizeof(Dcm_HsmTrWaitForFullComProcessSteps4)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_TIMEOUTTX, /* triggering event */
  DCM_HSM_DCM_GIDX_WAITFORFULLCOMPROCESS_GUARD_4, /* guard idx */
  DCM_HSM_DCM_SIDX_CANCELPROCESSING /* target state */
},
{
  Dcm_HsmTrWaitForFullComProcessSteps5,
  sizeof(Dcm_HsmTrWaitForFullComProcessSteps5)/sizeof(Dcm_HsmActionIdxType),
  DCM_HSM_DCM_EV_TIMEOUTTX, /* triggering event */
  DCM_HSM_DCM_GIDX_WAITFORFULLCOMPROCESS_GUARD_5, /* guard idx */
  DCM_HSM_DCM_SIDX_CONFIRMINGNOK /* target state */
},
};



/* statechart model description of the Dcm state
   machine */
STATIC CONST(Dcm_HsmStateType, DCM_CONST)
  Dcm_HsmScdDcm[DCM_HSM_DCM_NO_OF_STATES] =
{
  {
  /* description of state Top */
0, /* no non-deferred event mask (no leaf state) */
0, /* no ignored event mask (no leaf state) */
    NULL_PTR,  /* no transitions */
  DCM_HSM_SIDX_INVALID, /* no parent state */
  DCM_HSM_DCM_SIDX_OUTOFSERVICE, /* init state */
  DCM_HSM_DCM_AIDX_TOP_ENTRY, /* entry function */
  DCM_HSM_AIDX_INVALID, /* no exit action */
    0  /* no transitions */

  },
  {
  /* description of state WaitForFullCom */
  /* non-deferred and non-ignored event mask */
 (1UL << DCM_HSM_DCM_EV_BL_TX_RESPONSE)
  | 0UL
,
  /* ignored event mask */
 (1UL << DCM_HSM_DCM_EV_RETURN_FROM_BL)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUT3)
  | (1UL << DCM_HSM_DCM_EV_RX_IND_OK)
  | (1UL << DCM_HSM_DCM_EV_ROE)
  | (1UL << DCM_HSM_DCM_EV_ROE_FINAL_RES)
  | (1UL << DCM_HSM_DCM_EV_RETRY)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTPGBUF)
  | (1UL << DCM_HSM_DCM_EV_PROVIDE_TX_BUF)
  | (1UL << DCM_HSM_DCM_EV_PROC_ABORT)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_NOT_OK)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_OK)
  | (1UL << DCM_HSM_DCM_EV_FORCE_RCRRP)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUT2)
  | (1UL << DCM_HSM_DCM_EV_RETRY_TX)
  | (1UL << DCM_HSM_DCM_EV_PROCESS_PAGE)
  | (1UL << DCM_HSM_DCM_EV_PROC_DONE)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTTX)
  | 0UL
,
    Dcm_HsmTrWaitForFullCom, /* transitions for this state */
  DCM_HSM_DCM_SIDX_TOP, /* parent state */
  DCM_HSM_SIDX_INVALID, /* no init state */
  DCM_HSM_AIDX_INVALID, /* no entry action */
  DCM_HSM_AIDX_INVALID, /* no exit action */
  2 /* num of transitions */

  },
  {
  /* description of state OutOfService */
0, /* no non-deferred event mask (no leaf state) */
0, /* no ignored event mask (no leaf state) */
    Dcm_HsmTrOutOfService, /* transitions for this state */
  DCM_HSM_DCM_SIDX_TOP, /* parent state */
  DCM_HSM_DCM_SIDX_OOSINIT, /* init state */
  DCM_HSM_DCM_AIDX_OUTOFSERVICE_ENTRY, /* entry function */
  DCM_HSM_AIDX_INVALID, /* no exit action */
  5 /* num of transitions */

  },
  {
  /* description of state OosInit */
  /* non-deferred and non-ignored event mask */
 (1UL << DCM_HSM_DCM_EV_RETURN_FROM_BL)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUT3)
  | (1UL << DCM_HSM_DCM_EV_RX_IND_OK)
  | (1UL << DCM_HSM_DCM_EV_ROE)
  | (1UL << DCM_HSM_DCM_EV_ROE_FINAL_RES)
  | (1UL << DCM_HSM_DCM_EV_RST2DFLTSESS)
  | 0UL
,
  /* ignored event mask */
 (1UL << DCM_HSM_DCM_EV_BL_TX_RESPONSE)
  | (1UL << DCM_HSM_DCM_EV_RETRY)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTPGBUF)
  | (1UL << DCM_HSM_DCM_EV_PROVIDE_TX_BUF)
  | (1UL << DCM_HSM_DCM_EV_PROC_ABORT)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_NOT_OK)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_OK)
  | (1UL << DCM_HSM_DCM_EV_FORCE_RCRRP)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUT2)
  | (1UL << DCM_HSM_DCM_EV_RETRY_TX)
  | (1UL << DCM_HSM_DCM_EV_PROCESS_PAGE)
  | (1UL << DCM_HSM_DCM_EV_PROC_DONE)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTTX)
  | 0UL
,
    Dcm_HsmTrOosInit, /* transitions for this state */
  DCM_HSM_DCM_SIDX_OUTOFSERVICE, /* parent state */
  DCM_HSM_SIDX_INVALID, /* no init state */
  DCM_HSM_AIDX_INVALID, /* no entry action */
  DCM_HSM_AIDX_INVALID, /* no exit action */
  1 /* num of transitions */

  },
  {
  /* description of state OosNotified */
  /* non-deferred and non-ignored event mask */
 (1UL << DCM_HSM_DCM_EV_TIMEOUT3)
  | (1UL << DCM_HSM_DCM_EV_RX_IND_OK)
  | (1UL << DCM_HSM_DCM_EV_ROE)
  | (1UL << DCM_HSM_DCM_EV_ROE_FINAL_RES)
  | (1UL << DCM_HSM_DCM_EV_RST2DFLTSESS)
  | 0UL
,
  /* ignored event mask */
 (1UL << DCM_HSM_DCM_EV_BL_TX_RESPONSE)
  | (1UL << DCM_HSM_DCM_EV_RETURN_FROM_BL)
  | (1UL << DCM_HSM_DCM_EV_RETRY)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTPGBUF)
  | (1UL << DCM_HSM_DCM_EV_PROVIDE_TX_BUF)
  | (1UL << DCM_HSM_DCM_EV_PROC_ABORT)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_NOT_OK)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_OK)
  | (1UL << DCM_HSM_DCM_EV_FORCE_RCRRP)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUT2)
  | (1UL << DCM_HSM_DCM_EV_RETRY_TX)
  | (1UL << DCM_HSM_DCM_EV_PROCESS_PAGE)
  | (1UL << DCM_HSM_DCM_EV_PROC_DONE)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTTX)
  | 0UL
,
    NULL_PTR,  /* no transitions */
  DCM_HSM_DCM_SIDX_OUTOFSERVICE, /* parent state */
  DCM_HSM_SIDX_INVALID, /* no init state */
  DCM_HSM_DCM_AIDX_OOSNOTIFIED_ENTRY, /* entry function */
  DCM_HSM_AIDX_INVALID, /* no exit action */
    0  /* no transitions */

  },
  {
  /* description of state InService */
0, /* no non-deferred event mask (no leaf state) */
0, /* no ignored event mask (no leaf state) */
    Dcm_HsmTrInService, /* transitions for this state */
  DCM_HSM_DCM_SIDX_TOP, /* parent state */
  DCM_HSM_DCM_SIDX_SERVICECALLED, /* init state */
  DCM_HSM_DCM_AIDX_INSERVICE_ENTRY, /* entry function */
  DCM_HSM_AIDX_INVALID, /* no exit action */
  1 /* num of transitions */

  },
  {
  /* description of state Finishing */
0, /* no non-deferred event mask (no leaf state) */
0, /* no ignored event mask (no leaf state) */
    Dcm_HsmTrFinishing, /* transitions for this state */
  DCM_HSM_DCM_SIDX_INSERVICE, /* parent state */
  DCM_HSM_DCM_SIDX_CONFIRMINGOK, /* init state */
  DCM_HSM_DCM_AIDX_FINISHING_ENTRY, /* entry function */
  DCM_HSM_DCM_AIDX_FINISHING_EXIT, /* exit function */
  1 /* num of transitions */

  },
  {
  /* description of state CancelProcessing */
  /* non-deferred and non-ignored event mask */
 (1UL << DCM_HSM_DCM_EV_RETRY)
  | (1UL << DCM_HSM_DCM_EV_PROC_ABORT)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_NOT_OK)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_OK)
  | (1UL << DCM_HSM_DCM_EV_FORCE_RCRRP)
  | (1UL << DCM_HSM_DCM_EV_PROCESS_PAGE)
  | (1UL << DCM_HSM_DCM_EV_PROC_DONE)
  | 0UL
,
  /* ignored event mask */
 (1UL << DCM_HSM_DCM_EV_BL_TX_RESPONSE)
  | (1UL << DCM_HSM_DCM_EV_RETURN_FROM_BL)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTPGBUF)
  | (1UL << DCM_HSM_DCM_EV_PROVIDE_TX_BUF)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUT2)
  | (1UL << DCM_HSM_DCM_EV_RETRY_TX)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTTX)
  | 0UL
,
    Dcm_HsmTrCancelProcessing, /* transitions for this state */
  DCM_HSM_DCM_SIDX_FINISHING, /* parent state */
  DCM_HSM_SIDX_INVALID, /* no init state */
  DCM_HSM_DCM_AIDX_CANCELPROCESSING_ENTRY, /* entry function */
  DCM_HSM_AIDX_INVALID, /* no exit action */
  5 /* num of transitions */

  },
  {
  /* description of state ConfirmingNOk */
  /* non-deferred and non-ignored event mask */
 (1UL << DCM_HSM_DCM_EV_RETRY)
  | (1UL << DCM_HSM_DCM_EV_PROC_DONE)
  | 0UL
,
  /* ignored event mask */
 (1UL << DCM_HSM_DCM_EV_BL_TX_RESPONSE)
  | (1UL << DCM_HSM_DCM_EV_RETURN_FROM_BL)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTPGBUF)
  | (1UL << DCM_HSM_DCM_EV_PROVIDE_TX_BUF)
  | (1UL << DCM_HSM_DCM_EV_PROC_ABORT)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_NOT_OK)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_OK)
  | (1UL << DCM_HSM_DCM_EV_FORCE_RCRRP)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUT2)
  | (1UL << DCM_HSM_DCM_EV_RETRY_TX)
  | (1UL << DCM_HSM_DCM_EV_PROCESS_PAGE)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTTX)
  | 0UL
,
    NULL_PTR,  /* no transitions */
  DCM_HSM_DCM_SIDX_FINISHING, /* parent state */
  DCM_HSM_SIDX_INVALID, /* no init state */
  DCM_HSM_DCM_AIDX_CONFIRMINGNOK_ENTRY, /* entry function */
  DCM_HSM_AIDX_INVALID, /* no exit action */
    0  /* no transitions */

  },
  {
  /* description of state ConfirmingOk */
  /* non-deferred and non-ignored event mask */
 (1UL << DCM_HSM_DCM_EV_RETRY)
  | (1UL << DCM_HSM_DCM_EV_PROC_DONE)
  | 0UL
,
  /* ignored event mask */
 (1UL << DCM_HSM_DCM_EV_BL_TX_RESPONSE)
  | (1UL << DCM_HSM_DCM_EV_RETURN_FROM_BL)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTPGBUF)
  | (1UL << DCM_HSM_DCM_EV_PROVIDE_TX_BUF)
  | (1UL << DCM_HSM_DCM_EV_PROC_ABORT)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_NOT_OK)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_OK)
  | (1UL << DCM_HSM_DCM_EV_FORCE_RCRRP)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUT2)
  | (1UL << DCM_HSM_DCM_EV_RETRY_TX)
  | (1UL << DCM_HSM_DCM_EV_PROCESS_PAGE)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTTX)
  | 0UL
,
    NULL_PTR,  /* no transitions */
  DCM_HSM_DCM_SIDX_FINISHING, /* parent state */
  DCM_HSM_SIDX_INVALID, /* no init state */
  DCM_HSM_DCM_AIDX_CONFIRMINGOK_ENTRY, /* entry function */
  DCM_HSM_AIDX_INVALID, /* no exit action */
    0  /* no transitions */

  },
  {
  /* description of state RoePrServiceCalled */
0, /* no non-deferred event mask (no leaf state) */
0, /* no ignored event mask (no leaf state) */
    Dcm_HsmTrRoePrServiceCalled, /* transitions for this state */
  DCM_HSM_DCM_SIDX_INSERVICE, /* parent state */
  DCM_HSM_DCM_SIDX_ROEPRRESPONSE, /* init state */
  DCM_HSM_AIDX_INVALID, /* no entry action */
  DCM_HSM_AIDX_INVALID, /* no exit action */
  3 /* num of transitions */

  },
  {
  /* description of state RoeFinalResponse */
  /* non-deferred and non-ignored event mask */
 (1UL << DCM_HSM_DCM_EV_RETRY)
  | (1UL << DCM_HSM_DCM_EV_PROC_ABORT)
  | (1UL << DCM_HSM_DCM_EV_PROCESS_PAGE)
  | (1UL << DCM_HSM_DCM_EV_PROC_DONE)
  | 0UL
,
  /* ignored event mask */
 (1UL << DCM_HSM_DCM_EV_BL_TX_RESPONSE)
  | (1UL << DCM_HSM_DCM_EV_RETURN_FROM_BL)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTPGBUF)
  | (1UL << DCM_HSM_DCM_EV_PROVIDE_TX_BUF)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_NOT_OK)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_OK)
  | (1UL << DCM_HSM_DCM_EV_FORCE_RCRRP)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUT2)
  | (1UL << DCM_HSM_DCM_EV_RETRY_TX)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTTX)
  | 0UL
,
    NULL_PTR,  /* no transitions */
  DCM_HSM_DCM_SIDX_ROEPRSERVICECALLED, /* parent state */
  DCM_HSM_SIDX_INVALID, /* no init state */
  DCM_HSM_DCM_AIDX_ROEFINALRESPONSE_ENTRY, /* entry function */
  DCM_HSM_AIDX_INVALID, /* no exit action */
    0  /* no transitions */

  },
  {
  /* description of state RoePrResponse */
  /* non-deferred and non-ignored event mask */
 (1UL << DCM_HSM_DCM_EV_RETRY)
  | (1UL << DCM_HSM_DCM_EV_PROC_ABORT)
  | (1UL << DCM_HSM_DCM_EV_PROCESS_PAGE)
  | (1UL << DCM_HSM_DCM_EV_PROC_DONE)
  | 0UL
,
  /* ignored event mask */
 (1UL << DCM_HSM_DCM_EV_BL_TX_RESPONSE)
  | (1UL << DCM_HSM_DCM_EV_RETURN_FROM_BL)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTPGBUF)
  | (1UL << DCM_HSM_DCM_EV_PROVIDE_TX_BUF)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_NOT_OK)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_OK)
  | (1UL << DCM_HSM_DCM_EV_FORCE_RCRRP)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUT2)
  | (1UL << DCM_HSM_DCM_EV_RETRY_TX)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTTX)
  | 0UL
,
    NULL_PTR,  /* no transitions */
  DCM_HSM_DCM_SIDX_ROEPRSERVICECALLED, /* parent state */
  DCM_HSM_SIDX_INVALID, /* no init state */
  DCM_HSM_DCM_AIDX_ROEPRRESPONSE_ENTRY, /* entry function */
  DCM_HSM_AIDX_INVALID, /* no exit action */
    0  /* no transitions */

  },
  {
  /* description of state Sending */
0, /* no non-deferred event mask (no leaf state) */
0, /* no ignored event mask (no leaf state) */
    Dcm_HsmTrSending, /* transitions for this state */
  DCM_HSM_DCM_SIDX_INSERVICE, /* parent state */
  DCM_HSM_DCM_SIDX_NORMALPROCESSING, /* init state */
  DCM_HSM_DCM_AIDX_SENDING_ENTRY, /* entry function */
  DCM_HSM_AIDX_INVALID, /* no exit action */
  2 /* num of transitions */

  },
  {
  /* description of state NormalProcessing */
  /* non-deferred and non-ignored event mask */
 (1UL << DCM_HSM_DCM_EV_RETRY)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_NOT_OK)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_OK)
  | 0UL
,
  /* ignored event mask */
 (1UL << DCM_HSM_DCM_EV_BL_TX_RESPONSE)
  | (1UL << DCM_HSM_DCM_EV_RETURN_FROM_BL)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTPGBUF)
  | (1UL << DCM_HSM_DCM_EV_PROVIDE_TX_BUF)
  | (1UL << DCM_HSM_DCM_EV_PROC_ABORT)
  | (1UL << DCM_HSM_DCM_EV_FORCE_RCRRP)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUT2)
  | (1UL << DCM_HSM_DCM_EV_RETRY_TX)
  | (1UL << DCM_HSM_DCM_EV_PROCESS_PAGE)
  | (1UL << DCM_HSM_DCM_EV_PROC_DONE)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTTX)
  | 0UL
,
    NULL_PTR,  /* no transitions */
  DCM_HSM_DCM_SIDX_SENDING, /* parent state */
  DCM_HSM_SIDX_INVALID, /* no init state */
  DCM_HSM_DCM_AIDX_NORMALPROCESSING_ENTRY, /* entry function */
  DCM_HSM_AIDX_INVALID, /* no exit action */
    0  /* no transitions */

  },
  {
  /* description of state PgBufProcessing */
0, /* no non-deferred event mask (no leaf state) */
0, /* no ignored event mask (no leaf state) */
    NULL_PTR,  /* no transitions */
  DCM_HSM_DCM_SIDX_SENDING, /* parent state */
  DCM_HSM_DCM_SIDX_REALPGBUFPROCESSING, /* init state */
  DCM_HSM_AIDX_INVALID, /* no entry action */
  DCM_HSM_AIDX_INVALID, /* no exit action */
    0  /* no transitions */

  },
  {
  /* description of state EmulatePgBufProcessing */
  /* non-deferred and non-ignored event mask */
 (1UL << DCM_HSM_DCM_EV_RETRY)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTPGBUF)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_NOT_OK)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_OK)
  | (1UL << DCM_HSM_DCM_EV_PROCESS_PAGE)
  | 0UL
,
  /* ignored event mask */
 (1UL << DCM_HSM_DCM_EV_BL_TX_RESPONSE)
  | (1UL << DCM_HSM_DCM_EV_RETURN_FROM_BL)
  | (1UL << DCM_HSM_DCM_EV_PROVIDE_TX_BUF)
  | (1UL << DCM_HSM_DCM_EV_PROC_ABORT)
  | (1UL << DCM_HSM_DCM_EV_FORCE_RCRRP)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUT2)
  | (1UL << DCM_HSM_DCM_EV_RETRY_TX)
  | (1UL << DCM_HSM_DCM_EV_PROC_DONE)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTTX)
  | 0UL
,
    Dcm_HsmTrEmulatePgBufProcessing, /* transitions for this state */
  DCM_HSM_DCM_SIDX_PGBUFPROCESSING, /* parent state */
  DCM_HSM_SIDX_INVALID, /* no init state */
  DCM_HSM_DCM_AIDX_EMULATEPGBUFPROCESSING_ENTRY, /* entry function */
  DCM_HSM_DCM_AIDX_EMULATEPGBUFPROCESSING_EXIT, /* exit function */
  3 /* num of transitions */

  },
  {
  /* description of state RealPgBufProcessing */
0, /* no non-deferred event mask (no leaf state) */
0, /* no ignored event mask (no leaf state) */
    Dcm_HsmTrRealPgBufProcessing, /* transitions for this state */
  DCM_HSM_DCM_SIDX_PGBUFPROCESSING, /* parent state */
  DCM_HSM_DCM_SIDX_PGBUFDATAAVAILABLE, /* init state */
  DCM_HSM_DCM_AIDX_REALPGBUFPROCESSING_ENTRY, /* entry function */
  DCM_HSM_AIDX_INVALID, /* no exit action */
  1 /* num of transitions */

  },
  {
  /* description of state PgBufDataAvailable */
  /* non-deferred and non-ignored event mask */
 (1UL << DCM_HSM_DCM_EV_RETRY)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTPGBUF)
  | (1UL << DCM_HSM_DCM_EV_PROVIDE_TX_BUF)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_NOT_OK)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_OK)
  | 0UL
,
  /* ignored event mask */
 (1UL << DCM_HSM_DCM_EV_BL_TX_RESPONSE)
  | (1UL << DCM_HSM_DCM_EV_RETURN_FROM_BL)
  | (1UL << DCM_HSM_DCM_EV_PROC_ABORT)
  | (1UL << DCM_HSM_DCM_EV_FORCE_RCRRP)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUT2)
  | (1UL << DCM_HSM_DCM_EV_RETRY_TX)
  | (1UL << DCM_HSM_DCM_EV_PROCESS_PAGE)
  | (1UL << DCM_HSM_DCM_EV_PROC_DONE)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTTX)
  | 0UL
,
    Dcm_HsmTrPgBufDataAvailable, /* transitions for this state */
  DCM_HSM_DCM_SIDX_REALPGBUFPROCESSING, /* parent state */
  DCM_HSM_SIDX_INVALID, /* no init state */
  DCM_HSM_DCM_AIDX_PGBUFDATAAVAILABLE_ENTRY, /* entry function */
  DCM_HSM_AIDX_INVALID, /* no exit action */
  1 /* num of transitions */

  },
  {
  /* description of state PgBufDataRequested */
  /* non-deferred and non-ignored event mask */
 (1UL << DCM_HSM_DCM_EV_RETRY)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTPGBUF)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_NOT_OK)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_OK)
  | (1UL << DCM_HSM_DCM_EV_PROCESS_PAGE)
  | 0UL
,
  /* ignored event mask */
 (1UL << DCM_HSM_DCM_EV_BL_TX_RESPONSE)
  | (1UL << DCM_HSM_DCM_EV_RETURN_FROM_BL)
  | (1UL << DCM_HSM_DCM_EV_PROVIDE_TX_BUF)
  | (1UL << DCM_HSM_DCM_EV_PROC_ABORT)
  | (1UL << DCM_HSM_DCM_EV_FORCE_RCRRP)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUT2)
  | (1UL << DCM_HSM_DCM_EV_RETRY_TX)
  | (1UL << DCM_HSM_DCM_EV_PROC_DONE)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTTX)
  | 0UL
,
    Dcm_HsmTrPgBufDataRequested, /* transitions for this state */
  DCM_HSM_DCM_SIDX_REALPGBUFPROCESSING, /* parent state */
  DCM_HSM_SIDX_INVALID, /* no init state */
  DCM_HSM_DCM_AIDX_PGBUFDATAREQUESTED_ENTRY, /* entry function */
  DCM_HSM_DCM_AIDX_PGBUFDATAREQUESTED_EXIT, /* exit function */
  1 /* num of transitions */

  },
  {
  /* description of state SendingGr */
  /* non-deferred and non-ignored event mask */
 (1UL << DCM_HSM_DCM_EV_RETRY)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_NOT_OK)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_OK)
  | 0UL
,
  /* ignored event mask */
 (1UL << DCM_HSM_DCM_EV_BL_TX_RESPONSE)
  | (1UL << DCM_HSM_DCM_EV_RETURN_FROM_BL)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTPGBUF)
  | (1UL << DCM_HSM_DCM_EV_PROVIDE_TX_BUF)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUT2)
  | (1UL << DCM_HSM_DCM_EV_RETRY_TX)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTTX)
  | 0UL
,
    Dcm_HsmTrSendingGr, /* transitions for this state */
  DCM_HSM_DCM_SIDX_INSERVICE, /* parent state */
  DCM_HSM_SIDX_INVALID, /* no init state */
  DCM_HSM_DCM_AIDX_SENDINGGR_ENTRY, /* entry function */
  DCM_HSM_AIDX_INVALID, /* no exit action */
  2 /* num of transitions */

  },
  {
  /* description of state ServiceCalled */
0, /* no non-deferred event mask (no leaf state) */
0, /* no ignored event mask (no leaf state) */
    Dcm_HsmTrServiceCalled, /* transitions for this state */
  DCM_HSM_DCM_SIDX_INSERVICE, /* parent state */
  DCM_HSM_DCM_SIDX_WAITFORAPPL, /* init state */
  DCM_HSM_DCM_AIDX_SERVICECALLED_ENTRY, /* entry function */
  DCM_HSM_AIDX_INVALID, /* no exit action */
  8 /* num of transitions */

  },
  {
  /* description of state SendRp */
0, /* no non-deferred event mask (no leaf state) */
0, /* no ignored event mask (no leaf state) */
    NULL_PTR,  /* no transitions */
  DCM_HSM_DCM_SIDX_SERVICECALLED, /* parent state */
  DCM_HSM_DCM_SIDX_SENDRPNORMAL, /* init state */
  DCM_HSM_DCM_AIDX_SENDRP_ENTRY, /* entry function */
  DCM_HSM_DCM_AIDX_SENDRP_EXIT, /* exit function */
    0  /* no transitions */

  },
  {
  /* description of state SendRpForced */
  /* non-deferred and non-ignored event mask */
 (1UL << DCM_HSM_DCM_EV_RETRY)
  | (1UL << DCM_HSM_DCM_EV_PROC_ABORT)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_NOT_OK)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_OK)
  | 0UL
,
  /* ignored event mask */
 (1UL << DCM_HSM_DCM_EV_BL_TX_RESPONSE)
  | (1UL << DCM_HSM_DCM_EV_RETURN_FROM_BL)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTPGBUF)
  | (1UL << DCM_HSM_DCM_EV_PROVIDE_TX_BUF)
  | (1UL << DCM_HSM_DCM_EV_FORCE_RCRRP)
  | (1UL << DCM_HSM_DCM_EV_RETRY_TX)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTTX)
  | 0UL
,
    Dcm_HsmTrSendRpForced, /* transitions for this state */
  DCM_HSM_DCM_SIDX_SENDRP, /* parent state */
  DCM_HSM_SIDX_INVALID, /* no init state */
  DCM_HSM_AIDX_INVALID, /* no entry action */
  DCM_HSM_AIDX_INVALID, /* no exit action */
  1 /* num of transitions */

  },
  {
  /* description of state SendRpNormal */
  /* non-deferred and non-ignored event mask */
 (1UL << DCM_HSM_DCM_EV_RETRY)
  | (1UL << DCM_HSM_DCM_EV_PROC_ABORT)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_NOT_OK)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_OK)
  | 0UL
,
  /* ignored event mask */
 (1UL << DCM_HSM_DCM_EV_BL_TX_RESPONSE)
  | (1UL << DCM_HSM_DCM_EV_RETURN_FROM_BL)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTPGBUF)
  | (1UL << DCM_HSM_DCM_EV_PROVIDE_TX_BUF)
  | (1UL << DCM_HSM_DCM_EV_FORCE_RCRRP)
  | (1UL << DCM_HSM_DCM_EV_RETRY_TX)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTTX)
  | 0UL
,
    Dcm_HsmTrSendRpNormal, /* transitions for this state */
  DCM_HSM_DCM_SIDX_SENDRP, /* parent state */
  DCM_HSM_SIDX_INVALID, /* no init state */
  DCM_HSM_AIDX_INVALID, /* no entry action */
  DCM_HSM_AIDX_INVALID, /* no exit action */
  1 /* num of transitions */

  },
  {
  /* description of state WaitForAppl */
  /* non-deferred and non-ignored event mask */
 (1UL << DCM_HSM_DCM_EV_RETRY)
  | (1UL << DCM_HSM_DCM_EV_PROC_ABORT)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_NOT_OK)
  | (1UL << DCM_HSM_DCM_EV_FORCE_RCRRP)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUT2)
  | (1UL << DCM_HSM_DCM_EV_PROCESS_PAGE)
  | (1UL << DCM_HSM_DCM_EV_PROC_DONE)
  | 0UL
,
  /* ignored event mask */
 (1UL << DCM_HSM_DCM_EV_BL_TX_RESPONSE)
  | (1UL << DCM_HSM_DCM_EV_RETURN_FROM_BL)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTPGBUF)
  | (1UL << DCM_HSM_DCM_EV_PROVIDE_TX_BUF)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_OK)
  | (1UL << DCM_HSM_DCM_EV_RETRY_TX)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTTX)
  | 0UL
,
    Dcm_HsmTrWaitForAppl, /* transitions for this state */
  DCM_HSM_DCM_SIDX_SERVICECALLED, /* parent state */
  DCM_HSM_SIDX_INVALID, /* no init state */
  DCM_HSM_AIDX_INVALID, /* no entry action */
  DCM_HSM_AIDX_INVALID, /* no exit action */
  3 /* num of transitions */

  },
  {
  /* description of state WaitForFullComProcess */
  /* non-deferred and non-ignored event mask */
 (1UL << DCM_HSM_DCM_EV_RETRY)
  | (1UL << DCM_HSM_DCM_EV_RETRY_TX)
  | (1UL << DCM_HSM_DCM_EV_PROCESS_PAGE)
  | (1UL << DCM_HSM_DCM_EV_PROC_DONE)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTTX)
  | 0UL
,
  /* ignored event mask */
 (1UL << DCM_HSM_DCM_EV_BL_TX_RESPONSE)
  | (1UL << DCM_HSM_DCM_EV_RETURN_FROM_BL)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUTPGBUF)
  | (1UL << DCM_HSM_DCM_EV_PROVIDE_TX_BUF)
  | (1UL << DCM_HSM_DCM_EV_PROC_ABORT)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_NOT_OK)
  | (1UL << DCM_HSM_DCM_EV_TX_CONF_OK)
  | (1UL << DCM_HSM_DCM_EV_FORCE_RCRRP)
  | (1UL << DCM_HSM_DCM_EV_TIMEOUT2)
  | 0UL
,
    Dcm_HsmTrWaitForFullComProcess, /* transitions for this state */
  DCM_HSM_DCM_SIDX_INSERVICE, /* parent state */
  DCM_HSM_SIDX_INVALID, /* no init state */
  DCM_HSM_DCM_AIDX_WAITFORFULLCOMPROCESS_ENTRY, /* entry function */
  DCM_HSM_DCM_AIDX_WAITFORFULLCOMPROCESS_EXIT, /* exit function */
  5 /* num of transitions */

  }
};

#if (DCM_HSM_TRACE == STD_ON)
/* Deviation MISRA-1 */
STATIC CONSTP2CONST(char, DCM_CONST, DCM_CONST)
  Dcm_HsmDcmStateNames[] =
{
  "Top",
  "WaitForFullCom",
  "OutOfService",
  "OosInit",
  "OosNotified",
  "InService",
  "Finishing",
  "CancelProcessing",
  "ConfirmingNOk",
  "ConfirmingOk",
  "RoePrServiceCalled",
  "RoeFinalResponse",
  "RoePrResponse",
  "Sending",
  "NormalProcessing",
  "PgBufProcessing",
  "EmulatePgBufProcessing",
  "RealPgBufProcessing",
  "PgBufDataAvailable",
  "PgBufDataRequested",
  "SendingGr",
  "ServiceCalled",
  "SendRp",
  "SendRpForced",
  "SendRpNormal",
  "WaitForAppl",
  "WaitForFullComProcess",
};

/* Deviation MISRA-1 */
STATIC CONSTP2CONST(char, DCM_CONST, DCM_CONST)
  Dcm_HsmDcmActionNames[] =
{
  "Top entry",
  "WaitForFullCom action 1",
  "WaitForFullCom action 2",
  "OutOfService entry",
  "OutOfService action 1",
  "OutOfService action 2",
  "OutOfService action 3",
  "OutOfService action 5",
  "OosInit action 1",
  "OosNotified entry",
  "InService entry",
  "InService action 1",
  "Finishing entry",
  "Finishing exit",
  "CancelProcessing entry",
  "ConfirmingNOk entry",
  "ConfirmingOk entry",
  "RoePrServiceCalled action 2",
  "RoeFinalResponse entry",
  "RoePrResponse entry",
  "Sending entry",
  "NormalProcessing entry",
  "EmulatePgBufProcessing entry",
  "EmulatePgBufProcessing exit",
  "EmulatePgBufProcessing action 1",
  "EmulatePgBufProcessing action 3",
  "RealPgBufProcessing entry",
  "RealPgBufProcessing action 1",
  "PgBufDataAvailable entry",
  "PgBufDataRequested entry",
  "PgBufDataRequested exit",
  "SendingGr entry",
  "ServiceCalled entry",
  "ServiceCalled action 4",
  "ServiceCalled action 5",
  "SendRp entry",
  "SendRp exit",
  "SendRpForced action 1",
  "WaitForFullComProcess entry",
  "WaitForFullComProcess exit",
  "WaitForFullComProcess action 1",
  "WaitForFullComProcess action 4",
  "WaitForFullComProcess action 5",
};

/* Deviation MISRA-1 */
STATIC CONSTP2CONST(char, DCM_CONST, DCM_CONST)
  Dcm_HsmDcmGuardNames[] =
{
  "WaitForFullCom guard 1",
  "OutOfService guard 2",
  "OutOfService guard 3",
  "OutOfService guard 4",
  "EmulatePgBufProcessing guard 1",
  "ServiceCalled guard 1",
  "ServiceCalled guard 2",
  "ServiceCalled guard 3",
  "ServiceCalled guard 5",
  "ServiceCalled guard 6",
  "ServiceCalled guard 7",
  "WaitForAppl guard 2",
  "WaitForFullComProcess guard 4",
  "WaitForFullComProcess guard 5",
};

/* Deviation MISRA-1 */
STATIC CONSTP2CONST(char, DCM_CONST, DCM_CONST)
  Dcm_HsmDcmEventNames[] =
{
  "BL_TX_RESPONSE",
  "RETURN_FROM_BL",
  "TIMEOUT3",
  "RX_IND_OK",
  "ROE",
  "ROE_FINAL_RES",
  "RST2DFLTSESS",
  "RETRY",
  "TIMEOUTPGBUF",
  "PROVIDE_TX_BUF",
  "PROC_ABORT",
  "TX_CONF_NOT_OK",
  "TX_CONF_OK",
  "FORCE_RCRRP",
  "TIMEOUT2",
  "RETRY_TX",
  "PROCESS_PAGE",
  "PROC_DONE",
  "TIMEOUTTX",
};
#endif

/*==================[external constants]====================================*/

/* Top level state chart description data */
CONST(Dcm_HsmStatechartType, DCM_CONST)
  Dcm_HsmScDcm =
{
  Dcm_HsmScdDcm, /* state description array */
  Dcm_HsmDcmActions, /* actions */
  Dcm_HsmDcmGuards, /* guards */
  Dcm_HsmInstDcm, /* instances RAM */
  Dcm_HsmEvQueuesDcm, /* event queues RAM */
#if (DCM_HSM_TRACE == STD_ON)
  "Dcm", /* name of the HSM */
  Dcm_HsmDcmStateNames,
  Dcm_HsmDcmActionNames,
  Dcm_HsmDcmGuardNames,
  Dcm_HsmDcmEventNames,
#endif
  DCM_HSM_DCM_NUM_INST, /* num of instances */
  DCM_HSM_DCM_EV_QUEUE_SIZE, /* event queue size */
  DCM_HSM_DCM_SIDX_TOP, /* top state index */
  DCM_HSM_DCM_NUM_EVENTS /* num of events */

};


#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[internal function definitions]=========================*/

/*==================[external function definitions]=========================*/

/*==================[end of file]===========================================*/
