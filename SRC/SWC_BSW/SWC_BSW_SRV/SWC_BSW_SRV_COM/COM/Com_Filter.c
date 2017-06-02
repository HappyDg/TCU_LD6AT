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
 * MISRA-1) Deviated Rule: 11.3 (required)
 * "A cast should not be performed between a pointer type and an integral type."
 *
 * Reason:
 * Actually this is not a cast between a pointer and a integral type, since 0
 * is null pointer constant.
 *
 * MISRA-2) Deviated Rule: 6.3 (advisory)
 * "'typedefs' that indicate size and signedness should be used in place of the basic types."
 *
 * Reason:
 * In this case variables are casted to a natural integral type since, the value is further used
 * for purposes where natural types are most efficient (e.g. indexing).
 */


/*==================[inclusions]============================================*/

#include <Com_Trace.h>
#include <TSAutosar.h>          /* EB specific standard types */
#include <Com_Filter.h>

#if (COM_FILTER_AVAILABLE == STD_ON)
#include <Com_Priv.h>           /* Module private API */

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_START_SEC_CODE
#include <MemMap.h>
#endif

#if (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON)

_COM_STATIC_ FUNC(boolean, COM_CODE) Com_EB_FilterOneEveryN
(
      ComFilterRefType ComFilterRef
);

_COM_STATIC_ FUNC(boolean, COM_CODE) Com_EB_FilterOneEveryN
(
      ComFilterRefType ComFilterRef
)
{
   boolean FilterResult;
   /* Do OneEveryN-filtering */
   /* get reference to the structure where the data of the filter are
    * stored */
   /* Deviation MISRA-1, MISRA-2 <+7> */
   CONSTP2CONST(ComFilterOneEveryNType, AUTOMATIC,
                COM_APPL_CONST) ComFilterOneEveryNPtr =
      COM_GET_CONFIG_ELEMENT(ComFilterOneEveryNType,
                             Com_gConfigPtr->ComFilterOneEveryNRef, ComFilterRef);
   ComFilterOneEveryNSizeType period;
   ComFilterOneEveryNSizeType offset;
   ComFilterOneEveryNSizeType occurrence;
   /* pointer to the start of array where the occurrence values  are stored */
   P2VAR(ComFilterOneEveryNSizeType, AUTOMATIC, COM_VAR_NOINIT) occurrencebase;

   DBG_COM_EB_FILTERONEEVERYN_ENTRY(ComFilterRef);

   /* get the configuration of the filter */
   offset = ComFilterOneEveryNPtr->ComFilterOffset;
   period = ComFilterOneEveryNPtr->ComFilterPeriodFactor;

   /* get the start of the occurrence values */
   occurrencebase =
       COM_GET_MEMPTR(ComFilterOneEveryNSizeType, Com_gConfigPtr->ComFilterOneEveryNBase);

   /* Enter critical section */
   Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

   /* get the value how often the signal occurred */
   occurrence = occurrencebase[ComFilterOneEveryNPtr->ComFilterOccurrence];

   /* Evaluate if the filter allows the value to pass */
   FilterResult = (occurrence == offset);
   /* increase occurrence and store its new value */
   occurrence++;
   occurrencebase[ComFilterOneEveryNPtr->ComFilterOccurrence] = (occurrence % period);

   /* Leave critical section */
   Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();


   DBG_COM_EB_FILTERONEEVERYN_EXIT(FilterResult,ComFilterRef);
   return FilterResult;
}

#endif /* (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON) */

