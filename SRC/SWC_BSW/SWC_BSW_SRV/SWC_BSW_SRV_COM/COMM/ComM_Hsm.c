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

/* This file contains the implementation of the hierarchical state machine
 * driver. */

/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 17.4 (required)
 *     Array indexing shall be the only allowed form of pointer arithmetic.
 *
 *     Reason:
 *     This operation will not cause any problem and reduce the need for extra
 *     index variable
 *
 *  MISRA-2) Deviated Rule: 19.10 (required)
 *     Parameter instance shall be enclosed in parentheses.
 *
 *     Reason:
 *     It is used in function parameter declarations and definitions
 *     or as structure member.
 *
 *  MISRA-3) Deviated Rule: 20.9 (required)
 *     The input/output library <stdio.h> shall not be used in production code.
 *
 *     Reason:
 *     Library function printf() which is defined inside library <stdio.h> is
 *     used in this file, for debugging purpose only.
 *
 *  MISRA-4) Deviated Rule: 13.5 (required)
 *     The three expressions of a for statement shall be concerned only with loop control.
 *
 *     Reason:
 *     MISRA rule 13.5 is not deviated. This is a 'false positive' in the MISRA checker.
 */

/*==================[inclusions]============================================*/

#include <ComM_Trace.h>
#include <Std_Types.h>          /* AUTOSAR standard types */

#include <SchM_ComM.h>           /* SchM symbols for crit. sections */

#include <ComM_Hsm.h>            /* public API of ComM_Hsm.c */

#include <ComM_BSW_Cfg.h>
/* design debugging output */
#if (COMM_HSM_TRACE == STD_ON)
/* CHECK: RULE 501 OFF (macro needed in std headers) */
#define __NO_ISOCEXT
#include <stdlib.h>
#include <stdio.h>
/* CHECK: RULE 501 ON */
#endif

/*==================[macros]================================================*/

#if (COMM_HSM_INST_MULTI_ENABLED == STD_ON)
/* Deviation MISRA-2 */
#define COMM_HSM_DEL_FROM_QUEUE(a,b,c) ComM_HsmDelFromQueue(a,b,c)
/* Deviation MISRA-2 */
#define COMM_HSM_TRAN(a,b,c)           ComM_HsmTran(a,b,c)
/* Deviation MISRA-2 */
#define COMM_HSM_INIT_SUBSTATES(a,b)   ComM_HsmInitSubstates(a,b)
/* Deviation MISRA-2 */
#define COMM_HSM_FIND_EV_TO_DISPATCH(a,b,c,d) ComM_HsmFindEvToDispatch(a,b,c,d)
/* Deviation MISRA-2 */
#define COMM_HSM_DISPATCH_EVENT(a,b,c) ComM_HsmDispatchEvent(a,b,c)

/** \brief Access entry in event queue of a specific hsm instance */
/* Deviation MISRA-2 <+2> */
#define COMM_EV_QUEUE_ENTRY(sc,instIdx,entryIdx) \
  ((sc)->events[((instIdx)*((sc)->numEvents))+(entryIdx)])
#define COMM_EV_COUNTER_ENTRY(sc,instIdx,entryIdx) \
  ((sc)->evCounters[((instIdx)*((sc)->numEvents))+(entryIdx)])
#else
/* Deviation MISRA-2 */
#define COMM_HSM_DEL_FROM_QUEUE(a,b,c) ComM_HsmDelFromQueue(a,c)
/* Deviation MISRA-2 */
#define COMM_HSM_TRAN(a,b,c)           ComM_HsmTran(a,c)
#define COMM_HSM_INIT_SUBSTATES(a,b)   ComM_HsmInitSubstates(a)
/* Deviation MISRA-2 */
#define COMM_HSM_FIND_EV_TO_DISPATCH(a,b,c,d) ComM_HsmFindEvToDispatch(a,c,d)
/* Deviation MISRA-2 <+2> */
#define COMM_HSM_DISPATCH_EVENT(a,b,c) ComM_HsmDispatchEvent(a,c)
#define COMM_EV_QUEUE_ENTRY(sc,instIdx,entryIdx) \
  ((sc)->events[(entryIdx)])
