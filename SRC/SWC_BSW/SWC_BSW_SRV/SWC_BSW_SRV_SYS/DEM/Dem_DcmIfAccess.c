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
/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 16.7 (required)
 *    "A pointer parameter in a function prototype should be declared as
 *     pointer to const if the pointer is not used to modify the
 *     addressed object."
 *
 *    Reason:
 *    Pointer parameter is not modified in some configuration variants.
 */

/* This file contains definitions for interface functions provided by Dem to
 * the Dcm for clearing and control of DTC setting. */

/*==================[inclusions]============================================*/
/* !LINKSTO dsn.Dem.IncludeStr,1 */

#include <TSAutosar.h>                        /* EB specific standard types */
#include <Std_Types.h>                            /* AUTOSAR standard types */

/* !LINKSTO dsn.Dem.SchMUsage,1 */
#include <SchM_Dem.h>             /* for the locking of the exclusive areas */

#include <Dem_Int.h>             /* Module public and internal declarations */
#include <Dem_Trace.h>                        /* Dbg related macros for Dem */

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/** \brief Internal data type to define if event status and/or event data are
 ** modified. */
typedef struct
{
  boolean EvSt;        /**< Event status modified flag **/
#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
  boolean EvMemEntry;  /**< Event data modified flag **/
#endif
} Dem_EventModifiedType;

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

#define DEM_START_SEC_CODE
#include <MemMap.h>

/** \brief Process clearing of all events related to a DTC or DTC group
 **
 ** \param[in]  DTC
 ** \param[in]  DTCFormat
 ** \param[in]  DTCOrigin
 **
 ** \return Updated result of clear event process
 */
STATIC FUNC(Dem_ReturnClearDTCType, DEM_CODE) Dem_StartClearDTC(
  Dem_DTCType       DTC,
  Dem_DTCFormatType DTCFormat,
  Dem_DTCOriginType DTCOrigin);

#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
/** \brief Checks if there are earlier scheduled entries for clearing
 ** immediately
 **
 ** \param[in] OriginIdx
 **
 ** \return Boolean
 ** \retval TRUE  at least one event changed
 ** \retval FALSE no events changed
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(boolean, DEM_CODE) Dem_CheckForOldClearImmediateEntries(
  uint8 OriginIdx);
#endif

/** \brief Process clearing of all events related to a DTC or DTC group
 **
 ** \param[in]  DTC
 ** \param[in]  DTCOrigin
 ** \param[in]  DtcGroupRequest
 ** \param[in]  groupIdx
 ** \param[inout]  AnyEventModified
 **
 ** \return Updated result of clear event process
 */
STATIC FUNC(Dem_ReturnClearDTCType, DEM_CODE) Dem_ClearEvents(
  Dem_DTCType       DTC,
  Dem_DTCOriginType DTCOrigin,
  boolean           DtcGroupRequest,
  uint8             groupIdx,
  CONSTP2VAR(Dem_EventModifiedType, AUTOMATIC, AUTOMATIC) AnyEventModified);

/** \brief Reset status bits, clear an event entry and event related data
 ** (like healing counters)
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[in,out] NvMGateStatus
 **
 ** \return Dem_EventModifiedType changed notification structure
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Asynchronous}
 */
STATIC FUNC(Dem_EventModifiedType, DEM_CODE) Dem_ClearEvent(
  Dem_EventIdType              EventId,
  Dem_NvMGatePrepStatusPtrType NvMGateStatus);

/** \brief Function to convert an 24-bit DTC-group-value into the
 ** corresponding DTC-group-index
 **
 ** \param[in] DTCGroup
 ** \param[out] Idx
 **
 ** \return Boolean value indication success
 ** \retval TRUE  could find corresponding DTC-group-index
 ** \retval FALSE wrong DTC-group-value
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **
 */
STATIC FUNC(boolean, DEM_CODE) Dem_GetIdxOfDTCGroup(
  Dem_DTCGroupType                      DTCGroup,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_VAR) Idx);

