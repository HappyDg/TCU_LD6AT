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
 * MISRA-1) Deviated Rule: 16.7 (advisory)
 * A pointer parameter in a function prototype should be declared as pointer to const
 * if the pointer is not used to modify the addressed object.
 *
 * Reason:
 * This violation is a false positive.
 * The tool does not recognize the following situations:
 * a) There is a direct write access to the addressed object, but the pointer is casted
 *    beforehand.
 * b) There is an indirect write access to the addressed object. The pointer was
 *    assigned to a local variable used to write the addressed object. Declaring
 *    the pointer as "pointer to const" would produce a compiler warning for the assignment.
 * c) The pointer is used as parameter of a function expecting a pointer to non-const.
 *
 * MISRA-2) Deviated Rule: 11.3 (advisory)
 * "A cast should not be performed between a pointer type and an integral type."
 *
 * Reason:
 * Actually this is not a cast between a pointer and a integral type, since 0
 * is null pointer constant.
 *
 * MISRA-3) Deviated Rule: 6.3 (advisory)
 * "'typedefs' that indicate size and signedness should be used in place of the basic types."
 *
 * Reason:
 * In this case variables are casted to a natural integral type since, the value is further used
 * for purposes where natural types are most efficient (e.g. indexing).
 *
 */


/*==================[inclusions]============================================*/

#include <Com_Trace.h>
#include <TSAutosar.h>          /* EB specific standard types */
#include <ComStack_Types.h>     /* AUTOSAR Standard types */
#include <Com_Api.h>                /* Module public API */
#include <Com_Lcfg_Static.h>    /* declaration of the callback arrays */
#include <Com_Priv.h>           /* Module private API */

#include <Com_Core_TxIPdu.h>    /* Header TxIPdu functions */
#include <Com_Core_RxIPdu.h>    /* Header RxIPdu functions */


#if ((COM_TM_AVAILABLE == STD_ON) || (COM_TMS_ENABLE == STD_ON))
#include <Com_Core_TM.h> /* Transmission Mode functions */
#endif /* ((COM_TM_AVAILABLE == STD_ON) || (COM_TMS_ENABLE == STD_ON)) */

#if (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)
#include <Com_Core_RxUpdateBit.h> /* UpdateBit Functions */
#endif /* (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) */

#if ((COM_FILTER_RECEIVER_ENABLE == STD_ON) || \
      ((COM_TMS_ENABLE == STD_ON) && (COM_SIGNAL_GW_ENABLE == STD_ON)))
#include <Com_Filter.h>
#endif /* ((COM_FILTER_RECEIVER_ENABLE == STD_ON) || \
      ((COM_TMS_ENABLE == STD_ON) && (COM_SIGNAL_GW_ENABLE == STD_ON))) */

/*==================[version check]=========================================*/

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/** \brief definition of the Com_EB_WriteToPduOrSBuff_UA_Type */
typedef struct
{


#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   /* pointer where the result of trigger on change calculation shall be written */
   P2VAR(boolean, TYPEDEF, AUTOMATIC) triggerPtr;
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */

   ComSignalDescBitType row;
   /**< starting position in Bytes */
   ComSignalBitSizeType size;
   /**< size of the signal in bits */
   uint8 col;
   /**< starting position of the signal in bits relative to row */
   sint8 step;
   /**< -1 if for big endianness, 1 for little endianness signals */

} Com_EB_WriteToPduOrSBuff_UA_Type;


/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*------------------[version constants definition]--------------------------*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/


#define COM_START_SEC_VAR_FAST_8BIT
#include <MemMap.h>

/** \brief Com_InitStatus
 * global variable for the actual initialization status of the Com */
VAR(Com_EB_StatusType, COM_VAR_FAST) Com_InitStatus = COM_EB_UNINIT;


#if (COM_GLOBAL_TIME == COM_SIZE_8_BIT)
/** \brief Com_GlobalTime
 * time in COM specific ticks */
VAR(ComGlobalTimeType, COM_VAR_FAST) Com_GlobalTime;
#endif /* (COM_GLOBAL_TIME == COM_SIZE_8_BIT) */

#define COM_STOP_SEC_VAR_FAST_8BIT
#include <MemMap.h>


#define COM_START_SEC_VAR_FAST_16BIT
#include <MemMap.h>

#if (COM_GLOBAL_TIME == COM_SIZE_16_BIT)
/** \brief Com_GlobalTime
 * time in COM specific ticks */
VAR(ComGlobalTimeType, COM_VAR_FAST) Com_GlobalTime;
#endif /* (COM_GLOBAL_TIME == COM_SIZE_16_BIT) */

#define COM_STOP_SEC_VAR_FAST_16BIT
#include <MemMap.h>


#define COM_START_SEC_VAR_FAST_32BIT
#include <MemMap.h>


#if (COM_GLOBAL_TIME == COM_SIZE_32_BIT)
/** \brief Com_GlobalTime
 * time in COM specific ticks */
VAR(ComGlobalTimeType, COM_VAR_FAST) Com_GlobalTime;
#endif /* (COM_GLOBAL_TIME == COM_SIZE_32_BIT) */

#define COM_STOP_SEC_VAR_FAST_32BIT
#include <MemMap.h>



/*
 * if not a constant configuration address is used - define pointer variable
 */
#if (COM_CONST_CFG_ADDRESS_ENABLE == STD_OFF)


#define COM_START_SEC_VAR_FAST_UNSPECIFIED
#include <MemMap.h>

/**
 * global variable for the pointer to the config of Com
 */
P2CONST(Com_ConfigType, COM_VAR_FAST, COM_APPL_CONST) Com_gConfigPtr;


#define COM_STOP_SEC_VAR_FAST_UNSPECIFIED
#include <MemMap.h>

#endif /* COM_CONST_CFG_ADDRESS_ENABLE == STD_OFF */


/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/


#define COM_START_SEC_CODE
#include <MemMap.h>



#if ((COM_FILTER_RECEIVER_ENABLE == STD_ON) || \
      ((COM_TMS_ENABLE == STD_ON) && (COM_SIGNAL_GW_ENABLE == STD_ON)))


#if (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON)
_COM_STATIC_ FUNC(boolean, COM_CODE) Com_EB_CalculateFilter_Bool
(
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr,
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr
);
#endif /* (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON) */

#if (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON)
_COM_STATIC_ FUNC(boolean, COM_CODE) Com_EB_CalculateFilter_Uint8
(
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr,
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr
);
#endif /* (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON) */

#if (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON)
_COM_STATIC_ FUNC(boolean, COM_CODE) Com_EB_CalculateFilter_Uint16
(
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr,
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr
);
#endif /* (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON) */

#if (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON)
_COM_STATIC_ FUNC(boolean, COM_CODE) Com_EB_CalculateFilter_Uint32
(
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr,
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr
);
#endif /* (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON) */

#if (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON)
_COM_STATIC_ FUNC(boolean, COM_CODE) Com_EB_CalculateFilter_Sint8
(
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr,
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr
);
#endif /* (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON) */

#if (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON)
_COM_STATIC_ FUNC(boolean, COM_CODE) Com_EB_CalculateFilter_Sint16
(
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr,
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr
);
#endif /* (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON) */

#if (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON)
_COM_STATIC_ FUNC(boolean, COM_CODE) Com_EB_CalculateFilter_Sint32
(
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr,
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr
);
#endif /* (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON) */

#endif  /* ((COM_FILTER_RECEIVER_ENABLE == STD_ON) || \
      ((COM_TMS_ENABLE == STD_ON) && (COM_SIGNAL_GW_ENABLE == STD_ON))) */



#if (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
#if ((COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON) || (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON))

_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_WriteToPduOrSBuff16BitUA
(
   P2CONST(Com_EB_WriteToPduOrSBuff_UA_Type, AUTOMATIC, AUTOMATIC) PropPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr,
   uint16 Val
);

#endif /* ((COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON) || (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON)) */

#if ((COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON) || (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON))

_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_WriteToPduOrSBuff8BitUA
(
   P2CONST(Com_EB_WriteToPduOrSBuff_UA_Type, AUTOMATIC, AUTOMATIC) PropPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr,
   uint8 Val
);
#endif /* ((COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON) || (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON)) */
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_OFF) */


#if (COM_CHECK_VALUE_SIZE == STD_ON)

/** \brief Com_EB_CheckValueSizeBoolean - checks if the value fits into the
 * signal and if the size of the signal fits to its type.
 * If not, DET is called.
 * \param[in] Val - value which shall be checked
 * \param[in] size - number of bits reserved for the signal
 * \retval None
 */

_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_CheckValueSizeBoolean
(
   boolean Val,
   ComSignalBitSizeType size
);


/** \brief Com_EB_CheckValueSize8Bit - checks if the value fits into the
 * signal and if the size of the signal fits to its type.
 * If not, DET is called.
 * \param[in] Val - value which shall be checked
 * \param[in] size - number of bits reserved for the signal
 * \retval None
 */

_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_CheckValueSize8Bit
(
   uint8 Val,
   ComSignalBitSizeType size,
   boolean un_int
);


/** \brief Com_EB_CheckValueSize16Bit - checks if the value fits into the
 * signal and if the size of the signal fits to its type.
 * If not, DET is called.
 * \param[in] Val - value which shall be checked
 * \param[in] size - number of bits reserved for the signal
 * \retval None
 */

_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_CheckValueSize16Bit
(
   uint16 Val,
   ComSignalBitSizeType size,
   boolean un_int
);


/** \brief Com_EB_CheckValueSize32Bit - checks if the value fits into the
 * signal and if the size of the signal fits to its type.
 * If not, DET is called.
 * \param[in] Val - value which shall be checked
 * \param[in] size - number of bits reserved for the signal
 * \retval None
 */

_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_CheckValueSize32Bit
(
   uint32 Val,
   ComSignalBitSizeType size,
   boolean un_int
);


/** \brief Com_EB_CheckValueSizeBoolean - checks if the value fits into the
 * signal and if the size of the signal fits to its type.
 * If not, DET is called.
 * \param[in] Val - value which shall be checked
 * \param[in] size - number of bits reserved for the signal
 * \retval None
 */

_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_CheckValueSizeBoolean
(
   boolean Val,
   ComSignalBitSizeType size
)
{
   uint8 numval = (uint8) Val;

   DBG_COM_EB_CHECKVALUESIZEBOOLEAN_ENTRY(Val,size);

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
   COM_PRECONDITION_ASSERT((size == 1U), COM_INTERNAL_API_ID);
#else /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */
   TS_PARAM_UNUSED(size);
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */

   if (numval > 1U)
   {
      COM_DET_REPORTERROR(COM_E_SIGNAL_TOO_WIDE, COM_INTERNAL_API_ID);
   }

   DBG_COM_EB_CHECKVALUESIZEBOOLEAN_EXIT(Val,size);
}                               /* Com_EB_CheckValueSizeBoolean */


/** \brief Com_EB_CheckValueSize8Bit - checks if the value fits into the
 * signal and if the size of the signal fits to its type.
 * If not, DET is called.
 * \param[in] Val - value which shall be checked
 * \param[in] size - number of bits reserved for the signal
 * \retval None
 */

