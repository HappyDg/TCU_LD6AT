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

#if (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)

typedef struct
{
   /** \brief pointer to the signal group array  */
   P2VAR(uint8, AUTOMATIC, AUTOSAR_COMSTACKDATA) SGArrayPtr;
   /** \brief pointer where the number of bytes copied shall be stored  */
   P2VAR(uint16, AUTOMATIC, AUTOSAR_COMSTACKDATA) outSGArrayLengthPtr;
   /** \brief length signal group array buffer */
   uint16 inSGArrayLength;
} Com_RxSGArrayInfoType;

typedef FUNC(void, COM_CODE) (Com_RxSignalGroupFPtrType)
(
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr,
   P2VAR(Com_RxSGArrayInfoType, AUTOMATIC, COM_APPL_DATA)Com_RxSGArrayInfoPtr,
   P2CONST(ComRxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr,
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
   ComIPduRefType PduId
);

#endif /* (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

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

#if (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)

#if (COM_RX_DATA_TOUT_ACTION != COM_RX_DATA_TOUT_ACTION_NONE)

/** \brief Com_ReceiveSignalGroup_Replace - checks if the value of the signal
 * group shall be replaced with the init value
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] SignalPtr - pointer to the description of the signal
 * \param[in] PduId - Id of the Pdu to which the signal belongs to
 * \retval TRUE - when the value shall be replaced
 * \retval FALSE - when the value shall be no be replaced
 */
_COM_STATIC_ FUNC(boolean, COM_CODE) Com_ReceiveSignalGroup_Replace
(
   P2CONST(ComRxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr,
   ComIPduRefType PduId
);
#endif /* (COM_RX_DATA_TOUT_ACTION != COM_RX_DATA_TOUT_ACTION_NONE) */


/** \brief Com_SetupRxSignalGroup - prepares reading of a signal group array and invokes
 * a function to copy the signal group array from the I-Pdu buffer
 * either to a signal group array or to a shadow buffer
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] SignalGroupId - ID of signal group to be accessed.
 * \param[out] RxSGArrayInfoPtr - info pointer of the signal group array;
 *             if function referred with Com_RxSignalGroupFPtr does not need info,
 *             it may be set to NULL_PTR
 * \param[in] Com_RxSignalGroupFPtr - function which shall be used to
 * copy the value
 * \param[in] ServiceId - Id which shall be used for DET calls
 * \retval E_OK - service has been accepted
 * \retval COM_SERVICE_NOT_AVAILABLE - corresponding I-PDU group was stopped
 * (or service failed due to development error)
 */
_COM_STATIC_ FUNC(uint8, COM_CODE) Com_SetupRxSignalGroup
(
   Com_SignalGroupIdType SignalGroupId,
   P2VAR(Com_RxSGArrayInfoType, AUTOMATIC, COM_APPL_DATA) RxSGArrayInfoPtr,
   P2VAR(Com_RxSignalGroupFPtrType, AUTOMATIC, COM_CODE) Com_RxSignalGroupFPtr,
   uint8 ServiceId
);

#if (COM_BASED_TRANSFORMER_SUPPORT_RX == STD_ON)
/** \brief Com_CopyRxSignalGroupArray_Array - copies the signal group array to
 * the I-Pdu buffer from a signal group array
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[out] retvalPtr - reference where the return vale shall be stored
 *    E_OK - service has been accepted
 *    COM_SERVICE_NOT_AVAILABLE - corresponding I-PDU group was stopped
 *    (or service failed due to development error)
 * \param[out] RxSGArrayInfoPtr - info pointer of the signal group array;
 *             if function referred with Com_RxSignalGroupFPtr does not need info,
 *             it may be set to NULL_PTR
 * \param[in] SignalGPtr - reference to the configuration of the signal group
 * \param[in] IPduPtr - reference to the configuration of the I-Pdu
 * to which the signal group belongs to
 * \param[in] PduId - Id of the I-Pdu
 * to which the signal group belongs to
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_CopyRxSignalGroupArray_Array
(
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr,
   P2VAR(Com_RxSGArrayInfoType, AUTOMATIC, COM_APPL_DATA) RxSGArrayInfoPtr,
   P2CONST(ComRxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr,
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
   ComIPduRefType PduId
);
#endif /* (COM_BASED_TRANSFORMER_SUPPORT_RX == STD_ON) */

/** \brief Com_CopyRxSignalGroupArray_Shadow - copies the signal group array to
 * the I-Pdu buffer from a shadow buffer
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[out] retvalPtr - reference where the return vale shall be stored
 *    E_OK - service has been accepted
 *    COM_SERVICE_NOT_AVAILABLE - corresponding I-PDU group was stopped
 *    (or service failed due to development error)
 * \param[out] SGArrayPtr - not used
 * \param[in] SGArrayLengthPtr - not used
 * \param[in] SignalGPtr - reference to the configuration of the signal group
 * \param[in] IPduPtr - reference to the configuration of the I-Pdu
 * to which the signal group belongs to
 * \param[in] PduId - Id of the I-Pdu
 * to which the signal group belongs to
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_CopyRxSignalGroupArray_Shadow
(
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr,
   P2VAR(Com_RxSGArrayInfoType, AUTOMATIC, COM_APPL_DATA) RxSGArrayInfoType,
   P2CONST(ComRxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr,
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
   ComIPduRefType PduId
);

/** \brief Com_CopyRxSignalGroupArray - copies the signal group array to
 * the I-Pdu buffer from a buffer
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[out] SGArrayPtr - reference to the location where the received
 *  signal group array shall be stored
 * \param[in] SignalGPtr - reference to the configuration of the signal group
 * \param[in] IPduPtr - reference to the configuration of the I-Pdu
 * to which the signal group belongs to
 * \param[in] PduId - Id of the I-Pdu
 * to which the signal group belongs to
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_CopyRxSignalGroupArray
(
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) SGArrayPtr,
   P2CONST(ComRxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr,
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
   ComIPduRefType PduId
);


#if (COM_RX_DATA_TOUT_ACTION != COM_RX_DATA_TOUT_ACTION_NONE)
/** \brief Com_ReceiveSignalGroup_Replace - checks if the value of the signal
 * group shall be replaced with the init value
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] SignalPtr - pointer to the description of the signal
 * \param[in] PduId - Id of the Pdu to which the signal belongs to
 * \retval TRUE - when the value shall be replaced
 * \retval FALSE - when the value shall be no be replaced
 */
_COM_STATIC_ FUNC(boolean, COM_CODE) Com_ReceiveSignalGroup_Replace
(
   P2CONST(ComRxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr,
   ComIPduRefType PduId
)
{
   boolean RxDMReplace = FALSE;
   uint8 RxDMTout;

   DBG_COM_RECEIVESIGNALGROUP_REPLACE_ENTRY(SignalGPtr,PduId);

#if (COM_RX_SIGNAL_BASED_DM == STD_ON)
   /* check if signal based DM is configured */
   if (COM_GET_RX_SIGNAL_GROUP_DM(SignalGPtr) == COM_RX_DM_ON)
   {
      /* check signal based DM flags */
      TS_GetBit(COM_RX_SIGNAL_GROUP_DM_FLAGS_BYTE_POS(SignalGPtr),
            COM_RX_SIGNAL_GROUP_DM_TIMEOUT_BIT_POS(SignalGPtr), uint8, RxDMTout);

   }                      /* if (COM_GET_RX_SIGNAL_GROUP_DM(SignalGPtr) == COM_RX_DM_ON) */
   else
#endif /* (COM_RX_SIGNAL_BASED_DM == STD_ON) */
   {                      /* COM_RX_DM_OFF */
      /* evaluate I-Pdu based DM */
      TS_GetBit(&Com_gDataMemPtr[(Com_gConfigPtr->ComRxIPduStatusBase + PduId)],
                COM_RXPDU_RXDMTIMEOUT, uint8, RxDMTout);
   }                      /* COM_RX_DM_OFF */

   if (1U == RxDMTout)
   {
#if ((COM_RX_DATA_TOUT_ACTION == COM_RX_DATA_TOUT_ACTION_CONFIG))
      /* check if timeout replace is configured for the signal group */
      if (COM_GET_RX_SIGNAL_GROUP_TIMEOUT_ACTION(SignalGPtr) == COM_RX_DATA_TOUT_ACTION_REPLACE)
#endif /* (COM_RX_DATA_TOUT_ACTION == COM_RX_DATA_TOUT_ACTION_CONFIG) */
      {
         RxDMReplace = TRUE;
      }

   }

   DBG_COM_RECEIVESIGNALGROUP_REPLACE_EXIT(RxDMReplace,SignalGPtr,PduId);
   return RxDMReplace;
}

#endif /* (COM_RX_DATA_TOUT_ACTION != COM_RX_DATA_TOUT_ACTION_NONE) */

_COM_STATIC_ FUNC(uint8, COM_CODE) Com_SetupRxSignalGroup
(
   Com_SignalGroupIdType SignalGroupId,
   P2VAR(Com_RxSGArrayInfoType, AUTOMATIC, COM_APPL_DATA) RxSGArrayInfoPtr,
   P2VAR(Com_RxSignalGroupFPtrType, AUTOMATIC, COM_CODE) Com_RxSignalGroupFPtr,
   uint8 ServiceId
)
{

   uint8 retval = COM_SERVICE_NOT_AVAILABLE;

   /* pointer to the configuration of the signal group */
   P2CONST(ComRxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr;

   /* pointer to the configuration of the IPdu to which the signal belongs */
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr;
   ComIPduRefType PduId;   /* Id of the IPdu to which the the signal belongs */

   uint8 BitRes;

   DBG_COM_SETUPRXSIGNALGROUP_ENTRY(SignalGroupId,RxSGArrayInfoPtr,Com_RxSignalGroupFPtr,ServiceId);

   TS_PARAM_UNUSED(ServiceId);

#if (COM_DEV_ERROR_DETECT == STD_ON)

   /* check whether Com is initialized */
   if (Com_InitStatus == COM_EB_UNINIT)
   {
      COM_DET_REPORTERROR(COM_E_UNINIT, ServiceId);
   }
   /* Check if the SignalGroupId is within the range of the ComRxSignalGroupArraySize */
   else if (Com_gConfigPtr->ComRxSignalGroupArraySize <= SignalGroupId)
   {
      COM_DET_REPORTERROR(COM_E_PARAM, ServiceId);
   }
   else
      /* The check whether the signal is a Rx signal or not is done below with the check of the
       * configuration of the signal */

#endif /* COM_DEV_ERROR_DETECT */

   {

      /* get the configuration of the signal identified by the signal Id and check the
       * configuration */
      /* Deviation MISRA-1 */
      /* Deviation MISRA-2 */
      SignalGPtr =
            COM_GET_CONFIG_ELEMENT(ComRxSignalGroupType, Com_gConfigPtr->ComRxSignalGroupRef,
                  SignalGroupId);

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
      /* CHECK: NOPARSE */
      if (NULL_PTR == SignalGPtr)
      {
         COM_PRECONDITION_ASSERT(
               (NULL_PTR == SignalGPtr),
               ServiceId);
      }
      else if (SignalGPtr->ComConfigCheckData != COM_CONFIG_CHECK_RX_SIG_GROUP)
      {
         COM_PRECONDITION_ASSERT(
               (SignalGPtr->ComConfigCheckData == COM_CONFIG_CHECK_RX_SIG_GROUP),
               ServiceId);
      }
      else
         /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */

      {
         /* get the IPdu Id to which the signal belongs */
         PduId = SignalGPtr->ComIPduRef;

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
                  ServiceId);
         }
         else if (IPduPtr->ComConfigCheckData != COM_CONFIG_CHECK_RX_IPDU)
         {
            COM_PRECONDITION_ASSERT(
                  (IPduPtr->ComConfigCheckData == COM_CONFIG_CHECK_RX_IPDU),
                  ServiceId);
         }
         else
            /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */

         {
            TS_GetBit(&Com_gDataMemPtr[(Com_gConfigPtr->ComRxIPduStatusBase + PduId)],
                  COM_RXPDU_STARTED, uint8, BitRes);

            if (BitRes == TRUE)
            {
               retval = E_OK;
            }

            Com_RxSignalGroupFPtr(
               &retval,
               RxSGArrayInfoPtr,
               SignalGPtr,
               IPduPtr,
               PduId
            );

         }
      }
   }

   DBG_COM_SETUPRXSIGNALGROUP_EXIT(retval,SignalGroupId,RxSGArrayInfoPtr,Com_RxSignalGroupFPtr,ServiceId);

   return retval;
}                               /* Com_SetupRxSignalGroup */

#if (COM_BASED_TRANSFORMER_SUPPORT_RX == STD_ON)
_COM_STATIC_ FUNC(void, COM_CODE) Com_CopyRxSignalGroupArray_Array
(
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr,
   P2VAR(Com_RxSGArrayInfoType, AUTOMATIC, COM_APPL_DATA) RxSGArrayInfoPtr,
   P2CONST(ComRxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr,
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
   ComIPduRefType PduId
)
{
   DBG_COM_SETUPRXSIGNALGROUPARRAY_ARRAY_ENTRY(retvalPtr,RxSGArrayInfoPtr,SignalGPtr,IPduPtr,PduId);

#if (COM_DEV_ERROR_DETECT == STD_ON)
   if (RxSGArrayInfoPtr->inSGArrayLength < SignalGPtr->ComByteSize)
   {
      *retvalPtr = COM_SERVICE_NOT_AVAILABLE;
      COM_DET_REPORTERROR(COM_E_PARAM, COMServiceId_ReceiveSignalGroupArray);
   }
   else
#endif /* (COM_DEV_ERROR_DETECT == STD_ON) */
   {

      Com_CopyRxSignalGroupArray(
            RxSGArrayInfoPtr->SGArrayPtr,
            SignalGPtr,
            IPduPtr,
            PduId
      );

      *RxSGArrayInfoPtr->outSGArrayLengthPtr = SignalGPtr->ComByteSize;
   }

   DBG_COM_SETUPRXSIGNALGROUPARRAY_ARRAY_EXIT(retvalPtr,RxSGArrayInfoPtr,SignalGPtr,IPduPtr,PduId);
}
#endif /* (COM_BASED_TRANSFORMER_SUPPORT_RX == STD_ON) */



/* Deviation MISRA-3 <START> */
_COM_STATIC_ FUNC(void, COM_CODE) Com_CopyRxSignalGroupArray_Shadow
(
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) retvalPtr,
   P2VAR(Com_RxSGArrayInfoType, AUTOMATIC, COM_APPL_DATA) RxSGArrayInfoType,
   P2CONST(ComRxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr,
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
   ComIPduRefType PduId
)
/* Deviation MISRA-3 <STOP> */
{

   const ComRAMIdxType shadowBufferRef = SignalGPtr->ComSignalGroupValueRef;

   DBG_COM_SETUPRXSIGNALGROUPARRAY_SHADOW_ENTRY(retvalPtr,RxSGArrayInfoType,IPduPtr,PduId);

   TS_PARAM_UNUSED(RxSGArrayInfoType);


#if ((COM_DEV_ERROR_DETECT == STD_ON) && \
      (COM_BASED_TRANSFORMER_SUPPORT_RX == STD_ON))
   if (shadowBufferRef == COM_RAM_SIZE_MAX)
   {
      /* the signal group has no shadow buffer assigned an shall
       * only be used with the Com_ReceiveSignalGroupArray() */
      *retvalPtr = COM_SERVICE_NOT_AVAILABLE;
      COM_DET_REPORTERROR(COM_E_PARAM, COMServiceId_ReceiveSignalGroup);
   }
   else
#else
      TS_PARAM_UNUSED(retvalPtr);
#endif /* ((COM_DEV_ERROR_DETECT == STD_ON) && \
     (COM_BASED_TRANSFORMER_SUPPORT_RX == STD_ON)) */
   {

      CONSTP2VAR(uint8, COM_CONST, COM_VAR_NOINIT) shadowBufferPtr =
            &Com_gDataMemPtr[shadowBufferRef];

      Com_CopyRxSignalGroupArray(
         shadowBufferPtr,
         SignalGPtr,
         IPduPtr,
         PduId
      );
   }

   DBG_COM_SETUPRXSIGNALGROUPARRAY_SHADOW_EXIT(retvalPtr,RxSGArrayInfoType,SignalGPtr,IPduPtr,PduId);

}                               /* Com_CopyRxSignalGroupArray_Shadow */



_COM_STATIC_ FUNC(void, COM_CODE) Com_CopyRxSignalGroupArray
(
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) SGArrayPtr,
   P2CONST(ComRxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr,
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
   ComIPduRefType PduId
)
{
   DBG_COM_COPYRXSIGNALGROUPARRAY_ENTRY(SGArrayPtr,SignalGPtr,IPduPtr,PduId);
   {

#if (COM_RX_DATA_TOUT_ACTION != COM_RX_DATA_TOUT_ACTION_NONE)
      boolean const RxDMReplace = Com_ReceiveSignalGroup_Replace(SignalGPtr, PduId);

      /* check if value should be replaced */
      if (RxDMReplace == TRUE)
      {
         /* value has to be replaced with init value */
#if (COM_SIGNAL_INIT_VALUE_ENABLE == STD_ON)

         /* pointer to first byte of init value of the signal */
         /* Deviation MISRA-1 */
         /* Deviation MISRA-2 */
         CONSTP2CONST(uint8, AUTOMATIC, COM_APPL_CONST) valPtr =
               COM_GET_CONFIG_ELEMENT(uint8, IPduPtr->ComInitValueRef,
                     SignalGPtr->ComSignalPositionInByte);

         /* copy value from PDU buffer to shadow buffer */
         TS_MemCpy(SGArrayPtr,
            valPtr,
            SignalGPtr->ComByteSize);

#else
         ComSignalBitSizeType l;

         COM_UINT8_COPY_INIT_DEFAULT(SGArrayPtr,
            SignalGPtr->ComByteSize,
            l);
#endif /* (COM_SIGNAL_INIT_VALUE_ENABLE == STD_ON) */
      }
      else
#else
         TS_PARAM_UNUSED(PduId);
#endif /* (COM_RX_DATA_TOUT_ACTION != COM_RX_DATA_TOUT_ACTION_NONE) */
      {

         /* pointer to first byte of value */
         CONSTP2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) valPtr =
               &Com_gDataMemPtr[(IPduPtr->ComIPduValueRef +
                     SignalGPtr->ComSignalPositionInByte)];

         /* Enter critical section */
         Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

         /* copy value from PDU buffer to shadow buffer */
         TS_MemCpy(SGArrayPtr,
            valPtr,
            SignalGPtr->ComByteSize);

         /* Leave critical section */
         Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();
      }

   }

   DBG_COM_COPYRXSIGNALGROUPARRAY_EXIT(SGArrayPtr,SignalGPtr,IPduPtr,PduId);

}

