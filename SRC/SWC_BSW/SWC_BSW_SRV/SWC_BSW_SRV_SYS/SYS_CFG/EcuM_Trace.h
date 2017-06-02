/**
 * \file
 *
 * \brief AUTOSAR EcuM
 *
 * This file contains the implementation of the AUTOSAR
 * module EcuM.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#if (!defined ECUM_TRACE_H)
#define ECUM_TRACE_H
/*==================[inclusions]============================================*/



/*==================[macros]================================================*/

#ifndef DBG_ECUM_AL_RESET_ENTRY
/** \brief Entry point of function EcuM_AL_Reset() */
#define DBG_ECUM_AL_RESET_ENTRY(a)
#endif

#ifndef DBG_ECUM_AL_RESET_EXIT
/** \brief Exit point of function EcuM_AL_Reset() */
#define DBG_ECUM_AL_RESET_EXIT(a)
#endif

#ifndef DBG_ECUM_AL_SETPROGRAMMABLEINTERRUPTS_ENTRY
/** \brief Entry point of function EcuM_AL_SetProgrammableInterrupts() */
#define DBG_ECUM_AL_SETPROGRAMMABLEINTERRUPTS_ENTRY()
#endif

#ifndef DBG_ECUM_AL_SETPROGRAMMABLEINTERRUPTS_EXIT
/** \brief Exit point of function EcuM_AL_SetProgrammableInterrupts() */
#define DBG_ECUM_AL_SETPROGRAMMABLEINTERRUPTS_EXIT()
#endif

#ifndef DBG_ECUM_AL_SWITCHOFF_ENTRY
/** \brief Entry point of function EcuM_AL_SwitchOff() */
#define DBG_ECUM_AL_SWITCHOFF_ENTRY()
#endif

#ifndef DBG_ECUM_AL_SWITCHOFF_EXIT
/** \brief Exit point of function EcuM_AL_SwitchOff() */
#define DBG_ECUM_AL_SWITCHOFF_EXIT()
#endif

#ifndef DBG_ECUM_CHECKRAMHASH_ENTRY
/** \brief Entry point of function EcuM_CheckRamHash() */
#define DBG_ECUM_CHECKRAMHASH_ENTRY()
#endif

#ifndef DBG_ECUM_CHECKRAMHASH_EXIT
/** \brief Exit point of function EcuM_CheckRamHash() */
#define DBG_ECUM_CHECKRAMHASH_EXIT(a)
#endif

#ifndef DBG_ECUM_CHECKVALIDATION_ENTRY
/** \brief Entry point of function EcuM_CheckValidation() */
#define DBG_ECUM_CHECKVALIDATION_ENTRY(a)
#endif

#ifndef DBG_ECUM_CHECKVALIDATION_EXIT
/** \brief Exit point of function EcuM_CheckValidation() */
#define DBG_ECUM_CHECKVALIDATION_EXIT(a)
#endif

#ifndef DBG_ECUM_CHECKWAKEUP_ENTRY
/** \brief Entry point of function EcuM_CheckWakeup() */
#define DBG_ECUM_CHECKWAKEUP_ENTRY(a)
#endif

#ifndef DBG_ECUM_CHECKWAKEUP_EXIT
/** \brief Exit point of function EcuM_CheckWakeup() */
#define DBG_ECUM_CHECKWAKEUP_EXIT(a)
#endif

#ifndef DBG_ECUM_CLEARWAKEUPEVENT_ENTRY
/** \brief Entry point of function EcuM_ClearWakeupEvent() */
#define DBG_ECUM_CLEARWAKEUPEVENT_ENTRY(a)
#endif

#ifndef DBG_ECUM_CLEARWAKEUPEVENT_EXIT
/** \brief Exit point of function EcuM_ClearWakeupEvent() */
#define DBG_ECUM_CLEARWAKEUPEVENT_EXIT(a)
#endif

#ifndef DBG_ECUM_COMMWAKEUPINDICATION_ENTRY
/** \brief Entry point of function EcuM_ComMWakeupIndication() */
#define DBG_ECUM_COMMWAKEUPINDICATION_ENTRY(a)
#endif

#ifndef DBG_ECUM_COMMWAKEUPINDICATION_EXIT
/** \brief Exit point of function EcuM_ComMWakeupIndication() */
#define DBG_ECUM_COMMWAKEUPINDICATION_EXIT(a)
#endif

