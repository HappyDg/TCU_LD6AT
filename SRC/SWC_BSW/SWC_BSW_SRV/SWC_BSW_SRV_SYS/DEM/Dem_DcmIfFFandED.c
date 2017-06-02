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
 * the Dcm for the access of extended data records and freeze frame data. */

/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 17.4 (required)
 *    "Array indexing shall be the only allowed form of pointer arithmetic."
 *
 *    Reason:
 *    In special cases pointer arithmetic is more efficient in run
 *    time and/or code size.
 *
 *  MISRA-2) Deviated Rule: 12.4 (required)
 *    "The right-hand operand of a logical '&&' or '||' operator shall not
 *    contain side effects."
 *
 *    Reason:
 *    Call to getter functions which do not modify any global state.
 *
 *  MISRA-3) Deviated Rule: 16.7 (required)
 *    "A pointer parameter in a function prototype should be declared as
 *     pointer to const if the pointer is not used to modify the
 *     addressed object."
 *
 *    Reason:
 *    Pointer parameter is not modified in some configuration variants
 *    or functionality is not currently implemented.
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

/*==================[macros]================================================*/

#if (defined DEM_HIBYTE)
#error DEM_HIBYTE already defined
#endif
/** \brief Macro to get hi-byte of an uint16 */
#define DEM_HIBYTE(a) ((uint8)((a) >> 8U))

#if (defined DEM_LOBYTE)
#error DEM_LOBYTE already defined
#endif
/** \brief Macro to get low-byte of an uint16 */
#define DEM_LOBYTE(a) ((uint8)((a) & (uint16)0xFFU))

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

#define DEM_START_SEC_CODE
#include <MemMap.h>

#if (DEM_NUM_FFSEGS > 0U)
/** \brief Function to copy one or all freeze frame segment data Ids and
 ** values into the destination buffer
 **
 ** \param[in] DestBuffer
 ** \param[in] EventMemoryEntry
 ** \param[in] FFClass
 ** \param[in] RecIndex  0 <= RecIndex < NumFF
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 **
 */
STATIC FUNC(void, DEM_CODE) Dem_CopyFFInfo(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)              DestBuffer,
  const Dem_EventMemoryEntryPtrConstType              EventMemoryEntry,
  CONSTP2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) FFClass,
  uint8                                               RecIndex);
#endif

#if (DEM_NUM_EDSEGS > 0U)
/** \brief Function to copy the ED informations of one record to the
 ** destination buffer
 **
 ** \param[in] EDClass
 ** \param[in] ExtendedDataNumber  0x01 <= ExtendedDataNumber <= 0xEF
 ** \param[in] EventMemoryEntry
 ** \param[out] DestBuffer
 ** \param[in,out] BufSize
 **
 ** \return Status of the operation of type
 **            Dem_ReturnGetExtendedDataRecordByDTCType
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Dem_ReturnGetExtendedDataRecordByDTCType, DEM_CODE)
  Dem_GetOneEDRecord(
    P2CONST(Dem_EDClassType, AUTOMATIC, DEM_CONST) EDClass,
    uint8                                          ExtendedDataNumber,
    Dem_EventMemoryEntryPtrConstType               EventMemoryEntry,
    P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)         DestBuffer,
    P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)        BufSize);
#endif

#define DEM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief Lock for Dcm and FF/ED getter function access */
VAR(uint8, DEM_VAR_NOINIT) Dem_EvMemReadAccessSemaphore;

/** \brief Event corresponding to record update disabled DTC */
VAR(Dem_EventIdType, DEM_VAR_NOINIT) Dem_EvIdOfRecordUpdateDisabledDTC;

#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

#define DEM_START_SEC_CODE
#include <MemMap.h>

/*---------------------[Dem_DisableDTCRecordUpdate]-------------------------*/

FUNC(Dem_ReturnDisableDTCRecordUpdateType, DEM_CODE)
  Dem_DisableDTCRecordUpdate(
    Dem_DTCType       DTC,
    Dem_DTCOriginType DTCOrigin)
{
  Dem_ReturnDisableDTCRecordUpdateType result = DEM_DISABLE_DTCRECUP_WRONG_DTC;

  DBG_DEM_DISABLEDTCRECORDUPDATE_ENTRY(DTC, DTCOrigin);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_DisableDTCRecordUpdate, DEM_E_UNINIT);
  }
  else if ((DTC == (Dem_DTCType)0U) || (DTC > (Dem_DTCType)0xFFFFFFU))
  {
    DEM_REPORT_ERROR(DEM_SID_DisableDTCRecordUpdate, DEM_E_PARAM_DATA);
  }
  else if ( ( ( (DTCOrigin != DEM_DTC_ORIGIN_PRIMARY_MEMORY) &&
                (DTCOrigin != DEM_DTC_ORIGIN_SECONDARY_MEMORY) ) &&
              (DTCOrigin != DEM_DTC_ORIGIN_MIRROR_MEMORY) ) &&
            (DTCOrigin != DEM_DTC_ORIGIN_PERMANENT_MEMORY)
          )
  {
    DEM_REPORT_ERROR(DEM_SID_DisableDTCRecordUpdate, DEM_E_PARAM_DATA);
    result = DEM_DISABLE_DTCRECUP_WRONG_DTCORIGIN;
  }
  else if (Dem_EvIdOfRecordUpdateDisabledDTC != DEM_EVENT_ID_INVALID)
  {
    /* !LINKSTO Dem648,1 */
    DEM_REPORT_ERROR(DEM_SID_DisableDTCRecordUpdate, DEM_E_WRONG_CONDITION);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* !LINKSTO Dem270,2 */
    Dem_EventIdType EventId;

    /* search event Id by DTC and map return value */
    switch (Dem_GetEvIdByDTC(DTC, DEM_DTC_FORMAT_UDS, DTCOrigin, &EventId))
    {
      case DEM_EIBD_OK:
        Dem_EvIdOfRecordUpdateDisabledDTC = EventId;
        result = DEM_DISABLE_DTCRECUP_OK;
        break;
      case DEM_EIBD_WRONG_DTC:
        /* result remains DEM_DISABLE_DTCRECUP_WRONG_DTC */
        break;
      case DEM_EIBD_WRONG_DTCORIGIN:
        result = DEM_DISABLE_DTCRECUP_WRONG_DTCORIGIN;
        break;
      /* CHECK: NOPARSE */
      default: /* should never be reached */
        DEM_UNREACHABLE_CODE_ASSERT(DEM_SID_DisableDTCRecordUpdate);
        /* result remains DEM_DISABLE_DTCRECUP_WRONG_DTC */
        break;
      /* CHECK: PARSE */
    }
  }

  DBG_DEM_DISABLEDTCRECORDUPDATE_EXIT(result, DTC, DTCOrigin);
  return result;
}

