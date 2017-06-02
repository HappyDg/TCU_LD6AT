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
#ifndef COM_RULES_H_
#define COM_RULES_H_

#include <TSAutosar.h>          /* EB specific standard types */
#include <Com_Defs.h>           /* Definitions of macros */
#include <Com_Cfg.h>
#include <ComStack_Types.h>     /* AUTOSAR Standard types */
#include <Com_Local_Cfg.h>


/*==================[macros]================================================*/


#if (COM_SIGNAL_GW_ENABLE == STD_OFF)

#if (!defined COM_GW_SOURCE_DESCRIPTION_ARRAY_SIZE_MAX) /* To prevent double declaration */
#define COM_GW_SOURCE_DESCRIPTION_ARRAY_SIZE_MAX COM_INDEX_NONE
#endif /* if (defined COM_GW_SOURCE_DESCRIPTION_ARRAY_SIZE_MAX) */


#if (defined COM_GW_SOURCE_ARRAY_SIZE_MAX) /* To prevent double declaration */
#error COM_GW_SOURCE_ARRAY_SIZE_MAX already defined
#endif /* if (defined COM_GW_SOURCE_ARRAY_SIZE_MAX) */

/** \brief Define COM_GW_SOURCE_ARRAY_SIZE_MAX */
#define COM_GW_SOURCE_ARRAY_SIZE_MAX COM_INDEX_NONE


#if (!defined COM_GW_DESTINATION_DESCRIPTION_ARRAY_SIZE_MAX) /* To prevent double declaration */
#define COM_GW_DESTINATION_DESCRIPTION_ARRAY_SIZE_MAX COM_INDEX_NONE
#endif /* if (defined COM_GW_DESTINATION_DESCRIPTION_ARRAY_SIZE_MAX) */


#if (defined COM_GW_DESTINATION_ARRAY_SIZE_MAX) /* To prevent double declaration */
#error COM_GW_DESTINATION_ARRAY_SIZE_MAX already defined
#endif /* if (defined COM_GW_DESTINATION_ARRAY_SIZE_MAX) */

/** \brief Define COM_GW_DESTINATION_ARRAY_SIZE_MAX */
#define COM_GW_DESTINATION_ARRAY_SIZE_MAX COM_INDEX_NONE

#endif


#if ((COM_TX_MODE_N_TIMES_ENABLE == STD_ON) || \
      (COM_TX_MODE_MIXED_N_TIMES_ENABLE == STD_ON) || \
      (COM_TX_MODE_DIRECT_ENABLE == STD_ON) ||\
      (COM_TX_MODE_MIXED_DIRECT_ENABLE == STD_ON))
#define COM_TX_MODE_NOT_NONE_OR_PERIODIC_AVAILABLE STD_ON
#else
#define COM_TX_MODE_NOT_NONE_OR_PERIODIC_AVAILABLE STD_OFF
#endif



#if (defined COM_RX_SIGNAL_BASED_DM)     /* To prevent double declaration */
#error COM_RX_SIGNAL_BASED_DM already defined
#endif /* #if (defined COM_RX_SIGNAL_BASED_DM) */

/** \brief definition COM_RX_SIGNAL_BASED_DM */
#if ((COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) && \
      (COM_RX_TIMEOUT_FACTOR_SIZE != COM_SIZE_0_BIT))
#define COM_RX_SIGNAL_BASED_DM STD_ON
#else
#define COM_RX_SIGNAL_BASED_DM STD_OFF
#endif


#if (defined COM_FILTER_AVAILABLE)      /* To prevent double declaration */
#error COM_FILTER_AVAILABLE already defined
#endif /* #if (defined COM_FILTER_AVAILABLE) */

/** \brief definition COM_FILTER_AVAILABLE */
#if ((COM_TMS_ENABLE == STD_ON) || \
    (COM_FILTER_RECEIVER_ENABLE == STD_ON))
#define COM_FILTER_AVAILABLE STD_ON
#else
#define COM_FILTER_AVAILABLE STD_OFF
#endif /* ((COM_TMS_ENABLE == STD_ON) || \
          (COM_FILTER_RECEIVER_ENABLE == STD_ON)) */


#if (defined COM_MDT_QUEUE_AVAILABLE)   /* To prevent double declaration */
#error COM_MDT_QUEUE_AVAILABLE already defined
#endif /* #if (defined COM_MDT_QUEUE_AVAILABLE) */

/** \brief definition COM_MDT_QUEUE_AVAILABLE */
#if (COM_TX_IPDU_MINIMUM_DELAY_TIME_FACTOR_SIZE != COM_SIZE_0_BIT)
#define COM_MDT_QUEUE_AVAILABLE STD_ON
#else
#define COM_MDT_QUEUE_AVAILABLE STD_OFF
#endif


#if (defined COM_TX_TIMEOUT_FACTOR_AVAILABLE)   /* To prevent double declaration */
#error COM_TX_TIMEOUT_FACTOR_AVAILABLE already defined
#endif /* (defined COM_TX_TIMEOUT_FACTOR_AVAILABLE) */

/** \brief definition COM_TX_TIMEOUT_FACTOR_AVAILABLE */
#if (COM_TX_TIMEOUT_FACTOR_SIZE != COM_SIZE_0_BIT)
#define COM_TX_TIMEOUT_FACTOR_AVAILABLE STD_ON
#else
#define COM_TX_TIMEOUT_FACTOR_AVAILABLE STD_OFF
#endif


