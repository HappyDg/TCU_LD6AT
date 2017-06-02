#if (!defined ECUM_INT_H)
#define ECUM_INT_H

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

/*==================[inclusions]============================================*/

#include <Std_Types.h>     /* AUTOSAR standard types */
#include <EcuM.h>          /* module public API, types needed in declarations */
#include <TSAutosar.h>     /* EB specific standard types */

#if (ECUM_DEV_ERROR_DETECT == STD_ON)
#include <Det.h>          /* Det API */
#endif

#if (ECUM_INCLUDE_DEM == STD_ON)
/* !LINKSTO EcuM2875,1 */
#include <Dem.h>          /* Dem error types */
#endif

#include <Mcu.h>

/*==================[macros]================================================*/

#if (defined ECUM_INSTANCE_ID)
#error ECUM_INSTANCE_ID already defined
#endif
/** \brief Instance ID of EcuM */
#define ECUM_INSTANCE_ID 0U

/*------------------[AUTOSAR development check]-----------------------------*/

#if (defined ECUM_DET_REPORT_ERROR)
#error ECUM_DET_REPORT_ERROR already defined
#endif
#if (ECUM_DEV_ERROR_DETECT == STD_ON)
/** \brief Macro for reporting an error to Det
 **
 ** \param[in] SID Service ID of the API function
 ** \param[in] ERROR_CODE Error code reported to Det module */
#define ECUM_DET_REPORT_ERROR(SID,ERROR_CODE)                           \
  (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, (SID), (ERROR_CODE))

#else
/** \brief  If ECUM_DEV_ERROR_DETECT turned off then
 ** expand ECUM_DET_REPORT_ERROR to nothing */
#define ECUM_DET_REPORT_ERROR(SID,ERROR_CODE)
#endif




/*------------------------[Defensive programming]----------------------------*/

#if (defined ECUM_PRECONDITION_ASSERT)
#error ECUM_PRECONDITION_ASSERT is already defined
#endif
#if (ECUM_PRECONDITION_ASSERT_ENABLED == STD_ON)
/** \brief Report an assertion violation to Det
 **
 ** \param[in] Condition Condition which is violated
 ** \param[in] ApiId Service ID of the API function */
#define ECUM_PRECONDITION_ASSERT(Condition, ApiId) \
  DET_PRECONDITION_ASSERT((Condition), ECUM_MODULE_ID, ECUM_INSTANCE_ID, (ApiId))
#else
#define ECUM_PRECONDITION_ASSERT(Condition, ApiId)
#endif

#if (defined ECUM_POSTCONDITION_ASSERT)
#error ECUM_POSTCONDITION_ASSERT is already defined
#endif
#if (ECUM_POSTCONDITION_ASSERT_ENABLED == STD_ON)
/** \brief Report an assertion violation to Det
 **
 ** \param[in] Condition Condition which is violated
 ** \param[in] ApiId Service ID of the API function */
#define ECUM_POSTCONDITION_ASSERT(Condition, ApiId) \
  DET_POSTCONDITION_ASSERT((Condition), ECUM_MODULE_ID, ECUM_INSTANCE_ID, (ApiId))
#else
#define ECUM_POSTCONDITION_ASSERT(Condition, ApiId)
#endif

#if (defined ECUM_INVARIANT_ASSERT)
#error ECUM_INVARIANT_ASSERT is already defined
#endif
#if (ECUM_INVARIANT_ASSERT_ENABLED == STD_ON)
/** \brief Report an assertion violation to Det
 **
 ** \param[in] Condition Condition which is violated
 ** \param[in] ApiId Service ID of the API function */
#define ECUM_INVARIANT_ASSERT(Condition, ApiId) \
  DET_INVARIANT_ASSERT((Condition), ECUM_MODULE_ID, ECUM_INSTANCE_ID, (ApiId))
#else
#define ECUM_INVARIANT_ASSERT(Condition, ApiId)
#endif

#if (defined ECUM_STATIC_ASSERT)
# error ECUM_STATIC_ASSERT is already defined
#endif
#if (ECUM_STATIC_ASSERT_ENABLED == STD_ON)
/** \brief Report an static assertion violation to Det
 **
 ** \param[in] Condition Condition which is violated */