#ifndef DBG_ECUM_DETERMINEPBCONFIGURATION_ENTRY
/** \brief Entry point of function EcuM_DeterminePbConfiguration() */
#define DBG_ECUM_DETERMINEPBCONFIGURATION_ENTRY()
#endif

#ifndef DBG_ECUM_DETERMINEPBCONFIGURATION_EXIT
/** \brief Exit point of function EcuM_DeterminePbConfiguration() */
#define DBG_ECUM_DETERMINEPBCONFIGURATION_EXIT()
#endif

#ifndef DBG_ECUM_DISABLEWAKEUPSOURCES_ENTRY
/** \brief Entry point of function EcuM_DisableWakeupSources() */
#define DBG_ECUM_DISABLEWAKEUPSOURCES_ENTRY(a)
#endif

#ifndef DBG_ECUM_DISABLEWAKEUPSOURCES_EXIT
/** \brief Exit point of function EcuM_DisableWakeupSources() */
#define DBG_ECUM_DISABLEWAKEUPSOURCES_EXIT(a)
#endif

#ifndef DBG_ECUM_ENABLEWAKEUPSOURCES_ENTRY
/** \brief Entry point of function EcuM_EnableWakeupSources() */
#define DBG_ECUM_ENABLEWAKEUPSOURCES_ENTRY(a)
#endif

#ifndef DBG_ECUM_ENABLEWAKEUPSOURCES_EXIT
/** \brief Exit point of function EcuM_EnableWakeupSources() */
#define DBG_ECUM_ENABLEWAKEUPSOURCES_EXIT(a)
#endif

#ifndef DBG_ECUM_GENERATERAMHASH_ENTRY
/** \brief Entry point of function EcuM_GenerateRamHash() */
#define DBG_ECUM_GENERATERAMHASH_ENTRY()
#endif

#ifndef DBG_ECUM_GENERATERAMHASH_EXIT
/** \brief Exit point of function EcuM_GenerateRamHash() */
#define DBG_ECUM_GENERATERAMHASH_EXIT()
#endif

#ifndef DBG_ECUM_GETBOOTTARGET_ENTRY
/** \brief Entry point of function EcuM_GetBootTarget() */
#define DBG_ECUM_GETBOOTTARGET_ENTRY(a)
#endif

#ifndef DBG_ECUM_GETBOOTTARGET_EXIT
/** \brief Exit point of function EcuM_GetBootTarget() */
#define DBG_ECUM_GETBOOTTARGET_EXIT(a,b)
#endif

#ifndef DBG_ECUM_GETEXPIREDWAKEUPEVENTS_ENTRY
/** \brief Entry point of function EcuM_GetExpiredWakeupEvents() */
#define DBG_ECUM_GETEXPIREDWAKEUPEVENTS_ENTRY()
#endif

#ifndef DBG_ECUM_GETEXPIREDWAKEUPEVENTS_EXIT
/** \brief Exit point of function EcuM_GetExpiredWakeupEvents() */
#define DBG_ECUM_GETEXPIREDWAKEUPEVENTS_EXIT(a)
#endif

#ifndef DBG_ECUM_GETLASTSHUTDOWNTARGET_ENTRY
/** \brief Entry point of function EcuM_GetLastShutdownTarget() */
#define DBG_ECUM_GETLASTSHUTDOWNTARGET_ENTRY(a,b)
#endif

#ifndef DBG_ECUM_GETLASTSHUTDOWNTARGET_EXIT
/** \brief Exit point of function EcuM_GetLastShutdownTarget() */
#define DBG_ECUM_GETLASTSHUTDOWNTARGET_EXIT(a,b,c)
#endif

#ifndef DBG_ECUM_GETMOSTRECENTSHUTDOWN_ENTRY
/** \brief Entry point of function EcuM_GetMostRecentShutdown() */
#define DBG_ECUM_GETMOSTRECENTSHUTDOWN_ENTRY(a,b,c,d)
#endif

#ifndef DBG_ECUM_GETMOSTRECENTSHUTDOWN_EXIT
/** \brief Exit point of function EcuM_GetMostRecentShutdown() */
#define DBG_ECUM_GETMOSTRECENTSHUTDOWN_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_ECUM_GETNEXTRECENTSHUTDOWN_ENTRY
/** \brief Entry point of function EcuM_GetNextRecentShutdown() */
#define DBG_ECUM_GETNEXTRECENTSHUTDOWN_ENTRY(a,b,c,d)
#endif

