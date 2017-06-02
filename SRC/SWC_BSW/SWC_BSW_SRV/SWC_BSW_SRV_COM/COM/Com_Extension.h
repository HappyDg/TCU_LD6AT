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

/* Misra-C:2004 Deviations:
 *
 * MISRA-1) Deviated Rule: 14.7 (required)
 * "A function shall have a single point of exit at the end of the function."
 *
 * Reason:
 * Point of exits exists only if DET is enabled.
 *
 *
 * MISRA-2) Deviated Rule: 17.4 (required)
 * "Array indexing shall be the only allowed form of pointer arithmetic."
 *
 * Reason:
 * Calculation is needed to get the index of the Signal Group to which the
 * Group Signal belongs.
 *
 * MISRA-3) Deviated Rule: 19.10 (required)
 * Parameter instance shall be enclosed in parentheses.
 *
 * Reason:
 * Enclosing the paramter in parentheses is not possible, because it results
 * in compiler syntax error.
 */

#if (!defined COM_EXTENSION_H)
#define COM_EXTENSION_H

/*==================[inclusions]============================================*/

#include <TSAutosar.h>          /* EB specific standard types */
#include <Com_Rules.h>          /* Generated configuration + derived rules */
#include <Com_Api.h>            /* get module interface */
#include <SchM_Com.h>           /* Header of Schedule Manager for Com */
#include <stddef.h>             /* ptrdiff_t */
#include <TSMem.h>

/*==================[checks]================================================*/

/*==================[macros]================================================*/


#if (COM_TX_MODE_TIME_OFFSET_FACTOR_SIZE == COM_SIZE_0_BIT)
#define COM_GET_TM_TIME_OFFSET_FACTOR(tmPtr) 0U
#else
#define COM_GET_TM_TIME_OFFSET_FACTOR(tmPtr) (tmPtr)->ComTxModeTimeOffsetFactor
#endif

/** \brief Define COM_CALC_MASK generates a bit mask which is maximum
 * 32 bits
 * \param[in] type - the data type of the mask
 * \param[in] position - position of the mask
 * (LSB = 0, MSB = (sizeof(type)*8-1)
 * \param[in] num_bits - number of 1 in the mask
 * \retval generated mask */
#define COM_CALC_MASK(type, position, num_bits) \
    ( (type) (((uint32) (UINT32_C(0xFFFFFFFF) >> ((32U) - (num_bits))) ) << (position) ))

#if (COM_RX_SIG_CONF_IMMEDIATE_ENABLE == STD_ON)
#if (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON)
/** \brief Define COM_GET_COM_RX_IPDU_SIGNAL_PROCESSING returns the
 * processing of the indications of the signals within the I-Pdu
 * (COM_DEFERED/COM_IMMEDIATE)
 * \param[in] ipdu - reference to the Rx-Ipdu
 * \retval processing flag (COM_DEFERED/COM_IMMEDIATE) */
#define COM_GET_COM_RX_IPDU_SIGNAL_PROCESSING(ipdu) \
   ((uint8)((uint8)((ipdu)->ComRxIPduFlags) & 0x1U ))
#endif /* (COM_RX_SIG_CONF_IMMEDIATE_ENABLE == STD_ON) */
#endif /* (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON) */

#if (COM_RX_TIMEOUT_FACTOR_AVAILABLE == STD_ON)
/** \brief Define COM_GET_COM_RX_IPDU_DM returns if deadline monitoring is
 * configured for the I-Pdu
 * \param[in] ipdu - reference to the Rx-Ipdu
 * \retval deadline monitoring flag (COM_RX_DM_ON/COM_RX_DM_OFF) */
#define COM_GET_COM_RX_IPDU_DM(ipdu) \
   ((uint8)((uint8)((ipdu)->ComRxIPduFlags>>1U) & 0x1U ))
#endif /* (COM_RX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) */


/** \brief Define COM_GET_COM_TX_IPDU_SIGNAL_PROCESSING returns the
 * processing of the indications of the signals within the I-Pdu
 * (COM_DEFERED/COM_IMMEDIATE)
 * \param[in] ipdu - reference to the Tx-Ipdu
 * \retval processing flag (COM_DEFERED/COM_IMMEDIATE) */
#define COM_GET_COM_TX_IPDU_SIGNAL_PROCESSING(ipdu) \
   ((uint8)((uint8)((ipdu)->ComTxIPduFlags) & 0x1U ))

/** \brief Define COM_GET_COM_TX_IPDU_DM_AVAILABLE returns if deadline
 * monitoring is configured for the I-Pdu
 * \param[in] ipdu - reference to the Tx-Ipdu
 * \retval deadline monitoring flag (COM_TX_DM_ON/COM_TX_DM_OFF) */
#define COM_GET_COM_TX_IPDU_DM_AVAILABLE(ipdu) \
   ((uint8)((uint8)((ipdu)->ComTxIPduFlags>>1U) & 0x1U ))

/** \brief Define COM_GET_COM_TX_IPDU_INIT_TM returns the initial
 * transmission mode of the Tx-IPdu
 * \param[in] ipdu - reference to the Tx-Ipdu
 * \retval initial transmission mode flag (TM_TRUE/TM_FALSE) */
#define COM_GET_COM_TX_IPDU_INIT_TM(ipdu) \
   ((uint8)((uint8)((ipdu)->ComTxIPduFlags>>2U) & 0x1U ))


/** \brief Define COM_GET_COM_TX_IPDU_CLEAR_UPDATE_BITS returns during which
 * function call the update bits shall be cleared
 * \param[in] ipdu - reference to the Tx-Ipdu
 * \retval ClearUpdateBit  (COM_CL_UB_TRANSMIT,
 * COM_CL_UB_TRIGGERTRANSMIT, COM_CL_UB_CONFIRMATION, COM_CL_UB_NEVER) */
#define COM_GET_COM_TX_IPDU_CLEAR_UPDATE_BIT(ipdu) \
   ((uint8)((uint8)((ipdu)->ComTxIPduFlags>>3U) & 0x3U ))


/** \brief Define COM_GET_IPDU_GROUP_TYPE returns the type of the I-Pdu group
 * \param[in] IPduGroupPtr - reference to the Ipdu group
 * \retval type of the Ipdu group (COM_IPDU_GROUP_GROUP/COM_IPDU_GROUP_IPDU) */
#define COM_GET_IPDU_GROUP_TYPE(IPduGroupPtr) \
   ((uint8)(((IPduGroupPtr)->ComIPduGroupFlags) & 0x1U ))

/** \brief Define COM_GET_IPDU_GROUP_DIRECTION returns the direction  of the
 * I-Pdu group
 * \param[in] IPduGroupPtr - reference to the Ipdu group
 * \retval direction of the Ipdu group (COM_RECEIVE/COM_SEND) */
#define COM_GET_IPDU_GROUP_DIRECTION(IPduGroupPtr) \
   ((uint8)((uint8)((IPduGroupPtr)->ComIPduGroupFlags>>1U) & 0x1U ))


#if (COM_TX_IPDU_MINIMUM_DELAY_TIME_FACTOR_SIZE != COM_SIZE_0_BIT)
#if (COM_TX_IPDU_MINIMUM_DELAY_TIME_FACTOR_STORAGE == COM_STORAGE_REFERENCE)

/** \brief Define COM_GET_MDT gets the the minimum delay time value of a I-Pdu
 * \param[in] ipduPtr - reference to the I-Pdu
 * \retval value of MDT */
#define COM_GET_MDT(ipduPtr) \
   (*(COM_GET_CONFIG_ELEMENT(ComTxIPduMinimumDelayTimeFactorType, \
         Com_gConfigPtr->ComTxIPduMinimumDelayTimeFactorRef, \
         (ipduPtr)->ComTxIPduMinimumDelayTimeFactorRef)))
