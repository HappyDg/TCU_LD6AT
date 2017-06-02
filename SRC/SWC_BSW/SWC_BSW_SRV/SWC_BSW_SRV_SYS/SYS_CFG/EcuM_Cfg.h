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

/* !LINKSTO EcuM2993,1 */
#if (!defined ECUM_CFG_H)
#define ECUM_CFG_H

/*==================[includes]==============================================*/

#include <Os.h>                 /* OS AppMode */
#include <Std_Types.h>          /* AUTOSAR standard types */

/*==================[macros]================================================*/

#if (defined ECUM_EB_SERVICE_API_NONE)
#error ECUM_EB_SERVICE_API_NONE already defined
#endif
/** \brief Definition that no service API is set as default **/
#define ECUM_EB_SERVICE_API_NONE 0U

#if (defined ECUM_EB_SERVICE_API_ASR32)
#error ECUM_EB_SERVICE_API_ASR32 already defined
#endif
/** \brief Definition that AUTOSAR 3.2 service API is set as default **/
#define ECUM_EB_SERVICE_API_ASR32 32U

#if (defined ECUM_EB_SERVICE_API_ASR40)
#error ECUM_EB_SERVICE_API_ASR40 already defined
#endif
/** \brief Definition that AUTOSAR 4.0 service API is set as default **/
#define ECUM_EB_SERVICE_API_ASR40 40U

#if (defined ECUM_EB_ENABLE_ASR32_SERVICE_API)
#error ECUM_EB_ENABLE_ASR32_SERVICE_API already defined
#endif
/** \brief Definition whether AUTOSAR 3.2 service API for EcuM is enabled **/
#define ECUM_EB_ENABLE_ASR32_SERVICE_API                   STD_OFF

#if (defined ECUM_EB_ENABLE_ASR40_SERVICE_API)
#error ECUM_EB_ENABLE_ASR40_SERVICE_API already defined
#endif
/** \brief Definition whether AUTOSAR 4.0 service API for EcuM is enabled **/
#define ECUM_EB_ENABLE_ASR40_SERVICE_API                   STD_OFF

#if (defined ECUM_EB_DEFAULT_ASR_SERVICE_API)
#error ECUM_EB_DEFAULT_ASR_SERVICE_API already defined
#endif
/** \brief Definition of default service API **/
#define ECUM_EB_DEFAULT_ASR_SERVICE_API                    ECUM_EB_SERVICE_API_NONE


/** \brief Switch for DET usage */
/* !LINKSTO EcuM2983,1 */
#define ECUM_DEV_ERROR_DETECT      STD_OFF

/** \brief Switch for Defensive behaviour usage */
#define ECUM_DEF_BEHAVIOUR_ENABLED STD_OFF

#if (defined ECUM_INCLUDE_DET)
#error ECUM_INCLUDE_DET already defined
#endif
/** \brief Initialize Det module at startup **/
#define ECUM_INCLUDE_DET           STD_OFF

#if (defined ECUM_INCLUDE_DEM)
#error ECUM_INCLUDE_DEM already defined
#endif
/** \brief Initialize Dem module at startup **/
#define ECUM_INCLUDE_DEM           STD_OFF

#if (defined ECUM_INCLUDE_RTE)
#error ECUM_INCLUDE_RTE already defined
#endif
/** \brief Check if Rte is used in EcuM **/
#define ECUM_INCLUDE_RTE           STD_OFF

#if (defined ECUM_USE_BOOTTARGET_SEC)
#error ECUM_USE_BOOTTARGET_SEC already defined
#endif
/** \brief Use special memory section for EcuM_BootTarget */
#define ECUM_USE_BOOTTARGET_SEC    STD_OFF

#if (defined ECUM_VERSION_INFO_API)
#error ECUM_VERSION_INFO_API already defined
#endif
/** \brief Provide EcuM_GetVersionInfo() API !*/
#define ECUM_VERSION_INFO_API      STD_ON

#if (defined ECUM_PROVIDE_SHUTDOWN_HOOK)
#error ECUM_PROVIDE_SHUTDOWN_HOOK already defined
#endif
/** \brief Provide minimalistic ShutdownHook() implementation */
#define ECUM_PROVIDE_SHUTDOWN_HOOK STD_OFF

