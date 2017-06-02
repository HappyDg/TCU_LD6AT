/**
 * \file
 *
 * \brief AUTOSAR ComM
 *
 * This file contains the implementation of the AUTOSAR
 * module ComM.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#if (!defined COMM_TRACE_H)
#define COMM_TRACE_H
/*==================[inclusions]============================================*/

#include <TSAutosar.h>



/*==================[macros]================================================*/

#ifndef DBG_COMM_GENERIC_GRP
/** \brief Gegeric state change */
#define DBG_COMM_GENERIC_GRP(a,b,c,d) TS_PARAM_UNUSED(c)
#endif

#ifndef DBG_COMM_INIT_ENTRY
/** \brief Entry point of function ComM_Init() */
#define DBG_COMM_INIT_ENTRY()
#endif

#ifndef DBG_COMM_INIT_EXIT
/** \brief Exit point of function ComM_Init() */
#define DBG_COMM_INIT_EXIT()
#endif

#ifndef DBG_COMM_DEINIT_ENTRY
/** \brief Entry point of function ComM_DeInit() */
#define DBG_COMM_DEINIT_ENTRY()
#endif

#ifndef DBG_COMM_DEINIT_EXIT
/** \brief Exit point of function ComM_DeInit() */
#define DBG_COMM_DEINIT_EXIT()
#endif

#ifndef DBG_COMM_GETSTATE_ENTRY
/** \brief Entry point of function ComM_GetState() */
#define DBG_COMM_GETSTATE_ENTRY(a,b)
#endif

#ifndef DBG_COMM_GETSTATE_EXIT
/** \brief Exit point of function ComM_GetState() */
#define DBG_COMM_GETSTATE_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_GETSTATUS_ENTRY
/** \brief Entry point of function ComM_GetStatus() */
#define DBG_COMM_GETSTATUS_ENTRY(a)
#endif

#ifndef DBG_COMM_GETSTATUS_EXIT
/** \brief Exit point of function ComM_GetStatus() */
#define DBG_COMM_GETSTATUS_EXIT(a,b)
#endif

#ifndef DBG_COMM_ASR32_GETINHIBITIONSTATUS_ENTRY
/** \brief Entry point of function ComM_ASR32_GetInhibitionStatus() */
#define DBG_COMM_ASR32_GETINHIBITIONSTATUS_ENTRY(a,b)
#endif

#ifndef DBG_COMM_ASR32_GETINHIBITIONSTATUS_EXIT
/** \brief Exit point of function ComM_ASR32_GetInhibitionStatus() */
#define DBG_COMM_ASR32_GETINHIBITIONSTATUS_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_ASR40_GETINHIBITIONSTATUS_ENTRY
/** \brief Entry point of function ComM_ASR40_GetInhibitionStatus() */
#define DBG_COMM_ASR40_GETINHIBITIONSTATUS_ENTRY(a,b)
#endif

#ifndef DBG_COMM_ASR40_GETINHIBITIONSTATUS_EXIT
/** \brief Exit point of function ComM_ASR40_GetInhibitionStatus() */
#define DBG_COMM_ASR40_GETINHIBITIONSTATUS_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_ASR32_REQUESTCOMMODE_ENTRY
/** \brief Entry point of function ComM_ASR32_RequestComMode() */
#define DBG_COMM_ASR32_REQUESTCOMMODE_ENTRY(a,b)
#endif

#ifndef DBG_COMM_ASR32_REQUESTCOMMODE_EXIT
/** \brief Exit point of function ComM_ASR32_RequestComMode() */
#define DBG_COMM_ASR32_REQUESTCOMMODE_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_ASR40_REQUESTCOMMODE_ENTRY
/** \brief Entry point of function ComM_ASR40_RequestComMode() */
#define DBG_COMM_ASR40_REQUESTCOMMODE_ENTRY(a,b)
#endif

#ifndef DBG_COMM_ASR40_REQUESTCOMMODE_EXIT
/** \brief Exit point of function ComM_ASR40_RequestComMode() */
#define DBG_COMM_ASR40_REQUESTCOMMODE_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_ASR32_GETMAXCOMMODE_ENTRY
/** \brief Entry point of function ComM_ASR32_GetMaxComMode() */
#define DBG_COMM_ASR32_GETMAXCOMMODE_ENTRY(a,b)
#endif

#ifndef DBG_COMM_ASR32_GETMAXCOMMODE_EXIT
/** \brief Exit point of function ComM_ASR32_GetMaxComMode() */
#define DBG_COMM_ASR32_GETMAXCOMMODE_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_ASR40_GETMAXCOMMODE_ENTRY
/** \brief Entry point of function ComM_ASR40_GetMaxComMode() */
#define DBG_COMM_ASR40_GETMAXCOMMODE_ENTRY(a,b)
#endif

#ifndef DBG_COMM_ASR40_GETMAXCOMMODE_EXIT
/** \brief Exit point of function ComM_ASR40_GetMaxComMode() */
#define DBG_COMM_ASR40_GETMAXCOMMODE_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_ASR32_GETREQUESTEDMODE_ENTRY
/** \brief Entry point of function ComM_ASR32_GetRequestedMode() */
#define DBG_COMM_ASR32_GETREQUESTEDMODE_ENTRY(a,b)
#endif

#ifndef DBG_COMM_ASR32_GETREQUESTEDMODE_EXIT
/** \brief Exit point of function ComM_ASR32_GetRequestedMode() */
#define DBG_COMM_ASR32_GETREQUESTEDMODE_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_ASR40_GETREQUESTEDCOMMODE_ENTRY
/** \brief Entry point of function ComM_ASR40_GetRequestedComMode() */
#define DBG_COMM_ASR40_GETREQUESTEDCOMMODE_ENTRY(a,b)
#endif

#ifndef DBG_COMM_ASR40_GETREQUESTEDCOMMODE_EXIT
/** \brief Exit point of function ComM_ASR40_GetRequestedComMode() */
#define DBG_COMM_ASR40_GETREQUESTEDCOMMODE_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_ASR32_GETCURRENTCOMMODE_ENTRY
/** \brief Entry point of function ComM_ASR32_GetCurrentComMode() */
#define DBG_COMM_ASR32_GETCURRENTCOMMODE_ENTRY(a,b)
#endif

#ifndef DBG_COMM_ASR32_GETCURRENTCOMMODE_EXIT
/** \brief Exit point of function ComM_ASR32_GetCurrentComMode() */
#define DBG_COMM_ASR32_GETCURRENTCOMMODE_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_ASR40_GETCURRENTCOMMODE_ENTRY
/** \brief Entry point of function ComM_ASR40_GetCurrentComMode() */
#define DBG_COMM_ASR40_GETCURRENTCOMMODE_ENTRY(a,b)
#endif

#ifndef DBG_COMM_ASR40_GETCURRENTCOMMODE_EXIT
/** \brief Exit point of function ComM_ASR40_GetCurrentComMode() */
#define DBG_COMM_ASR40_GETCURRENTCOMMODE_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_ASR32_PREVENTWAKEUP_ENTRY
/** \brief Entry point of function ComM_ASR32_PreventWakeUp() */
#define DBG_COMM_ASR32_PREVENTWAKEUP_ENTRY(a,b)
#endif

#ifndef DBG_COMM_ASR32_PREVENTWAKEUP_EXIT
/** \brief Exit point of function ComM_ASR32_PreventWakeUp() */
#define DBG_COMM_ASR32_PREVENTWAKEUP_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_ASR40_PREVENTWAKEUP_ENTRY
/** \brief Entry point of function ComM_ASR40_PreventWakeUp() */
#define DBG_COMM_ASR40_PREVENTWAKEUP_ENTRY(a,b)
#endif

#ifndef DBG_COMM_ASR40_PREVENTWAKEUP_EXIT
/** \brief Exit point of function ComM_ASR40_PreventWakeUp() */
#define DBG_COMM_ASR40_PREVENTWAKEUP_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_ASR32_LIMITCHANNELTONOCOMMODE_ENTRY
/** \brief Entry point of function ComM_ASR32_LimitChannelToNoComMode() */
#define DBG_COMM_ASR32_LIMITCHANNELTONOCOMMODE_ENTRY(a,b)
#endif

#ifndef DBG_COMM_ASR32_LIMITCHANNELTONOCOMMODE_EXIT
/** \brief Exit point of function ComM_ASR32_LimitChannelToNoComMode() */
#define DBG_COMM_ASR32_LIMITCHANNELTONOCOMMODE_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_ASR40_LIMITCHANNELTONOCOMMODE_ENTRY
/** \brief Entry point of function ComM_ASR40_LimitChannelToNoComMode() */
#define DBG_COMM_ASR40_LIMITCHANNELTONOCOMMODE_ENTRY(a,b)
#endif

#ifndef DBG_COMM_ASR40_LIMITCHANNELTONOCOMMODE_EXIT
/** \brief Exit point of function ComM_ASR40_LimitChannelToNoComMode() */
#define DBG_COMM_ASR40_LIMITCHANNELTONOCOMMODE_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_ASR32_LIMITECUTONOCOMMODE_ENTRY
/** \brief Entry point of function ComM_ASR32_LimitECUToNoComMode() */
#define DBG_COMM_ASR32_LIMITECUTONOCOMMODE_ENTRY(a)
#endif

#ifndef DBG_COMM_ASR32_LIMITECUTONOCOMMODE_EXIT
/** \brief Exit point of function ComM_ASR32_LimitECUToNoComMode() */
#define DBG_COMM_ASR32_LIMITECUTONOCOMMODE_EXIT(a,b)
#endif

#ifndef DBG_COMM_ASR40_LIMITECUTONOCOMMODE_ENTRY
/** \brief Entry point of function ComM_ASR40_LimitECUToNoComMode() */
#define DBG_COMM_ASR40_LIMITECUTONOCOMMODE_ENTRY(a)
#endif

#ifndef DBG_COMM_ASR40_LIMITECUTONOCOMMODE_EXIT
/** \brief Exit point of function ComM_ASR40_LimitECUToNoComMode() */
#define DBG_COMM_ASR40_LIMITECUTONOCOMMODE_EXIT(a,b)
#endif

#ifndef DBG_COMM_ASR32_READINHIBITCOUNTER_ENTRY
/** \brief Entry point of function ComM_ASR32_ReadInhibitCounter() */
#define DBG_COMM_ASR32_READINHIBITCOUNTER_ENTRY(a)
#endif

#ifndef DBG_COMM_ASR32_READINHIBITCOUNTER_EXIT
/** \brief Exit point of function ComM_ASR32_ReadInhibitCounter() */
#define DBG_COMM_ASR32_READINHIBITCOUNTER_EXIT(a,b)
#endif

#ifndef DBG_COMM_ASR40_READINHIBITCOUNTER_ENTRY
/** \brief Entry point of function ComM_ASR40_ReadInhibitCounter() */
#define DBG_COMM_ASR40_READINHIBITCOUNTER_ENTRY(a)
#endif

#ifndef DBG_COMM_ASR40_READINHIBITCOUNTER_EXIT
/** \brief Exit point of function ComM_ASR40_ReadInhibitCounter() */
#define DBG_COMM_ASR40_READINHIBITCOUNTER_EXIT(a,b)
#endif

