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
 * MISRA-4) Deviated Rule: 15.2 (required)
 * "An unconditional 'break' statement shall terminate every non-empty switch clause."
 *
 * Reason:
 * fall through allows shorter and non-duplicated code
 *
 */


/*==================[inclusions]=============================================*/

#include <Com_Trace.h>
#include <TSAutosar.h>          /* EB specific standard types */
#include <ComStack_Types.h>     /* AUTOSAR standard types */
#include <Com_Api_Static.h>     /* module public static API */
#include <Com_Priv.h>           /* module internal stuff */

#include <Com_Core_TxIPdu.h>    /* Header TxIPdu functions */

#if (COM_DEV_ERROR_DETECT == STD_ON)
#include <Det.h>                /* Det API */
#endif

#if ((COM_TM_AVAILABLE == STD_ON) || (COM_TMS_ENABLE == STD_ON))
#include <Com_Core_TM.h> /* Transmission Mode functions */
#endif /* ((COM_TM_AVAILABLE == STD_ON) || (COM_TMS_ENABLE == STD_ON)) */

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_START_SEC_CODE
#include <MemMap.h>
#endif


#if (COM_TM_AVAILABLE == STD_ON)

#if (COM_TM_SWITCH_AVAILABLE == STD_ON)

/** \brief Com_EB_CheckTMSforPdu - check if TM-switching must be done
 * Preconditions:
 * - COM must be initialized
 * \param[in] PduId - Id of the Pdu which should be checked
 * \param[in] IPduPtr - configuration of the Pdu
 * \param[out] None
 * \retval TRUE if I-Pdu shall be sent, else FALSE
 */
_COM_STATIC_ FUNC(boolean, COM_CODE)Com_EB_CheckTMSforPdu
(
   ComIPduRefType PduId,
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
);


/** \brief Com_EB_TMSwitch - switch to new TM
 * Preconditions:
 * - COM must be initialized
 * \param[in] PduId - Id of the Pdu
 * \param[in] IPduPtr - pointer of the Pdu configuration
 * \param[in] CurrentTM - new TM
 * \param[out] None
 * \retval TRUE if I-Pdu shall be sent, else FALSE
 */

_COM_STATIC_ FUNC(boolean, COM_CODE) Com_EB_TMSwitch
(
   ComIPduRefType PduId,
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
   boolean CurrentTM
);

#endif /* (COM_TM_SWITCH_AVAILABLE == STD_ON) */

#if (COM_PERIODIC_QUEUE_AVAILABLE == STD_ON)

_COM_STATIC_ FUNC(boolean, COM_CODE) Com_EB_CheckPeriodicSendforPdu
(
   ComIPduRefType PduId,
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
);

#endif /* (COM_PERIODIC_QUEUE_AVAILABLE == STD_ON) */

#if (COM_N_TIMES_QUEUE_AVAILABLE == STD_ON)

_COM_STATIC_ FUNC(boolean, COM_CODE) Com_EB_CheckNTimesSendforPdu
(
   ComIPduRefType PduId,
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
);

#endif /* (COM_N_TIMES_QUEUE_AVAILABLE == STD_ON) */


#endif /* (COM_TM_AVAILABLE == STD_ON) */


#if (COM_MDT_QUEUE_AVAILABLE == STD_ON)


/** \brief Com_EB_CheckMdtforPdu - checks MDT for the given Pdu
 * This function checks the Mdt-table and un-blocks PDUs from sending
 * if a minimum delay time timed out (clears MDTQUEUED flag).
 * NOTE: function does not trigger sending of the Pdu.
 * Preconditions:
 * - COM must be initialized
 * - MDT has to be configured for the Pdu and MDT has to run
 * \param[in] PduId - Id of the Pdu which should be checked
 * \param[in] IPduPtr - configuration of the Pdu
 * \param[out] None
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_CheckMdtforPdu
(
   ComIPduRefType PduId,
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
);

#endif /* (COM_MDT_QUEUE_AVAILABLE == STD_ON) */

#if (COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON)

_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_CheckTxDMforPdu
(
   ComIPduRefType PduId,
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
#if (COM_MDT_QUEUE_AVAILABLE == STD_ON)
#if (COM_RETRY_FAILED_TRANSMIT_REQ == STD_ON)
   ,boolean TxDM_clearRTFR
#endif /* (COM_RETRY_FAILED_TRANSMIT_REQ == STD_ON) */
#endif /* (COM_MDT_QUEUE_AVAILABLE == STD_ON) */
);

#endif /* (COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) */


#if (COM_TX_CONFIRMATIONS_DEFERED_AVAILABLE == STD_ON)

_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_HandleDeferredTxConfirm
(
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
);

#endif /* (COM_TX_CONFIRMATIONS_DEFERED_AVAILABLE == STD_ON) */

/** \brief Com_EB_Handle_Send_Pdu - handles sending of I-Pdu
 * This function checks if an I-Pdu shall be transmitted with
 * respect to MDT and the ComEnableMDTForCyclicTransmission.
 * - Clears the SENDIMMEDIATELY flag if a pending transmission
 *  request could be issued successfully.
 * Preconditions:
 * - COM must be initialized
 * - API shall only be used in context of Com_MainfunctionTx
 * \param[in] PduId - Id of the Pdu which should be checked
 * \param[in] IPduPtr - configuration of the Pdu
 * \param[in] transmit - if TRUE an (additional) transmit request due
 *            to calculations in Com_MainFunctionTx is pending,
 *            else only the SENDIMMEDIATELY flag is used for calculation.
 * \param[out] None
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_Handle_Send_Pdu
(
   ComIPduRefType PduId,
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
   P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) IPduFlagBytePtr,
   boolean transmit
);

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_STOP_SEC_CODE
#include <MemMap.h>
#endif

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_START_SEC_CODE
#include <MemMap.h>
#endif



#if (COM_TM_AVAILABLE == STD_ON)

#if (COM_TM_SWITCH_AVAILABLE == STD_ON)

/** \brief Com_EB_CheckTMSforPdu - check if TM-switching must be done
 * Preconditions:
 * - COM must be initialized
 * \param[in] PduId - Id of the Pdu which should be checked
 * \param[in] IPduPtr - configuration of the Pdu
 * \param[out] None
 * \retval TRUE if I-Pdu shall be sent, else FALSE
 */

