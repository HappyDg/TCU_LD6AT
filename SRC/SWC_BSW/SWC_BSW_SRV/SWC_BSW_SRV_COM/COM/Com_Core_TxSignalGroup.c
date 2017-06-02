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
 * MISRA-1) Deviated Rule: 14.6 (required)
 * For any iteration statement there shall be at most one break statement
 * used for loop termination.
 *
 * Reason:
 * Multiple breaks are used to reduce clutter of functions if all of the following
 * conditions take place:
 * a) The immediately abort of the loop is required because data are invalid and
 *    may lead to inconsistent code exection
 * b) The function is highly cluttered with preprocessor statements. Additional branches
 *    might lead to unreadable code.
 *
 */

/*==================[inclusions]============================================*/


#include <Com_Trace.h>
#include <TSAutosar.h>          /* EB specific standard types */
#include <ComStack_Types.h>     /* AUTOSAR Standard types */
#include <Com_Api.h>            /* Module public API */
#include <Com_Priv.h>           /* Module private API */
#include <TSMem.h>              /* TS_MemCpy */
#include <Com_Core_TxSignalGroup.h>  /* (group)signal(group) functions */

#if (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)

#if ((COM_TM_AVAILABLE == STD_ON) || (COM_TMS_ENABLE == STD_ON))
#include <Com_Core_TM.h>        /* Transmission Mode functions */
#endif /* ((COM_TM_AVAILABLE == STD_ON) || (COM_TMS_ENABLE == STD_ON)) */

#if (COM_TMS_ENABLE == STD_ON)
#include <Com_Filter.h>          /* Filter functions */
#endif /* (COM_TMS_ENABLE == STD_ON) */


#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_START_SEC_CODE
#include <MemMap.h>
#endif



/** \brief Com_EB_CreateWriteProp_GSig - initializes the internal
 * structure for the representation of a Tx-group signal
 * Preconditions:
 * - prior to this call, the COM module shall be initialized
 * \param[out] ComWritePropPtr - pointer where the result shall be stored
 * \param[in] dataPtr - pointer where the data shall be written
 * \param[in] SignalPtr - pointer to the description of the Tx group signal
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_CreateWriteProp_GSig
(
   P2VAR(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr,
   P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComTxGroupSignalType, AUTOMATIC, COM_APPL_CONST) GSignalPtr
);


#if (COM_TMS_ENABLE == STD_ON)
#if ((COM_SIGNAL_GW_ENABLE == STD_ON) || (COM_BASED_TRANSFORMER_SUPPORT_TX == STD_ON))
/** \brief Com_EB_SetGroupSignalTMSFlagOfSignalGroup - calculates the TMS of a
 * signal group
 * This function Com_EB_SetGroupSignalTMSFlagOfSignalGroup loops over all group
 * signals of the signal group and calculates the TMS of the signal group
 * Preconditions:
 * - COM must be initialized
 * - the signal must be ready to be gated (has to be updated)
 * \param[in] DestSignalGId - Id of signal group
 * \param[in] DestSignalGPtr - reference to the configuration of signal group
 * \param[in] SGArrayPtr - reference to the signal group array
 * \retval E_OK - success
 * \retval E_NOT_OK - Configuration error
 */
_COM_STATIC_ FUNC(uint8, COM_CODE) Com_EB_SetGroupSignalTMSFlagOfSignalGroup
(
   ComSignalGroupRefType DestSignalGId,
   P2CONST(ComTxSignalGroupType, AUTOMATIC, COM_APPL_CONST) DestSignalGPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SGArrayPtr
);
#endif /* ((COM_SIGNAL_GW_ENABLE == STD_ON) || (COM_BASED_TRANSFORMER_SUPPORT_TX == STD_ON)) */
#endif /* (COM_TMS_ENABLE == STD_ON) */


/** \brief Com_EB_CreateWriteProp_GSig - initializes the internal
 * structure for the representation of a Tx-group signal
 * Preconditions:
 * - prior to this call, the COM module shall be initialized
 * \param[out] ComWritePropPtr - pointer where the result shall be stored
 * \param[in] dataPtr - pointer where the data shall be written
 * \param[in] SignalPtr - pointer to the description of the Tx group signal
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_CreateWriteProp_GSig
(
   P2VAR(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr,
   P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr,
   P2CONST(ComTxGroupSignalType, AUTOMATIC, COM_APPL_CONST) GSignalPtr
)
{

   ComWritePropPtr->dataPtr = dataPtr;
#if (COM_SIGNAL_BYTE_ALIGN == STD_ON)
   ComWritePropPtr->ComSignalPositionInByte = GSignalPtr->ComSignalPositionInByte;
#elif (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
   ComWritePropPtr->ComSignalPositionInBit = GSignalPtr->ComSignalPositionInBit;
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_ON) */

#if (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)
   ComWritePropPtr->ComUpdateBitPositionInBit = 0U;
#endif /* (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) */

   ComWritePropPtr->size = GSignalPtr->ComBitSize;

#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
   ComWritePropPtr->endianness = COM_GET_TX_GROUP_SIGNAL_ENDIANNESS(GSignalPtr);
#endif

#if (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL)
   ComWritePropPtr->updateBit = FALSE;
#endif /* (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL) */

}                               /* Com_EB_CreateWriteProp_GSig */


/** \brief Com_EB_CalculateSignalGroupTM - It evaluates the TMS flags of the
 * group signals and calculates the TMS for the signal group and
 * initiates sending of the I-Pdu if necessary
 * Preconditions:
 * - COM must be initialized.
 * \param[in] SignalGId - id of signal group
 * \param[in] SignalGPtr - reference to configuration of signal group
 * \param[in] PduId - id of I-Pdu to which the signal group belongs
 * \param[in] IPduPtr - reference to the configuration of I-Pdu
 * \param[in] SendInMainFunctionTx - if TRUE, the Pdu is sent not now but
 * during the next Com_MainfunctionTx(), otherwise immediately
 * \param[in] forceTrigger - if TRUE the transmission is triggered
 * \retval E_OK if signal group could be copied to the I-Pdu
 * \retval COM_SERVICE_NOT_AVAILABLE if corresponding I-PDU group was stopped
 * or development error occurred
 */
