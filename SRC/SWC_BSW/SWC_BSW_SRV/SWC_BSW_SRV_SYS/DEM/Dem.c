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

/* This file contains definitions for interface functions provided by Dem to
 * the Ecu State Manager and SW-Components. */

/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 16.7 (required)
 *    "A pointer parameter in a function prototype should be declared as
 *     pointer to const if the pointer is not used to modify the
 *     addressed object."
 *
 *    Reason:
 *    Pointer parameter is not modified in some configuration variants
 *    or functionality is not currently implemented.
 *
 *  MISRA-2) Deviated Rule: 12.4 (required)
 *    "The right-hand operand of a logical '&&' or '||' operator shall not
 *    contain side effects."
 *
 *    Reason:
 *    Call to getter functions which do not modify any global state.
 */

/*==================[inclusions]============================================*/
/* !LINKSTO dsn.Dem.IncludeStr,1 */

#include <Std_Types.h>                            /* AUTOSAR standard types */
#include <TSAutosar.h>                        /* EB specific standard types */
#include <TSMem.h>                          /* EB specific memory functions */

/* !LINKSTO dsn.Dem.SchMUsage,1 */
#include <SchM_Dem.h>             /* for the locking of the exclusive areas */

#include <Dem_Int.h>             /* Module public and internal declarations */
#include <Dem_Trace.h>                        /* Dbg related macros for Dem */

#if (DEM_USE_PERMANENT_STORAGE == STD_ON)
#include <NvM.h>                                      /* Memory Access APIs */
#endif

/*==================[macros]================================================*/
/* !LINKSTO Dem.Version.Check,2 */

/*------------------[AUTOSAR vendor identification check]-------------------*/

#if (!defined DEM_VENDOR_ID) /* configuration check */
#error DEM_VENDOR_ID must be defined
#endif

#if (DEM_VENDOR_ID != 1U) /* vendor check */
#error DEM_VENDOR_ID has wrong vendor id
#endif

/*------------------[AUTOSAR release version identification check]----------*/

#if (!defined DEM_AR_RELEASE_MAJOR_VERSION) /* configuration check */
#error DEM_AR_RELEASE_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (DEM_AR_RELEASE_MAJOR_VERSION != 4U)
#error DEM_AR_RELEASE_MAJOR_VERSION wrong (!= 4U)
#endif

#if (!defined DEM_AR_RELEASE_MINOR_VERSION) /* configuration check */
#error DEM_AR_RELEASE_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (DEM_AR_RELEASE_MINOR_VERSION != 0U )
#error DEM_AR_RELEASE_MINOR_VERSION wrong (!= 0U)
#endif

#if (!defined DEM_AR_RELEASE_REVISION_VERSION) /* configuration check */
#error DEM_AR_RELEASE_REVISION_VERSION must be defined
#endif

/* revision version check */
#if (DEM_AR_RELEASE_REVISION_VERSION != 3U )
#error DEM_AR_RELEASE_REVISION_VERSION wrong (!= 3U)
#endif

/*------------------[AUTOSAR module version identification check]-----------*/

#if (!defined DEM_SW_MAJOR_VERSION) /* configuration check */
#error DEM_SW_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (DEM_SW_MAJOR_VERSION != 5U)
#error DEM_SW_MAJOR_VERSION wrong (!= 5U)
#endif

#if (!defined DEM_SW_MINOR_VERSION) /* configuration check */
#error DEM_SW_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (DEM_SW_MINOR_VERSION < 9U)
#error DEM_SW_MINOR_VERSION wrong (< 9U)
#endif

#if (!defined DEM_SW_PATCH_VERSION) /* configuration check */
#error DEM_SW_PATCH_VERSION must be defined
#endif

/* patch version check */
#if (DEM_SW_PATCH_VERSION < 25U)
#error DEM_SW_PATCH_VERSION wrong (< 25U)
#endif

/*==================[type definitions]======================================*/

/** \brief Type of event memory entry allocation result */
typedef enum
{
  DEM_EVENTENTRYALLOC_INVALID   = 0,           /**< entry allocation failed */
  DEM_EVENTENTRYALLOC_ALLOCATED = 1,               /**< new entry allocated */
  DEM_EVENTENTRYALLOC_REPLACED  = 2,           /**< existing entry replaced */
  DEM_EVENTENTRYALLOC_EXISTS    = 3            /**< existing entry selected */
} Dem_EventEntryAllocResultType;

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

#define DEM_START_SEC_CODE
#include <MemMap.h>

#if (DEM_USE_PERMANENT_STORAGE == STD_ON)
/** \brief Function to get the status of the Dem's default NvM block from NvM
 **
 ** This is an interface function to the NvM, to get the status of the default
 ** NvM block.
 **
 ** \return Std_ReturnType value indication success
 ** \retval E_OK     the block was restored successfully from NVRAM
 ** \retval E_NOT_OK the block was NOT restored successfully from NVRAM
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_NvMGetNvRAMDataStatus(void);
#endif

/** \brief Function to reset the non-volatile Dem data
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 **
 ** \note Implementation is OEM specific.
 */
STATIC FUNC(void, DEM_CODE) Dem_ResetNvData(void);

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
/** \brief Function to restore the non-volatile Dem data immediately
 ** via NvM single block read functionality
 **
 ** If data restore fails then entry status is set such that either the reset
 ** data or new event data shall be written persistently during shutdown
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 **
 */
STATIC FUNC(void, DEM_CODE) Dem_RestoreImmediateData(void);
#endif

#if (DEM_MAX_NUMBER_PRESTORED_FF > 0U)
/** \brief Function to get the entry data pointer of a prestored freeze frame
 **
 ** This is done by searching in the event description array and adding all
 ** several freeze frame class sizes.
 **
 ** ATTENTION: If an event ID where prestorage of freeze frames is disabled
 ** is given, the entry data pointer of the last event where prestorage is
 ** enabled is returned.
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 **
 ** \return Pointer to the prestored freeze frame entry data
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Dem_EntryDataPtrType, DEM_CODE) Dem_GetPFFEntryDataPtr(
  Dem_EventIdType EventId);
#endif

#if (DEM_USE_AGING == STD_ON)
/** \brief Function to update the Aging counter of the given event Id, if an
 ** entry exists
 **
 ** The entry will be deleted, if the aging counter reaches 0(zero).
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_UpdateAgingCounter(
  const Dem_EventIdType EventId);
#endif /* DEM_USE_AGING */

/** \brief Function to get the value of the specified event status extended
 ** bit of the given event
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[in] EventStatusExtendedMask  only DEM_DTCSTATUSBIT_XXX values
 **
 ** \return Boolean value of the bit
 ** \retval TRUE  bit is set
 ** \retval FALSE bit is not set
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(boolean, DEM_CODE) Dem_GetEvStBitVal(
  Dem_EventIdType             EventId,
  Dem_EventStatusExtendedType EventStatusExtendedMask);

#if ( (DEM_USE_CB_TRIG_ON_EVST  == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) || \
      ( (DEM_USE_CB_TRIG_ON_EVDAT == STD_ON) && \
        ( (DEM_NUM_EDSEGS > 0U) || (DEM_NUM_FFSEGS > 0U) ) ) )
/** \brief Function to send event status notification messages
 **
 ** This function is used by the main function to notify (callback) all
 ** registered clients about event status changes done in ProcessEventEntry()
 **
 ** \param[in] Notification  Event status and trigger for messages
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ProcessEventNotifications(
  const Dem_EventNotificationDataPtrType Notification);
#endif

/** \brief This function adds a new or updates an existing entry in the event
 ** memory, including its entry data
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[in] EventStatus  status of event, either ::DEM_EVENT_STATUS_PASSED
 **               or ::DEM_EVENT_STATUS_FAILED
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ProcessEventEntry(
  const Dem_EventIdType     EventId,
  const Dem_EventStatusType EventStatus,
  const Dem_EventNotificationDataPtrType Notification);

#if (DEM_NUM_BSWEVENT_INDICATOR_USED > 0U)
/** \brief Function to set WIR-bit of BSW event, if indicator OnCriteria of the
 ** BSW event has been satisfied
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ProcessBSWEventWIRBit(void);
#endif

/** \brief This function tries to find an existing entry in the event memory
 ** or tries to allocate or replace an entry
 **
 ** It is used by Dem_ProcessEventEntry() to retrieve an event memory data
 ** element to store or update an event.
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[out] EvMemEntryPtr  Pointer to the event memory entry to be used
 ** \param[out] ReplacedEventIdPtr  EventId of the replaced event
 **
 ** \return Allocation result
 ** \retval DEM_EVENTENTRYALLOC_REPLACED
 ** \retval DEM_EVENTENTRYALLOC_ALLOCATED
 ** \retval DEM_EVENTENTRYALLOC_INVALID
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Dem_EventEntryAllocResultType, DEM_CODE)
  Dem_FindOrAllocateEventEntry(
    const Dem_EventIdType                             EventId,
    CONSTP2VAR(Dem_EventMemoryEntryPtrType, AUTOMATIC, AUTOMATIC) EvMemEntryPtr,
    CONSTP2VAR(Dem_SizeEvMemEntryType, AUTOMATIC, AUTOMATIC)      EvMemIdxPtr,
    CONSTP2VAR(Dem_EventIdType, AUTOMATIC, AUTOMATIC) ReplacedEventIdPtr,
    const Dem_EventStatusChangedMsgPtrType            EventStatusChangedMsgPtr);

/** \brief This function tries to replace an exisiting event entry with a
 ** new event
 **
 ** It is used by Dem_FindOrAllocateEventEntry() in case it could not find
 ** an empty entry to be allocated.
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[in] originIdx  Index specifying the event memory type
 ** \param[out] EvMemEntryPtr  Pointer to the event memory entry to be used
 ** \param[out] ReplacedEventIdPtr  EventId of the replaced event
 **
 ** \return Allocation result
 ** \retval DEM_EVENTENTRYALLOC_REPLACED  Event entry successfully replaced
 ** \retval DEM_EVENTENTRYALLOC_INVALID  Unable to replace an event entry
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Dem_EventEntryAllocResultType, DEM_CODE) Dem_ReplaceEventEntry(
  const Dem_EventIdType EventId,
  const uint8           originIdx,
  CONSTP2VAR(Dem_EventMemoryEntryPtrType, AUTOMATIC, AUTOMATIC) EvMemEntryPtr,
  CONSTP2VAR(Dem_SizeEvMemEntryType, AUTOMATIC, AUTOMATIC)      EvMemIdxPtr,
  CONSTP2VAR(Dem_EventIdType, AUTOMATIC, AUTOMATIC) ReplacedEventIdPtr,
  const Dem_EventStatusChangedMsgPtrType            EventStatusChangedMsgPtr);

#if (DEM_NUM_FFSEGS > 0U)
/** \brief Function which processes the freeze frame data of a reported event
 **
 ** It is used by Dem_ProcessEventEntry().
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[in] EvMemEntryPtr  Pointer to event memory entry where to store
 **                           data
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(boolean, DEM_CODE) Dem_ProcessEventEntryFFData(
  const Dem_EventIdType                  EventId,
  const Dem_EventMemoryEntryPtrConstType EvMemEntryPtr);

/** \brief Function to store a complete freeze frame at the specified position
 ** in memory, by using the RTE-callback function
 **
 ** \param[in] ServiceId  only in DEM_DEV_ERROR_DETECT lib-variant
 ** \param[in] FFEntryData
 ** \param[in] FFClass
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_StoreFF(
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  uint8                                               ServiceId,
#endif /* DEM_DEV_ERROR_DETECT */
  const Dem_EntryDataPtrType                          FFEntryData,
  CONSTP2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) FFClass);
#endif

#if (DEM_NUM_EDSEGS > 0U)
/** \brief Function which processes the extended data of a reported event
 **
 ** It is used by Dem_ProcessEventEntry().
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[in] EvMemEntryPtr  Pointer to event memory entry where to store
 **                           data
 ** \param[in] eventEntryAllocResult  Information if event is new or replaced
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(boolean, DEM_CODE) Dem_ProcessEventEntryEData(
  const Dem_EventIdType                  EventId,
  const Dem_EventMemoryEntryPtrConstType EvMemEntryPtr,
  Dem_EventEntryAllocResultType          eventEntryAllocResult);

/** \brief Function to store the complete extended data at the specified
 ** position in memory, by using the RTE-callback function
 **
 ** \param[in] EDEntryData
 ** \param[in] EDClass
 ** \param[in] EntryExists
 **
 ** \return Result of ED storage/update
 ** \retval TRUE  ED storage/update was done
 ** \retval FALSE ED storage/update was not required
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(boolean, DEM_CODE) Dem_StoreED(
  const Dem_EntryDataPtrType                          EDEntryData,
  CONSTP2CONST(Dem_EDClassType, AUTOMATIC, DEM_CONST) EDClass,
  boolean                                             EntryExists);

/** \brief Function to assemble the extended data class to translate and
 ** transfer internal data-structures into correct output-buffer format/layout
 **
 ** \param[in] EDClass
 ** \param[in] DestBuffer
 ** \param[in] EvMemEntry
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_AssembleExtendedData(
  CONSTP2CONST(Dem_EDClassType, AUTOMATIC, DEM_CONST) EDClass,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)              DestBuffer,
  const Dem_EventMemoryEntryPtrConstType              EvMemEntry);
#endif

/** \brief Function to search for an empty entry in the given event memory
 **
 ** \param[in] OriginIdx  0 <= OriginIdx < DEM_MAXNUM_ORIGINS
 ** \param[out] FoundEntry
 **
 ** \return Result of the searching
 ** \retval TRUE  entry was found
 ** \retval FALSE no entry exists
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(boolean, DEM_CODE) Dem_SearchForEmptyEntry(
  const uint8                                                 OriginIdx,
  CONSTP2VAR(Dem_EventMemoryEntryPtrType, AUTOMATIC, DEM_VAR) FoundEntry,
  CONSTP2VAR(Dem_SizeEvMemEntryType, AUTOMATIC, AUTOMATIC)    FoundEntryIdx);

#if (DEM_USE_EVENT_DISPLACEMENT == STD_ON)
/** \brief Function to search for a replaceable entry in the event memory by
 ** the given event Id using specific displacement-search-algorithm
 **
 ** \param[in] OriginIdx  0 <= OriginIdx < DEM_MAXNUM_ORIGINS
 ** \param[in] NewEventId  0 < EventId <= Dem_MaxEventId
 ** \param[out] FoundEntry
 **
 ** \return Result of the searching
 ** \retval TRUE  entry was found
 ** \retval FALSE no entry exists
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(boolean, DEM_CODE) Dem_SearchForEntryToReplace(
  uint8                                                         OriginIdx,
  Dem_EventIdType                                               NewEventId,
  CONSTP2VAR(Dem_EventMemoryEntryPtrType, AUTOMATIC, AUTOMATIC) FoundEntry,
  CONSTP2VAR(Dem_SizeEvMemEntryType, AUTOMATIC, AUTOMATIC)      FoundEntryIdx);

/** \brief Function to update the value of the occurrence order of the event,
 ** which is used for processing event displacement
 **
 ** \param[in] UpdatedEvMemEntry
 **
 ** \return Result of the occurrence order update
 ** \retval TRUE  occurrence order was updated
 ** \retval FALSE occurrence order was not updated
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(boolean, DEM_CODE) Dem_UpdateOccurrenceOrder(
  Dem_EventMemoryEntryPtrType UpdatedEvMemEntry);

/** \brief Function to re-arrange the occurrence order of events, which is used
 ** while processing event displacement, when the occurrence order threshold is
 ** reached for a memory
 **
 ** \param[in] Origin  0 < Origin < DEM_MAXNUM_ORIGINS
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_RearrangeOccurrenceOrder(
  const uint8 originIdx);

/** \brief Function to initialize array used to store the current largest value
 ** of the occurrence order of events, which is used for processing event
 ** displacement
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_InitMaxOccOrder(void);
#endif /* DEM_USE_EVENT_DISPLACEMENT == STD_ON */

#if (DEM_NUM_FAILURECYCLES > 0U)
/** \brief This function sets the ConfirmedDTC bit for all events in event
 ** memory, whose event failure counter has reached its threshold value
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ProcessFaultConfirmation(void);

/** \brief This function resets the event failure counter if the event
 ** is tested and never failed in the operation cycle
 **
 ** \param[in] EventId          1 < EventId <= DEM_MAX_EVENTID
 ** \param[in] OperationCycleId Identification of operation cycle
 **                             (0 <= OpCycleId < DEM_NUM_OPCYCLES)
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ProcessFailureCounterReset(
  const Dem_EventIdType          EventId,
  const Dem_OperationCycleIdType OperationCycleId);

/** \brief Updates failure counter at the start of failure cycle
 **
 ** \param[in] EventId          1 < EventId <= DEM_MAX_EVENTID
 ** \param[in] OperationCycleId Identification of operation cycle
 **                             (0 <= OpCycleId < DEM_NUM_OPCYCLES)
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_UpdateFailureCounterCycleStart(
  const Dem_EventIdType          EventId,
  const Dem_OperationCycleIdType OperationCycleId);

#if (DEM_EVENTFAILURECOUNTER_BUFFER_SIZE > 0U)
/** \brief Function to search for an entry in event failure counter buffer
 ** by the given event Id
 **
 ** \param[in] EventId
 ** \param[out] FailureCounterBufferIdx
 **
 ** \return Result of the searching
 ** \retval TRUE  entry was found
 ** \retval FALSE no entry exists
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(boolean, DEM_CODE) Dem_SearchForFailureCounterBufferEntry(
  const Dem_EventIdType                 EventId,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_VAR) FailureCounterBufferIdx);
#endif /* (DEM_EVENTFAILURECOUNTER_BUFFER_SIZE > 0U) */
#endif /* (DEM_NUM_FAILURECYCLES > 0U) */

#if ( (DEM_USE_CB_TRIG_ON_EVDAT == STD_ON) && \
      (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON) )
/** \brief Function to check whether the given Internal Data Element is mapped
 ** for the EventId
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[in] DataElementIdx
 **
 ** \return Result of the check
 ** \retval TRUE  given Internal Data Element is mapped for the EventId
 ** \retval FALSE given Internal Data Element is not mapped for the EventId
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(boolean, DEM_CODE) Dem_CheckIntDataElementUsage(
  const Dem_EventIdType        EventId,
  const Dem_DataElementIdxType DataElementIdx);

/** \brief Function to call Event data changed callback for all the events in
 ** the event memory for which the event memory overflow indication internal
 ** data element exists
 **
 ** \param[in] OriginIdx  0 <= OriginIdx < DEM_MAXNUM_ORIGINS
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_CbTriggerOnOvfIndSet(const uint8 OriginIdx);
#endif /* (DEM_USE_CB_TRIG_ON_EVDAT == STD_ON) &&
          (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON) */

#if (DEM_NUM_INDICATOR_LINKS > 0U)
/** \brief Function which processes the indicator cycle counter
 **
 ** \param[in] OperationCycleId  Identification of operation cycle, like power
 **                     cycle, driving cycle,  ... (0 <= OpCycleId < DEM_NUM_OPCYCLES)
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ProcessHealing(
  Dem_OperationCycleIdType OperationCycleId);

/** \brief Function which processes the healing cycle counter
 **
 ** It is used by Dem_ProcessHealing().
 **
 ** \param[in] IndicatorLinkIdx
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ProcessHealingCycleCounter(
  const Dem_IndicatorLnkIdxType IndicatorLinkIdx);

/** \brief Function which processes the failure cycle counter
 **
 ** It is used by Dem_ProcessHealing().
 **
 ** \param[in] IndicatorLinkIdx  0 < IndicatorLinkIdx <= DEM_NUM_INDICATOR_LINKS
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ProcessFailureCycleCounter(
  const Dem_IndicatorLnkIdxType IndicatorLinkIdx);

/** \brief Function to check the Warning indicator Off-Criteria of the event
 **
 ** It is used by Dem_ProcessHealingCycleCounter().
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 **
 ** \return Boolean value indicating whether Warning indicator Off-Criteria is
 **         fulfilled or not.
 ** \retval TRUE   Warning indicator Off-Criteria is fulfilled
 ** \retval FALSE  Warning indicator Off-Criteria is not fulfilled
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 **/
STATIC FUNC(boolean, DEM_CODE) Dem_CheckWIROffCriteriaFulfilled(
  const Dem_EventIdType EventId);

/** \brief Function which update the behaviour of indicator cycle counter
 **
 ** \param[in] CounterDataIdx  0 < CounterDataIdx <= DEM_NUM_INDICATOR_LINKS
 ** \param[in] CounterDataRole
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_SetCycleCounterRole(
  const Dem_CounterDataIdxType CounterDataIdx,
  Dem_IndicatorCounterDataRoleType CounterDataRole);
#endif /* (DEM_NUM_INDICATOR_LINKS > 0U) */

#define DEM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal data]=========================================*/

#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief Index of first entry in queue to read */
STATIC VAR(Dem_ErrorQueueIdxType, DEM_VAR_NOINIT) Dem_ErrorQueueReadIdx;

/** \brief Index of next entry in queue to write */
STATIC VAR(Dem_ErrorQueueIdxType, DEM_VAR_NOINIT) Dem_ErrorQueueWriteIdx;

#if (DEM_SIZE_PFF_ENTRY_DATA != 0U)
/** \brief Entry area for possible prestored freeze frames */
STATIC VAR(Dem_EntryDataType, DEM_VAR_NOINIT)
  Dem_PFFEntryDataArea[DEM_SIZE_PFF_ENTRY_DATA];
#endif

#if (DEM_USE_EVENT_DISPLACEMENT == STD_ON)
/** \brief Array which stores the value of current largest occurrence order
 ** of the events for each event memory
 */
STATIC VAR(Dem_OccOrderType, DEM_VAR_NOINIT)
  Dem_MaxOccOrder[DEM_MAXNUM_ORIGINS];
#endif

/*------[variables for event memory when Immediate storage is enabled]------*/

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)

/** \brief Primary event memory */
STATIC VAR(Dem_EventMemoryEntryType, DEM_VAR_NOINIT)
  Dem_EventMemoryPrimary[DEM_MAX_NUMBER_EVENT_ENTRY_PRI];

#if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR != 0U)
/* !LINKSTO Dem162_Implicit1,1 */
/** \brief Mirror event memory */
STATIC VAR(Dem_EventMemoryEntryType, DEM_VAR_NOINIT)
  Dem_EventMemoryMirror[DEM_MAX_NUMBER_EVENT_ENTRY_MIR];
#endif

#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U)
/* !LINKSTO Dem162_Implicit1,1 */
/** \brief Permanent event memory */
STATIC VAR(Dem_EventMemoryEntryType, DEM_VAR_NOINIT)
  Dem_EventMemoryPermanent[DEM_MAX_NUMBER_EVENT_ENTRY_PER];
#endif

#if (DEM_MAX_NUMBER_EVENT_ENTRY_SEC != 0U)
/* !LINKSTO Dem162_Implicit1,1 */
/** \brief Secondary event memory */
STATIC VAR(Dem_EventMemoryEntryType, DEM_VAR_NOINIT)
  Dem_EventMemorySecondary[DEM_MAX_NUMBER_EVENT_ENTRY_SEC];
#endif

#if (DEM_SIZE_ENTRY_DATA_PRIMARY != 0U)
/** \brief Primary entry data area */
STATIC VAR(Dem_EntryDataType, DEM_VAR_NOINIT) Dem_EntryDataPrimary[
  DEM_SIZE_ENTRY_DATA_PRIMARY];
#endif

#if (DEM_SIZE_ENTRY_DATA_MIRROR != 0U)
/** \brief Mirror entry data area */
STATIC VAR(Dem_EntryDataType, DEM_VAR_NOINIT) Dem_EntryDataMirror[
  DEM_SIZE_ENTRY_DATA_MIRROR];
#endif

#if (DEM_SIZE_ENTRY_DATA_PERMANENT != 0U)
/** \brief Mirror entry data area */
STATIC VAR(Dem_EntryDataType, DEM_VAR_NOINIT) Dem_EntryDataPermanent[
  DEM_SIZE_ENTRY_DATA_PERMANENT];
#endif

#if (DEM_SIZE_ENTRY_DATA_SECONDARY != 0U)
/** \brief Secondary entry data area */
STATIC VAR(Dem_EntryDataType, DEM_VAR_NOINIT) Dem_EntryDataSecondary[
  DEM_SIZE_ENTRY_DATA_SECONDARY];
#endif

#if (DEM_SIZE_ENTRY_DATA_PRIMARY != 0U)
/** \brief Primary entry data free position */
STATIC VAR(Dem_SizeEntryDataType, DEM_VAR_NOINIT) Dem_EntryDataFreePosPrimary;
#endif

#if (DEM_SIZE_ENTRY_DATA_MIRROR != 0U)
/** \brief Mirror entry data free position */
STATIC VAR(Dem_SizeEntryDataType, DEM_VAR_NOINIT) Dem_EntryDataFreePosMirror;
#endif

#if (DEM_SIZE_ENTRY_DATA_PERMANENT != 0U)
/** \brief Permanent entry data free position */
STATIC VAR(Dem_SizeEntryDataType, DEM_VAR_NOINIT) Dem_EntryDataFreePosPermanent;
#endif

