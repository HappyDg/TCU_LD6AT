
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


/* MISRA-C:2004 Deviations
 *
 * MISRA-1) Deviated Rule: 19.6 (required)
 * "'#undef' shall not be used"
 *
 *    Reason:
 *    The macros TS_PB_CFG_LAYOUT_TYPE and TS_PB_CFG_NAME must be redefined
 *    if submodules are included within a global layout structure.
 *
 *  MISRA-2) Deviated Rule: 20.6 (required)
 *    The macro `offsetof' shall not be used.
 *
 *    Reason:
 *    Relocatable postbuild macro requires the usage of `offsetof'.
 *
 *  MISRA-3) Deviated Rule: 11.3 (advisory)
 *    A cast should not be performed between a pointer type and an integral
 *    type.
 *
 *    Reason:
 *    Relocatable postbuild macro requires the cast between pointer and
 *    integral type.
 *
 */

/*==================[inclusions]=============================================*/

#include <CanTp_PBcfg.h>
#include <TSAutosar.h>
#include <Compiler.h>
#define TS_RELOCATABLE_CFG_ENABLE STD_ON
#define TS_PB_CFG_NAME CANTP_PB_CONFIG_NAME
#define TS_PB_CFG_LAYOUT_TYPE CANTP_CONST_CONFIG_LAYOUT_TYPE
#include <TSPBConfig_Init.h>

/*==================[macros]=================================================*/


/*==================[type definitions]=======================================*/


/*==================[external function declarations]=========================*/


/*==================[internal function declarations]=========================*/


/*==================[external constants]=====================================*/

#define CANTP_START_CONFIG_DATA_UNSPECIFIED
#include <MemMap.h>

