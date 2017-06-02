/**
 * \file
 *
 * \brief AUTOSAR PduR
 *
 * This file contains the implementation of the AUTOSAR
 * module PduR.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]============================================*/

#include <PduR_Trace.h>
#include <TSAutosar.h>            /* EB specific standard types */
#include <TSAtomic_Assign.h>      /* Atomic assignments from Base PlugIn */
#include <ComStack_Types.h>       /* AUTOSAR Communication Stack types */
#include <PduR_Internal_Static.h> /* Internal API (static part) */
#include <PduR_Api_Depend.h>      /* Public API (depend part) */

#if ((PDUR_ZERO_COST_OPERATION_TP == STD_OFF) && (PDUR_TPGATEWAY_SUPPORT == STD_ON))
#include <PduR_Lcfg.h>            /* Link-time configurable data */
/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/* AUTOSAR Memory Mapping - start section for code */
#if (TS_MERGED_COMPILE == STD_OFF)
#define PDUR_START_SEC_CODE
#include <MemMap.h>
#endif

/**
 ** \brief Auxiliary TP gateway handler function
 **
 ** Auxiliary function that allocates a free TP gateway session.
 **
 **
 ** \param[in]  GMPduId             Identification of the received gateway PDU.
 ** \param[in]  TpSduLength         Total length of the PDU to be received.
 ** \param[out] SessionIndexUsed    SessionIndex of the selected TP gateway session.
 **                                 PDUR_NO_GATETP_SESSION_ASSIGNED if no one is free or
 **                                 already one is pending for GMPduId.
 **
 ** \return Result of TP gateway session request
 ** \retval BUFREQ_E_OVFL: No Buffer of the required length can be provided.
 **                        Either it is not configured of that size or temporary not available.
 ** \retval BUFREQ_OK: Otherwise.
 **/
STATIC FUNC(BufReq_ReturnType, PDUR_CODE) PduR_AssignGateTpSession
(
   PduR_PduIdType GMPduId,
   PduR_PduLengthType TpSduLength,
   P2VAR(PduR_GateTpSessionIndexType, AUTOMATIC, PDUR_APPL_DATA) SessionIndexUsed
);

/**
 ** \brief Auxiliary TP gateway handler function
 **
 ** Auxiliary function that determines the index of the first free position in the array
 ** of queued TP gateway sessions.
 **
 ** \param[in]  GMPduId             Identification of the received gateway PDU.
 **
 ** \return Index of the first free position in the array to queue the TP gateway session.
 **         PDUR_NO_GATETP_QUEUEING_POSSIBLE if TP gateway session for GMPduId can not be queued.
 **
 **/
STATIC FUNC(PduR_GateTpQueueIndexType, PDUR_CODE) PduR_GetFreeGateTpQueueIndex
(
   PduR_PduIdType GMPduId
);

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_GateTpStartOfReception
(
   PduIdType GMPduId,
   PduLengthType TpSduLength,
   P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) BufferSizePtr
)
{
   PduR_GateTpSessionIndexType SessionIndex;

   /* assign TP gateway session,
      no protection since this is the first call of the sequence of calls */
   BufReq_ReturnType RetVal = PduR_AssignGateTpSession(GMPduId, TpSduLength, &SessionIndex);

   DBG_PDUR_GATETPSTARTOFRECEPTION_ENTRY(GMPduId, TpSduLength, BufferSizePtr);

   /* free TP gateway session (TP buffer) assigned */
   if(SessionIndex != PDUR_NO_GATETP_SESSION_ASSIGNED)
   {
      /* pointer to TP buffer configurations */
      CONSTP2CONST(PduR_BufTpConfigType, AUTOMATIC, PDUR_APPL_CONST) pBufTpConfig =
         PDUR_GET_CONFIG_ADDR(PduR_BufTpConfigType, PduR_gConfigPtr->PduR_BufTpConfigRef);

      *BufferSizePtr = pBufTpConfig[SessionIndex].Length;
   }
   /* else: no TP buffer of that size configured, temporary not available or
      already ongoing TP gateway session.
      RetVal = BUFREQ_E_OVFL, BufferSize shall remain unchanged */

   DBG_PDUR_GATETPSTARTOFRECEPTION_EXIT(RetVal, GMPduId, TpSduLength, BufferSizePtr);

   return RetVal;
}


/*==================[internal function definitions]=========================*/

