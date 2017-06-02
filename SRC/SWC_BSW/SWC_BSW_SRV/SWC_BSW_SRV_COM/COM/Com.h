/**
 * \file
 *
 * \brief AUTOSAR Com
 *
 * This file contains the implementation of the AUTOSAR
 * module Com.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/* MISRA-C:2004 Deviations:
 *
 * MISRA-1: Deviated Rule: 19.6 (required)
 * "#undef' shall not be used"
 *
 * Reason:
 * The macros COM_NO_PBCFG_REQUIRED, COM_NO_CFG_REQUIRED
 * are used for optimized compilation time of the modules using the Com module.
 * To avoid that this macro is used by other modules accidentally
 * a undef is used here.
 *
 */

#if (!defined COM_H)
#define COM_H
/*==================[inclusions]============================================*/


#include <TSAutosar.h>          /* EB specific standard types */
#include <Com_Api.h>            /* Module public API */
#include <Com_Version.h>        /* Module version declarations */

#include <Com_GenApi_Static.h>

/* Exclude post-build-time config include file if requested to do so */
#if (!defined COM_NO_PBCFG_REQUIRED) && (!defined COM_NO_CFG_REQUIRED)
#if (COM_PBCFGM_SUPPORT_ENABLED == STD_OFF)
/* Exclude post-build-time config include file if PbcfgM support is enabled */
#include <Com_PBcfg.h>
#endif /* (COM_PBCFGM_SUPPORT_ENABLED == STD_OFF) */
#include <Com_GenApi.h>
#endif /* (!defined COM_NO_PBCFG_REQUIRED) && (!defined COM_NO_CFG_REQUIRED) */

/* Deviation MISRA-4 */
#undef COM_NO_PBCFG_REQUIRED
/* Deviation MISRA-4 */
#undef COM_NO_CFG_REQUIRED


/*==================[version check]=========================================*/

/*==================[macros]================================================*/

/*==================[macro checks]==========================================*/


/* check for defined STD_ON macro value */
#if !defined STD_ON
#error STD_ON not defined
#endif /* STD_ON */


/* check for defined STD_OFF macro value */
#if !defined STD_OFF
#error STD_OFF not defined
#endif /* STD_OFF */

/* check for correctly defined switch COM_VERSION_INFO_API */
#if !defined COM_VERSION_INFO_API
#error macro COM_VERSION_INFO_API not defined
#endif /* COM_VERSION_INFO_API */

/* test for valid value of COM_VERSION_INFO_API */
#if (COM_VERSION_INFO_API != STD_ON) && \
    (COM_VERSION_INFO_API != STD_OFF)
#error macro COM_VERSION_INFO_API has an invalid value
#endif /* COM_VERSION_INFO_API */

/* check for correctly defined switch COM_DEV_ERROR_DETECT */
#if !defined COM_DEV_ERROR_DETECT
#error macro COM_DEV_ERROR_DETECT not defined
#endif /* COM_DEV_ERROR_DETECT */

/* test for valid value of COM_DEV_ERROR_DETECT */
#if (COM_DEV_ERROR_DETECT != STD_ON) && \
    (COM_DEV_ERROR_DETECT != STD_OFF)
#error macro COM_DEV_ERROR_DETECT has an invalid value
#endif /* COM_DEV_ERROR_DETECT */

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* if !defined( COM_H ) */
/*==================[end of file]===========================================*/
