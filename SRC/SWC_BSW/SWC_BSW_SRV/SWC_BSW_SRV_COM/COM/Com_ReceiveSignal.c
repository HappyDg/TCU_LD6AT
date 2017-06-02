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
#include <Com_Defs.h>           /* COM_SERVICE_NOT_AVAILABLE */
#include <TSMem.h>              /* TS_MemCpy */
#include <Com_Filter.h>         /* Filter functions */
#include <Com_Core_RxIPdu.h>    /* RxIPdu functions */

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



#if (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON)

/** \brief Com_EB_ReadValue_Boolean - reads the value of an Boolean signal
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] SignalDataPtr - pointer where value shall be copied
 * \param[in] ComReadPropPtr - properties of the signal which shall be read
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_ReadValue_Boolean
(
    /* Deviation MISRA-3 */
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
);

#endif /* (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON)

/** \brief Com_EB_ReadValue_Uint8 - reads the value of an Uint8 signal
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] SignalDataPtr - pointer where value shall be copied
 * \param[in] ComReadPropPtr - properties of the signal which shall be read
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_ReadValue_Uint8
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
);

#endif /* (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON)

/** \brief Com_EB_ReadValue_Uint16 - reads the value of an Uint16 signal
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] SignalDataPtr - pointer where value shall be copied
 * \param[in] ComReadPropPtr - properties of the signal which shall be read
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_ReadValue_Uint16
(
    /* Deviation MISRA-3 */
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
);

#endif /* (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON)

/** \brief Com_EB_ReadValue_Uint32 - reads the value of an Uint32 signal
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] SignalDataPtr - pointer where value shall be copied
 * \param[in] ComReadPropPtr - properties of the signal which shall be read
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_ReadValue_Uint32
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
);
#endif /* (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON)

/** \brief Com_EB_ReadValue_Sint8 - reads the value of an Sint8 signal
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] SignalDataPtr - pointer where value shall be copied
 * \param[in] ComReadPropPtr - properties of the signal which shall be read
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_ReadValue_Sint8
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
);

#endif /* (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON) */

#if (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON)

/** \brief Com_EB_ReadValue_Sint16 - reads the value of an Sint16 signal
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] SignalDataPtr - pointer where value shall be copied
 * \param[in] ComReadPropPtr - properties of the signal which shall be read
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_ReadValue_Sint16
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
);

#endif /* (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON)

/** \brief Com_EB_ReadValue_Sint32 - reads the value of an Sint32 signal
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] SignalDataPtr - pointer where value shall be copied
 * \param[in] ComReadPropPtr - properties of the signal which shall be read
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_ReadValue_Sint32
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
);

#endif /* (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_UINT8_N_ENABLE == STD_ON)
/** \brief Com_EB_ReadValue_Uint8N - reads the value of an Uint8N signal
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] SignalDataPtr - pointer where value shall be copied
 * \param[in] ComReadPropPtr - properties of the signal which shall be read
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_ReadValue_Uint8N
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
);
#endif /* (COM_SIGNAL_TYPE_UINT8_N_ENABLE == STD_ON) */

/** \brief Com_EB_ReadValue - reads the value of a signal
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] SignalDataPtr - pointer where value shall be copied
 * \param[in] ComReadPropPtr - properties of the signal which shall be read
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_ReadValue
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
);


#if (COM_RX_DATA_TOUT_ACTION != COM_RX_DATA_TOUT_ACTION_NONE)

/** \brief Com_EB_CheckRxSignalDM - Checks if the value of the signal shall be
 * replaced with the init value
 * this function checks if the DM (I-Pdu based or signal based) of the signal
 * timed out and the value of the signal shall be replaced.
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] SignalPtr - pointer to the description of the signal
 * \param[in] PduId - Id of the I-Pdu to which the signal belongs to
 * \retval TRUE if the value has to be replace, otherwise FALSE
 */

_COM_STATIC_ FUNC(boolean, COM_CODE) Com_EB_CheckRxSignalDM
(
#if ((COM_RX_SIGNAL_BASED_DM == STD_ON) || \
      (COM_RX_DATA_TOUT_ACTION == COM_RX_DATA_TOUT_ACTION_CONFIG))
   P2CONST(ComRxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr
#if (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_PRESENT_FOR_ALL)
   ,
#endif /* (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_PRESENT_FOR_ALL) */
#endif /* ((COM_RX_SIGNAL_BASED_DM == STD_ON) || \
      (COM_RX_DATA_TOUT_ACTION == COM_RX_DATA_TOUT_ACTION_CONFIG)) */