#define DEM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

#define DEM_START_SEC_CODE
#include <MemMap.h>

/*------------------[Dem_ClearDTC]------------------------------------------*/

FUNC(Dem_ReturnClearDTCType, DEM_CODE) Dem_ClearDTC(
  Dem_DTCType       DTC,
  Dem_DTCFormatType DTCFormat,
  Dem_DTCOriginType DTCOrigin)
  /* DTCFormat parameter is ignored since there is no OBD support:
     Implementation is scheduled for future releases. */
{
  Dem_ReturnClearDTCType result = DEM_CLEAR_FAILED;

  DBG_DEM_CLEARDTC_ENTRY(DTC, DTCFormat, DTCOrigin);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_ClearDTC, DEM_E_UNINIT);
    result = DEM_CLEAR_FAILED;
  }
  else if (DTC > (Dem_DTCType) 0xFFFFFFU)
  {
    DEM_REPORT_ERROR(DEM_SID_ClearDTC, DEM_E_PARAM_DATA);
    result = DEM_CLEAR_WRONG_DTC;
  }
  else if ( (DTCFormat != DEM_DTC_FORMAT_OBD) &&
            (DTCFormat != DEM_DTC_FORMAT_UDS)
          )
  {
    DEM_REPORT_ERROR(DEM_SID_ClearDTC, DEM_E_PARAM_DATA);
    result = DEM_CLEAR_FAILED;
  }
  else if ( ( ( (DTCOrigin != DEM_DTC_ORIGIN_PRIMARY_MEMORY) &&
                (DTCOrigin != DEM_DTC_ORIGIN_SECONDARY_MEMORY)
              ) &&
              (DTCOrigin != DEM_DTC_ORIGIN_MIRROR_MEMORY)
            ) &&
            (DTCOrigin != DEM_DTC_ORIGIN_PERMANENT_MEMORY)
          )
  {
    DEM_REPORT_ERROR(DEM_SID_ClearDTC, DEM_E_PARAM_DATA);
    result = DEM_CLEAR_WRONG_DTCORIGIN;
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
    /* check if an async ClearDTC was started */
    if (DEM_CLEARDTC_STATE_RUNNING == Dem_ClearDtcAsyncStatus.RunState)
    {
      /* report result PENDING */
      result = DEM_CLEAR_PENDING;
    }
    /* CHECK: NOPARSE */
    else if (DEM_CLEARDTC_STATE_CANCELLED == Dem_ClearDtcAsyncStatus.RunState)
    { /* !LINKSTO Dem629,1 */
      /* report result FAILED */
      result = DEM_CLEAR_FAILED;
      /* Dem_DcmCancelOperation is able to cancel ClearDTC immediately */
      DEM_UNREACHABLE_CODE_ASSERT(DEM_SID_ClearDTC);
    }
    /* CHECK: PARSE */
    else if (DEM_CLEARDTC_STATE_FAILED == Dem_ClearDtcAsyncStatus.RunState)
    {
      /* set the status back to IDLE */
      Dem_ClearDtcAsyncStatus.RunState = DEM_CLEARDTC_STATE_IDLE;
      /* report result FAILED */
      result = DEM_CLEAR_FAILED;
    }
    else if (DEM_CLEARDTC_STATE_FINISHED == Dem_ClearDtcAsyncStatus.RunState)
    { /* !LINKSTO Dem572,1 */
      /* set the status back to IDLE */
      Dem_ClearDtcAsyncStatus.RunState = DEM_CLEARDTC_STATE_IDLE;
      /* report result OK */
      result = DEM_CLEAR_OK;
    }
    else /* RunState: DEM_CLEARDTC_STATE_IDLE */
#endif /* DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH */
    {
      result = Dem_StartClearDTC(DTC, DTCFormat, DTCOrigin);
    }
  }

  DBG_DEM_CLEARDTC_EXIT(result, DTC, DTCFormat, DTCOrigin);
  return result;
}

