/**
 * \file
 *
 * \brief AUTOSAR Dcm
 *
 * This file contains the implementation of the AUTOSAR
 * module Dcm.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#if (!defined DCM_TRACE_H)
#define DCM_TRACE_H
/*==================[inclusions]============================================*/



/*==================[macros]================================================*/

#ifndef DCM_DBG_ENABLED
/** \brief Dbg module enable status for Dcm */

#define DCM_DBG_ENABLED STD_OFF

#endif

#ifndef DBG_DCM_INIT_ENTRY
/** \brief Entry point of function Dcm_Init() */
#define DBG_DCM_INIT_ENTRY(a)
#endif

#ifndef DBG_DCM_CURPROTOCOLID
/** \brief Change of Dcm_CurProtocolId */
#define DBG_DCM_CURPROTOCOLID(a,b)
#endif

#ifndef DBG_DCM_REQPROCESSING
/** \brief Change of Dcm_ReqProcessing */
#define DBG_DCM_REQPROCESSING(a,b)
#endif

#ifndef DBG_DCM_ROEPROCESSING
/** \brief Change of Dcm_ROEProcessing */
#define DBG_DCM_ROEPROCESSING(a,b)
#endif

#ifndef DBG_DCM_ROEENQUEUEEVENT
/** \brief Change of Dcm_ROEEnqueueEvent */
#define DBG_DCM_ROEENQUEUEEVENT(a,b)
#endif

#ifndef DBG_DCM_BLINITSTATUS
/** \brief Change of Dcm_BLInitStatus */
#define DBG_DCM_BLINITSTATUS(a,b)
#endif

#ifndef DBG_DCM_INIT_EXIT
/** \brief Exit point of function Dcm_Init() */
#define DBG_DCM_INIT_EXIT(a)
#endif

#ifndef DBG_DCM_GETVERSIONINFO_ENTRY
/** \brief Entry point of function Dcm_GetVersionInfo() */
#define DBG_DCM_GETVERSIONINFO_ENTRY(a)
#endif

#ifndef DBG_DCM_GETVERSIONINFO_EXIT
/** \brief Exit point of function Dcm_GetVersionInfo() */
#define DBG_DCM_GETVERSIONINFO_EXIT(a)
#endif

#ifndef DBG_DCM_GETSECURITYLEVEL_ENTRY
/** \brief Entry point of function Dcm_GetSecurityLevel() */
#define DBG_DCM_GETSECURITYLEVEL_ENTRY(a)
#endif

#ifndef DBG_DCM_GETSECURITYLEVEL_EXIT
/** \brief Exit point of function Dcm_GetSecurityLevel() */
#define DBG_DCM_GETSECURITYLEVEL_EXIT(a,b)
#endif

#ifndef DBG_DCM_GETSESCTRLTYPE_ENTRY
/** \brief Entry point of function Dcm_GetSesCtrlType() */
#define DBG_DCM_GETSESCTRLTYPE_ENTRY(a)
#endif

#ifndef DBG_DCM_GETSESCTRLTYPE_EXIT
/** \brief Exit point of function Dcm_GetSesCtrlType() */
#define DBG_DCM_GETSESCTRLTYPE_EXIT(a,b)
#endif

#ifndef DBG_DCM_GETACTIVEPROTOCOL_ENTRY
/** \brief Entry point of function Dcm_GetActiveProtocol() */
#define DBG_DCM_GETACTIVEPROTOCOL_ENTRY(a)
#endif

#ifndef DBG_DCM_GETACTIVEPROTOCOL_EXIT
/** \brief Exit point of function Dcm_GetActiveProtocol() */
#define DBG_DCM_GETACTIVEPROTOCOL_EXIT(a,b)
#endif

#ifndef DBG_DCM_RESETTODEFAULTSESSION_ENTRY
/** \brief Entry point of function Dcm_ResetToDefaultSession() */
#define DBG_DCM_RESETTODEFAULTSESSION_ENTRY()
#endif

#ifndef DBG_DCM_RESETTODEFAULTSESSION_EXIT
/** \brief Exit point of function Dcm_ResetToDefaultSession() */
#define DBG_DCM_RESETTODEFAULTSESSION_EXIT(a)
#endif

#ifndef DBG_DCM_TRIGGERONEVENT_ENTRY
/** \brief Entry point of function Dcm_TriggerOnEvent() */
#define DBG_DCM_TRIGGERONEVENT_ENTRY(a)
#endif

#ifndef DBG_DCM_TRIGGERONEVENT_EXIT
/** \brief Exit point of function Dcm_TriggerOnEvent() */
#define DBG_DCM_TRIGGERONEVENT_EXIT(a,b)
#endif

#ifndef DBG_DCM_MAINFUNCTION_ENTRY
/** \brief Entry point of function Dcm_MainFunction() */
#define DBG_DCM_MAINFUNCTION_ENTRY()
#endif

#ifndef DBG_DCM_MAINFUNCTION_EXIT
/** \brief Entry point of function Dcm_MainFunction() */
#define DBG_DCM_MAINFUNCTION_EXIT()
#endif

#ifndef DBG_DCM_INTERNAL_MAINFUNCTIONINITIALCALL_ENTRY
/** \brief Entry point of function Dcm_Internal_MainFunctionInitialCall() */
#define DBG_DCM_INTERNAL_MAINFUNCTIONINITIALCALL_ENTRY()
#endif

#ifndef DBG_DCM_INTERNAL_MAINFUNCTIONINITIALCALL_EXIT
/** \brief Entry point of function Dcm_Internal_MainFunctionInitialCall() */
#define DBG_DCM_INTERNAL_MAINFUNCTIONINITIALCALL_EXIT()
#endif

#ifndef DBG_DCM_DEMTRIGGERONDTCSTATUS_ENTRY
/** \brief Entry point of function Dcm_DemTriggerOnDTCStatus() */
#define DBG_DCM_DEMTRIGGERONDTCSTATUS_ENTRY(a,b,c)
#endif

#ifndef DBG_DCM_DEMTRIGGERONDTCSTATUS_EXIT
/** \brief Exit point of function Dcm_DemTriggerOnDTCStatus() */
#define DBG_DCM_DEMTRIGGERONDTCSTATUS_EXIT(a,b,c,d)
#endif

#ifndef DBG_DCM_HARDRESETMODEENTRY_ENTRY
/** \brief Entry point of function Dcm_HardResetModeEntry() */
#define DBG_DCM_HARDRESETMODEENTRY_ENTRY()
#endif

#ifndef DBG_DCM_HARDRESETMODEENTRY_EXIT
/** \brief Exit point of function Dcm_HardResetModeEntry() */
#define DBG_DCM_HARDRESETMODEENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_KEYONOFFRESETMODEENTRY_ENTRY
/** \brief Entry point of function Dcm_KeyOnOffResetModeEntry() */
#define DBG_DCM_KEYONOFFRESETMODEENTRY_ENTRY()
#endif

#ifndef DBG_DCM_KEYONOFFRESETMODEENTRY_EXIT
/** \brief Exit point of function Dcm_KeyOnOffResetModeEntry() */
#define DBG_DCM_KEYONOFFRESETMODEENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_SOFTRESETMODEENTRY_ENTRY
/** \brief Entry point of function Dcm_SoftResetModeEntry() */
#define DBG_DCM_SOFTRESETMODEENTRY_ENTRY()
#endif

#ifndef DBG_DCM_SOFTRESETMODEENTRY_EXIT
/** \brief Exit point of function Dcm_SoftResetModeEntry() */
#define DBG_DCM_SOFTRESETMODEENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_ENABLERAPIDPOWERSHUTDOWNRESETMODEENTRY_ENTRY
/** \brief Entry point of function Dcm_EnableRapidPowerShutdownResetModeEntry() */
#define DBG_DCM_ENABLERAPIDPOWERSHUTDOWNRESETMODEENTRY_ENTRY()
#endif

#ifndef DBG_DCM_ENABLERAPIDPOWERSHUTDOWNRESETMODEENTRY_EXIT
/** \brief Exit point of function Dcm_EnableRapidPowerShutdownResetModeEntry() */
#define DBG_DCM_ENABLERAPIDPOWERSHUTDOWNRESETMODEENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_DISABLERAPIDPOWERSHUTDOWNRESETMODEENTRY_ENTRY
/** \brief Entry point of function Dcm_DisableRapidPowerShutdownResetModeEntry() */
#define DBG_DCM_DISABLERAPIDPOWERSHUTDOWNRESETMODEENTRY_ENTRY()
#endif

#ifndef DBG_DCM_DISABLERAPIDPOWERSHUTDOWNRESETMODEENTRY_EXIT
/** \brief Exit point of function Dcm_DisableRapidPowerShutdownResetModeEntry() */
#define DBG_DCM_DISABLERAPIDPOWERSHUTDOWNRESETMODEENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_BOOTLOADERRESETMODEENTRY_ENTRY
/** \brief Entry point of function Dcm_BootloaderResetModeEntry() */
#define DBG_DCM_BOOTLOADERRESETMODEENTRY_ENTRY()
#endif

#ifndef DBG_DCM_BOOTLOADERRESETMODEENTRY_EXIT
/** \brief Exit point of function Dcm_BootloaderResetModeEntry() */
#define DBG_DCM_BOOTLOADERRESETMODEENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_SSBOOTLOADERRESETMODEENTRY_ENTRY
/** \brief Entry point of function Dcm_SsBootloaderResetModeEntry() */
#define DBG_DCM_SSBOOTLOADERRESETMODEENTRY_ENTRY()
#endif

#ifndef DBG_DCM_SSBOOTLOADERRESETMODEENTRY_EXIT
/** \brief Exit point of function Dcm_SsBootloaderResetModeEntry() */
#define DBG_DCM_SSBOOTLOADERRESETMODEENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_ENABLERXTXNORMMODEENTRY_ENTRY
/** \brief Entry point of function Dcm_EnableRxTxNormModeEntry() */
#define DBG_DCM_ENABLERXTXNORMMODEENTRY_ENTRY()
#endif

#ifndef DBG_DCM_ENABLERXTXNORMMODEENTRY_EXIT
/** \brief Exit point of function Dcm_EnableRxTxNormModeEntry() */
#define DBG_DCM_ENABLERXTXNORMMODEENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_ENABLERXDISABLETXNORMMODEENTRY_ENTRY
/** \brief Entry point of function Dcm_EnableRxDisableTxNormModeEntry() */
#define DBG_DCM_ENABLERXDISABLETXNORMMODEENTRY_ENTRY()
#endif

#ifndef DBG_DCM_ENABLERXDISABLETXNORMMODEENTRY_EXIT
/** \brief Exit point of function Dcm_EnableRxDisableTxNormModeEntry() */
#define DBG_DCM_ENABLERXDISABLETXNORMMODEENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_DISABLERXENABLETXNORMMODEENTRY_ENTRY
/** \brief Entry point of function Dcm_DisableRxEnableTxNormModeEntry() */
#define DBG_DCM_DISABLERXENABLETXNORMMODEENTRY_ENTRY()
#endif

#ifndef DBG_DCM_DISABLERXENABLETXNORMMODEENTRY_EXIT
/** \brief Exit point of function Dcm_DisableRxEnableTxNormModeEntry() */
#define DBG_DCM_DISABLERXENABLETXNORMMODEENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_DISABLERXTXNORMMODEENTRY_ENTRY
/** \brief Entry point of function Dcm_DisableRxTxNormModeEntry() */
#define DBG_DCM_DISABLERXTXNORMMODEENTRY_ENTRY()
#endif

#ifndef DBG_DCM_DISABLERXTXNORMMODEENTRY_EXIT
/** \brief Exit point of function Dcm_DisableRxTxNormModeEntry() */
#define DBG_DCM_DISABLERXTXNORMMODEENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_ENABLERXTXNMMODEENTRY_ENTRY
/** \brief Entry point of function Dcm_EnableRxTxNmModeEntry() */
#define DBG_DCM_ENABLERXTXNMMODEENTRY_ENTRY()
#endif

#ifndef DBG_DCM_ENABLERXTXNMMODEENTRY_EXIT
/** \brief Exit point of function Dcm_EnableRxTxNmModeEntry() */
#define DBG_DCM_ENABLERXTXNMMODEENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_ENABLERXDISABLETXNMMODEENTRY_ENTRY
/** \brief Entry point of function Dcm_EnableRxDisableTxNmModeEntry() */
#define DBG_DCM_ENABLERXDISABLETXNMMODEENTRY_ENTRY()
#endif

#ifndef DBG_DCM_ENABLERXDISABLETXNMMODEENTRY_EXIT
/** \brief Exit point of function Dcm_EnableRxDisableTxNmModeEntry() */
#define DBG_DCM_ENABLERXDISABLETXNMMODEENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_DISABLERXENABLETXNMMODEENTRY_ENTRY
/** \brief Entry point of function Dcm_DisableRxEnableTxNmModeEntry() */
#define DBG_DCM_DISABLERXENABLETXNMMODEENTRY_ENTRY()
#endif

#ifndef DBG_DCM_DISABLERXENABLETXNMMODEENTRY_EXIT
/** \brief Exit point of function Dcm_DisableRxEnableTxNmModeEntry() */
#define DBG_DCM_DISABLERXENABLETXNMMODEENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_DISABLERXTXNMMODEENTRY_ENTRY
/** \brief Entry point of function Dcm_DisableRxTxNmModeEntry() */
#define DBG_DCM_DISABLERXTXNMMODEENTRY_ENTRY()
#endif

#ifndef DBG_DCM_DISABLERXTXNMMODEENTRY_EXIT
/** \brief Exit point of function Dcm_DisableRxTxNmModeEntry() */
#define DBG_DCM_DISABLERXTXNMMODEENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_ENABLERXTXNORMNMMODEENTRY_ENTRY
/** \brief Entry point of function Dcm_EnableRxTxNormNmModeEntry() */
#define DBG_DCM_ENABLERXTXNORMNMMODEENTRY_ENTRY()
#endif

#ifndef DBG_DCM_ENABLERXTXNORMNMMODEENTRY_EXIT
/** \brief Exit point of function Dcm_EnableRxTxNormNmModeEntry() */
#define DBG_DCM_ENABLERXTXNORMNMMODEENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_ENABLERXDISABLETXNORMNMMODEENTRY_ENTRY
/** \brief Entry point of function Dcm_EnableRxDisableTxNormNmModeEntry() */
#define DBG_DCM_ENABLERXDISABLETXNORMNMMODEENTRY_ENTRY()
#endif

#ifndef DBG_DCM_ENABLERXDISABLETXNORMNMMODEENTRY_EXIT
/** \brief Exit point of function Dcm_EnableRxDisableTxNormNmModeEntry() */
#define DBG_DCM_ENABLERXDISABLETXNORMNMMODEENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_DISABLERXENABLETXNORMNMMODEENTRY_ENTRY
/** \brief Entry point of function Dcm_DisableRxEnableTxNormNmModeEntry() */
#define DBG_DCM_DISABLERXENABLETXNORMNMMODEENTRY_ENTRY()
#endif

#ifndef DBG_DCM_DISABLERXENABLETXNORMNMMODEENTRY_EXIT
/** \brief Exit point of function Dcm_DisableRxEnableTxNormNmModeEntry() */
#define DBG_DCM_DISABLERXENABLETXNORMNMMODEENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_DISABLERXTXNORMNMMODEENTRY_ENTRY
/** \brief Entry point of function Dcm_DisableRxTxNormNmModeEntry() */
#define DBG_DCM_DISABLERXTXNORMNMMODEENTRY_ENTRY()
#endif

#ifndef DBG_DCM_DISABLERXTXNORMNMMODEENTRY_EXIT
/** \brief Exit point of function Dcm_DisableRxTxNormNmModeEntry() */
#define DBG_DCM_DISABLERXTXNORMNMMODEENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_INTERNAL_NORMALPROCESSING_ENTRY
/** \brief Entry point of function Dcm_Internal_NormalProcessing() */
#define DBG_DCM_INTERNAL_NORMALPROCESSING_ENTRY()
#endif

#ifndef DBG_DCM_INTERNAL_NORMALPROCESSING_EXIT
/** \brief Exit point of function Dcm_Internal_NormalProcessing() */
#define DBG_DCM_INTERNAL_NORMALPROCESSING_EXIT()
#endif

#ifndef DBG_DCM_INTERNAL_PROCESSTIMERS_ENTRY
/** \brief Entry point of function Dcm_Internal_ProcessTimers() */
#define DBG_DCM_INTERNAL_PROCESSTIMERS_ENTRY()
#endif

#ifndef DBG_DCM_INTERNAL_PROCESSTIMERS_EXIT
/** \brief Exit point of function Dcm_Internal_ProcessTimers() */
#define DBG_DCM_INTERNAL_PROCESSTIMERS_EXIT()
#endif

#ifndef DBG_DCM_INTERNAL_PROCESSROEEVENTWINDOWTIME_ENTRY
/** \brief Entry point of function Dcm_Internal_ProcessRoeEventWindowTime() */
#define DBG_DCM_INTERNAL_PROCESSROEEVENTWINDOWTIME_ENTRY()
#endif

