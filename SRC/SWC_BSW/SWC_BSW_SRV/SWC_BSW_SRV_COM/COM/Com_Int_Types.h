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
#ifndef COM_INT_TYPES_H_
#define COM_INT_TYPES_H_
/*==================[inclusions]============================================*/

#include <TSAutosar.h>          /* EB specific standard types */
#include <Compiler.h>

#include <Com_Rules.h>
#include <ComStack_Types.h>     /* AUTOSAR Standard types */
#include <Com_Types.h>          /* Generated data types of the Com module */

/*==================[macros]================================================*/

/** \brief definition COM_REF2CONFIG(type)
 * macro used to define define a configuration structure element as
 * a relative offset
 */
#if (COM_RELOCATABLE_CFG_ENABLE == STD_ON)
#define COM_REF2CONFIG(type) \
    CONST(Com_ConfigOffsetType, AUTOMATIC)
#elif (COM_RELOCATABLE_CFG_ENABLE == STD_OFF)
#define COM_REF2CONFIG(type) \
    P2CONST(type, AUTOMATIC, COM_APPL_CONST)
#endif /* (COM_RELOCATABLE_CFG_ENABLE == STD_ON) */



#if (defined COM_CBK_TX_T_OUT_IDX_FUNC_PTR_NULL)        /* To prevent double declaration */
#error COM_CBK_TX_T_OUT_IDX_FUNC_PTR_NULL already defined
#endif /* if (defined COM_CBK_TX_T_OUT_IDX_FUNC_PTR_NULL) */

/** \brief definition COM_CBK_TX_T_OUT_IDX_FUNC_PTR_NULL */
#define COM_CBK_TX_T_OUT_IDX_FUNC_PTR_NULL COM_CBK_TX_T_OUT_ARRAY_SIZE_MAX


#if (defined COM_CBK_RX_T_OUT_IDX_FUNC_PTR_NULL)        /* To prevent double declaration */
#error COM_CBK_RX_T_OUT_IDX_FUNC_PTR_NULL already defined
#endif /* if (defined COM_CBK_RX_T_OUT_IDX_FUNC_PTR_NULL) */

/** \brief definition COM_CBK_RX_T_OUT_IDX_FUNC_PTR_NULL */
#define COM_CBK_RX_T_OUT_IDX_FUNC_PTR_NULL COM_CBK_RX_T_OUT_ARRAY_SIZE_MAX


#if (defined COM_CALL_OUT_FUNC_PTR_NULL)        /* To prevent double declaration */
#error COM_CALL_OUT_FUNC_PTR_NULL already defined
#endif /* if (defined COM_CALL_OUT_FUNC_PTR_NULL) */

/** \brief definition COM_CALL_OUT_FUNC_PTR_NULL */
#define COM_CALL_OUT_FUNC_PTR_NULL COM_CALL_OUT_FUNC_PTR_ARRAY_SIZE_MAX


#if (defined COM_CBK_TX_ACK_FUNC_PTR_NULL)        /* To prevent double declaration */
#error COM_CBK_TX_ACK_FUNC_PTR_NULL already defined
#endif /* if (defined COM_CBK_TX_ACK_FUNC_PTR_NULL) */

/** \brief definition of the COM_CBK_TX_ACK_FUNC_PTR_NULL */
#define COM_CBK_TX_ACK_FUNC_PTR_NULL COM_CBK_TX_ACK_PTR_ARRAY_SIZE_MAX


#if (defined COM_CBK_RX_ACK_FUNC_PTR_NULL)        /* To prevent double declaration */
#error COM_CBK_RX_ACK_FUNC_PTR_NULL already defined
#endif /* if (defined COM_CBK_RX_ACK_FUNC_PTR_NULL) */

/** \brief definition of the COM_CBK_RX_ACK_FUNC_PTR_NULL */
#define COM_CBK_RX_ACK_FUNC_PTR_NULL COM_CBK_RX_ACK_PTR_ARRAY_SIZE_MAX