_COM_STATIC_ FUNC(uint8, COM_CODE) Com_EB_CalculateSignalGroupTM
(
#if (COM_TMS_ENABLE == STD_ON)
   ComSignalGroupRefType SignalGId,
   P2CONST(ComTxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr,
#endif /* (COM_TMS_ENABLE == STD_ON) */
   ComIPduRefType PduId,
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
#if (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON)
   ,boolean SendInMainFunctionTx
#endif /* (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON) */
   ,boolean forceTrigger
);

/** \brief Com_EB_WriteShadowBuffer_Unaligned - writes unaligned part of a shadow buffer
 * to the I-Pdu
 * The service Com_EB_WriteShadowBuffer_Unaligned copies the value of unaligned parts
 * (first or last bits) of the signal group into the I-Pdu
 * Preconditions:
 * COM must be initialized.
 * *forceTriggerPtr shall be set to TRUE if the configuration or previous TOC calculations
 * indicate that the Pdu shall be triggered; else value shall be FALSE
 * \param[in] PduValPtr - reference to the value of the Pdu
 * \param[in] SGArrayValPtr - reference to the value in a signal group array
 * \param[in] SignalGPtr - reference to the configuration of the signal group
 * \param[in] TOCMaskPtr - reference the mask which defines the relevant bits
 * for the TRIGGERED ON CHANGE calculation
 * \param[inout] forceTriggerPtr - if the value changed and it is relevant for the
 * TRIGGERED ON CHANGE calculation, then the value is set to TRUE, else the value remains.
 * \param[in] writeMask mask which shall be applied to write the value to the Pdu
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_WriteShadowBuffer_Unaligned
(
   P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) PduValPtr,
   P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) SGArrayValPtr,
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   P2CONST(ComTxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr,
   P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) TOCMaskPtr,
   P2VAR(boolean, AUTOMATIC, AUTOMATIC) forceTriggerPtr,
#endif
   uint8 writeMask
);

/** \brief Com_EB_WriteShadowBuffer - writes the shadow buffer to the I-Pdu
 * The service Com_EB_WriteShadowBuffer copies the value of the signal group
 * into the I-Pdu
 * Preconditions:
 * COM must be initialized.
 * \param[in] SignalGPtr - reference to configuration of the signal group
 * \param[in] IPduPtr - reference to configuration of the I-Pdu to which the
 * \param[in] SGArrayPtr - reference to the signal group array
 * Signal Group is stored
 * signal group belongs
 * \retval TRUE if the value has changed, else FALSE
 */
_COM_STATIC_ FUNC(boolean, COM_CODE) Com_EB_WriteShadowBuffer
(
   P2CONST(ComTxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr,
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
   P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) SGArrayPtr
);


#if (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON)
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_UpdateShadowSignal_Bool
(
#if (COM_TMS_ENABLE == STD_ON)
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr,
   P2VAR(boolean, AUTOMATIC, AUTOMATIC) TMSResultPtr,
#endif /* (COM_TMS_ENABLE == STD_ON) */
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
);
#endif /* (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON)
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_UpdateShadowSignal_Uint8
(
#if (COM_TMS_ENABLE == STD_ON)
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr,
   P2VAR(boolean, AUTOMATIC, AUTOMATIC) TMSResultPtr,
#endif /* (COM_TMS_ENABLE == STD_ON) */
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
);
#endif /* (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON)
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_UpdateShadowSignal_Uint16
(
#if (COM_TMS_ENABLE == STD_ON)
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr,
   P2VAR(boolean, AUTOMATIC, AUTOMATIC) TMSResultPtr,
#endif /* (COM_TMS_ENABLE == STD_ON) */
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
);
#endif /* (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON)
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_UpdateShadowSignal_Uint32
(
#if (COM_TMS_ENABLE == STD_ON)
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr,
   P2VAR(boolean, AUTOMATIC, AUTOMATIC) TMSResultPtr,
#endif /* (COM_TMS_ENABLE == STD_ON) */
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
);
#endif /* (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON)
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_UpdateShadowSignal_Sint8
(
#if (COM_TMS_ENABLE == STD_ON)
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr,
   P2VAR(boolean, AUTOMATIC, AUTOMATIC) TMSResultPtr,
#endif /* (COM_TMS_ENABLE == STD_ON) */
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
);
#endif /* (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON)
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_UpdateShadowSignal_Sint16
(
#if (COM_TMS_ENABLE == STD_ON)
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr,
   P2VAR(boolean, AUTOMATIC, AUTOMATIC) TMSResultPtr,
#endif /* (COM_TMS_ENABLE == STD_ON) */
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
);
#endif /* (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON)
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_UpdateShadowSignal_Sint32
(
#if (COM_TMS_ENABLE == STD_ON)
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr,
   P2VAR(boolean, AUTOMATIC, AUTOMATIC) TMSResultPtr,
#endif /* (COM_TMS_ENABLE == STD_ON) */
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
);
#endif /* (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON)
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_UpdateShadowSignal_Bool
(
#if (COM_TMS_ENABLE == STD_ON)
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr,
   P2VAR(boolean, AUTOMATIC, AUTOMATIC) TMSResultPtr,
#endif /* (COM_TMS_ENABLE == STD_ON) */
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
)
{

#if (COM_TMS_ENABLE == STD_ON)
   if (TRUE == (COM_F_NON_TRIVIAL(ComFilterPropPtr->ComFilterType)))
   {
      *TMSResultPtr = Com_EB_FilterBoolean(ComFilterPropPtr, SignalDataPtr);
   }
   else
   {
      *TMSResultPtr = FALSE;
   }
#endif /* (COM_TMS_ENABLE == STD_ON) */

   /* Write the value to the I-Pdu */
   Com_EB_WriteToPduOrSBuffBool(
      SignalDataPtr,
      ComWritePropPtr
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
      ,triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
   );

   return;
}                               /* Com_EB_UpdateShadowSignal_Bool */
#endif /* (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON)
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_UpdateShadowSignal_Uint8
(
#if (COM_TMS_ENABLE == STD_ON)
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr,
   P2VAR(boolean, AUTOMATIC, AUTOMATIC) TMSResultPtr,
#endif /* (COM_TMS_ENABLE == STD_ON) */
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
)
{

#if (COM_TMS_ENABLE == STD_ON)
   if (TRUE == (COM_F_NON_TRIVIAL(ComFilterPropPtr->ComFilterType)))
   {
      *TMSResultPtr = Com_EB_FilterUint8(ComFilterPropPtr, SignalDataPtr);
   }
   else
   {
      *TMSResultPtr = FALSE;
   }
#endif /* (COM_TMS_ENABLE == STD_ON) */

   /* Write the value to the I-Pdu */
   Com_EB_WriteToPduOrSBuff8Bit(
      SignalDataPtr,
      ComWritePropPtr
#if (COM_CHECK_VALUE_SIZE == STD_ON)
      ,TRUE
#endif /* (COM_CHECK_VALUE_SIZE == STD_ON) */
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
      ,triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
   );
}                               /* Com_EB_UpdateShadowSignal_Uint8 */
#endif /* (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON)
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_UpdateShadowSignal_Uint16
(
#if (COM_TMS_ENABLE == STD_ON)
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr,
   P2VAR(boolean, AUTOMATIC, AUTOMATIC) TMSResultPtr,
#endif /* (COM_TMS_ENABLE == STD_ON) */
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
)
{
#if (COM_TMS_ENABLE == STD_ON)
   if (TRUE == (COM_F_NON_TRIVIAL(ComFilterPropPtr->ComFilterType)))
   {
      *TMSResultPtr = Com_EB_FilterUint16(ComFilterPropPtr, SignalDataPtr);
   }
   else
   {
      *TMSResultPtr = FALSE;
   }
#endif /* (COM_TMS_ENABLE == STD_ON) */

   /* Write the value to the I-Pdu */
   Com_EB_WriteToPduOrSBuff16Bit(
      SignalDataPtr,
      ComWritePropPtr
#if (COM_CHECK_VALUE_SIZE == STD_ON)
      ,TRUE
#endif /* (COM_CHECK_VALUE_SIZE == STD_ON) */
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
      ,triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
   );

}                               /* Com_EB_UpdateShadowSignal_Uint16 */
#endif /* (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON)
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_UpdateShadowSignal_Uint32
(
#if (COM_TMS_ENABLE == STD_ON)
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr,
   P2VAR(boolean, AUTOMATIC, AUTOMATIC) TMSResultPtr,
#endif /* (COM_TMS_ENABLE == STD_ON) */
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
)
{
#if (COM_TMS_ENABLE == STD_ON)
   if (TRUE == (COM_F_NON_TRIVIAL(ComFilterPropPtr->ComFilterType)))
   {
      *TMSResultPtr = Com_EB_FilterUint32(ComFilterPropPtr, SignalDataPtr);
   }
   else
   {
      *TMSResultPtr = FALSE;
   }
#endif /* (COM_TMS_ENABLE == STD_ON) */

   /* Write the value to the I-Pdu */
   Com_EB_WriteToPduOrSBuff32Bit(
      SignalDataPtr,
      ComWritePropPtr
#if (COM_CHECK_VALUE_SIZE == STD_ON)
      ,TRUE
#endif /* (COM_CHECK_VALUE_SIZE == STD_ON) */
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
      ,triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
   );

}                               /* Com_EB_UpdateShadowSignal_Uint32 */
#endif /* (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON)
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_UpdateShadowSignal_Sint8
(
#if (COM_TMS_ENABLE == STD_ON)
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr,
   P2VAR(boolean, AUTOMATIC, AUTOMATIC) TMSResultPtr,
#endif /* (COM_TMS_ENABLE == STD_ON) */
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
)
{

#if (COM_TMS_ENABLE == STD_ON)
   if (TRUE == (COM_F_NON_TRIVIAL(ComFilterPropPtr->ComFilterType)))
   {
      *TMSResultPtr = Com_EB_FilterSint8(ComFilterPropPtr, SignalDataPtr);
   }
   else
   {
      *TMSResultPtr = FALSE;
   }
#endif /* (COM_TMS_ENABLE == STD_ON) */

   /* Write the value to the I-Pdu */
   Com_EB_WriteToPduOrSBuff8Bit(
      SignalDataPtr,
      ComWritePropPtr
#if (COM_CHECK_VALUE_SIZE == STD_ON)
      ,FALSE
#endif /* (COM_CHECK_VALUE_SIZE == STD_ON) */
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
      ,triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
   );
}                               /* Com_EB_UpdateShadowSignal_Sint8 */
#endif /* (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON)
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_UpdateShadowSignal_Sint16
(
#if (COM_TMS_ENABLE == STD_ON)
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr,
   P2VAR(boolean, AUTOMATIC, AUTOMATIC) TMSResultPtr,
#endif /* (COM_TMS_ENABLE == STD_ON) */
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
)
{
#if (COM_TMS_ENABLE == STD_ON)
   if (TRUE == (COM_F_NON_TRIVIAL(ComFilterPropPtr->ComFilterType)))
   {
      *TMSResultPtr = Com_EB_FilterSint16(ComFilterPropPtr, SignalDataPtr);
   }
   else
   {
      *TMSResultPtr = FALSE;
   }
#endif /* (COM_TMS_ENABLE == STD_ON) */

   /* Write the value to the I-Pdu */
   Com_EB_WriteToPduOrSBuff16Bit(
      SignalDataPtr,
      ComWritePropPtr
#if (COM_CHECK_VALUE_SIZE == STD_ON)
      ,FALSE
#endif /* (COM_CHECK_VALUE_SIZE == STD_ON) */
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
      ,triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
   );

}                               /* Com_EB_UpdateShadowSignal_Sint16 */
#endif /* (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON)
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_UpdateShadowSignal_Sint32
(
#if (COM_TMS_ENABLE == STD_ON)
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr,
   P2VAR(boolean, AUTOMATIC, AUTOMATIC) TMSResultPtr,
#endif /* (COM_TMS_ENABLE == STD_ON) */
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
   P2CONST(ComCommonWritePropType, AUTOMATIC, AUTOMATIC) ComWritePropPtr
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   ,P2VAR(boolean, AUTOMATIC, AUTOMATIC) triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
)
{
#if (COM_TMS_ENABLE == STD_ON)
   if (TRUE == (COM_F_NON_TRIVIAL(ComFilterPropPtr->ComFilterType)))
   {
      *TMSResultPtr = Com_EB_FilterSint32(ComFilterPropPtr, SignalDataPtr);
   }
   else
   {
      *TMSResultPtr = FALSE;
   }
#endif /* (COM_TMS_ENABLE == STD_ON) */

   /* Write the value to the I-Pdu */
   Com_EB_WriteToPduOrSBuff32Bit(
      SignalDataPtr,
      ComWritePropPtr
#if (COM_CHECK_VALUE_SIZE == STD_ON)
      ,FALSE
#endif /* (COM_CHECK_VALUE_SIZE == STD_ON) */
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
      ,triggerPtr
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
   );

}                               /* Com_EB_UpdateShadowSignal_Sint32 */
#endif /* (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON) */



TS_MOD_PRIV_DEFN FUNC(void, COM_CODE) Com_EB_UpdateShadowSignal(
   P2CONST(ComTxGroupSignalType, AUTOMATIC, COM_APPL_CONST) GSignalPtr,
#if (COM_TMS_ENABLE == STD_ON)
   ComSignalGroupRefType SignalGId,
#endif /* (COM_TMS_ENABLE == STD_ON) */
   P2CONST(ComTxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
)
{
   /* reference to RAM where the value of the signal group is stored */
   ComRAMIdxType ComSignalGroupValueRef = SignalGPtr->ComSignalGroupValueRef;

   /* signal type of the group signal */
   Com_TS_SignalTypeType SignalType = COM_GET_TX_GROUP_SIGNAL_SIGNAL_TYPE(GSignalPtr);

   ComCommonWritePropType ComWriteProp;

   CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) dataPtr =
         &Com_gDataMemPtr[(ComSignalGroupValueRef)];

#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   boolean trigger = FALSE;
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */

#if (COM_TMS_ENABLE == STD_ON)
   boolean TMSResult = TRUE;
   ComCommonFilterPropertiesType ComFilterProp;
#endif /* (COM_TMS_ENABLE == STD_ON) */

   DBG_COM_EB_UPDATESHADOWSIGNAL_ENTRY(GSignalPtr,SignalGPtr,SignalDataPtr);

   Com_EB_CreateWriteProp_GSig(&ComWriteProp, dataPtr, GSignalPtr);

#if (COM_TMS_ENABLE == STD_ON)
   Com_EB_CreateFilterProp(
      &ComFilterProp,
      GSignalPtr->ComFilterSignalValueRef,
      GSignalPtr->ComFilterRef,
      GSignalPtr->ComFilterType);
#endif /* (COM_TMS_ENABLE == STD_ON) */

   switch(SignalType)
   {
#if (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON)
   case COM_BOOLEAN:
   {

      Com_EB_UpdateShadowSignal_Bool(
#if (COM_TMS_ENABLE == STD_ON)
            &ComFilterProp,
            &TMSResult,
#endif /* (COM_TMS_ENABLE == STD_ON) */
            SignalDataPtr,
            &ComWriteProp
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
            , &trigger
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
      );
      break;

   }                            /* case COM_BOOLEAN: */
#endif /* (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON) */
#if (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON)
   case COM_UINT8:
   {

      Com_EB_UpdateShadowSignal_Uint8(
#if (COM_TMS_ENABLE == STD_ON)
            &ComFilterProp,
            &TMSResult,
#endif /* (COM_TMS_ENABLE == STD_ON) */
            SignalDataPtr,
            &ComWriteProp
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
            , &trigger
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
      );
      break;

   }                            /* case COM_UINT8: */
#endif /* (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON) */
#if (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON)
   case COM_UINT16:
   {

      Com_EB_UpdateShadowSignal_Uint16(
#if (COM_TMS_ENABLE == STD_ON)
            &ComFilterProp,
            &TMSResult,
#endif /* (COM_TMS_ENABLE == STD_ON) */
            SignalDataPtr,
            &ComWriteProp
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
            , &trigger
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
      );
      break;

   }                            /* case COM_UINT16: */
#endif /* (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON) */
#if (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON)
   case COM_UINT32:
   {

      Com_EB_UpdateShadowSignal_Uint32(
#if (COM_TMS_ENABLE == STD_ON)
            &ComFilterProp,
            &TMSResult,
#endif /* (COM_TMS_ENABLE == STD_ON) */
            SignalDataPtr,
            &ComWriteProp
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
            , &trigger
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
      );
      break;

   }                            /* case COM_UINT32: */
#endif /* (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON) */
#if (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON)
   case COM_SINT8:
   {

      Com_EB_UpdateShadowSignal_Sint8(
#if (COM_TMS_ENABLE == STD_ON)
            &ComFilterProp,
            &TMSResult,
#endif /* (COM_TMS_ENABLE == STD_ON) */
            SignalDataPtr,
            &ComWriteProp
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
            , &trigger
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
      );
      break;

   }                            /* case COM_SINT8: */
#endif /* (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON) */
#if (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON)
   case COM_SINT16:
   {

      Com_EB_UpdateShadowSignal_Sint16(
#if (COM_TMS_ENABLE == STD_ON)
            &ComFilterProp,
            &TMSResult,
#endif /* (COM_TMS_ENABLE == STD_ON) */
            SignalDataPtr,
            &ComWriteProp
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
            , &trigger
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
      );
      break;

   }                            /* case COM_SINT16: */
#endif /* (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON) */
#if (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON)
   case COM_SINT32:
   {

      Com_EB_UpdateShadowSignal_Sint32(
#if (COM_TMS_ENABLE == STD_ON)
            &ComFilterProp,
            &TMSResult,
#endif /* (COM_TMS_ENABLE == STD_ON) */
            SignalDataPtr,
            &ComWriteProp
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
            , &trigger
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
      );
      break;

   }                            /* case COM_SINT32: */
#endif /* (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON) */
#if (COM_SIGNAL_TYPE_UINT8_N_ENABLE == STD_ON)
   case COM_UINT8_N:
   {

      ComSignalDescByteType StartingByte;

      /* get position of the signal within the Signal Group */
      COM_GET_GROUP_SIGNAL_POS_ALIG(GSignalPtr, StartingByte);

      {
         /* copy value from RAM */
         Com_EB_WriteToPduOrSBuffByteArray(
               (P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT))
               &Com_gDataMemPtr[(ComSignalGroupValueRef + StartingByte)],
               (P2CONST(uint8, AUTOMATIC, COM_APPL_DATA))
               SignalDataPtr,
               GSignalPtr->ComBitSize
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
               ,&trigger
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */
         );
      }
      /* NOTE: no filter mechanism has to be added here. If the filter would
       * be ALWAYS, the filter would always evaluate to true and therefore the
       * generator ommits all filters for the I-Pdu (the initial value of the
       * TMS Flag of the I-Pdu is set to TRUE).
       * If the filter would be NEVER the filter would never evaluate to
       * TRUE */

      break;
   }                            /* case COM_UINT8_N: */
#endif /* (COM_SIGNAL_TYPE_UINT8_N_ENABLE == STD_ON) */

   /* CHECK: NOPARSE */
   default:
      COM_UNREACHABLE_CODE_ASSERT(COM_INTERNAL_API_ID);
      break;
      /* CHECK: PARSE */

   }                            /* switch(SignalType) */


#if (COM_TMS_ENABLE == STD_ON)

   /* check if this group signal of the Signal Group contributes to TMS */
   /* In case the signal has the filter ALWAYS, the TM is always TRUE; -> does not contribute */
   /* In case the signal has the filter COM_F_NEVER, the TM does not depend on this signal */
   if ((GSignalPtr->ComFilterType != COM_F_ALWAYS) && (GSignalPtr->ComFilterType != COM_F_NEVER))
   {

      /* calculate the TMSFlag */
      Com_EB_CalculateGroupSignalTM(
            GSignalPtr,
            SignalGId,
            SignalGPtr,
            TMSResult);

   }
#else
   TS_PARAM_UNUSED(SignalGPtr);
#endif /* (COM_TMS_ENABLE == STD_ON) */


   DBG_COM_EB_UPDATESHADOWSIGNAL_EXIT(GSignalPtr,SignalGPtr,SignalDataPtr);
   return;
}                               /* Com_EB_UpdateShadowSignal */