_COM_STATIC_ FUNC(boolean, COM_CODE)Com_EB_CheckTMSforPdu
(
   ComIPduRefType PduId,
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
)
{

   boolean TMChanged;
   boolean newTM;
   boolean transmit = FALSE;

   CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) IPduFlagBytePtr =
         &Com_gDataMemPtr[(Com_gConfigPtr->ComTxIPduStatusBase + PduId)];

   DBG_COM_EB_CHECKTMSFORPDU_ENTRY(PduId,IPduPtr);

   /* get the TMChanged flag of Pdu */
   TS_GetBit(IPduFlagBytePtr, COM_TXPDU_TMSCHANGED, uint8, TMChanged);

   if (TMChanged == TRUE)
   {
      TS_AtomicClearBit_8(IPduFlagBytePtr, COM_TXPDU_TMSCHANGED);

      TS_GetBit(IPduFlagBytePtr, COM_TXPDU_TMSSTATE, uint8, newTM);

      /* if TM has changed, switch to the new mode */
      transmit = Com_EB_TMSwitch(PduId, IPduPtr, newTM);

   }                         /* if (TMChanged) */


   DBG_COM_EB_CHECKTMSFORPDU_EXIT(transmit,PduId,IPduPtr);
   return transmit;
}                               /* Com_EB_CheckTMSforPdu */


/** \brief Com_EB_TMSwitch - switch to new TM
 * Preconditions:
 * - COM must be initialized
 * \param[in] PduId - Id of the Pdu
 * \param[in] IPduPtr - pointer of the Pdu configuration
 * \param[in] CurrentTM - new TM
 * \param[out] None
 * \retval TRUE if I-Pdu shall be sent, else FALSE
 */


_COM_STATIC_ FUNC(boolean, COM_CODE) Com_EB_TMSwitch
(
   ComIPduRefType PduId,
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
   boolean CurrentTM
)
{
   boolean transmit = FALSE;
   uint8 mode;                  /* current TX mode */
#if (COM_PERIODIC_QUEUE_AVAILABLE == STD_ON)
   Com_PeriodicSendNextDueTimeType TimeToSendPeriodic = 0;      /* for cyclic sends */
#endif /* (COM_PERIODIC_QUEUE_AVAILABLE == STD_ON) */

   CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) IPduFlagBytePtr =
         &Com_gDataMemPtr[(Com_gConfigPtr->ComTxIPduStatusBase + PduId)];

   DBG_COM_EB_TMSWITCH_ENTRY(PduId,IPduPtr,CurrentTM);


   /* get the new TM */
   mode = COM_GET_COM_TX_MODE(CurrentTM, IPduPtr->ComTxModeModes);

   /* Prepare for setting up new TM and getting configuration for periodic
    * sending */
   switch (mode)
   {
      /* Deviation MISRA-4 */
      case COM_TX_MODE_MODE_NONE:
#if (COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON)
          /* disable TxDM for TM None of two TMs are configured */
          TS_AtomicClearBit_8(IPduFlagBytePtr, COM_TXPDU_TXDMQUEUED);
#endif /* (COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) */
          /* Cancel any periodic/n-times sending */
          /* fall through */
#if (COM_TX_MODE_DIRECT_ENABLE == STD_ON)
      case COM_TX_MODE_MODE_DIRECT:
#endif /* (COM_TX_MODE_DIRECT_ENABLE == STD_ON) */

#if (COM_PERIODIC_QUEUE_AVAILABLE == STD_ON)
         TS_AtomicClearBit_8(IPduFlagBytePtr, COM_TXPDU_PERIODICSENDQUEUED);
#endif /* (COM_PERIODIC_QUEUE_AVAILABLE == STD_ON) */

#if (COM_N_TIMES_QUEUE_AVAILABLE == STD_ON)
         TS_AtomicClearBit_8(IPduFlagBytePtr, COM_TXPDU_NTIMESSENDQUEUED);
#endif /* (COM_N_TIMES_QUEUE_AVAILABLE == STD_ON) */

         break;
#if (COM_TX_MODE_N_TIMES_ENABLE == STD_ON)
      case COM_TX_MODE_MODE_N_TIMES:
         /* NOTE: N-times queuing has to be done in context of SendSignal,
          * otherwise a TxConfirmation may be lost */
         TS_AtomicClearBit_8(IPduFlagBytePtr, COM_TXPDU_PERIODICSENDQUEUED);
         break;
#endif /* (COM_TX_MODE_N_TIMES_ENABLE == STD_ON) */

#if (COM_TX_MODE_PERIODIC_ENABLE == STD_ON)
      case COM_TX_MODE_MODE_PERIODIC:
#endif /* (COM_TX_MODE_PERIODIC_ENABLE == STD_ON) */
         /* fall through to cancellation of NTimes and get period */
         /* Deviation MISRA-4 */
#if (COM_TX_MODE_MIXED_DIRECT_ENABLE == STD_ON)
      case COM_TX_MODE_MODE_MIXED_DIRECT:
#endif /* COM_TX_MODE_MIXED_DIRECT_ENABLE */

#if ((COM_TX_MODE_MIXED_DIRECT_ENABLE == STD_ON) || (COM_TX_MODE_PERIODIC_ENABLE == STD_ON))
      {
         /* get configuration for new TM */
         ComTxModeIdxType TMRef;     /* reference to the TM configuration */
         P2CONST(ComTxModePeriodicType, AUTOMATIC, COM_APPL_CONST) TMPeriodicPtr;
         TMRef = COM_GET_COM_TX_MODE_REF(CurrentTM, IPduPtr);
         /* Deviation MISRA-2 */
         /* Deviation MISRA-3 */
         TMPeriodicPtr = COM_GET_CONFIG_ELEMENT(ComTxModePeriodicType,
                                                Com_gConfigPtr->ComTxModePeriodicRef, TMRef);
         TimeToSendPeriodic = TMPeriodicPtr->ComTxModeTimePeriodFactor;

         /* Cancel N-Times */
         TS_AtomicClearBit_8(IPduFlagBytePtr,  COM_TXPDU_NTIMESSENDQUEUED);
      }
      break;
#endif /* ((COM_TX_MODE_MIXED_DIRECT_ENABLE == STD_ON) || (COM_TX_MODE_PERIODIC_ENABLE == STD_ON)) */

#if (COM_TX_MODE_MIXED_N_TIMES_ENABLE == STD_ON)
      case COM_TX_MODE_MODE_MIXED_N_TIMES:
      {
         /* NOTE: N-times queuing has to be done in context of SendSignal,
          * otherwise a TxConfirmation may be lost */
         ComTxModeIdxType TMRef;     /* reference to the TM configuration */
         P2CONST(ComTxModeMixedNTimesType, AUTOMATIC, COM_APPL_CONST) TMMixedNTimesPtr;
         TMRef = COM_GET_COM_TX_MODE_REF(CurrentTM, IPduPtr);
         /* Deviation MISRA-2 */
         /* Deviation MISRA-3 */
         TMMixedNTimesPtr = COM_GET_CONFIG_ELEMENT(ComTxModeMixedNTimesType,
                                                   Com_gConfigPtr->ComTxModeMixedNTimesRef,
                                                   TMRef);
         TimeToSendPeriodic = TMMixedNTimesPtr->ComTxModeTimePeriodFactor;
      }

         break;
#endif /* (COM_TX_MODE_MIXED_N_TIMES_ENABLE == STD_ON) */
         /* CHECK: NOPARSE */
      default:
          COM_UNREACHABLE_CODE_ASSERT(COMServiceId_MainFunctionTx);
          break;
         /* CHECK: PARSE */
   }                            /* end switch(mode) */


   /* If TimeToSendPeriodic is legally configured, it can never be 0,
    * so if it is not 0, periodic sending is part of the new TM;
    * enable periodic sending, then */
