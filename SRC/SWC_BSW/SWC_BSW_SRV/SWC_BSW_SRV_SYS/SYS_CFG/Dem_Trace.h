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
#if (!defined DEM_TRACE_H)
#define DEM_TRACE_H

/*==================[inclusions]============================================*/

/*==================[macros]================================================*/

#ifndef DBG_DEM_GETVERSIONINFO_ENTRY
/** \brief Entry point of function Dem_GetVersionInfo() */
#define DBG_DEM_GETVERSIONINFO_ENTRY(a)
#endif

#ifndef DBG_DEM_GETVERSIONINFO_EXIT
/** \brief Exit point of function Dem_GetVersionInfo() */
#define DBG_DEM_GETVERSIONINFO_EXIT(a)
#endif

#ifndef DBG_DEM_PREINIT_ENTRY
/** \brief Entry point of function Dem_PreInit() */
#define DBG_DEM_PREINIT_ENTRY(a)
#endif

#ifndef DBG_DEM_PREINIT_EXIT
/** \brief Exit point of function Dem_PreInit() */
#define DBG_DEM_PREINIT_EXIT(a)
#endif

#ifndef DBG_DEM_INIT_ENTRY
/** \brief Entry point of function Dem_Init() */
#define DBG_DEM_INIT_ENTRY()
#endif

#ifndef DBG_DEM_INIT_EXIT
/** \brief Exit point of function Dem_Init() */
#define DBG_DEM_INIT_EXIT()
#endif

#ifndef DBG_DEM_SHUTDOWN_ENTRY
/** \brief Entry point of function Dem_Shutdown() */
#define DBG_DEM_SHUTDOWN_ENTRY()
#endif

#ifndef DBG_DEM_SHUTDOWN_EXIT
/** \brief Exit point of function Dem_Shutdown() */
#define DBG_DEM_SHUTDOWN_EXIT()
#endif

#ifndef DBG_DEM_REPORTERRORSTATUS_ENTRY
/** \brief Entry point of function Dem_ReportErrorStatus() */
#define DBG_DEM_REPORTERRORSTATUS_ENTRY(a, b)
#endif

#ifndef DBG_DEM_REPORTERRORSTATUS_EXIT
/** \brief Exit point of function Dem_ReportErrorStatus() */
#define DBG_DEM_REPORTERRORSTATUS_EXIT(a, b)
#endif

#ifndef DBG_DEM_SETEVENTSTATUS_ENTRY
/** \brief Entry point of function Dem_SetEventStatus() */
#define DBG_DEM_SETEVENTSTATUS_ENTRY(a, b)
#endif

#ifndef DBG_DEM_SETEVENTSTATUS_EXIT
/** \brief Exit point of function Dem_SetEventStatus() */
#define DBG_DEM_SETEVENTSTATUS_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_RESETEVENTSTATUS_ENTRY
/** \brief Entry point of function Dem_ResetEventStatus() */
#define DBG_DEM_RESETEVENTSTATUS_ENTRY(a)
#endif

#ifndef DBG_DEM_RESETEVENTSTATUS_EXIT
/** \brief Exit point of function Dem_ResetEventStatus() */
#define DBG_DEM_RESETEVENTSTATUS_EXIT(a, b)
#endif

#ifndef DBG_DEM_PRESTOREFREEZEFRAME_ENTRY
/** \brief Entry point of function Dem_PrestoreFreezeFrame() */
#define DBG_DEM_PRESTOREFREEZEFRAME_ENTRY(a)
#endif

#ifndef DBG_DEM_PRESTOREFREEZEFRAME_EXIT
/** \brief Exit point of function Dem_PrestoreFreezeFrame() */
#define DBG_DEM_PRESTOREFREEZEFRAME_EXIT(a, b)
#endif

#ifndef DBG_DEM_CLEARPRESTOREDFREEZEFRAME_ENTRY
/** \brief Entry point of function Dem_ClearPrestoredFreezeFrame() */
#define DBG_DEM_CLEARPRESTOREDFREEZEFRAME_ENTRY(a)
#endif

#ifndef DBG_DEM_CLEARPRESTOREDFREEZEFRAME_EXIT
/** \brief Exit point of function Dem_ClearPrestoredFreezeFrame() */
#define DBG_DEM_CLEARPRESTOREDFREEZEFRAME_EXIT(a, b)
#endif

#ifndef DBG_DEM_SETOPERATIONCYCLESTATE_ENTRY
/** \brief Entry point of function Dem_SetOperationCycleState() */
#define DBG_DEM_SETOPERATIONCYCLESTATE_ENTRY(a, b)
#endif

#ifndef DBG_DEM_SETOPERATIONCYCLESTATE_EXIT
/** \brief Exit point of function Dem_SetOperationCycleState() */
#define DBG_DEM_SETOPERATIONCYCLESTATE_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_SETOPERATIONCYCLECNTVALUE_ENTRY
/** \brief Entry point of function Dem_SetOperationCycleCntValue() */
#define DBG_DEM_SETOPERATIONCYCLECNTVALUE_ENTRY(a, b)
#endif

#ifndef DBG_DEM_SETOPERATIONCYCLECNTVALUE_EXIT
/** \brief Exit point of function Dem_SetOperationCycleCntValue() */
#define DBG_DEM_SETOPERATIONCYCLECNTVALUE_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_SETAGINGCYCLESTATE_ENTRY
/** \brief Entry point of function Dem_SetAgingCycleState() */
#define DBG_DEM_SETAGINGCYCLESTATE_ENTRY(a)
#endif

#ifndef DBG_DEM_SETAGINGCYCLESTATE_EXIT
/** \brief Exit point of function Dem_SetAgingCycleState() */
#define DBG_DEM_SETAGINGCYCLESTATE_EXIT(a, b)
#endif

#ifndef DBG_DEM_SETAGINGCYCLECOUNTERVALUE_ENTRY
/** \brief Entry point of function Dem_SetAgingCycleCounterValue() */
#define DBG_DEM_SETAGINGCYCLECOUNTERVALUE_ENTRY(a)
#endif

#ifndef DBG_DEM_SETAGINGCYCLECOUNTERVALUE_EXIT
/** \brief Exit point of function Dem_SetAgingCycleCounterValue() */
#define DBG_DEM_SETAGINGCYCLECOUNTERVALUE_EXIT(a, b)
#endif

#ifndef DBG_DEM_GETEVENTSTATUS_ENTRY
/** \brief Entry point of function Dem_GetEventStatus() */
#define DBG_DEM_GETEVENTSTATUS_ENTRY(a, b)
#endif

#ifndef DBG_DEM_GETEVENTSTATUS_EXIT
/** \brief Exit point of function Dem_GetEventStatus() */
#define DBG_DEM_GETEVENTSTATUS_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_GETEVENTFAILED_ENTRY
/** \brief Entry point of function Dem_GetEventFailed() */
#define DBG_DEM_GETEVENTFAILED_ENTRY(a, b)
#endif

#ifndef DBG_DEM_GETEVENTFAILED_EXIT
/** \brief Exit point of function Dem_GetEventFailed() */
#define DBG_DEM_GETEVENTFAILED_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_GETEVENTTESTED_ENTRY
/** \brief Entry point of function Dem_GetEventTested() */
#define DBG_DEM_GETEVENTTESTED_ENTRY(a, b)
#endif

#ifndef DBG_DEM_GETEVENTTESTED_EXIT
/** \brief Exit point of function Dem_GetEventTested() */
#define DBG_DEM_GETEVENTTESTED_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_GETDTCOFEVENT_ENTRY
/** \brief Entry point of function Dem_GetDTCOfEvent() */
#define DBG_DEM_GETDTCOFEVENT_ENTRY(a, b, c)
#endif

#ifndef DBG_DEM_GETDTCOFEVENT_EXIT
/** \brief Exit point of function Dem_GetDTCOfEvent() */
#define DBG_DEM_GETDTCOFEVENT_EXIT(a, b, c, d)
#endif

#ifndef DBG_DEM_SETENABLECONDITION_ENTRY
/** \brief Entry point of function Dem_SetEnableCondition() */
#define DBG_DEM_SETENABLECONDITION_ENTRY(a, b)
#endif

#ifndef DBG_DEM_SETENABLECONDITION_EXIT
/** \brief Exit point of function Dem_SetEnableCondition() */
#define DBG_DEM_SETENABLECONDITION_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_SETSTORAGECONDITION_ENTRY
/** \brief Entry point of function Dem_SetStorageCondition() */
#define DBG_DEM_SETSTORAGECONDITION_ENTRY(a, b)
#endif

#ifndef DBG_DEM_SETSTORAGECONDITION_EXIT
/** \brief Exit point of function Dem_SetStorageCondition() */
#define DBG_DEM_SETSTORAGECONDITION_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_GETFAULTDETECTIONCOUNTER_ENTRY
/** \brief Entry point of function Dem_GetFaultDetectionCounter() */
#define DBG_DEM_GETFAULTDETECTIONCOUNTER_ENTRY(a, b)
#endif

#ifndef DBG_DEM_GETFAULTDETECTIONCOUNTER_EXIT
/** \brief Exit point of function Dem_GetFaultDetectionCounter() */
#define DBG_DEM_GETFAULTDETECTIONCOUNTER_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_GETINDICATORSTATUS_ENTRY
/** \brief Entry point of function Dem_GetIndicatorStatus() */
#define DBG_DEM_GETINDICATORSTATUS_ENTRY(a, b)
#endif

#ifndef DBG_DEM_GETINDICATORSTATUS_EXIT
/** \brief Exit point of function Dem_GetIndicatorStatus() */
#define DBG_DEM_GETINDICATORSTATUS_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_GETEVENTFREEZEFRAMEDATA_ENTRY
/** \brief Entry point of function Dem_GetEventFreezeFrameData() */
#define DBG_DEM_GETEVENTFREEZEFRAMEDATA_ENTRY(a, b, c, d, e)
#endif

#ifndef DBG_DEM_GETEVENTFREEZEFRAMEDATA_EXIT
/** \brief Exit point of function Dem_GetEventFreezeFrameData() */
#define DBG_DEM_GETEVENTFREEZEFRAMEDATA_EXIT(a, b, c, d, e, f)
#endif

#ifndef DBG_DEM_GETEVENTEXTENDEDDATARECORD_ENTRY
/** \brief Entry point of function Dem_GetEventExtendedDataRecord() */
#define DBG_DEM_GETEVENTEXTENDEDDATARECORD_ENTRY(a, b, c)
#endif

#ifndef DBG_DEM_GETEVENTEXTENDEDDATARECORD_EXIT
/** \brief Exit point of function Dem_GetEventExtendedDataRecord() */
#define DBG_DEM_GETEVENTEXTENDEDDATARECORD_EXIT(a, b, c, d)
#endif

#ifndef DBG_DEM_GETEVENTMEMORYOVERFLOW_ENTRY
/** \brief Entry point of function Dem_GetEventMemoryOverflow() */
#define DBG_DEM_GETEVENTMEMORYOVERFLOW_ENTRY(a, b)
#endif

#ifndef DBG_DEM_GETEVENTMEMORYOVERFLOW_EXIT
/** \brief Exit point of function Dem_GetEventMemoryOverflow() */
#define DBG_DEM_GETEVENTMEMORYOVERFLOW_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_SETDTCSUPPRESSION_ENTRY
/** \brief Entry point of function Dem_SetDTCSuppression() */
#define DBG_DEM_SETDTCSUPPRESSION_ENTRY(a, b, c)
#endif

#ifndef DBG_DEM_SETDTCSUPPRESSION_EXIT
/** \brief Exit point of function Dem_SetDTCSuppression() */
#define DBG_DEM_SETDTCSUPPRESSION_EXIT(a, b, c, d)
#endif

#ifndef DBG_DEM_MAINFUNCTION_ENTRY
/** \brief Entry point of function Dem_MainFunction() */
#define DBG_DEM_MAINFUNCTION_ENTRY()
#endif

#ifndef DBG_DEM_MAINFUNCTION_EXIT
/** \brief Exit point of function Dem_MainFunction() */
#define DBG_DEM_MAINFUNCTION_EXIT()
#endif

#ifndef DBG_DEM_NVMGETNVRAMDATASTATUS_ENTRY
/** \brief Entry point of function Dem_NvMGetNvRAMDataStatus() */
#define DBG_DEM_NVMGETNVRAMDATASTATUS_ENTRY()
#endif

#ifndef DBG_DEM_NVMGETNVRAMDATASTATUS_EXIT
/** \brief Exit point of function Dem_NvMGetNvRAMDataStatus() */
#define DBG_DEM_NVMGETNVRAMDATASTATUS_EXIT(a)
#endif

#ifndef DBG_DEM_RESETNVDATA_ENTRY
/** \brief Entry point of function Dem_ResetNvData() */
#define DBG_DEM_RESETNVDATA_ENTRY()
#endif