#endif

#if (COM_TX_IPDU_MINIMUM_DELAY_TIME_FACTOR_STORAGE == COM_STORAGE_DIRECT)

/** \brief Define COM_GET_MDT gets the minimum delay time value of a I-Pdu
 * \param[in] ipduPtr - reference to the I-Pdu
 * \retval value of MDT */
#define COM_GET_MDT(ipduPtr) \
   ((ComTxIPduMinimumDelayTimeFactorType) (ipduPtr)->ComTxIPduMinimumDelayTimeFactorValue)
#endif /* (COM_TX_IPDU_MINIMUM_DELAY_TIME_FACTOR_STORAGE == COM_STORAGE_DIRECT) */
#endif /* (COM_TX_IPDU_MINIMUM_DELAY_TIME_FACTOR_SIZE != COM_SIZE_0_BIT) */


#if (COM_TM_AVAILABLE == STD_ON)

/** \brief Define COM_GET_COM_TX_MODE gets the transmission mode of a I-Pdu
 * \param[in] TM - TM which should be returned (TRUE/FALSE)
 * \param[in] ComTxModeModes - reference of the I-Pdu where the transmission
 * modes are stored
 * \retval value of TM (COM_TX_MODE_MODE_NONE/COM_TX_MODE_MODE_PERIODIC/
 * COM_TX_MODE_MODE_DIRECT/COM_TX_MODE_MODE_MIXED_DIRECT/
 * COM_TX_MODE_MODE_MIXED_N/COM_TX_MODE_MODE_N_TIMES) */
#define COM_GET_COM_TX_MODE(TM, ComTxModeModes) \
   (((TM) == TRUE) ? (COM_GET_COM_TX_MODE_TRUE(ComTxModeModes)) : \
         (COM_GET_COM_TX_MODE_FALSE(ComTxModeModes)))

/** \brief Define COM_GET_COM_TX_MODE_INV gets the inverted transmission mode
 * of a I-Pdu
 * \param[in] TM - TM which should be returned (if TRUE, TM FALSE is returned;
 * if FALSE, TM TRUE is returned)
 * \param[in] ComTxModeModes - reference of the I-Pdu where the transmission
 * modes are stored
 * \retval value of TM (COM_TX_MODE_MODE_NONE/COM_TX_MODE_MODE_PERIODIC/
 * COM_TX_MODE_MODE_DIRECT/COM_TX_MODE_MODE_MIXED_DIRECT/
 * COM_TX_MODE_MODE_MIXED_N/COM_TX_MODE_MODE_N_TIMES) */
#define COM_GET_COM_TX_MODE_INV(TM, ComTxModeModes) \
   (((TM) == FALSE) ? (COM_GET_COM_TX_MODE_TRUE(ComTxModeModes)) : \
         (COM_GET_COM_TX_MODE_FALSE(ComTxModeModes)))

/** \brief Define COM_GET_COM_TX_MODE_TRUE gets the transmission mode TRUE
 * of a I-Pdu
 * \param[in] ComTxModeModes - reference of the I-Pdu where the transmission
 * modes are stored
 * \retval value of TM (COM_TX_MODE_MODE_NONE/COM_TX_MODE_MODE_PERIODIC/
 * COM_TX_MODE_MODE_DIRECT/COM_TX_MODE_MODE_MIXED_DIRECT/
 * COM_TX_MODE_MODE_MIXED_N/COM_TX_MODE_MODE_N_TIMES) */
#define COM_GET_COM_TX_MODE_TRUE(ComTxModeModes) \
   ((uint8)((ComTxModeModes) & (0xFU)))

/** \brief Define COM_GET_COM_TX_MODE_TRUE gets the transmission mode FALSE
 * of a I-Pdu
 * \param[in] ComTxModeModes - reference of the I-Pdu where the transmission
 * modes are stored
 * \retval value of TM (COM_TX_MODE_MODE_NONE/COM_TX_MODE_MODE_PERIODIC/
 * COM_TX_MODE_MODE_DIRECT/COM_TX_MODE_MODE_MIXED_DIRECT/
 * COM_TX_MODE_MODE_MIXED_N/COM_TX_MODE_MODE_N_TIMES) */
#define COM_GET_COM_TX_MODE_FALSE(ComTxModeModes) \
   ((uint8)((uint8)((ComTxModeModes)>>4U) & (0xFU)))

/** \brief Define COM_GET_COM_TX_MODE_REF_TRUE gets the reference of the
 * configuration of the transmission mode TRUE of a I-Pdu
 * \param[in] IPduPtr - reference ot the I-Pdu
 * \retval reference to the TM TRUE */
#define COM_GET_COM_TX_MODE_REF_TRUE(IPduPtr) \
   ((ComTxModeIdxType)(IPduPtr)->ComTxModeTrueRef)


/** \brief Define COM_GET_COM_TX_MODE_REF_FALSE gets the reference of the
 * configuration of the transmission mode FALSE of a I-Pdu
 * \param[in] IPduPtr - reference ot the I-Pdu
 * \retval reference to the TM FALSE (is always COM_TX_MODE_INVALID if TM
 * selection is disabled) */
#if (COM_TMS_ENABLE == STD_ON)
#define COM_GET_COM_TX_MODE_REF_FALSE(IPduPtr) \
         ((ComTxModeIdxType)(IPduPtr)->ComTxModeFalseRef)
#else
#define COM_GET_COM_TX_MODE_REF_FALSE(IPduPtr) COM_TX_MODE_INVALID
#endif /* (COM_TMS_ENABLE == STD_ON) */

/** \brief Define COM_GET_COM_TX_MODE_REF gets the reference of the
 * configuration of the transmission mode of a I-Pdu
 * \param[in] TM - defines which reference should be returned (TRUE/FALSE)
 * \param[in] IPduPtr - reference ot the I-Pdu
 * \retval reference to the TM specified in TM (In case TM == FALSE and
 * TM selection is disabled COM_TX_MODE_INVALID is returned) */
#define COM_GET_COM_TX_MODE_REF(TM, IPduPtr) \
   (((TM) == TRUE)?(COM_GET_COM_TX_MODE_REF_TRUE(IPduPtr)) : \
         (COM_GET_COM_TX_MODE_REF_FALSE(IPduPtr)))

#endif /* (COM_TM_AVAILABLE == STD_ON) */


#if (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
#if (COM_RX_DATA_TOUT_ACTION == COM_RX_DATA_TOUT_ACTION_CONFIG)
/** \brief Define COM_GET_RX_SIGNAL_GROUP_TIMEOUT_ACTION returns the defined
 * action in case of RxDM timeout
 * \param[in] signalGPtr - reference to the signal group
 * \retval timeout action of the signal group (COM_RX_DATA_TOUT_ACTION_NONE/
 * COM_RX_DATA_TOUT_ACTION_REPLACE) */
#define COM_GET_RX_SIGNAL_GROUP_TIMEOUT_ACTION(signalGPtr) \
   ((boolean)((uint8)((signalGPtr)->ComRxSignalGroupFlags) & 0x1U))
#endif /* (COM_RX_DATA_TOUT_ACTION == COM_RX_DATA_TOUT_ACTION_CONFIG) */

#if (COM_UPDATE_BIT_RX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL)
/** \brief Define COM_GET_RX_SIGNAL_GROUP_UPDATE_BIT returns the presence of
 * an update bit for the signal group
 * \param[in] signalGPtr - reference to the signal group
 * \retval presence of an update bit for the signal group
 * (COM_UPDATE_BIT_ABSENT/COM_UPDATE_BIT_PRESENT) */
#define COM_GET_RX_SIGNAL_GROUP_UPDATE_BIT(signalGPtr) \
   ((boolean)((uint8)(((signalGPtr)->ComRxSignalGroupFlags)>>1U) & 0x1U))
