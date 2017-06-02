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
 * the Dcm for the access of DTC status information. */

/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 12.4 (required)
 *    "The right-hand operand of a logical '&&' or '||' operator shall not
 *    contain side effects."
 *
 *    Reason:
 *    Call to getter functions which do not modify any global state.
 */

/*==================[inclusions]============================================*/
/* !LINKSTO dsn.Dem.IncludeStr,1 */

#include <TSAutosar.h>                        /* EB specific standard types */
#include <Std_Types.h>                            /* AUTOSAR standard types */

#include <Dem_Int.h>             /* Module public and internal declarations */
#include <Dem_Trace.h>                        /* Dbg related macros for Dem */

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

#define DEM_START_SEC_CODE
#include <MemMap.h>

/** \brief Function to apply the DTC filter with the given event
 **
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[out] DTCStatus
 ** \param[out] FDC
 **
 ** \return Boolean value, if the filter matches the event configuration
 ** \retval TRUE  the filters match
 ** \retval FALSE the filters don't match
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(boolean, DEM_CODE) Dem_ApplyDTCFilter(
  Dem_EventIdType                                                EventId,
  P2VAR(Dem_DTCStatusMaskType, AUTOMATIC, DEM_APPL_DATA)         DTCStatus,
  P2VAR(Dem_FaultDetectionCounterType, AUTOMATIC, DEM_APPL_DATA) FDC);

#define DEM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

#define DEM_START_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief Status of DTC-filter */
VAR(Dem_DTCFilterType, DEM_VAR) Dem_DTCFilter =
{
  0xFFU,                         /* DTC status mask */
  DEM_DTC_KIND_ALL_DTCS,         /* DTC kind */
  DEM_DTC_FORMAT_UDS,            /* DTC format */
  DEM_DTC_ORIGIN_PRIMARY_MEMORY, /* DTC Origin */
  DEM_FILTER_WITH_SEVERITY_NO,   /* filter with severity */
  DEM_SEVERITY_NO_SEVERITY,      /* severity */
  DEM_FILTER_FOR_FDC_NO,         /* filter for FDC */
  1U                             /* index of event to read next */
};

#define DEM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

#define DEM_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>

/** \brief Status of record-filter */
VAR(uint8, DEM_VAR_NOINIT) Dem_RecordFilterRecNumIdx;

#define DEM_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>

#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief Record filter entry index */
VAR(Dem_SizeEvMemEntryType, DEM_VAR_NOINIT) Dem_RecordFilterEntryIdx;

#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

#define DEM_START_SEC_CODE
#include <MemMap.h>

/*----------------[Dem_SetDTCFilter]----------------------------------------*/