#if (DEM_SIZE_ENTRY_DATA_SECONDARY != 0U)
/** \brief Secondary entry data free position */
STATIC VAR(Dem_SizeEntryDataType, DEM_VAR_NOINIT) Dem_EntryDataFreePosSecondary;
#endif

#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */

/*==================[external data]=========================================*/

/** \brief Queue holding the errors appeared before Dem_Init(), or to be
 ** entered or updated in event memory after Dem_Init()
 */
VAR(Dem_ErrorQueueEntryType, DEM_VAR_NOINIT) Dem_ErrorQueue[
  DEM_BSW_ERROR_BUFFER_SIZE];

/** \brief Non-volatile data of the Dem - Native */
VAR(Dem_NvDataType, DEM_VAR_NOINIT) Dem_NvData;

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
/** \brief NvM write operation (and related gate entry) status per event
 ** memory */
VAR(Dem_NvMStatusType, DEM_VAR_NOINIT) Dem_NvMStatus[DEM_MAXNUM_ORIGINS];
#endif

#if (DEM_CLEAR_DTC_BEHAVIOR != DEM_CLRRESP_VOLATILE)
/** \brief Status of an asynchronous ClearDTC operation */
VAR(Dem_ClearDtcStatusType, DEM_VAR_NOINIT) Dem_ClearDtcAsyncStatus;
#endif

/*-----------------------[variables for gate-entry]-------------------------*/

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)

/* Non-volatile primary data of the Dem */
VAR(Dem_NvGateEntryPrimaryDataType, DEM_VAR_NOINIT)
  Dem_NvGateEntryPrimaryData;

#if (DEM_MAX_NUMBER_EVENT_ENTRY_SEC != 0U)
/* Non-volatile secondary data of the Dem */
VAR(Dem_NvGateEntrySecondaryDataType, DEM_VAR_NOINIT)
  Dem_NvGateEntrySecondaryData;
#endif

#if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR != 0U)
/* Non-volatile mirror data of the Dem */
VAR(Dem_NvGateEntryMirrorDataType, DEM_VAR_NOINIT)
  Dem_NvGateEntryMirrorData;
#endif

#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U)
/* Non-volatile permanent data of the Dem */
VAR(Dem_NvGateEntryPermanentDataType, DEM_VAR_NOINIT)
  Dem_NvGateEntryPermanentData;
#endif

#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */

#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[external constants]====================================*/

#define DEM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*---------------------------[Dem_EventMem array]---------------------------*/

/** \brief Pointers to the event memories */
CONSTP2VAR(Dem_EventMemoryEntryType, DEM_CONST, DEM_VAR_NOINIT)
  Dem_EventMem[DEM_MAXNUM_ORIGINS] =
{
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
  Dem_EventMemoryPrimary,
#if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR != 0U)
  Dem_EventMemoryMirror,
#else
  NULL_PTR,
#endif
#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U)
  Dem_EventMemoryPermanent,
#else
  NULL_PTR,
#endif
#if (DEM_MAX_NUMBER_EVENT_ENTRY_SEC != 0U)
  Dem_EventMemorySecondary
#else
  NULL_PTR
#endif
#else /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_OFF */
  Dem_NvData.EventMemoryPrimary,
#if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR != 0U)
  Dem_NvData.EventMemoryMirror,
#else
  NULL_PTR,
#endif
#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U)
  Dem_NvData.EventMemoryPermanent,
#else
  NULL_PTR,
#endif
#if (DEM_MAX_NUMBER_EVENT_ENTRY_SEC != 0U)
  Dem_NvData.EventMemorySecondary
#else
  NULL_PTR
#endif
#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */
};

/*---------------------------[Dem_EntryData array]--------------------------*/

/** \brief Pointers to the event memory entry data */
CONSTP2VAR(Dem_EntryDataType, DEM_CONST, DEM_VAR_NOINIT)
  Dem_EntryData[DEM_MAXNUM_ORIGINS] =
{
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
#if (DEM_SIZE_ENTRY_DATA_PRIMARY != 0U)
  Dem_EntryDataPrimary,
#else
  NULL_PTR,
#endif
#if (DEM_SIZE_ENTRY_DATA_MIRROR != 0U)
  Dem_EntryDataMirror,
#else
  NULL_PTR,
#endif
#if (DEM_SIZE_ENTRY_DATA_PERMANENT != 0U)
  Dem_EntryDataPermanent,
#else
  NULL_PTR,
#endif
#if (DEM_SIZE_ENTRY_DATA_SECONDARY != 0U)
  Dem_EntryDataSecondary
#else
  NULL_PTR
#endif
#else /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_OFF */
#if (DEM_SIZE_ENTRY_DATA_PRIMARY != 0U)
  Dem_NvData.EntryDataPrimary,
#else
  NULL_PTR,
#endif
#if (DEM_SIZE_ENTRY_DATA_MIRROR != 0U)
  Dem_NvData.EntryDataMirror,
#else
  NULL_PTR,
#endif
#if (DEM_SIZE_ENTRY_DATA_PERMANENT != 0U)
  Dem_NvData.EntryDataPermanent,
#else
  NULL_PTR,
#endif
#if (DEM_SIZE_ENTRY_DATA_SECONDARY != 0U)
  Dem_NvData.EntryDataSecondary
#else
  NULL_PTR
#endif
#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */
};

/*--------------------------[Dem_EntryDataFreePos array]--------------------*/

/** \brief Pointers to the event memory entry free position data */
CONSTP2VAR(Dem_SizeEntryDataType, DEM_CONST, DEM_VAR_NOINIT)
  Dem_EntryDataFreePos[DEM_MAXNUM_ORIGINS] =
{
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
#if (DEM_SIZE_ENTRY_DATA_PRIMARY != 0U)
  &Dem_EntryDataFreePosPrimary,
#else
  NULL_PTR,
#endif
#if (DEM_SIZE_ENTRY_DATA_MIRROR != 0U)
  &Dem_EntryDataFreePosMirror,
#else
  NULL_PTR,
#endif
#if (DEM_SIZE_ENTRY_DATA_PERMANENT != 0U)
  &Dem_EntryDataFreePosPermanent,
#else
  NULL_PTR,
#endif
#if (DEM_SIZE_ENTRY_DATA_SECONDARY != 0U)
  &Dem_EntryDataFreePosSecondary
#else
  NULL_PTR
#endif
#else /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_OFF */
#if (DEM_SIZE_ENTRY_DATA_PRIMARY != 0U)
  &Dem_NvData.EntryDataFreePosPrimary,
#else
  NULL_PTR,
#endif
#if (DEM_SIZE_ENTRY_DATA_MIRROR != 0U)
  &Dem_NvData.EntryDataFreePosMirror,
#else
  NULL_PTR,
#endif
#if (DEM_SIZE_ENTRY_DATA_PERMANENT != 0U)
  &Dem_NvData.EntryDataFreePosPermanent,
#else
  NULL_PTR,
#endif
#if (DEM_SIZE_ENTRY_DATA_SECONDARY != 0U)
  &Dem_NvData.EntryDataFreePosSecondary
#else
  NULL_PTR
#endif
#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */
};

/*-----------------------[Dem_NvGateEntryData array]------------------------*/

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
Dem_NvGateEntryDataPtrVoid Dem_NvGateEntryData[DEM_MAXNUM_ORIGINS] =
{
  (Dem_NvGateEntryDataPtrVoid) &Dem_NvGateEntryPrimaryData,
#if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR != 0U)
  (Dem_NvGateEntryDataPtrVoid) &Dem_NvGateEntryMirrorData,
#else
  (Dem_NvGateEntryDataPtrVoid) NULL_PTR,
#endif
#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U)
  (Dem_NvGateEntryDataPtrVoid) &Dem_NvGateEntryPermanentData,
#else
  (Dem_NvGateEntryDataPtrVoid) NULL_PTR,
#endif
#if (DEM_MAX_NUMBER_EVENT_ENTRY_SEC != 0U)
  (Dem_NvGateEntryDataPtrVoid) &Dem_NvGateEntrySecondaryData
#else
  (Dem_NvGateEntryDataPtrVoid) NULL_PTR
#endif
};

/*-----------------------[Dem_GateEntryData array]--------------------------*/

Dem_GateEntryDataPtrVoid Dem_GateEntryData[DEM_MAXNUM_ORIGINS] =
{
  (Dem_GateEntryDataPtrVoid)
    &Dem_NvGateEntryPrimaryData.EntryPrimary.EntryData,
#if (DEM_SIZE_ENTRY_DATA_MIRROR != 0U)
  (Dem_GateEntryDataPtrVoid)
    &Dem_NvGateEntryMirrorData.EntryMirror.EntryData,
#else
  (Dem_GateEntryDataPtrVoid) NULL_PTR,
#endif
#if (DEM_SIZE_ENTRY_DATA_PERMANENT != 0U)
  (Dem_GateEntryDataPtrVoid)
    &Dem_NvGateEntryPermanentData.EntryPermanent.EntryData,
#else
  (Dem_GateEntryDataPtrVoid) NULL_PTR,
#endif
#if (DEM_SIZE_ENTRY_DATA_SECONDARY != 0U)
  (Dem_GateEntryDataPtrVoid)
    &Dem_NvGateEntrySecondaryData.EntrySecondary.EntryData
#else
  (Dem_GateEntryDataPtrVoid) NULL_PTR
#endif
};

/*-----------------------[Dem_NvDataBlockId array]--------------------------*/

/** \brief Array of NvM block Id's on event memories */
CONST(NvM_BlockIdType, DEM_CONST) Dem_NvDataBlockId[DEM_MAXNUM_ORIGINS] =
{
  DEM_NVM_BLOCK_ID_PRIMARY,
  DEM_NVM_BLOCK_ID_MIRROR,
  DEM_NVM_BLOCK_ID_PERMANENT,
  DEM_NVM_BLOCK_ID_SECONDARY
};

#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */

/*-----------------------[Dem_SizeEventMem array]---------------------------*/

/** \brief Sizes of the event memories */
CONST(Dem_SizeEvMemEntryType, DEM_CONST)
  Dem_SizeEventMem[DEM_MAXNUM_ORIGINS] =
{
  DEM_MAX_NUMBER_EVENT_ENTRY_PRI,
  DEM_MAX_NUMBER_EVENT_ENTRY_MIR,
  DEM_MAX_NUMBER_EVENT_ENTRY_PER,
  DEM_MAX_NUMBER_EVENT_ENTRY_SEC
};

/*-----------------------[Dem_SizeEntryData array]--------------------------*/

/** \brief Sizes of the event memory entry data */
CONST(Dem_SizeEntryDataType, DEM_CONST)
  Dem_SizeEntryData[DEM_MAXNUM_ORIGINS] =
{
  DEM_SIZE_ENTRY_DATA_PRIMARY,
  DEM_SIZE_ENTRY_DATA_MIRROR,
  DEM_SIZE_ENTRY_DATA_PERMANENT,
  DEM_SIZE_ENTRY_DATA_SECONDARY
};

/*==================[internal constants]====================================*/

/** \brief Pointer to the prestored freeze frame data area */
CONSTP2VAR(Dem_EntryDataType, DEM_CONST, DEM_VAR_NOINIT) Dem_PFFEntryData =
#if (DEM_SIZE_PFF_ENTRY_DATA != 0U)
  Dem_PFFEntryDataArea;
#else
  NULL_PTR;
#endif

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[external function definitions]=========================*/

#define DEM_START_SEC_CODE
#include <MemMap.h>

/*------------------[Dem_GetVersionInfo]------------------------------------*/

#if (DEM_VERSION_INFO_API == STD_ON)
FUNC(void, DEM_CODE) Dem_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, DEM_APPL_DATA) versioninfo)
{
  DBG_DEM_GETVERSIONINFO_ENTRY(versioninfo);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (NULL_PTR == versioninfo)
  {
    DEM_REPORT_ERROR(DEM_SID_GetVersionInfo, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    versioninfo->vendorID         = DEM_VENDOR_ID;
    versioninfo->moduleID         = DEM_MODULE_ID;
    versioninfo->sw_major_version = DEM_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = DEM_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = DEM_SW_PATCH_VERSION;
  }

  DBG_DEM_GETVERSIONINFO_EXIT(versioninfo);
}
#endif /* DEM_VERSION_INFO_API == STD_ON */

/*------------------[Dem_PreInit]-------------------------------------------*/

FUNC(void, DEM_CODE) Dem_PreInit(
  P2CONST(Dem_ConfigType, AUTOMATIC, DEM_APPL_CONST) ConfigPtr)
{
  DBG_DEM_PREINIT_ENTRY(ConfigPtr);

  TS_PARAM_UNUSED(ConfigPtr);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_UNINITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_PreInit, DEM_E_UNINIT);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    Dem_ErrorQueueIdxType queueIdx;
    Dem_EvIdLeastType EvId;

    /* initialize (relative) error-queue pointers */
    Dem_ErrorQueueReadIdx =  0U;
    Dem_ErrorQueueWriteIdx = 0U;

    /* initialize error-queue event id's */
    for (queueIdx = 0U; queueIdx < DEM_BSW_ERROR_BUFFER_SIZE; ++queueIdx)
    {
      Dem_ErrorQueue[queueIdx] = (Dem_ErrorQueueEntryType)DEM_EVENT_ID_INVALID;
    }

    /* reset debouncing counters for event (Dem438) */
    for (EvId = 1U; EvId <= DEM_MAX_EVENTID; ++EvId)
    {
      Dem_DebounceFctPtrTable[Dem_GbiDebounceAlgo((Dem_EventIdType)EvId)].
        ResetFct((Dem_EventIdType)EvId);
    }

    /* !LINKSTO dsn.Dem.InitializationModes,1 */
    /* after pre-initializing, mark internal flag */
    Dem_InitializationState = DEM_PREINITIALIZED;
  }

  DBG_DEM_PREINIT_EXIT(ConfigPtr);
}

/*------------------[Dem_Init]----------------------------------------------*/

FUNC(void, DEM_CODE) Dem_Init(void)
{
  DBG_DEM_INIT_ENTRY();

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if ( (Dem_InitializationState != DEM_PREINITIALIZED) &&
       (Dem_InitializationState != DEM_POSTINITIALIZED)
     )
  {
    DEM_REPORT_ERROR(DEM_SID_Init, DEM_E_UNINIT);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* following initializations are only done, if the Dem is full initialized
     * first time */
    if (Dem_InitializationState == DEM_PREINITIALIZED)
    {
#if (DEM_OPCYC_NVSTORAGE == STD_OFF)
      Dem_OperationCycleIdType OpCycleId;
#endif
#if ( (DEM_USE_PERMANENT_STORAGE == STD_ON) && \
      (DEM_OPCYC_NVSTORAGE == STD_ON) && (DEM_NUM_DEBOUNCE_COUNTER_PERM > 0U) )
      Dem_EvIdLeastType NvDebIdx = 0U;
#endif
#if ( (DEM_MAX_NUMBER_PRESTORED_FF > 0U) || \
      (DEM_NUM_EVENT_INDICATOR_USED > 0U) )
      Dem_EventIdType ByteIdx;
#endif
#if ( (DEM_USE_PERMANENT_STORAGE == STD_ON) && \
      ( (DEM_STATUS_BIT_STORAGE_TF == STD_OFF) || \
        (DEM_NUM_DEBOUNCE_COUNTER_PERM > 0U) ) )
      Dem_EventIdType EvId;
#endif
#if (DEM_EVENTFAILURECOUNTER_BUFFER_SIZE > 0U)
      uint8_least FailCycCtrIdx;
#endif
#if (DEM_USE_IMMEDIATE_NV_STORAGE)
      uint8 OriginIdx;
#endif

#if (DEM_OPCYC_NVSTORAGE == STD_OFF)
      /* mark all operation cycles as closed */
      for (OpCycleId = 0U; OpCycleId < DEM_NUM_OPCYCLES; ++OpCycleId)
      {
        DEM_OPCYCLESTATE[OpCycleId] = DEM_CYCLE_STATE_END;
      }
#endif

#if (DEM_MAX_NUMBER_PRESTORED_FF > 0U)
      /* mark all prestored freeze frames as deleted */
      for (ByteIdx = 0U;
           ByteIdx < ((DEM_MAX_NUMBER_PRESTORED_FF + 7U) / 8U);
           ++ByteIdx)
      {
        /* set eight-bit-group at once */
        Dem_PFFEntryValid[ByteIdx] = 0U;
      }
#endif
#if (DEM_NUM_EVENT_INDICATOR_USED > 0U)
      /* mark all WIR On-Criteria status as unfulfilled */
      for (ByteIdx = 0U;
           ByteIdx < ((DEM_NUM_EVENT_INDICATOR_USED + 7U) / 8U);
           ++ByteIdx)
      {
        /* set eight-bit-group at once */
        Dem_WIROnCriteriaFulfilledFlags[ByteIdx] = 0U;
      }
#endif
#if (DEM_NUM_BSWEVENT_INDICATOR_USED > 0U)
      /* clear all BSW event WIR-status flag */
      for (ByteIdx = 0U;
           ByteIdx < ((DEM_NUM_BSWEVENT_INDICATOR_USED + 7U) / 8U);
           ++ByteIdx)
      {
        /* set eight-bit-group at once */
        Dem_BSWEventWIRStatusFlags[ByteIdx] = 0U;
      }
#endif
#if (DEM_USE_PERMANENT_STORAGE == STD_ON)
      /* recovery of Dem_NvData from persistent memory must be done within
       * NvM_ReadAll() */

      /* !LINKSTO Dem339_Implicit1,1 */
      if (Dem_NvMGetNvRAMDataStatus() == E_NOT_OK)
      {
#endif
        /* initialize RAM mirror of non-volatile data to default values */
        Dem_ResetNvData();
#if (DEM_USE_PERMANENT_STORAGE == STD_ON)
      }
      else
      {
#if (DEM_STATUS_BIT_STORAGE_TF == STD_OFF)
        /* As Nv storage of TF bit is disabled, it is cleared during init
         * so that its value stored in Nv memory is not used and thus the
         * volatile storage behavior is ensured */
        /* init loop for events */
        for (EvId = 0U; EvId <= DEM_MAX_EVENTID; ++EvId)
        {
          /* clear DTC status bit "test failed" */
          DEM_CLR_EV_ST_MASK(EvId, DEM_DTCSTATUSBIT_TF);
        }
#endif
      }
#if (DEM_NUM_DEBOUNCE_COUNTER_PERM > 0U)
      /* restore FDC's of events with debounce counter value stored non-volatile */
      for (EvId = 0U; EvId <= DEM_MAX_EVENTID; ++EvId)
      {
        if (Dem_GbiDebounceAlgo(EvId) == DEM_DEBOUNCE_COUNTERBASED)
        {
          const Dem_EventIdType DebounceIdx = Dem_GbiDebounceIdx(EvId);
          if (Dem_DebounceCounterCfg[DebounceIdx].PermCtrStorage == TRUE)
          {
            if (DEM_OPCYCLESTATE[Dem_GbiOpCycleIdx(EvId)] == DEM_CYCLE_STATE_START)
            {
              Dem_DebounceCounterStatus[DebounceIdx] =
                Dem_NvData.Dem_DebounceCounterStatus[NvDebIdx];
            }
            NvDebIdx++;
          }
          /* else: for events with PermCtrStorage FALSE: no need to reset
           * debounce counters as its already performed in Dem_PreInit() */
        }
      }
#endif

#endif /* DEM_USE_PERMANENT_STORAGE == STD_ON */

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
      /* !LINKSTO Dem551_Implicit1,1, dsn.Dem.ImmediateStorage,2 */
      Dem_RestoreImmediateData();

      for (OriginIdx = 0U; OriginIdx < DEM_MAXNUM_ORIGINS; ++OriginIdx)
      {
        /* clear async NvM gate write status */
        Dem_NvMStatus[OriginIdx].Status = DEM_NVM_IDLE;
      }
#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */

#if (DEM_CLEAR_DTC_BEHAVIOR != DEM_CLRRESP_VOLATILE)
      /* initialize asynchronous ClearDTC status */
      Dem_ClearDtcAsyncStatus.EventStatusWrite = DEM_NVM_IDLE;
#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_TRIGGER)
      Dem_ClearDtcAsyncStatus.RetriggerEventStatusWrite = FALSE;
#else
      Dem_ClearDtcAsyncStatus.EventMemWrite = DEM_NVM_IDLE;
      Dem_ClearDtcAsyncStatus.RunState = DEM_CLEARDTC_STATE_IDLE;
#endif
#endif /* DEM_CLEAR_DTC_BEHAVIOR != DEM_CLRRESP_VOLATILE */

#if (DEM_EVENTFAILURECOUNTER_BUFFER_SIZE > 0U)
      /* initialize the event failure counter buffer */
      for (FailCycCtrIdx = 0U;
           FailCycCtrIdx < DEM_EVENTFAILURECOUNTER_BUFFER_SIZE;
           ++FailCycCtrIdx)
      {
        Dem_EventFailureCycleCounterBuffer[FailCycCtrIdx].EventId =
          DEM_EVENT_ID_INVALID;
      }
#endif

#if (DEM_USE_EVENT_DISPLACEMENT == STD_ON)
      /* initialize the array which stores the largest value of occurrence order
       * in a memory */
      Dem_InitMaxOccOrder();
#endif

      /* Dem_EnableDTCSetting(<all DTCs>) */
      DEM_ATOMIC_ASSIGN_32(Dem_DTCSettingAllowed,
                           DEM_BITFIELD_VALUE_ALL_GROUPS);

      /* initialize freeze frame record-filter */
      Dem_RecordFilterEntryIdx = 0U;
      Dem_RecordFilterRecNumIdx = 0U;

      /* initialize the event memory read semaphore */
      Dem_EvMemReadAccessSemaphore = 0U;
    }

    /* following actions are also performed after DEM_POSTINITIALIZED: */

    /* Dem_EnableDTCRecordUpdate() */
    Dem_EvIdOfRecordUpdateDisabledDTC = DEM_EVENT_ID_INVALID;

    /* !LINKSTO dsn.Dem.InitializationModes,1 */
    /* after full initializing, mark internal flag */
    Dem_InitializationState = DEM_INITIALIZED;
  }

  DBG_DEM_INIT_EXIT();
}

/*------------------[Dem_Shutdown]------------------------------------------*/

FUNC(void, DEM_CODE) Dem_Shutdown(void)
{
  DBG_DEM_SHUTDOWN_ENTRY();

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_Shutdown, DEM_E_UNINIT);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
#if (DEM_USE_AGING == STD_ON)
    Dem_EventIdType LockedEvId;
#endif
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
    uint8 originIdx;
    Dem_SizeEvMemEntryType entryIdx;
#endif
#if ( (DEM_USE_PERMANENT_STORAGE == STD_ON) && \
      (DEM_NUM_DEBOUNCE_COUNTER_PERM > 0U) )
    Dem_EvIdLeastType DebounceIdx;
    Dem_EvIdLeastType NvDebIdx = 0U;
#endif

    /* reset the event memory read semaphore to enable main functionality
     * (if disabled) */
    Dem_EvMemReadAccessSemaphore = 0U;
    /* finalize all pending operations */
    Dem_MainFunction();

    /* before shutdown, mark internal flag */
    Dem_InitializationState = DEM_POSTINITIALIZED;

#if (DEM_USE_AGING == STD_ON)
    LockedEvId = Dem_EvIdOfRecordUpdateDisabledDTC;

    /* clear any aged disabled event from event memory */
    /* Deviation MISRA-2 */
    if ((LockedEvId != DEM_EVENT_ID_INVALID) && DEM_AGING_ALLOWED(LockedEvId))
    {
      Dem_EventMemoryEntryPtrType EvMemEntry;

      if (Dem_SearchForEntry(LockedEvId, &EvMemEntry, NULL_PTR) == TRUE)
      {
        const Dem_EntryDataPtrType AgingCounterPtr =
          Dem_IntValEntryData(EvMemEntry);

        if (*AgingCounterPtr == 0U)
        {
          Dem_ClearAgedEventEntry(LockedEvId, EvMemEntry);

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
          /* aged event shall be cleared from NVRAM during shutdown */
          EvMemEntry->EntryStatus = DEM_ENTRY_CHANGED;
#endif
        }
      }
    }
#endif

    /* --- shutdown RAM mirror of non-volatile data --- */
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
    /* shutdown loop for all event memories */
    for (originIdx = 0U; originIdx < (uint8)DEM_MAXNUM_ORIGINS; ++originIdx)
    {
      /* event memory is used */
      if (Dem_NvDataBlockId[originIdx] != DEM_NVM_BLOCK_ID_INVALID)
      {
        /* trigger the memory-stack main functions synchronously to complete
         * immediate storage processing */
        DEM_STORAGEWAITNVMREADY(Dem_NvDataBlockId[originIdx]);

        /* for every event entry */
        for (entryIdx = 0U; entryIdx < Dem_SizeEventMem[originIdx]; ++entryIdx)
        {
          /* check for events which had to be stored immediately but write to
           * NvM was not successful, events which have not to be stored
           * immediately with changed entry data, immediate storage events not
           * stored immediately due to maximum number of occurrences and event
           * memory entries whose restoration from NvM during initialization
           * was not successful */
          if (Dem_EventMem[originIdx][entryIdx].EntryStatus
               != DEM_ENTRY_UNCHANGED)
          {
            const NvM_BlockIdType NvDataBlockId = Dem_NvDataBlockId[originIdx];

            /* store this event memory entry persistently */
            Dem_StoreImmediately(originIdx, entryIdx);

            /* select corresponding NVRAM block dataset */
            (void)NvM_SetDataIndex(NvDataBlockId, entryIdx);

            /* queue write request of gate-entry to NvM - NvM_DstPtr is unused,
             * as permanent RAM block (gate-entry) is configured */
            (void)NvM_WriteBlock(NvDataBlockId, NULL_PTR);

            /* trigger the memory-stack main functions synchronously */
            DEM_STORAGEWAITNVMREADY(Dem_NvDataBlockId[originIdx]);
          }
        }
      }
    }
