/**
 * \file
 *
 * \brief AUTOSAR Dem
 *
 * This file contains the implementation of the AUTOSAR
 * module Dem.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/* This file contains definitions of Dem module internal functions. */

/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 12.4 (required)
 *    "The right-hand operand of a logical '&&' or '||' operator shall not
 *    contain side effects."
 *
 *    Reason:
 *    Call to getter functions which do not modify any global state.
 *
 *  MISRA-2) Deviated Rule: 17.4 (required)
 *    "Array indexing shall be the only allowed form of pointer arithmetic."
 *
 *    Reason:
 *    In special cases pointer arithmetic is more efficient in run
 *    time and/or code size.
 *
 *  MISRA-3) Deviated Rule: 16.7 (required)
 *    "A pointer parameter in a function prototype should be declared as
 *     pointer to const if the pointer is not used to modify the
 *     addressed object."
 *
 *    Reason:
 *    Function prototype cannot be changed as it is addressed by a
 *    function pointer which refer to functions of same prototype.
 */

/*==================[inclusions]============================================*/
/* !LINKSTO dsn.Dem.IncludeStr,1 */

#include <TSAutosar.h>                        /* EB specific standard types */
#include <TSMem.h>                          /* EB specific memory functions */
#include <Std_Types.h>                            /* AUTOSAR standard types */

#include <Dem_Int.h>             /* Module public and internal declarations */
#include <Dem_Trace.h>                        /* Dbg related macros for Dem */

/* !LINKSTO dsn.Dem.SchMUsage,1 */
#include <SchM_Dem.h>             /* for the locking of the exclusive areas */

#if (DEM_TRIGGER_FIM_REPORTS == STD_ON)
#include <FiM.h>                    /* for trigger on event status callback */
#endif
#if (DEM_TRIGGER_DCM_REPORTS == STD_ON)
#include <Dcm.h>                      /* for trigger on DTC status callback */
#endif
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
#include <NvM.h>                                             /* Module APIs */
#include <Dem_NvMCbk.h>                              /* Module callback API */
#endif

/*==================[macros]================================================*/

/** \brief Internal Macro to reset passed counter, failed counter and FDC in
 ** frequency based debouncing status structure
 */
#define DEM_RESETFREQBASEDCOUNTERS(debounceStatus) do             \
  {                                                               \
    (debounceStatus)->PassedCounter = 0U;                           \
    (debounceStatus)->FailedCounter = 0U;                           \
    (debounceStatus)->Status        = DEM_EVENT_STATUS_UNQUALIFIED; \
  } while(0)

/** \brief Returns the 'DTC setting allowed' bit for a given event */
#define DEM_DTC_SETTING_ALLOWED(EventId) \
  (DEM_IS_BIT_SET(Dem_DTCSettingAllowed, \
                  (uint32)1U << (Dem_GbiDTCGroupIdx(EventId))))

/*==================[type definitions]======================================*/

/** \brief Internal data type to define the structure of one DTC lookup cache
 ** entry */
typedef struct
{
  Dem_DTCType     DTC;             /**< DTC value, key of a key/value pair **/
  Dem_EventIdType EventId;        /**< Event Id, value of a key/value pair **/
} Dem_InternalDTCCacheEntryType;

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

#define DEM_START_SEC_CODE
#include <MemMap.h>

#if (DEM_NUM_FAILURECYCLES > 0U)
/** \brief Updates failure counter on first fail report for the event in
 ** the operation cycle if failure cycle is already started
 **
 ** \param[in] EventId 1 < EventId <= DEM_MAX_EVENTID
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_UpdateFailureCounterFirstFail(
  const Dem_EventIdType     EventId,
  const Dem_EventStatusType EventStatus);
#endif

#if (DEM_C_CALLBACK_TABLE_TRIG_ON_EVST_SIZE > 0U)
/** \brief Function to get the first and the last index in a function pointer
 ** lookup table
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[in] LookupTable  function pointer lookup table
 ** \param[in] TableSize
 ** \param[out] StartIdx  first index
 ** \param[out] LastIdx  last index
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **
 ** \pre This function must only be called for events triggering a
 ** callback-function available within the selected ::LookupTable array.
 */
STATIC FUNC(void, DEM_CODE) Dem_GetCallbackIndex(
  Dem_EventIdType                                           EventId,
  CONSTP2CONST(Dem_CbLookupTableType, AUTOMATIC, DEM_CONST) LookupTable,
  uint16                                                    TableSize,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_VAR)                    StartIdx,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_VAR)                    LastIdx);
#endif

#if (DEM_RTE_CALLBACK_TABLE_TRIG_ON_EVST_SIZE > 0U)
/** \brief Function to get the first and the last index in a function pointer
 ** lookup table
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[in] LookupTable  function pointer lookup table
 ** \param[in] TableSize
 ** \param[out] StartIdx  first index
 ** \param[out] LastIdx  last index
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **
 ** \pre This function must only be called for events triggering a
 ** callback-function available within the selected ::LookupTable array.
 */
STATIC FUNC(void, DEM_CODE) Dem_GetRteCallbackIndex(
  Dem_EventIdType                                     EventId,
  CONSTP2CONST(Dem_EventIdType, AUTOMATIC, DEM_CONST) LookupTable,
  uint16                                              TableSize,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_VAR)              StartIdx,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_VAR)              LastIdx);
#endif

#if (DEM_NUM_DEBOUNCE_TIME > 0U)
/** \brief Reset internal status for time based debouncing
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 **
 ** \Reentrancy{Non Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ResetDebounceTimeBased(
  Dem_EventIdType EventId);
#endif

/** \brief Reset internal status for monitor internal debouncing
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 **
 ** \Reentrancy{Non Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ResetDebounceMonitor(Dem_EventIdType EventId);

#if (DEM_NUM_DEBOUNCE_COUNTER > 0U)
/** \brief Reset internal status for counter based debouncing
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 **
 ** \Reentrancy{Non Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ResetDebounceCounterBased(
  Dem_EventIdType EventId);
#endif

#if (DEM_NUM_DEBOUNCE_FREQUENCY > 0U)
/** \brief Reset internal status for frequency based debouncing
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 **
 ** \Reentrancy{Non Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ResetDebounceFrequencyBased(
  Dem_EventIdType EventId);
#endif

#if (DEM_NUM_DEBOUNCE_COUNTER > 0U)
/** \brief Perform counter based debouncing for a given event
 **
 ** This function is called by the APIs Dem_ReportErrorStatus() and
 ** Dem_SetEventstatus() if counter based debouncing is enabled for the
 ** reported event.
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[in,out] EventStatus  status of event, either DEM_EVENT_STATUS_PREPASSED
 **                  or DEM_EVENT_STATUS_PREFAILED
 **
 ** \Reentrancy{Non-reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_DebounceEventCounterBased(
  Dem_EventIdType                                           EventId,
  CONSTP2VAR(Dem_EventStatusType, AUTOMATIC, DEM_APPL_DATA) EventStatus);
#endif

#if (DEM_NUM_DEBOUNCE_TIME > 0U)
/** \brief Perform time based debouncing for a given event
 **
 ** This function is called by the APIs Dem_ReportErrorStatus() and
 ** Dem_SetEventstatus() if time based debouncing is enabled for the
 ** reported event.
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[in] EventStatus  status of event, either DEM_EVENT_STATUS_PREPASSED
 **              or DEM_EVENT_STATUS_PREFAILED
 **
 ** \Reentrancy{Non-reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_DebounceEventTimeBased(
  Dem_EventIdType                                           EventId,
  CONSTP2VAR(Dem_EventStatusType, AUTOMATIC, DEM_APPL_DATA) EventStatus);
#endif

#if (DEM_NUM_DEBOUNCE_FREQUENCY > 0U)
/** \brief Perform frequency based debouncing for a given event
 **
 ** This function is called by the APIs Dem_ReportErrorStatus() and
 ** Dem_SetEventstatus() if frequency based debouncing is enabled for the
 ** reported event.
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[in,out] EventStatus  status of event, either DEM_EVENT_STATUS_PREPASSED
 **                  or DEM_EVENT_STATUS_PREFAILED
 **
 ** \Reentrancy{Non-reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_DebounceEventFrequencyBased(
  Dem_EventIdType                                           EventId,
  CONSTP2VAR(Dem_EventStatusType, AUTOMATIC, DEM_APPL_DATA) EventStatus);
#endif

#if (DEM_NUM_DEBOUNCE_COUNTER > 0U)
/** \brief Return FDC for an event using counter based debouncing
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[out] FDC
 **
 ** \return E_OK if FDC could be acquired, E_NOT_OK otherwise
 **
 ** \Reentrancy{Non-reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_GetFDCCounterBased(
  Dem_EventIdType EventId,
  CONSTP2VAR(Dem_FaultDetectionCounterType, AUTOMATIC, DEM_APPL_DATA) FDC);
#endif

#if (DEM_NUM_DEBOUNCE_TIME > 0U)
/** \brief Return FDC for an event using time based debouncing
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[out] FDC
 **
 ** \return E_OK if FDC could be acquired, E_NOT_OK otherwise
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_GetFDCTimeBased(
  Dem_EventIdType EventId,
  CONSTP2VAR(Dem_FaultDetectionCounterType, AUTOMATIC, DEM_APPL_DATA) FDC);
#endif

#if (DEM_NUM_DEBOUNCE_FREQUENCY > 0U)
/** \brief Return FDC for an event using frequency based debouncing
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[out] FDC
 **
 ** \return E_OK if FDC could be acquired, E_NOT_OK otherwise
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_GetFDCFrequencyBased(
  Dem_EventIdType EventId,
  CONSTP2VAR(Dem_FaultDetectionCounterType, AUTOMATIC, DEM_APPL_DATA) FDC);
#endif

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
/** \brief Function to search for next entry to be stored immediately
 **
 ** This function is invoked from a single block callback function from NvM
 ** related to job end notifcation.
 **
 ** \param[in] originIdx
 ** \param[in,out] NvMGateStatus
 **/
STATIC FUNC(void, DEM_CODE) Dem_StoreImmediatelyNext(
  const uint8 originIdx,
  Dem_NvMGatePrepStatusPtrType NvMGateStatus);
#endif

#if (DEM_NUM_INDICATOR_LINKS > 0U)
/** \brief Function to check the condition for set WIR-status-bit of event
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[in] EventStatus  status of event, either ::DEM_EVENT_STATUS_PASSED
 **              or ::DEM_EVENT_STATUS_FAILED
 ** \param[out] WIROnCritFulfilledFlagsIdx
 **
 ** \return Boolean value indicating whether the condition for set WIR-status-bit
 **         (bit 7) is satisfied or not.
 ** \retval TRUE  condition for set WIR-status-bit is satisfied
 ** \retval FALSE condition for set WIR-status-bit is not satisfied
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 **/
STATIC FUNC(boolean, DEM_CODE) Dem_CheckForEventWIRUpdate(
  const Dem_EventIdType     EventId,
  const Dem_EventStatusType EventStatus,
  CONSTP2VAR(Dem_EventIdType, AUTOMATIC, AUTOMATIC)
    WIROnCritFulfilledFlagsIdx);
#endif /* (DEM_NUM_INDICATOR_LINKS > 0U) */

#define DEM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]====================================*/

#define DEM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief function pointer array for easy access to debouncing functions */
CONST(Dem_DebounceFctPtrTableType, DEM_CONST)
  Dem_DebounceFctPtrTable[DEM_MAXNUM_DEBOUNCECLASSES] =
{
  /* "monitor internal" debouncing - DEM_DEBOUNCE_MONITOR */
  {
    &Dem_ResetDebounceMonitor,
    NULL_PTR, /* "debounce event" function will never be called */
#if (DEM_USE_CB_GET_FDC == STD_ON)
    &Dem_CbGetFaultDetectionCounter
#else
    NULL_PTR
#endif
  },
  /* counter based debouncing - DEM_DEBOUNCE_COUNTERBASED */
  {
#if (DEM_NUM_DEBOUNCE_COUNTER > 0U)
    &Dem_ResetDebounceCounterBased,
    &Dem_DebounceEventCounterBased,
    &Dem_GetFDCCounterBased
#else
    /* counter based debouncing not used - will never be called */
    NULL_PTR, NULL_PTR, NULL_PTR
#endif
  },
  /* time based debouncing - DEM_DEBOUNCE_TIMEBASED */
  {
#if (DEM_NUM_DEBOUNCE_TIME > 0U)
    &Dem_ResetDebounceTimeBased,
    &Dem_DebounceEventTimeBased,
    &Dem_GetFDCTimeBased
#else
    /* time based debouncing not used - will never be called */
    NULL_PTR, NULL_PTR, NULL_PTR
#endif
  },
  /* frequency based debouncing - DEM_DEBOUNCE_FREQUENCYBASED */
  {
#if (DEM_NUM_DEBOUNCE_FREQUENCY > 0U)
    &Dem_ResetDebounceFrequencyBased,
    &Dem_DebounceEventFrequencyBased,
    &Dem_GetFDCFrequencyBased
#else
    /* frequency based debouncing not used - will never be called */
    NULL_PTR, NULL_PTR, NULL_PTR
#endif
  }
};

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

#define DEM_START_SEC_VAR_NO_INIT_32
#include <MemMap.h>

/** \brief DTC setting flags */
VAR(uint32, DEM_VAR_NOINIT) Dem_DTCSettingAllowed;

#define DEM_STOP_SEC_VAR_NO_INIT_32
#include <MemMap.h>

#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

#if (DEM_OPCYC_NVSTORAGE == STD_OFF)
/** \brief Array of operation cycle states */
VAR(Dem_OperationCycleStateType, DEM_VAR_NOINIT)
  Dem_OpCycleState[DEM_NUM_OPCYCLES];
#endif

#if (DEM_MAX_NUMBER_PRESTORED_FF > 0U)
/** \brief Flags to hold validity of the PFFs */
VAR(uint8, DEM_VAR_NOINIT) Dem_PFFEntryValid[
  (DEM_MAX_NUMBER_PRESTORED_FF + 7U) / 8U];
#endif

#if (DEM_NUM_DEBOUNCE_COUNTER > 0U)
/** \brief per-event status for counter based debouncing */
VAR(Dem_DebounceCounterStatusType, DEM_VAR_NOINIT)
  Dem_DebounceCounterStatus[DEM_NUM_DEBOUNCE_COUNTER];
#endif

#if (DEM_NUM_DEBOUNCE_TIME > 0U)
/** \brief per-event status for time based debouncing */
VAR(Dem_DebounceTimeStatusType, DEM_VAR_NOINIT)
  Dem_DebounceTimeStatus[DEM_NUM_DEBOUNCE_TIME];
#endif

#if (DEM_NUM_DEBOUNCE_FREQUENCY > 0U)
/** \brief per-event status for frequency based debouncing */
VAR(Dem_DebounceFrequencyStatusType, DEM_VAR_NOINIT)
  Dem_DebounceFrequencyStatus[DEM_NUM_DEBOUNCE_FREQUENCY];
#endif

#if (DEM_EVENTFAILURECOUNTER_BUFFER_SIZE > 0U)
VAR(Dem_EventFailureCycleCounterBufferType, DEM_VAR_NOINIT)
  Dem_EventFailureCycleCounterBuffer[DEM_EVENTFAILURECOUNTER_BUFFER_SIZE];
#endif

#if (DEM_NUM_EVENT_INDICATOR_USED > 0U)
/** \brief Flags to hold the status of WIR On-Criteria */
VAR(uint8, DEM_VAR_NOINIT) Dem_WIROnCriteriaFulfilledFlags[
  (DEM_NUM_EVENT_INDICATOR_USED + 7U) / 8U];
#endif

#if (DEM_NUM_BSWEVENT_INDICATOR_USED > 0U)
/** \brief Flags to hold the status of BSW event WIR-status-bit */
VAR(uint8, DEM_VAR_NOINIT) Dem_BSWEventWIRStatusFlags[
  (DEM_NUM_BSWEVENT_INDICATOR_USED + 7U) / 8U];
#endif

#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

#define DEM_START_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief Status of the Dem  */
VAR(Dem_InitializationStateType, DEM_VAR) Dem_InitializationState =
  DEM_UNINITIALIZED;

#define DEM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[internal data]=========================================*/

#define DEM_START_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief DTC cache, stores temporary results of DTC lookup operation.
 **
 ** Used by \sa Dem_GetEvIdByDTC */
STATIC VAR(Dem_InternalDTCCacheEntryType, DEM_VAR) Dem_DTCCache =
{
  0U, DEM_NUMBER_OF_EVENTS
};

#define DEM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>


/*==================[external function definitions]=========================*/

#define DEM_START_SEC_CODE
#include <MemMap.h>

/*------------------[perform "timer tick" for all running timers]-----------*/

#if (DEM_NUM_DEBOUNCE_FREQUENCY > 0U)
FUNC(void, DEM_CODE) Dem_DebounceFrequencyTimerTick(void)
{
  Dem_EventIdType DebounceIdx;

  DBG_DEM_DEBOUNCEFREQUENCYTIMERTICK_ENTRY();

  /*
   * ENTER critical section to protect debounce status
   *       call-context: any
   */
  SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

  for (DebounceIdx = 0U;
       DebounceIdx < DEM_NUM_DEBOUNCE_FREQUENCY;
       DebounceIdx++)
  {
    CONSTP2CONST(Dem_DebounceFrequencyCfgType, AUTOMATIC, DEM_CONST)
      DebounceCfg = &Dem_DebounceFrequencyCfg[DebounceIdx];
    const Dem_EventIdType EventId = DebounceCfg->EventId;

    if (DEM_OPCYCLESTATE[Dem_GbiOpCycleIdx(EventId)] != DEM_CYCLE_STATE_END)
    {
      CONSTP2VAR(Dem_DebounceFrequencyStatusType, AUTOMATIC, DEM_VAR_NOINIT)
        DebounceStatus = &Dem_DebounceFrequencyStatus[DebounceIdx];

      if (DebounceStatus->InternalTimer != 0U)
      {
        /* timer running -> decrease timer */
        DebounceStatus->InternalTimer--;

        if (DebounceStatus->InternalTimer == 0U)
        {
          /* timer did expire */
          /* if neither threshold is reached within the time window, the
           * event is 'unqualified' (readiness is not set) */
          DebounceStatus->Status = DEM_EVENT_STATUS_UNQUALIFIED;
        }
      }
    }
  } /* for (every frequency based debounced event) */

  /*
   * LEAVE critical section
   */
  SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

  DBG_DEM_DEBOUNCEFREQUENCYTIMERTICK_EXIT();
}
#endif /* (DEM_NUM_DEBOUNCE_FREQUENCY > 0U) */