/*------------------[Dem_DisableDTCSetting]---------------------------------*/

FUNC(Dem_ReturnControlDTCSettingType, DEM_CODE) Dem_DisableDTCSetting(
  Dem_DTCGroupType DTCGroup,
  Dem_DTCKindType  DTCKind)
  /* DTCKind parameter is ignored:
     The current implementation only supports non OBD-relevant ECUs.
     Implementation is scheduled for future releases. */
{
  Dem_ReturnControlDTCSettingType result = DEM_CONTROL_DTC_SETTING_N_OK;

  DBG_DEM_DISABLEDTCSETTING_ENTRY(DTCGroup, DTCKind);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_DisableDTCSetting, DEM_E_UNINIT);
  }
  else if ( (DTCKind != DEM_DTC_KIND_ALL_DTCS) &&
            (DTCKind != DEM_DTC_KIND_EMISSION_REL_DTCS)
          )
  {
    DEM_REPORT_ERROR(DEM_SID_DisableDTCSetting, DEM_E_PARAM_DATA);
  }
  else
#else /* DEM_DEV_ERROR_DETECT */
  TS_PARAM_UNUSED(DTCKind);
#endif /* DEM_DEV_ERROR_DETECT */
  {
    if (DTCGroup == DEM_DTC_GROUP_ALL_DTCS)
    {
      /* disable DTC setting for all groups beside DEM_DTCGRP_IDX_NO_DTC */
      Dem_DTCSettingAllowed = (uint32)1U << DEM_DTCGRP_IDX_NO_DTC;

      result = DEM_CONTROL_DTC_SETTING_OK;
    }
    else
    {
      uint8 GroupIdx;

      if (Dem_GetIdxOfDTCGroup(DTCGroup, &GroupIdx) == TRUE)
      {
        /* disable DTC setting for requested group index */
        DEM_ATOMIC_CLR_BIT_32(Dem_DTCSettingAllowed, GroupIdx);

        result = DEM_CONTROL_DTC_SETTING_OK;
      }
      else /* invalid or not configured group */
      {
        result = DEM_CONTROL_DTC_WRONG_DTCGROUP;
      }
    }
  }

  DBG_DEM_DISABLEDTCSETTING_EXIT(result, DTCGroup, DTCKind);
  return result;
}

/*------------------[Dem_EnableDTCSetting]----------------------------------*/

FUNC(Dem_ReturnControlDTCSettingType, DEM_CODE) Dem_EnableDTCSetting(
  Dem_DTCGroupType DTCGroup,
  Dem_DTCKindType  DTCKind)
  /* DTCKind parameter is ignored:
     The current implementation only supports non OBD-relevant ECUs.
     Implementation is scheduled for future releases. */
{
  Dem_ReturnControlDTCSettingType result = DEM_CONTROL_DTC_SETTING_N_OK;

  DBG_DEM_ENABLEDTCSETTING_ENTRY(DTCGroup, DTCKind);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_EnableDTCSetting, DEM_E_UNINIT);
  }
  else if ( (DTCKind != DEM_DTC_KIND_ALL_DTCS) &&
            (DTCKind != DEM_DTC_KIND_EMISSION_REL_DTCS)
          )
  {
    DEM_REPORT_ERROR(DEM_SID_EnableDTCSetting, DEM_E_PARAM_DATA);
  }
  else
#else /* DEM_DEV_ERROR_DETECT */
  TS_PARAM_UNUSED(DTCKind);
