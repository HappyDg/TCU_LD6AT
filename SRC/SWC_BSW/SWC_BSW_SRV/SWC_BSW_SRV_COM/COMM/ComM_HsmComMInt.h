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

#ifndef COMM_HSMCOMMINT_H
#define COMM_HSMCOMMINT_H

/* Internal interface for the ComM state
 * machine.
 *
 * This header must only be included by
 * ComM_HsmComMData.c and ComM_HsmComMFnct.c.
 */

/* CHECK: RULE 301 OFF (this file is generated, some lines may be longer then
 * 100 characters) */

/*==================[inclusions]============================================*/

#include <Std_Types.h>                            /* AUTOSAR standard types */

/* include state machine driver interface */
#include <ComM_Hsm.h>

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/* *** State indices and IDs for states *** */
typedef enum
{
  COMM_HSM_COMM_SIDX_TOP,
  COMM_HSM_COMM_SIDX_FULLCOM,
  COMM_HSM_COMM_SIDX_FULLCOMNOTIFIED,
  COMM_HSM_COMM_SIDX_ACCEPTLIMITTONOCOM,
  COMM_HSM_COMM_SIDX_NETREQDELAYEDNONM,
  COMM_HSM_COMM_SIDX_NETREQNM,
  COMM_HSM_COMM_SIDX_NETREQNONM,
  COMM_HSM_COMM_SIDX_READYSLEEPNM,
  COMM_HSM_COMM_SIDX_READYSLEEPNONM,
  COMM_HSM_COMM_SIDX_PASSIVESTARTUPWAIT,
  COMM_HSM_COMM_SIDX_REQNETWORKWAIT,
  COMM_HSM_COMM_SIDX_WAITFORFULLCOM,
  COMM_HSM_COMM_SIDX_WFFCTONETREQ,
  COMM_HSM_COMM_SIDX_WFFCTONETREQACTIVE,
  COMM_HSM_COMM_SIDX_WFFCTONETREQPASSIVE,
  COMM_HSM_COMM_SIDX_WFFCTOREADYSLEEP,
  COMM_HSM_COMM_SIDX_NOCOM,
  COMM_HSM_COMM_SIDX_NOPENDINGREQUEST,
  COMM_HSM_COMM_SIDX_NOCOMFIRST,
  COMM_HSM_COMM_SIDX_NOCOMNOTIFED,
  COMM_HSM_COMM_SIDX_WAITFORNOCOM,
  COMM_HSM_COMM_SIDX_PENDINGREQUEST,
  COMM_HSM_COMM_SIDX_REQRUNACTIVE,
  COMM_HSM_COMM_SIDX_REQRUNPASSIVE,
  COMM_HSM_COMM_SIDX_SILENTCOM,
  COMM_HSM_COMM_SIDX_SILENTCOMNOTIFED,
  COMM_HSM_COMM_SIDX_WAITFORSILENTCOM,
  COMM_HSM_COMM_NO_OF_STATES
} ComM_HsmComMStateIdType;
/* typedefed type only used for debugging */