#ifndef DBG_DCM_INTERNAL_PROCESSROEEVENTWINDOWTIME_EXIT
/** \brief Exit point of function Dcm_Internal_ProcessRoeEventWindowTime() */
#define DBG_DCM_INTERNAL_PROCESSROEEVENTWINDOWTIME_EXIT()
#endif

#ifndef DBG_DCM_INTERNAL_ROEONCHANGEOFDIDPOLLING_ENTRY
/** \brief Entry point of function Dcm_Internal_ROEOnChangeOfDidPolling() */
#define DBG_DCM_INTERNAL_ROEONCHANGEOFDIDPOLLING_ENTRY()
#endif

#ifndef DBG_DCM_INTERNAL_ROEONCHANGEOFDIDPOLLING_EXIT
/** \brief Exit point of function Dcm_Internal_ROEOnChangeOfDidPolling() */
#define DBG_DCM_INTERNAL_ROEONCHANGEOFDIDPOLLING_EXIT()
#endif

#ifndef DBG_DCM_INTERNAL_ROEONCHANGEOFDIDTRIGEVENT_ENTRY
/** \brief Entry point of function Dcm_Internal_ROEOnChangeOfDidTrigEvent() */
#define DBG_DCM_INTERNAL_ROEONCHANGEOFDIDTRIGEVENT_ENTRY()
#endif

#ifndef DBG_DCM_INTERNAL_ROEONCHANGEOFDIDTRIGEVENT_EXIT
/** \brief Exit point of function Dcm_Internal_ROEOnChangeOfDidTrigEvent() */
#define DBG_DCM_INTERNAL_ROEONCHANGEOFDIDTRIGEVENT_EXIT(a)
#endif

#ifndef DBG_DCM_INTERNAL_ROEINITVARIABLES_ENTRY
/** \brief Entry point of function Dcm_Internal_ROEInitVariables() */
#define DBG_DCM_INTERNAL_ROEINITVARIABLES_ENTRY()
#endif

#ifndef DBG_DCM_INTERNAL_ROEINITVARIABLES_EXIT
/** \brief Exit point of function Dcm_Internal_ROEInitVariables() */
#define DBG_DCM_INTERNAL_ROEINITVARIABLES_EXIT()
#endif

#ifndef DBG_DCM_INTERNAL_ROEPERSISTENCEINIT_ENTRY
/** \brief Entry point of function Dcm_Internal_ROEPersistenceInit() */
#define DBG_DCM_INTERNAL_ROEPERSISTENCEINIT_ENTRY()
#endif

#ifndef DBG_DCM_INTERNAL_ROEPERSISTENCEINIT_EXIT
/** \brief Exit point of function Dcm_Internal_ROEPersistenceInit() */
#define DBG_DCM_INTERNAL_ROEPERSISTENCEINIT_EXIT()
#endif

#ifndef DBG_DCM_STARTOFRECEPTION_ENTRY
/** \brief Entry point of function Dcm_StartOfReception() */
#define DBG_DCM_STARTOFRECEPTION_ENTRY(a,b,c)
#endif

#ifndef DBG_DCM_STARTOFRECEPTION_EXIT
/** \brief Exit point of function Dcm_StartOfReception() */
#define DBG_DCM_STARTOFRECEPTION_EXIT(a,b,c,d)
#endif

#ifndef DBG_DCM_COPYRXDATA_ENTRY
/** \brief Entry point of function Dcm_CopyRxData() */
#define DBG_DCM_COPYRXDATA_ENTRY(a,b,c)
#endif

#ifndef DBG_DCM_COPYRXDATA_EXIT
/** \brief Exit point of function Dcm_CopyRxData() */
#define DBG_DCM_COPYRXDATA_EXIT(a,b,c,d)
#endif

#ifndef DBG_DCM_TPRXINDICATION_ENTRY
/** \brief Entry point of function Dcm_TpRxIndication() */
#define DBG_DCM_TPRXINDICATION_ENTRY(a,b)
#endif

#ifndef DBG_DCM_TPRXINDICATION_EXIT
/** \brief Entry point of function Dcm_TpRxIndication() */
#define DBG_DCM_TPRXINDICATION_EXIT(a,b)
#endif

#ifndef DBG_DCM_COPYTXDATA_ENTRY
/** \brief Entry point of function Dcm_CopyTxData() */
#define DBG_DCM_COPYTXDATA_ENTRY(a,b,c,d)
#endif

#ifndef DBG_DCM_COPYTXDATA_EXIT
/** \brief Exit point of function Dcm_CopyTxData() */
#define DBG_DCM_COPYTXDATA_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_DCM_CBKINTERNAL_COPYTXDATA_ENTRY
/** \brief Entry point of function Dcm_CbkInternal_CopyTxData() */
#define DBG_DCM_CBKINTERNAL_COPYTXDATA_ENTRY(a,b,c,d,e)
#endif

#ifndef DBG_DCM_CBKINTERNAL_COPYTXDATA_EXIT
/** \brief Exit point of function Dcm_CbkInternal_CopyTxData() */
#define DBG_DCM_CBKINTERNAL_COPYTXDATA_EXIT(a,b,c,d,e,f)
#endif

#ifndef DBG_DCM_TPTXCONFIRMATION_ENTRY
/** \brief Entry point of function Dcm_TpTxConfirmation() */
#define DBG_DCM_TPTXCONFIRMATION_ENTRY(a,b)
#endif

#ifndef DBG_DCM_TPTXCONFIRMATION_EXIT
/** \brief Exit point of function Dcm_TpTxConfirmation() */
#define DBG_DCM_TPTXCONFIRMATION_EXIT(a,b)
#endif

#ifndef DBG_DCM_COMM_NOCOMMODEENTERED_ENTRY
/** \brief Entry point of function Dcm_ComM_NoComModeEntered() */
#define DBG_DCM_COMM_NOCOMMODEENTERED_ENTRY(a)
#endif

#ifndef DBG_DCM_COMM_NOCOMMODEENTERED_EXIT
/** \brief Exit point of function Dcm_ComM_NoComModeEntered() */
#define DBG_DCM_COMM_NOCOMMODEENTERED_EXIT(a)
#endif

#ifndef DBG_DCM_COMM_SILENTCOMMODEENTERED_ENTRY
/** \brief Entry point of function Dcm_ComM_SilentComModeEntered() */
#define DBG_DCM_COMM_SILENTCOMMODEENTERED_ENTRY(a)
#endif

#ifndef DBG_DCM_COMM_SILENTCOMMODEENTERED_EXIT
/** \brief Exit point of function Dcm_ComM_SilentComModeEntered() */
#define DBG_DCM_COMM_SILENTCOMMODEENTERED_EXIT(a)
#endif

#ifndef DBG_DCM_COMM_FULLCOMMODEENTERED_ENTRY
/** \brief Entry point of function Dcm_ComM_FullComModeEntered() */
#define DBG_DCM_COMM_FULLCOMMODEENTERED_ENTRY(a)
#endif

#ifndef DBG_DCM_COMM_FULLCOMMODEENTERED_EXIT
/** \brief Exit point of function Dcm_ComM_FullComModeEntered() */
#define DBG_DCM_COMM_FULLCOMMODEENTERED_EXIT(a)
#endif

#ifndef DBG_DCM_DSDINTERNAL_DISPATCHSVCREQ_ENTRY
/** \brief Entry point of function Dcm_DsdInternal_DispatchSvcReq() */
#define DBG_DCM_DSDINTERNAL_DISPATCHSVCREQ_ENTRY()
#endif

#ifndef DBG_DCM_DSDINTERNAL_DISPATCHSVCREQ_EXIT
/** \brief Exit point of function Dcm_DsdInternal_DispatchSvcReq() */
#define DBG_DCM_DSDINTERNAL_DISPATCHSVCREQ_EXIT()
#endif

#ifndef DBG_DCM_EXTERNALSETNEGRESPONSE_ENTRY
/** \brief Entry point of function Dcm_ExternalSetNegResponse() */
#define DBG_DCM_EXTERNALSETNEGRESPONSE_ENTRY(a,b)
#endif

#ifndef DBG_DCM_EXTERNALSETNEGRESPONSE_EXIT
/** \brief Exit point of function Dcm_ExternalSetNegResponse() */
#define DBG_DCM_EXTERNALSETNEGRESPONSE_EXIT(a,b)
#endif

#ifndef DBG_DCM_EXTERNALPROCESSINGDONE_ENTRY
/** \brief Entry point of function Dcm_ExternalProcessingDone() */
#define DBG_DCM_EXTERNALPROCESSINGDONE_ENTRY(a)
#endif

#ifndef DBG_DCM_EXTERNALPROCESSINGDONE_EXIT
/** \brief Entry point of function Dcm_ExternalProcessingDone() */
#define DBG_DCM_EXTERNALPROCESSINGDONE_EXIT(a)
#endif

#ifndef DBG_DCM_DSDINTERNAL_STARTPAGEDPROCESSING_ENTRY
/** \brief Entry point of function Dcm_DsdInternal_StartPagedProcessing() */
#define DBG_DCM_DSDINTERNAL_STARTPAGEDPROCESSING_ENTRY(a)
#endif

#ifndef DBG_DCM_DSDINTERNAL_STARTPAGEDPROCESSING_EXIT
/** \brief Entry point of function Dcm_DsdInternal_StartPagedProcessing() */
#define DBG_DCM_DSDINTERNAL_STARTPAGEDPROCESSING_EXIT(a)
#endif

#ifndef DBG_DCM_DSDINTERNAL_PROCESSPAGE_ENTRY
/** \brief Entry point of function Dcm_DsdInternal_ProcessPage() */
#define DBG_DCM_DSDINTERNAL_PROCESSPAGE_ENTRY(a)
#endif

#ifndef DBG_DCM_DSDINTERNAL_PROCESSPAGE_EXIT
/** \brief Entry point of function Dcm_DsdInternal_ProcessPage() */
#define DBG_DCM_DSDINTERNAL_PROCESSPAGE_EXIT(a)
#endif

#ifndef DBG_DCM_DSDINTERNAL_VALIDATESVCREQ_ENTRY
/** \brief Entry point of function Dcm_DsdInternal_ValidateSvcReq() */
#define DBG_DCM_DSDINTERNAL_VALIDATESVCREQ_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSDINTERNAL_VALIDATESVCREQ_EXIT
/** \brief Exit point of function Dcm_DsdInternal_ValidateSvcReq() */
#define DBG_DCM_DSDINTERNAL_VALIDATESVCREQ_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSDINTERNAL_VALIDATESUBSVCREQ_ENTRY
/** \brief Entry point of function Dcm_DsdInternal_ValidateSubSvcReq() */
#define DBG_DCM_DSDINTERNAL_VALIDATESUBSVCREQ_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSDINTERNAL_VALIDATESUBSVCREQ_EXIT
/** \brief Exit point of function Dcm_DsdInternal_ValidateSubSvcReq() */
#define DBG_DCM_DSDINTERNAL_VALIDATESUBSVCREQ_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSDINTERNAL_ALLOCATETXBUFFER_ENTRY
/** \brief Entry point of function Dcm_DsdInternal_AllocateTxBuffer() */
#define DBG_DCM_DSDINTERNAL_ALLOCATETXBUFFER_ENTRY(a)
#endif

#ifndef DBG_DCM_DSDINTERNAL_ALLOCATETXBUFFER_EXIT
/** \brief Exit point of function Dcm_DsdInternal_AllocateTxBuffer() */
#define DBG_DCM_DSDINTERNAL_ALLOCATETXBUFFER_EXIT(a,b)
#endif

#ifndef DBG_DCM_DSDINTERNAL_MANUFACTURERNOTIFICATION_ENTRY
/** \brief Entry point of function Dcm_DsdInternal_ManufacturerNotification() */
#define DBG_DCM_DSDINTERNAL_MANUFACTURERNOTIFICATION_ENTRY(a)
#endif

#ifndef DBG_DCM_DSDINTERNAL_MANUFACTURERNOTIFICATION_EXIT
/** \brief Exit point of function Dcm_DsdInternal_ManufacturerNotification() */
#define DBG_DCM_DSDINTERNAL_MANUFACTURERNOTIFICATION_EXIT(a,b)
#endif

#ifndef DBG_DCM_DSDINTERNAL_SUPPLIERNOTIFICATION_ENTRY
/** \brief Entry point of function Dcm_DsdInternal_SupplierNotification() */
#define DBG_DCM_DSDINTERNAL_SUPPLIERNOTIFICATION_ENTRY(a)
#endif

#ifndef DBG_DCM_DSDINTERNAL_SUPPLIERNOTIFICATION_EXIT
/** \brief Exit point of function Dcm_DsdInternal_SupplierNotification() */
#define DBG_DCM_DSDINTERNAL_SUPPLIERNOTIFICATION_EXIT(a,b)
#endif

#ifndef DBG_DCM_DSLINTERNAL_RESPONSEONONEEVENT_ENTRY
/** \brief Entry point of function Dcm_DslInternal_ResponseOnOneEvent() */
#define DBG_DCM_DSLINTERNAL_RESPONSEONONEEVENT_ENTRY(a,b,c)
#endif

#ifndef DBG_DCM_DSLINTERNAL_RESPONSEONONEEVENT_EXIT
/** \brief Exit point of function Dcm_DslInternal_ResponseOnOneEvent() */
#define DBG_DCM_DSLINTERNAL_RESPONSEONONEEVENT_EXIT(a,b,c,d)
#endif

#ifndef DBG_DCM_DSPINTERNAL_SVCFUNC_ENTRY
/** \brief Entry point of function Dcm_DspInternal_SvcFunc() */
#define DBG_DCM_DSPINTERNAL_SVCFUNC_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_SVCFUNC_EXIT
/** \brief Exit point of function Dcm_DspInternal_SvcFunc() */
#define DBG_DCM_DSPINTERNAL_SVCFUNC_EXIT(a,b)
#endif

#ifndef DBG_DCM_INTERNAL_PROCESSSERVICEASYNC_ENTRY
/** \brief Entry point of function Dcm_Internal_ProcessServiceAsync() */
#define DBG_DCM_INTERNAL_PROCESSSERVICEASYNC_ENTRY()
#endif

#ifndef DBG_DCM_INTERNAL_PROCESSSERVICEASYNC_EXIT
/** \brief Exit point of function Dcm_Internal_ProcessServiceAsync() */
#define DBG_DCM_INTERNAL_PROCESSSERVICEASYNC_EXIT()
#endif