/*---------------------[Dem_EnableDTCRecordUpdate]--------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_EnableDTCRecordUpdate(void)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_ENABLEDTCRECORDUPDATE_ENTRY();

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_EnableDTCRecordUpdate, DEM_E_UNINIT);
  }
  /* Dem_EvIdOfRecordUpdateDisabledDTC == DEM_EVENT_ID_INVALID does not lead
   * to DEM_E_WRONG_CONDITION, because the implementation handles this
   * condition via defensive programming during (re-)enabling */
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
#if (DEM_USE_AGING == STD_ON)
    const Dem_EventIdType LockedEvId = Dem_EvIdOfRecordUpdateDisabledDTC;
#endif /* DEM_USE_AGING */

    /* !LINKSTO Dem271,3 */
    Dem_EvIdOfRecordUpdateDisabledDTC = DEM_EVENT_ID_INVALID;

#if (DEM_USE_AGING == STD_ON)
    /* clear disabled event from event memory if it was aged */
    /* Deviation MISRA-2 */
    if ((LockedEvId != DEM_EVENT_ID_INVALID) && DEM_AGING_ALLOWED(LockedEvId))
    {
      Dem_EventMemoryEntryPtrType EvMemEntry;
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
      Dem_SizeEvMemEntryType EvMemEntryIdx;
      const uint8 originIdx = Dem_GbiDTCOriginIdx(LockedEvId);
      Dem_NvMGatePrepStatusType NvMGateStatus;
#endif
#if ( (DEM_USE_CB_TRIG_ON_EVST == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) )
      Dem_DTCStatusMaskType OldDTCStatusMask = 0U;
      Dem_DTCStatusMaskType NewDTCStatusMask = 0U;
#endif

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
      /* try to lock gate entry */
      NvMGateStatus = Dem_BeginPrepareGateEntry(originIdx);
#endif

      /*
       * ENTER critical section to protect the event memory entry
       *       call-context: Dcm (Task)
       */
      SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
      if (Dem_SearchForEntry(LockedEvId, &EvMemEntry, &EvMemEntryIdx) == TRUE)
#else
      if (Dem_SearchForEntry(LockedEvId, &EvMemEntry, NULL_PTR) == TRUE)
#endif
      {
        /* pointer to internal aging value */
        const Dem_EntryDataPtrType AgingCounter =
          Dem_IntValEntryData(EvMemEntry);

        if (*AgingCounter == 0U)
        {
#if ( (DEM_USE_CB_TRIG_ON_EVST == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) )
          OldDTCStatusMask = DEM_DTC_STATUS_MASKS[LockedEvId];
#endif

          Dem_ClearAgedEventEntry(LockedEvId, EvMemEntry);

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
          Dem_CheckForImmediateEntryStorage(LockedEvId,
                                            EvMemEntry,
                                            EvMemEntryIdx,
                                            DEM_NVM_NO_FORCE,
                                            &NvMGateStatus);
#endif

#if ( (DEM_USE_CB_TRIG_ON_EVST == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) )
          NewDTCStatusMask = DEM_DTC_STATUS_MASKS[LockedEvId];
#endif
        }
      }

      /*
       * LEAVE critical section
       */
      SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

#if ( (DEM_USE_CB_TRIG_ON_EVST == STD_ON) || \
      (DEM_USE_CB_TRIG_ON_DTCST == STD_ON) )
      if (OldDTCStatusMask != NewDTCStatusMask)
      {
        Dem_CbTriggerOnEventStatus(
          LockedEvId, OldDTCStatusMask, NewDTCStatusMask);
      }
#endif

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
      /* unlock gate entry */
      Dem_EndPrepareGateEntry(originIdx, NvMGateStatus);

      if (DEM_GATE_PREPARED == NvMGateStatus)
      {
        Dem_TriggerNvmWriteGateEntry();
      }
#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */
    }
#endif /* DEM_USE_AGING */

    result = E_OK;
  }

  DBG_DEM_ENABLEDTCRECORDUPDATE_EXIT(result);
  return result;
}

/*---------------------[Dem_GetFreezeFrameDataByRecord]---------------------*/