#if (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_PRESENT_FOR_ALL)
   ComIPduRefType PduId
#endif /* (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_PRESENT_FOR_ALL) */
);

#endif /* (COM_RX_DATA_TOUT_ACTION != COM_RX_DATA_TOUT_ACTION_NONE) */


#if (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON)

/** \brief Com_EB_ReadValue_Boolean - reads the value of an Boolean signal
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] SignalDataPtr - pointer where value shall be copied
 * \param[in] ComReadPropPtr - properties of the signal which shall be read
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_ReadValue_Boolean
(
    /* Deviation MISRA-3 */
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
)
{
   P2VAR (boolean, AUTOMATIC, COM_APPL_DATA) dataPtr =
         (P2VAR (boolean, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr;

   /* Position in bit for Boolean signals */
   ComSignalDescBitType  const ComSignalPosition =
#if (COM_SIGNAL_BYTE_ALIGN == STD_ON)
         ComReadPropPtr->ComSignalPositionInByte;
#elif (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
   ComReadPropPtr->ComSignalPositionInBit;
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_ON) */

   DBG_COM_EB_READVALUE_BOOLEAN_ENTRY(SignalDataPtr,SignalDataPtr);

#if (COM_VALUE_INIT_REPLACE == STD_ON)
   if (ComReadPropPtr->TakePtrROM == TRUE)
   {

#if (COM_SIGNAL_INIT_VALUE_ENABLE == STD_ON)
      /* Deviation MISRA-1 */
      /* Deviation MISRA-2 */
      CONSTP2CONST(uint8, AUTOMATIC, COM_APPL_CONST) PduInit =
            ComReadPropPtr->pdudataptrROM;
#endif /* (COM_SIGNAL_INIT_VALUE_ENABLE == STD_ON) */

      /* init value shall be returned */
      *dataPtr = ((COM_GET_INIT_VALUE_BYTE(PduInit[ComSignalPosition / 8U])
            & (uint8) (1U << (ComSignalPosition % 8U))) != 0U)
            ? 1U : 0U;

   }
   else
#endif /* (COM_VALUE_INIT_REPLACE == STD_ON)*/
   {
#if (COM_FILTER_RECEIVER_ENABLE == STD_ON)
      if (ComReadPropPtr->ComFilterSignalValueRef != COM_SIGNAL_BUFFER_REF_INVALID)
      {
         /* the signal has a buffer, read the value */
         CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) bufferBaseBool =
               (P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT))
               & Com_gDataMemPtr[Com_gConfigPtr->ComBufferBaseBool];
         TS_GetBit(&bufferBaseBool[(ComReadPropPtr->ComFilterSignalValueRef / 8U)],
            ComReadPropPtr->ComFilterSignalValueRef % 8U, uint8, *dataPtr);
      }
      else
#endif /* (COM_FILTER_RECEIVER_ENABLE == STD_ON) */
      {
         /* the value from the I-Pdu shall be returned */
         CONSTP2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) PduRAM =
               ComReadPropPtr->pdudataptrRAM;

         *dataPtr = ((PduRAM[(ComSignalPosition / 8U)] &
               (uint8) (1U << (ComSignalPosition % 8U))) != 0U)
               ? 1U : 0U;
      }
   }

   DBG_COM_EB_READVALUE_BOOLEAN_EXIT(SignalDataPtr,ComReadPropPtr);
}

#endif /* (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON)

/** \brief Com_EB_ReadValue_Uint8 - reads the value of an Uint8 signal
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] SignalDataPtr - pointer where value shall be copied
 * \param[in] ComReadPropPtr - properties of the signal which shall be read
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_ReadValue_Uint8
(
   /* Deviation MISRA-3 */
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
)
{

   P2VAR (uint8, AUTOMATIC, COM_APPL_DATA) dataPtr =
         (P2VAR (uint8, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;

   DBG_COM_EB_READVALUE_UINT8_ENTRY(SignalDataPtr,ComReadPropPtr);

#if (COM_FILTER_RECEIVER_ENABLE == STD_ON)
   if ((ComReadPropPtr->TakePtrROM == FALSE)
         && (ComReadPropPtr->ComFilterSignalValueRef != COM_SIGNAL_BUFFER_REF_INVALID)
   )
   {
      /* value shall be read from buffer */
      CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) bufferBaseUint8 =
            (P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT))
            & Com_gDataMemPtr[Com_gConfigPtr->ComBufferBaseUInt8];
      TS_AtomicAssign8(*dataPtr, bufferBaseUint8[ComReadPropPtr->ComFilterSignalValueRef]);
   }
   else
#endif /* (COM_FILTER_RECEIVER_ENABLE == STD_ON) */
   {
      /* the value from the I-Pdu or the init value shall be returned */

      *dataPtr = Com_EB_ReadFromPduOrSBuffUint8(ComReadPropPtr);
   }

   DBG_COM_EB_READVALUE_UINT8_EXIT(SignalDataPtr,ComReadPropPtr);
   return;
}                               /* Com_EB_ReadValue_Uint8 */

