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
/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 16.4 (required)
 *     The identifiers used in the declaration and definition of a function
 *     shall be identical.
 *
 *     Reason:
 *     The requirement 'EcuM3011' defines the arguments of EcuM_ShutdownTarget
 *     (ClientServerInterface EcuM_ShutdownTarget) as 'target' and 'mode' but the
 *     EcuM API specification defines the arguments as 'shutdownTarget' and
 *     'sleepMode' respectively. This issue has been reported in
 *     http://www.autosar.org/bugzilla/show_bug.cgi?id=58147
 *
 *  MISRA-2) Deviated Rule: 16.10 (required)
 *     If a function returns error information, then that error information
 *     should be tested.
 *
 *     Reason:
 *     If the Os scheduler resource RES_SCHEDULER cannot be taken, the EcuM
 *     shall continue operating as specified.  Therefore, the error information
 *     returned by Os functions GetResource or ReleaseResource is not used.
 *
 *  MISRA-3) Deviated Rule: 12.13 (required)
 *     The increment (++) and decrement (--) operators should not be mixed with
 *     other operators in an expression.
 *
 *     Reason:
 *     The Os provides the implementation for the macros GetResource and
 *     ReleaseResource.
 *
 *  MISRA-4) Deviated Rule: 12.10 (required)
 *     The comma operator shall not be used.
 *
 *     Reason:
 *     The Os provides the implementation for the macros GetResource and
 *     ReleaseResource.
 */

/* !LINKSTO EcuM3023,1 */
/*==================[inclusions]============================================*/

#include <EcuM_Trace.h>
#include <Os.h>                  /* Os public API */

#include <Std_Types.h>           /* AUTOSAR standard types */
#include <TSAutosar.h>           /* EB specific standard types */

#include <Mcu.h>                 /* Mcu API */

#include <EcuM_BSW.h>            /* Module API */
#include <EcuM_Cbk.h>            /* Module callback/callout API */
#include <EcuM_Int.h>            /* Module internal API */
#include <EcuM_Cfg.h>            /* Module configuration */

/* !LINKSTO EcuM2862,1 */
#include <BswM_EcuM.h>           /* BswM callback API */
#include <BswM.h>                /* BswM API, for BswM_Init() and _Deinit() */

/* Include ComM_EcuM.h only if wakeup sources associated with ComM Channel are
 * available */
#if (ECUM_WKS_COMMCH_ENABLED == STD_ON)
#include <ComM_EcuMBswM.h>       /* ComM callback API */
#include <ComM.h>
#endif

/*==================[macros]================================================*/
/* !LINKSTO EcuM.Version.Check,1 */
/*------------------[AUTOSAR vendor identification check]-------------------*/

#if (!defined ECUM_VENDOR_ID) /* configuration check */
#error ECUM_VENDOR_ID must be defined
#endif

#if (ECUM_VENDOR_ID != 1U) /* vendor check */
#error ECUM_VENDOR_ID has wrong vendor id
#endif

/*------------------[AUTOSAR release version identification check]----------*/

#if (!defined ECUM_AR_RELEASE_MAJOR_VERSION) /* configuration check */
#error ECUM_AR_RELEASE_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (ECUM_AR_RELEASE_MAJOR_VERSION != 4U)
#error ECUM_AR_RELEASE_MAJOR_VERSION wrong (!= 4U)
#endif

#if (!defined ECUM_AR_RELEASE_MINOR_VERSION) /* configuration check */
#error ECUM_AR_RELEASE_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (ECUM_AR_RELEASE_MINOR_VERSION != 0U )
#error ECUM_AR_RELEASE_MINOR_VERSION wrong (!= 0U)
#endif

#if (!defined ECUM_AR_RELEASE_REVISION_VERSION) /* configuration check */
#error ECUM_AR_RELEASE_REVISION_VERSION must be defined
#endif

/* revision version check */
#if (ECUM_AR_RELEASE_REVISION_VERSION != 3U )
#error ECUM_AR_RELEASE_REVISION_VERSION wrong (!= 3U)
#endif

/*------------------[AUTOSAR module version identification check]-----------*/

#if (!defined ECUM_SW_MAJOR_VERSION) /* configuration check */
#error ECUM_SW_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (ECUM_SW_MAJOR_VERSION != 5U)
#error ECUM_SW_MAJOR_VERSION wrong (!= 5U)
#endif

#if (!defined ECUM_SW_MINOR_VERSION) /* configuration check */
#error ECUM_SW_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (ECUM_SW_MINOR_VERSION < 4U)
#error ECUM_SW_MINOR_VERSION wrong (< 4U)
#endif

#if (!defined ECUM_SW_PATCH_VERSION) /* configuration check */
#error ECUM_SW_PATCH_VERSION must be defined
#endif

/* patch version check */
#if (ECUM_SW_PATCH_VERSION < 17U)
#error ECUM_SW_PATCH_VERSION wrong (< 17U)
#endif

#if defined(MCU_WATCHDOG_RESET)
/** \brief Check for unintended restart by MCU
 ** \param McuReset Mcu reset reason
 **
 ** The implementation of this macro depends on the availablility of the Mcu
 ** reset reason MCU_WATCHDOG_RESET which is optional (see MCU134). */
# define ECUM_MCU_RESET_IS_UNINTENDED(McuReset) \
  (((McuReset) == MCU_POWER_ON_RESET)           \
   || (((McuReset) == MCU_RESET_UNDEFINED)      \
       || ((McuReset) == MCU_WATCHDOG_RESET)))
#else
# define ECUM_MCU_RESET_IS_UNINTENDED(McuReset) \
  (((McuReset) == MCU_POWER_ON_RESET)           \
   || ((McuReset) == MCU_RESET_UNDEFINED))
#endif


#if (ECUM_INCLUDE_DEM == STD_ON)
#if (ECUM_PROD_ERR_RAM_CHECK_FAILURE == TS_PROD_ERR_REP_TO_DEM)
/** \brief Status of RAM integrity check for reporting the error to DEM */
#define ECUM_RAM_CHECK_STATUS_UNTESTED  0U
#define ECUM_RAM_CHECK_STATUS_PASSED    1U
#define ECUM_RAM_CHECK_STATUS_FAILED    2U
#endif /* (ECUM_PROD_ERR_RAM_CHECK_FAILURE == TS_PROD_ERR_REP_TO_DEM) */

#if (ECUM_ECUM_FIXED_SUPPORT == STD_ON)
#define ECUM_E_ALL_RUN_REQUESTS_KILLED  1U
#endif /* (ECUM_ECUM_FIXED_SUPPORT == STD_ON) */

#endif /* (ECUM_INCLUDE_DEM == STD_ON) */

#if (ECUM_ECUM_FIXED_SUPPORT == STD_ON)

#define ECUM_FIXED_USER_BITMAP_SIZE  (((ECUM_FIXED_NUM_FIXED_USERS)/7U)+1U)
#define ECUM_BSWM_UNINIT    0U
#define ECUM_BSWM_INIT      1U
#define ECUM_BSWM_GO_RUN    2U
#define ECUM_BSWM_RUNNING   3U

#if (defined ECUM_EB_RTEMODESWITCH)
#error ECUM_EB_RTEMODESWITCH already defined
#endif
#if (ECUM_EB_DEFAULT_ASR_SERVICE_API != ECUM_EB_SERVICE_API_NONE)
/** \brief Signaling mode change via RTE
 *
 * The macro receives the new mode from the EcuM point of view and
 * propagates the arguments to the corresponding default RTE handle function.
 *
 * If the default service API is set to NONE then the macro is defined empty.
 *
 * \param[in] mode  new mode
 */
#define ECUM_EB_RTEMODESWITCH(mode) EcuM_RteModeSwitch(mode)
#else
#define ECUM_EB_RTEMODESWITCH(mode)
#endif

#if (defined ECUM_EB_ASR32_RTEMODESWITCH)
#error ECUM_EB_ASR32_RTEMODESWITCH already defined
#endif
#if (ECUM_EB_ENABLE_ASR32_SERVICE_API == STD_ON)
/** \brief Signaling mode change via RTE
 *
 * The macro receives the new mode from the EcuM point of view and
 * propagates the arguments to the corresponding Autosar 3.2 RTE handle function.
 *
 * If the AUTOSAR 3.2 service API is not configured then the macro is defined empty.
 *
 * \param[in] mode  new mode
 */
#define ECUM_EB_ASR32_RTEMODESWITCH(mode) EcuM_ASR32_RteModeSwitch(mode)
#else
#define ECUM_EB_ASR32_RTEMODESWITCH(mode)
#endif

#if (defined ECUM_EB_ASR40_RTEMODESWITCH)
#error ECUM_EB_ASR40_RTEMODESWITCH already defined
#endif
#if (ECUM_EB_ENABLE_ASR40_SERVICE_API == STD_ON)
/** \brief Signaling mode change via RTE
 *
 * The macro receives the new mode from the EcuM point of view and
 * propagates the arguments to the corresponding Autosar 4.0 RTE handle function.
 *
 * If the AUTOSAR 4.0 service API is not configured then the macro is defined empty.
 *
 * \param[in] mode  new mode
 */
#define ECUM_EB_ASR40_RTEMODESWITCH(mode) EcuM_ASR40_RteModeSwitch(mode)
#else
#define ECUM_EB_ASR40_RTEMODESWITCH(mode)
#endif

#if (defined ECUM_EB_CURRENT_MODE_SWITCH)
#error ECUM_EB_CURRENT_MODE_SWITCH already defined
#endif
#define ECUM_EB_CURRENT_MODE_SWITCH(mode) \
  do { \
    ECUM_EB_RTEMODESWITCH((mode)); \
    ECUM_EB_ASR32_RTEMODESWITCH((mode)); \
    ECUM_EB_ASR40_RTEMODESWITCH((mode)); \
  } while (0)

#endif /* (ECUM_ECUM_FIXED_SUPPORT == STD_ON) */
/*==================[type definitions]======================================*/

typedef struct
{
  /** \brief configured shutdown target */
  EcuM_ASR40_StateType         target;

  /** \brief configured sleep/reset mode */
  uint8                        mode;

  /** \brief real cause of shutdown */
  EcuM_ASR40_ShutdownCauseType cause;

  /** \brief time at which the shutdown happened */
  uint32                       sdTime;
} EcuM_ShutdownInfoType;

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

#define ECUM_START_SEC_CODE
#include <MemMap.h>

/** Executes the activities of the GoSleep Sequence. */
STATIC FUNC(void, ECUM_CODE) EcuM_GoSleep(void);

/** Executes the activities of the WakeupRestart Sequence. */
STATIC FUNC(void, ECUM_CODE) EcuM_WakeupRestart(void);

#if (ECUM_ECUM_FIXED_SUPPORT == STD_ON)
/** Performs the required actions for RUN and POST_RUN requests. */
STATIC FUNC(void, ECUM_CODE) EcuM_HandleRunRequests(void);
#endif

/** \brief Switch the status of wakeup sources
 **
 ** \param[in] sources  The wakeup sources to transition.
 ** \param[in] status   The new status of the wakeup sources.
 **
 ** \par The following values may be passed to this function:
 ** \li ECUM_WKSTATUS_DISABLED (super-state and leaf-state)
 ** \li ECUM_WKSTATUS_ENABLED (super-state)
 ** \li ECUM_WKSTATUS_EXPIRED
 ** \li ECUM_WKSTATUS_NONE
 ** \li ECUM_WKSTATUS_PENDING
 ** \li ECUM_WKSTATUS_VALIDATED
 **
 ** Because the wakeup source state machine is broken in the ASR-4.0.3 SWS, a
 ** wakeup source may be disabled or enabled and in one the following states:
 ** EXPIRED, NONE, PENDING or VALIDATED.  Therefore, ENABLE has been introduced
 ** as a super-state of NONE, PENDING, VALDIATED and EXPIRED.  DISABLED serves
 ** as a super-state of DISABLED (itself), NONE, PENDING, VALDIATED and EXPIRED.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous} */
STATIC FUNC(void, ECUM_CODE) EcuM_SwitchWakeupStatus
(
  EcuM_WakeupSourceType sources,
  EcuM_WakeupStatusType status
);
/** \brief Indicates the wakeup source changes to ECUM_WKSTATUS_DISABLED. */
STATIC FUNC(void, ECUM_CODE) EcuM_WksIndicateStatus_DISABLED(void);
/** \brief Indicates the wakeup source changes to ECUM_WKSTATUS_EXPIRED. */
STATIC FUNC(void, ECUM_CODE) EcuM_WksIndicateStatus_EXPIRED(void);
/** \brief Indicates the wakeup source changes to ECUM_WKSTATUS_NONE. */
STATIC FUNC(void, ECUM_CODE) EcuM_WksIndicateStatus_NONE(void);
/** \brief Indicates the wakeup source changes to ECUM_WKSTATUS_PENDING. */
STATIC FUNC(void, ECUM_CODE) EcuM_WksIndicateStatus_PENDING(void);
/** \brief Indicates the wakeup source changes to ECUM_WKSTATUS_VALIDATED. */
STATIC FUNC(void, ECUM_CODE) EcuM_WksIndicateStatus_VALIDATED(void);
/* Function to indicate the wakeup status to ComM channels. Indicates
 * the wakeup status to ComM channels only when ComM has been
 * successfully initialized */