#ifndef DBG_ECUM_GETNEXTRECENTSHUTDOWN_EXIT
/** \brief Exit point of function EcuM_GetNextRecentShutdown() */
#define DBG_ECUM_GETNEXTRECENTSHUTDOWN_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_ECUM_GETPENDINGWAKEUPEVENTS_ENTRY
/** \brief Entry point of function EcuM_GetPendingWakeupEvents() */
#define DBG_ECUM_GETPENDINGWAKEUPEVENTS_ENTRY()
#endif

#ifndef DBG_ECUM_GETPENDINGWAKEUPEVENTS_EXIT
/** \brief Exit point of function EcuM_GetPendingWakeupEvents() */
#define DBG_ECUM_GETPENDINGWAKEUPEVENTS_EXIT(a)
#endif

#ifndef DBG_ECUM_GETSHUTDOWNCAUSE_ENTRY
/** \brief Entry point of function EcuM_GetShutdownCause() */
#define DBG_ECUM_GETSHUTDOWNCAUSE_ENTRY(a)
#endif

#ifndef DBG_ECUM_GETSHUTDOWNCAUSE_EXIT
/** \brief Exit point of function EcuM_GetShutdownCause() */
#define DBG_ECUM_GETSHUTDOWNCAUSE_EXIT(a,b)
#endif

#ifndef DBG_ECUM_GETSHUTDOWNTARGET_ENTRY
/** \brief Entry point of function EcuM_GetShutdownTarget() */
#define DBG_ECUM_GETSHUTDOWNTARGET_ENTRY(a,b)
#endif

#ifndef DBG_ECUM_GETSHUTDOWNTARGET_EXIT
/** \brief Exit point of function EcuM_GetShutdownTarget() */
#define DBG_ECUM_GETSHUTDOWNTARGET_EXIT(a,b,c)
#endif

#ifndef DBG_ECUM_GETSTATUSOFWAKEUPSOURCE_ENTRY
/** \brief Entry point of function EcuM_GetStatusOfWakeupSource() */
#define DBG_ECUM_GETSTATUSOFWAKEUPSOURCE_ENTRY(a)
#endif

#ifndef DBG_ECUM_GETSTATUSOFWAKEUPSOURCE_EXIT
/** \brief Exit point of function EcuM_GetStatusOfWakeupSource() */
#define DBG_ECUM_GETSTATUSOFWAKEUPSOURCE_EXIT(a,b)
#endif

#ifndef DBG_ECUM_GETVALIDATEDWAKEUPEVENTS_ENTRY
/** \brief Entry point of function EcuM_GetValidatedWakeupEvents() */
#define DBG_ECUM_GETVALIDATEDWAKEUPEVENTS_ENTRY()
#endif

#ifndef DBG_ECUM_GETVALIDATEDWAKEUPEVENTS_EXIT
/** \brief Exit point of function EcuM_GetValidatedWakeupEvents() */
#define DBG_ECUM_GETVALIDATEDWAKEUPEVENTS_EXIT(a)
#endif

#ifndef DBG_ECUM_GETVERSIONINFO_ENTRY
/** \brief Entry point of function EcuM_GetVersionInfo() */
#define DBG_ECUM_GETVERSIONINFO_ENTRY(a)
#endif

#ifndef DBG_ECUM_GETVERSIONINFO_EXIT
/** \brief Exit point of function EcuM_GetVersionInfo() */
#define DBG_ECUM_GETVERSIONINFO_EXIT(a)
#endif

#ifndef DBG_ECUM_GODOWN_ENTRY
/** \brief Entry point of function EcuM_GoDown() */
#define DBG_ECUM_GODOWN_ENTRY(a)
#endif

#ifndef DBG_ECUM_GODOWN_EXIT
/** \brief Exit point of function EcuM_GoDown() */
#define DBG_ECUM_GODOWN_EXIT(a,b)
#endif

#ifndef DBG_ECUM_GOHALT_ENTRY
/** \brief Entry point of function EcuM_GoHalt() */
#define DBG_ECUM_GOHALT_ENTRY()
#endif