FUNC(Dem_ReturnSetFilterType, DEM_CODE) Dem_SetDTCFilter(
  Dem_DTCStatusMaskType      DTCStatusMask,
  Dem_DTCKindType            DTCKind,
  Dem_DTCFormatType          DTCFormat,
  Dem_DTCOriginType          DTCOrigin,
  Dem_FilterWithSeverityType FilterWithSeverity,
  Dem_DTCSeverityType        DTCSeverityMask,
  Dem_FilterForFDCType       FilterForFaultDetectionCounter)
{
  Dem_ReturnSetFilterType result = DEM_WRONG_FILTER;

  DBG_DEM_SETDTCFILTER_ENTRY(
    DTCStatusMask, DTCKind, DTCFormat, DTCOrigin, FilterWithSeverity,
    DTCSeverityMask, FilterForFaultDetectionCounter);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* check of Dem_InitializationState would be not necessary, but if this API
   * is called before full initialization, the system design is dubious
   * (and Dem_GetNextFilteredDTC[AndFDC]() is then not usable anyway) */
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_SetDTCFilter, DEM_E_UNINIT);
  }

  /* Dcm is responsible, that no status masks with unavailable bits are
   * requested (but this would not influence correctness of the filter) */
  /* no check with DEM_IS_UNMASKED_BIT_SET(DTCStatusMask, AVAILABILITY_MASK)
   * done, because all bits are supported */

  else if ( (DTCKind != DEM_DTC_KIND_ALL_DTCS) &&
            (DTCKind != DEM_DTC_KIND_EMISSION_REL_DTCS)
          )
  {
    DEM_REPORT_ERROR(DEM_SID_SetDTCFilter, DEM_E_PARAM_DATA);
  }
  else if ( (DTCFormat != DEM_DTC_FORMAT_OBD) &&
            (DTCFormat != DEM_DTC_FORMAT_UDS)
          )
  {
    DEM_REPORT_ERROR(DEM_SID_SetDTCFilter, DEM_E_PARAM_DATA);
  }
  else if ( ( ( (DTCOrigin != DEM_DTC_ORIGIN_PRIMARY_MEMORY) &&
                (DTCOrigin != DEM_DTC_ORIGIN_SECONDARY_MEMORY) ) &&
              (DTCOrigin != DEM_DTC_ORIGIN_MIRROR_MEMORY) ) &&
            (DTCOrigin != DEM_DTC_ORIGIN_PERMANENT_MEMORY)
          )
  {
    DEM_REPORT_ERROR(DEM_SID_SetDTCFilter, DEM_E_PARAM_DATA);
  }
  else if ( (FilterWithSeverity != DEM_FILTER_WITH_SEVERITY_NO) &&
            (FilterWithSeverity != DEM_FILTER_WITH_SEVERITY_YES)
          )
  {
    DEM_REPORT_ERROR(DEM_SID_SetDTCFilter, DEM_E_PARAM_DATA);
  }
  else if ( (DTCSeverityMask != DEM_SEVERITY_NO_SEVERITY) &&
            (DEM_IS_UNMASKED_BIT_SET(DTCSeverityMask,
               DEM_SEVERITY_MAINTENANCE_ONLY |
               DEM_SEVERITY_CHECK_AT_NEXT_HALT |
               DEM_SEVERITY_CHECK_IMMEDIATELY) )
          )
  {
    DEM_REPORT_ERROR(DEM_SID_SetDTCFilter, DEM_E_PARAM_DATA);
  }
  else if ( (FilterForFaultDetectionCounter != DEM_FILTER_FOR_FDC_YES) &&
            (FilterForFaultDetectionCounter != DEM_FILTER_FOR_FDC_NO)
          )
  {
    DEM_REPORT_ERROR(DEM_SID_SetDTCFilter, DEM_E_PARAM_DATA);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* save filter information in internal data structure */
    Dem_DTCFilter.DTCStatusMask      = DTCStatusMask;
    Dem_DTCFilter.DTCKind            = DTCKind;
    Dem_DTCFilter.DTCFormat          = DTCFormat;
    Dem_DTCFilter.DTCOrigin          = DTCOrigin;
    Dem_DTCFilter.FilterWithSeverity = FilterWithSeverity;
    Dem_DTCFilter.DTCSeverityMask    = DTCSeverityMask;
    Dem_DTCFilter.FilterForFDC       = FilterForFaultDetectionCounter;

    /* reset next event Id to the first configured event Id */
    Dem_DTCFilter.NextEventId        = 1U;

    result = DEM_FILTER_ACCEPTED;
  }

  DBG_DEM_SETDTCFILTER_EXIT(
    result, DTCStatusMask, DTCKind, DTCFormat, DTCOrigin, FilterWithSeverity,
    DTCSeverityMask, FilterForFaultDetectionCounter);
  return result;
}

/*----------------[Dem_SetFreezeFrameRecordFilter]--------------------------*/

FUNC(Dem_ReturnSetFilterType, DEM_CODE) Dem_SetFreezeFrameRecordFilter(
  Dem_DTCFormatType                       DTCFormat,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) NumberOfFilteredRecords)
  /* DTCFormat parameter is ignored since there is no OBD support:
     Implementation is scheduled for future releases. */
{
  Dem_ReturnSetFilterType result = DEM_WRONG_FILTER;

  DBG_DEM_SETFREEZEFRAMERECORDFILTER_ENTRY(
    DTCFormat, NumberOfFilteredRecords);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* check of Dem_InitializationState is necessary, as filter is reset in
   * Dem_Init() (and Dem_GetNextFilteredRecord() is then not usable anyway)
   * and also the event memory is accessed */
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_SetFreezeFrameRecordFilter, DEM_E_UNINIT);
  }
  else if ( (DTCFormat != DEM_DTC_FORMAT_OBD) &&
            (DTCFormat != DEM_DTC_FORMAT_UDS)
          )
  {
    DEM_REPORT_ERROR(DEM_SID_SetFreezeFrameRecordFilter, DEM_E_PARAM_DATA);
  }
  else if (NumberOfFilteredRecords == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_SetFreezeFrameRecordFilter, DEM_E_PARAM_POINTER);
  }
  else
#else /* DEM_DEV_ERROR_DETECT */
  TS_PARAM_UNUSED(DTCFormat);
#endif /* DEM_DEV_ERROR_DETECT */
  {
#if (DEM_NUM_FFSEGS > 0U)
    /* quoting Dem210: "This filter always belongs to primary memory." */
    const Dem_SizeEvMemEntryType sizeEventMem = Dem_SizeEventMem[0];
    const Dem_EventMemoryEntryPtrType Entry = Dem_EventMem[0];

    Dem_SizeEvMemEntryType index;
#endif

    uint16 NumOfFilteredRecs = 0U;

    /*
     * signal access of event memory
     */
    Dem_EvMemReadAccessSemaphore++;

#if (DEM_NUM_FFSEGS > 0U)
    /* count number of currently stored freeze frames */
    for (index = 0U; index < sizeEventMem; ++index)
    {
      if (Entry[index].EventId != (Dem_EventIdType)DEM_EVENT_ID_INVALID)
      {
        const Dem_FFIdxType NumFF =
          DEM_NUMFF(&Entry[index], Dem_GbiMaxNumFFRecs(Entry[index].EventId));

        NumOfFilteredRecs += (uint16)NumFF;
      }
    }
#endif

    /*
     * signal access of event memory finished
     */
    Dem_EvMemReadAccessSemaphore--;

    *NumberOfFilteredRecords = NumOfFilteredRecs;

    /* reset freeze frame record-filter */
    Dem_RecordFilterEntryIdx = 0U;
    Dem_RecordFilterRecNumIdx = 0U;

    result = DEM_FILTER_ACCEPTED;
  }

  DBG_DEM_SETFREEZEFRAMERECORDFILTER_EXIT(
    result, DTCFormat, NumberOfFilteredRecords);
  return result;
}