FUNC(Dem_ReturnGetFreezeFrameDataByRecordType, DEM_CODE)
  Dem_GetFreezeFrameDataByRecord(
    uint8                                        RecordNumber,
    Dem_DTCOriginType                            DTCOrigin,
    P2VAR(Dem_DTCType, AUTOMATIC, DEM_APPL_DATA) DTC,
    /* Deviation MISRA-3 <+2> */
    P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)       DestBuffer,
    P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)      BufSize)
{
  Dem_ReturnGetFreezeFrameDataByRecordType result =
    DEM_GET_FFBYRECORD_WRONG_RECORD;

  DBG_DEM_GETFREEZEFRAMEDATABYRECORD_ENTRY(
    RecordNumber, DTCOrigin, DTC, DestBuffer, BufSize);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetFreezeFrameDataByRecord, DEM_E_UNINIT);
  }
  else if (RecordNumber == 0xFFU)
  {
    DEM_REPORT_ERROR(DEM_SID_GetFreezeFrameDataByRecord, DEM_E_PARAM_DATA);
  }
  else if ( ( ( (DTCOrigin != DEM_DTC_ORIGIN_PRIMARY_MEMORY) &&
                (DTCOrigin != DEM_DTC_ORIGIN_SECONDARY_MEMORY) ) &&
              (DTCOrigin != DEM_DTC_ORIGIN_MIRROR_MEMORY) ) &&
            (DTCOrigin != DEM_DTC_ORIGIN_PERMANENT_MEMORY)
          )
  {
    DEM_REPORT_ERROR(DEM_SID_GetFreezeFrameDataByRecord, DEM_E_PARAM_DATA);
  }
  else if (DTC == NULL_PTR)
  {
    DEM_REPORT_ERROR(
      DEM_SID_GetFreezeFrameDataByRecord, DEM_E_PARAM_POINTER);
  }
  else if (DestBuffer == NULL_PTR)
  {
    DEM_REPORT_ERROR(
      DEM_SID_GetFreezeFrameDataByRecord, DEM_E_PARAM_POINTER);
  }
  else if (BufSize == NULL_PTR)
  {
    DEM_REPORT_ERROR(
      DEM_SID_GetFreezeFrameDataByRecord, DEM_E_PARAM_POINTER);
  }
  else
#else /* DEM_DEV_ERROR_DETECT */
  TS_PARAM_UNUSED(RecordNumber);
  TS_PARAM_UNUSED(DTCOrigin);
  TS_PARAM_UNUSED(DestBuffer);
  TS_PARAM_UNUSED(BufSize);
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* Function NOT fully implemented yet.
     * Implementation is scheduled for future releases. */
    *DTC = 0U; /* invalid DTC */
  }

  DBG_DEM_GETFREEZEFRAMEDATABYRECORD_EXIT(
    result, RecordNumber, DTCOrigin, DTC, DestBuffer, BufSize);
  return result;
}

/*---------------------[Dem_GetFreezeFrameDataByDTC]------------------------*/

FUNC(Dem_ReturnGetFreezeFrameDataByDTCType, DEM_CODE)
  Dem_GetFreezeFrameDataByDTC(
    Dem_DTCType                             DTC,
    Dem_DTCOriginType                       DTCOrigin,
    uint8                                   RecordNumber,
    /* Deviation MISRA-3 <+2> */
    P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,
    P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) BufSize)
{
  Dem_ReturnGetFreezeFrameDataByDTCType result;

  DBG_DEM_GETFREEZEFRAMEDATABYDTC_ENTRY(
    DTC, DTCOrigin, RecordNumber, DestBuffer, BufSize);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetFreezeFrameDataByDTC, DEM_E_UNINIT);
    result = DEM_GET_FFDATABYDTC_WRONG_DTC;
  }
  else if ((DTC == (Dem_DTCType)0U) || (DTC > (Dem_DTCType)0xFFFFFFU))
  {
    DEM_REPORT_ERROR(DEM_SID_GetFreezeFrameDataByDTC, DEM_E_PARAM_DATA);
    result = DEM_GET_FFDATABYDTC_WRONG_DTC;
  }
  else if ( ( ( (DTCOrigin != DEM_DTC_ORIGIN_PRIMARY_MEMORY) &&
                (DTCOrigin != DEM_DTC_ORIGIN_SECONDARY_MEMORY) ) &&
              (DTCOrigin != DEM_DTC_ORIGIN_MIRROR_MEMORY) ) &&
            (DTCOrigin != DEM_DTC_ORIGIN_PERMANENT_MEMORY)
          )
  {
    DEM_REPORT_ERROR(DEM_SID_GetFreezeFrameDataByDTC, DEM_E_PARAM_DATA);
    result = DEM_GET_FFDATABYDTC_WRONG_DTCORIGIN;
  }
  else if (RecordNumber == 0xFFU)
  {
    DEM_REPORT_ERROR(DEM_SID_GetFreezeFrameDataByDTC, DEM_E_PARAM_DATA);
    result = DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER;
  }
  else if (BufSize == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetFreezeFrameDataByDTC, DEM_E_PARAM_POINTER);
    result = DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE;
  }
  else if (DestBuffer == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetFreezeFrameDataByDTC, DEM_E_PARAM_POINTER);
    result = DEM_GET_FFDATABYDTC_WRONG_DTC;
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    Dem_EventIdType EventId;

    /* search event Id by DTC and map return value.
     * DTCFormat is passed as DEM_DTC_FORMAT_UDS, since the API supports only
     * DTC in UDS format (Dem SWS 8.3.4.2.4). */
    switch (Dem_GetEvIdByDTC(DTC, DEM_DTC_FORMAT_UDS, DTCOrigin, &EventId))
    {
      case DEM_EIBD_OK:
#if (DEM_NUM_FFSEGS > 0U)
        result = DEM_GET_FFDATABYDTC_OK;
#else
        result = DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER;
#endif
        break;
      case DEM_EIBD_WRONG_DTC:
        result = DEM_GET_FFDATABYDTC_WRONG_DTC;
        break;
      case DEM_EIBD_WRONG_DTCORIGIN:
        result = DEM_GET_FFDATABYDTC_WRONG_DTCORIGIN;
        break;
      /* CHECK: NOPARSE */
      default: /* should never be reached */
        DEM_UNREACHABLE_CODE_ASSERT(DEM_SID_GetFreezeFrameDataByDTC);
        result = DEM_GET_FFDATABYDTC_WRONG_DTC;
        break;
      /* CHECK: PARSE */
    }

