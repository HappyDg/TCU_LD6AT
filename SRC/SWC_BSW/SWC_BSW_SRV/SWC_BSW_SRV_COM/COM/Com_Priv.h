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
 * MISRA-1) Deviated Rule: 11.3 (advisory)
 * "A cast should not be performed between a pointer type and an integral type."
 *
 * Reason:
 * Actually this is not a cast between a pointer and a integral type, since 0
 * is the null pointer constant.
 *
 *
 * MISRA-2: Deviated Rule: 19.6 (required)
 * "#undef' shall not be used"
 *
 * Reason:
 * The macro TS_RELOCATABLE_CFG_ENABLE might be used by more modules than the
 * Com modules. To avoid that this macro is used by other modules accidentally
 * a undef is used here.
 *
 */

#if (!defined COM_PRIV_H)
#define COM_PRIV_H

/*==================[inclusions]============================================*/

#include <TSAutosar.h>          /* EB specific standard types */
#include <Com_Api.h>                /* get module interface */
#include <Com_Lcfg_Static.h>    /* declaration of the callback arrays */
#include <Com_Version.h>        /* declaration of COM_MODULE_ID */
#define TS_RELOCATABLE_CFG_ENABLE COM_RELOCATABLE_CFG_ENABLE
#include <TSPBConfig_Access.h>  /* Post Build Config Helpers */
/* Deviation MISRA-2 */
#undef TS_RELOCATABLE_CFG_ENABLE

/*==================[version check]=========================================*/

/*==================[macros]================================================*/

#if (COM_DEV_ERROR_DETECT == STD_ON)
#include <Det.h>                /* get development error tracer interface */

/** \brief Define COM_DET_REPORTERROR
 * macro for simplified DET usage - map to Det - API function call
 */
#define COM_DET_REPORTERROR(nErrorID, nFuncID) \
    COM_DET_REPORTERROR_HLP(nErrorID, nFuncID)

#define COM_DET_REPORTERROR_HLP(nErrorID, nFuncID)      \
    (void)Det_ReportError(                              \
        ((uint16) COM_MODULE_ID),                       \
        ((uint8) 0U),                                   \
        ((uint8) (nFuncID)),                            \
        ((uint8) (nErrorID))                            \
        )

#endif /* (COM_DEV_ERROR_DETECT == STD_ON) */


/** \brief Define COM_GET_CONFIG_ADDR
 * macro for getting a reference to a config element
 */

/* there are MISRA deviations in TS_UNCHECKEDGETCFG */
#define COM_GET_CONFIG_ADDR_NOCHK(type, offset) \
TS_UNCHECKEDGETCFG(Com_gConfigPtr, type, COM, offset)

/* there are MISRA deviations in TS_CHECKEDGETCFG */
#define COM_GET_CONFIG_ADDR(type, offset) \
TS_CHECKEDGETCFG(Com_gConfigPtr, type, COM, offset)


#if (COM_CONST_CFG_ADDRESS_ENABLE == STD_ON)
/** \brief Define Com_gConfigPtr
 * root config pointer is replaced by absolute address that is given via
 * pre-compile-time switch COM_CONST_CONFIG_ADDRESS
 */
#define Com_gConfigPtr \
    ((P2CONST(Com_ConfigType, COM_VAR_FAST, COM_APPL_CONST)) \
    COM_CONST_CFG_ADDRESS)
#endif /* COM_CONST_CFG_ADDRESS_ENABLE */


/** \brief COM_GET_MEMPTR
 * Provides a pointer of type \p type to the Com memory
 * \param[in] type defines the type of the provided pointer
 * \param[in] offset in Com memory in bytes
 * \retval None */
#define COM_GET_MEMPTR(type, offset)                                           \
    ( (P2VAR(type, AUTOMATIC, COM_VAR_NOINIT))                                 \
      ( (P2VAR(void, AUTOMATIC, COM_VAR_NOINIT)) &Com_gDataMemPtr[(offset)] )  \
    )


#if (defined COM_TXPDU_STARTED) /* To prevent double declaration */
#error COM_TXPDU_STARTED already defined
#endif /* if (defined COM_TXPDU_STARTED) */

/** \brief Define COM_TXPDU_STARTED */
#define COM_TXPDU_STARTED 0U

#if (defined COM_TXPDU_MDTQUEUED)       /* To prevent double declaration */
#error COM_TXPDU_MDTQUEUED already defined
#endif /* if (defined COM_TXPDU_MDTQUEUED) */

