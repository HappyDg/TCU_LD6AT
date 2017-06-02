
/**
 * \file
 *
 * \brief AUTOSAR CanTp
 *
 * This file contains the implementation of the AUTOSAR
 * module CanTp.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef CANTP_PBCFG_H
#define CANTP_PBCFG_H

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

#include <CanTp_SymbolicNames_PBcfg.h>
#include <TSAutosar.h>
#include <CanTp_Types_Int.h>
#include <Platform_Types.h>
#include <Compiler.h>
#define TS_RELOCATABLE_CFG_ENABLE STD_ON
#define TS_PB_CFG_PTR_CLASS CANTP_APPL_CONST
#include <TSPBConfig_Types.h>


/*==================[macros]=================================================*/

#if (defined CANTP_CONFIG_NAME) /* To prevent double definition */
#error CANTP_CONFIG_NAME already defined
#endif /* (defined CANTP_CONFIG_NAME) */

#define CANTP_CONFIG_NAME CanTp_ConfigLayout


#if (defined CANTP_PB_CONFIG_NAME) /* To prevent double definition */
#error CANTP_PB_CONFIG_NAME already defined
#endif /* (defined CANTP_PB_CONFIG_NAME) */

#define CANTP_PB_CONFIG_NAME CANTP_CONFIG_NAME


#if (defined CANTP_CONST_CONFIG_LAYOUT_TYPE) /* To prevent double definition */
#error CANTP_CONST_CONFIG_LAYOUT_TYPE already defined
#endif /* (defined CANTP_CONST_CONFIG_LAYOUT_TYPE) */

#define CANTP_CONST_CONFIG_LAYOUT_TYPE CanTp_ConstConfigLayoutType


#if (defined CanTpConfig) /* To prevent double definition */
#error CanTpConfig already defined
#endif /* (defined CanTpConfig) */

#define CanTpConfig (CANTP_CONFIG_NAME.RootCfg)



/*==================[type definitions]=======================================*/

typedef struct /* CanTp_ConfigLayoutType */ {
    VAR( CanTp_ConfigType, TYPEDEF ) RootCfg;
    VAR( CanTp_RxNPduLookupEntryType, TYPEDEF ) RxNPduLookupTable[3];
    VAR( CanTp_RxNPduTableType, TYPEDEF ) RxNPduTable[3];
    VAR( CanTp_RxNSduConfigType, TYPEDEF ) RxNSduConfig[2];
    VAR( CanTp_TxNSduConfigType, TYPEDEF ) TxNSduConfig[1];
    VAR( CanTp_MfCtrConfigType, TYPEDEF ) MfCtrConfig[1];
    VAR( uint8, TYPEDEF ) TxNPduToTpChannel[2];
} CanTp_ConfigLayoutType;

typedef CONST( CanTp_ConfigLayoutType, CANTP_APPL_CONST ) CanTp_ConstConfigLayoutType;


/*==================[external function declarations]=========================*/


/*==================[internal function declarations]=========================*/


/*==================[external constants]=====================================*/

#define CANTP_START_CONFIG_DATA_UNSPECIFIED
#include <MemMap.h>

/** 
CanTp post build config. - Static code accesses this config
 solely via the pointer of type CanTp_ConfigType passed to
 \a CanTp_Init() as parameter.
 */
extern CANTP_CONST_CONFIG_LAYOUT_TYPE CANTP_CONFIG_NAME;

#define CANTP_STOP_CONFIG_DATA_UNSPECIFIED
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

#endif /* CANTP_PBCFG_H */

/*==================[end of file]============================================*/