_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_CheckValueSize8Bit
(
   uint8 Val,
   ComSignalBitSizeType size,
   boolean un_int
)
{



   DBG_COM_EB_CHECKVALUESIZE8BIT_ENTRY(Val,size,un_int);
   COM_PRECONDITION_ASSERT((size <= 8U), COM_INTERNAL_API_ID);

   /* Only do this check if the size isn't 8, as in that case
    * - shifting doesn't work (undefined behavior)
    * - there are no more significant bits left to test */
   if (size < 8U)
   {
      if (un_int == TRUE)            /* unsigned */
      {
         /* Unsigned; there shall be no more significant bits set unlike the
          * most significant which gets into the Pdu. */

         if ((uint8) (Val >> size) != 0U)
         {
            COM_DET_REPORTERROR(COM_E_SIGNAL_TOO_WIDE, COM_INTERNAL_API_ID);
         }
      }
      else                   /* unsigned / signed */
      {
         /* Signed; all more significant bits in value shall be equal to the
          * most significant bit that will make it into the Pdu */

         /* Make a copy of value */
         uint8 valcopy = Val;

         /* Get the most significant bit of the value which will make
          * it into the PDU */
         uint8 MSB = (uint8)((uint8)(1U << (size - 1U)) & Val);

         /* Prepare for the check */
         if (MSB != 0U)
         {
            /* The MSB in the NWSig is 1 */
            /* Fill all lower bits, that is, all other bits which are in the
             * NWSig, too, with 1, too */
            valcopy |= (uint8) ((uint8) (~0U) >> (8U - size));
         }
         else
         {
            /* The MSB in the NWSig is 0 */
            /* Fill all lower bits, that is, all other bits which are in the
             * NWSig, too, with 0, too */
            valcopy = (uint8)(valcopy & ((uint8)(0xFFU << size)));
         }

         /* Do magic.
          * If the "MSB" is 1, the number resulting from un-packing the
          * network signal on the receiver side is negative.
          * If the number fits into the network signal, all more significant
          * bits must also be 1. As we made the less significant bits 1,
          * too, the inverted valcopy must be 0.
          * If the "MSB" is 0, the number resulting from un-packing the
          * network signal on the receiver side is positive.
          * If the number fits into the network signal, all more significant
          * bits must also be 0. As we made the less significant bits 0,
          * too, valcopy must be zero. */

         {
            /* calculate the complement of Valcopy */
            uint8 const compValcopy = (uint8)(~valcopy);

            if (((MSB != 0U) && (compValcopy != 0U)) || ((MSB == 0U) && (valcopy != 0U)))
            {
               COM_DET_REPORTERROR(COM_E_SIGNAL_TOO_WIDE, COM_INTERNAL_API_ID);
            }
         }

      }                      /* end if (signed) */
   }

   DBG_COM_EB_CHECKVALUESIZE8BIT_EXIT(Val,size,un_int);
}                               /* Com_EB_CheckValueSize8Bit */


/** \brief Com_EB_CheckValueSize16Bit - checks if the value fits into the
 * signal and if the size of the signal fits to its type.
 * If not, DET is called.
 * \param[in] Val - value which shall be checked
 * \param[in] size - number of bits reserved for the signal
 * \retval None
 */

_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_CheckValueSize16Bit
(
   uint16 Val,
   ComSignalBitSizeType size,
   boolean un_int
)
{




   DBG_COM_EB_CHECKVALUESIZE16BIT_ENTRY(Val,size,un_int);
   COM_PRECONDITION_ASSERT((size <= 16U), COM_INTERNAL_API_ID);

   /* Only do this check if the size isn't 16, as in that case
    * - shifting doesn't work (undefined behavior)
    * - there are no more significant bits left to test */
   if (size < 16U)
   {
      if (un_int == TRUE)            /* unsigned */
      {
         /* Unsigned; there shall be no more significant bits set unlike the
          * most significant which gets into the Pdu. */

         if ((uint16) (Val >> size) != 0U)
         {
            COM_DET_REPORTERROR(COM_E_SIGNAL_TOO_WIDE, COM_INTERNAL_API_ID);
         }
      }
      else                   /* unsigned / signed */
      {
         /* Signed; all more significant bits in value shall be equal to the
          * most significant bit that will make it into the Pdu */

         /* Make a copy of value */
         uint16 valcopy = Val;

         /* Get the most significant bit of the value which will make
          * it into the PDU */
         uint16 MSB = (uint16)(((uint16)((uint16)1U << (size - 1U))) & Val);

         /* Prepare for the check */
         if (MSB != 0U)
         {
            /* The MSB in the NWSig is 1 */
            /* Fill all lower bits, that is, all other bits which are in the
             * NWSig, too, with 1, too */
            valcopy |= (uint16) ( (uint16)(~((uint16)0U)) >> (16U - size));
         }
         else
         {
            /* The MSB in the NWSig is 0 */
            /* Fill all lower bits, that is, all other bits which are in the
             * NWSig, too, with 0, too */
            valcopy = (uint16)(valcopy & ((uint16)(0xFFFFU << size)));
         }

         /* Do magic.
          * If the "MSB" is 1, the number resulting from un-packing the
          * network signal on the receiver side is negative.
          * If the number fits into the network signal, all more significant
          * bits must also be 1. As we made the less significant bits 1,
          * too, the inverted valcopy must be 0.
          * If the "MSB" is 0, the number resulting from un-packing the
          * network signal on the receiver side is positive.
          * If the number fits into the network signal, all more significant
          * bits must also be 0. As we made the less significant bits 0,
          * too, valcopy must be zero. */

         {
            /* calculate the complement of Valcopy */
            uint16 const compValcopy = (uint16)(~valcopy);

            if (((MSB != 0U) && (compValcopy != 0U)) || ((MSB == 0U) && (valcopy != 0U)))
            {
               COM_DET_REPORTERROR(COM_E_SIGNAL_TOO_WIDE, COM_INTERNAL_API_ID);
            }
         }

      }                      /* end if (signed) */
   }

   DBG_COM_EB_CHECKVALUESIZE16BIT_EXIT(Val,size,un_int);
}                               /* Com_EB_CheckValueSize16Bit */


/** \brief Com_EB_CheckValueSize32Bit - checks if the value fits into the
 * signal and if the size of the signal fits to its type.
 * If not, DET is called.
 * \param[in] Val - value which shall be checked
 * \param[in] size - number of bits reserved for the signal
 * \retval None
 */

_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_CheckValueSize32Bit
(
   uint32 Val,
   ComSignalBitSizeType size,
   boolean un_int
)
{




DBG_COM_EB_CHECKVALUESIZE32BIT_ENTRY(Val,size,un_int);
   COM_PRECONDITION_ASSERT((size <= 32U), COM_INTERNAL_API_ID);

   /* Only do this check if the size isn't 32, as in that case
    * - shifting doesn't work (undefined behavior)
    * - there are no more significant bits left to test */
   if (size < 32U)
   {
      if (un_int == TRUE)            /* unsigned */
      {
         /* Unsigned; there shall be no more significant bits set unlike the
          * most significant which gets into the Pdu. */

         if ((uint32) (Val >> size) != 0UL)
         {
            COM_DET_REPORTERROR(COM_E_SIGNAL_TOO_WIDE, COM_INTERNAL_API_ID);
         }
      }
      else                   /* unsigned / signed */
      {
         /* Signed; all more significant bits in value shall be equal to the
          * most significant bit that will make it into the Pdu */

         /* Make a copy of value */
         uint32 valcopy = Val;

         /* Get the most significant bit of the value which will make
          * it into the PDU */
         uint32 MSB = (uint32)((1UL << (size - 1U)) & Val);

         /* Prepare for the check */
         if (MSB != 0U)
         {
            /* The MSB in the NWSig is 1 */
            /* Fill all lower bits, that is, all other bits which are in the
             * NWSig, too, with 1, too */
            valcopy |= (uint32) ((uint32) (~0UL) >> (32U - size));
         }
         else
         {
            /* The MSB in the NWSig is 0 */
            /* Fill all lower bits, that is, all other bits which are in the
             * NWSig, too, with 0, too */
            valcopy &= (uint32)((~0UL) << (size));
         }

         /* Do magic.
          * If the "MSB" is 1, the number resulting from un-packing the
          * network signal on the receiver side is negative.
          * If the number fits into the network signal, all more significant
          * bits must also be 1. As we made the less significant bits 1,
          * too, the inverted valcopy must be 0.
          * If the "MSB" is 0, the number resulting from un-packing the
          * network signal on the receiver side is positive.
          * If the number fits into the network signal, all more significant
          * bits must also be 0. As we made the less significant bits 0,
          * too, valcopy must be zero. */

         {
            /* calculate the complement of Valcopy */
            uint32 const compValcopy = (uint32)(~valcopy);

            if (((MSB != 0U) && (compValcopy != 0U)) || ((MSB == 0U) && (valcopy != 0U)))
            {
               COM_DET_REPORTERROR(COM_E_SIGNAL_TOO_WIDE, COM_INTERNAL_API_ID);
            }
         }

      }                      /* end if (signed) */
   }                         /* end if (size < 32U) */

   DBG_COM_EB_CHECKVALUESIZE32BIT_EXIT(Val,size,un_int);
}                               /* Com_EB_CheckValueSize32Bit */

#endif /* (COM_CHECK_VALUE_SIZE == STD_ON) */


#if (COM_SIGNAL_BYTE_ALIGN == STD_ON)
/** \brief Com_EB_Tx2RxPosinByte - calculates a Rx signal position (in byte)
 * from a Tx signal position (in byte)
 * \param[in] TxBitPosinByte - Position in Bit of Tx representation (in byte)
 * \param[in] BitSize - size of the signal (in byte, for Boolean in bit)
 * \param[in] SignalType - signal type
 * \param[in] endianness - endianness of the signal
 * \retval RxBitPosinByte - Position in Byte of Rx representation
 */
TS_MOD_PRIV_DEFN FUNC(ComSignalDescBitType, COM_CODE) Com_EB_Tx2RxPosinByte
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
)
{
   ComSignalDescBitType ComSignalPositionInByte;

   DBG_COM_EB_TX2RXPOSINBYTE_ENTRY(TxBitPosinByte);

#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
   if (endianness == COM_BIG_ENDIAN)
#endif /* (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE) */

#if ((COM_ENDIANNESS_CONVERSION == COM_BIG_ENDIAN) || \
                     (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE))
   {
      /* COM_BIG_ENDIAN: */
#if (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON)
      if (SignalType == COM_BOOLEAN)
      {
         /* the position of Boolean signal is given in bits and do not have
          * to be recalculated */
         ComSignalPositionInByte = TxBitPosinByte;
      }
      else
#endif /* (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON) */
      {
         uint8 pos = (BitSize / 8U) - 1U;
         /* the position of other signals have to be recalculated */
         ComSignalPositionInByte = (TxBitPosinByte - (ComSignalDescBitType) pos);
      }
   }
#endif /* ((COM_ENDIANNESS_CONVERSION == COM_BIG_ENDIAN) || \
                     (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)) */

#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
   else
#endif /* (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE) */

#if ((COM_ENDIANNESS_CONVERSION == COM_LITTLE_ENDIAN) || \
                     (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE))
   {

      /* COM_LITTLE_ENDIAN */
#if (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON)
      if (SignalType == COM_BOOLEAN)
      {
         /* the position of Boolean signal is given in bits and do not have
          * to be recalculated */
         ComSignalPositionInByte = TxBitPosinByte;
      }
      else
#endif /* (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON) */
      {
         uint8 pos = (BitSize / 8U) - 1U;
         /* the position of other signals have to be recalculated */
         ComSignalPositionInByte = (TxBitPosinByte + (ComSignalDescBitType) pos);
      }

   }