/** \brief Com_EB_SendSignalGroup - internal function for sending a signal group
 * The service Com_EB_SendSignalGroup sends a signal group. It evaluates the
 * TMS flags of the group signals and calculates the TMS for the signal group
 * Preconditions:
 * - COM must be initialized.
 * \param[in] SGArrayPtr - not used
 * \param[in] SGArrayPtrLength - not used
 * \param[in] SignalGId - Id of signal group
 * \param[in] SignalGPtr - reference to configuration of signal group
 * \param[in] PduId - id of I-Pdu to which the signal group belongs
 * \param[in] IPduPtr - reference to the configuration of I-Pdu
 * \param[in] SendInMainFunctionTx - if TRUE, the Pdu is sent not now but
 * during the next Com_MainfunctionTx(), otherwise immediately
 * \retval E_OK if signal group could be copied to the I-Pdu
 * \retval COM_SERVICE_NOT_AVAILABLE if corresponding I-PDU group was stopped
 * (or service failed due to development error)
 */
TS_MOD_PRIV_DEFN FUNC(uint8, COM_CODE) Com_EB_SendSignalGroup
(
   P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) SGArrayPtr,
   uint16 SGArrayPtrLength,
#if (COM_TMS_ENABLE == STD_ON)
   ComSignalGroupRefType SignalGId,
