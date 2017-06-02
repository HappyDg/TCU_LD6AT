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
 * MISRA-1) Deviated Rule: 11.3 (required)
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
 */

/*==================[inclusions]============================================*/


#include <Com_Trace.h>
#include <TSAutosar.h>          /* EB specific standard types */
#include <ComStack_Types.h>     /* AUTOSAR Standard types */
#include <Com_Api.h>                /* Module public API */

#include <Com_Priv.h>           /* Module private API */

#if (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)

#include <Com_Core_RxUpdateBit.h> /* UpdateBit Functions */

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_START_SEC_CODE
#include <MemMap.h>
#endif


#if (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
/** \brief Com_EB_CheckRxSignalGoupUpdateBitAndDM - handles update bit and DM of
 * Rx signals groups
 * this function evaluates the update bit and DM of Rx signals groups and
 * returns whether the value has to be replaced or not
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] SignalGPtr - reference to the description of the signal group
 * \param[in] IPduPtr - reference to the description of the signal group
 * \retval TRUE if the signal was updated, else FALSE
 */

TS_MOD_PRIV_DEFN FUNC(boolean, COM_CODE) Com_EB_CheckRxSignalGoupUpdateBitAndDM
(
   P2CONST(ComRxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr,
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
)
{
   uint8 SignalUpdated = 1U;
   DBG_COM_EB_CHECKRXSIGNALGOUPUPDATEBITANDDM_ENTRY(SignalGPtr,IPduPtr);

#if (COM_UPDATE_BIT_RX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL)
      if (COM_GET_RX_SIGNAL_GROUP_UPDATE_BIT(SignalGPtr) == COM_UPDATE_BIT_PRESENT)
#endif /* (COM_UPDATE_BIT_RX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL) */
      { /* update bit is available, check if bit is 1 */

         TS_GetBit(
               &Com_gDataMemPtr[(IPduPtr->ComIPduValueRef +
                     (SignalGPtr->ComUpdateBitPositionInBit / 8U))],
                     (SignalGPtr->ComUpdateBitPositionInBit % 8U),
                     uint8,
                     SignalUpdated);

#if (COM_RX_SIGNAL_BASED_DM == STD_ON)
         if (SignalUpdated == 1U)
         {

            /* check if signal group has a signal group based DM configured */
            if (COM_GET_RX_SIGNAL_GROUP_DM(SignalGPtr) == COM_RX_DM_ON)
            {

               uint8 BitRes;

               /* calculate the position of the flags */
               CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) RxDMFlagPtr =
                     COM_RX_SIGNAL_GROUP_DM_FLAGS_BYTE_POS(SignalGPtr);

               /* calculate position of the running flag */
               uint8 const RunningFlag =
                     (uint8)COM_RX_SIGNAL_GROUP_DM_RUNNING_BIT_POS(SignalGPtr);

               /* calculate position of the timeout flag */
               uint8 const ToutFlag =
                     (uint8)COM_RX_SIGNAL_GROUP_DM_TIMEOUT_BIT_POS(SignalGPtr);

               Com_RxDMNextDueTimeType const TimeOutOffset =
                     COM_GET_RX_SIGNAL_GROUP_TIMEOUT_FACTOR(SignalGPtr);

               /* enter critical section */
               Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

               TS_GetBit(RxDMFlagPtr, RunningFlag, uint8, BitRes);

               /* handle RxDM if enabled */
               if (1U == BitRes)
               {
                  /* Clear the timeout flag */
                  Com_ClearBitUInt8(RxDMFlagPtr, ToutFlag);

                  /* signal group based DM is enabled therefore rewind */
                  Com_EB_RxDMSignalGroupQueue(SignalGPtr, TimeOutOffset);
               }
#if (COM_RX_FIRST_TIMEOUT_FACTOR_SIZE != COM_SIZE_0_BIT)
               else
               {
                  ComIPduRefType const ComRxPduId = SignalGPtr->ComIPduRef;

                  /* pointer to byte with status flags of the Pdu */
                  CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) IPduFlagBytePtr =
                           &Com_gDataMemPtr[(Com_gConfigPtr->ComRxIPduStatusBase + ComRxPduId)];

                  /* RxDM is not running, check if shall be enabled */
                  /* check if RxDM is switched on */
                  TS_GetBit(IPduFlagBytePtr, COM_RXPDU_RXDMSWITCHON, uint8, BitRes);
                  if (1U == BitRes)
                  {
                     /* Clear the timeout flag */
                     Com_ClearBitUInt8(RxDMFlagPtr, ToutFlag);

                     /* enable RxDM */
                     Com_SetBitUInt8(RxDMFlagPtr, RunningFlag);

                     /* signal group based DM is enabled therefore rewind */
                     Com_EB_RxDMSignalGroupQueue(SignalGPtr, TimeOutOffset);
                  }

               }
#endif /* (COM_RX_FIRST_TIMEOUT_FACTOR_SIZE != COM_SIZE_0_BIT) */

               /* leave critical section */
               Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();


            }                   /* if (COM_GET_RX_SIGNAL_GROUP_DM(SignalGPtr) == COM_RX_DM_ON) */

         }                      /* if (SignalUpdated == 1U) */
#endif /* (COM_RX_SIGNAL_BASED_DM == STD_ON) */

      }                         /* update bit is available, check if bit is 1 */
      DBG_COM_EB_CHECKRXSIGNALGOUPUPDATEBITANDDM_EXIT(SignalUpdated,SignalGPtr,IPduPtr);
      return SignalUpdated;
}                               /* Com_EB_CheckRxSignalGoupUpdateBitAndDM */
#endif /* (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */




/** \brief Com_EB_CheckRxSignalUpdateBitAndDM - handles update bit and DM of
 * Rx signals this function evaluates the update bit and DM of Rx signals and
 * returns whether the value has to be replaced or not
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] SignalPtr - reference to the description of the signal
 * \param[in] IPduPtr - reference to the description of the signal
 * \retval TRUE if the signal was updated, else FALSE
 */

TS_MOD_PRIV_DEFN FUNC(boolean, COM_CODE) Com_EB_CheckRxSignalUpdateBitAndDM
(
   P2CONST(ComRxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr,
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
)
{
   uint8 SignalUpdated = 1U;
   DBG_COM_EB_CHECKRXSIGNALUPDATEBITANDDM_ENTRY(SignalPtr,IPduPtr);

#if (COM_UPDATE_BIT_RX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL)
      if (COM_GET_RX_SIGNAL_UPDATE_BIT(SignalPtr) == COM_UPDATE_BIT_PRESENT)
#endif /* (COM_UPDATE_BIT_RX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL) */
      { /* update bit is available, check if bit is 1 */

         TS_GetBit(
               &Com_gDataMemPtr[(IPduPtr->ComIPduValueRef +
                     (SignalPtr->RxBasicParam.ComUpdateBitPositionInBit / 8U))],
                     (SignalPtr->RxBasicParam.ComUpdateBitPositionInBit % 8U),
                     uint8,
                     SignalUpdated);

#if (COM_RX_SIGNAL_BASED_DM == STD_ON)
         if (SignalUpdated == 1U)
         {

            /* check if signal has a signal based DM configured */
            if (COM_GET_RX_SIGNAL_DM(SignalPtr) == COM_RX_DM_ON)
            {

               uint8 BitRes;

               /* calculate the position of the flags */
               CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) RxDMFlagPtr =
                     COM_RX_SIGNAL_DM_FLAGS_BYTE_POS(SignalPtr);

               /* calculate position of the running flag */
               uint8 const RunningFlag = (uint8)COM_RX_SIGNAL_DM_RUNNING_BIT_POS(SignalPtr);

               /* calculate position of the timeout flag */
               uint8 const ToutFlag = (uint8)COM_RX_SIGNAL_DM_TIMEOUT_BIT_POS(SignalPtr);

               Com_RxDMNextDueTimeType const TimeOutOffset =
                     COM_GET_RX_SIGNAL_TIMEOUT_FACTOR(SignalPtr);

               /* enter critical section */
               Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

               TS_GetBit(RxDMFlagPtr, RunningFlag, uint8, BitRes);

               /* handle RxDM if enabled */
               if (1U == BitRes)
               {
                  /* clear time out flag, new value is available */
                  Com_ClearBitUInt8(RxDMFlagPtr, ToutFlag);

                  /* signal based DM is enabled therefore rewind */
                  Com_EB_RxDMSignalQueue(SignalPtr, TimeOutOffset);
               }
#if (COM_RX_FIRST_TIMEOUT_FACTOR_SIZE != COM_SIZE_0_BIT)
               else
               {
                  ComIPduRefType const ComRxPduId = SignalPtr->RxBasicParam.ComIPduRef;

                  /* pointer to byte with status flags of the Pdu */
                  CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) IPduFlagBytePtr =
                           &Com_gDataMemPtr[(Com_gConfigPtr->ComRxIPduStatusBase + ComRxPduId)];

                  /* RxDM is not running, check if shall be enabled */
                  /* check if RxDM is switched on */
                  TS_GetBit(IPduFlagBytePtr, COM_RXPDU_RXDMSWITCHON, uint8, BitRes);
                  if (1U == BitRes)
                  {
                     /* clear time out flag, new value is available */
                     Com_ClearBitUInt8(RxDMFlagPtr, ToutFlag);

                     /* enable RxDM */
                     Com_SetBitUInt8(RxDMFlagPtr, RunningFlag);

                     /* signal based DM is enabled therefore start */
                     Com_EB_RxDMSignalQueue(SignalPtr, TimeOutOffset);
                  }
               }
#endif /* (COM_RX_FIRST_TIMEOUT_FACTOR_SIZE != COM_SIZE_0_BIT) */

               /* leave critical section */
               Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();

            }                   /* if (COM_GET_RX_SIGNAL_DM(SignalPtr) == COM_RX_DM_ON) */

         }                      /* if (SignalUpdated == 1U) */
#endif /* (COM_RX_SIGNAL_BASED_DM == STD_ON) */

      }                         /* update bit is available, check if bit is 1 */
      DBG_COM_EB_CHECKRXSIGNALUPDATEBITANDDM_EXIT(SignalUpdated,SignalPtr,IPduPtr);
      return SignalUpdated;
}                               /* Com_EB_CheckRxSignalUpdateBitAndDM */