#ifndef DBG_ECUM_GOHALT_EXIT
/** \brief Exit point of function EcuM_GoHalt() */
#define DBG_ECUM_GOHALT_EXIT(a)
#endif

#ifndef DBG_ECUM_GOHALTORPOLL_ENTRY
/** \brief Entry point of function EcuM_GoHaltOrPoll() */
#define DBG_ECUM_GOHALTORPOLL_ENTRY(a)
#endif

#ifndef DBG_ECUM_GOHALTORPOLL_EXIT
/** \brief Exit point of function EcuM_GoHaltOrPoll() */
#define DBG_ECUM_GOHALTORPOLL_EXIT(a,b)
#endif

#ifndef DBG_ECUM_GOPOLL_ENTRY
/** \brief Entry point of function EcuM_GoPoll() */
#define DBG_ECUM_GOPOLL_ENTRY()
#endif

#ifndef DBG_ECUM_GOPOLL_EXIT
/** \brief Exit point of function EcuM_GoPoll() */
#define DBG_ECUM_GOPOLL_EXIT(a)
#endif

#ifndef DBG_ECUM_GORUN_ENTRY
/** \brief Entry point of function EcuM_GoRun() */
#define DBG_ECUM_GORUN_ENTRY()
#endif

#ifndef DBG_ECUM_GORUN_EXIT
/** \brief Exit point of function EcuM_GoRun() */
#define DBG_ECUM_GORUN_EXIT(a)
#endif

#ifndef DBG_ECUM_GOSLEEP_ENTRY
/** \brief Entry point of function EcuM_GoSleep() */
#define DBG_ECUM_GOSLEEP_ENTRY()
#endif

#ifndef DBG_ECUM_GOSLEEP_EXIT
/** \brief Exit point of function EcuM_GoSleep() */
#define DBG_ECUM_GOSLEEP_EXIT()
#endif

#ifndef DBG_ECUM_HANDLERUNREQUESTS_ENTRY
/** \brief Entry point of function EcuM_HandleRunrequests() */
#define DBG_ECUM_HANDLERUNREQUESTS_ENTRY()
#endif

#ifndef DBG_ECUM_HANDLERUNREQUESTS_EXIT
/** \brief Exit point of function EcuM_HandleRunrequests() */
#define DBG_ECUM_HANDLERUNREQUESTS_EXIT()
#endif

#ifndef DBG_ECUM_INIT_ENTRY
/** \brief Entry point of function EcuM_Init() */
#define DBG_ECUM_INIT_ENTRY()
#endif

#ifndef DBG_ECUM_INIT_EXIT
/** \brief Exit point of function EcuM_Init() */
#define DBG_ECUM_INIT_EXIT()
#endif

#ifndef DBG_ECUM_ISPOSTRUNREQ_ENTRY
/** \brief Entry point of function EcuM_IsPostRunReq() */
#define DBG_ECUM_ISPOSTRUNREQ_ENTRY()
#endif

#ifndef DBG_ECUM_ISPOSTRUNREQ_EXIT
/** \brief Exit point of function EcuM_IsPostRunReq() */
#define DBG_ECUM_ISPOSTRUNREQ_EXIT(a)
#endif

#ifndef DBG_ECUM_ISRUNREQ_ENTRY
/** \brief Entry point of function EcuM_IsRunReq() */
#define DBG_ECUM_ISRUNREQ_ENTRY()
#endif

#ifndef DBG_ECUM_ISRUNREQ_EXIT
/** \brief Exit point of function EcuM_IsRunReq() */
#define DBG_ECUM_ISRUNREQ_EXIT(a)
#endif

#ifndef DBG_ECUM_KILLALLRUNREQUESTS_ENTRY
/** \brief Entry point of function EcuM_KillAllRUNRequests() */
#define DBG_ECUM_KILLALLRUNREQUESTS_ENTRY()
#endif

#ifndef DBG_ECUM_KILLALLRUNREQUESTS_EXIT
/** \brief Exit point of function EcuM_KillAllRUNRequests() */
#define DBG_ECUM_KILLALLRUNREQUESTS_EXIT()
#endif

#ifndef DBG_ECUM_MAINFUNCTION_ENTRY
/** \brief Entry point of function EcuM_MainFunction() */
#define DBG_ECUM_MAINFUNCTION_ENTRY()
#endif