#define COMM_EV_COUNTER_ENTRY(sc,instIdx,entryIdx) \
  ((sc)->evCounters[(entryIdx)])
#endif

#if (COMM_HSM_TRACE == STD_ON)
#define COMM_HSM_PRINT1(a)                       \
  do                                            \
  {                                             \
    if (ComM_HsmTraceEnabled == TRUE)            \
    {                                           \
      /* Deviation MISRA-2 */                   \
      /* Deviation MISRA-3 */                   \
      (void)printf("HsmTrace: " a);             \
    }                                           \
  } while (0U)
#define COMM_HSM_PRINT2(a,b)                     \
  do                                            \
  {                                             \
    if (ComM_HsmTraceEnabled == TRUE)            \
    {                                           \
      /* Deviation MISRA-2 */                   \
      /* Deviation MISRA-3 */                   \
      (void)printf("HsmTrace: " a,(b));         \
    }                                           \
  } while (0U)
#define COMM_HSM_PRINT3(a,b,c)                   \
  do                                            \
  {                                             \
    if (ComM_HsmTraceEnabled == TRUE)            \
    {                                           \
      /* Deviation MISRA-2 */                   \
      /* Deviation MISRA-3 */                   \
      (void)printf("HsmTrace: " a,(b),(c));     \
    }                                           \
  } while (0U)
#define COMM_HSM_PRINT4(a,b,c,d)                 \
  do                                            \
  {                                             \
    if (ComM_HsmTraceEnabled == TRUE)            \
    {                                           \
      /* Deviation MISRA-2 */                   \
      /* Deviation MISRA-3 */                   \
      (void)printf("HsmTrace: " a,(b),(c),(d)); \
    }                                           \
  } while (0U)
#define COMM_HSM_PRINT5(a,b,c,d,e)               \
  do                                            \
  {                                             \
    if (ComM_HsmTraceEnabled == TRUE)            \
    {                                           \
      /* Deviation MISRA-2 */                   \
      /* Deviation MISRA-3 */                   \
      (void)printf("HsmTrace: " a,(b),(c),(d),(e));  \
    }                                           \
  } while (0U)
#else
#define COMM_HSM_PRINT1(a)          /* nothing */
#define COMM_HSM_PRINT2(a,b)        /* nothing */
#define COMM_HSM_PRINT3(a,b,c)      /* nothing */
#define COMM_HSM_PRINT4(a,b,c,d)    /* nothing */
#define COMM_HSM_PRINT5(a,b,c,d,e)  /* nothing */
#endif

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

#define COMM_START_SEC_CODE
#include <MemMap.h>

/** \brief Delete entry from event queue
 ** \param sc pointer to state chart
 ** \param instIdx index of state machine instance to work on
 ** \param queueEntryNo entry in queue to delete
 **
 ** This function must be called inside of a critical section which prevents
 ** the concurrent access to the queue.
 **/
STATIC FUNC(void, COMM_CODE) COMM_HSM_DEL_FROM_QUEUE(
  const ComM_HsmStatechartPtrType sc,
  const uint8                    instIdx,
  const uint8                    queueEntryNo);

/** \brief Execute a transition
 ** \param sc pointer to state chart
 ** \param instIdx index of state machine instance to work on
 ** \param tran Pointer to the transition description struct */
STATIC FUNC(void, COMM_CODE) COMM_HSM_TRAN(
  const ComM_HsmStatechartPtrType                      sc,
  const uint8                                         instIdx,
  CONSTP2CONST(ComM_HsmTranType, AUTOMATIC, COMM_CONST) tran);

/** \brief Initialize all substates for the current state
 ** \param sc pointer to state chart to work on
 ** \param instIdx index of state machine instance to work on */
