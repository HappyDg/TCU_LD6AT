/**
 * \file
 *
 * \brief AUTOSAR ComM
 *
 * This file contains the implementation of the AUTOSAR
 * module ComM.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/* Definition of the configuration data of the state machine
 * ComM.
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

#include <ComM_Hsm.h> /* state machine driver interface */
#include <ComM_HsmComM.h> /* public statechart model definitions, */
#include <ComM_HsmComMInt.h> /* internal statechart model definitions */

/*==================[macros]================================================*/

/** \brief Number of user events */
#define COMM_HSM_COMM_NUM_EVENTS 17U

/* Check if number of hsm instances is defined in the user's configuration */
#ifndef COMM_HSM_COMM_NUM_INST
#error COMM_HSM_COMM_NUM_INST must be defined in ComM_HsmCfg.h
#endif


/*==================[type definitions]======================================*/

/*==================[internal function declarations]========================*/

/*==================[external function declarations]========================*/

/*==================[internal data]=========================================*/

#define COMM_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>

/* RAM data for event counters */
STATIC VAR(uint8, COMM_VAR_NOINIT)
  ComM_HsmEvCountersComM[
    COMM_HSM_COMM_NUM_INST * COMM_HSM_COMM_NUM_EVENTS];

/* RAM data for event queues */
STATIC VAR(ComM_HsmEventType, COMM_VAR_NOINIT)
  ComM_HsmEvQueuesComM[
    COMM_HSM_COMM_NUM_INST * COMM_HSM_COMM_NUM_EVENTS];

#define COMM_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>


#define COMM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/* RAM data for instances */
STATIC VAR(ComM_HsmInstType, COMM_VAR_NOINIT)
  ComM_HsmInstComM[COMM_HSM_COMM_NUM_INST];

#define COMM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[external data]=========================================*/

/*==================[internal constants]====================================*/

#define COMM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* *** array of entry/exit/do and transition actions *** */
STATIC CONST(ComM_HsmActionType, COMM_CONST)
  ComM_HsmComMActions[COMM_HSM_COMM_NO_OF_ACTIONS] =
{
  &ComM_HsmComMSfFullComNotifiedEntry,
  &ComM_HsmComMSfFullComNotifiedAction1,
  &ComM_HsmComMSfAcceptLimitToNoComEntry,
  &ComM_HsmComMSfAcceptLimitToNoComAction1,
  &ComM_HsmComMSfAcceptLimitToNoComAction2,
  &ComM_HsmComMSfAcceptLimitToNoComAction3,
  &ComM_HsmComMSfNetReqDelayedNoNmEntry,
  &ComM_HsmComMSfNetReqNmAction1,
  &ComM_HsmComMSfNetReqNmAction2,
  &ComM_HsmComMSfNetReqNoNmEntry,
  &ComM_HsmComMSfReadySleepNmEntry,
  &ComM_HsmComMSfReadySleepNmAction1,
  &ComM_HsmComMSfReadySleepNoNmEntry,
  &ComM_HsmComMSfPassiveStartupWaitEntry,
  &ComM_HsmComMSfPassiveStartupWaitExit,
  &ComM_HsmComMSfPassiveStartupWaitAction2,
  &ComM_HsmComMSfPassiveStartupWaitAction3,
  &ComM_HsmComMSfReqNetworkWaitEntry,
  &ComM_HsmComMSfReqNetworkWaitExit,
  &ComM_HsmComMSfWaitForFullComEntry,
  &ComM_HsmComMSfWaitForFullComExit,
  &ComM_HsmComMSfWaitForFullComAction1,
  &ComM_HsmComMSfWffcToNetReqActiveAction1,
  &ComM_HsmComMSfWffcToNetReqPassiveAction1,
  &ComM_HsmComMSfNoComFirstEntry,
  &ComM_HsmComMSfNoComNotifedEntry,
  &ComM_HsmComMSfWaitForNoComEntry,
  &ComM_HsmComMSfWaitForNoComExit,
  &ComM_HsmComMSfPendingRequestEntry,
  &ComM_HsmComMSfSilentComAction1,
  &ComM_HsmComMSfSilentComNotifedEntry,
  &ComM_HsmComMSfWaitForSilentComEntry,
  &ComM_HsmComMSfWaitForSilentComExit,
};

/* *** array of guards *** */
STATIC CONST(ComM_HsmGuardType, COMM_CONST)
  ComM_HsmComMGuards[COMM_HSM_COMM_NO_OF_GUARDS] =
{
  &ComM_HsmComMSfAcceptLimitToNoComGuard2,
  &ComM_HsmComMSfAcceptLimitToNoComGuard3,
  &ComM_HsmComMSfNetReqDelayedNoNmGuard1,
  &ComM_HsmComMSfNetReqDelayedNoNmGuard2,
  &ComM_HsmComMSfNetReqDelayedNoNmGuard3,
  &ComM_HsmComMSfNetReqNmGuard2,
  &ComM_HsmComMSfReadySleepNmGuard1,
  &ComM_HsmComMSfReadySleepNoNmGuard1,
  &ComM_HsmComMSfPassiveStartupWaitGuard1,
  &ComM_HsmComMSfPassiveStartupWaitGuard2,
  &ComM_HsmComMSfWaitForFullComGuard3,
  &ComM_HsmComMSfWffcToNetReqActiveGuard1,
  &ComM_HsmComMSfWffcToNetReqPassiveGuard1,
  &ComM_HsmComMSfNoPendingRequestGuard4,
  &ComM_HsmComMSfPendingRequestGuard1,
  &ComM_HsmComMSfReqRunActiveGuard1,
  &ComM_HsmComMSfReqRunActiveGuard2,
  &ComM_HsmComMSfReqRunPassiveGuard1,
  &ComM_HsmComMSfSilentComGuard3,
};

#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

#define COMM_START_SEC_CONST_8
#include <MemMap.h>

