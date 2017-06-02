/**
 * \file
 *
 * \brief AUTOSAR CanTp
 *
 * This file contains the implementation of the AUTOSAR
 * module CanTp.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#if(!defined CANTP_TRACE_H)
#define CANTP_TRACE_H
/*==================[inclusions]============================================*/



/*==================[macros]================================================*/

/* This macro is used to compute the channel index in functions
 * where there is only a pointer available to a structure from
 * the CanTp_Channel variable.
 * According to rule MISRA rule 17.2, this is perfectly valid, as
 * both used pointers point to locations from the same array.
 */
#ifndef DBG_CANTP_GET_CHANNEL_INDEX
#define DBG_CANTP_GET_CHANNEL_INDEX(ChannelPtr) ((ChannelPtr) - (CanTp_Channel))
#endif

#ifndef DBG_CANTP_INITVARS_STATE
/** \brief State tracing macro for CanTp_InitVars.State */
#define DBG_CANTP_INITVARS_STATE(a,b)
#endif

#ifndef DBG_CANTP_CHANNEL_STATE_GRP
/** \brief State tracing macro for CanTp_Channel[].State */
#define DBG_CANTP_CHANNEL_STATE_GRP(a,b,c)
#endif

#ifndef DBG_CANTP_CANCELRECEIVE_ENTRY
/** \brief Entry point of function CanTp_CancelReceive() */
#define DBG_CANTP_CANCELRECEIVE_ENTRY(a)
#endif

#ifndef DBG_CANTP_CANCELRECEIVE_EXIT
/** \brief Exit point of function CanTp_CancelReceive() */
#define DBG_CANTP_CANCELRECEIVE_EXIT(a,b)
#endif

#ifndef DBG_CANTP_CANCELTRANSMIT_ENTRY
/** \brief Entry point of function CanTp_CancelTransmit() */
#define DBG_CANTP_CANCELTRANSMIT_ENTRY(a)
#endif

#ifndef DBG_CANTP_CANCELTRANSMIT_EXIT
/** \brief Exit point of function CanTp_CancelTransmit() */
#define DBG_CANTP_CANCELTRANSMIT_EXIT(a,b)
#endif

#ifndef DBG_CANTP_CHANGEPARAMETER_ENTRY
/** \brief Entry point of function CanTp_ChangeParameter() */
#define DBG_CANTP_CHANGEPARAMETER_ENTRY(a,b,c)
#endif

#ifndef DBG_CANTP_CHANGEPARAMETER_EXIT
/** \brief Exit point of function CanTp_ChangeParameter() */
#define DBG_CANTP_CHANGEPARAMETER_EXIT(a,b,c,d)
#endif

#ifndef DBG_CANTP_GETNSA_ENTRY
/** \brief Entry point of function CanTp_GetNSa() */
#define DBG_CANTP_GETNSA_ENTRY(a,b,c)
#endif

#ifndef DBG_CANTP_GETNSA_EXIT
/** \brief Exit point of function CanTp_GetNSa() */
#define DBG_CANTP_GETNSA_EXIT(a,b,c,d)
#endif

#ifndef DBG_CANTP_GETVERSIONINFO_ENTRY
/** \brief Entry point of function CanTp_GetVersionInfo() */
#define DBG_CANTP_GETVERSIONINFO_ENTRY(a)
#endif

#ifndef DBG_CANTP_GETVERSIONINFO_EXIT
/** \brief Exit point of function CanTp_GetVersionInfo() */
#define DBG_CANTP_GETVERSIONINFO_EXIT(a)
#endif

#ifndef DBG_CANTP_ISVALIDCONFIG_ENTRY
/** \brief Entry point of function CanTp_IsValidConfig() */
#define DBG_CANTP_ISVALIDCONFIG_ENTRY(a)
#endif

#ifndef DBG_CANTP_ISVALIDCONFIG_EXIT
/** \brief Exit point of function CanTp_IsValidConfig() */
#define DBG_CANTP_ISVALIDCONFIG_EXIT(a,b)
#endif

#ifndef DBG_CANTP_INIT_ENTRY
/** \brief Entry point of function CanTp_Init() */
#define DBG_CANTP_INIT_ENTRY(a)
#endif

