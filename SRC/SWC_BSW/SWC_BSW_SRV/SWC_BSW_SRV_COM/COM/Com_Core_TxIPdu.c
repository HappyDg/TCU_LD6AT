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
 * MISRA-2) Deviated Rule: 11.3 (advisory)
 * "A cast should not be performed between a pointer type and an integral type."
 *
 * Reason:
 * Actually this is not a cast between a pointer and a integral type, since 0
 * is null pointer constant.
 *
 * MISRA-3) Deviated Rule: 14.6 (required)
 * For any iteration statement there shall be at most one break statement
 * used for loop termination.
 *
 * Reason:
 * Multiple breaks are used to reduce clutter of functions if all of the following
 * conditions take place:
 * a) The immediately abort of the loop is required because data are invalid and
 *    may lead to inconsistent code execution
 * b) The function is highly cluttered with preprocessor statements. Additional branches
 *    might lead to unreadable code.
 *
 * MISRA-5) Deviated Rule: 6.3 (advisory)
 * "'typedefs' that indicate size and signedness should be used in place of the basic types."
 *
 * Reason:
 * In this case variables are casted to a natural integral type since, the value is further used
 * for purposes where natural types are most efficient (e.g. indexing).
 *
 */

/* NOCOV List
 *
 * NOCOV-UNSUPPORTEDOPTIMIZATION:
 *
 * Reason:
 * A feature is not supported for this release and is inactivated with
 * pre-compile time switches (and therefore not included into the binary).
 *
 *
 */

/*==================[inclusions]============================================*/



#include <Com_Trace.h>
#include <TSAutosar.h>          /* EB specific standard types */
#include <ComStack_Types.h>     /* AUTOSAR Standard types */
#include <Com_Api.h>                /* Module public API */

#include <Com_Priv.h>           /* Module private API */

/* Com module does not require configuration of PduR, no need to re-build
 * Com module in case the post-build configuration of PduR changes */
#define PDUR_NO_PBCFG_REQUIRED
#include <PduR_Com.h>           /* For the PduR_ComTransmit-call */
#include <TSMem.h>              /* TS_MemCpy */

#include <Com_Core_TxIPdu.h>    /* Header TxIPdu functions */

#if ((COM_TM_AVAILABLE == STD_ON) || (COM_TMS_ENABLE == STD_ON))
#include <Com_Core_TM.h> /* Transmission Mode functions */
#endif /* ((COM_TM_AVAILABLE == STD_ON) || (COM_TMS_ENABLE == STD_ON)) */


/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_START_SEC_CODE
#include <MemMap.h>
#endif

#if (COM_MDT_QUEUE_AVAILABLE == STD_ON)
/** \brief Com_EB_HandleMDT
 * starts MDT if configured
 * \param[in] PduId - Id of the IPdu the API call was called for
 * \param[in] IPduPtr - reference to configuration of Pdu
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_HandleMDT
(
   ComIPduRefType PduId,
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
);
#endif /* (COM_MDT_QUEUE_AVAILABLE == STD_ON) */

/** \brief Com_EB_HandleTxIPdu_Start - starts a Tx IPdu
 * Preconditions:
 * - prior to this call, the COM module shall be initialized
 * \param[in] IPduPtr - configuration of the I-Pdu
 * \param[in] Initialize - defines if the Pdu group should be initialized
 * \param[in] IPduId - Id of the I-Pdu
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_HandleTxIPdu_Start
(
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
   boolean Initialize,
   ComIPduRefType IPduId
);


/** \brief Com_EB_HandleTxIPdu_Stop - stops a Tx IPdu
 * Preconditions:
 * - prior to this call, the COM module shall be initialized
 * \param[in] IPduPtr - configuration of the I-Pdu
 * \param[in] IPduId - Id of the I-Pdu
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_HandleTxIPdu_Stop
(
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
   ComIPduRefType IPduId
);

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)

/** \brief Com_EB_CheckTxIpdu check if the configuration of an I-Pdu is
 * plausible
 * \param[in] IPduPtr pointer to the configuration of the Tx-IPdu
 * \retval E_OK if config is plausible
 * \retval E_NOT_OK if config is wrong
 */
_COM_STATIC_ FUNC(uint8, COM_CODE)Com_EB_CheckTxIpdu
(
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
);

#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */


/** \brief Com_EB_InitTxIPdu_PduBuffer
 * function which initializes the IPdu-buffer of a Tx-IPdu
 * \param[in] IPduPtr pointer to the configuration of the Tx-IPdu
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_InitTxIPdu_PduBuffer
(
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
);

#if (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
/** \brief Com_EB_InitTxIPdu_SignalGroups
 * function which initializes the signal groups of a Tx-IPdu
 * \param[in] IPduPtr pointer to the configuration of the Tx-IPdu
 * \retval E_OK - success
 * \retval E_NOT_OK - in case of an config error
 */
_COM_STATIC_ FUNC(uint8, COM_CODE)Com_EB_InitTxIPdu_SignalGroups
(
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
);
#endif /* (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */


/** \brief Com_EB_InitTxIPdu_HandleFlags
 * function which initializes the flags of a Tx-IPdu
 * \param[in] IPduPtr pointer to the configuration of the Tx-IPdu
 * \param[in] TxPduId PduId to start
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_InitTxIPdu_HandleFlags
(
      P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
      ComIPduRefType TxPduId
);

#if (COM_TMS_ENABLE == STD_ON)

#if ((COM_TXF_MASKNEWDIFFERSMASKOLD_EN == STD_ON) || \
      (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON))

/** \brief Com_EB_InitTxIPdu_Signals
 * function which initializes the signals of a Tx-IPdu
 * \param[in] IPduPtr pointer to the configuration of the Tx-IPdu
 * \retval E_OK - success
 * \retval E_NOT_OK - in case of an config error
 */
_COM_STATIC_ FUNC(uint8, COM_CODE)Com_EB_InitTxIPdu_Signals
(
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
);


#if (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
/** \brief Com_EB_InitTxIPdu_GroupSignals
 * function which initializes the group signals of a Tx-IPdu
 * \param[in] PduId PduId to start
 * \retval E_OK - success
 * \retval E_NOT_OK - in case of an config error
 */
_COM_STATIC_ FUNC(uint8, COM_CODE)Com_EB_InitTxIPdu_GroupSignals
(
   ComIPduRefType TxPduId
);
#endif /* (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

#endif /* ((COM_TXF_MASKNEWDIFFERSMASKOLD_EN == STD_ON) || \
      (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON)) */

#endif /* (COM_TMS_ENABLE == STD_ON) */


/** \brief Com_EB_StartIPdu
 * function which manages starting a single IPdu
 * Preconditions:
 * - prior to this call, the COM module shall be initialized
 * - the Pdu must not be started before
 * \param[in] IPduPtr pointer to the configuration of the I-Pdu
 * \param[in] PduId PduId to start
 * \retval None
 */

_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_StartIPdu
(
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
   ComIPduRefType PduId
);


/** \brief Com_EB_Send_Pdu
 * Function which sends out the PDU (calls the I-Pdu callout if configured)
  * Preconditions:
 * - function does not check if MDT is running -> invoke only if MDT is not
 *   running or MDT shall be ignored.
 * \param[in] PduId - Id of the IPdu the API call was called for
 * \param[in] IPduPtr - reference to configuration of Pdu
 * \retval None
 */
TS_MOD_PRIV_DEFN FUNC(void, COM_CODE) Com_EB_Send_Pdu
(
   ComIPduRefType PduId,
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
)
{
   PduInfoType pduinfo;

   CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) pdudataptr =
      (P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT))
      & Com_gDataMemPtr[(IPduPtr->ComIPduValueRef)];


#if (COM_CALL_OUT_FUNC_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE)
   boolean coretval = TRUE;
   P2VAR(Com_TxCalloutType, AUTOMATIC, COM_APPL_CODE) fptr;
#else
   /* if no callout and MDT is possible, the PduId is not required */
#if (COM_MDT_QUEUE_AVAILABLE == STD_OFF)
   TS_PARAM_UNUSED(PduId);
#endif /* (COM_MDT_QUEUE_AVAILABLE == STD_ON) */
#endif /* (COM_CALL_OUT_FUNC_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) */
   
   DBG_COM_EB_SEND_PDU_ENTRY(PduId,IPduPtr);

   pduinfo.SduDataPtr = pdudataptr;
   pduinfo.SduLength = IPduPtr->ComIPduSize;

#if (COM_CALL_OUT_FUNC_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE)
   if (IPduPtr->ComIPduCallOutFuncPtrRef != COM_CALL_OUT_FUNC_PTR_NULL)
   {
      /* get the function pointer */
      fptr = Com_TxCallouts[(IPduPtr->ComIPduCallOutFuncPtrRef)];
#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
      /* check it the function pointer is NULL_PTR */
      /* CHECK: NOPARSE */
      /* Deviation MISRA-1 */
      /* Deviation MISRA-2 */
      if (fptr == NULL_PTR)
      {
          COM_PRECONDITION_ASSERT((fptr != NULL_PTR), COM_INTERNAL_API_ID);
      }
      else
      /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */
      {
         /* the function pointer seems to be OK, call it */
         coretval = fptr(PduId, pdudataptr);
      }
   }
   if (coretval == TRUE)