#ifndef DBG_DEM_RESETNVDATA_EXIT
/** \brief Exit point of function Dem_ResetNvData() */
#define DBG_DEM_RESETNVDATA_EXIT()
#endif

#ifndef DBG_DEM_RESTOREIMMEDIATEDATA_ENTRY
/** \brief Entry point of function Dem_RestoreImmediateData() */
#define DBG_DEM_RESTOREIMMEDIATEDATA_ENTRY()
#endif

#ifndef DBG_DEM_RESTOREIMMEDIATEDATA_EXIT
/** \brief Exit point of function Dem_RestoreImmediateData() */
#define DBG_DEM_RESTOREIMMEDIATEDATA_EXIT()
#endif

#ifndef DBG_DEM_READERRORQUEUEENTRY_ENTRY
/** \brief Entry point of function Dem_ReadErrorQueueEntry() */
#define DBG_DEM_READERRORQUEUEENTRY_ENTRY(a)
#endif

#ifndef DBG_DEM_READERRORQUEUEENTRY_EXIT
/** \brief Exit point of function Dem_ReadErrorQueueEntry() */
#define DBG_DEM_READERRORQUEUEENTRY_EXIT(a, b)
#endif

#ifndef DBG_DEM_INVALIDATEERRORQUEUEENTRY_ENTRY
/** \brief Entry point of function Dem_InvalidateErrorQueueEntry() */
#define DBG_DEM_INVALIDATEERRORQUEUEENTRY_ENTRY(a)
#endif

#ifndef DBG_DEM_INVALIDATEERRORQUEUEENTRY_EXIT
/** \brief Exit point of function Dem_InvalidateErrorQueueEntry() */
#define DBG_DEM_INVALIDATEERRORQUEUEENTRY_EXIT(a)
#endif

#ifndef DBG_DEM_WRITEERRORQUEUEENTRY_ENTRY
/** \brief Entry point of function Dem_WriteErrorQueueEntry() */
#define DBG_DEM_WRITEERRORQUEUEENTRY_ENTRY(a, b)
#endif

#ifndef DBG_DEM_WRITEERRORQUEUEENTRY_EXIT
/** \brief Exit point of function Dem_WriteErrorQueueEntry() */
#define DBG_DEM_WRITEERRORQUEUEENTRY_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_CHECKERRORQUEUEENTRY_ENTRY
/** \brief Entry point of function Dem_CheckErrorQueueEntry() */
#define DBG_DEM_CHECKERRORQUEUEENTRY_ENTRY(a, b)
#endif

#ifndef DBG_DEM_CHECKERRORQUEUEENTRY_EXIT
/** \brief Exit point of function Dem_CheckErrorQueueEntry() */
#define DBG_DEM_CHECKERRORQUEUEENTRY_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_GETPFFENTRYDATAPTR_ENTRY
/** \brief Entry point of function Dem_GetPFFEntryDataPtr() */
#define DBG_DEM_GETPFFENTRYDATAPTR_ENTRY(a)
#endif

#ifndef DBG_DEM_GETPFFENTRYDATAPTR_EXIT
/** \brief Exit point of function Dem_GetPFFEntryDataPtr() */
#define DBG_DEM_GETPFFENTRYDATAPTR_EXIT(a, b)
#endif

#ifndef DBG_DEM_UPDATEAGINGCOUNTER_ENTRY
/** \brief Entry point of function Dem_UpdateAgingCounter() */
#define DBG_DEM_UPDATEAGINGCOUNTER_ENTRY(a)
#endif

#ifndef DBG_DEM_UPDATEAGINGCOUNTER_EXIT
/** \brief Exit point of function Dem_UpdateAgingCounter() */
#define DBG_DEM_UPDATEAGINGCOUNTER_EXIT(a)
#endif

#ifndef DBG_DEM_BEGINPREPAREGATEENTRY_ENTRY
/** \brief Entry point of function Dem_BeginPrepareGateEntry() */
#define DBG_DEM_BEGINPREPAREGATEENTRY_ENTRY(a)
#endif

#ifndef DBG_DEM_BEGINPREPAREGATEENTRY_EXIT
/** \brief Exit point of function Dem_BeginPrepareGateEntry() */
#define DBG_DEM_BEGINPREPAREGATEENTRY_EXIT(a, b)
#endif

#ifndef DBG_DEM_ENDPREPAREGATEENTRY_ENTRY
/** \brief Entry point of function Dem_EndPrepareGateEntry() */
#define DBG_DEM_ENDPREPAREGATEENTRY_ENTRY(a, b)
#endif

#ifndef DBG_DEM_ENDPREPAREGATEENTRY_EXIT
/** \brief Exit point of function Dem_EndPrepareGateEntry() */
#define DBG_DEM_ENDPREPAREGATEENTRY_EXIT(a, b)
#endif

#ifndef DBG_DEM_CLEARAGEDEVENTENTRY_ENTRY
/** \brief Entry point of function Dem_ClearAgedEventEntry() */
#define DBG_DEM_CLEARAGEDEVENTENTRY_ENTRY(a, b)
#endif

#ifndef DBG_DEM_CLEARAGEDEVENTENTRY_EXIT
/** \brief Exit point of function Dem_ClearAgedEventEntry() */
#define DBG_DEM_CLEARAGEDEVENTENTRY_EXIT(a, b)
#endif

#ifndef DBG_DEM_GETEVSTBITVAL_ENTRY
/** \brief Entry point of function Dem_GetEvStBitVal() */
#define DBG_DEM_GETEVSTBITVAL_ENTRY(a, b)
#endif

#ifndef DBG_DEM_GETEVSTBITVAL_EXIT
/** \brief Exit point of function Dem_GetEvStBitVal() */
#define DBG_DEM_GETEVSTBITVAL_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_PROCESSEVENTENTRY_ENTRY
/** \brief Entry point of function Dem_ProcessEventEntry() */
#define DBG_DEM_PROCESSEVENTENTRY_ENTRY(a, b, c)
#endif

#ifndef DBG_DEM_PROCESSEVENTENTRY_EXIT
/** \brief Exit point of function Dem_ProcessEventEntry() */
#define DBG_DEM_PROCESSEVENTENTRY_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_PROCESSEVENTNOTIFICATIONS_ENTRY
/** \brief Entry point of function Dem_ProcessEventEntryNotifications() */
#define DBG_DEM_PROCESSEVENTNOTIFICATIONS_ENTRY(a)
#endif

#ifndef DBG_DEM_PROCESSEVENTNOTIFICATIONS_EXIT
/** \brief Exit point of function Dem_ProcessEventEntryNotifications() */
#define DBG_DEM_PROCESSEVENTNOTIFICATIONS_EXIT(a)
#endif

#ifndef DBG_DEM_PROCESSBSWEVENTWIRBIT_ENTRY
/** \brief Entry point of function Dem_ProcessBSWEventWIRBit() */
#define DBG_DEM_PROCESSBSWEVENTWIRBIT_ENTRY()
#endif

#ifndef DBG_DEM_PROCESSBSWEVENTWIRBIT_EXIT
/** \brief Exit point of function Dem_ProcessBSWEventWIRBit() */
#define DBG_DEM_PROCESSBSWEVENTWIRBIT_EXIT()
#endif

#ifndef DBG_DEM_FINDORALLOCATEEVENTENTRY_ENTRY
/** \brief Entry point of function Dem_FindOrAllocateEventEntry() */
#define DBG_DEM_FINDORALLOCATEEVENTENTRY_ENTRY(a, b, c, d ,e)
#endif

#ifndef DBG_DEM_FINDORALLOCATEEVENTENTRY_EXIT
/** \brief Exit point of function Dem_FindOrAllocateEventEntry() */
#define DBG_DEM_FINDORALLOCATEEVENTENTRY_EXIT(a, b, c, d, e, f)
#endif

#ifndef DBG_DEM_REPLACEEVENTENTRY_ENTRY
/** \brief Entry point of function Dem_ReplaceEventEntry() */
#define DBG_DEM_REPLACEEVENTENTRY_ENTRY(a, b, c, d, e, f)
#endif

#ifndef DBG_DEM_REPLACEEVENTENTRY_EXIT
/** \brief Exit point of function Dem_ReplaceEventEntry() */
#define DBG_DEM_REPLACEEVENTENTRY_EXIT(a, b, c, d, e, f, g)
#endif

#ifndef DBG_DEM_PROCESSEVENTENTRYFFDATA_ENTRY
/** \brief Entry point of function Dem_ProcessEventEntryFFData() */
#define DBG_DEM_PROCESSEVENTENTRYFFDATA_ENTRY(a, b)
#endif

#ifndef DBG_DEM_PROCESSEVENTENTRYFFDATA_EXIT
/** \brief Exit point of function Dem_ProcessEventEntryFFData() */
#define DBG_DEM_PROCESSEVENTENTRYFFDATA_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_PROCESSEVENTENTRYEDATA_ENTRY
/** \brief Entry point of function Dem_ProcessEventEntryEData() */
#define DBG_DEM_PROCESSEVENTENTRYEDATA_ENTRY(a, b, c)
#endif

#ifndef DBG_DEM_PROCESSEVENTENTRYEDATA_EXIT
/** \brief Exit point of function Dem_ProcessEventEntryEData() */
#define DBG_DEM_PROCESSEVENTENTRYEDATA_EXIT(a, b, c, d)
#endif

#ifndef DBG_DEM_STOREFF_ENTRY
/** \brief Entry point of function Dem_StoreFF() */
#define DBG_DEM_STOREFF_ENTRY(a, b)
#endif

#ifndef DBG_DEM_STOREFF_EXIT
/** \brief Exit point of function Dem_StoreFF() */
#define DBG_DEM_STOREFF_EXIT(a, b)
#endif

#ifndef DBG_DEM_STOREED_ENTRY
/** \brief Entry point of function Dem_StoreED() */
#define DBG_DEM_STOREED_ENTRY(a, b, c)
#endif

#ifndef DBG_DEM_STOREED_EXIT
/** \brief Exit point of function Dem_StoreED() */
#define DBG_DEM_STOREED_EXIT(a, b, c, d)
#endif

#ifndef DBG_DEM_ASSEMBLEEXTENDEDDATA_ENTRY
/** \brief Entry point of function Dem_AssembleExtendedData() */
#define DBG_DEM_ASSEMBLEEXTENDEDDATA_ENTRY(a, b, c)
#endif

#ifndef DBG_DEM_ASSEMBLEEXTENDEDDATA_EXIT
/** \brief Exit point of function Dem_AssembleExtendedData() */
#define DBG_DEM_ASSEMBLEEXTENDEDDATA_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_SEARCHFOREMPTYENTRY_ENTRY
/** \brief Entry point of function Dem_SearchForEmptyEntry() */
#define DBG_DEM_SEARCHFOREMPTYENTRY_ENTRY(a, b, c)
#endif

#ifndef DBG_DEM_SEARCHFOREMPTYENTRY_EXIT
/** \brief Exit point of function Dem_SearchForEmptyEntry() */
#define DBG_DEM_SEARCHFOREMPTYENTRY_EXIT(a, b, c, d)
#endif

#ifndef DBG_DEM_SEARCHFORENTRYTOREPLACE_ENTRY
/** \brief Entry point of function Dem_SearchForEntryToReplace() */
#define DBG_DEM_SEARCHFORENTRYTOREPLACE_ENTRY(a, b, c, d)
#endif

#ifndef DBG_DEM_SEARCHFORENTRYTOREPLACE_EXIT
/** \brief Exit point of function Dem_SearchForEntryToReplace() */
#define DBG_DEM_SEARCHFORENTRYTOREPLACE_EXIT(a, b, c, d, e)
#endif

#ifndef DBG_DEM_UPDATEOCCURRENCEORDER_ENTRY
/** \brief Entry point of function Dem_UpdateOccurrenceOrder() */
#define DBG_DEM_UPDATEOCCURRENCEORDER_ENTRY(a)
#endif

#ifndef DBG_DEM_UPDATEOCCURRENCEORDER_EXIT
/** \brief Exit point of function Dem_UpdateOccurrenceOrder() */
#define DBG_DEM_UPDATEOCCURRENCEORDER_EXIT(a, b)
#endif

#ifndef DBG_DEM_REARRANGEOCCURRENCEORDER_ENTRY
/** \brief Entry point of function Dem_RearrangeOccurrenceOrder() */
#define DBG_DEM_REARRANGEOCCURRENCEORDER_ENTRY(a)
#endif

#ifndef DBG_DEM_REARRANGEOCCURRENCEORDER_EXIT
/** \brief Exit point of function Dem_RearrangeOccurrenceOrder() */
#define DBG_DEM_REARRANGEOCCURRENCEORDER_EXIT(a)
#endif