#if (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON)
TS_MOD_PRIV_DEFN FUNC(boolean, COM_CODE) Com_EB_FilterBoolean
(
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
)
{
   boolean FilterResult = FALSE;
   uint8 NewVal = (uint8) * (P2CONST(boolean, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;

   DBG_COM_EB_FILTERBOOLEAN_ENTRY(ComFilterPropPtr,SignalDataPtr);

   switch (ComFilterPropPtr->ComFilterType)
   {
   case COM_F_MASK_NEW_DIFFERS_MASK_OLD:
   {
#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
      /* CHECK: NOPARSE */
      /* check if ComOldValueRef is valid */
      if (ComFilterPropPtr->ComOldValueRef == COM_SIGNAL_BUFFER_REF_INVALID)
      {
          COM_PRECONDITION_ASSERT(
                  (ComFilterPropPtr->ComOldValueRef != COM_SIGNAL_BUFFER_REF_INVALID),
                  COM_INTERNAL_API_ID);
      }
      else
      /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */
      {
         /* pointer to mask */
         /* Deviation MISRA-1, MISRA-2 <+6> */
         CONSTP2CONST(ComFilter8BitMaskType, AUTOMATIC, COM_APPL_CONST) maskPtr =
            COM_GET_CONFIG_ELEMENT(ComFilter8BitMaskType,
                                   Com_gConfigPtr->ComFilter8BitMaskRef,
                                   ComFilterPropPtr->ComFilterRef);
         uint8 mask = *maskPtr;
         /* pointer the old value */
            CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) bufferBaseBool =
               (P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT))
               & Com_gDataMemPtr[Com_gConfigPtr->ComBufferBaseBool];
            uint8 oldVal;
            TS_GetBit(&bufferBaseBool[(ComFilterPropPtr->ComOldValueRef / 8U)],
               ComFilterPropPtr->ComOldValueRef % 8U, uint8, oldVal);

         /* evaluate filter */
         FilterResult =
            ((( NewVal ^ ((uint8) oldVal)) &
              ((uint8) mask)) != 0);
      }
   }                      /* case COM_F_MASK_NEW_DIFFERS_MASK_OLD: */
   break;
#if (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON)
   case COM_F_ONE_EVERY_N:
   {
      FilterResult = Com_EB_FilterOneEveryN(ComFilterPropPtr->ComFilterRef);
   }                            /* case COM_F_ONE_EVERY_N: */
   break;
#endif /* (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON) */
      default:
         {
            /* Deviation MISRA-1, MISRA-2 <+7> */
            CONSTP2CONST(ComFilter8BitMaskXMinMaxType, AUTOMATIC,
                         COM_APPL_CONST) FilterPtr =
               COM_GET_CONFIG_ELEMENT(ComFilter8BitMaskXMinMaxType,
                                      Com_gConfigPtr->ComFilter8BitMaskXMinMaxRef,
                                      ComFilterPropPtr->ComFilterRef);
            uint8 maskOrMin = FilterPtr->ComFilterMaskOrMin;
            uint8 XOrMax = FilterPtr->ComFilterXOrMax;

            switch (ComFilterPropPtr->ComFilterType)
            {
            case COM_F_MASKED_NEW_EQUALS_X:
            {
               FilterResult =
                  (NewVal & (uint8) maskOrMin) ==
                  (uint8) XOrMax;
            }
            break;
            case COM_F_MASKED_NEW_DIFFERS_X:
            {
               FilterResult =
                  (NewVal & (uint8) maskOrMin) !=
                  (uint8) XOrMax;
            }
            break;
            /* CHECK: NOPARSE */
            default:
            {
               /* Should never be reached, FilterType is unknown */
                COM_UNREACHABLE_CODE_ASSERT(COM_INTERNAL_API_ID);
            }
            break;
            /* CHECK: PARSE */
            }
         }
         break;
   }                            /* end switch FilterType */

   /* Check if the value should be stored to the signal buffer */
   if ((FilterResult == TRUE) &&
       (ComFilterPropPtr->ComOldValueRef != COM_SIGNAL_BUFFER_REF_INVALID)
      )
   {
      CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) bufferBaseBool =
         (P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT))
         & Com_gDataMemPtr[Com_gConfigPtr->ComBufferBaseBool];
      if (NewVal == 1U)
      {
         TS_AtomicSetBit_8(&bufferBaseBool[(ComFilterPropPtr->ComOldValueRef / 8U)],
               ComFilterPropPtr->ComOldValueRef % 8U);
      }
      else
      {
         TS_AtomicClearBit_8(&bufferBaseBool[(ComFilterPropPtr->ComOldValueRef / 8U)],
               ComFilterPropPtr->ComOldValueRef % 8U);
      }
   }             /* if ((SaveResult == TRUE) && (ComOldValueRef != COM_SIGNAL_BUFFER_REF_INVALID)) */


   DBG_COM_EB_FILTERBOOLEAN_EXIT(FilterResult,ComFilterPropPtr,SignalDataPtr);
   return FilterResult;

}                               /* Com_EB_FilterBoolean */
#endif /* (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON) */