#ifndef DBG_COMM_ASR32_RESETINHIBITCOUNTER_ENTRY
/** \brief Entry point of function ComM_ASR32_ResetInhibitCounter() */
#define DBG_COMM_ASR32_RESETINHIBITCOUNTER_ENTRY()
#endif

#ifndef DBG_COMM_ASR32_RESETINHIBITCOUNTER_EXIT
/** \brief Exit point of function ComM_ASR32_ResetInhibitCounter() */
#define DBG_COMM_ASR32_RESETINHIBITCOUNTER_EXIT(a)
#endif

#ifndef DBG_COMM_ASR40_RESETINHIBITCOUNTER_ENTRY
/** \brief Entry point of function ComM_ASR40_ResetInhibitCounter() */
#define DBG_COMM_ASR40_RESETINHIBITCOUNTER_ENTRY()
#endif

#ifndef DBG_COMM_ASR40_RESETINHIBITCOUNTER_EXIT
/** \brief Exit point of function ComM_ASR40_ResetInhibitCounter() */
#define DBG_COMM_ASR40_RESETINHIBITCOUNTER_EXIT(a)
#endif

#ifndef DBG_COMM_ASR32_SETECUGROUPCLASSIFICATION_ENTRY
/** \brief Entry point of function ComM_ASR32_SetECUGroupClassification() */
#define DBG_COMM_ASR32_SETECUGROUPCLASSIFICATION_ENTRY(a)
#endif

#ifndef DBG_COMM_ASR32_SETECUGROUPCLASSIFICATION_EXIT
/** \brief Exit point of function ComM_ASR32_SetECUGroupClassification() */
#define DBG_COMM_ASR32_SETECUGROUPCLASSIFICATION_EXIT(a,b)
#endif

#ifndef DBG_COMM_ASR40_SETECUGROUPCLASSIFICATION_ENTRY
/** \brief Entry point of function ComM_ASR40_SetECUGroupClassification() */
#define DBG_COMM_ASR40_SETECUGROUPCLASSIFICATION_ENTRY(a)
#endif

#ifndef DBG_COMM_ASR40_SETECUGROUPCLASSIFICATION_EXIT
/** \brief Exit point of function ComM_ASR40_SetECUGroupClassification() */
#define DBG_COMM_ASR40_SETECUGROUPCLASSIFICATION_EXIT(a,b)
#endif

#ifndef DBG_COMM_GETVERSIONINFO_ENTRY
/** \brief Entry point of function ComM_GetVersionInfo() */
#define DBG_COMM_GETVERSIONINFO_ENTRY(a)
#endif

#ifndef DBG_COMM_GETVERSIONINFO_EXIT
/** \brief Exit point of function ComM_GetVersionInfo() */
#define DBG_COMM_GETVERSIONINFO_EXIT(a)
#endif

#ifndef DBG_COMM_CHANNELNOCOMINHIBITIONSTATUS_ENTRY
/** \brief Entry point of function ComM_ChannelNoComInhibitionStatus() */
#define DBG_COMM_CHANNELNOCOMINHIBITIONSTATUS_ENTRY(a)
#endif

#ifndef DBG_COMM_CHANNELNOCOMINHIBITIONSTATUS_EXIT
/** \brief Exit point of function ComM_ChannelNoComInhibitionStatus() */
#define DBG_COMM_CHANNELNOCOMINHIBITIONSTATUS_EXIT(a,b)
#endif

#ifndef DBG_COMM_CHANNELWAKEUPINHIBITIONSTATUS_ENTRY
/** \brief Entry point of function ComM_ChannelWakeUpInhibitionStatus() */
#define DBG_COMM_CHANNELWAKEUPINHIBITIONSTATUS_ENTRY(a)
#endif

#ifndef DBG_COMM_CHANNELWAKEUPINHIBITIONSTATUS_EXIT
/** \brief Exit point of function ComM_ChannelWakeUpInhibitionStatus() */
#define DBG_COMM_CHANNELWAKEUPINHIBITIONSTATUS_EXIT(a,b)
#endif

#ifndef DBG_COMM_NM_NETWORKSTARTINDICATION_ENTRY
/** \brief Entry point of function ComM_Nm_NetworkStartIndication() */
#define DBG_COMM_NM_NETWORKSTARTINDICATION_ENTRY(a)
#endif

#ifndef DBG_COMM_NM_NETWORKSTARTINDICATION_EXIT
/** \brief Exit point of function ComM_Nm_NetworkStartIndication() */
#define DBG_COMM_NM_NETWORKSTARTINDICATION_EXIT(a)
#endif

#ifndef DBG_COMM_NM_NETWORKMODE_ENTRY
/** \brief Entry point of function ComM_Nm_NetworkMode() */
#define DBG_COMM_NM_NETWORKMODE_ENTRY(a)
#endif

#ifndef DBG_COMM_NM_NETWORKMODE_EXIT
/** \brief Exit point of function ComM_Nm_NetworkMode() */
#define DBG_COMM_NM_NETWORKMODE_EXIT(a)
#endif

#ifndef DBG_COMM_NM_PREPAREBUSSLEEPMODE_ENTRY
/** \brief Entry point of function ComM_Nm_PrepareBusSleepMode() */
#define DBG_COMM_NM_PREPAREBUSSLEEPMODE_ENTRY(a)
#endif

#ifndef DBG_COMM_NM_PREPAREBUSSLEEPMODE_EXIT
/** \brief Exit point of function ComM_Nm_PrepareBusSleepMode() */
#define DBG_COMM_NM_PREPAREBUSSLEEPMODE_EXIT(a)
#endif

#ifndef DBG_COMM_NM_BUSSLEEPMODE_ENTRY
/** \brief Entry point of function ComM_Nm_BusSleepMode() */
#define DBG_COMM_NM_BUSSLEEPMODE_ENTRY(a)
#endif

#ifndef DBG_COMM_NM_BUSSLEEPMODE_EXIT
/** \brief Exit point of function ComM_Nm_BusSleepMode() */
#define DBG_COMM_NM_BUSSLEEPMODE_EXIT(a)
#endif

#ifndef DBG_COMM_NM_RESTARTINDICATION_ENTRY
/** \brief Entry point of function ComM_Nm_RestartIndication() */
#define DBG_COMM_NM_RESTARTINDICATION_ENTRY(a)
#endif

#ifndef DBG_COMM_NM_RESTARTINDICATION_EXIT
/** \brief Exit point of function ComM_Nm_RestartIndication() */
#define DBG_COMM_NM_RESTARTINDICATION_EXIT(a)
#endif

#ifndef DBG_COMM_DCM_ACTIVEDIAGNOSTIC_ENTRY
/** \brief Entry point of function ComM_DCM_ActiveDiagnostic() */
#define DBG_COMM_DCM_ACTIVEDIAGNOSTIC_ENTRY(a)
#endif

#ifndef DBG_COMM_DCM_ACTIVEDIAGNOSTIC_EXIT
/** \brief Exit point of function ComM_DCM_ActiveDiagnostic() */
#define DBG_COMM_DCM_ACTIVEDIAGNOSTIC_EXIT(a)
#endif

#ifndef DBG_COMM_DCM_INACTIVEDIAGNOSTIC_ENTRY
/** \brief Entry point of function ComM_DCM_InactiveDiagnostic() */
#define DBG_COMM_DCM_INACTIVEDIAGNOSTIC_ENTRY(a)
#endif

#ifndef DBG_COMM_DCM_INACTIVEDIAGNOSTIC_EXIT
/** \brief Exit point of function ComM_DCM_InactiveDiagnostic() */
#define DBG_COMM_DCM_INACTIVEDIAGNOSTIC_EXIT(a)
#endif

#ifndef DBG_COMM_ECUM_WAKEUPINDICATION_ENTRY
/** \brief Entry point of function ComM_EcuM_WakeUpIndication() */
#define DBG_COMM_ECUM_WAKEUPINDICATION_ENTRY(a)
#endif

#ifndef DBG_COMM_ECUM_WAKEUPINDICATION_EXIT
/** \brief Exit point of function ComM_EcuM_WakeUpIndication() */
#define DBG_COMM_ECUM_WAKEUPINDICATION_EXIT(a)
#endif

#ifndef DBG_COMM_COMMUNICATIONALLOWED_ENTRY
/** \brief Entry point of function ComM_CommunicationAllowed() */
#define DBG_COMM_COMMUNICATIONALLOWED_ENTRY(a,b)
#endif

#ifndef DBG_COMM_COMMUNICATIONALLOWED_EXIT
/** \brief Exit point of function ComM_CommunicationAllowed() */
#define DBG_COMM_COMMUNICATIONALLOWED_EXIT(a,b)
#endif

#ifndef DBG_COMM_BUSSM_MODEINDICATION_ENTRY
/** \brief Entry point of function ComM_BusSM_ModeIndication() */
#define DBG_COMM_BUSSM_MODEINDICATION_ENTRY(a,b)
#endif

#ifndef DBG_COMM_BUSSM_MODEINDICATION_EXIT
/** \brief Exit point of function ComM_BusSM_ModeIndication() */
#define DBG_COMM_BUSSM_MODEINDICATION_EXIT(a,b)
#endif

#ifndef DBG_COMM_EB_GETNUMUSERSOFCHANNEL_ENTRY
/** \brief Entry point of function ComM_EB_GetNumUsersOfChannel() */
#define DBG_COMM_EB_GETNUMUSERSOFCHANNEL_ENTRY(a)
#endif

#ifndef DBG_COMM_EB_GETNUMUSERSOFCHANNEL_EXIT
/** \brief Exit point of function ComM_EB_GetNumUsersOfChannel() */
#define DBG_COMM_EB_GETNUMUSERSOFCHANNEL_EXIT(a,b)
#endif

#ifndef DBG_COMM_EB_GETUSERSOFCHANNEL_ENTRY
/** \brief Entry point of function ComM_EB_GetUsersOfChannel() */
#define DBG_COMM_EB_GETUSERSOFCHANNEL_ENTRY(a,b)
#endif

#ifndef DBG_COMM_EB_GETUSERSOFCHANNEL_EXIT
/** \brief Exit point of function ComM_EB_GetUsersOfChannel() */
#define DBG_COMM_EB_GETUSERSOFCHANNEL_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_EB_GETUSERREQUESTEDCOMMODE_ENTRY
/** \brief Entry point of function ComM_EB_GetUserRequestedComMode() */
#define DBG_COMM_EB_GETUSERREQUESTEDCOMMODE_ENTRY(a)
#endif

#ifndef DBG_COMM_EB_GETUSERREQUESTEDCOMMODE_EXIT
/** \brief Exit point of function ComM_EB_GetUserRequestedComMode() */
#define DBG_COMM_EB_GETUSERREQUESTEDCOMMODE_EXIT(a,b)
#endif

#ifndef DBG_COMM_EB_SETREQUESTEDCOMMODE_ENTRY
/** \brief Entry point of function ComM_EB_SetRequestedComMode() */
#define DBG_COMM_EB_SETREQUESTEDCOMMODE_ENTRY(a,b)
#endif