#endif /* (COM_CALL_OUT_FUNC_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) */
   {

#if (COM_EVALUATE_TRANSMIT_RET_VAL == STD_ON)
      Std_ReturnType PduRRet;
#endif /* (COM_EVALUATE_TRANSMIT_RET_VAL == STD_ON) */

      /* Tx request shall be issued now. In order to reduce possibility of race condition
       * we start MDT now and disable again when transmit shall be repeated again because of RFTR.
       * Note: it is still possible that MDT is violated if there are several trigger sources of
       * an I-Pdu (e.g Com_SendSignal(), Com_SendSignalGroup(), Com_SendSignalGroupArray
       * Com_TriggerIPDUSend() and
       * Com_MainFunctionTx(). During the time of checking that MDT is running
       * (outside this function) and starting of MDT below, several send requests may be issued
       * which violate MDT. However, changes are high that several rapidly Tx requests are
       * accumulated to one frame on the bus. */
#if (COM_MDT_QUEUE_AVAILABLE == STD_ON)
      Com_EB_HandleMDT(PduId, IPduPtr);
#endif /* (COM_MDT_QUEUE_AVAILABLE == STD_ON) */

      /* COM428: If not stated otherwise AUTOSAR COM will ignore all errors
       * from the underlying communication layer. Note: AUTOSAR COM supervises
       * the communication with deadline monitoring if configured. The specific
       * error codes from the underlying layer therefore can be ignored. In
       * case of update-bits this error codes are handled see COM062. */

#if (COM_EVALUATE_TRANSMIT_RET_VAL == STD_ON)
      PduRRet =
#else
         /* ignore return value */
         (void)
#endif /* (COM_EVALUATE_TRANSMIT_RET_VAL == STD_ON) */

      PduR_ComTransmit((PduIdType)IPduPtr->PduRTxPduId,&pduinfo);


#if (COM_EVALUATE_TRANSMIT_RET_VAL == STD_ON)

      if (PduRRet == E_OK)
      {

         /* COM062: If the parameter ComTxIPduClearUpdateBit of an I-PDU is
          * configured to Transmit, the AUTOSAR COM module shall clear all
          * update-bits of all contained signals and signal groups after this
          * I-PDU was sent out via PduR_ComTransmit and PduR_ComTransmit returned
          * E_OK. */
         /* clear update bits of all signals within the I-Pdu */
#if (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)
#if (!((COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_PRESENT_FOR_ALL) &&  \
   (COM_CL_UB_TX_TRIGGERTRANSMIT_ENABLE == STD_OFF) && \
   (COM_CL_UB_TX_TXCONFIRMATION_ENABLE == STD_OFF)))

         if (COM_GET_COM_TX_IPDU_CLEAR_UPDATE_BIT(IPduPtr) == COM_CL_UB_TRANSMIT)
#endif
         {
            Com_EB_ClearTxUpdateBits(IPduPtr);
         }
#endif /* (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) */

      }                         /* if (PduRRet == E_OK) */
#if (COM_RETRY_FAILED_TRANSMIT_REQ == STD_ON)
      else
      {                         /* (PduRRet != E_OK) */
         CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) PduStatusFlagsPtr =
            &Com_gDataMemPtr[(Com_gConfigPtr->ComTxIPduStatusBase + PduId)];

         TS_AtomicSetBit_8(PduStatusFlagsPtr, COM_TXPDU_SENDIMMEDIATELY);

#if (COM_MDT_QUEUE_AVAILABLE == STD_ON)
         /* Clear MDT since Tx request failed and shall be repeated within next
          * Com_MainFunctionTx() */
         TS_AtomicClearBit_8(PduStatusFlagsPtr, COM_TXPDU_MDTQUEUED);
#endif /* (COM_MDT_QUEUE_AVAILABLE == STD_ON) */

      }                         /* (PduRRet != E_OK) */
#endif /* (COM_RETRY_FAILED_TRANSMIT_REQ == STD_ON) */

#endif /* (COM_EVALUATE_TRANSMIT_RET_VAL == STD_ON) */

   }                            /* if (coretval == TRUE) */


   DBG_COM_EB_SEND_PDU_EXIT(PduId,IPduPtr);
   return;
}                               /* Com_EB_Send_Pdu */


#if (COM_MDT_QUEUE_AVAILABLE == STD_ON)
/** \brief Com_EB_HandleMDT
 * starts MDT if configured
 * \param[in] PduId - Id of the IPdu the API call was called for
 * \param[in] IPduPtr - reference to configuration of Pdu
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_HandleMDT
(
   ComIPduRefType PduId,
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
)
{

   /* Get MDT */
   /* Deviation MISRA-2 */
   /* Deviation MISRA-5 */
   ComTxIPduMinimumDelayTimeFactorType const MDT = COM_GET_MDT(IPduPtr);

   DBG_COM_EB_HANDLEMDT_ENTRY(PduId,IPduPtr);
   if (MDT > 0)
   {
      Com_EB_MdtQueue(PduId, IPduPtr, MDT);
   }


   DBG_COM_EB_HANDLEMDT_EXIT(PduId,IPduPtr);
   return;
}                               /* Com_EB_HandleMDT */
#endif /* (COM_MDT_QUEUE_AVAILABLE == STD_ON) */


/** \brief Com_EB_HandleTxIPdu_Start - starts a Tx IPdu
 * Preconditions:
 * - prior to this call, the COM module shall be initialized
 * \param[in] IPduPtr - configuration of the I-Pdu
 * \param[in] Initialize - defines if the Pdu group should be initialized
 * \param[in] IPduId - Id of the I-Pdu
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_HandleTxIPdu_Start
(
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
   boolean Initialize,
   ComIPduRefType IPduId
)
{
   uint8 BitRes;

   DBG_COM_EB_HANDLETXIPDU_START_ENTRY(IPduPtr,Initialize,IPduId);

   /* If the IPdu is not yet started */
   TS_GetBit(&Com_gDataMemPtr[(Com_gConfigPtr->ComTxIPduStatusBase + IPduId)],
      COM_TXPDU_STARTED, uint8, BitRes);
   if (BitRes == FALSE)
   {
      uint8 hlp_ret = E_OK;

      if (Initialize == TRUE)
      {
         /* Re-initialize the IPdu (including shadow signal buffers of
          * signal groups)*/
         hlp_ret = Com_EB_InitTxIPdu(IPduId);
      }                /* if (Initialize == TRUE) */

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_OFF)
      TS_PARAM_UNUSED(hlp_ret);
#else
      /* CHECK: NOPARSE */
      if (E_OK == hlp_ret)
         /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */
      {
         Com_EB_StartIPdu(IPduPtr, IPduId);
      }
   }                   /* if (BitRes == FALSE) */

   DBG_COM_EB_HANDLETXIPDU_START_EXIT(IPduPtr,Initialize,IPduId);
}                               /* Com_EB_HandleTxIPdu_Start */


/** \brief Com_EB_HandleTxIPdu_Stop - stops a Tx IPdu
 * Preconditions:
 * - prior to this call, the COM module shall be initialized
 * \param[in] IPduPtr - configuration of the I-Pdu
 * \param[in] IPduId - Id of the I-Pdu
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_HandleTxIPdu_Stop
(
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
   ComIPduRefType IPduId
)
{
   uint8 BitRes;

#if (COM_TM_AVAILABLE == STD_ON)
   uint8 AktTM;
#endif /* (COM_TM_AVAILABLE == STD_ON) */
   DBG_COM_EB_HANDLETXIPDU_STOP_ENTRY(IPduPtr,IPduId);

   /* Stop group: Clear the started-flag for the IPDU */
   TS_AtomicClearBit_8(&Com_gDataMemPtr[(Com_gConfigPtr->ComTxIPduStatusBase + IPduId)],
                     COM_TXPDU_STARTED);

   /* Cancel sending of pending Pdus */
   TS_AtomicClearBit_8(&Com_gDataMemPtr[(Com_gConfigPtr->ComTxIPduStatusBase + IPduId)],
         COM_TXPDU_SENDIMMEDIATELY);