#ifndef DBG_DEM_INITMAXOCCORDER_ENTRY
/** \brief Entry point of function Dem_InitMaxOccOrder() */
#define DBG_DEM_INITMAXOCCORDER_ENTRY()
#endif

#ifndef DBG_DEM_INITMAXOCCORDER_EXIT
/** \brief Exit point of function Dem_InitMaxOccOrder() */
#define DBG_DEM_INITMAXOCCORDER_EXIT()
#endif

#ifndef DBG_DEM_PROCESSFAULTCONFIRMATION_ENTRY
/** \brief Entry point of function Dem_ProcessFaultConfirmation() */
#define DBG_DEM_PROCESSFAULTCONFIRMATION_ENTRY()
#endif

#ifndef DBG_DEM_PROCESSFAULTCONFIRMATION_EXIT
/** \brief Exit point of function Dem_ProcessFaultConfirmation() */
#define DBG_DEM_PROCESSFAULTCONFIRMATION_EXIT()
#endif

#ifndef DBG_DEM_PROCESSFAILURECOUNTERRESET_ENTRY
/** \brief Entry point of function Dem_ProcessFailureCounterReset() */
#define DBG_DEM_PROCESSFAILURECOUNTERRESET_ENTRY(a, b)
#endif

#ifndef DBG_DEM_PROCESSFAILURECOUNTERRESET_EXIT
/** \brief Exit point of function Dem_ProcessFailureCounterReset() */
#define DBG_DEM_PROCESSFAILURECOUNTERRESET_EXIT(a, b)
#endif

#ifndef DBG_DEM_UPDATEFAILURECOUNTERCYCLESTART_ENTRY
/** \brief Entry point of function Dem_UpdateFailureCounterCycleStart() */
#define DBG_DEM_UPDATEFAILURECOUNTERCYCLESTART_ENTRY(a, b)
#endif

#ifndef DBG_DEM_UPDATEFAILURECOUNTERCYCLESTART_EXIT
/** \brief Exit point of function Dem_UpdateFailureCounterCycleStart() */
#define DBG_DEM_UPDATEFAILURECOUNTERCYCLESTART_EXIT(a, b)
#endif

#ifndef DBG_DEM_INCREMENTFAILURECOUNTER_ENTRY
/** \brief Entry point of function Dem_IncrementFailureCounter() */
#define DBG_DEM_INCREMENTFAILURECOUNTER_ENTRY(a)
#endif

#ifndef DBG_DEM_INCREMENTFAILURECOUNTER_EXIT
/** \brief Exit point of function Dem_IncrementFailureCounter() */
#define DBG_DEM_INCREMENTFAILURECOUNTER_EXIT(a)
#endif

#ifndef DBG_DEM_SEARCHFORFAILURECOUNTERBUFFERENTRY_ENTRY
/** \brief Entry point of function Dem_SearchForFailureCounterBufferEntry() */
#define DBG_DEM_SEARCHFORFAILURECOUNTERBUFFERENTRY_ENTRY(a, b)
#endif

#ifndef DBG_DEM_SEARCHFORFAILURECOUNTERBUFFERENTRY_EXIT
/** \brief Exit point of function Dem_SearchForFailureCounterBufferEntry() */
#define DBG_DEM_SEARCHFORFAILURECOUNTERBUFFERENTRY_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_SEARCHFOREMPTYFAILURECOUNTERBUFFERENTRY_ENTRY
/** \brief Entry point of function Dem_SearchForEmptyFailureCounterBufferEntry() */
#define DBG_DEM_SEARCHFOREMPTYFAILURECOUNTERBUFFERENTRY_ENTRY(a)
#endif

#ifndef DBG_DEM_SEARCHFOREMPTYFAILURECOUNTERBUFFERENTRY_EXIT
/** \brief Exit point of function Dem_SearchForEmptyFailureCounterBufferEntry() */
#define DBG_DEM_SEARCHFOREMPTYFAILURECOUNTERBUFFERENTRY_EXIT(a, b)
#endif

#ifndef DBG_DEM_CHECKINTDATAELEMENTUSAGE_ENTRY
/** \brief Entry point of function Dem_CheckIntDataElementUsage() */
#define DBG_DEM_CHECKINTDATAELEMENTUSAGE_ENTRY(a, b)
#endif

#ifndef DBG_DEM_CHECKINTDATAELEMENTUSAGE_EXIT
/** \brief Exit point of function Dem_CheckIntDataElementUsage() */
#define DBG_DEM_CHECKINTDATAELEMENTUSAGE_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_CBTRIGGERONOVFINDSET_ENTRY
/** \brief Entry point of function Dem_CbTriggerOnOvfIndSet() */
#define DBG_DEM_CBTRIGGERONOVFINDSET_ENTRY(a)
#endif

#ifndef DBG_DEM_CBTRIGGERONOVFINDSET_EXIT
/** \brief Exit point of function Dem_CbTriggerOnOvfIndSet() */
#define DBG_DEM_CBTRIGGERONOVFINDSET_EXIT(a)
#endif

#ifndef DBG_DEM_PROCESSHEALING_ENTRY
/** \brief Entry point of function Dem_ProcessHealing() */
#define DBG_DEM_PROCESSHEALING_ENTRY(a)
#endif

#ifndef DBG_DEM_PROCESSHEALING_EXIT
/** \brief Exit point of function Dem_ProcessHealing() */
#define DBG_DEM_PROCESSHEALING_EXIT(a)
#endif

#ifndef DBG_DEM_PROCESSHEALINGCYCLECOUNTER_ENTRY
/** \brief Entry point of function Dem_ProcessHealingCycleCounter() */
#define DBG_DEM_PROCESSHEALINGCYCLECOUNTER_ENTRY(a)
#endif

#ifndef DBG_DEM_PROCESSHEALINGCYCLECOUNTER_EXIT
/** \brief Exit point of function Dem_ProcessHealingCycleCounter() */
#define DBG_DEM_PROCESSHEALINGCYCLECOUNTER_EXIT(a)
#endif

#ifndef DBG_DEM_PROCESSFAILURECYCLECOUNTER_ENTRY
/** \brief Entry point of function Dem_ProcessFailureCycleCounter() */
#define DBG_DEM_PROCESSFAILURECYCLECOUNTER_ENTRY(a)
#endif

#ifndef DBG_DEM_PROCESSFAILURECYCLECOUNTER_EXIT
/** \brief Exit point of function Dem_ProcessFailureCycleCounter() */
#define DBG_DEM_PROCESSFAILURECYCLECOUNTER_EXIT(a)
#endif

#ifndef DBG_DEM_CHECKWIROFFCRITERIAFULFILLED_ENTRY
/** \brief Entry point of function Dem_CheckWIROffCriteriaFulfilled() */
#define DBG_DEM_CHECKWIROFFCRITERIAFULFILLED_ENTRY(a)
#endif

#ifndef DBG_DEM_CHECKWIROFFCRITERIAFULFILLED_EXIT
/** \brief Exit point of function Dem_CheckWIROffCriteriaFulfilled() */
#define DBG_DEM_CHECKWIROFFCRITERIAFULFILLED_EXIT(a, b)
#endif

#ifndef DBG_DEM_SETCYCLECOUNTERROLE_ENTRY
/** \brief Entry point of function Dem_SetCycleCounterRole() */
#define DBG_DEM_SETCYCLECOUNTERROLE_ENTRY(a, b)
#endif

#ifndef DBG_DEM_SETCYCLECOUNTERROLE_EXIT
/** \brief Exit point of function Dem_SetCycleCounterRole() */
#define DBG_DEM_SETCYCLECOUNTERROLE_EXIT(a, b)
#endif

#ifndef DBG_DEM_DEBOUNCEFREQUENCYTIMERTICK_ENTRY
/** \brief Entry point of function Dem_DebounceFrequencyTimerTick() */
#define DBG_DEM_DEBOUNCEFREQUENCYTIMERTICK_ENTRY()
#endif

#ifndef DBG_DEM_DEBOUNCEFREQUENCYTIMERTICK_EXIT
/** \brief Exit point of function Dem_DebounceFrequencyTimerTick() */
#define DBG_DEM_DEBOUNCEFREQUENCYTIMERTICK_EXIT()
#endif

#ifndef DBG_DEM_DEBOUNCETIMETIMERTICK_ENTRY
/** \brief Entry point of function Dem_DebounceTimeTimerTick() */
#define DBG_DEM_DEBOUNCETIMETIMERTICK_ENTRY()
#endif

#ifndef DBG_DEM_DEBOUNCETIMETIMERTICK_EXIT
/** \brief Exit point of function Dem_DebounceTimeTimerTick() */
#define DBG_DEM_DEBOUNCETIMETIMERTICK_EXIT()
#endif

#ifndef DBG_DEM_GBIDTC_ENTRY
/** \brief Entry point of function Dem_GbiDTC() */
#define DBG_DEM_GBIDTC_ENTRY(a)
#endif

#ifndef DBG_DEM_GBIDTC_EXIT
/** \brief Exit point of function Dem_GbiDTC() */
#define DBG_DEM_GBIDTC_EXIT(a, b)
#endif

#ifndef DBG_DEM_GBIDTCKIND_ENTRY
/** \brief Entry point of function Dem_GbiDTCKind() */
#define DBG_DEM_GBIDTCKIND_ENTRY(a)
#endif

#ifndef DBG_DEM_GBIDTCKIND_EXIT
/** \brief Exit point of function Dem_GbiDTCKind() */
#define DBG_DEM_GBIDTCKIND_EXIT(a, b)
#endif

#ifndef DBG_DEM_GBIDTCORIGIN_ENTRY
/** \brief Entry point of function Dem_GbiDTCOrigin() */
#define DBG_DEM_GBIDTCORIGIN_ENTRY(a)
#endif

#ifndef DBG_DEM_GBIDTCORIGIN_EXIT
/** \brief Exit point of function Dem_GbiDTCOrigin() */
#define DBG_DEM_GBIDTCORIGIN_EXIT(a, b)
#endif

#ifndef DBG_DEM_GBIDTCORIGINIDX_ENTRY
/** \brief Entry point of function Dem_GbiDTCOrigin() */
#define DBG_DEM_GBIDTCORIGINIDX_ENTRY(a)
#endif

#ifndef DBG_DEM_GBIDTCORIGINIDX_EXIT
/** \brief Exit point of function Dem_GbiDTCOrigin() */
#define DBG_DEM_GBIDTCORIGINIDX_EXIT(a, b)
#endif

#ifndef DBG_DEM_GBIDTCGROUPIDX_ENTRY
/** \brief Entry point of function Dem_GbiDTCGroupIdx() */
#define DBG_DEM_GBIDTCGROUPIDX_ENTRY(a)
#endif

#ifndef DBG_DEM_GBIDTCGROUPIDX_EXIT
/** \brief Exit point of function Dem_GbiDTCGroupIdx() */
#define DBG_DEM_GBIDTCGROUPIDX_EXIT(a, b)
#endif

#ifndef DBG_DEM_GBIIMMEDIATESTORAGE_ENTRY
/** \brief Entry point of function Dem_GbiImmediateStorage() */
#define DBG_DEM_GBIIMMEDIATESTORAGE_ENTRY(a)
#endif

#ifndef DBG_DEM_GBIIMMEDIATESTORAGE_EXIT
/** \brief Exit point of function Dem_GbiImmediateStorage() */
#define DBG_DEM_GBIIMMEDIATESTORAGE_EXIT(a, b)
#endif

#ifndef DBG_DEM_GBIDTCSEVERITY_ENTRY
/** \brief Entry point of function Dem_GbiDTCSeverity() */
#define DBG_DEM_GBIDTCSEVERITY_ENTRY(a)
#endif

#ifndef DBG_DEM_GBIDTCSEVERITY_EXIT
/** \brief Exit point of function Dem_GbiDTCSeverity() */
#define DBG_DEM_GBIDTCSEVERITY_EXIT(a, b)
#endif

#ifndef DBG_DEM_GBIDTCFUNCTIONALUNIT_ENTRY
/** \brief Entry point of function Dem_GbiDTCFunctionalUnit() */
#define DBG_DEM_GBIDTCFUNCTIONALUNIT_ENTRY(a)
#endif

#ifndef DBG_DEM_GBIDTCFUNCTIONALUNIT_EXIT
/** \brief Exit point of function Dem_GbiDTCFunctionalUnit() */
#define DBG_DEM_GBIDTCFUNCTIONALUNIT_EXIT(a, b)
#endif

#ifndef DBG_DEM_GBIENABLEPRESTORAGE_ENTRY
/** \brief Entry point of function Dem_GbiEnablePrestorage() */
#define DBG_DEM_GBIENABLEPRESTORAGE_ENTRY(a)
#endif