#if (defined COM_IPDU_INVALID)        /* To prevent double declaration */
#error COM_IPDU_INVALID already defined
#endif /* if (defined COM_IPDU_INVALID) */

/** \brief definition of the COM_IPDU_INVALID */
#define COM_IPDU_INVALID COM_IPDU_ARRAY_SIZE_MAX

#if (defined COM_SIGNAL_BUFFER_REF_INVALID)        /* To prevent double declaration */
#error COM_SIGNAL_BUFFER_REF_INVALID already defined
#endif /* if (defined COM_SIGNAL_BUFFER_REF_INVALID) */

/** \brief definition of the COM_SIGNAL_BUFFER_REF_INVALID */
#define COM_SIGNAL_BUFFER_REF_INVALID COM_SIGNAL_BUFFER_REF_SIZE_MAX


#if (defined COM_CBK_TX_ERR_PTR_NULL)        /* To prevent double declaration */
#error COM_CBK_TX_ERR_PTR_NULL already defined
#endif /* if (defined COM_CBK_TX_ERR_PTR_NULL) */

/** \brief definition of the COM_CBK_TX_ERR_PTR_NULL */
#define COM_CBK_TX_ERR_PTR_NULL COM_CBK_TX_ERR_PTR_ARRAY_SIZE_MAX


#if (defined COM_SIGNAL_INVALID)        /* To prevent double declaration */
#error COM_SIGNAL_INVALID already defined
#endif /* if (defined COM_SIGNAL_INVALID) */

/** \brief definition of the COM_SIGNAL_INVALID */
#define COM_SIGNAL_INVALID COM_SIGNAL_ARRAY_SIZE_MAX


#if (defined COM_TX_MODE_INVALID)        /* To prevent double declaration */
#error COM_TX_MODE_INVALID already defined
#endif /* if (defined COM_TX_MODE_INVALID) */

#if (COM_TM_AVAILABLE == STD_ON)
/** \brief definition of the COM_TX_MODE_INVALID */
#define COM_TX_MODE_INVALID COM_TX_MODE_ARRAY_SIZE_MAX
#endif /* #if (COM_TM_AVAILABLE == STD_ON) */


#if (defined COM_SIGNAL_GROUP_INVALID)        /* To prevent double declaration */
#error COM_SIGNAL_GROUP_INVALID already defined
#endif /* if (defined COM_SIGNAL_GROUP_INVALID) */

/** \brief definition of the COM_SIGNAL_GROUP_INVALID */
#define COM_SIGNAL_GROUP_INVALID COM_SIGNAL_GROUP_ARRAY_SIZE_MAX


#if (defined COM_GROUP_SIGNAL_INVALID)        /* To prevent double declaration */
#error COM_GROUP_SIGNAL_INVALID already defined
#endif /* if (defined COM_GROUP_SIGNAL_INVALID) */

/** \brief definition of the COM_GROUP_SIGNAL_INVALID */
#define COM_GROUP_SIGNAL_INVALID COM_GROUP_SIGNAL_ARRAY_SIZE_MAX


#if (COM_RX_FIRST_TIMEOUT_FACTOR_SIZE > COM_RX_TIMEOUT_FACTOR_SIZE)
#define COM_RX_DM_QUEUE_SIZE COM_RX_FIRST_TIMEOUT_FACTOR_SIZE
#else
#define COM_RX_DM_QUEUE_SIZE COM_RX_TIMEOUT_FACTOR_SIZE
#endif /* (COM_RX_FIRST_TIMEOUT_FACTOR_SIZE > COM_RX_TIMEOUT_FACTOR_SIZE) */

#if (COM_RX_SIGNAL_BASED_DM == STD_ON)
#define COM_RX_DM_SIGNAL_QUEUE_SIZE COM_RX_DM_QUEUE_SIZE
#else
#define COM_RX_DM_SIGNAL_QUEUE_SIZE 0U
#endif /* (COM_RX_SIGNAL_BASED_DM == STD_ON) */