#if (COM_PERIODIC_QUEUE_AVAILABLE == STD_ON)
   if (TimeToSendPeriodic != 0)
   {
      /* Schedule periodic sending */

      Com_EB_PeriodicSendQueue(TimeToSendPeriodic, IPduPtr->PeriodicQueueRef);

      /* Mark the PDU as send queued */
      TS_AtomicSetBit_8(IPduFlagBytePtr, COM_TXPDU_PERIODICSENDQUEUED);

      /* Finally, if TM now is a mode with cyclic part, and the IPdu
       * was not sent because of an eventual triggered property, send
       * the IPdu out once at once. */

#if (COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON)

      /* Check if PDU has TxDM */
      if (COM_GET_COM_TX_IPDU_DM_AVAILABLE(IPduPtr) == COM_TX_DM_ON)
      {
         uint8 BitRes;
         TS_GetBit(IPduFlagBytePtr, COM_TXPDU_TXDMQUEUED, uint8, BitRes);

         /* If it is not yet running, start Tx DM */
         if (BitRes == FALSE)
         {
            /* Deviation MISRA-2 */
            /* Deviation MISRA-3 */
            Com_EB_TxDMQueue(PduId, COM_GET_TX_TIMEOUT_FACTOR(IPduPtr), IPduPtr->TxDMQueueRef);
         }
      }
#endif /* (COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) */

      /* Set flag to send Pdu */
      transmit = TRUE;

   }                            /* if (TimeToSendPeriodic != 0) */
#endif /* (COM_PERIODIC_QUEUE_AVAILABLE == STD_ON) */


   DBG_COM_EB_TMSWITCH_EXIT(transmit,PduId,IPduPtr,CurrentTM);
   return transmit;
}                               /* Com_EB_TMSwitch */

#endif /* (COM_TM_SWITCH_AVAILABLE == STD_ON) */

#if (COM_PERIODIC_QUEUE_AVAILABLE == STD_ON)

/** \brief Com_EB_CheckPeriodicSendforPdu
 * This function checks if a scheduled sending must be executed.
 * Preconditions:
 * - COM must be initialized
 * - Pdu has to be periodic queued
 * \param[in] PduId - Id of the Pdu which should be checked
 * \param[in] IPduPtr - configuration of the Pdu
 * \param[out] None
 * \retval TRUE if I-Pdu shall be sent, else FALSE
 */