#ifndef DBG_DEM_GBIENABLEPRESTORAGE_EXIT
/** \brief Exit point of function Dem_GbiEnablePrestorage() */
#define DBG_DEM_GBIENABLEPRESTORAGE_EXIT(a, b)
#endif

#ifndef DBG_DEM_GBIFFCLASSIDX_ENTRY
/** \brief Entry point of function Dem_GbiFFClassIdx() */
#define DBG_DEM_GBIFFCLASSIDX_ENTRY(a)
#endif

#ifndef DBG_DEM_GBIFFCLASSIDX_EXIT
/** \brief Exit point of function Dem_GbiFFClassIdx() */
#define DBG_DEM_GBIFFCLASSIDX_EXIT(a, b)
#endif

#ifndef DBG_DEM_GBIMAXNUMFFRECS_ENTRY
/** \brief Entry point of function Dem_GbiMaxNumFFRecs() */
#define DBG_DEM_GBIMAXNUMFFRECS_ENTRY(a)
#endif

#ifndef DBG_DEM_GBIMAXNUMFFRECS_EXIT
/** \brief Exit point of function Dem_GbiMaxNumFFRecs() */
#define DBG_DEM_GBIMAXNUMFFRECS_EXIT(a, b)
#endif

#ifndef DBG_DEM_GBIFFRECNUMCLASSIDX_ENTRY
/** \brief Entry point of function Dem_GbiFFRecNumClassIdx() */
#define DBG_DEM_GBIFFRECNUMCLASSIDX_ENTRY(a)
#endif

#ifndef DBG_DEM_GBIFFRECNUMCLASSIDX_EXIT
/** \brief Exit point of function Dem_GbiFFRecNumClassIdx() */
#define DBG_DEM_GBIFFRECNUMCLASSIDX_EXIT(a, b)
#endif

#ifndef DBG_DEM_GBIEDCLASSIDX_ENTRY
/** \brief Entry point of function Dem_GbiEDClassIdx() */
#define DBG_DEM_GBIEDCLASSIDX_ENTRY(a)
#endif

#ifndef DBG_DEM_GBIEDCLASSIDX_EXIT
/** \brief Exit point of function Dem_GbiEDClassIdx() */
#define DBG_DEM_GBIEDCLASSIDX_EXIT(a, b)
#endif

#ifndef DBG_DEM_GBIOPCYCLEIDX_ENTRY
/** \brief Entry point of function Dem_GbiOpCycleIdx() */
#define DBG_DEM_GBIOPCYCLEIDX_ENTRY(a)
#endif

#ifndef DBG_DEM_GBIOPCYCLEIDX_EXIT
/** \brief Exit point of function Dem_GbiOpCycleIdx() */
#define DBG_DEM_GBIOPCYCLEIDX_EXIT(a, b)
#endif

#ifndef DBG_DEM_GBINUMAGINGCYCLES_ENTRY
/** \brief Entry point of function Dem_GbiNumAgingCycles() */
#define DBG_DEM_GBINUMAGINGCYCLES_ENTRY(a)
#endif

#ifndef DBG_DEM_GBINUMAGINGCYCLES_EXIT
/** \brief Exit point of function Dem_GbiNumAgingCycles() */
#define DBG_DEM_GBINUMAGINGCYCLES_EXIT(a, b)
#endif

#ifndef DBG_DEM_GBIAGINGCYCLEIDX_ENTRY
/** \brief Entry point of function Dem_GbiAgingCycleIdx() */
#define DBG_DEM_GBIAGINGCYCLEIDX_ENTRY(a)
#endif

#ifndef DBG_DEM_GBIAGINGCYCLEIDX_EXIT
/** \brief Exit point of function Dem_GbiAgingCycleIdx() */
#define DBG_DEM_GBIAGINGCYCLEIDX_EXIT(a, b)
#endif

#ifndef DBG_DEM_GBIENCONDLNKIDX_ENTRY
/** \brief Entry point of function Dem_GbiEnCondLnkIdx() */
#define DBG_DEM_GBIENCONDLNKIDX_ENTRY(a)
#endif

#ifndef DBG_DEM_GBIENCONDLNKIDX_EXIT
/** \brief Exit point of function Dem_GbiEnCondLnkIdx() */
#define DBG_DEM_GBIENCONDLNKIDX_EXIT(a, b)
#endif

#ifndef DBG_DEM_GBINUMENCOND_ENTRY
/** \brief Entry point of function Dem_GbiNumEnCond() */
#define DBG_DEM_GBINUMENCOND_ENTRY(a)
#endif

#ifndef DBG_DEM_GBINUMENCOND_EXIT
/** \brief Exit point of function Dem_GbiNumEnCond() */
#define DBG_DEM_GBINUMENCOND_EXIT(a, b)
#endif

#ifndef DBG_DEM_GBIINDICATORUSED_ENTRY
/** \brief Entry point of function Dem_GbiIndicatorUsed() */
#define DBG_DEM_GBIINDICATORUSED_ENTRY(a)
#endif

#ifndef DBG_DEM_GBIINDICATORUSED_EXIT
/** \brief Exit point of function Dem_GbiIndicatorUsed() */
#define DBG_DEM_GBIINDICATORUSED_EXIT(a, b)
#endif

#ifndef DBG_DEM_GBIPRIORITY_ENTRY
/** \brief Entry point of function Dem_GbiPriority() */
#define DBG_DEM_GBIPRIORITY_ENTRY(a)
#endif

#ifndef DBG_DEM_GBIPRIORITY_EXIT
/** \brief Exit point of function Dem_GbiPriority() */
#define DBG_DEM_GBIPRIORITY_EXIT(a, b)
#endif

#ifndef DBG_DEM_GBIDEBOUNCEALGO_ENTRY
/** \brief Entry point of function Dem_GbiDebounceAlgo() */
#define DBG_DEM_GBIDEBOUNCEALGO_ENTRY(a)
#endif

#ifndef DBG_DEM_GBIDEBOUNCEALGO_EXIT
/** \brief Exit point of function Dem_GbiDebounceAlgo() */
#define DBG_DEM_GBIDEBOUNCEALGO_EXIT(a, b)
#endif

#ifndef DBG_DEM_GBIDEBOUNCEIDX_ENTRY
/** \brief Entry point of function Dem_GbiDebounceIdx() */
#define DBG_DEM_GBIDEBOUNCEIDX_ENTRY(a)
#endif

#ifndef DBG_DEM_GBIDEBOUNCEIDX_EXIT
/** \brief Exit point of function Dem_GbiDebounceIdx() */
#define DBG_DEM_GBIDEBOUNCEIDX_EXIT(a, b)
#endif

#ifndef DBG_DEM_GBIEVENTKIND_ENTRY
/** \brief Entry point of function Dem_GbiEventKind() */
#define DBG_DEM_GBIEVENTKIND_ENTRY(a)
#endif

#ifndef DBG_DEM_GBIEVENTKIND_EXIT
/** \brief Exit point of function Dem_GbiEventKind() */
#define DBG_DEM_GBIEVENTKIND_EXIT(a, b)
#endif

#ifndef DBG_DEM_GBIEVENTFAILURECLASSIDX_ENTRY
/** \brief Entry point of function Dem_GbiEventFailureClassIdx() */
#define DBG_DEM_GBIEVENTFAILURECLASSIDX_ENTRY(a)
#endif

#ifndef DBG_DEM_GBIEVENTFAILURECLASSIDX_EXIT
/** \brief Exit point of function Dem_GbiEventFailureClassIdx() */
#define DBG_DEM_GBIEVENTFAILURECLASSIDX_EXIT(a, b)
#endif

#ifndef DBG_DEM_GETPFFINDEX_ENTRY
/** \brief Entry point of function Dem_GetPFFIndex() */
#define DBG_DEM_GETPFFINDEX_ENTRY(a)
#endif

#ifndef DBG_DEM_GETPFFINDEX_EXIT
/** \brief Exit point of function Dem_GetPFFIndex() */
#define DBG_DEM_GETPFFINDEX_EXIT(a, b)
#endif

#ifndef DBG_DEM_GETWIRONCRITERIAFULFILLEDFLAGSIDX_ENTRY
/** \brief Entry point of function Dem_GetWIROnCriteriaFulfilledFlagsIdx() */
#define DBG_DEM_GETWIRONCRITERIAFULFILLEDFLAGSIDX_ENTRY(a)
#endif

#ifndef DBG_DEM_GETWIRONCRITERIAFULFILLEDFLAGSIDX_EXIT
/** \brief Exit point of function Dem_GetWIROnCriteriaFulfilledFlagsIdx() */
#define DBG_DEM_GETWIRONCRITERIAFULFILLEDFLAGSIDX_EXIT(a, b)
#endif

#ifndef DBG_DEM_GETBSWEVENTWIRSTATUSFLAGSINDEX_ENTRY
/** \brief Entry point of function Dem_GetBSWEventWIRStatusFlagsIndex() */
#define DBG_DEM_GETBSWEVENTWIRSTATUSFLAGSINDEX_ENTRY(a)
#endif

#ifndef DBG_DEM_GETBSWEVENTWIRSTATUSFLAGSINDEX_EXIT
/** \brief Exit point of function Dem_GetBSWEventWIRStatusFlagsIndex() */
#define DBG_DEM_GETBSWEVENTWIRSTATUSFLAGSINDEX_EXIT(a, b)
#endif

#ifndef DBG_DEM_GETEVIDBYDTC_ENTRY
/** \brief Entry point of function Dem_GetEvIdByDTC() */
#define DBG_DEM_GETEVIDBYDTC_ENTRY(a, b, c, d)
#endif

#ifndef DBG_DEM_GETEVIDBYDTC_EXIT
/** \brief Exit point of function Dem_GetEvIdByDTC() */
#define DBG_DEM_GETEVIDBYDTC_EXIT(a, b, c, d, e)
#endif

#ifndef DBG_DEM_SEARCHFORENTRY_ENTRY
/** \brief Entry point of function Dem_SearchForEntry() */
#define DBG_DEM_SEARCHFORENTRY_ENTRY(a, b, c)
#endif

#ifndef DBG_DEM_SEARCHFORENTRY_EXIT
/** \brief Exit point of function Dem_SearchForEntry() */
#define DBG_DEM_SEARCHFORENTRY_EXIT(a, b, c, d)
#endif

#ifndef DBG_DEM_FINDDIDINDEX_ENTRY
/** \brief Entry point of function Dem_FindDIDIndex() */
#define DBG_DEM_FINDDIDINDEX_ENTRY(a, b)
#endif

#ifndef DBG_DEM_FINDDIDINDEX_EXIT
/** \brief Exit point of function Dem_FindDIDIndex() */
#define DBG_DEM_FINDDIDINDEX_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_FFENTRYDATA_ENTRY
/** \brief Entry point of function Dem_FFEntryData() */
#define DBG_DEM_FFENTRYDATA_ENTRY(a, b, c)
#endif

#ifndef DBG_DEM_FFENTRYDATA_EXIT
/** \brief Exit point of function Dem_FFEntryData() */
#define DBG_DEM_FFENTRYDATA_EXIT(a, b, c, d)
#endif

#ifndef DBG_DEM_CHECKFFRECNUMVALID_ENTRY
/** \brief Entry point of function Dem_CheckFFRecNumValid() */
#define DBG_DEM_CHECKFFRECNUMVALID_ENTRY(a, b)
#endif

#ifndef DBG_DEM_CHECKFFRECNUMVALID_EXIT
/** \brief Exit point of function Dem_CheckFFRecNumValid() */
#define DBG_DEM_CHECKFFRECNUMVALID_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_CHECKFFRECNUMSTORED_ENTRY
/** \brief Entry point of function Dem_CheckFFRecNumStored() */
#define DBG_DEM_CHECKFFRECNUMSTORED_ENTRY(a, b)
#endif

#ifndef DBG_DEM_CHECKFFRECNUMSTORED_EXIT
/** \brief Exit point of function Dem_CheckFFRecNumStored() */
#define DBG_DEM_CHECKFFRECNUMSTORED_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_EDENTRYDATA_ENTRY
/** \brief Entry point of function Dem_EDEntryData() */
#define DBG_DEM_EDENTRYDATA_ENTRY(a)
#endif

#ifndef DBG_DEM_EDENTRYDATA_EXIT
/** \brief Exit point of function Dem_EDEntryData() */
#define DBG_DEM_EDENTRYDATA_EXIT(a, b)
#endif

#ifndef DBG_DEM_INTVALENTRYDATA_ENTRY
/** \brief Entry point of function Dem_IntValEntryData() */
#define DBG_DEM_INTVALENTRYDATA_ENTRY(a)
#endif

#ifndef DBG_DEM_INTVALENTRYDATA_EXIT
/** \brief Exit point of function Dem_IntValEntryData() */
#define DBG_DEM_INTVALENTRYDATA_EXIT(a, b)
#endif