#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */

#if (DEM_USE_PERMANENT_STORAGE == STD_ON)

#if (DEM_NUM_DEBOUNCE_COUNTER_PERM > 0U)
      /* !LINKSTO Dem577,1 */
      /* store FDC's of events with non-volatile storage of counter values enabled */
      for (DebounceIdx = 0U;
           DebounceIdx < DEM_NUM_DEBOUNCE_COUNTER;
           ++DebounceIdx)
      {
        if (Dem_DebounceCounterCfg[DebounceIdx].PermCtrStorage == TRUE)
        {
          Dem_NvData.Dem_DebounceCounterStatus[NvDebIdx] =
            Dem_DebounceCounterStatus[DebounceIdx];
          NvDebIdx++;
        }
      }
#endif
    /* validate Dem_NvData, to be stored persistently during NvM_WriteAll() */
    (void)NvM_SetRamBlockStatus(DEM_NVM_BLOCK_ID_DEFAULT, TRUE);

    /* persistent storage of Dem_NvData must be done within NvM_WriteAll() */
#endif
  }

  DBG_DEM_SHUTDOWN_EXIT();
}

/*------------------[Dem_ReportErrorStatus]---------------------------------*/

FUNC(void, DEM_CODE) Dem_ReportErrorStatus(
  Dem_EventIdType     EventId,
  Dem_EventStatusType EventStatus)
{
  DBG_DEM_REPORTERRORSTATUS_ENTRY(EventId, EventStatus);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* this function can also be called within pre-initialized state */
  if (Dem_InitializationState == DEM_UNINITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_ReportErrorStatus, DEM_E_UNINIT);
  }
  else if (EventId == (Dem_EventIdType)DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_ReportErrorStatus, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_ReportErrorStatus, DEM_E_PARAM_CONFIG);
  }
  else if ( ( (EventStatus != DEM_EVENT_STATUS_PASSED) &&
              (EventStatus != DEM_EVENT_STATUS_FAILED) ) &&
            ( (EventStatus != DEM_EVENT_STATUS_PREPASSED) &&
              (EventStatus != DEM_EVENT_STATUS_PREFAILED) )
          )
  {
    DEM_REPORT_ERROR(DEM_SID_ReportErrorStatus, DEM_E_PARAM_DATA);
  }
  else if (Dem_GbiEventKind(EventId) == DEM_EVENT_KIND_SWC)
  {
    DEM_REPORT_ERROR(DEM_SID_ReportErrorStatus, DEM_E_PARAM_DATA);
  }
#if (DEM_NUM_DEBOUNCE_COUNTER_PERM > 0U)
  /* Deviation MISRA-2 <+4> */
  else if ( (Dem_InitializationState == DEM_PREINITIALIZED) &&
            (Dem_GbiDebounceAlgo(EventId) == DEM_DEBOUNCE_COUNTERBASED) &&
            (Dem_DebounceCounterCfg[Dem_GbiDebounceIdx(EventId)].
               PermCtrStorage == TRUE) )
  {
    DEM_REPORT_ERROR(DEM_SID_ReportErrorStatus, DEM_E_WRONG_CONDITION);
  }
#endif
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    boolean EntryPresent = FALSE;
    Dem_EventStatusType PreviousEntryStatus = DEM_EVENT_STATUS_FAILED;
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  boolean queueWriteSuccess = FALSE;
#endif /* DEM_DEV_ERROR_DETECT */

    /* !LINKSTO Dem.BufferMechanism.Startup,2 */
    if (Dem_InitializationState == DEM_PREINITIALIZED)
    {
      Std_ReturnType debounceResult;

      if (Dem_DebounceEvent(EventId, &EventStatus, &debounceResult) == FALSE)
      {
#if (DEM_DEV_ERROR_DETECT == STD_ON)
        if (debounceResult == DEM_E_DET_REPORT)
        {
          /* debouncing did not qualify the event:
           * no qualification-handling possible */
          DEM_REPORT_ERROR(DEM_SID_ReportErrorStatus, DEM_E_PARAM_DATA);
        }
#endif /* DEM_DEV_ERROR_DETECT */
      }

      if ( (EventStatus == DEM_EVENT_STATUS_FAILED) ||
           (EventStatus == DEM_EVENT_STATUS_PASSED) )
      {
        /*
         * ENTER critical section to protect the error-queue and queue-pointers
         *       call-context: any
         */
        SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

        /* check if event is already present in error-queue */
        EntryPresent = Dem_CheckErrorQueueEntry(EventId, &PreviousEntryStatus);

        /* make entry in error-queue */
        if ( (EntryPresent == FALSE) || (EventStatus != PreviousEntryStatus) )
        {
#if (DEM_DEV_ERROR_DETECT == STD_ON)
          queueWriteSuccess = Dem_WriteErrorQueueEntry(EventId, EventStatus);
#else
          /* return value is used for error detection in Det only */
          (void) Dem_WriteErrorQueueEntry(EventId, EventStatus);
#endif /* DEM_DEV_ERROR_DETECT */
        }

        /*
         * LEAVE critical section
         */
        SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

#if (DEM_DEV_ERROR_DETECT == STD_ON)
        if (queueWriteSuccess == FALSE)
        {
          DEM_REPORT_ERROR(DEM_SID_ReportErrorStatus, DEM_E_PARAM_CONFIG);
        }
#endif
      }
    }
    else /* Dem_InitializationState == DEM_INITIALIZED/DEM_POSTINITIALIZED
          * or development error */
    {
      /* process "normal" event handling */

#if (DEM_DEV_ERROR_DETECT == STD_ON)
      if (Dem_InternalSetEventStatus(EventId, EventStatus) == DEM_E_DET_REPORT)
      {
        DEM_REPORT_ERROR(DEM_SID_ReportErrorStatus, DEM_E_PARAM_CONFIG);
      }
#else
      /* return value is used for error detection in Det only */
      (void) Dem_InternalSetEventStatus(EventId, EventStatus);
#endif /* DEM_DEV_ERROR_DETECT */
    }
  }

  DBG_DEM_REPORTERRORSTATUS_EXIT(EventId, EventStatus);
}

/* APIs are only allowed for SW-C events as per SWS */
#if ( (DEM_INCLUDE_RTE == STD_OFF) || (DEM_NUM_SWC_EVENTS > 0) )
/*------------------[Dem_SetEventStatus]------------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_SetEventStatus(
  Dem_EventIdType     EventId,
  Dem_EventStatusType EventStatus)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_SETEVENTSTATUS_ENTRY(EventId, EventStatus);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_SetEventStatus, DEM_E_UNINIT);
  }
  else if (EventId == (Dem_EventIdType)DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_SetEventStatus, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_SetEventStatus, DEM_E_PARAM_CONFIG);
  }
  else if ( ( (EventStatus != DEM_EVENT_STATUS_PASSED) &&
              (EventStatus != DEM_EVENT_STATUS_FAILED) ) &&
            ( (EventStatus != DEM_EVENT_STATUS_PREPASSED) &&
              (EventStatus != DEM_EVENT_STATUS_PREFAILED) )
          )
  {
    DEM_REPORT_ERROR(DEM_SID_SetEventStatus, DEM_E_PARAM_DATA);
  }
  else if (Dem_GbiEventKind(EventId) == DEM_EVENT_KIND_BSW)
  {
    DEM_REPORT_ERROR(DEM_SID_SetEventStatus, DEM_E_PARAM_DATA);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    result = Dem_InternalSetEventStatus(EventId, EventStatus);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
    if (result == DEM_E_DET_REPORT )
    {
      DEM_REPORT_ERROR(DEM_SID_SetEventStatus, DEM_E_PARAM_CONFIG);
      result = E_NOT_OK;
    }
#endif /* DEM_DEV_ERROR_DETECT */
  }

  DBG_DEM_SETEVENTSTATUS_EXIT(result, EventId, EventStatus);
  return result;
}

/*------------------[Dem_ResetEventStatus]----------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_ResetEventStatus(Dem_EventIdType EventId)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_RESETEVENTSTATUS_ENTRY(EventId);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_ResetEventStatus, DEM_E_UNINIT);
  }
  else if (EventId == (Dem_EventIdType)DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_ResetEventStatus, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_ResetEventStatus, DEM_E_PARAM_CONFIG);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* !LINKSTO Dem638,1 */
    /* reset of failed qualification-result is allowed only if event
     * is not already tested this operation cycle */
    if (DEM_IS_EV_ST_BIT_TNCTOC_SET(EventId))
    {
#if ( (DEM_USE_CB_TRIG_ON_EVST == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) )
      Dem_DTCStatusMaskType OldDTCStatusMask = 0U;
      Dem_DTCStatusMaskType NewDTCStatusMask = 0U;
#endif

      /*
       * ENTER critical section to protect the status bits AND debounce status
       *       call-context: Rte (Task)
       */
      SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

      /* clear bit only if it is set */
      if (DEM_IS_EV_ST_BIT_TF_SET(EventId))
      {
#if ( (DEM_USE_CB_TRIG_ON_EVST == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) )
        OldDTCStatusMask = DEM_DTC_STATUS_MASKS[EventId];
#endif

        /* TEST FAILED -> 0 */
        DEM_CLR_EV_ST_MASK(EventId, DEM_DTCSTATUSBIT_TF);
        /* other bits are unchanged */

#if ( (DEM_USE_CB_TRIG_ON_EVST == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) )
        NewDTCStatusMask = DEM_DTC_STATUS_MASKS[EventId];
#endif
      }
      /* else: testFailed bit is already set to 0, do nothing */

      /* reset debouncing counters for event (Dem187) */
      Dem_DebounceFctPtrTable[Dem_GbiDebounceAlgo(EventId)].ResetFct(EventId);

      /*
       * LEAVE critical section
       */
      SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

#if ( (DEM_USE_CB_TRIG_ON_EVST == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) )
      if (OldDTCStatusMask != NewDTCStatusMask)
      {
        /* notify application that event status has changed */
        Dem_CbTriggerOnEventStatus(EventId,
                                   OldDTCStatusMask,
                                   NewDTCStatusMask);
      }
#endif

      result = E_OK;
    }
  }

  DBG_DEM_RESETEVENTSTATUS_EXIT(result, EventId);
  return result;
}

/*------------------[Dem_PrestoreFreezeFrame]-------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_PrestoreFreezeFrame(
  Dem_EventIdType EventId)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_PRESTOREFREEZEFRAME_ENTRY(EventId);

#if ((DEM_DEV_ERROR_DETECT != STD_ON) && (DEM_MAX_NUMBER_PRESTORED_FF == 0U))
  TS_PARAM_UNUSED(EventId);
#endif

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_PrestoreFreezeFrame, DEM_E_UNINIT);
  }
  else if (EventId == (Dem_EventIdType)DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_PrestoreFreezeFrame, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_PrestoreFreezeFrame, DEM_E_PARAM_CONFIG);
  }
  else if (Dem_GbiEnablePrestorage(EventId) == FALSE)
  {
    DEM_REPORT_ERROR(DEM_SID_PrestoreFreezeFrame, DEM_E_PARAM_CONFIG);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
#if (DEM_MAX_NUMBER_PRESTORED_FF > 0U)
    /* there are maximal as much PFFs as events */
    Dem_EventIdType PFFIndex = Dem_GetPFFIndex(EventId);
    Dem_EntryDataPtrType PFFEntryData = Dem_GetPFFEntryDataPtr(EventId);

    /* before filling, mark prestored freeze frame as invalid, to avoid
     * corrupt data reads */
    DEM_ATOMIC_CLR_BIT_IN_ARRAY_8(Dem_PFFEntryValid, PFFIndex);

    /* store new FF to the reserved PFF-entry-space of the given event Id */
    Dem_StoreFF(
#if (DEM_DEV_ERROR_DETECT == STD_ON)
      DEM_SID_PrestoreFreezeFrame,
#endif /* DEM_DEV_ERROR_DETECT */
      PFFEntryData,
      &Dem_FFClass[Dem_GbiFFClassIdx(EventId)]);

    /* mark prestored freeze frame as filled */
    DEM_ATOMIC_SET_BIT_IN_ARRAY_8(Dem_PFFEntryValid, PFFIndex);

    result = E_OK;
#endif /* (DEM_MAX_NUMBER_PRESTORED_FF > 0U) */
  }

  DBG_DEM_PRESTOREFREEZEFRAME_EXIT(result, EventId);
  return result;
}

/*------------------[Dem_ClearPrestoredFreezeFrame]-------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_ClearPrestoredFreezeFrame(
  Dem_EventIdType EventId)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_CLEARPRESTOREDFREEZEFRAME_ENTRY(EventId);

#if ((DEM_DEV_ERROR_DETECT != STD_ON) && (DEM_MAX_NUMBER_PRESTORED_FF == 0U))
  TS_PARAM_UNUSED(EventId);
#endif

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_ClearPrestoredFreezeFrame, DEM_E_UNINIT);
  }
  else if (EventId == (Dem_EventIdType)DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_ClearPrestoredFreezeFrame, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_ClearPrestoredFreezeFrame, DEM_E_PARAM_CONFIG);
  }
  else if (Dem_GbiEnablePrestorage(EventId) == FALSE)
  {
    DEM_REPORT_ERROR(DEM_SID_ClearPrestoredFreezeFrame, DEM_E_PARAM_CONFIG);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
#if (DEM_MAX_NUMBER_PRESTORED_FF > 0U)
    Dem_EventIdType PFFIndex = Dem_GetPFFIndex(EventId);

    /* mark prestored freeze frame as empty */
    DEM_ATOMIC_CLR_BIT_IN_ARRAY_8(Dem_PFFEntryValid, PFFIndex);

    result = E_OK;
#endif
  }

  DBG_DEM_CLEARPRESTOREDFREEZEFRAME_EXIT(result, EventId);
  return result;
}
#endif /* ( (DEM_INCLUDE_RTE == STD_OFF) || (DEM_NUM_SWC_EVENTS > 0) ) */

/*------------------[Dem_SetOperationCycleState]----------------------------*/

#if (DEM_OPERATION_CYCLE_PROCESSING == DEM_PROCESS_OPCYC_STATE)
FUNC(Std_ReturnType, DEM_CODE) Dem_SetOperationCycleState(
  Dem_OperationCycleIdType    OperationCycleId,
  Dem_OperationCycleStateType CycleState)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_SETOPERATIONCYCLESTATE_ENTRY(OperationCycleId, CycleState);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_SetOperationCycleState, DEM_E_UNINIT);
  }
  else if (OperationCycleId >= DEM_NUM_OPCYCLES)
  {
    DEM_REPORT_ERROR(DEM_SID_SetOperationCycleState, DEM_E_PARAM_CONFIG);
  }
  else if ( (CycleState != DEM_CYCLE_STATE_START) &&
            (CycleState != DEM_CYCLE_STATE_END) )
  {
    DEM_REPORT_ERROR(DEM_SID_SetOperationCycleState, DEM_E_PARAM_DATA);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    CONSTP2VAR(Dem_OperationCycleStateType, AUTOMATIC, DEM_VAR_NOINIT)
      StoredCycleState = &DEM_OPCYCLESTATE[OperationCycleId];

    Dem_EvIdLeastType EvId;

#if ( (DEM_USE_CB_TRIG_ON_EVST == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) )
    Dem_DTCStatusMaskType OldDTCStatusMask;
    Dem_DTCStatusMaskType NewDTCStatusMask;
#endif

    /* end previous cycle on transisition: START->END or START->START */
    if (((CycleState == DEM_CYCLE_STATE_END) && (*StoredCycleState != CycleState)) ||
        ((CycleState == DEM_CYCLE_STATE_START) && (*StoredCycleState == CycleState)))
    {
      /* check all events */
      for (EvId = 1U; EvId <= DEM_MAX_EVENTID; ++EvId)
      {
        /* only for events of this operation cycle */
        if (Dem_GbiOpCycleIdx((Dem_EventIdType)EvId) == OperationCycleId)
        {
          /*
           * ENTER critical section to protect the event status bits
           *       call-context: Rte (Task)
           */
          SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

#if ( (DEM_USE_CB_TRIG_ON_EVST == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) )
          OldDTCStatusMask = DEM_DTC_STATUS_MASKS[EvId];
#endif

          /* test is complete, passed this operation cycle */
          if ( (!DEM_IS_EV_ST_BIT_TNCTOC_SET((Dem_EventIdType)EvId)) &&
               (!DEM_IS_EV_ST_BIT_TFTOC_SET((Dem_EventIdType)EvId))
             )
          {
            /* clear "pending DTC" status bit */
            DEM_CLR_EV_ST_MASK(EvId, DEM_DTCSTATUSBIT_PDTC);
          }

          /*
           * LEAVE critical section
           */
          SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

#if (DEM_USE_AGING == STD_ON)
#if (DEM_NUM_AGINGCYCLES > 0U)
          if ( (DEM_AGING_ALLOWED((Dem_EventIdType)EvId)) &&
               /* Deviation MISRA-2 <+2> */
               ( (Dem_GbiAgingCycleIdx((Dem_EventIdType)EvId)) ==
                    (DEM_NUM_OPCYCLES + DEM_NUM_AGINGCYCLES) ) )
#else
          if (DEM_AGING_ALLOWED((Dem_EventIdType)EvId))
#endif
          {
            /* process aging algorithm only, if the event is entered and was
             * tested and never failed this operation cycle (Dem489).
             * TNCTOC bit is checked since aging counter needs to be incremented
             * only if the event is reported at least once in this operation
             * cycle.
             * TFTOC bit is checked since operation cycle is used for processing
             * of the aging counter.
             * (ISO 14229-1:2006 Section D.6, Figure D.11) */
            if ( (!DEM_IS_EV_ST_BIT_TNCTOC_SET((Dem_EventIdType)EvId)) &&
                 (!DEM_IS_EV_ST_BIT_TFTOC_SET((Dem_EventIdType)EvId)) )
            {
              /* process aging counter (may lead to status change) */
              Dem_UpdateAgingCounter((Dem_EventIdType)EvId);
            }
          }
          /* else: this event uses a different aging cycle, thus aging counter
                   will be processed by Dem_SetAgingCycleState()
                 OR aging is disabled */
#endif /* DEM_USE_AGING */

#if ( (DEM_USE_CB_TRIG_ON_EVST == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) )
          NewDTCStatusMask = DEM_DTC_STATUS_MASKS[EvId];

          /* notify application if event status has changed */
          if (OldDTCStatusMask != NewDTCStatusMask)
          {
            Dem_CbTriggerOnEventStatus(
              (Dem_EventIdType)EvId, OldDTCStatusMask, NewDTCStatusMask);
          }
#endif
        }

#if (DEM_NUM_FAILURECYCLES > 0U)
        /* for events with this failure cycle, reset the failure counter if
         * the event is tested and never failed this operation cycle */
        Dem_ProcessFailureCounterReset((Dem_EventIdType)EvId, OperationCycleId);
#endif
      }
    }

    /* start new cycle on transition: START->START or END->START */
    if (CycleState == DEM_CYCLE_STATE_START)
    {
#if (DEM_NUM_INDICATOR_LINKS > 0U)
      Dem_ProcessHealing(OperationCycleId);
#endif

      /* check all events */
      for (EvId = 1U; EvId <= DEM_MAX_EVENTID; ++EvId)
      {
#if (DEM_NUM_FAILURECYCLES > 0U)
        /* update failure counter for events with this failure cycle */
        Dem_UpdateFailureCounterCycleStart(
          (Dem_EventIdType)EvId, OperationCycleId);
#endif

        /* only for events of this operation cycle */
        if (Dem_GbiOpCycleIdx((Dem_EventIdType)EvId) == OperationCycleId)
        {
          /*
           * ENTER critical section to protect the event status bits
           *       call-context: Rte (Task)
           */
          SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

#if ( (DEM_USE_CB_TRIG_ON_EVST == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) )
          OldDTCStatusMask = DEM_DTC_STATUS_MASKS[EvId];
#endif

          /* set DTC status bit: "test not completed this operation cycle" */
          /* clear DTC status bit: "test failed this operation cycle" */
          DEM_CHNG_EV_ST_MASK(EvId,
                              DEM_DTCSTATUSBIT_TNCTOC,
                              DEM_DTCSTATUSBIT_TFTOC);

#if ( (DEM_USE_CB_TRIG_ON_EVST == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) )
          NewDTCStatusMask = DEM_DTC_STATUS_MASKS[EvId];
#endif

          /* reset debouncing counters for event */
          Dem_DebounceFctPtrTable[Dem_GbiDebounceAlgo((Dem_EventIdType)EvId)].
            ResetFct((Dem_EventIdType)EvId);

          /*
           * LEAVE critical section
           */
          SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

#if ( (DEM_USE_CB_TRIG_ON_EVST == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) )
          /* notify application if event status has changed */
          if (OldDTCStatusMask != NewDTCStatusMask)
          {
            Dem_CbTriggerOnEventStatus(
              (Dem_EventIdType)EvId, OldDTCStatusMask, NewDTCStatusMask);
          }
#endif

#if (DEM_USE_CB_INIT_MONITOR == STD_ON)
          /* reinit of monitor function */
          Dem_CbInitMonitorForEvent(
            (Dem_EventIdType)EvId, DEM_INIT_MONITOR_RESTART);
#endif
        }
      }
    }

    /* switch stored state to new state */
    *StoredCycleState = CycleState;

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
    Dem_TriggerNvmWriteGateEntry();
#endif

    result = E_OK;
  }

  DBG_DEM_SETOPERATIONCYCLESTATE_EXIT(result, OperationCycleId, CycleState);
  return result;
}
#endif /* DEM_OPERATION_CYCLE_PROCESSING == DEM_PROCESS_OPCYC_STATE */

/*------------------[Dem_SetOperationCycleCntValue]-------------------------*/

/* stub is currently only supported without RTE-usage */
#if (DEM_INCLUDE_RTE == STD_OFF)
FUNC(Std_ReturnType, DEM_CODE) Dem_SetOperationCycleCntValue(
  uint8 OperationCycleId,
  uint8 CounterValue)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_SETOPERATIONCYCLECNTVALUE_ENTRY(OperationCycleId, CounterValue);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_SetOperationCycleCntValue, DEM_E_UNINIT);
  }
  else if (OperationCycleId >= DEM_NUM_OPCYCLES)
  {
    DEM_REPORT_ERROR(DEM_SID_SetOperationCycleCntValue, DEM_E_PARAM_CONFIG);
  }
  else
#else
  TS_PARAM_UNUSED(OperationCycleId);
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* Function NOT fully implemented yet.
     * Implementation is scheduled for future releases. */
    TS_PARAM_UNUSED(CounterValue);

  }

  DBG_DEM_SETOPERATIONCYCLECNTVALUE_EXIT(
    result, OperationCycleId, CounterValue);
  return result;
}
#endif

/*------------------[Dem_SetAgingCycleState]--------------------------------*/

#if ((DEM_AGINGCYCLE_COUNTER_PROCESSING == DEM_PROCESS_AGINGCTR_INTERN) && \
    (DEM_NUM_AGINGCYCLES > 0U))
FUNC(Std_ReturnType, DEM_CODE) Dem_SetAgingCycleState(uint8 AgingCycleId)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_SETAGINGCYCLESTATE_ENTRY(AgingCycleId);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_SetAgingCycleState, DEM_E_UNINIT);
  }
  else if ((AgingCycleId < DEM_NUM_OPCYCLES) ||
           (AgingCycleId >= (DEM_NUM_OPCYCLES + DEM_NUM_AGINGCYCLES)))
  {
    DEM_REPORT_ERROR(DEM_SID_SetAgingCycleState, DEM_E_PARAM_CONFIG);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    Dem_EvIdLeastType EvId;

    /* check all events */
    for (EvId = 1U; EvId <= DEM_MAX_EVENTID; ++EvId)
    {
      /* only for events of this aging cycle */
      /* aging is always enabled, if corresponding aging cycle is set */
      if (Dem_GbiAgingCycleIdx((Dem_EventIdType)EvId) == AgingCycleId)
      {
#if ( (DEM_USE_CB_TRIG_ON_EVST == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) )
        const Dem_DTCStatusMaskType OldDTCStatusMask =
          DEM_DTC_STATUS_MASKS[EvId];
        Dem_DTCStatusMaskType NewDTCStatusMask;
#endif
        /* process aging algorithm only, if the event is entered and the current
         * status is passed (Dem489).
         * TF bit is checked to make aging counter incrementation independent of
         * a previously reported failure and independent of operation cycle */
        if (!DEM_IS_EV_ST_BIT_TF_SET((Dem_EventIdType)EvId))
        {
          /* process aging counter (may lead to status change) */
          Dem_UpdateAgingCounter((Dem_EventIdType)EvId);
        }

#if ( (DEM_USE_CB_TRIG_ON_EVST == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) )
        NewDTCStatusMask = DEM_DTC_STATUS_MASKS[EvId];

        /* notify application if event status has changed */
        if (OldDTCStatusMask != NewDTCStatusMask)
        {
          Dem_CbTriggerOnEventStatus(
            (Dem_EventIdType)EvId, OldDTCStatusMask, NewDTCStatusMask);
        }
#endif
      }
    }

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
    Dem_TriggerNvmWriteGateEntry();
#endif

    result = E_OK;
  }

  DBG_DEM_SETAGINGCYCLESTATE_EXIT(result, AgingCycleId);
  return result;
}
#endif