#ifndef DBG_COMM_EB_SETREQUESTEDCOMMODE_EXIT
/** \brief Exit point of function ComM_EB_SetRequestedComMode() */
#define DBG_COMM_EB_SETREQUESTEDCOMMODE_EXIT(a,b)
#endif

#ifndef DBG_COMM_EVALUATEPNC_ENTRY
/** \brief Entry point of function ComM_EvaluatePnc() */
#define DBG_COMM_EVALUATEPNC_ENTRY(a,b)
#endif

#ifndef DBG_COMM_EVALUATEPNC_EXIT
/** \brief Exit point of function ComM_EvaluatePnc() */
#define DBG_COMM_EVALUATEPNC_EXIT(a,b)
#endif

#ifndef DBG_COMM_SETCHANNELCOMMINHIBITIONSTATUS_ENTRY
/** \brief Entry point of function ComM_SetChannelComMInhibitionStatus() */
#define DBG_COMM_SETCHANNELCOMMINHIBITIONSTATUS_ENTRY(a,b,c)
#endif

#ifndef DBG_COMM_SETCHANNELCOMMINHIBITIONSTATUS_EXIT
/** \brief Exit point of function ComM_SetChannelComMInhibitionStatus() */
#define DBG_COMM_SETCHANNELCOMMINHIBITIONSTATUS_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_BITARRAYSET_ENTRY
/** \brief Entry point of function ComM_BitArraySet() */
#define DBG_COMM_BITARRAYSET_ENTRY(a,b)
#endif

#ifndef DBG_COMM_BITARRAYSET_EXIT
/** \brief Exit point of function ComM_BitArraySet() */
#define DBG_COMM_BITARRAYSET_EXIT(a,b)
#endif

#ifndef DBG_COMM_BITARRAYCLEAR_ENTRY
/** \brief Entry point of function ComM_BitArrayClear() */
#define DBG_COMM_BITARRAYCLEAR_ENTRY(a,b)
#endif

#ifndef DBG_COMM_BITARRAYCLEAR_EXIT
/** \brief Exit point of function ComM_BitArrayClear() */
#define DBG_COMM_BITARRAYCLEAR_EXIT(a,b)
#endif

#ifndef DBG_COMM_BITARRAYISBITSET_ENTRY
/** \brief Entry point of function ComM_BitArrayIsBitSet() */
#define DBG_COMM_BITARRAYISBITSET_ENTRY(a,b)
#endif

#ifndef DBG_COMM_BITARRAYISBITSET_EXIT
/** \brief Exit point of function ComM_BitArrayIsBitSet() */
#define DBG_COMM_BITARRAYISBITSET_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_PNCMAINFUNCTION_ENTRY
/** \brief Entry point of function ComM_PncMainFunction() */
#define DBG_COMM_PNCMAINFUNCTION_ENTRY()
#endif

#ifndef DBG_COMM_PNCMAINFUNCTION_EXIT
/** \brief Exit point of function ComM_PncMainFunction() */
#define DBG_COMM_PNCMAINFUNCTION_EXIT()
#endif

#ifndef DBG_COMM_ASR32_RTENOTIFY_ENTRY
/** \brief Entry point of function ComM_ASR32_RteNotify() */
#define DBG_COMM_ASR32_RTENOTIFY_ENTRY(a,b)
#endif

#ifndef DBG_COMM_ASR32_RTENOTIFY_EXIT
/** \brief Exit point of function ComM_ASR32_RteNotify() */
#define DBG_COMM_ASR32_RTENOTIFY_EXIT(a,b)
#endif

#ifndef DBG_COMM_ASR32_RTE_GETINHIBITIONSTATUS_ENTRY
/** \brief Entry point of function ComM_ASR32_Rte_GetInhibitionStatus() */
#define DBG_COMM_ASR32_RTE_GETINHIBITIONSTATUS_ENTRY(a,b)
#endif

#ifndef DBG_COMM_ASR32_RTE_GETINHIBITIONSTATUS_EXIT
/** \brief Exit point of function ComM_ASR32_Rte_GetInhibitionStatus() */
#define DBG_COMM_ASR32_RTE_GETINHIBITIONSTATUS_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_ASR32_RTE_REQUESTCOMMODE_ENTRY
/** \brief Entry point of function ComM_ASR32_Rte_RequestComMode() */
#define DBG_COMM_ASR32_RTE_REQUESTCOMMODE_ENTRY(a,b)
#endif

#ifndef DBG_COMM_ASR32_RTE_REQUESTCOMMODE_EXIT
/** \brief Exit point of function ComM_ASR32_Rte_RequestComMode() */
#define DBG_COMM_ASR32_RTE_REQUESTCOMMODE_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_ASR32_RTE_GETMAXCOMMODE_ENTRY
/** \brief Entry point of function ComM_ASR32_Rte_GetMaxComMode() */
#define DBG_COMM_ASR32_RTE_GETMAXCOMMODE_ENTRY(a,b)
#endif

#ifndef DBG_COMM_ASR32_RTE_GETMAXCOMMODE_EXIT
/** \brief Exit point of function ComM_ASR32_Rte_GetMaxComMode() */
#define DBG_COMM_ASR32_RTE_GETMAXCOMMODE_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_ASR32_RTE_GETREQUESTEDMODE_ENTRY
/** \brief Entry point of function ComM_ASR32_Rte_GetRequestedMode() */
#define DBG_COMM_ASR32_RTE_GETREQUESTEDMODE_ENTRY(a,b)
#endif

#ifndef DBG_COMM_ASR32_RTE_GETREQUESTEDMODE_EXIT
/** \brief Exit point of function ComM_ASR32_Rte_GetRequestedMode() */
#define DBG_COMM_ASR32_RTE_GETREQUESTEDMODE_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_ASR32_RTE_GETCURRENTCOMMODE_ENTRY
/** \brief Entry point of function ComM_ASR32_Rte_GetCurrentComMode() */
#define DBG_COMM_ASR32_RTE_GETCURRENTCOMMODE_ENTRY(a,b)
#endif

#ifndef DBG_COMM_ASR32_RTE_GETCURRENTCOMMODE_EXIT
/** \brief Exit point of function ComM_ASR32_Rte_GetCurrentComMode() */
#define DBG_COMM_ASR32_RTE_GETCURRENTCOMMODE_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_ASR32_RTE_PREVENTWAKEUP_ENTRY
/** \brief Entry point of function ComM_ASR32_Rte_PreventWakeUp() */
#define DBG_COMM_ASR32_RTE_PREVENTWAKEUP_ENTRY(a,b)
#endif

#ifndef DBG_COMM_ASR32_RTE_PREVENTWAKEUP_EXIT
/** \brief Exit point of function ComM_ASR32_Rte_PreventWakeUp() */
#define DBG_COMM_ASR32_RTE_PREVENTWAKEUP_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_ASR32_RTE_LIMITCHANNELTONOCOMMODE_ENTRY
/** \brief Entry point of function ComM_ASR32_Rte_LimitChannelToNoComMode() */
#define DBG_COMM_ASR32_RTE_LIMITCHANNELTONOCOMMODE_ENTRY(a,b)
#endif

#ifndef DBG_COMM_ASR32_RTE_LIMITCHANNELTONOCOMMODE_EXIT
/** \brief Exit point of function ComM_ASR32_Rte_LimitChannelToNoComMode() */
#define DBG_COMM_ASR32_RTE_LIMITCHANNELTONOCOMMODE_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_ASR32_RTE_LIMITECUTONOCOMMODE_ENTRY
/** \brief Entry point of function ComM_ASR32_Rte_LimitECUToNoComMode() */
#define DBG_COMM_ASR32_RTE_LIMITECUTONOCOMMODE_ENTRY(a)
#endif

#ifndef DBG_COMM_ASR32_RTE_LIMITECUTONOCOMMODE_EXIT
/** \brief Exit point of function ComM_ASR32_Rte_LimitECUToNoComMode() */
#define DBG_COMM_ASR32_RTE_LIMITECUTONOCOMMODE_EXIT(a,b)
#endif

#ifndef DBG_COMM_ASR32_RTE_READINHIBITCOUNTER_ENTRY
/** \brief Entry point of function ComM_ASR32_Rte_ReadInhibitCounter() */
#define DBG_COMM_ASR32_RTE_READINHIBITCOUNTER_ENTRY(a)
#endif

#ifndef DBG_COMM_ASR32_RTE_READINHIBITCOUNTER_EXIT
/** \brief Exit point of function ComM_ASR32_Rte_ReadInhibitCounter() */
#define DBG_COMM_ASR32_RTE_READINHIBITCOUNTER_EXIT(a,b)
#endif

#ifndef DBG_COMM_ASR32_RTE_RESETINHIBITCOUNTER_ENTRY
/** \brief Entry point of function ComM_ASR32_Rte_ResetInhibitCounter() */
#define DBG_COMM_ASR32_RTE_RESETINHIBITCOUNTER_ENTRY()
#endif

#ifndef DBG_COMM_ASR32_RTE_RESETINHIBITCOUNTER_EXIT
/** \brief Exit point of function ComM_ASR32_Rte_ResetInhibitCounter() */
#define DBG_COMM_ASR32_RTE_RESETINHIBITCOUNTER_EXIT(a)
#endif

#ifndef DBG_COMM_ASR32_RTE_SETECUGROUPCLASSIFICATION_ENTRY
/** \brief Entry point of function ComM_ASR32_Rte_SetECUGroupClassification() */
#define DBG_COMM_ASR32_RTE_SETECUGROUPCLASSIFICATION_ENTRY(a)
#endif

#ifndef DBG_COMM_ASR32_RTE_SETECUGROUPCLASSIFICATION_EXIT
/** \brief Exit point of function ComM_ASR32_Rte_SetECUGroupClassification() */
#define DBG_COMM_ASR32_RTE_SETECUGROUPCLASSIFICATION_EXIT(a,b)
#endif

#ifndef DBG_COMM_ASR40_RTENOTIFY_ENTRY
/** \brief Entry point of function ComM_ASR40_RteNotify() */
#define DBG_COMM_ASR40_RTENOTIFY_ENTRY(a,b)
#endif

#ifndef DBG_COMM_ASR40_RTENOTIFY_EXIT
/** \brief Exit point of function ComM_ASR40_RteNotify() */
#define DBG_COMM_ASR40_RTENOTIFY_EXIT(a,b)
#endif

#ifndef DBG_COMM_ASR40_RTE_GETINHIBITIONSTATUS_ENTRY
/** \brief Entry point of function ComM_ASR40_Rte_GetInhibitionStatus() */
#define DBG_COMM_ASR40_RTE_GETINHIBITIONSTATUS_ENTRY(a,b)
#endif

#ifndef DBG_COMM_ASR40_RTE_GETINHIBITIONSTATUS_EXIT
/** \brief Exit point of function ComM_ASR40_Rte_GetInhibitionStatus() */
#define DBG_COMM_ASR40_RTE_GETINHIBITIONSTATUS_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_ASR40_RTE_REQUESTCOMMODE_ENTRY
/** \brief Entry point of function ComM_ASR40_Rte_RequestComMode() */
#define DBG_COMM_ASR40_RTE_REQUESTCOMMODE_ENTRY(a,b)
#endif

