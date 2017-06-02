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

#if ((PDUR_ZERO_COST_OPERATION_IF == STD_OFF) && \
    (PDUR_MULTICAST_FROMIF_SUPPORT == STD_ON))
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

FUNC(void, PDUR_CODE) PduR_MultiIfRxIndication
(
   PduIdType MPduId,
   P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr
)
{
   /* pointer to routing table */
   /* Deviation MISRA-1 <+2> */
   CONSTP2CONST(PduR_MTabLoIfRxType, AUTOMATIC, PDUR_APPL_CONST) pMTabIfRx =
      PDUR_GET_CONFIG_ADDR(PduR_MTabLoIfRxType, PduR_gConfigPtr->PduR_MTabLoIfConfig.MTabRxRef);

   /* iterator for all entries providing the same MPduId */
   PduR_PduIdType MTabPos = (PduR_PduIdType)MPduId;

   /* provided local variable to ease readability of while condition */
   uint8 MoreEntries;

   DBG_PDUR_MULTIIFRXINDICATION_ENTRY(MPduId, PduInfoPtr);

   /* loop through all routing paths matching the current MPduId */
   do{
      /* reference to set of target If-module API-functions */
      const PduR_RefToModuleAPI TargetAPIRef = pMTabIfRx[MTabPos].TargetModuleAPIRef;

      /* get pointer to RxIndication function from routing table */
      const PduR_IfRxIndFpType RxIndFp = PduR_IfModuleAPI[TargetAPIRef].IfRxIndication;

      /* get target PDU ID to RxIndication function from routing table */
      const PduR_PduIdType TargetPduId = pMTabIfRx[MTabPos].TargetPduId;

      /* initialize to check while condition */
      MoreEntries = pMTabIfRx[MTabPos].MoreEntries;

      /* call RxIndication function */
      RxIndFp(TargetPduId, PduInfoPtr);

      /* select next entry in routing table */
      MTabPos++;

   }while(MoreEntries != PDUR_LAST_MULTICAST_ENTRY_OF_PDUID);

   DBG_PDUR_MULTIIFRXINDICATION_EXIT(MPduId, PduInfoPtr);
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