#if (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON)
TS_MOD_PRIV_DEFN FUNC(boolean, COM_CODE) Com_EB_FilterUint8
(
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
)
{
   boolean FilterResult = FALSE;
   uint8 NewVal = (uint8) * (P2CONST(uint8, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;

   DBG_COM_EB_FILTERUINT8_ENTRY(ComFilterPropPtr,SignalDataPtr);

   switch (ComFilterPropPtr->ComFilterType)
   {
   case COM_F_MASK_NEW_DIFFERS_MASK_OLD:
   {
#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
      /* CHECK: NOPARSE */
      /* check if ComOldValueRef is valid */
      if (ComFilterPropPtr->ComOldValueRef == COM_SIGNAL_BUFFER_REF_INVALID)
      {
          COM_PRECONDITION_ASSERT(
                  (ComFilterPropPtr->ComOldValueRef != COM_SIGNAL_BUFFER_REF_INVALID),
                  COM_INTERNAL_API_ID);
      }
      else
      /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */
      {
         /* pointer to mask */
         /* Deviation MISRA-1, MISRA-2 <+6> */
         CONSTP2CONST(ComFilter8BitMaskType, AUTOMATIC, COM_APPL_CONST) maskPtr =
            COM_GET_CONFIG_ELEMENT(ComFilter8BitMaskType,
                                   Com_gConfigPtr->ComFilter8BitMaskRef,
                                   ComFilterPropPtr->ComFilterRef);
         uint8 mask = *maskPtr;
         /* pointer the old value */
        CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) bufferBaseUint8 =
           (P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT))
           & Com_gDataMemPtr[Com_gConfigPtr->ComBufferBaseUInt8];
            uint8 oldVal;
            TS_AtomicAssign8(oldVal, (uint8) bufferBaseUint8[ComFilterPropPtr->ComOldValueRef]);
         /* evaluate filter */
         FilterResult =
            ((((uint8) NewVal ^ ((uint8) oldVal)) &
              ((uint8) mask)) != 0);
      }

   }                      /* case COM_F_MASK_NEW_DIFFERS_MASK_OLD: */
   break;
#if (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON)
   case COM_F_ONE_EVERY_N:
   {
      FilterResult = Com_EB_FilterOneEveryN(ComFilterPropPtr->ComFilterRef);
   }                            /* case COM_F_ONE_EVERY_N: */
   break;
#endif /* (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON) */
      default:
         {
            /* Deviation MISRA-1, MISRA-2 <+7> */
            CONSTP2CONST(ComFilter8BitMaskXMinMaxType, AUTOMATIC,
                         COM_APPL_CONST) FilterPtr =
               COM_GET_CONFIG_ELEMENT(ComFilter8BitMaskXMinMaxType,
                                      Com_gConfigPtr->ComFilter8BitMaskXMinMaxRef,
                                      ComFilterPropPtr->ComFilterRef);
            uint8 maskOrMin = FilterPtr->ComFilterMaskOrMin;
            uint8 XOrMax = FilterPtr->ComFilterXOrMax;

            switch (ComFilterPropPtr->ComFilterType)
            {
            case COM_F_MASKED_NEW_EQUALS_X:
            {
               FilterResult =
                  ((uint8) NewVal & (uint8) maskOrMin) ==
                  (uint8) XOrMax;
            }
            break;
            case COM_F_MASKED_NEW_DIFFERS_X:
            {
               FilterResult =
                  ((uint8) NewVal & (uint8) maskOrMin) !=
                  (uint8) XOrMax;
            }
            break;
            case COM_F_NEW_IS_WITHIN:
            {
              FilterResult = ((uint8) maskOrMin <= (uint8) NewVal)
                 && ((uint8) NewVal <= (uint8) XOrMax);
            }
            break;
            case COM_F_NEW_IS_OUTSIDE:
            {
               FilterResult = ((uint8) maskOrMin > (uint8) NewVal)
                  || ((uint8) NewVal > (uint8) XOrMax);
            }
            break;
            /* CHECK: NOPARSE */
            default:
            {
               /* Should never be reached, FilterType is unknown */
               COM_UNREACHABLE_CODE_ASSERT(COM_INTERNAL_API_ID);
            }
            break;
            /* CHECK: PARSE */
            }
         }
         break;
   }                            /* end switch FilterType */

   /* Check if the value should be stored to the signal buffer */
   if ((FilterResult == TRUE) &&
       (ComFilterPropPtr->ComOldValueRef != COM_SIGNAL_BUFFER_REF_INVALID)
      )
   {
      CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) bufferBaseUint8 =
         (P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT))
         & Com_gDataMemPtr[Com_gConfigPtr->ComBufferBaseUInt8];
      TS_AtomicAssign8(bufferBaseUint8[ComFilterPropPtr->ComOldValueRef], NewVal);

   }             /* if ((FilterResult == TRUE) && (ComOldValueRef != COM_SIGNAL_BUFFER_REF_INVALID)) */


   DBG_COM_EB_FILTERUINT8_EXIT(FilterResult,ComFilterPropPtr,SignalDataPtr);
   return FilterResult;

}                               /* Com_EB_FilterUint8 */
#endif /* (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON) */