#if (DEM_NUM_DEBOUNCE_TIME > 0U)
FUNC(void, DEM_CODE) Dem_DebounceTimeTimerTick(void)
{
  Dem_EventIdType DebounceIdx;
  Dem_EventIdType DebounceStartIdx = 0U;

  DBG_DEM_DEBOUNCETIMETIMERTICK_ENTRY();

  do
  {
    Dem_EventStatusType EventDebounceStatus = DEM_EVENT_STATUS_UNQUALIFIED;

    /*
     * ENTER critical section to protect debounce status
     *       call-context: any
     */
    SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

    for (DebounceIdx = DebounceStartIdx;
         DebounceIdx < DEM_NUM_DEBOUNCE_TIME;
         ++DebounceIdx)
    {
      const Dem_OperationCycleIdType OpCycleIdx =
        Dem_GbiOpCycleIdx(Dem_DebounceTimeCfg[DebounceIdx].EventId);

      if (DEM_OPCYCLESTATE[OpCycleIdx] != DEM_CYCLE_STATE_END)
      {
        CONSTP2VAR(Dem_DebounceTimeStatusType, AUTOMATIC, DEM_VAR_NOINIT)
          DebounceStatus = &Dem_DebounceTimeStatus[DebounceIdx];

        if (DebounceStatus->InternalTimer != 0U)
        {
          /* timer running -> decrease timer */
          DebounceStatus->InternalTimer--;

          if (DebounceStatus->InternalTimer == 0U)
          {
            /* debouncing complete -> save event status to be used outside of
             * critical section */
            EventDebounceStatus = DebounceStatus->Direction;
            /* increment and save current index to continue later */
            DebounceStartIdx = DebounceIdx;
            /* break from search loop to process event status */
            break;
          }
        }
      }
    } /* for (every time based debounced event) */

    /*
     * LEAVE critical section
     */
    SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

    /* check if search loop has completed debouncing for an event */
    if (EventDebounceStatus != DEM_EVENT_STATUS_UNQUALIFIED)
    {
      /* note: Dem_InternalSetEventStatus(PASSED|FAILED) will call
       * Dem_DebounceEventTimeBased() for the event, which in
       * turn will reset the debouncing status */
      Std_ReturnType SetStatusResult =
        Dem_InternalSetEventStatus(Dem_DebounceTimeCfg[DebounceIdx].EventId,
                                   EventDebounceStatus);

      if (SetStatusResult == E_NOT_OK)
      { /* !LINKSTO Dem.DebounceTimeBased.Reset,1 */
        const Dem_EventIdType EventId =
          Dem_DebounceTimeCfg[DebounceIdx].EventId;
        CONSTP2VAR(Dem_DebounceTimeStatusType, AUTOMATIC, DEM_VAR_NOINIT)
          DebounceStatus = &Dem_DebounceTimeStatus[DebounceIdx];

        /* The qualification of the event was ignored. DebounceStatus->
         * Direction shall be reset to the current event status.
         * In this way, next time when Dem_DebounceEventTimeBased will be
         * called, the timer and the direction will be reset correctly, but
         * also the value returned by Dem_GetFDCTimeBased will be aligned to
         * the current status of the event.
         * Since the fault detection counter is reset upon starting a new
         * operation cycle (according to Dem344), for debouncing algorithm is
         * relevant only the status of the event during the current operation
         * cycle.
         */

        /*
         * ENTER critical section to protect debounce status
         *       call-context: any
         */
        SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

        if (DEM_IS_BIT_SET(DEM_DTC_STATUS_MASKS[EventId], DEM_UDS_STATUS_TNCTOC))
        {
          /* the event was not qualified this operation cycle */
          DebounceStatus->Direction = DEM_EVENT_STATUS_UNQUALIFIED;
        }
        else
        {
          if (DEM_IS_BIT_SET(DEM_DTC_STATUS_MASKS[EventId], DEM_UDS_STATUS_TF))
          {
            /* the event was qualified as failed this operation cycle */
            DebounceStatus->Direction = DEM_EVENT_STATUS_FAILED;
          }
          else
          {
            /* the event was qualified as passed this operation cycle */
            DebounceStatus->Direction = DEM_EVENT_STATUS_PASSED;
          }
        }

        /*
         * LEAVE critical section to protect debounce status
         */
        SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();
      }
      else
      {
#if (DEM_DEV_ERROR_DETECT == STD_ON)
        if (SetStatusResult == DEM_E_DET_REPORT)
        {
          /* error-queue overflow happened */
          DEM_REPORT_ERROR(DEM_SID_MainFunction, DEM_E_PARAM_CONFIG);
        }
        else
        {
          /* Do nothing. */
        }
#else
        /* Do nothing. */
#endif /* DEM_DEV_ERROR_DETECT */
      }
    }

  } while (DebounceIdx < DEM_NUM_DEBOUNCE_TIME);

  DBG_DEM_DEBOUNCETIMETIMERTICK_EXIT();
}
#endif /* (DEM_NUM_DEBOUNCE_TIME > 0U) */

/*------------------[internal core-function definitions]--------------------*/

FUNC(uint32, DEM_CODE) Dem_GbiDTC(const Dem_EventIdType EventId)
{
  uint32 DTC = DEM_BIT_FIELD_VALUE_32(Dem_EventDesc[EventId].EvConf1,
                    DEM_UDS_DTC_OFFSET, DEM_UDS_DTC_MASK);

#if ( (DEM_USE_DYNAMIC_DTCS == STD_ON) && \
      (DEM_DEV_ERROR_DETECT == STD_ON) )
  sint16 RetGrpIndex = (sint16)DEM_NUM_DTC_GROUPS - 1;
  sint16 CfgGrpIndex = (sint16)Dem_GbiDTCGroupIdx(EventId);
  boolean EntryFound = FALSE;
#endif

  DBG_DEM_GBIDTC_ENTRY(EventId);

#if (DEM_USE_DYNAMIC_DTCS == STD_ON)
  /* Enter only if a DTC is configured for event */
  if (DTC != DEM_NO_DTC)
  {
    /* !LINKSTO Dem.DTCConfiguration.GetDynamic,1 */
    DTC = DEM_GET_DYNAMIC_DTC(EventId, DTC);

#if (DEM_DEV_ERROR_DETECT == STD_ON)

    /* Search for the index of DTC group of returned DTC. Searching uses the
       configured DTC group array sorted in ascending order of DTC
       group value. */
    do
    {
      if (DTC > Dem_DTCGroups[RetGrpIndex])
      {
        EntryFound = TRUE;
      }
      else
      {
        RetGrpIndex--;
      }
    }
    while ( (RetGrpIndex >= 0) && (EntryFound != TRUE) );

    if (RetGrpIndex != CfgGrpIndex)
    {
      DEM_REPORT_ERROR(DEM_SID_CalloutDynamicDTCFnc, DEM_E_INTEGRATION);
      DTC = 0U;
    }
#endif /* DEM_DEV_ERROR_DETECT */
  }
#endif /* DEM_USE_DYNAMIC_DTCS */

  DBG_DEM_GBIDTC_EXIT(DTC, EventId);
  return DTC;
}

FUNC(Dem_DTCKindType, DEM_CODE) Dem_GbiDTCKind(const Dem_EventIdType EventId)
{
  DBG_DEM_GBIDTCKIND_ENTRY(EventId);

  /* Function NOT fully implemented yet since there is no OBD support.
   * Implementation is scheduled for future releases. */

  TS_PARAM_UNUSED(EventId);

  DBG_DEM_GBIDTCKIND_EXIT(DEM_DTC_KIND_ALL_DTCS, EventId);
  return DEM_DTC_KIND_ALL_DTCS;
}

FUNC(Dem_DTCOriginType, DEM_CODE) Dem_GbiDTCOrigin(
  const Dem_EventIdType EventId)
{
  /* the 4 different AUTOSAR values of DTC Origin are packed into two bytes in
     event description, therefore these values are transformed */
  const Dem_DTCOriginType result =
    (Dem_DTCOriginType)(
      DEM_BIT_FIELD_VALUE_32(
        Dem_EventDesc[EventId].EvConf1,
        DEM_DTCORIGIN_OFFSET,
        DEM_DTCORIGIN_MASK) +
      1U); /* unpacking */

  DBG_DEM_GBIDTCORIGIN_ENTRY(EventId);

  DBG_DEM_GBIDTCORIGIN_EXIT(result, EventId);
  return result;
}

FUNC(uint8, DEM_CODE) Dem_GbiDTCOriginIdx(
  const Dem_EventIdType EventId)
{
  const uint8 result = (uint8)DEM_BIT_FIELD_VALUE_32(
                                Dem_EventDesc[EventId].EvConf1,
                                DEM_DTCORIGIN_OFFSET,
                                DEM_DTCORIGIN_MASK);

  DBG_DEM_GBIDTCORIGINIDX_ENTRY(EventId);

  DBG_DEM_GBIDTCORIGINIDX_EXIT(result, EventId);
  return result;
}

FUNC(uint8, DEM_CODE) Dem_GbiDTCGroupIdx(const Dem_EventIdType EventId)
{
  const uint8 result =
    (uint8)DEM_BIT_FIELD_VALUE_32(
      Dem_EventDesc[EventId].EvConf1,
      DEM_DTCGROUP_OFFSET,
      DEM_DTCGROUP_MASK);

  DBG_DEM_GBIDTCGROUPIDX_ENTRY(EventId);

  DBG_DEM_GBIDTCGROUPIDX_EXIT(result, EventId);
  return result;
}

FUNC(boolean, DEM_CODE) Dem_GbiImmediateStorage(
  const Dem_EventIdType EventId)
{
  const boolean result =
    (boolean)DEM_BIT_FIELD_VALUE_32(
      Dem_EventDesc[EventId].EvConf1,
      DEM_IMMEDIATESTORAGE_OFFSET,
      DEM_IMMEDIATESTORAGE_MASK);

  DBG_DEM_GBIIMMEDIATESTORAGE_ENTRY(EventId);

  DBG_DEM_GBIIMMEDIATESTORAGE_EXIT(result, EventId);
  return result;
}

FUNC(Dem_DTCSeverityType, DEM_CODE) Dem_GbiDTCSeverity(
  const Dem_EventIdType EventId)
{
  const uint8 sevNo =
    (uint8)DEM_BIT_FIELD_VALUE_32(Dem_EventDesc[EventId].EvConf2,
                                  DEM_DTCSEVERITY_OFFSET,
                                  DEM_DTCSEVERITY_MASK);

  /* this number to severity code translation must match to the configuration
   * in Dem_Cfg.c */
  const Dem_DTCSeverityType result =
    (Dem_DTCSeverityType)(
      (sevNo == 0U) ? DEM_SEVERITY_NO_SEVERITY :
      ( (sevNo == 1U) ? DEM_SEVERITY_MAINTENANCE_ONLY :
        ( (sevNo == 2U) ? DEM_SEVERITY_CHECK_AT_NEXT_HALT :
          DEM_SEVERITY_CHECK_IMMEDIATELY) ) );

  DBG_DEM_GBIDTCSEVERITY_ENTRY(EventId);

  DBG_DEM_GBIDTCSEVERITY_EXIT(result, EventId);
  return result;
}

FUNC(uint8, DEM_CODE) Dem_GbiDTCFunctionalUnit(const Dem_EventIdType EventId)
{
  const uint8 result =
    (uint8)DEM_BIT_FIELD_VALUE_32(
      Dem_EventDesc[EventId].EvConf3,
      DEM_DTCFUNCTIONALUNIT_OFFSET,
      DEM_DTCFUNCTIONALUNIT_MASK);

  DBG_DEM_GBIDTCFUNCTIONALUNIT_ENTRY(EventId);

  DBG_DEM_GBIDTCFUNCTIONALUNIT_EXIT(result, EventId);
  return result;
}

FUNC(boolean, DEM_CODE) Dem_GbiEnablePrestorage(const Dem_EventIdType EventId)
{
  const boolean result =
    (boolean)DEM_BIT_FIELD_VALUE_32(
      Dem_EventDesc[EventId].EvConf2,
      DEM_ENABLEPRESTORAGE_OFFSET,
      DEM_ENABLEPRESTORAGE_MASK);

  DBG_DEM_GBIENABLEPRESTORAGE_ENTRY(EventId);

  DBG_DEM_GBIENABLEPRESTORAGE_EXIT(result, EventId);
  return result;
}

FUNC(Dem_FFClassIdxType, DEM_CODE) Dem_GbiFFClassIdx(
  const Dem_EventIdType EventId)
{
  const Dem_FFClassIdxType result =
    (Dem_FFClassIdxType)DEM_BIT_FIELD_VALUE_32(
      Dem_EventDesc[EventId].EvConf2,
      DEM_FFCLASSIDX_OFFSET,
      DEM_FFCLASSIDX_MASK);

  DBG_DEM_GBIFFCLASSIDX_ENTRY(EventId);

  DBG_DEM_GBIFFCLASSIDX_EXIT(result, EventId);
  return result;
}

#if (DEM_NUM_FFSEGS > 0U)
FUNC(Dem_FFIdxType, DEM_CODE) Dem_GbiMaxNumFFRecs(
  const Dem_EventIdType EventId)
{
  Dem_FFIdxType result;

  DBG_DEM_GBIMAXNUMFFRECS_ENTRY(EventId);

#if (DEM_FREEZE_FRAME_REC_NUMERATION_TYPE == DEM_FF_RECNUM_CALCULATED)
  result =
    (Dem_FFIdxType)DEM_BIT_FIELD_VALUE_32(
      Dem_EventDesc[EventId].EvConf2,
      DEM_FFRECINFO_OFFSET,
      DEM_FFRECINFO_MASK);
#else
  result =
    Dem_FFRecNumerationClass[Dem_GbiFFRecNumClassIdx(EventId)].NumFFRecs;
#endif

  DBG_DEM_GBIMAXNUMFFRECS_EXIT(result, EventId);
  return result;
}
#endif /* (DEM_NUM_FFSEGS > 0U) */
#if (DEM_FREEZE_FRAME_REC_NUMERATION_TYPE == DEM_FF_RECNUM_CONFIGURED)
FUNC(Dem_FFIdxType, DEM_CODE) Dem_GbiFFRecNumClassIdx(
  const Dem_EventIdType EventId)
{
  const Dem_FFClassIdxType result =
    (Dem_FFIdxType)DEM_BIT_FIELD_VALUE_32(
      Dem_EventDesc[EventId].EvConf2,
      DEM_FFRECINFO_OFFSET,
      DEM_FFRECINFO_MASK);

  DBG_DEM_GBIFFRECNUMCLASSIDX_ENTRY(EventId);

  DBG_DEM_GBIFFRECNUMCLASSIDX_EXIT(result, EventId);
  return result;
}
#endif /* (DEM_FREEZE_FRAME_REC_NUMERATION_TYPE == DEM_FF_RECNUM_CONFIGURED) */

FUNC(Dem_EDClassIdxType, DEM_CODE) Dem_GbiEDClassIdx(
  const Dem_EventIdType EventId)
{
  const Dem_EDClassIdxType result =
    (Dem_EDClassIdxType)DEM_BIT_FIELD_VALUE_32(
      Dem_EventDesc[EventId].EvConf2,
      DEM_EDCLASSIDX_OFFSET,
      DEM_EDCLASSIDX_MASK);

  DBG_DEM_GBIEDCLASSIDX_ENTRY(EventId);

  DBG_DEM_GBIEDCLASSIDX_EXIT(result, EventId);
  return result;
}

FUNC(Dem_OperationCycleIdType, DEM_CODE) Dem_GbiOpCycleIdx(
  const Dem_EventIdType EventId)
{
  const Dem_OperationCycleIdType result =
    (Dem_OperationCycleIdType)DEM_BIT_FIELD_VALUE_32(
      Dem_EventDesc[EventId].EvConf2,
      DEM_OPCYCLEIDX_OFFSET,
      DEM_OPCYCLEIDX_MASK);

  DBG_DEM_GBIOPCYCLEIDX_ENTRY(EventId);

  DBG_DEM_GBIOPCYCLEIDX_EXIT(result, EventId);
  return result;
}

#if (DEM_USE_AGING == STD_ON)
FUNC(Dem_AgingCyclesType, DEM_CODE) Dem_GbiNumAgingCycles(
  const Dem_EventIdType EventId)
{
  const Dem_AgingCyclesType result =
    (Dem_AgingCyclesType)DEM_BIT_FIELD_VALUE_32(
      Dem_EventDesc[EventId].EvConf2,
      DEM_AGINGCYCLES_OFFSET,
      DEM_AGINGCYCLES_MASK);

  DBG_DEM_GBINUMAGINGCYCLES_ENTRY(EventId);

  DBG_DEM_GBINUMAGINGCYCLES_EXIT(result, EventId);
  return result;
}
#endif

#if (DEM_NUM_AGINGCYCLES > 0U)
FUNC(Dem_OperationCycleIdType, DEM_CODE) Dem_GbiAgingCycleIdx(
  const Dem_EventIdType EventId)
{
  /* calculate absolute aging cycle Id/index */
  const Dem_OperationCycleIdType result =
    (Dem_OperationCycleIdType)(
      DEM_BIT_FIELD_VALUE_32(
        Dem_EventDesc[EventId].EvConf3,
        DEM_AGINGCYCLEIDX_OFFSET,
        DEM_AGINGCYCLEIDX_MASK) +
      DEM_NUM_OPCYCLES);

  DBG_DEM_GBIAGINGCYCLEIDX_ENTRY(EventId);

  DBG_DEM_GBIAGINGCYCLEIDX_EXIT(result, EventId);
  return result;
}
#endif

#if (DEM_NUM_ENCOND_LINKS > 0U)
FUNC(Dem_EnCondLnkIdxType, DEM_CODE) Dem_GbiEnCondLnkIdx(
  const Dem_EventIdType EventId)
{
  const Dem_EnCondLnkIdxType result =
    (Dem_EnCondLnkIdxType)DEM_BIT_FIELD_VALUE_32(
      Dem_EventDesc[EventId].EvConf3,
      DEM_ENCONDIDX_OFFSET,
      DEM_ENCONDIDX_MASK);

  DBG_DEM_GBIENCONDLNKIDX_ENTRY(EventId);

  DBG_DEM_GBIENCONDLNKIDX_EXIT(result, EventId);
  return result;
}

FUNC(Dem_EnableConditionIdType, DEM_CODE) Dem_GbiNumEnCond(
  const Dem_EventIdType EventId)
{
  const Dem_EnableConditionIdType result =
    (Dem_EnableConditionIdType)DEM_BIT_FIELD_VALUE_32(
      Dem_EventDesc[EventId].EvConf3,
      DEM_NUMENCOND_OFFSET,
      DEM_NUMENCOND_MASK);

  DBG_DEM_GBINUMENCOND_ENTRY(EventId);

  DBG_DEM_GBINUMENCOND_EXIT(result, EventId);
  return result;
}
#endif

FUNC(boolean, DEM_CODE) Dem_GbiIndicatorUsed(const Dem_EventIdType EventId)
{
  const boolean result =
    (boolean)DEM_BIT_FIELD_VALUE_32(
      Dem_EventDesc[EventId].EvConf3,
      DEM_INDICATORUSED_OFFSET,
      DEM_INDICATORUSED_MASK);

  DBG_DEM_GBIINDICATORUSED_ENTRY(EventId);

  DBG_DEM_GBIINDICATORUSED_EXIT(result, EventId);
  return result;
}

#if (DEM_USE_EVENT_DISPLACEMENT == STD_ON)
FUNC(Dem_PriorityType, DEM_CODE) Dem_GbiPriority(
  const Dem_EventIdType EventId)
{
  const Dem_PriorityType result =
    (Dem_PriorityType)DEM_BIT_FIELD_VALUE_32(
      Dem_EventDesc[EventId].EvConf3,
      DEM_PRIORITY_OFFSET,
      DEM_PRIORITY_MASK);

  DBG_DEM_GBIPRIORITY_ENTRY(EventId);

  DBG_DEM_GBIPRIORITY_EXIT(result, EventId);
  return result;
}
#endif

FUNC(Dem_DebounceType, DEM_CODE) Dem_GbiDebounceAlgo(
  const Dem_EventIdType EventId)
{
  const Dem_DebounceType result =
    (Dem_DebounceType)DEM_BIT_FIELD_VALUE_32(
      Dem_EventDesc[EventId].EvConf3,
      DEM_DEBOUNCEALGO_OFFSET,
      DEM_DEBOUNCEALGO_MASK);

  DBG_DEM_GBIDEBOUNCEALGO_ENTRY(EventId);

  DBG_DEM_GBIDEBOUNCEALGO_EXIT(result, EventId);
  return result;
}

FUNC(Dem_EventIdType, DEM_CODE) Dem_GbiDebounceIdx(
  const Dem_EventIdType EventId)
{
  const Dem_EventIdType result =
    (Dem_EventIdType)DEM_BIT_FIELD_VALUE_32(
      Dem_EventDesc[EventId].EvConf3,
      DEM_DEBOUNCEIDX_OFFSET,
      DEM_DEBOUNCEIDX_MASK);

  DBG_DEM_GBIDEBOUNCEIDX_ENTRY(EventId);

  DBG_DEM_GBIDEBOUNCEIDX_EXIT(result, EventId);
  return result;
}

FUNC(Dem_EventKindType, DEM_CODE) Dem_GbiEventKind(
  const Dem_EventIdType EventId)
{
  const Dem_EventKindType result =
    (Dem_EventKindType)DEM_BIT_FIELD_VALUE_32(
      Dem_EventDesc[EventId].EvConf2,
      DEM_EVENTKIND_OFFSET,
      DEM_EVENTKIND_MASK);

  DBG_DEM_GBIEVENTKIND_ENTRY(EventId);

  DBG_DEM_GBIEVENTKIND_EXIT(result, EventId);
  return result;
}

