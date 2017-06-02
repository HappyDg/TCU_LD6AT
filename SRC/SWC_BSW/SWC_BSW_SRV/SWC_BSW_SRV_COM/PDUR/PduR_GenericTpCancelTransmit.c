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

#if ((PDUR_UPTP_CANCELTX_ENABLED == STD_ON) && (PDUR_ZERO_COST_OPERATION_TP == STD_OFF))
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

FUNC(Std_ReturnType, PDUR_CODE) PduR_GenericTpCancelTransmit
(
   PduIdType   TxPduId,
   uint8 RTabUpTpConfigIdx
)
{
   /* initialize return value */
   Std_ReturnType RetVal = E_NOT_OK;

   /* pointer to configuration */
   CONSTP2CONST(PduR_RTabUpTpConfigType, AUTOMATIC, PDUR_APPL_CONST) pRTabUpTpConfig =
       &PduR_gConfigPtr->PduR_RTabUpTpConfig[RTabUpTpConfigIdx];

   DBG_PDUR_GENERICTPCANCELTRANSMIT_ENTRY(TxPduId, RTabUpTpConfigIdx);

   /* check if PDU Router is initialized */
   if(PduR_State == PDUR_UNINIT)
   {
      /* according to PDUR330, no routing shall be performed in the uninitialized state */

#if (PDUR_DEV_ERROR_DETECT == STD_ON)
      /* reported to Det in development mode */
      PDUR_DET_REPORT_ERROR(PDUR_SID_UP_CANCELTXREQ, PDUR_E_INVALID_REQUEST);
#endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON) */
   }

#if (PDUR_DEV_ERROR_DETECT == STD_ON)
   /* range check of PDU ID */
   else if (TxPduId >= pRTabUpTpConfig->RTabTxCount)
   {
       PDUR_DET_REPORT_ERROR(PDUR_SID_UP_CANCELTXREQ, PDUR_E_PDU_ID_INVALID);
   }
#endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON) */

   else
   {
      /* pointer to routing table */
      /* Deviation MISRA-1 <+2> */
      CONSTP2CONST(PduR_RTabUpTpType, AUTOMATIC, PDUR_APPL_CONST) pRTabUpTpTx =
         PDUR_GET_CONFIG_ADDR(PduR_RTabUpTpType, pRTabUpTpConfig->RTabTxRef);

      /* reference to set of target Tp-module API-functions */
      const PduR_RefToModuleAPI TargetAPIRef = pRTabUpTpTx[TxPduId].TargetModuleAPIRef;

      /* pointer to CancelTransmit function */
      const PduR_CancelTransmitFpType CancelTransmitFp =
         PduR_TpModuleAPI[TargetAPIRef].TpCancelTransmit;

      /* check if target function pointer is equal to null pointer */
      /* this might occur since multicast routing paths for CancelTransmit
         are not supported yet but specified */
      if(NULL_PTR == CancelTransmitFp)
      {
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
         PDUR_DET_REPORT_ERROR(PDUR_SID_UP_CANCELTXREQ, PDUR_E_PDU_ID_INVALID);
#endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON) */
         /* RetVal is still E_NOT_OK */
      }
      else
      {
         /* get target PDU ID */
         const PduR_PduIdType TargetPduId = pRTabUpTpTx[TxPduId].TargetPduId;

         /* call CancelTransmit function */
         RetVal = CancelTransmitFp(TargetPduId);
      }
   }


   DBG_PDUR_GENERICTPCANCELTRANSMIT_EXIT(RetVal, TxPduId, RTabUpTpConfigIdx);
   return RetVal;
}

/* AUTOSAR Memory Mapping - end section for code */
#if (TS_MERGED_COMPILE == STD_OFF)
#define PDUR_STOP_SEC_CODE
#include <MemMap.h>
#endif

#else /* if (PDUR_UPTP_CANCELTX_ENABLED == STD_ON) && .. */

#include <TSCompiler.h>           /* usage of macro in TSCompiler_Default.h */

/* Avoid empty translation unit according to ISO C90 */
TS_PREVENTEMPTYTRANSLATIONUNIT


/*==================[internal function definitions]=========================*/

#endif /* if (PDUR_UPTP_CANCELTX_ENABLED == STD_ON) && .. */
/*==================[end of file]===========================================*/