#ifndef DBG_COMM_ASR40_RTE_REQUESTCOMMODE_EXIT
/** \brief Exit point of function ComM_ASR40_Rte_RequestComMode() */
#define DBG_COMM_ASR40_RTE_REQUESTCOMMODE_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_ASR40_RTE_GETMAXCOMMODE_ENTRY
/** \brief Entry point of function ComM_ASR40_Rte_GetMaxComMode() */
#define DBG_COMM_ASR40_RTE_GETMAXCOMMODE_ENTRY(a,b)
#endif

#ifndef DBG_COMM_ASR40_RTE_GETMAXCOMMODE_EXIT
/** \brief Exit point of function ComM_ASR40_Rte_GetMaxComMode() */
#define DBG_COMM_ASR40_RTE_GETMAXCOMMODE_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_ASR40_RTE_GETREQUESTEDCOMMODE_ENTRY
/** \brief Entry point of function ComM_ASR40_Rte_GetRequestedComMode() */
#define DBG_COMM_ASR40_RTE_GETREQUESTEDCOMMODE_ENTRY(a,b)
#endif

#ifndef DBG_COMM_ASR40_RTE_GETREQUESTEDCOMMODE_EXIT
/** \brief Exit point of function ComM_ASR40_Rte_GetRequestedComMode() */
#define DBG_COMM_ASR40_RTE_GETREQUESTEDCOMMODE_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_ASR40_RTE_GETCURRENTCOMMODE_ENTRY
/** \brief Entry point of function ComM_ASR40_Rte_GetCurrentComMode() */
#define DBG_COMM_ASR40_RTE_GETCURRENTCOMMODE_ENTRY(a,b)
#endif

#ifndef DBG_COMM_ASR40_RTE_GETCURRENTCOMMODE_EXIT
/** \brief Exit point of function ComM_ASR40_Rte_GetCurrentComMode() */
#define DBG_COMM_ASR40_RTE_GETCURRENTCOMMODE_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_ASR40_RTE_PREVENTWAKEUP_ENTRY
/** \brief Entry point of function ComM_ASR40_Rte_PreventWakeUp() */
#define DBG_COMM_ASR40_RTE_PREVENTWAKEUP_ENTRY(a,b)
#endif

#ifndef DBG_COMM_ASR40_RTE_PREVENTWAKEUP_EXIT
/** \brief Exit point of function ComM_ASR40_Rte_PreventWakeUp() */
#define DBG_COMM_ASR40_RTE_PREVENTWAKEUP_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_ASR40_RTE_LIMITCHANNELTONOCOMMODE_ENTRY
/** \brief Entry point of function ComM_ASR40_Rte_LimitChannelToNoComMode() */
#define DBG_COMM_ASR40_RTE_LIMITCHANNELTONOCOMMODE_ENTRY(a,b)
#endif

#ifndef DBG_COMM_ASR40_RTE_LIMITCHANNELTONOCOMMODE_EXIT
/** \brief Exit point of function ComM_ASR40_Rte_LimitChannelToNoComMode() */
#define DBG_COMM_ASR40_RTE_LIMITCHANNELTONOCOMMODE_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_ASR40_RTE_LIMITECUTONOCOMMODE_ENTRY
/** \brief Entry point of function ComM_ASR40_Rte_LimitECUToNoComMode() */
#define DBG_COMM_ASR40_RTE_LIMITECUTONOCOMMODE_ENTRY(a)
#endif

#ifndef DBG_COMM_ASR40_RTE_LIMITECUTONOCOMMODE_EXIT
/** \brief Exit point of function ComM_ASR40_Rte_LimitECUToNoComMode() */
#define DBG_COMM_ASR40_RTE_LIMITECUTONOCOMMODE_EXIT(a,b)
#endif

#ifndef DBG_COMM_ASR40_RTE_READINHIBITCOUNTER_ENTRY
/** \brief Entry point of function ComM_ASR40_Rte_ReadInhibitCounter() */
#define DBG_COMM_ASR40_RTE_READINHIBITCOUNTER_ENTRY(a)
#endif

#ifndef DBG_COMM_ASR40_RTE_READINHIBITCOUNTER_EXIT
/** \brief Exit point of function ComM_ASR40_Rte_ReadInhibitCounter() */
#define DBG_COMM_ASR40_RTE_READINHIBITCOUNTER_EXIT(a,b)
#endif

#ifndef DBG_COMM_ASR40_RTE_RESETINHIBITCOUNTER_ENTRY
/** \brief Entry point of function ComM_ASR40_Rte_ResetInhibitCounter() */
#define DBG_COMM_ASR40_RTE_RESETINHIBITCOUNTER_ENTRY()
#endif

#ifndef DBG_COMM_ASR40_RTE_RESETINHIBITCOUNTER_EXIT
/** \brief Exit point of function ComM_ASR40_Rte_ResetInhibitCounter() */
#define DBG_COMM_ASR40_RTE_RESETINHIBITCOUNTER_EXIT(a)
#endif

#ifndef DBG_COMM_ASR40_RTE_SETECUGROUPCLASSIFICATION_ENTRY
/** \brief Entry point of function ComM_ASR40_Rte_SetECUGroupClassification() */
#define DBG_COMM_ASR40_RTE_SETECUGROUPCLASSIFICATION_ENTRY(a)
#endif

#ifndef DBG_COMM_ASR40_RTE_SETECUGROUPCLASSIFICATION_EXIT
/** \brief Exit point of function ComM_ASR40_Rte_SetECUGroupClassification() */
#define DBG_COMM_ASR40_RTE_SETECUGROUPCLASSIFICATION_EXIT(a,b)
#endif

#ifndef DBG_COMM_PROCESSTIMERS_ENTRY
/** \brief Entry point of function ComM_ProcessTimers() */
#define DBG_COMM_PROCESSTIMERS_ENTRY(a)
#endif

#ifndef DBG_COMM_PROCESSTIMERS_EXIT
/** \brief Exit point of function ComM_ProcessTimers() */
#define DBG_COMM_PROCESSTIMERS_EXIT(a)
#endif

#ifndef DBG_COMM_NOTIFY2ARG_ENTRY
/** \brief Entry point of function ComM_Notify2Arg() */
#define DBG_COMM_NOTIFY2ARG_ENTRY(a,b)
#endif

#ifndef DBG_COMM_NOTIFY2ARG_EXIT
/** \brief Exit point of function ComM_Notify2Arg() */
#define DBG_COMM_NOTIFY2ARG_EXIT(a,b)
#endif

#ifndef DBG_COMM_BUSSMREQUESTCOMMODE2ARG_ENTRY
/** \brief Entry point of function ComM_BusSmRequestComMode2Arg() */
#define DBG_COMM_BUSSMREQUESTCOMMODE2ARG_ENTRY(a,b)
#endif

#ifndef DBG_COMM_BUSSMREQUESTCOMMODE2ARG_EXIT
/** \brief Exit point of function ComM_BusSmRequestComMode2Arg() */
#define DBG_COMM_BUSSMREQUESTCOMMODE2ARG_EXIT(a,b)
#endif

#ifndef DBG_COMM_RETRYBUSSMREQUEST_ENTRY
/** \brief Entry point of function ComM_RetryBusSmRequest() */
#define DBG_COMM_RETRYBUSSMREQUEST_ENTRY(a)
#endif

#ifndef DBG_COMM_RETRYBUSSMREQUEST_EXIT
/** \brief Exit point of function ComM_RetryBusSmRequest() */
#define DBG_COMM_RETRYBUSSMREQUEST_EXIT(a)
#endif

#ifndef DBG_COMM_CLEARUSERREQUEST_ENTRY
/** \brief Entry point of function ComM_ClearUserRequest() */
#define DBG_COMM_CLEARUSERREQUEST_ENTRY(a)
#endif

#ifndef DBG_COMM_CLEARUSERREQUEST_EXIT
/** \brief Exit point of function ComM_ClearUserRequest() */
#define DBG_COMM_CLEARUSERREQUEST_EXIT(a)
#endif

#ifndef DBG_COMM_ISCHANRELALLOWED_ENTRY
/** \brief Entry point of function ComM_IsChanRelAllowed() */
#define DBG_COMM_ISCHANRELALLOWED_ENTRY(a)
#endif

#ifndef DBG_COMM_ISCHANRELALLOWED_EXIT
/** \brief Exit point of function ComM_IsChanRelAllowed() */
#define DBG_COMM_ISCHANRELALLOWED_EXIT(a,b)
#endif

#ifndef DBG_COMM_ISCHANREQALLOWEDFULLCOM_ENTRY
/** \brief Entry point of function ComM_IsChanReqAllowedFullCom() */
#define DBG_COMM_ISCHANREQALLOWEDFULLCOM_ENTRY(a)
#endif

#ifndef DBG_COMM_ISCHANREQALLOWEDFULLCOM_EXIT
/** \brief Exit point of function ComM_IsChanReqAllowedFullCom() */
#define DBG_COMM_ISCHANREQALLOWEDFULLCOM_EXIT(a,b)
#endif

#ifndef DBG_COMM_ISCHANREQALLOWEDNOFULLCOM_ENTRY
/** \brief Entry point of function ComM_IsChanReqAllowedNoFullCom() */
#define DBG_COMM_ISCHANREQALLOWEDNOFULLCOM_ENTRY(a)
#endif

#ifndef DBG_COMM_ISCHANREQALLOWEDNOFULLCOM_EXIT
/** \brief Exit point of function ComM_IsChanReqAllowedNoFullCom() */
#define DBG_COMM_ISCHANREQALLOWEDNOFULLCOM_EXIT(a,b)
#endif

#ifndef DBG_COMM_ENTER_SCHM_COMM_EXCLUSIVE_AREA_0_ENTRY
/** \brief Entry point of function ComM_Enter_SCHM_COMM_EXCLUSIVE_AREA_0() */
#define DBG_COMM_ENTER_SCHM_COMM_EXCLUSIVE_AREA_0_ENTRY()
#endif

#ifndef DBG_COMM_ENTER_SCHM_COMM_EXCLUSIVE_AREA_0_EXIT
/** \brief Exit point of function ComM_Enter_SCHM_COMM_EXCLUSIVE_AREA_0() */
#define DBG_COMM_ENTER_SCHM_COMM_EXCLUSIVE_AREA_0_EXIT()
#endif

#ifndef DBG_COMM_EXIT_SCHM_COMM_EXCLUSIVE_AREA_0_ENTRY
/** \brief Entry point of function ComM_Exit_SCHM_COMM_EXCLUSIVE_AREA_0() */
#define DBG_COMM_EXIT_SCHM_COMM_EXCLUSIVE_AREA_0_ENTRY()
#endif

#ifndef DBG_COMM_EXIT_SCHM_COMM_EXCLUSIVE_AREA_0_EXIT
/** \brief Exit point of function ComM_Exit_SCHM_COMM_EXCLUSIVE_AREA_0() */
#define DBG_COMM_EXIT_SCHM_COMM_EXCLUSIVE_AREA_0_EXIT()
#endif