#endif /* (COM_TMS_ENABLE == STD_ON) */
   P2CONST(ComTxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr,
   ComIPduRefType PduId,
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
#if (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON)
   ,boolean SendInMainFunctionTx
#endif /* (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON) */
)
{

   const ComRAMIdxType ComSignalGroupValueRef = SignalGPtr->ComSignalGroupValueRef;

   uint8 retval = COM_SERVICE_NOT_AVAILABLE;

   DBG_COM_EB_SENDSIGNALGROUP_ENTRY(SignalGPtr,PduId,IPduPtr);

   TS_PARAM_UNUSED(SGArrayPtr);
   TS_PARAM_UNUSED(SGArrayPtrLength);

#if (COM_DEV_ERROR_DETECT == STD_ON)
#if (COM_BASED_TRANSFORMER_SUPPORT_TX == STD_ON)
   if (ComSignalGroupValueRef == COM_RAM_SIZE_MAX)
   {
      /* the signal group has no shadow buffer assigned an shall
       * only be used with the Com_SendSignalGroupArray() */
      COM_DET_REPORTERROR(COM_E_PARAM, COMServiceId_SendSignalGroup);
   }
   else
#endif /* (COM_BASED_TRANSFORMER_SUPPORT_TX == STD_ON) */
#endif /* (COM_DEV_ERROR_DETECT == STD_ON) */
   {

      boolean forceTrigger =
            Com_EB_WriteShadowBuffer(SignalGPtr, IPduPtr, &Com_gDataMemPtr[(ComSignalGroupValueRef)]);

      {
         retval = Com_EB_CalculateSignalGroupTM(
#if (COM_TMS_ENABLE == STD_ON)
               SignalGId,
               SignalGPtr,
#endif /* (COM_TMS_ENABLE == STD_ON) */
               PduId,
               IPduPtr
#if (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON)
               ,SendInMainFunctionTx
#endif /* (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON) */
               ,forceTrigger
         );

      }
   }

   DBG_COM_EB_SENDSIGNALGROUP_EXIT(retval,SignalGPtr,PduId,IPduPtr);
   return retval;
}                               /* Com_EB_SendSignalGroup */

#if (COM_BASED_TRANSFORMER_SUPPORT_TX == STD_ON)

TS_MOD_PRIV_DEFN FUNC(uint8, COM_CODE) Com_EB_SendSignalGroupArray_DETCheck
(
   P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) SGArrayPtr,
   uint16 SGArrayLength,
#if (COM_TMS_ENABLE == STD_ON)
   ComSignalGroupRefType SignalGId,