#endif /* DEM_DEV_ERROR_DETECT */
  {
    if (DTCGroup == DEM_DTC_GROUP_ALL_DTCS)
    {
      /* enable DTC setting for all groups */
      DEM_ATOMIC_ASSIGN_32(Dem_DTCSettingAllowed,
                           DEM_BITFIELD_VALUE_ALL_GROUPS);

      result = DEM_CONTROL_DTC_SETTING_OK;
    }
    else
    {
      uint8 GroupIdx;

      if (Dem_GetIdxOfDTCGroup(DTCGroup, &GroupIdx) == TRUE)
      {
        /* enable DTC setting for requested group index */
        DEM_ATOMIC_SET_BIT_32(Dem_DTCSettingAllowed, GroupIdx);

        result = DEM_CONTROL_DTC_SETTING_OK;
      }
      else /* invalid or not configured group */
      {
        result = DEM_CONTROL_DTC_WRONG_DTCGROUP;
      }
    }
  }

  DBG_DEM_ENABLEDTCSETTING_EXIT(result, DTCGroup, DTCKind);
  return result;
}

/*------------------[Dem_DcmCancelOperation]--------------------------------*/

FUNC(void, DEM_CODE) Dem_DcmCancelOperation(void)
{
  DBG_DEM_DCMCANCELOPERATION_ENTRY();

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmCancelOperation, DEM_E_UNINIT);
  }
  else
#endif
  {
#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
    /* check if asynchronous ClearDTC request is running */
    if (DEM_CLEARDTC_STATE_RUNNING == Dem_ClearDtcAsyncStatus.RunState)
    {
      /* immediate storage mechanism can handle data management in the
       * background including subsequent ClearDTC requests and event status
       * reports -> simply ClearDtcAsyncStatus back to IDLE */
      Dem_ClearDtcAsyncStatus.RunState = DEM_CLEARDTC_STATE_IDLE;
    }
#endif
  }

  /* Dem_Set<...>Filter() APIs will cancel previous filter automatically,
     when called again by Dcm */

  DBG_DEM_DCMCANCELOPERATION_EXIT();
}

/*==================[internal function definitions]=========================*/

/*------------------[Dem_StartClearDTC]-------------------------------------*/