#endif /* (COM_UPDATE_BIT_RX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL) */

#if (COM_RX_SIGNAL_BASED_DM == STD_ON)
/** \brief Define COM_GET_RX_SIGNAL_GROUP_DM returns if
 * the a signal group based RxDM is configured for the signal group
 * \param[in] signalGPtr - reference to the signal group
 * \retval TRUE if invalid value equals init value, else FALSE
 * (COM_RX_DM_ON/COM_RX_DM_OFF) */
#define COM_GET_RX_SIGNAL_GROUP_DM(signalGPtr) \
   ((boolean)((uint8)(((signalGPtr)->ComRxSignalGroupFlags)>>2U) & 0x1U))
#endif /* (COM_RX_SIGNAL_BASED_DM == STD_ON) */


/* calculate the RAM buffer of signal groups for signal base DM */
#if (COM_RX_SIGNAL_BASED_DM == STD_ON)


/** \brief Define COM_RX_SIGNAL_GROUP_BYTE_POS returns the byte position of the
 * flags of the signal group
 * \param[in] SignalGPtr - reference to the signal group
 * \retval address of the byte where the flags of the signal group are stored */
#define COM_RX_SIGNAL_GROUP_BYTE_POS(SignalGPtr) \
   (&Com_gDataMemPtr[(Com_gConfigPtr->ComRxDMInvSignalGroupStatusQueueBase + \
         ((SignalGPtr)->RxGroupSignalFlagsRef / 4U))])

/** \brief Define COM_RX_SIGNAL_GROUP_BIT_POS returns the bit position of the
 * flags of the signal group
 * \param[in] SignalGPtr - reference to the signal group
 * \retval position of the first flag of the signal group within a byte */
#define COM_RX_SIGNAL_GROUP_BIT_POS(SignalGPtr) \
   ((((SignalGPtr)->RxGroupSignalFlagsRef) % 4U) * \
         2U)

/** \brief Define COM_RX_SIGNAL_GROUP_DM_FLAGS_BYTE_POS,
 * COM_RX_SIGNAL_GROUP_DM_TIMEOUT_BIT_POS,
 * COM_RX_SIGNAL_GROUP_DM_RUNNING_BIT_POS return the the bit and byte position
 * of the DM timeout flag and the DM enable flag of a signal group
 * \param[in] SignalGPtr - reference to the signal group
 * \retval position of the DM flags the signal group */
#if (COM_RX_SIGNAL_BASED_DM == STD_ON)
#define COM_RX_SIGNAL_GROUP_DM_FLAGS_BYTE_POS(SignalGPtr) \
   (COM_RX_SIGNAL_GROUP_BYTE_POS(SignalGPtr))
#define COM_RX_SIGNAL_GROUP_DM_TIMEOUT_BIT_POS(SignalGPtr) \
   (COM_RX_SIGNAL_GROUP_BIT_POS(SignalGPtr))
#define COM_RX_SIGNAL_GROUP_DM_RUNNING_BIT_POS(SignalGPtr) \
   (COM_RX_SIGNAL_GROUP_BIT_POS(SignalGPtr)+ 1U)
#endif /* (COM_RX_SIGNAL_BASED_DM == STD_ON) */


#endif /* (COM_RX_SIGNAL_BASED_DM == STD_ON) */
#endif /* (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */


#if (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
#if (COM_TM_AVAILABLE == STD_ON)
#define COM_GET_COM_TX_SIGNAL_GROUP_TRANSFER_PROPERTY(signalGPtr) \
   ((uint8)((uint8)((signalGPtr)->ComTxSignalGroupFlags) & (0x3U)))
#endif

#if (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL)
#define COM_GET_TX_SIGNAL_GROUP_UPDATE_BIT(signalGPtr) \
   ((uint8)((uint8)(((signalGPtr)->ComTxSignalGroupFlags)>>2U) & (0x1U)))
#endif
#endif /* (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */


#if (COM_RX_FIRST_TIMEOUT_FACTOR_SIZE != COM_SIZE_0_BIT)

/** \brief COM_GET_RX_FIRST_TIMEOUT_FACTOR
 * gets the Rx First Timeout Factor of an IPdu
 * Preconditions:
 * - a Timeout Factor has to be configured for the IPdu
 * \param[in] IPduPtr configuration of the IPdu
 * \retval Rx First Timeout Factor */

#if (COM_RX_TIMEOUT_FACTOR_STORAGE == COM_STORAGE_REFERENCE)

#define COM_GET_RX_FIRST_TIMEOUT_FACTOR(ipduPtr) \
   (*(COM_GET_CONFIG_ELEMENT(ComRxFirstTimeoutFactorType, \
         Com_gConfigPtr->ComRxFirstTimeoutFactorRef, \
         (ipduPtr)->ComRxFirstTimeoutFactorRef)))
#endif /* (COM_RX_TIMEOUT_FACTOR_STORAGE == COM_STORAGE_REFERENCE) */

#if (COM_RX_TIMEOUT_FACTOR_STORAGE == COM_STORAGE_DIRECT)

#define COM_GET_RX_FIRST_TIMEOUT_FACTOR(IPduPtr) \
   ((ComRxFirstTimeoutFactorType)((IPduPtr)->ComRxFirstTimeoutFactorValue))

#endif /* (COM_RX_TIMEOUT_FACTOR_STORAGE == COM_STORAGE_DIRECT) */


#if (COM_RX_SIGNAL_BASED_DM == STD_ON)

/** \brief COM_GET_RX_SIGNAL_FIRST_TIMEOUT_FACTOR
 * gets the Rx First Timeout Factor of an Signal
 * Preconditions:
 * - a Timeout Factor has to be configured for the Signal
 * \param[in] signalPtr configuration of the signal
 * \retval Rx First Timeout Factor */

#if (COM_RX_TIMEOUT_FACTOR_STORAGE == COM_STORAGE_REFERENCE)

#define COM_GET_RX_SIGNAL_FIRST_TIMEOUT_FACTOR(signalPtr) \
   (*(COM_GET_CONFIG_ELEMENT(ComRxFirstTimeoutFactorType, \
         Com_gConfigPtr->ComRxFirstTimeoutFactorRef, \
         (signalPtr)->ComRxFirstTimeoutFactorRef)))

#endif /* (COM_RX_TIMEOUT_FACTOR_STORAGE == COM_STORAGE_REFERENCE) */

#if (COM_RX_TIMEOUT_FACTOR_STORAGE == COM_STORAGE_DIRECT)

#define COM_GET_RX_SIGNAL_FIRST_TIMEOUT_FACTOR(signalPtr) \
   ((ComRxFirstTimeoutFactorType)((signalPtr)->ComRxFirstTimeoutFactorValue))

#endif /* (COM_RX_TIMEOUT_FACTOR_STORAGE == COM_STORAGE_DIRECT) */


#if (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
/** \brief COM_GET_RX_SIGNAL_GROUP_FIRST_TIMEOUT_FACTOR
 * gets the Rx First Timeout Factor of an Signal Group
 * Preconditions:
 * - a Timeout Factor has to be configured for the Signal Group
 * \param[in] signalGPtr configuration of the signal group
 * \retval Rx First Timeout Factor */


#if (COM_RX_TIMEOUT_FACTOR_STORAGE == COM_STORAGE_REFERENCE)

#define COM_GET_RX_SIGNAL_GROUP_FIRST_TIMEOUT_FACTOR(signalGPtr) \
   (*(COM_GET_CONFIG_ELEMENT(ComRxFirstTimeoutFactorType, \
         Com_gConfigPtr->ComRxFirstTimeoutFactorRef, \
         (signalGPtr)->ComRxFirstTimeoutFactorRef)))