#endif /* (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON)

/** \brief Com_EB_ReadValue_Uint16 - reads the value of an Uint16 signal
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] SignalDataPtr - pointer where value shall be copied
 * \param[in] ComReadPropPtr - properties of the signal which shall be read
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_ReadValue_Uint16
(
    /* Deviation MISRA-3 */
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
)
{

   P2VAR (uint16, AUTOMATIC, COM_APPL_DATA) dataPtr =
         (P2VAR (uint16, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;

   DBG_COM_EB_READVALUE_UINT16_ENTRY(SignalDataPtr,ComReadPropPtr);

#if (COM_FILTER_RECEIVER_ENABLE == STD_ON)
   if ((ComReadPropPtr->TakePtrROM == FALSE)
         && (ComReadPropPtr->ComFilterSignalValueRef != COM_SIGNAL_BUFFER_REF_INVALID)
   )
   {
      /* value shall be read from buffer */
      CONSTP2VAR(uint16, AUTOMATIC, COM_VAR_NOINIT) bufferBaseUint16 =
            COM_GET_MEMPTR(uint16, Com_gConfigPtr->ComBufferBaseUInt16);
      TS_AtomicAssign16(*dataPtr, bufferBaseUint16[ComReadPropPtr->ComFilterSignalValueRef]);
   }
   else
#endif /* (COM_FILTER_RECEIVER_ENABLE == STD_ON) */
   {
      /* the value from the I-Pdu or the init value shall be returned */

      *dataPtr = Com_EB_ReadFromPduOrSBuffUint16(ComReadPropPtr);

   }

   DBG_COM_EB_READVALUE_UINT16_EXIT(SignalDataPtr,ComReadPropPtr);
   return;
}                               /* Com_EB_ReadValue_Uint16 */

#endif /* (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON) */



#if (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON)

/** \brief Com_EB_ReadValue_Uint32 - reads the value of an Uint32 signal
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] SignalDataPtr - pointer where value shall be copied
 * \param[in] ComReadPropPtr - properties of the signal which shall be read
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_ReadValue_Uint32
(
   /* Deviation MISRA-3 */
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
)
{
   P2VAR (uint32, AUTOMATIC, COM_APPL_DATA) dataPtr =
         (P2VAR (uint32, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;

   DBG_COM_EB_READVALUE_UINT32_ENTRY(SignalDataPtr,ComReadPropPtr);

#if (COM_FILTER_RECEIVER_ENABLE == STD_ON)
   if ((ComReadPropPtr->TakePtrROM == FALSE)
         && (ComReadPropPtr->ComFilterSignalValueRef != COM_SIGNAL_BUFFER_REF_INVALID)
   )
   {
      /* value shall be read from buffer */
      CONSTP2VAR(uint32, AUTOMATIC, COM_VAR_NOINIT) bufferBaseUint32 =
            COM_GET_MEMPTR(uint32, Com_gConfigPtr->ComBufferBaseUInt32);
      TS_AtomicAssign32(*dataPtr, bufferBaseUint32[ComReadPropPtr->ComFilterSignalValueRef]);
   }
   else
#endif /* (COM_FILTER_RECEIVER_ENABLE == STD_ON) */
   {
      /* the value from the I-Pdu or the init value shall be returned */

      *dataPtr = Com_EB_ReadFromPduOrSBuffUint32(ComReadPropPtr);

   }

   DBG_COM_EB_READVALUE_UINT32_EXIT(SignalDataPtr,ComReadPropPtr);
   return;
}                               /* Com_EB_ReadValue_Uint32 */

#endif /* (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON)

/** \brief Com_EB_ReadValue_Sint8 - reads the value of an Sint8 signal
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] SignalDataPtr - pointer where value shall be copied
 * \param[in] ComReadPropPtr - properties of the signal which shall be read
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_ReadValue_Sint8
(
   /* Deviation MISRA-3 */
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
)
{
   P2VAR (sint8, AUTOMATIC, COM_APPL_DATA) dataPtr =
         (P2VAR (sint8, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;

   DBG_COM_EB_READVALUE_SINT8_ENTRY(SignalDataPtr,ComReadPropPtr);

#if (COM_FILTER_RECEIVER_ENABLE == STD_ON)
   if ((ComReadPropPtr->TakePtrROM == FALSE)
         && (ComReadPropPtr->ComFilterSignalValueRef != COM_SIGNAL_BUFFER_REF_INVALID)
   )
   {
      /* value shall be read from buffer */
      CONSTP2VAR(sint8, AUTOMATIC, COM_VAR_NOINIT) bufferBaseSint8 =
            (P2VAR(sint8, AUTOMATIC, COM_VAR_NOINIT))
            & Com_gDataMemPtr[Com_gConfigPtr->ComBufferBaseSInt8];
      TS_AtomicAssign8(*dataPtr, bufferBaseSint8[ComReadPropPtr->ComFilterSignalValueRef]);
   }
   else
#endif /* (COM_FILTER_RECEIVER_ENABLE == STD_ON) */
   {
      /* the value from the I-Pdu or the init value shall be returned */

      *dataPtr = Com_EB_ReadFromPduOrSBuffSint8(ComReadPropPtr);

   }

   DBG_COM_EB_READVALUE_SINT8_EXIT(SignalDataPtr,ComReadPropPtr);
   return;
}                               /* Com_EB_ReadValue_Sint8 */

#endif /* (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON)

/** \brief Com_EB_ReadValue_Sint16 - reads the value of an Sint16 signal
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] SignalDataPtr - pointer where value shall be copied
 * \param[in] ComReadPropPtr - properties of the signal which shall be read
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_ReadValue_Sint16
(
   /* Deviation MISRA-3 */
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
)
{

   P2VAR (sint16, AUTOMATIC, COM_APPL_DATA) dataPtr =
         (P2VAR (sint16, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;

   DBG_COM_EB_READVALUE_SINT16_ENTRY(SignalDataPtr,ComReadPropPtr);

#if (COM_FILTER_RECEIVER_ENABLE == STD_ON)
   if ((ComReadPropPtr->TakePtrROM == FALSE)
         && (ComReadPropPtr->ComFilterSignalValueRef != COM_SIGNAL_BUFFER_REF_INVALID)
   )
   {
      /* value shall be read from buffer */
      CONSTP2VAR(sint16, AUTOMATIC, COM_VAR_NOINIT) bufferBaseSint16 =
            COM_GET_MEMPTR(sint16, Com_gConfigPtr->ComBufferBaseSInt16);
      TS_AtomicAssign16(*dataPtr, bufferBaseSint16[ComReadPropPtr->ComFilterSignalValueRef]);
   }
   else
#endif /* (COM_FILTER_RECEIVER_ENABLE == STD_ON) */
   {
      /* the value from the I-Pdu or the init value shall be returned */

      *dataPtr = Com_EB_ReadFromPduOrSBuffSint16(ComReadPropPtr);

   }

   DBG_COM_EB_READVALUE_SINT16_EXIT(SignalDataPtr,ComReadPropPtr);
   return;
}                               /* Com_EB_ReadValue_Sint16 */

#endif /* (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON)

/** \brief Com_EB_ReadValue_Sint32 - reads the value of an Sint32 signal
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] SignalDataPtr - pointer where value shall be copied
 * \param[in] ComReadPropPtr - properties of the signal which shall be read
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_ReadValue_Sint32
(
   /* Deviation MISRA-3 */
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
)
{
   P2VAR (sint32, AUTOMATIC, COM_APPL_DATA) dataPtr =
         (P2VAR (sint32, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;

   DBG_COM_EB_READVALUE_SINT32_ENTRY(SignalDataPtr,ComReadPropPtr);

#if (COM_FILTER_RECEIVER_ENABLE == STD_ON)
   if ((ComReadPropPtr->TakePtrROM == FALSE)
         && (ComReadPropPtr->ComFilterSignalValueRef != COM_SIGNAL_BUFFER_REF_INVALID)
   )
   {
      /* value shall be read from buffer */
      CONSTP2VAR(sint32, AUTOMATIC, COM_VAR_NOINIT) bufferBaseSint32 =
            COM_GET_MEMPTR(sint32, Com_gConfigPtr->ComBufferBaseSInt32);
      TS_AtomicAssign32(*dataPtr, bufferBaseSint32[ComReadPropPtr->ComFilterSignalValueRef]);
   }
   else
#endif /* (COM_FILTER_RECEIVER_ENABLE == STD_ON) */
   {
      /* the value from the I-Pdu or the init value shall be returned */

      *dataPtr = Com_EB_ReadFromPduOrSBuffSint32(ComReadPropPtr);

   }

   DBG_COM_EB_READVALUE_SINT32_EXIT(SignalDataPtr,ComReadPropPtr);
   return;
}                               /* Com_EB_ReadValue_Sint32 */

#endif /* (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_UINT8_N_ENABLE == STD_ON)

/** \brief Com_EB_ReadValue_Uint8N - reads the value of an Uint8N signal
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] SignalDataPtr - pointer where value shall be copied
 * \param[in] ComReadPropPtr - properties of the signal which shall be read
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_ReadValue_Uint8N
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
)
{

   /* Starting position of the signals in bits divided by 8 NOTE: this
    * assumes that signals of type UINT8_N are always byte aligned */
   ComSignalDescBitType startbyte =
#if (COM_SIGNAL_BYTE_ALIGN == STD_ON)
         ComReadPropPtr->ComSignalPositionInByte;
#elif (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
   ComReadPropPtr->ComSignalPositionInBit;
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_ON) */

   DBG_COM_EB_READVALUE_UINT8N_ENTRY(SignalDataPtr,ComReadPropPtr);

#if (COM_VALUE_INIT_REPLACE == STD_ON)
   /* copy value from PDU buffer to upper layer buffer */
   if (ComReadPropPtr->TakePtrROM)
   {
      /* value from Pdu shall be replaced by the init value */
#if (COM_SIGNAL_INIT_VALUE_ENABLE == STD_ON)

      /* pointer to first byte of init value of the signal */
      /* Deviation MISRA-1 */
      /* Deviation MISRA-2 */
      CONSTP2CONST(uint8, AUTOMATIC, COM_APPL_CONST) valPtr =
            &ComReadPropPtr->pdudataptrROM[startbyte];

      /* copy init value */
      TS_MemCpy(SignalDataPtr,
         valPtr,
         ComReadPropPtr->ComBitSize);

#else
      {

         ComSignalBitSizeType l;

         COM_UINT8_COPY_INIT_DEFAULT(
            (P2VAR(uint8, AUTOMATIC, COM_APPL_DATA))SignalDataPtr,
            ComReadPropPtr->ComBitSize,
            l);
      }

#endif /* (COM_SIGNAL_INIT_VALUE_ENABLE == STD_ON) */
   }
   else
#endif /* (COM_VALUE_INIT_REPLACE == STD_ON) */
   {
      /* read the value from the Pdu */
      /* pointer to first byte of value */
      CONSTP2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) valPtr =
            &ComReadPropPtr->pdudataptrRAM[startbyte];

      /* Enter critical section */
      Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

      /* copy the data from the Pdu */
      TS_MemCpy(SignalDataPtr,
         valPtr,
         ComReadPropPtr->ComBitSize);

      /* Leave critical section */
      Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();
   }

   DBG_COM_EB_READVALUE_UINT8N_EXIT(SignalDataPtr,ComReadPropPtr);
   return;
}                               /* Com_EB_ReadValue_Uint8N */
#endif /* (COM_SIGNAL_TYPE_UINT8_N_ENABLE == STD_ON) */

/** \brief Com_EB_ReadValue - reads the value of a signal
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] SignalDataPtr - pointer where value shall be copied
 * \param[in] ComReadPropPtr - properties of the signal which shall be read
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_ReadValue
(
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr
)
{

   DBG_COM_EB_READVALUE_ENTRY(SignalDataPtr,ComReadPropPtr);

   switch (ComReadPropPtr->SignalType)
   {
#if (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON)
   case COM_BOOLEAN:
   {
      Com_EB_ReadValue_Boolean(SignalDataPtr, ComReadPropPtr);
      break;
   }
#endif /* (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON) */

#if (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON)
   case COM_UINT8:
   {
      Com_EB_ReadValue_Uint8(SignalDataPtr, ComReadPropPtr);
      break;
   }
#endif /* (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON)
   case COM_UINT16:
   {
      Com_EB_ReadValue_Uint16(SignalDataPtr, ComReadPropPtr);
      break;
   }
#endif /* (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON)
   case COM_UINT32:
   {
      Com_EB_ReadValue_Uint32(SignalDataPtr, ComReadPropPtr);
      break;
   }
#endif /* (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON) */

#if (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON)
   case COM_SINT8:
   {
      Com_EB_ReadValue_Sint8(SignalDataPtr, ComReadPropPtr);
      break;
   }
#endif /* (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON)
   case COM_SINT16:
   {
      Com_EB_ReadValue_Sint16(SignalDataPtr, ComReadPropPtr);
      break;
   }
#endif /* (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON)
   case COM_SINT32:
   {
      Com_EB_ReadValue_Sint32(SignalDataPtr, ComReadPropPtr);
      break;
   }
#endif /* (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON) */

#if (COM_SIGNAL_TYPE_UINT8_N_ENABLE == STD_ON)
   case COM_UINT8_N:
   {
      Com_EB_ReadValue_Uint8N(SignalDataPtr, ComReadPropPtr);
      break;
   }
#endif /* (COM_SIGNAL_TYPE_UINT8_N_ENABLE == STD_ON) */

   /* CHECK: NOPARSE */
   default:
      COM_UNREACHABLE_CODE_ASSERT(COMServiceId_ReceiveSignal);
      break;
      /* CHECK: PARSE */
   }                         /* switch (SignalType) */

   DBG_COM_EB_READVALUE_EXIT(SignalDataPtr,ComReadPropPtr);
}                               /* Com_EB_ReadValue */


#if (COM_RX_DATA_TOUT_ACTION != COM_RX_DATA_TOUT_ACTION_NONE)

/** \brief Com_EB_CheckRxSignalDM - Checks if the value of the signal shall be
 * replaced with the init value
 * this function checks if the DM (I-Pdu based or signal based) of the signal
 * timed out and the value of the signal shall be replaced.
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] SignalPtr - pointer to the description of the signal
 * \param[in] PduId - Id of the I-Pdu to which the signal belongs to
 * \retval TRUE if the value has to be replace, otherwise FALSE
 */

_COM_STATIC_ FUNC(boolean, COM_CODE) Com_EB_CheckRxSignalDM
(
#if ((COM_RX_SIGNAL_BASED_DM == STD_ON) || \
      (COM_RX_DATA_TOUT_ACTION == COM_RX_DATA_TOUT_ACTION_CONFIG))
   P2CONST(ComRxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr
#if (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_PRESENT_FOR_ALL)
   ,
#endif /* (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_PRESENT_FOR_ALL) */
#endif /* ((COM_RX_SIGNAL_BASED_DM == STD_ON) || \
      (COM_RX_DATA_TOUT_ACTION == COM_RX_DATA_TOUT_ACTION_CONFIG)) */
#if (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_PRESENT_FOR_ALL)
   ComIPduRefType PduId
#endif /* (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_PRESENT_FOR_ALL) */
)
{
   boolean RxDMReplace = FALSE;

   uint8 RxDMTout;

   DBG_COM_EB_CHECKRXSIGNALDM_ENTRY();

#if (COM_RX_SIGNAL_BASED_DM == STD_ON)

   if (COM_GET_RX_SIGNAL_DM(SignalPtr) == COM_RX_DM_ON)
   {
      /* Signal based DM is configured for the signal */

      /* Check if signal timed out */

      TS_GetBit(COM_RX_SIGNAL_DM_FLAGS_BYTE_POS(SignalPtr),
            COM_RX_SIGNAL_DM_TIMEOUT_BIT_POS(SignalPtr), uint8, RxDMTout);

   }
   else
#endif /* (COM_RX_SIGNAL_BASED_DM == STD_ON) */
   {
#if (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_PRESENT_FOR_ALL)
      /* If all signals have an update bit configured, there is no I-Pdu based DM */
      /* signal has no signal base DM */

      /* Check if I-Pdu timed out */
      TS_GetBit(&Com_gDataMemPtr[(Com_gConfigPtr->ComRxIPduStatusBase + PduId)],
            COM_RXPDU_RXDMTIMEOUT, uint8, RxDMTout);

#endif /* (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_PRESENT_FOR_ALL) */
   }

   if (1U == RxDMTout)
   {
#if ((COM_RX_DATA_TOUT_ACTION == COM_RX_DATA_TOUT_ACTION_CONFIG))
      /* check if timeout replace is configured for the signal */
      if (COM_GET_RX_SIGNAL_TIMEOUT_ACTION(SignalPtr) == COM_RX_DATA_TOUT_ACTION_REPLACE)
#endif /* (COM_RX_DATA_TOUT_ACTION == COM_RX_DATA_TOUT_ACTION_CONFIG) */
      {
         RxDMReplace = TRUE;
      }

   }

   DBG_COM_EB_CHECKRXSIGNALDM_EXIT(RxDMReplace);
   return RxDMReplace;
}                               /* Com_EB_CheckRxSignalDM */