STATIC FUNC(Dem_ReturnClearDTCType, DEM_CODE) Dem_StartClearDTC(
  Dem_DTCType       DTC,
  Dem_DTCFormatType DTCFormat,
  Dem_DTCOriginType DTCOrigin)
{
  Dem_ReturnClearDTCType result = DEM_CLEAR_FAILED;
  const uint8 OriginIdx = (uint8)(DTCOrigin - DEM_DTC_ORIGIN_PRIMARY_MEMORY);
  uint8 groupIdx = DEM_DTCGRP_IDX_INVALID;

  boolean DtcGroupRequest = FALSE;

  DBG_DEM_STARTCLEARDTC_ENTRY(DTC, DTCFormat, DTCOrigin);

  /* check if requested DTC origin is supported */
  if (Dem_SizeEventMem[OriginIdx] == (Dem_SizeEvMemEntryType) 0U)
  {
    result = DEM_CLEAR_WRONG_DTCORIGIN;
  }
  /* check if DTC matches a group Id */
  else if ((Dem_DTCGroupType)DTC == DEM_DTC_GROUP_ALL_DTCS)
  {
    /* groupIdx is not modified if 'DTCGroup == DEM_DTC_GROUP_ALL_DTCS',
     * and is not allowed to be used in this case */
    DtcGroupRequest = TRUE;
    /* request accepted */
    result = DEM_CLEAR_OK;
  }
  else if (Dem_GetIdxOfDTCGroup((Dem_DTCGroupType) DTC, &groupIdx) != FALSE)
  {
    DtcGroupRequest = TRUE;
    /* request accepted */
    result = DEM_CLEAR_OK;
  }
  else if (DTCFormat == DEM_DTC_FORMAT_OBD)
  {
    result = DEM_CLEAR_WRONG_DTC;
  }
  else
  {
    /* DtcGroupRequest remains FALSE, request accepted */
    result = DEM_CLEAR_OK;
  }

  /* - if all preconditions are met, clear event(s) */
  if (result == DEM_CLEAR_OK)
  {
    /* AnyEvenModified is needed only in case of non-volatile processing, but
     * to avoid multiple declarations of function Dem_ClearEvents, it is
     * declared for all configurations */
    Dem_EventModifiedType AnyEventModified;

#if (DEM_CLEAR_DTC_BEHAVIOR != DEM_CLRRESP_VOLATILE)
    /* status modified flag is always present */
    AnyEventModified.EvSt = FALSE;
#endif

#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
    /* data modified flag is only present for NONVOLATILE_FINISH */
    AnyEventModified.EvMemEntry =
      Dem_CheckForOldClearImmediateEntries(OriginIdx);
#endif

    /* clearing events */
    result = Dem_ClearEvents(DTC, DTCOrigin, DtcGroupRequest,
                             groupIdx, &AnyEventModified);

#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
    if ((AnyEventModified.EvMemEntry == TRUE) ||
        (AnyEventModified.EvSt == TRUE))
    {
      Dem_ClearDtcAsyncStatus.RunState = DEM_CLEARDTC_STATE_RUNNING;

      /* !LINKSTO Dem572,1 */
      /* set result to PENDING */
      result = DEM_CLEAR_PENDING;
    }
#endif

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
    /* at this point, result is always CLEAR_OK or CLEAR_PENDING */
    /* depending on DTC behavior:
     * - !LINKSTO Dem571,1,Dem.ClearDTC.NonvolatileTrigger,1
     *     if set to NONVOLATILE_TRIGGER, trigger NvM and return OK
     * - !LINKSTO Dem572,1
     *     if set to NONVOLATILE_FINISH, trigger NvM and return PENDING
     * - !LINKSTO Dem570,1
     *     if set to VOLATILE, trigger NvM (for immediate storage events)
     *                         and return OK */
#if (DEM_CLEAR_DTC_BEHAVIOR != DEM_CLRRESP_VOLATILE)
    if (AnyEventModified.EvSt == TRUE)
    {
#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_TRIGGER)
      switch (Dem_ClearDtcAsyncStatus.EventStatusWrite)
      {
        case DEM_NVM_IDLE:
          /* NvM is idle -> trigger writing of event status block */
          if (Dem_TriggerNvmWriteEventStatus() != E_OK)
          {
            /* report result FAILED */
            result = DEM_CLEAR_FAILED;
          }
          break;
        case DEM_NVM_WAITING:
          /* NvM did NOT start processing of event status block yet - it is
           * only queued in NvM -> do nothing */
          break;
        case DEM_NVM_PENDING:
          /* NvM already started processing of event status block by an
           * earlier ClearDTC request
           * -> set flag to re-trigger after current processing is finished */
          Dem_ClearDtcAsyncStatus.RetriggerEventStatusWrite = TRUE;
          break;
        /* CHECK: NOPARSE */
        default:
          DEM_UNREACHABLE_CODE_ASSERT(DEM_SID_ClearDTC);
          break;
        /* CHECK: PARSE */
      }
#else /* DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH */
      /* return value handled asynchronously via ClearDTC RunState */
      (void)Dem_TriggerNvmWriteEventStatus();
#endif /* DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_TRIGGER */
    }
#endif /* DEM_CLEAR_DTC_BEHAVIOR != DEM_CLRRESP_VOLATILE */

    Dem_TriggerNvmWriteGateEntry();
#endif
  }

  DBG_DEM_STARTCLEARDTC_EXIT(result, DTC, DTCFormat, DTCOrigin);
  return result;
}

/*------------------[Dem_CheckForOldClearImmediateEntries]------------------*/