/* *** exit/action/entry sequences for transitions *** */
/* trans sequence for transition #1 from state FullComNotified */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrFullComNotifiedSteps1[2] =
{
  COMM_HSM_COMM_AIDX_FULLCOMNOTIFIED_ACTION_1,
  COMM_HSM_COMM_AIDX_WAITFORNOCOM_ENTRY,
};
/* trans sequence for transition #1 from state AcceptLimitToNoCom */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrAcceptLimitToNoComSteps1[1] =
{
  COMM_HSM_COMM_AIDX_ACCEPTLIMITTONOCOM_ACTION_1,
};
/* trans sequence for transition #2 from state AcceptLimitToNoCom */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrAcceptLimitToNoComSteps2[2] =
{
  COMM_HSM_COMM_AIDX_ACCEPTLIMITTONOCOM_ACTION_2,
  COMM_HSM_COMM_AIDX_WAITFORFULLCOM_ENTRY,
};
/* trans sequence for transition #3 from state AcceptLimitToNoCom */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrAcceptLimitToNoComSteps3[2] =
{
  COMM_HSM_COMM_AIDX_ACCEPTLIMITTONOCOM_ACTION_3,
  COMM_HSM_COMM_AIDX_WAITFORFULLCOM_ENTRY,
};
/* trans sequence for transition #1 from state NetReqDelayedNoNm */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrNetReqDelayedNoNmSteps1[1] =
{
  COMM_HSM_COMM_AIDX_NOCOMNOTIFED_ENTRY,
};
/* trans sequence for transition #2 from state NetReqDelayedNoNm */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrNetReqDelayedNoNmSteps2[1] =
{
  COMM_HSM_COMM_AIDX_WAITFORNOCOM_ENTRY,
};
/* trans sequence for transition #3 from state NetReqDelayedNoNm */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrNetReqDelayedNoNmSteps3[1] =
{
  COMM_HSM_COMM_AIDX_READYSLEEPNONM_ENTRY,
};
/* trans sequence for transition #1 from state NetReqNm */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrNetReqNmSteps1[1] =
{
  COMM_HSM_COMM_AIDX_NETREQNM_ACTION_1,
};
/* trans sequence for transition #2 from state NetReqNm */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrNetReqNmSteps2[2] =
{
  COMM_HSM_COMM_AIDX_NETREQNM_ACTION_2,
  COMM_HSM_COMM_AIDX_READYSLEEPNM_ENTRY,
};
/* trans sequence for transition #1 from state NetReqNoNm */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrNetReqNoNmSteps1[1] =
{
  COMM_HSM_COMM_AIDX_NETREQDELAYEDNONM_ENTRY,
};
/* trans sequence for transition #1 from state ReadySleepNm */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrReadySleepNmSteps1[2] =
{
  COMM_HSM_COMM_AIDX_READYSLEEPNM_ACTION_1,
  COMM_HSM_COMM_AIDX_ACCEPTLIMITTONOCOM_ENTRY,
};
/* trans sequence for transition #1 from state ReadySleepNoNm */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrReadySleepNoNmSteps1[2] =
{
  COMM_HSM_COMM_AIDX_ACCEPTLIMITTONOCOM_ENTRY,
  COMM_HSM_COMM_AIDX_NETREQNONM_ENTRY,
};
/* trans sequence for transition #2 from state ReadySleepNoNm */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrReadySleepNoNmSteps2[1] =
{
  COMM_HSM_COMM_AIDX_WAITFORNOCOM_ENTRY,
};
/* trans sequence for transition #1 from state PassiveStartupWait */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrPassiveStartupWaitSteps1[3] =
{
  COMM_HSM_COMM_AIDX_PASSIVESTARTUPWAIT_EXIT,
  COMM_HSM_COMM_AIDX_FULLCOMNOTIFIED_ENTRY,
  COMM_HSM_COMM_AIDX_ACCEPTLIMITTONOCOM_ENTRY,
};
/* trans sequence for transition #2 from state PassiveStartupWait */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrPassiveStartupWaitSteps2[4] =
{
  COMM_HSM_COMM_AIDX_PASSIVESTARTUPWAIT_EXIT,
  COMM_HSM_COMM_AIDX_PASSIVESTARTUPWAIT_ACTION_2,
  COMM_HSM_COMM_AIDX_FULLCOMNOTIFIED_ENTRY,
  COMM_HSM_COMM_AIDX_ACCEPTLIMITTONOCOM_ENTRY,
};
/* trans sequence for transition #3 from state PassiveStartupWait */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrPassiveStartupWaitSteps3[4] =
{
  COMM_HSM_COMM_AIDX_PASSIVESTARTUPWAIT_EXIT,
  COMM_HSM_COMM_AIDX_PASSIVESTARTUPWAIT_ACTION_3,
  COMM_HSM_COMM_AIDX_FULLCOMNOTIFIED_ENTRY,
  COMM_HSM_COMM_AIDX_READYSLEEPNM_ENTRY,
};
/* trans sequence for transition #4 from state PassiveStartupWait */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrPassiveStartupWaitSteps4[2] =
{
  COMM_HSM_COMM_AIDX_PASSIVESTARTUPWAIT_EXIT,
  COMM_HSM_COMM_AIDX_PASSIVESTARTUPWAIT_ENTRY,
};
/* trans sequence for transition #1 from state ReqNetworkWait */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrReqNetworkWaitSteps1[3] =
{
  COMM_HSM_COMM_AIDX_REQNETWORKWAIT_EXIT,
  COMM_HSM_COMM_AIDX_FULLCOMNOTIFIED_ENTRY,
  COMM_HSM_COMM_AIDX_ACCEPTLIMITTONOCOM_ENTRY,
};
/* trans sequence for transition #2 from state ReqNetworkWait */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrReqNetworkWaitSteps2[2] =
{
  COMM_HSM_COMM_AIDX_REQNETWORKWAIT_EXIT,
  COMM_HSM_COMM_AIDX_REQNETWORKWAIT_ENTRY,
};
/* trans sequence for transition #1 from state WaitForFullCom */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrWaitForFullComSteps1[1] =
{
  COMM_HSM_COMM_AIDX_WAITFORFULLCOM_ACTION_1,
};
/* trans sequence for transition #2 from state WaitForFullCom */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrWaitForFullComSteps2[2] =
{
  COMM_HSM_COMM_AIDX_WAITFORFULLCOM_EXIT,
  COMM_HSM_COMM_AIDX_WAITFORNOCOM_ENTRY,
};
/* trans sequence for transition #3 from state WaitForFullCom */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrWaitForFullComSteps3[2] =
{
  COMM_HSM_COMM_AIDX_WAITFORFULLCOM_EXIT,
  COMM_HSM_COMM_AIDX_WAITFORNOCOM_ENTRY,
};
/* trans sequence for transition #1 from state WffcToNetReq */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrWffcToNetReqSteps1[4] =
{
  COMM_HSM_COMM_AIDX_WAITFORFULLCOM_EXIT,
  COMM_HSM_COMM_AIDX_FULLCOMNOTIFIED_ENTRY,
  COMM_HSM_COMM_AIDX_ACCEPTLIMITTONOCOM_ENTRY,
  COMM_HSM_COMM_AIDX_NETREQNONM_ENTRY,
};
/* trans sequence for transition #1 from state WffcToNetReqActive */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrWffcToNetReqActiveSteps1[3] =
{
  COMM_HSM_COMM_AIDX_WAITFORFULLCOM_EXIT,
  COMM_HSM_COMM_AIDX_WFFCTONETREQACTIVE_ACTION_1,
  COMM_HSM_COMM_AIDX_REQNETWORKWAIT_ENTRY,
};
/* trans sequence for transition #1 from state WffcToNetReqPassive */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrWffcToNetReqPassiveSteps1[3] =
{
  COMM_HSM_COMM_AIDX_WAITFORFULLCOM_EXIT,
  COMM_HSM_COMM_AIDX_WFFCTONETREQPASSIVE_ACTION_1,
  COMM_HSM_COMM_AIDX_PASSIVESTARTUPWAIT_ENTRY,
};
/* trans sequence for transition #1 from state WffcToReadySleep */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrWffcToReadySleepSteps1[3] =
{
  COMM_HSM_COMM_AIDX_WAITFORFULLCOM_EXIT,
  COMM_HSM_COMM_AIDX_FULLCOMNOTIFIED_ENTRY,
  COMM_HSM_COMM_AIDX_READYSLEEPNM_ENTRY,
};
/* trans sequence for transition #1 from state NoPendingRequest */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrNoPendingRequestSteps1[1] =
{
  COMM_HSM_COMM_AIDX_PENDINGREQUEST_ENTRY,
};
/* trans sequence for transition #2 from state NoPendingRequest */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrNoPendingRequestSteps2[1] =
{
  COMM_HSM_COMM_AIDX_PENDINGREQUEST_ENTRY,
};
/* trans sequence for transition #3 from state NoPendingRequest */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrNoPendingRequestSteps3[1] =
{
  COMM_HSM_COMM_AIDX_PENDINGREQUEST_ENTRY,
};
/* trans sequence for transition #4 from state NoPendingRequest */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrNoPendingRequestSteps4[1] =
{
  COMM_HSM_COMM_AIDX_PENDINGREQUEST_ENTRY,
};
/* trans sequence for transition #1 from state WaitForNoCom */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrWaitForNoComSteps1[2] =
{
  COMM_HSM_COMM_AIDX_WAITFORNOCOM_EXIT,
  COMM_HSM_COMM_AIDX_NOCOMNOTIFED_ENTRY,
};
/* trans sequence for transition #2 from state WaitForNoCom */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrWaitForNoComSteps2[2] =
{
  COMM_HSM_COMM_AIDX_WAITFORNOCOM_EXIT,
  COMM_HSM_COMM_AIDX_WAITFORNOCOM_ENTRY,
};
/* trans sequence for transition #1 from state PendingRequest */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrPendingRequestSteps1[3] =
{
  COMM_HSM_COMM_AIDX_FULLCOMNOTIFIED_ENTRY,
  COMM_HSM_COMM_AIDX_ACCEPTLIMITTONOCOM_ENTRY,
  COMM_HSM_COMM_AIDX_NETREQNONM_ENTRY,
};
/* trans sequence for transition #1 from state ReqRunActive */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrReqRunActiveSteps1[1] =
{
  COMM_HSM_COMM_AIDX_WAITFORFULLCOM_ENTRY,
};
/* trans sequence for transition #1 from state ReqRunPassive */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrReqRunPassiveSteps1[1] =
{
  COMM_HSM_COMM_AIDX_WAITFORFULLCOM_ENTRY,
};
/* trans sequence for transition #1 from state SilentCom */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrSilentComSteps1[2] =
{
  COMM_HSM_COMM_AIDX_SILENTCOM_ACTION_1,
  COMM_HSM_COMM_AIDX_WAITFORNOCOM_ENTRY,
};
/* trans sequence for transition #2 from state SilentCom */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrSilentComSteps2[1] =
{
  COMM_HSM_COMM_AIDX_WAITFORFULLCOM_ENTRY,
};
/* trans sequence for transition #3 from state SilentCom */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrSilentComSteps3[1] =
{
  COMM_HSM_COMM_AIDX_WAITFORFULLCOM_ENTRY,
};
/* trans sequence for transition #1 from state WaitForSilentCom */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrWaitForSilentComSteps1[2] =
{
  COMM_HSM_COMM_AIDX_WAITFORSILENTCOM_EXIT,
  COMM_HSM_COMM_AIDX_SILENTCOMNOTIFED_ENTRY,
};
/* trans sequence for transition #2 from state WaitForSilentCom */
STATIC CONST(ComM_HsmActionIdxType, COMM_CONST)
  ComM_HsmTrWaitForSilentComSteps2[2] =
{
  COMM_HSM_COMM_AIDX_WAITFORSILENTCOM_EXIT,
  COMM_HSM_COMM_AIDX_WAITFORSILENTCOM_ENTRY,
};

#define COMM_STOP_SEC_CONST_8
#include <MemMap.h>

/* ****** */

