/**
 * \file
 *
 * \brief AUTOSAR PduR
 *
 * This file contains the implementation of the AUTOSAR
 * module PduR.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#if (!defined PDUR_H)
#define PDUR_H

/*
 *  MISRA-1) Deviated Rule: 19.6 (required)
 *   '#undef' shall not be used.
 *
 *  Reason:
 *  The macros PDUR_NO_PBCFG_REQUIRED, PDUR_NO_CFG_REQUIRED
 *  are used for optimized compilation time of the modules using the PduR module.
 *  To avoid that this macro is used by other modules accidentally
 *  a #undef is used here.
 *
 */

/*==================[inclusions]============================================*/

#include <TSAutosar.h>     /* EB specific standard types */
#include <PduR_Api.h>      /* Module public API */

/* Exclude post-build-time configuration include file if requested to do so */
#if (!defined PDUR_NO_PBCFG_REQUIRED) && (!defined PDUR_NO_CFG_REQUIRED)
#if (PDUR_PBCFGM_SUPPORT_ENABLED == STD_OFF)
#include <PduR_PBcfg.h>    /* get name of PduR post build configuration */
#endif /* PDUR_PBCFGM_SUPPORT_ENABLED == STD_OFF */
#endif /* PDUR_NO_PBCFG_REQUIRED */

/* Deviation MISRA-1 */
#undef PDUR_NO_PBCFG_REQUIRED
/* Deviation MISRA-1 */
#undef PDUR_NO_CFG_REQUIRED
/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* if !defined( PDUR_H ) */
/*==================[end of file]===========================================*/
