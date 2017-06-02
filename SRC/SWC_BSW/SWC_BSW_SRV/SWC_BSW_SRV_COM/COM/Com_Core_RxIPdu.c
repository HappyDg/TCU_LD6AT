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
 *
 * MISRA-2) Deviated Rule: 11.3 (advisory)
 * "A cast should not be performed between a pointer type and an integral type."
 *
 * Reason:
 * Actually this is not a cast between a pointer and a integral type, since 0
 * is null pointer constant.
 *
 *
 * MISRA-3) Deviated Rule: 15.2 (required)
 * "An unconditional 'break' statement shall terminate every non-empty switch clause."
 *
 * Reason:
 * fall through allows shorter and non-duplicated code
 *
 * MISRA-4) Deviated Rule: 14.6 (required)
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
 * MISRA-5) Deviated Rule: 6.3 (advisory)
 * "'typedefs' that indicate size and signedness should be used in place of the basic types."
 *
 * Reason:
 * In this case variables are casted to a natural integral type since, the value is further used
 * for purposes where natural types are most efficient (e.g. indexing).
 */

/* NOCOV List
 *
 *
 * NOCOV-UNSUPPORTEDOPTIMIZATION:
 *
 * Reason:
 * A feature is not supported for this release and is inactivated with
 * pre-compile time switches (and therefore not included into the binary).
 */

/*==================[inclusions]============================================*/



#include <Com_Trace.h>
#include <TSAutosar.h>          /* EB specific standard types */
#include <ComStack_Types.h>     /* AUTOSAR Standard types */
#include <Com_Api.h>            /* Module public API */
#include <Com_Lcfg_Static.h>    /* declaration of the callback arrays */
#include <Com_Priv.h>           /* Module private API */
#include <TSMem.h>              /* TS_MemCpy */
#include <Com_Filter.h>         /* Filter functions */
#include <Com_Core_RxIPdu.h>    /* RxIPdu functions */

#if (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)
#include <Com_Core_RxUpdateBit.h> /* UpdateBit Functions */
#endif /*(COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) */
/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_START_SEC_CODE
#include <MemMap.h>
#endif

#if (COM_RX_TIMEOUT_FACTOR_AVAILABLE == STD_ON)

/** \brief Com_EB_HandleRxIPdu_EnableRxDM - starts RxDM of I-Pdu and signal based RxDM
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * - invoke only when Pdu is started.
 * \param[in] IPduPtr - pointer to the description of the Pdu
 * \param[in] IPduFlagBytePtr - Pointer to byte where the flags of the Pdu are
 * stored
 * \retval none
 */

_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_HandleRxIPdu_EnableRxDM
(
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
   P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) IPduFlagBytePtr
);

#endif /* (COM_RX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) */


/** \brief Com_EB_HandleRxIPdu_Start - starts I-Pdu
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] IPduId - Id of Pdu which shall be started
 * \param[in] Initialize - defines if the Pdu group should be initialized
 * \param[in] IPduFlagBytePtr - Pointer to byte where the flags of the Pdu are
 * stored
 * \retval none
 */

_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_HandleRxIPdu_Start
(
   ComIPduRefType IPduId,
   boolean Initialize,
   P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) IPduFlagBytePtr
);


#if (COM_SIGNALS_WITH_UB_RXDM_GW_ONLY == STD_ON)
/** \brief Com_EB_HandleRxSignalsDMUBOnly - handles all Rx signals within an
 * I-Pdu which have only a signal based DM and/or an update bit
 * this function handles all Rx signals Signals within an I-Pdu which have
 * filters with filter COM_F_ALWAYS or COM_F_NEVER, no notification, no signal
 * invalidation configured. Evaluates only the update bit and DM
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * - the filter has to be COM_F_ALWAYS or COM_F_NEVER (or no filter configured)
 * - a notification callback function has to be configured
 * - no invalid value has to be configured
 * \param[in] IPduPtr - pointer to the description of the signal
 * \retval none
 */

_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_HandleRxSignalsDMUBOnly
(
      P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
);
#endif /* (COM_SIGNALS_WITH_UB_RXDM_GW_ONLY == STD_ON) */

#if (COM_CBK_RX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE)
/** \brief Com_EB_HandleRxSig_W_F_A_A_Noti - handles
 * Rx signals with filter COM_F_ALWAYS, Notification but no signal invalidation
 * this function handles the Rx signals which have filters COM_F_ALWAYS and a
 * Notification callback configured but no signal invalidation configured.
 * Evaluates the update bit, DM, and calls the notification callback
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * - the filter has to be COM_F_ALWAYS
 * - a notification callback function has to be configured
 * - no invalid value has to be configured
 * \param[in] IPduPtr - pointer to the description of the signal
 * \retval none
 */

_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_HandleRxSig_W_F_A_A_Noti
(
      P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
);

#endif /* (COM_CBK_RX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

#if (COM_FILTER_RECEIVER_ENABLE == STD_ON)
/** \brief Com_EB_HandleRxSignalsWithBuffer - handles Rx signals with buffers
 * this function handles the Rx signals which have filters (but not COM_F_NEVER
 * or COM_F_ALWAYS) or an invalid value. Evaluates the update bit and DM,
 * invalidates the signal, filters the value (after invalidation as defined in
 * SWS 3.0 -> Deviation in SWS 2.1) updates signal buffers and call the
 * callback functions (receive and invalid)
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] IPduPtr - pointer to the description of the signal
 * \retval none
 */

_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_HandleRxSignalsWithBuffer
(
      P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
);

#endif /* ((COM_FILTER_RECEIVER_ENABLE == STD_ON) */


#if (COM_CBK_RX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE)

#if (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
/** \brief Com_EB_HandleRxSignalGroups - handles Rx signals groups
 * this function evaluates the update bit and DM,
 * invalidates the signal group calls callback of group signals and the
 * signal group
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] IPduPtr - pointer to the description of the signal
 * \retval none
 */

_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_HandleRxSignalGroups
(
      P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
);
#endif /* (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */
#endif /* (COM_CBK_RX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) */


#if (COM_FILTER_RECEIVER_ENABLE == STD_ON)
/** \brief Com_EB_InitRxSignalsWithFilter - initializes the signal buffers and
 * the RxSigGWFlag of all signals of the Rx-Pdus
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] IPduPtr - pointer to the description of the signal
 * \retval E_OK if init was successful
 * \retval E_NOT_OK if init failed (wrong configuration)
 */

