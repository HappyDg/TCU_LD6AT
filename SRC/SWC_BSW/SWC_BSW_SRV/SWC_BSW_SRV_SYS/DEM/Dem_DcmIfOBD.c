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

/* This file contains definitions of OBD related APIs provided by Dem to the
 * Dcm. */
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

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/* OBD not implemented in this version. All OBD APIs are currently available
 * as stubs. */

#define DEM_START_SEC_CODE
#include <MemMap.h>

/*----------------[Dem_SetEventDisabled]------------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_SetEventDisabled(Dem_EventIdType EventId)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_SETEVENTDISABLED_ENTRY(EventId);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_SetEventDisabled, DEM_E_UNINIT);
  }
  else if (EventId == (Dem_EventIdType)DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_SetEventDisabled, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_SetEventDisabled, DEM_E_PARAM_CONFIG);
  }
  else
#else /* DEM_DEV_ERROR_DETECT */
  TS_PARAM_UNUSED(EventId);
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* Function NOT fully implemented yet.
     * Implementation is scheduled for future releases. */
  }

  DBG_DEM_SETEVENTDISABLED_EXIT(result, EventId);
  return result;
}

/*----------------[Dem_RepIUMPRFaultDetect]---------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_RepIUMPRFaultDetect(
  Dem_RatioIdType RatioID)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_REPIUMPRFAULTDETECT_ENTRY(RatioID);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_RepIUMPRFaultDetect, DEM_E_UNINIT);
  }
  else
#endif
  {
    /* Function NOT fully implemented yet.
     * Implementation is scheduled for future releases. */
    TS_PARAM_UNUSED(RatioID);
  }

  DBG_DEM_REPIUMPRFAULTDETECT_EXIT(result, RatioID);
  return result;
}

/*----------------[Dem_RepIUMPRDenLock]-------------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_RepIUMPRDenLock(Dem_RatioIdType RatioID)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_REPIUMPRDENLOCK_ENTRY(RatioID);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_RepIUMPRDenLock, DEM_E_UNINIT);
  }
  else
#endif
  {
    /* Function NOT fully implemented yet.
     * Implementation is scheduled for future releases. */
    TS_PARAM_UNUSED(RatioID);
  }

  DBG_DEM_REPIUMPRDENLOCK_EXIT(result, RatioID);
  return result;
}

/*----------------[Dem_RepIUMPRDenRelease]----------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_RepIUMPRDenRelease(Dem_RatioIdType RatioID)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_REPIUMPRDENRELEASE_ENTRY(RatioID);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_RepIUMPRDenRelease, DEM_E_UNINIT);
  }
  else
#endif
  {
    /* Function NOT fully implemented yet.
     * Implementation is scheduled for future releases. */
    TS_PARAM_UNUSED(RatioID);
   }

  DBG_DEM_REPIUMPRDENRELEASE_EXIT(result, RatioID);
  return result;
}

/*----------------[Dem_GetInfoTypeValue08]----------------------------------*/

#if (DEM_DCM_ENABLED == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_GetInfoTypeValue08(
  Dcm_OpStatusType                       OpStatus,
  /* Deviation MISRA-1 */
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Iumprdata08)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_GETINFOTYPEVALUE08_ENTRY(OpStatus, Iumprdata08);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetInfoTypeValue08, DEM_E_UNINIT);
  }
  else if (DCM_INITIAL != OpStatus)
  {
    DEM_REPORT_ERROR(DEM_SID_GetInfoTypeValue08, DEM_E_PARAM_DATA);
  }
  else if (Iumprdata08 == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetInfoTypeValue08, DEM_E_PARAM_POINTER);
  }
  else
#else /* DEM_DEV_ERROR_DETECT */
  TS_PARAM_UNUSED(Iumprdata08);
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* Function NOT fully implemented yet.
     * Implementation is scheduled for future releases. */
    TS_PARAM_UNUSED(OpStatus);
  }

  DBG_DEM_GETINFOTYPEVALUE08_EXIT(result, OpStatus, Iumprdata08);
  return result;
}
#endif

/*----------------[Dem_GetInfoTypeValue0B]----------------------------------*/

#if (DEM_DCM_ENABLED == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_GetInfoTypeValue0B(
  Dcm_OpStatusType                       OpStatus,
  /* Deviation MISRA-1 */
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Iumprdata0B)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_GETINFOTYPEVALUE0B_ENTRY(OpStatus, Iumprdata0B);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetInfoTypeValue0B, DEM_E_UNINIT);
  }
  else if (DCM_INITIAL != OpStatus)
  {
    DEM_REPORT_ERROR(DEM_SID_GetInfoTypeValue0B, DEM_E_PARAM_DATA);
  }
  else if (Iumprdata0B == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetInfoTypeValue0B, DEM_E_PARAM_POINTER);
  }
  else