#define COMM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* transitions from state FullCom */
STATIC CONST(ComM_HsmTranType, COMM_CONST)
 ComM_HsmTrFullCom[1] =
{
{
  NULL_PTR,
  0U,
  COMM_HSM_COMM_EV_NM_PREP_BUS_SLEEP_MODE, /* triggering event */
  COMM_HSM_GIDX_INVALID, /* no guard */
  COMM_HSM_COMM_SIDX_SILENTCOM /* target state */
},
};
/* transitions from state FullComNotified */
STATIC CONST(ComM_HsmTranType, COMM_CONST)
 ComM_HsmTrFullComNotified[1] =
{
{
  ComM_HsmTrFullComNotifiedSteps1,
  sizeof(ComM_HsmTrFullComNotifiedSteps1)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_NM_BUS_SLEEP_MODE, /* triggering event */
  COMM_HSM_GIDX_INVALID, /* no guard */
  COMM_HSM_COMM_SIDX_WAITFORNOCOM /* target state */
},
};
/* transitions from state AcceptLimitToNoCom */
STATIC CONST(ComM_HsmTranType, COMM_CONST)
 ComM_HsmTrAcceptLimitToNoCom[3] =
{
{
  ComM_HsmTrAcceptLimitToNoComSteps1,
  sizeof(ComM_HsmTrAcceptLimitToNoComSteps1)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_LIMIT_TO_NO_COM, /* triggering event */
  COMM_HSM_GIDX_INVALID, /* no guard */
  COMM_HSM_SIDX_INVALID /* no target state, internal transition */
},
{
  ComM_HsmTrAcceptLimitToNoComSteps2,
  sizeof(ComM_HsmTrAcceptLimitToNoComSteps2)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_BUSSM_MODE_IND_NO_COM, /* triggering event */
  COMM_HSM_COMM_GIDX_ACCEPTLIMITTONOCOM_GUARD_2, /* guard idx */
  COMM_HSM_COMM_SIDX_WAITFORFULLCOM /* target state */
},
{
  ComM_HsmTrAcceptLimitToNoComSteps3,
  sizeof(ComM_HsmTrAcceptLimitToNoComSteps3)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_BUSSM_MODE_IND_SILENT_COM, /* triggering event */
  COMM_HSM_COMM_GIDX_ACCEPTLIMITTONOCOM_GUARD_3, /* guard idx */
  COMM_HSM_COMM_SIDX_WAITFORFULLCOM /* target state */
},
};
/* transitions from state NetReqDelayedNoNm */
STATIC CONST(ComM_HsmTranType, COMM_CONST)
 ComM_HsmTrNetReqDelayedNoNm[3] =
{
{
  ComM_HsmTrNetReqDelayedNoNmSteps1,
  sizeof(ComM_HsmTrNetReqDelayedNoNmSteps1)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_REQ_STATUS_CHANGED, /* triggering event */
  COMM_HSM_COMM_GIDX_NETREQDELAYEDNONM_GUARD_1, /* guard idx */
  COMM_HSM_COMM_SIDX_NOCOMNOTIFED /* target state */
},
{
  ComM_HsmTrNetReqDelayedNoNmSteps2,
  sizeof(ComM_HsmTrNetReqDelayedNoNmSteps2)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_REQ_STATUS_CHANGED, /* triggering event */
  COMM_HSM_COMM_GIDX_NETREQDELAYEDNONM_GUARD_2, /* guard idx */
  COMM_HSM_COMM_SIDX_WAITFORNOCOM /* target state */
},
{
  ComM_HsmTrNetReqDelayedNoNmSteps3,
  sizeof(ComM_HsmTrNetReqDelayedNoNmSteps3)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_REQ_STATUS_CHANGED, /* triggering event */
  COMM_HSM_COMM_GIDX_NETREQDELAYEDNONM_GUARD_3, /* guard idx */
  COMM_HSM_COMM_SIDX_READYSLEEPNONM /* target state */
},
};
/* transitions from state NetReqNm */
STATIC CONST(ComM_HsmTranType, COMM_CONST)
 ComM_HsmTrNetReqNm[2] =
{
{
  ComM_HsmTrNetReqNmSteps1,
  sizeof(ComM_HsmTrNetReqNmSteps1)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_PNC_NM_REQUEST, /* triggering event */
  COMM_HSM_GIDX_INVALID, /* no guard */
  COMM_HSM_SIDX_INVALID /* no target state, internal transition */
},
{
  ComM_HsmTrNetReqNmSteps2,
  sizeof(ComM_HsmTrNetReqNmSteps2)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_REQ_STATUS_CHANGED, /* triggering event */
  COMM_HSM_COMM_GIDX_NETREQNM_GUARD_2, /* guard idx */
  COMM_HSM_COMM_SIDX_READYSLEEPNM /* target state */
},
};
/* transitions from state NetReqNoNm */
STATIC CONST(ComM_HsmTranType, COMM_CONST)
 ComM_HsmTrNetReqNoNm[1] =
{
{
  ComM_HsmTrNetReqNoNmSteps1,
  sizeof(ComM_HsmTrNetReqNoNmSteps1)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_TIMEOUT, /* triggering event */
  COMM_HSM_GIDX_INVALID, /* no guard */
  COMM_HSM_COMM_SIDX_NETREQDELAYEDNONM /* target state */
},
};
/* transitions from state ReadySleepNm */
STATIC CONST(ComM_HsmTranType, COMM_CONST)
 ComM_HsmTrReadySleepNm[1] =
{
{
  ComM_HsmTrReadySleepNmSteps1,
  sizeof(ComM_HsmTrReadySleepNmSteps1)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_REQ_STATUS_CHANGED, /* triggering event */
  COMM_HSM_COMM_GIDX_READYSLEEPNM_GUARD_1, /* guard idx */
  COMM_HSM_COMM_SIDX_NETREQNM /* target state */
},
};
/* transitions from state ReadySleepNoNm */
STATIC CONST(ComM_HsmTranType, COMM_CONST)
 ComM_HsmTrReadySleepNoNm[2] =
{
{
  ComM_HsmTrReadySleepNoNmSteps1,
  sizeof(ComM_HsmTrReadySleepNoNmSteps1)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_REQ_STATUS_CHANGED, /* triggering event */
  COMM_HSM_COMM_GIDX_READYSLEEPNONM_GUARD_1, /* guard idx */
  COMM_HSM_COMM_SIDX_NETREQNONM /* target state */
},
{
  ComM_HsmTrReadySleepNoNmSteps2,
  sizeof(ComM_HsmTrReadySleepNoNmSteps2)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_TIMEOUT, /* triggering event */
  COMM_HSM_GIDX_INVALID, /* no guard */
  COMM_HSM_COMM_SIDX_WAITFORNOCOM /* target state */
},
};
/* transitions from state PassiveStartupWait */
STATIC CONST(ComM_HsmTranType, COMM_CONST)
 ComM_HsmTrPassiveStartupWait[4] =
{
{
  ComM_HsmTrPassiveStartupWaitSteps1,
  sizeof(ComM_HsmTrPassiveStartupWaitSteps1)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_NM_NETWORK_MODE, /* triggering event */
  COMM_HSM_COMM_GIDX_PASSIVESTARTUPWAIT_GUARD_1, /* guard idx */
  COMM_HSM_COMM_SIDX_NETREQNM /* target state */
},
{
  ComM_HsmTrPassiveStartupWaitSteps2,
  sizeof(ComM_HsmTrPassiveStartupWaitSteps2)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_NM_NETWORK_MODE, /* triggering event */
  COMM_HSM_COMM_GIDX_PASSIVESTARTUPWAIT_GUARD_2, /* guard idx */
  COMM_HSM_COMM_SIDX_NETREQNM /* target state */
},
{
  ComM_HsmTrPassiveStartupWaitSteps3,
  sizeof(ComM_HsmTrPassiveStartupWaitSteps3)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_NM_NETWORK_MODE, /* triggering event */
  COMM_HSM_GIDX_INVALID, /* no guard */
  COMM_HSM_COMM_SIDX_READYSLEEPNM /* target state */
},
{
  ComM_HsmTrPassiveStartupWaitSteps4,
  sizeof(ComM_HsmTrPassiveStartupWaitSteps4)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_NM_TIMEOUT, /* triggering event */
  COMM_HSM_GIDX_INVALID, /* no guard */
  COMM_HSM_COMM_SIDX_PASSIVESTARTUPWAIT /* target state */
},
};
/* transitions from state ReqNetworkWait */
STATIC CONST(ComM_HsmTranType, COMM_CONST)
 ComM_HsmTrReqNetworkWait[2] =
{
{
  ComM_HsmTrReqNetworkWaitSteps1,
  sizeof(ComM_HsmTrReqNetworkWaitSteps1)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_NM_NETWORK_MODE, /* triggering event */
  COMM_HSM_GIDX_INVALID, /* no guard */
  COMM_HSM_COMM_SIDX_NETREQNM /* target state */
},
{
  ComM_HsmTrReqNetworkWaitSteps2,
  sizeof(ComM_HsmTrReqNetworkWaitSteps2)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_NM_TIMEOUT, /* triggering event */
  COMM_HSM_GIDX_INVALID, /* no guard */
  COMM_HSM_COMM_SIDX_REQNETWORKWAIT /* target state */
},
};
/* transitions from state WaitForFullCom */
STATIC CONST(ComM_HsmTranType, COMM_CONST)
 ComM_HsmTrWaitForFullCom[3] =
{
{
  ComM_HsmTrWaitForFullComSteps1,
  sizeof(ComM_HsmTrWaitForFullComSteps1)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_BUSSM_TIMEOUT, /* triggering event */
  COMM_HSM_GIDX_INVALID, /* no guard */
  COMM_HSM_SIDX_INVALID /* no target state, internal transition */
},
{
  ComM_HsmTrWaitForFullComSteps2,
  sizeof(ComM_HsmTrWaitForFullComSteps2)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_BUSSM_RETRY_COUNT_LIMIT, /* triggering event */
  COMM_HSM_GIDX_INVALID, /* no guard */
  COMM_HSM_COMM_SIDX_WAITFORNOCOM /* target state */
},
{
  ComM_HsmTrWaitForFullComSteps3,
  sizeof(ComM_HsmTrWaitForFullComSteps3)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_REQ_STATUS_CHANGED, /* triggering event */
  COMM_HSM_COMM_GIDX_WAITFORFULLCOM_GUARD_3, /* guard idx */
  COMM_HSM_COMM_SIDX_WAITFORNOCOM /* target state */
},
};
/* transitions from state WffcToNetReq */
STATIC CONST(ComM_HsmTranType, COMM_CONST)
 ComM_HsmTrWffcToNetReq[1] =
{
{
  ComM_HsmTrWffcToNetReqSteps1,
  sizeof(ComM_HsmTrWffcToNetReqSteps1)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_BUSSM_MODE_IND_FULL_COM, /* triggering event */
  COMM_HSM_GIDX_INVALID, /* no guard */
  COMM_HSM_COMM_SIDX_NETREQNONM /* target state */
},
};
/* transitions from state WffcToNetReqActive */
STATIC CONST(ComM_HsmTranType, COMM_CONST)
 ComM_HsmTrWffcToNetReqActive[1] =
{
{
  ComM_HsmTrWffcToNetReqActiveSteps1,
  sizeof(ComM_HsmTrWffcToNetReqActiveSteps1)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_BUSSM_MODE_IND_FULL_COM, /* triggering event */
  COMM_HSM_COMM_GIDX_WFFCTONETREQACTIVE_GUARD_1, /* guard idx */
  COMM_HSM_COMM_SIDX_REQNETWORKWAIT /* target state */
},
};
/* transitions from state WffcToNetReqPassive */
STATIC CONST(ComM_HsmTranType, COMM_CONST)
 ComM_HsmTrWffcToNetReqPassive[1] =
{
{
  ComM_HsmTrWffcToNetReqPassiveSteps1,
  sizeof(ComM_HsmTrWffcToNetReqPassiveSteps1)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_BUSSM_MODE_IND_FULL_COM, /* triggering event */
  COMM_HSM_COMM_GIDX_WFFCTONETREQPASSIVE_GUARD_1, /* guard idx */
  COMM_HSM_COMM_SIDX_PASSIVESTARTUPWAIT /* target state */
},
};
/* transitions from state WffcToReadySleep */
STATIC CONST(ComM_HsmTranType, COMM_CONST)
 ComM_HsmTrWffcToReadySleep[1] =
{
{
  ComM_HsmTrWffcToReadySleepSteps1,
  sizeof(ComM_HsmTrWffcToReadySleepSteps1)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_BUSSM_MODE_IND_FULL_COM, /* triggering event */
  COMM_HSM_GIDX_INVALID, /* no guard */
  COMM_HSM_COMM_SIDX_READYSLEEPNM /* target state */
},
};
/* transitions from state NoPendingRequest */
STATIC CONST(ComM_HsmTranType, COMM_CONST)
 ComM_HsmTrNoPendingRequest[4] =
{
{
  ComM_HsmTrNoPendingRequestSteps1,
  sizeof(ComM_HsmTrNoPendingRequestSteps1)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_ECUM_WAKEUP_IND, /* triggering event */
  COMM_HSM_GIDX_INVALID, /* no guard */
  COMM_HSM_COMM_SIDX_REQRUNPASSIVE /* target state */
},
{
  ComM_HsmTrNoPendingRequestSteps2,
  sizeof(ComM_HsmTrNoPendingRequestSteps2)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_NM_NETWORK_START_INDICATION, /* triggering event */
  COMM_HSM_GIDX_INVALID, /* no guard */
  COMM_HSM_COMM_SIDX_REQRUNPASSIVE /* target state */
},
{
  ComM_HsmTrNoPendingRequestSteps3,
  sizeof(ComM_HsmTrNoPendingRequestSteps3)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_NM_RESTART_IND, /* triggering event */
  COMM_HSM_GIDX_INVALID, /* no guard */
  COMM_HSM_COMM_SIDX_REQRUNPASSIVE /* target state */
},
{
  ComM_HsmTrNoPendingRequestSteps4,
  sizeof(ComM_HsmTrNoPendingRequestSteps4)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_REQ_STATUS_CHANGED, /* triggering event */
  COMM_HSM_COMM_GIDX_NOPENDINGREQUEST_GUARD_4, /* guard idx */
  COMM_HSM_COMM_SIDX_REQRUNACTIVE /* target state */
},
};
/* transitions from state WaitForNoCom */
STATIC CONST(ComM_HsmTranType, COMM_CONST)
 ComM_HsmTrWaitForNoCom[2] =
{
{
  ComM_HsmTrWaitForNoComSteps1,
  sizeof(ComM_HsmTrWaitForNoComSteps1)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_BUSSM_MODE_IND_NO_COM, /* triggering event */
  COMM_HSM_GIDX_INVALID, /* no guard */
  COMM_HSM_COMM_SIDX_NOCOMNOTIFED /* target state */
},
{
  ComM_HsmTrWaitForNoComSteps2,
  sizeof(ComM_HsmTrWaitForNoComSteps2)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_BUSSM_TIMEOUT, /* triggering event */
  COMM_HSM_GIDX_INVALID, /* no guard */
  COMM_HSM_COMM_SIDX_WAITFORNOCOM /* target state */
},
};
/* transitions from state PendingRequest */
STATIC CONST(ComM_HsmTranType, COMM_CONST)
 ComM_HsmTrPendingRequest[1] =
{
{
  ComM_HsmTrPendingRequestSteps1,
  sizeof(ComM_HsmTrPendingRequestSteps1)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_COMALLOWED_CHANGED, /* triggering event */
  COMM_HSM_COMM_GIDX_PENDINGREQUEST_GUARD_1, /* guard idx */
  COMM_HSM_COMM_SIDX_NETREQNONM /* target state */
},
};
/* transitions from state ReqRunActive */
STATIC CONST(ComM_HsmTranType, COMM_CONST)
 ComM_HsmTrReqRunActive[2] =
{
{
  ComM_HsmTrReqRunActiveSteps1,
  sizeof(ComM_HsmTrReqRunActiveSteps1)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_COMALLOWED_CHANGED, /* triggering event */
  COMM_HSM_COMM_GIDX_REQRUNACTIVE_GUARD_1, /* guard idx */
  COMM_HSM_COMM_SIDX_WFFCTONETREQACTIVE /* target state */
},
{
  NULL_PTR,
  0U,
  COMM_HSM_COMM_EV_REQ_STATUS_CHANGED, /* triggering event */
  COMM_HSM_COMM_GIDX_REQRUNACTIVE_GUARD_2, /* guard idx */
  COMM_HSM_COMM_SIDX_NOPENDINGREQUEST /* target state */
},
};
/* transitions from state ReqRunPassive */
STATIC CONST(ComM_HsmTranType, COMM_CONST)
 ComM_HsmTrReqRunPassive[1] =
{
{
  ComM_HsmTrReqRunPassiveSteps1,
  sizeof(ComM_HsmTrReqRunPassiveSteps1)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_COMALLOWED_CHANGED, /* triggering event */
  COMM_HSM_COMM_GIDX_REQRUNPASSIVE_GUARD_1, /* guard idx */
  COMM_HSM_COMM_SIDX_WFFCTONETREQPASSIVE /* target state */
},
};
/* transitions from state SilentCom */
STATIC CONST(ComM_HsmTranType, COMM_CONST)
 ComM_HsmTrSilentCom[3] =
{
{
  ComM_HsmTrSilentComSteps1,
  sizeof(ComM_HsmTrSilentComSteps1)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_NM_BUS_SLEEP_MODE, /* triggering event */
  COMM_HSM_GIDX_INVALID, /* no guard */
  COMM_HSM_COMM_SIDX_WAITFORNOCOM /* target state */
},
{
  ComM_HsmTrSilentComSteps2,
  sizeof(ComM_HsmTrSilentComSteps2)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_NM_NETWORK_MODE, /* triggering event */
  COMM_HSM_GIDX_INVALID, /* no guard */
  COMM_HSM_COMM_SIDX_WFFCTOREADYSLEEP /* target state */
},
{
  ComM_HsmTrSilentComSteps3,
  sizeof(ComM_HsmTrSilentComSteps3)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_REQ_STATUS_CHANGED, /* triggering event */
  COMM_HSM_COMM_GIDX_SILENTCOM_GUARD_3, /* guard idx */
  COMM_HSM_COMM_SIDX_WFFCTONETREQACTIVE /* target state */
},
};
/* transitions from state WaitForSilentCom */
STATIC CONST(ComM_HsmTranType, COMM_CONST)
 ComM_HsmTrWaitForSilentCom[2] =
{
{
  ComM_HsmTrWaitForSilentComSteps1,
  sizeof(ComM_HsmTrWaitForSilentComSteps1)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_BUSSM_MODE_IND_SILENT_COM, /* triggering event */
  COMM_HSM_GIDX_INVALID, /* no guard */
  COMM_HSM_COMM_SIDX_SILENTCOMNOTIFED /* target state */
},
{
  ComM_HsmTrWaitForSilentComSteps2,
  sizeof(ComM_HsmTrWaitForSilentComSteps2)/sizeof(ComM_HsmActionIdxType),
  COMM_HSM_COMM_EV_BUSSM_TIMEOUT, /* triggering event */
  COMM_HSM_GIDX_INVALID, /* no guard */
  COMM_HSM_COMM_SIDX_WAITFORSILENTCOM /* target state */
},
};