#endif /* ((COM_ENDIANNESS_CONVERSION == COM_LITTLE_ENDIAN) || \
                     (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)) */


   DBG_COM_EB_TX2RXPOSINBYTE_EXIT(ComSignalPositionInByte,TxBitPosinByte);

   return ComSignalPositionInByte;
}
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
TS_MOD_PRIV_DEFN FUNC(ComSignalDescBitType, COM_CODE) Com_EB_Tx2RxPosinBit
(
   ComSignalDescBitType TxBitPosinBit
   ,ComSignalBitSizeType BitSize
#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
   ,Com_TS_SignalEndiannessType endianness
#endif /* (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE) */
)
{
   ComSignalDescBitType ComSignalPositionInBit;

   DBG_COM_EB_TX2RXPOSINBIT_ENTRY(TxBitPosinBit,BitSize);

#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
   if (endianness == COM_BIG_ENDIAN)
#endif /* (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE) */

#if ((COM_ENDIANNESS_CONVERSION == COM_BIG_ENDIAN) || \
      (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE))
   {
      /* Recalculate Position for BIG_ENDIAN */

      uint16 BaseRow;
      uint16 RBase;
      uint16 MSBRPos;
      uint16 RowSkips;

      BaseRow = TxBitPosinBit / 8U;
      RBase = BaseRow * 8U;
      MSBRPos = (TxBitPosinBit - RBase) + ((uint16) BitSize - 1U);
      RowSkips = MSBRPos / 8U;

      ComSignalPositionInBit = (ComSignalDescBitType)((RBase + (MSBRPos % 8U)) - (8U * RowSkips));
   }

#endif /* ((COM_ENDIANNESS_CONVERSION == COM_BIG_ENDIAN) || \
      (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)) */
#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
   else
#endif /* (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE) */

#if ((COM_ENDIANNESS_CONVERSION == COM_LITTLE_ENDIAN) || \
      (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE))

   {
      /* Recalculate Position for LITTLE_ENDIAN */
       ComSignalPositionInBit = (ComSignalDescBitType)((TxBitPosinBit + (uint16)BitSize) - 1U);
   }
#endif /* ((COM_ENDIANNESS_CONVERSION == COM_LITTLE_ENDIAN) || \
      (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)) */


   DBG_COM_EB_TX2RXPOSINBIT_EXIT(ComSignalPositionInBit,TxBitPosinBit,BitSize);

   return ComSignalPositionInBit;

}                               /* Com_EB_Tx2RxPosinBit */

#endif /* ((COM_SIGNAL_GW_ENABLE == STD_ON) || (COM_TXF_MASKNEWDIFFERSMASKOLD_EN == STD_ON)) */
#endif /* ((COM_SIGNAL_BYTE_ALIGN == STD_OFF) && (COM_TMS_ENABLE == STD_ON)) */



#if (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON)
TS_MOD_PRIV_DEFN FUNC(void, COM_CODE) Com_EB_WriteToPduOrSBuffBool
(
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
)
{

   ComSignalDescBitType const ComSignalPosition =
#if (COM_SIGNAL_BYTE_ALIGN == STD_ON)
         ComWritePropPtr->ComSignalPositionInByte;
#elif (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
   ComWritePropPtr->ComSignalPositionInBit;
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_ON) */

   DBG_COM_EB_WRITETOPDUORSBUFFBOOL_ENTRY(SignalDataPtr,ComWritePropPtr);

#if (COM_TX_ZERO_SIGNAL_ENABLE == STD_ON)
   if (0 != ComWritePropPtr->size)
#endif /* (COM_TX_ZERO_SIGNAL_ENABLE == STD_ON) */
   {

      boolean Val = (boolean) * (P2CONST(boolean, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;

#if (COM_CHECK_VALUE_SIZE == STD_ON)
      Com_EB_CheckValueSizeBoolean(Val, ComWritePropPtr->size);
#endif /* (COM_CHECK_VALUE_SIZE == STD_ON) */

      Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

#if (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)
#if (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL)
      if (ComWritePropPtr->updateBit == TRUE)
#endif /* (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL) */
      {

         Com_SetBitUInt8(&ComWritePropPtr->dataPtr[ComWritePropPtr->ComUpdateBitPositionInBit / 8U],
               (ComWritePropPtr->ComUpdateBitPositionInBit % 8U));

      }
#endif /* (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) */

#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
      {
         uint8 oldval;
         TS_GetBit(&ComWritePropPtr->dataPtr[ComSignalPosition / 8U],
            ComSignalPosition % 8U, uint8, oldval);
         COM_TRIGGERED_OC_VALUE_CHANGED(oldval, Val, *triggerPtr);
      }
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */

      if (Val == FALSE)
      {
         Com_ClearBitUInt8(&ComWritePropPtr->dataPtr[ComSignalPosition / 8U],
               (ComSignalPosition % 8U));

      }
      else
      {
         Com_SetBitUInt8(&ComWritePropPtr->dataPtr[ComSignalPosition / 8U],
               (ComSignalPosition % 8U));
      }

      Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();

   }                            /* if (0 != size) */


   DBG_COM_EB_WRITETOPDUORSBUFFBOOL_EXIT(SignalDataPtr,ComWritePropPtr);
   return;
}                     /* Com_EB_WriteToPduOrSBuffBool */
#endif /* (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON) */


#if ((COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON) || (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON))

#if (COM_SIGNAL_BYTE_ALIGN == STD_OFF)

_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_WriteToPduOrSBuff8BitUA
(
   P2CONST(Com_EB_WriteToPduOrSBuff_UA_Type, AUTOMATIC, AUTOMATIC) PropPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr,
   uint8 Val
)
{
   /* Signal position in bit has a maximum value of 2031. */
   sint16 pos = (sint16) PropPtr->row;

#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   boolean valueChanged = FALSE;
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */

   DBG_COM_EB_WRITETOPDUORSBUFF8BITUA_ENTRY(PropPtr,ComWritePropPtr,Val);

   /* If the least significant bits are not byte-aligned */
   /* check if value fits into the first byte anyway */
   if ((PropPtr->col + PropPtr->size) > 8U)
   {
      /* value has to be stored in two bytes */
      uint16 mask = 0xFFFFU;
      uint16 calval;
      /* get a mask with the number of bits */
      mask = (uint16) (mask >> (16U - PropPtr->size));
      /* shift mask to the right position */
      mask = (uint16) (mask << PropPtr->col);
      /* shift the value to the right position */
      calval = (uint16)(((uint16)Val) << PropPtr->col);
      /* just in case the value would be to big for the space reserved in the I-Pdu */
      calval = (uint16)(calval & mask);

      Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

#if (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)
#if (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL)
      if (ComWritePropPtr->updateBit == TRUE)
#endif /* (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL) */
      {

         Com_SetBitUInt8(&ComWritePropPtr->dataPtr[ComWritePropPtr->ComUpdateBitPositionInBit / 8U],
               (ComWritePropPtr->ComUpdateBitPositionInBit % 8U));

      }
#endif /* (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) */

      {
         /* copy the LSB */
         COM_TRIGGERED_OC_WRITE_BYTE_TO_PDU(
               ComWritePropPtr->dataPtr[pos],
               (uint8)((uint8) (ComWritePropPtr->dataPtr[pos] & (uint8)((uint16) (~mask))) |
                     ((uint8) (calval & 0xFFU))),
               valueChanged);

         calval = calval >> 8U;
         mask = mask >> 8U;
         pos = COM_SIGNAL_DESC_CAST(pos + (sint16)PropPtr->step);

         /* copy the second byte */
         COM_TRIGGERED_OC_WRITE_BYTE_TO_PDU(
            ComWritePropPtr->dataPtr[pos],
               (uint8)((uint8) (ComWritePropPtr->dataPtr[pos] & (uint8)((uint16) (~mask))) |
                     ((uint8) (calval & 0xFFU))),
               valueChanged);
      }

      Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();

   }
   else
   {
      /* value fits into one byte */
      uint8 mask = 0xFFU;
      uint8 calval;
      /* get a mask with the number of bits */
      mask = (uint8) (mask >> (8U - PropPtr->size));
      /* shift mask to the right position */
      mask = (uint8) (mask << PropPtr->col);
      /* shift the value to the right position */
      calval = (uint8)(Val << PropPtr->col);
      /* just in case the value would be to big for the space reserved in the I-Pdu */
      calval = (uint8)(calval & mask);

      Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

#if (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)
#if (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL)
      if (ComWritePropPtr->updateBit == TRUE)
#endif /* (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL) */
      {

         Com_SetBitUInt8(&ComWritePropPtr->dataPtr[ComWritePropPtr->ComUpdateBitPositionInBit / 8U],
               (ComWritePropPtr->ComUpdateBitPositionInBit % 8U));

      }
#endif /* (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) */

      {
         /* copy the LSB */
         COM_TRIGGERED_OC_WRITE_BYTE_TO_PDU(
               ComWritePropPtr->dataPtr[pos],
               (uint8)((uint8) (ComWritePropPtr->dataPtr[pos] & (uint8) (~mask)) | calval),
               valueChanged);
      }

      Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();

   }

#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   *PropPtr->triggerPtr = valueChanged;
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */


   DBG_COM_EB_WRITETOPDUORSBUFF8BITUA_EXIT(PropPtr,ComWritePropPtr,Val);
   return;
}                               /* Com_EB_WriteToPduOrSBuff8BitUA */
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_OFF) */


TS_MOD_PRIV_DEFN FUNC(void, COM_CODE) Com_EB_WriteToPduOrSBuff8Bit
(
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_CHECK_VALUE_SIZE == STD_ON)
   ,boolean un_int