_COM_STATIC_ FUNC(uint8, COM_CODE) Com_EB_InitRxSignalsWithFilter
(
      P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
);
#endif /* (COM_FILTER_RECEIVER_ENABLE == STD_ON) */



#if (COM_NOTIFY_RECEIVERS_ENABLE == STD_ON)

/** \brief Com_EB_NotifyReceivers
 * Notifies the receivers about the reception of an PDU. For signals within
 * the PDU Reception filtering is performed
 * \param[in] IPduPtr: pointer to the configuration of the PDU
 * \retval none
 */
TS_MOD_PRIV_DEFN FUNC(void, COM_CODE) Com_EB_NotifyReceivers
(
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
)
{
   DBG_COM_EB_NOTIFYRECEIVERS_ENTRY(IPduPtr);
#if (COM_FILTER_RECEIVER_ENABLE == STD_ON)
   /* Handle all signals with buffers */
   Com_EB_HandleRxSignalsWithBuffer(IPduPtr);
#endif /* (COM_FILTER_RECEIVER_ENABLE == STD_ON) */

#if (COM_CBK_RX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE)
   /* Handle the Rx signals which have the filter COM_F_ALWAYS and a notification
    * (no invalid value) */
   Com_EB_HandleRxSig_W_F_A_A_Noti(IPduPtr);
#endif /* (COM_CBK_RX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

#if (COM_SIGNALS_WITH_UB_RXDM_GW_ONLY == STD_ON)
   /* Handle signals which have only signal base DM and update bits*/
   Com_EB_HandleRxSignalsDMUBOnly(IPduPtr);
#endif /* (COM_SIGNALS_WITH_UB_RXDM_GW_ONLY == STD_ON) */

#if (COM_CBK_RX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE)
#if (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
   /* Handle signal groups */
   Com_EB_HandleRxSignalGroups(IPduPtr);
#endif /* (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */
#endif /* (COM_CBK_RX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) */


   DBG_COM_EB_NOTIFYRECEIVERS_EXIT(IPduPtr);
   return;
}                               /* Com_EB_NotifyReceivers */

#endif /* (COM_NOTIFY_RECEIVERS_ENABLE == STD_ON) */


/** \brief Com_EB_HandleRxIPdu_Start - starts I-Pdu
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] IPduId - Id of Pdu which shall be started
 * \param[in] Initialize - defines if the Pdu group should be initialized
 * \param[in] IPduFlagBytePtr - Pointer to byte where the flags of the Pdu are
 * stored
 * \retval none
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_HandleRxIPdu_Start
(
   ComIPduRefType IPduId,
   boolean Initialize,
   P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) IPduFlagBytePtr
)
{
   uint8 hlp_retval = E_OK;

   DBG_COM_EB_HANDLERXIPDU_START_ENTRY(IPduId,Initialize,IPduFlagBytePtr);

   if (Initialize == TRUE)
   {
      /* initialize the Pdu */
      hlp_retval = Com_EB_InitRxIPdu(IPduId);
   }

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_OFF)
   TS_PARAM_UNUSED(hlp_retval);
#else
   /* CHECK: NOPARSE */
   if (E_OK == hlp_retval)
      /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */
   {
      /* Start group */
      TS_AtomicSetBit_8(IPduFlagBytePtr, COM_RXPDU_STARTED);
   }

   DBG_COM_EB_HANDLERXIPDU_START_EXIT(IPduId,Initialize,IPduFlagBytePtr);
}                               /* Com_EB_HandleRxIPdu_Start */

#if (COM_RX_TIMEOUT_FACTOR_AVAILABLE == STD_ON)

/** \brief Com_EB_HandleRxIPdu_EnableRxDM - starts RxDM of I-Pdu and signal based RxDM
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * - invoke only when Pdu is started.
 * \param[in] IPduPtr - pointer to the description of the Pdu
 * \param[in] IPduFlagBytePtr - Pointer to byte where the flags of the Pdu are
 * stored
 * \retval none
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_HandleRxIPdu_EnableRxDM
(
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
   P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) IPduFlagBytePtr
)
{
   DBG_COM_EB_HANDLERXIPDU_ENABLERXDM_ENTRY(IPduPtr,IPduFlagBytePtr);
#if (COM_RX_FIRST_TIMEOUT_FACTOR_SIZE != COM_SIZE_0_BIT)
   /* RxDM is switch on */
   TS_AtomicSetBit_8(IPduFlagBytePtr, COM_RXPDU_RXDMSWITCHON);
#endif /* (COM_RX_FIRST_TIMEOUT_FACTOR_SIZE != COM_SIZE_0_BIT) */

   /* Pdu based RxDM shall be started if
    * 1) Pdu based RxDM is configured and
    * 2) FirstTimeout != 0 and
    * 3) RxDM not started yet */

   if (COM_GET_COM_RX_IPDU_DM(IPduPtr) == COM_RX_DM_ON)
   {

      Com_RxDMNextDueTimeType const TimeOutOffset =

#if (COM_RX_FIRST_TIMEOUT_FACTOR_SIZE == COM_SIZE_0_BIT)
            COM_GET_RX_TIMEOUT_FACTOR(IPduPtr);
#else
            COM_GET_RX_FIRST_TIMEOUT_FACTOR(IPduPtr);

      /* if ComRxFirstTimeoutFactor is zero start RxDM with first reception */
      if (0U != TimeOutOffset)
#endif /* (COM_RX_FIRST_TIMEOUT_FACTOR_SIZE == COM_SIZE_0_BIT) */
      {

         uint8 RxPduDMEnabled;

         /* enter the critical section */
         Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

         TS_GetBit(IPduFlagBytePtr, COM_RXPDU_RXDMRUNNING, uint8, RxPduDMEnabled);

         /* do not re-start if already enabled  */
         if (RxPduDMEnabled == FALSE)
         {

            /* Set RXDM enabled flag for IPDU */
            Com_SetBitUInt8(IPduFlagBytePtr, COM_RXPDU_RXDMRUNNING);

            /* Start DM timer */
            Com_EB_RxDMQueue(IPduPtr, TimeOutOffset);

         }         /* if (RxPduDMEnabled == FALSE) */


         /* exit the critical section */
         Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();

      }                /* if (0U != TimeOutOffset) */

   }                            /*    if (COM_GET_COM_RX_IPDU_DM(IPduPtr) == COM_RX_DM_ON) */