#endif /* (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

FUNC(uint8, COM_CODE) Com_ReceiveSignalGroup
(
   Com_SignalGroupIdType SignalGroupId
)
{
   uint8 retval = COM_SERVICE_NOT_AVAILABLE;

   DBG_COM_RECEIVESIGNALGROUP_ENTRY(SignalGroupId);

#if (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)

   retval = Com_SetupRxSignalGroup(
         SignalGroupId,
         NULL_PTR,
         &Com_CopyRxSignalGroupArray_Shadow,
         COMServiceId_ReceiveSignalGroup
   );


#else
   TS_PARAM_UNUSED(SignalGroupId);

#if (COM_DEV_ERROR_DETECT == STD_ON)
   COM_DET_REPORTERROR(COM_E_PARAM, COMServiceId_ReceiveSignalGroup);
#endif /* (COM_DEV_ERROR_DETECT == STD_ON) */

#endif /* (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */


   DBG_COM_RECEIVESIGNALGROUP_EXIT(retval,SignalGroupId);
   return retval;
}                               /* Com_ReceiveSignalGroup */

/* Deviation MISRA-3 <START> */
FUNC(uint8, COM_CODE) Com_ReceiveSignalGroupArray
(
   Com_SignalGroupIdType SignalGroupId,
   P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) SignalGroupArrayPtr,
   P2VAR(uint16, AUTOMATIC, COM_APPL_DATA) SignalGroupArrayLengthPtr
)
/* Deviation MISRA-3 <STOP> */
{
   uint8 retval = COM_SERVICE_NOT_AVAILABLE;

   DBG_COM_RECEIVESIGNALGROUPARRAY_ENTRY(SignalGroupId,SignalGroupArrayPtr,SignalGroupArrayLengthPtr);

#if ((COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) && \
      (COM_BASED_TRANSFORMER_SUPPORT_RX == STD_ON))