#endif /* (COM_CHECK_VALUE_SIZE == STD_ON) */
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
)
{

#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   boolean valueChanged = FALSE;
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */

   DBG_COM_EB_WRITETOPDUORSBUFF8BIT_ENTRY(SignalDataPtr,ComWritePropPtr);

#if (COM_TX_ZERO_SIGNAL_ENABLE == STD_ON)
   if (0 != ComWritePropPtr->size)
#endif /* (COM_TX_ZERO_SIGNAL_ENABLE == STD_ON) */
   {

      uint8 Val = (uint8) * (P2CONST(uint8, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;

#if (COM_SIGNAL_BYTE_ALIGN == STD_ON)

      /* Starting position of the signals in bytes */
      ComSignalDescBitType row = ComWritePropPtr->ComSignalPositionInByte;
#elif (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
      /* Starting position of the signals in bits divided by 8 => starting position in byte */
      ComSignalDescBitType row = (ComWritePropPtr->ComSignalPositionInBit / 8U);
      uint8 col = (uint8)ComWritePropPtr->ComSignalPositionInBit % 8U;

#if (COM_ENDIANNESS_CONVERSION == COM_BIG_ENDIAN)
      sint8 step = -1;
#elif (COM_ENDIANNESS_CONVERSION == COM_LITTLE_ENDIAN)
      sint8 step = 1;
#elif (COM_ENDIANNESS_CONVERSION == COM_OPAQUE)
      sint8 step = 1;
#elif (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
      sint8 step;
      if (ComWritePropPtr->endianness == COM_BIG_ENDIAN)
      {
         step = -1;
      }
      else
      {
         step = 1;
      }
#elif (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_DISABLE)
      sint8 step = 1;
#endif /* (COM_ENDIANNESS_CONVERSION == COM_BIG_ENDIAN) */
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_ON) */


#if (COM_CHECK_VALUE_SIZE == STD_ON)
      Com_EB_CheckValueSize8Bit(Val, ComWritePropPtr->size, un_int);
#endif /* (COM_CHECK_VALUE_SIZE == STD_ON) */


#if (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
      if (col != 0)
      {
         Com_EB_WriteToPduOrSBuff_UA_Type Prop;

#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
         Prop.triggerPtr = &valueChanged;
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */

         Prop.row = row;
         Prop.size = ComWritePropPtr->size;
         Prop.col = col;
         Prop.step = step;

         Com_EB_WriteToPduOrSBuff8BitUA(&Prop,ComWritePropPtr,Val);
      }
      else
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_OFF) */
      {
         /* the least significant bits are byte-aligned */
         /* value fits into one byte */
         uint8 mask = 0xFFU;
         uint8 calval = Val;
         /* get a mask with the number of bits */
         mask = (uint8) (mask >> (8U - ComWritePropPtr->size));
         /* just in case the value would be to big for the space reserved in the I-Pdu */
         calval = (uint8)(calval & mask);

         Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

#if (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)
#if (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL)
         if (ComWritePropPtr->updateBit == TRUE)
#endif /* (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL) */
         {

            Com_SetBitUInt8(&ComWritePropPtr->dataPtr[ComWritePropPtr->ComUpdateBitPositionInBit / 8U],
                  (ComWritePropPtr->ComUpdateBitPositionInBit % 8U));

         }
#endif /* (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) */

         {
            /* copy the LSB */
            COM_TRIGGERED_OC_WRITE_BYTE_TO_PDU(
                  ComWritePropPtr->dataPtr[row],
                  (uint8)((uint8) (ComWritePropPtr->dataPtr[row] & (uint8) (~mask)) | calval ),
                  valueChanged);
         }

         Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();
      }

   }                            /* if (0 != size) */

#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   *triggerPtr = valueChanged;
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */


   DBG_COM_EB_WRITETOPDUORSBUFF8BIT_EXIT(SignalDataPtr,ComWritePropPtr);
   return;
}                               /* Com_EB_WriteToPduOrSBuff8Bit */
#endif /* ((COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON) || (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON)) */



#if ((COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON) || (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON))

#if (COM_SIGNAL_BYTE_ALIGN == STD_OFF)

_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_WriteToPduOrSBuff16BitUA
(
   P2CONST(Com_EB_WriteToPduOrSBuff_UA_Type, AUTOMATIC, AUTOMATIC) PropPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr,
   uint16 Val
)
{
   /* Signal position in bit has a maximum value of 2031. */
   sint16 pos = (sint16) PropPtr->row;

#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   boolean valueChanged = FALSE;
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
   DBG_COM_EB_WRITETOPDUORSBUFF16BITUA_ENTRY(PropPtr,ComWritePropPtr,Val);

   /* If the least significant bits are not byte-aligned */
   /* check if value fits into the first two bytes anyway */
   if ((PropPtr->col + PropPtr->size) > 16U)
   {
      /* value has to be stored in three bytes */
      uint32 mask = (uint32)UINT32_C(0xFFFFFFFF);
      uint32 calval;
      /* get a mask with the number of bits */
      mask = (uint32) (mask >> (32U - PropPtr->size));
      /* shift mask to the right position */
      mask = (uint32) (mask << PropPtr->col);
      /* shift the value to the right position */
      calval = (uint32)(((uint32)Val) << PropPtr->col);
      /* just in case the value would be to big for the space reserved in the I-Pdu */
      calval = (uint32)(calval & mask);

      Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

#if (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)
#if (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL)
      if (ComWritePropPtr->updateBit == TRUE)
#endif /* (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL) */
      {

         Com_SetBitUInt8(&ComWritePropPtr->dataPtr[ComWritePropPtr->ComUpdateBitPositionInBit / 8U],
               (ComWritePropPtr->ComUpdateBitPositionInBit % 8U));

      }
#endif /* (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) */

      {
         /* 3 bytes have to be copied */
         uint8 i;
         for (i = 0; i < 3U; i++)
         {
            COM_TRIGGERED_OC_WRITE_BYTE_TO_PDU(
                  ComWritePropPtr->dataPtr[pos],
                  (uint8)((uint8) (ComWritePropPtr->dataPtr[pos] & (uint8) (~mask)) |
                        ((uint8) (calval & 0xFFU))),
                  valueChanged);
            calval = calval >> 8U;
            mask = mask >> 8U;
            pos = COM_SIGNAL_DESC_CAST(pos + (sint16)PropPtr->step);
         }                   /* for (i = 0; i < 3U; i++) */

      }

      Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();

   }
   else
   {
      /* value fits into two byte or less */
      uint16 mask = 0xFFFFU;
      uint16 calval;
      /* get a mask with the number of bits */
      mask = (uint16) (mask >> (16U - PropPtr->size));
      /* shift mask to the right position */
      mask = (uint16) (mask << PropPtr->col);
      /* shift the value to the right position */
      calval = (uint16)(Val << PropPtr->col);
      /* just in case the value would be to big for the space reserved in the I-Pdu */
      calval = (uint16)(calval & mask);

      Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

#if (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)
#if (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL)
      if (ComWritePropPtr->updateBit == TRUE)
#endif /* (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL) */
      {

         Com_SetBitUInt8(&ComWritePropPtr->dataPtr[ComWritePropPtr->ComUpdateBitPositionInBit / 8U],
               (ComWritePropPtr->ComUpdateBitPositionInBit % 8U));

      }
#endif /* (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) */

      {
         /* copy the LSB */
         COM_TRIGGERED_OC_WRITE_BYTE_TO_PDU(
               ComWritePropPtr->dataPtr[pos],
               (uint8)((uint8) (ComWritePropPtr->dataPtr[pos] & (uint8) ((uint16)(~mask))) |
                     ((uint8) (calval & 0xFFU))),
               valueChanged);

         mask = mask >> 8U;
         if (mask > 0U)
         {
            calval = calval >> 8U;
            pos = COM_SIGNAL_DESC_CAST(pos + (sint16)PropPtr->step);
            /* copy the MSB */
            COM_TRIGGERED_OC_WRITE_BYTE_TO_PDU(
               ComWritePropPtr->dataPtr[pos],
                  (uint8)((uint8) (ComWritePropPtr->dataPtr[pos] & (uint8) ((uint16)(~mask))) |
                        ((uint8) (calval & 0xFFU))),
                  valueChanged);
         }
      }

      Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();

   }

#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   *PropPtr->triggerPtr = valueChanged;
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */


   DBG_COM_EB_WRITETOPDUORSBUFF16BITUA_EXIT(PropPtr,ComWritePropPtr,Val);
   return;
}                               /* Com_EB_WriteToPduOrSBuff16BitUA */
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_OFF) */


TS_MOD_PRIV_DEFN FUNC (void, COM_CODE) Com_EB_WriteToPduOrSBuff16Bit
(
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_CHECK_VALUE_SIZE == STD_ON)
   ,boolean un_int
#endif /* (COM_CHECK_VALUE_SIZE == STD_ON) */
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
)
{
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   boolean valueChanged = FALSE;
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */

   DBG_COM_EB_WRITETOPDUORSBUFF16BIT_ENTRY(SignalDataPtr,ComWritePropPtr);

#if (COM_TX_ZERO_SIGNAL_ENABLE == STD_ON)
   if (0 != ComWritePropPtr->size)
#endif /* (COM_TX_ZERO_SIGNAL_ENABLE == STD_ON) */
   {
      uint16 Val =
            (uint16) * (P2CONST(uint16, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;

#if (COM_SIGNAL_BYTE_ALIGN == STD_ON)

      /* Starting position of the signals in bytes */
      ComSignalDescBitType row = ComWritePropPtr->ComSignalPositionInByte;
#elif (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
      /* Starting position of the signals in bits divided by 8 => starting position in byte */
      ComSignalDescBitType row = (ComWritePropPtr->ComSignalPositionInBit / 8U);
      uint8 col = (uint8)ComWritePropPtr->ComSignalPositionInBit % 8U;
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_ON) */



#if (COM_ENDIANNESS_CONVERSION == COM_BIG_ENDIAN)
      sint8 step = -1;
#elif (COM_ENDIANNESS_CONVERSION == COM_LITTLE_ENDIAN)
      sint8 step = 1;
#elif (COM_ENDIANNESS_CONVERSION == COM_OPAQUE)
      sint8 step = 1;
#elif (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
      sint8 step;
      if (ComWritePropPtr->endianness == COM_BIG_ENDIAN)
      {
         step = -1;
      }
      else
      {
         step = 1;
      }
#elif (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_DISABLE)
      sint8 step = 1;
#endif


#if (COM_CHECK_VALUE_SIZE == STD_ON)
      Com_EB_CheckValueSize16Bit(Val, ComWritePropPtr->size, un_int);
#endif /* (COM_CHECK_VALUE_SIZE == STD_ON) */


#if (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
      if (col != 0)
      {

         Com_EB_WriteToPduOrSBuff_UA_Type Prop;

#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
         Prop.triggerPtr = &valueChanged;
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */

         Prop.row = row;
         Prop.size = ComWritePropPtr->size;
         Prop.col = col;
         Prop.step = step;

         Com_EB_WriteToPduOrSBuff16BitUA(&Prop,ComWritePropPtr,Val);
      }
      else
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_OFF) */
      {
         /* the least significant bits are byte-aligned */
         /* value fits into two bytes */
         uint16 mask = 0xFFFFU;
         uint16 calval = Val;
         /* Signal position in bit has a maximum value of 2031. */
         sint16 pos = (sint16) row;
         /* get a mask with the number of bits */
         mask = (uint16) (mask >> (16U - ComWritePropPtr->size));
         /* just in case the value would be to big for the space reserved in the I-Pdu */
         calval = (uint16)(calval & mask);

         Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

#if (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)
#if (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL)
         if (ComWritePropPtr->updateBit == TRUE)
#endif /* (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL) */
         {

            Com_SetBitUInt8(&
                  ComWritePropPtr->dataPtr[ComWritePropPtr->ComUpdateBitPositionInBit / 8U],
                  (ComWritePropPtr->ComUpdateBitPositionInBit % 8U));

         }
#endif /* (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) */

         {
            COM_TRIGGERED_OC_WRITE_BYTE_TO_PDU(
                  ComWritePropPtr->dataPtr[pos],
                  (uint8)((uint8) (ComWritePropPtr->dataPtr[pos] & (uint8) ((uint16)(~mask))) |
                        ((uint8) (calval & 0xFFU))),
                        valueChanged);

            mask = mask >> 8U;
            if (mask > 0U)
            {
               calval = calval >> 8U;
               pos = COM_SIGNAL_DESC_CAST(pos + (sint16)step);
               /* copy the MSB */
               COM_TRIGGERED_OC_WRITE_BYTE_TO_PDU(
                  ComWritePropPtr->dataPtr[pos],
                  (uint8)((uint8) (ComWritePropPtr->dataPtr[pos] & (uint8) ((uint16)(~mask))) |
                        ((uint8) (calval & 0xFFU))),
                        valueChanged);
            }
         }

         Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();
      }

   }                            /* if (0 != size) */

#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   *triggerPtr = valueChanged;
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */


   DBG_COM_EB_WRITETOPDUORSBUFF16BIT_EXIT(SignalDataPtr,ComWritePropPtr);
   return;
}                               /* Com_EB_WriteToPduOrSBuff16Bit */
#endif /* ((COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON) || (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON)) */