#if (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON)
TS_MOD_PRIV_DEFN FUNC(boolean, COM_CODE) Com_EB_FilterSint8
(
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
)
{
   boolean FilterResult = FALSE;
   sint8 NewVal = (sint8) * (P2CONST(sint8, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;

   DBG_COM_EB_FILTERSINT8_ENTRY(ComFilterPropPtr,SignalDataPtr);

   switch (ComFilterPropPtr->ComFilterType)
   {
   case COM_F_MASK_NEW_DIFFERS_MASK_OLD:
   {
#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
      /* CHECK: NOPARSE */
      /* check if ComOldValueRef is valid */
      if (ComFilterPropPtr->ComOldValueRef == COM_SIGNAL_BUFFER_REF_INVALID)
      {
          COM_PRECONDITION_ASSERT(
                  (ComFilterPropPtr->ComOldValueRef != COM_SIGNAL_BUFFER_REF_INVALID),
                  COM_INTERNAL_API_ID);
      }
      else
      /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */
      {
         /* Deviation MISRA-1, MISRA-2 <+6> */
         CONSTP2CONST(ComFilter8BitMaskType, AUTOMATIC, COM_APPL_CONST) maskPtr =
            COM_GET_CONFIG_ELEMENT(ComFilter8BitMaskType,
                                   Com_gConfigPtr->ComFilter8BitMaskRef,
                                   ComFilterPropPtr->ComFilterRef);
         uint8 mask = *maskPtr;
         /* pointer the old value */
        CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) bufferBaseSint8 =
           (P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT))
           & Com_gDataMemPtr[Com_gConfigPtr->ComBufferBaseSInt8];
            sint8 oldVal;
            TS_AtomicAssign8(oldVal, (sint8) bufferBaseSint8[ComFilterPropPtr->ComOldValueRef]);
         /* evaluate filter */
         FilterResult =
            ((((uint8) NewVal ^ ((uint8) oldVal)) &
              ((uint8) mask)) != 0);
      }
   }                      /* case COM_F_MASK_NEW_DIFFERS_MASK_OLD: */
   break;
#if (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON)
   case COM_F_ONE_EVERY_N:
   {
      FilterResult = Com_EB_FilterOneEveryN(ComFilterPropPtr->ComFilterRef);
   }                            /* case COM_F_ONE_EVERY_N: */
   break;
#endif /* (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON) */
      default:
         {
            /* Deviation MISRA-1, MISRA-2 <+7> */
            CONSTP2CONST(ComFilter8BitMaskXMinMaxType, AUTOMATIC,
                         COM_APPL_CONST) FilterPtr =
               COM_GET_CONFIG_ELEMENT(ComFilter8BitMaskXMinMaxType,
                                      Com_gConfigPtr->ComFilter8BitMaskXMinMaxRef,
                                      ComFilterPropPtr->ComFilterRef);
            uint8 maskOrMin = FilterPtr->ComFilterMaskOrMin;
            uint8 XOrMax = FilterPtr->ComFilterXOrMax;

            switch (ComFilterPropPtr->ComFilterType)
            {
            case COM_F_MASKED_NEW_EQUALS_X:
            {
               FilterResult =
                  ((uint8) NewVal & (uint8) maskOrMin) ==
                  (uint8) XOrMax;
            }
            break;
            case COM_F_MASKED_NEW_DIFFERS_X:
            {
               FilterResult =
                  ((uint8) NewVal & (uint8) maskOrMin) !=
                  (uint8) XOrMax;
            }
            break;
            case COM_F_NEW_IS_WITHIN:
            {
              FilterResult = ((sint8) maskOrMin <= (sint8) NewVal)
                 && ((sint8) NewVal <= (sint8) XOrMax);
            }
            break;
            case COM_F_NEW_IS_OUTSIDE:
            {
               FilterResult = ((sint8) maskOrMin > (sint8) NewVal)
                  || ((sint8) NewVal > (sint8) XOrMax);
            }
            break;
            /* CHECK: NOPARSE */
            default:
            {
               /* Should never be reached, FilterType is unknown */
                COM_UNREACHABLE_CODE_ASSERT(COM_INTERNAL_API_ID);
            }
            break;
            /* CHECK: PARSE */
            }
         }
         break;
   }                            /* end switch FilterType */

   /* Check if the value should be stored to the signal buffer */
   if ((FilterResult == TRUE) &&
       (ComFilterPropPtr->ComOldValueRef != COM_SIGNAL_BUFFER_REF_INVALID)
      )
   {
      CONSTP2VAR(sint8, AUTOMATIC, COM_VAR_NOINIT) bufferBaseSint8 =
         (P2VAR(sint8, AUTOMATIC, COM_VAR_NOINIT))
         & Com_gDataMemPtr[Com_gConfigPtr->ComBufferBaseSInt8];
      TS_AtomicAssign8(bufferBaseSint8[ComFilterPropPtr->ComOldValueRef], NewVal);

   }             /* if ((FilterResult == TRUE) && (ComOldValueRef != COM_SIGNAL_BUFFER_REF_INVALID)) */


   DBG_COM_EB_FILTERSINT8_EXIT(FilterResult,ComFilterPropPtr,SignalDataPtr);
   return FilterResult;

}                               /* Com_EB_FilterSint8 */
#endif /* (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON) */