#endif /* (COM_RX_TIMEOUT_FACTOR_STORAGE == COM_STORAGE_REFERENCE) */

#if (COM_RX_TIMEOUT_FACTOR_STORAGE == COM_STORAGE_DIRECT)

#define COM_GET_RX_SIGNAL_GROUP_FIRST_TIMEOUT_FACTOR(signalGPtr) \
   ((ComRxFirstTimeoutFactorType)((signalGPtr)->ComRxFirstTimeoutFactorValue))

#endif /* (COM_RX_TIMEOUT_FACTOR_STORAGE == COM_STORAGE_DIRECT) */

#endif /* (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

#endif /* (COM_RX_SIGNAL_BASED_DM == STD_ON) */

#endif /* (COM_RX_FIRST_TIMEOUT_FACTOR_SIZE != COM_SIZE_0_BIT) */



#if (COM_RX_TIMEOUT_FACTOR_AVAILABLE == STD_ON)


/** \brief COM_GET_RX_TIMEOUT_FACTOR
 * gets the Rx Timeout Factor of an IPdu
 * Preconditions:
 * - a Timeout Factor has to be configured for the IPdu
 * \param[in] IPduPtr configuration of the IPdu
 * \retval Rx Timeout Factor */

#if (COM_RX_TIMEOUT_FACTOR_STORAGE == COM_STORAGE_REFERENCE)

#define COM_GET_RX_TIMEOUT_FACTOR(ipduPtr) \
   (*(COM_GET_CONFIG_ELEMENT(ComRxTimeoutFactorType, Com_gConfigPtr->ComRxTimeoutFactorRef, \
         (ipduPtr)->ComRxTimeoutFactorRef)))

#endif /* (COM_RX_TIMEOUT_FACTOR_STORAGE == COM_STORAGE_REFERENCE) */

#if (COM_RX_TIMEOUT_FACTOR_STORAGE == COM_STORAGE_DIRECT)

#define COM_GET_RX_TIMEOUT_FACTOR(IPduPtr) \
   ((ComRxTimeoutFactorType)((IPduPtr)->ComRxTimeoutFactorValue))

#endif /* (COM_RX_TIMEOUT_FACTOR_STORAGE == COM_STORAGE_DIRECT) */


#if (COM_RX_SIGNAL_BASED_DM == STD_ON)

/** \brief COM_GET_RX_SIGNAL_TIMEOUT_FACTOR
 * gets the Rx Timeout Factor of an Signal
 * Preconditions:
 * - a Timeout Factor has to be configured for the Signal
 * \param[in] signalPtr configuration of the signal
 * \retval Rx Timeout Factor */

#if (COM_RX_TIMEOUT_FACTOR_STORAGE == COM_STORAGE_REFERENCE)

#define COM_GET_RX_SIGNAL_TIMEOUT_FACTOR(signalPtr) \
   (*(COM_GET_CONFIG_ELEMENT(ComRxTimeoutFactorType, \
         Com_gConfigPtr->ComRxTimeoutFactorRef, (signalPtr)->ComRxTimeoutFactorRef)))

#endif /* (COM_RX_TIMEOUT_FACTOR_STORAGE == COM_STORAGE_REFERENCE) */

#if (COM_RX_TIMEOUT_FACTOR_STORAGE == COM_STORAGE_DIRECT)

#define COM_GET_RX_SIGNAL_TIMEOUT_FACTOR(signalPtr) \
   ((ComRxTimeoutFactorType)((signalPtr)->ComRxTimeoutFactorValue))

#endif /* (COM_RX_TIMEOUT_FACTOR_STORAGE == COM_STORAGE_DIRECT) */


#if (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
/** \brief COM_GET_RX_SIGNAL_GROUP_TIMEOUT_FACTOR
 * gets the Rx Timeout Factor of an Signal Group
 * Preconditions:
 * - a Timeout Factor has to be configured for the Signal Group
 * \param[in] signalGPtr configuration of the signal group
 * \retval Rx Timeout Factor */

#if (COM_RX_TIMEOUT_FACTOR_STORAGE == COM_STORAGE_REFERENCE)

#define COM_GET_RX_SIGNAL_GROUP_TIMEOUT_FACTOR(signalGPtr) \
   (*(COM_GET_CONFIG_ELEMENT(ComRxTimeoutFactorType, \
         Com_gConfigPtr->ComRxTimeoutFactorRef, (signalGPtr)->ComRxTimeoutFactorRef)))

#endif /* (COM_RX_TIMEOUT_FACTOR_STORAGE == COM_STORAGE_REFERENCE) */

#if (COM_RX_TIMEOUT_FACTOR_STORAGE == COM_STORAGE_DIRECT)

#define COM_GET_RX_SIGNAL_GROUP_TIMEOUT_FACTOR(signalGPtr) \
   ((ComRxTimeoutFactorType)((signalGPtr)->ComRxTimeoutFactorValue))

#endif /* (COM_RX_TIMEOUT_FACTOR_STORAGE == COM_STORAGE_DIRECT) */

#endif /* (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

#endif /* (COM_RX_SIGNAL_BASED_DM == STD_ON) */

#endif /* (COM_RX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) */



#if (COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON)

/** \brief COM_GET_TX_TIMEOUT_FACTOR
 * gets the Tx Timeout Factor of an IPdu
 * Preconditions:
 * - a Timeout Factor has to be configured for the IPdu
 * \param[in] IPduPtr configuration of the IPdu
 * \retval Tx Timeout Factor */
#if (COM_TX_TIMEOUT_FACTOR_STORAGE == COM_STORAGE_REFERENCE)

#define COM_GET_TX_TIMEOUT_FACTOR(IPduPtr) \
   (*(COM_GET_CONFIG_ELEMENT(ComTxTimeoutFactorType, \
         Com_gConfigPtr->ComTxTimeoutFactorRef, (IPduPtr)->ComTxTimeoutFactorRef)))
#endif /* (COM_TX_TIMEOUT_FACTOR_STORAGE == COM_STORAGE_REFERENCE) */

#if (COM_TX_TIMEOUT_FACTOR_STORAGE == COM_STORAGE_DIRECT)

#define COM_GET_TX_TIMEOUT_FACTOR(IPduPtr) \
   ((IPduPtr)->ComTxTimeoutFactorValue)

#endif /* (COM_TX_TIMEOUT_FACTOR_STORAGE == COM_STORAGE_DIRECT) */

#endif /* (COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) */



#define COM_RX_SIGNAL_FLAGS RxBasicParam.ComRxSignalFlags

#define COM_GET_RX_SIGNAL_SIGNAL_TYPE(signalPtr) \
   ((Com_TS_SignalTypeType) ((ComRxSignalFlagsType)((signalPtr)->RxBasicParam.ComRxSignalFlags) & \
         ((COM_CALC_MASK(ComRxSignalFlagsType, 0U, COM_RX_SIGNAL_FLAG_SIGNAL_TYPE_SIZE))) ))


#if (COM_RX_SIGNAL_FLAG_ENDIANNESS_OCC == COM_FLAG_PRESENT)
#define COM_GET_RX_SIGNAL_ENDIANNESS(signalPtr) \
   ((Com_TS_SignalEndiannessType) ((ComRxSignalFlagsType) \
         (((signalPtr)->RxBasicParam.ComRxSignalFlags)>> \
         (COM_RX_SIGNAL_FLAG_SIGNAL_TYPE_SIZE)) & ((COM_CALC_MASK(ComRxSignalFlagsType, 0U, \
               COM_RX_SIGNAL_FLAG_ENDIANNESS_SIZE)))  ))
#endif