#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
STATIC FUNC(boolean, DEM_CODE) Dem_CheckForOldClearImmediateEntries(
  uint8 OriginIdx)
{
  boolean result = FALSE;
  Dem_SizeEvMemEntryType EventEntryIdx;
  const Dem_EventMemoryEntryPtrType EventMem = Dem_EventMem[OriginIdx];
  const Dem_SizeEvMemEntryType sizeEventMem = Dem_SizeEventMem[OriginIdx];

  DBG_DEM_CHECKFOROLDCLEARIMMEDIATEENTRIES_ENTRY(OriginIdx);

  /*
   * ENTER critical section to protect the event memory
   *       call-context: Dcm (Task)
   */
  SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

  /* search for entries that were scheduled to be cleared by earlier
   * ClearDTC request(s) */
  for (EventEntryIdx = 0U; EventEntryIdx < sizeEventMem; ++EventEntryIdx)
  {
    /* check if entry was scheduled to be cleared earlier */
    if (EventMem[EventEntryIdx].EntryStatus == DEM_ENTRY_CLEAR_IMMEDIATELY)
    {
      Dem_ClearDtcAsyncStatus.OriginIdx = OriginIdx;
      Dem_ClearDtcAsyncStatus.EventMemWrite = DEM_NVM_WAITING;

      result = TRUE;

      /* earlier scheduled entry found: stop searching */
      break;
    }
  }

  /*
   * LEAVE critical section
   */
  SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

  DBG_DEM_CHECKFOROLDCLEARIMMEDIATEENTRIES_EXIT(result, OriginIdx);
  return result;
}
#endif /* DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH */

/*------------------[Dem_ClearEvents]---------------------------------------*/

STATIC FUNC(Dem_ReturnClearDTCType, DEM_CODE) Dem_ClearEvents(
  Dem_DTCType       DTC,
  Dem_DTCOriginType DTCOrigin,
  boolean           DtcGroupRequest,
  uint8             groupIdx,
  /* Deviation MISRA-1 */
  CONSTP2VAR(Dem_EventModifiedType, AUTOMATIC, AUTOMATIC) AnyEventModified)
{
  /* result is initially set to DEM_CLEAR_OK since same value has result
   * variable in Dem_StartClearDTC */
  Dem_ReturnClearDTCType result = DEM_CLEAR_OK;
  const uint8 OriginIdx = (uint8)(DTCOrigin - DEM_DTC_ORIGIN_PRIMARY_MEMORY);
  Dem_EventIdType EventId;
  /* only needed if immediate storage in use, but to avoid multiple
   * declarations of Dem_ClearEvent() with several different calls to it,
   * this variable is defined independent of the configuration */
  Dem_NvMGatePrepStatusType NvMGateStatus = DEM_GATE_LOCKED;

  DBG_DEM_CLEAREVENTS_ENTRY(DTC, DTCOrigin, DtcGroupRequest,
    groupIdx, AnyEventModified);

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
  /* try to lock the gate entry */
  NvMGateStatus = Dem_BeginPrepareGateEntry(OriginIdx);
#endif

  /* search all event Ids for requested event */
  for (EventId = 1U; EventId <= DEM_MAX_EVENTID; ++EventId)
  {
    const uint8 groupIdxOfEvt = Dem_GbiDTCGroupIdx(EventId);
    const Dem_DTCOriginType originOfEvt = Dem_GbiDTCOrigin(EventId);
    boolean entryDTC = FALSE;

    if ((FALSE == DtcGroupRequest) && (DTCOrigin == originOfEvt))
    {
      if (Dem_GbiDTC(EventId) == DTC)
      {
        entryDTC = TRUE;
      }
    }

    if ( /* single DTC */
         (TRUE == entryDTC) ||
         /* group of DTC: requested group and respective origin only */
         ( ( ( ((Dem_DTCGroupType) DTC == DEM_DTC_GROUP_ALL_DTCS) &&
               (groupIdxOfEvt != DEM_DTCGRP_IDX_NO_DTC) ) ||
             (groupIdx == groupIdxOfEvt) ) &&
           (originOfEvt == DTCOrigin) ) )
    {
#if (DEM_USE_CB_CLEAR_EVENT_ALLOWED == STD_ON)
      boolean Allowed;
      const Std_ReturnType RetVal =
        Dem_CbClearEventAllowed(EventId, &Allowed);

      if ( (RetVal != E_OK) || ( Allowed == TRUE) )
#endif
      {
#if (DEM_CLEAR_DTC_BEHAVIOR != DEM_CLRRESP_VOLATILE)
        const Dem_EventModifiedType EventModified =
          Dem_ClearEvent(EventId, &NvMGateStatus);

#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
        if (EventModified.EvMemEntry == TRUE)
        {
          AnyEventModified->EvMemEntry = TRUE;
        }
#endif

        if (EventModified.EvSt == TRUE)
        {
          AnyEventModified->EvSt = TRUE;
        }
#else
        TS_PARAM_UNUSED(AnyEventModified);
        (void)Dem_ClearEvent(EventId, &NvMGateStatus);
#endif
      }

      if (FALSE == DtcGroupRequest)
      {
        /* event for single DTC found: clear OK, stop searching */
        /* result remains DEM_CLEAR_OK */
        break;
      } /* else: group of DTC -> continue searching */
    } /* else: neither DTC nor group is matching */
  }

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
  /* unlock the gate entry */
  Dem_EndPrepareGateEntry(OriginIdx, NvMGateStatus);
#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */

  /* check if a single DTC was not found */
  if ( (FALSE == DtcGroupRequest) && (EventId > DEM_MAX_EVENTID) )
  {
    /* single DTC not found, wrong DTC */
    result = DEM_CLEAR_WRONG_DTC;
  } /* else: status already set to DEM_CLEAR_OK */

  /* clear overflow indication status of all event memories */
  if (DEM_DTC_GROUP_ALL_DTCS == (Dem_DTCGroupType)DTC)
  {
    DEM_ATOMIC_CLR_BIT_8(DEM_OVFIND_FLAGS, OriginIdx);
  }

  DBG_DEM_CLEAREVENTS_EXIT(result, DTC, DTCOrigin,
    DtcGroupRequest, groupIdx, AnyEventModified);

  return result;
}