#else /* DEM_DEV_ERROR_DETECT */
  TS_PARAM_UNUSED(Iumprdata0B);
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* Function NOT fully implemented yet.
     * Implementation is scheduled for future releases. */
    TS_PARAM_UNUSED(OpStatus);
  }

  DBG_DEM_GETINFOTYPEVALUE0B_EXIT(result, OpStatus, Iumprdata0B);
  return result;
}
#endif

/*----------------[Dem_DcmReadDataOfPID01]----------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID01(
  /* Deviation MISRA-1 */
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID01value)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_DCMREADDATAOFPID01_ENTRY(PID01value);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID01, DEM_E_UNINIT);
  }
  else if (PID01value == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID01, DEM_E_PARAM_POINTER);
  }
  else
#else /* DEM_DEV_ERROR_DETECT */
  TS_PARAM_UNUSED(PID01value);
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* Function NOT fully implemented yet.
     * Implementation is scheduled for future releases. */
  }

  DBG_DEM_DCMREADDATAOFPID01_EXIT(result, PID01value);
  return result;
}

/*----------------[Dem_DcmReadDataOfPID21]----------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID21(
  /* Deviation MISRA-1 */
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID21value)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_DCMREADDATAOFPID21_ENTRY(PID21value);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID21, DEM_E_UNINIT);
  }
  else if (PID21value == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID21, DEM_E_PARAM_POINTER);
  }
  else
#else /* DEM_DEV_ERROR_DETECT */
  TS_PARAM_UNUSED(PID21value);
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* Function NOT fully implemented yet.
     * Implementation is scheduled for future releases. */
  }

  DBG_DEM_DCMREADDATAOFPID21_EXIT(result, PID21value);
  return result;
}

/*----------------[Dem_DcmReadDataOfPID30]----------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID30(
  /* Deviation MISRA-1 */
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID30value)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_DCMREADDATAOFPID30_ENTRY(PID30value);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID30, DEM_E_UNINIT);
  }
  else if (PID30value == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID30, DEM_E_PARAM_POINTER);
  }
  else
#else /* DEM_DEV_ERROR_DETECT */
  TS_PARAM_UNUSED(PID30value);
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* Function NOT fully implemented yet.
     * Implementation is scheduled for future releases. */
  }

  DBG_DEM_DCMREADDATAOFPID30_EXIT(result, PID30value);
  return result;
}

/*----------------[Dem_DcmReadDataOfPID31]----------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID31(
  /* Deviation MISRA-1 */
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID31value)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_DCMREADDATAOFPID31_ENTRY(PID31value);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID31, DEM_E_UNINIT);
  }
  else if (PID31value == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID31, DEM_E_PARAM_POINTER);
  }
  else
#else /* DEM_DEV_ERROR_DETECT */
  TS_PARAM_UNUSED(PID31value);
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* Function NOT fully implemented yet.
     * Implementation is scheduled for future releases. */
  }

  DBG_DEM_DCMREADDATAOFPID31_EXIT(result, PID31value);
  return result;
}

/*----------------[Dem_DcmReadDataOfPID41]----------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID41(
  /* Deviation MISRA-1 */
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID41value)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_DCMREADDATAOFPID41_ENTRY(PID41value);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID41, DEM_E_UNINIT);
  }
  else if (PID41value == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID41, DEM_E_PARAM_POINTER);
  }
  else
#else /* DEM_DEV_ERROR_DETECT */
  TS_PARAM_UNUSED(PID41value);
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* Function NOT fully implemented yet.
     * Implementation is scheduled for future releases. */
  }

  DBG_DEM_DCMREADDATAOFPID41_EXIT(result, PID41value);
  return result;
}

/*----------------[Dem_DcmReadDataOfPID4D]----------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID4D(
  /* Deviation MISRA-1 */
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID4Dvalue)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_DCMREADDATAOFPID4D_ENTRY(PID4Dvalue);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID4D, DEM_E_UNINIT);
  }
  else if (PID4Dvalue == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID4D, DEM_E_PARAM_POINTER);
  }
  else
#else /* DEM_DEV_ERROR_DETECT */
  TS_PARAM_UNUSED(PID4Dvalue);
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* Function NOT fully implemented yet.
     * Implementation is scheduled for future releases. */
  }

  DBG_DEM_DCMREADDATAOFPID4D_EXIT(result, PID4Dvalue);
  return result;
}