/** \brief Switch for Reset Loop Detection usage */
#define ECUM_RESET_LOOP_DETECTION  STD_OFF

#define ECUM_ECUM_FIXED_SUPPORT    STD_OFF
#if (defined ECUM_STORED_SHUTDOWN_OPERATIONS)
#error ECUM_STORED_SHUTDOWN_OPERATIONS already defined
#endif
/** \brief Size of the array which contains all the recent
 shutdown information. Used to implement EcuM_GetNextRecentShutdown() */
#define ECUM_STORED_SHUTDOWN_OPERATIONS   1U
/*------------------[DEM/DET error configuration]---------------------------*/

#if (defined ECUM_PROD_ERR_RAM_CHECK_FAILURE)
#error ECUM_PROD_ERR_RAM_CHECK_FAILURE already defined
#endif
/** \brief Switch for DEM to DET reporting Ram Check Failure */
#define ECUM_PROD_ERR_RAM_CHECK_FAILURE                 TS_PROD_ERR_DISABLE

#if (defined ECUM_PROD_ERR_CFG_DATA_INCONSISTENT)
#error ECUM_PROD_ERR_CFG_DATA_INCONSISTENT already defined
#endif
/** \brief Switch for DEM to DET reporting Configuration Data Inconsistent
 **
 ** This preprocessor macro belongs to a feature which is not supported by the
 ** current implementation. It is available for completeness reasons only. */
#define ECUM_PROD_ERR_CFG_DATA_INCONSISTENT             TS_PROD_ERR_DISABLE


#if (defined ECUM_PROD_ERR_ALL_RUN_REQUESTS_KILLED)
#error ECUM_PROD_ERR_ALL_RUN_REQUESTS_KILLED already defined
#endif
/** \brief Switch for DEM reporting of all run requests killed */
#define ECUM_PROD_ERR_ALL_RUN_REQUESTS_KILLED TS_PROD_ERR_DISABLE

/*------------------[User defined initialization switches]------------------*/

/** \brief Switch for usage of EcuM_Al_DriverInitZero */
#define ECUM_INITLIST_ZERO      STD_OFF

/** \brief Switch for usage of EcuM_Al_DriverInitOne */
#define ECUM_INITLIST_ONE       STD_ON

/** \brief Switch for usage of EcuM_Al_DriverRestart */
#define ECUM_INITLIST_RESTART   STD_ON

/*------------------[EcuM Flex User Config]--------------------------------------*/

/* Symbolic names which can be used for all function argument of type
 * EcuM_UserType */
#if (defined EcuMConf_EcuMFlexUserConfig_EcuMFlexUserConfig)
#error EcuMConf_EcuMFlexUserConfig_EcuMFlexUserConfig already defined
#endif
/** \brief Identifier for the EcuM user "EcuMFlexUserConfig" */
#define EcuMConf_EcuMFlexUserConfig_EcuMFlexUserConfig   0U

#if (!defined ECUM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined EcuMFlexUserConfig)
#error EcuMFlexUserConfig already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define EcuMFlexUserConfig   0U

#if (defined EcuM_EcuMFlexUserConfig)
#error EcuM_EcuMFlexUserConfig already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define EcuM_EcuMFlexUserConfig   0U
#endif /* ECUM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */



#define ECUM_FIXED_NUM_FIXED_USERS 0U
/*------------------[Wakeup Sources]----------------------------------------*/

#if (defined EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_POWER)
#error EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_POWER already defined
#endif
/** \brief Identifier for wakeup source ECUM_WKSOURCE_POWER */
#define EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_POWER   1U

#if (!defined ECUM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined ECUM_WKSOURCE_POWER)
#error ECUM_WKSOURCE_POWER already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define ECUM_WKSOURCE_POWER   1U

#if (defined EcuM_ECUM_WKSOURCE_POWER)
#error EcuM_ECUM_WKSOURCE_POWER already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define EcuM_ECUM_WKSOURCE_POWER   1U
#endif /* ECUM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

#if (defined EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_RESET)
#error EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_RESET already defined
#endif
/** \brief Identifier for wakeup source ECUM_WKSOURCE_RESET */
#define EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_RESET   2U