/** \brief Define COM_TXPDU_MDTQUEUED */
#define COM_TXPDU_MDTQUEUED 1U

#if (defined COM_TXPDU_PERIODICSENDQUEUED)      /* To prevent double declaration */
#error COM_TXPDU_PERIODICSENDQUEUED already defined
#endif /* if (defined COM_TXPDU_PERIODICSENDQUEUED) */

/** \brief Define COM_TXPDU_PERIODICSENDQUEUED */
#define COM_TXPDU_PERIODICSENDQUEUED 2U

#if (defined COM_TXPDU_NTIMESSENDQUEUED)        /* To prevent double declaration */
#error COM_TXPDU_NTIMESSENDQUEUED already defined
#endif /* if (defined COM_TXPDU_NTIMESSENDQUEUED) */

/** \brief Define COM_TXPDU_NTIMESSENDQUEUED */
#define COM_TXPDU_NTIMESSENDQUEUED 3U

#if (defined COM_TXPDU_SENDIMMEDIATELY) /* To prevent double declaration */
#error COM_TXPDU_SENDIMMEDIATELY already defined
#endif /* if (defined COM_TXPDU_SENDIMMEDIATELY) */

/** \brief Define COM_TXPDU_SENDIMMEDIATELY */
#define COM_TXPDU_SENDIMMEDIATELY 4U

#if (defined COM_TXPDU_TXDMQUEUED)      /* To prevent double declaration */
#error COM_TXPDU_TXDMQUEUED already defined
#endif /* if (defined COM_TXPDU_TXDMQUEUED) */

/** \brief Define COM_TXPDU_TXDMQUEUED */
#define COM_TXPDU_TXDMQUEUED 5U

#if (COM_TM_AVAILABLE == STD_ON)
#if (defined COM_TXPDU_TMSSTATE)        /* To prevent double declaration */
#error COM_TXPDU_TMSSTATE already defined
#endif /* if (defined COM_TXPDU_TMSSTATE) */

/** \brief Define COM_TXPDU_TMSSTATE */
#define COM_TXPDU_TMSSTATE 6U

#if (defined COM_TXPDU_TMSCHANGED)  /* To prevent double declaration */
#error COM_TXPDU_TMSCHANGED already defined
#endif /* if (defined COM_TXPDU_TMSCHANGED) */

/** \brief Define COM_TXPDU_TMSCHANGED */
#define COM_TXPDU_TMSCHANGED 7U
#endif /* (COM_TM_AVAILABLE == STD_ON) */


#if (defined COM_RXPDU_STARTED) /* To prevent double declaration */
#error COM_RXPDU_STARTED already defined
#endif /* if (defined COM_RXPDU_STARTED) */

/** \brief Define COM_RXPDU_STARTED */
#define COM_RXPDU_STARTED 0U

#if (defined COM_RXPDU_RXDMRUNNING)     /* To prevent double declaration */
#error COM_RXPDU_RXDMRUNNING already defined
#endif /* if (defined COM_RXPDU_RXDMRUNNING) */

/** \brief Define COM_RXPDU_RXDMRUNNING */
#define COM_RXPDU_RXDMRUNNING 1U

#if (defined COM_RXPDU_RXDMTIMEOUT)     /* To prevent double declaration */
#error COM_RXPDU_RXDMTIMEOUT already defined
#endif /* if (defined COM_RXPDU_RXDMTIMEOUT) */

/** \brief Define COM_RXPDU_RXDMTIMEOUT */
#define COM_RXPDU_RXDMTIMEOUT 2U

#if (defined COM_RXPDU_RXDEFNOTIFY)     /* To prevent double declaration */
#error COM_RXPDU_RXDEFNOTIFY already defined
#endif /* if (defined COM_RXPDU_RXDEFNOTIFY) */

/** \brief Define COM_RXPDU_RXDEFNOTIFY */
#define COM_RXPDU_RXDEFNOTIFY 3U

#if (COM_RX_FIRST_TIMEOUT_FACTOR_SIZE != COM_SIZE_0_BIT)

#if (defined COM_RXPDU_RXDMSWITCHON)     /* To prevent double declaration */
#error COM_RXPDU_RXDMSWITCHON already defined
#endif /* if (defined COM_RXPDU_RXDMSWITCHON) */

/** \brief Define COM_RXPDU_RXDMSWITCHON */
/* indicates that RxDM is switch on */
#define COM_RXPDU_RXDMSWITCHON 4U

