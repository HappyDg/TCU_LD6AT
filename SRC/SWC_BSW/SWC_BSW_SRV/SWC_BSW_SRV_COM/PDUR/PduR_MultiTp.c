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
#include <TSCompiler.h>           /* usage of macro in TSCompiler_Default.h */
#include <ComStack_Types.h>       /* AUTOSAR Communication Stack types */
#include <PduR_Internal_Static.h> /* Internal API (static part) */
#include <PduR_Api_Depend.h>      /* Public API (depend part) */

#if (PDUR_ZERO_COST_OPERATION_TP == STD_OFF)
/* Attention: avoid double inclusion of SchM_PduR.h in PduR_Merged.c by proper
 * selection of the pre-compile switches */
#if (PDUR_MULTICAST_UPTOLOTP_SUPPORT == STD_ON)
#include <SchM_PduR.h>            /* Schedule Manager for module PduR */
#include <PduR_Lcfg.h>            /* Link-time configurable data */

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

TS_MOD_PRIV_DEFN FUNC(uint8, PDUR_CODE) PduR_SearchMultiTpTxSessionIndex
(
   PduR_PduIdType MTpTxPduId
)
{
   /* loop index */
   uint8_least LoopIdx = 0U;

   /* initialize return value */
   uint8 RetValSessionIndex = PDUR_NO_MULTITP_SESSION_ASSIGNED;

   /* pointer to multicast transmit sessions */
   CONSTP2VAR(PduR_MultiTpTxSessionInfoType, AUTOMATIC, PDUR_VAR_NOINIT) pMultiTpTxSessionInfo =
      PDUR_GET_RAM_ADDR(PduR_MultiTpTxSessionInfoType, PduR_gConfigPtr->PduR_MultiTpTxSessionInfoRef);

   DBG_PDUR_SEARCHMULTITPTXSESSIONINDEX_ENTRY(MTpTxPduId);

   /* search for multicast transmit session in use */
   while((LoopIdx < PduR_gConfigPtr->PduR_MultiTpTxRPathsMax) &&
         (pMultiTpTxSessionInfo[LoopIdx].MTpTxPduId != MTpTxPduId))
   {
      /* loop is left if assigned multicast transmit session of considered PduId is detected.
         If it is not detected, LoopIdx holds the value of PduR_gConfigPtr->PduR_MultiTpTxRPathsMax */
      LoopIdx++;
   }

   /* multicast transmit session detected */
   if(LoopIdx < PduR_gConfigPtr->PduR_MultiTpTxRPathsMax)
   {
      /* update return value to detected multicast transmit session index */
      RetValSessionIndex = (uint8)LoopIdx;
   }

   DBG_PDUR_SEARCHMULTITPTXSESSIONINDEX_EXIT(RetValSessionIndex, MTpTxPduId);

   return RetValSessionIndex;
}


TS_MOD_PRIV_DEFN FUNC(void, PDUR_CODE) PduR_ReleaseMultiTpTxSession
(
   uint8 SessionIndex
)
{
   /* pointer to multicast transmit sessions */
   CONSTP2VAR(PduR_MultiTpTxSessionInfoType, AUTOMATIC, PDUR_VAR_NOINIT) pMultiTpTxSessionInfo =
     PDUR_GET_RAM_ADDR(PduR_MultiTpTxSessionInfoType, PduR_gConfigPtr->PduR_MultiTpTxSessionInfoRef);

   DBG_PDUR_RELEASEMULTITPTXSESSION_ENTRY(SessionIndex);

   /* reset Status */
   TS_AtomicAssign8(pMultiTpTxSessionInfo[SessionIndex].Status,
      (uint8)PDUR_MULTITPTX_RESET_STATUS_VAL);

   /* reset multicast PduId */
   pMultiTpTxSessionInfo[SessionIndex].MTpTxPduId = (PduR_PduIdType)PDUR_INVALID_PDUID;

   /* reset SduLength */
   pMultiTpTxSessionInfo[SessionIndex].SduLength = PDUR_SDU_LENGTH_ZERO;

   /* reset parameter Result of TpTxConfirmation */
   pMultiTpTxSessionInfo[SessionIndex].ResultTxConf = NTFRSLT_OK;

   DBG_PDUR_RELEASEMULTITPTXSESSION_EXIT(SessionIndex);
}

/* AUTOSAR Memory Mapping - end section for code */
#if (TS_MERGED_COMPILE == STD_OFF)
#define PDUR_STOP_SEC_CODE
#include <MemMap.h>
#endif

/*==================[internal function definitions]=========================*/
#endif /* (PDUR_MULTICAST_UPTOLOTP_SUPPORT == STD_ON) */
#endif /* if (PDUR_ZERO_COST_OPERATION_TP == STD_OFF) */

/* Avoid empty translation unit according to ISO C90 */
TS_PREVENTEMPTYTRANSLATIONUNIT

/*==================[end of file]===========================================*/