#ifndef DBG_CANTP_INIT_EXIT
/** \brief Exit point of function CanTp_Init() */
#define DBG_CANTP_INIT_EXIT(a)
#endif

#ifndef DBG_CANTP_MAINFUNCTION_ENTRY
/** \brief Entry point of function CanTp_MainFunction() */
#define DBG_CANTP_MAINFUNCTION_ENTRY()
#endif

#ifndef DBG_CANTP_MAINFUNCTION_EXIT
/** \brief Exit point of function CanTp_MainFunction() */
#define DBG_CANTP_MAINFUNCTION_EXIT()
#endif

#ifndef DBG_CANTP_RXINDICATION_ENTRY
/** \brief Entry point of function CanTp_RxIndication() */
#define DBG_CANTP_RXINDICATION_ENTRY(a,b)
#endif

#ifndef DBG_CANTP_RXINDICATION_EXIT
/** \brief Exit point of function CanTp_RxIndication() */
#define DBG_CANTP_RXINDICATION_EXIT(a,b)
#endif

#ifndef DBG_CANTP_SETNSA_ENTRY
/** \brief Entry point of function CanTp_SetNSa() */
#define DBG_CANTP_SETNSA_ENTRY(a,b,c)
#endif

#ifndef DBG_CANTP_SETNSA_EXIT
/** \brief Exit point of function CanTp_SetNSa() */
#define DBG_CANTP_SETNSA_EXIT(a,b,c,d)
#endif

#ifndef DBG_CANTP_TRANSMIT_ENTRY
/** \brief Entry point of function CanTp_Transmit() */
#define DBG_CANTP_TRANSMIT_ENTRY(a,b)
#endif

#ifndef DBG_CANTP_TRANSMIT_EXIT
/** \brief Exit point of function CanTp_Transmit() */
#define DBG_CANTP_TRANSMIT_EXIT(a,b,c)
#endif

#ifndef DBG_CANTP_TXCONFIRMATION_ENTRY
/** \brief Entry point of function CanTp_TxConfirmation() */
#define DBG_CANTP_TXCONFIRMATION_ENTRY(a)
#endif

#ifndef DBG_CANTP_TXCONFIRMATION_EXIT
/** \brief Exit point of function CanTp_TxConfirmation() */
#define DBG_CANTP_TXCONFIRMATION_EXIT(a)
#endif

#ifndef DBG_CANTP_POSTRXINDICATION_ENTRY
/** \brief Entry point of function CanTp_PostRxIndication */
#define DBG_CANTP_POSTRXINDICATION_ENTRY(a)
#endif

#ifndef DBG_CANTP_POSTRXINDICATION_EXIT
/** \brief Exit point of function CanTp_PostRxIndication */
#define DBG_CANTP_POSTRXINDICATION_EXIT(a)
#endif

#ifndef DBG_CANTP_POSTPONERXFRAME_ENTRY
/** \brief Entry point of function CanTp_PostponeRxFrame */
#define DBG_CANTP_POSTPONERXFRAME_ENTRY(a,b,c,d)
#endif

#ifndef DBG_CANTP_POSTPONERXFRAME_EXIT
/** \brief Exit point of function CanTp_PostponeRxFrame */
#define DBG_CANTP_POSTPONERXFRAME_EXIT(a,b,c,d)
#endif

#ifndef DBG_CANTP_PROCESSRXFRAME_ENTRY
/** \brief Entry point of function CanTp_ProcessRxFrame */
#define DBG_CANTP_PROCESSRXFRAME_ENTRY(a,b,c,d)
#endif

#ifndef DBG_CANTP_PROCESSRXFRAME_EXIT
/** \brief Exit point of function CanTp_ProcessRxFrame */
#define DBG_CANTP_PROCESSRXFRAME_EXIT(a,b,c,d)
#endif

#ifndef DBG_CANTP_RXCHANNELCLEANUP_ENTRY
/** \brief Entry point of function CanTp_RxChannelCleanup */
#define DBG_CANTP_RXCHANNELCLEANUP_ENTRY(a)
#endif

#ifndef DBG_CANTP_RXCHANNELCLEANUP_EXIT
/** \brief Exit point of function CanTp_RxChannelCleanup */
#define DBG_CANTP_RXCHANNELCLEANUP_EXIT(a)
#endif