#if ((COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON) || (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON))
TS_MOD_PRIV_DEFN FUNC(void, COM_CODE) Com_EB_WriteToPduOrSBuff32Bit
(
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_CHECK_VALUE_SIZE == STD_ON)
   ,boolean un_int
#endif /* (COM_CHECK_VALUE_SIZE == STD_ON) */
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
)
{

#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   boolean valueChanged = FALSE;
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */

   DBG_COM_EB_WRITETOPDUORSBUFF32BIT_ENTRY(SignalDataPtr,ComWritePropPtr);

#if (COM_TX_ZERO_SIGNAL_ENABLE == STD_ON)
   if (0 != ComWritePropPtr->size)
#endif /* (COM_TX_ZERO_SIGNAL_ENABLE == STD_ON) */
   {

      uint32 Val = (uint32) * (P2CONST(uint32, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;

      uint8 putvalue = (uint8) Val;
      uint32 mask = (uint32) 0xFFFFFFFFUL;
      uint8 space = 8U;
      sint8 ssize;

#if (COM_SIGNAL_BYTE_ALIGN == STD_ON)

      /* Starting position of the signals in bytes */
      ComSignalDescBitType row = ComWritePropPtr->ComSignalPositionInByte;
#elif (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
      /* Starting position of the signals in bits divided by 8 => starting position in byte */
      ComSignalDescBitType row = (ComWritePropPtr->ComSignalPositionInBit / 8U);
      uint8 col = (uint8)ComWritePropPtr->ComSignalPositionInBit % 8U;
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_ON) */
      /* Signal position in bit has a maximum value of 2031. */
      sint16 pos = (sint16) row;


#if (COM_ENDIANNESS_CONVERSION == COM_BIG_ENDIAN)
      sint8 step = -1;
#elif (COM_ENDIANNESS_CONVERSION == COM_LITTLE_ENDIAN)
      sint8 step = 1;
#elif (COM_ENDIANNESS_CONVERSION == COM_OPAQUE)
      sint8 step = 1;
#elif (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
      sint8 step;
      if (ComWritePropPtr->endianness == COM_BIG_ENDIAN)
      {
         step = -1;
      }
      else
      {
         step = 1;
      }
#elif (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_DISABLE)
      sint8 step = 1;
#endif


#if (COM_CHECK_VALUE_SIZE == STD_ON)
      Com_EB_CheckValueSize32Bit(Val, ComWritePropPtr->size, un_int);
#endif /* (COM_CHECK_VALUE_SIZE == STD_ON) */


#if (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
      /* in the first byte, this much space can be used */
      space = space - col;

      /* reduce mask to the size of the signal */
      mask = mask >> (32U - ComWritePropPtr->size);

      /* shift LSB of mask to LSB position of the signal in the Pdu */
      mask = mask << col;

      /* prepare an uint8 which contains the least significant bits
       * of value */
      putvalue = (uint8)(((uint8) putvalue) << col);

#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_OFF) */


      Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

#if (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)
#if (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL)
      if (ComWritePropPtr->updateBit == TRUE)
#endif /* (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL) */
      {

         Com_SetBitUInt8(&ComWritePropPtr->dataPtr[ComWritePropPtr->ComUpdateBitPositionInBit / 8U],
               (ComWritePropPtr->ComUpdateBitPositionInBit % 8U));

      }
#endif /* (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) */

      /* use all bits available in the first byte */
      COM_TRIGGERED_OC_WRITE_BYTE_TO_PDU(
         ComWritePropPtr->dataPtr[pos],
         (uint8) (ComWritePropPtr->dataPtr[pos] & (uint8) (~mask)) | (uint8) (putvalue & mask),
         valueChanged);

      {
         uint8 tmp_val = ComWritePropPtr->size - space;
         ssize = (sint8) tmp_val;
      }
      pos = COM_SIGNAL_DESC_CAST(pos + (sint16)step);
      Val = Val >> space;

      while (ssize > 7)
      {
         /* if there are whole bytes of data, copy the byte-wise */
         COM_TRIGGERED_OC_WRITE_BYTE_TO_PDU(
               ComWritePropPtr->dataPtr[pos],
               (uint8) (0xFFU & Val),
               valueChanged);

         Val = Val >> 8U;
         ssize = ssize - (sint8)8;
         pos = COM_SIGNAL_DESC_CAST(pos + (sint16)step);
      }

#if (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
      if (ssize > 0)
      {
         /* mask out the bits not to be overwritten and write them */
         uint8 mask_u8 = 0xFFU >> ((sint8)8 - ssize);
         mask = (uint32) mask_u8;
         COM_TRIGGERED_OC_WRITE_BYTE_TO_PDU(
            ComWritePropPtr->dataPtr[pos],
            ((uint8) (ComWritePropPtr->dataPtr[pos] & (uint8) (~mask)) | (uint8) (Val & mask)),
            valueChanged);
      }
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_OFF) */

      Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();

   }                            /* if (0 != size) */

#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   *triggerPtr = valueChanged;
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */


   DBG_COM_EB_WRITETOPDUORSBUFF32BIT_EXIT(SignalDataPtr,ComWritePropPtr);
   return;
}                               /* Com_EB_WriteToPduOrSBuff32Bit */
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
TS_MOD_PRIV_DEFN FUNC(void, COM_CODE) Com_EB_WriteToPduOrSBuffByteArray
(
   P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   ComSignalBitSizeType size
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
)
{

#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   boolean valueChanged = FALSE;
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
   DBG_COM_EB_WRITETOPDUORSBUFFBYTEARRAY_ENTRY(dataPtr,SignalDataPtr,size);
   COM_TRIGGERED_OC_WRITE_BYTEARRAY_TO_PDU(
         dataPtr,
         SignalDataPtr,
         size,
         valueChanged);

#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   *triggerPtr = valueChanged;
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */


   DBG_COM_EB_WRITETOPDUORSBUFFBYTEARRAY_EXIT(dataPtr,SignalDataPtr,size);
   return;
}                               /* Com_EB_WriteToPduOrSBuffByteArray */


#endif /* (COM_SIGNAL_TYPE_UINT8_N_ENABLE == STD_ON) */



#if ((COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON) || (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON))

TS_MOD_PRIV_DEFN FUNC(uint8, COM_CODE) Com_EB_ReadFromPduOrSBuffUint8
(
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
)
{
   uint8 value;

#if (COM_SIGNAL_BYTE_ALIGN == STD_ON)
   ComSignalDescBitType row = ComReadPropPtr->ComSignalPositionInByte;      /* Starting position of the signals in bytes */
#elif (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
   ComSignalDescBitType row = (ComReadPropPtr->ComSignalPositionInBit / 8U); /* Starting position of the signals in bits divided by 8 => starting position in byte */
   uint8 col = (uint8)ComReadPropPtr->ComSignalPositionInBit % 8U;
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_ON) */
   /* Signal position in bit has a maximum value of 2031. */
   sint16 pos = (sint16) row;

#if (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
   if (col != 7U)
   {
      /* data does not start on byte boundary (MSB) */

      uint16 tmpval;
      const uint8 space = col + 1U;
      uint8 bitsread = 0U;

#if (COM_ENDIANNESS_CONVERSION == COM_BIG_ENDIAN)
      sint8 step = 1;
#elif (COM_ENDIANNESS_CONVERSION == COM_LITTLE_ENDIAN)
      sint8 step = -1;
#elif (COM_ENDIANNESS_CONVERSION == COM_OPAQUE)
      sint8 step = -1;
#elif (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
      sint8 step;
#elif (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_DISABLE)
      sint8 step = -1;
#endif

   DBG_COM_EB_READFROMPDUORSBUFFUINT8_ENTRY(ComReadPropPtr);

      /* Read most significant bits first and continue in the appropriate
       * direction, which depends on the byte order */
#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
      if (ComReadPropPtr->Endianness == COM_BIG_ENDIAN)
      {
         step = 1;
      }
      else
      {
         step = -1;
      }
#endif /* (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE) */

#if (COM_VALUE_INIT_REPLACE == STD_ON)
      if (ComReadPropPtr->TakePtrROM == TRUE)
      {
         /* read from ROM */

         tmpval = (uint8)COM_GET_INIT_VALUE_BYTE(ComReadPropPtr->pdudataptrROM[pos]);
         /* check number of bytes which shall be read */
         if (space < ComReadPropPtr->ComBitSize)
         {
            /* another byte has to be read */
            bitsread = bitsread + 8U;
            tmpval = tmpval << 8U;
            pos = COM_SIGNAL_DESC_CAST(pos + (sint16)step);
            tmpval = (uint16)(tmpval |
                     (uint8)COM_GET_INIT_VALUE_BYTE(ComReadPropPtr->pdudataptrROM[pos]));
         }
      }
      else
#endif /* (COM_VALUE_INIT_REPLACE == STD_ON) */
      {
         /* read value from Pdu */

         Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

         tmpval = (uint8)(ComReadPropPtr->pdudataptrRAM[pos]);
         /* check number of bytes which shall be read */
         if (space < ComReadPropPtr->ComBitSize)
         {
            /* another byte has to be read */
            bitsread = bitsread + 8U;
            tmpval = tmpval << 8U;
            pos = COM_SIGNAL_DESC_CAST(pos + (sint16)step);
            tmpval = (uint16)(tmpval | (uint8)(ComReadPropPtr->pdudataptrRAM[pos]));
         }

         Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();
      }



      /* read to much, shift back */
      tmpval = tmpval >> ((col + 1U + bitsread) - ComReadPropPtr->ComBitSize);
      value = (uint8)tmpval;

   }                            /* if (col != 7U) */
   else
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_OFF) */
   {
      /* byte aligned */
#if (COM_VALUE_INIT_REPLACE == STD_ON)
      if (ComReadPropPtr->TakePtrROM == TRUE)
      {
         /* read from ROM */
         value = (uint8)COM_GET_INIT_VALUE_BYTE(ComReadPropPtr->pdudataptrROM[pos]);
      }
      else
#endif /* (COM_VALUE_INIT_REPLACE == STD_ON) */
      {
         /* read value from Pdu */

         Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

         value = (uint8)(ComReadPropPtr->pdudataptrRAM[pos]);

         Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();
      }


#if (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
      /* read to much, shift back */
      value = (uint8)value >> (8U - ComReadPropPtr->ComBitSize);
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_OFF) */

   }

   /* mask the unused bits */
   {
      uint8 mask = 0xFFU;
      mask = (uint8)(mask >> (8U - ComReadPropPtr->ComBitSize));
      value = (uint8)(value & mask);
   }


   DBG_COM_EB_READFROMPDUORSBUFFUINT8_EXIT(value,ComReadPropPtr);
   return value;
}                               /* Com_EB_ReadFromPduOrSBuffUint8 */

#endif /* ((COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON) || (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON)) */

#if (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON)

TS_MOD_PRIV_DEFN FUNC(sint8, COM_CODE) Com_EB_ReadFromPduOrSBuffSint8
(
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
)
{

   uint8 uint8value = Com_EB_ReadFromPduOrSBuffUint8(ComReadPropPtr);

   /* get the MSB */
   boolean const MSB = (boolean)(uint8value >> (ComReadPropPtr->ComBitSize - 1U));

   DBG_COM_EB_READFROMPDUORSBUFFSINT8_ENTRY(ComReadPropPtr);
   if (MSB != 0U)
   {
      /* the value is negative, fill all leading bits with 1 */
      uint8 mask = 0xFFU;
      mask = (uint8)(mask << (ComReadPropPtr->ComBitSize - 1U));
      uint8value = (uint8)(uint8value | mask);
   }



   DBG_COM_EB_READFROMPDUORSBUFFSINT8_EXIT((sint8)uint8value,ComReadPropPtr);
   return (sint8)uint8value;
}                               /* Com_EB_ReadFromPduOrSBuffSint8 */