#if (defined COM_RX_TIMEOUT_FACTOR_AVAILABLE)   /* To prevent double declaration */
#error COM_RX_TIMEOUT_FACTOR_AVAILABLE already defined
#endif /* (defined COM_RX_TIMEOUT_FACTOR_AVAILABLE) */

/** \brief definition COM_RX_TIMEOUT_FACTOR_AVAILABLE */
#if (COM_RX_TIMEOUT_FACTOR_SIZE != COM_SIZE_0_BIT)
#define COM_RX_TIMEOUT_FACTOR_AVAILABLE STD_ON
#else
#define COM_RX_TIMEOUT_FACTOR_AVAILABLE STD_OFF
#endif



#if (defined COM_FILTER_8_BIT_MASK_AVAILABLE)   /* To prevent double declaration */
#error COM_FILTER_8_BIT_MASK_AVAILABLE already defined
#endif /* (defined COM_FILTER_8_BIT_MASK_AVAILABLE) */

#if (defined COM_FILTER_8_BIT_MASK_X_MIN_MAX_AVAILABLE) /* To prevent double declaration */
#error COM_FILTER_8_BIT_MASK_X_MIN_MAX_AVAILABLE already defined
#endif /* (defined COM_FILTER_8_BIT_MASK_X_MIN_MAX_AVAILABLE) */

/* To prevent double declaration */
#if (defined COM_FILTER_8_BIT_NEW_DIFFERS_MASKED_OLD_VALUE_AVAILABLE)
#error COM_FILTER_8_BIT_NEW_DIFFERS_MASKED_OLD_VALUE_AVAILABLE already defined
#endif /* (defined COM_FILTER_8_BIT_NEW_DIFFERS_MASKED_OLD_VALUE_AVAILABLE) */

/** \brief definition of the COM_FILTER_8_BIT_MASK_AVAILABLE,
 * COM_FILTER_8_BIT_MASK_X_MIN_MAX_AVAILABLE and
 * COM_FILTER_8_BIT_NEW_DIFFERS_MASKED_OLD_VALUE_AVAILABLE*/
#if ((COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON) || \
    (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON) || \
    (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON))
#define COM_FILTER_8_BIT_MASK_AVAILABLE COM_FILTER_AVAILABLE
#define COM_FILTER_8_BIT_MASK_X_MIN_MAX_AVAILABLE COM_FILTER_AVAILABLE
#define COM_FILTER_8_BIT_NEW_DIFFERS_MASKED_OLD_VALUE_AVAILABLE COM_FILTER_AVAILABLE
#else
#define COM_FILTER_8_BIT_MASK_AVAILABLE STD_OFF
#define COM_FILTER_8_BIT_MASK_X_MIN_MAX_AVAILABLE STD_OFF
#define COM_FILTER_8_BIT_NEW_DIFFERS_MASKED_OLD_VALUE_AVAILABLE STD_OFF
#endif /* ((COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON) || \
          (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON) || \
          (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON)) */


#if (defined COM_FILTER_16_BIT_MASK_AVAILABLE)  /* To prevent double declaration */
#error COM_FILTER_16_BIT_MASK_AVAILABLE already defined
#endif /* (defined COM_FILTER_16_BIT_MASK_AVAILABLE) */

#if (defined COM_FILTER_16_BIT_MASK_X_MIN_MAX_AVAILABLE)        /* To prevent double declaration */
#error COM_FILTER_16_BIT_MASK_X_MIN_MAX_AVAILABLE already defined
#endif /* (defined COM_FILTER_16_BIT_MASK_X_MIN_MAX_AVAILABLE) */

/* To prevent double declaration */
#if (defined COM_FILTER_16_BIT_NEW_DIFFERS_MASKED_OLD_VALUE_AVAILABLE)
#error COM_FILTER_16_BIT_NEW_DIFFERS_MASKED_OLD_VALUE_AVAILABLE already defined
#endif /* (defined COM_FILTER_16_BIT_NEW_DIFFERS_MASKED_OLD_VALUE_AVAILABLE) */

/** \brief definition of the COM_FILTER_16_BIT_MASK_AVAILABLE,
 * COM_FILTER_16_BIT_MASK_X_MIN_MAX_AVAILABLE and
 * COM_FILTER_16_BIT_NEW_DIFFERS_MASKED_OLD_VALUE_AVAILABLE*/
#if ((COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON) || \
    (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON))
#define COM_FILTER_16_BIT_MASK_AVAILABLE COM_FILTER_AVAILABLE
#define COM_FILTER_16_BIT_MASK_X_MIN_MAX_AVAILABLE COM_FILTER_AVAILABLE
#define COM_FILTER_16_BIT_NEW_DIFFERS_MASKED_OLD_VALUE_AVAILABLE COM_FILTER_AVAILABLE
#else
#define COM_FILTER_16_BIT_MASK_AVAILABLE STD_OFF
#define COM_FILTER_16_BIT_MASK_X_MIN_MAX_AVAILABLE STD_OFF
#define COM_FILTER_16_BIT_NEW_DIFFERS_MASKED_OLD_VALUE_AVAILABLE STD_OFF
#endif /* ((COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON) || \
          (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON)) */


#if (defined COM_FILTER_32_BIT_MASK_AVAILABLE)  /* To prevent double declaration */
#error COM_FILTER_32_BIT_MASK_AVAILABLE already defined
#endif /* (defined COM_FILTER_32_BIT_MASK_AVAILABLE) */

