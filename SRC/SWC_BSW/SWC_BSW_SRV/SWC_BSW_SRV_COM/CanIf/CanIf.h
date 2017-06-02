/**
 * \file
 *
 * \brief AUTOSAR CanIf
 *
 * This file contains the implementation of the AUTOSAR
 * module CanIf.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#if (!defined CANIF_H)
#define CANIF_H

/*
 * Misra-C:2004 Deviations:
 *
 * MISRA-1) Deviated Rule: 19.6 (required)
 * '#undef' shall not be used.
 *
 * Reason:
 * AUTOSAR requires to include all headerfiles via CanIf.h.
 * Anyway, this is not very clever as it increases include dependencies.
 * Local definition of macros can break this dependency. In order to avoid global
 * influence those macros must be undef'ed.
 */

 /*==================[inclusions]=============================================*/

/* NOTE: this if-clause is only possible if the <MODULENAME>_H itself doesn't depend on the PreCompile configuration! */
#if !defined CANIF_NO_CFG_REQUIRED
/* Always include pre-compile-time information - needed by own and foreign modules */
/* don't mix PBcfg or Lcfg symbolic name values into Cfg since those headerfiles are included anyway right afterwards */
#define CANIF_NO_CFGCLASSMIX_REQUIRED
#include <CanIf_Cfg.h>              /* pre-compile-time configuration */
#endif /* CANIF_NO_CFG_REQUIRED */

/* Exclude post-build-time config include file if requested to do so */
#if (!defined CANIF_NO_PBCFG_REQUIRED) && (!defined CANIF_NO_CFG_REQUIRED)
#if (CANIF_PBCFGM_SUPPORT_ENABLED == STD_OFF)
#include <CanIf_PBcfg.h>
#endif /* CANIF_PBCFGM_SUPPORT_ENABLED == STD_OFF */
#endif /* CANIF_NO_PBCFG_REQUIRED */


/* Deviation MISRA-1 */
#undef CANIF_NO_LCFG_REQUIRED
/* Deviation MISRA-1 */
#undef CANIF_NO_PBCFG_REQUIRED
/* Deviation MISRA-1 */
#undef CANIF_NO_CFG_REQUIRED

#include <CanIf_Api.h>        /* CanIf type definitions */

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

#endif /* if !defined( CANIF_H ) */
/*==================[end of file]============================================*/
