
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

#include <PduR_PBcfg.h>
#include <TSAutosar.h>
#include <Compiler.h>
#define TS_RELOCATABLE_CFG_ENABLE STD_OFF
#define TS_PB_CFG_NAME PDUR_PB_CONFIG_NAME
#define TS_PB_CFG_LAYOUT_TYPE PDUR_CONST_CONFIG_LAYOUT_TYPE
#include <TSPBConfig_Init.h>

/*==================[macros]=================================================*/


/*==================[type definitions]=======================================*/


/*==================[external function declarations]=========================*/


/*==================[internal function declarations]=========================*/


/*==================[external constants]=====================================*/

#define PDUR_START_CONFIG_DATA_UNSPECIFIED
#include <MemMap.h>

/* Deviation MISRA-2, MISRA-3 <START> */
PDUR_CONST_CONFIG_LAYOUT_TYPE PDUR_CONFIG_NAME = {
    { /* PduR_RootConfig */
        UINT32_C( 2147485970 ), /* PduR_PlatformSignature */
        UINT32_C( 3287086706 ), /* PduR_PublicInfoSignature */
        UINT32_C( 595525791 ), /* PduR_CfgSignature */
        UINT32_C( 3958107115 ), /* PduR_LcfgSignature */
        TS_MAKENULLREF2CFG, /* PduR_BufDefaultRef */
        TS_MAKENULLREF2CFG, /* PduR_BufSbConfigRef */
        TS_MAKENULLREF2CFG, /* PduR_BufDfConfigRef */
        TS_MAKENULLREF2CFG, /* PduR_BufTfConfigRef */
        TS_MAKENULLREF2CFG, /* PduR_BufSbDynPyldConfigRef */
        TS_MAKENULLREF2CFG, /* PduR_BufDfDynPyldConfigRef */
        TS_MAKENULLREF2CFG, /* PduR_BufTfDynPyldConfigRef */
        TS_MAKENULLREF2CFG, /* PduR_BufTpConfigRef */
        { /* PduR_MTabLoIfConfig */
            TS_MAKENULLREF2CFG, /* MTabRxRef */
            UINT16_C( 0 ) /* MTabRxCount */
        },
        { /* PduR_MTabUpIfConfig */
            TS_MAKENULLREF2CFG, /* MTabTxRef */
            UINT16_C( 0 ) /* MTabTxCount */
        },
        { /* PduR_MTabUpTpConfig */
            TS_MAKENULLREF2CFG, /* MTabTxRef */
            UINT16_C( 0 ) /* MTabTxCount */
        },
        { /* PduR_GTabIfConfig */
            TS_MAKENULLREF2CFG, /* GTabRxRef */
            UINT16_C( 0 ) /* GTabRxCount */
        },
        { /* PduR_GTabTpConfig */
            TS_MAKENULLREF2CFG, /* GTabRxRef */
            UINT16_C( 0 ) /* GTabRxCount */
        },
        { /* PduR_RTabLoIfConfig */
            { /* PduR_RTabLoIfConfig[0] -- CanIf */
                TS_MAKEREF2CFG( PduR_RTabLoIfRx[0] ), /* RTabRxRef */
                TS_MAKEREF2CFG( PduR_RTabLoIfTx[0] ), /* RTabTxRef */
                UINT16_C( 7 ), /* RTabRxCount */
                UINT16_C( 2 ) /* RTabTxCount */
            }
        },
        { /* PduR_RTabUpIfTxConfig */
            { /* PduR_RTabUpIfTxConfig[0] -- Com */
                TS_MAKEREF2CFG( PduR_RTabUpIfTx[0] ), /* RTabTxRef */
                UINT16_C( 2 ) /* RTabTxCount */
            }
        },
        { /* PduR_RTabLoTpConfig */
            { /* PduR_RTabLoTpConfig[0] -- CanTp */
                TS_MAKEREF2CFG( PduR_RTabLoTpRx[0] ), /* RTabRxRef */
                TS_MAKEREF2CFG( PduR_RTabLoTpTx[0] ), /* RTabTxRef */
                UINT16_C( 2 ), /* RTabRxCount */
                UINT16_C( 1 ) /* RTabTxCount */
            }
        },
        { /* PduR_RTabUpTpConfig */
            { /* PduR_RTabUpTpConfig[0] -- Dcm */
                TS_MAKEREF2CFG( PduR_RTabUpTpTx[0] ), /* RTabTxRef */
                TS_MAKENULLREF2CFG, /* RTabRxRef */
                UINT16_C( 1 ), /* RTabTxCount */
                UINT16_C( 0 ) /* RTabRxCount */
            }
        },
        UINT16_C( 0 ), /* PduR_ConfigurationId */
        UINT16_C( 0 ), /* PduR_BufSbCount */
        UINT16_C( 0 ), /* PduR_BufDfCount */
        UINT16_C( 0 ), /* PduR_BufTfCount */
        UINT16_C( 0 ), /* PduR_BufSbDynPyldCount */
        UINT16_C( 0 ), /* PduR_BufDfDynPyldCount */
        UINT16_C( 0 ), /* PduR_BufTfDynPyldCount */
        UINT16_C( 0 ), /* PduR_BufTpCount */
        UINT16_C( 0 ), /* PduR_MultiTpTxSessionInfoRef */
        UINT16_C( 0 ), /* PduR_BufSbDynPyldInfoRef */
        UINT16_C( 0 ), /* PduR_BufDfInfoRef */
        UINT16_C( 0 ), /* PduR_BufDfDynPyldInfoRef */
        UINT16_C( 0 ), /* PduR_BufTfInfoRef */
        UINT16_C( 0 ), /* PduR_BufTfDynPyldInfoRef */
        UINT16_C( 0 ), /* PduR_GateTpSessionInfoRef */
        UINT8_C( 0 ) /* PduR_MultiTpTxRPathsMax */
    },
    { /* PduR_RTabLoIfRx */
        { /* PduR_RTabLoIfRx[0] -- Routing path:'ECM1_273R', calling module:'CanIf-LO-IF', PDU ID:0 */
            UINT16_C( 0 ), /* TargetPduId */
            UINT16_C( 0 ) /* TargetModuleAPIRef -- TargetModuleAPIRef: Com */
        },
        { /* PduR_RTabLoIfRx[1] -- Routing path:'ECM2_289R', calling module:'CanIf-LO-IF', PDU ID:1 */
            UINT16_C( 1 ), /* TargetPduId */
            UINT16_C( 0 ) /* TargetModuleAPIRef -- TargetModuleAPIRef: Com */
        },
        { /* PduR_RTabLoIfRx[2] -- Routing path:'ABS1_529R', calling module:'CanIf-LO-IF', PDU ID:2 */
            UINT16_C( 2 ), /* TargetPduId */
            UINT16_C( 0 ) /* TargetModuleAPIRef -- TargetModuleAPIRef: Com */
        },
        { /* PduR_RTabLoIfRx[3] -- Routing path:'ABS2_545R', calling module:'CanIf-LO-IF', PDU ID:3 */
            UINT16_C( 3 ), /* TargetPduId */
            UINT16_C( 0 ) /* TargetModuleAPIRef -- TargetModuleAPIRef: Com */
        },
        { /* PduR_RTabLoIfRx[4] -- Routing path:'ESC1_561R', calling module:'CanIf-LO-IF', PDU ID:4 */
            UINT16_C( 4 ), /* TargetPduId */
            UINT16_C( 0 ) /* TargetModuleAPIRef -- TargetModuleAPIRef: Com */
        },
        { /* PduR_RTabLoIfRx[5] -- Routing path:'ECM3_609R', calling module:'CanIf-LO-IF', PDU ID:5 */
            UINT16_C( 5 ), /* TargetPduId */
            UINT16_C( 0 ) /* TargetModuleAPIRef -- TargetModuleAPIRef: Com */
        },
        { /* PduR_RTabLoIfRx[6] -- Routing path:'IP1_641R', calling module:'CanIf-LO-IF', PDU ID:6 */
            UINT16_C( 6 ), /* TargetPduId */
            UINT16_C( 0 ) /* TargetModuleAPIRef -- TargetModuleAPIRef: Com */
        }
    },
    { /* PduR_RTabLoIfTx */
        { /* PduR_RTabLoIfTx[0] -- Routing path:'TCU1_321T', calling module:'CanIf-LO-IF', PDU ID:0 */
            UINT16_C( 0 ), /* TargetPduId */
            UINT16_C( 0 ) /* TargetModuleAPIRef -- TargetModuleAPIRef: Com */
        },
        { /* PduR_RTabLoIfTx[1] -- Routing path:'TCU2_337T', calling module:'CanIf-LO-IF', PDU ID:1 */
            UINT16_C( 1 ), /* TargetPduId */
            UINT16_C( 0 ) /* TargetModuleAPIRef -- TargetModuleAPIRef: Com */
        }
    },
    { /* PduR_RTabUpIfTx */
        { /* PduR_RTabUpIfTx[0] -- Routing path:'TCU1_321T', calling module:'Com-UP-IF', PDU ID:0 */
            UINT16_C( 6 ), /* TargetPduId */
            UINT16_C( 1 ) /* TargetModuleAPIRef -- TargetModuleAPIRef: CanIf */
        },
        { /* PduR_RTabUpIfTx[1] -- Routing path:'TCU2_337T', calling module:'Com-UP-IF', PDU ID:1 */
            UINT16_C( 7 ), /* TargetPduId */
            UINT16_C( 1 ) /* TargetModuleAPIRef -- TargetModuleAPIRef: CanIf */
        }
    },
    { /* PduR_RTabLoTpRx */
        { /* PduR_RTabLoTpRx[0] -- Routing path:'Dcm_Phy_Rx', calling module:'CanTp-LO-TP', PDU ID:0 */
            UINT16_C( 0 ), /* TargetPduId */
            UINT16_C( 1 ) /* TargetModuleAPIRef -- TargetModuleAPIRef: Dcm */
        },
        { /* PduR_RTabLoTpRx[1] -- Routing path:'Dcm_Func_Rx', calling module:'CanTp-LO-TP', PDU ID:1 */
            UINT16_C( 1 ), /* TargetPduId */
            UINT16_C( 1 ) /* TargetModuleAPIRef -- TargetModuleAPIRef: Dcm */
        }
    },
    { /* PduR_RTabLoTpTx */
        { /* PduR_RTabLoTpTx[0] -- Routing path:'Dcm_Phy_Tx', calling module:'CanTp-LO-TP', PDU ID:0 */
            UINT16_C( 0 ), /* TargetPduId */
            UINT16_C( 1 ) /* TargetModuleAPIRef -- TargetModuleAPIRef: Dcm */
        }
    },
    { /* PduR_RTabUpTpTx */
        { /* PduR_RTabUpTpTx[0] -- Routing path:'Dcm_Phy_Tx', calling module:'Dcm-UP-TP', PDU ID:0 */
            UINT16_C( 0 ), /* TargetPduId */
            UINT16_C( 0 ) /* TargetModuleAPIRef -- TargetModuleAPIRef: CanTp */
        }
    }
};

/* Deviation MISRA-2, MISRA-3 <STOP> */

#define PDUR_STOP_CONFIG_DATA_UNSPECIFIED
#include <MemMap.h>

/*==================[internal constants]=====================================*/


/*==================[external data]==========================================*/


/*==================[internal data]==========================================*/


/*==================[external function definitions]==========================*/


/*==================[internal function definitions]==========================*/


/*==================[end of file]============================================*/

