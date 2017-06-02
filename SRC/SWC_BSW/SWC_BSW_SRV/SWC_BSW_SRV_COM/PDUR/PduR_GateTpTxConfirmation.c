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
#include <ComStack_Types.h>       /* AUTOSAR Communication Stack types */
#include <PduR_Internal_Static.h> /* Internal API (static part) */
#include <PduR_Api_Depend.h>      /* Public API (depend part) */

#if ((PDUR_ZERO_COST_OPERATION_TP == STD_OFF) && (PDUR_TPGATEWAY_SUPPORT == STD_ON))
#include <SchM_PduR.h>            /* Schedule Manager for module PduR */

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

FUNC(void, PDUR_CODE) PduR_GateTpTxConfirmation
(
   PduIdType GMPduId,
   NotifResultType Result
)
{
   PduR_GateTpSessionIndexType SessionIndex;

#if (PDUR_DEV_ERROR_DETECT == STD_ON)
   boolean CallDetReportError = FALSE;
   uint8 DetErrorCode = PDUR_E_INVALID_REQUEST;
#endif /* if (PDUR_DEV_ERROR_DETECT == STD_ON) */

   DBG_PDUR_GATETPTXCONFIRMATION_ENTRY(GMPduId, Result);

   /* ENTER CRITICAL SECTION */
   SchM_Enter_PduR_SCHM_PDUR_EXCLUSIVE_AREA_0();

   /* get TP gateway session in use */
   SessionIndex = PduR_GetGateTpSessionInUse(GMPduId);

   /* TpTxConfirmation called without preceding StartOfReception */
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
   if(SessionIndex == PDUR_NO_GATETP_SESSION_ASSIGNED)
   {
      CallDetReportError = TRUE;
      DetErrorCode = PDUR_E_INVALID_REQUEST;
   }
   else
#endif /* if (PDUR_DEV_ERROR_DETECT == STD_ON) */
   {
      /* pointer to TP gateway sessions */
      CONSTP2VAR(PduR_GateTpSessionInfoType, AUTOMATIC, PDUR_VAR_NOINIT) pSessionInfos =
         PDUR_GET_RAM_ADDR(PduR_GateTpSessionInfoType, PduR_gConfigPtr->PduR_GateTpSessionInfoRef);

      uint8 ResultGetBitReceptFin;

      pSessionInfos[SessionIndex].PendTxConfCount--;

      if(Result != NTFRSLT_OK)
      {
         /* abort transmission */
         TS_AtomicSetBit_8(&pSessionInfos[SessionIndex].Status, PDUR_GATETP_ABORT_POS);
      }

      /* last TpTxConfirmation without pending reception */
      TS_GetBit(&pSessionInfos[SessionIndex].Status, PDUR_GATETP_RECEPT_FIN_POS, uint8,
                ResultGetBitReceptFin);
      if((pSessionInfos[SessionIndex].PendTxConfCount == 0U) &&
         (ResultGetBitReceptFin > 0U))
      {
         /* release TP gateway session for final call of TpTxConfirmation */
         PduR_ReleaseGateTpSession(&pSessionInfos[SessionIndex]);

         /* release assigned Tp gateway queue */
         PduR_ReleaseGateTpQueue(GMPduId);
      }
   } /* (SessionIndex != PDUR_NO_GATETP_SESSION_ASSIGNED) */

   /* EXIT CRITICAL SECTION */
   SchM_Exit_PduR_SCHM_PDUR_EXCLUSIVE_AREA_0();

   /* Conglomerate DET handling */
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
   if(CallDetReportError)
   {
      PDUR_DET_REPORT_ERROR(PDUR_SID_LOTP_TX_CONF, DetErrorCode);
   }
#endif /* if (PDUR_DEV_ERROR_DETECT == STD_ON) */

   DBG_PDUR_GATETPTXCONFIRMATION_EXIT(GMPduId, Result);
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
