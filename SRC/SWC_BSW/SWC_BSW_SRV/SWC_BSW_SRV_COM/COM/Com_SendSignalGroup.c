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
 */

/*==================[inclusions]=============================================*/

#include <Com_Trace.h>
#include <TSAutosar.h>          /* EB specific standard types */
#include <ComStack_Types.h>     /* AUTOSAR standard types */
#include <Com_Api_Static.h>     /* module public static API */
#include <Com_Priv.h>           /* module internal stuff */

#include <Com_Core_TxSignalGroup.h>  /* (group)signal(group) functions */

#if (COM_DEV_ERROR_DETECT == STD_ON)
#include <Det.h>                /* Det API */
#endif

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

#if (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)

typedef FUNC(uint8, COM_CODE) (Com_TxSignalGroupFPtrType)
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
);

#endif /* (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */
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


#if (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)


/** \brief Com_SetupTxSignalGroup - handles a Tx signal group access
 * Preconditions:
 * \param[in] SignalGroupId - Id of the signal group which shall be accessed
 * \param[out] SGArrayPtr - Reference to the signal group array to be transmitted;
 *             if function referred with Com_TxSignalGroupFPtr does not need info,
 *             it may be set to NULL_PTR
 * \param[in] SGArrayLength - Length of the signal group array
 *             if function referred with Com_TxSignalGroupFPtr does not need info,
 *             it may be set to 0
 * \param[in] Com_TxSignalGroupFPtr - function which shall be used to
 * copy the value
 * \param[in] ServiceId - Id which shall be used for DET calls
 * \retval E_OK - success
 * \retval COM_SERVICE_NOT_AVAILABLE - failure (Com not initialized,
 * corresponding I-PDU group was stopped or
 * service failed due to development error)
 */
_COM_STATIC_ FUNC(uint8, COM_CODE) Com_SetupTxSignalGroup
(
   Com_SignalGroupIdType SignalGroupId,
   P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) SGArrayPtr,
   uint16 SGArrayLength,
   P2VAR(Com_TxSignalGroupFPtrType, AUTOMATIC, COM_CODE) Com_TxSignalGroupFPtr,
   uint8 ServiceId
);