#if (defined COM_GLOBAL_TIME)   /* To prevent double declaration */
#error COM_GLOBAL_TIME already defined
#endif /* (defined COM_GLOBAL_TIME) */

/** \brief definition of COM_GLOBAL_TIME */
#if ((COM_TX_MODE_TIME_PERIOD_FACTOR_SIZE == COM_SIZE_32_BIT) || \
      (COM_TX_MODE_TIME_OFFSET_FACTOR_SIZE == COM_SIZE_32_BIT) || \
      (COM_TX_MODE_REPETITION_PERIOD_FACTOR_SIZE == COM_SIZE_32_BIT) || \
      ((COM_RX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) && (COM_RX_DM_QUEUE_SIZE == COM_SIZE_32_BIT)) || \
      ((COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) && (COM_TX_TIMEOUT_FACTOR_SIZE == COM_SIZE_32_BIT)) || \
      ((COM_MDT_QUEUE_AVAILABLE == STD_ON) && (COM_TX_IPDU_MINIMUM_DELAY_TIME_FACTOR_SIZE == COM_SIZE_32_BIT)))
#define COM_GLOBAL_TIME COM_SIZE_32_BIT
#elif ((COM_TX_MODE_TIME_PERIOD_FACTOR_SIZE == COM_SIZE_16_BIT) || \
      (COM_TX_MODE_TIME_OFFSET_FACTOR_SIZE == COM_SIZE_16_BIT) || \
      (COM_TX_MODE_REPETITION_PERIOD_FACTOR_SIZE == COM_SIZE_16_BIT) || \
      ((COM_RX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) && (COM_RX_DM_QUEUE_SIZE == COM_SIZE_16_BIT)) || \
      ((COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) && (COM_TX_TIMEOUT_FACTOR_SIZE == COM_SIZE_16_BIT)) || \
      ((COM_MDT_QUEUE_AVAILABLE == STD_ON) && (COM_TX_IPDU_MINIMUM_DELAY_TIME_FACTOR_SIZE == COM_SIZE_16_BIT)))
#define COM_GLOBAL_TIME COM_SIZE_16_BIT
#elif ((COM_TX_MODE_TIME_PERIOD_FACTOR_SIZE == COM_SIZE_8_BIT) || \
      (COM_TX_MODE_TIME_OFFSET_FACTOR_SIZE == COM_SIZE_8_BIT) || \
      (COM_TX_MODE_REPETITION_PERIOD_FACTOR_SIZE == COM_SIZE_8_BIT) || \
      ((COM_RX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) && (COM_RX_DM_QUEUE_SIZE == COM_SIZE_8_BIT)) || \
      ((COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) && (COM_TX_TIMEOUT_FACTOR_SIZE == COM_SIZE_8_BIT)) || \
      ((COM_MDT_QUEUE_AVAILABLE == STD_ON) && (COM_TX_IPDU_MINIMUM_DELAY_TIME_FACTOR_SIZE == COM_SIZE_8_BIT)))
#define COM_GLOBAL_TIME COM_SIZE_8_BIT
#else
#define COM_GLOBAL_TIME COM_SIZE_0_BIT
#endif


#if (defined COM_SIGNAL_DESC_CAST)        /* To prevent double declaration */
#error COM_SIGNAL_DESC_CAST already defined
#endif /* if (defined COM_SIGNAL_DESC_CAST) */

/** \brief definition COM_SIGNAL_DESC_CAST - cast macro depending on
 * pre-compile-time setting  of COM_SIGNAL_BYTE_ALIGN
 */
#define COM_SIGNAL_DESC_CAST(statement) (statement)


#if (COM_PERIODIC_QUEUE_AVAILABLE == STD_ON)