#if (ECUM_WKS_COMMCH_ENABLED == STD_ON)
STATIC FUNC(void, ECUM_CODE)EcuM_ComMWakeupIndication
(
  EcuM_WakeupSourceType ComMevents
);
#endif

#if (ECUM_ECUM_FIXED_SUPPORT == STD_ON)
STATIC FUNC(boolean, ECUM_CODE)EcuM_IsRunReq(void);
STATIC FUNC(boolean, ECUM_CODE)EcuM_IsPostRunReq(void);
#endif /* (ECUM_ECUM_FIXED_SUPPORT == STD_ON) */
#define ECUM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/* --------------[init variables]------------------------------------------ */

#define ECUM_START_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

VAR(EcuM_ASR40_StateType, ECUM_VAR) EcuM_State = ECUM_STATE_UNINIT;

#define ECUM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[internal data]=========================================*/

/* --------------[power on init variables]--------------------------------- */
#if (ECUM_ECUM_FIXED_SUPPORT == STD_ON)
#define ECUM_START_SEC_VAR_INIT_8
#include <MemMap.h>
/* STATIC VAR(uint8, ECUM_VAR) EcuM_FixedState = ECUM_FIXED_STATE_INVALID; */
STATIC VAR(uint8, ECUM_VAR) EcuM_RunReq[ECUM_FIXED_USER_BITMAP_SIZE] = {0U};
STATIC VAR(uint8, ECUM_VAR) EcuM_PostRunReq[ECUM_FIXED_USER_BITMAP_SIZE] = {0U};
#define ECUM_STOP_SEC_VAR_INIT_8
#include <MemMap.h>
#define ECUM_START_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>
STATIC VAR(boolean, ECUM_VAR) EcuM_KillAllRUNRequested = FALSE;
#define ECUM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>
#endif /* (ECUM_ECUM_FIXED_SUPPORT == STD_ON) */

#define ECUM_START_SEC_INTERNAL_VAR_POWER_ON_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief Last shutdown target
 *
 * This variable holds the shutdown target used in last shutdown sequence.
 *
 * It is unspecified in the SWS what last shutdown target shall be reported as
 * default not shutdown sequence was performed after a power on.
 *
 * This variable must survive ECU resets.*/
STATIC VAR(EcuM_ASR40_StateType, ECUM_VAR_POWER_ON_INIT) EcuM_LastShutdownTarget
  = ECUM_STATE_OFF;

/** \brief Previous shutdown information
 **
 ** This variable holds all the previous shutdown information which contains
 ** shutdown target, cause of shutdown, time and sleep mode.
 **
 ** This variable must survive ECU resets. */
STATIC VAR(EcuM_ShutdownInfoType, ECUM_VAR_POWER_ON_INIT)
  EcuM_ShutdownInfo[ECUM_STORED_SHUTDOWN_OPERATIONS];

#define ECUM_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_UNSPECIFIED
#include <MemMap.h>

#define ECUM_START_SEC_VAR_POWER_ON_INIT_8
#include <MemMap.h>

/** \brief Last Sleep Mode
 **
 ** This variable holds the sleep mode of the last sleep sequence.
 **
 ** This variable must survive ECU resets. */
STATIC VAR(uint8, ECUM_VAR_POWER_ON_INIT) EcuM_LastSleepMode;

/** \brief Last Reset Mode
 **
 ** This variable holds the reset mode of the last reset sequence.
 **
 ** This variable must survive ECU resets. */
STATIC VAR(uint8, ECUM_VAR_POWER_ON_INIT) EcuM_LastResetMode;

/** \brief Starting index of the buffer which stores the shutdown information.
 **
 ** This variable holds the starting point of the buffer which is having all
 ** the recent shutdown information. The shutdown information is retrieved
 ** with the help of EcuM_ShutdownInfoCurrentIdx, which points to the current
 ** location of the buffer. To get all the stored information, iterate the
 ** current index point till it reaches the start index. Once the buffer is
 ** filled to the maximum capacity, the starting index point shifts forward
 ** and works as an index to ring buffer.
 **
 ** This variable must survive ECU resets. */
STATIC VAR(uint8, ECUM_VAR_POWER_ON_INIT) EcuM_ShutdownInfoStartIdx = 0U;

/** \brief Current location of the buffer which stores the shutdown
 ** information.
 **
 ** This variable holds the current location of the buffer which stores the
 ** shutdown information. The stored shutdown inforamtion are retrieved by
 ** iterationg this index till it reaches EcuM_ShutdownInfoStartIdx.
 **
 ** This variable must survive ECU resets. */
STATIC VAR(uint8, ECUM_VAR_POWER_ON_INIT) EcuM_ShutdownInfoCurrentIdx = 0U;

#if (ECUM_INCLUDE_DEM == STD_ON) \
 && (ECUM_PROD_ERR_RAM_CHECK_FAILURE == TS_PROD_ERR_REP_TO_DEM)
/** \brief variable to store the status of a failed RAM check
 **
 ** Content of variable will be updated in SLEEP phase(Halt sequence)
 ** and will be evaluated after reset in up phase */
STATIC VAR(uint8, ECUM_VAR_POWER_ON_INIT) EcuM_RamCheckStatus
    = ECUM_RAM_CHECK_STATUS_UNTESTED;
#endif

#define ECUM_STOP_SEC_VAR_POWER_ON_INIT_8
#include <MemMap.h>

/* --------------[no init variables]--------------------------------------- */

#define ECUM_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>

/** \brief Current sleep mode for shutdown
 **
 ** This variable holds the current sleep mode used in the next
 ** shutdown sequence. */
STATIC VAR(uint8, ECUM_VAR_NOINIT) EcuM_SleepMode;

/** \brief Current reset mode for Ecu Reset
 **
 ** This variable holds the current reset mode used in the next
 ** shutdown sequence if the selected shutdown target is ECUM_STATE_RESET. */
STATIC VAR(uint8, ECUM_VAR_NOINIT) EcuM_ResetMode;

/* Index variable for getting the shutdown information by iteration, used
 * by EcuM_GetMostRecentShutdown() and EcuM_GetNextRecentShutdown() */
STATIC VAR(uint8, ECUM_VAR_NOINIT) EcuM_NextShutdownInfoIdx;

#define ECUM_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>

#define ECUM_START_SEC_VAR_NO_INIT_16
#include <MemMap.h>

/** \brief Wakeup Validation Counter
 **
 ** Counter for timeout measuring for wakeup validation */
STATIC VAR(uint16, ECUM_VAR_NOINIT) EcuM_WksValCounter;

#define ECUM_STOP_SEC_VAR_NO_INIT_16
#include <MemMap.h>

#define ECUM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief Pointer to Post-Build Time Configuration for EcuM
 **
 ** Pointer to the configuration returned from the function
 ** EcuM_DeterminePbConfiguration().  Set in EcuM_Init(). */
STATIC P2CONST(EcuM_ConfigType, ECUM_VAR_NOINIT, ECUM_CONST) EcuM_ConfigPtr;

/** \brief Currently selected Shutdown Target
 **
 ** This variable holds the current shutdown target used in the next
 ** shutdown sequence. */
STATIC VAR(EcuM_ASR40_StateType, ECUM_VAR_NOINIT) EcuM_ShutdownTarget;

/** \brief Currently selected Shutdown Cause
 **
 ** This variable holds the slected shutdown cause used for the next
 ** shutdown. */
STATIC VAR(EcuM_ASR40_ShutdownCauseType, ECUM_VAR_NOINIT) EcuM_ShutdownCause;

/** \brief Disabled Wakeup Sources */
STATIC VAR(EcuM_WakeupSourceType, ECUM_VAR_NOINIT) EcuM_WksDisabled;
/** \brief Cleared Wakeup Sources */
STATIC VAR(EcuM_WakeupSourceType, ECUM_VAR_NOINIT) EcuM_WksNone;
/** \brief Pending Wakeup Sources */
STATIC VAR(EcuM_WakeupSourceType, ECUM_VAR_NOINIT) EcuM_WksPending;


/** \brief Validated Wakeup Sources */
STATIC VAR(EcuM_WakeupSourceType, ECUM_VAR_NOINIT) EcuM_WksValidated;

/** \brief Expired Wakeup Sources */
STATIC VAR(EcuM_WakeupSourceType, ECUM_VAR_NOINIT) EcuM_WksExpired;

/** \brief Started Wakeup Sources */
STATIC VAR(EcuM_WakeupSourceType, ECUM_VAR_NOINIT) EcuM_WksStarted;

/** \brief Wakeup Sources to be stopped when the main function is executed. */
STATIC VAR(EcuM_WakeupSourceType, ECUM_VAR_NOINIT) EcuM_WksStopped;

/* The EcuM_WksIndicate* variables are not mutually exclusive.  At a given point
 * in time, a wakeup source bit may be set in zero or more indication
 * variables. After indicating the changed status, the variable's value shall be
 * reset. */
/** \brief The disabled wakeup events to be indicated to the BswM. */
STATIC VAR(EcuM_WakeupSourceType, ECUM_VAR_NOINIT) EcuM_WksIndicateDisabled;

/** \brief The disabled wakeup events to be indicated to the BswM. */
STATIC VAR(EcuM_WakeupSourceType, ECUM_VAR_NOINIT) EcuM_WksIndicateExpired;
/** \brief The cleared wakeup events to be indicated to the BswM. */
STATIC VAR(EcuM_WakeupSourceType, ECUM_VAR_NOINIT) EcuM_WksIndicateNone;

/** \brief The pending wakeup events to be indicated to the BswM. */
STATIC VAR(EcuM_WakeupSourceType, ECUM_VAR_NOINIT) EcuM_WksIndicatePending;

/** \brief The validated wakeup events to be indicated to the BswM. */
STATIC VAR(EcuM_WakeupSourceType, ECUM_VAR_NOINIT) EcuM_WksIndicateValidated;

#if (ECUM_ECUM_FIXED_SUPPORT == STD_ON)
/** \brief Timeout for RUN state
 **
 ** This variable holds the timeout counter for the RUN state in
 ** fixed mode. */
STATIC VAR(uint32, ECUM_VAR_NOINIT) EcuM_RunTimeout;
#endif /* (ECUM_ECUM_FIXED_SUPPORT == STD_ON) */
#define ECUM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[external function definitions]=========================*/

#define ECUM_START_SEC_CODE
#include <MemMap.h>

/*--------------------------------------------------------------------------
 * General
 *--------------------------------------------------------------------------*/

#if (ECUM_VERSION_INFO_API == STD_ON)
/*------------------[EcuM_GetVersionInfo]----------------------------------*/
FUNC(void, ECUM_CODE) EcuM_GetVersionInfo(
  CONSTP2VAR(Std_VersionInfoType, AUTOMATIC, ECUM_APPL_DATA) VersionInfoPtr)
{
  DBG_ECUM_GETVERSIONINFO_ENTRY(VersionInfoPtr);

#if (ECUM_DEV_ERROR_DETECT == STD_ON)

  if (NULL_PTR == VersionInfoPtr)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_GET_VERSION_INFO, ECUM_E_NULL_POINTER);
  }
  else
#endif
  {
    VersionInfoPtr->vendorID         = ECUM_VENDOR_ID;
    VersionInfoPtr->moduleID         = ECUM_MODULE_ID;
    VersionInfoPtr->sw_major_version = ECUM_SW_MAJOR_VERSION;
    VersionInfoPtr->sw_minor_version = ECUM_SW_MINOR_VERSION;
    VersionInfoPtr->sw_patch_version = ECUM_SW_PATCH_VERSION;
  }

  DBG_ECUM_GETVERSIONINFO_EXIT(VersionInfoPtr);
}
#endif

/*--------------------------------------------------------------------------
 * Initialization and Shutdown Sequences
 *--------------------------------------------------------------------------*/

/*------------------[EcuM_GoDown]--------------------------------*/