/*------------------[Dem_SetAgingCycleCounterValue]-------------------------*/

/* stub is currently only supported without RTE-usage */
#if (DEM_INCLUDE_RTE == STD_OFF)
FUNC(Std_ReturnType, DEM_CODE) Dem_SetAgingCycleCounterValue(
  uint8 CounterValue)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_SETAGINGCYCLECOUNTERVALUE_ENTRY(CounterValue);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_SetAgingCycleCounterValue, DEM_E_UNINIT);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* Function NOT fully implemented yet.
     * Implementation is scheduled for future releases. */
    TS_PARAM_UNUSED(CounterValue);
  }

  DBG_DEM_SETAGINGCYCLECOUNTERVALUE_EXIT(result, CounterValue);
  return result;
}
#endif

/*------------------[Dem_GetEventStatus]------------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventStatus(
  Dem_EventIdType EventId,
  P2VAR(Dem_EventStatusExtendedType, AUTOMATIC, DEM_APPL_DATA)
    EventStatusExtended)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_GETEVENTSTATUS_ENTRY(EventId, EventStatusExtended);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventStatus, DEM_E_UNINIT);
  }
  else if (EventId == (Dem_EventIdType)DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventStatus, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventStatus, DEM_E_PARAM_CONFIG);
  }
  else if (EventStatusExtended == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventStatus, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    *EventStatusExtended = (Dem_EventStatusExtendedType)
      (DEM_DTC_STATUS_MASKS[EventId] & DEM_DTC_STATUS_AVAILABILITY_MASK);

    result = E_OK;
  }

  DBG_DEM_GETEVENTSTATUS_EXIT(result, EventId, EventStatusExtended);
  return result;
}

/*------------------[Dem_GetEventFailed]------------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventFailed(
  Dem_EventIdType                          EventId,
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA) EventFailed)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_GETEVENTFAILED_ENTRY(EventId, EventFailed);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventFailed, DEM_E_UNINIT);
  }
  else if (EventId == (Dem_EventIdType)DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventFailed, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventFailed, DEM_E_PARAM_CONFIG);
  }
  else if (EventFailed == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventFailed, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    *EventFailed = Dem_GetEvStBitVal(
      EventId,
      (Dem_EventStatusExtendedType)DEM_DTCSTATUSBIT_TF);

    result = E_OK;
  }

  DBG_DEM_GETEVENTFAILED_EXIT(result, EventId, EventFailed);
  return result;
}

/*------------------[Dem_GetEventTested]------------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventTested(
  Dem_EventIdType                          EventId,
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA) EventTested)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_GETEVENTTESTED_ENTRY(EventId, EventTested);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventTested, DEM_E_UNINIT);
  }
  else if (EventId == (Dem_EventIdType)DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventTested, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventTested, DEM_E_PARAM_CONFIG);
  }
  else if (EventTested == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventTested, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    if ( Dem_GetEvStBitVal(
           EventId, (Dem_EventStatusExtendedType)DEM_DTCSTATUSBIT_TNCTOC )
         != FALSE
       )
    {
      *EventTested = FALSE;
    }
    else
    {
      *EventTested = TRUE;
    }

    result = E_OK;
  }

  DBG_DEM_GETEVENTTESTED_EXIT(result, EventId, EventTested);
  return result;
}

/*------------------[Dem_GetDTCOfEvent]-------------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_GetDTCOfEvent(
  Dem_EventIdType                              EventId,
  Dem_DTCFormatType                            DTCFormat,
  P2VAR(Dem_DTCType, AUTOMATIC, DEM_APPL_DATA) DTCOfEvent)
  /* DTCFormat parameter is ignored since there is no OBD support:
     Implementation is scheduled for future releases. */
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_GETDTCOFEVENT_ENTRY(EventId, DTCFormat, DTCOfEvent);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* check of Dem_InitializationState is not necessary:
   * it's allowed to get DTC of event even if Dem is uninitialized */

  if (EventId == (Dem_EventIdType)DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetDTCOfEvent, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetDTCOfEvent, DEM_E_PARAM_CONFIG);
  }
  else if ( (DTCFormat != DEM_DTC_FORMAT_OBD) &&
            (DTCFormat != DEM_DTC_FORMAT_UDS)
          )
  {
    DEM_REPORT_ERROR(DEM_SID_GetDTCOfEvent, DEM_E_PARAM_DATA);
  }
  else if (DTCOfEvent == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetDTCOfEvent, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* get the DTC mapped to event Id */
    *DTCOfEvent = Dem_GbiDTC(EventId);

    if (*DTCOfEvent == 0U)
    {
      result = DEM_E_NO_DTC_AVAILABLE;
    }
    /* check if DTCFormat is DEM_DTC_FORMAT_OBD which is not supported,
     * as current implementation only supports non OBD-relevant ECUs. */
    else if (DTCFormat == DEM_DTC_FORMAT_OBD)
    {
      result = DEM_E_NO_DTC_AVAILABLE;
    }
    else
    {
      result = E_OK;
    }
  }

  DBG_DEM_GETDTCOFEVENT_EXIT(result, EventId, DTCFormat, DTCOfEvent);
  return result;
}

/*------------------[Dem_SetEnableCondition]--------------------------------*/

/* feature related code-part concerning enable conditions */
#if (DEM_NUM_ENABLECONDITIONS > 0U)
FUNC(Std_ReturnType, DEM_CODE) Dem_SetEnableCondition(
  uint8   EnableConditionID,
  boolean ConditionFulfilled)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_SETENABLECONDITION_ENTRY(EnableConditionID, ConditionFulfilled);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_SetEnableCondition, DEM_E_UNINIT);
  }
  else if (EnableConditionID >= DEM_NUM_ENABLECONDITIONS)
  {
    DEM_REPORT_ERROR(DEM_SID_SetEnableCondition, DEM_E_PARAM_CONFIG);
  }
  else if ( (ConditionFulfilled != FALSE) &&
            (ConditionFulfilled != TRUE)
          )
  {
    DEM_REPORT_ERROR(DEM_SID_SetEnableCondition, DEM_E_PARAM_DATA);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    Dem_EnCondStatus[EnableConditionID] = ConditionFulfilled;

    result = E_OK;
  }

  DBG_DEM_SETENABLECONDITION_EXIT(
    result, EnableConditionID, ConditionFulfilled);
  return result;
}
#endif /* DEM_NUM_ENABLECONDITIONS > 0U */

/*------------------[Dem_SetStorageCondition]-------------------------------*/

/* stub is currently only supported without RTE-usage */
#if (DEM_INCLUDE_RTE == STD_OFF)
FUNC(Std_ReturnType, DEM_CODE) Dem_SetStorageCondition(
  uint8   StorageConditionID,
  boolean ConditionFulfilled)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_SETSTORAGECONDITION_ENTRY(StorageConditionID, ConditionFulfilled);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_SetStorageCondition, DEM_E_UNINIT);
  }
  else if ( (ConditionFulfilled != FALSE) &&
            (ConditionFulfilled != TRUE)
          )
  {
    DEM_REPORT_ERROR(DEM_SID_SetStorageCondition, DEM_E_PARAM_DATA);
  }
  else
#else
  TS_PARAM_UNUSED(ConditionFulfilled);
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* Function NOT fully implemented yet.
     * Implementation is scheduled for future releases. */
    TS_PARAM_UNUSED(StorageConditionID);
  }

  DBG_DEM_SETSTORAGECONDITION_EXIT(
    result, StorageConditionID, ConditionFulfilled);
  return result;
}
#endif

/*------------------[Dem_GetFaultDetectionCounter]--------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_GetFaultDetectionCounter(
  Dem_EventIdType EventId,
  P2VAR(Dem_FaultDetectionCounterType, AUTOMATIC, DEM_APPL_DATA)
    EventIdFaultDetectionCounter)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_GETFAULTDETECTIONCOUNTER_ENTRY(
    EventId, EventIdFaultDetectionCounter);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetFaultDetectionCounter, DEM_E_UNINIT);
  }
  else if (EventId == (Dem_EventIdType)DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetFaultDetectionCounter, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetFaultDetectionCounter, DEM_E_PARAM_CONFIG);
  }
  else if (EventIdFaultDetectionCounter == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetFaultDetectionCounter, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    if (Dem_DebounceFctPtrTable[Dem_GbiDebounceAlgo(EventId)].GetFDCFct !=
          NULL_PTR)
    {
      result = Dem_DebounceFctPtrTable[Dem_GbiDebounceAlgo(EventId)].
        GetFDCFct(EventId, EventIdFaultDetectionCounter);
    }
  }

  DBG_DEM_GETFAULTDETECTIONCOUNTER_EXIT(
    result, EventId, EventIdFaultDetectionCounter);
  return result;
}

/*------------------[Dem_GetIndicatorStatus]--------------------------------*/

/* feature related code-part concerning indicators */
#if (DEM_NUMBER_OF_INDICATORS > 0U)
FUNC(Std_ReturnType, DEM_CODE) Dem_GetIndicatorStatus(
  Dem_IndicatorIdType                                      IndicatorId,
  P2VAR(Dem_IndicatorStatusType, AUTOMATIC, DEM_APPL_DATA) IndicatorStatus)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_GETINDICATORSTATUS_ENTRY(IndicatorId, IndicatorStatus);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetIndicatorStatus, DEM_E_UNINIT);
  }
  else if (IndicatorId >= DEM_NUMBER_OF_INDICATORS)
  {
    DEM_REPORT_ERROR(DEM_SID_GetIndicatorStatus, DEM_E_PARAM_DATA);
  }
  else if (IndicatorStatus == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetIndicatorStatus, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
#if (DEM_NUM_INDICATOR_LINKS > 0U)
    /* indicator status is calculated re-entrant, as the WIR bits are evaluated
     * atomically (and further accesses are only done on constant values) */
    P2CONST(Dem_IndicatorLinkType, AUTOMATIC, DEM_CONST) IndicatorLink;
    Dem_IndicatorLnkIdxType LinkIdx;

    *IndicatorStatus = DEM_INDICATOR_OFF;

    /* point to first indicator link of according data structures */
    IndicatorLink = &Dem_IndicatorLink[Dem_IndicatorDesc[IndicatorId].StartIdx];

    for (LinkIdx = 0U;
         LinkIdx < Dem_IndicatorDesc[IndicatorId].Number;
         ++LinkIdx)
    {
      const Dem_CounterDataIdxType CounterDataIdx =
        IndicatorLink[LinkIdx].CounterDataIdx;

      if ( DEM_IS_EV_ST_BIT_WIR_SET(IndicatorLink[LinkIdx].EventId) &&
           DEM_IS_BIT_SET_IN_ARRAY(DEM_INDICATOR_CYC_COUNTER_WIR_STATUS,
                                    CounterDataIdx)
         )
      {
        if (*IndicatorStatus == DEM_INDICATOR_OFF)
        {
          /* set initial behaviour */
          *IndicatorStatus = IndicatorLink[LinkIdx].Behaviour;
        }
        else
        {
          if (*IndicatorStatus != IndicatorLink[LinkIdx].Behaviour)
          {
            /* as different behaviours are requested, SW-C is responsible
             * for behaviour selection */
            *IndicatorStatus = DEM_INDICATOR_BLINK_CONT;
          }
        }
      }
      /* else: no linked event requests its warning indicator
       * -> status remains DEM_INDICATOR_OFF */
      /* !LINKSTO Dem.Dem_GetIndicatorStatus.Unlinked,2 */
    }
#else
    /* none of the configured indicators has a link to an event*/

#if (DEM_DEV_ERROR_DETECT == STD_OFF)
    TS_PARAM_UNUSED(IndicatorId);
#endif
    /* !LINKSTO Dem.Dem_GetIndicatorStatus.Unlinked,2 */
    *IndicatorStatus = DEM_INDICATOR_OFF;
#endif

    result = E_OK;
  }

  DBG_DEM_GETINDICATORSTATUS_EXIT(result, IndicatorId, IndicatorStatus);
  return result;
}
#endif /* DEM_NUMBER_OF_INDICATORS > 0U */

/*------------------[Dem_GetEventFreezeFrameData]---------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventFreezeFrameData(
  Dem_EventIdType                        EventId,
  uint8                                  RecordNumber,
  boolean                                ReportTotalRecord,
  uint16                                 DataId,
  /* Deviation MISRA-1 */
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) DestBuffer)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_GETEVENTFREEZEFRAMEDATA_ENTRY(
    EventId, RecordNumber, ReportTotalRecord, DataId, DestBuffer);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventFreezeFrameData, DEM_E_UNINIT);
  }
  else if (EventId == (Dem_EventIdType)DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventFreezeFrameData, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventFreezeFrameData, DEM_E_PARAM_CONFIG);
  }
  else if ( (ReportTotalRecord != FALSE) &&
            (ReportTotalRecord != TRUE)
          )
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventFreezeFrameData, DEM_E_PARAM_DATA);
  }
  else if (DestBuffer == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventFreezeFrameData, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
#if (DEM_NUM_FFSEGS > 0U)
    Dem_EventMemoryEntryPtrType EvMemEntry;

    /* get freeze frame class layout */
    CONSTP2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) FFClass =
      &Dem_FFClass[Dem_GbiFFClassIdx(EventId)];

    const Dem_FFIdxType MaxNumFF = Dem_GbiMaxNumFFRecs(EventId);
    const Dem_SizeFFType SizeOfFF = Dem_SizeOfFF(FFClass);

    /*
     * ENTER critical section to protect the event memory entry
     *       call-context: any
     */
    SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

    /* check whether requested record number is valid for the event */
#if (DEM_FREEZE_FRAME_REC_NUMERATION_TYPE == DEM_FF_RECNUM_CALCULATED)
    if ( (RecordNumber == 0xFFU) ||
         ( (RecordNumber <= MaxNumFF) && (RecordNumber != 0U) ) )
#else
    if ( (RecordNumber == 0xFFU) ||
         /* Deviation MISRA-2 */
         (Dem_CheckFFRecNumValid(EventId, RecordNumber) == TRUE) )
#endif
    {
      /* search for event in event memory */
      if (Dem_SearchForEntry(EventId, &EvMemEntry, NULL_PTR) == TRUE)
      {
        const Dem_FFIdxType NumFF = DEM_NUMFF(EvMemEntry, MaxNumFF);
        Dem_FFIdxType FFIndex;

#if (DEM_FREEZE_FRAME_REC_NUMERATION_TYPE == DEM_FF_RECNUM_CALCULATED)
        FFIndex = RecordNumber - 1U;
#else
        /* valid FFIndex will be returned if the record is stored.
         * NumFF will be returned if it is not stored */
        FFIndex = Dem_CheckFFRecNumStored(EvMemEntry, RecordNumber);
#endif
        /* check if most recent record data shall be returned */
        if (RecordNumber == 0xFFU)
        {
          FFIndex = NumFF - 1U;
        }

        /* check if record is stored */
        if (FFIndex < NumFF)
        {
          /* pointer to const FF data */
          const Dem_EntryDataPtrConstType FFEntryData =
            Dem_FFEntryData(EvMemEntry, FFClass, FFIndex);

          if (ReportTotalRecord == TRUE)
          {
            /* write content into the destination buffer */
            TS_MemCpy(DestBuffer, &FFEntryData[0], SizeOfFF);

            result = E_OK;
          }
          else /* report one DID only */
          {
            const Dem_FFSegIdxType SegIndex = Dem_FindDIDIndex(FFClass, DataId);

            /* check if DID is valid (is known) for this event */
            if (SegIndex < FFClass->NumFFSegs)
            {
              const Dem_SizeFFType FFSegSize =
                Dem_SizeOfFFSegment(&Dem_FFSegment[FFClass->FFSegIdx[SegIndex]]);

              /* copy content of the DID into the destination buffer */
              TS_MemCpy(DestBuffer,
                        &FFEntryData[FFClass->StartByte[SegIndex]],
                        FFSegSize);

              result = E_OK;
            } /* else: Data Id is not valid for this event */
          }
        } /* else: event stored, freeze frame data entry does not exist */
      } /* else: event not stored */
    } /* else: non-existing record requested, "out of range" */

    /*
     * LEAVE critical section
     */
    SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();
#else
#if (DEM_DEV_ERROR_DETECT == STD_OFF)
    TS_PARAM_UNUSED(EventId);
    TS_PARAM_UNUSED(ReportTotalRecord);
    TS_PARAM_UNUSED(DestBuffer);
#endif
    TS_PARAM_UNUSED(RecordNumber);
    TS_PARAM_UNUSED(DataId);
#endif /* (DEM_NUM_FFSEGS > 0U) */
  }

  DBG_DEM_GETEVENTFREEZEFRAMEDATA_EXIT(
    result, EventId, RecordNumber, ReportTotalRecord, DataId, DestBuffer);
  return result;
}

/*------------------[Dem_GetEventExtendedDataRecord]------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventExtendedDataRecord(
  Dem_EventIdType                        EventId,
  uint8                                  RecordNumber,
  /* Deviation MISRA-1 */
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) DestBuffer)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_GETEVENTEXTENDEDDATARECORD_ENTRY(EventId, RecordNumber, DestBuffer);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventExtendedDataRecord, DEM_E_UNINIT);
  }
  else if (EventId == (Dem_EventIdType)DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventExtendedDataRecord, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventExtendedDataRecord, DEM_E_PARAM_CONFIG);
  }
  else if ( (RecordNumber == 0U) ||
            ((RecordNumber > 0xEFU) && (RecordNumber != 0xFFU)) )
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventExtendedDataRecord, DEM_E_PARAM_DATA);
  }
  else if (DestBuffer == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventExtendedDataRecord, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* no DET */
    {
#if (DEM_NUM_EDSEGS > 0U)
      Dem_EventMemoryEntryPtrType EvMemEntry;

      /* get extended data class layout */
      CONSTP2CONST(Dem_EDClassType, AUTOMATIC, DEM_CONST) EDClass =
        &Dem_EDClass[Dem_GbiEDClassIdx(EventId)];

      Dem_EDSegIdxType SegIndex = 0U;

      if (RecordNumber != 0xFFU)
      {
        /* check if record number is valid (is known) for this event */
        SegIndex = Dem_FindEDNumIndex(EDClass, RecordNumber);
      }

      /*
       * ENTER critical section to protect the event memory entry
       *       call-context: any
       */
      SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

      /* search for the event in event memory */
      if (Dem_SearchForEntry(EventId, &EvMemEntry, NULL_PTR) != FALSE)
      {
        if (RecordNumber == 0xFFU)
        {
          /* copy content of the ED class into the destination buffer */
          Dem_AssembleExtendedData(EDClass, DestBuffer, EvMemEntry);

          result = E_OK;
        }
        else
        {
          /* check if ED record is valid (is known) for this event */
          if (SegIndex < EDClass->NumEDSegs)
          {
            CONSTP2CONST(Dem_EDSegmentType, AUTOMATIC, DEM_CONST) EDSegment =
              &Dem_EDSegment[EDClass->EDSegIdx[SegIndex]];

            /* copy content of the record into the destination buffer */
            (void)Dem_AssembleExtendedDataSeg(EDSegment,
              EDClass->StartByte[SegIndex], DestBuffer, EvMemEntry);

            result = E_OK;
          } /* else: record number invalid for this event */
        }
      } /* else: event not stored in event memory implicates no extended data */

      /*
       * LEAVE critical section
       */
      SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();
#else
#if (DEM_DEV_ERROR_DETECT == STD_OFF)
      TS_PARAM_UNUSED(EventId);
      TS_PARAM_UNUSED(RecordNumber);
      TS_PARAM_UNUSED(DestBuffer);
#endif
#endif /* (DEM_NUM_EDSEGS > 0U) */
    }
  }

  DBG_DEM_GETEVENTEXTENDEDDATARECORD_EXIT(
    result, EventId, RecordNumber, DestBuffer);
  return result;
}

/*------------------[Dem_GetEventMemoryOverflow]----------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventMemoryOverflow(
  Dem_DTCOriginType                        DTCOrigin,
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA) OverflowIndication)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_GETEVENTMEMORYOVERFLOW_ENTRY(DTCOrigin, OverflowIndication);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventMemoryOverflow, DEM_E_UNINIT);
  }
  else if ( ( ( (DTCOrigin != DEM_DTC_ORIGIN_PRIMARY_MEMORY) &&
                (DTCOrigin != DEM_DTC_ORIGIN_SECONDARY_MEMORY) ) &&
              (DTCOrigin != DEM_DTC_ORIGIN_MIRROR_MEMORY) ) &&
            (DTCOrigin != DEM_DTC_ORIGIN_PERMANENT_MEMORY) )
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventMemoryOverflow, DEM_E_PARAM_DATA);
  }
  else if (OverflowIndication == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventMemoryOverflow, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    *OverflowIndication = DEM_IS_OVFIND_SET(DTCOrigin - 1U) ? TRUE : FALSE;

    result = E_OK;
  }

  DBG_DEM_GETEVENTMEMORYOVERFLOW_EXIT(result, DTCOrigin, OverflowIndication);
  return result;
}

/*------------------[Dem_SetDTCSuppression]---------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_SetDTCSuppression(
  uint32            DTC,
  Dem_DTCFormatType DTCFormat,
  boolean           SuppressionStatus)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_SETDTCSUPPRESSION_ENTRY(DTC, DTCFormat, SuppressionStatus);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_SetDTCSuppression, DEM_E_UNINIT);
  }
  else if ( (DTC == (Dem_DTCType)0U) || (DTC > (Dem_DTCType)0xFFFFFFU) )
  {
    DEM_REPORT_ERROR(DEM_SID_SetDTCSuppression, DEM_E_PARAM_DATA);
  }
  else if ( (DTCFormat != DEM_DTC_FORMAT_OBD) &&
            (DTCFormat != DEM_DTC_FORMAT_UDS)
          )
  {
    DEM_REPORT_ERROR(DEM_SID_SetDTCSuppression, DEM_E_PARAM_DATA);
  }
  else if ( (SuppressionStatus != FALSE) &&
            (SuppressionStatus != TRUE)
          )
  {
    DEM_REPORT_ERROR(DEM_SID_SetDTCSuppression, DEM_E_PARAM_DATA);
  }
  else
#else
  TS_PARAM_UNUSED(DTC);
  TS_PARAM_UNUSED(DTCFormat);
  TS_PARAM_UNUSED(SuppressionStatus);
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* Function NOT fully implemented yet.
     * Implementation is scheduled for future releases. */
  }

  DBG_DEM_SETDTCSUPPRESSION_EXIT(result, DTC, DTCFormat, SuppressionStatus);
  return result;
}

/*------------------[Dem_MainFunction]--------------------------------------*/

/* !LINKSTO Dem266,1 */
FUNC(void, DEM_CODE) Dem_MainFunction(void)
{
  DBG_DEM_MAINFUNCTION_ENTRY();

  /* verify initialization-status before performing any actions */
  if (DEM_INITIALIZED == Dem_InitializationState)
  {
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
    boolean TriggerNvMWrite = FALSE;
#endif

    /* update timers used for debouncing */
#if (DEM_NUM_DEBOUNCE_TIME > 0U)
    Dem_DebounceTimeTimerTick();
#endif
#if (DEM_NUM_DEBOUNCE_FREQUENCY > 0U)
    Dem_DebounceFrequencyTimerTick();
#endif

#if (DEM_NUM_BSWEVENT_INDICATOR_USED > 0U)
    Dem_ProcessBSWEventWIRBit();
#endif

    /* only try to access event memory if there is no
     * Dcm/(FF/ED getter function) access in progress
     */
    if (Dem_EvMemReadAccessSemaphore == 0U)
    {
      Dem_ErrorQueueEntryType QueueEntry = 0U;
      boolean QueueEntryIsFetched;

      /* if DTCRecordUpdate is disabled entries need not be
       * re-entered into the queue and can be skipped
       */
      do
      {
        /*
         * ENTER critical section to protect the error-queue & queue-pointers
         *       call-context: Dem (Task)
         */
        SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

        QueueEntryIsFetched = Dem_ReadErrorQueueEntry(&QueueEntry);

        /*
         * LEAVE critical section
         */
        SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

        if (QueueEntryIsFetched)
        {
          Dem_EventNotificationDataType Notification =
            {
              /* ReplacedEventMsg */
              { DEM_EVENT_ID_INVALID, 0x00U, 0x00U },
#if ( (DEM_USE_CB_TRIG_ON_EVST  == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) )
              /* ProcessedEventMsg */
              { DEM_EVENT_ID_INVALID, 0x00U, 0x00U },
#endif
#if ( (DEM_USE_CB_TRIG_ON_EVDAT == STD_ON) && \
      ( (DEM_NUM_EDSEGS > 0U) || (DEM_NUM_FFSEGS > 0U) ) )
              /* TriggerOnEvenData */
              DEM_EVENT_ID_INVALID
#endif
            };

          Dem_ProcessEventEntry(
            DEM_ERRORQUEUE_GET_EVID(QueueEntry),
            DEM_ERRORQUEUE_GET_EVST(QueueEntry),
            &Notification);

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
          /* flag to trigger NvM write after queue entry processing */
          TriggerNvMWrite = TRUE;
#endif

#if ( (DEM_USE_CB_TRIG_ON_EVST  == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) || \
      ( (DEM_USE_CB_TRIG_ON_EVDAT == STD_ON) && \
        ( (DEM_NUM_EDSEGS > 0U) || (DEM_NUM_FFSEGS > 0U) ) ) )
          Dem_ProcessEventNotifications(&Notification);
#endif
        }
      }
      while (QueueEntryIsFetched);
    }

