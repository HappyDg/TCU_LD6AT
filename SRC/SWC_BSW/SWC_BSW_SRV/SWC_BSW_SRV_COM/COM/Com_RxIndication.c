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
 * MISRA-1) Deviated Rule: 11.1 (required)
 * "Conversions shall not be performed between a pointer to a function and any type other than an integral type."
 *
 * Reason:
 * Actually this is not a cast between a pointer to a function, since 0 is the
 * null pointer constant.
 *
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


/*==================[inclusions]=============================================*/

#include <Com_Trace.h>
#include <TSAutosar.h>          /* EB specific standard types */
#include <ComStack_Types.h>     /* AUTOSAR standard types */
#include <Com_Api_Static.h>     /* module public static API */
#include <Com_Priv.h>           /* module internal stuff */
#include <Com_Cbk_Static.h>     /* Callback declarations header */
#include <TSMem.h>              /* TS_MemCpy */

#include <Com_Core_RxIPdu.h>    /* Header TxIPdu functions */

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


#if (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_PRESENT_FOR_ALL)
#if (COM_RX_TIMEOUT_FACTOR_SIZE != COM_SIZE_0_BIT)

/** \brief Com_EB_HandlePduRxDM - sets the Pdu based Rx deadline monitoring
  ** Preconditions:
 ** - COM should be initialized
 ** \param[in] IPduFlagBytePtr - pointer to the flags of the Pdu
 ** \param[in] IPduPtr - pointer to the configuration of the Pdu
 ** \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_HandlePduRxDM
(
   P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) IPduFlagBytePtr,
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
);

#endif /* (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_PRESENT_FOR_ALL) */
#endif /* (COM_RX_TIMEOUT_FACTOR_SIZE != COM_SIZE_0_BIT) */



#if ((COM_RX_SIG_CONF_IMMEDIATE_ENABLE == STD_ON) || \
      (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON))
#if (COM_NOTIFY_RECEIVERS_ENABLE == STD_ON)

/** \brief Com_EB_HandleRxConfirm - handles to Rx confirmations of a Pdu
  ** Preconditions:
 ** - COM should be initialized
 ** \param[in] IPduFlagBytePtr - pointer to the flags of the Pdu
 ** \param[in] IPduPtr - pointer to the configuration of the Pdu
 ** \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_HandleRxConfirm
(
#if (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON)
   P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) IPduFlagBytePtr,
#endif /* (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON) */
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
);
#endif /* (COM_NOTIFY_RECEIVERS_ENABLE == STD_ON) */
#endif /* ((COM_RX_SIG_CONF_IMMEDIATE_ENABLE == STD_ON) || \
      (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON))*/


#if (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_PRESENT_FOR_ALL)
#if (COM_RX_TIMEOUT_FACTOR_SIZE != COM_SIZE_0_BIT)

/** \brief Com_EB_HandlePduRxDM - sets the Pdu based Rx deadline monitoring
  ** Preconditions:
 ** - COM should be initialized
 ** \param[in] IPduFlagBytePtr - pointer to the flags of the Pdu
 ** \param[in] IPduPtr - pointer to the configuration of the Pdu
 ** \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_HandlePduRxDM
(
   P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) IPduFlagBytePtr,
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
)
{
   DBG_COM_EB_HANDLEPDURXDM_ENTRY(IPduFlagBytePtr,IPduPtr);

   if (COM_GET_COM_RX_IPDU_DM(IPduPtr) == COM_RX_DM_ON)
   {

      uint8 BitRes;
      Com_RxDMNextDueTimeType const TimeOutOffset = COM_GET_RX_TIMEOUT_FACTOR(IPduPtr);

      /* enter critical section */
      Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

      /* check if RxDM is enabled */
      TS_GetBit(IPduFlagBytePtr, COM_RXPDU_RXDMRUNNING, uint8, BitRes);

      /* handle RxDM if enabled */
      if (1U == BitRes)

      {
         /* clear time out flag, new value is available */
         Com_ClearBitUInt8(IPduFlagBytePtr, COM_RXPDU_RXDMTIMEOUT);

         /* restart RxDM */
         Com_EB_RxDMQueue(IPduPtr, TimeOutOffset);
      }