/* *** IDs for entry/axit and transition actions *** */
typedef enum
{
  COMM_HSM_COMM_AIDX_FULLCOMNOTIFIED_ENTRY,
  COMM_HSM_COMM_AIDX_FULLCOMNOTIFIED_ACTION_1,
  COMM_HSM_COMM_AIDX_ACCEPTLIMITTONOCOM_ENTRY,
  COMM_HSM_COMM_AIDX_ACCEPTLIMITTONOCOM_ACTION_1,
  COMM_HSM_COMM_AIDX_ACCEPTLIMITTONOCOM_ACTION_2,
  COMM_HSM_COMM_AIDX_ACCEPTLIMITTONOCOM_ACTION_3,
  COMM_HSM_COMM_AIDX_NETREQDELAYEDNONM_ENTRY,
  COMM_HSM_COMM_AIDX_NETREQNM_ACTION_1,
  COMM_HSM_COMM_AIDX_NETREQNM_ACTION_2,
  COMM_HSM_COMM_AIDX_NETREQNONM_ENTRY,
  COMM_HSM_COMM_AIDX_READYSLEEPNM_ENTRY,
  COMM_HSM_COMM_AIDX_READYSLEEPNM_ACTION_1,
  COMM_HSM_COMM_AIDX_READYSLEEPNONM_ENTRY,
  COMM_HSM_COMM_AIDX_PASSIVESTARTUPWAIT_ENTRY,
  COMM_HSM_COMM_AIDX_PASSIVESTARTUPWAIT_EXIT,
  COMM_HSM_COMM_AIDX_PASSIVESTARTUPWAIT_ACTION_2,
  COMM_HSM_COMM_AIDX_PASSIVESTARTUPWAIT_ACTION_3,
  COMM_HSM_COMM_AIDX_REQNETWORKWAIT_ENTRY,
  COMM_HSM_COMM_AIDX_REQNETWORKWAIT_EXIT,
  COMM_HSM_COMM_AIDX_WAITFORFULLCOM_ENTRY,
  COMM_HSM_COMM_AIDX_WAITFORFULLCOM_EXIT,
  COMM_HSM_COMM_AIDX_WAITFORFULLCOM_ACTION_1,
  COMM_HSM_COMM_AIDX_WFFCTONETREQACTIVE_ACTION_1,
  COMM_HSM_COMM_AIDX_WFFCTONETREQPASSIVE_ACTION_1,
  COMM_HSM_COMM_AIDX_NOCOMFIRST_ENTRY,
  COMM_HSM_COMM_AIDX_NOCOMNOTIFED_ENTRY,
  COMM_HSM_COMM_AIDX_WAITFORNOCOM_ENTRY,
  COMM_HSM_COMM_AIDX_WAITFORNOCOM_EXIT,
  COMM_HSM_COMM_AIDX_PENDINGREQUEST_ENTRY,
  COMM_HSM_COMM_AIDX_SILENTCOM_ACTION_1,
  COMM_HSM_COMM_AIDX_SILENTCOMNOTIFED_ENTRY,
  COMM_HSM_COMM_AIDX_WAITFORSILENTCOM_ENTRY,
  COMM_HSM_COMM_AIDX_WAITFORSILENTCOM_EXIT,
  COMM_HSM_COMM_NO_OF_ACTIONS
} ComM_HsmComMActionIdType;
/* typedefed type only used for debugging */

/* *** IDs for guards *** */
typedef enum
{
  COMM_HSM_COMM_GIDX_ACCEPTLIMITTONOCOM_GUARD_2,
  COMM_HSM_COMM_GIDX_ACCEPTLIMITTONOCOM_GUARD_3,
  COMM_HSM_COMM_GIDX_NETREQDELAYEDNONM_GUARD_1,
  COMM_HSM_COMM_GIDX_NETREQDELAYEDNONM_GUARD_2,
  COMM_HSM_COMM_GIDX_NETREQDELAYEDNONM_GUARD_3,
  COMM_HSM_COMM_GIDX_NETREQNM_GUARD_2,
  COMM_HSM_COMM_GIDX_READYSLEEPNM_GUARD_1,
  COMM_HSM_COMM_GIDX_READYSLEEPNONM_GUARD_1,
  COMM_HSM_COMM_GIDX_PASSIVESTARTUPWAIT_GUARD_1,
  COMM_HSM_COMM_GIDX_PASSIVESTARTUPWAIT_GUARD_2,
  COMM_HSM_COMM_GIDX_WAITFORFULLCOM_GUARD_3,
  COMM_HSM_COMM_GIDX_WFFCTONETREQACTIVE_GUARD_1,
  COMM_HSM_COMM_GIDX_WFFCTONETREQPASSIVE_GUARD_1,
  COMM_HSM_COMM_GIDX_NOPENDINGREQUEST_GUARD_4,
  COMM_HSM_COMM_GIDX_PENDINGREQUEST_GUARD_1,
  COMM_HSM_COMM_GIDX_REQRUNACTIVE_GUARD_1,
  COMM_HSM_COMM_GIDX_REQRUNACTIVE_GUARD_2,
  COMM_HSM_COMM_GIDX_REQRUNPASSIVE_GUARD_1,
  COMM_HSM_COMM_GIDX_SILENTCOM_GUARD_3,
  COMM_HSM_COMM_NO_OF_GUARDS
} ComM_HsmComMGuardIdType;
/* typedefed type only used for debugging */

/*==================[external function declarations]========================*/

#define COMM_START_SEC_CODE
#include <MemMap.h>

/* function declarations of state entry, exit, guard, action functions
 * defined in ComM_fnct.c */



extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfFullComNotifiedEntry(
  COMM_PDL_SF(const uint8 instIdx));
/* implements action 'if (ComMNmVariant==FULL) Nm_NetworkRelease();' */
extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfFullComNotifiedAction1(
  COMM_PDL_SF(const uint8 instIdx));

extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfAcceptLimitToNoComEntry(
  COMM_PDL_SF(const uint8 instIdx));
