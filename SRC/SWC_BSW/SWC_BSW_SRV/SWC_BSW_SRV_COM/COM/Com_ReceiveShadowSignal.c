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
 * MISRA-1) Deviated Rule: 11.3 (advisory)
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
 *
 * MISRA-3) Deviated Rule: 16.7 (advisory)
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
 */

/*==================[inclusions]=============================================*/

#include <Com_Trace.h>
#include <TSAutosar.h>          /* EB specific standard types */
#include <ComStack_Types.h>     /* AUTOSAR standard types */
#include <Com_Api_Static.h>     /* module public static API */
#include <Com_Priv.h>           /* module internal stuff */
#include <TSMem.h>              /* TS_MemCpy */

#if (COM_DEV_ERROR_DETECT == STD_ON)
#include <Det.h>                /* Det API */
#endif

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_START_SEC_CODE
#include <MemMap.h>
#endif

FUNC(void, COM_CODE) Com_ReceiveShadowSignal
(
   Com_SignalIdType SignalId,
   /* Deviation MISRA-3 */
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
)
{

#if (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)

   /* pointer to the configuration of the signal */
   P2CONST(ComRxGroupSignalType, AUTOMATIC, COM_APPL_CONST) GSignalPtr;

   /* pointer to the configuration of the Signal Group to which the group signal belongs */
   P2CONST(ComRxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr;
   ComSignalGroupRefType SignalGId;     /* Id of the Signal Group to which the the group signal belongs */

   Com_TS_SignalTypeType SignalType;    /* signal type of the signal */

   DBG_COM_RECEIVESHADOWSIGNAL_ENTRY(SignalId,SignalDataPtr);

#if (COM_DEV_ERROR_DETECT == STD_ON)

   /* check whether Com is initialized */
   if (Com_InitStatus == COM_EB_UNINIT)
   {
      COM_DET_REPORTERROR(COM_E_UNINIT, COMServiceId_ReceiveShadowSignal);
   }
   /* check SignalDataPtr */
   else if (SignalDataPtr == NULL_PTR)
   {
      COM_DET_REPORTERROR(COM_E_PARAM_POINTER, COMServiceId_ReceiveShadowSignal);
   }
   /* Check if the SignalId is within the range of the ComRxGroupSignalArraySize */
   else if (Com_gConfigPtr->ComRxGroupSignalArraySize <= SignalId)
   {
      COM_DET_REPORTERROR(COM_E_PARAM, COMServiceId_ReceiveShadowSignal);
   }
   else
      /* The check whether the signal is a Rx signal or not is done below with the check of the
       * configuration of the signal */

#endif /* (COM_DEV_ERROR_DETECT == STD_ON) */

   {
      /* get the configuration of the signal identified by the signal Id and check the
       * configuration */
      /* Deviation MISRA-1 */
      /* Deviation MISRA-2 */
      GSignalPtr = COM_GET_CONFIG_ELEMENT(ComRxGroupSignalType,
            Com_gConfigPtr->ComRxGroupSignalRef,
            SignalId
      );

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
      /* CHECK: NOPARSE */
      if (GSignalPtr->ComConfigCheckData != COM_CONFIG_CHECK_RX_GROUP_SIG)
      {
         COM_PRECONDITION_ASSERT(
               (GSignalPtr->ComConfigCheckData == COM_CONFIG_CHECK_RX_GROUP_SIG),
               COMServiceId_ReceiveShadowSignal);
      }
      else
         /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */

      {
         /* get the Signal Group Id to which the group signal belongs */
         SignalGId = GSignalPtr->ComSignalGroupRef;

         /* get Signal Group to which the the group signal belongs and check if the
          * Signal Group is valid */
         /* Deviation MISRA-1 */
         /* Deviation MISRA-2 */
         SignalGPtr = COM_GET_CONFIG_ELEMENT(ComRxSignalGroupType,
               Com_gConfigPtr->ComRxSignalGroupRef,
               SignalGId
         );

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
         /* CHECK: NOPARSE */
         if (NULL_PTR == SignalGPtr)
         {
            COM_PRECONDITION_ASSERT(
                  (NULL_PTR == SignalGPtr),
                  COMServiceId_ReceiveShadowSignal);
         }
         else if (SignalGPtr->ComConfigCheckData != COM_CONFIG_CHECK_RX_SIG_GROUP)
         {
            COM_PRECONDITION_ASSERT(
                  (SignalGPtr->ComConfigCheckData == COM_CONFIG_CHECK_RX_SIG_GROUP),
                  COMServiceId_ReceiveShadowSignal);
         }
         else
            /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */
         {

#if (COM_DEV_ERROR_DETECT == STD_ON)
#if (COM_BASED_TRANSFORMER_SUPPORT_RX == STD_ON)
            if (SignalGPtr->ComSignalGroupValueRef == COM_RAM_SIZE_MAX)
            {
               /* the signal group has no shadow buffer assigned an shall
                * only be used with the Com_ReceiveSignalGroupArray() */
               COM_DET_REPORTERROR(COM_E_PARAM, COMServiceId_ReceiveShadowSignal);
            }
            else
#endif /* (COM_BASED_TRANSFORMER_SUPPORT_RX == STD_ON) */
#endif /* (COM_DEV_ERROR_DETECT == STD_ON) */
            {

               /* get the type of the signal */
               SignalType = COM_GET_RX_GROUP_SIGNAL_SIGNAL_TYPE(GSignalPtr);


#if (COM_SIGNAL_TYPE_UINT8_N_ENABLE == STD_ON)
               if (SignalType != COM_UINT8_N)
#endif /* (COM_SIGNAL_TYPE_UINT8_N_ENABLE == STD_ON) */
               {

                  ComCommonReadPropType ComReadProp;

                  ComReadProp.pdudataptrRAM =
                        &Com_gDataMemPtr[(SignalGPtr->ComSignalGroupValueRef)];
#if (COM_SIGNAL_INIT_VALUE_ENABLE == STD_ON)
                  /* if value shall be replaced with initial value,
                   * the shadow buffer is already updated accordingly,
                   * no replace during reading of group signal required. */
                  ComReadProp.pdudataptrROM = COM_CONST_NULL_PTR;
#endif /* (COM_SIGNAL_INIT_VALUE_ENABLE == STD_ON) */

#if (COM_SIGNAL_BYTE_ALIGN == STD_ON)
                  ComReadProp.ComSignalPositionInByte = GSignalPtr->ComSignalPositionInByte;
#elif (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
                  ComReadProp.ComSignalPositionInBit = GSignalPtr->ComSignalPositionInBit;
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_ON) */

                  ComReadProp.ComBitSize= GSignalPtr->ComBitSize;
#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
                  ComReadProp.Endianness = COM_GET_RX_GROUP_SIGNAL_ENDIANNESS(GSignalPtr);
#endif /* (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE) */
                  ComReadProp.SignalType = SignalType;
#if (COM_VALUE_INIT_REPLACE == STD_ON)
                  /* if value shall be replaced with initial value,
                   * the shadow buffer is already updated accordingly,
                   * no replace during reading of group signal required. */
                  ComReadProp.TakePtrROM = FALSE;
#endif /* (COM_VALUE_INIT_REPLACE == STD_ON) */

                  {
                     /* get value from signal group shadow buffer value */
                     const uint32 value = Com_EB_ReadFromPduOrShadowBuffer(&ComReadProp);

                     /* write value to the data pointer of the upper layer */
                     Com_EB_WriteToUpperLayer(value, SignalDataPtr, SignalType);
                  }
               }
#if (COM_SIGNAL_TYPE_UINT8_N_ENABLE == STD_ON)
               else
               {                            /* signal has type UINT8_N */

                  /* Starting position of the group signals in bits divided by 8
                   * NOTE: this assumes that signals of type UINT8_N are always byte aligned */
                  ComSignalDescBitType const startbyte  =
#if (COM_SIGNAL_BYTE_ALIGN == STD_ON)
                        GSignalPtr->ComSignalPositionInByte;
#elif (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
                  GSignalPtr->ComSignalPositionInBit;
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_ON) */

                  /* get the first byte of the UINT8_N signal in the shadow buffer */
                  CONSTP2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) startbyteShadowBuffer =
                        &Com_gDataMemPtr[SignalGPtr->ComSignalGroupValueRef + startbyte];

                  /* copy value from PDU buffer to upper layer buffer */
                  TS_MemCpy(SignalDataPtr,
                     startbyteShadowBuffer,
                     GSignalPtr->ComBitSize);
               }
#endif /* (COM_SIGNAL_TYPE_UINT8_N_ENABLE == STD_ON) */
            }
         }
      }
   }

#else

   DBG_COM_RECEIVESHADOWSIGNAL_ENTRY(SignalId,SignalDataPtr);

   TS_PARAM_UNUSED(SignalId);
   TS_PARAM_UNUSED(SignalDataPtr);
#if (COM_DEV_ERROR_DETECT == STD_ON)
   COM_DET_REPORTERROR(COM_E_PARAM, COMServiceId_ReceiveShadowSignal);
#endif /* (COM_DEV_ERROR_DETECT == STD_ON) */

#endif /* (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

   DBG_COM_RECEIVESHADOWSIGNAL_EXIT(SignalId,SignalDataPtr);
}

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_STOP_SEC_CODE
#include <MemMap.h>
#endif

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/

