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

#if ((PDUR_LOIF_ENABLED == STD_ON) && (PDUR_ZERO_COST_OPERATION_IF == STD_OFF))
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

FUNC(void, PDUR_CODE) PduR_GenericIfRxIndication
(
   PduIdType   RxPduId,
   P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr,
   uint8 RTabLoIfConfigIdx
)
{
   /* pointer to configuration */
   CONSTP2CONST(PduR_RTabLoIfConfigType, AUTOMATIC, PDUR_APPL_CONST) pRTabLoIfConfig =
      &PduR_gConfigPtr->PduR_RTabLoIfConfig[RTabLoIfConfigIdx];

   DBG_PDUR_GENERICIFRXINDICATION_ENTRY(RxPduId, PduInfoPtr, RTabLoIfConfigIdx);

   /* check if PDU Router is initialized */
   if(PduR_State == PDUR_UNINIT)
   {
      /* according to PDUR330, no routing shall be performed in the uninitialized state */

#if (PDUR_DEV_ERROR_DETECT == STD_ON)
      /* reported to Det in development mode */
      PDUR_DET_REPORT_ERROR(PDUR_SID_LO_RXIND, PDUR_E_INVALID_REQUEST);
   }
   /* range check of PDU ID */
   else if (RxPduId >= pRTabLoIfConfig->RTabRxCount)
   {
       PDUR_DET_REPORT_ERROR(PDUR_SID_LO_RXIND, PDUR_E_PDU_ID_INVALID);
   }
   /* check if input parameter is not NULL */
   else if (PduInfoPtr == NULL_PTR)
   {
       PDUR_DET_REPORT_ERROR(PDUR_SID_LO_RXIND, PDUR_E_NULL_POINTER);
#endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON) */
   }
   else
   {
      /* pointer to routing table */
      /* Deviation MISRA-1 <+2> */
      CONSTP2CONST(PduR_RTabLoIfType, AUTOMATIC, PDUR_APPL_CONST) pIfRTabRx =
         PDUR_GET_CONFIG_ADDR(PduR_RTabLoIfType, pRTabLoIfConfig->RTabRxRef);

      /* reference to set of target If-module API-functions */
      const PduR_RefToModuleAPI TargetAPIRef = pIfRTabRx[RxPduId].TargetModuleAPIRef;

      /* get pointer to RxIndication function from routing table */
      const PduR_IfRxIndFpType RxIndFp = PduR_IfModuleAPI[TargetAPIRef].IfRxIndication;

#if (PDUR_DEV_ERROR_DETECT == STD_ON)
      /* check if target function pointer is equal to null pointer */
      /* CHECK: NOPARSE */
      if(NULL_PTR == RxIndFp)
      {
         /* in the sense of defensive programming, call assertion if
          * target function pointer is equal to null pointer */
         PDUR_UNREACHABLE_CODE_ASSERT(PDUR_SID_LO_RXIND);
      }
      else
      /* CHECK: PARSE */
#endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON) */
      {
         /* get target PDU ID to RxIndication function from routing table */
         const PduR_PduIdType TargetPduId = pIfRTabRx[RxPduId].TargetPduId;

         /* call RxIndication function */
         RxIndFp(TargetPduId, PduInfoPtr);
      }
   }

   DBG_PDUR_GENERICIFRXINDICATION_EXIT(RxPduId, PduInfoPtr, RTabLoIfConfigIdx);
}

/* AUTOSAR Memory Mapping - end section for code */
#if (TS_MERGED_COMPILE == STD_OFF)
#define PDUR_STOP_SEC_CODE
#include <MemMap.h>
#endif

#else /* if (PDUR_LOIF_ENABLED == STD_ON) && .. */

#include <TSCompiler.h>           /* usage of macro in TSCompiler_Default.h */

/* Avoid empty translation unit according to ISO C90 */
TS_PREVENTEMPTYTRANSLATIONUNIT


/*==================[internal function definitions]=========================*/

#endif /* if (PDUR_LOIF_ENABLED == STD_ON) && .. */
/*==================[end of file]===========================================*/
