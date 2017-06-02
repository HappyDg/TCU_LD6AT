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

/* Implementation of the state handler functions of the state machine
 * ComM.
 *
 * This file contains the implementation of the state functions.  It
 * is generated but must be edited to implement the real actions.  If the
 * state machine model is updated and the code generator regenerates the
 * files the user must manually merge the changes with any existing hand
 * written code.
 */

/* MISRA-C:2004 Deviation List
 *
 * MISRA-1) Deviated Rule: 19.13 (advisory)
 *      The #and ##preprocessor operators should not be used.
 *
 *     Reason:
 *     Encapsulation of generic code into macros improves readability
 *     by reducing redundant code.
 *
 * MISRA-2) Deviated Rule: 12.4 (required)
 *     The right-hand operand of a logical '&&' or '||' operator
 *     shall not contain side effects.
 *
 *     Reason:
 *     Function like macros and functions are used to read configuration
 *     settings and variables.  These constructs are free of side effects.
 *
 * MISRA-3) Deviated Rule: 13.7 (required)
 *     Boolean operations whose results are invariant shall not be permitted.
 *
 *     Reason:
 *     This is not a programming error. This approach has been deliberately
 *     selected to apply a common method to access the channel configuration
 *     data in all configuration possibilities.
 */

/* CHECK: RULE 301 OFF (this file is partly generated, some lines may be
 * longer then 100 characters) */

/*==================[inclusions]============================================*/

/* prevent RTE symbols defined in ComM.h to be visible for ComM's .c files */
#define COMM_INTERNAL_USAGE

#include <ComM_Trace.h>
#include <ComM_BSW.h>
#include <ComM_BSW_Cfg.h>
#include <ComM_Int.h>

#if (COMM_NM_ACCESS_NEEDED == STD_ON)
#include <ComM_Nm.h>             /* NM callback APIs */
#include <NmStack_Types.h> /* Nm stack specific types, includes Std_Types.h */

/* !LINKSTO ComM506_Refine_Nm,1 */
#include <Nm.h>                /* Network Management Identifiers */
#endif /* (COMM_NM_ACCESS_NEEDED == STD_ON) */

/* !LINKSTO ComM506_Refine_Dcm,1 */
#if (COMM_DCM_ENABLED == STD_ON)
#include <Dcm_Cbk.h>            /* Diagnostic communication manager */
#endif

/* !LINKSTO ComM506_Refine_BswM,1 */
#include <BswM_ComM.h>

/* !LINKSTO ComM506_Refine_CanSM,1 */
#if (COMM_CANSM_ACCESS_NEEDED == STD_ON)
#include <CanSM_ComM.h>        /* Can state manager */
#endif

/* !LINKSTO ComM506_Refine_FrSM,1 */
#if (COMM_FRSM_ACCESS_NEEDED == STD_ON)
#include <FrSM.h>              /* Flexray state manager */
#endif

/* !LINKSTO ComM506_Refine_LinSM,1 */
#if (COMM_LINSM_ACCESS_NEEDED == STD_ON)
#include <LinSM.h>             /* Lin state manager */
#endif
/* !LINKSTO ComM506_Refine_EthSM,1 */
#if (COMM_ETHSM_ACCESS_NEEDED == STD_ON)
#include <EthSM.h>             /* Eth state manager */
#endif

#if (COMM_DEV_ERROR_DETECT == STD_ON)
#include <Det.h>               /* Det API */
#endif

/*==================[macros]================================================*/

#define COMM_NM_RETRY_TIME    1U
#define COMM_BUSSM_RETRY_TIME 1U

#if (COMM_HSM_INST_MULTI_ENABLED == STD_ON)
#define COMM_PARAM_UNUSED(instIdx)      TS_PARAM_UNUSED(instIdx)
#define ComM_Notify(a,b)                ComM_Notify2Arg(a,b)
#define ComM_BusSmRequestComMode(a,b)   ComM_BusSmRequestComMode2Arg(a,b)
#define COMM_CHANNEL(a)                 (a)
#else
#define COMM_PARAM_UNUSED(instIdx)      /* nothing */
#define ComM_Notify(a,b)                ComM_Notify1Arg(b)
#define ComM_BusSmRequestComMode(a,b)   ComM_BusSmRequestComMode1Arg(b)
#define COMM_CHANNEL(a)                 0U
#endif

#define ComM_StartTimer(Channel,Event,StartValue) \
  do                                              \
  {                                               \
    COMM_TIMEOUT_EVENT(Channel) = (Event);        \
    COMM_TIMER(Channel)         = (StartValue);   \
  } while (0)
#define ComM_StopTimer(a)  ComM_StartTimer(a, COMM_HSM_EVENT_INVALID, 0U)

/* Deviation MISRA-1 <START> */
/* Define wrapper to NM functions only if ComM requires Nm access */
#if (COMM_NM_ACCESS_NEEDED == STD_ON)
/** \brief Call wrapper to Nm_*() functions */
#define COMM_NM_CALL(func,channel) \
  ((void)Nm_##func(COMM_NM_CHANNEL_OF_CHANNEL(channel)))

/** \brief Call wrapper to call Nm_PassiveStartUp() */
#define COMM_NM_PASSIVESTARTUP(channel) COMM_NM_CALL(PassiveStartUp,channel)
/** \brief Call wrapper to call Nm_NetworkRelease() */
#define COMM_NM_NETWORKRELEASE(channel) COMM_NM_CALL(NetworkRelease,channel)
/** \brief Call wrapper to call Nm_NetworkRequest() */
#define COMM_NM_NETWORKREQUEST(channel) COMM_NM_CALL(NetworkRequest,channel)
#endif  /* COMM_NM_ACCESS_NEEDED == STD_ON */
/* Deviation MISRA-1 <STOP> */

/** \brief Call wrapper for bus state manager function
 * <Bus>SM_GetCurrentComMode() */
#define COMM_BUSSM_GET_CURRENT_COM_MODE(channel, mode)                  \
  (ComM_BusSMGetCurrentComModeFpList[COMM_BUSTYPE_OF_CHANNEL(channel)]( \
    COMM_CHANNEL(channel), (mode)))

#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
/** \brief Evaluate NoCom Inhibition status for ComM channels
 *
 * Always FALSE if mode limitation is disabled. */
#define COMM_CHANNEL_NOCOM_INHIBITION_STATUS(a)        \
  ComM_ChannelNoComInhibitionStatus(COMM_CHANNEL(a))
#else
#define COMM_CHANNEL_NOCOM_INHIBITION_STATUS(a)  FALSE
#endif

#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
/** \brief WakeUp Inhibition status for ComM channels
 *
 * always FALSE if wakeup inhibition is disabled. */
#define COMM_CHANNEL_WAKEUP_INHIBITION_STATUS(a)       \
  ComM_ChannelWakeUpInhibitionStatus(COMM_CHANNEL(a))
#else
#define COMM_CHANNEL_WAKEUP_INHIBITION_STATUS(a) FALSE
#endif

/** \brief Time counter value for checking the timeouts of different states */
#define COMM_TIMER(Channel)                     \
  COMM_INST_ACCESS(ComM_Timer,Channel)

/** \brief Time counter value for checking the timeouts of different states */
#define COMM_TIMEOUT_EVENT(Channel)             \
  COMM_INST_ACCESS(ComM_TimeoutEvent,Channel)

/** \brief Main function period in ms for each channel in ms. */
#define COMM_MAINFUNCTIONPERIODMS(Channel)              \
  COMM_INST_ACCESS(ComM_MainFunctionPeriodMs,Channel)

/** \brief Current mode of the ComM Channel. */
#define COMM_CHANNELMODE(Channel)               \
  COMM_INST_ACCESS(ComM_ChannelMode,Channel)

/** \brief Current state of the ComM Channel. */
#define COMM_CHANNELSTATE(Channel)               \
  COMM_INST_ACCESS(ComM_ChanState,Channel)

/** \brief User ID of a channel. */
#define COMM_USERSOFCHANNEL(Channel,i)                  \
  (COMM_INST_ACCESS(ComM_UsersOfChannel,Channel)[(i)])

/** \brief Currently requested ComM Mode. */
#define COMM_REQUESTEDCOMMODE(Channel)                  \
  COMM_INST_ACCESS(ComM_RequestedComMode,Channel)

/** \brief Ready Sleep Timeout. */
#define COMM_READYSLEEPNONMTIMEOUTMS(Channel)                   \
  COMM_INST_ACCESS(ComM_ReadySleepNoNmTimeoutMs,Channel)

/** \brief Full Com Mode Duration. */
#define COMM_MIN_FULL_COM_MODE_DURATION(Channel)                   \
  COMM_INST_ACCESS(ComM_NetReqNoNmTimeoutMs,Channel)

/*--------------------------------------------------------------------------*/

/* Macros for the abstraction of the RTE callback functions.
 * The macros resolve to the required callback function names according to
 * the service API configuration (default, ASR40, ASR32)
 */

#if (defined COMM_EB_DEFAULT_RTE_NOTIFY)
#error COMM_EB_DEFAULT_RTE_NOTIFY already defined
#endif
#if ((COMM_INCLUDE_RTE == STD_ON) && \
    (COMM_DEFAULT_ASR_SERVICE_API != COMM_SERVICE_API_NONE))
/** \brief Signal the user the current communication mode via Rte
 *
 * The macro receives the user handle and gets the current communication mode
 * and propagates the arguments to the corresponding default RTE handle
 * function.
 *
 * If the default service API is set to NONE then the macro is defined empty.
 *
 * The return value of the RTE call is ignored on purpose because the ComM
 * does not have a strategy to handle failing SW-C calls.
 *
 * \param[in] user       the user to be notified as uint8 value
 */
#define COMM_EB_DEFAULT_RTE_NOTIFY(user)      \
  do { \
    ComM_ASR40_ModeType CurComMMode; \
    if (E_OK == ComM_ASR40_GetCurrentComMode((user), &CurComMMode)) \
    { \
      ComM_RteNotify((user), CurComMMode); \
    } \
  } while (0)
#else
#define COMM_EB_DEFAULT_RTE_NOTIFY(user)
#endif

#if (defined COMM_EB_ASR40_RTE_NOTIFY)
#error COMM_EB_ASR40_RTE_NOTIFY already defined
#endif
#if ((COMM_INCLUDE_RTE == STD_ON) && \
     (COMM_ENABLE_ASR40_SERVICE_API == STD_ON))
/** \brief Signal the user the current communication mode via ASR40 Rte
 * callbacks
 *
 * The macro receives the user handle, gets the current communication mode and
 * propagates the arguments to the corresponding ASR40 RTE handle function.
 *
 * If the ASR40 service API is set to STD_OFF then the macro is defined empty.
 *
 * The return value of the RTE call is ignored on purpose because the ComM
 * does not have a strategy to handle failing SW-C calls.
 *
 * \param[in] user       the user to be notified as uint8 value
 */