#endif /* (COM_RX_FIRST_TIMEOUT_FACTOR_SIZE != COM_SIZE_0_BIT) */

/** \brief Define COM_CONST_NULL_PTR */
/* Deviation MISRA-1 */
#define COM_CONST_NULL_PTR ((P2CONST(void, AUTOMATIC, COM_APPL_CONST)) 0)


/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/


#define COM_START_SEC_VAR_FAST_8BIT
#include <MemMap.h>

/** \brief Com_InitStatus
 * global variable for the actual initialization status of the Com */
extern VAR(Com_EB_StatusType, COM_VAR_FAST) Com_InitStatus;

#if (COM_GLOBAL_TIME == COM_SIZE_8_BIT)
/** \brief Com_GlobalTime (8 bit)
 * time in COM specific ticks */
extern VAR(ComGlobalTimeType, COM_VAR_FAST) Com_GlobalTime;
#endif /* (COM_GLOBAL_TIME == COM_SIZE_8_BIT) */

#define COM_STOP_SEC_VAR_FAST_8BIT
#include <MemMap.h>


#define COM_START_SEC_VAR_FAST_16BIT
#include <MemMap.h>

#if (COM_GLOBAL_TIME == COM_SIZE_16_BIT)
/** \brief Com_GlobalTime (16 bit)
 * time in COM specific ticks */
extern VAR(ComGlobalTimeType, COM_VAR_FAST) Com_GlobalTime;
#endif /* (COM_GLOBAL_TIME == COM_SIZE_16_BIT) */

#define COM_STOP_SEC_VAR_FAST_16BIT
#include <MemMap.h>


#define COM_START_SEC_VAR_FAST_32BIT
#include <MemMap.h>

#if (COM_GLOBAL_TIME == COM_SIZE_32_BIT)
/** \brief Com_GlobalTime (32 bit)
 * time in COM specific ticks */
extern VAR(ComGlobalTimeType, COM_VAR_FAST) Com_GlobalTime;
#endif /* (COM_GLOBAL_TIME == COM_SIZE_32_BIT) */

#define COM_STOP_SEC_VAR_FAST_32BIT
#include <MemMap.h>

/*
 * if not a constant configuration address is used - define pointer variable
 */
#if (COM_CONST_CFG_ADDRESS_ENABLE == STD_OFF)


#define COM_START_SEC_VAR_FAST_UNSPECIFIED
#include <MemMap.h>

/** \brief Com_gConfigPtr
 * global variable for the pointer to the config of Com
 */
extern P2CONST(Com_ConfigType, COM_VAR_FAST, COM_APPL_CONST) Com_gConfigPtr;


#define COM_STOP_SEC_VAR_FAST_UNSPECIFIED
#include <MemMap.h>

#endif /* COM_CONST_CFG_ADDRESS_ENABLE == STD_OFF */


/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/


#define COM_START_SEC_CODE
#include <MemMap.h>


#if (COM_SIGNAL_BYTE_ALIGN == STD_ON)
/** \brief Com_EB_Tx2RxPosinByte - calculates a Rx signal position (in byte)
 * from a Tx signal position (in byte)
 * \param[in] TxBitPosinByte - Position in Bit of Tx representation (in byte)
 * \param[in] BitSize - size of the signal (in byte, for Boolean in bit)
 * \param[in] SignalType - signal type
 * \param[in] endianness - endianness of the signal
 * \retval RxBitPosinByte - Position in Byte of Rx representation
 */
TS_MOD_PRIV_DECL FUNC(ComSignalDescBitType, COM_CODE) Com_EB_Tx2RxPosinByte
(
      ComSignalDescBitType TxBitPosinByte
#if ((COM_ENDIANNESS_CONVERSION == COM_LITTLE_ENDIAN) || \
                     (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE))
   ,ComSignalBitSizeType BitSize
#if (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON)
   ,Com_TS_SignalTypeType SignalType
#endif /* (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON) */
#endif /* ((COM_ENDIANNESS_CONVERSION == COM_LITTLE_ENDIAN) || \
                     (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)) */
#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
   ,Com_TS_SignalEndiannessType endianness
#endif /* (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE) */
);
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_ON) */