#if (COM_RX_SIGNAL_FLAG_TIMEOUT_ACTION_OCC == COM_FLAG_PRESENT)
#define COM_GET_RX_SIGNAL_TIMEOUT_ACTION(signalPtr) \
   ((boolean)((ComRxSignalFlagsType)(((signalPtr)->RxBasicParam.ComRxSignalFlags)>> \
         (COM_RX_SIGNAL_FLAG_SIGNAL_TYPE_SIZE + COM_RX_SIGNAL_FLAG_ENDIANNESS_SIZE)) & \
         ((COM_CALC_MASK(ComRxSignalFlagsType, 0U, COM_RX_SIGNAL_FLAG_TIMEOUT_ACTION_SIZE)))  ))
#endif


#if (COM_RX_SIGNAL_FLAG_UPDATE_BIT_OCC == COM_FLAG_PRESENT)
#define COM_GET_RX_SIGNAL_UPDATE_BIT(signalPtr) \
   COM_GET_RX_UPDATE_BIT_HLP(signalPtr, COM_RX_SIGNAL_FLAGS)
#endif

#if (COM_RX_SIGNAL_FLAG_UPDATE_BIT_OCC == COM_FLAG_PRESENT)
/* Deviation MISRA-3 */
#define COM_GET_RX_UPDATE_BIT_HLP(RxPtr, RxFlags) \
      ((boolean)((ComRxSignalFlagsType) \
            (((RxPtr)->RxFlags)>>(COM_RX_SIGNAL_FLAG_SIGNAL_TYPE_SIZE + \
            COM_RX_SIGNAL_FLAG_ENDIANNESS_SIZE + COM_RX_SIGNAL_FLAG_TIMEOUT_ACTION_SIZE )) & \
            ((COM_CALC_MASK(ComRxSignalFlagsType, \
                  0U, COM_RX_SIGNAL_FLAG_UPDATE_BIT_SIZE)))  ))
#endif


#if (COM_RX_SIGNAL_FLAG_DM_OCC == COM_FLAG_PRESENT)
#define COM_GET_RX_SIGNAL_DM(signalPtr) \
   ((boolean)((ComRxSignalFlagsType) \
         (((signalPtr)->RxBasicParam.ComRxSignalFlags)>>(COM_RX_SIGNAL_FLAG_SIGNAL_TYPE_SIZE + \
         COM_RX_SIGNAL_FLAG_ENDIANNESS_SIZE + COM_RX_SIGNAL_FLAG_TIMEOUT_ACTION_SIZE + \
         COM_RX_SIGNAL_FLAG_UPDATE_BIT_SIZE)) & \
         ((COM_CALC_MASK(ComRxSignalFlagsType, 0U, COM_RX_SIGNAL_FLAG_DM_SIZE)))  ))
#endif

#if (COM_RX_SIGNAL_BASED_DM == STD_ON)
#define COM_RX_SIGNAL_DM_FLAGS_BYTE_POS(SignalPtr) \
   (&Com_gDataMemPtr[(Com_gConfigPtr->ComRxTimeoutSignalStatusQueueBase + \
         (((SignalPtr)->RxSigDMQueueRef) / 4U))])
#define COM_RX_SIGNAL_DM_TIMEOUT_BIT_POS(SignalPtr) \
   ((((SignalPtr)->RxSigDMQueueRef) % 4U) * 2U)
#define COM_RX_SIGNAL_DM_RUNNING_BIT_POS(SignalPtr) \
   (COM_RX_SIGNAL_DM_TIMEOUT_BIT_POS(SignalPtr) + 1U)
#endif /* (COM_RX_SIGNAL_BASED_DM == STD_ON) */


#define COM_TX_SIGNAL_FLAGS TxBasicParam.ComTxSignalFlags


#define COM_GET_TX_SIGNAL_SIGNAL_TYPE(signalPtr) \
   COM_GET_TX_SIGNAL_TYPE_HLP(signalPtr, COM_TX_SIGNAL_FLAGS)

/* Deviation MISRA-3 */
#define COM_GET_TX_SIGNAL_TYPE_HLP(signalPtr, TxFlags) \
   ((Com_TS_SignalTypeType) ((uint8)((signalPtr)->TxFlags) & 0x7U))


#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
#define COM_GET_TX_SIGNAL_ENDIANNESS(signalPtr) \
   ((Com_TS_SignalEndiannessType) ( \
         (uint8)(((signalPtr)->TxBasicParam.ComTxSignalFlags)>>3U) & 0x3U))
#endif



#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)

/** \brief COM_TRIGGERED_OC_VALUE_CHANGED
 * if trigger on change is enabled COM_EVALUATE_TRIGGERED_OC == STD_ON oldVal
 * and newVal are compared.
 * If COM_EVALUATE_TRIGGERED_OC == STD_OFF macro is empty.
 * \param[in] oldVal value to be compared
 * \param[in] newVal value to be compared
 * \param[out] retVal TRUE if oldVal and newVal differs, else unchanged
 * \retval None */
#define COM_TRIGGERED_OC_VALUE_CHANGED(oldVal, newVal, retVal) \
   do {\
      if ((oldVal) != (newVal)) \
      { \
         (retVal) = TRUE; \
      } \
   }while(0)

/** \brief COM_TRIGGERED_OC_BYTE_VALUE_CHANGED_TOCMASK
 * if trigger on change is enabled COM_EVALUATE_TRIGGERED_OC == STD_ON oldVal (Byte)
 * and newVal (Byte) are masked and compared.
 * If COM_EVALUATE_TRIGGERED_OC == STD_OFF macro is empty.
 * \param[in] oldVal value to be compared
 * \param[in] newVal value to be compared
 * \param[in] mask mask which is applied for comparison
 * \param[out] retVal TRUE if oldVal and newVal differs, else unchanged
 * \retval None */
#define COM_TRIGGERED_OC_BYTE_VALUE_CHANGED_TOCMASK(oldVal, newVal, mask, retVal) \
   COM_TRIGGERED_OC_VALUE_CHANGED((uint8)((oldVal) & (mask)), (uint8)((newVal) & (mask)), (retVal))

/** \brief COM_TRIGGERED_OC_WRITE_BYTE_TO_PDU
 * copies (one byte) from newVal to pduVal.
 * If trigger on change is enabled COM_EVALUATE_TRIGGERED_OC == STD_ON old pduVal
 * and newVal are compared.
 * If COM_EVALUATE_TRIGGERED_OC == STD_OFF just copies.
 * \param[in] pduVal value to be compared
 * \param[in] newVal value to be compared
 * \param[out] retVal TRUE if oldVal and newVal differs, else unchanged
 * \retval None */
#define COM_TRIGGERED_OC_WRITE_BYTE_TO_PDU(pduVal, newVal, retVal) \
   do { \
      COM_TRIGGERED_OC_VALUE_CHANGED((pduVal), (newVal), (retVal)); \
      (pduVal) = (newVal); \
   } while (0)


/** \brief COM_TRIGGERED_OC_WRITE_BYTE_TO_PDU_TOCMASK
 * copies (one byte) from newVal to pduVal.
 * If trigger on change is enabled COM_EVALUATE_TRIGGERED_OC == STD_ON old pduVal
 * and newVal are masked and compared.
 * If COM_EVALUATE_TRIGGERED_OC == STD_OFF just copies.
 * \param[in] pduVal value to be compared
 * \param[in] newVal value to be compared
 * \param[in] mask mask which is applied for comparison
 * \param[out] retVal TRUE if oldVal and newVal differs, else unchanged
 * \retval None */
#define COM_TRIGGERED_OC_WRITE_BYTE_TO_PDU_TOCMASK(pduVal, newVal, mask, retVal) \
   do { \
      COM_TRIGGERED_OC_BYTE_VALUE_CHANGED_TOCMASK((pduVal), (newVal), (mask), (retVal)); \
      (pduVal) = (newVal); \
   } while (0)

