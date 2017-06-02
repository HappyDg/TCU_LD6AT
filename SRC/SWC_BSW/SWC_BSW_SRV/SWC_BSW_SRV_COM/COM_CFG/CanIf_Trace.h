/**
 * \file
 *
 * \brief AUTOSAR CanIf
 *
 * This file contains the implementation of the AUTOSAR
 * module CanIf.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#if (!defined CANIF_TRACE_H)
#define CANIF_TRACE_H
/*==================[inclusions]============================================*/




/*==================[macros]================================================*/

#ifndef DBG_CANIF_SENDTXCONFIRMATION_ENTRY
/** \brief Entry point of function CanIf_SendTxConfirmation() */
#define DBG_CANIF_SENDTXCONFIRMATION_ENTRY(a)
#endif

#ifndef DBG_CANIF_SENDTXCONFIRMATION_EXIT
/** \brief Exit point of function CanIf_SendTxConfirmation() */
#define DBG_CANIF_SENDTXCONFIRMATION_EXIT(a)
#endif

#ifndef DBG_CANIF_ISVALIDCONFIG_ENTRY
/** \brief Entry point of function CanIf_IsValidConfig() */
#define DBG_CANIF_ISVALIDCONFIG_ENTRY(a)
#endif

#ifndef DBG_CANIF_ISVALIDCONFIG_EXIT
/** \brief Exit point of function CanIf_IsValidConfig() */
#define DBG_CANIF_ISVALIDCONFIG_EXIT(a,b)
#endif

#ifndef DBG_CANIF_INIT_ENTRY
/** \brief Entry point of function CanIf_Init() */
#define DBG_CANIF_INIT_ENTRY(a)
#endif

#ifndef DBG_CANIF_CANCONTROLLERMODE_GRP
/** \brief Change of CanIf_CanControllerMode */
#define DBG_CANIF_CANCONTROLLERMODE_GRP(a,b,c)
#endif

#ifndef DBG_CANIF_CANCONTROLLERFLAGS_GRP
/** \brief Change of CanIf_CanControllerFlags */
#define DBG_CANIF_CANCONTROLLERFLAGS_GRP(a,b,c)
#endif

#ifndef DBG_CANIF_PDUMODE_GRP
/** \brief Change of CanIf_PduMode */
#define DBG_CANIF_PDUMODE_GRP(a,b,c)
#endif

#ifndef DBG_CANIF_STATE
/** \brief Change of CanIf_State */
#define DBG_CANIF_STATE(a,b)
#endif

#ifndef DBG_CANIF_INIT_EXIT
/** \brief Exit point of function CanIf_Init() */
#define DBG_CANIF_INIT_EXIT(a)
#endif

#ifndef DBG_CANIF_SETCONTROLLERMODE_ENTRY
/** \brief Entry point of function CanIf_SetControllerMode() */
#define DBG_CANIF_SETCONTROLLERMODE_ENTRY(a,b)
#endif

#ifndef DBG_CANIF_SETCONTROLLERMODE_EXIT
/** \brief Exit point of function CanIf_SetControllerMode() */
#define DBG_CANIF_SETCONTROLLERMODE_EXIT(a,b,c)
#endif

#ifndef DBG_CANIF_GETCONTROLLERMODE_ENTRY
/** \brief Entry point of function CanIf_GetControllerMode() */
#define DBG_CANIF_GETCONTROLLERMODE_ENTRY(a,b)
#endif

#ifndef DBG_CANIF_GETCONTROLLERMODE_EXIT
/** \brief Exit point of function CanIf_GetControllerMode() */
#define DBG_CANIF_GETCONTROLLERMODE_EXIT(a,b,c)
#endif

#ifndef DBG_CANIF_TRANSMIT_ENTRY
/** \brief Entry point of function CanIf_Transmit() */
#define DBG_CANIF_TRANSMIT_ENTRY(a,b)
#endif