#ifndef DBG_DEM_FINDEDNUMINDEX_ENTRY
/** \brief Entry point of function Dem_FindEDNumIndex() */
#define DBG_DEM_FINDEDNUMINDEX_ENTRY(a, b)
#endif

#ifndef DBG_DEM_FINDEDNUMINDEX_EXIT
/** \brief Exit point of function Dem_FindEDNumIndex() */
#define DBG_DEM_FINDEDNUMINDEX_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_INTERNALSETEVENTSTATUS_ENTRY
/** \brief Entry point of function Dem_InternalSetEventStatus() */
#define DBG_DEM_INTERNALSETEVENTSTATUS_ENTRY(a, b)
#endif

#ifndef DBG_DEM_INTERNALSETEVENTSTATUS_EXIT
/** \brief Exit point of function Dem_InternalSetEventStatus() */
#define DBG_DEM_INTERNALSETEVENTSTATUS_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_UPDATEEVENTSTATUSONQUALIFICATION_ENTRY
/** \brief Entry point of function Dem_UpdateEventStatusOnQualification() */
#define DBG_DEM_UPDATEEVENTSTATUSONQUALIFICATION_ENTRY(a, b)
#endif

#ifndef DBG_DEM_UPDATEEVENTSTATUSONQUALIFICATION_EXIT
/** \brief Exit point of function Dem_UpdateEventStatusOnQualification() */
#define DBG_DEM_UPDATEEVENTSTATUSONQUALIFICATION_EXIT(a, b)
#endif

#ifndef DBG_DEM_CLEAREVENTENTRY_ENTRY
/** \brief Entry point of function Dem_ClearEntry() */
#define DBG_DEM_CLEAREVENTENTRY_ENTRY(a)
#endif

#ifndef DBG_DEM_CLEAREVENTENTRY_EXIT
/** \brief Exit point of function Dem_ClearEntry() */
#define DBG_DEM_CLEAREVENTENTRY_EXIT(a)
#endif

#ifndef DBG_DEM_SIZEOFENTRYDATA_ENTRY
/** \brief Entry point of function Dem_SizeOfEntryData() */
#define DBG_DEM_SIZEOFENTRYDATA_ENTRY(a)
#endif

#ifndef DBG_DEM_SIZEOFENTRYDATA_EXIT
/** \brief Exit point of function Dem_SizeOfEntryData() */
#define DBG_DEM_SIZEOFENTRYDATA_EXIT(a, b)
#endif

#ifndef DBG_DEM_NVMGATEENTRYPRIMARYBLOCKCALLBACK_ENTRY
/** \brief Entry point of function Dem_NvMGateEntryPrimaryBlockCallback() */
#define DBG_DEM_NVMGATEENTRYPRIMARYBLOCKCALLBACK_ENTRY(a, b)
#endif

#ifndef DBG_DEM_NVMGATEENTRYPRIMARYBLOCKCALLBACK_EXIT
/** \brief Exit point of function Dem_NvMGateEntryPrimaryBlockCallback() */
#define DBG_DEM_NVMGATEENTRYPRIMARYBLOCKCALLBACK_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_NVMGATEENTRYSECONDARYBLOCKCALLBACK_ENTRY
/** \brief Entry point of function Dem_NvMGateEntrySecondaryBlockCallback() */
#define DBG_DEM_NVMGATEENTRYSECONDARYBLOCKCALLBACK_ENTRY(a, b)
#endif

#ifndef DBG_DEM_NVMGATEENTRYSECONDARYBLOCKCALLBACK_EXIT
/** \brief Exit point of function Dem_NvMGateEntrySecondaryBlockCallback() */
#define DBG_DEM_NVMGATEENTRYSECONDARYBLOCKCALLBACK_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_NVMGATEENTRYMIRRORBLOCKCALLBACK_ENTRY
/** \brief Entry point of function Dem_NvMGateEntryMirrorBlockCallback() */
#define DBG_DEM_NVMGATEENTRYMIRRORBLOCKCALLBACK_ENTRY(a, b)
#endif

#ifndef DBG_DEM_NVMGATEENTRYMIRRORBLOCKCALLBACK_EXIT
/** \brief Exit point of function Dem_NvMGateEntryMirrorBlockCallback() */
#define DBG_DEM_NVMGATEENTRYMIRRORBLOCKCALLBACK_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_NVMGATEENTRYPERMANENTBLOCKCALLBACK_ENTRY
/** \brief Entry point of function Dem_NvMGateEntryPermanentBlockCallback() */
#define DBG_DEM_NVMGATEENTRYPERMANENTBLOCKCALLBACK_ENTRY(a, b)
#endif

#ifndef DBG_DEM_NVMGATEENTRYPERMANENTBLOCKCALLBACK_EXIT
/** \brief Exit point of function Dem_NvMGateEntryPermanentBlockCallback() */
#define DBG_DEM_NVMGATEENTRYPERMANENTBLOCKCALLBACK_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_NVMGATEENTRYBLOCKCALLBACK_ENTRY
/** \brief Entry point of function Dem_NvMGateEntryBlockCallback() */
#define DBG_DEM_NVMGATEENTRYBLOCKCALLBACK_ENTRY(a, b)
#endif

#ifndef DBG_DEM_NVMGATEENTRYBLOCKCALLBACK_EXIT
/** \brief Exit point of function Dem_NvMGateEntrytBlockCallback() */
#define DBG_DEM_NVMGATEENTRYBLOCKCALLBACK_EXIT(a, b)
#endif

#ifndef DBG_DEM_NVMREADCOPYEVENTSTATUSBLOCK_ENTRY
/** \brief Entry point of function Dem_NvMReadCopyEventStatusBlock() */
#define DBG_DEM_NVMREADCOPYEVENTSTATUSBLOCK_ENTRY(a)
#endif

#ifndef DBG_DEM_NVMREADCOPYEVENTSTATUSBLOCK_EXIT
/** \brief Exit point of function Dem_NvMReadCopyEventStatusBlock() */
#define DBG_DEM_NVMREADCOPYEVENTSTATUSBLOCK_EXIT(a, b)
#endif

#ifndef DBG_DEM_NVMWRITECOPYEVENTSTATUSBLOCK_ENTRY
/** \brief Entry point of function Dem_NvMWriteCopyEventStatusBlock() */
#define DBG_DEM_NVMWRITECOPYEVENTSTATUSBLOCK_ENTRY(a)
#endif

#ifndef DBG_DEM_NVMWRITECOPYEVENTSTATUSBLOCK_EXIT
/** \brief Exit point of function Dem_NvMWriteCopyEventStatusBlock() */
#define DBG_DEM_NVMWRITECOPYEVENTSTATUSBLOCK_EXIT(a, b)
#endif

#ifndef DBG_DEM_NVMEVENTSTATUSBLOCKCALLBACK_ENTRY
/** \brief Entry point of function Dem_NvMEventStatusBlockCallback() */
#define DBG_DEM_NVMEVENTSTATUSBLOCKCALLBACK_ENTRY(a, b)
#endif

#ifndef DBG_DEM_NVMEVENTSTATUSBLOCKCALLBACK_EXIT
/** \brief Exit point of function Dem_NvMEventStatusBlockCallback() */
#define DBG_DEM_NVMEVENTSTATUSBLOCKCALLBACK_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_CBINITMONITORFOREVENT_ENTRY
/** \brief Entry point of function Dem_CbInitMonitorForEvent() */
#define DBG_DEM_CBINITMONITORFOREVENT_ENTRY(a, b)
#endif

#ifndef DBG_DEM_CBINITMONITORFOREVENT_EXIT
/** \brief Exit point of function Dem_CbInitMonitorForEvent() */
#define DBG_DEM_CBINITMONITORFOREVENT_EXIT(a, b)
#endif

#ifndef DBG_DEM_CBTRIGGERONEVENTSTATUS_ENTRY
/** \brief Entry point of function Dem_CbTriggerOnEventStatus() */
#define DBG_DEM_CBTRIGGERONEVENTSTATUS_ENTRY(a, b, c)
#endif

#ifndef DBG_DEM_CBTRIGGERONEVENTSTATUS_EXIT
/** \brief Exit point of function Dem_CbTriggerOnEventStatus() */
#define DBG_DEM_CBTRIGGERONEVENTSTATUS_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_CBTRIGGERONEVENTDATA_ENTRY
/** \brief Entry point of function Dem_CbTriggerOnEventData() */
#define DBG_DEM_CBTRIGGERONEVENTDATA_ENTRY(a)
#endif

#ifndef DBG_DEM_CBTRIGGERONEVENTDATA_EXIT
/** \brief Exit point of function Dem_CbTriggerOnEventData() */
#define DBG_DEM_CBTRIGGERONEVENTDATA_EXIT(a)
#endif

#ifndef DBG_DEM_CBCLEAREVENTALLOWED_ENTRY
/** \brief Entry point of function Dem_CbClearEventAllowed() */
#define DBG_DEM_CBCLEAREVENTALLOWED_ENTRY(a, b)
#endif

#ifndef DBG_DEM_CBCLEAREVENTALLOWED_EXIT
/** \brief Exit point of function Dem_CbClearEventAllowed() */
#define DBG_DEM_CBCLEAREVENTALLOWED_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_CBGETFAULTDETECTIONCOUNTER_ENTRY
/** \brief Entry point of function Dem_CbGetFaultDetectionCounter() */
#define DBG_DEM_CBGETFAULTDETECTIONCOUNTER_ENTRY(a, b)
#endif

#ifndef DBG_DEM_CBGETFAULTDETECTIONCOUNTER_EXIT
/** \brief Exit point of function Dem_CbGetFaultDetectionCounter() */
#define DBG_DEM_CBGETFAULTDETECTIONCOUNTER_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_SIZEOFFF_ENTRY
/** \brief Entry point of function Dem_SizeOfFF() */
#define DBG_DEM_SIZEOFFF_ENTRY(a)
#endif

#ifndef DBG_DEM_SIZEOFFF_EXIT
/** \brief Exit point of function Dem_SizeOfFF() */
#define DBG_DEM_SIZEOFFF_EXIT(a, b)
#endif

#ifndef DBG_DEM_SIZEOFFFSEGMENT_ENTRY
/** \brief Entry point of function Dem_SizeOfFFSegment() */
#define DBG_DEM_SIZEOFFFSEGMENT_ENTRY(a)
#endif

#ifndef DBG_DEM_SIZEOFFFSEGMENT_EXIT
/** \brief Exit point of function Dem_SizeOfFFSegment() */
#define DBG_DEM_SIZEOFFFSEGMENT_EXIT(a, b)
#endif

#ifndef DBG_DEM_SIZEOFED_ENTRY
/** \brief Entry point of function Dem_SizeOfED() */
#define DBG_DEM_SIZEOFED_ENTRY(a)
#endif

#ifndef DBG_DEM_SIZEOFED_EXIT
/** \brief Exit point of function Dem_SizeOfED() */
#define DBG_DEM_SIZEOFED_EXIT(a, b)
#endif

#ifndef DBG_DEM_SIZEOFEDSEGMENT_ENTRY
/** \brief Entry point of function Dem_SizeOfEDSegment() */
#define DBG_DEM_SIZEOFEDSEGMENT_ENTRY(a)
#endif

#ifndef DBG_DEM_SIZEOFEDSEGMENT_EXIT
/** \brief Exit point of function Dem_SizeOfEDSegment() */
#define DBG_DEM_SIZEOFEDSEGMENT_EXIT(a, b)
#endif

#ifndef DBG_DEM_SIZEOFMAPINTVALCLASS_ENTRY
/** \brief Entry point of function Dem_SizeOfMapIntValClass() */
#define DBG_DEM_SIZEOFMAPINTVALCLASS_ENTRY(a)
#endif

#ifndef DBG_DEM_SIZEOFMAPINTVALCLASS_EXIT
/** \brief Exit point of function Dem_SizeOfMapIntValClass() */
#define DBG_DEM_SIZEOFMAPINTVALCLASS_EXIT(a, b)
#endif

#ifndef DBG_DEM_SIZEOFMAPINTVALSEGMENT_ENTRY
/** \brief Entry point of function Dem_SizeOfMapIntValSegment() */
#define DBG_DEM_SIZEOFMAPINTVALSEGMENT_ENTRY(a)
#endif

#ifndef DBG_DEM_SIZEOFMAPINTVALSEGMENT_EXIT
/** \brief Exit point of function Dem_SizeOfMapIntValSegment() */
#define DBG_DEM_SIZEOFMAPINTVALSEGMENT_EXIT(a, b)
#endif

#ifndef DBG_DEM_ASSEMBLEEXTENDEDDATASEG_ENTRY
/** \brief Entry point of function Dem_AssembleExtendedDataSeg() */
#define DBG_DEM_ASSEMBLEEXTENDEDDATASEG_ENTRY(a, b, c, d)
#endif