STATIC FUNC(void, COMM_CODE) COMM_HSM_INIT_SUBSTATES(
  const ComM_HsmStatechartPtrType sc,
  const uint8                    instIdx);

/** \brief Look for dispatchable event in event queue
 ** \param sc pointer to state chart to work on
 ** \param instIdx index of state machine instance to work on
 ** \param event identified event from queue
 ** \param queueEntryNo index in queue for identified event
 ** \return look up status
 ** \retval TRUE an event is found in the queue and it is not deferred
 ** and not ignored
 ** \retval FALSE no event is not found or one which is deferred or one
 ** which is ignored in the current state
 **
 ** Events which are marked to be ignored in the current state are deleted
 ** from the queue within this function. */
STATIC FUNC(boolean, COMM_CODE) COMM_HSM_FIND_EV_TO_DISPATCH(
  const ComM_HsmStatechartPtrType                     sc,
  const uint8                                        instIdx,
  CONSTP2VAR(ComM_HsmEventType, AUTOMATIC, AUTOMATIC) event,
  CONSTP2VAR(uint8, AUTOMATIC, AUTOMATIC)            queueEntryNo);

/** \brief Dispatch event from event queue
 ** \param sc pointer to state chart to work on
 ** \param instIdx index of state machine instance to work on
 ** \param event identified event from queue
 ** \return Transition fired indicator
 ** \retval TRUE the event dispatching resulted in an fired transition
 ** \retval FALSE else */
STATIC FUNC(boolean, COMM_CODE) COMM_HSM_DISPATCH_EVENT(
  const ComM_HsmStatechartPtrType sc,
  const uint8                    instIdx,
  const ComM_HsmEventType         event);

#define COMM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

#if (COMM_HSM_TRACE == STD_ON)

#define COMM_START_SEC_VAR_INIT_8
#include <MemMap.h>

STATIC VAR(boolean, COMM_VAR) ComM_HsmTraceEnabled = FALSE;

#define COMM_STOP_SEC_VAR_INIT_8
#include <MemMap.h>

#endif

/*==================[external function definitions]=========================*/

#define COMM_START_SEC_CODE
#include <MemMap.h>

/*------------------ init functions ----------------------------------------*/

#if (COMM_HSM_INST_MULTI_ENABLED == STD_ON)
FUNC(void, COMM_CODE) ComM_HsmInit(const ComM_HsmStatechartPtrType sc)
{
  uint8 instIdx;
  DBG_COMM_HSMINIT_ENTRY(sc);
  for (instIdx = 0U; instIdx < sc->numInstances; ++instIdx)
  {
    COMM_HSMINITINST(sc, instIdx);
  }
  DBG_COMM_HSMINIT_EXIT(sc);
}
/* else: function is implemented as macro and maps to ComM_HsmInitInst() */
#endif

FUNC(void, COMM_CODE) COMM_HSMINITINST(
  const ComM_HsmStatechartPtrType sc,
  const uint8                    instIdx)
{
  CONSTP2VAR(ComM_HsmInstType, AUTOMATIC, COMM_VAR_NOINIT) inst
    = &COMM_INST_ACCESS(sc->instances, instIdx);
  uint8 i;

  ComM_HsmStateIdxType oldState;

  DBG_COMM_HSMINITINST_ENTRY(sc, instIdx);

  /* Deviation MISRA-3 */
  COMM_HSM_PRINT3("%s %d Init\n", sc->hsmName, COMM_INST(instIdx));

  /* init all fields because the struct is placed in a NOINIT memory
   * section */
  oldState = inst->stateId;
  inst->stateId  = sc->topStateId;
  inst->sourceId = COMM_HSM_SIDX_INVALID;

  for (i = 0U; i < sc->numEvents; ++i)
  {
    COMM_EV_QUEUE_ENTRY(sc, instIdx, i) = 0U;
    COMM_EV_COUNTER_ENTRY(sc, instIdx, i) = 0U;
  }
  inst->evQueueFill       = 0U;
  inst->evQueueInsertEvNo = 0U;

  /* init all substates */
  COMM_HSM_INIT_SUBSTATES(sc, instIdx);
  DBG_COMM_GENERIC_GRP((sc->stateChartId), (instIdx), (oldState), (inst->stateId));

  DBG_COMM_HSMINITINST_EXIT(sc, instIdx);
}