#if (defined COM_FILTER_32_BIT_MASK_X_MIN_MAX_AVAILABLE)        /* To prevent double declaration */
#error COM_FILTER_32_BIT_MASK_X_MIN_MAX_AVAILABLE already defined
#endif /* (defined COM_FILTER_32_BIT_MASK_X_MIN_MAX_AVAILABLE) */

/* To prevent double declaration */
#if (defined COM_FILTER_32_BIT_NEW_DIFFERS_MASKED_OLD_VALUE_AVAILABLE)
#error COM_FILTER_32_BIT_NEW_DIFFERS_MASKED_OLD_VALUE_AVAILABLE already defined
#endif /* (defined COM_FILTER_32_BIT_NEW_DIFFERS_MASKED_OLD_VALUE_AVAILABLE) */

/** \brief definition of the COM_FILTER_32_BIT_MASK_AVAILABLE,
 * COM_FILTER_32_BIT_MASK_X_MIN_MAX_AVAILABLE and
 * COM_FILTER_32_BIT_NEW_DIFFERS_MASKED_OLD_VALUE_AVAILABLE */
#if ((COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON) || \
    (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON))
#define COM_FILTER_32_BIT_MASK_AVAILABLE COM_FILTER_AVAILABLE
#define COM_FILTER_32_BIT_MASK_X_MIN_MAX_AVAILABLE COM_FILTER_AVAILABLE
#define COM_FILTER_32_BIT_NEW_DIFFERS_MASKED_OLD_VALUE_AVAILABLE COM_FILTER_AVAILABLE
#else
#define COM_FILTER_32_BIT_MASK_AVAILABLE STD_OFF
#define COM_FILTER_32_BIT_MASK_X_MIN_MAX_AVAILABLE STD_OFF
#define COM_FILTER_32_BIT_NEW_DIFFERS_MASKED_OLD_VALUE_AVAILABLE STD_OFF
#endif /* ((COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON) || \
          (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON)) */


#if (defined COM_FILTER_ONE_EVERY_N_AVAILABLE)  /* To prevent double declaration */
#error COM_FILTER_ONE_EVERY_N_AVAILABLE already defined
#endif /* (defined COM_FILTER_ONE_EVERY_N_AVAILABLE) */

/** \brief definition of the COM_FILTER_ONE_EVERY_N_AVAILABLE */
#if ((COM_FILTER_ONE_EVERY_N_PERIOD_OFFSET_SIZE_MAX != COM_SIZE_0_BIT) && \
     (COM_FILTER_ONE_EVERY_N_OCCURANCE_MAX != COM_SIZE_0_BIT))
#define COM_FILTER_ONE_EVERY_N_AVAILABLE COM_FILTER_AVAILABLE
#else
#define COM_FILTER_ONE_EVERY_N_AVAILABLE STD_OFF
#endif /* ((COM_FILTER_ONE_EVERY_N_PERIOD_OFFSET_SIZE_MAX != COM_SIZE_0_BIT) && \
          (COM_FILTER_ONE_EVERY_N_OCCURANCE_MAX != COM_SIZE_0_BIT)) */


#if (defined COM_TM_AVAILABLE)  /* To prevent double declaration */
#error COM_TM_AVAILABLE already defined
#endif /* (defined COM_TM_AVAILABLE) */


/** \brief definition of the COM_TM_AVAILABLE */
#if ((COM_TX_MODE_DIRECT_ENABLE == STD_ON) || \
    (COM_TX_MODE_N_TIMES_ENABLE == STD_ON) || \
    (COM_TX_MODE_PERIODIC_ENABLE == STD_ON) || \
    (COM_TX_MODE_MIXED_DIRECT_ENABLE == STD_ON) || \
    (COM_TX_MODE_MIXED_N_TIMES_ENABLE == STD_ON))
#define COM_TM_AVAILABLE STD_ON
#else
#define COM_TM_AVAILABLE STD_OFF
#endif


#if (defined COM_PERIODIC_QUEUE_AVAILABLE)      /* To prevent double declaration */
#error COM_PERIODIC_QUEUE_AVAILABLE already defined
#endif /* (defined COM_PERIODIC_QUEUE_AVAILABLE) */

/** \brief definition of the COM_PERIODIC_QUEUE_AVAILABLE */
#if ((COM_TX_MODE_PERIODIC_ENABLE == STD_ON) || \
    (COM_TX_MODE_MIXED_DIRECT_ENABLE == STD_ON) || \
    (COM_TX_MODE_MIXED_N_TIMES_ENABLE == STD_ON))
#define COM_PERIODIC_QUEUE_AVAILABLE STD_ON
#else
#define COM_PERIODIC_QUEUE_AVAILABLE STD_OFF
#endif


#if (defined COM_N_TIMES_QUEUE_AVAILABLE)       /* To prevent double declaration */
#error COM_N_TIMES_QUEUE_AVAILABLE already defined
#endif /* (defined COM_N_TIMES_QUEUE_AVAILABLE) */

/** \brief definition of the COM_N_TIMES_QUEUE_AVAILABLE */
#if ((COM_TX_MODE_N_TIMES_ENABLE == STD_ON) || \
    (COM_TX_MODE_MIXED_N_TIMES_ENABLE == STD_ON))
#define COM_N_TIMES_QUEUE_AVAILABLE STD_ON
#else
#define COM_N_TIMES_QUEUE_AVAILABLE STD_OFF
#endif