STATIC FUNC(BufReq_ReturnType, PDUR_CODE) PduR_AssignGateTpSession
(
   PduR_PduIdType GMPduId,
   PduR_PduLengthType TpSduLength,
   P2VAR(PduR_GateTpSessionIndexType, AUTOMATIC, PDUR_APPL_DATA) SessionIndexUsed
)
{
   PduR_BufTpIndexType  BufTpIndex = 0U;

   /* initialize with value showing that no TP buffer is assigned */
   BufReq_ReturnType RetVal = BUFREQ_E_OVFL;

   /* pointer to TP buffer configurations */
   CONSTP2CONST(PduR_BufTpConfigType, AUTOMATIC, PDUR_APPL_CONST) pBufTpConfig =
      PDUR_GET_CONFIG_ADDR(PduR_BufTpConfigType, PduR_gConfigPtr->PduR_BufTpConfigRef);

   /* pointer to routing table */
   CONSTP2CONST(PduR_GTabTpRxType, AUTOMATIC, PDUR_APPL_CONST) pGTabTpRx =
      PDUR_GET_CONFIG_ADDR(PduR_GTabTpRxType, PduR_gConfigPtr->PduR_GTabTpConfig.GTabRxRef);

   /* initial session index, empty element in queue */
   PduR_GateTpSessionIndexType SessionIndex = PDUR_NO_GATETP_SESSION_ASSIGNED;

   /* pointer to TP gateway sessions */
   CONSTP2VAR(PduR_GateTpSessionInfoType, AUTOMATIC, PDUR_VAR_NOINIT) pSessionInfos =
      PDUR_GET_RAM_ADDR(PduR_GateTpSessionInfoType, PduR_gConfigPtr->PduR_GateTpSessionInfoRef);

   PduR_PduLengthType BufTpThreshold;

   PduR_GateTpQueueIndexType QueueIndex = PduR_GetFreeGateTpQueueIndex(GMPduId);

   DBG_PDUR_ASSIGNGATETPSESSION_ENTRY(GMPduId, TpSduLength, SessionIndexUsed);

   /* GMPduId can be queued */
   if(QueueIndex != PDUR_NO_GATETP_QUEUEING_POSSIBLE)
   {
      /* TP buffer threshold for direct routing (no TpThreshold configured) */
      if(pGTabTpRx[GMPduId].TpThreshold == PDUR_GATETPTHRESHOLD_DIRECT)
      {
         BufTpThreshold = TpSduLength;
      }
      /* TP buffer threshold for routing on the fly (TpThreshold configured) */
      else
      {
         BufTpThreshold = pGTabTpRx[GMPduId].TpThreshold;
      }

      /* search for free TP buffer */
      /* determine TP buffer of maximum size */
      if(TpSduLength == PDUR_SDU_LENGTH_ZERO)
      {
         /* initially set to allow first while loop */
         uint8 ResultGetBitOccupiedSession;

         /* search for TP buffer in descending order */
         SessionIndex = (PduR_GateTpSessionIndexType)PduR_gConfigPtr->PduR_BufTpCount;

         /* search for free TP gateway session */
         do{
            /* loop is left if free TP gateway session is detected. */
            SessionIndex--;

            /* check if TP gateway session is occupied */
            TS_GetBit(&pSessionInfos[SessionIndex].Status, PDUR_GATETP_OCCUPIED_SES_POS,
                      uint8, ResultGetBitOccupiedSession);

         }while((SessionIndex > 0U) &&
                (ResultGetBitOccupiedSession > 0U) &&
                (BufTpThreshold <= pBufTpConfig[SessionIndex - 1U].Length));

         /* no free TP gateway session detected or not applicable */
         if((ResultGetBitOccupiedSession > 0U) ||
            (BufTpThreshold > pBufTpConfig[SessionIndex].Length))
         {
            SessionIndex = PDUR_NO_GATETP_SESSION_ASSIGNED;
         }
      }
      /*  No TP buffer of the required length can be provided */
      else if(BufTpThreshold > pBufTpConfig[PduR_gConfigPtr->PduR_BufTpCount - 1U].Length)
      {
        /* RetVal from initialization BUFREQ_E_OVFL is returned */
      }
      /* determine free TP buffer next to TpSduLength - direct routing (no TpThreshold configured)
         or TP buffer next to TpThreshold - routing on the fly (TpThreshold configured) */
      else
      {
         uint8 ResultGetBitOccupiedSession;

         /* search for first suitable TP buffer in ascending order */
         while((BufTpIndex < PduR_gConfigPtr->PduR_BufTpCount) &&
               (BufTpThreshold > pBufTpConfig[BufTpIndex].Length))
         {
            /* loop is left if first valid TP buffer size is detected. */
            BufTpIndex++;
         }

         SessionIndex = BufTpIndex;

         /* search for free TP gateway session */
         do{
            /* check if session is occupied */
            TS_GetBit(&pSessionInfos[SessionIndex].Status, PDUR_GATETP_OCCUPIED_SES_POS,
                      uint8, ResultGetBitOccupiedSession);

            /* loop is left if free TP gateway session is detected.
               If its not detected, the final SessionIndex
               holds the value of PduR_gConfigPtr->PduR_BufTpCount. */
            SessionIndex++;

         }while((SessionIndex < PduR_gConfigPtr->PduR_BufTpCount) &&
                (ResultGetBitOccupiedSession > 0U));

         /* no proper TP gateway session detected */
         if(ResultGetBitOccupiedSession > 0U)
         {
            SessionIndex = PDUR_NO_GATETP_SESSION_ASSIGNED;
         }
         else
         {
            /* correction from do-while loop */
            SessionIndex--;
         }
      }
   }

   /* assign TP gateway session and queue at proper position */
   if(SessionIndex != PDUR_NO_GATETP_SESSION_ASSIGNED)
   {
      /* pointer to queued TP gateway sessions */
      CONSTP2VAR(PduR_GateTpSessionIndexType, AUTOMATIC, PDUR_VAR_NOINIT) pGateTpSessionIndex =
         PDUR_GET_RAM_ADDR(PduR_GateTpSessionIndexType, pGTabTpRx[GMPduId].SessionQueueMemRef);

      /* both are identical if valid TP gateway session detected */
      BufTpIndex = (PduR_BufTpIndexType)SessionIndex;

      /* provide entry to queued gateway sessions */
      pGateTpSessionIndex[QueueIndex] = SessionIndex;

      /* occupy TP gateway session and initialize */
      TS_AtomicAssign8(pSessionInfos[SessionIndex].Status, (uint8)PDUR_GATETP_RST_STATUS_MSK);
      TS_AtomicSetBit_8(&pSessionInfos[SessionIndex].Status, PDUR_GATETP_OCCUPIED_SES_POS);
      TS_AtomicAssign8(pSessionInfos[SessionIndex].PendTxConfCount,
                       (uint8)PDUR_GATETP_NO_PEND_TXCONF_MSK);
      pSessionInfos[SessionIndex].TpSduLength = TpSduLength;
      pSessionInfos[SessionIndex].RxWriteIndex = 0U;
      pSessionInfos[SessionIndex].AvailableBufferSize = pBufTpConfig[BufTpIndex].Length;

      /* if a TP gateway session is assigned also a TP buffer is assigned and vice versa */
      RetVal = BUFREQ_OK;
   }

   *SessionIndexUsed = SessionIndex;

   DBG_PDUR_ASSIGNGATETPSESSION_EXIT(RetVal, GMPduId, TpSduLength, SessionIndexUsed);

   return RetVal;
}