#if (COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON)
   /* cancel Tx deadline monitoring, if running */
   TS_GetBit(&Com_gDataMemPtr[(Com_gConfigPtr->ComTxIPduStatusBase + IPduId)],
             COM_TXPDU_TXDMQUEUED, uint8, BitRes);
   if (BitRes == TRUE)
   {

      /* clear TxDM-queued-flag */
      TS_AtomicClearBit_8(&Com_gDataMemPtr[(Com_gConfigPtr->ComTxIPduStatusBase + IPduId)],
                        COM_TXPDU_TXDMQUEUED);

#if (COM_CBK_TX_ERR_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE)
      {
         {
            ComSignalRefType j;

            ComSignalRefType signalId;
            P2CONST(ComTxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr;

            for (j = IPduPtr->ComIPduSignalRefFirst;
                 j < (IPduPtr->ComIPduSignalRefFirst
                 + IPduPtr->ComIPduSignalRefNum); j++)
            {
               /* Get signal id and pointer to config of the signal in
                * the signal list of the IPdu */
               /* Deviation MISRA-2, MISRA-5 <+7> */
               signalId =
                  (ComSignalRefType) *
                  (COM_GET_CONFIG_ELEMENT
                   (ComSignalRefType, (Com_gConfigPtr->ComTxIPduSignalListRef), (j)));
               /* Deviation MISRA-2 */
               /* Deviation MISRA-5 */
               SignalPtr = COM_GET_CONFIG_ELEMENT(ComTxSignalType,
                     Com_gConfigPtr->ComTxSignalRef, signalId);

               if (SignalPtr->ComErrorNotification != COM_CBK_TX_ERR_PTR_NULL)
               {
                  /* call callback */
                  Com_CbkTxErr_Array[SignalPtr->ComErrorNotification] ();
               }
            }             /* for */
         }

#if (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
         {
            ComSignalGroupRefType j;

            P2CONST(ComTxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr;
            ComSignalGroupRefType SignalGId;     /* Id of signal group which belongs to Pdu */

            for (j = IPduPtr->ComIPduSignalGroupRefFirst;
                 j < (IPduPtr->ComIPduSignalGroupRefFirst
                 + IPduPtr->ComIPduSignalGroupRefNum); j++)
            {
               /* Get signal id and pointer to config of the signal in
                * the signal group list of the IPdu */
               /* Deviation MISRA-2, MISRA-5 <+7> */
               SignalGId =
                  (ComSignalGroupRefType) *
                  (COM_GET_CONFIG_ELEMENT
                   (ComSignalGroupRefType, (Com_gConfigPtr->ComTxIPduSignalGroupListRef), (j)));
               /* Deviation MISRA-2 */
               /* Deviation MISRA-5 */
               SignalGPtr = COM_GET_CONFIG_ELEMENT(ComTxSignalGroupType,
                     Com_gConfigPtr->ComTxSignalGroupRef, SignalGId);

               if (SignalGPtr->ComErrorNotification != COM_CBK_TX_ERR_PTR_NULL)
               {
                  /* call callback */
                  Com_CbkTxErr_Array[SignalGPtr->ComErrorNotification] ();
               }
            }             /* for */
         }
#endif /* (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */


      }

#endif /* #if (COM_CBK_TX_ERR_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

   }                            /* if (BitRes == TRUE) */

#endif /* (COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) */


#if (COM_TM_AVAILABLE == STD_ON)
   /* If the IPdu is sent periodically, stop it */

   /* Get the actual transmission mode */
   /* Have a look if the reason for sending is a periodic event */
   TS_GetBit(&Com_gDataMemPtr[(Com_gConfigPtr->ComTxIPduStatusBase + IPduId)],
             COM_TXPDU_TMSSTATE, uint8, BitRes);

   /* get current TM */
   AktTM = COM_GET_COM_TX_MODE(BitRes, IPduPtr->ComTxModeModes);

   switch (AktTM)
   {
#if (COM_TX_MODE_DIRECT_ENABLE == STD_ON)
      case COM_TX_MODE_MODE_DIRECT:
#endif /* (COM_TX_MODE_DIRECT_ENABLE == STD_ON) */
         /* Deviation MISRA-1 */
         /* fall through */
      case COM_TX_MODE_MODE_NONE:
         break;

#if (COM_TX_MODE_N_TIMES_ENABLE == STD_ON)
      case COM_TX_MODE_MODE_N_TIMES:
#endif /* (COM_TX_MODE_N_TIMES_ENABLE == STD_ON) */
         /* fall through */
#if (COM_TX_MODE_MIXED_N_TIMES_ENABLE == STD_ON)
      case COM_TX_MODE_MODE_MIXED_N_TIMES:
#endif /* (COM_TX_MODE_MIXED_N_TIMES_ENABLE == STD_ON) */
         /* fall through */
#if (COM_TX_MODE_MIXED_DIRECT_ENABLE == STD_ON)
      case COM_TX_MODE_MODE_MIXED_DIRECT:
#endif /* COM_TX_MODE_MIXED_DIRECT_ENABLE */

#if (COM_TX_MODE_PERIODIC_ENABLE == STD_ON)
      case COM_TX_MODE_MODE_PERIODIC:
         /* fall through */
#endif /* (COM_TX_MODE_PERIODIC_ENABLE == STD_ON) */

#if (COM_PERIODIC_QUEUE_AVAILABLE == STD_ON)
         /* unqueue the IPdu by clearing
          * its Tx-queued flag for Periodic. */
         TS_AtomicClearBit_8(&Com_gDataMemPtr
                           [(Com_gConfigPtr->ComTxIPduStatusBase + IPduId)],
                           COM_TXPDU_PERIODICSENDQUEUED);
#endif /* (COM_PERIODIC_QUEUE_AVAILABLE == STD_ON) */

#if (COM_N_TIMES_QUEUE_AVAILABLE == STD_ON)
         /* unqueue the IPdu by clearing
          * its Tx-queued flag for NTImes. */
         TS_AtomicClearBit_8(&Com_gDataMemPtr
                           [(Com_gConfigPtr->ComTxIPduStatusBase + IPduId)],
                           COM_TXPDU_NTIMESSENDQUEUED);
#endif /* (COM_N_TIMES_QUEUE_AVAILABLE == STD_ON) */

#if ((COM_PERIODIC_QUEUE_AVAILABLE == STD_ON) || (COM_N_TIMES_QUEUE_AVAILABLE == STD_ON))
         break;
#endif
         /* CHECK: NOPARSE */
      default:
         COM_UNREACHABLE_CODE_ASSERT(COMServiceId_IpduGroupControl);
         break;
         /* CHECK: PARSE */

   }                   /* end switch (AktTM) */
#endif /* (COM_TM_AVAILABLE == STD_ON) */


   DBG_COM_EB_HANDLETXIPDU_STOP_EXIT(IPduPtr,IPduId);
   return;
}                               /* Com_EB_HandleTxIPdu_Stop */


/* CHECK: NOPARSE */
#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)

/** \brief Com_EB_CheckTxIpdu check if the configuration of an I-Pdu is
 * plausible
 * \param[in] IPduPtr pointer to the configuration of the Tx-IPdu
 * \retval E_OK if config is plausible
 * \retval E_NOT_OK if config is wrong
 */
_COM_STATIC_ FUNC(uint8, COM_CODE)Com_EB_CheckTxIpdu
(
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
)
{
   uint8 retval = E_OK;

   DBG_COM_EB_CHECKTXIPDU_ENTRY(IPduPtr);

   if (NULL_PTR == IPduPtr)
   {
      COM_PRECONDITION_ASSERT(
            (NULL_PTR == IPduPtr),
            COMServiceId_Init);
      retval = E_NOT_OK;
   }
   else if (IPduPtr->ComConfigCheckData != COM_CONFIG_CHECK_TX_IPDU)
   {
      COM_PRECONDITION_ASSERT(
            (IPduPtr->ComConfigCheckData == COM_CONFIG_CHECK_TX_IPDU),
            COMServiceId_Init);
      retval = E_NOT_OK;
   }
   else
   {
      boolean fail_condition;

#if (COM_TM_AVAILABLE == STD_ON)
#if (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)

      /* COM054: Note: Update-bits are not allowed if Direct/N-Times Transmission
       * Mode with n>1 is used */
      fail_condition =
#if (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL)
            (COM_GET_COM_TX_IPDU_CLEAR_UPDATE_BIT(IPduPtr) != COM_CL_UB_NEVER)
            &&
#endif /* (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL) */
            ( (COM_GET_COM_TX_MODE_TRUE(IPduPtr->ComTxModeModes) == COM_TX_MODE_MODE_N_TIMES)
                  ||
                  (COM_GET_COM_TX_MODE_FALSE(IPduPtr->ComTxModeModes) == COM_TX_MODE_MODE_N_TIMES)
            );
      if (fail_condition)
      {
         COM_PRECONDITION_ASSERT((!fail_condition), COMServiceId_Init);
         retval = E_NOT_OK;
      }

#endif /* (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) */


      /* If no reference is available, the transmission mode as to be
       * COM_TX_MODE_MODE_NONE or COM_TX_MODE_MODE_MIXED_DIRECT */

      fail_condition =
            (!((COM_GET_COM_TX_MODE_TRUE(IPduPtr->ComTxModeModes) == COM_TX_MODE_MODE_NONE)
                  ||
                  (COM_GET_COM_TX_MODE_TRUE(IPduPtr->ComTxModeModes) == COM_TX_MODE_MODE_DIRECT))
            )
            &&
            (COM_GET_COM_TX_MODE_REF_TRUE(IPduPtr) == COM_TX_MODE_INVALID);
      if (fail_condition)
      {
         COM_PRECONDITION_ASSERT(!(fail_condition), COMServiceId_Init);
         retval = E_NOT_OK;
      }

#if (COM_TMS_ENABLE == STD_ON)

      /* check if Transmission Mode FALSE is configured right */
      fail_condition =
            (!((COM_GET_COM_TX_MODE_FALSE(IPduPtr->ComTxModeModes) == COM_TX_MODE_MODE_NONE)
                  ||
                  (COM_GET_COM_TX_MODE_FALSE(IPduPtr->ComTxModeModes) == COM_TX_MODE_MODE_DIRECT))
            )
            &&
            (COM_GET_COM_TX_MODE_REF_FALSE(IPduPtr) == COM_TX_MODE_INVALID);
      if (fail_condition)
      {
         COM_PRECONDITION_ASSERT((!fail_condition), COMServiceId_Init);
         retval = E_NOT_OK;
      }

#endif /* (COM_TMS_ENABLE == STD_ON) */

#endif /* (COM_TM_AVAILABLE == STD_ON) */
   }


   DBG_COM_EB_CHECKTXIPDU_EXIT(retval,IPduPtr);
   return retval;
}

#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */
/* CHECK: PARSE */


/** \brief Com_EB_InitTxIPdu_PduBuffer
 * function which initializes the IPdu-buffer of a Tx-IPdu
 * \param[in] IPduPtr pointer to the configuration of the Tx-IPdu
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_InitTxIPdu_PduBuffer
(
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
)
{


#if (COM_SIGNAL_INIT_VALUE_ENABLE == STD_ON)
   {
      /* a init value for the I-Pdu is available */
      /* pointer to first byte of init value */
      /* Deviation MISRA-2 */
      /* Deviation MISRA-5 */
      CONSTP2CONST(uint8, AUTOMATIC, COM_APPL_CONST) valPtr =
         COM_GET_CONFIG_ELEMENT(uint8, IPduPtr->ComInitValueRef, 0U);
      DBG_COM_EB_INITTXIPDU_PDUBUFFER_ENTRY(IPduPtr);
      /* copy PDU Init data to PDU buffer */
      TS_MemCpy(&Com_gDataMemPtr[IPduPtr->ComIPduValueRef], valPtr, IPduPtr->ComIPduSize);

   }
#else
   {
      ComIPduSizeType j;
      DBG_COM_EB_INITTXIPDU_PDUBUFFER_ENTRY(IPduPtr);
      /* no init value is available, use the default value COM_SIGNAL_INIT_VALUE_CONSTANT instead */
      /* NOCOV-UNSUPPORTEDOPTIMIZATION */
      for (j = 0; j < (IPduPtr->ComIPduSize); j++)
      {
         Com_gDataMemPtr[(IPduPtr->ComIPduValueRef + j)] = (uint8) COM_SIGNAL_INIT_VALUE_CONSTANT;
      }

#if (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)
      Com_EB_ClearTxUpdateBits(IPduPtr);
#endif /* (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) */
   }

#endif /* (COM_SIGNAL_INIT_VALUE_ENABLE == STD_ON) */


   DBG_COM_EB_INITTXIPDU_PDUBUFFER_EXIT(IPduPtr);
   return;
}                               /* Com_EB_InitTxIPdu_PduBuffer */