#if ((COM_SIGNAL_BYTE_ALIGN == STD_OFF) && (COM_TMS_ENABLE == STD_ON))
#if ((COM_SIGNAL_GW_ENABLE == STD_ON) || (COM_TXF_MASKNEWDIFFERSMASKOLD_EN == STD_ON))
/** \brief Com_EB_Tx2RxPosinBit - calculates a Rx signal position (in bit)
 * from a Tx signal position (in bit)
 * \param[in] TxBitPosinBit - Position in Bit of Tx representation (in bit)
 * \param[in] BitSize - size of the signal (in bit)
 * \param[in] endianness - endianness of the signal
 * \retval RxBitPosinBit - Position in Bit of Rx representation
 */
TS_MOD_PRIV_DECL FUNC(ComSignalDescBitType, COM_CODE) Com_EB_Tx2RxPosinBit
(
   ComSignalDescBitType TxBitPosinBit
   ,ComSignalBitSizeType BitSize
#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
   ,Com_TS_SignalEndiannessType endianness
#endif /* (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE) */
);
#endif /* ((COM_SIGNAL_GW_ENABLE == STD_ON) || (COM_TXF_MASKNEWDIFFERSMASKOLD_EN == STD_ON)) */
#endif /* ((COM_SIGNAL_BYTE_ALIGN == STD_OFF) && (COM_TMS_ENABLE == STD_ON)) */


#if (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON)
TS_MOD_PRIV_DECL FUNC(void, COM_CODE) Com_EB_WriteToPduOrSBuffBool
(
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
);
#endif /* (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON) */

#if ((COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON) || (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON))
TS_MOD_PRIV_DECL FUNC(void, COM_CODE) Com_EB_WriteToPduOrSBuff8Bit
(
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_CHECK_VALUE_SIZE == STD_ON)
   ,boolean un_int
#endif /* (COM_CHECK_VALUE_SIZE == STD_ON) */
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
);
#endif /* ((COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON) || (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON)) */


#if ((COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON) || (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON))
TS_MOD_PRIV_DECL FUNC(void, COM_CODE) Com_EB_WriteToPduOrSBuff16Bit
(
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_CHECK_VALUE_SIZE == STD_ON)
   ,boolean un_int
#endif /* (COM_CHECK_VALUE_SIZE == STD_ON) */
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
);
#endif /* ((COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON) || (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON)) */


#if ((COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON) || (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON))
TS_MOD_PRIV_DECL FUNC(void, COM_CODE) Com_EB_WriteToPduOrSBuff32Bit
(
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_CHECK_VALUE_SIZE == STD_ON)
   ,boolean un_int
#endif /* (COM_CHECK_VALUE_SIZE == STD_ON) */
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
);
#endif /* ((COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON) || (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON)) */

#if (COM_SIGNAL_TYPE_UINT8_N_ENABLE == STD_ON)
/** \brief Com_EB_WriteToPduOrSBuffByteArray - writes a byte array
 * (Uint8_N signal) to a buffer
 * This function writes a byte array to a buffer. If trigger on change is
 * enabled COM_EVALUATE_TRIGGERED_OC == STD_ON the old buffer value and the
 * value of the byte array are compared. If equal the pointer flag is set to
 * true otherwise false.
 * Preconditions:
 * - COM must be initialized
 * \param[in] dataPtr - pointer to the destination
 * \param[in] SignalDataPtr - pointer to the source of the byte array
 * \param[in] size - size in bytes of the byte array
 * \param[in] triggerPtr - pointer to the trigger flag
* \retval None
 */
TS_MOD_PRIV_DECL FUNC(void, COM_CODE) Com_EB_WriteToPduOrSBuffByteArray
(
   P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   ComSignalBitSizeType size
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
);
#endif /* (COM_SIGNAL_TYPE_UINT8_N_ENABLE == STD_ON) */


#if ((COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON) || (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON))

TS_MOD_PRIV_DECL FUNC(uint8, COM_CODE) Com_EB_ReadFromPduOrSBuffUint8
(
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
);

#endif /* ((COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON) || (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON)) */

#if (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON)

TS_MOD_PRIV_DECL FUNC(sint8, COM_CODE) Com_EB_ReadFromPduOrSBuffSint8
(
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
);

#endif /* (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON) */

#if ((COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON) || (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON))

TS_MOD_PRIV_DECL FUNC(uint16, COM_CODE) Com_EB_ReadFromPduOrSBuffUint16
(
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
);

#endif /* ((COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON) || (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON)) */

#if (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON)

TS_MOD_PRIV_DECL FUNC(sint16, COM_CODE) Com_EB_ReadFromPduOrSBuffSint16
(
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
);