#ifndef DBG_ECUM_MAINFUNCTION_EXIT
/** \brief Exit point of function EcuM_MainFunction() */
#define DBG_ECUM_MAINFUNCTION_EXIT()
#endif

#ifndef DBG_ECUM_ONGOOFFONE_ENTRY
/** \brief Entry point of function EcuM_OnGoOffOne() */
#define DBG_ECUM_ONGOOFFONE_ENTRY()
#endif

#ifndef DBG_ECUM_ONGOOFFONE_EXIT
/** \brief Exit point of function EcuM_OnGoOffOne() */
#define DBG_ECUM_ONGOOFFONE_EXIT()
#endif

#ifndef DBG_ECUM_ONGOOFFTWO_ENTRY
/** \brief Entry point of function EcuM_OnGoOffTwo() */
#define DBG_ECUM_ONGOOFFTWO_ENTRY()
#endif

#ifndef DBG_ECUM_ONGOOFFTWO_EXIT
/** \brief Exit point of function EcuM_OnGoOffTwo() */
#define DBG_ECUM_ONGOOFFTWO_EXIT()
#endif

#ifndef DBG_ECUM_POSTHALT_ENTRY
/** \brief Entry point of function EcuM_PostHalt() */
#define DBG_ECUM_POSTHALT_ENTRY()
#endif

#ifndef DBG_ECUM_POSTHALT_EXIT
/** \brief Exit point of function EcuM_PostHalt() */
#define DBG_ECUM_POSTHALT_EXIT()
#endif

#ifndef DBG_ECUM_PREHALT_ENTRY
/** \brief Entry point of function EcuM_PreHalt() */
#define DBG_ECUM_PREHALT_ENTRY()
#endif

#ifndef DBG_ECUM_PREHALT_EXIT
/** \brief Exit point of function EcuM_PreHalt() */
#define DBG_ECUM_PREHALT_EXIT()
#endif

#ifndef DBG_ECUM_RELEASEPOST_RUN_ENTRY
/** \brief Entry point of function EcuM_ReleasePOST_RUN() */
#define DBG_ECUM_RELEASEPOST_RUN_ENTRY(a)
#endif

#ifndef DBG_ECUM_RELEASEPOST_RUN_EXIT
/** \brief Exit point of function EcuM_ReleasePOST_RUN() */
#define DBG_ECUM_RELEASEPOST_RUN_EXIT(a,b)
#endif

#ifndef DBG_ECUM_RELEASERUN_ENTRY
/** \brief Entry point of function EcuM_ReleaseRUN() */
#define DBG_ECUM_RELEASERUN_ENTRY(a)
#endif

#ifndef DBG_ECUM_RELEASERUN_EXIT
/** \brief Exit point of function EcuM_ReleaseRUN() */
#define DBG_ECUM_RELEASERUN_EXIT(a,b)
#endif

#ifndef DBG_ECUM_REQUESTPOST_RUN_ENTRY
/** \brief Entry point of function EcuM_RequestPOST_RUN() */
#define DBG_ECUM_REQUESTPOST_RUN_ENTRY(a)
#endif

#ifndef DBG_ECUM_REQUESTPOST_RUN_EXIT
/** \brief Exit point of function EcuM_RequestPOST_RUN() */
#define DBG_ECUM_REQUESTPOST_RUN_EXIT(a,b)
#endif

#ifndef DBG_ECUM_REQUESTRUN_ENTRY
/** \brief Entry point of function EcuM_RequestRUN() */
#define DBG_ECUM_REQUESTRUN_ENTRY(a)
#endif

#ifndef DBG_ECUM_REQUESTRUN_EXIT
/** \brief Exit point of function EcuM_RequestRUN() */
#define DBG_ECUM_REQUESTRUN_EXIT(a,b)
#endif

#ifndef DBG_ECUM_SELECTBOOTTARGET_ENTRY
/** \brief Entry point of function EcuM_SelectBootTarget() */
#define DBG_ECUM_SELECTBOOTTARGET_ENTRY(a)
#endif

#ifndef DBG_ECUM_SELECTBOOTTARGET_EXIT
/** \brief Exit point of function EcuM_SelectBootTarget() */
#define DBG_ECUM_SELECTBOOTTARGET_EXIT(a,b)
#endif

