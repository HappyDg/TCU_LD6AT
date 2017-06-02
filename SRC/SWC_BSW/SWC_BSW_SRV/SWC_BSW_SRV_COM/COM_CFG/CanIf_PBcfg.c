
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

#include <CanIf_PBcfg.h>
#include <TSAutosar.h>
#include <Compiler.h>
#define TS_RELOCATABLE_CFG_ENABLE STD_ON
#define TS_PB_CFG_NAME CANIF_PB_CONFIG_NAME
#define TS_PB_CFG_LAYOUT_TYPE CANIF_CONST_CONFIG_LAYOUT_TYPE
#include <TSPBConfig_Init.h>

/*==================[macros]=================================================*/


/*==================[type definitions]=======================================*/


/*==================[external function declarations]=========================*/


/*==================[internal function declarations]=========================*/


/*==================[external constants]=====================================*/

#define CANIF_START_CONFIG_DATA_UNSPECIFIED
#include <MemMap.h>

/* Deviation MISRA-2, MISRA-3 <START> */
CANIF_CONST_CONFIG_LAYOUT_TYPE CANIF_CONFIG_NAME = {
    { /* RootCfg */
        UINT32_C( 2147485970 ), /* PlatformSignature */
        UINT32_C( 1786276887 ), /* LcfgSignature */
        UINT32_C( 1542389019 ), /* CfgSignature */
        UINT32_C( 3295759444 ), /* PublicInfoSignature */
        TS_MAKEREF2CFG( txLPduConfig[0] ), /* txLPduConfigPtr */
        TS_MAKEREF2CFG( rxLPduConfig[0] ), /* rxLPduConfigPtr */
        TS_MAKENULLREF2CFG, /* sortedRxLPduConfigPtr */
        TS_MAKEREF2CFG( canDriverConfig[0] ), /* driverConfigPtr */
        UINT16_C( 8 ), /* nrOfStaticTxLPdus */
        UINT16_C( 8 ), /* nrOfTxLPdus */
        UINT16_C( 10 ), /* nrOfRxLPdus */
        UINT16_C( 0 ) /* nrOfTxBuffers */
    },
    { /* txLPduConfig */
        { /* txLPduConfig[0] */
            UINT32_C( 511 ), /* canId */
            UINT8_C( 13 ), /* hth */
            UINT16_C( 65535 ), /* bufferIndex */
            UINT16_C( 15 ), /* sourcePduId_UL */
            UINT8_C( 4 ) /* userType */
        },
        { /* txLPduConfig[1] */
            UINT32_C( 512 ), /* canId */
            UINT8_C( 14 ), /* hth */
            UINT16_C( 65535 ), /* bufferIndex */
            UINT16_C( 16 ), /* sourcePduId_UL */
            UINT8_C( 5 ) /* userType */
        },
        { /* txLPduConfig[2] */
            UINT32_C( 513 ), /* canId */
            UINT8_C( 15 ), /* hth */
            UINT16_C( 65535 ), /* bufferIndex */
            UINT16_C( 17 ), /* sourcePduId_UL */
            UINT8_C( 6 ) /* userType */
        },
        { /* txLPduConfig[3] */
            UINT32_C( 770 ), /* canId */
            UINT8_C( 16 ), /* hth */
            UINT16_C( 65535 ), /* bufferIndex */
            UINT16_C( 18 ), /* sourcePduId_UL */
            UINT8_C( 3 ) /* userType */
        },
        { /* txLPduConfig[4] */
            UINT32_C( 1922 ), /* canId */
            UINT8_C( 17 ), /* hth */
            UINT16_C( 65535 ), /* bufferIndex */
            UINT16_C( 0 ), /* sourcePduId_UL */
            UINT8_C( 1 ) /* userType */
        },
        { /* txLPduConfig[5] */
            UINT32_C( 1040 ), /* canId */
            UINT8_C( 18 ), /* hth */
            UINT16_C( 65535 ), /* bufferIndex */
            UINT16_C( 1 ), /* sourcePduId_UL */
            UINT8_C( 1 ) /* userType */
        },
        { /* txLPduConfig[6] */
            UINT32_C( 321 ), /* canId */
            UINT8_C( 11 ), /* hth */
            UINT16_C( 65535 ), /* bufferIndex */
            UINT16_C( 0 ), /* sourcePduId_UL */
            UINT8_C( 2 ) /* userType */
        },
        { /* txLPduConfig[7] */
            UINT32_C( 337 ), /* canId */
            UINT8_C( 12 ), /* hth */
            UINT16_C( 65535 ), /* bufferIndex */
            UINT16_C( 1 ), /* sourcePduId_UL */
            UINT8_C( 2 ) /* userType */
        }
    },
    { /* rxLPduConfig */
        { /* rxLPduConfig[0] */
            UINT32_C( 769 ), /* canId */
            UINT16_C( 56 ), /* targetPduId */
            UINT8_C( 7 ), /* userType */
            UINT8_C( 8 ) /* dlc */
        },
        { /* rxLPduConfig[1] */
            UINT32_C( 1794 ), /* canId */
            UINT16_C( 0 ), /* targetPduId */
            UINT8_C( 1 ), /* userType */
            UINT8_C( 8 ) /* dlc */
        },
        { /* rxLPduConfig[2] */
            UINT32_C( 2015 ), /* canId */
            UINT16_C( 1 ), /* targetPduId */
            UINT8_C( 1 ), /* userType */
            UINT8_C( 8 ) /* dlc */
        },
        { /* rxLPduConfig[3] */
            UINT32_C( 273 ), /* canId */
            UINT16_C( 0 ), /* targetPduId */
            UINT8_C( 2 ), /* userType */
            UINT8_C( 8 ) /* dlc */
        },
        { /* rxLPduConfig[4] */
            UINT32_C( 289 ), /* canId */
            UINT16_C( 1 ), /* targetPduId */
            UINT8_C( 2 ), /* userType */
            UINT8_C( 8 ) /* dlc */
        },
        { /* rxLPduConfig[5] */
            UINT32_C( 529 ), /* canId */
            UINT16_C( 2 ), /* targetPduId */
            UINT8_C( 2 ), /* userType */
            UINT8_C( 8 ) /* dlc */
        },
        { /* rxLPduConfig[6] */
            UINT32_C( 545 ), /* canId */
            UINT16_C( 3 ), /* targetPduId */
            UINT8_C( 2 ), /* userType */
            UINT8_C( 8 ) /* dlc */
        },
        { /* rxLPduConfig[7] */
            UINT32_C( 561 ), /* canId */
            UINT16_C( 4 ), /* targetPduId */
            UINT8_C( 2 ), /* userType */
            UINT8_C( 8 ) /* dlc */
        },
        { /* rxLPduConfig[8] */
            UINT32_C( 609 ), /* canId */
            UINT16_C( 5 ), /* targetPduId */
            UINT8_C( 2 ), /* userType */
            UINT8_C( 8 ) /* dlc */
        },
        { /* rxLPduConfig[9] */
            UINT32_C( 641 ), /* canId */
            UINT16_C( 6 ), /* targetPduId */
            UINT8_C( 2 ), /* userType */
            UINT8_C( 8 ) /* dlc */
        }
    },
    { /* driverHthConfig */
        { /* driverHthConfig[0] */
            UINT16_C( 0 ), /* firstIndex */
            UINT8_C( 0 ) /* intCtrlIdx */
        },
        { /* driverHthConfig[1] */
            UINT16_C( 0 ), /* firstIndex */
            UINT8_C( 0 ) /* intCtrlIdx */
        },
        { /* driverHthConfig[2] */
            UINT16_C( 0 ), /* firstIndex */
            UINT8_C( 2 ) /* intCtrlIdx */
        },
        { /* driverHthConfig[3] */
            UINT16_C( 0 ), /* firstIndex */
            UINT8_C( 2 ) /* intCtrlIdx */
        },
        { /* driverHthConfig[4] */
            UINT16_C( 0 ), /* firstIndex */
            UINT8_C( 2 ) /* intCtrlIdx */
        },
        { /* driverHthConfig[5] */
            UINT16_C( 0 ), /* firstIndex */
            UINT8_C( 2 ) /* intCtrlIdx */
        },
        { /* driverHthConfig[6] */
            UINT16_C( 0 ), /* firstIndex */
            UINT8_C( 2 ) /* intCtrlIdx */
        },
        { /* driverHthConfig[7] */
            UINT16_C( 0 ), /* firstIndex */
            UINT8_C( 2 ) /* intCtrlIdx */
        }
    },
    { /* driverHrhConfig */
        { /* driverHrhConfig[0] */
            UINT16_C( 5 ), /* firstIndex */
            UINT16_C( 0 ), /* lastIndex */
            UINT8_C( 0 ), /* swFiltering */
            UINT8_C( 0 ) /* intCtrlIdx */
        },
        { /* driverHrhConfig[1] */
            UINT16_C( 6 ), /* firstIndex */
            UINT16_C( 0 ), /* lastIndex */
            UINT8_C( 0 ), /* swFiltering */
            UINT8_C( 0 ) /* intCtrlIdx */
        },
        { /* driverHrhConfig[2] */
            UINT16_C( 3 ), /* firstIndex */
            UINT16_C( 0 ), /* lastIndex */
            UINT8_C( 0 ), /* swFiltering */
            UINT8_C( 0 ) /* intCtrlIdx */
        },
        { /* driverHrhConfig[3] */
            UINT16_C( 4 ), /* firstIndex */
            UINT16_C( 0 ), /* lastIndex */
            UINT8_C( 0 ), /* swFiltering */
            UINT8_C( 0 ) /* intCtrlIdx */
        },
        { /* driverHrhConfig[4] */
            UINT16_C( 8 ), /* firstIndex */
            UINT16_C( 0 ), /* lastIndex */
            UINT8_C( 0 ), /* swFiltering */
            UINT8_C( 0 ) /* intCtrlIdx */
        },
        { /* driverHrhConfig[5] */
            UINT16_C( 7 ), /* firstIndex */
            UINT16_C( 0 ), /* lastIndex */
            UINT8_C( 0 ), /* swFiltering */
            UINT8_C( 0 ) /* intCtrlIdx */
        },
        { /* driverHrhConfig[6] */
            UINT16_C( 9 ), /* firstIndex */
            UINT16_C( 0 ), /* lastIndex */
            UINT8_C( 0 ), /* swFiltering */
            UINT8_C( 0 ) /* intCtrlIdx */
        },
        { /* driverHrhConfig[7] */
            UINT16_C( 0 ), /* firstIndex */
            UINT16_C( 0 ), /* lastIndex */
            UINT8_C( 0 ), /* swFiltering */
            UINT8_C( 2 ) /* intCtrlIdx */
        },
        { /* driverHrhConfig[8] */
            UINT16_C( 65535 ), /* firstIndex */
            UINT16_C( 65535 ), /* lastIndex */
            UINT8_C( 0 ), /* swFiltering */
            UINT8_C( 2 ) /* intCtrlIdx */
        },
        { /* driverHrhConfig[9] */
            UINT16_C( 1 ), /* firstIndex */
            UINT16_C( 0 ), /* lastIndex */
            UINT8_C( 0 ), /* swFiltering */
            UINT8_C( 2 ) /* intCtrlIdx */
        },
        { /* driverHrhConfig[10] */
            UINT16_C( 2 ), /* firstIndex */
            UINT16_C( 0 ), /* lastIndex */
            UINT8_C( 0 ), /* swFiltering */
            UINT8_C( 2 ) /* intCtrlIdx */
        }
    },
    { /* hohIdToCanIfIdx */
        UINT16_C( 0 ), /* hohIdToCanIfIdx[0] */
        UINT16_C( 1 ), /* hohIdToCanIfIdx[1] */
        UINT16_C( 2 ), /* hohIdToCanIfIdx[2] */
        UINT16_C( 3 ), /* hohIdToCanIfIdx[3] */
        UINT16_C( 4 ), /* hohIdToCanIfIdx[4] */
        UINT16_C( 5 ), /* hohIdToCanIfIdx[5] */
        UINT16_C( 6 ), /* hohIdToCanIfIdx[6] */
        UINT16_C( 7 ), /* hohIdToCanIfIdx[7] */
        UINT16_C( 8 ), /* hohIdToCanIfIdx[8] */
        UINT16_C( 9 ), /* hohIdToCanIfIdx[9] */
        UINT16_C( 10 ), /* hohIdToCanIfIdx[10] */
        UINT16_C( 0 ), /* hohIdToCanIfIdx[11] */
        UINT16_C( 1 ), /* hohIdToCanIfIdx[12] */
        UINT16_C( 2 ), /* hohIdToCanIfIdx[13] */
        UINT16_C( 3 ), /* hohIdToCanIfIdx[14] */
        UINT16_C( 4 ), /* hohIdToCanIfIdx[15] */
        UINT16_C( 5 ), /* hohIdToCanIfIdx[16] */
        UINT16_C( 6 ), /* hohIdToCanIfIdx[17] */
        UINT16_C( 7 ) /* hohIdToCanIfIdx[18] */
    },
    { /* canControllerConfig */
        { /* canControllerConfig[0] */
            UINT8_C( 0 ) /* controllerId */
        },
        { /* canControllerConfig[1] */
            UINT8_C( 2 ) /* controllerId */
        },
        { /* canControllerConfig[2] */
            UINT8_C( 1 ) /* controllerId */
        }
    },
    { /* canDriverConfig */
        { /* canDriverConfig[0] */
            TS_MAKEREF2CFG( canControllerConfig[0] ), /* ctrlConfigPtr */
            TS_MAKEREF2CFG( hohIdToCanIfIdx[0] ), /* hohIdToCanIfIdxPtr */
            TS_MAKEREF2CFG( driverHthConfig[0] ), /* hthConfigPtr */
            TS_MAKEREF2CFG( driverHrhConfig[0] ), /* hrhConfigPtr */
            UINT8_C( 8 ), /* nrOfHths */
            UINT8_C( 3 ) /* nrOfControllers */
        }
    }
};

/* Deviation MISRA-2, MISRA-3 <STOP> */

#define CANIF_STOP_CONFIG_DATA_UNSPECIFIED
#include <MemMap.h>

/*==================[internal constants]=====================================*/


/*==================[external data]==========================================*/


/*==================[internal data]==========================================*/


/*==================[external function definitions]==========================*/


/*==================[internal function definitions]==========================*/


/*==================[end of file]============================================*/