FUNC(uint8, DEM_CODE) Dem_GbiEventFailureClassIdx(
  const Dem_EventIdType EventId)
{
  const uint8 result =
    (uint8)DEM_BIT_FIELD_VALUE_32(
      Dem_EventDesc[EventId].EvConf2,
      DEM_EVENTFAILURECLASSIDX_OFFSET,
      DEM_EVENTFAILURECLASSIDX_MASK);

  DBG_DEM_GBIEVENTFAILURECLASSIDX_ENTRY(EventId);

  DBG_DEM_GBIEVENTFAILURECLASSIDX_EXIT(result, EventId);
  return result;
}

#if (DEM_MAX_NUMBER_PRESTORED_FF > 0U)
FUNC(Dem_EventIdType, DEM_CODE) Dem_GetPFFIndex(Dem_EventIdType EventId)
{
  Dem_EventIdType result = 0U;

  Dem_EventIdType EvId;

  DBG_DEM_GETPFFINDEX_ENTRY(EventId);

  /* check if there are PFFs in front of the target PFF */
  for (EvId = 0U; EvId < EventId; ++EvId)
  {
    if (Dem_GbiEnablePrestorage(EvId) == TRUE)
    {
      ++result;
    }
  }

  DBG_DEM_GETPFFINDEX_EXIT(result, EventId);
  return result;
}
#endif

#if (DEM_NUM_INDICATOR_LINKS > 0U)
FUNC(Dem_EventIdType, DEM_CODE) Dem_GetWIROnCriteriaFulfilledFlagsIdx(
  Dem_EventIdType EventId)
{
  Dem_EventIdType index;

  DBG_DEM_GETWIRONCRITERIAFULFILLEDFLAGSIDX_ENTRY(EventId);

  /* check if there are WIR On-Criteria fulfilled flags in front of the target
   * WIR On-Criteria fulfilled flag */

  /* CHECK: NOPARSE */
  /* Condition "index == DEM_NUM_EVENT_INDICATOR_USED" is unreachable */
  for (index = 0U; index < DEM_NUM_EVENT_INDICATOR_USED; ++index)
  {
    if (Dem_EventIndicatorUsed[index] == EventId)
    {
      break;
    }
  }
  /* CHECK: PARSE */
  DBG_DEM_GETWIRONCRITERIAFULFILLEDFLAGSIDX_EXIT(index, EventId);
  return index;
}
#endif

#if (DEM_NUM_BSWEVENT_INDICATOR_USED > 0U)
FUNC(Dem_EventIdType, DEM_CODE) Dem_GetBSWEventWIRStatusFlagsIndex(
  const Dem_EventIdType EventId)
{
  Dem_EventIdType index;

  DBG_DEM_GETBSWEVENTWIRSTATUSFLAGSINDEX_ENTRY(EventId);

  /* check if there are BSW event WIR status flags in front of the target
   * BSW event WIR status flag */
  for (index = 0U; index < DEM_NUM_BSWEVENT_INDICATOR_USED; ++index)
  {
    if (Dem_BSWEventIndicatorUsed[index] == EventId)
    {
      break;
    }
  }

  DBG_DEM_GETBSWEVENTWIRSTATUSFLAGSINDEX_EXIT(index, EventId);
  return index;
}
#endif

FUNC(Dem_ReturnGetEvIdByDTCType, DEM_CODE) Dem_GetEvIdByDTC(
  Dem_DTCType                                     DTC,
  Dem_DTCFormatType                               DTCFormat,
  Dem_DTCOriginType                               DTCOrigin,
  CONSTP2VAR(Dem_EventIdType, AUTOMATIC, DEM_VAR) EventId)
{
  Dem_ReturnGetEvIdByDTCType result = DEM_EIBD_WRONG_DTC;

  Dem_EvIdLeastType EvId = 1U; /* invalid event Id 0 is skipped */

  DBG_DEM_GETEVIDBYDTC_ENTRY(DTC, DTCFormat, DTCOrigin, EventId);

  /* DTC origin is not supported */
  if (Dem_SizeEventMem[DTCOrigin - 1U] == (Dem_SizeEvMemEntryType)0U)
  {
    result = DEM_EIBD_WRONG_DTCORIGIN;
  }
  /* CHECK: NOPARSE */
  else if (DTCFormat == DEM_DTC_FORMAT_OBD)
  {
    /* DTCFormat DEM_DTC_FORMAT_OBD which is not supported and currently not used */
    DEM_UNREACHABLE_CODE_ASSERT(DEM_INTERNAL_API_ID);
    /* result remains DEM_EIBD_WRONG_DTC */
  }
  /* CHECK: PARSE */
  else /* DTC origin is supported */
  {
    /* Dem.GetEvIdByDTC.RunTimeOptimization */
    /* check the DTC cache for results from earlier queries */
    if (DTC == Dem_DTCCache.DTC)
    {
      /* DTC cached, read appropriate EventId */
      EvId = Dem_DTCCache.EventId;
    }
    else
    {
      /* DTC not cached, search for event Id of unique DTC */
      /* check EvId first (left-hand), before using it (right-hand) */
      while ( (EvId <= DEM_MAX_EVENTID) &&
              /* Deviation MISRA-1 <+2> */
              (DTC != Dem_GbiDTC((Dem_EventIdType)EvId))
            )
      {
        ++EvId;
      }

      /* Store the result of this search operation in DTC cache including
       * unsuccessful searches. */
      Dem_DTCCache.DTC = DTC;
      Dem_DTCCache.EventId = (Dem_EventIdType)EvId;
    }

    /* DTC matches to the current event Id */
    if (EvId <= DEM_MAX_EVENTID)
    {
      /* check DTC origin */
      if (DTCOrigin == Dem_GbiDTCOrigin((Dem_EventIdType)EvId))
      {
        *EventId = (Dem_EventIdType)EvId;

        /* fully matching entry found */
        result = DEM_EIBD_OK;
      }
      /* else: DTC origin does not match:
       * result remains DEM_EIBD_WRONG_DTC */
    }
  }

  /* not necessary to set EventId = DEM_EVENT_ID_INVALID,
   * if result != DEM_EIBD_OK */

  DBG_DEM_GETEVIDBYDTC_EXIT(result, DTC, DTCFormat, DTCOrigin, EventId);
  return result;
}

FUNC(boolean, DEM_CODE) Dem_SearchForEntry(
  Dem_EventIdType                                               EventId,
  CONSTP2VAR(Dem_EventMemoryEntryPtrType, AUTOMATIC, AUTOMATIC) FoundEntry,
  CONSTP2VAR(Dem_SizeEvMemEntryType, AUTOMATIC, AUTOMATIC)      FoundEntryIdx)
{
  boolean result = FALSE;

  const uint8 originIdx = Dem_GbiDTCOriginIdx(EventId);
  const Dem_SizeEvMemEntryType sizeEventMem = Dem_SizeEventMem[originIdx];

  Dem_SizeEvMemEntryType index;
  Dem_EventMemoryEntryPtrType Entry = Dem_EventMem[originIdx];

  DBG_DEM_SEARCHFORENTRY_ENTRY(EventId, FoundEntry, FoundEntryIdx);

  /* search for entry with given event id */
  for (index = 0U; index < sizeEventMem; ++index)
  {
    if (Entry[index].EventId == EventId)
    {
      break;
    }
  }

  if (index < sizeEventMem)
  {
    if (NULL_PTR != FoundEntry)
    {
      *FoundEntry = &Entry[index];
    }

    if (NULL_PTR != FoundEntryIdx)
    {
      *FoundEntryIdx = index;
    }

    result = TRUE;
  }

  DBG_DEM_SEARCHFORENTRY_EXIT(result, EventId, FoundEntry, FoundEntryIdx);
  return result;
}

#if (DEM_NUM_FFSEGS > 0U)
FUNC(Dem_FFSegIdxType, DEM_CODE) Dem_FindDIDIndex(
  CONSTP2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) FFClass,
  const uint16                                        DataId)
{
  Dem_FFSegIdxType SegIndex;

  DBG_DEM_FINDDIDINDEX_ENTRY(FFClass, DataId);

  for (SegIndex = 0U; SegIndex < FFClass->NumFFSegs; ++SegIndex)
  {
    if (Dem_FFSegment[FFClass->FFSegIdx[SegIndex]].DataId == DataId)
    {
      break;
    }
  }

  DBG_DEM_FINDDIDINDEX_EXIT(SegIndex, FFClass, DataId);
  return SegIndex;
}
#endif /* (DEM_NUM_FFSEGS > 0U) */

#if (DEM_NUM_FFSEGS > 0U)
FUNC(Dem_EntryDataPtrType, DEM_CODE) Dem_FFEntryData(
  const Dem_EventMemoryEntryPtrConstType              EvMemEntry,
  CONSTP2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) FFClass,
  const Dem_FFIdxType                                 FFIndex)
{
  const Dem_EventIdType EventId = EvMemEntry->EventId;

#if (DEM_NUM_EDSEGS > 0U)
  /* get extended data class layout */
  CONSTP2CONST(Dem_EDClassType, AUTOMATIC, DEM_CONST) EDClass =
    &Dem_EDClass[Dem_GbiEDClassIdx(EventId)];
#endif

  /* calculate start position of the needed FF */
  const Dem_SizeEntryDataType StartPos = EvMemEntry->EntryDataPos +
#if (DEM_USE_INT_VAL_AREA == STD_ON)
    Dem_SizeOfIntValArea(EventId) +
#endif
#if (DEM_NUM_EDSEGS > 0U)
    Dem_SizeOfED(EDClass) +
#endif
    ((Dem_SizeEntryDataType)Dem_SizeOfFF(FFClass) * FFIndex);

  const uint8 originIdx = Dem_GbiDTCOriginIdx(EventId);
  const Dem_EntryDataPtrType result = &Dem_EntryData[originIdx][StartPos];

  DBG_DEM_FFENTRYDATA_ENTRY(EvMemEntry, FFClass, FFIndex);

  DBG_DEM_FFENTRYDATA_EXIT(result, EvMemEntry, FFClass, FFIndex);
  return result;
}

#if (DEM_FREEZE_FRAME_REC_NUMERATION_TYPE == DEM_FF_RECNUM_CONFIGURED)
FUNC(boolean, DEM_CODE) Dem_CheckFFRecNumValid(
  const Dem_EventIdType EventId,
  const uint8           RecordNumber)
{
  uint8 FFRecNumIdx;
  boolean result = FALSE;

  const Dem_FFIdxType FFRecNumClassIdx = Dem_GbiFFRecNumClassIdx(EventId);
  const Dem_FFIdxType NumFF =
    Dem_FFRecNumerationClass[FFRecNumClassIdx].NumFFRecs;
  CONSTP2CONST(Dem_FFIdxType, AUTOMATIC, DEM_CONST) FFRecNumClass =
    Dem_FFRecNumerationClass[FFRecNumClassIdx].Dem_FFRecNumClassIdx;

  DBG_DEM_CHECKFFRECNUMVALID_ENTRY(EventId, RecordNumber);

  for (FFRecNumIdx = 0U; FFRecNumIdx < NumFF; FFRecNumIdx++)
  {
    /* check whether the requested record number is valid for the record
     * number class*/
    if (RecordNumber == FFRecNumClass[FFRecNumIdx])
    {
      result = TRUE;
      break;
    }
  }

  DBG_DEM_CHECKFFRECNUMVALID_EXIT(result, EventId, RecordNumber);
  return result;
}

FUNC(uint8, DEM_CODE) Dem_CheckFFRecNumStored(
  const Dem_EventMemoryEntryPtrConstType EvMemEntry,
  const uint8                            RecordNumber)
{
  uint8 FFRecNumIdx = 0U;

  const Dem_FFIdxType FFRecNumClassIdx =
    Dem_GbiFFRecNumClassIdx(EvMemEntry->EventId);
  const Dem_FFIdxType NumFF =
    DEM_NUMFF(EvMemEntry,
              Dem_FFRecNumerationClass[FFRecNumClassIdx].NumFFRecs);
  CONSTP2CONST(Dem_FFIdxType, AUTOMATIC, DEM_CONST) FFRecNumClass =
    Dem_FFRecNumerationClass[FFRecNumClassIdx].Dem_FFRecNumClassIdx;

  DBG_DEM_CHECKFFRECNUMSTORED_ENTRY(EvMemEntry, RecordNumber);

  /* loop over the record numbers until the requested RecordNumber is found */
  while ( (FFRecNumIdx < NumFF) &&
          (RecordNumber != FFRecNumClass[FFRecNumIdx]) )
  {
    FFRecNumIdx++;
  }

  DBG_DEM_CHECKFFRECNUMSTORED_EXIT(FFRecNumIdx, EvMemEntry, RecordNumber);
  return FFRecNumIdx;
}
#endif /* (DEM_FREEZE_FRAME_REC_NUMERATION_TYPE == DEM_FF_RECNUM_CONFIGURED) */
#endif /* (DEM_NUM_FFSEGS > 0U) */

#if (DEM_NUM_EDSEGS > 0U)
FUNC(Dem_EntryDataPtrType, DEM_CODE) Dem_EDEntryData(
  const Dem_EventMemoryEntryPtrConstType EvMemEntry)
{
  /* calculate start position of the needed ED */
  Dem_EntryDataPtrType EDEntryData = Dem_IntValEntryData(EvMemEntry);

  DBG_DEM_EDENTRYDATA_ENTRY(EvMemEntry);

#if (DEM_USE_INT_VAL_AREA == STD_ON)
  /* if entry data starts with internal value area (e.g. for aging counter),
   * ED entry exists from the next byte only */
  EDEntryData = &EDEntryData[Dem_SizeOfIntValArea(EvMemEntry->EventId)];
#endif

  DBG_DEM_EDENTRYDATA_EXIT(EDEntryData, EvMemEntry);
  return EDEntryData;
}
#endif /* (DEM_NUM_EDSEGS > 0U) */

FUNC(Dem_EntryDataPtrType, DEM_CODE) Dem_IntValEntryData(
  const Dem_EventMemoryEntryPtrConstType EvMemEntry)
{
  Dem_EntryDataPtrType result;

  /* calculate start position of the IntVal entry data */
  const Dem_SizeEntryDataType StartPos = EvMemEntry->EntryDataPos;
  const uint8 originIdx = Dem_GbiDTCOriginIdx(EvMemEntry->EventId);

  DBG_DEM_INTVALENTRYDATA_ENTRY(EvMemEntry);

  result = &Dem_EntryData[originIdx][StartPos];

  DBG_DEM_INTVALENTRYDATA_EXIT(result, EvMemEntry);
  return result;
}

#if (DEM_NUM_EDSEGS > 0U)
FUNC(Dem_EDSegIdxType, DEM_CODE) Dem_FindEDNumIndex(
  CONSTP2CONST(Dem_EDClassType, AUTOMATIC, DEM_CONST) EDClass,
  const uint8                                         Number)
{
  Dem_EDSegIdxType SegIndex;

  DBG_DEM_FINDEDNUMINDEX_ENTRY(EDClass, Number);

  for (SegIndex = 0U; SegIndex < EDClass->NumEDSegs; ++SegIndex)
  {
    if (Dem_EDSegment[EDClass->EDSegIdx[SegIndex]].RecNum == Number)
    {
      break;
    }
  }

  DBG_DEM_FINDEDNUMINDEX_EXIT(SegIndex, EDClass, Number);
  return SegIndex;
}
#endif /* (DEM_NUM_EDSEGS > 0U) */

FUNC(Std_ReturnType, DEM_CODE) Dem_InternalSetEventStatus(
  Dem_EventIdType     EventId,
  Dem_EventStatusType EventStatus)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_INTERNALSETEVENTSTATUS_ENTRY(EventId, EventStatus);

  if (DEM_OPCYCLESTATE[Dem_GbiOpCycleIdx(EventId)] == DEM_CYCLE_STATE_END)
  {
    /* the operation cycle of the event is not started:
     * no debounce-/qualification-handling allowed */
    result = E_NOT_OK;
  }

  /* !LINKSTO Dem447,2, Dem449,2, Dem450,2 */
#if (DEM_NUM_ENCOND_LINKS > 0U)
  /* feature related code-part concerning enable conditions */
  else if (Dem_EventReportingEnabled(EventId) == FALSE)
  {
    result = E_NOT_OK;
  }
#endif
  /* getter function is used in place in order to optimize runtime access */
  else if (!DEM_DTC_SETTING_ALLOWED(EventId))
  {
    /* DTC setting of the group is not enabled:
     * no debounce-/qualification-handling allowed (as per Dem626) */
    result = E_NOT_OK;
  }
  else if (Dem_DebounceEvent(EventId, &EventStatus, &result) == FALSE)
  {
    /* result has been set by called function */
  }
  else
  {
#if (DEM_MAX_NUMBER_PRESTORED_FF > 0U)
    /* release prestored freeze frame for passed events */
    if ( (EventStatus == DEM_EVENT_STATUS_PASSED) &&
         /* Deviation MISRA-1 <+2> */
         (Dem_GbiEnablePrestorage(EventId) == TRUE)
       )
    {
      /* mark prestored freeze frame as unused */
      DEM_ATOMIC_CLR_BIT_IN_ARRAY_8(Dem_PFFEntryValid, Dem_GetPFFIndex(EventId));
    }
#endif
    /* event qualification-handling */
#if (DEM_NUM_FAILURECYCLES > 0U)
    /* update failure counter on first fail report of the event in the
       operation cycle */
    Dem_UpdateFailureCounterFirstFail(EventId, EventStatus);
#endif

    if (Dem_GbiEventKind(EventId) == DEM_EVENT_KIND_SWC)
    {
      Dem_InternalSetSwcEventStatus(EventId, EventStatus, &result);
    }
    else /* DEM_EVENT_KIND_BSW */
    {
      Dem_InternalSetBswEventStatus(EventId, EventStatus, &result);
    }
  }

  DBG_DEM_INTERNALSETEVENTSTATUS_EXIT(result, EventId, EventStatus);
  return result;
}

#if (DEM_NUM_ENCOND_LINKS > 0U)
FUNC(boolean, DEM_CODE) Dem_EventReportingEnabled(Dem_EventIdType EventId)
{
  Dem_EnCondLnkIdxType EnCondLnkIdx;
  boolean result = TRUE;

  const Dem_EnCondLnkIdxType EnCondLnkStartIdx = Dem_GbiEnCondLnkIdx(EventId);

  DBG_DEM_EVENTREPORTINGENABLED_ENTRY(EventId);

  for (EnCondLnkIdx = EnCondLnkStartIdx;
       /* enable conditions only exist for the event, if number > 0 */
       EnCondLnkIdx < (Dem_EnCondLnkIdxType)(
         EnCondLnkStartIdx + Dem_GbiNumEnCond(EventId));
       EnCondLnkIdx++)
  {
    if (Dem_EnCondStatus[Dem_EnCondLink[EnCondLnkIdx]] == FALSE)
    {
      /* at least one enable condition of the event is not set */
      result = FALSE;
      /* stop searching */
      break;
    }
  }

  DBG_DEM_EVENTREPORTINGENABLED_EXIT(EventId, result);

  return result;
}
#endif

FUNC(boolean, DEM_CODE) Dem_DebounceEvent(
  Dem_EventIdType                                       EventId,
  CONSTP2VAR(Dem_EventStatusType, AUTOMATIC, AUTOMATIC) EventStatus,
  CONSTP2VAR(Std_ReturnType, AUTOMATIC, AUTOMATIC)      debounceResult)
{
  boolean result = FALSE;

  const Dem_DebounceType DebounceAlgo = Dem_GbiDebounceAlgo(EventId);

  DBG_DEM_DEBOUNCEEVENT_ENTRY(EventId, EventStatus, debounceResult);

  /* event debounce-handling */
  if (DebounceAlgo != DEM_DEBOUNCE_MONITOR)
  {
    /*
     * ENTER critical section to protect debounce status
     *       call-context: any
     */
    SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

    /* debounce event */
    Dem_DebounceFctPtrTable[DebounceAlgo].DebounceEventFct(
      EventId, EventStatus);

    /*
     * LEAVE critical section
     */
    SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();
  }

  if ( (*EventStatus == DEM_EVENT_STATUS_PREFAILED) ||
       (*EventStatus == DEM_EVENT_STATUS_PREPASSED) )
  {
    if (DebounceAlgo == DEM_DEBOUNCE_MONITOR)
    {
      /* if the event is not qualified and monitor internal debouncing is used,
       * an error is signaled (caller will trigger DET) */
      *debounceResult = DEM_E_DET_REPORT;
    }
    else
    {
      /* debouncing for prefailed or prepassed event successful */
      *debounceResult = E_OK;
    }

    /* event not qualified, result remains FALSE -> stop processing */
  }
  else
  {
    /* set result to OK, potentially clearing DEM_E_DET_REPORT */
    *debounceResult = E_OK;
    /* debouncing qualified the event, continue processing */
    result = TRUE;
  }

  DBG_DEM_DEBOUNCEEVENT_EXIT(result, EventId, EventStatus, debounceResult);

  return result;
}