/*------------------ emit functions ----------------------------------------*/

#if (COMM_HSM_INST_MULTI_ENABLED == STD_ON)
FUNC(void, COMM_CODE) ComM_HsmEmit(
  const ComM_HsmStatechartPtrType sc,
  const ComM_HsmEventType         event)
{
  uint8 instIdx;

  DBG_COMM_HSMEMIT_ENTRY(sc, event);

  for (instIdx = 0U; instIdx < sc->numInstances; ++instIdx)
  {
    COMM_HSMEMITINST(sc, instIdx, event);
  }
  DBG_COMM_HSMEMIT_EXIT(sc, event);
}
/* else: function is implemented as macro */
#endif

FUNC(void, COMM_CODE) COMM_HSMEMITINST(
  const ComM_HsmStatechartPtrType sc,
  const uint8                    instIdx,
  const ComM_HsmEventType         event)
{
  CONSTP2VAR(ComM_HsmInstType, AUTOMATIC, COMM_VAR_NOINIT) inst
    = &COMM_INST_ACCESS(sc->instances, instIdx);

  DBG_COMM_HSMEMITINST_ENTRY(sc, instIdx, event);

  SchM_Enter_ComM_SCHM_COMM_EXCLUSIVE_AREA_0();
  /* in case the event has already been queued don't add it again to the queue*/
  if ( COMM_EV_COUNTER_ENTRY(sc, instIdx, event) < 1 )
  {
    COMM_EV_QUEUE_ENTRY(sc, instIdx, inst->evQueueFill) = event;
    inst->evQueueFill++;
    /* leave evQueueInsertEvNo unchanged, this pointer will be updated on
     * insertion or event dispatching */
    ++COMM_EV_COUNTER_ENTRY(sc, instIdx, event);
  }
  SchM_Exit_ComM_SCHM_COMM_EXCLUSIVE_AREA_0();

  /* Deviation MISRA-3 */
  COMM_HSM_PRINT4(
    "%s %d event %s enqueued\n",
    sc->hsmName, COMM_INST(instIdx), sc->eventNames[event]);

  DBG_COMM_HSMEMITINST_EXIT(sc, instIdx, event);
}

FUNC(void, COMM_CODE) COMM_HSMEMITTOSELFINST(
  const ComM_HsmStatechartPtrType sc,
  const uint8                    instIdx,
  const ComM_HsmEventType         event)
{
  CONSTP2VAR(ComM_HsmInstType, AUTOMATIC, COMM_VAR_NOINIT) inst
    = &COMM_INST_ACCESS(sc->instances, instIdx);

  DBG_COMM_HSMEMITTOSELFINST_ENTRY(sc, instIdx, event);

  SchM_Enter_ComM_SCHM_COMM_EXCLUSIVE_AREA_0();
  if ( COMM_EV_COUNTER_ENTRY(sc, instIdx, event) < 1 )
  {
    /* make room for new entry */
    uint8 j;
    for (j = inst->evQueueFill; j > inst->evQueueInsertEvNo; --j)
    {
      COMM_EV_QUEUE_ENTRY(sc, instIdx, j) = COMM_EV_QUEUE_ENTRY(sc, instIdx, j-1);
    }
    ++inst->evQueueFill;
    ++COMM_EV_COUNTER_ENTRY(sc, instIdx, event);
    COMM_EV_QUEUE_ENTRY(sc, instIdx, inst->evQueueInsertEvNo) = event;
    inst->evQueueInsertEvNo++;
  }
  SchM_Exit_ComM_SCHM_COMM_EXCLUSIVE_AREA_0();

  /* Deviation MISRA-3 */
  COMM_HSM_PRINT4(
    "%s %d event %s enqueued internally\n",
    sc->hsmName, COMM_INST(instIdx), sc->eventNames[event]);

  DBG_COMM_HSMEMITTOSELFINST_EXIT(sc, instIdx, event);
}