#define COMM_EB_ASR40_RTE_NOTIFY(user)      \
  do { \
    ComM_ASR40_ModeType CurASR40ComMMode; \
    if (E_OK == ComM_ASR40_GetCurrentComMode((user), &CurASR40ComMMode)) \
    { \
      ComM_ASR40_RteNotify((user), (CurASR40ComMMode)); \
    } \
  } while (0)
#else
#define COMM_EB_ASR40_RTE_NOTIFY(user)
#endif

#if (defined COMM_EB_ASR32_RTE_NOTIFY)
#error COMM_EB_ASR32_RTE_NOTIFY already defined
#endif
#if ((COMM_INCLUDE_RTE == STD_ON) && \
     (COMM_ENABLE_ASR32_SERVICE_API == STD_ON))
/** \brief Signal the user the current communication mode via ASR32 Rte
 * callbacks
 *
 * The macro receives the user handle, gets the current communication mode and
 * propagates the arguments to the corresponding ASR32 RTE handle function.
 *
 * If the ASR32 service API is set to STD_OFF then the macro is defined empty.
 *
 * The return value of the RTE call is ignored on purpose because the ComM
 * does not have a strategy to handle failing SW-C calls.
 *
 * \param[in] user       the user to be notified as uint8 value
 */
#define COMM_EB_ASR32_RTE_NOTIFY(user)      \
  do { \
    ComM_ASR32_ModeType CurASR32ComMMode; \
    if (E_OK == ComM_ASR32_GetCurrentComMode((user), &CurASR32ComMMode)) \
    { \
      ComM_ASR32_RteNotify((user), (CurASR32ComMMode)); \
    } \
  } while (0)
#else
#define COMM_EB_ASR32_RTE_NOTIFY(user)
#endif

#if (defined COMM_EB_RTE_NOTIFY)
#error COMM_EB_RTE_NOTIFY already defined
#endif
#if (COMM_INCLUDE_RTE == STD_ON)
/** \brief Signal the user the current communication mode via ASR32 Rte
 * callbacks
 *
 * The macro receives the user handle and propagates the argument to the
 * corresponding sub-macros for the specific RTE handle functions.
 *
 * If the RTE is set to STD_OFF then the macro is defined empty.
 *
 * \param[in] user       the user to be notified as uint8 value
 */
#define COMM_EB_RTE_NOTIFY(user)      \
  do { \
      COMM_EB_ASR32_RTE_NOTIFY((user));\
      COMM_EB_ASR40_RTE_NOTIFY((user));\
      COMM_EB_DEFAULT_RTE_NOTIFY((user));\
  } while (0)
#else
#define COMM_EB_RTE_NOTIFY(user, curcommod)
#endif

/*--------------------------------------------------------------------------*/

/*==================[type definitions]======================================*/

/** \brief Function pointer type for the bus state manager functions to
 ** request a new communication mode. */
typedef P2FUNC(Std_ReturnType, COMM_CODE, ComM_BusSMRequestComModeType)(
  NetworkHandleType Channel,
  uint8             ComMode);

/** \brief Function pointer type for the bus state manager functions to
 ** query the current communication mode. */
typedef P2FUNC(Std_ReturnType, COMM_CODE, ComM_BusSMGetCurrentComModeType)
(
  NetworkHandleType                       Channel,
  P2VAR(uint8, AUTOMATIC, COMM_APPL_DATA) ComMode
);

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

#define COMM_START_SEC_CODE
#include <MemMap.h>
/** \brief Notify Mode Transition of ComM channels to RTE ,DCM and BSWM ,
 **
 ** This function notifies the mode change of all ComM channels to RTE(if RTE
 ** enabled) , DCM and BSWM.
 **
 ** \param[in] Channel Channel Network channel on which the mode transition
 **                    has occurred.
 ** \param[in] ComMode Maximum allowed communication mode. */
STATIC FUNC(void, COMM_CODE) ComM_Notify(
  uint8               Channel,
  const ComM_ModeType ComMMode);

/** \brief Check current BusSm mode and request a new one if needed
 **
 ** \param[in] Channel Network channel on which the mode transition
 ** has occurred.
 ** \param[in] reqComMMode communication mode. */
STATIC FUNC(void, COMM_CODE) ComM_BusSmRequestComMode(
  const uint8         Channel,
  const ComM_ModeType reqComMMode);

/** \brief Manage the BusSM rerequest counter and trigger further actions in
 **  dependency of its value.
 **
 **  If the user defined number of BusSM requests occurred within a state
 **  event BUSSM_RETRY_COUNT_LIMIT will be emitted. Otherwise further rerequests
 **  will be triggered.
 **
 ** \param[in] Channel  Network channel on which the mode transition
 **                     has occurred. */
STATIC FUNC(void, COMM_CODE) ComM_RetryBusSmRequest(
  const uint8         Channel);

#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
 /** \brief Clears all ComM requests
 **
 ** This function clears all ComM user requests and set the state to No
 ** ComMode.
 **
 ** \param[in] instIdx index of state machine instance. */
STATIC FUNC(void, COMM_CODE)
  ComM_ClearUserRequest(COMM_PDL_SF(const uint8 instIdx));
#endif

/** \brief Evaluate if the channel can be released.
 **
 ** This function checks if the channel can be released.
 **
 ** \param[in] Channel Network channel on which the mode transition has
 **            occurred. */
STATIC FUNC(boolean, COMM_CODE) ComM_IsChanRelAllowed(
  COMM_PDL_SF(const uint8 Channel));

/** \brief Evaluate if the channel can be requested in full com mode.
 **
 ** This function checks if the channel can be requested in full com mode.
 **
 ** \param[in] Channel Network channel on which the mode transition has
 **            occurred. */
STATIC FUNC(boolean, COMM_CODE) ComM_IsChanReqAllowedFullCom(
  COMM_PDL_SF(const uint8 Channel));

/** \brief Evaluate if the channel can be requested in no com mode.
 **
 ** This function checks if the channel can be requested in no com mode.
 **
 ** \param[in] Channel Network channel on which the mode transition has
 **            occurred. */
STATIC FUNC(boolean, COMM_CODE) ComM_IsChanReqAllowedNoFullCom(
  COMM_PDL_SF(const uint8 Channel));

 /** \brief Emits the event NM_NETWORK_MODE if current mode is NM_MODE_NETWORK.
 **
 ** \param[in] Channel Network channel on which the mode transition has
 **            occurred. */
STATIC FUNC(void, COMM_CODE) ComM_CheckNwr(
  COMM_PDL_SF(const uint8 Channel));

#define COMM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

#define COMM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief Stores function pointer for bus specific state managers **/
STATIC CONST(ComM_BusSMRequestComModeType, COMM_CONST)
  ComM_BusSMRequestComModeFpList[5] =
{
#if (COMM_CANSM_ACCESS_NEEDED == STD_ON)
  &CanSM_RequestComMode,         /* COMM_BUS_TYPE_CAN = 0 */
#else
  NULL_PTR,                /* never accessed if no CAN channel is available */
#endif
#if (COMM_ETHSM_ACCESS_NEEDED == STD_ON)
  &EthSM_RequestComMode,         /* COMM_BUS_TYPE_ETH = 1 */
#else
  NULL_PTR,                /* never accessed if no ETH channel is available */
#endif
#if (COMM_FRSM_ACCESS_NEEDED == STD_ON)
  &FrSM_RequestComMode,          /* COMM_BUS_TYPE_FR = 2 */
#else
  NULL_PTR,                 /* never accessed if no FR channel is available */
#endif
  NULL_PTR,                 /* COMM_BUS_TYPE_INTERNAL = 3 */
#if (COMM_LINSM_ACCESS_NEEDED == STD_ON)
  &LinSM_RequestComMode         /* COMM_BUS_TYPE_LIN = 4 */
#else
  NULL_PTR                /* never accessed if no LIN channel is available */
#endif
};

/** \brief Stores function pointer for bus specific state managers **/
STATIC CONST(ComM_BusSMGetCurrentComModeType, COMM_CONST)
  ComM_BusSMGetCurrentComModeFpList[5] =
{
#if (COMM_CANSM_ACCESS_NEEDED == STD_ON)
  &CanSM_GetCurrentComMode,      /* COMM_BUS_TYPE_CAN = 0 */
#else
  NULL_PTR,                /* never accessed if no CAN channel is available */
#endif
#if (COMM_ETHSM_ACCESS_NEEDED == STD_ON)
  &EthSM_GetCurrentComMode,      /* COMM_BUS_TYPE_ETH = 1 */
#else
  NULL_PTR,                /* never accessed if no CAN channel is available */
#endif
#if (COMM_FRSM_ACCESS_NEEDED == STD_ON)
  &FrSM_GetCurrentComMode,       /* COMM_BUS_TYPE_FR = 2 */
#else
  NULL_PTR,                 /* never accessed if no FR channel is available */
#endif
  NULL_PTR,                   /* COMM_BUS_TYPE_INTERNAL = 3 */
#if (COMM_LINSM_ACCESS_NEEDED == STD_ON)
  &LinSM_GetCurrentComMode      /* COMM_BUS_TYPE_LIN = 4 */
#else
  NULL_PTR                /* never accessed if no LIN channel is available */
#endif
};

#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

#define COMM_START_SEC_VAR_INIT_16
#include <MemMap.h>

/** \brief Time counter value for checking the timeouts of different states */
STATIC VAR(uint16, COMM_VAR) ComM_Timer[COMM_NUM_CHANNELS];

/** \brief  Stores the current counter value for every channel how often
 ** BusSM_RequestComMode() has been rerequested. */
STATIC VAR(uint16, COMM_VAR) ComM_BusSMRetryCounter[COMM_NUM_CHANNELS];

#define COMM_STOP_SEC_VAR_INIT_16
#include <MemMap.h>

#define COMM_START_SEC_VAR_INIT_8
#include <MemMap.h>

/** \brief Event to be sent on timeout */
STATIC VAR(ComM_HsmEventType, COMM_VAR) ComM_TimeoutEvent[COMM_NUM_CHANNELS];

#define COMM_STOP_SEC_VAR_INIT_8
#include <MemMap.h>


/*==================[external function definitions]=========================*/

#define COMM_START_SEC_CODE
#include <MemMap.h>

/* ************************ state functions ******************************* */

/* ************************************************************************
 * State: TOP
 * Parent state: none
 * Init substate: NoCom
 * Transitions originating from this state:
 */


/* ************************************************************************
 * State: FullCom
 * Parent state: TOP
 * Init substate: FullComNotified
 * Transitions originating from this state:
 * 1) FullCom -> SilentCom: NM_PREP_BUS_SLEEP_MODE[]/
 */


/* ************************************************************************
 * State: FullComNotified
 * Parent state: FullCom
 * Init substate: AcceptLimitToNoCom
 * Transitions originating from this state:
 * 1) FullComNotified -> WaitForNoCom: NM_BUS_SLEEP_MODE[]/
 *    if (ComMNmVariant==FULL) Nm_NetworkRelease();
 */