#ifndef DBG_CANTP_FINDNSDUID_ENTRY
/** \brief Entry point of function CanTp_FindNSduId */
#define DBG_CANTP_FINDNSDUID_ENTRY(a,b,c,d)
#endif

#ifndef DBG_CANTP_FINDNSDUID_EXIT
/** \brief Exit point of function CanTp_FindNSduId */
#define DBG_CANTP_FINDNSDUID_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_CANTP_PROCESSRECEIVEDSF_ENTRY
/** \brief Entry point of function CanTp_ProcessReceivedSF */
#define DBG_CANTP_PROCESSRECEIVEDSF_ENTRY(a,b)
#endif

#ifndef DBG_CANTP_PROCESSRECEIVEDSF_EXIT
/** \brief Exit point of function CanTp_ProcessReceivedSF */
#define DBG_CANTP_PROCESSRECEIVEDSF_EXIT(a,b)
#endif

#ifndef DBG_CANTP_PROCESSRECEIVEDFF_ENTRY
/** \brief Entry point of function CanTp_ProcessReceivedFF */
#define DBG_CANTP_PROCESSRECEIVEDFF_ENTRY(a,b)
#endif

#ifndef DBG_CANTP_PROCESSRECEIVEDFF_EXIT
/** \brief Exit point of function CanTp_ProcessReceivedFF */
#define DBG_CANTP_PROCESSRECEIVEDFF_EXIT(a,b)
#endif

#ifndef DBG_CANTP_PROCESSRECEIVEDCF_ENTRY
/** \brief Entry point of function CanTp_ProcessReceivedCF */
#define DBG_CANTP_PROCESSRECEIVEDCF_ENTRY(a,b)
#endif

#ifndef DBG_CANTP_PROCESSRECEIVEDCF_EXIT
/** \brief Exit point of function CanTp_ProcessReceivedCF */
#define DBG_CANTP_PROCESSRECEIVEDCF_EXIT(a,b)
#endif

#ifndef DBG_CANTP_PROCESSRECEIVEDINTERMEDIATECF_ENTRY
/** \brief Entry point of function CanTp_ProcessReceivedIntermediateCF */
#define DBG_CANTP_PROCESSRECEIVEDINTERMEDIATECF_ENTRY(a,b)
#endif

#ifndef DBG_CANTP_PROCESSRECEIVEDINTERMEDIATECF_EXIT
/** \brief Exit point of function CanTp_ProcessReceivedIntermediateCF */
#define DBG_CANTP_PROCESSRECEIVEDINTERMEDIATECF_EXIT(a,b)
#endif

#ifndef DBG_CANTP_PROCESSRECEIVEDLASTCF_ENTRY
/** \brief Entry point of function CanTp_ProcessReceivedLastCF */
#define DBG_CANTP_PROCESSRECEIVEDLASTCF_ENTRY(a,b,c)
#endif

#ifndef DBG_CANTP_PROCESSRECEIVEDLASTCF_EXIT
/** \brief Exit point of function CanTp_ProcessReceivedLastCF */
#define DBG_CANTP_PROCESSRECEIVEDLASTCF_EXIT(a,b,c)
#endif

#ifndef DBG_CANTP_PROCESSRECEIVEDFC_ENTRY
/** \brief Entry point of function CanTp_ProcessReceivedFC */
#define DBG_CANTP_PROCESSRECEIVEDFC_ENTRY(a,b)
#endif

#ifndef DBG_CANTP_PROCESSRECEIVEDFC_EXIT
/** \brief Exit point of function CanTp_ProcessReceivedFC */
#define DBG_CANTP_PROCESSRECEIVEDFC_EXIT(a,b)
#endif

#ifndef DBG_CANTP_PROCESSSTARTOFRECEPTION_ENTRY
/** \brief Entry point of function CanTp_ProcessStartOfReception */
#define DBG_CANTP_PROCESSSTARTOFRECEPTION_ENTRY(a)
#endif

#ifndef DBG_CANTP_PROCESSSTARTOFRECEPTION_EXIT
/** \brief Exit point of function CanTp_ProcessStartOfReception */
#define DBG_CANTP_PROCESSSTARTOFRECEPTION_EXIT(a,b)
#endif

