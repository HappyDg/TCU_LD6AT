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


#if((PDUR_ZERO_COST_OPERATION_TP == STD_OFF) && \
    (PDUR_MULTICAST_UPTOLOTP_SUPPORT == STD_ON))
#include <SchM_PduR.h>            /* Schedule Manager for module PduR */
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
 ** \brief Auxiliary TP multicast handler function
 **
 ** Assigns free multicast transmit session.
 ** If no multicast transmit session can be assigned PDUR_NO_MULTITP_SESSION_ASSIGNED is returned.
 **
 ** \param[in]  MTpTxPduId  PduId group of multicast Transmit to LoTP(s)
 **
 ** \return     Assigned multicast transmit session index.
 ** \retval     uint8       Multicast transmit session index assigned
 **                         or PDUR_NO_MULTITP_SESSION_ASSIGNED if no session can be assigned.
 **/
STATIC FUNC(uint8, PDUR_CODE) PduR_AssignMultiTpTxSession
(
   PduR_PduIdType MTpTxPduId
);

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

FUNC(Std_ReturnType, PDUR_CODE) PduR_MultiTpTransmit
(
   PduIdType MTpTxPduId,
   P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr
)
{
   /* return value */
   Std_ReturnType RetVal = E_OK;

   /* determine pending multicast transmit session */
   const uint8 PendingSessionIndex = PduR_SearchMultiTpTxSessionIndex((PduR_PduIdType)MTpTxPduId);

   DBG_PDUR_MULTITPTRANSMIT_ENTRY(MTpTxPduId, PduInfoPtr);

   /* check for pending multicast transmit session */
   if(PendingSessionIndex != PDUR_NO_MULTITP_SESSION_ASSIGNED)
   {
      /* E_NOT_OK is returned for already pending multicast transmit session */
      RetVal = E_NOT_OK;
   }
   else
   {
      /* determine multicast transmit session */
      const uint8 SessionIndex = PduR_AssignMultiTpTxSession((PduR_PduIdType)MTpTxPduId);

      /* free multicast transmit session assigned */
      if(SessionIndex != PDUR_NO_MULTITP_SESSION_ASSIGNED)
      {
         /* no correct Transmit call initially */
         boolean SingleTransmitOk = FALSE;

         /* pointer to routing table */
         CONSTP2CONST(PduR_MTabUpTpTxType, AUTOMATIC, PDUR_APPL_CONST) pMTabUpTpTx =
            PDUR_GET_CONFIG_ADDR(PduR_MTabUpTpTxType,
                                 PduR_gConfigPtr->PduR_MTabUpTpConfig.MTabTxRef);

         /* pointer to multicast transmit sessions */
         CONSTP2VAR(PduR_MultiTpTxSessionInfoType, AUTOMATIC, PDUR_VAR_NOINIT) pMultiTpTxSessionInfo =
            PDUR_GET_RAM_ADDR(PduR_MultiTpTxSessionInfoType,
                              PduR_gConfigPtr->PduR_MultiTpTxSessionInfoRef);

         /* initialize iterator for all entries providing the same MTpTxPduId */
         PduR_PduIdType MTabPos = (PduR_PduIdType)MTpTxPduId;

         /* provided local variable to ease readability of while condition */
         uint8 MoreEntries;

         /* loop through all routing table entries matching the current MTpTxPduId */
         do{
            /* reference set of TP API-functions */
            const PduR_RefToModuleAPI TargetAPIRef = pMTabUpTpTx[MTabPos].TargetModuleAPIRef;

            /* pointer to Transmit function */
            const PduR_TransmitFpType TransmitFp = PduR_TpModuleAPI[TargetAPIRef].TpTransmit;

            /* get target PDU ID */
            const PduR_PduIdType TargetPduId = pMTabUpTpTx[MTabPos].TargetPduId;

            /* initialize to check while condition */
            MoreEntries = pMTabUpTpTx[MTabPos].MoreEntries;

            /* handle rejected Transmit call */
            if(TransmitFp(TargetPduId, PduInfoPtr) == E_NOT_OK)
            {
               /* E_NOT_OK is returned if at least one of the Transmit functions returns E_NOT_OK */
               RetVal = E_NOT_OK;

               /* indicate abort of transmission to CopyTxData */
               TS_AtomicSetBit_8(&pMultiTpTxSessionInfo[SessionIndex].Status,
                  PDUR_MULTITPTX_ABORT_POS);
            }
            else
            {
               /* ENTER CRITICAL SECTION */
               SchM_Enter_PduR_SCHM_PDUR_EXCLUSIVE_AREA_0();

               /* increment part of Status holding the number of successful Transmit calls */
               pMultiTpTxSessionInfo[SessionIndex].Status++;

               /* LEAVE CRITICAL SECTION  */
               SchM_Exit_PduR_SCHM_PDUR_EXCLUSIVE_AREA_0();

               /* at least one Transmit call was successfully */
               SingleTransmitOk = TRUE;
            }

            MTabPos++;

         }while(MoreEntries != PDUR_LAST_MULTICAST_ENTRY_OF_PDUID);

         /* release multicast transmit session when all Transmit calls are rejected */
         if(SingleTransmitOk == FALSE)
         {
            /* release assigned session info */
            PduR_ReleaseMultiTpTxSession(SessionIndex);
         }
         else
         {
            /* store SduLength for retry parameter TxTpDataCnt applied within CopyTxData */
            pMultiTpTxSessionInfo[SessionIndex].SduLength = PduInfoPtr->SduLength;

            /* provide information of finished Transmit calls to CopyTxData */
            TS_AtomicSetBit_8(&pMultiTpTxSessionInfo[SessionIndex].Status,
               PDUR_MULTITPTX_TX_COMPLETE_POS);
         }
      }
      else
      {
         /* return E_NOT_OK when all sessions are blocked */
         RetVal = E_NOT_OK;
      } /* end if SessionIndex != PDUR_NO_MULTITP_SESSION_ASSIGNED */
   }

   DBG_PDUR_MULTITPTRANSMIT_EXIT(RetVal, MTpTxPduId, PduInfoPtr);

   return RetVal;
}


/*==================[internal function definitions]=========================*/

STATIC FUNC(uint8, PDUR_CODE) PduR_AssignMultiTpTxSession
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
      PDUR_GET_RAM_ADDR(PduR_MultiTpTxSessionInfoType,
      PduR_gConfigPtr->PduR_MultiTpTxSessionInfoRef);

   DBG_PDUR_ASSIGNMULTITPTXSESSION_ENTRY(MTpTxPduId);

   /* search for multicast transmit session in use */
   while((LoopIdx < PduR_gConfigPtr->PduR_MultiTpTxRPathsMax) &&
         (pMultiTpTxSessionInfo[LoopIdx].MTpTxPduId != PDUR_INVALID_PDUID))
   {
      /* loop is left if free multicast transmit session is detected. If no free session is
         detected, LoopIdx holds the value of PduR_gConfigPtr->PduR_MultiTpTxRPathsMax */
      LoopIdx++;
   }

   /* assign free multicast transmit session */
   if(LoopIdx < PduR_gConfigPtr->PduR_MultiTpTxRPathsMax)
   {
      /* assign multicast transmit session member */
      pMultiTpTxSessionInfo[LoopIdx].MTpTxPduId = MTpTxPduId;

      /* update return value to assigned multicast transmit session index */
      RetValSessionIndex = (uint8)LoopIdx;
   }

   DBG_PDUR_ASSIGNMULTITPTXSESSION_EXIT(RetValSessionIndex, MTpTxPduId);

   return RetValSessionIndex;
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