_COM_STATIC_ FUNC(boolean, COM_CODE) Com_EB_CheckPeriodicSendforPdu
(
   ComIPduRefType PduId,
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
)
{
   /* variable to hold global time in data type of TimePeriodFactor */
   Com_PeriodicSendNextDueTimeType globalTime;

   Com_PeriodicSendNextDueTimeType CompTime;    /* temporary variable for expiration time
                                                   calculation */
   Com_PeriodicSendNextDueTimeType Period = 0;      /* period for periodic PDU sending */

   uint8 BitRes;

   uint8 AktTM;     /* current TM mode */

   ComTxModeIdxType TMRef;  /* reference to the TM configuration */

   boolean transmit = FALSE;

#if (COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON)
   /* if QueuedTxDM == 0 the TxDM has to be started
    * if QueuedTxDM == 1 the TxDM is started or not configured (nothing to do) */
   uint8 QueuedTxDM = 1U;
#endif /* (COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) */

   CONSTP2VAR(Com_PeriodicSendNextDueTimeType, AUTOMATIC, COM_VAR_NOINIT) PeriodicQueueBase =
         COM_GET_MEMPTR(Com_PeriodicSendNextDueTimeType, Com_gConfigPtr->ComPeriodicQueueBase);

   CONSTP2VAR(Com_PeriodicSendNextDueTimeType, AUTOMATIC, COM_VAR_NOINIT) PeriodicQueueValPtr =
         &PeriodicQueueBase[IPduPtr->PeriodicQueueRef];

   CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) IPduFlagBytePtr =
         &Com_gDataMemPtr[(Com_gConfigPtr->ComTxIPduStatusBase + PduId)];

   DBG_COM_EB_CHECKPERIODICSENDFORPDU_ENTRY(PduId,IPduPtr);

   /* Enter critical section */
   Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

   globalTime = (Com_PeriodicSendNextDueTimeType) Com_GlobalTime;

   CompTime = *PeriodicQueueValPtr;

   if (globalTime == CompTime)
   {

#if (COM_UNREACHABLE_CODE_ASSERT_ENABLED == STD_ON)
      boolean proceedProcessing = TRUE;
#endif /* (COM_UNREACHABLE_CODE_ASSERT_ENABLED == STD_ON) */

      /* Have a look if the reason for sending is a periodic event */
      TS_GetBit(IPduFlagBytePtr, COM_TXPDU_TMSSTATE, uint8, BitRes);

      /* get current TM */
      AktTM = COM_GET_COM_TX_MODE(BitRes, IPduPtr->ComTxModeModes);
      TMRef = COM_GET_COM_TX_MODE_REF(BitRes, IPduPtr);

      switch (AktTM)
      {
#if (COM_TX_MODE_MIXED_N_TIMES_ENABLE == STD_ON)
      case COM_TX_MODE_MODE_MIXED_N_TIMES:
      {
         P2CONST(ComTxModeMixedNTimesType, AUTOMATIC, COM_APPL_CONST) TMMixedNTimesPtr;
         /* Deviation MISRA-2 */
         /* Deviation MISRA-3 */
         TMMixedNTimesPtr = COM_GET_CONFIG_ELEMENT(ComTxModeMixedNTimesType,
               Com_gConfigPtr->
               ComTxModeMixedNTimesRef, TMRef);
         Period = TMMixedNTimesPtr->ComTxModeTimePeriodFactor;
         break;
      }
#endif /* (COM_TX_MODE_MIXED_N_TIMES_ENABLE == STD_ON) */

#if ((COM_TX_MODE_MIXED_DIRECT_ENABLE == STD_ON) || (COM_TX_MODE_PERIODIC_ENABLE == STD_ON))
#if (COM_TX_MODE_MIXED_DIRECT_ENABLE == STD_ON)
      case COM_TX_MODE_MODE_MIXED_DIRECT:
         /* fall trough */
         /* Deviation MISRA-4 */
#endif /* (COM_TX_MODE_MIXED_DIRECT_ENABLE == STD_ON) */

#if (COM_TX_MODE_PERIODIC_ENABLE == STD_ON)
      case COM_TX_MODE_MODE_PERIODIC:
#endif /* (COM_TX_MODE_PERIODIC_ENABLE == STD_ON) */
      {
         P2CONST(ComTxModePeriodicType, AUTOMATIC, COM_APPL_CONST) TMPeriodicPtr;

         /* Deviation MISRA-2 */
         /* Deviation MISRA-3 */
         TMPeriodicPtr = COM_GET_CONFIG_ELEMENT(ComTxModePeriodicType,
               Com_gConfigPtr->ComTxModePeriodicRef,
               TMRef);
         Period = TMPeriodicPtr->ComTxModeTimePeriodFactor;
         break;
      }                /* COM_TX_MODE_MODE_MIXED_DIRECT or COM_TX_MODE_MODE_PERIODIC */
#endif /* ((COM_TX_MODE_MIXED_DIRECT_ENABLE == STD_ON) || (COM_TX_MODE_PERIODIC_ENABLE == STD_ON)) */

      /* CHECK: NOPARSE */
      default:
      {
#if (COM_UNREACHABLE_CODE_ASSERT_ENABLED == STD_ON)
         /* if the mode is neither periodic, mixed direct or
          * mixed N-times an error occurred */
         COM_UNREACHABLE_CODE_ASSERT(COMServiceId_MainFunctionTx);
         proceedProcessing = FALSE;
#endif /* (COM_UNREACHABLE_CODE_ASSERT_ENABLED == STD_ON) */
         break;
      }                         /* default */
      /* CHECK: PARSE */
      }                         /* switch (AktTM) */

#if (COM_UNREACHABLE_CODE_ASSERT_ENABLED == STD_ON)
      /* CHECK: NOPARSE */
      if (TRUE == proceedProcessing)
         /* CHECK: PARSE */
#endif /* (COM_UNREACHABLE_CODE_ASSERT_ENABLED == STD_ON) */
      {


#if (COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON)
         /* Check if PDU has TxDM */
         if (COM_GET_COM_TX_IPDU_DM_AVAILABLE(IPduPtr) == COM_TX_DM_ON)
         {
            TS_GetBit(IPduFlagBytePtr, COM_TXPDU_TXDMQUEUED, uint8, QueuedTxDM);

         }

#endif /* (COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) */

         transmit = TRUE;

      }                         /* if (TRUE == proceedProcessing) */

   }                            /* if (globalTime == CompTime) */

   /* Leave critical section */
   Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();

   if (TRUE == transmit)
   {
      /* Schedule next sending */
      Com_EB_PeriodicSendQueue(Period, IPduPtr->PeriodicQueueRef);
   }


#if (COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON)
   /* Check if PDU has TxDM */

   /* If it is not yet running, start Tx DM */
   if (QueuedTxDM == 0U)
   {
      /* Deviation MISRA-2 */
      /* Deviation MISRA-3 */
      Com_EB_TxDMQueue(PduId, COM_GET_TX_TIMEOUT_FACTOR(IPduPtr), IPduPtr->TxDMQueueRef);
   }
#endif /* (COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) */


   DBG_COM_EB_CHECKPERIODICSENDFORPDU_EXIT(transmit,PduId,IPduPtr);
   return transmit;
}                               /* Com_EB_CheckPeriodicSendTable */

#endif /* (COM_PERIODIC_QUEUE_AVAILABLE == STD_ON) */

#if (COM_N_TIMES_QUEUE_AVAILABLE == STD_ON)


/** \brief Com_EB_CheckNTimesSendforPdu
 * This function checks if a scheduled sending must be executed.
 * Preconditions:
 * - COM must be initialized
 * - Pdu has to be N-Times send queued
 * \param[in] PduId - Id of the Pdu which should be checked
 * \param[in] IPduPtr - configuration of the Pdu
 * \param[out] None
 * \retval TRUE if I-Pdu shall be sent, else FALSE
 */