/*----------------[Dem_GetStatusOfDTC]--------------------------------------*/

FUNC(Dem_ReturnGetStatusOfDTCType, DEM_CODE) Dem_GetStatusOfDTC(
  Dem_DTCType                                            DTC,
  Dem_DTCOriginType                                      DTCOrigin,
  P2VAR(Dem_DTCStatusMaskType, AUTOMATIC, DEM_APPL_DATA) DTCStatus)
{
  Dem_ReturnGetStatusOfDTCType result;

  DBG_DEM_GETSTATUSOFDTC_ENTRY(DTC, DTCOrigin, DTCStatus);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetStatusOfDTC, DEM_E_UNINIT);
    result = DEM_STATUS_FAILED;
  }
  else if ( (DTC == (Dem_DTCType)0U) || (DTC > (Dem_DTCType)0xFFFFFFU) )
  {
    DEM_REPORT_ERROR(DEM_SID_GetStatusOfDTC, DEM_E_PARAM_DATA);
    result = DEM_STATUS_WRONG_DTC;
  }
  else if ( ( ( (DTCOrigin != DEM_DTC_ORIGIN_PRIMARY_MEMORY) &&
                (DTCOrigin != DEM_DTC_ORIGIN_SECONDARY_MEMORY) ) &&
              (DTCOrigin != DEM_DTC_ORIGIN_MIRROR_MEMORY) ) &&
            (DTCOrigin != DEM_DTC_ORIGIN_PERMANENT_MEMORY) )
  {
    DEM_REPORT_ERROR(DEM_SID_GetStatusOfDTC, DEM_E_PARAM_DATA);
    result = DEM_STATUS_WRONG_DTCORIGIN;
  }
  else if (DTCStatus == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetStatusOfDTC, DEM_E_PARAM_POINTER);
    result = DEM_STATUS_FAILED;
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    Dem_EventIdType EventId;

    /* search event Id by DTC and map return value.
     * DTCFormat is passed as DEM_DTC_FORMAT_UDS, since the API supports only
     * DTC in UDS format (Dem SWS 8.3.4.1.3). */
    switch (Dem_GetEvIdByDTC(DTC, DEM_DTC_FORMAT_UDS, DTCOrigin, &EventId))
    {
      case DEM_EIBD_OK:
        result = DEM_STATUS_OK;
        break;
      case DEM_EIBD_WRONG_DTC:
        result = DEM_STATUS_WRONG_DTC;
        break;
      case DEM_EIBD_WRONG_DTCORIGIN:
        result = DEM_STATUS_WRONG_DTCORIGIN;
        break;
      /* CHECK: NOPARSE */
      default: /* should never be reached */
        DEM_UNREACHABLE_CODE_ASSERT(DEM_SID_GetStatusOfDTC);
        result = DEM_STATUS_WRONG_DTC;
        break;
      /* CHECK: PARSE */
    }

    if (result == DEM_STATUS_OK)
    {
      /* copy DTCStatusMask to return parameter */
      *DTCStatus =
        DEM_DTC_STATUS_MASKS[EventId] & DEM_DTC_STATUS_AVAILABILITY_MASK;
    }
  }

  DBG_DEM_GETSTATUSOFDTC_EXIT(result, DTC, DTCOrigin, DTCStatus);
  return result;
}

/*----------------[Dem_GetDTCStatusAvailabilityMask]------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_GetDTCStatusAvailabilityMask(
  P2VAR(Dem_DTCStatusMaskType, AUTOMATIC, DEM_APPL_DATA) DTCStatusMask)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_GETDTCSTATUSAVAILABILITYMASK_ENTRY(DTCStatusMask);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* check of Dem_InitializationState is not necessary:
   * it's allowed to get availability mask even if Dem is uninitialized */
  if (DTCStatusMask == NULL_PTR)
  {
    DEM_REPORT_ERROR(
      DEM_SID_GetDTCStatusAvailabilityMask, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    *DTCStatusMask = DEM_DTC_STATUS_AVAILABILITY_MASK;

    result = E_OK;
  }

  DBG_DEM_GETDTCSTATUSAVAILABILITYMASK_EXIT(result, DTCStatusMask);
  return result;
}

/*----------------[Dem_GetNumberOfFilteredDTC]------------------------------*/