#if (DEM_NUM_FFSEGS > 0U)
    if (result == DEM_GET_FFDATABYDTC_OK)
    {
      Dem_EventMemoryEntryPtrType EvMemEntry;
      boolean EntryExists;

      /* get freeze frame class layout */
      CONSTP2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) FFClass =
        &Dem_FFClass[Dem_GbiFFClassIdx(EventId)];

      const Dem_FFIdxType MaxNumFF = Dem_GbiMaxNumFFRecs(EventId);
      const uint16 SizeFFInfo      =
        ((uint16)Dem_SizeOfFF(FFClass) + (2U * (uint16)(FFClass->NumFFSegs)));
      Dem_FFIdxType FFIndex = 0U;

      /*
       * ENTER critical section to protect the event memory entry
       *       call-context: Dcm (Task)
       */
      SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

      /* search for DTC in event memory */
      EntryExists = Dem_SearchForEntry(EventId, &EvMemEntry, NULL_PTR);

#if (DEM_FREEZE_FRAME_REC_NUMERATION_TYPE == DEM_FF_RECNUM_CALCULATED)
      FFIndex = RecordNumber - 1U;
#else
      if (EntryExists)
      {
        FFIndex = Dem_CheckFFRecNumStored(EvMemEntry, RecordNumber);
      }
#endif

      /* check whether the record number is valid */
#if (DEM_FREEZE_FRAME_REC_NUMERATION_TYPE == DEM_FF_RECNUM_CALCULATED)
      if ((RecordNumber > MaxNumFF) || (RecordNumber == 0U))
#else
      if (Dem_CheckFFRecNumValid( EventId, RecordNumber ) != TRUE)
#endif
      {
        /* one non-existing record requested: return "out of range" */
        result = DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER;
      }
      else if (!(EntryExists))
      {
        /* No DTC stored, return empty buffer */
        *BufSize = 0U;
      }
      /* only one FF requested and record number is valid and stored */
      else if (FFIndex < DEM_NUMFF(EvMemEntry, MaxNumFF))
      {
        /* calculate needed buffer size */
        const Dem_SizeEntryDataType NeededSize = 2U + SizeFFInfo;

        if (NeededSize <= *BufSize)
        {
          /* write data for one record: */
          /*  byte 0: record number */
          DestBuffer[0] = RecordNumber;
          /*  byte 1: number of segments */
          DestBuffer[1] = FFClass->NumFFSegs;
          /*  byte 2-n: freeze frames */
          Dem_CopyFFInfo(&DestBuffer[2], EvMemEntry, FFClass, FFIndex);

          *BufSize = NeededSize;
        }
        else /* destination buffer is too small */
        {
          result = DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE;
        }
      }
      else /* only one FF requested; valid record number, but FF not stored */
      {
        /* !LINKSTO Dem630,1 return DEM_GET_FFDATABYDTC_OK and BufSize 0 */
        *BufSize = 0U;
        /* result remains DEM_GET_FFDATABYDTC_OK */
      }

      /*
       * LEAVE critical section
       */
      SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();
    }
#else
    TS_PARAM_UNUSED(RecordNumber);
    TS_PARAM_UNUSED(DestBuffer);
    TS_PARAM_UNUSED(BufSize);
#endif /* (DEM_NUM_FFSEGS > 0U) */
  }

  DBG_DEM_GETFREEZEFRAMEDATABYDTC_EXIT(
    result, DTC, DTCOrigin, RecordNumber, DestBuffer, BufSize);
  return result;
}

/*------------------[Dem_GetSizeOfFreezeFrameByDTC]-------------------------*/

FUNC(Dem_ReturnGetSizeOfFreezeFrameByDTCType, DEM_CODE)
  Dem_GetSizeOfFreezeFrameByDTC(
    Dem_DTCType                             DTC,
    Dem_DTCOriginType                       DTCOrigin,
    uint8                                   RecordNumber,
    P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) SizeOfFreezeFrame)
{
  Dem_ReturnGetSizeOfFreezeFrameByDTCType result;

  DBG_DEM_GETSIZEOFFREEZEFRAMEBYDTC_ENTRY(
    DTC, DTCOrigin, RecordNumber, SizeOfFreezeFrame);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetSizeOfFreezeFrameByDTC, DEM_E_UNINIT);
    result = DEM_GET_SIZEOFFF_WRONG_DTC;
  }
  else if ((DTC == (Dem_DTCType)0U) || (DTC > (Dem_DTCType)0xFFFFFFU))
  {
    DEM_REPORT_ERROR(DEM_SID_GetSizeOfFreezeFrameByDTC, DEM_E_PARAM_DATA);
    result = DEM_GET_SIZEOFFF_WRONG_DTC;
  }
  else if ( ( ( (DTCOrigin != DEM_DTC_ORIGIN_PRIMARY_MEMORY) &&
                (DTCOrigin != DEM_DTC_ORIGIN_SECONDARY_MEMORY) ) &&
              (DTCOrigin != DEM_DTC_ORIGIN_MIRROR_MEMORY) ) &&
            (DTCOrigin != DEM_DTC_ORIGIN_PERMANENT_MEMORY)
          )
  {
    DEM_REPORT_ERROR(DEM_SID_GetSizeOfFreezeFrameByDTC, DEM_E_PARAM_DATA);
    result = DEM_GET_SIZEOFFF_WRONG_DTCOR;
  }
  else if (SizeOfFreezeFrame == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetSizeOfFreezeFrameByDTC, DEM_E_PARAM_POINTER);
    result = DEM_GET_SIZEOFFF_WRONG_DTC;
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    Dem_EventIdType EventId;
    *SizeOfFreezeFrame = 0U;

    /* search event Id by DTC and map return value.
     * DTCFormat is passed as DEM_DTC_FORMAT_UDS, since the API supports only
     * DTC in UDS format (Dem SWS 8.3.4.2.5). */
    switch (Dem_GetEvIdByDTC(DTC, DEM_DTC_FORMAT_UDS, DTCOrigin, &EventId))
    {
      case DEM_EIBD_OK:
#if (DEM_NUM_FFSEGS > 0U)
        result = DEM_GET_SIZEOFFF_OK;
#else
        result = DEM_GET_SIZEOFFF_WRONG_RNUM;
#endif
        break;
      case DEM_EIBD_WRONG_DTC:
        result = DEM_GET_SIZEOFFF_WRONG_DTC;
        break;
      case DEM_EIBD_WRONG_DTCORIGIN:
        result = DEM_GET_SIZEOFFF_WRONG_DTCOR;
        break;
      /* CHECK: NOPARSE */
      default: /* should never be reached */
        DEM_UNREACHABLE_CODE_ASSERT(DEM_SID_GetSizeOfFreezeFrameByDTC);
        result = DEM_GET_SIZEOFFF_WRONG_DTC;
        break;
      /* CHECK: PARSE */
    }