#endif /* (COM_TMS_ENABLE == STD_ON) */
   P2CONST(ComTxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr,
   ComIPduRefType PduId,
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
#if (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON)
   ,boolean SendInMainFunctionTx
#endif /* (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON) */
)
{

   uint8 retval = COM_SERVICE_NOT_AVAILABLE;

#if (COM_DEV_ERROR_DETECT == STD_ON)
   uint16 length = SignalGPtr->ComByteSize;

   if (SignalGPtr->ComBitMaskFirstPart > 0U)
   {
      length++;
   }

   if (SignalGPtr->ComBitMaskLastPart > 0U)
   {
      length++;
   }

   if (SGArrayPtr == NULL_PTR)
   {
      retval = COM_SERVICE_NOT_AVAILABLE;
      COM_DET_REPORTERROR(COM_E_PARAM_POINTER, COMServiceId_SendSignalGroupArray);
   }
   else if (SGArrayLength != length)
   {
      retval = COM_SERVICE_NOT_AVAILABLE;
      COM_DET_REPORTERROR(COM_E_PARAM, COMServiceId_SendSignalGroupArray);
   }
   else
#endif /* COM_DEV_ERROR_DETECT */
   {
      TS_PARAM_UNUSED(SGArrayLength);

      retval = Com_EB_SendSignalGroupArray(
            SGArrayPtr,
#if (COM_TMS_ENABLE == STD_ON)
            SignalGId,
#endif /* (COM_TMS_ENABLE == STD_ON) */
            SignalGPtr,
            PduId,
            IPduPtr
#if (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON)
            ,SendInMainFunctionTx
#endif /* (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON) */
      );
   }


   return retval;

}                               /* Com_EB_SendSignalGroupArray */

#endif /* (COM_BASED_TRANSFORMER_SUPPORT_TX == STD_ON) */

#if ((COM_BASED_TRANSFORMER_SUPPORT_TX == STD_ON) || \
      ((COM_SIGNAL_GW_ENABLE == STD_ON)))

TS_MOD_PRIV_DEFN FUNC(uint8, COM_CODE) Com_EB_SendSignalGroupArray
(
   P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) SGArrayPtr,
#if (COM_TMS_ENABLE == STD_ON)
   ComSignalGroupRefType SignalGId,
#endif /* (COM_TMS_ENABLE == STD_ON) */
   P2CONST(ComTxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr,
   ComIPduRefType PduId,
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
#if (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON)
   ,boolean SendInMainFunctionTx
#endif /* (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON) */
)
{
   uint8 retval = COM_SERVICE_NOT_AVAILABLE;

   DBG_COM_EB_SENDSIGNALGROUPARRAY_ENTRY(SGArrayPtr,SignalGPtr,PduId,IPduPtr);

#if (COM_TMS_ENABLE == STD_ON)
   /* set the TMSFlags of the group signals */
   retval = Com_EB_SetGroupSignalTMSFlagOfSignalGroup(
         SignalGId,
         SignalGPtr,
         SGArrayPtr);

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
   /* CHECK: NOPARSE */
   if (E_OK != retval)
   {
      /* Com_EB_SetGroupSignalTMSFlagOfSignalGroup() only returns
       * E_NOT_OK in case of an invalid configuration */
   }
   else
      /* CHECK: PARSE */
#endif /*(COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */
#endif /* (COM_TMS_ENABLE == STD_ON) */
   {
      /* copy the value to the I-Pdu buffer */
      boolean forceTrigger =
            Com_EB_WriteShadowBuffer(SignalGPtr, IPduPtr, SGArrayPtr);

      /* calculate the TM of the signal group
       * and send if required */
      retval = Com_EB_CalculateSignalGroupTM(
#if (COM_TMS_ENABLE == STD_ON)
            SignalGId,
            SignalGPtr,
#endif /* (COM_TMS_ENABLE == STD_ON) */
            PduId,
            IPduPtr
#if (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON)
            ,SendInMainFunctionTx
#endif /* (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON) */
            ,forceTrigger
      );
   }

   DBG_COM_EB_SENDSIGNALGROUPARRAY_EXIT(retval,SGArrayPtr,SignalGPtr,PduId,IPduPtr);

   return retval;
}

#endif /* ((COM_BASED_TRANSFORMER_SUPPORT_TX == STD_ON) || \
      ((COM_SIGNAL_GW_ENABLE == STD_ON))) */


/** \brief Com_EB_CalculateSignalGroupTM - It evaluates the TMS flags of the
 * group signals and calculates the TMS for the signal group and
 * initiates sending of the I-Pdu if necessary
 * Preconditions:
 * - COM must be initialized.
 * \param[in] SignalGId - id of signal group
 * \param[in] SignalGPtr - reference to configuration of signal group
 * \param[in] PduId - id of I-Pdu to which the signal group belongs
 * \param[in] IPduPtr - reference to the configuration of I-Pdu
 * \param[in] SendInMainFunctionTx - if TRUE, the Pdu is sent not now but
 * during the next Com_MainfunctionTx(), otherwise immediately
 * \param[in] forceTrigger - if TRUE the transmission is triggered
 * \retval E_OK if signal group could be copied to the I-Pdu
 * \retval COM_SERVICE_NOT_AVAILABLE if corresponding I-PDU group was stopped
 * or development error occurred
 */