#if (!defined ECUM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined ECUM_WKSOURCE_RESET)
#error ECUM_WKSOURCE_RESET already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define ECUM_WKSOURCE_RESET   2U

#if (defined EcuM_ECUM_WKSOURCE_RESET)
#error EcuM_ECUM_WKSOURCE_RESET already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define EcuM_ECUM_WKSOURCE_RESET   2U
#endif /* ECUM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

#if (defined EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_INTERNAL_RESET)
#error EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_INTERNAL_RESET already defined
#endif
/** \brief Identifier for wakeup source ECUM_WKSOURCE_INTERNAL_RESET */
#define EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_INTERNAL_RESET   4U

#if (!defined ECUM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined ECUM_WKSOURCE_INTERNAL_RESET)
#error ECUM_WKSOURCE_INTERNAL_RESET already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define ECUM_WKSOURCE_INTERNAL_RESET   4U

#if (defined EcuM_ECUM_WKSOURCE_INTERNAL_RESET)
#error EcuM_ECUM_WKSOURCE_INTERNAL_RESET already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define EcuM_ECUM_WKSOURCE_INTERNAL_RESET   4U
#endif /* ECUM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

#if (defined EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_INTERNAL_WDG)
#error EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_INTERNAL_WDG already defined
#endif
/** \brief Identifier for wakeup source ECUM_WKSOURCE_INTERNAL_WDG */
#define EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_INTERNAL_WDG   8U

#if (!defined ECUM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined ECUM_WKSOURCE_INTERNAL_WDG)
#error ECUM_WKSOURCE_INTERNAL_WDG already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define ECUM_WKSOURCE_INTERNAL_WDG   8U

#if (defined EcuM_ECUM_WKSOURCE_INTERNAL_WDG)
#error EcuM_ECUM_WKSOURCE_INTERNAL_WDG already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define EcuM_ECUM_WKSOURCE_INTERNAL_WDG   8U
#endif /* ECUM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

#if (defined EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_EXTERNAL_WDG)
#error EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_EXTERNAL_WDG already defined
#endif
/** \brief Identifier for wakeup source ECUM_WKSOURCE_EXTERNAL_WDG */
#define EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_EXTERNAL_WDG   16U

#if (!defined ECUM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined ECUM_WKSOURCE_EXTERNAL_WDG)
#error ECUM_WKSOURCE_EXTERNAL_WDG already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define ECUM_WKSOURCE_EXTERNAL_WDG   16U

#if (defined EcuM_ECUM_WKSOURCE_EXTERNAL_WDG)
#error EcuM_ECUM_WKSOURCE_EXTERNAL_WDG already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define EcuM_ECUM_WKSOURCE_EXTERNAL_WDG   16U
#endif /* ECUM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

#if (defined EcuMConf_EcuMWakeupSource_EcuMWakeupSource1)
#error EcuMConf_EcuMWakeupSource_EcuMWakeupSource1 already defined
#endif
/** \brief Identifier for wakeup source EcuMWakeupSource1 */
#define EcuMConf_EcuMWakeupSource_EcuMWakeupSource1   32U

#if (!defined ECUM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined EcuMWakeupSource1)
#error EcuMWakeupSource1 already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define EcuMWakeupSource1   32U

#if (defined EcuM_EcuMWakeupSource1)
#error EcuM_EcuMWakeupSource1 already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define EcuM_EcuMWakeupSource1   32U
#endif /* ECUM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

#if (defined EcuMConf_EcuMWakeupSource_EcuMWakeupSource2)
#error EcuMConf_EcuMWakeupSource_EcuMWakeupSource2 already defined
#endif
/** \brief Identifier for wakeup source EcuMWakeupSource2 */
#define EcuMConf_EcuMWakeupSource_EcuMWakeupSource2   64U

#if (!defined ECUM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined EcuMWakeupSource2)
#error EcuMWakeupSource2 already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define EcuMWakeupSource2   64U

#if (defined EcuM_EcuMWakeupSource2)
#error EcuM_EcuMWakeupSource2 already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define EcuM_EcuMWakeupSource2   64U
#endif /* ECUM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