#if (DEM_NUM_FFSEGS > 0U)
    if (result == DEM_GET_SIZEOFFF_OK)
    {
      Dem_EventMemoryEntryPtrType EvMemEntry;

      Dem_FFIdxType NumFF          = 0U;
      const Dem_FFIdxType MaxNumFF = Dem_GbiMaxNumFFRecs(EventId);

      /*
       * ENTER critical section to protect event memory entry
       */
      SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

      /* search for DTC in event memory */
      if (Dem_SearchForEntry(EventId, &EvMemEntry, NULL_PTR))
      {
        NumFF = DEM_NUMFF(EvMemEntry, MaxNumFF);

        /* check whether the overall size is requested or
         * whether the requested record number is stored */
#if (DEM_FREEZE_FRAME_REC_NUMERATION_TYPE == DEM_FF_RECNUM_CALCULATED)
        if ( (RecordNumber == 0xFFU) ||
             ( (RecordNumber >= 1U) && (RecordNumber <= NumFF) ) )
#else
        if ( (RecordNumber == 0xFFU) ||
             /* Deviation MISRA-2 */
             (Dem_CheckFFRecNumStored(EvMemEntry, RecordNumber) < NumFF) )
#endif
        {
          /* get freeze frame class layout */
          CONSTP2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) FFClass =
            &Dem_FFClass[Dem_GbiFFClassIdx(EventId)];

          /* one or more FF(s) requested and record num is valid and stored */

          /*
           I) Single record
              [Note: Size1 + ... + SizeN = Dem_SizeOfFF(FFClass)]
         |----------|---------------------|------|-------|---|------|-------|
 Format  |  RecNum  | NumberOfIdentifiers | DID1 | Data1 |...| DIDN | DataN |
         |----------|---------------------|------|-------|---|------|-------|
 Size in |----------|---------------------|------|-------|---|---- -|-------|
 bytes   |    1     |         1           |  2   | Size1 |...|  2   | SizeN |
         |----------|---------------------|------|-------|---|------|-------|

         \                                                                  /
          \________________________________________________________________/
                  |                    |                       |
                  |                    |                       |
          II)  RecordNumber = 0xFF     |                       |
              [Note: N = Number of stored FF records]          |
         |-------------------|-------------------|----|-------------------|
 Format  |       Record1     |       Record2     | .. |      RecordN      |
         |-------------------|-------------------|----|-------------------|
 Size in |-------------------|-------------------|----|-------------------|
 bytes   |  SizeOf(Record1)  |  SizeOf(Record2)  | .. |  SizeOf(RecordN)  |
         |-------------------|-------------------|----|-------------------|
          */

          *SizeOfFreezeFrame =
            ((uint16)Dem_SizeOfFF(FFClass) +
             (2U * ((uint16)(FFClass->NumFFSegs))) + 2U);

          if (RecordNumber == 0xFFU)
          {
            *SizeOfFreezeFrame *= (uint16)NumFF;
          }
        }
#if (DEM_FREEZE_FRAME_REC_NUMERATION_TYPE == DEM_FF_RECNUM_CALCULATED)
        else if ( (RecordNumber >= 1U) && (RecordNumber <= MaxNumFF) )
#else
        else if ( Dem_CheckFFRecNumValid( EventId, RecordNumber ) == TRUE )
#endif
        {
          /* record number is valid but no FF is stored for this record,
           * return 0 length buffer */
          *SizeOfFreezeFrame = 0U;
        }
        else
        {
          /* FF record number is not possible for this DTC */
          result = DEM_GET_SIZEOFFF_WRONG_RNUM;
        }
      }

      /*
       * LEAVE critical section
       */
      SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();
    }
    /* else: SizeOfFreezeFrame remains 0 */
#else
    TS_PARAM_UNUSED(RecordNumber);
#endif /* (DEM_NUM_FFSEGS > 0U) */
  }

  DBG_DEM_GETSIZEOFFREEZEFRAMEBYDTC_EXIT(
    result, DTC, DTCOrigin, RecordNumber, SizeOfFreezeFrame);
  return result;
}

/*------------------[Dem_GetExtendedDataRecordByDTC]------------------------*/