#if (COM_RX_FIRST_TIMEOUT_FACTOR_SIZE != COM_SIZE_0_BIT)
      else
      {
         /* RxDM is not enabled, check if shall be enabled */
         /* check if RxDM is switched on */
         TS_GetBit(IPduFlagBytePtr, COM_RXPDU_RXDMSWITCHON, uint8, BitRes);
         if (1U == BitRes)
         {
            /* clear time out flag, new value is available */
            Com_ClearBitUInt8(IPduFlagBytePtr, COM_RXPDU_RXDMTIMEOUT);

            /* enable RxDM */
            Com_SetBitUInt8(IPduFlagBytePtr, COM_RXPDU_RXDMRUNNING);

            /* start RxDM */
            Com_EB_RxDMQueue(IPduPtr, TimeOutOffset);
         }
      }
#endif /* (COM_RX_FIRST_TIMEOUT_FACTOR_SIZE != COM_SIZE_0_BIT) */

      /* leave critical section */
      Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();

   }                            /* if (COM_GET_COM_RX_IPDU_DM(IPduPtr) == COM_RX_DM_ON) */

   DBG_COM_EB_HANDLEPDURXDM_EXIT(IPduFlagBytePtr,IPduPtr);
   return;
}                               /* Com_EB_HandlePduRxDM */

#endif /* (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_PRESENT_FOR_ALL) */
#endif /* (COM_RX_TIMEOUT_FACTOR_SIZE != COM_SIZE_0_BIT) */



#if ((COM_RX_SIG_CONF_IMMEDIATE_ENABLE == STD_ON) || \
      (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON))
#if (COM_NOTIFY_RECEIVERS_ENABLE == STD_ON)

/** \brief Com_EB_HandleRxConfirm - handles to Rx confirmations of a Pdu
  ** Preconditions:
 ** - COM should be initialized
 ** \param[in] IPduFlagBytePtr - pointer to the flags of the Pdu
 ** \param[in] IPduPtr - pointer to the configuration of the Pdu
 ** \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_HandleRxConfirm
(
#if (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON)
   P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) IPduFlagBytePtr,
#endif /* (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON) */
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
)
{
   DBG_COM_EB_HANDLERXCONFIRM_ENTRY(IPduPtr);

#if ((COM_RX_SIG_CONF_IMMEDIATE_ENABLE == STD_ON) && (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON))

         if (COM_GET_COM_RX_IPDU_SIGNAL_PROCESSING(IPduPtr) == COM_DEFERED)
#endif /* ((COM_RX_SIG_CONF_IMMEDIATE_ENABLE == STD_ON) && (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON)) */

#if (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON)
         {
            /* Set Notify Flag */
            TS_AtomicSetBit_8(IPduFlagBytePtr, COM_RXPDU_RXDEFNOTIFY);
         }
#endif /* (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON) */

#if ((COM_RX_SIG_CONF_IMMEDIATE_ENABLE == STD_ON) && (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON))
         else
#endif /* ((COM_RX_SIG_CONF_IMMEDIATE_ENABLE == STD_ON) && (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON)) */

#if (COM_RX_SIG_CONF_IMMEDIATE_ENABLE == STD_ON)
         {
            /* Notify Receivers */
            Com_EB_NotifyReceivers(IPduPtr);
         }
#endif /* (COM_RX_SIG_CONF_IMMEDIATE_ENABLE == STD_ON) */


   DBG_COM_EB_HANDLERXCONFIRM_EXIT(IPduPtr);
   return;
}
#endif /* (COM_NOTIFY_RECEIVERS_ENABLE == STD_ON) */
#endif /* ((COM_RX_SIG_CONF_IMMEDIATE_ENABLE == STD_ON) || \
      (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON))*/


