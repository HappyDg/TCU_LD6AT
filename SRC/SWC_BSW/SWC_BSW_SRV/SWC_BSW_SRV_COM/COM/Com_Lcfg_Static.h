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
 * MISRA-1) Deviated Rule: 8.12 (required)
 * "When an array is declared with external linkage, its
 * size shall be stated explicitely or defined implicitely by initialisation."
 *
 * Reason:
 * Size of array is defined during configuration (link-time configuration) and
 * therefore not known
 *
 */

#ifndef COM_LCFG_STATIC_H_
#define COM_LCFG_STATIC_H_

/*==================[inclusions]============================================*/

#include <TSAutosar.h>          /* EB specific standard types */
#include <Com_Cfg.h>            /* get module interface */
#include <Com_Cbk.h>             /* callback types */
#include <Com_Callout.h>             /* callback types */

/*==================[version check]=========================================*/

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

#define COM_START_CONFIG_DATA_UNSPECIFIED
#include <MemMap.h>


#if (COM_CALL_OUT_FUNC_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE)
/* Deviation MISRA-1 */
extern CONSTP2VAR(Com_TxCalloutType, AUTOMATIC, COM_APPL_CODE) Com_TxCallouts[];
/* Deviation MISRA-1 */
extern CONSTP2VAR(Com_RxCalloutType, AUTOMATIC, COM_APPL_CODE) Com_RxCallouts[];
#endif /* (COM_CALL_OUT_FUNC_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

#if (COM_CBK_TX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE)
/* Deviation MISRA-1 */
extern CONSTP2VAR(Com_CbkTxAck_Type, AUTOMATIC, COM_RTE_CODE) Com_CbkTxAck_Array[];
#endif /* (COM_CBK_TX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

#if (COM_CBK_TX_ERR_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE)
/* Deviation MISRA-1 */
extern CONSTP2VAR(Com_CbkTxErr_Type, AUTOMATIC, COM_RTE_CODE) Com_CbkTxErr_Array[];
#endif /* (COM_CBK_TX_ERR_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

#if (COM_CBK_TX_T_OUT_ARRAY_SIZE_MAX != COM_INDEX_NONE)
/* Deviation MISRA-1 */
extern CONSTP2VAR(Com_CbkTxTOut_Type, AUTOMATIC, COM_RTE_CODE)Com_CbkTxTOut_Array[];
#endif /* (COM_CBK_TX_T_OUT_ARRAY_SIZE_MAX != COM_INDEX_NONE) */


#if (COM_CBK_RX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE)
/* Deviation MISRA-1 */
extern CONSTP2VAR(Com_CbkRxAck_Type, AUTOMATIC, COM_RTE_CODE) Com_CbkRxAck_Array[];
#endif /* (COM_CBK_RX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) */


#if (COM_CBK_RX_T_OUT_ARRAY_SIZE_MAX != COM_INDEX_NONE)
/* Deviation MISRA-1 */
extern CONSTP2VAR(Com_CbkRxTOut_Type, AUTOMATIC, COM_RTE_CODE)Com_CbkRxTOut_Array[];
#endif /* (COM_CBK_RX_T_OUT_ARRAY_SIZE_MAX != COM_INDEX_NONE) */


#define COM_STOP_CONFIG_DATA_UNSPECIFIED
#include <MemMap.h>


/* start data section declaration */
#define COM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/**
 * Pointer to statically allocated RAM.
 */
extern CONSTP2VAR(uint8, COM_CONST, COM_VAR_NOINIT) Com_gDataMemPtr;

/* stop data section declaration */
#define COM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>



/* start data section declaration */
#define COM_START_SEC_CONST_32
#include <MemMap.h>

/**
 * Variable holding link-time configuration
 */
extern CONST(uint32, COM_CONST) Com_LcfgSignature;

/* stop data section declaration */
#define COM_STOP_SEC_CONST_32
#include <MemMap.h>



/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/


#endif /*COM_LCFG_STATIC_H_ */