_COM_STATIC_ FUNC(uint8, COM_CODE) Com_EB_CalculateSignalGroupTM
(
#if (COM_TMS_ENABLE == STD_ON)
   ComSignalGroupRefType SignalGId,
   P2CONST(ComTxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr,
#endif /* (COM_TMS_ENABLE == STD_ON) */
   ComIPduRefType PduId,
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
#if (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON)
   ,boolean SendInMainFunctionTx
#endif /* (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON) */
   ,boolean forceTrigger
)
{
   uint8 retval = E_OK;
   uint8 BitRes;

   boolean transmit = forceTrigger;

   /* Flag byte Ptr for status byte of I-Pdu */
   CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) PduStatusFlagsPtr =
         &Com_gDataMemPtr[(Com_gConfigPtr->ComTxIPduStatusBase + PduId)];

#if (COM_TMS_ENABLE == STD_ON)

   /* Flag byte Ptr for status byte of group signal */
   CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT)SGFlagPtr =
         COM_TXSG_TMS_MIGHT_CHANGE_FLAG_ADDRESS(SignalGId);

   boolean TMMightChange;

   DBG_COM_EB_CALCULATESIGNALGROUPTM_ENTRY(SignalGPtr,PduId,IPduPtr);

   /* Critical section */
   Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();


   /* get the TM might change flag of Signal Group */
   TS_GetBit(SGFlagPtr, COM_TXSG_TMSMIGHTCHANGE, uint8, TMMightChange);

   if (TMMightChange == TRUE)
   {
      /* Although the might change flag is set, it does not mean that the
       * state really has changed. We have to check if at least on signal
       * has a positive result */
      CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT)SignalGTMFlagsBase =
            (&Com_gDataMemPtr[(SignalGPtr->ComSignalGTMSFlagsRef)]);
      uint16 j = 0U;
      boolean newResult = FALSE;
      boolean CurrentTMSG;
      uint16 numberOfFlagBytes;

      /* clear the COM_TXSG_TMSMIGHTCHANGE flag */
      Com_ClearBitUInt8(SGFlagPtr, COM_TXSG_TMSMIGHTCHANGE);

      /* get the number of Bytes which hold the TM flags of the Signal group */
      numberOfFlagBytes = SignalGPtr->ComGroupSignalWithFilterRefNum / 8U;
      if ((SignalGPtr->ComGroupSignalWithFilterRefNum % 8U) > 0U)
      {
         numberOfFlagBytes++;
      }

      /* check if at least one bit is set */
      for(j = 0U; j < numberOfFlagBytes; j++)
      {
         if (SignalGTMFlagsBase[j] > 0U)
         {
            /* at least one bit is set -> TM is TRUE */
            newResult = TRUE;
         }
      }                            /* for(j = 0U; j < numberOfFlagBytes; j++) */

      /* get the current TMS status of Signal Group */
      TS_GetBit(SGFlagPtr, COM_TXSG_TMSSTATE, uint8, CurrentTMSG);

      if (newResult != CurrentTMSG)
      {

         /* store result of signal group */
         if (newResult == TRUE)
         {
            Com_SetBitUInt8((&Com_gDataMemPtr[(IPduPtr->ComIPduTMSFlagsRef) +
                                              (SignalGPtr->ComPositionOfTMSFlag / 8U)]),
                                              ((uint8) (SignalGPtr->ComPositionOfTMSFlag % 8U)));

            Com_SetBitUInt8(SGFlagPtr, COM_TXSG_TMSSTATE);
         }
         else
         {
            Com_ClearBitUInt8((&Com_gDataMemPtr[(IPduPtr->ComIPduTMSFlagsRef) +
                                                (SignalGPtr->ComPositionOfTMSFlag / 8U)]),
                                                ((uint8) (SignalGPtr->ComPositionOfTMSFlag % 8U)));

            Com_ClearBitUInt8(SGFlagPtr, COM_TXSG_TMSSTATE);
         }
      }                         /* if (newResult != CurrentTM) */


      /* always recalculate the TM of I-PDU since it might have changed due to a call to
       * Com_SwitchIpduTxMode() */
      {

         boolean newTM;
         boolean CurrentTMIPDU;

         /* get the current TMS status of I-PDU */
         TS_GetBit(PduStatusFlagsPtr, COM_TXPDU_TMSSTATE, uint8, CurrentTMIPDU);

         /* calculate if the TM of the Pdu changed */
         /* we are already in a critical section -> no need to protect the function */
         newTM = Com_EB_CalculateTM(IPduPtr);

         if (newTM != CurrentTMIPDU)
         {
            /* change the TM of the I-Pdu */
            if (newTM == TRUE)
            {
               /* set the flag in the IPdu */
               Com_SetBitUInt8(PduStatusFlagsPtr, COM_TXPDU_TMSSTATE);
            }
            else
            {
               /* clear the flag in the IPdu */
               Com_ClearBitUInt8(PduStatusFlagsPtr, COM_TXPDU_TMSSTATE);
            }

            /* Set the changed flag of the I-Pdu */
            Com_SetBitUInt8(PduStatusFlagsPtr, COM_TXPDU_TMSCHANGED);

            /* COM582: If a change of the TMS causes a change to the
             * transmission mode DIRECT, an immediate (respecting the MDT)
             * direct/ n-times transmission to the underlying layer shall
             * be initiated.
             * -> shall also initiate transmission if signal has
             * transfer property Pending */
            {
               uint8 const AktTM =
                     COM_GET_COM_TX_MODE(newTM, IPduPtr->ComTxModeModes);

               if ((COM_TX_MODE_MODE_DIRECT == AktTM) || (COM_TX_MODE_MODE_N_TIMES == AktTM))
               {
                  transmit = TRUE;
               }

            }

         }                      /* if (newTM != CurrentTM) */

      }

   }                            /* (TMMightChange) */

   /* Leave critical section */
   Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();
#else
   DBG_COM_EB_CALCULATESIGNALGROUPTM_ENTRY(SignalGPtr,PduId,IPduPtr);
#endif /* (COM_TMS_ENABLE == STD_ON) */
   /* There is a minor race here; see Com_SendSignal */

   /* Only do further processing if the IPdu is started */
   TS_GetBit(PduStatusFlagsPtr, COM_TXPDU_STARTED, uint8, BitRes);

   if (BitRes == TRUE)
   {
#if (COM_SENDUPONAPICALL == STD_ON)

      if (TRUE == transmit)
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

#endif /* (COM_SENDUPONAPICALL == STD_ON) */
   }
   else                         /* <-- IPdu started / stopped --> */
   {
      /* If the IPdu is not started, do return error code */
      retval = COM_SERVICE_NOT_AVAILABLE;
   }
   DBG_COM_EB_CALCULATESIGNALGROUPTM_EXIT(retval,SignalGPtr,PduId,IPduPtr);
   return retval;
}                               /* Com_EB_CalculateSignalGroupTM */


/** \brief Com_EB_WriteShadowBuffer_Unaligned - writes unaligned part of a shadow buffer
 * to the I-Pdu
 * The service Com_EB_WriteShadowBuffer_Unaligned copies the value of unaligned parts
 * (first or last bits) of the signal group into the I-Pdu
 * Preconditions:
 * COM must be initialized.
 * *forceTriggerPtr shall be set to TRUE if the configuration or previous TOC calculations
 * indicate that the Pdu shall be triggered; else value shall be FALSE
 * \param[in] PduValPtr - reference to the value of the Pdu
 * \param[in] SGArrayValPtr - reference to the value in a signal group array
 * \param[in] SignalGPtr - reference to the configuration of the signal group
 * \param[in] TOCMaskPtr - reference the mask which defines the relevant bits
 * for the TRIGGERED ON CHANGE calculation
 * \param[inout] forceTriggerPtr - if the value changed and it is relevant for the
 * TRIGGERED ON CHANGE calculation, then the value is set to TRUE, else the value remains.
 * \param[in] writeMask mask which shall be applied to write the value to the Pdu
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_WriteShadowBuffer_Unaligned
(
   P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) PduValPtr,
   P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) SGArrayValPtr,
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   P2CONST(ComTxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr,
   P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) TOCMaskPtr,
   P2VAR(boolean, AUTOMATIC, AUTOMATIC) forceTriggerPtr,
#endif
   uint8 writeMask
)
{

   uint8 valuePdu = *PduValPtr;
   uint8 valueShadowBuffer = *SGArrayValPtr;

   /* clear the unused bits */
   valuePdu = (valuePdu & (uint8)(~(writeMask)));
   valueShadowBuffer = (valueShadowBuffer & writeMask);

#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
   {
      if(COM_TRANSFER_PPROPERTY_TRIG_OC ==
            COM_GET_COM_TX_SIGNAL_GROUP_TRANSFER_PROPERTY(SignalGPtr))
      {
      /* calculate value for comparison */
      uint8 valuePduCmp = *PduValPtr;
      valuePduCmp = (valuePduCmp & writeMask);

      /* check if the relevant parts have changed */
      COM_TRIGGERED_OC_BYTE_VALUE_CHANGED_TOCMASK(
                  valuePduCmp, valueShadowBuffer,  TOCMaskPtr[0], *forceTriggerPtr);
      }

   }
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */

   /* Copy to Pdu */
   *PduValPtr =
      (uint8)(valuePdu | valueShadowBuffer);

}                               /* Com_EB_WriteShadowBuffer_Unaligned */


/** \brief Com_EB_WriteShadowBuffer - writes the shadow buffer to the I-Pdu
 * The service Com_EB_WriteShadowBuffer copies the value of the signal group
 * into the I-Pdu
 * Preconditions:
 * COM must be initialized.
 * \param[in] SignalGPtr - reference to configuration of the signal group
 * \param[in] IPduPtr - reference to configuration of the I-Pdu to which the
 * \param[in] SGArrayPtr - reference to the signal group array
 * Signal Group is stored
 * signal group belongs
 * \retval TRUE transmission shall be triggered, else FALSE
 */
_COM_STATIC_ FUNC(boolean, COM_CODE) Com_EB_WriteShadowBuffer
(
   P2CONST(ComTxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr,
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
   P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) SGArrayPtr
)
{
   boolean forceTrigger = FALSE;

   ComSignalDescByteType ByteSize;
   ComSignalDescByteType byteOffset = 0U;
   /* reference to RAM where the value of the IPdu is stored */
   ComRAMIdxType ComIPduValueRef;

   ComSignalDescByteType StartingByte;

#if (COM_TRANSF_PROP_TRIGGERED_OC_ENABLE == STD_ON)
   P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) maskPtr =
         COM_GET_CONFIG_ELEMENT(uint8, SignalGPtr->ComTOCMaskRef, 0U);
