/**
 * \file
 *
 * \brief AUTOSAR Dem
 *
 * This file contains the implementation of the AUTOSAR
 * module Dem.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#if (!defined DEM_INT_EVT_ID_H)
#define DEM_INT_EVT_ID_H

/* This file contains the configuration declarations of the
 * SW-C Event ID symbols for AUTOSAR module Dem. */


/*==================[inclusions]============================================*/

/*==================[macros]================================================*/

/*------------------[Events configuration]----------------------------------*/

/* Symbolic names of configured SW-C event IDs */

#if (defined DemConf_DemEventParameter_APPL_E_DDVFD_HVLowVoltage)
#error DemConf_DemEventParameter_APPL_E_DDVFD_HVLowVoltage already defined
#endif
/** \brief Export symbolic name value */
#define DemConf_DemEventParameter_APPL_E_DDVFD_HVLowVoltage       1U

#if (!defined DEM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined APPL_E_DDVFD_HVLowVoltage)
#error APPL_E_DDVFD_HVLowVoltage already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define APPL_E_DDVFD_HVLowVoltage       1U

#if (defined Dem_APPL_E_DDVFD_HVLowVoltage)
#error Dem_APPL_E_DDVFD_HVLowVoltage already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) **/
#define Dem_APPL_E_DDVFD_HVLowVoltage       1U
#endif /* !defined DEM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

#if (defined DemConf_DemEventParameter_APPL_E_DDVFD_HVHighVoltage)
#error DemConf_DemEventParameter_APPL_E_DDVFD_HVHighVoltage already defined
#endif
/** \brief Export symbolic name value */
#define DemConf_DemEventParameter_APPL_E_DDVFD_HVHighVoltage      2U

#if (!defined DEM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined APPL_E_DDVFD_HVHighVoltage)
#error APPL_E_DDVFD_HVHighVoltage already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define APPL_E_DDVFD_HVHighVoltage      2U

#if (defined Dem_APPL_E_DDVFD_HVHighVoltage)
#error Dem_APPL_E_DDVFD_HVHighVoltage already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) **/
#define Dem_APPL_E_DDVFD_HVHighVoltage      2U
#endif /* !defined DEM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

#if (defined DemConf_DemEventParameter_APPL_E_DDVFD_HiOVPPermanentFauSts)
#error DemConf_DemEventParameter_APPL_E_DDVFD_HiOVPPermanentFauSts already defined
#endif
/** \brief Export symbolic name value */
#define DemConf_DemEventParameter_APPL_E_DDVFD_HiOVPPermanentFauSts 3U

#if (!defined DEM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined APPL_E_DDVFD_HiOVPPermanentFauSts)
#error APPL_E_DDVFD_HiOVPPermanentFauSts already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define APPL_E_DDVFD_HiOVPPermanentFauSts 3U

#if (defined Dem_APPL_E_DDVFD_HiOVPPermanentFauSts)
#error Dem_APPL_E_DDVFD_HiOVPPermanentFauSts already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) **/
#define Dem_APPL_E_DDVFD_HiOVPPermanentFauSts 3U
#endif /* !defined DEM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

#if (defined DemConf_DemEventParameter_APPL_E_DDVFD_HiUVPPermanentFauSts)
#error DemConf_DemEventParameter_APPL_E_DDVFD_HiUVPPermanentFauSts already defined
#endif
/** \brief Export symbolic name value */
#define DemConf_DemEventParameter_APPL_E_DDVFD_HiUVPPermanentFauSts 4U

#if (!defined DEM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined APPL_E_DDVFD_HiUVPPermanentFauSts)
#error APPL_E_DDVFD_HiUVPPermanentFauSts already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define APPL_E_DDVFD_HiUVPPermanentFauSts 4U

#if (defined Dem_APPL_E_DDVFD_HiUVPPermanentFauSts)
#error Dem_APPL_E_DDVFD_HiUVPPermanentFauSts already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) **/
#define Dem_APPL_E_DDVFD_HiUVPPermanentFauSts 4U
#endif /* !defined DEM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* if !defined( DEM_INT_EVT_ID_H ) */
/*==================[end of file]===========================================*/
