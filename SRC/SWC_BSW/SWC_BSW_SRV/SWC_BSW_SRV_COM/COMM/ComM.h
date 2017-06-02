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
#if (!defined COMM_H)
#define COMM_H

/*==================[inclusions]============================================*/

/* !LINKSTO ComM956,1 */
#include <ComM_Types.h>                                /* ComM's common API */
/* !LINKSTO ComM280,1 */
#include <ComM_BSW.h>                                  /* ComM's common API */

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/


/* hide declaration in own header if included by ComM itself and RTE is
 * enabled */
#if ((!defined(COMM_INTERNAL_USAGE)) || (COMM_INCLUDE_RTE == STD_OFF))

#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON) || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))

/**
 * Wrapping macro for ComM_GetInhibitionStatus to provide AUTOSAR 4.0 API as
 * default to other BSW modules
 */
#define ComM_GetInhibitionStatus ComM_ASR40_GetInhibitionStatus

#endif

/**
 * Wrapping macro for ComM_RequestComMode to provide AUTOSAR 4.0 API as
 * default to other BSW modules
 */
#define ComM_RequestComMode ComM_ASR40_RequestComMode

/**
 * Wrapping macro for ComM_GetMaxComMode to provide AUTOSAR 4.0 API as
 * default to other BSW modules
 */
#define ComM_GetMaxComMode ComM_ASR40_GetMaxComMode

/**
 * Wrapping macro for ComM_GetRequestedComMode to provide AUTOSAR 4.0 API as
 * default to other BSW modules
 */
#define ComM_GetRequestedComMode ComM_ASR40_GetRequestedComMode

/**
 * Wrapping macro for ComM_GetCurrentComMode to provide AUTOSAR 4.0 API as
 * default to other BSW modules
 */
#define ComM_GetCurrentComMode ComM_ASR40_GetCurrentComMode


#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
/**
 * Wrapping macro for ComM_PreventWakeUp to provide AUTOSAR 4.0 API as
 * default to other BSW modules
 */
#define ComM_PreventWakeUp ComM_ASR40_PreventWakeUp

#endif

#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
/**
 * Wrapping macro for ComM_LimitChannelToNoComMode to provide AUTOSAR 4.0 API as
 * default to other BSW modules
 */
#define ComM_LimitChannelToNoComMode ComM_ASR40_LimitChannelToNoComMode

#endif

#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
/**
 * Wrapping macro for ComM_LimitECUToNoComMode to provide AUTOSAR 4.0 API as
 * default to other BSW modules
 */
#define ComM_LimitECUToNoComMode ComM_ASR40_LimitECUToNoComMode

#endif

#if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) || (COMM_MODE_LIMITATION_ENABLED == STD_ON))
/**
 * Wrapping macro for ComM_ReadInhibitCounter to provide AUTOSAR 4.0 API as
 * default to other BSW modules
 */
#define ComM_ReadInhibitCounter ComM_ASR40_ReadInhibitCounter

/**
 * Wrapping macro for ComM_ResetInhibitCounter to provide AUTOSAR 4.0 API as
 * default to other BSW modules
 */
#define ComM_ResetInhibitCounter ComM_ASR40_ResetInhibitCounter

/**
 * Wrapping macro for ComM_SetECUGroupClassification to provide AUTOSAR 4.0 API as
 * default to other BSW modules
 */
#define ComM_SetECUGroupClassification ComM_ASR40_SetECUGroupClassification

#endif

#endif /* ((!defined(COMM_INTERNAL_USAGE)) || (COMM_INCLUDE_RTE == STD_OFF)) */

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* if !defined( COMM_H ) */
/*==================[end of file]===========================================*/