/** \brief Number of wakeup sources */
#define ECUM_WKSCONFIGNUM          7U

/** \brief Maximum value of Wakeup Source ID */
#define ECUM_WKS_ID_MAXVAL          6U

/** \brief Bit mask of all wakeup sources */
#define ECUM_WKSMASKALL (EcuM_WakeupSourceType)(\
   EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_POWER | \
   EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_RESET | \
   EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_INTERNAL_RESET | \
   EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_INTERNAL_WDG | \
   EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_EXTERNAL_WDG | \
   EcuMConf_EcuMWakeupSource_EcuMWakeupSource1 | \
   EcuMConf_EcuMWakeupSource_EcuMWakeupSource2 | \
   0U)

/** \brief Bit mask of wakeup sources with no validation All standard WKS
 * require no validation */
#define ECUM_WKSMASKNOVAL (EcuM_WakeupSourceType)(\
   EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_POWER | \
   EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_RESET | \
   EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_INTERNAL_RESET | \
   EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_INTERNAL_WDG | \
   EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_EXTERNAL_WDG | \
   EcuMConf_EcuMWakeupSource_EcuMWakeupSource1 | \
   0U)

/** \brief Bit mask of wakeup sources with ComM channel */
#define ECUM_WKSMASKCOMMCH (EcuM_WakeupSourceType)(\
   0U)

/** \brief Switch to enable handling of wakeup sources with ComM channel */
#define ECUM_WKS_COMMCH_ENABLED    STD_OFF

/*------------------[Sleep modes]-------------------------------------------*/
/* !LINKSTO EcuM2957,1 */
/** \brief number of sleep modes */
#define ECUM_SLEEPMODECONFIGNUM    1U

#if (defined EcuMConf_EcuMSleepMode_EcuMSleepMode)
#error EcuMConf_EcuMSleepMode_EcuMSleepMode already defined
#endif

/** \brief Identifier for sleep mode EcuMSleepMode */
#define EcuMConf_EcuMSleepMode_EcuMSleepMode   0x0U

#if (!defined ECUM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined EcuMSleepMode)
#error EcuMSleepMode already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define EcuMSleepMode   0x0U

#if (defined EcuM_EcuMSleepMode)
#error EcuM_EcuMSleepMode already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define EcuM_EcuMSleepMode   0x0U
#endif /* ECUM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

/** \brief Wakeup event mask of sleep mode EcuMSleepMode */
#define ECUM_EcuMSleepMode_WKUP_MASK (\
EcuMConf_EcuMWakeupSource_EcuMWakeupSource1 | \
0U)



/*------------------[Mcu Mode]----------------------------------------------*/

#if (defined McuConf_McuModeSettingConf_McuModeSettingConf_0)
#define ECUM_NORMALMCUMODE   McuConf_McuModeSettingConf_McuModeSettingConf_0  /* 0U */
#else
#define ECUM_NORMALMCUMODE   McuModeSettingConf_0   /* 0U */
#endif

/*------------------[Reset Modes]----------------------------------------------*/
/* !LINKSTO EcuM4005,1 */
#if (defined EcuMConf_EcuMResetMode_EcuMResetMode)
#error EcuMConf_EcuMResetMode_EcuMResetMode already defined
#endif
/** \brief Identifier for reset modes EcuMResetMode */
#define EcuMConf_EcuMResetMode_EcuMResetMode   0U

#if (!defined ECUM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined EcuMResetMode)
#error EcuMResetMode already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define EcuMResetMode   0U

#if (defined EcuM_EcuMResetMode)
#error EcuM_EcuMResetMode already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define EcuM_EcuMResetMode   0U
#endif /* ECUM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */


/*------------------[Shutdown Causes]----------------------------------------------*/
/* !LINKSTO EcuM4007,1 */
#if (defined EcuMConf_EcuMShutdownCause_EcuMShutdownCause)
#error EcuMConf_EcuMShutdownCause_EcuMShutdownCause already defined
#endif
/** \brief Identifier for reset modes EcuMShutdownCause */
#define EcuMConf_EcuMShutdownCause_EcuMShutdownCause   0U

#if (!defined ECUM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)