_COM_STATIC_ FUNC(uint8, COM_CODE) Com_SetupTxSignalGroup
(
   Com_SignalGroupIdType SignalGroupId,
   P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) SGArrayPtr,
   uint16 SGArrayLength,
   P2VAR(Com_TxSignalGroupFPtrType, AUTOMATIC, COM_CODE) Com_TxSignalGroupFPtr,
   uint8 ServiceId
)
{
   uint8 retval = COM_SERVICE_NOT_AVAILABLE;

   /* pointer to the configuration of the signal group */
   P2CONST(ComTxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr;
   ComIPduRefType PduId;
   /* pointer to the configuration of the IPdu to which the signal group belongs */
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr;

   DBG_COM_SETUPTXSIGNALGROUP_ENTRY(SignalGroupId,SGArrayPtr,SGArrayLength,Com_TxSignalGroupFPtr,ServiceId);

   TS_PARAM_UNUSED(ServiceId);

#if (COM_DEV_ERROR_DETECT == STD_ON)

   /* check whether Com is initialized */
   if (Com_InitStatus == COM_EB_UNINIT)
   {
      COM_DET_REPORTERROR(COM_E_UNINIT, ServiceId);
   }
   /* Check if the SignalGroupId is within the range of the ComTxSignalGroupArraySize */
   else if (Com_gConfigPtr->ComTxSignalGroupArraySize <= SignalGroupId)
   {
      COM_DET_REPORTERROR(COM_E_PARAM, ServiceId);
   }
   else
      /* The check whether the signal is a Tx signal or not is done below with the check of the
       * configuration of the signal */

#endif /* COM_DEV_ERROR_DETECT */

   {
      /* get the configuration of the signal group identified by the SignalGroupId and check the
       * configuration */
      /* Deviation MISRA-1 */
      /* Deviation MISRA-2 */
      SignalGPtr =
            COM_GET_CONFIG_ELEMENT(ComTxSignalGroupType, Com_gConfigPtr->ComTxSignalGroupRef,
                  SignalGroupId);

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
      /* CHECK: NOPARSE */
      if (NULL_PTR == SignalGPtr)
      {
         COM_PRECONDITION_ASSERT(
               (NULL_PTR == SignalGPtr),
               ServiceId);
      }
      else if (SignalGPtr->ComConfigCheckData != COM_CONFIG_CHECK_TX_SIG_GROUP)
      {
         COM_PRECONDITION_ASSERT(
               (SignalGPtr->ComConfigCheckData == COM_CONFIG_CHECK_TX_SIG_GROUP),
               ServiceId);
      }
      else
         /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */

      {
         /* get the IPdu Id to which the signal group belongs */
         PduId = SignalGPtr->ComIPduRef;

         /* get IPdu to which the the signal belongs and check if the IPdu is valid */
         /* Deviation MISRA-1 */
         /* Deviation MISRA-2 */
         IPduPtr = COM_GET_CONFIG_ELEMENT(ComTxIPduType, Com_gConfigPtr->ComTxIPduRef, PduId);

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
         /* CHECK: NOPARSE */
         if (NULL_PTR == IPduPtr)
         {
            COM_PRECONDITION_ASSERT(
                  (NULL_PTR == IPduPtr),
                  ServiceId);
         }
         else if (IPduPtr->ComConfigCheckData != COM_CONFIG_CHECK_TX_IPDU)
         {
            COM_PRECONDITION_ASSERT(
                  (IPduPtr->ComConfigCheckData == COM_CONFIG_CHECK_TX_IPDU),
                  ServiceId);
         }
         else
            /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */

         {

            /* call internal signal group sending function */
            retval = Com_TxSignalGroupFPtr(
                  SGArrayPtr,
                  SGArrayLength,
#if (COM_TMS_ENABLE == STD_ON)
                  ((ComSignalGroupRefType)SignalGroupId),
#endif /* (COM_TMS_ENABLE == STD_ON) */
                  SignalGPtr,
                  PduId,
                  IPduPtr
#if (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON)
                  ,FALSE
#endif /* (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON) */
            );

         }
      }
   }

   DBG_COM_SETUPTXSIGNALGROUP_EXIT(retval,SignalGroupId,SGArrayPtr,SGArrayLength,Com_TxSignalGroupFPtr,ServiceId);

   return retval;
}                               /* Com_SetupTxSignalGroup */

#endif /* (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */


FUNC(uint8, COM_CODE) Com_SendSignalGroup
(
   Com_SignalGroupIdType SignalGroupId
)
{
   uint8 retval = COM_SERVICE_NOT_AVAILABLE;

   DBG_COM_SENDSIGNALGROUP_ENTRY(SignalGroupId);

#if (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)

   retval = Com_SetupTxSignalGroup(
         SignalGroupId,
         NULL_PTR,
         0U,
         &Com_EB_SendSignalGroup,
         COMServiceId_SendSignalGroup
   );

#else /* (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */
   TS_PARAM_UNUSED(SignalGroupId);
#if (COM_DEV_ERROR_DETECT == STD_ON)
   COM_DET_REPORTERROR(COM_E_PARAM, COMServiceId_SendSignalGroup);
#endif /* (COM_DEV_ERROR_DETECT == STD_ON) */

#endif /* (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */


   DBG_COM_SENDSIGNALGROUP_EXIT(retval,SignalGroupId);
   return retval;
}                               /* Com_SendSignalGroup */


FUNC(uint8, COM_CODE) Com_SendSignalGroupArray
(
   Com_SignalGroupIdType SignalGroupId,
   P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) SignalGroupArrayPtr,
   uint16 SignalGroupArrayLength
)
{
   uint8 retval = COM_SERVICE_NOT_AVAILABLE;

   DBG_COM_SENDSIGNALGROUPARRAY_ENTRY(SignalGroupId,SignalGroupArrayPtr,SignalGroupArrayLength);

#if ((COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) && \
      (COM_BASED_TRANSFORMER_SUPPORT_TX == STD_ON))

   retval = Com_SetupTxSignalGroup(
         SignalGroupId,
         SignalGroupArrayPtr,
         SignalGroupArrayLength,
         &Com_EB_SendSignalGroupArray_DETCheck,
         COMServiceId_SendSignalGroupArray
   );

#else
   TS_PARAM_UNUSED(SignalGroupId);
   TS_PARAM_UNUSED(SignalGroupArrayPtr);
   TS_PARAM_UNUSED(SignalGroupArrayLength);
#if (COM_DEV_ERROR_DETECT == STD_ON)
   COM_DET_REPORTERROR(COM_E_PARAM, COMServiceId_SendSignalGroupArray);
#endif /* (COM_DEV_ERROR_DETECT == STD_ON) */

#endif /* ((COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) && \
     (COM_BASED_TRANSFORMER_SUPPORT_TX == STD_ON)) */


   DBG_COM_SENDSIGNALGROUPARRAY_EXIT(retval,SignalGroupId,SignalGroupArrayPtr,SignalGroupArrayLength);
   return retval;
}                               /* Com_SendSignalGroupArray */

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_STOP_SEC_CODE
#include <MemMap.h>
#endif

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/