FUNC(void, DEM_CODE) Dem_InternalSetSwcEventStatus(
  Dem_EventIdType                                  EventId,
  Dem_EventStatusType                              EventStatus,
  CONSTP2VAR(Std_ReturnType, AUTOMATIC, AUTOMATIC) SetSwcEventStatusResult)
{
  const Dem_DTCStatusMaskType OldDTCStatusMask =
    DEM_DTC_STATUS_MASKS[EventId];

  const Dem_EventStatusType OldEventStatus =
    DEM_IS_BIT_SET(OldDTCStatusMask, DEM_DTCSTATUSBIT_TF) ?
      DEM_EVENT_STATUS_FAILED : DEM_EVENT_STATUS_PASSED;

  boolean ReportDtcStatusChanged = FALSE;

#if (DEM_NUM_INDICATOR_LINKS > 0U)
  Dem_EventIdType WIROnCriteriaFulfilledFlagsIdx = 0U;

  const boolean EventWIRUpdate = Dem_CheckForEventWIRUpdate(
    EventId, EventStatus, &WIROnCriteriaFulfilledFlagsIdx);
#endif

  DBG_DEM_INTERNALSETSWCEVENTSTATUS_ENTRY(EventId,
                                          EventStatus,
                                          SetSwcEventStatusResult);

#if (DEM_NUM_INDICATOR_LINKS > 0U)
  if (EventWIRUpdate != FALSE)
  {
    /* update event status */
    DEM_ATOMIC_SET_EV_ST_MASK(EventId, DEM_DTCSTATUSBIT_WIR);

    /* clear 'WIR on criteria fullfilled' flag */
    DEM_ATOMIC_CLR_BIT_IN_ARRAY_8(Dem_WIROnCriteriaFulfilledFlags,
                                  WIROnCriteriaFulfilledFlagsIdx);
    /* notify application as WIR-bit has changed */
    ReportDtcStatusChanged = TRUE;
  }
#endif

  if ( (!DEM_IS_EV_ST_BIT_TNCTOC_SET(EventId)) &&
       (EventStatus == OldEventStatus)
     )
  {
    /* the event was already tested this operation cycle and reported status
     * doesn't change: no qualification-handling necessary */
    *SetSwcEventStatusResult = E_OK;
  }
  else
  {
    /* update status mask of event: */
    Dem_UpdateEventStatusOnQualification(EventId, EventStatus);

    /* append or update event entry, if error-reenter-condition is satisfied */
    if ( (OldEventStatus == DEM_EVENT_STATUS_PASSED) &&
         (EventStatus    == DEM_EVENT_STATUS_FAILED)
       )
    {
      boolean EntryIsWritten = FALSE;

      /*
       * ENTER critical section to protect the error-queue & queue-pointers
       *       call-context: Rte (Task), Dem (Task)
       */
      SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

      /* make entry in error-queue */
      EntryIsWritten = Dem_WriteErrorQueueEntry(EventId, EventStatus);

      /*
       * LEAVE critical section
       */
      SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

      /* check if write was successful */
      if (EntryIsWritten == FALSE)
      {
        /* an error is signaled (caller will trigger DET) */
        *SetSwcEventStatusResult = DEM_E_DET_REPORT;
      }
    }

    /* notify application as TF-bit or TNCTOC-bit has changed in any case */
    ReportDtcStatusChanged = TRUE;
  }

  if (ReportDtcStatusChanged)
  {
#if ( (DEM_USE_CB_TRIG_ON_EVST == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) )
    Dem_CbTriggerOnEventStatus(EventId,
                               OldDTCStatusMask,
                               DEM_DTC_STATUS_MASKS[EventId]);
#endif
  }

  DBG_DEM_INTERNALSETSWCEVENTSTATUS_EXIT(EventId,
                                         EventStatus,
                                         SetSwcEventStatusResult);
}

FUNC(void, DEM_CODE) Dem_InternalSetBswEventStatus(
  Dem_EventIdType                                  EventId,
  Dem_EventStatusType                              EventStatus,
  CONSTP2VAR(Std_ReturnType, AUTOMATIC, AUTOMATIC) SetBswEventStatusResult)
{
  Dem_EventStatusType PreviousEntryStatus;
  boolean EntryPresent;

  const Dem_DTCStatusMaskType OldDTCStatusMask =
    DEM_DTC_STATUS_MASKS[EventId];

  const Dem_EventStatusType OldEventStatus =
    DEM_IS_BIT_SET(OldDTCStatusMask, DEM_DTCSTATUSBIT_TF) ?
      DEM_EVENT_STATUS_FAILED : DEM_EVENT_STATUS_PASSED;

#if (DEM_NUM_BSWEVENT_INDICATOR_USED > 0U)
  Dem_EventIdType WIROnCriteriaFulfilledFlagsIdx = 0U;

  /* check if WIR status bit needs to be updated */
  const boolean EventWIRUpdate = Dem_CheckForEventWIRUpdate(
    EventId, EventStatus, &WIROnCriteriaFulfilledFlagsIdx);
#endif

  DBG_DEM_INTERNALSETBSWEVENTSTATUS_ENTRY(EventId,
                                          EventStatus,
                                          SetBswEventStatusResult);

#if (DEM_NUM_BSWEVENT_INDICATOR_USED > 0U)
  if (EventWIRUpdate != FALSE)
  {
    /* load index of event in BSW event WIR status flag array */
    Dem_EventIdType BSWEventWIRStatusFlagsIndex =
      Dem_GetBSWEventWIRStatusFlagsIndex(EventId);
    /* mark event's WIR bit to be set later (done asynchronously) */
    DEM_ATOMIC_SET_BIT_IN_ARRAY_8(Dem_BSWEventWIRStatusFlags,
                                  BSWEventWIRStatusFlagsIndex);
  }
#endif

  /*
   * ENTER critical section to protect the error-queue & queue-pointers
   *       call-context: any, Dem (Task)
   */
  SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

  /* check if event is already present in error-queue */
  EntryPresent = Dem_CheckErrorQueueEntry(EventId, &PreviousEntryStatus);

  /* append or update event entry, if error-reenter-condition is satisfied */
  if ( ((EntryPresent == TRUE) && (EventStatus != PreviousEntryStatus)) ||
       ( (EntryPresent == FALSE) &&
         ( DEM_IS_EV_ST_BIT_TNCTOC_SET(EventId) ||
           (EventStatus != OldEventStatus)
         )
       )
     )
  {
    /* make entry in error-queue */
    boolean EntryIsWritten = Dem_WriteErrorQueueEntry(EventId, EventStatus);

    /* check if write was successful */
    if (EntryIsWritten == FALSE)
    {
      /* an error is signaled (caller will trigger DET) */
      *SetBswEventStatusResult = DEM_E_DET_REPORT;
    }
  }

  /*
   * LEAVE critical section
   */
  SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();


  DBG_DEM_INTERNALSETBSWEVENTSTATUS_EXIT(EventId,
                                         EventStatus,
                                         SetBswEventStatusResult);
}

FUNC(void, DEM_CODE) Dem_UpdateEventStatusOnQualification(
  Dem_EventIdType     EventId,
  Dem_EventStatusType EventStatus)
{
  DBG_DEM_UPDATEEVENTSTATUSONQUALIFICATION_ENTRY(EventId, EventStatus);

  /* check Event Status */
  if (EventStatus == DEM_EVENT_STATUS_PASSED)
  {
    /* TEST NOT COMPLETE -> 0, TEST FAILED -> 0 */
    DEM_ATOMIC_CLR_EV_ST_MASK(EventId,
                              (DEM_DTCSTATUSBIT_TNCSLC |
                               DEM_DTCSTATUSBIT_TNCTOC |
                               DEM_DTCSTATUSBIT_TF));

    /* EVER FAILED -> unchanged */
  }
  else /* EventStatus == DEM_EVENT_STATUS_FAILED */
  {
    /* !LINKSTO Dem.PendingDTC.Set,1 */
    DEM_ATOMIC_CHNG_EV_ST_MASK(EventId,
                               (DEM_DTCSTATUSBIT_TF    |
                                DEM_DTCSTATUSBIT_TFTOC |
                                DEM_DTCSTATUSBIT_TFSLC |
                                DEM_DTCSTATUSBIT_PDTC),
                               (DEM_DTCSTATUSBIT_TNCSLC |
                                DEM_DTCSTATUSBIT_TNCTOC));
  }

  DBG_DEM_UPDATEEVENTSTATUSONQUALIFICATION_EXIT(EventId, EventStatus);
}

FUNC(void, DEM_CODE) Dem_ClearEventEntry(
  const Dem_EventMemoryEntryPtrType EvMemEntry)
{
#if ((DEM_USE_INT_VAL_AREA == STD_ON) || \
     (DEM_NUM_EDSEGS > 0U) || (DEM_NUM_FFSEGS > 0U))
  const Dem_SizeEntryDataType EntryDataSize =
    Dem_SizeOfEntryData(EvMemEntry->EventId);

  DBG_DEM_CLEAREVENTENTRY_ENTRY(EvMemEntry);

  if (EntryDataSize > 0U)
  {
    Dem_SizeEvMemEntryType entry;

    const uint8 originIdx = Dem_GbiDTCOriginIdx(EvMemEntry->EventId);

    /* calculate entry data size behind data to delete */
    const Dem_SizeEntryDataType width = *(Dem_EntryDataFreePos[originIdx]) -
      EvMemEntry->EntryDataPos - EntryDataSize;

    /* shift internal, extended and freeze frame data, to close the gap -
     * this ensures sufficient monolithic entry data capacity to store maximal
     * number of entries */
    Dem_ShiftData(Dem_IntValEntryData(EvMemEntry), EntryDataSize, width);

    /* shift relevant event memory entry data positions */
    for (entry = 0U; entry < Dem_SizeEventMem[originIdx]; ++entry)
    {
      if (Dem_EventMem[originIdx][entry].EntryDataPos >
          EvMemEntry->EntryDataPos)
      {
        Dem_EventMem[originIdx][entry].EntryDataPos -= EntryDataSize;
      }
    }

    /* recalculate free position of event memory entry data */
    *(Dem_EntryDataFreePos[originIdx]) -= EntryDataSize;
  }
#endif /* ((DEM_USE_INT_VAL_AREA == STD_ON) ||
           (DEM_NUM_EDSEGS > 0U) || (DEM_NUM_FFSEGS > 0U)) */

#if (DEM_NUM_BSWEVENT_INDICATOR_USED > 0U)
  if (Dem_GbiEventKind(EvMemEntry->EventId) == DEM_EVENT_KIND_BSW)
  {
    /* load index of event in BSW event WIR status flag array */
    const Dem_EventIdType BSWEventWIRStatusFlagsIndex =
      Dem_GetBSWEventWIRStatusFlagsIndex(EvMemEntry->EventId);

    if (BSWEventWIRStatusFlagsIndex < DEM_NUM_BSWEVENT_INDICATOR_USED)
    {
      /* clear mark event's WIR bit no matter is it set or not */
      DEM_ATOMIC_CLR_BIT_IN_ARRAY_8(Dem_BSWEventWIRStatusFlags,
                                      BSWEventWIRStatusFlagsIndex);
    }
  }
#endif

  /* clear event entry information */
  EvMemEntry->EventId = (Dem_EventIdType)DEM_EVENT_ID_INVALID;
  /* not necessary to reset EvMemEntry->OccCtr (= 0) */
  /* not necessary to reset EvMemEntry->OccOrder (= 0) */
  /* not necessary to reset EvMemEntry->EntryDataPos (= 0) */

  DBG_DEM_CLEAREVENTENTRY_EXIT(EvMemEntry);
}

FUNC(Dem_SizeEntryDataType, DEM_CODE) Dem_SizeOfEntryData(
  const Dem_EventIdType EventId)
{
  uint8 SizeOfIntValArea = 0U;
  Dem_SizeEDType SizeOfED = 0U;
  Dem_SizeEntryDataType SizeOfFF = 0U;
  Dem_SizeEntryDataType SizeOfEntryData;

#if (DEM_NUM_EDSEGS > 0U)
  /* get extended data class layout */
  CONSTP2CONST(Dem_EDClassType, AUTOMATIC, DEM_CONST) EDClass =
    &Dem_EDClass[Dem_GbiEDClassIdx(EventId)];
#endif

#if (DEM_NUM_FFSEGS > 0U)
  /* get freeze frame class layout */
  CONSTP2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) FFClass =
    &Dem_FFClass[Dem_GbiFFClassIdx(EventId)];

  DBG_DEM_SIZEOFENTRYDATA_ENTRY(EventId);

  /* calculate the total freeze frame data size of the event */
  SizeOfFF = ((Dem_SizeEntryDataType)Dem_SizeOfFF(FFClass) *
                      Dem_GbiMaxNumFFRecs(EventId));
#else
  DBG_DEM_SIZEOFENTRYDATA_ENTRY(EventId);
#endif /* (DEM_NUM_FFSEGS > 0U) */

#if (DEM_USE_INT_VAL_AREA == STD_ON)
  SizeOfIntValArea = Dem_SizeOfIntValArea(EventId);
#endif

#if (DEM_NUM_EDSEGS > 0U)
  SizeOfED = Dem_SizeOfED(EDClass);
#endif

#if ((DEM_USE_INT_VAL_AREA == STD_OFF) && \
     (DEM_NUM_EDSEGS == 0U) && (DEM_NUM_FFSEGS == 0U))
  TS_PARAM_UNUSED(EventId);
#endif

  SizeOfEntryData = ((Dem_SizeEntryDataType)SizeOfIntValArea +
                      SizeOfED + SizeOfFF);

  DBG_DEM_SIZEOFENTRYDATA_EXIT(SizeOfEntryData, EventId);
  return SizeOfEntryData;
}

/*------------------[interface Dem <--> NvM]--------------------------------*/

#if ((DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH) || \
     (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_TRIGGER))

/* this function is mandatory to be configured in NvM but not used */
/* CHECK: NOPARSE */
FUNC(Std_ReturnType, DEM_CODE) Dem_NvMReadCopyEventStatusBlock(
  P2CONST(void, NVM_APPL_DATA, NVM_VAR_NOINIT) NvMBuffer)
{
  TS_PARAM_UNUSED(NvMBuffer);

  DBG_DEM_NVMREADCOPYEVENTSTATUSBLOCK_ENTRY(NvMBuffer);

  /* No-Operation function, nothing to do */

  DBG_DEM_NVMREADCOPYEVENTSTATUSBLOCK_EXIT(NvMBuffer, result);
  return E_OK;
}
/* CHECK: PARSE */

FUNC(Std_ReturnType, DEM_CODE) Dem_NvMWriteCopyEventStatusBlock(
  P2VAR(void, NVM_APPL_DATA, NVM_VAR_NOINIT) NvMBuffer)
{
  Std_ReturnType result = E_NOT_OK;
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  boolean RunStatusValid = TRUE;
  boolean DevErrorReported = FALSE;
#endif

  DBG_DEM_NVMWRITECOPYEVENTSTATUSBLOCK_ENTRY(NvMBuffer);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
  if (DEM_CLEARDTC_STATE_RUNNING != Dem_ClearDtcAsyncStatus.RunState)
  {
    RunStatusValid = FALSE;
  }
#endif

  if ( (Dem_InitializationState == DEM_INITIALIZED) &&
       ( (Dem_ClearDtcAsyncStatus.EventStatusWrite != DEM_NVM_WAITING) ||
         (RunStatusValid == FALSE)
       )
     )
  {
    /* Callback triggered from external source directly or
     * NvM_WriteBlock of Dem status block triggered from external source or
     * NvM module triggered it when in wrong state */
    DEM_REPORT_ERROR(DEM_INTERNAL_API_ID, DEM_E_WRONG_CONDITION);

    /* DET reported, don't do that again if NvMBuffer is NULL pointer */
    DevErrorReported = TRUE;
  }
#endif /* DEM_DEV_ERROR_DETECT */

  if (NvMBuffer == NULL_PTR)
  {
#if (DEM_DEV_ERROR_DETECT == STD_ON)
    if (DevErrorReported == FALSE)
    {
      DEM_REPORT_ERROR(DEM_INTERNAL_API_ID, DEM_E_PARAM_POINTER);
    }
#endif

    /* result remains E_NOT_OK */
  }
  else
  {
    /*
     * ENTER critical section to protect Dem_ClearDtcAsyncStatus and copying
     *       call-context: optional NvM(Task)
     */
    SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

    Dem_ClearDtcAsyncStatus.EventStatusWrite = DEM_NVM_PENDING;
    TS_MemCpy(NvMBuffer, &Dem_NvData, sizeof(Dem_NvData));

    /*
     * LEAVE critical section
     */
    SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

    result = E_OK;
  }

  DBG_DEM_NVMWRITECOPYEVENTSTATUSBLOCK_EXIT(NvMBuffer, result);
  return result;
}

FUNC(Std_ReturnType, DEM_CODE) Dem_NvMEventStatusBlockCallback(
  uint8                 ServiceId,
  NvM_RequestResultType JobResult)
{
  Std_ReturnType result = E_OK;

  DBG_DEM_NVMEVENTSTATUSBLOCKCALLBACK_ENTRY(ServiceId, JobResult);

  /* !LINKSTO Dem579,1
   * retry mechanism is done by NvM, return value is ignored */
  TS_PARAM_UNUSED(JobResult);

  if (DEM_NVM_SID_WriteBlock == ServiceId)
  {
#if (DEM_DEV_ERROR_DETECT == STD_ON)
    boolean RunStatusValid = TRUE;

#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
    if (DEM_CLEARDTC_STATE_RUNNING != Dem_ClearDtcAsyncStatus.RunState)
    {
      RunStatusValid = FALSE;
    }
#endif

    if ( (Dem_InitializationState == DEM_INITIALIZED) &&
         ( (Dem_ClearDtcAsyncStatus.EventStatusWrite != DEM_NVM_PENDING) ||
           (RunStatusValid == FALSE)
         )
       )
    {
      /* Callback triggered from external source directly or
       * NvM_WriteBlock of Dem status block triggered from external source or
       * NvM module triggered it when in wrong state */
      DEM_REPORT_ERROR(DEM_INTERNAL_API_ID, DEM_E_WRONG_CONDITION);
    }
#endif /* DEM_DEV_ERROR_DETECT */
    /*
     * ENTER critical section to protect Dem_ClearDtcAsyncStatus
     *       call-context: optional NvM(Task)
     */
    SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

    Dem_ClearDtcAsyncStatus.EventStatusWrite = DEM_NVM_IDLE;

#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
    if (DEM_NVM_IDLE == Dem_ClearDtcAsyncStatus.EventMemWrite)
    {
      /* If one of the preceding NvM write requests failed the RunState
       * has already been advanced to FAILED. Or, if Dcm cancelled the
       * operation, the RunState is already IDLE.
       * In both cases the RunState must not be modified any more. */
      if (DEM_CLEARDTC_STATE_RUNNING == Dem_ClearDtcAsyncStatus.RunState)
      {
        Dem_ClearDtcAsyncStatus.RunState = DEM_CLEARDTC_STATE_FINISHED;
      }
      /* else: a NvM write request failed, do not change state */
    }
#endif

    /*
     * LEAVE critical section
     */
    SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_TRIGGER)
    if (Dem_ClearDtcAsyncStatus.RetriggerEventStatusWrite == TRUE)
    {
      Dem_ClearDtcAsyncStatus.RetriggerEventStatusWrite = FALSE;

      /* NvM is idle, trigger writing of the event status block */
      /* return value is not checked since Dem_ClearDTC is already finished */
      (void)Dem_TriggerNvmWriteEventStatus();
    }
#endif
  }

  DBG_DEM_NVMEVENTSTATUSBLOCKCALLBACK_EXIT(ServiceId, JobResult, result);
  return result;
}

#endif /* DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH/TRIGGER */

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)