FUNC(void, COMM_CODE) ComM_HsmComMSfFullComNotifiedEntry(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFFULLCOMNOTIFIEDENTRY_ENTRY(COMM_INST(instIdx));
  /* entry action 'ComM_Notify(COMM_FULL_COMMUNICATION);emit REQ_STATUS_CHANGED' */
  /* Notify RTE/DCM */
  ComM_Notify(instIdx, COMM_FULL_COMMUNICATION);
  (void)COMM_HSMEMITTOSELFINST(
    &ComM_HsmScComM, instIdx, COMM_HSM_COMM_EV_REQ_STATUS_CHANGED);
  DBG_COMM_HSMCOMMSFFULLCOMNOTIFIEDENTRY_EXIT(COMM_INST(instIdx));
}
FUNC(void, COMM_CODE) ComM_HsmComMSfFullComNotifiedAction1(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFFULLCOMNOTIFIEDACTION1_ENTRY(COMM_INST(instIdx));
  /* action 'if (ComMNmVariant==FULL) Nm_NetworkRelease();'
   * for NM_BUS_SLEEP_MODE[]/...
   * external transition to state WaitForNoCom */

  /* The parameter instIdx is not used in the following conditions:
   * - All channels with the same ComMNmVariant
   * - No channels with ComMNmVariant = "FULL"
   */
#if ((COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_OFF) || \
     (COMM_NM_VARIANT_FULL_NEEDED == STD_OFF))
  COMM_PARAM_UNUSED(instIdx);
#endif

#if (COMM_NM_VARIANT_FULL_NEEDED == STD_ON)
#if (COMM_NM_VARIANT_FULL_ONLY == STD_OFF)
  if (COMM_NM_FULL_VARIANT == COMM_NM_VARIANT_OF_CHANNEL(instIdx))
#endif
  {
    COMM_NM_NETWORKRELEASE(instIdx);
  }
#endif
  DBG_COMM_HSMCOMMSFFULLCOMNOTIFIEDACTION1_EXIT(COMM_INST(instIdx));
}
/* ************************************************************************
 * State: AcceptLimitToNoCom
 * Parent state: FullComNotified
 * Init substate: NetReqNm
 * Transitions originating from this state:
 * 1) LIMIT_TO_NO_COM[]/ComM_LimitToNoCom()
 * 2) AcceptLimitToNoCom -> WaitForFullCom: BUSSM_MODE_IND_NO_COM
 *    [IsChanReqAllowedFullCom()] /ComM_Notify(COMM_NO_COMMUNICATION);
 *    if (NmVariant == FULL) Nm_NetworkRelease();
 * 3) AcceptLimitToNoCom -> WaitForFullCom: BUSSM_MODE_IND_SILENT_COM
 *    [IsChanReqAllowedFullCom()]/ComM_Notify(COMM_SILENT_COMMUNICATION);
 *    if (NmVariant == FULL) Nm_NetworkRelease();
 */

FUNC(void, COMM_CODE) ComM_HsmComMSfAcceptLimitToNoComEntry(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMENTRY_ENTRY(COMM_INST(instIdx));
  /* entry action 'ChanState := FULL_COM_NETWORK_REQUESTED' */
  COMM_CHANNELSTATE(instIdx) = COMM_FULL_COM_NETWORK_REQUESTED;
  DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMENTRY_EXIT(COMM_INST(instIdx));
}

FUNC(void, COMM_CODE) ComM_HsmComMSfAcceptLimitToNoComAction1(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMACTION1_ENTRY(COMM_INST(instIdx));
  /* action 'ComM_LimitToNoCom()'
   * for LIMIT_TO_NO_COM[]/...
   * internal transition */

#if (COMM_MODE_LIMITATION_ENABLED == STD_OFF)
  COMM_PARAM_UNUSED(instIdx);
#else
  /* Check if DCM is not active and Limit to No com not already set */

  /* Deviation MISRA-2 <+6> */
#if (COMM_DCM_ENABLED == STD_ON)
  if ((FALSE == COMM_CHANNEL_NOCOM_INHIBITION_STATUS(instIdx))
       &&
      (FALSE == ComM_BitArrayIsBitSet(ComM_DcmActiveStatus, COMM_INST(instIdx)))
     )
#else
  /* For user requests: if inhibition is already enabled, we will not be in
     AcceptLimitToNoCom state. So, NO check for previous status of inhibition
     is required */
#endif
  {
    /* Set inhibition status of channel to "Limited to No Com" */
    ComM_SetChannelComMInhibitionStatus(COMM_CHANNEL(instIdx), COMM_LIMIT_NOCOMM, TRUE);
    (void)COMM_HSMEMITTOSELFINST(
      &ComM_HsmScComM, instIdx, COMM_HSM_COMM_EV_REQ_STATUS_CHANGED);
  }
#endif
  DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMACTION1_EXIT(COMM_INST(instIdx));
}
FUNC(boolean, COMM_CODE) ComM_HsmComMSfAcceptLimitToNoComGuard2(
  COMM_PDL_SF(const uint8 instIdx))
{
  boolean ret;
  DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMGUARD2_ENTRY(COMM_INST(instIdx));
  /* guard condition 'IsChanReqAllowedFullCom()'
   * for BUSSM_MODE_IND_NO_COM[...]/ComM_Notify(COMM_NO_COMMUNICATION);
   * if (NmVariant == FULL) Nm_NetworkRelease();
   * external transition to state WaitForFullCom */
  ret = (TRUE == ComM_IsChanReqAllowedFullCom(COMM_PL_SF(instIdx))) ? TRUE : FALSE;
  DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMGUARD2_EXIT(ret, COMM_INST(instIdx));
  return ret;
}
FUNC(void, COMM_CODE) ComM_HsmComMSfAcceptLimitToNoComAction2(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMACTION2_ENTRY(COMM_INST(instIdx));
  /* action 'ComM_Notify(COMM_NO_COMMUNICATION);
   * if (NmVariant == FULL) Nm_NetworkRelease();'
   * for BUSSM_MODE_IND_NO_COM[IsChanReqAllowedFullCom()]/...
   * external transition to state WaitForFullCom */
  ComM_Notify(instIdx, COMM_NO_COMMUNICATION);

   /* if NmVariant is FULL, release the network */
#if (COMM_NM_VARIANT_FULL_NEEDED == STD_ON)
#if (COMM_NM_VARIANT_FULL_ONLY == STD_OFF)
  if (COMM_NM_FULL_VARIANT == COMM_NM_VARIANT_OF_CHANNEL(instIdx))
#endif
  {
    COMM_NM_NETWORKRELEASE(instIdx);
  }
#endif
  DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMACTION2_EXIT(COMM_INST(instIdx));
}
FUNC(boolean, COMM_CODE) ComM_HsmComMSfAcceptLimitToNoComGuard3(
  COMM_PDL_SF(const uint8 instIdx))
{
  boolean ret;
  DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMGUARD3_ENTRY(COMM_INST(instIdx));
  /* guard condition 'IsChanReqAllowedFullCom()'
   * for BUSSM_MODE_IND_SILENT_COM[...]/ComM_Notify(COMM_SILENT_COMMUNICATION);
   * external transition to state WaitForFullCom */
  ret = (TRUE == ComM_IsChanReqAllowedFullCom(COMM_PL_SF(instIdx))) ? TRUE : FALSE;
  DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMGUARD3_EXIT(ret, COMM_INST(instIdx));
  return ret;
}
FUNC(void, COMM_CODE) ComM_HsmComMSfAcceptLimitToNoComAction3(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMACTION3_ENTRY(COMM_INST(instIdx));
  /* action 'ComM_Notify(COMM_SILENT_COMMUNICATION); if (NmVariant == FULL)
   * Nm_NetworkRelease();'
   * for BUSSM_MODE_IND_SILENT_COM[IsChanReqAllowedFullCom()]/...
   * external transition to state WaitForFullCom */
  ComM_Notify(instIdx, COMM_SILENT_COMMUNICATION);

  /* if NmVariant is FULL, release the network */
#if (COMM_NM_VARIANT_FULL_NEEDED == STD_ON)
#if (COMM_NM_VARIANT_FULL_ONLY == STD_OFF)
  if (COMM_NM_FULL_VARIANT == COMM_NM_VARIANT_OF_CHANNEL(instIdx))
#endif
  {
    COMM_NM_NETWORKRELEASE(instIdx);
  }
#endif
  DBG_COMM_HSMCOMMSFACCEPTLIMITTONOCOMACTION3_EXIT(COMM_INST(instIdx));
}

/* ************************************************************************
 * State: NetReqDelayedNoNm
 * Parent state: AcceptLimitToNoCom
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) NetReqDelayedNoNm -> NoComNotifed: REQ_STATUS_CHANGED[(NmVariant==NONE)
 *    && (BusType==Internal) && IsChanRelAllowed()]/
 * 2) NetReqDelayedNoNm -> WaitForNoCom: REQ_STATUS_CHANGED[(NmVariant==NONE)
 *    && (BusType!=Internal) && IsChanRelAllowed()]/
 * 3) NetReqDelayedNoNm -> ReadySleepNoNm: REQ_STATUS_CHANGED[(NmVariant!=NONE)
 *    && IsChanRelAllowed()]/
 */

FUNC(void, COMM_CODE) ComM_HsmComMSfNetReqDelayedNoNmEntry(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFNETREQDELAYEDNONMENTRY_ENTRY(COMM_INST(instIdx));
  /* entry action 'emit REQ_STATUS_CHANGED' */
  (void)COMM_HSMEMITTOSELFINST(
    &ComM_HsmScComM, instIdx, COMM_HSM_COMM_EV_REQ_STATUS_CHANGED);
  DBG_COMM_HSMCOMMSFNETREQDELAYEDNONMENTRY_EXIT(COMM_INST(instIdx));
}

FUNC(boolean, COMM_CODE) ComM_HsmComMSfNetReqDelayedNoNmGuard1(
  COMM_PDL_SF(const uint8 instIdx))
{
  boolean ret;
  DBG_COMM_HSMCOMMSFNETREQDELAYEDNONMGUARD1_ENTRY(COMM_INST(instIdx));
  /* guard condition '(NmVariant==NONE) && (BusType==Internal) &&
   * IsChanRelAllowed()' for REQ_STATUS_CHANGED[...]/
   * external transition to state NoComNotifed */

  /* The parameter instIdx is not used when only a single Nm variant
   * and Bus type are configured.
   */
#if ((COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_OFF) && \
     (COMM_BUSTYPE_OF_CHANNEL_DYNAMIC == STD_OFF))
  COMM_PARAM_UNUSED(instIdx);
#endif

  /* Deviation MISRA-2, MISRA-3 <+5> */
  ret = ( ( (COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_NONE_VARIANT) &&
              (COMM_BUSTYPE_OF_CHANNEL(instIdx) == COMM_BUS_TYPE_INTERNAL)
           ) &&
              (TRUE == ComM_IsChanRelAllowed(COMM_PL_SF(instIdx)))
         ) ? TRUE : FALSE;
  DBG_COMM_HSMCOMMSFNETREQDELAYEDNONMGUARD1_EXIT(ret, COMM_INST(instIdx));
  return ret;
}