/*------------------ main functions ----------------------------------------*/

FUNC(boolean, COMM_CODE) COMM_HSMMAININST(
  const ComM_HsmStatechartPtrType sc,
  const uint8                    instIdx)
{
  CONSTP2VAR(ComM_HsmInstType, AUTOMATIC, COMM_VAR_NOINIT) inst
    = &COMM_INST_ACCESS(sc->instances,instIdx);
  /* return value, flag indicating if at least one transition fired */
  boolean          transitionFired = FALSE;
  ComM_HsmEventType event;
  uint8            queueEntryNo;
  boolean          eventPending;

  DBG_COMM_HSMMAININST_ENTRY(sc, instIdx);

  /* Deviation MISRA-3 */
  COMM_HSM_PRINT3(
    "%s %d Main\n",
    sc->hsmName, COMM_INST(instIdx));

  /* reset event insertion pointer to an invalid value, this will be set to a
   * valid location if the first event is being dispatched */
  inst->evQueueInsertEvNo = 0U;

  /* check if there are is at least one pending event */
  eventPending
    = COMM_HSM_FIND_EV_TO_DISPATCH(sc, instIdx, &event, &queueEntryNo);

  /* dispatch all pending events from event queue */
  while (TRUE == eventPending)
  {
    const boolean retVal = COMM_HSM_DISPATCH_EVENT(sc, instIdx, event);
    transitionFired = (retVal || transitionFired);

    /* delete dispatched event from queue */
    SchM_Enter_ComM_SCHM_COMM_EXCLUSIVE_AREA_0();
    COMM_HSM_DEL_FROM_QUEUE(sc, instIdx, queueEntryNo);
    SchM_Exit_ComM_SCHM_COMM_EXCLUSIVE_AREA_0();

    eventPending
      = COMM_HSM_FIND_EV_TO_DISPATCH(sc, instIdx, &event, &queueEntryNo);
  }

  DBG_COMM_HSMMAININST_EXIT(transitionFired, sc, instIdx);
  return transitionFired;
}

#if (COMM_HSM_TRACE == STD_ON)
FUNC(void, COMM_CODE) ComM_HsmSetTracing(const boolean newValue)
{
  DBG_COMM_HSMSETTRACING_ENTRY(newValue);
  ComM_HsmTraceEnabled = newValue;
  DBG_COMM_HSMSETTRACING_EXIT(newValue);
}
#endif

#define COMM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function definitions]=========================*/

#define COMM_START_SEC_CODE
#include <MemMap.h>

STATIC FUNC(void, COMM_CODE) COMM_HSM_DEL_FROM_QUEUE(
  const ComM_HsmStatechartPtrType sc,
  const uint8                    instIdx,
  const uint8                    queueEntryNo)
{
  /* delete event no queueEntryNo from queue */
  CONSTP2VAR(ComM_HsmInstType, AUTOMATIC, COMM_VAR_NOINIT) inst
    = &COMM_INST_ACCESS(sc->instances, instIdx);
  uint8 j;

  /* reduce the occurrence counter of the respective event */
  ComM_HsmEventType event = COMM_EV_QUEUE_ENTRY(sc, instIdx, queueEntryNo);
  --COMM_EV_COUNTER_ENTRY(sc, instIdx, event);

  DBG_COMM_HSM_DEL_FROM_QUEUE_ENTRY(sc, instIdx, queueEntryNo);

  /* Deviation MISRA-4 */
  for (j = queueEntryNo; (j + 1U) < inst->evQueueFill; ++j)
  {
    COMM_EV_QUEUE_ENTRY(sc, instIdx, j)
      = COMM_EV_QUEUE_ENTRY(sc, instIdx, j + 1U);
  }
  --inst->evQueueFill;
  if (queueEntryNo < inst->evQueueInsertEvNo)
  {
    /* if this was an event emitted to self also decrement the insertion
     * pointer  */
    --inst->evQueueInsertEvNo;
  }
  /* no need to check for queueEntryNo >= inst->evQueueInsertEvNo here.  This
   * will be done before dispatching the next event from the queue */
   DBG_COMM_HSM_DEL_FROM_QUEUE_EXIT(sc, instIdx, queueEntryNo);
}