#ifndef DBG_DCM_DSPINTERNAL_DIAGNOSTICSESSIONCONTROL_SVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_DiagnosticSessionControl_SvcH() */
#define DBG_DCM_DSPINTERNAL_DIAGNOSTICSESSIONCONTROL_SVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DIAGNOSTICSESSIONCONTROL_SVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_DiagnosticSessionControl_SvcH() */
#define DBG_DCM_DSPINTERNAL_DIAGNOSTICSESSIONCONTROL_SVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DIAGNOSTICSESSIONCONTROL_SVCSTART_ENTRY
/** \brief Entry point of function Dcm_DspInternal_DiagnosticSessionControl_SvcStart() */
#define DBG_DCM_DSPINTERNAL_DIAGNOSTICSESSIONCONTROL_SVCSTART_ENTRY(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DIAGNOSTICSESSIONCONTROL_SVCSTART_EXIT
/** \brief Exit point of function Dcm_DspInternal_DiagnosticSessionControl_SvcStart() */
#define DBG_DCM_DSPINTERNAL_DIAGNOSTICSESSIONCONTROL_SVCSTART_EXIT(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DIAGNOSTICSESSIONCONTROLCOMMON_SSVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_DiagnosticSessionControlCommon_SSvcH() */
#define DBG_DCM_DSPINTERNAL_DIAGNOSTICSESSIONCONTROLCOMMON_SSVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DIAGNOSTICSESSIONCONTROLCOMMON_SSVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_DiagnosticSessionControlCommon_SSvcH() */
#define DBG_DCM_DSPINTERNAL_DIAGNOSTICSESSIONCONTROLCOMMON_SSVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DIAGNOSTICSESSIONCONTROL_SVCCONT_ENTRY
/** \brief Entry point of function Dcm_DspInternal_DiagnosticSessionControl_SvcCont() */
#define DBG_DCM_DSPINTERNAL_DIAGNOSTICSESSIONCONTROL_SVCCONT_ENTRY(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DIAGNOSTICSESSIONCONTROL_SVCCONT_EXIT
/** \brief Exit point of function Dcm_DspInternal_DiagnosticSessionControl_SvcCont() */
#define DBG_DCM_DSPINTERNAL_DIAGNOSTICSESSIONCONTROL_SVCCONT_EXIT(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_JUMPTOBL_ENTRY
/** \brief Entry point of function Dcm_DspInternal_JumpToBL() */
#define DBG_DCM_DSPINTERNAL_JUMPTOBL_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_JUMPTOBL_EXIT
/** \brief Exit point of function Dcm_DspInternal_JumpToBL() */
#define DBG_DCM_DSPINTERNAL_JUMPTOBL_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_PROCESSSETPROGCONDITIONS_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ProcessSetProgConditions() */
#define DBG_DCM_DSPINTERNAL_PROCESSSETPROGCONDITIONS_ENTRY(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_PROCESSSETPROGCONDITIONS_EXIT
/** \brief Exit point of function Dcm_DspInternal_ProcessSetProgConditions() */
#define DBG_DCM_DSPINTERNAL_PROCESSSETPROGCONDITIONS_EXIT(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_SETSESSIONSTATE_ENTRY
/** \brief Entry point of function Dcm_DspInternal_SetSessionState() */
#define DBG_DCM_DSPINTERNAL_SETSESSIONSTATE_ENTRY(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_SETSESSIONSTATE_EXIT
/** \brief Exit point of function Dcm_DspInternal_SetSessionState() */
#define DBG_DCM_DSPINTERNAL_SETSESSIONSTATE_EXIT(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ECURESET_SVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ECUReset_SvcH() */
#define DBG_DCM_DSPINTERNAL_ECURESET_SVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ECURESET_SVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_ECUReset_SvcH() */
#define DBG_DCM_DSPINTERNAL_ECURESET_SVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ECURESET_SVCSTART_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ECUReset_SvcStart() */
#define DBG_DCM_DSPINTERNAL_ECURESET_SVCSTART_ENTRY(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ECURESET_SVCSTART_EXIT
/** \brief Exit point of function Dcm_DspInternal_ECUReset_SvcStart() */
#define DBG_DCM_DSPINTERNAL_ECURESET_SVCSTART_EXIT(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ECURESET_SVCCONT_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ECUReset_SvcCont() */
#define DBG_DCM_DSPINTERNAL_ECURESET_SVCCONT_ENTRY(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ECURESET_SVCCONT_EXIT
/** \brief Exit point of function Dcm_DspInternal_ECUReset_SvcCont() */
#define DBG_DCM_DSPINTERNAL_ECURESET_SVCCONT_EXIT(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_HARDRESET_SSVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_HardReset_SSvcH() */
#define DBG_DCM_DSPINTERNAL_HARDRESET_SSVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_HARDRESET_SSVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_HardReset_SSvcH() */
#define DBG_DCM_DSPINTERNAL_HARDRESET_SSVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_KEYOFFONRESET_SSVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_KeyOffOnReset_SSvcH() */
#define DBG_DCM_DSPINTERNAL_KEYOFFONRESET_SSVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_KEYOFFONRESET_SSVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_KeyOffOnReset_SSvcH() */
#define DBG_DCM_DSPINTERNAL_KEYOFFONRESET_SSVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_SOFTRESET_SSVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_SoftReset_SSvcH() */
#define DBG_DCM_DSPINTERNAL_SOFTRESET_SSVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_SOFTRESET_SSVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_SoftReset_SSvcH() */
#define DBG_DCM_DSPINTERNAL_SOFTRESET_SSVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ENABLERAPIDPOWERSHUTDOWN_SSVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_EnableRapidPowerShutDown_SSvcH() */
#define DBG_DCM_DSPINTERNAL_ENABLERAPIDPOWERSHUTDOWN_SSVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ENABLERAPIDPOWERSHUTDOWN_SSVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_EnableRapidPowerShutDown_SSvcH() */
#define DBG_DCM_DSPINTERNAL_ENABLERAPIDPOWERSHUTDOWN_SSVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DISABLERAPIDPOWERSHUTDOWN_SSVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_DisableRapidPowerShutDown_SSvcH() */
#define DBG_DCM_DSPINTERNAL_DISABLERAPIDPOWERSHUTDOWN_SSVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DISABLERAPIDPOWERSHUTDOWN_SSVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_DisableRapidPowerShutDown_SSvcH() */
#define DBG_DCM_DSPINTERNAL_DISABLERAPIDPOWERSHUTDOWN_SSVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_SETRESETMODE_ENTRY
/** \brief Entry point of function Dcm_DspInternal_SetResetMode() */
#define DBG_DCM_DSPINTERNAL_SETRESETMODE_ENTRY(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_SETRESETMODE_EXIT
/** \brief Exit point of function Dcm_DspInternal_SetResetMode() */
#define DBG_DCM_DSPINTERNAL_SETRESETMODE_EXIT(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_CLEARDIAGNOSTICINFORMATION_SVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ClearDiagnosticInformation_SvcH() */
#define DBG_DCM_DSPINTERNAL_CLEARDIAGNOSTICINFORMATION_SVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_CLEARDIAGNOSTICINFORMATION_SVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_ClearDiagnosticInformation_SvcH() */
#define DBG_DCM_DSPINTERNAL_CLEARDIAGNOSTICINFORMATION_SVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_CLEARDTCINFO_SVCSTART_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ClearDTCInfo_SvcStart() */
#define DBG_DCM_DSPINTERNAL_CLEARDTCINFO_SVCSTART_ENTRY(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_CLEARDTCINFO_SVCSTART_EXIT
/** \brief Exit point of function Dcm_DspInternal_ClearDTCInfo_SvcStart() */
#define DBG_DCM_DSPINTERNAL_CLEARDTCINFO_SVCSTART_EXIT(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_READDTCINFORMATION_SVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ReadDTCInformation_SvcH() */
#define DBG_DCM_DSPINTERNAL_READDTCINFORMATION_SVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_READDTCINFORMATION_SVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_ReadDTCInformation_SvcH() */
#define DBG_DCM_DSPINTERNAL_READDTCINFORMATION_SVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_READDTCINFORMATION_SVCSTART_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ReadDTCInformation_SvcStart() */
#define DBG_DCM_DSPINTERNAL_READDTCINFORMATION_SVCSTART_ENTRY(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_READDTCINFORMATION_SVCSTART_EXIT
/** \brief Exit point of function Dcm_DspInternal_ReadDTCInformation_SvcStart() */
#define DBG_DCM_DSPINTERNAL_READDTCINFORMATION_SVCSTART_EXIT(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_READDTCINFORMATION_SVCCONT_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ReadDTCInformation_SvcCont() */
#define DBG_DCM_DSPINTERNAL_READDTCINFORMATION_SVCCONT_ENTRY(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_READDTCINFORMATION_SVCCONT_EXIT
/** \brief Exit point of function Dcm_DspInternal_ReadDTCInformation_SvcCont() */
#define DBG_DCM_DSPINTERNAL_READDTCINFORMATION_SVCCONT_EXIT(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REPORTNUMBEROFDTCBYSTATUSMASK_SSVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_reportNumberOfDTCByStatusMask_SSvcH() */
#define DBG_DCM_DSPINTERNAL_REPORTNUMBEROFDTCBYSTATUSMASK_SSVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REPORTNUMBEROFDTCBYSTATUSMASK_SSVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_reportNumberOfDTCByStatusMask_SSvcH() */
#define DBG_DCM_DSPINTERNAL_REPORTNUMBEROFDTCBYSTATUSMASK_SSVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REPORTDTCBYSTATUSMASK_SSVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ReportDTCByStatusMask_SSvcH() */
#define DBG_DCM_DSPINTERNAL_REPORTDTCBYSTATUSMASK_SSVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REPORTDTCBYSTATUSMASK_SSVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_ReportDTCByStatusMask_SSvcH() */
#define DBG_DCM_DSPINTERNAL_REPORTDTCBYSTATUSMASK_SSVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REPORTDTCSNAPSHOTRECORDIDENTIFICATION_SSVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ReportDtcSnapshotRecordIdentification_SSvcH() */
#define DBG_DCM_DSPINTERNAL_REPORTDTCSNAPSHOTRECORDIDENTIFICATION_SSVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REPORTDTCSNAPSHOTRECORDIDENTIFICATION_SSVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_ReportDtcSnapshotRecordIdentification_SSvcH() */
#define DBG_DCM_DSPINTERNAL_REPORTDTCSNAPSHOTRECORDIDENTIFICATION_SSVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REPORTDTCSNAPSHOTRECORDBYDTCNUMBER_SSVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ReportDtcSnapshotRecordByDtcNumber_SSvcH() */
#define DBG_DCM_DSPINTERNAL_REPORTDTCSNAPSHOTRECORDBYDTCNUMBER_SSVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REPORTDTCSNAPSHOTRECORDBYDTCNUMBER_SSVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_ReportDtcSnapshotRecordByDtcNumber_SSvcH() */
#define DBG_DCM_DSPINTERNAL_REPORTDTCSNAPSHOTRECORDBYDTCNUMBER_SSVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REPORTDTCEXTENDEDDATARECORDBYDTCNUMBER_SSVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ReportDtcExtendedDataRecordByDtcNumber_SSvcH() */
#define DBG_DCM_DSPINTERNAL_REPORTDTCEXTENDEDDATARECORDBYDTCNUMBER_SSVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REPORTDTCEXTENDEDDATARECORDBYDTCNUMBER_SSVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_ReportDtcExtendedDataRecordByDtcNumber_SSvcH() */
#define DBG_DCM_DSPINTERNAL_REPORTDTCEXTENDEDDATARECORDBYDTCNUMBER_SSVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DEMENABLEDTCRECORDUPDATE_ENTRY
/** \brief Entry point of function Dcm_DspInternal_DemEnableDTCRecordUpdate() */
#define DBG_DCM_DSPINTERNAL_DEMENABLEDTCRECORDUPDATE_ENTRY(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DEMENABLEDTCRECORDUPDATE_EXIT
/** \brief Exit point of function Dcm_DspInternal_DemEnableDTCRecordUpdate() */
#define DBG_DCM_DSPINTERNAL_DEMENABLEDTCRECORDUPDATE_EXIT(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DEMDISABLEDTCRECORDUPDATE_ENTRY
/** \brief Entry point of function Dcm_DspInternal_DemDisableDTCRecordUpdate() */
#define DBG_DCM_DSPINTERNAL_DEMDISABLEDTCRECORDUPDATE_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DEMDISABLEDTCRECORDUPDATE_EXIT
/** \brief Exit point of function Dcm_DspInternal_DemDisableDTCRecordUpdate() */
#define DBG_DCM_DSPINTERNAL_DEMDISABLEDTCRECORDUPDATE_EXIT(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REPORTSUPPORTEDDTCS_SSVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ReportSupportedDtcs_SSvcH() */
#define DBG_DCM_DSPINTERNAL_REPORTSUPPORTEDDTCS_SSVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REPORTSUPPORTEDDTCS_SSVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_ReportSupportedDtcs_SSvcH() */
#define DBG_DCM_DSPINTERNAL_REPORTSUPPORTEDDTCS_SSVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DEMGETALLEXTDATARECORDSPAGEOFF_ENTRY
/** \brief Entry point of function Dcm_DspInternal_DemGetAllExtDataRecordsPageOff() */
#define DBG_DCM_DSPINTERNAL_DEMGETALLEXTDATARECORDSPAGEOFF_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DEMGETALLEXTDATARECORDSPAGEOFF_EXIT
/** \brief Exit point of function Dcm_DspInternal_DemGetAllExtDataRecordsPageOff() */
#define DBG_DCM_DSPINTERNAL_DEMGETALLEXTDATARECORDSPAGEOFF_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_READDATABYIDENTIFIER_SVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ReadDataByIdentifier_SvcH() */
#define DBG_DCM_DSPINTERNAL_READDATABYIDENTIFIER_SVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_READDATABYIDENTIFIER_SVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_ReadDataByIdentifier_SvcH() */
#define DBG_DCM_DSPINTERNAL_READDATABYIDENTIFIER_SVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_READDATABYIDENTIFIER_SVCSTART_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ReadDataByIdentifier_SvcStart() */
#define DBG_DCM_DSPINTERNAL_READDATABYIDENTIFIER_SVCSTART_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_READDATABYIDENTIFIER_SVCSTART_EXIT
/** \brief Exit point of function Dcm_DspInternal_ReadDataByIdentifier_SvcStart() */
#define DBG_DCM_DSPINTERNAL_READDATABYIDENTIFIER_SVCSTART_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REQDIDSETSTATUS_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ReqDidSetStatus() */
#define DBG_DCM_DSPINTERNAL_REQDIDSETSTATUS_ENTRY(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REQDIDSETSTATUS_EXIT
/** \brief Exit point of function Dcm_DspInternal_ReqDidSetStatus() */
#define DBG_DCM_DSPINTERNAL_REQDIDSETSTATUS_EXIT(a,b,c,d)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REFDIDSETSTATUS_ENTRY
/** \brief Entry point of function Dcm_DspInternal_RefDidSetStatus() */
#define DBG_DCM_DSPINTERNAL_REFDIDSETSTATUS_ENTRY(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REFDIDSETSTATUS_EXIT
/** \brief Exit point of function Dcm_DspInternal_RefDidSetStatus() */
#define DBG_DCM_DSPINTERNAL_REFDIDSETSTATUS_EXIT(a,b,c,d)
#endif

#ifndef DBG_DCM_DSPINTERNAL_SECURITYACCESSCONTROL_SVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_SecurityAccessControl_SvcH() */
#define DBG_DCM_DSPINTERNAL_SECURITYACCESSCONTROL_SVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_SECURITYACCESSCONTROL_SVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_SecurityAccessControl_SvcH() */
#define DBG_DCM_DSPINTERNAL_SECURITYACCESSCONTROL_SVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_SECURITYACCESSCONTROL_SVCSTART_ENTRY
/** \brief Entry point of function Dcm_DspInternal_SecurityAccessControl_SvcStart() */
#define DBG_DCM_DSPINTERNAL_SECURITYACCESSCONTROL_SVCSTART_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_SECURITYACCESSCONTROL_SVCSTART_EXIT
/** \brief Exit point of function Dcm_DspInternal_SecurityAccessControl_SvcStart() */
#define DBG_DCM_DSPINTERNAL_SECURITYACCESSCONTROL_SVCSTART_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_SECURITYACCESSCONTROL_SVCCONT_ENTRY
/** \brief Entry point of function Dcm_DspInternal_SecurityAccessControl_SvcCont() */
#define DBG_DCM_DSPINTERNAL_SECURITYACCESSCONTROL_SVCCONT_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_SECURITYACCESSCONTROL_SVCCONT_EXIT
/** \brief Exit point of function Dcm_DspInternal_SecurityAccessControl_SvcCont() */
#define DBG_DCM_DSPINTERNAL_SECURITYACCESSCONTROL_SVCCONT_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_SECURITYACCESSREQUESTSEED_SSVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_SecurityAccessRequestSeed_SSvcH() */
#define DBG_DCM_DSPINTERNAL_SECURITYACCESSREQUESTSEED_SSVCH_ENTRY(a,b,c,d,e)
#endif

#ifndef DBG_DCM_DSPINTERNAL_SECURITYACCESSREQUESTSEED_SSVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_SecurityAccessRequestSeed_SSvcH() */
#define DBG_DCM_DSPINTERNAL_SECURITYACCESSREQUESTSEED_SSVCH_EXIT(a,b,c,d,e,f)
#endif

#ifndef DBG_DCM_DSPINTERNAL_GETSEED_OPERATION_ENTRY
/** \brief Entry point of function Dcm_DspInternal_GetSeed_Operation() */
#define DBG_DCM_DSPINTERNAL_GETSEED_OPERATION_ENTRY(a,b,c,d)
#endif

#ifndef DBG_DCM_DSPINTERNAL_GETSEED_OPERATION_EXIT
/** \brief Exit point of function Dcm_DspInternal_GetSeed_Operation() */
#define DBG_DCM_DSPINTERNAL_GETSEED_OPERATION_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_DCM_DSPINTERNAL_SECURITYACCESSSENDKEY_SSVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_SecurityAccessSendKey_SSvcH() */
#define DBG_DCM_DSPINTERNAL_SECURITYACCESSSENDKEY_SSVCH_ENTRY(a,b,c,d,e,f)
#endif

#ifndef DBG_DCM_DSPINTERNAL_SECURITYACCESSSENDKEY_SSVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_SecurityAccessSendKey_SSvcH() */
#define DBG_DCM_DSPINTERNAL_SECURITYACCESSSENDKEY_SSVCH_EXIT(a,b,c,d,e,f,g)
#endif