#ifndef DBG_DEM_ASSEMBLEEXTENDEDDATASEG_EXIT
/** \brief Exit point of function Dem_AssembleExtendedDataSeg() */
#define DBG_DEM_ASSEMBLEEXTENDEDDATASEG_EXIT(a, b, c, d, e)
#endif

#ifndef DBG_DEM_SIZEOFINTVALAREA_ENTRY
/** \brief Entry point of function Dem_SizeOfIntValArea() */
#define DBG_DEM_SIZEOFINTVALAREA_ENTRY(a)
#endif

#ifndef DBG_DEM_SIZEOFINTVALAREA_EXIT
/** \brief Exit point of function Dem_SizeOfIntValArea() */
#define DBG_DEM_SIZEOFINTVALAREA_EXIT(a, b)
#endif

#ifndef DBG_DEM_SHIFTDATA_ENTRY
/** \brief Entry point of function Dem_ShiftData() */
#define DBG_DEM_SHIFTDATA_ENTRY(a, b, c)
#endif

#ifndef DBG_DEM_SHIFTDATA_EXIT
/** \brief Exit point of function Dem_ShiftData() */
#define DBG_DEM_SHIFTDATA_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_CHECKFORIMMEDIATEENTRYSTORAGE_ENTRY
/** \brief Entry point of function Dem_CheckForImmediateEntryStorage() */
#define DBG_DEM_CHECKFORIMMEDIATEENTRYSTORAGE_ENTRY(a, b, c, d, e)
#endif

#ifndef DBG_DEM_CHECKFORIMMEDIATEENTRYSTORAGE_EXIT
/** \brief Exit point of function Dem_CheckForImmediateEntryStorage() */
#define DBG_DEM_CHECKFORIMMEDIATEENTRYSTORAGE_EXIT(a, b, c, d, e)
#endif

#ifndef DBG_DEM_STOREIMMEDIATELYNEXT_ENTRY
/** \brief Entry point of function Dem_StoreImmediatelyNext() */
#define DBG_DEM_STOREIMMEDIATELYNEXT_ENTRY(a, b)
#endif

#ifndef DBG_DEM_STOREIMMEDIATELYNEXT_EXIT
/** \brief Exit point of function Dem_StoreImmediatelyNext() */
#define DBG_DEM_STOREIMMEDIATELYNEXT_EXIT(a, b)
#endif

#ifndef DBG_DEM_TRIGGERNVMWRITEEVENTSTATUS_ENTRY
/** \brief Entry point of function Dem_TriggerNvmWriteEventStatus() */
#define DBG_DEM_TRIGGERNVMWRITEEVENTSTATUS_ENTRY()
#endif

#ifndef DBG_DEM_TRIGGERNVMWRITEEVENTSTATUS_EXIT
/** \brief Exit point of function Dem_TriggerNvmWriteEventStatus() */
#define DBG_DEM_TRIGGERNVMWRITEEVENTSTATUS_EXIT(a)
#endif

#ifndef DBG_DEM_TRIGGERNVMWRITEGATEENTRY_ENTRY
/** \brief Entry point of function Dem_TriggerNvmWriteGateEntry() */
#define DBG_DEM_TRIGGERNVMWRITEGATEENTRY_ENTRY()
#endif

#ifndef DBG_DEM_TRIGGERNVMWRITEGATEENTRY_EXIT
/** \brief Exit point of function Dem_TriggerNvmWriteGateEntry() */
#define DBG_DEM_TRIGGERNVMWRITEGATEENTRY_EXIT()
#endif

#ifndef DBG_DEM_CHECKFOREVENTWIRUPDATE_ENTRY
/** \brief Entry point of function Dem_CheckForEventWIRUpdate() */
#define DBG_DEM_CHECKFOREVENTWIRUPDATE_ENTRY(a, b, c)
#endif

#ifndef DBG_DEM_CHECKFOREVENTWIRUPDATE_EXIT
/** \brief Exit point of function Dem_CheckForEventWIRUpdate() */
#define DBG_DEM_CHECKFOREVENTWIRUPDATE_EXIT(a, b, c, d)
#endif

#ifndef DBG_DEM_STOREIMMEDIATELY_ENTRY
/** \brief Entry point of function Dem_StoreImmediately() */
#define DBG_DEM_STOREIMMEDIATELY_ENTRY(a, b)
#endif

#ifndef DBG_DEM_STOREIMMEDIATELY_EXIT
/** \brief Exit point of function Dem_StoreImmediately() */
#define DBG_DEM_STOREIMMEDIATELY_EXIT(a, b)
#endif

#ifndef DBG_DEM_RESETDEBOUNCETIMEBASED_ENTRY
/** \brief Entry point of function Dem_ResetDebounceTimeBased() */
#define DBG_DEM_RESETDEBOUNCETIMEBASED_ENTRY(a)
#endif

#ifndef DBG_DEM_RESETDEBOUNCETIMEBASED_EXIT
/** \brief Exit point of function Dem_ResetDebounceTimeBased() */
#define DBG_DEM_RESETDEBOUNCETIMEBASED_EXIT(a)
#endif

#ifndef DBG_DEM_RESETDEBOUNCECOUNTERBASED_ENTRY
/** \brief Entry point of function Dem_ResetDebounceCounterBased() */
#define DBG_DEM_RESETDEBOUNCECOUNTERBASED_ENTRY(a)
#endif

#ifndef DBG_DEM_RESETDEBOUNCECOUNTERBASED_EXIT
/** \brief Exit point of function Dem_ResetDebounceCounterBased() */
#define DBG_DEM_RESETDEBOUNCECOUNTERBASED_EXIT(a)
#endif

#ifndef DBG_DEM_RESETDEBOUNCEFREQUENCYBASED_ENTRY
/** \brief Entry point of function Dem_ResetDebounceFrequencyBased() */
#define DBG_DEM_RESETDEBOUNCEFREQUENCYBASED_ENTRY(a)
#endif

#ifndef DBG_DEM_RESETDEBOUNCEFREQUENCYBASED_EXIT
/** \brief Exit point of function Dem_ResetDebounceFrequencyBased() */
#define DBG_DEM_RESETDEBOUNCEFREQUENCYBASED_EXIT(a)
#endif

#ifndef DBG_DEM_RESETDEBOUNCEMONITOR_ENTRY
/** \brief Entry point of function Dem_ResetDebounceMonitor() */
#define DBG_DEM_RESETDEBOUNCEMONITOR_ENTRY(a)
#endif

#ifndef DBG_DEM_RESETDEBOUNCEMONITOR_EXIT
/** \brief Exit point of function Dem_ResetDebounceMonitor() */
#define DBG_DEM_RESETDEBOUNCEMONITOR_EXIT(a)
#endif

#ifndef DBG_DEM_DEBOUNCEEVENTCOUNTERBASED_ENTRY
/** \brief Entry point of function Dem_DebounceEventCounterBased() */
#define DBG_DEM_DEBOUNCEEVENTCOUNTERBASED_ENTRY(a, b)
#endif

#ifndef DBG_DEM_DEBOUNCEEVENTCOUNTERBASED_EXIT
/** \brief Exit point of function Dem_DebounceEventCounterBased() */
#define DBG_DEM_DEBOUNCEEVENTCOUNTERBASED_EXIT(a, b)
#endif

#ifndef DBG_DEM_DEBOUNCEEVENTFREQUENCYBASED_ENTRY
/** \brief Entry point of function Dem_DebounceEventFrequencyBased() */
#define DBG_DEM_DEBOUNCEEVENTFREQUENCYBASED_ENTRY(a, b)
#endif

#ifndef DBG_DEM_DEBOUNCEEVENTFREQUENCYBASED_EXIT
/** \brief Exit point of function Dem_DebounceEventFrequencyBased() */
#define DBG_DEM_DEBOUNCEEVENTFREQUENCYBASED_EXIT(a, b)
#endif

#ifndef DBG_DEM_DEBOUNCEEVENTTIMEBASED_ENTRY
/** \brief Entry point of function Dem_DebounceEventTimeBased() */
#define DBG_DEM_DEBOUNCEEVENTTIMEBASED_ENTRY(a, b)
#endif

#ifndef DBG_DEM_DEBOUNCEEVENTTIMEBASED_EXIT
/** \brief Exit point of function Dem_DebounceEventTimeBased() */
#define DBG_DEM_DEBOUNCEEVENTTIMEBASED_EXIT(a, b)
#endif

#ifndef DBG_DEM_GETFDCCOUNTERBASED_ENTRY
/** \brief Entry point of function Dem_GetFDCCounterBased() */
#define DBG_DEM_GETFDCCOUNTERBASED_ENTRY(a, b)
#endif

#ifndef DBG_DEM_GETFDCCOUNTERBASED_EXIT
/** \brief Exit point of function Dem_GetFDCCounterBased() */
#define DBG_DEM_GETFDCCOUNTERBASED_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_GETFDCFREQUENCYBASED_ENTRY
/** \brief Entry point of function Dem_GetFDCFrequencyBased() */
#define DBG_DEM_GETFDCFREQUENCYBASED_ENTRY(a, b)
#endif

#ifndef DBG_DEM_GETFDCFREQUENCYBASED_EXIT
/** \brief Exit point of function Dem_GetFDCFrequencyBased() */
#define DBG_DEM_GETFDCFREQUENCYBASED_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_GETFDCTIMEBASED_ENTRY
/** \brief Entry point of function Dem_GetFDCTimeBased() */
#define DBG_DEM_GETFDCTIMEBASED_ENTRY(a, b)
#endif

#ifndef DBG_DEM_GETFDCTIMEBASED_EXIT
/** \brief Exit point of function Dem_GetFDCTimeBased() */
#define DBG_DEM_GETFDCTIMEBASED_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_UPDATEFAILURECOUNTERFIRSTFAIL_ENTRY
/** \brief Entry point of function Dem_UpdateFailureCounterFirstFail() */
#define DBG_DEM_UPDATEFAILURECOUNTERFIRSTFAIL_ENTRY(a, b)
#endif

#ifndef DBG_DEM_UPDATEFAILURECOUNTERFIRSTFAIL_EXIT
/** \brief Exit point of function Dem_UpdateFailureCounterFirstFail() */
#define DBG_DEM_UPDATEFAILURECOUNTERFIRSTFAIL_EXIT(a, b)
#endif

#ifndef DBG_DEM_GETCALLBACKINDEX_ENTRY
/** \brief Entry point of function Dem_GetCallbackIndex() */
#define DBG_DEM_GETCALLBACKINDEX_ENTRY(a, b, c, d, e)
#endif

#ifndef DBG_DEM_GETCALLBACKINDEX_EXIT
/** \brief Exit point of function Dem_GetCallbackIndex() */
#define DBG_DEM_GETCALLBACKINDEX_EXIT(a, b, c, d, e)
#endif

#ifndef DBG_DEM_GETRTECALLBACKINDEX_ENTRY
/** \brief Entry point of function Dem_GetRteCallbackIndex() */
#define DBG_DEM_GETRTECALLBACKINDEX_ENTRY(a, b, c, d, e)
#endif

#ifndef DBG_DEM_GETRTECALLBACKINDEX_EXIT
/** \brief Exit point of function Dem_GetRteCallbackIndex() */
#define DBG_DEM_GETRTECALLBACKINDEX_EXIT(a, b, c, d, e)
#endif

#ifndef DBG_DEM_CLEARDTC_ENTRY
/** \brief Entry point of function Dem_ClearDTC() */
#define DBG_DEM_CLEARDTC_ENTRY(a, b, c)
#endif

#ifndef DBG_DEM_CLEARDTC_EXIT
/** \brief Exit point of function Dem_ClearDTC() */
#define DBG_DEM_CLEARDTC_EXIT(a, b, c, d)
#endif

#ifndef DBG_DEM_STARTCLEARDTC_ENTRY
/** \brief Entry point of function Dem_StartClearDTC() */
#define DBG_DEM_STARTCLEARDTC_ENTRY(a, b, c)
#endif

#ifndef DBG_DEM_STARTCLEARDTC_EXIT
/** \brief Exit point of function Dem_StartClearDTC() */
#define DBG_DEM_STARTCLEARDTC_EXIT(a, b, c, d)
#endif

#ifndef DBG_DEM_CHECKFOROLDCLEARIMMEDIATEENTRIES_ENTRY
/** \brief Entry point of function Dem_CheckForOldClearImmediateEntries() */
#define DBG_DEM_CHECKFOROLDCLEARIMMEDIATEENTRIES_ENTRY(a)
#endif

#ifndef DBG_DEM_CHECKFOROLDCLEARIMMEDIATEENTRIES_EXIT
/** \brief Exit point of function Dem_CheckForOldClearImmediateEntries() */
#define DBG_DEM_CHECKFOROLDCLEARIMMEDIATEENTRIES_EXIT(a, b)
#endif