FUNC(Dem_ReturnGetExtendedDataRecordByDTCType, DEM_CODE)
  Dem_GetExtendedDataRecordByDTC(
    Dem_DTCType                             DTC,
    Dem_DTCOriginType                       DTCOrigin,
    uint8                                   ExtendedDataNumber,
    /* Deviation MISRA-3 <+2> */
    P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,
    P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) BufSize)
{
  Dem_ReturnGetExtendedDataRecordByDTCType result;

  DBG_DEM_GETEXTENDEDDATARECORDBYDTC_ENTRY(
    DTC, DTCOrigin, ExtendedDataNumber, DestBuffer, BufSize);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetExtendedDataRecordByDTC, DEM_E_UNINIT);
    result = DEM_RECORD_WRONG_DTC;
  }
  else if ((DTC == (Dem_DTCType)0U) || (DTC > (Dem_DTCType)0xFFFFFFU))
  {
    DEM_REPORT_ERROR(DEM_SID_GetExtendedDataRecordByDTC, DEM_E_PARAM_DATA);
    result = DEM_RECORD_WRONG_DTC;
  }
  else if ( ( ( (DTCOrigin != DEM_DTC_ORIGIN_PRIMARY_MEMORY) &&
                (DTCOrigin != DEM_DTC_ORIGIN_SECONDARY_MEMORY) ) &&
              (DTCOrigin != DEM_DTC_ORIGIN_MIRROR_MEMORY) ) &&
            (DTCOrigin != DEM_DTC_ORIGIN_PERMANENT_MEMORY)
          )
  {
    DEM_REPORT_ERROR(DEM_SID_GetExtendedDataRecordByDTC, DEM_E_PARAM_DATA);
    result = DEM_RECORD_WRONG_DTCORIGIN;
  }
  else if ((ExtendedDataNumber == 0U) || (ExtendedDataNumber > 0xEFU))
  {
    DEM_REPORT_ERROR(DEM_SID_GetExtendedDataRecordByDTC, DEM_E_PARAM_DATA);
    result = DEM_RECORD_WRONG_NUMBER;
  }
  else if (BufSize == NULL_PTR)
  {
    DEM_REPORT_ERROR(
      DEM_SID_GetExtendedDataRecordByDTC, DEM_E_PARAM_POINTER);
    result = DEM_RECORD_WRONG_BUFFERSIZE;
  }
  else if (DestBuffer == NULL_PTR)
  {
    DEM_REPORT_ERROR(
      DEM_SID_GetExtendedDataRecordByDTC, DEM_E_PARAM_POINTER);
    result = DEM_RECORD_WRONG_DTC;
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    Dem_EventIdType EventId;

    /* search event Id by DTC and map return value.
     * DTCFormat is passed as DEM_DTC_FORMAT_UDS, since the API supports only
     * DTC in UDS format (Dem SWS 8.3.4.2.6). */
    switch (Dem_GetEvIdByDTC(DTC, DEM_DTC_FORMAT_UDS, DTCOrigin, &EventId))
    {
      case DEM_EIBD_OK:
#if (DEM_NUM_EDSEGS > 0U)
        result = DEM_RECORD_OK;
#else
        result = DEM_RECORD_WRONG_NUMBER;
#endif
        break;
      case DEM_EIBD_WRONG_DTC:
        result = DEM_RECORD_WRONG_DTC;
        break;
      case DEM_EIBD_WRONG_DTCORIGIN:
        result = DEM_RECORD_WRONG_DTCORIGIN;
        break;
      /* CHECK: NOPARSE */
      default: /* should never be reached */
        DEM_UNREACHABLE_CODE_ASSERT(DEM_SID_GetExtendedDataRecordByDTC);
        result = DEM_RECORD_WRONG_DTC;
        break;
      /* CHECK: PARSE */
    }

#if (DEM_NUM_EDSEGS > 0U)
    if (result == DEM_RECORD_OK)
    {
      Dem_EventMemoryEntryPtrType EvMemEntry;

      /* get extended data class layout */
      CONSTP2CONST(Dem_EDClassType, AUTOMATIC, DEM_CONST) EDClass =
        &Dem_EDClass[Dem_GbiEDClassIdx(EventId)];

      /*
       * ENTER critical section to protect event memory entry
       */
      SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

      /* search for DTC in event memory */
      if (Dem_SearchForEntry(EventId, &EvMemEntry, NULL_PTR))
      {
        result = Dem_GetOneEDRecord(
          EDClass, ExtendedDataNumber, EvMemEntry, DestBuffer, BufSize);
      }
      else /* DTC not stored in event memory */
      {
        /* check if record number is valid (is known) for this DTC */
        const Dem_EDSegIdxType SegIndex =
          Dem_FindEDNumIndex(EDClass, ExtendedDataNumber);

        if (SegIndex < EDClass->NumEDSegs)
        {
          /* record number is valid, but DTC is not stored */
          /* !LINKSTO Dem631,1 return DEM_RECORD_OK and BufSize 0 */
          *BufSize = 0U;
          /* result remains DEM_RECORD_OK */
        }
        else
        {
          /* Record number invalid for this DTC */
          result = DEM_RECORD_WRONG_NUMBER;
        }
      }

      /*
       * LEAVE critical section
       */
      SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();
    }
#else
    TS_PARAM_UNUSED(ExtendedDataNumber);
    TS_PARAM_UNUSED(DestBuffer);
    TS_PARAM_UNUSED(BufSize);
#endif /* (DEM_NUM_EDSEGS > 0U) */
  }

  DBG_DEM_GETEXTENDEDDATARECORDBYDTC_EXIT(
    result, DTC, DTCOrigin, ExtendedDataNumber, DestBuffer, BufSize);
  return result;
}

/*----------------[Dem_GetSizeOfExtendedDataRecordByDTC]--------------------*/