FUNC(Std_ReturnType, ECUM_CODE) EcuM_GoDown(uint16 caller)
{
  Std_ReturnType ret = E_OK;

  DBG_ECUM_GODOWN_ENTRY(caller);

#if (ECUM_MULTICORE_ENABLED == TRUE)
  if (GetCoreID() == OS_CORE_ID_MASTER)
  {
#endif /* (ECUM_MULTICORE_ENABLED == TRUE) */

  /* If Defensive behaviour enabled , then check if the given CallerID is in
   * the list of allowed CallerIDs. Report "ECUM_E_IMPROPER_CALLER " to DEM if
   * the check fails.
   *
   * return E_NOT_OK if the request not accepted. */

  /* The current implementaion not support the feature Defensive behaviour. */
  TS_PARAM_UNUSED(caller);

    /* This callout notifies the integrator - a shutdown sequence is
     * about to be entered */
    EcuM_OnGoOffOne();
#if (ECUM_ECUM_FIXED_SUPPORT == STD_ON)
  EcuM_KillAllRUNRequested = FALSE;
#endif /* (ECUM_ECUM_FIXED_SUPPORT == STD_ON) */

    /* De-initialize BSW Mode Manager */
    BswM_Deinit();

    /* De-init BSW Scheduler */
    EcuM_SchM_Deinit();

    /* Check for pending wakeup events, purpose is to detect wakeup events
     * that occurred during shutdown */
    if ((EcuM_WksPending != 0U) || (EcuM_WksValidated != 0U))
    {
      /* !LINKSTO EcuM2756,1 */
      /* Set RESET as shutdown target, this action shall only be carried out
       * when pending wakeup events were detected */
      EcuM_ShutdownTarget = ECUM_STATE_RESET;
    }

    /* Store the shutdown information at the current location of buffer before
     * shutting down */
    EcuM_ShutdownInfo[EcuM_ShutdownInfoCurrentIdx].target
      = EcuM_ShutdownTarget;

    /* If the selected shutdown target is reset then store the reset modality */
    if (EcuM_ShutdownTarget == ECUM_STATE_RESET)
    {
      EcuM_ShutdownInfo[EcuM_ShutdownInfoCurrentIdx].mode = EcuM_ResetMode;
    }
     /* SWS doesnot specify explicitely what to be done when the target is
      * ECUM_STATE_OFF for the APIs EcuM_SelectShutdownCause(),
      * EcuM_GetShutdownCause(), EcuM_GetMostRecentShutdown and
      * EcuM_GetMostRecentShutdown(). */
    else
    {
      /* The returned mode value is always 0U if the shutdown target
       * is ECUM_STATE_OFF since no mode is existing for ECUM_STATE_OFF */
      EcuM_ShutdownInfo[EcuM_ShutdownInfoCurrentIdx].mode = 0U;
    }

    EcuM_ShutdownInfo[EcuM_ShutdownInfoCurrentIdx].cause  = EcuM_ShutdownCause;
    /* returned time value is always 0 as alarm clock functionality is not yet
     * supported */
    EcuM_ShutdownInfo[EcuM_ShutdownInfoCurrentIdx].sdTime = 0U;

    EcuM_ShutdownInfoCurrentIdx++;

    /* Reset the current buffer pointer if it reached max value */
    if (EcuM_ShutdownInfoCurrentIdx == ECUM_STORED_SHUTDOWN_OPERATIONS)
    {
      /* Reset the current index pointer to zero if it reaches the max value
       * to rotate throughout the buffer. */
      EcuM_ShutdownInfoCurrentIdx = 0U;
    }

    if (EcuM_ShutdownInfoCurrentIdx == EcuM_ShutdownInfoStartIdx)
    {
      /* If the current index point of the buffer reaches the
       * EcuM_ShutdownInfoStartIdx then buffer is filled with maximum storage
       * and the EcuM_ShutdownInfoStartIdx has to move forward one step */
      EcuM_ShutdownInfoStartIdx++;

      if (EcuM_ShutdownInfoStartIdx == ECUM_STORED_SHUTDOWN_OPERATIONS)
      {
        /* Reset the start index pointer to zero if it reaches the max value
         * to rotate throughout the buffer. */
        EcuM_ShutdownInfoStartIdx = 0U;
      }
    }

  EcuM_State = ECUM_STATE_OFF;
#if (ECUM_MULTICORE_ENABLED == TRUE)
    {
      /* Master Core SHUTDOWN
       * The E_OK is passed to the ShutdownHook and is
       * not evaluated by the OS. A neutral value has
       * chosen in this situation.
       * THIS CALL WILL NOT RETURN.
       */
      ShutdownAllCores(E_OK);
    }
  } /* if (GetCoreID() == OS_CORE_ID_MASTER) */
#endif /* (ECUM_MULTICORE_ENABLED == TRUE) */

#if (ECUM_MULTICORE_ENABLED == FALSE)
  ShutdownOS(E_OK);              /* THIS CALL WILL NOT RETURN */
#endif /* (ECUM_MULTICORE_ENABLED == FALSE) */


  DBG_ECUM_GODOWN_EXIT(ret,caller);
  return ret;
}

/*------------------[EcuM_GoHalt]--------------------------------------------*/

FUNC(Std_ReturnType, ECUM_CODE) EcuM_GoHalt(void)
{
  DBG_ECUM_GOHALT_ENTRY();

  /* *** GoSleep sequence *** */
  EcuM_GoSleep();

  /* *** Halt sequence *** */
  EcuM_GenerateRamHash();     /* Invoke callout to generate RamHash */

  /* until here a wakeup event may have been reported via an interrupt and
   * it may be pending.
   *
   * Within the EcuM_PreHalt() callout the interrupts may be disabled for
   * architectures on which disabled interrupts may still lead to a MCU
   * wakeup. Disabling interrupts here prevents ISR routines that may be
   * executed between the checking for pending events and call to
   * Mcu_SetMode(). Such an interruption would set a pending wakeup event,
   * but MCU would still go into halt without reacting to the event. */
  /* !LINKSTO EcuM.Sleep,1 */
  EcuM_PreHalt();
  if ( (EcuM_WksPending == 0U) && (EcuM_WksValidated == 0U) )
  {
    /* here CPU is halted and the function Mcu_SetMode() does not return
     * until a wakeup interrupt happened */
    Mcu_SetMode(EcuM_SleepModeConfigList[EcuM_SleepMode].mcuMode);
    /* at this point the MCU has received a wakeup interrupt and the
     * functions EcuM_SetWakeupEvent() was called in the meantime */
}
  /* revert any actions from the EcuM_PreHalt() call */
  EcuM_PostHalt();

  /* Invoke callout to check RamHash */
  if (0U == EcuM_CheckRamHash())
  {
    /* It is left integrator's discretion to allow EcuM_ErrorHook() to
     * rely the error to the DEM. The following call to EcuM_ErrorHook()
     * will never return. Instead the failing RamCheck may be stored in a
     * flag which survives a reset */

#if (ECUM_PROD_ERR_RAM_CHECK_FAILURE == TS_PROD_ERR_REP_TO_DET)
    /* The DET may still acccept a call here */
    ECUM_DET_REPORT_ERROR(
      ECUM_SID_MAIN_FUNCTION, ECUM_E_DEMTODET_RAM_CHECK_FAILED);
#endif

#if (ECUM_INCLUDE_DEM == STD_ON) \
&& (ECUM_PROD_ERR_RAM_CHECK_FAILURE == TS_PROD_ERR_REP_TO_DEM)
    EcuM_RamCheckStatus = ECUM_RAM_CHECK_STATUS_FAILED;
#endif
    /* this call should never return according to SWS */
    EcuM_ErrorHook(ECUM_RAM_CHECK_FAILED);
  }
  else
  {
#if (ECUM_INCLUDE_DEM == STD_ON) \
&& (ECUM_PROD_ERR_RAM_CHECK_FAILURE == TS_PROD_ERR_REP_TO_DEM)
    EcuM_RamCheckStatus = ECUM_RAM_CHECK_STATUS_PASSED;
#endif
  }

  /* Notification to BswM regarding the pending and validated
   * wakeup events are done in MainFuntion */

  /* *** WakeupRestart sequence *** */
  EcuM_WakeupRestart();

  DBG_ECUM_GOHALT_EXIT(E_OK);

  return E_OK;
}

/*------------------[EcuM_GoPoll]--------------------------------------------*/

FUNC(Std_ReturnType, ECUM_CODE) EcuM_GoPoll(void)
{
  DBG_ECUM_GOPOLL_ENTRY();

  /* *** GoSleep sequence *** */
  EcuM_GoSleep();

  /* *** Poll sequence *** */
  Mcu_SetMode(EcuM_SleepModeConfigList[EcuM_SleepMode].mcuMode);

  /* Blocking synchronous loop till a wakeup is detected.
   *
   * The scheduling of the OS is deactivated during GoSleep sequence
   * (RES_SCHEDULER is taken) so that the EcuM main function is not
   * periodically called.
   *
   * Additional Confidition to Loop: While (AlarmClockService Present AND
   * EcuM_AlarmClock only pending event AND Alarm not expired). */
  while ((EcuM_WksPending == 0U) && (EcuM_WksValidated == 0U))
  {
    EcuM_SleepActivity(); /* Invoke callout function */

    /* Check enabled wakeup sources */
    EcuM_CheckWakeup(EcuM_SleepModeConfigList[EcuM_SleepMode].wakeupSource & ECUM_WKSMASKALL);
}
  /* Notification to BswM regarding the pending and validated
   * wakeup events are done in MainFuntion */

  /* *** WakeupRestart sequence *** */
  EcuM_WakeupRestart();

  DBG_ECUM_GOPOLL_EXIT(E_OK);
  return E_OK;
}

/*------------------[EcuM_Init]--------------------------------------------*/

FUNC(void, ECUM_CODE) EcuM_Init(void)
{

  DBG_ECUM_INIT_ENTRY();

#if (ECUM_MULTICORE_ENABLED == TRUE)
  /* Master Core STARTUP */
  if (GetCoreID() == OS_CORE_ID_MASTER)
  {
#endif /* (ECUM_MULTICORE_ENABLED == TRUE) */

  EcuM_State = ECUM_STATE_STARTUP_ONE;

  /* Inialization of the wakeup source status variables. On startup, all wakeup
   * sources are disabled. */
  EcuM_WksDisabled = ECUM_WKSMASKALL;
  EcuM_WksNone = 0U;
  EcuM_WksExpired = 0U;
  EcuM_WksPending = 0U;
  EcuM_WksValidated = 0U;
  /* On startup, no status change indications shall be made. */
  EcuM_WksIndicateDisabled = 0U;
  EcuM_WksIndicateExpired = 0U;
  EcuM_WksIndicateNone = 0U;
  EcuM_WksIndicatePending = 0U;
  EcuM_WksIndicateValidated = 0U;
  /* On startup, no wakeup sources have been started or stopped. */
  EcuM_WksStarted = 0U;
  EcuM_WksStopped = 0U;
#if (ECUM_ECUM_FIXED_SUPPORT == STD_ON)
/*   EcuM_FixedState = ECUM_FIXED_STATE_STARTUP; */
  EcuM_KillAllRUNRequested = FALSE;
#endif
  /* On ECUs with programmable interrupt priorities, these priorities
   * must be set before the OS is started.*/
  EcuM_AL_SetProgrammableInterrupts();


#if (ECUM_INITLIST_ZERO == STD_ON)
  EcuM_AL_DriverInitZero();     /* initialize configured drivers */
#endif

  /* determine and store configuration */
  EcuM_ConfigPtr = EcuM_DeterminePbConfiguration();

#if (ECUM_DEV_ERROR_DETECT == STD_ON)
  /* Check for NULL pointer */
  if (EcuM_ConfigPtr == NULL_PTR)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_INIT, ECUM_E_NULL_POINTER);
  }
  else
#endif
  {
    /* loop variables */
    uint8_least wks;
    boolean ReasonFound;        /* To check if the reset reason is found */
    Mcu_ResetType McuReset;     /* Reset type fetched from Mcu */
  /* !LINKSTO EcuM2980,1 */
  /* The ECU Manager module does not report the errors during their initialization  */
#if (ECUM_INITLIST_ONE == STD_ON)
    EcuM_AL_DriverInitOne(EcuM_ConfigPtr); /* initialize configured drivers */
#endif

    /* set default shutdown target */
    EcuM_ShutdownTarget = EcuM_ConfigPtr->DefaultShutdownTarget;

    if (EcuM_ShutdownTarget == ECUM_STATE_SLEEP)
    {
      /* set default sleep mode. It is ensured by configuration checks
         that mode will be corresponding to sleep if the shutdown target
         is selected as sleep.*/
      EcuM_SleepMode = EcuM_ConfigPtr->DefaultMode;
    }
    else if (EcuM_ShutdownTarget == ECUM_STATE_RESET)
    {
      /* set default reset mode. It is ensured by configuration checks
         that mode will be corresponding to reset if the shutdown target
         is selected as reset.*/
      EcuM_ResetMode = EcuM_ConfigPtr->DefaultMode;
    }
    else
    {
      /* Do Nothing */
    }

    /* set default boot target */
    EcuM_BootTarget[0] = ECUM_BOOT_TARGET_APP;
    EcuM_BootTarget[1] = ECUM_BOOT_TARGET_APP;

    /* check reset reason */
    McuReset = Mcu_GetResetReason();

    /* Initialize found flag to false */
    ReasonFound = FALSE;

    /* Set wakeup events resulting from reset reasons */
    for (wks = 0U; (wks < ECUM_WKSCONFIGNUM) && (ReasonFound != TRUE); wks++)
    {
      /* Get a pointer to the wake-up source configuration */
      P2CONST(EcuM_WksConfigType, AUTOMATIC, ECUM_CONST) WksPtr = &(EcuM_WksConfigList[wks]);

      /* if the reset reason is found then set the wakeup event */
      if ((WksPtr->ResetReason != MCU_RESET_UNDEFINED) && (WksPtr->ResetReason == McuReset))
      {
        EcuM_SetWakeupEvent((EcuM_WakeupSourceType)((EcuM_WakeupSourceType)1U << WksPtr->WksId));
        ReasonFound = TRUE;
      }
    }
#if (ECUM_MULTICORE_ENABLED == TRUE)
    {
      StatusType status;
      uint8 i;
      for (i = 0U; i < ECUM_NUM_CORES; i++)
        {
           StartCore(i, &status);
        }
    }
#endif /* (ECUM_MULTICORE_ENABLED == TRUE) */

    /* start the operating system */
    StartOS(EcuM_ConfigPtr->DefaultAppMode);
  }