FUNC(boolean, COMM_CODE) ComM_HsmComMSfNetReqDelayedNoNmGuard2(
  COMM_PDL_SF(const uint8 instIdx))
{
  boolean ret;
  DBG_COMM_HSMCOMMSFNETREQDELAYEDNONMGUARD2_ENTRY(COMM_INST(instIdx));
  /* guard condition '(NmVariant==NONE) && (BusType!=Internal) &&
   * IsChanRelAllowed()' for REQ_STATUS_CHANGED[...]/
   * external transition to state WaitForNoCom */

  /* The parameter instIdx is not used when only a single Nm variant
   * and Bus type are configured.
   */
#if ((COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_OFF) && \
     (COMM_BUSTYPE_OF_CHANNEL_DYNAMIC == STD_OFF))
  COMM_PARAM_UNUSED(instIdx);
#endif

  /* Deviation MISRA-2, MISRA-3 <+5> */
  ret = ( ( (COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_NONE_VARIANT) &&
             (COMM_BUSTYPE_OF_CHANNEL(instIdx) != COMM_BUS_TYPE_INTERNAL)
           ) &&
             (TRUE == ComM_IsChanRelAllowed(COMM_PL_SF(instIdx)))
         ) ? TRUE : FALSE;
  DBG_COMM_HSMCOMMSFNETREQDELAYEDNONMGUARD2_EXIT(ret, COMM_INST(instIdx));
  return ret;
}
FUNC(boolean, COMM_CODE) ComM_HsmComMSfNetReqDelayedNoNmGuard3(
  COMM_PDL_SF(const uint8 instIdx))
{
  boolean ret;
  DBG_COMM_HSMCOMMSFNETREQDELAYEDNONMGUARD3_ENTRY(COMM_INST(instIdx));
  /* guard condition '(NmVariant!=NONE) && IsChanRelAllowed()'
   * for REQ_STATUS_CHANGED[...]/
   * external transition to state ReadySleepNoNm */

  /* The parameter instIdx is not used when only a single Nm variant
   * is configured.
   */
#if (COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_OFF)
  COMM_PARAM_UNUSED(instIdx);
#endif

  /* Deviation MISRA-2, MISRA-3 <+3> */
  ret = ( (COMM_NM_VARIANT_OF_CHANNEL(instIdx) != COMM_NM_NONE_VARIANT) &&
           (TRUE == ComM_IsChanRelAllowed(COMM_PL_SF(instIdx)))
         ) ? TRUE : FALSE;
  DBG_COMM_HSMCOMMSFNETREQDELAYEDNONMGUARD3_EXIT(ret, COMM_INST(instIdx));
  return ret;
}

/* ************************************************************************
 * State: NetReqNm
 * Parent state: AcceptLimitToNoCom
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) PNC_NM_REQUEST[]/Nm_NetworkRequest(); ==> ComM980
 * 2) NetReqNm -> ReadySleepNm: REQ_STATUS_CHANGED[IsChanRelAllowed()]/if
 *   (NmVariant == FULL) Nm_NetworkRelease();
 */

FUNC(void, COMM_CODE) ComM_HsmComMSfNetReqNmAction1(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFNETREQNMACTION1_ENTRY(COMM_INST(instIdx));
  /* action 'Nm_NetworkRequest(); ==> ComM980'
   * for PNC_NM_REQUEST[]/...
   * internal transition */

  /* The parameter instIdx is not used in the following conditions:
   * - All channels with the same ComMNmVariant
   * - No channels with ComMNmVariant = "FULL"
   */

#if ((COMM_NM_VARIANT_FULL_NEEDED == STD_OFF) || \
     (COMM_HSM_INST_MULTI_ENABLED == STD_ON))
  COMM_PARAM_UNUSED(instIdx);
#endif

#if (COMM_NM_VARIANT_FULL_NEEDED == STD_ON)
  COMM_NM_NETWORKREQUEST(instIdx);
#endif
  DBG_COMM_HSMCOMMSFNETREQNMACTION1_EXIT(COMM_INST(instIdx));
}
FUNC(boolean, COMM_CODE) ComM_HsmComMSfNetReqNmGuard2(
  COMM_PDL_SF(const uint8 instIdx))
{
  boolean ret;
  DBG_COMM_HSMCOMMSFNETREQNMGUARD2_ENTRY(COMM_INST(instIdx));
  /* guard condition 'IsChanRelAllowed()'
   * for REQ_STATUS_CHANGED[...]/if (NmVariant == FULL) Nm_NetworkRelease();
   * external transition to state ReadySleepNm */

  ret = ComM_IsChanRelAllowed(COMM_PL_SF(instIdx));
  DBG_COMM_HSMCOMMSFNETREQNMGUARD2_EXIT(ret, COMM_INST(instIdx));
  return ret;
}
FUNC(void, COMM_CODE) ComM_HsmComMSfNetReqNmAction2(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFNETREQNMACTION2_ENTRY(COMM_INST(instIdx));
  /* action 'if (NmVariant == FULL) Nm_NetworkRelease();'
   * for REQ_STATUS_CHANGED[IsChanRelAllowed()]/...
   * external transition to state ReadySleepNm */

  /* The parameter instIdx is not used in the following conditions:
   * - All channels with the same ComMNmVariant
   * - No channels with ComMNmVariant = "FULL"
   */
#if ((COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_OFF) || \
     (COMM_NM_VARIANT_FULL_NEEDED == STD_OFF))
  COMM_PARAM_UNUSED(instIdx);
#endif

  /* if NmVariant is FULL, release the network */
#if (COMM_NM_VARIANT_FULL_NEEDED == STD_ON)
#if (COMM_NM_VARIANT_FULL_ONLY == STD_OFF)
  if (COMM_NM_FULL_VARIANT == COMM_NM_VARIANT_OF_CHANNEL(instIdx))
#endif
  {
    COMM_NM_NETWORKRELEASE(instIdx);
  }
#endif
  DBG_COMM_HSMCOMMSFNETREQNMACTION2_EXIT(COMM_INST(instIdx));
}

/* ************************************************************************
 * State: NetReqNoNm
 * Parent state: AcceptLimitToNoCom
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) NetReqNoNm -> NetReqDelayedNoNm: TIMEOUT[]/
 */

FUNC(void, COMM_CODE) ComM_HsmComMSfNetReqNoNmEntry(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFNETREQNONMENTRY_ENTRY(COMM_INST(instIdx));
  /* entry action 'StartTimer(TIMEOUT, MIN_FULL_COM_MODE_DURATION);' */
#if ((COMM_NM_VARIANT_LIGHT_NEEDED == STD_OFF) && \
     (COMM_NM_VARIANT_NONE_NEEDED == STD_OFF))
  COMM_PARAM_UNUSED(instIdx);
#else
  ComM_StartTimer(
    instIdx, COMM_HSM_COMM_EV_TIMEOUT, COMM_MIN_FULL_COM_MODE_DURATION(instIdx));
#endif
  DBG_COMM_HSMCOMMSFNETREQNONMENTRY_EXIT(COMM_INST(instIdx));
}

/* ************************************************************************
 * State: ReadySleepNm
 * Parent state: FullComNotified
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) ReadySleepNm -> NetReqNm:
 *    REQ_STATUS_CHANGED[IsChanReqAllowedFullCom()]/if (NmVariant == FULL)
 *    Nm_NetworkRequest();
 */

FUNC(void, COMM_CODE) ComM_HsmComMSfReadySleepNmEntry(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFREADYSLEEPNMENTRY_ENTRY(COMM_INST(instIdx));
  /* entry action 'ChanState := FULL_COM_READY_SLEEP' */
  COMM_CHANNELSTATE(instIdx) = COMM_FULL_COM_READY_SLEEP;
  DBG_COMM_HSMCOMMSFREADYSLEEPNMENTRY_EXIT(COMM_INST(instIdx));
}
FUNC(boolean, COMM_CODE) ComM_HsmComMSfReadySleepNmGuard1(
  COMM_PDL_SF(const uint8 instIdx))
{
  boolean ret;
  DBG_COMM_HSMCOMMSFREADYSLEEPNMGUARD1_ENTRY(COMM_INST(instIdx));
  /* guard condition 'IsChanReqAllowedFullCom()'
   * for REQ_STATUS_CHANGED[...]/if (NmVariant == FULL) Nm_NetworkRequest();
   * external transition to state NetReqNm */

  ret = ComM_IsChanReqAllowedFullCom(COMM_PL_SF(instIdx));
  DBG_COMM_HSMCOMMSFREADYSLEEPNMGUARD1_EXIT(ret, COMM_INST(instIdx));
  return ret;
}
FUNC(void, COMM_CODE) ComM_HsmComMSfReadySleepNmAction1(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFREADYSLEEPNMACTION1_ENTRY(COMM_INST(instIdx));
  /* action 'if (NmVariant == FULL) Nm_NetworkRequest();'
   * for REQ_STATUS_CHANGED[IsChanReqAllowedFullCom()]/...
   * external transition to state NetReqNm */

  /* The parameter instIdx is not used in the following conditions:
   * - All channels with the same ComMNmVariant
   * - No channels with ComMNmVariant = "FULL"
   */
#if ((COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_OFF) || \
     (COMM_NM_VARIANT_FULL_NEEDED == STD_OFF))
  COMM_PARAM_UNUSED(instIdx);
#endif

  /* if NmVariant is FULL, request the network */
  /* !LINKSTO ComM667,1 */
#if (COMM_NM_VARIANT_FULL_NEEDED == STD_ON)
  COMM_NM_NETWORKREQUEST(instIdx);
#endif
  DBG_COMM_HSMCOMMSFREADYSLEEPNMACTION1_EXIT(COMM_INST(instIdx));
}

/* ************************************************************************
 * State: ReadySleepNoNm
 * Parent state: FullComNotified
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) ReadySleepNoNm -> NetReqNoNm:
 *    REQ_STATUS_CHANGED[IsChanReqAllowedFullCom()]/
 * 2) ReadySleepNoNm -> WaitForNoCom: TIMEOUT[]/
 */

FUNC(void, COMM_CODE) ComM_HsmComMSfReadySleepNoNmEntry(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFREADYSLEEPNONMENTRY_ENTRY(COMM_INST(instIdx));
  /* entry action 'StartTimer(TIMEOUT, ComNmLightTimeout);
   * ChanState := FULL_COM_READY_SLEEP' */
#if (COMM_NM_VARIANT_LIGHT_NEEDED == STD_OFF)
  COMM_PARAM_UNUSED(instIdx);
#else
  ComM_StartTimer(
    instIdx, COMM_HSM_COMM_EV_TIMEOUT, COMM_READYSLEEPNONMTIMEOUTMS(instIdx));

  /* Set the current State of the Channel */
  COMM_CHANNELSTATE(instIdx) = COMM_FULL_COM_READY_SLEEP;
#endif
  DBG_COMM_HSMCOMMSFREADYSLEEPNONMENTRY_EXIT(COMM_INST(instIdx));
}
FUNC(boolean, COMM_CODE) ComM_HsmComMSfReadySleepNoNmGuard1(
  COMM_PDL_SF(const uint8 instIdx))
{
  boolean ret;
  DBG_COMM_HSMCOMMSFREADYSLEEPNONMGUARD1_ENTRY(COMM_INST(instIdx));
  /* guard condition 'IsChanReqAllowedFullCom()'
   * for REQ_STATUS_CHANGED[...]/
   * external transition to state NetReqNoNm */
  ret = ComM_IsChanReqAllowedFullCom(COMM_PL_SF(instIdx));
  DBG_COMM_HSMCOMMSFREADYSLEEPNONMGUARD1_EXIT(ret, COMM_INST(instIdx));
  return ret;
}