#if (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)

/** \brief Com_EB_InitTxIPdu_SignalGroups
 * function which initializes the signal groups of a Tx-IPdu
 * \param[in] IPduPtr pointer to the configuration of the Tx-IPdu
 * \retval E_OK - success
 * \retval E_NOT_OK - in case of an config error
 */
_COM_STATIC_ FUNC(uint8, COM_CODE)Com_EB_InitTxIPdu_SignalGroups
(
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
)
{
   ComSignalGroupRefType i;
   uint8 retval = E_OK;

   DBG_COM_EB_INITTXIPDU_SIGNALGROUPS_ENTRY(IPduPtr);

   for (i = 0; i < IPduPtr->ComIPduSignalGroupRefNum; i++)
   {
      /* Get signal group id and pointer to config of the signal group in the
       * signal group list of the IPdu */
      ComSignalDescByteType byteSize;

       /* Id of signal group which belongs to Pdu */
      /* Deviation MISRA-2, MISRA-5 <+7>*/
      ComSignalGroupRefType const SignalGId =
         (ComSignalGroupRefType) *
         (COM_GET_CONFIG_ELEMENT
          (ComSignalGroupRefType,
           (Com_gConfigPtr->ComTxIPduSignalGroupListRef),
           (i + IPduPtr->ComIPduSignalGroupRefFirst)));

      /* Deviation MISRA-2 */
      /* Deviation MISRA-5 */
      CONSTP2CONST(ComTxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr =
         COM_GET_CONFIG_ELEMENT(ComTxSignalGroupType, Com_gConfigPtr->ComTxSignalGroupRef,
                                SignalGId);
#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
      /* CHECK: NOPARSE */
      if (NULL_PTR == SignalGPtr)
      {
          retval = E_NOT_OK;
          break;
      }
      if (SignalGPtr->ComConfigCheckData != COM_CONFIG_CHECK_TX_SIG_GROUP)
      {
          retval = E_NOT_OK;
          /* Deviation MISRA-3 */
          break;
      }
      /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */

#if (COM_BASED_TRANSFORMER_SUPPORT_TX == STD_ON)
   if (SignalGPtr->ComSignalGroupValueRef != COM_RAM_SIZE_MAX)
#endif /* (COM_BASED_TRANSFORMER_SUPPORT_TX == STD_ON) */
   {
      /* the signal group has a shadow buffer assigned which has to be initialized */
      byteSize = SignalGPtr->ComByteSize;
      if (SignalGPtr->ComBitMaskFirstPart > 0U)
      {
         byteSize++;
      }
      if (SignalGPtr->ComBitMaskLastPart > 0U)
      {
         byteSize++;
      }

      {
         /* get the first byte of the signal group in the Pdu */
         CONSTP2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT)pduStartPos =
               &Com_gDataMemPtr[(IPduPtr->ComIPduValueRef + SignalGPtr->ComSignalPositionInByte)];

         /* copy the init value of the Pdu to the shadow buffer */
         TS_MemCpy(&Com_gDataMemPtr[(SignalGPtr->ComSignalGroupValueRef)],
               pduStartPos,
               byteSize);
      }
   }

#if (COM_TMS_ENABLE == STD_ON)
      /* clear the COM_TXSG_TMSSTATE flag */
      TS_AtomicClearBit_8(COM_TXSG_TMS_MIGHT_CHANGE_FLAG_ADDRESS(SignalGId),
                        COM_TXSG_TMSSTATE);

      /* clear the COM_TXSG_TMSMIGHTCHANGE flag */
      TS_AtomicClearBit_8(COM_TXSG_TMS_MIGHT_CHANGE_FLAG_ADDRESS(SignalGId),
                        COM_TXSG_TMSMIGHTCHANGE);

      /* clear the flags of all group signals within the group if filter are configured */
      if (SignalGPtr->ComGroupSignalWithFilterRefNum > 0U)
      {
         ComTxGroupSignalRefType length = ((SignalGPtr->ComGroupSignalWithFilterRefNum + 7U) / 8U);
         /* copy init values for TMS flags */
         /* Deviation MISRA-2 */
         /* Deviation MISRA-5 */
         TS_MemCpy(&Com_gDataMemPtr[(SignalGPtr->ComSignalGTMSFlagsRef)],
               COM_GET_CONFIG_ELEMENT(uint8, SignalGPtr->ComSignalGTMSFlagsInitValueRef, 0U),
               length);
      }

      {
         uint16 j;
         /* Set the COM_TXSG_TMSSTATE if TM of signal group is TRUE */
         for (j = 0U; j < ((SignalGPtr->ComGroupSignalWithFilterRefNum + 7U) / 8U); j++)
         {
            if (Com_gDataMemPtr[(SignalGPtr->ComSignalGTMSFlagsRef + j)] > 0U)
            {
               TS_AtomicSetBit_8(COM_TXSG_TMS_MIGHT_CHANGE_FLAG_ADDRESS(SignalGId),
                                 COM_TXSG_TMSSTATE);
            }
         }
      }


#endif /* (COM_TMS_ENABLE == STD_ON) */

  }                            /* for (i = 0; i < IPduPtr->ComIPduSignalGroupRefNum; i++) */
   DBG_COM_EB_INITTXIPDU_SIGNALGROUPS_EXIT(retval,IPduPtr);
   return retval;
}

#endif /* (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */


/** \brief Com_EB_InitTxIPdu_HandleFlags
 * function which initializes the flags of a Tx-IPdu
 * \param[in] IPduPtr pointer to the configuration of the Tx-IPdu
 * \param[in] PduId PduId to start
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_InitTxIPdu_HandleFlags
(
      P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
      ComIPduRefType TxPduId
)
{

   /* clear all flags of the IPdu */



   DBG_COM_EB_INITTXIPDU_HANDLEFLAGS_ENTRY(IPduPtr,TxPduId);
   Com_gDataMemPtr[(Com_gConfigPtr->ComTxIPduStatusBase + TxPduId)] = 0U;

   /* After this reset of all flags the Transmission Mode false is selected.
    * If there is a transmission mode true select it, otherwise leave it as is.
    * TM false is not invalid, so it MAY eventually be the transmission
    * mode which is selected after startup for the respective IPdu.
    * So we select this transmission mode here; if the startup TM is
    * going to be the TM true, the initial evaluation of the filters
    * will lead to the correct selection of TM true later on */

#if (COM_TM_AVAILABLE == STD_ON)
   /* If there is a TM true, TM true must always be selected - do it! */
   if (COM_GET_COM_TX_IPDU_INIT_TM(IPduPtr) == TRUE)
   {
      TS_AtomicSetBit_8(&Com_gDataMemPtr[(Com_gConfigPtr->ComTxIPduStatusBase + TxPduId)],
                      COM_TXPDU_TMSSTATE);
   }
#endif /* (COM_TM_AVAILABLE == STD_ON) */

#if (COM_TMS_ENABLE == STD_ON)
   /* Set the ComIPduTMSFlags */
   {

      /* calculate number of bytes which hold the TMS flags of the signals and
       * the signal groups */
      /* calculate number of bytes which hold the TMS flags of the signals and
       * the signal groups */
      uint16 NumberOfFlagsBits =
         IPduPtr->ComIPduSignalWithFilterRefNum
#if (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
+ IPduPtr->ComIPduSignalGroupWithFilterRefNum
#endif /* (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */
                                             ;

      uint16 NumberOfFlagsBytesFull = (NumberOfFlagsBits) / 8U;

      uint16 NumberOfFlagsBytesPartly = 0U;

      uint16 NumberOfFlagsBytes;

      if ((NumberOfFlagsBits % 8U) > 0U)
      {
         NumberOfFlagsBytesPartly = 1U;
      }

      NumberOfFlagsBytes = NumberOfFlagsBytesFull + NumberOfFlagsBytesPartly;

      /* copy init values for TMS flags */
      /* Deviation MISRA-2 */
      /* Deviation MISRA-5 */
      TS_MemCpy(&Com_gDataMemPtr[(IPduPtr->ComIPduTMSFlagsRef)],
            COM_GET_CONFIG_ELEMENT(uint8, IPduPtr->ComIPduTMSFlagsInitValueRef, 0U),
            NumberOfFlagsBytes);
   }

#endif /* (COM_TMS_ENABLE == STD_ON) */

   DBG_COM_EB_INITTXIPDU_HANDLEFLAGS_EXIT(IPduPtr,TxPduId);
}                               /* Com_EB_InitTxIPdu_HandleFlags */

#if (COM_TMS_ENABLE == STD_ON)

#if ((COM_TXF_MASKNEWDIFFERSMASKOLD_EN == STD_ON) || \
      (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON))

/** \brief Com_EB_InitTxIPdu_Signals
 * function which initializes the signals of a Tx-IPdu (filter)
 * \param[in] IPduPtr pointer to the configuration of the Tx-IPdu
 * \retval E_OK - success
 * \retval E_NOT_OK - in case of an config error
 */