#if (COM_DEV_ERROR_DETECT == STD_ON)
   if (SignalGroupArrayLengthPtr == NULL_PTR)
   {
      COM_DET_REPORTERROR(COM_E_PARAM_POINTER, COMServiceId_ReceiveSignalGroupArray);
   }
   else if (SignalGroupArrayPtr == NULL_PTR)
   {
      *SignalGroupArrayLengthPtr = 0U;
      COM_DET_REPORTERROR(COM_E_PARAM_POINTER, COMServiceId_ReceiveSignalGroupArray);
   }
   else
#endif /* (COM_DEV_ERROR_DETECT == STD_ON) */
   {

      Com_RxSGArrayInfoType SGArrayInfo;
      SGArrayInfo.SGArrayPtr = SignalGroupArrayPtr;
      SGArrayInfo.outSGArrayLengthPtr = SignalGroupArrayLengthPtr;
      SGArrayInfo.inSGArrayLength = *SignalGroupArrayLengthPtr;

      *SignalGroupArrayLengthPtr = 0U;

      retval = Com_SetupRxSignalGroup(
            SignalGroupId,
            &SGArrayInfo,
            &Com_CopyRxSignalGroupArray_Array,
            COMServiceId_ReceiveSignalGroupArray
      );
   }

#else
   TS_PARAM_UNUSED(SignalGroupId);
   TS_PARAM_UNUSED(SignalGroupArrayPtr);
   *SignalGroupArrayLengthPtr = 0U;

#if (COM_DEV_ERROR_DETECT == STD_ON)
   COM_DET_REPORTERROR(COM_E_PARAM, COMServiceId_ReceiveSignalGroupArray);
#endif /* (COM_DEV_ERROR_DETECT == STD_ON) */

#endif /* ((COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) && \
      (COM_BASED_TRANSFORMER_SUPPORT_RX == STD_ON)) */


   DBG_COM_RECEIVESIGNALGROUPARRAY_EXIT(retval,SignalGroupId,SignalGroupArrayPtr,SignalGroupArrayLengthPtr);
   return retval;
}                               /* Com_ReceiveSignalGroupArray */

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_STOP_SEC_CODE
#include <MemMap.h>
#endif

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/