STATIC FUNC(void, COMM_CODE) COMM_HSM_TRAN(
  const ComM_HsmStatechartPtrType                      sc,
  const uint8                                         instIdx,
  CONSTP2CONST(ComM_HsmTranType, AUTOMATIC, COMM_CONST) tran)
{
  P2CONST(ComM_HsmStateType, AUTOMATIC, COMM_CONST) state;
  CONSTP2VAR(ComM_HsmInstType, AUTOMATIC, COMM_VAR_NOINIT) inst
      = &COMM_INST_ACCESS(sc->instances, instIdx);

  ComM_HsmStateIdxType oldState = inst->stateId;

  DBG_COMM_HSM_TRAN_ENTRY(sc, instIdx, tran);

  /* perform simplified transition for internal transitions */
  if (tran->target == COMM_HSM_SIDX_INVALID)
  {
    /* Deviation MISRA-3 */
    COMM_HSM_PRINT4(
      "%s %d %s (internal transition)\n",
      sc->hsmName, COMM_INST(instIdx), sc->actionNames[tran->steps[0U]]);
    sc->actions[tran->steps[0U]](COMM_PL_SF(instIdx));
  }
  else /* external transitions */
  {
    uint8_least i;

    /* "source" may be a superstate of "state".  exit all states from "state"
     * until "source" is reached */
    while (inst->stateId != inst->sourceId)
    {
      state = &sc->states[inst->stateId];

      if (state->exitFnIdx != COMM_HSM_AIDX_INVALID)
      {
        /* Deviation MISRA-3 */
        COMM_HSM_PRINT4(
          "%s %d %s\n",
          sc->hsmName, COMM_INST(instIdx), sc->actionNames[state->exitFnIdx]);
        sc->actions[state->exitFnIdx](COMM_PL_SF(instIdx));
      }

      inst->stateId = state->parentId;
    }

    /* execute exit/transiton/entry actions on transition path */
    for (i = 0U; i < tran->numSteps; ++i)
    {
      /* Deviation MISRA-3 */
      COMM_HSM_PRINT4(
        "%s %d %s\n",
        sc->hsmName, COMM_INST(instIdx), sc->actionNames[tran->steps[i]]);
      sc->actions[tran->steps[i]](COMM_PL_SF(instIdx));
    }

    /* set the new current state and perform init steps of substates */
    inst->stateId = tran->target; /* current state is last entered state */
    COMM_HSM_INIT_SUBSTATES(sc, instIdx);

    /* Deviation MISRA-3 */
    COMM_HSM_PRINT4(
      "%s %d transition to state %s finished\n",
      sc->hsmName, COMM_INST(instIdx), sc->stateNames[inst->stateId]);
  }

  DBG_COMM_GENERIC_GRP((sc->stateChartId), (instIdx), (oldState), (inst->stateId));
  DBG_COMM_HSM_TRAN_EXIT(sc, instIdx, tran);
}