#if (COM_RX_SIGNAL_BASED_DM == STD_ON)

#if (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
/** \brief Com_EB_RxDMSignalGroupQueue - "rewind" the RxDM timeout for a
 * signal group
 * This function starts a timeout for the Rx deadline monitoring of a
 * signal group
 * Preconditions:
 * - must only be invoked within a critical section
 * - prior to this call, the COM must be initialized.
 * \param[in] SignalGPtr pointer to configuration of the Rx signal group to
 * start deadline monitoring
 * \param[in] TimeOutOffset - value which shall be used for "rewind"
 * \retval None
 */
TS_MOD_PRIV_DEFN FUNC(void, COM_CODE) Com_EB_RxDMSignalGroupQueue
(
   P2CONST(ComRxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr,
   Com_RxDMNextDueTimeType TimeOutOffset
)
{
   Com_RxDMNextDueTimeType globalTime;
   Com_RxDMNextDueTimeType TimeOut;

   CONSTP2VAR(Com_RxDMNextDueTimeType, AUTOMATIC, COM_VAR_NOINIT) RxTimeoutSignalGroupQueueBase =
       COM_GET_MEMPTR(Com_RxDMNextDueTimeType, Com_gConfigPtr->ComRxTimeoutSignalGroupQueueBase);

    DBG_COM_EB_RXDMSIGNALGROUPQUEUE_ENTRY(SignalGPtr,TimeOutOffset);

   /* get global time */
   globalTime = (Com_RxDMNextDueTimeType) Com_GlobalTime;

   /* see other queue-functions above */
   TimeOut = (Com_RxDMNextDueTimeType) (globalTime + TimeOutOffset);
   RxTimeoutSignalGroupQueueBase[SignalGPtr->RxGroupSignalFlagsRef] = TimeOut;
   DBG_COM_EB_RXDMSIGNALGROUPQUEUE_EXIT(SignalGPtr,TimeOutOffset);
}                               /* Com_EB_RxDMSignalGroupQueue */
#endif /* (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */


/** \brief Com_EB_RxDMSignalQueue - "rewind" the RxDM timeout for a signal
 * This function starts a timeout for the Rx deadline monitoring of a signal
 * Preconditions:
 * - must only be invoked within a critical section
 * - prior to this call, the COM must be initialized.
 * \param[in] SignalPtr pointer to configuration of the Rx signal to start
 * deadline monitoring
  * \param[in] TimeOutOffset - value which shall be used for "rewind"
 * \retval None
 */
TS_MOD_PRIV_DEFN FUNC(void, COM_CODE) Com_EB_RxDMSignalQueue
(
   P2CONST(ComRxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr,
   Com_RxDMNextDueTimeType TimeOutOffset
)
{
   Com_RxDMNextDueTimeType globalTime;
   Com_RxDMNextDueTimeType TimeOut;

   CONSTP2VAR(Com_RxDMNextDueTimeType, AUTOMATIC, COM_VAR_NOINIT) RxTimeoutSignalQueueBase =
       COM_GET_MEMPTR(Com_RxDMNextDueTimeType, Com_gConfigPtr->ComRxTimeoutSignalQueueBase);

   DBG_COM_EB_RXDMSIGNALQUEUE_ENTRY(SignalPtr,TimeOutOffset);

   /* get global time */
   globalTime = (Com_RxDMNextDueTimeType) Com_GlobalTime;

   /* see other queue-functions above */
   TimeOut = (Com_RxDMNextDueTimeType) (globalTime + TimeOutOffset);
   RxTimeoutSignalQueueBase[SignalPtr->RxSigDMQueueRef] = TimeOut;

   DBG_COM_EB_RXDMSIGNALQUEUE_EXIT(SignalPtr,TimeOutOffset);
}                               /* Com_EB_RxDMSignalQueue */


/** \brief Com_EB_EnableSignalBasedDMFlag - sets up signal based DM
 * Preconditions:
 * - prior to this call, the COM module shall be initialized
 * \param[in] IPduPtr - configuration of the I-Pdu
 * \retval None
 */
TS_MOD_PRIV_DEFN FUNC(void, COM_CODE)Com_EB_EnableSignalBasedDMFlag
(
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
)
{
   ComSignalRefType i; /* iteration variable for signal list*/
   DBG_COM_EB_ENABLESIGNALBASEDDMFLAG_ENTRY(IPduPtr);

   /* set up signal based DM */
   for (i = IPduPtr->ComIPduSignalRefFirst;
   i < (IPduPtr->ComIPduSignalWithDMOnly + IPduPtr->ComIPduSignalRefFirst); i++)
   {
      /* Get signal id and pointer to config of the signal in the signal list of the IPdu */
      /* Deviation MISRA-1, MISRA-2 <+7> */
      ComSignalRefType const signalId =
         (ComSignalRefType) *
         (COM_GET_CONFIG_ELEMENT
          (ComSignalRefType, Com_gConfigPtr->ComRxIPduSignalListRef, i));

       /* Deviation MISRA-1 */
       /* Deviation MISRA-2 */
      CONSTP2CONST(ComRxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr =
         COM_GET_CONFIG_ELEMENT(ComRxSignalType, Com_gConfigPtr->ComRxSignalRef, signalId);

      /* Signal based RxDM shall be started if
       * 1) Signal based RxDM is configured
       * 2) FirstTimeout != 0 and
       * 3) RxDM not started yet */

      if (COM_GET_RX_SIGNAL_DM(SignalPtr) == COM_RX_DM_ON)
      {

         Com_RxDMNextDueTimeType const TimeOutOffset =
#if (COM_RX_FIRST_TIMEOUT_FACTOR_SIZE == COM_SIZE_0_BIT)
               COM_GET_RX_SIGNAL_TIMEOUT_FACTOR(SignalPtr);
#else
               COM_GET_RX_SIGNAL_FIRST_TIMEOUT_FACTOR(SignalPtr);

         /* if ComRxFirstTimeoutFactor is zero start RxDM with first reception */
         if (0U != TimeOutOffset)
#endif /* (COM_RX_FIRST_TIMEOUT_FACTOR_SIZE == COM_SIZE_0_BIT) */
         {
            uint8 SigRxDMEnabled;

            CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) SigDMFlagsPtr =
                  COM_RX_SIGNAL_DM_FLAGS_BYTE_POS(SignalPtr);

            uint8 enableBitPos = (uint8)COM_RX_SIGNAL_DM_RUNNING_BIT_POS(SignalPtr);

            /* enter the critical section */
            Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

            TS_GetBit(SigDMFlagsPtr, enableBitPos, uint8, SigRxDMEnabled);

            /* do not re-start if already enabled  */
            if (SigRxDMEnabled == FALSE)
            {
               /* set enable bit */
               Com_SetBitUInt8(SigDMFlagsPtr, enableBitPos);

               /* start DM timer */
               Com_EB_RxDMSignalQueue(SignalPtr, TimeOutOffset);
            }                   /* if (SigRxDMEnabled == FALSE) */

            /* exit the critical section */
            Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();

         }                      /* if (0U != TimeOutOffset) */

      }                         /* if (COM_GET_RX_SIGNAL_DM(SignalPtr) == COM_RX_DM_ON) */

   }                            /* for (i = IPduPtr->ComIPduSignalRefFirst;
   i < (IPduPtr->ComIPduSignalWithDMOnly + IPduPtr->ComIPduSignalRefFirst); i++) */

   DBG_COM_EB_ENABLESIGNALBASEDDMFLAG_EXIT(IPduPtr);
   return;
}                               /* Com_EB_EnableSignalBasedDMFlag */


#if (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
/** \brief Com_EB_EnableSignalGroupBasedDMFlag - sets up signal group based DM
 * Preconditions:
 * - prior to this call, the COM module shall be initialized
 * \param[in] IPduPtr - configuration of the I-Pdu
 * \retval None
 */
TS_MOD_PRIV_DEFN FUNC(void, COM_CODE)Com_EB_EnableSignalGroupBasedDMFlag
(
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
)
{
   ComSignalGroupRefType j; /* iteration variable for signal group list*/
   DBG_COM_EB_ENABLESIGNALGROUPBASEDDMFLAG_ENTRY(IPduPtr);
   for (j = IPduPtr->ComIPduSignalGroupRefFirst;
   j < (IPduPtr->ComIPduSignalGroupRefNum + IPduPtr->ComIPduSignalGroupRefFirst); j++)
   {
      /* Get signal id and pointer to config of the signal in the signal list of the IPdu */
      /* Deviation MISRA-1, MISRA-2 <+7> */
      ComSignalGroupRefType const signalGId =
         (ComSignalGroupRefType) *
         (COM_GET_CONFIG_ELEMENT
          (ComSignalGroupRefType, Com_gConfigPtr->ComRxIPduSignalGroupListRef, j));

      /* Deviation MISRA-1 */
      /* Deviation MISRA-2 */
      CONSTP2CONST(ComRxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr =
         COM_GET_CONFIG_ELEMENT(ComRxSignalGroupType,
               Com_gConfigPtr->ComRxSignalGroupRef, signalGId);

      /* SignalGroup based RxDM shall be started if
       * 1) SignalGroup based RxDM is configured and
       * 2) FirstTimeout != 0 and
       * 3) not started yet */

      if (COM_GET_RX_SIGNAL_GROUP_DM(SignalGPtr) == COM_RX_DM_ON)
      {

         Com_RxDMNextDueTimeType const TimeOutOffset =
#if (COM_RX_FIRST_TIMEOUT_FACTOR_SIZE == COM_SIZE_0_BIT)
               COM_GET_RX_SIGNAL_GROUP_TIMEOUT_FACTOR(SignalGPtr);
#else
               COM_GET_RX_SIGNAL_GROUP_FIRST_TIMEOUT_FACTOR(SignalGPtr);

         /* if ComRxFirstTimeoutFactor is zero start RxDM with first reception */
         if (0U != TimeOutOffset)
#endif /* (COM_RX_FIRST_TIMEOUT_FACTOR_SIZE == COM_SIZE_0_BIT) */
         {
            uint8 SigGRxDMEnabled;

            CONSTP2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) SigGDMFlagsPtr =
                  COM_RX_SIGNAL_GROUP_DM_FLAGS_BYTE_POS(SignalGPtr);

            uint8 enableBitPos = (uint8)COM_RX_SIGNAL_GROUP_DM_RUNNING_BIT_POS(SignalGPtr);

            /* enter the critical section */
            Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

            TS_GetBit(SigGDMFlagsPtr, enableBitPos, uint8, SigGRxDMEnabled);

            /* do not re-start if already enabled  */
            if (SigGRxDMEnabled == FALSE)
            {

               /* set enable bit */
               Com_SetBitUInt8(SigGDMFlagsPtr, enableBitPos);

               /* start DM timer */
               Com_EB_RxDMSignalGroupQueue(SignalGPtr, TimeOutOffset);

            }                   /* if (SigGRxDMEnabled == FALSE) */

            /* exit the critical section */
            Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();

         }                      /* if (0U != TimeOutOffset) */

      }                         /*       if (COM_GET_RX_SIGNAL_GROUP_DM(SignalGPtr) == COM_RX_DM_ON) */

   }                            /* for (j = IPduPtr->ComIPduSignalGroupRefFirst;
   j < (IPduPtr->ComIPduSignalGroupRefNum + IPduPtr->ComIPduSignalGroupRefFirst); j++) */

   DBG_COM_EB_ENABLESIGNALGROUPBASEDDMFLAG_EXIT(IPduPtr);
   return;
}                               /* Com_EB_EnableSignalGroupBasedDMFlag */

#endif /* (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */



/** \brief Com_EB_DisableSignalAndSignalGroupBasedDMFlag - disables
 * signal(group) based DM
 * Preconditions:
 * - prior to this call, the COM module shall be initialized
 * \param[in] IPduPtr - configuration of the I-Pdu
 * \param[in] Initialize - defines if timeout flag shall be cleared
 * \retval None
 */
TS_MOD_PRIV_DEFN FUNC(void, COM_CODE)Com_EB_DisableSignalAndSignalGroupBasedDMFlag
(
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
   boolean Initialize
)
{
   ComSignalRefType i; /* iteration variable for signal list*/
#if (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
   ComSignalGroupRefType j; /* iteration variable for signal group list*/
#endif /* (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */
   DBG_COM_EB_DISABLESIGNALANDSIGNALGROUPBASEDDMFLAG_ENTRY(IPduPtr,Initialize);
   /* set up signal based DM */
   for (i = IPduPtr->ComIPduSignalRefFirst;
   i < (IPduPtr->ComIPduSignalWithDMOnly + IPduPtr->ComIPduSignalRefFirst); i++)
   {
      /* Get signal id and pointer to config of the signal in the signal list of the IPdu */
      /* Deviation MISRA-1, MISRA-2 <+7> */
      ComSignalRefType const signalId =
         (ComSignalRefType) *
         (COM_GET_CONFIG_ELEMENT
          (ComSignalRefType, Com_gConfigPtr->ComRxIPduSignalListRef, i));

      /* Deviation MISRA-1 */
      /* Deviation MISRA-2 */
      CONSTP2CONST(ComRxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr =
         COM_GET_CONFIG_ELEMENT(ComRxSignalType, Com_gConfigPtr->ComRxSignalRef, signalId);

      /* check if DM configured */
      if (COM_GET_RX_SIGNAL_DM(SignalPtr) == COM_RX_DM_ON)
      {
         /* Clear running bit */
         TS_AtomicClearBit_8(COM_RX_SIGNAL_DM_FLAGS_BYTE_POS(SignalPtr),
               COM_RX_SIGNAL_DM_RUNNING_BIT_POS(SignalPtr));

         /* clear timeout flag only when the I-Pdu is initialized */
         if (TRUE == Initialize)
         {
            /* Clear timed-out flag for of signal group DM */
            TS_AtomicClearBit_8(COM_RX_SIGNAL_DM_FLAGS_BYTE_POS(SignalPtr),
                  COM_RX_SIGNAL_DM_TIMEOUT_BIT_POS(SignalPtr));
         }

      }
   }                            /* for (i = IPduPtr->ComIPduSignalRefFirst;
   i < (IPduPtr->ComIPduSignalWithDMOnly + IPduPtr->ComIPduSignalRefFirst); i++) */

#if (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
   for (j = IPduPtr->ComIPduSignalGroupRefFirst;
   j < (IPduPtr->ComIPduSignalGroupRefNum + IPduPtr->ComIPduSignalGroupRefFirst); j++)
   {
      /* Get signal id and pointer to config of the signal in the signal list of the IPdu */
      /* Deviation MISRA-1, MISRA-2 <+7> */
      ComSignalGroupRefType const signalGId =
         (ComSignalGroupRefType) *
         (COM_GET_CONFIG_ELEMENT
          (ComSignalGroupRefType, Com_gConfigPtr->ComRxIPduSignalGroupListRef, j));

      /* Deviation MISRA-1 */
      /* Deviation MISRA-2 */
      CONSTP2CONST(ComRxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr =
         COM_GET_CONFIG_ELEMENT(ComRxSignalGroupType,
               Com_gConfigPtr->ComRxSignalGroupRef, signalGId);

      /* check if DM configured */
      if (COM_GET_RX_SIGNAL_GROUP_DM(SignalGPtr) == COM_RX_DM_ON)
      {
         /* set enable bit */
         TS_AtomicClearBit_8(COM_RX_SIGNAL_GROUP_DM_FLAGS_BYTE_POS(SignalGPtr),
               COM_RX_SIGNAL_GROUP_DM_RUNNING_BIT_POS(SignalGPtr));

         /* clear timeout flag only when the I-Pdu is initialized */
         if (TRUE == Initialize)
         {
            /* Clear timed-out flag for of signal group DM */
            TS_AtomicClearBit_8(COM_RX_SIGNAL_GROUP_DM_FLAGS_BYTE_POS(SignalGPtr),
                  COM_RX_SIGNAL_GROUP_DM_TIMEOUT_BIT_POS(SignalGPtr));
         }
      }
   }                            /* for (j = IPduPtr->ComIPduSignalGroupRefFirst;
   j < (IPduPtr->ComIPduSignalGroupRefNum + IPduPtr->ComIPduSignalGroupRefFirst); j++) */
#endif /* (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

   DBG_COM_EB_DISABLESIGNALANDSIGNALGROUPBASEDDMFLAG_EXIT(IPduPtr,Initialize);
}                               /* Com_EB_DisableSignalAndSignalGroupBasedDMFlag */
#endif /* (COM_RX_SIGNAL_BASED_DM == STD_ON) */



#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_STOP_SEC_CODE
#include <MemMap.h>
#endif

#endif /* (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) */

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/