FUNC(Dem_ReturnGetNumberOfFilteredDTCType, DEM_CODE)
  Dem_GetNumberOfFilteredDTC(
    P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) NumberOfFilteredDTC)
{
  Dem_ReturnGetNumberOfFilteredDTCType result = DEM_NUMBER_FAILED;

  DBG_DEM_GETNUMBEROFFILTEREDDTC_ENTRY(NumberOfFilteredDTC);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetNumberOfFilteredDTC, DEM_E_UNINIT);
  }
  else if (NumberOfFilteredDTC == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetNumberOfFilteredDTC, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    Dem_EvIdLeastType EvId;
    *NumberOfFilteredDTC = 0U; /* total number of counted DTCs */

    /* When calculing the number of filtered DTCs the event memory need not be
     * locked (by DcmAccessInProgress): when interrupting this routine while
     * looping over the events, modifications of events with Id smaller than
     * the current processed Id are neglected, while modifications of events
     * with event Id greater than the current processed Id are represented by
     * the result. Thus the result is never corrupt (but at most represents an
     * obsolete state of the event memory). */
    for (EvId = 1U; EvId <= DEM_MAX_EVENTID; ++EvId)
    {
      Dem_DTCStatusMaskType idleDTCStatus; /* status not needed this time */
      Dem_FaultDetectionCounterType idleFDC; /* FDC not needed this time */

      /* if status mask matches */
      if (Dem_ApplyDTCFilter((Dem_EventIdType)EvId, &idleDTCStatus, &idleFDC)
          != FALSE)
      {
        /* new match found */
        ++(*NumberOfFilteredDTC);
      }
    }

    result = DEM_NUMBER_OK;
  }

  DBG_DEM_GETNUMBEROFFILTEREDDTC_EXIT(result, NumberOfFilteredDTC);
  return result;
}

/*----------------[Dem_GetNextFilteredDTC]----------------------------------*/

/* !LINKSTO Dem215,2 */
FUNC(Dem_ReturnGetNextFilteredDTCType, DEM_CODE) Dem_GetNextFilteredDTC(
  P2VAR(Dem_DTCType, AUTOMATIC, DEM_APPL_DATA)           DTC,
  P2VAR(Dem_DTCStatusMaskType, AUTOMATIC, DEM_APPL_DATA) DTCStatus)
{
  Dem_ReturnGetNextFilteredDTCType result = DEM_FILTERED_NO_MATCHING_DTC;

  DBG_DEM_GETNEXTFILTEREDDTC_ENTRY(DTC, DTCStatus);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetNextFilteredDTC, DEM_E_UNINIT);
  }
  else if ( (DTCStatus == NULL_PTR) || (DTC == NULL_PTR) )
  {
    DEM_REPORT_ERROR(DEM_SID_GetNextFilteredDTC, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    boolean filterresult = FALSE;

    /* Function NOT fully implemented yet.
     * Filter criteria related to DTCFormat and DTCKind is not implemented
     * since there is no OBD support.
     * Implementation is scheduled for future releases. */

    /* search for first DTC fulfilling the filter criterion */
    while ( (Dem_DTCFilter.NextEventId <= DEM_MAX_EVENTID) &&
            (filterresult == FALSE)
          )
    {
      Dem_FaultDetectionCounterType idleFDC; /* FDC not needed this time */

      filterresult = Dem_ApplyDTCFilter(
        (Dem_EventIdType)Dem_DTCFilter.NextEventId, DTCStatus, &idleFDC);

      /* skip events not matching the filter criterion */
      if (filterresult == TRUE)
      {
        /* return DTC */
        *DTC = Dem_GbiDTC((Dem_EventIdType)Dem_DTCFilter.NextEventId);

#if (DEM_DTC_STATUS_AVAILABILITY_MASK == 0U)
        *DTCStatus = 0U;
#elif (DEM_DTC_STATUS_AVAILABILITY_MASK != 255U)
        /* mask out unsupported bits in DTC status */
        *DTCStatus &= DEM_DTC_STATUS_AVAILABILITY_MASK;
#else
        /* DTCStatus is fully available */
#endif

        /* next matching DTC found */
        result = DEM_FILTERED_OK;
      }

      /* store event id for next call in filter */
      ++Dem_DTCFilter.NextEventId;
    }
  }

  DBG_DEM_GETNEXTFILTEREDDTC_EXIT(result, DTC, DTCStatus);
  return result;
}

/*----------------[Dem_GetDTCByOccurrenceTime]------------------------------*/

FUNC(Dem_ReturnGetDTCByOccurrenceTimeType, DEM_CODE)
  Dem_GetDTCByOccurrenceTime(
    Dem_DTCRequestType                           DTCRequest,
    P2VAR(Dem_DTCType, AUTOMATIC, DEM_APPL_DATA) DTC)
{
  Dem_ReturnGetDTCByOccurrenceTimeType result = DEM_OCCURR_NOT_AVAILABLE;

  DBG_DEM_GETDTCBYOCCURRENCETIME_ENTRY(DTCRequest, DTC);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetDTCByOccurrenceTime, DEM_E_UNINIT);
  }
  else if ( ( ( (DTCRequest != DEM_FIRST_FAILED_DTC) &&
                (DTCRequest != DEM_MOST_RECENT_FAILED_DTC) ) &&
              (DTCRequest != DEM_FIRST_DET_CONFIRMED_DTC) ) &&
            (DTCRequest != DEM_MOST_REC_DET_CONFIRMED_DTC) )
  {
    DEM_REPORT_ERROR(DEM_SID_GetDTCByOccurrenceTime, DEM_E_PARAM_DATA);
  }
  else if (DTC == NULL_PTR)
  {
    DEM_REPORT_ERROR(
      DEM_SID_GetDTCByOccurrenceTime, DEM_E_PARAM_POINTER);
  }
  else
