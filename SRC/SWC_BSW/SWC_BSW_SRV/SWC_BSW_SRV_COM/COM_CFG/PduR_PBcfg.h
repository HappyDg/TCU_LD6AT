
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

#ifndef PDUR_PBCFG_H
#define PDUR_PBCFG_H

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

#include <PduR_SymbolicNames_PBcfg.h>
#include <TSAutosar.h>
#include <PduR_CfgTypes.h>
#include <Compiler.h>
#define TS_RELOCATABLE_CFG_ENABLE STD_OFF
#define TS_PB_CFG_PTR_CLASS PDUR_APPL_CONST
#include <TSPBConfig_Types.h>


/*==================[macros]=================================================*/

#if (defined PDUR_CONFIG_NAME) /* To prevent double definition */
#error PDUR_CONFIG_NAME already defined
#endif /* (defined PDUR_CONFIG_NAME) */

#define PDUR_CONFIG_NAME PduR_Configuration


#if (defined PDUR_PB_CONFIG_NAME) /* To prevent double definition */
#error PDUR_PB_CONFIG_NAME already defined
#endif /* (defined PDUR_PB_CONFIG_NAME) */

#define PDUR_PB_CONFIG_NAME PDUR_CONFIG_NAME


#if (defined PDUR_CONST_CONFIG_LAYOUT_TYPE) /* To prevent double definition */
#error PDUR_CONST_CONFIG_LAYOUT_TYPE already defined
#endif /* (defined PDUR_CONST_CONFIG_LAYOUT_TYPE) */

#define PDUR_CONST_CONFIG_LAYOUT_TYPE VAR( PduR_ConstConfigLayoutType, PDUR_APPL_CONST )


#if (defined PduRRoutingTables) /* To prevent double definition */
#error PduRRoutingTables already defined
#endif /* (defined PduRRoutingTables) */

#define PduRRoutingTables (PDUR_CONFIG_NAME.PduR_RootConfig)



/*==================[type definitions]=======================================*/

typedef struct /* PduR_ConfigLayoutType */ {
    CONST( PduR_PBConfigType, TYPEDEF ) PduR_RootConfig;
    VAR( PduR_RTabLoIfType, TYPEDEF ) PduR_RTabLoIfRx[7];
    VAR( PduR_RTabLoIfType, TYPEDEF ) PduR_RTabLoIfTx[2];
    VAR( PduR_RTabUpIfTxType, TYPEDEF ) PduR_RTabUpIfTx[2];
    VAR( PduR_RTabLoTpType, TYPEDEF ) PduR_RTabLoTpRx[2];
    VAR( PduR_RTabLoTpType, TYPEDEF ) PduR_RTabLoTpTx[1];
    VAR( PduR_RTabUpTpType, TYPEDEF ) PduR_RTabUpTpTx[1];
} PduR_ConfigLayoutType;

typedef CONST( PduR_ConfigLayoutType, TYPEDEF ) PduR_ConstConfigLayoutType;


/*==================[external function declarations]=========================*/


/*==================[internal function declarations]=========================*/


/*==================[external constants]=====================================*/

#define PDUR_START_CONFIG_DATA_UNSPECIFIED
#include <MemMap.h>

extern PDUR_CONST_CONFIG_LAYOUT_TYPE PDUR_CONFIG_NAME;

#define PDUR_STOP_CONFIG_DATA_UNSPECIFIED
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

#endif /* PDUR_PBCFG_H */

/*==================[end of file]============================================*/