/** \brief definition of the Com_PeriodicSendNextDueTimeType */
#if (COM_TX_MODE_TIME_PERIOD_FACTOR_SIZE != COM_SIZE_0_BIT)
#if (COM_TX_MODE_TIME_PERIOD_FACTOR_SIZE > COM_TX_MODE_TIME_OFFSET_FACTOR_SIZE)
typedef ComTxModeTimePeriodFactorType Com_PeriodicSendNextDueTimeType;
#define COM_PERIODIC_QUEUE_SIZE COM_TX_MODE_TIME_PERIOD_FACTOR_SIZE
#else
typedef ComTxModeTimeOffsetFactorType Com_PeriodicSendNextDueTimeType;
#define COM_PERIODIC_QUEUE_SIZE COM_TX_MODE_TIME_OFFSET_FACTOR_SIZE
#endif /* (COM_TX_MODE_TIME_PERIOD_FACTOR_SIZE > COM_TX_MODE_TIME_OFFSET_FACTOR_SIZE) */
#else
#define COM_PERIODIC_QUEUE_SIZE COM_SIZE_0_BIT
#endif /* (COM_TX_MODE_TIME_PERIOD_FACTOR_SIZE == COM_SIZE_0_BIT) */

#endif /* (COM_PERIODIC_QUEUE_AVAILABLE == STD_ON) */


/** \brief Definition of constant COM_EB_UNINIT */
#if (defined COM_EB_UNINIT)        /* To prevent double declaration */
#error COM_EB_UNINIT already defined
#endif /* if (defined COM_EB_UNINIT) */

/** \brief Define COM_EB_UNINIT */
#define COM_EB_UNINIT 0U

/** \brief Definition of constant COM_EB_INIT */
#if (defined COM_EB_INIT)          /* To prevent double declaration */
#error COM_EB_INIT already defined
#endif /* if (defined COM_EB_INIT) */

/** \brief Define COM_EB_INIT */
#define COM_EB_INIT 1U


/*==================[type definitions]======================================*/

/** \brief definition of the Com_ConfigDataRefType, compiler-abstracted */
typedef P2CONST(void, AUTOMATIC, COM_APPL_CONST) Com_ConfigDataRefType;

/** \brief definition of the Com_TS_SignalTypeType */
typedef uint8 Com_TS_SignalTypeType;

/** \brief definition of the Com_TS_SignalEndiannessType */
typedef uint8 Com_TS_SignalEndiannessType;

/** \brief definition of the Com_IpduGroupModeType */
typedef uint8 Com_IpduGroupModeType;

#if (COM_RX_TIMEOUT_FACTOR_AVAILABLE == STD_ON)

#if (COM_RX_FIRST_TIMEOUT_FACTOR_SIZE > COM_RX_TIMEOUT_FACTOR_SIZE)
typedef ComRxFirstTimeoutFactorType Com_RxDMNextDueTimeType;
#else
typedef ComRxTimeoutFactorType Com_RxDMNextDueTimeType;
#endif /* (COM_RX_FIRST_TIMEOUT_FACTOR_SIZE > COM_RX_TIMEOUT_FACTOR_SIZE) */

#endif /* (COM_RX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) */


/** \brief definition of the ComGlobalTimeType */
#if (COM_GLOBAL_TIME == COM_SIZE_0_BIT)
#elif (COM_GLOBAL_TIME == COM_SIZE_8_BIT)
typedef uint8 ComGlobalTimeType;
#elif (COM_GLOBAL_TIME == COM_SIZE_16_BIT)
typedef uint16 ComGlobalTimeType;
#elif (COM_GLOBAL_TIME == COM_SIZE_32_BIT)
typedef uint32 ComGlobalTimeType;
#endif


/** \brief definition of the ComCommonReadPropType */
typedef struct
{
   /* reference to buffer to which the signal / group signal is associated */
   P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) pdudataptrRAM;
#if (COM_SIGNAL_INIT_VALUE_ENABLE == STD_ON)
   /* reference to initial data of buffer to which the signal / group signal is associated */
   P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) pdudataptrROM;
#endif /* (COM_SIGNAL_INIT_VALUE_ENABLE == STD_ON) */
#if (COM_FILTER_RECEIVER_ENABLE == STD_ON)
   /* reference to a buffer if a filter is configured for the signal,
    * else COM_SIGNAL_BUFFER_REF_INVALID */
   ComSignalBufferRefType ComFilterSignalValueRef;