#ifndef DBG_COMM_EVALUATECHANNEL_ENTRY
/** \brief Entry point of function ComM_EvaluateChannel() */
#define DBG_COMM_EVALUATECHANNEL_ENTRY(a)
#endif

#ifndef DBG_COMM_EVALUATECHANNEL_EXIT
/** \brief Exit point of function ComM_EvaluateChannel() */
#define DBG_COMM_EVALUATECHANNEL_EXIT(a)
#endif

#ifndef DBG_COMM_RTENOTIFY_ENTRY
#define DBG_COMM_RTENOTIFY_ENTRY(User,CurComMode)
#endif

#ifndef DBG_COMM_RTENOTIFY_EXIT
#define DBG_COMM_RTENOTIFY_EXIT(User,CurComMode)
#endif

#ifndef DBG_COMM_RTE_GETINHIBITIONSTATUS_ENTRY
#define DBG_COMM_RTE_GETINHIBITIONSTATUS_ENTRY(Channel,Status)
#endif

#ifndef DBG_COMM_RTE_GETINHIBITIONSTATUS_EXIT
#define DBG_COMM_RTE_GETINHIBITIONSTATUS_EXIT(RetVal,Channel,Status)
#endif

#ifndef DBG_COMM_RTE_REQUESTCOMMODE_ENTRY
/** \brief Entry point of function ComM_Rte_RequestComMode */
#define DBG_COMM_RTE_REQUESTCOMMODE_ENTRY(a,b)
#endif

#ifndef DBG_COMM_RTE_REQUESTCOMMODE_EXIT
/** \brief Exit point of function ComM_Rte_RequestComMode */
#define DBG_COMM_RTE_REQUESTCOMMODE_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_RTE_GETMAXCOMMODE_ENTRY
/** \brief Entry point of function ComM_Rte_GetMaxComMode */
#define DBG_COMM_RTE_GETMAXCOMMODE_ENTRY(a,b)
#endif

#ifndef DBG_COMM_RTE_GETMAXCOMMODE_EXIT
/** \brief Exit point of function ComM_Rte_GetMaxComMode */
#define DBG_COMM_RTE_GETMAXCOMMODE_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_RTE_GETREQUESTEDMODE_ENTRY
/** \brief Entry point of function ComM_Rte_GetRequestedMode */
#define DBG_COMM_RTE_GETREQUESTEDMODE_ENTRY(a,b)
#endif

#ifndef DBG_COMM_RTE_GETREQUESTEDMODE_EXIT
/** \brief Exit point of function ComM_Rte_GetRequestedMode */
#define DBG_COMM_RTE_GETREQUESTEDMODE_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_RTE_GETCURRENTCOMMODE_ENTRY
/** \brief Entry point of function ComM_Rte_GetCurrentComMode */
#define DBG_COMM_RTE_GETCURRENTCOMMODE_ENTRY(a,b)
#endif

#ifndef DBG_COMM_RTE_GETCURRENTCOMMODE_EXIT
/** \brief Exit point of function ComM_Rte_GetCurrentComMode */
#define DBG_COMM_RTE_GETCURRENTCOMMODE_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_RTE_PREVENTWAKEUP_ENTRY
/** \brief Entry point of function ComM_Rte_PreventWakeUp */
#define DBG_COMM_RTE_PREVENTWAKEUP_ENTRY(a,b)
#endif

#ifndef DBG_COMM_RTE_PREVENTWAKEUP_EXIT
/** \brief Exit point of function ComM_Rte_PreventWakeUp */
#define DBG_COMM_RTE_PREVENTWAKEUP_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_RTE_LIMITCHANNELTONOCOMMODE_ENTRY
/** \brief Entry point of function ComM_Rte_LimitChannelToNoComMode */
#define DBG_COMM_RTE_LIMITCHANNELTONOCOMMODE_ENTRY(a,b)
#endif

#ifndef DBG_COMM_RTE_LIMITCHANNELTONOCOMMODE_EXIT
/** \brief Exit point of function ComM_Rte_LimitChannelToNoComMode */
#define DBG_COMM_RTE_LIMITCHANNELTONOCOMMODE_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_RTE_LIMITECUTONOCOMMODE_ENTRY
/** \brief Entry point of function ComM_Rte_LimitECUToNoComMode */
#define DBG_COMM_RTE_LIMITECUTONOCOMMODE_ENTRY(a)
#endif

#ifndef DBG_COMM_RTE_LIMITECUTONOCOMMODE_EXIT
/** \brief Exit point of function ComM_Rte_LimitECUToNoComMode */
#define DBG_COMM_RTE_LIMITECUTONOCOMMODE_EXIT(a,b)
#endif

#ifndef DBG_COMM_RTE_READINHIBITCOUNTER_ENTRY
/** \brief Entry point of function ComM_Rte_ReadInhibitCounter */
#define DBG_COMM_RTE_READINHIBITCOUNTER_ENTRY(a)
#endif

#ifndef DBG_COMM_RTE_READINHIBITCOUNTER_EXIT
/** \brief Exit point of function ComM_Rte_ReadInhibitCounter */
#define DBG_COMM_RTE_READINHIBITCOUNTER_EXIT(a,b)
#endif

#ifndef DBG_COMM_RTE_RESETINHIBITCOUNTER_ENTRY
/** \brief Entry point of function ComM_Rte_ResetInhibitCounter */
#define DBG_COMM_RTE_RESETINHIBITCOUNTER_ENTRY()
#endif

#ifndef DBG_COMM_RTE_RESETINHIBITCOUNTER_EXIT
/** \brief Exit point of function ComM_Rte_ResetInhibitCounter */
#define DBG_COMM_RTE_RESETINHIBITCOUNTER_EXIT(a)
#endif

#ifndef DBG_COMM_RTE_SETECUGROUPCLASSIFICATION_ENTRY
/** \brief Entry point of function ComM_Rte_SetECUGroupClassification */
#define DBG_COMM_RTE_SETECUGROUPCLASSIFICATION_ENTRY(a)
#endif

#ifndef DBG_COMM_RTE_SETECUGROUPCLASSIFICATION_EXIT
/** \brief Exit point of function ComM_Rte_SetECUGroupClassification */
#define DBG_COMM_RTE_SETECUGROUPCLASSIFICATION_EXIT(a,b)
#endif

#ifndef DBG_COMM_RTE_GETREQUESTEDCOMMODE_ENTRY
/** \brief Entry point of function ComM_Rte_GetRequestedComMode */
#define DBG_COMM_RTE_GETREQUESTEDCOMMODE_ENTRY(a,b)
#endif

#ifndef DBG_COMM_RTE_GETREQUESTEDCOMMODE_EXIT
/** \brief Exit point of function ComM_Rte_GetRequestedComMode */
#define DBG_COMM_RTE_GETREQUESTEDCOMMODE_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_HSMCOMMSFFULLCOMNOTIFIEDENTRY_ENTRY
/** \brief Entry point of function ComM_HsmComMSfFullComNotifiedEntry */
#define DBG_COMM_HSMCOMMSFFULLCOMNOTIFIEDENTRY_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFFULLCOMNOTIFIEDENTRY_EXIT
/** \brief Exit point of function ComM_HsmComMSfFullComNotifiedEntry */
#define DBG_COMM_HSMCOMMSFFULLCOMNOTIFIEDENTRY_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFFULLCOMNOTIFIEDACTION1_ENTRY
/** \brief Entry point of function ComM_HsmComMSfFullComNotifiedAction1 */
#define DBG_COMM_HSMCOMMSFFULLCOMNOTIFIEDACTION1_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFFULLCOMNOTIFIEDACTION1_EXIT
/** \brief Exit point of function ComM_HsmComMSfFullComNotifiedAction1 */
#define DBG_COMM_HSMCOMMSFFULLCOMNOTIFIEDACTION1_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMENTRY_ENTRY
/** \brief Entry point of function ComM_HsmComMSfAcceptLimitToNoComEntry */
#define DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMENTRY_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMENTRY_EXIT
/** \brief Exit point of function ComM_HsmComMSfAcceptLimitToNoComEntry */
#define DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMENTRY_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMACTION1_ENTRY
/** \brief Entry point of function ComM_HsmComMSfAcceptLimitToNoComAction1 */
#define DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMACTION1_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMACTION1_EXIT
/** \brief Exit point of function ComM_HsmComMSfAcceptLimitToNoComAction1 */
#define DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMACTION1_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMGUARD2_ENTRY
/** \brief Entry point of function ComM_HsmComMSfAcceptLimitToNoComGuard2 */
#define DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMGUARD2_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMGUARD2_EXIT
/** \brief Exit point of function ComM_HsmComMSfAcceptLimitToNoComGuard2 */
#define DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMGUARD2_EXIT(a,b)
#endif

#ifndef DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMACTION2_ENTRY
/** \brief Entry point of function ComM_HsmComMSfAcceptLimitToNoComAction2 */
#define DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMACTION2_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMACTION2_EXIT
/** \brief Exit point of function ComM_HsmComMSfAcceptLimitToNoComAction2 */
#define DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMACTION2_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMGUARD3_ENTRY
/** \brief Entry point of function ComM_HsmComMSfAcceptLimitToNoComGuard3 */
#define DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMGUARD3_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMGUARD3_EXIT
/** \brief Exit point of function ComM_HsmComMSfAcceptLimitToNoComGuard3 */
#define DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMGUARD3_EXIT(a,b)
#endif

#ifndef DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMACTION3_ENTRY
/** \brief Entry point of function ComM_HsmComMSfAcceptLimitToNoComAction3 */
#define DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMACTION3_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMACTION3_EXIT
/** \brief Exit point of function ComM_HsmComMSfAcceptLimitToNoComAction3 */
#define DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMACTION3_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFNETREQDELAYEDNONMENTRY_ENTRY
/** \brief Entry point of function ComM_HsmComMSfNetReqDelayedNoNmEntry */
#define DBG_COMM_HSMCOMMSFNETREQDELAYEDNONMENTRY_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFNETREQDELAYEDNONMENTRY_EXIT
/** \brief Exit point of function ComM_HsmComMSfNetReqDelayedNoNmEntry */
#define DBG_COMM_HSMCOMMSFNETREQDELAYEDNONMENTRY_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFNETREQDELAYEDNONMGUARD1_ENTRY
/** \brief Entry point of function ComM_HsmComMSfNetReqDelayedNoNmGuard1 */
#define DBG_COMM_HSMCOMMSFNETREQDELAYEDNONMGUARD1_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFNETREQDELAYEDNONMGUARD1_EXIT
/** \brief Exit point of function ComM_HsmComMSfNetReqDelayedNoNmGuard1 */
#define DBG_COMM_HSMCOMMSFNETREQDELAYEDNONMGUARD1_EXIT(a,b)
#endif

#ifndef DBG_COMM_HSMCOMMSFNETREQDELAYEDNONMGUARD2_ENTRY
/** \brief Entry point of function ComM_HsmComMSfNetReqDelayedNoNmGuard2 */
#define DBG_COMM_HSMCOMMSFNETREQDELAYEDNONMGUARD2_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFNETREQDELAYEDNONMGUARD2_EXIT
/** \brief Exit point of function ComM_HsmComMSfNetReqDelayedNoNmGuard2 */
#define DBG_COMM_HSMCOMMSFNETREQDELAYEDNONMGUARD2_EXIT(a,b)
#endif