/* implements action 'ComM_LimitToNoCom()' */
extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfAcceptLimitToNoComAction1(
  COMM_PDL_SF(const uint8 instIdx));
/* implements guard 'IsChanReqAllowedFullCom()' */
extern FUNC(boolean, COMM_CODE)
 ComM_HsmComMSfAcceptLimitToNoComGuard2(
  COMM_PDL_SF(const uint8 instIdx));
/* implements action 'ComM_Notify(COMM_NO_COMMUNICATION); if (NmVariant == FULL) Nm_NetworkRelease();' */
extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfAcceptLimitToNoComAction2(
  COMM_PDL_SF(const uint8 instIdx));
/* implements guard 'IsChanReqAllowedFullCom()' */
extern FUNC(boolean, COMM_CODE)
 ComM_HsmComMSfAcceptLimitToNoComGuard3(
  COMM_PDL_SF(const uint8 instIdx));
/* implements action 'ComM_Notify(COMM_SILENT_COMMUNICATION); if (NmVariant == FULL) Nm_NetworkRelease();' */
extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfAcceptLimitToNoComAction3(
  COMM_PDL_SF(const uint8 instIdx));

extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfNetReqDelayedNoNmEntry(
  COMM_PDL_SF(const uint8 instIdx));
/* implements guard '(NmVariant==NONE) && (BusType==Internal) &&
 * IsChanRelAllowed()' */
extern FUNC(boolean, COMM_CODE)
 ComM_HsmComMSfNetReqDelayedNoNmGuard1(
  COMM_PDL_SF(const uint8 instIdx));
/* implements guard '(NmVariant==NONE) && (BusType!=Internal) &&
 * IsChanRelAllowed()' */
extern FUNC(boolean, COMM_CODE)
 ComM_HsmComMSfNetReqDelayedNoNmGuard2(
  COMM_PDL_SF(const uint8 instIdx));
/* implements guard '(NmVariant!=NONE) && IsChanRelAllowed()' */
extern FUNC(boolean, COMM_CODE)
 ComM_HsmComMSfNetReqDelayedNoNmGuard3(
  COMM_PDL_SF(const uint8 instIdx));

/* implements action 'Nm_NetworkRequest(); ==> ComM980' */
extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfNetReqNmAction1(
  COMM_PDL_SF(const uint8 instIdx));
/* implements guard 'IsChanRelAllowed()' */
extern FUNC(boolean, COMM_CODE)
 ComM_HsmComMSfNetReqNmGuard2(
  COMM_PDL_SF(const uint8 instIdx));
/* implements action 'if (NmVariant == FULL) Nm_NetworkRelease();' */
extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfNetReqNmAction2(
  COMM_PDL_SF(const uint8 instIdx));

extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfNetReqNoNmEntry(
  COMM_PDL_SF(const uint8 instIdx));

extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfReadySleepNmEntry(
  COMM_PDL_SF(const uint8 instIdx));
/* implements guard 'IsChanReqAllowedFullCom()' */
extern FUNC(boolean, COMM_CODE)
 ComM_HsmComMSfReadySleepNmGuard1(
  COMM_PDL_SF(const uint8 instIdx));
/* implements action 'if (NmVariant == FULL) Nm_NetworkRequest();' */
extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfReadySleepNmAction1(
  COMM_PDL_SF(const uint8 instIdx));

extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfReadySleepNoNmEntry(
  COMM_PDL_SF(const uint8 instIdx));
/* implements guard 'IsChanReqAllowedFullCom()' */
extern FUNC(boolean, COMM_CODE)
 ComM_HsmComMSfReadySleepNoNmGuard1(
  COMM_PDL_SF(const uint8 instIdx));

extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfPassiveStartupWaitEntry(
  COMM_PDL_SF(const uint8 instIdx));
extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfPassiveStartupWaitExit(
  COMM_PDL_SF(const uint8 instIdx));
/* implements guard 'NmVariant==PASSIVE' */
extern FUNC(boolean, COMM_CODE)
 ComM_HsmComMSfPassiveStartupWaitGuard1(
  COMM_PDL_SF(const uint8 instIdx));
/* implements guard 'NmVariant==FULL && IsChanReqAllowedFullCom()' */
extern FUNC(boolean, COMM_CODE)
 ComM_HsmComMSfPassiveStartupWaitGuard2(
  COMM_PDL_SF(const uint8 instIdx));