#ifndef DBG_CANIF_TRANSMIT_EXIT
/** \brief Exit point of function CanIf_Transmit() */
#define DBG_CANIF_TRANSMIT_EXIT(a,b,c)
#endif

#ifndef DBG_CANIF_CANCELTRANSMIT_ENTRY
/** \brief Entry point of function CanIf_CancelTransmit() */
#define DBG_CANIF_CANCELTRANSMIT_ENTRY(a)
#endif

#ifndef DBG_CANIF_CANCELTRANSMIT_EXIT
/** \brief Exit point of function CanIf_CancelTransmit() */
#define DBG_CANIF_CANCELTRANSMIT_EXIT(a,b)
#endif

#ifndef DBG_CANIF_READRXPDUDATA_ENTRY
/** \brief Entry point of function CanIf_ReadRxPduData() */
#define DBG_CANIF_READRXPDUDATA_ENTRY(a,b)
#endif

#ifndef DBG_CANIF_READRXPDUDATA_EXIT
/** \brief Exit point of function CanIf_ReadRxPduData() */
#define DBG_CANIF_READRXPDUDATA_EXIT(a,b,c)
#endif

#ifndef DBG_CANIF_READTXNOTIFSTATUS_ENTRY
/** \brief Entry point of function CanIf_ReadTxNotifStatus() */
#define DBG_CANIF_READTXNOTIFSTATUS_ENTRY(a)
#endif

#ifndef DBG_CANIF_READTXNOTIFSTATUS_EXIT
/** \brief Exit point of function CanIf_ReadTxNotifStatus() */
#define DBG_CANIF_READTXNOTIFSTATUS_EXIT(a,b)
#endif

#ifndef DBG_CANIF_READRXNOTIFSTATUS_ENTRY
/** \brief Entry point of function CanIf_ReadRxNotifStatus() */
#define DBG_CANIF_READRXNOTIFSTATUS_ENTRY(a)
#endif

#ifndef DBG_CANIF_READRXNOTIFSTATUS_EXIT
/** \brief Exit point of function CanIf_ReadRxNotifStatus() */
#define DBG_CANIF_READRXNOTIFSTATUS_EXIT(a,b)
#endif

#ifndef DBG_CANIF_SETPDUMODE_ENTRY
/** \brief Entry point of function CanIf_SetPduMode() */
#define DBG_CANIF_SETPDUMODE_ENTRY(a,b)
#endif

#ifndef DBG_CANIF_SETPDUMODE_EXIT
/** \brief Exit point of function CanIf_SetPduMode() */
#define DBG_CANIF_SETPDUMODE_EXIT(a,b,c)
#endif

#ifndef DBG_CANIF_GETPDUMODE_ENTRY
/** \brief Entry point of function CanIf_GetPduMode() */
#define DBG_CANIF_GETPDUMODE_ENTRY(a,b)
#endif

#ifndef DBG_CANIF_GETPDUMODE_EXIT
/** \brief Exit point of function CanIf_GetPduMode() */
#define DBG_CANIF_GETPDUMODE_EXIT(a,b,c)
#endif

#ifndef DBG_CANIF_GETVERSIONINFO_ENTRY
/** \brief Entry point of function CanIf_GetVersionInfo() */
#define DBG_CANIF_GETVERSIONINFO_ENTRY(a)
#endif

#ifndef DBG_CANIF_GETVERSIONINFO_EXIT
/** \brief Exit point of function CanIf_GetVersionInfo() */
#define DBG_CANIF_GETVERSIONINFO_EXIT(a)
#endif

#ifndef DBG_CANIF_SETDYNAMICTXID_ENTRY
/** \brief Entry point of function CanIf_SetDynamicTxId() */
#define DBG_CANIF_SETDYNAMICTXID_ENTRY(a,b)
#endif

#ifndef DBG_CANIF_SETDYNAMICTXID_EXIT
/** \brief Exit point of function CanIf_SetDynamicTxId() */
#define DBG_CANIF_SETDYNAMICTXID_EXIT(a,b)
#endif