/**
 * \brief Com_RxIndication - Signal the COM a PDU has arrived
 *
 * This functions signals the COM that a PDU has arrived
 * Preconditions:
 * - COM should be initialized
 *
 * \param[in] ComRxPduId - ID of the received I-PDU.
 * \param[in] PduInfoPtr - Contains the length (SduLength) of the received I-PDU and a pointer to
 * a buffer (SduDataPtr) containing the I-PDU.
 * \return
 * \retval None
 *
 * \ServiceID{0x42}
 * \Reentrancy{Re-entrant for different values of ComRxPduId only.}
 * \Synchronicity{Synchronous}
 */
FUNC(void, COM_CODE) Com_RxIndication
(
   PduIdType ComRxPduId,
   P2VAR(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr
)
{

   DBG_COM_RXINDICATION_ENTRY(ComRxPduId,PduInfoPtr);

   /* Debug output */
#if (COM_DEV_ERROR_DETECT == STD_ON)
   /* check whether Com is initialized */
   if (Com_InitStatus == COM_EB_UNINIT)
   {
      COM_DET_REPORTERROR(COM_E_UNINIT, COMServiceId_RxIndication);
   }
   /* check SignalDataPtr */
   else if (PduInfoPtr == NULL_PTR)
   {
      COM_DET_REPORTERROR(COM_E_PARAM_POINTER, COMServiceId_RxIndication);
   }
   /* check if PduInfoPtr->SduDataPtr is NULL_PTR */
   else if (PduInfoPtr->SduDataPtr == NULL_PTR)
   {
      COM_DET_REPORTERROR(COM_E_PARAM_POINTER, COMServiceId_RxIndication);
   }
   /* check if ComRxPduId is valid */
   else if (Com_gConfigPtr->ComRxIPduArraySize <= ComRxPduId)
   {
      COM_DET_REPORTERROR(COM_E_PARAM, COMServiceId_RxIndication);
   }
   else

#endif /* (COM_DEV_ERROR_DETECT == STD_ON) */

   {
      uint8 BitRes;

      /* pointer to the configuration of the IPdu to which the signal belongs */
      P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr;
      P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) pdudataptr; /* pointer to the data of the PDU */

      /* pointer to byte with status flags of the Pdu */
      CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) IPduFlagBytePtr =
            &Com_gDataMemPtr[(Com_gConfigPtr->ComRxIPduStatusBase + ComRxPduId)];

      /* get IPdu to which ComRxPduId identifies and check if the IPdu is valid */
      /* Deviation MISRA-2 */
      /* Deviation MISRA-3 */
      IPduPtr = COM_GET_CONFIG_ELEMENT(ComRxIPduType, Com_gConfigPtr->ComRxIPduRef, ComRxPduId);

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
      /* CHECK: NOPARSE */
      if (NULL_PTR == IPduPtr)
      {
         COM_PRECONDITION_ASSERT(
               (NULL_PTR == IPduPtr),
               COMServiceId_RxIndication);
      }
      else if (IPduPtr->ComConfigCheckData != COM_CONFIG_CHECK_RX_IPDU)
      {
         COM_PRECONDITION_ASSERT(
               (IPduPtr->ComConfigCheckData == COM_CONFIG_CHECK_RX_IPDU),
               COMServiceId_RxIndication);
      }
      else
         /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */

      {
         /* get data pointer of I-PDU */
         pdudataptr = &Com_gDataMemPtr[(IPduPtr->ComIPduValueRef)];

         /* If the PDU can be received (is started) */
         TS_GetBit(IPduFlagBytePtr, COM_RXPDU_STARTED, uint8, BitRes);
         if (BitRes == TRUE)
         {
            /* If there is a callout, let it decide whether to receive the
             * IPDU or not */

#if (COM_CALL_OUT_FUNC_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE)
            boolean coretval = TRUE;  /* call-out function return value */
            P2VAR(Com_RxCalloutType, AUTOMATIC, COM_APPL_CODE) fptr;

            /* Get the function pointer of the callout function */
            if (IPduPtr->ComIPduCallOutFuncPtrRef != COM_CALL_OUT_FUNC_PTR_NULL)
            {
               fptr = Com_RxCallouts[(IPduPtr->ComIPduCallOutFuncPtrRef)];

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
               /* Check if fptr is valid */
               /* CHECK: NOPARSE */
               if (fptr == NULL_PTR)
               {
                  COM_PRECONDITION_ASSERT((fptr != NULL_PTR), COMServiceId_RxIndication);
                  /* prevent further proceeding in case of DET error */
                  coretval = FALSE;
               }
               else
                  /* CHECK: PARSE */
#endif /* COM_PRECONDITION_ASSERT_ENABLED */

               {
                  coretval = fptr(ComRxPduId, PduInfoPtr->SduDataPtr);
               }
            }

            /* If the callout-function was not called (because there is none),
             * the coretval is TRUE by default */

            /* Stop processing if the callout returned FALSE */
            if (coretval == TRUE)
#endif /* (COM_CALL_OUT_FUNC_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) */
            {

               /* get length of I-PDU */
               PduLengthType pdulength = IPduPtr->ComIPduSize;

               if (PduInfoPtr->SduLength < pdulength)
               {
                  pdulength = PduInfoPtr->SduLength;
               }

               /* Copy the content of the received PDU to the PDU buffer */
               /* Enter critical section to guarantee a consistent PDU is copied */
               Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_1();

               /* copy the Pdu */
               TS_MemCpy(pdudataptr, PduInfoPtr->SduDataPtr, pdulength);

               /* Leave critical section */
               Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_1();

#if (COM_SIGNAL_GW_ENABLE == STD_ON)
               /* check if the I-Pdu has a flag for SigGW configured and therefore
                * at least one signal (with or without update bit) which has to be
                * gated */
               if (IPduPtr->ComIPduSigGWFlagBit != COM_IPDU_INVALID)
               {
                  /* set the I-Pdu SigGWFlag */
                  TS_AtomicSetBit_8(COM_RX_IPDU_SIG_GW_FLAG_ADDRESS(IPduPtr),
                        COM_RX_IPDU_SIG_GW_FLAG_BIT(IPduPtr));
               }
#endif /* (COM_SIGNAL_GW_ENABLE == STD_ON) */

#if (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_PRESENT_FOR_ALL)
#if (COM_RX_TIMEOUT_FACTOR_SIZE != COM_SIZE_0_BIT)

               Com_EB_HandlePduRxDM(IPduFlagBytePtr, IPduPtr);

#endif /* (COM_RX_TIMEOUT_FACTOR_SIZE != COM_SIZE_0_BIT) */
#endif /* (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_PRESENT_FOR_ALL) */


#if ((COM_RX_SIG_CONF_IMMEDIATE_ENABLE == STD_ON) || \
      (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON))
#if (COM_NOTIFY_RECEIVERS_ENABLE == STD_ON)

               Com_EB_HandleRxConfirm(
#if (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON)
                  IPduFlagBytePtr,
#endif /* (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON) */
                  IPduPtr
               );
#endif /* (COM_NOTIFY_RECEIVERS_ENABLE == STD_ON) */
#endif /* ((COM_RX_SIG_CONF_IMMEDIATE_ENABLE == STD_ON) || \
      (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON))*/

            }                         /* coretval == TRUE */
         }                            /* COM_RXPDU_STARTED */
      }
   }

   DBG_COM_RXINDICATION_EXIT(ComRxPduId,PduInfoPtr);
}                               /* Com_RxIndication */

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_STOP_SEC_CODE
#include <MemMap.h>
#endif

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/