_COM_STATIC_ FUNC(uint8, COM_CODE)Com_EB_InitTxIPdu_Signals
(
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
)
{

   ComSignalRefType i;
   uint8 retval = E_OK;

   DBG_COM_EB_INITTXIPDU_SIGNALS_ENTRY(IPduPtr);

   for (i = 0; i < IPduPtr->ComIPduSignalWithFilterRefNum; i++)
   {
      /* Get signal id and pointer to config of the signal in the signal list of the IPdu */
      /* Deviation MISRA-2, MISRA-5 <+7> */
      ComSignalRefType const signalId =
         (ComSignalRefType) *
         (COM_GET_CONFIG_ELEMENT
          (ComSignalRefType,
           (Com_gConfigPtr->ComTxIPduSignalListRef), (i + IPduPtr->ComIPduSignalRefFirst)));

      /* Deviation MISRA-2 */
      /* Deviation MISRA-5 */
      CONSTP2CONST(ComTxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr =
         COM_GET_CONFIG_ELEMENT(ComTxSignalType, Com_gConfigPtr->ComTxSignalRef, signalId);

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
      /* CHECK: NOPARSE */
      if (NULL_PTR == SignalPtr)
      {
          retval = E_NOT_OK;
          break;
      }
      if (SignalPtr->ComConfigCheckData != COM_CONFIG_CHECK_TX_SIGNAL)
      {
          retval = E_NOT_OK;
          /* Deviation MISRA-3 */
          break;
      }
      /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */

#if (COM_TXF_MASKNEWDIFFERSMASKOLD_EN == STD_ON)
      /* check if the signal has the filter COM_F_MASK_NEW_DIFFERS_MASK_OLD */
      if (SignalPtr->ComFilterType == COM_F_MASK_NEW_DIFFERS_MASK_OLD)
      {
         /* ComFilterSignalValueRef has to be configured  */
#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
         /* CHECK: NOPARSE */
         if (SignalPtr->ComFilterSignalValueRef == COM_SIGNAL_BUFFER_REF_INVALID)
         {
             retval = E_NOT_OK;
             /* Deviation MISRA-3 */
             break;
         }
         /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */
         {

#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
            Com_TS_SignalEndiannessType const endianness =
                  COM_GET_TX_SIGNAL_ENDIANNESS(SignalPtr);
#endif /* (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE) */

            ComCommonReadPropType ComReadProp;

            /* type of the signal */
            Com_TS_SignalTypeType const SignalType =
                  COM_GET_TX_SIGNAL_SIGNAL_TYPE(SignalPtr);

#if (COM_SIGNAL_BYTE_ALIGN == STD_ON)

            /* get the Rx bit position from the Tx bit position */
            ComSignalDescBitType const ComSignalPositionInByte =
                  Com_EB_Tx2RxPosinByte(
                        SignalPtr->TxBasicParam.ComSignalPositionInByte
#if ((COM_ENDIANNESS_CONVERSION == COM_LITTLE_ENDIAN) || \
                        (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE))
                        ,SignalPtr->ComBitSize
#if (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON)
                        ,SignalType
#endif /* (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON) */
#endif /* ((COM_ENDIANNESS_CONVERSION == COM_LITTLE_ENDIAN) || \
                  (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)) */
#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
                        ,endianness
#endif /* (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE) */
                  );

#elif (COM_SIGNAL_BYTE_ALIGN == STD_OFF)

            /* get the Rx bit position from the Tx bit position */
            ComSignalDescBitType const ComSignalPositionInBit =
                  Com_EB_Tx2RxPosinBit(
                        SignalPtr->TxBasicParam.ComSignalPositionInBit
                        ,SignalPtr->ComBitSize
#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
                        ,endianness
#endif /* (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE) */
                  );

#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_ON) */


            ComReadProp.pdudataptrRAM = &Com_gDataMemPtr[(IPduPtr->ComIPduValueRef)];
#if (COM_SIGNAL_INIT_VALUE_ENABLE == STD_ON)
            ComReadProp.pdudataptrROM = COM_CONST_NULL_PTR;
#endif /* (COM_SIGNAL_INIT_VALUE_ENABLE == STD_ON) */

#if (COM_SIGNAL_BYTE_ALIGN == STD_ON)
            ComReadProp.ComSignalPositionInByte = ComSignalPositionInByte;
#elif (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
            ComReadProp.ComSignalPositionInBit = ComSignalPositionInBit;
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_ON) */

            ComReadProp.ComBitSize= SignalPtr->ComBitSize;
#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
            ComReadProp.Endianness = endianness;
#endif /* (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE) */
            ComReadProp.SignalType = SignalType;
#if (COM_VALUE_INIT_REPLACE == STD_ON)
            ComReadProp.TakePtrROM = FALSE;
#endif /* (COM_VALUE_INIT_REPLACE == STD_ON) */

            {
               /* get value from PDU buffer or init value */
               uint32 const value =
                     Com_EB_ReadFromPduOrShadowBuffer(&ComReadProp);

               /* write value into buffer of signal */
               Com_EB_SetBufferUInt32(value,
                  SignalType,
                  SignalPtr->ComFilterSignalValueRef);
            }

         }  /* else from if (SignalPtr->ComFilterSignalValueRef == COM_SIGNAL_BUFFER_REF_INVALID) */
      }                /* if (SignalPtr->ComFilterType == COM_F_MASK_NEW_DIFFERS_MASK_OLD) */
#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
      /* CHECK: NOPARSE */
      else
      {
         /* ComFilterSignalValueRef must not be configured */
         if (SignalPtr->ComFilterSignalValueRef != COM_SIGNAL_BUFFER_REF_INVALID)
         {
             retval = E_NOT_OK;
             /* Deviation MISRA-3 */
             break;
         }
      }
      /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */

#endif /* (COM_TXF_MASKNEWDIFFERSMASKOLD_EN == STD_ON) */

#if (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON)
      /* check if the signal has the filter COM_F_ONE_EVERY_N */
      if (SignalPtr->ComFilterType == COM_F_ONE_EVERY_N)
      {
         /* reset the filter */
         Com_ResetFilerOneEveryN(SignalPtr->ComFilterRef);
      }

#endif /* (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON) */

   }                           /* for (i = 0; i < IPduPtr->ComIPduSignalWithFilterRefNum; i++) */


   DBG_COM_EB_INITTXIPDU_SIGNALS_EXIT(retval,IPduPtr);
   return retval;
}                               /* Com_EB_InitTxIPdu_Signals */


#if (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
/** \brief Com_EB_InitTxIPdu_GroupSignals
 * function which initializes the group signals of a Tx-IPdu
 * \param[in] PduId PduId to start
 * \retval E_OK - success
 * \retval E_NOT_OK - in case of an config error
 */
_COM_STATIC_ FUNC(uint8, COM_CODE)Com_EB_InitTxIPdu_GroupSignals
(
   ComIPduRefType TxPduId
)
{

   ComTxGroupSignalRefType i;
   uint8 retval = E_OK;

   /* reference to the configuration of a group signal */
   P2CONST(ComTxGroupSignalType, AUTOMATIC, COM_APPL_CONST) GSignalPtr;

   /* pointer to config structure of a signal group */
   P2CONST(ComTxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr;

   DBG_COM_EB_INITTXIPDU_GROUPSIGNALS_ENTRY(TxPduId);

   for (i = 0; i < Com_gConfigPtr->ComTxGroupSignalArraySize; i++)
   {

      /* Deviation MISRA-2 */
      /* Deviation MISRA-5 */
      GSignalPtr =
         COM_GET_CONFIG_ELEMENT(ComTxGroupSignalType,
               Com_gConfigPtr->ComTxGroupSignalRef, i);

      /* check if the configuration is valid */
#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
      /* CHECK: NOPARSE */
      if (NULL_PTR == GSignalPtr)
      {
          retval = E_NOT_OK;
          break;
      }
      if (GSignalPtr->ComConfigCheckData != COM_CONFIG_CHECK_TX_GROUP_SIG)
      {
          retval = E_NOT_OK;
          /* Deviation MISRA-3 */
          break;
      }
      /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */

      /* get the configuration of the Group Signal to which this group signal belongs to */
      /* Deviation MISRA-2 */
      /* Deviation MISRA-5 */
      SignalGPtr =
         COM_GET_CONFIG_ELEMENT(ComTxSignalGroupType, Com_gConfigPtr->ComTxSignalGroupRef,
               GSignalPtr->ComSignalGroupRef);

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
      /* CHECK: NOPARSE */
      if (NULL_PTR == SignalGPtr)
      {
          retval = E_NOT_OK;
          /* Deviation MISRA-3 */
          break;
      }
      if (SignalGPtr->ComConfigCheckData != COM_CONFIG_CHECK_TX_SIG_GROUP)
      {
          retval = E_NOT_OK;
          /* Deviation MISRA-3 */
          break;
      }
      /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */

      /* Check if the signal group belongs to the current I-Pdu  */
      if (SignalGPtr->ComIPduRef == TxPduId)
      {
#if (COM_TXF_MASKNEWDIFFERSMASKOLD_EN == STD_ON)
         /* check if the signal has the filter COM_F_MASK_NEW_DIFFERS_MASK_OLD */
         if (GSignalPtr->ComFilterType == COM_F_MASK_NEW_DIFFERS_MASK_OLD)
         {
            /* ComFilterSignalValueRef has to be configured  */
#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
            /* CHECK: NOPARSE */
            if (GSignalPtr->ComFilterSignalValueRef == COM_SIGNAL_BUFFER_REF_INVALID)
            {
               retval = E_NOT_OK;
               /* Deviation MISRA-3 */
               break;
            }
            /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */
            {

#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
               Com_TS_SignalEndiannessType const endianness =
                  COM_GET_TX_GROUP_SIGNAL_ENDIANNESS(GSignalPtr);
#endif /* (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE) */

               ComCommonReadPropType ComReadProp;

               /* type of the group signal */
               Com_TS_SignalTypeType const SignalType =
                     COM_GET_TX_GROUP_SIGNAL_SIGNAL_TYPE(GSignalPtr);

#if (COM_SIGNAL_BYTE_ALIGN == STD_ON)

               ComSignalDescBitType const ComSignalPositionInByte  =

                     Com_EB_Tx2RxPosinByte(
                           GSignalPtr->ComSignalPositionInByte
#if ((COM_ENDIANNESS_CONVERSION == COM_LITTLE_ENDIAN) || \
                  (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE))
                           ,GSignalPtr->ComBitSize
#if (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON)
                           ,SignalType
#endif /* (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON) */
#endif /* ((COM_ENDIANNESS_CONVERSION == COM_LITTLE_ENDIAN) || \
            (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)) */
#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
                           ,endianness
#endif /* (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE) */
                     );

#elif (COM_SIGNAL_BYTE_ALIGN == STD_OFF)

               ComSignalDescBitType const ComSignalPositionInBit =
                     Com_EB_Tx2RxPosinBit(
                           GSignalPtr->ComSignalPositionInBit
                           ,GSignalPtr->ComBitSize
#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
                           ,endianness
#endif /* (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE) */
                     );
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_ON) */


               ComReadProp.pdudataptrRAM = &Com_gDataMemPtr[(SignalGPtr->ComSignalGroupValueRef)];
#if (COM_SIGNAL_INIT_VALUE_ENABLE == STD_ON)
               ComReadProp.pdudataptrROM = COM_CONST_NULL_PTR;
#endif /* (COM_SIGNAL_INIT_VALUE_ENABLE == STD_ON) */

#if (COM_SIGNAL_BYTE_ALIGN == STD_ON)
               ComReadProp.ComSignalPositionInByte = ComSignalPositionInByte;
#elif (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
               ComReadProp.ComSignalPositionInBit = ComSignalPositionInBit;
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_ON) */

               ComReadProp.ComBitSize= GSignalPtr->ComBitSize;
#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
               ComReadProp.Endianness = endianness;
#endif /* (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE) */
               ComReadProp.SignalType = SignalType;
#if (COM_VALUE_INIT_REPLACE == STD_ON)
               ComReadProp.TakePtrROM = FALSE;
#endif /* (COM_VALUE_INIT_REPLACE == STD_ON) */

               {

                  /* get value from signal group shadow buffer value */
                  uint32 const value =
                        Com_EB_ReadFromPduOrShadowBuffer(&ComReadProp);

                  /* write value into buffer of signal */
                  Com_EB_SetBufferUInt32(value,
                     SignalType,
                     GSignalPtr->ComFilterSignalValueRef);
               }

            }   /* else (GSignalPtr->ComFilterSignalValueRef == COM_SIGNAL_BUFFER_REF_INVALID) */
         }   /* if (GSignalPtr->ComFilterType == COM_F_MASK_NEW_DIFFERS_MASK_OLD) */