#if (ECUM_MULTICORE_ENABLED == TRUE)
  }  /* end if (GetCoreID() == OS_CORE_ID_MASTER) */
  else
  {
    /* Slave Core STARTUP */
    StartOS(EcuM_ConfigPtr->DefaultAppMode);
  }
#endif /* (ECUM_MULTICORE_ENABLED == TRUE) */
  DBG_ECUM_INIT_EXIT();
}

/*------------------[EcuM_StartupTwo]---------------------------------------*/

FUNC(void, ECUM_CODE) EcuM_StartupTwo(void)
{

  DBG_ECUM_STARTUPTWO_ENTRY();

#if (ECUM_MULTICORE_ENABLED == TRUE)
/* On multicore platforms, the SchM and BswM shall be initialized 
 * only on the master core */
  if (GetCoreID() == OS_CORE_ID_MASTER)
  {
#endif

#if (ECUM_DEV_ERROR_DETECT == STD_ON)
  if (EcuM_State == ECUM_STATE_UNINIT)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_STARTUP_TWO, ECUM_E_UNINIT);
  }
  else
#endif /* (ECUM_DEV_ERROR_DETECT == STD_ON) */
  {
    EcuM_State = ECUM_STATE_STARTUP_TWO;

    EcuM_SchM_Init();
    BswM_Init(NULL_PTR);

    /* enter UP phase */
    EcuM_State = ECUM_STATE_RUN;
  }

#if (ECUM_MULTICORE_ENABLED == TRUE)
  }
#endif

  DBG_ECUM_STARTUPTWO_EXIT();
}

/*------------------[EcuM_Shutdown]-----------------------------------------*/

FUNC(void, ECUM_CODE) EcuM_Shutdown(void)
{
  DBG_ECUM_SHUTDOWN_ENTRY();
#if (ECUM_DEV_ERROR_DETECT == STD_ON)
  if (EcuM_State == ECUM_STATE_UNINIT)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_SHUTDOWN, ECUM_E_UNINIT);
  }
  else
#endif /* (ECUM_DEV_ERROR_DETECT == STD_ON) */
  {
    EcuM_OnGoOffTwo();

    /* If the selected shutdown target is RESET then call EcuM_AL_Reset() with
     * the selected reset modality from the configuration. */

    /* store last shutdown target */
    EcuM_LastShutdownTarget = EcuM_ShutdownTarget;

    if (EcuM_ShutdownTarget == ECUM_STATE_RESET)
    {
      EcuM_AL_Reset(EcuM_ResetMode);
    }
    else
    {
      /* If the selected shutdown target is OFF then Switch off Ecu */
      EcuM_AL_SwitchOff();
    }
  }

  DBG_ECUM_SHUTDOWN_EXIT();
}

/*--------------------------------------------------------------------------
 * Shutdown management
 *--------------------------------------------------------------------------*/

/*------------------[EcuM_SelectShutdownTarget]-----------------------------*/
/* !LINKSTO EcuM.EB.ASR32.EcuM106,1 */
FUNC(Std_ReturnType, ECUM_CODE) EcuM_ASR40_SelectShutdownTarget
(
  EcuM_ASR40_StateType target,
  uint8          mode
)
{
  Std_ReturnType ret = E_NOT_OK; /* return value */

  DBG_ECUM_SELECTSHUTDOWNTARGET_ENTRY(target,mode);

  /* checks for development error detection */
#if (ECUM_DEV_ERROR_DETECT == STD_ON)
  if (EcuM_State == ECUM_STATE_UNINIT)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_SEL_SHUT_TAR, ECUM_E_UNINIT);
  }
  else if ( (target != ECUM_STATE_SLEEP) &&
            ( (target != ECUM_STATE_RESET) && (target != ECUM_STATE_OFF) )
          )
  {
    ECUM_DET_REPORT_ERROR(
      ECUM_SID_SEL_SHUT_TAR, ECUM_E_STATE_PAR_OUT_OF_RANGE);
  }
  else if ((target == ECUM_STATE_SLEEP) &&
           (mode >= ECUM_SLEEPMODECONFIGNUM))
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_SEL_SHUT_TAR, ECUM_E_INVALID_PAR);
  }
  else
#endif /* (ECUM_DEV_ERROR_DETECT == STD_ON) */
  {
    EcuM_Enter_SCHM_ECUM_EXCLUSIVE_AREA_0();

    if (target == ECUM_STATE_SLEEP)
    {
      EcuM_ShutdownTarget = target;
      EcuM_SleepMode = mode;
    }
    else if (target == ECUM_STATE_RESET)
    {
      EcuM_ShutdownTarget = target;
      EcuM_ResetMode = mode;
    }
    else if (target == ECUM_STATE_OFF)
    {
      EcuM_ShutdownTarget = target;
    }
    else
    {
      /* ignore mode if target is not SLEEP, RESET or OFF */
    }

    EcuM_Exit_SCHM_ECUM_EXCLUSIVE_AREA_0();

    ret = E_OK;
  }


  DBG_ECUM_SELECTSHUTDOWNTARGET_EXIT(ret,target,mode);
  return ret;
}

/* !LINKSTO EcuM.EB.ASR32.EcuM107,1 */
#if ((ECUM_EB_ENABLE_ASR32_SERVICE_API == STD_ON) || \
    (ECUM_EB_DEFAULT_ASR_SERVICE_API == ECUM_EB_SERVICE_API_ASR32))
FUNC(Std_ReturnType, ECUM_CODE) EcuM_ASR32_SelectShutdownTarget
(
  EcuM_ASR32_StateType target,
  uint8                mode
)
{
  Std_ReturnType ret = E_NOT_OK; /* return value */

  /* EcuM_ASR40_StateType and EcuM_ASR32_StateType are referencing to
   * the same base type and the state definitions are identical.
   * Therefore no argument type mapping is done. */
  ret = EcuM_ASR40_SelectShutdownTarget(target, mode);

  return ret;
}
#endif

/*------------------[EcuM_GetShutdownTarget]--------------------------------*/
/* !LINKSTO EcuM.EB.ASR32.EcuM106,1 */
/* Deviation MISRA-1 */
FUNC(Std_ReturnType, ECUM_CODE) EcuM_ASR40_GetShutdownTarget
(
  P2VAR(EcuM_ASR40_StateType, AUTOMATIC, ECUM_APPL_DATA) shutdownTarget,
  P2VAR(uint8, AUTOMATIC, ECUM_APPL_DATA)                sleepMode
)
{
  Std_ReturnType ret = E_OK;

  DBG_ECUM_GETSHUTDOWNTARGET_ENTRY(shutdownTarget,sleepMode);

#if (ECUM_DEV_ERROR_DETECT == STD_ON)
  if (EcuM_State == ECUM_STATE_UNINIT)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_GET_SHUT_TAR, ECUM_E_UNINIT);
    ret = E_NOT_OK;
  }
  else
#endif
  {
    if (shutdownTarget != NULL_PTR)
    {
      *shutdownTarget = EcuM_ShutdownTarget;
    }
    else
    {
#if (ECUM_DEV_ERROR_DETECT == STD_ON)
      ECUM_DET_REPORT_ERROR(ECUM_SID_GET_SHUT_TAR,ECUM_E_NULL_POINTER);
#endif
      ret = E_NOT_OK;
    }

    if (sleepMode != NULL_PTR)
    {
      if (EcuM_ShutdownTarget == ECUM_STATE_SLEEP)
      {
        *sleepMode = EcuM_SleepMode;
      }
      else if (EcuM_ShutdownTarget == ECUM_STATE_RESET)
      {
        *sleepMode = EcuM_ResetMode;
      }
      else
      {
        /* ignore mode if target is not SLEEP or RESET */
      }
    }
    else
    {
#if (ECUM_DEV_ERROR_DETECT == STD_ON)
      ECUM_DET_REPORT_ERROR(ECUM_SID_GET_SHUT_TAR,ECUM_E_NULL_POINTER);
#endif
      ret = E_NOT_OK;
    }
  }


  DBG_ECUM_GETSHUTDOWNTARGET_EXIT(ret,shutdownTarget,sleepMode);
  return ret;
}

/* !LINKSTO EcuM.EB.ASR32.EcuM107,1 */
#if ((ECUM_EB_ENABLE_ASR32_SERVICE_API == STD_ON) || \
    (ECUM_EB_DEFAULT_ASR_SERVICE_API == ECUM_EB_SERVICE_API_ASR32))
FUNC(Std_ReturnType, ECUM_CODE) EcuM_ASR32_GetShutdownTarget
(
  P2VAR(EcuM_ASR32_StateType, AUTOMATIC, ECUM_APPL_DATA) shutdownTarget,
  P2VAR(uint8, AUTOMATIC, ECUM_APPL_DATA)                sleepMode
)
{
  Std_ReturnType ret = E_OK;

  /* EcuM_ASR40_StateType and EcuM_ASR32_StateType are referencing to
   * the same base type and the state definitions are identical.
   * Therefore no argument type mapping is done. */
  ret = EcuM_ASR40_GetShutdownTarget(shutdownTarget, sleepMode);

  return ret;
}
#endif

/*------------------[EcuM_GetLastShutdownTarget]----------------------------*/
/* !LINKSTO EcuM.EB.ASR32.EcuM106,1 */
/* Deviation MISRA-1 */
FUNC(Std_ReturnType, ECUM_CODE) EcuM_ASR40_GetLastShutdownTarget
(
  P2VAR(EcuM_ASR40_StateType, AUTOMATIC, ECUM_APPL_DATA) shutdownTarget,
  P2VAR(uint8, AUTOMATIC, ECUM_APPL_DATA)                sleepMode
)
{
  Std_ReturnType ret = E_OK;

  DBG_ECUM_GETLASTSHUTDOWNTARGET_ENTRY(shutdownTarget,sleepMode);

#if (ECUM_DEV_ERROR_DETECT == STD_ON)
  if (EcuM_State == ECUM_STATE_UNINIT)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_GET_LAST_SHUT_TAR, ECUM_E_UNINIT);
    ret = E_NOT_OK;
  }
  else
#endif
  {
    if (shutdownTarget != NULL_PTR)
    {
      *shutdownTarget = EcuM_LastShutdownTarget;
    }
    else
    {
#if (ECUM_DEV_ERROR_DETECT == STD_ON)
      ECUM_DET_REPORT_ERROR(ECUM_SID_GET_LAST_SHUT_TAR, ECUM_E_NULL_POINTER);
#endif
      ret = E_NOT_OK;
    }

    if (sleepMode != NULL_PTR)
    {
      if (EcuM_LastShutdownTarget == ECUM_STATE_SLEEP)
      {
        /* !LINKSTO EcuM2336,1 */
        *sleepMode = EcuM_LastSleepMode;
      }
      else if (EcuM_LastShutdownTarget == ECUM_STATE_RESET)
      {
        /* !LINKSTO EcuM2336,1 */
        *sleepMode = EcuM_LastResetMode;
      }
      else
      {
        /* ignore mode if target is not SLEEP or RESET */
      }
    }
    else
    {
#if (ECUM_DEV_ERROR_DETECT == STD_ON)
      ECUM_DET_REPORT_ERROR(ECUM_SID_GET_LAST_SHUT_TAR,ECUM_E_NULL_POINTER);
#endif
      ret = E_NOT_OK;
    }
  }


  DBG_ECUM_GETLASTSHUTDOWNTARGET_EXIT(ret,shutdownTarget,sleepMode);
  return ret;
}

/* !LINKSTO EcuM.EB.ASR32.EcuM107,1 */
#if ((ECUM_EB_ENABLE_ASR32_SERVICE_API == STD_ON) || \
    (ECUM_EB_DEFAULT_ASR_SERVICE_API == ECUM_EB_SERVICE_API_ASR32))
FUNC(Std_ReturnType, ECUM_CODE) EcuM_ASR32_GetLastShutdownTarget
(
  P2VAR(EcuM_ASR32_StateType, AUTOMATIC, ECUM_APPL_DATA) shutdownTarget,
  P2VAR(uint8, AUTOMATIC, ECUM_APPL_DATA)                sleepMode
)
{
  Std_ReturnType ret = E_OK;

  /* EcuM_ASR40_StateType and EcuM_ASR32_StateType are referencing to
   * the same base type and the state definitions are identical.
   * Therefore no argument type mapping is done. */
  ret = EcuM_ASR40_GetLastShutdownTarget(shutdownTarget, sleepMode);

  return ret;
}
#endif

/*------------------[EcuM_SelectShutdownCause]-----------------------------*/
/* !LINKSTO EcuM.EB.ASR32.EcuM106,1 */
FUNC(Std_ReturnType, ECUM_CODE) EcuM_ASR40_SelectShutdownCause
(
  EcuM_ASR40_ShutdownCauseType target
)
{
  Std_ReturnType ret = E_NOT_OK;

#if (ECUM_DEV_ERROR_DETECT == STD_ON)
  uint8_least idx;

  DBG_ECUM_SELECTSHUTDOWNCAUSE_ENTRY(target);

  /* check for valid shutdown cause */
  for(idx = 0U; idx < ECUM_SHUTDOWNCAUSECONFIGNUM; idx++)
  {
    if (target == EcuM_ValidShutdownCause[idx])
    {
      break;
    }
  }
  if (EcuM_State == ECUM_STATE_UNINIT)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_SEL_SHUT_CAUSE, ECUM_E_UNINIT);
  }
  else if (idx >= ECUM_SHUTDOWNCAUSECONFIGNUM)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_SEL_SHUT_CAUSE, ECUM_E_INVALID_PAR);
  }
  else