#ifndef DBG_CANTP_PROCESSSTARTOFRECEPTIONDATA_ENTRY
/** \brief Entry point of function CanTp_ProcessStartOfReceptionData */
#define DBG_CANTP_PROCESSSTARTOFRECEPTIONDATA_ENTRY(a,b,c)
#endif

#ifndef DBG_CANTP_PROCESSSTARTOFRECEPTIONDATA_EXIT
/** \brief Exit point of function CanTp_ProcessStartOfReceptionData */
#define DBG_CANTP_PROCESSSTARTOFRECEPTIONDATA_EXIT(a,b,c,d)
#endif

#ifndef DBG_CANTP_RXPROCESSDATA_ENTRY
/** \brief Entry point of function CanTp_RxProcessData */
#define DBG_CANTP_RXPROCESSDATA_ENTRY(a,b,c)
#endif

#ifndef DBG_CANTP_RXPROCESSDATA_EXIT
/** \brief Exit point of function CanTp_RxProcessData */
#define DBG_CANTP_RXPROCESSDATA_EXIT(a,b,c,d)
#endif

#ifndef DBG_CANTP_RXSTATEHANDLING_ENTRY
/** \brief Entry point of function CanTp_RxStateHandling */
#define DBG_CANTP_RXSTATEHANDLING_ENTRY(a)
#endif

#ifndef DBG_CANTP_RXSTATEHANDLING_EXIT
/** \brief Exit point of function CanTp_RxStateHandling */
#define DBG_CANTP_RXSTATEHANDLING_EXIT(a)
#endif

#ifndef DBG_CANTP_POSTTXCONFIRMATION_ENTRY
/** \brief Entry point of function CanTp_PostTxConfirmation */
#define DBG_CANTP_POSTTXCONFIRMATION_ENTRY(a)
#endif

#ifndef DBG_CANTP_POSTTXCONFIRMATION_EXIT
/** \brief Exit point of function CanTp_PostTxConfirmation */
#define DBG_CANTP_POSTTXCONFIRMATION_EXIT(a)
#endif

#ifndef DBG_CANTP_PROCESSTXPDU_ENTRY
/** \brief Entry point of function CanTp_ProcessTxPdu */
#define DBG_CANTP_PROCESSTXPDU_ENTRY(a,b)
#endif

#ifndef DBG_CANTP_PROCESSTXPDU_EXIT
/** \brief Exit point of function CanTp_ProcessTxPdu */
#define DBG_CANTP_PROCESSTXPDU_EXIT(a,b)
#endif

#ifndef DBG_CANTP_GETTXPDUCHANNEL_ENTRY
/** \brief Entry point of function CanTp_GetTxPduChannel */
#define DBG_CANTP_GETTXPDUCHANNEL_ENTRY(a,b)
#endif

#ifndef DBG_CANTP_GETTXPDUCHANNEL_EXIT
/** \brief Exit point of function CanTp_GetTxPduChannel */
#define DBG_CANTP_GETTXPDUCHANNEL_EXIT(a,b,c)
#endif

#ifndef DBG_CANTP_PROCESSCONFIRMEDCF_ENTRY
/** \brief Entry point of function CanTp_ProcessConfirmedCF */
#define DBG_CANTP_PROCESSCONFIRMEDCF_ENTRY(a)
#endif

#ifndef DBG_CANTP_PROCESSCONFIRMEDCF_EXIT
/** \brief Exit point of function CanTp_ProcessConfirmedCF */
#define DBG_CANTP_PROCESSCONFIRMEDCF_EXIT(a)
#endif

#ifndef DBG_CANTP_UNLOCKCHANNEL_ENTRY
/** \brief Entry point of function CanTp_UnlockChannel */
#define DBG_CANTP_UNLOCKCHANNEL_ENTRY(a)
#endif

#ifndef DBG_CANTP_UNLOCKCHANNEL_EXIT
/** \brief Exit point of function CanTp_UnlockChannel */
#define DBG_CANTP_UNLOCKCHANNEL_EXIT(a)
#endif

#ifndef DBG_CANTP_TXSTATEHANDLING_ENTRY
/** \brief Entry point of function CanTp_TxStateHandling */
#define DBG_CANTP_TXSTATEHANDLING_ENTRY(a)
#endif