#ifndef DBG_DEM_CLEAREVENTS_ENTRY
/** \brief Entry point of function Dem_ClearEvents() */
#define DBG_DEM_CLEAREVENTS_ENTRY(a, b, c, d, e)
#endif

#ifndef DBG_DEM_CLEAREVENTS_EXIT
/** \brief Exit point of function Dem_ClearEvents() */
#define DBG_DEM_CLEAREVENTS_EXIT(a, b, c, d, e, f)
#endif

#ifndef DBG_DEM_CLEAREVENT_ENTRY
/** \brief Entry point of function Dem_ClearEvent() */
#define DBG_DEM_CLEAREVENT_ENTRY(a, b)
#endif

#ifndef DBG_DEM_CLEAREVENT_EXIT
/** \brief Exit point of function Dem_ClearEvent() */
#define DBG_DEM_CLEAREVENT_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_DISABLEDTCSETTING_ENTRY
/** \brief Entry point of function Dem_DisableDTCSetting() */
#define DBG_DEM_DISABLEDTCSETTING_ENTRY(a, b)
#endif

#ifndef DBG_DEM_DISABLEDTCSETTING_EXIT
/** \brief Exit point of function Dem_DisableDTCSetting() */
#define DBG_DEM_DISABLEDTCSETTING_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_ENABLEDTCSETTING_ENTRY
/** \brief Entry point of function Dem_EnableDTCSetting() */
#define DBG_DEM_ENABLEDTCSETTING_ENTRY(a, b)
#endif

#ifndef DBG_DEM_ENABLEDTCSETTING_EXIT
/** \brief Exit point of function Dem_EnableDTCSetting() */
#define DBG_DEM_ENABLEDTCSETTING_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_DCMCANCELOPERATION_ENTRY
/** \brief Entry point of function Dem_DcmCancelOperation() */
#define DBG_DEM_DCMCANCELOPERATION_ENTRY()
#endif

#ifndef DBG_DEM_DCMCANCELOPERATION_EXIT
/** \brief Exit point of function Dem_DcmCancelOperation() */
#define DBG_DEM_DCMCANCELOPERATION_EXIT()
#endif

#ifndef DBG_DEM_GETIDXOFDTCGROUP_ENTRY
/** \brief Entry point of function Dem_GetIdxOfDTCGroup() */
#define DBG_DEM_GETIDXOFDTCGROUP_ENTRY(a, b)
#endif

#ifndef DBG_DEM_GETIDXOFDTCGROUP_EXIT
/** \brief Exit point of function Dem_GetIdxOfDTCGroup() */
#define DBG_DEM_GETIDXOFDTCGROUP_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_DISABLEDTCRECORDUPDATE_ENTRY
/** \brief Entry point of function Dem_DisableDTCRecordUpdate() */
#define DBG_DEM_DISABLEDTCRECORDUPDATE_ENTRY(a, b)
#endif

#ifndef DBG_DEM_DISABLEDTCRECORDUPDATE_EXIT
/** \brief Exit point of function Dem_DisableDTCRecordUpdate() */
#define DBG_DEM_DISABLEDTCRECORDUPDATE_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_ENABLEDTCRECORDUPDATE_ENTRY
/** \brief Entry point of function Dem_EnableDTCRecordUpdate() */
#define DBG_DEM_ENABLEDTCRECORDUPDATE_ENTRY()
#endif

#ifndef DBG_DEM_ENABLEDTCRECORDUPDATE_EXIT
/** \brief Exit point of function Dem_EnableDTCRecordUpdate() */
#define DBG_DEM_ENABLEDTCRECORDUPDATE_EXIT(a)
#endif

#ifndef DBG_DEM_GETFREEZEFRAMEDATABYRECORD_ENTRY
/** \brief Entry point of function Dem_GetFreezeFrameDataByRecord() */
#define DBG_DEM_GETFREEZEFRAMEDATABYRECORD_ENTRY(a, b, c, d, e)
#endif

#ifndef DBG_DEM_GETFREEZEFRAMEDATABYRECORD_EXIT
/** \brief Exit point of function Dem_GetFreezeFrameDataByRecord() */
#define DBG_DEM_GETFREEZEFRAMEDATABYRECORD_EXIT(a, b, c, d, e, f)
#endif

#ifndef DBG_DEM_GETFREEZEFRAMEDATABYDTC_ENTRY
/** \brief Entry point of function Dem_GetFreezeFrameDataByDTC() */
#define DBG_DEM_GETFREEZEFRAMEDATABYDTC_ENTRY(a, b, c, d, e)
#endif

#ifndef DBG_DEM_GETFREEZEFRAMEDATABYDTC_EXIT
/** \brief Exit point of function Dem_GetFreezeFrameDataByDTC() */
#define DBG_DEM_GETFREEZEFRAMEDATABYDTC_EXIT(a, b, c, d, e, f)
#endif

#ifndef DBG_DEM_GETSIZEOFFREEZEFRAMEBYDTC_ENTRY
/** \brief Entry point of function Dem_GetSizeOfFreezeFrameByDTC() */
#define DBG_DEM_GETSIZEOFFREEZEFRAMEBYDTC_ENTRY(a, b, c, d)
#endif

#ifndef DBG_DEM_GETSIZEOFFREEZEFRAMEBYDTC_EXIT
/** \brief Exit point of function Dem_GetSizeOfFreezeFrameByDTC() */
#define DBG_DEM_GETSIZEOFFREEZEFRAMEBYDTC_EXIT(a, b, c, d, e)
#endif

#ifndef DBG_DEM_GETEXTENDEDDATARECORDBYDTC_ENTRY
/** \brief Entry point of function Dem_GetExtendedDataRecordByDTC() */
#define DBG_DEM_GETEXTENDEDDATARECORDBYDTC_ENTRY(a, b, c, d, e)
#endif

#ifndef DBG_DEM_GETEXTENDEDDATARECORDBYDTC_EXIT
/** \brief Exit point of function Dem_GetExtendedDataRecordByDTC() */
#define DBG_DEM_GETEXTENDEDDATARECORDBYDTC_EXIT(a, b, c, d, e, f)
#endif

#ifndef DBG_DEM_GETSIZEOFEXTENDEDDATARECORDBYDTC_ENTRY
/** \brief Entry point of function Dem_GetSizeOfExtendedDataRecordByDTC() */
#define DBG_DEM_GETSIZEOFEXTENDEDDATARECORDBYDTC_ENTRY(a, b, c, d)
#endif

#ifndef DBG_DEM_GETSIZEOFEXTENDEDDATARECORDBYDTC_EXIT
/** \brief Exit point of function Dem_GetSizeOfExtendedDataRecordByDTC() */
#define DBG_DEM_GETSIZEOFEXTENDEDDATARECORDBYDTC_EXIT(a, b, c, d, e)
#endif

#ifndef DBG_DEM_COPYFFINFO_ENTRY
/** \brief Entry point of function Dem_CopyFFInfo() */
#define DBG_DEM_COPYFFINFO_ENTRY(a, b, c, d)
#endif

#ifndef DBG_DEM_COPYFFINFO_EXIT
/** \brief Exit point of function Dem_CopyFFInfo() */
#define DBG_DEM_COPYFFINFO_EXIT(a, b, c, d)
#endif

#ifndef DBG_DEM_GETONEEDRECORD_ENTRY
/** \brief Entry point of function Dem_GetOneEDRecord() */
#define DBG_DEM_GETONEEDRECORD_ENTRY(a, b, c, d, e)
#endif

#ifndef DBG_DEM_GETONEEDRECORD_EXIT
/** \brief Exit point of function Dem_GetOneEDRecord() */
#define DBG_DEM_GETONEEDRECORD_EXIT(a, b, c, d, e, f)
#endif

#ifndef DBG_DEM_SETEVENTDISABLED_ENTRY
/** \brief Entry point of function Dem_SetEventDisabled() */
#define DBG_DEM_SETEVENTDISABLED_ENTRY(a)
#endif

#ifndef DBG_DEM_SETEVENTDISABLED_EXIT
/** \brief Exit point of function Dem_SetEventDisabled() */
#define DBG_DEM_SETEVENTDISABLED_EXIT(a, b)
#endif

#ifndef DBG_DEM_REPIUMPRFAULTDETECT_ENTRY
/** \brief Entry point of function Dem_RepIUMPRFaultDetect() */
#define DBG_DEM_REPIUMPRFAULTDETECT_ENTRY(a)
#endif

#ifndef DBG_DEM_REPIUMPRFAULTDETECT_EXIT
/** \brief Exit point of function Dem_RepIUMPRFaultDetect() */
#define DBG_DEM_REPIUMPRFAULTDETECT_EXIT(a, b)
#endif

#ifndef DBG_DEM_REPIUMPRDENLOCK_ENTRY
/** \brief Entry point of function Dem_RepIUMPRDenLock() */
#define DBG_DEM_REPIUMPRDENLOCK_ENTRY(a)
#endif

#ifndef DBG_DEM_REPIUMPRDENLOCK_EXIT
/** \brief Exit point of function Dem_RepIUMPRDenLock() */
#define DBG_DEM_REPIUMPRDENLOCK_EXIT(a, b)
#endif

#ifndef DBG_DEM_REPIUMPRDENRELEASE_ENTRY
/** \brief Entry point of function Dem_RepIUMPRDenRelease() */
#define DBG_DEM_REPIUMPRDENRELEASE_ENTRY(a)
#endif

#ifndef DBG_DEM_REPIUMPRDENRELEASE_EXIT
/** \brief Exit point of function Dem_RepIUMPRDenRelease() */
#define DBG_DEM_REPIUMPRDENRELEASE_EXIT(a, b)
#endif

#ifndef DBG_DEM_GETINFOTYPEVALUE08_ENTRY
/** \brief Entry point of function Dem_GetInfoTypeValue08() */
#define DBG_DEM_GETINFOTYPEVALUE08_ENTRY(a, b)
#endif

#ifndef DBG_DEM_GETINFOTYPEVALUE08_EXIT
/** \brief Exit point of function Dem_GetInfoTypeValue08() */
#define DBG_DEM_GETINFOTYPEVALUE08_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_GETINFOTYPEVALUE0B_ENTRY
/** \brief Entry point of function Dem_GetInfoTypeValue0B() */
#define DBG_DEM_GETINFOTYPEVALUE0B_ENTRY(a, b)
#endif

#ifndef DBG_DEM_GETINFOTYPEVALUE0B_EXIT
/** \brief Exit point of function Dem_GetInfoTypeValue0B() */
#define DBG_DEM_GETINFOTYPEVALUE0B_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_DCMREADDATAOFPID01_ENTRY
/** \brief Entry point of function Dem_DcmReadDataOfPID01() */
#define DBG_DEM_DCMREADDATAOFPID01_ENTRY(a)
#endif

#ifndef DBG_DEM_DCMREADDATAOFPID01_EXIT
/** \brief Exit point of function Dem_DcmReadDataOfPID01() */
#define DBG_DEM_DCMREADDATAOFPID01_EXIT(a, b)
#endif

#ifndef DBG_DEM_DCMREADDATAOFPID21_ENTRY
/** \brief Entry point of function Dem_DcmReadDataOfPID21() */
#define DBG_DEM_DCMREADDATAOFPID21_ENTRY(a)
#endif

#ifndef DBG_DEM_DCMREADDATAOFPID21_EXIT
/** \brief Exit point of function Dem_DcmReadDataOfPID21() */
#define DBG_DEM_DCMREADDATAOFPID21_EXIT(a, b)
#endif

#ifndef DBG_DEM_DCMREADDATAOFPID30_ENTRY
/** \brief Entry point of function Dem_DcmReadDataOfPID30() */
#define DBG_DEM_DCMREADDATAOFPID30_ENTRY(a)
#endif

#ifndef DBG_DEM_DCMREADDATAOFPID30_EXIT
/** \brief Exit point of function Dem_DcmReadDataOfPID30() */
#define DBG_DEM_DCMREADDATAOFPID30_EXIT(a, b)
#endif

#ifndef DBG_DEM_DCMREADDATAOFPID31_ENTRY
/** \brief Entry point of function Dem_DcmReadDataOfPID31() */
#define DBG_DEM_DCMREADDATAOFPID31_ENTRY(a)
#endif

#ifndef DBG_DEM_DCMREADDATAOFPID31_EXIT
/** \brief Exit point of function Dem_DcmReadDataOfPID31() */
#define DBG_DEM_DCMREADDATAOFPID31_EXIT(a, b)
#endif

#ifndef DBG_DEM_DCMREADDATAOFPID41_ENTRY
/** \brief Entry point of function Dem_DcmReadDataOfPID41() */
#define DBG_DEM_DCMREADDATAOFPID41_ENTRY(a)
#endif