#else
  DBG_ECUM_SELECTSHUTDOWNCAUSE_ENTRY(target);
#endif
  {
    ret = E_OK;
    EcuM_ShutdownCause = target;
  }


  DBG_ECUM_SELECTSHUTDOWNCAUSE_EXIT(ret,target);
  return ret;
}

/*------------------[EcuM_GetShutdownCause]-----------------------------*/
/* !LINKSTO EcuM.EB.ASR32.EcuM106,1 */
/* Deviation MISRA-1 */
FUNC(Std_ReturnType, ECUM_CODE) EcuM_ASR40_GetShutdownCause
(
  P2VAR(EcuM_ASR40_ShutdownCauseType, AUTOMATIC, ECUM_APPL_DATA) shutdownCause
)
{
  Std_ReturnType ret = E_NOT_OK;

  DBG_ECUM_GETSHUTDOWNCAUSE_ENTRY(shutdownCause);

#if (ECUM_DEV_ERROR_DETECT == STD_ON)
  if (EcuM_State == ECUM_STATE_UNINIT)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_GET_SHUT_CAUSE, ECUM_E_UNINIT);
  }
  else
#endif
  {
    if (shutdownCause != NULL_PTR)
    {
      *shutdownCause = EcuM_ShutdownCause;
      ret = E_OK;
    }
    else
    {
#if (ECUM_DEV_ERROR_DETECT == STD_ON)
      ECUM_DET_REPORT_ERROR(ECUM_SID_GET_SHUT_CAUSE,ECUM_E_NULL_POINTER);
#endif
    }
  }


  DBG_ECUM_GETSHUTDOWNCAUSE_EXIT(ret,shutdownCause);
  return ret;
}

/*------------------[EcuM_GetMostRecentShutdown]-----------------------------*/
/* !LINKSTO EcuM.EB.ASR32.EcuM106,1 */
FUNC(Std_ReturnType, ECUM_CODE) EcuM_ASR40_GetMostRecentShutdown
(
  P2VAR(EcuM_ASR40_StateType, AUTOMATIC, ECUM_APPL_DATA)          target,
  P2VAR(uint8, AUTOMATIC, ECUM_APPL_DATA)                         mode,
  P2VAR(EcuM_ASR40_ShutdownCauseType, AUTOMATIC, ECUM_APPL_DATA)  cause,
  P2VAR(uint32, AUTOMATIC, ECUM_APPL_DATA)                        time
)
{
  Std_ReturnType ret = E_NOT_OK;

  DBG_ECUM_GETMOSTRECENTSHUTDOWN_ENTRY(target,mode,cause,time);

#if (ECUM_DEV_ERROR_DETECT == STD_ON)
  if (EcuM_State == ECUM_STATE_UNINIT)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_GET_RCNT_SHUT_CAUSE, ECUM_E_UNINIT);
  }
  else
#endif
  {
    if ( ( (target == NULL_PTR) || (mode == NULL_PTR) ) ||
         ( (cause == NULL_PTR)  || (time == NULL_PTR))
       )
    {
#if (ECUM_DEV_ERROR_DETECT == STD_ON)
      ECUM_DET_REPORT_ERROR(ECUM_SID_GET_RCNT_SHUT_CAUSE, ECUM_E_NULL_POINTER);
#endif
    }
    else
    {
      EcuM_NextShutdownInfoIdx = EcuM_ShutdownInfoCurrentIdx;

      /* Data is available only when the start index and the current index
       * are different. Return E_NOT_OK if there is no data */
      if (EcuM_NextShutdownInfoIdx != EcuM_ShutdownInfoStartIdx)
      {
        /*  Most recent shutdown information is always stored just before the
         *  location of EcuM_ShutdownInfoCurrentIdx. If the current location
         *  is zero then load the max value to loop throughout the buffer */
        if (EcuM_NextShutdownInfoIdx == 0U)
        {
          EcuM_NextShutdownInfoIdx = ECUM_STORED_SHUTDOWN_OPERATIONS-1U;
        }
        else
        {
          EcuM_NextShutdownInfoIdx--;
        }

        /* Get the most recent shutdown information using the current index
         *  point of the shutdowninfo buffer */
        *target = EcuM_ShutdownInfo[EcuM_NextShutdownInfoIdx].target;
        *mode   = EcuM_ShutdownInfo[EcuM_NextShutdownInfoIdx].mode;
        *cause  = EcuM_ShutdownInfo[EcuM_NextShutdownInfoIdx].cause;
        *time   = EcuM_ShutdownInfo[EcuM_NextShutdownInfoIdx].sdTime;

        ret = E_OK;
      }
    }
  }

  DBG_ECUM_GETMOSTRECENTSHUTDOWN_EXIT(ret,target,mode,cause,time);
  return ret;
}

/*------------------[EcuM_GetNextRecentShutdown]-----------------------------*/
/* !LINKSTO EcuM.EB.ASR32.EcuM106,1 */
FUNC(Std_ReturnType, ECUM_CODE) EcuM_ASR40_GetNextRecentShutdown
(
  P2VAR(EcuM_ASR40_StateType, AUTOMATIC, ECUM_APPL_DATA)          target,
  P2VAR(uint8, AUTOMATIC, ECUM_APPL_DATA)                         mode,
  P2VAR(EcuM_ASR40_ShutdownCauseType, AUTOMATIC, ECUM_APPL_DATA)  cause,
  P2VAR(uint32, AUTOMATIC, ECUM_APPL_DATA)                        time
)
{
  Std_ReturnType ret = E_NOT_OK;

  DBG_ECUM_GETNEXTRECENTSHUTDOWN_ENTRY(target,mode,cause,time);

#if (ECUM_DEV_ERROR_DETECT == STD_ON)
  if (EcuM_State == ECUM_STATE_UNINIT)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_GET_NXT_RCNT_SHUT_CAUSE, ECUM_E_UNINIT);
  }
  else
#endif
  {
    if (EcuM_NextShutdownInfoIdx != 0U)
    {
      /* Decrement the buffer index to get next shutdown info */
      EcuM_NextShutdownInfoIdx--;
    }
    else
    {
      /* If the index pointer EcuM_NextShutdownInfoIdx reached the bottom
       * of the buffer, then start the static index from top */
      EcuM_NextShutdownInfoIdx = ECUM_STORED_SHUTDOWN_OPERATIONS - 1U;
    }

    if (EcuM_NextShutdownInfoIdx != EcuM_ShutdownInfoStartIdx)
    {
      if ( ( (target == NULL_PTR)  || (mode == NULL_PTR) ) ||
           ( (cause == NULL_PTR)   || (time == NULL_PTR) )
         )
      {
#if (ECUM_DEV_ERROR_DETECT == STD_ON)
        ECUM_DET_REPORT_ERROR(
          ECUM_SID_GET_NXT_RCNT_SHUT_CAUSE, ECUM_E_NULL_POINTER);
#endif
      }
      else
      {
        /* Returns the available shutdown information */
        *target = EcuM_ShutdownInfo[EcuM_NextShutdownInfoIdx].target;
        *mode   = EcuM_ShutdownInfo[EcuM_NextShutdownInfoIdx].mode;
        *cause  = EcuM_ShutdownInfo[EcuM_NextShutdownInfoIdx].cause;
        *time   = EcuM_ShutdownInfo[EcuM_NextShutdownInfoIdx].sdTime;

        ret = E_OK;
      }
    }
    /* else: The iteration point equals the start of buffer index means there
     * is no more data available to retrieve. Call EcuM_GetMostRecentShutdown
     * once next to get the information again. */
  }


  DBG_ECUM_GETNEXTRECENTSHUTDOWN_EXIT(ret,target,mode,cause,time);
  return ret;
}

/*--------------------------------------------------------------------------
 * Wakeup handling
 *--------------------------------------------------------------------------*/

/*------------------[EcuM_GetPendingWakeupEvents]---------------------------*/
FUNC(EcuM_WakeupSourceType, ECUM_CODE) EcuM_GetPendingWakeupEvents(void)
{
  EcuM_WakeupSourceType ret = 0U;

  DBG_ECUM_GETPENDINGWAKEUPEVENTS_ENTRY();

#if (ECUM_DEV_ERROR_DETECT == STD_ON)
  if (EcuM_State == ECUM_STATE_UNINIT)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_GET_PEND_WK_EV, ECUM_E_UNINIT);
  }
  else
#endif
  {
    /* !LINKSTO EcuM3003,1 */
    EcuM_Enter_SCHM_ECUM_EXCLUSIVE_AREA_0();
    ret = EcuM_WksPending;
    EcuM_Exit_SCHM_ECUM_EXCLUSIVE_AREA_0();
  }


  DBG_ECUM_GETPENDINGWAKEUPEVENTS_EXIT(ret);
  return ret;
}

/*------------------[EcuM_ClearWakeupEvent]---------------------------------*/
FUNC(void, ECUM_CODE) EcuM_ClearWakeupEvent
(
  EcuM_WakeupSourceType sources
)
{
  DBG_ECUM_CLEARWAKEUPEVENT_ENTRY(sources);

#if (ECUM_DEV_ERROR_DETECT == STD_ON)
  if (EcuM_State == ECUM_STATE_UNINIT)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_CLEAR_WK_EV, ECUM_E_UNINIT);
  }
  else
#endif
  {

    /* EcuM2683*/
    EcuM_SwitchWakeupStatus(sources, ECUM_WKSTATUS_NONE);

    EcuM_Enter_SCHM_ECUM_EXCLUSIVE_AREA_0();

    /* Clear the started wakeup sources when the main function is executed. As 
     * per SWS the started wakeup sources are stopped only when the validation 
     * timeout get expired. If the wakeup event is cleared during the ongoing 
     * validation, then this event cannot be considered as validated or 
     * expired */
    EcuM_WksStopped |= sources;

    EcuM_Exit_SCHM_ECUM_EXCLUSIVE_AREA_0();

    /* The cleared wakeup events are indicated to BswM in EcuM_MainFunction */
  }

  DBG_ECUM_CLEARWAKEUPEVENT_EXIT(sources);
}

/*------------------[EcuM_GetValidatedWakeupEvents]-------------------------*/
FUNC(EcuM_WakeupSourceType, ECUM_CODE) EcuM_GetValidatedWakeupEvents(void)
{
  EcuM_WakeupSourceType ret = 0U;

  DBG_ECUM_GETVALIDATEDWAKEUPEVENTS_ENTRY();

#if (ECUM_DEV_ERROR_DETECT == STD_ON)
  if (EcuM_State == ECUM_STATE_UNINIT)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_GET_VALID_WK_EV, ECUM_E_UNINIT);
  }
  else
#endif
  {
    EcuM_Enter_SCHM_ECUM_EXCLUSIVE_AREA_0();
    ret = EcuM_WksValidated;
    EcuM_Exit_SCHM_ECUM_EXCLUSIVE_AREA_0();
  }


  DBG_ECUM_GETVALIDATEDWAKEUPEVENTS_EXIT(ret);
  return ret;
}

/*------------------[EcuM_GetExpiredWakeupEvents]---------------------------*/
FUNC(EcuM_WakeupSourceType, ECUM_CODE) EcuM_GetExpiredWakeupEvents(void)
{
  EcuM_WakeupSourceType ret = 0U;

  DBG_ECUM_GETEXPIREDWAKEUPEVENTS_ENTRY();

#if (ECUM_DEV_ERROR_DETECT == STD_ON)
  if (EcuM_State == ECUM_STATE_UNINIT)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_GET_EXP_WK_EV, ECUM_E_UNINIT);
  }
  else
#endif
  {
    EcuM_Enter_SCHM_ECUM_EXCLUSIVE_AREA_0();
    ret = EcuM_WksExpired;
    EcuM_Exit_SCHM_ECUM_EXCLUSIVE_AREA_0();
  }


  DBG_ECUM_GETEXPIREDWAKEUPEVENTS_EXIT(ret);
  return ret;
}

/*--------------------------------------------------------------------------
 * Scheduled functions
 *--------------------------------------------------------------------------*/

/*------------------[EcuM_MainFunction]-------------------------------------*/