#else
  TS_PARAM_UNUSED(DTCRequest);
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* Function NOT fully implemented yet.
     * Implementation is scheduled for future releases. */

    *DTC = 0U; /* invalid DTC */
  }

  DBG_DEM_GETDTCBYOCCURRENCETIME_EXIT(result, DTCRequest, DTC);
  return result;
}

/*----------------[Dem_GetNextFilteredRecord]-------------------------------*/

FUNC(Dem_ReturnGetNextFilteredDTCType, DEM_CODE) Dem_GetNextFilteredRecord(
  P2VAR(Dem_DTCType, AUTOMATIC, DEM_APPL_DATA) DTC,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)       RecordNumber)
{
  Dem_ReturnGetNextFilteredDTCType result = DEM_FILTERED_NO_MATCHING_DTC;

  DBG_DEM_GETNEXTFILTEREDRECORD_ENTRY(DTC, RecordNumber);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetNextFilteredRecord, DEM_E_UNINIT);
  }
  else if (DTC == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetNextFilteredRecord, DEM_E_PARAM_POINTER);
  }
  else if (RecordNumber == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetNextFilteredRecord, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* quoting SWS: "This filter always belongs to primary memory." */
    const Dem_SizeEvMemEntryType sizeEventMem = Dem_SizeEventMem[0];

    const Dem_EventMemoryEntryPtrType Entry = Dem_EventMem[0];

    Dem_FFIdxType NumStoredFFs;
    Dem_EventIdType EventId;
    Dem_DTCType DTCValue;
    Dem_EventMemoryEntryPtrType EvMemEntry;
    Dem_FFIdxType MaxNumFF = 0U;

    /* if Dcm disables DTCRecordUpdate while retrieving all records by subsequent
     * API-calls, data can not get inconsistent */

    /*
     * signal access of event memory
     */
    Dem_EvMemReadAccessSemaphore++;

    /* search for event memory entry, which contains the next record */
    while (Dem_RecordFilterEntryIdx < sizeEventMem)
    {
      EventId = Entry[Dem_RecordFilterEntryIdx].EventId;

      if (EventId != (Dem_EventIdType)DEM_EVENT_ID_INVALID)
      {
        DTCValue = Dem_GbiDTC(EventId);

        if (DTCValue != 0U)
        {
#if (DEM_NUM_FFSEGS > 0U)
          MaxNumFF = Dem_GbiMaxNumFFRecs(EventId);
#endif
          EvMemEntry = &Entry[Dem_RecordFilterEntryIdx];
          NumStoredFFs = (Dem_FFIdxType)DEM_NUMFF(EvMemEntry, MaxNumFF);

          if (NumStoredFFs > Dem_RecordFilterRecNumIdx)
          {
            /* event memory entry with demanded freeze frame record reached */

            *DTC = DTCValue;

            /* calculate FF record number (relative addressing) */
#if (DEM_FREEZE_FRAME_REC_NUMERATION_TYPE == DEM_FF_RECNUM_CALCULATED)
            *RecordNumber = Dem_RecordFilterRecNumIdx + 1U;
#else
            *RecordNumber =
              Dem_FFRecNumerationClass[Dem_GbiFFRecNumClassIdx(EventId)].
                Dem_FFRecNumClassIdx[Dem_RecordFilterRecNumIdx];
#endif

            Dem_RecordFilterRecNumIdx++;

            result = DEM_FILTERED_OK;
            break;
          }
        }
      }

      Dem_RecordFilterEntryIdx++;
      Dem_RecordFilterRecNumIdx = 0U;
    }

    /*
     * signal access of event memory finished
     */
    Dem_EvMemReadAccessSemaphore--;
  }

  DBG_DEM_GETNEXTFILTEREDRECORD_EXIT(result, DTC, RecordNumber);
  return result;
}

/*----------------[Dem_GetNextFilteredDTCAndFDC]----------------------------*/