/* statechart model description of the ComM state
 * machine */
STATIC CONST(ComM_HsmStateType, COMM_CONST)
  ComM_HsmScdComM[COMM_HSM_COMM_NO_OF_STATES] =
{
  {
    /* description of state TOP */
    0U, /* no non-deferred event mask (no leaf state) */
    0U, /* no ignored event mask (no leaf state) */
    NULL_PTR,  /* no transitions */
    COMM_HSM_SIDX_INVALID, /* no parent state */
    COMM_HSM_COMM_SIDX_NOCOM, /* init state */
      COMM_HSM_AIDX_INVALID, /* no entry action */
    COMM_HSM_AIDX_INVALID, /* no exit action */
    COMM_HSM_AIDX_INVALID, /* no do action */
    0U  /* no transitions */
  },
  {
    /* description of state FullCom */
    0U, /* no non-deferred event mask (no leaf state) */
    0U, /* no ignored event mask (no leaf state) */
    ComM_HsmTrFullCom, /* transitions for this state */
    COMM_HSM_COMM_SIDX_TOP, /* parent state */
    COMM_HSM_COMM_SIDX_FULLCOMNOTIFIED, /* init state */
      COMM_HSM_AIDX_INVALID, /* no entry action */
    COMM_HSM_AIDX_INVALID, /* no exit action */
    COMM_HSM_AIDX_INVALID, /* no do action */
    1 /* num of transitions */
  },
  {
    /* description of state FullComNotified */
    0U, /* no non-deferred event mask (no leaf state) */
    0U, /* no ignored event mask (no leaf state) */
    ComM_HsmTrFullComNotified, /* transitions for this state */
    COMM_HSM_COMM_SIDX_FULLCOM, /* parent state */
    COMM_HSM_COMM_SIDX_ACCEPTLIMITTONOCOM, /* init state */
      COMM_HSM_COMM_AIDX_FULLCOMNOTIFIED_ENTRY, /* entry function */
    COMM_HSM_AIDX_INVALID, /* no exit action */
    COMM_HSM_AIDX_INVALID, /* no do action */
    1 /* num of transitions */
  },
  {
    /* description of state AcceptLimitToNoCom */
    0U, /* no non-deferred event mask (no leaf state) */
    0U, /* no ignored event mask (no leaf state) */
    ComM_HsmTrAcceptLimitToNoCom, /* transitions for this state */
    COMM_HSM_COMM_SIDX_FULLCOMNOTIFIED, /* parent state */
    COMM_HSM_COMM_SIDX_NETREQNM, /* init state */
      COMM_HSM_COMM_AIDX_ACCEPTLIMITTONOCOM_ENTRY, /* entry function */
    COMM_HSM_AIDX_INVALID, /* no exit action */
    COMM_HSM_AIDX_INVALID, /* no do action */
    3 /* num of transitions */
  },
  {
    /* description of state NetReqDelayedNoNm */
    /* non-deferred and non-ignored event mask */
   (1UL << COMM_HSM_COMM_EV_LIMIT_TO_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_NM_PREP_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_NM_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_REQ_STATUS_CHANGED)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_SILENT_COM)
    | 0UL
    ,
      /* ignored event mask */
   (1UL << COMM_HSM_COMM_EV_PNC_NM_REQUEST)
    |   (1UL << COMM_HSM_COMM_EV_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_NM_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_RETRY_COUNT_LIMIT)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_FULL_COM)
    |   (1UL << COMM_HSM_COMM_EV_ECUM_WAKEUP_IND)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_START_INDICATION)
    |   (1UL << COMM_HSM_COMM_EV_NM_RESTART_IND)
    |   (1UL << COMM_HSM_COMM_EV_COMALLOWED_CHANGED)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_MODE)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_TIMEOUT)
    | 0UL
    ,
    ComM_HsmTrNetReqDelayedNoNm, /* transitions for this state */
    COMM_HSM_COMM_SIDX_ACCEPTLIMITTONOCOM, /* parent state */
    COMM_HSM_SIDX_INVALID, /* no init state */
      COMM_HSM_COMM_AIDX_NETREQDELAYEDNONM_ENTRY, /* entry function */
    COMM_HSM_AIDX_INVALID, /* no exit action */
    COMM_HSM_AIDX_INVALID, /* no do action */
    3 /* num of transitions */
  },
  {
    /* description of state NetReqNm */
    /* non-deferred and non-ignored event mask */
   (1UL << COMM_HSM_COMM_EV_LIMIT_TO_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_PNC_NM_REQUEST)
    |   (1UL << COMM_HSM_COMM_EV_NM_PREP_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_NM_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_REQ_STATUS_CHANGED)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_SILENT_COM)
    | 0UL
    ,
      /* ignored event mask */
   (1UL << COMM_HSM_COMM_EV_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_NM_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_RETRY_COUNT_LIMIT)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_FULL_COM)
    |   (1UL << COMM_HSM_COMM_EV_ECUM_WAKEUP_IND)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_START_INDICATION)
    |   (1UL << COMM_HSM_COMM_EV_NM_RESTART_IND)
    |   (1UL << COMM_HSM_COMM_EV_COMALLOWED_CHANGED)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_MODE)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_TIMEOUT)
    | 0UL
    ,
    ComM_HsmTrNetReqNm, /* transitions for this state */
    COMM_HSM_COMM_SIDX_ACCEPTLIMITTONOCOM, /* parent state */
    COMM_HSM_SIDX_INVALID, /* no init state */
      COMM_HSM_AIDX_INVALID, /* no entry action */
    COMM_HSM_AIDX_INVALID, /* no exit action */
    COMM_HSM_AIDX_INVALID, /* no do action */
    2 /* num of transitions */
  },
  {
    /* description of state NetReqNoNm */
    /* non-deferred and non-ignored event mask */
   (1UL << COMM_HSM_COMM_EV_LIMIT_TO_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_NM_PREP_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_NM_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_SILENT_COM)
    | 0UL
    ,
      /* ignored event mask */
   (1UL << COMM_HSM_COMM_EV_PNC_NM_REQUEST)
    |   (1UL << COMM_HSM_COMM_EV_NM_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_RETRY_COUNT_LIMIT)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_FULL_COM)
    |   (1UL << COMM_HSM_COMM_EV_ECUM_WAKEUP_IND)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_START_INDICATION)
    |   (1UL << COMM_HSM_COMM_EV_NM_RESTART_IND)
    |   (1UL << COMM_HSM_COMM_EV_COMALLOWED_CHANGED)
    |   (1UL << COMM_HSM_COMM_EV_REQ_STATUS_CHANGED)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_MODE)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_TIMEOUT)
    | 0UL
    ,
    ComM_HsmTrNetReqNoNm, /* transitions for this state */
    COMM_HSM_COMM_SIDX_ACCEPTLIMITTONOCOM, /* parent state */
    COMM_HSM_SIDX_INVALID, /* no init state */
      COMM_HSM_COMM_AIDX_NETREQNONM_ENTRY, /* entry function */
    COMM_HSM_AIDX_INVALID, /* no exit action */
    COMM_HSM_AIDX_INVALID, /* no do action */
    1 /* num of transitions */
  },
  {
    /* description of state ReadySleepNm */
    /* non-deferred and non-ignored event mask */
   (1UL << COMM_HSM_COMM_EV_NM_PREP_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_NM_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_REQ_STATUS_CHANGED)
    | 0UL
    ,
      /* ignored event mask */
   (1UL << COMM_HSM_COMM_EV_LIMIT_TO_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_PNC_NM_REQUEST)
    |   (1UL << COMM_HSM_COMM_EV_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_NM_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_RETRY_COUNT_LIMIT)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_FULL_COM)
    |   (1UL << COMM_HSM_COMM_EV_ECUM_WAKEUP_IND)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_START_INDICATION)
    |   (1UL << COMM_HSM_COMM_EV_NM_RESTART_IND)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_COMALLOWED_CHANGED)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_MODE)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_SILENT_COM)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_TIMEOUT)
    | 0UL
    ,
    ComM_HsmTrReadySleepNm, /* transitions for this state */
    COMM_HSM_COMM_SIDX_FULLCOMNOTIFIED, /* parent state */
    COMM_HSM_SIDX_INVALID, /* no init state */
      COMM_HSM_COMM_AIDX_READYSLEEPNM_ENTRY, /* entry function */
    COMM_HSM_AIDX_INVALID, /* no exit action */
    COMM_HSM_AIDX_INVALID, /* no do action */
    1 /* num of transitions */
  },
  {
    /* description of state ReadySleepNoNm */
    /* non-deferred and non-ignored event mask */
   (1UL << COMM_HSM_COMM_EV_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_NM_PREP_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_NM_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_REQ_STATUS_CHANGED)
    | 0UL
    ,
      /* ignored event mask */
   (1UL << COMM_HSM_COMM_EV_LIMIT_TO_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_PNC_NM_REQUEST)
    |   (1UL << COMM_HSM_COMM_EV_NM_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_RETRY_COUNT_LIMIT)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_FULL_COM)
    |   (1UL << COMM_HSM_COMM_EV_ECUM_WAKEUP_IND)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_START_INDICATION)
    |   (1UL << COMM_HSM_COMM_EV_NM_RESTART_IND)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_COMALLOWED_CHANGED)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_MODE)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_SILENT_COM)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_TIMEOUT)
    | 0UL
    ,
    ComM_HsmTrReadySleepNoNm, /* transitions for this state */
    COMM_HSM_COMM_SIDX_FULLCOMNOTIFIED, /* parent state */
    COMM_HSM_SIDX_INVALID, /* no init state */
      COMM_HSM_COMM_AIDX_READYSLEEPNONM_ENTRY, /* entry function */
    COMM_HSM_AIDX_INVALID, /* no exit action */
    COMM_HSM_AIDX_INVALID, /* no do action */
    2 /* num of transitions */
  },
  {
    /* description of state PassiveStartupWait */
    /* non-deferred and non-ignored event mask */
   (1UL << COMM_HSM_COMM_EV_NM_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_NM_PREP_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_MODE)
    | 0UL
    ,
      /* ignored event mask */
   (1UL << COMM_HSM_COMM_EV_LIMIT_TO_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_PNC_NM_REQUEST)
    |   (1UL << COMM_HSM_COMM_EV_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_RETRY_COUNT_LIMIT)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_FULL_COM)
    |   (1UL << COMM_HSM_COMM_EV_ECUM_WAKEUP_IND)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_START_INDICATION)
    |   (1UL << COMM_HSM_COMM_EV_NM_RESTART_IND)
    |   (1UL << COMM_HSM_COMM_EV_COMALLOWED_CHANGED)
    |   (1UL << COMM_HSM_COMM_EV_NM_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_REQ_STATUS_CHANGED)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_TIMEOUT)
    | 0UL
    ,
    ComM_HsmTrPassiveStartupWait, /* transitions for this state */
    COMM_HSM_COMM_SIDX_FULLCOM, /* parent state */
    COMM_HSM_SIDX_INVALID, /* no init state */
      COMM_HSM_COMM_AIDX_PASSIVESTARTUPWAIT_ENTRY, /* entry function */
    COMM_HSM_COMM_AIDX_PASSIVESTARTUPWAIT_EXIT, /* exit function */
    COMM_HSM_AIDX_INVALID, /* no do action */
    4 /* num of transitions */
  },
  {
    /* description of state ReqNetworkWait */
    /* non-deferred and non-ignored event mask */
   (1UL << COMM_HSM_COMM_EV_NM_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_NM_PREP_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_MODE)
    | 0UL
    ,
      /* ignored event mask */
   (1UL << COMM_HSM_COMM_EV_LIMIT_TO_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_PNC_NM_REQUEST)
    |   (1UL << COMM_HSM_COMM_EV_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_RETRY_COUNT_LIMIT)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_FULL_COM)
    |   (1UL << COMM_HSM_COMM_EV_ECUM_WAKEUP_IND)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_START_INDICATION)
    |   (1UL << COMM_HSM_COMM_EV_NM_RESTART_IND)
    |   (1UL << COMM_HSM_COMM_EV_COMALLOWED_CHANGED)
    |   (1UL << COMM_HSM_COMM_EV_NM_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_REQ_STATUS_CHANGED)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_TIMEOUT)
    | 0UL
    ,
    ComM_HsmTrReqNetworkWait, /* transitions for this state */
    COMM_HSM_COMM_SIDX_FULLCOM, /* parent state */
    COMM_HSM_SIDX_INVALID, /* no init state */
      COMM_HSM_COMM_AIDX_REQNETWORKWAIT_ENTRY, /* entry function */
    COMM_HSM_COMM_AIDX_REQNETWORKWAIT_EXIT, /* exit function */
    COMM_HSM_AIDX_INVALID, /* no do action */
    2 /* num of transitions */
  },
  {
    /* description of state WaitForFullCom */
    0U, /* no non-deferred event mask (no leaf state) */
    0U, /* no ignored event mask (no leaf state) */
    ComM_HsmTrWaitForFullCom, /* transitions for this state */
    COMM_HSM_COMM_SIDX_FULLCOM, /* parent state */
    COMM_HSM_COMM_SIDX_WFFCTONETREQ, /* init state */
      COMM_HSM_COMM_AIDX_WAITFORFULLCOM_ENTRY, /* entry function */
    COMM_HSM_COMM_AIDX_WAITFORFULLCOM_EXIT, /* exit function */
    COMM_HSM_AIDX_INVALID, /* no do action */
    3 /* num of transitions */
  },
  {
    /* description of state WffcToNetReq */
    0U, /* no non-deferred event mask (no leaf state) */
    0U, /* no ignored event mask (no leaf state) */
    ComM_HsmTrWffcToNetReq, /* transitions for this state */
    COMM_HSM_COMM_SIDX_WAITFORFULLCOM, /* parent state */
    COMM_HSM_COMM_SIDX_WFFCTONETREQACTIVE, /* init state */
      COMM_HSM_AIDX_INVALID, /* no entry action */
    COMM_HSM_AIDX_INVALID, /* no exit action */
    COMM_HSM_AIDX_INVALID, /* no do action */
    1 /* num of transitions */
  },
  {
    /* description of state WffcToNetReqActive */
    /* non-deferred and non-ignored event mask */
   (1UL << COMM_HSM_COMM_EV_BUSSM_RETRY_COUNT_LIMIT)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_FULL_COM)
    |   (1UL << COMM_HSM_COMM_EV_REQ_STATUS_CHANGED)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_TIMEOUT)
    | 0UL
    ,
      /* ignored event mask */
   (1UL << COMM_HSM_COMM_EV_LIMIT_TO_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_PNC_NM_REQUEST)
    |   (1UL << COMM_HSM_COMM_EV_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_NM_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_NM_PREP_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_ECUM_WAKEUP_IND)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_START_INDICATION)
    |   (1UL << COMM_HSM_COMM_EV_NM_RESTART_IND)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_COMALLOWED_CHANGED)
    |   (1UL << COMM_HSM_COMM_EV_NM_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_MODE)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_SILENT_COM)
    | 0UL
    ,
    ComM_HsmTrWffcToNetReqActive, /* transitions for this state */
    COMM_HSM_COMM_SIDX_WFFCTONETREQ, /* parent state */
    COMM_HSM_SIDX_INVALID, /* no init state */
      COMM_HSM_AIDX_INVALID, /* no entry action */
    COMM_HSM_AIDX_INVALID, /* no exit action */
    COMM_HSM_AIDX_INVALID, /* no do action */
    1 /* num of transitions */
  },
  {
    /* description of state WffcToNetReqPassive */
    /* non-deferred and non-ignored event mask */
   (1UL << COMM_HSM_COMM_EV_BUSSM_RETRY_COUNT_LIMIT)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_FULL_COM)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_TIMEOUT)
    | 0UL
    ,
      /* ignored event mask */
   (1UL << COMM_HSM_COMM_EV_LIMIT_TO_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_PNC_NM_REQUEST)
    |   (1UL << COMM_HSM_COMM_EV_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_NM_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_NM_PREP_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_ECUM_WAKEUP_IND)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_START_INDICATION)
    |   (1UL << COMM_HSM_COMM_EV_NM_RESTART_IND)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_COMALLOWED_CHANGED)
    |   (1UL << COMM_HSM_COMM_EV_NM_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_REQ_STATUS_CHANGED)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_MODE)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_SILENT_COM)
    | 0UL
    ,
    ComM_HsmTrWffcToNetReqPassive, /* transitions for this state */
    COMM_HSM_COMM_SIDX_WFFCTONETREQ, /* parent state */
    COMM_HSM_SIDX_INVALID, /* no init state */
      COMM_HSM_AIDX_INVALID, /* no entry action */
    COMM_HSM_AIDX_INVALID, /* no exit action */
    COMM_HSM_AIDX_INVALID, /* no do action */
    1 /* num of transitions */
  },
  {
    /* description of state WffcToReadySleep */
    /* non-deferred and non-ignored event mask */
   (1UL << COMM_HSM_COMM_EV_BUSSM_RETRY_COUNT_LIMIT)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_FULL_COM)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_TIMEOUT)
    | 0UL
    ,
      /* ignored event mask */
   (1UL << COMM_HSM_COMM_EV_LIMIT_TO_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_PNC_NM_REQUEST)
    |   (1UL << COMM_HSM_COMM_EV_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_NM_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_NM_PREP_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_ECUM_WAKEUP_IND)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_START_INDICATION)
    |   (1UL << COMM_HSM_COMM_EV_NM_RESTART_IND)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_COMALLOWED_CHANGED)
    |   (1UL << COMM_HSM_COMM_EV_NM_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_REQ_STATUS_CHANGED)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_MODE)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_SILENT_COM)
    | 0UL
    ,
    ComM_HsmTrWffcToReadySleep, /* transitions for this state */
    COMM_HSM_COMM_SIDX_WAITFORFULLCOM, /* parent state */
    COMM_HSM_SIDX_INVALID, /* no init state */
      COMM_HSM_AIDX_INVALID, /* no entry action */
    COMM_HSM_AIDX_INVALID, /* no exit action */
    COMM_HSM_AIDX_INVALID, /* no do action */
    1 /* num of transitions */
  },
  {
    /* description of state NoCom */
    0U, /* no non-deferred event mask (no leaf state) */
    0U, /* no ignored event mask (no leaf state) */
    NULL_PTR,  /* no transitions */
    COMM_HSM_COMM_SIDX_TOP, /* parent state */
    COMM_HSM_COMM_SIDX_NOPENDINGREQUEST, /* init state */
      COMM_HSM_AIDX_INVALID, /* no entry action */
    COMM_HSM_AIDX_INVALID, /* no exit action */
    COMM_HSM_AIDX_INVALID, /* no do action */
    0U  /* no transitions */
  },
  {
    /* description of state NoPendingRequest */
    0U, /* no non-deferred event mask (no leaf state) */
    0U, /* no ignored event mask (no leaf state) */
    ComM_HsmTrNoPendingRequest, /* transitions for this state */
    COMM_HSM_COMM_SIDX_NOCOM, /* parent state */
    COMM_HSM_COMM_SIDX_NOCOMFIRST, /* init state */
      COMM_HSM_AIDX_INVALID, /* no entry action */
    COMM_HSM_AIDX_INVALID, /* no exit action */
    COMM_HSM_AIDX_INVALID, /* no do action */
    4 /* num of transitions */
  },
  {
    /* description of state NoComFirst */
    /* non-deferred and non-ignored event mask */
   (1UL << COMM_HSM_COMM_EV_ECUM_WAKEUP_IND)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_START_INDICATION)
    |   (1UL << COMM_HSM_COMM_EV_NM_RESTART_IND)
    |   (1UL << COMM_HSM_COMM_EV_REQ_STATUS_CHANGED)
    | 0UL
    ,
      /* ignored event mask */
   (1UL << COMM_HSM_COMM_EV_LIMIT_TO_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_PNC_NM_REQUEST)
    |   (1UL << COMM_HSM_COMM_EV_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_NM_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_NM_PREP_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_RETRY_COUNT_LIMIT)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_FULL_COM)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_COMALLOWED_CHANGED)
    |   (1UL << COMM_HSM_COMM_EV_NM_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_MODE)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_SILENT_COM)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_TIMEOUT)
    | 0UL
    ,
    NULL_PTR,  /* no transitions */
    COMM_HSM_COMM_SIDX_NOPENDINGREQUEST, /* parent state */
    COMM_HSM_SIDX_INVALID, /* no init state */
      COMM_HSM_COMM_AIDX_NOCOMFIRST_ENTRY, /* entry function */
    COMM_HSM_AIDX_INVALID, /* no exit action */
    COMM_HSM_AIDX_INVALID, /* no do action */
    0U  /* no transitions */
  },
  {
    /* description of state NoComNotifed */
    /* non-deferred and non-ignored event mask */
   (1UL << COMM_HSM_COMM_EV_ECUM_WAKEUP_IND)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_START_INDICATION)
    |   (1UL << COMM_HSM_COMM_EV_NM_RESTART_IND)
    |   (1UL << COMM_HSM_COMM_EV_REQ_STATUS_CHANGED)
    | 0UL
    ,
      /* ignored event mask */
   (1UL << COMM_HSM_COMM_EV_LIMIT_TO_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_PNC_NM_REQUEST)
    |   (1UL << COMM_HSM_COMM_EV_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_NM_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_NM_PREP_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_RETRY_COUNT_LIMIT)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_FULL_COM)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_COMALLOWED_CHANGED)
    |   (1UL << COMM_HSM_COMM_EV_NM_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_MODE)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_SILENT_COM)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_TIMEOUT)
    | 0UL
    ,
    NULL_PTR,  /* no transitions */
    COMM_HSM_COMM_SIDX_NOPENDINGREQUEST, /* parent state */
    COMM_HSM_SIDX_INVALID, /* no init state */
      COMM_HSM_COMM_AIDX_NOCOMNOTIFED_ENTRY, /* entry function */
    COMM_HSM_AIDX_INVALID, /* no exit action */
    COMM_HSM_AIDX_INVALID, /* no do action */
    0U  /* no transitions */
  },
  {
    /* description of state WaitForNoCom */
    /* non-deferred and non-ignored event mask */
   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_TIMEOUT)
    | 0UL
    ,
      /* ignored event mask */
   (1UL << COMM_HSM_COMM_EV_LIMIT_TO_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_PNC_NM_REQUEST)
    |   (1UL << COMM_HSM_COMM_EV_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_NM_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_NM_PREP_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_RETRY_COUNT_LIMIT)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_FULL_COM)
    |   (1UL << COMM_HSM_COMM_EV_COMALLOWED_CHANGED)
    |   (1UL << COMM_HSM_COMM_EV_NM_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_MODE)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_SILENT_COM)
    | 0UL
    ,
    ComM_HsmTrWaitForNoCom, /* transitions for this state */
    COMM_HSM_COMM_SIDX_NOPENDINGREQUEST, /* parent state */
    COMM_HSM_SIDX_INVALID, /* no init state */
      COMM_HSM_COMM_AIDX_WAITFORNOCOM_ENTRY, /* entry function */
    COMM_HSM_COMM_AIDX_WAITFORNOCOM_EXIT, /* exit function */
    COMM_HSM_AIDX_INVALID, /* no do action */
    2 /* num of transitions */
  },
  {
    /* description of state PendingRequest */
    0U, /* no non-deferred event mask (no leaf state) */
    0U, /* no ignored event mask (no leaf state) */
    ComM_HsmTrPendingRequest, /* transitions for this state */
    COMM_HSM_COMM_SIDX_NOCOM, /* parent state */
    COMM_HSM_COMM_SIDX_REQRUNPASSIVE, /* init state */
      COMM_HSM_COMM_AIDX_PENDINGREQUEST_ENTRY, /* entry function */
    COMM_HSM_AIDX_INVALID, /* no exit action */
    COMM_HSM_AIDX_INVALID, /* no do action */
    1 /* num of transitions */
  },
  {
    /* description of state ReqRunActive */
    /* non-deferred and non-ignored event mask */
   (1UL << COMM_HSM_COMM_EV_COMALLOWED_CHANGED)
    |   (1UL << COMM_HSM_COMM_EV_REQ_STATUS_CHANGED)
    | 0UL
    ,
      /* ignored event mask */
   (1UL << COMM_HSM_COMM_EV_LIMIT_TO_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_PNC_NM_REQUEST)
    |   (1UL << COMM_HSM_COMM_EV_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_NM_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_NM_PREP_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_RETRY_COUNT_LIMIT)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_FULL_COM)
    |   (1UL << COMM_HSM_COMM_EV_ECUM_WAKEUP_IND)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_START_INDICATION)
    |   (1UL << COMM_HSM_COMM_EV_NM_RESTART_IND)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_NM_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_MODE)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_SILENT_COM)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_TIMEOUT)
    | 0UL
    ,
    ComM_HsmTrReqRunActive, /* transitions for this state */
    COMM_HSM_COMM_SIDX_PENDINGREQUEST, /* parent state */
    COMM_HSM_SIDX_INVALID, /* no init state */
      COMM_HSM_AIDX_INVALID, /* no entry action */
    COMM_HSM_AIDX_INVALID, /* no exit action */
    COMM_HSM_AIDX_INVALID, /* no do action */
    2 /* num of transitions */
  },
  {
    /* description of state ReqRunPassive */
    /* non-deferred and non-ignored event mask */
   (1UL << COMM_HSM_COMM_EV_COMALLOWED_CHANGED)
    | 0UL
    ,
      /* ignored event mask */
   (1UL << COMM_HSM_COMM_EV_LIMIT_TO_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_PNC_NM_REQUEST)
    |   (1UL << COMM_HSM_COMM_EV_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_NM_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_NM_PREP_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_RETRY_COUNT_LIMIT)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_FULL_COM)
    |   (1UL << COMM_HSM_COMM_EV_ECUM_WAKEUP_IND)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_START_INDICATION)
    |   (1UL << COMM_HSM_COMM_EV_NM_RESTART_IND)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_NM_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_REQ_STATUS_CHANGED)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_MODE)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_SILENT_COM)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_TIMEOUT)
    | 0UL
    ,
    ComM_HsmTrReqRunPassive, /* transitions for this state */
    COMM_HSM_COMM_SIDX_PENDINGREQUEST, /* parent state */
    COMM_HSM_SIDX_INVALID, /* no init state */
      COMM_HSM_AIDX_INVALID, /* no entry action */
    COMM_HSM_AIDX_INVALID, /* no exit action */
    COMM_HSM_AIDX_INVALID, /* no do action */
    1 /* num of transitions */
  },
  {
    /* description of state SilentCom */
    0U, /* no non-deferred event mask (no leaf state) */
    0U, /* no ignored event mask (no leaf state) */
    ComM_HsmTrSilentCom, /* transitions for this state */
    COMM_HSM_COMM_SIDX_TOP, /* parent state */
    COMM_HSM_COMM_SIDX_WAITFORSILENTCOM, /* init state */
      COMM_HSM_AIDX_INVALID, /* no entry action */
    COMM_HSM_AIDX_INVALID, /* no exit action */
    COMM_HSM_AIDX_INVALID, /* no do action */
    3 /* num of transitions */
  },
  {
    /* description of state SilentComNotifed */
    /* non-deferred and non-ignored event mask */
   (1UL << COMM_HSM_COMM_EV_NM_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_REQ_STATUS_CHANGED)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_MODE)
    | 0UL
    ,
      /* ignored event mask */
   (1UL << COMM_HSM_COMM_EV_LIMIT_TO_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_PNC_NM_REQUEST)
    |   (1UL << COMM_HSM_COMM_EV_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_NM_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_NM_PREP_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_RETRY_COUNT_LIMIT)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_FULL_COM)
    |   (1UL << COMM_HSM_COMM_EV_ECUM_WAKEUP_IND)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_START_INDICATION)
    |   (1UL << COMM_HSM_COMM_EV_NM_RESTART_IND)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_COMALLOWED_CHANGED)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_SILENT_COM)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_TIMEOUT)
    | 0UL
    ,
    NULL_PTR,  /* no transitions */
    COMM_HSM_COMM_SIDX_SILENTCOM, /* parent state */
    COMM_HSM_SIDX_INVALID, /* no init state */
      COMM_HSM_COMM_AIDX_SILENTCOMNOTIFED_ENTRY, /* entry function */
    COMM_HSM_AIDX_INVALID, /* no exit action */
    COMM_HSM_AIDX_INVALID, /* no do action */
    0U  /* no transitions */
  },
  {
    /* description of state WaitForSilentCom */
    /* non-deferred and non-ignored event mask */
   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_SILENT_COM)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_TIMEOUT)
    | 0UL
    ,
      /* ignored event mask */
   (1UL << COMM_HSM_COMM_EV_LIMIT_TO_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_PNC_NM_REQUEST)
    |   (1UL << COMM_HSM_COMM_EV_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_NM_TIMEOUT)
    |   (1UL << COMM_HSM_COMM_EV_NM_PREP_BUS_SLEEP_MODE)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_RETRY_COUNT_LIMIT)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_FULL_COM)
    |   (1UL << COMM_HSM_COMM_EV_ECUM_WAKEUP_IND)
    |   (1UL << COMM_HSM_COMM_EV_NM_NETWORK_START_INDICATION)
    |   (1UL << COMM_HSM_COMM_EV_NM_RESTART_IND)
    |   (1UL << COMM_HSM_COMM_EV_BUSSM_MODE_IND_NO_COM)
    |   (1UL << COMM_HSM_COMM_EV_COMALLOWED_CHANGED)
    | 0UL
    ,
    ComM_HsmTrWaitForSilentCom, /* transitions for this state */
    COMM_HSM_COMM_SIDX_SILENTCOM, /* parent state */
    COMM_HSM_SIDX_INVALID, /* no init state */
      COMM_HSM_COMM_AIDX_WAITFORSILENTCOM_ENTRY, /* entry function */
    COMM_HSM_COMM_AIDX_WAITFORSILENTCOM_EXIT, /* exit function */
    COMM_HSM_AIDX_INVALID, /* no do action */
    2 /* num of transitions */
  }
};