FUNC(Dem_ReturnGetSizeOfExtendedDataRecordByDTCType, DEM_CODE)
  Dem_GetSizeOfExtendedDataRecordByDTC(
    Dem_DTCType                             DTC,
    Dem_DTCOriginType                       DTCOrigin,
    uint8                                   ExtendedDataNumber,
    P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) SizeOfExtendedDataRecord)
{
  Dem_ReturnGetSizeOfExtendedDataRecordByDTCType result;

  DBG_DEM_GETSIZEOFEXTENDEDDATARECORDBYDTC_ENTRY(
    DTC, DTCOrigin, ExtendedDataNumber, SizeOfExtendedDataRecord);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetSizeOfExtendedDataRecordByDTC, DEM_E_UNINIT);
    result = DEM_GET_SIZEOFEDRBYDTC_W_DTC;
  }
  else if ((DTC == (Dem_DTCType)0U) || (DTC > (Dem_DTCType)0xFFFFFFU))
  {
    DEM_REPORT_ERROR(
      DEM_SID_GetSizeOfExtendedDataRecordByDTC, DEM_E_PARAM_DATA);
    result = DEM_GET_SIZEOFEDRBYDTC_W_DTC;
  }
  else if ( ( ( (DTCOrigin != DEM_DTC_ORIGIN_PRIMARY_MEMORY) &&
                (DTCOrigin != DEM_DTC_ORIGIN_SECONDARY_MEMORY) ) &&
              (DTCOrigin != DEM_DTC_ORIGIN_MIRROR_MEMORY) ) &&
            (DTCOrigin != DEM_DTC_ORIGIN_PERMANENT_MEMORY)
          )
  {
    DEM_REPORT_ERROR(
      DEM_SID_GetSizeOfExtendedDataRecordByDTC, DEM_E_PARAM_DATA);
    result = DEM_GET_SIZEOFEDRBYDTC_W_DTCOR;
  }
  else if (SizeOfExtendedDataRecord == NULL_PTR)
  {
    DEM_REPORT_ERROR(
      DEM_SID_GetSizeOfExtendedDataRecordByDTC, DEM_E_PARAM_POINTER);
    result = DEM_GET_SIZEOFEDRBYDTC_W_DTC;
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    Dem_EventIdType EventId;
    *SizeOfExtendedDataRecord = 0U;

    /* search event Id by DTC and map return value.
     * DTCFormat is passed as DEM_DTC_FORMAT_UDS, since the API supports only
     * DTC in UDS format (Dem SWS 8.3.4.2.7). */
    switch (Dem_GetEvIdByDTC(DTC, DEM_DTC_FORMAT_UDS, DTCOrigin, &EventId))
    {
      case DEM_EIBD_OK:
#if (DEM_NUM_EDSEGS > 0U)
        result = DEM_GET_SIZEOFEDRBYDTC_OK;
#else
        result = DEM_GET_SIZEOFEDRBYDTC_W_RNUM;
#endif
        break;
      case DEM_EIBD_WRONG_DTC:
        result = DEM_GET_SIZEOFEDRBYDTC_W_DTC;
        break;
      case DEM_EIBD_WRONG_DTCORIGIN:
        result = DEM_GET_SIZEOFEDRBYDTC_W_DTCOR;
        break;
      /* CHECK: NOPARSE */
      default: /* should never be reached */
        DEM_UNREACHABLE_CODE_ASSERT(DEM_SID_GetSizeOfExtendedDataRecordByDTC);
        result = DEM_GET_SIZEOFEDRBYDTC_W_DTC;
        break;
      /* CHECK: PARSE */
    }

#if (DEM_NUM_EDSEGS > 0U)
    if (result == DEM_GET_SIZEOFEDRBYDTC_OK)
    {
      /*
       * ENTER critical section to protect event memory entry
       */
      SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

      /* search for DTC in event memory */
      if (Dem_SearchForEntry(EventId, NULL_PTR, NULL_PTR) == TRUE)
      {
        /* get extended data class layout */
        CONSTP2CONST(Dem_EDClassType, AUTOMATIC, DEM_CONST) EDClass =
          &Dem_EDClass[Dem_GbiEDClassIdx(EventId)];

        if (ExtendedDataNumber == 0xFFU)
        {
          /* add all record sizes of this extended data class */
          *SizeOfExtendedDataRecord =
#if (DEM_GET_SIZEOFEDRBYDTC_OPTIMIZATION == STD_ON)
            /* add record number size */
            EDClass->NumEDSegs +
#endif
#if (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON)
            (uint16)Dem_SizeOfMapIntValClass(EDClass) +
#endif
            (uint16)Dem_SizeOfED(EDClass);
        }
        else if (ExtendedDataNumber == 0xFEU)
        {
          Dem_EDSegIdxType SegIndex;

          for (SegIndex = 0U; (SegIndex < EDClass->NumEDSegs); ++SegIndex)
          {
            if ( (Dem_EDSegment[EDClass->EDSegIdx[SegIndex]].RecNum >= 0x90U) &&
                 (Dem_EDSegment[EDClass->EDSegIdx[SegIndex]].RecNum <= 0xEFU) )
            {
              *SizeOfExtendedDataRecord +=
#if (DEM_GET_SIZEOFEDRBYDTC_OPTIMIZATION == STD_ON)
                /* add record number size */
                1U +
#endif
#if (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON)
                (uint16)Dem_SizeOfMapIntValSegment(&Dem_EDSegment[EDClass->EDSegIdx[SegIndex]]) +
#endif
                (uint16)Dem_SizeOfEDSegment(&Dem_EDSegment[EDClass->EDSegIdx[SegIndex]]);
            }
          }
        }
        else
        {
          /* check if record number is valid (is known) for this DTC */
          const Dem_EDSegIdxType SegIndex =
            Dem_FindEDNumIndex(EDClass, ExtendedDataNumber);

          if (SegIndex < EDClass->NumEDSegs)
          {
            CONSTP2CONST(Dem_EDSegmentType, AUTOMATIC, DEM_CONST) EDSegment =
              &Dem_EDSegment[EDClass->EDSegIdx[SegIndex]];

            /* add all data element sizes of this extended data record */
            *SizeOfExtendedDataRecord =
#if (DEM_GET_SIZEOFEDRBYDTC_OPTIMIZATION == STD_ON)
              /* add record number size */
              1U +
#endif
#if (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON)
              (uint16)Dem_SizeOfMapIntValSegment(EDSegment) +
#endif
              (uint16)Dem_SizeOfEDSegment(EDSegment);
          }
          else
          {
            result = DEM_GET_SIZEOFEDRBYDTC_W_RNUM;
          }
        }
      }

      /*
       * LEAVE critical section
       */
      SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();

      /* else: SizeOfExtendedDataRecord remains 0 */
    }
#else
    TS_PARAM_UNUSED(ExtendedDataNumber);
#endif
  }

  DBG_DEM_GETSIZEOFEXTENDEDDATARECORDBYDTC_EXIT(
    result, DTC, DTCOrigin, ExtendedDataNumber, SizeOfExtendedDataRecord);
  return result;
}