FUNC(Dem_ReturnGetNextFilteredDTCType, DEM_CODE) Dem_GetNextFilteredDTCAndFDC(
  P2VAR(Dem_DTCType, AUTOMATIC, DEM_APPL_DATA) DTC,
  P2VAR(Dem_FaultDetectionCounterType, AUTOMATIC, DEM_APPL_DATA)
    DTCFaultDetectionCounter)
{
  Dem_ReturnGetNextFilteredDTCType result = DEM_FILTERED_NO_MATCHING_DTC;

  DBG_DEM_GETNEXTFILTEREDDTCANDFDC_ENTRY(DTC, DTCFaultDetectionCounter);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetNextFilteredDTCAndFDC, DEM_E_UNINIT);
  }
  else if ( (DTC == NULL_PTR) || (DTCFaultDetectionCounter == NULL_PTR) )
  {
    DEM_REPORT_ERROR(DEM_SID_GetNextFilteredDTCAndFDC, DEM_E_PARAM_POINTER);
  }
  else if (Dem_DTCFilter.FilterForFDC == DEM_FILTER_FOR_FDC_NO)
  {
    /* API was called while FDC-filtering is inactive (not sensible)
     * -> this API is not functional by optimization, as FDC information would
     *    not be retrieved and be returned bogus by Dem_ApplyDTCFilter() */
    DEM_REPORT_ERROR(DEM_SID_GetNextFilteredDTCAndFDC, DEM_E_WRONG_CONDITION);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
      boolean filterresult = FALSE;

    /* Function NOT fully implemented yet.
     * Filter criteria related to DTCFormat and DTCKind is not implemented
     * since there is no OBD support.
     * Implementation is scheduled for future releases. */

    /* search for first DTC fulfilling the filter criterion */
    while ( (Dem_DTCFilter.NextEventId <= DEM_MAX_EVENTID) &&
            (filterresult == FALSE)
          )
    {
      Dem_DTCStatusMaskType idleDTCStatus; /* status not needed this time */

      filterresult = Dem_ApplyDTCFilter(
        (Dem_EventIdType)Dem_DTCFilter.NextEventId,
        &idleDTCStatus,
        DTCFaultDetectionCounter);

      /* skip events not matching the filter criterion */
      if (filterresult == TRUE)
      {
        /* return DTC */
        *DTC = Dem_GbiDTC((Dem_EventIdType)Dem_DTCFilter.NextEventId);

        /* next matching DTC found */
        result = DEM_FILTERED_OK;
      }

      /* store event id for next call in filter */
      ++Dem_DTCFilter.NextEventId;
    }
  }

  DBG_DEM_GETNEXTFILTEREDDTCANDFDC_EXIT(
    result, DTC, DTCFaultDetectionCounter);
  return result;
}

/*----------------[Dem_GetNextFilteredDTCAndSeverity]-----------------------*/

/* !LINKSTO Dem281,2 */
FUNC(Dem_ReturnGetNextFilteredDTCType, DEM_CODE)
  Dem_GetNextFilteredDTCAndSeverity(
    P2VAR(Dem_DTCType, AUTOMATIC, DEM_APPL_DATA)         DTC,
    P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)               DTCStatus,
    P2VAR(Dem_DTCSeverityType, AUTOMATIC, DEM_APPL_DATA) DTCSeverity,
    P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)               DTCFunctionalUnit)
{
  Dem_ReturnGetNextFilteredDTCType result = DEM_FILTERED_NO_MATCHING_DTC;

  DBG_DEM_GETNEXTFILTEREDDTCANDSEVERITY_ENTRY(
    DTC, DTCStatus, DTCSeverity, DTCFunctionalUnit);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetNextFilteredDTCAndSeverity, DEM_E_UNINIT);
  }
  else if (DTC == NULL_PTR)
  {
    DEM_REPORT_ERROR(
      DEM_SID_GetNextFilteredDTCAndSeverity, DEM_E_PARAM_POINTER);
  }
  else if (DTCStatus == NULL_PTR)
  {
    DEM_REPORT_ERROR(
      DEM_SID_GetNextFilteredDTCAndSeverity, DEM_E_PARAM_POINTER);
  }
  else if (DTCSeverity == NULL_PTR)
  {
    DEM_REPORT_ERROR(
      DEM_SID_GetNextFilteredDTCAndSeverity, DEM_E_PARAM_POINTER);
  }
  else if (DTCFunctionalUnit == NULL_PTR)
  {
    DEM_REPORT_ERROR(
      DEM_SID_GetNextFilteredDTCAndSeverity, DEM_E_PARAM_POINTER);
  }
  else if (Dem_DTCFilter.FilterWithSeverity == DEM_FILTER_WITH_SEVERITY_NO)
  {
    /* API was called while severity-filtering is inactive
     * (functional, but not sensible) */
    DEM_REPORT_ERROR(
      DEM_SID_GetNextFilteredDTCAndSeverity, DEM_E_WRONG_CONDITION);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    boolean filterresult = FALSE;

    /* Function NOT fully implemented yet.
     * Filter criteria related to DTCFormat and DTCKind is not implemented
     * since there is no OBD support.
     * Implementation is scheduled for future releases. */

    /* search for first DTC fulfilling the filter criterion */
    while ( (Dem_DTCFilter.NextEventId <= DEM_MAX_EVENTID) &&
            (filterresult == FALSE)
          )
    {
      Dem_FaultDetectionCounterType idleFDC; /* FDC not needed this time */

      filterresult = Dem_ApplyDTCFilter(
        (Dem_EventIdType)Dem_DTCFilter.NextEventId, DTCStatus, &idleFDC);

      /* skip events not matching the filter criterion */
      if (filterresult == TRUE)
      {
        /* return DTC */
        *DTC = Dem_GbiDTC((Dem_EventIdType)Dem_DTCFilter.NextEventId);

#if (DEM_DTC_STATUS_AVAILABILITY_MASK == 0U)
        *DTCStatus = 0U;
#elif (DEM_DTC_STATUS_AVAILABILITY_MASK != 255U)
        /* mask out unsupported bits in DTC status */
        *DTCStatus &= DEM_DTC_STATUS_AVAILABILITY_MASK;
#else
        /* DTCStatus is fully available */
#endif

        /* get the severity mapped to event Id */
        *DTCSeverity =
          Dem_GbiDTCSeverity((Dem_EventIdType)Dem_DTCFilter.NextEventId);
        /* get the functional unit mapped to event Id */
        *DTCFunctionalUnit =
          Dem_GbiDTCFunctionalUnit((Dem_EventIdType)Dem_DTCFilter.NextEventId);

       /* next matching DTC found */
        result = DEM_FILTERED_OK;
      }

      /* store event id for next call in filter */
      ++Dem_DTCFilter.NextEventId;
    }
  }

  DBG_DEM_GETNEXTFILTEREDDTCANDSEVERITY_EXIT(
    result, DTC, DTCStatus, DTCSeverity, DTCFunctionalUnit);
  return result;
}