#if (COMM_HSM_TRACE == STD_ON)
/* Deviation MISRA-1 */
STATIC CONSTP2CONST(char, COMM_CONST, COMM_CONST)
  ComM_HsmComMStateNames[] =
{
  "TOP",
  "FullCom",
  "FullComNotified",
  "AcceptLimitToNoCom",
  "NetReqDelayedNoNm",
  "NetReqNm",
  "NetReqNoNm",
  "ReadySleepNm",
  "ReadySleepNoNm",
  "PassiveStartupWait",
  "ReqNetworkWait",
  "WaitForFullCom",
  "WffcToNetReq",
  "WffcToNetReqActive",
  "WffcToNetReqPassive",
  "WffcToReadySleep",
  "NoCom",
  "NoPendingRequest",
  "NoComFirst",
  "NoComNotifed",
  "WaitForNoCom",
  "PendingRequest",
  "ReqRunActive",
  "ReqRunPassive",
  "SilentCom",
  "SilentComNotifed",
  "WaitForSilentCom",
};

/* Deviation MISRA-1 */
STATIC CONSTP2CONST(char, COMM_CONST, COMM_CONST)
  ComM_HsmComMActionNames[] =
{
  "FullComNotified entry",
  "FullComNotified action 1",
  "AcceptLimitToNoCom entry",
  "AcceptLimitToNoCom action 1",
  "AcceptLimitToNoCom action 2",
  "AcceptLimitToNoCom action 3",
  "NetReqDelayedNoNm entry",
  "NetReqNm action 1",
  "NetReqNm action 2",
  "NetReqNoNm entry",
  "ReadySleepNm entry",
  "ReadySleepNm action 1",
  "ReadySleepNoNm entry",
  "PassiveStartupWait entry",
  "PassiveStartupWait exit",
  "PassiveStartupWait action 2",
  "PassiveStartupWait action 3",
  "ReqNetworkWait entry",
  "ReqNetworkWait exit",
  "WaitForFullCom entry",
  "WaitForFullCom exit",
  "WaitForFullCom action 1",
  "WffcToNetReqActive action 1",
  "WffcToNetReqPassive action 1",
  "NoComFirst entry",
  "NoComNotifed entry",
  "WaitForNoCom entry",
  "WaitForNoCom exit",
  "PendingRequest entry",
  "SilentCom action 1",
  "SilentComNotifed entry",
  "WaitForSilentCom entry",
  "WaitForSilentCom exit",
};