/* ************************************************************************
 * State: PassiveStartupWait
 * Parent state: FullCom
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) PassiveStartupWait -> NetReqNm: NM_NETWORK_MODE[NmVariant==PASSIVE]/
 * 2) PassiveStartupWait -> NetReqNm: NM_NETWORK_MODE[NmVariant==FULL &&
 *    IsChanReqAllowedFullCom()]/Nm_NetworkRequest()
 * 3) PassiveStartupWait -> ReadySleepNm: NM_NETWORK_MODE[]/Nm_NetworkRelease()
 * 4) PassiveStartupWait -> PassiveStartupWait: NM_TIMEOUT[]/
 */

FUNC(void, COMM_CODE) ComM_HsmComMSfPassiveStartupWaitEntry(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITENTRY_ENTRY(COMM_INST(instIdx));
  /* entry action 'StartTimer(NM_RETRY_TIME); ComM_CheckNwr();' */

  ComM_StartTimer(instIdx, COMM_HSM_COMM_EV_NM_TIMEOUT, COMM_NM_RETRY_TIME);
  ComM_CheckNwr(COMM_PL_SF(instIdx));
  DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITENTRY_EXIT(COMM_INST(instIdx));
}
FUNC(void, COMM_CODE) ComM_HsmComMSfPassiveStartupWaitExit(
   COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITEXIT_ENTRY(COMM_INST(instIdx));
  /* exit action 'StopTimer();'*/
  ComM_StopTimer(instIdx);
  DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITEXIT_EXIT(COMM_INST(instIdx));
}
FUNC(boolean, COMM_CODE) ComM_HsmComMSfPassiveStartupWaitGuard1(
  COMM_PDL_SF(const uint8 instIdx))
{
  boolean ret;
  DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITGUARD1_ENTRY(COMM_INST(instIdx));
  /* guard condition 'NmVariant==PASSIVE'
   * for NM_NETWORK_MODE[...]/
   * external transition to state NetReqNm */

  /* The parameter instIdx is not used when only a single Nm variant
   * is configured.
   */
#if (COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_OFF)
  COMM_PARAM_UNUSED(instIdx);
#endif

  /* Deviation MISRA-3 */
  ret = (COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_PASSIVE_VARIANT) ? TRUE : FALSE;
  DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITGUARD1_EXIT(ret, COMM_INST(instIdx));
  return ret;
}
FUNC(boolean, COMM_CODE) ComM_HsmComMSfPassiveStartupWaitGuard2(
  COMM_PDL_SF(const uint8 instIdx))
{
  boolean ret;
  DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITGUARD2_ENTRY(COMM_INST(instIdx));
  /* guard condition 'NmVariant==FULL && IsChanReqAllowedFullCom()'
   * for NM_NETWORK_MODE[...]/Nm_NetworkRequest()
   * external transition to state NetReqNm */

  /* The parameter instIdx is not used in the following conditions:
   * - All channels with the same ComMNmVariant
   */
#if (COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_OFF)
  COMM_PARAM_UNUSED(instIdx);
#endif

  /* Deviation MISRA-2 */
  /* Deviation MISRA-3 */
  ret = ( (COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_FULL_VARIANT) &&
           (ComM_IsChanReqAllowedFullCom(COMM_PL_SF(instIdx)))
         ) ? TRUE : FALSE;
  DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITGUARD2_EXIT(ret, COMM_INST(instIdx));
  return ret;
}
FUNC(void, COMM_CODE) ComM_HsmComMSfPassiveStartupWaitAction2(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITACTION2_ENTRY(COMM_INST(instIdx));
  /* action 'Nm_NetworkRequest()'
   * for NM_NETWORK_MODE[NmVariant==FULL && IsChanReqAllowedFullCom()]/...
   * external transition to state NetReqNm */

  /* The parameter instIdx is not used in the following conditions:
   * - No channels with ComMNmVariant = "FULL"
   * - Only a single channel/PNC is configured
   */
#if ((COMM_NM_VARIANT_FULL_NEEDED == STD_OFF) || \
     (COMM_HSM_INST_MULTI_ENABLED == STD_ON))
  COMM_PARAM_UNUSED(instIdx);
#endif

#if (COMM_NM_VARIANT_FULL_NEEDED == STD_ON)
  COMM_NM_NETWORKREQUEST(instIdx);
#endif
  DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITACTION2_EXIT(COMM_INST(instIdx));
}
FUNC(void, COMM_CODE) ComM_HsmComMSfPassiveStartupWaitAction3(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITACTION3_ENTRY(COMM_INST(instIdx));
  /* action 'Nm_NetworkRelease()'
   * for NM_NETWORK_MODE[]/...
   * external transition to state ReadySleepNm */

  /* The parameter instIdx is not used in the following conditions:
   * - No channels with ComMNmVariant = "FULL"
   * - Only a single channel/PNC is configured
   */
#if ((COMM_NM_VARIANT_FULL_NEEDED == STD_OFF) || \
     (COMM_HSM_INST_MULTI_ENABLED == STD_ON))
  COMM_PARAM_UNUSED(instIdx);
#endif

#if (COMM_NM_VARIANT_FULL_NEEDED == STD_ON)
  COMM_NM_NETWORKRELEASE(instIdx);
#endif
  DBG_COMM_HSMCOMMSFPASSIVESTARTUPWAITACTION3_EXIT(COMM_INST(instIdx));
}

/* ************************************************************************
 * State: ReqNetworkWait
 * Parent state: FullCom
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) ReqNetworkWait -> NetReqNm: NM_NETWORK_MODE[]/
 * 2) ReqNetworkWait -> ReqNetworkWait: NM_TIMEOUT[]/
 */

FUNC(void, COMM_CODE) ComM_HsmComMSfReqNetworkWaitEntry(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFREQNETWORKWAITENTRY_ENTRY(COMM_INST(instIdx));
  /* entry action 'StartTimer(NM_RETRY_TIME); ComM_CheckNwr();' */
  ComM_StartTimer(instIdx, COMM_HSM_COMM_EV_NM_TIMEOUT, COMM_NM_RETRY_TIME);
  ComM_CheckNwr(COMM_PL_SF(instIdx));
  DBG_COMM_HSMCOMMSFREQNETWORKWAITENTRY_EXIT(COMM_INST(instIdx));
}
FUNC(void, COMM_CODE) ComM_HsmComMSfReqNetworkWaitExit(
   COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFREQNETWORKWAITEXIT_ENTRY(COMM_INST(instIdx));
  /* exit action 'StopTimer();' */
  ComM_StopTimer(instIdx);
  DBG_COMM_HSMCOMMSFREQNETWORKWAITEXIT_EXIT(COMM_INST(instIdx));
}

/* ************************************************************************
 * State: WaitForFullCom
 * Parent state: FullCom
 * Init substate: WffcToNetReq
 * Transitions originating from this state:
 * 1) BUSSM_TIMEOUT[]/ComM_RetryBusSmRequest()
 * 2) WaitForFullCom -> WaitForNoCom: BUSSM_RETRY_COUNT_LIMIT[]/
 * 3) WaitForFullCom -> WaitForNoCom: REQ_STATUS_CHANGED[IsChanRelAllowed()]/
 */

FUNC(void, COMM_CODE) ComM_HsmComMSfWaitForFullComEntry(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFWAITFORFULLCOMENTRY_ENTRY(COMM_INST(instIdx));
  /* entry action 'ComM_BusSmRequestComMode(COMM_FULL_COMMUNICATION); BusSMRetryCount := MaxRetryValue' */

  /* Initialize BusSM Request retry counter */
  ComM_BusSMRetryCounter[COMM_INST(instIdx)] = ComM_BusSMMaxRetryCount[COMM_INST(instIdx)];

  /* Request full communication mode from corresponding Bus state manager */
  ComM_BusSmRequestComMode(instIdx, COMM_FULL_COMMUNICATION);

  DBG_COMM_HSMCOMMSFWAITFORFULLCOMENTRY_EXIT(COMM_INST(instIdx));
}
FUNC(void, COMM_CODE) ComM_HsmComMSfWaitForFullComExit(
   COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFWAITFORFULLCOMEXIT_ENTRY(COMM_INST(instIdx));
  /* exit action 'StopTimer();' */
  ComM_StopTimer(instIdx);
  DBG_COMM_HSMCOMMSFWAITFORFULLCOMEXIT_EXIT(COMM_INST(instIdx));
}
FUNC(void, COMM_CODE) ComM_HsmComMSfWaitForFullComAction1(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFWAITFORFULLCOMACTION1_ENTRY(COMM_INST(instIdx));
  /* action 'ComM_RetryBusSmRequest()'
   * for BUSSM_TIMEOUT[]/...
   * internal transition */
  ComM_RetryBusSmRequest(COMM_INST(instIdx));

  DBG_COMM_HSMCOMMSFWAITFORFULLCOMACTION1_EXIT(COMM_INST(instIdx));
}

FUNC(boolean, COMM_CODE) ComM_HsmComMSfWaitForFullComGuard3(
  COMM_PDL_SF(const uint8 instIdx))
{
  boolean ret;
  DBG_COMM_HSMCOMMSFWAITFORFULLCOMGUARD3_ENTRY(COMM_INST(instIdx));
  /* guard condition 'IsChanRelAllowed()'
   * for REQ_STATUS_CHANGED[...]/
   * external transition to state WaitForNoCom */

  /* Deviation MISRA-2 */
  ret = (TRUE == ComM_IsChanRelAllowed(COMM_PL_SF(instIdx))) ? TRUE : FALSE;
  DBG_COMM_HSMCOMMSFWAITFORFULLCOMGUARD3_EXIT(ret, COMM_INST(instIdx));
  return ret;
}

/* ************************************************************************
 * State: WffcToNetReq
 * Parent state: WaitForFullCom
 * Init substate: WffcToNetReqActive
 * Transitions originating from this state:
 * 1) WffcToNetReq -> NetReqNoNm: BUSSM_MODE_IND_FULL_COM[]/
 */


/* ************************************************************************
 * State: WffcToNetReqActive
 * Parent state: WffcToNetReq
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) WffcToNetReqActive -> ReqNetworkWait:
 *    BUSSM_MODE_IND_FULL_COM[NmVariant==FULL]/Nm_NetworkRequest();
 */