#ifndef DBG_DCM_DSPINTERNAL_COMMUNICATIONCONTROL_SVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_CommunicationControl_SvcH() */
#define DBG_DCM_DSPINTERNAL_COMMUNICATIONCONTROL_SVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_COMMUNICATIONCONTROL_SVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_CommunicationControl_SvcH() */
#define DBG_DCM_DSPINTERNAL_COMMUNICATIONCONTROL_SVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_COMMUNICATIONCONTROL_SVCSTART_ENTRY
/** \brief Entry point of function Dcm_DspInternal_CommunicationControl_SvcStart() */
#define DBG_DCM_DSPINTERNAL_COMMUNICATIONCONTROL_SVCSTART_ENTRY(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_COMMUNICATIONCONTROL_SVCSTART_EXIT
/** \brief Exit point of function Dcm_DspInternal_CommunicationControl_SvcStart() */
#define DBG_DCM_DSPINTERNAL_COMMUNICATIONCONTROL_SVCSTART_EXIT(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_COMMUNICATIONCONTROL_SVCCONT_ENTRY
/** \brief Entry point of function Dcm_DspInternal_CommunicationControl_SvcCont() */
#define DBG_DCM_DSPINTERNAL_COMMUNICATIONCONTROL_SVCCONT_ENTRY(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_COMMUNICATIONCONTROL_SVCCONT_EXIT
/** \brief Exit point of function Dcm_DspInternal_CommunicationControl_SvcCont() */
#define DBG_DCM_DSPINTERNAL_COMMUNICATIONCONTROL_SVCCONT_EXIT(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ENABLERXANDTX_SSVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_EnableRxAndTx_SSvcH() */
#define DBG_DCM_DSPINTERNAL_ENABLERXANDTX_SSVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ENABLERXANDTX_SSVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_EnableRxAndTx_SSvcH() */
#define DBG_DCM_DSPINTERNAL_ENABLERXANDTX_SSVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ENABLERXANDDISABLETX_SSVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_EnableRxAndDisableTx_SSvcH() */
#define DBG_DCM_DSPINTERNAL_ENABLERXANDDISABLETX_SSVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ENABLERXANDDISABLETX_SSVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_EnableRxAndDisableTx_SSvcH() */
#define DBG_DCM_DSPINTERNAL_ENABLERXANDDISABLETX_SSVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DISABLERXANDENABLETX_SSVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_DisableRxAndEnableTx_SSvcH() */
#define DBG_DCM_DSPINTERNAL_DISABLERXANDENABLETX_SSVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DISABLERXANDENABLETX_SSVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_DisableRxAndEnableTx_SSvcH() */
#define DBG_DCM_DSPINTERNAL_DISABLERXANDENABLETX_SSVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DISABLERXANDTX_SSVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_DisableRxAndTx_SSvcH() */
#define DBG_DCM_DSPINTERNAL_DISABLERXANDTX_SSVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DISABLERXANDTX_SSVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_DisableRxAndTx_SSvcH() */
#define DBG_DCM_DSPINTERNAL_DISABLERXANDTX_SSVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_SETCOMMUNICATIONMODE_ENTRY
/** \brief Entry point of function Dcm_DspInternal_SetCommunicationMode() */
#define DBG_DCM_DSPINTERNAL_SETCOMMUNICATIONMODE_ENTRY(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_SETCOMMUNICATIONMODE_EXIT
/** \brief Exit point of function Dcm_DspInternal_SetCommunicationMode() */
#define DBG_DCM_DSPINTERNAL_SETCOMMUNICATIONMODE_EXIT(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_WRITEDATABYIDENTIFIER_SVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_WriteDataByIdentifier_SvcH() */
#define DBG_DCM_DSPINTERNAL_WRITEDATABYIDENTIFIER_SVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_WRITEDATABYIDENTIFIER_SVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_WriteDataByIdentifier_SvcH() */
#define DBG_DCM_DSPINTERNAL_WRITEDATABYIDENTIFIER_SVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_WRITEDATABYIDENTIFIER_SVCSTART_ENTRY
/** \brief Entry point of function Dcm_DspInternal_WriteDataByIdentifier_SvcStart() */
#define DBG_DCM_DSPINTERNAL_WRITEDATABYIDENTIFIER_SVCSTART_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_WRITEDATABYIDENTIFIER_SVCSTART_EXIT
/** \brief Exit point of function Dcm_DspInternal_WriteDataByIdentifier_SvcStart() */
#define DBG_DCM_DSPINTERNAL_WRITEDATABYIDENTIFIER_SVCSTART_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_INPUTOUTPUTCONTROLBYIDENTIFIER_SVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_InputOutputControlByIdentifier_SvcH() */
#define DBG_DCM_DSPINTERNAL_INPUTOUTPUTCONTROLBYIDENTIFIER_SVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_INPUTOUTPUTCONTROLBYIDENTIFIER_SVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_InputOutputControlByIdentifier_SvcH() */
#define DBG_DCM_DSPINTERNAL_INPUTOUTPUTCONTROLBYIDENTIFIER_SVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_IOCONTROLBYIDENTIFIER_SVCSTART_ENTRY
/** \brief Entry point of function Dcm_DspInternal_IOControlByIdentifier_SvcStart() */
#define DBG_DCM_DSPINTERNAL_IOCONTROLBYIDENTIFIER_SVCSTART_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_IOCONTROLBYIDENTIFIER_SVCSTART_EXIT
/** \brief Exit point of function Dcm_DspInternal_IOControlByIdentifier_SvcStart() */
#define DBG_DCM_DSPINTERNAL_IOCONTROLBYIDENTIFIER_SVCSTART_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_IOCONTROLBYIDENTIFIER_SVCCONT_ENTRY
/** \brief Entry point of function Dcm_DspInternal_IOControlByIdentifier_SvcCont() */
#define DBG_DCM_DSPINTERNAL_IOCONTROLBYIDENTIFIER_SVCCONT_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_IOCONTROLBYIDENTIFIER_SVCCONT_EXIT
/** \brief Exit point of function Dcm_DspInternal_IOControlByIdentifier_SvcCont() */
#define DBG_DCM_DSPINTERNAL_IOCONTROLBYIDENTIFIER_SVCCONT_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_IORETURNCONTROLTOECU_DATA_ENTRY
/** \brief Entry point of function Dcm_DspInternal_IOReturnControlToECU_Data() */
#define DBG_DCM_DSPINTERNAL_IORETURNCONTROLTOECU_DATA_ENTRY(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_IORETURNCONTROLTOECU_DATA_EXIT
/** \brief Exit point of function Dcm_DspInternal_IOReturnControlToECU_Data() */
#define DBG_DCM_DSPINTERNAL_IORETURNCONTROLTOECU_DATA_EXIT(a,b,c,d)
#endif

#ifndef DBG_DCM_DSPINTERNAL_IORESETTODEFAULT_DATA_ENTRY
/** \brief Entry point of function Dcm_DspInternal_IOResetToDefault_Data() */
#define DBG_DCM_DSPINTERNAL_IORESETTODEFAULT_DATA_ENTRY(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_IORESETTODEFAULT_DATA_EXIT
/** \brief Exit point of function Dcm_DspInternal_IOResetToDefault_Data() */
#define DBG_DCM_DSPINTERNAL_IORESETTODEFAULT_DATA_EXIT(a,b,c,d)
#endif

#ifndef DBG_DCM_DSPINTERNAL_IOFREEZECURRENTSTATE_DATA_ENTRY
/** \brief Entry point of function Dcm_DspInternal_IOFreezeCurrentState_Data() */
#define DBG_DCM_DSPINTERNAL_IOFREEZECURRENTSTATE_DATA_ENTRY(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_IOFREEZECURRENTSTATE_DATA_EXIT
/** \brief Exit point of function Dcm_DspInternal_IOFreezeCurrentState_Data() */
#define DBG_DCM_DSPINTERNAL_IOFREEZECURRENTSTATE_DATA_EXIT(a,b,c,d)
#endif

#ifndef DBG_DCM_DSPINTERNAL_IOSHORTTERMADJUSTMENT_DATA_ENTRY
/** \brief Entry point of function Dcm_DspInternal_IOShortTermAdjustment_Data() */
#define DBG_DCM_DSPINTERNAL_IOSHORTTERMADJUSTMENT_DATA_ENTRY(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_IOSHORTTERMADJUSTMENT_DATA_EXIT
/** \brief Exit point of function Dcm_DspInternal_IOShortTermAdjustment_Data() */
#define DBG_DCM_DSPINTERNAL_IOSHORTTERMADJUSTMENT_DATA_EXIT(a,b,c,d)
#endif

#ifndef DBG_DCM_DSPINTERNAL_IOCONTROL_INTERFACERETVALCHECK_ENTRY
/** \brief Entry point of function Dcm_DspInternal_IOControl_InterfaceRetValCheck() */
#define DBG_DCM_DSPINTERNAL_IOCONTROL_INTERFACERETVALCHECK_ENTRY(a,b,c,d,e,f)
#endif

#ifndef DBG_DCM_DSPINTERNAL_IOCONTROL_INTERFACERETVALCHECK_EXIT
/** \brief Exit point of function Dcm_DspInternal_IOControl_InterfaceRetValCheck() */
#define DBG_DCM_DSPINTERNAL_IOCONTROL_INTERFACERETVALCHECK_EXIT(a,b,c,d,e,f,g)
#endif

#ifndef DBG_DCM_DSPINTERNAL_IOCONTROL_READSIGNALS_ENTRY
/** \brief Entry point of function Dcm_DspInternal_IOControl_ReadSignals() */
#define DBG_DCM_DSPINTERNAL_IOCONTROL_READSIGNALS_ENTRY(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_IOCONTROL_READSIGNALS_EXIT
/** \brief Exit point of function Dcm_DspInternal_IOControl_ReadSignals() */
#define DBG_DCM_DSPINTERNAL_IOCONTROL_READSIGNALS_EXIT(a,b,c,d)
#endif

#ifndef DBG_DCM_DSPINTERNAL_IOCONTROL_CHECKCONTROLMASK_ENTRY
/** \brief Entry point of function Dcm_DspInternal_IOControl_CheckControlMask() */
#define DBG_DCM_DSPINTERNAL_IOCONTROL_CHECKCONTROLMASK_ENTRY(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_IOCONTROL_CHECKCONTROLMASK_EXIT
/** \brief Exit point of function Dcm_DspInternal_IOControl_CheckControlMask() */
#define DBG_DCM_DSPINTERNAL_IOCONTROL_CHECKCONTROLMASK_EXIT(a,b,c,d)
#endif

#ifndef DBG_DCM_DSPINTERNAL_SIGNALDATACOPYING_ENTRY
/** \brief Entry point of function Dcm_DspInternal_SignalDataCopying() */
#define DBG_DCM_DSPINTERNAL_SIGNALDATACOPYING_ENTRY(a,b,c,d,e)
#endif

#ifndef DBG_DCM_DSPINTERNAL_SIGNALDATACOPYING_EXIT
/** \brief Exit point of function Dcm_DspInternal_SignalDataCopying() */
#define DBG_DCM_DSPINTERNAL_SIGNALDATACOPYING_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_DCM_DSPINTERNAL_IOCONTROLDIDREQUESTLENGTHCHK_ENTRY
/** \brief Entry point of function Dcm_DspInternal_IOControlDidRequestLengthChk() */
#define DBG_DCM_DSPINTERNAL_IOCONTROLDIDREQUESTLENGTHCHK_ENTRY(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_IOCONTROLDIDREQUESTLENGTHCHK_EXIT
/** \brief Exit point of function Dcm_DspInternal_IOControlDidRequestLengthChk() */
#define DBG_DCM_DSPINTERNAL_IOCONTROLDIDREQUESTLENGTHCHK_EXIT(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_RETURNCONTROLTOECUFORALLSIGNALS_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ReturnControlToEcuforallSignals() */
#define DBG_DCM_DSPINTERNAL_RETURNCONTROLTOECUFORALLSIGNALS_ENTRY()
#endif

#ifndef DBG_DCM_DSPINTERNAL_RETURNCONTROLTOECUFORALLSIGNALS_EXIT
/** \brief Exit point of function Dcm_DspInternal_ReturnControlToEcuforallSignals() */
#define DBG_DCM_DSPINTERNAL_RETURNCONTROLTOECUFORALLSIGNALS_EXIT()
#endif

#ifndef DBG_DCM_DSPINTERNAL_ROUTINECONTROL_SVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_RoutineControl_SvcH() */
#define DBG_DCM_DSPINTERNAL_ROUTINECONTROL_SVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ROUTINECONTROL_SVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_RoutineControl_SvcH() */
#define DBG_DCM_DSPINTERNAL_ROUTINECONTROL_SVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ROUTINECONTROL_SVCSTART_ENTRY
/** \brief Entry point of function Dcm_DspInternal_RoutineControl_SvcStart() */
#define DBG_DCM_DSPINTERNAL_ROUTINECONTROL_SVCSTART_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ROUTINECONTROL_SVCSTART_EXIT
/** \brief Exit point of function Dcm_DspInternal_RoutineControl_SvcStart() */
#define DBG_DCM_DSPINTERNAL_ROUTINECONTROL_SVCSTART_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ROUTINECONTROL_SVCCONT_ENTRY
/** \brief Entry point of function Dcm_DspInternal_RoutineControl_SvcCont() */
#define DBG_DCM_DSPINTERNAL_ROUTINECONTROL_SVCCONT_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ROUTINECONTROL_SVCCONT_EXIT
/** \brief Exit point of function Dcm_DspInternal_RoutineControl_SvcCont() */
#define DBG_DCM_DSPINTERNAL_ROUTINECONTROL_SVCCONT_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_TESTERPRESENT_SVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_TesterPresent_SvcH() */
#define DBG_DCM_DSPINTERNAL_TESTERPRESENT_SVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_TESTERPRESENT_SVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_TesterPresent_SvcH() */
#define DBG_DCM_DSPINTERNAL_TESTERPRESENT_SVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_CONTROLDTCSETTING_SVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ControlDTCSetting_SvcH() */
#define DBG_DCM_DSPINTERNAL_CONTROLDTCSETTING_SVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_CONTROLDTCSETTING_SVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_ControlDTCSetting_SvcH() */
#define DBG_DCM_DSPINTERNAL_CONTROLDTCSETTING_SVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_CONTROLDTCSETTING_SVCSTART_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ControlDTCSetting_SvcStart() */
#define DBG_DCM_DSPINTERNAL_CONTROLDTCSETTING_SVCSTART_ENTRY(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_CONTROLDTCSETTING_SVCSTART_EXIT
/** \brief Exit point of function Dcm_DspInternal_ControlDTCSetting_SvcStart() */
#define DBG_DCM_DSPINTERNAL_CONTROLDTCSETTING_SVCSTART_EXIT(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DTCSETTINGTYPEON_SSVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_DTCSettingTypeOn_SSvcH() */
#define DBG_DCM_DSPINTERNAL_DTCSETTINGTYPEON_SSVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DTCSETTINGTYPEON_SSVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_DTCSettingTypeOn_SSvcH() */
#define DBG_DCM_DSPINTERNAL_DTCSETTINGTYPEON_SSVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DTCSETTINGTYPEOFF_SSVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_DTCSettingTypeOff_SSvcH() */
#define DBG_DCM_DSPINTERNAL_DTCSETTINGTYPEOFF_SSVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DTCSETTINGTYPEOFF_SSVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_DTCSettingTypeOff_SSvcH() */
#define DBG_DCM_DSPINTERNAL_DTCSETTINGTYPEOFF_SSVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_RESPONSEONEVENT_SVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ResponseOnEvent_SvcH() */
#define DBG_DCM_DSPINTERNAL_RESPONSEONEVENT_SVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_RESPONSEONEVENT_SVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_ResponseOnEvent_SvcH() */
#define DBG_DCM_DSPINTERNAL_RESPONSEONEVENT_SVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_RESPONSEONEVENT_SVCSTART_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ResponseOnEvent_SvcStart() */
#define DBG_DCM_DSPINTERNAL_RESPONSEONEVENT_SVCSTART_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_RESPONSEONEVENT_SVCSTART_EXIT
/** \brief Exit point of function Dcm_DspInternal_ResponseOnEvent_SvcStart() */
#define DBG_DCM_DSPINTERNAL_RESPONSEONEVENT_SVCSTART_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_RESPONSEONEVENT_SVCCONT_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ResponseOnEvent_SvcCont() */
#define DBG_DCM_DSPINTERNAL_RESPONSEONEVENT_SVCCONT_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_RESPONSEONEVENT_SVCCONT_EXIT
/** \brief Exit point of function Dcm_DspInternal_ResponseOnEvent_SvcCont() */
#define DBG_DCM_DSPINTERNAL_RESPONSEONEVENT_SVCCONT_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ONDTCSTATUSCHANGE_SSVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_OnDTCStatusChange_SSvcH() */
#define DBG_DCM_DSPINTERNAL_ONDTCSTATUSCHANGE_SSVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ONDTCSTATUSCHANGE_SSVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_OnDTCStatusChange_SSvcH() */
#define DBG_DCM_DSPINTERNAL_ONDTCSTATUSCHANGE_SSVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ONCHANGEOFDATAIDENTIFIER_SSVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_OnChangeOfDataIdentifier_SSvcH() */
#define DBG_DCM_DSPINTERNAL_ONCHANGEOFDATAIDENTIFIER_SSVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ONCHANGEOFDATAIDENTIFIER_SSVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_OnChangeOfDataIdentifier_SSvcH() */
#define DBG_DCM_DSPINTERNAL_ONCHANGEOFDATAIDENTIFIER_SSVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_INTERNAL_ROEONCHANGEOFDIDEXTERNALEVENTACTIVATE_ENTRY
/** \brief Entry point of function Dcm_DspInternal_RoeOnChangeOfDidExternalEventActivate() */
#define DBG_DCM_INTERNAL_ROEONCHANGEOFDIDEXTERNALEVENTACTIVATE_ENTRY()
#endif