#ifndef DBG_DEM_DCMREADDATAOFPID41_EXIT
/** \brief Exit point of function Dem_DcmReadDataOfPID41() */
#define DBG_DEM_DCMREADDATAOFPID41_EXIT(a, b)
#endif

#ifndef DBG_DEM_DCMREADDATAOFPID4D_ENTRY
/** \brief Entry point of function Dem_DcmReadDataOfPID4D() */
#define DBG_DEM_DCMREADDATAOFPID4D_ENTRY(a)
#endif

#ifndef DBG_DEM_DCMREADDATAOFPID4D_EXIT
/** \brief Exit point of function Dem_DcmReadDataOfPID4D() */
#define DBG_DEM_DCMREADDATAOFPID4D_EXIT(a, b)
#endif

#ifndef DBG_DEM_DCMREADDATAOFPID4E_ENTRY
/** \brief Entry point of function Dem_DcmReadDataOfPID4E() */
#define DBG_DEM_DCMREADDATAOFPID4E_ENTRY(a)
#endif

#ifndef DBG_DEM_DCMREADDATAOFPID4E_EXIT
/** \brief Exit point of function Dem_DcmReadDataOfPID4E() */
#define DBG_DEM_DCMREADDATAOFPID4E_EXIT(a, b)
#endif

#ifndef DBG_DEM_DCMREADDATAOFPID1C_ENTRY
/** \brief Entry point of function Dem_DcmReadDataOfPID1C() */
#define DBG_DEM_DCMREADDATAOFPID1C_ENTRY(a)
#endif

#ifndef DBG_DEM_DCMREADDATAOFPID1C_EXIT
/** \brief Exit point of function Dem_DcmReadDataOfPID1C() */
#define DBG_DEM_DCMREADDATAOFPID1C_EXIT(a, b)
#endif

#ifndef DBG_DEM_READDATAOFOBDFREEZEFRAME_ENTRY
/** \brief Entry point of function Dem_ReadDataOfOBDFreezeFrame() */
#define DBG_DEM_READDATAOFOBDFREEZEFRAME_ENTRY(a, b, c, d)
#endif

#ifndef DBG_DEM_READDATAOFOBDFREEZEFRAME_EXIT
/** \brief Exit point of function Dem_ReadDataOfOBDFreezeFrame() */
#define DBG_DEM_READDATAOFOBDFREEZEFRAME_EXIT(a, b, c, d, e)
#endif

#ifndef DBG_DEM_GETDTCOFOBDFREEZEFRAME_ENTRY
/** \brief Entry point of function Dem_GetDTCOfOBDFreezeFrame() */
#define DBG_DEM_GETDTCOFOBDFREEZEFRAME_ENTRY(a, b)
#endif

#ifndef DBG_DEM_GETDTCOFOBDFREEZEFRAME_EXIT
/** \brief Exit point of function Dem_GetDTCOfOBDFreezeFrame() */
#define DBG_DEM_GETDTCOFOBDFREEZEFRAME_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_SETPTOSTATUS_ENTRY
/** \brief Entry point of function Dem_SetPtoStatus() */
#define DBG_DEM_SETPTOSTATUS_ENTRY(a)
#endif

#ifndef DBG_DEM_SETPTOSTATUS_EXIT
/** \brief Exit point of function Dem_SetPtoStatus() */
#define DBG_DEM_SETPTOSTATUS_EXIT(a, b)
#endif

#ifndef DBG_DEM_SETDTCFILTER_ENTRY
/** \brief Entry point of function Dem_SetDTCFilter() */
#define DBG_DEM_SETDTCFILTER_ENTRY(a, b, c, d, e, f, g)
#endif

#ifndef DBG_DEM_SETDTCFILTER_EXIT
/** \brief Exit point of function Dem_SetDTCFilter() */
#define DBG_DEM_SETDTCFILTER_EXIT(a, b, c, d, e, f, g, h)
#endif

#ifndef DBG_DEM_SETFREEZEFRAMERECORDFILTER_ENTRY
/** \brief Entry point of function Dem_SetFreezeFrameRecordFilter() */
#define DBG_DEM_SETFREEZEFRAMERECORDFILTER_ENTRY(a, b)
#endif

#ifndef DBG_DEM_SETFREEZEFRAMERECORDFILTER_EXIT
/** \brief Exit point of function Dem_SetFreezeFrameRecordFilter() */
#define DBG_DEM_SETFREEZEFRAMERECORDFILTER_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_GETSTATUSOFDTC_ENTRY
/** \brief Entry point of function Dem_GetStatusOfDTC() */
#define DBG_DEM_GETSTATUSOFDTC_ENTRY(a, b, c)
#endif

#ifndef DBG_DEM_GETSTATUSOFDTC_EXIT
/** \brief Exit point of function Dem_GetStatusOfDTC() */
#define DBG_DEM_GETSTATUSOFDTC_EXIT(a, b, c, d)
#endif

#ifndef DBG_DEM_GETDTCSTATUSAVAILABILITYMASK_ENTRY
/** \brief Entry point of function Dem_GetDTCStatusAvailabilityMask() */
#define DBG_DEM_GETDTCSTATUSAVAILABILITYMASK_ENTRY(a)
#endif

#ifndef DBG_DEM_GETDTCSTATUSAVAILABILITYMASK_EXIT
/** \brief Exit point of function Dem_GetDTCStatusAvailabilityMask() */
#define DBG_DEM_GETDTCSTATUSAVAILABILITYMASK_EXIT(a, b)
#endif

#ifndef DBG_DEM_GETNUMBEROFFILTEREDDTC_ENTRY
/** \brief Entry point of function Dem_GetNumberOfFilteredDTC() */
#define DBG_DEM_GETNUMBEROFFILTEREDDTC_ENTRY(a)
#endif

#ifndef DBG_DEM_GETNUMBEROFFILTEREDDTC_EXIT
/** \brief Exit point of function Dem_GetNumberOfFilteredDTC() */
#define DBG_DEM_GETNUMBEROFFILTEREDDTC_EXIT(a, b)
#endif

#ifndef DBG_DEM_GETNEXTFILTEREDDTC_ENTRY
/** \brief Entry point of function Dem_GetNextFilteredDTC() */
#define DBG_DEM_GETNEXTFILTEREDDTC_ENTRY(a, b)
#endif

#ifndef DBG_DEM_GETNEXTFILTEREDDTC_EXIT
/** \brief Exit point of function Dem_GetNextFilteredDTC() */
#define DBG_DEM_GETNEXTFILTEREDDTC_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_GETDTCBYOCCURRENCETIME_ENTRY
/** \brief Entry point of function Dem_GetDTCByOccurrenceTime() */
#define DBG_DEM_GETDTCBYOCCURRENCETIME_ENTRY(a, b)
#endif

#ifndef DBG_DEM_GETDTCBYOCCURRENCETIME_EXIT
/** \brief Exit point of function Dem_GetDTCByOccurrenceTime() */
#define DBG_DEM_GETDTCBYOCCURRENCETIME_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_GETNEXTFILTEREDRECORD_ENTRY
/** \brief Entry point of function Dem_GetNextFilteredRecord() */
#define DBG_DEM_GETNEXTFILTEREDRECORD_ENTRY(a, b)
#endif

#ifndef DBG_DEM_GETNEXTFILTEREDRECORD_EXIT
/** \brief Exit point of function Dem_GetNextFilteredRecord() */
#define DBG_DEM_GETNEXTFILTEREDRECORD_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_GETNEXTFILTEREDDTCANDFDC_ENTRY
/** \brief Entry point of function Dem_GetNextFilteredDTCAndFDC() */
#define DBG_DEM_GETNEXTFILTEREDDTCANDFDC_ENTRY(a, b)
#endif

#ifndef DBG_DEM_GETNEXTFILTEREDDTCANDFDC_EXIT
/** \brief Exit point of function Dem_GetNextFilteredDTCAndFDC() */
#define DBG_DEM_GETNEXTFILTEREDDTCANDFDC_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_GETNEXTFILTEREDDTCANDSEVERITY_ENTRY
/** \brief Entry point of function Dem_GetNextFilteredDTCAndSeverity() */
#define DBG_DEM_GETNEXTFILTEREDDTCANDSEVERITY_ENTRY(a, b, c, d)
#endif

#ifndef DBG_DEM_GETNEXTFILTEREDDTCANDSEVERITY_EXIT
/** \brief Exit point of function Dem_GetNextFilteredDTCAndSeverity() */
#define DBG_DEM_GETNEXTFILTEREDDTCANDSEVERITY_EXIT(a, b, c, d, e)
#endif

#ifndef DBG_DEM_GETTRANSLATIONTYPE_ENTRY
/** \brief Entry point of function Dem_GetTranslationType() */
#define DBG_DEM_GETTRANSLATIONTYPE_ENTRY()
#endif

#ifndef DBG_DEM_GETTRANSLATIONTYPE_EXIT
/** \brief Exit point of function Dem_GetTranslationType() */
#define DBG_DEM_GETTRANSLATIONTYPE_EXIT(a)
#endif

#ifndef DBG_DEM_GETSEVERITYOFDTC_ENTRY
/** \brief Entry point of function Dem_GetSeverityOfDTC() */
#define DBG_DEM_GETSEVERITYOFDTC_ENTRY(a, b)
#endif

#ifndef DBG_DEM_GETSEVERITYOFDTC_EXIT
/** \brief Exit point of function Dem_GetSeverityOfDTC() */
#define DBG_DEM_GETSEVERITYOFDTC_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_GETFUNCTIONALUNITOFDTC_ENTRY
/** \brief Entry point of function Dem_GetFunctionalUnitOfDTC() */
#define DBG_DEM_GETFUNCTIONALUNITOFDTC_ENTRY(a, b)
#endif

#ifndef DBG_DEM_GETFUNCTIONALUNITOFDTC_EXIT
/** \brief Exit point of function Dem_GetFunctionalUnitOfDTC() */
#define DBG_DEM_GETFUNCTIONALUNITOFDTC_EXIT(a, b, c)
#endif

#ifndef DBG_DEM_APPLYDTCFILTER_ENTRY
/** \brief Entry point of function Dem_ApplyDTCFilter() */
#define DBG_DEM_APPLYDTCFILTER_ENTRY(a, b, c)
#endif

#ifndef DBG_DEM_APPLYDTCFILTER_EXIT
/** \brief Exit point of function Dem_ApplyDTCFilter() */
#define DBG_DEM_APPLYDTCFILTER_EXIT(a, b, c, d)
#endif

#ifndef DBG_DEM_EVENTREPORTINGENABLED_ENTRY
/** \brief Entry point of function Dem_EventEnabled() */
#define DBG_DEM_EVENTREPORTINGENABLED_ENTRY(a) do {} while (0);
#endif

#ifndef DBG_DEM_EVENTREPORTINGENABLED_EXIT
/** \brief Exit point of function Dem_EventEnabled() */
#define DBG_DEM_EVENTREPORTINGENABLED_EXIT(a, b) do {} while (0);
#endif

#ifndef DBG_DEM_DEBOUNCEEVENT_ENTRY
/** \brief Entry point of function Dem_DebounceEvent() */
#define DBG_DEM_DEBOUNCEEVENT_ENTRY(a, b, c) do {} while (0);
#endif

#ifndef DBG_DEM_DEBOUNCEEVENT_EXIT
/** \brief Exit point of function Dem_DebounceEvent() */
#define DBG_DEM_DEBOUNCEEVENT_EXIT(a, b, c, d) do {} while (0);
#endif

#ifndef DBG_DEM_INTERNALSETSWCEVENTSTATUS_ENTRY
/** \brief Entry point of function Dem_InternalSetSwcEventStatus() */
#define DBG_DEM_INTERNALSETSWCEVENTSTATUS_ENTRY(a, b, c) do {} while (0);
#endif

#ifndef DBG_DEM_INTERNALSETSWCEVENTSTATUS_EXIT
/** \brief Exit point of function Dem_InternalSetSwcEventStatus() */
#define DBG_DEM_INTERNALSETSWCEVENTSTATUS_EXIT(a, b, c) do {} while (0);
#endif

#ifndef DBG_DEM_INTERNALSETBSWEVENTSTATUS_ENTRY
/** \brief Entry point of function Dem_InternalSetSwcEventStatus() */
#define DBG_DEM_INTERNALSETBSWEVENTSTATUS_ENTRY(a, b, c) do {} while (0);
#endif

#ifndef DBG_DEM_INTERNALSETBSWEVENTSTATUS_EXIT
/** \brief Exit point of function Dem_InternalSetSwcEventStatus() */
#define DBG_DEM_INTERNALSETBSWEVENTSTATUS_EXIT(a, b, c) do {} while (0);
#endif

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[external data]=========================================*/

#endif /* (!defined DEM_TRACE_H) */
/*==================[end of file]===========================================*/