#endif /* (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON) */

#if ((COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON) || (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON))

TS_MOD_PRIV_DECL FUNC(uint32, COM_CODE) Com_EB_ReadFromPduOrSBuffUint32
(
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
);

#endif /* ((COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON) || (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON)) */

#if (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON)

TS_MOD_PRIV_DECL FUNC(sint32, COM_CODE) Com_EB_ReadFromPduOrSBuffSint32
(
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
);

#endif /* (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON) */


#if (COM_GENERIC_READ_REQUIRED == STD_ON)
/** \brief Com_EB_ReadFromPduOrShadowBuffer
 * This function unpacks a bit-pattern from an UInt8-array representing an
 * IPDU into an UInt32.
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * - does not handle signal type UINT8_N
 * \param[in] ComReadPropPtr - properties of the signal which shall be read
 * \retval UInt32-packed bit pattern representing the value extracted.
 */

TS_MOD_PRIV_DECL FUNC(uint32, COM_CODE) Com_EB_ReadFromPduOrShadowBuffer
(
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
);
#endif /* (COM_GENERIC_READ_REQUIRED == STD_ON) */


#if ((COM_FILTER_RECEIVER_ENABLE == STD_ON) || \
      ((COM_TMS_ENABLE == STD_ON) && (COM_SIGNAL_GW_ENABLE == STD_ON)))

TS_MOD_PRIV_DECL FUNC(boolean, COM_CODE) Com_EB_CalculateFilter
(
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr,
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr
);

#endif /* ((COM_FILTER_RECEIVER_ENABLE == STD_ON) || \
      ((COM_TMS_ENABLE == STD_ON) && (COM_SIGNAL_GW_ENABLE == STD_ON))) */


/** \brief Com_EB_SetBufferUInt32 - store a value packed as UInt32 inside
 * a buffer set
 * Function which stores a value given as UInt32 in a buffer set
 * Preconditions:
 * - prior to this call, the COM module shall be initialized
 * \param[in] Val - value to be stored (any integer type packed as UInt32)
 * \param[in] SignalType - signal type
 * \param[in] ValueRef - reference to the position where the
 * value is stored. NOTE: If SignalType == COM_BOOLEAN, the position is
 * interpreted as bits, not bytes as with all other data types!
 * \retval None
 */

#if ((COM_RX_SIGNAL_BUFFER_AVAILABLE == STD_ON) || \
      (COM_TX_SIGNAL_BUFFER_AVAILABLE == STD_ON))

TS_MOD_PRIV_DECL FUNC(void, COM_CODE) Com_EB_SetBufferUInt32
(
   uint32 Val,
   Com_TS_SignalTypeType SignalType,
   ComSignalBufferRefType ValueRef
);

#endif /* ((COM_RX_SIGNAL_BUFFER_AVAILABLE == STD_ON) || \
      (COM_TX_SIGNAL_BUFFER_AVAILABLE == STD_ON)) */


#if (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
/** \brief Com_EB_WriteToUpperLayer - pass data to upper layer
 * Function which passes a value given as UInt32-packed data
 * to the upper layer via void pointer.
 * Preconditions:
 * - prior to this call, the COM module shall be initialized
 * - SignalType COM_UINT8_N is not allowed
 * \param[in] value - value which should be written
 * \param[in] SignalDataPtr - void pointer to data location
 * \param[in] SignalType - SignalType of the data
 * \retval None
 */

TS_MOD_PRIV_DECL FUNC(void, COM_CODE) Com_EB_WriteToUpperLayer
(
   uint32 value,
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) DataPtr,
   Com_TS_SignalTypeType SignalType
);
#endif /* (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

#if (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON)
/** \brief Com_ResetFilerOneEveryN - resets the occurance value of a
 * OneEveryN filter
 * Preconditions:
 * - prior to this call, the COM module shall be initialized
 * - ComFilterRef has to address a ComOneEveryN configuration
 * \param[in] ComFilterRef - Filter which shall be reseted
 * \retval None
 */

TS_MOD_PRIV_DECL FUNC(void, COM_CODE) Com_ResetFilerOneEveryN
(
   ComFilterRefType ComFilterRef
);
#endif /* (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON) */

#define COM_STOP_SEC_CODE
#include <MemMap.h>

#endif /* if !defined( COM_PRIV_H ) */
/*==================[end of file]===========================================*/