#ifndef DBG_DCM_INTERNAL_ROEONCHANGEOFDIDEXTERNALEVENTACTIVATE_EXIT
/** \brief Exit point of function Dcm_DspInternal_RoeOnChangeOfDidExternalEventActivate() */
#define DBG_DCM_INTERNAL_ROEONCHANGEOFDIDEXTERNALEVENTACTIVATE_EXIT()
#endif

#ifndef DBG_DCM_DSPINTERNAL_STARTROE_SSVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_StartROE_SSvcH() */
#define DBG_DCM_DSPINTERNAL_STARTROE_SSVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_STARTROE_SSVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_StartROE_SSvcH() */
#define DBG_DCM_DSPINTERNAL_STARTROE_SSVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_STOPROE_SSVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_StopROE_SSvcH() */
#define DBG_DCM_DSPINTERNAL_STOPROE_SSVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_STOPROE_SSVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_StopROE_SSvcH() */
#define DBG_DCM_DSPINTERNAL_STOPROE_SSVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_CLEARROE_SSVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ClearROE_SSvcH() */
#define DBG_DCM_DSPINTERNAL_CLEARROE_SSVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_CLEARROE_SSVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_ClearROE_SSvcH() */
#define DBG_DCM_DSPINTERNAL_CLEARROE_SSVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REPORTACTIVATEDEVENTS_SSVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ReportActivatedEvents_SSvcH() */
#define DBG_DCM_DSPINTERNAL_REPORTACTIVATEDEVENTS_SSVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REPORTACTIVATEDEVENTS_SSVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_ReportActivatedEvents_SSvcH() */
#define DBG_DCM_DSPINTERNAL_REPORTACTIVATEDEVENTS_SSVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ONDTCSTATUSCHANGE_SVCSTART_ENTRY
/** \brief Entry point of function Dcm_DspInternal_OnDTCStatusChange_SvcStart() */
#define DBG_DCM_DSPINTERNAL_ONDTCSTATUSCHANGE_SVCSTART_ENTRY(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ONDTCSTATUSCHANGE_SVCSTART_EXIT
/** \brief Exit point of function Dcm_DspInternal_OnDTCStatusChange_SvcStart() */
#define DBG_DCM_DSPINTERNAL_ONDTCSTATUSCHANGE_SVCSTART_EXIT(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ONCHANGEOFDATAIDENTIFIER_SVCSTART_ENTRY
/** \brief Entry point of function Dcm_DspInternal_OnChangeOfDataIdentifier_SvcStart() */
#define DBG_DCM_DSPINTERNAL_ONCHANGEOFDATAIDENTIFIER_SVCSTART_ENTRY(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ONCHANGEOFDATAIDENTIFIER_SVCSTART_EXIT
/** \brief Exit point of function Dcm_DspInternal_OnChangeOfDataIdentifier_SvcStart() */
#define DBG_DCM_DSPINTERNAL_ONCHANGEOFDATAIDENTIFIER_SVCSTART_EXIT(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_STARTROE_SVCSTART_ENTRY
/** \brief Entry point of function Dcm_DspInternal_StartROE_SvcStart() */
#define DBG_DCM_DSPINTERNAL_STARTROE_SVCSTART_ENTRY(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_STARTROE_SVCSTART_EXIT
/** \brief Exit point of function Dcm_DspInternal_StartROE_SvcStart() */
#define DBG_DCM_DSPINTERNAL_STARTROE_SVCSTART_EXIT(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_CLEARROE_SVCSTART_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ClearROE_SvcStart() */
#define DBG_DCM_DSPINTERNAL_CLEARROE_SVCSTART_ENTRY(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_CLEARROE_SVCSTART_EXIT
/** \brief Exit point of function Dcm_DspInternal_ClearROE_SvcStart() */
#define DBG_DCM_DSPINTERNAL_CLEARROE_SVCSTART_EXIT(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_STOPROE_SVCSTART_ENTRY
/** \brief Entry point of function Dcm_DspInternal_StopROE_SvcStart() */
#define DBG_DCM_DSPINTERNAL_STOPROE_SVCSTART_ENTRY(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_STOPROE_SVCSTART_EXIT
/** \brief Exit point of function Dcm_DspInternal_StopROE_SvcStart() */
#define DBG_DCM_DSPINTERNAL_STOPROE_SVCSTART_EXIT(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_UPDATEPAGE_ENTRY
/** \brief Entry point of function Dcm_DspInternal_UpdatePage() */
#define DBG_DCM_DSPINTERNAL_UPDATEPAGE_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_UPDATEPAGE_EXIT
/** \brief Entry point of function Dcm_DspInternal_UpdatePage() */
#define DBG_DCM_DSPINTERNAL_UPDATEPAGE_EXIT(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_CANCELPAGEDBUFFERPROCESSING_ENTRY
/** \brief Entry point of function Dcm_DspInternal_CancelPagedBufferProcessing() */
#define DBG_DCM_DSPINTERNAL_CANCELPAGEDBUFFERPROCESSING_ENTRY()
#endif

#ifndef DBG_DCM_DSPINTERNAL_CANCELPAGEDBUFFERPROCESSING_EXIT
/** \brief Exit point of function Dcm_DspInternal_CancelPagedBufferProcessing() */
#define DBG_DCM_DSPINTERNAL_CANCELPAGEDBUFFERPROCESSING_EXIT()
#endif

#ifndef DBG_DCM_DSPINTERNAL_CANCELPROCESSING_ENTRY
/** \brief Entry point of function Dcm_DspInternal_CancelProcessing() */
#define DBG_DCM_DSPINTERNAL_CANCELPROCESSING_ENTRY()
#endif

#ifndef DBG_DCM_DSPINTERNAL_CANCELPROCESSING_EXIT
/** \brief Exit point of function Dcm_DspInternal_CancelProcessing() */
#define DBG_DCM_DSPINTERNAL_CANCELPROCESSING_EXIT()
#endif

#ifndef DBG_DCM_DSPINTERNAL_DCMCONFIRMATION_ENTRY
/** \brief Entry point of function Dcm_DspInternal_DcmConfirmation() */
#define DBG_DCM_DSPINTERNAL_DCMCONFIRMATION_ENTRY(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DCMCONFIRMATION_EXIT
/** \brief Entry point of function Dcm_DspInternal_DcmConfirmation() */
#define DBG_DCM_DSPINTERNAL_DCMCONFIRMATION_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DEMGETSNAPSHOTRECORD_ENTRY
/** \brief Entry point of function Dcm_DspInternal_DemGetSnapShotRecord() */
#define DBG_DCM_DSPINTERNAL_DEMGETSNAPSHOTRECORD_ENTRY(a,b,c,d,e)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DEMGETSNAPSHOTRECORD_EXIT
/** \brief Exit point of function Dcm_DspInternal_DemGetSnapShotRecord() */
#define DBG_DCM_DSPINTERNAL_DEMGETSNAPSHOTRECORD_EXIT(a,b,c,d,e,f)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DEMGETEXTDATARECORD_ENTRY
/** \brief Entry point of function Dcm_DspInternal_DemGetExtDataRecord() */
#define DBG_DCM_DSPINTERNAL_DEMGETEXTDATARECORD_ENTRY(a,b,c,d,e)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DEMGETEXTDATARECORD_EXIT
/** \brief Exit point of function Dcm_DspInternal_DemGetExtDataRecord() */
#define DBG_DCM_DSPINTERNAL_DEMGETEXTDATARECORD_EXIT(a,b,c,d,e,f)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DEMREPORTSTATUSBYTE_ENTRY
/** \brief Entry point of function Dcm_DspInternal_DemReportStatusByte() */
#define DBG_DCM_DSPINTERNAL_DEMREPORTSTATUSBYTE_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DEMREPORTSTATUSBYTE_EXIT
/** \brief Exit point of function Dcm_DspInternal_DemReportStatusByte() */
#define DBG_DCM_DSPINTERNAL_DEMREPORTSTATUSBYTE_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ENABLEPROCESSPAGE_ENTRY
/** \brief Entry point of function Dcm_DspInternal_EnableProcessPage() */
#define DBG_DCM_DSPINTERNAL_ENABLEPROCESSPAGE_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ENABLEPROCESSPAGE_EXIT
/** \brief Exit point of function Dcm_DspInternal_EnableProcessPage() */
#define DBG_DCM_DSPINTERNAL_ENABLEPROCESSPAGE_EXIT(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_UPDATERESPONSEBUFFER_ENTRY
/** \brief Entry point of function Dcm_DspInternal_UpdateResponseBuffer() */
#define DBG_DCM_DSPINTERNAL_UPDATERESPONSEBUFFER_ENTRY(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_UPDATERESPONSEBUFFER_EXIT
/** \brief Exit point of function Dcm_DspInternal_UpdateResponseBuffer() */
#define DBG_DCM_DSPINTERNAL_UPDATERESPONSEBUFFER_EXIT(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_PROCESSPAGEDTCBYSTATUSMASK_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ProcessPageDTCByStatusMask() */
#define DBG_DCM_DSPINTERNAL_PROCESSPAGEDTCBYSTATUSMASK_ENTRY(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_PROCESSPAGEDTCBYSTATUSMASK_EXIT
/** \brief Exit point of function Dcm_DspInternal_ProcessPageDTCByStatusMask() */
#define DBG_DCM_DSPINTERNAL_PROCESSPAGEDTCBYSTATUSMASK_EXIT(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_PROCESSPAGEDTCSNAPSHOTBYIDENTIFICATION_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ProcessPageDTCSnapshotByIdentification() */
#define DBG_DCM_DSPINTERNAL_PROCESSPAGEDTCSNAPSHOTBYIDENTIFICATION_ENTRY(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_PROCESSPAGEDTCSNAPSHOTBYIDENTIFICATION_EXIT
/** \brief Exit point of function Dcm_DspInternal_ProcessPageDTCSnapshotByIdentification() */
#define DBG_DCM_DSPINTERNAL_PROCESSPAGEDTCSNAPSHOTBYIDENTIFICATION_EXIT(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_PROCESSPAGEDTCSNAPSHOTRECORD_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ProcessPageDtcSnapshotRecord() */
#define DBG_DCM_DSPINTERNAL_PROCESSPAGEDTCSNAPSHOTRECORD_ENTRY(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_PROCESSPAGEDTCSNAPSHOTRECORD_EXIT
/** \brief Exit point of function Dcm_DspInternal_ProcessPageDtcSnapshotRecord() */
#define DBG_DCM_DSPINTERNAL_PROCESSPAGEDTCSNAPSHOTRECORD_EXIT(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_PROCESSPAGEDTCEXTDATARECORD_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ProcessPageDtcExtDataRecord() */
#define DBG_DCM_DSPINTERNAL_PROCESSPAGEDTCEXTDATARECORD_ENTRY(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_PROCESSPAGEDTCEXTDATARECORD_EXIT
/** \brief Exit point of function Dcm_DspInternal_ProcessPageDtcExtDataRecord() */
#define DBG_DCM_DSPINTERNAL_PROCESSPAGEDTCEXTDATARECORD_EXIT(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DEMGETSIZEOFFREEZEFRAME_ENTRY
/** \brief Entry point of function Dcm_DspInternal_DemGetSizeOfFreezeFrame() */
#define DBG_DCM_DSPINTERNAL_DEMGETSIZEOFFREEZEFRAME_ENTRY(a,b,c,d)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DEMGETSIZEOFFREEZEFRAME_EXIT
/** \brief Exit point of function Dcm_DspInternal_DemGetSizeOfFreezeFrame() */
#define DBG_DCM_DSPINTERNAL_DEMGETSIZEOFFREEZEFRAME_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DEMGETSIZEOFEXTDATARECORD_ENTRY
/** \brief Entry point of function Dcm_DspInternal_DemGetSizeOfExtDataRecord() */
#define DBG_DCM_DSPINTERNAL_DEMGETSIZEOFEXTDATARECORD_ENTRY(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DEMGETSIZEOFEXTDATARECORD_EXIT
/** \brief Exit point of function Dcm_DspInternal_DemGetSizeOfExtDataRecord() */
#define DBG_DCM_DSPINTERNAL_DEMGETSIZEOFEXTDATARECORD_EXIT(a,b,c,d)
#endif

#ifndef DBG_DCM_DSPINTERNAL_READDID_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ReadDid() */
#define DBG_DCM_DSPINTERNAL_READDID_ENTRY(a,b,c,d)
#endif

#ifndef DBG_DCM_DSPINTERNAL_READDID_EXIT
/** \brief Exit point of function Dcm_DspInternal_ReadDid() */
#define DBG_DCM_DSPINTERNAL_READDID_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_DCM_DSPINTERNAL_READDID_SIGNAL_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ReadDid_Signal() */
#define DBG_DCM_DSPINTERNAL_READDID_SIGNAL_ENTRY(a,b,c,d,e,f)
#endif

#ifndef DBG_DCM_DSPINTERNAL_READDID_SIGNAL_EXIT
/** \brief Exit point of function Dcm_DspInternal_ReadDid_Signal() */
#define DBG_DCM_DSPINTERNAL_READDID_SIGNAL_EXIT(a,b,c,d,e,f,g)
#endif

#ifndef DBG_DCM_DSPINTERNAL_READDID_CONDITIONCHECKASYNC_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ReadDid_ConditionCheckAsync() */
#define DBG_DCM_DSPINTERNAL_READDID_CONDITIONCHECKASYNC_ENTRY(a,b,c,d)
#endif

#ifndef DBG_DCM_DSPINTERNAL_READDID_CONDITIONCHECKASYNC_EXIT
/** \brief Exit point of function Dcm_DspInternal_ReadDid_ConditionCheckAsync() */
#define DBG_DCM_DSPINTERNAL_READDID_CONDITIONCHECKASYNC_EXIT(a,b,c,d)
#endif

#ifndef DBG_DCM_DSPINTERNAL_READDID_CONDITIONCHECKSYNC_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ReadDid_ConditionCheckSync() */
#define DBG_DCM_DSPINTERNAL_READDID_CONDITIONCHECKSYNC_ENTRY(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_READDID_CONDITIONCHECKSYNC_EXIT
/** \brief Exit point of function Dcm_DspInternal_ReadDid_ConditionCheckSync() */
#define DBG_DCM_DSPINTERNAL_READDID_CONDITIONCHECKSYNC_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_READDIDSIGNALDATALENGTH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ReadDidSignalDataLength() */
#define DBG_DCM_DSPINTERNAL_READDIDSIGNALDATALENGTH_ENTRY(a,b,c,d)
#endif

#ifndef DBG_DCM_DSPINTERNAL_READDIDSIGNALDATALENGTH_EXIT
/** \brief Exit point of function Dcm_DspInternal_ReadDidSignalDataLength() */
#define DBG_DCM_DSPINTERNAL_READDIDSIGNALDATALENGTH_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_DCM_DSPINTERNAL_SIGNALLENGTHORDATAPOSITION_ENTRY
/** \brief Entry point of function Dcm_DspInternal_SignalLengthOrDataPosition() */
#define DBG_DCM_DSPINTERNAL_SIGNALLENGTHORDATAPOSITION_ENTRY(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_SIGNALLENGTHORDATAPOSITION_EXIT
/** \brief Exit point of function Dcm_DspInternal_SignalLengthOrDataPosition() */
#define DBG_DCM_DSPINTERNAL_SIGNALLENGTHORDATAPOSITION_EXIT(a,b,c,d)
#endif

#ifndef DBG_DCM_DSPINTERNAL_READDIDSIGNALDATA_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ReadDidSignalData() */
#define DBG_DCM_DSPINTERNAL_READDIDSIGNALDATA_ENTRY(a,b,c,d,e)
#endif

#ifndef DBG_DCM_DSPINTERNAL_READDIDSIGNALDATA_EXIT
/** \brief Exit point of function Dcm_DspInternal_ReadDidSignalData() */
#define DBG_DCM_DSPINTERNAL_READDIDSIGNALDATA_EXIT(a,b,c,d,e,f)
#endif

#ifndef DBG_DCM_DSPINTERNAL_READNVMDATA_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ReadNvmData() */
#define DBG_DCM_DSPINTERNAL_READNVMDATA_ENTRY(a,b,c,d)
#endif

#ifndef DBG_DCM_DSPINTERNAL_READNVMDATA_EXIT
/** \brief Exit point of function Dcm_DspInternal_ReadNvmData() */
#define DBG_DCM_DSPINTERNAL_READNVMDATA_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DIDCONDITIONCHECKS_ENTRY
/** \brief Entry point of function Dcm_DspInternal_DidConditionChecks() */
#define DBG_DCM_DSPINTERNAL_DIDCONDITIONCHECKS_ENTRY(a,b,c,d,e)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DIDCONDITIONCHECKS_EXIT
/** \brief Exit point of function Dcm_DspInternal_DidConditionChecks() */
#define DBG_DCM_DSPINTERNAL_DIDCONDITIONCHECKS_EXIT(a,b,c,d,e,f)
#endif