#endif /* (COM_EVALUATE_TRIGGERED_OC == STD_ON) */

   DBG_COM_EB_WRITESHADOWBUFFER_ENTRY(SignalGPtr,IPduPtr,SGArrayPtr);

#if (COM_TRANSF_PROP_TRIGGERED_ENABLE == STD_ON)
   /* transmit Pdu if TransferProperty == TRIGGERED */
   if (COM_TRANSFER_PPROPERTY_TRIG == COM_GET_COM_TX_SIGNAL_GROUP_TRANSFER_PROPERTY(SignalGPtr))
   {
      forceTrigger = TRUE;
   }
#endif /* (COM_TRANSF_PROP_TRIGGERED_ENABLE == STD_ON) */

   /* get the size of the aligned part of the signal group within the IPdu */
   ByteSize = SignalGPtr->ComByteSize;

   /* get the reference to RAM where the value of the IPdu is stored */
   ComIPduValueRef = IPduPtr->ComIPduValueRef;

   /* get position of the aligned part of the signal group within the IPdu */
   StartingByte = SignalGPtr->ComSignalPositionInByte;

   /* enter critical section */
   Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();


   /* check if there is a non aligned part at the beginning */
   if (SignalGPtr->ComBitMaskFirstPart != 0U)
   {
      /* some bits are not byte aligned at the beginning */

      /* Copy the first part */
      Com_EB_WriteShadowBuffer_Unaligned(
            &Com_gDataMemPtr[(ComIPduValueRef + StartingByte)],
            &SGArrayPtr[byteOffset],
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
            SignalGPtr,
            &maskPtr[byteOffset],
            &forceTrigger,
#endif
            SignalGPtr->ComBitMaskFirstPart
      );

      /* Since there is a non aligned part in the beginning the signal group
       * buffer reference has to be increased as well as the reference to the
       * I-Pdu buffer */
      byteOffset++;
      StartingByte++;
   }                            /* if (SignalGPtr->ComBitMaskFirstPart != 0U) */

   if (ByteSize != 0U)
   {
      /* a byte aligned part of the signal group is available */

      /* copy the byte-aligned part of the signal group */

#if (COM_TRANSF_PROP_TRIGGERED_ENABLE == STD_ON)
   if(COM_TRANSFER_PPROPERTY_TRIG_OC ==
         COM_GET_COM_TX_SIGNAL_GROUP_TRANSFER_PROPERTY(SignalGPtr))
   {
      COM_TRIGGERED_OC_WRITE_BYTEARRAY_TO_PDU_TOCMASK(
            &Com_gDataMemPtr[ComIPduValueRef + StartingByte],
            &SGArrayPtr[byteOffset],
            &maskPtr[byteOffset],
            ByteSize,
            forceTrigger);
   }
   else
#endif /* (COM_TRANSF_PROP_TRIGGERED_ENABLE == STD_ON) */
   {
      TS_MemCpy(&Com_gDataMemPtr[ComIPduValueRef + StartingByte],
            &SGArrayPtr[byteOffset],
            ByteSize);
   }



   }                            /* if (ByteSize != 0) */

   /* maybe there is a last non-aligned part left */
   if (SignalGPtr->ComBitMaskLastPart != 0U)
   {
      /* some bits are still left */

      /* calculate the position of the last part in the shadow buffer */
      byteOffset = byteOffset + ByteSize;

      /* Copy the last part */
      Com_EB_WriteShadowBuffer_Unaligned(
            &Com_gDataMemPtr[(ComIPduValueRef + SignalGPtr->ComSignalPositionInByteLastPart)],
            &SGArrayPtr[byteOffset],
#if (COM_EVALUATE_TRIGGERED_OC == STD_ON)
            SignalGPtr,
            &maskPtr[byteOffset],
            &forceTrigger,
#endif
            SignalGPtr->ComBitMaskLastPart
      );

   }                            /* if (SignalGPtr->ComBitMaskLastPart != 0U) */



#if (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)

#if (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL)
   if (COM_GET_TX_SIGNAL_GROUP_UPDATE_BIT(SignalGPtr) == TRUE)
#endif /* (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL) */
   {

#if (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)
   TS_AtomicSetBit_8(&Com_gDataMemPtr[(IPduPtr->ComIPduValueRef +
         (SignalGPtr->ComUpdateBitPositionInBit / 8U))],
         (SignalGPtr->ComUpdateBitPositionInBit % 8U));
#endif /* (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) */
   }

#endif /* (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) */

   /* leave critical section */
   Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();


   DBG_COM_EB_WRITESHADOWBUFFER_EXIT(SignalGPtr,IPduPtr,SGArrayPtr);
   return forceTrigger;
}                               /* Com_EB_WriteShadowBuffer */



#if (COM_TMS_ENABLE == STD_ON)
/** \brief Com_EB_CalculateGroupSignalTM - calculates the transmission mode of
 * a group signal
 * The service Com_EB_CalculateGroupSignalTM evaluates the filter of the group
 * signal and sets the TMS flags
 * Preconditions:
 * - COM must be initialized.
 * - signal type COM_UINT8_N not allowed
 * \param[in] GSignalPtr - reference to configuration of group signal
 * \param[in] SignalGId - Id of signal group to which the group signal belongs
 * \param[in] SignalGPtr - reference to configuration of signal group to
 * which the group signal belongs
 * \param[in] TMSResult - result of filter
 * \param[in] SignalType - type of the group signal
 * \retval none
 */
TS_MOD_PRIV_DEFN FUNC(void, COM_CODE) Com_EB_CalculateGroupSignalTM
(
   P2CONST(ComTxGroupSignalType, AUTOMATIC, COM_APPL_CONST) GSignalPtr,
   ComSignalGroupRefType SignalGId,
   P2CONST(ComTxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr,
   boolean TMSResult
)
{


   /* get the old value of TMS of signal */
   CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT)FlagPtr =
      (&Com_gDataMemPtr
       [(SignalGPtr->ComSignalGTMSFlagsRef) +
        (GSignalPtr->ComPositionInComSignalGTMSFlags / 8)]);

   boolean OldFilterResult;
   boolean CurrentTM;

   DBG_COM_EB_CALCULATEGROUPSIGNALTM_ENTRY(GSignalPtr,SignalGId,SignalGPtr,TMSResult);

   TS_GetBit(FlagPtr, ((uint8) (GSignalPtr->ComPositionInComSignalGTMSFlags % 8)),
             uint8, OldFilterResult);


   /* get the current TMS status of Signal Group */
   TS_GetBit(COM_TXSG_TMS_MIGHT_CHANGE_FLAG_ADDRESS(SignalGId),
             COM_TXSG_TMSSTATE, uint8, CurrentTM);


   /* set the COM_TXSG_TMSMIGHTCHANGE flag if TMSResult is FALSE and
    * OldFilterResult is TRUE and CurrentTM is TRUE */
   if (((TMSResult == FALSE) && (OldFilterResult)) && (CurrentTM))
   {
      TS_AtomicSetBit_8(COM_TXSG_TMS_MIGHT_CHANGE_FLAG_ADDRESS(SignalGId),
                      COM_TXSG_TMSMIGHTCHANGE);
   }

   /* set COM_TXSG_TMSMIGHTCHANGE to TRUE if CurrentTM was FALSE and the
    * TMSResult is TRUE (OldFilterResult has to be FALSE because CurrentTM
    * is FALSE)*/
   if ((TMSResult) && (CurrentTM == FALSE))
   {
      TS_AtomicSetBit_8(COM_TXSG_TMS_MIGHT_CHANGE_FLAG_ADDRESS(SignalGId),
                      COM_TXSG_TMSMIGHTCHANGE);
   }

   /* store result of filter */
   if (TMSResult == TRUE)
   {
      TS_AtomicSetBit_8(FlagPtr, ((uint8) (GSignalPtr->ComPositionInComSignalGTMSFlags % 8)));
   }
   else
   {
      TS_AtomicClearBit_8(FlagPtr, ((uint8) (GSignalPtr->ComPositionInComSignalGTMSFlags % 8)));
   }
   DBG_COM_EB_CALCULATEGROUPSIGNALTM_EXIT(GSignalPtr,SignalGId,SignalGPtr,TMSResult);
   return;
}                               /* Com_EB_CalculateGroupSignalTM */