/*----------------[Dem_GetTranslationType]----------------------------------*/

FUNC(Dem_DTCTranslationFormatType, DEM_CODE) Dem_GetTranslationType(void)
{
  DBG_DEM_GETTRANSLATIONTYPE_ENTRY();

  /* DEM_DEV_ERROR_DETECT: */
  /* check of Dem_InitializationState is not necessary:
   * it's allowed to get severity even if Dem is uninitialized */

  DBG_DEM_GETTRANSLATIONTYPE_EXIT(DEM_TYPE_OF_DTC_SUPPORTED);
  return DEM_TYPE_OF_DTC_SUPPORTED;
}

/*----------------[Dem_GetSeverityOfDTC]------------------------------------*/

FUNC(Dem_ReturnGetSeverityOfDTCType, DEM_CODE) Dem_GetSeverityOfDTC(
  Dem_DTCType                                          DTC,
  P2VAR(Dem_DTCSeverityType, AUTOMATIC, DEM_APPL_DATA) DTCSeverity)
{
  Dem_ReturnGetSeverityOfDTCType result = DEM_GET_SEVERITYOFDTC_WRONG_DTC;

  DBG_DEM_GETSEVERITYOFDTC_ENTRY(DTC, DTCSeverity);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* check of Dem_InitializationState is not necessary:
   * it's allowed to get severity even if Dem is uninitialized */

  if ( (DTC == (Dem_DTCType)0U) || (DTC > (Dem_DTCType)0xFFFFFFU) )
  {
    DEM_REPORT_ERROR(DEM_SID_GetSeverityOfDTC, DEM_E_PARAM_DATA);
  }
  else if (DTCSeverity == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetSeverityOfDTC, DEM_E_PARAM_POINTER);
    result = DEM_GET_SEVERITYOFDTC_NOSEVERITY;
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    Dem_EvIdLeastType EvId = 1U; /* invalid event Id 0 is skipped */

    /* search for event Id of unique DTC */
    /* check EvId first (left-hand), before using it (right-hand) */
    while ( (EvId <= DEM_MAX_EVENTID) &&
            /* Deviation MISRA-1 <+2> */
            (DTC != Dem_GbiDTC((Dem_EventIdType)EvId))
          )
    {
      ++EvId;
    }

    if (EvId <= DEM_MAX_EVENTID)
    {
      /* get the severity mapped to event Id */
      *DTCSeverity = Dem_GbiDTCSeverity((Dem_EventIdType)EvId);

      result = DEM_GET_SEVERITYOFDTC_OK;
    }
  }

  DBG_DEM_GETSEVERITYOFDTC_EXIT(result, DTC, DTCSeverity);
  return result;
}

/*------------------[Dem_GetFunctionalUnitOfDTC]----------------------------*/