/** \brief COM_TRIGGERED_OC_WRITE_BYTEARRAY_TO_PDU
 * copies a byte array from newValPtr to pduVal.
 * If trigger on change is enabled COM_EVALUATE_TRIGGERED_OC == STD_ON old pduVal
 * and newVal are compared. If equal retVal is true otherwise false.
 * If COM_EVALUATE_TRIGGERED_OC == STD_OFF just copies.
 * \param[in] pduValuint8Ptr - reference to destination array to be copied/compared
 * \param[in] newValuint8Ptr - reference to source array to be copied/compared
 * \param[in] num - number of bytes which shall be copied/compared
 * \param[out] retVal TRUE if oldVal and newVal is equal, else FALSE
 * \retval None */
#define COM_TRIGGERED_OC_WRITE_BYTEARRAY_TO_PDU(pduValuint8Ptr, newValuint8Ptr, num, retVal) \
   do { \
      uint16 i; \
      (retVal) = FALSE;          \
      for (i = 0U; i < (num); i++)              \
      { \
        COM_TRIGGERED_OC_WRITE_BYTE_TO_PDU((pduValuint8Ptr)[i], (newValuint8Ptr)[i], (retVal)); \
      } \
   } while (0)


/** \brief COM_TRIGGERED_OC_WRITE_BYTEARRAY_TO_PDU_TOCMASK
 * copies a byte array from newValPtr to pduVal.
 * If trigger on change is enabled COM_EVALUATE_TRIGGERED_OC == STD_ON old pduVal
 * and newVal are masked and compared.
 * If COM_EVALUATE_TRIGGERED_OC == STD_OFF just copies.
  * Preconditions:
 * retVal shall be TRUE or FALSE.
 * \param[in] pduValuint8Ptr - reference to destination array to be copied/compared
 * \param[in] newValuint8Ptr - reference to source array to be copied/compared
 * \param[in] maskPtr - reference to mask array which shall be applied for comparison
 * \param[in] num - number of bytes which shall be copied/compared
 * \param[out] retVal TRUE if oldVal and newVal is differs, else unchanged
 * \retval None */
#define COM_TRIGGERED_OC_WRITE_BYTEARRAY_TO_PDU_TOCMASK(pduValuint8Ptr, newValuint8Ptr, maskPtr, num, retVal) \
   do { \
      uint16 i; \
      for (i = 0U; i < (num); i++)              \
      { \
        COM_TRIGGERED_OC_WRITE_BYTE_TO_PDU_TOCMASK((pduValuint8Ptr)[i], (newValuint8Ptr)[i], (maskPtr)[i], (retVal)); \
      } \
   } while (0)


#else


#define COM_TRIGGERED_OC_WRITE_BYTE_TO_PDU(pduVal, newVal, retVal) \
   (pduVal) = (newVal)
#define COM_TRIGGERED_OC_WRITE_BYTEARRAY_TO_PDU(pduValuint8Ptr, newValuint8Ptr, num, retVal) \
      TS_MemCpy(pduValuint8Ptr, newValuint8Ptr, num)
#define COM_TRIGGERED_OC_WRITE_BYTEARRAY_TO_PDU_TOCMASK(pduValuint8Ptr, newValuint8Ptr, maskPtr, num, retVal) \
   COM_TRIGGERED_OC_WRITE_BYTEARRAY_TO_PDU((pduValuint8Ptr), (newValuint8Ptr), (num), (retVal))
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */

#if (COM_TM_AVAILABLE == STD_ON)
#define COM_GET_TX_SIGNAL_TRANSFER_PROPERTY(signalPtr) \
   COM_GET_TX_TRANSFER_PROPERTY_HLP(signalPtr, COM_TX_SIGNAL_FLAGS)


/* Deviation MISRA-3 */
#define COM_GET_TX_TRANSFER_PROPERTY_HLP(signalPtr, TxFlags) \
   ((uint8) ((uint8)(((signalPtr)->TxFlags)>>5U) & 0x3U))
#endif

#if (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL)
#define COM_GET_TX_SIGNAL_UPDATE_BIT(signalPtr) \
   ((uint8) ((uint8)(((signalPtr)->TxBasicParam.ComTxSignalFlags)>>7U) & 0x1U))
#endif


#if (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
#define COM_GET_RX_GROUP_SIGNAL_SIGNAL_TYPE(GSignalPtr) \
   ((Com_TS_SignalTypeType) ((uint8)((GSignalPtr)->ComRxGroupSignalFlags) & 0x7U))

#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
#define COM_GET_RX_GROUP_SIGNAL_ENDIANNESS(GSignalPtr) \
   ((Com_TS_SignalEndiannessType) ((uint8)(((GSignalPtr)->ComRxGroupSignalFlags)>>3U) & 0x3U))
#endif

#if (COM_UPDATE_BIT_RX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL)
#define COM_GET_RX_GROUP_SIGNAL_UPDATE_BIT(GSignalPtr) \
   ((Com_TS_SignalEndiannessType) ((uint8)(((GSignalPtr)->ComRxGroupSignalFlags)>>5U) & 0x1U))
#endif /* (COM_UPDATE_BIT_RX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL) */
#endif /* (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */


#if (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
#define COM_GET_TX_GROUP_SIGNAL_SIGNAL_TYPE(GSignalPtr) \
   ((Com_TS_SignalTypeType) ( \
         (uint8)((GSignalPtr)->ComTxGroupSignalFlags) & 0x7U))

#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
#define COM_GET_TX_GROUP_SIGNAL_ENDIANNESS(GSignalPtr) \
   ((Com_TS_SignalEndiannessType) ( \
         (uint8)(((GSignalPtr)->ComTxGroupSignalFlags)>>3U) & 0x3U))
#endif

#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
#define COM_GET_TX_GROUP_SIGNAL_TRANSFER_PROPERTY(gSignalPtr) \
   ((uint8) ((uint8)(((gSignalPtr)->ComTxGroupSignalFlags)>>5U) & 0x3U))
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */

#endif /* (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */


#if (COM_SIGNAL_BYTE_ALIGN == STD_ON)

#if (COM_SIGNAL_TYPE_UINT8_N_ENABLE == STD_ON)
#define COM_GET_SIGNAL_POS_ALIG(signalPtr, byte) \
do {\
   (byte) = ((signalPtr)->TxBasicParam.ComSignalPositionInByte); \
} while(0)

#if (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
#define COM_GET_GROUP_SIGNAL_POS_ALIG(signalPtr, byte) \
do {\
   (byte) = (ComSignalDescByteType)((signalPtr)->ComSignalPositionInByte); \
} while(0)
#endif /* (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */
#endif /* (COM_SIGNAL_TYPE_UINT8_N_ENABLE == STD_ON) */

#elif (COM_SIGNAL_BYTE_ALIGN == STD_OFF)

#if (COM_SIGNAL_TYPE_UINT8_N_ENABLE == STD_ON)
#define COM_GET_SIGNAL_POS_ALIG(signalPtr, byte) \
do {\
   (byte) = (ComSignalDescBitType)((signalPtr)->TxBasicParam.ComSignalPositionInBit); \
} while(0)

#if (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
#define COM_GET_GROUP_SIGNAL_POS_ALIG(signalPtr, byte) \
do {\
   (byte) = (ComSignalDescByteType)((signalPtr)->ComSignalPositionInBit); \
} while(0)
#endif /* (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */
#endif /* (COM_SIGNAL_TYPE_UINT8_N_ENABLE == STD_ON) */

#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_ON) */


/* there are MISRA deviations in COM_GET_CONFIG_ADDR_NOCHK (from TS_GETCONSTCFGNOCHK) */
#define COM_GET_CONFIG_ELEMENT(type, ref, id) \
   (&((P2CONST(type, AUTOMATIC, COM_APPL_CONST))(COM_GET_CONFIG_ADDR_NOCHK(type, ref)))[(id)])


