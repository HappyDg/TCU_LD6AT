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

FUNC(void, PDUR_CODE) PduR_GateTpRxIndication
(
   PduIdType GMPduId,
   NotifResultType Result
)
{
   /* TP gateway session in use */
   PduR_GateTpSessionIndexType SessionIndex;

   boolean CallLoTpTransmit = FALSE;

   /* PduInfo for Transmit */
   PduInfoType PduR_PduInfo;

   /* pointer to TP gateway sessions */
   CONSTP2VAR(PduR_GateTpSessionInfoType, AUTOMATIC, PDUR_VAR_NOINIT) pSessionInfos =
      PDUR_GET_RAM_ADDR(PduR_GateTpSessionInfoType, PduR_gConfigPtr->PduR_GateTpSessionInfoRef);

   /* pointer to routing table */
   CONSTP2CONST(PduR_GTabTpRxType, AUTOMATIC, PDUR_APPL_CONST) pGTabTpRx =
      PDUR_GET_CONFIG_ADDR(PduR_GTabTpRxType, PduR_gConfigPtr->PduR_GTabTpConfig.GTabRxRef);

#if (PDUR_DEV_ERROR_DETECT == STD_ON)
   boolean CallDetReportError = FALSE;
   uint8 DetErrorCode = PDUR_E_INVALID_REQUEST;
#endif /* if (PDUR_DEV_ERROR_DETECT == STD_ON) */

   DBG_PDUR_GATETPRXINDICATION_ENTRY(GMPduId, Result);

   /* ENTER CRITICAL SECTION */
   SchM_Enter_PduR_SCHM_PDUR_EXCLUSIVE_AREA_0();

   /* get TP gateway session in use */
   SessionIndex = PduR_GetGateTpSessionInUse(GMPduId);

   /* TpRxIndication called without preceding StartOfReception */
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
   if(SessionIndex == PDUR_NO_GATETP_SESSION_ASSIGNED)
   {
      CallDetReportError = TRUE;
      DetErrorCode = PDUR_E_INVALID_REQUEST;
   }
   else
#endif /* if (PDUR_DEV_ERROR_DETECT == STD_ON) */
   {
      uint8 ResultGetBitAbort;

      /* reception completed */
      TS_AtomicSetBit_8(&pSessionInfos[SessionIndex].Status, PDUR_GATETP_RECEPT_FIN_POS);

      /* reception failed */
      if(Result != NTFRSLT_OK)
      {
         /* abort transmission */
         TS_AtomicSetBit_8(&pSessionInfos[SessionIndex].Status, PDUR_GATETP_ABORT_POS);
      }

      /* check if TP gateway session shall be released) */
      TS_GetBit(&pSessionInfos[SessionIndex].Status, PDUR_GATETP_ABORT_POS, uint8,
                ResultGetBitAbort);
      if((ResultGetBitAbort > 0U) && (pSessionInfos[SessionIndex].PendTxConfCount == 0U))
      {
         /* release assigned TP gateway session */
         PduR_ReleaseGateTpSession(&pSessionInfos[SessionIndex]);

         /* release assigned Tp gateway queue */
         PduR_ReleaseGateTpQueue(GMPduId);
      }
      /* direct gateway */
      else if(pGTabTpRx[GMPduId].TpThreshold == PDUR_GATETPTHRESHOLD_DIRECT)
      {
         const PduR_BufTpIndexType BufTpIndex = (PduR_BufTpIndexType)SessionIndex;

         /* pointer to TP buffer configurations */
         CONSTP2CONST(PduR_BufTpConfigType, AUTOMATIC, PDUR_APPL_CONST) pBufTpConfig =
            PDUR_GET_CONFIG_ADDR(PduR_BufTpConfigType, PduR_gConfigPtr->PduR_BufTpConfigRef);

         /* pointer to the first element of the TP buffer */
         CONSTP2VAR(uint8, AUTOMATIC, PDUR_VAR_NOINIT) pStartTpBuf =
            PDUR_GET_RAM_ADDR(uint8, pBufTpConfig[BufTpIndex].MemRef);

         /* No need for a check of TpSduLength equal to AvailableDataSize,
          * the LoTP module is responsible for correctly provided data */

         /* setup PduInfo for Transmit */
         /* SduLength: No explicit cast is necessary since PduR_PduLengthType and PduLengthType
          * are both fixed with uint16 by the Java generator */
         /* SduDataPtr: For the upper layer called via Transmit, a dedicated SduDataPtr has to be
          * provided */
         PduR_PduInfo.SduLength = pSessionInfos[SessionIndex].TpSduLength;
         PduR_PduInfo.SduDataPtr = pStartTpBuf;

         /* call all LoTp_Transmit with PduR_PduInfo after critical section is closed */
         CallLoTpTransmit = TRUE;
      }
      /* routing on the fly */
      else
      {
         uint8 ResultGetBitTxComplete;
         TS_GetBit(&pSessionInfos[SessionIndex].Status, PDUR_GATETP_TX_COMPLETE_POS, uint8,
                   ResultGetBitTxComplete);

         /* provide Transmit call at end of successful reception */
         if(ResultGetBitTxComplete == 0U)
         {
            /* setup PduInfo for Transmit */
            /* No explicit cast is necessary since PduR_PduLengthType and PduLengthType
             * are both fixed with uint16 by the Java generator */
            PduR_PduInfo.SduLength = pSessionInfos[SessionIndex].TpSduLength;
            PduR_PduInfo.SduDataPtr = NULL_PTR;

            /* call LoTp_Transmit with PduR_PduInfo after critical section is closed */
            CallLoTpTransmit = TRUE;
         }

         /* RxIndication after TxConfirmation */
         if((ResultGetBitTxComplete > 0U) && (pSessionInfos[SessionIndex].PendTxConfCount == 0U))
         {
            /* release assigned TP gateway session */
            PduR_ReleaseGateTpSession(&pSessionInfos[SessionIndex]);

            /* release assigned Tp gateway queue */
            PduR_ReleaseGateTpQueue(GMPduId);
         }
      }
   }

   /* EXIT CRITICAL SECTION */
   SchM_Exit_PduR_SCHM_PDUR_EXCLUSIVE_AREA_0();

   if(CallLoTpTransmit)
   {
     /* no correct Transmit call initially */
      boolean SingleTransmitOk = FALSE;

      /* initialize iterator for all entries providing the same GMPduId */
      PduR_PduIdType GTabPos = GMPduId;

      /* provided local variable to ease readability of while condition */
      uint8 MoreEntries;

      /* loop through all routing table entries matching the current GMPduId */
      do{
         /* reference to set of target Tp-module API-functions */
         const PduR_RefToModuleAPI TargetAPIRef = pGTabTpRx[GTabPos].TargetModuleAPIRef;

         /* get pointer to Transmit function */
         const PduR_TransmitFpType TransmitFp = PduR_TpModuleAPI[TargetAPIRef].TpTransmit;

         /* get target PDU ID to Transmit function from routing table */
         const PduR_PduIdType TargetPduId = pGTabTpRx[GTabPos].TargetPduId;

         /* call Transmit function */
         const Std_ReturnType RetVal = TransmitFp(TargetPduId, &PduR_PduInfo);

          /* initialize to check while condition */
         MoreEntries = pGTabTpRx[GTabPos].MoreEntries;

         /* ENTER CRITICAL SECTION */
         SchM_Enter_PduR_SCHM_PDUR_EXCLUSIVE_AREA_0();

#if(PDUR_MULTICAST_LOTPTOUP_SUPPORT == STD_ON)
         if(!((MoreEntries == PDUR_LAST_MULTICAST_ENTRY_OF_PDUID) &&
              (PDUR_GATETP_CALL_UPPER_LAYER(TargetAPIRef))))
         {
#endif
            /* handle Transmit call */
            if(RetVal == E_OK)
            {
               /* increment counter for pending TpTxConfirmation */
               pSessionInfos[SessionIndex].PendTxConfCount++;

               /* at least one Transmit call was successfully */
               SingleTransmitOk = TRUE;
            }
            /* handle rejected Transmit call */
            else
            {
               /* indicate abort of transmission to CopyTxData */
               TS_AtomicSetBit_8(&pSessionInfos[SessionIndex].Status, PDUR_GATETP_ABORT_POS);

               /* development error detection handling for rejected transmit call */
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
               CallDetReportError = TRUE;
               DetErrorCode = PDUR_E_TP_TX_REQ_REJECTED;
#endif /* if (PDUR_DEV_ERROR_DETECT == STD_ON) */

            }


#if(PDUR_MULTICAST_LOTPTOUP_SUPPORT == STD_ON)
         /* the reception by the upper layer shall not influence the
            TP gateway (no else statement) */
         }
#endif

         /* EXIT CRITICAL SECTION */
         SchM_Exit_PduR_SCHM_PDUR_EXCLUSIVE_AREA_0();

         GTabPos++;

      }while(MoreEntries != PDUR_LAST_MULTICAST_ENTRY_OF_PDUID);

      /* release TP gateway session when all Transmit calls are rejected,
       * no need to protect since no Transmit is called */
      if(SingleTransmitOk == FALSE)
      {
         /* release assigned TP gateway session */
         PduR_ReleaseGateTpSession(&pSessionInfos[SessionIndex]);

         /* release assigned Tp gateway queue */
         PduR_ReleaseGateTpQueue(GMPduId);
      }
      /* no need to protect since PduR_GateTpCopyTxData can only be called successfully if all
       * LoTp_Transmit calls have finished */
      else
      {
         /* provide information on all finished LoTp_Transmit calls to PduR_GateTpCopyTxData */
         TS_AtomicSetBit_8(&pSessionInfos[SessionIndex].Status, PDUR_GATETP_TX_COMPLETE_POS);
      }

   }

   /* Conglomerate DET handling */
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
   if(CallDetReportError)
   {
      PDUR_DET_REPORT_ERROR(PDUR_SID_LOTP_RXIND, DetErrorCode);
   }
#endif /* if (PDUR_DEV_ERROR_DETECT == STD_ON) */

   DBG_PDUR_GATETPRXINDICATION_EXIT(GMPduId, Result);
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