/* Deviation MISRA-2, MISRA-3 <START> */
CANTP_CONST_CONFIG_LAYOUT_TYPE CANTP_CONFIG_NAME = {
    { /* RootCfg */
        UINT32_C( 2147485970 ), /* PlatformSignature */
        UINT32_C( 3958107115 ), /* LcfgSignature */
        UINT32_C( 3746009740 ), /* CfgSignature */
        UINT32_C( 1103003787 ), /* PublicInfoSignature */
        TS_MAKEREF2CFG( RxNPduLookupTable[0] ), /* RxNPduLookupTablePtr */
        TS_MAKEREF2CFG( RxNPduTable[0] ), /* RxNPduTablePtr */
        TS_MAKEREF2CFG( RxNSduConfig[0] ), /* RxNSduConfigPtr */
        TS_MAKEREF2CFG( TxNSduConfig[0] ), /* TxNSduConfigPtr */
        TS_MAKEREF2CFG( MfCtrConfig[0] ), /* MfCtrConfigPtr */
        TS_MAKEREF2CFG( TxNPduToTpChannel[0] ), /* TxNPduToTpChannelPtr */
        UINT16_C( 2 ), /* NumberRxNPdus */
        UINT16_C( 1 ), /* NumberTxNSdus */
        UINT16_C( 2 ), /* NumberRxNSdus */
        UINT16_C( 2 ), /* NumberTxConfNPdus */
        UINT8_C( 2 ), /* NumberOfChannels */
        UINT8_C( 1 ) /* NumberOfTxChannels */
    },
    { /* RxNPduLookupTable */
        UINT16_C( 0 ), /* RxNPduLookupTable[0] */
        UINT16_C( 2 ), /* RxNPduLookupTable[1] */
        UINT16_C( 3 ) /* RxNPduLookupTable[2] */
    },
    { /* RxNPduTable */
        { /* RxNPduTable[0] */
            UINT16_C( 0 ), /* Index */
            UINT16_C( 1 ), /* Next */
            UINT8_C( 0 ), /* AddressingFormat */
            UINT8_C( 0 ), /* N_SA_AE */
            UINT8_C( 1 ) /* Direction */
        },
        { /* RxNPduTable[1] */
            UINT16_C( 0 ), /* Index */
            UINT16_C( 0 ), /* Next */
            UINT8_C( 0 ), /* AddressingFormat */
            UINT8_C( 0 ), /* N_SA_AE */
            UINT8_C( 0 ) /* Direction */
        },
        { /* RxNPduTable[2] */
            UINT16_C( 1 ), /* Index */
            UINT16_C( 0 ), /* Next */
            UINT8_C( 0 ), /* AddressingFormat */
            UINT8_C( 0 ), /* N_SA_AE */
            UINT8_C( 1 ) /* Direction */
        }
    },
    { /* RxNSduConfig */
        { /* RxNSduConfig[0] */
            UINT16_C( 1 ), /* NPduConfIdFc */
            UINT16_C( 5 ), /* LSduIdFc */
            UINT16_C( 0 ), /* IPduId */
            UINT16_C( 0 ), /* NPduIdxF */
            UINT16_C( 20 ), /* N_Ar */
            UINT16_C( 20 ), /* N_Br */
            UINT16_C( 200 ), /* N_Cr */
            UINT8_C( 0 ), /* AddressingFormat */
            UINT8_C( 0 ), /* Tatype */
            UINT8_C( 1 ), /* PaddingActivation */
            UINT8_C( 0 ), /* N_TA_AE */
            UINT8_C( 4 ), /* WftMax */
            UINT8_C( 16 ), /* BS */
            UINT8_C( 0 ), /* Channel */
            UINT8_C( 1 ), /* ChannelMode */
            UINT8_C( 0 ) /* STmin */
        },
        { /* RxNSduConfig[1] */
            UINT16_C( 65535 ), /* NPduConfIdFc */
            UINT16_C( 65535 ), /* LSduIdFc */
            UINT16_C( 1 ), /* IPduId */
            UINT16_C( 1 ), /* NPduIdxF */
            UINT16_C( 0 ), /* N_Ar */
            UINT16_C( 20 ), /* N_Br */
            UINT16_C( 0 ), /* N_Cr */
            UINT8_C( 0 ), /* AddressingFormat */
            UINT8_C( 1 ), /* Tatype */
            UINT8_C( 1 ), /* PaddingActivation */
            UINT8_C( 0 ), /* N_TA_AE */
            UINT8_C( 0 ), /* WftMax */
            UINT8_C( 0 ), /* BS */
            UINT8_C( 1 ), /* Channel */
            UINT8_C( 1 ), /* ChannelMode */
            UINT8_C( 0 ) /* STmin */
        }
    },
    { /* TxNSduConfig */
        { /* TxNSduConfig[0] */
            UINT16_C( 0 ), /* NPduIdFc */
            UINT16_C( 0 ), /* NPduConfIdxF */
            UINT16_C( 4 ), /* LSduIdxF */
            UINT16_C( 0 ), /* IPduConfId */
            UINT16_C( 200 ), /* N_As */
            UINT16_C( 200 ), /* N_Bs */
            UINT16_C( 2 ), /* N_Cs */
            UINT8_C( 0 ), /* AddressingFormat */
            UINT8_C( 0 ), /* Tatype */
            UINT8_C( 1 ), /* PaddingActivation */
            UINT8_C( 0 ), /* N_TA_AE */
            UINT8_C( 0 ), /* Channel */
            UINT8_C( 1 ), /* ChannelMode */
            BOOLEAN_C( 1 ) /* CanTpTc */
        }
    },
    { /* MfCtrConfig */
        { /* MfCtrConfig[0] */
            UINT32_C( 5000000 ), /* Resolution */
            UINT8_C( 1 ) /* CallbackType */
        }
    },
    { /* TxNPduToTpChannel */
        UINT8_C( 0 ), /* TxNPduToTpChannel[0] */
        UINT8_C( 0 ) /* TxNPduToTpChannel[1] */
    }
};

/* Deviation MISRA-2, MISRA-3 <STOP> */

#define CANTP_STOP_CONFIG_DATA_UNSPECIFIED
#include <MemMap.h>

/*==================[internal constants]=====================================*/


/*==================[external data]==========================================*/


/*==================[internal data]==========================================*/


/*==================[external function definitions]==========================*/


/*==================[internal function definitions]==========================*/


/*==================[end of file]============================================*/