#if (COM_SIGNAL_GW_ENABLE == STD_ON)

#define COM_GW_SOURCE_FLAGS RxBasicParam.ComRxSignalFlags

#define COM_GET_GW_SOURCE_DESCRIPTION_UPDATE_BIT(srcGWDecriptionPtr) \
      (COM_GET_RX_UPDATE_BIT_HLP((srcGWDecriptionPtr), COM_GW_SOURCE_FLAGS))

#define COM_GW_SOURCE_DESCRIPTION_UPDATE_BIT_ADDRESS(srcGWDecriptionPtr) \
   (COM_GW_SOURCE_DESCRIPTION_RX_IPDU_VALUE_RAM_ADDRESS(srcGWDecriptionPtr) +\
         COM_GW_SOURCE_DESCRIPTION_UPDATE_BIT_IPDU_BYTE_OFFSET(srcGWDecriptionPtr))



#define COM_GW_SOURCE_DESCRIPTION_UPDATE_BIT_FLAG(srcGWDecriptionPtr) \
   COM_GW_SOURCE_DESCRIPTION_UPDATE_BIT_IPDU_BIT_OFFSET(srcGWDecriptionPtr)

#define COM_GET_GW_SOURCE_DESCRIPTION_IPDU_ID(srcGWDecriptionPtr) \
   ((srcGWDecriptionPtr)->RxBasicParam.ComIPduRef)

#define COM_GET_GW_SOURCE_DESCRIPTION_IPDU_REF(srcGWDecriptionPtr) \
   (COM_GET_CONFIG_ELEMENT(ComRxIPduType, \
         Com_gConfigPtr->ComRxIPduRef, \
         COM_GET_GW_SOURCE_DESCRIPTION_IPDU_ID(srcGWDecriptionPtr)))

#define COM_GET_RX_IPDU_VALUE_RAM_ADDRESS(iPduPtr) \
   (&Com_gDataMemPtr[((iPduPtr)->ComIPduValueRef)])


#define COM_GW_SOURCE_DESCRIPTION_RX_IPDU_VALUE_RAM_ADDRESS(srcGWDecriptionPtr) \
   (COM_GET_RX_IPDU_VALUE_RAM_ADDRESS(COM_GET_GW_SOURCE_DESCRIPTION_IPDU_REF(srcGWDecriptionPtr)))

#if (COM_UPDATE_BIT_RX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL)

#define COM_GW_SOURCE_DESCRIPTION_UPDATE_BIT_IPDU_BYTE_OFFSET(srcGWDecriptionPtr) \
   ((srcGWDecriptionPtr)->RxBasicParam.ComUpdateBitPositionInBit / 8U)
#define COM_GW_SOURCE_DESCRIPTION_UPDATE_BIT_IPDU_BIT_OFFSET(srcGWDecriptionPtr) \
   ((srcGWDecriptionPtr)->RxBasicParam.ComUpdateBitPositionInBit % 8U)

#endif /* (COM_UPDATE_BIT_RX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL) */



#define COM_GW_DESTINATION_DESCRIPTION_FLAGS TxBasicParam.ComTxSignalFlags

#define COM_GET_COM_GW_DESTINATION_DESCRIPTION_SIGNAL_TYPE(destDescPtr) \
   COM_GET_TX_SIGNAL_TYPE_HLP((destDescPtr), COM_GW_DESTINATION_DESCRIPTION_FLAGS)

#if (COM_TM_AVAILABLE == STD_ON)

#define COM_GET_COM_GW_DESTINATION_DESCRIPTION_TRANSFER_PROPERTY(destDescPtr) \
   COM_GET_TX_TRANSFER_PROPERTY_HLP((destDescPtr), COM_GW_DESTINATION_DESCRIPTION_FLAGS)
#endif /* (COM_TM_AVAILABLE == STD_ON) */


#endif /* (COM_SIGNAL_GW_ENABLE == STD_ON) */


/** \brief Define COM_CHOOSE_INIT_PTR returns a pointer from which either the
 * initial value or a value from a buffer can be read. If the constant initial value
 * optimization is enabled, the value COM_SIGNAL_INIT_VALUE_CONSTANT is used.
 * \param[in] globTakeInitPtr - if TRUE the InitPtr[row] or COM_SIGNAL_INIT_VALUE_CONSTANT
 *                              else bufferPtr[row] is returned.
 * \param[in] InitPtr - pointer to the initial value buffer of the Pdu,
 * \param[in] bufferPtr - pointer to the RAM buffer of the Pdu
 * \param[in] row - byte in which the value of a signal starts
 * \retval address of the buffer from which the value shall be extracted */
#if (COM_VALUE_INIT_REPLACE == STD_ON)
#define COM_CHOOSE_INIT_PTR(TakeInitPtr, InitPtr, bufferPtr, row) \
   (((TakeInitPtr) == TRUE) ? COM_GET_INIT_VALUE_BYTE((InitPtr)[(row)]) : (bufferPtr)[(row)])
#else
#define COM_CHOOSE_INIT_PTR(TakeInitPtr, InitPtr, bufferPtr, row) ((bufferPtr)[(row)])
#endif /* (COM_VALUE_INIT_REPLACE == STD_ON) */


#if (COM_SIGNAL_INIT_VALUE_ENABLE == STD_ON)

/** \brief Define COM_GET_INIT_VALUE_BYTE returns initial value
 * \param[in] ByteFromRom - value which is returned
 * \retval ByteFromRom */
#define COM_GET_INIT_VALUE_BYTE(ByteFromRom) (ByteFromRom)

#else

/** \brief Define COM_GET_INIT_VALUE_BYTE returns constant initial value
 * \param[in] ByteFromRom - value is ignored
 * \retval constant initial value COM_SIGNAL_INIT_VALUE_CONSTANT */
#define COM_GET_INIT_VALUE_BYTE(ByteFromRom) COM_SIGNAL_INIT_VALUE_CONSTANT

#endif /* (COM_SIGNAL_INIT_VALUE_ENABLE == STD_ON) */


#if (COM_SIGNAL_INIT_VALUE_ENABLE == STD_OFF)

#if (defined COM_UINT8_COPY_INIT_DEFAULT)
#error COM_UINT8_COPY_INIT_DEFAULT already defined
#endif

#define COM_UINT8_COPY_INIT_DEFAULT(destptr, count, var)\
do {\
   for ((var) = 0; (var) < (count); (var)++) {\
      ((destptr))[(var)] = COM_SIGNAL_INIT_VALUE_CONSTANT;\
   }\
} while(0)

#endif /* (COM_SIGNAL_INIT_VALUE_ENABLE == STD_OFF) */

#if (COM_SIGNAL_GW_ENABLE == STD_ON)

/** \brief COM_RX_IPDU_SIG_GW_FLAG_ADDRESS
 * return the address of the I-Pdu SigGWFlag
 * \param[in] ipduPtr - reference to the I-Pdu configuration
 * \retval address of the SigGWFlag of the I-Pdu */
#define COM_RX_IPDU_SIG_GW_FLAG_ADDRESS(ipduPtr) \
   (&Com_gDataMemPtr[(Com_gConfigPtr->ComSigGWRxPduFlagBase + \
         (((ipduPtr)->ComIPduSigGWFlagBit) / 8U))])

/** \brief COM_RX_IPDU_SIG_GW_FLAG_BIT
 * return the bit of the I-Pdu SigGWFlag relative to COM_RX_IPDU_SIG_GW_FLAG_ADDRESS
 * \param[in] ipduPtr - reference to the I-Pdu configuration
 * \retval bit of the SigGWFlag of the I-Pdu */
#define COM_RX_IPDU_SIG_GW_FLAG_BIT(ipduPtr) (((ipduPtr)->ComIPduSigGWFlagBit) % 8U)