STATIC FUNC(void, COMM_CODE) COMM_HSM_INIT_SUBSTATES(
  const ComM_HsmStatechartPtrType sc,
  const uint8                    instIdx)
{
  CONSTP2VAR(ComM_HsmInstType, AUTOMATIC, COMM_VAR_NOINIT) inst
    = &COMM_INST_ACCESS(sc->instances,instIdx);

  ComM_HsmStateIdxType stateIdx = sc->states[inst->stateId].initId;

  DBG_COMM_HSM_INIT_SUBSTATES_ENTRY(sc, instIdx);

  while (stateIdx != COMM_HSM_SIDX_INVALID) /* init state if necessary */
  {
    P2CONST(ComM_HsmStateType, AUTOMATIC, COMM_CONST) state
      = &sc->states[stateIdx];

    inst->stateId = stateIdx; /* set new current state */
    /* enter the substate */
    if (state->entryFnIdx != COMM_HSM_AIDX_INVALID)
    {
      /* Deviation MISRA-3 */
      COMM_HSM_PRINT4(
        "%s %d %s\n",
        sc->hsmName, COMM_INST(instIdx), sc->actionNames[state->entryFnIdx]);
      sc->actions[state->entryFnIdx](COMM_PL_SF(instIdx));
    }
    /* get next init state */
    stateIdx = state->initId;
  }
  DBG_COMM_HSM_INIT_SUBSTATES_EXIT(sc, instIdx);
}

STATIC FUNC(boolean, COMM_CODE) COMM_HSM_FIND_EV_TO_DISPATCH(
  const ComM_HsmStatechartPtrType                     sc,
  const uint8                                        instIdx,
  CONSTP2VAR(ComM_HsmEventType, AUTOMATIC, AUTOMATIC) event,
  CONSTP2VAR(uint8, AUTOMATIC, AUTOMATIC)            queueEntryNo)
{
    CONSTP2VAR(ComM_HsmInstType, AUTOMATIC, COMM_VAR_NOINIT) inst
      = &COMM_INST_ACCESS(sc->instances,instIdx);
    CONSTP2CONST(ComM_HsmStateType, AUTOMATIC, COMM_CONST) state
      = &sc->states[inst->stateId];
    boolean          foundEventToDispatch = FALSE;
    ComM_HsmEventType ev                   = COMM_HSM_EVENT_INVALID;
    uint8            entryNo              = 0U;

    DBG_COMM_HSM_FIND_EV_TO_DISPATCH_ENTRY(sc, instIdx, event, queueEntryNo);

    /* lock event queue access */
    SchM_Enter_ComM_SCHM_COMM_EXCLUSIVE_AREA_0();
    while ((entryNo < inst->evQueueFill)
           && (FALSE == foundEventToDispatch))
    {
      ComM_HsmEventMaskType eventMask;
      ev        = COMM_EV_QUEUE_ENTRY(sc, instIdx, entryNo);
      eventMask = (ComM_HsmEventMaskType)1UL << ev;

      if ((eventMask & state->ignoredEventMask) != 0U)
      {
        /* Deviation MISRA-3 */
        COMM_HSM_PRINT4(
          "%s %d event %s ignored\n",
          sc->hsmName, COMM_INST(instIdx), sc->eventNames[ev]);

        /* delete event no 'entryNo' from queue */
        COMM_HSM_DEL_FROM_QUEUE(sc, instIdx, entryNo);
        /* do not increment entryNo */
      }
      else if ((eventMask & state->actionEventMask) != 0U)
      {
        if (inst->evQueueInsertEvNo <= entryNo)
        {
          /* if the insertion location is still unset (or pointing to an
           * invalid location) then set the insertion location to just after
           * the current event to be dispatched. */
          inst->evQueueInsertEvNo = entryNo + 1U;
        }
        /* leave while loop and dispatch event no entryNo */
        foundEventToDispatch = TRUE;
      }
      else
      {
        /* Deviation MISRA-3 */
        COMM_HSM_PRINT4(
          "%s %d event %s deferred\n",
          sc->hsmName, COMM_INST(instIdx), sc->eventNames[ev]);

        /* found only deferred event, try next one in queue */
        ++entryNo;
      }
    }
    SchM_Exit_ComM_SCHM_COMM_EXCLUSIVE_AREA_0();

    *event        = ev;
    *queueEntryNo = entryNo;

    DBG_COMM_HSM_FIND_EV_TO_DISPATCH_EXIT(foundEventToDispatch, sc, instIdx, event, queueEntryNo);
    return foundEventToDispatch;
}

