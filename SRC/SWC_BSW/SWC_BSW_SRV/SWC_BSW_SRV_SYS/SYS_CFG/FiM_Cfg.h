/**
 * \file
 *
 * \brief AUTOSAR FiM
 *
 * This file contains the implementation of the AUTOSAR
 * module FiM.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#if (!defined FIM_CFG_H)
#define FIM_CFG_H

/* This file contains the generated FiM module configuration. */

/*==================[includes]===============================================*/

#include <Std_Types.h>  /* AUTOSAR standard types */

/*==================[macros]=================================================*/

/*------------------[API configuration options]------------------------------*/

/* !LINKSTO FIM033,1 */
#if (defined FIM_VERSION_INFO_API)
#error FIM_VERSION_INFO_API already defined
#endif
/** \brief Switch, indicating if Version Info is activated for FiM */
#define FIM_VERSION_INFO_API         STD_OFF

#if (defined FIM_DEV_ERROR_DETECT)
#error FIM_DEV_ERROR_DETECT already defined
#endif
/** \brief Switch, indicating if the detection of development errors is
 ** activated or deactivated for FiM */
#define FIM_DEV_ERROR_DETECT         STD_OFF

#if (defined FIM_EVENT_UPDATE_TRIGGERED_BY_DEM)
#error FIM_EVENT_UPDATE_TRIGGERED_BY_DEM already defined
#endif
/** \brief Switch, indicating if the Event update triggered by Dem is activated or
 ** deactivated for FiM */
#define FIM_EVENT_UPDATE_TRIGGERED_BY_DEM  STD_OFF

#if (defined FIM_DATA_FIXED)
#error FIM_DATA_FIXED already defined
#endif
/** \brief Switch, indicating if the data is fixed */
#define FIM_DATA_FIXED               STD_ON

#if (defined FIM_INCLUDE_RTE)
#error FIM_INCLUDE_RTE already defined
#endif
/** \brief Switch, indicating if RTE is activated or deactivated for FiM */
#define FIM_INCLUDE_RTE              STD_OFF

#if (defined FIM_MAXIMUM_EVENT_FID_LINKS)
#error FIM_MAXIMUM_EVENT_FID_LINKS already defined
#endif
/** \brief This configuration parameter specifies the total maximum number of
 ** links between EventIds and FIDs. */
#define FIM_MAXIMUM_EVENT_FID_LINKS  65535U

#if (defined FIM_MAXIMUM_FIDS_PER_EVENT)
#error FIM_MAXIMUM_FIDS_PER_EVENT already defined
#endif
/** \brief This configuration parameter specifies the maximum number of FIDs
 ** that can be linked to a single event. */
#define FIM_MAXIMUM_FIDS_PER_EVENT   65535U

#if (defined FIM_MAXIMUM_EVENTS_PER_FID)
#error FIM_MAXIMUM_EVENTS_PER_FID already defined
#endif
/** \brief This configuration parameter specifies the maximum number of
 ** EventIds that can be linked to a single FID. */
#define FIM_MAXIMUM_EVENTS_PER_FID   255U

#if (defined FIM_MAXIMUM_SUMMARY_EVENTS)
#error FIM_MAXIMUM_SUMMARY_EVENTS already defined
#endif
/** \brief This configuration parameter specifies the maximum number of
 ** summarized events that can be configured. */
#define FIM_MAXIMUM_SUMMARY_EVENTS   65535U

#if (defined FIM_MAXIMUM_SUMMARY_LINKS)
#error FIM_MAXIMUM_SUMMARY_LINKS already defined
#endif
/** \brief This configuration parameter specifies the total maximum number of
 ** links between EventIds and summarized events. */
#define FIM_MAXIMUM_SUMMARY_LINKS    65535U

#if (defined FIM_MAXIMUM_TOTAL_LINKS)
#error FIM_MAXIMUM_TOTAL_LINKS already defined
#endif
/** \brief This configuration parameter specifies the total maximum number of
 ** links between EventIds and FIDs plus the number of links between EventIds
 ** and summarized events. */
#define FIM_MAXIMUM_TOTAL_LINKS      65535U

/*------------------[FIDs configuration]-------------------------------------*/

#if (defined FIM_FID_NUM)
#error FIM_FID_NUM already defined
#endif
/** \brief This configuration parameter specifies the total number of FIDs.
 **
 ** Calculated by number of configured FIDs including the invalid FID 0. */
#define FIM_FID_NUM    6U

/* Symbolic names of configured Function IDs */

#if (defined FiMConf_FiMFID_FID_DDVFD_HVLowVoltage)
#error FiMConf_FiMFID_FID_DDVFD_HVLowVoltage already defined
#endif
/** \brief Export symbolic name value */
#define FiMConf_FiMFID_FID_DDVFD_HVLowVoltage           1U

#if (!defined FIM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined FID_DDVFD_HVLowVoltage)
#error FID_DDVFD_HVLowVoltage already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define FID_DDVFD_HVLowVoltage           1U

