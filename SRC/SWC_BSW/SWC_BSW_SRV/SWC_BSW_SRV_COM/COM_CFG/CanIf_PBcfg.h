
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

#ifndef CANIF_PBCFG_H
#define CANIF_PBCFG_H

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

#include <CanIf_SymbolicNames_PBcfg.h>
#include <TSAutosar.h>
#include <CanIf_Types_Int.h>
#include <Platform_Types.h>
#include <Compiler.h>
#define TS_RELOCATABLE_CFG_ENABLE STD_ON
#define TS_PB_CFG_PTR_CLASS CANIF_APPL_CONST
#include <TSPBConfig_Types.h>


/*==================[macros]=================================================*/

#if (defined CANIF_CONFIG_NAME) /* To prevent double definition */
#error CANIF_CONFIG_NAME already defined
#endif /* (defined CANIF_CONFIG_NAME) */

#define CANIF_CONFIG_NAME CanIf_ConfigLayout


#if (defined CANIF_PB_CONFIG_NAME) /* To prevent double definition */
#error CANIF_PB_CONFIG_NAME already defined
#endif /* (defined CANIF_PB_CONFIG_NAME) */

#define CANIF_PB_CONFIG_NAME CANIF_CONFIG_NAME


#if (defined CANIF_CONST_CONFIG_LAYOUT_TYPE) /* To prevent double definition */
#error CANIF_CONST_CONFIG_LAYOUT_TYPE already defined
#endif /* (defined CANIF_CONST_CONFIG_LAYOUT_TYPE) */

#define CANIF_CONST_CONFIG_LAYOUT_TYPE CanIf_ConstConfigLayoutType


#if (defined CanIf_InitCfg_0) /* To prevent double definition */
#error CanIf_InitCfg_0 already defined
#endif /* (defined CanIf_InitCfg_0) */

#define CanIf_InitCfg_0 (CANIF_CONFIG_NAME.RootCfg)



/*==================[type definitions]=======================================*/

typedef struct /* CanIf_ConfigLayoutType */ {
    VAR( CanIf_ConfigType, TYPEDEF ) RootCfg;
    VAR( CanIf_TxLPduConfigType, TYPEDEF ) txLPduConfig[8];
    VAR( CanIf_RxLPduConfigType, TYPEDEF ) rxLPduConfig[10];
    VAR( CanIf_HthConfigType, TYPEDEF ) driverHthConfig[8];
    VAR( CanIf_HrhConfigType, TYPEDEF ) driverHrhConfig[11];
    VAR( uint16, TYPEDEF ) hohIdToCanIfIdx[19];
    VAR( CanIf_CanControllerConfigType, TYPEDEF ) canControllerConfig[3];
    VAR( CanIf_CanDriverConfigType, TYPEDEF ) canDriverConfig[1];
} CanIf_ConfigLayoutType;

typedef CONST( CanIf_ConfigLayoutType, CANIF_APPL_CONST ) CanIf_ConstConfigLayoutType;


/*==================[external function declarations]=========================*/


/*==================[internal function declarations]=========================*/


/*==================[external constants]=====================================*/

#define CANIF_START_CONFIG_DATA_UNSPECIFIED
#include <MemMap.h>

extern CANIF_CONST_CONFIG_LAYOUT_TYPE CANIF_CONFIG_NAME;

#define CANIF_STOP_CONFIG_DATA_UNSPECIFIED
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

#endif /* CANIF_PBCFG_H */

/*==================[end of file]============================================*/