#if (COM_PERIODIC_QUEUE_AVAILABLE == STD_ON)
#define COM_TM_SWITCH_AVAILABLE STD_ON
#elif (COM_N_TIMES_QUEUE_AVAILABLE == STD_ON)
#define COM_TM_SWITCH_AVAILABLE STD_ON
#elif (COM_TX_MODE_N_TIMES_ENABLE == STD_ON)
#define COM_TM_SWITCH_AVAILABLE STD_ON
#elif ((COM_TX_MODE_MIXED_DIRECT_ENABLE == STD_ON) || (COM_TX_MODE_PERIODIC_ENABLE == STD_ON))
#define COM_TM_SWITCH_AVAILABLE STD_ON
#elif (COM_TX_MODE_MIXED_N_TIMES_ENABLE == STD_ON)
#define COM_TM_SWITCH_AVAILABLE STD_ON
#else
#define COM_TM_SWITCH_AVAILABLE STD_OFF
#endif




#if (defined COM_TX_CONFIRMATIONS_DEFERED_AVAILABLE)    /* To prevent double declaration */
#error COM_TX_CONFIRMATIONS_DEFERED_AVAILABLE already defined
#endif /* (defined COM_TX_CONFIRMATIONS_DEFERED_AVAILABLE) */

/** \brief definition of COM_TX_CONFIRMATIONS_DEFERED_AVAILABLE */
#if ((COM_CBK_TX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) && \
     (COM_TX_SIG_CONF_DEFERRED_ENABLE == STD_ON))
#define COM_TX_CONFIRMATIONS_DEFERED_AVAILABLE STD_ON
#else
#define COM_TX_CONFIRMATIONS_DEFERED_AVAILABLE STD_OFF
#endif /* ((COM_CBK_TX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) && \
          (COM_TX_SIG_CONF_DEFERRED_ENABLE == STD_ON)) */


#if (defined COM_TX_CONFIRMATIONS_IMMEDIATE_AVAILABLE)  /* To prevent double declaration */
#error COM_TX_CONFIRMATIONS_IMMEDIATE_AVAILABLE already defined
#endif /* (defined COM_TX_CONFIRMATIONS_IMMEDIATE_AVAILABLE) */

/** \brief definition of COM_TX_CONFIRMATIONS_IMMEDIATE_AVAILABLE */
#if ((COM_CBK_TX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) && \
     (COM_TX_SIG_CONF_IMMEDIATE_ENABLE == STD_ON))
#define COM_TX_CONFIRMATIONS_IMMEDIATE_AVAILABLE STD_ON
#else
#define COM_TX_CONFIRMATIONS_IMMEDIATE_AVAILABLE STD_OFF
#endif /* ((COM_CBK_TX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) && \
          (COM_TX_SIG_CONF_IMMEDIATE_ENABLE == STD_ON)) */


#if (defined COM_RX_CONF_DEFERED_AVAILABLE)    /* To prevent double declaration */
#error COM_RX_CONF_DEFERED_AVAILABLE already defined
#endif /* (defined COM_RX_CONF_DEFERED_AVAILABLE) */

/** \brief definition of COM_RX_CONF_DEFERED_AVAILABLE */
#if ((COM_CBK_RX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) && \
     (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON))
#define COM_RX_CONF_DEFERED_AVAILABLE STD_ON
#else
#define COM_RX_CONF_DEFERED_AVAILABLE STD_OFF
#endif /* ((COM_CBK_RX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) && \
          (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON)) */


#if (defined COM_RX_CONF_IMMEDIATE_AVAILABLE)  /* To prevent double declaration */
#error COM_RX_CONF_IMMEDIATE_AVAILABLE already defined
#endif /* (defined COM_RX_CONF_IMMEDIATE_AVAILABLE) */

/** \brief definition of COM_RX_CONF_IMMEDIATE_AVAILABLE */
#if ((COM_CBK_RX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) && \
     (COM_RX_SIG_CONF_IMMEDIATE_ENABLE == STD_ON))
#define COM_RX_CONF_IMMEDIATE_AVAILABLE STD_ON
#else
#define COM_RX_CONF_IMMEDIATE_AVAILABLE STD_OFF
#endif /* ((COM_CBK_RX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) && \
          (COM_RX_SIG_CONF_IMMEDIATE_ENABLE == STD_ON)) */


#if (defined COM_RX_SIGNAL_FLAG_SIGNAL_TYPE_OCC)    /* To prevent double declaration */
#error COM_RX_SIGNAL_FLAG_SIGNAL_TYPE_OCC already defined
#endif /* (defined COM_RX_SIGNAL_FLAG_SIGNAL_TYPE_OCC) */

/** \brief definition COM_RX_SIGNAL_FLAG_SIGNAL_TYPE_OCC */
#define COM_RX_SIGNAL_FLAG_SIGNAL_TYPE_OCC COM_FLAG_PRESENT

#if (defined COM_RX_SIGNAL_FLAG_SIGNAL_TYPE_SIZE)   /* To prevent double declaration */
#error COM_RX_SIGNAL_FLAG_SIGNAL_TYPE_SIZE already defined
#endif /* (defined COM_RX_SIGNAL_FLAG_SIGNAL_TYPE_SIZE) */

/** \brief definition COM_RX_SIGNAL_FLAG_SIGNAL_TYPE_SIZE */
#define COM_RX_SIGNAL_FLAG_SIGNAL_TYPE_SIZE 3U


#if (defined COM_RX_SIGNAL_FLAG_ENDIANNESS_OCC)     /* To prevent double declaration */
#error COM_RX_SIGNAL_FLAG_ENDIANNESS_OCC already defined
#endif /* (defined COM_RX_SIGNAL_FLAG_ENDIANNESS_OCC) */