FUNC(boolean, COMM_CODE) ComM_HsmComMSfWffcToNetReqActiveGuard1(
  COMM_PDL_SF(const uint8 instIdx))
{
  boolean ret;
  DBG_COMM_HSMCOMMSFWFFCTONETREQACTIVEGUARD1_ENTRY(COMM_INST(instIdx));
  /* guard condition 'NmVariant==FULL'
   * for BUSSM_MODE_IND_FULL_COM[...]/Nm_NetworkRequest();
   * external transition to state ReqNetworkWait */

  /* The parameter instIdx is not used when only a single Nm variant
   * is configured.
   */
#if (COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_OFF)
  COMM_PARAM_UNUSED(instIdx);
#endif

  /* Deviation MISRA-3 */
  ret = (COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_FULL_VARIANT) ? TRUE : FALSE;
  DBG_COMM_HSMCOMMSFWFFCTONETREQACTIVEGUARD1_EXIT(ret, COMM_INST(instIdx));
  return ret;
}

FUNC(void, COMM_CODE) ComM_HsmComMSfWffcToNetReqActiveAction1(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFWFFCTONETREQACTIVEACTION1_ENTRY(COMM_INST(instIdx));
  /* action 'Nm_NetworkRequest();'
   * for BUSSM_MODE_IND_FULL_COM[NmVariant==FULL]/...
   * external transition to state ReqNetworkWait */

  /* The parameter instIdx is not used in the following conditions:
   * - No channels with ComMNmVariant = "FULL"
   * - Only a single channel/PNC is configured
   */
#if ((COMM_NM_VARIANT_FULL_NEEDED == STD_OFF) || \
     (COMM_HSM_INST_MULTI_ENABLED == STD_ON))
  COMM_PARAM_UNUSED(instIdx);
#endif

#if (COMM_NM_VARIANT_FULL_NEEDED == STD_ON)
  COMM_NM_NETWORKREQUEST(COMM_PDL_SF(instIdx));
#endif
  DBG_COMM_HSMCOMMSFWFFCTONETREQACTIVEACTION1_EXIT(COMM_INST(instIdx));
}

/* ************************************************************************
 * State: WffcToNetReqPassive
 * Parent state: WffcToNetReq
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) WffcToNetReqPassive -> PassiveStartupWait:
 *    BUSSM_MODE_IND_FULL_COM[NmVariant==(FULL|PASSIVE)]/Nm_PassiveStartUp();
 */

FUNC(boolean, COMM_CODE) ComM_HsmComMSfWffcToNetReqPassiveGuard1(
  COMM_PDL_SF(const uint8 instIdx))
{
  boolean ret;
  DBG_COMM_HSMCOMMSFWFFCTONETREQPASSIVEGUARD1_ENTRY(COMM_INST(instIdx));
  /* guard condition 'NmVariant==(FULL|PASSIVE)'
   * for BUSSM_MODE_IND_FULL_COM[...]/Nm_PassiveStartUp();
   * external transition to state PassiveStartupWait */

  /* The parameter instIdx is not used when only a single Nm variant
   * is configured.
   */
#if (COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_OFF)
  COMM_PARAM_UNUSED(instIdx);
#endif

   /* Deviation MISRA-3 <+3> */
  ret = ( (COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_FULL_VARIANT) ||
           (COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_PASSIVE_VARIANT)
         ) ? TRUE : FALSE;
  DBG_COMM_HSMCOMMSFWFFCTONETREQPASSIVEGUARD1_EXIT(ret, COMM_INST(instIdx));
  return ret;
}
FUNC(void, COMM_CODE) ComM_HsmComMSfWffcToNetReqPassiveAction1(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFWFFCTONETREQPASSIVEACTION1_ENTRY(COMM_INST(instIdx));

#if ((COMM_NM_ACCESS_NEEDED == STD_OFF) || \
     (COMM_HSM_INST_MULTI_ENABLED == STD_ON))
  COMM_PARAM_UNUSED(instIdx);
#endif
  /* action 'Nm_PassiveStartup();'
   * for BUSSM_MODE_IND_FULL_COM[NmVariant==(FULL|PASSIVE)]/...
   * external transition to state PassiveStartupWait */

#if (COMM_NM_ACCESS_NEEDED == STD_ON)
  COMM_NM_PASSIVESTARTUP(instIdx);
#endif
  DBG_COMM_HSMCOMMSFWFFCTONETREQPASSIVEACTION1_EXIT(COMM_INST(instIdx));
}

/* ************************************************************************
 * State: WffcToReadySleep
 * Parent state: WaitForFullCom
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) WffcToReadySleep -> ReadySleepNm: BUSSM_MODE_IND_FULL_COM[]/
 */


/* ************************************************************************
 * State: NoCom
 * Parent state: TOP
 * Init substate: NoPendingRequest
 * Transitions originating from this state:
 */


/* ************************************************************************
 * State: NoPendingRequest
 * Parent state: NoCom
 * Init substate: NoComFirst
 * Transitions originating from this state:
 * 1) NoPendingRequest -> ReqRunPassive: ECUM_WAKEUP_IND[]/
 * 2) NoPendingRequest -> ReqRunPassive: NM_NETWORK_START_INDICATION[]/
 * 3) NoPendingRequest -> ReqRunPassive: NM_RESTART_IND[]/
 * 4) NoPendingRequest -> ReqRunActive:
 *    REQ_STATUS_CHANGED[IsChanReqAllowedNoFullCom()]/
 */

FUNC(boolean, COMM_CODE) ComM_HsmComMSfNoPendingRequestGuard4(
  COMM_PDL_SF(const uint8 instIdx))
{
  boolean ret;
  DBG_COMM_HSMCOMMSFNOPENDINGREQUESTGUARD4_ENTRY(COMM_INST(instIdx));
  /* guard condition 'IsChanReqAllowedNoFullCom()'
   * for REQ_STATUS_CHANGED[...]/
   * external transition to state ReqRunActive */

  ret = ComM_IsChanReqAllowedNoFullCom(COMM_PL_SF(instIdx));
  DBG_COMM_HSMCOMMSFNOPENDINGREQUESTGUARD4_EXIT(ret, COMM_INST(instIdx));
  return ret;
}

/* ************************************************************************
 * State: NoComFirst
 * Parent state: NoPendingRequest
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 */

FUNC(void, COMM_CODE) ComM_HsmComMSfNoComFirstEntry(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFNOCOMFIRSTENTRY_ENTRY(COMM_INST(instIdx));
  /* entry action 'ChanState := NO_COM_NO_PENDING_REQUEST' */
  COMM_CHANNELSTATE(instIdx) = COMM_NO_COM_NO_PENDING_REQUEST;
  DBG_COMM_HSMCOMMSFNOCOMFIRSTENTRY_EXIT(COMM_INST(instIdx));
}

/* ************************************************************************
 * State: NoComNotifed
 * Parent state: NoPendingRequest
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 */

FUNC(void, COMM_CODE) ComM_HsmComMSfNoComNotifedEntry(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFNOCOMNOTIFEDENTRY_ENTRY(COMM_INST(instIdx));
  /* entry action 'ComM_Notify(COMM_NO_COMMUNICATION);
   * ChanState := NO_COM_NO_PENDING_REQUEST';
   * if (ModeLimitation == TRUE) ComM_ClearUserRequest();' */
  COMM_CHANNELSTATE(instIdx) = COMM_NO_COM_NO_PENDING_REQUEST;
  ComM_Notify(instIdx, COMM_NO_COMMUNICATION);

#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
  /* User request needs to be cleared if all channels corresponding to this user
   * (also shared channels) are in NoCom Mode and mode limitation is active
   */
  if (TRUE == COMM_CHANNEL_NOCOM_INHIBITION_STATUS(instIdx))
  {
    ComM_ClearUserRequest(COMM_PL_SF(instIdx));
  }
#endif
  DBG_COMM_HSMCOMMSFNOCOMNOTIFEDENTRY_EXIT(COMM_INST(instIdx));
}

/* ************************************************************************
 * State: WaitForNoCom
 * Parent state: NoPendingRequest
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) WaitForNoCom -> NoComNotifed: BUSSM_MODE_IND_NO_COM[]/
 * 2) WaitForNoCom -> WaitForNoCom: BUSSM_TIMEOUT[]/
 */

FUNC(void, COMM_CODE) ComM_HsmComMSfWaitForNoComEntry(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFWAITFORNOCOMENTRY_ENTRY(COMM_INST(instIdx));
  /* entry action 'ComM_BusSmRequestComMode(COMM_NO_COMMUNICATION);' */

  /* Request no communication mode from corresponding Bus state manager */
  ComM_BusSmRequestComMode(instIdx, COMM_NO_COMMUNICATION);
  DBG_COMM_HSMCOMMSFWAITFORNOCOMENTRY_EXIT(COMM_INST(instIdx));
}
FUNC(void, COMM_CODE) ComM_HsmComMSfWaitForNoComExit(
   COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFWAITFORNOCOMEXIT_ENTRY(COMM_INST(instIdx));
  /* exit action 'StopTimer();' */
  ComM_StopTimer(instIdx);
  DBG_COMM_HSMCOMMSFWAITFORNOCOMEXIT_EXIT(COMM_INST(instIdx));
}

/* ************************************************************************
 * State: PendingRequest
 * Parent state: NoCom
 * Init substate: ReqRunPassive
 * Transitions originating from this state:
 * 1) PendingRequest -> NetReqNoNm:
 *    COMALLOWED_CHANGED[CommunicationAllowed==TRUE && BusType==Internal]/
 */

FUNC(void, COMM_CODE) ComM_HsmComMSfPendingRequestEntry(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFPENDINGREQUESTENTRY_ENTRY(COMM_INST(instIdx));
  /* entry action 'emit COMALLOWED_CHANGED;
   * ChanState := NO_COM_REQUEST_PENDING' */
  COMM_CHANNELSTATE(instIdx) = COMM_NO_COM_REQUEST_PENDING;
  (void)COMM_HSMEMITINST(
    &ComM_HsmScComM, instIdx, COMM_HSM_COMM_EV_COMALLOWED_CHANGED);
  DBG_COMM_HSMCOMMSFPENDINGREQUESTENTRY_EXIT(COMM_INST(instIdx));
}
FUNC(boolean, COMM_CODE) ComM_HsmComMSfPendingRequestGuard1(
  COMM_PDL_SF(const uint8 instIdx))
{
  boolean ret;
  DBG_COMM_HSMCOMMSFPENDINGREQUESTGUARD1_ENTRY(COMM_INST(instIdx));
  /* guard condition 'CommunicationAllowed==TRUE && BusType==Internal'
   * for COMALLOWED_CHANGED[...]/
   * external transition to state NetReqNoNm */

   /* Deviation MISRA-3 <+3> */
   ret = ( (ComM_BitArrayIsBitSet(ComM_Communication_Allowed, COMM_INST(instIdx))) &&
            (COMM_BUSTYPE_OF_CHANNEL(instIdx) == COMM_BUS_TYPE_INTERNAL)
          ) ? TRUE : FALSE;
  DBG_COMM_HSMCOMMSFPENDINGREQUESTGUARD1_EXIT(ret, COMM_INST(instIdx));
  return ret;
}

