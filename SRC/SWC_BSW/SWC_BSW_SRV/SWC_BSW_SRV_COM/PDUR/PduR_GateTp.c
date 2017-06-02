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
#include <PduR_Types.h>           /* type definitions of PduR module */
#include <PduR_Internal_Static.h> /* Internal API (static part) */
#include <PduR_Api_Depend.h>      /* Public API (depend part) */

#if ((PDUR_ZERO_COST_OPERATION_TP == STD_OFF) && (PDUR_TPGATEWAY_SUPPORT == STD_ON))
/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/* AUTOSAR Memory Mapping - start section for code */
#if (TS_MERGED_COMPILE == STD_OFF)
#define PDUR_START_SEC_CODE
#include <MemMap.h>
#endif

TS_MOD_PRIV_DEFN FUNC(void, PDUR_CODE) PduR_ReleaseGateTpSession
(
   CONSTP2VAR(PduR_GateTpSessionInfoType, AUTOMATIC, PDUR_VAR_NOINIT) pSessionInfo
)
{
   DBG_PDUR_RELEASEGATETPSESSION_ENTRY(pSessionInfo);

   TS_AtomicAssign8(pSessionInfo->Status, (uint8)PDUR_GATETP_RST_STATUS_MSK);
   TS_AtomicAssign8(pSessionInfo->PendTxConfCount, (uint8)PDUR_GATETP_NO_PEND_TXCONF_MSK);
   pSessionInfo->RxWriteIndex = 0U;
   pSessionInfo->AvailableBufferSize = PDUR_TPBUFFER_LENGTH_ZERO;
   pSessionInfo->TpSduLength = PDUR_SDU_LENGTH_ZERO;

   DBG_PDUR_RELEASEGATETPSESSION_EXIT(pSessionInfo);
}


TS_MOD_PRIV_DEFN FUNC(void, PDUR_CODE) PduR_ReleaseGateTpQueue
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

   DBG_PDUR_RELEASEGATETPQUEUE_ENTRY(GMPduId);

   /* Restricted to single queue entry */
   pGateTpSessionIndex[PDUR_GATETPQUEUE_FIRSTINDEX] =  PDUR_NO_GATETP_SESSION_ASSIGNED;

   DBG_PDUR_RELEASEGATETPQUEUE_EXIT(GMPduId);
}


TS_MOD_PRIV_DEFN FUNC(PduR_GateTpSessionIndexType, PDUR_CODE) PduR_GetGateTpSessionInUse
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

   PduR_GateTpSessionIndexType SessionIndexRetVal;

   DBG_PDUR_GETGATETPSESSIONINUSE_ENTRY(GMPduId);

   SessionIndexRetVal = pGateTpSessionIndex[PDUR_GATETPQUEUE_FIRSTINDEX];

   DBG_PDUR_GETGATETPSESSIONINUSE_EXIT(SessionIndexRetVal, GMPduId);

   return SessionIndexRetVal;
}


TS_MOD_PRIV_DEFN FUNC(PduR_PduLengthType, PDUR_CODE) PduR_CalcAvailableDataSize
(
   PduR_GateTpSessionIndexType SessionIndex
)
{
   const PduR_BufTpIndexType BufTpIndex = (PduR_BufTpIndexType)SessionIndex;
   PduR_PduLengthType DataSize;

   /* pointer to TP gateway sessions */
   CONSTP2VAR(PduR_GateTpSessionInfoType, AUTOMATIC, PDUR_VAR_NOINIT) pGateTpSessions =
      PDUR_GET_RAM_ADDR(PduR_GateTpSessionInfoType, PduR_gConfigPtr->PduR_GateTpSessionInfoRef);

   /* pointer to TP buffer configurations */
   CONSTP2CONST(PduR_BufTpConfigType, AUTOMATIC, PDUR_APPL_CONST) pBufTpConfig =
      PDUR_GET_CONFIG_ADDR(PduR_BufTpConfigType, PduR_gConfigPtr->PduR_BufTpConfigRef);

   DBG_PDUR_CALCAVAILABLEDATASIZE_ENTRY(SessionIndex);

   DataSize = pBufTpConfig[BufTpIndex].Length - pGateTpSessions[SessionIndex].AvailableBufferSize

   DBG_PDUR_CALCAVAILABLEDATASIZE_EXIT(DataSize, SessionIndex);

   return DataSize;
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

/*==================[internal function definitions]=========================*/

#endif /* if (PDUR_ZERO_COST_OPERATION_TP == STD_OFF) && .. */
/*==================[end of file]===========================================*/