_COM_STATIC_ FUNC(boolean, COM_CODE) Com_EB_CheckNTimesSendforPdu
(
   ComIPduRefType PduId,
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
)
{
   /* variable to hold global time in data type of ComTxModeRepetitionPeriodFactorType */
   ComTxModeRepetitionPeriodFactorType globalTime;

   ComTxModeRepetitionPeriodFactorType CompTime;        /* temporary variable for expiration time
                                                           calculation */

   ComTxModeRepetitionPeriodFactorType NPeriod = 0U;    /* period of N-Times PDU sending */
   uint8 N = 0U;                     /* number of repetitions left */

   uint8 BitRes;
   uint8 AktTM;     /* current TM mode */
   ComTxModeIdxType TMRef;  /* reference to the TM configuration */

   boolean transmit = FALSE;

   CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) NTimesQueueBaseRemaining =
         (P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT))
         & Com_gDataMemPtr[Com_gConfigPtr->ComNTimesQueueBaseRemaining];

   /* address of the storage of N */
   CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) NTimesQueueValRemainingPtr =
         &NTimesQueueBaseRemaining[IPduPtr->NTimesQueueRef];

   CONSTP2VAR(ComTxModeRepetitionPeriodFactorType, AUTOMATIC, COM_VAR_NOINIT)
   NTimesQueueBaseNextTimeBase = COM_GET_MEMPTR(ComTxModeRepetitionPeriodFactorType,
         Com_gConfigPtr->ComNTimesQueueBaseNextTime);

   /* address of storage of Next Time to send */
   CONSTP2VAR(ComTxModeRepetitionPeriodFactorType, AUTOMATIC, COM_VAR_NOINIT)
   NTimesQueueValNextTimePtr =
         &NTimesQueueBaseNextTimeBase[IPduPtr->NTimesQueueRef];

   DBG_COM_EB_CHECKNTIMESSENDFORPDU_ENTRY(PduId,IPduPtr);

   /* Enter critical section */
   Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

   globalTime = (ComTxModeRepetitionPeriodFactorType) Com_GlobalTime;

   CompTime = *NTimesQueueValNextTimePtr;

   if (globalTime == CompTime)
   {

#if (COM_UNREACHABLE_CODE_ASSERT_ENABLED == STD_ON)
      boolean proceedProcessing = TRUE;
#endif /* (COM_UNREACHABLE_CODE_ASSERT_ENABLED == STD_ON) */

      /* Have a look if the reason for sending is a periodic event */
      TS_GetBit(&Com_gDataMemPtr[(Com_gConfigPtr->ComTxIPduStatusBase + PduId)],
         COM_TXPDU_TMSSTATE, uint8, BitRes);

      /* get current TM */
      AktTM = COM_GET_COM_TX_MODE(BitRes, IPduPtr->ComTxModeModes);
      TMRef = COM_GET_COM_TX_MODE_REF(BitRes, IPduPtr);
      switch (AktTM)
      {
#if (COM_TX_MODE_N_TIMES_ENABLE == STD_ON)
      case COM_TX_MODE_MODE_N_TIMES:
      {
         P2CONST(ComTxModeNTimesType, AUTOMATIC, COM_APPL_CONST) TMNTimesPtr;
         /* Deviation MISRA-2 */
         /* Deviation MISRA-3 */
         TMNTimesPtr = COM_GET_CONFIG_ELEMENT(ComTxModeNTimesType,
               Com_gConfigPtr->ComTxModeNTimesRef,
               TMRef);
         NPeriod = TMNTimesPtr->ComTxModeRepetitionPeriodFactor;
         break;
      }          /* case COM_TX_MODE_MODE_N_TIMES */
#endif /* (COM_TX_MODE_N_TIMES_ENABLE == STD_ON) */
#if (COM_TX_MODE_MIXED_N_TIMES_ENABLE == STD_ON)
      case COM_TX_MODE_MODE_MIXED_N_TIMES:
      {
         P2CONST(ComTxModeMixedNTimesType, AUTOMATIC,
               COM_APPL_CONST) TMMixedNTimesPtr;

         /* Deviation MISRA-2 */
         /* Deviation MISRA-3 */
         TMMixedNTimesPtr = COM_GET_CONFIG_ELEMENT(ComTxModeMixedNTimesType,
               Com_gConfigPtr->
               ComTxModeMixedNTimesRef, TMRef);
         NPeriod = TMMixedNTimesPtr->ComTxModeRepetitionPeriodFactor;
         break;
      }          /* case COM_TX_MODE_MODE_MIXED_N_TIMES */
#endif /* (COM_TX_MODE_MIXED_N_TIMES_ENABLE == STD_ON) */
      /* CHECK: NOPARSE */
      default:
      {
#if (COM_UNREACHABLE_CODE_ASSERT_ENABLED == STD_ON)
         COM_UNREACHABLE_CODE_ASSERT(COMServiceId_MainFunctionTx);
         proceedProcessing = FALSE;
#endif /* (COM_UNREACHABLE_CODE_ASSERT_ENABLED == STD_ON) */
         break;
      }          /* default */
      /* CHECK: PARSE */
      }                /* switch (AktTM) */

#if (COM_UNREACHABLE_CODE_ASSERT_ENABLED == STD_ON)
      /* CHECK: NOPARSE */
      if (TRUE == proceedProcessing)
         /* CHECK: PARSE */
#endif /* (COM_UNREACHABLE_CODE_ASSERT_ENABLED == STD_ON) */
      {
         N = *NTimesQueueValRemainingPtr;
      }
   }                   /* if (globalTime == CompTime) */

   /* Leave critical section */
   Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();

   if (N > 0)
   {
      /* DO NOT decrease N; N is decreased in Com_TxConfirmation;
       * As long as N is not zero, send and schedule next sending */

      transmit = TRUE;

      /* Schedule next sending */
      Com_EB_NTimesSendQueue(PduId,
         NPeriod,
         IPduPtr->NTimesQueueRef);

   }                /* end N > 0 */

   DBG_COM_EB_CHECKNTIMESSENDFORPDU_EXIT(transmit,PduId,IPduPtr);
   return transmit;
}                               /* Com_EB_CheckNTimesSendforPdu */



#endif /* (COM_N_TIMES_QUEUE_AVAILABLE == STD_ON) */

#endif /* (COM_TM_AVAILABLE == STD_ON) */


#if (COM_MDT_QUEUE_AVAILABLE == STD_ON)