#endif /* (COM_RX_DATA_TOUT_ACTION != COM_RX_DATA_TOUT_ACTION_NONE) */



/* Note of COM301: Note: If in DEFERRED mode a call to Com_ReceiveSignal() is
 * made before the deferred unpacking takes place the previous (not updated)
 * values are returned. That is only the case when the signal has filter
 * enabled (in case of signal tye UINT8_N therefore always a deviation) If a
 * signal has no filter, The value returned by Com_ReceiveSignal is the new
 * value. If signal invalidation is configured with action replace, the value
 * is replaced in the main task! So in this case a call to Com_ReceiveSignal
 * will return the invalid value instead of the init value */


#if ((COM_GENERATED_RCV_SIG_ENABLE == STD_ON) && \
(COM_MAP_RECEIVE_SIGNAL == COM_RECEIVE_SIGNAL_GENERATED))
/** \brief Com_ReceiveSignalGeneric - get a signal's actual value from COM
 * This function returns the actual value of a signal.
 * This function is only available if the configuration parameter
 * ComGeneratedRcvSigEnable is enabled and
 * ComMapReceiveSignal == Com_ReceiveSignalGenerated.
 * If available, this function maps to the generic implementation of the function.
 * Preconditions:
 * - COM must be initialized
 * \param[in] SignalId - ID of signal to receive
 * \param[in] SignalDataPtr - piece of memory to copy data to
 * \retval E_OK - success
 * \retval COM_SERVICE_NOT_AVAILABLE - Com is disabled, no valid value passed over
 */