#if (DEM_NUM_FAILURECYCLES > 0U)

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
    /* event failure cycle Counter has been changed */
    TriggerNvMWrite = TRUE;
#endif

    /* process fault confirmation for all stored events */
    Dem_ProcessFaultConfirmation();
#endif

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
    /* check if NvM must be triggered */
    if (TriggerNvMWrite != FALSE)
    {
      /* event entries and/or event cycle counter have changed
       * -> trigger NvM write */
      Dem_TriggerNvmWriteGateEntry();
    }
#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */
  }

  DBG_DEM_MAINFUNCTION_EXIT();
}

/*==================[internal function definitions]=========================*/

/*------------------[NvData-related sub-functions]--------------------------*/

#if (DEM_USE_PERMANENT_STORAGE == STD_ON)
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_NvMGetNvRAMDataStatus(void)
{
  Std_ReturnType result;
  NvM_RequestResultType RestoredNvData;

  DBG_DEM_NVMGETNVRAMDATASTATUS_ENTRY();

  /* get status from NvM of Dem default block */
  (void)NvM_GetErrorStatus(DEM_NVM_BLOCK_ID_DEFAULT, &RestoredNvData);
  result = (Std_ReturnType)((RestoredNvData == NVM_REQ_OK) ? E_OK : E_NOT_OK);

  DBG_DEM_NVMGETNVRAMDATASTATUS_EXIT(result);
  return result;
}
#endif

STATIC FUNC(void, DEM_CODE) Dem_ResetNvData(void)
{
  Dem_EvIdLeastType EvId;
#if (DEM_NUM_INDICATOR_LINKS > 0U)
  Dem_IndicatorLnkIdxType LinkIdx;
  Dem_IndicatorLnkIdxType ByteIdx;
#endif
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_OFF)
  uint8_least originIdx;
  Dem_SizeEvMemEntryType entryIdx;
#endif
#if (DEM_OPCYC_NVSTORAGE == STD_ON)
  Dem_OperationCycleIdType OpCycleId;
#endif

  DBG_DEM_RESETNVDATA_ENTRY();

  /* init loop for events */
  for (EvId = 0U; EvId <= DEM_MAX_EVENTID; ++EvId)
  {
    /* clear all DTC status bits beside "not tested this operating cycle"
     * and "not tested since last clear" */
    DEM_DTC_STATUS_MASKS[EvId] =
      DEM_DTCSTATUSBIT_TNCSLC |
      DEM_DTCSTATUSBIT_TNCTOC;
  }

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_OFF)
  /* init loop for event memories */
  for (originIdx = 0U; originIdx < DEM_MAXNUM_ORIGINS; ++originIdx)
  {
    /* for every event entry */
    for (entryIdx = 0U; entryIdx < Dem_SizeEventMem[originIdx]; ++entryIdx)
    {
      /* mark entry in event memory as cleared */
      Dem_EventMem[originIdx][entryIdx].EventId =
        (Dem_EventIdType)DEM_EVENT_ID_INVALID;

      /* freeze frame counter of the entry needs not to be initialized */
      /* not necessary:  EventMem[originIdx][entryIdx].OccCtr = 0 */

      /* position of entry data will calculated on new entry */
      /* not necessary:  EventMem[originIdx][entryIdx].EntryDataPos = 0 */
    }

    /* Dem_EntryDataFreePos[originIdx] may be NULL_PTR, if no event
     * configured for this memory has any entry data */
    if (Dem_EntryDataFreePos[originIdx] != NULL_PTR)
    {
      /* initialize free position of event memory entry data */
      *(Dem_EntryDataFreePos[originIdx]) = 0U;
    }

    /* event memory entry data need not to be initialized */
    /* Dem_EntryData[originIdx][0 .. Dem_SizeEntryData[originIdx]] = 0 */
  }
#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_OFF */

  /* clear event memory overflow indication flags */
  DEM_OVFIND_FLAGS = 0U;

#if (DEM_NUM_INDICATOR_LINKS > 0U)
  for (LinkIdx = 0U; LinkIdx < DEM_NUM_INDICATOR_LINKS; ++LinkIdx)
  {
    /* clear indicator cycle counter */
    DEM_INDICATOR_CYC_COUNTER[LinkIdx] = 0U;
  }

  for (ByteIdx = 0U;
       ByteIdx < ((DEM_NUM_INDICATOR_LINKS + 7U) / 8U);
       ++ByteIdx)
  {
    /*  set indicator cycle counter role flag
     * (i.e: DEM_INDICATORCOUNTER_ROLE_HEALING_CYCLE_COUNTER) */
    DEM_INDICATOR_CYC_COUNTER_ROLE[ByteIdx] = 0xFFU;

    /* clear indicator cycle counter WIR status */
    DEM_INDICATOR_CYC_COUNTER_WIR_STATUS[ByteIdx] = 0U;
  }
#endif /* (DEM_NUM_INDICATOR_LINKS > 0U) */

#if (DEM_OPCYC_NVSTORAGE == STD_ON)
  /* reset operation cycle state array */
  for (OpCycleId = 0U; OpCycleId < DEM_NUM_OPCYCLES; ++OpCycleId)
  {
    DEM_OPCYCLESTATE[OpCycleId] = DEM_CYCLE_STATE_END;
  }
#endif
  DBG_DEM_RESETNVDATA_EXIT();
}

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
STATIC FUNC(void, DEM_CODE) Dem_RestoreImmediateData(void)
{
  uint8_least originIdx;
  Dem_SizeEvMemEntryType entryIdx;
  Dem_EvIdLeastType EvId;

  Std_ReturnType readBlockResult;
  NvM_RequestResultType reqResult = NVM_REQ_NOT_OK;

  DBG_DEM_RESTOREIMMEDIATEDATA_ENTRY();

  /* clear CDTC bits for the case, that Dem_NvData could be
   * loaded but one event memory entry (NvM block) got lost */
  for (EvId = 0U; EvId <= DEM_MAX_EVENTID; ++EvId)
  {
    DEM_CLR_EV_ST_MASK(EvId, DEM_DTCSTATUSBIT_CDTC);
  }

  /* init loop for all event memories */
  for (originIdx = 0U; originIdx < (uint8)DEM_MAXNUM_ORIGINS; ++originIdx)
  {
    const Dem_SizeEvMemEntryType sizeEventMem = Dem_SizeEventMem[originIdx];

    /* event memory is used */
    if (sizeEventMem != (Dem_SizeEvMemEntryType)0U)
    {
      CONSTP2VAR(Dem_GateEntryBaseType, AUTOMATIC, DEM_VAR_NOINIT)
        GateEntryBase = Dem_NvGateEntryData[originIdx];

      const NvM_BlockIdType NvDataBlockId = Dem_NvDataBlockId[originIdx];

      /* clear gate-entry (for the case that no event memory entry can be
       * restored) */
      GateEntryBase->EntryBase.EventId = (Dem_EventIdType)DEM_EVENT_ID_INVALID;

      /* need not initialize entry data of the corresponding event memory
       * as during write to gate within Dem_StoreImmediately() only valid
       * freeze frame datas are written and rest of the entry is initialized
       * to zero */

      /* Dem_EntryDataFreePos[originIdx] may be NULL_PTR, if no event
       * configured for this memory has any entry data */
      if (Dem_EntryDataFreePos[originIdx] != NULL_PTR)
      {
        /* initalize free position of event memory entry data */
        *(Dem_EntryDataFreePos[originIdx]) = 0U;
      }

      /* for each event memory entry */
      for (entryIdx = 0U; entryIdx < sizeEventMem; ++entryIdx)
      {
        /* --- transfer NVRAM content into gate-entry --- */

        const Dem_EventMemoryEntryPtrType EvMemEntry =
          &Dem_EventMem[originIdx][entryIdx];

        /* select corresponding NVRAM block dataset */
        (void)NvM_SetDataIndex(NvDataBlockId, (uint8)entryIdx);

        /* queue read request of gate-entry to NvM - NvM_DstPtr is unused,
         * as permanent RAM block (gate-entry) is configured */
        readBlockResult = NvM_ReadBlock(NvDataBlockId, NULL_PTR);

        /* if NvM read request was not accepted */
        if (readBlockResult == E_OK)
        {
          /* trigger the memory-stack main functions synchronously */
          DEM_STORAGEWAITNVMREADY(NvDataBlockId);

          /* check if NVRAM dataset was successfully restored */
          (void)NvM_GetErrorStatus(NvDataBlockId, &reqResult);

          /* Nv-data consistence-checks against configuration are not done and
           * has to be ensured for example by the ECU flash-process */
          if (reqResult == NVM_REQ_OK)
          {
            /* --- transfer gate-entry into event memory entry --- */

            EvId = GateEntryBase->EntryBase.EventId;

            /* restore EventId from gate-entry */
            EvMemEntry->EventId = (Dem_EventIdType)EvId;

            /* mark event entry as unchanged concerning its persistent data */
            EvMemEntry->EntryStatus = DEM_ENTRY_UNCHANGED;

            /* check if event exists in the event memory */
            if (EvId != (Dem_EventIdType)DEM_EVENT_ID_INVALID)
            {
              Dem_SizeEntryDataType EntryDataFreePos = 0U;
              const Dem_SizeEntryDataType sizeEntryData =
                Dem_SizeOfEntryData((Dem_EventIdType)EvId);
#if (DEM_NUM_FAILURECYCLES > 0U)
              uint8 EventFailureClassIdx =
                Dem_GbiEventFailureClassIdx((Dem_EventIdType)EvId);
#endif

              if (Dem_EntryDataFreePos[originIdx] != NULL_PTR)
              {
                EntryDataFreePos = *(Dem_EntryDataFreePos[originIdx]);
              }

              /* initalize free position of event memory entry data */
              EvMemEntry->EntryDataPos = EntryDataFreePos;

              /* restore OccCtr and OccOrder from gate-entry */
              EvMemEntry->OccCtr = GateEntryBase->EntryBase.OccCtr;
#if (DEM_USE_EVENT_DISPLACEMENT == STD_ON)
              EvMemEntry->OccOrder = GateEntryBase->EntryBase.OccOrder;
#endif

#if (DEM_NUM_FAILURECYCLES > 0U)
              /* restore EventFailureCycleCounter from gate-entry */
              EvMemEntry->EventFailureCycleCounter =
                GateEntryBase->EntryBase.EventFailureCycleCounter;
#endif

              /* check if event data exists */
              if (sizeEntryData > 0U)
              {
                /* copy gate-entry data into event memory entry data */
                TS_MemCpy(&Dem_EntryData[originIdx][EntryDataFreePos],
                  (Dem_EntryDataPtrConstType)Dem_GateEntryData[originIdx],
                  sizeEntryData);

                /* recalculate free position of event memory entry data */
                *(Dem_EntryDataFreePos[originIdx]) += sizeEntryData;
              }

              /* set the status bits correctly for the case when they may not
               * have been restored during NvM_ReadAll():
               * only bits TNCSLC, CDTC and TFSLC are set as they can directly
               * be derived from event memory entries */
              DEM_CHNG_EV_ST_MASK(EvId,
                                  DEM_DTCSTATUSBIT_TFSLC,
                                  DEM_DTCSTATUSBIT_TNCSLC);
              /* set the CDTC bit if
               * the event has default configuration for fault confirmation
               * (i.e. CDTC bit is set immediately after the event gets
               * qualified as failed)
               * or the restored failure counter value equals the
               * configured failure counter threshold value for the event */
#if (DEM_NUM_FAILURECYCLES > 0U)
              if ( (EventFailureClassIdx == DEM_NO_FAULT_CONFIRMATION) ||
                   (EvMemEntry->EventFailureCycleCounter ==
                      Dem_EventFailureCycleCfg[EventFailureClassIdx].
                        EventFailureCycleCounterThreshold) )
#endif
              {
                DEM_SET_EV_ST_MASK(EvId, DEM_DTCSTATUSBIT_CDTC);
              }
            }
            /* else: not necessary to reset any other data of this entry */
          }
          else /* reqResult != NVM_REQ_OK */
          {
            /* clear event memory entry */
            EvMemEntry->EventId = (Dem_EventIdType)DEM_EVENT_ID_INVALID;

            /* not necessary to reset EvMemEntry->OccCtr (= 0) */
            /* not necessary to reset EvMemEntry->OccOrder (= 0) */
            /* not necessary to reset EvMemEntry->EntryDataPos (= 0) */
            /* not necessary to reset event memory entry data */

            /* !LINKSTO Dem.NvStorageEmptyEvMemEntries.Shutdown,1 */
            /* restoration of data from NvM was not successful,
             * depend on configuration: */
#if (DEM_NV_STORAGE_EMPTY_EVMEM_ENTRIES == STD_ON)
            /* mark entry as changed so that at least initialized data
             * is stored persistently during next shutdown */
            EvMemEntry->EntryStatus = DEM_ENTRY_CHANGED;
#else
            /* only occupied entries will be stored, to avoid NvRAM aging */
#endif
          }
        }
        else /* readBlockResult != E_OK */
        {
          /* clear event memory entry */
          EvMemEntry->EventId = (Dem_EventIdType)DEM_EVENT_ID_INVALID;

          /* not necessary to reset EvMemEntry->OccCtr (= 0) */
          /* not necessary to reset EvMemEntry->OccOrder (= 0) */
          /* not necessary to reset EvMemEntry->EntryDataPos (= 0) */
          /* not necessary to reset event memory entry data */

          /* !LINKSTO Dem.NvStorageEmptyEvMemEntries.Shutdown,1 */
          /* invalid data exist (as read was not successful),
           * depend on configuration: */
#if (DEM_NV_STORAGE_EMPTY_EVMEM_ENTRIES == STD_ON)
          /* mark entry as changed so that at least initialized data
           * is stored persistently during next shutdown */
          EvMemEntry->EntryStatus = DEM_ENTRY_CHANGED;
#else
          /* only occupied entries will be stored, to avoid NvRAM aging */
#endif
        }
      }
    }
  }

  DBG_DEM_RESTOREIMMEDIATEDATA_EXIT();
}
#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */

/*------------------[internal error-queue access-function definitions]------*/

FUNC(void, DEM_CODE) Dem_InvalidateErrorQueueEntry(Dem_EventIdType EventId)
{
  Dem_ErrorQueueIdxType ErrorQueueIndex = Dem_ErrorQueueReadIdx;
  boolean ProcessFirstEntryOfFullQueue = FALSE;

  DBG_DEM_INVALIDATEERRORQUEUEENTRY_ENTRY(EventId);

  /* if queue is full */
  if ( (ErrorQueueIndex == Dem_ErrorQueueWriteIdx) &&
       (Dem_ErrorQueue[ErrorQueueIndex] != DEM_EVENT_ID_INVALID) )
  {
    /* mark first entry to be processed since read/write-index are the same */
    ProcessFirstEntryOfFullQueue = TRUE;
  }

  /* loop through all used queue entries (from read- to write-index) */
  while ( (ErrorQueueIndex != Dem_ErrorQueueWriteIdx) ||
          (ProcessFirstEntryOfFullQueue == TRUE) )
  {
    const Dem_EventIdType ErrorQueueEventId =
      DEM_ERRORQUEUE_GET_EVID(Dem_ErrorQueue[ErrorQueueIndex]);

    /* mark entries with targeted event Id as ignore for later processing */
    if (ErrorQueueEventId == EventId)
    {
      Dem_ErrorQueue[ErrorQueueIndex] =
        (Dem_ErrorQueueEntryType)DEM_EVENT_ID_IGNORE;
    }

    ++ErrorQueueIndex;
    ErrorQueueIndex %= DEM_BSW_ERROR_BUFFER_SIZE;

    /* first entry was processed */
    ProcessFirstEntryOfFullQueue = FALSE;
  }

  DBG_DEM_INVALIDATEERRORQUEUEENTRY_EXIT(EventId);
}

FUNC(boolean, DEM_CODE) Dem_ReadErrorQueueEntry(
  CONSTP2VAR(Dem_ErrorQueueEntryType, AUTOMATIC, AUTOMATIC) QueueEntry)
{
  boolean result = FALSE;

  DBG_DEM_READERRORQUEUEENTRY_ENTRY(QueueEntry);

  /* ignore all invalidated entries before the next valid/empty entry */
  while (Dem_ErrorQueue[Dem_ErrorQueueReadIdx] ==
           (Dem_ErrorQueueEntryType)DEM_EVENT_ID_IGNORE)
  {
    /* remove entry from queue */
    Dem_ErrorQueue[Dem_ErrorQueueReadIdx] = DEM_EVENT_ID_INVALID;

    ++Dem_ErrorQueueReadIdx;
    Dem_ErrorQueueReadIdx %= DEM_BSW_ERROR_BUFFER_SIZE;
  }

  /* read queue entry */
  if (Dem_ErrorQueue[Dem_ErrorQueueReadIdx] !=
        (Dem_ErrorQueueEntryType)DEM_EVENT_ID_INVALID)
  {
    *QueueEntry = Dem_ErrorQueue[Dem_ErrorQueueReadIdx];

    /* remove entry from queue */
    Dem_ErrorQueue[Dem_ErrorQueueReadIdx] = DEM_EVENT_ID_INVALID;

    ++Dem_ErrorQueueReadIdx;
    Dem_ErrorQueueReadIdx %= DEM_BSW_ERROR_BUFFER_SIZE;

    result = TRUE;
  }

  DBG_DEM_READERRORQUEUEENTRY_EXIT(result, QueueEntry);
  return result;
}

FUNC(boolean, DEM_CODE) Dem_WriteErrorQueueEntry(
  const Dem_EventIdType     EventId,
  const Dem_EventStatusType EventStatus)
{
  boolean result = FALSE;

  DBG_DEM_WRITEERRORQUEUEENTRY_ENTRY(EventId, EventStatus);

  if (Dem_ErrorQueue[Dem_ErrorQueueWriteIdx] ==
        (Dem_ErrorQueueEntryType)DEM_EVENT_ID_INVALID)
  {
    Dem_ErrorQueueEntryType QueueEntry = (Dem_ErrorQueueEntryType)EventId;

    if (EventStatus == DEM_EVENT_STATUS_FAILED)
    {
      /* highest bit to one */
      QueueEntry |= 0x8000U;
    }
    /* else: for passed status, no need to clear highest bit, since default
     * value is 0 (because the event range is limited by configuration) */

    Dem_ErrorQueue[Dem_ErrorQueueWriteIdx] = QueueEntry;

    ++Dem_ErrorQueueWriteIdx;
    Dem_ErrorQueueWriteIdx %= DEM_BSW_ERROR_BUFFER_SIZE;

    result = TRUE;
  }

  DBG_DEM_WRITEERRORQUEUEENTRY_EXIT(result, EventId, EventStatus);
  return result;
}

FUNC(boolean, DEM_CODE) Dem_CheckErrorQueueEntry(
  const Dem_EventIdType                                 EventId,
  CONSTP2VAR(Dem_EventStatusType, AUTOMATIC, AUTOMATIC) PreviousEntryStatus)
{
  boolean result = FALSE;

  DBG_DEM_CHECKERRORQUEUEENTRY_ENTRY(EventId, PreviousEntryStatus);

  /* check if error-queue is not empty */
  if (Dem_ErrorQueue[Dem_ErrorQueueReadIdx] !=
        (Dem_ErrorQueueEntryType)DEM_EVENT_ID_INVALID)
  {
    Dem_ErrorQueueEntryType QueueEntry;
    uint8 index = Dem_ErrorQueueWriteIdx;

    /* search error-queue from Dem_ErrorQueueWriteIdx - 1 (most recent entry)
     * decreasing to Dem_ErrorQueueReadIdx (oldest entry) in circular way */
    do
    {
      if (index == 0U)
      {
        index = DEM_BSW_ERROR_BUFFER_SIZE - 1U;
      }
      else
      {
        index--;
      }

      QueueEntry = Dem_ErrorQueue[index];

      if (EventId == DEM_ERRORQUEUE_GET_EVID(QueueEntry))
      {
        *PreviousEntryStatus = DEM_ERRORQUEUE_GET_EVST(QueueEntry);
        result = TRUE;
      }
    }
    while ((Dem_ErrorQueueReadIdx != index) && (result == FALSE));
  }

  DBG_DEM_CHECKERRORQUEUEENTRY_EXIT(result, EventId, PreviousEntryStatus);
  return result;
}

/*------------------[further sub-functions]---------------------------------*/

#if (DEM_MAX_NUMBER_PRESTORED_FF > 0U)
STATIC FUNC(Dem_EntryDataPtrType, DEM_CODE) Dem_GetPFFEntryDataPtr(
  Dem_EventIdType EventId)
{
  Dem_EntryDataPtrType result;
  Dem_SizeEntryDataType StartPos = 0U;

  Dem_EventIdType EvId;

  DBG_DEM_GETPFFENTRYDATAPTR_ENTRY(EventId);

  /* check if there are PFFs in front of the target PFF */
  for (EvId = 0U; EvId < EventId; ++EvId)
  {
    if (Dem_GbiEnablePrestorage(EvId) == TRUE)
    {
      /* get freeze frame class layout */
      CONSTP2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) FFClass =
        &Dem_FFClass[Dem_GbiFFClassIdx(EvId)];

      /* update start position of PFF */
      StartPos += Dem_SizeOfFF(FFClass);
    }
  }

  result = &Dem_PFFEntryData[StartPos];

  DBG_DEM_GETPFFENTRYDATAPTR_EXIT(result, EventId);
  return result;
}
#endif

#if (DEM_USE_AGING == STD_ON)
STATIC FUNC(void, DEM_CODE) Dem_UpdateAgingCounter(
  const Dem_EventIdType EventId
)
{
  Dem_EventMemoryEntryPtrType EvMemEntry;
  Dem_SizeEvMemEntryType EvMemEntryIdx;
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
  const uint8 OriginIdx = Dem_GbiDTCOriginIdx(EventId);
  Dem_NvMGatePrepStatusType NvMGateStatus;
#endif

  DBG_DEM_UPDATEAGINGCOUNTER_ENTRY(EventId);

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
  /* try to lock gate entry */
  NvMGateStatus = Dem_BeginPrepareGateEntry(OriginIdx);
#endif

  /*
   * ENTER critical section to protect the event memory entry
   *       call-context: Rte (Task)
   */
  SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

  if (Dem_SearchForEntry(EventId, &EvMemEntry, &EvMemEntryIdx) == TRUE)
  {
    /* pointer to internal aging value */
    const Dem_EntryDataPtrType AgingCounterPtr =
      Dem_IntValEntryData(EvMemEntry);

    /* decrease aging counter if it has not reached zero
     * (while DTCRecordUpdate was disabled) */
    if (*AgingCounterPtr > 0U)
    {
      (*AgingCounterPtr) -= 1U;
    }

    /* age the event if counter reaches zero */
    if ( (*AgingCounterPtr == 0U) &&
         (EventId != Dem_EvIdOfRecordUpdateDisabledDTC) )
    {
      Dem_ClearAgedEventEntry(EventId, EvMemEntry);
    }

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
    if ( (*AgingCounterPtr != 0U) ||
         (EventId != Dem_EvIdOfRecordUpdateDisabledDTC) )
    {
      /* event memory entry has been updated or event is aged:
       * it needs to be stored immediately if the immediate storage
       * is enabled for the updated or cleared event */
      Dem_CheckForImmediateEntryStorage(EventId,
                                        EvMemEntry,
                                        EvMemEntryIdx,
                                        DEM_NVM_NO_FORCE,
                                        &NvMGateStatus);
    }
#endif
  }

  /*
   * LEAVE critical section
   */
  SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
    Dem_EndPrepareGateEntry(OriginIdx, NvMGateStatus);
#endif

#if ( (DEM_USE_CB_TRIG_ON_EVDAT == STD_ON) && \
      (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON) )
  if (Dem_CheckIntDataElementUsage(EventId, DEM_INT_VAL_IDX_AGECTR))
  {
    /* notify application that event data has changed */
    Dem_CbTriggerOnEventData(EventId);
  }