/** \brief Com_EB_CheckMdtforPdu - checks MDT for the given Pdu
 * This function checks the Mdt-table and un-blocks PDUs from sending
 * if a minimum delay time timed out (clears MDTQUEUED flag).
 * NOTE: function does not trigger sending of the Pdu.
 * Preconditions:
 * - COM must be initialized
 * - MDT has to be configured for the Pdu and MDT has to run
 * \param[in] PduId - Id of the Pdu which should be checked
 * \param[in] IPduPtr - configuration of the Pdu
 * \param[out] None
 * \retval None
 */

_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_CheckMdtforPdu
(
   ComIPduRefType PduId,
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
)
{

   /* variable to hold global time in data type of ComTxIPduMinimumDelayTimeFactorType */
   ComTxIPduMinimumDelayTimeFactorType globalTime;

   /* temporary variable for expiration time calculation */
   ComTxIPduMinimumDelayTimeFactorType CompTime;

   CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) PduFlagPtr =
         &Com_gDataMemPtr[(Com_gConfigPtr->ComTxIPduStatusBase + PduId)];

   CONSTP2VAR(ComTxIPduMinimumDelayTimeFactorType, AUTOMATIC, COM_VAR_NOINIT) MDTQueueBase =
       COM_GET_MEMPTR(ComTxIPduMinimumDelayTimeFactorType, Com_gConfigPtr->ComMDTQueueBase);

   CONSTP2VAR(ComTxIPduMinimumDelayTimeFactorType, AUTOMATIC, COM_VAR_NOINIT) MDTQueueValPtr =
         &MDTQueueBase[IPduPtr->MDTQueueRef];

   DBG_COM_EB_CHECKMDTFORPDU_ENTRY(PduId,IPduPtr);


   /* Enter critical section */
   Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

   globalTime = (ComTxIPduMinimumDelayTimeFactorType) Com_GlobalTime;
   /* get the time out */
   CompTime = *MDTQueueValPtr;

   /* Check if this IPdu has timed out */
   if (globalTime == CompTime)
   {
      /* This PDU's MDT timed out; clear queued flag */
      Com_ClearBitUInt8(PduFlagPtr, COM_TXPDU_MDTQUEUED);
   }

   /* Leave critical section */
   Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();


   DBG_COM_EB_CHECKMDTFORPDU_EXIT(PduId,IPduPtr);
}                               /* Com_EB_CheckMdtforPdu */

#endif /* (COM_MDT_QUEUE_AVAILABLE == STD_ON) */


#if (COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON)

/** \brief Com_EB_CheckTxDMforPdu - checks if TxDM expired
 * Preconditions:
 * - COM must be initialized
 * - TxDM has to be running
 * \param[in] PduId - Id of the Pdu which should be checked
 * \param[in] IPduPtr - configuration of the Pdu#
 * \param[in] TxDM_clearRTFR - indicates if pending RTFR shall be cleared in case TxDM expires
 * \param[out] None
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_CheckTxDMforPdu
(
   ComIPduRefType PduId,
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
#if (COM_MDT_QUEUE_AVAILABLE == STD_ON)
#if (COM_RETRY_FAILED_TRANSMIT_REQ == STD_ON)
   ,boolean TxDM_clearRTFR
#endif /* (COM_RETRY_FAILED_TRANSMIT_REQ == STD_ON) */
#endif /* (COM_MDT_QUEUE_AVAILABLE == STD_ON) */
)
{
   /* variable to hold global time in data type of ComTxTimeoutFactorType */
   ComTxTimeoutFactorType globalTime;

   ComTxTimeoutFactorType CompTime;

   boolean timeout = FALSE;

   CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) IPduFlagBytePtr =
         &Com_gDataMemPtr[(Com_gConfigPtr->ComTxIPduStatusBase + PduId)];

   CONSTP2VAR(ComTxTimeoutFactorType, AUTOMATIC, COM_VAR_NOINIT) TxTimeoutQueueBase =
       COM_GET_MEMPTR(ComTxTimeoutFactorType, Com_gConfigPtr->ComTxTimeoutQueueBase);

   CONSTP2VAR(ComTxTimeoutFactorType, AUTOMATIC, COM_VAR_NOINIT) TxTimeoutQueueValPtr =
         &TxTimeoutQueueBase[IPduPtr->TxDMQueueRef];

   DBG_COM_EB_CHECKTXDMFORPDU_ENTRY(PduId,IPduPtr);


   /* Enter critical section */
   Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

   globalTime = (ComTxTimeoutFactorType) Com_GlobalTime;

   CompTime = *TxTimeoutQueueValPtr;

   if (globalTime == CompTime)
   {

      timeout = TRUE;

      /* Entry times out right now */
      Com_ClearBitUInt8(IPduFlagBytePtr, COM_TXPDU_TXDMQUEUED);

#if (COM_N_TIMES_QUEUE_AVAILABLE == STD_ON)

      /* Un-Schedule NTimes-Sending */
      Com_ClearBitUInt8(IPduFlagBytePtr, COM_TXPDU_NTIMESSENDQUEUED);

#endif /* (COM_N_TIMES_QUEUE_AVAILABLE == STD_ON) */

#if (COM_RETRY_FAILED_TRANSMIT_REQ == STD_ON)
      {
#if (COM_MDT_QUEUE_AVAILABLE == STD_ON)

         /* clear pending ComRetryFailedTransmitRequests (RTF Requests) */

         if (TxDM_clearRTFR)
#endif /* (COM_MDT_QUEUE_AVAILABLE == STD_ON) */
         {
            /* cancel pending retry transmission requests */
            Com_ClearBitUInt8(IPduFlagBytePtr, COM_TXPDU_SENDIMMEDIATELY);
         }
      }

#endif /* (COM_RETRY_FAILED_TRANSMIT_REQ == STD_ON) */

#if (COM_MDT_QUEUE_AVAILABLE == STD_ON)

      /* stop MDT monitoring */
      Com_ClearBitUInt8(IPduFlagBytePtr, COM_TXPDU_MDTQUEUED);

#endif /* (COM_MDT_QUEUE_AVAILABLE == STD_ON) */

   }                   /* if (globalTime == CompTime) */


   /* LEAVE CRITICAL SECTION */
   Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();


   if (timeout)
   {

      Com_CbkTxTOutIdxType j;  /* iterator variable */
      /* Notify configured signals */
      for (j = IPduPtr->ComTxTimeoutNotificationFirst;
            j < (IPduPtr->ComTxTimeoutNotificationFirst
                  + IPduPtr->ComTxTimeoutNotificationNum); j++)
      {
         /* call callback */
         /* Deviation MISRA-2 */
         /* Deviation MISRA-3 */
         Com_CbkTxTOut_Array[COM_GET_CBK_TX_T_OUT_IDX(j)] ();
      }

      {
#if (COM_TM_AVAILABLE == STD_ON)
         uint8 CurrentTMS;
         uint8 AktTM;

         /* get TM state of Pdu */
         TS_GetBit(IPduFlagBytePtr, COM_TXPDU_TMSSTATE, uint8, CurrentTMS);

         /* Get transmission mode */
         AktTM = COM_GET_COM_TX_MODE(CurrentTMS, IPduPtr->ComTxModeModes);

         if (COM_TX_MODE_MODE_NONE == AktTM)
#endif /* (COM_TM_AVAILABLE == STD_ON) */
         {
            /* rewind TxDM if only TM None is configured */
            Com_EB_TxDM_TMNone(IPduPtr, PduId);
         }
      }
   }                            /* if (timeout) */

   DBG_COM_EB_CHECKTXDMFORPDU_EXIT(PduId,IPduPtr);
}                               /* Com_EB_CheckTxDMTable */
#endif /* (COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) */