#endif /* (COM_FILTER_RECEIVER_ENABLE == STD_ON) */
   /* ComBitPosition
    * If (COM_SIGNAL_BYTE_ALIGN == STD_ON) (all signals starts on byte borders)
    * ComSignalPositionInByte describes the byte where the signal starts
    * If (COM_SIGNAL_BYTE_ALIGN == STD_OFF) (AUTOSAR COM 3.0)
    * ComSignalPositionInBit describes in bits where the signal starts */
#if (COM_SIGNAL_BYTE_ALIGN == STD_ON)
   /* Starting position in BITS for BOOLEAN signals and for all other signals in BYTES */
   ComSignalDescBitType ComSignalPositionInByte;
#elif (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
   /* Starting position of the signals in bits NOTE: for COM_UINT8_N in bytes */
   ComSignalDescBitType ComSignalPositionInBit;
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_ON) */
   /* Size of the signal bits NOTE: for COM_UINT8_N in bytes */
   ComSignalBitSizeType ComBitSize;
#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
   Com_TS_SignalEndiannessType Endianness;
#endif /* (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE) */
   Com_TS_SignalTypeType SignalType;    /* signal type of the signal */
#if (COM_VALUE_INIT_REPLACE == STD_ON)
   boolean TakePtrROM;
#endif /* (COM_VALUE_INIT_REPLACE == STD_ON) */
} ComCommonReadPropType;


#if (COM_FILTER_AVAILABLE == STD_ON)
/** \brief definition of the ComCommonFilterPropertiesType */
typedef struct
{
   ComSignalBufferRefType ComOldValueRef;  /* reference to buffer of filter */
   ComFilterRefType ComFilterRef; /* reference to filter configuration */
   /* COM_F_NEVER,
    * COM_F_ALWAYS,
    * COM_F_MASK_NEW_DIFFERS_MASK_OLD,
    * COM_F_MASKED_NEW_DIFFERS_X,
    * COM_F_MASKED_NEW_EQUALS_X,
    * COM_F_NEW_IS_OUTSIDE,
    * COM_F_NEW_IS_WITHIN,
    * COM_F_ONE_EVERY_N */
   uint8 ComFilterType;
} ComCommonFilterPropertiesType;
#endif /* (COM_FILTER_AVAILABLE == STD_ON) */

/** \brief definition of the ComCommonWritePropType */
typedef struct
{

   /* pointer where the data shall be written */
   P2VAR(uint8, TYPEDEF, COM_VAR_NOINIT) dataPtr;
#if (COM_SIGNAL_BYTE_ALIGN == STD_ON)
   /* Starting position in BITS for BOOLEAN signals and
    * for all other signals in BYTES within the Signal Group
    * NOTE: not within the I-Pdu as given in the configuration */
   ComSignalDescBitType ComSignalPositionInByte;
#elif (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
   /* Starting position of the group signals in bits of the signal group
    * NOTE: the position is the position of the signal within the signal group buffer.
    * If the signal group is not byte-aligned in the I-Pdu
    * the size of the buffer of signal group buffer is extended so that the signal group buffer
    * is aligned to the I-Pdu byte borders */
   ComSignalDescBitType ComSignalPositionInBit;
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_ON) */

#if (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)
   /* Update bit position of the signal group in bits */
   ComSignalDescBitType ComUpdateBitPositionInBit;
#endif /* (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) */

   ComSignalBitSizeType size;
#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
   Com_TS_SignalEndiannessType endianness;
#endif

#if (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL)
   boolean updateBit;  /* defines if an update bit is configured */
#endif /* (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL) */

} ComCommonWritePropType;

/** \brief definition of the Com_EB_StatusType */
typedef uint8 Com_EB_StatusType;


/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /*COM_INT_TYPES_H_ */
/*==================[end of file]===========================================*/