/*------------------[Dem_ClearEvent]----------------------------------------*/

STATIC FUNC(Dem_EventModifiedType, DEM_CODE) Dem_ClearEvent(
  Dem_EventIdType              EventId,
  Dem_NvMGatePrepStatusPtrType NvMGateStatus)
{
  Dem_EventModifiedType EventModified;

  const Dem_DTCStatusMaskType DTCStatusMask =
    (DEM_UDS_STATUS_TNCSLC | DEM_UDS_STATUS_TNCTOC);
  Dem_DTCStatusMaskType OldDTCStatusMask;

  Dem_EventMemoryEntryPtrType EvMemEntry;
  Dem_SizeEvMemEntryType EvMemEntryIdx;

  DBG_DEM_CLEAREVENT_ENTRY(EventId, NvMGateStatus);

  /* initialize return value */
  EventModified.EvSt = FALSE;
#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
  EventModified.EvMemEntry = FALSE;
#endif

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_OFF)
  /* to avoid multiple declarations of Dem_ClearEvent() with several different
   * calls to it, this parameter is handled with a dummy value for this
   * configuration */
  *NvMGateStatus = DEM_GATE_UNUSED;
#endif

  /*
   * ENTER critical section to protect the event memory
   *       call-context: Dcm (Task)
   */
  SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

  /* get old status mask */
  OldDTCStatusMask = DEM_DTC_STATUS_MASKS[EventId];

  /* reset status mask for event */
  DEM_DTC_STATUS_MASKS[EventId] = DTCStatusMask;

#if (DEM_MAX_NUMBER_PRESTORED_FF > 0U)
  /* release prestored freeze frame */
  if (Dem_GbiEnablePrestorage(EventId) == TRUE)
  {
    /* mark prestored freeze frame as unused */
    DEM_CLR_BIT_IN_ARRAY(Dem_PFFEntryValid, Dem_GetPFFIndex(EventId));
  }
