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


/*==================[inclusions]============================================*/



#include <Com_Trace.h>
#include <TSAutosar.h>          /* EB specific standard types */
#include <ComStack_Types.h>     /* AUTOSAR Standard types */
#include <Com_Api.h>                /* Module public API */

#include <Com_Priv.h>           /* Module private API */
#include <TSMem.h>              /* TS_MemCpy */

#include <Com_Core_TxSignal.h>  /* signal functions */

#if ((COM_TM_AVAILABLE == STD_ON) || (COM_TMS_ENABLE == STD_ON))
#include <Com_Core_TM.h> /* Transmission Mode functions */
#endif /* ((COM_TM_AVAILABLE == STD_ON) || (COM_TMS_ENABLE == STD_ON)) */

#if (COM_TMS_ENABLE == STD_ON)
#include <Com_Filter.h>       /* Filter functions */
#endif /* (COM_TMS_ENABLE == STD_ON) */


#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_START_SEC_CODE
#include <MemMap.h>
#endif


/** \brief Com_EB_CreateWriteProp_Sig - initializes the internal
 * structure for the representation of a Tx-signal
 * Preconditions:
 * - prior to this call, the COM module shall be initialized
 * \param[out] ComWritePropPtr - pointer where the result shall be stored
 * \param[in] dataPtr - pointer where the data shall be written
 * \param[in] SignalPtr - pointer to the description of the Tx signal
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_CreateWriteProp_Sig
(
   P2VAR(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr,
   P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComTxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr
);


#if (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON)

/** \brief Com_EB_FilterAndWriteUint8 - performs filter and writes value
 * to Pdu of an Uint8 signal
 * Preconditions:
 * COM must be initialized.
 * \param[in] SignalPtr - reference to configuration of signal
 * \param[in] SignalDataPtr - place in memory to copy the data from (RAM)
 * \param[in] ComWritePropPtr - properties of the signal which shall be written
 * \retval TRUE - filter evaluated to TRUE
 * \retval FALSE - filter evaluated to FALSE
 */
