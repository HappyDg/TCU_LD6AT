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

#ifndef COMM_HSMCOMMPNCINT_H
#define COMM_HSMCOMMPNCINT_H

/* Internal interface for the ComMPnc state
 * machine.
 *
 * This header must only be included by
 * ComM_HsmComMPncData.c and ComM_HsmComMPncFnct.c.
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
  COMM_HSM_COMMPNC_SIDX_PNCTOP,
  COMM_HSM_COMMPNC_SIDX_PNCFULLCOM,
  COMM_HSM_COMMPNC_SIDX_PNCPREPARESLEEP,
  COMM_HSM_COMMPNC_SIDX_PNCREADYSLEEP,
  COMM_HSM_COMMPNC_SIDX_PNCREQUESTED,
  COMM_HSM_COMMPNC_SIDX_PNCNOCOM,
  COMM_HSM_COMMPNC_SIDX_PNCNOCOMINIT,
  COMM_HSM_COMMPNC_SIDX_PNCNOCOMNOTIFY,
  COMM_HSM_COMMPNC_NO_OF_STATES
} ComM_HsmComMPncStateIdType;
/* typedefed type only used for debugging */

/* *** IDs for entry/axit and transition actions *** */
typedef enum
{
  COMM_HSM_COMMPNC_AIDX_PNCPREPARESLEEP_ENTRY,
  COMM_HSM_COMMPNC_AIDX_PNCPREPARESLEEP_ACTION_1,
  COMM_HSM_COMMPNC_AIDX_PNCPREPARESLEEP_ACTION_2,
  COMM_HSM_COMMPNC_AIDX_PNCREADYSLEEP_ENTRY,
  COMM_HSM_COMMPNC_AIDX_PNCREQUESTED_ENTRY,
  COMM_HSM_COMMPNC_AIDX_PNCREQUESTED_ACTION_1,
  COMM_HSM_COMMPNC_AIDX_PNCNOCOMNOTIFY_ENTRY,
  COMM_HSM_COMMPNC_NO_OF_ACTIONS
} ComM_HsmComMPncActionIdType;
/* typedefed type only used for debugging */

/* *** IDs for guards *** */
typedef enum
{
  COMM_HSM_COMMPNC_GIDX_PNCPREPARESLEEP_GUARD_1,
  COMM_HSM_COMMPNC_GIDX_PNCREADYSLEEP_GUARD_1,
  COMM_HSM_COMMPNC_GIDX_PNCNOCOM_GUARD_1,
  COMM_HSM_COMMPNC_GIDX_PNCNOCOM_GUARD_2,
  COMM_HSM_COMMPNC_NO_OF_GUARDS
} ComM_HsmComMPncGuardIdType;
/* typedefed type only used for debugging */

/*==================[external function declarations]========================*/

#define COMM_START_SEC_CODE
#include <MemMap.h>

/* function declarations of state entry, exit, guard, action functions
 * defined in ComMPnc_fnct.c */



extern FUNC(void, COMM_CODE)
 ComM_HsmComMPncSfPncPrepareSleepEntry(
  COMM_PDL_SF(const uint8 instIdx));
/* implements guard 'ComM_PncGetEIRA() == 1' */
extern FUNC(boolean, COMM_CODE)
 ComM_HsmComMPncSfPncPrepareSleepGuard1(
  COMM_PDL_SF(const uint8 instIdx));
/* implements action 'StopTimer(ComMPncPrepareSleepTimer);' */
extern FUNC(void, COMM_CODE)
 ComM_HsmComMPncSfPncPrepareSleepAction1(
  COMM_PDL_SF(const uint8 instIdx));
/* implements action 'StopTimer(ComMPncPrepareSleepTimer);' */
extern FUNC(void, COMM_CODE)
 ComM_HsmComMPncSfPncPrepareSleepAction2(
  COMM_PDL_SF(const uint8 instIdx));

extern FUNC(void, COMM_CODE)
 ComM_HsmComMPncSfPncReadySleepEntry(
  COMM_PDL_SF(const uint8 instIdx));
/* implements guard 'ComM_PncGetEIRA() == 0' */
extern FUNC(boolean, COMM_CODE)
 ComM_HsmComMPncSfPncReadySleepGuard1(
  COMM_PDL_SF(const uint8 instIdx));

extern FUNC(void, COMM_CODE)
 ComM_HsmComMPncSfPncRequestedEntry(
  COMM_PDL_SF(const uint8 instIdx));
/* implements action 'Com_SendSignal(ERA_PNC_ID, 0); if (COMM_NO_INTERNAL_REQUESTS) ComM_SetChannelActiveStatus(FALSE);' */
extern FUNC(void, COMM_CODE)
 ComM_HsmComMPncSfPncRequestedAction1(
  COMM_PDL_SF(const uint8 instIdx));

/* implements guard 'ComM_PncGetEIRA() == 1' */
extern FUNC(boolean, COMM_CODE)
 ComM_HsmComMPncSfPncNoComGuard1(
  COMM_PDL_SF(const uint8 instIdx));
/* implements guard 'ComMSynchronousWakeUp == TRUE' */
extern FUNC(boolean, COMM_CODE)
 ComM_HsmComMPncSfPncNoComGuard2(
  COMM_PDL_SF(const uint8 instIdx));


extern FUNC(void, COMM_CODE)
 ComM_HsmComMPncSfPncNoComNotifyEntry(
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

#endif /* defined COMM_HSMCOMMPNCINT_H */
/*==================[end of file]===========================================*/
