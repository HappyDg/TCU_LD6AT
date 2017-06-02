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

/*
 *  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 6.3 (advisory)
 *   'typedefs' that indicate size and signedness should be used in place
 *   of the basic types
 *
 *   Reason:
 *   Deviation originates from the TS_GETCONSTVAR macro in file TSPBConfig.h
 *   and is already documented therein as follows:
 *   In that case we explicitly cast to unsigned int (which is
 *   guaranteed to be large enough to hold the uint16 value since
 *   section 5.2.4.2.1 of the C-Standard mandates that UINT_MAX is
 *   at least 65535)), since otherwise we obtain warnings by other
 *   MISRA checkers due to the implicit conversion (e.g., by QAC).
 */

/*==================[inclusions]============================================*/

#include <PduR_Trace.h>
#include <TSAutosar.h>            /* EB specific standard types */
#include <ComStack_Types.h>       /* AUTOSAR Communication Stack types */
#include <PduR_Internal_Static.h> /* Internal API (static part) */
#include <PduR_Api_Depend.h>      /* Public API (depend part) */

#if ((PDUR_ZERO_COST_OPERATION_IF == STD_OFF) &&\
     (PDUR_LOIF_STATPAYLOAD_ENABLED == STD_ON) &&\
     (PDUR_IFGATEWAY_SUPPORT == STD_ON) &&\
     (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON))
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

FUNC(void, PDUR_CODE) PduR_GateIfTxConfirmationDf
(
    PduIdType GPduId
)
{
   /* pointer to routing table */
   /* Deviation MISRA-1 <+2> */
   CONSTP2CONST(PduR_GTabIfRxType, AUTOMATIC, PDUR_APPL_CONST) pGTabIfRx =
      PDUR_GET_CONFIG_ADDR(PduR_GTabIfRxType, PduR_gConfigPtr->PduR_GTabIfConfig.GTabRxRef);

   /* pointer to configuration of D-FIFO buffer */
   /* Deviation MISRA-1 <+2> */
   CONSTP2CONST(PduR_BufDfConfigType, AUTOMATIC, PDUR_APPL_CONST) pBufDfConfig =
      PDUR_GET_CONFIG_ADDR(PduR_BufDfConfigType, PduR_gConfigPtr->PduR_BufDfConfigRef);

   /* pointer to D-FIFO buffer information in RAM */
   /* Deviation MISRA-1 <+2> */
   CONSTP2VAR(PduR_BufDfInfoType, AUTOMATIC, PDUR_VAR_NOINIT) pBufDfInfo =
      PDUR_GET_RAM_ADDR(PduR_BufDfInfoType, PduR_gConfigPtr->PduR_BufDfInfoRef);

   /* local representation of the BufferId */
   const uint16 BufferId = pGTabIfRx[GPduId].BufferId;

   /* PduInfo for Transmit call */
   PduInfoType PduR_PduInfo;

   boolean ContinueDoWhile = TRUE;

   DBG_PDUR_GATEIFTXCONFIRMATIONDF_ENTRY(GPduId);

   do
   {
      /* ENTER CRITICAL SECTION */
      SchM_Enter_PduR_SCHM_PDUR_EXCLUSIVE_AREA_0();

      switch(pBufDfInfo[BufferId].ConfP)
      {
         case 0U:
            ContinueDoWhile = FALSE;
            break;

         case 1U:
            if (pBufDfInfo[BufferId].Count > 0U)
            {
               /* Get HeadPos of FIFO buffer of PDU Router */
               const uint8 HeadPos = pBufDfInfo[BufferId].HeadPos;

               /* length of direct FIFO buffer */
               const uint8 LenDfBuffer = pBufDfConfig[BufferId].Length;

               /* pointer to memory location of D-FIFO buffer in RAM */
               /* Deviation MISRA-1 <+2> */
               CONSTP2VAR(uint8, AUTOMATIC, PDUR_VAR_NOINIT) pBufMem =
                  PDUR_GET_RAM_ADDR(uint8, pBufDfConfig[BufferId].MemRef);

               /* set up data of PduInfo for Transmit call */
               PduR_PduInfo.SduDataPtr = &pBufMem[HeadPos * LenDfBuffer];
               PduR_PduInfo.SduLength = LenDfBuffer;

               /* set InTransmission flag */
               pBufDfInfo[BufferId].InTransmission++;
            }
            /* Count == 0U: if buffer is empty decrement 'confirmation pending' */
            else
            {
               --(pBufDfInfo[BufferId].ConfP);
               ContinueDoWhile = FALSE;
            } /* (Count > 0U) */

            break;

         default:
            /* ConfP > 1U: more than one TxConfirmation is pending (overflow occurred)*/
            --(pBufDfInfo[BufferId].ConfP);
            ContinueDoWhile = FALSE;
            break;

      } /* switch(ConfP)   */

      /* LEAVE CRITICAL SECTION */
      SchM_Exit_PduR_SCHM_PDUR_EXCLUSIVE_AREA_0();

      if (ContinueDoWhile == TRUE)
      {
         /* reference to set of target If-module API-functions */
         const PduR_RefToModuleAPI TargetAPIRef = pGTabIfRx[GPduId].TargetModuleAPIRef;

         /* get target PDU ID to Transmit function from routing table */
         const PduR_PduIdType TargetPduId = pGTabIfRx[GPduId].TargetPduId;

         /* pointer to Transmit function */
         const PduR_TransmitFpType TransmitFp = PduR_IfModuleAPI[TargetAPIRef].IfTransmit;

         if(TransmitFp(TargetPduId, &PduR_PduInfo) == E_OK)
         {
            ContinueDoWhile = FALSE;
         }

         /* ENTER CRITICAL SECTION */
         SchM_Enter_PduR_SCHM_PDUR_EXCLUSIVE_AREA_0();

         /* clear InTransmission flag */
         pBufDfInfo[BufferId].InTransmission--;

         /* set head of FIFO to next entry,
          * HeadPos ranges from 0...254, so no possible loss of data may occur */
         pBufDfInfo[BufferId].HeadPos = (uint8)((pBufDfInfo[BufferId].HeadPos + 1U) %
            pBufDfConfig[BufferId].Depth);

         /* decrement number of elements stored in T-FIFO */
         --(pBufDfInfo[BufferId].Count);

         /* LEAVE CRITICAL SECTION */
         SchM_Exit_PduR_SCHM_PDUR_EXCLUSIVE_AREA_0();
      }

   }while(ContinueDoWhile == TRUE);

   DBG_PDUR_GATEIFTXCONFIRMATIONDF_EXIT(GPduId);
}

/* AUTOSAR Memory Mapping - end section for code */
#if (TS_MERGED_COMPILE == STD_OFF)
#define PDUR_STOP_SEC_CODE
#include <MemMap.h>
#endif

#else /* if (PDUR_ZERO_COST_OPERATION_IF == STD_OFF) && .. */

#include <TSCompiler.h>           /* usage of macro in TSCompiler_Default.h */

/* Avoid empty translation unit according to ISO C90 */
TS_PREVENTEMPTYTRANSLATIONUNIT


/*==================[internal function definitions]=========================*/

#endif /* if (PDUR_ZERO_COST_OPERATION_IF == STD_OFF) && .. */
/*==================[end of file]===========================================*/