FUNC(void, ECUM_CODE) EcuM_MainFunction(void)
{
  EcuM_WakeupSourceType wksPending = 0U;
  EcuM_WakeupSourceType wksStarted = 0U;
  EcuM_WakeupSourceType wksStopped = 0U;
  uint16 wksValCounter = 0U;

  DBG_ECUM_MAINFUNCTION_ENTRY();

/* The fixed SWS requires that EcuM_MainFunction() shall return without any
 * functionality if called before EcuM_Init(). Thus we circumvent the DET
 * check here. */
#if ((ECUM_ECUM_FIXED_SUPPORT == STD_ON) || (ECUM_DEV_ERROR_DETECT == STD_ON))
  if (EcuM_State == ECUM_STATE_UNINIT)
  {
#if (ECUM_ECUM_FIXED_SUPPORT == STD_OFF)
    ECUM_DET_REPORT_ERROR(ECUM_SID_MAIN_FUNCTION, ECUM_E_UNINIT);
#endif /* (ECUM_ECUM_FIXED_SUPPORT == STD_OFF) */
  }
  else
#endif /* ((ECUM_ECUM_FIXED_SUPPORT == STD_ON) || (ECUM_DEV_ERROR_DETECT == STD_ON)) */
  {

    EcuM_Enter_SCHM_ECUM_EXCLUSIVE_AREA_0();

    /* Create a snapshot of the current wakeup validation state. */
    EcuM_WksStarted &= ~EcuM_WksStopped;
    EcuM_WksStopped = 0U;
    
    wksPending = EcuM_WksPending;
    wksStarted = EcuM_WksStarted;

    wksValCounter = EcuM_WksValCounter;

    EcuM_Exit_SCHM_ECUM_EXCLUSIVE_AREA_0();

    /* Indicate the wakeup sources status changes to the BswM. */
    EcuM_WksIndicateStatus_NONE();
    EcuM_WksIndicateStatus_PENDING();
    EcuM_WksIndicateStatus_VALIDATED();
    EcuM_WksIndicateStatus_DISABLED();

    /* Check for a validation timeout. */
    if ((wksPending != 0U) && (wksValCounter == 0U))
    {
      /* Validation timeout has occurred. Since the timeout value corresponds to
       * the longest timeout of the pending wakeup events, all wakeup events
       * must have expired. */
      EcuM_SwitchWakeupStatus(wksPending, ECUM_WKSTATUS_EXPIRED);
      EcuM_StopWakeupSources(wksPending);
      wksStopped = wksPending;
      wksPending = 0U;
      /* Indicate the expired wakeup sources to the BswM. */
      EcuM_WksIndicateStatus_EXPIRED();
    }

    /* Start the pending wakeup sources that have not yet been started. */
    if ((wksPending & ~wksStarted) != 0U)
    {
      EcuM_StartWakeupSources(wksPending & ~wksStarted);

      /* All pending wakeup sources have been started. */
      wksStarted = wksPending;
    }

    if (wksPending != 0U)
    {
      /* Execute the validation routine if there any pending wakeup events */
      EcuM_CheckValidation(wksPending);
    }

    EcuM_Enter_SCHM_ECUM_EXCLUSIVE_AREA_0();
    /* Wakeup validation iteration complete, save state. */
    if (EcuM_WksValCounter > 0U)
    {
        EcuM_WksValCounter--;
    }
    EcuM_WksStarted |= wksStarted;
    EcuM_WksStarted &= ~wksStopped;
    EcuM_Exit_SCHM_ECUM_EXCLUSIVE_AREA_0();

#if (ECUM_ECUM_FIXED_SUPPORT == STD_ON)
      if(EcuM_State == ECUM_STATE_WAKEUP_VALIDATION)
      {
        ECUM_EB_CURRENT_MODE_SWITCH(ECUM_EB_MODE_WAKE_SLEEP);
      }
#endif /* (ECUM_ECUM_FIXED_SUPPORT == STD_ON) */
#if (ECUM_INCLUDE_DEM == STD_ON) \
 && (ECUM_PROD_ERR_RAM_CHECK_FAILURE == TS_PROD_ERR_REP_TO_DEM)
    if (EcuM_RamCheckStatus != ECUM_RAM_CHECK_STATUS_UNTESTED)
    {
      /* report result of last RamCheck, the last RamCheck is performed after
       * DEM was shutdown */
      Dem_ReportErrorStatus(
        EcuM_DemErrRamChkFailed,
          ( (EcuM_RamCheckStatus == ECUM_RAM_CHECK_STATUS_FAILED) ?
             DEM_EVENT_STATUS_FAILED : DEM_EVENT_STATUS_PASSED
          ));

      /* reset variable to only report status to Dem once */
      EcuM_RamCheckStatus = ECUM_RAM_CHECK_STATUS_UNTESTED;
    }
#endif
#if (ECUM_ECUM_FIXED_SUPPORT == STD_ON)
    EcuM_HandleRunRequests();
#endif /* (ECUM_ECUM_FIXED_SUPPORT == STD_ON) */
  }

  DBG_ECUM_MAINFUNCTION_EXIT();
}
/*--------------------------------------------------------------------------
 * Callbacks from BswM
 *--------------------------------------------------------------------------*/
#if (ECUM_ECUM_FIXED_SUPPORT == STD_ON)
FUNC(Std_ReturnType, ECUM_CODE) EcuM_GoRun(void)
{
  Std_ReturnType ret = E_NOT_OK;
  DBG_ECUM_GORUN_ENTRY();

#if (ECUM_DEV_ERROR_DETECT == STD_ON)
  if (EcuM_State == ECUM_STATE_UNINIT)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_GO_RUN, ECUM_E_UNINIT);
  }
  else
#endif /* (ECUM_DEV_ERROR_DETECT == STD_ON) */
  {
    EcuM_State=ECUM_STATE_APP_RUN;
    EcuM_RunTimeout = EcuM_ConfigPtr->RunTimeout;
    ECUM_EB_CURRENT_MODE_SWITCH(ECUM_EB_MODE_RUN);
    EcuM_OnEnterRun();
    ret = E_OK;
  }
  DBG_ECUM_GORUN_EXIT(E_OK);
  return ret;
}
#endif /* (ECUM_ECUM_FIXED_SUPPORT == STD_ON) */

/*--------------------------------------------------------------------------
 * Callbacks from wakeup sources
 *--------------------------------------------------------------------------*/

/*------------------[EcuM_SetWakeupEvent]-----------------------------------*/
FUNC(void, ECUM_CODE) EcuM_SetWakeupEvent(EcuM_WakeupSourceType sources)
{
  DBG_ECUM_SETWAKEUPEVENT_ENTRY(sources);

  /* checks for development error detection */
#if (ECUM_DEV_ERROR_DETECT == STD_ON)
  if (EcuM_State == ECUM_STATE_UNINIT)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_SET_WK_EV, ECUM_E_UNINIT);
  }
  else if ((sources & ECUM_WKSMASKALL) == 0U)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_SET_WK_EV, ECUM_E_UNKNOWN_WAKEUP_SOURCE);
  }
  else
#endif
  {
    uint8_least wks;            /* loop variable */

    /* The new wakeup events that require validation. */
    EcuM_WakeupSourceType wksPendingNew = 0U;

    /* The maximal timeout of the wakeup events set. */
    uint16 maxTimeout = 0U;

    /* consider only events for enabled wakeup sources */
    sources &= EcuM_SleepModeConfigList[EcuM_SleepMode].wakeupSource;

    EcuM_Enter_SCHM_ECUM_EXCLUSIVE_AREA_0();
    /* Contains only the new pending wakeup sources that require validation. */
    /* !LINKSTO EcuM2572,1 */
    wksPendingNew = sources & (EcuM_WakeupSourceType)~(EcuM_WksPending | ECUM_WKSMASKNOVAL);

    EcuM_Exit_SCHM_ECUM_EXCLUSIVE_AREA_0();

    EcuM_SwitchWakeupStatus(wksPendingNew, ECUM_WKSTATUS_PENDING);
    EcuM_SwitchWakeupStatus((sources & ECUM_WKSMASKNOVAL), ECUM_WKSTATUS_VALIDATED);

    /* Only new pending events may prolong the validation timeout. */
    /* !LINKSTO EcuM2712,1 */
    wks = 0U;
    while (wksPendingNew != 0U)
    {
      if ((wksPendingNew & 0x01U) != 0U)
      {
        /* if current validation timeout is smaller than the validation
         * timeout required for this wakeup source update current timeout */
        if (maxTimeout < ECUM_WKS_VAL_TIMEOUT(wks))
        {
          /* !LINKSTO EcuM2709,1 */
          maxTimeout = ECUM_WKS_VAL_TIMEOUT(wks);
        }
      }
      wksPendingNew >>= 1U;
      wks++;
    }

    EcuM_Enter_SCHM_ECUM_EXCLUSIVE_AREA_0();
    if (EcuM_WksValCounter < maxTimeout)
    {
      EcuM_WksValCounter = maxTimeout;
    }
    EcuM_Exit_SCHM_ECUM_EXCLUSIVE_AREA_0();

  }

  DBG_ECUM_SETWAKEUPEVENT_EXIT(sources);
}

/*------------------[EcuM_ValidateWakeupEvent]------------------------------*/
FUNC(void, ECUM_CODE) EcuM_ValidateWakeupEvent(EcuM_WakeupSourceType sources)
{
  /* copy state to local variable first to protect against global state
   * variable change during evaluation of state variable */
  const EcuM_ASR40_StateType state      = EcuM_State; /* atomic copy */

  DBG_ECUM_VALIDATEWAKEUPEVENT_ENTRY(sources);

  /* checks for development error detection */
#if (ECUM_DEV_ERROR_DETECT == STD_ON)

  if (state == ECUM_STATE_UNINIT)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_VALIDATE_WK_EV, ECUM_E_UNINIT);
  }
  else if ((sources & ECUM_WKSMASKALL) == 0U)
  {
    ECUM_DET_REPORT_ERROR(
      ECUM_SID_VALIDATE_WK_EV, ECUM_E_UNKNOWN_WAKEUP_SOURCE);
  }
  else
#endif
  {
    /* remove not pending wakeup sources */
    sources &= EcuM_WksPending;

    /* if EcuM enters UP phase it sets the state set to either RUN
     * or ECUM_STATE_WAKEUP_VALIDATION */
    /* !LINKSTO EcuM2791,1 */
    if ((state & (EcuM_ASR40_StateType)~ECUM_SUBSTATE_MASK) == ECUM_STATE_RUN)
    {
      /* EcuM2790: EcuM_ValidateWakeupEvent shall return without effect for
       * all sources except communication channels when called while the ECU
       * Manager module is in the UP Phase. */

      /* remove wakeup sources without a ComM channel */
      sources &= ECUM_WKSMASKCOMMCH;
    }

    EcuM_SwitchWakeupStatus(sources, ECUM_WKSTATUS_VALIDATED);

    EcuM_Enter_SCHM_ECUM_EXCLUSIVE_AREA_0();
    EcuM_WksStopped |= sources;
    EcuM_Exit_SCHM_ECUM_EXCLUSIVE_AREA_0();
  }

  DBG_ECUM_VALIDATEWAKEUPEVENT_EXIT(sources);
}

/*------------------[ShutdownHook]------------------------------------------*/
#if (ECUM_PROVIDE_SHUTDOWN_HOOK == STD_ON)
void ShutdownHook(StatusType errorID)
{
  /* if enabled by configuration the EcuM provides a minimalistic
   * implementation of the ShutdownHook() callback function for the Os. */

  DBG_SHUTDOWNHOOK_ENTRY(errorID);

  TS_PARAM_UNUSED(errorID);
  EcuM_Shutdown();

  DBG_SHUTDOWNHOOK_EXIT(errorID);
}
#endif

#if (ECUM_ECUM_FIXED_SUPPORT == STD_ON)
FUNC(Std_ReturnType, ECUM_CODE) EcuM_ASR40_RequestRUN(EcuM_ASR40_UserType user)
{
  Std_ReturnType retVal = E_OK;

  DBG_ECUM_REQUESTRUN_ENTRY(user);
#if (ECUM_DEV_ERROR_DETECT == STD_ON)
  if (EcuM_State == ECUM_STATE_UNINIT)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_REQUEST_RUN, ECUM_E_UNINIT);
    retVal = E_NOT_OK;
  }
  else if((EcuM_RunReq[ECUM_USER_IDX(user)] & ((uint8)(1U << ECUM_USER_FLG(user)))) != 0U)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_REQUEST_RUN, ECUM_E_MULTIPLE_RUN_REQUESTS);
    retVal = E_NOT_OK;
  }
  else
#endif /* (ECUM_DEV_ERROR_DETECT == STD_ON) */
  {
    EcuM_Enter_SCHM_ECUM_EXCLUSIVE_AREA_0();
    if(EcuM_KillAllRUNRequested == FALSE)
    {
      EcuM_RunReq[ECUM_USER_IDX(user)] |= (uint8)(1U << ECUM_USER_FLG(user));
    }
    EcuM_Exit_SCHM_ECUM_EXCLUSIVE_AREA_0();
  }

  DBG_ECUM_REQUESTRUN_EXIT(retVal,user);
  return retVal;
}

/* !LINKSTO EcuM.EB.ASR32.EcuM107,1 */
#if ((ECUM_EB_ENABLE_ASR32_SERVICE_API == STD_ON) || \
    (ECUM_EB_DEFAULT_ASR_SERVICE_API == ECUM_EB_SERVICE_API_ASR32))
FUNC(Std_ReturnType, ECUM_CODE) EcuM_ASR32_RequestRUN(EcuM_ASR32_UserType user)
{
  Std_ReturnType retVal = E_OK;

  /* EcuM_ASR40_UserType and EcuM_ASR32_UserType are referencing to
   * the same base type. Therefore no argument type mapping is done. */
  retVal = EcuM_ASR40_RequestRUN(user);
  
  return retVal;
}
#endif

