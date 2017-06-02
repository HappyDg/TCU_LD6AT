
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

#ifndef CANTP_TYPES_INT_H
#define CANTP_TYPES_INT_H

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

#include <Platform_Types.h>
#include <ComStack_Cfg.h>
#include <TSAutosar.h>
#define TS_RELOCATABLE_CFG_ENABLE STD_ON
#define TS_PB_CFG_PTR_CLASS CANTP_APPL_CONST
#include <TSPBConfig_Types.h>


/*==================[macros]=================================================*/


/*==================[type definitions]=======================================*/

/** 
Type for the N-PDU Lookup Table.
 */
typedef VAR( uint16, TYPEDEF ) CanTp_RxNPduLookupEntryType;

typedef struct /* CanTp_MfCtrConfigType */ {
    VAR( uint32, TYPEDEF ) Resolution;
    VAR( uint8, TYPEDEF ) CallbackType;
} CanTp_MfCtrConfigType;

typedef struct /* CanTp_RxNPduTableType */ {
    VAR( PduIdType, TYPEDEF ) Index;
    VAR( uint16, TYPEDEF ) Next;
    VAR( uint8, TYPEDEF ) AddressingFormat;
    VAR( uint8, TYPEDEF ) N_SA_AE;
    VAR( uint8, TYPEDEF ) Direction;
} CanTp_RxNPduTableType;

typedef struct /* CanTp_RxNSduConfigType */ {
    VAR( PduIdType, TYPEDEF ) NPduConfIdFc;
    VAR( PduIdType, TYPEDEF ) LSduIdFc;
    VAR( PduIdType, TYPEDEF ) IPduId;
    VAR( PduIdType, TYPEDEF ) NPduIdxF;
    VAR( uint16, TYPEDEF ) N_Ar;
    VAR( uint16, TYPEDEF ) N_Br;
    VAR( uint16, TYPEDEF ) N_Cr;
    VAR( uint8, TYPEDEF ) AddressingFormat;
    VAR( uint8, TYPEDEF ) Tatype;
    VAR( uint8, TYPEDEF ) PaddingActivation;
    VAR( uint8, TYPEDEF ) N_TA_AE;
    VAR( uint8, TYPEDEF ) WftMax;
    VAR( uint8, TYPEDEF ) BS;
    VAR( uint8, TYPEDEF ) Channel;
    VAR( uint8, TYPEDEF ) ChannelMode;
    VAR( uint8, TYPEDEF ) STmin;
} CanTp_RxNSduConfigType;

typedef struct /* CanTp_TxNSduConfigType */ {
    VAR( PduIdType, TYPEDEF ) NPduIdFc;
    VAR( PduIdType, TYPEDEF ) NPduConfIdxF;
    VAR( PduIdType, TYPEDEF ) LSduIdxF;
    VAR( PduIdType, TYPEDEF ) IPduConfId;
    VAR( uint16, TYPEDEF ) N_As;
    VAR( uint16, TYPEDEF ) N_Bs;
    VAR( uint16, TYPEDEF ) N_Cs;
    VAR( uint8, TYPEDEF ) AddressingFormat;
    VAR( uint8, TYPEDEF ) Tatype;
    VAR( uint8, TYPEDEF ) PaddingActivation;
    VAR( uint8, TYPEDEF ) N_TA_AE;
    VAR( uint8, TYPEDEF ) Channel;
    VAR( uint8, TYPEDEF ) ChannelMode;
    VAR( boolean, TYPEDEF ) CanTpTc;
} CanTp_TxNSduConfigType;

typedef struct /* CanTp_ConfigType */ {
    VAR( uint32, TYPEDEF ) PlatformSignature;
    VAR( uint32, TYPEDEF ) LcfgSignature;
    VAR( uint32, TYPEDEF ) CfgSignature;
    VAR( uint32, TYPEDEF ) PublicInfoSignature;
    TS_REF2CFG( CanTp_RxNPduLookupEntryType )  RxNPduLookupTablePtr;
    TS_REF2CFG( CanTp_RxNPduTableType )  RxNPduTablePtr;
    TS_REF2CFG( CanTp_RxNSduConfigType )  RxNSduConfigPtr;
    TS_REF2CFG( CanTp_TxNSduConfigType )  TxNSduConfigPtr;
    TS_REF2CFG( CanTp_MfCtrConfigType )  MfCtrConfigPtr;
    TS_REF2CFG( uint8 )  TxNPduToTpChannelPtr;
    VAR( uint16, TYPEDEF ) NumberRxNPdus;
    VAR( uint16, TYPEDEF ) NumberTxNSdus;
    VAR( uint16, TYPEDEF ) NumberRxNSdus;
    VAR( uint16, TYPEDEF ) NumberTxConfNPdus;
    VAR( uint8, TYPEDEF ) NumberOfChannels;
    VAR( uint8, TYPEDEF ) NumberOfTxChannels;
} CanTp_ConfigType;


/*==================[external function declarations]=========================*/


/*==================[internal function declarations]=========================*/


/*==================[external constants]=====================================*/


/*==================[internal constants]=====================================*/


/*==================[external data]==========================================*/


/*==================[internal data]==========================================*/


/*==================[external function definitions]==========================*/


/*==================[internal function definitions]==========================*/


/* Deviation MISRA-1 */
#undef TS_RELOCATABLE_CFG_ENABLE
/* Deviation MISRA-1 */
#undef TS_PB_CFG_PTR_CLASS

#endif /* CANTP_TYPES_INT_H */

/*==================[end of file]============================================*/