STATIC FUNC(boolean, COMM_CODE) COMM_HSM_DISPATCH_EVENT(
  const ComM_HsmStatechartPtrType sc,
  const uint8                    instIdx,
  const ComM_HsmEventType         event)
{
  CONSTP2VAR(ComM_HsmInstType, AUTOMATIC, COMM_VAR_NOINIT) inst
    = &COMM_INST_ACCESS(sc->instances,instIdx);
  P2CONST(ComM_HsmTranType, AUTOMATIC, COMM_CONST) trans = NULL_PTR;
  /* return value, flag indicating if at least one transition fired */
  boolean transitionFired = FALSE;
  /* flag for the trigger search algorithm */
  boolean triggerFound    = FALSE;

  DBG_COMM_HSM_DISPATCH_EVENT_ENTRY(sc, instIdx, event);

  /* *** search for transition for non-deferred and non-ignored event and
   * fire the transition if found *** */

  /* Deviation MISRA-3 */
  COMM_HSM_PRINT5(
    "%s %d dispatching event %s in state %s\n",
    sc->hsmName, COMM_INST(instIdx), sc->eventNames[event],
    sc->stateNames[inst->stateId]);

  /* try current leaf state as src of transitions */
  inst->sourceId = inst->stateId;

  /* start searching for a triggering event */
  do
  {
    uint8_least i;          /* index in transition array of state */

    CONSTP2CONST(ComM_HsmStateType, AUTOMATIC, COMM_CONST) state
      = &sc->states[inst->sourceId];

    /* check all possible transitions of state */
    for (i = 0U; (i < state->numTrans) && (FALSE == triggerFound); ++i)
    {
      trans = &state->trans[i]; /* test next transition */

      if (event == trans->event)
      {
        /* evaluate guard condition */
        boolean guardCond = TRUE;

        if (trans->guardFnIdx != COMM_HSM_GIDX_INVALID)
        {
          guardCond = sc->guards[trans->guardFnIdx](COMM_PL_SF(instIdx));

          /* Deviation MISRA-3 */
          COMM_HSM_PRINT5(
            "%s %d %s evaluates to %s\n",
            sc->hsmName, COMM_INST(instIdx),
            sc->guardNames[trans->guardFnIdx], (guardCond?"TRUE":"FALSE"));
        }

        if (TRUE == guardCond)
        {
          /* exit for loop and middle do-while loop in any case because we
           * have found at least one enabled transition for this event. */
          triggerFound    = TRUE;

          /* remember that some real event processing e.g. a state machine
           * action happened. In this case a subsequent call of this or other
           * dispatching functions may be necessary */
          transitionFired = TRUE;

          /* event+guard is OK: transition action is perfomed later after
           * loops are left and stack usage is lower */
        }
        /* else: if guard is false, then treat it as if the related
         * transition is not existing in the state chart model, "Practical
         * Statecharts", 2.ed, sect. 2.3.15  */
      }
    }

    if (FALSE == triggerFound)
    {
      /* we did not find the trigger in this state: try parent state as next
       * source state */
      inst->sourceId = state->parentId;
    }
  } while ((FALSE == triggerFound)
           && (COMM_HSM_SIDX_INVALID != inst->sourceId));

  /* a triggering event was found and transition is ready to be executed or
   * the top state is reached the queued event must be ignored
   *
   * we have to check if the top state is not yet reached at runtime because
   * there may still be non-ignored and not handled events due to false
   * guard conditions */

  if (TRUE == triggerFound)
  {
    COMM_HSM_TRAN(sc, instIdx, trans); /* execute the transition */
  }
  else
  {
    /* Deviation MISRA-3 */
    COMM_HSM_PRINT4(
      "%s %d event %s ignored at top state\n",
      sc->hsmName, COMM_INST(instIdx), sc->eventNames[event]);
  }

  DBG_COMM_HSM_DISPATCH_EVENT_EXIT(transitionFired, sc, instIdx, event);
  return transitionFired;
}

#define COMM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[end of file]===========================================*/