/* Generating the symbolic name for only user-configured
 * shutdown casues, since all pre-configured shutdown causes are already
 * defined in EcuM.h. */


#if (defined EcuM_EcuMShutdownCause)
#error EcuM_EcuMShutdownCause already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define EcuM_EcuMShutdownCause   0U
#endif /* ECUM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

#if (defined EcuMConf_EcuMShutdownCause_ECUM_CAUSE_ECU_STATE)
#error EcuMConf_EcuMShutdownCause_ECUM_CAUSE_ECU_STATE already defined
#endif
/** \brief Identifier for reset modes ECUM_CAUSE_ECU_STATE */
#define EcuMConf_EcuMShutdownCause_ECUM_CAUSE_ECU_STATE   1U

#if (!defined ECUM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)


/* Generating the symbolic name for only user-configured
 * shutdown casues, since all pre-configured shutdown causes are already
 * defined in EcuM.h. */


#if (defined EcuM_ECUM_CAUSE_ECU_STATE)
#error EcuM_ECUM_CAUSE_ECU_STATE already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define EcuM_ECUM_CAUSE_ECU_STATE   1U
#endif /* ECUM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

#if (defined EcuMConf_EcuMShutdownCause_ECUM_CAUSE_WDGM)
#error EcuMConf_EcuMShutdownCause_ECUM_CAUSE_WDGM already defined
#endif
/** \brief Identifier for reset modes ECUM_CAUSE_WDGM */
#define EcuMConf_EcuMShutdownCause_ECUM_CAUSE_WDGM   2U

#if (!defined ECUM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)


/* Generating the symbolic name for only user-configured
 * shutdown casues, since all pre-configured shutdown causes are already
 * defined in EcuM.h. */


#if (defined EcuM_ECUM_CAUSE_WDGM)
#error EcuM_ECUM_CAUSE_WDGM already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define EcuM_ECUM_CAUSE_WDGM   2U
#endif /* ECUM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

#if (defined EcuMConf_EcuMShutdownCause_ECUM_CAUSE_DCM)
#error EcuMConf_EcuMShutdownCause_ECUM_CAUSE_DCM already defined
#endif
/** \brief Identifier for reset modes ECUM_CAUSE_DCM */
#define EcuMConf_EcuMShutdownCause_ECUM_CAUSE_DCM   3U

#if (!defined ECUM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)


/* Generating the symbolic name for only user-configured
 * shutdown casues, since all pre-configured shutdown causes are already
 * defined in EcuM.h. */


#if (defined EcuM_ECUM_CAUSE_DCM)
#error EcuM_ECUM_CAUSE_DCM already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define EcuM_ECUM_CAUSE_DCM   3U
#endif /* ECUM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

/** \brief Number of shutdown causes */
#define ECUM_SHUTDOWNCAUSECONFIGNUM          4U

/*------------------[EcuM Alarm Clock]----------------------------------------------*/




/*------------------[EcuM Multi Core]-----------------------------------------------*/





#define ECUM_MULTICORE_ENABLED FALSE

#define ECUM_NUM_CORES 1U




/*------------------[Defensive programming]---------------------------------*/

#if (defined ECUM_DEFENSIVE_PROGRAMMING_ENABLED)
#error ECUM_DEFENSIVE_PROGRAMMING_ENABLED is already defined
#endif
/** \brief Defensive programming usage
 **
 ** En- or disables the usage of the defensive programming */
#define ECUM_DEFENSIVE_PROGRAMMING_ENABLED   STD_OFF

#if (defined ECUM_PRECONDITION_ASSERT_ENABLED)
#error ECUM_PRECONDITION_ASSERT_ENABLED is already defined
#endif
/** \brief Precondition assertion usage
 **
 ** En- or disables the usage of precondition assertion checks */
#define ECUM_PRECONDITION_ASSERT_ENABLED     STD_OFF

#if (defined ECUM_POSTCONDITION_ASSERT_ENABLED)
#error ECUM_POSTCONDITION_ASSERT_ENABLED is already defined
#endif
/** \brief Postcondition assertion usage
 **
 ** En- or disables the usage of postcondition assertion checks */