#ifndef DBG_CANTP_TXSTATEHANDLING_EXIT
/** \brief Exit point of function CanTp_TxStateHandling */
#define DBG_CANTP_TXSTATEHANDLING_EXIT(a)
#endif

#ifndef DBG_CANTP_TRANSMITFRAME_ENTRY
/** \brief Entry point of function CanTp_TransmitFrame */
#define DBG_CANTP_TRANSMITFRAME_ENTRY(a)
#endif

#ifndef DBG_CANTP_TRANSMITFRAME_EXIT
/** \brief Exit point of function CanTp_TransmitFrame */
#define DBG_CANTP_TRANSMITFRAME_EXIT(a)
#endif

#ifndef DBG_CANTP_STOPCHANNEL_ENTRY
/** \brief Entry point of function CanTp_StopChannel */
#define DBG_CANTP_STOPCHANNEL_ENTRY(a,b,c)
#endif

#ifndef DBG_CANTP_STOPCHANNEL_EXIT
/** \brief Exit point of function CanTp_StopChannel */
#define DBG_CANTP_STOPCHANNEL_EXIT(a,b,c)
#endif

#ifndef DBG_CANTP_STMINCALLBACK_ENTRY
/** \brief Entry point of function CanTp_STminCallback */
#define DBG_CANTP_STMINCALLBACK_ENTRY(a)
#endif

#ifndef DBG_CANTP_STMINCALLBACK_EXIT
/** \brief Exit point of function CanTp_STminCallback */
#define DBG_CANTP_STMINCALLBACK_EXIT(a)
#endif

#ifndef DBG_CANTP_POSTSTMINCALLBACK_ENTRY
/** \brief Entry point of function CanTp_PostSTminCallback */
#define DBG_CANTP_POSTSTMINCALLBACK_ENTRY(a)
#endif

#ifndef DBG_CANTP_POSTSTMINCALLBACK_EXIT
/** \brief Exit point of function CanTp_PostSTminCallback */
#define DBG_CANTP_POSTSTMINCALLBACK_EXIT(a)
#endif

#ifndef DBG_CANTP_STMINTIMEOUTHANDLING_ENTRY
/** \brief Entry point of function CanTp_STminTimeoutHandling */
#define DBG_CANTP_STMINTIMEOUTHANDLING_ENTRY(a)
#endif

#ifndef DBG_CANTP_STMINTIMEOUTHANDLING_EXIT
/** \brief Exit point of function CanTp_STminTimeoutHandling */
#define DBG_CANTP_STMINTIMEOUTHANDLING_EXIT(a)
#endif

#ifndef DBG_CANTP_PREPAREXF_ENTRY
/** \brief Entry point of function CanTp_PreparexF */
#define DBG_CANTP_PREPAREXF_ENTRY(a)
#endif

#ifndef DBG_CANTP_PREPAREXF_EXIT
/** \brief Exit point of function CanTp_PreparexF */
#define DBG_CANTP_PREPAREXF_EXIT(a)
#endif

#ifndef DBG_CANTP_PREPAREFCWT_ENTRY
/** \brief Entry point of function CanTp_PrepareFCwt */
#define DBG_CANTP_PREPAREFCWT_ENTRY(a)
#endif

#ifndef DBG_CANTP_PREPAREFCWT_EXIT
/** \brief Exit point of function CanTp_PrepareFCwt */
#define DBG_CANTP_PREPAREFCWT_EXIT(a)
#endif

#ifndef DBG_CANTP_CHECKANDHANDLEWAITFRAMETIMEOUT_ENTRY
/** \brief Entry point of function CanTp_CheckAndHandleWaitFrameTimeOut */
#define DBG_CANTP_CHECKANDHANDLEWAITFRAMETIMEOUT_ENTRY(a)
#endif

#ifndef DBG_CANTP_CHECKANDHANDLEWAITFRAMETIMEOUT_EXIT
/** \brief Exit point of function CanTp_CheckAndHandleWaitFrameTimeOut */
#define DBG_CANTP_CHECKANDHANDLEWAITFRAMETIMEOUT_EXIT(a)
#endif

#ifndef DBG_CANTP_PREPAREFCOVFLW_ENTRY
/** \brief Entry point of function CanTp_PrepareFCovflw */
#define DBG_CANTP_PREPAREFCOVFLW_ENTRY(a)
#endif