#ifndef DBG_ECUM_SELECTSHUTDOWNCAUSE_ENTRY
/** \brief Entry point of function EcuM_SelectShutdownCause() */
#define DBG_ECUM_SELECTSHUTDOWNCAUSE_ENTRY(a)
#endif

#ifndef DBG_ECUM_SELECTSHUTDOWNCAUSE_EXIT
/** \brief Exit point of function EcuM_SelectShutdownCause() */
#define DBG_ECUM_SELECTSHUTDOWNCAUSE_EXIT(a,b)
#endif

#ifndef DBG_ECUM_SELECTSHUTDOWNTARGET_ENTRY
/** \brief Entry point of function EcuM_SelectShutdownTarget() */
#define DBG_ECUM_SELECTSHUTDOWNTARGET_ENTRY(a,b)
#endif

#ifndef DBG_ECUM_SELECTSHUTDOWNTARGET_EXIT
/** \brief Exit point of function EcuM_SelectShutdownTarget() */
#define DBG_ECUM_SELECTSHUTDOWNTARGET_EXIT(a,b,c)
#endif

#ifndef DBG_ECUM_SETWAKEUPEVENT_ENTRY
/** \brief Entry point of function EcuM_SetWakeupEvent() */
#define DBG_ECUM_SETWAKEUPEVENT_ENTRY(a)
#endif

#ifndef DBG_ECUM_SETWAKEUPEVENT_EXIT
/** \brief Exit point of function EcuM_SetWakeupEvent() */
#define DBG_ECUM_SETWAKEUPEVENT_EXIT(a)
#endif

#ifndef DBG_ECUM_SHUTDOWN_ENTRY
/** \brief Entry point of function EcuM_Shutdown() */
#define DBG_ECUM_SHUTDOWN_ENTRY()
#endif

#ifndef DBG_ECUM_SHUTDOWN_EXIT
/** \brief Exit point of function EcuM_Shutdown() */
#define DBG_ECUM_SHUTDOWN_EXIT()
#endif

#ifndef DBG_ECUM_SLEEPACTIVITY_ENTRY
/** \brief Entry point of function EcuM_SleepActivity() */
#define DBG_ECUM_SLEEPACTIVITY_ENTRY()
#endif

#ifndef DBG_ECUM_SLEEPACTIVITY_EXIT
/** \brief Exit point of function EcuM_SleepActivity() */
#define DBG_ECUM_SLEEPACTIVITY_EXIT()
#endif

#ifndef DBG_ECUM_STARTUPTWO_ENTRY
/** \brief Entry point of function EcuM_StartupTwo() */
#define DBG_ECUM_STARTUPTWO_ENTRY()
#endif

#ifndef DBG_ECUM_STARTUPTWO_EXIT
/** \brief Exit point of function EcuM_StartupTwo() */
#define DBG_ECUM_STARTUPTWO_EXIT()
#endif

#ifndef DBG_ECUM_STARTWAKEUPSOURCES_ENTRY
/** \brief Entry point of function EcuM_StartWakeupSources() */
#define DBG_ECUM_STARTWAKEUPSOURCES_ENTRY(a)
#endif

#ifndef DBG_ECUM_STARTWAKEUPSOURCES_EXIT
/** \brief Exit point of function EcuM_StartWakeupSources() */
#define DBG_ECUM_STARTWAKEUPSOURCES_EXIT(a)
#endif

#ifndef DBG_ECUM_STOPWAKEUPSOURCES_ENTRY
/** \brief Entry point of function EcuM_StopWakeupSources() */
#define DBG_ECUM_STOPWAKEUPSOURCES_ENTRY(a)
#endif

#ifndef DBG_ECUM_STOPWAKEUPSOURCES_EXIT
/** \brief Exit point of function EcuM_StopWakeupSources() */
#define DBG_ECUM_STOPWAKEUPSOURCES_EXIT(a)
#endif

#ifndef DBG_SHUTDOWNHOOK_ENTRY
/** \brief Entry point of function ShutdownHook() */
#define DBG_SHUTDOWNHOOK_ENTRY(a)
#endif

#ifndef DBG_SHUTDOWNHOOK_EXIT
/** \brief Exit point of function ShutdownHook() */
#define DBG_SHUTDOWNHOOK_EXIT(a)
#endif

#ifndef DBG_ECUM_SWITCHWAKEUPSTATUS_ENTRY
/** \brief Entry point of function EcuM_SwitchWakeupStatus() */
#define DBG_ECUM_SWITCHWAKEUPSTATUS_ENTRY(a,b)
#endif