FUNC(uint8, COM_CODE) Com_ReceiveSignalGeneric
(
   Com_SignalIdType SignalId,
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
)
#else
/** \brief Com_ReceiveSignal - get a signal's actual value from COM
 * This function returns the actual value of a signal.
 * This function is always available.
 * If the configuration parameter ComGeneratedRcvSigEnable is disabled,
 * this function maps to the generic implementation of the function.
 * If the configuration parameter ComGeneratedRcvSigEnable is enabled
 * and ComMapReceiveSignal == Com_ReceiveSignalGeneric,
 * this function maps to the generic implementation of the function.
 * If the configuration parameter ComGeneratedRcvSigEnable is enabled
 * and ComMapReceiveSignal == Com_ReceiveSignalGenerated,
 * this function maps to the generated implementation of the function.
 * Preconditions:
 * - COM must be initialized
 * \param[in] SignalId - ID of signal to receive
 * \param[in] SignalDataPtr - piece of memory to copy data to
 * \retval E_OK - success
 * \retval COM_SERVICE_NOT_AVAILABLE - Com is disabled, no valid value passed over
 */
FUNC(uint8, COM_CODE) Com_ReceiveSignal
(
   Com_SignalIdType SignalId,
   P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
)
#endif /* #if ((COM_GENERATED_RCV_SIG_ENABLE == STD_ON) && \
(COM_MAP_RECEIVE_SIGNAL == COM_RECEIVE_SIGNAL_GENERATED)) */

