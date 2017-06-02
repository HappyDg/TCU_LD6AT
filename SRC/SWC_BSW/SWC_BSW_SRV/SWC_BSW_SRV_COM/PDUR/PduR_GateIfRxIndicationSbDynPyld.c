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
#include <TSMem.h>                /* TS_MemCpy */

#if ((PDUR_ZERO_COST_OPERATION_IF == STD_OFF) &&\
     (PDUR_IFGATEWAY_SUPPORT == STD_ON) &&\
     (PDUR_SB_TX_BUFFER_SUPPORT == STD_ON))
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

FUNC(void, PDUR_CODE) PduR_GateIfRxIndicationSbDynPyld
(
    PduIdType GPduId,
    P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr
)
{
   DBG_PDUR_GATEIFRXINDICATIONSBDYNPYLD_ENTRY(GPduId, PduInfoPtr);

#if (PDUR_DEV_ERROR_DETECT == STD_ON)
   /* check if input parameter is NULL */
   if (NULL_PTR == PduInfoPtr->SduDataPtr)
   {
       PDUR_DET_REPORT_ERROR(PDUR_SID_IFGW_RXIND_SB, PDUR_E_NULL_POINTER);
   }
   else
#endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON) */
   {
      /* pointer to routing table */
      /* Deviation MISRA-1 <+2> */
      CONSTP2CONST(PduR_GTabIfRxType, AUTOMATIC, PDUR_APPL_CONST) pGTabIfRx =
         PDUR_GET_CONFIG_ADDR(PduR_GTabIfRxType, PduR_gConfigPtr->PduR_GTabIfConfig.GTabRxRef);

      /* pointer to configuration of single buffer for dynamic payload */
      /* Deviation MISRA-1 <+2> */
      CONSTP2CONST(PduR_BufSbConfigType, AUTOMATIC, PDUR_APPL_CONST) pBufSbConfig =
         PDUR_GET_CONFIG_ADDR(PduR_BufSbConfigType, PduR_gConfigPtr->PduR_BufSbDynPyldConfigRef);

      /* local representation of the BufferId */
      const uint16 BufferId = pGTabIfRx[GPduId].BufferId;

      /* pointer to memory location of single buffer in RAM */
      /* Deviation MISRA-1 <+2> */
      CONSTP2VAR(uint8, AUTOMATIC, PDUR_VAR_NOINIT) pBufMem =
         PDUR_GET_RAM_ADDR(uint8, pBufSbConfig[BufferId].MemRef);

      /* pointer to single buffer information in RAM for dynamic payload */
      /* Deviation MISRA-1 <+2> */
      CONSTP2VAR(PduR_BufSbDynPyldInfoType, AUTOMATIC, PDUR_VAR_NOINIT) pBufSbInfo =
         PDUR_GET_RAM_ADDR(PduR_BufSbDynPyldInfoType, PduR_gConfigPtr->PduR_BufSbDynPyldInfoRef);

      /* length of single buffer */
      const uint8 lenSbBuffer = pBufSbConfig[BufferId].Length;

      /* ENTER CRITICAL SECTION */
      SchM_Enter_PduR_SCHM_PDUR_EXCLUSIVE_AREA_0();

      /* allocate length value */
      if(PduInfoPtr->SduLength > lenSbBuffer)
      {
         /* use buffer length */
         pBufSbInfo[BufferId].UsedSduLength = lenSbBuffer;
      }
      else
      {
         /* use SDU length value from PduInfoPtr: the SduLength data type (fix PduLengthTypeEnum
          * uint16) is casted to uint8 since the maximum value that can be reached by SduLength
          * does not exceed the maximum value that can be represented by uint8 */
         pBufSbInfo[BufferId].UsedSduLength = (uint8)PduInfoPtr->SduLength;
      }

      /* Copy data to single buffer of PDU Router */
      TS_MemCpy(pBufMem, PduInfoPtr->SduDataPtr, pBufSbInfo[BufferId].UsedSduLength);

      /* LEAVE CRITICAL SECTION */
      SchM_Exit_PduR_SCHM_PDUR_EXCLUSIVE_AREA_0();

      {
         /* reference to set of target If-module API-functions */
         const PduR_RefToModuleAPI TargetAPIRef = pGTabIfRx[GPduId].TargetModuleAPIRef;

         /* pointer to Transmit function */
         const PduR_TransmitFpType TransmitFp = PduR_IfModuleAPI[TargetAPIRef].IfTransmit;

         /* get target PDU ID to Transmit function from routing table */
         const PduR_PduIdType TargetPduId = pGTabIfRx[GPduId].TargetPduId;

         /* check if received SDU length fits to configured Tx buffer size */
         if (PduInfoPtr->SduLength > lenSbBuffer)
         {
            /* set up data of PduInfo for Transmit call */
            PduInfoType PduR_PduInfo;
            PduR_PduInfo.SduDataPtr = PduInfoPtr->SduDataPtr;
            PduR_PduInfo.SduLength = lenSbBuffer;

            /* Call Transmit function with restricted data length */
            (void)TransmitFp(TargetPduId, &PduR_PduInfo);
         }
         else
         {
            /* Call Transmit function with PduInfoPtr passed through */
            (void)TransmitFp(TargetPduId, PduInfoPtr);
         }
      }
   }

   DBG_PDUR_GATEIFRXINDICATIONSBDYNPYLD_EXIT(GPduId, PduInfoPtr);
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