# define ECUM_STATIC_ASSERT(expr) DET_STATIC_ASSERT(expr)
#else
# define ECUM_STATIC_ASSERT(expr)
#endif

#if (defined ECUM_UNREACHABLE_CODE_ASSERT)
#error ECUM_UNREACHABLE_CODE_ASSERT is already defined
#endif
#if (ECUM_UNREACHABLE_CODE_ASSERT_ENABLED == STD_ON)
/** \brief Report an unreachable code assertion violation to Det
 **
 ** \param[in] ApiId Service ID of the API function */
#define ECUM_UNREACHABLE_CODE_ASSERT(ApiId) \
  DET_UNREACHABLE_CODE_ASSERT(ECUM_MODULE_ID, ECUM_INSTANCE_ID, (ApiId))
#else
#define ECUM_UNREACHABLE_CODE_ASSERT(ApiId)
#endif

#if (defined ECUM_INTERNAL_API_ID)
#error ECUM_INTERNAL_API_ID is already defined
#endif
/** \brief API ID of module internal functions to be used in assertions */
#define ECUM_INTERNAL_API_ID DET_INTERNAL_API_ID


/*------------------[other internal identifiers]----------------------------*/

#if (defined ECUM_STATE_UNINIT)
#error ECUM_STATE_UNINIT already defined
#endif
/** \brief If EcuM_State is not set, it is equal to 0 */
#define ECUM_STATE_UNINIT               0U

#if (defined ECUM_WKS_DEFAULT)
#error ECUM_WKS_DEFAULT already defined
#endif
/** \brief All default wakeup sources.
 *
 * Bitwise 'or' of the default wakeup sources:
 *  - ECUM_WKSOURCE_POWER          0x01
 *  - ECUM_WKSOURCE_RESET          0x02
 *  - ECUM_WKSOURCE_INTERNAL_RESET 0x04
 *  - ECUM_WKSOURCE_INTERNAL_WDG   0x08
 *  - ECUM_WKSOURCE_EXTERNAL_WDG   0x10 */
#define ECUM_WKS_DEFAULT                                                \
  (ECUM_WKSOURCE_POWER | ECUM_WKSOURCE_RESET | ECUM_WKSOURCE_INTERNAL_RESET \
   | ECUM_WKSOURCE_INTERNAL_WDG | ECUM_WKSOURCE_EXTERNAL_WDG)


#if (defined ECUM_NO_COMM_CH)
#error ECUM_NO_COMM_CH already defined
#endif
/** \brief NetworkHandle value for no ComM channel
 *
 * Used as value for the EcuM_WksConfigType::ComMCh if the wakeup source has
 * no ComM channel associated. */
#define ECUM_NO_COMM_CH                 0xFFU

/** \brief Invalid value for a Wakeup Source Index
 *
 * Used as value for the EcuM_WksMapping array if the wakeup source Id has
 * not been configured. */
#define ECUM_WKS_INVALID_ID             0xFFU

/** \brief Translate the Wakeup Source Id to Wakeup source configuration */
#define ECUM_WKSID_TO_CFG(WksId)        (EcuM_WksConfigList[EcuM_WksMapping[(WksId)]])

/** \brief Get the validation timeout for the Wakeup Source Id */
#define ECUM_WKS_VAL_TIMEOUT(WksId)     (EcuM_WksValTimeout[EcuM_WksMapping[(WksId)]])

#if (ECUM_ECUM_FIXED_SUPPORT == STD_ON)
#define ECUM_FIXED_STATE_INVALID        0x00U
#define ECUM_FIXED_STATE_STARTUP        0x01U
#define ECUM_FIXED_STATE_RUN            0x02U
#define ECUM_FIXED_STATE_POST_RUN       0x04U
#define ECUM_FIXED_STATE_SHUTDOWN       0x05U
#define ECUM_FIXED_STATE_OFF            0x06U
#define ECUM_USER_IDX(usr) ((uint8)((usr)/8U))
#define ECUM_USER_FLG(usr) ((usr)%8U)

/*------------------[internal mode defines]----------------------------*/
#if (defined ECUM_EB_MODE_STARTUP)
#error ECUM_EB_MODE_STARTUP already defined
#endif
/** \brief internal define for STARTUP mode
 *
 * This define is required to separate BSW specific code from Rte specific
 * code. */