/* implements action 'Nm_NetworkRequest()' */
extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfPassiveStartupWaitAction2(
  COMM_PDL_SF(const uint8 instIdx));
/* implements action 'Nm_NetworkRelease()' */
extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfPassiveStartupWaitAction3(
  COMM_PDL_SF(const uint8 instIdx));

extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfReqNetworkWaitEntry(
  COMM_PDL_SF(const uint8 instIdx));
extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfReqNetworkWaitExit(
  COMM_PDL_SF(const uint8 instIdx));

extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfWaitForFullComEntry(
  COMM_PDL_SF(const uint8 instIdx));
extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfWaitForFullComExit(
  COMM_PDL_SF(const uint8 instIdx));
/* implements action 'ComM_RetryBusSmRequest()' */
extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfWaitForFullComAction1(
  COMM_PDL_SF(const uint8 instIdx));
/* implements guard 'IsChanRelAllowed()' */
extern FUNC(boolean, COMM_CODE)
 ComM_HsmComMSfWaitForFullComGuard3(
  COMM_PDL_SF(const uint8 instIdx));


/* implements guard 'NmVariant==FULL' */
extern FUNC(boolean, COMM_CODE)
 ComM_HsmComMSfWffcToNetReqActiveGuard1(
  COMM_PDL_SF(const uint8 instIdx));
/* implements action 'Nm_NetworkRequest();' */
extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfWffcToNetReqActiveAction1(
  COMM_PDL_SF(const uint8 instIdx));

/* implements guard 'NmVariant==(FULL|PASSIVE)' */
extern FUNC(boolean, COMM_CODE)
 ComM_HsmComMSfWffcToNetReqPassiveGuard1(
  COMM_PDL_SF(const uint8 instIdx));
/* implements action 'Nm_PassiveStartUp();' */
extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfWffcToNetReqPassiveAction1(
  COMM_PDL_SF(const uint8 instIdx));



/* implements guard 'IsChanReqAllowedNoFullCom()' */
extern FUNC(boolean, COMM_CODE)
 ComM_HsmComMSfNoPendingRequestGuard4(
  COMM_PDL_SF(const uint8 instIdx));

extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfNoComFirstEntry(
  COMM_PDL_SF(const uint8 instIdx));

extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfNoComNotifedEntry(
  COMM_PDL_SF(const uint8 instIdx));

extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfWaitForNoComEntry(
  COMM_PDL_SF(const uint8 instIdx));
extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfWaitForNoComExit(
  COMM_PDL_SF(const uint8 instIdx));

extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfPendingRequestEntry(
  COMM_PDL_SF(const uint8 instIdx));
/* implements guard 'CommunicationAllowed==TRUE && BusType==Internal' */
extern FUNC(boolean, COMM_CODE)
 ComM_HsmComMSfPendingRequestGuard1(
  COMM_PDL_SF(const uint8 instIdx));

/* implements guard 'CommunicationAllowed==TRUE && BusType != Internal' */
extern FUNC(boolean, COMM_CODE)
 ComM_HsmComMSfReqRunActiveGuard1(
  COMM_PDL_SF(const uint8 instIdx));
/* implements guard '!IsChanReqAllowedNoFullCom()' */
extern FUNC(boolean, COMM_CODE)
 ComM_HsmComMSfReqRunActiveGuard2(
  COMM_PDL_SF(const uint8 instIdx));

/* implements guard 'CommunicationAllowed==TRUE && BusType != Internal' */
extern FUNC(boolean, COMM_CODE)
 ComM_HsmComMSfReqRunPassiveGuard1(
  COMM_PDL_SF(const uint8 instIdx));

/* implements action 'if (ComMNmVariant==FULL) Nm_NetworkRelease();' */
extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfSilentComAction1(
  COMM_PDL_SF(const uint8 instIdx));
/* implements guard 'IsChanReqAllowedNoFullCom()' */
extern FUNC(boolean, COMM_CODE)
 ComM_HsmComMSfSilentComGuard3(
  COMM_PDL_SF(const uint8 instIdx));

extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfSilentComNotifedEntry(
  COMM_PDL_SF(const uint8 instIdx));

extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfWaitForSilentComEntry(
  COMM_PDL_SF(const uint8 instIdx));
extern FUNC(void, COMM_CODE)
 ComM_HsmComMSfWaitForSilentComExit(
  COMM_PDL_SF(const uint8 instIdx));


#define COMM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* defined COMM_HSMCOMMINT_H */
/*==================[end of file]===========================================*/