#if (defined COM_RX_SIGNAL_FLAG_ENDIANNESS_SIZE)    /* To prevent double declaration */
#error COM_RX_SIGNAL_FLAG_ENDIANNESS_SIZE already defined
#endif /* (defined COM_RX_SIGNAL_FLAG_ENDIANNESS_SIZE) */

/** \brief definition COM_RX_SIGNAL_FLAG_ENDIANNESS_OCC and
 * COM_RX_SIGNAL_FLAG_ENDIANNESS_SIZE */
#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
#define COM_RX_SIGNAL_FLAG_ENDIANNESS_OCC COM_FLAG_PRESENT
#define COM_RX_SIGNAL_FLAG_ENDIANNESS_SIZE 2U
#else
#define COM_RX_SIGNAL_FLAG_ENDIANNESS_OCC COM_FLAG_ABSENT
#define COM_RX_SIGNAL_FLAG_ENDIANNESS_SIZE 0U
#endif


#if (defined COM_RX_SIGNAL_FLAG_TIMEOUT_ACTION_OCC) /* To prevent double declaration */
#error COM_RX_SIGNAL_FLAG_TIMEOUT_ACTION_OCC already defined
#endif /* (defined COM_RX_SIGNAL_FLAG_TIMEOUT_ACTION_OCC) */

#if (defined COM_RX_SIGNAL_FLAG_TIMEOUT_ACTION_SIZE)        /* To prevent double declaration */
#error COM_RX_SIGNAL_FLAG_TIMEOUT_ACTION_SIZE already defined
#endif /* (defined COM_RX_SIGNAL_FLAG_TIMEOUT_ACTION_SIZE) */

/** \brief definition COM_RX_SIGNAL_FLAG_TIMEOUT_ACTION_OCC and
 * COM_RX_SIGNAL_FLAG_TIMEOUT_ACTION_SIZE */
#if (COM_RX_DATA_TOUT_ACTION == COM_RX_DATA_TOUT_ACTION_CONFIG)
#define COM_RX_SIGNAL_FLAG_TIMEOUT_ACTION_OCC COM_FLAG_PRESENT
#define COM_RX_SIGNAL_FLAG_TIMEOUT_ACTION_SIZE 1U
#else
#define COM_RX_SIGNAL_FLAG_TIMEOUT_ACTION_OCC COM_FLAG_ABSENT
#define COM_RX_SIGNAL_FLAG_TIMEOUT_ACTION_SIZE 0U
#endif


#if (defined COM_RX_SIGNAL_FLAG_UPDATE_BIT_OCC)     /* To prevent double declaration */
#error COM_RX_SIGNAL_FLAG_UPDATE_BIT_OCC already defined
#endif /* (defined COM_RX_SIGNAL_FLAG_UPDATE_BIT_OCC) */

#if (defined COM_RX_SIGNAL_FLAG_UPDATE_BIT_SIZE)    /* To prevent double declaration */
#error COM_RX_SIGNAL_FLAG_UPDATE_BIT_SIZE already defined
#endif /* (defined COM_RX_SIGNAL_FLAG_UPDATE_BIT_SIZE) */

/** \brief definition COM_RX_SIGNAL_FLAG_UPDATE_BIT_OCC and
 * COM_RX_SIGNAL_FLAG_UPDATE_BIT_SIZE */
#if (COM_UPDATE_BIT_RX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL)
#define COM_RX_SIGNAL_FLAG_UPDATE_BIT_OCC COM_FLAG_PRESENT
#define COM_RX_SIGNAL_FLAG_UPDATE_BIT_SIZE 1U
#else
#define COM_RX_SIGNAL_FLAG_UPDATE_BIT_OCC COM_FLAG_ABSENT
#define COM_RX_SIGNAL_FLAG_UPDATE_BIT_SIZE 0U
#endif


#if (defined COM_RX_SIGNAL_FLAG_DM_OCC)     /* To prevent double declaration */
#error COM_RX_SIGNAL_FLAG_DM_OCC already defined
#endif /* (defined COM_RX_SIGNAL_FLAG_DM_OCC) */

#if (defined COM_RX_SIGNAL_FLAG_DM_SIZE)    /* To prevent double declaration */
#error COM_RX_SIGNAL_FLAG_DM_SIZE already defined
#endif /* (defined COM_RX_SIGNAL_FLAG_DM_SIZE) */

/** \brief definition COM_RX_SIGNAL_FLAG_DM_OCC and
 * COM_RX_SIGNAL_FLAG_DM_SIZE */
#if (COM_RX_SIGNAL_BASED_DM == STD_ON)
#define COM_RX_SIGNAL_FLAG_DM_OCC COM_FLAG_PRESENT
#define COM_RX_SIGNAL_FLAG_DM_SIZE 1U
#else
#define COM_RX_SIGNAL_FLAG_DM_OCC COM_FLAG_ABSENT
#define COM_RX_SIGNAL_FLAG_DM_SIZE 0U
#endif


#if (defined COM_RX_SIGNAL_FLAG_SIZE)       /* To prevent double declaration */
#error COM_RX_SIGNAL_FLAG_SIZE already defined
#endif /* (defined COM_RX_SIGNAL_FLAG_SIZE) */

/** \brief definition COM_RX_SIGNAL_FLAG_SIZE */
#define COM_RX_SIGNAL_FLAG_SIZE (COM_RX_SIGNAL_FLAG_SIGNAL_TYPE_SIZE + \
      COM_RX_SIGNAL_FLAG_ENDIANNESS_SIZE + \
      COM_RX_SIGNAL_FLAG_TIMEOUT_ACTION_SIZE + \
      COM_RX_SIGNAL_FLAG_UPDATE_BIT_SIZE +\
      COM_RX_SIGNAL_FLAG_DM_SIZE)