#endif

  /* reset debouncing counters for event (Dem343) */
  Dem_DebounceFctPtrTable[Dem_GbiDebounceAlgo(EventId)].ResetFct(EventId);

  /* search for DTC in event memory */
  if (Dem_SearchForEntry(EventId, &EvMemEntry, &EvMemEntryIdx) == TRUE)
  {
    Dem_ClearEventEntry(EvMemEntry);

#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
    /* event entry was modified */
    EventModified.EvMemEntry = TRUE;
#endif

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
    /* event memory entry has been deleted: trigger immediate storage */
    Dem_CheckForImmediateEntryStorage(
      EventId,
      EvMemEntry,
      EvMemEntryIdx,
#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_VOLATILE)
      DEM_NVM_NO_FORCE, /* CLRRESP_VOLATILE: updated on shutdown */
#else
      DEM_NVM_FORCE, /* CLRRESP_NONVOLATILE_<...>: write immediately */
#endif
      NvMGateStatus);
#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */

#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
    /* entry is scheduled to be cleared */
    Dem_ClearDtcAsyncStatus.OriginIdx = Dem_GbiDTCOriginIdx(EventId);
    Dem_ClearDtcAsyncStatus.EventMemWrite = DEM_NVM_WAITING;
#endif
  }

  if (OldDTCStatusMask != DTCStatusMask)
  {
    /* event status was modified: mark block as modified to trigger
     * a ClearDtc run state transition to RUNNING */
    EventModified.EvSt = TRUE;
  }

  /* clear error queue */
  Dem_InvalidateErrorQueueEntry(EventId);

  /*
   * LEAVE critical section
   */
  SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

#if ( (DEM_USE_CB_TRIG_ON_EVST == STD_ON)  || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) || \
      (DEM_USE_CB_INIT_MONITOR == STD_ON))
  /* report event change by callback */
  if (OldDTCStatusMask != DTCStatusMask)
  {
#if ( (DEM_USE_CB_TRIG_ON_EVST == STD_ON)  || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) )
    /* notify application that event status has changed */
    Dem_CbTriggerOnEventStatus(EventId, OldDTCStatusMask, DTCStatusMask);
#endif

#if (DEM_USE_CB_INIT_MONITOR == STD_ON)
    /* Dem009: inform application about clearance */
    Dem_CbInitMonitorForEvent(EventId, DEM_INIT_MONITOR_CLEAR);
#endif
  }
#endif /* DEM_USE_CB_TRIG_ON_EVST == STD_ON  ||
          DEM_USE_CB_TRIG_ON_DTCST == STD_ON ||
          DEM_USE_CB_INIT_MONITOR == STD_ON */

  DBG_DEM_CLEAREVENT_EXIT(EventModified, EventId, NvMGateStatus);
  return EventModified;
}

STATIC FUNC(boolean, DEM_CODE) Dem_GetIdxOfDTCGroup(
  Dem_DTCGroupType                      DTCGroup,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_VAR) Idx)
{
  boolean result;
  uint8_least index;

  DBG_DEM_GETIDXOFDTCGROUP_ENTRY(DTCGroup, Idx);

  /* for all DTCGroups */
  for (index = 0U; index < DEM_NUM_DTC_GROUPS; index++)
  {
    if (DTCGroup == Dem_DTCGroups[index])
    {
      break;
    }
  }

  if (index < DEM_NUM_DTC_GROUPS)
  {
    *Idx   = (uint8)index;
    result = TRUE;
  }
  else
  {
    *Idx   = DEM_DTCGRP_IDX_INVALID;
    result = FALSE;
  }

  DBG_DEM_GETIDXOFDTCGROUP_EXIT(result, DTCGroup, Idx);
  return result;
}

#define DEM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[end of file]===========================================*/