#if ((COM_SIGNAL_GW_ENABLE == STD_ON) || (COM_BASED_TRANSFORMER_SUPPORT_TX == STD_ON))

/** \brief Com_EB_SetGroupSignalTMSFlagOfSignalGroup - calculates the TMS of a
 * signal group
 * This function Com_EB_SetGroupSignalTMSFlagOfSignalGroup loops over all group
 * signals of the signal group and calculates the TMS of the signal group
 * Preconditions:
 * - COM must be initialized
 * - the signal must be ready to be gated (has to be updated)
 * \param[in] DestSignalGId - Id of signal group
 * \param[in] DestSignalGPtr - reference to the configuration of signal group
 * \param[in] SGArrayPtr - reference to the signal group array
 * \retval E_OK - success
 * \retval E_NOT_OK - Configuration error
 */
_COM_STATIC_ FUNC(uint8, COM_CODE) Com_EB_SetGroupSignalTMSFlagOfSignalGroup
(
   ComSignalGroupRefType DestSignalGId,
   P2CONST(ComTxSignalGroupType, AUTOMATIC, COM_APPL_CONST) DestSignalGPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SGArrayPtr
)
{
   uint8 retval = E_OK;
   Com_SignalIdType i; /* iteration variable */

   /* Id of group signal which belongs to the signal group */
   ComTxGroupSignalRefType DestGSignalId;
   /* reference to the configuration of the group signal*/
   P2CONST(ComTxGroupSignalType, AUTOMATIC, COM_APPL_CONST) DestGSignalPtr;

   boolean TMSResult;

   DBG_COM_EB_SETGROUPSIGNALTMSFLAGOFSIGNALGROUP_ENTRY(DestSignalGId,DestSignalGPtr,SGArrayPtr);

   /* loop over all group signals with filter */
   for(i = DestSignalGPtr->ComGroupSignalRefFirst;
         i < (DestSignalGPtr->ComGroupSignalWithFilterRefNum + DestSignalGPtr->ComGroupSignalRefFirst);
         i++)
   {

      ComCommonReadPropType ComReadProp;
      ComCommonFilterPropertiesType ComFilterProp;

      /* Get signal id and pointer to config of the signal in the signal list of the IPdu */
      DestGSignalId =
            (ComTxGroupSignalRefType) *
            (COM_GET_CONFIG_ELEMENT
                  (ComTxGroupSignalRefType,
                        (Com_gConfigPtr->ComTxSignalGroupGroupSignalListRef), i));

      DestGSignalPtr =
            COM_GET_CONFIG_ELEMENT(ComTxGroupSignalType,
                  Com_gConfigPtr->ComTxGroupSignalRef, DestGSignalId);
#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
      /* CHECK: NOPARSE */
      if (NULL_PTR == DestGSignalPtr)
      {
         COM_PRECONDITION_ASSERT(
               (NULL_PTR == DestGSignalPtr),
               COM_INTERNAL_API_ID);
         retval = E_NOT_OK;
         break;
      }
      if (DestGSignalPtr->ComConfigCheckData != COM_CONFIG_CHECK_TX_GROUP_SIG)
      {
         COM_PRECONDITION_ASSERT(
               (DestGSignalPtr->ComConfigCheckData == COM_CONFIG_CHECK_TX_GROUP_SIG),
               COM_INTERNAL_API_ID);
         retval = E_NOT_OK;
         /* Deviation MISRA-1 */
         break;
      }
      /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */


      ComReadProp.pdudataptrRAM = SGArrayPtr;
#if (COM_SIGNAL_INIT_VALUE_ENABLE == STD_ON)
      ComReadProp.pdudataptrROM = COM_CONST_NULL_PTR;
#endif /* (COM_SIGNAL_INIT_VALUE_ENABLE == STD_ON) */

      ComReadProp.ComBitSize= DestGSignalPtr->ComBitSize;
#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
      ComReadProp.Endianness = COM_GET_TX_GROUP_SIGNAL_ENDIANNESS(DestGSignalPtr);
#endif /* (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE) */
      ComReadProp.SignalType = COM_GET_TX_GROUP_SIGNAL_SIGNAL_TYPE(DestGSignalPtr);
#if (COM_VALUE_INIT_REPLACE == STD_ON)
      ComReadProp.TakePtrROM = FALSE;
#endif /* (COM_VALUE_INIT_REPLACE == STD_ON) */

      Com_EB_CreateFilterProp(
         &ComFilterProp,
         DestGSignalPtr->ComFilterSignalValueRef,
         DestGSignalPtr->ComFilterRef,
         DestGSignalPtr->ComFilterType);

#if (COM_SIGNAL_BYTE_ALIGN == STD_ON)

      ComReadProp.ComSignalPositionInByte  =
            Com_EB_Tx2RxPosinByte(
                  DestGSignalPtr->ComSignalPositionInByte
#if ((COM_ENDIANNESS_CONVERSION == COM_LITTLE_ENDIAN) || \
      (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE))
                  ,DestGSignalPtr->ComBitSize
#if (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON)
                  ,ComReadProp.SignalType
#endif /* (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON) */
#endif /* ((COM_ENDIANNESS_CONVERSION == COM_LITTLE_ENDIAN) || \
            (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)) */
#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
                  ,ComReadProp.Endianness
#endif /* (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE) */
            );

#elif (COM_SIGNAL_BYTE_ALIGN == STD_OFF)

      ComReadProp.ComSignalPositionInBit =
            Com_EB_Tx2RxPosinBit(
                  DestGSignalPtr->ComSignalPositionInBit
                  ,DestGSignalPtr->ComBitSize
#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
                  ,ComReadProp.Endianness
#endif /* (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE) */
            );
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_ON) */


      TMSResult = Com_EB_CalculateFilter(&ComReadProp, &ComFilterProp);


      /* calculate the value of the TMS Flag of the group signal */
      Com_EB_CalculateGroupSignalTM(
         DestGSignalPtr,
         DestSignalGId,
         DestSignalGPtr,
         TMSResult);

   } /* for(i = DestSignalGPtr->ComGroupSignalRefFirst;
   i < (DestSignalGPtr->ComGroupSignalWithFilterRefNum + DestSignalGPtr->ComGroupSignalRefFirst);
   i++) */
   DBG_COM_EB_SETGROUPSIGNALTMSFLAGOFSIGNALGROUP_EXIT(retval,DestSignalGId,DestSignalGPtr,SGArrayPtr);
   return retval;
}                               /* Com_EB_SetGroupSignalTMSFlagOfSignalGroup */
#endif /* ((COM_SIGNAL_GW_ENABLE == STD_ON) || (COM_BASED_TRANSFORMER_SUPPORT_TX == STD_ON)) */

#endif /* (COM_TMS_ENABLE == STD_ON) */

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_STOP_SEC_CODE
#include <MemMap.h>
#endif

#endif /* (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