FUNC(Std_ReturnType, DEM_CODE) Dem_NvMGateEntryPrimaryBlockCallback(
  uint8                 ServiceId,
  NvM_RequestResultType JobResult)
{
  DBG_DEM_NVMGATEENTRYPRIMARYBLOCKCALLBACK_ENTRY(ServiceId, JobResult);

  /* !LINKSTO Dem579,1
   * retry mechanism is done by NvM, return value is ignored */
  TS_PARAM_UNUSED(JobResult);

  /* call generic block callback function */
  Dem_NvMGateEntryBlockCallback(
    ServiceId, (uint8)(DEM_DTC_ORIGIN_PRIMARY_MEMORY - 1U));

  DBG_DEM_NVMGATEENTRYPRIMARYBLOCKCALLBACK_EXIT(E_OK, ServiceId, JobResult);
  return E_OK;
}

#if (DEM_MAX_NUMBER_EVENT_ENTRY_SEC != 0U)
FUNC(Std_ReturnType, DEM_CODE) Dem_NvMGateEntrySecondaryBlockCallback(
  uint8                 ServiceId,
  NvM_RequestResultType JobResult)
{
  DBG_DEM_NVMGATEENTRYSECONDARYBLOCKCALLBACK_ENTRY(ServiceId, JobResult);

  /* !LINKSTO Dem579,1
   * retry mechanism is done by NvM, return value is ignored */
  TS_PARAM_UNUSED(JobResult);

  /* call generic block callback function */
  Dem_NvMGateEntryBlockCallback(
    ServiceId, (uint8)(DEM_DTC_ORIGIN_SECONDARY_MEMORY - 1U));

  DBG_DEM_NVMGATEENTRYSECONDARYBLOCKCALLBACK_EXIT(E_OK, ServiceId, JobResult);
  return E_OK;
}
#endif

#if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR != 0U)
FUNC(Std_ReturnType, DEM_CODE) Dem_NvMGateEntryMirrorBlockCallback(
  uint8                 ServiceId,
  NvM_RequestResultType JobResult)
{
  DBG_DEM_NVMGATEENTRYMIRRORBLOCKCALLBACK_ENTRY(ServiceId, JobResult);

  /* !LINKSTO Dem579,1
   * retry mechanism is done by NvM, return value is ignored */
  TS_PARAM_UNUSED(JobResult);

  /* call generic block callback function */
  Dem_NvMGateEntryBlockCallback(
    ServiceId, (uint8)(DEM_DTC_ORIGIN_MIRROR_MEMORY - 1U));

  DBG_DEM_NVMGATEENTRYMIRRORBLOCKCALLBACK_EXIT(E_OK, ServiceId, JobResult);
  return E_OK;
}
#endif

#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U)
FUNC(Std_ReturnType, DEM_CODE) Dem_NvMGateEntryPermanentBlockCallback(
  uint8                 ServiceId,
  NvM_RequestResultType JobResult)
{
  DBG_DEM_NVMGATEENTRYPERMANENTBLOCKCALLBACK_ENTRY(ServiceId, JobResult);

  /* !LINKSTO Dem579,1
   * retry mechanism is done by NvM, return value is ignored */
  TS_PARAM_UNUSED(JobResult);

  /* call generic block callback function */
  Dem_NvMGateEntryBlockCallback(
    ServiceId, (uint8)(DEM_DTC_ORIGIN_PERMANENT_MEMORY - 1U));

  DBG_DEM_NVMGATEENTRYPERMANENTBLOCKCALLBACK_EXIT(E_OK, ServiceId, JobResult);
  return E_OK;
}
#endif

FUNC(void, DEM_CODE) Dem_NvMGateEntryBlockCallback(
  const uint8 ServiceId,
  const uint8 OriginIdx)
{
  DBG_DEM_NVMGATEENTRYBLOCKCALLBACK_ENTRY(ServiceId, OriginIdx);

  /* Dem must not add module-initialized DET-check as NvM-block callback must
     be allowed in general */

  if (ServiceId == DEM_NVM_SID_WriteBlock)
  {
    Dem_NvMGatePrepStatusType NvMGateStatus;

    /* unprotected clearing of PENDING state is allowed in NvM callback */
    Dem_NvMStatus[OriginIdx].Status = DEM_NVM_IDLE;

    /* try to lock gate entry */
    NvMGateStatus = Dem_BeginPrepareGateEntry(OriginIdx);

    /* check which event of the given origin (for which this job end
     * notification was called) shall be stored next */
    Dem_StoreImmediatelyNext(OriginIdx, &NvMGateStatus);

    /* unlock gate entry */
    Dem_EndPrepareGateEntry(OriginIdx, NvMGateStatus);

    if (DEM_GATE_PREPARED == NvMGateStatus)
    {
      /* immediately trigger writing of next block (faster writes) */
      /* can be skipped here in case delays of up to one main function period
       * are acceptable and/or made dependent on ASYNC_ONLY parameter */
      Dem_TriggerNvmWriteGateEntry();
    }
  }

  DBG_DEM_NVMGATEENTRYBLOCKCALLBACK_EXIT(ServiceId, OriginIdx);
}

#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */

/*------------------[Interface Dem <--> SW-Components / BSW modules]--------*/

#if (DEM_USE_CB_INIT_MONITOR == STD_ON)
FUNC(void, DEM_CODE) Dem_CbInitMonitorForEvent(
  const Dem_EventIdType           EventId,
  const Dem_InitMonitorReasonType InitMonitorReason)
{
  DBG_DEM_CBINITMONITORFOREVENT_ENTRY(EventId, InitMonitorReason);

  if ((Dem_CbProperty[EventId] & DEM_GEN_CB_INIT_MONITOR) != 0U)
  {
    Dem_CbIndexType CbIdx = 0U;

    while ( (CbIdx < DEM_LOOKUP_TABLE_INIT_MONITOR_SIZE) &&
            (Dem_CbLookupTableInitMonitor[CbIdx] != EventId) )
    {
      CbIdx++;
    }

    DEM_PRECONDITION_ASSERT(
      (CbIdx < (Dem_CbIndexType)DEM_LOOKUP_TABLE_INIT_MONITOR_SIZE),
      DEM_INTERNAL_API_ID);

    /* !LINKSTO Dem376_Implicit1,1
     * return value is ignored
     * same index in both arrays */
    (void)Dem_CbFuncPtrInitMonitor[CbIdx](InitMonitorReason);
  }

  DBG_DEM_CBINITMONITORFOREVENT_EXIT(EventId, InitMonitorReason);
}
#endif /* (DEM_USE_CB_INIT_MONITOR == STD_ON) */

#if ((DEM_USE_CB_TRIG_ON_EVST == STD_ON) || (DEM_USE_CB_TRIG_ON_DTCST == STD_ON))
FUNC(void, DEM_CODE) Dem_CbTriggerOnEventStatus(
  const Dem_EventIdType       EventId,
  const Dem_DTCStatusMaskType OldDTCStatusMask,
  const Dem_DTCStatusMaskType NewDTCStatusMask)
{
#if ((DEM_RTE_CALLBACK_TABLE_TRIG_ON_EVST_SIZE > 0U) || \
     (DEM_C_CALLBACK_TABLE_TRIG_ON_EVST_SIZE > 0U))
  uint16 StartIdx = 0U;
  uint16 LastIdx = 0U;
  uint16_least LookUpIdx;
#endif
#if ((DEM_C_CALLBACK_TABLE_TRIG_ON_EVST_SIZE > 0U) || \
     (DEM_RTE_CALLBACK_TABLE_TRIG_ON_EVST_SIZE > 0U) || \
     (DEM_CB_TABLE_TRIG_ON_DTCST_SIZE > 0U))
  Dem_CbIndexType CbIdx;
#endif
#if ((DEM_CB_TABLE_TRIG_ON_DTCST_SIZE > 0U) || \
     (DEM_TRIGGER_DCM_REPORTS == STD_ON))
  uint32 DTC;
#endif

  DBG_DEM_CBTRIGGERONEVENTSTATUS_ENTRY(EventId, OldDTCStatusMask, NewDTCStatusMask);

#if (DEM_RTE_CALLBACK_TABLE_TRIG_ON_EVST_SIZE > 0U)
  if ((Dem_CbProperty[EventId] & DEM_RTE_CB_TRIG_ON_EVST) != 0U)
  {
    Dem_GetRteCallbackIndex(
      EventId,
      Dem_RteLookupTableTrigOnEvSt,
      DEM_RTE_LOOKUP_TABLE_TRIG_ON_EVST_SIZE,
      &StartIdx,
      &LastIdx);

    for (LookUpIdx = StartIdx; LookUpIdx <= LastIdx; LookUpIdx++)
    {
      /* !LINKSTO Dem016_Implicit1,1
       * return value is ignored */
      (void)Dem_RteFuncPtrTrigOnEvSt[LookUpIdx](
        OldDTCStatusMask,
        NewDTCStatusMask);
    }
  }

  /* trigger global port GeneralCallbackEventStatusChange (Dem616) */
  (void)Rte_Call_GeneralCBStatusEvt_EventStatusChanged(EventId,
    OldDTCStatusMask, NewDTCStatusMask);
#endif

#if (DEM_C_CALLBACK_TABLE_TRIG_ON_EVST_SIZE > 0U)
  if ((Dem_CbProperty[EventId] & DEM_C_CB_TRIG_ON_EVST) != 0U)
  {
    Dem_GetCallbackIndex(
      EventId,
      Dem_CbLookupTableTrigOnEvSt,
      DEM_C_LOOKUP_TABLE_TRIG_ON_EVST_SIZE,
      &StartIdx,
      &LastIdx);

    for (LookUpIdx = StartIdx; LookUpIdx <= LastIdx; LookUpIdx++)
    {
      CbIdx = Dem_CbLookupTableTrigOnEvSt[LookUpIdx].CallbackIdx;
      /* !LINKSTO Dem016_Implicit1,1
       * return value is ignored */
      Dem_CbFuncPtrTrigOnEvSt[CbIdx](
        EventId,
        OldDTCStatusMask,
        NewDTCStatusMask);
    }
  }
#endif

  /* if trigger on event status callback functionality is enabled for FiM */
#if (DEM_TRIGGER_FIM_REPORTS == STD_ON)
  FiM_DemTriggerOnEventStatus(EventId, OldDTCStatusMask, NewDTCStatusMask);
#endif

#if ((DEM_CB_TABLE_TRIG_ON_DTCST_SIZE > 0U) || \
     (DEM_TRIGGER_DCM_REPORTS == STD_ON))
  /* get the DTC mapped to event Id */
  DTC = Dem_GbiDTC(EventId);

  /* check if DTC is available for this event */
  if (DTC != 0U)
  {
#if (DEM_CB_TABLE_TRIG_ON_DTCST_SIZE > 0U)
    for (CbIdx = 0U; CbIdx < DEM_CB_TABLE_TRIG_ON_DTCST_SIZE; CbIdx++)
    {
      /* !LINKSTO Dem284_Implicit1,1
       * return value is ignored
       * same prototype for C/RTE */
      (void)Dem_CbFuncPtrTrigOnDTCSt[CbIdx](DTC, OldDTCStatusMask, NewDTCStatusMask);
    }
#endif

    /* If trigger on DTC status callback functionality is enabled for Dcm */
#if (DEM_TRIGGER_DCM_REPORTS == STD_ON)
    (void)Dcm_DemTriggerOnDTCStatus(DTC, OldDTCStatusMask, NewDTCStatusMask);
#endif
  }
#endif

  DBG_DEM_CBTRIGGERONEVENTSTATUS_EXIT(EventId, OldDTCStatusMask, NewDTCStatusMask);
}
#endif /* (DEM_USE_CB_TRIG_ON_EVST == STD_ON) || (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) */

#if (DEM_USE_CB_TRIG_ON_EVDAT == STD_ON)
FUNC(void, DEM_CODE) Dem_CbTriggerOnEventData(const Dem_EventIdType EventId)
{
  DBG_DEM_CBTRIGGERONEVENTDATA_ENTRY(EventId);

#if (DEM_RTE_CB_TABLE_TRIG_ON_EVDAT_SIZE > 0U)
  if ((Dem_CbProperty[EventId] & DEM_RTE_CB_TRIG_ON_EVDAT) != 0U)
  {
    Dem_CbIndexType RteCbIdx = 0U;

    while ( (RteCbIdx < DEM_RTE_LOOKUP_TABLE_TRIG_ON_EVDAT_SIZE) &&
            (Dem_RteLookupTableTrigOnEvDat[RteCbIdx] != EventId) )
    {
      RteCbIdx++;
    }

    DEM_PRECONDITION_ASSERT((RteCbIdx < DEM_RTE_LOOKUP_TABLE_TRIG_ON_EVDAT_SIZE),
                            DEM_INTERNAL_API_ID);

    /* !LINKSTO Dem474_Implicit1,1
     * return value is ignored
     * same index in both arrays */
    (void)Dem_RteFuncPtrTrigOnEvDat[RteCbIdx]();
  }

  /* trigger global port GeneralCallbackEventDataChanged (Dem619) */
  (void)Rte_Call_GeneralCBDataEvt_EventDataChanged(EventId);
#endif

#if (DEM_C_CB_TABLE_TRIG_ON_EVDAT_SIZE > 0U)
  if ((Dem_CbProperty[EventId] & DEM_C_CB_TRIG_ON_EVDAT) != 0U)
  {
    Dem_CbIndexType CCbIdx = 0U;

    while ( (CCbIdx < DEM_C_LOOKUP_TABLE_TRIG_ON_EVDAT_SIZE) &&
            (Dem_CbLookupTableTrigOnEvDat[CCbIdx].EventId != EventId) )
    {
      CCbIdx++;
    }

    DEM_PRECONDITION_ASSERT((CCbIdx < DEM_C_LOOKUP_TABLE_TRIG_ON_EVDAT_SIZE),
                            DEM_INTERNAL_API_ID);

    /* get index/link of callback function pointer */
    CCbIdx = Dem_CbLookupTableTrigOnEvDat[CCbIdx].CallbackIdx;
    /* !LINKSTO Dem474_Implicit1,1
     * return value is ignored */
    (void)Dem_CbFuncPtrTrigOnEvDat[CCbIdx](EventId);
  }
#endif

  DBG_DEM_CBTRIGGERONEVENTDATA_EXIT(EventId);
}
#endif /* (DEM_USE_CB_TRIG_ON_EVDAT == STD_ON) */

#if (DEM_USE_CB_CLEAR_EVENT_ALLOWED == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_CbClearEventAllowed(
  const Dem_EventIdType                    EventId,
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA) Allowed)
{
  Std_ReturnType RetVal = E_NOT_OK;

  DBG_DEM_CBCLEAREVENTALLOWED_ENTRY(EventId, Allowed);

#if (DEM_RTE_CB_TABLE_CLEAR_EVENT_ALLOWED_SIZE > 0U)
  if ((Dem_CbProperty[EventId] & DEM_RTE_CB_CLEAR_EVENT_ALLOWED) != 0U)
  {
    Dem_CbIndexType RteCbIdx = 0U;

    while ( (RteCbIdx < DEM_RTE_LOOKUP_TABLE_CLEAR_EVENT_ALLOWED_SIZE) &&
            (Dem_RteLookupTableClearEventAllowed[RteCbIdx] != EventId) )
    {
      RteCbIdx++;
    }

    DEM_PRECONDITION_ASSERT((RteCbIdx < DEM_RTE_LOOKUP_TABLE_CLEAR_EVENT_ALLOWED_SIZE),
                            DEM_INTERNAL_API_ID);

    /* same index in both arrays */
    RetVal = Dem_RteFuncPtrClearEventAllowed[RteCbIdx](Allowed);

  }
#endif

#if (DEM_C_CB_TABLE_CLEAR_EVENT_ALLOWED_SIZE > 0U)
  if ((Dem_CbProperty[EventId] & DEM_C_CB_CLEAR_EVENT_ALLOWED) != 0U)
  {
    Dem_CbIndexType CCbIdx = 0U;

    while ( (CCbIdx < DEM_C_LOOKUP_TABLE_CLEAR_EVENT_ALLOWED_SIZE) &&
            (Dem_CbLookupTableClearEventAllowed[CCbIdx].EventId != EventId) )
    {
      CCbIdx++;
    }

    DEM_PRECONDITION_ASSERT((CCbIdx < DEM_C_LOOKUP_TABLE_CLEAR_EVENT_ALLOWED_SIZE),
                            DEM_INTERNAL_API_ID);

    /* get index/link of callback function pointer */
    CCbIdx = Dem_CbLookupTableClearEventAllowed[CCbIdx].CallbackIdx;
    RetVal = Dem_CbFuncPtrClearEventAllowed[CCbIdx](Allowed);
  }
#endif

  DBG_DEM_CBCLEAREVENTALLOWED_EXIT(RetVal, EventId, Allowed);
  return RetVal;
}
#endif /* (DEM_USE_CB_CLEAR_EVENT_ALLOWED == STD_ON) */

#if (DEM_USE_CB_GET_FDC == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_CbGetFaultDetectionCounter(
  Dem_EventIdType                                                     EventId,
  CONSTP2VAR(Dem_FaultDetectionCounterType, AUTOMATIC, DEM_APPL_DATA) FDC)
{
  Std_ReturnType RetVal = E_NOT_OK;

  Dem_CbIndexType CbIdx;

  DBG_DEM_CBGETFAULTDETECTIONCOUNTER_ENTRY(EventId, FDC);

  if ((Dem_CbProperty[EventId] & DEM_GEN_CB_FAULT_DETECTION_CTR) != 0U)
  {
    CbIdx = 0U;

    while ( (CbIdx < DEM_LOOKUP_TABLE_GET_FDC_SIZE) &&
            (Dem_CbLookupTableGetFDC[CbIdx] != EventId) )
    {
      CbIdx++;
    }

    DEM_PRECONDITION_ASSERT(
      (CbIdx < (Dem_CbIndexType)DEM_LOOKUP_TABLE_GET_FDC_SIZE),
      DEM_INTERNAL_API_ID);

    RetVal = Dem_CbFuncPtrGetFDC[CbIdx](FDC);
  }

  DBG_DEM_CBGETFAULTDETECTIONCOUNTER_EXIT(RetVal, EventId, FDC);
  return RetVal;
}
#endif /* (DEM_USE_CB_GET_FDC == STD_ON) */

#if (DEM_NUM_FFSEGS > 0U)
FUNC(Dem_SizeFFType, DEM_CODE) Dem_SizeOfFF(
  CONSTP2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) FFClass)
{
  Dem_SizeFFType result = 0U;

  DBG_DEM_SIZEOFFF_ENTRY(FFClass);

  if (FFClass->NumFFSegs > 0U)
  {
    const Dem_FFSegIdxType LastSegIdx = FFClass->NumFFSegs - 1U;

    /* add start byte and size of last segment */
    result = FFClass->StartByte[LastSegIdx] +
      Dem_SizeOfFFSegment(&Dem_FFSegment[FFClass->FFSegIdx[LastSegIdx]]);
  }

  DBG_DEM_SIZEOFFF_EXIT(result, FFClass);
  return result;
}

FUNC(Dem_SizeFFType, DEM_CODE) Dem_SizeOfFFSegment(
  CONSTP2CONST(Dem_FFSegmentType, AUTOMATIC, DEM_CONST) FFSegment)
{
  const Dem_DataElementIdxType LastDataElemIdx =
    FFSegment->NumFFDataElements - 1U;

  /* add offset and size of last data element */
  const Dem_SizeFFType result =
    (FFSegment->DataElementOffset[LastDataElemIdx] +
    Dem_DataElement[FFSegment->DataElementIdx[LastDataElemIdx]].Size);

  DBG_DEM_SIZEOFFFSEGMENT_ENTRY(FFSegment);

  DBG_DEM_SIZEOFFFSEGMENT_EXIT(result, FFSegment);
  return result;
}
#endif /* (DEM_NUM_FFSEGS > 0U) */

#if (DEM_NUM_EDSEGS > 0U)
FUNC(Dem_SizeEDType, DEM_CODE) Dem_SizeOfED(
  CONSTP2CONST(Dem_EDClassType, AUTOMATIC, DEM_CONST) EDClass)
{
  Dem_SizeEDType result = 0U;

  DBG_DEM_SIZEOFED_ENTRY(EDClass);

  if (EDClass->NumEDSegs > 0U)
  {
    const Dem_EDSegIdxType LastSegIdx = EDClass->NumEDSegs - 1U;

    /* add start byte and size of last segment */
    result = EDClass->StartByte[LastSegIdx] +
      Dem_SizeOfEDSegment(&Dem_EDSegment[EDClass->EDSegIdx[LastSegIdx]]);
  }

  DBG_DEM_SIZEOFED_EXIT(result, EDClass);
  return result;
}