#ifndef DBG_COMM_HSMCOMMSFNETREQDELAYEDNONMGUARD3_ENTRY
/** \brief Entry point of function ComM_HsmComMSfNetReqDelayedNoNmGuard3 */
#define DBG_COMM_HSMCOMMSFNETREQDELAYEDNONMGUARD3_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFNETREQDELAYEDNONMGUARD3_EXIT
/** \brief Exit point of function ComM_HsmComMSfNetReqDelayedNoNmGuard3 */
#define DBG_COMM_HSMCOMMSFNETREQDELAYEDNONMGUARD3_EXIT(a,b)
#endif

#ifndef DBG_COMM_HSMCOMMSFNETREQNMACTION1_ENTRY
/** \brief Entry point of function ComM_HsmComMSfNetReqNmAction1 */
#define DBG_COMM_HSMCOMMSFNETREQNMACTION1_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFNETREQNMACTION1_EXIT
/** \brief Exit point of function ComM_HsmComMSfNetReqNmAction1 */
#define DBG_COMM_HSMCOMMSFNETREQNMACTION1_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFNETREQNMGUARD2_ENTRY
/** \brief Entry point of function ComM_HsmComMSfNetReqNmGuard2 */
#define DBG_COMM_HSMCOMMSFNETREQNMGUARD2_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFNETREQNMGUARD2_EXIT
/** \brief Exit point of function ComM_HsmComMSfNetReqNmGuard2 */
#define DBG_COMM_HSMCOMMSFNETREQNMGUARD2_EXIT(a,b)
#endif

#ifndef DBG_COMM_HSMCOMMSFNETREQNMACTION2_ENTRY
/** \brief Entry point of function ComM_HsmComMSfNetReqNmAction2 */
#define DBG_COMM_HSMCOMMSFNETREQNMACTION2_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFNETREQNMACTION2_EXIT
/** \brief Exit point of function ComM_HsmComMSfNetReqNmAction2 */
#define DBG_COMM_HSMCOMMSFNETREQNMACTION2_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFNETREQNONMENTRY_ENTRY
/** \brief Entry point of function ComM_HsmComMSfNetReqNoNmEntry */
#define DBG_COMM_HSMCOMMSFNETREQNONMENTRY_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFNETREQNONMENTRY_EXIT
/** \brief Exit point of function ComM_HsmComMSfNetReqNoNmEntry */
#define DBG_COMM_HSMCOMMSFNETREQNONMENTRY_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFREADYSLEEPNMENTRY_ENTRY
/** \brief Entry point of function ComM_HsmComMSfReadySleepNmEntry */
#define DBG_COMM_HSMCOMMSFREADYSLEEPNMENTRY_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFREADYSLEEPNMENTRY_EXIT
/** \brief Exit point of function ComM_HsmComMSfReadySleepNmEntry */
#define DBG_COMM_HSMCOMMSFREADYSLEEPNMENTRY_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFREADYSLEEPNMGUARD1_ENTRY
/** \brief Entry point of function ComM_HsmComMSfReadySleepNmGuard1 */
#define DBG_COMM_HSMCOMMSFREADYSLEEPNMGUARD1_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFREADYSLEEPNMGUARD1_EXIT
/** \brief Exit point of function ComM_HsmComMSfReadySleepNmGuard1 */
#define DBG_COMM_HSMCOMMSFREADYSLEEPNMGUARD1_EXIT(a,b)
#endif

#ifndef DBG_COMM_HSMCOMMSFREADYSLEEPNMACTION1_ENTRY
/** \brief Entry point of function ComM_HsmComMSfReadySleepNmAction1 */
#define DBG_COMM_HSMCOMMSFREADYSLEEPNMACTION1_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFREADYSLEEPNMACTION1_EXIT
/** \brief Exit point of function ComM_HsmComMSfReadySleepNmAction1 */
#define DBG_COMM_HSMCOMMSFREADYSLEEPNMACTION1_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFREADYSLEEPNONMENTRY_ENTRY
/** \brief Entry point of function ComM_HsmComMSfReadySleepNoNmEntry */
#define DBG_COMM_HSMCOMMSFREADYSLEEPNONMENTRY_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFREADYSLEEPNONMENTRY_EXIT
/** \brief Exit point of function ComM_HsmComMSfReadySleepNoNmEntry */
#define DBG_COMM_HSMCOMMSFREADYSLEEPNONMENTRY_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFREADYSLEEPNONMGUARD1_ENTRY
/** \brief Entry point of function ComM_HsmComMSfReadySleepNoNmGuard1 */
#define DBG_COMM_HSMCOMMSFREADYSLEEPNONMGUARD1_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFREADYSLEEPNONMGUARD1_EXIT
/** \brief Exit point of function ComM_HsmComMSfReadySleepNoNmGuard1 */
#define DBG_COMM_HSMCOMMSFREADYSLEEPNONMGUARD1_EXIT(a,b)
#endif

#ifndef DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITENTRY_ENTRY
/** \brief Entry point of function ComM_HsmComMSfPassiveStartupWaitEntry */
#define DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITENTRY_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITENTRY_EXIT
/** \brief Exit point of function ComM_HsmComMSfPassiveStartupWaitEntry */
#define DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITENTRY_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITEXIT_ENTRY
/** \brief Entry point of function ComM_HsmComMSfPassiveStartupWaitExit */
#define DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITEXIT_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITEXIT_EXIT
/** \brief Exit point of function ComM_HsmComMSfPassiveStartupWaitExit */
#define DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITEXIT_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITGUARD1_ENTRY
/** \brief Entry point of function ComM_HsmComMSfPassiveStartupWaitGuard1 */
#define DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITGUARD1_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITGUARD1_EXIT
/** \brief Exit point of function ComM_HsmComMSfPassiveStartupWaitGuard1 */
#define DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITGUARD1_EXIT(a,b)
#endif

#ifndef DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITGUARD2_ENTRY
/** \brief Entry point of function ComM_HsmComMSfPassiveStartupWaitGuard2 */
#define DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITGUARD2_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITGUARD2_EXIT
/** \brief Exit point of function ComM_HsmComMSfPassiveStartupWaitGuard2 */
#define DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITGUARD2_EXIT(a,b)
#endif

#ifndef DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITACTION2_ENTRY
/** \brief Entry point of function ComM_HsmComMSfPassiveStartupWaitAction2 */
#define DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITACTION2_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITACTION2_EXIT
/** \brief Exit point of function ComM_HsmComMSfPassiveStartupWaitAction2 */
#define DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITACTION2_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITACTION3_ENTRY
/** \brief Entry point of function ComM_HsmComMSfPassiveStartupWaitAction3 */
#define DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITACTION3_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITACTION3_EXIT
/** \brief Exit point of function ComM_HsmComMSfPassiveStartupWaitAction3 */
#define DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITACTION3_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFREQNETWORKWAITENTRY_ENTRY
/** \brief Entry point of function ComM_HsmComMSfReqNetworkWaitEntry */
#define DBG_COMM_HSMCOMMSFREQNETWORKWAITENTRY_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFREQNETWORKWAITENTRY_EXIT
/** \brief Exit point of function ComM_HsmComMSfReqNetworkWaitEntry */
#define DBG_COMM_HSMCOMMSFREQNETWORKWAITENTRY_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFREQNETWORKWAITEXIT_ENTRY
/** \brief Entry point of function ComM_HsmComMSfReqNetworkWaitExit */
#define DBG_COMM_HSMCOMMSFREQNETWORKWAITEXIT_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFREQNETWORKWAITEXIT_EXIT
/** \brief Exit point of function ComM_HsmComMSfReqNetworkWaitExit */
#define DBG_COMM_HSMCOMMSFREQNETWORKWAITEXIT_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFWAITFORFULLCOMENTRY_ENTRY
/** \brief Entry point of function ComM_HsmComMSfWaitForFullComEntry */
#define DBG_COMM_HSMCOMMSFWAITFORFULLCOMENTRY_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFWAITFORFULLCOMENTRY_EXIT
/** \brief Exit point of function ComM_HsmComMSfWaitForFullComEntry */
#define DBG_COMM_HSMCOMMSFWAITFORFULLCOMENTRY_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFWAITFORFULLCOMEXIT_ENTRY
/** \brief Entry point of function ComM_HsmComMSfWaitForFullComExit */
#define DBG_COMM_HSMCOMMSFWAITFORFULLCOMEXIT_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFWAITFORFULLCOMEXIT_EXIT
/** \brief Exit point of function ComM_HsmComMSfWaitForFullComExit */
#define DBG_COMM_HSMCOMMSFWAITFORFULLCOMEXIT_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFWAITFORFULLCOMACTION1_ENTRY
/** \brief Entry point of function ComM_HsmComMSfWaitForFullComAction1 */
#define DBG_COMM_HSMCOMMSFWAITFORFULLCOMACTION1_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFWAITFORFULLCOMACTION1_EXIT
/** \brief Exit point of function ComM_HsmComMSfWaitForFullComAction1 */
#define DBG_COMM_HSMCOMMSFWAITFORFULLCOMACTION1_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFWAITFORFULLCOMGUARD3_ENTRY
/** \brief Entry point of function ComM_HsmComMSfWaitForFullComGuard3 */
#define DBG_COMM_HSMCOMMSFWAITFORFULLCOMGUARD3_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFWAITFORFULLCOMGUARD3_EXIT
/** \brief Exit point of function ComM_HsmComMSfWaitForFullComGuard3 */
#define DBG_COMM_HSMCOMMSFWAITFORFULLCOMGUARD3_EXIT(a,b)
#endif

#ifndef DBG_COMM_HSMCOMMSFWFFCTONETREQACTIVEGUARD1_ENTRY
/** \brief Entry point of function ComM_HsmComMSfWffcToNetReqActiveGuard1 */
#define DBG_COMM_HSMCOMMSFWFFCTONETREQACTIVEGUARD1_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFWFFCTONETREQACTIVEGUARD1_EXIT
/** \brief Exit point of function ComM_HsmComMSfWffcToNetReqActiveGuard1 */
#define DBG_COMM_HSMCOMMSFWFFCTONETREQACTIVEGUARD1_EXIT(a,b)
#endif

#ifndef DBG_COMM_HSMCOMMSFWFFCTONETREQACTIVEACTION1_ENTRY
/** \brief Entry point of function ComM_HsmComMSfWffcToNetReqActiveAction1 */
#define DBG_COMM_HSMCOMMSFWFFCTONETREQACTIVEACTION1_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFWFFCTONETREQACTIVEACTION1_EXIT
/** \brief Exit point of function ComM_HsmComMSfWffcToNetReqActiveAction1 */
#define DBG_COMM_HSMCOMMSFWFFCTONETREQACTIVEACTION1_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFWFFCTONETREQPASSIVEGUARD1_ENTRY
/** \brief Entry point of function ComM_HsmComMSfWffcToNetReqPassiveGuard1 */
#define DBG_COMM_HSMCOMMSFWFFCTONETREQPASSIVEGUARD1_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFWFFCTONETREQPASSIVEGUARD1_EXIT
/** \brief Exit point of function ComM_HsmComMSfWffcToNetReqPassiveGuard1 */
#define DBG_COMM_HSMCOMMSFWFFCTONETREQPASSIVEGUARD1_EXIT(a,b)
#endif