#ifndef DBG_CANTP_PREPAREFCOVFLW_EXIT
/** \brief Exit point of function CanTp_PrepareFCovflw */
#define DBG_CANTP_PREPAREFCOVFLW_EXIT(a)
#endif

#ifndef DBG_CANTP_PREPAREFCCTS_ENTRY
/** \brief Entry point of function CanTp_PrepareFCcts */
#define DBG_CANTP_PREPAREFCCTS_ENTRY(a)
#endif

#ifndef DBG_CANTP_PREPAREFCCTS_EXIT
/** \brief Exit point of function CanTp_PrepareFCcts */
#define DBG_CANTP_PREPAREFCCTS_EXIT(a)
#endif

#ifndef DBG_CANTP_CALCULATEBLOCKSIZE_ENTRY
/** \brief Entry point of function CanTp_CalculateBlockSize */
#define DBG_CANTP_CALCULATEBLOCKSIZE_ENTRY(a,b)
#endif

#ifndef DBG_CANTP_CALCULATEBLOCKSIZE_EXIT
/** \brief Exit point of function CanTp_CalculateBlockSize */
#define DBG_CANTP_CALCULATEBLOCKSIZE_EXIT(a,b,c)
#endif

#ifndef DBG_CANTP_TIMEOUTHANDLING_ENTRY
/** \brief Entry point of function CanTp_TimeoutHandling */
#define DBG_CANTP_TIMEOUTHANDLING_ENTRY(a)
#endif

#ifndef DBG_CANTP_TIMEOUTHANDLING_EXIT
/** \brief Exit point of function CanTp_TimeoutHandling */
#define DBG_CANTP_TIMEOUTHANDLING_EXIT(a)
#endif

#ifndef DBG_CANTP_STALLHANDLING_ENTRY
/** \brief Entry point of function CanTp_StallHandling */
#define DBG_CANTP_STALLHANDLING_ENTRY()
#endif

#ifndef DBG_CANTP_STALLHANDLING_EXIT
/** \brief Exit point of function CanTp_StallHandling */
#define DBG_CANTP_STALLHANDLING_EXIT()
#endif

#ifndef DBG_CANTP_INITCHANNELPTR_ENTRY
/** \brief Entry point of function CanTp_InitChannelPtr */
#define DBG_CANTP_INITCHANNELPTR_ENTRY(a)
#endif

#ifndef DBG_CANTP_INITCHANNELPTR_EXIT
/** \brief Exit point of function CanTp_InitChannelPtr */
#define DBG_CANTP_INITCHANNELPTR_EXIT(a)
#endif

#ifndef DBG_CANTP_PROCESSCOPYTXDATA_ENTRY
/** \brief Entry point of function CanTp_ProcessCopyTxData */
#define DBG_CANTP_PROCESSCOPYTXDATA_ENTRY(a,b)
#endif

#ifndef DBG_CANTP_PROCESSCOPYTXDATA_EXIT
/** \brief Exit point of function CanTp_ProcessCopyTxData */
#define DBG_CANTP_PROCESSCOPYTXDATA_EXIT(a,b,c)
#endif

#ifndef DBG_CANTP_VERIFYBLOCKSIZE_ENTRY
/** \brief Entry point of function CanTp_VerifyBlockSize */
#define DBG_CANTP_VERIFYBLOCKSIZE_ENTRY(a)
#endif

#ifndef DBG_CANTP_VERIFYBLOCKSIZE_EXIT
/** \brief Exit point of function CanTp_VerifyBlockSize */
#define DBG_CANTP_VERIFYBLOCKSIZE_EXIT(a,b)
#endif

#ifndef DBG_CANTP_REQUESTTXFRAMEDATA_ENTRY
/** \brief Entry point of function CanTp_RequestTxFrameData */
#define DBG_CANTP_REQUESTTXFRAMEDATA_ENTRY(a)
#endif

#ifndef DBG_CANTP_REQUESTTXFRAMEDATA_EXIT
/** \brief Exit point of function CanTp_RequestTxFrameData */
#define DBG_CANTP_REQUESTTXFRAMEDATA_EXIT(a,b)
#endif

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[external data]=========================================*/

#endif /* (!defined CANTP_TRACE_H) */
/*==================[end of file]===========================================*/