FUNC(Dem_SizeEDType, DEM_CODE) Dem_SizeOfEDSegment(
  CONSTP2CONST(Dem_EDSegmentType, AUTOMATIC, DEM_CONST) EDSegment)
{
  const Dem_DataElementIdxType LastDataElemIdx =
    EDSegment->NumEDDataElements - 1U;
  Dem_SizeEDType result = EDSegment->DataElementOffset[LastDataElemIdx];

  DBG_DEM_SIZEOFEDSEGMENT_ENTRY(EDSegment);

#if (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON)
  if (EDSegment->DataElementIdx[LastDataElemIdx] < DEM_NUM_EXT_CS_DATAELEMENTS)
#endif
  {
    /* add offset and size of last data element */
    result +=
      Dem_DataElement[EDSegment->DataElementIdx[LastDataElemIdx]].Size;
  }
  /* else: last element being an internal data element do not use the size */

  DBG_DEM_SIZEOFEDSEGMENT_EXIT(result, EDSegment);
  return result;
}

#if (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON)
FUNC(uint8, DEM_CODE) Dem_SizeOfMapIntValClass(
  CONSTP2CONST(Dem_EDClassType, AUTOMATIC, DEM_CONST) EDClass)
{
  Dem_EDSegIdxType SegIndex;
  P2CONST(Dem_EDSegmentType, AUTOMATIC, DEM_CONST) EDSegment;
  Dem_SizeEDType SizeOfIntDE = 0U;

  DBG_DEM_SIZEOFMAPINTVALCLASS_ENTRY(EDClass);

  for (SegIndex = 0U; SegIndex < EDClass->NumEDSegs; ++SegIndex)
  {
    EDSegment = &Dem_EDSegment[EDClass->EDSegIdx[SegIndex]];

    SizeOfIntDE += Dem_SizeOfMapIntValSegment(EDSegment);
  }

  DBG_DEM_SIZEOFMAPINTVALCLASS_EXIT(SizeOfIntDE, EDClass);
  return SizeOfIntDE;
}

FUNC(uint8, DEM_CODE) Dem_SizeOfMapIntValSegment(
  CONSTP2CONST(Dem_EDSegmentType, AUTOMATIC, DEM_CONST) EDSegment)
{
  Dem_DataElementIdxType DataElementIndex;
  Dem_DataElementIdxType DataElementIdx;
  Dem_SizeEDType SizeOfIntDE = 0U;

  DBG_DEM_SIZEOFMAPINTVALSEGMENT_ENTRY(EDSegment);

  /* all data elements of the ED segment */
  for (DataElementIndex = 0U;
       DataElementIndex < EDSegment->NumEDDataElements;
       ++DataElementIndex)
  {
    DataElementIdx = EDSegment->DataElementIdx[DataElementIndex];

    if (DataElementIdx >= DEM_NUM_EXT_CS_DATAELEMENTS)
    {
      /* maximum size of the internal data elements are 1 byte because
       * AgeCtr: DemAgingCycleCounterThreshold range is 1 byte
       * OvfInd: for each memory type 1 bit is used
       * OccCtr: DemImmediateNvStorageLimit range is 1 byte (Immediate storage)
       *       : NumFF range is 1 byte (No immediate storage) */
      SizeOfIntDE += 1U;
    }
  }

  DBG_DEM_SIZEOFMAPINTVALSEGMENT_EXIT(SizeOfIntDE, EDSegment);
  return SizeOfIntDE;
}
#endif /* (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON) */

FUNC(uint8, DEM_CODE) Dem_AssembleExtendedDataSeg(
  CONSTP2CONST(Dem_EDSegmentType, AUTOMATIC, DEM_CONST) EDSegment,
  Dem_EDStartByteType                                   EDStartByte,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)                DestBuffer,
  Dem_EventMemoryEntryPtrConstType                      EvMemEntry)
{
  Dem_DataElementIdxType DataElementIndex;
  uint8 EDSegSize = 0U;
#if (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON)
  const uint8 originIdx = Dem_GbiDTCOriginIdx(EvMemEntry->EventId);
#endif

  /* pointer to const ED data */
  const Dem_EntryDataPtrConstType EDEntryData =
    &(Dem_EDEntryData(EvMemEntry)[EDStartByte]);

  DBG_DEM_ASSEMBLEEXTENDEDDATASEG_ENTRY(
    EDSegment, EDStartByte, DestBuffer, EvMemEntry);

  /* add all data elements of the ED segment */
  for (DataElementIndex = 0U;
       DataElementIndex < EDSegment->NumEDDataElements;
       ++DataElementIndex)
  {
    const Dem_DataElementIdxType DataElementIdx =
      EDSegment->DataElementIdx[DataElementIndex];
    const Dem_DataElementOffsetType EDDataElemOffset =
      EDSegment->DataElementOffset[DataElementIndex];

#if (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON)
    if (DataElementIdx == DEM_INT_VAL_IDX_OCCCTR)
    {
      /* read the occurrence counter from the event memory */
      DestBuffer[EDSegSize] = EvMemEntry->OccCtr;

      /* update internal value size */
      EDSegSize += 1U;
    }
#if (DEM_USE_AGING == STD_ON)
    else if (DataElementIdx == DEM_INT_VAL_IDX_AGECTR)
    {
      /* calculate aging counter output (Dem472, internal value is count-down
       * and stored at the begining of entry data) */
      DestBuffer[EDSegSize] = Dem_GbiNumAgingCycles(EvMemEntry->EventId) -
        *(Dem_IntValEntryData(EvMemEntry));

      /* update internal value size */
      EDSegSize += 1U;
    }
#endif /* (DEM_USE_AGING == STD_ON) */
    else if (DataElementIdx == DEM_INT_VAL_IDX_OVFIND)
    {
      /* read the status of overflow indication bit from EvMemOvfIndFlags and
       * transfer into format: 0x00 = no overflow, 0x01 = overflow */
      DestBuffer[EDSegSize] =
        (uint8)(DEM_IS_OVFIND_SET(originIdx) ? 0x01U : 0x00U);

      /* update internal value size */
      EDSegSize += 1U;
    }
    else
#endif /* (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON) */
    {
      const uint8 DataElementSize = Dem_DataElement[DataElementIdx].Size;

      /* copy data element values for all its size */
      TS_MemCpy(&DestBuffer[EDSegSize], &EDEntryData[EDDataElemOffset],
                DataElementSize);

      /* get the data element sizes excluding internal data element */
      EDSegSize += DataElementSize;
    }
  }

  DBG_DEM_ASSEMBLEEXTENDEDDATASEG_EXIT(
    EDSegSize, EDSegment, EDStartByte, DestBuffer, EvMemEntry);
  return EDSegSize;
}
#endif /* (DEM_NUM_EDSEGS > 0U) */

#if (DEM_USE_INT_VAL_AREA == STD_ON)
FUNC(uint8, DEM_CODE) Dem_SizeOfIntValArea(const Dem_EventIdType EventId)
{
  uint8 SizeOfIntVal = 0U;

  DBG_DEM_SIZEOFINTVALAREA_ENTRY(EventId);

#if (DEM_USE_AGING == STD_ON)
  /* aging counter internal value exists */
  if (DEM_AGING_ALLOWED(EventId))
  {
    SizeOfIntVal = 1U;
  }
#endif /* DEM_USE_AGING */

  DBG_DEM_SIZEOFINTVALAREA_EXIT(SizeOfIntVal, EventId);
  return SizeOfIntVal;
}
#endif /* DEM_USE_INT_VAL_AREA */

FUNC(void, DEM_CODE) Dem_ShiftData(
  P2VAR(Dem_EntryDataType, AUTOMATIC, DEM_VAR_NOINIT) EntryData,
  const Dem_SizeEntryDataType                         offset,
  Dem_SizeEntryDataType                               width)
{
  DBG_DEM_SHIFTDATA_ENTRY(EntryData, offset, width);

  while (width > 0U)
  {
    *EntryData = EntryData[offset];
    /* Deviation MISRA-2 */
    ++EntryData;

    --width;
  }

  DBG_DEM_SHIFTDATA_EXIT(EntryData, offset, width);
}

/*------------------[immediate storage core-functions]----------------------*/

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
FUNC(void, DEM_CODE) Dem_CheckForImmediateEntryStorage(
  Dem_EventIdType                   OriginalEventId,
  const Dem_EventMemoryEntryPtrType EvMemEntryPtr,
  Dem_SizeEvMemEntryType            EvMemEntryIdx,
  boolean                           ForceWrite,
  Dem_NvMGatePrepStatusPtrType      NvMGateStatus)
{
  const uint8 originIdx = Dem_GbiDTCOriginIdx(OriginalEventId);
  const Dem_EventIdType CurrentEventId = EvMemEntryPtr->EventId;

  DBG_DEM_CHECKFORIMMEDIATEENTRYSTORAGE_ENTRY(
    OriginalEventId, EvMemEntryPtr, EvMemEntryIdx, ForceWrite, NvMGateStatus);

#if (DEM_IMMEDIATE_NV_STORAGE_LIMIT > 0U)
  if ( (ForceWrite == FALSE) &&
       ( /* Deviation MISRA-1 <+2> */
         ( (Dem_GbiImmediateStorage(CurrentEventId) == FALSE) &&
           (Dem_GbiImmediateStorage(OriginalEventId) == FALSE) ) ||
         (EvMemEntryPtr->OccCtr > DEM_IMMEDIATE_NV_STORAGE_LIMIT)) )
#else
  if ( (ForceWrite == FALSE) &&
       /* Deviation MISRA-1 <+2> */
       (Dem_GbiImmediateStorage(CurrentEventId) == FALSE) &&
       (Dem_GbiImmediateStorage(OriginalEventId) == FALSE) )
#endif
  {
    if (EvMemEntryPtr->EntryStatus != DEM_ENTRY_CLEAR_IMMEDIATELY)
    {
      /* entry changed but no immediate storage - store during shutdown */
      EvMemEntryPtr->EntryStatus = DEM_ENTRY_CHANGED;
    }
  }
  else if ((*NvMGateStatus) != DEM_GATE_READY)
  {
    /* the gate-entry is queued for processing -> select a storage method
     * except in case this entry is already set to CLEAR_IMMEDIATELY */
    /* !LINKSTO Dem.ClearDTCBehavior.NonvolatileFinish, 1 */
    if (EvMemEntryPtr->EntryStatus != DEM_ENTRY_CLEAR_IMMEDIATELY)
    {
      if (DEM_EVENT_ID_INVALID != EvMemEntryPtr->EventId)
      {
        /* entry is in use and shall be stored */
#if (DEM_IMMEDIATE_NV_STORAGE_TYPE == DEM_IMMEDIATE_CLEARED)
        /* immediate storage restricted to cleared events -> store on shutdown */
        EvMemEntryPtr->EntryStatus = DEM_ENTRY_CHANGED;
#else
        /* immediate storage unrestricted -> store immediately */
        EvMemEntryPtr->EntryStatus = DEM_ENTRY_STORE_IMMEDIATELY;
#endif
      }
      else
      {
        /* entry has been cleared -> store immediately */
        EvMemEntryPtr->EntryStatus = DEM_ENTRY_CLEAR_IMMEDIATELY;
      }
    }
  }
  else
  {
    /* store this event memory entry persistently */
    Dem_StoreImmediately(originIdx, EvMemEntryIdx);
    /* gate entry has successfully been prepared -> update status */
    (*NvMGateStatus) = DEM_GATE_PREPARED;
  }

  DBG_DEM_CHECKFORIMMEDIATEENTRYSTORAGE_EXIT(
    OriginalEventId, EvMemEntryPtr, EvMemEntryIdx, ForceWrite, NvMGateStatus);
}

#if (DEM_CLEAR_DTC_BEHAVIOR != DEM_CLRRESP_VOLATILE)
FUNC(Std_ReturnType, DEM_CODE) Dem_TriggerNvmWriteEventStatus(void)
{
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  NvM_RequestResultType NvMErrorStatus = NVM_REQ_PENDING;
#endif

  Std_ReturnType writeBlockResult = E_NOT_OK;

  DBG_DEM_TRIGGERNVMWRITEEVENTSTATUS_ENTRY();

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  (void)NvM_GetErrorStatus(DEM_NVM_BLOCK_ID_DEFAULT, &NvMErrorStatus);

  if (NVM_REQ_PENDING == NvMErrorStatus)
  {
    DEM_REPORT_ERROR(DEM_INTERNAL_API_ID, DEM_E_WRONG_CONDITION);
  }
#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
  else if
    ( (DEM_CLEARDTC_STATE_RUNNING != Dem_ClearDtcAsyncStatus.RunState) ||
      /* for NONVOLATILE_TRIGGER this is already checked by caller: */
      (DEM_NVM_IDLE != Dem_ClearDtcAsyncStatus.EventStatusWrite) )
  {
    /* indicate an integration error (e.g. NvM callback not configured) */
    DEM_REPORT_ERROR(DEM_INTERNAL_API_ID, DEM_E_WRONG_CONDITION);
  }
#endif
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* set write state to waiting before queuing writing event status
     * block in NvM to allow synchronous execution of write callbacks */
    Dem_ClearDtcAsyncStatus.EventStatusWrite = DEM_NVM_WAITING;

    /* queue write request of default-entry to NvM - NvM_DstPtr is unused,
     * as permanent RAM block (default-entry) is configured */
    writeBlockResult =
      NvM_WriteBlock(DEM_NVM_BLOCK_ID_DEFAULT, NULL_PTR);

    /* if write request for immediate storage was not accepted */
    if (writeBlockResult != E_OK)
    {
      /*
       * ENTER critical section to protect Dem_ClearDtcAsyncStatus
       *       call-context: Dem(Task), optional NvM(Task), Rte(Task)
       */
      SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

      Dem_ClearDtcAsyncStatus.EventStatusWrite = DEM_NVM_IDLE;
#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
      Dem_ClearDtcAsyncStatus.RunState = DEM_CLEARDTC_STATE_FAILED;
#endif

      /*
       * LEAVE critical section
       */
      SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();
    }
  }

  DBG_DEM_TRIGGERNVMWRITEEVENTSTATUS_EXIT(writeBlockResult);
  return writeBlockResult;
}
#endif /* DEM_CLEAR_DTC_BEHAVIOR != DEM_CLRRESP_VOLATILE */

FUNC(void, DEM_CODE) Dem_TriggerNvmWriteGateEntry(void)
{
  boolean GateIsWaiting = FALSE;
  uint8 OriginIdx;

  DBG_DEM_TRIGGERNVMWRITEGATEENTRY_ENTRY();

  for (OriginIdx = 0U; OriginIdx < DEM_MAXNUM_ORIGINS; ++OriginIdx)
  {
    const NvM_BlockIdType NvDataBlockId = Dem_NvDataBlockId[OriginIdx];

#if (DEM_DEV_ERROR_DETECT == STD_ON)
    /* in case the Dem-internal NvM status does not match the NvM-reported
     * status, a critical section has not been configured correctly */
    NvM_RequestResultType NvMErrorStatus = NVM_REQ_PENDING;

    (void)NvM_GetErrorStatus(NvDataBlockId, &NvMErrorStatus);

    if (NVM_REQ_PENDING == NvMErrorStatus)
    {
      /* !LINKSTO Dem.DetReport.TriggerNvmWriteGateEntry,1 */
      DEM_REPORT_ERROR(DEM_INTERNAL_API_ID, DEM_E_WRONG_CONDITION);
    }
    else
#endif /* DEM_DEV_ERROR_DETECT == STD_ON */
    {
      /*
       * ENTER critical section to protect the Nv_Status
       *       call-context: Dem(Task), optional NvM(Task), Rte(Task)
       */
      SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

      /* Dem_NvMStatus must only be modified within crit. sect. */
      if (DEM_NVM_WAITING == Dem_NvMStatus[OriginIdx].Status)
      {
        GateIsWaiting = TRUE;

        /* advance internal NvM gate status to pending */
        Dem_NvMStatus[OriginIdx].Status = DEM_NVM_PENDING;
      }

      /*
       * LEAVE critical section
       */
      SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

      if (GateIsWaiting)
      {
        Std_ReturnType writeBlockResult;
        CONSTP2VAR(Dem_GateEntryBaseType, AUTOMATIC, DEM_VAR_NOINIT)
          GateEntryBase = Dem_NvGateEntryData[OriginIdx];
        const Dem_SizeEvMemEntryType EntryIdx =
          Dem_NvMStatus[OriginIdx].PendingEntryIdx;

        /* reset 'gate waiting' flag */
        GateIsWaiting = FALSE;

        /* select corresponding NVRAM block dataset */
        (void)NvM_SetDataIndex(NvDataBlockId, EntryIdx);

        /* queue write request of gate-entry to NvM - NvM_DstPtr is unused,
         * as permanent RAM block (gate-entry) is configured */
        writeBlockResult = NvM_WriteBlock(NvDataBlockId, NULL_PTR);

        /* if write request for immediate storage was not accepted */
        if (writeBlockResult != E_OK)
        {
          /*
           * ENTER critical section to protect the event memory entry
           *       call-context: Dem(Task), optional NvM(Task), Rte(Task)
           */
          SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
          /* check if a ClearDTC request for this event memory is running */
          if ( (DEM_CLEARDTC_STATE_RUNNING ==
                  Dem_ClearDtcAsyncStatus.RunState) &&
               (OriginIdx == Dem_ClearDtcAsyncStatus.OriginIdx))
          {
            Dem_ClearDtcAsyncStatus.EventMemWrite = DEM_NVM_IDLE;
            Dem_ClearDtcAsyncStatus.RunState = DEM_CLEARDTC_STATE_FAILED;
          }
#endif

          /* check if the entry status can be set to write again later */
          if ( (Dem_EventMem[OriginIdx][EntryIdx].EventId ==
                 GateEntryBase->EntryBase.EventId) &&
               (Dem_EventMem[OriginIdx][EntryIdx].EntryStatus ==
                 DEM_ENTRY_UNCHANGED) )
          {
            /* mark entry as changed to store it during shutdown */
            Dem_EventMem[OriginIdx][EntryIdx].EntryStatus = DEM_ENTRY_CHANGED;
          }

          /* set internal NvM gate status from PENDING back to IDLE */
          Dem_NvMStatus[OriginIdx].Status = DEM_NVM_IDLE;

          /*
           * LEAVE critical section
           */
          SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();
        }
      }
    }
  }

  DBG_DEM_TRIGGERNVMWRITEGATEENTRY_EXIT();
}