#endif /* (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON) */

#if ((COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON) || (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON))

TS_MOD_PRIV_DEFN FUNC(uint16, COM_CODE) Com_EB_ReadFromPduOrSBuffUint16
(
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
)
{
   uint16 value;

   uint8 bitsread;

   sint8 ssize = (sint8)ComReadPropPtr->ComBitSize;

#if (COM_SIGNAL_BYTE_ALIGN == STD_ON)
   ComSignalDescBitType row = ComReadPropPtr->ComSignalPositionInByte;      /* Starting position of the signals in bytes */

#elif (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
   ComSignalDescBitType row = (ComReadPropPtr->ComSignalPositionInBit / 8U); /* Starting position of the signals in bits divided by 8 => starting position in byte */
   uint8 col = (uint8)ComReadPropPtr->ComSignalPositionInBit % 8U;
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_ON) */
   /* Signal position in bit has a maximum value of 2031. */
   sint16 pos = (sint16) row;

#if (COM_ENDIANNESS_CONVERSION == COM_BIG_ENDIAN)
   sint8 step = 1;
#elif (COM_ENDIANNESS_CONVERSION == COM_LITTLE_ENDIAN)
   sint8 step = -1;
#elif (COM_ENDIANNESS_CONVERSION == COM_OPAQUE)
   sint8 step = -1;
#elif (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
   sint8 step;
#elif (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_DISABLE)
   sint8 step = -1;
#endif

   DBG_COM_EB_READFROMPDUORSBUFFUINT16_ENTRY(ComReadPropPtr);

   /* Read most significant bits first and continue in the appropriate
    * direction, which depends on the byte order */
#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
   if (ComReadPropPtr->Endianness == COM_BIG_ENDIAN)
   {
      step = 1;
   }
   else
   {
      step = -1;
   }
#endif /* (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE) */


#if (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
   if (col != 7U)
   {
      /* data does not start on byte boundary (MSB) */

      uint32 tmpval;
      bitsread = 0U;

#if (COM_VALUE_INIT_REPLACE == STD_ON)
      if (ComReadPropPtr->TakePtrROM == TRUE)
      {
         /* read from ROM */

         /* read the byte with the MSB */
         tmpval = (uint8)COM_GET_INIT_VALUE_BYTE(ComReadPropPtr->pdudataptrROM[pos]);

         /* range of col if 0-7, cast to signed char is still in range */
         ssize = ssize - 1 - (sint8) col;

         while (ssize > 0)
         {
            bitsread = bitsread + 8U;
            ssize = ssize - 8;
            tmpval = tmpval << 8U;
            pos = COM_SIGNAL_DESC_CAST(pos + (sint16)step);
            tmpval = (uint32)(tmpval |
                     (uint8)COM_GET_INIT_VALUE_BYTE(ComReadPropPtr->pdudataptrROM[pos]));
         }
      }
      else
#endif /* (COM_VALUE_INIT_REPLACE == STD_ON) */
      {
         /* read value from Pdu */
         Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

         /* read the byte with the MSB */
         tmpval = (uint8)(ComReadPropPtr->pdudataptrRAM[pos]);

         /* range of col if 0-7, cast to signed char is still in range */
         ssize = ssize - 1 - (sint8) col;

         while (ssize > 0)
         {
            bitsread = bitsread + 8U;
            ssize = ssize - 8;
            tmpval = tmpval << 8U;
            pos = COM_SIGNAL_DESC_CAST(pos + (sint16)step);
            tmpval = (uint32)(tmpval | (uint8)(ComReadPropPtr->pdudataptrRAM[pos]));
         }

         Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();
      }


      /* read to much, shift back */
      tmpval = tmpval >> ((col + 1U + bitsread) - ComReadPropPtr->ComBitSize);
      value = (uint16)tmpval;

   }                            /* if (col != 7U) */
   else
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_OFF) */
   {

      bitsread = 8U;

#if (COM_VALUE_INIT_REPLACE == STD_ON)
      /* byte aligned */
      if (ComReadPropPtr->TakePtrROM == TRUE)
      {
         /* read from ROM */
         ssize = ssize - 8;

         value = (uint8)COM_GET_INIT_VALUE_BYTE(ComReadPropPtr->pdudataptrROM[pos]);

         while (ssize > 0)
         {
            bitsread = bitsread + 8U;
            ssize = ssize - 8;
            value = (uint16)value << 8U;
            pos = COM_SIGNAL_DESC_CAST(pos + (sint16)step);
            value = (uint16)(value |
                    (uint8)COM_GET_INIT_VALUE_BYTE(ComReadPropPtr->pdudataptrROM[pos]));
         }

      }
      else
#endif /* (COM_VALUE_INIT_REPLACE == STD_ON) */
      {
         /* read value from Pdu */

         ssize = ssize - 8;

         Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

         value = (uint8)(ComReadPropPtr->pdudataptrRAM[pos]);

         while (ssize > 0)
         {
            bitsread = bitsread + 8U;
            ssize = ssize - 8;
            value = (uint16)value << 8U;
            pos = COM_SIGNAL_DESC_CAST(pos + (sint16)step);
            value = (uint16)(value | (uint8)(ComReadPropPtr->pdudataptrRAM[pos]));
         }


         Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();
      }


#if (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
      /* read to much, shift back */
      value = (uint16)value >> (bitsread - ComReadPropPtr->ComBitSize);
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_OFF) */

   }

   /* mask the unused bits */
   {
      uint16 mask = 0xFFFFU;
      mask = (uint16)(mask >> (16U - ComReadPropPtr->ComBitSize));
      value = (uint16)(value & mask);
   }


   DBG_COM_EB_READFROMPDUORSBUFFUINT16_EXIT(value,ComReadPropPtr);
   return value;
}                               /* Com_EB_ReadFromPduOrSBuffUint16 */

#endif /* ((COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON) || (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON)) */

#if (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON)

TS_MOD_PRIV_DEFN FUNC(sint16, COM_CODE) Com_EB_ReadFromPduOrSBuffSint16
(
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
)
{

   uint16 uint16value = Com_EB_ReadFromPduOrSBuffUint16(ComReadPropPtr);

   /* get the MSB */
   boolean const MSB = (boolean)(uint16value >> (ComReadPropPtr->ComBitSize - 1U));

   DBG_COM_EB_READFROMPDUORSBUFFSINT16_ENTRY(ComReadPropPtr);
   if (MSB != 0U)
   {
      /* the value is negative, fill all leading bits with 1 */
      uint16 mask = 0xFFFFU;
      mask = (uint16)(mask << (ComReadPropPtr->ComBitSize - 1U));
      uint16value = (uint16)(uint16value | mask);
   }



   DBG_COM_EB_READFROMPDUORSBUFFSINT16_EXIT((sint16)uint16value,ComReadPropPtr);
   return (sint16)uint16value;
}                               /* Com_EB_ReadFromPduOrSBuffSint16 */

#endif /* (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON) */

#if ((COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON) || (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON))

TS_MOD_PRIV_DEFN FUNC(uint32, COM_CODE) Com_EB_ReadFromPduOrSBuffUint32
(
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
)
{

   uint32 value = 0;

#if (COM_ENDIANNESS_CONVERSION == COM_BIG_ENDIAN)
   sint8 step = 1;
#elif (COM_ENDIANNESS_CONVERSION == COM_LITTLE_ENDIAN)
   sint8 step = -1;
#elif (COM_ENDIANNESS_CONVERSION == COM_OPAQUE)
   sint8 step = -1;
#elif (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
   sint8 step;
#elif (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_DISABLE)
   sint8 step = -1;
#endif


#if (COM_SIGNAL_BYTE_ALIGN == STD_ON)
   ComSignalDescBitType row = ComReadPropPtr->ComSignalPositionInByte;      /* Starting position of the signals in bytes */
#elif (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
   ComSignalDescBitType row = (ComReadPropPtr->ComSignalPositionInBit / 8U); /* Starting position of the signals in bits divided by 8 => starting position in byte */
   uint8 col = (uint8)ComReadPropPtr->ComSignalPositionInBit % 8U;
   uint8 mask;
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_ON) */
   /* Signal position in bit has a maximum value of 2031. */
   sint16 pos = (sint16) row;

   ComSignalBitSizeType size = ComReadPropPtr->ComBitSize;

   DBG_COM_EB_READFROMPDUORSBUFFUINT32_ENTRY(ComReadPropPtr);

   /* Read most significant bits first and continue in the appropriate
    * direction, which depends on the byte order */
#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
   if (ComReadPropPtr->Endianness == COM_BIG_ENDIAN)
   {
      step = 1;
   }
   else
   {
      step = -1;
   }
#endif /* (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE) */

#if (COM_VALUE_INIT_REPLACE == STD_ON)
   if (ComReadPropPtr->TakePtrROM == TRUE)
   {
      /* read from ROM */

#if (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
      if (col != 7U)
      {
         /* data does not start on byte boundary (MSB) */
         uint8 space = col + 1;
         uint8 tmp_val;
         mask = (uint8)(0xFFU >> (7U - col));
         tmp_val = COM_GET_INIT_VALUE_BYTE(ComReadPropPtr->pdudataptrROM[pos]) & mask;
         value = (uint32) tmp_val;

         if (space >= size)
         {
            /* If we've already read as many or more bits than intended */
            value >>= (space - size);
            size = 0U;
         }
         else
         {
            /* prepare to continue reading */
            pos = COM_SIGNAL_DESC_CAST(pos + (sint16)step);
            size -= space;
         }
      }
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_OFF) */

      while (size > 7U)
      {
         /* read whole bytes */
         value <<= 8U;
         value += COM_GET_INIT_VALUE_BYTE(ComReadPropPtr->pdudataptrROM[pos]);
         size -= 8U;
         pos = COM_SIGNAL_DESC_CAST(pos + (sint16)step);
      }

#if (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
      if (size > 0U)
      {
         /* read last bits */
         value <<= size;
         value += (uint32) COM_GET_INIT_VALUE_BYTE(
               ComReadPropPtr->pdudataptrROM[pos]) >> (8U - size);
      }
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_OFF) */

   }
   else
#endif /* (COM_VALUE_INIT_REPLACE == STD_ON) */
   {
      /* read value from the Pdu */

      Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

#if (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
      if (col != 7U)
      {
         /* data does not start on byte boundary (MSB) */
         uint8 space = col + 1;
         uint8 tmp_val;
         mask = ((uint8) 0xFFU) >> (7U - col);
         tmp_val = ComReadPropPtr->pdudataptrRAM[pos] & mask;
         value = (uint32) tmp_val;

         if (space >= size)
         {
            /* If we've already read as many or more bits than intended */
            value >>= (space - size);
            size = 0U;
         }
         else
         {
            /* prepare to continue reading */
            pos = COM_SIGNAL_DESC_CAST(pos + (sint16)step);
            size -= space;
         }
      }
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_OFF) */

      while (size > 7U)
      {
         /* read whole bytes */
         value <<= 8U;
         value += ComReadPropPtr->pdudataptrRAM[pos];
         size -= 8U;
         pos = COM_SIGNAL_DESC_CAST(pos + (sint16)step);
      }

