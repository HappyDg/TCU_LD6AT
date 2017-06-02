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
 */

/*==================[inclusions]=============================================*/

#include <Com_Trace.h>
#include <TSAutosar.h>          /* EB specific standard types */
#include <ComStack_Types.h>     /* AUTOSAR standard types */
#include <Com_Api_Static.h>     /* module public static API */
#include <Com_Priv.h>           /* module internal stuff */

#include <Com_Core_RxIPdu.h>    /* Header TxIPdu functions */


#if (COM_RX_SIGNAL_BASED_DM == STD_ON)
#include <Com_Core_RxUpdateBit.h> /* UpdateBit Functions */
#endif /* (COM_RX_SIGNAL_BASED_DM == STD_ON) */


/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_START_SEC_CODE
#include <MemMap.h>
#endif

#if (COM_RX_TIMEOUT_FACTOR_AVAILABLE == STD_ON)
_COM_STATIC_ FUNC(void, COM_CODE)Com_EB_CheckRxDMTable
(
   void
);
#endif /* (COM_RX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) */

#if (COM_RX_SIGNAL_BASED_DM == STD_ON)

_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_CheckRxSignalDMTable
(
   void
);
#endif /* (COM_RX_SIGNAL_BASED_DM == STD_ON) */

#if (COM_RX_SIGNAL_BASED_DM == STD_ON)
#if (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)

_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_CheckRxSignalGroupDMTable
(
   void
);
#endif /* (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */
#endif /* (COM_RX_SIGNAL_BASED_DM == STD_ON) */

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



#if (COM_RX_TIMEOUT_FACTOR_AVAILABLE == STD_ON)

_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_CheckRxDMTable
(
   void
)
{
   /* variable to hold global time in data type of Com_RxDMNextDueTimeType */
   Com_RxDMNextDueTimeType globalTime;
   Com_RxDMNextDueTimeType CompTime;
   ComIPduRefType i;       /* iterator variable */

   DBG_COM_EB_CHECKRXDMTABLE_ENTRY();


   /* no critical section needed here, the only Com_GlobalTime is update only in
    * context of Com_MainfunctionRx() and this function is also only invoked in context of
    * Com_MainfunctionRx() */
   globalTime = (Com_RxDMNextDueTimeType) Com_GlobalTime;

   for (i = 0; i < Com_gConfigPtr->ComRxTimeoutQueueMax; i++)
   {
      uint8 BitRes;
      boolean invokeCbks = FALSE;

      P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr;
      CONSTP2VAR(Com_RxDMNextDueTimeType, AUTOMATIC, COM_VAR_NOINIT) RxTimeoutQueueBase =
            COM_GET_MEMPTR(Com_RxDMNextDueTimeType, Com_gConfigPtr->ComRxTimeoutQueueBase);

      ComIPduRefType AktPduId;    /* temporary PDU-Id variable */
      /* fetch the PDU id of the actual entry */
      /* Deviation MISRA-1 */
      /* Deviation MISRA-2 */
      AktPduId =
            (ComIPduRefType) *
            (COM_GET_CONFIG_ELEMENT(ComIPduRefType, (Com_gConfigPtr->ComRxTimeoutQueueListRef), i));

      /* Deviation MISRA-1 */
      /* Deviation MISRA-2 */
      IPduPtr = COM_GET_CONFIG_ELEMENT(ComRxIPduType, Com_gConfigPtr->ComRxIPduRef, AktPduId);

      /* Critical section; Com_TS_RxDMQueue may interrupt the
       * function at the wrong time; clearing of RXDMTIMEOUT may be lost */
      Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

      /* This entry may have timed out, if it had RxDM enabled */
      TS_GetBit(&Com_gDataMemPtr[(Com_gConfigPtr->ComRxIPduStatusBase + AktPduId)],
            COM_RXPDU_RXDMRUNNING, uint8, BitRes);

      if (BitRes == TRUE)
      {
         /* get the time out */
         CompTime = RxTimeoutQueueBase[i];
         if (globalTime == CompTime)
         {

            /* Entry times out right now */
            Com_SetBitUInt8(&Com_gDataMemPtr[(Com_gConfigPtr->ComRxIPduStatusBase + AktPduId)],
                  COM_RXPDU_RXDMTIMEOUT);

            /* Restart RxDM at once */
            Com_EB_RxDMQueue(IPduPtr, COM_GET_RX_TIMEOUT_FACTOR(IPduPtr));

            /* call callbacks outside critical section */
            invokeCbks = TRUE;

         }                   /* if (globalTime == CompTime) */
      }                      /* if (BitRes == TRUE) */

      /* LEAVE CRITICAL SECTION */
      Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();

      if (TRUE == invokeCbks)
      {
         Com_CbkRxTOutIdxType j;  /* iterator variable */

         /* send timeout notifications */
         for (j = IPduPtr->ComRxTimeoutNotificationFirst;
               j < (IPduPtr->ComRxTimeoutNotificationFirst
                     + IPduPtr->ComRxTimeoutNotificationNum); j++)
         {
            /* call timeout notification */
            /* Deviation MISRA-1 */
            /* Deviation MISRA-2 */
            Com_CbkRxTOut_Array[COM_GET_CBK_RX_T_OUT_IDX(j)] ();
         }

      }                      /* if (TRUE == invokeCbks) */
   }                         /* for (i = 0; i < Com_gConfigPtr->ComRxTimeoutQueueMax; i++) */

   DBG_COM_EB_CHECKRXDMTABLE_EXIT();
   return;
}                               /* Com_EB_CheckRxDMTable */
#endif /* (COM_RX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) */