STATIC FUNC(PduR_GateTpQueueIndexType, PDUR_CODE) PduR_GetFreeGateTpQueueIndex
(
   PduR_PduIdType GMPduId
)
{
   /* pointer to routing table */
   CONSTP2CONST(PduR_GTabTpRxType, AUTOMATIC, PDUR_APPL_CONST) pGTabTpRx =
      PDUR_GET_CONFIG_ADDR(PduR_GTabTpRxType, PduR_gConfigPtr->PduR_GTabTpConfig.GTabRxRef);

   /* pointer to queued TP gateway sessions */
   CONSTP2VAR(PduR_GateTpSessionIndexType, AUTOMATIC, PDUR_VAR_NOINIT) pGateTpSessionIndex =
      PDUR_GET_RAM_ADDR(PduR_GateTpSessionIndexType, pGTabTpRx[GMPduId].SessionQueueMemRef);

   PduR_GateTpQueueIndexType QueueIndex = PDUR_GATETPQUEUE_FIRSTINDEX;

   DBG_PDUR_GETFREEGATETPQUEUEINDEX_ENTRY(GMPduId);

   /* Restricted to single queue entry */
   if(pGateTpSessionIndex[PDUR_GATETPQUEUE_FIRSTINDEX] != PDUR_NO_GATETP_SESSION_ASSIGNED)
   {
      QueueIndex = PDUR_NO_GATETP_QUEUEING_POSSIBLE;
   }

   DBG_PDUR_GETFREEGATETPQUEUEINDEX_EXIT(QueueIndex, GMPduId);

   return QueueIndex;
}


/* AUTOSAR Memory Mapping - end section for code */
#if (TS_MERGED_COMPILE == STD_OFF)
#define PDUR_STOP_SEC_CODE
#include <MemMap.h>
#endif

#else /* if (PDUR_ZERO_COST_OPERATION_TP == STD_OFF) && .. */

#include <TSCompiler.h>           /* usage of macro in TSCompiler_Default.h */

/* Avoid empty translation unit according to ISO C90 */
TS_PREVENTEMPTYTRANSLATIONUNIT

#endif /* if (PDUR_ZERO_COST_OPERATION_TP == STD_OFF) && .. */
/*==================[end of file]===========================================*/