#ifndef DBG_CANIF_SETTRCVMODE_ENTRY
/** \brief Entry point of function CanIf_SetTrcvMode() */
#define DBG_CANIF_SETTRCVMODE_ENTRY(a,b)
#endif

#ifndef DBG_CANIF_SETTRCVMODE_EXIT
/** \brief Exit point of function CanIf_SetTrcvMode() */
#define DBG_CANIF_SETTRCVMODE_EXIT(a,b,c)
#endif

#ifndef DBG_CANIF_GETTRCVMODE_ENTRY
/** \brief Entry point of function CanIf_GetTrcvMode() */
#define DBG_CANIF_GETTRCVMODE_ENTRY(a,b)
#endif

#ifndef DBG_CANIF_GETTRCVMODE_EXIT
/** \brief Exit point of function CanIf_GetTrcvMode() */
#define DBG_CANIF_GETTRCVMODE_EXIT(a,b,c)
#endif

#ifndef DBG_CANIF_GETTRCVWAKEUPREASON_ENTRY
/** \brief Entry point of function CanIf_GetTrcvWakeupReason() */
#define DBG_CANIF_GETTRCVWAKEUPREASON_ENTRY(a,b)
#endif

#ifndef DBG_CANIF_GETTRCVWAKEUPREASON_EXIT
/** \brief Exit point of function CanIf_GetTrcvWakeupReason() */
#define DBG_CANIF_GETTRCVWAKEUPREASON_EXIT(a,b,c)
#endif

#ifndef DBG_CANIF_SETTRCVWAKEUPMODE_ENTRY
/** \brief Entry point of function CanIf_SetTrcvWakeupMode() */
#define DBG_CANIF_SETTRCVWAKEUPMODE_ENTRY(a,b)
#endif

#ifndef DBG_CANIF_SETTRCVWAKEUPMODE_EXIT
/** \brief Exit point of function CanIf_SetTrcvWakeupMode() */
#define DBG_CANIF_SETTRCVWAKEUPMODE_EXIT(a,b,c)
#endif

#ifndef DBG_CANIF_CHECKWAKEUP_ENTRY
/** \brief Entry point of function CanIf_CheckWakeup() */
#define DBG_CANIF_CHECKWAKEUP_ENTRY(a)
#endif

#ifndef DBG_CANIF_CHECKWAKEUP_EXIT
/** \brief Exit point of function CanIf_CheckWakeup() */
#define DBG_CANIF_CHECKWAKEUP_EXIT(a,b)
#endif

#ifndef DBG_CANIF_CHECKVALIDATION_ENTRY
/** \brief Entry point of function CanIf_CheckValidation() */
#define DBG_CANIF_CHECKVALIDATION_ENTRY(a)
#endif

#ifndef DBG_CANIF_CHECKVALIDATION_EXIT
/** \brief Exit point of function CanIf_CheckValidation() */
#define DBG_CANIF_CHECKVALIDATION_EXIT(a,b)
#endif

#ifndef DBG_CANIF_GETTXCONFIRMATIONSTATE_ENTRY
/** \brief Entry point of function CanIf_GetTxConfirmationState() */
#define DBG_CANIF_GETTXCONFIRMATIONSTATE_ENTRY(a)
#endif

#ifndef DBG_CANIF_GETTXCONFIRMATIONSTATE_EXIT
/** \brief Exit point of function CanIf_GetTxConfirmationState() */
#define DBG_CANIF_GETTXCONFIRMATIONSTATE_EXIT(a,b)
#endif

#ifndef DBG_CANIF_CLEARTRCVWUFFLAG_ENTRY
/** \brief Entry point of function CanIf_ClearTrcvWufFlag() */
#define DBG_CANIF_CLEARTRCVWUFFLAG_ENTRY(a)
#endif