#if (COM_RX_SIGNAL_BASED_DM == STD_ON)
   /* if I-Pdu based DM is set up do so also for signal(group) based DM */
   Com_EB_EnableSignalBasedDMFlag(IPduPtr);
#if (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
   Com_EB_EnableSignalGroupBasedDMFlag(IPduPtr);
#endif /* (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */
#endif /* (COM_RX_SIGNAL_BASED_DM == STD_ON) */


   DBG_COM_EB_HANDLERXIPDU_ENABLERXDM_EXIT(IPduPtr,IPduFlagBytePtr);
   return;
}                               /* Com_EB_HandleRxIPdu_EnableRxDM */

#endif /* (COM_RX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) */



#if (COM_CBK_RX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE)
/** \brief Com_EB_HandleRxSig_W_F_A_A_Noti - handles
 * Rx signals with filter COM_F_ALWAYS, Notification but no signal invalidation
 * this function handles the Rx signals which have filters COM_F_ALWAYS and a
 * Notification callback configured but no signal invalidation configured.
 * Evaluates the update bit, DM, and calls the notification callback
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * - the filter has to be COM_F_ALWAYS
 * - a notification callback function has to be configured
 * - no invalid value has to be configured
 * \param[in] IPduPtr - pointer to the description of the signal
 * \retval none
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_HandleRxSig_W_F_A_A_Noti
(
      P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
)
{
   ComSignalRefType i;              /* loop variable */
   ComSignalRefType loopStart;      /* variable for start value of loop */
   ComSignalRefType loopStop;       /* variable for stop value of loop */

   ComSignalRefType signalId;   /* Id of signal which belongs to Pdu */
   /* pointer to the configuration of a signal */
   P2CONST(ComRxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr;


#if (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)
   boolean SignalUpdated;
#endif /* (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) */

   DBG_COM_EB_HANDLERXSIG_W_F_A_A_NOTI_ENTRY(IPduPtr);

#if (COM_FILTER_RECEIVER_ENABLE == STD_ON)
   loopStart = IPduPtr->ComIPduSignalWithBufferRefNum;
#else
   loopStart = 0U;
#endif /* (COM_FILTER_RECEIVER_ENABLE == STD_ON) */

   loopStop = IPduPtr->ComIPduSignalW_F_A_NotiRefNum;

   /* Handle all which have no invalidation and COM_F_ALWAYS */
   for (i = loopStart; i < loopStop; i++)
   {
      /* Get signal id and pointer to config of the signal in the signal list of the IPdu */
      /* Deviation MISRA-2, MISRA-5 <+7> */
      signalId =
         (ComSignalRefType) *
         (COM_GET_CONFIG_ELEMENT
          (ComSignalRefType,
           (Com_gConfigPtr->ComRxIPduSignalListRef), (i + IPduPtr->ComIPduSignalRefFirst)));
      /* Deviation MISRA-2 */
      /* Deviation MISRA-5 */
      SignalPtr =
         COM_GET_CONFIG_ELEMENT(ComRxSignalType, Com_gConfigPtr->ComRxSignalRef, signalId);

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
#if (COM_FILTER_RECEIVER_ENABLE == STD_ON)
      /* CHECK: NOPARSE */
      if (SignalPtr->ComFilterType != COM_F_ALWAYS)
      {
         /* The signal has a filter configured which is not COM_F_ALWAYS */
         COM_PRECONDITION_ASSERT(SignalPtr->ComFilterType == COM_F_ALWAYS, COM_INTERNAL_API_ID);
         break;
      }
#else
                  /* No filter available, therefore the signal is treated as a
                   * signal with the filter COM_F_ALWAYS */
#endif /* (COM_FILTER_RECEIVER_ENABLE == STD_ON) */

      /* Check if fptr is valid */
      {
         boolean fail_condition;
         fail_condition =
                 (SignalPtr->ComNotification == COM_CBK_RX_ACK_FUNC_PTR_NULL)
              || (Com_CbkRxAck_Array[(SignalPtr->ComNotification)] == NULL_PTR);
         if (fail_condition)
         {
            COM_PRECONDITION_ASSERT((!fail_condition), COM_INTERNAL_API_ID);
            /* Deviation MISRA-4 */
            break;
         }
      }
      /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */

      /* before calling the callback check the update bit */

#if (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)
      SignalUpdated = Com_EB_CheckRxSignalUpdateBitAndDM(SignalPtr, IPduPtr);
      if (SignalUpdated == TRUE)
#endif /* (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) */

      {
         /* HINT this point should only be reached if no update bit is
            configured or a configured update bit is 1 */

         /* function pointer for ComNotification callbacks */
         P2VAR(Com_CbkRxAck_Type, AUTOMATIC, COM_APPL_CODE) fptr;

         fptr = Com_CbkRxAck_Array[(SignalPtr->ComNotification)];

         /* call the Rx-notification function of the signal */
         fptr();

      } /* update is 1 (or not configured)*/

   }                            /* for (i = loopStart; i < loopStop; i++) */
   DBG_COM_EB_HANDLERXSIG_W_F_A_A_NOTI_EXIT(IPduPtr);
}                               /* Com_EB_HandleRxSig_W_F_A_A_Noti */

#endif /* (COM_CBK_RX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) */





#if (COM_SIGNALS_WITH_UB_RXDM_GW_ONLY == STD_ON)
/** \brief Com_EB_HandleRxSignalsDMUBOnly - handles all Rx signals within an
 * I-Pdu which have only a signal based DM and/or an update bit
 * this function handles all Rx signals Signals within an I-Pdu which have
 * filters with filter COM_F_ALWAYS or COM_F_NEVER, no notification, no signal
 * invalidation configured. Evaluates only the update bit and DM
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * - the filter has to be COM_F_ALWAYS or COM_F_NEVER (or no filter configured)
 * - a notification callback function has to be configured
 * - no invalid value has to be configured
 * \param[in] IPduPtr - pointer to the description of the signal
 * \retval none
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_HandleRxSignalsDMUBOnly
(
      P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
)
{

   ComSignalRefType i;              /* loop variable */
   /* variable for start value of loop */
   ComSignalRefType loopStart = IPduPtr->ComIPduSignalRefFirst;
   /* variable for start value of loop */
   ComSignalRefType loopStop = IPduPtr->ComIPduSignalRefFirst;

   DBG_COM_EB_HANDLERXSIGNALSDMUBONLY_ENTRY(IPduPtr);

   /* it is only neccessary to handle the signals with no DM configured in
    * case the SigGW is enabled */