#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
         /* CHECK: NOPARSE */
         else
         {
            /* ComFilterSignalValueRef must not be configured */
            if (GSignalPtr->ComFilterSignalValueRef != COM_SIGNAL_BUFFER_REF_INVALID)
            {
               retval = E_NOT_OK;
               /* Deviation MISRA-3 */
               break;
            }
         }
         /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */

#endif /* (COM_TXF_MASKNEWDIFFERSMASKOLD_EN == STD_ON) */


#if (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON)
      /* check if the signal has the filter COM_F_ONE_EVERY_N */
      if (GSignalPtr->ComFilterType == COM_F_ONE_EVERY_N)
      {
         /* reset the filter */
         Com_ResetFilerOneEveryN(GSignalPtr->ComFilterRef);
      }

#endif /* (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON) */
      }                      /* if (SignalGPtr->ComIPduRef != TxPduId) */

   }                       /* for (i = 0; i < SignalGPtr->ComGroupSignalWithFilterRefNum; i++) */
   DBG_COM_EB_INITTXIPDU_GROUPSIGNALS_EXIT(retval,TxPduId);
   return retval;
}                               /* Com_EB_InitTxIPdu_GroupSignals */

#endif /* (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

#endif /* ((COM_TXF_MASKNEWDIFFERSMASKOLD_EN == STD_ON) || \
      (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON)) */

#endif /* (COM_TMS_ENABLE == STD_ON) */



/** \brief Com_EB_StartIPdu
 * function which manages starting a single IPdu
 * Preconditions:
 * - prior to this call, the COM module shall be initialized
 * - the Pdu must not be started before
 * \param[in] IPduPtr pointer to the configuration of the I-Pdu
 * \param[in] PduId PduId to start
 * \retval None
 */

_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_StartIPdu
(
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
   ComIPduRefType PduId
)
{

#if (COM_TM_AVAILABLE == STD_ON)
   uint8 AktTM;                 /*  current Transmission Mode */
   uint8 BitRes;
#if ((COM_TX_MODE_MIXED_N_TIMES_ENABLE == STD_ON) || \
      (COM_TX_MODE_MIXED_DIRECT_ENABLE == STD_ON) || \
      (COM_TX_MODE_PERIODIC_ENABLE == STD_ON))
   ComTxModeIdxType TMRef;      /* reference to the TM configuration */
#endif
#endif /* (COM_TM_AVAILABLE == STD_ON) */

#if (COM_PERIODIC_QUEUE_AVAILABLE == STD_ON)
   Com_PeriodicSendNextDueTimeType TimeToSendPeriodic = 0;      /* for cyclic sends */
   Com_PeriodicSendNextDueTimeType TimeToSendFirst = 0; /* for first sends */
#endif /* (COM_PERIODIC_QUEUE_AVAILABLE == STD_ON) */

   CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) IPduFlagBytePtr =
         &Com_gDataMemPtr[(Com_gConfigPtr->ComTxIPduStatusBase + PduId)];


   DBG_COM_EB_STARTIPDU_ENTRY(IPduPtr,PduId);


   /* enter the critical */
   Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

   /* start the IPdu via setting the started flag */
   Com_SetBitUInt8(IPduFlagBytePtr, COM_TXPDU_STARTED);

   /* clear the TMS change flag, because the flag might have been set while
    * I-Pdu group was stopped. If would not have been cleared in the next
    * Com_MainFunctionTx call the switch would be done again */
   Com_ClearBitUInt8(IPduFlagBytePtr, COM_TXPDU_TMSCHANGED);

#if (COM_TM_AVAILABLE == STD_ON)
   /* get current TM state */
   TS_GetBit(IPduFlagBytePtr, COM_TXPDU_TMSSTATE, uint8, BitRes);
#endif /* (COM_TM_AVAILABLE == STD_ON) */

   /* exit the critical section */
   Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();

#if (COM_TM_AVAILABLE == STD_ON)

   /* get current TM */
   AktTM = COM_GET_COM_TX_MODE(BitRes, IPduPtr->ComTxModeModes);

#if ((COM_TX_MODE_MIXED_N_TIMES_ENABLE == STD_ON) || \
      (COM_TX_MODE_MIXED_DIRECT_ENABLE == STD_ON) || \
      (COM_TX_MODE_PERIODIC_ENABLE == STD_ON))
   TMRef = COM_GET_COM_TX_MODE_REF(BitRes, IPduPtr);
#endif

#if (COM_PERIODIC_QUEUE_AVAILABLE == STD_ON)
   /* if the transmission mode contains periodic sending,
    * start periodic transmissions; see if it is required
    * to send immediately */

   switch (AktTM)
   {
#if (COM_TX_MODE_MIXED_N_TIMES_ENABLE == STD_ON)
      case COM_TX_MODE_MODE_MIXED_N_TIMES:
         {
            /* Deviation MISRA-2, MISRA-5 <+6> */
            CONSTP2CONST(ComTxModeMixedNTimesType, AUTOMATIC, COM_APPL_CONST) TMMixedNTimesPtr =
                  COM_GET_CONFIG_ELEMENT(
                        ComTxModeMixedNTimesType,
                        Com_gConfigPtr->ComTxModeMixedNTimesRef,
                        TMRef
                        );
            TimeToSendFirst = COM_GET_TM_TIME_OFFSET_FACTOR(TMMixedNTimesPtr);
            TimeToSendPeriodic = TMMixedNTimesPtr->ComTxModeTimePeriodFactor;
         }
         break;
#endif /* (COM_TX_MODE_MIXED_N_TIMES_ENABLE == STD_ON) */

#if (COM_TX_MODE_PERIODIC_ENABLE == STD_ON)
      case COM_TX_MODE_MODE_PERIODIC:
#endif /* (COM_TX_MODE_PERIODIC_ENABLE == STD_ON) */

         /* fall through */
#if (COM_TX_MODE_MIXED_DIRECT_ENABLE == STD_ON)
      case COM_TX_MODE_MODE_MIXED_DIRECT:
#endif /* COM_TX_MODE_MIXED_DIRECT_ENABLE */

#if ((COM_TX_MODE_MIXED_DIRECT_ENABLE == STD_ON) || (COM_TX_MODE_PERIODIC_ENABLE == STD_ON))
         {
            /* Deviation MISRA-2, MISRA-5 <+6> */
            CONSTP2CONST(ComTxModePeriodicType, AUTOMATIC, COM_APPL_CONST) TMPeriodicPtr =
                  COM_GET_CONFIG_ELEMENT(
                        ComTxModePeriodicType,
                        Com_gConfigPtr->ComTxModePeriodicRef,
                        TMRef
                        );
            TimeToSendFirst = COM_GET_TM_TIME_OFFSET_FACTOR(TMPeriodicPtr);
            TimeToSendPeriodic = TMPeriodicPtr->ComTxModeTimePeriodFactor;
         }
#endif /* ((COM_TX_MODE_MIXED_DIRECT_ENABLE == STD_ON) || (COM_TX_MODE_PERIODIC_ENABLE == STD_ON)) */
         break;
      default:
         break;
   }                            /* switch (AktTM) */