#ifndef DBG_CANIF_CLEARTRCVWUFFLAG_EXIT
/** \brief Exit point of function CanIf_ClearTrcvWufFlag() */
#define DBG_CANIF_CLEARTRCVWUFFLAG_EXIT(a,b)
#endif

#ifndef DBG_CANIF_CHECKTRCVWAKEFLAG_ENTRY
/** \brief Entry point of function CanIf_CheckTrcvWakeFlag() */
#define DBG_CANIF_CHECKTRCVWAKEFLAG_ENTRY(a)
#endif

#ifndef DBG_CANIF_CHECKTRCVWAKEFLAG_EXIT
/** \brief Exit point of function CanIf_CheckTrcvWakeFlag() */
#define DBG_CANIF_CHECKTRCVWAKEFLAG_EXIT(a,b)
#endif

#ifndef DBG_CANIF_TXCONFIRMATION_ENTRY
/** \brief Entry point of function CanIf_TxConfirmation() */
#define DBG_CANIF_TXCONFIRMATION_ENTRY(a)
#endif

#ifndef DBG_CANIF_TXCONFIRMATION_EXIT
/** \brief Exit point of function CanIf_TxConfirmation() */
#define DBG_CANIF_TXCONFIRMATION_EXIT(a)
#endif

#ifndef DBG_CANIF_RXINDICATION_ENTRY
/** \brief Entry point of function CanIf_RxIndication() */
#define DBG_CANIF_RXINDICATION_ENTRY(a,b,c,d)
#endif

#ifndef DBG_CANIF_RXINDICATION_EXIT
/** \brief Exit point of function CanIf_RxIndication() */
#define DBG_CANIF_RXINDICATION_EXIT(a,b,c,d)
#endif

  #ifndef DBG_CANIF_CANCELTXCONFIRMATION_ENTRY
/** \brief Entry point of function CanIf_CancelTxConfirmation() */
#define DBG_CANIF_CANCELTXCONFIRMATION_ENTRY(a, b)
#endif

#ifndef DBG_CANIF_CANCELTXCONFIRMATION_EXIT
/** \brief Exit point of function CanIf_CancelTxConfirmation() */
#define DBG_CANIF_CANCELTXCONFIRMATION_EXIT(a, b)
#endif

#ifndef DBG_CANIF_CONTROLLERBUSOFF_ENTRY
/** \brief Entry point of function CanIf_ControllerBusOff() */
#define DBG_CANIF_CONTROLLERBUSOFF_ENTRY(a)
#endif

#ifndef DBG_CANIF_CONTROLLERBUSOFF_EXIT
/** \brief Exit point of function CanIf_ControllerBusOff() */
#define DBG_CANIF_CONTROLLERBUSOFF_EXIT(a)
#endif

#ifndef DBG_CANIF_CONTROLLERMODEINDICATION_ENTRY
/** \brief Entry point of function CanIf_ControllerModeIndication() */
#define DBG_CANIF_CONTROLLERMODEINDICATION_ENTRY(a,b)
#endif

#ifndef DBG_CANIF_CONTROLLERMODEINDICATION_EXIT
/** \brief Exit point of function CanIf_ControllerModeIndication() */
#define DBG_CANIF_CONTROLLERMODEINDICATION_EXIT(a,b)
#endif

#ifndef DBG_CANIF_TRCVMODEINDICATION_ENTRY
/** \brief Entry point of function CanIf_TrcvModeIndication() */
#define DBG_CANIF_TRCVMODEINDICATION_ENTRY(a,b)
#endif

#ifndef DBG_CANIF_TRCVMODEINDICATION_EXIT
/** \brief Exit point of function CanIf_TrcvModeIndication() */
#define DBG_CANIF_TRCVMODEINDICATION_EXIT(a,b)
#endif

#ifndef DBG_CANIF_CONFIRMPNAVAILABILITY_ENTRY
/** \brief Entry point of function CanIf_ConfirmPnAvailability() */
#define DBG_CANIF_CONFIRMPNAVAILABILITY_ENTRY(a)
#endif