#ifndef DBG_DCM_DSPINTERNAL_VALIDATEDIDINDEX_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ValidateDidIndex() */
#define DBG_DCM_DSPINTERNAL_VALIDATEDIDINDEX_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_VALIDATEDIDINDEX_EXIT
/** \brief Exit point of function Dcm_DspInternal_ValidateDidIndex() */
#define DBG_DCM_DSPINTERNAL_VALIDATEDIDINDEX_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DIDCONDITIONCHECKSSESLEVEL_ENTRY
/** \brief Entry point of function Dcm_DspInternal_DidConditionChecksSesLevel() */
#define DBG_DCM_DSPINTERNAL_DIDCONDITIONCHECKSSESLEVEL_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DIDCONDITIONCHECKSSESLEVEL_EXIT
/** \brief Exit point of function Dcm_DspInternal_DidConditionChecksSesLevel() */
#define DBG_DCM_DSPINTERNAL_DIDCONDITIONCHECKSSESLEVEL_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DIDCONDITIONCHECKSSECLEVEL_ENTRY
/** \brief Entry point of function Dcm_DspInternal_DidConditionChecksSecLevel() */
#define DBG_DCM_DSPINTERNAL_DIDCONDITIONCHECKSSECLEVEL_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DIDCONDITIONCHECKSSECLEVEL_EXIT
/** \brief Exit point of function Dcm_DspInternal_DidConditionChecksSecLevel() */
#define DBG_DCM_DSPINTERNAL_DIDCONDITIONCHECKSSECLEVEL_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_COPYSIGNALDATA_ENTRY
/** \brief Entry point of function Dcm_DspInternal_CopySignalData() */
#define DBG_DCM_DSPINTERNAL_COPYSIGNALDATA_ENTRY(a,b,c,d,e)
#endif

#ifndef DBG_DCM_DSPINTERNAL_COPYSIGNALDATA_EXIT
/** \brief Exit point of function Dcm_DspInternal_CopySignalData() */
#define DBG_DCM_DSPINTERNAL_COPYSIGNALDATA_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_DCM_DSPINTERNAL_WRITEDIDREQUESTLENGTHCHK_ENTRY
/** \brief Entry point of function Dcm_DspInternal_WriteDidRequestLengthChk() */
#define DBG_DCM_DSPINTERNAL_WRITEDIDREQUESTLENGTHCHK_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_WRITEDIDREQUESTLENGTHCHK_EXIT
/** \brief Exit point of function Dcm_DspInternal_WriteDidRequestLengthChk() */
#define DBG_DCM_DSPINTERNAL_WRITEDIDREQUESTLENGTHCHK_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_WRITEDID_ENTRY
/** \brief Entry point of function Dcm_DspInternal_WriteDid() */
#define DBG_DCM_DSPINTERNAL_WRITEDID_ENTRY(a,b,c,d)
#endif

#ifndef DBG_DCM_DSPINTERNAL_WRITEDID_EXIT
/** \brief Exit point of function Dcm_DspInternal_WriteDid() */
#define DBG_DCM_DSPINTERNAL_WRITEDID_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_DCM_DSPINTERNAL_WRITEDIDSIGNAL_ENTRY
/** \brief Entry point of function Dcm_DspInternal_WriteDidSignal() */
#define DBG_DCM_DSPINTERNAL_WRITEDIDSIGNAL_ENTRY(a,b,c,d,e,f)
#endif

#ifndef DBG_DCM_DSPINTERNAL_WRITEDIDSIGNAL_EXIT
/** \brief Exit point of function Dcm_DspInternal_WriteDidSignal() */
#define DBG_DCM_DSPINTERNAL_WRITEDIDSIGNAL_EXIT(a,b,c,d,e,f,g)
#endif

#ifndef DBG_DCM_DSPINTERNAL_WRITEDIDASYNCCLIENTSERVER_ENTRY
/** \brief Entry point of function Dcm_DspInternal_WriteDidAsyncClientServer() */
#define DBG_DCM_DSPINTERNAL_WRITEDIDASYNCCLIENTSERVER_ENTRY(a,b,c,d,e)
#endif

#ifndef DBG_DCM_DSPINTERNAL_WRITEDIDASYNCCLIENTSERVER_EXIT
/** \brief Exit point of function Dcm_DspInternal_WriteDidAsyncClientServer() */
#define DBG_DCM_DSPINTERNAL_WRITEDIDASYNCCLIENTSERVER_EXIT(a,b,c,d,e,f)
#endif

#ifndef DBG_DCM_DSPINTERNAL_WRITEDIDSYNCCLIENTSERVER_ENTRY
/** \brief Entry point of function Dcm_DspInternal_WriteDidSyncClientServer() */
#define DBG_DCM_DSPINTERNAL_WRITEDIDSYNCCLIENTSERVER_ENTRY(a,b,c,d)
#endif

#ifndef DBG_DCM_DSPINTERNAL_WRITEDIDSYNCCLIENTSERVER_EXIT
/** \brief Exit point of function Dcm_DspInternal_WriteDidSyncClientServer() */
#define DBG_DCM_DSPINTERNAL_WRITEDIDSYNCCLIENTSERVER_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_DCM_DSPINTERNAL_WRITEDIDSYNCFUNC_ENTRY
/** \brief Entry point of function Dcm_DspInternal_WriteDidSyncFunc() */
#define DBG_DCM_DSPINTERNAL_WRITEDIDSYNCFUNC_ENTRY(a,b,c,d)
#endif

#ifndef DBG_DCM_DSPINTERNAL_WRITEDIDSYNCFUNC_EXIT
/** \brief Exit point of function Dcm_DspInternal_WriteDidSyncFunc() */
#define DBG_DCM_DSPINTERNAL_WRITEDIDSYNCFUNC_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_DCM_DSPINTERNAL_WRITEDIDASYNCFUNC_ENTRY
/** \brief Entry point of function Dcm_DspInternal_WriteDidAsyncFunc() */
#define DBG_DCM_DSPINTERNAL_WRITEDIDASYNCFUNC_ENTRY(a,b,c,d,e)
#endif

#ifndef DBG_DCM_DSPINTERNAL_WRITEDIDASYNCFUNC_EXIT
/** \brief Exit point of function Dcm_DspInternal_WriteDidAsyncFunc() */
#define DBG_DCM_DSPINTERNAL_WRITEDIDASYNCFUNC_EXIT(a,b,c,d,e,f)
#endif

#ifndef DBG_DCM_DSPINTERNAL_WRITENVMDATA_ENTRY
/** \brief Entry point of function Dcm_DspInternal_WriteNvmData() */
#define DBG_DCM_DSPINTERNAL_WRITENVMDATA_ENTRY(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_WRITENVMDATA_EXIT
/** \brief Exit point of function Dcm_DspInternal_WriteNvmData() */
#define DBG_DCM_DSPINTERNAL_WRITENVMDATA_EXIT(a,b,c,d)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ENDIANNESS_CONVERSION_ENTRY
/** \brief Entry point of function Dcm_DspInternal_Endianness_Conversion() */
#define DBG_DCM_DSPINTERNAL_ENDIANNESS_CONVERSION_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ENDIANNESS_CONVERSION_EXIT
/** \brief Exit point of function Dcm_DspInternal_Endianness_Conversion() */
#define DBG_DCM_DSPINTERNAL_ENDIANNESS_CONVERSION_EXIT(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REQUESTDOWNLOADHANDLER_SVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_RequestDownloadHandler_SvcH() */
#define DBG_DCM_DSPINTERNAL_REQUESTDOWNLOADHANDLER_SVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REQUESTDOWNLOADHANDLER_SVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_RequestDownloadHandler_SvcH() */
#define DBG_DCM_DSPINTERNAL_REQUESTDOWNLOADHANDLER_SVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REQUESTDOWNLOAD_SVCSTART_ENTRY
/** \brief Entry point of function Dcm_DspInternal_RequestDownload_SvcStart() */
#define DBG_DCM_DSPINTERNAL_REQUESTDOWNLOAD_SVCSTART_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REQUESTDOWNLOAD_SVCSTART_EXIT
/** \brief Exit point of function Dcm_DspInternal_RequestDownload_SvcStart() */
#define DBG_DCM_DSPINTERNAL_REQUESTDOWNLOAD_SVCSTART_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REQUESTDOWNLOAD_SVCCONT_ENTRY
/** \brief Entry point of function Dcm_DspInternal_RequestDownload_SvcCont() */
#define DBG_DCM_DSPINTERNAL_REQUESTDOWNLOAD_SVCCONT_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REQUESTDOWNLOAD_SVCCONT_EXIT
/** \brief Exit point of function Dcm_DspInternal_RequestDownload_SvcCont() */
#define DBG_DCM_DSPINTERNAL_REQUESTDOWNLOAD_SVCCONT_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REQUESTUPLOADHANDLER_SVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_RequestUploadHandler_SvcH() */
#define DBG_DCM_DSPINTERNAL_REQUESTUPLOADHANDLER_SVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REQUESTUPLOADHANDLER_SVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_RequestUploadHandler_SvcH() */
#define DBG_DCM_DSPINTERNAL_REQUESTUPLOADHANDLER_SVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REQUESTUPLOAD_SVCSTART_ENTRY
/** \brief Entry point of function Dcm_DspInternal_RequestUpload_SvcStart() */
#define DBG_DCM_DSPINTERNAL_REQUESTUPLOAD_SVCSTART_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REQUESTUPLOAD_SVCSTART_EXIT
/** \brief Exit point of function Dcm_DspInternal_RequestUpload_SvcStart() */
#define DBG_DCM_DSPINTERNAL_REQUESTUPLOAD_SVCSTART_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REQUESTUPLOAD_SVCCONT_ENTRY
/** \brief Entry point of function Dcm_DspInternal_RequestUpload_SvcCont() */
#define DBG_DCM_DSPINTERNAL_REQUESTUPLOAD_SVCCONT_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REQUESTUPLOAD_SVCCONT_EXIT
/** \brief Exit point of function Dcm_DspInternal_RequestUpload_SvcCont() */
#define DBG_DCM_DSPINTERNAL_REQUESTUPLOAD_SVCCONT_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_TRANSFERDATAHANDLER_SVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_TransferDataHandler_SvcH() */
#define DBG_DCM_DSPINTERNAL_TRANSFERDATAHANDLER_SVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_TRANSFERDATAHANDLER_SVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_TransferDataHandler_SvcH() */
#define DBG_DCM_DSPINTERNAL_TRANSFERDATAHANDLER_SVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_TRANSFERDATA_SVCSTART_ENTRY
/** \brief Entry point of function Dcm_DspInternal_TransferData_SvcStart() */
#define DBG_DCM_DSPINTERNAL_TRANSFERDATA_SVCSTART_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_TRANSFERDATA_SVCSTART_EXIT
/** \brief Exit point of function Dcm_DspInternal_TransferData_SvcStart() */
#define DBG_DCM_DSPINTERNAL_TRANSFERDATA_SVCSTART_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_TRANSFERDATA_SVCCONT_ENTRY
/** \brief Entry point of function Dcm_DspInternal_TransferData_SvcCont() */
#define DBG_DCM_DSPINTERNAL_TRANSFERDATA_SVCCONT_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_TRANSFERDATA_SVCCONT_EXIT
/** \brief Exit point of function Dcm_DspInternal_TransferData_SvcCont() */
#define DBG_DCM_DSPINTERNAL_TRANSFERDATA_SVCCONT_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DOWNLOADTRANSFERDATA_ENTRY
/** \brief Entry point of function Dcm_DspInternal_DownloadTransferData() */
#define DBG_DCM_DSPINTERNAL_DOWNLOADTRANSFERDATA_ENTRY(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_DOWNLOADTRANSFERDATA_EXIT
/** \brief Exit point of function Dcm_DspInternal_DownloadTransferData() */
#define DBG_DCM_DSPINTERNAL_DOWNLOADTRANSFERDATA_EXIT(a,b,c,d)
#endif

#ifndef DBG_DCM_DSPINTERNAL_UPLOADTRANSFERDATA_ENTRY
/** \brief Entry point of function Dcm_DspInternal_UploadTransferData() */
#define DBG_DCM_DSPINTERNAL_UPLOADTRANSFERDATA_ENTRY(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_UPLOADTRANSFERDATA_EXIT
/** \brief Exit point of function Dcm_DspInternal_UploadTransferData() */
#define DBG_DCM_DSPINTERNAL_UPLOADTRANSFERDATA_EXIT(a,b,c,d)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REQUESTTRANSFEREXITHANDLER_SVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_RequestTransferExitHandler_SvcH() */
#define DBG_DCM_DSPINTERNAL_REQUESTTRANSFEREXITHANDLER_SVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REQUESTTRANSFEREXITHANDLER_SVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_RequestTransferExitHandler_SvcH() */
#define DBG_DCM_DSPINTERNAL_REQUESTTRANSFEREXITHANDLER_SVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REQUESTTRANSFEREXIT_SVCSTART_ENTRY
/** \brief Entry point of function Dcm_DspInternal_RequestTransferExit_SvcStart() */
#define DBG_DCM_DSPINTERNAL_REQUESTTRANSFEREXIT_SVCSTART_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REQUESTTRANSFEREXIT_SVCSTART_EXIT
/** \brief Exit point of function Dcm_DspInternal_RequestTransferExit_SvcStart() */
#define DBG_DCM_DSPINTERNAL_REQUESTTRANSFEREXIT_SVCSTART_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REQUESTTRANSFEREXIT_SVCCONT_ENTRY
/** \brief Entry point of function Dcm_DspInternal_RequestTransferExit_SvcCont() */
#define DBG_DCM_DSPINTERNAL_REQUESTTRANSFEREXIT_SVCCONT_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_REQUESTTRANSFEREXIT_SVCCONT_EXIT
/** \brief Exit point of function Dcm_DspInternal_RequestTransferExit_SvcCont() */
#define DBG_DCM_DSPINTERNAL_REQUESTTRANSFEREXIT_SVCCONT_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_LINKCONTROLHANDLER_SVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_LinkControlHandler_SvcH() */
#define DBG_DCM_DSPINTERNAL_LINKCONTROLHANDLER_SVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_LINKCONTROLHANDLER_SVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_LinkControlHandler_SvcH() */
#define DBG_DCM_DSPINTERNAL_LINKCONTROLHANDLER_SVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_LINKCONTROL_SVCSTART_ENTRY
/** \brief Entry point of function Dcm_DspInternal_LinkControl_SvcStart() */
#define DBG_DCM_DSPINTERNAL_LINKCONTROL_SVCSTART_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_LINKCONTROL_SVCSTART_EXIT
/** \brief Exit point of function Dcm_DspInternal_LinkControl_SvcStart() */
#define DBG_DCM_DSPINTERNAL_LINKCONTROL_SVCSTART_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_LINKCONTROL_SVCCONT_ENTRY
/** \brief Entry point of function Dcm_DspInternal_LinkControl_SvcCont() */
#define DBG_DCM_DSPINTERNAL_LINKCONTROL_SVCCONT_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_LINKCONTROL_SVCCONT_EXIT
/** \brief Exit point of function Dcm_DspInternal_LinkControl_SvcCont() */
#define DBG_DCM_DSPINTERNAL_LINKCONTROL_SVCCONT_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_FIXEDBAUDRATEVERIFICATION_SSVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_FixedBaudrateVerification_SSvcH() */
#define DBG_DCM_DSPINTERNAL_FIXEDBAUDRATEVERIFICATION_SSVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_FIXEDBAUDRATEVERIFICATION_SSVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_FixedBaudrateVerification_SSvcH() */
#define DBG_DCM_DSPINTERNAL_FIXEDBAUDRATEVERIFICATION_SSVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_SPECIFICBAUDRATEVERIFICATION_SSVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_SpecificBaudrateVerification_SSvcH() */
#define DBG_DCM_DSPINTERNAL_SPECIFICBAUDRATEVERIFICATION_SSVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_SPECIFICBAUDRATEVERIFICATION_SSVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_SpecificBaudrateVerification_SSvcH() */
#define DBG_DCM_DSPINTERNAL_SPECIFICBAUDRATEVERIFICATION_SSVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_TRANSITIONBAUDRATE_SSVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_TransitionBaudrate_SSvcH() */
#define DBG_DCM_DSPINTERNAL_TRANSITIONBAUDRATE_SSVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_TRANSITIONBAUDRATE_SSVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_TransitionBaudrate_SSvcH() */
#define DBG_DCM_DSPINTERNAL_TRANSITIONBAUDRATE_SSVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_LINKCONTROL_EXECUTION_ENTRY
/** \brief Entry point of function Dcm_DspInternal_LinkControl_Execution() */
#define DBG_DCM_DSPINTERNAL_LINKCONTROL_EXECUTION_ENTRY(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_LINKCONTROL_EXECUTION_EXIT
/** \brief Exit point of function Dcm_DspInternal_LinkControl_Execution() */
#define DBG_DCM_DSPINTERNAL_LINKCONTROL_EXECUTION_EXIT(a,b,c,d)
#endif