FUNC(Std_ReturnType, ECUM_CODE) EcuM_ASR40_ReleaseRUN(EcuM_ASR40_UserType user)
{
  Std_ReturnType retVal = E_OK;

  DBG_ECUM_RELEASERUN_ENTRY(user);
#if (ECUM_DEV_ERROR_DETECT == STD_ON)
  if (EcuM_State == ECUM_STATE_UNINIT)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_RELEASE_RUN, ECUM_E_UNINIT);
    retVal = E_NOT_OK;
  }
  else if((EcuM_RunReq[ECUM_USER_IDX(user)] & ((uint8)(1U << ECUM_USER_FLG(user)))) == 0U)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_RELEASE_RUN, ECUM_E_MISMATCHED_RUN_RELEASE);
    retVal = E_NOT_OK;
  }
  else
#endif /* (ECUM_DEV_ERROR_DETECT == STD_ON) */
  {
    EcuM_Enter_SCHM_ECUM_EXCLUSIVE_AREA_0();
    EcuM_RunReq[ECUM_USER_IDX(user)] &= (uint8)~((uint8)(1U << ECUM_USER_FLG(user)));
    EcuM_Exit_SCHM_ECUM_EXCLUSIVE_AREA_0();
  }

  DBG_ECUM_RELEASERUN_EXIT(retVal,user);
  return retVal;
}

/* !LINKSTO EcuM.EB.ASR32.EcuM107,1 */
#if ((ECUM_EB_ENABLE_ASR32_SERVICE_API == STD_ON) || \
    (ECUM_EB_DEFAULT_ASR_SERVICE_API == ECUM_EB_SERVICE_API_ASR32))
FUNC(Std_ReturnType, ECUM_CODE) EcuM_ASR32_ReleaseRUN(EcuM_ASR32_UserType user)
{
  Std_ReturnType retVal = E_OK;

  /* EcuM_ASR40_UserType and EcuM_ASR32_UserType are referencing to
   * the same base type. Therefore no argument type mapping is done. */
  retVal = EcuM_ASR40_ReleaseRUN(user);
  
  return retVal;
}
#endif

FUNC(Std_ReturnType, ECUM_CODE) EcuM_ASR40_RequestPOST_RUN(EcuM_ASR40_UserType user)
{
  Std_ReturnType retVal = E_OK;

  DBG_ECUM_REQUESTPOST_RUN_ENTRY(user);
#if (ECUM_DEV_ERROR_DETECT == STD_ON)
  if (EcuM_State == ECUM_STATE_UNINIT)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_REQUEST_POST_RUN, ECUM_E_UNINIT);
    retVal = E_NOT_OK;
  }
  else if((EcuM_PostRunReq[ECUM_USER_IDX(user)] & ((uint8)(1U << ECUM_USER_FLG(user)))) != 0U)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_REQUEST_POST_RUN, ECUM_E_MULTIPLE_RUN_REQUESTS);
    retVal = E_NOT_OK;
  }
  else
#endif /* (ECUM_DEV_ERROR_DETECT == STD_ON) */
  {
    EcuM_Enter_SCHM_ECUM_EXCLUSIVE_AREA_0();
    if(EcuM_KillAllRUNRequested == FALSE)
    {
      EcuM_PostRunReq[ECUM_USER_IDX(user)] |= (uint8)(1U << ECUM_USER_FLG(user));
    }
    EcuM_Exit_SCHM_ECUM_EXCLUSIVE_AREA_0();
  }

  DBG_ECUM_REQUESTPOST_RUN_EXIT(retVal,user);
  return retVal;
}

/* !LINKSTO EcuM.EB.ASR32.EcuM107,1 */
#if ((ECUM_EB_ENABLE_ASR32_SERVICE_API == STD_ON) || \
    (ECUM_EB_DEFAULT_ASR_SERVICE_API == ECUM_EB_SERVICE_API_ASR32))
FUNC(Std_ReturnType, ECUM_CODE) EcuM_ASR32_RequestPOST_RUN(EcuM_ASR32_UserType user)
{
  Std_ReturnType retVal = E_OK;

  /* EcuM_ASR40_UserType and EcuM_ASR32_UserType are referencing to
   * the same base type. Therefore no argument type mapping is done. */
  retVal = EcuM_ASR40_RequestPOST_RUN(user);
  
  return retVal;
}
#endif

FUNC(Std_ReturnType, ECUM_CODE) EcuM_ASR40_ReleasePOST_RUN(EcuM_ASR40_UserType user)
{
  Std_ReturnType retVal = E_OK;

  DBG_ECUM_RELEASEPOST_RUN_ENTRY(user);
#if (ECUM_DEV_ERROR_DETECT == STD_ON)
  if (EcuM_State == ECUM_STATE_UNINIT)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_RELEASE_POST_RUN, ECUM_E_UNINIT);
    retVal = E_NOT_OK;
  }
  else if((EcuM_PostRunReq[ECUM_USER_IDX(user)] & ((uint8)(1U << ECUM_USER_FLG(user)))) == 0U)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_RELEASE_POST_RUN, ECUM_E_MISMATCHED_RUN_RELEASE);
    retVal = E_NOT_OK;
  }
  else
#endif /* (ECUM_DEV_ERROR_DETECT == STD_ON) */
  {
    EcuM_Enter_SCHM_ECUM_EXCLUSIVE_AREA_0();
    EcuM_PostRunReq[ECUM_USER_IDX(user)] &= (uint8)~((uint8)(1U << ECUM_USER_FLG(user)));
    EcuM_Exit_SCHM_ECUM_EXCLUSIVE_AREA_0();
  }

  DBG_ECUM_RELEASEPOST_RUN_EXIT(retVal,user);
  return retVal;
}

/* !LINKSTO EcuM.EB.ASR32.EcuM107,1 */
#if ((ECUM_EB_ENABLE_ASR32_SERVICE_API == STD_ON) || \
    (ECUM_EB_DEFAULT_ASR_SERVICE_API == ECUM_EB_SERVICE_API_ASR32))
FUNC(Std_ReturnType, ECUM_CODE) EcuM_ASR32_ReleasePOST_RUN(EcuM_ASR32_UserType user)
{
  Std_ReturnType retVal = E_OK;

  /* EcuM_ASR40_UserType and EcuM_ASR32_UserType are referencing to
   * the same base type. Therefore no argument type mapping is done. */
  retVal = EcuM_ASR40_ReleasePOST_RUN(user);
  
  return retVal;
}
#endif

FUNC(void, ECUM_CODE) EcuM_KillAllRUNRequests(void)
{
  uint8 i;
  DBG_ECUM_KILLALLRUNREQUESTS_ENTRY();
#if (ECUM_DEV_ERROR_DETECT == STD_ON)
  if (EcuM_State == ECUM_STATE_UNINIT)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_KILL_ALL_RUN_REQUESTS, ECUM_E_UNINIT);
  }
  else
#endif /* (ECUM_DEV_ERROR_DETECT == STD_ON) */
  {
#if ((ECUM_INCLUDE_DEM == STD_ON) \
 && (ECUM_PROD_ERR_ALL_RUN_REQUESTS_KILLED == TS_PROD_ERR_REP_TO_DEM))
    Dem_ReportErrorStatus(
          EcuM_DemErrAllRUNRequestsKilled, ECUM_E_ALL_RUN_REQUESTS_KILLED);
#endif /* (ECUM_INCLUDE_DEM == STD_ON) */
    EcuM_Enter_SCHM_ECUM_EXCLUSIVE_AREA_0();
    EcuM_KillAllRUNRequested = TRUE;
    for(i=0U; i<ECUM_FIXED_USER_BITMAP_SIZE; i++)
    {
      EcuM_RunReq[i]=0U;
      EcuM_PostRunReq[i]=0U;
    }
    EcuM_Exit_SCHM_ECUM_EXCLUSIVE_AREA_0();
  }

  DBG_ECUM_KILLALLRUNREQUESTS_EXIT();
}
FUNC(EcuM_WakeupStatusType, ECUM_CODE)
    EcuM_GetStatusOfWakeupSource(EcuM_WakeupSourceType sources)
{
  EcuM_WakeupStatusType WakeupStatus = ECUM_WKSTATUS_DISABLED;
  DBG_ECUM_GETSTATUSOFWAKEUPSOURCE_ENTRY(sources);

#if (ECUM_DEV_ERROR_DETECT == STD_ON)
  if (EcuM_State == ECUM_STATE_UNINIT)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_GET_STAT_OF_WK_SRC, ECUM_E_UNINIT);
  }
  else
#endif /* (ECUM_DEV_ERROR_DETECT == STD_ON) */
  {
    if (sources == ECUM_WKSOURCE_ALL_SOURCES)
    {
      sources = ECUM_WKSMASKALL;
    }
    else if((sources & ((EcuM_WakeupSourceType)~ECUM_WKSMASKALL)) != 0U)
    {
#if (ECUM_DEV_ERROR_DETECT == STD_ON)
      ECUM_DET_REPORT_ERROR(ECUM_SID_GET_STAT_OF_WK_SRC, ECUM_E_UNKNOWN_WAKEUP_SOURCE);
#endif /* (ECUM_DEV_ERROR_DETECT == STD_ON) */
      sources &= ECUM_WKSMASKALL;
    }
    else
    {
      /* Nothing to do. */
    }
    if((sources & EcuM_WksValidated) != 0U)
    {
      WakeupStatus = ECUM_WKSTATUS_VALIDATED;
    }
    else if((sources & EcuM_WksPending) != 0U)
    {
      WakeupStatus = ECUM_WKSTATUS_PENDING;
    }
    else if((sources & EcuM_WksExpired) != 0U)
    {
      WakeupStatus = ECUM_WKSTATUS_EXPIRED;
    }
    else
    {
      WakeupStatus = ECUM_WKSTATUS_NONE;
    }
  }

  DBG_ECUM_GETSTATUSOFWAKEUPSOURCE_EXIT(WakeupStatus,sources);
  return WakeupStatus;
}
#endif /* (ECUM_ECUM_FIXED_SUPPORT == STD_ON) */
/*==================[internal function definitions]=========================*/

#if (ECUM_ECUM_FIXED_SUPPORT == STD_ON)
/*------------------[EcuM_HandleRunRequests]--------------------------------*/
STATIC FUNC(void, ECUM_CODE) EcuM_HandleRunRequests(void)
{
  DBG_ECUM_HANDLERUNREQUESTS_ENTRY();
  switch(EcuM_State)
  {
    case ECUM_STATE_APP_RUN:
      if(EcuM_RunTimeout > 0U)
      {
        EcuM_RunTimeout--;
      }
      /* Timeout has expired and there are no RUN requests, thus
       * call the callout, disable the ComM channels and switch to
       * APP_POST_RUN state. */
      else if(EcuM_IsRunReq() == FALSE)
      {
        EcuM_OnExitRun();
        EcuM_State = ECUM_STATE_APP_POST_RUN;
        ECUM_EB_CURRENT_MODE_SWITCH(ECUM_EB_MODE_POST_RUN);
      }
      else
      {
        /* Do nothing */
      }
      break;
    case ECUM_STATE_APP_POST_RUN:
      /* If a RUN request is made, switch back to APP_RUN state
       * immediately. */
      if(EcuM_IsRunReq() == TRUE)
      {
        /* Currently always returns E_OK */
        (void)EcuM_GoRun();
      }
      /* If there are no POST_RUN requests, call the callout and
       * go to shutdown state. BswM does the rest then. */
      else if (EcuM_IsPostRunReq() == FALSE)
      {
        EcuM_State = ECUM_STATE_PREP_SHUTDOWN;
        if (ECUM_STATE_SLEEP == EcuM_ShutdownTarget)
        {
          ECUM_EB_CURRENT_MODE_SWITCH(ECUM_EB_MODE_SLEEP);
        }
        else
        {
          /* ECUM_STATE_RESET or ECUM_STATE_OFF */
          ECUM_EB_CURRENT_MODE_SWITCH(ECUM_EB_MODE_SHUTDOWN);
        }
        EcuM_OnExitPostRun();
      }
      else
      {
        /* Do nothing */
      }
      break;
    default:
      /* Do nothing */
      break;
  }
  DBG_ECUM_HANDLERUNREQUESTS_EXIT();
}
#endif /* (ECUM_ECUM_FIXED_SUPPORT == STD_ON) */