#endif

  DBG_DEM_UPDATEAGINGCOUNTER_EXIT(EventId);
}
#endif /* DEM_USE_AGING */

STATIC FUNC(boolean, DEM_CODE) Dem_GetEvStBitVal(
  Dem_EventIdType             EventId,
  Dem_EventStatusExtendedType EventStatusExtendedMask)
{
  boolean result;
  const Dem_EventStatusExtendedType EventStatusExtended =
    DEM_DTC_STATUS_MASKS[EventId];

  DBG_DEM_GETEVSTBITVAL_ENTRY(EventId, EventStatusExtendedMask);

  result =
    DEM_IS_BIT_SET(EventStatusExtended, EventStatusExtendedMask) ?
      TRUE : FALSE;

  DBG_DEM_GETEVSTBITVAL_EXIT(result, EventId, EventStatusExtendedMask);
  return result;
}

STATIC FUNC(void, DEM_CODE) Dem_ProcessEventEntry(
  const Dem_EventIdType     EventId,
  const Dem_EventStatusType EventStatus,
  const Dem_EventNotificationDataPtrType Notification)
{
  /* Function is used on several places.
   * Calling it only here, reduces number of its executions. */
  const Dem_EventKindType eventKind = Dem_GbiEventKind(EventId);
  const boolean previousTF = (DEM_IS_EV_ST_BIT_TF_SET(EventId)) ? TRUE : FALSE;

  DBG_DEM_PROCESSEVENTENTRY_ENTRY(EventId, EventStatus, Notification);

  /*
   * ENTER critical section to protect the event memory
   *       call-context: Dem (Task)
   */
  SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

#if ( (DEM_USE_CB_TRIG_ON_EVST == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) )
  /* store the old & new DTC status mask for 'status changed' notifications */
  Notification->ProcessedEventMsg.OldStatusMask =
    DEM_DTC_STATUS_MASKS[EventId];
  Notification->ProcessedEventMsg.NewStatusMask =
    Notification->ProcessedEventMsg.OldStatusMask;
#endif

  if (eventKind == DEM_EVENT_KIND_BSW)
  {
    /* intentional nested critical section in this call */
    Dem_UpdateEventStatusOnQualification(EventId, EventStatus);
  }

  if ((EventStatus == DEM_EVENT_STATUS_FAILED) &&
      ((eventKind == DEM_EVENT_KIND_SWC) ||
       ((eventKind == DEM_EVENT_KIND_BSW) && (previousTF == FALSE))
      )
     )
  {
    /* pointer to existing or newly allocated event memory entry */
    Dem_EventMemoryEntryPtrType EvMemEntryPtr =
      (Dem_EventMemoryEntryPtrType)NULL_PTR;
    /* index of exisiting or newly allocated event memory entry */
    Dem_SizeEvMemEntryType EvMemEntryIdx;
    /* event id used for immediate storage. is overwritten by the
     * entry allocation function in case an exisiting entry is replaced. */
    Dem_EventIdType ReplacedEventId = EventId;
    Dem_EventEntryAllocResultType eventEntryAllocResult;

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
    const uint8 OriginIdx = Dem_GbiDTCOriginIdx(EventId);
    Dem_NvMGateStatusType NvMGateStatus;
    boolean NvMForceWrite = DEM_NVM_NO_FORCE;

    /* try to lock the gate entry */
    /* intentional nested critical section in this call */
    NvMGateStatus = Dem_BeginPrepareGateEntry(OriginIdx);
#endif

    eventEntryAllocResult =
      Dem_FindOrAllocateEventEntry(EventId,
                                   &EvMemEntryPtr,
                                   &EvMemEntryIdx,
                                   &ReplacedEventId,
                                   &Notification->ReplacedEventMsg);

    if (eventEntryAllocResult != DEM_EVENTENTRYALLOC_INVALID)
    {
      /* increment the occurrence counter of the event which is used for
       * calculating the number of freeze frames, for limiting the number of
       * times the event is stored immediately to NvM (by comparing with NvM
       * storage limit, if configured) and for using as an internal data
       * element if the occurrence counter is mapped to extended data */
      if (EvMemEntryPtr->OccCtr < 0xFFU)
      {
        ++(EvMemEntryPtr->OccCtr);
      }

#if ((DEM_USE_INT_VAL_AREA == STD_ON) || \
     (DEM_NUM_EDSEGS > 0U) || (DEM_NUM_FFSEGS > 0U))
      /* update internal, extended and freeze frame data */

#if (DEM_USE_AGING == STD_ON)
      if (DEM_AGING_ALLOWED(EventId))
      {
        /* reset aging counter */
        DEM_ATOMIC_ASSIGN_8(*(Dem_IntValEntryData(EvMemEntryPtr)),
                            Dem_GbiNumAgingCycles(EventId));
      }
#endif /* DEM_USE_AGING */

#if (DEM_NUM_EDSEGS > 0U)
#if (DEM_USE_CB_TRIG_ON_EVDAT == STD_ON)
      /* process extended data for event */
      if (Dem_ProcessEventEntryEData(
            EventId, EvMemEntryPtr, eventEntryAllocResult) == TRUE)
      {
        Notification->TriggerOnEventData = EventId;
      }
#else
      (void)Dem_ProcessEventEntryEData(
              EventId, EvMemEntryPtr, eventEntryAllocResult);
#endif
#endif /* (DEM_NUM_EDSEGS > 0U) */

#if (DEM_NUM_FFSEGS > 0U)
#if (DEM_USE_CB_TRIG_ON_EVDAT == STD_ON)
      /* process freeze frame data for event */
      if (Dem_ProcessEventEntryFFData(EventId, EvMemEntryPtr) == TRUE)
      {
        Notification->TriggerOnEventData = EventId;
      }
#else
      (void)Dem_ProcessEventEntryFFData(EventId, EvMemEntryPtr);
#endif
#endif /* (DEM_NUM_FFSEGS > 0U) */

#endif /* ((DEM_USE_INT_VAL_AREA == STD_ON) ||
           (DEM_NUM_EDSEGS > 0U) || (DEM_NUM_FFSEGS > 0U)) */

#if (DEM_USE_EVENT_DISPLACEMENT == STD_ON)
      /* update the occurrence order of the event */
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
      NvMForceWrite = Dem_UpdateOccurrenceOrder(EvMemEntryPtr);
#else
      (void)Dem_UpdateOccurrenceOrder(EvMemEntryPtr);
#endif
#endif /* DEM_USE_EVENT_DISPLACEMENT == STD_ON */

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
      Dem_CheckForImmediateEntryStorage(ReplacedEventId,
                                        EvMemEntryPtr,
                                        EvMemEntryIdx,
                                        NvMForceWrite,
                                        &NvMGateStatus);
#endif
    }
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
    /* unlock the gate entry */
    /* intentional nested critical section in this call */
    Dem_EndPrepareGateEntry(OriginIdx, NvMGateStatus);
    /* no need to trigger NvM write here, this is done at the end of main */
#endif
  }
#if ( (DEM_USE_CB_TRIG_ON_EVST == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) )
  Notification->ProcessedEventMsg.NewStatusMask =
  DEM_DTC_STATUS_MASKS[EventId];

  /* check if DTC status has changed for new event
   * remark: this is always true for BSW events (TF bit changes) */
  if ( (Notification->ProcessedEventMsg.OldStatusMask !=
        Notification->ProcessedEventMsg.NewStatusMask) ||
       (eventKind == DEM_EVENT_KIND_BSW) )
  {
    /* status has changed, mark message 'to be sent' by writing event id */
    Notification->ProcessedEventMsg.EventId = EventId;
  }
#endif

  /*
   * LEAVE critical section
   */
  SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

  DBG_DEM_PROCESSEVENTENTRY_EXIT(EventId, EventStatus, Notification);
}

#if ( (DEM_USE_CB_TRIG_ON_EVST  == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) || \
      ( (DEM_USE_CB_TRIG_ON_EVDAT == STD_ON) && \
        ( (DEM_NUM_EDSEGS > 0U) || (DEM_NUM_FFSEGS > 0U) ) ) )
STATIC FUNC(void, DEM_CODE) Dem_ProcessEventNotifications(
  const Dem_EventNotificationDataPtrType Notification)
{
  DBG_DEM_PROCESSEVENTNOTIFICATIONS_ENTRY(Notification);

#if ( (DEM_USE_CB_TRIG_ON_EVST  == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) )
    /* check if an EventStatusChangedMsg has been prepared by displacement */
  if (Notification->ReplacedEventMsg.EventId != DEM_EVENT_ID_INVALID)
  {
    Dem_CbTriggerOnEventStatus(Notification->ReplacedEventMsg.EventId,
                               Notification->ReplacedEventMsg.OldStatusMask,
                               Notification->ReplacedEventMsg.NewStatusMask);
  }
#endif

#if ( (DEM_USE_CB_TRIG_ON_EVDAT == STD_ON) && \
      ( (DEM_NUM_EDSEGS > 0U) || (DEM_NUM_FFSEGS > 0U) ) )
  /* trigger EventDataChanged RTE/C callback (only once), when the event
   * memory entry for the event was updated */
  if (Notification->TriggerOnEventData != DEM_EVENT_ID_INVALID)
  {
    /* notify application that event data has changed */
    Dem_CbTriggerOnEventData(Notification->TriggerOnEventData);
  }
#endif

#if ( (DEM_USE_CB_TRIG_ON_EVST  == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) )
  if (Notification->ProcessedEventMsg.EventId != DEM_EVENT_ID_INVALID)
  {
    Dem_CbTriggerOnEventStatus(Notification->ProcessedEventMsg.EventId,
                               Notification->ProcessedEventMsg.OldStatusMask,
                               Notification->ProcessedEventMsg.NewStatusMask);
  }
#endif

  DBG_DEM_PROCESSEVENTNOTIFICATIONS_EXIT(Notification);
}
#endif

STATIC FUNC(Dem_EventEntryAllocResultType, DEM_CODE)
  Dem_FindOrAllocateEventEntry(
    const Dem_EventIdType EventId,
    CONSTP2VAR(Dem_EventMemoryEntryPtrType, AUTOMATIC, AUTOMATIC) EvMemEntryPtr,
    CONSTP2VAR(Dem_SizeEvMemEntryType, AUTOMATIC, AUTOMATIC)      EvMemIdxPtr,
    CONSTP2VAR(Dem_EventIdType, AUTOMATIC, AUTOMATIC) ReplacedEventIdPtr,
    const Dem_EventStatusChangedMsgPtrType            EventStatusChangedMsgPtr)
{
  Dem_EventEntryAllocResultType allocationResult = DEM_EVENTENTRYALLOC_INVALID;
  const uint8 originIdx = Dem_GbiDTCOriginIdx(EventId);

  DBG_DEM_FINDORALLOCATEEVENTENTRY_ENTRY(EventId, EvMemEntryPtr, EvMemIdxPtr,
    ReplacedEventIdPtr, EventStatusChangedMsgPtr);

  /* search for DTC in event memory */
  if (Dem_SearchForEntry(EventId, EvMemEntryPtr, EvMemIdxPtr) == FALSE)
  {
    /* event entry not found -> search empty event memory entry */
    if (Dem_SearchForEmptyEntry(originIdx, EvMemEntryPtr, EvMemIdxPtr) == FALSE)
    {
      /* !LINKSTO Dem400,1
       * empty entry not found -> find replaceable event memory entry */
      allocationResult =
        Dem_ReplaceEventEntry(EventId, originIdx, EvMemEntryPtr, EvMemIdxPtr,
                              ReplacedEventIdPtr, EventStatusChangedMsgPtr);
    }
    else /* empty entry found */
    {
      /* an empty entry has been found and allocated */
      allocationResult = DEM_EVENTENTRYALLOC_ALLOCATED;
    }

    if (allocationResult != DEM_EVENTENTRYALLOC_INVALID)
    {
      /* create new event memory entry for the new or replaced event */
      const Dem_SizeEntryDataType width = Dem_SizeOfEntryData(EventId);
#if ( (DEM_NUM_FAILURECYCLES > 0U) && \
      (DEM_EVENTFAILURECOUNTER_BUFFER_SIZE > 0U) )
      uint8 FailureCounterBufferIdx = 0U;
#endif

      if (Dem_GbiEventFailureClassIdx(EventId) == DEM_NO_FAULT_CONFIRMATION)
      {
        /* fault confirmation is not configured for the event
         * set CDTC bit immediately */
        DEM_SET_EV_ST_MASK(EventId, DEM_DTCSTATUSBIT_CDTC);
      }

      /* --- store initial event entry information --- */

      (*EvMemEntryPtr)->EventId = EventId;
      (*EvMemEntryPtr)->OccCtr = 0U;
#if (DEM_NUM_FAILURECYCLES > 0U)
      (*EvMemEntryPtr)->EventFailureCycleCounter = 0U;
#if (DEM_EVENTFAILURECOUNTER_BUFFER_SIZE > 0U)
      /* check if failure counter for the event is stored in buffer */
      if (Dem_SearchForFailureCounterBufferEntry(
            EventId, &FailureCounterBufferIdx))
      {
        /* store the failure counter value for the event from buffer */
        (*EvMemEntryPtr)->EventFailureCycleCounter =
          Dem_EventFailureCycleCounterBuffer[FailureCounterBufferIdx].
            FailureCycleCounter;
        /* clear the entry from failure counter buffer */
        Dem_EventFailureCycleCounterBuffer[FailureCounterBufferIdx].
          EventId = DEM_EVENT_ID_INVALID;
      }
#endif
#endif /* (DEM_NUM_FAILURECYCLES > 0U) */

      if (width > 0U)
      {
        (*EvMemEntryPtr)->EntryDataPos = *(Dem_EntryDataFreePos[originIdx]);

        /* recalculate free position of event memory entry data */
        *(Dem_EntryDataFreePos[originIdx]) += width;
      }
    }
  }
  else /* entry exists */
  {
    /* check if DTCRecordUpdate is locked */
    if (Dem_EvIdOfRecordUpdateDisabledDTC == EventId)
    {
      /* do not update the event memory entry */
      allocationResult = DEM_EVENTENTRYALLOC_INVALID;
    }
    else
    {
      allocationResult = DEM_EVENTENTRYALLOC_EXISTS;
    }
  }

  DBG_DEM_FINDORALLOCATEEVENTENTRY_EXIT(allocationResult, EventId,
    EvMemEntryPtr, EvMemIdxPtr, ReplacedEventIdPtr, EventStatusChangedMsgPtr);
  return allocationResult;
}

STATIC FUNC(Dem_EventEntryAllocResultType, DEM_CODE) Dem_ReplaceEventEntry(
  const Dem_EventIdType EventId,
  const uint8           originIdx,
  /* Deviation MISRA-1 */
  CONSTP2VAR(Dem_EventMemoryEntryPtrType, AUTOMATIC, AUTOMATIC) EvMemEntryPtr,
  CONSTP2VAR(Dem_SizeEvMemEntryType, AUTOMATIC, AUTOMATIC)      EvMemIdxPtr,
  /* Deviation MISRA-1 */
  CONSTP2VAR(Dem_EventIdType, AUTOMATIC, AUTOMATIC) ReplacedEventIdPtr,
  const Dem_EventStatusChangedMsgPtrType            EventStatusChangedMsgPtr)
{
  Dem_EventEntryAllocResultType allocationResult =
    DEM_EVENTENTRYALLOC_INVALID;
#if (DEM_USE_EVENT_DISPLACEMENT == STD_ON)
  boolean replaceableEntryFound = FALSE;
#endif

  DBG_DEM_REPLACEEVENTENTRY_ENTRY(EventId, originIdx, EvMemEntryPtr,
    EvMemIdxPtr, ReplacedEventIdPtr, EventStatusChangedMsgPtr);

#if (DEM_USE_EVENT_DISPLACEMENT == STD_ON)
  /* find event memory entry to replace */
  replaceableEntryFound =
    Dem_SearchForEntryToReplace(originIdx, EventId, EvMemEntryPtr, EvMemIdxPtr);

  /* !LINKSTO Dem408,1
   * clear existing event memory entry */
  if (replaceableEntryFound)
  {
    Dem_EventIdType ReplacedEventId = (*EvMemEntryPtr)->EventId;

    if (Dem_EvIdOfRecordUpdateDisabledDTC != ReplacedEventId)
    {
#if ( (DEM_USE_CB_TRIG_ON_EVST == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) )
      Dem_DTCStatusMaskType ReplacedDTCStatusMask =
        DEM_DTC_STATUS_MASKS[ReplacedEventId];
#endif

      Dem_ClearEventEntry(*EvMemEntryPtr);

      /* !LINKSTO Dem409,1
       * clear confirmed and TestFailedSinceLastClear (only if allowed),
       * but NOT warning indicator request bit */
#if (DEM_STATUS_BIT_HANDLING_TESTFAILEDSINCELASTCLEAR == \
      DEM_STATUS_BIT_AGING_AND_DISPLACEMENT)
      DEM_CLR_EV_ST_MASK(ReplacedEventId,
                         DEM_DTCSTATUSBIT_CDTC |
                         DEM_DTCSTATUSBIT_TFSLC);
#else
      DEM_CLR_EV_ST_MASK(ReplacedEventId, DEM_DTCSTATUSBIT_CDTC);
#endif

#if ( (DEM_USE_CB_TRIG_ON_EVST == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) )
      /* notify application that event status has changed */
      EventStatusChangedMsgPtr->EventId = ReplacedEventId;
      EventStatusChangedMsgPtr->OldStatusMask = ReplacedDTCStatusMask;
      EventStatusChangedMsgPtr->NewStatusMask = DEM_DTC_STATUS_MASKS[ReplacedEventId];
#else
      TS_PARAM_UNUSED(EventStatusChangedMsgPtr);
#endif

      /* return the id of the replaced event */
      *ReplacedEventIdPtr = ReplacedEventId;
      /* a replaceable entry has been found */
      allocationResult = DEM_EVENTENTRYALLOC_REPLACED;
    } /* else: DTCRecordUpdate is locked; DEM_EVENTENTRYALLOC_INVALID */
  } /* else: no replaceable entry has been found; DEM_EVENTENTRYALLOC_INVALID */
#else
  TS_PARAM_UNUSED(EventId);
  TS_PARAM_UNUSED(EvMemEntryPtr);
  TS_PARAM_UNUSED(EvMemIdxPtr);
  TS_PARAM_UNUSED(ReplacedEventIdPtr);
  TS_PARAM_UNUSED(EventStatusChangedMsgPtr);
#endif /* DEM_USE_EVENT_DISPLACEMENT == STD_ON */

  /* if memory overflow indication bit is not set, set it now and call
   * callback functions for events in the origin */
  if (!DEM_IS_OVFIND_SET(originIdx))
  {
    /* set event memory overflow indication bit */
    DEM_ATOMIC_SET_BIT_8(DEM_OVFIND_FLAGS, originIdx);

#if ( (DEM_USE_CB_TRIG_ON_EVDAT == STD_ON) && \
      (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON) )
    /* check if Event data change callback function needs to be called
     * for events in the origin and invoke callback function */
    Dem_CbTriggerOnOvfIndSet(originIdx);
#endif
  }

  DBG_DEM_REPLACEEVENTENTRY_EXIT(allocationResult, EventId, originIdx,
    EvMemEntryPtr, EvMemIdxPtr, ReplacedEventIdPtr, EventStatusChangedMsgPtr);
  return allocationResult;
}

#if (DEM_NUM_FFSEGS > 0U)
STATIC FUNC(boolean, DEM_CODE) Dem_ProcessEventEntryFFData(
  const Dem_EventIdType                  EventId,
  const Dem_EventMemoryEntryPtrConstType EvMemEntryPtr)
{
  boolean triggerOnEventData = FALSE;

  /* get freeze frame class layout */
  CONSTP2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) FFClass =
    &Dem_FFClass[Dem_GbiFFClassIdx(EventId)];

  DBG_DEM_PROCESSEVENTENTRYFFDATA_ENTRY(EventId, EvMemEntryPtr);

  /* check if a FF class is assigned to event */
  if (FFClass->NumFFSegs > 0U)
  {
    const Dem_FFIdxType MaxNumFF = Dem_GbiMaxNumFFRecs(EventId);

    /* if MaxNumFF = 1, freeze frame record will not be
     * updated when the event re-occurs (note of Dem585) */
    if ((MaxNumFF > 1U) || (EvMemEntryPtr->OccCtr == 1U))
    {
      /* get index where to place the new FF */
      /* FFIndex is obtained by subtracting one from DEM_NUMFF() since
       * OccCtr is incremented before.
       * if OccCtr > MaxNumFF, the most recent freeze frame record will be
       * replaced */
      const Dem_FFIdxType FFIndex = DEM_NUMFF(EvMemEntryPtr, MaxNumFF) - 1U;

#if (DEM_MAX_NUMBER_PRESTORED_FF > 0U)
      const Dem_EventIdType PFFIndex = Dem_GetPFFIndex(EventId);
#endif

      /* pointer to FF data - for writing */
      const Dem_EntryDataPtrType FFEntryData =
        Dem_FFEntryData(EvMemEntryPtr, FFClass, FFIndex);

#if (DEM_MAX_NUMBER_PRESTORED_FF > 0U)
      /* check if prestored freeze frame for this event exists */
      if ( (Dem_GbiEnablePrestorage(EventId) != FALSE) &&
           DEM_IS_BIT_SET_IN_ARRAY(Dem_PFFEntryValid, PFFIndex) )
      {
        /* get destination pointer to prestore freeze frame */
        const Dem_EntryDataPtrConstType PFFEntryData =
          Dem_GetPFFEntryDataPtr(EventId);

        /* copy PFF to event memory */
        TS_MemCpy(FFEntryData, PFFEntryData, Dem_SizeOfFF(FFClass));

        /* mark prestored freeze frame as empty */
        DEM_CLR_BIT_IN_ARRAY(Dem_PFFEntryValid, PFFIndex);
      }
      else
#endif
      {
        Dem_StoreFF(
#if (DEM_DEV_ERROR_DETECT == STD_ON)
          DEM_SID_MainFunction,
#endif /* DEM_DEV_ERROR_DETECT */
          FFEntryData,
          FFClass);
      }

#if (DEM_USE_CB_TRIG_ON_EVDAT == STD_ON)
      triggerOnEventData = TRUE;
#endif
    }
  }

  DBG_DEM_PROCESSEVENTENTRYFFDATA_EXIT(
    triggerOnEventData, EventId, EvMemEntryPtr);
  return triggerOnEventData;
}
#endif /* (DEM_NUM_FFSEGS > 0U) */

#if (DEM_NUM_EDSEGS > 0U)
STATIC FUNC(boolean, DEM_CODE) Dem_ProcessEventEntryEData(
  const Dem_EventIdType                  EventId,
  const Dem_EventMemoryEntryPtrConstType EvMemEntryPtr,
  Dem_EventEntryAllocResultType          eventEntryAllocResult)
{
  boolean triggerOnEventData = FALSE;

  /* get extended data class layout */
  CONSTP2CONST(Dem_EDClassType, AUTOMATIC, DEM_CONST) EDClass =
    &Dem_EDClass[Dem_GbiEDClassIdx(EventId)];

  DBG_DEM_PROCESSEVENTENTRYEDATA_ENTRY(
    EventId, EvMemEntryPtr, eventEntryAllocResult);

  /* check if an ED class is assigned to event */
  if (EDClass->NumEDSegs > 0U)
  {
    boolean EntryExists = FALSE;

    /* pointer to ED data - for writing */
    const Dem_EntryDataPtrType EDEntryData = Dem_EDEntryData(EvMemEntryPtr);

    /* initialize ED entry data area at new (or displaced) entry only */
    if ( (eventEntryAllocResult == DEM_EVENTENTRYALLOC_ALLOCATED) ||
         (eventEntryAllocResult == DEM_EVENTENTRYALLOC_REPLACED) )
    {
      Dem_EntryDataType index;

      for (index = 0U; index < Dem_SizeOfED(EDClass); ++index)
      {
        EDEntryData[index] = 0U;
      }
    }
    else /* eventEntryAllocResult == INVALID or EXISTS */
    {
      EntryExists = TRUE;
    }

    /* update extended data */
#if (DEM_USE_CB_TRIG_ON_EVDAT == STD_ON)
    if (Dem_StoreED(EDEntryData, EDClass, EntryExists) == TRUE)
    {
      triggerOnEventData = TRUE;
    }
#else
    (void)Dem_StoreED(EDEntryData, EDClass, EntryExists);
#endif
  }

  DBG_DEM_PROCESSEVENTENTRYEDATA_EXIT(
    triggerOnEventData, EventId, EvMemEntryPtr, eventEntryAllocResult);
  return triggerOnEventData;
}
#endif /* (DEM_NUM_EDSEGS > 0U) */