#ifndef DBG_DCM_DSPINTERNAL_FINALROERESPONSE_ENTRY
/** \brief Entry point of function Dcm_DspInternal_FinalRoeResponse() */
#define DBG_DCM_DSPINTERNAL_FINALROERESPONSE_ENTRY(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_FINALROERESPONSE_EXIT
/** \brief Exit point of function Dcm_DspInternal_FinalRoeResponse() */
#define DBG_DCM_DSPINTERNAL_FINALROERESPONSE_EXIT(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ROEWRITETONVM_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ROEWriteToNvM() */
#define DBG_DCM_DSPINTERNAL_ROEWRITETONVM_ENTRY()
#endif

#ifndef DBG_DCM_DSPINTERNAL_ROEWRITETONVM_EXIT
/** \brief Exit point of function Dcm_DspInternal_ROEWriteToNvM() */
#define DBG_DCM_DSPINTERNAL_ROEWRITETONVM_EXIT(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_READMEMORYBYADDRESS_SVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ReadMemoryByAddress_SvcH() */
#define DBG_DCM_DSPINTERNAL_READMEMORYBYADDRESS_SVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_READMEMORYBYADDRESS_SVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_ReadMemoryByAddress_SvcH() */
#define DBG_DCM_DSPINTERNAL_READMEMORYBYADDRESS_SVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_READMEMORYRANGECHK_ENTRY
/** \brief Entry point of function Dcm_DspInternal_ReadMemoryRangeChk() */
#define DBG_DCM_DSPINTERNAL_READMEMORYRANGECHK_ENTRY(a,b,c,d)
#endif

#ifndef DBG_DCM_DSPINTERNAL_READMEMORYRANGECHK_EXIT
/** \brief Exit point of function Dcm_DspInternal_ReadMemoryRangeChk() */
#define DBG_DCM_DSPINTERNAL_READMEMORYRANGECHK_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_DCM_DSPINTERNAL_WRITEMEMORYBYADDRESS_SVCH_ENTRY
/** \brief Entry point of function Dcm_DspInternal_WriteMemoryByAddress_SvcH() */
#define DBG_DCM_DSPINTERNAL_WRITEMEMORYBYADDRESS_SVCH_ENTRY(a,b)
#endif

#ifndef DBG_DCM_DSPINTERNAL_WRITEMEMORYBYADDRESS_SVCH_EXIT
/** \brief Exit point of function Dcm_DspInternal_WriteMemoryByAddress_SvcH() */
#define DBG_DCM_DSPINTERNAL_WRITEMEMORYBYADDRESS_SVCH_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_DSPINTERNAL_WRITEMEMORYRANGECHK_ENTRY
/** \brief Entry point of function Dcm_DspInternal_WriteMemoryRangeChk() */
#define DBG_DCM_DSPINTERNAL_WRITEMEMORYRANGECHK_ENTRY(a,b,c,d)
#endif

#ifndef DBG_DCM_DSPINTERNAL_WRITEMEMORYRANGECHK_EXIT
/** \brief Exit point of function Dcm_DspInternal_WriteMemoryRangeChk() */
#define DBG_DCM_DSPINTERNAL_WRITEMEMORYRANGECHK_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_DCM_DSPINTERNAL_GETMEMORYADDRESSANDSIZE_ENTRY
/** \brief Entry point of function Dcm_DspInternal_GetMemoryAddressAndSize() */
#define DBG_DCM_DSPINTERNAL_GETMEMORYADDRESSANDSIZE_ENTRY(a,b,c,d,e)
#endif

#ifndef DBG_DCM_DSPINTERNAL_GETMEMORYADDRESSANDSIZE_EXIT
/** \brief Exit point of function Dcm_DspInternal_GetMemoryAddressAndSize() */
#define DBG_DCM_DSPINTERNAL_GETMEMORYADDRESSANDSIZE_EXIT(a,b,c,d,e,f)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ADDRESSLENGTHANDFORMAT_VERIFICATION_ENTRY
/** \brief Entry point of function Dcm_DspInternal_AddressLengthAndFormat_Verification() */
#define DBG_DCM_DSPINTERNAL_ADDRESSLENGTHANDFORMAT_VERIFICATION_ENTRY(a)
#endif

#ifndef DBG_DCM_DSPINTERNAL_ADDRESSLENGTHANDFORMAT_VERIFICATION_EXIT
/** \brief Exit point of function Dcm_DspInternal_AddressLengthAndFormat_Verification() */
#define DBG_DCM_DSPINTERNAL_ADDRESSLENGTHANDFORMAT_VERIFICATION_EXIT(a,b)
#endif

#ifndef DBG_DCM_HSMINIT_ENTRY
/** \brief Entry point of function Dcm_HsmInit() */
#define DBG_DCM_HSMINIT_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMINIT_EXIT
/** \brief Exit point of function Dcm_HsmInit() */
#define DBG_DCM_HSMINIT_EXIT(a)
#endif

#ifndef DBG_DCM_HSMINITINST_ENTRY
/** \brief Entry point of function DCM_HSMINITINST() */
#define DBG_DCM_HSMINITINST_ENTRY(a,b)
#endif

#ifndef DBG_DCM_HSMINITINST_EXIT
/** \brief Exit point of function DCM_HSMINITINST() */
#define DBG_DCM_HSMINITINST_EXIT(a,b)
#endif

#ifndef DBG_DCM_HSMEMITINST_ENTRY
/** \brief Entry point of function DCM_HSMEMITINST() */
#define DBG_DCM_HSMEMITINST_ENTRY(a,b,c)
#endif

#ifndef DBG_DCM_HSMEMITINST_EXIT
/** \brief Exit point of function DCM_HSMEMITINST() */
#define DBG_DCM_HSMEMITINST_EXIT(a,b,c,d)
#endif

#ifndef DBG_DCM_HSMEMITTOSELFINST_ENTRY
/** \brief Entry point of function DCM_HSMEMITTOSELFINST() */
#define DBG_DCM_HSMEMITTOSELFINST_ENTRY(a,b,c)
#endif

#ifndef DBG_DCM_HSMEMITTOSELFINST_EXIT
/** \brief Exit point of function DCM_HSMEMITTOSELFINST() */
#define DBG_DCM_HSMEMITTOSELFINST_EXIT(a,b,c,d)
#endif

#ifndef DBG_DCM_HSMMAIN_ENTRY
/** \brief Entry point of function Dcm_HsmMain() */
#define DBG_DCM_HSMMAIN_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMMAIN_EXIT
/** \brief Exit point of function Dcm_HsmMain() */
#define DBG_DCM_HSMMAIN_EXIT(a)
#endif

#ifndef DBG_DCM_HSMMAININST_ENTRY
/** \brief Entry point of function DCM_HSMMAININST() */
#define DBG_DCM_HSMMAININST_ENTRY(a,b)
#endif

#ifndef DBG_DCM_HSMMAININST_EXIT
/** \brief Exit point of function DCM_HSMMAININST() */
#define DBG_DCM_HSMMAININST_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_HSMSETTRACING_ENTRY
/** \brief Entry point of function Dcm_HsmSetTracing() */
#define DBG_DCM_HSMSETTRACING_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMSETTRACING_EXIT
/** \brief Exit point of function Dcm_HsmSetTracing() */
#define DBG_DCM_HSMSETTRACING_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDELFROMQUEUE_ENTRY
/** \brief Entry point of function Dcm_HsmDelFromQueue() */
#define DBG_DCM_HSMDELFROMQUEUE_ENTRY(a,b,c)
#endif

#ifndef DBG_DCM_HSMDELFROMQUEUE_EXIT
/** \brief Exit point of function Dcm_HsmDelFromQueue() */
#define DBG_DCM_HSMDELFROMQUEUE_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_HSMTRAN_ENTRY
/** \brief Entry point of function Dcm_HsmTran() */
#define DBG_DCM_HSMTRAN_ENTRY(a,b,c)
#endif

#ifndef DBG_DCM_HSMTRAN_EXIT
/** \brief Exit point of function Dcm_HsmTran() */
#define DBG_DCM_HSMTRAN_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_HSMINITSUBSTATES_ENTRY
/** \brief Entry point of function Dcm_HsmInitSubstates() */
#define DBG_DCM_HSMINITSUBSTATES_ENTRY(a,b)
#endif

#ifndef DBG_DCM_HSMINITSUBSTATES_EXIT
/** \brief Exit point of function Dcm_HsmInitSubstates() */
#define DBG_DCM_HSMINITSUBSTATES_EXIT(a,b)
#endif

#ifndef DBG_DCM_HSMFINDEVTODISPATCH_ENTRY
/** \brief Entry point of function Dcm_HsmFindEvToDispatch() */
#define DBG_DCM_HSMFINDEVTODISPATCH_ENTRY(a,b,c,d)
#endif

#ifndef DBG_DCM_HSMFINDEVTODISPATCH_EXIT
/** \brief Exit point of function Dcm_HsmFindEvToDispatch() */
#define DBG_DCM_HSMFINDEVTODISPATCH_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_DCM_HSMDCMSFTOPENTRY_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfTopEntry() */
#define DBG_DCM_HSMDCMSFTOPENTRY_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFTOPENTRY_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfTopEntry() */
#define DBG_DCM_HSMDCMSFTOPENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFWAITFORFULLCOMGUARD1_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfWaitForFullComGuard1() */
#define DBG_DCM_HSMDCMSFWAITFORFULLCOMGUARD1_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFWAITFORFULLCOMGUARD1_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfWaitForFullComGuard1() */
#define DBG_DCM_HSMDCMSFWAITFORFULLCOMGUARD1_EXIT(a, b)
#endif

#ifndef DBG_DCM_HSMDCMSFWAITFORFULLCOMACTION1_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfWaitForFullComAction1() */
#define DBG_DCM_HSMDCMSFWAITFORFULLCOMACTION1_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFWAITFORFULLCOMACTION1_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfWaitForFullComAction1() */
#define DBG_DCM_HSMDCMSFWAITFORFULLCOMACTION1_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFWAITFORFULLCOMACTION2_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfWaitForFullComAction2() */
#define DBG_DCM_HSMDCMSFWAITFORFULLCOMACTION2_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFWAITFORFULLCOMACTION2_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfWaitForFullComAction2() */
#define DBG_DCM_HSMDCMSFWAITFORFULLCOMACTION2_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFOUTOFSERVICEENTRY_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfOutOfServiceEntry() */
#define DBG_DCM_HSMDCMSFOUTOFSERVICEENTRY_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFOUTOFSERVICEENTRY_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfOutOfServiceEntry() */
#define DBG_DCM_HSMDCMSFOUTOFSERVICEENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFOUTOFSERVICEACTION1_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfOutOfServiceAction1() */
#define DBG_DCM_HSMDCMSFOUTOFSERVICEACTION1_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFOUTOFSERVICEACTION1_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfOutOfServiceAction1() */
#define DBG_DCM_HSMDCMSFOUTOFSERVICEACTION1_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFOUTOFSERVICEGUARD2_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfOutOfServiceGuard2() */
#define DBG_DCM_HSMDCMSFOUTOFSERVICEGUARD2_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFOUTOFSERVICEGUARD2_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfOutOfServiceGuard2() */
#define DBG_DCM_HSMDCMSFOUTOFSERVICEGUARD2_EXIT(a, b)
#endif

#ifndef DBG_DCM_HSMDCMSFOUTOFSERVICEACTION2_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfOutOfServiceAction2() */
#define DBG_DCM_HSMDCMSFOUTOFSERVICEACTION2_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFOUTOFSERVICEACTION2_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfOutOfServiceAction2() */
#define DBG_DCM_HSMDCMSFOUTOFSERVICEACTION2_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFOUTOFSERVICEACTION3_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfOutOfServiceAction2() */
#define DBG_DCM_HSMDCMSFOUTOFSERVICEACTION3_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFOUTOFSERVICEACTION3_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfOutOfServiceAction2() */
#define DBG_DCM_HSMDCMSFOUTOFSERVICEACTION3_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFOUTOFSERVICEGUARD3_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfOutOfServiceGuard3() */
#define DBG_DCM_HSMDCMSFOUTOFSERVICEGUARD3_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFOUTOFSERVICEGUARD3_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfOutOfServiceGuard3() */
#define DBG_DCM_HSMDCMSFOUTOFSERVICEGUARD3_EXIT(a, b)
#endif

#ifndef DBG_DCM_HSMDCMSFOUTOFSERVICEGUARD4_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfOutOfServiceGuard4() */
#define DBG_DCM_HSMDCMSFOUTOFSERVICEGUARD4_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFOUTOFSERVICEGUARD4_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfOutOfServiceGuard4() */
#define DBG_DCM_HSMDCMSFOUTOFSERVICEGUARD4_EXIT(a, b)
#endif

#ifndef DBG_DCM_HSMDCMSFOUTOFSERVICEACTION5_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfOutOfServiceAction5() */
#define DBG_DCM_HSMDCMSFOUTOFSERVICEACTION5_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFOUTOFSERVICEACTION5_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfOutOfServiceAction5() */
#define DBG_DCM_HSMDCMSFOUTOFSERVICEACTION5_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFOOSINITACTION1_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfOosInitAction1() */
#define DBG_DCM_HSMDCMSFOOSINITACTION1_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFOOSINITACTION1_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfOosInitAction1() */
#define DBG_DCM_HSMDCMSFOOSINITACTION1_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFOOSNOTIFIEDENTRY_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfOosNotifiedEntry() */
#define DBG_DCM_HSMDCMSFOOSNOTIFIEDENTRY_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFOOSNOTIFIEDENTRY_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfOosNotifiedEntry() */
#define DBG_DCM_HSMDCMSFOOSNOTIFIEDENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFINSERVICEENTRY_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfInServiceEntry() */
#define DBG_DCM_HSMDCMSFINSERVICEENTRY_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFINSERVICEENTRY_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfInServiceEntry() */
#define DBG_DCM_HSMDCMSFINSERVICEENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFINSERVICEACTION1_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfInServiceAction1() */
#define DBG_DCM_HSMDCMSFINSERVICEACTION1_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFINSERVICEACTION1_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfInServiceAction1() */
#define DBG_DCM_HSMDCMSFINSERVICEACTION1_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFFINISHINGENTRY_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfFinishingEntry() */
#define DBG_DCM_HSMDCMSFFINISHINGENTRY_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFFINISHINGENTRY_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfFinishingEntry() */
#define DBG_DCM_HSMDCMSFFINISHINGENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFFINISHINGEXIT_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfFinishingExit() */
#define DBG_DCM_HSMDCMSFFINISHINGEXIT_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFFINISHINGEXIT_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfFinishingExit() */
#define DBG_DCM_HSMDCMSFFINISHINGEXIT_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFCANCELPROCESSINGENTRY_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfCancelProcessingEntry() */
#define DBG_DCM_HSMDCMSFCANCELPROCESSINGENTRY_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFCANCELPROCESSINGENTRY_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfCancelProcessingEntry() */
#define DBG_DCM_HSMDCMSFCANCELPROCESSINGENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFCONFIRMINGNOKENTRY_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfConfirmingNOkEntry() */
#define DBG_DCM_HSMDCMSFCONFIRMINGNOKENTRY_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFCONFIRMINGNOKENTRY_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfConfirmingNOkEntry() */
#define DBG_DCM_HSMDCMSFCONFIRMINGNOKENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFCONFIRMINGOKENTRY_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfConfirmingOkEntry() */
#define DBG_DCM_HSMDCMSFCONFIRMINGOKENTRY_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFCONFIRMINGOKENTRY_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfConfirmingOkEntry() */
#define DBG_DCM_HSMDCMSFCONFIRMINGOKENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFROEPRSERVICECALLEDACTION2_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfRoePrServiceCalledAction2() */
#define DBG_DCM_HSMDCMSFROEPRSERVICECALLEDACTION2_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFROEPRSERVICECALLEDACTION2_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfRoePrServiceCalledAction2() */
#define DBG_DCM_HSMDCMSFROEPRSERVICECALLEDACTION2_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFROEFINALRESPONSEENTRY_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfRoeFinalResponseEntry() */
#define DBG_DCM_HSMDCMSFROEFINALRESPONSEENTRY_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFROEFINALRESPONSEENTRY_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfRoeFinalResponseEntry() */
#define DBG_DCM_HSMDCMSFROEFINALRESPONSEENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFROEPRRESPONSEENTRY_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfRoePrResponseEntry() */
#define DBG_DCM_HSMDCMSFROEPRRESPONSEENTRY_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFROEPRRESPONSEENTRY_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfRoePrResponseEntry() */
#define DBG_DCM_HSMDCMSFROEPRRESPONSEENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFSENDINGENTRY_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfSendingEntry() */
#define DBG_DCM_HSMDCMSFSENDINGENTRY_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFSENDINGENTRY_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfSendingEntry() */
#define DBG_DCM_HSMDCMSFSENDINGENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFNORMALPROCESSINGENTRY_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfNormalProcessingEntry() */
#define DBG_DCM_HSMDCMSFNORMALPROCESSINGENTRY_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFNORMALPROCESSINGENTRY_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfNormalProcessingEntry() */
#define DBG_DCM_HSMDCMSFNORMALPROCESSINGENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGACTION3_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfEmulatePgBufProcessingAction3() */
#define  DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGACTION3_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGACTION3_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfEmulatePgBufProcessingAction3() */
#define DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGACTION3_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSREALPGBUFPROCESSINGACTION1_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfRealPgBufProcessingAction1() */
#define DBG_DCM_HSMDCMSREALPGBUFPROCESSINGACTION1_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSREALPGBUFPROCESSINGACTION1_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfRealPgBufProcessingAction1() */
#define DBG_DCM_HSMDCMSREALPGBUFPROCESSINGACTION1_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGENTRY_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfEmulatePgBufProcessingEntry() */
#define DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGENTRY_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGENTRY_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfEmulatePgBufProcessingEntry() */
#define DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGEXIT_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfEmulatePgBufProcessingExit() */
#define DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGEXIT_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGEXIT_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfEmulatePgBufProcessingExit() */
#define DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGEXIT_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGGUARD1_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfEmulatePgBufProcessingGuard1() */
#define DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGGUARD1_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGGUARD1_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfEmulatePgBufProcessingGuard1() */
#define DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGGUARD1_EXIT(a, b)
#endif