#define ECUM_EB_MODE_STARTUP 0U

#if (defined ECUM_EB_MODE_RUN)
#error ECUM_EB_MODE_RUN already defined
#endif
/** \brief internal define for RUN mode
 *
 * This define is required to separate BSW specific code from Rte specific
 * code. */
#define ECUM_EB_MODE_RUN 1U

#if (defined ECUM_EB_MODE_POST_RUN)
#error ECUM_EB_MODE_POST_RUN already defined
#endif
/** \brief internal define for POST_RUN mode
 *
 * This define is required to separate BSW specific code from Rte specific
 * code. */
#define ECUM_EB_MODE_POST_RUN 2U


#if (defined ECUM_EB_MODE_SHUTDOWN)
#error ECUM_EB_MODE_SHUTDOWN already defined
#endif
/** \brief internal define for SHUTDOWN mode
 *
 * This define is required to separate BSW specific code from Rte specific
 * code. */
#define ECUM_EB_MODE_SHUTDOWN 3U

#if (defined ECUM_EB_MODE_SLEEP)
#error ECUM_EB_MODE_SLEEP already defined
#endif
/** \brief internal define for SLEEP mode
 *
 * This define is required to separate BSW specific code from Rte specific
 * code. */
#define ECUM_EB_MODE_SLEEP 4U

#if (defined ECUM_EB_MODE_WAKE_SLEEP)
#error ECUM_EB_MODE_WAKE_SLEEP already defined
#endif
/** \brief internal define for WAKE_SLEEP mode
 *
 * This define is required to separate BSW specific code from Rte specific
 * code. */
#define ECUM_EB_MODE_WAKE_SLEEP 5U
#endif /* (ECUM_ECUM_FIXED_SUPPORT == STD_ON) */

/*==================[type definitions]======================================*/

/** \brief Type for holding a wakeup source configuration */
typedef struct
{
  /** \brief ComM channel associated to this Wakeup Source */
  NetworkHandleType ComMCh;
  /** \brief Reset reason associated to this Wakeup Source */
  Mcu_ResetType     ResetReason;
  /** \brief The identifier of this Wakeup Source */
  uint8             WksId;
} EcuM_WksConfigType;

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

#define ECUM_START_SEC_CODE
#include <MemMap.h>

/** \brief Proxy function for SchM_Enter_EcuM_SCHM_ECUM_EXCLUSIVE_AREA_0
 **
 ** This function was introduced to avoid RTE includes
 ** within compilation units EcuM.c and EcuM_BootTarget.c
 **
 ** \return No return value. */
FUNC(void, ECUM_CODE) EcuM_Enter_SCHM_ECUM_EXCLUSIVE_AREA_0 (void);

/** \brief Proxy function for SchM_Exit_EcuM_SCHM_ECUM_EXCLUSIVE_AREA_0
 **
 ** This function was introduced to avoid RTE includes
 ** within compilation unit EcuM.c and EcuM_BootTarget.c
 **
 ** \return No return value. */
FUNC(void, ECUM_CODE) EcuM_Exit_SCHM_ECUM_EXCLUSIVE_AREA_0 (void);

/** \brief Proxy function for SchM_Init
 **
 ** This function was introduced to avoid RTE includes
 ** within compilation units EcuM.c and EcuM_BootTarget.c
 **
 ** \return No return value. */
FUNC(void, ECUM_CODE) EcuM_SchM_Init(void);

/** \brief Proxy function for SchM_Deinit
 **
 ** This function was introduced to avoid RTE includes
 ** within compilation units EcuM.c and EcuM_BootTarget.c
 **
 ** \return No return value. */
FUNC(void, ECUM_CODE) EcuM_SchM_Deinit(void);

#if (ECUM_ECUM_FIXED_SUPPORT == STD_ON)
#if (ECUM_EB_DEFAULT_ASR_SERVICE_API != ECUM_EB_SERVICE_API_NONE)
/** \brief Signal mode change via RTE
 *
 * The function receives the status from the EcuM point of view and has to
 * translate them into the values expected by the RTE. The reported values depend
 * on the AUTOSAR service API selected as default.
 *
 * \param[in] mode  new mode */
FUNC(void, ECUM_CODE) EcuM_RteModeSwitch(uint8 mode);
#endif /* (ECUM_EB_DEFAULT_ASR_SERVICE_API != ECUM_EB_SERVICE_API_NONE) */

