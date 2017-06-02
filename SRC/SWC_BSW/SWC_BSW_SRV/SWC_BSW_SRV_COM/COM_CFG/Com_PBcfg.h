
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

#ifndef COM_PBCFG_H
#define COM_PBCFG_H

/* MISRA-C:2004 Deviations
 *
 * MISRA-1) Deviated Rule: 19.6 (required)
 * "'#undef' shall not be used"
 *
 * Reason:
 * The macros TS_RELOCATABLE_CFG_ENABLE and TS_PB_CFG_PTR_CLASS might also be
 * used by other modules. To avoid that these macros are accidentally used
 * by other modules an undef is used here.
 *
 */

/*==================[inclusions]=============================================*/

#include <Com_SymbolicNames_PBcfg.h>
#include <TSAutosar.h>
#include <Com_Types.h>
#include <Platform_Types.h>
#include <Compiler.h>
#define TS_RELOCATABLE_CFG_ENABLE STD_ON
#define TS_PB_CFG_PTR_CLASS COM_APPL_CONST
#include <TSPBConfig_Types.h>


/*==================[macros]=================================================*/

#if (defined COM_CONFIG_NAME) /* To prevent double definition */
#error COM_CONFIG_NAME already defined
#endif /* (defined COM_CONFIG_NAME) */

#define COM_CONFIG_NAME Com_Configuration


#if (defined COM_PB_CONFIG_NAME) /* To prevent double definition */
#error COM_PB_CONFIG_NAME already defined
#endif /* (defined COM_PB_CONFIG_NAME) */

#define COM_PB_CONFIG_NAME COM_CONFIG_NAME


#if (defined COM_CONST_CONFIG_LAYOUT_TYPE) /* To prevent double definition */
#error COM_CONST_CONFIG_LAYOUT_TYPE already defined
#endif /* (defined COM_CONST_CONFIG_LAYOUT_TYPE) */

#define COM_CONST_CONFIG_LAYOUT_TYPE VAR( Com_ConstConfigLayoutType, COM_APPL_CONST )


#if (defined ComConfig) /* To prevent double definition */
#error ComConfig already defined
#endif /* (defined ComConfig) */

#define ComConfig (COM_CONFIG_NAME.Com_RootConfig)



/*==================[type definitions]=======================================*/

typedef struct /* Com_ConfigLayoutType */ {
    VAR( Com_ConfigType, TYPEDEF ) Com_RootConfig;
    VAR( ComRxIPduType, TYPEDEF ) ComRxIPdu[7];
    VAR( ComTxIPduType, TYPEDEF ) ComTxIPdu[2];
    VAR( ComTxIPduMinimumDelayTimeFactorType, TYPEDEF ) ComTxIPduMinimumDelayTimeFactor[1];
    VAR( ComTxModePeriodicType, TYPEDEF ) ComTxModePeriodic[1];
    VAR( ComSignalRefType, TYPEDEF ) ComRxIPduSignalList[34];
    VAR( ComSignalRefType, TYPEDEF ) ComTxIPduSignalList[16];
    VAR( ComRxFirstTimeoutFactorType, TYPEDEF ) ComRxFirstTimeoutFactorList[2];
    VAR( ComRxTimeoutFactorType, TYPEDEF ) ComRxTimeoutFactorList[2];
    VAR( ComRxSignalType, TYPEDEF ) ComRxSignal[34];
    VAR( ComTxSignalType, TYPEDEF ) ComTxSignal[16];
    VAR( Com_CbkRxTOutIdxType, TYPEDEF ) ComRxTimeoutNotificationList[7];
    VAR( ComIPduRefType, TYPEDEF ) ComPeriodicQueueList[2];
    VAR( ComIPduRefType, TYPEDEF ) ComRxTimeoutQueueList[7];
    VAR( ComIPduRefType, TYPEDEF ) ComCbkTxAckDeferredList[2];
    VAR( ComIPduGroupMaskType, TYPEDEF ) ComIPduGroupMask[2];
    VAR( uint8, TYPEDEF ) ComIPduInit[8];
} Com_ConfigLayoutType;

typedef CONST( Com_ConfigLayoutType, TYPEDEF ) Com_ConstConfigLayoutType;


/*==================[external function declarations]=========================*/


/*==================[internal function declarations]=========================*/


/*==================[external constants]=====================================*/

#define COM_START_CONFIG_DATA_UNSPECIFIED
#include <MemMap.h>

extern COM_CONST_CONFIG_LAYOUT_TYPE COM_CONFIG_NAME;

#define COM_STOP_CONFIG_DATA_UNSPECIFIED
#include <MemMap.h>


/*==================[internal constants]=====================================*/


/*==================[external data]==========================================*/


/*==================[internal data]==========================================*/


/*==================[external function definitions]==========================*/


/*==================[internal function definitions]==========================*/


/* Deviation MISRA-1 */
#undef TS_RELOCATABLE_CFG_ENABLE
/* Deviation MISRA-1 */
#undef TS_PB_CFG_PTR_CLASS

#endif /* COM_PBCFG_H */

/*==================[end of file]============================================*/

