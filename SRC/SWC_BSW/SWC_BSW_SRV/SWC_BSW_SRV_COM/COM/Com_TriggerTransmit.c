/**
 * \file
 *
 * \brief AUTOSAR Com
 *
 * This file contains the implementation of the AUTOSAR
 * module Com.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */


/* Misra-C:2004 Deviations:
 *
 * MISRA-1) Deviated Rule: 11.1 (required)
 * "Conversions shall not be performed between a pointer to a function and any type other than an integral type."
 *
 * Reason:
 * Actually this is not a cast between a pointer to a function, since 0 is the
 * null pointer constant.
 *
 * MISRA-2) Deviated Rule: 11.3 (advisory)
 * "A cast should not be performed between a pointer type and an integral type."
 *
 * Reason:
 * Actually this is not a cast between a pointer and a integral type, since 0
 * is null pointer constant.
 *
 * MISRA-3) Deviated Rule: 6.3 (advisory)
 * "'typedefs' that indicate size and signedness should be used in place of the basic types."
 *
 * Reason:
 * In this case variables are casted to a natural integral type since, the value is further used
 * for purposes where natural types are most efficient (e.g. indexing).
 *
 */


/*==================[inclusions]=============================================*/

#include <Com_Trace.h>
#include <TSAutosar.h>          /* EB specific standard types */
#include <ComStack_Types.h>     /* AUTOSAR standard types */
#include <Com_Api_Static.h>     /* module public static API */
#include <Com_Priv.h>           /* module internal stuff */
#include <Com_Cbk_Static.h>     /* Callback declaration header */
#include <TSMem.h>              /* TS_MemCpy */

#include <Com_Core_TxIPdu.h>    /* Header TxIPdu functions */

#if (COM_DEV_ERROR_DETECT == STD_ON)
#include <Det.h>                /* Det API */
#endif

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/



#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_START_SEC_CODE
#include <MemMap.h>
#endif

/**
 * \brief Com_TriggerTransmit - copy data to PDU-router memory
 *
 * a function to be used to fetch data from the COM immediately
 * Preconditions:
 * - COM should be initialized
 *
 * \param[in] ComTxPduId - ID of the PDU which's data shall be copied
 * \param[in] PduInfoPtr - Contains a pointer to a buffer (SduDataPtr) to where the SDU
 * shall be copied to. On return, the service will indicate the length of
 * the copied SDU data in SduLength.
 * \return
 * \retval E_OK: SDU has been copied and SduLength indicates the
 * number of copied bytes.
 * \retval E_NOT_OK: No SDU has been copied. PduInfoPtr must not be
 * used since it may contain a NULL pointer or point to invalid data.
 *
 * \ServiceID{0x41}
 * \Reentrancy{Re-entrant for different values of ComTxPduId only.}
 * \Synchronicity{Synchronous}
 */