/* Deviation MISRA-1 */
STATIC CONSTP2CONST(char, COMM_CONST, COMM_CONST)
  ComM_HsmComMGuardNames[] =
{
  "AcceptLimitToNoCom guard 2",
  "AcceptLimitToNoCom guard 3",
  "NetReqDelayedNoNm guard 1",
  "NetReqDelayedNoNm guard 2",
  "NetReqDelayedNoNm guard 3",
  "NetReqNm guard 2",
  "ReadySleepNm guard 1",
  "ReadySleepNoNm guard 1",
  "PassiveStartupWait guard 1",
  "PassiveStartupWait guard 2",
  "WaitForFullCom guard 3",
  "WffcToNetReqActive guard 1",
  "WffcToNetReqPassive guard 1",
  "NoPendingRequest guard 4",
  "PendingRequest guard 1",
  "ReqRunActive guard 1",
  "ReqRunActive guard 2",
  "ReqRunPassive guard 1",
  "SilentCom guard 3",
};

/* Deviation MISRA-1 */
STATIC CONSTP2CONST(char, COMM_CONST, COMM_CONST)
  ComM_HsmComMEventNames[] =
{
  "LIMIT_TO_NO_COM",
  "PNC_NM_REQUEST",
  "TIMEOUT",
  "NM_TIMEOUT",
  "NM_PREP_BUS_SLEEP_MODE",
  "BUSSM_RETRY_COUNT_LIMIT",
  "BUSSM_MODE_IND_FULL_COM",
  "ECUM_WAKEUP_IND",
  "NM_NETWORK_START_INDICATION",
  "NM_RESTART_IND",
  "BUSSM_MODE_IND_NO_COM",
  "COMALLOWED_CHANGED",
  "NM_BUS_SLEEP_MODE",
  "REQ_STATUS_CHANGED",
  "NM_NETWORK_MODE",
  "BUSSM_MODE_IND_SILENT_COM",
  "BUSSM_TIMEOUT",
};
#endif

/*==================[external constants]====================================*/

/* Top level state chart description data */
CONST(ComM_HsmStatechartType, COMM_CONST)
  ComM_HsmScComM =
{
  ComM_HsmScdComM, /* state description array */
  ComM_HsmInstComM, /* instances RAM */
  ComM_HsmComMActions, /* actions */
  ComM_HsmComMGuards, /* guards */
  ComM_HsmEvCountersComM, /* event counters RAM */
  ComM_HsmEvQueuesComM, /* event queues RAM */
#if (COMM_HSM_TRACE == STD_ON)
  "ComM", /* name of the HSM */
  ComM_HsmComMStateNames,
  ComM_HsmComMActionNames,
  ComM_HsmComMGuardNames,
  ComM_HsmComMEventNames,
#endif
  COMM_HSM_COMM_NUM_EVENTS, /* num of events */
  0U, /* state chart id */
  COMM_HSM_COMM_NUM_INST, /* num of instances */
  COMM_HSM_COMM_SIDX_TOP /* top state index */
};


#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[internal function definitions]=========================*/

/*==================[external function definitions]=========================*/

/*==================[end of file]===========================================*/