#ifndef DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGACTION1_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfEmulatePgBufProcessingAction1() */
#define DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGACTION1_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGACTION1_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfEmulatePgBufProcessingAction1() */
#define DBG_DCM_HSMDCMSFEMULATEPGBUFPROCESSINGACTION1_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFREALPGBUFPROCESSINGENTRY_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfRealPgBufProcessingEntry() */
#define DBG_DCM_HSMDCMSFREALPGBUFPROCESSINGENTRY_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFREALPGBUFPROCESSINGENTRY_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfRealPgBufProcessingEntry() */
#define DBG_DCM_HSMDCMSFREALPGBUFPROCESSINGENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFPGBUFDATAAVAILABLEENTRY_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfPgBufDataAvailableEntry() */
#define DBG_DCM_HSMDCMSFPGBUFDATAAVAILABLEENTRY_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFPGBUFDATAAVAILABLEENTRY_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfPgBufDataAvailableEntry() */
#define DBG_DCM_HSMDCMSFPGBUFDATAAVAILABLEENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFPGBUFDATAREQUESTEDENTRY_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfPgBufDataRequestedEntry() */
#define DBG_DCM_HSMDCMSFPGBUFDATAREQUESTEDENTRY_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFPGBUFDATAREQUESTEDENTRY_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfPgBufDataRequestedEntry() */
#define DBG_DCM_HSMDCMSFPGBUFDATAREQUESTEDENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFPGBUFDATAREQUESTEDEXIT_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfPgBufDataRequestedExit() */
#define DBG_DCM_HSMDCMSFPGBUFDATAREQUESTEDEXIT_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFPGBUFDATAREQUESTEDEXIT_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfPgBufDataRequestedExit() */
#define DBG_DCM_HSMDCMSFPGBUFDATAREQUESTEDEXIT_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFSENDINGGRENTRY_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfSendingGrEntry() */
#define DBG_DCM_HSMDCMSFSENDINGGRENTRY_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFSENDINGGRENTRY_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfSendingGrEntry() */
#define DBG_DCM_HSMDCMSFSENDINGGRENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFSERVICECALLEDENTRY_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfServiceCalledEntry() */
#define DBG_DCM_HSMDCMSFSERVICECALLEDENTRY_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFSERVICECALLEDENTRY_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfServiceCalledEntry() */
#define DBG_DCM_HSMDCMSFSERVICECALLEDENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFSERVICECALLEDGUARD1_ENTRY
/** \brief Exit point of function Dcm_HsmDcmSfServiceCalledGuard1() */
#define DBG_DCM_HSMDCMSFSERVICECALLEDGUARD1_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFSERVICECALLEDGUARD1_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfServiceCalledGuard1() */
#define DBG_DCM_HSMDCMSFSERVICECALLEDGUARD1_EXIT(a, b)
#endif

#ifndef DBG_DCM_HSMDCMSFSERVICECALLEDGUARD2_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfServiceCalledGuard2() */
#define DBG_DCM_HSMDCMSFSERVICECALLEDGUARD2_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFSERVICECALLEDGUARD2_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfServiceCalledGuard2() */
#define DBG_DCM_HSMDCMSFSERVICECALLEDGUARD2_EXIT(a, b)
#endif

#ifndef DBG_DCM_HSMDCMSFSERVICECALLEDGUARD3_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfServiceCalledGuard3() */
#define DBG_DCM_HSMDCMSFSERVICECALLEDGUARD3_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFSERVICECALLEDGUARD3_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfServiceCalledGuard3() */
#define DBG_DCM_HSMDCMSFSERVICECALLEDGUARD3_EXIT(a, b)
#endif

#ifndef DBG_DCM_HSMDCMSFSERVICECALLEDACTION4_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfServiceCalledAction4() */
#define DBG_DCM_HSMDCMSFSERVICECALLEDACTION4_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFSERVICECALLEDACTION4_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfServiceCalledAction4() */
#define DBG_DCM_HSMDCMSFSERVICECALLEDACTION4_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFSERVICECALLEDGUARD5_ENTRY
/** \brief Exit point of function Dcm_HsmDcmSfServiceCalledGuard5() */
#define DBG_DCM_HSMDCMSFSERVICECALLEDGUARD5_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFSERVICECALLEDGUARD5_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfServiceCalledGuard5() */
#define DBG_DCM_HSMDCMSFSERVICECALLEDGUARD5_EXIT(a, b)
#endif

#ifndef DBG_DCM_HSMDCMSFSERVICECALLEDACTION5_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfServiceCalledAction5() */
#define DBG_DCM_HSMDCMSFSERVICECALLEDACTION5_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFSERVICECALLEDACTION5_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfServiceCalledAction5() */
#define DBG_DCM_HSMDCMSFSERVICECALLEDACTION5_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFSERVICECALLEDGUARD6_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfServiceCalledGuard6() */
#define DBG_DCM_HSMDCMSFSERVICECALLEDGUARD6_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFSERVICECALLEDGUARD6_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfServiceCalledGuard6() */
#define DBG_DCM_HSMDCMSFSERVICECALLEDGUARD6_EXIT(a, b)
#endif

#ifndef DBG_DCM_HSMDCMSFSERVICECALLEDGUARD7_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfServiceCalledGuard7() */
#define DBG_DCM_HSMDCMSFSERVICECALLEDGUARD7_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFSERVICECALLEDGUARD7_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfServiceCalledGuard7() */
#define DBG_DCM_HSMDCMSFSERVICECALLEDGUARD7_EXIT(a, b)
#endif

#ifndef DBG_DCM_HSMDCMSFSENDRPENTRY_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfSendRpEntry() */
#define DBG_DCM_HSMDCMSFSENDRPENTRY_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFSENDRPENTRY_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfSendRpEntry() */
#define DBG_DCM_HSMDCMSFSENDRPENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFSENDRPEXIT_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfSendRpExit() */
#define DBG_DCM_HSMDCMSFSENDRPEXIT_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFSENDRPEXIT_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfSendRpExit() */
#define DBG_DCM_HSMDCMSFSENDRPEXIT_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFSENDRPFORCEDACTION1_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfSendRpForcedAction1() */
#define DBG_DCM_HSMDCMSFSENDRPFORCEDACTION1_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFSENDRPFORCEDACTION1_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfSendRpForcedAction1() */
#define DBG_DCM_HSMDCMSFSENDRPFORCEDACTION1_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFWAITFORAPPLGUARD2_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfWaitForApplGuard2() */
#define DBG_DCM_HSMDCMSFWAITFORAPPLGUARD2_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFWAITFORAPPLGUARD2_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfWaitForApplGuard2() */
#define DBG_DCM_HSMDCMSFWAITFORAPPLGUARD2_EXIT(a, b)
#endif

#ifndef DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSENTRY_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfWaitForFullComProcessEntry() */
#define DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSENTRY_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSENTRY_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfWaitForFullComProcessEntry() */
#define DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSENTRY_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSEXIT_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfWaitForFullComProcessExit() */
#define DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSEXIT_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSEXIT_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfWaitForFullComProcessExit() */
#define DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSEXIT_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSACTION1_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfWaitForFullComProcessAction1() */
#define DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSACTION1_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSACTION1_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfWaitForFullComProcessAction1() */
#define DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSACTION1_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSGUARD4_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfWaitForFullComProcessGuard4() */
#define DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSGUARD4_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSGUARD4_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfWaitForFullComProcessGuard4() */
#define DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSGUARD4_EXIT(a, b)
#endif

#ifndef DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSACTION4_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfWaitForFullComProcessAction4() */
#define DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSACTION4_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSACTION4_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfWaitForFullComProcessAction4() */
#define DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSACTION4_EXIT(a)
#endif

#ifndef DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSGUARD5_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfWaitForFullComProcessGuard5() */
#define DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSGUARD5_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSGUARD5_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfWaitForFullComProcessGuard5() */
#define DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSGUARD5_EXIT(a, b)
#endif

#ifndef DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSACTION5_ENTRY
/** \brief Entry point of function Dcm_HsmDcmSfWaitForFullComProcessAction5() */
#define DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSACTION5_ENTRY(a)
#endif

#ifndef DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSACTION5_EXIT
/** \brief Exit point of function Dcm_HsmDcmSfWaitForFullComProcessAction5() */
#define DBG_DCM_HSMDCMSFWAITFORFULLCOMPROCESSACTION5_EXIT(a)
#endif

#ifndef DBG_DCM_CHECKBUF_ENTRY
/** \brief Entry point of function Dcm_CheckBuf() */
#define DBG_DCM_CHECKBUF_ENTRY(a,b)
#endif

#ifndef DBG_DCM_CHECKBUF_EXIT
/** \brief Exit point of function Dcm_CheckBuf() */
#define DBG_DCM_CHECKBUF_EXIT(a,b,c)
#endif

#ifndef DBG_DCM_STARTTIMERTX_ENTRY
/** \brief Entry point of function Dcm_StartTimerTx() */
#define DBG_DCM_STARTTIMERTX_ENTRY(a,b)
#endif

#ifndef DBG_DCM_STARTTIMERTX_EXIT
/** \brief Exit point of function Dcm_StartTimerTx() */
#define DBG_DCM_STARTTIMERTX_EXIT(a,b)
#endif

#ifndef DBG_DCM_STARTTIMERPGBUF_ENTRY
/** \brief Entry point of function Dcm_StartTimerPgBuf() */
#define DBG_DCM_STARTTIMERPGBUF_ENTRY(a,b)
#endif

#ifndef DBG_DCM_STARTTIMERPGBUF_EXIT
/** \brief Exit point of function Dcm_StartTimerPgBuf() */
#define DBG_DCM_STARTTIMERPGBUF_EXIT(a,b)
#endif

#ifndef DBG_DCM_STARTTIMER2_ENTRY
/** \brief Entry point of function Dcm_StartTimer2() */
#define DBG_DCM_STARTTIMER2_ENTRY(a,b)
#endif

#ifndef DBG_DCM_STARTTIMER2_EXIT
/** \brief Exit point of function Dcm_StartTimer2() */
#define DBG_DCM_STARTTIMER2_EXIT(a,b)
#endif

#ifndef DBG_DCM_STARTTIMER3_ENTRY
/** \brief Entry point of function Dcm_StartTimer3() */
#define DBG_DCM_STARTTIMER3_ENTRY(a,b)
#endif

#ifndef DBG_DCM_STARTTIMER3_EXIT
/** \brief Exit point of function Dcm_StartTimer3() */
#define DBG_DCM_STARTTIMER3_EXIT(a,b)
#endif

#ifndef DBG_DCM_STOPTIMERTX_ENTRY
/** \brief Entry point of function Dcm_StopTimerTx() */
#define DBG_DCM_STOPTIMERTX_ENTRY()
#endif

#ifndef DBG_DCM_STOPTIMERTX_EXIT
/** \brief Exit point of function Dcm_StopTimerTx() */
#define DBG_DCM_STOPTIMERTX_EXIT()
#endif

#ifndef DBG_DCM_STOPTIMERPGBUF_ENTRY
/** \brief Entry point of function Dcm_StopTimerPgBuf() */
#define DBG_DCM_STOPTIMERPGBUF_ENTRY()
#endif

#ifndef DBG_DCM_STOPTIMERPGBUF_EXIT
/** \brief Exit point of function Dcm_StopTimerPgBuf() */
#define DBG_DCM_STOPTIMERPGBUF_EXIT()
#endif

#ifndef DBG_DCM_STOPTIMER2_ENTRY
/** \brief Entry point of function Dcm_StopTimer2() */
#define DBG_DCM_STOPTIMER2_ENTRY()
#endif

#ifndef DBG_DCM_STOPTIMER2_EXIT
/** \brief Exit point of function Dcm_StopTimer2() */
#define DBG_DCM_STOPTIMER2_EXIT()
#endif

#ifndef DBG_DCM_RELEASERXTXBUFFERS_ENTRY
/** \brief Entry point of function Dcm_ReleaseRxTxBuffers() */
#define DBG_DCM_RELEASERXTXBUFFERS_ENTRY(a)
#endif

#ifndef DBG_DCM_RELEASERXTXBUFFERS_EXIT
/** \brief Exit point of function Dcm_ReleaseRxTxBuffers() */
#define DBG_DCM_RELEASERXTXBUFFERS_EXIT(a)
#endif

#ifndef DBG_DCM_SENDRESPPENDINFIRSTCYCLE_ENTRY
/** \brief Entry point of function Dcm_SendRespPendInFirstCycle() */
#define DBG_DCM_SENDRESPPENDINFIRSTCYCLE_ENTRY(a)
#endif

#ifndef DBG_DCM_SENDRESPPENDINFIRSTCYCLE_EXIT
/** \brief Exit point of function Dcm_SendRespPendInFirstCycle() */
#define DBG_DCM_SENDRESPPENDINFIRSTCYCLE_EXIT(a,b)
#endif

#ifndef DBG_DCM_RESPPENDINFIRSTCYCLE_ENTRY
/** \brief Entry point of function Dcm_SendRespPendInFirstCycle() */
#define DBG_DCM_RESPPENDINFIRSTCYCLE_ENTRY(a)
#endif

#ifndef DBG_DCM_RESPPENDINFIRSTCYCLE_EXIT
/** \brief Exit point of function Dcm_SendRespPendInFirstCycle() */
#define DBG_DCM_RESPPENDINFIRSTCYCLE_EXIT(a)
#endif

#ifndef DBG_DCM_INTERNAL_TRIGGERPROCESSSERVICEASYNC_ENTRY
/** \brief Entry point of function Dcm_Internal_TriggerProcessServiceAsync() */
#define DBG_DCM_INTERNAL_TRIGGERPROCESSSERVICEASYNC_ENTRY()
#endif

#ifndef DBG_DCM_INTERNAL_TRIGGERPROCESSSERVICEASYNC_EXIT
/** \brief Exit point of function Dcm_Internal_TriggerProcessServiceAsync() */
#define DBG_DCM_INTERNAL_TRIGGERPROCESSSERVICEASYNC_EXIT()
#endif

#ifndef DBG_DCM_CHECKTXENBEMITEVT_ENTRY
/** \brief Entry point of function Dcm_CheckTxEnbEmitEvt() */
#define DBG_DCM_CHECKTXENBEMITEVT_ENTRY(a)
#endif

#ifndef DBG_DCM_CHECKTXENBEMITEVT_EXIT
/** \brief Exit point of function Dcm_CheckTxEnbEmitEvt() */
#define DBG_DCM_CHECKTXENBEMITEVT_EXIT(a)
#endif

#ifndef DBG_DCM_SUPPRESSRESPONSE_ENTRY
/** \brief Entry point of function Dcm_SuppressResponse() */
#define DBG_DCM_SUPPRESSRESPONSE_ENTRY(a)
#endif

#ifndef DBG_DCM_SUPPRESSRESPONSE_EXIT
/** \brief Exit point of function Dcm_SuppressResponse() */
#define DBG_DCM_SUPPRESSRESPONSE_EXIT(a)
#endif

#ifndef DBG_DCM_PAGEBUFFERINPROGRESS_ENTRY
/** \brief Entry point of function Dcm_PageBufferInProgress() */
#define DBG_DCM_PAGEBUFFERINPROGRESS_ENTRY(a)
#endif
 
#ifndef DBG_DCM_PAGEBUFFERINPROGRESS_EXIT
/** \brief Exit point of function Dcm_PageBufferInProgress() */
#define DBG_DCM_PAGEBUFFERINPROGRESS_EXIT(a, b)
#endif

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[external data]=========================================*/

#endif /* (!defined DCM_TRACE_H) */
/*==================[end of file]===========================================*/