#ifndef DBG_CANIF_CONFIRMPNAVAILABILITY_EXIT
/** \brief Exit point of function CanIf_ConfirmPnAvailability() */
#define DBG_CANIF_CONFIRMPNAVAILABILITY_EXIT(a)
#endif

#ifndef DBG_CANIF_CLEARTRCVWUFFLAGINDICATION_ENTRY
/** \brief Entry point of function CanIf_ClearTrcvWufFlagIndication() */
#define DBG_CANIF_CLEARTRCVWUFFLAGINDICATION_ENTRY(a)
#endif

#ifndef DBG_CANIF_CLEARTRCVWUFFLAGINDICATION_EXIT
/** \brief Exit point of function CanIf_ClearTrcvWufFlagIndication() */
#define DBG_CANIF_CLEARTRCVWUFFLAGINDICATION_EXIT(a)
#endif

#ifndef DBG_CANIF_CHECKTRCVWAKEFLAGINDICATION_ENTRY
/** \brief Entry point of function CanIf_CheckTrcvWakeFlagIndication() */
#define DBG_CANIF_CHECKTRCVWAKEFLAGINDICATION_ENTRY(a)
#endif

#ifndef DBG_CANIF_CHECKTRCVWAKEFLAGINDICATION_EXIT
/** \brief Exit point of function CanIf_CheckTrcvWakeFlagIndication() */
#define DBG_CANIF_CHECKTRCVWAKEFLAGINDICATION_EXIT(a)
#endif

#ifndef DBG_CANIF_GETCANIFIDFROMCTRLIDX_ENTRY
/** \brief Entry point of function CanIf_GetCanIfIdFromCtrlIdx() */
#define DBG_CANIF_GETCANIFIDFROMCTRLIDX_ENTRY(a)
#endif

#ifndef DBG_CANIF_GETCANIFIDFROMCTRLIDX_EXIT
/** \brief Exit point of function CanIf_GetCanIfIdFromCtrlIdx() */
#define DBG_CANIF_GETCANIFIDFROMCTRLIDX_EXIT(a,b)
#endif

#ifndef DBG_CANIF_SETCONTROLLERMODEINTERNAL_ENTRY
/** \brief Entry point of function CanIf_SetControllerModeInternal() */
#define DBG_CANIF_SETCONTROLLERMODEINTERNAL_ENTRY(a,b)
#endif

#ifndef DBG_CANIF_SETCONTROLLERMODEINTERNAL_EXIT
/** \brief Exit point of function CanIf_SetControllerModeInternal() */
#define DBG_CANIF_SETCONTROLLERMODEINTERNAL_EXIT(a,b,c)
#endif

#ifndef DBG_CANIF_BUFFERMESSAGE_ENTRY
/** \brief Entry point of function CanIf_BufferMessage() */
#define DBG_CANIF_BUFFERMESSAGE_ENTRY(a,b,c)
#endif

#ifndef DBG_CANIF_BUFFERMESSAGE_EXIT
/** \brief Exit point of function CanIf_BufferMessage() */
#define DBG_CANIF_BUFFERMESSAGE_EXIT(a,b,c,d)
#endif

#ifndef DBG_CANIF_SETPDUMODEINTERNAL_ENTRY
/** \brief Entry point of function CanIf_SetPduModeInternal() */
#define DBG_CANIF_SETPDUMODEINTERNAL_ENTRY(a,b)
#endif

#ifndef DBG_CANIF_SETPDUMODEINTERNAL_EXIT
/** \brief Exit point of function CanIf_SetPduModeInternal() */
#define DBG_CANIF_SETPDUMODEINTERNAL_EXIT(a,b,c)
#endif

#ifndef DBG_CANIF_SETRXOFFLINE_ENTRY
/** \brief Entry point of function CanIf_SetRxOffline() */
#define DBG_CANIF_SETRXOFFLINE_ENTRY(a,b)
#endif