#if (COM_TX_CONFIRMATIONS_DEFERED_AVAILABLE == STD_ON)

_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_HandleDeferredTxConfirm
(
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
)
{

   uint8 BitRes;

   DBG_COM_EB_HANDLEDEFERREDTXCONFIRM_ENTRY(IPduPtr);

#if ((COM_TX_CONFIRMATIONS_IMMEDIATE_AVAILABLE == STD_ON) && (COM_TX_CONFIRMATIONS_DEFERED_AVAILABLE == STD_ON))
   if (COM_GET_COM_TX_IPDU_SIGNAL_PROCESSING(IPduPtr) == COM_DEFERED)
#endif /* ((COM_TX_CONFIRMATIONS_IMMEDIATE_AVAILABLE == STD_ON) && (COM_TX_CONFIRMATIONS_DEFERED_AVAILABLE == STD_ON)) */
   {
      TS_GetBit(&Com_gDataMemPtr[(Com_gConfigPtr->ComCbkTxAckDeferredStatusBase +
              (IPduPtr->ComNotificationDeferredQueueRef / 8))],
              (IPduPtr->ComNotificationDeferredQueueRef % 8), uint8, BitRes);
      if (BitRes == TRUE)
      {
         /* Clear the flag */
         TS_AtomicClearBit_8(&Com_gDataMemPtr[(Com_gConfigPtr->ComCbkTxAckDeferredStatusBase +
              (IPduPtr->ComNotificationDeferredQueueRef / 8))],
              (IPduPtr->ComNotificationDeferredQueueRef % 8));

         /* handle confirmations */
         Com_EB_TxConfirmations(IPduPtr);
      }
   }

   DBG_COM_EB_HANDLEDEFERREDTXCONFIRM_EXIT(IPduPtr);
}

#endif /* (COM_TX_CONFIRMATIONS_DEFERED_AVAILABLE == STD_ON) */


/** \brief Com_EB_Handle_Send_Pdu - handles sending of I-Pdu
 * This function checks if an I-Pdu shall be transmitted with
 * respect to MDT and the ComEnableMDTForCyclicTransmission.
 * - Clears the SENDIMMEDIATELY flag if a pending transmission
 *  request could be issued successfully.
 * Preconditions:
 * - COM must be initialized
 * - API shall only be used in context of Com_MainfunctionTx
 * \param[in] PduId - Id of the Pdu which should be checked
 * \param[in] IPduPtr - configuration of the Pdu
 * \param[in] transmit - if TRUE an (additional) transmit request due
 *            to calculations in Com_MainFunctionTx is pending,
 *            else only the SENDIMMEDIATELY flag is used for calculation.
 * \param[out] None
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_Handle_Send_Pdu
(
   ComIPduRefType PduId,
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
   P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) IPduFlagBytePtr,
   boolean transmit
)
{
   uint8 BitRes;
   boolean to_transmit = transmit;

   DBG_COM_EB_HANDLE_SEND_PDU_ENTRY(PduId,IPduPtr,IPduFlagBytePtr,transmit);

#if (COM_ENABLE_MDT_FOR_CYCLIC_TX == STD_ON)
   /* Postpone Tx request from MainFunction only if configured
    * (ComEnableMDTForCyclicTransmission == true) */
#if (COM_MDT_QUEUE_AVAILABLE == STD_ON)
   TS_GetBit(IPduFlagBytePtr, COM_TXPDU_MDTQUEUED, uint8, BitRes);
   if (BitRes == TRUE)
   {
      if (TRUE == to_transmit)
      {
         TS_AtomicSetBit_8(IPduFlagBytePtr, COM_TXPDU_SENDIMMEDIATELY);
      }
   }
   else
#endif /* (COM_MDT_QUEUE_AVAILABLE == STD_ON) */
#endif /* (COM_ENABLE_MDT_FOR_CYCLIC_TX == STD_ON) */
   {

      /* check if there are pending event based Tx- Requests
       *  ( = Tx Request not from MainFunction) */
      TS_GetBit(IPduFlagBytePtr, COM_TXPDU_SENDIMMEDIATELY, uint8, BitRes);
      if (TRUE == BitRes)
      {
#if (COM_ENABLE_MDT_FOR_CYCLIC_TX == STD_OFF)
         /* Postpone pending event based Tx Request
          * further if
          * (ComEnableMDTForCyclicTransmission == false) */
         TS_GetBit(IPduFlagBytePtr, COM_TXPDU_MDTQUEUED, uint8, BitRes);
         if (BitRes == FALSE)
#endif /* (COM_ENABLE_MDT_FOR_CYCLIC_TX == STD_OFF) */
         {
            to_transmit = TRUE;
         }
      }

      if(TRUE == to_transmit)
      {
         /* Clear send-immediately flag */
         TS_AtomicClearBit_8(IPduFlagBytePtr, COM_TXPDU_SENDIMMEDIATELY);

         /* send the Pdu out */
         Com_EB_Send_Pdu(PduId, IPduPtr);

      }
   }

   DBG_COM_EB_HANDLE_SEND_PDU_EXIT(PduId,IPduPtr,IPduFlagBytePtr,transmit);
}                               /* Com_EB_Handle_Send_Pdu */