#ifndef DBG_COMM_HSMCOMMSFWFFCTONETREQPASSIVEACTION1_ENTRY
/** \brief Entry point of function ComM_HsmComMSfWffcToNetReqPassiveAction1 */
#define DBG_COMM_HSMCOMMSFWFFCTONETREQPASSIVEACTION1_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFWFFCTONETREQPASSIVEACTION1_EXIT
/** \brief Exit point of function ComM_HsmComMSfWffcToNetReqPassiveAction1 */
#define DBG_COMM_HSMCOMMSFWFFCTONETREQPASSIVEACTION1_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFNOPENDINGREQUESTGUARD4_ENTRY
/** \brief Entry point of function ComM_HsmComMSfNoPendingRequestGuard4 */
#define DBG_COMM_HSMCOMMSFNOPENDINGREQUESTGUARD4_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFNOPENDINGREQUESTGUARD4_EXIT
/** \brief Exit point of function ComM_HsmComMSfNoPendingRequestGuard4 */
#define DBG_COMM_HSMCOMMSFNOPENDINGREQUESTGUARD4_EXIT(a,b)
#endif

#ifndef DBG_COMM_HSMCOMMSFNOCOMFIRSTENTRY_ENTRY
/** \brief Entry point of function ComM_HsmComMSfNoComFirstEntry */
#define DBG_COMM_HSMCOMMSFNOCOMFIRSTENTRY_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFNOCOMFIRSTENTRY_EXIT
/** \brief Exit point of function ComM_HsmComMSfNoComFirstEntry */
#define DBG_COMM_HSMCOMMSFNOCOMFIRSTENTRY_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFNOCOMNOTIFEDENTRY_ENTRY
/** \brief Entry point of function ComM_HsmComMSfNoComNotifedEntry */
#define DBG_COMM_HSMCOMMSFNOCOMNOTIFEDENTRY_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFNOCOMNOTIFEDENTRY_EXIT
/** \brief Exit point of function ComM_HsmComMSfNoComNotifedEntry */
#define DBG_COMM_HSMCOMMSFNOCOMNOTIFEDENTRY_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFWAITFORNOCOMENTRY_ENTRY
/** \brief Entry point of function ComM_HsmComMSfWaitForNoComEntry */
#define DBG_COMM_HSMCOMMSFWAITFORNOCOMENTRY_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFWAITFORNOCOMENTRY_EXIT
/** \brief Exit point of function ComM_HsmComMSfWaitForNoComEntry */
#define DBG_COMM_HSMCOMMSFWAITFORNOCOMENTRY_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFWAITFORNOCOMEXIT_ENTRY
/** \brief Entry point of function ComM_HsmComMSfWaitForNoComExit */
#define DBG_COMM_HSMCOMMSFWAITFORNOCOMEXIT_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFWAITFORNOCOMEXIT_EXIT
/** \brief Exit point of function ComM_HsmComMSfWaitForNoComExit */
#define DBG_COMM_HSMCOMMSFWAITFORNOCOMEXIT_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFPENDINGREQUESTENTRY_ENTRY
/** \brief Entry point of function ComM_HsmComMSfPendingRequestEntry */
#define DBG_COMM_HSMCOMMSFPENDINGREQUESTENTRY_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFPENDINGREQUESTENTRY_EXIT
/** \brief Exit point of function ComM_HsmComMSfPendingRequestEntry */
#define DBG_COMM_HSMCOMMSFPENDINGREQUESTENTRY_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFPENDINGREQUESTGUARD1_ENTRY
/** \brief Entry point of function ComM_HsmComMSfPendingRequestGuard1 */
#define DBG_COMM_HSMCOMMSFPENDINGREQUESTGUARD1_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFPENDINGREQUESTGUARD1_EXIT
/** \brief Exit point of function ComM_HsmComMSfPendingRequestGuard1 */
#define DBG_COMM_HSMCOMMSFPENDINGREQUESTGUARD1_EXIT(a,b)
#endif

#ifndef DBG_COMM_HSMCOMMSFREQRUNACTIVEGUARD1_ENTRY
/** \brief Entry point of function ComM_HsmComMSfReqRunActiveGuard1 */
#define DBG_COMM_HSMCOMMSFREQRUNACTIVEGUARD1_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFREQRUNACTIVEGUARD1_EXIT
/** \brief Exit point of function ComM_HsmComMSfReqRunActiveGuard1 */
#define DBG_COMM_HSMCOMMSFREQRUNACTIVEGUARD1_EXIT(a,b)
#endif

#ifndef DBG_COMM_HSMCOMMSFREQRUNACTIVEGUARD2_ENTRY
/** \brief Entry point of function ComM_HsmComMSfReqRunActiveGuard2 */
#define DBG_COMM_HSMCOMMSFREQRUNACTIVEGUARD2_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFREQRUNACTIVEGUARD2_EXIT
/** \brief Exit point of function ComM_HsmComMSfReqRunActiveGuard2 */
#define DBG_COMM_HSMCOMMSFREQRUNACTIVEGUARD2_EXIT(a,b)
#endif

#ifndef DBG_COMM_HSMCOMMSFREQRUNPASSIVEGUARD1_ENTRY
/** \brief Entry point of function ComM_HsmComMSfReqRunPassiveGuard1 */
#define DBG_COMM_HSMCOMMSFREQRUNPASSIVEGUARD1_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFREQRUNPASSIVEGUARD1_EXIT
/** \brief Exit point of function ComM_HsmComMSfReqRunPassiveGuard1 */
#define DBG_COMM_HSMCOMMSFREQRUNPASSIVEGUARD1_EXIT(a,b)
#endif

#ifndef DBG_COMM_HSMCOMMSFSILENTCOMACTION1_ENTRY
/** \brief Entry point of function ComM_HsmComMSfSilentComAction1 */
#define DBG_COMM_HSMCOMMSFSILENTCOMACTION1_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFSILENTCOMACTION1_EXIT
/** \brief Exit point of function ComM_HsmComMSfSilentComAction1 */
#define DBG_COMM_HSMCOMMSFSILENTCOMACTION1_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFSILENTCOMGUARD3_ENTRY
/** \brief Entry point of function ComM_HsmComMSfSilentComGuard3 */
#define DBG_COMM_HSMCOMMSFSILENTCOMGUARD3_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFSILENTCOMGUARD3_EXIT
/** \brief Exit point of function ComM_HsmComMSfSilentComGuard3 */
#define DBG_COMM_HSMCOMMSFSILENTCOMGUARD3_EXIT(a,b)
#endif

#ifndef DBG_COMM_HSMCOMMSFSILENTCOMNOTIFEDENTRY_ENTRY
/** \brief Entry point of function ComM_HsmComMSfSilentComNotifedEntry */
#define DBG_COMM_HSMCOMMSFSILENTCOMNOTIFEDENTRY_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFSILENTCOMNOTIFEDENTRY_EXIT
/** \brief Exit point of function ComM_HsmComMSfSilentComNotifedEntry */
#define DBG_COMM_HSMCOMMSFSILENTCOMNOTIFEDENTRY_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFWAITFORSILENTCOMENTRY_ENTRY
/** \brief Entry point of function ComM_HsmComMSfWaitForSilentComEntry */
#define DBG_COMM_HSMCOMMSFWAITFORSILENTCOMENTRY_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFWAITFORSILENTCOMENTRY_EXIT
/** \brief Exit point of function ComM_HsmComMSfWaitForSilentComEntry */
#define DBG_COMM_HSMCOMMSFWAITFORSILENTCOMENTRY_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFWAITFORSILENTCOMEXIT_ENTRY
/** \brief Entry point of function ComM_HsmComMSfWaitForSilentComExit */
#define DBG_COMM_HSMCOMMSFWAITFORSILENTCOMEXIT_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMSFWAITFORSILENTCOMEXIT_EXIT
/** \brief Exit point of function ComM_HsmComMSfWaitForSilentComExit */
#define DBG_COMM_HSMCOMMSFWAITFORSILENTCOMEXIT_EXIT(a)
#endif

#ifndef DBG_COMM_NOTIFY_ENTRY
/** \brief Entry point of function ComM_Notify */
#define DBG_COMM_NOTIFY_ENTRY(a,b)
#endif

#ifndef DBG_COMM_NOTIFY_EXIT
/** \brief Exit point of function ComM_Notify */
#define DBG_COMM_NOTIFY_EXIT(a,b)
#endif

#ifndef DBG_COMM_BUSSMREQUESTCOMMODE_ENTRY
/** \brief Entry point of function ComM_BusSmRequestComMode */
#define DBG_COMM_BUSSMREQUESTCOMMODE_ENTRY(a,b)
#endif

#ifndef DBG_COMM_BUSSMREQUESTCOMMODE_EXIT
/** \brief Exit point of function ComM_BusSmRequestComMode */
#define DBG_COMM_BUSSMREQUESTCOMMODE_EXIT(a,b)
#endif

#ifndef DBG_COMM_CHECKNWR_ENTRY
/** \brief Entry point of function ComM_CheckNwr */
#define DBG_COMM_CHECKNWR_ENTRY(a)
#endif

#ifndef DBG_COMM_CHECKNWR_EXIT
/** \brief Exit point of function ComM_CheckNwr */
#define DBG_COMM_CHECKNWR_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMPNCSFPNCPREPARESLEEPACTION1_ENTRY
/** \brief Entry point of function ComM_HsmComMPncSfPncPrepareSleepAction1 */
#define DBG_COMM_HSMCOMMPNCSFPNCPREPARESLEEPACTION1_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMPNCSFPNCPREPARESLEEPACTION1_EXIT
/** \brief Exit point of function ComM_HsmComMPncSfPncPrepareSleepAction1 */
#define DBG_COMM_HSMCOMMPNCSFPNCPREPARESLEEPACTION1_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMPNCSFPNCPREPARESLEEPACTION2_ENTRY
/** \brief Entry point of function ComM_HsmComMPncSfPncPrepareSleepAction2 */
#define DBG_COMM_HSMCOMMPNCSFPNCPREPARESLEEPACTION2_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMPNCSFPNCPREPARESLEEPACTION2_EXIT
/** \brief Exit point of function ComM_HsmComMPncSfPncPrepareSleepAction2 */
#define DBG_COMM_HSMCOMMPNCSFPNCPREPARESLEEPACTION2_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMPNCSFPNCREADYSLEEPENTRY_ENTRY
/** \brief Entry point of function ComM_HsmComMPncSfPncReadySleepEntry */
#define DBG_COMM_HSMCOMMPNCSFPNCREADYSLEEPENTRY_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMPNCSFPNCREADYSLEEPENTRY_EXIT
/** \brief Exit point of function ComM_HsmComMPncSfPncReadySleepEntry */
#define DBG_COMM_HSMCOMMPNCSFPNCREADYSLEEPENTRY_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMPNCSFPNCREADYSLEEPGUARD1_ENTRY
/** \brief Entry point of function ComM_HsmComMPncSfPncReadySleepGuard1 */
#define DBG_COMM_HSMCOMMPNCSFPNCREADYSLEEPGUARD1_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMPNCSFPNCREADYSLEEPGUARD1_EXIT
/** \brief Exit point of function ComM_HsmComMPncSfPncReadySleepGuard1 */
#define DBG_COMM_HSMCOMMPNCSFPNCREADYSLEEPGUARD1_EXIT(a,b)
#endif

