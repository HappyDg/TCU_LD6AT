
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

#include <Com_PBcfg.h>
#include <TSAutosar.h>
#include <Compiler.h>
#define TS_RELOCATABLE_CFG_ENABLE STD_ON
#define TS_PB_CFG_NAME COM_PB_CONFIG_NAME
#define TS_PB_CFG_LAYOUT_TYPE COM_CONST_CONFIG_LAYOUT_TYPE
#include <TSPBConfig_Init.h>

/*==================[macros]=================================================*/


/*==================[type definitions]=======================================*/


/*==================[external function declarations]=========================*/


/*==================[internal function declarations]=========================*/


/*==================[external constants]=====================================*/

#define COM_START_CONFIG_DATA_UNSPECIFIED
#include <MemMap.h>

/* Deviation MISRA-2, MISRA-3 <START> */
COM_CONST_CONFIG_LAYOUT_TYPE COM_CONFIG_NAME = {
    { /* Com_RootConfig */
        UINT32_C( 2147485970 ), /* ComPlatformSignature */
        UINT32_C( 697644921 ), /* ComPublicInfoSignature */
        UINT32_C( 1098706859 ), /* ComCfgSignature */
        UINT32_C( 918703805 ), /* ComLcfgSignature */
        UINT32_C( 0 ), /* ComConfigurationId */
        TS_MAKEREF2CFG( ComRxTimeoutQueueList[0] ), /* ComRxTimeoutQueueListRef */
        TS_MAKEREF2CFG( ComRxIPdu[0] ), /* ComRxIPduRef */
        TS_MAKEREF2CFG( ComTxIPdu[0] ), /* ComTxIPduRef */
        TS_MAKEREF2CFG( ComTxIPduMinimumDelayTimeFactor[0] ), /* ComTxIPduMinimumDelayTimeFactorRef */
        TS_MAKENULLREF2CFG, /* ComTxModeNTimesRef */
        TS_MAKEREF2CFG( ComTxModePeriodic[0] ), /* ComTxModePeriodicRef */
        TS_MAKENULLREF2CFG, /* ComTxModeMixedNTimesRef */
        TS_MAKEREF2CFG( ComIPduGroupMask[0] ), /* ComIPduGroupMaskRef */
        TS_MAKENULLREF2CFG, /* ComSigGWRxIPduListRef */
        TS_MAKENULLREF2CFG, /* ComRxIPduSignalGroupListRef */
        TS_MAKENULLREF2CFG, /* ComTxIPduSignalGroupListRef */
        TS_MAKEREF2CFG( ComRxIPduSignalList[0] ), /* ComRxIPduSignalListRef */
        TS_MAKEREF2CFG( ComTxIPduSignalList[0] ), /* ComTxIPduSignalListRef */
        TS_MAKENULLREF2CFG, /* ComRxSignalGroupRef */
        TS_MAKENULLREF2CFG, /* ComTxSignalGroupRef */
        TS_MAKENULLREF2CFG, /* ComTxSignalGroupGroupSignalListRef */
        TS_MAKEREF2CFG( ComRxTimeoutFactorList[0] ), /* ComRxTimeoutFactorRef */
        TS_MAKEREF2CFG( ComRxFirstTimeoutFactorList[0] ), /* ComRxFirstTimeoutFactorRef */
        TS_MAKENULLREF2CFG, /* ComTxTimeoutFactorRef */
        TS_MAKENULLREF2CFG, /* ComRxGroupSignalRef */
        TS_MAKENULLREF2CFG, /* ComTxGroupSignalRef */
        TS_MAKENULLREF2CFG, /* ComFilter8BitMaskRef */
        TS_MAKENULLREF2CFG, /* ComFilter16BitMaskRef */
        TS_MAKENULLREF2CFG, /* ComFilter32BitMaskRef */
        TS_MAKENULLREF2CFG, /* ComFilter8BitMaskXMinMaxRef */
        TS_MAKENULLREF2CFG, /* ComFilter16BitMaskXMinMaxRef */
        TS_MAKENULLREF2CFG, /* ComFilter32BitMaskXMinMaxRef */
        TS_MAKENULLREF2CFG, /* ComFilterOneEveryNRef */
        TS_MAKEREF2CFG( ComRxSignal[0] ), /* ComRxSignalRef */
        TS_MAKEREF2CFG( ComTxSignal[0] ), /* ComTxSignalRef */
        TS_MAKEREF2CFG( ComRxTimeoutNotificationList[0] ), /* ComRxTimeoutNotificationRef */
        TS_MAKENULLREF2CFG, /* ComTxTimeoutNotificationRef */
        TS_MAKENULLREF2CFG, /* ComTxNotificationRef */
        UINT16_C( 90 ), /* ComRxIPduStatusBase */
        UINT16_C( 97 ), /* ComTxIPduStatusBase */
        UINT16_C( 0 ), /* ComTxSignalGroupStatusBase */
        UINT16_C( 0 ), /* ComBufferBaseUInt32 */
        UINT16_C( 0 ), /* ComBufferBaseSInt32 */
        UINT16_C( 0 ), /* ComBufferBaseUInt16 */
        UINT16_C( 0 ), /* ComBufferBaseSInt16 */
        UINT16_C( 0 ), /* ComBufferBaseUInt8 */
        UINT16_C( 0 ), /* ComBufferBaseSInt8 */
        UINT16_C( 0 ), /* ComBufferBaseBool */
        UINT16_C( 0 ), /* ComFilterOneEveryNBase */
        UINT16_C( 0 ), /* ComMDTQueueBase */
        UINT16_C( 0 ), /* ComMDTQueueMax */
        UINT16_C( 0 ), /* ComPeriodicQueueBase */
        UINT16_C( 2 ), /* ComPeriodicQueueMax */
        UINT16_C( 0 ), /* ComNTimesQueueBaseNextTime */
        UINT16_C( 0 ), /* ComNTimesQueueBaseRemaining */
        UINT16_C( 0 ), /* ComNTimesQueueMax */
        UINT16_C( 4 ), /* ComRxTimeoutQueueBase */
        UINT16_C( 7 ), /* ComRxTimeoutQueueMax */
        UINT16_C( 0 ), /* ComTxTimeoutQueueBase */
        UINT16_C( 0 ), /* ComTxTimeoutQueueMax */
        UINT16_C( 99 ), /* ComCbkTxAckDeferredStatusBase */
        UINT16_C( 2 ), /* ComCbkTxAckDeferredListMax */
        UINT16_C( 7 ), /* ComRxIPduArraySize */
        UINT16_C( 2 ), /* ComTxIPduArraySize */
        UINT16_C( 34 ), /* ComRxSignalArraySize */
        UINT16_C( 16 ), /* ComTxSignalArraySize */
        UINT16_C( 0 ), /* ComFilterOneEveryNArraySize */
        UINT16_C( 4 ), /* ComIPduGroupsNum */
        UINT16_C( 0 ), /* ComSigGWRxIPduArraySize */
        UINT16_C( 0 ), /* ComTxSignalGroupArraySize */
        UINT16_C( 0 ), /* ComRxSignalGroupArraySize */
        UINT16_C( 0 ), /* ComTxGroupSignalArraySize */
        UINT16_C( 0 ) /* ComRxGroupSignalArraySize */
    },
    { /* ComRxIPdu */
        { /* ComRxIPdu[0] -- PDECM1_273R */
            TS_MAKEREF2CFG( ComIPduInit[0] ), /* ComInitValueRef */
            UINT16_C( 0 ), /* ComIPduGroupMaskRef */
            UINT16_C( 18 ), /* ComIPduValueRef */
            UINT16_C( 0 ), /* ComIPduSignalGroupRefNum */
            UINT16_C( 0 ), /* ComIPduSignalGroupRefFirst */
            UINT16_C( 10 ), /* ComIPduSignalRefNum */
            UINT16_C( 0 ), /* ComIPduSignalWithBufferRefNum */
            UINT16_C( 1 ), /* ComIPduSignalW_F_A_NotiRefNum */
            UINT16_C( 0 ), /* ComIPduSignalRefFirst */
            UINT16_C( 65535 ), /* ComIPduCallOutFuncPtrRef */
            UINT16_C( 0 ), /* ComRxTimeoutNotificationFirst */
            UINT16_C( 1 ), /* ComRxTimeoutNotificationNum */
            UINT16_C( 0 ), /* ComRxTimeoutFactorRef */
            UINT16_C( 0 ), /* ComRxFirstTimeoutFactorRef */
            UINT16_C( 0 ), /* RxDMQueueRef */
            UINT8_C( 8 ), /* ComIPduSize */
            UINT8_C( 2 ) /* ComRxIPduFlags -- DEFERRED,COM_RX_DM_ON */
        },
        { /* ComRxIPdu[1] -- PDECM2_289R */
            TS_MAKEREF2CFG( ComIPduInit[0] ), /* ComInitValueRef */
            UINT16_C( 0 ), /* ComIPduGroupMaskRef */
            UINT16_C( 26 ), /* ComIPduValueRef */
            UINT16_C( 0 ), /* ComIPduSignalGroupRefNum */
            UINT16_C( 0 ), /* ComIPduSignalGroupRefFirst */
            UINT16_C( 6 ), /* ComIPduSignalRefNum */
            UINT16_C( 0 ), /* ComIPduSignalWithBufferRefNum */
            UINT16_C( 1 ), /* ComIPduSignalW_F_A_NotiRefNum */
            UINT16_C( 10 ), /* ComIPduSignalRefFirst */
            UINT16_C( 65535 ), /* ComIPduCallOutFuncPtrRef */
            UINT16_C( 1 ), /* ComRxTimeoutNotificationFirst */
            UINT16_C( 1 ), /* ComRxTimeoutNotificationNum */
            UINT16_C( 0 ), /* ComRxTimeoutFactorRef */
            UINT16_C( 0 ), /* ComRxFirstTimeoutFactorRef */
            UINT16_C( 1 ), /* RxDMQueueRef */
            UINT8_C( 8 ), /* ComIPduSize */
            UINT8_C( 2 ) /* ComRxIPduFlags -- DEFERRED,COM_RX_DM_ON */
        },
        { /* ComRxIPdu[2] -- PDABS1_529R */
            TS_MAKEREF2CFG( ComIPduInit[0] ), /* ComInitValueRef */
            UINT16_C( 0 ), /* ComIPduGroupMaskRef */
            UINT16_C( 34 ), /* ComIPduValueRef */
            UINT16_C( 0 ), /* ComIPduSignalGroupRefNum */
            UINT16_C( 0 ), /* ComIPduSignalGroupRefFirst */
            UINT16_C( 4 ), /* ComIPduSignalRefNum */
            UINT16_C( 0 ), /* ComIPduSignalWithBufferRefNum */
            UINT16_C( 1 ), /* ComIPduSignalW_F_A_NotiRefNum */
            UINT16_C( 16 ), /* ComIPduSignalRefFirst */
            UINT16_C( 65535 ), /* ComIPduCallOutFuncPtrRef */
            UINT16_C( 2 ), /* ComRxTimeoutNotificationFirst */
            UINT16_C( 1 ), /* ComRxTimeoutNotificationNum */
            UINT16_C( 0 ), /* ComRxTimeoutFactorRef */
            UINT16_C( 0 ), /* ComRxFirstTimeoutFactorRef */
            UINT16_C( 2 ), /* RxDMQueueRef */
            UINT8_C( 8 ), /* ComIPduSize */
            UINT8_C( 2 ) /* ComRxIPduFlags -- DEFERRED,COM_RX_DM_ON */
        },
        { /* ComRxIPdu[3] -- PDABS2_545R */
            TS_MAKEREF2CFG( ComIPduInit[0] ), /* ComInitValueRef */
            UINT16_C( 0 ), /* ComIPduGroupMaskRef */
            UINT16_C( 42 ), /* ComIPduValueRef */
            UINT16_C( 0 ), /* ComIPduSignalGroupRefNum */
            UINT16_C( 0 ), /* ComIPduSignalGroupRefFirst */
            UINT16_C( 3 ), /* ComIPduSignalRefNum */
            UINT16_C( 0 ), /* ComIPduSignalWithBufferRefNum */
            UINT16_C( 1 ), /* ComIPduSignalW_F_A_NotiRefNum */
            UINT16_C( 20 ), /* ComIPduSignalRefFirst */
            UINT16_C( 65535 ), /* ComIPduCallOutFuncPtrRef */
            UINT16_C( 3 ), /* ComRxTimeoutNotificationFirst */
            UINT16_C( 1 ), /* ComRxTimeoutNotificationNum */
            UINT16_C( 0 ), /* ComRxTimeoutFactorRef */
            UINT16_C( 0 ), /* ComRxFirstTimeoutFactorRef */
            UINT16_C( 3 ), /* RxDMQueueRef */
            UINT8_C( 8 ), /* ComIPduSize */
            UINT8_C( 2 ) /* ComRxIPduFlags -- DEFERRED,COM_RX_DM_ON */
        },
        { /* ComRxIPdu[4] -- PDESC1_561R */
            TS_MAKEREF2CFG( ComIPduInit[0] ), /* ComInitValueRef */
            UINT16_C( 0 ), /* ComIPduGroupMaskRef */
            UINT16_C( 50 ), /* ComIPduValueRef */
            UINT16_C( 0 ), /* ComIPduSignalGroupRefNum */
            UINT16_C( 0 ), /* ComIPduSignalGroupRefFirst */
            UINT16_C( 5 ), /* ComIPduSignalRefNum */
            UINT16_C( 0 ), /* ComIPduSignalWithBufferRefNum */
            UINT16_C( 1 ), /* ComIPduSignalW_F_A_NotiRefNum */
            UINT16_C( 23 ), /* ComIPduSignalRefFirst */
            UINT16_C( 65535 ), /* ComIPduCallOutFuncPtrRef */
            UINT16_C( 4 ), /* ComRxTimeoutNotificationFirst */
            UINT16_C( 1 ), /* ComRxTimeoutNotificationNum */
            UINT16_C( 0 ), /* ComRxTimeoutFactorRef */
            UINT16_C( 0 ), /* ComRxFirstTimeoutFactorRef */
            UINT16_C( 4 ), /* RxDMQueueRef */
            UINT8_C( 8 ), /* ComIPduSize */
            UINT8_C( 2 ) /* ComRxIPduFlags -- DEFERRED,COM_RX_DM_ON */
        },
        { /* ComRxIPdu[5] -- PDECM3_609R */
            TS_MAKEREF2CFG( ComIPduInit[0] ), /* ComInitValueRef */
            UINT16_C( 0 ), /* ComIPduGroupMaskRef */
            UINT16_C( 58 ), /* ComIPduValueRef */
            UINT16_C( 0 ), /* ComIPduSignalGroupRefNum */
            UINT16_C( 0 ), /* ComIPduSignalGroupRefFirst */
            UINT16_C( 5 ), /* ComIPduSignalRefNum */
            UINT16_C( 0 ), /* ComIPduSignalWithBufferRefNum */
            UINT16_C( 1 ), /* ComIPduSignalW_F_A_NotiRefNum */
            UINT16_C( 28 ), /* ComIPduSignalRefFirst */
            UINT16_C( 65535 ), /* ComIPduCallOutFuncPtrRef */
            UINT16_C( 5 ), /* ComRxTimeoutNotificationFirst */
            UINT16_C( 1 ), /* ComRxTimeoutNotificationNum */
            UINT16_C( 1 ), /* ComRxTimeoutFactorRef */
            UINT16_C( 1 ), /* ComRxFirstTimeoutFactorRef */
            UINT16_C( 5 ), /* RxDMQueueRef */
            UINT8_C( 8 ), /* ComIPduSize */
            UINT8_C( 2 ) /* ComRxIPduFlags -- DEFERRED,COM_RX_DM_ON */
        },
        { /* ComRxIPdu[6] -- PDIP1_641R */
            TS_MAKEREF2CFG( ComIPduInit[0] ), /* ComInitValueRef */
            UINT16_C( 0 ), /* ComIPduGroupMaskRef */
            UINT16_C( 66 ), /* ComIPduValueRef */
            UINT16_C( 0 ), /* ComIPduSignalGroupRefNum */
            UINT16_C( 0 ), /* ComIPduSignalGroupRefFirst */
            UINT16_C( 1 ), /* ComIPduSignalRefNum */
            UINT16_C( 0 ), /* ComIPduSignalWithBufferRefNum */
            UINT16_C( 1 ), /* ComIPduSignalW_F_A_NotiRefNum */
            UINT16_C( 33 ), /* ComIPduSignalRefFirst */
            UINT16_C( 65535 ), /* ComIPduCallOutFuncPtrRef */
            UINT16_C( 6 ), /* ComRxTimeoutNotificationFirst */
            UINT16_C( 1 ), /* ComRxTimeoutNotificationNum */
            UINT16_C( 1 ), /* ComRxTimeoutFactorRef */
            UINT16_C( 1 ), /* ComRxFirstTimeoutFactorRef */
            UINT16_C( 6 ), /* RxDMQueueRef */
            UINT8_C( 8 ), /* ComIPduSize */
            UINT8_C( 2 ) /* ComRxIPduFlags -- DEFERRED,COM_RX_DM_ON */
        }
    },
    { /* ComTxIPdu */
        { /* ComTxIPdu[0] -- PDTCU1_321T */
            TS_MAKEREF2CFG( ComIPduInit[0] ), /* ComInitValueRef */
            TS_MAKENULLREF2CFG, /* ComIPduTMSFlagsInitValueRef */
            UINT16_C( 1 ), /* ComIPduGroupMaskRef */
            UINT16_C( 0 ), /* PduRTxPduId */
            UINT16_C( 74 ), /* ComIPduValueRef */
            UINT16_C( 0 ), /* ComIPduSignalGroupRefNum */
            UINT16_C( 0 ), /* ComIPduSignalGroupRefFirst */
            UINT16_C( 6 ), /* ComIPduSignalRefNum */
            UINT16_C( 0 ), /* ComIPduSignalWithFilterRefNum */
            UINT16_C( 0 ), /* ComIPduSignalGroupWithFilterRefNum */
            UINT16_C( 0 ), /* ComIPduTMSFlagsRef */
            UINT16_C( 0 ), /* ComIPduSignalRefFirst */
            UINT16_C( 65535 ), /* ComIPduCallOutFuncPtrRef */
            UINT16_C( 65535 ), /* ComIPduTrigTxCallOutFuncPtrRef */
            UINT16_C( 0 ), /* ComTxIPduMinimumDelayTimeFactorRef */
            UINT16_C( 65535 ), /* MDTQueueRef */
            UINT16_C( 0 ), /* ComTxModeTrueRef */
            UINT16_C( 65535 ), /* ComTxModeFalseRef */
            UINT16_C( 0 ), /* PeriodicQueueRef */
            UINT16_C( 0 ), /* NTimesQueueRef */
            UINT16_C( 0 ), /* ComTxTimeoutNotificationFirst */
            UINT16_C( 0 ), /* ComTxTimeoutNotificationNum */
            UINT16_C( 0 ), /* ComTxTimeoutFactorRef */
            UINT16_C( 65535 ), /* TxDMQueueRef */
            UINT16_C( 0 ), /* ComNotificationFirst */
            UINT16_C( 0 ), /* ComNotificationNum */
            UINT16_C( 0 ), /* ComNotificationDeferredQueueRef */
            UINT8_C( 8 ), /* ComIPduSize */
            UINT8_C( 28 ), /* ComTxIPduFlags -- COM_CL_UB_NEVER,DEFERRED,TM_TRUE,COM_TX_DM_OFF */
            UINT8_C( 1 ) /* ComTxModeModes -- True=PERIODIC,False=<undef> */
        },
        { /* ComTxIPdu[1] -- PDTCU2_337T */
            TS_MAKEREF2CFG( ComIPduInit[0] ), /* ComInitValueRef */
            TS_MAKENULLREF2CFG, /* ComIPduTMSFlagsInitValueRef */
            UINT16_C( 1 ), /* ComIPduGroupMaskRef */
            UINT16_C( 1 ), /* PduRTxPduId */
            UINT16_C( 82 ), /* ComIPduValueRef */
            UINT16_C( 0 ), /* ComIPduSignalGroupRefNum */
            UINT16_C( 0 ), /* ComIPduSignalGroupRefFirst */
            UINT16_C( 10 ), /* ComIPduSignalRefNum */
            UINT16_C( 0 ), /* ComIPduSignalWithFilterRefNum */
            UINT16_C( 0 ), /* ComIPduSignalGroupWithFilterRefNum */
            UINT16_C( 0 ), /* ComIPduTMSFlagsRef */
            UINT16_C( 6 ), /* ComIPduSignalRefFirst */
            UINT16_C( 65535 ), /* ComIPduCallOutFuncPtrRef */
            UINT16_C( 65535 ), /* ComIPduTrigTxCallOutFuncPtrRef */
            UINT16_C( 0 ), /* ComTxIPduMinimumDelayTimeFactorRef */
            UINT16_C( 65535 ), /* MDTQueueRef */
            UINT16_C( 0 ), /* ComTxModeTrueRef */
            UINT16_C( 65535 ), /* ComTxModeFalseRef */
            UINT16_C( 1 ), /* PeriodicQueueRef */
            UINT16_C( 0 ), /* NTimesQueueRef */
            UINT16_C( 0 ), /* ComTxTimeoutNotificationFirst */
            UINT16_C( 0 ), /* ComTxTimeoutNotificationNum */
            UINT16_C( 0 ), /* ComTxTimeoutFactorRef */
            UINT16_C( 65535 ), /* TxDMQueueRef */
            UINT16_C( 0 ), /* ComNotificationFirst */
            UINT16_C( 0 ), /* ComNotificationNum */
            UINT16_C( 1 ), /* ComNotificationDeferredQueueRef */
            UINT8_C( 8 ), /* ComIPduSize */
            UINT8_C( 28 ), /* ComTxIPduFlags -- COM_CL_UB_NEVER,DEFERRED,TM_TRUE,COM_TX_DM_OFF */
            UINT8_C( 1 ) /* ComTxModeModes -- True=PERIODIC,False=<undef> */
        }
    },
    { /* ComTxIPduMinimumDelayTimeFactor */
        UINT16_C( 0 ) /* ComTxIPduMinimumDelayTimeFactor[0] */
    },
    { /* ComTxModePeriodic */
        { /* ComTxModePeriodic[0] */
            UINT16_C( 1 ), /* ComTxModeTimeOffsetFactor */
            UINT16_C( 2 ) /* ComTxModeTimePeriodFactor */
        }
    },
    { /* ComRxIPduSignalList */
        UINT16_C( 0 ), /* ComRxIPduSignalList[0] */
        UINT16_C( 1 ), /* ComRxIPduSignalList[1] */
        UINT16_C( 2 ), /* ComRxIPduSignalList[2] */
        UINT16_C( 3 ), /* ComRxIPduSignalList[3] */
        UINT16_C( 4 ), /* ComRxIPduSignalList[4] */
        UINT16_C( 5 ), /* ComRxIPduSignalList[5] */
        UINT16_C( 6 ), /* ComRxIPduSignalList[6] */
        UINT16_C( 7 ), /* ComRxIPduSignalList[7] */
        UINT16_C( 8 ), /* ComRxIPduSignalList[8] */
        UINT16_C( 9 ), /* ComRxIPduSignalList[9] */
        UINT16_C( 10 ), /* ComRxIPduSignalList[10] */
        UINT16_C( 11 ), /* ComRxIPduSignalList[11] */
        UINT16_C( 12 ), /* ComRxIPduSignalList[12] */
        UINT16_C( 13 ), /* ComRxIPduSignalList[13] */
        UINT16_C( 14 ), /* ComRxIPduSignalList[14] */
        UINT16_C( 15 ), /* ComRxIPduSignalList[15] */
        UINT16_C( 16 ), /* ComRxIPduSignalList[16] */
        UINT16_C( 17 ), /* ComRxIPduSignalList[17] */
        UINT16_C( 18 ), /* ComRxIPduSignalList[18] */
        UINT16_C( 19 ), /* ComRxIPduSignalList[19] */
        UINT16_C( 20 ), /* ComRxIPduSignalList[20] */
        UINT16_C( 21 ), /* ComRxIPduSignalList[21] */
        UINT16_C( 22 ), /* ComRxIPduSignalList[22] */
        UINT16_C( 23 ), /* ComRxIPduSignalList[23] */
        UINT16_C( 24 ), /* ComRxIPduSignalList[24] */
        UINT16_C( 25 ), /* ComRxIPduSignalList[25] */
        UINT16_C( 26 ), /* ComRxIPduSignalList[26] */
        UINT16_C( 27 ), /* ComRxIPduSignalList[27] */
        UINT16_C( 30 ), /* ComRxIPduSignalList[28] */
        UINT16_C( 28 ), /* ComRxIPduSignalList[29] */
        UINT16_C( 29 ), /* ComRxIPduSignalList[30] */
        UINT16_C( 31 ), /* ComRxIPduSignalList[31] */
        UINT16_C( 32 ), /* ComRxIPduSignalList[32] */
        UINT16_C( 33 ) /* ComRxIPduSignalList[33] */
    },
    { /* ComTxIPduSignalList */
        UINT16_C( 0 ), /* ComTxIPduSignalList[0] */
        UINT16_C( 1 ), /* ComTxIPduSignalList[1] */
        UINT16_C( 2 ), /* ComTxIPduSignalList[2] */
        UINT16_C( 3 ), /* ComTxIPduSignalList[3] */
        UINT16_C( 4 ), /* ComTxIPduSignalList[4] */
        UINT16_C( 5 ), /* ComTxIPduSignalList[5] */
        UINT16_C( 6 ), /* ComTxIPduSignalList[6] */
        UINT16_C( 7 ), /* ComTxIPduSignalList[7] */
        UINT16_C( 8 ), /* ComTxIPduSignalList[8] */
        UINT16_C( 9 ), /* ComTxIPduSignalList[9] */
        UINT16_C( 10 ), /* ComTxIPduSignalList[10] */
        UINT16_C( 11 ), /* ComTxIPduSignalList[11] */
        UINT16_C( 12 ), /* ComTxIPduSignalList[12] */
        UINT16_C( 13 ), /* ComTxIPduSignalList[13] */
        UINT16_C( 14 ), /* ComTxIPduSignalList[14] */
        UINT16_C( 15 ) /* ComTxIPduSignalList[15] */
    },
    { /* ComRxFirstTimeoutFactorList */
        UINT16_C( 6 ), /* ComRxFirstTimeoutFactorList[0] */
        UINT16_C( 12 ) /* ComRxFirstTimeoutFactorList[1] */
    },
    { /* ComRxTimeoutFactorList */
        UINT16_C( 6 ), /* ComRxTimeoutFactorList[0] */
        UINT16_C( 12 ) /* ComRxTimeoutFactorList[1] */
    },
    { /* ComRxSignal */
        { /* ComRxSignal[0] -- SGAccrPedlRat_273R */
            { /* RxBasicParam */
                UINT16_C( 0 ), /* ComIPduRef */
                UINT16_C( 7 ), /* ComSignalPositionInBit */
                UINT8_C( 14 ), /* ComRxSignalFlags -- UINT8,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 8 ) /* ComBitSize */
            },
            UINT16_C( 0 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[1] -- SGBrkPedlPsd_273R */
            { /* RxBasicParam */
                UINT16_C( 0 ), /* ComIPduRef */
                UINT16_C( 23 ), /* ComSignalPositionInBit */
                UINT8_C( 14 ), /* ComRxSignalFlags -- UINT8,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 2 ) /* ComBitSize */
            },
            UINT16_C( 65535 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[2] -- SGECM1AliveCounter_273R */
            { /* RxBasicParam */
                UINT16_C( 0 ), /* ComIPduRef */
                UINT16_C( 54 ), /* ComSignalPositionInBit */
                UINT8_C( 14 ), /* ComRxSignalFlags -- UINT8,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 4 ) /* ComBitSize */
            },
            UINT16_C( 65535 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[3] -- SGECM1Checksum_273R */
            { /* RxBasicParam */
                UINT16_C( 0 ), /* ComIPduRef */
                UINT16_C( 39 ), /* ComSignalPositionInBit */
                UINT8_C( 14 ), /* ComRxSignalFlags -- UINT8,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 4 ) /* ComBitSize */
            },
            UINT16_C( 65535 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[4] -- SGEngStAct_273R */
            { /* RxBasicParam */
                UINT16_C( 0 ), /* ComIPduRef */
                UINT16_C( 21 ), /* ComSignalPositionInBit */
                UINT8_C( 14 ), /* ComRxSignalFlags -- UINT8,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 3 ) /* ComBitSize */
            },
            UINT16_C( 65535 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[5] -- SGEngTqIndAct_273R */
            { /* RxBasicParam */
                UINT16_C( 0 ), /* ComIPduRef */
                UINT16_C( 18 ), /* ComSignalPositionInBit */
                UINT8_C( 12 ), /* ComRxSignalFlags -- UINT16,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 11 ) /* ComBitSize */
            },
            UINT16_C( 65535 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[6] -- SGEngTqIndDrvDmd_273R */
            { /* RxBasicParam */
                UINT16_C( 0 ), /* ComIPduRef */
                UINT16_C( 34 ), /* ComSignalPositionInBit */
                UINT8_C( 12 ), /* ComRxSignalFlags -- UINT16,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 11 ) /* ComBitSize */
            },
            UINT16_C( 65535 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[7] -- SGEngTqLoss_273R */
            { /* RxBasicParam */
                UINT16_C( 0 ), /* ComIPduRef */
                UINT16_C( 50 ), /* ComSignalPositionInBit */
                UINT8_C( 12 ), /* ComRxSignalFlags -- UINT16,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 11 ) /* ComBitSize */
            },
            UINT16_C( 65535 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[8] -- SGHvacCluSts_273R */
            { /* RxBasicParam */
                UINT16_C( 0 ), /* ComIPduRef */
                UINT16_C( 55 ), /* ComSignalPositionInBit */
                UINT8_C( 8 ), /* ComRxSignalFlags -- BOOLEAN,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 1 ) /* ComBitSize */
            },
            UINT16_C( 65535 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[9] -- SGThrottleCmdPos_273R */
            { /* RxBasicParam */
                UINT16_C( 0 ), /* ComIPduRef */
                UINT16_C( 15 ), /* ComSignalPositionInBit */
                UINT8_C( 14 ), /* ComRxSignalFlags -- UINT8,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 8 ) /* ComBitSize */
            },
            UINT16_C( 65535 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[10] -- SGCrsCtrlCtrlActv_289R */
            { /* RxBasicParam */
                UINT16_C( 1 ), /* ComIPduRef */
                UINT16_C( 39 ), /* ComSignalPositionInBit */
                UINT8_C( 8 ), /* ComRxSignalFlags -- BOOLEAN,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 1 ) /* ComBitSize */
            },
            UINT16_C( 1 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[11] -- SGECM2AliveCounter_289R */
            { /* RxBasicParam */
                UINT16_C( 1 ), /* ComIPduRef */
                UINT16_C( 43 ), /* ComSignalPositionInBit */
                UINT8_C( 14 ), /* ComRxSignalFlags -- UINT8,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 4 ) /* ComBitSize */
            },
            UINT16_C( 65535 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[12] -- SGECM2Checksum_289R */
            { /* RxBasicParam */
                UINT16_C( 1 ), /* ComIPduRef */
                UINT16_C( 47 ), /* ComSignalPositionInBit */
                UINT8_C( 14 ), /* ComRxSignalFlags -- UINT8,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 4 ) /* ComBitSize */
            },
            UINT16_C( 65535 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[13] -- SGEngN_289R */
            { /* RxBasicParam */
                UINT16_C( 1 ), /* ComIPduRef */
                UINT16_C( 7 ), /* ComSignalPositionInBit */
                UINT8_C( 12 ), /* ComRxSignalFlags -- UINT16,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 16 ) /* ComBitSize */
            },
            UINT16_C( 65535 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[14] -- SGEngNTgtIdle_289R */
            { /* RxBasicParam */
                UINT16_C( 1 ), /* ComIPduRef */
                UINT16_C( 23 ), /* ComSignalPositionInBit */
                UINT8_C( 12 ), /* ComRxSignalFlags -- UINT16,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 16 ) /* ComBitSize */
            },
            UINT16_C( 65535 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[15] -- SGGearLmtForLightOff_289R */
            { /* RxBasicParam */
                UINT16_C( 1 ), /* ComIPduRef */
                UINT16_C( 38 ), /* ComSignalPositionInBit */
                UINT8_C( 14 ), /* ComRxSignalFlags -- UINT8,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 2 ) /* ComBitSize */
            },
            UINT16_C( 65535 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[16] -- SGWhlSpdFrntLeRaw_529R */
            { /* RxBasicParam */
                UINT16_C( 2 ), /* ComIPduRef */
                UINT16_C( 51 ), /* ComSignalPositionInBit */
                UINT8_C( 12 ), /* ComRxSignalFlags -- UINT16,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 12 ) /* ComBitSize */
            },
            UINT16_C( 2 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[17] -- SGWhlSpdFrntRiRaw_529R */
            { /* RxBasicParam */
                UINT16_C( 2 ), /* ComIPduRef */
                UINT16_C( 35 ), /* ComSignalPositionInBit */
                UINT8_C( 12 ), /* ComRxSignalFlags -- UINT16,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 12 ) /* ComBitSize */
            },
            UINT16_C( 65535 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[18] -- SGWhlSpdReLeRaw_529R */
            { /* RxBasicParam */
                UINT16_C( 2 ), /* ComIPduRef */
                UINT16_C( 19 ), /* ComSignalPositionInBit */
                UINT8_C( 12 ), /* ComRxSignalFlags -- UINT16,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 12 ) /* ComBitSize */
            },
            UINT16_C( 65535 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[19] -- SGWhlSpdReRiRaw_529R */
            { /* RxBasicParam */
                UINT16_C( 2 ), /* ComIPduRef */
                UINT16_C( 3 ), /* ComSignalPositionInBit */
                UINT8_C( 12 ), /* ComRxSignalFlags -- UINT16,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 12 ) /* ComBitSize */
            },
            UINT16_C( 65535 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[20] -- SGAbsCtrlActv_545R */
            { /* RxBasicParam */
                UINT16_C( 3 ), /* ComIPduRef */
                UINT16_C( 39 ), /* ComSignalPositionInBit */
                UINT8_C( 8 ), /* ComRxSignalFlags -- BOOLEAN,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 1 ) /* ComBitSize */
            },
            UINT16_C( 3 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[21] -- SGAbsFlgFlt_545R */
            { /* RxBasicParam */
                UINT16_C( 3 ), /* ComIPduRef */
                UINT16_C( 38 ), /* ComSignalPositionInBit */
                UINT8_C( 8 ), /* ComRxSignalFlags -- BOOLEAN,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 1 ) /* ComBitSize */
            },
            UINT16_C( 65535 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[22] -- SGEbdFlgFlt_545R */
            { /* RxBasicParam */
                UINT16_C( 3 ), /* ComIPduRef */
                UINT16_C( 37 ), /* ComSignalPositionInBit */
                UINT8_C( 8 ), /* ComRxSignalFlags -- BOOLEAN,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 1 ) /* ComBitSize */
            },
            UINT16_C( 65535 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[23] -- SGAlgt_561R */
            { /* RxBasicParam */
                UINT16_C( 4 ), /* ComIPduRef */
                UINT16_C( 39 ), /* ComSignalPositionInBit */
                UINT8_C( 9 ), /* ComRxSignalFlags -- SINT16,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 16 ) /* ComBitSize */
            },
            UINT16_C( 4 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[24] -- SGEscFlgFlt_561R */
            { /* RxBasicParam */
                UINT16_C( 4 ), /* ComIPduRef */
                UINT16_C( 13 ), /* ComSignalPositionInBit */
                UINT8_C( 8 ), /* ComRxSignalFlags -- BOOLEAN,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 1 ) /* ComBitSize */
            },
            UINT16_C( 65535 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[25] -- SGGearShiftPrevn_561R */
            { /* RxBasicParam */
                UINT16_C( 4 ), /* ComIPduRef */
                UINT16_C( 9 ), /* ComSignalPositionInBit */
                UINT8_C( 14 ), /* ComRxSignalFlags -- UINT8,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 2 ) /* ComBitSize */
            },
            UINT16_C( 65535 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[26] -- SGTcsCtrlActv_561R */
            { /* RxBasicParam */
                UINT16_C( 4 ), /* ComIPduRef */
                UINT16_C( 12 ), /* ComSignalPositionInBit */
                UINT8_C( 8 ), /* ComRxSignalFlags -- BOOLEAN,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 1 ) /* ComBitSize */
            },
            UINT16_C( 65535 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[27] -- SGTcsFlgFlt_561R */
            { /* RxBasicParam */
                UINT16_C( 4 ), /* ComIPduRef */
                UINT16_C( 14 ), /* ComSignalPositionInBit */
                UINT8_C( 8 ), /* ComRxSignalFlags -- BOOLEAN,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 1 ) /* ComBitSize */
            },
            UINT16_C( 65535 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[28] -- SGEngPAmbAir_609R */
            { /* RxBasicParam */
                UINT16_C( 5 ), /* ComIPduRef */
                UINT16_C( 7 ), /* ComSignalPositionInBit */
                UINT8_C( 14 ), /* ComRxSignalFlags -- UINT8,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 8 ) /* ComBitSize */
            },
            UINT16_C( 65535 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[29] -- SGEngT_609R */
            { /* RxBasicParam */
                UINT16_C( 5 ), /* ComIPduRef */
                UINT16_C( 15 ), /* ComSignalPositionInBit */
                UINT8_C( 14 ), /* ComRxSignalFlags -- UINT8,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 8 ) /* ComBitSize */
            },
            UINT16_C( 65535 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[30] -- SGEngineSoakTime_609R */
            { /* RxBasicParam */
                UINT16_C( 5 ), /* ComIPduRef */
                UINT16_C( 19 ), /* ComSignalPositionInBit */
                UINT8_C( 12 ), /* ComRxSignalFlags -- UINT16,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 12 ) /* ComBitSize */
            },
            UINT16_C( 5 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[31] -- SGOBDDrivingCycleStatus_609R */
            { /* RxBasicParam */
                UINT16_C( 5 ), /* ComIPduRef */
                UINT16_C( 55 ), /* ComSignalPositionInBit */
                UINT8_C( 8 ), /* ComRxSignalFlags -- BOOLEAN,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 1 ) /* ComBitSize */
            },
            UINT16_C( 65535 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[32] -- SGOBDWarmUpCycleStatus_609R */
            { /* RxBasicParam */
                UINT16_C( 5 ), /* ComIPduRef */
                UINT16_C( 54 ), /* ComSignalPositionInBit */
                UINT8_C( 8 ), /* ComRxSignalFlags -- BOOLEAN,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 1 ) /* ComBitSize */
            },
            UINT16_C( 65535 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        },
        { /* ComRxSignal[33] -- SGAmbAirTemp_641R */
            { /* RxBasicParam */
                UINT16_C( 6 ), /* ComIPduRef */
                UINT16_C( 7 ), /* ComSignalPositionInBit */
                UINT8_C( 14 ), /* ComRxSignalFlags -- UINT8,BIG_ENDIAN,COM_RX_DATA_TOUT_ACTION_NONE, */
                UINT8_C( 8 ) /* ComBitSize */
            },
            UINT16_C( 6 ), /* ComNotification */
            UINT16_C( 0 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT8_C( 1 ) /* ComFilterType */
        }
    },
    { /* ComTxSignal */
        { /* ComTxSignal[0] -- SGEngNIdleReq_321T */
            { /* TxBasicParam */
                UINT16_C( 0 ), /* ComIPduRef */
                UINT16_C( 32 ), /* ComSignalPositionInBit */
                UINT8_C( 14 ) /* ComTxSignalFlags -- UINT8,BIG_ENDIAN,PENDING,updateBit off */
            },
            UINT16_C( 65535 ), /* ComErrorNotification */
            UINT16_C( 65535 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT16_C( 0 ), /* ComPositionOfTMSFlag */
            UINT8_C( 8 ), /* ComBitSize */
            UINT8_C( 0 ) /* ComFilterType -- NEVER */
        },
        { /* ComTxSignal[1] -- SGEngTqIndDecReqdByTrsm_321T */
            { /* TxBasicParam */
                UINT16_C( 0 ), /* ComIPduRef */
                UINT16_C( 0 ), /* ComSignalPositionInBit */
                UINT8_C( 14 ) /* ComTxSignalFlags -- UINT8,BIG_ENDIAN,PENDING,updateBit off */
            },
            UINT16_C( 65535 ), /* ComErrorNotification */
            UINT16_C( 65535 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT16_C( 0 ), /* ComPositionOfTMSFlag */
            UINT8_C( 8 ), /* ComBitSize */
            UINT8_C( 0 ) /* ComFilterType -- NEVER */
        },
        { /* ComTxSignal[2] -- SGEngTqIndLmtdByTrsm_321T */
            { /* TxBasicParam */
                UINT16_C( 0 ), /* ComIPduRef */
                UINT16_C( 8 ), /* ComSignalPositionInBit */
                UINT8_C( 14 ) /* ComTxSignalFlags -- UINT8,BIG_ENDIAN,PENDING,updateBit off */
            },
            UINT16_C( 65535 ), /* ComErrorNotification */
            UINT16_C( 65535 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT16_C( 0 ), /* ComPositionOfTMSFlag */
            UINT8_C( 8 ), /* ComBitSize */
            UINT8_C( 0 ) /* ComFilterType -- NEVER */
        },
        { /* ComTxSignal[3] -- SGTrsmCluStAct_321T */
            { /* TxBasicParam */
                UINT16_C( 0 ), /* ComIPduRef */
                UINT16_C( 46 ), /* ComSignalPositionInBit */
                UINT8_C( 14 ) /* ComTxSignalFlags -- UINT8,BIG_ENDIAN,PENDING,updateBit off */
            },
            UINT16_C( 65535 ), /* ComErrorNotification */
            UINT16_C( 65535 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT16_C( 0 ), /* ComPositionOfTMSFlag */
            UINT8_C( 2 ), /* ComBitSize */
            UINT8_C( 0 ) /* ComFilterType -- NEVER */
        },
        { /* ComTxSignal[4] -- SGTrsmMsgCnt_321T */
            { /* TxBasicParam */
                UINT16_C( 0 ), /* ComIPduRef */
                UINT16_C( 56 ), /* ComSignalPositionInBit */
                UINT8_C( 14 ) /* ComTxSignalFlags -- UINT8,BIG_ENDIAN,PENDING,updateBit off */
            },
            UINT16_C( 65535 ), /* ComErrorNotification */
            UINT16_C( 65535 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT16_C( 0 ), /* ComPositionOfTMSFlag */
            UINT8_C( 4 ), /* ComBitSize */
            UINT8_C( 0 ) /* ComFilterType -- NEVER */
        },
        { /* ComTxSignal[5] -- SGTrsmNInp_321T */
            { /* TxBasicParam */
                UINT16_C( 0 ), /* ComIPduRef */
                UINT16_C( 24 ), /* ComSignalPositionInBit */
                UINT8_C( 12 ) /* ComTxSignalFlags -- UINT16,BIG_ENDIAN,PENDING,updateBit off */
            },
            UINT16_C( 65535 ), /* ComErrorNotification */
            UINT16_C( 65535 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT16_C( 0 ), /* ComPositionOfTMSFlag */
            UINT8_C( 16 ), /* ComBitSize */
            UINT8_C( 0 ) /* ComFilterType -- NEVER */
        },
        { /* ComTxSignal[6] -- SGEngTqIndIncReqdByTrsm_337T */
            { /* TxBasicParam */
                UINT16_C( 1 ), /* ComIPduRef */
                UINT16_C( 32 ), /* ComSignalPositionInBit */
                UINT8_C( 14 ) /* ComTxSignalFlags -- UINT8,BIG_ENDIAN,PENDING,updateBit off */
            },
            UINT16_C( 65535 ), /* ComErrorNotification */
            UINT16_C( 65535 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT16_C( 0 ), /* ComPositionOfTMSFlag */
            UINT8_C( 8 ), /* ComBitSize */
            UINT8_C( 0 ) /* ComFilterType -- NEVER */
        },
        { /* ComTxSignal[7] -- SGTrsmFlgFlt_337T */
            { /* TxBasicParam */
                UINT16_C( 1 ), /* ComIPduRef */
                UINT16_C( 9 ), /* ComSignalPositionInBit */
                UINT8_C( 14 ) /* ComTxSignalFlags -- UINT8,BIG_ENDIAN,PENDING,updateBit off */
            },
            UINT16_C( 65535 ), /* ComErrorNotification */
            UINT16_C( 65535 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT16_C( 0 ), /* ComPositionOfTMSFlag */
            UINT8_C( 2 ), /* ComBitSize */
            UINT8_C( 0 ) /* ComFilterType -- NEVER */
        },
        { /* ComTxSignal[8] -- SGTrsmFlgShiftProgs_337T */
            { /* TxBasicParam */
                UINT16_C( 1 ), /* ComIPduRef */
                UINT16_C( 15 ), /* ComSignalPositionInBit */
                UINT8_C( 8 ) /* ComTxSignalFlags -- BOOLEAN,BIG_ENDIAN,PENDING,updateBit off */
            },
            UINT16_C( 65535 ), /* ComErrorNotification */
            UINT16_C( 65535 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT16_C( 0 ), /* ComPositionOfTMSFlag */
            UINT8_C( 1 ), /* ComBitSize */
            UINT8_C( 0 ) /* ComFilterType -- NEVER */
        },
        { /* ComTxSignal[9] -- SGTrsmGearAct_337T */
            { /* TxBasicParam */
                UINT16_C( 1 ), /* ComIPduRef */
                UINT16_C( 0 ), /* ComSignalPositionInBit */
                UINT8_C( 14 ) /* ComTxSignalFlags -- UINT8,BIG_ENDIAN,PENDING,updateBit off */
            },
            UINT16_C( 65535 ), /* ComErrorNotification */
            UINT16_C( 65535 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT16_C( 0 ), /* ComPositionOfTMSFlag */
            UINT8_C( 4 ), /* ComBitSize */
            UINT8_C( 0 ) /* ComFilterType -- NEVER */
        },
        { /* ComTxSignal[10] -- SGTrsmGearTar_337T */
            { /* TxBasicParam */
                UINT16_C( 1 ), /* ComIPduRef */
                UINT16_C( 4 ), /* ComSignalPositionInBit */
                UINT8_C( 14 ) /* ComTxSignalFlags -- UINT8,BIG_ENDIAN,PENDING,updateBit off */
            },
            UINT16_C( 65535 ), /* ComErrorNotification */
            UINT16_C( 65535 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT16_C( 0 ), /* ComPositionOfTMSFlag */
            UINT8_C( 4 ), /* ComBitSize */
            UINT8_C( 0 ) /* ComFilterType -- NEVER */
        },
        { /* ComTxSignal[11] -- SGTrsmMILReq_337T */
            { /* TxBasicParam */
                UINT16_C( 1 ), /* ComIPduRef */
                UINT16_C( 8 ), /* ComSignalPositionInBit */
                UINT8_C( 8 ) /* ComTxSignalFlags -- BOOLEAN,BIG_ENDIAN,PENDING,updateBit off */
            },
            UINT16_C( 65535 ), /* ComErrorNotification */
            UINT16_C( 65535 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT16_C( 0 ), /* ComPositionOfTMSFlag */
            UINT8_C( 1 ), /* ComBitSize */
            UINT8_C( 0 ) /* ComFilterType -- NEVER */
        },
        { /* ComTxSignal[12] -- SGTrsmStGearLvr_337T */
            { /* TxBasicParam */
                UINT16_C( 1 ), /* ComIPduRef */
                UINT16_C( 11 ), /* ComSignalPositionInBit */
                UINT8_C( 14 ) /* ComTxSignalFlags -- UINT8,BIG_ENDIAN,PENDING,updateBit off */
            },
            UINT16_C( 65535 ), /* ComErrorNotification */
            UINT16_C( 65535 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT16_C( 0 ), /* ComPositionOfTMSFlag */
            UINT8_C( 4 ), /* ComBitSize */
            UINT8_C( 0 ) /* ComFilterType -- NEVER */
        },
        { /* ComTxSignal[13] -- SGTrsmStGearMode_337T */
            { /* TxBasicParam */
                UINT16_C( 1 ), /* ComIPduRef */
                UINT16_C( 21 ), /* ComSignalPositionInBit */
                UINT8_C( 14 ) /* ComTxSignalFlags -- UINT8,BIG_ENDIAN,PENDING,updateBit off */
            },
            UINT16_C( 65535 ), /* ComErrorNotification */
            UINT16_C( 65535 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT16_C( 0 ), /* ComPositionOfTMSFlag */
            UINT8_C( 3 ), /* ComBitSize */
            UINT8_C( 0 ) /* ComFilterType -- NEVER */
        },
        { /* ComTxSignal[14] -- SGTrsmTOil_337T */
            { /* TxBasicParam */
                UINT16_C( 1 ), /* ComIPduRef */
                UINT16_C( 24 ), /* ComSignalPositionInBit */
                UINT8_C( 14 ) /* ComTxSignalFlags -- UINT8,BIG_ENDIAN,PENDING,updateBit off */
            },
            UINT16_C( 65535 ), /* ComErrorNotification */
            UINT16_C( 65535 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT16_C( 0 ), /* ComPositionOfTMSFlag */
            UINT8_C( 8 ), /* ComBitSize */
            UINT8_C( 0 ) /* ComFilterType -- NEVER */
        },
        { /* ComTxSignal[15] -- SGTrsmTOilWrnLmpReq_337T */
            { /* TxBasicParam */
                UINT16_C( 1 ), /* ComIPduRef */
                UINT16_C( 20 ), /* ComSignalPositionInBit */
                UINT8_C( 8 ) /* ComTxSignalFlags -- BOOLEAN,BIG_ENDIAN,PENDING,updateBit off */
            },
            UINT16_C( 65535 ), /* ComErrorNotification */
            UINT16_C( 65535 ), /* ComFilterRef */
            UINT16_C( 65535 ), /* ComFilterSignalValueRef */
            UINT16_C( 0 ), /* ComPositionOfTMSFlag */
            UINT8_C( 1 ), /* ComBitSize */
            UINT8_C( 0 ) /* ComFilterType -- NEVER */
        }
    },
    { /* ComRxTimeoutNotificationList */
        UINT16_C( 0 ), /* ComRxTimeoutNotificationList[0] */
        UINT16_C( 1 ), /* ComRxTimeoutNotificationList[1] */
        UINT16_C( 2 ), /* ComRxTimeoutNotificationList[2] */
        UINT16_C( 3 ), /* ComRxTimeoutNotificationList[3] */
        UINT16_C( 4 ), /* ComRxTimeoutNotificationList[4] */
        UINT16_C( 5 ), /* ComRxTimeoutNotificationList[5] */
        UINT16_C( 6 ) /* ComRxTimeoutNotificationList[6] */
    },
    { /* ComPeriodicQueueList */
        UINT16_C( 0 ), /* ComPeriodicQueueList[0] */
        UINT16_C( 1 ) /* ComPeriodicQueueList[1] */
    },
    { /* ComRxTimeoutQueueList */
        UINT16_C( 0 ), /* ComRxTimeoutQueueList[0] */
        UINT16_C( 1 ), /* ComRxTimeoutQueueList[1] */
        UINT16_C( 2 ), /* ComRxTimeoutQueueList[2] */
        UINT16_C( 3 ), /* ComRxTimeoutQueueList[3] */
        UINT16_C( 4 ), /* ComRxTimeoutQueueList[4] */
        UINT16_C( 5 ), /* ComRxTimeoutQueueList[5] */
        UINT16_C( 6 ) /* ComRxTimeoutQueueList[6] */
    },
    { /* ComCbkTxAckDeferredList */
        UINT16_C( 0 ), /* ComCbkTxAckDeferredList[0] */
        UINT16_C( 1 ) /* ComCbkTxAckDeferredList[1] */
    },
    { /* ComIPduGroupMask */
        UINT8_C( 5 ), /* ComIPduGroupMask[0] -- [0][0] RXPDUS_GLOBAL RGCanNetwork */
        UINT8_C( 10 ) /* ComIPduGroupMask[1] -- [1][0] TXPDUS_GLOBAL TGCanNetwork */
    },
    { /* ComIPduInit */
        UINT8_C( 0 ), /* ComIPduInit[0] */
        UINT8_C( 0 ), /* ComIPduInit[1] */
        UINT8_C( 0 ), /* ComIPduInit[2] */
        UINT8_C( 0 ), /* ComIPduInit[3] */
        UINT8_C( 0 ), /* ComIPduInit[4] */
        UINT8_C( 0 ), /* ComIPduInit[5] */
        UINT8_C( 0 ), /* ComIPduInit[6] */
        UINT8_C( 0 ) /* ComIPduInit[7] */
    }
};

/* Deviation MISRA-2, MISRA-3 <STOP> */

#define COM_STOP_CONFIG_DATA_UNSPECIFIED
#include <MemMap.h>

/*==================[internal constants]=====================================*/


/*==================[external data]==========================================*/


/*==================[internal data]==========================================*/


/*==================[external function definitions]==========================*/


/*==================[internal function definitions]==========================*/


/*==================[end of file]============================================*/