#if (COM_SIGGW_RX_FILTER_ENABLE == STD_ON)

/** \brief COM_RX_SIGNAL_SIG_GW_FLAG_ADDRESS
 * return the address of the signal SigGWFlag
 * \param[in] signalPtr - reference to the signal configuration
 * \retval address of the SigGWFlag of the signal */
#define COM_RX_SIGNAL_SIG_GW_FLAG_ADDRESS(signalPtr) \
   (&Com_gDataMemPtr[(Com_gConfigPtr->ComSigGWRxSigFlagBase + \
         (((signalPtr)->ComSignalSigGWFlagBit) / 8U))])


/** \brief COM_RX_SIGNAL_SIG_GW_FLAG_BIT
 * return bit position of the signal SigGWFlag relative to
 * COM_RX_SIGNAL_SIG_GW_FLAG_ADDRESS
 * \param[in] signalPtr - reference to the signal configuration
 * \retval position of the SigGWFlag of the signal */
#define COM_RX_SIGNAL_SIG_GW_FLAG_BIT(signalPtr) (((signalPtr)->ComSignalSigGWFlagBit) % 8U)

#endif /* (COM_SIGGW_RX_FILTER_ENABLE == STD_ON) */


#endif /* (COM_SIGNAL_GW_ENABLE == STD_ON) */


#if (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)

/** \brief COM_GET_RX_SIGNAL_GROUP_ID
 * returns the Id of the signal group of a group signal
 * \param[in] GSignalPtr - reference to the group signal configuration
 * \retval Id of the signal group */
#define COM_GET_RX_SIGNAL_GROUP_ID(GSignalPtr) ((GSignalPtr)->ComSignalGroupRef)


/** \brief COM_GET_RX_SIGNAL_GROUP_CONFIG_REF
 * returns the reference to the configuration of a signal group identified by
 * an reference to a configuration of a group signal.
 * \param[in] GSignalPtr - reference to the group signal configuration
 * \retval reference to the signal group to which the group signal belongs */
#define COM_GET_RX_SIGNAL_GROUP_CONFIG_REF(GSignalPtr) \
   (COM_GET_CONFIG_ELEMENT(ComRxSignalGroupType, \
         Com_gConfigPtr->ComRxSignalGroupRef, \
         COM_GET_RX_SIGNAL_GROUP_ID(GSignalPtr)))


#if (COM_TM_AVAILABLE == STD_ON)

#if (defined COM_TXSG_TMSSTATE) /* To prevent double declaration */
#error COM_TXSG_TMSSTATE already defined
#endif /* if (defined COM_TXSG_TMSSTATE) */

/** \brief Define COM_TXSG_TMSSTATE */
#define COM_TXSG_TMSSTATE 0U

#if (defined COM_TXSG_TMSMIGHTCHANGE)   /* To prevent double declaration */
#error COM_TXSG_TMSMIGHTCHANGE already defined
#endif /* if (defined COM_TXSG_TMSMIGHTCHANGE) */

/** \brief Define COM_TXSG_TMSMIGHTCHANGE */
#define COM_TXSG_TMSMIGHTCHANGE 1U


#if (defined COM_TXSG_TMS_MIGHT_CHANGE_FLAG_ADDRESS)   /* To prevent double declaration */
#error COM_TXSG_TMS_MIGHT_CHANGE_FLAG_ADDRESS already defined
#endif /* if (defined COM_TXSG_TMS_MIGHT_CHANGE_FLAG_ADDRESS) */

/** \brief COM_TXSG_TMS_MIGHT_CHANGE_FLAG_ADDRESS
 * returns the address of the TMS Flags of a signal group
 * \param[in] signalGId - id of the signal group
 * \retval address of the TMS flags of the signal group */
#define COM_TXSG_TMS_MIGHT_CHANGE_FLAG_ADDRESS(signalGId) \
   &Com_gDataMemPtr[(Com_gConfigPtr->ComTxSignalGroupStatusBase + (signalGId))]


/** \brief COM_GET_TX_SG_ID
 * calculates the ID of the Signal Group
 * \param[in] result - variable where the ID of the signal group is written to
 * \param[in] signalGPtr - reference to the signal group configuration
 * \retval ID of the signal group */
/* Deviation MISRA-2 */
#define COM_GET_TX_SG_ID(result, signalGPtr) \
    do \
    { \
        ptrdiff_t offset = (signalGPtr) - \
        (COM_GET_CONFIG_ELEMENT(ComTxSignalGroupType, Com_gConfigPtr->ComTxSignalGroupRef, 0)); \
        (result) = (ComSignalGroupRefType) offset; \
    } while (0)

#endif /* (COM_TM_AVAILABLE == STD_ON) */
#endif /* (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

#if (COM_CBK_TX_T_OUT_ARRAY_SIZE_MAX != COM_INDEX_NONE)
#define COM_GET_CBK_TX_T_OUT_IDX(listnum) \
   ((Com_CbkTxTOutIdxType) *COM_GET_CONFIG_ELEMENT(Com_CbkTxTOutIdxType, \
      Com_gConfigPtr->ComTxTimeoutNotificationRef, (listnum)))
#endif /* (COM_CBK_TX_T_OUT_ARRAY_SIZE_MAX != COM_INDEX_NONE) */


#if (COM_CBK_RX_T_OUT_ARRAY_SIZE_MAX != COM_INDEX_NONE)
#define COM_GET_CBK_RX_T_OUT_IDX(listnum) \
   ((Com_CbkRxTOutIdxType) *COM_GET_CONFIG_ELEMENT(Com_CbkRxTOutIdxType, \
         Com_gConfigPtr->ComRxTimeoutNotificationRef, (listnum)))
#endif /* (COM_CBK_RX_T_OUT_ARRAY_SIZE_MAX != COM_INDEX_NONE) */


#if (COM_CBK_TX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE)
#define COM_GET_CBK_TX_ACK_PTR_IDX(listnum) \
   ((Com_CbkTxAckIdxType) *COM_GET_CONFIG_ELEMENT(Com_CbkTxAckIdxType, \
         (Com_gConfigPtr->ComTxNotificationRef), (listnum)))
#endif /* (COM_CBK_TX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) */


/** \brief Com_ClearBitUInt8
 * clears a bit from a byte at the given address and position
 * \param[in] Address pointer to the variable of type uint8
 * \param[in] Bit number of the bit to clear (0..7)
 * \retval None */
#define Com_ClearBitUInt8(Address, Bit)                         \
   *(Address) = (uint8)(*(Address) & (uint8)(~(uint8)(1U << (Bit))))


/** \brief Com_SetBitUInt8
 * sets a bit from a byte at the given address and position
 * \param[in] Address pointer to the variable of type uint8
 * \param[in] Bit number of the bit to set (0..7)
 * \retval None */
#define Com_SetBitUInt8(Address, Bit)                           \
      *(Address) = (uint8)(*(Address) | (uint8)(1U << (Bit)))


/** \brief Com_ClearBitUInt8Var
 * clears a bit from a byte at the given variable and position
 * \param[in] Var variable of type uint8
 * \param[in] Bit number of the bit to clear (0..7)
 * \retval None */
#define Com_ClearBitUInt8Var(Var, Bit)                          \
   (Var) = (uint8)((Var) & (uint8)(~(uint8)(1U << (Bit))))


/** \brief Com_SetBitUInt8Var
 * sets a bit from a byte at the given variable and position
 * \param[in] Var variable of type uint8
 * \param[in] Bit number of the bit to set (0..7)
 * \retval None */
#define Com_SetBitUInt8Var(Var, Bit)                            \
   (Var) = (uint8)((Var) | (uint8)(1U << (Bit)))



/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* if !defined( COM_EXTENSION_H ) */
/*==================[end of file]===========================================*/