/*----------------[Dem_DcmReadDataOfPID4E]----------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID4E(
  /* Deviation MISRA-1 */
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID4Evalue)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_DCMREADDATAOFPID4E_ENTRY(PID4Evalue);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID4E, DEM_E_UNINIT);
  }
  else if (PID4Evalue == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID4E, DEM_E_PARAM_POINTER);
  }
  else
#else /* DEM_DEV_ERROR_DETECT */
  TS_PARAM_UNUSED(PID4Evalue);
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* Function NOT fully implemented yet.
     * Implementation is scheduled for future releases. */
  }

  DBG_DEM_DCMREADDATAOFPID4E_EXIT(result, PID4Evalue);
  return result;
}

/*----------------[Dem_DcmReadDataOfPID1C]----------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID1C(
  /* Deviation MISRA-1 */
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID1Cvalue)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_DCMREADDATAOFPID1C_ENTRY(PID1Cvalue);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID1C, DEM_E_UNINIT);
  }
  else if (PID1Cvalue == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_DcmReadDataOfPID1C, DEM_E_PARAM_POINTER);
  }
  else
#else /* DEM_DEV_ERROR_DETECT */
  TS_PARAM_UNUSED(PID1Cvalue);
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* Function NOT fully implemented yet.
     * Implementation is scheduled for future releases. */
  }

  DBG_DEM_DCMREADDATAOFPID1C_EXIT(result, PID1Cvalue);
  return result;
}

/*----------------[Dem_ReadDataOfOBDFreezeFrame]----------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_ReadDataOfOBDFreezeFrame(
  uint8                                  PID,
  uint8                                  DataElementIndexOfPID,
  /* Deviation MISRA-1 <+2> */
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) DestBuffer,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Bufsize)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_READDATAOFOBDFREEZEFRAME_ENTRY(
    PID, DataElementIndexOfPID, DestBuffer, Bufsize);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_ReadDataOfOBDFreezeFrame, DEM_E_UNINIT);
  }
  else if (DestBuffer == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_ReadDataOfOBDFreezeFrame, DEM_E_PARAM_POINTER);
  }
  else if (Bufsize == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_ReadDataOfOBDFreezeFrame, DEM_E_PARAM_POINTER);
  }
  else
#else /* DEM_DEV_ERROR_DETECT */
  TS_PARAM_UNUSED(DestBuffer);
  TS_PARAM_UNUSED(Bufsize);
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* Function NOT fully implemented yet.
     * Implementation is scheduled for future releases. */
    TS_PARAM_UNUSED(PID);
    TS_PARAM_UNUSED(DataElementIndexOfPID);
  }

  DBG_DEM_READDATAOFOBDFREEZEFRAME_EXIT(
    result, PID, DataElementIndexOfPID, DestBuffer, Bufsize);
  return result;
}

/*----------------[Dem_GetDTCOfOBDFreezeFrame]------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_GetDTCOfOBDFreezeFrame(
  uint8                                   FrameNumber,
  /* Deviation MISRA-1 */
  P2VAR(uint32, AUTOMATIC, DEM_APPL_DATA) DTC)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_GETDTCOFOBDFREEZEFRAME_ENTRY(FrameNumber, DTC);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetDTCOfOBDFreezeFrame, DEM_E_UNINIT);
  }
  else if (DTC == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetDTCOfOBDFreezeFrame, DEM_E_PARAM_POINTER);
  }
  else
#else /* DEM_DEV_ERROR_DETECT */
  TS_PARAM_UNUSED(DTC);
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* Function NOT fully implemented yet.
     * Implementation is scheduled for future releases. */
    TS_PARAM_UNUSED(FrameNumber);
  }

  DBG_DEM_GETDTCOFOBDFREEZEFRAME_EXIT(result, FrameNumber, DTC);
  return result;
}

/*----------------[Dem_SetPtoStatus]----------------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_SetPtoStatus(boolean PtoStatus)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_DEM_SETPTOSTATUS_ENTRY(PtoStatus);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_SetPtoStatus, DEM_E_UNINIT);
  }
  else if ( (PtoStatus != TRUE) && (PtoStatus != FALSE) )
  {
    DEM_REPORT_ERROR(DEM_SID_SetPtoStatus, DEM_E_PARAM_DATA);
  }
  else
#else /* DEM_DEV_ERROR_DETECT */
  TS_PARAM_UNUSED(PtoStatus);
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* Function NOT fully implemented yet.
     * Implementation is scheduled for future releases. */
  }

  DBG_DEM_SETPTOSTATUS_EXIT(result, PtoStatus);
  return result;
}

#define DEM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/