#if (defined COM_CHECK_VALUE_SIZE)        /* To prevent double declaration */
#error COM_CHECK_VALUE_SIZE already defined
#endif /* #if (defined COM_CHECK_VALUE_SIZE) */

#if (COM_DEV_ERROR_DETECT == STD_ON)

/** \brief Define COM_CHECK_VALUE_SIZE
 * defines if it shall be check if the value of a Tx signal fits into the Tx-Pdu
 * STD_ON Check turned on
 * STD_OFF Check turned off */
#define COM_CHECK_VALUE_SIZE COM_CHECK_VALUE_SIZE_ENABLE
#else
#define COM_CHECK_VALUE_SIZE STD_OFF
#endif /* (COM_DEV_ERROR_DETECT == STD_ON) */



#if (defined COM_FILTER_ONE_EVERY_N_SIZE_TYPE_MAX)        /* To prevent double declaration */
#error COM_FILTER_ONE_EVERY_N_SIZE_TYPE_MAX already defined
#endif /* #if (defined COM_FILTER_ONE_EVERY_N_SIZE_TYPE_MAX) */

#if (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON)

#if (COM_FILTER_ONE_EVERY_N_PERIOD_OFFSET_SIZE_MAX == COM_FILTER_ONE_EVERY_N_OCCURANCE_MAX)
#define COM_FILTER_ONE_EVERY_N_SIZE_TYPE_MAX COM_FILTER_ONE_EVERY_N_PERIOD_OFFSET_SIZE_MAX
#else
#error COM_FILTER_ONE_EVERY_N_PERIOD_OFFSET_SIZE_MAX shall be equal COM_FILTER_ONE_EVERY_N_OCCURANCE_MAX
#endif /* (COM_FILTER_ONE_EVERY_N_PERIOD_OFFSET_SIZE_MAX == COM_FILTER_ONE_EVERY_N_OCCURANCE_MAX) */

#endif /* (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON) */



#if (defined COM_VALUE_INIT_REPLACE)        /* To prevent double declaration */
#error COM_VALUE_INIT_REPLACE already defined
#endif /* #if (defined COM_VALUE_INIT_REPLACE) */

#if ((COM_RX_DATA_TOUT_ACTION != COM_RX_DATA_TOUT_ACTION_NONE) || \
      (COM_FILTER_RECEIVER_ENABLE == STD_ON))
#define COM_VALUE_INIT_REPLACE STD_ON
#else
#define COM_VALUE_INIT_REPLACE STD_OFF
#endif /* ((COM_RX_DATA_TOUT_ACTION != COM_RX_DATA_TOUT_ACTION_NONE) || \
      (COM_FILTER_RECEIVER_ENABLE == STD_ON)) */


#if (defined COM_SIGNALS_WITH_UB_RXDM_GW_ONLY)        /* To prevent double declaration */
#error COM_SIGNALS_WITH_UB_RXDM_GW_ONLY already defined
#endif /* #if (defined COM_SIGNALS_WITH_UB_RXDM_GW_ONLY) */

#if ((COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) && \
     ((COM_RX_TIMEOUT_FACTOR_SIZE != COM_SIZE_0_BIT) || (COM_SIGNAL_GW_ENABLE == STD_ON)))
#define COM_SIGNALS_WITH_UB_RXDM_GW_ONLY STD_ON
#else
#define COM_SIGNALS_WITH_UB_RXDM_GW_ONLY STD_OFF
#endif /* ((COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) && \
     ((COM_RX_TIMEOUT_FACTOR_SIZE != COM_SIZE_0_BIT) || (COM_SIGNAL_GW_ENABLE == STD_ON))) */


#if (defined COM_NOTIFY_RECEIVERS_ENABLE)        /* To prevent double declaration */
#error COM_NOTIFY_RECEIVERS_ENABLE already defined
#endif /* #if (defined COM_NOTIFY_RECEIVERS_ENABLE) */

#if ((COM_FILTER_RECEIVER_ENABLE == STD_ON) ||\
      (COM_CBK_RX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) ||\
      (COM_SIGNALS_WITH_UB_RXDM_GW_ONLY == STD_ON))
#define COM_NOTIFY_RECEIVERS_ENABLE STD_ON
#else
#define COM_NOTIFY_RECEIVERS_ENABLE STD_OFF
#endif


#if (defined COM_RX_SIGNAL_BUFFER_AVAILABLE)        /* To prevent double declaration */
#error COM_RX_SIGNAL_BUFFER_AVAILABLE already defined
#endif /* (defined COM_RX_SIGNAL_BUFFER_AVAILABLE) */

#if (COM_FILTER_RECEIVER_ENABLE == STD_ON)
#define COM_RX_SIGNAL_BUFFER_AVAILABLE STD_ON
#else
#define COM_RX_SIGNAL_BUFFER_AVAILABLE STD_OFF
#endif

#if (defined COM_TX_SIGNAL_BUFFER_AVAILABLE)        /* To prevent double declaration */
#error COM_TX_SIGNAL_BUFFER_AVAILABLE already defined
#endif /* (defined COM_TX_SIGNAL_BUFFER_AVAILABLE) */