{
   uint8 retval = COM_SERVICE_NOT_AVAILABLE;

   /* pointer to the configuration of the signal */
   P2CONST(ComRxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr;

   /* pointer to the configuration of the IPdu to which the signal belongs */
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr;
   ComIPduRefType PduId;             /* Id of the IPdu to which the the signal belongs */

   uint8 BitRes;

   DBG_COM_RECEIVESIGNALGENERIC_ENTRY(SignalId,SignalDataPtr);

#if (COM_DEV_ERROR_DETECT == STD_ON)

   /* check whether Com is initialized */
   if (Com_InitStatus == COM_EB_UNINIT)
   {
      COM_DET_REPORTERROR(COM_E_UNINIT, COMServiceId_ReceiveSignal);
   }
   /* check SignalDataPtr */
   else if (SignalDataPtr == NULL_PTR)
   {
      COM_DET_REPORTERROR(COM_E_PARAM_POINTER, COMServiceId_ReceiveSignal);
   }
   /* Check if the SignalId is within the range of the ComRxSignalArraySize */
   else if (Com_gConfigPtr->ComRxSignalArraySize <= SignalId)
   {
      COM_DET_REPORTERROR(COM_E_PARAM, COMServiceId_ReceiveSignal);
   }

   /* The check whether the signal is a Rx signal or not is done below with the check of the
    * configuration of the signal */
   else

#endif /* COM_DEV_ERROR_DETECT */

   {

      /* get the configuration of the signal identified by the signal Id and check the
       * configuration */
      /* Deviation MISRA-1 */
      /* Deviation MISRA-2 */
      SignalPtr = COM_GET_CONFIG_ELEMENT(ComRxSignalType, Com_gConfigPtr->ComRxSignalRef, SignalId);

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
      /* CHECK: NOPARSE */
      if (NULL_PTR == SignalPtr)
      {
         COM_PRECONDITION_ASSERT(
               (NULL_PTR == SignalPtr),
               COMServiceId_ReceiveSignal);
      }
      else if (SignalPtr->ComConfigCheckData != COM_CONFIG_CHECK_RX_SIGNAL)
      {
         COM_PRECONDITION_ASSERT(
               (SignalPtr->ComConfigCheckData == COM_CONFIG_CHECK_RX_SIGNAL),
               COMServiceId_ReceiveSignal);
      }
      else
         /* CHECK: PARSE */
#endif /* COM_PRECONDITION_ASSERT_ENABLED */

      {
         /* get the IPdu Id to which the signal belongs */
         PduId = SignalPtr->RxBasicParam.ComIPduRef;

         /* get IPdu to which the the signal belongs and check if the IPdu is valid */
         /* Deviation MISRA-1 */
         /* Deviation MISRA-2 */
         IPduPtr = COM_GET_CONFIG_ELEMENT(ComRxIPduType, Com_gConfigPtr->ComRxIPduRef, PduId);

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
         /* CHECK: NOPARSE */
         if (NULL_PTR == IPduPtr)
         {
            COM_PRECONDITION_ASSERT(
                  (NULL_PTR == IPduPtr),
                  COMServiceId_ReceiveSignal);
         }
         else if (IPduPtr->ComConfigCheckData != COM_CONFIG_CHECK_RX_IPDU)
         {
            COM_PRECONDITION_ASSERT(
                  (IPduPtr->ComConfigCheckData == COM_CONFIG_CHECK_RX_IPDU),
                  COMServiceId_ReceiveSignal);
         }
         else
            /* CHECK: PARSE */
#endif /* COM_PRECONDITION_ASSERT_ENABLED */

         {
            TS_GetBit(&Com_gDataMemPtr[(Com_gConfigPtr->ComRxIPduStatusBase + PduId)],
                  COM_RXPDU_STARTED, uint8, BitRes);

            if (BitRes == TRUE)
            {
               retval = E_OK;
            }

            {
#if (COM_VALUE_INIT_REPLACE == STD_ON)
               boolean takeInitVal = FALSE;

#if (COM_FILTER_RECEIVER_ENABLE == STD_ON)
               uint8 filterType = SignalPtr->ComFilterType;
               takeInitVal = takeInitVal || (filterType == COM_F_NEVER);
#endif /* (COM_FILTER_RECEIVER_ENABLE == STD_ON) */

#if (COM_RX_DATA_TOUT_ACTION != COM_RX_DATA_TOUT_ACTION_NONE)
               {
                  boolean rxDMReplace;

                  rxDMReplace = Com_EB_CheckRxSignalDM(
#if ((COM_RX_SIGNAL_BASED_DM == STD_ON) || \
      (COM_RX_DATA_TOUT_ACTION == COM_RX_DATA_TOUT_ACTION_CONFIG))
                        SignalPtr
#if (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_PRESENT_FOR_ALL)
                        ,
#endif /* (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_PRESENT_FOR_ALL) */
#endif /* ((COM_RX_SIGNAL_BASED_DM == STD_ON) || \
                     (COM_RX_DATA_TOUT_ACTION == COM_RX_DATA_TOUT_ACTION_CONFIG)) */

#if (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_PRESENT_FOR_ALL)
                        PduId
#endif /* (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_PRESENT_FOR_ALL) */
                  );

                  takeInitVal = takeInitVal || rxDMReplace;
               }
#endif /* (COM_RX_DATA_TOUT_ACTION != COM_RX_DATA_TOUT_ACTION_NONE) */

#endif /* (COM_VALUE_INIT_REPLACE == STD_ON) */

               {
                  ComCommonReadPropType ComReadProp;
                  Com_EB_CreateReadProp(
                     &ComReadProp,
                     SignalPtr,
                     IPduPtr
#if (COM_VALUE_INIT_REPLACE == STD_ON)
                     ,takeInitVal
#endif /* (COM_VALUE_INIT_REPLACE == STD_ON) */
                  );

                  /* get the value */
                  Com_EB_ReadValue(SignalDataPtr, &ComReadProp);
               }
            }
         }
      }
   }


   DBG_COM_RECEIVESIGNALGENERIC_EXIT(retval,SignalId,SignalDataPtr);
   return retval;
}

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_STOP_SEC_CODE
#include <MemMap.h>
#endif

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/