#if (DEM_NUM_FFSEGS > 0U)
STATIC FUNC(void, DEM_CODE) Dem_StoreFF(
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  uint8                                               ServiceId,
#endif /* DEM_DEV_ERROR_DETECT */
  const Dem_EntryDataPtrType                          FFEntryData,
  CONSTP2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) FFClass)
{
  Dem_FFSegIdxType SegIndex;
  Dem_FFSegIdxType FFSegIdx;
  P2CONST(Dem_FFSegmentType, AUTOMATIC, DEM_CONST) FFSegment;
  Std_ReturnType dataPresent;
  Dem_DataElementIdxType DataElementIndex;
  Dem_DataElementIdxType DataElementIdx;
  Dem_FFStartByteType FFStartByte;
  Dem_DataElementOffsetType FFDataElemOffset;

  DBG_DEM_STOREFF_ENTRY(FFEntryData, FFClass);

  /* get data values to all data Ids of the freeze frame class */
  for (SegIndex = 0U; SegIndex < FFClass->NumFFSegs; ++SegIndex)
  {
    FFSegIdx = FFClass->FFSegIdx[SegIndex];
    FFSegment = &Dem_FFSegment[FFSegIdx];
    FFStartByte = FFClass->StartByte[SegIndex];

    /* add all data elements of the FF segment */
    for (DataElementIndex = 0U;
         DataElementIndex < FFSegment->NumFFDataElements; ++DataElementIndex)
    {
      FFDataElemOffset = FFSegment->DataElementOffset[DataElementIndex];
      DataElementIdx = FFSegment->DataElementIdx[DataElementIndex];

      /* Invoke C/RTE callback function to get data value */
      dataPresent = Dem_DataElement[DataElementIdx].Callback(
                    &FFEntryData[FFStartByte + FFDataElemOffset]);

      if (dataPresent != E_OK)
      {
        Dem_SizeEntryDataType index;

        const Dem_SizeEntryDataType StartIndex =
          (Dem_SizeEntryDataType)FFStartByte + FFDataElemOffset;

        const Dem_SizeEntryDataType StopIndex  =
          StartIndex + Dem_DataElement[DataElementIdx].Size;

        /* fill FF segment with padding values */
        for (index = StartIndex; index < StopIndex; ++index)
        {
          FFEntryData[index] = DEM_DATA_PADDING_VALUE;
        }

#if (DEM_DEV_ERROR_DETECT == STD_ON)
      /* report non-available data for FFS */
      DEM_REPORT_ERROR(ServiceId, DEM_E_NODATAAVAILABLE);
#endif /* DEM_DEV_ERROR_DETECT */
      }
    }
  }

  DBG_DEM_STOREFF_EXIT(FFEntryData, FFClass);
}
#endif /* (DEM_NUM_FFSEGS > 0U) */

#if (DEM_NUM_EDSEGS > 0U)
STATIC FUNC(boolean, DEM_CODE) Dem_StoreED(
  const Dem_EntryDataPtrType                          EDEntryData,
  CONSTP2CONST(Dem_EDClassType, AUTOMATIC, DEM_CONST) EDClass,
  boolean                                             EntryExists)
{
  Dem_EDSegIdxType SegIndex;
  Dem_EDSegIdxType EDSegIdx;
  boolean result = FALSE;
  P2CONST(Dem_EDSegmentType, AUTOMATIC, DEM_CONST) EDSegment;
  Dem_DataElementOffsetType EDDataElemOffset;
  Dem_EDStartByteType EDStartByte;

  DBG_DEM_STOREED_ENTRY(EDEntryData, EDClass, EntryExists);

  /* get data values to all numbers of the extended data class */
  for (SegIndex = 0U; SegIndex < EDClass->NumEDSegs; ++SegIndex)
  {
    EDSegIdx = EDClass->EDSegIdx[SegIndex];
    EDSegment = &Dem_EDSegment[EDSegIdx];
    EDStartByte = EDClass->StartByte[SegIndex];

    /* check if ED record update is enabled */
    if ((EntryExists == FALSE) || (EDSegment->Update == TRUE))
    {
      Std_ReturnType dataPresent = E_NOT_OK;
      Dem_DataElementIdxType DataElementIndex;
      Dem_DataElementIdxType DataElementIdx;

      /* add all data elements of the ED segment */
      for (DataElementIndex = 0U;
           DataElementIndex < EDSegment->NumEDDataElements; ++DataElementIndex)
      {
        DataElementIdx = EDSegment->DataElementIdx[DataElementIndex];

#if (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON)
        if (DataElementIdx < DEM_NUM_EXT_CS_DATAELEMENTS)
#endif
        {
          EDDataElemOffset = EDSegment->DataElementOffset[DataElementIndex];

          /* Invoke C/RTE callback function to get data value */
          dataPresent = Dem_DataElement[DataElementIdx].Callback(
                        &EDEntryData[EDStartByte + EDDataElemOffset]);

          if (dataPresent != E_OK)
          {
            Dem_SizeEntryDataType index;

            Dem_SizeEntryDataType StartIndex =
              (Dem_SizeEntryDataType)EDStartByte + EDDataElemOffset;

            Dem_SizeEntryDataType StopIndex  =
              StartIndex + Dem_DataElement[DataElementIdx].Size;

            /* fill data element with padding values */
            for (index = StartIndex; index < StopIndex; ++index)
            {
              EDEntryData[index] = DEM_DATA_PADDING_VALUE;
            }

#if (DEM_DEV_ERROR_DETECT == STD_ON)
            /* report non-available data for EDS */
            DEM_REPORT_ERROR(DEM_SID_MainFunction, DEM_E_NODATAAVAILABLE);
#endif /* DEM_DEV_ERROR_DETECT */
          }
        }
      }

      /* ED record was stored/updated in event memory */
      result = TRUE;
    }
  }

  DBG_DEM_STOREED_EXIT(result, EDEntryData, EDClass, EntryExists);
  return result;
}

STATIC FUNC(void, DEM_CODE) Dem_AssembleExtendedData(
  CONSTP2CONST(Dem_EDClassType, AUTOMATIC, DEM_CONST) EDClass,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)              DestBuffer,
  const Dem_EventMemoryEntryPtrConstType              EvMemEntry)
{
  Dem_EDSegIdxType SegIndex;
  P2CONST(Dem_EDSegmentType, AUTOMATIC, DEM_CONST) EDSegment;
  Dem_EDStartByteType EDStartByte;
  uint8 EDSegSize = 0U;

  DBG_DEM_ASSEMBLEEXTENDEDDATA_ENTRY(EDClass, DestBuffer, EvMemEntry);

  for (SegIndex = 0U; SegIndex < EDClass->NumEDSegs; ++SegIndex)
  {
    EDSegment = &Dem_EDSegment[EDClass->EDSegIdx[SegIndex]];
    EDStartByte = EDClass->StartByte[SegIndex];

    /* next record of ED class should be assembled consecutive to the
     * previous record */
    /* the size returned shall be used for getting position of DestBuffer
     * for copying the next record */
    EDSegSize += Dem_AssembleExtendedDataSeg(
      EDSegment, EDStartByte, &DestBuffer[EDSegSize], EvMemEntry);
  }

  DBG_DEM_ASSEMBLEEXTENDEDDATA_EXIT(EDClass, DestBuffer, EvMemEntry);
}

#endif /* (DEM_NUM_EDSEGS > 0U) */

STATIC FUNC(boolean, DEM_CODE) Dem_SearchForEmptyEntry(
  const uint8                                                 OriginIdx,
  CONSTP2VAR(Dem_EventMemoryEntryPtrType, AUTOMATIC, DEM_VAR) FoundEntry,
  CONSTP2VAR(Dem_SizeEvMemEntryType, AUTOMATIC, AUTOMATIC)    FoundEntryIdx )
{
  boolean result = FALSE;

  const Dem_SizeEvMemEntryType sizeEventMem = Dem_SizeEventMem[OriginIdx];

  Dem_SizeEvMemEntryType entryIdx;
  Dem_EventMemoryEntryPtrType EvMemEntry = Dem_EventMem[OriginIdx];

  DBG_DEM_SEARCHFOREMPTYENTRY_ENTRY(OriginIdx, FoundEntry, FoundEntryIdx);

  /* search for empty entry in event memory */
  /* stop if all entries checked or the first empty entry was found */
  for (entryIdx = 0U; entryIdx < sizeEventMem; ++entryIdx)
  {
    if (EvMemEntry[entryIdx].EventId == (Dem_EventIdType)DEM_EVENT_ID_INVALID)
    {
      break;
    }

  }

  if (entryIdx < sizeEventMem)
  {
    *FoundEntryIdx = entryIdx;
    *FoundEntry = &EvMemEntry[entryIdx];

    result = TRUE;
  }

  DBG_DEM_SEARCHFOREMPTYENTRY_EXIT(
    result, OriginIdx, FoundEntry, FoundEntryIdx);
  return result;
}

#if (DEM_USE_EVENT_DISPLACEMENT == STD_ON)
STATIC FUNC(boolean, DEM_CODE) Dem_SearchForEntryToReplace(
  uint8                                                         OriginIdx,
  Dem_EventIdType                                               NewEventId,
  CONSTP2VAR(Dem_EventMemoryEntryPtrType, AUTOMATIC, AUTOMATIC) FoundEntry,
  CONSTP2VAR(Dem_SizeEvMemEntryType, AUTOMATIC, AUTOMATIC)      FoundEntryIdx)
{
  boolean result = FALSE;

  const Dem_SizeEvMemEntryType sizeEventMem = Dem_SizeEventMem[OriginIdx];
  const Dem_EventMemoryEntryPtrType EvMemEntry = Dem_EventMem[OriginIdx];

  Dem_SizeEvMemEntryType entryIdx;
  Dem_SizeEvMemEntryType bestEntryIdx = 0U;

  Dem_EventIdType currentEventId;
  Dem_EventIdType bestEventId;

  const Dem_PriorityType newEvtPrioVal = Dem_GbiPriority(NewEventId);

  Dem_PriorityType currentEvtPrioVal;
  /* initialize with highest allowed priority (smallest allowed value) */
  Dem_PriorityType bestPrioVal = newEvtPrioVal;

  DBG_DEM_SEARCHFORENTRYTOREPLACE_ENTRY(
    OriginIdx, NewEventId, FoundEntry, FoundEntryIdx);

  /* refer to figure 25 "Combined displacement criteria processing"
   * in SWS for the displacement algorithm of combined  criteria */
  for (entryIdx = 0U; entryIdx < sizeEventMem; ++entryIdx)
  {
    currentEventId = EvMemEntry[entryIdx].EventId;
    currentEvtPrioVal = Dem_GbiPriority(currentEventId);

    /* !LINKSTO Dem383,2
     * filter for valid event memory entries with lower or same priority than
     * new event and best entry, i.e. larger priority value */
    if ( (currentEventId != DEM_EVENT_ID_INVALID) &&
         (currentEvtPrioVal >= newEvtPrioVal) &&
         (currentEvtPrioVal >= bestPrioVal) )
    {
      /* entry with lower priority (larger value) than best entry
       * (and new event) */
      if (currentEvtPrioVal > bestPrioVal)
      {
        /* select entry with lower priority for displacement */
        bestPrioVal  = currentEvtPrioVal;
        bestEntryIdx = entryIdx;
        result = TRUE;
      }
      else /* currentEvtPrioVal == bestPrioVal */
      {
        /* entry has same priority than best entry and new event */
        if (currentEvtPrioVal == newEvtPrioVal)
        {
          /* only a passive entry can be displaced, but not an active one */
          if ( (!DEM_IS_EV_ST_BIT_TF_SET(currentEventId)) &&
               ( (result == FALSE) ||
                 (EvMemEntry[entryIdx].OccOrder <
                    EvMemEntry[bestEntryIdx].OccOrder) ) )
          {
            /* select older passive entry with same priority than new event
             * prior to a newer entry with same priority than new event for
             * displacement */
            bestEntryIdx = entryIdx;
            result = TRUE;
          }
          /* else: 1) active entry of same priority than new event must not be
           *          displaced
           *       2) passive entry must not be displaced if older passive
           *          entry with same priority is present */
        }
        else /* entry with same priority than best entry, but lower than new event */
        {
          bestEventId = EvMemEntry[bestEntryIdx].EventId;

          if ( DEM_IS_EV_ST_BIT_TF_SET(bestEventId) &&
               (!DEM_IS_EV_ST_BIT_TF_SET(currentEventId)) )
          {
            /* select passive entry prior to an active entry with same
             * priority for displacement */
            bestEntryIdx = entryIdx;
          }
          else if (DEM_IS_EV_ST_BIT_TF_SET(bestEventId) ==
                   DEM_IS_EV_ST_BIT_TF_SET(currentEventId))
          {
            if (EvMemEntry[entryIdx].OccOrder <
                  EvMemEntry[bestEntryIdx].OccOrder)
            {
              /* select older entry prior to a newer entry with same priority
               * and same active/passive status for displacement */
              bestEntryIdx = entryIdx;
            }
            /* else: entry must not be displaced if older entry with same
             *       priority is present */
          }
          else /* entry is active, but best entry is passive */
          {
            /* active entry must not be displaced if passive entry with same
             * priority is present */
          }
        }
      }
    }
  }

  if (result == TRUE)
  {
    *FoundEntry = &EvMemEntry[bestEntryIdx];
    *FoundEntryIdx = bestEntryIdx;
  }

  DBG_DEM_SEARCHFORENTRYTOREPLACE_EXIT(
    result, OriginIdx, NewEventId, FoundEntry, FoundEntryIdx);
  return result;
}

STATIC FUNC(boolean, DEM_CODE) Dem_UpdateOccurrenceOrder(
  Dem_EventMemoryEntryPtrType UpdatedEvMemEntry)
{
  /* result value to support forced immediate write */
  boolean orderRearranged = DEM_NVM_NO_FORCE;
  /* flag to indicate whether Dem_MaxOccOrder needs to be incremented */
  boolean maxOccOrderIncrement = TRUE;

  const uint8 originIdx = Dem_GbiDTCOriginIdx(UpdatedEvMemEntry->EventId);
  const Dem_EventMemoryEntryPtrType EvMemEntry = Dem_EventMem[originIdx];

  Dem_SizeEvMemEntryType entryIdx;

  DBG_DEM_UPDATEOCCURRENCEORDER_ENTRY(UpdatedEvMemEntry);

  /* no need to increment Dem_MaxOccOrder if its value is 0 (starting value)
   * and no other valid events are present in the memory, so that the value of
   * OccOrder starts from 0 and is set for first event memory entry */
  if (Dem_MaxOccOrder[originIdx] == 0U)
  {
    maxOccOrderIncrement = FALSE;

    for (entryIdx = 0U; entryIdx < Dem_SizeEventMem[originIdx]; entryIdx++)
    {
      if ( (EvMemEntry[entryIdx].EventId != DEM_EVENT_ID_INVALID) &&
           (EvMemEntry[entryIdx].EventId != UpdatedEvMemEntry->EventId) )
      {
        maxOccOrderIncrement = TRUE;
        break;
      }
    }
  }

  /* OccOrder of reported event is the same than Dem_MaxOccOrder
   * since it was the newest event stored already
   * (OccOrder needs not to be incremented if it is the largest value already)
   * or the OccOrder of reported event is 0 (starting value)
   * but there was a newer event with larger occurrence order value */
  if ( (Dem_MaxOccOrder[originIdx] != UpdatedEvMemEntry->OccOrder) ||
       ((UpdatedEvMemEntry->OccOrder == 0U) && (maxOccOrderIncrement == TRUE))
     )
  {
    if (maxOccOrderIncrement == TRUE)
    {
      /* update the array which stores the largest value of occurrence order
       * in the event memory */
      Dem_MaxOccOrder[originIdx]++;
    }

    /* update the occurrence order of the event */
    UpdatedEvMemEntry->OccOrder = Dem_MaxOccOrder[originIdx];

    /* check whether the occurrence order exceeded the threshold */
    if (Dem_MaxOccOrder[originIdx] >= DEM_MAX_OCC_ORDER)
    {
      /* re-arrange the existing occurrence order */
      Dem_RearrangeOccurrenceOrder(originIdx);
      /* order rearranged, force immediate write if enabled */
      orderRearranged = DEM_NVM_FORCE;
    }
  }

  DBG_DEM_UPDATEOCCURRENCEORDER_EXIT(orderRearranged, UpdatedEvMemEntry);
  return orderRearranged;
}

STATIC FUNC(void, DEM_CODE) Dem_RearrangeOccurrenceOrder(
  const uint8 originIdx)
{
  const Dem_EventMemoryEntryPtrType EvMemEntry = Dem_EventMem[originIdx];

  Dem_SizeEvMemEntryType entryIdx;
  Dem_SizeEvMemEntryType foundEntryIdx = 0U;
  Dem_SizeEvMemEntryType validEntryIdx;
  Dem_SizeEvMemEntryType numValidEntries = 0U;

  Dem_OccOrderType nextOccOrder = 0U;
  Dem_OccOrderType nextMinOccOrder;

  DBG_DEM_REARRANGEOCCURRENCEORDER_ENTRY(originIdx);

  /* calculate the number of valid event entries in the memory */
  for (entryIdx = 0U; entryIdx < Dem_SizeEventMem[originIdx]; entryIdx++)
  {
    if (EvMemEntry[entryIdx].EventId != DEM_EVENT_ID_INVALID)
    {
      numValidEntries++;
    }
  }

  for (validEntryIdx = 0U; validEntryIdx < numValidEntries; validEntryIdx++)
  {
    /* initialize the current occurrence order with maximum possible value of
     * OccOrder */
    nextMinOccOrder = DEM_MAX_OCC_ORDER;

    /* find the valid entry with next lowest value of OccOrder */
    for (entryIdx = 0U; entryIdx < Dem_SizeEventMem[originIdx]; entryIdx++)
    {
      if ( (EvMemEntry[entryIdx].EventId != DEM_EVENT_ID_INVALID) &&
           (EvMemEntry[entryIdx].OccOrder >= nextOccOrder) &&
           (EvMemEntry[entryIdx].OccOrder <= nextMinOccOrder) )
      {
        nextMinOccOrder = EvMemEntry[entryIdx].OccOrder;
        foundEntryIdx = entryIdx;
      }
    }

    /* occurrence order value of next newer event is non-conscutive */
    if (EvMemEntry[foundEntryIdx].OccOrder > nextOccOrder)
    {
      /* re-arrange the OccOrder of entry with lowest value of OccOrder which
       * is not re-arranged previously */
      EvMemEntry[foundEntryIdx].OccOrder = nextOccOrder;

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
      /* 1) if EntryStatus is CLEAR_IMM never change it to sth. else
         2) if immediate storage is enabled for cleared events only
              --> target state CHANGED
         3) if immediate storage is enabled because of immediate events
              --> target state STORE_IMM */
      /* !LINKSTO Dem.ClearDTCBehavior.NonvolatileFinish, 1 */
      if (EvMemEntry[foundEntryIdx].EntryStatus != DEM_ENTRY_CLEAR_IMMEDIATELY)
      {
#if (DEM_IMMEDIATE_NV_STORAGE_TYPE == DEM_IMMEDIATE_CLEARED)
        EvMemEntry[foundEntryIdx].EntryStatus = DEM_ENTRY_CHANGED;
#else
        EvMemEntry[foundEntryIdx].EntryStatus = DEM_ENTRY_STORE_IMMEDIATELY;
#endif
      }
#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */
    }
    /* else: next occurrence order value is consecutive already */

    nextOccOrder++;
  }

  /* update the array which stores the largest value of occurrence order in
   * a memory */
  Dem_MaxOccOrder[originIdx] = (Dem_OccOrderType)numValidEntries - 1U;

  DBG_DEM_REARRANGEOCCURRENCEORDER_EXIT(originIdx);
}

STATIC FUNC(void, DEM_CODE) Dem_InitMaxOccOrder(void)
{
  uint8 originIdx;

#if (DEM_USE_PERMANENT_STORAGE == STD_ON)
  Dem_EventMemoryEntryPtrType EvMemEntry;
  Dem_SizeEvMemEntryType entryIdx;
#endif

  DBG_DEM_INITMAXOCCORDER_ENTRY();

  for (originIdx = 0U; originIdx < DEM_MAXNUM_ORIGINS; originIdx++)
  {
    /* initialize the array which stores the largest value of occurrence order
     * per event memory */
    Dem_MaxOccOrder[originIdx] = 0U;

#if (DEM_USE_PERMANENT_STORAGE == STD_ON)
    EvMemEntry = Dem_EventMem[originIdx];

    for (entryIdx = 0U; entryIdx < Dem_SizeEventMem[originIdx]; entryIdx++)
    {
      /* update largest value of occurrence order for the related event memory
       * kind, with highest valid occurrence order found */
      if ( (EvMemEntry[entryIdx].EventId != DEM_EVENT_ID_INVALID) &&
           (EvMemEntry[entryIdx].OccOrder > Dem_MaxOccOrder[originIdx]) )
      {
        Dem_MaxOccOrder[originIdx] = EvMemEntry[entryIdx].OccOrder;
      }
    }
#endif
  }

  DBG_DEM_INITMAXOCCORDER_EXIT();
}
#endif /* DEM_USE_EVENT_DISPLACEMENT == STD_ON */

#if (DEM_NUM_FAILURECYCLES > 0U)
STATIC FUNC(void, DEM_CODE) Dem_ProcessFaultConfirmation(void)
{
  uint8_least originIdx;
  Dem_SizeEvMemEntryType entry;
  Dem_EventIdType EventId;

  DBG_DEM_PROCESSFAULTCONFIRMATION_ENTRY();

  for (originIdx = 0U; originIdx < (uint8)DEM_MAXNUM_ORIGINS; ++originIdx)
  {
    for (entry = 0U; entry < Dem_SizeEventMem[originIdx]; ++entry)
    {
      EventId = Dem_EventMem[originIdx][entry].EventId;

      if (EventId != DEM_EVENT_ID_INVALID)
      {
        uint8 EventFailureClassIdx = Dem_GbiEventFailureClassIdx(EventId);
#if ( (DEM_USE_CB_TRIG_ON_EVST == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) )
        Dem_DTCStatusMaskType OldDTCStatusMask = DEM_DTC_STATUS_MASKS[EventId];
#endif

        /* for unconfirmed DTC with fault confirmation configured */
        if ( (EventFailureClassIdx != DEM_NO_FAULT_CONFIRMATION) &&
             (!DEM_IS_EV_ST_BIT_CDTC_SET(EventId))
           )
        {
          /* if failure counter reached threshold value */
          if (Dem_EventMem[originIdx][entry].EventFailureCycleCounter ==
              Dem_EventFailureCycleCfg[EventFailureClassIdx].
                EventFailureCycleCounterThreshold)
          {
            /* set confirmedDTC bit */
            DEM_ATOMIC_SET_EV_ST_MASK(EventId, DEM_DTCSTATUSBIT_CDTC);

#if ( (DEM_USE_CB_TRIG_ON_EVST == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) )
          /* notify application as CDTC-bit is changed */
            Dem_CbTriggerOnEventStatus(
              EventId,
              OldDTCStatusMask,
              DEM_DTC_STATUS_MASKS[EventId]);
#endif
          }
        }
      }
    }
  }

  DBG_DEM_PROCESSFAULTCONFIRMATION_EXIT();
}

STATIC FUNC(void, DEM_CODE) Dem_ProcessFailureCounterReset(
  const Dem_EventIdType          EventId,
  const Dem_OperationCycleIdType OperationCycleId)
{
  const uint8 EventFailureClassIdx = Dem_GbiEventFailureClassIdx(EventId);
  Dem_EventMemoryEntryPtrType EvMemEntry;
  Dem_SizeEvMemEntryType EvMemEntryIdx;
#if (DEM_EVENTFAILURECOUNTER_BUFFER_SIZE > 0U)
  uint8 FailureCounterBufferIdx = 0U;
#endif

  DBG_DEM_PROCESSFAILURECOUNTERRESET_ENTRY(EventId, OperationCycleId);

  /* for events with fault confirmation configured */
  if (EventFailureClassIdx != DEM_NO_FAULT_CONFIRMATION)
  {
    /* only for events of this failure cycle */
    if (Dem_EventFailureCycleCfg[EventFailureClassIdx].
          EventFailureCycleIdx == OperationCycleId)
    {
      /* !LINKSTO Dem.FaultConfirmation.EventFailureCounterReset,1
       * unconfirmed DTC, TESTED and NOT FAILED this failure cycle */
      if ( ( (!DEM_IS_EV_ST_BIT_CDTC_SET(EventId)) &&
             (!DEM_IS_EV_ST_BIT_TNCTOC_SET(EventId)) ) &&
           (!DEM_IS_EV_ST_BIT_TFTOC_SET(EventId))
         )
      {
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
        Dem_NvMGatePrepStatusType NvMGateStatus;
        const uint8 OriginIdx = Dem_GbiDTCOriginIdx(EventId);

        /* try to lock gate entry */
        NvMGateStatus = Dem_BeginPrepareGateEntry(OriginIdx);
#endif
        /*
         * ENTER critical section to protect the event memory entry
         *       call-context: Rte (Task)
         */
        SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

        if (Dem_SearchForEntry(EventId, &EvMemEntry, &EvMemEntryIdx) == TRUE)
        {
          /* reset the failure counter in event memory entry */
          EvMemEntry->EventFailureCycleCounter = 0U;

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
          /* event memory entry has been updated:
           * it needs to be stored immediately if the immediate storage
           * is enabled for the updated event */
          Dem_CheckForImmediateEntryStorage(EventId,
                                            EvMemEntry,
                                            EvMemEntryIdx,
                                            DEM_NVM_NO_FORCE,
                                            &NvMGateStatus);
#endif
        }
#if (DEM_EVENTFAILURECOUNTER_BUFFER_SIZE > 0U)
        else if (Dem_SearchForFailureCounterBufferEntry(
                   EventId, &FailureCounterBufferIdx))
        {
          /* clear the failure counter buffer */
          Dem_EventFailureCycleCounterBuffer[FailureCounterBufferIdx].
            EventId = DEM_EVENT_ID_INVALID;
        }
        else
        {
          /* no failure counter, do nothing */
        }
#endif

        /*
         * LEAVE critical section
         */
        SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
        Dem_EndPrepareGateEntry(OriginIdx, NvMGateStatus);
#endif
      }
    }
  }

  DBG_DEM_PROCESSFAILURECOUNTERRESET_EXIT(EventId, OperationCycleId);
}