#if ((COM_TXF_MASKNEWDIFFERSMASKOLD_EN == STD_ON) && (COM_TMS_ENABLE == STD_ON))
#define COM_TX_SIGNAL_BUFFER_AVAILABLE STD_ON
#else
#define COM_TX_SIGNAL_BUFFER_AVAILABLE STD_OFF
#endif


#if (defined COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX)        /* To prevent double declaration */
#error COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX already defined
#endif /* (defined COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX) */

#define COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX COM_SIGNAL_GROUP_ARRAY_SIZE_MAX

#if (defined COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX)        /* To prevent double declaration */
#error COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX already defined
#endif /* (defined COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX) */

#define COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX COM_SIGNAL_GROUP_ARRAY_SIZE_MAX


/** \brief COM_RCV_RX_SIG_GENERATED_SCHMENTER */
/** \brief COM_RCV_RX_SIG_GENERATED_SCHMEXIT */
/** \brief COM_RCV_RX_SIG_GENERATED_ATOMIC_ASSIGN8 */
/** \brief COM_RCV_RX_SIG_GENERATED_ATOMIC_ASSIGN16 */
/** \brief COM_RCV_RX_SIG_GENERATED_ATOMIC_ASSIGN32 */
#if (defined COM_RCV_RX_SIG_GENERATED_SCHMENTER)        /* To prevent double declaration */
#error COM_RCV_RX_SIG_GENERATED_SCHMENTER already defined
#endif /* #if (defined COM_RCV_RX_SIG_GENERATED_SCHMENTER) */

#if (defined COM_RCV_RX_SIG_GENERATED_SCHMEXIT)        /* To prevent double declaration */
#error COM_RCV_RX_SIG_GENERATED_SCHMEXIT already defined
#endif /* #if (defined COM_RCV_RX_SIG_GENERATED_SCHMEXIT) */

#if (defined COM_RCV_RX_SIG_GENERATED_ATOMIC_ASSIGN8)        /* To prevent double declaration */
#error COM_RCV_RX_SIG_GENERATED_ATOMIC_ASSIGN8 already defined
#endif /* #if (defined COM_RCV_RX_SIG_GENERATED_ATOMIC_ASSIGN8) */

#if (defined COM_RCV_RX_SIG_GENERATED_ATOMIC_ASSIGN16)        /* To prevent double declaration */
#error COM_RCV_RX_SIG_GENERATED_ATOMIC_ASSIGN16 already defined
#endif /* #if (defined COM_RCV_RX_SIG_GENERATED_ATOMIC_ASSIGN16) */

#if (defined COM_RCV_RX_SIG_GENERATED_ATOMIC_ASSIGN32)        /* To prevent double declaration */
#error COM_RCV_RX_SIG_GENERATED_ATOMIC_ASSIGN32 already defined
#endif /* #if (defined COM_RCV_RX_SIG_GENERATED_ATOMIC_ASSIGN32) */

#if (defined COM_RCV_RX_SIG_LOCK_GENERATED)
#if (COM_RCV_RX_SIG_LOCK_GENERATED == STD_ON)
#define COM_RCV_RX_SIG_GENERATED_SCHMENTER() \
   Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0()

#define COM_RCV_RX_SIG_GENERATED_SCHMEXIT() \
   Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0()

#define COM_RCV_RX_SIG_GENERATED_ATOMIC_ASSIGN8(to, from) \
   TS_AtomicAssign8((to), (from))

#define COM_RCV_RX_SIG_GENERATED_ATOMIC_ASSIGN16(to, from) \
   TS_AtomicAssign16((to), (from))

#define COM_RCV_RX_SIG_GENERATED_ATOMIC_ASSIGN32(to, from) \
   TS_AtomicAssign32((to), (from))

#else
#define COM_RCV_RX_SIG_GENERATED_SCHMENTER()
#define COM_RCV_RX_SIG_GENERATED_SCHMEXIT()
#define COM_RCV_RX_SIG_GENERATED_ATOMIC_ASSIGN8(to, from) ((to) = (from))
#define COM_RCV_RX_SIG_GENERATED_ATOMIC_ASSIGN16(to, from) ((to) = (from))
#define COM_RCV_RX_SIG_GENERATED_ATOMIC_ASSIGN32(to, from) ((to) = (from))
#endif /* (COM_RCV_RX_SIG_LOCK_GENERATED == STD_ON) */
#endif /* (defined COM_RCV_RX_SIG_LOCK_GENERATED) */


/** \brief COM_GENERATED_RCV_SIG_ENABLE */
#if (!defined COM_GENERATED_RCV_SIG_ENABLE)
#define COM_GENERATED_RCV_SIG_ENABLE STD_OFF
#endif /* (!defined COM_GENERATED_RCV_SIG_ENABLE) */


/** \brief COM_EVALUATE_TRIGGERED_OC */
#if (defined COM_EVALUATE_TRIGGERED_OC)        /* To prevent double declaration */
#error COM_EVALUATE_TRIGGERED_OC already defined
#endif /* #if (defined COM_EVALUATE_TRIGGERED_OC) */

#if ((COM_TM_AVAILABLE == STD_ON) && (COM_TRANSF_PROP_TRIGGERED_OC_ENABLE == STD_ON))
#define COM_EVALUATE_TRIGGERED_OC STD_ON
#else
#define COM_EVALUATE_TRIGGERED_OC STD_OFF
#endif /* ((COM_TM_AVAILABLE == STD_ON) && (COM_TRANSF_PROP_TRIGGERED_OC_ENABLE == STD_ON)) */