/*==================[internal function definitions]=========================*/

#if (DEM_NUM_FFSEGS > 0U)
STATIC FUNC(void, DEM_CODE) Dem_CopyFFInfo(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)              DestBuffer,
  const Dem_EventMemoryEntryPtrConstType              EventMemoryEntry,
  CONSTP2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) FFClass,
  uint8                                               RecIndex)
{
  /* pointer to const FF data */
  const Dem_EntryDataPtrConstType FFEntryData =
    Dem_FFEntryData(EventMemoryEntry, FFClass, RecIndex);

  Dem_FFSegIdxType SegIdx;

  Dem_SizeEntryDataType offset = 0U;

  DBG_DEM_COPYFFINFO_ENTRY(DestBuffer, EventMemoryEntry, FFClass, RecIndex);

  for (SegIdx = 0U; SegIdx < FFClass->NumFFSegs; ++SegIdx)
  {
    /* Copy one freeze frame segment data Ids and values into
       the destination buffer */

    const Dem_SizeFFType FFSegSize =
      Dem_SizeOfFFSegment(&Dem_FFSegment[FFClass->FFSegIdx[SegIdx]]);

    DestBuffer[offset] =
      DEM_HIBYTE(Dem_FFSegment[FFClass->FFSegIdx[SegIdx]].DataId);
    DestBuffer[offset + 1U] =
      DEM_LOBYTE(Dem_FFSegment[FFClass->FFSegIdx[SegIdx]].DataId);

    /* advance offset by 2 bytes */
    offset += 2;

    /* write content into response */
    TS_MemCpy(&DestBuffer[offset],
              &FFEntryData[FFClass->StartByte[SegIdx]],
              FFSegSize);

    /* advance offset by number of bytes in segment */
    offset += (Dem_SizeEntryDataType)FFSegSize;
  }

  DBG_DEM_COPYFFINFO_EXIT(DestBuffer, EventMemoryEntry, FFClass, RecIndex);
}
#endif /* (DEM_NUM_FFSEGS > 0U) */

#if (DEM_NUM_EDSEGS > 0U)
STATIC FUNC(Dem_ReturnGetExtendedDataRecordByDTCType, DEM_CODE)
  Dem_GetOneEDRecord(
    P2CONST(Dem_EDClassType, AUTOMATIC, DEM_CONST) EDClass,
    uint8                                          ExtendedDataNumber,
    Dem_EventMemoryEntryPtrConstType               EventMemoryEntry,
    P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)         DestBuffer,
    P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)        BufSize)
{
  Dem_ReturnGetExtendedDataRecordByDTCType result = DEM_RECORD_WRONG_NUMBER;

  /* check if record number is valid (is known) for this DTC */
  const Dem_EDSegIdxType SegIndex =
    Dem_FindEDNumIndex(EDClass, ExtendedDataNumber);

  DBG_DEM_GETONEEDRECORD_ENTRY(
    EDClass, ExtendedDataNumber, EventMemoryEntry, DestBuffer, BufSize);

  if (SegIndex < EDClass->NumEDSegs)
  {
    CONSTP2CONST(Dem_EDSegmentType, AUTOMATIC, DEM_CONST) EDSegment =
      &Dem_EDSegment[EDClass->EDSegIdx[SegIndex]];

    const Dem_SizeEDType EDSegSize =
#if (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON)
      Dem_SizeOfMapIntValSegment(EDSegment) +
#endif
      Dem_SizeOfEDSegment(EDSegment);

    /* calculate needed buffer size */
    const Dem_SizeEntryDataType NeededSize = EDSegSize;

    if (NeededSize <= (Dem_SizeEntryDataType)*BufSize)
    {
      /* copy content of the record into the destination buffer */
      (void)Dem_AssembleExtendedDataSeg(EDSegment,
        EDClass->StartByte[SegIndex], DestBuffer, EventMemoryEntry);

      /* store size of buffer */
      *BufSize = NeededSize;

      result = DEM_RECORD_OK;
    }
    else
    {
      result = DEM_RECORD_WRONG_BUFFERSIZE;
    }
  }
  /* else: Record number not found in extended data */

  DBG_DEM_GETONEEDRECORD_EXIT(
    result, EDClass, ExtendedDataNumber, EventMemoryEntry, DestBuffer,
    BufSize);
  return result;
}
#endif /* (DEM_NUM_EDSEGS > 0U) */

#define DEM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[end of file]===========================================*/