/* ************************************************************************
 * State: ReqRunActive
 * Parent state: PendingRequest
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) ReqRunActive -> WffcToNetReqActive:
 *    COMALLOWED_CHANGED[CommunicationAllowed==TRUE && BusType != Internal]/
 * 2) ReqRunActive -> NoPendingRequest: REQ_STATUS_CHANGED[!IsChanReqAllowedNoFullCom()]/
 */

FUNC(boolean, COMM_CODE) ComM_HsmComMSfReqRunActiveGuard1(
  COMM_PDL_SF(const uint8 instIdx))
{
  boolean ret;
  DBG_COMM_HSMCOMMSFREQRUNACTIVEGUARD1_ENTRY(COMM_INST(instIdx));
  /* guard condition 'CommunicationAllowed==TRUE && BusType != Internal'
   * for COMALLOWED_CHANGED[...]/
   * external transition to state WffcToNetReqActive */

  /* Deviation MISRA-3 <+3> */
  ret = ( (ComM_BitArrayIsBitSet(ComM_Communication_Allowed, COMM_INST(instIdx))) &&
           (COMM_BUSTYPE_OF_CHANNEL(instIdx) != COMM_BUS_TYPE_INTERNAL)
         ) ? TRUE : FALSE;
  DBG_COMM_HSMCOMMSFREQRUNACTIVEGUARD1_EXIT(ret, COMM_INST(instIdx));
  return ret;
}
FUNC(boolean, COMM_CODE) ComM_HsmComMSfReqRunActiveGuard2(
  COMM_PDL_SF(const uint8 instIdx))
{
  boolean ret;
  DBG_COMM_HSMCOMMSFREQRUNACTIVEGUARD2_ENTRY(COMM_INST(instIdx));
  /* guard condition '!IsChanReqAllowedNoFullCom()'
   * for REQ_STATUS_CHANGED[...]/
   * external transition to state NoPendingRequest */
  ret = (!ComM_IsChanReqAllowedNoFullCom(COMM_PL_SF(instIdx))) ? TRUE : FALSE;
  DBG_COMM_HSMCOMMSFREQRUNACTIVEGUARD2_EXIT(ret, COMM_INST(instIdx));
  return ret;
}

/* ************************************************************************
 * State: ReqRunPassive
 * Parent state: PendingRequest
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) ReqRunPassive -> WffcToNetReqPassive:
 *    COMALLOWED_CHANGED[CommunicationAllowed==TRUE && BusType != Internal]/
 */

FUNC(boolean, COMM_CODE) ComM_HsmComMSfReqRunPassiveGuard1(
  COMM_PDL_SF(const uint8 instIdx))
{
  boolean ret;
  DBG_COMM_HSMCOMMSFREQRUNPASSIVEGUARD1_ENTRY(COMM_INST(instIdx));
  /* guard condition 'CommunicationAllowed==TRUE && BusType != Internal'
   * for COMALLOWED_CHANGED[...]/
   * external transition to state WffcToNetReqPassive */

  /* Deviation MISRA-3 <+3> */
  ret = ( (ComM_BitArrayIsBitSet(ComM_Communication_Allowed, COMM_INST(instIdx))) &&
           (COMM_BUSTYPE_OF_CHANNEL(instIdx) != COMM_BUS_TYPE_INTERNAL)
         ) ? TRUE : FALSE;
  DBG_COMM_HSMCOMMSFREQRUNPASSIVEGUARD1_EXIT(ret, COMM_INST(instIdx));
  return ret;
}

/* ************************************************************************
 * State: SilentCom
 * Parent state: TOP
 * Init substate: WaitForSilentCom
 * Transitions originating from this state:
 * 1) SilentCom -> WaitForNoCom: NM_BUS_SLEEP_MODE[]/if (ComMNmVariant==FULL) Nm_NetworkRelease();
 * 2) SilentCom -> WffcToReadySleep: NM_NETWORK_MODE[]/
 * 3) SilentCom -> WffcToNetReqActive:
 *    REQ_STATUS_CHANGED[IsChanReqAllowedNoFullCom()]/
 */

FUNC(void, COMM_CODE) ComM_HsmComMSfSilentComAction1(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFSILENTCOMACTION1_ENTRY(COMM_INST(instIdx));
  /* action 'if (ComMNmVariant==FULL) Nm_NetworkRelease();'
   * for NM_BUS_SLEEP_MODE[]/...
   * external transition to state WaitForNoCom */

  /* The parameter instIdx is not used in the following conditions:
   * - All channels with the same ComMNmVariant
   * - No channels with ComMNmVariant = "FULL"
   */
#if ((COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_OFF) || \
     (COMM_NM_VARIANT_FULL_NEEDED == STD_OFF))
  COMM_PARAM_UNUSED(instIdx);
#endif

#if (COMM_NM_VARIANT_FULL_NEEDED == STD_ON)
#if (COMM_NM_VARIANT_FULL_ONLY == STD_OFF)
  if (COMM_NM_FULL_VARIANT == COMM_NM_VARIANT_OF_CHANNEL(instIdx))
#endif
  {
    COMM_NM_NETWORKRELEASE(instIdx);
  }
#endif
  DBG_COMM_HSMCOMMSFSILENTCOMACTION1_EXIT(COMM_INST(instIdx));
}
FUNC(boolean, COMM_CODE) ComM_HsmComMSfSilentComGuard3(
  COMM_PDL_SF(const uint8 instIdx))
{
  boolean ret;
  DBG_COMM_HSMCOMMSFSILENTCOMGUARD3_ENTRY(COMM_INST(instIdx));
  /* guard condition 'IsChanReqAllowedNoFullCom()'
   * for REQ_STATUS_CHANGED[...]/
   * external transition to state WffcToNetReqActive */

  ret = ComM_IsChanReqAllowedNoFullCom(COMM_PL_SF(instIdx));
  DBG_COMM_HSMCOMMSFSILENTCOMGUARD3_EXIT(ret, COMM_INST(instIdx));
  return ret;
}

/* ************************************************************************
 * State: SilentComNotifed
 * Parent state: SilentCom
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 */

FUNC(void, COMM_CODE) ComM_HsmComMSfSilentComNotifedEntry(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFSILENTCOMNOTIFEDENTRY_ENTRY(COMM_INST(instIdx));
  /* entry action 'ComM_Notify(COMM_SILENT_COMMUNICATION);ChanState := SILENT_COM'
   */
  /* Set the current State of the Channel */
  COMM_CHANNELSTATE(instIdx) = COMM_SILENT_COM;
  /* Notify RTE /DCM /BSWM */
  ComM_Notify(instIdx, COMM_SILENT_COMMUNICATION);
  DBG_COMM_HSMCOMMSFSILENTCOMNOTIFEDENTRY_EXIT(COMM_INST(instIdx));
}

/* ************************************************************************
 * State: WaitForSilentCom
 * Parent state: SilentCom
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) WaitForSilentCom -> SilentComNotifed: BUSSM_MODE_IND_SILENT_COM[]/
 * 2) WaitForSilentCom -> WaitForSilentCom: BUSSM_TIMEOUT[]/
 */

FUNC(void, COMM_CODE) ComM_HsmComMSfWaitForSilentComEntry(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFWAITFORSILENTCOMENTRY_ENTRY(COMM_INST(instIdx));
  /* entry action 'ComM_BusSmRequestComMode(COMM_SILENT_COMMUNICATION);' */

  /* Request silent communication mode from corresponding Bus state manager */
  ComM_BusSmRequestComMode(instIdx, COMM_SILENT_COMMUNICATION);
  DBG_COMM_HSMCOMMSFWAITFORSILENTCOMENTRY_EXIT(COMM_INST(instIdx));
}
FUNC(void, COMM_CODE) ComM_HsmComMSfWaitForSilentComExit(
   COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMSFWAITFORSILENTCOMEXIT_ENTRY(COMM_INST(instIdx));
  /* exit action 'StopTimer();' */
  ComM_StopTimer(instIdx);
  DBG_COMM_HSMCOMMSFWAITFORSILENTCOMEXIT_EXIT(COMM_INST(instIdx));
}

/*------------------[Timer function]----------------------------------------*/

FUNC(void, COMM_CODE) ComM_ProcessTimers(
  const uint8 Channel)
{
  DBG_COMM_PROCESSTIMERS_ENTRY(Channel);
#if (COMM_HSM_INST_MULTI_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(Channel);
#endif

  if (COMM_TIMER(Channel) > 0U)
  {
    --COMM_TIMER(Channel);
    if ((COMM_TIMER(Channel) == 0U)
        && (COMM_HSM_EVENT_INVALID != COMM_TIMEOUT_EVENT(Channel)))
    {
      /* timeout events are generated outside of transitions, therefore do not
       * use the EMITTOSELF function */
      (void)COMM_HSMEMITINST(
        &ComM_HsmScComM, Channel, COMM_TIMEOUT_EVENT(Channel));
    }
  }
  DBG_COMM_PROCESSTIMERS_EXIT(Channel);
}

/*==================[internal function definitions]=========================*/

/*------------------[ComM_Notify]--------------------------------------------*/

STATIC FUNC(void, COMM_CODE) ComM_Notify(
  uint8               Channel,
  const ComM_ModeType ComMMode)
{
  uint8 instIdx = COMM_CHANNEL(Channel);

#if (COMM_INCLUDE_RTE == STD_ON)
  uint8_least i;
#endif
  DBG_COMM_NOTIFY_ENTRY(Channel, ComMMode);
  /* Set the current mode of the Channel */
  COMM_CHANNELMODE(Channel) = ComMMode;

  /* Report full communication mode of ComM to RTE */
#if (COMM_INCLUDE_RTE == STD_ON)
  /* For all users of the channel */
  for (i = 0U; i < COMM_NUM_USERS_OF_CHANNEL(Channel); i++)
  {
    const uint8 User = COMM_USERSOFCHANNEL(Channel,i);

   /* Report the mode to RTE, if the current mode was not yet reported to
    * the Rte for this user */
      COMM_EB_RTE_NOTIFY(User);
  }
#endif

  /* Report communication mode of ComM to BswM */
  BswM_ComM_CurrentMode(instIdx, ComMMode);

  /* Report communication mode of ComM to DCM */
#if (COMM_DCM_ENABLED == STD_ON)
  if (COMM_FULL_COMMUNICATION == COMM_CHANNELMODE(Channel))
  {
    Dcm_ComM_FullComModeEntered(instIdx);
  }
  else if (COMM_SILENT_COMMUNICATION == COMM_CHANNELMODE(Channel))
  {
    Dcm_ComM_SilentComModeEntered(instIdx);
  }
  else
  {
    Dcm_ComM_NoComModeEntered(instIdx);
  }
#endif
  DBG_COMM_NOTIFY_EXIT(Channel, ComMMode);
}

/*------------------[ComM_BusSmRequestComMode]------------------------------*/