FUNC(Std_ReturnType, COM_CODE) Com_TriggerTransmit
(
   PduIdType ComTxPduId,
   P2VAR(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr
)
{
   Std_ReturnType retval = E_NOT_OK;
   boolean proceedProcessing = TRUE;

   /* pointer to the configuration of the IPdu to which the signal belongs */
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr;
   P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) pdudataptr; /* pointer to the data of the PDU */

#if (COM_CALL_OUT_FUNC_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE)
#if (COM_TRIGGERTX_CALLOUT_ENABLE == STD_ON)
   P2VAR(Com_TxCalloutType, AUTOMATIC, COM_APPL_CODE) fptr;
#endif /* (COM_TRIGGERTX_CALLOUT_ENABLE == STD_ON) */
#endif /* (COM_CALL_OUT_FUNC_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

   DBG_COM_TRIGGERTRANSMIT_ENTRY(ComTxPduId,PduInfoPtr);


#if (COM_DEV_ERROR_DETECT == STD_ON)

   /* check SignalDataPtr */
   if (PduInfoPtr == NULL_PTR)
   {
      COM_DET_REPORTERROR(COM_E_PARAM_POINTER, COMServiceId_TriggerTransmit);
   }
   else
   {
      /* set return value in case function fails */
      PduInfoPtr->SduLength = 0U;

      /* check whether Com is initialized */
      if (Com_InitStatus == COM_EB_UNINIT)
      {
         COM_DET_REPORTERROR(COM_E_UNINIT, COMServiceId_TriggerTransmit);
      }
      /* check if SduPtr is NULL_PTR */
      else if (PduInfoPtr->SduDataPtr == NULL_PTR)
      {
         COM_DET_REPORTERROR(COM_E_PARAM_POINTER, COMServiceId_TriggerTransmit);
      }
      /* check if ComTxPduId is valid */
      else if (Com_gConfigPtr->ComTxIPduArraySize <= ComTxPduId)
      {
         COM_DET_REPORTERROR(COM_E_PARAM, COMServiceId_TriggerTransmit);
      }
      else

#endif /* COM_DEV_ERROR_DETECT */

      {
         /* get IPdu to which ComTxPduId identifies and check if the IPdu is valid */
         /* Deviation MISRA-2 */
         /* Deviation MISRA-3 */
         IPduPtr = COM_GET_CONFIG_ELEMENT(ComTxIPduType, Com_gConfigPtr->ComTxIPduRef, ComTxPduId);

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
         /* CHECK: NOPARSE */
         if (NULL_PTR == IPduPtr)
         {
            COM_PRECONDITION_ASSERT(
                  (NULL_PTR == IPduPtr),
                  COMServiceId_TriggerTransmit);
         }
         else if (IPduPtr->ComConfigCheckData != COM_CONFIG_CHECK_TX_IPDU)
         {
            COM_PRECONDITION_ASSERT(
                  (IPduPtr->ComConfigCheckData == COM_CONFIG_CHECK_TX_IPDU),
                  COMServiceId_TriggerTransmit);
         }
         else
            /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */

         {
            /* get data pointer of IPdu */
            pdudataptr = &Com_gDataMemPtr[(IPduPtr->ComIPduValueRef)];

#if (COM_CALL_OUT_FUNC_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE)
#if (COM_TRIGGERTX_CALLOUT_ENABLE == STD_ON)
            /* Get the function pointer of the callout function */
            if (IPduPtr->ComIPduTrigTxCallOutFuncPtrRef != COM_CALL_OUT_FUNC_PTR_NULL)
            {
               fptr = Com_TxCallouts[(IPduPtr->ComIPduTrigTxCallOutFuncPtrRef)];

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
               /* Check if fptr is valid */
               /* CHECK: NOPARSE */
               /* Deviation MISRA-1 */
               /* Deviation MISRA-2 */
               if (fptr == NULL_PTR)
               {
                  COM_PRECONDITION_ASSERT((fptr != NULL_PTR), COMServiceId_TriggerTransmit);
                  proceedProcessing = FALSE;
               }
               else
                  /* CHECK: PARSE */
#endif /* COM_PRECONDITION_ASSERT_ENABLED */

               {
                  /* call callout, ignore return value (see COM395) */
                  (void)fptr(ComTxPduId, pdudataptr);
               }
            }

#endif /* (COM_TRIGGERTX_CALLOUT_ENABLE == STD_ON) */
#endif /* (COM_CALL_OUT_FUNC_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
            /* CHECK: NOPARSE */
            if (proceedProcessing)
                /* CHECK: PARSE */
#endif /* COM_PRECONDITION_ASSERT_ENABLED */
            {
               TS_GetBit(&Com_gDataMemPtr[(Com_gConfigPtr->ComTxIPduStatusBase + ComTxPduId)],
                     COM_TXPDU_STARTED, uint8, proceedProcessing);
            }

            if (proceedProcessing)
            {
               /* Enter critical section;
                * the section is critical as an interrupting SendSignal call may
                * cause data garbage to be copied */
               Com_EB_SchM_Enter_SCHM_COM_EXCLUSIVE_AREA_0();

               /* copy PDU content */
               TS_MemCpy(PduInfoPtr->SduDataPtr, pdudataptr, IPduPtr->ComIPduSize);

               /* Leave critical section */
               Com_EB_SchM_Exit_SCHM_COM_EXCLUSIVE_AREA_0();

               /* set size of copied bytes */
               PduInfoPtr->SduLength = IPduPtr->ComIPduSize;

#if (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)
#if (COM_CL_UB_TX_TRIGGERTRANSMIT_ENABLE == STD_ON)

#if (!((COM_UPDATE_BIT_TX_CONFIG == COM_UPDATE_BIT_PRESENT_FOR_ALL) &&  \
      (COM_CL_UB_TX_TRANSMIT_ENABLE == STD_OFF) && \
      (COM_CL_UB_TX_TXCONFIRMATION_ENABLE == STD_OFF)))
               if (COM_GET_COM_TX_IPDU_CLEAR_UPDATE_BIT(IPduPtr) == COM_CL_UB_TRIGGERTRANSMIT)
#endif

               {
                  Com_EB_ClearTxUpdateBits(IPduPtr);
               }

#endif /* (COM_CL_UB_TX_TRIGGERTRANSMIT_ENABLE == STD_ON) */
#endif /* (COM_UPDATE_BIT_TX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) */

               retval = E_OK;
            } /* proceedProcessing */
         }
      }

#if (COM_DEV_ERROR_DETECT == STD_ON)
   }
#endif /* COM_DEV_ERROR_DETECT == STD_ON */


   DBG_COM_TRIGGERTRANSMIT_EXIT(retval,ComTxPduId,PduInfoPtr);
   return retval;
}                               /* Com_TriggerTransmit */

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_STOP_SEC_CODE
#include <MemMap.h>
#endif

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/