#if (ECUM_EB_ENABLE_ASR32_SERVICE_API == STD_ON)
/** \brief Signal mode change via RTE
 *
 * The function receives the status from the EcuM point of view and has to
 * translate them into the Autosar 3.2 values expected by the RTE.
 *
 * \param[in] mode  new mode */
FUNC(void, ECUM_CODE) EcuM_ASR32_RteModeSwitch(uint8 mode);
#endif /* (ECUM_EB_ENABLE_ASR32_SERVICE_API == STD_ON) */

#if (ECUM_EB_ENABLE_ASR40_SERVICE_API == STD_ON)
/** \brief Signal mode change via RTE
 *
 * The function receives the status from the EcuM point of view and has to
 * translate them into the Autosar 4.0 values expected by the RTE.
 *
 * \param[in] mode  new mode */
FUNC(void, ECUM_CODE) EcuM_ASR40_RteModeSwitch(uint8 mode);
#endif /* (ECUM_EB_ENABLE_ASR40_SERVICE_API == STD_ON) */
#endif /* (ECUM_ECUM_FIXED_SUPPORT == STD_ON) */

#define ECUM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]====================================*/

#define ECUM_START_SEC_CONST_8
#include <MemMap.h>

/** \brief Wake-up Source ID mapping
 **
 ** Translation array to map a Wake-up Source ID to an array index
 ** inside "EcuM_WksConfigList" or "EcuM_WksValTimeout".*/
extern CONST(uint8, ECUM_CONST) EcuM_WksMapping[ECUM_WKS_ID_MAXVAL + 1U];

#define ECUM_STOP_SEC_CONST_8
#include <MemMap.h>

#define ECUM_START_SEC_CONST_16
#include <MemMap.h>

/** \brief Timeout for wakeup source */
extern CONST(uint16, ECUM_CONST) EcuM_WksValTimeout[ECUM_WKSCONFIGNUM];

#define ECUM_STOP_SEC_CONST_16
#include <MemMap.h>


#define ECUM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief List of Sleep Modes Configurations */
extern CONST(EcuM_SleepModeConfigType, ECUM_CONST)
  EcuM_SleepModeConfigList[ECUM_SLEEPMODECONFIGNUM];

/** \brief List of Wakeup Source Configurations */
extern CONST(EcuM_WksConfigType, ECUM_CONST)
  EcuM_WksConfigList[ECUM_WKSCONFIGNUM];

#if (ECUM_INCLUDE_DEM == STD_ON)
#if(ECUM_PROD_ERR_RAM_CHECK_FAILURE == TS_PROD_ERR_REP_TO_DEM)
/** \brief Event ID for ECUM_E_RAM_CHECK_FAILED */
extern CONST(Dem_EventIdType, ECUM_CONST) EcuM_DemErrRamChkFailed;
#endif

#if(ECUM_PROD_ERR_CFG_DATA_INCONSISTENT == TS_PROD_ERR_REP_TO_DEM)
/** \brief Event ID for ECUM_E_CONFIGURATION_DATA_INCONSISTENT */
extern CONST(Dem_EventIdType, ECUM_CONST) EcuM_DemErrConfigDataInconsistent;
#endif
#if (ECUM_ECUM_FIXED_SUPPORT == STD_ON)
/** \brief Event ID for ECUM_E_ALL_RUN_REQUESTS_KILLED */
extern CONST(Dem_EventIdType, ECUM_CONST) EcuM_DemErrAllRUNRequestsKilled;
#endif /* (ECUM_ECUM_FIXED_SUPPORT == STD_ON) */
#endif

#if (ECUM_DEV_ERROR_DETECT == STD_ON)
/** \brief Array holding the configured values of Shutdown Causes */
extern CONST(EcuM_ShutdownCauseType, ECUM_CONST)
   EcuM_ValidShutdownCause[ECUM_SHUTDOWNCAUSECONFIGNUM];
#endif

#define ECUM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

#define ECUM_START_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief EcuM State
 **
 ** This variable holds the current state of the EcuM module. */
extern VAR(EcuM_StateType, ECUM_VAR) EcuM_State;

#define ECUM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/
#endif /* if !defined( ECUM_INT_H ) */