#if (COM_SIGNAL_GW_ENABLE == STD_ON)
   loopStop = loopStop + IPduPtr->ComIPduSignalRefNum;
#else
   loopStop = loopStop + IPduPtr->ComIPduSignalWithDMOnly;
#endif /* (COM_SIGNAL_GW_ENABLE == STD_ON) */


#if (COM_CBK_RX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE)
   loopStart = loopStart + IPduPtr->ComIPduSignalW_F_A_NotiRefNum;

#else
   /* no notifications can be configured, therefore the loop starts either
    * with ComIPduSignalWithBufferRefNum if available or with 0 */
#if (COM_FILTER_RECEIVER_ENABLE == STD_ON)
   loopStart = loopStart + IPduPtr->ComIPduSignalWithBufferRefNum;
#else
   /* do not change loopStart */
#endif /* (COM_FILTER_RECEIVER_ENABLE == STD_ON) */
#endif /* (COM_CBK_RX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

   /* the loop stops always with ComIPduSignalWithDMOnly, otherwise the this
    * function is not called */

   /* Hanlde all signals with update bit */
   for (i = loopStart; i < loopStop; i++)
   {
      /* Get signal id and pointer to config of the signal in the signal list of the IPdu */
      /* Deviation MISRA-2, MISRA-5 <+7> */
      ComSignalRefType const signalId =
         (ComSignalRefType) *
         (COM_GET_CONFIG_ELEMENT
          (ComSignalRefType, Com_gConfigPtr->ComRxIPduSignalListRef, i));

      /* Deviation MISRA-2 */
      /* Deviation MISRA-5 */
      CONSTP2CONST(ComRxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr =
         COM_GET_CONFIG_ELEMENT(ComRxSignalType, Com_gConfigPtr->ComRxSignalRef, signalId);

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
#if (COM_FILTER_RECEIVER_ENABLE == STD_ON)
      /* CHECK: NOPARSE */
      boolean pass_condition;
      pass_condition =
            (SignalPtr->ComFilterType == COM_F_ALWAYS)
            || (SignalPtr->ComFilterType == COM_F_NEVER);

      if (!(pass_condition))
      {
         /* The signal has a filter configured which is not COM_F_ALWAYS or COM_F_NEVER*/
         COM_PRECONDITION_ASSERT(pass_condition, COM_INTERNAL_API_ID);
         break;
      }
#else
      /* No filter available, therefore the signal is treated as a
       * signal with the filter COM_F_ALWAYS */
#endif /* (COM_FILTER_RECEIVER_ENABLE == STD_ON) */
      {
         boolean fail_condition;
         fail_condition =
#if (COM_SIGNAL_GW_ENABLE == STD_ON)
               (i < (IPduPtr->ComIPduSignalRefFirst + IPduPtr->ComIPduSignalWithDMOnly))
               &&
#endif /* (COM_SIGNAL_GW_ENABLE == STD_ON) */
               (SignalPtr->ComNotification != COM_CBK_RX_ACK_FUNC_PTR_NULL);
         if (fail_condition)
         {
            COM_PRECONDITION_ASSERT((!fail_condition), COM_INTERNAL_API_ID);
            /* Deviation MISRA-4 */
            break;
         }
      }

      /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */

      /* check the update bit */

      (void)Com_EB_CheckRxSignalUpdateBitAndDM(SignalPtr, IPduPtr);

   }                            /* for (i = loopStart; i < loopStop; i++) */


   DBG_COM_EB_HANDLERXSIGNALSDMUBONLY_EXIT(IPduPtr);
}                               /* Com_EB_HandleRxSignalsDMUBOnly */

#endif /* (COM_SIGNALS_WITH_UB_RXDM_GW_ONLY == STD_ON) */


#if (COM_RX_TIMEOUT_FACTOR_AVAILABLE == STD_ON)

/** \brief Com_EB_RxDMQueue - "rewind" the RxDM timeout for an IPDU
 * This function starts a timeout for the Rx deadline monitoring of an IPDU
 * Preconditions:
 * - must only be invoked within a critical section
 * - prior to this call, the COM must be initialized.
 * \param[in] IPduPtr - reference to the I-Pdu configuration
 * \param[in] TimeOutOffset - value which shall be used for "rewind"
 * \retval None
 */
TS_MOD_PRIV_DEFN FUNC(void, COM_CODE) Com_EB_RxDMQueue
(
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
   Com_RxDMNextDueTimeType TimeOutOffset
)
{
   Com_RxDMNextDueTimeType globalTime;

   Com_RxDMNextDueTimeType TimeOut;

   CONSTP2VAR(Com_RxDMNextDueTimeType, AUTOMATIC, COM_VAR_NOINIT) RxTimeoutQueueBase =
           COM_GET_MEMPTR(Com_RxDMNextDueTimeType, Com_gConfigPtr->ComRxTimeoutQueueBase);

           DBG_COM_EB_RXDMQUEUE_ENTRY(IPduPtr,TimeOutOffset);

   /* get global time */
   globalTime = (Com_RxDMNextDueTimeType) Com_GlobalTime;

   /* see other queue-functions above */
   TimeOut = (Com_RxDMNextDueTimeType) (globalTime + TimeOutOffset);
   RxTimeoutQueueBase[IPduPtr->RxDMQueueRef] = TimeOut;


   DBG_COM_EB_RXDMQUEUE_EXIT(IPduPtr,TimeOutOffset);
   return;
}                               /* Com_EB_RxDMQueue */

#endif /* (COM_RX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) */




/** \brief Com_EB_HandleRxIPdu - handles a Rx IPdu
 * function which manages starting/stopping a Rx I-Pdu and enabling/disabling
 * RxDM of Rx I-Pdu.
 * Preconditions:
 * - prior to this call, the COM module shall be initialized
 *
 * \param[in] mode - type of action which should be performed
 * (COM_IPDUGROUP_CONTROL, COM_IPDUGROUP_RXDM_CONTROL)
 * \param[in] toBeActivated - state of start/stop or activate/de-activate RxDM
 * \param[in] IPduPtr - configuration of the I-Pdu
 * \param[in] Initialize - defines if the Pdu group should be initialized
 * in case of starting of Pdus
 * \param[in] IPduId - Id of the I-Pdu
 * \retval None
 */