#if (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
      if (size > 0U)
      {
         /* read last bits */
         value <<= size;
         value += (uint32) ComReadPropPtr->pdudataptrRAM[pos] >> (8U - size);
      }
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_OFF) */

      Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();
   }

   DBG_COM_EB_READFROMPDUORSBUFFUINT32_EXIT(value,ComReadPropPtr);
   return value;
}                               /* Com_EB_ReadFromPduOrSBuffUint32 */

#endif /* ((COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON) || (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON)) */

#if (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON)

TS_MOD_PRIV_DEFN FUNC(sint32, COM_CODE) Com_EB_ReadFromPduOrSBuffSint32
(
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
)
{


   uint32 uint32value = Com_EB_ReadFromPduOrSBuffUint32(ComReadPropPtr);

   /* get the MSB */
   boolean const MSB = (boolean)(uint32value >> (ComReadPropPtr->ComBitSize - 1U));

   DBG_COM_EB_READFROMPDUORSBUFFSINT32_ENTRY(ComReadPropPtr);

   if (MSB != 0U)
   {
      /* the value is negative, fill all leading bits with 1 */
      uint32 mask = (uint32) 0xFFFFFFFFUL;
      mask = (uint32)(mask << (ComReadPropPtr->ComBitSize - 1U));
      uint32value = (uint32)(uint32value | mask);
   }



   DBG_COM_EB_READFROMPDUORSBUFFSINT32_EXIT((sint32)uint32value,ComReadPropPtr);
   return (sint32)uint32value;
}                               /* Com_EB_ReadFromPduOrSBuffSint32 */

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

TS_MOD_PRIV_DEFN FUNC(uint32, COM_CODE) Com_EB_ReadFromPduOrShadowBuffer
(
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
)
{
   boolean un_int = FALSE;
   /* the flag go makes the function exit if the signal to extract is
    * of boolean type */
   boolean go = FALSE;
   uint32 value = 0;
   uint32 bigmask = 0;
   ComSignalBitSizeType size = ComReadPropPtr->ComBitSize;
   ComSignalBitSizeType MSBPos = ComReadPropPtr->ComBitSize - 1U;

   DBG_COM_EB_READFROMPDUORSHADOWBUFFER_ENTRY(ComReadPropPtr);

   /* Read data from IPdu into an UInt32 */

   switch (ComReadPropPtr->SignalType)
   {
#if ((COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON) || \
      (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL))
      case COM_BOOLEAN:
      {
#if (COM_SIGNAL_BYTE_ALIGN == STD_ON)
         /* ComSignalPositionInByte is the position in bit for Boolean signals */
         ComSignalDescBitType const ComSignalPosition = ComReadPropPtr->ComSignalPositionInByte;
#elif (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
         ComSignalDescBitType  const ComSignalPosition = ComReadPropPtr->ComSignalPositionInBit;
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_ON) */
         uint8 tmp_result;
         uint8 var = (uint8) COM_CHOOSE_INIT_PTR(
               ComReadPropPtr->TakePtrROM,
               ComReadPropPtr->pdudataptrROM,
               ComReadPropPtr->pdudataptrRAM,
               (ComSignalPosition / 8U));

         TS_GetBit(&var, ComSignalPosition % 8U, uint8, tmp_result);
         value = (uint32) tmp_result;
      }
        break;
#endif /* ((COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON) || \
      (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)) */
#if (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON)
      case COM_UINT8:
#endif /* (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON) */
#if (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON)
      case COM_UINT16:
#endif /* (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON) */
#if (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON)
      case COM_UINT32:
#endif /* (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON) */

#if ((COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON) || (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON) || (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON))
         /* set a flag that the value to be extracted is unsigned */
         un_int = TRUE;
         /* set a flag triggering further processing */
         go = TRUE;
         break;
#endif

#if (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON)
      case COM_SINT8:
#endif /* (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON) */
#if (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON)
      case COM_SINT16:
#endif /* (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON) */

#if ((COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON) || (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON))
         /* create a mask for sign extension */
         bigmask = (uint32) ((uint32) ~ 0UL) << size;
         /* set a flag triggering further processing */
         go = TRUE;
         break;
#endif

#if (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON)
      case COM_SINT32:
         /* create mask for sign extension only if required; if a value
          * is shifted left it's full size in bits, some implementations
          * faciliate a number with all bits set and not a number with all
          * bits cleared, which is required */
         if (size != 32)
         {
            bigmask = (uint32) ((uint32) ~ 0UL) << size;
         }
         /* set a flag triggering further processing */
         go = TRUE;
         break;
#endif /* (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON) */
         /* CHECK: NOPARSE */
      default:
          COM_UNREACHABLE_CODE_ASSERT(COM_INTERNAL_API_ID);
          break;
         /* CHECK: PARSE */
   }
   if (go == TRUE)
   {

#if (COM_ENDIANNESS_CONVERSION == COM_BIG_ENDIAN)
      sint8 step = 1;
#elif (COM_ENDIANNESS_CONVERSION == COM_LITTLE_ENDIAN)
      sint8 step = -1;
#elif (COM_ENDIANNESS_CONVERSION == COM_OPAQUE)
      sint8 step = -1;
#elif (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
      sint8 step;
#elif (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_DISABLE)
      sint8 step = -1;
#endif


#if (COM_SIGNAL_BYTE_ALIGN == STD_ON)
      ComSignalDescBitType row = ComReadPropPtr->ComSignalPositionInByte;      /* Starting position of the signals in bytes */
#elif (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
      ComSignalDescBitType row = (ComReadPropPtr->ComSignalPositionInBit / 8U); /* Starting position of the signals in bits divided by 8 => starting position in byte */
      uint8 col = (uint8)ComReadPropPtr->ComSignalPositionInBit % 8U;
      uint8 mask;
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_ON) */
      /* Signal position in bit has a maximum value of 2031. */
      sint16 pos = (sint16) row;

      /* Read most significant bits first and continue in the appropriate
       * direction, which depends on the byte order */
#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
      if (ComReadPropPtr->Endianness == COM_BIG_ENDIAN)
      {
         step = 1;
      }
      else
      {
         step = -1;
      }
#endif /* (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE) */

      Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

#if (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
      if (col != 7U)
      {
         /* data does not start on byte boundary (MSB) */
         uint8 space = col + 1U;
         uint8 tmp_val;
         mask = ((uint8) 0xFFU) >> (7U - col);
         tmp_val = COM_CHOOSE_INIT_PTR(
               ComReadPropPtr->TakePtrROM,
               ComReadPropPtr->pdudataptrROM,
               ComReadPropPtr->pdudataptrRAM,
               pos) & mask;
         value = (uint32) tmp_val;

         if (space >= size)
         {
            /* If we've already read as many or more bits than intended */
            value >>= (space - size);
            size = 0U;
         }
         else
         {
            /* prepare to continue reading */
            pos = COM_SIGNAL_DESC_CAST(pos + (sint16)step);
            size -= space;
         }
      }
#endif

      while (size > 7U)
      {
         /* read whole bytes */
         value <<= 8U;
         value += (uint8) COM_CHOOSE_INIT_PTR(
               ComReadPropPtr->TakePtrROM,
               ComReadPropPtr->pdudataptrROM,
               ComReadPropPtr->pdudataptrRAM,
               pos);
         size -= 8U;
         pos = COM_SIGNAL_DESC_CAST(pos + (sint16)step);
      }

#if (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
      if (size > 0)
      {
         uint8 tmp_val =
             COM_CHOOSE_INIT_PTR(
                   ComReadPropPtr->TakePtrROM,
                   ComReadPropPtr->pdudataptrROM,
                   ComReadPropPtr->pdudataptrRAM,
                   pos) >> (8U - size);
         /* read last bits */
         value <<= size;
         value += (uint32) tmp_val;
      }
#endif

      Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();

      if (un_int == FALSE)
      {
         boolean const MSB = (boolean)(value >> (MSBPos));
         if (MSB == 1U)
         {
            /* sign extension; eventually fill up leftmost bits with ones */
            value |= bigmask;
         }
      }
   }

   DBG_COM_EB_READFROMPDUORSHADOWBUFFER_EXIT(value,ComReadPropPtr);
   return value;
}                               /* Com_EB_ReadFromPduOrShadowBuffer */
#endif /* (COM_GENERIC_READ_REQUIRED == STD_ON) */


#if ((COM_FILTER_RECEIVER_ENABLE == STD_ON) || \
      ((COM_TMS_ENABLE == STD_ON) && (COM_SIGNAL_GW_ENABLE == STD_ON)))


#if (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON)
_COM_STATIC_ FUNC(boolean, COM_CODE) Com_EB_CalculateFilter_Bool
(
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr,
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr
)
{
#if (COM_SIGNAL_BYTE_ALIGN == STD_ON)
      /* ComSignalPositionInByte is the position in bit for Boolean signals */
      ComSignalDescBitType const ComSignalPosition = ComReadPropPtr->ComSignalPositionInByte;
#elif (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
      ComSignalDescBitType  const ComSignalPosition = ComReadPropPtr->ComSignalPositionInBit;
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_ON) */

      uint8 MSB;
      uint8 tmp_val =
#if (COM_VALUE_INIT_REPLACE == STD_ON)
            COM_CHOOSE_INIT_PTR(
                  ComReadPropPtr->TakePtrROM,
                  ComReadPropPtr->pdudataptrROM,
                  ComReadPropPtr->pdudataptrRAM,
                  (ComSignalPosition / 8U));
#else
                  (ComReadPropPtr->pdudataptrRAM)[ComSignalPosition / 8U];
#endif /* (COM_VALUE_INIT_REPLACE == STD_ON) */
      TS_GetBit(&tmp_val, ComSignalPosition % 8U, uint8, MSB);

      return Com_EB_FilterBoolean(ComFilterPropPtr, &MSB);
}
#endif /* (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON)
_COM_STATIC_ FUNC(boolean, COM_CODE) Com_EB_CalculateFilter_Uint8
(
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr,
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr
)
{
   uint8 const value = Com_EB_ReadFromPduOrSBuffUint8(ComReadPropPtr);

   return Com_EB_FilterUint8(ComFilterPropPtr, &value);
}
#endif /* (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON)
_COM_STATIC_ FUNC(boolean, COM_CODE) Com_EB_CalculateFilter_Uint16
(
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr,
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr
)
{
   uint16 const value = Com_EB_ReadFromPduOrSBuffUint16(ComReadPropPtr);

   return Com_EB_FilterUint16(ComFilterPropPtr, &value);
}
#endif /* (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON)
_COM_STATIC_ FUNC(boolean, COM_CODE) Com_EB_CalculateFilter_Uint32
(
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr,
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr
)
{
   uint32 const value = Com_EB_ReadFromPduOrSBuffUint32(ComReadPropPtr);

   return Com_EB_FilterUint32(ComFilterPropPtr, &value);
}
#endif /* (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON)
_COM_STATIC_ FUNC(boolean, COM_CODE) Com_EB_CalculateFilter_Sint8
(
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr,
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr
)
{
   sint8 const value = Com_EB_ReadFromPduOrSBuffSint8(ComReadPropPtr);

   return Com_EB_FilterSint8(ComFilterPropPtr, &value);
}
#endif /* (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON)
_COM_STATIC_ FUNC(boolean, COM_CODE) Com_EB_CalculateFilter_Sint16
(
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr,
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr
)
{
   sint16 const value = Com_EB_ReadFromPduOrSBuffSint16(ComReadPropPtr);

   return Com_EB_FilterSint16(ComFilterPropPtr, &value);
}
#endif /* (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON)
_COM_STATIC_ FUNC(boolean, COM_CODE) Com_EB_CalculateFilter_Sint32
(
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr,
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr
)
{
   sint32 const value = Com_EB_ReadFromPduOrSBuffSint32(ComReadPropPtr);

   return Com_EB_FilterSint32(ComFilterPropPtr, &value);
}
#endif /* (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON) */