#if (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON)
TS_MOD_PRIV_DEFN FUNC(boolean, COM_CODE) Com_EB_FilterUint16
(
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
)
{
   boolean FilterResult = FALSE;
   uint16 NewVal = (uint16) * (P2CONST(uint16, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;

   DBG_COM_EB_FILTERUINT16_ENTRY(ComFilterPropPtr,SignalDataPtr);

   switch (ComFilterPropPtr->ComFilterType)
   {
   case COM_F_MASK_NEW_DIFFERS_MASK_OLD:
   {
#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
      /* CHECK: NOPARSE */
      /* check if ComOldValueRef is valid */
      if (ComFilterPropPtr->ComOldValueRef == COM_SIGNAL_BUFFER_REF_INVALID)
      {
          COM_PRECONDITION_ASSERT(
                  (ComFilterPropPtr->ComOldValueRef != COM_SIGNAL_BUFFER_REF_INVALID),
                  COM_INTERNAL_API_ID);
      }
      else
      /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */
      {
         /* pointer to mask */
         /* Deviation MISRA-1, MISRA-2 <+6> */
         CONSTP2CONST(ComFilter16BitMaskType, AUTOMATIC, COM_APPL_CONST) maskPtr =
            COM_GET_CONFIG_ELEMENT(ComFilter16BitMaskType,
                                   Com_gConfigPtr->ComFilter16BitMaskRef,
                                   ComFilterPropPtr->ComFilterRef);
         uint16 mask = *maskPtr;
         /* pointer the old value */
         CONSTP2VAR(uint16, AUTOMATIC, COM_VAR_NOINIT) bufferBaseUint16 =
             COM_GET_MEMPTR(uint16, Com_gConfigPtr->ComBufferBaseUInt16);
         uint16 oldVal;
         TS_AtomicAssign16(oldVal, (uint16) bufferBaseUint16[ComFilterPropPtr->ComOldValueRef]);
         /* evaluate filter */
         FilterResult =
            ((((uint16) NewVal ^ ((uint16) oldVal)) &
              ((uint16) mask)) != 0);
      }
   }                      /* case COM_F_MASK_NEW_DIFFERS_MASK_OLD: */
   break;
#if (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON)
   case COM_F_ONE_EVERY_N:
   {
      FilterResult = Com_EB_FilterOneEveryN(ComFilterPropPtr->ComFilterRef);
   }                            /* case COM_F_ONE_EVERY_N: */
   break;
#endif /* (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON) */
      default:
         {
            /* Deviation MISRA-1, MISRA-2 <+7> */
            CONSTP2CONST(ComFilter16BitMaskXMinMaxType, AUTOMATIC,
                         COM_APPL_CONST) FilterPtr =
               COM_GET_CONFIG_ELEMENT(ComFilter16BitMaskXMinMaxType,
                                      Com_gConfigPtr->ComFilter16BitMaskXMinMaxRef,
                                      ComFilterPropPtr->ComFilterRef);
            uint16 maskOrMin = FilterPtr->ComFilterMaskOrMin;
            uint16 XOrMax = FilterPtr->ComFilterXOrMax;

            switch (ComFilterPropPtr->ComFilterType)
            {
            case COM_F_MASKED_NEW_EQUALS_X:
            {
               FilterResult =
                  ((uint16) NewVal & (uint16) maskOrMin) ==
                  (uint16) XOrMax;
            }
            break;
            case COM_F_MASKED_NEW_DIFFERS_X:
            {
               FilterResult =
                  ((uint16) NewVal & (uint16) maskOrMin) !=
                  (uint16) XOrMax;
            }
            break;
            case COM_F_NEW_IS_WITHIN:
            {
              FilterResult = ((uint16) maskOrMin <= (uint16) NewVal)
                 && ((uint16) NewVal <= (uint16) XOrMax);
            }
            break;
            case COM_F_NEW_IS_OUTSIDE:
            {
               FilterResult = ((uint16) maskOrMin > (uint16) NewVal)
                  || ((uint16) NewVal > (uint16) XOrMax);
            }
            break;
            /* CHECK: NOPARSE */
            default:
            {
               /* Should never be reached, FilterType is unknown */
               COM_UNREACHABLE_CODE_ASSERT(COM_INTERNAL_API_ID);
            }
            break;
            /* CHECK: PARSE */
            }
         }
         break;
   }                            /* end switch FilterType */

   /* Check if the value should be stored to the signal buffer */
   if ((FilterResult == TRUE) &&
       (ComFilterPropPtr->ComOldValueRef != COM_SIGNAL_BUFFER_REF_INVALID)
      )
   {
      CONSTP2VAR(uint16, AUTOMATIC, COM_VAR_NOINIT) bufferBaseUint16 =
          COM_GET_MEMPTR(uint16, Com_gConfigPtr->ComBufferBaseUInt16);
      TS_AtomicAssign16(bufferBaseUint16[ComFilterPropPtr->ComOldValueRef], NewVal);

   }             /* if ((FilterResult == TRUE) && (ComOldValueRef != COM_SIGNAL_BUFFER_REF_INVALID)) */


   DBG_COM_EB_FILTERUINT16_EXIT(FilterResult,ComFilterPropPtr,SignalDataPtr);
   return FilterResult;

}                               /* Com_EB_FilterUint16 */
#endif /* (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON) */

#if (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON)
TS_MOD_PRIV_DEFN FUNC(boolean, COM_CODE) Com_EB_FilterSint16
(
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
)
{
   boolean FilterResult = FALSE;
   sint16 NewVal = (sint16) * (P2CONST(sint16, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;

   DBG_COM_EB_FILTERSINT16_ENTRY(ComFilterPropPtr,SignalDataPtr);

   switch (ComFilterPropPtr->ComFilterType)
   {
   case COM_F_MASK_NEW_DIFFERS_MASK_OLD:
   {
#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
      /* CHECK: NOPARSE */
      /* check if ComOldValueRef is valid */
      if (ComFilterPropPtr->ComOldValueRef == COM_SIGNAL_BUFFER_REF_INVALID)
      {
          COM_PRECONDITION_ASSERT(
                  (ComFilterPropPtr->ComOldValueRef != COM_SIGNAL_BUFFER_REF_INVALID),
                  COM_INTERNAL_API_ID);
      }
      else
      /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */
      {
         /* pointer to mask */
         /* Deviation MISRA-1, MISRA-2 <+6> */
         CONSTP2CONST(ComFilter16BitMaskType, AUTOMATIC, COM_APPL_CONST) maskPtr =
            COM_GET_CONFIG_ELEMENT(ComFilter16BitMaskType,
                                   Com_gConfigPtr->ComFilter16BitMaskRef,
                                   ComFilterPropPtr->ComFilterRef);
         uint16 mask = *maskPtr;
         /* pointer the old value */
         CONSTP2VAR(uint16, AUTOMATIC, COM_VAR_NOINIT) bufferBaseSint16 =
             COM_GET_MEMPTR(uint16, Com_gConfigPtr->ComBufferBaseSInt16);
         sint16 oldVal;
         TS_AtomicAssign16(oldVal, (sint16) bufferBaseSint16[ComFilterPropPtr->ComOldValueRef]);
         /* evaluate filter */
         FilterResult =
            ((((uint16) NewVal ^ ((uint16) oldVal)) &
              ((uint16) mask)) != 0);
      }
   }                      /* case COM_F_MASK_NEW_DIFFERS_MASK_OLD: */
   break;
#if (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON)
   case COM_F_ONE_EVERY_N:
   {
      FilterResult = Com_EB_FilterOneEveryN(ComFilterPropPtr->ComFilterRef);
   }                            /* case COM_F_ONE_EVERY_N: */
   break;
#endif /* (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON) */
      default:
         {
            /* Deviation MISRA-1, MISRA-2 <+7> */
            CONSTP2CONST(ComFilter16BitMaskXMinMaxType, AUTOMATIC,
                         COM_APPL_CONST) FilterPtr =
               COM_GET_CONFIG_ELEMENT(ComFilter16BitMaskXMinMaxType,
                                      Com_gConfigPtr->ComFilter16BitMaskXMinMaxRef,
                                      ComFilterPropPtr->ComFilterRef);
            uint16 maskOrMin = FilterPtr->ComFilterMaskOrMin;
            uint16 XOrMax = FilterPtr->ComFilterXOrMax;

            switch (ComFilterPropPtr->ComFilterType)
            {
            case COM_F_MASKED_NEW_EQUALS_X:
            {
               FilterResult =
                  ((uint16) NewVal & (uint16) maskOrMin) ==
                  (uint16) XOrMax;
            }
            break;
            case COM_F_MASKED_NEW_DIFFERS_X:
            {
               FilterResult =
                  ((uint16) NewVal & (uint16) maskOrMin) !=
                  (uint16) XOrMax;
            }
            break;
            case COM_F_NEW_IS_WITHIN:
            {
              FilterResult = ((sint16) maskOrMin <= (sint16) NewVal)
                 && ((sint16) NewVal <= (sint16) XOrMax);
            }
            break;
            case COM_F_NEW_IS_OUTSIDE:
            {
               FilterResult = ((sint16) maskOrMin > (sint16) NewVal)
                  || ((sint16) NewVal > (sint16) XOrMax);
            }
            break;
            /* CHECK: NOPARSE */
            default:
            {
               /* Should never be reached, FilterType is unknown */
               COM_UNREACHABLE_CODE_ASSERT(COM_INTERNAL_API_ID);
            }
            break;
            /* CHECK: PARSE */
            }
         }
         break;
   }                            /* end switch FilterType */

   /* Check if the value should be stored to the signal buffer */
   if ((FilterResult == TRUE) &&
       (ComFilterPropPtr->ComOldValueRef != COM_SIGNAL_BUFFER_REF_INVALID)
      )
   {
      CONSTP2VAR(sint16, AUTOMATIC, COM_VAR_NOINIT) bufferBaseSint16 =
          COM_GET_MEMPTR(sint16, Com_gConfigPtr->ComBufferBaseSInt16);
      TS_AtomicAssign16(bufferBaseSint16[ComFilterPropPtr->ComOldValueRef], NewVal);

   }             /* if ((FilterResult == TRUE) && (ComOldValueRef != COM_SIGNAL_BUFFER_REF_INVALID)) */


   DBG_COM_EB_FILTERSINT16_EXIT(FilterResult,ComFilterPropPtr,SignalDataPtr);
   return FilterResult;

}                               /* Com_EB_FilterSint16 */
#endif /* (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON) */

#if (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON)
TS_MOD_PRIV_DEFN FUNC(boolean, COM_CODE) Com_EB_FilterUint32
(
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
)
{
   boolean FilterResult = FALSE;
   uint32 NewVal = (uint32) * (P2CONST(uint32, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;

   DBG_COM_EB_FILTERUINT32_ENTRY(ComFilterPropPtr,SignalDataPtr);

   switch (ComFilterPropPtr->ComFilterType)
   {
   case COM_F_MASK_NEW_DIFFERS_MASK_OLD:
   {
#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
      /* CHECK: NOPARSE */
      /* check if ComOldValueRef is valid */
      if (ComFilterPropPtr->ComOldValueRef == COM_SIGNAL_BUFFER_REF_INVALID)
      {
          COM_PRECONDITION_ASSERT(
                  (ComFilterPropPtr->ComOldValueRef != COM_SIGNAL_BUFFER_REF_INVALID),
                  COM_INTERNAL_API_ID);
      }
      else
      /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */
      {
         /* pointer to mask */
         /* Deviation MISRA-1, MISRA-2 <+6> */
         CONSTP2CONST(ComFilter32BitMaskType, AUTOMATIC, COM_APPL_CONST) maskPtr =
            COM_GET_CONFIG_ELEMENT(ComFilter32BitMaskType,
                                   Com_gConfigPtr->ComFilter32BitMaskRef,
                                   ComFilterPropPtr->ComFilterRef);
         uint32 mask = *maskPtr;
         /* pointer the old value */
         CONSTP2VAR(uint32, AUTOMATIC, COM_VAR_NOINIT) bufferBaseUint32 =
             COM_GET_MEMPTR(uint32, Com_gConfigPtr->ComBufferBaseUInt32);
         uint32 oldVal;
         TS_AtomicAssign32(oldVal, (uint32) bufferBaseUint32[ComFilterPropPtr->ComOldValueRef]);
         /* evaluate filter */
         FilterResult =
            ((((uint32) NewVal ^ ((uint32) oldVal)) &
              ((uint32) mask)) != 0);
      }
   }                      /* case COM_F_MASK_NEW_DIFFERS_MASK_OLD: */
   break;
#if (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON)
   case COM_F_ONE_EVERY_N:
   {
      FilterResult = Com_EB_FilterOneEveryN(ComFilterPropPtr->ComFilterRef);
   }                            /* case COM_F_ONE_EVERY_N: */
   break;
#endif /* (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON) */
      default:
         {
            /* Deviation MISRA-1, MISRA-2 <+7> */
            CONSTP2CONST(ComFilter32BitMaskXMinMaxType, AUTOMATIC,
                         COM_APPL_CONST) FilterPtr =
               COM_GET_CONFIG_ELEMENT(ComFilter32BitMaskXMinMaxType,
                                      Com_gConfigPtr->ComFilter32BitMaskXMinMaxRef,
                                      ComFilterPropPtr->ComFilterRef);
            uint32 maskOrMin = FilterPtr->ComFilterMaskOrMin;
            uint32 XOrMax = FilterPtr->ComFilterXOrMax;

            switch (ComFilterPropPtr->ComFilterType)
            {
            case COM_F_MASKED_NEW_EQUALS_X:
            {
               FilterResult =
                  ((uint32) NewVal & (uint32) maskOrMin) ==
                  (uint32) XOrMax;
            }
            break;
            case COM_F_MASKED_NEW_DIFFERS_X:
            {
               FilterResult =
                  ((uint32) NewVal & (uint32) maskOrMin) !=
                  (uint32) XOrMax;
            }
            break;
            case COM_F_NEW_IS_WITHIN:
            {
              FilterResult = ((uint32) maskOrMin <= (uint32) NewVal)
                 && ((uint32) NewVal <= (uint32) XOrMax);
            }
            break;
            case COM_F_NEW_IS_OUTSIDE:
            {
               FilterResult = ((uint32) maskOrMin > (uint32) NewVal)
                  || ((uint32) NewVal > (uint32) XOrMax);
            }
            break;
            /* CHECK: NOPARSE */
            default:
            {
               /* Should never be reached, FilterType is unknown */
               COM_UNREACHABLE_CODE_ASSERT(COM_INTERNAL_API_ID);
            }
            break;
            /* CHECK: PARSE */
            }
         }
         break;
   }                            /* end switch FilterType */

   /* Check if the value should be stored to the signal buffer */
   if ((FilterResult == TRUE) &&
       (ComFilterPropPtr->ComOldValueRef != COM_SIGNAL_BUFFER_REF_INVALID)
      )
   {
      CONSTP2VAR(uint32, AUTOMATIC, COM_VAR_NOINIT) bufferBaseUint32 =
          COM_GET_MEMPTR(uint32, Com_gConfigPtr->ComBufferBaseUInt32);
      TS_AtomicAssign32(bufferBaseUint32[ComFilterPropPtr->ComOldValueRef], NewVal);

   }             /* if ((FilterResult == TRUE) && (ComOldValueRef != COM_SIGNAL_BUFFER_REF_INVALID)) */


   DBG_COM_EB_FILTERUINT32_EXIT(FilterResult,ComFilterPropPtr,SignalDataPtr);
   return FilterResult;

}                               /* Com_EB_FilterUint32 */
#endif /* (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON)
TS_MOD_PRIV_DEFN FUNC(boolean, COM_CODE) Com_EB_FilterSint32
(
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
)
{
   boolean FilterResult = FALSE;
   sint32 NewVal = (sint32) * (P2CONST(sint32, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;

   DBG_COM_EB_FILTERSINT32_ENTRY(ComFilterPropPtr,SignalDataPtr);

   switch (ComFilterPropPtr->ComFilterType)
   {
   case COM_F_MASK_NEW_DIFFERS_MASK_OLD:
   {
#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
      /* CHECK: NOPARSE */
      /* check if ComOldValueRef is valid */
      if (ComFilterPropPtr->ComOldValueRef == COM_SIGNAL_BUFFER_REF_INVALID)
      {
          COM_PRECONDITION_ASSERT(
                  (ComFilterPropPtr->ComOldValueRef != COM_SIGNAL_BUFFER_REF_INVALID),
                  COM_INTERNAL_API_ID);
      }
      else
      /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */
      {
         /* pointer to mask */
         /* Deviation MISRA-1, MISRA-2 <+6> */
         CONSTP2CONST(ComFilter32BitMaskType, AUTOMATIC, COM_APPL_CONST) maskPtr =
            COM_GET_CONFIG_ELEMENT(ComFilter32BitMaskType,
                                   Com_gConfigPtr->ComFilter32BitMaskRef,
                                   ComFilterPropPtr->ComFilterRef);
         uint32 mask = *maskPtr;
         /* pointer the old value */
         CONSTP2VAR(uint32, AUTOMATIC, COM_VAR_NOINIT) bufferBaseSint32 =
             COM_GET_MEMPTR(uint32, Com_gConfigPtr->ComBufferBaseSInt32);
         sint32 oldVal;
         TS_AtomicAssign32(oldVal, (sint32) bufferBaseSint32[ComFilterPropPtr->ComOldValueRef]);
         /* evaluate filter */
         FilterResult =
            ((((uint32) NewVal ^ ((uint32) oldVal)) &
              ((uint32) mask)) != 0);
      }
   }                      /* case COM_F_MASK_NEW_DIFFERS_MASK_OLD: */
   break;
#if (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON)
   case COM_F_ONE_EVERY_N:
   {
      FilterResult = Com_EB_FilterOneEveryN(ComFilterPropPtr->ComFilterRef);
   }                            /* case COM_F_ONE_EVERY_N: */
   break;
#endif /* (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON) */
      default:
         {
            /* Deviation MISRA-1, MISRA-2 <+7> */
            CONSTP2CONST(ComFilter32BitMaskXMinMaxType, AUTOMATIC,
                         COM_APPL_CONST) FilterPtr =
               COM_GET_CONFIG_ELEMENT(ComFilter32BitMaskXMinMaxType,
                                      Com_gConfigPtr->ComFilter32BitMaskXMinMaxRef,
                                      ComFilterPropPtr->ComFilterRef);
            uint32 maskOrMin = FilterPtr->ComFilterMaskOrMin;
            uint32 XOrMax = FilterPtr->ComFilterXOrMax;

            switch (ComFilterPropPtr->ComFilterType)
            {
            case COM_F_MASKED_NEW_EQUALS_X:
            {
               FilterResult =
                  ((uint32) NewVal & (uint32) maskOrMin) ==
                  (uint32) XOrMax;
            }
            break;
            case COM_F_MASKED_NEW_DIFFERS_X:
            {
               FilterResult =
                  ((uint32) NewVal & (uint32) maskOrMin) !=
                  (uint32) XOrMax;
            }
            break;
            case COM_F_NEW_IS_WITHIN:
            {
              FilterResult = ((sint32) maskOrMin <= (sint32) NewVal)
                 && ((sint32) NewVal <= (sint32) XOrMax);
            }
            break;
            case COM_F_NEW_IS_OUTSIDE:
            {
               FilterResult = ((sint32) maskOrMin > (sint32) NewVal)
                  || ((sint32) NewVal > (sint32) XOrMax);
            }
            break;
            /* CHECK: NOPARSE */
            default:
            {
               /* Should never be reached, FilterType is unknown */
               COM_UNREACHABLE_CODE_ASSERT(COM_INTERNAL_API_ID);
            }
            break;
            /* CHECK: PARSE */
            }
         }
         break;
   }                            /* end switch FilterType */

   /* Check if the value should be stored to the signal buffer */
   if ((FilterResult == TRUE) &&
       (ComFilterPropPtr->ComOldValueRef != COM_SIGNAL_BUFFER_REF_INVALID)
      )
   {
      CONSTP2VAR(sint32, AUTOMATIC, COM_VAR_NOINIT) bufferBaseSint32 =
          COM_GET_MEMPTR(sint32, Com_gConfigPtr->ComBufferBaseSInt32);
      TS_AtomicAssign32(bufferBaseSint32[ComFilterPropPtr->ComOldValueRef], NewVal);

   }             /* if ((FilterResult == TRUE) && (ComOldValueRef != COM_SIGNAL_BUFFER_REF_INVALID)) */


   DBG_COM_EB_FILTERSINT32_EXIT(FilterResult,ComFilterPropPtr,SignalDataPtr);
   return FilterResult;

}                               /* Com_EB_FilterTxSin32 */
#endif /* (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON) */


/** \brief Com_EB_CreateFilterProp - initializes the internal
 * structure for the representation of filter
 * \param[out] ComFilterPropPtr - pointer where the result shall be stored
 * \param[in] ComOldValueRef - reference to buffer of filter
 * \param[in] ComFilterRef - reference to filter configuration
 * \param[in] ComFilterType - type of the filter
 * \retval None
 */
TS_MOD_PRIV_DEFN FUNC(void, COM_CODE) Com_EB_CreateFilterProp
(
   P2VAR(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr,
   ComSignalBufferRefType ComOldValueRef,
   ComFilterRefType ComFilterRef,
   uint8 ComFilterType
)
{

   ComFilterPropPtr->ComOldValueRef = ComOldValueRef;
   ComFilterPropPtr->ComFilterRef = ComFilterRef;
   ComFilterPropPtr->ComFilterType = ComFilterType;

   return;

}                               /* Com_EB_CreateFilterProp */


#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_STOP_SEC_CODE
#include <MemMap.h>
#endif

#endif /* (COM_FILTER_AVAILABLE == STD_ON) */

/*==================[end of file]============================================*/