/*------------------[EcuM_GoSleep]------------------------------------------*/
STATIC FUNC(void, ECUM_CODE) EcuM_GoSleep(void)
{
  EcuM_WakeupSourceType wksSleepMode = EcuM_SleepModeConfigList[EcuM_SleepMode].wakeupSource;
  /* PENDING wakeup events shall not be cleared. */
  EcuM_WakeupSourceType wksCleared = wksSleepMode & (EcuM_WakeupSourceType)~EcuM_WksPending;

  DBG_ECUM_GOSLEEP_ENTRY();

  EcuM_State = ECUM_STATE_GO_SLEEP;
#if (ECUM_ECUM_FIXED_SUPPORT == STD_ON)
  EcuM_KillAllRUNRequested = FALSE;
  EcuM_OnGoSleep();
#endif /* (ECUM_ECUM_FIXED_SUPPORT == STD_ON) */
  /* !LINKSTO EcuM2546,1 */
  EcuM_EnableWakeupSources(wksSleepMode);
  /* ENABLED is a super-state of NONE. */
  EcuM_SwitchWakeupStatus(wksSleepMode, ECUM_WKSTATUS_ENABLED);
  EcuM_SwitchWakeupStatus(wksCleared, ECUM_WKSTATUS_NONE);

  /* Prevent scheduling: The first Task which is allowed to be run after
   * wakeup is the task containing the EcuM_MainFunction()  */
  /* Deviation MISRA-2, MISRA-3, MISRA-4 */
#if (ECUM_MULTICORE_ENABLED == TRUE)
  (void)GetResource(RES_SCHEDULER_0);
#else
  (void)GetResource(RES_SCHEDULER);
#endif /* (ECUM_MULTICORE_ENABLED == TRUE) */

  /* Indicate to BswM the state of the cleared wakeup sources. */
  EcuM_WksIndicateStatus_NONE();

  /* store last shutdown target and sleep mode */
  EcuM_LastShutdownTarget = EcuM_ShutdownTarget;
  EcuM_LastSleepMode      = EcuM_SleepMode;
  EcuM_LastResetMode      = EcuM_ResetMode;

  EcuM_State = ECUM_STATE_SLEEP;

  DBG_ECUM_GOSLEEP_EXIT();
}

/*------------------[EcuM_WakeupRestart-------------------------------------*/
STATIC FUNC(void, ECUM_CODE) EcuM_WakeupRestart(void)
{
  DBG_ECUM_WAKEUPRESTART_ENTRY();

  /* *** Wakeup Restart sequence *** */

  /* restore MCU normal mode */
  Mcu_SetMode(ECUM_NORMALMCUMODE);

  /* Disable the wakeup sources that were set. */
  if ((EcuM_WksPending != 0U) || (EcuM_WksValidated != 0U))
    {
    /* Invoke callout for disabling current pending or validated wakeup
     * sources. Disable currently pending wakeup source but leave the others
     * armed so that later wakeups are possible. */
    EcuM_WakeupSourceType wksDisable = EcuM_WksPending | EcuM_WksValidated;
    EcuM_DisableWakeupSources(wksDisable);
    EcuM_SwitchWakeupStatus(wksDisable, ECUM_WKSTATUS_DISABLED);

   /* The disabled wakeup events are indicated to BswM in EcuM_MainFunction */
    }

#if (ECUM_INITLIST_RESTART == STD_ON)
  /* Restart driver of restart list: Initialize drivers that need
   * restarting */
  EcuM_AL_DriverRestart(EcuM_ConfigPtr); /* initialize configured drivers */
#endif

  /* Allow Scheduling */
  /* Deviation MISRA-2, MISRA-3, MISRA-4 */
#if (ECUM_MULTICORE_ENABLED == TRUE)
  (void)ReleaseResource(RES_SCHEDULER_0);
#else
  (void)ReleaseResource(RES_SCHEDULER);
#endif /* (ECUM_MULTICORE_ENABLED == TRUE) */

  /* *** Enter Wakeup Validation *** */

  /* validation timer was wound up in EcuM_SetWakeupEvent() */

  EcuM_State = ECUM_STATE_WAKEUP_VALIDATION;

  DBG_ECUM_WAKEUPRESTART_EXIT();
}

/*------------------[EcuM Wakeup Source State Management]---------------------------*/
STATIC FUNC(void, ECUM_CODE) EcuM_SwitchWakeupStatus
(
  EcuM_WakeupSourceType sources,
  EcuM_WakeupStatusType status
)
{
  DBG_ECUM_SWITCHWAKEUPSTATUS_ENTRY(sources, status);

  EcuM_Enter_SCHM_ECUM_EXCLUSIVE_AREA_0();
  switch(status)
  {
    case ECUM_WKSTATUS_ENABLED:
    {
      /* No notification will be sent to the BswM since ENABLED is not a
       * specified state. This is for internal use only. See the function
       * prototype comment for more information on the state ENABLED. */
      EcuM_WksDisabled &= (EcuM_WakeupSourceType)~sources;
      break;
    }
    case ECUM_WKSTATUS_DISABLED:
    {
      EcuM_WksIndicateDisabled |= sources;
      EcuM_WksDisabled |= sources;
      break;
    }
    case ECUM_WKSTATUS_NONE:
    {
      EcuM_WksIndicateNone |= sources;
      EcuM_WksNone |= sources;

      EcuM_WksExpired &= (EcuM_WakeupSourceType)~sources;
      EcuM_WksPending &= (EcuM_WakeupSourceType)~sources;
      EcuM_WksValidated &= (EcuM_WakeupSourceType)~sources;
      break;
    }
    case ECUM_WKSTATUS_PENDING:
    {
      EcuM_WksIndicatePending |= sources;
      EcuM_WksPending |= sources;

      EcuM_WksExpired &= (EcuM_WakeupSourceType)~sources;
      EcuM_WksNone &= (EcuM_WakeupSourceType)~sources;
      EcuM_WksValidated &= (EcuM_WakeupSourceType)~sources;
      break;
    }
    case ECUM_WKSTATUS_VALIDATED:
    {
      EcuM_WksIndicateValidated |= sources;
      EcuM_WksValidated |= sources;

      EcuM_WksExpired &= (EcuM_WakeupSourceType)~sources;
      EcuM_WksNone &= (EcuM_WakeupSourceType)~sources;
      EcuM_WksPending &= (EcuM_WakeupSourceType)~sources;
      break;
    }
    case ECUM_WKSTATUS_EXPIRED:
    {
      EcuM_WksIndicateExpired |= sources;
      EcuM_WksExpired |= sources;

      EcuM_WksNone &= (EcuM_WakeupSourceType)~sources;
      EcuM_WksPending &= (EcuM_WakeupSourceType)~sources;
      EcuM_WksValidated &= (EcuM_WakeupSourceType)~sources;
      break;
    }
    /* CHECK: NOPARSE */
    default:
    {
      ECUM_UNREACHABLE_CODE_ASSERT(ECUM_INTERNAL_API_ID);
      /* Should never be entered. */
      break;
    }
    /* CHECK: PARSE */
  }
  EcuM_Exit_SCHM_ECUM_EXCLUSIVE_AREA_0();

  DBG_ECUM_SWITCHWAKEUPSTATUS_EXIT(sources, status);
}

STATIC FUNC(void, ECUM_CODE) EcuM_WksIndicateStatus_DISABLED(void)
{
  EcuM_WakeupSourceType wksDisabled;

  DBG_ECUM_WKSINDICATESTATUS_DISABLED_ENTRY();

  EcuM_Enter_SCHM_ECUM_EXCLUSIVE_AREA_0();
  wksDisabled = EcuM_WksIndicateDisabled;
  EcuM_WksIndicateDisabled = 0U;
  EcuM_Exit_SCHM_ECUM_EXCLUSIVE_AREA_0();

  if (wksDisabled != 0U)
  {
    BswM_EcuM_CurrentWakeup(wksDisabled, ECUM_WKSTATUS_DISABLED);
  }

  DBG_ECUM_WKSINDICATESTATUS_DISABLED_EXIT();
}

STATIC FUNC(void, ECUM_CODE) EcuM_WksIndicateStatus_PENDING(void)
{
  EcuM_WakeupSourceType wksPending;

  DBG_ECUM_WKSINDICATESTATUS_PENDING_ENTRY();

  EcuM_Enter_SCHM_ECUM_EXCLUSIVE_AREA_0();
  wksPending = EcuM_WksIndicatePending;
  EcuM_WksIndicatePending = 0U;
  EcuM_Exit_SCHM_ECUM_EXCLUSIVE_AREA_0();

  if (wksPending != 0U)
  {
    BswM_EcuM_CurrentWakeup(wksPending, ECUM_WKSTATUS_PENDING);
  }

  DBG_ECUM_WKSINDICATESTATUS_PENDING_EXIT();
}

STATIC FUNC(void, ECUM_CODE) EcuM_WksIndicateStatus_VALIDATED(void)
{
  EcuM_WakeupSourceType wksValidated;

  DBG_ECUM_WKSINDICATESTATUS_VALIDATED_ENTRY();

  EcuM_Enter_SCHM_ECUM_EXCLUSIVE_AREA_0();
  wksValidated = EcuM_WksIndicateValidated;
  EcuM_WksIndicateValidated = 0U;
  EcuM_Exit_SCHM_ECUM_EXCLUSIVE_AREA_0();

  if (wksValidated != 0U)
  {
    BswM_EcuM_CurrentWakeup(wksValidated, ECUM_WKSTATUS_VALIDATED);
#if (ECUM_WKS_COMMCH_ENABLED == STD_ON)
    EcuM_ComMWakeupIndication(wksValidated & ECUM_WKSMASKCOMMCH);
#endif
  }

  DBG_ECUM_WKSINDICATESTATUS_VALIDATED_EXIT();
}

STATIC FUNC(void, ECUM_CODE) EcuM_WksIndicateStatus_EXPIRED(void)
{
  EcuM_WakeupSourceType wksExpired;

  DBG_ECUM_WKSINDICATESTATUS_EXPIRED_ENTRY();

  EcuM_Enter_SCHM_ECUM_EXCLUSIVE_AREA_0();
  wksExpired = EcuM_WksIndicateExpired;
  EcuM_WksIndicateExpired = 0U;
  EcuM_Exit_SCHM_ECUM_EXCLUSIVE_AREA_0();

  /* EcuM_WksIndicateStatus_EXPIRED() is called only if one or more wakeup
   * sources have just expired.  Therefore, the guard check is not needed.  */
  BswM_EcuM_CurrentWakeup(wksExpired, ECUM_WKSTATUS_EXPIRED);

  DBG_ECUM_WKSINDICATESTATUS_EXPIRED_EXIT();
}

STATIC FUNC(void, ECUM_CODE) EcuM_WksIndicateStatus_NONE(void)
{
  EcuM_WakeupSourceType wksNone;

  DBG_ECUM_WKSINDICATESTATUS_NONE_ENTRY();

  EcuM_Enter_SCHM_ECUM_EXCLUSIVE_AREA_0();
  wksNone = EcuM_WksIndicateNone;
  EcuM_WksIndicateNone = 0U;
  EcuM_Exit_SCHM_ECUM_EXCLUSIVE_AREA_0();

  if (wksNone != 0U)
  {
    BswM_EcuM_CurrentWakeup(wksNone, ECUM_WKSTATUS_NONE);
  }

  DBG_ECUM_WKSINDICATESTATUS_NONE_EXIT();
}

/*------------------[EcuM_ComMWakeupIndication]-------------------------------------*/
#if (ECUM_WKS_COMMCH_ENABLED == STD_ON)
STATIC FUNC(void, ECUM_CODE)EcuM_ComMWakeupIndication
(
  EcuM_WakeupSourceType ComMevents
)
{
  uint8_least           wks = 0U;           /* loop variable */
  ComM_InitStatusType   Status;             /* Initialization status of ComM */
  Std_ReturnType        RetVal = E_NOT_OK;  /* Return value of ComM_GetStatus */

  DBG_ECUM_COMMWAKEUPINDICATION_ENTRY(ComMevents);

  /* Requirement: EcuM.ComMWakeupIndication
   *
   * Get the initialization status of Communication Manager and
   * indicate wakeup notification to ComM only if ComM had successfully
   * initialized and is usable. */
  RetVal = ComM_GetStatus(&Status);

  if ( (E_OK == RetVal) && (COMM_INIT == Status) )
  {
    while (ComMevents != 0U)
    {
      if ((ComMevents & 1U) != 0U)
      {
        /* Inform ComM about the event */
        ComM_EcuM_WakeUpIndication(ECUM_WKSID_TO_CFG(wks).ComMCh);
      }
      ComMevents >>= 1U;
      ++wks;
    }
  }

  DBG_ECUM_COMMWAKEUPINDICATION_EXIT(ComMevents);
}
#endif

#if (ECUM_ECUM_FIXED_SUPPORT == STD_ON)
STATIC FUNC(boolean, ECUM_CODE)EcuM_IsRunReq(void)
{
  uint8 i;
  boolean retVal = FALSE;

  DBG_ECUM_ISRUNREQ_ENTRY();
  for(i=0U; i<ECUM_FIXED_USER_BITMAP_SIZE; i++)
  {
    if(EcuM_RunReq[i] != 0U)
    {
       retVal = TRUE;
    }
  }

  DBG_ECUM_ISRUNREQ_EXIT(retVal);
  return retVal;
}
STATIC FUNC(boolean, ECUM_CODE)EcuM_IsPostRunReq(void)
{
  uint8 i;
  boolean retVal = FALSE;

  DBG_ECUM_ISPOSTRUNREQ_ENTRY();
  for(i=0U; i<ECUM_FIXED_USER_BITMAP_SIZE; i++)
  {
    if(EcuM_PostRunReq[i] != 0U)
    {
       retVal = TRUE;
    }
  }

  DBG_ECUM_ISPOSTRUNREQ_EXIT(retVal);
  return retVal;
}
#endif /* (ECUM_ECUM_FIXED_SUPPORT == STD_ON) */
#define ECUM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[end of file]===========================================*/