/** \brief Com_MainFunctionTx - handle cyclic sending-related tasks
 ** This function handles cyclic sending-related tasks such as minimum delay
 ** time and cyclic sending.
 ** Preconditions:
 ** - COM must be initialized
 ** \param[in] None
 ** \retval None
 */

FUNC(void, COM_CODE) Com_MainFunctionTx
(
   void
)
{

   DBG_COM_MAINFUNCTIONTX_ENTRY();
   if (Com_InitStatus == COM_EB_INIT)
   {

      ComIPduRefType PduId;
      uint8 BitRes;
      boolean transmit;

      for (PduId = 0U; PduId < Com_gConfigPtr->ComTxIPduArraySize; PduId++)
      {
         /* Deviation MISRA-2 */
         /* Deviation MISRA-3 */
         P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr =
               COM_GET_CONFIG_ELEMENT(ComTxIPduType, Com_gConfigPtr->ComTxIPduRef, PduId);

         CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) IPduFlagBytePtr =
               &Com_gDataMemPtr[(Com_gConfigPtr->ComTxIPduStatusBase + PduId)];


#if (COM_MDT_QUEUE_AVAILABLE == STD_ON)

#if (COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON)
#if (COM_RETRY_FAILED_TRANSMIT_REQ == STD_ON)
         /* clear pending ComRetryFailedTransmitRequests (RTF Requests) in case TxDM expires */
         /* MDT is only started when transmit was successful -> no RTF Request pending,
          * therefore eventually pending transmission request shall be cleared when
          * no MDT is running */
         boolean TxDM_clearRTFR = FALSE;
#endif /* (COM_RETRY_FAILED_TRANSMIT_REQ == STD_ON) */
#endif /* (COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) */

         /* Check if the MDT timed out, if so clear flag */
         /* has to be done even if Pdu is not started! */

         TS_GetBit(IPduFlagBytePtr, COM_TXPDU_MDTQUEUED, uint8, BitRes);
         if (BitRes == TRUE)
         {
            Com_EB_CheckMdtforPdu(PduId, IPduPtr);
         }
#if (COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON)
#if (COM_RETRY_FAILED_TRANSMIT_REQ == STD_ON)
         else
         {
            TxDM_clearRTFR = TRUE;
         }
#endif /* (COM_RETRY_FAILED_TRANSMIT_REQ == STD_ON) */
#endif /* (COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) */

#endif /* (COM_MDT_QUEUE_AVAILABLE == STD_ON) */

         transmit = FALSE;

         TS_GetBit(IPduFlagBytePtr, COM_TXPDU_STARTED, uint8, BitRes);
         if (BitRes == TRUE)
         {
            /* Handle the I-Pdu only if started */

#if (COM_TM_SWITCH_AVAILABLE == STD_ON)

            /* Check if TMs must be switched for periodic parts */
            transmit = Com_EB_CheckTMSforPdu(PduId, IPduPtr);

#endif /* (COM_TM_SWITCH_AVAILABLE == STD_ON) */

#if (COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON)

            TS_GetBit(IPduFlagBytePtr, COM_TXPDU_TXDMQUEUED, uint8, BitRes);
            if (BitRes == TRUE)
            {
               /* Check Tx DM */
               Com_EB_CheckTxDMforPdu(PduId, IPduPtr
#if (COM_MDT_QUEUE_AVAILABLE == STD_ON)
#if (COM_RETRY_FAILED_TRANSMIT_REQ == STD_ON)
                     ,TxDM_clearRTFR
#endif /* (COM_RETRY_FAILED_TRANSMIT_REQ == STD_ON) */
#endif /* (COM_MDT_QUEUE_AVAILABLE == STD_ON) */
                     );
            }

#endif /* (COM_TX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) */


#if (COM_TM_AVAILABLE == STD_ON)
#if (COM_N_TIMES_QUEUE_AVAILABLE == STD_ON)

            TS_GetBit(IPduFlagBytePtr, COM_TXPDU_NTIMESSENDQUEUED, uint8, BitRes);
            if (BitRes == TRUE)
            {
               /* Check if Pdu has to be sent N-times */
               boolean const transmit_ntimes =
                     Com_EB_CheckNTimesSendforPdu(PduId, IPduPtr);

               transmit =  transmit || transmit_ntimes;
            }

#endif /* (COM_N_TIMES_QUEUE_AVAILABLE == STD_ON) */

#if (COM_PERIODIC_QUEUE_AVAILABLE == STD_ON)

            TS_GetBit(IPduFlagBytePtr, COM_TXPDU_PERIODICSENDQUEUED, uint8, BitRes);
            if (BitRes == TRUE)
            {
               /* Check if Pdu has to be sent cyclic */
               boolean const transmit_cyclic =
                     Com_EB_CheckPeriodicSendforPdu(PduId, IPduPtr);

               transmit = transmit || transmit_cyclic;
            }

#endif /* (COM_PERIODIC_QUEUE_AVAILABLE == STD_ON) */

#endif /* (COM_TM_AVAILABLE == STD_ON) */


            /* Now check if the Pdu shall be sent and check if shall be sent
             * immediately */
            Com_EB_Handle_Send_Pdu(PduId, IPduPtr, IPduFlagBytePtr, transmit);

         }                      /* COM_TXPDU_STARTED */


#if (COM_TX_CONFIRMATIONS_DEFERED_AVAILABLE == STD_ON)

         Com_EB_HandleDeferredTxConfirm(IPduPtr);

#endif /* (COM_TX_CONFIRMATIONS_DEFERED_AVAILABLE == STD_ON) */

      }                /* for (PduId = 0U; PduId < Com_gConfigPtr->ComTxIPduArraySize; PduId++) */

   }                            /* if (Com_Status == COM_EB_INIT) */

   DBG_COM_MAINFUNCTIONTX_EXIT();
}                               /* Com_MainFunctionTx */

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_STOP_SEC_CODE
#include <MemMap.h>
#endif

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/
