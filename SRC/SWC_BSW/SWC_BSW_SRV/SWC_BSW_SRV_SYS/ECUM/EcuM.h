#if (!defined ECUM_H)
#define ECUM_H

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

#include <EcuM_Types.h>         /* EcuM's common module types */
#include <EcuM_BSW.h>           /* EcuM's common API and configuration */

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/* !LINKSTO EcuM.EB.ASR32.EcuM100,1 */
/**
 * \brief Wrapping macro for EcuM_SelectShutdownTarget
 *
 * Provides an AUTOSAR 4.0 API as default to other BSW modules.
 */
#define EcuM_SelectShutdownTarget EcuM_ASR40_SelectShutdownTarget

/* !LINKSTO EcuM.EB.ASR32.EcuM100,1 */
/**
 * \brief Wrapping macro for EcuM_GetShutdownTarget
 *
 * Provides an AUTOSAR 4.0 API as default to other BSW modules.
 */
#define EcuM_GetShutdownTarget EcuM_ASR40_GetShutdownTarget

/* !LINKSTO EcuM.EB.ASR32.EcuM100,1 */
/**
 * \brief Wrapping macro for EcuM_GetLastShutdownTarget
 *
 * Provides an AUTOSAR 4.0 API as default to other BSW modules.
 */
#define EcuM_GetLastShutdownTarget EcuM_ASR40_GetLastShutdownTarget

/* !LINKSTO EcuM.EB.ASR32.EcuM100,1 */
/**
 * \brief Wrapping macro for EcuM_SelectShutdownCause
 *
 * Provides an AUTOSAR 4.0 API as default to other BSW modules.
 */
#define EcuM_SelectShutdownCause EcuM_ASR40_SelectShutdownCause

/* !LINKSTO EcuM.EB.ASR32.EcuM100,1 */
/**
 * \brief Wrapping macro for EcuM_GetShutdownCause
 *
 * Provides an AUTOSAR 4.0 API as default to other BSW modules.
 */
#define EcuM_GetShutdownCause EcuM_ASR40_GetShutdownCause

/* !LINKSTO EcuM.EB.ASR32.EcuM100,1 */
/**
 * \brief Wrapping macro for EcuM_GetMostRecentShutdown
 *
 * Provides an AUTOSAR 4.0 API as default to other BSW modules.
 */
#define EcuM_GetMostRecentShutdown EcuM_ASR40_GetMostRecentShutdown

/* !LINKSTO EcuM.EB.ASR32.EcuM100,1 */
/**
 * \brief Wrapping macro for EcuM_GetNextRecentShutdown
 *
 * Provides an AUTOSAR 4.0 API as default to other BSW modules.
 */
#define EcuM_GetNextRecentShutdown EcuM_ASR40_GetNextRecentShutdown

/* !LINKSTO EcuM.EB.ASR32.EcuM100,1 */
/**
 * \brief Wrapping macro for EcuM_SelectBootTarget
 *
 * Provides an AUTOSAR 4.0 API as default to other BSW modules.
 */
#define EcuM_SelectBootTarget EcuM_ASR40_SelectBootTarget

/* !LINKSTO EcuM.EB.ASR32.EcuM100,1 */
/**
 * \brief Wrapping macro for EcuM_GetBootTarget
 *
 * Provides an AUTOSAR 4.0 API as default to other BSW modules.
 */
#define EcuM_GetBootTarget EcuM_ASR40_GetBootTarget

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/
#endif /* if !defined( ECUM_H ) */