FUNC(Dem_ReturnGetFunctionalUnitOfDTCType, DEM_CODE)
  Dem_GetFunctionalUnitOfDTC(
    Dem_DTCType                            DTC,
    P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) DTCFunctionalUnit)
{
  Dem_ReturnGetFunctionalUnitOfDTCType result =
    DEM_GET_FUNCTIONALUNITOFDTC_WRONG_DTC;

  DBG_DEM_GETFUNCTIONALUNITOFDTC_ENTRY(DTC, DTCFunctionalUnit);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* check of Dem_InitializationState is not necessary:
   * it's allowed to get functional unit even if Dem is uninitialized */

  if ( (DTC == (Dem_DTCType)0U) || (DTC > (Dem_DTCType)0xFFFFFFU) )
  {
    DEM_REPORT_ERROR(DEM_SID_GetFunctionalUnitOfDTC, DEM_E_PARAM_DATA);
  }
  else if (DTCFunctionalUnit == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetFunctionalUnitOfDTC, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    Dem_EvIdLeastType EvId = 1U; /* invalid event Id 0 is skipped */

    /* search for event Id of unique DTC */
    /* check EvId first (left-hand), before using it (right-hand) */
    while ( (EvId <= DEM_MAX_EVENTID) &&
            /* Deviation MISRA-1 <+2> */
            (DTC != Dem_GbiDTC((Dem_EventIdType)EvId))
          )
    {
      ++EvId;
    }

    if (EvId <= DEM_MAX_EVENTID)
    {
      /* get the functional unit mapped to event Id */
      *DTCFunctionalUnit = Dem_GbiDTCFunctionalUnit((Dem_EventIdType)EvId);

      result = DEM_GET_FUNCTIONALUNITOFDTC_OK;
    }
  }

  DBG_DEM_GETFUNCTIONALUNITOFDTC_EXIT(result, DTC, DTCFunctionalUnit);
  return result;
}

#define DEM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function definitions]=========================*/

#define DEM_START_SEC_CODE
#include <MemMap.h>

STATIC FUNC(boolean, DEM_CODE) Dem_ApplyDTCFilter(
  Dem_EventIdType                                                EventId,
  P2VAR(Dem_DTCStatusMaskType, AUTOMATIC, DEM_APPL_DATA)         DTCStatus,
  P2VAR(Dem_FaultDetectionCounterType, AUTOMATIC, DEM_APPL_DATA) FDC)
{
  boolean result = FALSE;

  DBG_DEM_APPLYDTCFILTER_ENTRY(EventId, DTCStatus, FDC);

  /* Function NOT fully implemented yet.
   * Filter criteria related to DTCFormat and DTCKind is not implemented
   * since there is no OBD support.
   * Implementation is scheduled for future releases. */

  /* check if DTC format set is 'UDS', as the current
   * implementation supports only non OBD-relevant ECUs. */
  if (Dem_DTCFilter.DTCFormat == DEM_DTC_FORMAT_UDS)
  {
    /* check if a DTC is associated with the given event */
    if (Dem_GbiDTC(EventId) != 0U)
    {
      /* access DTC status only once centrally to ensure consistent value for
       * that filter services, which return this value */
      *DTCStatus = DEM_DTC_STATUS_MASKS[EventId];

      /* apply all filter-criteria (Dem SWS 8.3.4.1.1) */

      /* filter for DTCStatusMask */
      if ( (Dem_DTCFilter.DTCStatusMask == 0U) ||
           ((Dem_DTCFilter.DTCStatusMask & *DTCStatus) != 0U)
         )
      {
        /* filter for DTCOrigin */
        if (Dem_DTCFilter.DTCOrigin == Dem_GbiDTCOrigin(EventId))
        {
          /* filter for DTCSeverity as mask */
          if ( (Dem_DTCFilter.FilterWithSeverity == DEM_FILTER_WITH_SEVERITY_NO) ||
                 /* to handle DEM_SEVERITY_NO_SEVERITY */
               /* Deviation MISRA-1 <+4>*/
               ( (Dem_DTCFilter.DTCSeverityMask == Dem_GbiDTCSeverity(EventId)) ||
                 ( (Dem_DTCFilter.DTCSeverityMask & Dem_GbiDTCSeverity(EventId)) != 0U )
               )
             )
          {
            /* filter for fault detection counter */
            if (Dem_DTCFilter.FilterForFDC == DEM_FILTER_FOR_FDC_NO)
            {
              /* filter-criteria matched to event */
              result = TRUE;
            }
            else
            {
              Std_ReturnType ret = E_NOT_OK;

              if (Dem_DebounceFctPtrTable[Dem_GbiDebounceAlgo(EventId)].
                    GetFDCFct != NULL_PTR)
              {
                ret = Dem_DebounceFctPtrTable[Dem_GbiDebounceAlgo(EventId)].
                  GetFDCFct(EventId, FDC);
              }

              /* fault detection counter filter criteria:
               * FDC must between 1 and 0x7E (inclusive) - this means all
               * DTCs where debouncing is in PREFAILED (but not yet FAILED)
               * stage will be returned by the filter.
               * (Dem SWS 8.3.4.1.1, ISO 14229-1:2006 Table 258) */

              /* note that Dem_FaultDetectionCounterType is signed! */
              if ( (ret == E_OK) && ( (1 <= *FDC) && (*FDC <= 126) ) )
              {
                /* filter-criteria matched to event */
                result = TRUE;
              }
            } /* FDC */
          } /* DTCSeverity */
        } /* DTCOrigin */
      } /* DTCStatus */
    } /* DTC */
  } /* DTCFormat */

  DBG_DEM_APPLYDTCFILTER_EXIT(result, EventId, DTCStatus, FDC);
  return result;
}

#define DEM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[end of file]===========================================*/