TS_MOD_PRIV_DEFN FUNC(void, COM_CODE)Com_EB_HandleRxIPdu
(
   Com_IpduGroupModeType mode,
   boolean toBeActivated,
#if (COM_RX_TIMEOUT_FACTOR_AVAILABLE == STD_ON)
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
#endif /* (COM_RX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) */
   boolean Initialize,
   ComIPduRefType IPduId
)
{

   /* pointer to byte with status flags of the Pdu */
   CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) IPduFlagBytePtr =
            &Com_gDataMemPtr[(Com_gConfigPtr->ComRxIPduStatusBase + IPduId)];

   boolean alreadyStarted = FALSE;

   DBG_COM_EB_HANDLERXIPDU_ENTRY(mode,toBeActivated,Initialize,IPduId);
   TS_GetBit(IPduFlagBytePtr, COM_RXPDU_STARTED, uint8, alreadyStarted);

   /* Pdu mode shall be switched */
   /* Pdu shall be started/RxDM shall */
   switch (mode)
   {
   /* Deviation MISRA-3 */
   case COM_IPDUGROUP_CONTROL:
   {
      /* check of state shall change */
      if (toBeActivated != alreadyStarted)
      {
         if (TRUE == toBeActivated)
         {
            /* start the Pdu */
            Com_EB_HandleRxIPdu_Start(IPduId, Initialize, IPduFlagBytePtr);
            /* allow RxDM to be started also */
            alreadyStarted = TRUE;
         }
         else
         {
            /* stop the Pdu */
            /* clear started-flag for the IPdu */
            TS_AtomicClearBit_8(IPduFlagBytePtr, COM_RXPDU_STARTED);
            /* do NOT set alreadyStarted in order to allow deactivation of RxDM */
         }
      }
   }
   /* fall through, as starting an IPdu also requires enabling
    * RxDM */
   /* Deviation MISRA-3 */
#if (COM_RX_TIMEOUT_FACTOR_AVAILABLE == STD_ON)
   case COM_IPDUGROUP_RXDM_CONTROL:
   {
      /* change RxDM state only of Pdu is started */
      if (TRUE == alreadyStarted)
      {
         if (TRUE == toBeActivated)
         {
            /* enable the RxDM of Pdu and signal based RxDM*/
            Com_EB_HandleRxIPdu_EnableRxDM(IPduPtr, IPduFlagBytePtr);
         }
         else
         {

#if (COM_RX_FIRST_TIMEOUT_FACTOR_SIZE != COM_SIZE_0_BIT)
            /* clear first RxDM switch on flag, otherwise a interrupting
             * Com_RxIndication may start RxDM */
            TS_AtomicClearBit_8(IPduFlagBytePtr, COM_RXPDU_RXDMSWITCHON);
#endif /* (COM_RX_FIRST_TIMEOUT_FACTOR_SIZE != COM_SIZE_0_BIT) */

            /* clear RxDM-enabled flag for the IPdu */
            TS_AtomicClearBit_8(IPduFlagBytePtr, COM_RXPDU_RXDMRUNNING);

#if (COM_RX_SIGNAL_BASED_DM == STD_ON)
            /* disable signal(group) based DM */
            Com_EB_DisableSignalAndSignalGroupBasedDMFlag(IPduPtr, FALSE);
#endif /* (COM_RX_SIGNAL_BASED_DM == STD_ON) */
         }
      }
   }
#endif /* (COM_RX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) */
   break;
   /* CHECK: NOPARSE */
   default:
   {
       /* Should never be reached */
       COM_UNREACHABLE_CODE_ASSERT(COM_INTERNAL_API_ID);
   }
   break;
   /* CHECK: PARSE */
   }                            /* switch (mode) */


   DBG_COM_EB_HANDLERXIPDU_EXIT(mode,toBeActivated,Initialize,IPduId);
   return;
}                               /* Com_EB_HandleRxIPdu */


#if (COM_FILTER_RECEIVER_ENABLE == STD_ON)
/** \brief Com_EB_HandleRxSignalsWithBuffer - handles Rx signals with buffers
 * this function handles the Rx signals which have filters (but not COM_F_NEVER
 * or COM_F_ALWAYS) or an invalid value. Evaluates the update bit and DM,
 * invalidates the signal, filters the value (after invalidation as defined in
 * SWS 3.0 -> Deviation in SWS 2.1) updates signal buffers and call the
 * callback functions (receive and invalid)
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] IPduPtr - pointer to the description of the signal
 * \retval none
 */