#ifndef DBG_CANIF_SETRXOFFLINE_EXIT
/** \brief Exit point of function CanIf_SetRxOffline() */
#define DBG_CANIF_SETRXOFFLINE_EXIT(a,b)
#endif

#ifndef DBG_CANIF_SETRXONLINE_ENTRY
/** \brief Entry point of function CanIf_SetRxOnline() */
#define DBG_CANIF_SETRXONLINE_ENTRY(a,b)
#endif

#ifndef DBG_CANIF_SETRXONLINE_EXIT
/** \brief Exit point of function CanIf_SetRxOnline() */
#define DBG_CANIF_SETRXONLINE_EXIT(a,b)
#endif

#ifndef DBG_CANIF_SETTXOFFLINE_ENTRY
/** \brief Entry point of function CanIf_SetTxOffline() */
#define DBG_CANIF_SETTXOFFLINE_ENTRY(a,b)
#endif

#ifndef DBG_CANIF_SETTXOFFLINE_EXIT
/** \brief Exit point of function CanIf_SetTxOffline() */
#define DBG_CANIF_SETTXOFFLINE_EXIT(a,b)
#endif

#ifndef DBG_CANIF_SETTXONLINE_ENTRY
/** \brief Entry point of function CanIf_SetTxOnline() */
#define DBG_CANIF_SETTXONLINE_ENTRY(a,b)
#endif

#ifndef DBG_CANIF_SETTXONLINE_EXIT
/** \brief Exit point of function CanIf_SetTxOnline() */
#define DBG_CANIF_SETTXONLINE_EXIT(a,b)
#endif

#ifndef DBG_CANIF_SETTXOFFLINEACTIVE_ENTRY
/** \brief Entry point of function CanIf_SetTxOfflineActive() */
#define DBG_CANIF_SETTXOFFLINEACTIVE_ENTRY(a,b)
#endif

#ifndef DBG_CANIF_SETTXOFFLINEACTIVE_EXIT
/** \brief Exit point of function CanIf_SetTxOfflineActive() */
#define DBG_CANIF_SETTXOFFLINEACTIVE_EXIT(a,b)
#endif

  #ifndef DBG_CANIF_SETOFFLINE_ENTRY
/** \brief Entry point of function CanIf_SetOffline() */
#define DBG_CANIF_SETOFFLINE_ENTRY(a, b)
#endif

#ifndef DBG_CANIF_SETOFFLINE_EXIT
/** \brief Exit point of function CanIf_SetOffline() */
#define DBG_CANIF_SETOFFLINE_EXIT(a, b)
#endif

#ifndef DBG_CANIF_WRITERXBUFFER_ENTRY
/** \brief Entry point of function CanIf_WriteRxBuffer() */
#define DBG_CANIF_WRITERXBUFFER_ENTRY(a,b)
#endif

#ifndef DBG_CANIF_WRITERXBUFFER_EXIT
/** \brief Exit point of function CanIf_WriteRxBuffer() */
#define DBG_CANIF_WRITERXBUFFER_EXIT(a,b)
#endif

#ifndef DBG_CANIF_SOFTWAREFILTERING_ENTRY
/** \brief Entry point of function CanIf_SoftwareFiltering() */
#define DBG_CANIF_SOFTWAREFILTERING_ENTRY(a,b,c)
#endif

#ifndef DBG_CANIF_SOFTWAREFILTERING_EXIT
/** \brief Exit point of function CanIf_SoftwareFiltering() */
#define DBG_CANIF_SOFTWAREFILTERING_EXIT(a,b,c,d)
#endif

#ifndef DBG_CANIF_BINARYSWFILTERING_ENTRY
/** \brief Entry point of function CanIf_BinarySwFiltering() */
#define DBG_CANIF_BINARYSWFILTERING_ENTRY(a,b,c,d)
#endif