_COM_STATIC_ FUNC(boolean, COM_CODE)Com_EB_FilterAndWriteUint8
(
   P2CONST(ComTxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
);

#endif /* (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON)

/** \brief Com_EB_FilterAndWriteUint16 - performs filter and writes value
 * to Pdu of an Uint16 signal
 * Preconditions:
 * COM must be initialized.
 * \param[in] SignalPtr - reference to configuration of signal
 * \param[in] SignalDataPtr - place in memory to copy the data from (RAM)
 * \param[in] ComWritePropPtr - properties of the signal which shall be written
 * \retval TRUE - filter evaluated to TRUE
 * \retval FALSE - filter evaluated to FALSE
 */
_COM_STATIC_ FUNC(boolean, COM_CODE)Com_EB_FilterAndWriteUint16
(
   P2CONST(ComTxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
);

#endif /* (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON)

/** \brief Com_EB_FilterAndWriteUint32 - performs filter and writes value
 * to Pdu of an Uint32 signal
 * Preconditions:
 * COM must be initialized.
 * \param[in] SignalPtr - reference to configuration of signal
 * \param[in] SignalDataPtr - place in memory to copy the data from (RAM)
 * \param[in] ComWritePropPtr - properties of the signal which shall be written
 * \retval TRUE - filter evaluated to TRUE
 * \retval FALSE - filter evaluated to FALSE
 */
_COM_STATIC_ FUNC(boolean, COM_CODE)Com_EB_FilterAndWriteUint32
(
   P2CONST(ComTxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
);

#endif /* (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON)

/** \brief Com_EB_FilterAndWriteSint8 - performs filter and writes value
 * to Pdu of a Sint8 signal
 * Preconditions:
 * COM must be initialized.
 * \param[in] SignalPtr - reference to configuration of signal
 * \param[in] SignalDataPtr - place in memory to copy the data from (RAM)
 * \param[in] ComWritePropPtr - properties of the signal which shall be written
 * \retval TRUE - filter evaluated to TRUE
 * \retval FALSE - filter evaluated to FALSE
 */
_COM_STATIC_ FUNC(boolean, COM_CODE)Com_EB_FilterAndWriteSint8
(
   P2CONST(ComTxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
);

#endif /* (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON)

/** \brief Com_EB_FilterAndWriteSint16 - performs filter and writes value
 * to Pdu of a Sint16 signal
 * Preconditions:
 * COM must be initialized.
 * \param[in] SignalPtr - reference to configuration of signal
 * \param[in] SignalDataPtr - place in memory to copy the data from (RAM)
 * \param[in] ComWritePropPtr - properties of the signal which shall be written
 * \retval TRUE - filter evaluated to TRUE
 * \retval FALSE - filter evaluated to FALSE
 */
_COM_STATIC_ FUNC(boolean, COM_CODE)Com_EB_FilterAndWriteSint16
(
   P2CONST(ComTxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
);

#endif /* (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON)

/** \brief Com_EB_FilterAndWriteSint32 - performs filter and writes value
 * to Pdu of a Sint32 signal
 * Preconditions:
 * COM must be initialized.
 * \param[in] SignalPtr - reference to configuration of signal
 * \param[in] SignalDataPtr - place in memory to copy the data from (RAM)
 * \param[in] ComWritePropPtr - properties of the signal which shall be written
 * \retval TRUE - filter evaluated to TRUE
 * \retval FALSE - filter evaluated to FALSE
 */
_COM_STATIC_ FUNC(boolean, COM_CODE)Com_EB_FilterAndWriteSint32
(
   P2CONST(ComTxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
);

#endif /* (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_UINT8_N_ENABLE == STD_ON)

/** \brief Com_EB_FilterAndWriteUint8N - writes value
 * to Pdu of an Uint8N signal
 * Preconditions:
 * COM must be initialized.
 * \param[in] SignalPtr - reference to configuration of signal
 * \param[in] SignalDataPtr - place in memory to copy the data from (RAM)
 * \param[in] ComWritePropPtr - properties of the signal which shall be written
 * \retval None
 */

_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_FilterAndWriteUint8N
(
   P2CONST(ComTxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
);

#endif /* (COM_SIGNAL_TYPE_UINT8_N_ENABLE == STD_ON) */



/** \brief Com_EB_SendSignal_FilterAndWrite - performs filter and writes value
 * to Pdu
 * Preconditions:
 * COM must be initialized.
 * \param[in]SignalType - signal type of the signal
 * \param[in] SignalPtr - reference to configuration of signal
 * \param[in] SignalDataPtr - place in memory to copy the data from (RAM)
 * \param[in] ComIPduValueRef - reference to the pdu buffer
 * \retval TRUE - filter evaluated to TRUE
 * \retval FALSE - filter evaluated to FALSE
 */
_COM_STATIC_ FUNC(boolean, COM_CODE)Com_EB_SendSignal_FilterAndWrite
(
   Com_TS_SignalTypeType SignalType,
   P2CONST(ComTxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   ComRAMIdxType ComIPduValueRef
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
);



/** \brief Com_EB_CreateWriteProp_Sig - initializes the internal
 * structure for the representation of a Tx-signal
 * Preconditions:
 * - prior to this call, the COM module shall be initialized
 * \param[out] ComWritePropPtr - pointer where the result shall be stored
 * \param[in] dataPtr - pointer where the data shall be written
 * \param[in] SignalPtr - pointer to the description of the Tx signal
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_CreateWriteProp_Sig
(
   P2VAR(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr,
   P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComTxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr
)
{

   ComWritePropPtr->dataPtr = dataPtr;
#if (COM_SIGNAL_BYTE_ALIGN == STD_ON)
   ComWritePropPtr->ComSignalPositionInByte = SignalPtr->TxBasicParam.ComSignalPositionInByte;
#elif (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
   ComWritePropPtr->ComSignalPositionInBit = SignalPtr->TxBasicParam.ComSignalPositionInBit;
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_ON) */

#if (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)
   ComWritePropPtr->ComUpdateBitPositionInBit = SignalPtr->TxBasicParam.ComUpdateBitPositionInBit;
#endif /* (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) */

   ComWritePropPtr->size = SignalPtr->ComBitSize;

#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
   ComWritePropPtr->endianness = COM_GET_TX_SIGNAL_ENDIANNESS(SignalPtr);
#endif

#if (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL)
   ComWritePropPtr->updateBit = COM_GET_TX_SIGNAL_UPDATE_BIT(SignalPtr);
#endif /* (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL) */

   return;

}                               /* Com_EB_CreateWriteProp_Sig */


#if (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON)

/** \brief Com_EB_FilterAndWriteUint8 - performs filter and writes value
 * to Pdu of an Uint8 signal
 * Preconditions:
 * COM must be initialized.
 * \param[in] SignalPtr - reference to configuration of signal
 * \param[in] SignalDataPtr - place in memory to copy the data from (RAM)
 * \param[in] ComWritePropPtr - properties of the signal which shall be written
 * \retval TRUE - filter evaluated to TRUE
 * \retval FALSE - filter evaluated to FALSE
 */
_COM_STATIC_ FUNC(boolean, COM_CODE)Com_EB_FilterAndWriteUint8
(
   P2CONST(ComTxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
)
{

   boolean TMSResult = FALSE;

   DBG_COM_EB_FILTERANDWRITEUINT8_ENTRY(SignalPtr,SignalDataPtr,ComWritePropPtr);

#if (COM_TMS_ENABLE == STD_ON)
   if (TRUE == (COM_F_NON_TRIVIAL(SignalPtr->ComFilterType)))
   {
      ComCommonFilterPropertiesType ComFilterProp;
      Com_EB_CreateFilterProp(
         &ComFilterProp,
         SignalPtr->ComFilterSignalValueRef,
         SignalPtr->ComFilterRef,
         SignalPtr->ComFilterType);

      TMSResult = Com_EB_FilterUint8(
            &ComFilterProp,
            SignalDataPtr);
   }
#else
   TS_PARAM_UNUSED(SignalPtr);
#endif /* (COM_TMS_ENABLE == STD_ON) */

   /* Write the value to the I-Pdu */
   Com_EB_WriteToPduOrSBuff8Bit(
      SignalDataPtr,
      ComWritePropPtr
#if (COM_CHECK_VALUE_SIZE == STD_ON)
      ,TRUE
#endif /* (COM_CHECK_VALUE_SIZE == STD_ON) */
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
      , triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
   );

   DBG_COM_EB_FILTERANDWRITEUINT8_EXIT(TMSResult,SignalPtr,SignalDataPtr,ComWritePropPtr);

   return TMSResult;

}                               /* Com_EB_FilterAndWriteUint8 */

#endif /* (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON)

/** \brief Com_EB_FilterAndWriteUint16 - performs filter and writes value
 * to Pdu of an Uint16 signal
 * Preconditions:
 * COM must be initialized.
 * \param[in] SignalPtr - reference to configuration of signal
 * \param[in] SignalDataPtr - place in memory to copy the data from (RAM)
 * \param[in] ComWritePropPtr - properties of the signal which shall be written
 * \retval TRUE - filter evaluated to TRUE
 * \retval FALSE - filter evaluated to FALSE
 */
_COM_STATIC_ FUNC(boolean, COM_CODE)Com_EB_FilterAndWriteUint16
(
   P2CONST(ComTxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
)
{

   boolean TMSResult = FALSE;

   DBG_COM_EB_FILTERANDWRITEUINT16_ENTRY(SignalPtr,SignalDataPtr,ComWritePropPtr);

#if (COM_TMS_ENABLE == STD_ON)
   if (TRUE == (COM_F_NON_TRIVIAL(SignalPtr->ComFilterType)))
   {
      ComCommonFilterPropertiesType ComFilterProp;
      Com_EB_CreateFilterProp(
         &ComFilterProp,
         SignalPtr->ComFilterSignalValueRef,
         SignalPtr->ComFilterRef,
         SignalPtr->ComFilterType);

      TMSResult = Com_EB_FilterUint16(&ComFilterProp,SignalDataPtr);

   }
#else
   TS_PARAM_UNUSED(SignalPtr);
#endif /* (COM_TMS_ENABLE == STD_ON) */

   /* Write the value to the I-Pdu */
   Com_EB_WriteToPduOrSBuff16Bit(
      SignalDataPtr,
      ComWritePropPtr
#if (COM_CHECK_VALUE_SIZE == STD_ON)
      ,TRUE
#endif /* (COM_CHECK_VALUE_SIZE == STD_ON) */
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
      , triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
   );

   DBG_COM_EB_FILTERANDWRITEUINT16_EXIT(TMSResult,SignalPtr,SignalDataPtr,ComWritePropPtr);

   return TMSResult;

}                               /* Com_EB_FilterAndWriteUint16 */

#endif /* (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON)

/** \brief Com_EB_FilterAndWriteUint32 - performs filter and writes value
 * to Pdu of an Uint32 signal
 * Preconditions:
 * COM must be initialized.
 * \param[in] SignalPtr - reference to configuration of signal
 * \param[in] SignalDataPtr - place in memory to copy the data from (RAM)
 * \param[in] ComWritePropPtr - properties of the signal which shall be written
 * \retval TRUE - filter evaluated to TRUE
 * \retval FALSE - filter evaluated to FALSE
 */
_COM_STATIC_ FUNC(boolean, COM_CODE)Com_EB_FilterAndWriteUint32
(
   P2CONST(ComTxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
)
{

   boolean TMSResult = FALSE;

   DBG_COM_EB_FILTERANDWRITEUINT32_ENTRY(SignalPtr,SignalDataPtr,ComWritePropPtr);


#if (COM_TMS_ENABLE == STD_ON)
   if (TRUE == (COM_F_NON_TRIVIAL(SignalPtr->ComFilterType)))
   {
      ComCommonFilterPropertiesType ComFilterProp;
      Com_EB_CreateFilterProp(
         &ComFilterProp,
         SignalPtr->ComFilterSignalValueRef,
         SignalPtr->ComFilterRef,
         SignalPtr->ComFilterType);

      TMSResult = Com_EB_FilterUint32(&ComFilterProp,SignalDataPtr);
   }
#else
   TS_PARAM_UNUSED(SignalPtr);
#endif /* (COM_TMS_ENABLE == STD_ON) */

   /* Write the value to the I-Pdu */
   Com_EB_WriteToPduOrSBuff32Bit(
      SignalDataPtr,
      ComWritePropPtr
#if (COM_CHECK_VALUE_SIZE == STD_ON)
      ,TRUE
#endif /* (COM_CHECK_VALUE_SIZE == STD_ON) */
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
      , triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
   );

   DBG_COM_EB_FILTERANDWRITEUINT32_EXIT(TMSResult, SignalPtr,SignalDataPtr,ComWritePropPtr);

   return TMSResult;

}                               /* Com_EB_FilterAndWriteUint32 */

#endif /* (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON)

/** \brief Com_EB_FilterAndWriteSint8 - performs filter and writes value
 * to Pdu of a Sint8 signal
 * Preconditions:
 * COM must be initialized.
 * \param[in] SignalPtr - reference to configuration of signal
 * \param[in] SignalDataPtr - place in memory to copy the data from (RAM)
 * \param[in] ComWritePropPtr - properties of the signal which shall be written
 * \retval TRUE - filter evaluated to TRUE
 * \retval FALSE - filter evaluated to FALSE
 */
_COM_STATIC_ FUNC(boolean, COM_CODE)Com_EB_FilterAndWriteSint8
(
   P2CONST(ComTxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
)
{

   boolean TMSResult = FALSE;

   DBG_COM_EB_FILTERANDWRITESINT8_ENTRY(SignalPtr,SignalDataPtr,ComWritePropPtr);

#if (COM_TMS_ENABLE == STD_ON)
   if (TRUE == (COM_F_NON_TRIVIAL(SignalPtr->ComFilterType)))
   {
      ComCommonFilterPropertiesType ComFilterProp;
      Com_EB_CreateFilterProp(
         &ComFilterProp,
         SignalPtr->ComFilterSignalValueRef,
         SignalPtr->ComFilterRef,
         SignalPtr->ComFilterType);

      TMSResult = Com_EB_FilterSint8(&ComFilterProp,SignalDataPtr);
   }
#else
   TS_PARAM_UNUSED(SignalPtr);
#endif /* (COM_TMS_ENABLE == STD_ON) */


   /* Write the value to the I-Pdu */
   Com_EB_WriteToPduOrSBuff8Bit(
      SignalDataPtr,
      ComWritePropPtr
#if (COM_CHECK_VALUE_SIZE == STD_ON)
      ,FALSE
#endif /* (COM_CHECK_VALUE_SIZE == STD_ON) */
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
      , triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
   );

   DBG_COM_EB_FILTERANDWRITESINT8_EXIT(TMSResult,SignalPtr,SignalDataPtr,ComWritePropPtr);

   return TMSResult;

}                               /* Com_EB_FilterAndWriteSint8 */

#endif /* (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON) */

#if (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON)

/** \brief Com_EB_FilterAndWriteSint16 - performs filter and writes value
 * to Pdu of a Sint16 signal
 * Preconditions:
 * COM must be initialized.
 * \param[in] SignalPtr - reference to configuration of signal
 * \param[in] SignalDataPtr - place in memory to copy the data from (RAM)
 * \param[in] ComWritePropPtr - properties of the signal which shall be written
 * \retval TRUE - filter evaluated to TRUE
 * \retval FALSE - filter evaluated to FALSE
 */
_COM_STATIC_ FUNC(boolean, COM_CODE)Com_EB_FilterAndWriteSint16
(
   P2CONST(ComTxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
)
{

   boolean TMSResult = FALSE;

   DBG_COM_EB_FILTERANDWRITESINT16_ENTRY(SignalPtr,SignalDataPtr,ComWritePropPtr);

#if (COM_TMS_ENABLE == STD_ON)
   if (TRUE == (COM_F_NON_TRIVIAL(SignalPtr->ComFilterType)))
   {
      ComCommonFilterPropertiesType ComFilterProp;
      Com_EB_CreateFilterProp(
         &ComFilterProp,
         SignalPtr->ComFilterSignalValueRef,
         SignalPtr->ComFilterRef,
         SignalPtr->ComFilterType);

      TMSResult = Com_EB_FilterSint16(&ComFilterProp,SignalDataPtr);
   }
#else
   TS_PARAM_UNUSED(SignalPtr);
#endif /* (COM_TMS_ENABLE == STD_ON) */


   /* Write the value to the I-Pdu */
   Com_EB_WriteToPduOrSBuff16Bit(
      SignalDataPtr,
      ComWritePropPtr
#if (COM_CHECK_VALUE_SIZE == STD_ON)
      ,FALSE
#endif /* (COM_CHECK_VALUE_SIZE == STD_ON) */
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
      , triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
   );

   DBG_COM_EB_FILTERANDWRITESINT16_EXIT(TMSResult,SignalPtr,SignalDataPtr,ComWritePropPtr);

   return TMSResult;

}                               /* Com_EB_FilterAndWriteSint16 */

#endif /* (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON)

/** \brief Com_EB_FilterAndWriteSint32 - performs filter and writes value
 * to Pdu of a Sint32 signal
 * Preconditions:
 * COM must be initialized.
 * \param[in] SignalPtr - reference to configuration of signal
 * \param[in] SignalDataPtr - place in memory to copy the data from (RAM)
 * \param[in] ComWritePropPtr - properties of the signal which shall be written
 * \retval TRUE - filter evaluated to TRUE
 * \retval FALSE - filter evaluated to FALSE
 */
_COM_STATIC_ FUNC(boolean, COM_CODE)Com_EB_FilterAndWriteSint32
(
   P2CONST(ComTxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
)
{

   boolean TMSResult = FALSE;

   DBG_COM_EB_FILTERANDWRITESINT32_ENTRY(SignalPtr,SignalDataPtr,ComWritePropPtr);

#if (COM_TMS_ENABLE == STD_ON)
   if (TRUE == (COM_F_NON_TRIVIAL(SignalPtr->ComFilterType)))
   {
      ComCommonFilterPropertiesType ComFilterProp;
      Com_EB_CreateFilterProp(
         &ComFilterProp,
         SignalPtr->ComFilterSignalValueRef,
         SignalPtr->ComFilterRef,
         SignalPtr->ComFilterType);

      TMSResult = Com_EB_FilterSint32(&ComFilterProp,SignalDataPtr);
   }
#else
   TS_PARAM_UNUSED(SignalPtr);
#endif /* (COM_TMS_ENABLE == STD_ON) */


   /* Write the value to the I-Pdu */
   Com_EB_WriteToPduOrSBuff32Bit(
      SignalDataPtr,
      ComWritePropPtr
#if (COM_CHECK_VALUE_SIZE == STD_ON)
      ,FALSE
#endif /* (COM_CHECK_VALUE_SIZE == STD_ON) */
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
      , triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
   );

   DBG_COM_EB_FILTERANDWRITESINT32_EXIT(TMSResult,SignalPtr,SignalDataPtr,ComWritePropPtr);

   return TMSResult;
}                               /* Com_EB_FilterAndWriteSint32 */

#endif /* (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON) */



#if (COM_SIGNAL_TYPE_UINT8_N_ENABLE == STD_ON)

/** \brief Com_EB_FilterAndWriteUint8N - writes value
 * to Pdu of an Uint8N signal
 * Preconditions:
 * COM must be initialized.
 * \param[in] SignalPtr - reference to configuration of signal
 * \param[in] SignalDataPtr - place in memory to copy the data from (RAM)
 * \param[in] ComWritePropPtr - properties of the signal which shall be written
 * \retval None
 */

_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_FilterAndWriteUint8N
(
   P2CONST(ComTxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
)
{

   ComSignalDescBitType StartingByte;

   DBG_COM_EB_FILTERANDWRITEUINT8N_ENTRY(SignalPtr,SignalDataPtr,ComWritePropPtr);

   /* get position of the signal within the IPDu */
   COM_GET_SIGNAL_POS_ALIG(SignalPtr, StartingByte);

   /* enter critical section */
   Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

#if (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)

#if (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL)
   if (COM_GET_TX_SIGNAL_UPDATE_BIT(SignalPtr) == TRUE)
#endif /* (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL) */
   {

#if (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)
   Com_SetBitUInt8(
         &ComWritePropPtr->dataPtr[(SignalPtr->TxBasicParam.ComUpdateBitPositionInBit / 8U)],
         (SignalPtr->TxBasicParam.ComUpdateBitPositionInBit % 8U));
#endif /* (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) */
   }

#endif /* (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) */

   /* copy value from RAM */
   Com_EB_WriteToPduOrSBuffByteArray(
         (P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT))
            &ComWritePropPtr->dataPtr[StartingByte],
         (P2CONST(uint8, AUTOMATIC, COM_APPL_DATA))
            SignalDataPtr,
         SignalPtr->ComBitSize
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
         ,triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
         );

   /* leave critical section */
   Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();


   /* Here no filter have to be evaluated; if filter would be ALWAYS, the
    * TM mode TRUE would always be selected, If filter would be NEVER, it
    * would not contribute to TMS */


   DBG_COM_EB_FILTERANDWRITEUINT8N_EXIT(SignalPtr,SignalDataPtr,ComWritePropPtr);
}                               /* Com_EB_FilterAndWriteUint8N */

#endif /* (COM_SIGNAL_TYPE_UINT8_N_ENABLE == STD_ON) */


/** \brief Com_EB_SendSignal_FilterAndWrite - performs filter and writes value
 * to Pdu
 * Preconditions:
 * COM must be initialized.
 * \param[in]SignalType - signal type of the signal
 * \param[in] SignalPtr - reference to configuration of signal
 * \param[in] SignalDataPtr - place in memory to copy the data from (RAM)
 * \param[in] ComIPduValueRef - reference to the pdu buffer
 * \retval TRUE - filter evaluated to TRUE
 * \retval FALSE - filter evaluated to FALSE
 */
_COM_STATIC_ FUNC(boolean, COM_CODE)Com_EB_SendSignal_FilterAndWrite
(
   Com_TS_SignalTypeType SignalType,
   P2CONST(ComTxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   ComRAMIdxType ComIPduValueRef
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
)
{
   boolean TMSResult = FALSE;
   ComCommonWritePropType ComWriteProp;

   DBG_COM_EB_SENDSIGNAL_FILTERANDWRITE_ENTRY(SignalType,SignalPtr,SignalDataPtr,ComIPduValueRef);

   Com_EB_CreateWriteProp_Sig(&ComWriteProp, &Com_gDataMemPtr[(ComIPduValueRef)], SignalPtr);

   switch(SignalType)
   {
#if (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON)
   case COM_BOOLEAN:
   {

#if (COM_TMS_ENABLE == STD_ON)
      if (TRUE == (COM_F_NON_TRIVIAL(SignalPtr->ComFilterType)))
      {
         ComCommonFilterPropertiesType ComFilterProp;
         Com_EB_CreateFilterProp(
            &ComFilterProp,
            SignalPtr->ComFilterSignalValueRef,
            SignalPtr->ComFilterRef,
            SignalPtr->ComFilterType);

         TMSResult = Com_EB_FilterBoolean(&ComFilterProp,SignalDataPtr);
      }
#endif /* (COM_TMS_ENABLE == STD_ON) */

      /* Write the value to the I-Pdu */
      Com_EB_WriteToPduOrSBuffBool(
         SignalDataPtr,
         &ComWriteProp
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
         , triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
      );

      break;
   }                            /* case COM_BOOLEAN: */
#endif /* (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON) */
#if (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON)
   case COM_UINT8:
   {

      TMSResult =
            Com_EB_FilterAndWriteUint8(
                  SignalPtr,
                  SignalDataPtr,
                  &ComWriteProp
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
                  ,triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
            );

      break;
   }                            /* case COM_UINT8: */
#endif /* (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON) */
#if (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON)
   case COM_UINT16:
   {

      TMSResult =
            Com_EB_FilterAndWriteUint16(
                  SignalPtr,
                  SignalDataPtr,
                  &ComWriteProp
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
                  ,triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
            );

      break;
   }                            /* case COM_UINT16: */
#endif /* (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON) */
#if (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON)
   case COM_UINT32:
   {

      TMSResult =
            Com_EB_FilterAndWriteUint32(
                  SignalPtr,
                  SignalDataPtr,
                  &ComWriteProp
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
                  ,triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
            );

      break;
   }                            /* case COM_UINT32: */
#endif /* (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON) */
#if (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON)
   case COM_SINT8:
   {

      TMSResult =
            Com_EB_FilterAndWriteSint8(
                  SignalPtr,
                  SignalDataPtr,
                  &ComWriteProp
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
                  ,triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
            );

      break;
   }                            /* case COM_SINT8: */
#endif /* (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON) */
#if (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON)
   case COM_SINT16:
   {

      TMSResult =
            Com_EB_FilterAndWriteSint16(
                  SignalPtr,
                  SignalDataPtr,
                  &ComWriteProp
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
                  ,triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
            );

      break;
   }                            /* case COM_SINT16: */
#endif /* (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON) */
#if (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON)
   case COM_SINT32:
   {

      TMSResult =
            Com_EB_FilterAndWriteSint32(
                  SignalPtr,
                  SignalDataPtr,
                  &ComWriteProp
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
                  ,triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
            );

      break;
   }                            /* case COM_SINT32: */
#endif /* (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON) */
#if (COM_SIGNAL_TYPE_UINT8_N_ENABLE == STD_ON)
   case COM_UINT8_N:
   {
      Com_EB_FilterAndWriteUint8N(
            SignalPtr,
            SignalDataPtr,
            &ComWriteProp
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
            ,triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
      );

      break;
   }                            /* case COM_UINT8_N: */
#endif /* (COM_SIGNAL_TYPE_UINT8_N_ENABLE == STD_ON) */

   /* CHECK: NOPARSE */
   default:
      COM_UNREACHABLE_CODE_ASSERT(COM_INTERNAL_API_ID);
      break;
      /* CHECK: PARSE */

   }                            /* switch(SignalType) */
   DBG_COM_EB_SENDSIGNAL_FILTERANDWRITE_EXIT(TMSResult,SignalType,SignalPtr,SignalDataPtr,ComIPduValueRef);
   return TMSResult;

}                               /* Com_EB_SendSignal_FilterAndWrite */

/** \brief Com_EB_SendSignal - send a signal
 * The service Com_SendSignal updates the signal object identified by SignalId
 * with the signal referenced by the SignalDataPtr parameter.
 * Preconditions:
 * COM must be initialized.
 * \param[in] SignalPtr - reference to configuration of signal
 * \param[in] IPduPtr - reference to configuration of I-Pdu to which the
 * signal belongs
 * \param[in] PduId - ID of I-Pdu to which the signal belongs
 * \param[in] SignalDataPtr - place in memory to copy the data from (RAM)
 * \param[in] SendInMainFunctionTx - if TRUE, the Pdu is sent not now but
 * during the next Com_MainfunctionTx(), otherwise immediately
 * \retval E_OK - success
 * \retval COM_SERVICE_NOT_AVAILABLE - failure (corresponding I-PDU group was
 * stopped)
 */

TS_MOD_PRIV_DEFN FUNC(uint8, COM_CODE) Com_EB_SendSignal
(
   P2CONST(ComTxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr,
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
   ComIPduRefType PduId,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
#if (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON)
   ,boolean SendInMainFunctionTx
#endif /* (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON) */
)
{

   uint8 retval = E_OK;

   uint8 BitRes;                /* flag for COM_TXPDU_STARTED */

   CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) PduStatusFlagsPtr =
         &Com_gDataMemPtr[(Com_gConfigPtr->ComTxIPduStatusBase + PduId)];

   /* signal type of the signal */
   Com_TS_SignalTypeType SignalType = COM_GET_TX_SIGNAL_SIGNAL_TYPE(SignalPtr);

#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   boolean trigger = FALSE;
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */

#if (COM_TMS_ENABLE == STD_ON)
   boolean forceTrigger = FALSE;
   boolean TMSResult;
#endif /* (COM_TMS_ENABLE == STD_ON) */

   DBG_COM_EB_SENDSIGNAL_ENTRY(SignalPtr,IPduPtr,PduId,SignalDataPtr);

#if (COM_TMS_ENABLE == STD_ON)
   TMSResult =
#else
         (void)
#endif /* (COM_TMS_ENABLE == STD_ON) */

         Com_EB_SendSignal_FilterAndWrite(
               SignalType,
               SignalPtr,
               SignalDataPtr,
               IPduPtr->ComIPduValueRef
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
               , &trigger
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
         );


#if (COM_TMS_ENABLE == STD_ON)


   /* the signal is a real signal */
   /* check if this signal of the I-Pdu contributes to TMS */
   if (!((SignalPtr->ComFilterType == COM_F_ALWAYS) ||
         (SignalPtr->ComFilterType == COM_F_NEVER)))
   {

      /* signal has non trivial filter */

      /* get the old value of TMS of signal */
      CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT)PduTMSFlagPtr =
            (&Com_gDataMemPtr
                  [(IPduPtr->ComIPduTMSFlagsRef) + (SignalPtr->ComPositionOfTMSFlag / 8U)]);

      boolean OldFilterResult;

      boolean CurrentTM;

      uint8 const SignalTMSFlag =
            (uint8)(SignalPtr->ComPositionOfTMSFlag % 8U);

      TS_GetBit(PduTMSFlagPtr, ((uint8) SignalTMSFlag), uint8,
         OldFilterResult);

      if (OldFilterResult != TMSResult)
      {
         /* the result of the filter changed */
         boolean newTM;

         uint8 PduStatusByte;

         /* store result of filter */
         if (TMSResult == TRUE)
         {
            TS_AtomicSetBit_8(PduTMSFlagPtr, ((uint8) SignalTMSFlag));
         }
         else
         {
            TS_AtomicClearBit_8(PduTMSFlagPtr, ((uint8) SignalTMSFlag));
         }


         /* enter the critical section for calculation the new TM */
         Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

         /* calculate if the TM of the Pdu changed */
         newTM = Com_EB_CalculateTM(IPduPtr);

         /* get the status byte of the Pdu */
         PduStatusByte = *PduStatusFlagsPtr;

         /* get the current TMS status of Pdu */
         TS_GetBit(&PduStatusByte, COM_TXPDU_TMSSTATE, uint8, CurrentTM);

         if (newTM != CurrentTM)
         {
            /* change the TM of the I-Pdu */
            if (newTM == TRUE)
            {
               Com_SetBitUInt8Var(PduStatusByte, COM_TXPDU_TMSSTATE);
            }
            else
            {
               Com_ClearBitUInt8Var(PduStatusByte, COM_TXPDU_TMSSTATE);
            }

            /* Set the changed flag of the I-Pdu */
            Com_SetBitUInt8Var(PduStatusByte, COM_TXPDU_TMSCHANGED);

            /* save the status byte again */
            *PduStatusFlagsPtr = PduStatusByte;

         }                /* if (newTM != CurrentTM) */

         Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();

         /* COM582: If a change of the TMS causes a change to the
          * transmission mode DIRECT, an immediate (respecting the MDT)
          * direct/ n-times transmission to the underlying layer shall
          * be initiated.
          * -> shall also initiate transmission if signal has
          * transfer property Pending */
         if(newTM != CurrentTM)
         {
            uint8 const AktTM =
                  COM_GET_COM_TX_MODE(newTM, IPduPtr->ComTxModeModes);

            if ((COM_TX_MODE_MODE_DIRECT == AktTM) || (COM_TX_MODE_MODE_N_TIMES == AktTM))
            {
               forceTrigger = TRUE;
            }

         }

      }                   /* if (OldFilterResult != TMSResult) */

   }                      /* if (!((SignalPtr->ComFilterType == COM_F_ALWAYS) ||
               (SignalPtr->ComFilterType == COM_F_NEVER))) */

#endif /* (COM_TMS_ENABLE == STD_ON) */

   /* check if Pdu is started */
   TS_GetBit(PduStatusFlagsPtr, COM_TXPDU_STARTED, uint8, BitRes);

   /* Only do further processing if the IPdu is started */
   if (BitRes == TRUE)
   {
#if (COM_SENDUPONAPICALL == STD_ON)

#if ((COM_TRANSF_PROP_TRIGGERED_ENABLE == STD_ON) || \
      (COM_TRANSF_PROP_TRIGGERED_OC_ENABLE == STD_ON) || \
      (COM_TMS_ENABLE == STD_ON) \
)
      boolean TmpTrigger = FALSE;

#if (COM_TMS_ENABLE == STD_ON)
      if (TRUE == forceTrigger)
      {
         TmpTrigger = TRUE;
      }
#endif /* (COM_TMS_ENABLE == STD_ON) */

#if (COM_TRANSF_PROP_TRIGGERED_ENABLE == STD_ON)
      if (COM_TRANSFER_PPROPERTY_TRIG == COM_GET_TX_SIGNAL_TRANSFER_PROPERTY(SignalPtr))
      {
         TmpTrigger = TRUE;
      }
#endif /* (COM_TRANSF_PROP_TRIGGERED_ENABLE == STD_ON) */

#if (COM_TRANSF_PROP_TRIGGERED_OC_ENABLE == STD_ON)
      if ((TRUE == trigger) && (COM_TRANSFER_PPROPERTY_TRIG_OC ==
            COM_GET_TX_SIGNAL_TRANSFER_PROPERTY(SignalPtr))
      )
      {
         TmpTrigger = TRUE;
      }
#endif /* (COM_TRANSF_PROP_TRIGGERED_OC_ENABLE == STD_ON) */

      if (TRUE == TmpTrigger)
      {
         /* make a call to eventually have it sent */
         retval = Com_EB_SendUponSendApiCall(
               PduId,
               IPduPtr
#if (COM_SIGNAL_GW_ENABLE == STD_ON)
               ,SendInMainFunctionTx
#endif /* (COM_SIGNAL_GW_ENABLE == STD_ON) */
         );

      }
#endif /* ((COM_TRANSF_PROP_TRIGGERED_ENABLE == STD_ON) || \
      (COM_TRANSF_PROP_TRIGGERED_OC_ENABLE == STD_ON) || \
      (COM_TMS_ENABLE == STD_ON)) */

#endif /* (COM_SENDUPONAPICALL == STD_ON) */
   }
   else                         /* <-- IPdu started / stopped --> */
   {
      /* If the IPdu is not started, do return error code */
      retval = COM_SERVICE_NOT_AVAILABLE;
   }


   DBG_COM_EB_SENDSIGNAL_EXIT(retval,SignalPtr,IPduPtr,PduId,SignalDataPtr);
   return retval;
}                               /* Com_EB_SendSignal */


#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_STOP_SEC_CODE
#include <MemMap.h>
#endif