#if (defined FiM_FID_DDVFD_HVLowVoltage)
#error FiM_FID_DDVFD_HVLowVoltage already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define FiM_FID_DDVFD_HVLowVoltage           1U
#endif /* !defined FIM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

#if (defined FiMConf_FiMFID_FID_DDVFD_HVHighVoltage)
#error FiMConf_FiMFID_FID_DDVFD_HVHighVoltage already defined
#endif
/** \brief Export symbolic name value */
#define FiMConf_FiMFID_FID_DDVFD_HVHighVoltage          2U

#if (!defined FIM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined FID_DDVFD_HVHighVoltage)
#error FID_DDVFD_HVHighVoltage already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define FID_DDVFD_HVHighVoltage          2U

#if (defined FiM_FID_DDVFD_HVHighVoltage)
#error FiM_FID_DDVFD_HVHighVoltage already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define FiM_FID_DDVFD_HVHighVoltage          2U
#endif /* !defined FIM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

#if (defined FiMConf_FiMFID_FID_DDVFD_HVDerating)
#error FiMConf_FiMFID_FID_DDVFD_HVDerating already defined
#endif
/** \brief Export symbolic name value */
#define FiMConf_FiMFID_FID_DDVFD_HVDerating             3U

#if (!defined FIM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined FID_DDVFD_HVDerating)
#error FID_DDVFD_HVDerating already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define FID_DDVFD_HVDerating             3U

#if (defined FiM_FID_DDVFD_HVDerating)
#error FiM_FID_DDVFD_HVDerating already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define FiM_FID_DDVFD_HVDerating             3U
#endif /* !defined FIM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

#if (defined FiMConf_FiMFID_FID_DDVFD_HiOVPPermanentFauSts)
#error FiMConf_FiMFID_FID_DDVFD_HiOVPPermanentFauSts already defined
#endif
/** \brief Export symbolic name value */
#define FiMConf_FiMFID_FID_DDVFD_HiOVPPermanentFauSts   4U

#if (!defined FIM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined FID_DDVFD_HiOVPPermanentFauSts)
#error FID_DDVFD_HiOVPPermanentFauSts already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define FID_DDVFD_HiOVPPermanentFauSts   4U

#if (defined FiM_FID_DDVFD_HiOVPPermanentFauSts)
#error FiM_FID_DDVFD_HiOVPPermanentFauSts already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define FiM_FID_DDVFD_HiOVPPermanentFauSts   4U
#endif /* !defined FIM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

#if (defined FiMConf_FiMFID_FID_DDVFD_HiUVPPermanentFauSts)
#error FiMConf_FiMFID_FID_DDVFD_HiUVPPermanentFauSts already defined
#endif
/** \brief Export symbolic name value */
#define FiMConf_FiMFID_FID_DDVFD_HiUVPPermanentFauSts   5U

#if (!defined FIM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined FID_DDVFD_HiUVPPermanentFauSts)
#error FID_DDVFD_HiUVPPermanentFauSts already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define FID_DDVFD_HiUVPPermanentFauSts   5U

#if (defined FiM_FID_DDVFD_HiUVPPermanentFauSts)
#error FiM_FID_DDVFD_HiUVPPermanentFauSts already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define FiM_FID_DDVFD_HiUVPPermanentFauSts   5U
#endif /* !defined FIM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */


#if (defined FIM_MAX_DEM_EVENT_ID)
#error FIM_MAX_DEM_EVENT_ID already defined
#endif
/** \brief This configuration parameter specifies the largest event Id
 ** configured in Dem. */
#define FIM_MAX_DEM_EVENT_ID  4U

/*------------------[Event summaries configuration]----------------------------*/

/* Symbolic names of configured Event Summary IDs - not relevant to this implementation */

#if (defined FiMConf_FiMSummaryEventId_EVENT_SUMMARY_DDVFD_HVDerating)
#error FiMConf_FiMSummaryEventId_EVENT_SUMMARY_DDVFD_HVDerating already defined
#endif
/** \brief Export symbolic name value */
#define FiMConf_FiMSummaryEventId_EVENT_SUMMARY_DDVFD_HVDerating   0U

#if (!defined FIM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined EVENT_SUMMARY_DDVFD_HVDerating)
#error EVENT_SUMMARY_DDVFD_HVDerating already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define EVENT_SUMMARY_DDVFD_HVDerating   0U

#if (defined FiM_EVENT_SUMMARY_DDVFD_HVDerating)
#error FiM_EVENT_SUMMARY_DDVFD_HVDerating already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define FiM_EVENT_SUMMARY_DDVFD_HVDerating   0U
#endif /* !defined FIM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

/*==================[type definitions]=======================================*/

/*------------------[FiM_ConfigType]----------------------------------------*/

/** \brief This type defines a data structure for the post build
 ** parameters of the FiM
 **
 ** \note Type is unused, as only pre-compile time support is implemented. */
typedef uint8 FiM_ConfigType;

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

#define FIM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief Configuration structure */
extern CONST(FiM_ConfigType, FIM_CONST) FiM_Config_0;

#define FIM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

#endif /* if !defined( FIM_CFG_H ) */
/*==================[end of file]============================================*/