#ifndef DBG_COMM_HSMCOMMPNCSFPNCREQUESTEDENTRY_ENTRY
/** \brief Entry point of function ComM_HsmComMPncSfPncRequestedEntry */
#define DBG_COMM_HSMCOMMPNCSFPNCREQUESTEDENTRY_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMPNCSFPNCREQUESTEDENTRY_EXIT
/** \brief Exit point of function ComM_HsmComMPncSfPncRequestedEntry */
#define DBG_COMM_HSMCOMMPNCSFPNCREQUESTEDENTRY_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMPNCSFPNCREQUESTEDACTION1_ENTRY
/** \brief Entry point of function ComM_HsmComMPncSfPncRequestedAction1 */
#define DBG_COMM_HSMCOMMPNCSFPNCREQUESTEDACTION1_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMPNCSFPNCREQUESTEDACTION1_EXIT
/** \brief Exit point of function ComM_HsmComMPncSfPncRequestedAction1 */
#define DBG_COMM_HSMCOMMPNCSFPNCREQUESTEDACTION1_EXIT(a)
#endif

#ifndef DBG_COMM_HSMCOMMPNCSFPNCNOCOMGUARD1_ENTRY
/** \brief Entry point of function ComM_HsmComMPncSfPncNoComGuard1 */
#define DBG_COMM_HSMCOMMPNCSFPNCNOCOMGUARD1_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMPNCSFPNCNOCOMGUARD1_EXIT
/** \brief Exit point of function ComM_HsmComMPncSfPncNoComGuard1 */
#define DBG_COMM_HSMCOMMPNCSFPNCNOCOMGUARD1_EXIT(a,b)
#endif

#ifndef DBG_COMM_HSMCOMMPNCSFPNCNOCOMGUARD2_ENTRY
/** \brief Entry point of function ComM_HsmComMPncSfPncNoComGuard2 */
#define DBG_COMM_HSMCOMMPNCSFPNCNOCOMGUARD2_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMPNCSFPNCNOCOMGUARD2_EXIT
/** \brief Exit point of function ComM_HsmComMPncSfPncNoComGuard2 */
#define DBG_COMM_HSMCOMMPNCSFPNCNOCOMGUARD2_EXIT(a,b)
#endif

#ifndef DBG_COMM_HSMCOMMPNCSFPNCNOCOMNOTIFYENTRY_ENTRY
/** \brief Entry point of function ComM_HsmComMPncSfPncNoComNotifyEntry */
#define DBG_COMM_HSMCOMMPNCSFPNCNOCOMNOTIFYENTRY_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMCOMMPNCSFPNCNOCOMNOTIFYENTRY_EXIT
/** \brief Exit point of function ComM_HsmComMPncSfPncNoComNotifyEntry */
#define DBG_COMM_HSMCOMMPNCSFPNCNOCOMNOTIFYENTRY_EXIT(a)
#endif

#ifndef DBG_COMM_NMNWREQALLCHOFPNC_ENTRY
/** \brief Entry point of function ComM_NmNwReqAllChOfPnc */
#define DBG_COMM_NMNWREQALLCHOFPNC_ENTRY(a)
#endif

#ifndef DBG_COMM_NMNWREQALLCHOFPNC_EXIT
/** \brief Exit point of function ComM_NmNwReqAllChOfPnc */
#define DBG_COMM_NMNWREQALLCHOFPNC_EXIT(a)
#endif

#ifndef DBG_COMM_PNCGETEIRA_ENTRY
/** \brief Entry point of function ComM_PncGetEIRA */
#define DBG_COMM_PNCGETEIRA_ENTRY(a)
#endif

#ifndef DBG_COMM_PNCGETEIRA_EXIT
/** \brief Exit point of function ComM_PncGetEIRA */
#define DBG_COMM_PNCGETEIRA_EXIT(a,b)
#endif

#ifndef DBG_COMM_PNCSENDSIGNAL_ENTRY
/** \brief Entry point of function ComM_PncSendSignal */
#define DBG_COMM_PNCSENDSIGNAL_ENTRY(a)
#endif

#ifndef DBG_COMM_PNCSENDSIGNAL_EXIT
/** \brief Exit point of function ComM_PncSendSignal */
#define DBG_COMM_PNCSENDSIGNAL_EXIT(a)
#endif

#ifndef DBG_COMM_PNCPROCESSTIMERS_ENTRY
/** \brief Entry point of function ComM_PncProcessTimers */
#define DBG_COMM_PNCPROCESSTIMERS_ENTRY()
#endif

#ifndef DBG_COMM_PNCPROCESSTIMERS_EXIT
/** \brief Exit point of function ComM_PncProcessTimers */
#define DBG_COMM_PNCPROCESSTIMERS_EXIT()
#endif

#ifndef DBG_COMM_SETCHANNELACTIVESTATUS_ENTRY
/** \brief Entry point of function ComM_SetChannelActiveStatus */
#define DBG_COMM_SETCHANNELACTIVESTATUS_ENTRY(a,b)
#endif

#ifndef DBG_COMM_SETCHANNELACTIVESTATUS_EXIT
/** \brief Exit point of function ComM_SetChannelActiveStatus */
#define DBG_COMM_SETCHANNELACTIVESTATUS_EXIT(a,b)
#endif

#ifndef DBG_COMM_HSMINIT_ENTRY
/** \brief Entry point of function ComM_HsmInit */
#define DBG_COMM_HSMINIT_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMINIT_EXIT
/** \brief Exit point of function ComM_HsmInit */
#define DBG_COMM_HSMINIT_EXIT(a)
#endif

#ifndef DBG_COMM_HSMINITINST_ENTRY
/** \brief Entry point of function COMM_HSMINITINST */
#define DBG_COMM_HSMINITINST_ENTRY(a,b)
#endif

#ifndef DBG_COMM_HSMINITINST_EXIT
/** \brief Exit point of function COMM_HSMINITINST */
#define DBG_COMM_HSMINITINST_EXIT(a,b)
#endif

#ifndef DBG_COMM_HSMEMIT_ENTRY
/** \brief Entry point of function ComM_HsmEmit */
#define DBG_COMM_HSMEMIT_ENTRY(a,b)
#endif

#ifndef DBG_COMM_HSMEMIT_EXIT
/** \brief Exit point of function ComM_HsmEmit */
#define DBG_COMM_HSMEMIT_EXIT(a,b)
#endif

#ifndef DBG_COMM_HSMEMITINST_ENTRY
/** \brief Entry point of function COMM_HSMEMITINST */
#define DBG_COMM_HSMEMITINST_ENTRY(a,b,c)
#endif

#ifndef DBG_COMM_HSMEMITINST_EXIT
/** \brief Exit point of function COMM_HSMEMITINST */
#define DBG_COMM_HSMEMITINST_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_HSMEMITTOSELFINST_ENTRY
/** \brief Entry point of function COMM_HSMEMITTOSELFINST */
#define DBG_COMM_HSMEMITTOSELFINST_ENTRY(a,b,c)
#endif

#ifndef DBG_COMM_HSMEMITTOSELFINST_EXIT
/** \brief Exit point of function COMM_HSMEMITTOSELFINST */
#define DBG_COMM_HSMEMITTOSELFINST_EXIT(a,b,c)
#endif


#ifndef DBG_COMM_HSMMAININST_ENTRY
/** \brief Entry point of function COMM_HSMMAININST */
#define DBG_COMM_HSMMAININST_ENTRY(a,b)
#endif

#ifndef DBG_COMM_HSMMAININST_EXIT
/** \brief Exit point of function COMM_HSMMAININST */
#define DBG_COMM_HSMMAININST_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_HSMSETTRACING_ENTRY
/** \brief Entry point of function ComM_HsmSetTracing */
#define DBG_COMM_HSMSETTRACING_ENTRY(a)
#endif

#ifndef DBG_COMM_HSMSETTRACING_EXIT
/** \brief Exit point of function ComM_HsmSetTracing */
#define DBG_COMM_HSMSETTRACING_EXIT(a)
#endif

#ifndef DBG_COMM_HSM_DEL_FROM_QUEUE_ENTRY
/** \brief Entry point of function COMM_HSM_DEL_FROM_QUEUE */
#define DBG_COMM_HSM_DEL_FROM_QUEUE_ENTRY(a,b,c)
#endif

#ifndef DBG_COMM_HSM_DEL_FROM_QUEUE_EXIT
/** \brief Exit point of function COMM_HSM_DEL_FROM_QUEUE */
#define DBG_COMM_HSM_DEL_FROM_QUEUE_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_HSM_TRAN_ENTRY
/** \brief Entry point of function COMM_HSM_TRAN */
#define DBG_COMM_HSM_TRAN_ENTRY(a,b,c)
#endif

#ifndef DBG_COMM_HSM_TRAN_EXIT
/** \brief Exit point of function COMM_HSM_TRAN */
#define DBG_COMM_HSM_TRAN_EXIT(a,b,c)
#endif

#ifndef DBG_COMM_HSM_INIT_SUBSTATES_ENTRY
/** \brief Entry point of function COMM_HSM_INIT_SUBSTATES */
#define DBG_COMM_HSM_INIT_SUBSTATES_ENTRY(a,b)
#endif

#ifndef DBG_COMM_HSM_INIT_SUBSTATES_EXIT
/** \brief Exit point of function COMM_HSM_INIT_SUBSTATES */
#define DBG_COMM_HSM_INIT_SUBSTATES_EXIT(a,b)
#endif

#ifndef DBG_COMM_HSM_FIND_EV_TO_DISPATCH_ENTRY
/** \brief Entry point of function COMM_HSM_FIND_EV_TO_DISPATCH */
#define DBG_COMM_HSM_FIND_EV_TO_DISPATCH_ENTRY(a,b,c,d)
#endif

#ifndef DBG_COMM_HSM_FIND_EV_TO_DISPATCH_EXIT
/** \brief Exit point of function COMM_HSM_FIND_EV_TO_DISPATCH */
#define DBG_COMM_HSM_FIND_EV_TO_DISPATCH_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_COMM_HSM_DISPATCH_EVENT_ENTRY
/** \brief Entry point of function COMM_HSM_DISPATCH_EVENT */
#define DBG_COMM_HSM_DISPATCH_EVENT_ENTRY(a,b,c)
#endif

#ifndef DBG_COMM_HSM_DISPATCH_EVENT_EXIT
/** \brief Exit point of function COMM_HSM_DISPATCH_EVENT */
#define DBG_COMM_HSM_DISPATCH_EVENT_EXIT(a,b,c,d)
#endif


/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[external data]=========================================*/

#endif /* (!defined COMM_TRACE_H) */
/*==================[end of file]===========================================*/