TS_MOD_PRIV_DEFN FUNC(boolean, COM_CODE) Com_EB_CalculateFilter
(
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr,
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr
)
{
   boolean FilterResult = FALSE;

   DBG_COM_EB_CALCULATEFILTER_ENTRY(ComReadPropPtr,ComFilterPropPtr);

   switch (ComReadPropPtr->SignalType)
   {
#if (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON)
   case COM_BOOLEAN:
   {
      FilterResult = Com_EB_CalculateFilter_Bool(ComReadPropPtr, ComFilterPropPtr);
      break;
   }                            /* case COM_BOOLEAN: */
#endif /* (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON)
   case COM_UINT8:
   {
      FilterResult = Com_EB_CalculateFilter_Uint8(ComReadPropPtr, ComFilterPropPtr);
      break;
   }                            /* case COM_UINT8: */
#endif /* (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON)
   case COM_UINT16:
   {
      FilterResult = Com_EB_CalculateFilter_Uint16(ComReadPropPtr, ComFilterPropPtr);
      break;
   }                            /* case COM_UINT16: */
#endif /* (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON)
   case COM_UINT32:
   {
      FilterResult = Com_EB_CalculateFilter_Uint32(ComReadPropPtr, ComFilterPropPtr);
      break;
   }                            /* case COM_UINT32: */
#endif /* (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON)
   case COM_SINT8:
   {
      FilterResult = Com_EB_CalculateFilter_Sint8(ComReadPropPtr, ComFilterPropPtr);
      break;
   }                            /* case COM_SINT8: */
#endif /* (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON)
   case COM_SINT16:
   {
      FilterResult = Com_EB_CalculateFilter_Sint16(ComReadPropPtr, ComFilterPropPtr);
      break;
   }                            /* case COM_SINT16: */
#endif /* (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON)
   case COM_SINT32:
   {
      FilterResult = Com_EB_CalculateFilter_Sint32(ComReadPropPtr, ComFilterPropPtr);
      break;
   }                            /* case COM_SINT32: */
#endif /* (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON) */

   /* CHECK: NOPARSE */
   default:
   {
       COM_UNREACHABLE_CODE_ASSERT(COM_INTERNAL_API_ID);
   }
   break;
   /* CHECK: PARSE */
   }


   DBG_COM_EB_CALCULATEFILTER_EXIT(FilterResult,ComReadPropPtr,ComFilterPropPtr);
   return FilterResult;
}                               /* Com_EB_CalculateFilter */

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

TS_MOD_PRIV_DEFN FUNC(void, COM_CODE) Com_EB_SetBufferUInt32
(
   uint32 Val,
   Com_TS_SignalTypeType SignalType,
   ComSignalBufferRefType ValueRef
)
{



   DBG_COM_EB_SETBUFFERUINT32_ENTRY(Val,SignalType,ValueRef);
   switch (SignalType)
   {
#if ((COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON) || \
      (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL))
      case COM_BOOLEAN:
         {
            CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) bufferBaseBool =
               (P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT))
               & Com_gDataMemPtr[Com_gConfigPtr->ComBufferBaseBool];
            if (Val == 1U)
            {
               TS_AtomicSetBit_8(&bufferBaseBool[(ValueRef / 8U)], (ValueRef % 8U));
            }
            else
            {
               TS_AtomicClearBit_8(&bufferBaseBool[(ValueRef / 8U)], (ValueRef % 8U));
            }
         }
         break;
#endif /* ((COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON) || \
      (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)) */

#if (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON)
      case COM_UINT8:
         {
            CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) bufferBaseUint8 =
               (P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT))
               & Com_gDataMemPtr[Com_gConfigPtr->ComBufferBaseUInt8];
            TS_AtomicAssign8(bufferBaseUint8[ValueRef], (uint8) Val);
         }
         break;
#endif /* (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON) */

#if (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON)
      case COM_UINT16:
         {
            CONSTP2VAR(uint16, AUTOMATIC, COM_VAR_NOINIT) bufferBaseUint16 =
                COM_GET_MEMPTR(uint16, Com_gConfigPtr->ComBufferBaseUInt16);
            TS_AtomicAssign16(bufferBaseUint16[ValueRef], (uint16) Val);
         }
         break;
#endif /* (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON) */

#if (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON)
      case COM_UINT32:
         {
            CONSTP2VAR(uint32, AUTOMATIC, COM_VAR_NOINIT) bufferBaseUint32 =
                COM_GET_MEMPTR(uint32, Com_gConfigPtr->ComBufferBaseUInt32);
            TS_AtomicAssign32(bufferBaseUint32[ValueRef], (uint32) Val);
         }
         break;
#endif /* (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON) */

#if (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON)
      case COM_SINT8:
         {
            CONSTP2VAR(sint8, AUTOMATIC, COM_VAR_NOINIT) bufferBaseSint8 =
               (P2VAR(sint8, AUTOMATIC, COM_VAR_NOINIT))
               & Com_gDataMemPtr[Com_gConfigPtr->ComBufferBaseSInt8];
            TS_AtomicAssign8(bufferBaseSint8[ValueRef], (sint8) Val);
         }
         break;
#endif /* (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON) */

#if (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON)
      case COM_SINT16:
         {
            CONSTP2VAR(sint16, AUTOMATIC, COM_VAR_NOINIT) bufferBaseSint16 =
                COM_GET_MEMPTR(sint16, Com_gConfigPtr->ComBufferBaseSInt16);
            TS_AtomicAssign16(bufferBaseSint16[ValueRef], (sint16) Val);
         }
         break;
#endif /* (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON) */

#if (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON)
      case COM_SINT32:
         {
            CONSTP2VAR(sint32, AUTOMATIC, COM_VAR_NOINIT) bufferBaseSint32 =
                COM_GET_MEMPTR(sint32, Com_gConfigPtr->ComBufferBaseSInt32);
            TS_AtomicAssign32(bufferBaseSint32[ValueRef], (sint32) Val);
         }
         break;
#endif /* (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON) */

         /* CHECK: NOPARSE */
      default:
          COM_UNREACHABLE_CODE_ASSERT(COM_INTERNAL_API_ID);
          break;
         /* CHECK: PARSE */
   }                            /* end switch */

   DBG_COM_EB_SETBUFFERUINT32_EXIT(Val,SignalType,ValueRef);
   return;
}                               /* Com_EB_SetBufferUInt32 */

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

TS_MOD_PRIV_DEFN FUNC(void, COM_CODE) Com_EB_WriteToUpperLayer
(
   uint32 value,
   /* Deviation MISRA-1 */
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) DataPtr,
   Com_TS_SignalTypeType SignalType
)
{
   DBG_COM_EB_WRITETOUPPERLAYER_ENTRY(value,DataPtr,SignalType);
   switch (SignalType)
   {
#if (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON)
      case COM_BOOLEAN:
         (* (P2VAR(boolean, AUTOMATIC, COM_APPL_DATA)) DataPtr) = (boolean) value;
         break;
#endif /* (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON) */
#if (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON)
      case COM_UINT8:
         (* (P2VAR(uint8, AUTOMATIC, COM_APPL_DATA)) DataPtr) = (uint8) value;
         break;
#endif /* (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON) */
#if (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON)
      case COM_UINT16:
         (* (P2VAR(uint16, AUTOMATIC, COM_APPL_DATA)) DataPtr) = (uint16) value;
         break;
#endif /* (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON) */
#if (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON)
      case COM_UINT32:
         (* (P2VAR(uint32, AUTOMATIC, COM_APPL_DATA)) DataPtr) = (uint32) value;
         break;
#endif /* (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON) */
#if (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON)
      case COM_SINT8:
         (* (P2VAR(sint8, AUTOMATIC, COM_APPL_DATA)) DataPtr) = (sint8) value;
         break;
#endif /* (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON) */
#if (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON)
      case COM_SINT16:
         (* (P2VAR(sint16, AUTOMATIC, COM_APPL_DATA)) DataPtr) = (sint16) value;
         break;
#endif /* (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON) */
#if (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON)
      case COM_SINT32:
         (* (P2VAR(sint32, AUTOMATIC, COM_APPL_DATA)) DataPtr) = (sint32) value;
         break;
#endif /* (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON) */
         /* CHECK: NOPARSE */
      default:
          COM_UNREACHABLE_CODE_ASSERT(COM_INTERNAL_API_ID);
          break;
         /* CHECK: PARSE */
   }
   DBG_COM_EB_WRITETOUPPERLAYER_EXIT(value,DataPtr,SignalType);
}                               /* Com_EB_WriteToUpperLayer */
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

TS_MOD_PRIV_DEFN FUNC(void, COM_CODE) Com_ResetFilerOneEveryN
(
   ComFilterRefType ComFilterRef
)
{
   P2CONST(ComFilterOneEveryNType, AUTOMATIC, COM_APPL_CONST) ComFilterOneEveryNPtr;
   /* pointer to the start of array where the occurrence values  are stored */
   P2VAR(ComFilterOneEveryNSizeType, AUTOMATIC, COM_VAR_NOINIT) occurrencebase;

   DBG_COM_RESETFILERONEEVERYN_ENTRY(ComFilterRef);

   /* Deviation MISRA-2, MISRA-3 <+5> */
   ComFilterOneEveryNPtr =
         COM_GET_CONFIG_ELEMENT(ComFilterOneEveryNType,
                                Com_gConfigPtr->ComFilterOneEveryNRef,
                                ComFilterRef);

   /* get the start of the occurrence values */
   occurrencebase =
       COM_GET_MEMPTR(ComFilterOneEveryNSizeType, Com_gConfigPtr->ComFilterOneEveryNBase);

   /* reset counter */
#if (COM_FILTER_ONE_EVERY_N_SIZE_TYPE_MAX == COM_SIZE_8_BIT)
   TS_AtomicAssign8(occurrencebase[ComFilterOneEveryNPtr->ComFilterOccurrence],
         0U);
#elif (COM_FILTER_ONE_EVERY_N_SIZE_TYPE_MAX == COM_SIZE_16_BIT)
   TS_AtomicAssign16(occurrencebase[ComFilterOneEveryNPtr->ComFilterOccurrence],
         0U);
#elif (COM_FILTER_ONE_EVERY_N_SIZE_TYPE_MAX == COM_SIZE_32_BIT)
   TS_AtomicAssign32(occurrencebase[ComFilterOneEveryNPtr->ComFilterOccurrence],
         0U);
#endif /* (COM_FILTER_ONE_EVERY_N_SIZE_TYPE_MAX == COM_SIZE_8_BIT) */

   DBG_COM_RESETFILERONEEVERYN_EXIT(ComFilterRef);
   return;
}                               /* Com_ResetFilerOneEveryN */

#endif /* (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON) */



#define COM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[end of file]===========================================*/