STATIC FUNC(void, DEM_CODE) Dem_StoreImmediatelyNext(
  const uint8                  originIdx,
  Dem_NvMGatePrepStatusPtrType NvMGateStatus)
{
  DBG_DEM_STOREIMMEDIATELYNEXT_ENTRY(originIdx, NvMGateStatus);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if ( (Dem_InitializationState != DEM_INITIALIZED) &&
       (Dem_InitializationState != DEM_POSTINITIALIZED) )
  {
    /* One of the NvM block callback function was triggered in an unexpected
       state of the Dem module, most probably because of an unwanted external
       Dem block write */
    DEM_REPORT_ERROR(DEM_SID_StoreImmediatelyNext, DEM_E_UNINIT);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* in order to suppress conflicting parallel NvM-requests, the NvM single-
     * block callback must not be processed if it is invoked due to NvM write
     * within Dem_Shutdown() after the Dem module state has been advanced to
     * POSTINITIALIZED */
    if (Dem_InitializationState == DEM_INITIALIZED)
    {
      const Dem_SizeEvMemEntryType sizeEventMem = Dem_SizeEventMem[originIdx];
      const Dem_EventMemoryEntryPtrType EvMemEntry = Dem_EventMem[originIdx];

      Dem_SizeEvMemEntryType entryIdx;
      Dem_SizeEvMemEntryType foundEntryIdx = sizeEventMem;
#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
      boolean clearedEntriesFound = FALSE;
#endif
#if (DEM_USE_EVENT_DISPLACEMENT == STD_ON)
      Dem_OccOrderType minOccOrder = DEM_MAX_OCC_ORDER;
#endif

      /* another NvM write might have been triggerd outside of this critical
       * section so the NvM status of the Dem has to be re-checked */

      /* at this point, the state IS ALWAYS PREPARE -- see calling function! */
      DEM_PRECONDITION_ASSERT(
        (DEM_NVM_PREPARE == Dem_NvMStatus[originIdx].Status),
        DEM_SID_StoreImmediatelyNext);

      /*
       * ENTER critical section to protect the event memory
       *       call-context: NvM (Task)
       */
      SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

      /* search for the next entry which shall be stored immediately */
      for (entryIdx = 0U; entryIdx < sizeEventMem; ++entryIdx)
      {
        /* check if an 'immediate write' status is set for the event entry */
        if (DEM_ENTRY_CLEAR_IMMEDIATELY == EvMemEntry[entryIdx].EntryStatus)
        {
          /* select entry found */
          foundEntryIdx = entryIdx;

#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
          /* set flag that there are still entries to be cleared */
          clearedEntriesFound = TRUE;
#endif

          /* stop searching, state CLEAR_IMMEDIATELY has highest prio */
          break;
        }
        else if (DEM_ENTRY_STORE_IMMEDIATELY ==
                  EvMemEntry[entryIdx].EntryStatus)
        {
#if (DEM_USE_EVENT_DISPLACEMENT == STD_ON)
          /* select entry with lowest occurrence order value to ensure correct
           * order at any time in case of occurrence order rearrangement */
          if (EvMemEntry[entryIdx].OccOrder < minOccOrder)
          {
            minOccOrder = EvMemEntry[entryIdx].OccOrder;
            foundEntryIdx = entryIdx;
            /* no break */
          }
#else
          /* select first entry found */
          foundEntryIdx = entryIdx;
          /* no break, continue searching for state CLEAR_IMMEDIATELY */
#endif /* DEM_USE_EVENT_DISPLACEMENT == STD_ON */
        }
        else
        {
          /* state is CHANGED or UNCHANGED -> not handled immediately */
        }
      }

      /* next immediate-storage entry was found */
      if (foundEntryIdx < sizeEventMem)
      {
        /* store this event memory entry persistently */
        Dem_StoreImmediately(originIdx, foundEntryIdx);

        /* gate entry has successfully been prepared -> update status */
        (*NvMGateStatus) = DEM_GATE_PREPARED;
      }
      /* else: all immediate-storage entries of this event memory are written */

#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
      /*
       * REUSE critical section to protect the ClearDtc Status
       *       call-context: NvM(Task)
       */

      /* check if a ClearDTC request for this event memory is finished */
      if ( (originIdx == Dem_ClearDtcAsyncStatus.OriginIdx) &&
           (FALSE == clearedEntriesFound) )
      {
        Dem_ClearDtcAsyncStatus.EventMemWrite = DEM_NVM_IDLE;

        if (DEM_NVM_IDLE == Dem_ClearDtcAsyncStatus.EventStatusWrite)
        {
          /* If one of the preceding NvM write requests failed the RunState
           * has already been advanced to FAILED. Or, if Dcm cancelled the
           * operation, the RunState is already IDLE.
           * In both cases the RunState must not be modified anymore. */
          if (DEM_CLEARDTC_STATE_RUNNING == Dem_ClearDtcAsyncStatus.RunState)
          {
            Dem_ClearDtcAsyncStatus.RunState = DEM_CLEARDTC_STATE_FINISHED;
          }
        }
      }
#endif

      /*
       * LEAVE critical section
       */
      SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();
    }
  }

  DBG_DEM_STOREIMMEDIATELYNEXT_EXIT(originIdx, NvMGateStatus);
}

FUNC(void, DEM_CODE) Dem_StoreImmediately(
  const uint8                  originIdx,
  const Dem_SizeEvMemEntryType entryIdx)
{
  /* sizes of the gate-entry data
   * Incase no event data exist for any of the events of one event memory,
   * SizeGateEntryData[] will be 1 */
  const Dem_SizeEntryDataType SizeGateEntryData[DEM_MAXNUM_ORIGINS] =
  {
    DEM_SIZE_GATE_ENTRY_DATA_PRIMARY,
    DEM_SIZE_GATE_ENTRY_DATA_MIRROR,
    DEM_SIZE_GATE_ENTRY_DATA_PERMANENT,
    DEM_SIZE_GATE_ENTRY_DATA_SECONDARY
  };

  CONSTP2VAR(Dem_GateEntryBaseType, AUTOMATIC, DEM_VAR_NOINIT) GateEntryBase
    = Dem_NvGateEntryData[originIdx];
  const Dem_EventMemoryEntryPtrType EvMemEntry
    = &Dem_EventMem[originIdx][entryIdx];

  /* --- transfer event memory entry into gate-entry --- */

  const Dem_EventIdType EvId = EvMemEntry->EventId;

  Dem_SizeEntryDataType sizeUsedEntryData;

  DBG_DEM_STOREIMMEDIATELY_ENTRY(originIdx, entryIdx);

  /* copy the event Id from event memory to gate-entry */
  GateEntryBase->EntryBase.EventId = EvId;

  /* check if this entry exists within the event memory */
  if (EvId != (Dem_EventIdType)DEM_EVENT_ID_INVALID)
  {
#if (DEM_NUM_FFSEGS > 0U)
    Dem_FFIdxType MaxNumFF = Dem_GbiMaxNumFFRecs(EvId);
    Dem_FFIdxType NumFF = DEM_NUMFF(EvMemEntry, MaxNumFF);
    CONSTP2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) FFClass =
      &Dem_FFClass[Dem_GbiFFClassIdx(EvId)];
#endif

    /* copy OccCtr and OccOrder from event memory entry */
    GateEntryBase->EntryBase.OccCtr = EvMemEntry->OccCtr;
#if (DEM_USE_EVENT_DISPLACEMENT == STD_ON)
    GateEntryBase->EntryBase.OccOrder = EvMemEntry->OccOrder;
#endif

#if (DEM_NUM_FAILURECYCLES > 0U)
    /* copy EventFailureCycleCounter from event memory entry */
    GateEntryBase->EntryBase.EventFailureCycleCounter =
      EvMemEntry->EventFailureCycleCounter;
#endif

    sizeUsedEntryData = Dem_SizeOfEntryData(EvId);

#if (DEM_NUM_FFSEGS > 0U)
    /* write only the valid freeze frame data */
    sizeUsedEntryData -=
      (((Dem_SizeEntryDataType)MaxNumFF - NumFF) * Dem_SizeOfFF(FFClass));
#endif

    if ( (Dem_GateEntryData[originIdx] != NULL_PTR) &&
         (sizeUsedEntryData > 0U) )
    {
      /* copy event memory entry data into gate-entry data:
       * for the case when no event data exists for any of the events in this
       * event memory no copying takes place as sizeUsedEntryData is 0 */
      TS_MemCpy((Dem_EntryDataPtrType)Dem_GateEntryData[originIdx],
        &Dem_EntryData[originIdx][EvMemEntry->EntryDataPos], sizeUsedEntryData);
    }
  }
  else /* reset gate-entry for an invalid event */
  {
    GateEntryBase->EntryBase.OccCtr = 0U;
#if (DEM_USE_EVENT_DISPLACEMENT == STD_ON)
    GateEntryBase->EntryBase.OccOrder = 0U;
#endif
#if (DEM_NUM_FAILURECYCLES > 0U)
    GateEntryBase->EntryBase.EventFailureCycleCounter = 0U;
#endif

    sizeUsedEntryData = 0U;
  }

  if (Dem_GateEntryData[originIdx] != NULL_PTR)
  {
    /* check if empty space remained in gate-entry after event entry is copied
     * to it:
     * - this occurs when current event data has a size lower than gate-entry
     *   size for that event memory
     * - when no event data exists for any of the events in this event memory
     *   -> there shall be only the empty entry of size 1 to be filled with 0
     */
    while (sizeUsedEntryData < SizeGateEntryData[originIdx])
    {
      /* clear remaining GateEntryData[] with zero values */
      ((Dem_EntryDataPtrType) Dem_GateEntryData[originIdx])
                                [sizeUsedEntryData] = 0U;

      ++sizeUsedEntryData;
    }
  }

  /* --- prepare asynchronous transfer of gate-entry into NVRAM --- */

  /* unprotected access to these members is allowed in state DEM_NVM_PREPARE */
  Dem_NvMStatus[originIdx].PendingEntryIdx = (uint8)entryIdx;

  /* mark entry as stored persistently */
  EvMemEntry->EntryStatus = DEM_ENTRY_UNCHANGED;

  DBG_DEM_STOREIMMEDIATELY_EXIT(originIdx, entryIdx);
}

#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */

/*------------------[aging]-------------------------------------------------*/

#if (DEM_USE_AGING == STD_ON)
FUNC(void, DEM_CODE) Dem_ClearAgedEventEntry(
  const Dem_EventIdType             EventId,
  const Dem_EventMemoryEntryPtrType EvMemEntry)
{
  DBG_DEM_CLEARAGEDEVENTENTRY_ENTRY(EventId, EvMemEntry);

  Dem_ClearEventEntry(EvMemEntry);

  /* clear confirmed, TestFailedSinceLastClear (only if allowed),
   * and warning indicator request bits */
#if (DEM_STATUS_BIT_HANDLING_TESTFAILEDSINCELASTCLEAR == \
      DEM_STATUS_BIT_AGING_AND_DISPLACEMENT)
  DEM_CLR_EV_ST_MASK(EventId,
                     DEM_DTCSTATUSBIT_CDTC |
                     DEM_DTCSTATUSBIT_TFSLC |
                     DEM_DTCSTATUSBIT_WIR);
#else
  DEM_CLR_EV_ST_MASK(EventId,
                     DEM_DTCSTATUSBIT_CDTC |
                     DEM_DTCSTATUSBIT_WIR);
#endif

  DBG_DEM_CLEARAGEDEVENTENTRY_EXIT(EventId, EvMemEntry);
}
#endif /* DEM_USE_AGING */

/*==================[internal function definitions]=========================*/

/*------------------[reset debounce status]---------------------------------*/

#if (DEM_NUM_DEBOUNCE_TIME > 0U)
STATIC FUNC(void, DEM_CODE) Dem_ResetDebounceTimeBased(
  Dem_EventIdType EventId)
{
  const Dem_EventIdType DebounceIdx = Dem_GbiDebounceIdx(EventId);
  CONSTP2VAR(Dem_DebounceTimeStatusType, AUTOMATIC, DEM_VAR_NOINIT)
    DebounceStatus = &Dem_DebounceTimeStatus[DebounceIdx];

  DBG_DEM_RESETDEBOUNCETIMEBASED_ENTRY(EventId);

  /* (re-)initialize Dem_DebounceTimeStatus */
  DebounceStatus->InternalTimer = 0U;
  DebounceStatus->Direction = DEM_EVENT_STATUS_UNQUALIFIED;

  DBG_DEM_RESETDEBOUNCETIMEBASED_EXIT(EventId);
}
#endif /* (DEM_NUM_DEBOUNCE_TIME > 0U) */

#if (DEM_NUM_DEBOUNCE_COUNTER > 0U)
STATIC FUNC(void, DEM_CODE) Dem_ResetDebounceCounterBased(
  Dem_EventIdType EventId)
{
  const Dem_EventIdType DebounceIdx = Dem_GbiDebounceIdx(EventId);
  CONSTP2VAR(Dem_DebounceCounterStatusType, AUTOMATIC, DEM_VAR_NOINIT)
    DebounceStatus = &Dem_DebounceCounterStatus[DebounceIdx];

  DBG_DEM_RESETDEBOUNCECOUNTERBASED_ENTRY(EventId);

  /* (re-)initialize Dem_DebounceCounterStatus */
  DebounceStatus->InternalCounter = 0;
  DebounceStatus->Direction = DEM_EVENT_STATUS_UNQUALIFIED;

  DBG_DEM_RESETDEBOUNCECOUNTERBASED_EXIT(EventId);
}
#endif /* (DEM_NUM_DEBOUNCE_COUNTER > 0U) */

#if (DEM_NUM_DEBOUNCE_FREQUENCY > 0U)
STATIC FUNC(void, DEM_CODE) Dem_ResetDebounceFrequencyBased(
  Dem_EventIdType EventId)
{
  const Dem_EventIdType DebounceIdx = Dem_GbiDebounceIdx(EventId);
  CONSTP2VAR(Dem_DebounceFrequencyStatusType, AUTOMATIC, DEM_VAR_NOINIT)
    DebounceStatus = &Dem_DebounceFrequencyStatus[DebounceIdx];

  DBG_DEM_RESETDEBOUNCEFREQUENCYBASED_ENTRY(EventId);

  /* (re-)initialize Dem_DebounceFrequencyStatus */
  DebounceStatus->InternalTimer = 0U;
  /* not necessary to reset DebounceStatus->PassedCounter (= 0) */
  /* not necessary to reset DebounceStatus->FailedCounter (= 0) */
  DebounceStatus->Status   = DEM_EVENT_STATUS_UNQUALIFIED;

  DBG_DEM_RESETDEBOUNCEFREQUENCYBASED_EXIT(EventId);
}
#endif /* (DEM_NUM_DEBOUNCE_FREQUENCY > 0U) */

STATIC FUNC(void, DEM_CODE) Dem_ResetDebounceMonitor(Dem_EventIdType EventId)
{
  DBG_DEM_RESETDEBOUNCEMONITOR_ENTRY(EventId);

  /* dummy function, do nothing */
  TS_PARAM_UNUSED(EventId);

  DBG_DEM_RESETDEBOUNCEMONITOR_EXIT(EventId);
}

/*------------------[debounce an event entry]-------------------------------*/

#if (DEM_NUM_DEBOUNCE_COUNTER > 0U)
STATIC FUNC(void, DEM_CODE) Dem_DebounceEventCounterBased(
  Dem_EventIdType                                           EventId,
  CONSTP2VAR(Dem_EventStatusType, AUTOMATIC, DEM_APPL_DATA) EventStatus)
{
  const Dem_EventIdType DebounceIdx = Dem_GbiDebounceIdx(EventId);
  CONSTP2CONST(Dem_DebounceCounterCfgType, AUTOMATIC, DEM_CONST)
    DebounceCfg = &Dem_DebounceCounterCfg[DebounceIdx];
  CONSTP2VAR(Dem_DebounceCounterStatusType, AUTOMATIC, DEM_VAR_NOINIT)
    DebounceStatus = &Dem_DebounceCounterStatus[DebounceIdx];

  DBG_DEM_DEBOUNCEEVENTCOUNTERBASED_ENTRY(EventId, EventStatus);

  switch (*EventStatus)
  {
    case DEM_EVENT_STATUS_PREPASSED:
      /* jump-down enabled, direction toggled and counter value is greater
       * than configured jump-down value */
      if ( ( (DebounceCfg->JumpDown != FALSE) &&
             (DebounceStatus->Direction == DEM_EVENT_STATUS_FAILED) ) &&
             (DebounceStatus->InternalCounter > DebounceCfg->JumpDownValue) )
      {
        /* jump down (and step down in action below) */
        DebounceStatus->InternalCounter = DebounceCfg->JumpDownValue;
      }

      if ( DebounceStatus->InternalCounter >
           (DebounceCfg->CounterPassedThreshold +
           (sint16)DebounceCfg->CountDecStepSize) )
      {
        /* step down */
        DebounceStatus->InternalCounter -=
          (sint16)DebounceCfg->CountDecStepSize;
      }
      else
      {
        /* step down to threshold: qualify event as passed */
        DebounceStatus->InternalCounter =
          DebounceCfg->CounterPassedThreshold;
        *EventStatus = DEM_EVENT_STATUS_PASSED;
      }

      DebounceStatus->Direction = DEM_EVENT_STATUS_PASSED;

      break;

    case DEM_EVENT_STATUS_PREFAILED:

      /* jump-up enabled, direction toggled and counter value is less
       * than configured jump-up value */
      if ( ( (DebounceCfg->JumpUp != FALSE) &&
             (DebounceStatus->Direction == DEM_EVENT_STATUS_PASSED) ) &&
             (DebounceStatus->InternalCounter < DebounceCfg->JumpUpValue) )
      {
        /* jump up (and step up in action below) */
        DebounceStatus->InternalCounter = DebounceCfg->JumpUpValue;
      }

      if ( DebounceStatus->InternalCounter <
           (DebounceCfg->CounterFailedThreshold -
           (sint16)DebounceCfg->CountIncStepSize) )
      {
        /* step up */
        DebounceStatus->InternalCounter +=
          (sint16)DebounceCfg->CountIncStepSize;
      }
      else
      {
        /* step up to threshold: qualify event as failed */
        DebounceStatus->InternalCounter =
          DebounceCfg->CounterFailedThreshold;
        *EventStatus = DEM_EVENT_STATUS_FAILED;
      }

      DebounceStatus->Direction = DEM_EVENT_STATUS_FAILED;

      break;

    case DEM_EVENT_STATUS_PASSED:

      DebounceStatus->InternalCounter = DebounceCfg->CounterPassedThreshold;
      DebounceStatus->Direction = DEM_EVENT_STATUS_PASSED;

      break;

    default: /* DEM_EVENT_STATUS_FAILED */

      DebounceStatus->InternalCounter = DebounceCfg->CounterFailedThreshold;
      DebounceStatus->Direction = DEM_EVENT_STATUS_FAILED;

      break;

  } /* event status */

  DBG_DEM_DEBOUNCEEVENTCOUNTERBASED_EXIT(EventId, EventStatus);
}
#endif /* (DEM_NUM_DEBOUNCE_COUNTER > 0U) */

#if (DEM_NUM_DEBOUNCE_FREQUENCY > 0U)
STATIC FUNC(void, DEM_CODE) Dem_DebounceEventFrequencyBased(
  Dem_EventIdType                                           EventId,
  CONSTP2VAR(Dem_EventStatusType, AUTOMATIC, DEM_APPL_DATA) EventStatus)
{
  const Dem_EventIdType DebounceIdx = Dem_GbiDebounceIdx(EventId);
  CONSTP2CONST(Dem_DebounceFrequencyCfgType, AUTOMATIC, DEM_CONST)
    DebounceCfg = &Dem_DebounceFrequencyCfg[DebounceIdx];
  CONSTP2VAR(Dem_DebounceFrequencyStatusType, AUTOMATIC, DEM_VAR_NOINIT)
    DebounceStatus = &Dem_DebounceFrequencyStatus[DebounceIdx];

  DBG_DEM_DEBOUNCEEVENTFREQUENCYBASED_ENTRY(EventId, EventStatus);

  switch (*EventStatus)
  {
    case DEM_EVENT_STATUS_PREPASSED:

      if (DebounceStatus->InternalTimer == 0U)
      {
        /* timer not running -> start timer */
        DebounceStatus->InternalTimer = DebounceCfg->TimeWindowDuration;
        DEM_RESETFREQBASEDCOUNTERS(DebounceStatus);
      }

      if ( DebounceStatus->PassedCounter <
           DebounceCfg->ThresholdBeforeEvPassed )
      {
        DebounceStatus->PassedCounter++;
      }
      else /* passed-threshold reached */
      {
        /* qualify event as PASSED */
        DebounceStatus->Status = DEM_EVENT_STATUS_PASSED;
        /* not necessary to perform DebounceStatus->PassedCounter++ */
        DebounceStatus->InternalTimer = 0U;
        *EventStatus = DEM_EVENT_STATUS_PASSED;
      }

      break;

    case DEM_EVENT_STATUS_PREFAILED:

      if (DebounceStatus->InternalTimer == 0U)
      {
        /* timer not running -> start timer */
        DebounceStatus->InternalTimer = DebounceCfg->TimeWindowDuration;
          DEM_RESETFREQBASEDCOUNTERS(DebounceStatus);
      }

      if ( DebounceStatus->FailedCounter <
           DebounceCfg->ThresholdBeforeEvFailed )
      {
        DebounceStatus->FailedCounter++;
      }
      else /* failed-threshold reached */
      {
        /* qualify event as FAILED */
        DebounceStatus->Status = DEM_EVENT_STATUS_FAILED;
        /* not necessary to perform DebounceStatus->FailedCounter++ */
        DebounceStatus->InternalTimer = 0U;
        *EventStatus = DEM_EVENT_STATUS_FAILED;
      }

      break;

    case DEM_EVENT_STATUS_PASSED:

      /* stop timer, set "passed" FDC */
      DebounceStatus->InternalTimer = 0U;
      DebounceStatus->Status = DEM_EVENT_STATUS_PASSED;

      break;

    default: /* DEM_EVENT_STATUS_FAILED */

      /* stop timer, set "failed" FDC */
      DebounceStatus->InternalTimer = 0U;
      DebounceStatus->Status = DEM_EVENT_STATUS_FAILED;

      break;

  } /* event status */

  DBG_DEM_DEBOUNCEEVENTFREQUENCYBASED_EXIT(EventId, EventStatus);
}
#endif /* (DEM_NUM_DEBOUNCE_FREQUENCY > 0U) */