#if (COM_RX_SIGNAL_BASED_DM == STD_ON)

_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_CheckRxSignalDMTable
(
   void
)
{
   /* variable to hold global time in data type of Com_RxDMNextDueTimeType */
   Com_RxDMNextDueTimeType globalTime;
   Com_RxDMNextDueTimeType CompTime;
   ComSignalRefType i;       /* iterator variable */

   DBG_COM_EB_CHECKRXSIGNALDMTABLE_ENTRY();

   /* no critical section needed here, the only Com_GlobalTime is update only in
    * context of Com_MainfunctionRx() and this function is also only invoked in context of
    * Com_MainfunctionRx() */
   globalTime = (Com_RxDMNextDueTimeType) Com_GlobalTime;


      for (i = 0; i < Com_gConfigPtr->ComRxTimeoutSignalQueueMax; i++)
      {
         uint8 BitRes;
         boolean invokeCbks = FALSE;

         /* reference to configuration of the signal */
         P2CONST(ComRxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr;
         CONSTP2VAR(Com_RxDMNextDueTimeType, AUTOMATIC, COM_VAR_NOINIT) RxTimeoutSignalQueueBase =
             COM_GET_MEMPTR(Com_RxDMNextDueTimeType, Com_gConfigPtr->ComRxTimeoutSignalQueueBase);

         ComSignalRefType AktSignalId;    /* temporary signal-Id variable */
         /* fetch the PDU id of the actual entry */
         /* Deviation MISRA-1 */
         /* Deviation MISRA-2 */
         AktSignalId =
            (ComSignalRefType) *(COM_GET_CONFIG_ELEMENT(ComSignalRefType,
                  (Com_gConfigPtr->ComRxTimeoutSignalQueueListRef), i));

         /* Deviation MISRA-1 */
         /* Deviation MISRA-2 */
         SignalPtr = COM_GET_CONFIG_ELEMENT(ComRxSignalType,
               Com_gConfigPtr->ComRxSignalRef, AktSignalId);

         /* Critical section; Com_TS_RxDMQueue may interrupt the
          * function at the wrong time; clearing of RXDMTIMEOUT may be lost */
         Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

         /* This entry may have timed out, if it had RxDM enabled */
         TS_GetBit(COM_RX_SIGNAL_DM_FLAGS_BYTE_POS(SignalPtr),
               COM_RX_SIGNAL_DM_RUNNING_BIT_POS(SignalPtr), uint8, BitRes);

         if (BitRes == TRUE)
         {
            /* get the time out */
            CompTime = RxTimeoutSignalQueueBase[i];
            if (globalTime == CompTime)
            {

               /* Entry times out right now */
               TS_AtomicSetBit_8(COM_RX_SIGNAL_DM_FLAGS_BYTE_POS(SignalPtr),
                     COM_RX_SIGNAL_DM_TIMEOUT_BIT_POS(SignalPtr));

               /* Restart RxDM at once */
               Com_EB_RxDMSignalQueue(SignalPtr, COM_GET_RX_SIGNAL_TIMEOUT_FACTOR(SignalPtr));

               /* call callbacks outside critical section */
               invokeCbks = TRUE;

            }                   /* if (globalTime == CompTime) */
         }                      /* if (BitRes == TRUE) */

         /* LEAVE CRITICAL SECTION */
         Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();

         if (TRUE == invokeCbks)
         {
            /* check if a callback is configured */
            if (SignalPtr->ComRxTimeoutNotification != COM_CBK_RX_T_OUT_IDX_FUNC_PTR_NULL)
            {
               /* call timeout notification */
               Com_CbkRxTOut_Array[SignalPtr->ComRxTimeoutNotification] ();
            }
         }                      /* if (TRUE == invokeCbks) */
      }                         /* for (i = 0; i < Com_gConfigPtr->ComRxTimeoutSignalQueueMax; i++) */

   DBG_COM_EB_CHECKRXSIGNALDMTABLE_EXIT();
   return;
}                               /* Com_EB_CheckRxSignalDMTable */
#endif /* (COM_RX_SIGNAL_BASED_DM == STD_ON) */

#if (COM_RX_SIGNAL_BASED_DM == STD_ON)
#if (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_CheckRxSignalGroupDMTable
(
   void
)
{
   /* variable to hold global time in data type of Com_RxDMNextDueTimeType */
   Com_RxDMNextDueTimeType globalTime;
   Com_RxDMNextDueTimeType CompTime;
   ComSignalGroupRefType i;       /* iterator variable */

   DBG_COM_EB_CHECKRXSIGNALGROUPDMTABLE_ENTRY();

   /* no critical section needed here, the only Com_GlobalTime is update only in
    * context of Com_MainfunctionRx() and this function is also only invoked in context of
    * Com_MainfunctionRx() */
   globalTime = (Com_RxDMNextDueTimeType) Com_GlobalTime;

   for (i = 0; i < Com_gConfigPtr->ComRxTimeoutSignalGroupQueueMax; i++)
   {
      uint8 BitRes;
      boolean invokeCbks = FALSE;

      /* reference to configuration of the signal */
      P2CONST(ComRxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr;
      CONSTP2VAR(Com_RxDMNextDueTimeType, AUTOMATIC, COM_VAR_NOINIT)
      RxTimeoutSignalGroupQueueBase =
            COM_GET_MEMPTR(Com_RxDMNextDueTimeType,
                  Com_gConfigPtr->ComRxTimeoutSignalGroupQueueBase);

      ComSignalGroupRefType AktSignalGId;    /* temporary signal-Id variable */
      /* fetch the PDU id of the actual entry */
      /* Deviation MISRA-1 */
      /* Deviation MISRA-2 */
      AktSignalGId =
            (ComSignalGroupRefType) *(COM_GET_CONFIG_ELEMENT(ComSignalGroupRefType,
                  (Com_gConfigPtr->ComRxTimeoutSignalGroupQueueListRef), i));

      /* Deviation MISRA-1 */
      /* Deviation MISRA-2 */
      SignalGPtr = COM_GET_CONFIG_ELEMENT(ComRxSignalGroupType,
            Com_gConfigPtr->ComRxSignalGroupRef, AktSignalGId);

      /* Critical section; Com_TS_RxDMQueue may interrupt the
       * function at the wrong time; clearing of RXDMTIMEOUT may be lost */
      Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

      /* This entry may have timed out, if it had RxDM enabled */
      TS_GetBit(COM_RX_SIGNAL_GROUP_DM_FLAGS_BYTE_POS(SignalGPtr),
            COM_RX_SIGNAL_GROUP_DM_RUNNING_BIT_POS(SignalGPtr), uint8, BitRes);

      if (BitRes == TRUE)
      {
         /* get the time out */
         CompTime = RxTimeoutSignalGroupQueueBase[i];
         if (globalTime == CompTime)
         {

            /* Entry times out right now */
            TS_AtomicSetBit_8(COM_RX_SIGNAL_GROUP_DM_FLAGS_BYTE_POS(SignalGPtr),
                  COM_RX_SIGNAL_GROUP_DM_TIMEOUT_BIT_POS(SignalGPtr));

            /* Restart RxDM at once */
            Com_EB_RxDMSignalGroupQueue(
                  SignalGPtr,
                  COM_GET_RX_SIGNAL_GROUP_TIMEOUT_FACTOR(SignalGPtr));

            /* call callbacks outside critical section */
            invokeCbks = TRUE;

         }                   /* if (globalTime == CompTime) */

      }                      /* if (BitRes == TRUE) */

      /* LEAVE CRITICAL SECTION */
      Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();

      if (TRUE == invokeCbks)
      {
         /* check if a callback is configured */
         if (SignalGPtr->ComRxTimeoutNotification != COM_CBK_RX_T_OUT_IDX_FUNC_PTR_NULL)
         {
            /* call timeout notification */
            Com_CbkRxTOut_Array[SignalGPtr->ComRxTimeoutNotification] ();
         }
      }                      /* if (TRUE == invokeCbks) */
   }                         /* for (i = 0; i < Com_gConfigPtr->ComRxTimeoutSignalGroupQueueMax; i++) */
   DBG_COM_EB_CHECKRXSIGNALGROUPDMTABLE_EXIT();
   return;
}                               /* Com_EB_CheckRxSignalGroupDMTable */

#endif /* (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */
#endif /* (COM_RX_SIGNAL_BASED_DM == STD_ON) */


/** \brief Com_MainFunctionTx - handle cyclic sending-related tasks
 * This function handles cyclic sending-related tasks such as minimum delay
 * time and cyclic sending.
 * Preconditions:
 * - COM must be initialized
 * \param[in] None
 * \retval None
 */

FUNC(void, COM_CODE) Com_MainFunctionRx
(
   void
)
{


DBG_COM_MAINFUNCTIONRX_ENTRY();
   if (Com_InitStatus == COM_EB_INIT)
   {

#if (COM_GLOBAL_TIME != COM_SIZE_0_BIT)
      /* Make the time tick */
      Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();
      Com_GlobalTime += 1;
      Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();
#endif /* (COM_GLOBAL_TIME != COM_SIZE_0_BIT) */

#if (COM_RX_TIMEOUT_FACTOR_AVAILABLE == STD_ON)
      /* See if Rx DM timed out */
      Com_EB_CheckRxDMTable();
#endif /* (COM_RX_TIMEOUT_FACTOR_AVAILABLE == STD_ON) */


#if (COM_RX_SIGNAL_BASED_DM == STD_ON)
      /* check if signal based Rx DM timed out */
      Com_EB_CheckRxSignalDMTable();

#if (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
      /* check if signal group based DM timed out */
      Com_EB_CheckRxSignalGroupDMTable();
#endif /* (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

#endif /* (COM_RX_SIGNAL_BASED_DM == STD_ON) */


#if (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON)
#if (COM_NOTIFY_RECEIVERS_ENABLE == STD_ON)
      {
         uint16 i;
         uint8 BitRes;
         uint16 RxPduCount = Com_gConfigPtr->ComRxIPduArraySize;

         for (i = 0; i < RxPduCount; i++)
         {
            TS_GetBit(&Com_gDataMemPtr[(Com_gConfigPtr->ComRxIPduStatusBase + i)],
                      COM_RXPDU_RXDEFNOTIFY, uint8, BitRes);
            if (BitRes == TRUE)
            {
               P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr;
               TS_AtomicClearBit_8(&Com_gDataMemPtr[(Com_gConfigPtr->ComRxIPduStatusBase + i)],
                                 COM_RXPDU_RXDEFNOTIFY);

               /* Notify receivers (deferred) */
               /* Deviation MISRA-1 */
               /* Deviation MISRA-2 */
               IPduPtr = COM_GET_CONFIG_ELEMENT(ComRxIPduType, Com_gConfigPtr->ComRxIPduRef, i);
               Com_EB_NotifyReceivers(IPduPtr);
            }
         }
      }
#endif /* (COM_NOTIFY_RECEIVERS_ENABLE == STD_ON) */
#endif /* (COM_RX_SIG_CONF_DEFERRED_ENABLE == STD_ON) */


   }                            /* if (Com_Status == COM_EB_INIT) */

   DBG_COM_MAINFUNCTIONRX_EXIT();
   return;
}

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_STOP_SEC_CODE
#include <MemMap.h>
#endif

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/