#ifndef DBG_CANIF_BINARYSWFILTERING_EXIT
/** \brief Exit point of function CanIf_BinarySwFiltering() */
#define DBG_CANIF_BINARYSWFILTERING_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_CANIF_RXINDICATION_DETCHECKS_ENTRY
/** \brief Entry point of function CanIf_RxIndication_DetChecks() */
#define DBG_CANIF_RXINDICATION_DETCHECKS_ENTRY(a,b,c,d)
#endif

#ifndef DBG_CANIF_RXINDICATION_DETCHECKS_EXIT
/** \brief Exit point of function CanIf_RxIndication_DetChecks() */
#define DBG_CANIF_RXINDICATION_DETCHECKS_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_CANIF_DLCHANDLING_ENTRY
/** \brief Entry point of function CanIf_DlcHandling() */
#define DBG_CANIF_DLCHANDLING_ENTRY(a,b,c)
#endif

#ifndef DBG_CANIF_DLCHANDLING_EXIT
/** \brief Exit point of function CanIf_DlcHandling() */
#define DBG_CANIF_DLCHANDLING_EXIT(a,b,c,d)
#endif

#ifndef DBG_CANIF_FREECONTROLLERTXBUFFERS_ENTRY
/** \brief Entry point of function CanIf_FreeControllerTxBuffers() */
#define DBG_CANIF_FREECONTROLLERTXBUFFERS_ENTRY(a)
#endif

#ifndef DBG_CANIF_FREECONTROLLERTXBUFFERS_EXIT
/** \brief Exit point of function CanIf_FreeControllerTxBuffers() */
#define DBG_CANIF_FREECONTROLLERTXBUFFERS_EXIT(a)
#endif

#ifndef DBG_CANIF_ADDPENDINGTXREQUEST_ENTRY
/** \brief Entry point of function CanIf_AddPendingTxRequest() */
#define DBG_CANIF_ADDPENDINGTXREQUEST_ENTRY(a,b)
#endif

#ifndef DBG_CANIF_ADDPENDINGTXREQUEST_EXIT
/** \brief Exit point of function CanIf_AddPendingTxRequest() */
#define DBG_CANIF_ADDPENDINGTXREQUEST_EXIT(a,b)
#endif

#ifndef DBG_CANIF_SENDNEXTTXREQUEST_ENTRY
/** \brief Entry point of function CanIf_SendNextTxRequest() */
#define DBG_CANIF_SENDNEXTTXREQUEST_ENTRY(a)
#endif

#ifndef DBG_CANIF_SENDNEXTTXREQUEST_EXIT
/** \brief Exit point of function CanIf_SendNextTxRequest() */
#define DBG_CANIF_SENDNEXTTXREQUEST_EXIT(a)
#endif

#ifndef DBG_CANIF_CLEARHTHTXREQUESTS_ENTRY
/** \brief Entry point of function CanIf_ClearHthTxRequests() */
#define DBG_CANIF_CLEARHTHTXREQUESTS_ENTRY(a)
#endif

#ifndef DBG_CANIF_CLEARHTHTXREQUESTS_EXIT
/** \brief Exit point of function CanIf_ClearHthTxRequests() */
#define DBG_CANIF_CLEARHTHTXREQUESTS_EXIT(a)
#endif

#ifndef DBG_CANIF_SENDRXINDICATION_ENTRY
/** \brief Entry point of function CanIf_SendRxIndication() */
#define DBG_CANIF_SENDRXINDICATION_ENTRY(a,b,c,d)
#endif

#ifndef DBG_CANIF_SENDRXINDICATION_EXIT
/** \brief Exit point of function CanIf_SendRxIndication() */
#define DBG_CANIF_SENDRXINDICATION_EXIT(a,b,c,d)
#endif


/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[external data]=========================================*/

#endif /* (!defined CANIF_TRACE_H) */
/*==================[end of file]===========================================*/