#endif /* (COM_PERIODIC_QUEUE_AVAILABLE == STD_ON) */

   /* send immediately and schedule sending or only
    * schedule sending */
   switch (AktTM)
   {
#if (COM_TX_MODE_PERIODIC_ENABLE == STD_ON)
      case COM_TX_MODE_MODE_PERIODIC:
#endif /* (COM_TX_MODE_PERIODIC_ENABLE == STD_ON) */

         /* fall through */
#if (COM_TX_MODE_MIXED_DIRECT_ENABLE == STD_ON)
      case COM_TX_MODE_MODE_MIXED_DIRECT:
#endif /* COM_TX_MODE_MIXED_DIRECT_ENABLE */

         /* fall through */
#if (COM_TX_MODE_MIXED_N_TIMES_ENABLE == STD_ON)
      case COM_TX_MODE_MODE_MIXED_N_TIMES:
#endif /* (COM_TX_MODE_MIXED_N_TIMES_ENABLE == STD_ON) */

#if (COM_PERIODIC_QUEUE_AVAILABLE == STD_ON)
         {
            if (TimeToSendFirst == 0)
            {
               /* This means, the PDU must first be sent at
                * once and then in TimeToSendPeriodic cycle;
                * try sending at once */

               /* Since the Pdu cannot be started twice, MDT is not running */

               /* send the Pdu out */
               Com_EB_Send_Pdu(PduId, IPduPtr);


#if (COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON)

               /* Check if PDU has TxDM */
               if (COM_GET_COM_TX_IPDU_DM_AVAILABLE(IPduPtr) == COM_TX_DM_ON)
               {

                  /* Since the Pdu cannot be started twice, TxDM is not running */

                  /* Queue the Pdu */
                  /* Deviation MISRA-2 */
                  /* Deviation MISRA-5 */
                  Com_EB_TxDMQueue(PduId, COM_GET_TX_TIMEOUT_FACTOR(IPduPtr),
                                   IPduPtr->TxDMQueueRef);

               }                /* if (COM_GET_COM_TX_IPDU_DM_AVAILABLE(IPduPtr) == COM_TX_DM_ON) */
#endif /* (COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) */

            }
            else                /* if (TimeToSendFirst == 0) */
            {
               /* Sending the first time needs to be done
                * to some point in time later; let the "period"
                * being set for "next" sending be the time
                * to send first */
               TimeToSendPeriodic = TimeToSendFirst;
            }                   /* else from if (TimeToSendFirst == 0) */

            /* Schedule periodic sending */
            Com_EB_PeriodicSendQueue(TimeToSendPeriodic, IPduPtr->PeriodicQueueRef);

            /* Mark the PDU as send queued */
            TS_AtomicSetBit_8(IPduFlagBytePtr, COM_TXPDU_PERIODICSENDQUEUED);

         }
         break;
#endif /* (COM_PERIODIC_QUEUE_AVAILABLE == STD_ON) */

      case COM_TX_MODE_MODE_NONE:
      {
#if (COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON)
         /* rewind TxDM if TxDM is configured and only TM None is configured */
         Com_EB_TxDM_TMNone(IPduPtr, PduId);
#endif /* (COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) */
      }
      break;
      default:
         break;
   }                            /* switch (AktTM) */
#endif /* (COM_TM_AVAILABLE == STD_ON) */


   DBG_COM_EB_STARTIPDU_EXIT(IPduPtr,PduId);
   return;
}                               /* Com_EB_StartIPdu */



/** \brief Com_EB_HandleTxIPdu - handles a Tx IPdu
 * function which manages starting/stopping a Tx I-Pdu
 * Preconditions:
 * - prior to this call, the COM module shall be initialized
 *
 * \param[in] toBeActivated - state of start/stop
 * \param[in] IPduPtr - configuration of the I-Pdu
 * \param[in] Initialize - defines if the Pdu group should be initialized
 * in case of COM_START_GROUP
 * \param[in] IPduId - Id of the I-Pdu
 * \retval None
 */
TS_MOD_PRIV_DEFN FUNC(void, COM_CODE)Com_EB_HandleTxIPdu
(
   boolean toBeActivated,
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
   boolean Initialize,
   ComIPduRefType IPduId
)
{




   DBG_COM_EB_HANDLETXIPDU_ENTRY(toBeActivated,IPduPtr,Initialize,IPduId);
   if (TRUE == toBeActivated)
   {
      Com_EB_HandleTxIPdu_Start(IPduPtr, Initialize, IPduId);
   }
   else
   {
      Com_EB_HandleTxIPdu_Stop(IPduPtr, IPduId);
   }

   DBG_COM_EB_HANDLETXIPDU_EXIT(toBeActivated,IPduPtr,Initialize,IPduId);
}                               /* Com_EB_HandleTxIPdu */




/** \brief Com_EB_InitTxIPdu - initialize the specified Tx IPdu and the
 * shadow buffer if the signal groups belonging to the I-Pdu group.
 * NOTE does not clear the RAM buffers of ONE_EVERY_N filters
 * \param[in] TxPduId -IPdu which should be initialized
 * \retval E_OK if init was successful
 * \retval E_NOT_OK if init failed (wrong configuration)
 */

TS_MOD_PRIV_DEFN FUNC(uint8, COM_CODE) Com_EB_InitTxIPdu
(
   ComIPduRefType TxPduId
)
{
   uint8 retval = E_OK;
   uint8 hlp_retval;

   /* pointer to config structure of I-Pdu */
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr;

   DBG_COM_EB_INITTXIPDU_ENTRY(TxPduId);

   /* get IPdu to which TxPduId identifies and check if the IPdu is valid */
   /* Deviation MISRA-2 */
   /* Deviation MISRA-5 */
   IPduPtr = COM_GET_CONFIG_ELEMENT(ComTxIPduType, Com_gConfigPtr->ComTxIPduRef, TxPduId);

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
   /* CHECK: NOPARSE */
   hlp_retval = Com_EB_CheckTxIpdu(IPduPtr);
   if (hlp_retval != E_OK)
   {
      COM_PRECONDITION_ASSERT((hlp_retval == E_OK), COMServiceId_Init);
      retval = E_NOT_OK;
   }
   else
      /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */

   {
      /* initialize the pdu buffer */
      Com_EB_InitTxIPdu_PduBuffer(IPduPtr);

#if (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
      /* initialize signal groups of Pdu*/
      hlp_retval = Com_EB_InitTxIPdu_SignalGroups(IPduPtr);

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
      /* CHECK: NOPARSE */
      if (hlp_retval != E_OK)
      {
         COM_PRECONDITION_ASSERT((hlp_retval == E_OK), COMServiceId_Init);
         retval = E_NOT_OK;
      }
      /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */
#endif /* (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

      /* Handle the flags */
      Com_EB_InitTxIPdu_HandleFlags(IPduPtr, TxPduId);


#if ( (COM_TMS_ENABLE == STD_ON) &&                     \
      ((COM_TXF_MASKNEWDIFFERSMASKOLD_EN == STD_ON) ||  \
            (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON))    \
)

      /* initialize the signals (filter) */
      hlp_retval = Com_EB_InitTxIPdu_Signals(IPduPtr);

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
      /* CHECK: NOPARSE */
      if (hlp_retval != E_OK)
      {
         COM_PRECONDITION_ASSERT((hlp_retval == E_OK), COMServiceId_Init);
         retval = E_NOT_OK;
      }
      /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */

#if (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
      /* initialize the group signals (filter) */
      hlp_retval = Com_EB_InitTxIPdu_GroupSignals(TxPduId);

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
      /* CHECK: NOPARSE */
      if (hlp_retval != E_OK)
      {
         COM_PRECONDITION_ASSERT((hlp_retval == E_OK), COMServiceId_Init);
         retval = E_NOT_OK;
      }
      /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */

#endif /* (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

#endif /* (COM_TMS_ENABLE == STD_ON) && .... */


#if (COM_PRECONDITION_ASSERT_ENABLED != STD_ON)
      TS_PARAM_UNUSED(hlp_retval);
#endif /* (COM_PRECONDITION_ASSERT_ENABLED != STD_ON) */
   }


   DBG_COM_EB_INITTXIPDU_EXIT(retval,TxPduId);
   return retval;
}                               /* Com_EB_InitTxIPdu */

#if (COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON)

/** \brief Com_EB_TxDMQueue - "rewind" the TxDM timeout for an IPDU
 * This function starts a timeout for the Tx deadline monitoring of an IPDU
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] PduId ID of the Tx PDU to start deadline monitoring for
 * \param[in] Offset Time (in COM ticks) to pass by before sending
 * \param[in] EntryInTxDMcQueue position in of the PDU in TxDM Queue
 * \retval None
 */

TS_MOD_PRIV_DEFN FUNC(void, COM_CODE) Com_EB_TxDMQueue
(
   ComIPduRefType PduId,
   ComTxTimeoutFactorType Offset,
   ComIPduRefType EntryInTxDMcQueue
)
{
   ComTxTimeoutFactorType TimeOut;
   ComTxTimeoutFactorType globalTime;


   CONSTP2VAR(ComTxTimeoutFactorType, AUTOMATIC, COM_VAR_NOINIT) TxTimeoutQueueBase =
       COM_GET_MEMPTR(ComTxTimeoutFactorType, Com_gConfigPtr->ComTxTimeoutQueueBase);

   CONSTP2VAR(ComTxTimeoutFactorType, AUTOMATIC, COM_VAR_NOINIT) TxTimeoutQueueValPtr =
         &TxTimeoutQueueBase[EntryInTxDMcQueue];

   DBG_COM_EB_TXDMQUEUE_ENTRY(PduId,Offset,EntryInTxDMcQueue);


   Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

   globalTime = (ComTxTimeoutFactorType) Com_GlobalTime;

   /* see other queue-functions above */
   TimeOut = (ComTxTimeoutFactorType) (globalTime + Offset);
   *TxTimeoutQueueValPtr = TimeOut;

   Com_SetBitUInt8(&Com_gDataMemPtr[(Com_gConfigPtr->ComTxIPduStatusBase + PduId)],
                   COM_TXPDU_TXDMQUEUED);

   Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();

   DBG_COM_EB_TXDMQUEUE_EXIT(PduId,Offset,EntryInTxDMcQueue);
}                               /* Com_EB_TxDMQueue */

/** \brief Com_EB_TxDM_TMNone - "rewind" the TxDM timeout for an IPDU with
 * TM only one TM configured.
 * This function starts a timeout for the Tx deadline monitoring of an IPDU
 * for an I-Pdu which has TxDM configured and only one Transmission Mode.
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * - shall only be called in the current TM is TM_NONE
 * \param[in] IPduPtr pointer to the configuration of the PDU
 * \param[in] PduId ID of the Tx PDU to start deadline monitoring for
 * \retval None
 */