#if (DEM_NUM_DEBOUNCE_TIME > 0U)
STATIC FUNC(void, DEM_CODE) Dem_DebounceEventTimeBased(
  Dem_EventIdType                                           EventId,
  /* Deviation MISRA-3 */
  CONSTP2VAR(Dem_EventStatusType, AUTOMATIC, DEM_APPL_DATA) EventStatus)
{
  const Dem_EventIdType DebounceIdx = Dem_GbiDebounceIdx(EventId);
  CONSTP2CONST(Dem_DebounceTimeCfgType, AUTOMATIC, DEM_CONST)
    DebounceCfg = &Dem_DebounceTimeCfg[DebounceIdx];
  CONSTP2VAR(Dem_DebounceTimeStatusType, AUTOMATIC, DEM_VAR_NOINIT)
    DebounceStatus = &Dem_DebounceTimeStatus[DebounceIdx];

  DBG_DEM_DEBOUNCEEVENTTIMEBASED_ENTRY(EventId, EventStatus);

  switch (*EventStatus)
  {
    case DEM_EVENT_STATUS_PREPASSED:

      /*
       * if either
       *  - the timer is already running, but as a "failed" timer
       * or
       *  - the timer is not running and the event has not been qualified
       *    as "passed" yet
       * then the "passed" timer must be (re-)started
       */
      if ( ( (DebounceStatus->InternalTimer != 0U) &&
             (DebounceStatus->Direction == DEM_EVENT_STATUS_FAILED)
           ) ||
           ( (DebounceStatus->InternalTimer == 0U) &&
             (DebounceStatus->Direction != DEM_EVENT_STATUS_PASSED)
           )
         )
      {
        /* if TimePassedThreshold = 0, no debouncing is started */
        DebounceStatus->InternalTimer = DebounceCfg->TimePassedThreshold;
        DebounceStatus->Direction = DEM_EVENT_STATUS_PASSED;
      }
      /*
       * in all other cases ("passed" timer already running or event
       * already qualified as "passed" and no timer running) there's
       * nothing to do.
       */
      break;

    case DEM_EVENT_STATUS_PREFAILED:

      /* see description above, exchanging "passed" and "failed" */

      if ( ( (DebounceStatus->InternalTimer != 0U) &&
             (DebounceStatus->Direction == DEM_EVENT_STATUS_PASSED)
           ) ||
           ( (DebounceStatus->InternalTimer == 0U) &&
             (DebounceStatus->Direction != DEM_EVENT_STATUS_FAILED)
           )
         )
      {
        /* if TimeFailedThreshold = 0, no debouncing is started */
        DebounceStatus->InternalTimer = DebounceCfg->TimeFailedThreshold;
        DebounceStatus->Direction = DEM_EVENT_STATUS_FAILED;
      }

      break;

    default: /* DEM_EVENT_STATUS_PASSED, DEM_EVENT_STATUS_FAILED */

      /* stop any running timer */
      DebounceStatus->InternalTimer = 0U;
      DebounceStatus->Direction = *EventStatus;

      break;

  } /* event status */

  DBG_DEM_DEBOUNCEEVENTTIMEBASED_EXIT(EventId, EventStatus);
}
#endif /* (DEM_NUM_DEBOUNCE_TIME > 0U) */

/*------------------[return FDC for an event]-------------------------------*/

#if (DEM_NUM_DEBOUNCE_COUNTER > 0U)
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_GetFDCCounterBased(
  Dem_EventIdType                                                     EventId,
  CONSTP2VAR(Dem_FaultDetectionCounterType, AUTOMATIC, DEM_APPL_DATA) FDC)
{
  const Dem_EventIdType DebounceIdx = Dem_GbiDebounceIdx(EventId);
  CONSTP2CONST(Dem_DebounceCounterCfgType, AUTOMATIC, DEM_CONST)
    DebounceCfg = &Dem_DebounceCounterCfg[DebounceIdx];
  CONSTP2VAR(Dem_DebounceCounterStatusType, AUTOMATIC, DEM_VAR_NOINIT)
    DebounceStatus = &Dem_DebounceCounterStatus[DebounceIdx];

  DBG_DEM_GETFDCCOUNTERBASED_ENTRY(EventId, FDC);

  /* passed region */
  /* deriving FDC linearly from internal counter */
  if (DebounceStatus->InternalCounter < 0)
  {
    /* DEM_FDC_VALUE_PASSED needs to be muliplied first with the counter value
       before dividing counter value with threshold in order to avoid
       floating-point calculation */
    *FDC = (Dem_FaultDetectionCounterType)
      (((sint32)(DebounceStatus->InternalCounter) * DEM_FDC_VALUE_PASSED) /
       DebounceCfg->CounterPassedThreshold);
  }
  else /* failed region */
  {
    /* DEM_FDC_VALUE_FAILED needs to be muliplied first with the counter value
       before dividing counter value with threshold in order to avoid
       floating-point calculation */
    *FDC = (Dem_FaultDetectionCounterType)
      (((sint32)(DebounceStatus->InternalCounter) * DEM_FDC_VALUE_FAILED) /
       DebounceCfg->CounterFailedThreshold);
  }

  DBG_DEM_GETFDCCOUNTERBASED_EXIT(E_OK, EventId, FDC);
  return E_OK;
}
#endif /* (DEM_NUM_DEBOUNCE_COUNTER > 0U) */

#if (DEM_NUM_DEBOUNCE_FREQUENCY > 0U)
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_GetFDCFrequencyBased(
  Dem_EventIdType                                                     EventId,
  CONSTP2VAR(Dem_FaultDetectionCounterType, AUTOMATIC, DEM_APPL_DATA) FDC)
{
  const Dem_EventIdType DebounceIdx = Dem_GbiDebounceIdx(EventId);
  CONSTP2CONST(Dem_DebounceFrequencyCfgType, AUTOMATIC, DEM_CONST)
    DebounceCfg = &Dem_DebounceFrequencyCfg[DebounceIdx];
  CONSTP2VAR(Dem_DebounceFrequencyStatusType, AUTOMATIC, DEM_VAR_NOINIT)
    DebounceStatus = &Dem_DebounceFrequencyStatus[DebounceIdx];

  DBG_DEM_GETFDCFREQUENCYBASED_ENTRY(EventId, FDC);

  /* timer is running */
  if (DebounceStatus->InternalTimer != 0U)
  {
    /* DEM_FDC_VALUE_PASSED/FAILED needs to be muliplied first with the
       counter value before dividing counter value with threshold in order to
       avoid floating-point calculation */
    *FDC = (Dem_FaultDetectionCounterType)
      (((sint32)(DebounceStatus->FailedCounter) * DEM_FDC_VALUE_FAILED) /
       ((sint32)DebounceCfg->ThresholdBeforeEvFailed + 1)) +
      (Dem_FaultDetectionCounterType)
      (((sint32)DebounceStatus->PassedCounter * DEM_FDC_VALUE_PASSED) /
       ((sint32)DebounceCfg->ThresholdBeforeEvPassed + 1));
  }
  else /* timer is not running */
  {
    if (DebounceStatus->Status == DEM_EVENT_STATUS_PASSED)
    {
      *FDC = DEM_FDC_VALUE_PASSED;
    }
    else if (DebounceStatus->Status == DEM_EVENT_STATUS_FAILED)
    {
      *FDC = DEM_FDC_VALUE_FAILED;
    }
    else
    {
      *FDC = 0;
    }
  }

  DBG_DEM_GETFDCFREQUENCYBASED_EXIT(E_OK, EventId, FDC);
  return E_OK;
}
#endif /* (DEM_NUM_DEBOUNCE_FREQUENCY > 0U) */

#if (DEM_NUM_DEBOUNCE_TIME > 0U)
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_GetFDCTimeBased(
  Dem_EventIdType                                                     EventId,
  CONSTP2VAR(Dem_FaultDetectionCounterType, AUTOMATIC, DEM_APPL_DATA) FDC)
{
  const Dem_EventIdType DebounceIdx = Dem_GbiDebounceIdx(EventId);
  CONSTP2CONST(Dem_DebounceTimeCfgType, AUTOMATIC, DEM_CONST)
    DebounceCfg = &Dem_DebounceTimeCfg[DebounceIdx];
  CONSTP2VAR(Dem_DebounceTimeStatusType, AUTOMATIC, DEM_VAR_NOINIT)
    DebounceStatus = &Dem_DebounceTimeStatus[DebounceIdx];

  DBG_DEM_GETFDCTIMEBASED_ENTRY(EventId, FDC);

  if (DebounceStatus->Direction != DEM_EVENT_STATUS_UNQUALIFIED)
  {
    /* deriving FDC linearly from internal timer */
    if ((DebounceStatus->Direction == DEM_EVENT_STATUS_PASSED) ||
       (DebounceStatus->Direction == DEM_EVENT_STATUS_PREPASSED))
    {
      /* DEM_FDC_VALUE_PASSED needs to be muliplied first with the counter
         value before dividing counter value with threshold in order to avoid
         floating-point calculation */
      *FDC = (Dem_FaultDetectionCounterType)
        ((((sint32)(DebounceCfg->TimePassedThreshold) -
           (sint32)(DebounceStatus->InternalTimer)) * DEM_FDC_VALUE_PASSED) /
         (sint32)DebounceCfg->TimePassedThreshold);
    }
    else
    {
      /* DEM_FDC_VALUE_FAILED needs to be muliplied first with the counter
         value before dividing counter value with threshold in order to avoid
         floating-point calculation */
      *FDC = (Dem_FaultDetectionCounterType)
        ((((sint32)(DebounceCfg->TimeFailedThreshold) -
           (sint32)(DebounceStatus->InternalTimer)) * DEM_FDC_VALUE_FAILED) /
         (sint32)DebounceCfg->TimeFailedThreshold);
    }
  }
  else /* unqualified state */
  {
    *FDC = 0;
  }

  DBG_DEM_GETFDCTIMEBASED_EXIT(E_OK, EventId, FDC);
  return E_OK;
}
#endif /* (DEM_NUM_DEBOUNCE_TIME > 0U) */


#if (DEM_NUM_FAILURECYCLES > 0U)
STATIC FUNC(void, DEM_CODE) Dem_UpdateFailureCounterFirstFail(
  const Dem_EventIdType     EventId,
  const Dem_EventStatusType EventStatus)
{
  uint8 EventFailureClassIdx = Dem_GbiEventFailureClassIdx(EventId);

  DBG_DEM_UPDATEFAILURECOUNTERFIRSTFAIL_ENTRY(EventId, EventStatus);

  /* if fault confirmation is configured for the event */
  if (EventFailureClassIdx != DEM_NO_FAULT_CONFIRMATION)
  {
    Dem_OperationCycleIdType EventFailureCycleIdx =
      Dem_EventFailureCycleCfg[EventFailureClassIdx].EventFailureCycleIdx;

    /* for unconfirmed DTC
     * with event failure cycle different from operation cycle,
     * failure cycle started and
     * first failure report for the event in this operation cycle */
    if ( (!DEM_IS_EV_ST_BIT_CDTC_SET(EventId)) &&
         /* Deviation MISRA-1 <+3> */
         ( ( (EventFailureCycleIdx != Dem_GbiOpCycleIdx(EventId)) &&
             (DEM_OPCYCLESTATE[EventFailureCycleIdx] == DEM_CYCLE_STATE_START)
           ) &&
           ( (EventStatus == DEM_EVENT_STATUS_FAILED) &&
             (!DEM_IS_EV_ST_BIT_TFTOC_SET(EventId))
           )
         )
       )
    {
      Dem_IncrementFailureCounter(EventId);
    }
  }

  DBG_DEM_UPDATEFAILURECOUNTERFIRSTFAIL_EXIT(EventId, EventStatus);
}
#endif


#if (DEM_C_CALLBACK_TABLE_TRIG_ON_EVST_SIZE > 0U)
STATIC FUNC(void, DEM_CODE) Dem_GetCallbackIndex(
  Dem_EventIdType                                           EventId,
  CONSTP2CONST(Dem_CbLookupTableType, AUTOMATIC, DEM_CONST) LookupTable,
  uint16                                                    TableSize,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_VAR)                    StartIdx,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_VAR)                    LastIdx)
{
  uint16 Idx = 0U;

  DBG_DEM_GETCALLBACKINDEX_ENTRY(
    EventId, LookupTable, TableSize, StartIdx, LastIdx);

  /* search for first matching CbIdx-lookup-table entry */
  while ( (Idx < TableSize) && (LookupTable[Idx].EventId != EventId) )
  {
    Idx++;
  }

  /* check if (at least) one matching entry was found */
  DEM_PRECONDITION_ASSERT((Idx < TableSize), DEM_INTERNAL_API_ID);

  *StartIdx = Idx;

  /* search for last matching CbIdx-lookup-table entry */
  do
  {
    Idx++;
  }
  while ( (Idx < TableSize) && (LookupTable[Idx].EventId == EventId) );

  *LastIdx = Idx - 1U;

  DBG_DEM_GETCALLBACKINDEX_EXIT(
    EventId, LookupTable, TableSize, StartIdx, LastIdx);
}
#endif /* (DEM_C_CALLBACK_TABLE_TRIG_ON_EVST_SIZE > 0U) */

#if (DEM_RTE_CALLBACK_TABLE_TRIG_ON_EVST_SIZE > 0U)
STATIC FUNC(void, DEM_CODE) Dem_GetRteCallbackIndex(
  Dem_EventIdType                                     EventId,
  CONSTP2CONST(Dem_EventIdType, AUTOMATIC, DEM_CONST) LookupTable,
  uint16                                              TableSize,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_VAR)              StartIdx,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_VAR)              LastIdx)
{
  uint16 Idx = 0U;

  DBG_DEM_GETRTECALLBACKINDEX_ENTRY(
    EventId, LookupTable, TableSize, StartIdx, LastIdx);

  /* search for first matching CbIdx-lookup-table entry */
  while ( (Idx < TableSize) && (LookupTable[Idx] != EventId) )
  {
    Idx++;
  }

  /* check if (at least) one matching entry was found */
  DEM_PRECONDITION_ASSERT((Idx < TableSize), DEM_INTERNAL_API_ID);

  *StartIdx = Idx;

  /* search for last matching CbIdx-lookup-table entry */
  do
  {
    Idx++;
  }
  while ( (Idx < TableSize) && (LookupTable[Idx] == EventId) );

  *LastIdx = Idx - 1U;

  DBG_DEM_GETRTECALLBACKINDEX_EXIT(
    EventId, LookupTable, TableSize, StartIdx, LastIdx);
}
#endif /* (DEM_RTE_CALLBACK_TABLE_TRIG_ON_EVST_SIZE > 0U) */

#if (DEM_NUM_INDICATOR_LINKS > 0U)
STATIC FUNC(boolean, DEM_CODE) Dem_CheckForEventWIRUpdate(
  const Dem_EventIdType     EventId,
  const Dem_EventStatusType EventStatus,
  CONSTP2VAR(Dem_EventIdType, AUTOMATIC, AUTOMATIC)
    WIROnCritFulfilledFlagsIdx)
{
  boolean result = FALSE;

  DBG_DEM_CHECKFOREVENTWIRUPDATE_ENTRY(
    EventId, EventStatus, WIROnCritFulfilledFlagsIdx);

  if ( ( DEM_IS_EV_ST_BIT_CDTC_SET(EventId) &&
         (!DEM_IS_EV_ST_BIT_WIR_SET(EventId)) ) &&
       /* Deviation MISRA-1 <+3> */
       ( (Dem_GbiIndicatorUsed(EventId) != FALSE) &&
         (EventStatus == DEM_EVENT_STATUS_FAILED) )
     )
  {
    Dem_IndicatorLnkIdxType LinkIdx;
    Dem_CounterDataIdxType CounterDataIdx;
    Dem_FailureCycleCounterInfoIdxType FailureCycleCounterInfoIdx;

    *WIROnCritFulfilledFlagsIdx =
      Dem_GetWIROnCriteriaFulfilledFlagsIdx(EventId);

    if (DEM_IS_BIT_SET_IN_ARRAY(
          Dem_WIROnCriteriaFulfilledFlags, *WIROnCritFulfilledFlagsIdx))
    {
      for (LinkIdx = 0U; LinkIdx < DEM_NUM_INDICATOR_LINKS; ++LinkIdx)
      {
        if (Dem_IndicatorLink[LinkIdx].EventId == EventId)
        {
          CounterDataIdx = Dem_IndicatorLink[LinkIdx].CounterDataIdx;
          FailureCycleCounterInfoIdx =
            Dem_IndicatorLink[LinkIdx].FailureCycleCounterInfoIdx;

          if ( (DEM_IS_BIT_SET_IN_ARRAY(DEM_INDICATOR_CYC_COUNTER_WIR_STATUS,
                                        CounterDataIdx)) ||
               (Dem_FailureCycleCounterInfo[FailureCycleCounterInfoIdx].
                  Threshold == 0U)
             )
          {
            /* !LINKSTO dsn.Dem.IndicatorCycleCounterWIRStatus,1 */
            DEM_ATOMIC_SET_BIT_IN_ARRAY_8(DEM_INDICATOR_CYC_COUNTER_WIR_STATUS,
                                          CounterDataIdx);
            result = TRUE;
          }
        }
      }
    }
  }

  DBG_DEM_CHECKFOREVENTWIRUPDATE_EXIT(
    result, EventId, EventStatus, WIROnCritFulfilledFlagsIdx);
  return result;
}
#endif /* (DEM_NUM_INDICATOR_LINKS > 0U) */

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
FUNC(Dem_NvMGatePrepStatusType, DEM_CODE) Dem_BeginPrepareGateEntry(
  uint8 OriginIdx)
{
  Dem_NvMGatePrepStatusType NvMGateStatus;

  DBG_DEM_BEGINPREPAREGATEENTRY_ENTRY(OriginIdx);

  /*
   * ENTER critical section to protect the Nv_Status
   *       call-context: to be re-analyzed
   */
  SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

  if (DEM_NVM_IDLE == Dem_NvMStatus[OriginIdx].Status)
  {
    Dem_NvMStatus[OriginIdx].Status = DEM_NVM_PREPARE;

    /* gate is ready for copying data */
    NvMGateStatus = DEM_GATE_READY;
  }
  else
  {
    /* gate is NOT ready for copying data by the current process */
    NvMGateStatus = DEM_GATE_LOCKED;
  }

  /*
   * LEAVE critical section
   */
  SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

  DBG_DEM_BEGINPREPAREGATEENTRY_EXIT(NvMGateStatus, OriginIdx);

  return NvMGateStatus;
}

FUNC(void, DEM_CODE) Dem_EndPrepareGateEntry(
  uint8 OriginIdx,
  Dem_NvMGateStatusType NvMGateStatus)
{
  DBG_DEM_ENDPREPAREGATEENTRY_ENTRY(OriginIdx, NvMGateStatus);

  /*
   * ENTER critical section to protect the Nv_Status
   *       call-context: to be re-analyzed
   */
  SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

  if (DEM_GATE_PREPARED == NvMGateStatus)
  {
    /* gate is waiting to be written to NvM */
    Dem_NvMStatus[OriginIdx].Status = DEM_NVM_WAITING;
  }
  else if (DEM_GATE_READY == NvMGateStatus)
  {
    /* no more entry has been prepared to written to NvM */
    Dem_NvMStatus[OriginIdx].Status = DEM_NVM_IDLE;
  }
  else
  {
    /* gate was locked by another process, do not touch Dem_NvMStatus */
  }

  /*
   * LEAVE critical section
   */
  SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

  DBG_DEM_ENDPREPAREGATEENTRY_EXIT(OriginIdx, NvMGateStatus);
}
#endif /* (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON) */

#define DEM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[end of file]===========================================*/