#ifndef DBG_ECUM_SWITCHWAKEUPSTATUS_EXIT
/** \brief Exit point of function EcuM_SwitchWakeupStatus() */
#define DBG_ECUM_SWITCHWAKEUPSTATUS_EXIT(a,b)
#endif

#ifndef DBG_ECUM_VALIDATEWAKEUPEVENT_ENTRY
/** \brief Entry point of function EcuM_ValidateWakeupEvent() */
#define DBG_ECUM_VALIDATEWAKEUPEVENT_ENTRY(a)
#endif

#ifndef DBG_ECUM_VALIDATEWAKEUPEVENT_EXIT
/** \brief Exit point of function EcuM_ValidateWakeupEvent() */
#define DBG_ECUM_VALIDATEWAKEUPEVENT_EXIT(a)
#endif

#ifndef DBG_ECUM_WAKEUPRESTART_ENTRY
/** \brief Entry point of function EcuM_WakeupRestart() */
#define DBG_ECUM_WAKEUPRESTART_ENTRY()
#endif

#ifndef DBG_ECUM_WAKEUPRESTART_EXIT
/** \brief Exit point of function EcuM_WakeupRestart() */
#define DBG_ECUM_WAKEUPRESTART_EXIT()
#endif

#ifndef DBG_ECUM_WKSINDICATESTATUS_DISABLED_ENTRY
/** \brief Entry point of function EcuM_WksIndicateStatus_DISABLED() */
#define DBG_ECUM_WKSINDICATESTATUS_DISABLED_ENTRY()
#endif

#ifndef DBG_ECUM_WKSINDICATESTATUS_DISABLED_EXIT
/** \brief Exit point of function EcuM_WksIndicateStatus_DISABLED() */
#define DBG_ECUM_WKSINDICATESTATUS_DISABLED_EXIT()
#endif

#ifndef DBG_ECUM_WKSINDICATESTATUS_EXPIRED_ENTRY
/** \brief Entry point of function EcuM_WksIndicateStatus_EXPIRED() */
#define DBG_ECUM_WKSINDICATESTATUS_EXPIRED_ENTRY()
#endif

#ifndef DBG_ECUM_WKSINDICATESTATUS_EXPIRED_EXIT
/** \brief Exit point of function EcuM_WksIndicateStatus_EXPIRED() */
#define DBG_ECUM_WKSINDICATESTATUS_EXPIRED_EXIT()
#endif

#ifndef DBG_ECUM_WKSINDICATESTATUS_NONE_ENTRY
/** \brief Entry point of function EcuM_WksIndicateStatus_NONE() */
#define DBG_ECUM_WKSINDICATESTATUS_NONE_ENTRY()
#endif

#ifndef DBG_ECUM_WKSINDICATESTATUS_NONE_EXIT
/** \brief Exit point of function EcuM_WksIndicateStatus_NONE() */
#define DBG_ECUM_WKSINDICATESTATUS_NONE_EXIT()
#endif

#ifndef DBG_ECUM_WKSINDICATESTATUS_PENDING_ENTRY
/** \brief Entry point of function EcuM_WksIndicateStatus_PENDING() */
#define DBG_ECUM_WKSINDICATESTATUS_PENDING_ENTRY()
#endif

#ifndef DBG_ECUM_WKSINDICATESTATUS_PENDING_EXIT
/** \brief Exit point of function EcuM_WksIndicateStatus_PENDING() */
#define DBG_ECUM_WKSINDICATESTATUS_PENDING_EXIT()
#endif

#ifndef DBG_ECUM_WKSINDICATESTATUS_VALIDATED_ENTRY
/** \brief Entry point of function EcuM_WksIndicateStatus_VALIDATED() */
#define DBG_ECUM_WKSINDICATESTATUS_VALIDATED_ENTRY()
#endif

#ifndef DBG_ECUM_WKSINDICATESTATUS_VALIDATED_EXIT
/** \brief Exit point of function EcuM_WksIndicateStatus_VALIDATED() */
#define DBG_ECUM_WKSINDICATESTATUS_VALIDATED_EXIT()
#endif

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[external data]=========================================*/

#endif /* (!defined ECUM_TRACE_H) */
/*==================[end of file]===========================================*/