/** \brief COM_SENDUPONAPICALL */
#if (defined COM_SENDUPONAPICALL)        /* To prevent double declaration */
#error COM_SENDUPONAPICALL already defined
#endif /* #if (defined COM_SENDUPONAPICALL) */

#if ((COM_TM_AVAILABLE == STD_ON) && \
      ((COM_TRANSF_PROP_TRIGGERED_OC_ENABLE == STD_ON) || \
       (COM_TRANSF_PROP_TRIGGERED_ENABLE == STD_ON) || \
       (COM_TMS_ENABLE == STD_ON)))
#define COM_SENDUPONAPICALL STD_ON
#else
#define COM_SENDUPONAPICALL STD_OFF
#endif /* ((COM_TM_AVAILABLE == STD_ON) && \
      ((COM_TRANSF_PROP_TRIGGERED_OC_ENABLE == STD_ON) || \
       (COM_TRANSF_PROP_TRIGGERED_ENABLE == STD_ON) || \
       (COM_TMS_ENABLE == STD_ON)))) */


/** \brief COM_SENDUPONAPICALL_AND_SIGGW */
#if (defined COM_SENDUPONAPICALL_AND_SIGGW)        /* To prevent double declaration */
#error COM_SENDUPONAPICALL_AND_SIGGW already defined
#endif /* #if (defined COM_SENDUPONAPICALL_AND_SIGGW) */

#if ((COM_SENDUPONAPICALL == STD_ON) && (COM_SIGNAL_GW_ENABLE == STD_ON))
#define COM_SENDUPONAPICALL_AND_SIGGW STD_ON
#else
#define COM_SENDUPONAPICALL_AND_SIGGW STD_OFF
#endif /* ((COM_SENDUPONAPICALL == STD_ON) && (COM_SIGNAL_GW_ENABLE == STD_ON)) */


/** \brief COM_CONST_INIT_ARRAY_SIZE */
#if (defined COM_CONST_INIT_ARRAY_SIZE)        /* To prevent double declaration */
#error COM_CONST_INIT_ARRAY_SIZE already defined
#endif /* #if (defined COM_CONST_INIT_ARRAY_SIZE) */

#define COM_CONST_INIT_ARRAY_SIZE 9U


/** \brief COM_CONST_INIT_START_IDX */
#if (defined COM_CONST_INIT_START_IDX)        /* To prevent double declaration */
#error COM_CONST_INIT_START_IDX already defined
#endif /* #if (defined COM_CONST_INIT_START_IDX) */

#define COM_CONST_INIT_START_IDX ((COM_CONST_INIT_ARRAY_SIZE + 1U) / 2U)


/** \brief COM_IPDU_GROUP_VECTOR_NUM_BYTES */
#if (defined COM_IPDU_GROUP_VECTOR_NUM_BYTES)        /* To prevent double declaration */
#error COM_IPDU_GROUP_VECTOR_NUM_BYTES already defined
#endif /* #if (defined COM_IPDU_GROUP_VECTOR_NUM_BYTES) */

#define COM_IPDU_GROUP_VECTOR_NUM_BYTES (((COM_SUPPORTED_IPDU_GROUPS - 1U) / 8U) + 1U)


/** \brief Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0
 * maps the entry point of the EXCLUSIVE_AREA_0 to the SchM API */
#define Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0() \
   SchM_Enter_Com_SCHM_COM_EXCLUSIVE_AREA_0()

/** \brief Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0
 * maps the exit point of the EXCLUSIVE_AREA_0 to the SchM API */
#define Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0() \
   SchM_Exit_Com_SCHM_COM_EXCLUSIVE_AREA_0()


/** \brief Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_1
 * mapps the entry point of the EXCLUSIVE_AREA_1 to the SchM API */
#define Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_1() \
   SchM_Enter_Com_SCHM_COM_EXCLUSIVE_AREA_1()

/** \brief Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_1
 * maps the exit point of the EXCLUSIVE_AREA_1 to the SchM API */
#define Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_1() \
   SchM_Exit_Com_SCHM_COM_EXCLUSIVE_AREA_1()


/** \brief COM_EVALUATE_TRANSMIT_RET_VAL */
#if (defined COM_EVALUATE_TRANSMIT_RET_VAL)        /* To prevent double declaration */
#error COM_EVALUATE_TRANSMIT_RET_VAL already defined
#endif /* #if (defined COM_EVALUATE_TRANSMIT_RET_VAL) */

#if (((COM_CL_UB_TX_TRANSMIT_ENABLE == STD_ON) && \
      (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)) || \
      (COM_RETRY_FAILED_TRANSMIT_REQ == STD_ON))

#define COM_EVALUATE_TRANSMIT_RET_VAL STD_ON
#else
#define COM_EVALUATE_TRANSMIT_RET_VAL STD_OFF
#endif


/** \brief COM_GENERIC_READ_REQUIRED */
#if (defined COM_GENERIC_READ_REQUIRED)        /* To prevent double declaration */
#error COM_GENERIC_READ_REQUIRED already defined
#endif /* #if (defined COM_GENERIC_READ_REQUIRED) */

#if ((COM_FILTER_RECEIVER_ENABLE == STD_ON) || \
     ((COM_TXF_MASKNEWDIFFERSMASKOLD_EN == STD_ON) && (COM_TMS_ENABLE == STD_ON)) || \
     (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON) || \
     (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) || \
     (COM_SIGNAL_GW_ENABLE == STD_ON) || \
     (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) \
    )
#define COM_GENERIC_READ_REQUIRED STD_ON
#else
#define COM_GENERIC_READ_REQUIRED STD_OFF
#endif

#endif /*COM_RULES_H_ */