STATIC FUNC(void, DEM_CODE) Dem_UpdateFailureCounterCycleStart(
  const Dem_EventIdType          EventId,
  const Dem_OperationCycleIdType OperationCycleId)
{
  const uint8 EventFailureClassIdx = Dem_GbiEventFailureClassIdx(EventId);

  DBG_DEM_UPDATEFAILURECOUNTERCYCLESTART_ENTRY(EventId, OperationCycleId);

  /* for events with fault confirmation configured */
  if (EventFailureClassIdx != DEM_NO_FAULT_CONFIRMATION)
  {
    /* !LINKSTO Dem.FaultConfirmation.EventFailureCounterUpdateCycleStart,1
     * only for events with this failure cycle */
    if (Dem_EventFailureCycleCfg[EventFailureClassIdx].
          EventFailureCycleIdx == OperationCycleId)
    {
      /* unconfirmed DTC, test failed this operation cycle */
      if ( DEM_IS_EV_ST_BIT_TFTOC_SET(EventId) &&
           (!DEM_IS_EV_ST_BIT_CDTC_SET(EventId))
         )
      {
        /* increment the failure counter */
        Dem_IncrementFailureCounter(EventId);
      }
    }
  }

  DBG_DEM_UPDATEFAILURECOUNTERCYCLESTART_EXIT(EventId, OperationCycleId);
}

FUNC(void, DEM_CODE) Dem_IncrementFailureCounter(
  const Dem_EventIdType EventId)
{
  const uint8 EventFailureClassIdx = Dem_GbiEventFailureClassIdx(EventId);
  Dem_EventMemoryEntryPtrType EvMemEntry;
  Dem_SizeEvMemEntryType EvMemEntryIdx;
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
  const uint8 OriginIdx = Dem_GbiDTCOriginIdx(EventId);
  /* try to lock gate entry */
  Dem_NvMGatePrepStatusType NvMGateStatus = Dem_BeginPrepareGateEntry(OriginIdx);
#endif
#if (DEM_EVENTFAILURECOUNTER_BUFFER_SIZE > 0U)
  uint8 FailureCounterBufferIdx = 0U;
#endif

  DBG_DEM_INCREMENTFAILURECOUNTER_ENTRY(EventId);

  /*
   * ENTER critical section to protect the event memory entry
   * call-context: any
   */
  SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

  /* if event memory entry exists */
  if (Dem_SearchForEntry(EventId, &EvMemEntry, &EvMemEntryIdx) == TRUE)
  {
    /* increment the failure counter if threshold is not reached */
    if ( EvMemEntry->EventFailureCycleCounter <
         Dem_EventFailureCycleCfg[EventFailureClassIdx].
           EventFailureCycleCounterThreshold
       )
    {
      EvMemEntry->EventFailureCycleCounter++;

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
      /* event memory entry has been updated:
       * it needs to be stored immediately if the immediate storage
       * is enabled for the updated event */
      Dem_CheckForImmediateEntryStorage(EventId,
                                        EvMemEntry,
                                        EvMemEntryIdx,
                                        DEM_NVM_NO_FORCE,
                                        &NvMGateStatus);
#endif
    }
  }
#if (DEM_EVENTFAILURECOUNTER_BUFFER_SIZE > 0U)
  /* check if failure counter for the event is stored in buffer */
  else if (Dem_SearchForFailureCounterBufferEntry(
             EventId, &FailureCounterBufferIdx))
  {
    /* increment the failure counter in buffer if threshold is not reached */
    if ( Dem_EventFailureCycleCounterBuffer[FailureCounterBufferIdx].
           FailureCycleCounter <
         Dem_EventFailureCycleCfg[EventFailureClassIdx].
           EventFailureCycleCounterThreshold
       )
    {
      Dem_EventFailureCycleCounterBuffer[FailureCounterBufferIdx].
        FailureCycleCounter++;
    }
  }
  /* check if a failure counter entry can be created in buffer */
  else if (Dem_SearchForEmptyFailureCounterBufferEntry(&FailureCounterBufferIdx))
  {
    /* add a new entry for the event in failure counter buffer */
    Dem_EventFailureCycleCounterBuffer[FailureCounterBufferIdx].
      EventId = EventId;
    Dem_EventFailureCycleCounterBuffer[FailureCounterBufferIdx].
      FailureCycleCounter = 1U;
  }
  else
  {
    /* failure counter cannot be processed */
  }
#endif

  /*
   * LEAVE critical section
   */
  SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
  Dem_EndPrepareGateEntry(OriginIdx, NvMGateStatus);
#endif

  DBG_DEM_INCREMENTFAILURECOUNTER_EXIT(EventId);
}

#if (DEM_EVENTFAILURECOUNTER_BUFFER_SIZE > 0U)
STATIC FUNC(boolean, DEM_CODE) Dem_SearchForFailureCounterBufferEntry(
  const Dem_EventIdType                 EventId,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_VAR) FailureCounterBufferIdx)
{
  boolean result = FALSE;
  uint8 index;

  DBG_DEM_SEARCHFORFAILURECOUNTERBUFFERENTRY_ENTRY(
    EventId, FailureCounterBufferIdx);

  /* search for entry with given event id */
  for (index = 0U; index < DEM_EVENTFAILURECOUNTER_BUFFER_SIZE; ++index)
  {
    if (Dem_EventFailureCycleCounterBuffer[index].EventId == EventId)
    {
      break;
    }
  }

  if (index < DEM_EVENTFAILURECOUNTER_BUFFER_SIZE)
  {
    result = TRUE;
    *FailureCounterBufferIdx = index;
  }

  DBG_DEM_SEARCHFORFAILURECOUNTERBUFFERENTRY_EXIT(
    result, EventId, FailureCounterBufferIdx);
  return result;
}

FUNC(boolean, DEM_CODE) Dem_SearchForEmptyFailureCounterBufferEntry(
  CONSTP2VAR(uint8, AUTOMATIC, DEM_VAR) FailureCounterBufferIdx)
{
  boolean result = FALSE;
  uint8 index;

  DBG_DEM_SEARCHFOREMPTYFAILURECOUNTERBUFFERENTRY_ENTRY(
    FailureCounterBufferIdx);

  /* search for entry with given event id */
  for (index = 0U; index < DEM_EVENTFAILURECOUNTER_BUFFER_SIZE; ++index)
  {
    if (Dem_EventFailureCycleCounterBuffer[index].EventId ==
            DEM_EVENT_ID_INVALID)
    {
      break;
    }
  }

  if (index < DEM_EVENTFAILURECOUNTER_BUFFER_SIZE)
  {
    result = TRUE;
    *FailureCounterBufferIdx = index;
  }

  DBG_DEM_SEARCHFOREMPTYFAILURECOUNTERBUFFERENTRY_EXIT(
    result, FailureCounterBufferIdx);
  return result;
}
#endif /* (DEM_EVENTFAILURECOUNTER_BUFFER_SIZE > 0U) */
#endif /* (DEM_NUM_FAILURECYCLES > 0U) */

#if ( (DEM_USE_CB_TRIG_ON_EVDAT == STD_ON) && \
      (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON) )
STATIC FUNC(boolean, DEM_CODE) Dem_CheckIntDataElementUsage(
  const Dem_EventIdType        EventId,
  const Dem_DataElementIdxType DataElementIdx)
{
  /* get extended data class layout */
  CONSTP2CONST(Dem_EDClassType, AUTOMATIC, DEM_CONST) EDClass =
    &Dem_EDClass[Dem_GbiEDClassIdx(EventId)];

  Dem_EDSegIdxType SegIndex;
  P2CONST(Dem_EDSegmentType, AUTOMATIC, DEM_CONST) EDSegment;
  Dem_DataElementIdxType DataElementIndex;
  boolean EventMemIntDataElementMapFound = FALSE;

  DBG_DEM_CHECKINTDATAELEMENTUSAGE_ENTRY(EventId, DataElementIdx);

  for (SegIndex = 0U;
       ((SegIndex < EDClass->NumEDSegs) &&
        (FALSE == EventMemIntDataElementMapFound));
       ++SegIndex)
  {
    EDSegment = &Dem_EDSegment[EDClass->EDSegIdx[SegIndex]];

    for (DataElementIndex = 0U;
         ((DataElementIndex < EDSegment->NumEDDataElements) &&
          (FALSE == EventMemIntDataElementMapFound));
         ++DataElementIndex)
    {
      if (EDSegment->DataElementIdx[DataElementIndex] == DataElementIdx)
      {
        EventMemIntDataElementMapFound = TRUE;
      }
    }
  }

  DBG_DEM_CHECKINTDATAELEMENTUSAGE_EXIT(
    EventMemIntDataElementMapFound, EventId, DataElementIdx);
  return EventMemIntDataElementMapFound;
}

STATIC FUNC(void, DEM_CODE) Dem_CbTriggerOnOvfIndSet(const uint8 OriginIdx)
{
  const Dem_SizeEvMemEntryType sizeEventMem = Dem_SizeEventMem[OriginIdx];

  Dem_SizeEvMemEntryType index;
  Dem_EventMemoryEntryPtrType EvMemEntry = Dem_EventMem[OriginIdx];

  DBG_DEM_CBTRIGGERONOVFINDSET_ENTRY(OriginIdx);

  for (index = 0U; index < sizeEventMem; ++index)
  {
    const Dem_EventIdType EventId = EvMemEntry[index].EventId;

    if (EventId != (Dem_EventIdType)DEM_EVENT_ID_INVALID)
    {
      if (Dem_CheckIntDataElementUsage(EventId, DEM_INT_VAL_IDX_OVFIND))
      {
        /* notify application that event data has changed */
        Dem_CbTriggerOnEventData(EventId);
      }
    }
  }

  DBG_DEM_CBTRIGGERONOVFINDSET_EXIT(OriginIdx);
}
#endif /* (DEM_USE_CB_TRIG_ON_EVDAT == STD_ON) &&
          (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON) */

#if (DEM_NUM_INDICATOR_LINKS > 0U)
STATIC FUNC(void, DEM_CODE) Dem_ProcessHealing(
  Dem_OperationCycleIdType OperationCycleId)
{
  Dem_IndicatorLnkIdxType LinkIdx;
  Dem_HealingCycleCounterInfoIdxType HealingCycleCounterInfoIdx;
  Dem_FailureCycleCounterInfoIdxType FailureCycleCounterInfoIdx;

  DBG_DEM_PROCESSHEALING_ENTRY(OperationCycleId);

  for (LinkIdx = 0U; LinkIdx < DEM_NUM_INDICATOR_LINKS; ++LinkIdx)
  {
    HealingCycleCounterInfoIdx =
      Dem_IndicatorLink[LinkIdx].HealingCycleCounterInfoIdx;
    FailureCycleCounterInfoIdx =
      Dem_IndicatorLink[LinkIdx].FailureCycleCounterInfoIdx;

    /* Process only links where Indicator healing cycle
     * equals to current processed operation cycle */
    if (Dem_HealingCycleCounterInfo[HealingCycleCounterInfoIdx].OperationCycleRef ==
         OperationCycleId)
    {
      Dem_ProcessHealingCycleCounter(LinkIdx);
    }

    /* Process only links where Indicator failure cycle
     * equals to current processed operation cycle */
    if (Dem_FailureCycleCounterInfo[FailureCycleCounterInfoIdx].OperationCycleRef ==
         OperationCycleId)
    {
      Dem_ProcessFailureCycleCounter(LinkIdx);
    }
  }

  DBG_DEM_PROCESSHEALING_EXIT(OperationCycleId);
}

STATIC FUNC(void, DEM_CODE) Dem_ProcessHealingCycleCounter(
  const Dem_IndicatorLnkIdxType IndicatorLinkIdx)
{
  const Dem_EventIdType EventId = Dem_IndicatorLink[IndicatorLinkIdx].EventId;

  DBG_DEM_PROCESSHEALINGCYCLECOUNTER_ENTRY(IndicatorLinkIdx);

  if ( ( (!DEM_IS_EV_ST_BIT_TF_SET(EventId)) &&
         (!DEM_IS_EV_ST_BIT_TNCTOC_SET(EventId)) ) &&
       (!DEM_IS_EV_ST_BIT_TFTOC_SET(EventId))
     )
  {
    const Dem_CounterDataIdxType CounterDataIdx =
      Dem_IndicatorLink[IndicatorLinkIdx].CounterDataIdx;
    const Dem_HealingCycleCounterInfoIdxType HealingCycleCounterInfoIdx =
      Dem_IndicatorLink[IndicatorLinkIdx].HealingCycleCounterInfoIdx;

    Dem_IndicatorCounterDataRoleType IndicatorCounterDataRole =
      (DEM_IS_BIT_SET_IN_ARRAY(DEM_INDICATOR_CYC_COUNTER_ROLE, CounterDataIdx) ?
       DEM_INDICATORCOUNTER_ROLE_HEALING_CYCLE_COUNTER :
       DEM_INDICATORCOUNTER_ROLE_FAILURE_CYCLE_COUNTER);

    if (IndicatorCounterDataRole !=
         DEM_INDICATORCOUNTER_ROLE_HEALING_CYCLE_COUNTER)
    {
      IndicatorCounterDataRole = DEM_INDICATORCOUNTER_ROLE_HEALING_CYCLE_COUNTER;

      Dem_SetCycleCounterRole(CounterDataIdx, IndicatorCounterDataRole);
      DEM_INDICATOR_CYC_COUNTER[CounterDataIdx] = 0U;
    }

    if ( (DEM_INDICATOR_CYC_COUNTER[CounterDataIdx]) <
         (Dem_HealingCycleCounterInfo[HealingCycleCounterInfoIdx].Threshold)
       )
    {
      DEM_INDICATOR_CYC_COUNTER[CounterDataIdx]++;
    }

    if ( (DEM_INDICATOR_CYC_COUNTER[CounterDataIdx]) ==
         (Dem_HealingCycleCounterInfo[HealingCycleCounterInfoIdx].Threshold)
       )
    {
#if (DEM_NUM_BSWEVENT_INDICATOR_USED > 0U)
      if (Dem_GbiEventKind(EventId) == DEM_EVENT_KIND_BSW)
      {
        /* load index of event in BSW event WIR status flag array */
        const Dem_EventIdType BSWEventWIRStatusFlagsIndex =
          Dem_GetBSWEventWIRStatusFlagsIndex(EventId);

        /* given indicator is linked to a BSW event which then has to be
         * listed in Dem_BSWEventIndicatorUsed */
        DEM_PRECONDITION_ASSERT(
          (BSWEventWIRStatusFlagsIndex < DEM_NUM_BSWEVENT_INDICATOR_USED),
           DEM_INTERNAL_API_ID);

        /* clear event's WIR bit no matter is it set or not */
        DEM_ATOMIC_CLR_BIT_IN_ARRAY_8(Dem_BSWEventWIRStatusFlags,
                                      BSWEventWIRStatusFlagsIndex);
      }
#endif
      /* !LINKSTO dsn.Dem.IndicatorCycleCounterWIRStatus,1 */
      DEM_ATOMIC_CLR_BIT_IN_ARRAY_8(DEM_INDICATOR_CYC_COUNTER_WIR_STATUS,
                                    CounterDataIdx);

      if (DEM_IS_EV_ST_BIT_WIR_SET(EventId))
      {
        if (Dem_CheckWIROffCriteriaFulfilled(EventId))
        {
          Dem_EventIdType WIROnCriteriaFulfilledFlagsIdx =
            Dem_GetWIROnCriteriaFulfilledFlagsIdx(EventId);
#if ( (DEM_USE_CB_TRIG_ON_EVST == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) )
          const Dem_DTCStatusMaskType OldDTCStatusMask =
            DEM_DTC_STATUS_MASKS[EventId];
#endif

          /* atomic clear of the WIR status bit */
          DEM_ATOMIC_CLR_EV_ST_MASK(EventId, DEM_DTCSTATUSBIT_WIR);

#if ( (DEM_USE_CB_TRIG_ON_EVST == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) )
          /*  notify application as WIR-bit has changed */
          Dem_CbTriggerOnEventStatus(
            EventId, OldDTCStatusMask, DEM_DTC_STATUS_MASKS[EventId]);
#endif
          DEM_ATOMIC_CLR_BIT_IN_ARRAY_8(
            Dem_WIROnCriteriaFulfilledFlags, WIROnCriteriaFulfilledFlagsIdx);
        }
      }
    }
  }

  DBG_DEM_PROCESSHEALINGCYCLECOUNTER_EXIT(IndicatorLinkIdx);
}

STATIC FUNC(void, DEM_CODE) Dem_ProcessFailureCycleCounter(
  const Dem_IndicatorLnkIdxType IndicatorLinkIdx)
{
  const Dem_EventIdType EventId = Dem_IndicatorLink[IndicatorLinkIdx].EventId;
  const Dem_FailureCycleCounterInfoIdxType FailureCycleCounterInfoIdx =
    Dem_IndicatorLink[IndicatorLinkIdx].FailureCycleCounterInfoIdx;
  const Dem_OperationCycleIdType FailureCycleId = (Dem_OperationCycleIdType)
    Dem_FailureCycleCounterInfo[FailureCycleCounterInfoIdx].OperationCycleRef;
  const Dem_OperationCycleIdType EventOperationCycle =
    Dem_GbiOpCycleIdx(EventId);

  DBG_DEM_PROCESSFAILURECYCLECOUNTER_ENTRY(IndicatorLinkIdx);

  /* !LINKSTO dsn.Dem.ProcessFailureCycleCounter_ProcessCondition,1 */
  if ( ( (FailureCycleId == EventOperationCycle) &&
         DEM_IS_EV_ST_BIT_TFTOC_SET(EventId)
       ) ||
       ( (FailureCycleId != EventOperationCycle) &&
         DEM_IS_EV_ST_BIT_TF_SET(EventId)
       )
     )
  {
    const Dem_CounterDataIdxType CounterDataIdx =
      Dem_IndicatorLink[IndicatorLinkIdx].CounterDataIdx;

    Dem_IndicatorCounterDataRoleType IndicatorCounterDataRole =
      (DEM_IS_BIT_SET_IN_ARRAY(DEM_INDICATOR_CYC_COUNTER_ROLE, CounterDataIdx) ?
      DEM_INDICATORCOUNTER_ROLE_HEALING_CYCLE_COUNTER :
      DEM_INDICATORCOUNTER_ROLE_FAILURE_CYCLE_COUNTER);

    if (IndicatorCounterDataRole !=
         DEM_INDICATORCOUNTER_ROLE_FAILURE_CYCLE_COUNTER)
    {
      IndicatorCounterDataRole = DEM_INDICATORCOUNTER_ROLE_FAILURE_CYCLE_COUNTER;

      Dem_SetCycleCounterRole(CounterDataIdx, IndicatorCounterDataRole);
      DEM_INDICATOR_CYC_COUNTER[CounterDataIdx] = 0U;
    }

    if ( (DEM_INDICATOR_CYC_COUNTER[CounterDataIdx]) <
         (Dem_FailureCycleCounterInfo[FailureCycleCounterInfoIdx].Threshold)
       )
    {
      DEM_INDICATOR_CYC_COUNTER[CounterDataIdx]++;
    }

    if ( (DEM_INDICATOR_CYC_COUNTER[CounterDataIdx]) ==
         (Dem_FailureCycleCounterInfo[FailureCycleCounterInfoIdx].Threshold)
       )
    {
      Dem_EventIdType WIROnCriteriaFulfilledFlagsIdx =
        Dem_GetWIROnCriteriaFulfilledFlagsIdx(EventId);

      /* !LINKSTO dsn.Dem.IndicatorCycleCounterWIRStatus,1 */
      DEM_ATOMIC_SET_BIT_IN_ARRAY_8(DEM_INDICATOR_CYC_COUNTER_WIR_STATUS,
                                    CounterDataIdx);
      DEM_ATOMIC_SET_BIT_IN_ARRAY_8(
        Dem_WIROnCriteriaFulfilledFlags, WIROnCriteriaFulfilledFlagsIdx);
    }
  }

  DBG_DEM_PROCESSFAILURECYCLECOUNTER_EXIT(IndicatorLinkIdx);
}

STATIC FUNC(void, DEM_CODE) Dem_SetCycleCounterRole(
  const Dem_CounterDataIdxType CounterDataIdx,
  Dem_IndicatorCounterDataRoleType CounterDataRole)
{
  DBG_DEM_SETCYCLECOUNTERROLE_ENTRY(CounterDataIdx, CounterDataRole);

  if (CounterDataRole == DEM_INDICATORCOUNTER_ROLE_HEALING_CYCLE_COUNTER)
  {
    /* !LINKSTO dsn.Dem.IndicatorCycleCounterRole,1 */
    DEM_ATOMIC_SET_BIT_IN_ARRAY_8(DEM_INDICATOR_CYC_COUNTER_ROLE,
                                  CounterDataIdx);
  }
  else
  {
    /* !LINKSTO dsn.Dem.IndicatorCycleCounterRole,1 */
    DEM_ATOMIC_CLR_BIT_IN_ARRAY_8(DEM_INDICATOR_CYC_COUNTER_ROLE,
                                  CounterDataIdx);
  }

  DBG_DEM_SETCYCLECOUNTERROLE_EXIT(CounterDataIdx, CounterDataRole);
}

STATIC FUNC(boolean, DEM_CODE) Dem_CheckWIROffCriteriaFulfilled(
  const Dem_EventIdType EventId)
{
  Dem_IndicatorLnkIdxType LinkIdx;
  boolean result = TRUE;

  DBG_DEM_CHECKWIROFFCRITERIAFULFILLED_ENTRY(EventId);

  for (LinkIdx = 0U; LinkIdx < DEM_NUM_INDICATOR_LINKS; ++LinkIdx)
  {
    if (Dem_IndicatorLink[LinkIdx].EventId == EventId)
    {
      const Dem_CounterDataIdxType CounterDataIdx = Dem_IndicatorLink[LinkIdx].CounterDataIdx;

      if (DEM_IS_BIT_SET_IN_ARRAY(DEM_INDICATOR_CYC_COUNTER_WIR_STATUS,
                                  CounterDataIdx))
      {
        /* one CycleCounterWIR bit of the event is not cleared yet */
        result = FALSE;
      }
    }
  }

  DBG_DEM_CHECKWIROFFCRITERIAFULFILLED_EXIT(result, EventId);
  return result;
}
#endif /* (DEM_NUM_INDICATOR_LINKS > 0U) */

#if (DEM_NUM_BSWEVENT_INDICATOR_USED > 0U)
STATIC FUNC(void, DEM_CODE) Dem_ProcessBSWEventWIRBit(void)
{
  Dem_EventIdType index;

  DBG_DEM_PROCESSBSWEVENTWIRBIT_ENTRY();

  for (index = 0U; index < DEM_NUM_BSWEVENT_INDICATOR_USED; ++index)
  {
    Dem_EventIdType EvId = Dem_BSWEventIndicatorUsed[index];

    if (!DEM_IS_EV_ST_BIT_WIR_SET(EvId))
    {
      if (DEM_IS_BIT_SET_IN_ARRAY(Dem_BSWEventWIRStatusFlags, index))
      {
        Dem_EventIdType WIROnCriteriaFulfilledFlagsIdx =
          Dem_GetWIROnCriteriaFulfilledFlagsIdx(EvId);
#if ( (DEM_USE_CB_TRIG_ON_EVST == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) )
        const Dem_DTCStatusMaskType OldDTCStatusMask =
          DEM_DTC_STATUS_MASKS[EvId];
#endif

        DEM_ATOMIC_SET_EV_ST_MASK(EvId, DEM_DTCSTATUSBIT_WIR);
        /* reset the related Dem_BSWEventWIRStatusFlags bit */
        DEM_ATOMIC_CLR_BIT_IN_ARRAY_8(Dem_BSWEventWIRStatusFlags, index);

#if ( (DEM_USE_CB_TRIG_ON_EVST == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) )
        /*  notify application as WIR-bit has changed */
        Dem_CbTriggerOnEventStatus(
          EvId, OldDTCStatusMask, DEM_DTC_STATUS_MASKS[EvId]);
#endif
        DEM_ATOMIC_CLR_BIT_IN_ARRAY_8(Dem_WIROnCriteriaFulfilledFlags,
          WIROnCriteriaFulfilledFlagsIdx);
      }
    }
  }

  DBG_DEM_PROCESSBSWEVENTWIRBIT_EXIT();
}
#endif /* (DEM_NUM_BSWEVENT_INDICATOR_USED > 0U) */

#define DEM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[end of file]===========================================*/