#define ECUM_POSTCONDITION_ASSERT_ENABLED    STD_OFF

#if (defined ECUM_UNREACHABLE_CODE_ASSERT_ENABLED)
#error ECUM_UNREACHABLE_CODE_ASSERT_ENABLED is already defined
#endif
/** \brief Unreachable code assertion usage
 **
 ** En- or disables the usage of unreachable code assertion checks */
#define ECUM_UNREACHABLE_CODE_ASSERT_ENABLED STD_OFF

#if (defined ECUM_INVARIANT_ASSERT_ENABLED)
#error ECUM_INVARIANT_ASSERT_ENABLED is already defined
#endif
/** \brief Invariant assertion usage
 **
 ** En- or disables the usage of invariant assertion checks */
#define ECUM_INVARIANT_ASSERT_ENABLED        STD_OFF

#if (defined ECUM_STATIC_ASSERT_ENABLED)
#error ECUM_STATIC_ASSERT_ENABLED is already defined
#endif
/** \brief Static assertion usage
 **
 ** En- or disables the usage of static assertion checks */
#define ECUM_STATIC_ASSERT_ENABLED           STD_OFF


/*==================[type definitions]======================================*/

/* !LINKSTO EcuM4038,1 */
/** \brief Type for EcuM configuration */
typedef struct EcuM_ConfigStruct EcuM_ConfigType;

/* !LINKSTO EcuM2801,1 */
/** \brief Structure definition of EcuM configuration
 *
 * This structure must be defined publically for the public variable
 * declarations later on in this file. */
struct EcuM_ConfigStruct
{
  /** \brief OS Application Mode started by default. **/
  AppModeType DefaultAppMode;

  /* *** Init list related parameters *** */

  P2FUNC(void, ECUM_CODE, DriverInitOne)(P2CONST(
    struct EcuM_ConfigStruct, AUTOMATIC, ECUM_CONST) ConfigPtr);
  P2FUNC(void, ECUM_CODE, DriverRestart)(P2CONST(
    struct EcuM_ConfigStruct, AUTOMATIC, ECUM_CONST) ConfigPtr);

  /* *** Shutdown/Sleep related parameters *** */

  /** \brief State of the default shutdown target. **/
  uint8 DefaultShutdownTarget;

  /** \brief Mode of the default shutdown target (only required if
   * DefaultShutdownState is equal to ECUM_STATE_SLEEP or ECUM_STATE_RESET). **/
  uint8 DefaultMode;
};

/*==================[external function declarations]========================*/
#define ECUM_START_SEC_CODE
#include <MemMap.h>

/** \brief Callout for driver initialization sequence one for EcuM.
 **
 ** This is the configuration specific callout called from
 ** EcuM_AL_DriverInitOne().  This function contains the Initialization
 ** of Modules configured in EcuMDriverInitListOne
 **
 ** \param[in] ConfigPtr Pointer to the EcuM post-build configuration which
 ** contains pointers to all other BSW module post-build configurations. */
extern FUNC(void, ECUM_APPL_CODE) EcuM_DriverInitListOne
(
  P2CONST(EcuM_ConfigType, AUTOMATIC, ECUM_CONST) ConfigPtr
);

/** \brief Callout for restarting drivers for EcuM.
 **
 ** This is the configuration specific callout called from
 ** EcuM_AL_DriverRestart().  This function contains the Initialization
 ** of Modules configured in EcuMDriverRestartList
 **
 ** \param[in] ConfigPtr Pointer to the EcuM post-build configuration which
 ** contains pointers to all other BSW module post-build configurations. */
extern FUNC(void, ECUM_APPL_CODE) EcuM_DriverRestartList
(
  P2CONST(EcuM_ConfigType, AUTOMATIC, ECUM_CONST) ConfigPtr
);



#define ECUM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

#define ECUM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief EcuM configuration for EcuM_Config_0
 **
 ** This EcuM configuration may be be returned by
 ** EcuM_DeterminePbConfiguration().  The name of this element is
 ** configuration dependent. */
extern CONST(EcuM_ConfigType, ECUM_CONST) EcuM_Config_0;
#define ECUM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* if !defined( ECUM_CFG_H ) */
/*==================[end of file]===========================================*/