STATIC FUNC(void, COMM_CODE) ComM_BusSmRequestComMode(
  const uint8         Channel,
  const ComM_ModeType reqComMMode)
{
  ComM_ModeType curComMMode;

  DBG_COMM_BUSSMREQUESTCOMMODE_ENTRY(Channel, reqComMMode);

  if ((E_OK != COMM_BUSSM_GET_CURRENT_COM_MODE(Channel, &curComMMode))
    || (curComMMode != reqComMMode))
  {
    if(E_OK != ComM_BusSMRequestComModeFpList[
         COMM_BUSTYPE_OF_CHANNEL(Channel)](
          COMM_CHANNEL(Channel), reqComMMode))
    {
      /* Start the timer, when BusSM_RequestComMode() returns E_NOT_OK
       * (e.g LINSM174), once the expiry of the timer, and if the
       * target communication mode is not achieved, ComM shall resend
       * the request again to the BusSM */
      ComM_StartTimer(
           Channel, COMM_HSM_COMM_EV_BUSSM_TIMEOUT, COMM_BUSSM_RETRY_TIME);
    }
  }
  else if (curComMMode == COMM_FULL_COMMUNICATION)
  {
    (void)COMM_HSMEMITTOSELFINST(
      &ComM_HsmScComM, Channel, COMM_HSM_COMM_EV_BUSSM_MODE_IND_FULL_COM);
  }
  else if (curComMMode == COMM_SILENT_COMMUNICATION)
  {
    (void)COMM_HSMEMITTOSELFINST(
      &ComM_HsmScComM, Channel, COMM_HSM_COMM_EV_BUSSM_MODE_IND_SILENT_COM);
  }
  else
  {
    (void)COMM_HSMEMITTOSELFINST(
      &ComM_HsmScComM, Channel, COMM_HSM_COMM_EV_BUSSM_MODE_IND_NO_COM);
  }
  DBG_COMM_BUSSMREQUESTCOMMODE_EXIT(Channel, reqComMMode);
}

STATIC FUNC(void, COMM_CODE) ComM_RetryBusSmRequest(
  const uint8         Channel)
{
  DBG_COMM_RETRYBUSSMREQUEST_ENTRY(Channel);
  if (0U == ComM_BusSMRetryCounter[Channel])
  {
    /* BusSM Request Retry counter reaches the limit;
     * emit the event "BUSSM_RETRY_COUNT_LIMIT" */
   (void)COMM_HSMEMITINST(&ComM_HsmScComM, Channel,
                      COMM_HSM_COMM_EV_BUSSM_RETRY_COUNT_LIMIT
                    );
  }
  else
  {
    ComM_BusSmRequestComMode(Channel, COMM_FULL_COMMUNICATION);

    /* Decrement BusSM Request Retry counter */
    ComM_BusSMRetryCounter[Channel]--;
  }
  DBG_COMM_RETRYBUSSMREQUEST_EXIT(Channel);
}

/*------------------[ComM_ClearUserRequest]----------------------------------*/
#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
STATIC FUNC(void, COMM_CODE)
  ComM_ClearUserRequest(COMM_PDL_SF(const uint8 instIdx))
{
  /* Get number of users of specific channel */
  const uint8 NumUser = COMM_NUM_USERS_OF_CHANNEL(instIdx);
  uint8_least UserIdx;

  /* For all users of shared channel of ComM */
  for (UserIdx = 0U; UserIdx < NumUser; ++UserIdx)
  {
    /* Get specific users of shared channel */
    const uint8 User = COMM_USERSOFCHANNEL(instIdx,UserIdx);
    boolean AllInNoCom = TRUE;
    uint8_least ChannelPos;

    /* [ComM582]: Check if all the channels that belong to the user
     * have entered COMM_NO_COMMUNICATION mode.
     */
    for (ChannelPos = 0U; ChannelPos < ComM_NumChannelsOfUser[User]; ++ChannelPos)
    {
      const uint8 Channel = ComM_ChannelsOfUser[User][ChannelPos];

      /* Check current communication mode of the channel  */
      if (COMM_NO_COMMUNICATION < ComM_ChannelMode[Channel])
      {
        /* At least one channel has not yet reached COMM_NO_COMMUNICATION.
         * Reset the flag and leave the loop.
         */
        AllInNoCom = FALSE;
        break;
      }
    }

    /* Clear the user request if all the channels that belong to the user
     * have entered COMM_NO_COMMUNICATION mode
     */
    if (TRUE == AllInNoCom)
    {
      /* Call the SchM wrapper functions */
      ComM_Enter_SCHM_COMM_EXCLUSIVE_AREA_0();
      ComM_UserRequestedComMode[User] = COMM_NO_COMMUNICATION;
      ComM_Exit_SCHM_COMM_EXCLUSIVE_AREA_0();
    }
  }
}
#endif
/*------------------[ComM_IsChanRelAllowed]---------------------------------*/

STATIC FUNC(boolean, COMM_CODE) ComM_IsChanRelAllowed(
  COMM_PDL_SF(const uint8 Channel))
{
  boolean ret;
  boolean PncFullComRequested = FALSE;
  boolean DcmFullComRequested = FALSE;
  DBG_COMM_ISCHANRELALLOWED_ENTRY(COMM_INST(Channel));

  /* When PncSupport is enabled, return TRUE
   *  - if Full communication is not requested AND
   *    all associated PNCs are in PNC_NO_COMMUNICATION state or
   *    Limit to No Com is enabled for the channel AND
   *  - active diagnostic request is not active
   *
   * When PncSupport is disabled, return TRUE
   *  - if communication mode is not requested or Limit to No Com is enabled
   *    for the channel AND
   *  - active diagnostic request is not active
   */

  /* This guard function is also called in state 'WaitForNoCom' for which
   * the ComM state is 'COMM_NO_COM_REQUEST_PENDING'.
   * However, checking the "PncActive" status is required only in
   * ComM state 'COMM_FULL_COM_NETWORK_REQUESTED'.
   */

/* Deviation MISRA-2, MISRA-3 <+35> */
#if (COMM_PNC_SUPPORT == STD_ON)
  if(COMM_CHANNELSTATE(Channel) == COMM_FULL_COM_NETWORK_REQUESTED)
  {
    PncFullComRequested = ComM_BitArrayIsBitSet(ComM_ChannelActiveStatus, COMM_INST(Channel));
  }
#endif

#if (COMM_DCM_ENABLED == STD_ON)
  DcmFullComRequested = ComM_BitArrayIsBitSet(ComM_DcmActiveStatus, COMM_INST(Channel));
#endif

  ret = ( ( ( (COMM_REQUESTEDCOMMODE(Channel) != COMM_FULL_COMMUNICATION) &&
              (FALSE == PncFullComRequested)
            ) ||
            (TRUE == COMM_CHANNEL_NOCOM_INHIBITION_STATUS(Channel))
          )
          && (FALSE == DcmFullComRequested)
        );

  DBG_COMM_ISCHANRELALLOWED_EXIT(ret, COMM_INST(Channel));
  return ret;
}

/*------------------[ComM_IsChanReqAllowedFullCom]--------------------------*/

STATIC FUNC(boolean, COMM_CODE) ComM_IsChanReqAllowedFullCom(
  COMM_PDL_SF(const uint8 Channel))
{
  boolean ret;
  DBG_COMM_ISCHANREQALLOWEDFULLCOM_ENTRY(COMM_INST(Channel));
  /* return TRUE if communication mode is requested and Limit to No Com is
   * disabled for the channel or active diagnostic request is active */

  /* Deviation MISRA-2, MISRA-3 <+12> */
#if (COMM_DCM_ENABLED == STD_ON)
  ret = ( ( (COMM_REQUESTEDCOMMODE(Channel) == COMM_FULL_COMMUNICATION) &&
             (COMM_CHANNEL_NOCOM_INHIBITION_STATUS(Channel) == FALSE)
           ) ||
           (TRUE == ComM_BitArrayIsBitSet(ComM_DcmActiveStatus, COMM_INST(Channel)))
         ) ? TRUE : FALSE;
#else
  ret =  ( (COMM_REQUESTEDCOMMODE(Channel) == COMM_FULL_COMMUNICATION) &&
            (COMM_CHANNEL_NOCOM_INHIBITION_STATUS(Channel) == FALSE)
          ) ? TRUE : FALSE;
#endif
  DBG_COMM_ISCHANREQALLOWEDFULLCOM_EXIT(ret, COMM_INST(Channel));
  return ret;
}

/*------------------[ComM_IsChanReqAllowedNoFullCom]------------------------*/

STATIC FUNC(boolean, COMM_CODE) ComM_IsChanReqAllowedNoFullCom(
  COMM_PDL_SF(const uint8 Channel))
{
  boolean ret;
  DBG_COMM_ISCHANREQALLOWEDNOFULLCOM_ENTRY(COMM_INST(Channel));
  /* return TRUE if communication mode is requested and Limit to No Com is
   * disabled and WakeUp Inhibition is disabled for the channel or active
   * diagnostic request is active */

  /* Deviation MISRA-2, MISRA-3 <+16> */
#if (COMM_DCM_ENABLED == STD_ON)
  ret = ( ( (COMM_REQUESTEDCOMMODE(Channel) == COMM_FULL_COMMUNICATION) &&
             ( (COMM_CHANNEL_NOCOM_INHIBITION_STATUS(Channel) == FALSE) &&
               (COMM_CHANNEL_WAKEUP_INHIBITION_STATUS(Channel) == FALSE)
             )
           ) ||
           (TRUE == ComM_BitArrayIsBitSet(ComM_DcmActiveStatus, COMM_INST(Channel)))
         ) ? TRUE : FALSE;
#else
  ret =  ( (COMM_REQUESTEDCOMMODE(Channel) == COMM_FULL_COMMUNICATION) &&
            ( (COMM_CHANNEL_NOCOM_INHIBITION_STATUS(Channel) == FALSE) &&
              (COMM_CHANNEL_WAKEUP_INHIBITION_STATUS(Channel) == FALSE)
            )
          ) ? TRUE : FALSE;
#endif
  DBG_COMM_ISCHANREQALLOWEDNOFULLCOM_EXIT(ret, COMM_INST(Channel));
  return ret;
}

/*------------------[ComM_CheckNwr]---------------------------------*/

STATIC FUNC(void, COMM_CODE) ComM_CheckNwr(
  COMM_PDL_SF(const uint8 Channel))
{
#if (COMM_NM_ACCESS_NEEDED == STD_ON)
  Nm_StateType  nmState;
  Nm_ModeType   nmMode;
  Std_ReturnType RetVal;
#endif
  DBG_COMM_CHECKNWR_ENTRY(COMM_INST(Channel));
#if (COMM_NM_ACCESS_NEEDED == STD_OFF)
  COMM_PARAM_UNUSED(Channel);
#else
  RetVal = Nm_GetState(COMM_NM_CHANNEL_OF_CHANNEL(Channel), &nmState, &nmMode);
  if ((E_OK == RetVal) && (NM_MODE_NETWORK == nmMode))
  {
    (void)COMM_HSMEMITTOSELFINST(
      &ComM_HsmScComM, Channel, COMM_HSM_COMM_EV_NM_NETWORK_MODE);
  }
#endif
  DBG_COMM_CHECKNWR_EXIT(COMM_INST(Channel));
}

#define COMM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[end of file]===========================================*/