TS_MOD_PRIV_DEFN FUNC(void, COM_CODE) Com_EB_TxDM_TMNone
(
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
   ComIPduRefType PduId
)
{
   boolean TxDM = (COM_GET_COM_TX_IPDU_DM_AVAILABLE(IPduPtr) == COM_TX_DM_ON) ? TRUE: FALSE;

   DBG_COM_EB_TXDM_TMNONE_ENTRY(IPduPtr,PduId);

   /* rewind only if only TM None is configured (TM False is configured as TM_UNDEF) */
   if (TRUE == TxDM)
   {

#if (COM_TM_AVAILABLE == STD_ON)
      uint8 BitRes;
      uint8 TMOther;
      /* get current TM state */
      TS_GetBit( &Com_gDataMemPtr[(Com_gConfigPtr->ComTxIPduStatusBase + PduId)],
            COM_TXPDU_TMSSTATE, uint8, BitRes);

      TMOther = COM_GET_COM_TX_MODE_INV(BitRes, IPduPtr->ComTxModeModes);

      /* rewind only if only TM None is configured */
      if (COM_TX_MODE_MODE_UNDEF == TMOther)
#endif /* (COM_TM_AVAILABLE == STD_ON) */
      {
          /* Deviation MISRA-2 */
          Com_EB_TxDMQueue(PduId,
               COM_GET_TX_TIMEOUT_FACTOR(IPduPtr),
               IPduPtr->TxDMQueueRef);
      }
   }


   DBG_COM_EB_TXDM_TMNONE_EXIT(IPduPtr,PduId);
   return;
}                               /* Com_EB_TxDM_TMNone */


#endif /* (COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) */


#if (COM_CBK_TX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE)
/** \brief Com_EB_TxConfirmations - calls all Tx notifications of the signals
 * which are within a PDU
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] IPduPtr pointer to the configuration of the PDU
 * \retval None
 */

TS_MOD_PRIV_DEFN FUNC(void, COM_CODE) Com_EB_TxConfirmations
(
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
)
{
   Com_CbkTxAckIdxType i;
   P2VAR(Com_CbkTxAck_Type, AUTOMATIC, COM_APPL_CODE) fptr;
   
   DBG_COM_EB_TXCONFIRMATIONS_ENTRY(IPduPtr);
   
   /* Call Tx confirmations */

   for (i = IPduPtr->ComNotificationFirst;
        i < (IPduPtr->ComNotificationFirst + IPduPtr->ComNotificationNum); i++)
   {

      /* get the function pointer */
      /* Deviation MISRA-2 */
      /* Deviation MISRA-5 */
      fptr = Com_CbkTxAck_Array[COM_GET_CBK_TX_ACK_PTR_IDX(i)];

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
      /* CHECK: NOPARSE */
      /* Deviation MISRA-1 */
      /* Deviation MISRA-2 */
      if (fptr == NULL_PTR)
      {
          COM_PRECONDITION_ASSERT((fptr != NULL_PTR), COMServiceId_TxConfirmation);

      }
      else
      /* CHECK: PARSE */
#endif /* COM_PRECONDITION_ASSERT_ENABLED */
      {
         fptr();
      }
   }
   DBG_COM_EB_TXCONFIRMATIONS_EXIT(IPduPtr);
}                               /*Com_EB_TxConfirmations  */

#endif /* (COM_CBK_TX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) */



#if (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)

/** \brief Com_EB_ClearTxUpdateBits - clears the update bit within the I-Pdu.
 * function which clears the update bit of the signals and signal groups
 * within the specified I-Pdu
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * - must not be called from any function but Com_TxConfirmation
 * - must only be called for IPdus which have MDT configured
 * \param[in] IPduPtr reference to the I-Pdu
 * or stopped (false)
 * \retval None
 */
TS_MOD_PRIV_DEFN FUNC(void, COM_APPL_CODE) Com_EB_ClearTxUpdateBits
(
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
)
{

   ComSignalRefType i; /* iteration variable for signal list*/
#if (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
   ComSignalGroupRefType j; /* iteration variable for signal group list*/
#endif /* (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

   DBG_COM_EB_CLEARTXUPDATEBITS_ENTRY(IPduPtr);
   
   for (i = IPduPtr->ComIPduSignalRefFirst;
   i < (IPduPtr->ComIPduSignalRefNum + IPduPtr->ComIPduSignalRefFirst); i++)
   {
      /* check if the signal has an update bit and clear it */
      /* possible optimization: */
      /* Use list with signals which have an update bit */
      /* generate bit masks which which can be used to clear bit(s) */

      /* get signal */
      /* Deviation MISRA-2, MISRA-5 <+7> */
      ComSignalRefType const signalId =
         (ComSignalRefType) *
         (COM_GET_CONFIG_ELEMENT(
               ComSignalRefType, Com_gConfigPtr->ComTxIPduSignalListRef, i));

      /* Deviation MISRA-2 */
      /* Deviation MISRA-5 */
      CONSTP2CONST(ComTxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr =
         COM_GET_CONFIG_ELEMENT(ComTxSignalType, Com_gConfigPtr->ComTxSignalRef, signalId);

#if (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL)
      if (COM_GET_TX_SIGNAL_UPDATE_BIT(SignalPtr) == TRUE)
#endif /* (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL) */
      {

         TS_AtomicClearBit_8(
              &Com_gDataMemPtr[(IPduPtr->ComIPduValueRef +
                    (SignalPtr->TxBasicParam.ComUpdateBitPositionInBit / 8U))],
               (SignalPtr->TxBasicParam.ComUpdateBitPositionInBit % 8U));

      }                         /* if (COM_GET_TX_SIGNAL_UPDATE_BIT(SignalPtr) == TRUE) */

   }                            /* for (i = IPduPtr->ComIPduSignalRefFirst;
   i < (IPduPtr->ComIPduSignalRefNum + IPduPtr->ComIPduSignalRefFirst); i++) */

#if (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
   for (j = IPduPtr->ComIPduSignalGroupRefFirst;
   j < (IPduPtr->ComIPduSignalGroupRefNum + IPduPtr->ComIPduSignalGroupRefFirst); j++)
   {
      /* check if the signal group has an update bit and clear it */
      /* possible optimization: */
      /* Use list with signals which have an update bit */
      /* generate bit masks which which can be used to clear bit(s) */

      /* get signal */
      /* Deviation MISRA-2, MISRA-5 <+6> */
      ComSignalGroupRefType const signalGId =
         (ComSignalGroupRefType) *
         (COM_GET_CONFIG_ELEMENT(ComSignalGroupRefType,
            Com_gConfigPtr->ComTxIPduSignalGroupListRef, j));

      /* Deviation MISRA-2 */
      /* Deviation MISRA-5 */
      CONSTP2CONST(ComTxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr =
         COM_GET_CONFIG_ELEMENT(ComTxSignalGroupType,
            Com_gConfigPtr->ComTxSignalGroupRef, signalGId);

#if (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL)
      if (COM_GET_TX_SIGNAL_GROUP_UPDATE_BIT(SignalGPtr) == TRUE)
#endif /* (COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL) */
      {

         TS_AtomicClearBit_8(
              &Com_gDataMemPtr[(IPduPtr->ComIPduValueRef +
                    (SignalGPtr->ComUpdateBitPositionInBit / 8U))],
               (SignalGPtr->ComUpdateBitPositionInBit % 8U));

      }                         /* if (COM_GET_TX_SIGNAL_GROUP_UPDATE_BIT(SignalGPtr) == TRUE) */

   }                            /* for (j = IPduPtr->ComIPduSignalGroupRefFirst;
   j < (IPduPtr->ComIPduSignalGroupRefNum + IPduPtr->ComIPduSignalGroupRefFirst); j++) */

#endif /* (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

   DBG_COM_EB_CLEARTXUPDATEBITS_EXIT(IPduPtr);
   return;
} /* Com_EB_ClearTxUpdateBits */


#endif /* (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) */

#if (COM_MDT_QUEUE_AVAILABLE == STD_ON)

/** \brief Com_EB_MdtQueue - set a minimum delay time for a PDU.
 * function which blocks sending of a PDU for an amount of time to implement
 * the minimum delay time mechanism of the COM.
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * - must not be called from any function but Com_TxConfirmation
 * - must only be called for IPdus which have MDT configured
 * \param[in] PduId ID of the PDU to be blocked for its' minimum delay time
 * or stopped (false)
 * \retval None
 */

TS_MOD_PRIV_DEFN FUNC(void, COM_CODE)Com_EB_MdtQueue
(
   ComIPduRefType Pdu,
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
   ComTxIPduMinimumDelayTimeFactorType MDT
)
{
   /* variable to hold global time in data type of ComTxIPduMinimumDelayTimeFactorType */
   ComTxIPduMinimumDelayTimeFactorType globalTime;
   ComTxIPduMinimumDelayTimeFactorType TimeOut; /* calculated point in time for unblocking */

   CONSTP2VAR(ComTxIPduMinimumDelayTimeFactorType, AUTOMATIC, COM_VAR_NOINIT) MDTQueueBase =
       COM_GET_MEMPTR(ComTxIPduMinimumDelayTimeFactorType, Com_gConfigPtr->ComMDTQueueBase);

   CONSTP2VAR(ComTxIPduMinimumDelayTimeFactorType, AUTOMATIC, COM_VAR_NOINIT) MDTQueueValPtr =
         &MDTQueueBase[IPduPtr->MDTQueueRef];

   DBG_COM_EB_MDTQUEUE_ENTRY(Pdu,IPduPtr,MDT);

   /* Enter critical section;
    * it must be made sure that the MainFunction is not called before
    * the due time has been added to the MDT "queue", as this could
    * block the PDU from being sent for a long time */
   Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

   globalTime = (ComTxIPduMinimumDelayTimeFactorType) Com_GlobalTime;

   /* calculate new timeout */
   TimeOut = (ComTxIPduMinimumDelayTimeFactorType) globalTime + MDT;
   /* set timeout */
   *MDTQueueValPtr = TimeOut;

   Com_SetBitUInt8(&Com_gDataMemPtr[(Com_gConfigPtr->ComTxIPduStatusBase + Pdu)],
                   COM_TXPDU_MDTQUEUED);

   /* Leave critical section */
   Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();


   DBG_COM_EB_MDTQUEUE_EXIT(Pdu,IPduPtr,MDT);
   return;
}

#endif /* (COM_MDT_QUEUE_AVAILABLE == STD_ON) */

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_STOP_SEC_CODE
#include <MemMap.h>
#endif