_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_HandleRxSignalsWithBuffer
(
      P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
)
{
   ComSignalRefType i;              /* loop variable */

   ComSignalRefType signalId;   /* Id of signal which belongs to Pdu */
   /* pointer to the configuration of a signal */
   P2CONST(ComRxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr;

   DBG_COM_EB_HANDLERXSIGNALSWITHBUFFER_ENTRY(IPduPtr);



   /* Handle signals which have buffer (with filter != COM_F_ALWAYS/COM_F_NEVER and/or
    * invalid value) */
   for (i = 0; i < IPduPtr->ComIPduSignalWithBufferRefNum; i++)
   {
#if (COM_FILTER_RECEIVER_ENABLE == STD_ON)
      uint8 filter = TRUE;        /* flag for notification */
#endif /* (COM_FILTER_RECEIVER_ENABLE == STD_ON) */

      /* Get signal id and pointer to config of the signal in the signal list of the IPdu */
      /* Deviation MISRA-2, MISRA-5 <+7> */
      signalId =
            (ComSignalRefType) *
            (COM_GET_CONFIG_ELEMENT
                  (ComSignalRefType,
                        (Com_gConfigPtr->ComRxIPduSignalListRef), (i + IPduPtr->ComIPduSignalRefFirst)));
      /* Deviation MISRA-2 */
      /* Deviation MISRA-5 */
      SignalPtr =
            COM_GET_CONFIG_ELEMENT(ComRxSignalType, Com_gConfigPtr->ComRxSignalRef, signalId);

#if (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)
      if (Com_EB_CheckRxSignalUpdateBitAndDM(SignalPtr, IPduPtr) == TRUE)
#endif /* (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) */

      {
         /* HINT this point should only be reached if no update bit is
          * configured or a configured update bit is 1 */
         /* signal type of the signal */

         {
#if (COM_FILTER_RECEIVER_ENABLE == STD_ON)

            ComCommonFilterPropertiesType ComFilterProp;
            ComCommonReadPropType ComReadProp;

            Com_EB_CreateFilterProp(
               &ComFilterProp,
               SignalPtr->ComFilterSignalValueRef,
               SignalPtr->ComFilterRef,
               SignalPtr->ComFilterType);

            Com_EB_CreateReadProp(
               &ComReadProp,
               SignalPtr,
               IPduPtr
#if (COM_VALUE_INIT_REPLACE == STD_ON)
               ,FALSE
#endif /* (COM_VALUE_INIT_REPLACE == STD_ON) */
            );

            filter = Com_EB_CalculateFilter(&ComReadProp, &ComFilterProp);

#endif /* (COM_FILTER_RECEIVER_ENABLE == STD_ON) */

         }


#if (COM_SIGGW_RX_FILTER_ENABLE == STD_ON)
#if (COM_SIGNAL_GW_ENABLE == STD_ON)

         /* in case the signal shall be gated if
          * - the signal has a gateway relation
          * - the filter evaluates to TRUE */
         if ((filter == TRUE) && (SignalPtr->ComSignalSigGWFlagBit != COM_SIGNAL_INVALID))
         {
            /* set the SigGWFlag */
            TS_AtomicSetBit_8(COM_RX_SIGNAL_SIG_GW_FLAG_ADDRESS(SignalPtr),
                  COM_RX_SIGNAL_SIG_GW_FLAG_BIT(SignalPtr));
         }

#endif /* (COM_SIGNAL_GW_ENABLE == STD_ON) */
#endif /* (COM_SIGGW_RX_FILTER_ENABLE == STD_ON) */


         {
            /* if no invalid notifications have been called check if the
             * normal notifications should be called */

#if (COM_CBK_RX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE)

            /* check if notification is configured and call it */
#if (COM_FILTER_RECEIVER_ENABLE == STD_ON)
            if (filter == TRUE)
#endif /* (COM_FILTER_RECEIVER_ENABLE == STD_ON) */
            {
               if (SignalPtr->ComNotification != COM_CBK_RX_ACK_FUNC_PTR_NULL)
               {
                  /* function pointer for ComNotification callbacks */
                  P2VAR(Com_CbkRxAck_Type, AUTOMATIC, COM_APPL_CODE) fptr;

                  fptr = Com_CbkRxAck_Array[(SignalPtr->ComNotification)];

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
                  /* Check if fptr is valid */
                  /* CHECK: NOPARSE */
                  if (fptr == NULL_PTR)
                  {
                     COM_PRECONDITION_ASSERT((fptr != NULL_PTR), COM_INTERNAL_API_ID);
                     break;
                  }
                  /* CHECK: PARSE */
#endif /* COM_PRECONDITION_ASSERT_ENABLED == STD_ON */

                  /* call the Rx-notification function of the signal */
                  fptr();
               }
            }                /* check if notification is configured and call it */
#endif /* (COM_CBK_RX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

         }                   /* else from if (InvalidNotification == TRUE) */

      }                      /* if update bit is 1 */

   }                            /* for(i = 0; i < SignalWithBufferIdxMax; i++) */


   DBG_COM_EB_HANDLERXSIGNALSWITHBUFFER_EXIT(IPduPtr);
}                               /* Com_EB_HandleRxSignalsWithBuffer */
#endif /* (COM_FILTER_RECEIVER_ENABLE == STD_ON) */




#if (COM_CBK_RX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE)

#if (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
/** \brief Com_EB_HandleRxSignalGroups - handles Rx signals groups
 * this function evaluates the update bit and DM,
 * invalidates the signal group calls callback of group signals and the
 * signal group
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] IPduPtr - pointer to the description of the signal
 * \retval none
 */

_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_HandleRxSignalGroups
(
      P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
)
{
   ComSignalGroupRefType i;              /* loop variable */


   ComSignalGroupRefType signalGId;   /* Id of signal group which belongs to Pdu */
   /* reference to the configuration of a signal group */
   P2CONST(ComRxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr;

   DBG_COM_EB_HANDLERXSIGNALGROUPS_ENTRY(IPduPtr);

   /* Handle signals all signal groups within the I-Pdu */
   for (i = 0; i < IPduPtr->ComIPduSignalGroupRefNum; i++)
   {

      /* Get signal id and pointer to config of the signal in the signal list of the IPdu */
      /* Deviation MISRA-2, MISRA-5 <+7> */
      signalGId =
         (ComSignalGroupRefType) *
         (COM_GET_CONFIG_ELEMENT
          (ComSignalGroupRefType,
           (Com_gConfigPtr->ComRxIPduSignalGroupListRef),
           (i + IPduPtr->ComIPduSignalGroupRefFirst)));
      /* Deviation MISRA-2 */
      /* Deviation MISRA-5 */
      SignalGPtr =
         COM_GET_CONFIG_ELEMENT(ComRxSignalGroupType,
               Com_gConfigPtr->ComRxSignalGroupRef, signalGId);

#if (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)
      if (Com_EB_CheckRxSignalGoupUpdateBitAndDM(SignalGPtr, IPduPtr) == TRUE)
#endif /* (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) */
      {
         /* HINT this point should only be reached if no update bit is
          * configured or a configured update bit is 1 */



#if (COM_CBK_RX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE)

            {
               /* check if notification is configured and call it */

               if (SignalGPtr->ComNotification != COM_CBK_RX_ACK_FUNC_PTR_NULL)
               {
                  P2VAR(Com_CbkRxAck_Type, AUTOMATIC, COM_APPL_CODE) fptr;

                  fptr = Com_CbkRxAck_Array[(SignalGPtr->ComNotification)];

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
                  /* Check if fptr is valid */
                  /* CHECK: NOPARSE */
                  if (fptr == NULL_PTR)
                  {
                      COM_PRECONDITION_ASSERT((fptr != NULL_PTR), COM_INTERNAL_API_ID);
                      break;
                  }
                  /* CHECK: PARSE */
#endif /* COM_PRECONDITION_ASSERT_ENABLED == STD_ON */

                  /* call the Rx-notification function of the signal group */
                  fptr();

               }                         /* check if notification is configured and call it */

            }
#endif /* (COM_CBK_RX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

      }                         /* group signal is updated */

   }                            /* for (i = 0; i < IPduPtr->ComIPduSignalGroupRefNum; i++) */
   DBG_COM_EB_HANDLERXSIGNALGROUPS_EXIT(IPduPtr);
}                               /* Com_EB_HandleRxSignalGroups */
#endif /* (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

#endif /* (COM_CBK_RX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) */


#if (COM_FILTER_RECEIVER_ENABLE == STD_ON)
/** \brief Com_EB_InitRxSignalsWithFilter - initializes the signal buffers and
 * the RxSigGWFlag of all signals of the Rx-Pdus
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] IPduPtr - pointer to the description of the signal
 * \retval E_OK if init was successful
 * \retval E_NOT_OK if init failed (wrong configuration)
 */

_COM_STATIC_ FUNC(uint8, COM_CODE) Com_EB_InitRxSignalsWithFilter
(
      P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
)
{
   uint8 retval = E_OK;
   ComSignalRefType j;

   DBG_COM_EB_INITRXSIGNALSWITHFILTER_ENTRY(IPduPtr);

   /* initialize signals with buffer */
   for (j = 0; j < IPduPtr->ComIPduSignalWithBufferRefNum; j++)
   {

      /* Get signal id and pointer to config of the signal in the signal list of the IPdu */
      Com_TS_SignalTypeType SignalType; /* type of the signal */
      /* Id of signal which belongs to Pdu */
      /* Deviation MISRA-2, MISRA-5 <+7> */
      ComSignalRefType signalId =
         (ComSignalRefType) * (COM_GET_CONFIG_ELEMENT(ComSignalRefType,
                                                      (Com_gConfigPtr->ComRxIPduSignalListRef),
                                                       (j + IPduPtr->ComIPduSignalRefFirst)));
      /* pointer to the configuration of the signal */
      /* Deviation MISRA-2 */
      /* Deviation MISRA-5 */
      P2CONST(ComRxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr =
         COM_GET_CONFIG_ELEMENT(ComRxSignalType, Com_gConfigPtr->ComRxSignalRef, signalId);

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
      /* CHECK: NOPARSE */
      if (NULL_PTR == SignalPtr)
      {
          COM_PRECONDITION_ASSERT(
                  (NULL_PTR == SignalPtr),
                  COM_INTERNAL_API_ID);
          retval = E_NOT_OK;
          break;
      }
      if (SignalPtr->ComConfigCheckData != COM_CONFIG_CHECK_RX_SIGNAL)
      {
          COM_PRECONDITION_ASSERT(
                  (SignalPtr->ComConfigCheckData == COM_CONFIG_CHECK_RX_SIGNAL),
                  COM_INTERNAL_API_ID);
          retval = E_NOT_OK;
          /* Deviation MISRA-4 */
          break;
      }
      /* CHECK: PARSE */
#endif /* COM_PRECONDITION_ASSERT_ENABLED == STD_ON */

      /* get signal type */
      SignalType = COM_GET_RX_SIGNAL_SIGNAL_TYPE(SignalPtr);

      {

         ComCommonReadPropType ComReadProp;
         Com_EB_CreateReadProp(
            &ComReadProp,
            SignalPtr,
            IPduPtr
#if (COM_VALUE_INIT_REPLACE == STD_ON)
            ,FALSE
#endif /* (COM_VALUE_INIT_REPLACE == STD_ON) */
         );

         {
            uint32 const NewVal = Com_EB_ReadFromPduOrShadowBuffer(&ComReadProp);

            Com_EB_SetBufferUInt32(NewVal, SignalType, SignalPtr->ComFilterSignalValueRef);
         }

      }

      /* COM_UINT8_N have no signal buffer even if they have a filter */

#if (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON)
      if (SignalPtr->ComFilterType == COM_F_ONE_EVERY_N)
      {
         /* reset the OneEveryN filter */
         Com_ResetFilerOneEveryN(SignalPtr->ComFilterRef);
      }
#endif /* (COM_FILTER_ONE_EVERY_N_AVAILABLE == STD_ON) */

#if (COM_SIGNAL_GW_ENABLE == STD_ON)
#if (COM_SIGGW_RX_FILTER_ENABLE == STD_ON)
      /* initialize the flags for the SigGwRxFilter */
      if (SignalPtr->ComSignalSigGWFlagBit != COM_SIGNAL_INVALID)
      {
         /* reset ComSignalSigGWFlagBit */
         TS_AtomicClearBit_8(COM_RX_SIGNAL_SIG_GW_FLAG_ADDRESS(SignalPtr),
               COM_RX_SIGNAL_SIG_GW_FLAG_BIT(SignalPtr));
      }
#endif /* (COM_SIGGW_RX_FILTER_ENABLE == STD_ON) */
#endif /* (COM_SIGNAL_GW_ENABLE == STD_ON) */

   }                          /* for (j = 0; j < IPduPtr->ComIPduSignalWithBufferRefNum; j++) */


   DBG_COM_EB_INITRXSIGNALSWITHFILTER_EXIT(retval,IPduPtr);
   return retval;
}                               /* Com_EB_InitRxSignalsWithFilter */
#endif /* (COM_FILTER_RECEIVER_ENABLE == STD_ON) */



/** \brief Com_EB_InitRxIPdu - initializes the specified Rx IPdu and the
 * Rx-Signals associated with it
 * NOTE does not clear the RAM buffers of ONE_EVERY_N filters
 * \param[in] RxPduId -IPdu which should be initialized
 * \retval E_OK if init was successful
 * \retval E_NOT_OK if init failed (wrong configuration)
 */

TS_MOD_PRIV_DEFN FUNC(uint8, COM_CODE) Com_EB_InitRxIPdu
(
   ComIPduRefType RxPduId
)
{

   /* pointer to config structure of I-Pdu */
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr;
   uint8 retval = E_NOT_OK;         /* return value of check of I-Pdu */

   DBG_COM_EB_INITRXIPDU_ENTRY(RxPduId);


   /* get IPdu to which RxPduId identifies and check if the IPdu is valid */
   /* Deviation MISRA-2 */
   /* Deviation MISRA-5 */
   IPduPtr = COM_GET_CONFIG_ELEMENT(ComRxIPduType, Com_gConfigPtr->ComRxIPduRef, RxPduId);

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
   /* CHECK: NOPARSE */
   if (NULL_PTR == IPduPtr)
   {
       COM_PRECONDITION_ASSERT(
               (NULL_PTR == IPduPtr),
               COM_INTERNAL_API_ID);
   }
   else if (IPduPtr->ComConfigCheckData != COM_CONFIG_CHECK_RX_IPDU)
   {
       COM_PRECONDITION_ASSERT(
               (IPduPtr->ComConfigCheckData == COM_CONFIG_CHECK_RX_IPDU),
               COM_INTERNAL_API_ID);
   }
   else
   /* CHECK: PARSE */
#endif /* COM_PRECONDITION_ASSERT_ENABLED == STD_ON */

   {

      retval = E_OK;

#if (COM_SIGNAL_INIT_VALUE_ENABLE == STD_ON)
       {
          /* a init value for the I-Pdu is available */

          /* set pointer to the first byte of the init value */
          /* Deviation MISRA-2 */
          /* Deviation MISRA-5 */
          CONSTP2CONST(uint8, AUTOMATIC, COM_APPL_CONST)valPtr =
                COM_GET_CONFIG_ELEMENT(uint8, IPduPtr->ComInitValueRef, 0);

          /* copy PDU Init data to PDU buffer */
          TS_MemCpy(&Com_gDataMemPtr[IPduPtr->ComIPduValueRef], valPtr, IPduPtr->ComIPduSize);

       }
#else
       {
          ComIPduSizeType pdubyte;           /*iteration variable */
          /* no init value is available, use the default value
           * COM_SIGNAL_INIT_VALUE_CONSTANT instead */
          /* NOCOV-UNSUPPORTEDOPTIMIZATION */
          for (pdubyte = 0; pdubyte < (IPduPtr->ComIPduSize); pdubyte++)
          {
             Com_gDataMemPtr[(IPduPtr->ComIPduValueRef + pdubyte)] =
                   (uint8) COM_SIGNAL_INIT_VALUE_CONSTANT;
          }
       }

#endif /* (COM_SIGNAL_INIT_VALUE_ENABLE == STD_ON) */

       /* HINT: there is no need to initialize signal group buffer here see note
        * of COM484: Since it is not suspected that a well-formed SWC tries to read
        * a group signal before a call to Com_ReceiveSignalGroup COM484 applies to
        * the sender side only.*/

       /* clear all flags of the IPdu */
       Com_gDataMemPtr[(Com_gConfigPtr->ComRxIPduStatusBase + RxPduId)] = 0U;

#if (COM_FILTER_RECEIVER_ENABLE == STD_ON)
       retval = Com_EB_InitRxSignalsWithFilter(IPduPtr);
#endif /* (COM_FILTER_RECEIVER_ENABLE == STD_ON) */

#if (COM_SIGNAL_GW_ENABLE == STD_ON)
       /* reset ComIPduSigGWFlagBit  */
       if (IPduPtr->ComIPduSigGWFlagBit != COM_IPDU_INVALID)
       {
          /* clear the I-Pdu SigGWFlag */
          TS_AtomicClearBit_8(COM_RX_IPDU_SIG_GW_FLAG_ADDRESS(IPduPtr),
                COM_RX_IPDU_SIG_GW_FLAG_BIT(IPduPtr));
       }
#endif /* (COM_SIGNAL_GW_ENABLE == STD_ON) */

#if (COM_RX_SIGNAL_BASED_DM == STD_ON)
       /* clear the flags for signal based DM */
       Com_EB_DisableSignalAndSignalGroupBasedDMFlag(IPduPtr, TRUE);
#endif /* (COM_RX_SIGNAL_BASED_DM == STD_ON) */
   }


   DBG_COM_EB_INITRXIPDU_EXIT(retval,RxPduId);
   return retval;
}                               /* Com_EB_InitRxIPdu */


/** \brief Com_EB_CreateReadProp - initializes the internal
 * structure for the representation of an Rx-signal
 * Preconditions:
 * - prior to this call, the COM module shall be initialized
 * \param[out] ComReadPropPtr - pointer where the result shall be stored
 * \param[in] SignalPtr - pointer to the description of the Rx signal
 * \param[in] IPduPtr - pointer to the description of the I-PDU of the signal
 * \param[in] TakePtrROM - defines if the initial value shall be used
 * \retval None
 */
TS_MOD_PRIV_DEFN FUNC(void, COM_CODE) Com_EB_CreateReadProp
(
   P2VAR(ComCommonReadPropType, AUTOMATIC, AUTOMATIC) ComReadPropPtr,
   P2CONST(ComRxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr,
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
#if (COM_VALUE_INIT_REPLACE == STD_ON)
   ,boolean TakePtrROM
#endif /* (COM_VALUE_INIT_REPLACE == STD_ON) */
)
{

   ComReadPropPtr->pdudataptrRAM = &Com_gDataMemPtr[(IPduPtr->ComIPduValueRef)];
#if (COM_SIGNAL_INIT_VALUE_ENABLE == STD_ON)
   ComReadPropPtr->pdudataptrROM = COM_GET_CONFIG_ELEMENT(uint8, IPduPtr->ComInitValueRef, 0U);
#endif /* (COM_SIGNAL_INIT_VALUE_ENABLE == STD_ON) */
#if (COM_FILTER_RECEIVER_ENABLE == STD_ON)
   ComReadPropPtr->ComFilterSignalValueRef = SignalPtr->ComFilterSignalValueRef;
#endif /* (COM_FILTER_RECEIVER_ENABLE == STD_ON) */
#if (COM_SIGNAL_BYTE_ALIGN == STD_ON)
   ComReadPropPtr->ComSignalPositionInByte =
         SignalPtr->RxBasicParam.ComSignalPositionInByte;
#elif (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
   ComReadPropPtr->ComSignalPositionInBit = SignalPtr->RxBasicParam.ComSignalPositionInBit;
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_ON) */
   ComReadPropPtr->ComBitSize= SignalPtr->RxBasicParam.ComBitSize;
#if (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE)
   ComReadPropPtr->Endianness = COM_GET_RX_SIGNAL_ENDIANNESS(SignalPtr);
#endif /* (COM_ENDIANNESS_CONVERSION == COM_ENDIAN_ENABLE) */
   ComReadPropPtr->SignalType = COM_GET_RX_SIGNAL_SIGNAL_TYPE(SignalPtr);
#if (COM_VALUE_INIT_REPLACE == STD_ON)
   ComReadPropPtr->TakePtrROM = TakePtrROM;
#endif /* (COM_VALUE_INIT_REPLACE == STD_ON) */

   return;

}                               /* Com_EB_CreateReadSigProp */


#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_STOP_SEC_CODE
#include <MemMap.h>
#endif


